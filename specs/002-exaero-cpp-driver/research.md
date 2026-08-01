# Research Notes: Exaero C++ Driver

**Objective**: Resolve technical unknowns required to implement the Exaero Host Driver.

## Needs Clarification Resolutions

**Unknown**: How to elegantly link the MKPP generated mechanisms into the C++ driver?
**Decision**: Use CMake variables (e.g. `-DMKPP_MECHANISMS="Chapman;CRACMM"`) to conditionally include source paths. The `registry.cpp` will use preprocessor macros (e.g. `#ifdef ENABLE_MECHANISM_CHAPMAN`) to map the strings to the generated headers.
**Rationale**: This keeps the library statically compiled and HPC-friendly, avoiding the complexity and instability of `dlopen` shared plugins on varied supercomputer architectures.

**Unknown**: Best approach for Kokkos SZA Workload Sorting without dynamic memory allocations?
**Decision**: Allocate persistent `Kokkos::View<int*, Kokkos::DeviceSpace>` index maps during the initial driver instantiation. During each timestep execution, `Kokkos::sort` or a custom histogram sort will simply reorder the values inside the persistent view. The `TeamPolicy` will iterate over the sorted indices rather than the physical grid directly.
**Rationale**: Guarantees zero runtime allocations, strictly adhering to SC-003.
