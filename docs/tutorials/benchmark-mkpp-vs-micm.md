---
type: tutorial
category: tutorials
tags: [benchmark, micm, c++, performance]
---

# Benchmarking MKPP against MICM

This tutorial walks you through executing the direct C++ side-by-side performance benchmark comparing the **MKPP Ahead-Of-Time (AOT) Kokkos Solvers** against the **NCAR/MICM C++ Library**.

We will configure CMake to fetch the `libmicm` library directly from GitHub, build the side-by-side benchmark executable, and run a standard Chapman mechanism scenario (1,000 cells x 100 timesteps) to compare solver throughput.

## Prerequisites

Before running this benchmark, ensure your system has the following installed:
- Python 3.10+ (with `sympy` and `pyyaml`)
- CMake 3.24+
- A C++20 compliant compiler (e.g., GCC 11+, Clang 14+)
- OpenMP development headers
- Git (for CMake `FetchContent`)

## Step 1: Generate MKPP AOT Headers

The benchmark binary links directly against MKPP's generated C++ header files. First, ensure the `mkpp-generated/` directory is populated with up-to-date headers.

Run the AOT compiler against the Chapman mechanism:

```bash
python3 -m mkpp.cli compile mechanisms/chapman.yaml --out mkpp-generated/ --solver ros3
```

This generates `mkpp-generated/chapman.hpp`, which contains the fully unrolled, symbolic Jacobian and Doolittle factorization for the Chapman cycle.

## Step 2: Configure CMake for the Benchmark

By default, the MICM benchmark is disabled to prevent unnecessary downloads during regular builds. You must enable the `-DMKPP_ENABLE_MICM_COMPARE=ON` CMake flag. This flag triggers CMake `FetchContent` to download the `NCAR/micm` repository and compiles it as a static library dependency.

From the root of the MKPP repository, run:

```bash
cmake -B build -DMKPP_ENABLE_MICM_COMPARE=ON -DBUILD_TESTING=ON
```

*Note: Depending on your system and compiler, you may need to specify your compiler explicitly if CMake fails to locate OpenMP (e.g., `CXX=g++ cmake -B build ...`).*

## Step 3: Build the Benchmark Executable

Once configured, build the `benchmark_mkpp_vs_micm` target:

```bash
cmake --build build --target benchmark_mkpp_vs_micm
```

This step compiles:
1. The `libmicm` library headers.
2. The `mkpp_host` C++ shim interface.
3. The `benchmark_mkpp_vs_micm.cpp` application.

## Step 4: Run the Benchmark

Execute the compiled binaries from the command line:

```bash
# Run Chapman Benchmark (4 species, 4 reactions)
./build/tests/integration/e2e_validation/benchmark_mkpp_vs_micm

# Run T1 Mechanism Benchmark (210 species, 547 reactions)
./build/tests/integration/e2e_validation/benchmark_mkpp_vs_micm_t1
```

### Understanding the Output

#### 1. Chapman Mechanism (4 Species, 4 Reactions, 1,000 cells x 100 steps)
```text
==========================================================================
      Direct C++ Benchmark: MKPP vs NCAR/MICM (Chapman Mechanism)
==========================================================================
Grid Cells : 1000
Timesteps  : 100
Step Size  : 60 s

Metric                      MKPP C++ (AOT)    MICM C++          Speedup
--------------------------------------------------------------------------------
Execution Time (ms)         10.10             299.32            29.63x
Throughput (cell-st/s)      9.90e+06          3.34e+05          --
==========================================================================
```

#### 2. T1 Mechanism (210 Species, 547 Reactions, 1,000 cells x 10 steps)
```text
==========================================================================
      Direct C++ Benchmark: MKPP vs NCAR/MICM (T1 Mechanism)
==========================================================================
Species    : 210
Reactions  : 547
Grid Cells : 1000
Timesteps  : 10
Step Size  : 60 s

Metric                      MKPP C++ (AOT)    MICM C++          Speedup
--------------------------------------------------------------------------------
Execution Time (ms)         372.83            2370.77           6.36x
Throughput (cell-st/s)      2.68e+04          4.22e+03          --
==========================================================================
```

### Why MKPP is Faster

If you look closely at the source code of the benchmark (`tests/integration/e2e_validation/benchmark_mkpp_vs_micm.cpp`), you will notice the structural differences in how the two libraries operate:

1. **MICM (Runtime Assembly)**:
   MICM dynamically allocates state objects, evaluates generalized sparse matrices in loops, and resolves generic rate constants during the time integration loop.

2. **MKPP (Compile-Time Symbolic Unrolling)**:
   MKPP hoists the cell state into scalar registers, computes the exact symbolic non-zero Jacobian operations sequentially, and executes a branch-free Doolittle LU factorization natively on the CPU/GPU.

## (Optional) Step 5: Automated Python Wrapper

If you want to run the automated Python/SciPy Radau ODE accuracy benchmarking script (which validates numerical accuracy against SciPy and profiles instruction counts using Callgrind), you can use the provided wrapper script:

```bash
./scripts/compare_micm.sh
```

This runs `compare_micm.py` across all default mechanisms and exports the results to `reports/micm_comparison.md`.