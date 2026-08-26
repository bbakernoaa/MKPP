#include <algorithm>
#include <array>
#include <cmath>
#include <cstdio>

#include "chapman.hpp"

int main() {
  constexpr int N = mkpp::generated::chapman::SolverKernels<Kokkos::DefaultExecutionSpace>::NUM_SPECIES;
  std::array<double, N * N> w{};
  w[0] = 4.0; w[1] = 1.0; w[4] = 2.0; w[5] = 3.0; w[10] = 2.0; w[15] = 5.0;
  std::array<double, N * N> reference{};
  std::array<double, N * N> candidate{};
  mkpp::generated::chapman::detail::factorize_lu_chunk_0(w.data(), reference.data());
  mkpp::generated::chapman::detail::factorize_plan(w.data(), candidate.data());
  for (int index = 0; index < N * N; ++index)
    if (std::abs(reference[index] - candidate[index]) > 1.0e-12) {
      std::fprintf(stderr, "LU mismatch at %d: %.17g %.17g\n", index, reference[index], candidate[index]);
      return 1;
    }
  std::array<double, N> rhs{1.0, 2.0, 3.0, 4.0}, reference_solution{}, candidate_solution{};
  mkpp::generated::chapman::detail::solve_lu(reference.data(), rhs.data(), reference_solution.data());
  mkpp::generated::chapman::detail::solve_plan(candidate.data(), rhs.data(), candidate_solution.data());
  for (int index = 0; index < N; ++index)
    if (std::abs(reference_solution[index] - candidate_solution[index]) > 1.0e-12) {
      std::fprintf(stderr, "solve mismatch at %d: %.17g %.17g\n", index, reference_solution[index], candidate_solution[index]);
      return 2;
    }
  return 0;
}
