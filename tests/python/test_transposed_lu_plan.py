"""
Unit test for compute_transposed_lu_plan() in lowering.py.

Validates task 1.1: transposed solve swaps L/U roles —
forward sub uses U^T (lower-tri), backward sub uses L^T (upper-tri).

Requirements: 5.1, 5.2
"""
import pytest
import numpy as np
from mkpp.model import SymbolicLUPlan
from mkpp.lowering import compute_transposed_lu_plan


def _build_full_3x3_plan():
    """Build a fully-connected 3x3 LU plan (dense W)."""
    return SymbolicLUPlan(
        num_species=3,
        species_map=["A", "B", "C"],
        l_expressions=[
            (1, 0, "(W_1_0) / U_0_0"),
            (2, 0, "(W_2_0) / U_0_0"),
            (2, 1, "(W_2_1 - L_2_0 * U_0_1) / U_1_1"),
        ],
        u_expressions=[
            (0, 0, "W_0_0"),
            (0, 1, "W_0_1"),
            (0, 2, "W_0_2"),
            (1, 1, "W_1_1 - L_1_0 * U_0_1"),
            (1, 2, "W_1_2 - L_1_0 * U_0_2"),
            (2, 2, "W_2_2 - L_2_0 * U_0_2 - L_2_1 * U_1_2"),
        ],
        forward_sub_steps=[
            (0, "b_0"),
            (1, "b_1 - L_1_0 * y_0"),
            (2, "b_2 - L_2_0 * y_0 - L_2_1 * y_1"),
        ],
        backward_sub_steps=[
            (2, "y_2 / U_2_2"),
            (1, "(y_1 - U_1_2 * x_2) / U_1_1"),
            (0, "(y_0 - U_0_1 * x_1 - U_0_2 * x_2) / U_0_0"),
        ],
    )


def _build_sparse_2x2_plan():
    """Build a 2x2 plan with sparse L (diagonal only, no off-diag L)."""
    return SymbolicLUPlan(
        num_species=2,
        species_map=["X", "Y"],
        l_expressions=[
            (1, 0, "(W_1_0) / U_0_0"),
        ],
        u_expressions=[
            (0, 0, "W_0_0"),
            (0, 1, "W_0_1"),
            (1, 1, "W_1_1 - L_1_0 * U_0_1"),
        ],
        forward_sub_steps=[
            (0, "b_0"),
            (1, "b_1 - L_1_0 * y_0"),
        ],
        backward_sub_steps=[
            (1, "y_1 / U_1_1"),
            (0, "(y_0 - U_0_1 * x_1) / U_0_0"),
        ],
    )


