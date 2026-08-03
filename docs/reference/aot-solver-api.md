# Reference: AOT Kokkos ODE Solver C++ API

This reference documents the C++ functions, constants, and layout specifications exposed by MKPP generated AOT Kokkos solver headers (`mkpp-generated/*.hpp`).

---

## 1. Constants and Type Aliases

Each generated header defines namespace-scoped constants describing the mechanism size:

```cpp
namespace mechanism_name {
    // Total number of prognostic chemical species
    constexpr int NUM_SPECIES = ...;

    // Total number of chemical reactions
    constexpr int NUM_REACTIONS = ...;

    // Total non-zero entries in the symbolic Jacobian
    constexpr int NONZERO_JACOBIAN_ENTRIES = ...;
}
```

---

## 2. Primary Function Signatures

All generated solver routines are annotated with `KOKKOS_INLINE_FUNCTION` to enable host and device compilation.

### `compute_rates`

Evaluates chemical reaction rates based on species concentration vector, temperature, pressure, and ambient air density.

```cpp
template <typename StateView, typename RateView>
KOKKOS_INLINE_FUNCTION
void compute_rates(
    const StateView& y,
    RateView& r,
    double temp,
    double press,
    double cair
);
```

#### Parameters
- **`y`** (`const StateView&`): 1D view or subview of species concentrations $[\text{molec/cm}^3]$, size `NUM_SPECIES`.
- **`r`** (`RateView&`): Output 1D view or subview for reaction rates $[\text{molec/cm}^3/\text{s}]$, size `NUM_REACTIONS`.
- **`temp`** (`double`): Temperature $[K]$.
- **`press`** (`double`): Pressure $[Pa]$.
- **`cair`** (`double`): Total air density $[\text{molec/cm}^3]$.

---

### `compute_jacobian`

Evaluates the unrolled symbolic chemical Jacobian entries ($J_{i,j} = \frac{\partial f_i}{\partial y_j}$) into scalar variables.

```cpp
template <typename StateView, typename JacView>
KOKKOS_INLINE_FUNCTION
void compute_jacobian(
    const StateView& y,
    JacView& J,
    double temp,
    double press,
    double cair
);
```

#### Parameters
- **`y`** (`const StateView&`): 1D species concentration view.
- **`J`** (`JacView&`): Sparse/unrolled Jacobian representation view or scalar buffer.
- **`temp`**, **`press`**, **`cair`**: Environmental state drivers.

---

### `lu_decompose` & `lu_solve`

Performs branchless, zero-loop symbolic sparse LU decomposition and forward/backward substitution.

```cpp
// Decomposes (I - gamma * dt * J) in-place into L and U scalar factors
KOKKOS_INLINE_FUNCTION
void lu_decompose(/* internal scalar references */);

// Solves A * x = b for x in-place
KOKKOS_INLINE_FUNCTION
void lu_solve(/* internal scalar references */);
```

---

### `integrate`

Integrates the chemical ODE system over time interval $[t_{\text{start}}, t_{\text{end}}]$ using adaptive Rosenbrock-2 (ROS-2) integration.

```cpp
template <typename StateView>
KOKKOS_INLINE_FUNCTION
void integrate(
    const StateView& y,
    double temp,
    double press,
    double t_start,
    double t_end,
    double rtol = 1.0e-4,
    double atol = 1.0e-3
);
```

#### Parameters
- **`y`** (`const StateView&`): In-out species state subview. Updated in-place to $y(t_{\text{end}})$.
- **`temp`** (`double`): Temperature $[K]$.
- **`press`** (`double`): Pressure $[Pa]$.
- **`t_start`** (`double`): Integration start time $[s]$.
- **`t_end`** (`double`): Integration end time $[s]$.
- **`rtol`** (`double`, optional): Relative tolerance (default: $10^{-4}$).
- **`atol`** (`double`, optional): Absolute tolerance (default: $10^{-3}$).

---

## 3. CF Metadata Standard Table

Variables and species states in MKPP generated solvers conform to standard Climate and Forecast (CF) metadata conventions:

| Variable | Standard Name | Long Name | Units | Memory Layout |
| :--- | :--- | :--- | :--- | :--- |
| `state` | `mole_fraction_of_chemical_species_in_air` | Chemical Species Concentration Vector | $\text{molec/cm}^3$ | `Kokkos::LayoutLeft` (GPU contiguous) |
| `temp` | `air_temperature` | Ambient Air Temperature | $K$ | Scalar / 1D View |
| `press` | `air_pressure` | Ambient Air Pressure | $Pa$ | Scalar / 1D View |
| `cair` | `molar_concentration_of_air` | Total Air Molar Density | $\text{molec/cm}^3$ | Scalar / 1D View |
| `reaction_rates` | `chemical_reaction_rate` | Chemical Reaction Fluxes | $\text{molec/cm}^3/\text{s}$ | 1D View |

---

## Related Documents

- [Reaction Types & YAML Schema Reference](reaction-types-and-yaml-schema.md)
- [Reaction Kinetics & Unified Jacobian Explanation](../explanation/unified-jacobian-and-reaction-kinetics.md)
- [How-To: Create Custom Reactions](../how-to/create-custom-reactions.md)
- [AOT Solver Quickstart Tutorial](../tutorials/aot-solver-quickstart.md)
- [How-To: Run AOT Solver Benchmarks](../how-to/run-aot-solver-benchmarks.md)
- [AOT Symbolic LU Architecture Explanation](../explanation/aot-symbolic-lu-architecture.md)
