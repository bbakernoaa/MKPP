# Implementation Plan: Ahead-Of-Time (AOT) Symbolic LU Kokkos ODE Solver Generator

**Branch**: `013-aot-symbolic-lu-solver` | **Date**: 2026-08-02 | **Spec**: [spec.md](./spec.md)
**Input**: Feature specification from `specs/013-aot-symbolic-lu-solver/spec.md`

## Summary

Refactor the Python AOT code generator (`src/mkpp/codegen.py` and `src/mkpp/lowering.py`) to emit Kokkos C++ ODE solver headers using build-time symbolic sparse LU factorization, pure scalar register mapping (zero thread-local arrays), architecture-aware Kokkos subview interfaces (zero raw double pointers), and fused stage update expressions for Rosenbrock-2 (ROS-2) integration. This eliminates GPU local memory stack spilling (80 KB thread bomb), removes $O(N^3)$ warp divergence and CPU cache thrashing, and ensures optimal performance portability across host CPU and device GPU architectures.

## Technical Context

**Language/Version**: Python 3.10+ (AOT generator), C++20 / C++23 (emitted Kokkos headers)
**Primary Dependencies**: SymPy (symbolic algebra & differentiation), Kokkos 4.x (HPC abstraction framework)
**Storage**: File system (emission of C++ `.hpp` headers)
**Testing**: `pytest` (Python generator unit/integration tests), `ctest` / C++ compilation checks
**Target Platform**: Multi-tenant HPC supercomputers (NOAA WCOSS / Cray / Linux clusters with NVIDIA Ampere/Hopper GPUs and x86_64/ARM CPUs)
**Project Type**: Ahead-Of-Time compiler module and generated C++ header library
**Performance Goals**:
- 0 bytes thread-local stack array allocation inside Kokkos thread execution functors
- 0 runtime `for` loop iterations in matrix LU decomposition and forward/backward substitution
- 100% elimination of raw pointer signatures (`double*`)
- Exact numerical accuracy ($< 10^{-12}$ relative tolerance) compared to reference ODE solvers
**Constraints**:
- Absolute compliance with NOAA NWS OMD Master Guidelines and EE2 standards
- Code must compile with GCC, Clang, Intel icpx, and NVCC compilers without warnings

## Constitution Check

*GATE: Must pass before proceeding. Re-check after design phase.*

| Principle | Status | Notes |
|-----------|--------|-------|
| **1. Security & Federal Compliance** | PASS | No secrets, credentials, or dynamic external command executions introduced. Pure code generation. |
| **2. EE2 Standards Compliance** | PASS | Fail-fast loud errors on invalid matrix dimensions, deterministic header generation, zero background processing. |
| **3. High-Performance Computing & GPU Portability** | PASS | Replaces thread-local array stack allocations with scalar register mapping, avoiding GPU local memory spilling and warp divergence. |
| **4. Multi-Dimensional Scientific Data Layouts** | PASS | Accepts templated subview state representations that adapt to `Kokkos::LayoutLeft` or `Kokkos::LayoutRight`. |
| **5. Zero Dead Code & Defensive Programming** | PASS | Completely removes unused legacy loop-based `lu_decompose` and `lu_solve` templates. Validates matrix invertibility at build time. |

## Project Structure

### Documentation (this feature)

```text
specs/013-aot-symbolic-lu-solver/
├── spec.md              # Feature specification
├── plan.md              # This file
├── research.md          # Technical research & decision record
├── data-model.md        # Entity definitions & workflow diagrams
├── quickstart.md        # Runnable validation guide
├── contracts/
│   └── contracts.md     # Interface contracts for Python generator & C++ solver
└── checklists/
    └── requirements.md  # Specification quality checklist
```

### Source Code (repository root)

```text
src/
└── mkpp/
    ├── lowering.py      # Computes symbolic Jacobian & symbolic LU factorization plan
    ├── codegen.py       # Emits unrolled scalar C++ Kokkos ODE solver headers
    └── model.py         # Chemical mechanism data structures

tests/
├── test_codegen_symbolic_lu.py  # Unit & integration tests for symbolic LU generation
└── test_solver_accuracy.py      # Numerical validation against reference Rosenbrock-2
```

**Structure Decision**: Code generation changes are localized to `src/mkpp/lowering.py` and `src/mkpp/codegen.py` within the existing `mkpp` package layout, accompanied by new targeted unit and numerical accuracy tests.

## Execution Strategy

### TDD Requirements

- [x] `test_codegen_symbolic_lu.py`: Test symbolic LU decomposition logic for 2x2, 3x3, and mechanism-scale Jacobians. Verify emitted C++ strings contain zero array declarations (`Jac[...]`, `W[...]`) and zero `for (` loops.
- [x] `test_solver_accuracy.py`: Verify that generated scalar ROS-2 solver matches reference ODE integrator output within $10^{-12}$ relative precision.

### Parallel Execution Opportunities

- [x] **Work Stream A**: Lowering & Symbolic Sparse LU Engine (`src/mkpp/lowering.py`)
- [x] **Work Stream B**: C++ Scalar Unrolling Code Generator (`src/mkpp/codegen.py`)
- [x] Work Stream A and Work Stream B can be developed and unit tested independently once symbolic LU plan interface contract is finalized.

### Human Checkpoints

1. **Foundational Setup Checkpoint**: Verify symbolic LU plan data structure and SymPy elimination routines.
2. **Code Generation Checkpoint**: Inspect generated C++ header for SAPRC99 or Chapman mechanism to confirm 0 array allocations and 0 runtime loops.
3. **Numerical Validation Checkpoint**: Confirm exact numerical agreement against reference Rosenbrock-2 integrator.

### Review Gates

- [x] `src/mkpp/lowering.py`: Code review on symbolic LU pivoting and zero-diagonal error handling.
- [x] `src/mkpp/codegen.py`: Code review on C++ view template signatures and fused stage update generation.

## Complexity Tracking

| Violation | Why Needed | Simpler Alternative Rejected Because |
|-----------|------------|-------------------------------------|
| *None* | N/A | N/A |

- [ ] [Data model changes]: Review before migration

## Complexity Tracking

> **Fill ONLY if Constitution Check has violations that must be justified**

| Violation | Why Needed | Simpler Alternative Rejected Because |
|-----------|------------|-------------------------------------|
| [e.g., extra dependency] | [current need] | [why simpler approach insufficient] |
