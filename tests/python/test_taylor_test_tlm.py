"""
Taylor test for TLM (Tangent Linear Model) verification.

Verifies that for each supported Rosenbrock solver variant, the TLM satisfies:
    ||F(C + ε·δC) - F(C)|| / (ε * ||TLM(δC)||) → 1 as ε → 0

This is a NUMERICAL test that:
1. Builds a mechanism's symbolic ODE system and Jacobian
2. Evaluates them numerically at concrete concentrations
3. Implements a pure-Python Rosenbrock forward integrator (multi-step)
4. Implements the TLM propagation through the same Rosenbrock steps
5. Verifies first-order Taylor convergence for decreasing ε

Tested on:
- Chapman mechanism (4 species)
- A small multi-species mechanism (3 species, non-trivial coupling)

**Validates: Requirements 7.1, 7.3**
"""

import numpy as np
import pytest
import sympy as sp
from mkpp.lowering import prepare_unified_jacobian
from mkpp.model import (
    AerosolRepresentation,
    MechanismDefinition,
    PhaseMode,
    ReactionDefinition,
    SpeciesDefinition,
)
from mkpp.rosenbrock import SOLVER_COEFFICIENTS, get_A, get_C

# ---------------------------------------------------------------------------
# Mechanism builders
# ---------------------------------------------------------------------------


def _build_chapman_mechanism():
    """Build the Chapman mechanism (4 species: O, O2, O3, M).

    Uses the mechanism YAML but with fixed species (O2, M) handled
    by giving them constant concentrations in the substitution dict.
    """
    sp_o = SpeciesDefinition(name="O", phase=PhaseMode.GAS)
    sp_o2 = SpeciesDefinition(name="O2", phase=PhaseMode.GAS, role="fixed")
    sp_o3 = SpeciesDefinition(name="O3", phase=PhaseMode.GAS)
    sp_m = SpeciesDefinition(name="M", phase=PhaseMode.GAS, role="fixed")

    r1 = ReactionDefinition(
        reaction_type="PHOTOLYSIS",
        reactants={"O2": 1.0},
        products={"O": 2.0},
        rate_expression="",
        parameters={"A": "J_phot1"},
        stiff=False,
        continuous_transition=True,
    )
    r2 = ReactionDefinition(
        reaction_type="ARRHENIUS",
        reactants={"O": 1.0, "O2": 1.0, "M": 1.0},
        products={"O3": 1.0, "M": 1.0},
        rate_expression="",
        parameters={"A": 6.0e-34, "B": 0.0, "C": 0.0},
        stiff=True,
    )
    r3 = ReactionDefinition(
        reaction_type="PHOTOLYSIS",
        reactants={"O3": 1.0},
        products={"O": 1.0, "O2": 1.0},
        rate_expression="",
        parameters={"A": "J_phot2"},
        stiff=False,
        continuous_transition=True,
    )
    r4 = ReactionDefinition(
        reaction_type="ARRHENIUS",
        reactants={"O": 1.0, "O3": 1.0},
        products={"O2": 2.0},
        rate_expression="",
        parameters={"A": 8.0e-12, "B": 0.0, "C": 0.0},
        stiff=True,
    )

    return MechanismDefinition(
        name="chapman_taylor_test",
        description="Chapman mechanism for Taylor test",
        aerosol_representation=AerosolRepresentation.BULK,
        species=[sp_o, sp_o2, sp_o3, sp_m],
        phases=[],
        reactions=[r1, r2, r3, r4],
    )


