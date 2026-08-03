# Reference: Reaction Types, Parameters, and YAML Schema

This document provides a reference for all reaction types, parameter definitions, species phase modes, and YAML schema rules supported by the Futuristic Kinetic PreProcessor (MKPP/FKPP).

---

## 1. Mechanism Specification YAML Schema

A mechanism YAML file consists of top-level metadata, species declarations, and reaction list definitions:

```yaml
name: mechanism_identifier
description: Detailed description of chemical mechanism
species:
  - name: SpeciesName
    phase: gas # gas | aerosol | aqueous
    role: variable # variable | fixed
    elements:
      C: 2
      H: 6

reactions:
  - type: REACTION_TYPE
    reactants:
      SpeciesA: 1.0
      SpeciesB: 1.0
    products:
      SpeciesC: 1.0
    parameters:
      # Type-specific rate parameters
```

---

## 2. Species Declarations

Each species entry defines physical phase, solver variable mode, and elemental stoichiometry.

| Property | Type | Options | Description |
| :--- | :--- | :--- | :--- |
| `name` | string | Valid identifier (e.g., `O3`, `NO2`, `SO4_aero`) | Unique species identifier |
| `phase` | string | `gas`, `aerosol`, `aqueous` | Physical state phase for Unified Jacobian coupling |
| `role` | string | `variable` (default), `fixed` | `fixed` species have constant background concentration ($dC/dt = 0$) |
| `elements` | dict | `{ElementSymbol: integer}` | Elemental stoichiometry for mass balance verification (e.g. `{C: 2, H: 6}`) |

---

## 3. Supported Reaction Types & Parameters

### 3.1 `ARRHENIUS`
Standard and modified Arrhenius reaction rate laws.

- **Formula**: $k(T) = A \cdot \left(\frac{T}{300}\right)^B \cdot \exp\left(-\frac{C}{T}\right)$
- **Parameters**:
  - `A` (*float*, required): Pre-exponential factor $[\text{cm}^3/\text{molec/s}$ or $1/\text{s}]$.
  - `B` (*float*, optional, default `0.0`): Temperature exponent $n$.
  - `C` (*float*, optional, default `0.0`): Activation energy parameter $E_a / R$ $[K]$.

---

### 3.2 `TROE` / `FALLOFF`
Pressure-dependent falloff reactions with low and high pressure limit parameterization.

- **Formula**:
  $$k_0(T) = A_0 \left(\frac{T}{300}\right)^{B_0} \exp\left(-\frac{C_0}{T}\right) \cdot [M]$$
  $$k_\infty(T) = A_\infty \left(\frac{T}{300}\right)^{B_\infty} \exp\left(-\frac{C_\infty}{T}\right)$$
  $$k(T, M) = \left(\frac{k_0}{1 + k_0/k_\infty}\right) \cdot F_c^{\frac{1}{1 + \left(\log_{10}(k_0/k_\infty)\right)^2}}$$
- **Parameters**:
  - `k0`: `{A: float, B: float, C: float}` (Low pressure limit parameters)
  - `kinf`: `{A: float, B: float, C: float}` (High pressure limit parameters)
  - `Fc` (*float*, optional, default `0.6`): Falloff broadening factor.

---

### 3.3 `PHOTOLYSIS`
Photolytic rate laws driven by light absorption.

- **Formula**: $R = J_{\text{photo}} \cdot \prod_{j} [C_j]^{s_{j}}$
- **Parameters**:
  - `A` (*float* or *string*, required): Base photolysis rate coefficient $J_0$ $[1/\text{s}]$ or photolysis reaction key.

---

### 3.4 `EP2`
Specialized termolecular rate law.

- **Formula**: $k(T) = K_0 + \frac{K_3}{1 + K_3 / K_2}$ where $K_i = A_i \exp(-C_i / T)$.
- **Parameters**: `A0`, `C0`, `A2`, `C2`, `A3`, `C3`.

---

### 3.5 `EP3`
Specialized termolecular rate law with total air density dependence.

- **Formula**: $k(T, M) = K_1 + K_2 \cdot [M]$ where $K_i = A_i \exp(-C_i / T)$.
- **Parameters**: `A1`, `C1`, `A2`, `C2`.

---

### 3.6 `HETEROGENEOUS`
Gas-to-aerosol particle surface uptake rate laws.

- **Formula**: $k_{\text{het}} = \frac{1}{4} \cdot \gamma \cdot v_{\text{gas}} \cdot S_a$
- **Parameters**:
  - `gamma` (*float*, required): Mass accommodation / uptake coefficient $\gamma \in [0, 1]$.

---

### 3.7 `PHASE_CHANGE` / `CONDENSATION`
Direct kinetic phase transfer between gas, aerosol, and aqueous species.

- **Formula**: Evaluated as continuous kinetic flux ODEs coupling $[C_{\text{gas}}]$ and $[C_{\text{aerosol}}]$ in the Unified Jacobian state vector.

---

### 3.8 `CUSTOM` / `TUNNELING`
Custom user-defined SymPy math expressions.

- **Parameters**:
  - `rate_expression` (*string*): Valid SymPy-parseable math string using variables `Temp`, `Press`, `M_density`, `cair`, `S_a`, `v_gas`.

---

## 4. CF Metadata for Multiphase States

Generated solvers emit variables conforming to standard Climate and Forecast (CF) metadata conventions:

| Variable Name | Standard Name | Long Name | Units | Phase |
| :--- | :--- | :--- | :--- | :--- |
| `C_gas` | `mole_fraction_of_gas_phase_species_in_air` | Gas Phase Concentration | $\text{molec/cm}^3$ | Gas |
| `C_aerosol` | `mass_concentration_of_aerosol_species_in_air` | Aerosol Particle Concentration | $\text{molec/cm}^3$ or $\mu\text{g/m}^3$ | Aerosol |
| `C_aqueous` | `mass_concentration_of_aqueous_species_in_cloud_water` | Aqueous Phase Concentration | $\text{molec/cm}^3$ | Aqueous |
| `temp` | `air_temperature` | Temperature | $K$ | Driver |
| `press` | `air_pressure` | Pressure | $Pa$ | Driver |
| `S_a` | `aerosol_surface_area_density` | Aerosol Surface Area | $m^2/m^3$ | Driver |

---

## Related Documents

- [Reaction Kinetics & Unified Jacobian Explanation](../explanation/unified-jacobian-and-reaction-kinetics.md)
- [How-To: Create Custom Reactions](../how-to/create-custom-reactions.md)
- [AOT Solver C++ API Reference](aot-solver-api.md)
