// Generated sparse LU factorization chunk 0 for small_strato.
// Chunks execute in symbolic-lowering order and share the packed LU storage.
#ifdef MKPP_GENERATED_MECHANISM_NAMESPACE
namespace MKPP_GENERATED_MECHANISM_NAMESPACE {
#endif
namespace mkpp::detail::small_strato {
void factorize_lu_chunk_0(const double* w, double* lu) {
  constexpr int N = 7;
  lu[0 * N + 0] = w[0 * N + 0];
  lu[1 * N + 0] = (w[1 * N + 0]) / lu[0 * N + 0];
  lu[2 * N + 0] = (w[2 * N + 0]) / lu[0 * N + 0];
  lu[1 * N + 1] = w[1 * N + 1];
  lu[1 * N + 4] = w[1 * N + 4];
  lu[2 * N + 1] = (w[2 * N + 1]) / lu[1 * N + 1];
  lu[3 * N + 1] = (w[3 * N + 1]) / lu[1 * N + 1];
  lu[4 * N + 1] = (w[4 * N + 1]) / lu[1 * N + 1];
  lu[2 * N + 2] = w[2 * N + 2];
  lu[2 * N + 3] = w[2 * N + 3];
  lu[2 * N + 4] = w[2 * N + 4] - lu[2 * N + 1] * lu[1 * N + 4];
  lu[2 * N + 6] = w[2 * N + 6];
  lu[3 * N + 2] = (w[3 * N + 2]) / lu[2 * N + 2];
  lu[4 * N + 2] = (w[4 * N + 2]) / lu[2 * N + 2];
  lu[5 * N + 2] = (w[5 * N + 2]) / lu[2 * N + 2];
  lu[6 * N + 2] = (w[6 * N + 2]) / lu[2 * N + 2];
  lu[3 * N + 3] = w[3 * N + 3] - lu[3 * N + 2] * lu[2 * N + 3];
  lu[3 * N + 4] = w[3 * N + 4] - lu[3 * N + 1] * lu[1 * N + 4] - lu[3 * N + 2] * lu[2 * N + 4];
  lu[3 * N + 5] = w[3 * N + 5];
  lu[3 * N + 6] = w[3 * N + 6] - lu[3 * N + 2] * lu[2 * N + 6];
  lu[4 * N + 3] = (w[4 * N + 3] - lu[4 * N + 2] * lu[2 * N + 3]) / lu[3 * N + 3];
  lu[5 * N + 3] = (0.0 - lu[5 * N + 2] * lu[2 * N + 3]) / lu[3 * N + 3];
  lu[6 * N + 3] = (0.0 - lu[6 * N + 2] * lu[2 * N + 3]) / lu[3 * N + 3];
  lu[4 * N + 4] = w[4 * N + 4] - lu[4 * N + 1] * lu[1 * N + 4] - lu[4 * N + 2] * lu[2 * N + 4] - lu[4 * N + 3] * lu[3 * N + 4];
  lu[4 * N + 5] = w[4 * N + 5] - lu[4 * N + 3] * lu[3 * N + 5];
  lu[4 * N + 6] = 0.0 - lu[4 * N + 2] * lu[2 * N + 6] - lu[4 * N + 3] * lu[3 * N + 6];
  lu[5 * N + 4] = (w[5 * N + 4] - lu[5 * N + 2] * lu[2 * N + 4] - lu[5 * N + 3] * lu[3 * N + 4]) / lu[4 * N + 4];
  lu[6 * N + 4] = (w[6 * N + 4] - lu[6 * N + 2] * lu[2 * N + 4] - lu[6 * N + 3] * lu[3 * N + 4]) / lu[4 * N + 4];
  lu[5 * N + 5] = w[5 * N + 5] - lu[5 * N + 3] * lu[3 * N + 5] - lu[5 * N + 4] * lu[4 * N + 5];
  lu[5 * N + 6] = w[5 * N + 6] - lu[5 * N + 2] * lu[2 * N + 6] - lu[5 * N + 3] * lu[3 * N + 6] - lu[5 * N + 4] * lu[4 * N + 6];
  lu[6 * N + 5] = (w[6 * N + 5] - lu[6 * N + 3] * lu[3 * N + 5] - lu[6 * N + 4] * lu[4 * N + 5]) / lu[5 * N + 5];
  lu[6 * N + 6] = w[6 * N + 6] - lu[6 * N + 2] * lu[2 * N + 6] - lu[6 * N + 3] * lu[3 * N + 6] - lu[6 * N + 4] * lu[4 * N + 6] - lu[6 * N + 5] * lu[5 * N + 6];
}
}  // namespace mkpp::detail::small_strato
#ifdef MKPP_GENERATED_MECHANISM_NAMESPACE
}  // namespace MKPP_GENERATED_MECHANISM_NAMESPACE
#endif
