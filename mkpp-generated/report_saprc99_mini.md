# MKPP Mechanism Diagnostic Report: saprc99_mini

## Overview
- **Total Species**: 17
- **Total Reactions**: 13

### Reaction Types Breakdown
- **PHOTOLYSIS**: 4
- **ARRHENIUS**: 5
- **TROE**: 2
- **EP2**: 1
- **EP3**: 1

### Stiffness Partitioning
- **Implicit (Stiff) Reactions**: 10
- **Explicit (Non-Stiff) Reactions**: 3
- **Graph Topology Status**: Mechanism contains cyclically dependent fast radicals. Tarjan SCC was applied.

## Generated SymPy Rate Expressions
Below are the exact algebraic AST expressions evaluated by SymPy for the Unified Jacobian.

```text
R1: PHOTOLYSIS | Reactants: ['NO2'] | Products: ['NO', 'O3P'] | A: 6.69e-1
R2: ARRHENIUS | Reactants: ['O3P', 'O2', 'AIR'] | Products: ['O3'] | A: 5.68e-34
R3: ARRHENIUS | Reactants: ['O3P', 'O3'] | Products: ['O2'] | A: 8.00e-12
R4: ARRHENIUS | Reactants: ['O3', 'NO'] | Products: ['NO2'] | A: 1.80e-12
R5: ARRHENIUS | Reactants: ['O3', 'NO2'] | Products: ['NO3'] | A: 1.40e-13
R6: ARRHENIUS | Reactants: ['NO', 'NO3'] | Products: ['NO2'] | A: 1.80e-11
R7: TROE | Reactants: ['NO2', 'NO3'] | Products: ['N2O5'] | A: N/A
R8: TROE | Reactants: ['N2O5'] | Products: ['NO2', 'NO3'] | A: N/A
R9: EP2 | Reactants: ['OH', 'HNO3'] | Products: ['NO3'] | A: N/A
R10: EP3 | Reactants: ['HO2'] | Products: ['H2O2', 'O2'] | A: N/A
R11: PHOTOLYSIS | Reactants: ['HONO'] | Products: ['OH', 'NO'] | A: 1.27e-1
R12: PHOTOLYSIS | Reactants: ['HNO3'] | Products: ['OH', 'NO2'] | A: 5.40e-5
R13: PHOTOLYSIS | Reactants: ['H2O2'] | Products: ['OH'] | A: 5.64e-4
d[O3]/dt = (IMPLICIT: 4.9010355073085e-27*C_AIR*C_O2*C_O3P/Temp**2.8 - 1.8e-12*C_NO*C_O3*exp(-1370.0/Temp) - 1.4e-13*C_NO2*C_O3*exp(-2470.0/Temp) - 8.0e-12*C_O3*C_O3P*exp(-2060.0/Temp)) + (EXPLICIT: 0)
d[H2O2]/dt = (IMPLICIT: 1.0*C_HO2*(1.7e-33*C_AIR*exp(1000.0/Temp) + 2.3e-13*exp(600.0/Temp))) + (EXPLICIT: -1.0*C_H2O2*J_3)
d[NO]/dt = (IMPLICIT: -1.8e-11*C_NO*C_NO3*exp(110.0/Temp) - 1.8e-12*C_NO*C_O3*exp(-1370.0/Temp) + 1.0*C_NO2*J_0) + (EXPLICIT: 1.0*C_HONO*J_1)
d[NO2]/dt = (IMPLICIT: -2.8e-30*0.45**(1.0/(log(1.4e-18*C_AIR*exp(-3.3/Temp))**2/log(10)**2 + 1.0))*C_AIR*C_NO2*C_NO3*exp(-3.5/Temp)/(1.4e-18*C_AIR*exp(-3.3/Temp) + 1.0) + 2.13833433033195e-12*0.45**(1.0/(log(1.24621148321367e-27*C_AIR*Temp**3.6*exp(80.0/Temp))**2/log(10)**2 + 1.0))*C_AIR*C_N2O5*Temp**3.5*exp(-11000.0/Temp)/(1.24621148321367e-27*C_AIR*Temp**3.6*exp(80.0/Temp) + 1.0) + 3.6e-11*C_NO*C_NO3*exp(110.0/Temp) + 1.8e-12*C_NO*C_O3*exp(-1370.0/Temp) - 1.4e-13*C_NO2*C_O3*exp(-2470.0/Temp) - 1.0*C_NO2*J_0) + (EXPLICIT: 1.0*C_HNO3*J_2)
d[NO3]/dt = (IMPLICIT: -2.8e-30*0.45**(1.0/(log(1.4e-18*C_AIR*exp(-3.3/Temp))**2/log(10)**2 + 1.0))*C_AIR*C_NO2*C_NO3*exp(-3.5/Temp)/(1.4e-18*C_AIR*exp(-3.3/Temp) + 1.0) + 2.13833433033195e-12*0.45**(1.0/(log(1.24621148321367e-27*C_AIR*Temp**3.6*exp(80.0/Temp))**2/log(10)**2 + 1.0))*C_AIR*C_N2O5*Temp**3.5*exp(-11000.0/Temp)/(1.24621148321367e-27*C_AIR*Temp**3.6*exp(80.0/Temp) + 1.0) + 1.0*C_HNO3*C_OH*(1.9e-33*C_AIR*exp(725.0/Temp)/(4.63414634146341e-18*C_AIR*exp(-715.0/Temp) + 1.0) + 7.2e-15*exp(785.0/Temp)) - 1.8e-11*C_NO*C_NO3*exp(110.0/Temp) + 1.4e-13*C_NO2*C_O3*exp(-2470.0/Temp)) + (EXPLICIT: 0)
d[N2O5]/dt = (IMPLICIT: 2.8e-30*0.45**(1.0/(log(1.4e-18*C_AIR*exp(-3.3/Temp))**2/log(10)**2 + 1.0))*C_AIR*C_NO2*C_NO3*exp(-3.5/Temp)/(1.4e-18*C_AIR*exp(-3.3/Temp) + 1.0) - 2.13833433033195e-12*0.45**(1.0/(log(1.24621148321367e-27*C_AIR*Temp**3.6*exp(80.0/Temp))**2/log(10)**2 + 1.0))*C_AIR*C_N2O5*Temp**3.5*exp(-11000.0/Temp)/(1.24621148321367e-27*C_AIR*Temp**3.6*exp(80.0/Temp) + 1.0)) + (EXPLICIT: 0)
d[HONO]/dt = (IMPLICIT: 0) + (EXPLICIT: -1.0*C_HONO*J_1)
d[HNO3]/dt = (IMPLICIT: -1.0*C_HNO3*C_OH*(1.9e-33*C_AIR*exp(725.0/Temp)/(4.63414634146341e-18*C_AIR*exp(-715.0/Temp) + 1.0) + 7.2e-15*exp(785.0/Temp))) + (EXPLICIT: -1.0*C_HNO3*J_2)
d[HNO4]/dt = (IMPLICIT: 0) + (EXPLICIT: 0)
d[O3P]/dt = (IMPLICIT: -4.9010355073085e-27*C_AIR*C_O2*C_O3P/Temp**2.8 + 1.0*C_NO2*J_0 - 8.0e-12*C_O3*C_O3P*exp(-2060.0/Temp)) + (EXPLICIT: 0)
d[OH]/dt = (IMPLICIT: -1.0*C_HNO3*C_OH*(1.9e-33*C_AIR*exp(725.0/Temp)/(4.63414634146341e-18*C_AIR*exp(-715.0/Temp) + 1.0) + 7.2e-15*exp(785.0/Temp))) + (EXPLICIT: 2.0*C_H2O2*J_3 + 1.0*C_HNO3*J_2 + 1.0*C_HONO*J_1)
d[HO2]/dt = (IMPLICIT: -1.0*C_HO2*(1.7e-33*C_AIR*exp(1000.0/Temp) + 2.3e-13*exp(600.0/Temp))) + (EXPLICIT: 0)
d[AIR]/dt = (IMPLICIT: 0) + (EXPLICIT: 0)
d[O2]/dt = (IMPLICIT: 0) + (EXPLICIT: 0)
d[H2O]/dt = (IMPLICIT: 0) + (EXPLICIT: 0)
d[M]/dt = (IMPLICIT: 0) + (EXPLICIT: 0)
d[N2]/dt = (IMPLICIT: 0) + (EXPLICIT: 0)
```

## Performance & Stiffness Diagnostics
The following species are the most heavily coupled (densest Jacobian rows). These dictate the performance ceiling of the Dense LU / ROS2 implicit solver block:

| Species | Non-Zero Dependencies |
|---------|-----------------------|
| NO3 | 8 |
| NO2 | 7 |
| O3 | 6 |
| NO | 5 |
| O3P | 5 |

### Warnings
- ⚠️ Mechanism contains complex pressure-dependent or empirical falloff rates which expand the AST depth significantly.
