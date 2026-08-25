// Generated sparse LU factorization chunk 0 for carbon.
// Chunks execute in symbolic-lowering order and share the packed LU storage.
#ifdef MKPP_GENERATED_MECHANISM_NAMESPACE
namespace MKPP_GENERATED_MECHANISM_NAMESPACE {
#endif
namespace mkpp::detail::carbon {
void factorize_lu_chunk_0(const double* w, double* lu) {
  constexpr int N = 11;
  lu[0 * N + 0] = w[0 * N + 0];
  lu[0 * N + 2] = w[0 * N + 2];
  lu[1 * N + 1] = w[1 * N + 1];
  lu[1 * N + 3] = w[1 * N + 3];
  lu[2 * N + 2] = w[2 * N + 2];
  lu[4 * N + 2] = (w[4 * N + 2]) / lu[2 * N + 2];
  lu[3 * N + 3] = w[3 * N + 3];
  lu[4 * N + 3] = (w[4 * N + 3]) / lu[3 * N + 3];
  lu[4 * N + 4] = w[4 * N + 4];
  lu[4 * N + 6] = w[4 * N + 6];
  lu[5 * N + 4] = (w[5 * N + 4]) / lu[4 * N + 4];
  lu[6 * N + 4] = (w[6 * N + 4]) / lu[4 * N + 4];
  lu[5 * N + 5] = w[5 * N + 5];
  lu[5 * N + 6] = w[5 * N + 6] - lu[5 * N + 4] * lu[4 * N + 6];
  lu[6 * N + 6] = w[6 * N + 6] - lu[6 * N + 4] * lu[4 * N + 6];
  lu[6 * N + 8] = w[6 * N + 8];
  lu[7 * N + 6] = (w[7 * N + 6]) / lu[6 * N + 6];
  lu[8 * N + 6] = (w[8 * N + 6]) / lu[6 * N + 6];
  lu[7 * N + 7] = w[7 * N + 7];
  lu[7 * N + 8] = w[7 * N + 8] - lu[7 * N + 6] * lu[6 * N + 8];
  lu[8 * N + 8] = w[8 * N + 8] - lu[8 * N + 6] * lu[6 * N + 8];
  lu[8 * N + 10] = w[8 * N + 10];
  lu[9 * N + 8] = (w[9 * N + 8]) / lu[8 * N + 8];
  lu[10 * N + 8] = (w[10 * N + 8]) / lu[8 * N + 8];
  lu[9 * N + 9] = w[9 * N + 9];
  lu[9 * N + 10] = w[9 * N + 10] - lu[9 * N + 8] * lu[8 * N + 10];
  lu[10 * N + 10] = w[10 * N + 10] - lu[10 * N + 8] * lu[8 * N + 10];
}
}  // namespace mkpp::detail::carbon
#ifdef MKPP_GENERATED_MECHANISM_NAMESPACE
}  // namespace MKPP_GENERATED_MECHANISM_NAMESPACE
#endif
