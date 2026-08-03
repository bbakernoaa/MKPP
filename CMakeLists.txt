cmake_minimum_required(VERSION 3.24)
project(MKPP_Root CXX)

find_package(Kokkos REQUIRED)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)
FetchContent_MakeAvailable(googletest)

if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
add_executable(test_gocart tests/test_gocart.cpp)
target_include_directories(test_gocart PRIVATE mkpp-generated)
target_link_libraries(test_gocart PRIVATE Kokkos::kokkos)
