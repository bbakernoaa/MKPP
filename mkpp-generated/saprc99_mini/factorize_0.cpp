// Generated sparse LU factorization chunk 0 for saprc99_mini.
// Chunks execute in symbolic-lowering order and share the packed LU storage.
#ifdef MKPP_GENERATED_MECHANISM_NAMESPACE
namespace MKPP_GENERATED_MECHANISM_NAMESPACE {
#endif
namespace mkpp::detail::saprc99_mini {
void factorize_lu_chunk_0(const double* w, double* lu) {
  constexpr int N = 17;
  lu[0 * N + 0] = w[0 * N + 0];
  lu[1 * N + 1] = w[1 * N + 1];
  lu[2 * N + 2] = w[2 * N + 2];
  lu[3 * N + 3] = w[3 * N + 3];
  lu[4 * N + 4] = w[4 * N + 4];
  lu[8 * N + 4] = (w[8 * N + 4]) / lu[4 * N + 4];
  lu[11 * N + 4] = (w[11 * N + 4]) / lu[4 * N + 4];
  lu[5 * N + 5] = w[5 * N + 5];
  lu[5 * N + 6] = w[5 * N + 6];
  lu[5 * N + 9] = w[5 * N + 9];
  lu[5 * N + 12] = w[5 * N + 12];
  lu[5 * N + 13] = w[5 * N + 13];
  lu[9 * N + 5] = (w[9 * N + 5]) / lu[5 * N + 5];
  lu[12 * N + 5] = (w[12 * N + 5]) / lu[5 * N + 5];
  lu[6 * N + 6] = w[6 * N + 6];
  lu[6 * N + 13] = w[6 * N + 13];
  lu[7 * N + 6] = (w[7 * N + 6]) / lu[6 * N + 6];
  lu[9 * N + 6] = (0.0 - lu[9 * N + 5] * lu[5 * N + 6]) / lu[6 * N + 6];
  lu[12 * N + 6] = (0.0 - lu[12 * N + 5] * lu[5 * N + 6]) / lu[6 * N + 6];
  lu[7 * N + 7] = w[7 * N + 7];
  lu[7 * N + 13] = w[7 * N + 13] - lu[7 * N + 6] * lu[6 * N + 13];
  lu[8 * N + 7] = (w[8 * N + 7]) / lu[7 * N + 7];
  lu[8 * N + 8] = w[8 * N + 8];
  lu[8 * N + 10] = w[8 * N + 10];
  lu[8 * N + 13] = w[8 * N + 13] - lu[8 * N + 7] * lu[7 * N + 13];
  lu[10 * N + 8] = (w[10 * N + 8]) / lu[8 * N + 8];
  lu[14 * N + 8] = (w[14 * N + 8]) / lu[8 * N + 8];
  lu[9 * N + 9] = w[9 * N + 9] - lu[9 * N + 5] * lu[5 * N + 9];
  lu[9 * N + 11] = w[9 * N + 11];
  lu[9 * N + 12] = w[9 * N + 12] - lu[9 * N + 5] * lu[5 * N + 12];
  lu[9 * N + 13] = w[9 * N + 13] - lu[9 * N + 5] * lu[5 * N + 13] - lu[9 * N + 6] * lu[6 * N + 13];
  lu[9 * N + 15] = w[9 * N + 15];
  lu[11 * N + 9] = (w[11 * N + 9]) / lu[9 * N + 9];
  lu[12 * N + 9] = (w[12 * N + 9] - lu[12 * N + 5] * lu[5 * N + 9]) / lu[9 * N + 9];
  lu[14 * N + 9] = (w[14 * N + 9]) / lu[9 * N + 9];
  lu[15 * N + 9] = (w[15 * N + 9]) / lu[9 * N + 9];
  lu[10 * N + 10] = w[10 * N + 10] - lu[10 * N + 8] * lu[8 * N + 10];
  lu[10 * N + 13] = w[10 * N + 13] - lu[10 * N + 8] * lu[8 * N + 13];
  lu[14 * N + 10] = (w[14 * N + 10] - lu[14 * N + 8] * lu[8 * N + 10]) / lu[10 * N + 10];
  lu[15 * N + 10] = (w[15 * N + 10]) / lu[10 * N + 10];
  lu[11 * N + 11] = w[11 * N + 11] - lu[11 * N + 9] * lu[9 * N + 11];
  lu[11 * N + 12] = 0.0 - lu[11 * N + 9] * lu[9 * N + 12];
  lu[11 * N + 13] = 0.0 - lu[11 * N + 9] * lu[9 * N + 13];
  lu[11 * N + 14] = w[11 * N + 14];
  lu[11 * N + 15] = w[11 * N + 15] - lu[11 * N + 9] * lu[9 * N + 15];
  lu[12 * N + 11] = (0.0 - lu[12 * N + 9] * lu[9 * N + 11]) / lu[11 * N + 11];
  lu[14 * N + 11] = (w[14 * N + 11] - lu[14 * N + 9] * lu[9 * N + 11]) / lu[11 * N + 11];
  lu[15 * N + 11] = (w[15 * N + 11] - lu[15 * N + 9] * lu[9 * N + 11]) / lu[11 * N + 11];
  lu[12 * N + 12] = w[12 * N + 12] - lu[12 * N + 5] * lu[5 * N + 12] - lu[12 * N + 9] * lu[9 * N + 12] - lu[12 * N + 11] * lu[11 * N + 12];
  lu[12 * N + 13] = w[12 * N + 13] - lu[12 * N + 5] * lu[5 * N + 13] - lu[12 * N + 6] * lu[6 * N + 13] - lu[12 * N + 9] * lu[9 * N + 13] - lu[12 * N + 11] * lu[11 * N + 13];
  lu[12 * N + 14] = 0.0 - lu[12 * N + 11] * lu[11 * N + 14];
  lu[12 * N + 15] = w[12 * N + 15] - lu[12 * N + 9] * lu[9 * N + 15] - lu[12 * N + 11] * lu[11 * N + 15];
  lu[14 * N + 12] = (0.0 - lu[14 * N + 9] * lu[9 * N + 12] - lu[14 * N + 11] * lu[11 * N + 12]) / lu[12 * N + 12];
  lu[15 * N + 12] = (0.0 - lu[15 * N + 9] * lu[9 * N + 12] - lu[15 * N + 11] * lu[11 * N + 12]) / lu[12 * N + 12];
  lu[13 * N + 13] = w[13 * N + 13];
  lu[14 * N + 13] = (w[14 * N + 13] - lu[14 * N + 8] * lu[8 * N + 13] - lu[14 * N + 9] * lu[9 * N + 13] - lu[14 * N + 10] * lu[10 * N + 13] - lu[14 * N + 11] * lu[11 * N + 13] - lu[14 * N + 12] * lu[12 * N + 13]) / lu[13 * N + 13];
  lu[15 * N + 13] = (w[15 * N + 13] - lu[15 * N + 9] * lu[9 * N + 13] - lu[15 * N + 10] * lu[10 * N + 13] - lu[15 * N + 11] * lu[11 * N + 13] - lu[15 * N + 12] * lu[12 * N + 13]) / lu[13 * N + 13];
  lu[16 * N + 13] = (w[16 * N + 13]) / lu[13 * N + 13];
  lu[14 * N + 14] = w[14 * N + 14] - lu[14 * N + 11] * lu[11 * N + 14] - lu[14 * N + 12] * lu[12 * N + 14];
  lu[14 * N + 15] = w[14 * N + 15] - lu[14 * N + 9] * lu[9 * N + 15] - lu[14 * N + 11] * lu[11 * N + 15] - lu[14 * N + 12] * lu[12 * N + 15];
  lu[14 * N + 16] = w[14 * N + 16];
  lu[15 * N + 14] = (w[15 * N + 14] - lu[15 * N + 11] * lu[11 * N + 14] - lu[15 * N + 12] * lu[12 * N + 14]) / lu[14 * N + 14];
  lu[16 * N + 14] = (w[16 * N + 14]) / lu[14 * N + 14];
  lu[15 * N + 15] = w[15 * N + 15] - lu[15 * N + 9] * lu[9 * N + 15] - lu[15 * N + 11] * lu[11 * N + 15] - lu[15 * N + 12] * lu[12 * N + 15] - lu[15 * N + 14] * lu[14 * N + 15];
  lu[15 * N + 16] = w[15 * N + 16] - lu[15 * N + 14] * lu[14 * N + 16];
  lu[16 * N + 15] = (w[16 * N + 15] - lu[16 * N + 14] * lu[14 * N + 15]) / lu[15 * N + 15];
  lu[16 * N + 16] = w[16 * N + 16] - lu[16 * N + 14] * lu[14 * N + 16] - lu[16 * N + 15] * lu[15 * N + 16];
}
}  // namespace mkpp::detail::saprc99_mini
#ifdef MKPP_GENERATED_MECHANISM_NAMESPACE
}  // namespace MKPP_GENERATED_MECHANISM_NAMESPACE
#endif
