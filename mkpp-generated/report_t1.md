# MKPP Mechanism Diagnostic Report: t1

## Overview
- **Total Species**: 210
- **Total Reactions**: 547

### Reaction Types Breakdown
- **ARRHENIUS**: 361
- **SURFACE**: 13
- **TROE**: 31
- **PHOTOLYSIS**: 123
- **USER_DEFINED**: 19

### Stiffness Partitioning
- **Implicit (Stiff) Reactions**: 0
- **Explicit (Non-Stiff) Reactions**: 547
- **Graph Topology Status**: Mechanism contains cyclically dependent fast radicals. Tarjan SCC was applied.

## Generated SymPy Rate Expressions
Below are the exact algebraic AST expressions evaluated by SymPy for the Unified Jacobian.

```text
R1: ARRHENIUS | Reactants: ['CH3O2', 'TERPO2'] | Products: ['TERPROD1', 'CH2O', 'CH3OH', 'HO2', 'CH3COCH3'] | A: 1204428.152
R2: ARRHENIUS | Reactants: ['C3H7OOH', 'OH'] | Products: ['H2O', 'C3H7O2'] | A: 2288413.4888
R3: ARRHENIUS | Reactants: ['N', 'NO2'] | Products: ['N2', 'O2'] | A: 873210.4102
R4: ARRHENIUS | Reactants: ['O', 'CH2O'] | Products: ['HO2', 'OH', 'CO'] | A: 20475278.584
R5: ARRHENIUS | Reactants: ['TOLUO2VBS', 'HO2'] | Products: ['HO2', 'SOAG0', 'SOAG1', 'SOAG2', 'SOAG3', 'SOAG4'] | A: 451660.55700000003
R6: ARRHENIUS | Reactants: ['OH', 'HCFC142B'] | Products: ['CL', 'COF2'] | A: 782878.2988
R7: ARRHENIUS | Reactants: ['CFC114', 'O1D'] | Products: ['CL', 'COF2'] | A: 70459046.892
R8: ARRHENIUS | Reactants: ['NO', 'CH3CO3'] | Products: ['CH3O2', 'CO2', 'NO2'] | A: 4877934.0156
R9: ARRHENIUS | Reactants: ['HONITR', 'OH'] | Products: ['ONITR', 'HO2'] | A: 1204428.152
R10: ARRHENIUS | Reactants: ['ISOPO2VBS', 'HO2'] | Products: ['HO2', 'SOAG0', 'SOAG1', 'SOAG2', 'SOAG3', 'SOAG4'] | A: 127669.384112
R11: ARRHENIUS | Reactants: ['CH3CO3'] | Products: ['CH3O2', 'CO2'] | A: 1746420.8204
R12: ARRHENIUS | Reactants: ['H2O', 'O1D'] | Products: ['OH'] | A: 98160894.388
R13: ARRHENIUS | Reactants: ['OH', 'CLO'] | Products: ['HCL', 'O2'] | A: 361328.4456
R14: ARRHENIUS | Reactants: ['OH', 'MTERP'] | Products: ['MTERP', 'OH', 'MTERPO2VBS'] | A: 7226568.9120000005
R15: ARRHENIUS | Reactants: ['CH3BR', 'O1D'] | Products: ['BR'] | A: 108398533.67999999
R16: ARRHENIUS | Reactants: ['SVOC', 'OH'] | Products: ['OH', 'SOAG0', 'SOAG1', 'SOAG2', 'SOAG3', 'SOAG4'] | A: 8069668.6184
R17: ARRHENIUS | Reactants: ['XYLENOOH', 'OH'] | Products: ['XYLENO2'] | A: 2288413.4888
R18: ARRHENIUS | Reactants: ['HCL', 'O1D'] | Products: ['CL', 'OH'] | A: 59619193.524
R19: ARRHENIUS | Reactants: ['SO', 'BRO'] | Products: ['SO2', 'BR'] | A: 34326202.331999995
R20: ARRHENIUS | Reactants: ['NO', 'BENZO2'] | Products: ['NO2', 'GLYOXAL', 'BIGALD1', 'HO2'] | A: 1565756.5976
R21: ARRHENIUS | Reactants: ['TOLO2', 'NO'] | Products: ['NO2', 'GLYOXAL', 'CH3COCHO', 'HO2', 'BIGALD1', 'BIGALD2', 'BIGALD3'] | A: 1565756.5976
R22: ARRHENIUS | Reactants: ['BCARY', 'OH'] | Products: ['BCARY', 'OH', 'BCARYO2VBS'] | A: 120442815.2
R23: ARRHENIUS | Reactants: ['CH3O2', 'C3H7O2'] | Products: ['CH2O', 'HO2', 'CH3COCH3'] | A: 225830.27850000001
R24: ARRHENIUS | Reactants: ['O1D', 'HCFC22'] | Products: ['CL', 'COF2'] | A: 46069376.813999996
R25: ARRHENIUS | Reactants: ['MEK', 'OH'] | Products: ['MEKO2'] | A: 1385092.3747999999
R26: ARRHENIUS | Reactants: ['OH', 'TOLOOH'] | Products: ['TOLO2'] | A: 2288413.4888
R27: ARRHENIUS | Reactants: ['COF2', 'O1D'] | Products: ['F'] | A: 12887381.2264
R28: ARRHENIUS | Reactants: ['ISOP', 'OH'] | Products: ['ISOPAO2', 'ISOPBO2'] | A: 15296237.5304
R29: ARRHENIUS | Reactants: ['E90'] | Products: [] | A: 1.29e-07
R30: ARRHENIUS | Reactants: ['O3', 'MTERP'] | Products: ['MTERP', 'O3', 'SOAG0', 'SOAG1', 'SOAG2', 'SOAG3', 'SOAG4'] | A: 379.39486788
R31: ARRHENIUS | Reactants: ['CH3O2', 'MCO3'] | Products: ['CH2O', 'HO2', 'CO2', 'CH3CO3'] | A: 1204428.152
R32: ARRHENIUS | Reactants: ['CH3CL', 'OH'] | Products: ['CL', 'H2O', 'HO2'] | A: 1180339.58896
R33: ARRHENIUS | Reactants: ['NO', 'ISOPBO2'] | Products: ['HYDRALD', 'ISOPNITB', 'NO2', 'HO2', 'GLYOXAL', 'GLYALD', 'CH3COCHO', 'HYAC'] | A: 2649741.9343999997
R34: ARRHENIUS | Reactants: ['CH3O2', 'CH3CO3'] | Products: ['CH3O2', 'CH2O', 'HO2', 'CO2', 'CH3COOH'] | A: 1204428.152
R35: ARRHENIUS | Reactants: ['O3', 'MACR'] | Products: ['CH2O', 'OH', 'CO', 'CH3CO3', 'CH3COCHO', 'HCOOH', 'HO2'] | A: 903.321114
R36: ARRHENIUS | Reactants: ['OH', 'ALKOOH'] | Products: ['ALKO2'] | A: 2288413.4888
R37: ARRHENIUS | Reactants: ['OH', 'CH3CHO'] | Products: ['CH3CO3', 'H2O'] | A: 2788251.1718800003
R38: ARRHENIUS | Reactants: ['BCARYO2VBS', 'HO2'] | Products: ['HO2', 'SOAG0', 'SOAG1', 'SOAG2', 'SOAG3', 'SOAG4'] | A: 165608.87089999998
R39: ARRHENIUS | Reactants: ['NO3', 'MTERP'] | Products: ['NTERPO2'] | A: 722656.8912
R40: ARRHENIUS | Reactants: ['N', 'O2'] | Products: ['NO', 'O'] | A: 1987306.4508
R41: ARRHENIUS | Reactants: ['HOCH2OO', 'NO'] | Products: ['HCOOH', 'NO2', 'HO2'] | A: 1565756.5976
R42: ARRHENIUS | Reactants: ['SO', 'CLO'] | Products: ['SO2', 'CL'] | A: 16861994.128
R43: ARRHENIUS | Reactants: ['CH2BR2', 'O1D'] | Products: ['BR'] | A: 154769017.532
R44: ARRHENIUS | Reactants: ['OH', 'CH3COCHO'] | Products: ['CH3CO3', 'CO', 'H2O'] | A: 505859.82383999997
R45: ARRHENIUS | Reactants: ['O1D', 'COFCL'] | Products: ['F', 'CL'] | A: 114420674.44
R46: ARRHENIUS | Reactants: ['CH3CCL3', 'OH'] | Products: ['H2O', 'CL'] | A: 987631.08464
R47: ARRHENIUS | Reactants: ['O1D', 'HCFC141B'] | Products: ['CL', 'COFCL'] | A: 108037205.2344
R48: ARRHENIUS | Reactants: ['CH4', 'O1D'] | Products: ['CH2O', 'H2'] | A: 5419926.683999999
R49: ARRHENIUS | Reactants: ['C3H7O2', 'HO2'] | Products: ['C3H7OOH', 'O2'] | A: 451660.55700000003
R50: ARRHENIUS | Reactants: ['ISOP', 'OH'] | Products: ['ISOP', 'OH', 'ISOPO2VBS'] | A: 15296237.5304
R51: ARRHENIUS | Reactants: ['OH', 'TERPROD1'] | Products: ['TERP2O2'] | A: 34326202.331999995
R52: ARRHENIUS | Reactants: ['N', 'NO2'] | Products: ['NO'] | A: 873210.4102
R53: ARRHENIUS | Reactants: ['H', 'O3'] | Products: ['OH', 'O2'] | A: 84309970.64
R54: ARRHENIUS | Reactants: ['ISOPNO3', 'CH3O2'] | Products: ['NC4CHO', 'HO2', 'CH2O', 'CH3OH', 'NC4CH2OH'] | A: 301107.038
R55: ARRHENIUS | Reactants: ['MDIALO2', 'HO2'] | Products: ['OH', 'HO2', 'CH3COCHO', 'CO', 'CH3O2', 'GLYOXAL'] | A: 258952.05268
R56: ARRHENIUS | Reactants: ['CH3O2', 'ISOPBO2'] | Products: ['CH3OH', 'HO2', 'CH2O', 'HYDRALD'] | A: 301107.038
R57: ARRHENIUS | Reactants: ['OH', 'DMS'] | Products: ['SO2'] | A: 6624354.836
R58: ARRHENIUS | Reactants: ['HOCH2OO', 'HO2'] | Products: ['HCOOH'] | A: 451660.55700000003
R59: ARRHENIUS | Reactants: ['NO3', 'MTERP'] | Products: ['MTERP', 'NO3', 'SOAG3', 'SOAG4'] | A: 722656.8912
R60: ARRHENIUS | Reactants: ['C2H6', 'OH'] | Products: ['C2H5O2', 'H2O'] | A: 4612959.82216
R61: ARRHENIUS | Reactants: ['GLYOXAL', 'OH'] | Products: ['HO2', 'CO', 'CO2'] | A: 6925461.874000001
R62: ARRHENIUS | Reactants: ['C6H5O2', 'HO2'] | Products: ['C6H5OOH'] | A: 451660.55700000003
R63: ARRHENIUS | Reactants: ['OH', 'MTERP'] | Products: ['TERPO2'] | A: 7226568.9120000005
R64: ARRHENIUS | Reactants: ['OH', 'XOOH'] | Products: ['XO2', 'OH'] | A: 915365.39552
R65: ARRHENIUS | Reactants: ['O', 'O3'] | Products: ['O2'] | A: 4817712.608
R66: ARRHENIUS | Reactants: ['OH', 'IEPOX'] | Products: ['XO2'] | A: 7828782.988
R67: ARRHENIUS | Reactants: ['C2H6', 'CL'] | Products: ['HCL', 'C2H5O2'] | A: 43359413.471999995
R68: ARRHENIUS | Reactants: ['ALKO2', 'NO'] | Products: ['ALKNIT'] | A: 32519.560103999996
R69: ARRHENIUS | Reactants: ['BZOO', 'NO'] | Products: ['BZALD', 'NO2', 'HO2'] | A: 1565756.5976
R70: ARRHENIUS | Reactants: ['OH', 'O'] | Products: ['H', 'O2'] | A: 10839853.367999999
R71: ARRHENIUS | Reactants: ['NO3', 'DMS'] | Products: ['SO2', 'HNO3'] | A: 114420.67444
R72: ARRHENIUS | Reactants: ['MCO3'] | Products: ['CO2', 'CH2O', 'CH3CO3'] | A: 1385092.3747999999
R73: ARRHENIUS | Reactants: ['NO', 'ENEO2'] | Products: ['CH3CHO', 'CH2O', 'CH3COCH3', 'HO2', 'NO2'] | A: 2890627.5648
R74: ARRHENIUS | Reactants: ['O2', 'M', 'O'] | Products: ['O3', 'M'] | A: 217.59707599952029
R75: ARRHENIUS | Reactants: ['NO', 'CLO'] | Products: ['NO2', 'CL'] | A: 3854170.0864
R76: ARRHENIUS | Reactants: ['XO2', 'HO2'] | Products: ['XOOH'] | A: 481771.2608
R77: ARRHENIUS | Reactants: ['O', 'HO2'] | Products: ['OH', 'O2'] | A: 18066422.28
R78: ARRHENIUS | Reactants: ['TOLUENE', 'OH'] | Products: ['TOLUENE', 'OH', 'TOLUO2VBS'] | A: 1023763.9292
R79: ARRHENIUS | Reactants: ['OH', 'MACR'] | Products: ['MACRO2', 'H2O', 'MCO3'] | A: 5781255.1296
R80: ARRHENIUS | Reactants: ['CFC12', 'O1D'] | Products: ['CL', 'COF2'] | A: 72506574.75039999
R81: ARRHENIUS | Reactants: ['O', 'BRO'] | Products: ['BR', 'O2'] | A: 11442067.444
R82: ARRHENIUS | Reactants: ['H', 'HO2'] | Products: ['H2', 'O2'] | A: 4155277.1244
R83: ARRHENIUS | Reactants: ['OH', 'HBR'] | Products: ['BR', 'H2O'] | A: 3312177.418
R84: ARRHENIUS | Reactants: ['BCARY', 'OH'] | Products: ['TERPO2'] | A: 120442815.2
R85: ARRHENIUS | Reactants: ['MACRO2', 'CH3CO3'] | Products: ['CH3COCHO', 'CH3O2', 'CO', 'HO2', 'GLYALD', 'HYAC', 'CH2O', 'CH3CO3'] | A: 8430997.064
R86: ARRHENIUS | Reactants: ['O1D', 'H2'] | Products: ['H', 'OH'] | A: 72265689.12
R87: ARRHENIUS | Reactants: ['SO', 'O2'] | Products: ['SO2', 'O'] | A: 96354.25216
R88: ARRHENIUS | Reactants: ['OH', 'C6H5OOH'] | Products: ['C6H5O2'] | A: 2288413.4888
R89: ARRHENIUS | Reactants: ['O', 'HOCL'] | Products: ['CLO', 'OH'] | A: 102376.39292
R90: ARRHENIUS | Reactants: ['PHENO', 'O3'] | Products: ['C6H5O2'] | A: 168619.94128
R91: ARRHENIUS | Reactants: ['NO', 'BENZO2VBS'] | Products: ['NO', 'SOAG0', 'SOAG1', 'SOAG2', 'SOAG3', 'SOAG4'] | A: 1565756.5976
R92: ARRHENIUS | Reactants: ['PHENO2', 'NO'] | Products: ['HO2', 'GLYOXAL', 'NO2'] | A: 1565756.5976
R93: ARRHENIUS | Reactants: ['SO', 'NO2'] | Products: ['SO2', 'NO'] | A: 8430997.064
R94: ARRHENIUS | Reactants: ['NO', 'ACBZO2'] | Products: ['C6H5O2', 'NO2'] | A: 4516605.57
R95: ARRHENIUS | Reactants: ['CL', 'HO2'] | Products: ['HCL', 'O2'] | A: 8430997.064
R96: ARRHENIUS | Reactants: ['PO2', 'HO2'] | Products: ['POOH', 'O2'] | A: 451660.55700000003
R97: ARRHENIUS | Reactants: ['PHENO2', 'HO2'] | Products: ['PHENOOH'] | A: 451660.55700000003
R98: ARRHENIUS | Reactants: ['MCO3', 'HO2'] | Products: ['O3', 'CH3COOH', 'CH3COOOH', 'OH', 'CO2', 'CH2O', 'CH3CO3'] | A: 258952.05268
R99: ARRHENIUS | Reactants: ['NO', 'C2H5O2'] | Products: ['CH3CHO', 'HO2', 'NO2'] | A: 1565756.5976
R100: ARRHENIUS | Reactants: ['O1D', 'CFC11'] | Products: ['CL', 'COFCL'] | A: 124658313.73200001
R101: ARRHENIUS | Reactants: ['CH3O2', 'C2H5O2'] | Products: ['CH2O', 'CH3CHO', 'HO2', 'CH3OH', 'C2H5OH'] | A: 120442.8152
R102: ARRHENIUS | Reactants: ['ISOPBO2', 'HO2'] | Products: ['ISOPOOH'] | A: 481771.2608
R103: ARRHENIUS | Reactants: ['OH', 'H2'] | Products: ['H2O', 'H'] | A: 1686199.4128
R104: ARRHENIUS | Reactants: ['H', 'HO2'] | Products: ['H2O', 'O'] | A: 963542.5216
R105: ARRHENIUS | Reactants: ['CH4', 'OH'] | Products: ['CH3O2', 'H2O'] | A: 1475424.4862
R106: ARRHENIUS | Reactants: ['ISOPO2VBS', 'NO'] | Products: ['NO', 'SOAG0', 'SOAG1', 'SOAG2', 'SOAG3', 'SOAG4'] | A: 1625978.0051999998
R107: ARRHENIUS | Reactants: ['OH', 'HO2'] | Products: ['H2O', 'O2'] | A: 28906275.648000002
R108: ARRHENIUS | Reactants: ['PHENO', 'NO2'] | Products: [] | A: 1264649.5596
R109: ARRHENIUS | Reactants: ['BRO'] | Products: ['BR', 'O2'] | A: 903321.1140000001
R110: ARRHENIUS | Reactants: ['OH', 'NC4CH2OH'] | Products: ['GLYALD', 'NOA', 'HO2'] | A: 42154985.32
R111: ARRHENIUS | Reactants: ['OH', 'CLO'] | Products: ['CL', 'HO2'] | A: 4456384.1624
R112: ARRHENIUS | Reactants: ['NO', 'NTERPO2'] | Products: ['TERPNIT', 'NO2', 'TERPROD1'] | A: 2529299.1192
R113: ARRHENIUS | Reactants: ['NO3', 'TERPROD1'] | Products: ['TERP2O2', 'NTERPO2'] | A: 602214.076
R114: ARRHENIUS | Reactants: ['S', 'O2'] | Products: ['SO', 'O'] | A: 1385092.3747999999
R115: ARRHENIUS | Reactants: ['C2H4', 'O3'] | Products: ['CO', 'OH', 'HO2', 'HCOOH', 'CH2O'] | A: 7226.568912
R116: ARRHENIUS | Reactants: ['ST80_25'] | Products: [] | A: 4.63e-07
R117: ARRHENIUS | Reactants: ['CLONO2', 'OH'] | Products: ['HOCL', 'NO3'] | A: 722656.8912
R118: ARRHENIUS | Reactants: ['O', 'OCS'] | Products: ['SO', 'CO'] | A: 12646495.595999999
R119: ARRHENIUS | Reactants: ['ISOPNO3', 'HO2'] | Products: ['ISOPNOOH'] | A: 481771.2608
R120: ARRHENIUS | Reactants: ['OH', 'MVK'] | Products: ['MACRO2'] | A: 2487144.13388
R121: ARRHENIUS | Reactants: ['ISOPBO2', 'CH3CO3'] | Products: ['HYDRALD', 'CH3O2', 'HO2'] | A: 8430997.064
R122: ARRHENIUS | Reactants: ['C2H5O2', 'HO2'] | Products: ['C2H5OOH', 'O2'] | A: 451660.55700000003
R123: ARRHENIUS | Reactants: ['H2402', 'O1D'] | Products: ['BR', 'COF2'] | A: 72265689.12
R124: ARRHENIUS | Reactants: ['ISOP', 'NO3'] | Products: ['ISOP', 'NO3', 'SOAG3', 'SOAG4'] | A: 1824708.65028
R125: ARRHENIUS | Reactants: ['OH', 'CH3OOH'] | Products: ['CH3O2', 'OH', 'CH2O', 'H2O'] | A: 2288413.4888
R126: ARRHENIUS | Reactants: ['O', 'NO2'] | Products: ['NO', 'O2'] | A: 3071291.7876
R127: ARRHENIUS | Reactants: ['MEKOOH', 'OH'] | Products: ['MEKO2'] | A: 2288413.4888
R128: ARRHENIUS | Reactants: ['NO', 'MCO3'] | Products: ['NO2', 'CH2O', 'CH3CO3'] | A: 3191734.6028
R129: ARRHENIUS | Reactants: ['NO', 'HO2'] | Products: ['NO2', 'OH'] | A: 2071616.42144
R130: ARRHENIUS | Reactants: ['OH', 'HCFC141B'] | Products: ['CL', 'COFCL'] | A: 752767.595
R131: ARRHENIUS | Reactants: ['BRO', 'CLO'] | Products: ['BR', 'CL', 'O2'] | A: 1385092.3747999999
R132: ARRHENIUS | Reactants: ['OH', 'ISOPNITA'] | Products: ['HYAC', 'GLYALD', 'NO2', 'CH2O', 'HONITR', 'HO2'] | A: 24088563.04
R133: ARRHENIUS | Reactants: ['NO', 'PO2'] | Products: ['CH3CHO', 'CH2O', 'HO2', 'NO2'] | A: 2529299.1192
R134: ARRHENIUS | Reactants: ['BENZO2VBS', 'HO2'] | Products: ['HO2', 'SOAG0', 'SOAG1', 'SOAG2', 'SOAG3', 'SOAG4'] | A: 451660.55700000003
R135: ARRHENIUS | Reactants: ['O3', 'HO2'] | Products: ['OH', 'O2'] | A: 6022.14076
R136: ARRHENIUS | Reactants: ['CHBR3', 'O1D'] | Products: ['BR'] | A: 278222903.112
R137: ARRHENIUS | Reactants: ['NO', 'MACRO2'] | Products: ['HONITR'] | A: 78287.82988
R138: ARRHENIUS | Reactants: ['O1D', 'CF3BR'] | Products: ['BR', 'F', 'COF2'] | A: 27099633.419999998
R139: ARRHENIUS | Reactants: ['BENZOOH', 'OH'] | Products: ['BENZO2'] | A: 2288413.4888
R140: ARRHENIUS | Reactants: ['NO', 'TERPO2'] | Products: ['TERPNIT', 'NO2', 'CH2O', 'CH3COCH3', 'TERPROD1', 'HO2'] | A: 2529299.1192
R141: ARRHENIUS | Reactants: ['OH', 'S'] | Products: ['SO', 'H'] | A: 39746129.016
R142: ARRHENIUS | Reactants: ['CH3COOOH', 'OH'] | Products: ['CH3CO3', 'CH2O', 'CO2', 'H2O'] | A: 602214.076
R143: ARRHENIUS | Reactants: ['O1D', 'O2'] | Products: ['O', 'O2'] | A: 19873064.508
R144: ARRHENIUS | Reactants: ['HNO3', 'OH'] | Products: ['NO3', 'H2O'] | A: 14453.137824
R145: ARRHENIUS | Reactants: ['CLO', 'HO2'] | Products: ['O2', 'HOCL'] | A: 1565756.5976
R146: ARRHENIUS | Reactants: ['NO', 'MDIALO2'] | Products: ['NO2', 'HO2', 'CH3COCHO', 'CO', 'CH3O2', 'GLYOXAL'] | A: 4516605.57
R147: ARRHENIUS | Reactants: ['H2O', 'F'] | Products: ['HF', 'OH'] | A: 8430997.064
R148: ARRHENIUS | Reactants: ['NO3', 'CH3COCHO'] | Products: ['HNO3', 'CO', 'CH3CO3'] | A: 843099.7064
R149: ARRHENIUS | Reactants: ['NO', 'N'] | Products: ['N2', 'O'] | A: 12646495.595999999
R150: ARRHENIUS | Reactants: ['CH3OH', 'OH'] | Products: ['HO2', 'CH2O'] | A: 1746420.8204
R151: ARRHENIUS | Reactants: ['CH3O2', 'XO2'] | Products: ['CH3OH', 'HO2', 'CH2O', 'CO', 'GLYOXAL', 'CH3COCHO', 'HYAC', 'GLYALD'] | A: 301107.038
R152: ARRHENIUS | Reactants: ['OH', 'PHENOOH'] | Products: ['PHENO2'] | A: 2288413.4888
R153: ARRHENIUS | Reactants: ['ISOPNO3', 'CH3CO3'] | Products: ['NC4CHO', 'CH3O2', 'HO2'] | A: 8430997.064
R154: ARRHENIUS | Reactants: ['NO', 'XYLENO2'] | Products: ['NO2', 'HO2', 'GLYOXAL', 'CH3COCHO', 'BIGALD1', 'BIGALD2', 'BIGALD3', 'BIGALD4'] | A: 1565756.5976
R155: ARRHENIUS | Reactants: ['OH', 'XYLOLOOH'] | Products: ['XYLOLO2'] | A: 2288413.4888
R156: ARRHENIUS | Reactants: ['OH', 'HYAC'] | Products: ['CH3COCHO', 'HO2'] | A: 1806642.2280000001
R157: ARRHENIUS | Reactants: ['NO3', 'CH2O'] | Products: ['CO', 'HO2', 'HNO3'] | A: 361328.4456
R158: ARRHENIUS | Reactants: ['MALO2', 'NO'] | Products: ['GLYOXAL', 'HO2', 'CO', 'NO2'] | A: 4516605.57
R159: ARRHENIUS | Reactants: ['ALKO2', 'HO2'] | Products: ['ALKOOH'] | A: 451660.55700000003
R160: ARRHENIUS | Reactants: ['OH', 'TERPNIT'] | Products: ['NO2', 'TERPROD1'] | A: 12044281.52
R161: ARRHENIUS | Reactants: ['HOCH2OO'] | Products: ['CH2O', 'HO2'] | A: 2400000000000.0
R162: ARRHENIUS | Reactants: ['BRO', 'CLO'] | Products: ['BRCL', 'O2'] | A: 246907.77116
R163: ARRHENIUS | Reactants: ['ISOPAO2', 'CH3O2'] | Products: ['CH3OH', 'HO2', 'CH2O', 'MACR', 'MVK'] | A: 301107.038
R164: ARRHENIUS | Reactants: ['O', 'H2O2'] | Products: ['OH', 'HO2'] | A: 843099.7064
R165: ARRHENIUS | Reactants: ['EO', 'O2'] | Products: ['GLYALD', 'HO2'] | A: 6022.14076
R166: ARRHENIUS | Reactants: ['N2O', 'O1D'] | Products: ['N2', 'O2'] | A: 27942733.1264
R167: ARRHENIUS | Reactants: ['OH', 'HPALD'] | Products: ['XO2'] | A: 11201181.8136
R168: ARRHENIUS | Reactants: ['HOBR', 'O'] | Products: ['BRO', 'OH'] | A: 72265689.12
R169: ARRHENIUS | Reactants: ['CH2O', 'HO2'] | Products: ['HOCH2OO'] | A: 5841.4765372
R170: ARRHENIUS | Reactants: ['ISOPNO3', 'NO3'] | Products: ['NC4CHO', 'NO2', 'HO2'] | A: 1445313.7824
R171: ARRHENIUS | Reactants: ['IVOC', 'OH'] | Products: ['OH', 'IVOCO2VBS'] | A: 8069668.6184
R172: ARRHENIUS | Reactants: ['NO3', 'HO2'] | Products: ['OH', 'NO2', 'O2'] | A: 2107749.266
R173: ARRHENIUS | Reactants: ['CH3CL', 'CL'] | Products: ['HO2', 'CO', 'HCL'] | A: 12224945.742800001
R174: ARRHENIUS | Reactants: ['CHBR3', 'OH'] | Products: ['BR'] | A: 541992.6684
R175: ARRHENIUS | Reactants: ['O1D', 'HCFC142B'] | Products: ['CL', 'COF2'] | A: 78287829.88
R176: ARRHENIUS | Reactants: ['CH3O2', 'CLO'] | Products: ['CL', 'HO2', 'CH2O'] | A: 1987306.4508
R177: ARRHENIUS | Reactants: ['CLO'] | Products: ['CL', 'OCLO'] | A: 210774.9266
R178: ARRHENIUS | Reactants: ['CL', 'HO2'] | Products: ['OH', 'CLO'] | A: 21679706.735999998
R179: ARRHENIUS | Reactants: ['NO', 'C3H7O2'] | Products: ['CH3COCH3', 'NO2', 'HO2', 'CH3CHO'] | A: 2529299.1192
R180: ARRHENIUS | Reactants: ['C2H5OH', 'OH'] | Products: ['HO2', 'CH3CHO'] | A: 4155277.1244
R181: ARRHENIUS | Reactants: ['O3', 'S'] | Products: ['SO', 'O2'] | A: 7226568.9120000005
R182: ARRHENIUS | Reactants: ['OH', 'ISOPOOH'] | Products: ['XO2', 'IEPOX', 'OH'] | A: 9153653.9552
R183: ARRHENIUS | Reactants: ['NO', 'RO2'] | Products: ['CH3CO3', 'CH2O', 'NO2'] | A: 1746420.8204
R184: ARRHENIUS | Reactants: ['OH', 'BZOOH'] | Products: ['BZOO'] | A: 2288413.4888
R185: ARRHENIUS | Reactants: ['O3', 'O1D'] | Products: ['O2'] | A: 72265689.12
R186: ARRHENIUS | Reactants: ['MALO2', 'HO2'] | Products: ['GLYOXAL', 'HO2', 'CO'] | A: 258952.05268
R187: ARRHENIUS | Reactants: ['NH_50'] | Products: [] | A: 2.31e-07
R188: ARRHENIUS | Reactants: ['O1D', 'N2'] | Products: ['O', 'N2'] | A: 12947602.634
R189: ARRHENIUS | Reactants: ['OH', 'XYLENES'] | Products: ['XYLOL', 'TEPOMUC', 'BZOO', 'XYLENO2', 'HO2'] | A: 10237639.292
R190: ARRHENIUS | Reactants: ['NO3', 'OH'] | Products: ['HO2', 'NO2'] | A: 13248709.672
R191: ARRHENIUS | Reactants: ['NO', 'IVOCO2VBS'] | Products: ['NO', 'SOAG0', 'SOAG1', 'SOAG2', 'SOAG3', 'SOAG4'] | A: 1565756.5976
R192: ARRHENIUS | Reactants: ['BCARYO2VBS', 'NO'] | Products: ['NO', 'SOAG0', 'SOAG1', 'SOAG2', 'SOAG3', 'SOAG4'] | A: 1625978.0051999998
R193: ARRHENIUS | Reactants: ['NO', 'EO2'] | Products: ['CH2O', 'HO2', 'EO', 'NO2'] | A: 2529299.1192
R194: ARRHENIUS | Reactants: ['O1D', 'HBR'] | Products: ['BRO', 'H'] | A: 18066422.28
R195: ARRHENIUS | Reactants: ['O', 'CLO'] | Products: ['CL', 'O2'] | A: 16861994.128
R196: ARRHENIUS | Reactants: ['CH4', 'CL'] | Products: ['CH3O2', 'HCL'] | A: 4275719.9396
R197: ARRHENIUS | Reactants: ['CH2BR2', 'CL'] | Products: ['BR', 'HCL'] | A: 3793948.6788000003
R198: ARRHENIUS | Reactants: ['OH', 'HOCL'] | Products: ['H2O', 'CLO'] | A: 1806642.2280000001
R199: ARRHENIUS | Reactants: ['NO3', 'CH3CHO'] | Products: ['CH3CO3', 'HNO3'] | A: 843099.7064
R200: ARRHENIUS | Reactants: ['MACRO2', 'HO2'] | Products: ['MACROOH'] | A: 481771.2608
R201: ARRHENIUS | Reactants: ['BR', 'HO2'] | Products: ['HBR', 'O2'] | A: 2890627.5648
R202: ARRHENIUS | Reactants: ['NO', 'MACRO2'] | Products: ['NO2', 'HO2', 'CH2O', 'GLYALD', 'CH3COCHO', 'CH3CO3', 'HYAC', 'CO'] | A: 1625978.0051999998
R203: ARRHENIUS | Reactants: ['ISOP', 'O3'] | Products: ['ISOP', 'O3', 'SOAG3'] | A: 6323.247797999999
R204: ARRHENIUS | Reactants: ['SO', 'OCLO'] | Products: ['SO2', 'CLO'] | A: 1144206.7444
R205: ARRHENIUS | Reactants: ['ACBZO2', 'HO2'] | Products: ['C6H5O2', 'OH'] | A: 258952.05268
R206: ARRHENIUS | Reactants: ['XYLEO2VBS', 'HO2'] | Products: ['HO2', 'SOAG0', 'SOAG1', 'SOAG2', 'SOAG3', 'SOAG4'] | A: 451660.55700000003
R207: ARRHENIUS | Reactants: ['BZALD', 'OH'] | Products: ['ACBZO2'] | A: 3553063.0484
R208: ARRHENIUS | Reactants: ['CH4', 'F'] | Products: ['HF', 'CH3O2'] | A: 96354252.16
R209: ARRHENIUS | Reactants: ['NH_5'] | Products: [] | A: 2.31e-06
R210: ARRHENIUS | Reactants: ['ISOPAO2', 'CH3CO3'] | Products: ['CH3O2', 'HO2', 'CH2O', 'MACR', 'MVK', 'CO2'] | A: 8430997.064
R211: ARRHENIUS | Reactants: ['CH3COCH3', 'OH'] | Products: ['RO2', 'H2O'] | A: 23004577.7032
R212: ARRHENIUS | Reactants: ['CH3COCH3', 'OH'] | Products: ['RO2', 'H2O'] | A: 80094.47210799999
R213: ARRHENIUS | Reactants: ['HO2NO2', 'OH'] | Products: ['H2O', 'NO2', 'O2'] | A: 270996.3342
R214: ARRHENIUS | Reactants: ['NO3', 'O'] | Products: ['NO2', 'O2'] | A: 7828782.988
R215: ARRHENIUS | Reactants: ['ALKO2', 'NO'] | Products: ['CH3CHO', 'CH2O', 'CH3COCH3', 'HO2', 'MEK', 'NO2'] | A: 4034834.3092
R216: ARRHENIUS | Reactants: ['ISOPNITB', 'OH'] | Products: ['HYAC', 'GLYALD', 'NOA', 'HO2', 'HONITR'] | A: 24088563.04
R217: ARRHENIUS | Reactants: ['OH', 'XYLOL'] | Products: ['XYLOLO2', 'HO2', 'PHENO'] | A: 50585982.383999996
R218: ARRHENIUS | Reactants: ['SO', 'OH'] | Products: ['SO2', 'H'] | A: 15657565.976
R219: ARRHENIUS | Reactants: ['MCO3', 'CH3CO3'] | Products: ['CO2', 'CH3O2', 'CH2O', 'CH3CO3'] | A: 2770184.7495999997
R220: ARRHENIUS | Reactants: ['OH', 'XYLENES'] | Products: ['XYLENES', 'OH', 'XYLEO2VBS'] | A: 10237639.292
R221: ARRHENIUS | Reactants: ['HOCL', 'CL'] | Products: ['HCL', 'CLO'] | A: 2047527.8584
R222: ARRHENIUS | Reactants: ['CRESOL', 'OH'] | Products: ['PHENO2', 'HO2', 'PHENO'] | A: 28304061.572
R223: ARRHENIUS | Reactants: ['OH', 'CH3COOH'] | Products: ['CH3O2', 'CO2', 'H2O'] | A: 18969.743393999997
R224: ARRHENIUS | Reactants: ['OH'] | Products: ['H2O', 'O'] | A: 1083985.3368
R225: ARRHENIUS | Reactants: ['CLO'] | Products: ['CL', 'O2'] | A: 18066422.28
R226: ARRHENIUS | Reactants: ['XO2', 'CH3CO3'] | Products: ['CO', 'CH2O', 'GLYOXAL', 'CH3O2', 'HO2', 'CH3COCHO', 'HYAC', 'GLYALD', 'CO2'] | A: 782878.2988
R227: ARRHENIUS | Reactants: ['NO3', 'XO2'] | Products: ['NO2', 'HO2', 'CO', 'HYAC', 'GLYOXAL', 'CH3COCHO', 'GLYALD'] | A: 1445313.7824
R228: ARRHENIUS | Reactants: ['TERP2O2', 'NO'] | Products: ['ONITR', 'NO2', 'CH2O', 'CH3COCH3', 'CO', 'CO2', 'TERPROD2', 'HO2', 'GLYALD'] | A: 2529299.1192
R229: ARRHENIUS | Reactants: ['CH3BR', 'OH'] | Products: ['BR', 'H2O', 'HO2'] | A: 855143.98792
R230: ARRHENIUS | Reactants: ['OH', 'GLYALD'] | Products: ['HO2', 'GLYOXAL', 'CH2O', 'CO2'] | A: 6022140.76
R231: ARRHENIUS | Reactants: ['NTERPO2', 'HO2'] | Products: ['NTERPOOH'] | A: 451660.55700000003
R232: ARRHENIUS | Reactants: ['OH', 'POOH'] | Products: ['PO2', 'OH', 'HYAC', 'H2O'] | A: 2288413.4888
R233: ARRHENIUS | Reactants: ['O1D', 'CF2CLBR'] | Products: ['CL', 'BR', 'COF2'] | A: 58715872.41
R234: ARRHENIUS | Reactants: ['RO2', 'HO2'] | Products: ['ROOH', 'OH', 'CH2O', 'CH3CO3'] | A: 517904.10536
R235: ARRHENIUS | Reactants: ['NO3', 'MACRO2'] | Products: ['NO2', 'HO2', 'CH2O', 'CH3COCHO', 'CO', 'GLYALD', 'HYAC', 'CH3CO3'] | A: 1445313.7824
R236: ARRHENIUS | Reactants: ['CH3O2', 'NTERPO2'] | Products: ['TERPNIT', 'CH2O', 'CH3OH', 'HO2', 'TERPROD1', 'NO2'] | A: 1204428.152
R237: ARRHENIUS | Reactants: ['MACROOH', 'OH'] | Products: ['MCO3', 'MACRO2', 'OH', 'HO2'] | A: 13850923.748000002
R238: ARRHENIUS | Reactants: ['MEKO2', 'HO2'] | Products: ['MEKOOH', 'OH', 'CH3CHO', 'CH3CO3'] | A: 451660.55700000003
R239: ARRHENIUS | Reactants: ['SO', 'O3'] | Products: ['SO2', 'O2'] | A: 2047527.8584
R240: ARRHENIUS | Reactants: ['BENZENE', 'OH'] | Products: ['BENZENE', 'OH', 'BENZO2VBS'] | A: 1385092.3747999999
R241: ARRHENIUS | Reactants: ['PAN', 'OH'] | Products: ['CH2O', 'NO3'] | A: 24088.56304
R242: ARRHENIUS | Reactants: ['TERPO2', 'HO2'] | Products: ['TERPOOH'] | A: 451660.55700000003
R243: ARRHENIUS | Reactants: ['NO3', 'MCO3'] | Products: ['NO2', 'CH2O', 'CH3CO3'] | A: 3011070.38
R244: ARRHENIUS | Reactants: ['O3', 'CL'] | Products: ['CLO', 'O2'] | A: 13850923.748000002
R245: ARRHENIUS | Reactants: ['NO3', 'NO'] | Products: ['NO2'] | A: 10237639.292
R246: ARRHENIUS | Reactants: ['EO2', 'HO2'] | Products: ['EOOH'] | A: 451660.55700000003
R247: ARRHENIUS | Reactants: ['CH3CN', 'OH'] | Products: ['HO2'] | A: 469726.97928
R248: ARRHENIUS | Reactants: ['OH', 'O3'] | Products: ['HO2', 'O2'] | A: 1023763.9292
R249: ARRHENIUS | Reactants: ['O3', 'NO2'] | Products: ['NO3', 'O2'] | A: 72265.68912
R250: ARRHENIUS | Reactants: ['CL', 'H2'] | Products: ['HCL', 'H'] | A: 18367529.318
R251: ARRHENIUS | Reactants: ['O3', 'C3H6'] | Products: ['CH2O', 'HCOOH', 'CH3COOH', 'CH3CHO', 'CO', 'CH3O2', 'CH4', 'CO2', 'HO2', 'OH'] | A: 3914.391494
R252: ARRHENIUS | Reactants: ['C6H5O2', 'NO'] | Products: ['PHENO', 'NO2'] | A: 1565756.5976
R253: ARRHENIUS | Reactants: ['NO3', 'ISOPBO2'] | Products: ['NO2', 'HYDRALD', 'HO2', 'GLYOXAL', 'GLYALD', 'CH3COCHO', 'HYAC'] | A: 1445313.7824
R254: ARRHENIUS | Reactants: ['N2O', 'O1D'] | Products: ['NO'] | A: 43720741.9176
R255: ARRHENIUS | Reactants: ['OH', 'NC4CHO'] | Products: ['GLYOXAL', 'NOA', 'HO2'] | A: 60221407.6
R256: ARRHENIUS | Reactants: ['NO', 'MTERPO2VBS'] | Products: ['NO', 'SOAG0', 'SOAG1', 'SOAG2', 'SOAG3', 'SOAG4'] | A: 1625978.0051999998
R257: ARRHENIUS | Reactants: ['NO', 'XYLEO2VBS'] | Products: ['NO', 'SOAG0', 'SOAG1', 'SOAG2', 'SOAG3', 'SOAG4'] | A: 1565756.5976
R258: ARRHENIUS | Reactants: ['OH', 'BRO'] | Products: ['BR', 'HO2'] | A: 10237639.292
R259: ARRHENIUS | Reactants: ['NO', 'BRO'] | Products: ['BR', 'NO2'] | A: 5299483.868799999
R260: ARRHENIUS | Reactants: ['HO2'] | Products: ['H2O2', 'O2'] | A: 180664.2228
R261: ARRHENIUS | Reactants: ['HO2', 'M'] | Products: ['H2O2', 'O2', 'M'] | A: 761.5897659983209
R262: ARRHENIUS | Reactants: ['HO2', 'H2O'] | Products: ['H2O2', 'O2', 'H2O'] | A: 152.3179531996642
R263: ARRHENIUS | Reactants: ['HO2', 'M', 'H2O'] | Products: ['H2O2', 'O2', 'M', 'H2O'] | A: 0.642096108110429
R264: ARRHENIUS | Reactants: ['NO3', 'C3H6'] | Products: ['NOA'] | A: 277018.47495999996
R265: ARRHENIUS | Reactants: ['BCARY', 'NO3'] | Products: ['NTERPO2'] | A: 11442067.444
R266: ARRHENIUS | Reactants: ['BCARY', 'O3'] | Products: ['TERPROD1', 'TERPROD2', 'OH', 'HO2', 'CO', 'CO2', 'CH3COCH3', 'CH2O', 'BIGALD', 'HCOOH', 'BIGALK', 'CH3CO3', 'RO2'] | A: 7226.568912
R267: ARRHENIUS | Reactants: ['OH', 'HCFC22'] | Products: ['H2O', 'CL', 'COF2'] | A: 554036.9499199999
R268: ARRHENIUS | Reactants: ['O3', 'O1D'] | Products: ['O2', 'O'] | A: 72265689.12
R269: ARRHENIUS | Reactants: ['C2H5OOH', 'OH'] | Products: ['C2H5O2', 'CH3CHO', 'OH'] | A: 2288413.4888
R270: ARRHENIUS | Reactants: ['C2H5O2'] | Products: ['CH3CHO', 'HO2', 'C2H5OH'] | A: 40950.557168
R271: ARRHENIUS | Reactants: ['OH', 'N'] | Products: ['NO', 'H'] | A: 30110703.8
R272: ARRHENIUS | Reactants: ['NO', 'XO2'] | Products: ['NO2', 'HO2', 'CO', 'CH2O', 'GLYOXAL', 'CH3COCHO', 'HYAC', 'GLYALD'] | A: 1625978.0051999998
R273: ARRHENIUS | Reactants: ['CFC115', 'O1D'] | Products: ['CL', 'F', 'COF2'] | A: 27966821.689439997
R274: ARRHENIUS | Reactants: ['CH3CO3', 'HO2'] | Products: ['CH3COOOH', 'CH3COOH', 'O3', 'OH', 'CH3O2'] | A: 258952.05268
R275: ARRHENIUS | Reactants: ['OH', 'PHENOL'] | Products: ['PHENO2', 'HO2', 'PHENO'] | A: 283040.61572
R276: ARRHENIUS | Reactants: ['HCN', 'O1D'] | Products: ['OH'] | A: 65039120.208000004
R277: ARRHENIUS | Reactants: ['ISOPNOOH', 'OH'] | Products: ['NOA', 'HO2'] | A: 24088563.04
R278: ARRHENIUS | Reactants: ['N', 'NO2'] | Products: ['N2O', 'O'] | A: 1746420.8204
R279: ARRHENIUS | Reactants: ['O1D', 'HBR'] | Products: ['BR', 'OH'] | A: 54199266.839999996
R280: ARRHENIUS | Reactants: ['HNO3', 'F'] | Products: ['HF', 'NO3'] | A: 3613284.4560000002
R281: ARRHENIUS | Reactants: ['OH', 'C3H8'] | Products: ['C3H7O2', 'H2O'] | A: 5534347.35844
R282: ARRHENIUS | Reactants: ['CH4', 'O1D'] | Products: ['CH2O', 'H', 'HO2'] | A: 21077492.66
R283: ARRHENIUS | Reactants: ['HCL', 'O'] | Products: ['CL', 'OH'] | A: 6022140.76
R284: ARRHENIUS | Reactants: ['HCOOH', 'OH'] | Products: ['HO2', 'CO2', 'H2O'] | A: 240885.6304
R285: ARRHENIUS | Reactants: ['BR', 'CH2O'] | Products: ['HBR', 'HO2', 'CO'] | A: 10237639.292
R286: ARRHENIUS | Reactants: ['BRO', 'HO2'] | Products: ['HOBR', 'O2'] | A: 2709963.3419999997
R287: ARRHENIUS | Reactants: ['CH3O2', 'HO2'] | Products: ['CH3OOH', 'O2'] | A: 246907.77116
R288: ARRHENIUS | Reactants: ['ISOPNO3', 'NO'] | Products: ['NC4CHO', 'NO2', 'HO2'] | A: 1625978.0051999998
R289: ARRHENIUS | Reactants: ['O', 'M'] | Products: ['O2', 'M'] | A: 100.09465495977932
R290: ARRHENIUS | Reactants: ['O3', 'MTERP'] | Products: ['TERPROD1', 'TERPROD2', 'OH', 'HO2', 'CO', 'CO2', 'CH3COCH3', 'CH2O', 'BIGALD', 'HCOOH', 'BIGALK', 'CH3CO3', 'RO2'] | A: 379.39486788
R291: ARRHENIUS | Reactants: ['CL', 'H2O2'] | Products: ['HCL', 'HO2'] | A: 6624354.836
R292: ARRHENIUS | Reactants: ['OH', 'NOA'] | Products: ['NO2', 'CH3COCHO'] | A: 403483.43091999996
R293: ARRHENIUS | Reactants: ['OH', 'OCS'] | Products: ['SO2', 'CO', 'H'] | A: 43359.413472
R294: ARRHENIUS | Reactants: ['OH', 'TERPOOH'] | Products: ['TERPO2'] | A: 19873064.508
R295: ARRHENIUS | Reactants: ['BIGALK', 'OH'] | Products: ['ALKO2'] | A: 2107749.266
R296: ARRHENIUS | Reactants: ['BR', 'O3'] | Products: ['BRO', 'O2'] | A: 9635425.216
R297: ARRHENIUS | Reactants: ['BENZENE', 'OH'] | Products: ['PHENOL', 'BEPOMUC', 'HO2', 'BENZO2'] | A: 1385092.3747999999
R298: ARRHENIUS | Reactants: ['CH3O2', 'MACRO2'] | Products: ['HO2', 'CH2O', 'CO', 'CH3COCHO', 'GLYALD', 'CH3CO3', 'CH3OH', 'HYAC'] | A: 301107.038
R299: ARRHENIUS | Reactants: ['ISOPAO2', 'HO2'] | Products: ['ISOPOOH'] | A: 481771.2608
R300: ARRHENIUS | Reactants: ['H2O', 'SO3'] | Products: ['H2SO4', 'H2O'] | A: 3.082625243326537e-05
R301: ARRHENIUS | Reactants: ['NTERPOOH', 'OH'] | Products: ['NTERPO2'] | A: 12044281.52
R302: ARRHENIUS | Reactants: ['CH3O2', 'NO'] | Products: ['CH2O', 'NO2', 'HO2'] | A: 1686199.4128
R303: ARRHENIUS | Reactants: ['ISOPAO2', 'NO3'] | Products: ['NO2', 'MACR', 'MVK', 'CH2O', 'HO2'] | A: 1445313.7824
R304: ARRHENIUS | Reactants: ['BZOO', 'HO2'] | Products: ['BZOOH'] | A: 451660.55700000003
R305: ARRHENIUS | Reactants: ['NO', 'TOLUO2VBS'] | Products: ['NO', 'SOAG0', 'SOAG1', 'SOAG2', 'SOAG3', 'SOAG4'] | A: 1565756.5976
R306: ARRHENIUS | Reactants: ['MTERPO2VBS', 'HO2'] | Products: ['HO2', 'SOAG0', 'SOAG1', 'SOAG2', 'SOAG3', 'SOAG4'] | A: 156575.65976
R307: ARRHENIUS | Reactants: ['NO', 'MEKO2'] | Products: ['CH3CO3', 'CH3CHO', 'NO2'] | A: 2529299.1192
R308: ARRHENIUS | Reactants: ['XYLENO2', 'HO2'] | Products: ['XYLENOOH'] | A: 451660.55700000003
R309: ARRHENIUS | Reactants: ['NO', 'DICARBO2'] | Products: ['NO2', 'HO2', 'CH3COCHO', 'CO', 'CH3O2'] | A: 4516605.57
R310: ARRHENIUS | Reactants: ['TERP2O2', 'HO2'] | Products: ['TERP2OOH'] | A: 451660.55700000003
R311: ARRHENIUS | Reactants: ['HCL', 'O1D'] | Products: ['CLO', 'H'] | A: 1987306.4508
R312: ARRHENIUS | Reactants: ['BCARY', 'O3'] | Products: ['BCARY', 'O3', 'SOAG0', 'SOAG1', 'SOAG2', 'SOAG3', 'SOAG4'] | A: 7226.568912
R313: ARRHENIUS | Reactants: ['CH3O2', 'RO2'] | Products: ['CH3CO3', 'CH2O', 'HO2', 'HYAC', 'CH3COCHO', 'CH3OH'] | A: 427571.99396
R314: ARRHENIUS | Reactants: ['XYLOLO2', 'HO2'] | Products: ['XYLOLOOH'] | A: 451660.55700000003
R315: ARRHENIUS | Reactants: ['BCARY', 'NO3'] | Products: ['BCARY', 'NO3', 'SOAG3', 'SOAG4'] | A: 11442067.444
R316: ARRHENIUS | Reactants: ['O1D', 'CCL4'] | Products: ['CL'] | A: 156997209.61319998
R317: ARRHENIUS | Reactants: ['DICARBO2', 'HO2'] | Products: ['OH', 'HO2', 'CH3COCHO', 'CO', 'CH3O2'] | A: 258952.05268
R318: ARRHENIUS | Reactants: ['OH', 'ROOH'] | Products: ['RO2', 'H2O'] | A: 2288413.4888
R319: ARRHENIUS | Reactants: ['EO'] | Products: ['CH2O', 'HO2'] | A: 160000000000.0
R320: ARRHENIUS | Reactants: ['ISOP', 'O3'] | Products: ['MACR', 'MVK', 'HCOOH', 'CO', 'OH', 'HO2', 'CH2O', 'CH3CO3', 'C3H6', 'CH3O2'] | A: 6323.247797999999
R321: ARRHENIUS | Reactants: ['NO', 'ENEO2'] | Products: ['HONITR'] | A: 30712.917876
R322: ARRHENIUS | Reactants: ['ISOP', 'NO3'] | Products: ['ISOPNO3'] | A: 1824708.65028
R323: ARRHENIUS | Reactants: ['CH4', 'O1D'] | Products: ['CH3O2', 'OH'] | A: 78890043.95600002
R324: ARRHENIUS | Reactants: ['BIGENE', 'NO3'] | Products: ['NO2', 'CH3CHO', 'CH2O', 'CH3COCH3'] | A: 210774.9266
R325: ARRHENIUS | Reactants: ['NO3', 'NTERPO2'] | Products: ['NO2', 'TERPROD1'] | A: 1445313.7824
R326: ARRHENIUS | Reactants: ['NH4'] | Products: [] | A: 6.34e-08
R327: ARRHENIUS | Reactants: ['ISOPBO2'] | Products: ['HPALD', 'HO2'] | A: 1600000000.0
R328: ARRHENIUS | Reactants: ['BENZO2', 'HO2'] | Products: ['BENZOOH'] | A: 451660.55700000003
R329: ARRHENIUS | Reactants: ['OH', 'ALKNIT'] | Products: ['CH2O', 'CH3CHO', 'CH3COCH3', 'NO2'] | A: 963542.5216
R330: ARRHENIUS | Reactants: ['CH3BR', 'CL'] | Products: ['HCL', 'HO2', 'BR'] | A: 8792325.5096
R331: ARRHENIUS | Reactants: ['OH', 'TERPROD2'] | Products: ['RO2', 'CH2O', 'CO2', 'CH3COCH3', 'CH3CO3', 'HO2', 'CO'] | A: 20475278.584
R332: ARRHENIUS | Reactants: ['NO', 'XYLOLO2'] | Products: ['HO2', 'NO2', 'GLYOXAL', 'CH3COCHO'] | A: 1565756.5976
R333: ARRHENIUS | Reactants: ['OH', 'HYDRALD'] | Products: ['XO2'] | A: 11201181.8136
R334: ARRHENIUS | Reactants: ['TERP2O2', 'CH3O2'] | Products: ['TERPROD2', 'CH2O', 'CH3OH', 'HO2', 'CO2', 'CO', 'GLYALD', 'CH3COCH3'] | A: 1204428.152
R335: ARRHENIUS | Reactants: ['OH', 'CH2O'] | Products: ['CO', 'H2O', 'H'] | A: 3312177.418
R336: ARRHENIUS | Reactants: ['O', 'BRONO2'] | Products: ['BRO', 'NO3'] | A: 11442067.444
R337: ARRHENIUS | Reactants: ['O3', 'MVK'] | Products: ['CH2O', 'CO', 'CH3CHO', 'CO2', 'CH3CO3', 'CH3COCHO', 'HO2', 'OH', 'HCOOH'] | A: 511.8819646
R338: ARRHENIUS | Reactants: ['CL', 'CH2O'] | Products: ['HCL', 'HO2', 'CO'] | A: 48779340.156
R339: ARRHENIUS | Reactants: ['CH3O2'] | Products: ['CH2O', 'HO2'] | A: 301107.038
R340: ARRHENIUS | Reactants: ['TOLUENE', 'OH'] | Products: ['CRESOL', 'TEPOMUC', 'BZOO', 'TOLO2', 'HO2'] | A: 1023763.9292
R341: ARRHENIUS | Reactants: ['CLO'] | Products: ['CL2', 'O2'] | A: 602214.076
R342: ARRHENIUS | Reactants: ['IVOCO2VBS', 'HO2'] | Products: ['HO2', 'SOAG0', 'SOAG1', 'SOAG2', 'SOAG3', 'SOAG4'] | A: 451660.55700000003
R343: ARRHENIUS | Reactants: ['NO', 'O3'] | Products: ['NO2', 'O2'] | A: 1806642.2280000001
R344: ARRHENIUS | Reactants: ['TERP2OOH', 'OH'] | Products: ['TERP2O2'] | A: 13850923.748000002
R345: ARRHENIUS | Reactants: ['BRO', 'CLO'] | Products: ['BR', 'OCLO'] | A: 572103.3722
R346: ARRHENIUS | Reactants: ['CH2BR2', 'OH'] | Products: ['BR', 'H2O'] | A: 1204428.152
R347: ARRHENIUS | Reactants: ['OH', 'H2O2'] | Products: ['H2O', 'HO2'] | A: 1083985.3368
R348: ARRHENIUS | Reactants: ['H', 'HO2'] | Products: ['OH'] | A: 43359413.471999995
R349: ARRHENIUS | Reactants: ['HCL', 'OH'] | Products: ['H2O', 'CL'] | A: 1083985.3368
R350: ARRHENIUS | Reactants: ['CFC113', 'O1D'] | Products: ['CL', 'COFCL', 'COF2'] | A: 125742299.0688
R351: ARRHENIUS | Reactants: ['CH3O2'] | Products: ['CH2O', 'CH3OH'] | A: 11442.067444
R352: ARRHENIUS | Reactants: ['F', 'H2'] | Products: ['HF', 'H'] | A: 84309970.64
R353: ARRHENIUS | Reactants: ['NH3', 'OH'] | Products: ['H2O'] | A: 1023763.9292
R354: ARRHENIUS | Reactants: ['CHBR3', 'CL'] | Products: ['BR', 'HCL'] | A: 2920738.2686
R355: ARRHENIUS | Reactants: ['CLONO2', 'O'] | Products: ['CLO', 'NO3'] | A: 2167970.6736
R356: ARRHENIUS | Reactants: ['ISOPAO2', 'NO'] | Products: ['ISOPNITA', 'NO2', 'MACR', 'MVK', 'CH2O', 'HO2'] | A: 2649741.9343999997
R357: ARRHENIUS | Reactants: ['O', 'H2'] | Products: ['OH', 'H'] | A: 9635425.216
R358: ARRHENIUS | Reactants: ['O', 'HBR'] | Products: ['BR', 'OH'] | A: 3492841.6408
R359: ARRHENIUS | Reactants: ['BIGENE', 'OH'] | Products: ['ENEO2'] | A: 32519560.104000002
R360: ARRHENIUS | Reactants: ['TOLO2', 'HO2'] | Products: ['TOLOOH'] | A: 451660.55700000003
R361: ARRHENIUS | Reactants: ['CLONO2', 'CL'] | Products: ['CL2', 'NO3'] | A: 3914391.494
R362: SURFACE | Reactants: [] | Products: [] | A: N/A
R363: SURFACE | Reactants: [] | Products: [] | A: N/A
R364: SURFACE | Reactants: [] | Products: [] | A: N/A
R365: SURFACE | Reactants: [] | Products: [] | A: N/A
R366: SURFACE | Reactants: [] | Products: [] | A: N/A
R367: SURFACE | Reactants: [] | Products: [] | A: N/A
R368: SURFACE | Reactants: [] | Products: [] | A: N/A
R369: SURFACE | Reactants: [] | Products: [] | A: N/A
R370: SURFACE | Reactants: [] | Products: [] | A: N/A
R371: SURFACE | Reactants: [] | Products: [] | A: N/A
R372: SURFACE | Reactants: [] | Products: [] | A: N/A
R373: SURFACE | Reactants: [] | Products: [] | A: N/A
R374: SURFACE | Reactants: [] | Products: [] | A: N/A
R375: TROE | Reactants: ['C2H2', 'OH'] | Products: ['GLYOXAL', 'OH', 'HCOOH', 'HO2', 'CO'] | A: N/A
R376: TROE | Reactants: ['PAN'] | Products: ['CH3CO3', 'NO2'] | A: N/A
R377: TROE | Reactants: ['CL2O2'] | Products: ['CLO'] | A: N/A
R378: TROE | Reactants: ['MDIALO2', 'NO2'] | Products: [] | A: N/A
R379: TROE | Reactants: ['OH', 'HCN'] | Products: ['HO2'] | A: N/A
R380: TROE | Reactants: ['SO2', 'OH'] | Products: ['SO3', 'HO2'] | A: N/A
R381: TROE | Reactants: ['OH', 'NO2'] | Products: ['HNO3'] | A: N/A
R382: TROE | Reactants: ['CLO', 'NO2'] | Products: ['CLONO2'] | A: N/A
R383: TROE | Reactants: ['OH', 'C3H6'] | Products: ['PO2'] | A: N/A
R384: TROE | Reactants: ['N2O5'] | Products: ['NO2', 'NO3'] | A: N/A
R385: TROE | Reactants: ['CLO'] | Products: ['CL2O2'] | A: N/A
R386: TROE | Reactants: ['C2H4', 'OH'] | Products: ['EO2'] | A: N/A
R387: TROE | Reactants: ['O2', 'H'] | Products: ['HO2'] | A: N/A
R388: TROE | Reactants: ['MALO2', 'NO2'] | Products: [] | A: N/A
R389: TROE | Reactants: ['ACBZO2', 'NO2'] | Products: ['PBZNIT'] | A: N/A
R390: TROE | Reactants: ['HNO3', 'OH'] | Products: ['NO3', 'H2O'] | A: N/A
R391: TROE | Reactants: ['C2H2', 'CL'] | Products: ['CL'] | A: N/A
R392: TROE | Reactants: ['MCO3', 'NO2'] | Products: ['MPAN'] | A: N/A
R393: TROE | Reactants: ['CH3CO3', 'NO2'] | Products: ['PAN'] | A: N/A
R394: TROE | Reactants: ['OH', 'MPAN'] | Products: ['HYAC', 'NO3', 'CH2O', 'HO2', 'CO2'] | A: N/A
R395: TROE | Reactants: ['PBZNIT'] | Products: ['ACBZO2', 'NO2'] | A: N/A
R396: TROE | Reactants: ['NO', 'O'] | Products: ['NO2'] | A: N/A
R397: TROE | Reactants: ['NO2', 'HO2'] | Products: ['HO2NO2'] | A: N/A
R398: TROE | Reactants: ['HO2NO2'] | Products: ['HO2', 'NO2'] | A: N/A
R399: TROE | Reactants: ['BRO', 'NO2'] | Products: ['BRONO2'] | A: N/A
R400: TROE | Reactants: ['C2H4', 'CL'] | Products: ['CL'] | A: N/A
R401: TROE | Reactants: ['OH'] | Products: ['H2O2'] | A: N/A
R402: TROE | Reactants: ['DICARBO2', 'NO2'] | Products: [] | A: N/A
R403: TROE | Reactants: ['MPAN'] | Products: ['MCO3', 'NO2'] | A: N/A
R404: TROE | Reactants: ['NO2', 'O'] | Products: ['NO3'] | A: N/A
R405: TROE | Reactants: ['NO3', 'NO2'] | Products: ['N2O5'] | A: N/A
R406: PHOTOLYSIS | Reactants: ['TERPNIT'] | Products: ['TERPROD1', 'NO2', 'HO2'] | A: 1.0
R407: PHOTOLYSIS | Reactants: ['O2'] | Products: ['O'] | A: 1.0
R408: PHOTOLYSIS | Reactants: ['CH3COCHO'] | Products: ['CH3CO3', 'CO', 'HO2'] | A: 1.0
R409: PHOTOLYSIS | Reactants: ['XYLENOOH'] | Products: ['OH', 'HO2', 'GLYOXAL', 'CH3COCHO', 'BIGALD1', 'BIGALD2', 'BIGALD3', 'BIGALD4'] | A: 1.0
R410: PHOTOLYSIS | Reactants: ['CH4'] | Products: ['H2', 'CH2O', 'O', 'OH', 'H', 'CO2', 'CO', 'H2O'] | A: 1.0
R411: PHOTOLYSIS | Reactants: ['TERP2OOH'] | Products: ['OH', 'CH2O', 'CH3COCH3', 'CO', 'CO2', 'TERPROD2', 'HO2', 'GLYALD'] | A: 1.0
R412: PHOTOLYSIS | Reactants: ['BRONO2'] | Products: ['BR', 'NO3'] | A: 1.0
R413: PHOTOLYSIS | Reactants: ['BIGALD4'] | Products: ['HO2', 'CO', 'CH3COCHO', 'CH3CO3'] | A: 1.0
R414: PHOTOLYSIS | Reactants: ['soa3_a2'] | Products: [] | A: 1.0
R415: PHOTOLYSIS | Reactants: ['BRO'] | Products: ['BR', 'O'] | A: 1.0
R416: PHOTOLYSIS | Reactants: ['TEPOMUC'] | Products: ['CH3CO3', 'HO2', 'CO'] | A: 1.0
R417: PHOTOLYSIS | Reactants: ['COF2'] | Products: ['F'] | A: 1.0
R418: PHOTOLYSIS | Reactants: ['CH2O'] | Products: ['CO', 'H2'] | A: 1.0
R419: PHOTOLYSIS | Reactants: ['BRONO2'] | Products: ['BRO', 'NO2'] | A: 1.0
R420: PHOTOLYSIS | Reactants: ['NO'] | Products: ['N', 'O'] | A: 1.0
R421: PHOTOLYSIS | Reactants: ['H2O'] | Products: ['H2', 'O1D'] | A: 1.0
R422: PHOTOLYSIS | Reactants: ['C3H7OOH'] | Products: ['CH3COCH3', 'OH', 'HO2'] | A: 1.0
R423: PHOTOLYSIS | Reactants: ['CFC113'] | Products: ['CL', 'COFCL', 'COF2'] | A: 1.0
R424: PHOTOLYSIS | Reactants: ['CCL4'] | Products: ['CL'] | A: 1.0
R425: PHOTOLYSIS | Reactants: ['NOA'] | Products: ['NO2', 'CH2O', 'CH3CO3'] | A: 1.0
R426: PHOTOLYSIS | Reactants: ['H2SO4'] | Products: ['SO3', 'H2O'] | A: 1.0
R427: PHOTOLYSIS | Reactants: ['MACR'] | Products: ['HO2', 'CO'] | A: 1.0
R428: PHOTOLYSIS | Reactants: ['NTERPOOH'] | Products: ['TERPROD1', 'NO2', 'OH'] | A: 1.0
R429: PHOTOLYSIS | Reactants: ['ROOH'] | Products: ['CH3CO3', 'CH2O', 'OH'] | A: 1.0
R430: PHOTOLYSIS | Reactants: ['HBR'] | Products: ['BR', 'H'] | A: 1.0
R431: PHOTOLYSIS | Reactants: ['POOH'] | Products: ['CH3CHO', 'CH2O', 'HO2', 'OH'] | A: 1.0
R432: PHOTOLYSIS | Reactants: ['soa2_a2'] | Products: [] | A: 1.0
R433: PHOTOLYSIS | Reactants: ['HYAC'] | Products: ['CH3CO3', 'HO2', 'CH2O'] | A: 1.0
R434: PHOTOLYSIS | Reactants: ['HCFC142B'] | Products: ['CL', 'COF2'] | A: 1.0
R435: PHOTOLYSIS | Reactants: ['H2O2'] | Products: ['OH'] | A: 1.0
R436: PHOTOLYSIS | Reactants: ['OCLO'] | Products: ['O', 'CLO'] | A: 1.0
R437: PHOTOLYSIS | Reactants: ['soa5_a2'] | Products: [] | A: 1.0
R438: PHOTOLYSIS | Reactants: ['MACR'] | Products: ['HO2', 'MCO3', 'CH2O', 'CH3CO3'] | A: 1.0
R439: PHOTOLYSIS | Reactants: ['BENZOOH'] | Products: ['OH', 'GLYOXAL', 'BIGALD1', 'HO2'] | A: 1.0
R440: PHOTOLYSIS | Reactants: ['N2O5'] | Products: ['NO', 'O', 'NO3'] | A: 1.0
R441: PHOTOLYSIS | Reactants: ['SO'] | Products: ['S', 'O'] | A: 1.0
R442: PHOTOLYSIS | Reactants: ['ISOPNOOH'] | Products: ['NO2', 'HO2', 'ISOPOOH'] | A: 1.0
R443: PHOTOLYSIS | Reactants: ['ALKOOH'] | Products: ['CH3CHO', 'CH2O', 'CH3COCH3', 'HO2', 'MEK', 'OH'] | A: 1.0
R444: PHOTOLYSIS | Reactants: ['soa1_a1'] | Products: [] | A: 1.0
R445: PHOTOLYSIS | Reactants: ['EOOH'] | Products: ['EO', 'OH'] | A: 1.0
R446: PHOTOLYSIS | Reactants: ['BRCL'] | Products: ['BR', 'CL'] | A: 1.0
R447: PHOTOLYSIS | Reactants: ['ISOPOOH'] | Products: ['MVK', 'MACR', 'OH', 'CH2O', 'HO2'] | A: 1.0
R448: PHOTOLYSIS | Reactants: ['C6H5OOH'] | Products: ['PHENO', 'OH'] | A: 1.0
R449: PHOTOLYSIS | Reactants: ['CFC114'] | Products: ['CL', 'COF2'] | A: 1.0
R450: PHOTOLYSIS | Reactants: ['HO2NO2'] | Products: ['NO2', 'HO2'] | A: 1.0
R451: PHOTOLYSIS | Reactants: ['PAN'] | Products: ['CH3CO3', 'NO2', 'CH3O2', 'NO3', 'CO2'] | A: 1.0
R452: PHOTOLYSIS | Reactants: ['O3'] | Products: ['O', 'O2'] | A: 1.0
R453: PHOTOLYSIS | Reactants: ['CFC12'] | Products: ['CL', 'COF2'] | A: 1.0
R454: PHOTOLYSIS | Reactants: ['NO3'] | Products: ['NO', 'O2'] | A: 1.0
R455: PHOTOLYSIS | Reactants: ['BIGALD2'] | Products: ['HO2', 'DICARBO2'] | A: 1.0
R456: PHOTOLYSIS | Reactants: ['HO2NO2'] | Products: ['OH', 'NO3'] | A: 1.0
R457: PHOTOLYSIS | Reactants: ['CH3BR'] | Products: ['BR', 'CH3O2'] | A: 1.0
R458: PHOTOLYSIS | Reactants: ['CLONO2'] | Products: ['CLO', 'NO2'] | A: 1.0
R459: PHOTOLYSIS | Reactants: ['GLYOXAL'] | Products: ['CO', 'HO2'] | A: 1.0
R460: PHOTOLYSIS | Reactants: ['O3'] | Products: ['O1D', 'O2'] | A: 1.0
R461: PHOTOLYSIS | Reactants: ['N2O5'] | Products: ['NO2', 'NO3'] | A: 1.0
R462: PHOTOLYSIS | Reactants: ['HPALD'] | Products: ['BIGALD3', 'OH', 'HO2'] | A: 1.0
R463: PHOTOLYSIS | Reactants: ['BZOOH'] | Products: ['BZALD', 'OH', 'HO2'] | A: 1.0
R464: PHOTOLYSIS | Reactants: ['CL2O2'] | Products: ['CL'] | A: 1.0
R465: PHOTOLYSIS | Reactants: ['ALKNIT'] | Products: ['NO2', 'CH3CHO', 'CH2O', 'CH3COCH3', 'HO2', 'MEK'] | A: 1.0
R466: PHOTOLYSIS | Reactants: ['BIGALD'] | Products: ['CO', 'GLYOXAL', 'HO2', 'CH3CO3', 'CH3COCHO'] | A: 1.0
R467: PHOTOLYSIS | Reactants: ['soa5_a1'] | Products: [] | A: 1.0
R468: PHOTOLYSIS | Reactants: ['MVK'] | Products: ['C3H6', 'CO', 'CH3O2', 'CH3CO3'] | A: 1.0
R469: PHOTOLYSIS | Reactants: ['SO3'] | Products: ['SO2', 'O'] | A: 1.0
R470: PHOTOLYSIS | Reactants: ['CHBR3'] | Products: ['BR'] | A: 1.0
R471: PHOTOLYSIS | Reactants: ['TERPROD2'] | Products: ['RO2', 'CH2O', 'CO2', 'CH3COCH3', 'CH3CO3', 'HO2', 'CO'] | A: 1.0
R472: PHOTOLYSIS | Reactants: ['MEK'] | Products: ['CH3CO3', 'C2H5O2'] | A: 1.0
R473: PHOTOLYSIS | Reactants: ['CH3COCH3'] | Products: ['CH3CO3', 'CH3O2'] | A: 1.0
R474: PHOTOLYSIS | Reactants: ['CF2CLBR'] | Products: ['BR', 'CL', 'COF2'] | A: 1.0
R475: PHOTOLYSIS | Reactants: ['H2O'] | Products: ['H', 'O'] | A: 1.0
R476: PHOTOLYSIS | Reactants: ['XYLOLOOH'] | Products: ['OH', 'GLYOXAL', 'CH3COCHO', 'HO2'] | A: 1.0
R477: PHOTOLYSIS | Reactants: ['SO2'] | Products: ['SO', 'O'] | A: 1.0
R478: PHOTOLYSIS | Reactants: ['MEKOOH'] | Products: ['OH', 'CH3CO3', 'CH3CHO'] | A: 1.0
R479: PHOTOLYSIS | Reactants: ['PHENOOH'] | Products: ['OH', 'HO2', 'GLYOXAL'] | A: 1.0
R480: PHOTOLYSIS | Reactants: ['soa4_a1'] | Products: [] | A: 1.0
R481: PHOTOLYSIS | Reactants: ['NO2'] | Products: ['NO', 'O'] | A: 1.0
R482: PHOTOLYSIS | Reactants: ['BIGALD3'] | Products: ['HO2', 'CO', 'MDIALO2'] | A: 1.0
R483: PHOTOLYSIS | Reactants: ['CH2BR2'] | Products: ['BR'] | A: 1.0
R484: PHOTOLYSIS | Reactants: ['HF'] | Products: ['H', 'F'] | A: 1.0
R485: PHOTOLYSIS | Reactants: ['BEPOMUC'] | Products: ['BIGALD1', 'HO2', 'CO'] | A: 1.0
R486: PHOTOLYSIS | Reactants: ['N2O'] | Products: ['O1D', 'N2'] | A: 1.0
R487: PHOTOLYSIS | Reactants: ['CH2O'] | Products: ['CO', 'H'] | A: 1.0
R488: PHOTOLYSIS | Reactants: ['HCFC22'] | Products: ['CL', 'COF2'] | A: 1.0
R489: PHOTOLYSIS | Reactants: ['NC4CHO'] | Products: ['BIGALD3', 'NO2', 'HO2'] | A: 1.0
R490: PHOTOLYSIS | Reactants: ['HONITR'] | Products: ['NO2', 'HO2', 'CH3CHO', 'CH2O', 'CO', 'GLYALD', 'CH3CO3', 'HYAC', 'CH3COCH3'] | A: 1.0
R491: PHOTOLYSIS | Reactants: ['XOOH'] | Products: ['OH'] | A: 1.0
R492: PHOTOLYSIS | Reactants: ['CH4'] | Products: ['H', 'CH3O2'] | A: 1.0
R493: PHOTOLYSIS | Reactants: ['HOBR'] | Products: ['BR', 'OH'] | A: 1.0
R494: PHOTOLYSIS | Reactants: ['NO3'] | Products: ['NO2', 'O'] | A: 1.0
R495: PHOTOLYSIS | Reactants: ['H2O'] | Products: ['OH', 'H'] | A: 1.0
R496: PHOTOLYSIS | Reactants: ['CH3COOOH'] | Products: ['CH3O2', 'OH', 'CO2'] | A: 1.0
R497: PHOTOLYSIS | Reactants: ['ONITR'] | Products: ['NO2'] | A: 1.0
R498: PHOTOLYSIS | Reactants: ['TERPOOH'] | Products: ['CH2O', 'CH3COCH3', 'TERPROD1', 'HO2', 'OH'] | A: 1.0
R499: PHOTOLYSIS | Reactants: ['CL2'] | Products: ['CL'] | A: 1.0
R500: USER_DEFINED | Reactants: ['OH', 'DMS'] | Products: ['SO2', 'HO2'] | A: N/A
R501: PHOTOLYSIS | Reactants: ['CH3CHO'] | Products: ['CH3O2', 'CO', 'HO2'] | A: 1.0
R502: PHOTOLYSIS | Reactants: ['BIGALD1'] | Products: ['MALO2', 'HO2'] | A: 1.0
R503: PHOTOLYSIS | Reactants: ['HNO3'] | Products: ['NO2', 'OH'] | A: 1.0
R504: PHOTOLYSIS | Reactants: ['C2H5OOH'] | Products: ['CH3CHO', 'HO2', 'OH'] | A: 1.0
R505: PHOTOLYSIS | Reactants: ['CO2'] | Products: ['CO', 'O'] | A: 1.0
R506: PHOTOLYSIS | Reactants: ['CFC115'] | Products: ['CL', 'F', 'COF2'] | A: 1.0
R507: PHOTOLYSIS | Reactants: ['HCFC141B'] | Products: ['CL', 'COFCL'] | A: 1.0
R508: PHOTOLYSIS | Reactants: ['TERPROD1'] | Products: ['HO2', 'CO', 'TERPROD2'] | A: 1.0
R509: PHOTOLYSIS | Reactants: ['MPAN'] | Products: ['MCO3', 'NO2'] | A: 1.0
R510: PHOTOLYSIS | Reactants: ['CLONO2'] | Products: ['CL', 'NO3'] | A: 1.0
R511: PHOTOLYSIS | Reactants: ['soa3_a1'] | Products: [] | A: 1.0
R512: PHOTOLYSIS | Reactants: ['soa4_a2'] | Products: [] | A: 1.0
R513: PHOTOLYSIS | Reactants: ['CF3BR'] | Products: ['BR', 'F', 'COF2'] | A: 1.0
R514: PHOTOLYSIS | Reactants: ['CH3CL'] | Products: ['CL', 'CH3O2'] | A: 1.0
R515: PHOTOLYSIS | Reactants: ['HCL'] | Products: ['H', 'CL'] | A: 1.0
R516: PHOTOLYSIS | Reactants: ['TOLOOH'] | Products: ['OH', 'GLYOXAL', 'CH3COCHO', 'HO2', 'BIGALD1', 'BIGALD2', 'BIGALD3'] | A: 1.0
R517: PHOTOLYSIS | Reactants: ['CH3CCL3'] | Products: ['CL'] | A: 1.0
R518: PHOTOLYSIS | Reactants: ['soa2_a1'] | Products: [] | A: 1.0
R519: PHOTOLYSIS | Reactants: ['GLYALD'] | Products: ['HO2', 'CO', 'CH2O'] | A: 1.0
R520: PHOTOLYSIS | Reactants: ['OCS'] | Products: ['S', 'CO'] | A: 1.0
R521: PHOTOLYSIS | Reactants: ['SF6'] | Products: ['sink'] | A: 1.0
R522: PHOTOLYSIS | Reactants: ['HOCL'] | Products: ['OH', 'CL'] | A: 1.0
R523: PHOTOLYSIS | Reactants: ['CH3OOH'] | Products: ['CH2O', 'H', 'OH'] | A: 1.0
R524: PHOTOLYSIS | Reactants: ['CLO'] | Products: ['CL', 'O'] | A: 1.0
R525: PHOTOLYSIS | Reactants: ['COFCL'] | Products: ['F', 'CL'] | A: 1.0
R526: PHOTOLYSIS | Reactants: ['O2'] | Products: ['O', 'O1D'] | A: 1.0
R527: PHOTOLYSIS | Reactants: ['H2402'] | Products: ['BR', 'COF2'] | A: 1.0
R528: PHOTOLYSIS | Reactants: ['soa1_a2'] | Products: [] | A: 1.0
R529: PHOTOLYSIS | Reactants: ['CFC11'] | Products: ['CL', 'COFCL'] | A: 1.0
R530: USER_DEFINED | Reactants: ['HOBR', 'HCL'] | Products: ['BRCL', 'H2O'] | A: N/A
R531: USER_DEFINED | Reactants: ['BRONO2'] | Products: ['HOBR', 'HNO3'] | A: N/A
R532: USER_DEFINED | Reactants: ['HCL', 'HOCL'] | Products: ['CL2', 'H2O'] | A: N/A
R533: USER_DEFINED | Reactants: ['HCL', 'HOCL'] | Products: ['CL2', 'H2O'] | A: N/A
R534: USER_DEFINED | Reactants: ['BRONO2'] | Products: ['HOBR', 'HNO3'] | A: N/A
R535: USER_DEFINED | Reactants: ['CLONO2'] | Products: ['HOCL', 'HNO3'] | A: N/A
R536: USER_DEFINED | Reactants: ['BRONO2'] | Products: ['HOBR', 'HNO3'] | A: N/A
R537: USER_DEFINED | Reactants: ['CLONO2'] | Products: ['HOCL', 'HNO3'] | A: N/A
R538: USER_DEFINED | Reactants: ['HCL', 'HOCL'] | Products: ['CL2', 'H2O'] | A: N/A
R539: USER_DEFINED | Reactants: ['CLONO2'] | Products: ['HOCL', 'HNO3'] | A: N/A
R540: USER_DEFINED | Reactants: ['CLONO2', 'HCL'] | Products: ['CL2', 'HNO3'] | A: N/A
R541: USER_DEFINED | Reactants: ['N2O5'] | Products: ['HNO3'] | A: N/A
R542: USER_DEFINED | Reactants: ['HOBR', 'HCL'] | Products: ['BRCL', 'H2O'] | A: N/A
R543: USER_DEFINED | Reactants: ['N2O5'] | Products: ['HNO3'] | A: N/A
R544: USER_DEFINED | Reactants: ['N2O5'] | Products: ['HNO3'] | A: N/A
R545: USER_DEFINED | Reactants: ['CLONO2', 'HCL'] | Products: ['CL2', 'HNO3'] | A: N/A
R546: USER_DEFINED | Reactants: ['OH', 'CO'] | Products: ['CO2', 'HO2'] | A: N/A
R547: USER_DEFINED | Reactants: ['CLONO2', 'HCL'] | Products: ['CL2', 'HNO3'] | A: N/A
d[ALKNIT]/dt = (IMPLICIT: -963542.5216*C_ALKNIT*C_OH - 1.0*C_ALKNIT*J_59 + 32519.560104*C_ALKO2*C_NO*exp(-870.0/Temp)) + (EXPLICIT: 0)
d[BZOOH]/dt = (IMPLICIT: 451660.557*C_BZOO*C_HO2*exp(-700.0/Temp) - 2288413.4888*C_BZOOH*C_OH*exp(-200.0/Temp) - 1.0*C_BZOOH*J_57) + (EXPLICIT: 0)
d[C6H5OOH]/dt = (IMPLICIT: 451660.557*C_C6H5O2*C_HO2*exp(-700.0/Temp) - 2288413.4888*C_C6H5OOH*C_OH*exp(-200.0/Temp) - 1.0*C_C6H5OOH*J_42) + (EXPLICIT: 0)
d[COF2]/dt = (IMPLICIT: 58715872.41*C_CF2CLBR*C_O1D + 27099633.42*C_CF3BR*C_O1D + 125742299.0688*C_CFC113*C_O1D + 70459046.892*C_CFC114*C_O1D + 27966821.68944*C_CFC115*C_O1D + 72506574.7504*C_CFC12*C_O1D - 12887381.2264*C_COF2*C_O1D - 1.0*C_COF2*J_11 + 72265689.12*C_H2402*C_O1D + 78287829.88*C_HCFC142B*C_O1D + 782878.2988*C_HCFC142B*C_OH*exp(1770.0/Temp) + 46069376.814*C_HCFC22*C_O1D + 554036.94992*C_HCFC22*C_OH*exp(1560.0/Temp)) + (EXPLICIT: 1.0*C_CF2CLBR*J_68 + 1.0*C_CF3BR*J_106 + 1.0*C_CFC113*J_17 + 1.0*C_CFC114*J_43 + 1.0*C_CFC115*J_99 + 1.0*C_CFC12*J_47 + 1.0*C_H2402*J_120 + 1.0*C_HCFC142B*J_28 + 1.0*C_HCFC22*J_82)
d[O2]/dt = (IMPLICIT: 0) + (EXPLICIT: 0)
d[COFCL]/dt = (IMPLICIT: 124658313.732*C_CFC11*C_O1D + 125742299.0688*C_CFC113*C_O1D - 114420674.44*C_COFCL*C_O1D - 1.0*C_COFCL*J_118 + 108037205.2344*C_HCFC141B*C_O1D + 752767.595*C_HCFC141B*C_OH*exp(1600.0/Temp)) + (EXPLICIT: 1.0*C_CFC11*J_122 + 1.0*C_CFC113*J_17 + 1.0*C_HCFC141B*J_100)
d[HF]/dt = (IMPLICIT: 96354252.16*C_CH4*C_F*exp(260.0/Temp) + 84309970.64*C_F*C_H2*exp(500.0/Temp) + 8430997.064*C_F*C_H2O + 3613284.456*C_F*C_HNO3*exp(-400.0/Temp) - 1.0*C_HF*J_78) + (EXPLICIT: 0)
d[F]/dt = (IMPLICIT: 27099633.42*C_CF3BR*C_O1D + 27966821.68944*C_CFC115*C_O1D - 96354252.16*C_CH4*C_F*exp(260.0/Temp) + 12887381.2264*C_COF2*C_O1D + 1.0*C_COF2*J_11 + 114420674.44*C_COFCL*C_O1D + 1.0*C_COFCL*J_118 - 84309970.64*C_F*C_H2*exp(500.0/Temp) - 8430997.064*C_F*C_H2O - 3613284.456*C_F*C_HNO3*exp(-400.0/Temp) + 1.0*C_HF*J_78) + (EXPLICIT: 1.0*C_CF3BR*J_106 + 1.0*C_CFC115*J_99)
d[BENZO2]/dt = (IMPLICIT: 1385092.3748*C_BENZENE*C_OH*exp(193.0/Temp) - 451660.557*C_BENZO2*C_HO2*exp(-700.0/Temp) - 1565756.5976*C_BENZO2*C_NO*exp(-365.0/Temp) + 2288413.4888*C_BENZOOH*C_OH*exp(-200.0/Temp)) + (EXPLICIT: 0)
d[BZOO]/dt = (IMPLICIT: -451660.557*C_BZOO*C_HO2*exp(-700.0/Temp) - 1565756.5976*C_BZOO*C_NO*exp(-365.0/Temp) + 2288413.4888*C_BZOOH*C_OH*exp(-200.0/Temp) + 1023763.9292*C_OH*C_TOLUENE*exp(-352.0/Temp) + 10237639.292*C_OH*C_XYLENES) + (EXPLICIT: 0)
d[N2]/dt = (IMPLICIT: 0) + (EXPLICIT: 0)
d[E90]/dt = (IMPLICIT: 0) + (EXPLICIT: -1.29e-7*C_E90)
d[NH_5]/dt = (IMPLICIT: 0) + (EXPLICIT: -2.31e-6*C_NH_5)
d[NH_50]/dt = (IMPLICIT: 0) + (EXPLICIT: -2.31e-7*C_NH_50)
d[ST80_25]/dt = (IMPLICIT: 0) + (EXPLICIT: -4.63e-7*C_ST80_25)
d[PAN]/dt = (IMPLICIT: -9.79990230341848e-34663*0.6**(1.0/(log(4.62753974189474*M_density*exp(-2.5/Temp))**2/log(10)**2 + 1.0))*C_PAN*M_density*Temp**14000.0*exp(-4.1/Temp)/(4.62753974189474*M_density*exp(-2.5/Temp) + 1.0) + 26474310.913275*0.6**(1.0/(log(4.62753974189474*M_density*exp(-2.5/Temp))**2/log(10)**2 + 1.0))*C_CH3CO3*C_NO2*M_density*exp(-4.1/Temp)/(4.62753974189474*M_density*exp(-2.5/Temp) + 1.0) - 24088.56304*C_OH*C_PAN - 1.0*C_PAN*J_45) + (EXPLICIT: 0)
d[MVK]/dt = (IMPLICIT: 8430997.064*C_CH3CO3*C_ISOPAO2 + 301107.038*C_CH3O2*C_ISOPAO2*exp(-400.0/Temp) + 6323.247798*C_ISOP*C_O3*exp(2000.0/Temp) + 2649741.9344*C_ISOPAO2*C_NO*exp(-180.0/Temp) + 1445313.7824*C_ISOPAO2*C_NO3 + 1.0*C_ISOPOOH*J_41 - 511.8819646*C_MVK*C_O3*exp(1520.0/Temp) - 2487144.13388*C_MVK*C_OH*exp(-452.0/Temp) - 1.0*C_MVK*J_62) + (EXPLICIT: 0)
d[MACROOH]/dt = (IMPLICIT: 481771.2608*C_HO2*C_MACRO2*exp(-700.0/Temp) - 13850923.748*C_MACROOH*C_OH*exp(-200.0/Temp)) + (EXPLICIT: 0)
d[SOAG0]/dt = (IMPLICIT: 7226.568912*C_BCARY*C_O3 + 165608.8709*C_BCARYO2VBS*C_HO2*exp(-1300.0/Temp) + 1625978.0052*C_BCARYO2VBS*C_NO*exp(-360.0/Temp) + 451660.557*C_BENZO2VBS*C_HO2*exp(-700.0/Temp) + 1565756.5976*C_BENZO2VBS*C_NO*exp(-365.0/Temp) + 127669.384112*C_HO2*C_ISOPO2VBS*exp(-1300.0/Temp) + 451660.557*C_HO2*C_IVOCO2VBS*exp(-700.0/Temp) + 156575.65976*C_HO2*C_MTERPO2VBS*exp(-1300.0/Temp) + 451660.557*C_HO2*C_TOLUO2VBS*exp(-700.0/Temp) + 451660.557*C_HO2*C_XYLEO2VBS*exp(-700.0/Temp) + 1625978.0052*C_ISOPO2VBS*C_NO*exp(-350.0/Temp) + 1565756.5976*C_IVOCO2VBS*C_NO*exp(-365.0/Temp) + 379.39486788*C_MTERP*C_O3*exp(580.0/Temp) + 1625978.0052*C_MTERPO2VBS*C_NO*exp(-360.0/Temp) + 1565756.5976*C_NO*C_TOLUO2VBS*exp(-365.0/Temp) + 1565756.5976*C_NO*C_XYLEO2VBS*exp(-365.0/Temp) + 8069668.6184*C_OH*C_SVOC) + (EXPLICIT: 0)
d[SOAG1]/dt = (IMPLICIT: 7226.568912*C_BCARY*C_O3 + 165608.8709*C_BCARYO2VBS*C_HO2*exp(-1300.0/Temp) + 1625978.0052*C_BCARYO2VBS*C_NO*exp(-360.0/Temp) + 451660.557*C_BENZO2VBS*C_HO2*exp(-700.0/Temp) + 1565756.5976*C_BENZO2VBS*C_NO*exp(-365.0/Temp) + 127669.384112*C_HO2*C_ISOPO2VBS*exp(-1300.0/Temp) + 451660.557*C_HO2*C_IVOCO2VBS*exp(-700.0/Temp) + 156575.65976*C_HO2*C_MTERPO2VBS*exp(-1300.0/Temp) + 451660.557*C_HO2*C_TOLUO2VBS*exp(-700.0/Temp) + 451660.557*C_HO2*C_XYLEO2VBS*exp(-700.0/Temp) + 1625978.0052*C_ISOPO2VBS*C_NO*exp(-350.0/Temp) + 1565756.5976*C_IVOCO2VBS*C_NO*exp(-365.0/Temp) + 379.39486788*C_MTERP*C_O3*exp(580.0/Temp) + 1625978.0052*C_MTERPO2VBS*C_NO*exp(-360.0/Temp) + 1565756.5976*C_NO*C_TOLUO2VBS*exp(-365.0/Temp) + 1565756.5976*C_NO*C_XYLEO2VBS*exp(-365.0/Temp) + 8069668.6184*C_OH*C_SVOC) + (EXPLICIT: 0)
d[SOAG2]/dt = (IMPLICIT: 7226.568912*C_BCARY*C_O3 + 165608.8709*C_BCARYO2VBS*C_HO2*exp(-1300.0/Temp) + 1625978.0052*C_BCARYO2VBS*C_NO*exp(-360.0/Temp) + 451660.557*C_BENZO2VBS*C_HO2*exp(-700.0/Temp) + 1565756.5976*C_BENZO2VBS*C_NO*exp(-365.0/Temp) + 127669.384112*C_HO2*C_ISOPO2VBS*exp(-1300.0/Temp) + 451660.557*C_HO2*C_IVOCO2VBS*exp(-700.0/Temp) + 156575.65976*C_HO2*C_MTERPO2VBS*exp(-1300.0/Temp) + 451660.557*C_HO2*C_TOLUO2VBS*exp(-700.0/Temp) + 451660.557*C_HO2*C_XYLEO2VBS*exp(-700.0/Temp) + 1625978.0052*C_ISOPO2VBS*C_NO*exp(-350.0/Temp) + 1565756.5976*C_IVOCO2VBS*C_NO*exp(-365.0/Temp) + 379.39486788*C_MTERP*C_O3*exp(580.0/Temp) + 1625978.0052*C_MTERPO2VBS*C_NO*exp(-360.0/Temp) + 1565756.5976*C_NO*C_TOLUO2VBS*exp(-365.0/Temp) + 1565756.5976*C_NO*C_XYLEO2VBS*exp(-365.0/Temp) + 8069668.6184*C_OH*C_SVOC) + (EXPLICIT: 0)
d[SOAG3]/dt = (IMPLICIT: 11442067.444*C_BCARY*C_NO3 + 7226.568912*C_BCARY*C_O3 + 165608.8709*C_BCARYO2VBS*C_HO2*exp(-1300.0/Temp) + 1625978.0052*C_BCARYO2VBS*C_NO*exp(-360.0/Temp) + 451660.557*C_BENZO2VBS*C_HO2*exp(-700.0/Temp) + 1565756.5976*C_BENZO2VBS*C_NO*exp(-365.0/Temp) + 127669.384112*C_HO2*C_ISOPO2VBS*exp(-1300.0/Temp) + 451660.557*C_HO2*C_IVOCO2VBS*exp(-700.0/Temp) + 156575.65976*C_HO2*C_MTERPO2VBS*exp(-1300.0/Temp) + 451660.557*C_HO2*C_TOLUO2VBS*exp(-700.0/Temp) + 451660.557*C_HO2*C_XYLEO2VBS*exp(-700.0/Temp) + 1824708.65028*C_ISOP*C_NO3*exp(446.0/Temp) + 6323.247798*C_ISOP*C_O3*exp(2000.0/Temp) + 1625978.0052*C_ISOPO2VBS*C_NO*exp(-350.0/Temp) + 1565756.5976*C_IVOCO2VBS*C_NO*exp(-365.0/Temp) + 722656.8912*C_MTERP*C_NO3*exp(-490.0/Temp) + 379.39486788*C_MTERP*C_O3*exp(580.0/Temp) + 1625978.0052*C_MTERPO2VBS*C_NO*exp(-360.0/Temp) + 1565756.5976*C_NO*C_TOLUO2VBS*exp(-365.0/Temp) + 1565756.5976*C_NO*C_XYLEO2VBS*exp(-365.0/Temp) + 8069668.6184*C_OH*C_SVOC) + (EXPLICIT: 0)
d[SOAG4]/dt = (IMPLICIT: 11442067.444*C_BCARY*C_NO3 + 7226.568912*C_BCARY*C_O3 + 165608.8709*C_BCARYO2VBS*C_HO2*exp(-1300.0/Temp) + 1625978.0052*C_BCARYO2VBS*C_NO*exp(-360.0/Temp) + 451660.557*C_BENZO2VBS*C_HO2*exp(-700.0/Temp) + 1565756.5976*C_BENZO2VBS*C_NO*exp(-365.0/Temp) + 127669.384112*C_HO2*C_ISOPO2VBS*exp(-1300.0/Temp) + 451660.557*C_HO2*C_IVOCO2VBS*exp(-700.0/Temp) + 156575.65976*C_HO2*C_MTERPO2VBS*exp(-1300.0/Temp) + 451660.557*C_HO2*C_TOLUO2VBS*exp(-700.0/Temp) + 451660.557*C_HO2*C_XYLEO2VBS*exp(-700.0/Temp) + 1824708.65028*C_ISOP*C_NO3*exp(446.0/Temp) + 1625978.0052*C_ISOPO2VBS*C_NO*exp(-350.0/Temp) + 1565756.5976*C_IVOCO2VBS*C_NO*exp(-365.0/Temp) + 722656.8912*C_MTERP*C_NO3*exp(-490.0/Temp) + 379.39486788*C_MTERP*C_O3*exp(580.0/Temp) + 1625978.0052*C_MTERPO2VBS*C_NO*exp(-360.0/Temp) + 1565756.5976*C_NO*C_TOLUO2VBS*exp(-365.0/Temp) + 1565756.5976*C_NO*C_XYLEO2VBS*exp(-365.0/Temp) + 8069668.6184*C_OH*C_SVOC) + (EXPLICIT: 0)
d[soa4_a1]/dt = (IMPLICIT: 0) + (EXPLICIT: -1.0*C_soa4_a1*J_74)
d[soa5_a1]/dt = (IMPLICIT: 0) + (EXPLICIT: -1.0*C_soa5_a1*J_61)
d[soa5_a2]/dt = (IMPLICIT: 0) + (EXPLICIT: -1.0*C_soa5_a2*J_31)
d[soa3_a1]/dt = (IMPLICIT: 0) + (EXPLICIT: -1.0*C_soa3_a1*J_104)
d[soa2_a1]/dt = (IMPLICIT: 0) + (EXPLICIT: -1.0*C_soa2_a1*J_111)
d[soa1_a1]/dt = (IMPLICIT: 0) + (EXPLICIT: -1.0*C_soa1_a1*J_38)
d[soa1_a2]/dt = (IMPLICIT: 0) + (EXPLICIT: -1.0*C_soa1_a2*J_121)
d[soa2_a2]/dt = (IMPLICIT: 0) + (EXPLICIT: -1.0*C_soa2_a2*J_26)
d[soa3_a2]/dt = (IMPLICIT: 0) + (EXPLICIT: -1.0*C_soa3_a2*J_8)
d[soa4_a2]/dt = (IMPLICIT: 0) + (EXPLICIT: -1.0*C_soa4_a2*J_105)
d[ISOPNITB]/dt = (IMPLICIT: 2649741.9344*C_ISOPBO2*C_NO*exp(-180.0/Temp) - 24088563.04*C_ISOPNITB*C_OH) + (EXPLICIT: 0)
d[SO3]/dt = (IMPLICIT: 105171.920066435*0.6**(1.0/(log(0.102730636494118*M_density*exp(-4.3/Temp))**2/log(10)**2 + 1.0))*C_OH*C_SO2*M_density*exp(-4.1/Temp)/(0.102730636494118*M_density*exp(-4.3/Temp) + 1.0) - 3.08262524332654e-5*C_H2O**2*C_SO3*exp(-6540.0/Temp) + 1.0*C_H2SO4*J_20 - 1.0*C_SO3*J_63) + (EXPLICIT: 0)
d[OCS]/dt = (IMPLICIT: -12646495.596*C_O*C_OCS*exp(2200.0/Temp) - 43359.413472*C_OCS*C_OH*exp(1070.0/Temp)) + (EXPLICIT: -1.0*C_OCS*J_113)
d[SO]/dt = (IMPLICIT: -34326202.332*C_BRO*C_SO - 16861994.128*C_CLO*C_SO - 8430997.064*C_NO2*C_SO + 12646495.596*C_O*C_OCS*exp(2200.0/Temp) + 1385092.3748*C_O2*C_S - 96354.25216*C_O2*C_SO*exp(2280.0/Temp) + 7226568.912*C_O3*C_S - 2047527.8584*C_O3*C_SO*exp(1100.0/Temp) - 1144206.7444*C_OCLO*C_SO + 39746129.016*C_OH*C_S - 15657565.976*C_OH*C_SO*exp(-330.0/Temp) - 1.0*C_SO*J_35 + 1.0*C_SO2*J_71) + (EXPLICIT: 0)
d[S]/dt = (IMPLICIT: -1385092.3748*C_O2*C_S - 7226568.912*C_O3*C_S - 39746129.016*C_OH*C_S + 1.0*C_SO*J_35) + (EXPLICIT: 1.0*C_OCS*J_113)
d[BCARYO2VBS]/dt = (IMPLICIT: 120442815.2*C_BCARY*C_OH - 165608.8709*C_BCARYO2VBS*C_HO2*exp(-1300.0/Temp) - 1625978.0052*C_BCARYO2VBS*C_NO*exp(-360.0/Temp)) + (EXPLICIT: 0)
d[SF6]/dt = (IMPLICIT: 0) + (EXPLICIT: -1.0*C_SF6*J_114)
d[sink]/dt = (IMPLICIT: 0) + (EXPLICIT: 1.0*C_SF6*J_114)
d[H]/dt = (IMPLICIT: -19221.0750466243*0.6**(1.0/(log(0.000335972063452632*M_density*exp(-2.2/Temp))**2/log(10)**2 + 1.0))*C_H*C_O2*M_density*exp(-1.8/Temp)/(0.000335972063452632*M_density*exp(-2.2/Temp) + 1.0) + 3312177.418*C_CH2O*C_OH*exp(-125.0/Temp) + 1.0*C_CH2O*J_81 + 1.0*C_CH3OOH*J_116 + 21077492.66*C_CH4*C_O1D + 1.0*C_CH4*J_4 + 1.0*C_CH4*J_86 + 18367529.318*C_CL*C_H2*exp(2270.0/Temp) + 84309970.64*C_F*C_H2*exp(500.0/Temp) - 48478233.118*C_H*C_HO2 - 84309970.64*C_H*C_O3*exp(470.0/Temp) + 9635425.216*C_H2*C_O*exp(4570.0/Temp) + 72265689.12*C_H2*C_O1D + 1686199.4128*C_H2*C_OH*exp(1800.0/Temp) + 1.0*C_H2O*J_69 + 1.0*C_H2O*J_89 + 18066422.28*C_HBR*C_O1D + 1.0*C_HBR*J_24 + 1987306.4508*C_HCL*C_O1D + 1.0*C_HCL*J_108 + 1.0*C_HF*J_78 + 30110703.8*C_N*C_OH + 10839853.368*C_O*C_OH*exp(-180.0/Temp) + 43359.413472*C_OCS*C_OH*exp(1070.0/Temp) + 39746129.016*C_OH*C_S + 15657565.976*C_OH*C_SO*exp(-330.0/Temp)) + (EXPLICIT: 0)
d[MEK]/dt = (IMPLICIT: 1.0*C_ALKNIT*J_59 + 4034834.3092*C_ALKO2*C_NO + 1.0*C_ALKOOH*J_37 - 1385092.3748*C_MEK*C_OH*exp(170.0/Temp) - 1.0*C_MEK*J_66) + (EXPLICIT: 0)
d[MTERP]/dt = (IMPLICIT: -722656.8912*C_MTERP*C_NO3*exp(-490.0/Temp) - 379.39486788*C_MTERP*C_O3*exp(580.0/Temp) - 7226568.912*C_MTERP*C_OH*exp(-440.0/Temp)) + (EXPLICIT: 0)
d[N2O5]/dt = (IMPLICIT: 870388.303998081*0.6**(1.0/(log(0.903321114*M_density*exp(-3.1/Temp))**2/log(10)**2 + 1.0))*C_NO2*C_NO3*M_density*exp(-3.0/Temp)/(0.903321114*M_density*exp(-3.1/Temp) + 1.0) - 2.52425373052892e-26838*0.6**(1.0/(log(0.903321114*M_density*exp(-3.1/Temp))**2/log(10)**2 + 1.0))*C_N2O5*M_density*Temp**10840.0*exp(-3.0/Temp)/(0.903321114*M_density*exp(-3.1/Temp) + 1.0) - 1.0*C_N2O5*J_34 - 1.0*C_N2O5*J_55 - 1.0*C_N2O5*Rate_540 - 1.0*C_N2O5*Rate_542 - 1.0*C_N2O5*Rate_543) + (EXPLICIT: 0)
d[HCN]/dt = (IMPLICIT: -2212.23693932846*0.8**(1.0/(log(0.374847537102041*M_density*exp(-6.1/Temp))**2/log(10)**2 + 1.0))*C_HCN*C_OH*M_density*exp(-1.5/Temp)/(0.374847537102041*M_density*exp(-6.1/Temp) + 1.0) - 65039120.208*C_HCN*C_O1D*exp(-105.0/Temp)) + (EXPLICIT: 0)
d[SVOC]/dt = (IMPLICIT: -8069668.6184*C_OH*C_SVOC) + (EXPLICIT: 0)
d[ISOPNO3]/dt = (IMPLICIT: -8430997.064*C_CH3CO3*C_ISOPNO3 - 301107.038*C_CH3O2*C_ISOPNO3*exp(-400.0/Temp) - 481771.2608*C_HO2*C_ISOPNO3*exp(-700.0/Temp) + 1824708.65028*C_ISOP*C_NO3*exp(446.0/Temp) - 1625978.0052*C_ISOPNO3*C_NO*exp(-360.0/Temp) - 1445313.7824*C_ISOPNO3*C_NO3) + (EXPLICIT: 0)
d[RO2]/dt = (IMPLICIT: 0) + (EXPLICIT: 0)
d[PHENO2]/dt = (IMPLICIT: 28304061.572*C_CRESOL*C_OH - 451660.557*C_HO2*C_PHENO2*exp(-700.0/Temp) - 1565756.5976*C_NO*C_PHENO2*exp(-365.0/Temp) + 283040.61572*C_OH*C_PHENOL*exp(-1220.0/Temp) + 2288413.4888*C_OH*C_PHENOOH*exp(-200.0/Temp)) + (EXPLICIT: 0)
d[BENZO2VBS]/dt = (IMPLICIT: 1385092.3748*C_BENZENE*C_OH*exp(193.0/Temp) - 451660.557*C_BENZO2VBS*C_HO2*exp(-700.0/Temp) - 1565756.5976*C_BENZO2VBS*C_NO*exp(-365.0/Temp)) + (EXPLICIT: 0)
d[IVOC]/dt = (IMPLICIT: -8069668.6184*C_IVOC*C_OH) + (EXPLICIT: 0)
d[TERPNIT]/dt = (IMPLICIT: 1204428.152*C_CH3O2*C_NTERPO2*exp(-500.0/Temp) + 2529299.1192*C_NO*C_NTERPO2*exp(-180.0/Temp) + 2529299.1192*C_NO*C_TERPO2*exp(-180.0/Temp) - 12044281.52*C_OH*C_TERPNIT - 1.0*C_TERPNIT*J_0) + (EXPLICIT: 0)
d[ISOPO2VBS]/dt = (IMPLICIT: -127669.384112*C_HO2*C_ISOPO2VBS*exp(-1300.0/Temp) + 15296237.5304*C_ISOP*C_OH*exp(-410.0/Temp) - 1625978.0052*C_ISOPO2VBS*C_NO*exp(-350.0/Temp)) + (EXPLICIT: 0)
d[IVOCO2VBS]/dt = (IMPLICIT: -451660.557*C_HO2*C_IVOCO2VBS*exp(-700.0/Temp) + 8069668.6184*C_IVOC*C_OH - 1565756.5976*C_IVOCO2VBS*C_NO*exp(-365.0/Temp)) + (EXPLICIT: 0)
d[HNO3]/dt = (IMPLICIT: 652791.227998561*0.6**(1.0/(log(0.0387137620285714*M_density*exp(-3.0/Temp))**2/log(10)**2 + 1.0))*C_NO2*C_OH*M_density*exp(-3.0/Temp)/(0.0387137620285714*M_density*exp(-3.0/Temp) + 1.0) - 2.13447077159129e+3309*1.0**(1.0/(log(8.48274510194932e-2140*M_density*Temp**864.0)**2/log(10)**2 + 1.0))*C_HNO3*C_OH*M_density/(Temp**1335.0*(8.48274510194932e-2140*M_density*Temp**864.0 + 1.0)) + 1.0*C_BRONO2*Rate_530 + 1.0*C_BRONO2*Rate_533 + 1.0*C_BRONO2*Rate_535 + 361328.4456*C_CH2O*C_NO3*exp(2058.0/Temp) + 843099.7064*C_CH3CHO*C_NO3*exp(1900.0/Temp) + 843099.7064*C_CH3COCHO*C_NO3*exp(1860.0/Temp) + 1.0*C_CLONO2*C_HCL*Rate_539 + 1.0*C_CLONO2*C_HCL*Rate_544 + 1.0*C_CLONO2*C_HCL*Rate_546 + 1.0*C_CLONO2*Rate_534 + 1.0*C_CLONO2*Rate_536 + 1.0*C_CLONO2*Rate_538 + 114420.67444*C_DMS*C_NO3*exp(-520.0/Temp) - 3613284.456*C_F*C_HNO3*exp(-400.0/Temp) - 14453.137824*C_HNO3*C_OH*exp(-460.0/Temp) - 1.0*C_HNO3*J_96 + 1.0*C_N2O5*Rate_540 + 1.0*C_N2O5*Rate_542 + 1.0*C_N2O5*Rate_543) + (EXPLICIT: 0)
d[ACBZO2]/dt = (IMPLICIT: 1.30217879922136e-34662*0.6**(1.0/(log(6.28115756688172*M_density*exp(-4.1/Temp))**2/log(10)**2 + 1.0))*C_PBZNIT*M_density*Temp**14000.0*exp(-5.6/Temp)/(6.28115756688172*M_density*exp(-4.1/Temp) + 1.0) - 35178193.9532558*0.6**(1.0/(log(6.28115756688172*M_density*exp(-4.1/Temp))**2/log(10)**2 + 1.0))*C_ACBZO2*C_NO2*M_density*exp(-5.6/Temp)/(6.28115756688172*M_density*exp(-4.1/Temp) + 1.0) - 258952.05268*C_ACBZO2*C_HO2*exp(-1040.0/Temp) - 4516605.57*C_ACBZO2*C_NO*exp(-290.0/Temp) + 3553063.0484*C_BZALD*C_OH*exp(-225.0/Temp)) + (EXPLICIT: 0)
d[CH3COOOH]/dt = (IMPLICIT: 258952.05268*C_CH3CO3*C_HO2*exp(-1040.0/Temp) - 602214.076*C_CH3COOOH*C_OH - 1.0*C_CH3COOOH*J_90 + 258952.05268*C_HO2*C_MCO3*exp(-1040.0/Temp)) + (EXPLICIT: 0)
d[SO2]/dt = (IMPLICIT: -105171.920066435*0.6**(1.0/(log(0.102730636494118*M_density*exp(-4.3/Temp))**2/log(10)**2 + 1.0))*C_OH*C_SO2*M_density*exp(-4.1/Temp)/(0.102730636494118*M_density*exp(-4.3/Temp) + 1.0) + 34326202.332*C_BRO*C_SO + 16861994.128*C_CLO*C_SO + 114420.67444*C_DMS*C_NO3*exp(-520.0/Temp) + 1.0*C_DMS*C_OH*Rate_499 + 6624354.836*C_DMS*C_OH*exp(280.0/Temp) + 8430997.064*C_NO2*C_SO + 96354.25216*C_O2*C_SO*exp(2280.0/Temp) + 2047527.8584*C_O3*C_SO*exp(1100.0/Temp) + 1144206.7444*C_OCLO*C_SO + 43359.413472*C_OCS*C_OH*exp(1070.0/Temp) + 15657565.976*C_OH*C_SO*exp(-330.0/Temp) - 1.0*C_SO2*J_71 + 1.0*C_SO3*J_63) + (EXPLICIT: 0)
d[MTERPO2VBS]/dt = (IMPLICIT: -156575.65976*C_HO2*C_MTERPO2VBS*exp(-1300.0/Temp) + 7226568.912*C_MTERP*C_OH*exp(-440.0/Temp) - 1625978.0052*C_MTERPO2VBS*C_NO*exp(-360.0/Temp)) + (EXPLICIT: 0)
d[CH4]/dt = (IMPLICIT: 0) + (EXPLICIT: 0)
d[CH3CL]/dt = (IMPLICIT: -12224945.7428*C_CH3CL*C_CL*exp(1100.0/Temp) - 1180339.58896*C_CH3CL*C_OH*exp(1200.0/Temp)) + (EXPLICIT: -1.0*C_CH3CL*J_107)
d[CH3CO3]/dt = (IMPLICIT: 9.79990230341848e-34663*0.6**(1.0/(log(4.62753974189474*M_density*exp(-2.5/Temp))**2/log(10)**2 + 1.0))*C_PAN*M_density*Temp**14000.0*exp(-4.1/Temp)/(4.62753974189474*M_density*exp(-2.5/Temp) + 1.0) - 26474310.913275*0.6**(1.0/(log(4.62753974189474*M_density*exp(-2.5/Temp))**2/log(10)**2 + 1.0))*C_CH3CO3*C_NO2*M_density*exp(-4.1/Temp)/(4.62753974189474*M_density*exp(-2.5/Temp) + 1.0) + 7226.568912*C_BCARY*C_O3 + 1.0*C_BIGALD*J_60 + 1.0*C_BIGALD4*J_7 + 843099.7064*C_CH3CHO*C_NO3*exp(1900.0/Temp) + 2788251.17188*C_CH3CHO*C_OH*exp(-350.0/Temp) - 3492841.6408*C_CH3CO3**2*exp(-500.0/Temp) - 1204428.152*C_CH3CO3*C_CH3O2*exp(-500.0/Temp) - 258952.05268*C_CH3CO3*C_HO2*exp(-1040.0/Temp) - 8430997.064*C_CH3CO3*C_ISOPAO2 - 8430997.064*C_CH3CO3*C_ISOPBO2 - 8430997.064*C_CH3CO3*C_ISOPNO3 - 4877934.0156*C_CH3CO3*C_NO*exp(-270.0/Temp) - 782878.2988*C_CH3CO3*C_XO2*exp(-640.0/Temp) + 1.0*C_CH3COCH3*J_67 + 843099.7064*C_CH3COCHO*C_NO3*exp(1860.0/Temp) + 505859.82384*C_CH3COCHO*C_OH*exp(-830.0/Temp) + 1.0*C_CH3COCHO*J_2 + 602214.076*C_CH3COOOH*C_OH + 301107.038*C_CH3O2*C_MACRO2*exp(-400.0/Temp) + 1204428.152*C_CH3O2*C_MCO3*exp(-500.0/Temp) + 427571.99396*C_CH3O2*C_RO2*exp(-500.0/Temp) + 258952.05268*C_HO2*C_MCO3*exp(-1040.0/Temp) + 451660.557*C_HO2*C_MEKO2*exp(-700.0/Temp) + 517904.10536*C_HO2*C_RO2*exp(-700.0/Temp) + 1.0*C_HONITR*J_84 + 1.0*C_HYAC*J_27 + 6323.247798*C_ISOP*C_O3*exp(2000.0/Temp) + 903.321114*C_MACR*C_O3*exp(2100.0/Temp) + 1.0*C_MACR*J_32 + 1625978.0052*C_MACRO2*C_NO*exp(-360.0/Temp) + 1445313.7824*C_MACRO2*C_NO3 + 1385092.3748*C_MCO3**2*exp(-530.0/Temp) + 3191734.6028*C_MCO3*C_NO*exp(-360.0/Temp) + 3011070.38*C_MCO3*C_NO3 + 1.0*C_MEK*J_66 + 2529299.1192*C_MEKO2*C_NO*exp(-180.0/Temp) + 1.0*C_MEKOOH*J_72 + 379.39486788*C_MTERP*C_O3*exp(580.0/Temp) + 511.8819646*C_MVK*C_O3*exp(1520.0/Temp) + 1.0*C_MVK*J_62 + 1746420.8204*C_NO*C_RO2*exp(-300.0/Temp) + 1.0*C_NOA*J_19 + 20475278.584*C_OH*C_TERPROD2 + 1.0*C_PAN*J_45 + 1.0*C_ROOH*J_23 + 1.0*C_TEPOMUC*J_10 + 1.0*C_TERPROD2*J_65) + (EXPLICIT: 0)
d[C6H5O2]/dt = (IMPLICIT: 258952.05268*C_ACBZO2*C_HO2*exp(-1040.0/Temp) + 4516605.57*C_ACBZO2*C_NO*exp(-290.0/Temp) - 451660.557*C_C6H5O2*C_HO2*exp(-700.0/Temp) - 1565756.5976*C_C6H5O2*C_NO*exp(-365.0/Temp) + 2288413.4888*C_C6H5OOH*C_OH*exp(-200.0/Temp) + 168619.94128*C_O3*C_PHENO) + (EXPLICIT: 0)
d[TERPROD1]/dt = (IMPLICIT: 7226.568912*C_BCARY*C_O3 + 1204428.152*C_CH3O2*C_NTERPO2*exp(-500.0/Temp) + 1204428.152*C_CH3O2*C_TERPO2*exp(-500.0/Temp) + 379.39486788*C_MTERP*C_O3*exp(580.0/Temp) + 2529299.1192*C_NO*C_NTERPO2*exp(-180.0/Temp) + 2529299.1192*C_NO*C_TERPO2*exp(-180.0/Temp) + 1445313.7824*C_NO3*C_NTERPO2 - 602214.076*C_NO3*C_TERPROD1 + 1.0*C_NTERPOOH*J_22 + 12044281.52*C_OH*C_TERPNIT - 34326202.332*C_OH*C_TERPROD1 + 1.0*C_TERPNIT*J_0 + 1.0*C_TERPOOH*J_92 - 1.0*C_TERPROD1*J_101) + (EXPLICIT: 0)
d[HYAC]/dt = (IMPLICIT: 2901294346.66027*0.5**(1.0/(log(160.590420266667*M_density*exp(-3.5/Temp))**2/log(10)**2 + 1.0))*C_MPAN*C_OH*M_density*exp(-3.5/Temp)/(160.590420266667*M_density*exp(-3.5/Temp) + 1.0) + 8430997.064*C_CH3CO3*C_MACRO2 + 782878.2988*C_CH3CO3*C_XO2*exp(-640.0/Temp) + 301107.038*C_CH3O2*C_MACRO2*exp(-400.0/Temp) + 427571.99396*C_CH3O2*C_RO2*exp(-500.0/Temp) + 301107.038*C_CH3O2*C_XO2*exp(-400.0/Temp) + 1.0*C_HONITR*J_84 - 1806642.228*C_HYAC*C_OH - 1.0*C_HYAC*J_27 + 2649741.9344*C_ISOPBO2*C_NO*exp(-180.0/Temp) + 1445313.7824*C_ISOPBO2*C_NO3 + 24088563.04*C_ISOPNITA*C_OH + 24088563.04*C_ISOPNITB*C_OH + 1625978.0052*C_MACRO2*C_NO*exp(-360.0/Temp) + 1445313.7824*C_MACRO2*C_NO3 + 1625978.0052*C_NO*C_XO2*exp(-360.0/Temp) + 1445313.7824*C_NO3*C_XO2 + 2288413.4888*C_OH*C_POOH*exp(-200.0/Temp)) + (EXPLICIT: 0)
d[HPALD]/dt = (IMPLICIT: -11201181.8136*C_HPALD*C_OH*exp(-175.0/Temp) - 1.0*C_HPALD*J_56 + 1600000000.0*C_ISOPBO2*exp(8300.0/Temp)) + (EXPLICIT: 0)
d[TOLUO2VBS]/dt = (IMPLICIT: -451660.557*C_HO2*C_TOLUO2VBS*exp(-700.0/Temp) - 1565756.5976*C_NO*C_TOLUO2VBS*exp(-365.0/Temp) + 1023763.9292*C_OH*C_TOLUENE*exp(-352.0/Temp)) + (EXPLICIT: 0)
d[H2O]/dt = (IMPLICIT: 0) + (EXPLICIT: 0)
d[NO2]/dt = (IMPLICIT: 1.30217879922136e-34662*0.6**(1.0/(log(6.28115756688172*M_density*exp(-4.1/Temp))**2/log(10)**2 + 1.0))*C_MPAN*M_density*Temp**14000.0*exp(-5.6/Temp)/(6.28115756688172*M_density*exp(-4.1/Temp) + 1.0) + 1.30217879922136e-34662*0.6**(1.0/(log(6.28115756688172*M_density*exp(-4.1/Temp))**2/log(10)**2 + 1.0))*C_PBZNIT*M_density*Temp**14000.0*exp(-5.6/Temp)/(6.28115756688172*M_density*exp(-4.1/Temp) + 1.0) - 35178193.9532558*0.6**(1.0/(log(6.28115756688172*M_density*exp(-4.1/Temp))**2/log(10)**2 + 1.0))*C_ACBZO2*C_NO2*M_density*exp(-5.6/Temp)/(6.28115756688172*M_density*exp(-4.1/Temp) + 1.0) - 35178193.9532558*0.6**(1.0/(log(6.28115756688172*M_density*exp(-4.1/Temp))**2/log(10)**2 + 1.0))*C_MCO3*C_NO2*M_density*exp(-5.6/Temp)/(6.28115756688172*M_density*exp(-4.1/Temp) + 1.0) + 1.30199334468671e-26987*0.6**(1.0/(log(0.02860516861*M_density*exp(-3.1/Temp))**2/log(10)**2 + 1.0))*C_HO2NO2*M_density*Temp**10900.0*exp(-3.4/Temp)/(0.02860516861*M_density*exp(-3.1/Temp) + 1.0) - 68905.7407331814*0.6**(1.0/(log(0.02860516861*M_density*exp(-3.1/Temp))**2/log(10)**2 + 1.0))*C_HO2*C_NO2*M_density*exp(-3.4/Temp)/(0.02860516861*M_density*exp(-3.1/Temp) + 1.0) - 870388.303998081*0.6**(1.0/(log(0.903321114*M_density*exp(-3.1/Temp))**2/log(10)**2 + 1.0))*C_NO2*C_NO3*M_density*exp(-3.0/Temp)/(0.903321114*M_density*exp(-3.1/Temp) + 1.0) + 2.52425373052892e-26838*0.6**(1.0/(log(0.903321114*M_density*exp(-3.1/Temp))**2/log(10)**2 + 1.0))*C_N2O5*M_density*Temp**10840.0*exp(-3.0/Temp)/(0.903321114*M_density*exp(-3.1/Temp) + 1.0) - 652791.227998561*0.6**(1.0/(log(0.0387137620285714*M_density*exp(-3.0/Temp))**2/log(10)**2 + 1.0))*C_NO2*C_OH*M_density*exp(-3.0/Temp)/(0.0387137620285714*M_density*exp(-3.0/Temp) + 1.0) + 9.79990230341848e-34663*0.6**(1.0/(log(4.62753974189474*M_density*exp(-2.5/Temp))**2/log(10)**2 + 1.0))*C_PAN*M_density*Temp**14000.0*exp(-4.1/Temp)/(4.62753974189474*M_density*exp(-2.5/Temp) + 1.0) - 26474310.913275*0.6**(1.0/(log(4.62753974189474*M_density*exp(-2.5/Temp))**2/log(10)**2 + 1.0))*C_CH3CO3*C_NO2*M_density*exp(-4.1/Temp)/(4.62753974189474*M_density*exp(-2.5/Temp) + 1.0) + 32639.561399928*0.6**(1.0/(log(0.001806642228*M_density*exp(-1.5/Temp))**2/log(10)**2 + 1.0))*C_NO*C_O*M_density*exp(-1.5/Temp)/(0.001806642228*M_density*exp(-1.5/Temp) + 1.0) - 65279.1227998561*0.6**(1.0/(log(0.007226568912*M_density*exp(-1.5/Temp))**2/log(10)**2 + 1.0))*C_CLO*C_NO2*M_density*exp(-3.4/Temp)/(0.007226568912*M_density*exp(-1.5/Temp) + 1.0) - 90665.4483331334*0.6**(1.0/(log(0.00684334177272727*M_density*exp(-1.1/Temp))**2/log(10)**2 + 1.0))*C_NO2*C_O*M_density*exp(-1.8/Temp)/(0.00684334177272727*M_density*exp(-1.1/Temp) + 1.0) - 188584.132532918*0.6**(1.0/(log(0.0453842492057971*M_density*exp(-0.3/Temp))**2/log(10)**2 + 1.0))*C_BRO*C_NO2*M_density*exp(-3.2/Temp)/(0.0453842492057971*M_density*exp(-0.3/Temp) + 1.0) + 4516605.57*C_ACBZO2*C_NO*exp(-290.0/Temp) + 963542.5216*C_ALKNIT*C_OH + 1.0*C_ALKNIT*J_59 + 4034834.3092*C_ALKO2*C_NO + 1565756.5976*C_BENZO2*C_NO*exp(-365.0/Temp) + 210774.9266*C_BIGENE*C_NO3 + 5299483.8688*C_BRO*C_NO*exp(-260.0/Temp) + 1.0*C_BRONO2*J_13 + 1565756.5976*C_BZOO*C_NO*exp(-365.0/Temp) + 1565756.5976*C_C2H5O2*C_NO*exp(-365.0/Temp) + 2529299.1192*C_C3H7O2*C_NO*exp(-180.0/Temp) + 1565756.5976*C_C6H5O2*C_NO*exp(-365.0/Temp) + 4877934.0156*C_CH3CO3*C_NO*exp(-270.0/Temp) + 1686199.4128*C_CH3O2*C_NO*exp(-300.0/Temp) + 1204428.152*C_CH3O2*C_NTERPO2*exp(-500.0/Temp) + 3854170.0864*C_CLO*C_NO*exp(-290.0/Temp) + 1.0*C_CLONO2*J_52 + 4516605.57*C_DICARBO2*C_NO*exp(-290.0/Temp) + 2890627.5648*C_ENEO2*C_NO*exp(-120.0/Temp) + 2529299.1192*C_EO2*C_NO*exp(-180.0/Temp) + 1.0*C_HNO3*J_96 + 2071616.42144*C_HO2*C_NO*exp(-260.0/Temp) + 2107749.266*C_HO2*C_NO3 + 270996.3342*C_HO2NO2*C_OH*exp(-610.0/Temp) + 1.0*C_HO2NO2*J_44 + 1565756.5976*C_HOCH2OO*C_NO*exp(-265.0/Temp) + 1.0*C_HONITR*J_84 + 2649741.9344*C_ISOPAO2*C_NO*exp(-180.0/Temp) + 1445313.7824*C_ISOPAO2*C_NO3 + 2649741.9344*C_ISOPBO2*C_NO*exp(-180.0/Temp) + 1445313.7824*C_ISOPBO2*C_NO3 + 24088563.04*C_ISOPNITA*C_OH + 1625978.0052*C_ISOPNO3*C_NO*exp(-360.0/Temp) + 1445313.7824*C_ISOPNO3*C_NO3 + 1.0*C_ISOPNOOH*J_36 + 1625978.0052*C_MACRO2*C_NO*exp(-360.0/Temp) + 1445313.7824*C_MACRO2*C_NO3 + 4516605.57*C_MALO2*C_NO*exp(-290.0/Temp) + 3191734.6028*C_MCO3*C_NO*exp(-360.0/Temp) + 3011070.38*C_MCO3*C_NO3 + 4516605.57*C_MDIALO2*C_NO*exp(-290.0/Temp) + 2529299.1192*C_MEKO2*C_NO*exp(-180.0/Temp) + 1.0*C_MPAN*J_102 - 3492841.6408*C_N*C_NO2*exp(-220.0/Temp) + 1.0*C_N2O5*J_55 + 1.0*C_NC4CHO*J_83 + 10237639.292*C_NO*C_NO3*exp(-125.0/Temp) + 2529299.1192*C_NO*C_NTERPO2*exp(-180.0/Temp) + 1806642.228*C_NO*C_O3*exp(1500.0/Temp) + 1565756.5976*C_NO*C_PHENO2*exp(-365.0/Temp) + 2529299.1192*C_NO*C_PO2*exp(-180.0/Temp) + 1746420.8204*C_NO*C_RO2*exp(-300.0/Temp) + 2529299.1192*C_NO*C_TERP2O2*exp(-180.0/Temp) + 2529299.1192*C_NO*C_TERPO2*exp(-180.0/Temp) + 1565756.5976*C_NO*C_TOLO2*exp(-365.0/Temp) + 1625978.0052*C_NO*C_XO2*exp(-360.0/Temp) + 1565756.5976*C_NO*C_XYLENO2*exp(-365.0/Temp) + 1565756.5976*C_NO*C_XYLOLO2*exp(-365.0/Temp) - 3071291.7876*C_NO2*C_O*exp(-210.0/Temp) - 72265.68912*C_NO2*C_O3*exp(2450.0/Temp) - 8430997.064*C_NO2*C_SO - 1.0*C_NO2*J_75 + 1445313.7824*C_NO3*C_NTERPO2 + 7828782.988*C_NO3*C_O + 13248709.672*C_NO3*C_OH + 1445313.7824*C_NO3*C_XO2 + 1.0*C_NO3*J_88 + 403483.43092*C_NOA*C_OH + 1.0*C_NOA*J_19 + 1.0*C_NTERPOOH*J_22 + 12044281.52*C_OH*C_TERPNIT + 1.0*C_ONITR*J_91 + 1.0*C_PAN*J_45 + 1.0*C_TERPNIT*J_0) + (EXPLICIT: -35178193.9532558*0.6**(1.0/(log(6.28115756688172*M_density*exp(-4.1/Temp))**2/log(10)**2 + 1.0))*C_DICARBO2*C_NO2*M_density*exp(-5.6/Temp)/(6.28115756688172*M_density*exp(-4.1/Temp) + 1.0) - 35178193.9532558*0.6**(1.0/(log(6.28115756688172*M_density*exp(-4.1/Temp))**2/log(10)**2 + 1.0))*C_MALO2*C_NO2*M_density*exp(-5.6/Temp)/(6.28115756688172*M_density*exp(-4.1/Temp) + 1.0) - 35178193.9532558*0.6**(1.0/(log(6.28115756688172*M_density*exp(-4.1/Temp))**2/log(10)**2 + 1.0))*C_MDIALO2*C_NO2*M_density*exp(-5.6/Temp)/(6.28115756688172*M_density*exp(-4.1/Temp) + 1.0) - 1264649.5596*C_NO2*C_PHENO)
d[EOOH]/dt = (IMPLICIT: 451660.557*C_EO2*C_HO2*exp(-700.0/Temp) - 1.0*C_EOOH*J_39) + (EXPLICIT: 0)
d[NTERPOOH]/dt = (IMPLICIT: 451660.557*C_HO2*C_NTERPO2*exp(-700.0/Temp) - 12044281.52*C_NTERPOOH*C_OH - 1.0*C_NTERPOOH*J_22) + (EXPLICIT: 0)
d[XYLEO2VBS]/dt = (IMPLICIT: -451660.557*C_HO2*C_XYLEO2VBS*exp(-700.0/Temp) - 1565756.5976*C_NO*C_XYLEO2VBS*exp(-365.0/Temp) + 10237639.292*C_OH*C_XYLENES) + (EXPLICIT: 0)
d[CCL4]/dt = (IMPLICIT: -156997209.6132*C_CCL4*C_O1D) + (EXPLICIT: -1.0*C_CCL4*J_18)
d[CF2CLBR]/dt = (IMPLICIT: -58715872.41*C_CF2CLBR*C_O1D) + (EXPLICIT: -1.0*C_CF2CLBR*J_68)
d[CF3BR]/dt = (IMPLICIT: -27099633.42*C_CF3BR*C_O1D) + (EXPLICIT: -1.0*C_CF3BR*J_106)
d[CFC11]/dt = (IMPLICIT: -124658313.732*C_CFC11*C_O1D) + (EXPLICIT: -1.0*C_CFC11*J_122)
d[CFC113]/dt = (IMPLICIT: -125742299.0688*C_CFC113*C_O1D) + (EXPLICIT: -1.0*C_CFC113*J_17)
d[CFC114]/dt = (IMPLICIT: -70459046.892*C_CFC114*C_O1D) + (EXPLICIT: -1.0*C_CFC114*J_43)
d[CFC115]/dt = (IMPLICIT: -27966821.68944*C_CFC115*C_O1D) + (EXPLICIT: -1.0*C_CFC115*J_99)
d[CFC12]/dt = (IMPLICIT: -72506574.7504*C_CFC12*C_O1D) + (EXPLICIT: -1.0*C_CFC12*J_47)
d[CH2BR2]/dt = (IMPLICIT: -3793948.6788*C_CH2BR2*C_CL*exp(800.0/Temp) - 154769017.532*C_CH2BR2*C_O1D - 1204428.152*C_CH2BR2*C_OH*exp(840.0/Temp)) + (EXPLICIT: -1.0*C_CH2BR2*J_77)
d[CH3BR]/dt = (IMPLICIT: -8792325.5096*C_CH3BR*C_CL*exp(1040.0/Temp) - 108398533.68*C_CH3BR*C_O1D - 855143.98792*C_CH3BR*C_OH*exp(1150.0/Temp)) + (EXPLICIT: -1.0*C_CH3BR*J_51)
d[CH3CCL3]/dt = (IMPLICIT: -987631.08464*C_CH3CCL3*C_OH*exp(1520.0/Temp)) + (EXPLICIT: -1.0*C_CH3CCL3*J_110)
d[NO]/dt = (IMPLICIT: -32639.561399928*0.6**(1.0/(log(0.001806642228*M_density*exp(-1.5/Temp))**2/log(10)**2 + 1.0))*C_NO*C_O*M_density*exp(-1.5/Temp)/(0.001806642228*M_density*exp(-1.5/Temp) + 1.0) - 4516605.57*C_ACBZO2*C_NO*exp(-290.0/Temp) - 4034834.3092*C_ALKO2*C_NO - 32519.560104*C_ALKO2*C_NO*exp(-870.0/Temp) - 1565756.5976*C_BENZO2*C_NO*exp(-365.0/Temp) - 5299483.8688*C_BRO*C_NO*exp(-260.0/Temp) - 1565756.5976*C_BZOO*C_NO*exp(-365.0/Temp) - 1565756.5976*C_C2H5O2*C_NO*exp(-365.0/Temp) - 2529299.1192*C_C3H7O2*C_NO*exp(-180.0/Temp) - 1565756.5976*C_C6H5O2*C_NO*exp(-365.0/Temp) - 4877934.0156*C_CH3CO3*C_NO*exp(-270.0/Temp) - 1686199.4128*C_CH3O2*C_NO*exp(-300.0/Temp) - 3854170.0864*C_CLO*C_NO*exp(-290.0/Temp) - 4516605.57*C_DICARBO2*C_NO*exp(-290.0/Temp) - 30712.917876*C_ENEO2*C_NO*exp(-693.0/Temp) - 2890627.5648*C_ENEO2*C_NO*exp(-120.0/Temp) - 2529299.1192*C_EO2*C_NO*exp(-180.0/Temp) - 2071616.42144*C_HO2*C_NO*exp(-260.0/Temp) - 1565756.5976*C_HOCH2OO*C_NO*exp(-265.0/Temp) - 2649741.9344*C_ISOPAO2*C_NO*exp(-180.0/Temp) - 2649741.9344*C_ISOPBO2*C_NO*exp(-180.0/Temp) - 1625978.0052*C_ISOPNO3*C_NO*exp(-360.0/Temp) - 1704265.83508*C_MACRO2*C_NO*exp(-360.0/Temp) - 4516605.57*C_MALO2*C_NO*exp(-290.0/Temp) - 3191734.6028*C_MCO3*C_NO*exp(-360.0/Temp) - 4516605.57*C_MDIALO2*C_NO*exp(-290.0/Temp) - 2529299.1192*C_MEKO2*C_NO*exp(-180.0/Temp) - 12646495.596*C_N*C_NO*exp(-100.0/Temp) + 873210.4102*C_N*C_NO2*exp(-220.0/Temp) + 1987306.4508*C_N*C_O2*exp(3150.0/Temp) + 30110703.8*C_N*C_OH + 43720741.9176*C_N2O*C_O1D*exp(-20.0/Temp) + 1.0*C_N2O5*J_34 - 10237639.292*C_NO*C_NO3*exp(-125.0/Temp) - 2529299.1192*C_NO*C_NTERPO2*exp(-180.0/Temp) - 1806642.228*C_NO*C_O3*exp(1500.0/Temp) - 1565756.5976*C_NO*C_PHENO2*exp(-365.0/Temp) - 2529299.1192*C_NO*C_PO2*exp(-180.0/Temp) - 1746420.8204*C_NO*C_RO2*exp(-300.0/Temp) - 2529299.1192*C_NO*C_TERP2O2*exp(-180.0/Temp) - 2529299.1192*C_NO*C_TERPO2*exp(-180.0/Temp) - 1565756.5976*C_NO*C_TOLO2*exp(-365.0/Temp) - 1625978.0052*C_NO*C_XO2*exp(-360.0/Temp) - 1565756.5976*C_NO*C_XYLENO2*exp(-365.0/Temp) - 1565756.5976*C_NO*C_XYLOLO2*exp(-365.0/Temp) - 1.0*C_NO*J_14 + 3071291.7876*C_NO2*C_O*exp(-210.0/Temp) + 8430997.064*C_NO2*C_SO + 1.0*C_NO2*J_75 + 1.0*C_NO3*J_48) + (EXPLICIT: 0)
d[BR]/dt = (IMPLICIT: -10237639.292*C_BR*C_CH2O*exp(800.0/Temp) - 2890627.5648*C_BR*C_HO2*exp(310.0/Temp) - 9635425.216*C_BR*C_O3*exp(780.0/Temp) + 1.0*C_BRCL*J_40 + 903321.114*C_BRO**2*exp(-230.0/Temp) + 572103.3722*C_BRO*C_CLO*exp(-550.0/Temp) + 1385092.3748*C_BRO*C_CLO*exp(-260.0/Temp) + 5299483.8688*C_BRO*C_NO*exp(-260.0/Temp) + 11442067.444*C_BRO*C_O*exp(-230.0/Temp) + 10237639.292*C_BRO*C_OH*exp(-250.0/Temp) + 34326202.332*C_BRO*C_SO + 1.0*C_BRO*J_9 + 1.0*C_BRONO2*J_6 + 58715872.41*C_CF2CLBR*C_O1D + 27099633.42*C_CF3BR*C_O1D + 3793948.6788*C_CH2BR2*C_CL*exp(800.0/Temp) + 154769017.532*C_CH2BR2*C_O1D + 1204428.152*C_CH2BR2*C_OH*exp(840.0/Temp) + 8792325.5096*C_CH3BR*C_CL*exp(1040.0/Temp) + 108398533.68*C_CH3BR*C_O1D + 855143.98792*C_CH3BR*C_OH*exp(1150.0/Temp) + 2920738.2686*C_CHBR3*C_CL*exp(850.0/Temp) + 278222903.112*C_CHBR3*C_O1D + 541992.6684*C_CHBR3*C_OH*exp(360.0/Temp) + 72265689.12*C_H2402*C_O1D + 3492841.6408*C_HBR*C_O*exp(1500.0/Temp) + 54199266.84*C_HBR*C_O1D + 3312177.418*C_HBR*C_OH*exp(-200.0/Temp) + 1.0*C_HBR*J_24 + 1.0*C_HOBR*J_87) + (EXPLICIT: 1.0*C_CF2CLBR*J_68 + 1.0*C_CF3BR*J_106 + 1.0*C_CH2BR2*J_77 + 1.0*C_CH3BR*J_51 + 1.0*C_CHBR3*J_64 + 1.0*C_H2402*J_120)
d[BRCL]/dt = (IMPLICIT: -1.0*C_BRCL*J_40 + 246907.77116*C_BRO*C_CLO*exp(-290.0/Temp) + 1.0*C_HCL*C_HOBR*Rate_529 + 1.0*C_HCL*C_HOBR*Rate_541) + (EXPLICIT: 0)
d[BRO]/dt = (IMPLICIT: -188584.132532918*0.6**(1.0/(log(0.0453842492057971*M_density*exp(-0.3/Temp))**2/log(10)**2 + 1.0))*C_BRO*C_NO2*M_density*exp(-3.2/Temp)/(0.0453842492057971*M_density*exp(-0.3/Temp) + 1.0) + 9635425.216*C_BR*C_O3*exp(780.0/Temp) - 1806642.228*C_BRO**2*exp(-230.0/Temp) - 572103.3722*C_BRO*C_CLO*exp(-550.0/Temp) - 246907.77116*C_BRO*C_CLO*exp(-290.0/Temp) - 1385092.3748*C_BRO*C_CLO*exp(-260.0/Temp) - 2709963.342*C_BRO*C_HO2*exp(-460.0/Temp) - 5299483.8688*C_BRO*C_NO*exp(-260.0/Temp) - 11442067.444*C_BRO*C_O*exp(-230.0/Temp) - 10237639.292*C_BRO*C_OH*exp(-250.0/Temp) - 34326202.332*C_BRO*C_SO - 1.0*C_BRO*J_9 + 11442067.444*C_BRONO2*C_O*exp(-215.0/Temp) + 1.0*C_BRONO2*J_13 + 18066422.28*C_HBR*C_O1D + 72265689.12*C_HOBR*C_O*exp(430.0/Temp)) + (EXPLICIT: 0)
d[BRONO2]/dt = (IMPLICIT: 188584.132532918*0.6**(1.0/(log(0.0453842492057971*M_density*exp(-0.3/Temp))**2/log(10)**2 + 1.0))*C_BRO*C_NO2*M_density*exp(-3.2/Temp)/(0.0453842492057971*M_density*exp(-0.3/Temp) + 1.0) - 11442067.444*C_BRONO2*C_O*exp(-215.0/Temp) - 1.0*C_BRONO2*J_13 - 1.0*C_BRONO2*J_6 - 1.0*C_BRONO2*Rate_530 - 1.0*C_BRONO2*Rate_533 - 1.0*C_BRONO2*Rate_535) + (EXPLICIT: 0)
d[CL]/dt = (IMPLICIT: 1.0*C_BRCL*J_40 + 1385092.3748*C_BRO*C_CLO*exp(-260.0/Temp) - 43359413.472*C_C2H6*C_CL*exp(70.0/Temp) + 156997209.6132*C_CCL4*C_O1D + 58715872.41*C_CF2CLBR*C_O1D + 124658313.732*C_CFC11*C_O1D + 125742299.0688*C_CFC113*C_O1D + 70459046.892*C_CFC114*C_O1D + 27966821.68944*C_CFC115*C_O1D + 72506574.7504*C_CFC12*C_O1D - 3793948.6788*C_CH2BR2*C_CL*exp(800.0/Temp) - 48779340.156*C_CH2O*C_CL*exp(30.0/Temp) - 8792325.5096*C_CH3BR*C_CL*exp(1040.0/Temp) + 987631.08464*C_CH3CCL3*C_OH*exp(1520.0/Temp) - 12224945.7428*C_CH3CL*C_CL*exp(1100.0/Temp) + 1180339.58896*C_CH3CL*C_OH*exp(1200.0/Temp) + 1987306.4508*C_CH3O2*C_CLO*exp(115.0/Temp) - 4275719.9396*C_CH4*C_CL*exp(1270.0/Temp) - 2920738.2686*C_CHBR3*C_CL*exp(850.0/Temp) - 3914391.494*C_CL*C_CLONO2*exp(-135.0/Temp) - 18367529.318*C_CL*C_H2*exp(2270.0/Temp) - 6624354.836*C_CL*C_H2O2*exp(980.0/Temp) - 21679706.736*C_CL*C_HO2*exp(375.0/Temp) - 8430997.064*C_CL*C_HO2*exp(-270.0/Temp) - 2047527.8584*C_CL*C_HOCL*exp(130.0/Temp) - 13850923.748*C_CL*C_O3*exp(200.0/Temp) + 1.0*C_CL2*J_93 + 1.0*C_CL2O2*J_58 + 210774.9266*C_CLO**2*exp(1370.0/Temp) + 18066422.28*C_CLO**2*exp(2450.0/Temp) + 3854170.0864*C_CLO*C_NO*exp(-290.0/Temp) + 16861994.128*C_CLO*C_O*exp(-85.0/Temp) + 4456384.1624*C_CLO*C_OH*exp(-270.0/Temp) + 16861994.128*C_CLO*C_SO + 1.0*C_CLO*J_117 + 1.0*C_CLONO2*J_103 + 114420674.44*C_COFCL*C_O1D + 1.0*C_COFCL*J_118 + 108037205.2344*C_HCFC141B*C_O1D + 752767.595*C_HCFC141B*C_OH*exp(1600.0/Temp) + 78287829.88*C_HCFC142B*C_O1D + 782878.2988*C_HCFC142B*C_OH*exp(1770.0/Temp) + 46069376.814*C_HCFC22*C_O1D + 554036.94992*C_HCFC22*C_OH*exp(1560.0/Temp) + 6022140.76*C_HCL*C_O*exp(3300.0/Temp) + 59619193.524*C_HCL*C_O1D + 1083985.3368*C_HCL*C_OH*exp(250.0/Temp) + 1.0*C_HCL*J_108 + 1.0*C_HOCL*J_115) + (EXPLICIT: 1.0*C_CCL4*J_18 + 1.0*C_CF2CLBR*J_68 + 1.0*C_CFC11*J_122 + 1.0*C_CFC113*J_17 + 1.0*C_CFC114*J_43 + 1.0*C_CFC115*J_99 + 1.0*C_CFC12*J_47 + 1.0*C_CH3CCL3*J_110 + 1.0*C_CH3CL*J_107 + 1.0*C_HCFC141B*J_100 + 1.0*C_HCFC142B*J_28 + 1.0*C_HCFC22*J_82)
d[CL2]/dt = (IMPLICIT: 3914391.494*C_CL*C_CLONO2*exp(-135.0/Temp) - 1.0*C_CL2*J_93 + 602214.076*C_CLO**2*exp(1590.0/Temp) + 1.0*C_CLONO2*C_HCL*Rate_539 + 1.0*C_CLONO2*C_HCL*Rate_544 + 1.0*C_CLONO2*C_HCL*Rate_546 + 1.0*C_HCL*C_HOCL*Rate_531 + 1.0*C_HCL*C_HOCL*Rate_532 + 1.0*C_HCL*C_HOCL*Rate_537) + (EXPLICIT: 0)
d[CL2O2]/dt = (IMPLICIT: -3.46656390292415e-21135*0.6**(1.0/(log(0.00309245066054054*M_density*exp(-2.0/Temp))**2/log(10)**2 + 1.0))*C_CL2O2*M_density*Temp**8537.0*exp(-3.6/Temp)/(0.00309245066054054*M_density*exp(-2.0/Temp) + 1.0) + 6890.57407331814*0.6**(1.0/(log(0.00309245066054054*M_density*exp(-2.0/Temp))**2/log(10)**2 + 1.0))*C_CLO**2*M_density*exp(-3.6/Temp)/(0.00309245066054054*M_density*exp(-2.0/Temp) + 1.0) - 1.0*C_CL2O2*J_58) + (EXPLICIT: 0)
d[CLO]/dt = (IMPLICIT: 3.46656390292415e-21135*0.6**(1.0/(log(0.00309245066054054*M_density*exp(-2.0/Temp))**2/log(10)**2 + 1.0))*C_CL2O2*M_density*Temp**8537.0*exp(-3.6/Temp)/(0.00309245066054054*M_density*exp(-2.0/Temp) + 1.0) - 13781.1481466363*0.6**(1.0/(log(0.00309245066054054*M_density*exp(-2.0/Temp))**2/log(10)**2 + 1.0))*C_CLO**2*M_density*exp(-3.6/Temp)/(0.00309245066054054*M_density*exp(-2.0/Temp) + 1.0) - 65279.1227998561*0.6**(1.0/(log(0.007226568912*M_density*exp(-1.5/Temp))**2/log(10)**2 + 1.0))*C_CLO*C_NO2*M_density*exp(-3.4/Temp)/(0.007226568912*M_density*exp(-1.5/Temp) + 1.0) - 572103.3722*C_BRO*C_CLO*exp(-550.0/Temp) - 246907.77116*C_BRO*C_CLO*exp(-290.0/Temp) - 1385092.3748*C_BRO*C_CLO*exp(-260.0/Temp) - 1987306.4508*C_CH3O2*C_CLO*exp(115.0/Temp) + 21679706.736*C_CL*C_HO2*exp(375.0/Temp) + 2047527.8584*C_CL*C_HOCL*exp(130.0/Temp) + 13850923.748*C_CL*C_O3*exp(200.0/Temp) - 421549.8532*C_CLO**2*exp(1370.0/Temp) - 1204428.152*C_CLO**2*exp(1590.0/Temp) - 36132844.56*C_CLO**2*exp(2450.0/Temp) - 1565756.5976*C_CLO*C_HO2*exp(-290.0/Temp) - 3854170.0864*C_CLO*C_NO*exp(-290.0/Temp) - 16861994.128*C_CLO*C_O*exp(-85.0/Temp) - 4456384.1624*C_CLO*C_OH*exp(-270.0/Temp) - 361328.4456*C_CLO*C_OH*exp(-230.0/Temp) - 16861994.128*C_CLO*C_SO - 1.0*C_CLO*J_117 + 2167970.6736*C_CLONO2*C_O*exp(840.0/Temp) + 1.0*C_CLONO2*J_52 + 1987306.4508*C_HCL*C_O1D + 102376.39292*C_HOCL*C_O + 1806642.228*C_HOCL*C_OH*exp(500.0/Temp) + 1144206.7444*C_OCLO*C_SO + 1.0*C_OCLO*J_30) + (EXPLICIT: 0)
d[CLONO2]/dt = (IMPLICIT: 65279.1227998561*0.6**(1.0/(log(0.007226568912*M_density*exp(-1.5/Temp))**2/log(10)**2 + 1.0))*C_CLO*C_NO2*M_density*exp(-3.4/Temp)/(0.007226568912*M_density*exp(-1.5/Temp) + 1.0) - 3914391.494*C_CL*C_CLONO2*exp(-135.0/Temp) - 1.0*C_CLONO2*C_HCL*Rate_539 - 1.0*C_CLONO2*C_HCL*Rate_544 - 1.0*C_CLONO2*C_HCL*Rate_546 - 2167970.6736*C_CLONO2*C_O*exp(840.0/Temp) - 722656.8912*C_CLONO2*C_OH*exp(330.0/Temp) - 1.0*C_CLONO2*J_103 - 1.0*C_CLONO2*J_52 - 1.0*C_CLONO2*Rate_534 - 1.0*C_CLONO2*Rate_536 - 1.0*C_CLONO2*Rate_538) + (EXPLICIT: 0)
d[HCOOH]/dt = (IMPLICIT: 1994639.86332894*0.6**(1.0/(log(3.99057520240964*M_density*exp(-2.0/Temp))**2/log(10)**2 + 1.0))*C_C2H2*C_OH*M_density/(3.99057520240964*M_density*exp(-2.0/Temp) + 1.0) + 7226.568912*C_BCARY*C_O3 + 7226.568912*C_C2H4*C_O3*exp(2630.0/Temp) + 3914.391494*C_C3H6*C_O3*exp(1900.0/Temp) - 240885.6304*C_HCOOH*C_OH + 451660.557*C_HO2*C_HOCH2OO*exp(-700.0/Temp) + 1565756.5976*C_HOCH2OO*C_NO*exp(-265.0/Temp) + 6323.247798*C_ISOP*C_O3*exp(2000.0/Temp) + 903.321114*C_MACR*C_O3*exp(2100.0/Temp) + 379.39486788*C_MTERP*C_O3*exp(580.0/Temp) + 511.8819646*C_MVK*C_O3*exp(1520.0/Temp)) + (EXPLICIT: 0)
d[HBR]/dt = (IMPLICIT: 10237639.292*C_BR*C_CH2O*exp(800.0/Temp) + 2890627.5648*C_BR*C_HO2*exp(310.0/Temp) - 3492841.6408*C_HBR*C_O*exp(1500.0/Temp) - 72265689.12*C_HBR*C_O1D - 3312177.418*C_HBR*C_OH*exp(-200.0/Temp) - 1.0*C_HBR*J_24) + (EXPLICIT: 0)
d[HOBR]/dt = (IMPLICIT: 2709963.342*C_BRO*C_HO2*exp(-460.0/Temp) + 1.0*C_BRONO2*Rate_530 + 1.0*C_BRONO2*Rate_533 + 1.0*C_BRONO2*Rate_535 - 1.0*C_HCL*C_HOBR*Rate_529 - 1.0*C_HCL*C_HOBR*Rate_541 - 72265689.12*C_HOBR*C_O*exp(430.0/Temp) - 1.0*C_HOBR*J_87) + (EXPLICIT: 0)
d[HOCL]/dt = (IMPLICIT: -2047527.8584*C_CL*C_HOCL*exp(130.0/Temp) + 1565756.5976*C_CLO*C_HO2*exp(-290.0/Temp) + 722656.8912*C_CLONO2*C_OH*exp(330.0/Temp) + 1.0*C_CLONO2*Rate_534 + 1.0*C_CLONO2*Rate_536 + 1.0*C_CLONO2*Rate_538 - 1.0*C_HCL*C_HOCL*Rate_531 - 1.0*C_HCL*C_HOCL*Rate_532 - 1.0*C_HCL*C_HOCL*Rate_537 - 102376.39292*C_HOCL*C_O - 1806642.228*C_HOCL*C_OH*exp(500.0/Temp) - 1.0*C_HOCL*J_115) + (EXPLICIT: 0)
d[N]/dt = (IMPLICIT: -12646495.596*C_N*C_NO*exp(-100.0/Temp) - 3492841.6408*C_N*C_NO2*exp(-220.0/Temp) - 1987306.4508*C_N*C_O2*exp(3150.0/Temp) - 30110703.8*C_N*C_OH + 1.0*C_NO*J_14) + (EXPLICIT: 0)
d[BIGENE]/dt = (IMPLICIT: -210774.9266*C_BIGENE*C_NO3 - 32519560.104*C_BIGENE*C_OH) + (EXPLICIT: 0)
d[C2H4]/dt = (IMPLICIT: -31188914.2265979*0.48**(1.0/(log(5.75449005955556*M_density*exp(-2.25/Temp))**2/log(10)**2 + 1.0))*C_C2H4*C_OH*M_density*exp(-3.1/Temp)/(5.75449005955556*M_density*exp(-2.25/Temp) + 1.0) - 5802588.69332054*0.6**(1.0/(log(0.0310820168258065*M_density*exp(-2.3/Temp))**2/log(10)**2 + 1.0))*C_C2H4*C_CL*M_density*exp(-3.3/Temp)/(0.0310820168258065*M_density*exp(-2.3/Temp) + 1.0) - 7226.568912*C_C2H4*C_O3*exp(2630.0/Temp)) + (EXPLICIT: 0)
d[C2H5O2]/dt = (IMPLICIT: -81901.114336*C_C2H5O2**2 - 120442.8152*C_C2H5O2*C_CH3O2 - 451660.557*C_C2H5O2*C_HO2*exp(-700.0/Temp) - 1565756.5976*C_C2H5O2*C_NO*exp(-365.0/Temp) + 2288413.4888*C_C2H5OOH*C_OH*exp(-200.0/Temp) + 43359413.472*C_C2H6*C_CL*exp(70.0/Temp) + 4612959.82216*C_C2H6*C_OH*exp(1020.0/Temp) + 1.0*C_MEK*J_66) + (EXPLICIT: 0)
d[CH3COCHO]/dt = (IMPLICIT: 1.0*C_BIGALD*J_60 + 1.0*C_BIGALD4*J_7 + 8430997.064*C_CH3CO3*C_MACRO2 + 782878.2988*C_CH3CO3*C_XO2*exp(-640.0/Temp) - 843099.7064*C_CH3COCHO*C_NO3*exp(1860.0/Temp) - 505859.82384*C_CH3COCHO*C_OH*exp(-830.0/Temp) - 1.0*C_CH3COCHO*J_2 + 301107.038*C_CH3O2*C_MACRO2*exp(-400.0/Temp) + 427571.99396*C_CH3O2*C_RO2*exp(-500.0/Temp) + 301107.038*C_CH3O2*C_XO2*exp(-400.0/Temp) + 258952.05268*C_DICARBO2*C_HO2*exp(-1040.0/Temp) + 4516605.57*C_DICARBO2*C_NO*exp(-290.0/Temp) + 258952.05268*C_HO2*C_MDIALO2*exp(-1040.0/Temp) + 1806642.228*C_HYAC*C_OH + 2649741.9344*C_ISOPBO2*C_NO*exp(-180.0/Temp) + 1445313.7824*C_ISOPBO2*C_NO3 + 903.321114*C_MACR*C_O3*exp(2100.0/Temp) + 1625978.0052*C_MACRO2*C_NO*exp(-360.0/Temp) + 1445313.7824*C_MACRO2*C_NO3 + 4516605.57*C_MDIALO2*C_NO*exp(-290.0/Temp) + 511.8819646*C_MVK*C_O3*exp(1520.0/Temp) + 1565756.5976*C_NO*C_TOLO2*exp(-365.0/Temp) + 1625978.0052*C_NO*C_XO2*exp(-360.0/Temp) + 1565756.5976*C_NO*C_XYLENO2*exp(-365.0/Temp) + 1565756.5976*C_NO*C_XYLOLO2*exp(-365.0/Temp) + 1445313.7824*C_NO3*C_XO2 + 403483.43092*C_NOA*C_OH + 1.0*C_TOLOOH*J_109 + 1.0*C_XYLENOOH*J_3 + 1.0*C_XYLOLOOH*J_70) + (EXPLICIT: 0)
d[CH3COCH3]/dt = (IMPLICIT: 963542.5216*C_ALKNIT*C_OH + 1.0*C_ALKNIT*J_59 + 4034834.3092*C_ALKO2*C_NO + 1.0*C_ALKOOH*J_37 + 7226.568912*C_BCARY*C_O3 + 210774.9266*C_BIGENE*C_NO3 + 225830.2785*C_C3H7O2*C_CH3O2*exp(40.0/Temp) + 2529299.1192*C_C3H7O2*C_NO*exp(-180.0/Temp) + 1.0*C_C3H7OOH*J_16 - 23004577.7032*C_CH3COCH3*C_OH*exp(2000.0/Temp) - 80094.472108*C_CH3COCH3*C_OH - 1.0*C_CH3COCH3*J_67 + 1204428.152*C_CH3O2*C_TERP2O2*exp(-500.0/Temp) + 1204428.152*C_CH3O2*C_TERPO2*exp(-500.0/Temp) + 2890627.5648*C_ENEO2*C_NO*exp(-120.0/Temp) + 1.0*C_HONITR*J_84 + 379.39486788*C_MTERP*C_O3*exp(580.0/Temp) + 2529299.1192*C_NO*C_TERP2O2*exp(-180.0/Temp) + 2529299.1192*C_NO*C_TERPO2*exp(-180.0/Temp) + 20475278.584*C_OH*C_TERPROD2 + 1.0*C_TERP2OOH*J_5 + 1.0*C_TERPOOH*J_92 + 1.0*C_TERPROD2*J_65) + (EXPLICIT: 0)
d[O]/dt = (IMPLICIT: -32639.561399928*0.6**(1.0/(log(0.001806642228*M_density*exp(-1.5/Temp))**2/log(10)**2 + 1.0))*C_NO*C_O*M_density*exp(-1.5/Temp)/(0.001806642228*M_density*exp(-1.5/Temp) + 1.0) - 90665.4483331334*0.6**(1.0/(log(0.00684334177272727*M_density*exp(-1.1/Temp))**2/log(10)**2 + 1.0))*C_NO2*C_O*M_density*exp(-1.8/Temp)/(0.00684334177272727*M_density*exp(-1.1/Temp) + 1.0) - 11442067.444*C_BRO*C_O*exp(-230.0/Temp) + 1.0*C_BRO*J_9 - 11442067.444*C_BRONO2*C_O*exp(-215.0/Temp) - 20475278.584*C_CH2O*C_O*exp(1600.0/Temp) + 1.0*C_CH4*J_4 - 16861994.128*C_CLO*C_O*exp(-85.0/Temp) + 1.0*C_CLO*J_117 - 2167970.6736*C_CLONO2*C_O*exp(840.0/Temp) + 1.0*C_CO2*J_98 + 963542.5216*C_H*C_HO2 - 9635425.216*C_H2*C_O*exp(4570.0/Temp) + 1.0*C_H2O*J_69 - 843099.7064*C_H2O2*C_O*exp(2000.0/Temp) - 3492841.6408*C_HBR*C_O*exp(1500.0/Temp) - 6022140.76*C_HCL*C_O*exp(3300.0/Temp) - 18066422.28*C_HO2*C_O*exp(-200.0/Temp) - 72265689.12*C_HOBR*C_O*exp(430.0/Temp) - 102376.39292*C_HOCL*C_O - 200.189309919559*C_M*C_O**2*exp(-720.0/Temp) - 191753838.55752*C_M*C_O*C_O2/Temp**2.4 + 12646495.596*C_N*C_NO*exp(-100.0/Temp) + 1746420.8204*C_N*C_NO2*exp(-220.0/Temp) + 1987306.4508*C_N*C_O2*exp(3150.0/Temp) + 12947602.634*C_N2*C_O1D*exp(-110.0/Temp) + 1.0*C_N2O5*J_34 + 1.0*C_NO*J_14 - 3071291.7876*C_NO2*C_O*exp(-210.0/Temp) + 1.0*C_NO2*J_75 - 7828782.988*C_NO3*C_O + 1.0*C_NO3*J_88 - 4817712.608*C_O*C_O3*exp(2060.0/Temp) - 12646495.596*C_O*C_OCS*exp(2200.0/Temp) - 10839853.368*C_O*C_OH*exp(-180.0/Temp) + 19873064.508*C_O1D*C_O2*exp(-55.0/Temp) + 72265689.12*C_O1D*C_O3 + 1385092.3748*C_O2*C_S + 96354.25216*C_O2*C_SO*exp(2280.0/Temp) + 1.0*C_O2*J_1 + 1.0*C_O2*J_119 + 1.0*C_O3*J_46 + 1.0*C_OCLO*J_30 + 1083985.3368*C_OH**2 + 1.0*C_SO*J_35 + 1.0*C_SO2*J_71 + 1.0*C_SO3*J_63) + (EXPLICIT: 0)
d[OCLO]/dt = (IMPLICIT: 572103.3722*C_BRO*C_CLO*exp(-550.0/Temp) + 210774.9266*C_CLO**2*exp(1370.0/Temp) - 1144206.7444*C_OCLO*C_SO - 1.0*C_OCLO*J_30) + (EXPLICIT: 0)
d[O1D]/dt = (IMPLICIT: -156997209.6132*C_CCL4*C_O1D - 58715872.41*C_CF2CLBR*C_O1D - 27099633.42*C_CF3BR*C_O1D - 124658313.732*C_CFC11*C_O1D - 125742299.0688*C_CFC113*C_O1D - 70459046.892*C_CFC114*C_O1D - 27966821.68944*C_CFC115*C_O1D - 72506574.7504*C_CFC12*C_O1D - 154769017.532*C_CH2BR2*C_O1D - 108398533.68*C_CH3BR*C_O1D - 105387463.3*C_CH4*C_O1D - 278222903.112*C_CHBR3*C_O1D - 12887381.2264*C_COF2*C_O1D - 114420674.44*C_COFCL*C_O1D - 72265689.12*C_H2*C_O1D - 72265689.12*C_H2402*C_O1D - 98160894.388*C_H2O*C_O1D*exp(-60.0/Temp) + 1.0*C_H2O*J_15 - 72265689.12*C_HBR*C_O1D - 108037205.2344*C_HCFC141B*C_O1D - 78287829.88*C_HCFC142B*C_O1D - 46069376.814*C_HCFC22*C_O1D - 61606499.9748*C_HCL*C_O1D - 65039120.208*C_HCN*C_O1D*exp(-105.0/Temp) - 12947602.634*C_N2*C_O1D*exp(-110.0/Temp) - 71663475.044*C_N2O*C_O1D*exp(-20.0/Temp) + 1.0*C_N2O*J_80 - 19873064.508*C_O1D*C_O2*exp(-55.0/Temp) - 144531378.24*C_O1D*C_O3 + 1.0*C_O2*J_119 + 1.0*C_O3*J_54) + (EXPLICIT: 0)
d[PHENO]/dt = (IMPLICIT: 1565756.5976*C_C6H5O2*C_NO*exp(-365.0/Temp) + 1.0*C_C6H5OOH*J_42 + 28304061.572*C_CRESOL*C_OH - 168619.94128*C_O3*C_PHENO + 283040.61572*C_OH*C_PHENOL*exp(-1220.0/Temp) + 50585982.384*C_OH*C_XYLOL) + (EXPLICIT: -1264649.5596*C_NO2*C_PHENO)
d[HCFC141B]/dt = (IMPLICIT: -108037205.2344*C_HCFC141B*C_O1D - 752767.595*C_HCFC141B*C_OH*exp(1600.0/Temp)) + (EXPLICIT: -1.0*C_HCFC141B*J_100)
d[HCFC142B]/dt = (IMPLICIT: -78287829.88*C_HCFC142B*C_O1D - 782878.2988*C_HCFC142B*C_OH*exp(1770.0/Temp)) + (EXPLICIT: -1.0*C_HCFC142B*J_28)
d[HCFC22]/dt = (IMPLICIT: -46069376.814*C_HCFC22*C_O1D - 554036.94992*C_HCFC22*C_OH*exp(1560.0/Temp)) + (EXPLICIT: -1.0*C_HCFC22*J_82)
d[DMS]/dt = (IMPLICIT: -114420.67444*C_DMS*C_NO3*exp(-520.0/Temp) - 1.0*C_DMS*C_OH*Rate_499 - 6624354.836*C_DMS*C_OH*exp(280.0/Temp)) + (EXPLICIT: 0)
d[C2H5OH]/dt = (IMPLICIT: 40950.557168*C_C2H5O2**2 + 120442.8152*C_C2H5O2*C_CH3O2 - 4155277.1244*C_C2H5OH*C_OH*exp(230.0/Temp)) + (EXPLICIT: 0)
d[HCL]/dt = (IMPLICIT: 43359413.472*C_C2H6*C_CL*exp(70.0/Temp) + 3793948.6788*C_CH2BR2*C_CL*exp(800.0/Temp) + 48779340.156*C_CH2O*C_CL*exp(30.0/Temp) + 8792325.5096*C_CH3BR*C_CL*exp(1040.0/Temp) + 12224945.7428*C_CH3CL*C_CL*exp(1100.0/Temp) + 4275719.9396*C_CH4*C_CL*exp(1270.0/Temp) + 2920738.2686*C_CHBR3*C_CL*exp(850.0/Temp) + 18367529.318*C_CL*C_H2*exp(2270.0/Temp) + 6624354.836*C_CL*C_H2O2*exp(980.0/Temp) + 8430997.064*C_CL*C_HO2*exp(-270.0/Temp) + 2047527.8584*C_CL*C_HOCL*exp(130.0/Temp) + 361328.4456*C_CLO*C_OH*exp(-230.0/Temp) - 1.0*C_CLONO2*C_HCL*Rate_539 - 1.0*C_CLONO2*C_HCL*Rate_544 - 1.0*C_CLONO2*C_HCL*Rate_546 - 1.0*C_HCL*C_HOBR*Rate_529 - 1.0*C_HCL*C_HOBR*Rate_541 - 1.0*C_HCL*C_HOCL*Rate_531 - 1.0*C_HCL*C_HOCL*Rate_532 - 1.0*C_HCL*C_HOCL*Rate_537 - 6022140.76*C_HCL*C_O*exp(3300.0/Temp) - 61606499.9748*C_HCL*C_O1D - 1083985.3368*C_HCL*C_OH*exp(250.0/Temp) - 1.0*C_HCL*J_108) + (EXPLICIT: 0)
d[BEPOMUC]/dt = (IMPLICIT: 1385092.3748*C_BENZENE*C_OH*exp(193.0/Temp) - 1.0*C_BEPOMUC*J_79) + (EXPLICIT: 0)
d[CHBR3]/dt = (IMPLICIT: -2920738.2686*C_CHBR3*C_CL*exp(850.0/Temp) - 278222903.112*C_CHBR3*C_O1D - 541992.6684*C_CHBR3*C_OH*exp(360.0/Temp)) + (EXPLICIT: -1.0*C_CHBR3*J_64)
d[H2402]/dt = (IMPLICIT: -72265689.12*C_H2402*C_O1D) + (EXPLICIT: -1.0*C_H2402*J_120)
d[CO2]/dt = (IMPLICIT: 2901294346.66027*0.5**(1.0/(log(160.590420266667*M_density*exp(-3.5/Temp))**2/log(10)**2 + 1.0))*C_MPAN*C_OH*M_density*exp(-3.5/Temp)/(160.590420266667*M_density*exp(-3.5/Temp) + 1.0) + 7226.568912*C_BCARY*C_O3 + 3914.391494*C_C3H6*C_O3*exp(1900.0/Temp) + 1746420.8204*C_CH3CO3**2*exp(-500.0/Temp) + 1204428.152*C_CH3CO3*C_CH3O2*exp(-500.0/Temp) + 8430997.064*C_CH3CO3*C_ISOPAO2 + 2770184.7496*C_CH3CO3*C_MCO3*exp(-530.0/Temp) + 4877934.0156*C_CH3CO3*C_NO*exp(-270.0/Temp) + 782878.2988*C_CH3CO3*C_XO2*exp(-640.0/Temp) + 18969.743394*C_CH3COOH*C_OH*exp(-920.0/Temp) + 602214.076*C_CH3COOOH*C_OH + 1.0*C_CH3COOOH*J_90 + 1204428.152*C_CH3O2*C_MCO3*exp(-500.0/Temp) + 1204428.152*C_CH3O2*C_TERP2O2*exp(-500.0/Temp) + 1.0*C_CH4*J_4 + 1.0*C_CO*C_OH*Rate_545 - 1.0*C_CO2*J_98 + 6022140.76*C_GLYALD*C_OH + 6925461.874*C_GLYOXAL*C_OH + 240885.6304*C_HCOOH*C_OH + 258952.05268*C_HO2*C_MCO3*exp(-1040.0/Temp) + 1385092.3748*C_MCO3**2*exp(-530.0/Temp) + 379.39486788*C_MTERP*C_O3*exp(580.0/Temp) + 511.8819646*C_MVK*C_O3*exp(1520.0/Temp) + 2529299.1192*C_NO*C_TERP2O2*exp(-180.0/Temp) + 20475278.584*C_OH*C_TERPROD2 + 1.0*C_PAN*J_45 + 1.0*C_TERP2OOH*J_5 + 1.0*C_TERPROD2*J_65) + (EXPLICIT: 0)
d[BZALD]/dt = (IMPLICIT: -3553063.0484*C_BZALD*C_OH*exp(-225.0/Temp) + 1565756.5976*C_BZOO*C_NO*exp(-365.0/Temp) + 1.0*C_BZOOH*J_57) + (EXPLICIT: 0)
d[BENZENE]/dt = (IMPLICIT: -1385092.3748*C_BENZENE*C_OH*exp(193.0/Temp)) + (EXPLICIT: 0)
d[C3H7O2]/dt = (IMPLICIT: -225830.2785*C_C3H7O2*C_CH3O2*exp(40.0/Temp) - 451660.557*C_C3H7O2*C_HO2*exp(-700.0/Temp) - 2529299.1192*C_C3H7O2*C_NO*exp(-180.0/Temp) + 2288413.4888*C_C3H7OOH*C_OH*exp(-200.0/Temp) + 5534347.35844*C_C3H8*C_OH*exp(630.0/Temp)) + (EXPLICIT: 0)
d[CH3O2]/dt = (IMPLICIT: -120442.8152*C_C2H5O2*C_CH3O2 + 3914.391494*C_C3H6*C_O3*exp(1900.0/Temp) - 225830.2785*C_C3H7O2*C_CH3O2*exp(40.0/Temp) + 1.0*C_CH3CHO*J_94 + 1746420.8204*C_CH3CO3**2*exp(-500.0/Temp) + 258952.05268*C_CH3CO3*C_HO2*exp(-1040.0/Temp) + 8430997.064*C_CH3CO3*C_ISOPAO2 + 8430997.064*C_CH3CO3*C_ISOPBO2 + 8430997.064*C_CH3CO3*C_ISOPNO3 + 8430997.064*C_CH3CO3*C_MACRO2 + 2770184.7496*C_CH3CO3*C_MCO3*exp(-530.0/Temp) + 4877934.0156*C_CH3CO3*C_NO*exp(-270.0/Temp) + 782878.2988*C_CH3CO3*C_XO2*exp(-640.0/Temp) + 1.0*C_CH3COCH3*J_67 + 18969.743394*C_CH3COOH*C_OH*exp(-920.0/Temp) + 1.0*C_CH3COOOH*J_90 - 602214.076*C_CH3O2**2*exp(424.0/Temp) - 22884.134888*C_CH3O2**2*exp(-706.0/Temp) - 1987306.4508*C_CH3O2*C_CLO*exp(115.0/Temp) - 246907.77116*C_CH3O2*C_HO2*exp(-750.0/Temp) - 301107.038*C_CH3O2*C_ISOPAO2*exp(-400.0/Temp) - 301107.038*C_CH3O2*C_ISOPBO2*exp(-400.0/Temp) - 301107.038*C_CH3O2*C_ISOPNO3*exp(-400.0/Temp) - 301107.038*C_CH3O2*C_MACRO2*exp(-400.0/Temp) - 1204428.152*C_CH3O2*C_MCO3*exp(-500.0/Temp) - 1686199.4128*C_CH3O2*C_NO*exp(-300.0/Temp) - 1204428.152*C_CH3O2*C_NTERPO2*exp(-500.0/Temp) - 427571.99396*C_CH3O2*C_RO2*exp(-500.0/Temp) - 1204428.152*C_CH3O2*C_TERP2O2*exp(-500.0/Temp) - 1204428.152*C_CH3O2*C_TERPO2*exp(-500.0/Temp) - 301107.038*C_CH3O2*C_XO2*exp(-400.0/Temp) + 2288413.4888*C_CH3OOH*C_OH*exp(-200.0/Temp) + 4275719.9396*C_CH4*C_CL*exp(1270.0/Temp) + 96354252.16*C_CH4*C_F*exp(260.0/Temp) + 78890043.956*C_CH4*C_O1D + 1475424.4862*C_CH4*C_OH*exp(1775.0/Temp) + 1.0*C_CH4*J_86 + 258952.05268*C_DICARBO2*C_HO2*exp(-1040.0/Temp) + 4516605.57*C_DICARBO2*C_NO*exp(-290.0/Temp) + 258952.05268*C_HO2*C_MDIALO2*exp(-1040.0/Temp) + 6323.247798*C_ISOP*C_O3*exp(2000.0/Temp) + 4516605.57*C_MDIALO2*C_NO*exp(-290.0/Temp) + 1.0*C_MVK*J_62 + 1.0*C_PAN*J_45) + (EXPLICIT: 1.0*C_CH3BR*J_51 + 1.0*C_CH3CL*J_107)
d[BCARY]/dt = (IMPLICIT: -11442067.444*C_BCARY*C_NO3 - 7226.568912*C_BCARY*C_O3 - 120442815.2*C_BCARY*C_OH) + (EXPLICIT: 0)
d[BIGALD]/dt = (IMPLICIT: 7226.568912*C_BCARY*C_O3 - 1.0*C_BIGALD*J_60 + 379.39486788*C_MTERP*C_O3*exp(580.0/Temp)) + (EXPLICIT: 0)
d[BIGALD2]/dt = (IMPLICIT: -1.0*C_BIGALD2*J_49 + 1565756.5976*C_NO*C_TOLO2*exp(-365.0/Temp) + 1565756.5976*C_NO*C_XYLENO2*exp(-365.0/Temp) + 1.0*C_TOLOOH*J_109 + 1.0*C_XYLENOOH*J_3) + (EXPLICIT: 0)
d[BIGALD3]/dt = (IMPLICIT: -1.0*C_BIGALD3*J_76 + 1.0*C_HPALD*J_56 + 1.0*C_NC4CHO*J_83 + 1565756.5976*C_NO*C_TOLO2*exp(-365.0/Temp) + 1565756.5976*C_NO*C_XYLENO2*exp(-365.0/Temp) + 1.0*C_TOLOOH*J_109 + 1.0*C_XYLENOOH*J_3) + (EXPLICIT: 0)
d[BIGALD4]/dt = (IMPLICIT: -1.0*C_BIGALD4*J_7 + 1565756.5976*C_NO*C_XYLENO2*exp(-365.0/Temp) + 1.0*C_XYLENOOH*J_3) + (EXPLICIT: 0)
d[BIGALK]/dt = (IMPLICIT: 7226.568912*C_BCARY*C_O3 - 2107749.266*C_BIGALK*C_OH + 379.39486788*C_MTERP*C_O3*exp(580.0/Temp)) + (EXPLICIT: 0)
d[H2O2]/dt = (IMPLICIT: 250236.637399448*0.6**(1.0/(log(0.0159818350938462*M_density*exp(-1.0/Temp))**2/log(10)**2 + 1.0))*C_OH**2*M_density*exp(-1.0/Temp)/(0.0159818350938462*M_density*exp(-1.0/Temp) + 1.0) - 6624354.836*C_CL*C_H2O2*exp(980.0/Temp) + 0.642096108110429*C_H2O*C_HO2**2*C_M*exp(-3120.0/Temp) + 152.317953199664*C_H2O*C_HO2**2*exp(-2660.0/Temp) - 843099.7064*C_H2O2*C_O*exp(2000.0/Temp) - 1083985.3368*C_H2O2*C_OH - 1.0*C_H2O2*J_29 + 761.589765998321*C_HO2**2*C_M*exp(-920.0/Temp) + 180664.2228*C_HO2**2*exp(-460.0/Temp)) + (EXPLICIT: 0)
d[C2H5OOH]/dt = (IMPLICIT: 451660.557*C_C2H5O2*C_HO2*exp(-700.0/Temp) - 2288413.4888*C_C2H5OOH*C_OH*exp(-200.0/Temp) - 1.0*C_C2H5OOH*J_97) + (EXPLICIT: 0)
d[C2H6]/dt = (IMPLICIT: -43359413.472*C_C2H6*C_CL*exp(70.0/Temp) - 4612959.82216*C_C2H6*C_OH*exp(1020.0/Temp)) + (EXPLICIT: 0)
d[C3H8]/dt = (IMPLICIT: -5534347.35844*C_C3H8*C_OH*exp(630.0/Temp)) + (EXPLICIT: 0)
d[C3H6]/dt = (IMPLICIT: -2901294346.66027*0.5**(1.0/(log(160.590420266667*M_density*exp(-3.5/Temp))**2/log(10)**2 + 1.0))*C_C3H6*C_OH*M_density*exp(-3.5/Temp)/(160.590420266667*M_density*exp(-3.5/Temp) + 1.0) - 277018.47496*C_C3H6*C_NO3*exp(1156.0/Temp) - 3914.391494*C_C3H6*C_O3*exp(1900.0/Temp) + 6323.247798*C_ISOP*C_O3*exp(2000.0/Temp) + 1.0*C_MVK*J_62) + (EXPLICIT: 0)
d[CH2O]/dt = (IMPLICIT: 2901294346.66027*0.5**(1.0/(log(160.590420266667*M_density*exp(-3.5/Temp))**2/log(10)**2 + 1.0))*C_MPAN*C_OH*M_density*exp(-3.5/Temp)/(160.590420266667*M_density*exp(-3.5/Temp) + 1.0) + 963542.5216*C_ALKNIT*C_OH + 1.0*C_ALKNIT*J_59 + 4034834.3092*C_ALKO2*C_NO + 1.0*C_ALKOOH*J_37 + 7226.568912*C_BCARY*C_O3 + 210774.9266*C_BIGENE*C_NO3 - 10237639.292*C_BR*C_CH2O*exp(800.0/Temp) + 7226.568912*C_C2H4*C_O3*exp(2630.0/Temp) + 120442.8152*C_C2H5O2*C_CH3O2 + 3914.391494*C_C3H6*C_O3*exp(1900.0/Temp) + 225830.2785*C_C3H7O2*C_CH3O2*exp(40.0/Temp) - 48779340.156*C_CH2O*C_CL*exp(30.0/Temp) - 5841.4765372*C_CH2O*C_HO2*exp(-625.0/Temp) - 361328.4456*C_CH2O*C_NO3*exp(2058.0/Temp) - 20475278.584*C_CH2O*C_O*exp(1600.0/Temp) - 3312177.418*C_CH2O*C_OH*exp(-125.0/Temp) - 1.0*C_CH2O*J_12 - 1.0*C_CH2O*J_81 + 1204428.152*C_CH3CO3*C_CH3O2*exp(-500.0/Temp) + 8430997.064*C_CH3CO3*C_ISOPAO2 + 8430997.064*C_CH3CO3*C_MACRO2 + 2770184.7496*C_CH3CO3*C_MCO3*exp(-530.0/Temp) + 782878.2988*C_CH3CO3*C_XO2*exp(-640.0/Temp) + 602214.076*C_CH3COOOH*C_OH + 301107.038*C_CH3O2**2*exp(424.0/Temp) + 11442.067444*C_CH3O2**2*exp(-706.0/Temp) + 1987306.4508*C_CH3O2*C_CLO*exp(115.0/Temp) + 301107.038*C_CH3O2*C_ISOPAO2*exp(-400.0/Temp) + 301107.038*C_CH3O2*C_ISOPBO2*exp(-400.0/Temp) + 301107.038*C_CH3O2*C_ISOPNO3*exp(-400.0/Temp) + 301107.038*C_CH3O2*C_MACRO2*exp(-400.0/Temp) + 1204428.152*C_CH3O2*C_MCO3*exp(-500.0/Temp) + 1686199.4128*C_CH3O2*C_NO*exp(-300.0/Temp) + 1204428.152*C_CH3O2*C_NTERPO2*exp(-500.0/Temp) + 427571.99396*C_CH3O2*C_RO2*exp(-500.0/Temp) + 1204428.152*C_CH3O2*C_TERP2O2*exp(-500.0/Temp) + 1204428.152*C_CH3O2*C_TERPO2*exp(-500.0/Temp) + 301107.038*C_CH3O2*C_XO2*exp(-400.0/Temp) + 1746420.8204*C_CH3OH*C_OH*exp(345.0/Temp) + 2288413.4888*C_CH3OOH*C_OH*exp(-200.0/Temp) + 1.0*C_CH3OOH*J_116 + 26497419.344*C_CH4*C_O1D + 1.0*C_CH4*J_4 + 2890627.5648*C_ENEO2*C_NO*exp(-120.0/Temp) + 160000000000.0*C_EO*exp(4150.0/Temp) + 2529299.1192*C_EO2*C_NO*exp(-180.0/Temp) + 6022140.76*C_GLYALD*C_OH + 1.0*C_GLYALD*J_112 + 258952.05268*C_HO2*C_MCO3*exp(-1040.0/Temp) + 517904.10536*C_HO2*C_RO2*exp(-700.0/Temp) + 2400000000000.0*C_HOCH2OO*exp(7000.0/Temp) + 1.0*C_HONITR*J_84 + 1.0*C_HYAC*J_27 + 6323.247798*C_ISOP*C_O3*exp(2000.0/Temp) + 2649741.9344*C_ISOPAO2*C_NO*exp(-180.0/Temp) + 1445313.7824*C_ISOPAO2*C_NO3 + 24088563.04*C_ISOPNITA*C_OH + 1.0*C_ISOPOOH*J_41 + 903.321114*C_MACR*C_O3*exp(2100.0/Temp) + 1.0*C_MACR*J_32 + 1625978.0052*C_MACRO2*C_NO*exp(-360.0/Temp) + 1445313.7824*C_MACRO2*C_NO3 + 1385092.3748*C_MCO3**2*exp(-530.0/Temp) + 3191734.6028*C_MCO3*C_NO*exp(-360.0/Temp) + 3011070.38*C_MCO3*C_NO3 + 379.39486788*C_MTERP*C_O3*exp(580.0/Temp) + 511.8819646*C_MVK*C_O3*exp(1520.0/Temp) + 2529299.1192*C_NO*C_PO2*exp(-180.0/Temp) + 1746420.8204*C_NO*C_RO2*exp(-300.0/Temp) + 2529299.1192*C_NO*C_TERP2O2*exp(-180.0/Temp) + 2529299.1192*C_NO*C_TERPO2*exp(-180.0/Temp) + 1625978.0052*C_NO*C_XO2*exp(-360.0/Temp) + 1.0*C_NOA*J_19 + 24088.56304*C_OH*C_PAN + 20475278.584*C_OH*C_TERPROD2 + 1.0*C_POOH*J_25 + 1.0*C_ROOH*J_23 + 1.0*C_TERP2OOH*J_5 + 1.0*C_TERPOOH*J_92 + 1.0*C_TERPROD2*J_65) + (EXPLICIT: 0)
d[CH3CN]/dt = (IMPLICIT: -469726.97928*C_CH3CN*C_OH*exp(1050.0/Temp)) + (EXPLICIT: 0)
d[C2H2]/dt = (IMPLICIT: -1994639.86332894*0.6**(1.0/(log(3.99057520240964*M_density*exp(-2.0/Temp))**2/log(10)**2 + 1.0))*C_C2H2*C_OH*M_density/(3.99057520240964*M_density*exp(-2.0/Temp) + 1.0) - 1885841.32532918*0.6**(1.0/(log(0.0142341508872727*M_density*exp(-1.7/Temp))**2/log(10)**2 + 1.0))*C_C2H2*C_CL*M_density*exp(-2.4/Temp)/(0.0142341508872727*M_density*exp(-1.7/Temp) + 1.0)) + (EXPLICIT: 0)
d[CH3OH]/dt = (IMPLICIT: 120442.8152*C_C2H5O2*C_CH3O2 + 11442.067444*C_CH3O2**2*exp(-706.0/Temp) + 301107.038*C_CH3O2*C_ISOPAO2*exp(-400.0/Temp) + 301107.038*C_CH3O2*C_ISOPBO2*exp(-400.0/Temp) + 301107.038*C_CH3O2*C_ISOPNO3*exp(-400.0/Temp) + 301107.038*C_CH3O2*C_MACRO2*exp(-400.0/Temp) + 1204428.152*C_CH3O2*C_NTERPO2*exp(-500.0/Temp) + 427571.99396*C_CH3O2*C_RO2*exp(-500.0/Temp) + 1204428.152*C_CH3O2*C_TERP2O2*exp(-500.0/Temp) + 1204428.152*C_CH3O2*C_TERPO2*exp(-500.0/Temp) + 301107.038*C_CH3O2*C_XO2*exp(-400.0/Temp) - 1746420.8204*C_CH3OH*C_OH*exp(345.0/Temp)) + (EXPLICIT: 0)
d[CH3OOH]/dt = (IMPLICIT: 246907.77116*C_CH3O2*C_HO2*exp(-750.0/Temp) - 2288413.4888*C_CH3OOH*C_OH*exp(-200.0/Temp) - 1.0*C_CH3OOH*J_116) + (EXPLICIT: 0)
d[CRESOL]/dt = (IMPLICIT: -28304061.572*C_CRESOL*C_OH + 1023763.9292*C_OH*C_TOLUENE*exp(-352.0/Temp)) + (EXPLICIT: 0)
d[ENEO2]/dt = (IMPLICIT: 32519560.104*C_BIGENE*C_OH - 30712.917876*C_ENEO2*C_NO*exp(-693.0/Temp) - 2890627.5648*C_ENEO2*C_NO*exp(-120.0/Temp)) + (EXPLICIT: 0)
d[MACRO2]/dt = (IMPLICIT: -8430997.064*C_CH3CO3*C_MACRO2 - 301107.038*C_CH3O2*C_MACRO2*exp(-400.0/Temp) - 481771.2608*C_HO2*C_MACRO2*exp(-700.0/Temp) + 5781255.1296*C_MACR*C_OH*exp(-360.0/Temp) - 1704265.83508*C_MACRO2*C_NO*exp(-360.0/Temp) - 1445313.7824*C_MACRO2*C_NO3 + 13850923.748*C_MACROOH*C_OH*exp(-200.0/Temp) + 2487144.13388*C_MVK*C_OH*exp(-452.0/Temp)) + (EXPLICIT: 0)
d[ISOPAO2]/dt = (IMPLICIT: -8430997.064*C_CH3CO3*C_ISOPAO2 - 301107.038*C_CH3O2*C_ISOPAO2*exp(-400.0/Temp) - 481771.2608*C_HO2*C_ISOPAO2*exp(-700.0/Temp) + 15296237.5304*C_ISOP*C_OH*exp(-410.0/Temp) - 2649741.9344*C_ISOPAO2*C_NO*exp(-180.0/Temp) - 1445313.7824*C_ISOPAO2*C_NO3) + (EXPLICIT: 0)
d[MALO2]/dt = (IMPLICIT: 1.0*C_BIGALD1*J_95 - 258952.05268*C_HO2*C_MALO2*exp(-1040.0/Temp) - 4516605.57*C_MALO2*C_NO*exp(-290.0/Temp)) + (EXPLICIT: -35178193.9532558*0.6**(1.0/(log(6.28115756688172*M_density*exp(-4.1/Temp))**2/log(10)**2 + 1.0))*C_MALO2*C_NO2*M_density*exp(-5.6/Temp)/(6.28115756688172*M_density*exp(-4.1/Temp) + 1.0))
d[ISOPBO2]/dt = (IMPLICIT: -8430997.064*C_CH3CO3*C_ISOPBO2 - 301107.038*C_CH3O2*C_ISOPBO2*exp(-400.0/Temp) - 481771.2608*C_HO2*C_ISOPBO2*exp(-700.0/Temp) + 15296237.5304*C_ISOP*C_OH*exp(-410.0/Temp) - 2649741.9344*C_ISOPBO2*C_NO*exp(-180.0/Temp) - 1445313.7824*C_ISOPBO2*C_NO3 - 1600000000.0*C_ISOPBO2*exp(8300.0/Temp)) + (EXPLICIT: 0)
d[MCO3]/dt = (IMPLICIT: 1.30217879922136e-34662*0.6**(1.0/(log(6.28115756688172*M_density*exp(-4.1/Temp))**2/log(10)**2 + 1.0))*C_MPAN*M_density*Temp**14000.0*exp(-5.6/Temp)/(6.28115756688172*M_density*exp(-4.1/Temp) + 1.0) - 35178193.9532558*0.6**(1.0/(log(6.28115756688172*M_density*exp(-4.1/Temp))**2/log(10)**2 + 1.0))*C_MCO3*C_NO2*M_density*exp(-5.6/Temp)/(6.28115756688172*M_density*exp(-4.1/Temp) + 1.0) - 2770184.7496*C_CH3CO3*C_MCO3*exp(-530.0/Temp) - 1204428.152*C_CH3O2*C_MCO3*exp(-500.0/Temp) - 258952.05268*C_HO2*C_MCO3*exp(-1040.0/Temp) + 5781255.1296*C_MACR*C_OH*exp(-360.0/Temp) + 1.0*C_MACR*J_32 + 13850923.748*C_MACROOH*C_OH*exp(-200.0/Temp) - 2770184.7496*C_MCO3**2*exp(-530.0/Temp) - 3191734.6028*C_MCO3*C_NO*exp(-360.0/Temp) - 3011070.38*C_MCO3*C_NO3 + 1.0*C_MPAN*J_102) + (EXPLICIT: 0)
d[MDIALO2]/dt = (IMPLICIT: 1.0*C_BIGALD3*J_76 - 258952.05268*C_HO2*C_MDIALO2*exp(-1040.0/Temp) - 4516605.57*C_MDIALO2*C_NO*exp(-290.0/Temp)) + (EXPLICIT: -35178193.9532558*0.6**(1.0/(log(6.28115756688172*M_density*exp(-4.1/Temp))**2/log(10)**2 + 1.0))*C_MDIALO2*C_NO2*M_density*exp(-5.6/Temp)/(6.28115756688172*M_density*exp(-4.1/Temp) + 1.0))
d[MEKO2]/dt = (IMPLICIT: -451660.557*C_HO2*C_MEKO2*exp(-700.0/Temp) + 1385092.3748*C_MEK*C_OH*exp(170.0/Temp) - 2529299.1192*C_MEKO2*C_NO*exp(-180.0/Temp) + 2288413.4888*C_MEKOOH*C_OH*exp(-200.0/Temp)) + (EXPLICIT: 0)
d[EO2]/dt = (IMPLICIT: 31188914.2265979*0.48**(1.0/(log(5.75449005955556*M_density*exp(-2.25/Temp))**2/log(10)**2 + 1.0))*C_C2H4*C_OH*M_density*exp(-3.1/Temp)/(5.75449005955556*M_density*exp(-2.25/Temp) + 1.0) - 451660.557*C_EO2*C_HO2*exp(-700.0/Temp) - 2529299.1192*C_EO2*C_NO*exp(-180.0/Temp)) + (EXPLICIT: 0)
d[EO]/dt = (IMPLICIT: -6022.14076*C_EO*C_O2 - 160000000000.0*C_EO*exp(4150.0/Temp) + 2529299.1192*C_EO2*C_NO*exp(-180.0/Temp) + 1.0*C_EOOH*J_39) + (EXPLICIT: 0)
d[GLYOXAL]/dt = (IMPLICIT: 1994639.86332894*0.6**(1.0/(log(3.99057520240964*M_density*exp(-2.0/Temp))**2/log(10)**2 + 1.0))*C_C2H2*C_OH*M_density/(3.99057520240964*M_density*exp(-2.0/Temp) + 1.0) + 1565756.5976*C_BENZO2*C_NO*exp(-365.0/Temp) + 1.0*C_BENZOOH*J_33 + 1.0*C_BIGALD*J_60 + 782878.2988*C_CH3CO3*C_XO2*exp(-640.0/Temp) + 301107.038*C_CH3O2*C_XO2*exp(-400.0/Temp) + 6022140.76*C_GLYALD*C_OH - 6925461.874*C_GLYOXAL*C_OH - 1.0*C_GLYOXAL*J_53 + 258952.05268*C_HO2*C_MALO2*exp(-1040.0/Temp) + 258952.05268*C_HO2*C_MDIALO2*exp(-1040.0/Temp) + 2649741.9344*C_ISOPBO2*C_NO*exp(-180.0/Temp) + 1445313.7824*C_ISOPBO2*C_NO3 + 4516605.57*C_MALO2*C_NO*exp(-290.0/Temp) + 4516605.57*C_MDIALO2*C_NO*exp(-290.0/Temp) + 60221407.6*C_NC4CHO*C_OH + 1565756.5976*C_NO*C_PHENO2*exp(-365.0/Temp) + 1565756.5976*C_NO*C_TOLO2*exp(-365.0/Temp) + 1625978.0052*C_NO*C_XO2*exp(-360.0/Temp) + 1565756.5976*C_NO*C_XYLENO2*exp(-365.0/Temp) + 1565756.5976*C_NO*C_XYLOLO2*exp(-365.0/Temp) + 1445313.7824*C_NO3*C_XO2 + 1.0*C_PHENOOH*J_73 + 1.0*C_TOLOOH*J_109 + 1.0*C_XYLENOOH*J_3 + 1.0*C_XYLOLOOH*J_70) + (EXPLICIT: 0)
d[MPAN]/dt = (IMPLICIT: -2901294346.66027*0.5**(1.0/(log(160.590420266667*M_density*exp(-3.5/Temp))**2/log(10)**2 + 1.0))*C_MPAN*C_OH*M_density*exp(-3.5/Temp)/(160.590420266667*M_density*exp(-3.5/Temp) + 1.0) - 1.30217879922136e-34662*0.6**(1.0/(log(6.28115756688172*M_density*exp(-4.1/Temp))**2/log(10)**2 + 1.0))*C_MPAN*M_density*Temp**14000.0*exp(-5.6/Temp)/(6.28115756688172*M_density*exp(-4.1/Temp) + 1.0) + 35178193.9532558*0.6**(1.0/(log(6.28115756688172*M_density*exp(-4.1/Temp))**2/log(10)**2 + 1.0))*C_MCO3*C_NO2*M_density*exp(-5.6/Temp)/(6.28115756688172*M_density*exp(-4.1/Temp) + 1.0) - 1.0*C_MPAN*J_102) + (EXPLICIT: 0)
d[NC4CH2OH]/dt = (IMPLICIT: 301107.038*C_CH3O2*C_ISOPNO3*exp(-400.0/Temp) - 42154985.32*C_NC4CH2OH*C_OH) + (EXPLICIT: 0)
d[ISOPOOH]/dt = (IMPLICIT: 481771.2608*C_HO2*C_ISOPAO2*exp(-700.0/Temp) + 481771.2608*C_HO2*C_ISOPBO2*exp(-700.0/Temp) + 1.0*C_ISOPNOOH*J_36 - 9153653.9552*C_ISOPOOH*C_OH*exp(-200.0/Temp) - 1.0*C_ISOPOOH*J_41) + (EXPLICIT: 0)
d[GLYALD]/dt = (IMPLICIT: 8430997.064*C_CH3CO3*C_MACRO2 + 782878.2988*C_CH3CO3*C_XO2*exp(-640.0/Temp) + 301107.038*C_CH3O2*C_MACRO2*exp(-400.0/Temp) + 1204428.152*C_CH3O2*C_TERP2O2*exp(-500.0/Temp) + 301107.038*C_CH3O2*C_XO2*exp(-400.0/Temp) + 6022.14076*C_EO*C_O2 - 6022140.76*C_GLYALD*C_OH - 1.0*C_GLYALD*J_112 + 1.0*C_HONITR*J_84 + 2649741.9344*C_ISOPBO2*C_NO*exp(-180.0/Temp) + 1445313.7824*C_ISOPBO2*C_NO3 + 24088563.04*C_ISOPNITA*C_OH + 24088563.04*C_ISOPNITB*C_OH + 1625978.0052*C_MACRO2*C_NO*exp(-360.0/Temp) + 1445313.7824*C_MACRO2*C_NO3 + 42154985.32*C_NC4CH2OH*C_OH + 2529299.1192*C_NO*C_TERP2O2*exp(-180.0/Temp) + 1625978.0052*C_NO*C_XO2*exp(-360.0/Temp) + 1445313.7824*C_NO3*C_XO2 + 1.0*C_TERP2OOH*J_5) + (EXPLICIT: 0)
d[HO2]/dt = (IMPLICIT: 2901294346.66027*0.5**(1.0/(log(160.590420266667*M_density*exp(-3.5/Temp))**2/log(10)**2 + 1.0))*C_MPAN*C_OH*M_density*exp(-3.5/Temp)/(160.590420266667*M_density*exp(-3.5/Temp) + 1.0) + 105171.920066435*0.6**(1.0/(log(0.102730636494118*M_density*exp(-4.3/Temp))**2/log(10)**2 + 1.0))*C_OH*C_SO2*M_density*exp(-4.1/Temp)/(0.102730636494118*M_density*exp(-4.3/Temp) + 1.0) + 1.30199334468671e-26987*0.6**(1.0/(log(0.02860516861*M_density*exp(-3.1/Temp))**2/log(10)**2 + 1.0))*C_HO2NO2*M_density*Temp**10900.0*exp(-3.4/Temp)/(0.02860516861*M_density*exp(-3.1/Temp) + 1.0) - 68905.7407331814*0.6**(1.0/(log(0.02860516861*M_density*exp(-3.1/Temp))**2/log(10)**2 + 1.0))*C_HO2*C_NO2*M_density*exp(-3.4/Temp)/(0.02860516861*M_density*exp(-3.1/Temp) + 1.0) + 19221.0750466243*0.6**(1.0/(log(0.000335972063452632*M_density*exp(-2.2/Temp))**2/log(10)**2 + 1.0))*C_H*C_O2*M_density*exp(-1.8/Temp)/(0.000335972063452632*M_density*exp(-2.2/Temp) + 1.0) + 1994639.86332894*0.6**(1.0/(log(3.99057520240964*M_density*exp(-2.0/Temp))**2/log(10)**2 + 1.0))*C_C2H2*C_OH*M_density/(3.99057520240964*M_density*exp(-2.0/Temp) + 1.0) + 2212.23693932846*0.8**(1.0/(log(0.374847537102041*M_density*exp(-6.1/Temp))**2/log(10)**2 + 1.0))*C_HCN*C_OH*M_density*exp(-1.5/Temp)/(0.374847537102041*M_density*exp(-6.1/Temp) + 1.0) - 258952.05268*C_ACBZO2*C_HO2*exp(-1040.0/Temp) + 1.0*C_ALKNIT*J_59 - 451660.557*C_ALKO2*C_HO2*exp(-700.0/Temp) + 4034834.3092*C_ALKO2*C_NO + 1.0*C_ALKOOH*J_37 + 7226.568912*C_BCARY*C_O3 + 1385092.3748*C_BENZENE*C_OH*exp(193.0/Temp) - 451660.557*C_BENZO2*C_HO2*exp(-700.0/Temp) + 1565756.5976*C_BENZO2*C_NO*exp(-365.0/Temp) + 1.0*C_BENZOOH*J_33 + 1.0*C_BEPOMUC*J_79 + 1.0*C_BIGALD*J_60 + 1.0*C_BIGALD1*J_95 + 1.0*C_BIGALD2*J_49 + 1.0*C_BIGALD3*J_76 + 1.0*C_BIGALD4*J_7 + 10237639.292*C_BR*C_CH2O*exp(800.0/Temp) - 2890627.5648*C_BR*C_HO2*exp(310.0/Temp) - 2709963.342*C_BRO*C_HO2*exp(-460.0/Temp) + 10237639.292*C_BRO*C_OH*exp(-250.0/Temp) - 451660.557*C_BZOO*C_HO2*exp(-700.0/Temp) + 1565756.5976*C_BZOO*C_NO*exp(-365.0/Temp) + 1.0*C_BZOOH*J_57 + 7226.568912*C_C2H4*C_O3*exp(2630.0/Temp) + 40950.557168*C_C2H5O2**2 + 120442.8152*C_C2H5O2*C_CH3O2 - 451660.557*C_C2H5O2*C_HO2*exp(-700.0/Temp) + 1565756.5976*C_C2H5O2*C_NO*exp(-365.0/Temp) + 4155277.1244*C_C2H5OH*C_OH*exp(230.0/Temp) + 1.0*C_C2H5OOH*J_97 + 3914.391494*C_C3H6*C_O3*exp(1900.0/Temp) + 225830.2785*C_C3H7O2*C_CH3O2*exp(40.0/Temp) - 451660.557*C_C3H7O2*C_HO2*exp(-700.0/Temp) + 2529299.1192*C_C3H7O2*C_NO*exp(-180.0/Temp) + 1.0*C_C3H7OOH*J_16 - 451660.557*C_C6H5O2*C_HO2*exp(-700.0/Temp) + 48779340.156*C_CH2O*C_CL*exp(30.0/Temp) - 5841.4765372*C_CH2O*C_HO2*exp(-625.0/Temp) + 361328.4456*C_CH2O*C_NO3*exp(2058.0/Temp) + 20475278.584*C_CH2O*C_O*exp(1600.0/Temp) + 8792325.5096*C_CH3BR*C_CL*exp(1040.0/Temp) + 855143.98792*C_CH3BR*C_OH*exp(1150.0/Temp) + 1.0*C_CH3CHO*J_94 + 12224945.7428*C_CH3CL*C_CL*exp(1100.0/Temp) + 1180339.58896*C_CH3CL*C_OH*exp(1200.0/Temp) + 469726.97928*C_CH3CN*C_OH*exp(1050.0/Temp) + 1204428.152*C_CH3CO3*C_CH3O2*exp(-500.0/Temp) - 258952.05268*C_CH3CO3*C_HO2*exp(-1040.0/Temp) + 8430997.064*C_CH3CO3*C_ISOPAO2 + 8430997.064*C_CH3CO3*C_ISOPBO2 + 8430997.064*C_CH3CO3*C_ISOPNO3 + 8430997.064*C_CH3CO3*C_MACRO2 + 782878.2988*C_CH3CO3*C_XO2*exp(-640.0/Temp) + 1.0*C_CH3COCHO*J_2 + 301107.038*C_CH3O2**2*exp(424.0/Temp) + 1987306.4508*C_CH3O2*C_CLO*exp(115.0/Temp) - 246907.77116*C_CH3O2*C_HO2*exp(-750.0/Temp) + 301107.038*C_CH3O2*C_ISOPAO2*exp(-400.0/Temp) + 301107.038*C_CH3O2*C_ISOPBO2*exp(-400.0/Temp) + 301107.038*C_CH3O2*C_ISOPNO3*exp(-400.0/Temp) + 301107.038*C_CH3O2*C_MACRO2*exp(-400.0/Temp) + 1204428.152*C_CH3O2*C_MCO3*exp(-500.0/Temp) + 1686199.4128*C_CH3O2*C_NO*exp(-300.0/Temp) + 1204428.152*C_CH3O2*C_NTERPO2*exp(-500.0/Temp) + 427571.99396*C_CH3O2*C_RO2*exp(-500.0/Temp) + 1204428.152*C_CH3O2*C_TERP2O2*exp(-500.0/Temp) + 1204428.152*C_CH3O2*C_TERPO2*exp(-500.0/Temp) + 301107.038*C_CH3O2*C_XO2*exp(-400.0/Temp) + 1746420.8204*C_CH3OH*C_OH*exp(345.0/Temp) + 21077492.66*C_CH4*C_O1D + 6624354.836*C_CL*C_H2O2*exp(980.0/Temp) - 21679706.736*C_CL*C_HO2*exp(375.0/Temp) - 8430997.064*C_CL*C_HO2*exp(-270.0/Temp) - 1565756.5976*C_CLO*C_HO2*exp(-290.0/Temp) + 4456384.1624*C_CLO*C_OH*exp(-270.0/Temp) + 1.0*C_CO*C_OH*Rate_545 + 28304061.572*C_CRESOL*C_OH + 4516605.57*C_DICARBO2*C_NO*exp(-290.0/Temp) + 1.0*C_DMS*C_OH*Rate_499 + 2890627.5648*C_ENEO2*C_NO*exp(-120.0/Temp) + 6022.14076*C_EO*C_O2 + 160000000000.0*C_EO*exp(4150.0/Temp) - 451660.557*C_EO2*C_HO2*exp(-700.0/Temp) + 2529299.1192*C_EO2*C_NO*exp(-180.0/Temp) + 6022140.76*C_GLYALD*C_OH + 1.0*C_GLYALD*J_112 + 6925461.874*C_GLYOXAL*C_OH + 1.0*C_GLYOXAL*J_53 - 48478233.118*C_H*C_HO2 - 1.28419221622086*C_H2O*C_HO2**2*C_M*exp(-3120.0/Temp) - 304.635906399328*C_H2O*C_HO2**2*exp(-2660.0/Temp) + 843099.7064*C_H2O2*C_O*exp(2000.0/Temp) + 1083985.3368*C_H2O2*C_OH + 240885.6304*C_HCOOH*C_OH - 1523.17953199664*C_HO2**2*C_M*exp(-920.0/Temp) - 361328.4456*C_HO2**2*exp(-460.0/Temp) - 451660.557*C_HO2*C_HOCH2OO*exp(-700.0/Temp) - 481771.2608*C_HO2*C_ISOPAO2*exp(-700.0/Temp) - 481771.2608*C_HO2*C_ISOPBO2*exp(-700.0/Temp) - 481771.2608*C_HO2*C_ISOPNO3*exp(-700.0/Temp) - 481771.2608*C_HO2*C_MACRO2*exp(-700.0/Temp) - 258952.05268*C_HO2*C_MCO3*exp(-1040.0/Temp) - 451660.557*C_HO2*C_MEKO2*exp(-700.0/Temp) - 2071616.42144*C_HO2*C_NO*exp(-260.0/Temp) - 2107749.266*C_HO2*C_NO3 - 451660.557*C_HO2*C_NTERPO2*exp(-700.0/Temp) - 18066422.28*C_HO2*C_O*exp(-200.0/Temp) - 6022.14076*C_HO2*C_O3*exp(490.0/Temp) - 28906275.648*C_HO2*C_OH*exp(-250.0/Temp) - 451660.557*C_HO2*C_PHENO2*exp(-700.0/Temp) - 451660.557*C_HO2*C_PO2*exp(-700.0/Temp) - 517904.10536*C_HO2*C_RO2*exp(-700.0/Temp) - 451660.557*C_HO2*C_TERP2O2*exp(-700.0/Temp) - 451660.557*C_HO2*C_TERPO2*exp(-700.0/Temp) - 451660.557*C_HO2*C_TOLO2*exp(-700.0/Temp) - 481771.2608*C_HO2*C_XO2*exp(-700.0/Temp) - 451660.557*C_HO2*C_XYLENO2*exp(-700.0/Temp) - 451660.557*C_HO2*C_XYLOLO2*exp(-700.0/Temp) + 1.0*C_HO2NO2*J_44 + 1565756.5976*C_HOCH2OO*C_NO*exp(-265.0/Temp) + 2400000000000.0*C_HOCH2OO*exp(7000.0/Temp) + 1204428.152*C_HONITR*C_OH + 1.0*C_HONITR*J_84 + 1.0*C_HPALD*J_56 + 1806642.228*C_HYAC*C_OH + 1.0*C_HYAC*J_27 + 6323.247798*C_ISOP*C_O3*exp(2000.0/Temp) + 2649741.9344*C_ISOPAO2*C_NO*exp(-180.0/Temp) + 1445313.7824*C_ISOPAO2*C_NO3 + 2649741.9344*C_ISOPBO2*C_NO*exp(-180.0/Temp) + 1445313.7824*C_ISOPBO2*C_NO3 + 1600000000.0*C_ISOPBO2*exp(8300.0/Temp) + 24088563.04*C_ISOPNITA*C_OH + 24088563.04*C_ISOPNITB*C_OH + 1625978.0052*C_ISOPNO3*C_NO*exp(-360.0/Temp) + 1445313.7824*C_ISOPNO3*C_NO3 + 24088563.04*C_ISOPNOOH*C_OH + 1.0*C_ISOPNOOH*J_36 + 1.0*C_ISOPOOH*J_41 + 903.321114*C_MACR*C_O3*exp(2100.0/Temp) + 1.0*C_MACR*J_21 + 1.0*C_MACR*J_32 + 1625978.0052*C_MACRO2*C_NO*exp(-360.0/Temp) + 1445313.7824*C_MACRO2*C_NO3 + 13850923.748*C_MACROOH*C_OH*exp(-200.0/Temp) + 4516605.57*C_MALO2*C_NO*exp(-290.0/Temp) + 4516605.57*C_MDIALO2*C_NO*exp(-290.0/Temp) + 379.39486788*C_MTERP*C_O3*exp(580.0/Temp) + 511.8819646*C_MVK*C_O3*exp(1520.0/Temp) + 42154985.32*C_NC4CH2OH*C_OH + 60221407.6*C_NC4CHO*C_OH + 1.0*C_NC4CHO*J_83 + 1565756.5976*C_NO*C_PHENO2*exp(-365.0/Temp) + 2529299.1192*C_NO*C_PO2*exp(-180.0/Temp) + 2529299.1192*C_NO*C_TERP2O2*exp(-180.0/Temp) + 2529299.1192*C_NO*C_TERPO2*exp(-180.0/Temp) + 1565756.5976*C_NO*C_TOLO2*exp(-365.0/Temp) + 1625978.0052*C_NO*C_XO2*exp(-360.0/Temp) + 1565756.5976*C_NO*C_XYLENO2*exp(-365.0/Temp) + 1565756.5976*C_NO*C_XYLOLO2*exp(-365.0/Temp) + 13248709.672*C_NO3*C_OH + 1445313.7824*C_NO3*C_XO2 + 1023763.9292*C_O3*C_OH*exp(940.0/Temp) + 283040.61572*C_OH*C_PHENOL*exp(-1220.0/Temp) + 20475278.584*C_OH*C_TERPROD2 + 1023763.9292*C_OH*C_TOLUENE*exp(-352.0/Temp) + 10237639.292*C_OH*C_XYLENES + 50585982.384*C_OH*C_XYLOL + 1.0*C_PHENOOH*J_73 + 1.0*C_POOH*J_25 + 1.0*C_TEPOMUC*J_10 + 1.0*C_TERP2OOH*J_5 + 1.0*C_TERPNIT*J_0 + 1.0*C_TERPOOH*J_92 + 1.0*C_TERPROD1*J_101 + 1.0*C_TERPROD2*J_65 + 1.0*C_TOLOOH*J_109 + 1.0*C_XYLENOOH*J_3 + 1.0*C_XYLOLOOH*J_70) + (EXPLICIT: 0)
d[HOCH2OO]/dt = (IMPLICIT: 5841.4765372*C_CH2O*C_HO2*exp(-625.0/Temp) - 451660.557*C_HO2*C_HOCH2OO*exp(-700.0/Temp) - 1565756.5976*C_HOCH2OO*C_NO*exp(-265.0/Temp) - 2400000000000.0*C_HOCH2OO*exp(7000.0/Temp)) + (EXPLICIT: 0)
d[H2]/dt = (IMPLICIT: 0) + (EXPLICIT: 0)
d[HYDRALD]/dt = (IMPLICIT: 8430997.064*C_CH3CO3*C_ISOPBO2 + 301107.038*C_CH3O2*C_ISOPBO2*exp(-400.0/Temp) - 11201181.8136*C_HYDRALD*C_OH*exp(-175.0/Temp) + 2649741.9344*C_ISOPBO2*C_NO*exp(-180.0/Temp) + 1445313.7824*C_ISOPBO2*C_NO3) + (EXPLICIT: 0)
d[ISOP]/dt = (IMPLICIT: -1824708.65028*C_ISOP*C_NO3*exp(446.0/Temp) - 6323.247798*C_ISOP*C_O3*exp(2000.0/Temp) - 15296237.5304*C_ISOP*C_OH*exp(-410.0/Temp)) + (EXPLICIT: 0)
d[NTERPO2]/dt = (IMPLICIT: 11442067.444*C_BCARY*C_NO3 - 1204428.152*C_CH3O2*C_NTERPO2*exp(-500.0/Temp) - 451660.557*C_HO2*C_NTERPO2*exp(-700.0/Temp) + 722656.8912*C_MTERP*C_NO3*exp(-490.0/Temp) - 2529299.1192*C_NO*C_NTERPO2*exp(-180.0/Temp) - 1445313.7824*C_NO3*C_NTERPO2 + 602214.076*C_NO3*C_TERPROD1 + 12044281.52*C_NTERPOOH*C_OH) + (EXPLICIT: 0)
d[TOLO2]/dt = (IMPLICIT: -451660.557*C_HO2*C_TOLO2*exp(-700.0/Temp) - 1565756.5976*C_NO*C_TOLO2*exp(-365.0/Temp) + 2288413.4888*C_OH*C_TOLOOH*exp(-200.0/Temp) + 1023763.9292*C_OH*C_TOLUENE*exp(-352.0/Temp)) + (EXPLICIT: 0)
d[TERP2O2]/dt = (IMPLICIT: -1204428.152*C_CH3O2*C_TERP2O2*exp(-500.0/Temp) - 451660.557*C_HO2*C_TERP2O2*exp(-700.0/Temp) - 2529299.1192*C_NO*C_TERP2O2*exp(-180.0/Temp) + 602214.076*C_NO3*C_TERPROD1 + 13850923.748*C_OH*C_TERP2OOH + 34326202.332*C_OH*C_TERPROD1) + (EXPLICIT: 0)
d[XYLENO2]/dt = (IMPLICIT: -451660.557*C_HO2*C_XYLENO2*exp(-700.0/Temp) - 1565756.5976*C_NO*C_XYLENO2*exp(-365.0/Temp) + 10237639.292*C_OH*C_XYLENES + 2288413.4888*C_OH*C_XYLENOOH*exp(-200.0/Temp)) + (EXPLICIT: 0)
d[TERPO2]/dt = (IMPLICIT: 120442815.2*C_BCARY*C_OH - 1204428.152*C_CH3O2*C_TERPO2*exp(-500.0/Temp) - 451660.557*C_HO2*C_TERPO2*exp(-700.0/Temp) + 7226568.912*C_MTERP*C_OH*exp(-440.0/Temp) - 2529299.1192*C_NO*C_TERPO2*exp(-180.0/Temp) + 19873064.508*C_OH*C_TERPOOH) + (EXPLICIT: 0)
d[XYLOLO2]/dt = (IMPLICIT: -451660.557*C_HO2*C_XYLOLO2*exp(-700.0/Temp) - 1565756.5976*C_NO*C_XYLOLO2*exp(-365.0/Temp) + 50585982.384*C_OH*C_XYLOL + 2288413.4888*C_OH*C_XYLOLOOH*exp(-200.0/Temp)) + (EXPLICIT: 0)
d[PBZNIT]/dt = (IMPLICIT: -1.30217879922136e-34662*0.6**(1.0/(log(6.28115756688172*M_density*exp(-4.1/Temp))**2/log(10)**2 + 1.0))*C_PBZNIT*M_density*Temp**14000.0*exp(-5.6/Temp)/(6.28115756688172*M_density*exp(-4.1/Temp) + 1.0) + 35178193.9532558*0.6**(1.0/(log(6.28115756688172*M_density*exp(-4.1/Temp))**2/log(10)**2 + 1.0))*C_ACBZO2*C_NO2*M_density*exp(-5.6/Temp)/(6.28115756688172*M_density*exp(-4.1/Temp) + 1.0)) + (EXPLICIT: 0)
d[XYLENES]/dt = (IMPLICIT: -10237639.292*C_OH*C_XYLENES) + (EXPLICIT: 0)
d[PO2]/dt = (IMPLICIT: 2901294346.66027*0.5**(1.0/(log(160.590420266667*M_density*exp(-3.5/Temp))**2/log(10)**2 + 1.0))*C_C3H6*C_OH*M_density*exp(-3.5/Temp)/(160.590420266667*M_density*exp(-3.5/Temp) + 1.0) - 451660.557*C_HO2*C_PO2*exp(-700.0/Temp) - 2529299.1192*C_NO*C_PO2*exp(-180.0/Temp) + 2288413.4888*C_OH*C_POOH*exp(-200.0/Temp)) + (EXPLICIT: 0)
d[TOLUENE]/dt = (IMPLICIT: -1023763.9292*C_OH*C_TOLUENE*exp(-352.0/Temp)) + (EXPLICIT: 0)
d[XO2]/dt = (IMPLICIT: -782878.2988*C_CH3CO3*C_XO2*exp(-640.0/Temp) - 301107.038*C_CH3O2*C_XO2*exp(-400.0/Temp) - 481771.2608*C_HO2*C_XO2*exp(-700.0/Temp) + 11201181.8136*C_HPALD*C_OH*exp(-175.0/Temp) + 11201181.8136*C_HYDRALD*C_OH*exp(-175.0/Temp) + 7828782.988*C_IEPOX*C_OH + 9153653.9552*C_ISOPOOH*C_OH*exp(-200.0/Temp) - 1625978.0052*C_NO*C_XO2*exp(-360.0/Temp) - 1445313.7824*C_NO3*C_XO2 + 915365.39552*C_OH*C_XOOH*exp(-200.0/Temp)) + (EXPLICIT: 0)
d[XOOH]/dt = (IMPLICIT: 481771.2608*C_HO2*C_XO2*exp(-700.0/Temp) - 915365.39552*C_OH*C_XOOH*exp(-200.0/Temp) - 1.0*C_XOOH*J_85) + (EXPLICIT: 0)
d[TERPROD2]/dt = (IMPLICIT: 7226.568912*C_BCARY*C_O3 + 1204428.152*C_CH3O2*C_TERP2O2*exp(-500.0/Temp) + 379.39486788*C_MTERP*C_O3*exp(580.0/Temp) + 2529299.1192*C_NO*C_TERP2O2*exp(-180.0/Temp) - 20475278.584*C_OH*C_TERPROD2 + 1.0*C_TERP2OOH*J_5 + 1.0*C_TERPROD1*J_101 - 1.0*C_TERPROD2*J_65) + (EXPLICIT: 0)
d[MEKOOH]/dt = (IMPLICIT: 451660.557*C_HO2*C_MEKO2*exp(-700.0/Temp) - 2288413.4888*C_MEKOOH*C_OH*exp(-200.0/Temp) - 1.0*C_MEKOOH*J_72) + (EXPLICIT: 0)
d[MACR]/dt = (IMPLICIT: 8430997.064*C_CH3CO3*C_ISOPAO2 + 301107.038*C_CH3O2*C_ISOPAO2*exp(-400.0/Temp) + 6323.247798*C_ISOP*C_O3*exp(2000.0/Temp) + 2649741.9344*C_ISOPAO2*C_NO*exp(-180.0/Temp) + 1445313.7824*C_ISOPAO2*C_NO3 + 1.0*C_ISOPOOH*J_41 - 903.321114*C_MACR*C_O3*exp(2100.0/Temp) - 5781255.1296*C_MACR*C_OH*exp(-360.0/Temp) - 1.0*C_MACR*J_21 - 1.0*C_MACR*J_32) + (EXPLICIT: 0)
d[HONITR]/dt = (IMPLICIT: 30712.917876*C_ENEO2*C_NO*exp(-693.0/Temp) - 1204428.152*C_HONITR*C_OH - 1.0*C_HONITR*J_84 + 24088563.04*C_ISOPNITA*C_OH + 24088563.04*C_ISOPNITB*C_OH + 78287.82988*C_MACRO2*C_NO*exp(-360.0/Temp)) + (EXPLICIT: 0)
d[ISOPNITA]/dt = (IMPLICIT: 2649741.9344*C_ISOPAO2*C_NO*exp(-180.0/Temp) - 24088563.04*C_ISOPNITA*C_OH) + (EXPLICIT: 0)
d[ISOPNOOH]/dt = (IMPLICIT: 481771.2608*C_HO2*C_ISOPNO3*exp(-700.0/Temp) - 24088563.04*C_ISOPNOOH*C_OH - 1.0*C_ISOPNOOH*J_36) + (EXPLICIT: 0)
d[IEPOX]/dt = (IMPLICIT: -7828782.988*C_IEPOX*C_OH + 9153653.9552*C_ISOPOOH*C_OH*exp(-200.0/Temp)) + (EXPLICIT: 0)
d[ONITR]/dt = (IMPLICIT: 1204428.152*C_HONITR*C_OH + 2529299.1192*C_NO*C_TERP2O2*exp(-180.0/Temp) - 1.0*C_ONITR*J_91) + (EXPLICIT: 0)
d[H2SO4]/dt = (IMPLICIT: 3.08262524332654e-5*C_H2O**2*C_SO3*exp(-6540.0/Temp) - 1.0*C_H2SO4*J_20) + (EXPLICIT: 0)
d[N2O]/dt = (IMPLICIT: 1746420.8204*C_N*C_NO2*exp(-220.0/Temp) - 71663475.044*C_N2O*C_O1D*exp(-20.0/Temp) - 1.0*C_N2O*J_80) + (EXPLICIT: 0)
d[NO3]/dt = (IMPLICIT: 2901294346.66027*0.5**(1.0/(log(160.590420266667*M_density*exp(-3.5/Temp))**2/log(10)**2 + 1.0))*C_MPAN*C_OH*M_density*exp(-3.5/Temp)/(160.590420266667*M_density*exp(-3.5/Temp) + 1.0) - 870388.303998081*0.6**(1.0/(log(0.903321114*M_density*exp(-3.1/Temp))**2/log(10)**2 + 1.0))*C_NO2*C_NO3*M_density*exp(-3.0/Temp)/(0.903321114*M_density*exp(-3.1/Temp) + 1.0) + 2.52425373052892e-26838*0.6**(1.0/(log(0.903321114*M_density*exp(-3.1/Temp))**2/log(10)**2 + 1.0))*C_N2O5*M_density*Temp**10840.0*exp(-3.0/Temp)/(0.903321114*M_density*exp(-3.1/Temp) + 1.0) + 90665.4483331334*0.6**(1.0/(log(0.00684334177272727*M_density*exp(-1.1/Temp))**2/log(10)**2 + 1.0))*C_NO2*C_O*M_density*exp(-1.8/Temp)/(0.00684334177272727*M_density*exp(-1.1/Temp) + 1.0) + 2.13447077159129e+3309*1.0**(1.0/(log(8.48274510194932e-2140*M_density*Temp**864.0)**2/log(10)**2 + 1.0))*C_HNO3*C_OH*M_density/(Temp**1335.0*(8.48274510194932e-2140*M_density*Temp**864.0 + 1.0)) - 11442067.444*C_BCARY*C_NO3 - 210774.9266*C_BIGENE*C_NO3 + 11442067.444*C_BRONO2*C_O*exp(-215.0/Temp) + 1.0*C_BRONO2*J_6 - 277018.47496*C_C3H6*C_NO3*exp(1156.0/Temp) - 361328.4456*C_CH2O*C_NO3*exp(2058.0/Temp) - 843099.7064*C_CH3CHO*C_NO3*exp(1900.0/Temp) - 843099.7064*C_CH3COCHO*C_NO3*exp(1860.0/Temp) + 3914391.494*C_CL*C_CLONO2*exp(-135.0/Temp) + 2167970.6736*C_CLONO2*C_O*exp(840.0/Temp) + 722656.8912*C_CLONO2*C_OH*exp(330.0/Temp) + 1.0*C_CLONO2*J_103 - 114420.67444*C_DMS*C_NO3*exp(-520.0/Temp) + 3613284.456*C_F*C_HNO3*exp(-400.0/Temp) + 14453.137824*C_HNO3*C_OH*exp(-460.0/Temp) - 2107749.266*C_HO2*C_NO3 + 1.0*C_HO2NO2*J_50 - 1824708.65028*C_ISOP*C_NO3*exp(446.0/Temp) - 1445313.7824*C_ISOPAO2*C_NO3 - 1445313.7824*C_ISOPBO2*C_NO3 - 1445313.7824*C_ISOPNO3*C_NO3 - 1445313.7824*C_MACRO2*C_NO3 - 3011070.38*C_MCO3*C_NO3 - 722656.8912*C_MTERP*C_NO3*exp(-490.0/Temp) + 1.0*C_N2O5*J_34 + 1.0*C_N2O5*J_55 - 10237639.292*C_NO*C_NO3*exp(-125.0/Temp) + 72265.68912*C_NO2*C_O3*exp(2450.0/Temp) - 1445313.7824*C_NO3*C_NTERPO2 - 7828782.988*C_NO3*C_O - 13248709.672*C_NO3*C_OH - 602214.076*C_NO3*C_TERPROD1 - 1445313.7824*C_NO3*C_XO2 - 1.0*C_NO3*J_48 - 1.0*C_NO3*J_88 + 24088.56304*C_OH*C_PAN + 1.0*C_PAN*J_45) + (EXPLICIT: 0)
d[OH]/dt = (IMPLICIT: -31188914.2265979*0.48**(1.0/(log(5.75449005955556*M_density*exp(-2.25/Temp))**2/log(10)**2 + 1.0))*C_C2H4*C_OH*M_density*exp(-3.1/Temp)/(5.75449005955556*M_density*exp(-2.25/Temp) + 1.0) - 2901294346.66027*0.5**(1.0/(log(160.590420266667*M_density*exp(-3.5/Temp))**2/log(10)**2 + 1.0))*C_C3H6*C_OH*M_density*exp(-3.5/Temp)/(160.590420266667*M_density*exp(-3.5/Temp) + 1.0) - 2901294346.66027*0.5**(1.0/(log(160.590420266667*M_density*exp(-3.5/Temp))**2/log(10)**2 + 1.0))*C_MPAN*C_OH*M_density*exp(-3.5/Temp)/(160.590420266667*M_density*exp(-3.5/Temp) + 1.0) - 105171.920066435*0.6**(1.0/(log(0.102730636494118*M_density*exp(-4.3/Temp))**2/log(10)**2 + 1.0))*C_OH*C_SO2*M_density*exp(-4.1/Temp)/(0.102730636494118*M_density*exp(-4.3/Temp) + 1.0) - 652791.227998561*0.6**(1.0/(log(0.0387137620285714*M_density*exp(-3.0/Temp))**2/log(10)**2 + 1.0))*C_NO2*C_OH*M_density*exp(-3.0/Temp)/(0.0387137620285714*M_density*exp(-3.0/Temp) + 1.0) - 500473.274798897*0.6**(1.0/(log(0.0159818350938462*M_density*exp(-1.0/Temp))**2/log(10)**2 + 1.0))*C_OH**2*M_density*exp(-1.0/Temp)/(0.0159818350938462*M_density*exp(-1.0/Temp) + 1.0) - 2212.23693932846*0.8**(1.0/(log(0.374847537102041*M_density*exp(-6.1/Temp))**2/log(10)**2 + 1.0))*C_HCN*C_OH*M_density*exp(-1.5/Temp)/(0.374847537102041*M_density*exp(-6.1/Temp) + 1.0) - 2.13447077159129e+3309*1.0**(1.0/(log(8.48274510194932e-2140*M_density*Temp**864.0)**2/log(10)**2 + 1.0))*C_HNO3*C_OH*M_density/(Temp**1335.0*(8.48274510194932e-2140*M_density*Temp**864.0 + 1.0)) + 258952.05268*C_ACBZO2*C_HO2*exp(-1040.0/Temp) - 963542.5216*C_ALKNIT*C_OH - 2288413.4888*C_ALKOOH*C_OH*exp(-200.0/Temp) + 1.0*C_ALKOOH*J_37 + 7226.568912*C_BCARY*C_O3 - 120442815.2*C_BCARY*C_OH - 1385092.3748*C_BENZENE*C_OH*exp(193.0/Temp) - 2288413.4888*C_BENZOOH*C_OH*exp(-200.0/Temp) + 1.0*C_BENZOOH*J_33 - 2107749.266*C_BIGALK*C_OH - 32519560.104*C_BIGENE*C_OH - 10237639.292*C_BRO*C_OH*exp(-250.0/Temp) - 3553063.0484*C_BZALD*C_OH*exp(-225.0/Temp) - 2288413.4888*C_BZOOH*C_OH*exp(-200.0/Temp) + 1.0*C_BZOOH*J_57 + 7226.568912*C_C2H4*C_O3*exp(2630.0/Temp) - 4155277.1244*C_C2H5OH*C_OH*exp(230.0/Temp) + 1.0*C_C2H5OOH*J_97 - 4612959.82216*C_C2H6*C_OH*exp(1020.0/Temp) + 3914.391494*C_C3H6*C_O3*exp(1900.0/Temp) - 2288413.4888*C_C3H7OOH*C_OH*exp(-200.0/Temp) + 1.0*C_C3H7OOH*J_16 - 5534347.35844*C_C3H8*C_OH*exp(630.0/Temp) - 2288413.4888*C_C6H5OOH*C_OH*exp(-200.0/Temp) + 1.0*C_C6H5OOH*J_42 - 1204428.152*C_CH2BR2*C_OH*exp(840.0/Temp) + 20475278.584*C_CH2O*C_O*exp(1600.0/Temp) - 3312177.418*C_CH2O*C_OH*exp(-125.0/Temp) - 855143.98792*C_CH3BR*C_OH*exp(1150.0/Temp) - 987631.08464*C_CH3CCL3*C_OH*exp(1520.0/Temp) - 2788251.17188*C_CH3CHO*C_OH*exp(-350.0/Temp) - 1180339.58896*C_CH3CL*C_OH*exp(1200.0/Temp) - 469726.97928*C_CH3CN*C_OH*exp(1050.0/Temp) + 258952.05268*C_CH3CO3*C_HO2*exp(-1040.0/Temp) - 23004577.7032*C_CH3COCH3*C_OH*exp(2000.0/Temp) - 80094.472108*C_CH3COCH3*C_OH - 505859.82384*C_CH3COCHO*C_OH*exp(-830.0/Temp) - 18969.743394*C_CH3COOH*C_OH*exp(-920.0/Temp) - 602214.076*C_CH3COOOH*C_OH + 1.0*C_CH3COOOH*J_90 - 1746420.8204*C_CH3OH*C_OH*exp(345.0/Temp) + 1.0*C_CH3OOH*J_116 + 78890043.956*C_CH4*C_O1D - 1475424.4862*C_CH4*C_OH*exp(1775.0/Temp) + 1.0*C_CH4*J_4 - 541992.6684*C_CHBR3*C_OH*exp(360.0/Temp) + 21679706.736*C_CL*C_HO2*exp(375.0/Temp) - 4456384.1624*C_CLO*C_OH*exp(-270.0/Temp) - 361328.4456*C_CLO*C_OH*exp(-230.0/Temp) - 722656.8912*C_CLONO2*C_OH*exp(330.0/Temp) - 1.0*C_CO*C_OH*Rate_545 - 28304061.572*C_CRESOL*C_OH + 258952.05268*C_DICARBO2*C_HO2*exp(-1040.0/Temp) - 1.0*C_DMS*C_OH*Rate_499 - 6624354.836*C_DMS*C_OH*exp(280.0/Temp) + 1.0*C_EOOH*J_39 + 8430997.064*C_F*C_H2O - 6022140.76*C_GLYALD*C_OH - 6925461.874*C_GLYOXAL*C_OH + 43359413.472*C_H*C_HO2 + 84309970.64*C_H*C_O3*exp(470.0/Temp) + 9635425.216*C_H2*C_O*exp(4570.0/Temp) + 72265689.12*C_H2*C_O1D - 1686199.4128*C_H2*C_OH*exp(1800.0/Temp) + 98160894.388*C_H2O*C_O1D*exp(-60.0/Temp) + 1.0*C_H2O*J_89 + 843099.7064*C_H2O2*C_O*exp(2000.0/Temp) - 1083985.3368*C_H2O2*C_OH + 1.0*C_H2O2*J_29 + 3492841.6408*C_HBR*C_O*exp(1500.0/Temp) + 54199266.84*C_HBR*C_O1D - 3312177.418*C_HBR*C_OH*exp(-200.0/Temp) - 752767.595*C_HCFC141B*C_OH*exp(1600.0/Temp) - 782878.2988*C_HCFC142B*C_OH*exp(1770.0/Temp) - 554036.94992*C_HCFC22*C_OH*exp(1560.0/Temp) + 6022140.76*C_HCL*C_O*exp(3300.0/Temp) + 59619193.524*C_HCL*C_O1D - 1083985.3368*C_HCL*C_OH*exp(250.0/Temp) + 65039120.208*C_HCN*C_O1D*exp(-105.0/Temp) - 240885.6304*C_HCOOH*C_OH - 14453.137824*C_HNO3*C_OH*exp(-460.0/Temp) + 1.0*C_HNO3*J_96 + 258952.05268*C_HO2*C_MCO3*exp(-1040.0/Temp) + 258952.05268*C_HO2*C_MDIALO2*exp(-1040.0/Temp) + 451660.557*C_HO2*C_MEKO2*exp(-700.0/Temp) + 2071616.42144*C_HO2*C_NO*exp(-260.0/Temp) + 2107749.266*C_HO2*C_NO3 + 18066422.28*C_HO2*C_O*exp(-200.0/Temp) + 6022.14076*C_HO2*C_O3*exp(490.0/Temp) - 28906275.648*C_HO2*C_OH*exp(-250.0/Temp) + 517904.10536*C_HO2*C_RO2*exp(-700.0/Temp) - 270996.3342*C_HO2NO2*C_OH*exp(-610.0/Temp) + 1.0*C_HO2NO2*J_50 + 72265689.12*C_HOBR*C_O*exp(430.0/Temp) + 1.0*C_HOBR*J_87 + 102376.39292*C_HOCL*C_O - 1806642.228*C_HOCL*C_OH*exp(500.0/Temp) + 1.0*C_HOCL*J_115 - 1204428.152*C_HONITR*C_OH - 11201181.8136*C_HPALD*C_OH*exp(-175.0/Temp) + 1.0*C_HPALD*J_56 - 1806642.228*C_HYAC*C_OH - 11201181.8136*C_HYDRALD*C_OH*exp(-175.0/Temp) - 7828782.988*C_IEPOX*C_OH + 6323.247798*C_ISOP*C_O3*exp(2000.0/Temp) - 15296237.5304*C_ISOP*C_OH*exp(-410.0/Temp) - 24088563.04*C_ISOPNITA*C_OH - 24088563.04*C_ISOPNITB*C_OH - 24088563.04*C_ISOPNOOH*C_OH + 1.0*C_ISOPOOH*J_41 + 903.321114*C_MACR*C_O3*exp(2100.0/Temp) - 5781255.1296*C_MACR*C_OH*exp(-360.0/Temp) - 1385092.3748*C_MEK*C_OH*exp(170.0/Temp) - 2288413.4888*C_MEKOOH*C_OH*exp(-200.0/Temp) + 1.0*C_MEKOOH*J_72 + 379.39486788*C_MTERP*C_O3*exp(580.0/Temp) - 7226568.912*C_MTERP*C_OH*exp(-440.0/Temp) + 511.8819646*C_MVK*C_O3*exp(1520.0/Temp) - 2487144.13388*C_MVK*C_OH*exp(-452.0/Temp) - 30110703.8*C_N*C_OH - 42154985.32*C_NC4CH2OH*C_OH - 60221407.6*C_NC4CHO*C_OH - 1023763.9292*C_NH3*C_OH*exp(710.0/Temp) - 13248709.672*C_NO3*C_OH - 403483.43092*C_NOA*C_OH - 12044281.52*C_NTERPOOH*C_OH + 1.0*C_NTERPOOH*J_22 - 10839853.368*C_O*C_OH*exp(-180.0/Temp) - 1023763.9292*C_O3*C_OH*exp(940.0/Temp) - 43359.413472*C_OCS*C_OH*exp(1070.0/Temp) - 2167970.6736*C_OH**2 - 24088.56304*C_OH*C_PAN - 283040.61572*C_OH*C_PHENOL*exp(-1220.0/Temp) - 2288413.4888*C_OH*C_PHENOOH*exp(-200.0/Temp) - 2288413.4888*C_OH*C_ROOH*exp(-200.0/Temp) - 39746129.016*C_OH*C_S - 15657565.976*C_OH*C_SO*exp(-330.0/Temp) - 13850923.748*C_OH*C_TERP2OOH - 12044281.52*C_OH*C_TERPNIT - 19873064.508*C_OH*C_TERPOOH - 34326202.332*C_OH*C_TERPROD1 - 20475278.584*C_OH*C_TERPROD2 - 2288413.4888*C_OH*C_TOLOOH*exp(-200.0/Temp) - 1023763.9292*C_OH*C_TOLUENE*exp(-352.0/Temp) - 10237639.292*C_OH*C_XYLENES - 2288413.4888*C_OH*C_XYLENOOH*exp(-200.0/Temp) - 50585982.384*C_OH*C_XYLOL - 2288413.4888*C_OH*C_XYLOLOOH*exp(-200.0/Temp) + 1.0*C_PHENOOH*J_73 + 1.0*C_POOH*J_25 + 1.0*C_ROOH*J_23 + 1.0*C_TERP2OOH*J_5 + 1.0*C_TERPOOH*J_92 + 1.0*C_TOLOOH*J_109 + 1.0*C_XOOH*J_85 + 1.0*C_XYLENOOH*J_3 + 1.0*C_XYLOLOOH*J_70) + (EXPLICIT: 0)
d[PHENOOH]/dt = (IMPLICIT: 451660.557*C_HO2*C_PHENO2*exp(-700.0/Temp) - 2288413.4888*C_OH*C_PHENOOH*exp(-200.0/Temp) - 1.0*C_PHENOOH*J_73) + (EXPLICIT: 0)
d[PHENOL]/dt = (IMPLICIT: 1385092.3748*C_BENZENE*C_OH*exp(193.0/Temp) - 283040.61572*C_OH*C_PHENOL*exp(-1220.0/Temp)) + (EXPLICIT: 0)
d[XYLOL]/dt = (IMPLICIT: 10237639.292*C_OH*C_XYLENES - 50585982.384*C_OH*C_XYLOL) + (EXPLICIT: 0)
d[ROOH]/dt = (IMPLICIT: 517904.10536*C_HO2*C_RO2*exp(-700.0/Temp) - 2288413.4888*C_OH*C_ROOH*exp(-200.0/Temp) - 1.0*C_ROOH*J_23) + (EXPLICIT: 0)
d[O3]/dt = (IMPLICIT: -7226.568912*C_BCARY*C_O3 - 9635425.216*C_BR*C_O3*exp(780.0/Temp) - 7226.568912*C_C2H4*C_O3*exp(2630.0/Temp) - 3914.391494*C_C3H6*C_O3*exp(1900.0/Temp) + 258952.05268*C_CH3CO3*C_HO2*exp(-1040.0/Temp) - 13850923.748*C_CL*C_O3*exp(200.0/Temp) - 84309970.64*C_H*C_O3*exp(470.0/Temp) + 258952.05268*C_HO2*C_MCO3*exp(-1040.0/Temp) - 6022.14076*C_HO2*C_O3*exp(490.0/Temp) - 6323.247798*C_ISOP*C_O3*exp(2000.0/Temp) + 191753838.55752*C_M*C_O*C_O2/Temp**2.4 - 903.321114*C_MACR*C_O3*exp(2100.0/Temp) - 379.39486788*C_MTERP*C_O3*exp(580.0/Temp) - 511.8819646*C_MVK*C_O3*exp(1520.0/Temp) - 1806642.228*C_NO*C_O3*exp(1500.0/Temp) - 72265.68912*C_NO2*C_O3*exp(2450.0/Temp) - 4817712.608*C_O*C_O3*exp(2060.0/Temp) - 144531378.24*C_O1D*C_O3 - 1023763.9292*C_O3*C_OH*exp(940.0/Temp) - 168619.94128*C_O3*C_PHENO - 7226568.912*C_O3*C_S - 2047527.8584*C_O3*C_SO*exp(1100.0/Temp) - 1.0*C_O3*J_46 - 1.0*C_O3*J_54) + (EXPLICIT: 0)
d[TERPOOH]/dt = (IMPLICIT: 451660.557*C_HO2*C_TERPO2*exp(-700.0/Temp) - 19873064.508*C_OH*C_TERPOOH - 1.0*C_TERPOOH*J_92) + (EXPLICIT: 0)
d[TOLOOH]/dt = (IMPLICIT: 451660.557*C_HO2*C_TOLO2*exp(-700.0/Temp) - 2288413.4888*C_OH*C_TOLOOH*exp(-200.0/Temp) - 1.0*C_TOLOOH*J_109) + (EXPLICIT: 0)
d[XYLENOOH]/dt = (IMPLICIT: 451660.557*C_HO2*C_XYLENO2*exp(-700.0/Temp) - 2288413.4888*C_OH*C_XYLENOOH*exp(-200.0/Temp) - 1.0*C_XYLENOOH*J_3) + (EXPLICIT: 0)
d[XYLOLOOH]/dt = (IMPLICIT: 451660.557*C_HO2*C_XYLOLO2*exp(-700.0/Temp) - 2288413.4888*C_OH*C_XYLOLOOH*exp(-200.0/Temp) - 1.0*C_XYLOLOOH*J_70) + (EXPLICIT: 0)
d[CO]/dt = (IMPLICIT: 1994639.86332894*0.6**(1.0/(log(3.99057520240964*M_density*exp(-2.0/Temp))**2/log(10)**2 + 1.0))*C_C2H2*C_OH*M_density/(3.99057520240964*M_density*exp(-2.0/Temp) + 1.0) + 7226.568912*C_BCARY*C_O3 + 1.0*C_BEPOMUC*J_79 + 1.0*C_BIGALD*J_60 + 1.0*C_BIGALD3*J_76 + 1.0*C_BIGALD4*J_7 + 10237639.292*C_BR*C_CH2O*exp(800.0/Temp) + 7226.568912*C_C2H4*C_O3*exp(2630.0/Temp) + 3914.391494*C_C3H6*C_O3*exp(1900.0/Temp) + 48779340.156*C_CH2O*C_CL*exp(30.0/Temp) + 361328.4456*C_CH2O*C_NO3*exp(2058.0/Temp) + 20475278.584*C_CH2O*C_O*exp(1600.0/Temp) + 3312177.418*C_CH2O*C_OH*exp(-125.0/Temp) + 1.0*C_CH2O*J_12 + 1.0*C_CH2O*J_81 + 1.0*C_CH3CHO*J_94 + 12224945.7428*C_CH3CL*C_CL*exp(1100.0/Temp) + 8430997.064*C_CH3CO3*C_MACRO2 + 782878.2988*C_CH3CO3*C_XO2*exp(-640.0/Temp) + 843099.7064*C_CH3COCHO*C_NO3*exp(1860.0/Temp) + 505859.82384*C_CH3COCHO*C_OH*exp(-830.0/Temp) + 1.0*C_CH3COCHO*J_2 + 301107.038*C_CH3O2*C_MACRO2*exp(-400.0/Temp) + 1204428.152*C_CH3O2*C_TERP2O2*exp(-500.0/Temp) + 301107.038*C_CH3O2*C_XO2*exp(-400.0/Temp) + 1.0*C_CH4*J_4 - 1.0*C_CO*C_OH*Rate_545 + 1.0*C_CO2*J_98 + 258952.05268*C_DICARBO2*C_HO2*exp(-1040.0/Temp) + 4516605.57*C_DICARBO2*C_NO*exp(-290.0/Temp) + 1.0*C_GLYALD*J_112 + 6925461.874*C_GLYOXAL*C_OH + 1.0*C_GLYOXAL*J_53 + 258952.05268*C_HO2*C_MALO2*exp(-1040.0/Temp) + 258952.05268*C_HO2*C_MDIALO2*exp(-1040.0/Temp) + 1.0*C_HONITR*J_84 + 6323.247798*C_ISOP*C_O3*exp(2000.0/Temp) + 903.321114*C_MACR*C_O3*exp(2100.0/Temp) + 1.0*C_MACR*J_21 + 1625978.0052*C_MACRO2*C_NO*exp(-360.0/Temp) + 1445313.7824*C_MACRO2*C_NO3 + 4516605.57*C_MALO2*C_NO*exp(-290.0/Temp) + 4516605.57*C_MDIALO2*C_NO*exp(-290.0/Temp) + 379.39486788*C_MTERP*C_O3*exp(580.0/Temp) + 511.8819646*C_MVK*C_O3*exp(1520.0/Temp) + 1.0*C_MVK*J_62 + 2529299.1192*C_NO*C_TERP2O2*exp(-180.0/Temp) + 1625978.0052*C_NO*C_XO2*exp(-360.0/Temp) + 1445313.7824*C_NO3*C_XO2 + 12646495.596*C_O*C_OCS*exp(2200.0/Temp) + 43359.413472*C_OCS*C_OH*exp(1070.0/Temp) + 20475278.584*C_OH*C_TERPROD2 + 1.0*C_TEPOMUC*J_10 + 1.0*C_TERP2OOH*J_5 + 1.0*C_TERPROD1*J_101 + 1.0*C_TERPROD2*J_65) + (EXPLICIT: 1.0*C_OCS*J_113)
d[CH3COOH]/dt = (IMPLICIT: 3914.391494*C_C3H6*C_O3*exp(1900.0/Temp) + 1204428.152*C_CH3CO3*C_CH3O2*exp(-500.0/Temp) + 258952.05268*C_CH3CO3*C_HO2*exp(-1040.0/Temp) - 18969.743394*C_CH3COOH*C_OH*exp(-920.0/Temp) + 258952.05268*C_HO2*C_MCO3*exp(-1040.0/Temp)) + (EXPLICIT: 0)
d[CH3CHO]/dt = (IMPLICIT: 963542.5216*C_ALKNIT*C_OH + 1.0*C_ALKNIT*J_59 + 4034834.3092*C_ALKO2*C_NO + 1.0*C_ALKOOH*J_37 + 210774.9266*C_BIGENE*C_NO3 + 40950.557168*C_C2H5O2**2 + 120442.8152*C_C2H5O2*C_CH3O2 + 1565756.5976*C_C2H5O2*C_NO*exp(-365.0/Temp) + 4155277.1244*C_C2H5OH*C_OH*exp(230.0/Temp) + 2288413.4888*C_C2H5OOH*C_OH*exp(-200.0/Temp) + 1.0*C_C2H5OOH*J_97 + 3914.391494*C_C3H6*C_O3*exp(1900.0/Temp) + 2529299.1192*C_C3H7O2*C_NO*exp(-180.0/Temp) - 843099.7064*C_CH3CHO*C_NO3*exp(1900.0/Temp) - 2788251.17188*C_CH3CHO*C_OH*exp(-350.0/Temp) - 1.0*C_CH3CHO*J_94 + 2890627.5648*C_ENEO2*C_NO*exp(-120.0/Temp) + 451660.557*C_HO2*C_MEKO2*exp(-700.0/Temp) + 1.0*C_HONITR*J_84 + 2529299.1192*C_MEKO2*C_NO*exp(-180.0/Temp) + 1.0*C_MEKOOH*J_72 + 511.8819646*C_MVK*C_O3*exp(1520.0/Temp) + 2529299.1192*C_NO*C_PO2*exp(-180.0/Temp) + 1.0*C_POOH*J_25) + (EXPLICIT: 0)
d[BIGALD1]/dt = (IMPLICIT: 1565756.5976*C_BENZO2*C_NO*exp(-365.0/Temp) + 1.0*C_BENZOOH*J_33 + 1.0*C_BEPOMUC*J_79 - 1.0*C_BIGALD1*J_95 + 1565756.5976*C_NO*C_TOLO2*exp(-365.0/Temp) + 1565756.5976*C_NO*C_XYLENO2*exp(-365.0/Temp) + 1.0*C_TOLOOH*J_109 + 1.0*C_XYLENOOH*J_3) + (EXPLICIT: 0)
d[ALKOOH]/dt = (IMPLICIT: 451660.557*C_ALKO2*C_HO2*exp(-700.0/Temp) - 2288413.4888*C_ALKOOH*C_OH*exp(-200.0/Temp) - 1.0*C_ALKOOH*J_37) + (EXPLICIT: 0)
d[DICARBO2]/dt = (IMPLICIT: 1.0*C_BIGALD2*J_49 - 258952.05268*C_DICARBO2*C_HO2*exp(-1040.0/Temp) - 4516605.57*C_DICARBO2*C_NO*exp(-290.0/Temp)) + (EXPLICIT: -35178193.9532558*0.6**(1.0/(log(6.28115756688172*M_density*exp(-4.1/Temp))**2/log(10)**2 + 1.0))*C_DICARBO2*C_NO2*M_density*exp(-5.6/Temp)/(6.28115756688172*M_density*exp(-4.1/Temp) + 1.0))
d[BENZOOH]/dt = (IMPLICIT: 451660.557*C_BENZO2*C_HO2*exp(-700.0/Temp) - 2288413.4888*C_BENZOOH*C_OH*exp(-200.0/Temp) - 1.0*C_BENZOOH*J_33) + (EXPLICIT: 0)
d[ALKO2]/dt = (IMPLICIT: -451660.557*C_ALKO2*C_HO2*exp(-700.0/Temp) - 4034834.3092*C_ALKO2*C_NO - 32519.560104*C_ALKO2*C_NO*exp(-870.0/Temp) + 2288413.4888*C_ALKOOH*C_OH*exp(-200.0/Temp) + 2107749.266*C_BIGALK*C_OH) + (EXPLICIT: 0)
d[HO2NO2]/dt = (IMPLICIT: -1.30199334468671e-26987*0.6**(1.0/(log(0.02860516861*M_density*exp(-3.1/Temp))**2/log(10)**2 + 1.0))*C_HO2NO2*M_density*Temp**10900.0*exp(-3.4/Temp)/(0.02860516861*M_density*exp(-3.1/Temp) + 1.0) + 68905.7407331814*0.6**(1.0/(log(0.02860516861*M_density*exp(-3.1/Temp))**2/log(10)**2 + 1.0))*C_HO2*C_NO2*M_density*exp(-3.4/Temp)/(0.02860516861*M_density*exp(-3.1/Temp) + 1.0) - 270996.3342*C_HO2NO2*C_OH*exp(-610.0/Temp) - 1.0*C_HO2NO2*J_44 - 1.0*C_HO2NO2*J_50) + (EXPLICIT: 0)
d[C3H7OOH]/dt = (IMPLICIT: 451660.557*C_C3H7O2*C_HO2*exp(-700.0/Temp) - 2288413.4888*C_C3H7OOH*C_OH*exp(-200.0/Temp) - 1.0*C_C3H7OOH*J_16) + (EXPLICIT: 0)
d[NH3]/dt = (IMPLICIT: -1023763.9292*C_NH3*C_OH*exp(710.0/Temp)) + (EXPLICIT: 0)
d[TERP2OOH]/dt = (IMPLICIT: 451660.557*C_HO2*C_TERP2O2*exp(-700.0/Temp) - 13850923.748*C_OH*C_TERP2OOH - 1.0*C_TERP2OOH*J_5) + (EXPLICIT: 0)
d[POOH]/dt = (IMPLICIT: 451660.557*C_HO2*C_PO2*exp(-700.0/Temp) - 2288413.4888*C_OH*C_POOH*exp(-200.0/Temp) - 1.0*C_POOH*J_25) + (EXPLICIT: 0)
d[NOA]/dt = (IMPLICIT: 277018.47496*C_C3H6*C_NO3*exp(1156.0/Temp) + 24088563.04*C_ISOPNITB*C_OH + 24088563.04*C_ISOPNOOH*C_OH + 42154985.32*C_NC4CH2OH*C_OH + 60221407.6*C_NC4CHO*C_OH - 403483.43092*C_NOA*C_OH - 1.0*C_NOA*J_19) + (EXPLICIT: 0)
d[NC4CHO]/dt = (IMPLICIT: 8430997.064*C_CH3CO3*C_ISOPNO3 + 301107.038*C_CH3O2*C_ISOPNO3*exp(-400.0/Temp) + 1625978.0052*C_ISOPNO3*C_NO*exp(-360.0/Temp) + 1445313.7824*C_ISOPNO3*C_NO3 - 60221407.6*C_NC4CHO*C_OH - 1.0*C_NC4CHO*J_83) + (EXPLICIT: 0)
d[TEPOMUC]/dt = (IMPLICIT: 1023763.9292*C_OH*C_TOLUENE*exp(-352.0/Temp) + 10237639.292*C_OH*C_XYLENES - 1.0*C_TEPOMUC*J_10) + (EXPLICIT: 0)
d[NH4]/dt = (IMPLICIT: 0) + (EXPLICIT: -6.34e-8*C_NH4)
d[M]/dt = (IMPLICIT: 0) + (EXPLICIT: 0)
```

## Performance & Stiffness Diagnostics
The following species are the most heavily coupled (densest Jacobian rows). These dictate the performance ceiling of the Dense LU / ROS2 implicit solver block:

| Species | Non-Zero Dependencies |
|---------|-----------------------|
| OH | 116 |
| HO2 | 114 |
| NO2 | 61 |
| CH2O | 58 |
| NO | 46 |

### Warnings
- ⚠️ Mechanism exceeds 50 species. Consider running with `--lump` to auto-reduce.
- ⚠️ Mechanism contains complex pressure-dependent or empirical falloff rates which expand the AST depth significantly.
