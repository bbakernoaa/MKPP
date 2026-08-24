add_subdirectory(mkpp)

if(TARGET micm)
  add_subdirectory(micm)
endif()

if(CMAKE_Fortran_COMPILER)
  add_subdirectory(kpp)
endif()
