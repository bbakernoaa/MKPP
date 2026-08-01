# Quickstart Validation Guide: Exaero Auxiliary Engines

## Prerequisites
- CMake 3.20+
- C++23 compliant compiler (e.g., GCC 13+)
- Fortran 2008+ compliant compiler (e.g., gfortran)
- Kokkos Core installed and visible to CMake

## Validation Scenario 1: Disabled Auxiliary Engines
Ensure that compiling without the engines results in a successful build without linking the Fortran libraries.

```bash
# 1. Configure the build with engines disabled
mkdir -p build/exaero_disabled && cd build/exaero_disabled
cmake ../../src/exaero -DEXAERO_ENABLE_CLOUDJ=OFF -DEXAERO_ENABLE_ISORROPIA_LITE=OFF

# 2. Build the utility
make -j4

# 3. Verify linkage (Linux)
# The binary should NOT link to any Cloud-J or ISORROPIA objects.
ldd bin/exaero | grep cloudj || echo "Success: Cloud-J not linked"
```

## Validation Scenario 2: Enabled Engines & Zero-Copy Execution
Ensure the engines compile, link, and the integration tests verify memory correctness.

```bash
# 1. Configure the build with engines enabled
mkdir -p build/exaero_enabled && cd build/exaero_enabled
cmake ../../src/exaero -DEXAERO_ENABLE_CLOUDJ=ON -DEXAERO_ENABLE_ISORROPIA_LITE=ON

# 2. Build the utility
make -j4

# 3. Run the memory validation integration test
# This test specifically allocates a LayoutLeft view and asserts that
# the Fortran engine modifies the memory identically without copies.
ctest -R test_engine_dispatch --output-on-failure
```

## Expected Outcomes
- The `exaero` target builds successfully under both CMake configurations.
- Execution of the binary in the enabled state dispatches the workload to the GPU using Kokkos `TeamPolicy` and reports zero memory transfer bottlenecks between the C++ driver and the Fortran hooks.
