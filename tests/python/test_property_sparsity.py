"""
Property-based tests for sparsity optimization (Component 4).

Validates:
- Property 10: Fill-in prediction soundness (Requirements 4.1, 4.2)
- Property 11: RCM bandwidth reduction (Requirements 4.3)
- Property 12: Permuted solve equivalence (Requirements 4.4, 4.5, 4.6)
- Property 13: Sparsity optimizer determinism (Requirements 4.7)
"""
import numpy as np
from hypothesis import given, settings, assume
from hypothesis import strategies as st

from mkpp.lowering import SparsityOptimizer
from mkpp.model import SparsityAnalysis


# ---------------------------------------------------------------------------
# Strategies
# ---------------------------------------------------------------------------

@st.composite
def random_sparse_structure(draw, min_n=3, max_n=15, min_density=0.1, max_density=0.5):
    """
    Generate a random NxN sparse structure set.
    Always includes diagonal entries. Off-diagonal entries are sampled
    with a density between min_density and max_density.
    """
    n = draw(st.integers(min_value=min_n, max_value=max_n))
    density = draw(st.floats(min_value=min_density, max_value=max_density))

    structure = set()
    # Diagonal is always present
    for i in range(n):
        structure.add((i, i))

    # Off-diagonal entries with the given density
    for i in range(n):
        for j in range(n):
            if i != j:
                if draw(st.floats(min_value=0.0, max_value=1.0)) < density:
                    structure.add((i, j))

    return n, structure


@st.composite
def random_symmetric_sparse_structure(draw, min_n=4, max_n=20, min_density=0.1, max_density=0.5):
    """
    Generate a random symmetric sparse structure graph.
    Ensures (i,j) in structure iff (j,i) in structure, plus diagonal.
    """
    n = draw(st.integers(min_value=min_n, max_value=max_n))
    density = draw(st.floats(min_value=min_density, max_value=max_density))

    structure = set()
    # Diagonal always present
    for i in range(n):
        structure.add((i, i))

    # Symmetric off-diagonal
    for i in range(n):
        for j in range(i + 1, n):
            if draw(st.floats(min_value=0.0, max_value=1.0)) < density:
                structure.add((i, j))
                structure.add((j, i))

    return n, structure


@st.composite
def random_diagonally_dominant_system(draw, min_n=2, max_n=8):
    """
    Generate a random NxN diagonally-dominant matrix and a random RHS vector.
    Diagonal dominance guarantees non-singularity (and no pivoting needed for LU).
    """
    n = draw(st.integers(min_value=min_n, max_value=max_n))

    # Generate random off-diagonal entries
    A = np.zeros((n, n))
    for i in range(n):
        for j in range(n):
            if i != j:
                A[i, j] = draw(st.floats(min_value=-1.0, max_value=1.0))

    # Make strictly diagonally dominant
    for i in range(n):
        row_sum = np.sum(np.abs(A[i, :])) - np.abs(A[i, i])
        A[i, i] = row_sum + draw(st.floats(min_value=1.0, max_value=5.0))

    # Random RHS
    b = np.array([
        draw(st.floats(min_value=-10.0, max_value=10.0))
        for _ in range(n)
    ])

    return n, A, b


# ---------------------------------------------------------------------------
# Property 10: Fill-in prediction soundness
# **Validates: Requirements 4.1, 4.2**
# ---------------------------------------------------------------------------

