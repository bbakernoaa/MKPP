add_subdirectory(contract)
add_subdirectory(integration/e2e_validation)
add_subdirectory(integration/solver_benchmark)

add_executable(test_host_dispatcher test_host_dispatcher.cpp)
target_link_libraries(test_host_dispatcher PRIVATE mkpp_host Kokkos::kokkos
                                                   GTest::gtest)
add_test(NAME test_host_dispatcher COMMAND test_host_dispatcher)
