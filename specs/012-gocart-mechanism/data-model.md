# Data Model: GOCART Mechanism

## Core Entities

### GOCART YAML Mechanism (`gocart.yaml`)
A structured definition of the GOCART chemical and aerosol processes suitable for compilation by MKPP.

#### Attributes
- `name`: "GOCART_Mechanism"
- `description`: "GOCART mechanism focusing strictly on chemistry and phase-transfer kinetics."

#### Species
- **Gases**: `OH`, `NO3`, `H2O2`, `DMS`, `SO2`
- **Aerosols**: 
  - `SO4`
  - `BC1` (Hydrophobic Black Carbon), `BC2` (Hydrophilic Black Carbon)
  - `OC1` (Hydrophobic Organic Carbon), `OC2` (Hydrophilic Organic Carbon)
  - `DUST1`, `DUST2`, `DUST3`, `DUST4`, `DUST5`
  - `SS1`, `SS2`, `SS3`, `SS4`, `SS5`

#### Reactions
- **DMS Oxidation**: `DMS + OH -> SO2` (Arrhenius)
- **DMS Oxidation**: `DMS + NO3 -> SO2` (Arrhenius)
- **SO2 Oxidation**: `SO2 + OH -> SO4` (Arrhenius)
- **Aqueous Oxidation**: `SO2 + H2O2 -> SO4` (Aqueous/Heterogeneous dependent on CLW)
- **Aging**: `BC1 -> BC2` (First-order)
- **Aging**: `OC1 -> OC2` (First-order)

*(Emissions and transport are deliberately excluded)*
