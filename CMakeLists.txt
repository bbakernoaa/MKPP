cmake_minimum_required(VERSION 3.24)
project(MKPP_Root CXX)

find_package(Kokkos REQUIRED)

add_subdirectory(src/mkpp_host)

# ---------------------------------------------------------------------------
# Install targets (EE2 compliance: all, debug, install, clean)
# ---------------------------------------------------------------------------
include(GNUInstallDirs)

install(
  DIRECTORY mkpp-generated/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mkpp
  FILES_MATCHING
  PATTERN "*.hpp")

# ---------------------------------------------------------------------------
# Testing (guarded behind BUILD_TESTING)
# ---------------------------------------------------------------------------
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0)

if(BUILD_TESTING)
  FetchContent_MakeAvailable(googletest)
  enable_testing()
  add_subdirectory(tests)

  add_executable(test_gocart tests/test_gocart.cpp)
  target_include_directories(test_gocart PRIVATE mkpp-generated)
  target_link_libraries(test_gocart PRIVATE Kokkos::kokkos GTest::gtest_main)
  add_test(NAME gocart_solver COMMAND test_gocart)
endif()
