# Implementation Plan: Exaero Auxiliary Engines

**Branch**: `003-exaero-auxiliary-engines` | **Date**: 2026-08-01 | **Spec**: [spec.md](spec.md)
**Input**: Feature specification from `specs/003-exaero-auxiliary-engines/spec.md`

## Summary

Extend the Exaero C++ Utility to conditionally compile and dispatch preexisting Fortran/C++ mechanisms (`Cloud-J` for Photolysis and `ISORROPIA-Lite` for Inorganic Thermodynamics) as optional auxiliary engines. This must be done via CMake configuration while maintaining zero-copy data views (CON-002) and strict GPU load balancing via hierarchical parallelism (CON-001).

## Technical Context

**Language/Version**: C++23, Fortran 2008+, CMake 3.20+
**Primary Dependencies**: Kokkos, Cloud-J (Fortran), ISORROPIA-Lite (C++/Fortran)
**Storage**: N/A
**Testing**: CMake CTest, GoogleTest (C++ driver tests)
**Target Platform**: Linux HPC clusters, GPUs (NVIDIA/AMD)
**Project Type**: C++ utility / driver application
**Performance Goals**: >80% GPU efficiency, zero-copy memory overhead, no thread starvation
**Constraints**:
- **CON-001**: TeamPolicy divergence (must use Kokkos hierarchical parallelism, avoid warp divergence)
- **CON-002**: LayoutLeft interoperability (zero-copy handshakes using column-major mapping)

## Constitution Check

*GATE: Must pass before proceeding. Re-check after design phase.*

| Principle | Status | Notes |
|-----------|--------|-------|
| CON-001: TeamPolicy divergence | PASS | Will use `Kokkos::TeamPolicy` and `Kokkos::TeamThreadRange` for GPU load balancing; no heavy if/else branches for phase conditions. |
| CON-002: LayoutLeft interoperability | PASS | C++23 `std::mdspan` or `Kokkos::MemoryUnmanaged` with `layout_left` will be used for C++ to Fortran data handoff. |
| Conditional Compilation (FR-001, FR-002) | PASS | CMake options will toggle auxiliary engines and substitute identity operations when disabled. |

## Project Structure

### Documentation (this feature)

```text
specs/003-exaero-auxiliary-engines/
├── spec.md              # Feature specification
├── plan.md              # This file
├── research.md          # Technical unknowns & decisions
├── data-model.md        # Key entities and state transitions
├── contracts/           # Interface contracts for engine dispatch
│   └── engine-dispatch.md
└── quickstart.md        # Validation guide
```

### Source Code (repository root)

```text
src/
├── exaero/
│   ├── CMakeLists.txt              # CMake configuration for Exaero
│   ├── include/
│   │   └── auxiliary_engines.hpp   # C++ driver wrappers and dummy handlers
│   └── src/
│       └── auxiliary_engines.cpp   # Zero-copy dispatch implementations
```

**Structure Decision**: Add lightweight C++ wrappers in the `exaero` source tree to conditionally link against the external `Cloud-J` and `ISORROPIA-Lite` source trees existing in the `src/` directory.

## Execution Strategy

### TDD Requirements

- [x] Engine Dispatch Wrapper: Needs unit testing to verify that identity/dummy operations are executed when engines are compiled out, and that memory is correctly mapped using `layout_left`.

### Parallel Execution Opportunities

- [x] CMake build script modifications can be done independently of the C++ hierarchical parallelism dispatch logic.

### Human Checkpoints
- Review CMake options and linkage.
- Review Kokkos memory layouts to confirm zero-copy C++/Fortran mapping.
