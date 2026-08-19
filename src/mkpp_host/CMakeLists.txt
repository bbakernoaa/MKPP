cmake_minimum_required(VERSION 3.24)
project(mkpp_host CXX C Fortran)

find_package(Kokkos REQUIRED)

add_library(mkpp_host INTERFACE)
add_library(MKPP::mkpp_host ALIAS mkpp_host)

target_include_directories(
  mkpp_host
  INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/mkpp-generated>
            $<INSTALL_INTERFACE:include>)
target_link_libraries(mkpp_host INTERFACE Kokkos::kokkos)

if(MKPP_ENABLE_KOKKOS_KERNELS)
  if(TARGET KokkosKernels::kokkoskernels)
    target_link_libraries(mkpp_host INTERFACE KokkosKernels::kokkoskernels)
  elseif(TARGET kokkoskernels)
    target_link_libraries(mkpp_host INTERFACE kokkoskernels)
  endif()
  target_compile_definitions(mkpp_host INTERFACE MKPP_HAS_KOKKOS_KERNELS)
endif()