def _build_small_multispecies_mechanism():
    """Build a small 3-species mechanism with non-trivial coupling.

    A → B → C with feedback (C catalyzes A→B), providing a stiff coupled system
    ideal for testing TLM convergence. All rates are simple Arrhenius with fixed
    temperature.
    """
    sp_a = SpeciesDefinition(name="A", phase=PhaseMode.GAS)
    sp_b = SpeciesDefinition(name="B", phase=PhaseMode.GAS)
    sp_c = SpeciesDefinition(name="C", phase=PhaseMode.GAS)

    r1 = ReactionDefinition(
        reaction_type="ARRHENIUS",
        reactants={"A": 1.0},
        products={"B": 1.0},
        rate_expression="",
        parameters={"A": 1.0e-2, "B": 0.0, "C": 0.0},
        stiff=True,
    )
    r2 = ReactionDefinition(
        reaction_type="ARRHENIUS",
        reactants={"B": 1.0},
        products={"C": 1.0},
        rate_expression="",
        parameters={"A": 5.0e-3, "B": 0.0, "C": 0.0},
        stiff=True,
    )
    r3 = ReactionDefinition(
        reaction_type="ARRHENIUS",
        reactants={"C": 1.0, "A": 1.0},
        products={"B": 2.0},
        rate_expression="",
        parameters={"A": 2.0e-3, "B": 0.0, "C": 0.0},
        stiff=True,
    )

    return MechanismDefinition(
        name="small_multispecies_taylor_test",
        description="Small 3-species coupled mechanism for Taylor test",
        aerosol_representation=AerosolRepresentation.BULK,
        species=[sp_a, sp_b, sp_c],
        phases=[],
        reactions=[r1, r2, r3],
    )


# ---------------------------------------------------------------------------
# Numerical evaluation utilities
# ---------------------------------------------------------------------------


def _build_numeric_evaluators(mech):
    """Build numeric evaluator functions for f(C) and J(C) from the mechanism.

    Returns:
        f_func: callable(state_vec) -> numpy array of dC/dt
        jac_func: callable(state_vec) -> numpy 2D array (Jacobian)
        species_map: list of species names in order
        env_subs: substitution dict for environmental parameters
    """
    lowering_data = prepare_unified_jacobian(mech)
    species_map = lowering_data["species_map"]
    f_total_sym = lowering_data["f_implicit"] + lowering_data["f_explicit"]
    J_sym = lowering_data["jacobian_matrix"]
    N = len(species_map)

    # Build the species symbol list in order
    c_symbols = [sp.Symbol(f"C_{name}", real=True, nonnegative=True) for name in species_map]

    # Environmental substitutions (fixed values for numerical evaluation)
    env_subs = {
        sp.Symbol("Temp", real=True, nonnegative=True): 298.0,
        sp.Symbol("Press", real=True, nonnegative=True): 101325.0,
        sp.Symbol("M_density", real=True, nonnegative=True): 2.5e19,
        sp.Symbol("v_gas", real=True, nonnegative=True): 300.0,
        sp.Symbol("S_a", real=True, nonnegative=True): 1.0e-6,
    }

    # Add photolysis rate symbols with realistic values
    for i in range(10):
        env_subs[sp.Symbol(f"J_{i}", real=True, nonnegative=True)] = 1.0e-4

    # Also add named photolysis symbols that might be used
    env_subs[sp.Symbol("J_phot1", real=True, nonnegative=True)] = 1.0e-5
    env_subs[sp.Symbol("J_phot2", real=True, nonnegative=True)] = 1.0e-3

    # Pre-substitute environmental parameters into expressions
    f_total_sub = f_total_sym.subs(env_subs)
    J_sub = J_sym.subs(env_subs)

    # Use sympy lambdify for efficient numerical evaluation
    f_lambdified = sp.lambdify(c_symbols, f_total_sub, modules="numpy")
    J_lambdified = sp.lambdify(c_symbols, J_sub, modules="numpy")

    def f_func(state_vec):
        """Evaluate f(C) at the given state vector."""
        args = list(state_vec)
        result = f_lambdified(*args)
        return np.array(result, dtype=float).flatten()

    def jac_func(state_vec):
        """Evaluate J(C) at the given state vector."""
        args = list(state_vec)
        result = J_lambdified(*args)
        return np.array(result, dtype=float).reshape(N, N)

    return f_func, jac_func, species_map, env_subs


