# Feature Specification: Exaero Auxiliary Engines

**Feature Branch**: `[###-feature-name]`

**Created**: 2026-08-01

**Status**: Draft

**Input**: User description: "Create the specification for extending the Exaero C++ Utility (in a new feature directory `specs/003-exaero-auxiliary-engines`) to integrate preexisting Fortran/C++ mechanisms (specifically `Cloud-J` for Photolysis Forcing and `ISORROPIA-Lite` for Inorganic Thermodynamics) as optional components in the utility driver. Ensure the specification dictates how these mechanisms are compiled conditionally (via CMake) and dispatched securely without breaking the zero-copy (CON-002) and GPU load balancing constraints from the Constitution."

## User Scenarios & Testing *(mandatory)*

### User Story 1 - Optional Compilation via CMake (Priority: P1)

As a model developer or systems engineer, I want to conditionally compile the auxiliary engines (Cloud-J and ISORROPIA-Lite) into the Exaero Utility using CMake flags, so that I can control the footprint and dependencies of the resulting binary.

**Why this priority**: Optional inclusion ensures that Exaero remains modular, allowing deployments to exclude unneeded engines when they are not strictly required for a given scientific run.

**Independent Test**: Can be fully tested by running CMake with varying flag combinations (e.g., `-DENABLE_CLOUDJ=ON`, `-DENABLE_ISORROPIA=OFF`) and verifying the successful compilation and linking of the appropriate dependencies.

**Acceptance Scenarios**:

1. **Given** a clean build environment, **When** the developer configures the build with Cloud-J disabled, **Then** the build completes without compiling or linking the Cloud-J sources.
2. **Given** a configured build with both engines enabled, **When** the utility is compiled, **Then** the final binary includes and executes hooks for both Cloud-J and ISORROPIA-Lite.

---

### User Story 2 - Zero-Copy Dispatch to Cloud-J (Priority: P1)

As a computational scientist, I want the Exaero utility to dispatch photolysis calculations to the Cloud-J engine using zero-copy memory handshakes between C++ and Fortran, so that memory overhead is minimized and performance remains high.

**Why this priority**: Eliminating data copies is critical for high-performance computing (HPC) environments to prevent out-of-memory errors and minimize data transfer latency (CON-002).

**Independent Test**: Can be tested by profiling memory allocations during a simulation step that calls Cloud-J, ensuring no redundant buffer allocations occur at the C++/Fortran boundary.

**Acceptance Scenarios**:

1. **Given** a model state resident in C++ managed memory, **When** Cloud-J is invoked for photolysis forcing, **Then** the data is accessed directly by Fortran routines via column-major zero-copy mapping.

---

### User Story 3 - GPU Load Balanced Execution (Priority: P2)

As an HPC operations engineer, I want the auxiliary engines to execute on GPUs using balanced workloads (e.g., hierarchical parallelism), so that there is no GPU thread starvation and execution time is strictly deterministic.

**Why this priority**: Ensures that GPU resources are utilized efficiently during computation without warp divergence bottlenecks.

**Independent Test**: Can be tested by running the utility under a GPU profiler (e.g., Nsight) to verify thread occupancy and absence of significant warp divergence when the auxiliary engines execute.

**Acceptance Scenarios**:

1. **Given** heterogeneous physical conditions across the grid, **When** the auxiliary engines process the domain on the GPU, **Then** the threads are load-balanced and do not suffer from starvation due to imbalanced branching.

### Edge Cases

- What happens when a model run attempts to invoke an auxiliary engine that was disabled during build time? (System must bypass gracefully or use a default identity operation).
- How does the system handle missing or corrupted input arrays from the C++ driver when handing off to the Fortran engines?
- What occurs if the GPU runs out of registers when instantiating the hierarchical parallelism structures for the auxiliary engines?

## Requirements *(mandatory)*

### Functional Requirements

- **FR-001**: System MUST provide distinct CMake configuration options to optionally compile and link the `Cloud-J` photolysis engine.
- **FR-002**: System MUST provide distinct CMake configuration options to optionally compile and link the `ISORROPIA-Lite` thermodynamic engine.
- **FR-003**: System MUST execute dummy or pass-through routines at runtime for any auxiliary engine that is disabled via CMake, preventing execution failures.
- **FR-004**: System MUST interface with Fortran-based mechanisms using C++23 `std::mdspan` (or `Kokkos::MemoryUnmanaged`) configured with `layout_left` to enforce zero-copy, column-major array views (CON-002 constraint).
- **FR-005**: System MUST utilize hierarchical parallelism (`Kokkos::TeamPolicy` and `Kokkos::TeamThreadRange`) for dispatching work to the engines on GPU architectures to maintain load balancing and prevent warp divergence.

### Key Entities

- **Exaero Utility Driver**: The core C++ component responsible for orchestrating the solvers and dispatching the data to auxiliary engines.
- **Cloud-J Engine**: The external Fortran mechanism calculating photolysis rates.
- **ISORROPIA-Lite Engine**: The external mechanism calculating inorganic thermodynamics.
- **Zero-Copy Arrays**: Multi-dimensional state arrays managed by Exaero, representing physical quantities across the atmospheric grid.

## Success Criteria *(mandatory)*

### Measurable Outcomes

- **SC-001**: Build configuration successfully toggles compilation of the auxiliary engines, yielding correct linkage configurations 100% of the time.
- **SC-002**: Memory allocation profiles show exactly zero supplementary data copying operations across component interfaces during auxiliary engine dispatch.
- **SC-003**: Hardware accelerator execution times for auxiliary engines demonstrate >80% efficiency without major processing starvation.
- **SC-004**: End-to-end integration tests pass successfully with identical numerical results (to within machine precision) compared to standalone baseline integrations.

## Assumptions

- Target build environments support C++23 standards (required for `std::mdspan`).
- Cloud-J and ISORROPIA-Lite repositories/sources are available and conform to expected Fortran interoperability conventions.
- The GPU hardware and backend driver support Kokkos hierarchical parallelism as mandated.
- Both auxiliary engines can be executed in a thread-safe manner inside Kokkos kernels.
