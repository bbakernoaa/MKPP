# Design Document: Multi-Solver Support

## Overview

This design extends MKPP's code generation pipeline to support five Rosenbrock solvers (Ros2, Ros3, Ros4, Rodas3, Rodas4) selectable via a `--solver` CLI flag. The architecture stores all coefficient tableaux in a single authoritative dictionary within `codegen.py` and refactors the integrator emission into a generic function that unrolls the correct number of stages at code-generation time. The LU plan remains solver-independent since the Jacobian sparsity pattern is a property of the mechanism, not the solver.

## Architecture

### Component Diagram

```
┌──────────┐        ┌────────────┐        ┌────────────────┐
│  cli.py  │──────▶ │  codegen.py │──────▶ │  Generated .hpp │
│ --solver │        │             │        │                │
└──────────┘        │ SOLVER_COEF │        │  integrate()   │
                    │ FICIENTS    │        │  integrate_    │
                    │ dict        │        │  with_reduc..  │
                    │             │        └────────────────┘
                    │ emit_rosen- │
                    │ brock_      │
                    │ stages()    │
                    └────────────┘
                          │
                          ▼
                    ┌────────────┐
                    │ lowering.py │  (unchanged — LU plan is solver-independent)
                    └────────────┘
```

### Data Flow

1. User invokes `mkpp compile mechanism.yaml --test-env env.yaml --solver rodas3`
2. `cli.py` validates `--solver` against the allowed set, defaults to `ros3` if omitted
3. `run_compiler()` passes the solver name to `generate_headers()`
4. `codegen.py` looks up the coefficient tableau from `SOLVER_COEFFICIENTS[solver_name]`
5. The generic `_emit_rosenbrock_stages()` function unrolls S stages, referencing the tableau arrays for A, C, M, E, Gamma, NewF, and ELO
6. The same LU plan (forward/backward substitution steps) is reused for every stage solve across all solvers

## Components

### 1. CLI Layer (`cli.py`)

**Changes:**

- Add `--solver` argument to the `compile` subparser with `choices=["ros2", "ros3", "ros4", "rodas3", "rodas4"]` and `default="ros3"`
- Add `solver: str = "ros3"` parameter to `run_compiler()`
- Pass `solver_name` to `generate_headers()`

```python
compile_parser.add_argument(
    "--solver",
    choices=["ros2", "ros3", "ros4", "rodas3", "rodas4"],
    default="ros3",
    help="Rosenbrock solver method (default: ros3)"
)
```

Since `argparse.choices` handles validation and error messaging natively, invalid values will produce a non-zero exit with a message listing valid choices — no custom validation needed.

### 2. Coefficient Tableau Storage (`codegen.py`)

**Data Structure:**

