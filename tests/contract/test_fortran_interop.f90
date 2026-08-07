!==============================================================================
! @file test_fortran_interop.f90
! @brief Contract integration test driver for Fortran host model API
!==============================================================================

program test_fortran_interop
  use iso_c_binding
  use mkpp_mod
  implicit none

  integer, parameter :: num_cells = 10
  integer, parameter :: num_species = 3
  integer, parameter :: num_photo = 1

  type(mkpp_handle_t) :: handle
  real(c_double), target :: conc(num_cells, num_species)
  real(c_double), target :: temp(num_cells)
  real(c_double), target :: pres(num_cells)
  real(c_double), target :: rho(num_cells)
  real(c_double), target :: photo(num_cells, num_photo)
  integer :: status, idx, count_val
  real(c_double) :: dt

  ! Initialize dummy physical data
  conc(:,:) = 1.0d-9
  temp(:) = 298.15d0
  pres(:) = 101325.0d0
  rho(:) = 2.45d19
  photo(:,:) = 1.0d-5
  dt = 60.0d0

  ! 1. Test handle creation
  call mkpp_create_handle(handle, num_cells, status)
  if (status /= MKPP_SUCCESS) stop "FAIL: mkpp_create_handle"

  ! 2. Test initialization
  call mkpp_initialize(handle, status)
  if (status /= MKPP_SUCCESS) stop "FAIL: mkpp_initialize"

  ! 3. Test species count query
  call mkpp_get_species_count(handle, count_val, status)
  if (status /= MKPP_SUCCESS .or. count_val /= num_species) stop "FAIL: mkpp_get_species_count"

  ! 4. Test state binding
  call mkpp_set_state_ptrs(handle, conc, temp, pres, rho, status)
  if (status /= MKPP_SUCCESS) stop "FAIL: mkpp_set_state_ptrs"

  ! 5. Test photolysis binding
  call mkpp_set_photolysis_ptrs(handle, photo, status)
  if (status /= MKPP_SUCCESS) stop "FAIL: mkpp_set_photolysis_ptrs"

  ! 6. Test species index lookup
  call mkpp_get_species_index(handle, "O3", idx, status)
  if (status /= MKPP_SUCCESS .or. idx <= 0) stop "FAIL: mkpp_get_species_index"

  ! 7. Test integration
  call mkpp_integrate(handle, dt, status)
  if (status /= MKPP_SUCCESS) stop "FAIL: mkpp_integrate"

  ! 8. Test handle destruction
  call mkpp_destroy_handle(handle, status)
  if (status /= MKPP_SUCCESS) stop "FAIL: mkpp_destroy_handle"

  print *, "Fortran contract integration test PASSED successfully!"
end program test_fortran_interop
