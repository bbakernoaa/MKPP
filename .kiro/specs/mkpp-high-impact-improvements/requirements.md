# Requirements Document

## Introduction

This document specifies five high-impact improvements to the Multiphase Kinetic PreProcessor (MKPP), an atmospheric chemistry ODE solver generator. MKPP uses a Python AOT frontend (SymPy + NetworkX) to compile chemical mechanism YAML files into optimized Kokkos C++ headers featuring symbolic sparse LU factorization, analytical Jacobians, Adjoints, and Tangent Linear Models. The improvements address foundational code health, numerical correctness, compilation performance, and runtime performance in priority order.

## Glossary

- **MKPP**: Multiphase Kinetic PreProcessor — the system under specification
- **AOT_Frontend**: The Python ahead-of-time compilation pipeline (`lowering.py`, `codegen.py`) that transforms mechanism YAML into C++ headers
- **Mechanism**: A YAML file defining chemical species, reactions, rate parameters, and metadata consumed by the AOT_Frontend
- **CLI**: The command-line interface (`cli.py`) providing user access to MKPP's compilation pipeline
- **Jacobian_Builder**: The `prepare_unified_jacobian()` function in `lowering.py` that computes the symbolic Jacobian matrix
- **LU_Decomposer**: The `compute_symbolic_lu_decomposition()` function in `lowering.py` that performs symbolic sparse Doolittle LU factorization
- **Code_Generator**: The `generate_headers()` function in `codegen.py` that emits Kokkos C++ solver kernels
- **SymbolicLUPlan**: The data structure holding non-zero Jacobian entries, L/U expressions, and forward/backward substitution steps
- **ROS-2**: A two-stage Rosenbrock implicit ODE solver method with error estimation
- **CSE**: Common Sub-expression Elimination — a SymPy optimization pass that factors repeated sub-expressions
- **Cache_Manager**: The proposed subsystem managing incremental build caching in `.mkpp_cache/`
- **Auto_Reducer**: The proposed runtime subsystem that dynamically freezes near-equilibrium species
- **Sparsity_Optimizer**: The proposed subsystem performing bandwidth-minimizing reordering and block-diagonal detection
- **RCM**: Reverse Cuthill-McKee algorithm for bandwidth-minimizing matrix reordering
- **AMD**: Approximate Minimum Degree algorithm for fill-reducing matrix reordering
- **SCC**: Strongly Connected Component — a maximal subset of mutually reachable nodes in a directed graph

## Requirements

### Requirement 1: Resolve Merge Conflicts and Stabilize Codebase

**User Story:** As a developer, I want all source files free of merge conflict markers and dead code, so that MKPP can be imported, tested, and extended without errors.

#### Acceptance Criteria

1. THE CLI SHALL import and execute without raising `SyntaxError`, `NameError`, or `ImportError` exceptions
2. WHEN the user runs `pip install -e .` followed by `mkpp compile <mechanism> --test-env <env> --out <dir>`, THE CLI SHALL complete the compilation pipeline without unhandled exceptions for valid inputs
3. THE CLI SHALL contain no duplicate import blocks, no triplicated code blocks, and no references to undefined variables
4. WHEN the `--drgep` flag is supplied, THE CLI SHALL reject the compilation request with a structured error message before any SymPy computation begins
5. WHEN the `--verbose` flag is supplied, THE CLI SHALL emit progress messages to stderr at each major pipeline stage (parsing, validation, partitioning, lowering, code generation)
6. WHEN the `--dry-run` flag is supplied, THE CLI SHALL validate the mechanism schema and report results without emitting any C++ code
7. IF a validation error occurs, THEN THE CLI SHALL emit a structured error message containing the offending reaction index, species name, and YAML source location where determinable
8. THE CLI SHALL NOT contain any git merge conflict markers (`<<<<<<<`, `=======`, `>>>>>>>`)

### Requirement 2: Correct the Rosenbrock Solver — Full ROS-2 with Adaptive Step Control

**User Story:** As an atmospheric modeler, I want the generated Rosenbrock solver to implement a correct two-stage algorithm with error estimation, so that I can trust integration results for real atmospheric timesteps.

#### Acceptance Criteria

1. WHEN the Code_Generator emits the `integrate()` function, THE Code_Generator SHALL produce backward substitution expressions for K1 that reference the correct forward-substitution intermediate values (not a fixed placeholder)
2. WHEN the Code_Generator emits the `integrate()` function, THE Code_Generator SHALL emit a complete Stage 2 computation: evaluate F2 at the intermediate state, form the Stage 2 RHS, and solve the linear system for K2
3. WHEN the Code_Generator emits the `integrate()` function, THE Code_Generator SHALL emit an embedded error estimator computed as `err_i = |K1_i - K2_i| / (atol_i + rtol_i * |state_i|)` for each species i
4. WHEN the computed error norm exceeds 1.0, THE generated solver SHALL reject the current step and retry with `dt_new = dt * safety_factor * (1.0 / err_norm)^0.5`
5. WHEN the computed error norm is at or below 1.0, THE generated solver SHALL accept the step and propose `dt_new = dt * safety_factor * (1.0 / err_norm)^0.5` clamped to a maximum growth factor
6. THE Code_Generator SHALL emit per-species `atol[]` and `rtol[]` arrays as configurable parameters in the generated header
7. WHEN validated against a scipy Radau reference solution for a test mechanism, THE generated solver SHALL produce species concentrations within the specified rtol/atol bounds over a 3600-second integration window