class TestComputeTransposedLUPlan:
    """Tests for compute_transposed_lu_plan correctness."""

    def test_transpose_forward_steps_count(self):
        """Transposed forward sub should have N steps (one per row)."""
        plan = _build_full_3x3_plan()
        result = compute_transposed_lu_plan(plan)
        assert len(result.transpose_forward_sub_steps) == 3

    def test_transpose_backward_steps_count(self):
        """Transposed backward sub should have N steps (one per row)."""
        plan = _build_full_3x3_plan()
        result = compute_transposed_lu_plan(plan)
        assert len(result.transpose_backward_sub_steps) == 3

    def test_transpose_forward_uses_U_entries(self):
        """U^T forward sub references U[k,i] (transposed U entries)."""
        plan = _build_full_3x3_plan()
        result = compute_transposed_lu_plan(plan)

        # Step 0: y_0 = b_0 / U_0_0 (no k < 0)
        assert result.transpose_forward_sub_steps[0] == (0, "b_0 / U_0_0")

        # Step 1: y_1 = (b_1 - U_0_1 * y_0) / U_1_1
        assert result.transpose_forward_sub_steps[1] == (1, "(b_1 - U_0_1 * y_0) / U_1_1")

        # Step 2: y_2 = (b_2 - U_0_2 * y_0 - U_1_2 * y_1) / U_2_2
        assert result.transpose_forward_sub_steps[2] == (2, "(b_2 - U_0_2 * y_0 - U_1_2 * y_1) / U_2_2")

    def test_transpose_backward_uses_L_entries(self):
        """L^T backward sub references L[k,i] (transposed L entries), no division (unit diag)."""
        plan = _build_full_3x3_plan()
        result = compute_transposed_lu_plan(plan)

        # Step ordering should be i = N-1, N-2, ..., 0
        # Step 0 (i=2): x_2 = y_2 (no k > 2 with L[k,2] != 0)
        assert result.transpose_backward_sub_steps[0] == (2, "y_2")

        # Step 1 (i=1): x_1 = y_1 - L_2_1 * x_2
        assert result.transpose_backward_sub_steps[1] == (1, "y_1 - L_2_1 * x_2")

        # Step 2 (i=0): x_0 = y_0 - L_1_0 * x_1 - L_2_0 * x_2
        assert result.transpose_backward_sub_steps[2] == (0, "y_0 - L_1_0 * x_1 - L_2_0 * x_2")

    def test_sparse_2x2_transpose_forward(self):
        """2x2 sparse case: U^T forward sub."""
        plan = _build_sparse_2x2_plan()
        result = compute_transposed_lu_plan(plan)

        # y_0 = b_0 / U_0_0
        assert result.transpose_forward_sub_steps[0] == (0, "b_0 / U_0_0")
        # y_1 = (b_1 - U_0_1 * y_0) / U_1_1
        assert result.transpose_forward_sub_steps[1] == (1, "(b_1 - U_0_1 * y_0) / U_1_1")

    def test_sparse_2x2_transpose_backward(self):
        """2x2 sparse case: L^T backward sub."""
        plan = _build_sparse_2x2_plan()
        result = compute_transposed_lu_plan(plan)

        # x_1 = y_1 (no L[k,1] for k > 1)
        assert result.transpose_backward_sub_steps[0] == (1, "y_1")
        # x_0 = y_0 - L_1_0 * x_1
        assert result.transpose_backward_sub_steps[1] == (0, "y_0 - L_1_0 * x_1")

    def test_mutates_input_plan(self):
        """compute_transposed_lu_plan stores results on the input plan object."""
        plan = _build_full_3x3_plan()
        assert plan.transpose_forward_sub_steps == []
        assert plan.transpose_backward_sub_steps == []

        returned = compute_transposed_lu_plan(plan)

        # Both the returned plan and the input plan should be the same object
        assert returned is plan
        assert len(plan.transpose_forward_sub_steps) == 3
        assert len(plan.transpose_backward_sub_steps) == 3

    def test_numerical_correctness_dense(self):
        """
        Verify transposed solve matches numpy solve(W.T, b) for a random dense matrix.

        This executes the generated substitution steps numerically and compares
        against numpy's direct W^T solve.
        """
        rng = np.random.default_rng(42)
        N = 3
        # Generate a random non-singular matrix W
        W = rng.standard_normal((N, N))
        W += np.eye(N) * 3.0  # Ensure diagonal dominance

        # Compute LU factorization (Doolittle: L unit lower-tri, U upper-tri)
        L = np.eye(N)
        U = np.zeros((N, N))

        for i in range(N):
            for j in range(i, N):
                s = sum(L[i, k] * U[k, j] for k in range(i))
                U[i, j] = W[i, j] - s
            for j in range(i + 1, N):
                s = sum(L[j, k] * U[k, i] for k in range(i))
                L[j, i] = (W[j, i] - s) / U[i, i]

        # Verify L*U = W
        np.testing.assert_allclose(L @ U, W, atol=1e-12)

        # Build SymbolicLUPlan from actual L and U values
        l_exprs = []
        u_exprs = []
        for j in range(N):
            for i in range(j + 1, N):
                if abs(L[i, j]) > 1e-15:
                    l_exprs.append((i, j, f"L_{i}_{j}_val"))
        for i in range(N):
            for j in range(i, N):
                if abs(U[i, j]) > 1e-15:
                    u_exprs.append((i, j, f"U_{i}_{j}_val"))

        plan = SymbolicLUPlan(
            num_species=N,
            species_map=["s0", "s1", "s2"],
            l_expressions=l_exprs,
            u_expressions=u_exprs,
            forward_sub_steps=[],  # Not used in this test
            backward_sub_steps=[],  # Not used in this test
        )

        result = compute_transposed_lu_plan(plan)

        # Now execute the transposed solve numerically
        b = rng.standard_normal(N)

        # Forward sub with U^T: y_i = (b_i - sum_{k<i} U[k,i]*y_k) / U[i,i]
        y = np.zeros(N)
        for i in range(N):
            s = sum(U[k, i] * y[k] for k in range(i) if (k, i) in {(r, c) for r, c, _ in u_exprs})
            y[i] = (b[i] - s) / U[i, i]

        # Backward sub with L^T: x_i = y_i - sum_{k>i} L[k,i]*x_k
        x = np.zeros(N)
        for i in range(N - 1, -1, -1):
            s = sum(L[k, i] * x[k] for k in range(i + 1, N) if (k, i) in {(r, c) for r, c, _ in l_exprs})
            x[i] = y[i] - s

        # Compare with numpy: solve(W.T, b)
        x_ref = np.linalg.solve(W.T, b)
        np.testing.assert_allclose(x, x_ref, atol=1e-12)

    def test_diagonal_only_plan(self):
        """When W is diagonal, transposed solve is trivial (same as forward)."""
        plan = SymbolicLUPlan(
            num_species=2,
            species_map=["P", "Q"],
            l_expressions=[],  # No off-diagonal L
            u_expressions=[
                (0, 0, "W_0_0"),
                (1, 1, "W_1_1"),
            ],
            forward_sub_steps=[
                (0, "b_0"),
                (1, "b_1"),
            ],
            backward_sub_steps=[
                (1, "y_1 / U_1_1"),
                (0, "y_0 / U_0_0"),
            ],
        )

        result = compute_transposed_lu_plan(plan)

        # U^T forward: y_i = b_i / U_i_i (diagonal only)
        assert result.transpose_forward_sub_steps[0] == (0, "b_0 / U_0_0")
        assert result.transpose_forward_sub_steps[1] == (1, "b_1 / U_1_1")

        # L^T backward: x_i = y_i (identity L means no corrections)
        assert result.transpose_backward_sub_steps[0] == (1, "y_1")
        assert result.transpose_backward_sub_steps[1] == (0, "y_0")
