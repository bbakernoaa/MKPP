# Implementation Plan: MKPP Built-in Solvers (Rosenbrock & LU)

**Branch**: `feature/015-mkpp-builtin-solvers` | **Date**: 2026-08-01 | **Spec**: [spec.md](spec.md)

## Summary

Inject numerical solvers directly into MKPP's generated Kokkos C++ headers. This completely relieves the host models (like Exaero) from needing to implement implicit integration routines (e.g. ROS2, ROS3) or rely on external dense matrix inversion libraries (e.g., KokkosBatched). We will implement a standalone, fully self-contained KOKKOS_INLINE_FUNCTION dense LU solver and a 2-stage L-Stable Rosenbrock method (ROS-2) directly in `codegen.py`.

## Technical Context

**Language/Version**: Python 3.14 (Code Generator), C++23 / Kokkos (Generated Output)
**Primary Dependencies**: SymPy
**Project Type**: Built-in AST Code Generation
**Constraints**: 
- **CON-001**: Must execute sequentially within a single Kokkos thread via `TeamThreadRange` (no device-wide kernels launched from inside).

## Constitution Check

| Principle | Status | Notes |
|-----------|--------|-------|
| CON-001 (GPU Threading) | PASS | LU decomposition and ROS2 steps will be marked `KOKKOS_INLINE_FUNCTION` and operate strictly on local thread memory (or unmanaged scratch) without nested kernel dispatches. |
| Self-contained | PASS | Will not require `kokkos-kernels`. |

## Project Structure

```text
src/
└── mkpp/
    └── codegen.py       # Core generator file to be modified
tests/
└── integration/
    └── e2e_validation/
        └── test_e2e_chapman.cpp  # Harness updated to use built-in integrate()
```

## Execution Strategy

### TDD Requirements
- [x] Integrate E2E test harness (`test_e2e_chapman.cpp`) to call `solver.integrate(dt, state)` and assert ROS2 behavior matches KPP.

### Human Checkpoints
1. Code review of the generated LU and ROS2 loops for off-by-one errors.
