# Performance & Instruction Profiling Guide

This document provides a comprehensive guide to performance benchmarking, instruction profiling, regression tracking, and hot-path analysis for the Multiphase Kinetic PreProcessor (MKPP).

---

## Overview

MKPP includes a performance profiling and benchmarking suite designed to measure solver execution speed, track CPU instruction count deltas, and prevent performance regressions in continuous integration (CI).

The profiling framework consists of:
1. **Benchmark Binary (`mkpp_bench`)**: Unified C++ executable wrapping Kokkos solver loops with Valgrind Callgrind instrumentation macros.
2. **Wall-Clock Benchmarking (`scripts/bench_mkpp.sh`)**: Shell driver for measuring integration time and grid-cell throughput (`cell-st/s`).
3. **Callgrind Instruction Profiling (`scripts/profile_mkpp.sh`)**: Valgrind driver isolating and counting CPU instructions executed strictly during the integration loop.
4. **Profile Comparison Tool (`scripts/compare_profiles.py`)**: Python tool for comparing baseline vs PR instruction counts against configurable regression tolerance thresholds.
5. **CI Regression Gate (`.github/workflows/perf-regression.yml`)**: Automated PR workflow running side-by-side instruction comparison.

---

## Building the Benchmark Executable (`mkpp_bench`)

To build the `mkpp_bench` target, enable the CMake boolean option `MKPP_ENABLE_BENCHMARK`.

### Build Commands

```bash
# Configure build with benchmark target enabled
cmake -B build -DCMAKE_BUILD_TYPE=Release -DMKPP_ENABLE_BENCHMARK=ON

# Build the mkpp_bench executable
cmake --build build --target mkpp_bench --parallel
```

### Command-Line Arguments

The `mkpp_bench` executable accepts the following arguments:

| Argument | Description | Default | Allowed Values |
| :--- | :--- | :--- | :--- |
| `--mechanism` | Mechanism solver to benchmark | `chapman` | `chapman`, `gocart`, `saprc99`, `t1` |
| `--cells` | Number of independent grid cells | `1000` | Positive integer |
| `--steps` | Number of integration steps per cell | `10` | Positive integer |

#### Execution Example

```bash
./build/test/benchmark/mkpp_bench --mechanism chapman --cells 2000 --steps 5
```

Sample output:
```text
================================================================================
                         MKPP Solver Benchmark
================================================================================
Mechanism    : chapman
Grid Cells   : 2000
Steps / Cell : 5
Total Steps  : 10000
================================================================================
Initialization Time : 0.421 ms
Integration Time    : 1.253 ms
Total Time          : 1.674 ms
Throughput          : 7980845.97 cell-st/s
================================================================================
```

---

## Wall-Clock Benchmarking (`scripts/bench_mkpp.sh`)

The `scripts/bench_mkpp.sh` script automates wall-clock throughput measurements across all chemical mechanisms.

### Usage

```bash
./scripts/bench_mkpp.sh [build_dir] [cells] [steps]
```

- **`build_dir`**: Directory containing the built `mkpp_bench` binary (default: `build`).
- **`cells`**: Number of grid cells (default: `2000`).
- **`steps`**: Number of timesteps per cell (default: `5`).

### Example Run

```bash
./scripts/bench_mkpp.sh build 2000 5
```

Sample output:
```text
Mechanism   Cells   Steps   TotalTime_ms    IntegrationTime_ms  Throughput_cell_st_sec
chapman     2000    5       1.674           1.253               7980845.97
gocart      2000    5       2.105           1.520               6578947.37
saprc99     2000    5       5.820           4.910               2036659.88
t1          2000    5       8.430           7.120               1404494.38
```

---

## Callgrind Instruction Profiling (`scripts/profile_mkpp.sh`)

Wall-clock timing fluctuates due to CPU frequency scaling, thread scheduling, and system load. For deterministic performance tracking, MKPP uses **Valgrind Callgrind** instruction count profiling.

### Callgrind Instrumentation

`mkpp_bench` uses Callgrind macros (`CALLGRIND_START_INSTRUMENTATION` and `CALLGRIND_STOP_INSTRUMENTATION`) to ensure profiling is active **strictly** during the integration loop, excluding initialization, host allocation, and tear-down overhead.

