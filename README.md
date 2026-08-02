# Multiphase Kinetic PreProcessor (MKPP) Engine

MKPP is a highly optimized, block-sparse Kokkos C++ chemistry solver generator that translates atmospheric chemistry mechanisms (defined via OpenAtmos YAML) into Exascale-ready Kokkos C++ headers using SymPy.

## Mechanisms Included
- **Chapman Cycle** (`chapman.yaml`)
- **Small Stratospheric** (`small_strato.yaml`)
- **Carbon** (`carbon.yaml`)
- **GOCART** (`gocart.yaml`)
- **SAPRC** mechanisms (`saprc99.yaml`, `saprcnov.yaml`)

## Building and Testing
```bash
python3 -m venv .venv
source .venv/bin/activate
pip install -e .
mkdir build && cd build
cmake ..
ninja
ctest
```

## License

This project is part of NOAA-EMC Ecosystem. 
See LICENSE and DISCLAIMER for details.
