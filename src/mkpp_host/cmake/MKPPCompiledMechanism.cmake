include_guard(GLOBAL)

# Register any generated mechanism through MKPP's one compiled-artifact path.
# The generator emits <mechanism>/rates_*.cpp and
# <mechanism>/jacobian_*.cpp for every mechanism, so this intentionally has no
# header-only fallback for small mechanisms.
function(mkpp_add_compiled_mechanism target generated_dir mechanism)
  file(GLOB mechanism_sources CONFIGURE_DEPENDS
       "${generated_dir}/${mechanism}/rates_*.cpp"
       "${generated_dir}/${mechanism}/jacobian_*.cpp"
       "${generated_dir}/${mechanism}/factorize_*.cpp"
       "${generated_dir}/${mechanism}/solve.cpp")
  if(NOT mechanism_sources)
    message(FATAL_ERROR
      "FATAL ERROR: ${mechanism} has no generated compiled kernel sources in ${generated_dir}")
  endif()

  add_library(${target} STATIC ${mechanism_sources})
  target_compile_features(${target} PUBLIC cxx_std_23)
endfunction()
