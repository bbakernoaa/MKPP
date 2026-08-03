# Implementation Plan: E2E Solver Validation & Baseline Testing

**Branch**: `feature/014-e2e-solver-validation` | **Date**: 2026-08-01 | **Spec**: [spec.md](spec.md)
**Input**: Feature specification from `specs/004-e2e-solver-validation/spec.md`

## Summary

Build a validation test suite that runs the Exaero C++ box-model with MKPP generated headers against a legacy KPP Fortran baseline for a standard mechanism (e.g., Chapman Cycle). The suite will verify analytical Jacobian sparsity patterns (AOT Generation) and integration accuracy (RMSE < 1e-6) while strictly ensuring zero memory overhead.

## Technical Context

**Language/Version**: C++23 (Validation Runner), Python 3.14 (Test driver/fixture)
**Primary Dependencies**: Kokkos, MKPP (Python), Exaero, GoogleTest, Pytest, NumPy (for RMSE)
**Storage**: N/A
**Testing**: CMake CTest / Pytest
**Target Platform**: Linux HPC clusters / CPUs / GPUs
**Project Type**: Testing/Validation fixture
**Performance Goals**: Zero-byte overhead (CON-001, CON-002) in solver execution.
**Constraints**: 
- **CON-001**: TeamPolicy divergence (must use Kokkos hierarchical parallelism)
- **CON-002**: LayoutLeft interoperability (zero-copy handshakes)

## Constitution Check

*GATE: Must pass before proceeding. Re-check after design phase.*

| Principle | Status | Notes |
|-----------|--------|-------|
| CON-001 (GPU Load Balancing) | PASS | Validation runner will verify 0-byte dynamic allocation during execution. |
| CON-002 (Zero-Copy) | PASS | Runner will pass C++ unmanaged layout_left views identical to Fortran expectations. |
| Test-First (TDD) | PASS | A testing framework will wrap the solver verification itself. |

## Project Structure

### Documentation (this feature)

```text
specs/004-e2e-solver-validation/
├── spec.md              # Feature specification
├── plan.md              # This file
├── tasks.md             # Task breakdown
├── research.md          # Technical unknowns & decisions
├── data-model.md        # Validation schemas
├── contracts/
│   └── test-harness.md  # Contracts for Exaero <-> Baseline testing
└── quickstart.md        # Guide to run E2E tests
```

### Source Code (repository root)

```text
tests/
├── integration/
│   ├── e2e_validation/
│   │   ├── CMakeLists.txt
│   │   ├── test_e2e_chapman.cpp          # C++ harness for Exaero execution
│   │   ├── compare_baselines.py          # Python RMSE script checking output
│   │   └── data/
│   │       ├── chapman.eqn               # KPP mechanism file
│   │       └── kpp_baseline_chapman.csv  # Pre-generated legacy KPP output
```

**Structure Decision**: Keep integration validation completely isolated in `tests/integration/e2e_validation` to avoid polluting the core `exaero` and `mkpp` source code. 

## Execution Strategy

### TDD Requirements

- [x] **Compare Baselines Script**: Write tests for the Python RMSE comparator before running it on real model output.
- [x] **C++ Harness**: Verify the harness can ingest a dummy output before comparing to real KPP output.

### Parallel Execution Opportunities

- [x] MKPP structural parsing and Jacobian sparsity verification can run in parallel with the Exaero C++ box-model runner development.

### Human Checkpoints

1. After generating the KPP baseline dataset to ensure the reference data is valid.
2. Before merging E2E results.

### Review Gates

- [x] **Validation Fixture**: Review the RMSE tolerance and Kokkos profiling assertions to ensure they are strict enough.
