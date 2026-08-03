# Implementation Plan: MKPP High-Impact Improvements

## Overview

This plan implements five incremental improvements to MKPP in strict dependency order: codebase stabilization → ROS-2 solver fix → cache + parallelism → sparsity optimization → auto-reduction. Each task is a self-contained coding session that builds on prior tasks. Python (3.11+) with SymPy, Hypothesis, and pytest.

## Tasks

- [ ] 1. Stabilize CLI and remove dead code
  - [x] 1.1 Remove duplicate imports, conflict markers, and dead code from cli.py
    - Remove the duplicated import block (lines 1–9 repeated at lines 11–19)
    - Remove any `<<<<<<<`, `=======`, `>>>>>>>` conflict markers in `cli.py`, `lowering.py`, `codegen.py`, `model.py`, `parser.py`, `validation.py`
    - Remove the triplicated `lump_path` processing blocks (keep one canonical version)
    - Remove reference to undefined `mech_reduced` variable
    - Verify `python -c "from mkpp.cli import main"` succeeds without ImportError/NameError/SyntaxError
    - _Requirements: 1.1, 1.3, 1.8_

  - [x] 1.2 Add --verbose, --dry-run, --no-cache, and --drgep CLI flags
    - Add `--verbose` flag that emits `[stage] description` lines to stderr at parsing, validation, partitioning, lowering, codegen
    - Add `--dry-run` flag that runs parsing + validation then exits without calling `generate_headers()`
    - Add `--no-cache` flag (wired in later task, just define the argument here)
    - Change `--enable-drgep` to `--drgep` as a fail-fast reject: raise `CompilationError` before any SymPy computation
    - Thread `verbose`, `dry_run`, `no_cache` parameters through `run_compiler()` signature
    - _Requirements: 1.4, 1.5, 1.6_

  - [x] 1.3 Add CompilationError dataclass and structured error reporting
    - Add `CompilationError` dataclass to `src/mkpp/model.py` with fields: `stage`, `message`, `reaction_index`, `species_name`, `yaml_location`
    - Update `run_compiler()` to catch exceptions, wrap them in `CompilationError`, and emit JSON-structured error to stderr
    - Ensure error messages include reaction index and species name where determinable
    - _Requirements: 1.7_

  - [x] 1.4 Write unit tests for CLI stabilization
    - Test: `mkpp compile` with valid input completes without exception
    - Test: `--drgep` rejects immediately with structured error
    - Test: `--dry-run` does not produce output files
    - Test: `--verbose` emits stage markers to stderr
    - Test: import of `mkpp.cli` succeeds without errors
    - _Requirements: 1.1, 1.2, 1.4, 1.5, 1.6_

  - [x] 1.5 Write property test for structured error messages
    - **Property 1: Structured error messages contain required fields**
    - **Validates: Requirements 1.7**
    - Generate invalid mechanisms (missing params, undefined species refs, bad types)
    - Assert `CompilationError` always has non-None `stage`, `message`, and at least one of `reaction_index`/`species_name`

- [x] 2. Checkpoint — codebase imports cleanly
  - Ensure `pip install -e .` succeeds
  - Ensure `python -c "from mkpp import cli; cli.main(['compile', '--help'])"` works
  - Ensure all existing tests pass
  - Ensure all tests pass, ask the user if questions arise.

