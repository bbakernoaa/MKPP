#include <type_traits>

#include "chapman.hpp"
#include "carbon.hpp"

int main() {
  using Chapman = mkpp::generated::chapman::SolverKernels<Kokkos::DefaultExecutionSpace>;
  using Carbon = mkpp::generated::carbon::SolverKernels<Kokkos::DefaultExecutionSpace>;
  static_assert(!std::is_same_v<Chapman, Carbon>);
  static_assert(Chapman::NUM_SPECIES != Carbon::NUM_SPECIES);
  return 0;
}
