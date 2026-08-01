# Tasks: Exaero C++ Host Driver & Mechanism Registry

**Input**: Design documents from `/specs/002-exaero-cpp-driver/`

**Prerequisites**: plan.md (required), spec.md (required for user stories), research.md, data-model.md, contracts/

**Tests**: TDD required by execution strategy

**Organization**: Tasks are grouped by user story to enable independent implementation and testing of each story.

## Format: `[ID] [P?] [Story] Description`

- **[P]**: Can run in parallel (different files, no dependencies)
- **[Story]**: Which user story this task belongs to (e.g., US1, US2, US3)
- Include exact file paths in descriptions

## Phase 1: Setup (Shared Infrastructure)

**Purpose**: Project initialization and basic structure

- [ ] T001 [P] Create CMake library structure for `exaero` in `src/exaero/CMakeLists.txt`
- [ ] T002 [P] Create initial CTest setup for exaero in `src/exaero/tests/CMakeLists.txt`
- [ ] T003 [P] Create dummy headers in `src/exaero/include/exaero/` for api, registry, dispatcher, and sorter

---

## Phase 2: Foundational (Blocking Prerequisites)

**Purpose**: Core infrastructure that MUST be complete before ANY user story can be implemented

**⚠️ CRITICAL**: No user story work can begin until this phase is complete

- [ ] T004 Implement `extern "C"` declarations and Host Integration API in `src/exaero/include/exaero/api.hpp` matching `host_integration_api.md`
- [ ] T005 Implement `ExaeroContext` and `UnmanagedDeviceState` zero-copy bindings in `src/exaero/include/exaero/state.hpp` based on `data-model.md`
- [ ] T006 Write tests for `ExaeroContext` instantiation and zero-allocation view bindings in `src/exaero/tests/test_state.cpp`

**Checkpoint**: Foundation ready - user story implementation can now begin in parallel

---

## Phase 3: User Story 2 - Modular Pre-generated Mechanism Registry (Priority: P1) 🎯 MVP

**Goal**: Support a library of pre-generated, optional mechanism headers alongside the ability to link new configurations dynamically.

**Independent Test**: The `test_registry` binary asserts that requesting "ChapmanCycle" maps successfully to a Kokkos functor, while an unregistered name throws an explicit error and fails fast.

### Tests for User Story 2 (MANDATORY - blocks implementation) ⚠️

- [ ] T007 [P] [US2] Write registry resolution tests in `src/exaero/tests/test_registry.cpp` verifying successful dispatch and fast-failing behavior

### Implementation for User Story 2

- [ ] T008 [US2] Define registry CMake injection flag (`-DEXAERO_MECHANISMS`) and auto-generate the switchboard in `src/exaero/CMakeLists.txt`
- [ ] T009 [US2] Implement Registry pattern in `src/exaero/src/registry.cpp` and `src/exaero/include/exaero/registry.hpp` to route string identifiers to C++ functor targets

**Checkpoint**: At this point, the Registry should be fully functional and testable independently. (US2 prioritized over US1 because dispatch depends on registry mapping).

---

## Phase 4: User Story 1 - Kokkos Execution and Multi-Rate Dispatch (Priority: P1)

**Goal**: Ingest the block-sparse Kokkos C++ headers and execute them using hierarchical parallelism with persistent, dynamically SZA-sorted grid cells.

**Independent Test**: The `test_sorter` confirms persistent scratch buffers are allocated once and never re-allocated. The `test_dispatcher` confirms SZA-sorted thread teams execute the correct explicit/implicit pathways.

### Tests for User Story 1 (MANDATORY - blocks implementation) ⚠️

- [ ] T010 [P] [US1] Write SZA sorting algorithm tests verifying zero allocations during sort in `src/exaero/tests/test_sorter.cpp`
- [ ] T011 [P] [US1] Write Kokkos TeamPolicy dispatch tests in `src/exaero/tests/test_dispatcher.cpp` checking perfectly balanced workload chunks

### Implementation for User Story 1

- [ ] T012 [P] [US1] Implement persistent `Kokkos::View` index mapping and sorting logic in `src/exaero/src/sorter.cpp`
- [ ] T013 [US1] Implement `TeamPolicy` dispatcher inside `src/exaero/src/dispatcher.cpp` to launch the hierarchical multi-rate kernel (depends on `sorter.cpp`)
- [ ] T014 [US1] Wire the full execution chain in `src/exaero/src/api.cpp`: `exaero_solve` -> Sorter -> Registry -> Dispatcher

**Checkpoint**: At this point, User Stories 1 AND 2 should both work independently.

---

## Phase 5: Polish & Cross-Cutting Concerns

- [ ] T015 Verify zero-copy alignment (`Kokkos::LayoutLeft`) across the entire execution loop.
- [ ] T016 Run comprehensive memory profiling (`test_sorter` and `test_dispatcher`) asserting 0 bytes of dynamic allocation during timestep execution (SC-003).

## Dependencies & Execution Order

### Phase Dependencies
- **Setup (Phase 1)**: Can start immediately.
- **Foundational (Phase 2)**: Depends on Setup completion.
- **User Story 2 (Phase 3)**: Depends on Foundational completion.
- **User Story 1 (Phase 4)**: Depends on User Story 2 completion.
- **Polish (Phase 5)**: Depends on all stories.
