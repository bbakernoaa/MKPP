# Data Model & Key Entities: Auxiliary Engines

## Key Entities

### Exaero Utility Driver
The primary C++ coordinator. It manages the allocation of large multidimensional atmospheric state arrays (temperature, pressure, gas species, aerosols).

### Atmospheric State Array (C++ to Fortran)
- **Type**: Unmanaged column-major view (`Kokkos::LayoutLeft` or `std::mdspan<... layout_left>`).
- **Fields**: Real arrays containing physical variables (e.g., density, chemical concentrations, zenith angles).
- **Constraints**: 
  - Must not be reallocated during the handoff.
  - Ownership remains with Exaero; Fortran receives temporary pointer references.

### Cloud-J Engine Hook
- **Input**: Radiative fluxes, physical state, zenith angle.
- **Output**: Photolysis rates for chemical kinetics.
- **State Transition**: Calculates rates in-place directly on the Exaero-provided memory blocks if `USE_CLOUDJ` is defined. If undefined, acts as an identity function (rates = 0.0 or unchanged).

### ISORROPIA-Lite Engine Hook
- **Input**: Inorganic aerosol concentrations, temperature, relative humidity.
- **Output**: Equilibrium partitioned solid/liquid/gas concentrations.
- **State Transition**: Modifies the inorganic species state arrays in-place if `USE_ISORROPIA_LITE` is defined. If undefined, does nothing.

## Memory Mapping Validation Rules
1. **Dimension Order**: C++ dimension definitions must reverse logical Fortran dimensions (e.g., C++ `[N, M]` corresponds to Fortran `(M, N)`) and enforce column-major indexing explicitly for the memory footprint to match.
2. **Bounds**: Boundary checks must be asserted prior to Fortran dispatch to prevent out-of-bounds pointer arithmetic within the external libraries.