# ---------------------------------------------------------------------------
# Python-level Rosenbrock integrator (mirrors generated C++ logic)
# ---------------------------------------------------------------------------


def _rosenbrock_step(y, dt, f_func, jac_func, tableau):
    """Execute one Rosenbrock step with given tableau.

    Returns (y_new, err_norm) where err_norm is the local error estimate.
    This mirrors the generated C++ logic exactly.
    """
    N = len(y)
    S = tableau.stages
    gamma = tableau.Gamma[0]

    # Compute Jacobian at current state
    J = jac_func(y)

    # Form W = (1/(gamma*dt))*I - J
    W = (1.0 / (gamma * dt)) * np.eye(N) - J

    # Storage for stage vectors K_i
    K = np.zeros((S, N))

    # Current F evaluation state (for NewF reuse)
    current_F = None

    for stage in range(1, S + 1):
        # Compute intermediate state Y_stage
        if stage == 1:
            Y_stage = y.copy()
        else:
            Y_stage = y.copy()
            for j in range(1, stage):
                a_val = get_A(tableau, stage, j)
                if a_val != 0.0:
                    Y_stage += a_val * K[j - 1]

        # Evaluate F at Y_stage if NewF is True
        if tableau.NewF[stage - 1]:
            current_F = f_func(Y_stage)

        # Form RHS
        rhs = current_F.copy()
        for j in range(1, stage):
            c_val = get_C(tableau, stage, j)
            if c_val != 0.0:
                rhs += (c_val / dt) * K[j - 1]

        # Solve W * K_stage = rhs
        K[stage - 1] = np.linalg.solve(W, rhs)

    # Solution update
    y_new = y.copy()
    for j in range(S):
        if tableau.M[j] != 0.0:
            y_new += tableau.M[j] * K[j]

    # Error estimate
    yerr = np.zeros(N)
    for j in range(S):
        if tableau.E[j] != 0.0:
            yerr += tableau.E[j] * K[j]

    # Compute scaled error norm
    atol = 1.0e-6
    rtol = 1.0e-3
    err_norm_sq = 0.0
    for i in range(N):
        sci = atol + rtol * max(abs(y[i]), abs(y_new[i]))
        err_norm_sq += (yerr[i] / sci) ** 2
    err_norm = np.sqrt(err_norm_sq / N)

    return y_new, err_norm, K


def _rosenbrock_integrate(y0, dt_total, f_func, jac_func, tableau, max_steps=200):
    """Integrate from t=0 to t=dt_total using adaptive Rosenbrock stepping.

    Returns (y_final, checkpoint_data) where checkpoint_data is a list of
    (h, state_at_step_start) tuples for each accepted step.
    """
    len(y0)
    tableau.Gamma[0]
    elo = tableau.ELO

    y = y0.copy()
    t = 0.0
    dt = dt_total * 0.1  # Initial step size guess
    dt = min(dt, dt_total)

    safety = 0.9
    min_shrink = 0.2
    max_growth = 6.0

    checkpoint_data = []  # List of (h, state_before_update) for accepted steps

    for _ in range(max_steps * 10):  # Allow retries
        if t >= dt_total:
            break

        # Don't overshoot
        dt = min(dt, dt_total - t)
        if dt <= 0:
            break

        # Save state before step (for checkpoint)
        y_saved = y.copy()

        # Execute one Rosenbrock step
        y_new, err_norm, K = _rosenbrock_step(y, dt, f_func, jac_func, tableau)
        err_norm = max(err_norm, 1.0e-10)

        # Step-size control
        if elo == 2.0:
            factor = safety / np.sqrt(err_norm)
        elif elo == 3.0:
            factor = safety / np.cbrt(err_norm)
        else:
            factor = safety * err_norm ** (-1.0 / elo)
        factor = max(min_shrink, min(factor, max_growth))

        if err_norm <= 1.0:
            # Accept step
            checkpoint_data.append((dt, y_saved))
            y = y_new
            t += dt
            dt *= factor
            if len(checkpoint_data) >= max_steps:
                break
        else:
            # Reject step, reduce dt
            dt *= factor

    return y, checkpoint_data


