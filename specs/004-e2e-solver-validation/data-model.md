# Data Model: E2E Solver Validation & Baseline Testing

## Key Entities

### Validation State (C++ / Fortran)
Represents the concentration state vectors compared across the test step.

**Fields**:
- `species_concentrations` (Array, `float64`): Multi-dimensional layout of species over grid cells.
- `meteorology` (Array, `float64`): Temperature, pressure, and background conditions.

**Validation Rules**:
- Dimensions must perfectly align with the `LayoutLeft` expectations of Fortran when extracted via `.data()`.
- Elements must not be NaN or Inf.

### Baseline Output Schema (.csv)
The pre-generated legacy KPP output format used for verification.

**Fields**:
- `time_step` (Integer)
- `species_name` (String)
- `concentration` (Float64)
- `jacobian_sparsity_row` (Integer, Optional)
- `jacobian_sparsity_col` (Integer, Optional)

**Relationships**:
- Baseline Output is ingested by the Python validation script and mapped against the C++ `Validation State` output.
