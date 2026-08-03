# Feature Specification: Ahead-Of-Time (AOT) Symbolic LU Kokkos ODE Solver Generator

**Feature Branch**: `013-aot-symbolic-lu-solver`

**Created**: 2026-08-02

**Status**: Draft

**Input**: User description: "**System Role:** You are an Exascale HPC Architecture Expert and Lead Compiler Engineer working on the Futuristic Kinetic PreProcessor (FKPP). Your goal is to optimize an Ahead-Of-Time (AOT) Python code generator that emits C++ Kokkos ODE solvers for atmospheric chemistry. **Context:** We currently have a Python generator emitting a Kokkos-based Rosenbrock-2 (ROS-2) solver (e.g., `saprc99.hpp`). While the Jacobian generation is perfectly unrolled into flat scalar math, the integration loop contains fatal architectural flaws for GPU/CPU performance portability: 1. It allocates massive dense arrays (`Jac[10000]`, `W[10000]`) inside the thread, causing an 80 KB "thread bomb" that triggers Local Memory spilling and destroys register limits. 2. It uses triple-nested dense `for` loops for `lu_decompose` and `lu_solve`, causing warp divergence and $O(N^3)$ CPU cache thrashing. 3. It uses raw `double* state` pointers, which breaks `Kokkos::LayoutLeft` memory striding. 4. It iterates over multiple consecutive `for` loops to update the ROS-2 stages, wasting memory bandwidth. **Your Task:** Rewrite the Python AOT generator logic and provide the target C++ template structure to fix all of these issues. **Strict Architectural Directives:** 1. Architecture-Aware Memory Layouts & Views 2. AOT Symbolic LU Factorization (Zero Loops) 3. Pure Scalar Register Mapping (No Arrays) 4. Loop Fusion for Stage Updates"

## User Scenarios & Testing *(mandatory)*

### User Story 1 - Build-Time Symbolic LU Factorization & Flat Scalar Inversion (Priority: P1)

Atmospheric chemistry modelers and HPC performance engineers require generated C++ ODE solvers that execute matrix inversions without runtime loops or dynamic allocations, so that GPU threads do not spill local memory to VRAM or suffer warp divergence.

**Why this priority**: Eliminating thread-local dense arrays (`Jac[10000]`, `W[10000]`) and triple-nested loops in `lu_decompose` / `lu_solve` removes the primary GPU performance bottleneck (register pressure and memory spilling).

**Independent Test**: Generate C++ solver code for a sample chemistry mechanism (e.g., SAPRC99), compile for GPU, and verify via binary analysis/profiling that thread local memory usage is 0 bytes and no loop structures exist in matrix decomposition/solving.

**Acceptance Scenarios**:

1. **Given** a chemical reaction mechanism, **When** the AOT generator processes the mechanism, **Then** it performs symbolic sparse LU decomposition during build time and emits forward/backward substitution as a branchless sequence of scalar assignments.
2. **Given** generated C++ solver headers, **When** compiled for execution on GPU architectures, **Then** zero thread-local array allocations (`double Jac[...]`, `double W[...]`) are emitted inside execution functors.

---

### User Story 2 - Architecture-Aware View Interfaces & Layout Striding (Priority: P2)

Model engine developers need solver interfaces that accept flexible multidimensional view types and execution layouts without using raw pointer arrays, ensuring seamless memory alignment across CPU and GPU backends.

**Why this priority**: Raw pointers break memory striding abstractions (e.g., `Kokkos::LayoutLeft` for GPU coalesced memory access) and violate memory safety standards.

**Independent Test**: Pass 1D subviews and strided multi-dimensional execution space views to generated solver integration functions and verify correct compile-time binding and numerical equivalence against reference state vectors.

**Acceptance Scenarios**:

1. **Given** state vectors stored in multidimensional grid views, **When** invoking generated solver functions (`integrate`, `compute_rates`, `compute_jacobian`), **Then** functions accept 1D Kokkos subviews or layout-preserving strided view parameters rather than raw C pointers.
2. **Given** different execution space memory layouts, **When** solver routines are called, **Then** data layout types adapt to execution space array layouts without hardcoding rigid layout requirements.

---

### User Story 3 - Pure Scalar Register Allocation & Stage Loop Fusion (Priority: P3)

Compiler and runtime optimization engineers require intermediate solver stage updates ($K_1$, $K_2$, $Y_{new}$) and Jacobian entries to be represented as scalar variables and fused into unified expressions, maximizing register reuse and reducing memory bandwidth.

**Why this priority**: Separate loop passes for intermediate Rosenbrock-2 stage updates re-read state vectors unnecessarily, wasting memory bandwidth and hardware registers.

**Independent Test**: Inspect generated ROS-2 integration kernels and confirm that intermediate stage updates and state combinations are fully unrolled and fused per species without intermediate array allocations or loop boundaries.

