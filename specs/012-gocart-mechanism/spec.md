# Feature Specification: GOCART Mechanism

**Feature Branch**: `gocart-mechanism`

**Created**: 2026-08-02

**Status**: Draft

**Input**: User description: "I want to build the GOCART mechanism. create it in #file:mechanisms https://github.com/GEOS-ESM/GOCART/blob/9ff3df9545dd582f415f682d3297e8c6c841e5cb/Process_Library/GOCART2G_Process.F90#L755-L766 this will help us test all of the reaction types"

## User Scenarios & Testing *(mandatory)*

### User Story 1 - Mechanism Compilation (Priority: P1)

As an atmospheric scientist, I want to define the GOCART mechanism in an OpenAtmos YAML format so that I can compile it into solver code using the MKPP engine.

**Why this priority**: Without the YAML definition, the MKPP engine cannot process the GOCART mechanism. It forms the foundational input for the solver pipeline.

**Independent Test**: Can be tested by running the MKPP YAML parser on `mechanisms/gocart.yaml` and verifying it parses without errors.

**Acceptance Scenarios**:

1. **Given** a complete `gocart.yaml` file in the `mechanisms/` directory, **When** the MKPP parser reads the file, **Then** all species and reactions are successfully loaded.
2. **Given** the GOCART YAML definition containing various reaction types, **When** the parser processes the reactions, **Then** the appropriate mathematical abstractions (like SymPy symbolic expressions) are created correctly.

---

### User Story 2 - Reaction Type Verification (Priority: P2)

As a framework developer, I want the GOCART mechanism to utilize all supported reaction types so that I can verify that the MKPP codebase handles complex, multiphase chemical and physical processes simultaneously without operator splitting.

**Why this priority**: Testing all chemical reaction types (gas phase, heterogeneous, gas-to-particle) while strictly excluding emissions ensures the robustness and proper scope boundaries of the Unified Jacobian.

**Independent Test**: Can be tested by executing the MKPP code generator on the GOCART mechanism and ensuring that the emitted solver libraries contain the exact Jacobian entries for every chemical reaction type, and no emission terms.

**Acceptance Scenarios**:

1. **Given** the GOCART mechanism focusing on chemical and heterogeneous processes, **When** MKPP builds the Unified Jacobian, **Then** it processes these reactions without including any out-of-scope emission or saltation terms.
2. **Given** the generated solver libraries, **When** compiled within the CATChem host driver, **Then** the compilation completes without register pressure overflows.

### Edge Cases

- What happens when a specific chemical reaction type required by GOCART is not natively supported by the standard OpenAtmos schema?
- How does the system ensure emission-related variables are explicitly rejected if inadvertently included in the YAML?

## Clarifications

### Session 2026-08-02
- Q: How should the GOCART saltation flux and threshold velocity calculations be represented in the OpenAtmos YAML schema since they are not standard chemical kinetic reactions? → A: MKPP should only handle CHEMISTRY/GAS->particle/HETEROGENEOUS chemistry. Saltation or emissions are entirely out of scope even passing the flux to MKPP.

## Requirements *(mandatory)*

### Functional Requirements

- **FR-001**: System MUST provide a new `gocart.yaml` file inside the `mechanisms/` directory.
- **FR-002**: The `gocart.yaml` MUST define all primary GOCART species (e.g., Dust bins, Sea Salt, Sulfate, organic carbon, black carbon).
- **FR-003**: The `gocart.yaml` MUST exclusively define chemical kinetics (gas-phase, gas-to-particle, heterogeneous) and MUST NOT include dust emissions or saltation fluxes.
- **FR-004**: The mechanism MUST test the MKPP parser and compiler against all distinct in-scope reaction types (Arrhenius, Heterogeneous, First-Order/Aging). Photolysis may be included if explicitly defined by GOCART.
- **FR-005**: GOCART saltation flux calculations and emissions are strictly out of scope for MKPP. These processes must be handled entirely by the host model and MUST NOT be passed into or evaluated by MKPP.

### Key Entities

- **GOCART Species**: Dust (various size bins), Sea Salt (various size bins), Sulfate precursors ($SO_2$, DMS), Sulfate aerosol, Black Carbon, Organic Carbon.

## Success Criteria *(mandatory)*

### Measurable Outcomes

- **SC-001**: The `gocart.yaml` file parses 100% successfully using the existing MKPP parser.
- **SC-002**: The MKPP engine successfully generates `gocart.hpp` and `gocart_reduced.hpp` solver routines from the YAML without compilation errors.
- **SC-003**: The generated solver routines successfully model the chemical and phase-transfer kinetics of GOCART, and pass an automated verification script proving no emission or saltation terms exist in the output.

## Assumptions

- We assume the existing MKPP OpenAtmos YAML parser supports all necessary representations for GOCART's purely chemical and heterogeneous reactions.
- We assume that external physical variables not related to emissions (like Temperature, RH) needed for the GOCART chemistry will be provided to the solver via the Exaero interface or `METEO_STRUCT`.
