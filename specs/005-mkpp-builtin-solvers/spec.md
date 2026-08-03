# Feature Specification: MKPP Built-in Solvers (Rosenbrock & LU)

**Feature Branch**: `feature/015-mkpp-builtin-solvers`
**Created**: 2026-08-01
**Status**: Draft

## User Scenarios & Testing *(mandatory)*

### User Story 1 - Built-in Dense LU Factorization (Priority: P1)
As a computational scientist, I want MKPP to generate a standalone, inline Dense LU factorization and back-substitution routine within the Kokkos C++ headers, so that the chemical mechanism can be inverted on GPUs without relying on external libraries like `kokkos-kernels` (KokkosBatched), which may not be installed on all host machines.

**Acceptance Scenarios**:
1. **Given** a generated mechanism header, **When** compiled, **Then** it contains a `KOKKOS_INLINE_FUNCTION` for dense LU decomposition and back-substitution.
2. **Given** a stiff Jacobian, **When** evaluated, **Then** the generated LU solver accurately factorizes and solves the linear system $A x = b$.

### User Story 2 - Built-in Rosenbrock Integrator (Priority: P1)
As an atmospheric modeler, I want MKPP to emit a full Rosenbrock integration loop (e.g., ROS2) directly inside the generated `SolverKernels`, so that the host utility only needs to call `solver.integrate(dt, state)` without implementing the numerical methods itself.

**Acceptance Scenarios**:
1. **Given** the generated headers, **When** `integrate()` is called with a time step `dt`, **Then** the solver successfully advances the state using a standard Rosenbrock formulation.
2. **Given** the E2E validation suite, **When** Exaero evaluates the generated ROS2 solver, **Then** the final concentrations match the legacy KPP baseline (within tolerances) and the integration overhead remains 0-bytes.

## Requirements *(mandatory)*
- **FR-001**: MKPP must emit a C++ inline Dense LU Solver (pivotless or partial pivoting) suitable for small dense reaction matrices.
- **FR-002**: MKPP must emit a 2-stage (ROS2) or 3-stage Rosenbrock solver loop.
- **FR-003**: The solver must be fully self-contained inside the `mkpp` namespace in the generated header.
- **FR-004**: The generated solver must use the previously verified `compute_jacobian` and `compute_rates` functions.

## Success Criteria *(mandatory)*
- **SC-001**: The E2E tests pass using the *internally generated* `integrate()` function rather than a mocked Euler step in the C++ test harness.
