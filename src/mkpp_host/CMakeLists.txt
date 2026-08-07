cmake_minimum_required(VERSION 3.24)
project(mkpp_host CXX C Fortran)

find_package(Kokkos REQUIRED)

add_library(mkpp_host INTERFACE)
add_library(MKPP::mkpp_host ALIAS mkpp_host)

target_include_directories(
  mkpp_host INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                      $<INSTALL_INTERFACE:include>)
target_link_libraries(mkpp_host INTERFACE Kokkos::kokkos)