**Acceptance Scenarios**:

1. **Given** intermediate stage equations for ODE integration, **When** code is generated, **Then** every non-zero matrix element and stage value is assigned to an explicitly named scalar variable (e.g., `J_1_2`, `K1_5`).
2. **Given** Rosenbrock-2 stage updates, **When** updating state solutions, **Then** intermediate stage calculations and final state updating expressions are fused per species into a single unrolled pass.

---

### Edge Cases

- How does the system handle zero pivot or near-zero pivot conditions during build-time symbolic LU factorization?
- What happens when a chemical mechanism has an empty or decoupled diagonal entry in its Jacobian matrix?
- How does the generated code behave when passed subviews with non-contiguous strides or offset bounds?

## Requirements *(mandatory)*

### Functional Requirements

- **FR-001**: The AOT code generator MUST perform symbolic sparse LU factorization of the mechanism Jacobian matrix at build time using symbolic computer algebra routines.
- **FR-002**: The generated C++ solver MUST represent LU factorization, forward substitution, and backward substitution as a flat, branchless sequence of scalar assignments with zero runtime loops.
- **FR-003**: The generated C++ solver MUST eliminate all thread-local array allocations (including `Jac[N]`, `W[N]`, `K1[N]`, `Ynew[N]`) inside GPU/CPU execution threads, mapping all variables to scalar registers.
- **FR-004**: Generated solver routines (`integrate`, `compute_rates`, `compute_jacobian`) MUST accept Kokkos subviews or layout-generic strided view interfaces instead of raw pointers (`double*`).
- **FR-005**: The code generator MUST fuse intermediate stage evaluations ($K_1$, $K_2$) and state updates ($Y_{new}$) into unrolled scalar expressions per species to minimize memory traffic.
- **FR-006**: The generator MUST emit templated Kokkos functor C++ headers capable of executing on both host CPU and device GPU execution spaces without code modification.

### Key Entities

- **Chemical Mechanism Matrix**: Symbolic representation of species reaction rate derivatives forming the $N \times N$ Jacobian.
- **Symbolic Sparse LU Plan**: Build-time schedule of symbolic pivot operations, forward substitution, and backward substitution assignments.
- **Kokkos Subview Interface**: Multi-dimensional view slice representing grid point chemical state vectors matching execution space layout conventions.

## Success Criteria *(mandatory)*

### Measurable Outcomes

- **SC-001**: Reduce thread-local memory allocation inside generated C++ solver kernels to 0 bytes (eliminating thread-local array spilling).
- **SC-002**: Achieve 0 runtime loop constructs inside generated matrix decomposition and linear solver routines ($O(1)$ control-flow overhead per timestep).
- **SC-003**: 100% elimination of raw pointer interfaces in generated C++ solver function signatures.
- **SC-004**: Achieve exact numerical equivalence ($< 10^{-12}$ relative difference) compared to dense reference Rosenbrock-2 solvers for tested chemical mechanisms.

## Assumptions

- Symbolic sparse LU factorization can be pre-computed at build time because the sparsity pattern of the chemical mechanism Jacobian is invariant during runtime.
- Target hardware platforms support at least 128 scalar registers per thread (typical for modern GPUs like NVIDIA Ampere/Hopper and AMD CDNA).
- Kokkos views and execution spaces are available in the target C++ build environment.

## Appendix: Python Strategy & C++ Blueprint Context

### Python AOT Generator Strategy (Symbolic LU)

```python
import sympy as sp

def generate_symbolic_lu(jacobian_matrix):
    """
    Computes symbolic sparse LU decomposition at build time
    and returns flat C++ assignment strings.
    """
    N = jacobian_matrix.shape[0]
    L = sp.eye(N)
    U = jacobian_matrix.copy()

    # Symbolic LU without pivoting (assuming positive-definite / pre-ordered)
    for i in range(N):
        for j in range(i + 1, N):
            if U[j, i] != 0:
                factor = U[j, i] / U[i, i]
                L[j, i] = factor
                for k in range(i, N):
                    U[j, k] = U[j, k] - factor * U[i, k]
    return L, U
```

### C++ Target Blueprint Structure

```cpp
template <class ExecSpace>
struct Rosenbrock2Solver {
    using view_1d = Kokkos::View<double*, typename ExecSpace::array_layout, typename ExecSpace::memory_space>;

    KOKKOS_INLINE_FUNCTION
    void operator()(const int idx) const {
        // Architecture-aware subview access
        auto state = Kokkos::subview(m_states, idx, Kokkos::ALL());

        // 1. Pure scalar register mapping (no arrays)
        double J_0_0 = ..., J_0_1 = ...;

        // 2. Symbolic LU Solve (Zero Loops)
        // Forward/Backward substitution scalar unroll
        double w_0 = ..., w_1 = ...;

        // 3. Fused Stage Update
        state(0) += dt * w_0;
    }
};
```