def _rosenbrock_tlm_propagate(delta_C, checkpoint_data, jac_func, tableau):
    """Propagate perturbation δC forward through checkpointed Rosenbrock steps.

    Implements the TLM formula:
      For each step (forward, using checkpointed h and state):
        For i = 1, ..., s:
          δK_i = W^{-1} * [ J * (δC + Σ_{j=1}^{i-1} A_{i,j} * δK_j)
                             + Σ_{j=1}^{i-1} C_{i,j}/h * δK_j ]
        δC_new = δC + Σ_{i=1}^{s} M_i * δK_i

    Returns the final propagated perturbation.
    """
    S = tableau.stages
    gamma = tableau.Gamma[0]
    dC = delta_C.copy()
    N = len(dC)

    for h, state in checkpoint_data:
        # Compute Jacobian at saved state
        J = jac_func(state)

        # Form W = (1/(gamma*h))*I - J
        W = (1.0 / (gamma * h)) * np.eye(N) - J

        # Storage for TLM stage vectors
        dK = np.zeros((S, N))

        for stage in range(1, S + 1):
            # Build argument to J: arg = δC + Σ_{j<i} A_{i,j} * δK_j
            arg = dC.copy()
            for j in range(1, stage):
                a_val = get_A(tableau, stage, j)
                if a_val != 0.0:
                    arg += a_val * dK[j - 1]

            # RHS = J * arg + Σ_{j<i} C_{i,j}/h * δK_j
            rhs = J @ arg
            for j in range(1, stage):
                c_val = get_C(tableau, stage, j)
                if c_val != 0.0:
                    rhs += (c_val / h) * dK[j - 1]

            # Solve W * δK_i = rhs
            dK[stage - 1] = np.linalg.solve(W, rhs)

        # Update δC: δC += Σ M_i * δK_i
        for j in range(S):
            if tableau.M[j] != 0.0:
                dC += tableau.M[j] * dK[j]

    return dC


# ---------------------------------------------------------------------------
# Taylor test implementation
# ---------------------------------------------------------------------------


def _run_taylor_test(f_func, jac_func, y0, dt_total, delta_C, tableau, epsilons=None, max_steps=200):
    """Run the Taylor test and return convergence ratios.

    For each ε in epsilons:
      1. Compute F(C) = forward_integrate(C, dt)
      2. Compute F(C + ε*δC) = forward_integrate(C + ε*δC, dt)
      3. Compute TLM(δC) via propagation through same steps as F(C)
      4. ratio = ||F(C + ε*δC) - F(C)|| / (ε * ||TLM(δC)||)

    Returns list of ratios.
    """
    if epsilons is None:
        epsilons = [1e-2, 1e-3, 1e-4, 1e-5, 1e-6, 1e-7]

    # Step 1: Compute reference forward integration F(C) and get checkpoint data
    y_final, checkpoint_data = _rosenbrock_integrate(y0, dt_total, f_func, jac_func, tableau, max_steps=max_steps)

    # Step 2: Compute TLM(δC) using the checkpoint from the reference integration
    tlm_result = _rosenbrock_tlm_propagate(delta_C, checkpoint_data, jac_func, tableau)
    tlm_norm = np.linalg.norm(tlm_result)

    if tlm_norm < 1e-30:
        pytest.skip("TLM result is essentially zero - cannot compute meaningful ratio")

    ratios = []
    for eps in epsilons:
        # Step 3: Compute perturbed forward integration F(C + ε*δC)
        y0_perturbed = y0 + eps * delta_C
        y_perturbed, _ = _rosenbrock_integrate(y0_perturbed, dt_total, f_func, jac_func, tableau, max_steps=max_steps)

        # Step 4: Compute difference and ratio
        diff = y_perturbed - y_final
        diff_norm = np.linalg.norm(diff)

        if eps * tlm_norm > 1e-30:
            ratio = diff_norm / (eps * tlm_norm)
            ratios.append(ratio)
        else:
            ratios.append(float("nan"))

    return ratios


