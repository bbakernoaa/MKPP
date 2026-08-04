"""
Unit test: transposed solve matches numpy solve(W.T, b) for non-symmetric Chapman Jacobian.

Task 1.3 — Verifies that the transposed symbolic LU solve produces the same result
as numpy.linalg.solve(W.T, b) for the Chapman mechanism's non-symmetric Jacobian
evaluated at concrete concentration values.

This exercises the full pipeline:
  1. Build Chapman mechanism Jacobian symbolically
  2. Compute LU plan + transposed LU plan
  3. Numerically evaluate W = (1/(gamma*h))*I - J at concrete species concentrations
  4. Execute numeric LU factorization following the symbolic plan
  5. Execute transposed forward/backward substitution
  6. Compare against numpy dense reference to machine precision
"""
import pytest
import re
import numpy as np
import sympy as sp
from mkpp.model import (
    MechanismDefinition,
    SpeciesDefinition,
    ReactionDefinition,
    PhaseMode,
    AerosolRepresentation,
    SymbolicLUPlan,
)
from mkpp.lowering import (
    prepare_unified_jacobian,
    compute_symbolic_lu_decomposition,
    compute_transposed_lu_plan,
)


def _build_chapman_mechanism():
    """Build the 3-species Chapman-like mechanism (O, O3, O1D) with non-trivial coupling."""
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
        name="chapman_transpose_test",
        description="Chapman mechanism for transposed LU solve verification",
        aerosol_representation=AerosolRepresentation.BULK,
        species=[sp_o, sp_o3, sp_o1d],
        phases=[],
        reactions=[r1, r2],
    )


def _evaluate_symbolic_jacobian(jacobian_matrix, species_map, concentrations, jvals):
    """
    Numerically evaluate the symbolic Jacobian matrix at given concentrations.

    Args:
        jacobian_matrix: sympy Matrix (N x N)
        species_map: list of species names in order
        concentrations: dict mapping species name -> numeric value
        jvals: dict mapping J-value symbol names -> numeric value

    Returns:
        numpy array (N x N) with numeric Jacobian values
    """
    N = jacobian_matrix.shape[0]

    # Build substitution dict
    subs = {}
    for name, val in concentrations.items():
        sym = sp.Symbol(f"C_{name}", real=True, nonnegative=True)
        subs[sym] = val

    # Add J-value symbols
    for name, val in jvals.items():
        sym = sp.Symbol(name, real=True, nonnegative=True)
        subs[sym] = val

    # Add temperature/pressure symbols (needed even if Jacobian doesn't depend on them)
    subs[sp.Symbol("Temp", real=True, nonnegative=True)] = 298.0
    subs[sp.Symbol("Press", real=True, nonnegative=True)] = 101325.0

    J_numeric = np.zeros((N, N))
    for i in range(N):
        for j in range(N):
            expr = jacobian_matrix[i, j]
            if expr != 0:
                val = float(expr.subs(subs))
                J_numeric[i, j] = val

    return J_numeric


def _execute_lu_factorization(W, lu_plan):
    """
    Execute the symbolic LU factorization plan on a numeric matrix W.

    Follows the exact same computation order as the symbolic plan
    (Doolittle: L unit lower-triangular, U upper-triangular).

    Returns:
        L, U as numpy arrays
    """
    N = lu_plan.num_species
    L = np.eye(N)
    U = np.zeros((N, N))

    # Build a namespace with all W entries
    ns = {}
    for i in range(N):
        for j in range(N):
            ns[f"W_{i}_{j}"] = W[i, j]

    # Execute LU expressions in order
    for kind, i, j, expr_str in lu_plan.lu_expressions_ordered:
        val = _eval_expr(expr_str, ns)
        if kind == "U":
            U[i, j] = val
            ns[f"U_{i}_{j}"] = val
        else:  # "L"
            L[i, j] = val
            ns[f"L_{i}_{j}"] = val

    return L, U


