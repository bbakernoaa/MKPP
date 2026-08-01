cmake_minimum_required(VERSION 3.24)

# We are testing the raw MKPP headers directly. We DO NOT link exaero!
add_executable(e2e_validation_runner test_e2e_chapman.cpp)
target_include_directories(e2e_validation_runner PRIVATE ${CMAKE_SOURCE_DIR}/../../build/mkpp-generated)
target_link_libraries(e2e_validation_runner PRIVATE Kokkos::kokkos GTest::gtest_main GTest::gtest)

add_test(NAME E2ESolverValidation COMMAND e2e_validation_runner)

# T014: CTest definition
add_test(NAME E2EBaselineCompare COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/compare_baselines.py --baseline ${CMAKE_CURRENT_SOURCE_DIR}/data/kpp_baseline_chapman.csv --target e2e_output.csv --hpp ${CMAKE_SOURCE_DIR}/../../build/mkpp-generated/chapman.hpp)
set_tests_properties(E2EBaselineCompare PROPERTIES DEPENDS E2ESolverValidation)