# ---------------------------------------------------------------------------
# Test classes
# ---------------------------------------------------------------------------

ALL_SOLVERS = list(SOLVER_COEFFICIENTS.keys())


@pytest.mark.parametrize("solver_name", ALL_SOLVERS)
class TestTaylorTestChapman:
    """Taylor test for TLM using the Chapman mechanism (4 species)."""

    def test_taylor_convergence(self, solver_name: str):
        """
        Verify ||F(C+ε·δC) - F(C)|| / (ε * ||TLM(δC)||) → 1 as ε → 0
        for the Chapman mechanism.

        **Validates: Requirements 7.1, 7.3**
        """
        tableau = SOLVER_COEFFICIENTS[solver_name]
        mech = _build_chapman_mechanism()
        f_func, jac_func, species_map, _ = _build_numeric_evaluators(mech)
        N = len(species_map)

        # Initial state (realistic atmospheric concentrations)
        # Species order from lowering: O, O2, O3, M
        y0 = np.array([1.0e6, 5.0e18, 1.0e12, 2.5e19], dtype=float)

        # Random perturbation direction (scaled to reasonable magnitude)
        rng = np.random.default_rng(seed=42)
        delta_C = rng.standard_normal(N)
        # Scale perturbation relative to state magnitudes
        delta_C = delta_C * np.abs(y0) * 0.01

        # Integration time (short — a few steps)
        dt_total = 60.0  # 60 seconds

        # Run Taylor test with decreasing epsilon
        epsilons = [1e-3, 1e-4, 1e-5, 1e-6, 1e-7, 1e-8]
        ratios = _run_taylor_test(f_func, jac_func, y0, dt_total, delta_C, tableau, epsilons)

        # Verify convergence toward 1.0
        # For a correct TLM, the ratio should approach 1.0 as ε → 0
        # We check that at least one of the middle ratios is close to 1.0
        # (very small ε might suffer from roundoff, very large ε from nonlinearity)
        valid_ratios = [r for r in ratios if not np.isnan(r) and r > 0]

        assert len(valid_ratios) >= 3, f"[{solver_name}] Too few valid ratios: {ratios}"

        # Find the ratio closest to 1.0 (should be in the "sweet spot" range)
        best_ratio = min(valid_ratios, key=lambda r: abs(r - 1.0))
        assert abs(best_ratio - 1.0) < 0.05, (
            f"[{solver_name}] Taylor test failed: best ratio = {best_ratio:.6f}, "
            f"expected ≈ 1.0. All ratios: {[f'{r:.6f}' for r in ratios]}"
        )

        # Additionally check monotonic convergence: ratios should approach 1.0
        # from above or below as ε decreases (until roundoff takes over)
        # Find where convergence is best (minimum distance from 1)
        distances = [abs(r - 1.0) for r in valid_ratios]
        best_idx = distances.index(min(distances))

        # At least the first few ratios should be converging toward 1.0
        # (i.e., distance from 1.0 should generally decrease)
        if best_idx >= 2:
            assert (
                distances[1] < distances[0] or distances[1] < 0.1
            ), f"[{solver_name}] Ratios not converging: {[f'{r:.6f}' for r in valid_ratios]}"