```python
from dataclasses import dataclass
from typing import List

@dataclass(frozen=True)
class RosenbrockTableau:
    """Immutable coefficient tableau for a Rosenbrock solver."""
    name: str
    stages: int
    A: List[float]       # Strictly lower-triangular, row-wise: A(2,1), A(3,1), A(3,2), ...
    C: List[float]       # Same storage as A
    M: List[float]       # Solution update weights, length = stages
    E: List[float]       # Error estimate weights, length = stages
    Alpha: List[float]   # Stage time offsets, length = stages
    Gamma: List[float]   # Gamma sums, length = stages
    NewF: List[bool]     # Whether stage i needs a fresh F evaluation
    ELO: float           # Estimator of local order (main + embedded + 1)

SOLVER_COEFFICIENTS: dict[str, RosenbrockTableau] = {
    "ros2": RosenbrockTableau(
        name="ROS-2",
        stages=2,
        A=[1.7071067811865475244],  # 1/g where g = 1 + 1/sqrt(2)
        C=[-1.1715728752538099024],  # -2/g
        M=[0.87867965644035742774, 0.29289321881345247560],  # 3/(2g), 1/(2g)
        E=[0.29289321881345247560, 0.29289321881345247560],  # 1/(2g), 1/(2g)
        Alpha=[0.0, 1.0],
        Gamma=[1.7071067811865475244, -1.7071067811865475244],  # g, -g
        NewF=[True, True],
        ELO=2.0,
    ),
    "ros3": RosenbrockTableau(
        name="ROS-3",
        stages=3,
        A=[1.0, 1.0, 0.0],
        C=[-1.0156171083877702092, 4.0759956452537699825, 9.2076794298330791242],
        M=[1.0, 6.1697947043828245593, -0.42772256543218573326],
        E=[0.5, -2.9079558716805469822, 0.22354069897811569627],
        Alpha=[0.0, 0.43586652150845899942, 0.43586652150845899942],
        Gamma=[0.43586652150845899942, 0.24291996454816804367, 2.1851380027664058512],
        NewF=[True, True, False],
        ELO=3.0,
    ),
    "ros4": RosenbrockTableau(
        name="ROS-4",
        stages=4,
        A=[2.0, 1.867943637803922, 0.2344449711399156,
           1.867943637803922, 0.2344449711399156, 0.0],
        C=[-7.137615036412310, 2.580708087951457, 0.6515950076447975,
           -2.137148994382534, -0.3214669691237626, -0.6949742501781779],
        M=[2.255570073418735, 0.2870493262186792,
           0.4353179431840180, 1.093502252409163],
        E=[-0.2815431932141155, -0.07276199124938920,
           -0.1082196201495311, -1.093502252409163],
        Alpha=[0.0, 1.145640000000000, 0.6552168638155900, 0.6552168638155900],
        Gamma=[0.5728200000000000, -1.769193891319233,
               0.7592633437920482, -0.1049021087100450],
        NewF=[True, True, True, False],
        ELO=4.0,
    ),
    "rodas3": RosenbrockTableau(
        name="RODAS-3",
        stages=4,
        A=[0.0, 2.0, 0.0, 2.0, 0.0, 1.0],
        C=[4.0, 1.0, -1.0, 1.0, -1.0, -8.0/3.0],
        M=[2.0, 0.0, 1.0, 1.0],
        E=[0.0, 0.0, 0.0, 1.0],
        Alpha=[0.0, 0.0, 1.0, 1.0],
        Gamma=[0.5, 1.5, 0.0, 0.0],
        NewF=[True, False, True, True],
        ELO=3.0,
    ),
    "rodas4": RosenbrockTableau(
        name="RODAS-4",
        stages=6,
        A=[1.544000000000000,
           0.9466785280815826, 0.2557011698983284,
           3.314825187068521, 2.896124015972201, 0.9986419139977817,
           1.221224509226641, 6.019134481288629, 12.53708332932087, -0.6878860361058950,
           1.221224509226641, 6.019134481288629, 12.53708332932087, -0.6878860361058950, 1.0],
        C=[-5.668800000000000,
           -2.430093356833875, -0.2063599157091915,
           -0.1073529058151375, -9.594562251023355, -20.47028614809616,
            7.496443313967647, -10.24680431464352, -33.99990352819905, 11.70890893206160,
            8.083246795921522, -7.981132988064893, -31.52159432874371, 16.31930543123136, -6.058818238834054],
        M=[1.221224509226641, 6.019134481288629, 12.53708332932087, -0.6878860361058950, 1.0, 1.0],
        E=[0.0, 0.0, 0.0, 0.0, 0.0, 1.0],
        Alpha=[0.0, 0.386, 0.210, 0.630, 1.0, 1.0],
        Gamma=[0.2500000000000000, -0.1043000000000000,
               0.1035000000000000, -0.03620000000000023, 0.0, 0.0],
        NewF=[True, True, True, True, True, True],
        ELO=4.0,
    ),
}
```

**Indexing Convention:**

The A and C arrays use KPP's row-wise strictly-lower-triangular storage. To access element `A(i, j)` (1-indexed stages): `A[(i-1)*(i-2)//2 + j - 1]`. This matches the Fortran reference exactly.

### 3. Generic Rosenbrock Stage Emission (`codegen.py`)

A new internal function `_emit_rosenbrock_stages()` replaces the current hardcoded 3-stage logic:

```python
def _emit_rosenbrock_stages(
    f,              # File handle
    tableau: RosenbrockTableau,
    N: int,         # Number of species
    lu_plan,        # Symbolic LU plan
    sympy_meta,     # Mechanism metadata
    mech,           # Mechanism definition
    perm,           # Species permutation (or None)
    is_reduction: bool = False,  # Whether this is the reduction variant
) -> None:
    """Emit fully-unrolled Rosenbrock stage computations for any supported solver."""
```

**Stage Loop Unrolling Pattern (Python-time loop, C++-time scalar code):**