def _execute_transposed_solve(b, lu_plan, L, U):
    """
    Execute the transposed solve W^T * x = b using the transposed substitution plan.

    Steps:
      1. Forward sub with U^T: solve U^T * y = b
      2. Backward sub with L^T: solve L^T * x = y

    Returns:
        x as numpy array
    """
    N = lu_plan.num_species

    # Build namespace with L and U entries
    ns = {}
    for i in range(N):
        for j in range(N):
            if abs(L[i, j]) > 1e-30 or i == j:
                ns[f"L_{i}_{j}"] = L[i, j]
            if abs(U[i, j]) > 1e-30:
                ns[f"U_{i}_{j}"] = U[i, j]

    # Add b values
    for i in range(N):
        ns[f"b_{i}"] = b[i]

    # Forward substitution (U^T * y = b)
    y = np.zeros(N)
    for idx, expr_str in lu_plan.transpose_forward_sub_steps:
        y[idx] = _eval_expr(expr_str, ns)
        ns[f"y_{idx}"] = y[idx]

    # Backward substitution (L^T * x = y)
    x = np.zeros(N)
    for idx, expr_str in lu_plan.transpose_backward_sub_steps:
        x[idx] = _eval_expr(expr_str, ns)
        ns[f"x_{idx}"] = x[idx]

    return x


def _eval_expr(expr_str, ns):
    """
    Evaluate a symbolic expression string using the given namespace of numeric values.

    Handles expressions like:
      "b_0"
      "b_0 / U_0_0"
      "(b_1 - U_0_1 * y_0) / U_1_1"
      "y_0 - L_1_0 * x_1 - L_2_0 * x_2"
    """
    # Replace variable references with namespace lookups
    # We need to handle operator precedence correctly, so use Python eval
    # but with a safe namespace containing only numeric values
    safe_ns = dict(ns)
    try:
        return float(eval(expr_str, {"__builtins__": {}}, safe_ns))
    except Exception as e:
        raise ValueError(f"Failed to evaluate expression '{expr_str}' with ns keys {list(ns.keys())[:20]}...") from e


