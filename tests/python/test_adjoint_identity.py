"""
Test: Adjoint identity <TLM(δC), λ> == <δC, ADJ(λ)> for all Rosenbrock solver variants.

Task 8.2 — Verifies the discrete adjoint identity (duality property):
    dot(TLM(δC), λ) == dot(δC, ADJ(λ))

This ensures that the TLM and adjoint integrators are exact transposes of each other
when operating on the same checkpointed forward trajectory.

The test performs a fully numerical Python simulation of:
  1. Forward Rosenbrock integration with checkpointing (saves h and state per step)
  2. TLM forward propagation through the same checkpointed steps
  3. Adjoint backward propagation through the same checkpointed steps
  4. Inner product identity verification to relative tolerance 1e-12

The linearized TLM formula (as emitted by MKPP):
  For each step (forward, using checkpointed h and J):
    For i = 1, ..., s:
      RHS_i = J * (δC + Σ_{j<i} A_{i,j} * δK_j) + Σ_{j<i} C_{i,j}/h * δK_j
      δK_i = W^{-1} * RHS_i
    δC += Σ M_i * δK_i

The exact adjoint (transpose of the linearized TLM map):
  For each step (backward, using same checkpointed h and J):
    Initialize grad_dK[i] = M_i * λ for all i
    For i = s, ..., 1:
      w_i = W^{-T} * grad_dK[i]
      For j < i: grad_dK[j] += A(i,j) * J^T * w_i + C(i,j)/h * w_i
    λ += Σ J^T * w_i

**Validates: Requirements 7.2, 7.3**
"""

import numpy as np
import pytest
import sympy as sp
from mkpp.lowering import (
    prepare_unified_jacobian,
)
from mkpp.model import (
    AerosolRepresentation,
    MechanismDefinition,
    PhaseMode,
    ReactionDefinition,
    SpeciesDefinition,
)
from mkpp.rosenbrock import SOLVER_COEFFICIENTS, get_A, get_C

# ---------------------------------------------------------------------------
# Mechanism builder
# ---------------------------------------------------------------------------


def _build_chapman_mechanism():
    """Build Chapman mechanism (O, O3, O1D) with non-trivial coupling for testing."""
    sp_o = SpeciesDefinition(name="O", phase=PhaseMode.GAS)
    sp_o3 = SpeciesDefinition(name="O3", phase=PhaseMode.GAS)
    sp_o1d = SpeciesDefinition(name="O1D", phase=PhaseMode.GAS)

    r1 = ReactionDefinition(
        reaction_type="PHOTOLYSIS",
        reactants={"O3": 1.0},
        products={"O1D": 1.0, "O": 1.0},
        rate_expression="J1*O3",
        parameters={"A": "J1"},
        stiff=True,
    )
    r2 = ReactionDefinition(
        reaction_type="ARRHENIUS",
        reactants={"O": 1.0, "O3": 1.0},
        products={"O": 2.0},
        rate_expression="k2*O*O3",
        parameters={"A": 1e-15, "B": 0.0, "C": 0.0},
        stiff=True,
    )
    return MechanismDefinition(
        name="chapman_adjoint_identity_test",
        description="Chapman mechanism for adjoint identity verification",
        aerosol_representation=AerosolRepresentation.BULK,
        species=[sp_o, sp_o3, sp_o1d],
        phases=[],
        reactions=[r1, r2],
    )


# ---------------------------------------------------------------------------
# Numerical Jacobian evaluator
# ---------------------------------------------------------------------------


def _evaluate_jacobian_at_state(jacobian_matrix, species_map, state, jvals):
    """
    Numerically evaluate the symbolic Jacobian at given concentration state.

    Args:
        jacobian_matrix: sympy Matrix (N x N)
        species_map: list of species names in order
        state: numpy array of concentrations (length N)
        jvals: dict mapping J-value symbol names -> numeric value

    Returns:
        numpy array (N x N) with numeric Jacobian values
    """
    N = jacobian_matrix.shape[0]

    # Build substitution dict
    subs = {}
    for idx, name in enumerate(species_map):
        sym = sp.Symbol(f"C_{name}", real=True, nonnegative=True)
        subs[sym] = float(state[idx])

    # Add J-value symbols
    for name, val in jvals.items():
        sym = sp.Symbol(name, real=True, nonnegative=True)
        subs[sym] = val

    # Temperature/pressure (constant, needed even if Jacobian doesn't depend on them)
    subs[sp.Symbol("Temp", real=True, nonnegative=True)] = 298.0
    subs[sp.Symbol("Press", real=True, nonnegative=True)] = 101325.0

    J_numeric = np.zeros((N, N))
    for i in range(N):
        for j in range(N):
            expr = jacobian_matrix[i, j]
            if expr != 0:
                J_numeric[i, j] = float(expr.subs(subs))

    return J_numeric