### Requirement 3: Cache and Parallelize the AOT Lowering Step

**User Story:** As a developer iterating on mechanism files, I want the SymPy compilation step to be cached and parallelized, so that recompilation completes in seconds rather than minutes.

#### Acceptance Criteria

1. WHEN a mechanism is compiled, THE Cache_Manager SHALL compute a content hash from the mechanism YAML file contents and the MKPP package version string
2. WHEN a cache entry with a matching hash exists in `.mkpp_cache/`, THE AOT_Frontend SHALL load the serialized symbolic matrices and SymbolicLUPlan from the cache instead of recomputing them
3. WHEN no matching cache entry exists, THE AOT_Frontend SHALL compute the symbolic matrices, serialize them to `.mkpp_cache/`, and proceed with code generation
4. WHEN the `--no-cache` flag is supplied, THE AOT_Frontend SHALL skip cache lookup and recompute all symbolic matrices unconditionally
5. WHEN computing the Jacobian matrix for a mechanism with N species, THE Jacobian_Builder SHALL parallelize column differentiation across available CPU cores using `multiprocessing.Pool`
6. WHEN parallel column computation completes, THE Jacobian_Builder SHALL assemble the full Jacobian matrix from the independently computed columns in deterministic column order
7. WHEN the final Jacobian expressions are computed, THE AOT_Frontend SHALL apply `sympy.cse()` to the complete expression set before passing them to the Code_Generator
8. WHEN CSE is applied, THE Code_Generator SHALL emit the extracted common sub-expressions as named temporaries preceding the expressions that reference them

### Requirement 4: Exploit Jacobian Sparsity with Block-Diagonal Partitioning

**User Story:** As a performance engineer, I want the symbolic LU decomposition to exploit sparsity structure, so that generated solvers have minimal FLOP count and register pressure on GPUs.

#### Acceptance Criteria

1. WHEN computing the LU decomposition, THE Sparsity_Optimizer SHALL compute the symbolic fill-in pattern via graph reachability on the iteration matrix structure
2. THE LU_Decomposer SHALL emit L and U expressions only for positions that are structurally non-zero after accounting for fill-in
3. WHEN the Jacobian matrix is provided, THE Sparsity_Optimizer SHALL apply a bandwidth-minimizing reordering (RCM or AMD) before LU factorization to reduce fill-in
4. WHEN a permutation is applied, THE Code_Generator SHALL emit the permuted variable ordering and ensure forward/backward substitution respects the reordered indices
5. WHEN Tarjan SCC analysis reveals independent diagonal blocks in the Jacobian, THE Sparsity_Optimizer SHALL decompose the system into separate block-level LU solves
6. WHEN block-diagonal structure is detected, THE Code_Generator SHALL emit independent smaller LU factorization and solve sequences per block rather than a single N×N solve
7. THE Sparsity_Optimizer SHALL produce byte-identical output for unchanged inputs (deterministic reordering)

### Requirement 5: Implement Rosenbrock Auto-Reduction

**User Story:** As a computational scientist running large mechanisms, I want the solver to dynamically freeze near-equilibrium species at runtime, so that the effective system size adapts to chemical activity and reduces compute cost.

#### Acceptance Criteria

1. WHEN the AOT_Frontend compiles a mechanism, THE Code_Generator SHALL emit a `species_importance[N]` diagnostic array and a configurable threshold parameter in the generated header
2. WHEN the generated solver begins a Rosenbrock step, THE generated solver SHALL evaluate `importance_i = |dC_i/dt| / (atol_i + rtol_i * |C_i|)` for each implicit species i
3. WHEN `importance_i` falls below the threshold for species i, THE generated solver SHALL zero the Jacobian row and column for species i and skip that species during the LU solve
4. WHEN a species is frozen, THE generated solver SHALL preserve the species concentration unchanged for that timestep
5. WHEN a previously frozen species has `importance_i` exceeding the threshold on a subsequent step, THE generated solver SHALL re-activate that species for the full implicit solve
6. THE Auto_Reducer SHALL leverage the existing SymbolicLUPlan non-zero structure to conditionally skip only the affected L/U scalar operations
7. WHEN auto-reduction is active, THE generated solver SHALL produce results within the same atol/rtol tolerances as the full unreduced solver for a reference test mechanism

## Priority and Dependencies

1. Requirement 1 is foundational — all other requirements depend on a clean, importable codebase
2. Requirement 2 depends on Requirement 1 — correct code generation requires a working pipeline
3. Requirement 3 depends on Requirement 1 — caching requires stable serializable intermediate representations
4. Requirement 4 depends on Requirements 1 and 3 — sparsity optimization refines the existing LU decomposition path
5. Requirement 5 depends on Requirements 2 and 4 — auto-reduction requires a correct adaptive solver and sparse structure awareness

## Constraints

- All improvements SHALL maintain byte-identical output for unchanged inputs (determinism requirement)
- Generated C++ SHALL remain pure Kokkos (no raw pragmas, no `std::` in device code)
- The Python frontend SHALL support Python 3.11+
- All improvements SHALL pass the existing test suite after implementation
- All improvements SHALL preserve the existing CLI contract (`mkpp compile <mechanism> --test-env <env> --out <dir>`)
