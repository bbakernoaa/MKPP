// Generated sparse LU factorization chunk 0 for chapman.
// Chunks execute in symbolic-lowering order and share the packed LU storage.
namespace mkpp::generated::chapman::detail {
void factorize_lu_chunk_0(const double* w, double* lu) {
  constexpr int N = 4;
  lu[0 * N + 0] = w[0 * N + 0];
  lu[1 * N + 0] = (w[1 * N + 0]) / lu[0 * N + 0];
  lu[2 * N + 0] = (w[2 * N + 0]) / lu[0 * N + 0];
  lu[3 * N + 0] = (w[3 * N + 0]) / lu[0 * N + 0];
  lu[1 * N + 1] = w[1 * N + 1];
  lu[1 * N + 2] = w[1 * N + 2];
  lu[1 * N + 3] = w[1 * N + 3];
  lu[2 * N + 1] = (w[2 * N + 1]) / lu[1 * N + 1];
  lu[3 * N + 1] = (w[3 * N + 1]) / lu[1 * N + 1];
  lu[2 * N + 2] = w[2 * N + 2] - lu[2 * N + 1] * lu[1 * N + 2];
  lu[2 * N + 3] = w[2 * N + 3] - lu[2 * N + 1] * lu[1 * N + 3];
  lu[3 * N + 2] = (w[3 * N + 2] - lu[3 * N + 1] * lu[1 * N + 2]) / lu[2 * N + 2];
  lu[3 * N + 3] = w[3 * N + 3] - lu[3 * N + 1] * lu[1 * N + 3] - lu[3 * N + 2] * lu[2 * N + 3];
}
}  // namespace mkpp::generated::chapman::detail
