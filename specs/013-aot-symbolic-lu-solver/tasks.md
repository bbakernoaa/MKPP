# Tasks: Ahead-Of-Time (AOT) Symbolic LU Kokkos ODE Solver Generator

**Input**: Design documents from `specs/013-aot-symbolic-lu-solver/`
**Prerequisites**: `plan.md` (required), `spec.md` (required for user stories), `research.md`, `data-model.md`, `contracts/contracts.md`

## Task Format

```
- [ ] [TaskID] [P?] [TDD?] [REVIEW?] [Story?] Description with file path
```

- **[P]**: Can run in parallel (different files, no dependencies)
- **[TDD]**: Follow RED-GREEN-REFACTOR cycle
- **[REVIEW]**: Code review checkpoint
- **[Story]**: User story label (`[US1]`, `[US2]`, `[US3]`)

---

## Phase 1: Setup (Shared Infrastructure)

**Purpose**: Test infrastructure initialization and benchmark setup for symbolic LU solver generator

- [x] T001 Create unit test harness for symbolic LU solver generator in `tests/python/test_codegen_symbolic_lu.py`
- [x] T002 [P] Initialize benchmark test fixture for Rosenbrock-2 numerical validation in `tests/python/test_solver_accuracy.py`

---

## Phase 2: Foundational (Blocking Prerequisites)

**Purpose**: Build-time symbolic matrix representation and symbolic sparse LU lowering engine in Python

**⚠️ CRITICAL**: No user story work can begin until this phase is complete

- [x] T003 [P] [TDD] Implement `SymbolicLUPlan` dataclass in `src/mkpp/model.py` for holding Doolittle sparse $L$, $U$, forward, and backward substitution assignments
- [x] T004 [TDD] Implement `compute_symbolic_lu_decomposition` function in `src/mkpp/lowering.py` using SymPy symbolic Doolittle elimination on $W = \frac{1}{\gamma \Delta t} I - J$
- [x] T005 [TDD] Integrate symbolic LU plan generation into `build_sympy_matrices` in `src/mkpp/lowering.py` and attach to mechanism metadata
- [x] T006 Add build-time zero-pivot and singular matrix exception guards in `src/mkpp/lowering.py`

**Checkpoint**: Symbolic LU lowering engine ready — user story code generation can now proceed

---

## Phase 3: User Story 1 - Build-Time Symbolic LU Factorization & Flat Scalar Inversion (Priority: P1) 🎯 MVP

**Goal**: Generate C++ solver code where matrix inversion ($W^{-1} b$) is fully unrolled into flat, branchless scalar assignments without runtime loops or local stack arrays (`Jac[...]`, `W[...]`)

**Independent Test**: Generate C++ header for Chapman or SAPRC99 mechanism, verify 0 thread-local array allocations (`Jac[10000]`, `W[10000]`) and 0 `for (` loops in linear decomposition/solve routines.

- [x] T007 [P] [US1] [TDD] Create unit test for unrolled symbolic LU scalar emission in `tests/python/test_codegen_symbolic_lu.py`
- [x] T008 [US1] Remove legacy loop-based `lu_decompose` and `lu_solve` template methods from `src/mkpp/codegen.py`
- [x] T009 [US1] Implement flat scalar unrolling emitter for forward ($L y = b$) and backward ($U x = y$) substitution in `src/mkpp/codegen.py`
- [x] T010 [US1] Replace thread-local array declarations (`Jac[10000]`, `W[10000]`, `K1[100]`) in `src/mkpp/codegen.py` with explicitly named scalar double variables (`J_i_j`, `W_i_j`, `K1_i`)
- [x] T011 [US1] [REVIEW] Validate that emitted C++ headers contain 0 stack array allocations and 0 runtime loops for Chapman and SAPRC99 mechanisms using `tests/python/test_codegen_symbolic_lu.py`

**Checkpoint**: User Story 1 (MVP) complete — generated solvers execute matrix solve with zero loops and zero thread-local arrays

---

## Phase 4: User Story 2 - Architecture-Aware View Interfaces & Layout Striding (Priority: P2)

**Goal**: Update solver C++ template function signatures to accept Kokkos subview types (`template <class StateView>`) instead of raw `double*` pointers, adapting to `Kokkos::LayoutLeft` and `Kokkos::LayoutRight`

**Independent Test**: Invoke generated solver functions with 1D Kokkos subviews and verify compilation and numerical equivalence.

