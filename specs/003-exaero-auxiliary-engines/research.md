# Research & Decisions: Exaero Auxiliary Engines

## Unknowns Resolved

### 1. CMake Optional Engine Linking
- **Decision**: Introduce CMake options `EXAERO_ENABLE_CLOUDJ` and `EXAERO_ENABLE_ISORROPIA_LITE` in `src/exaero/CMakeLists.txt` (default `OFF`). Use `target_compile_definitions` to define preprocessor macros (e.g., `USE_CLOUDJ`) in the Exaero C++ code to toggle compilation of the wrapper calls. When `OFF`, a dummy/identity operation is provided.
- **Rationale**: Keeps the Exaero binary footprint small if auxiliary mechanisms aren't needed, satisfying FR-001, FR-002, and FR-003.
- **Alternatives considered**: Dynamic linking/plugin architecture. Rejected due to HPC deployment complexity and Fortran ABI complications.

### 2. Zero-Copy Fortran Handoff (CON-002)
- **Decision**: Define data arrays using `Kokkos::View<double**, Kokkos::LayoutLeft, Kokkos::MemoryTraits<Kokkos::Unmanaged>>` or C++23 `std::mdspan` mapped to column-major layout when passing memory pointers to Fortran routines.
- **Rationale**: Fortran inherently expects column-major multi-dimensional arrays. By forcing `LayoutLeft` on the C++ side, we can pass raw pointers directly to Fortran without explicit transpose or buffer copies, minimizing overhead (FR-004).
- **Alternatives considered**: Row-major C++ arrays with runtime transposition. Rejected due to violating the strict zero-copy performance constraint.

### 3. GPU Load Balancing & Divergence Prevention (CON-001)
- **Decision**: Structure the engine dispatch using `Kokkos::parallel_for` with `Kokkos::TeamPolicy`. Inside the kernel, map work blocks to teams and use `Kokkos::TeamThreadRange` to loop over grid points concurrently without thread starvation.
- **Rationale**: Prevents warp divergence and thread starvation by explicitly managing how sub-grid points map to hardware threads (FR-005). 
- **Alternatives considered**: `Kokkos::RangePolicy`. Rejected because standard 1D iteration over complex multidimensional thermodynamic fields often causes severe divergence on GPUs without explicit team/thread block hierarchies.
