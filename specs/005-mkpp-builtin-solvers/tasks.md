---
description: "Task list for Built-in MKPP Solvers"
---

# Tasks: Built-in Solvers

## Phase 1: Core Solver Generation

- [x] T001 [US1] Add a `KOKKOS_INLINE_FUNCTION` Dense LU decomposition (`lu_decompose`) to `mkpp/codegen.py`
- [x] T002 [US1] Add a `KOKKOS_INLINE_FUNCTION` Dense LU back-substitution (`lu_solve`) to `mkpp/codegen.py`
- [x] T003 [US2] Implement the `integrate` function in `mkpp/codegen.py` combining ROS2 method, `compute_jacobian`, `compute_rates`, and the LU solver.

## Phase 2: End-to-End Test Integration

- [x] T004 [US2] Update `test_e2e_chapman.cpp` to remove the mock Euler step and invoke `solver.integrate(dt, state)`.
- [x] T005 [US2] Update `compare_baselines.py` to re-enable concentration RMSE checking against the legacy KPP baseline.
