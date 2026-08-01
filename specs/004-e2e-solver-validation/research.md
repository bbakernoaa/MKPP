# Research: E2E Solver Validation & Baseline Testing

## Technical Unknowns

**1. Availability of Legacy KPP Baseline**
- **Decision**: Provide a `chapman.eqn` file and a pre-generated `kpp_baseline_chapman.csv` output file within the `tests/integration/e2e_validation/data/` directory.
- **Rationale**: Installing and compiling the full legacy Fortran KPP code generation tool across all CI environments is heavy and error-prone. Providing a static reference baseline ensures deterministic verification of the Exaero outputs.
- **Alternatives considered**: Dynamically running legacy KPP during CI. (Rejected due to complexity and Fortran environment variance).

**2. Handling Near-Zero Limits (Subnormals)**
- **Decision**: The validation fixture will enforce an absolute tolerance (ATOL) of $1 \times 10^{-12}$ for values that approach zero, alongside the relative tolerance of $1 \times 10^{-6}$.
- **Rationale**: Atmospheric chemistry can push minor species to infinitesimal concentrations, triggering meaningless relative errors. 
- **Alternatives considered**: Clamping strictly to zero. (Rejected because analytical solvers shouldn't artificially lose conservation).

**3. Memory Profiling (Zero Overhead)**
- **Decision**: Use `Kokkos::Profiling::space_allocate` hooks within the GoogleTest harness to assert 0-bytes allocated.
- **Rationale**: Already proven successful in `003-exaero-auxiliary-engines`.