def _evaluate_rates_at_state(f_total, species_map, state, jvals):
    """
    Numerically evaluate the ODE RHS f(C) at given state.

    Args:
        f_total: sympy Matrix (N x 1) of rate expressions
        species_map: list of species names
        state: numpy array of concentrations
        jvals: dict of J-value symbol values

    Returns:
        numpy array (N,) of rate values
    """
    N = len(species_map)

    subs = {}
    for idx, name in enumerate(species_map):
        sym = sp.Symbol(f"C_{name}", real=True, nonnegative=True)
        subs[sym] = float(state[idx])

    for name, val in jvals.items():
        sym = sp.Symbol(name, real=True, nonnegative=True)
        subs[sym] = val

    subs[sp.Symbol("Temp", real=True, nonnegative=True)] = 298.0
    subs[sp.Symbol("Press", real=True, nonnegative=True)] = 101325.0

    F = np.zeros(N)
    for i in range(N):
        F[i] = float(f_total[i].subs(subs))
    return F


# ---------------------------------------------------------------------------
# Numerical Rosenbrock integrators (Python reference)
# ---------------------------------------------------------------------------


def _rosenbrock_forward_checkpoint(state_0, dt_total, tableau, J_sym, f_total, species_map, jvals, num_steps=5):
    """
    Rosenbrock forward integration with fixed step sizes, saving checkpoints.

    Uses fixed equal step sizes for reproducibility (no adaptive step control).
    Returns the final state and checkpoint data (list of {h, state}).

    Args:
        state_0: initial state (N,)
        dt_total: total integration time
        tableau: RosenbrockTableau
        J_sym: symbolic Jacobian matrix
        f_total: sympy Matrix of ODE RHS
        species_map: species name list
        jvals: J-value dict
        num_steps: number of equal-sized steps

    Returns:
        state_final: numpy array (N,)
        checkpoints: list of dicts with 'h' and 'state' keys
    """
    N = len(species_map)
    S = tableau.stages
    gamma = tableau.Gamma[0]
    h = dt_total / num_steps

    state = state_0.copy()
    checkpoints = []

    for step in range(num_steps):
        # Save checkpoint BEFORE the step (state at entry)
        checkpoints.append({"h": h, "state": state.copy()})

        # Evaluate Jacobian at current state
        J = _evaluate_jacobian_at_state(J_sym, species_map, state, jvals)

        # Form W = (1/(gamma*h))*I - J
        W = (1.0 / (gamma * h)) * np.eye(N) - J

        # Compute stages K_1, ..., K_s
        K = np.zeros((S, N))

        for i in range(S):
            # Evaluate F at the appropriate intermediate state
            if i == 0 or tableau.NewF[i]:
                y_i = state.copy()
                for j in range(i):
                    a_val = get_A(tableau, i + 1, j + 1)
                    if a_val != 0.0:
                        y_i += a_val * K[j]
                F_i = _evaluate_rates_at_state(f_total, species_map, y_i, jvals)

            # RHS = F_i + Σ_{j<i} (C_{i,j}/h) * K_j
            rhs = F_i.copy()
            for j in range(i):
                c_val = get_C(tableau, i + 1, j + 1)
                if c_val != 0.0:
                    rhs += (c_val / h) * K[j]

            # Solve W * K_i = rhs
            K[i] = np.linalg.solve(W, rhs)

        # Update state: state += Σ M_i * K_i
        for i in range(S):
            state += tableau.M[i] * K[i]

    return state, checkpoints


