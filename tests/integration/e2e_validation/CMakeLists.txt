add_subdirectory(${CMAKE_SOURCE_DIR}/src/mkpp_host
                 ${CMAKE_BINARY_DIR}/mkpp_host)
cmake_minimum_required(VERSION 3.24)

set(MECHS "chapman" "small_strato" "carbon" "saprc99" "saprc99_lumped")

foreach(MECH ${MECHS})
  if("${MECH}" STREQUAL "chapman")
    set(NUM_SPEC 3)
  elseif("${MECH}" STREQUAL "small_strato")
    set(NUM_SPEC 7)
  elseif("${MECH}" STREQUAL "carbon")
    set(NUM_SPEC 10)
  elseif("${MECH}" STREQUAL "gocart")
    set(NUM_SPEC 12)
  elseif("${MECH}" STREQUAL "saprc99")
    set(NUM_SPEC 82)
  elseif("${MECH}" STREQUAL "saprc99_lumped")
    set(NUM_SPEC 35)
  else()
    set(NUM_SPEC 100)
  endif()

  add_executable(e2e_${MECH}_runner test_e2e_mechanisms.cpp)
  target_include_directories(e2e_${MECH}_runner
                             PRIVATE ${CMAKE_SOURCE_DIR}/mkpp-generated)
  target_link_libraries(
    e2e_${MECH}_runner PRIVATE mkpp_host Kokkos::kokkos GTest::gtest_main
                               GTest::gtest)
  target_compile_definitions(
    e2e_${MECH}_runner PRIVATE MECH_HEADER=${MECH}.hpp
                               NUM_SPECIES_MACRO=${NUM_SPEC})

  add_test(NAME E2ESolver_${MECH} COMMAND e2e_${MECH}_runner)

  add_test(
    NAME E2ECompare_${MECH}
    COMMAND
      python3 ${CMAKE_CURRENT_SOURCE_DIR}/compare_baselines.py --baseline
      ${CMAKE_CURRENT_SOURCE_DIR}/data/kpp_baseline_${MECH}.csv --target
      e2e_output.csv --hpp ${CMAKE_SOURCE_DIR}/mkpp-generated/${MECH}.hpp)
  set_tests_properties(E2ECompare_${MECH} PROPERTIES DEPENDS E2ESolver_${MECH})
endforeach()

add_executable(benchmark_runner benchmark_runner.cpp)
target_include_directories(benchmark_runner
                           PRIVATE ${CMAKE_SOURCE_DIR}/mkpp-generated)
target_link_libraries(benchmark_runner PRIVATE mkpp_host Kokkos::kokkos)

# SciPy reference validation test
add_executable(test_scipy_validation test_scipy_validation.cpp)
target_include_directories(test_scipy_validation
                           PRIVATE ${CMAKE_SOURCE_DIR}/mkpp-generated)
target_link_libraries(
  test_scipy_validation PRIVATE mkpp_host Kokkos::kokkos GTest::gtest_main
                                GTest::gtest)
target_compile_definitions(
  test_scipy_validation PRIVATE REFERENCE_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data")

add_test(NAME mkpp_scipy_validation COMMAND test_scipy_validation)
