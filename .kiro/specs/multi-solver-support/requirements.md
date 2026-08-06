# Requirements Document

## Introduction

MKPP currently generates Kokkos C++ integrator headers using a hardcoded Ros3 (3-stage, order 3) Rosenbrock solver. This feature adds compile-time selection among five Rosenbrock solvers (Ros2, Ros3, Ros4, Rodas3, Rodas4), controlled via a `--solver` CLI flag. The generated `integrate()` and `integrate_with_reduction()` functions adapt their stage count, coefficients, and error estimation to the selected solver while remaining GPU-safe and numerically equivalent to the KPP reference implementation.

## Glossary

- **MKPP_Compiler**: The `mkpp compile` command-line tool that parses mechanism YAML, performs symbolic lowering, and emits Kokkos C++ headers.
- **Codegen_Module**: The Python module `src/mkpp/codegen.py` responsible for emitting generated C++ source text.
- **Solver**: One of the five supported Rosenbrock methods (Ros2, Ros3, Ros4, Rodas3, Rodas4) defined by its coefficient tableau.
- **Coefficient_Tableau**: The set of numerical arrays (A, C, M, E, Alpha, Gamma, NewF, ELO) that fully define a Rosenbrock solver's behavior.
- **Stage**: A single implicit evaluation within one Rosenbrock time step; each solver has a fixed number of stages (2, 3, 4, or 6).
- **Generated_Integrator**: The `integrate()` C++ template function emitted by Codegen_Module into the mechanism header.
- **Reduction_Integrator**: The `integrate_with_reduction()` C++ template function emitted alongside Generated_Integrator.
- **Step_Controller**: The adaptive step-size logic within Generated_Integrator that uses error estimation and the exponent 1/ELO.
- **LU_Plan**: The symbolic ahead-of-time LU factorization plan (W = I - gamma*dt*J) reused across all solvers.
- **KPP_Reference**: The Fortran 90 reference implementation in `kpp_legacy/saprc99_diurnal_Integrator.f90`.

## Requirements

### Requirement 1: CLI Solver Selection

**User Story:** As a developer, I want to select a Rosenbrock solver via a CLI flag, so that I can generate integrator code tuned for different accuracy/performance trade-offs.

#### Acceptance Criteria

1. THE MKPP_Compiler SHALL accept a `--solver` flag with allowed values `ros2`, `ros3`, `ros4`, `rodas3`, and `rodas4`.
2. WHEN the `--solver` flag is omitted, THE MKPP_Compiler SHALL default to `ros3`.
3. WHEN an invalid value is provided for `--solver`, THE MKPP_Compiler SHALL exit with a non-zero status code and emit a diagnostic message listing the valid solver names.
4. THE MKPP_Compiler SHALL pass the selected solver name to Codegen_Module for use during header generation.

### Requirement 2: Coefficient Tableau Storage

**User Story:** As a maintainer, I want all solver coefficients stored in a single authoritative location within Codegen_Module, so that adding or modifying solvers requires changes in only one place.

#### Acceptance Criteria

1. THE Codegen_Module SHALL store Coefficient_Tableau data for each of the five Solvers as a flat Python dictionary keyed by solver name.
2. WHEN a Coefficient_Tableau is accessed, THE Codegen_Module SHALL provide arrays A, C, M, E, Alpha, Gamma, NewF, and the scalar ELO.
3. THE Codegen_Module SHALL store coefficient values with at least 16 significant decimal digits to preserve double-precision fidelity.
4. THE Codegen_Module SHALL store the Ros2 tableau with gamma = 1 + 1/sqrt(2), 2 stages, and ELO = 2.
5. THE Codegen_Module SHALL store the Ros3 tableau with gamma = 0.43586652150845899941601945119356, 3 stages, and ELO = 3.
6. THE Codegen_Module SHALL store the Ros4 tableau with 4 stages, L-stable coefficients from Hairer & Wanner (1990), and ELO = 4.
7. THE Codegen_Module SHALL store the Rodas3 tableau with 4 stages, stiffly-accurate coefficients, and ELO = 3.
8. THE Codegen_Module SHALL store the Rodas4 tableau with 6 stages, stiffly-accurate coefficients from Hairer & Wanner (1996), and ELO = 4.

### Requirement 3: Adaptive Integrator Code Generation

**User Story:** As a developer, I want the generated `integrate()` function to implement the correct number of stages and coefficients for the selected solver, so that the numerical integration matches the solver's mathematical definition.