def _rosenbrock_tlm(delta_C, checkpoints, tableau, J_sym, species_map, jvals):
    """
    Rosenbrock TLM forward propagation through checkpointed steps.

    Implements the linearized TLM formula as emitted by MKPP:
      For each checkpointed step:
        For i = 1, ..., s:
          RHS_i = J*(δC + Σ_{j<i} A_{i,j}*δK_j) + Σ_{j<i} C_{i,j}/h*δK_j
          δK_i = W^{-1} * RHS_i
        δC += Σ M_i * δK_i

    Args:
        delta_C: initial perturbation (N,)
        checkpoints: list of {'h': ..., 'state': ...}
        tableau: RosenbrockTableau
        J_sym: symbolic Jacobian matrix
        species_map: species name list
        jvals: J-value dict

    Returns:
        delta_C_final: propagated perturbation (N,)
    """
    N = len(species_map)
    S = tableau.stages
    gamma = tableau.Gamma[0]

    dC = delta_C.copy()

    for chk in checkpoints:
        h = chk["h"]
        state = chk["state"]

        # Evaluate Jacobian at checkpointed state
        J = _evaluate_jacobian_at_state(J_sym, species_map, state, jvals)

        # Form W = (1/(gamma*h))*I - J
        W = (1.0 / (gamma * h)) * np.eye(N) - J

        # TLM stages
        dK = np.zeros((S, N))

        for i in range(S):
            # arg = δC + Σ_{j<i} A_{i,j} * δK_j
            arg = dC.copy()
            for j in range(i):
                a_val = get_A(tableau, i + 1, j + 1)
                if a_val != 0.0:
                    arg += a_val * dK[j]

            # RHS = J * arg + Σ_{j<i} C_{i,j}/h * δK_j
            rhs = J @ arg
            for j in range(i):
                c_val = get_C(tableau, i + 1, j + 1)
                if c_val != 0.0:
                    rhs += (c_val / h) * dK[j]

            # Solve W * δK_i = RHS
            dK[i] = np.linalg.solve(W, rhs)

        # Update: δC += Σ M_i * δK_i
        for i in range(S):
            dC += tableau.M[i] * dK[i]

    return dC


def _rosenbrock_adjoint(lam, checkpoints, tableau, J_sym, species_map, jvals):
    """
    Exact adjoint (transpose) of the linearized TLM map.

    This implements the reverse-mode differentiation of the TLM formula, ensuring
    the adjoint identity <TLM(δC), λ> == <δC, ADJ(λ)> holds to machine precision.

    For each checkpointed step (backward):
      Initialize grad_dK[i] = M_i * λ for all i
      For i = s, s-1, ..., 1:
        w_i = W^{-T} * grad_dK[i]
        For j < i: grad_dK[j] += A(i,j) * J^T * w_i + C(i,j)/h * w_i
      λ += Σ J^T * w_i

    Args:
        lam: initial adjoint variable (N,)
        checkpoints: list of {'h': ..., 'state': ...}
        tableau: RosenbrockTableau
        J_sym: symbolic Jacobian matrix
        species_map: species name list
        jvals: J-value dict

    Returns:
        lam_final: adjoint propagated backward (N,)
    """
    N = len(species_map)
    S = tableau.stages
    gamma = tableau.Gamma[0]

    lam_out = lam.copy()

    # Walk backward through checkpoints
    for chk in reversed(checkpoints):
        h = chk["h"]
        state = chk["state"]

        # Evaluate Jacobian at checkpointed state
        J = _evaluate_jacobian_at_state(J_sym, species_map, state, jvals)

        # Form W = (1/(gamma*h))*I - J
        W = (1.0 / (gamma * h)) * np.eye(N) - J

        # Initialize gradient accumulators for each stage
        # These accumulate contributions from the final output and later stages
        grad_dK = np.zeros((S, N))
        for i in range(S):
            grad_dK[i] = tableau.M[i] * lam_out.copy()

        # Process stages in reverse order
        w = np.zeros((S, N))
        for i in range(S - 1, -1, -1):
            # Solve W^T * w_i = grad_dK[i]
            w[i] = np.linalg.solve(W.T, grad_dK[i])

            # Propagate gradient to earlier stages
            for j in range(i):
                # A(i+1, j+1) in 1-indexed tableau terms
                a_val = get_A(tableau, i + 1, j + 1)
                c_val = get_C(tableau, i + 1, j + 1)

                if a_val != 0.0:
                    grad_dK[j] += a_val * (J.T @ w[i])

                if c_val != 0.0:
                    grad_dK[j] += (c_val / h) * w[i]

        # Final update: λ += Σ J^T * w_i
        for i in range(S):
            lam_out += J.T @ w[i]

    return lam_out


# ---------------------------------------------------------------------------
# Test class
# ---------------------------------------------------------------------------

ALL_SOLVERS = list(SOLVER_COEFFICIENTS.keys())