- [ ] 3. Correct ROS-2 solver with adaptive step control
  - [x] 3.1 Fix K1 backward substitution in codegen.py
    - In the K1 backward-substitution loop, add `s = expr_str` initialization before regex substitutions
    - Ensure `s` references `y1_*` intermediates and `U_*` factors, not stale values
    - Verify emitted K1 lines reference correct variables for a small test mechanism (N=3)
    - _Requirements: 2.1_

  - [x] 3.2 Fix K2 backward substitution and add Stage 2 computation
    - Apply same `s = expr_str` fix for K2 backward-substitution loop
    - Emit complete Stage 2 sequence: compute F2 at intermediate state, form rhs2 = F2 + (-2/γ)/dt * K1, solve for K2
    - Ensure backward substitution emits K2 in correct reverse index order
    - _Requirements: 2.2_

  - [x] 3.3 Emit adaptive while-loop with error estimation
    - Wrap the ROS-2 stages in an adaptive `while (t < dt_total)` loop
    - Emit error estimator: `err_i = |K1_i - K2_i| / (atol_i + rtol_i * |state_i|)`
    - Emit step acceptance logic: accept if err_norm ≤ 1.0, reject and shrink otherwise
    - Emit step growth with safety factor (0.9) and clamping (min_shrink=0.2, max_growth=5.0)
    - _Requirements: 2.3, 2.4, 2.5_

  - [x] 3.4 Emit per-species atol[] and rtol[] arrays
    - Emit `static constexpr double atol[NUM_SPECIES]` and `rtol[NUM_SPECIES]` arrays in the generated header
    - Source defaults from mechanism metadata or use atol=1e-3, rtol=1e-4
    - Ensure array size matches `NUM_SPECIES` exactly
    - _Requirements: 2.6_

  - [x] 3.5 Write property tests for ROS-2 code generation
    - **Property 2: Backward substitution variable initialization**
    - **Validates: Requirements 2.1**
    - Generate random NxN Jacobians (N=2..12), compute LU plans, emit code, verify K1 lines never reference stale variables
    - **Property 3: Stage 2 completeness**
    - **Validates: Requirements 2.2**
    - For same generated mechanisms, verify emitted code contains F2 evaluation, rhs2 formation, K2 forward/backward sub
    - **Property 4: Tolerance array sizing**
    - **Validates: Requirements 2.6**
    - Generate mechanisms with N=1..20 species, verify emitted atol/rtol arrays have exactly N entries

  - [x] 3.6 Write integration test: generated solver vs scipy Radau reference
    - Compile a small stratospheric mechanism (N=7), generate the solver
    - Run generated solver and scipy Radau on identical initial conditions for 3600s
    - Assert species concentrations agree within specified atol/rtol bounds
    - _Requirements: 2.7_

- [x] 4. Checkpoint — ROS-2 solver correct
  - Ensure all codegen tests pass
  - Verify generated code for test mechanism compiles with nvcc/g++ (if available)
  - Ensure all tests pass, ask the user if questions arise.

- [ ] 5. Cache and parallelize AOT lowering
  - [x] 5.1 Create CacheManager class in src/mkpp/cache_manager.py
    - Add `CacheKey` and `CacheEntry` dataclasses (or reference from model.py)
    - Implement `compute_key(yaml_path)`: SHA-256 of file bytes + MKPP version string
    - Implement `lookup(key)`: load from `.mkpp_cache/<hash[:16]>.pkl`, handle corruption gracefully
    - Implement `store(key, entry)`: pickle `CacheEntry` to disk
    - _Requirements: 3.1, 3.2, 3.3_

  - [x] 5.2 Wire cache into CLI pipeline and respect --no-cache
    - In `run_compiler()`, call `cache_manager.compute_key()` after parsing
    - If cache hit and `--no-cache` not set, load cached `CacheEntry` and skip lowering
    - If cache miss, run lowering then call `store()`
    - If `--no-cache`, always skip lookup and recompute
    - _Requirements: 3.2, 3.3, 3.4_

  - [x] 5.3 Parallelize Jacobian column differentiation
    - Add `prepare_unified_jacobian_parallel()` to `lowering.py`
    - Use `multiprocessing.Pool` to compute each column ∂f/∂C_j independently
    - Assemble full Jacobian from columns in deterministic column order
    - Fall back to sequential computation if multiprocessing raises an error (log warning)
    - _Requirements: 3.5, 3.6_

  - [x] 5.4 Apply CSE and emit temporaries in codegen
    - Add `apply_cse_to_plan(lu_plan, f_vector)` in `lowering.py`: apply `sympy.cse()` to combined expression set
    - In `codegen.py`, emit `const double cse_N = <expr>;` declarations before expressions that reference them
    - Ensure declaration order: each `cse_N` declared before any reference to it
    - _Requirements: 3.7, 3.8_

  - [x] 5.5 Write property tests for cache and parallelism
    - **Property 5: Cache round-trip consistency**
    - **Validates: Requirements 3.2**
    - Generate random SymbolicLUPlans, store/load, assert structural equality
    - **Property 6: Content hash determinism and sensitivity**
    - **Validates: Requirements 3.1**
    - Generate random byte sequences, assert same input → same hash, different input → different hash
    - **Property 7: Parallel Jacobian equivalence**
    - **Validates: Requirements 3.5, 3.6**
    - Generate small mechanisms (N=2..8), compare parallel vs sequential Jacobian element-wise
    - **Property 8: CSE semantic preservation**
    - **Validates: Requirements 3.7**
    - Generate random SymPy expression trees, apply CSE, substitute back, verify numerical equivalence
    - **Property 9: CSE declaration ordering**
    - **Validates: Requirements 3.8**
    - For emitted code, parse cse_N declarations and references, assert all declarations precede references

