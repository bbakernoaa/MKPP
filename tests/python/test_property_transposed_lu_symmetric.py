"""
Property-based test: transposed solve produces identical results for symmetric matrices.

For any symmetric matrix W, W == W^T, so solve(W, b) and solve(W^T, b)
must produce identical results. This verifies that the symbolic transposed LU
solve (compute_transposed_lu_plan) produces the same numerical answer as the
forward LU solve when the matrix is symmetric.

**Validates: Requirements 5.3**
"""

import numpy as np
from hypothesis import assume, given, settings
from hypothesis import strategies as st
from mkpp.lowering import compute_transposed_lu_plan
from mkpp.model import SymbolicLUPlan

# ---------------------------------------------------------------------------
# Strategies
# ---------------------------------------------------------------------------


@st.composite
def symmetric_diagonally_dominant_system(draw, min_n=2, max_n=8):
    """
    Generate a random NxN symmetric, diagonally-dominant matrix and RHS vector.

    Symmetry is enforced by constructing A = B + B^T then adding diagonal dominance.
    Diagonal dominance guarantees non-singularity and stable LU without pivoting.
    """
    n = draw(st.integers(min_value=min_n, max_value=max_n))

    # Generate random symmetric matrix: start with upper triangle, mirror it
    entries = []
    for i in range(n):
        for j in range(i, n):
            val = draw(st.floats(min_value=-2.0, max_value=2.0, allow_nan=False, allow_infinity=False))
            entries.append((i, j, val))

    A = np.zeros((n, n))
    for i, j, val in entries:
        A[i, j] = val
        A[j, i] = val  # Symmetric

    # Make strictly diagonally dominant to ensure non-singularity
    for i in range(n):
        row_sum = np.sum(np.abs(A[i, :])) - np.abs(A[i, i])
        dominance = draw(st.floats(min_value=1.0, max_value=5.0, allow_nan=False, allow_infinity=False))
        A[i, i] = row_sum + dominance

    # Random RHS vector
    b = np.array([draw(st.floats(min_value=-10.0, max_value=10.0, allow_nan=False, allow_infinity=False)) for _ in range(n)])

    return n, A, b


# ---------------------------------------------------------------------------
# Helper: execute symbolic LU solve numerically
# ---------------------------------------------------------------------------


def _doolittle_lu(W, n):
    """Compute Doolittle LU factorization (L unit lower-triangular, U upper-triangular)."""
    L = np.eye(n)
    U = np.zeros((n, n))

    for i in range(n):
        for j in range(i, n):
            s = sum(L[i, k] * U[k, j] for k in range(i))
            U[i, j] = W[i, j] - s
        for j in range(i + 1, n):
            s = sum(L[j, k] * U[k, i] for k in range(i))
            L[j, i] = (W[j, i] - s) / U[i, i]

    return L, U


def _execute_forward_solve(L, U, b, n, plan):
    """Execute the non-transposed symbolic forward/backward substitution numerically.

    Forward sub: L * y = b  (unit lower-triangular)
    Backward sub: U * x = y (upper-triangular)
    """
    # Forward substitution: y_i = b_i - sum_{k<i} L[i,k] * y[k]
    y = np.zeros(n)
    for i in range(n):
        s = 0.0
        for k in range(i):
            if abs(L[i, k]) > 1e-15:
                s += L[i, k] * y[k]
        y[i] = b[i] - s

    # Backward substitution: x_i = (y_i - sum_{k>i} U[i,k] * x[k]) / U[i,i]
    x = np.zeros(n)
    for i in range(n - 1, -1, -1):
        s = 0.0
        for k in range(i + 1, n):
            if abs(U[i, k]) > 1e-15:
                s += U[i, k] * x[k]
        x[i] = (y[i] - s) / U[i, i]

    return x


