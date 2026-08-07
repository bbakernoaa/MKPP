---
type: howto
category: how_to
tags: [host-model, fortran, c, cpp, cmake, api]
---

# How-To: Integrating MKPP Generated Mechanisms into Host Models

This guide describes how to include MKPP generated chemical mechanism solvers into Fortran, C, and C++ host models (such as UFS, WRF-Chem, CESM, or standalone CCPP suites) with zero Python dependencies at host model compile or run time.

---

## 1. Ahead-Of-Time (AOT) Code Generation

During the preprocessing phase, run MKPP with `--host-api` to emit the AOT C++, C, and Fortran interface files:

```bash
python -m mkpp generate --mechanism example_mechanism.yaml --out-dir src/solvers --host-api
```

This generates:
- `mkpp.h` (C11 ABI header with opaque context handles and status codes)
- `mkpp_mod.f90` (Fortran 2018 module wrapping `iso_c_binding`)
- `mkpp.hpp` (Idiomatic C++17 RAII class wrapper `mkpp::MechanismContext`)
- `mkpp_c_api.cpp` (C ABI implementation wrapping Kokkos solver views)
- `<mechanism_name>.hpp` (Kokkos GPU/CPU ODE solver kernels)

---

## 2. CMake Integration

Host models link against the generated mechanism code using standard CMake targets exported by `mkpp_host`:

In your host model `CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.24)
project(my_host_model CXX Fortran C)

# Locate MKPP host API targets
find_package(MKPP REQUIRED COMPONENTS mkpp_host)

# Fortran host driver executable
add_executable(my_fortran_model main.f90)
target_link_libraries(my_fortran_model PRIVATE MKPP::mkpp_host)

# C host driver executable
add_executable(my_c_model main.c)
target_link_libraries(my_c_model PRIVATE MKPP::mkpp_host)

# C++ host driver executable
add_executable(my_cpp_model main.cpp)
target_link_libraries(my_cpp_model PRIVATE MKPP::mkpp_host)
```

---

## 3. Multi-Language Usage Examples

### Fortran Host Model (`main.f90`)

```fortran
program main
  use iso_c_binding
  use mkpp_mod
  implicit none

  integer, parameter :: num_cells = 100
  type(mkpp_handle_t) :: handle
  real(c_double), target :: conc(num_cells, MKPP_NUM_SPECIES)
  real(c_double), target :: temp(num_cells), pres(num_cells), rho(num_cells)
  real(c_double), target :: photo(num_cells, MKPP_NUM_PHOTOLYSIS)
  integer :: status, o3_idx

  ! 1. Create and initialize handle
  call mkpp_create_handle(handle, num_cells, status)
  call mkpp_initialize(handle, status)

  ! 2. Bind host model arrays zero-copy (Column-Major order)
  call mkpp_set_state_ptrs(handle, conc, temp, pres, rho, status)
  call mkpp_set_photolysis_ptrs(handle, photo, status)

  ! 3. Look up species index dynamically by name
  call mkpp_get_species_index(handle, "O3", o3_idx, status)

  ! 4. Step chemistry integration
  call mkpp_integrate(handle, 60.0d0, status)

  ! 5. Teardown context handle
  call mkpp_destroy_handle(handle, status)
end program main
```

- **Explanation**: Fortran 2D column-major arrays `conc(num_cells, num_species)` pass directly to `c_loc` without copying memory, mapping natively to C++/Kokkos `LayoutLeft` unmanaged views.

---

### C Host Model (`main.c`)

```c
#include <stdio.h>
#include <stdlib.h>
#include <mkpp.h>

int main(void) {
    size_t num_cells = 100;
    mkpp_handle_t handle = NULL;

    // 1. Create and initialize handle
    if (mkpp_create_handle(&handle, num_cells) != MKPP_SUCCESS) {
        return 1;
    }
    if (mkpp_initialize(handle) != MKPP_SUCCESS) {
        return 1;
    }

    // 2. Allocate and bind host state buffers
    double* conc = (double*)calloc(num_cells * MKPP_NUM_SPECIES, sizeof(double));
    double* temp = (double*)malloc(num_cells * sizeof(double));
    double* pres = (double*)malloc(num_cells * sizeof(double));
    double* rho  = (double*)malloc(num_cells * sizeof(double));

    mkpp_set_state_ptrs(handle, conc, temp, pres, rho);

    // 3. Step chemistry
    if (mkpp_integrate(handle, 60.0) != MKPP_SUCCESS) {
        char err[512];
        mkpp_get_last_error(handle, err, sizeof(err));
        printf("Integration error: %s\n", err);
    }

    // 4. Teardown
    mkpp_destroy_handle(handle);
    free(conc); free(temp); free(pres); free(rho);
    return 0;
}
```

---

### C++ Host Model (`main.cpp`)

```cpp
#include <iostream>
#include <vector>
#include <mkpp.hpp>

int main() {
    std::size_t num_cells = 100;
    mkpp::MechanismContext ctx(num_cells);
    ctx.initialize();

    std::size_t num_species = ctx.getSpeciesCount();
    std::vector<double> conc(num_cells * num_species, 1.0e-9);
    std::vector<double> temp(num_cells, 298.15);
    std::vector<double> pres(num_cells, 101325.0);
    std::vector<double> rho(num_cells, 2.45e19);

    ctx.setStatePointers(conc.data(), temp.data(), pres.data(), rho.data());
    ctx.integrate(60.0);

    std::cout << "C++ integration completed successfully.\n";
    return 0;
}
```

---

## 4. Key Performance Guarantees

- **Zero Python Dependency**: Host models compile and execute purely using standard C11, C++17, and Fortran 2018 toolchains.
- **Zero Heap Allocations in Integration Loop**: Scratch solver memory is allocated once during `mkpp_initialize()`.
- **Zero-Copy Memory Interoperability**: Host model concentration and meteorological arrays bind unmanaged views directly across language boundaries.
