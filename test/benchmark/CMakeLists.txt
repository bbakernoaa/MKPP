include(CheckIncludeFile)

check_include_file("valgrind/callgrind.h" HAVE_CALLGRIND)

add_executable(mkpp_bench mkpp_bench.cpp)

target_include_directories(mkpp_bench PRIVATE ${CMAKE_SOURCE_DIR}/mkpp-generated)

target_link_libraries(mkpp_bench PRIVATE mkpp_host Kokkos::kokkos)

if(HAVE_CALLGRIND)
  target_compile_definitions(mkpp_bench PRIVATE MKPP_USE_CALLGRIND)
endif()
