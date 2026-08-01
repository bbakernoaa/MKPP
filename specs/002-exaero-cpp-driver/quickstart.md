# Exaero C++ Driver Quickstart

## Prerequisites
- A mechanism compiled via the MKPP Python tool (e.g. `python -m mkpp compile ... --out build/mkpp-generated`).
- A host C++ or Fortran application capable of linking to static libraries.

## Build the Library

The build requires specifying which generated mechanisms to compile into the registry via CMake flags.

```bash
mkdir build && cd build
cmake -G Ninja \
    -DEXAERO_MECHANISMS="ChapmanCycle" \
    -DMKPP_INCLUDE_DIR="../build/mkpp-generated" \
    ../src/exaero
ninja
```

## Validate via Tests

Run the built-in CTest suite to verify that sorting and registry dispatch logic operates flawlessly on your architecture.

```bash
ctest --output-on-failure
```

Expected Output:
*   The `test_registry` passes, successfully rejecting unregistered mechanisms.
*   The `test_sorter` passes, confirming zero dynamic allocations occurred during the sort step.