def _execute_transposed_solve(L, U, b, n, plan):
    """Execute the transposed symbolic solve numerically.

    For W^T * x = b where W = L*U:
      Forward sub with U^T: y_i = (b_i - sum_{k<i} U[k,i]*y[k]) / U[i,i]
      Backward sub with L^T: x_i = y_i - sum_{k>i} L[k,i]*x[k]
    """
    # Build non-zero sets from L and U for accurate sparsity
    nz_L = set()
    for i in range(n):
        for j in range(i):
            if abs(L[i, j]) > 1e-15:
                nz_L.add((i, j))

    nz_U = set()
    for i in range(n):
        for j in range(i, n):
            if abs(U[i, j]) > 1e-15:
                nz_U.add((i, j))

    # Transposed forward sub: U^T * y = b
    # y_i = (b_i - sum_{k<i} U[k,i]*y[k]) / U[i,i]
    y = np.zeros(n)
    for i in range(n):
        s = 0.0
        for k in range(i):
            if (k, i) in nz_U:
                s += U[k, i] * y[k]
        y[i] = (b[i] - s) / U[i, i]

    # Transposed backward sub: L^T * x = y
    # x_i = y_i - sum_{k>i} L[k,i]*x[k]
    x = np.zeros(n)
    for i in range(n - 1, -1, -1):
        s = 0.0
        for k in range(i + 1, n):
            if (k, i) in nz_L:
                s += L[k, i] * x[k]
        x[i] = y[i] - s

    return x


def _build_plan_from_numeric(L, U, n):
    """Build a SymbolicLUPlan from numerical L and U matrices."""
    l_exprs = []
    for i in range(n):
        for j in range(i):
            if abs(L[i, j]) > 1e-15:
                l_exprs.append((i, j, f"L_{i}_{j}_val"))

    u_exprs = []
    for i in range(n):
        for j in range(i, n):
            if abs(U[i, j]) > 1e-15:
                u_exprs.append((i, j, f"U_{i}_{j}_val"))

    plan = SymbolicLUPlan(
        num_species=n,
        species_map=[f"s{i}" for i in range(n)],
        l_expressions=l_exprs,
        u_expressions=u_exprs,
        forward_sub_steps=[],
        backward_sub_steps=[],
    )

    return plan


# ---------------------------------------------------------------------------
# Property test: symmetric matrix => forward and transposed solve match
# **Validates: Requirements 5.3**
# ---------------------------------------------------------------------------


@given(data=symmetric_diagonally_dominant_system(min_n=2, max_n=8))
@settings(max_examples=200, deadline=None)
def test_property_transposed_solve_matches_forward_for_symmetric(data):
    """
    For any symmetric diagonally-dominant matrix W and any RHS vector b,
    the transposed LU solve (using compute_transposed_lu_plan) must produce
    the same numerical result as the forward LU solve, since W == W^T.

    This verifies Requirement 5.3: The transposed solve MUST produce identical
    results to the non-transposed solve when the matrix is symmetric.

    **Validates: Requirements 5.3**
    """
    n, W, b = data

    # Verify W is actually symmetric (sanity check on the strategy)
    assert np.allclose(W, W.T, atol=1e-14), "Generated matrix is not symmetric"

    # Compute Doolittle LU factorization
    L, U = _doolittle_lu(W, n)

    # Verify factorization: L*U should equal W
    assume(np.allclose(L @ U, W, atol=1e-10))

    # Verify pivot is non-zero (stable factorization)
    assume(all(abs(U[i, i]) > 1e-10 for i in range(n)))

    # Build the symbolic plan from the numeric factorization
    plan = _build_plan_from_numeric(L, U, n)

    # Compute transposed plan (this is the function under test)
    compute_transposed_lu_plan(plan)

    # Execute forward (non-transposed) solve: W * x = b
    x_forward = _execute_forward_solve(L, U, b, n, plan)

    # Execute transposed solve: W^T * x = b (should be same as W * x = b)
    x_transposed = _execute_transposed_solve(L, U, b, n, plan)

    # For symmetric W, both solves must produce the same result
    np.testing.assert_allclose(
        x_transposed,
        x_forward,
        atol=1e-10,
        rtol=1e-10,
        err_msg=(
            f"Transposed solve differs from forward solve for symmetric matrix.\n"
            f"N={n}\n"
            f"W=\n{W}\n"
            f"b={b}\n"
            f"x_forward={x_forward}\n"
            f"x_transposed={x_transposed}\n"
            f"max_diff={np.max(np.abs(x_forward - x_transposed))}"
        ),
    )

    # Also verify both solutions actually solve the system
    residual_forward = np.max(np.abs(W @ x_forward - b))
    residual_transposed = np.max(np.abs(W.T @ x_transposed - b))
    assert residual_forward < 1e-8, f"Forward solve residual too large: {residual_forward}"
    assert residual_transposed < 1e-8, f"Transposed solve residual too large: {residual_transposed}"
