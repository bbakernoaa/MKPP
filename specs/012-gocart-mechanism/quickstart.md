# Quickstart Validation: GOCART Mechanism

## 1. Setup
Ensure you are in the MKPP repository root.
Activate the python environment:
```bash
source .venv/bin/activate
```

## 2. Parse the YAML
Run the MKPP parser to validate the mechanism definition:
```bash
python3 -m mkpp.parse mechanisms/gocart.yaml
```
Expected output: Success message indicating all species and reactions were loaded correctly, with 0 emissions or saltation fluxes detected.

## 3. Generate Code
Run the MKPP C++ code generator:
```bash
python3 -m mkpp.codegen mechanisms/gocart.yaml --outdir mkpp-generated/
```
Expected output: The generation of `gocart.hpp` and `gocart_reduced.hpp` in the `mkpp-generated/` directory without any compilation errors or SymPy differentiation failures.

## 4. Compile the Solver
Compile the generated headers with the mock C++ host driver to ensure register pressure and syntax correctness:
```bash
mkdir -p build && cd build
cmake ..
make mkpp_host
```
Expected output: Successful compilation.
