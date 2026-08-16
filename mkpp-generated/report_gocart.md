# MKPP Mechanism Diagnostic Report: gocart

## Overview
- **Total Species**: 26
- **Total Reactions**: 27

### Reaction Types Breakdown
- **ARRHENIUS**: 5
- **HETEROGENEOUS**: 21
- **PHOTOLYSIS**: 1

### Stiffness Partitioning
- **Implicit (Stiff) Reactions**: 1
- **Explicit (Non-Stiff) Reactions**: 26
- **Graph Topology Status**: Mechanism contains cyclically dependent fast radicals. Tarjan SCC was applied.

## Generated SymPy Rate Expressions
Below are the exact algebraic AST expressions evaluated by SymPy for the Unified Jacobian.

```text
R1: ARRHENIUS | Reactants: ['DMS', 'OH'] | Products: ['SO2'] | A: 1.2e-11
R2: ARRHENIUS | Reactants: ['DMS', 'NO3'] | Products: ['SO2'] | A: 1.9e-13
R3: ARRHENIUS | Reactants: ['SO2', 'OH'] | Products: ['SO4'] | A: 3.3e-12
R4: HETEROGENEOUS | Reactants: ['SO2', 'H2O2'] | Products: ['SO4'] | A: N/A
R5: ARRHENIUS | Reactants: ['BC1'] | Products: ['BC2'] | A: 5e-06
R6: ARRHENIUS | Reactants: ['OC1'] | Products: ['OC2'] | A: 5e-06
R7: PHOTOLYSIS | Reactants: ['H2O2'] | Products: ['OH'] | A: 1e-05
R8: HETEROGENEOUS | Reactants: ['SO2', 'DUST1'] | Products: ['SO4', 'DUST1'] | A: N/A
R9: HETEROGENEOUS | Reactants: ['SO2', 'DUST2'] | Products: ['SO4', 'DUST2'] | A: N/A
R10: HETEROGENEOUS | Reactants: ['SO2', 'DUST3'] | Products: ['SO4', 'DUST3'] | A: N/A
R11: HETEROGENEOUS | Reactants: ['SO2', 'DUST4'] | Products: ['SO4', 'DUST4'] | A: N/A
R12: HETEROGENEOUS | Reactants: ['SO2', 'DUST5'] | Products: ['SO4', 'DUST5'] | A: N/A
R13: HETEROGENEOUS | Reactants: ['SO2', 'SS1'] | Products: ['SO4', 'SS1'] | A: N/A
R14: HETEROGENEOUS | Reactants: ['SO2', 'SS2'] | Products: ['SO4', 'SS2'] | A: N/A
R15: HETEROGENEOUS | Reactants: ['SO2', 'SS3'] | Products: ['SO4', 'SS3'] | A: N/A
R16: HETEROGENEOUS | Reactants: ['SO2', 'SS4'] | Products: ['SO4', 'SS4'] | A: N/A
R17: HETEROGENEOUS | Reactants: ['SO2', 'SS5'] | Products: ['SO4', 'SS5'] | A: N/A
R18: HETEROGENEOUS | Reactants: ['HNO3', 'DUST1'] | Products: ['NO3an1', 'DUST1'] | A: N/A
R19: HETEROGENEOUS | Reactants: ['HNO3', 'DUST2'] | Products: ['NO3an2', 'DUST2'] | A: N/A
R20: HETEROGENEOUS | Reactants: ['HNO3', 'DUST3'] | Products: ['NO3an3', 'DUST3'] | A: N/A
R21: HETEROGENEOUS | Reactants: ['HNO3', 'DUST4'] | Products: ['NO3an1', 'DUST4'] | A: N/A
R22: HETEROGENEOUS | Reactants: ['HNO3', 'DUST5'] | Products: ['NO3an2', 'DUST5'] | A: N/A
R23: HETEROGENEOUS | Reactants: ['HNO3', 'SS1'] | Products: ['NO3an3', 'SS1'] | A: N/A
R24: HETEROGENEOUS | Reactants: ['HNO3', 'SS2'] | Products: ['NO3an1', 'SS2'] | A: N/A
R25: HETEROGENEOUS | Reactants: ['HNO3', 'SS3'] | Products: ['NO3an2', 'SS3'] | A: N/A
R26: HETEROGENEOUS | Reactants: ['HNO3', 'SS4'] | Products: ['NO3an3', 'SS4'] | A: N/A
R27: HETEROGENEOUS | Reactants: ['HNO3', 'SS5'] | Products: ['NO3an1', 'SS5'] | A: N/A
d[OH]/dt = (IMPLICIT: -3.3e-12*C_OH*C_SO2) + (EXPLICIT: -1.2e-11*C_DMS*C_OH*exp(-260.0/Temp) + 2.0*C_H2O2*J_0)
d[NO3]/dt = (IMPLICIT: 0) + (EXPLICIT: -1.9e-13*C_DMS*C_NO3*exp(-520.0/Temp))
d[H2O2]/dt = (IMPLICIT: 0) + (EXPLICIT: -0.0025*C_H2O2*C_SO2*S_a*v_gas - 1.0*C_H2O2*J_0)
d[DMS]/dt = (IMPLICIT: 0) + (EXPLICIT: -1.9e-13*C_DMS*C_NO3*exp(-520.0/Temp) - 1.2e-11*C_DMS*C_OH*exp(-260.0/Temp))
d[SO2]/dt = (IMPLICIT: -2.5e-5*C_DUST1*C_SO2*S_a*v_gas - 2.5e-5*C_DUST2*C_SO2*S_a*v_gas - 2.5e-5*C_DUST3*C_SO2*S_a*v_gas - 2.5e-5*C_DUST4*C_SO2*S_a*v_gas - 2.5e-5*C_DUST5*C_SO2*S_a*v_gas - 3.3e-12*C_OH*C_SO2 - 0.00025*C_SO2*C_SS1*S_a*v_gas - 0.00025*C_SO2*C_SS2*S_a*v_gas - 0.00025*C_SO2*C_SS3*S_a*v_gas - 0.00025*C_SO2*C_SS4*S_a*v_gas - 0.00025*C_SO2*C_SS5*S_a*v_gas) + (EXPLICIT: 1.9e-13*C_DMS*C_NO3*exp(-520.0/Temp) + 1.2e-11*C_DMS*C_OH*exp(-260.0/Temp) - 0.0025*C_H2O2*C_SO2*S_a*v_gas)
d[SO4]/dt = (IMPLICIT: 2.5e-5*C_DUST1*C_SO2*S_a*v_gas + 2.5e-5*C_DUST2*C_SO2*S_a*v_gas + 2.5e-5*C_DUST3*C_SO2*S_a*v_gas + 2.5e-5*C_DUST4*C_SO2*S_a*v_gas + 2.5e-5*C_DUST5*C_SO2*S_a*v_gas + 3.3e-12*C_OH*C_SO2 + 0.00025*C_SO2*C_SS1*S_a*v_gas + 0.00025*C_SO2*C_SS2*S_a*v_gas + 0.00025*C_SO2*C_SS3*S_a*v_gas + 0.00025*C_SO2*C_SS4*S_a*v_gas + 0.00025*C_SO2*C_SS5*S_a*v_gas) + (EXPLICIT: 0.0025*C_H2O2*C_SO2*S_a*v_gas)
d[BC1]/dt = (IMPLICIT: 0) + (EXPLICIT: -5.0e-6*C_BC1)
d[BC2]/dt = (IMPLICIT: 0) + (EXPLICIT: 5.0e-6*C_BC1)
d[OC1]/dt = (IMPLICIT: 0) + (EXPLICIT: -5.0e-6*C_OC1)
d[OC2]/dt = (IMPLICIT: 0) + (EXPLICIT: 5.0e-6*C_OC1)
d[DUST1]/dt = (IMPLICIT: 0) + (EXPLICIT: 0)
d[DUST2]/dt = (IMPLICIT: 0) + (EXPLICIT: 0)
d[DUST3]/dt = (IMPLICIT: 0) + (EXPLICIT: 0)
d[DUST4]/dt = (IMPLICIT: 0) + (EXPLICIT: 0)
d[DUST5]/dt = (IMPLICIT: 0) + (EXPLICIT: 0)
d[SS1]/dt = (IMPLICIT: 0) + (EXPLICIT: 0)
d[SS2]/dt = (IMPLICIT: 0) + (EXPLICIT: 0)
d[SS3]/dt = (IMPLICIT: 0) + (EXPLICIT: 0)
d[SS4]/dt = (IMPLICIT: 0) + (EXPLICIT: 0)
d[SS5]/dt = (IMPLICIT: 0) + (EXPLICIT: 0)
d[HNO3]/dt = (IMPLICIT: -0.025*C_DUST1*C_HNO3*S_a*v_gas - 0.025*C_DUST2*C_HNO3*S_a*v_gas - 0.025*C_DUST3*C_HNO3*S_a*v_gas - 0.025*C_DUST4*C_HNO3*S_a*v_gas - 0.025*C_DUST5*C_HNO3*S_a*v_gas - 0.025*C_HNO3*C_SS1*S_a*v_gas - 0.025*C_HNO3*C_SS2*S_a*v_gas - 0.025*C_HNO3*C_SS3*S_a*v_gas - 0.025*C_HNO3*C_SS4*S_a*v_gas - 0.025*C_HNO3*C_SS5*S_a*v_gas + 1000000.0*C_NO3an1 + 1000000.0*C_NO3an2 + 1000000.0*C_NO3an3 - 1000000.0*((20.0*(C_NH3 + C_NH4a)/(C_SO2 + C_SO4 + 1.0e-30) - 40.0)/(2*sqrt((20.0*(C_NH3 + C_NH4a)/(C_SO2 + C_SO4 + 1.0e-30) - 40.0)**2 + 1)) + 1/2)*((20.0*(C_NH3 + C_NH4a)/(C_SO2 + C_SO4 + 1.0e-30) - 20.0)/(2*sqrt((20.0*(C_NH3 + C_NH4a)/(C_SO2 + C_SO4 + 1.0e-30) - 20.0)**2 + 1)) + 1/2)*(C_HNO3/4 + C_NH3/4 + C_NH4a/4 + C_NO3an1/4 + C_NO3an2/4 + C_NO3an3/4 - C_SO2/2 - C_SO4/2 - sqrt((-C_HNO3 + C_NH3 + C_NH4a - C_NO3an1 - C_NO3an2 - C_NO3an3 - 2*C_SO2 - 2*C_SO4)**2 + 1.41511078464367e-29*exp(8989.05460668752/Temp))/4 + sqrt((C_HNO3/2 + C_NH3/2 + C_NH4a/2 + C_NO3an1/2 + C_NO3an2/2 + C_NO3an3/2 - C_SO2 - C_SO4 - sqrt((-C_HNO3 + C_NH3 + C_NH4a - C_NO3an1 - C_NO3an2 - C_NO3an3 - 2*C_SO2 - 2*C_SO4)**2 + 1.41511078464367e-29*exp(8989.05460668752/Temp))/2)**2 + 1.0e-20)/2)) + (EXPLICIT: 0)
d[NH3]/dt = (IMPLICIT: -1000000.0*C_NH3 + 1000000.0*((20.0*(C_NH3 + C_NH4a)/(C_SO2 + C_SO4 + 1.0e-30) - 40.0)/(2*sqrt((20.0*(C_NH3 + C_NH4a)/(C_SO2 + C_SO4 + 1.0e-30) - 40.0)**2 + 1)) + 1/2)*(-C_HNO3/8 + 3*C_NH3/8 + 3*C_NH4a/8 - C_NO3an1/8 - C_NO3an2/8 - C_NO3an3/8 - 3*C_SO2/4 - 3*C_SO4/4 + sqrt((-C_HNO3 + C_NH3 + C_NH4a - C_NO3an1 - C_NO3an2 - C_NO3an3 - 2*C_SO2 - 2*C_SO4)**2 + 1.41511078464367e-29*exp(8989.05460668752/Temp))/8 - sqrt((C_HNO3/2 + C_NH3/2 + C_NH4a/2 + C_NO3an1/2 + C_NO3an2/2 + C_NO3an3/2 - C_SO2 - C_SO4 - sqrt((-C_HNO3 + C_NH3 + C_NH4a - C_NO3an1 - C_NO3an2 - C_NO3an3 - 2*C_SO2 - 2*C_SO4)**2 + 1.41511078464367e-29*exp(8989.05460668752/Temp))/2)**2 + 1.0e-20)/4 + sqrt((-C_HNO3/4 + 3*C_NH3/4 + 3*C_NH4a/4 - C_NO3an1/4 - C_NO3an2/4 - C_NO3an3/4 - 3*C_SO2/2 - 3*C_SO4/2 + sqrt((-C_HNO3 + C_NH3 + C_NH4a - C_NO3an1 - C_NO3an2 - C_NO3an3 - 2*C_SO2 - 2*C_SO4)**2 + 1.41511078464367e-29*exp(8989.05460668752/Temp))/4 - sqrt((C_HNO3/2 + C_NH3/2 + C_NH4a/2 + C_NO3an1/2 + C_NO3an2/2 + C_NO3an3/2 - C_SO2 - C_SO4 - sqrt((-C_HNO3 + C_NH3 + C_NH4a - C_NO3an1 - C_NO3an2 - C_NO3an3 - 2*C_SO2 - 2*C_SO4)**2 + 1.41511078464367e-29*exp(8989.05460668752/Temp))/2)**2 + 1.0e-20)/2)**2 + 1.0e-20)/2)) + (EXPLICIT: 0)
d[NH4a]/dt = (IMPLICIT: 1000000.0*C_NH3 - 1000000.0*((20.0*(C_NH3 + C_NH4a)/(C_SO2 + C_SO4 + 1.0e-30) - 40.0)/(2*sqrt((20.0*(C_NH3 + C_NH4a)/(C_SO2 + C_SO4 + 1.0e-30) - 40.0)**2 + 1)) + 1/2)*(-C_HNO3/8 + 3*C_NH3/8 + 3*C_NH4a/8 - C_NO3an1/8 - C_NO3an2/8 - C_NO3an3/8 - 3*C_SO2/4 - 3*C_SO4/4 + sqrt((-C_HNO3 + C_NH3 + C_NH4a - C_NO3an1 - C_NO3an2 - C_NO3an3 - 2*C_SO2 - 2*C_SO4)**2 + 1.41511078464367e-29*exp(8989.05460668752/Temp))/8 - sqrt((C_HNO3/2 + C_NH3/2 + C_NH4a/2 + C_NO3an1/2 + C_NO3an2/2 + C_NO3an3/2 - C_SO2 - C_SO4 - sqrt((-C_HNO3 + C_NH3 + C_NH4a - C_NO3an1 - C_NO3an2 - C_NO3an3 - 2*C_SO2 - 2*C_SO4)**2 + 1.41511078464367e-29*exp(8989.05460668752/Temp))/2)**2 + 1.0e-20)/4 + sqrt((-C_HNO3/4 + 3*C_NH3/4 + 3*C_NH4a/4 - C_NO3an1/4 - C_NO3an2/4 - C_NO3an3/4 - 3*C_SO2/2 - 3*C_SO4/2 + sqrt((-C_HNO3 + C_NH3 + C_NH4a - C_NO3an1 - C_NO3an2 - C_NO3an3 - 2*C_SO2 - 2*C_SO4)**2 + 1.41511078464367e-29*exp(8989.05460668752/Temp))/4 - sqrt((C_HNO3/2 + C_NH3/2 + C_NH4a/2 + C_NO3an1/2 + C_NO3an2/2 + C_NO3an3/2 - C_SO2 - C_SO4 - sqrt((-C_HNO3 + C_NH3 + C_NH4a - C_NO3an1 - C_NO3an2 - C_NO3an3 - 2*C_SO2 - 2*C_SO4)**2 + 1.41511078464367e-29*exp(8989.05460668752/Temp))/2)**2 + 1.0e-20)/2)**2 + 1.0e-20)/2)) + (EXPLICIT: 0)
d[NO3an1]/dt = (IMPLICIT: 0.025*C_DUST1*C_HNO3*S_a*v_gas + 0.025*C_DUST4*C_HNO3*S_a*v_gas + 0.025*C_HNO3*C_SS2*S_a*v_gas + 0.025*C_HNO3*C_SS5*S_a*v_gas - 1000000.0*C_NO3an1 + 333333.333333333*((20.0*(C_NH3 + C_NH4a)/(C_SO2 + C_SO4 + 1.0e-30) - 40.0)/(2*sqrt((20.0*(C_NH3 + C_NH4a)/(C_SO2 + C_SO4 + 1.0e-30) - 40.0)**2 + 1)) + 1/2)*((20.0*(C_NH3 + C_NH4a)/(C_SO2 + C_SO4 + 1.0e-30) - 20.0)/(2*sqrt((20.0*(C_NH3 + C_NH4a)/(C_SO2 + C_SO4 + 1.0e-30) - 20.0)**2 + 1)) + 1/2)*(C_HNO3/4 + C_NH3/4 + C_NH4a/4 + C_NO3an1/4 + C_NO3an2/4 + C_NO3an3/4 - C_SO2/2 - C_SO4/2 - sqrt((-C_HNO3 + C_NH3 + C_NH4a - C_NO3an1 - C_NO3an2 - C_NO3an3 - 2*C_SO2 - 2*C_SO4)**2 + 1.41511078464367e-29*exp(8989.05460668752/Temp))/4 + sqrt((C_HNO3/2 + C_NH3/2 + C_NH4a/2 + C_NO3an1/2 + C_NO3an2/2 + C_NO3an3/2 - C_SO2 - C_SO4 - sqrt((-C_HNO3 + C_NH3 + C_NH4a - C_NO3an1 - C_NO3an2 - C_NO3an3 - 2*C_SO2 - 2*C_SO4)**2 + 1.41511078464367e-29*exp(8989.05460668752/Temp))/2)**2 + 1.0e-20)/2)) + (EXPLICIT: 0)
d[NO3an2]/dt = (IMPLICIT: 0.025*C_DUST2*C_HNO3*S_a*v_gas + 0.025*C_DUST5*C_HNO3*S_a*v_gas + 0.025*C_HNO3*C_SS3*S_a*v_gas - 1000000.0*C_NO3an2 + 333333.333333333*((20.0*(C_NH3 + C_NH4a)/(C_SO2 + C_SO4 + 1.0e-30) - 40.0)/(2*sqrt((20.0*(C_NH3 + C_NH4a)/(C_SO2 + C_SO4 + 1.0e-30) - 40.0)**2 + 1)) + 1/2)*((20.0*(C_NH3 + C_NH4a)/(C_SO2 + C_SO4 + 1.0e-30) - 20.0)/(2*sqrt((20.0*(C_NH3 + C_NH4a)/(C_SO2 + C_SO4 + 1.0e-30) - 20.0)**2 + 1)) + 1/2)*(C_HNO3/4 + C_NH3/4 + C_NH4a/4 + C_NO3an1/4 + C_NO3an2/4 + C_NO3an3/4 - C_SO2/2 - C_SO4/2 - sqrt((-C_HNO3 + C_NH3 + C_NH4a - C_NO3an1 - C_NO3an2 - C_NO3an3 - 2*C_SO2 - 2*C_SO4)**2 + 1.41511078464367e-29*exp(8989.05460668752/Temp))/4 + sqrt((C_HNO3/2 + C_NH3/2 + C_NH4a/2 + C_NO3an1/2 + C_NO3an2/2 + C_NO3an3/2 - C_SO2 - C_SO4 - sqrt((-C_HNO3 + C_NH3 + C_NH4a - C_NO3an1 - C_NO3an2 - C_NO3an3 - 2*C_SO2 - 2*C_SO4)**2 + 1.41511078464367e-29*exp(8989.05460668752/Temp))/2)**2 + 1.0e-20)/2)) + (EXPLICIT: 0)
d[NO3an3]/dt = (IMPLICIT: 0.025*C_DUST3*C_HNO3*S_a*v_gas + 0.025*C_HNO3*C_SS1*S_a*v_gas + 0.025*C_HNO3*C_SS4*S_a*v_gas - 1000000.0*C_NO3an3 + 333333.333333333*((20.0*(C_NH3 + C_NH4a)/(C_SO2 + C_SO4 + 1.0e-30) - 40.0)/(2*sqrt((20.0*(C_NH3 + C_NH4a)/(C_SO2 + C_SO4 + 1.0e-30) - 40.0)**2 + 1)) + 1/2)*((20.0*(C_NH3 + C_NH4a)/(C_SO2 + C_SO4 + 1.0e-30) - 20.0)/(2*sqrt((20.0*(C_NH3 + C_NH4a)/(C_SO2 + C_SO4 + 1.0e-30) - 20.0)**2 + 1)) + 1/2)*(C_HNO3/4 + C_NH3/4 + C_NH4a/4 + C_NO3an1/4 + C_NO3an2/4 + C_NO3an3/4 - C_SO2/2 - C_SO4/2 - sqrt((-C_HNO3 + C_NH3 + C_NH4a - C_NO3an1 - C_NO3an2 - C_NO3an3 - 2*C_SO2 - 2*C_SO4)**2 + 1.41511078464367e-29*exp(8989.05460668752/Temp))/4 + sqrt((C_HNO3/2 + C_NH3/2 + C_NH4a/2 + C_NO3an1/2 + C_NO3an2/2 + C_NO3an3/2 - C_SO2 - C_SO4 - sqrt((-C_HNO3 + C_NH3 + C_NH4a - C_NO3an1 - C_NO3an2 - C_NO3an3 - 2*C_SO2 - 2*C_SO4)**2 + 1.41511078464367e-29*exp(8989.05460668752/Temp))/2)**2 + 1.0e-20)/2)) + (EXPLICIT: 0)
```

## Performance & Stiffness Diagnostics
The following species are the most heavily coupled (densest Jacobian rows). These dictate the performance ceiling of the Dense LU / ROS2 implicit solver block:

| Species | Non-Zero Dependencies |
|---------|-----------------------|
| HNO3 | 18 |
| SO2 | 15 |
| SO4 | 13 |
| NO3an1 | 12 |
| NO3an2 | 11 |

### Warnings
No major warnings.
