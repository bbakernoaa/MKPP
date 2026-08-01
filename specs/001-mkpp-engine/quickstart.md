# MKPP Quickstart

## Prerequisites

- Python 3.11 environment configured for the repository.
- A CMake/Ninja toolchain available for the native runtime subproject under `src/exaero/`.
- Valid MICM mechanism and test-environment JSON definitions (e.g. `fixtures/micm-chapman/`).

## Validation Workflow

1. Run the compiler against the MICM mechanism and test environment.

```bash
python -m mkpp compile fixtures/micm-chapman/mechanism.json --test-env fixtures/micm-chapman/test_env.json --out build/mkpp-generated --emit-manifest
```

Expected outcome:

- The command exits with status `0`.
- Generated Kokkos C++ headers appear in `build/mkpp-generated/`.
- A manifest file records the emitted artifacts and zero-copy host interface bounds.

2. Build the native runtime consumer that will include the generated headers.

```bash
cmake -S src/exaero -B build/exaero -G Ninja
cmake --build build/exaero
```

3. Run the native test suite.

```bash
ctest --test-dir build/exaero --output-on-failure
```

4. Profile the Generated Solver (Register & Bandwidth Validation)

To ensure **SC-004** and **SC-005** compliance, profile the execution using NVIDIA Nsight Compute:

```bash
ncu --set full -o mkpp_profile build/exaero/test_mkpp_generated
ncu --csv --page details -i mkpp_profile.ncu-rep | grep -i "Registers Per Thread"
```

Expected outcome:
- **SC-004**: The output MUST show `<= 64` Registers Per Thread.
- **SC-005**: Memory throughput metric MUST show `> 80%`.