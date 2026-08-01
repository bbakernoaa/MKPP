# Quickstart Validation Guide: E2E Solver Testing

This guide explains how to run the E2E verification for the MKPP AOT generation and Exaero solver integration.

### Prerequisites
- MKPP Python virtual environment (`python 3.14.6`)
- CMake 3.24+ and C++23 compiler
- Kokkos correctly installed

### Step 1: Run the MKPP AOT Compiler
First, parse the legacy Chapman cycle to ensure the generated C++ headers correctly mimic the legacy KPP baseline structurally.

```bash
mkpp parse tests/integration/e2e_validation/data/chapman.eqn --output build/mkpp-generated/ChapmanCycle.hpp
```

### Step 2: Compile the Exaero Test Harness
Build the C++ runner that will instantiate the generated headers and run the numerical integration.

```bash
cd build
cmake ..
make e2e_validation_runner
```

### Step 3: Run the Integration
Execute the box-model over a simulated 24-hour cycle.

```bash
./tests/integration/e2e_validation/e2e_validation_runner
```
*(This command outputs `exaero_output.csv` locally)*

### Step 4: Verify Against Legacy KPP
Use the Python verification fixture to compute RMSE and compare sparsity.

```bash
python3 tests/integration/e2e_validation/compare_baselines.py \
    --baseline tests/integration/e2e_validation/data/kpp_baseline_chapman.csv \
    --target exaero_output.csv
```
**Expected Outcome**: The script should output a `0` exit code, confirming that relative errors are below $10^{-6}$ and the Kokkos allocation hooks reported `0-bytes` copied.
