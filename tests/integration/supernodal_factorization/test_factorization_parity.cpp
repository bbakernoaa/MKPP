#include <algorithm>
#include <array>
#include <cmath>
#include <cstdio>

#include "chapman.hpp"

int main() {
  constexpr int N = mkpp::generated::chapman::SolverKernels<Kokkos::DefaultExecutionSpace>::NUM_SPECIES;
  std::array<double, N * N> w{};
  w[0] = 4.0; w[1] = 1.0; w[4] = 2.0; w[5] = 3.0; w[10] = 2.0; w[15] = 5.0;
  std::array<double, N * N> candidate{};
  mkpp::generated::chapman::detail::factorize_plan(w.data(), candidate.data());
  for (int index = 0; index < N * N; ++index) {
    if (!std::isfinite(candidate[index])) {
      std::fprintf(stderr, "Non-finite factorization value at %d: %.17g\n", index, candidate[index]);
      return 1;
    }
  }

  std::array<double, N> rhs{1.0, 2.0, 3.0, 4.0}, candidate_solution{};
  mkpp::generated::chapman::detail::solve_plan(candidate.data(), rhs.data(), candidate_solution.data());
  for (int index = 0; index < N; ++index) {
    if (!std::isfinite(candidate_solution[index])) {
      std::fprintf(stderr, "Non-finite solve value at %d: %.17g\n", index, candidate_solution[index]);
      return 2;
    }
  }
  return 0;
}
