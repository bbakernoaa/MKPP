# Implementation Plan: Multi-Solver Support

## Overview

Extend MKPP's code generation pipeline to support five Rosenbrock solvers (Ros2, Ros3, Ros4, Rodas3, Rodas4) via a `--solver` CLI flag. The implementation adds coefficient tableau storage in `codegen.py`, refactors the integrator emission into a generic stage-unrolling function, and threads solver selection through the CLI and compiler pipeline. The LU plan remains solver-independent.

## Tasks

- [x] 1. Add coefficient tableau data structure and storage
  - [x] 1.1 Define `RosenbrockTableau` dataclass and `SOLVER_COEFFICIENTS` dictionary in `codegen.py`
    - Add `from dataclasses import dataclass` and `from typing import List`
    - Create frozen `RosenbrockTableau` dataclass with fields: name, stages, A, C, M, E, Alpha, Gamma, NewF, ELO
    - Create `SOLVER_COEFFICIENTS` dictionary with all five solver tableaux (ros2, ros3, ros4, rodas3, rodas4) using full 16+ digit precision
    - Add `get_A()` and `get_C()` helper functions for row-wise lower-triangular indexing
    - Add module-level assertions verifying array length invariants for each tableau
    - _Requirements: 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8_

  - [x] 1.2 Write property test for tableau structural consistency
    - **Property 2: Tableau structural consistency**
    - **Validates: Requirements 2.1, 2.2**

  - [x] 1.3 Write property test for coefficient precision preservation
    - **Property 3: Coefficient precision preservation**
    - **Validates: Requirements 2.3**

- [x] 2. Add CLI `--solver` flag and thread through compiler pipeline
  - [x] 2.1 Add `--solver` argument to the `compile` subparser in `cli.py`
    - Add `--solver` with `choices=["ros2", "ros3", "ros4", "rodas3", "rodas4"]` and `default="ros3"`
    - Add `solver: str = "ros3"` parameter to `run_compiler()`
    - Pass `solver_name` through to `generate_headers()` call
    - _Requirements: 1.1, 1.2, 1.3, 1.4_

  - [x] 2.2 Update `generate_headers()` signature to accept `solver_name` parameter
    - Add `solver_name: str = "ros3"` parameter to `generate_headers()` function
    - Look up `SOLVER_COEFFICIENTS[solver_name]` at the start of generation
    - Pass the retrieved tableau to all stage emission logic
    - _Requirements: 1.4, 8.1, 8.2_

  - [x] 2.3 Write property test for solver name validation
    - **Property 1: Solver name validation is exhaustive**
    - **Validates: Requirements 1.1, 1.3**

- [x] 3. Checkpoint - Ensure all tests pass
  - Ensure all tests pass, ask the user if questions arise.

- [ ] 4. Implement generic Rosenbrock stage emission
  - [x] 4.1 Implement `_emit_rosenbrock_stages()` function in `codegen.py`
    - Create the function with signature: `_emit_rosenbrock_stages(f, tableau, N, lu_plan, sympy_meta, mech, perm, is_reduction=False)`
    - Implement Python-time loop that unrolls S stages into named C++ scalar variables (e.g., `K2_0`, `Y3_5`)
    - For each stage: emit intermediate state computation using A coefficients, conditional F evaluation based on NewF, RHS formation using C coefficients, and W-solve using LU plan
    - Emit solution update using M coefficients and error estimate using E coefficients
    - Emit step-size control with literal `1/ELO` exponent
    - Use `Gamma[0]` for W matrix construction: `W = (1/(gamma*dt)) * I - J`
    - _Requirements: 3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 3.7, 4.1, 4.2, 4.3, 5.1, 5.2, 5.3, 5.4_

  - [-] 4.2 Refactor existing `integrate()` emission to use `_emit_rosenbrock_stages()`
    - Replace current hardcoded 3-stage Ros3 logic with a call to `_emit_rosenbrock_stages(tableau, ...)`
    - Ensure generated output for `ros3` is identical to previous output (backward compatibility)
    - Retain `KOKKOS_INLINE_FUNCTION` annotation on generated function
    - _Requirements: 5.4, 8.1, 8.3_

  - [-] 4.3 Refactor `integrate_with_reduction()` emission to use `_emit_rosenbrock_stages()`
    - Replace current hardcoded logic with a call to `_emit_rosenbrock_stages(tableau, ..., is_reduction=True)`
    - Ensure same tableau, stage count, and ELO exponent are used as in `integrate()`
    - _Requirements: 6.1, 6.2_

  - [~] 4.4 Write property test for stage count matches generated code
    - **Property 4: Stage count matches generated code**
    - **Validates: Requirements 3.1, 5.3**

  - [~] 4.5 Write property test for NewF=false reuse behavior
    - **Property 5: NewF=false reuses prior function evaluation**
    - **Validates: Requirements 3.2**

  - [~] 4.6 Write property test for generated coefficients match tableau
    - **Property 6: Generated coefficients match tableau**
    - **Validates: Requirements 3.3, 3.4, 3.5, 3.6, 3.7**