@pytest.mark.parametrize("solver_name", ALL_SOLVERS)
class TestAdjointIdentity:
    """
    Verify the discrete adjoint identity <TLM(δC), λ> == <δC, ADJ(λ)>
    for all Rosenbrock solver variants using the Chapman mechanism.

    This test exercises the mathematical duality between the TLM (tangent linear model)
    and the discrete adjoint: when both use the same checkpoint data (same W matrices,
    same step sizes), the inner products must be equal to machine precision.
    """

    def test_adjoint_identity_random_vectors(self, solver_name: str):
        """
        Core adjoint identity test with random δC and λ vectors.

        Verifies: dot(TLM(δC), λ) == dot(δC, ADJ(λ)) to relative tolerance 1e-12.
        """
        tableau = SOLVER_COEFFICIENTS[solver_name]

        # Build mechanism and compute symbolic Jacobian
        mech = _build_chapman_mechanism()
        lowering_data = prepare_unified_jacobian(mech)
        J_sym = lowering_data["jacobian_matrix"]
        species_map = lowering_data["species_map"]
        f_total = lowering_data["f_implicit"] + lowering_data["f_explicit"]
        N = len(species_map)

        # Initial conditions (realistic atmospheric concentrations)
        state_0 = np.array([1.0e6, 1.0e12, 1.0e4])  # O, O3, O1D
        jvals = {"J_0": 5.0e-5}

        # Integration parameters
        dt_total = 60.0  # 60 seconds
        num_steps = 5

        # Run forward integration to get checkpoints
        _state_final, checkpoints = _rosenbrock_forward_checkpoint(
            state_0, dt_total, tableau, J_sym, f_total, species_map, jvals, num_steps
        )

        # Generate random perturbation and adjoint vectors
        rng = np.random.default_rng(seed=42)
        delta_C = rng.standard_normal(N) * 1.0e3  # Scale to meaningful perturbation
        lam = rng.standard_normal(N) * 1.0e3

        # Run TLM forward: δC -> TLM(δC)
        tlm_result = _rosenbrock_tlm(delta_C, checkpoints, tableau, J_sym, species_map, jvals)

        # Run adjoint backward: λ -> ADJ(λ)
        adj_result = _rosenbrock_adjoint(lam, checkpoints, tableau, J_sym, species_map, jvals)

        # Compute inner products
        lhs = np.dot(tlm_result, lam)  # <TLM(δC), λ>
        rhs = np.dot(delta_C, adj_result)  # <δC, ADJ(λ)>

        # Verify identity to relative tolerance 1e-12
        denom = max(abs(lhs), abs(rhs), 1e-30)
        rel_err = abs(lhs - rhs) / denom

        assert rel_err < 1e-12, (
            f"[{solver_name}] Adjoint identity violated: "
            f"<TLM(δC), λ> = {lhs:.15e}, <δC, ADJ(λ)> = {rhs:.15e}, "
            f"relative error = {rel_err:.3e} (expected < 1e-12)"
        )

    def test_adjoint_identity_multiple_random_trials(self, solver_name: str):
        """
        Run the adjoint identity test with 5 different random vector pairs
        to increase confidence.
        """
        tableau = SOLVER_COEFFICIENTS[solver_name]

        mech = _build_chapman_mechanism()
        lowering_data = prepare_unified_jacobian(mech)
        J_sym = lowering_data["jacobian_matrix"]
        species_map = lowering_data["species_map"]
        f_total = lowering_data["f_implicit"] + lowering_data["f_explicit"]
        N = len(species_map)

        state_0 = np.array([1.0e6, 1.0e12, 1.0e4])
        jvals = {"J_0": 5.0e-5}
        dt_total = 120.0  # 2 minutes
        num_steps = 8

        _state_final, checkpoints = _rosenbrock_forward_checkpoint(
            state_0, dt_total, tableau, J_sym, f_total, species_map, jvals, num_steps
        )

        rng = np.random.default_rng(seed=12345)

        for trial in range(5):
            delta_C = rng.standard_normal(N) * 1.0e4
            lam = rng.standard_normal(N) * 1.0e4

            tlm_result = _rosenbrock_tlm(delta_C, checkpoints, tableau, J_sym, species_map, jvals)
            adj_result = _rosenbrock_adjoint(lam, checkpoints, tableau, J_sym, species_map, jvals)

            lhs = np.dot(tlm_result, lam)
            rhs = np.dot(delta_C, adj_result)

            denom = max(abs(lhs), abs(rhs), 1e-30)
            rel_err = abs(lhs - rhs) / denom

            assert rel_err < 1e-12, (
                f"[{solver_name}] Adjoint identity violated on trial {trial}: "
                f"<TLM(δC), λ> = {lhs:.15e}, <δC, ADJ(λ)> = {rhs:.15e}, "
                f"relative error = {rel_err:.3e}"
            )

    def test_adjoint_identity_unit_vectors(self, solver_name: str):
        """
        Test adjoint identity with canonical unit vectors.

        Using unit vectors for δC and λ is a strong test because it probes
        individual rows/columns of the propagator matrix.
        """
        tableau = SOLVER_COEFFICIENTS[solver_name]

        mech = _build_chapman_mechanism()
        lowering_data = prepare_unified_jacobian(mech)
        J_sym = lowering_data["jacobian_matrix"]
        species_map = lowering_data["species_map"]
        f_total = lowering_data["f_implicit"] + lowering_data["f_explicit"]
        N = len(species_map)

        state_0 = np.array([5.0e7, 2.0e11, 3.0e5])
        jvals = {"J_0": 1.0e-4}
        dt_total = 30.0
        num_steps = 3

        _state_final, checkpoints = _rosenbrock_forward_checkpoint(
            state_0, dt_total, tableau, J_sym, f_total, species_map, jvals, num_steps
        )

        # Test all combinations of unit vectors
        for i in range(N):
            for j in range(N):
                delta_C = np.zeros(N)
                delta_C[i] = 1.0
                lam = np.zeros(N)
                lam[j] = 1.0

                tlm_result = _rosenbrock_tlm(delta_C, checkpoints, tableau, J_sym, species_map, jvals)
                adj_result = _rosenbrock_adjoint(lam, checkpoints, tableau, J_sym, species_map, jvals)

                lhs = np.dot(tlm_result, lam)
                rhs = np.dot(delta_C, adj_result)

                denom = max(abs(lhs), abs(rhs), 1e-30)
                if denom < 1e-30:
                    # Both sides are essentially zero — identity holds trivially
                    continue

                rel_err = abs(lhs - rhs) / denom

                assert rel_err < 1e-12, (
                    f"[{solver_name}] Adjoint identity violated for "
                    f"e_{i} / e_{j}: "
                    f"<TLM(e_{i}), e_{j}> = {lhs:.15e}, "
                    f"<e_{i}, ADJ(e_{j})> = {rhs:.15e}, "
                    f"relative error = {rel_err:.3e}"
                )

    def test_adjoint_identity_different_initial_conditions(self, solver_name: str):
        """
        Test adjoint identity with different initial conditions to verify
        the property holds regardless of the forward trajectory.
        """
        tableau = SOLVER_COEFFICIENTS[solver_name]

        mech = _build_chapman_mechanism()
        lowering_data = prepare_unified_jacobian(mech)
        J_sym = lowering_data["jacobian_matrix"]
        species_map = lowering_data["species_map"]
        f_total = lowering_data["f_implicit"] + lowering_data["f_explicit"]
        N = len(species_map)

        # Different atmospheric scenarios
        scenarios = [
            {"state": np.array([1.0e8, 5.0e11, 1.0e6]), "jvals": {"J_0": 1.0e-3}},
            {"state": np.array([1.0e4, 1.0e13, 1.0e2]), "jvals": {"J_0": 1.0e-6}},
            {"state": np.array([1.0e10, 1.0e10, 1.0e10]), "jvals": {"J_0": 5.0e-4}},
        ]

        rng = np.random.default_rng(seed=7777)

        for scenario in scenarios:
            state_0 = scenario["state"]
            jvals = scenario["jvals"]

            _state_final, checkpoints = _rosenbrock_forward_checkpoint(
                state_0, 60.0, tableau, J_sym, f_total, species_map, jvals, num_steps=4
            )

            delta_C = rng.standard_normal(N) * 1.0e5
            lam = rng.standard_normal(N) * 1.0e5

            tlm_result = _rosenbrock_tlm(delta_C, checkpoints, tableau, J_sym, species_map, jvals)
            adj_result = _rosenbrock_adjoint(lam, checkpoints, tableau, J_sym, species_map, jvals)

            lhs = np.dot(tlm_result, lam)
            rhs = np.dot(delta_C, adj_result)

            denom = max(abs(lhs), abs(rhs), 1e-30)
            rel_err = abs(lhs - rhs) / denom

            assert rel_err < 1e-12, (
                f"[{solver_name}] Adjoint identity violated for scenario " f"state={state_0}: relative error = {rel_err:.3e}"
            )