@given(data=random_sparse_structure(min_n=3, max_n=15, min_density=0.1, max_density=0.5))
@settings(max_examples=100)
def test_property_10_fill_in_prediction_soundness(data):
    """
    For any NxN sparse structure, the fill-in positions predicted by
    SparsityOptimizer.predict_fill_in() are a superset of the positions
    that become non-zero during actual numeric Doolittle LU factorization.

    **Validates: Requirements 4.1, 4.2**
    """
    n, structure = data

    # Predict fill-in symbolically
    optimizer = SparsityOptimizer(structure, n)
    predicted_fill = optimizer.predict_fill_in()
    predicted_nonzero = structure | predicted_fill | {(i, i) for i in range(n)}

    # Create a random numeric matrix matching the structure pattern
    rng = np.random.default_rng(42)
    A = np.zeros((n, n))
    for i, j in structure:
        # Use non-zero values so that structural non-zeros are truly non-zero numerically
        val = rng.uniform(0.5, 2.0) * rng.choice([-1, 1])
        A[i, j] = val

    # Make diagonal dominant to avoid zero pivots
    for i in range(n):
        row_sum = np.sum(np.abs(A[i, :])) - np.abs(A[i, i])
        A[i, i] = row_sum + 1.0

    # Perform numeric Doolittle LU (no pivoting)
    L = np.eye(n)
    U = np.zeros((n, n))

    W = A.copy()  # Working matrix

    for i in range(n):
        # U row i
        for j in range(i, n):
            s = W[i, j]
            for k in range(i):
                s -= L[i, k] * U[k, j]
            U[i, j] = s

        # L column i (below diagonal)
        if abs(U[i, i]) < 1e-15:
            # Skip this case - near-singular pivot
            return
        for j in range(i + 1, n):
            s = W[j, i]
            for k in range(i):
                s -= L[j, k] * U[k, i]
            L[j, i] = s / U[i, i]

    # Find actual numeric fill: positions in L and U that are non-zero
    actual_nonzero = set()
    threshold = 1e-12

    for i in range(n):
        for j in range(n):
            if i > j and abs(L[i, j]) > threshold:
                actual_nonzero.add((i, j))
            elif i <= j and abs(U[i, j]) > threshold:
                actual_nonzero.add((i, j))

    # Verify predicted fill-in is a superset of actual fill-in
    # (predicted_nonzero should contain all positions in actual_nonzero)
    missed = actual_nonzero - predicted_nonzero
    assert missed == set(), (
        f"Fill-in prediction missed positions: {missed}. "
        f"N={n}, original structure size={len(structure)}, "
        f"predicted fill={len(predicted_fill)}"
    )


# ---------------------------------------------------------------------------
# Property 11: RCM bandwidth reduction
# **Validates: Requirements 4.3**
# ---------------------------------------------------------------------------

def compute_bandwidth(structure, n):
    """Compute bandwidth = max |i - j| for all (i,j) in structure."""
    if not structure:
        return 0
    return max(abs(i - j) for i, j in structure)


@given(data=random_symmetric_sparse_structure(min_n=4, max_n=20, min_density=0.1, max_density=0.5))
@settings(max_examples=100)
def test_property_11_rcm_bandwidth_reduction(data):
    """
    For any symmetric sparse structure graph, the bandwidth after RCM
    reordering is less than or equal to the original bandwidth.

    Bandwidth = max over all (i,j) in structure of |i-j|.

    **Validates: Requirements 4.3**
    """
    n, structure = data

    # Compute original bandwidth
    original_bw = compute_bandwidth(structure, n)

    # Apply RCM reordering
    optimizer = SparsityOptimizer(structure, n)
    perm = optimizer.compute_rcm_ordering()

    # Verify permutation is valid
    assert sorted(perm) == list(range(n)), (
        f"RCM permutation is not a valid permutation of 0..{n-1}: {perm}"
    )

    # Build inverse permutation: inv_perm[old_idx] = new_idx
    inv_perm = [0] * n
    for new_idx, old_idx in enumerate(perm):
        inv_perm[old_idx] = new_idx

    # Compute bandwidth of permuted structure
    permuted_structure = set()
    for i, j in structure:
        permuted_structure.add((inv_perm[i], inv_perm[j]))

    rcm_bw = compute_bandwidth(permuted_structure, n)

    assert rcm_bw <= original_bw, (
        f"RCM bandwidth ({rcm_bw}) exceeds original bandwidth ({original_bw}). "
        f"N={n}, structure_size={len(structure)}, perm={perm}"
    )


# ---------------------------------------------------------------------------
# Property 12: Permuted solve equivalence
# **Validates: Requirements 4.4, 4.5, 4.6**
# ---------------------------------------------------------------------------

