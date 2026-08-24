add_executable(solver_benchmark_mkpp main.cpp)

target_compile_features(solver_benchmark_mkpp PRIVATE cxx_std_23)
target_include_directories(
  solver_benchmark_mkpp PRIVATE ${CMAKE_SOURCE_DIR}/mkpp-generated)
target_link_libraries(solver_benchmark_mkpp PRIVATE mkpp_host Kokkos::kokkos)