```python
for stage in range(1, tableau.stages + 1):
    # 1. Compute intermediate state Y_stage if stage > 1
    #    Y_stage[i] = S_i + sum(A(stage,j) * K_j[i] for j in 1..stage-1)

    # 2. Evaluate F_stage if NewF[stage-1] is True, else reuse F_{stage-1}

    # 3. Form RHS: rhs_stage[i] = F_stage[i] + sum(C(stage,j)/dt * K_j[i] for j in 1..stage-1)
    #    (For stage 1: rhs = F1, the C sum is empty)

    # 4. Solve W * K_stage = rhs_stage using the pre-computed LU plan
    #    (forward substitution then backward substitution, same code for all stages)
```

Each iteration of this Python loop emits C++ lines with stage-specific variable names (e.g., `K2_0`, `Y3_5`, `F4_2`), ensuring full compile-time unrolling with no runtime loops over stages.

### 4. Solution Update and Error Estimation

After all stages are computed:

```python
# Solution update: Ynew[i] = S_i + sum(M[j] * K_{j+1}[i] for j in range(stages))
# Error estimate:  Yerr[i] = sum(E[j] * K_{j+1}[i] for j in range(stages))
# L2 norm with scaling: err_norm = sqrt(sum((Yerr[i]/sci[i])^2) / N)
# Step control exponent: 1/ELO
```

Generated C++ for step control:

```cpp
// For ros4 (ELO=4): exponent = 0.25
double factor = safety * Kokkos::pow(err_norm, -0.25);
factor = Kokkos::fmax(min_shrink, Kokkos::fmin(factor, max_growth));
```

The exponent `1/ELO` is computed at Python time and emitted as a literal constant — no runtime division.

### 5. W Matrix Construction

The system matrix W is identical for all stages within one step:

```
W = (1 / (gamma * dt)) * I - J
```

where `gamma = Gamma[0]` (the first element of the Gamma array, which equals the diagonal γ used in all Rosenbrock methods). This is solver-dependent only in the value of gamma — the sparsity structure and LU factorization plan are mechanism-dependent and shared across all solvers.

### 6. Function Signatures (Unchanged)

Both `integrate()` and `integrate_with_reduction()` retain their existing template signatures:

```cpp
template <class StateView>
KOKKOS_INLINE_FUNCTION void integrate(double dt_total, StateView& state, const double* jvals) const;

template <class StateView>
KOKKOS_INLINE_FUNCTION void integrate_with_reduction(
    double dt_total, StateView& state, const double* jvals, double importance_threshold) const;
```

The solver choice affects only the body of these functions, not their interface.

### 7. `generate_headers()` Interface Change

```python
def generate_headers(
    mech: MechanismDefinition,
    out_dir: str = "src/solvers",
    suffix: str = "",
    solver_name: str = "ros3",  # NEW parameter
) -> Dict[str, str]:
```

## Interfaces

### CLI Interface

| Flag | Type | Default | Description |
|------|------|---------|-------------|
| `--solver` | choice | `ros3` | Rosenbrock solver selection |

Valid choices: `ros2`, `ros3`, `ros4`, `rodas3`, `rodas4`

### Internal Python Interface

```python
# Access a tableau
tableau = SOLVER_COEFFICIENTS["rodas4"]
assert tableau.stages == 6
assert len(tableau.M) == 6
assert tableau.ELO == 4.0

# A(i,j) access helper (1-indexed i,j; i > j)
def get_A(tableau: RosenbrockTableau, i: int, j: int) -> float:
    """Get A(i,j) from row-wise lower-triangular storage. i,j are 1-indexed."""
    return tableau.A[(i - 1) * (i - 2) // 2 + j - 1]

def get_C(tableau: RosenbrockTableau, i: int, j: int) -> float:
    """Get C(i,j) from row-wise lower-triangular storage. i,j are 1-indexed."""
    return tableau.C[(i - 1) * (i - 2) // 2 + j - 1]
```

## Data Models

### RosenbrockTableau

| Field | Type | Constraint |
|-------|------|-----------|
| `name` | `str` | Human-readable solver name |
| `stages` | `int` | 2, 3, 4, or 6 |
| `A` | `List[float]` | Length = stages*(stages-1)/2 |
| `C` | `List[float]` | Length = stages*(stages-1)/2 |
| `M` | `List[float]` | Length = stages |
| `E` | `List[float]` | Length = stages |
| `Alpha` | `List[float]` | Length = stages |
| `Gamma` | `List[float]` | Length = stages |
| `NewF` | `List[bool]` | Length = stages |
| `ELO` | `float` | Positive integer value (2, 3, or 4) |

**Invariant:** `len(A) == len(C) == stages * (stages - 1) // 2`

