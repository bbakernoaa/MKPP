# MKPP Mechanism Diagnostic Report: small_strato

## Overview
- **Total Species**: 7
- **Total Reactions**: 10

### Reaction Types Breakdown
- **PHOTOLYSIS**: 4
- **ARRHENIUS**: 6

### Stiffness Partitioning
- **Implicit (Stiff) Reactions**: 6
- **Explicit (Non-Stiff) Reactions**: 4
- **Graph Topology Status**: Mechanism contains cyclically dependent fast radicals. Tarjan SCC was applied.

## Generated SymPy Rate Expressions
Below are the exact algebraic AST expressions evaluated by SymPy for the Unified Jacobian.

```text
R1: PHOTOLYSIS | Reactants: ['O2'] | Products: ['O'] | A: 2.643E-10 * SUN*SUN*SUN
R2: ARRHENIUS | Reactants: ['O', 'O2'] | Products: ['O3'] | A: 8.018E-17
R3: PHOTOLYSIS | Reactants: ['O3'] | Products: ['O', 'O2'] | A: 6.120E-04 * SUN
R4: ARRHENIUS | Reactants: ['O', 'O3'] | Products: ['O2'] | A: 1.576E-15
R5: PHOTOLYSIS | Reactants: ['O3'] | Products: ['O1D', 'O2'] | A: 1.070E-03 * SUN*SUN
R6: ARRHENIUS | Reactants: ['O1D', 'M'] | Products: ['O', 'M'] | A: 7.110E-11
R7: ARRHENIUS | Reactants: ['O1D', 'O3'] | Products: ['O2'] | A: 1.200E-10
R8: ARRHENIUS | Reactants: ['NO', 'O3'] | Products: ['NO2', 'O2'] | A: 6.062E-15
R9: ARRHENIUS | Reactants: ['NO2', 'O'] | Products: ['NO', 'O2'] | A: 1.069E-11
R10: PHOTOLYSIS | Reactants: ['NO2'] | Products: ['NO', 'O'] | A: 1.289E-02 * SUN
d[O]/dt = (IMPLICIT: 7.11e-11*C_M*C_O1D - 1.069e-11*C_NO2*C_O + 1.0*C_NO2*J_3 - 8.018e-17*C_O*C_O2 - 1.576e-15*C_O*C_O3 + 2.0*C_O2*J_0 + 1.0*C_O3*J_1) + (EXPLICIT: 0)
d[O1D]/dt = (IMPLICIT: -7.11e-11*C_M*C_O1D - 1.2e-10*C_O1D*C_O3 + 1.0*C_O3*J_2) + (EXPLICIT: 0)
d[O3]/dt = (IMPLICIT: -6.062e-15*C_NO*C_O3 + 8.018e-17*C_O*C_O2 - 1.576e-15*C_O*C_O3 - 1.2e-10*C_O1D*C_O3 - 1.0*C_O3*J_1 - 1.0*C_O3*J_2) + (EXPLICIT: 0)
d[NO]/dt = (IMPLICIT: -6.062e-15*C_NO*C_O3 + 1.069e-11*C_NO2*C_O + 1.0*C_NO2*J_3) + (EXPLICIT: 0)
d[NO2]/dt = (IMPLICIT: 6.062e-15*C_NO*C_O3 - 1.069e-11*C_NO2*C_O - 1.0*C_NO2*J_3) + (EXPLICIT: 0)
d[M]/dt = (IMPLICIT: 0) + (EXPLICIT: 0)
d[O2]/dt = (IMPLICIT: 0) + (EXPLICIT: 0)
```

## Performance & Stiffness Diagnostics
The following species are the most heavily coupled (densest Jacobian rows). These dictate the performance ceiling of the Dense LU / ROS2 implicit solver block:

| Species | Non-Zero Dependencies |
|---------|-----------------------|
| O | 6 |
| O3 | 5 |
| NO | 4 |
| NO2 | 4 |
| O1D | 3 |

### Warnings
No major warnings.