- [x] 6. Checkpoint — cache and parallel working
  - Run compilation twice on same input, verify second run uses cache (time < 2s)
  - Ensure all property tests pass at 100+ iterations
  - Ensure all tests pass, ask the user if questions arise.

- [ ] 7. Exploit Jacobian sparsity with block-diagonal partitioning
  - [x] 7.1 Implement SparsityOptimizer class with fill-in prediction
    - Add `SparsityOptimizer` class to `lowering.py`
    - Implement `predict_fill_in()`: iterative symbolic elimination on structure graph
    - Implement `SparsityAnalysis` dataclass in `model.py`
    - Ensure `lu_expressions` only emit at structurally non-zero positions (including fill-in)
    - _Requirements: 4.1, 4.2_

  - [x] 7.2 Implement RCM bandwidth-minimizing reordering
    - Implement `compute_rcm_ordering()` using `networkx.utils.rcm.cuthill_mckee_ordering`
    - Store `permutation` and `inverse_permutation` in `SparsityAnalysis`
    - Apply permutation to Jacobian before LU decomposition
    - _Requirements: 4.3_

  - [x] 7.3 Implement block-diagonal detection via Tarjan SCC
    - Implement `detect_blocks()` using `networkx.strongly_connected_components`
    - Check cross-block independence after fill-in prediction
    - Store `blocks` and `is_block_diagonal` flag in `SparsityAnalysis`
    - Sort blocks deterministically (by minimum index)
    - _Requirements: 4.5_

  - [x] 7.4 Modify LU decomposition to accept permutation and block structure
    - Update `compute_symbolic_lu_decomposition()` signature to accept `permutation` and `blocks`
    - When `is_block_diagonal`, compute per-block LU plans independently
    - Extend `SymbolicLUPlan` with `permutation`, `blocks`, and `fill_in_count` fields
    - _Requirements: 4.2, 4.5_

  - [x] 7.5 Emit per-block LU solves and permuted indices in codegen
    - When block-diagonal, emit independent smaller LU factorize/solve sequences per block
    - When not block-diagonal, emit single reordered solve with permuted indices
    - Ensure forward/backward substitution respects reordered indices
    - _Requirements: 4.4, 4.6_

  - [x] 7.6 Write property tests for sparsity optimization
    - **Property 10: Fill-in prediction soundness**
    - **Validates: Requirements 4.1, 4.2**
    - Generate random sparse patterns (N=3..15, density 0.1–0.5), verify predicted fill ⊇ actual fill
    - **Property 11: RCM bandwidth reduction**
    - **Validates: Requirements 4.3**
    - Generate random symmetric sparse graphs (N=4..20), verify RCM bandwidth ≤ original bandwidth
    - **Property 12: Permuted solve equivalence**
    - **Validates: Requirements 4.4, 4.5, 4.6**
    - Generate random NxN matrices + RHS, solve original and permuted, verify solutions match
    - **Property 13: Sparsity optimizer determinism**
    - **Validates: Requirements 4.7**
    - Generate random structure sets, run `analyze()` twice, verify byte-identical results