#### Acceptance Criteria

1. WHEN generating code for a Solver with S stages, THE Codegen_Module SHALL emit exactly S stage computations within Generated_Integrator.
2. WHEN a stage has NewF set to false, THE Codegen_Module SHALL emit code that reuses the function evaluation from the previous stage instead of computing a new one.
3. THE Generated_Integrator SHALL compute the solution update as the weighted sum of stage vectors using the M coefficients from the selected Solver's Coefficient_Tableau.
4. THE Generated_Integrator SHALL compute the error estimate as the weighted sum of stage vectors using the E coefficients from the selected Solver's Coefficient_Tableau.
5. THE Generated_Integrator SHALL use the A coefficients to form the predictor for each stage's function evaluation.
6. THE Generated_Integrator SHALL use the C coefficients to form the linear combination contribution from prior stages to each stage solve.
7. THE Generated_Integrator SHALL construct the system matrix W = I - gamma*dt*J using the first Gamma value from the selected Solver's Coefficient_Tableau.

### Requirement 4: Adaptive Step-Size Control

**User Story:** As a developer, I want the step controller to use the correct error order exponent for each solver, so that the step-size adaptation is optimal for the selected method's order.

#### Acceptance Criteria

1. THE Step_Controller SHALL compute the step-size growth factor using the exponent 1/ELO where ELO is taken from the selected Solver's Coefficient_Tableau.
2. WHEN the error estimate exceeds the tolerance, THE Step_Controller SHALL reject the step and recompute with a reduced step size scaled by safety * error^(-1/ELO).
3. WHEN the error estimate is within tolerance, THE Step_Controller SHALL accept the step and propose a new step size bounded by the max_growth factor.

### Requirement 5: GPU Safety of Generated Code

**User Story:** As a developer targeting GPU execution, I want the generated integrator to avoid dynamic memory allocation and variable-length loops, so that the code runs efficiently in Kokkos GPU kernels.

#### Acceptance Criteria

1. THE Generated_Integrator SHALL declare all stage variables as named scalar registers with compile-time-determined names (no runtime-indexed arrays over stages).
2. THE Generated_Integrator SHALL contain no dynamic memory allocations (no `new`, `malloc`, or `std::vector`).
3. THE Generated_Integrator SHALL contain no loops whose iteration count depends on the number of solver stages; all stage logic SHALL be fully unrolled at code-generation time.
4. THE Generated_Integrator SHALL use the `KOKKOS_INLINE_FUNCTION` annotation to remain callable from GPU kernels.

### Requirement 6: Reduction Integrator Consistency

**User Story:** As a developer, I want `integrate_with_reduction()` to use the same selected solver as `integrate()`, so that reduction-based workflows produce identical numerical results.

#### Acceptance Criteria

1. WHEN code is generated, THE Codegen_Module SHALL emit Reduction_Integrator using the same Solver selection as Generated_Integrator.
2. THE Reduction_Integrator SHALL use the same Coefficient_Tableau, stage count, and Step_Controller exponent as Generated_Integrator for the selected Solver.

### Requirement 7: Numerical Equivalence with KPP Reference

**User Story:** As a scientist, I want the generated solvers to produce results matching the KPP Fortran reference, so that I can trust the C++ implementation for production atmospheric chemistry.

#### Acceptance Criteria

1. WHEN the same initial conditions, tolerances, and step sizes are applied, THE Generated_Integrator for each Solver SHALL produce species concentrations within 1e-12 relative tolerance of KPP_Reference output for that solver.
2. THE Generated_Integrator SHALL use the same W factorization structure (I - gamma*dt*J) as KPP_Reference for all five Solvers.
3. THE LU_Plan SHALL be reused identically across all Solvers since the sparsity pattern of J is independent of solver choice.

### Requirement 8: Backward Compatibility

**User Story:** As an existing user, I want the default behavior of MKPP to remain unchanged, so that my existing workflows and tests continue to pass without modification.

#### Acceptance Criteria

1. WHEN `--solver` is not specified, THE MKPP_Compiler SHALL generate code identical to the current Ros3-only output.
2. WHEN existing test suites are executed without specifying `--solver`, THE MKPP_Compiler SHALL produce passing results with no behavioral regressions.
3. THE MKPP_Compiler SHALL not alter the function signature of `integrate()` or `integrate_with_reduction()` for any solver selection.
