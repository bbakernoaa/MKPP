# Implementation Plan: Exaero C++ Utility & Mechanism Registry

**Goal:** Build the native C++ execution layer (`exaero`) that dynamically registers, links, and dispatches the MKPP AOT-generated block-sparse Kokkos C++ headers over a 3D host grid. Ensure workloads are dynamically load-balanced via a Solar Zenith Angle (SZA) sorter, using persistent `Kokkos::MemoryUnmanaged` Views for zero-copy coupling to external host environments (e.g., Fortran UFS/CMAQ wrappers). `exaero` acts as a shared utility that can be utilized by both the Host Model and MKPP as needed, providing physical diagnostics, sorting, and structural abstractions.

**Architecture:** The utility lives in `src/exaero/`. It implements a Factory/Registry pattern to map configuration strings to specific generated kernels at runtime. It implements a core `TeamPolicy Dispatcher` that evaluates a dedicated SZA array to partition the global grid into balanced Kokkos thread blocks before calling the chemistry solver.

**Tech Stack:** C++23, Kokkos, CMake 3.24, CTest (with optionally compiled Python-generated fixtures from MKPP).

## Global Constraints

- `System MUST strictly adhere to Kokkos::TeamPolicy and Kokkos::TeamThreadRange to prevent warp divergence.`
- `System MUST guarantee zero-copy data interoperability using Fortran-compatible LayoutLeft unmanaged views.`
- `System MUST fail fast and loudly during module initialization if a requested mechanism is not present in the linked registry.`
- `The build system (CMake) MUST provide flags to conditionally compile specific pre-generated mechanisms directly into the main static/shared library.`
- `The utility MUST allocate persistent Kokkos views once during initialization for any sorting/scratch buffers, and reuse them at every timestep to avoid dynamic memory allocation overhead.`
- `Code inside this repository... Zero dead code allowed.`
- `Never use switch/case or heavy if/else logic for evaluating thermodynamic phase branches inside Kokkos kernels to prevent warp divergence.`

## Summary

The `exaero` C++ utility bridges the gap between the host Fortran models (which own the actual physical grid data) and the high-performance Kokkos solvers emitted by the MKPP AOT Python compiler. Because `exaero` is a shared utility, it can be invoked by the host model to manage zero-copy inputs, or called by MKPP components to access physical abstractions (like cloud optical diagnostics). It provides an `extern "C"` Fortran-compatible entry point, allocates minimal persistent scratch spaces for sorting overhead, and manages the intelligent execution dispatch (grouping stiff and non-stiff computational domains) to perfectly load-balance the GPU via `Kokkos::TeamPolicy`. Pre-generated mechanisms (like Chapman or CRACMM) are compiled into a static library via CMake configuration flags and invoked dynamically via a lightweight Registry class.

## Technical Context

**Language/Version**: C++23, Kokkos, CMake 3.24
**Primary Dependencies**: Kokkos Core, AOT MKPP Generated Headers (`.hpp`)
**Storage**: In-memory. Persistent Kokkos Device Views are allocated once for scratch space; all other memory maps directly back to the Host model (`MemoryUnmanaged`).
**Testing**: CTest testing the C++ logic using dummy input arrays and verified analytical test mechanism outputs.
**Target Platform**: GPU-accelerated Linux HPC (NVIDIA, AMD). Local verification on MacOS (CPU Kokkos backend).
**Project Type**: Native C++ Static Library / `extern "C"` Interface
**Performance Goals**: 0-byte dynamic memory allocation per timestep. >90% reduction in terminator wait starvation via TeamPolicy SZA sorting.
**Constraints**: The host controls the `Kokkos::initialize()` boundary; Exaero must not initialize Kokkos itself.

## Constitution Check

*GATE: Must pass before proceeding. Re-check after design phase.*

| Principle | Status | Notes |
|-----------|--------|-------|
| Clarity Over Cleverness | PASS | The registry pattern will be flat and explicitly mapped, avoiding dynamic `dlopen` trickery. |
| Defensive Programming | PASS | The registry explicitly checks if the string maps to a linked target and aborts loudly otherwise. |
| Fail Fast, Fail Loudly | PASS | Runtime registry failures or incorrect layout ranks from the host map directly to fatal crashes. |
| High-Performance HPC & MPI | PASS | The utility operates entirely on sub-communicators or local grid blocks without triggering root-rank gathers. |
| GPU Acceleration & Kokkos | PASS | The sorting logic is designed strictly for `Kokkos::TeamPolicy` utilization. |
| Zero-Copy Data Interoperability | PASS | Uses `Kokkos::View<..., Kokkos::LayoutLeft, Kokkos::MemoryUnmanaged>` internally. |
| Scientific Hygiene & Determinism | PASS | C++ logic defers scientific execution entirely to the deterministically generated MKPP headers. |

## Project Structure

### Documentation (this feature)

```text
specs/002-exaero-cpp-utility/
├── spec.md
├── plan.md
├── research.md
├── data-model.md
├── quickstart.md
└── contracts/
    └── host_integration_api.md
```

### Source Code

```text
src/
└── exaero/
    ├── CMakeLists.txt
    ├── include/
    │   └── exaero/
    │       ├── api.hpp
    │       ├── dispatcher.hpp
    │       ├── registry.hpp
    │       └── sorter.hpp
    ├── src/
    │   ├── api.cpp
    │   ├── dispatcher.cpp
    │   ├── registry.cpp
    │   └── sorter.cpp
    └── tests/
        ├── CMakeLists.txt
        ├── test_registry.cpp
        ├── test_sorter.cpp
        └── test_dispatcher.cpp
```

## Execution Strategy

### TDD Requirements
- [ ] `registry.cpp`: Test that requesting a registered mechanism returns the correct functor, and requesting an unregistered one throws an explicit runtime error.
- [ ] `sorter.cpp`: Test that persistent scratch buffers are correctly allocated once, and that an input array of SZA values is successfully grouped into contiguous execution blocks.
- [ ] `dispatcher.cpp`: Test that the dispatcher successfully invokes a mock Kokkos mechanism header using `Kokkos::TeamPolicy` without memory allocations during the integration loop.

### Parallel Execution Opportunities
- [ ] The `registry.cpp` (mapping string keys to C++ templates) can be built independently of the `sorter.cpp` (Kokkos index manipulation algorithm).
- [ ] CMake configuration (flag integration for mechanisms) can be scaffolded immediately.

### Human Checkpoints
1. After defining the `extern "C"` `api.hpp`, verify that the data signatures correctly match Fortran `ISO_C_BINDING` capabilities.
2. After writing the `sorter.cpp` logic, verify via the Kokkos memory tracking macros that zero allocations happen after initialization.

### Review Gates
- [ ] `registry.hpp` and `api.hpp`: review before implementation to ensure C++23 constraints don't violate C-bindings.
- [ ] `CMakeLists.txt`: review before finalizing to guarantee that mechanism inclusion flags correctly handle missing MKPP generation.

## Complexity Tracking

> No exceptions to the constitution requested. SZA Sorting algorithm may be algorithmically complex, but will be encapsulated behind `sorter.hpp`.