### Solver Selection Flow

```
CLI --solver arg
       │
       ▼
argparse validation (choices enum)
       │
       ▼
run_compiler(solver=...)
       │
       ▼
generate_headers(solver_name=...)
       │
       ▼
tableau = SOLVER_COEFFICIENTS[solver_name]
       │
       ▼
_emit_rosenbrock_stages(tableau, ...)
```

## Error Handling

| Scenario | Handler | Behavior |
|----------|---------|----------|
| Invalid `--solver` value | `argparse` | Exit 2, print usage with valid choices |
| Unknown solver name in codegen | `KeyError` → `CompilationError` | Exit 1, structured JSON error |
| Tableau array length mismatch | `assert` at module load | Fail fast during import with `AssertionError` |
| Missing LU plan | Existing fallback | Compute LU on-the-fly from Jacobian |

## Performance Considerations

- **Code size**: Higher-stage solvers (Rodas4 = 6 stages) produce ~3× more C++ lines than Ros2. This is acceptable for GPU register-based execution where instruction-level parallelism dominates.
- **Compilation time**: The generated C++ file grows linearly with stage count. For Rodas4 with a 20-species mechanism, expect ~1200 additional lines vs Ros3.
- **Runtime**: More stages per step means fewer total steps for the same accuracy, which typically reduces wall-clock time for stiff problems despite more work per step.

## Correctness Properties

*A property is a characteristic or behavior that should hold true across all valid executions of a system — essentially, a formal statement about what the system should do. Properties serve as the bridge between human-readable specifications and machine-verifiable correctness guarantees.*

### Property 1: Solver name validation is exhaustive

*For any* string `s`, the CLI accepts `s` as a valid `--solver` value if and only if `s` is in the set `{"ros2", "ros3", "ros4", "rodas3", "rodas4"}`.

**Validates: Requirements 1.1, 1.3**

### Property 2: Tableau structural consistency

*For any* solver name in the valid set, the corresponding `RosenbrockTableau` entry satisfies: `len(A) == len(C) == stages*(stages-1)//2` and `len(M) == len(E) == len(Alpha) == len(Gamma) == len(NewF) == stages`.

**Validates: Requirements 2.1, 2.2**

### Property 3: Coefficient precision preservation

*For any* floating-point coefficient value in any stored tableau, its string representation contains at least 16 significant decimal digits.

**Validates: Requirements 2.3**

### Property 4: Stage count matches generated code

*For any* solver and any mechanism, the generated `integrate()` function contains exactly `tableau.stages` forward/backward substitution blocks (one per stage solve).

**Validates: Requirements 3.1, 5.3**

### Property 5: NewF=false reuses prior function evaluation

*For any* solver and any stage `i` where `NewF[i]` is false, the generated code for stage `i+1` does not emit a new rate computation but reuses the function evaluation variable from stage `i`.

**Validates: Requirements 3.2**

### Property 6: Generated coefficients match tableau

*For any* solver, the M, E, A, C, and Gamma[0] coefficient literals emitted in the generated C++ code are numerically equal (within floating-point representation) to the values stored in `SOLVER_COEFFICIENTS[solver_name]`.

**Validates: Requirements 3.3, 3.4, 3.5, 3.6, 3.7**

### Property 7: Step-size exponent matches ELO

*For any* solver, the step-size control exponent emitted in the generated code equals `1.0 / tableau.ELO`.

**Validates: Requirements 4.1, 4.2, 4.3**

### Property 8: GPU safety invariants

*For any* solver and any mechanism, the generated `integrate()` code contains no dynamic allocations (`new`, `malloc`, `std::vector`), no runtime-indexed stage arrays, and includes the `KOKKOS_INLINE_FUNCTION` annotation.

**Validates: Requirements 5.1, 5.2, 5.3, 5.4**

### Property 9: Reduction integrator consistency

*For any* solver, the coefficient literals, stage count, and error exponent in `integrate_with_reduction()` are identical to those in `integrate()`.

**Validates: Requirements 6.1, 6.2**

### Property 10: LU plan independence from solver choice

*For any* two solvers applied to the same mechanism, the symbolic LU factorization expressions (L and U entries) in the generated code are identical.

**Validates: Requirements 7.2, 7.3**

### Property 11: Function signature invariance

*For any* solver, the template signature of `integrate()` and `integrate_with_reduction()` in the generated header is identical (same parameter types and annotations).

**Validates: Requirements 8.3**
