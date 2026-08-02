# Tasks: GOCART Mechanism

**Input**: Design documents from `specs/012-gocart-mechanism/`
**Prerequisites**: plan.md (required), spec.md (required for user stories)

## Phase 1: Setup (Shared Infrastructure)

**Purpose**: Project initialization and basic structure

- [X] T001 Initialize the GOCART mechanism definition file in `mechanisms/gocart.yaml`

**Execution notes**: No special discipline required. Verify file creation before proceeding.

---

## Phase 2: Foundational (Blocking Prerequisites)

**Purpose**: Core infrastructure that MUST be complete before ANY user story

**CRITICAL**: No user story work can begin until this phase is complete.

- [X] T002 Define all GOCART species (gases, sulfate aerosols, dust bins, sea salt bins, OC, BC) in `mechanisms/gocart.yaml`
- [X] T003 Ensure the OpenAtmos mechanism host interface arrays are defined in `mechanisms/gocart.yaml`

**Checkpoint**: Foundation ready. Get human approval before starting user stories.

---

## Phase 3: User Story 1 - Mechanism Compilation (Priority: P1)

**Goal**: Define the GOCART mechanism in an OpenAtmos YAML format so that I can compile it into solver code using the MKPP engine.
**Independent Test**: Can be tested by running the MKPP YAML parser on `mechanisms/gocart.yaml` and verifying it parses without errors.

### Implementation for User Story 1

- [X] T004 [US1] Add gas-phase chemical reactions (DMS and SO2 oxidation) to `mechanisms/gocart.yaml`
- [X] T005 [US1] Add aqueous/heterogeneous oxidation reactions to `mechanisms/gocart.yaml`
- [X] T006 [US1] Add aging (first-order) phase-transfer reactions for Black Carbon and Organic Carbon to `mechanisms/gocart.yaml`
- [X] T007 [US1] [REVIEW] Verify that no emission or saltation fluxes are included in `mechanisms/gocart.yaml`
- [X] T008 [US1] Run MKPP parser `PYTHONPATH=src python3 -m mkpp.cli compile mechanisms/gocart.yaml --test-env tests/integration/e2e_validation/data/env.yaml` to validate the mechanism definition

**Checkpoint**: User Story 1 fully functional and testable. Get human approval.

---

## Phase 4: User Story 2 - Reaction Type Verification (Priority: P2)

**Goal**: Utilize all supported reaction types so that I can verify that the MKPP codebase handles complex, multiphase chemical and physical processes simultaneously without operator splitting.
**Independent Test**: Can be tested by executing the MKPP code generator on the GOCART mechanism and ensuring that the emitted solver libraries contain the exact Jacobian entries for every chemical reaction type, and no emission terms.

### Implementation for User Story 2

- [X] T008b [US1] (Optional if applicable) Add Photolysis reactions if GOCART defines them, otherwise document their intentional omission in the YAML.
- [X] T009 [US2] Generate C++ solver code using `PYTHONPATH=src python3 -m mkpp.cli compile mechanisms/gocart.yaml --test-env tests/integration/e2e_validation/data/env.yaml --out mkpp-generated/`
- [X] T010 [US2] Write and execute a test script (`verify_no_emissions.py`) to parse `mkpp-generated/gocart.hpp` and assert no emission-related terms (e.g., saltation, threshold velocity) exist
- [X] T011 [US2] Compile the generated headers with the mock C++ host driver in the `build/` directory

**Checkpoint**: User Stories 1 AND 2 both work independently. Get human approval.

---

## Phase 5: Polish & Cross-Cutting Concerns

**Purpose**: Improvements that affect multiple user stories

- [X] T012 Run full test suite — all tests must pass
- [X] T013 Update documentation and README if necessary

**Execution notes**: All tests must pass before this phase is considered complete.

---

## Dependencies & Execution Order

### Phase Dependencies

- **Setup (Phase 1)**: No dependencies — start immediately
- **Foundational (Phase 2)**: Depends on Setup — BLOCKS all user stories
- **User Stories (Phase 3+)**: All depend on Foundational completion
  - Stories can proceed in parallel (if using subagents) or sequentially by priority
- **Polish (Final Phase)**: Depends on all desired user stories being complete

### Within Each User Story

1. Tests (if [TDD]) MUST be written and FAIL before implementation
2. Models before services
3. Services before endpoints
4. Core implementation before integration
5. [REVIEW] tasks pause for human review
6. Story complete before moving to next priority
