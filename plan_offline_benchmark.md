# Plan: 24-Hour Offline Benchmark (MKPP vs KPP)

## Goal
Perform a fully fair, 1-to-1 offline 24-hour diurnal benchmark comparing legacy KPP against MKPP.

## The Architectural Difference
1. **MKPP**: As specified in the MKPP design, it handles the "full shebang" natively. It takes raw environmental state variables (Solar Zenith Angle, Temperature, Pressure, Humidity) via the `METEO_STRUCT`. The `PHOTOLYSIS` reaction types are evaluated continuously *inside* the Unified Jacobian as analytical expressions of SZA.
2. **Legacy KPP**: KPP cannot evaluate continuous photolysis logic internally. To give it a fair comparison, we must use an external driver (like Cloud-J) to pre-calculate the discrete $J$-rates for the exact same SZA timeline, and feed those updated $J$-rates into KPP's `RCONST` array at every time step.

## Proposed Implementation Steps

### Step 1: Update MKPP Codegen for Environmental Variables
Currently, `codegen.py` hardcodes `Temp = 300.0` and `SUN = 1.0` during the SymPy translation.
- **Action**: Update `codegen.py` to leave `Temp`, `Press`, `SZA`, etc., as free variables in the C++ output.
- **Action**: Update the C++ `SolverKernels` signature to accept a `meteo_view` or struct containing these environmental drivers alongside the `state` array.

### Step 2: Build the 24-Hour Diurnal C++ Test Runner
- **Action**: Modify `test_e2e_mechanisms.cpp` (or create `test_diurnal_benchmark.cpp`).
- **Action**: Write a loop `for (double t = 0; t < 86400; t += 60.0)` representing a 24-hour cycle.
- **Action**: At each step, calculate the current Solar Zenith Angle (SZA) and Temperature based on a standard diurnal curve (e.g., sunrise at hour 6, sunset at hour 18).

### Step 3: Implement the KPP "Cloud-J" Feed 
- **Action**: For the KPP baseline run, write a small Python script that uses the exact same diurnal curve (SZA, Temp) to calculate the discrete $J$-rates and Arrhenius rates at every 60-second interval.
- **Action**: Use `scipy.integrate.odeint` or a bundled legacy KPP executable to solve the 24-hour cycle, feeding it the discrete, stepped rates. This represents the legacy operator-split "Cloud-J feeding KPP" workflow.

### Step 4: Compare Performance and Accuracy
- **Action**: Run the C++ MKPP runner over the 24-hour cycle.
- **Action**: Compare the concentration outputs against the KPP baseline CSV.
- **Action**: Compare the total wall-clock integration time, demonstrating the performance difference of MKPP handling the continuous photolysis internally vs KPP struggling through the discrete rate shocks at the terminators.
