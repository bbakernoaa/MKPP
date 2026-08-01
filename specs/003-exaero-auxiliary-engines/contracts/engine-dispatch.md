# Contract: Engine Dispatch Interoperability

This contract defines how the C++ Exaero Utility interfaces with Fortran auxiliary engines.

## 1. Fortran API Signatures

The Fortran subroutines (e.g., Cloud-J) must expose a standard `bind(C)` interface to prevent name mangling issues.

```fortran
! Example target interface in Fortran
subroutine cloudj_driver(n_cells, n_species, state_array, rates_array) bind(C, name="cloudj_driver")
  use iso_c_binding, only: c_int, c_double
  implicit none
  integer(c_int), value :: n_cells, n_species
  real(c_double), intent(in) :: state_array(n_cells, n_species)
  real(c_double), intent(out) :: rates_array(n_cells, n_species)
end subroutine
```

## 2. C++ API Declarations

The C++ code must declare these subroutines as `extern "C"` and pass raw memory pointers extracted from the unmanaged `Kokkos::View` or `std::mdspan` objects.

```cpp
extern "C" {
    void cloudj_driver(int n_cells, int n_species, const double* state_array, double* rates_array);
}

// C++ Wrapper Interface
namespace exaero {
    void dispatch_cloudj(
        Kokkos::View<const double**, Kokkos::LayoutLeft, Kokkos::MemoryTraits<Kokkos::Unmanaged>> state,
        Kokkos::View<double**, Kokkos::LayoutLeft, Kokkos::MemoryTraits<Kokkos::Unmanaged>> rates
    );
}
```

## 3. Dummy Engine Identity

If CMake compilation flags for an engine are `OFF`, the C++ wrapper must intercept the call and safely return without invoking the `extern "C"` block, effectively performing a zero-cost pass-through operation.