- [x] T012 [P] [US2] [TDD] Create view interface contract test in `tests/python/test_codegen_symbolic_lu.py` to verify subview signature generation
- [x] T013 [US2] Update `compute_rates`, `compute_jacobian`, `compute_adjoint`, and `compute_tlm` signatures in `src/mkpp/codegen.py` to use templated `StateView` and `RateView` parameters
- [x] T014 [US2] Update `integrate` signature in `src/mkpp/codegen.py` to `template <class StateView> KOKKOS_INLINE_FUNCTION void integrate(double dt, StateView& state)`
- [x] T015 [US2] Ensure subview indexing syntax (e.g., `state(i)`) is used consistently across generated functions in `src/mkpp/codegen.py` instead of raw pointer indexing (`state[i]`)
- [x] T016 [US2] [REVIEW] Validate zero raw `double*` pointer parameters in generated C++ header signatures using `tests/python/test_codegen_symbolic_lu.py`

**Checkpoint**: User Story 2 complete — solver interface accepts generic subviews across CPU/GPU layouts without raw pointers

---

## Phase 5: User Story 3 - Pure Scalar Register Allocation & Stage Loop Fusion (Priority: P3)

**Goal**: Unroll intermediate Rosenbrock-2 stage updates ($K_1$, $K_2$, $Y_{new}$) and state additions into fused per-species scalar expressions without intermediate loops or state array re-reads

**Independent Test**: Inspect generated headers to verify stage updates and final state updates are unrolled per species into fused scalar statements.

- [x] T017 [P] [US3] [TDD] Create stage update loop fusion test in `tests/python/test_codegen_symbolic_lu.py`
- [x] T018 [US3] Unroll Stage 1 rate evaluation ($F_1$) and $K_1$ forward/backward substitution into scalar register variables in `src/mkpp/codegen.py`
- [x] T019 [US3] Implement fused intermediate state $Y_{new, i} = \text{state}(i) + a_{21} K_{1, i}$ scalar expressions per species in `src/mkpp/codegen.py`
- [x] T020 [US3] Unroll Stage 2 rate evaluation ($F_2$) and $K_2$ forward/backward substitution into scalar register variables in `src/mkpp/codegen.py`
- [x] T021 [US3] Fuse final state update $\text{state}(i) += m_1 K_{1, i} + m_2 K_{2, i}$ into per-species scalar statements in `src/mkpp/codegen.py`
- [x] T022 [US3] [REVIEW] Run end-to-end numerical accuracy verification in `tests/python/test_solver_accuracy.py` comparing generated ROS-2 solver against dense reference integrator ($< 10^{-12}$ relative difference)

**Checkpoint**: User Story 3 complete — stage updates are fully fused per species with exact numerical accuracy

---

## Phase 6: Polish & Cross-Cutting Concerns

**Purpose**: Final documentation updates, guidelines compliance verification, and validation suite execution

- [x] T023 [P] Update user documentation in `docs/` and `README.md` with AOT symbolic LU solver features and subview usage examples
- [x] T024 [P] Verify compliance with NOAA NWS OMD Master Guidelines and EE2 coding standards across `src/mkpp/lowering.py` and `src/mkpp/codegen.py`
- [x] T025 Execute validation steps in `specs/013-aot-symbolic-lu-solver/quickstart.md` and run full pytest suite (`pytest tests/python/`)

---

## Dependencies & Execution Order

### Phase Dependencies

- **Setup (Phase 1)**: Can start immediately
- **Foundational (Phase 2)**: Depends on Setup completion — BLOCKS all user stories
- **User Stories (Phase 3+)**:
  - **User Story 1 (P1)**: Can start after Foundational phase (Phase 2)
  - **User Story 2 (P2)**: Can start after Foundational phase (Phase 2); refines C++ signatures
  - **User Story 3 (P3)**: Can start after User Story 1; unrolls and fuses ROS-2 stage equations
- **Polish (Phase 6)**: Depends on all user story phases being complete

### Parallel Opportunities

- T001 and T002 in Setup can run in parallel
- T003 (data model) and T004 (lowering logic) can run in parallel
- T007 (US1 test) and T012 (US2 test) and T017 (US3 test) can be prepared in parallel
- T023 and T024 in Polish can run in parallel

---

## Extension Hooks

**Optional Hook**: diagram
Command: `/speckit.diagram.dependencies`
Description: Auto-generate dependency DAG after tasks are created

Prompt: Generate task dependency diagram after task breakdown?
To execute: `/speckit.diagram.dependencies`