- [x] 8. Checkpoint — sparsity working
  - Run full pipeline on test mechanism, verify block decomposition occurs for disconnected sub-systems
  - Ensure all property tests pass
  - Ensure all tests pass, ask the user if questions arise.

- [ ] 9. Implement Rosenbrock auto-reduction
  - [x] 9.1 Annotate LU expressions with species dependencies
    - Add `AnnotatedLUExpression` dataclass to `model.py`
    - In `lowering.py`, after computing LU plan, annotate each expression with the set of species indices it depends on
    - Add `annotated_expressions` field to `SymbolicLUPlan`
    - _Requirements: 5.6_

  - [x] 9.2 Emit integrate_with_reduction() kernel in codegen
    - Emit `species_importance[N]` array and `importance_threshold` parameter in the header
    - Emit importance evaluation: `importance_i = |F_i| / (atol_i + rtol_i * |C_i|)`
    - Emit active/frozen logic: zero Jacobian rows/cols for frozen species, set identity diagonal
    - Emit conditional LU skip using annotated dependencies
    - Emit K1=0, K2=0 for frozen species; normal solve for active species
    - Emit re-activation: species with importance above threshold rejoin active set on next step
    - Wire into adaptive step control loop from Component 2
    - _Requirements: 5.1, 5.2, 5.3, 5.4, 5.5, 5.6_

  - [x] 9.3 Write property tests for auto-reduction
    - **Property 14: Auto-reduction freeze correctness**
    - **Validates: Requirements 5.3, 5.4**
    - Generate states + importance vectors with some species below threshold, verify K=0 and state unchanged
    - **Property 15: Auto-reduction re-activation**
    - **Validates: Requirements 5.5, 5.6**
    - Generate sequences of importance vectors crossing threshold, verify species correctly transition active↔frozen

  - [x] 9.4 Write integration test: auto-reduced vs full solver accuracy
    - Compile test mechanism, run full solver and auto-reduced solver on same initial conditions
    - Assert species concentrations agree within atol/rtol over 3600s window
    - _Requirements: 5.7_

- [ ] 10. Final checkpoint
  - Run full test suite: `pytest tests/ -v`
  - Run full pipeline end-to-end: `mkpp compile test_mechanism.yaml --test-env test.yaml --out /tmp/mkpp_out --verbose`
  - Verify no regressions in generated output for unchanged inputs (determinism)
  - Ensure all tests pass, ask the user if questions arise.

## Notes

- Tasks marked with `*` are optional and can be skipped for faster MVP
- Each task references specific requirements for traceability
- Checkpoints ensure incremental validation between major components
- Property tests validate universal correctness properties (Hypothesis, 100+ iterations each)
- Unit tests validate specific examples and edge cases
- The dependency order (R1→R2→R3→R4→R5) is strictly enforced by task sequencing
- All generated C++ must remain pure Kokkos (no raw pragmas, no `std::` in device code)

## Task Dependency Graph

```json
{
  "waves": [
    { "id": 0, "tasks": ["1.1"] },
    { "id": 1, "tasks": ["1.2", "1.3"] },
    { "id": 2, "tasks": ["1.4", "1.5"] },
    { "id": 3, "tasks": ["3.1", "3.2"] },
    { "id": 4, "tasks": ["3.3", "3.4"] },
    { "id": 5, "tasks": ["3.5", "3.6"] },
    { "id": 6, "tasks": ["5.1", "5.3"] },
    { "id": 7, "tasks": ["5.2", "5.4"] },
    { "id": 8, "tasks": ["5.5"] },
    { "id": 9, "tasks": ["7.1", "7.2", "7.3"] },
    { "id": 10, "tasks": ["7.4"] },
    { "id": 11, "tasks": ["7.5"] },
    { "id": 12, "tasks": ["7.6"] },
    { "id": 13, "tasks": ["9.1"] },
    { "id": 14, "tasks": ["9.2"] },
    { "id": 15, "tasks": ["9.3", "9.4"] }
  ]
}
```