- [~] 5. Checkpoint - Ensure all tests pass
  - Ensure all tests pass, ask the user if questions arise.

- [ ] 6. Validate GPU safety and cross-solver invariants
  - [~] 6.1 Add assertions/checks confirming GPU safety of generated code across all solvers
    - Verify generated code contains no `new`, `malloc`, `std::vector` for any solver
    - Verify no runtime-indexed stage arrays (all stage variables are named scalars)
    - Verify all stage logic is fully unrolled (no loops over stage count in generated C++)
    - _Requirements: 5.1, 5.2, 5.3_

  - [~] 6.2 Write property test for GPU safety invariants
    - **Property 8: GPU safety invariants**
    - **Validates: Requirements 5.1, 5.2, 5.3, 5.4**

  - [~] 6.3 Write property test for reduction integrator consistency
    - **Property 9: Reduction integrator consistency**
    - **Validates: Requirements 6.1, 6.2**

  - [~] 6.4 Write property test for LU plan independence from solver choice
    - **Property 10: LU plan independence from solver choice**
    - **Validates: Requirements 7.2, 7.3**

  - [~] 6.5 Write property test for function signature invariance
    - **Property 11: Function signature invariance**
    - **Validates: Requirements 8.3**

  - [~] 6.6 Write property test for step-size exponent matches ELO
    - **Property 7: Step-size exponent matches ELO**
    - **Validates: Requirements 4.1, 4.2, 4.3**

- [ ] 7. Backward compatibility and integration verification
  - [~] 7.1 Add regression test verifying default `ros3` output is unchanged
    - Generate headers with no `--solver` flag and compare against known-good Ros3 output
    - Ensure existing test suite passes without modification
    - _Requirements: 8.1, 8.2_

  - [~] 7.2 Add integration tests for each solver variant
    - Generate headers for each of the 5 solvers with a test mechanism
    - Verify each generated file compiles (syntactic correctness)
    - Verify stage counts and coefficient values in generated output match tableaux
    - _Requirements: 3.1, 7.1, 7.2, 7.3_

- [~] 8. Final checkpoint - Ensure all tests pass
  - Ensure all tests pass, ask the user if questions arise.

## Notes

- Tasks marked with `*` are optional and can be skipped for faster MVP
- Each task references specific requirements for traceability
- Checkpoints ensure incremental validation
- Property tests validate universal correctness properties from the design document
- The implementation language is Python (matching the existing codebase)
- The LU plan in `lowering.py` requires no changes — it is solver-independent
- Backward compatibility is critical: default behavior (no `--solver` flag) must produce identical output to the current Ros3-only codegen

## Task Dependency Graph

```json
{
  "waves": [
    { "id": 0, "tasks": ["1.1"] },
    { "id": 1, "tasks": ["1.2", "1.3", "2.1"] },
    { "id": 2, "tasks": ["2.2", "2.3"] },
    { "id": 3, "tasks": ["4.1"] },
    { "id": 4, "tasks": ["4.2", "4.3"] },
    { "id": 5, "tasks": ["4.4", "4.5", "4.6", "6.1"] },
    { "id": 6, "tasks": ["6.2", "6.3", "6.4", "6.5", "6.6"] },
    { "id": 7, "tasks": ["7.1", "7.2"] }
  ]
}
```
