# MKPP Mechanism Diagnostic Report: chapman

## Overview
- **Total Species**: 4
- **Total Reactions**: 4

### Reaction Types Breakdown
- **PHOTOLYSIS**: 2
- **ARRHENIUS**: 2

### Stiffness Partitioning
- **Implicit (Stiff) Reactions**: 2
- **Explicit (Non-Stiff) Reactions**: 2
- **Graph Topology Status**: Mechanism contains cyclically dependent fast radicals. Tarjan SCC was applied.

## Generated SymPy Rate Expressions
Below are the exact algebraic AST expressions evaluated by SymPy for the Unified Jacobian.

```text
R1: PHOTOLYSIS | Reactants: ['O2'] | Products: ['O'] | A: 1e-05
R2: ARRHENIUS | Reactants: ['O', 'O2', 'M'] | Products: ['O3', 'M'] | A: 6e-34
R3: PHOTOLYSIS | Reactants: ['O3'] | Products: ['O', 'O2'] | A: 0.001
R4: ARRHENIUS | Reactants: ['O', 'O3'] | Products: ['O2'] | A: 8e-12
d[O]/dt = (IMPLICIT: -6.0e-34*C_M*C_O*C_O2 - 8.0e-12*C_O*C_O3 + 2.0*C_O2*J_0 + 1.0*C_O3*J_1) + (EXPLICIT: 0)
d[O2]/dt = (IMPLICIT: 0) + (EXPLICIT: 0)
d[O3]/dt = (IMPLICIT: 6.0e-34*C_M*C_O*C_O2 - 8.0e-12*C_O*C_O3 - 1.0*C_O3*J_1) + (EXPLICIT: 0)
d[M]/dt = (IMPLICIT: 0) + (EXPLICIT: 0)
```

## Performance & Stiffness Diagnostics
The following species are the most heavily coupled (densest Jacobian rows). These dictate the performance ceiling of the Dense LU / ROS2 implicit solver block:

| Species | Non-Zero Dependencies |
|---------|-----------------------|
| O | 4 |
| O3 | 4 |
| O2 | 0 |
| M | 0 |

### Warnings
No major warnings.
