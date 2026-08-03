# Research Document: AOT Symbolic LU Decomposition & Kokkos Solver Optimizations

## Overview

This document resolves technical choices and architecture options for refactoring the MKPP Python AOT generator (`src/mkpp/codegen.py`) to emit loop-free, array-free, register-mapped Kokkos C++ ODE solvers.

---

## 1. Build-Time Symbolic Sparse LU Factorization Strategy

### Problem Statement
The current C++ generator emits nested runtime `for` loops for `lu_decompose` ($O(N^3)$) and `lu_solve` ($O(N^2)$) on a thread-local $N \times N$ dense matrix array `W[10000]`. On GPU architectures, this causes massive thread-local memory spilling (80 KB per thread) to VRAM and warp divergence.

### Decision
Implement build-time symbolic sparse LU factorization in Python (`src/mkpp/codegen.py`) using SymPy / symbolic matrix elimination to extract exact scalar expressions for $L$, $U$, and forward/backward substitution steps.

### Rationale
1. Chemical reaction mechanism Jacobians have invariant sparsity patterns known entirely at build time.
2. For $W = \frac{1}{\gamma \Delta t} I - J$, non-zero entries $W_{i,j}$ are known at build time based on mechanism stoichiometry and reaction network topology.
3. Performing symbolic Doolittle/Crout LU decomposition at build time allows the generator to emit branchless scalar code:
   - Doolittle decomposition: $W = L U$ with $L_{i,i} = 1$.
   - Forward substitution: $L y = b \implies y_i = b_i - \sum_{k=0}^{i-1} L_{i,k} y_k$.
   - Backward substitution: $U x = y \implies x_i = \frac{y_i - \sum_{k=i+1}^{N-1} U_{i,k} x_k}{U_{i,i}}$.
4. Emitting these operations as unrolled C++ scalar assignments reduces runtime control flow overhead to zero ($O(1)$) and avoids all nested loops.

### Alternatives Considered
- **Runtime Sparse Solvers (e.g., KokkosBatched::TeamLU)**: Requires maintaining sparse format metadata (CSR/COO) in thread local memory or shared memory, adding indexing overhead and memory lookups for small $N \le 100$ chemical systems.
- **Dense Runtime Pivot Solvers**: Causes $O(N^3)$ cache thrashing and 80 KB local memory spilling per GPU thread.

---

## 2. Architecture-Aware Kokkos View Signatures & Memory Layouts

### Problem Statement
Current solver signatures use raw double pointers (`double* state`, `double* F_block`, `double* Jac`), which breaks Kokkos view striding (e.g., `Kokkos::LayoutLeft` for GPU thread coalescing) and violates memory safety guidelines.

### Decision
Template solver kernels and helper functions on `StateType` or `ViewType`, accepting 1D subview slice references or layout-preserving view abstractions:

```cpp
template <class StateView>
KOKKOS_INLINE_FUNCTION
void integrate(double dt, StateView& state) const { ... }
```

### Rationale
1. Passing `StateView&` allows callers to invoke `integrate` with `Kokkos::subview(states, thread_idx, Kokkos::ALL())` regardless of whether `states` uses `LayoutLeft` (GPU optimized) or `LayoutRight` (CPU host optimized).
2. Supports unmanaged views, host views, and device subviews without hardcoding fixed layout tags in solver function signatures.
3. Completely eliminates raw C pointer signatures (`double*`).

---

## 3. Pure Scalar Register Mapping & Array Elimination

### Problem Statement
Current generated code allocates fixed-size arrays: `double Ynew[100]`, `double F1[100]`, `double K1[100]`, `double K2[100]`, `double Jac[10000]`, `double W[10000]`. Indexing into thread-local arrays prevents the C++ compiler from allocating them in hardware registers, forcing thread local memory stack allocation (spilling to GPU VRAM).

### Decision
Eliminate all array declarations inside `integrate`, `compute_rates`, and `compute_jacobian`. Represent every non-zero matrix element, intermediate rate, and Rosenbrock-2 stage vector as an explicitly named scalar variable:

- Jacobian non-zeros: `double J_0_0 = ...; double J_0_1 = ...;`
- Iteration matrix non-zeros: `double W_0_0 = inv_g_dt - J_0_0; double W_0_1 = -J_0_1;`
- Symbolic LU elements: `double U_0_0 = W_0_0; double L_1_0 = W_1_0 / U_0_0;`
- Intermediate rates: `double F1_0 = ...; double F1_1 = ...;`
- Stage vectors: `double K1_0 = ...; double K1_1 = ...;`
- Fused updates: `double Ynew_0 = state(0) + ros_A0 * K1_0;`

### Rationale
Modern GPU architectures (NVIDIA Ampere/Hopper, AMD CDNA) provide 128–255 32-bit registers per thread (64–127 64-bit double registers). Replacing 10,000-element arrays with ~100–300 scalar double variables allows the NVCC / Clang compiler to map all solver variables directly to hardware registers, eliminating 100% of thread local memory spilling.

---

## 4. Loop Fusion for Stage Updates

### Problem Statement
The current Rosenbrock-2 solver iterates through species in 6 consecutive `for` loops during a single timestep, re-reading state memory repeatedly.

### Decision
Fuse ROS-2 stage evaluations ($K_1, K_2$) and state updates ($Y_{new}$) per species in unrolled scalar statements:

1. Evaluate $F_1$ scalars from `state(i)`.
2. Solve $K_1$ scalars via unrolled backward/forward substitution.
3. Compute $Y_{new, i} = \text{state}(i) + a_{21} K_{1, i}$ in scalar variables.
4. Evaluate $F_2$ scalars from $Y_{new, i}$.
5. Solve $K_2$ scalars via unrolled substitution with right-hand side $F_{2, i} + \frac{c_{21}}{\Delta t} K_{1, i}$.
6. Update final state: $\text{state}(i) += m_1 K_{1, i} + m_2 K_{2, i}$.

### Rationale
Fusing state updates reduces memory read/write passes over species vectors, maximizes register lifetime reuse, and removes all loop iteration boundaries.