### Usage

```bash
./scripts/profile_mkpp.sh [build_dir] [cells] [steps] [mechanism] [out_dir]
```

- **`build_dir`**: Directory containing `mkpp_bench` (default: `build`).
- **`cells`**: Grid cell count (default: `2000`).
- **`steps`**: Integration step count (default: `5`).
- **`mechanism`**: Target mechanism (`chapman`, `gocart`, `saprc99`, `t1`, or `all`).
- **`out_dir`**: Directory for Callgrind output files (default: `/tmp`).

### Example Run

```bash
./scripts/profile_mkpp.sh build 2000 5 all /tmp/perf
```

Sample output:
```text
Mechanism   Cells   Steps   InstructionCount
chapman     2000    5       12450123
gocart      2000    5       28910450
saprc99     2000    5       85120300
t1          2000    5       142300100
```

This also generates raw Callgrind output files (`cg_chapman.out`, `cg_gocart.out`, etc.) in the target output directory.

---

## Profile Comparison & Regression Gate (`scripts/compare_profiles.py`)

The `scripts/compare_profiles.py` script compares instruction counts between a baseline run and a pull request (PR) run to detect regressions.

### Usage

```bash
python3 scripts/compare_profiles.py <base_profile.tsv> <pr_profile.tsv> [--tolerance N.N]
```

- **`base_profile.tsv`**: Path to baseline instruction count summary file.
- **`pr_profile.tsv`**: Path to PR instruction count summary file.
- **`--tolerance`**: Maximum allowed percentage increase in instruction count before failing (default: `0.0`).

### Example Run

```bash
python3 scripts/compare_profiles.py /tmp/base_profile.tsv /tmp/pr_profile.tsv --tolerance 0.0
```

Sample output:
```text
========================================================================================
                      MKPP Instruction Profile Comparison
========================================================================================
Mechanism      Base Instr         PR Instr           Delta          Delta %    Status  
----------------------------------------------------------------------------------------
chapman        12,450,123         12,450,123         +0             +0.00%     PASS    
gocart         28,910,450         28,332,241         -578209        -2.00%     PASS    
saprc99        85,120,300         85,120,300         +0             +0.00%     PASS    
t1             142,300,100        142,300,100        +0             +0.00%     PASS    
========================================================================================
Tolerance threshold : 0.00%
Overall Status      : PASS (All mechanisms within tolerance)
========================================================================================
```

If instruction count increases beyond the `--tolerance` threshold, `compare_profiles.py` marks status as `REGRESSED` and exits with code `1`.

---

## Hot-Path Line Analysis with `callgrind_annotate`

When an instruction regression is detected or when optimizing a solver kernel, use `callgrind_annotate` to break down instruction counts line-by-line.

### Annotating Callgrind Output

```bash
# Run profiling to generate cg_chapman.out
./scripts/profile_mkpp.sh build 2000 5 chapman /tmp/perf

# Inspect hot functions and line-by-line instruction distribution
callgrind_annotate /tmp/perf/cg_chapman.out --auto=yes
```

### Key Areas to Inspect

1. **LU Decomposition & Substitution**: Check if matrix pivoting or fill-in operations cause unexpected instruction loops.
2. **Kinetics Rate Calculation**: Check rate constant evaluation for redundant transcendentals (`exp`, `pow`, `log`).
3. **Jacobian Construction**: Verify sparse matrix indexing and coefficient updating loops.
4. **Kokkos Team Operations**: Verify team thread range overhead inside GPU/CPU kernels.

---

## CI Performance Regression Gate

MKPP enforces performance regression checks in GitHub Actions via `.github/workflows/perf-regression.yml`.

### Workflow Execution

- **Trigger**: Runs on pull requests targeting `main` or `develop`.
- **Process**:
  1. Checks out `base` and `PR` branches side-by-side.
  2. Compiles `mkpp_bench` in Release mode for both branches.
  3. Executes `profile_mkpp.sh` under Valgrind Callgrind.
  4. Runs `compare_profiles.py` to verify zero instruction regression (`--tolerance 0.0`).
  5. Fails PR checks if any mechanism exhibits instruction regressions.
