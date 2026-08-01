---
description: "Task list for Exaero Auxiliary Engines implementation"
---

# Tasks: Exaero Auxiliary Engines

**Input**: Design documents from `specs/003-exaero-auxiliary-engines/`
**Prerequisites**: plan.md (required), spec.md (required for user stories), contracts/engine-dispatch.md

## Task Format

```
[ID] [markers] [Story] Description
```

**Markers**:
- **[P]**: Can run in parallel (different files, no dependencies)
- **[TDD]**: Must follow RED-GREEN-REFACTOR (write test → fail → implement → pass → refactor)
- **[REVIEW]**: Requires code review before proceeding to next task
- **[SUBAGENT]**: Can be delegated to a subagent for parallel execution

**Story labels**: `[US1]`, `[US2]`, `[US3]` map tasks to user stories for traceability.

## Phase 1: Setup (Shared Infrastructure)

**Purpose**: Project initialization and basic structure

- [ ] T001 Create wrapper files in `src/exaero/include/auxiliary_engines.hpp` and `src/exaero/src/auxiliary_engines.cpp`

**Execution notes**: Setup the placeholder files before CMake configuration.

---

## Phase 2: Foundational (Blocking Prerequisites)

**Purpose**: Core infrastructure that MUST be complete before ANY user story

- [ ] T002 [TDD] Create test skeleton in `src/exaero/tests/test_auxiliary_engines.cpp` and register it in `src/exaero/CMakeLists.txt`

**Checkpoint**: Foundation ready. Proceed to User Stories.

---

## Phase 3: User Story 1 - Optional Compilation via CMake (Priority: P1) MVP

**Goal**: Conditionally compile Cloud-J and ISORROPIA-Lite into Exaero via CMake flags.
**Independent Test**: Run CMake with varying flag combinations and verify successful compilation/linking.

### Implementation for User Story 1

- [ ] T003 [US1] Add `EXAERO_WITH_CLOUDJ` and `EXAERO_WITH_ISORROPIALITE` options to `src/exaero/CMakeLists.txt`
- [ ] T004 [US1] Update `src/exaero/CMakeLists.txt` to enable device-linkage configuration (e.g., CUDA_SEPARABLE_COMPILATION) for Fortran compatibility and  `src/exaero/CMakeLists.txt` to conditionally `add_subdirectory` and `target_link_libraries` for `Cloud-J`
- [ ] T005 [P] [US1] Update `src/exaero/CMakeLists.txt` to conditionally `add_subdirectory` and `target_link_libraries` for `isorropialite`
- [ ] T006 [US1] Add compile definitions (`-DEXAERO_WITH_CLOUDJ`, `-DEXAERO_WITH_ISORROPIALITE`) to the Exaero target based on flags in `src/exaero/CMakeLists.txt`

**Checkpoint**: User Story 1 fully functional. CMake configuration works.

---

## Phase 4: User Story 2 - Zero-Copy Dispatch to Fortran Engines (Priority: P1)

**Goal**: Dispatch calculations using zero-copy memory handshakes and Fortran API contracts.
**Independent Test**: Profile memory allocations during simulation step to ensure zero redundant copies at C++/Fortran boundary.

### Tests for User Story 2

- [ ] T007 [P] [TDD] [US2] Write unit tests in `src/exaero/tests/test_auxiliary_engines.cpp` verifying zero-copy view configurations (`layout_left`, unmanaged) and dummy ops

### Implementation for User Story 2

- [ ] T008 [US2] Declare `extern "C"` interfaces for Fortran drivers in `src/exaero/src/auxiliary_engines.cpp`
- [ ] T009 [US2] Implement C++ zero-copy dispatch wrappers extracting `.data()` and passing extents explicitly to Fortran `bind(c)` boundaries using unmanaged `layout_left` Kokkos views in `src/exaero/include/auxiliary_engines.hpp`
- [ ] T010 [P] [US2] Implement preprocessor conditionals (`#ifdef EXAERO_WITH_CLOUDJ`, etc.) to execute Fortran calls or dummy pass-throughs in `src/exaero/src/auxiliary_engines.cpp`

**Checkpoint**: User Story 2 fully functional. Fortran linkage and dummy pass-throughs work.

---

## Phase 5: User Story 3 - GPU Load Balanced Execution (Priority: P2)

**Goal**: Execute on GPUs using balanced workloads without warp divergence.
**Independent Test**: Profile GPU execution to verify thread occupancy and hierarchical parallelism.

### Implementation for User Story 3

- [ ] T011 [US3] Wrap dispatch invocations in `Kokkos::TeamPolicy` parallel regions inside `src/exaero/src/auxiliary_engines.cpp`
- [ ] T012 [US3] Use `Kokkos::TeamThreadRange` within the dispatch logic to distribute cell calculations without starvation in `src/exaero/src/auxiliary_engines.cpp`

**Checkpoint**: User Story 3 fully functional. GPU parallelism is correctly implemented.

---

## Phase 6: Polish & Cross-Cutting Concerns

**Purpose**: Improvements that affect multiple user stories

- [ ] T013 [P] [SUBAGENT] Update `src/exaero/README.md` with new auxiliary engine CMake flags documentation
- [ ] T014 [REVIEW] Review zero-copy and hierarchical parallel logic in `src/exaero/src/auxiliary_engines.cpp` against CON-001 and CON-002 constraints
- [ ] T015 Run full CTest suite in `build/` to verify baseline integrations match

---

## Dependencies & Execution Order

### Phase Dependencies

- **Setup (Phase 1)**: No dependencies — start immediately
- **Foundational (Phase 2)**: Depends on Setup — BLOCKS all user stories
- **User Stories (Phase 3+)**: All depend on Foundational completion
- **Polish (Final Phase)**: Depends on all desired user stories being complete

### Parallel Opportunities

- CMake logic for ISORROPIA (T005) can be developed in parallel with Cloud-J CMake logic (T004)
- Zero-copy view unit tests (T007) can be written independently before wrapper implementation
- Preprocessor conditionals (T010) can be added independently to the dispatch implementation
- [ ] T016 Write E2E integration tests comparing MKPP's dispatched outputs against standalone engine baselines (SC-004).
- [ ] T017 Implement pre-dispatch validation checks for `NaN`/`Inf` conditions on incoming arrays.
- [ ] T018 Profile the compiled executable with Nsight Compute / HPCToolkit to assert 0-byte memory allocation overhead and >80% GPU warp efficiency.
