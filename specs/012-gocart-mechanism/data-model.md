# Data Model: GOCART Mechanism

## Core Entities

### GOCART YAML Mechanism (`gocart.yaml`)
A structured definition of the GOCART chemical and aerosol processes suitable for compilation by MKPP.

#### Attributes
- `name`: "GOCART_Mechanism"
- `description`: "GOCART mechanism focusing strictly on chemistry and phase-transfer kinetics."

#### Species
- **Gases**: `OH`, `NO3`, `H2O2`, `DMS`, `SO2`, `HNO3`, `NH3`
- **Aerosols**: 
  - `SO4`
  - `BC1` (Hydrophobic Black Carbon), `BC2` (Hydrophilic Black Carbon)
  - `OC1` (Hydrophobic Organic Carbon), `OC2` (Hydrophilic Organic Carbon)
  - `DUST1`, `DUST2`, `DUST3`, `DUST4`, `DUST5`
  - `SS1`, `SS2`, `SS3`, `SS4`, `SS5`
  - `NH4a` (Aerosol Ammonium)
  - `NO3an1`, `NO3an2`, `NO3an3` (Aerosol Nitrate size bins)

#### Reactions
- **DMS Oxidation**: `DMS + OH -> SO2` (Arrhenius)
- **DMS Oxidation**: `DMS + NO3 -> SO2` (Arrhenius)
- **SO2 Oxidation**: `SO2 + OH -> SO4` (Arrhenius)
- **Aqueous Oxidation**: `SO2 + H2O2 -> SO4` (Aqueous/Heterogeneous dependent on CLW)
- **Aging**: `BC1 -> BC2` (First-order)
- **Aging**: `OC1 -> OC2` (First-order)
- **Heterogeneous Uptake**: `HNO3 + DUST/SS -> NO3an + DUST/SS` (Dependent on Surface Area)
- **Thermodynamic Equilibration**: `NH3 + HNO3 + SO4 -> NH4a + NO3an` (RPMARES/ISORROPIA-Lite Phase Change)

*(Emissions and transport are deliberately excluded)*