@pytest.mark.parametrize("solver_name", ALL_SOLVERS)
class TestTaylorTestSmallMultispecies:
    """Taylor test for TLM using a small 3-species coupled mechanism."""

    def test_taylor_convergence(self, solver_name: str):
        """
        Verify ||F(C+ε·δC) - F(C)|| / (ε * ||TLM(δC)||) → 1 as ε → 0
        for a small multi-species mechanism.

        **Validates: Requirements 7.1, 7.3**
        """
        tableau = SOLVER_COEFFICIENTS[solver_name]
        mech = _build_small_multispecies_mechanism()
        f_func, jac_func, species_map, _ = _build_numeric_evaluators(mech)
        N = len(species_map)

        # Initial state (moderate concentrations)
        y0 = np.array([1.0, 0.5, 0.1], dtype=float)

        # Random perturbation
        rng = np.random.default_rng(seed=123)
        delta_C = rng.standard_normal(N) * 0.01

        # Integration time
        dt_total = 10.0

        # Run Taylor test
        epsilons = [1e-3, 1e-4, 1e-5, 1e-6, 1e-7, 1e-8]
        ratios = _run_taylor_test(f_func, jac_func, y0, dt_total, delta_C, tableau, epsilons)

        # Verify convergence toward 1.0
        valid_ratios = [r for r in ratios if not np.isnan(r) and r > 0]

        assert len(valid_ratios) >= 3, f"[{solver_name}] Too few valid ratios: {ratios}"

        best_ratio = min(valid_ratios, key=lambda r: abs(r - 1.0))
        assert abs(best_ratio - 1.0) < 0.05, (
            f"[{solver_name}] Taylor test failed: best ratio = {best_ratio:.6f}, "
            f"expected ≈ 1.0. All ratios: {[f'{r:.6f}' for r in ratios]}"
        )

    def test_taylor_first_order_convergence_rate(self, solver_name: str):
        """
        Verify that the first-order Taylor ratio converges monotonically toward 1.0
        as ε decreases (before roundoff kicks in).

        The ratio ||F(C+ε·δC) - F(C)|| / (ε * ||TLM(δC)||) should get closer to 1.0
        for successive halvings of ε, demonstrating first-order accuracy of the TLM.

        Note: Because adaptive stepping means the perturbed trajectory may take
        different steps than the reference, we verify first-order convergence of
        the ratio rather than strict O(ε²) second-order remainder behavior.

        **Validates: Requirements 7.1, 7.3**
        """
        tableau = SOLVER_COEFFICIENTS[solver_name]
        mech = _build_small_multispecies_mechanism()
        f_func, jac_func, species_map, _ = _build_numeric_evaluators(mech)
        N = len(species_map)

        y0 = np.array([1.0, 0.5, 0.1], dtype=float)
        rng = np.random.default_rng(seed=456)
        delta_C = rng.standard_normal(N) * 0.01
        dt_total = 10.0

        # Run Taylor test with a geometric sequence of epsilons
        epsilons = [1e-3, 1e-4, 1e-5, 1e-6, 1e-7]
        ratios = _run_taylor_test(f_func, jac_func, y0, dt_total, delta_C, tableau, epsilons)

        valid_ratios = [r for r in ratios if not np.isnan(r) and r > 0]
        assert len(valid_ratios) >= 3, f"[{solver_name}] Too few valid ratios: {ratios}"

        # Compute distances from 1.0
        distances = [abs(r - 1.0) for r in valid_ratios]

        # Find the optimal index (minimum distance)
        best_idx = distances.index(min(distances))

        # Verify that up to the optimal point, distances are generally decreasing
        # (allowing for one "hiccup" due to step-size adaptation differences)
        converging_pairs = sum(1 for i in range(min(best_idx, len(distances) - 1)) if distances[i + 1] < distances[i])
        total_pairs = min(best_idx, len(distances) - 1)

        if total_pairs >= 2:
            assert converging_pairs >= total_pairs // 2, (
                f"[{solver_name}] Ratios not converging toward 1.0: " f"distances = {[f'{d:.6e}' for d in distances]}"
            )
