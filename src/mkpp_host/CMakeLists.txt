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

# ---------------------------------------------------------------------------
# Pre-compiled C/Fortran host model libraries (libmkpp / libmkpp_fortran)
# ---------------------------------------------------------------------------
option(MKPP_BUILD_COMPILED_LIB
       "Build pre-compiled C/Fortran host model library (libmkpp)" ON)

if(MKPP_BUILD_COMPILED_LIB
   AND EXISTS "${CMAKE_SOURCE_DIR}/mkpp-generated/mkpp_c_api.cpp")
  add_library(mkpp_c_api STATIC
              "${CMAKE_SOURCE_DIR}/mkpp-generated/mkpp_c_api.cpp")
  add_library(MKPP::mkpp_c_api ALIAS mkpp_c_api)

  target_include_directories(
    mkpp_c_api
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
           $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/mkpp-generated>
           $<INSTALL_INTERFACE:include>)
  target_link_libraries(mkpp_c_api PUBLIC mkpp_host Kokkos::kokkos)
  set_target_properties(mkpp_c_api PROPERTIES OUTPUT_NAME "mkpp")

  if(CMAKE_Fortran_COMPILER_LOADED
     AND EXISTS "${CMAKE_SOURCE_DIR}/mkpp-generated/mkpp_mod.f90")
    add_library(mkpp_fortran STATIC
                "${CMAKE_SOURCE_DIR}/mkpp-generated/mkpp_mod.f90")
    add_library(MKPP::mkpp_fortran ALIAS mkpp_fortran)

    target_link_libraries(mkpp_fortran PUBLIC mkpp_c_api)
    set_target_properties(mkpp_fortran PROPERTIES OUTPUT_NAME "mkpp_fortran")
  endif()
endif()
