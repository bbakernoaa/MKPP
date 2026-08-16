# MKPP Mechanism Diagnostic Report: carbon

## Overview
- **Total Species**: 11
- **Total Reactions**: 5

### Reaction Types Breakdown
- **ARRHENIUS**: 5

### Stiffness Partitioning
- **Implicit (Stiff) Reactions**: 5
- **Explicit (Non-Stiff) Reactions**: 0
- **Graph Topology Status**: Mechanism contains cyclically dependent fast radicals. Tarjan SCC was applied.

## Generated SymPy Rate Expressions
Below are the exact algebraic AST expressions evaluated by SymPy for the Unified Jacobian.

```text
R1: ARRHENIUS | Reactants: ['CH4', 'FixedOH'] | Products: ['LCH4byOH'] | A: 2.45e-12*exp(-1775.0e0/TEMP)
R2: ARRHENIUS | Reactants: ['CH4', 'FixedCl'] | Products: ['LCH4byCl'] | A: 9.60e-12*exp(-1360.0e0/TEMP)
R3: ARRHENIUS | Reactants: ['DummyCH4'] | Products: ['CO', 'PCOfromCH4'] | A: 4.2566446e-15
R4: ARRHENIUS | Reactants: ['CO', 'FixedOH'] | Products: ['LCObyOH'] | A: 7.3679649e-14
R5: ARRHENIUS | Reactants: ['DummyNMVOC'] | Products: ['CO', 'PCOfromNMVOC'] | A: 38199.012
d[CH4]/dt = (IMPLICIT: 0) + (EXPLICIT: 0)
d[CO]/dt = (IMPLICIT: -7.3679649e-14*C_CO*C_FixedOH + 4.2566446e-15*C_DummyCH4 + 38199.012*C_DummyNMVOC) + (EXPLICIT: 0)
d[PCOfromCH4]/dt = (IMPLICIT: 4.2566446e-15*C_DummyCH4) + (EXPLICIT: 0)
d[PCOfromNMVOC]/dt = (IMPLICIT: 38199.012*C_DummyNMVOC) + (EXPLICIT: 0)
d[LCH4byOH]/dt = (IMPLICIT: 1.0*2.45e-12*exp(-1775.0e0/TEMP)*C_CH4*C_FixedOH) + (EXPLICIT: 0)
d[LCH4byCl]/dt = (IMPLICIT: 1.0*9.60e-12*exp(-1360.0e0/TEMP)*C_CH4*C_FixedCl) + (EXPLICIT: 0)
d[LCObyOH]/dt = (IMPLICIT: 7.3679649e-14*C_CO*C_FixedOH) + (EXPLICIT: 0)
d[FixedOH]/dt = (IMPLICIT: -1.0*2.45e-12*exp(-1775.0e0/TEMP)*C_CH4*C_FixedOH - 7.3679649e-14*C_CO*C_FixedOH) + (EXPLICIT: 0)
d[FixedCl]/dt = (IMPLICIT: -1.0*9.60e-12*exp(-1360.0e0/TEMP)*C_CH4*C_FixedCl) + (EXPLICIT: 0)
d[DummyCH4]/dt = (IMPLICIT: -4.2566446e-15*C_DummyCH4) + (EXPLICIT: 0)
d[DummyNMVOC]/dt = (IMPLICIT: -38199.012*C_DummyNMVOC) + (EXPLICIT: 0)
```

## Performance & Stiffness Diagnostics
The following species are the most heavily coupled (densest Jacobian rows). These dictate the performance ceiling of the Dense LU / ROS2 implicit solver block:

| Species | Non-Zero Dependencies |
|---------|-----------------------|
| CO | 4 |
| FixedOH | 3 |
| LCH4byOH | 2 |
| LCH4byCl | 2 |
| LCObyOH | 2 |

### Warnings
No major warnings.
