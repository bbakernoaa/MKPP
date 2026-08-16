# MKPP Mechanism Diagnostic Report: saprc99

## Overview
- **Total Species**: 82
- **Total Reactions**: 211

### Reaction Types Breakdown
- **PHOTOLYSIS**: 30
- **ARRHENIUS**: 167
- **TROE**: 10
- **EP2**: 1
- **EP3**: 3

### Stiffness Partitioning
- **Implicit (Stiff) Reactions**: 182
- **Explicit (Non-Stiff) Reactions**: 29
- **Graph Topology Status**: Mechanism contains cyclically dependent fast radicals. Tarjan SCC was applied.

## Generated SymPy Rate Expressions
Below are the exact algebraic AST expressions evaluated by SymPy for the Unified Jacobian.

```text
R1: PHOTOLYSIS | Reactants: ['NO2'] | Products: ['NO', 'O3P'] | A: 6.69e-1
R2: ARRHENIUS | Reactants: ['O3P', 'O2', 'AIR'] | Products: ['O3'] | A: 5.68e-34
R3: ARRHENIUS | Reactants: ['O3P', 'O3'] | Products: ['O2'] | A: 8.00e-12
R4: ARRHENIUS | Reactants: ['O3P', 'NO', 'AIR'] | Products: ['NO2'] | A: 1.00e-31
R5: ARRHENIUS | Reactants: ['O3P', 'NO2'] | Products: ['NO'] | A: 6.50e-12
R6: TROE | Reactants: ['O3P', 'NO2'] | Products: ['NO3'] | A: N/A
R7: ARRHENIUS | Reactants: ['O3', 'NO'] | Products: ['NO2'] | A: 1.80e-12
R8: ARRHENIUS | Reactants: ['O3', 'NO2'] | Products: ['NO3'] | A: 1.40e-13
R9: ARRHENIUS | Reactants: ['NO', 'NO3'] | Products: ['NO2'] | A: 1.80e-11
R10: ARRHENIUS | Reactants: ['NO', 'O2'] | Products: ['NO2'] | A: 3.30e-39
R11: TROE | Reactants: ['NO2', 'NO3'] | Products: ['N2O5'] | A: N/A
R12: TROE | Reactants: ['N2O5'] | Products: ['NO2', 'NO3'] | A: N/A
R13: ARRHENIUS | Reactants: ['N2O5', 'H2O'] | Products: ['HNO3'] | A: 2.60e-22
R14: ARRHENIUS | Reactants: ['NO2', 'NO3'] | Products: ['NO', 'NO2'] | A: 4.50e-14
R15: PHOTOLYSIS | Reactants: ['NO3'] | Products: ['NO'] | A: 1.59
R16: PHOTOLYSIS | Reactants: ['NO3'] | Products: ['NO2', 'O3P'] | A: 1.50e+1
R17: PHOTOLYSIS | Reactants: ['O3'] | Products: ['O3P'] | A: 3.76e-2
R18: PHOTOLYSIS | Reactants: ['O3'] | Products: ['O1D'] | A: 4.19e-3
R19: ARRHENIUS | Reactants: ['O1D', 'H2O'] | Products: ['OH'] | A: 2.20e-10
R20: ARRHENIUS | Reactants: ['O1D', 'AIR'] | Products: ['O3P'] | A: 2.09e-11
R21: TROE | Reactants: ['OH', 'NO'] | Products: ['HONO'] | A: N/A
R22: PHOTOLYSIS | Reactants: ['HONO'] | Products: ['OH', 'NO'] | A: 1.27e-1
R23: PHOTOLYSIS | Reactants: ['HONO'] | Products: ['HO2', 'NO2'] | A: 1.60e-2
R24: ARRHENIUS | Reactants: ['OH', 'HONO'] | Products: ['NO2'] | A: 2.70e-12
R25: TROE | Reactants: ['OH', 'NO2'] | Products: ['HNO3'] | A: N/A
R26: ARRHENIUS | Reactants: ['OH', 'NO3'] | Products: ['HO2', 'NO2'] | A: 2.00e-11
R27: EP2 | Reactants: ['OH', 'HNO3'] | Products: ['NO3'] | A: N/A
R28: PHOTOLYSIS | Reactants: ['HNO3'] | Products: ['OH', 'NO2'] | A: 5.40e-5
R29: EP3 | Reactants: ['OH', 'CO'] | Products: ['HO2'] | A: N/A
R30: ARRHENIUS | Reactants: ['OH', 'O3'] | Products: ['HO2'] | A: 1.90e-12
R31: ARRHENIUS | Reactants: ['HO2', 'NO'] | Products: ['OH', 'NO2'] | A: 3.40e-12
R32: TROE | Reactants: ['HO2', 'NO2'] | Products: ['HNO4'] | A: N/A
R33: TROE | Reactants: ['HNO4'] | Products: ['HO2', 'NO2'] | A: N/A
R34: PHOTOLYSIS | Reactants: ['HNO4'] | Products: ['HO2', 'NO2', 'OH', 'NO3'] | A: 4.69e-4
R35: ARRHENIUS | Reactants: ['HNO4', 'OH'] | Products: ['NO2'] | A: 1.50e-12
R36: ARRHENIUS | Reactants: ['HO2', 'O3'] | Products: ['OH'] | A: 1.40e-14
R37: EP3 | Reactants: ['HO2'] | Products: ['H2O2'] | A: N/A
R38: EP3 | Reactants: ['HO2', 'H2O'] | Products: ['H2O2'] | A: N/A
R39: ARRHENIUS | Reactants: ['NO3', 'HO2'] | Products: ['OH', 'NO2', 'HNO3'] | A: 4.00e-12
R40: ARRHENIUS | Reactants: ['NO3'] | Products: ['NO2'] | A: 8.50e-13
R41: PHOTOLYSIS | Reactants: ['H2O2'] | Products: ['OH'] | A: 5.64e-4
R42: ARRHENIUS | Reactants: ['H2O2', 'OH'] | Products: ['HO2'] | A: 2.90e-12
R43: ARRHENIUS | Reactants: ['OH', 'HO2'] | Products: ['H2O', 'O2'] | A: 4.80e-11
R44: TROE | Reactants: ['OH', 'SO2'] | Products: ['HO2', 'H2SO4'] | A: N/A
R45: ARRHENIUS | Reactants: ['OH', 'H2'] | Products: ['HO2'] | A: 7.70e-12
R46: ARRHENIUS | Reactants: ['C_O2', 'NO'] | Products: ['NO2', 'HCHO', 'HO2'] | A: 2.80e-12
R47: ARRHENIUS | Reactants: ['C_O2', 'HO2'] | Products: ['COOH'] | A: 3.80e-13
R48: ARRHENIUS | Reactants: ['C_O2', 'NO3'] | Products: ['HCHO', 'HO2', 'NO2'] | A: 1.30e-12
R49: ARRHENIUS | Reactants: ['C_O2'] | Products: ['MEOH', 'HCHO'] | A: 2.45e-14
R50: ARRHENIUS | Reactants: ['C_O2'] | Products: ['HCHO', 'HO2'] | A: 5.90e-13
R51: ARRHENIUS | Reactants: ['RO2_R', 'NO'] | Products: ['NO2', 'HO2'] | A: 2.70e-12
R52: ARRHENIUS | Reactants: ['RO2_R', 'HO2'] | Products: ['ROOH'] | A: 1.90e-13
R53: ARRHENIUS | Reactants: ['RO2_R', 'NO3'] | Products: ['NO2', 'HO2'] | A: 2.30e-12
R54: ARRHENIUS | Reactants: ['RO2_R', 'C_O2'] | Products: ['HO2', 'HCHO', 'MEOH'] | A: 2.00e-13
R55: ARRHENIUS | Reactants: ['RO2_R'] | Products: ['HO2'] | A: 3.50e-14
R56: ARRHENIUS | Reactants: ['R2O2', 'NO'] | Products: ['NO2'] | A: 2.70e-12
R57: ARRHENIUS | Reactants: ['R2O2', 'HO2'] | Products: ['HO2'] | A: 1.90e-13
R58: ARRHENIUS | Reactants: ['R2O2', 'NO3'] | Products: ['NO2'] | A: 2.30e-12
R59: ARRHENIUS | Reactants: ['R2O2', 'C_O2'] | Products: ['C_O2'] | A: 2.00e-13
R60: ARRHENIUS | Reactants: ['R2O2', 'RO2_R'] | Products: ['RO2_R'] | A: 3.50e-14
R61: ARRHENIUS | Reactants: ['R2O2'] | Products: ['R2O2'] | A: 0.0
R62: ARRHENIUS | Reactants: ['RO2_N', 'NO'] | Products: ['RNO3'] | A: 2.70e-12
R63: ARRHENIUS | Reactants: ['RO2_N', 'HO2'] | Products: ['ROOH'] | A: 1.90e-13
R64: ARRHENIUS | Reactants: ['RO2_N', 'C_O2'] | Products: ['HO2', 'MEOH', 'MEK', 'PROD2', 'HCHO'] | A: 2.00e-13
R65: ARRHENIUS | Reactants: ['RO2_N', 'NO3'] | Products: ['NO2', 'HO2', 'MEK'] | A: 2.30e-12
R66: ARRHENIUS | Reactants: ['RO2_N', 'RO2_R'] | Products: ['HO2', 'MEK', 'PROD2'] | A: 3.50e-14
R67: ARRHENIUS | Reactants: ['RO2_N', 'R2O2'] | Products: ['RO2_N'] | A: 3.50e-14
R68: ARRHENIUS | Reactants: ['RO2_N'] | Products: ['MEK', 'HO2', 'PROD2'] | A: 3.50e-14
R69: TROE | Reactants: ['CCO_O2', 'NO2'] | Products: ['PAN'] | A: N/A
R70: TROE | Reactants: ['PAN'] | Products: ['CCO_O2', 'NO2'] | A: N/A
R71: ARRHENIUS | Reactants: ['CCO_O2', 'NO'] | Products: ['C_O2', 'NO2'] | A: 7.80e-12
R72: ARRHENIUS | Reactants: ['CCO_O2', 'HO2'] | Products: ['CCO_OOH', 'CCO_OH', 'O3'] | A: 4.30e-13
R73: ARRHENIUS | Reactants: ['CCO_O2', 'NO3'] | Products: ['C_O2', 'NO2'] | A: 4.00e-12
R74: ARRHENIUS | Reactants: ['CCO_O2', 'C_O2'] | Products: ['CCO_OH', 'HCHO'] | A: 1.80e-12
R75: ARRHENIUS | Reactants: ['CCO_O2', 'RO2_R'] | Products: ['CCO_OH'] | A: 7.50e-12
R76: ARRHENIUS | Reactants: ['CCO_O2', 'R2O2'] | Products: ['CCO_O2'] | A: 7.50e-12
R77: ARRHENIUS | Reactants: ['CCO_O2', 'RO2_N'] | Products: ['CCO_OH', 'PROD2'] | A: 7.50e-12
R78: ARRHENIUS | Reactants: ['CCO_O2'] | Products: ['C_O2'] | A: 2.90e-12
R79: ARRHENIUS | Reactants: ['RCO_O2', 'NO2'] | Products: ['PAN2'] | A: 1.20e-11
R80: ARRHENIUS | Reactants: ['PAN2'] | Products: ['RCO_O2', 'NO2'] | A: 2.00e+15
R81: ARRHENIUS | Reactants: ['RCO_O2', 'NO'] | Products: ['NO2', 'CCHO', 'RO2_R'] | A: 1.25e-11
R82: ARRHENIUS | Reactants: ['RCO_O2', 'HO2'] | Products: ['RCO_OOH', 'RCO_OH', 'O3'] | A: 4.30e-13
R83: ARRHENIUS | Reactants: ['RCO_O2', 'NO3'] | Products: ['NO2', 'CCHO', 'RO2_R'] | A: 4.00e-12
R84: ARRHENIUS | Reactants: ['RCO_O2', 'C_O2'] | Products: ['RCO_OH', 'HCHO'] | A: 1.80e-12
R85: ARRHENIUS | Reactants: ['RCO_O2', 'RO2_R'] | Products: ['RCO_OH'] | A: 7.50e-12
R86: ARRHENIUS | Reactants: ['RCO_O2', 'R2O2'] | Products: ['RCO_O2'] | A: 7.50e-12
R87: ARRHENIUS | Reactants: ['RCO_O2', 'RO2_N'] | Products: ['RCO_OH', 'PROD2'] | A: 7.50e-12
R88: ARRHENIUS | Reactants: ['RCO_O2', 'CCO_O2'] | Products: ['C_O2', 'CCHO', 'RO2_R'] | A: 2.90e-12
R89: ARRHENIUS | Reactants: ['RCO_O2'] | Products: ['CCHO', 'RO2_R'] | A: 2.90e-12
R90: ARRHENIUS | Reactants: ['BZCO_O2', 'NO2'] | Products: ['PBZN'] | A: 1.37e-11
R91: ARRHENIUS | Reactants: ['PBZN'] | Products: ['BZCO_O2', 'NO2'] | A: 7.90e+16
R92: ARRHENIUS | Reactants: ['BZCO_O2', 'NO'] | Products: ['NO2', 'BZ_O', 'R2O2'] | A: 1.25e-11
R93: ARRHENIUS | Reactants: ['BZCO_O2', 'HO2'] | Products: ['RCO_OOH', 'RCO_OH', 'O3'] | A: 4.30e-13
R94: ARRHENIUS | Reactants: ['BZCO_O2', 'NO3'] | Products: ['NO2', 'BZ_O', 'R2O2'] | A: 4.00e-12
R95: ARRHENIUS | Reactants: ['BZCO_O2', 'C_O2'] | Products: ['RCO_OH', 'HCHO'] | A: 1.80e-12
R96: ARRHENIUS | Reactants: ['BZCO_O2', 'RO2_R'] | Products: ['RCO_OH'] | A: 7.50e-12
R97: ARRHENIUS | Reactants: ['BZCO_O2', 'R2O2'] | Products: ['BZCO_O2'] | A: 7.50e-12
R98: ARRHENIUS | Reactants: ['BZCO_O2', 'RO2_N'] | Products: ['RCO_OH', 'PROD2'] | A: 7.50e-12
R99: ARRHENIUS | Reactants: ['BZCO_O2', 'CCO_O2'] | Products: ['C_O2', 'BZ_O', 'R2O2'] | A: 2.90e-12
R100: ARRHENIUS | Reactants: ['BZCO_O2', 'RCO_O2'] | Products: ['CCHO', 'RO2_R', 'BZ_O', 'R2O2'] | A: 2.90e-12
R101: ARRHENIUS | Reactants: ['BZCO_O2'] | Products: ['BZ_O', 'R2O2'] | A: 2.90e-12
R102: ARRHENIUS | Reactants: ['MA_RCO3', 'NO2'] | Products: ['MA_PAN'] | A: 1.20e-11
R103: ARRHENIUS | Reactants: ['MA_PAN'] | Products: ['MA_RCO3', 'NO2'] | A: 1.60e+16
R104: ARRHENIUS | Reactants: ['MA_RCO3', 'NO'] | Products: ['NO2', 'HCHO', 'CCO_O2'] | A: 1.25e-11
R105: ARRHENIUS | Reactants: ['MA_RCO3', 'HO2'] | Products: ['RCO_OOH', 'RCO_OH', 'O3'] | A: 4.30e-13
R106: ARRHENIUS | Reactants: ['MA_RCO3', 'NO3'] | Products: ['NO2', 'HCHO', 'CCO_O2'] | A: 4.00e-12
R107: ARRHENIUS | Reactants: ['MA_RCO3', 'C_O2'] | Products: ['RCO_OH', 'HCHO'] | A: 1.80e-12
R108: ARRHENIUS | Reactants: ['MA_RCO3', 'RO2_R'] | Products: ['RCO_OH'] | A: 7.50e-12
R109: ARRHENIUS | Reactants: ['MA_RCO3', 'R2O2'] | Products: ['MA_RCO3'] | A: 7.50e-12
R110: ARRHENIUS | Reactants: ['MA_RCO3', 'RO2_N'] | Products: ['RCO_OH'] | A: 7.50e-12
R111: ARRHENIUS | Reactants: ['MA_RCO3', 'CCO_O2'] | Products: ['C_O2', 'HCHO', 'CCO_O2'] | A: 2.90e-12
R112: ARRHENIUS | Reactants: ['MA_RCO3', 'RCO_O2'] | Products: ['HCHO', 'CCO_O2', 'CCHO', 'RO2_R'] | A: 2.90e-12
R113: ARRHENIUS | Reactants: ['MA_RCO3', 'BZCO_O2'] | Products: ['HCHO', 'CCO_O2', 'BZ_O', 'R2O2'] | A: 2.90e-12
R114: ARRHENIUS | Reactants: ['MA_RCO3'] | Products: ['HCHO', 'CCO_O2'] | A: 2.90e-12
R115: ARRHENIUS | Reactants: ['TBU_O', 'NO2'] | Products: ['RNO3'] | A: 2.40e-11
R116: ARRHENIUS | Reactants: ['TBU_O'] | Products: ['ACET', 'C_O2'] | A: 7.50e+14
R117: ARRHENIUS | Reactants: ['BZ_O', 'NO2'] | Products: ['NPHE'] | A: 2.30e-11
R118: ARRHENIUS | Reactants: ['BZ_O', 'HO2'] | Products: ['PHEN'] | A: 1.90e-13
R119: ARRHENIUS | Reactants: ['BZ_O'] | Products: ['PHEN'] | A: 1.00e-03
R120: ARRHENIUS | Reactants: ['BZNO2_O', 'NO2'] | Products: ['XN', 'XC'] | A: 7.50e+14
R121: ARRHENIUS | Reactants: ['BZNO2_O', 'HO2'] | Products: ['NPHE'] | A: 2.30e-11
R122: ARRHENIUS | Reactants: ['BZNO2_O'] | Products: ['NPHE'] | A: 1.90e-13
R123: PHOTOLYSIS | Reactants: ['HCHO'] | Products: ['HO2', 'CO'] | A: 2.32e-3
R124: PHOTOLYSIS | Reactants: ['HCHO'] | Products: ['CO'] | A: 3.15e-3
R125: ARRHENIUS | Reactants: ['HCHO', 'OH'] | Products: ['HO2', 'CO'] | A: 8.60e-12
R126: ARRHENIUS | Reactants: ['HCHO', 'HO2'] | Products: ['HOCOO'] | A: 9.70e-15
R127: ARRHENIUS | Reactants: ['HOCOO'] | Products: ['HO2', 'HCHO'] | A: 2.40e+12
R128: ARRHENIUS | Reactants: ['HOCOO', 'NO'] | Products: ['HCOOH', 'NO2', 'HO2'] | A: 2.80e-12
R129: ARRHENIUS | Reactants: ['HCHO', 'NO3'] | Products: ['HNO3', 'HO2', 'CO'] | A: 2.00e-12
R130: ARRHENIUS | Reactants: ['CCHO', 'OH'] | Products: ['CCO_O2'] | A: 5.60e-12
R131: PHOTOLYSIS | Reactants: ['CCHO'] | Products: ['CO', 'HO2', 'C_O2'] | A: 4.16e-4
R132: ARRHENIUS | Reactants: ['CCHO', 'NO3'] | Products: ['HNO3', 'CCO_O2'] | A: 1.40e-12
R133: ARRHENIUS | Reactants: ['RCHO', 'OH'] | Products: ['RO2_R', 'RO2_N', 'RCO_O2', 'CO', 'CCHO'] | A: 2.00e-11
R134: PHOTOLYSIS | Reactants: ['RCHO'] | Products: ['CCHO', 'RO2_R', 'CO', 'HO2'] | A: 1.40e-3
R135: ARRHENIUS | Reactants: ['RCHO', 'NO3'] | Products: ['HNO3', 'RCO_O2'] | A: 1.40e-12
R136: ARRHENIUS | Reactants: ['ACET', 'OH'] | Products: ['HCHO', 'CCO_O2', 'R2O2'] | A: 1.10e-12
R137: PHOTOLYSIS | Reactants: ['ACET'] | Products: ['CCO_O2', 'C_O2'] | A: 4.16e-5
R138: ARRHENIUS | Reactants: ['MEK', 'OH'] | Products: ['RO2_R', 'RO2_N', 'R2O2', 'CCO_O2', 'RCO_O2', 'HCHO', 'CCHO', 'RCHO'] | A: 1.30e-12
R139: PHOTOLYSIS | Reactants: ['MEK'] | Products: ['CCO_O2', 'CCHO', 'RO2_R'] | A: 9.49e-4*(1.50e-1*SUN/60.0)
R140: ARRHENIUS | Reactants: ['MEOH', 'OH'] | Products: ['HCHO', 'HO2'] | A: 3.10e-12
R141: ARRHENIUS | Reactants: ['COOH', 'OH'] | Products: ['HCHO', 'OH', 'C_O2'] | A: 2.90e-12
R142: PHOTOLYSIS | Reactants: ['COOH'] | Products: ['HCHO', 'HO2', 'OH'] | A: 3.94e-4
R143: ARRHENIUS | Reactants: ['ROOH', 'OH'] | Products: ['RCHO', 'RO2_R', 'OH'] | A: 1.10e-11
R144: PHOTOLYSIS | Reactants: ['ROOH'] | Products: ['RCHO', 'HO2', 'OH'] | A: 3.94e-4
R145: PHOTOLYSIS | Reactants: ['GLY'] | Products: ['CO', 'HO2'] | A: 8.93e-3
R146: PHOTOLYSIS | Reactants: ['GLY'] | Products: ['HCHO', 'CO'] | A: 1.81e-1*(6.00e-3*SUN/60.0)
R147: ARRHENIUS | Reactants: ['GLY', 'OH'] | Products: ['HO2', 'CO', 'RCO_O2'] | A: 1.10e-11
R148: ARRHENIUS | Reactants: ['GLY', 'NO3'] | Products: ['HNO3', 'HO2', 'CO', 'RCO_O2'] | A: 2.80e-12
R149: PHOTOLYSIS | Reactants: ['MGLY'] | Products: ['HO2', 'CO', 'CCO_O2'] | A: 1.10e-2
R150: ARRHENIUS | Reactants: ['MGLY', 'OH'] | Products: ['CO', 'CCO_O2'] | A: 1.50e-11
R151: ARRHENIUS | Reactants: ['MGLY', 'NO3'] | Products: ['HNO3', 'CO', 'CCO_O2'] | A: 1.40e-12
R152: PHOTOLYSIS | Reactants: ['BACL'] | Products: ['CCO_O2'] | A: 1.90e-2
R153: ARRHENIUS | Reactants: ['PHEN', 'OH'] | Products: ['BZ_O', 'RO2_R', 'GLY'] | A: 2.63e-11
R154: ARRHENIUS | Reactants: ['PHEN', 'NO3'] | Products: ['HNO3', 'BZ_O'] | A: 3.78e-12
R155: ARRHENIUS | Reactants: ['CRES', 'OH'] | Products: ['BZ_O', 'RO2_R', 'MGLY'] | A: 4.20e-11
R156: ARRHENIUS | Reactants: ['CRES', 'NO3'] | Products: ['HNO3', 'BZ_O'] | A: 1.37e-11
R157: ARRHENIUS | Reactants: ['NPHE', 'NO3'] | Products: ['HNO3', 'BZNO2_O'] | A: 3.78e-12
R158: ARRHENIUS | Reactants: ['BALD', 'OH'] | Products: ['BZCO_O2'] | A: 1.29e-11
R159: PHOTOLYSIS | Reactants: ['BALD'] | Products: ['XC'] | A: 6.22e-2*(5.00e-2*SUN/60.0)
R160: ARRHENIUS | Reactants: ['BALD', 'NO3'] | Products: ['HNO3', 'BZCO_O2'] | A: 1.40e-12
R161: ARRHENIUS | Reactants: ['METHACRO', 'OH'] | Products: ['RO2_R', 'CO', 'HCHO', 'MEK', 'MGLY', 'MA_RCO3'] | A: 1.86e-11
R162: ARRHENIUS | Reactants: ['METHACRO', 'O3'] | Products: ['HO2', 'RO2_R', 'OH', 'RCO_O2', 'CO', 'HCHO', 'MGLY', 'HCOOH'] | A: 1.36e-15
R163: ARRHENIUS | Reactants: ['METHACRO', 'NO3'] | Products: ['HNO3', 'RO2_R', 'CO', 'MA_RCO3'] | A: 1.50e-12
R164: ARRHENIUS | Reactants: ['METHACRO', 'O3P'] | Products: ['RCHO'] | A: 6.34e-12
R165: PHOTOLYSIS | Reactants: ['METHACRO'] | Products: ['HO2', 'RO2_R', 'OH', 'CCO_O2', 'CO', 'HCHO', 'MA_RCO3'] | A: 3.32e-2*(4.10e-3*SUN/60.0)
R166: ARRHENIUS | Reactants: ['MVK', 'OH'] | Products: ['RO2_R', 'RO2_N', 'R2O2', 'CCO_O2', 'HCHO', 'RCHO', 'MGLY'] | A: 4.14e-12
R167: ARRHENIUS | Reactants: ['MVK', 'O3'] | Products: ['HO2', 'RO2_R', 'OH', 'RCO_O2', 'CO', 'HCHO', 'MGLY', 'HCOOH'] | A: 7.51e-16
R168: ARRHENIUS | Reactants: ['MVK', 'O3P'] | Products: ['RCHO', 'MEK'] | A: 4.32e-12
R169: PHOTOLYSIS | Reactants: ['MVK'] | Products: ['C_O2', 'CO', 'PROD2', 'MA_RCO3'] | A: 3.32e-2*(2.10e-3*SUN/60.0)
R170: ARRHENIUS | Reactants: ['ISOPROD', 'OH'] | Products: ['RO2_R', 'RO2_N', 'MA_RCO3', 'CO', 'HCHO', 'CCHO', 'RCHO', 'MEK', 'PROD2', 'GLY', 'MGLY'] | A: 6.19e-11
R171: ARRHENIUS | Reactants: ['ISOPROD', 'O3'] | Products: ['HO2', 'RO2_R', 'RCO_O2', 'OH', 'CO', 'HCHO', 'CCHO', 'MEK', 'GLY', 'MGLY', 'HCOOH', 'RCO_OH'] | A: 4.18e-18
R172: ARRHENIUS | Reactants: ['ISOPROD', 'NO3'] | Products: ['RO2_R', 'RO2_N', 'MA_RCO3', 'CO', 'HNO3', 'HCHO', 'RCHO', 'MGLY', 'RNO3'] | A: 1.00e-13
R173: PHOTOLYSIS | Reactants: ['ISOPROD'] | Products: ['HO2', 'CCO_O2', 'RCO_O2', 'CO', 'HCHO', 'CCHO', 'MEK'] | A: 3.32e-2*(4.10e-3*SUN/60.0)
R174: ARRHENIUS | Reactants: ['PROD2', 'OH'] | Products: ['HO2', 'RO2_R', 'RO2_N', 'CCO_O2', 'RCO_O2', 'HCHO', 'CCHO', 'RCHO', 'MEK', 'PROD2'] | A: 1.50e-11
R175: PHOTOLYSIS | Reactants: ['PROD2'] | Products: ['RO2_R', 'RO2_N', 'R2O2', 'CCO_O2', 'RCO_O2', 'HCHO', 'CCHO', 'RCHO'] | A: 9.49e-4*(2.00e-2*SUN/60.0)
R176: ARRHENIUS | Reactants: ['RNO3', 'OH'] | Products: ['NO2', 'HO2', 'RO2_R', 'RO2_N', 'R2O2', 'HCHO', 'CCHO', 'RCHO', 'ACET', 'MEK', 'PROD2', 'RNO3'] | A: 7.80e-12
R177: PHOTOLYSIS | Reactants: ['RNO3'] | Products: ['NO2', 'HO2', 'RO2_R', 'RO2_N', 'R2O2', 'HCHO', 'CCHO', 'RCHO', 'ACET', 'MEK', 'PROD2'] | A: 2.35e-4
R178: ARRHENIUS | Reactants: ['DCB1', 'OH'] | Products: ['RCHO', 'RO2_R', 'CO'] | A: 5.00e-11
R179: ARRHENIUS | Reactants: ['DCB1', 'O3'] | Products: ['HO2', 'OH', 'CO', 'GLY'] | A: 2.00e-18
R180: ARRHENIUS | Reactants: ['DCB2', 'OH'] | Products: ['R2O2', 'RCHO', 'CCO_O2'] | A: 5.00e-11
R181: PHOTOLYSIS | Reactants: ['DCB2'] | Products: ['RO2_R', 'CCO_O2', 'HO2', 'CO', 'R2O2', 'GLY', 'MGLY'] | A: 2.06e-1*(3.65e-1*SUN/60.0)
R182: ARRHENIUS | Reactants: ['DCB3', 'OH'] | Products: ['R2O2', 'RCHO', 'CCO_O2'] | A: 5.00e-11
R183: PHOTOLYSIS | Reactants: ['DCB3'] | Products: ['RO2_R', 'CCO_O2', 'HO2', 'CO', 'R2O2', 'GLY', 'MGLY'] | A: 3.32e-2*(7.28*SUN/60.0)
R184: ARRHENIUS | Reactants: ['CH4', 'OH'] | Products: ['C_O2'] | A: 2.15e-12
R185: ARRHENIUS | Reactants: ['ETHENE', 'OH'] | Products: ['RO2_R', 'HCHO', 'CCHO'] | A: 1.96e-12
R186: ARRHENIUS | Reactants: ['ETHENE', 'O3'] | Products: ['OH', 'HO2', 'CO', 'HCHO', 'HCOOH'] | A: 9.14e-15
R187: ARRHENIUS | Reactants: ['ETHENE', 'NO3'] | Products: ['RO2_R', 'RCHO'] | A: 4.39e-13
R188: ARRHENIUS | Reactants: ['ETHENE', 'O3P'] | Products: ['HO2', 'RO2_R', 'C_O2', 'CO', 'HCHO', 'CCHO', 'GLY'] | A: 1.04e-11
R189: ARRHENIUS | Reactants: ['ISOPRENE', 'OH'] | Products: ['RO2_R', 'RO2_N', 'R2O2', 'HCHO', 'METHACRO', 'MVK', 'ISOPROD'] | A: 2.50e-11
R190: ARRHENIUS | Reactants: ['ISOPRENE', 'O3'] | Products: ['OH', 'RO2_R', 'RO2_N', 'R2O2', 'MA_RCO3', 'CO', 'HCHO', 'PROD2', 'METHACRO', 'MVK', 'HCOOH', 'RCO_OH'] | A: 7.86e-15
R191: ARRHENIUS | Reactants: ['ISOPRENE', 'NO3'] | Products: ['NO2', 'RO2_R', 'RO2_N', 'R2O2', 'ISOPROD'] | A: 3.03e-12
R192: ARRHENIUS | Reactants: ['ISOPRENE', 'O3P'] | Products: ['RO2_N', 'R2O2', 'C_O2', 'MA_RCO3', 'HCHO', 'PROD2'] | A: 3.60e-11
R193: ARRHENIUS | Reactants: ['TERP', 'OH'] | Products: ['RO2_R', 'RO2_N', 'R2O2', 'HCHO', 'RCHO', 'PROD2'] | A: 1.83e-11
R194: ARRHENIUS | Reactants: ['TERP', 'O3'] | Products: ['OH', 'HO2', 'RO2_R', 'RO2_N', 'R2O2', 'CCO_O2', 'RCO_O2', 'CO', 'HCHO', 'RCHO', 'ACET', 'PROD2', 'GLY', 'BACL', 'HCOOH', 'RCO_OH'] | A: 1.08e-15
R195: ARRHENIUS | Reactants: ['TERP', 'NO3'] | Products: ['NO2', 'RO2_R', 'RO2_N', 'R2O2', 'RCHO', 'RNO3'] | A: 3.66e-12
R196: ARRHENIUS | Reactants: ['TERP', 'O3P'] | Products: ['RCHO', 'PROD2'] | A: 3.27e-11
R197: ARRHENIUS | Reactants: ['ALK1', 'OH'] | Products: ['RO2_R', 'CCHO'] | A: 1.37e-12
R198: ARRHENIUS | Reactants: ['ALK2', 'OH'] | Products: ['OH', 'HO2', 'RO2_R', 'RO2_N', 'CO', 'HCHO', 'RCHO', 'ACET', 'GLY', 'HCOOH'] | A: 9.87e-12
R199: ARRHENIUS | Reactants: ['ALK3', 'OH'] | Products: ['RO2_R', 'RO2_N', 'R2O2', 'TBU_O', 'HCHO', 'CCHO', 'RCHO', 'ACET', 'MEK'] | A: 1.019e-11
R200: ARRHENIUS | Reactants: ['ALK4', 'OH'] | Products: ['RO2_R', 'RO2_N', 'R2O2', 'C_O2', 'CCO_O2', 'CO', 'HCHO', 'CCHO', 'RCHO', 'ACET', 'MEK', 'PROD2'] | A: 5.946e-12
R201: ARRHENIUS | Reactants: ['ALK5', 'OH'] | Products: ['RO2_R', 'RO2_N', 'R2O2', 'HCHO', 'CCHO', 'RCHO', 'ACET', 'MEK', 'PROD2'] | A: 1.112e-11
R202: ARRHENIUS | Reactants: ['ARO1', 'OH'] | Products: ['HO2', 'RO2_R', 'RO2_N', 'PROD2', 'GLY', 'MGLY', 'PHEN', 'CRES', 'BALD', 'DCB1', 'DCB2', 'DCB3'] | A: 1.81e-12
R203: ARRHENIUS | Reactants: ['ARO2', 'OH'] | Products: ['HO2', 'RO2_R', 'RO2_N', 'GLY', 'MGLY', 'BACL', 'CRES', 'BALD', 'DCB1', 'DCB2', 'DCB3'] | A: 2.640e-11
R204: ARRHENIUS | Reactants: ['OLE1', 'OH'] | Products: ['RO2_R', 'RO2_N', 'R2O2', 'HCHO', 'CCHO', 'RCHO', 'ACET', 'PROD2'] | A: 7.095e-12
R205: ARRHENIUS | Reactants: ['OLE1', 'O3'] | Products: ['OH', 'HO2', 'RO2_R', 'RO2_N', 'C_O2', 'CO', 'HCHO', 'CCHO', 'RCHO', 'ACET', 'PROD2', 'HCOOH', 'CCO_OH', 'RCO_OH'] | A: 2.617e-15
R206: ARRHENIUS | Reactants: ['OLE1', 'NO3'] | Products: ['RO2_R', 'RO2_N', 'R2O2', 'CCHO', 'RCHO', 'ACET', 'RNO3'] | A: 4.453e-14
R207: ARRHENIUS | Reactants: ['OLE1', 'O3P'] | Products: ['RCHO', 'MEK', 'PROD2'] | A: 1.074e-11
R208: ARRHENIUS | Reactants: ['OLE2', 'OH'] | Products: ['RO2_R', 'RO2_N', 'R2O2', 'HCHO', 'CCHO', 'RCHO', 'ACET', 'MEK', 'BALD', 'METHACRO', 'ISOPROD'] | A: 1.743e-11
R209: ARRHENIUS | Reactants: ['OLE2', 'O3'] | Products: ['OH', 'HO2', 'RO2_R', 'RO2_N', 'R2O2', 'C_O2', 'CCO_O2', 'RCO_O2', 'CO', 'HCHO', 'CCHO', 'RCHO', 'ACET', 'MEK', 'PROD2', 'BALD', 'METHACRO', 'MVK', 'HCOOH', 'CCO_OH', 'RCO_OH'] | A: 5.022e-16
R210: ARRHENIUS | Reactants: ['OLE2', 'NO3'] | Products: ['NO2', 'RO2_R', 'RO2_N', 'R2O2', 'C_O2', 'HCHO', 'CCHO', 'RCHO', 'ACET', 'MEK', 'BALD', 'MVK', 'RNO3'] | A: 7.265e-13
R211: ARRHENIUS | Reactants: ['OLE2', 'O3P'] | Products: ['HO2', 'RO2_R', 'RO2_N', 'CO', 'RCHO', 'MEK', 'PROD2', 'METHACRO'] | A: 2.085e-11
d[O3]/dt = (IMPLICIT: 4.9010355073085e-27*C_AIR*C_O2*C_O3P/Temp**2.8 + 1.075e-13*C_BZCO_O2*C_HO2*exp(1040.0/Temp) + 1.075e-13*C_CCO_O2*C_HO2*exp(1040.0/Temp) - 2.0e-18*C_DCB1*C_O3 - 9.14e-15*C_ETHENE*C_O3*exp(-2580.0/Temp) + 1.075e-13*C_HO2*C_MA_RCO3*exp(1040.0/Temp) - 1.4e-14*C_HO2*C_O3*exp(-600.0/Temp) + 1.075e-13*C_HO2*C_RCO_O2*exp(1040.0/Temp) - 7.86e-15*C_ISOPRENE*C_O3*exp(-1912.0/Temp) - 4.18e-18*C_ISOPROD*C_O3 - 1.36e-15*C_METHACRO*C_O3*exp(-2114.0/Temp) - 7.51e-16*C_MVK*C_O3*exp(-1520.0/Temp) - 1.8e-12*C_NO*C_O3*exp(-1370.0/Temp) - 1.4e-13*C_NO2*C_O3*exp(-2470.0/Temp) - 8.0e-12*C_O3*C_O3P*exp(-2060.0/Temp) - 1.9e-12*C_O3*C_OH*exp(-1000.0/Temp) - 2.617e-15*C_O3*C_OLE1*exp(-1640.0/Temp) - 5.022e-16*C_O3*C_OLE2*exp(-461.0/Temp) - 1.08e-15*C_O3*C_TERP*exp(-821.0/Temp) - 1.0*C_O3*J_3 - 1.0*C_O3*J_4) + (EXPLICIT: 0)
d[H2O2]/dt = (IMPLICIT: 1.0*C_H2O*C_HO2**2*(2.59e-54*C_AIR*exp(3180.0/Temp) + 3.08e-34*exp(2800.0/Temp)) - 2.9e-12*C_H2O2*C_OH*exp(-160.0/Temp) - 1.0*C_H2O2*J_9 + 1.0*C_HO2**2*(1.85e-33*C_AIR*exp(980.0/Temp) + 2.2e-13*exp(600.0/Temp))) + (EXPLICIT: 0)
d[NO]/dt = (IMPLICIT: -2.53853279130624e-37*0.6**(1.0/(log(1.24736169269364e-26*C_AIR*Temp**2.5)**2/log(10)**2 + 1.0))*C_AIR*C_NO*C_OH*Temp**2.6/(1.24736169269364e-26*C_AIR*Temp**2.5 + 1.0) - 9.19166118840122e-28*C_AIR*C_NO*C_O3P/Temp**1.6 - 1.25e-11*C_BZCO_O2*C_NO*exp(240.0/Temp) - 7.8e-12*C_CCO_O2*C_NO*exp(300.0/Temp) - 2.8e-12*C_C_O2*C_NO*exp(285.0/Temp) - 3.4e-12*C_HO2*C_NO*exp(270.0/Temp) - 2.8e-12*C_HOCOO*C_NO*exp(285.0/Temp) + 1.0*C_HONO*J_5 - 1.25e-11*C_MA_RCO3*C_NO*exp(240.0/Temp) - 6.6e-39*C_NO**2*C_O2*exp(530.0/Temp) - 1.8e-11*C_NO*C_NO3*exp(110.0/Temp) - 1.8e-12*C_NO*C_O3*exp(-1370.0/Temp) - 2.7e-12*C_NO*C_R2O2*exp(360.0/Temp) - 1.25e-11*C_NO*C_RCO_O2*exp(240.0/Temp) - 2.7e-12*C_NO*C_RO2_N*exp(360.0/Temp) - 2.7e-12*C_NO*C_RO2_R*exp(360.0/Temp) + 4.5e-14*C_NO2*C_NO3*exp(-1260.0/Temp) + 6.5e-12*C_NO2*C_O3P*exp(120.0/Temp) + 1.0*C_NO2*J_0 + 1.0*C_NO3*J_1) + (EXPLICIT: 0)
d[NO2]/dt = (IMPLICIT: -6.97915519241595e-46*0.3**(1.0/(log(9.86349295796486e-33*C_AIR*Temp**6.2)**2/log(10)**2 + 1.0))*C_AIR*C_CCO_O2*C_NO2*Temp**7.1/(9.86349295796486e-33*C_AIR*Temp**6.2 + 1.0) + 0.0049*0.3**(1.0/(log(1.225e-19*C_AIR*exp(-1500.0/Temp)/(Temp/300)**0.0.)**2/log(10)**2 + 1.0))*C_AIR*C_PAN*exp(12100.0/Temp)/(1.225e-19*C_AIR*exp(-1500.0/Temp)/(Temp/300)**0.0. + 1.0) - 5.98733612492945e-39*0.45**(1.0/(log(9.56707972824405e-28*C_AIR*Temp**3.7)**2/log(10)**2 + 1.0))*C_AIR*C_NO2*C_NO3*Temp**3.5/(9.56707972824405e-28*C_AIR*Temp**3.7 + 1.0) + 2.13833433033195e-12*0.45**(1.0/(log(1.24621148321367e-27*C_AIR*Temp**3.6*exp(-80.0/Temp))**2/log(10)**2 + 1.0))*C_AIR*C_N2O5*Temp**3.5*exp(11000.0/Temp)/(1.24621148321367e-27*C_AIR*Temp**3.6*exp(-80.0/Temp) + 1.0) + 4.1e-5*0.5**(1.0/(log(7.19298245614035e-21*C_AIR*exp(-520.0/Temp))**2/log(10)**2 + 1.0))*C_AIR*C_HNO4*exp(10650.0/Temp)/(7.19298245614035e-21*C_AIR*exp(-520.0/Temp) + 1.0) - 5.08780413527122e-38*0.6**(1.0/(log(4.8502994011976e-22*C_AIR*Temp**1.0)**2/log(10)**2 + 1.0))*C_AIR*C_NO2*C_OH*Temp**3.1/(4.8502994011976e-22*C_AIR*Temp**1.0 + 1.0) - 2.1305144789204e-39*0.6**(1.0/(log(4.53300952961788e-28*C_AIR*Temp**3.2)**2/log(10)**2 + 1.0))*C_AIR*C_HO2*C_NO2*Temp**3.2/(4.53300952961788e-28*C_AIR*Temp**3.2 + 1.0) - 1.0e-36*0.8**(1.0/(log(4.54545454545455e-26*C_AIR*Temp**2.0)**2/log(10)**2 + 1.0))*C_AIR*C_NO2*C_O3P*Temp**2.0/(4.54545454545455e-26*C_AIR*Temp**2.0 + 1.0) + 9.19166118840122e-28*C_AIR*C_NO*C_O3P/Temp**1.6 + 1.25e-11*C_BZCO_O2*C_NO*exp(240.0/Temp) - 1.37e-11*C_BZCO_O2*C_NO2 + 4.0e-12*C_BZCO_O2*C_NO3 - 750000000000000.0*C_BZNO2_O*C_NO2*exp(-8152.0/Temp) - 2.3e-11*C_BZ_O*C_NO2*exp(150.0/Temp) + 7.8e-12*C_CCO_O2*C_NO*exp(300.0/Temp) + 4.0e-12*C_CCO_O2*C_NO3 + 2.8e-12*C_C_O2*C_NO*exp(285.0/Temp) + 1.3e-12*C_C_O2*C_NO3 + 1.0*C_HNO3*J_7 + 1.5e-12*C_HNO4*C_OH*exp(360.0/Temp) + 0.61*C_HNO4*J_8 + 3.4e-12*C_HO2*C_NO*exp(270.0/Temp) + 3.2e-12*C_HO2*C_NO3 + 2.8e-12*C_HOCOO*C_NO*exp(285.0/Temp) + 2.7e-12*C_HONO*C_OH*exp(260.0/Temp) + 1.0*C_HONO*J_6 + 5.6661e-13*C_ISOPRENE*C_NO3*exp(-448.0/Temp) + 1.6e+16*C_MA_PAN*exp(-13486.0/Temp) + 1.25e-11*C_MA_RCO3*C_NO*exp(240.0/Temp) - 2.03512165410849e-9*C_MA_RCO3*C_NO2/Temp**0.9 + 4.0e-12*C_MA_RCO3*C_NO3 + 6.6e-39*C_NO**2*C_O2*exp(530.0/Temp) + 3.6e-11*C_NO*C_NO3*exp(110.0/Temp) + 1.8e-12*C_NO*C_O3*exp(-1370.0/Temp) + 2.7e-12*C_NO*C_R2O2*exp(360.0/Temp) + 1.25e-11*C_NO*C_RCO_O2*exp(240.0/Temp) + 2.7e-12*C_NO*C_RO2_R*exp(360.0/Temp) - 1.4e-13*C_NO2*C_O3*exp(-2470.0/Temp) - 6.5e-12*C_NO2*C_O3P*exp(120.0/Temp) - 2.03512165410849e-9*C_NO2*C_RCO_O2/Temp**0.9 - 2.4e-11*C_NO2*C_TBU_O - 1.0*C_NO2*J_0 + 1.7e-12*C_NO3**2*exp(-2450.0/Temp) + 2.0e-11*C_NO3*C_OH + 2.840615e-13*C_NO3*C_OLE2 + 2.3e-12*C_NO3*C_R2O2 + 4.0e-12*C_NO3*C_RCO_O2 + 2.3e-12*C_NO3*C_RO2_N + 2.3e-12*C_NO3*C_RO2_R + 1.73484e-12*C_NO3*C_TERP*exp(175.0/Temp) + 1.0*C_NO3*J_2 + 2.6364e-12*C_OH*C_RNO3 + 2.0e+15*C_PAN2*exp(-12800.0/Temp) + 7.9e+16*C_PBZN*exp(-14000.0/Temp) + 1.0*C_RNO3*J_27) + (EXPLICIT: 0)
d[NO3]/dt = (IMPLICIT: -5.98733612492945e-39*0.45**(1.0/(log(9.56707972824405e-28*C_AIR*Temp**3.7)**2/log(10)**2 + 1.0))*C_AIR*C_NO2*C_NO3*Temp**3.5/(9.56707972824405e-28*C_AIR*Temp**3.7 + 1.0) + 2.13833433033195e-12*0.45**(1.0/(log(1.24621148321367e-27*C_AIR*Temp**3.6*exp(-80.0/Temp))**2/log(10)**2 + 1.0))*C_AIR*C_N2O5*Temp**3.5*exp(11000.0/Temp)/(1.24621148321367e-27*C_AIR*Temp**3.6*exp(-80.0/Temp) + 1.0) + 1.0e-36*0.8**(1.0/(log(4.54545454545455e-26*C_AIR*Temp**2.0)**2/log(10)**2 + 1.0))*C_AIR*C_NO2*C_O3P*Temp**2.0/(4.54545454545455e-26*C_AIR*Temp**2.0 + 1.0) - 1.4e-12*C_BALD*C_NO3*exp(-1872.0/Temp) - 4.0e-12*C_BZCO_O2*C_NO3 - 1.4e-12*C_CCHO*C_NO3*exp(-1860.0/Temp) - 4.0e-12*C_CCO_O2*C_NO3 - 1.37e-11*C_CRES*C_NO3 - 1.3e-12*C_C_O2*C_NO3 - 4.87777777777778e-18*C_ETHENE*C_NO3*Temp**2.0*exp(-2282.0/Temp) - 2.8e-12*C_GLY*C_NO3*exp(-2376.0/Temp) - 2.0e-12*C_HCHO*C_NO3*exp(-2431.0/Temp) + 1.0*C_HNO3*C_OH*(1.9e-33*C_AIR*exp(725.0/Temp)/(4.63414634146341e-18*C_AIR*exp(-715.0/Temp) + 1.0) + 7.2e-15*exp(785.0/Temp)) + 0.39*C_HNO4*J_8 - 4.0e-12*C_HO2*C_NO3 - 3.03e-12*C_ISOPRENE*C_NO3*exp(-448.0/Temp) - 1.0e-13*C_ISOPROD*C_NO3 - 4.0e-12*C_MA_RCO3*C_NO3 - 1.5e-12*C_METHACRO*C_NO3*exp(-1726.0/Temp) - 1.4e-12*C_MGLY*C_NO3*exp(-1895.0/Temp) - 1.8e-11*C_NO*C_NO3*exp(110.0/Temp) - 4.5e-14*C_NO2*C_NO3*exp(-1260.0/Temp) + 1.4e-13*C_NO2*C_O3*exp(-2470.0/Temp) - 1.7e-12*C_NO3**2*exp(-2450.0/Temp) - 3.78e-12*C_NO3*C_NPHE - 2.0e-11*C_NO3*C_OH - 4.453e-14*C_NO3*C_OLE1*exp(-376.0/Temp) - 7.265e-13*C_NO3*C_OLE2 - 3.78e-12*C_NO3*C_PHEN - 2.3e-12*C_NO3*C_R2O2 - 1.4e-12*C_NO3*C_RCHO*exp(-1771.0/Temp) - 4.0e-12*C_NO3*C_RCO_O2 - 2.3e-12*C_NO3*C_RO2_N - 2.3e-12*C_NO3*C_RO2_R - 3.66e-12*C_NO3*C_TERP*exp(175.0/Temp) - 1.0*C_NO3*J_1 - 1.0*C_NO3*J_2) + (EXPLICIT: 0)
d[N2O5]/dt = (IMPLICIT: 5.98733612492945e-39*0.45**(1.0/(log(9.56707972824405e-28*C_AIR*Temp**3.7)**2/log(10)**2 + 1.0))*C_AIR*C_NO2*C_NO3*Temp**3.5/(9.56707972824405e-28*C_AIR*Temp**3.7 + 1.0) - 2.13833433033195e-12*0.45**(1.0/(log(1.24621148321367e-27*C_AIR*Temp**3.6*exp(-80.0/Temp))**2/log(10)**2 + 1.0))*C_AIR*C_N2O5*Temp**3.5*exp(11000.0/Temp)/(1.24621148321367e-27*C_AIR*Temp**3.6*exp(-80.0/Temp) + 1.0) - 2.6e-22*C_H2O*C_N2O5) + (EXPLICIT: 0)
d[HONO]/dt = (IMPLICIT: 2.53853279130624e-37*0.6**(1.0/(log(1.24736169269364e-26*C_AIR*Temp**2.5)**2/log(10)**2 + 1.0))*C_AIR*C_NO*C_OH*Temp**2.6/(1.24736169269364e-26*C_AIR*Temp**2.5 + 1.0) - 2.7e-12*C_HONO*C_OH*exp(260.0/Temp) - 1.0*C_HONO*J_5 - 1.0*C_HONO*J_6) + (EXPLICIT: 0)
d[HNO3]/dt = (IMPLICIT: 5.08780413527122e-38*0.6**(1.0/(log(4.8502994011976e-22*C_AIR*Temp**1.0)**2/log(10)**2 + 1.0))*C_AIR*C_NO2*C_OH*Temp**3.1/(4.8502994011976e-22*C_AIR*Temp**1.0 + 1.0) + 1.4e-12*C_BALD*C_NO3*exp(-1872.0/Temp) + 1.4e-12*C_CCHO*C_NO3*exp(-1860.0/Temp) + 1.37e-11*C_CRES*C_NO3 + 2.8e-12*C_GLY*C_NO3*exp(-2376.0/Temp) + 5.2e-22*C_H2O*C_N2O5 + 2.0e-12*C_HCHO*C_NO3*exp(-2431.0/Temp) - 1.0*C_HNO3*C_OH*(1.9e-33*C_AIR*exp(725.0/Temp)/(4.63414634146341e-18*C_AIR*exp(-715.0/Temp) + 1.0) + 7.2e-15*exp(785.0/Temp)) - 1.0*C_HNO3*J_7 + 8.0e-13*C_HO2*C_NO3 + 1.5e-14*C_ISOPROD*C_NO3 + 7.5e-13*C_METHACRO*C_NO3*exp(-1726.0/Temp) + 1.4e-12*C_MGLY*C_NO3*exp(-1895.0/Temp) + 3.78e-12*C_NO3*C_NPHE + 3.78e-12*C_NO3*C_PHEN + 1.4e-12*C_NO3*C_RCHO*exp(-1771.0/Temp)) + (EXPLICIT: 0)
d[HNO4]/dt = (IMPLICIT: -4.1e-5*0.5**(1.0/(log(7.19298245614035e-21*C_AIR*exp(-520.0/Temp))**2/log(10)**2 + 1.0))*C_AIR*C_HNO4*exp(10650.0/Temp)/(7.19298245614035e-21*C_AIR*exp(-520.0/Temp) + 1.0) + 2.1305144789204e-39*0.6**(1.0/(log(4.53300952961788e-28*C_AIR*Temp**3.2)**2/log(10)**2 + 1.0))*C_AIR*C_HO2*C_NO2*Temp**3.2/(4.53300952961788e-28*C_AIR*Temp**3.2 + 1.0) - 1.5e-12*C_HNO4*C_OH*exp(360.0/Temp) - 1.0*C_HNO4*J_8) + (EXPLICIT: 0)
d[SO2]/dt = (IMPLICIT: -2.67645441385345e-39*0.45**(1.0/(log(1.33822720692672e-27*C_AIR*Temp**3.3)**2/log(10)**2 + 1.0))*C_AIR*C_OH*C_SO2*Temp**3.3/(1.33822720692672e-27*C_AIR*Temp**3.3 + 1.0)) + (EXPLICIT: 0)
d[H2SO4]/dt = (IMPLICIT: 2.67645441385345e-39*0.45**(1.0/(log(1.33822720692672e-27*C_AIR*Temp**3.3)**2/log(10)**2 + 1.0))*C_AIR*C_OH*C_SO2*Temp**3.3/(1.33822720692672e-27*C_AIR*Temp**3.3 + 1.0)) + (EXPLICIT: 0)
d[CO]/dt = (IMPLICIT: 1.5792e-12*C_ALK2*C_OH*exp(-671.0/Temp) + 1.1892e-14*C_ALK4*C_OH*exp(-91.0/Temp) + 1.0*C_CCHO*J_12 - 1.0*C_CO*C_OH*(3.19e-33*C_AIR + 1.3e-13) + 3.0e-18*C_DCB1*C_O3 + 5.0e-11*C_DCB1*C_OH + 1.0*C_DCB2*J_28 + 1.0*C_DCB3*J_29 + 4.57e-15*C_ETHENE*C_O3*exp(-2580.0/Temp) + 5.1064e-12*C_ETHENE*C_O3P*exp(-792.0/Temp) + 3.528e-12*C_GLY*C_NO3*exp(-2376.0/Temp) + 1.386e-11*C_GLY*C_OH + 2.0*C_GLY*J_18 + 1.0*C_GLY*J_19 + 2.0e-12*C_HCHO*C_NO3*exp(-2431.0/Temp) + 8.6e-12*C_HCHO*C_OH*exp(20.0/Temp) + 1.0*C_HCHO*J_10 + 1.0*C_HCHO*J_11 + 2.1615e-15*C_ISOPRENE*C_O3*exp(-1912.0/Temp) + 5.72e-14*C_ISOPROD*C_NO3 + 2.08164e-18*C_ISOPROD*C_O3 + 2.07984e-11*C_ISOPROD*C_OH + 1.233*C_ISOPROD*J_25 + 7.5e-13*C_METHACRO*C_NO3*exp(-1726.0/Temp) + 6.12e-16*C_METHACRO*C_O3*exp(-2114.0/Temp) + 7.7376e-12*C_METHACRO*C_OH*exp(176.0/Temp) + 0.67*C_METHACRO*J_23 + 1.4e-12*C_MGLY*C_NO3*exp(-1895.0/Temp) + 1.5e-11*C_MGLY*C_OH + 1.0*C_MGLY*J_20 + 3.56725e-16*C_MVK*C_O3*exp(-1520.0/Temp) + 0.7*C_MVK*J_24 + 9.02865e-16*C_O3*C_OLE1*exp(-1640.0/Temp) + 1.33083e-16*C_O3*C_OLE2*exp(-461.0/Temp) + 1.6956e-16*C_O3*C_TERP*exp(-821.0/Temp) + 2.502e-13*C_O3P*C_OLE2 + 6.8e-13*C_OH*C_RCHO + 1.0*C_RCHO*J_13) + (EXPLICIT: 0)
d[HCHO]/dt = (IMPLICIT: 1.1e-12*C_ACET*C_OH*exp(-520.0/Temp) + 3.8493e-13*C_ALK2*C_OH*exp(-671.0/Temp) + 2.6494e-13*C_ALK3*C_OH*exp(-434.0/Temp) + 1.42704e-13*C_ALK4*C_OH*exp(-91.0/Temp) + 2.8912e-13*C_ALK5*C_OH*exp(-52.0/Temp) + 1.8e-12*C_BZCO_O2*C_C_O2*exp(500.0/Temp) + 2.9e-12*C_BZCO_O2*C_MA_RCO3*exp(500.0/Temp) + 1.8e-12*C_CCO_O2*C_C_O2*exp(500.0/Temp) + 2.9e-12*C_CCO_O2*C_MA_RCO3*exp(500.0/Temp) + 1.015e-12*C_COOH*C_OH*exp(190.0/Temp) + 1.0*C_COOH*J_16 + 2.45e-14*C_C_O2**2*exp(710.0/Temp) + 1.18e-12*C_C_O2**2*exp(-509.0/Temp) + 1.8e-12*C_C_O2*C_MA_RCO3*exp(500.0/Temp) + 2.8e-12*C_C_O2*C_NO*exp(285.0/Temp) + 1.3e-12*C_C_O2*C_NO3 + 1.8e-12*C_C_O2*C_RCO_O2*exp(500.0/Temp) + 1.5e-13*C_C_O2*C_RO2_N + 1.5e-13*C_C_O2*C_RO2_R + 9.14e-15*C_ETHENE*C_O3*exp(-2580.0/Temp) + 1.9864e-12*C_ETHENE*C_O3P*exp(-792.0/Temp) + 3.1556e-12*C_ETHENE*C_OH*exp(438.0/Temp) + 1.0*C_GLY*J_19 - 9.7e-15*C_HCHO*C_HO2*exp(625.0/Temp) - 2.0e-12*C_HCHO*C_NO3*exp(-2431.0/Temp) - 8.6e-12*C_HCHO*C_OH*exp(20.0/Temp) - 1.0*C_HCHO*J_10 - 1.0*C_HCHO*J_11 + 2400000000000.0*C_HOCOO*exp(-7000.0/Temp) + 4.65312e-15*C_ISOPRENE*C_O3*exp(-1912.0/Temp) + 8.64e-12*C_ISOPRENE*C_O3P + 1.56e-11*C_ISOPRENE*C_OH*exp(408.0/Temp) + 2.27e-14*C_ISOPROD*C_NO3 + 5.225e-19*C_ISOPROD*C_O3 + 3.4045e-12*C_ISOPROD*C_OH + 0.3*C_ISOPROD*J_25 + 5.8e-12*C_MA_RCO3**2*exp(500.0/Temp) + 1.25e-11*C_MA_RCO3*C_NO*exp(240.0/Temp) + 4.0e-12*C_MA_RCO3*C_NO3 + 2.9e-12*C_MA_RCO3*C_RCO_O2*exp(500.0/Temp) + 1.66111111111111e-18*C_MEK*C_OH*Temp**2.0*exp(-25.0/Temp) + 3.44444444444444e-17*C_MEOH*C_OH*Temp**2.0*exp(-360.0/Temp) + 2.72e-16*C_METHACRO*C_O3*exp(-2114.0/Temp) + 1.5624e-12*C_METHACRO*C_OH*exp(176.0/Temp) + 0.67*C_METHACRO*J_23 + 7.51e-17*C_MVK*C_O3*exp(-1520.0/Temp) + 1.242e-12*C_MVK*C_OH*exp(453.0/Temp) + 5.73935e-14*C_NO3*C_OLE2 + 1.3085e-15*C_O3*C_OLE1*exp(-1640.0/Temp) + 1.350918e-16*C_O3*C_OLE2*exp(-461.0/Temp) + 2.538e-16*C_O3*C_TERP*exp(-821.0/Temp) + 5.19354e-12*C_OH*C_OLE1*exp(451.0/Temp) + 4.25292e-12*C_OH*C_OLE2*exp(384.0/Temp) + 3.195e-12*C_OH*C_PROD2 + 7.8e-14*C_OH*C_RNO3 + 5.0508e-12*C_OH*C_TERP*exp(449.0/Temp) + 0.506*C_PROD2*J_26 + 0.134*C_RNO3*J_27) + (EXPLICIT: 0)
d[CCHO]/dt = (IMPLICIT: 1.52222222222222e-17*C_ALK1*C_OH*Temp**2.0*exp(-498.0/Temp) + 4.53455e-12*C_ALK3*C_OH*exp(-434.0/Temp) + 2.70543e-12*C_ALK4*C_OH*exp(-91.0/Temp) + 1.10088e-12*C_ALK5*C_OH*exp(-52.0/Temp) + 2.9e-12*C_BZCO_O2*C_RCO_O2*exp(500.0/Temp) - 1.4e-12*C_CCHO*C_NO3*exp(-1860.0/Temp) - 5.6e-12*C_CCHO*C_OH*exp(310.0/Temp) - 1.0*C_CCHO*J_12 + 2.9e-12*C_CCO_O2*C_RCO_O2*exp(500.0/Temp) + 2.6e-12*C_ETHENE*C_O3P*exp(-792.0/Temp) + 3.822e-13*C_ETHENE*C_OH*exp(438.0/Temp) + 1.9646e-19*C_ISOPROD*C_O3 + 7.9851e-12*C_ISOPROD*C_OH + 0.467*C_ISOPROD*J_25 + 2.9e-12*C_MA_RCO3*C_RCO_O2*exp(500.0/Temp) + 6.96222222222222e-18*C_MEK*C_OH*Temp**2.0*exp(-25.0/Temp) + 1.0*C_MEK*J_15 + 1.25e-11*C_NO*C_RCO_O2*exp(240.0/Temp) + 4.0077e-16*C_NO3*C_OLE1*exp(-376.0/Temp) + 3.683355e-13*C_NO3*C_OLE2 + 4.0e-12*C_NO3*C_RCO_O2 + 4.03018e-16*C_O3*C_OLE1*exp(-1640.0/Temp) + 2.290032e-16*C_O3*C_OLE2*exp(-461.0/Temp) + 2.08593e-12*C_OH*C_OLE1*exp(451.0/Temp) + 1.275876e-11*C_OH*C_OLE2*exp(384.0/Temp) + 1.26e-12*C_OH*C_PROD2 + 6.8e-13*C_OH*C_RCHO + 3.4242e-12*C_OH*C_RNO3 + 0.246*C_PROD2*J_26 + 1.0*C_RCHO*J_13 + 5.8e-12*C_RCO_O2**2*exp(500.0/Temp) + 0.431*C_RNO3*J_27) + (EXPLICIT: 0)
d[RCHO]/dt = (IMPLICIT: 1.52985e-12*C_ALK2*C_OH*exp(-671.0/Temp) + 1.24318e-12*C_ALK3*C_OH*exp(-434.0/Temp) + 1.450824e-12*C_ALK4*C_OH*exp(-91.0/Temp) + 2.26848e-12*C_ALK5*C_OH*exp(-52.0/Temp) + 5.0e-11*C_DCB1*C_OH + 5.0e-11*C_DCB2*C_OH + 5.0e-11*C_DCB3*C_OH + 4.87777777777778e-18*C_ETHENE*C_NO3*Temp**2.0*exp(-2282.0/Temp) + 2.18e-14*C_ISOPROD*C_NO3 + 8.047e-13*C_ISOPROD*C_OH + 5.34444444444444e-18*C_MEK*C_OH*Temp**2.0*exp(-25.0/Temp) + 6.34e-12*C_METHACRO*C_O3P + 1.944e-12*C_MVK*C_O3P + 2.7945e-12*C_MVK*C_OH*exp(453.0/Temp) + 1.64761e-15*C_NO3*C_OLE1*exp(-376.0/Temp) + 1.097015e-13*C_NO3*C_OLE2 - 1.4e-12*C_NO3*C_RCHO*exp(-1771.0/Temp) + 1.73484e-12*C_NO3*C_TERP*exp(175.0/Temp) + 9.49971e-16*C_O3*C_OLE1*exp(-1640.0/Temp) + 1.53171e-16*C_O3*C_OLE2*exp(-461.0/Temp) + 2.214e-16*C_O3*C_TERP*exp(-821.0/Temp) + 4.833e-12*C_O3P*C_OLE1*exp(-234.0/Temp) + 1.43865e-12*C_O3P*C_OLE2 + 4.8069e-12*C_O3P*C_TERP + 3.526215e-12*C_OH*C_OLE1*exp(451.0/Temp) + 8.90673e-12*C_OH*C_OLE2*exp(384.0/Temp) + 8.37e-12*C_OH*C_PROD2 - 2.0e-11*C_OH*C_RCHO + 1.6614e-12*C_OH*C_RNO3 + 1.1e-11*C_OH*C_ROOH + 8.6742e-12*C_OH*C_TERP*exp(449.0/Temp) + 0.71*C_PROD2*J_26 - 1.0*C_RCHO*J_13 + 0.147*C_RNO3*J_27 + 1.0*C_ROOH*J_17) + (EXPLICIT: 0)
d[ACET]/dt = (IMPLICIT: -1.1e-12*C_ACET*C_OH*exp(-520.0/Temp) - 1.0*C_ACET*J_14 + 4.11579e-12*C_ALK2*C_OH*exp(-671.0/Temp) + 2.4456e-13*C_ALK3*C_OH*exp(-434.0/Temp) + 2.687592e-12*C_ALK4*C_OH*exp(-91.0/Temp) + 8.0064e-13*C_ALK5*C_OH*exp(-52.0/Temp) + 1.06872e-15*C_NO3*C_OLE1*exp(-376.0/Temp) + 7.4103e-14*C_NO3*C_OLE2 + 2.617e-18*C_O3*C_OLE1*exp(-1640.0/Temp) + 2.2599e-17*C_O3*C_OLE2*exp(-461.0/Temp) + 1.404e-16*C_O3*C_TERP*exp(-821.0/Temp) + 3.5475e-14*C_OH*C_OLE1*exp(451.0/Temp) + 2.21361e-12*C_OH*C_OLE2*exp(384.0/Temp) + 4.68e-14*C_OH*C_RNO3 + 0.02*C_RNO3*J_27 + 750000000000000.0*C_TBU_O*exp(-8152.0/Temp)) + (EXPLICIT: 0)
d[MEK]/dt = (IMPLICIT: 3.38308e-12*C_ALK3*C_OH*exp(-434.0/Temp) + 6.5406e-13*C_ALK4*C_OH*exp(-91.0/Temp) + 9.8968e-13*C_ALK5*C_OH*exp(-52.0/Temp) + 1.0e-13*C_C_O2*C_RO2_N + 8.778e-19*C_ISOPROD*C_O3 + 9.285e-12*C_ISOPROD*C_OH + 0.233*C_ISOPROD*J_25 - 1.44444444444444e-17*C_MEK*C_OH*Temp**2.0*exp(-25.0/Temp) - 1.0*C_MEK*J_15 + 7.7376e-12*C_METHACRO*C_OH*exp(176.0/Temp) + 2.376e-12*C_MVK*C_O3P + 7.265e-16*C_NO3*C_OLE2 + 2.3e-12*C_NO3*C_RO2_N + 1.30572e-17*C_O3*C_OLE2*exp(-461.0/Temp) + 4.69338e-12*C_O3P*C_OLE1*exp(-234.0/Temp) + 1.374015e-11*C_O3P*C_OLE2 + 1.25496e-12*C_OH*C_OLE2*exp(384.0/Temp) + 1.725e-12*C_OH*C_PROD2 + 1.3806e-12*C_OH*C_RNO3 + 0.243*C_RNO3*J_27 + 3.5e-14*C_RO2_N**2 + 1.75e-14*C_RO2_N*C_RO2_R) + (EXPLICIT: 0)
d[HCOOH]/dt = (IMPLICIT: 1.19427e-12*C_ALK2*C_OH*exp(-671.0/Temp) + 3.3818e-15*C_ETHENE*C_O3*exp(-2580.0/Temp) + 2.8e-12*C_HOCOO*C_NO*exp(285.0/Temp) + 1.60344e-15*C_ISOPRENE*C_O3*exp(-1912.0/Temp) + 4.18e-19*C_ISOPROD*C_O3 + 4.5288e-16*C_METHACRO*C_O3*exp(-2114.0/Temp) + 2.63601e-16*C_MVK*C_O3*exp(-1520.0/Temp) + 4.84145e-16*C_O3*C_OLE1*exp(-1640.0/Temp) + 3.66606e-17*C_O3*C_OLE2*exp(-461.0/Temp) + 1.1124e-16*C_O3*C_TERP*exp(-821.0/Temp)) + (EXPLICIT: 0)
d[MEOH]/dt = (IMPLICIT: 2.45e-14*C_C_O2**2*exp(710.0/Temp) + 5.0e-14*C_C_O2*C_RO2_N + 5.0e-14*C_C_O2*C_RO2_R - 3.44444444444444e-17*C_MEOH*C_OH*Temp**2.0*exp(-360.0/Temp)) + (EXPLICIT: 0)
d[CCO_OH]/dt = (IMPLICIT: 1.8e-12*C_CCO_O2*C_C_O2*exp(500.0/Temp) + 1.075e-13*C_CCO_O2*C_HO2*exp(1040.0/Temp) + 7.5e-12*C_CCO_O2*C_RO2_N + 7.5e-12*C_CCO_O2*C_RO2_R + 1.3085e-16*C_O3*C_OLE1*exp(-1640.0/Temp) + 6.47838e-17*C_O3*C_OLE2*exp(-461.0/Temp)) + (EXPLICIT: 0)
d[RCO_OH]/dt = (IMPLICIT: 1.8e-12*C_BZCO_O2*C_C_O2*exp(500.0/Temp) + 1.075e-13*C_BZCO_O2*C_HO2*exp(1040.0/Temp) + 7.5e-12*C_BZCO_O2*C_RO2_N + 7.5e-12*C_BZCO_O2*C_RO2_R + 1.8e-12*C_C_O2*C_MA_RCO3*exp(500.0/Temp) + 1.8e-12*C_C_O2*C_RCO_O2*exp(500.0/Temp) + 1.075e-13*C_HO2*C_MA_RCO3*exp(1040.0/Temp) + 1.075e-13*C_HO2*C_RCO_O2*exp(1040.0/Temp) + 1.179e-15*C_ISOPRENE*C_O3*exp(-1912.0/Temp) + 1.55496e-18*C_ISOPROD*C_O3 + 1.5e-11*C_MA_RCO3*C_RO2_N + 7.5e-12*C_MA_RCO3*C_RO2_R + 3.11423e-16*C_O3*C_OLE1*exp(-1640.0/Temp) + 1.240434e-16*C_O3*C_OLE2*exp(-461.0/Temp) + 2.0412e-16*C_O3*C_TERP*exp(-821.0/Temp) + 7.5e-12*C_RCO_O2*C_RO2_N + 7.5e-12*C_RCO_O2*C_RO2_R) + (EXPLICIT: 0)
d[GLY]/dt = (IMPLICIT: 2.44776e-12*C_ALK2*C_OH*exp(-671.0/Temp) + 2.1358e-13*C_ARO1*C_OH*exp(355.0/Temp) + 2.5608e-12*C_ARO2*C_OH + 2.0e-18*C_DCB1*C_O3 + 0.5*C_DCB2*J_28 + 0.5*C_DCB3*J_29 + 9.36e-14*C_ETHENE*C_O3P*exp(-792.0/Temp) - 2.8e-12*C_GLY*C_NO3*exp(-2376.0/Temp) - 1.1e-11*C_GLY*C_OH - 1.0*C_GLY*J_18 - 1.0*C_GLY*J_19 + 9.614e-20*C_ISOPROD*C_O3 + 9.285e-12*C_ISOPROD*C_OH + 1.08e-18*C_O3*C_TERP*exp(-821.0/Temp) + 6.049e-12*C_OH*C_PHEN) + (EXPLICIT: 0)
d[MGLY]/dt = (IMPLICIT: 2.1539e-13*C_ARO1*C_OH*exp(355.0/Temp) + 7.5768e-12*C_ARO2*C_OH + 9.66e-12*C_CRES*C_OH + 0.5*C_DCB2*J_28 + 0.5*C_DCB3*J_29 + 8.0e-16*C_ISOPROD*C_NO3 + 3.10156e-18*C_ISOPROD*C_O3 + 1.07706e-11*C_ISOPROD*C_OH + 1.224e-15*C_METHACRO*C_O3*exp(-2114.0/Temp) + 1.5624e-12*C_METHACRO*C_OH*exp(176.0/Temp) - 1.4e-12*C_MGLY*C_NO3*exp(-1895.0/Temp) - 1.5e-11*C_MGLY*C_OH - 1.0*C_MGLY*J_20 + 7.1345e-16*C_MVK*C_O3*exp(-1520.0/Temp) + 1.242e-12*C_MVK*C_OH*exp(453.0/Temp)) + (EXPLICIT: 0)
d[BACL]/dt = (IMPLICIT: 2.2968e-12*C_ARO2*C_OH - 1.0*C_BACL*J_21 + 3.348e-17*C_O3*C_TERP*exp(-821.0/Temp)) + (EXPLICIT: 0)
d[CRES]/dt = (IMPLICIT: 3.7467e-13*C_ARO1*C_OH*exp(355.0/Temp) + 4.9368e-12*C_ARO2*C_OH - 1.37e-11*C_CRES*C_NO3 - 4.2e-11*C_CRES*C_OH) + (EXPLICIT: 0)
d[BALD]/dt = (IMPLICIT: 1.0679e-13*C_ARO1*C_OH*exp(355.0/Temp) + 1.32e-12*C_ARO2*C_OH - 1.4e-12*C_BALD*C_NO3*exp(-1872.0/Temp) - 1.29e-11*C_BALD*C_OH + 1.08975e-14*C_NO3*C_OLE2 + 2.10924e-17*C_O3*C_OLE2*exp(-461.0/Temp) + 1.06323e-12*C_OH*C_OLE2*exp(384.0/Temp)) + (EXPLICIT: -1.0*C_BALD*J_22)
d[ISOPROD]/dt = (IMPLICIT: 2.83608e-12*C_ISOPRENE*C_NO3*exp(-448.0/Temp) + 8.925e-12*C_ISOPRENE*C_OH*exp(408.0/Temp) - 1.0e-13*C_ISOPROD*C_NO3 - 4.18e-18*C_ISOPROD*C_O3 - 6.19e-11*C_ISOPROD*C_OH - 1.0*C_ISOPROD*J_25 + 4.3575e-13*C_OH*C_OLE2*exp(384.0/Temp)) + (EXPLICIT: 0)
d[METHACRO]/dt = (IMPLICIT: 3.0654e-15*C_ISOPRENE*C_O3*exp(-1912.0/Temp) + 5.75e-12*C_ISOPRENE*C_OH*exp(408.0/Temp) - 1.5e-12*C_METHACRO*C_NO3*exp(-1726.0/Temp) - 1.36e-15*C_METHACRO*C_O3*exp(-2114.0/Temp) - 6.34e-12*C_METHACRO*C_O3P - 1.86e-11*C_METHACRO*C_OH*exp(176.0/Temp) - 1.0*C_METHACRO*J_23 + 1.30572e-17*C_O3*C_OLE2*exp(-461.0/Temp) + 2.502e-13*C_O3P*C_OLE2 + 4.3575e-13*C_OH*C_OLE2*exp(384.0/Temp)) + (EXPLICIT: 0)
d[MVK]/dt = (IMPLICIT: 1.2576e-15*C_ISOPRENE*C_O3*exp(-1912.0/Temp) + 8.0e-12*C_ISOPRENE*C_OH*exp(408.0/Temp) - 7.51e-16*C_MVK*C_O3*exp(-1520.0/Temp) - 4.32e-12*C_MVK*C_O3P - 4.14e-12*C_MVK*C_OH*exp(453.0/Temp) - 1.0*C_MVK*J_24 + 3.4872e-14*C_NO3*C_OLE2 + 9.5418e-18*C_O3*C_OLE2*exp(-461.0/Temp)) + (EXPLICIT: 0)
d[PROD2]/dt = (IMPLICIT: 7.4325e-13*C_ALK4*C_OH*exp(-91.0/Temp) + 4.63704e-12*C_ALK5*C_OH*exp(-52.0/Temp) + 9.955e-14*C_ARO1*C_OH*exp(355.0/Temp) + 7.5e-12*C_BZCO_O2*C_RO2_N + 7.5e-12*C_CCO_O2*C_RO2_N + 1.0e-13*C_C_O2*C_RO2_N + 7.86e-16*C_ISOPRENE*C_O3*exp(-1912.0/Temp) + 2.7e-11*C_ISOPRENE*C_O3P + 2.05508e-11*C_ISOPROD*C_OH + 0.7*C_MVK*J_24 + 5.62655e-16*C_O3*C_OLE1*exp(-1640.0/Temp) + 2.15946e-17*C_O3*C_OLE2*exp(-461.0/Temp) + 2.9808e-16*C_O3*C_TERP*exp(-821.0/Temp) + 1.21362e-12*C_O3P*C_OLE1*exp(-234.0/Temp) + 5.40015e-12*C_O3P*C_OLE2 + 2.78931e-11*C_O3P*C_TERP + 8.44305e-13*C_OH*C_OLE1*exp(451.0/Temp) - 1.0065e-11*C_OH*C_PROD2 + 3.744e-13*C_OH*C_RNO3 + 5.0508e-12*C_OH*C_TERP*exp(449.0/Temp) - 1.0*C_PROD2*J_26 + 7.5e-12*C_RCO_O2*C_RO2_N + 0.435*C_RNO3*J_27 + 3.5e-14*C_RO2_N**2 + 1.75e-14*C_RO2_N*C_RO2_R) + (EXPLICIT: 0)
d[DCB1]/dt = (IMPLICIT: 8.8871e-13*C_ARO1*C_OH*exp(355.0/Temp) + 1.48104e-11*C_ARO2*C_OH - 2.0e-18*C_DCB1*C_O3 - 5.0e-11*C_DCB1*C_OH) + (EXPLICIT: 0)
d[DCB2]/dt = (IMPLICIT: 1.9548e-13*C_ARO1*C_OH*exp(355.0/Temp) + 2.6136e-12*C_ARO2*C_OH - 5.0e-11*C_DCB2*C_OH - 1.0*C_DCB2*J_28) + (EXPLICIT: 0)
d[DCB3]/dt = (IMPLICIT: 9.231e-14*C_ARO1*C_OH*exp(355.0/Temp) + 2.4552e-12*C_ARO2*C_OH - 5.0e-11*C_DCB3*C_OH - 1.0*C_DCB3*J_29) + (EXPLICIT: 0)
d[ETHENE]/dt = (IMPLICIT: -4.87777777777778e-18*C_ETHENE*C_NO3*Temp**2.0*exp(-2282.0/Temp) - 9.14e-15*C_ETHENE*C_O3*exp(-2580.0/Temp) - 1.04e-11*C_ETHENE*C_O3P*exp(-792.0/Temp) - 1.96e-12*C_ETHENE*C_OH*exp(438.0/Temp)) + (EXPLICIT: 0)
d[ISOPRENE]/dt = (IMPLICIT: -3.03e-12*C_ISOPRENE*C_NO3*exp(-448.0/Temp) - 7.86e-15*C_ISOPRENE*C_O3*exp(-1912.0/Temp) - 3.6e-11*C_ISOPRENE*C_O3P - 2.5e-11*C_ISOPRENE*C_OH*exp(408.0/Temp)) + (EXPLICIT: 0)
d[ALK1]/dt = (IMPLICIT: -1.52222222222222e-17*C_ALK1*C_OH*Temp**2.0*exp(-498.0/Temp)) + (EXPLICIT: 0)
d[ALK2]/dt = (IMPLICIT: -9.87e-12*C_ALK2*C_OH*exp(-671.0/Temp)) + (EXPLICIT: 0)
d[ALK3]/dt = (IMPLICIT: -1.019e-11*C_ALK3*C_OH*exp(-434.0/Temp)) + (EXPLICIT: 0)
d[ALK4]/dt = (IMPLICIT: -5.946e-12*C_ALK4*C_OH*exp(-91.0/Temp)) + (EXPLICIT: 0)
d[ALK5]/dt = (IMPLICIT: -1.112e-11*C_ALK5*C_OH*exp(-52.0/Temp)) + (EXPLICIT: 0)
d[ARO1]/dt = (IMPLICIT: -1.81e-12*C_ARO1*C_OH*exp(355.0/Temp)) + (EXPLICIT: 0)
d[ARO2]/dt = (IMPLICIT: -2.64e-11*C_ARO2*C_OH) + (EXPLICIT: 0)
d[OLE1]/dt = (IMPLICIT: -4.453e-14*C_NO3*C_OLE1*exp(-376.0/Temp) - 2.617e-15*C_O3*C_OLE1*exp(-1640.0/Temp) - 1.074e-11*C_O3P*C_OLE1*exp(-234.0/Temp) - 7.095e-12*C_OH*C_OLE1*exp(451.0/Temp)) + (EXPLICIT: 0)
d[OLE2]/dt = (IMPLICIT: -7.265e-13*C_NO3*C_OLE2 - 5.022e-16*C_O3*C_OLE2*exp(-461.0/Temp) - 2.085e-11*C_O3P*C_OLE2 - 1.743e-11*C_OH*C_OLE2*exp(384.0/Temp)) + (EXPLICIT: 0)
d[TERP]/dt = (IMPLICIT: -3.66e-12*C_NO3*C_TERP*exp(175.0/Temp) - 1.08e-15*C_O3*C_TERP*exp(-821.0/Temp) - 3.27e-11*C_O3P*C_TERP - 1.83e-11*C_OH*C_TERP*exp(449.0/Temp)) + (EXPLICIT: 0)
d[RNO3]/dt = (IMPLICIT: 5.72e-14*C_ISOPROD*C_NO3 + 2.7e-12*C_NO*C_RO2_N*exp(360.0/Temp) + 2.4e-11*C_NO2*C_TBU_O + 2.275483e-14*C_NO3*C_OLE1*exp(-376.0/Temp) + 2.332065e-13*C_NO3*C_OLE2 + 1.01016e-12*C_NO3*C_TERP*exp(175.0/Temp) - 5.382e-12*C_OH*C_RNO3 - 1.0*C_RNO3*J_27) + (EXPLICIT: 0)
d[NPHE]/dt = (IMPLICIT: 2.3e-11*C_BZNO2_O*C_HO2*exp(150.0/Temp) + 1.9e-13*C_BZNO2_O*exp(1300.0/Temp) + 2.3e-11*C_BZ_O*C_NO2*exp(150.0/Temp) - 3.78e-12*C_NO3*C_NPHE) + (EXPLICIT: 0)
d[PHEN]/dt = (IMPLICIT: 3.077e-14*C_ARO1*C_OH*exp(355.0/Temp) + 1.9e-13*C_BZ_O*C_HO2*exp(1300.0/Temp) + 0.001*C_BZ_O - 3.78e-12*C_NO3*C_PHEN - 2.63e-11*C_OH*C_PHEN) + (EXPLICIT: 0)
d[PAN]/dt = (IMPLICIT: 6.97915519241595e-46*0.3**(1.0/(log(9.86349295796486e-33*C_AIR*Temp**6.2)**2/log(10)**2 + 1.0))*C_AIR*C_CCO_O2*C_NO2*Temp**7.1/(9.86349295796486e-33*C_AIR*Temp**6.2 + 1.0) - 0.0049*0.3**(1.0/(log(1.225e-19*C_AIR*exp(-1500.0/Temp)/(Temp/300)**0.0.)**2/log(10)**2 + 1.0))*C_AIR*C_PAN*exp(12100.0/Temp)/(1.225e-19*C_AIR*exp(-1500.0/Temp)/(Temp/300)**0.0. + 1.0)) + (EXPLICIT: 0)
d[PAN2]/dt = (IMPLICIT: 2.03512165410849e-9*C_NO2*C_RCO_O2/Temp**0.9 - 2.0e+15*C_PAN2*exp(-12800.0/Temp)) + (EXPLICIT: 0)
d[PBZN]/dt = (IMPLICIT: 1.37e-11*C_BZCO_O2*C_NO2 - 7.9e+16*C_PBZN*exp(-14000.0/Temp)) + (EXPLICIT: 0)
d[MA_PAN]/dt = (IMPLICIT: -1.6e+16*C_MA_PAN*exp(-13486.0/Temp) + 2.03512165410849e-9*C_MA_RCO3*C_NO2/Temp**0.9) + (EXPLICIT: 0)
d[CCO_OOH]/dt = (IMPLICIT: 3.225e-13*C_CCO_O2*C_HO2*exp(1040.0/Temp)) + (EXPLICIT: 0)
d[RCO_O2]/dt = (IMPLICIT: -2.9e-12*C_BZCO_O2*C_RCO_O2*exp(500.0/Temp) - 2.9e-12*C_CCO_O2*C_RCO_O2*exp(500.0/Temp) - 1.8e-12*C_C_O2*C_RCO_O2*exp(500.0/Temp) + 1.036e-12*C_GLY*C_NO3*exp(-2376.0/Temp) + 4.07e-12*C_GLY*C_OH - 4.3e-13*C_HO2*C_RCO_O2*exp(1040.0/Temp) + 2.0064e-19*C_ISOPROD*C_O3 + 0.3*C_ISOPROD*J_25 - 2.9e-12*C_MA_RCO3*C_RCO_O2*exp(500.0/Temp) + 1.38666666666667e-18*C_MEK*C_OH*Temp**2.0*exp(-25.0/Temp) + 1.36e-16*C_METHACRO*C_O3*exp(-2114.0/Temp) + 3.755e-17*C_MVK*C_O3*exp(-1520.0/Temp) - 1.25e-11*C_NO*C_RCO_O2*exp(240.0/Temp) - 2.03512165410849e-9*C_NO2*C_RCO_O2/Temp**0.9 + 1.4e-12*C_NO3*C_RCHO*exp(-1771.0/Temp) - 4.0e-12*C_NO3*C_RCO_O2 + 3.0132e-18*C_O3*C_OLE2*exp(-461.0/Temp) + 2.1708e-16*C_O3*C_TERP*exp(-821.0/Temp) + 7.35e-13*C_OH*C_PROD2 + 1.93e-11*C_OH*C_RCHO + 2.0e+15*C_PAN2*exp(-12800.0/Temp) + 0.333*C_PROD2*J_26 - 5.8e-12*C_RCO_O2**2*exp(500.0/Temp) - 7.5e-12*C_RCO_O2*C_RO2_N - 7.5e-12*C_RCO_O2*C_RO2_R) + (EXPLICIT: 0)
d[RCO_OOH]/dt = (IMPLICIT: 3.225e-13*C_BZCO_O2*C_HO2*exp(1040.0/Temp) + 3.225e-13*C_HO2*C_MA_RCO3*exp(1040.0/Temp) + 3.225e-13*C_HO2*C_RCO_O2*exp(1040.0/Temp)) + (EXPLICIT: 0)
d[XN]/dt = (IMPLICIT: 1.5e+15*C_BZNO2_O*C_NO2*exp(-8152.0/Temp)) + (EXPLICIT: 0)
d[XC]/dt = (IMPLICIT: 4.5e+15*C_BZNO2_O*C_NO2*exp(-8152.0/Temp)) + (EXPLICIT: 7.0*C_BALD*J_22)
d[O3P]/dt = (IMPLICIT: -1.0e-36*0.8**(1.0/(log(4.54545454545455e-26*C_AIR*Temp**2.0)**2/log(10)**2 + 1.0))*C_AIR*C_NO2*C_O3P*Temp**2.0/(4.54545454545455e-26*C_AIR*Temp**2.0 + 1.0) - 9.19166118840122e-28*C_AIR*C_NO*C_O3P/Temp**1.6 + 2.09e-11*C_AIR*C_O1D*exp(95.0/Temp) - 4.9010355073085e-27*C_AIR*C_O2*C_O3P/Temp**2.8 - 1.04e-11*C_ETHENE*C_O3P*exp(-792.0/Temp) - 3.6e-11*C_ISOPRENE*C_O3P - 6.34e-12*C_METHACRO*C_O3P - 4.32e-12*C_MVK*C_O3P - 6.5e-12*C_NO2*C_O3P*exp(120.0/Temp) + 1.0*C_NO2*J_0 + 1.0*C_NO3*J_2 - 8.0e-12*C_O3*C_O3P*exp(-2060.0/Temp) + 1.0*C_O3*J_3 - 1.074e-11*C_O3P*C_OLE1*exp(-234.0/Temp) - 2.085e-11*C_O3P*C_OLE2 - 3.27e-11*C_O3P*C_TERP) + (EXPLICIT: 0)
d[O1D]/dt = (IMPLICIT: -2.09e-11*C_AIR*C_O1D*exp(95.0/Temp) - 2.2e-10*C_H2O*C_O1D + 1.0*C_O3*J_4) + (EXPLICIT: 0)
d[OH]/dt = (IMPLICIT: -2.67645441385345e-39*0.45**(1.0/(log(1.33822720692672e-27*C_AIR*Temp**3.3)**2/log(10)**2 + 1.0))*C_AIR*C_OH*C_SO2*Temp**3.3/(1.33822720692672e-27*C_AIR*Temp**3.3 + 1.0) - 5.08780413527122e-38*0.6**(1.0/(log(4.8502994011976e-22*C_AIR*Temp**1.0)**2/log(10)**2 + 1.0))*C_AIR*C_NO2*C_OH*Temp**3.1/(4.8502994011976e-22*C_AIR*Temp**1.0 + 1.0) - 2.53853279130624e-37*0.6**(1.0/(log(1.24736169269364e-26*C_AIR*Temp**2.5)**2/log(10)**2 + 1.0))*C_AIR*C_NO*C_OH*Temp**2.6/(1.24736169269364e-26*C_AIR*Temp**2.5 + 1.0) - 1.1e-12*C_ACET*C_OH*exp(-520.0/Temp) - 1.52222222222222e-17*C_ALK1*C_OH*Temp**2.0*exp(-498.0/Temp) - 7.44198e-12*C_ALK2*C_OH*exp(-671.0/Temp) - 1.019e-11*C_ALK3*C_OH*exp(-434.0/Temp) - 5.946e-12*C_ALK4*C_OH*exp(-91.0/Temp) - 1.112e-11*C_ALK5*C_OH*exp(-52.0/Temp) - 1.81e-12*C_ARO1*C_OH*exp(355.0/Temp) - 2.64e-11*C_ARO2*C_OH - 1.29e-11*C_BALD*C_OH - 5.6e-12*C_CCHO*C_OH*exp(310.0/Temp) - 2.15e-12*C_CH4*C_OH*exp(-1735.0/Temp) - 1.0*C_CO*C_OH*(3.19e-33*C_AIR + 1.3e-13) - 1.885e-12*C_COOH*C_OH*exp(190.0/Temp) + 1.0*C_COOH*J_16 - 4.2e-11*C_CRES*C_OH + 1.0e-18*C_DCB1*C_O3 - 5.0e-11*C_DCB1*C_OH - 5.0e-11*C_DCB2*C_OH - 5.0e-11*C_DCB3*C_OH + 1.0968e-15*C_ETHENE*C_O3*exp(-2580.0/Temp) - 1.96e-12*C_ETHENE*C_OH*exp(438.0/Temp) - 1.1e-11*C_GLY*C_OH - 7.7e-12*C_H2*C_OH*exp(-2100.0/Temp) + 4.4e-10*C_H2O*C_O1D - 2.9e-12*C_H2O2*C_OH*exp(-160.0/Temp) + 2.0*C_H2O2*J_9 - 8.6e-12*C_HCHO*C_OH*exp(20.0/Temp) - 1.0*C_HNO3*C_OH*(1.9e-33*C_AIR*exp(725.0/Temp)/(4.63414634146341e-18*C_AIR*exp(-715.0/Temp) + 1.0) + 7.2e-15*exp(785.0/Temp)) + 1.0*C_HNO3*J_7 - 1.5e-12*C_HNO4*C_OH*exp(360.0/Temp) + 0.39*C_HNO4*J_8 + 3.4e-12*C_HO2*C_NO*exp(270.0/Temp) + 3.2e-12*C_HO2*C_NO3 + 1.4e-14*C_HO2*C_O3*exp(-600.0/Temp) - 4.8e-11*C_HO2*C_OH*exp(250.0/Temp) - 2.7e-12*C_HONO*C_OH*exp(260.0/Temp) + 1.0*C_HONO*J_5 + 2.09076e-15*C_ISOPRENE*C_O3*exp(-1912.0/Temp) - 2.5e-11*C_ISOPRENE*C_OH*exp(408.0/Temp) + 1.1913e-18*C_ISOPROD*C_O3 - 6.19e-11*C_ISOPROD*C_OH - 1.44444444444444e-17*C_MEK*C_OH*Temp**2.0*exp(-25.0/Temp) - 3.44444444444444e-17*C_MEOH*C_OH*Temp**2.0*exp(-360.0/Temp) + 2.8288e-16*C_METHACRO*C_O3*exp(-2114.0/Temp) - 1.86e-11*C_METHACRO*C_OH*exp(176.0/Temp) + 0.33*C_METHACRO*J_23 - 1.5e-11*C_MGLY*C_OH + 1.23164e-16*C_MVK*C_O3*exp(-1520.0/Temp) - 4.14e-12*C_MVK*C_OH*exp(453.0/Temp) - 2.0e-11*C_NO3*C_OH - 1.9e-12*C_O3*C_OH*exp(-1000.0/Temp) + 4.05635e-16*C_O3*C_OLE1*exp(-1640.0/Temp) + 1.898316e-16*C_O3*C_OLE2*exp(-461.0/Temp) + 6.1236e-16*C_O3*C_TERP*exp(-821.0/Temp) - 7.095e-12*C_OH*C_OLE1*exp(451.0/Temp) - 1.743e-11*C_OH*C_OLE2*exp(384.0/Temp) - 2.63e-11*C_OH*C_PHEN - 1.5e-11*C_OH*C_PROD2 - 2.0e-11*C_OH*C_RCHO - 7.8e-12*C_OH*C_RNO3 - 3.74e-12*C_OH*C_ROOH - 1.83e-11*C_OH*C_TERP*exp(449.0/Temp) + 1.0*C_ROOH*J_17) + (EXPLICIT: 0)
d[HO2]/dt = (IMPLICIT: 2.67645441385345e-39*0.45**(1.0/(log(1.33822720692672e-27*C_AIR*Temp**3.3)**2/log(10)**2 + 1.0))*C_AIR*C_OH*C_SO2*Temp**3.3/(1.33822720692672e-27*C_AIR*Temp**3.3 + 1.0) + 4.1e-5*0.5**(1.0/(log(7.19298245614035e-21*C_AIR*exp(-520.0/Temp))**2/log(10)**2 + 1.0))*C_AIR*C_HNO4*exp(10650.0/Temp)/(7.19298245614035e-21*C_AIR*exp(-520.0/Temp) + 1.0) - 2.1305144789204e-39*0.6**(1.0/(log(4.53300952961788e-28*C_AIR*Temp**3.2)**2/log(10)**2 + 1.0))*C_AIR*C_HO2*C_NO2*Temp**3.2/(4.53300952961788e-28*C_AIR*Temp**3.2 + 1.0) + 1.19427e-12*C_ALK2*C_OH*exp(-671.0/Temp) + 4.0544e-13*C_ARO1*C_OH*exp(355.0/Temp) + 4.9368e-12*C_ARO2*C_OH - 4.3e-13*C_BZCO_O2*C_HO2*exp(1040.0/Temp) - 2.3e-11*C_BZNO2_O*C_HO2*exp(150.0/Temp) - 1.9e-13*C_BZ_O*C_HO2*exp(1300.0/Temp) + 1.0*C_CCHO*J_12 - 4.3e-13*C_CCO_O2*C_HO2*exp(1040.0/Temp) + 1.0*C_CO*C_OH*(3.19e-33*C_AIR + 1.3e-13) + 1.0*C_COOH*J_16 + 1.18e-12*C_C_O2**2*exp(-509.0/Temp) - 3.8e-13*C_C_O2*C_HO2*exp(780.0/Temp) + 2.8e-12*C_C_O2*C_NO*exp(285.0/Temp) + 1.3e-12*C_C_O2*C_NO3 + 2.0e-13*C_C_O2*C_RO2_N + 2.0e-13*C_C_O2*C_RO2_R + 3.0e-18*C_DCB1*C_O3 + 0.5*C_DCB2*J_28 + 0.5*C_DCB3*J_29 + 1.0968e-15*C_ETHENE*C_O3*exp(-2580.0/Temp) + 5.2e-12*C_ETHENE*C_O3P*exp(-792.0/Temp) + 1.764e-12*C_GLY*C_NO3*exp(-2376.0/Temp) + 6.93e-12*C_GLY*C_OH + 2.0*C_GLY*J_18 + 7.7e-12*C_H2*C_OH*exp(-2100.0/Temp) - 2.0*C_H2O*C_HO2**2*(2.59e-54*C_AIR*exp(3180.0/Temp) + 3.08e-34*exp(2800.0/Temp)) + 2.9e-12*C_H2O2*C_OH*exp(-160.0/Temp) - 9.7e-15*C_HCHO*C_HO2*exp(625.0/Temp) + 2.0e-12*C_HCHO*C_NO3*exp(-2431.0/Temp) + 8.6e-12*C_HCHO*C_OH*exp(20.0/Temp) + 2.0*C_HCHO*J_10 + 0.61*C_HNO4*J_8 - 2.0*C_HO2**2*(1.85e-33*C_AIR*exp(980.0/Temp) + 2.2e-13*exp(600.0/Temp)) - 4.3e-13*C_HO2*C_MA_RCO3*exp(1040.0/Temp) - 3.4e-12*C_HO2*C_NO*exp(270.0/Temp) - 4.0e-12*C_HO2*C_NO3 - 1.4e-14*C_HO2*C_O3*exp(-600.0/Temp) - 4.8e-11*C_HO2*C_OH*exp(250.0/Temp) - 4.3e-13*C_HO2*C_RCO_O2*exp(1040.0/Temp) - 1.9e-13*C_HO2*C_RO2_N*exp(1300.0/Temp) - 1.9e-13*C_HO2*C_RO2_R*exp(1300.0/Temp) + 2.8e-12*C_HOCOO*C_NO*exp(285.0/Temp) + 2400000000000.0*C_HOCOO*exp(-7000.0/Temp) + 1.0*C_HONO*J_6 + 1.672e-18*C_ISOPROD*C_O3 + 1.233*C_ISOPROD*J_25 + 3.44444444444444e-17*C_MEOH*C_OH*Temp**2.0*exp(-360.0/Temp) + 1.088e-17*C_METHACRO*C_O3*exp(-2114.0/Temp) + 0.34*C_METHACRO*J_23 + 1.0*C_MGLY*J_20 + 4.8064e-17*C_MVK*C_O3*exp(-1520.0/Temp) + 2.7e-12*C_NO*C_RO2_R*exp(360.0/Temp) + 2.0e-11*C_NO3*C_OH + 2.3e-12*C_NO3*C_RO2_N + 2.3e-12*C_NO3*C_RO2_R + 1.9e-12*C_O3*C_OH*exp(-1000.0/Temp) + 1.46552e-16*C_O3*C_OLE1*exp(-1640.0/Temp) + 1.5066e-18*C_O3*C_OLE2*exp(-461.0/Temp) + 3.564e-17*C_O3*C_TERP*exp(-821.0/Temp) + 2.7105e-13*C_O3P*C_OLE2 + 5.685e-12*C_OH*C_PROD2 + 8.814e-13*C_OH*C_RNO3 + 1.0*C_RCHO*J_13 + 0.341*C_RNO3*J_27 + 3.5e-14*C_RO2_N**2 + 3.5e-14*C_RO2_N*C_RO2_R + 3.5e-14*C_RO2_R**2 + 1.0*C_ROOH*J_17) + (EXPLICIT: 0)
d[C_O2]/dt = (IMPLICIT: 1.0*C_ACET*J_14 + 6.5406e-14*C_ALK4*C_OH*exp(-91.0/Temp) + 2.9e-12*C_BZCO_O2*C_CCO_O2*exp(500.0/Temp) - 1.8e-12*C_BZCO_O2*C_C_O2*exp(500.0/Temp) + 1.0*C_CCHO*J_12 + 5.8e-12*C_CCO_O2**2*exp(500.0/Temp) - 1.8e-12*C_CCO_O2*C_C_O2*exp(500.0/Temp) + 2.9e-12*C_CCO_O2*C_MA_RCO3*exp(500.0/Temp) + 7.8e-12*C_CCO_O2*C_NO*exp(300.0/Temp) + 4.0e-12*C_CCO_O2*C_NO3 + 2.9e-12*C_CCO_O2*C_RCO_O2*exp(500.0/Temp) + 2.15e-12*C_CH4*C_OH*exp(-1735.0/Temp) + 1.885e-12*C_COOH*C_OH*exp(190.0/Temp) - 4.9e-14*C_C_O2**2*exp(710.0/Temp) - 1.18e-12*C_C_O2**2*exp(-509.0/Temp) - 3.8e-13*C_C_O2*C_HO2*exp(780.0/Temp) - 1.8e-12*C_C_O2*C_MA_RCO3*exp(500.0/Temp) - 2.8e-12*C_C_O2*C_NO*exp(285.0/Temp) - 1.3e-12*C_C_O2*C_NO3 - 1.8e-12*C_C_O2*C_RCO_O2*exp(500.0/Temp) - 2.0e-13*C_C_O2*C_RO2_N - 2.0e-13*C_C_O2*C_RO2_R + 3.12e-12*C_ETHENE*C_O3P*exp(-792.0/Temp) + 9.0e-12*C_ISOPRENE*C_O3P + 0.3*C_MVK*J_24 + 2.1795e-14*C_NO3*C_OLE2 + 1.98892e-16*C_O3*C_OLE1*exp(-1640.0/Temp) + 9.89334e-17*C_O3*C_OLE2*exp(-461.0/Temp) + 750000000000000.0*C_TBU_O*exp(-8152.0/Temp)) + (EXPLICIT: 0)
d[COOH]/dt = (IMPLICIT: -2.9e-12*C_COOH*C_OH*exp(190.0/Temp) - 1.0*C_COOH*J_16 + 3.8e-13*C_C_O2*C_HO2*exp(780.0/Temp)) + (EXPLICIT: 0)
d[ROOH]/dt = (IMPLICIT: 1.9e-13*C_HO2*C_RO2_N*exp(1300.0/Temp) + 1.9e-13*C_HO2*C_RO2_R*exp(1300.0/Temp) - 1.1e-11*C_OH*C_ROOH - 1.0*C_ROOH*J_17) + (EXPLICIT: 0)
d[RO2_R]/dt = (IMPLICIT: 1.52222222222222e-17*C_ALK1*C_OH*Temp**2.0*exp(-498.0/Temp) + 6.04044e-12*C_ALK2*C_OH*exp(-671.0/Temp) + 7.08205e-12*C_ALK3*C_OH*exp(-434.0/Temp) + 4.96491e-12*C_ALK4*C_OH*exp(-91.0/Temp) + 7.26136e-12*C_ALK5*C_OH*exp(-52.0/Temp) + 1.38465e-12*C_ARO1*C_OH*exp(355.0/Temp) + 2.12256e-11*C_ARO2*C_OH + 2.9e-12*C_BZCO_O2*C_RCO_O2*exp(500.0/Temp) - 7.5e-12*C_BZCO_O2*C_RO2_R + 2.9e-12*C_CCO_O2*C_RCO_O2*exp(500.0/Temp) - 7.5e-12*C_CCO_O2*C_RO2_R + 3.192e-11*C_CRES*C_OH - 2.0e-13*C_C_O2*C_RO2_R + 5.0e-11*C_DCB1*C_OH + 1.0*C_DCB2*J_28 + 1.0*C_DCB3*J_29 + 4.87777777777778e-18*C_ETHENE*C_NO3*Temp**2.0*exp(-2282.0/Temp) + 2.08e-12*C_ETHENE*C_O3P*exp(-792.0/Temp) + 1.96e-12*C_ETHENE*C_OH*exp(438.0/Temp) - 1.9e-13*C_HO2*C_RO2_R*exp(1300.0/Temp) + 2.26947e-12*C_ISOPRENE*C_NO3*exp(-448.0/Temp) + 5.1876e-16*C_ISOPRENE*C_O3*exp(-1912.0/Temp) + 2.2675e-11*C_ISOPRENE*C_OH*exp(408.0/Temp) + 7.99e-14*C_ISOPROD*C_NO3 + 2.0064e-19*C_ISOPROD*C_O3 + 4.1473e-11*C_ISOPROD*C_OH + 2.9e-12*C_MA_RCO3*C_RCO_O2*exp(500.0/Temp) - 7.5e-12*C_MA_RCO3*C_RO2_R + 5.34444444444444e-18*C_MEK*C_OH*Temp**2.0*exp(-25.0/Temp) + 1.0*C_MEK*J_15 + 7.5e-13*C_METHACRO*C_NO3*exp(-1726.0/Temp) + 1.36e-16*C_METHACRO*C_O3*exp(-2114.0/Temp) + 9.3e-12*C_METHACRO*C_OH*exp(176.0/Temp) + 0.33*C_METHACRO*J_23 + 3.755e-17*C_MVK*C_O3*exp(-1520.0/Temp) + 1.242e-12*C_MVK*C_OH*exp(453.0/Temp) + 1.25e-11*C_NO*C_RCO_O2*exp(240.0/Temp) - 2.7e-12*C_NO*C_RO2_R*exp(360.0/Temp) + 3.669272e-14*C_NO3*C_OLE1*exp(-376.0/Temp) + 3.21113e-13*C_NO3*C_OLE2 + 4.0e-12*C_NO3*C_RCO_O2 - 2.3e-12*C_NO3*C_RO2_R + 1.01016e-12*C_NO3*C_TERP*exp(175.0/Temp) + 5.7574e-17*C_O3*C_OLE1*exp(-1640.0/Temp) + 1.65726e-17*C_O3*C_OLE2*exp(-461.0/Temp) + 3.348e-17*C_O3*C_TERP*exp(-821.0/Temp) + 2.502e-13*C_O3P*C_OLE2 + 6.45645e-12*C_OH*C_OLE1*exp(451.0/Temp) + 1.600074e-11*C_OH*C_OLE2*exp(384.0/Temp) + 1.9988e-11*C_OH*C_PHEN + 7.095e-12*C_OH*C_PROD2 + 6.8e-13*C_OH*C_RCHO + 2.9328e-12*C_OH*C_RNO3 + 3.74e-12*C_OH*C_ROOH + 1.3725e-11*C_OH*C_TERP*exp(449.0/Temp) + 0.96*C_PROD2*J_26 + 1.0*C_RCHO*J_13 + 5.8e-12*C_RCO_O2**2*exp(500.0/Temp) - 7.5e-12*C_RCO_O2*C_RO2_R + 0.564*C_RNO3*J_27 - 3.5e-14*C_RO2_N*C_RO2_R - 7.0e-14*C_RO2_R**2) + (EXPLICIT: 0)
d[R2O2]/dt = (IMPLICIT: 1.1e-12*C_ACET*C_OH*exp(-520.0/Temp) + 5.69621e-12*C_ALK3*C_OH*exp(-434.0/Temp) + 5.565456e-12*C_ALK4*C_OH*exp(-91.0/Temp) + 1.054176e-11*C_ALK5*C_OH*exp(-52.0/Temp) + 5.8e-12*C_BZCO_O2**2*exp(500.0/Temp) + 2.9e-12*C_BZCO_O2*C_CCO_O2*exp(500.0/Temp) + 2.9e-12*C_BZCO_O2*C_MA_RCO3*exp(500.0/Temp) + 1.25e-11*C_BZCO_O2*C_NO*exp(240.0/Temp) + 4.0e-12*C_BZCO_O2*C_NO3 - 7.5e-12*C_BZCO_O2*C_R2O2 + 2.9e-12*C_BZCO_O2*C_RCO_O2*exp(500.0/Temp) - 7.5e-12*C_CCO_O2*C_R2O2 - 2.0e-13*C_C_O2*C_R2O2 + 5.0e-11*C_DCB2*C_OH + 1.0*C_DCB2*J_28 + 5.0e-11*C_DCB3*C_OH + 1.0*C_DCB3*J_29 - 1.9e-13*C_HO2*C_R2O2*exp(1300.0/Temp) + 5.6661e-13*C_ISOPRENE*C_NO3*exp(-448.0/Temp) + 9.9036e-16*C_ISOPRENE*C_O3*exp(-1912.0/Temp) + 8.64e-12*C_ISOPRENE*C_O3P + 1.975e-12*C_ISOPRENE*C_OH*exp(408.0/Temp) - 7.5e-12*C_MA_RCO3*C_R2O2 + 8.89777777777778e-18*C_MEK*C_OH*Temp**2.0*exp(-25.0/Temp) + 2.7945e-12*C_MVK*C_OH*exp(453.0/Temp) - 2.7e-12*C_NO*C_R2O2*exp(360.0/Temp) + 2.173064e-14*C_NO3*C_OLE1*exp(-376.0/Temp) + 5.165415e-13*C_NO3*C_OLE2 - 2.3e-12*C_NO3*C_R2O2 + 2.745e-12*C_NO3*C_TERP*exp(175.0/Temp) + 6.88014e-17*C_O3*C_OLE2*exp(-461.0/Temp) + 7.8732e-16*C_O3*C_TERP*exp(-821.0/Temp) + 1.454475e-12*C_OH*C_OLE1*exp(451.0/Temp) + 1.743e-14*C_OH*C_OLE2*exp(384.0/Temp) + 4.6488e-12*C_OH*C_RNO3 + 9.15e-12*C_OH*C_TERP*exp(449.0/Temp) + 0.515*C_PROD2*J_26 - 7.5e-12*C_R2O2*C_RCO_O2 - 3.5e-14*C_R2O2*C_RO2_N - 3.5e-14*C_R2O2*C_RO2_R + 0.152*C_RNO3*J_27) + (EXPLICIT: 0)
d[RO2_N]/dt = (IMPLICIT: 2.0727e-13*C_ALK2*C_OH*exp(-671.0/Temp) + 7.133e-13*C_ALK3*C_OH*exp(-434.0/Temp) + 8.50278e-13*C_ALK4*C_OH*exp(-91.0/Temp) + 3.85864e-12*C_ALK5*C_OH*exp(-52.0/Temp) + 1.991e-14*C_ARO1*C_OH*exp(355.0/Temp) + 2.376e-13*C_ARO2*C_OH - 7.5e-12*C_BZCO_O2*C_RO2_N - 7.5e-12*C_CCO_O2*C_RO2_N - 2.0e-13*C_C_O2*C_RO2_N - 1.9e-13*C_HO2*C_RO2_N*exp(1300.0/Temp) + 1.9392e-13*C_ISOPRENE*C_NO3*exp(-448.0/Temp) + 6.288e-17*C_ISOPRENE*C_O3*exp(-1912.0/Temp) + 3.6e-13*C_ISOPRENE*C_O3P + 2.325e-12*C_ISOPRENE*C_OH*exp(408.0/Temp) + 5.1e-15*C_ISOPROD*C_NO3 + 2.5379e-12*C_ISOPROD*C_OH - 7.5e-12*C_MA_RCO3*C_RO2_N + 6.06666666666667e-19*C_MEK*C_OH*Temp**2.0*exp(-25.0/Temp) + 1.035e-13*C_MVK*C_OH*exp(453.0/Temp) - 2.7e-12*C_NO*C_RO2_N*exp(360.0/Temp) + 7.83728e-15*C_NO3*C_OLE1*exp(-376.0/Temp) + 9.8804e-14*C_NO3*C_OLE2 - 2.3e-12*C_NO3*C_RO2_N + 9.15e-13*C_NO3*C_TERP*exp(175.0/Temp) + 2.617e-18*C_O3*C_OLE1*exp(-1640.0/Temp) + 1.0044e-18*C_O3*C_OLE2*exp(-461.0/Temp) + 1.944e-16*C_O3*C_TERP*exp(-821.0/Temp) + 2.085e-14*C_O3P*C_OLE2 + 6.3855e-13*C_OH*C_OLE1*exp(451.0/Temp) + 1.42926e-12*C_OH*C_OLE2*exp(384.0/Temp) + 1.05e-12*C_OH*C_PROD2 + 2.0e-14*C_OH*C_RCHO + 1.3494e-12*C_OH*C_RNO3 + 4.575e-12*C_OH*C_TERP*exp(449.0/Temp) + 0.04*C_PROD2*J_26 - 7.5e-12*C_RCO_O2*C_RO2_N + 0.095*C_RNO3*J_27 - 7.0e-14*C_RO2_N**2 - 3.5e-14*C_RO2_N*C_RO2_R) + (EXPLICIT: 0)
d[HOCOO]/dt = (IMPLICIT: 9.7e-15*C_HCHO*C_HO2*exp(625.0/Temp) - 2.8e-12*C_HOCOO*C_NO*exp(285.0/Temp) - 2400000000000.0*C_HOCOO*exp(-7000.0/Temp)) + (EXPLICIT: 0)
d[CCO_O2]/dt = (IMPLICIT: -6.97915519241595e-46*0.3**(1.0/(log(9.86349295796486e-33*C_AIR*Temp**6.2)**2/log(10)**2 + 1.0))*C_AIR*C_CCO_O2*C_NO2*Temp**7.1/(9.86349295796486e-33*C_AIR*Temp**6.2 + 1.0) + 0.0049*0.3**(1.0/(log(1.225e-19*C_AIR*exp(-1500.0/Temp)/(Temp/300)**0.0.)**2/log(10)**2 + 1.0))*C_AIR*C_PAN*exp(12100.0/Temp)/(1.225e-19*C_AIR*exp(-1500.0/Temp)/(Temp/300)**0.0. + 1.0) + 1.1e-12*C_ACET*C_OH*exp(-520.0/Temp) + 1.0*C_ACET*J_14 + 6.5406e-14*C_ALK4*C_OH*exp(-91.0/Temp) + 2.0*C_BACL*J_21 - 2.9e-12*C_BZCO_O2*C_CCO_O2*exp(500.0/Temp) + 2.9e-12*C_BZCO_O2*C_MA_RCO3*exp(500.0/Temp) + 1.4e-12*C_CCHO*C_NO3*exp(-1860.0/Temp) + 5.6e-12*C_CCHO*C_OH*exp(310.0/Temp) - 5.8e-12*C_CCO_O2**2*exp(500.0/Temp) - 1.8e-12*C_CCO_O2*C_C_O2*exp(500.0/Temp) - 4.3e-13*C_CCO_O2*C_HO2*exp(1040.0/Temp) - 7.8e-12*C_CCO_O2*C_NO*exp(300.0/Temp) - 4.0e-12*C_CCO_O2*C_NO3 - 2.9e-12*C_CCO_O2*C_RCO_O2*exp(500.0/Temp) - 7.5e-12*C_CCO_O2*C_RO2_N - 7.5e-12*C_CCO_O2*C_RO2_R + 5.0e-11*C_DCB2*C_OH + 0.5*C_DCB2*J_28 + 5.0e-11*C_DCB3*C_OH + 0.5*C_DCB3*J_29 + 0.467*C_ISOPROD*J_25 + 5.8e-12*C_MA_RCO3**2*exp(500.0/Temp) + 1.25e-11*C_MA_RCO3*C_NO*exp(240.0/Temp) + 4.0e-12*C_MA_RCO3*C_NO3 + 2.9e-12*C_MA_RCO3*C_RCO_O2*exp(500.0/Temp) + 7.10666666666667e-18*C_MEK*C_OH*Temp**2.0*exp(-25.0/Temp) + 1.0*C_MEK*J_15 + 0.67*C_METHACRO*J_23 + 1.4e-12*C_MGLY*C_NO3*exp(-1895.0/Temp) + 1.5e-11*C_MGLY*C_OH + 1.0*C_MGLY*J_20 + 2.7945e-12*C_MVK*C_OH*exp(453.0/Temp) + 6.88014e-17*C_O3*C_OLE2*exp(-461.0/Temp) + 1.3284e-16*C_O3*C_TERP*exp(-821.0/Temp) + 4.35e-13*C_OH*C_PROD2 + 0.667*C_PROD2*J_26) + (EXPLICIT: 0)
d[BZCO_O2]/dt = (IMPLICIT: 1.4e-12*C_BALD*C_NO3*exp(-1872.0/Temp) + 1.29e-11*C_BALD*C_OH - 5.8e-12*C_BZCO_O2**2*exp(500.0/Temp) - 2.9e-12*C_BZCO_O2*C_CCO_O2*exp(500.0/Temp) - 1.8e-12*C_BZCO_O2*C_C_O2*exp(500.0/Temp) - 4.3e-13*C_BZCO_O2*C_HO2*exp(1040.0/Temp) - 2.9e-12*C_BZCO_O2*C_MA_RCO3*exp(500.0/Temp) - 1.25e-11*C_BZCO_O2*C_NO*exp(240.0/Temp) - 1.37e-11*C_BZCO_O2*C_NO2 - 4.0e-12*C_BZCO_O2*C_NO3 - 2.9e-12*C_BZCO_O2*C_RCO_O2*exp(500.0/Temp) - 7.5e-12*C_BZCO_O2*C_RO2_N - 7.5e-12*C_BZCO_O2*C_RO2_R + 7.9e+16*C_PBZN*exp(-14000.0/Temp)) + (EXPLICIT: 0)
d[BZNO2_O]/dt = (IMPLICIT: -2.3e-11*C_BZNO2_O*C_HO2*exp(150.0/Temp) - 750000000000000.0*C_BZNO2_O*C_NO2*exp(-8152.0/Temp) - 1.9e-13*C_BZNO2_O*exp(1300.0/Temp) + 3.78e-12*C_NO3*C_NPHE) + (EXPLICIT: 0)
d[BZ_O]/dt = (IMPLICIT: 5.8e-12*C_BZCO_O2**2*exp(500.0/Temp) + 2.9e-12*C_BZCO_O2*C_CCO_O2*exp(500.0/Temp) + 2.9e-12*C_BZCO_O2*C_MA_RCO3*exp(500.0/Temp) + 1.25e-11*C_BZCO_O2*C_NO*exp(240.0/Temp) + 4.0e-12*C_BZCO_O2*C_NO3 + 2.9e-12*C_BZCO_O2*C_RCO_O2*exp(500.0/Temp) - 1.9e-13*C_BZ_O*C_HO2*exp(1300.0/Temp) - 2.3e-11*C_BZ_O*C_NO2*exp(150.0/Temp) - 0.001*C_BZ_O + 1.37e-11*C_CRES*C_NO3 + 1.008e-11*C_CRES*C_OH + 3.78e-12*C_NO3*C_PHEN + 6.312e-12*C_OH*C_PHEN) + (EXPLICIT: 0)
d[MA_RCO3]/dt = (IMPLICIT: -2.9e-12*C_BZCO_O2*C_MA_RCO3*exp(500.0/Temp) - 2.9e-12*C_CCO_O2*C_MA_RCO3*exp(500.0/Temp) - 1.8e-12*C_C_O2*C_MA_RCO3*exp(500.0/Temp) - 4.3e-13*C_HO2*C_MA_RCO3*exp(1040.0/Temp) + 1.50912e-15*C_ISOPRENE*C_O3*exp(-1912.0/Temp) + 8.64e-12*C_ISOPRENE*C_O3P + 1.5e-14*C_ISOPROD*C_NO3 + 1.78891e-11*C_ISOPROD*C_OH + 1.6e+16*C_MA_PAN*exp(-13486.0/Temp) - 5.8e-12*C_MA_RCO3**2*exp(500.0/Temp) - 1.25e-11*C_MA_RCO3*C_NO*exp(240.0/Temp) - 2.03512165410849e-9*C_MA_RCO3*C_NO2/Temp**0.9 - 4.0e-12*C_MA_RCO3*C_NO3 - 2.9e-12*C_MA_RCO3*C_RCO_O2*exp(500.0/Temp) - 7.5e-12*C_MA_RCO3*C_RO2_N - 7.5e-12*C_MA_RCO3*C_RO2_R + 7.5e-13*C_METHACRO*C_NO3*exp(-1726.0/Temp) + 9.3e-12*C_METHACRO*C_OH*exp(176.0/Temp) + 0.33*C_METHACRO*J_23 + 0.3*C_MVK*J_24) + (EXPLICIT: 0)
d[TBU_O]/dt = (IMPLICIT: 2.40484e-12*C_ALK3*C_OH*exp(-434.0/Temp) - 2.4e-11*C_NO2*C_TBU_O - 750000000000000.0*C_TBU_O*exp(-8152.0/Temp)) + (EXPLICIT: 0)
d[AIR]/dt = (IMPLICIT: 0) + (EXPLICIT: 0)
d[O2]/dt = (IMPLICIT: 0) + (EXPLICIT: 0)
d[H2O]/dt = (IMPLICIT: 0) + (EXPLICIT: 0)
d[H2]/dt = (IMPLICIT: 0) + (EXPLICIT: 0)
d[CH4]/dt = (IMPLICIT: 0) + (EXPLICIT: 0)
d[M]/dt = (IMPLICIT: 0) + (EXPLICIT: 0)
d[N2]/dt = (IMPLICIT: 0) + (EXPLICIT: 0)
d[RO2]/dt = (IMPLICIT: 0) + (EXPLICIT: 0)
```

## Performance & Stiffness Diagnostics
The following species are the most heavily coupled (densest Jacobian rows). These dictate the performance ceiling of the Dense LU / ROS2 implicit solver block:

| Species | Non-Zero Dependencies |
|---------|-----------------------|
| OH | 50 |
| HO2 | 48 |
| RO2_R | 38 |
| NO3 | 35 |
| HCHO | 34 |

### Warnings
- ⚠️ Mechanism exceeds 50 species. Consider running with `--lump` to auto-reduce.
- ⚠️ Mechanism contains complex pressure-dependent or empirical falloff rates which expand the AST depth significantly.
