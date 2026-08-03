# Research: GOCART Mechanism

## 1. Needs Clarification: GOCART Chemical Reactions
**Decision:** Implement the standard GOCART chemical and heterogeneous reactions in `mechanisms/gocart.yaml`.
**Rationale:** MKPP is strictly constrained to chemistry (gas-phase, heterogeneous, gas-to-particle). Emissions and saltation fluxes are completely out of scope. The GOCART chemistry involves:
- **Gas-Phase (Arrhenius):** DMS oxidation (DMS + OH -> SO2), SO2 oxidation (SO2 + OH -> SO4).
- **Aqueous/Heterogeneous:** In-cloud SO2 oxidation (SO2 + H2O2 -> SO4).
- **Aging (First-Order):** Hydrophobic to Hydrophilic aging for Black Carbon and Organic Carbon.

## 2. Needs Clarification: Meteorological Fields vs. Exaero
**Decision:** Use `METEO_STRUCT` or host meteorology variables directly instead of Exaero for standard physical inputs.
**Rationale:** The user specified: "Note that the host passes the meteorological fields not exaero". Therefore, we will rely on standard host meteorology variables (like Temperature, Relative Humidity, Pressure, Cloud Liquid Water, etc.) passed directly from the host.

## 3. Needs Clarification: Mechanism Species
**Decision:** Define the full suite of GOCART species.
**Rationale:** We need to test the Unified Jacobian with various species:
- `DMS`, `SO2`, `SO4`
- `BC1` (hydrophobic), `BC2` (hydrophilic)
- `OC1` (hydrophobic), `OC2` (hydrophilic)
- Dust bins (`DUST1`, `DUST2`, `DUST3`, `DUST4`, `DUST5`)
- Sea Salt bins (`SS1`, `SS2`, `SS3`, `SS4`, `SS5`)
Note: Dust and Sea salt bins will only have sinks (e.g. settling) or act as heterogeneous surfaces in MKPP, as emissions are out of scope. In this mechanism, they may not have explicit chemical reactions but are included as species to ensure the solver allocates state for them and can process heterogeneous uptake if defined.
