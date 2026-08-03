# Quickstart & Validation Guide: AOT Symbolic LU Kokkos ODE Solver

## Overview

This guide provides step-by-step instructions for running build-time code generation and verifying that the generated Kokkos ODE solver headers meet all architectural directives (zero thread-local arrays, zero runtime loops in linear solve, subview interface, and numerical precision).

---

## Prerequisites

1. Python 3.10+ with SymPy installed:
   ```bash
   python3 -m pip install sympy pytest
   ```
2. C++20 compiler with Kokkos or C++ test runner.

---

## Step 1: Code Generation Validation

Generate C++ solver headers for test mechanisms (e.g., `chapman` or `saprc99`):

```bash
python3 -c "
from mkpp.model import MechanismDefinition, Species, Reaction
from mkpp.lowering import build_sympy_matrices
from mkpp.codegen import generate_headers

# Load mechanism and build symbolic matrices
mech = MechanismDefinition.from_kpp('mechanisms/chapman.kpp')
build_sympy_matrices(mech)

# Generate C++ header
generate_headers(mech, out_dir='build/generated_solvers')
print('Successfully generated header!')
"
```

---

## Step 2: Verification of Architectural Directives

### 1. Verify Zero Local Thread Arrays (`SC-001`, `FR-003`)
Inspect generated header in `build/generated_solvers/chapman.hpp`:

```bash
grep -E "double (Jac|W|F1|F2|K1|K2|Ynew)\[" build/generated_solvers/chapman.hpp
```
**Expected Output**: Empty (0 matches). All thread-local arrays are eliminated.

### 2. Verify Zero Loops in Matrix Solve (`SC-002`, `FR-002`)
Check `integrate`, `lu_decompose`, and `lu_solve` sections in `chapman.hpp`:

```bash
grep -n "for (" build/generated_solvers/chapman.hpp
```
**Expected Output**: Zero loops inside solver execution routines (`integrate`, `lu_decompose`, `lu_solve`).

### 3. Verify No Raw Pointers (`SC-003`, `FR-004`)
Check function signatures:

```bash
grep -E "void (integrate|compute_rates|compute_jacobian)\(" build/generated_solvers/chapman.hpp
```
**Expected Output**: Functions use templated view parameters (`const StateView& state`, `RateView& rates`) instead of `double*`.

---

## Step 3: Run Automated Test Suite

Execute pytest validation suite:

```bash
pytest tests/test_codegen_symbolic_lu.py -v
```

**Expected Outcome**: All tests pass, confirming:
- Symbolic sparse LU factorization builds correct forward/backward substitution scalar expressions.
- Generated C++ code compiles cleanly under GCC/Clang/NVCC.
- Numerical integration matches dense reference Rosenbrock-2 solver results with $< 10^{-12}$ relative difference.