@given(data=random_diagonally_dominant_system(min_n=2, max_n=8))
@settings(max_examples=100)
def test_property_12_permuted_solve_equivalence(data):
    """
    For any NxN non-singular diagonally-dominant matrix A and RHS b,
    solving the permuted system (P A P^T)(P x) = P b and then un-permuting
    yields the same solution as solving A x = b directly.

    **Validates: Requirements 4.4, 4.5, 4.6**
    """
    n, A, b = data

    # Solve original system
    try:
        x_original = np.linalg.solve(A, b)
    except np.linalg.LinAlgError:
        # Skip singular cases (shouldn't happen with diagonal dominance)
        return

    # Generate a random permutation using the SparsityOptimizer's RCM
    # (or a deterministic permutation based on structure)
    structure = set()
    for i in range(n):
        for j in range(n):
            if abs(A[i, j]) > 1e-15:
                structure.add((i, j))

    optimizer = SparsityOptimizer(structure, n)
    perm = optimizer.compute_rcm_ordering()

    # Build permutation matrix P
    P = np.zeros((n, n))
    for new_idx, old_idx in enumerate(perm):
        P[new_idx, old_idx] = 1.0

    # Permuted system: (P A P^T) (P x) = P b
    A_perm = P @ A @ P.T
    b_perm = P @ b

    # Solve permuted system
    try:
        px = np.linalg.solve(A_perm, b_perm)
    except np.linalg.LinAlgError:
        return

    # Un-permute solution: x_recovered = P^T (P x)
    x_recovered = P.T @ px

    # Verify solutions match within floating-point tolerance
    tol = 1e-10 * max(np.max(np.abs(x_original)), 1.0)
    assert np.allclose(x_original, x_recovered, atol=tol, rtol=1e-10), (
        f"Solutions don't match after permutation.\n"
        f"Original: {x_original}\n"
        f"Recovered: {x_recovered}\n"
        f"Max diff: {np.max(np.abs(x_original - x_recovered))}\n"
        f"Permutation: {perm}\n"
        f"N={n}"
    )


# ---------------------------------------------------------------------------
# Property 13: Sparsity optimizer determinism
# **Validates: Requirements 4.7**
# ---------------------------------------------------------------------------

@given(data=random_sparse_structure(min_n=3, max_n=10, min_density=0.1, max_density=0.5))
@settings(max_examples=100)
def test_property_13_sparsity_optimizer_determinism(data):
    """
    For any Jacobian structure set S and matrix size N, invoking
    SparsityOptimizer(S, N).analyze() twice produces identical SparsityAnalysis
    results (same fill, same permutation, same blocks).

    **Validates: Requirements 4.7**
    """
    n, structure = data

    # Run analyze() twice on the same input
    optimizer1 = SparsityOptimizer(structure, n)
    result1 = optimizer1.analyze()

    optimizer2 = SparsityOptimizer(structure, n)
    result2 = optimizer2.analyze()

    # Verify byte-identical results
    assert result1.original_nnz == result2.original_nnz, (
        f"original_nnz differs: {result1.original_nnz} vs {result2.original_nnz}"
    )
    assert result1.fill_in_positions == result2.fill_in_positions, (
        f"fill_in_positions differs"
    )
    assert result1.total_nnz_after_fill == result2.total_nnz_after_fill, (
        f"total_nnz_after_fill differs: {result1.total_nnz_after_fill} vs {result2.total_nnz_after_fill}"
    )
    assert result1.permutation == result2.permutation, (
        f"permutation differs: {result1.permutation} vs {result2.permutation}"
    )
    assert result1.inverse_permutation == result2.inverse_permutation, (
        f"inverse_permutation differs"
    )
    assert result1.blocks == result2.blocks, (
        f"blocks differs: {result1.blocks} vs {result2.blocks}"
    )
    assert result1.is_block_diagonal == result2.is_block_diagonal, (
        f"is_block_diagonal differs: {result1.is_block_diagonal} vs {result2.is_block_diagonal}"
    )