class TestTransposedSolveChapmanJacobian:
    """
    Verify transposed symbolic LU solve matches numpy.linalg.solve(W.T, b)
    for the Chapman mechanism's non-symmetric Jacobian.
    """

    def test_chapman_transposed_solve_matches_numpy(self):
        """
        Core test: evaluate Chapman Jacobian at realistic concentrations,
        form W = (1/(gamma*h))*I - J, then verify:
            transposed_symbolic_solve(W, b) == numpy.linalg.solve(W.T, b)
        to machine precision (~1e-12 relative tolerance).
        """
        # 1. Build mechanism and compute symbolic Jacobian
        mech = _build_chapman_mechanism()
        lowering_data = prepare_unified_jacobian(mech)
        J_sym = lowering_data["jacobian_matrix"]
        species_map = lowering_data["species_map"]
        N = len(species_map)

        # 2. Compute symbolic LU plan
        lu_plan = compute_symbolic_lu_decomposition(J_sym, species_map)

        # 3. Compute transposed LU plan
        compute_transposed_lu_plan(lu_plan)
        assert len(lu_plan.transpose_forward_sub_steps) == N
        assert len(lu_plan.transpose_backward_sub_steps) == N

        # 4. Numerically evaluate Jacobian at test concentrations
        # Use realistic atmospheric concentrations (molecules/cm^3)
        concentrations = {
            "O": 1.0e6,
            "O3": 1.0e12,
            "O1D": 1.0e4,
        }
        jvals = {"J_0": 5.0e-5}  # Photolysis rate

        J_numeric = _evaluate_symbolic_jacobian(J_sym, species_map, concentrations, jvals)

        # 5. Form W = (1/(gamma*h))*I - J
        # Use Ros3 gamma = 0.43586652 and a typical timestep
        gamma = 0.43586652150845899
        h = 60.0  # 60 seconds
        inv_gamma_h = 1.0 / (gamma * h)
        W = inv_gamma_h * np.eye(N) - J_numeric

        # Verify W is non-symmetric (this is the point of using Chapman)
        assert not np.allclose(W, W.T, atol=1e-15), (
            "W should be non-symmetric for this test to be meaningful"
        )

        # 6. Execute numeric LU factorization using the symbolic plan
        L, U = _execute_lu_factorization(W, lu_plan)

        # Verify L*U = W (sanity check)
        np.testing.assert_allclose(L @ U, W, atol=1e-12)

        # 7. Generate random RHS vector
        rng = np.random.default_rng(seed=12345)
        b = rng.standard_normal(N)

        # 8. Execute transposed solve using symbolic plan steps
        x_symbolic = _execute_transposed_solve(b, lu_plan, L, U)

        # 9. Compare against numpy reference: solve(W.T, b)
        x_numpy = np.linalg.solve(W.T, b)

        # 10. Assert agreement to machine precision
        np.testing.assert_allclose(
            x_symbolic,
            x_numpy,
            rtol=1e-12,
            atol=1e-15,
            err_msg="Transposed symbolic solve does not match numpy.linalg.solve(W.T, b)",
        )

    def test_chapman_transposed_solve_multiple_rhs(self):
        """
        Verify transposed solve for multiple random RHS vectors to increase
        confidence the plan is correct for arbitrary inputs.
        """
        mech = _build_chapman_mechanism()
        lowering_data = prepare_unified_jacobian(mech)
        J_sym = lowering_data["jacobian_matrix"]
        species_map = lowering_data["species_map"]
        N = len(species_map)

        lu_plan = compute_symbolic_lu_decomposition(J_sym, species_map)
        compute_transposed_lu_plan(lu_plan)

        # Evaluate Jacobian at different concentrations
        concentrations = {
            "O": 5.0e7,
            "O3": 2.0e11,
            "O1D": 3.0e5,
        }
        jvals = {"J_0": 1.0e-4}

        J_numeric = _evaluate_symbolic_jacobian(J_sym, species_map, concentrations, jvals)

        gamma = 0.43586652150845899
        h = 120.0  # 2 minutes
        inv_gamma_h = 1.0 / (gamma * h)
        W = inv_gamma_h * np.eye(N) - J_numeric

        L, U = _execute_lu_factorization(W, lu_plan)
        np.testing.assert_allclose(L @ U, W, atol=1e-12)

        # Test 10 different random RHS vectors
        rng = np.random.default_rng(seed=99)
        for trial in range(10):
            b = rng.standard_normal(N)
            x_symbolic = _execute_transposed_solve(b, lu_plan, L, U)
            x_numpy = np.linalg.solve(W.T, b)

            np.testing.assert_allclose(
                x_symbolic,
                x_numpy,
                rtol=1e-12,
                atol=1e-15,
                err_msg=f"Transposed solve mismatch on trial {trial}",
            )

    def test_chapman_jacobian_is_nonsymmetric(self):
        """
        Confirm the Chapman Jacobian (and thus W) is genuinely non-symmetric,
        making this a meaningful test of the transposed solve path.
        """
        mech = _build_chapman_mechanism()
        lowering_data = prepare_unified_jacobian(mech)
        J_sym = lowering_data["jacobian_matrix"]
        species_map = lowering_data["species_map"]
        N = len(species_map)

        concentrations = {"O": 1.0e6, "O3": 1.0e12, "O1D": 1.0e4}
        jvals = {"J_0": 5.0e-5}

        J_numeric = _evaluate_symbolic_jacobian(J_sym, species_map, concentrations, jvals)

        # The Jacobian of the Chapman mechanism should be non-symmetric
        # because the coupling between species is directional
        assert not np.allclose(J_numeric, J_numeric.T, atol=1e-20), (
            "Chapman Jacobian should be non-symmetric"
        )

    def test_forward_and_transposed_solve_differ_for_nonsymmetric_W(self):
        """
        Verify that forward solve W*x=b and transposed solve W^T*x=b produce
        different results for non-symmetric W, confirming the transposed path
        is distinct from the forward path.
        """
        mech = _build_chapman_mechanism()
        lowering_data = prepare_unified_jacobian(mech)
        J_sym = lowering_data["jacobian_matrix"]
        species_map = lowering_data["species_map"]
        N = len(species_map)

        lu_plan = compute_symbolic_lu_decomposition(J_sym, species_map)
        compute_transposed_lu_plan(lu_plan)

        concentrations = {"O": 1.0e6, "O3": 1.0e12, "O1D": 1.0e4}
        jvals = {"J_0": 5.0e-5}
        J_numeric = _evaluate_symbolic_jacobian(J_sym, species_map, concentrations, jvals)

        gamma = 0.43586652150845899
        h = 60.0
        inv_gamma_h = 1.0 / (gamma * h)
        W = inv_gamma_h * np.eye(N) - J_numeric

        L, U = _execute_lu_factorization(W, lu_plan)

        rng = np.random.default_rng(seed=42)
        b = rng.standard_normal(N)

        # Forward solve: W * x = b
        x_forward = np.linalg.solve(W, b)

        # Transposed solve: W^T * x = b
        x_transposed = _execute_transposed_solve(b, lu_plan, L, U)

        # These should NOT be equal (W is non-symmetric)
        assert not np.allclose(x_forward, x_transposed, atol=1e-10), (
            "Forward and transposed solves should differ for non-symmetric W"
        )

        # But the transposed solve should match numpy's reference
        x_ref = np.linalg.solve(W.T, b)
        np.testing.assert_allclose(x_transposed, x_ref, rtol=1e-12, atol=1e-15)
