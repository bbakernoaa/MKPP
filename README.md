# Multiphase Kinetic PreProcessor (MKPP / FKPP) Engine

MKPP (Futuristic Kinetic PreProcessor) is a highly optimized, Ahead-Of-Time (AOT) Python compiler that translates atmospheric chemistry mechanisms (defined via OpenAtmos YAML) into Exascale-ready block-sparse Kokkos C++ headers for a Unified Jacobian using SymPy.

## NOAA NWS Office of Modeling and Development

To design, build, integrate, and optimize robust scientific software, high-performance computing (HPC) software pipelines, and numerical weather prediction (NWP) systems that protect life and property.

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

## Governance

Development on this project is governed by the [FKPP Constitution](.specify/memory/constitution.md). All contributors must adhere to its core principles including:
- Clarity Over Cleverness
- Defensive Programming
- Fail Fast, Fail Loudly
- High-Performance Computing & Message Passing (MPI) considerations
- GPU Acceleration & Kokkos constraints
- Zero-Copy Data Interoperability
- Scientific Hygiene & Determinism

See the Constitution and `.github/copilot-instructions.md` for complete guidelines.

## License

This project is part of NOAA-EMC Ecosystem.
See LICENSE and DISCLAIMER for details.
