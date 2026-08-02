# Implementation Plan: GOCART Mechanism

**Branch**: `gocart-mechanism` | **Date**: 2026-08-02 | **Spec**: [spec.md](spec.md)

## Summary

Build the GOCART mechanism definition in `mechanisms/gocart.yaml` targeting the OpenAtmos schema, strictly limited to chemical and phase-transfer kinetics (excluding emissions), and compile it into Kokkos C++ headers using the MKPP engine.

## Technical Context

**Language/Version**: Python 3.11+ (MKPP Frontend), C++23 (Kokkos Backend)
**Primary Dependencies**: OpenAtmos Schema, SymPy, Kokkos
**Storage**: N/A
**Testing**: YAML validation via MKPP parser, C++ compilation
**Target Platform**: Linux HPC
**Project Type**: Mechanism definition (YAML) and Code Generation
**Performance Goals**: Maximize GPU register reuse; branchless Jacobian evaluation
**Constraints**: Zero emissions or saltation fluxes within the mechanism definition. Host passes meteorological fields directly.

## Constitution Check

*GATE: Must pass before proceeding. Re-check after design phase.*

| Principle | Status | Notes |
|-----------|--------|-------|
| Clarity Over Cleverness | PASS | The YAML will use standard OpenAtmos conventions. |
| Strict Separation of Concerns | PASS | Emissions are explicitly decoupled as per user instruction. |
| Unified Jacobian & No Operator Splitting | PASS | All chemical reactions (gas-phase, heterogeneous) will be evaluated in the single block-sparse Jacobian. |

## Project Structure

### Documentation (this feature)

```text
specs/012-gocart-mechanism/
├── spec.md              # Feature specification
├── plan.md              # This file
├── research.md          # Domain and scoping decisions
├── data-model.md        # Mechanism entities
├── quickstart.md        # Validation guide
├── contracts/           # Interface definitions
└── checklists/          # Validation checklists
```

### Source Code (repository root)

```text
mechanisms/
└── gocart.yaml          # The mechanism definition file
mkpp-generated/
├── gocart.hpp           # Generated unreduced solver header
└── gocart_reduced.hpp   # Generated reduced solver header
```

**Structure Decision**: The YAML file will be placed in the `mechanisms/` directory alongside existing mechanisms (e.g., `chapman.yaml`), following the repository standard.

## Execution Strategy

### TDD Requirements

- [ ] **YAML Parsing**: Ensure the parser accepts the new mechanism without errors before generating code.
- [ ] **Generated Header Compilation**: Ensure `gocart.hpp` compiles flawlessly with Kokkos.

### Parallel Execution Opportunities

- N/A (Linear process: Create YAML -> Parse -> Generate Code -> Compile)

### Human Checkpoints

1. After generating the YAML, verify the species and reaction completeness.
2. Before merge, review the emitted C++ code to ensure no emission logic has been accidentally mapped.

### Review Gates

- [ ] **Mechanism Definition**: Domain experts should review the kinetic rates and species phases in `gocart.yaml`.
