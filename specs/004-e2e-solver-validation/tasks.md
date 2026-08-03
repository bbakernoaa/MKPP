---
description: "Task list for E2E Solver Validation & Baseline Testing"
---

# Tasks: E2E Solver Validation & Baseline Testing

**Input**: Design documents from `specs/004-e2e-solver-validation/`
**Prerequisites**: plan.md (required), spec.md (required for user stories)

## Task Format

```
[ID] [markers] [Story] Description
```

**Markers**:
- **[P]**: Can run in parallel (different files, no dependencies)
- **[TDD]**: Must follow RED-GREEN-REFACTOR (write test → fail → implement → pass → refactor)
- **[REVIEW]**: Requires code review before proceeding to next task
- **[SUBAGENT]**: Can be delegated to a subagent for parallel execution

**Story labels**: `[US1]`, `[US2]` map tasks to user stories for traceability.

## Phase 1: Setup (Shared Infrastructure)

**Purpose**: Project initialization and basic structure

- [x] T001 Create directory structure `tests/integration/e2e_validation/data/` and placeholder data files `chapman.yaml`, `kpp_baseline_chapman.csv`
- [x] T002 Add `CMakeLists.txt` in `tests/integration/e2e_validation` with executable configuration

**Execution notes**: Ensure directory structure exists.

---

## Phase 2: Foundational (Blocking Prerequisites)

**Purpose**: Core infrastructure that MUST be complete before ANY user story

**CRITICAL**: No user story work can begin until this phase is complete.

- [x] T003 [P] [TDD] Implement python baseline comparator script in `tests/integration/e2e_validation/compare_baselines.py`
- [x] T004 [P] Create C++ skeleton harness in `tests/integration/e2e_validation/test_e2e_chapman.cpp` with Kokkos initialization and GoogleTest integration
- [x] T005 Update `tests/CMakeLists.txt` to include the `e2e_validation` subdirectory

**Checkpoint**: Foundation ready. Python testing scripts and C++ boilerplate available.

---

## Phase 3: User Story 1 - AOT Generation Verification (Priority: P1) MVP

**Goal**: Ingest Chapman Cycle mechanism using MKPP AOT compiler and verify C++ Kokkos headers and Jacobian sparsity against KPP output.
**Independent Test**: Execute the MKPP Python parser on a legacy `.eqn` mechanism and diff the non-zero sparsity pattern against traditional KPP.

### Tests for User Story 1 (if TDD applies)

- [x] T006 [TDD] [US1] Write python test in `tests/integration/e2e_validation/test_mkpp_generation.py` to execute `mkpp parse` and verify `ChapmanCycle.hpp` generation

### Implementation for User Story 1

- [ ] T007 [P] [US1] Fill `tests/integration/e2e_validation/data/chapman.yaml` with valid legacy Chapman cycle KPP format equations
- [x] T008 [P] [US1] Fill `tests/integration/e2e_validation/data/kpp_baseline_chapman.csv` with expected sparsity pattern and concentration results
- [x] T009 [US1] Implement sparsity pattern and Jacobian matrix value verification in `tests/integration/e2e_validation/compare_baselines.py` parsing the generated AOT headers and evaluating at a test state

**Checkpoint**: User Story 1 fully functional and testable. AOT compiler successfully generates headers that match baseline structural sparsity.

---

## Phase 4: User Story 2 - Solver Integration Accuracy (Priority: P1)

**Goal**: Run Exaero host utility using the MKPP-generated headers to compare integrated chemical concentrations against standalone KPP Fortran baseline.
**Independent Test**: Calculate RMSE between C++ and Fortran concentration outputs.

### Tests for User Story 2 (if TDD applies)

- [x] T010 [TDD] [US2] Add Kokkos::Profiling::space_allocate hooks inside `tests/integration/e2e_validation/test_e2e_chapman.cpp` to assert 0-byte dynamic allocations

### Implementation for User Story 2

- [x] T011 [US2] Implement C++ box-model integration loop (Rosenbrock solver) in `tests/integration/e2e_validation/test_e2e_chapman.cpp` utilizing `ChapmanCycle.hpp`, unmanaged LayoutLeft views, and `Kokkos::TeamPolicy` hierarchical dispatch
- [x] T012 [US2] Implement CSV writing logic in `tests/integration/e2e_validation/test_e2e_chapman.cpp` to output `exaero_output.csv`
- [x] T013 [US2] Expand `tests/integration/e2e_validation/compare_baselines.py` to compare final concentrations (ATOL 1e-12, RTOL 1e-6)
- [x] T014 [US2] Create CTest definition in `tests/integration/e2e_validation/CMakeLists.txt` that chains the C++ runner and Python comparison script

**Checkpoint**: User Stories 1 AND 2 both work independently. E2E solver accuracy verified without memory overhead.

---

## Phase 5: Polish & Cross-Cutting Concerns

**Purpose**: Improvements that affect multiple user stories

- [x] T015 [REVIEW] Run full CTest suite locally to ensure E2E validation does not break other components

---

## Dependencies & Execution Order

### Phase Dependencies

- **Setup (Phase 1)**: No dependencies — start immediately
- **Foundational (Phase 2)**: Depends on Setup — BLOCKS all user stories
- **User Stories (Phase 3+)**: All depend on Foundational completion
- **Polish (Final Phase)**: Depends on all desired user stories being complete

### Parallel Opportunities

- Python comparator (T003) and C++ test harness (T004) can run in parallel.
- Setting up the test data `.eqn` and `.csv` files (T007, T008) can run in parallel.
