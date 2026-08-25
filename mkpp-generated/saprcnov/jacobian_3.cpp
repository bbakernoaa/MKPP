// Generated compiled jacobian kernel chunk 3
// for saprcnov.  This file is part of the required compiled-artifact
// pathway; do not include mechanism expressions in host-model translation units.
#include <cmath>
#ifdef MKPP_GENERATED_MECHANISM_NAMESPACE
namespace MKPP_GENERATED_MECHANISM_NAMESPACE {
#endif
namespace mkpp::detail::saprcnov {
void compute_jacobian_chunk_3(
    const double* state, double* jacobian,
    const double* jvals, double temp, double rh) {
  (void)temp;
  (void)rh;
  jacobian[86 * 96 + 71] = 8.64e-12*state[35];
  jacobian[86 * 96 + 73] = 1.78891e-11*state[27] + 1.67822418171901e-11*state[28];
  jacobian[87 * 96 + 3] = -2.4e-11*state[87];
  jacobian[87 * 96 + 40] = 5.609296629120887e-13*state[73];
  jacobian[87 * 96 + 73] = 5.609296629120887e-13*state[40];
  jacobian[87 * 96 + 87] = -2.4e-11*state[3] - 1001.3980443151514;
  jacobian[90 * 96 + 0] = 1.597572121590464e-14*state[71];
  jacobian[90 * 96 + 2] = -3.90443570238861e-38*state[2]*state[90];
  jacobian[90 * 96 + 71] = -5.779235214948339e-34*state[88]*state[90] + 1.597572121590464e-14*state[0];
  jacobian[90 * 96 + 73] = 1.1101941762569073e-10*state[74];
  jacobian[90 * 96 + 74] = 1.1101941762569073e-10*state[73];
  jacobian[90 * 96 + 88] = -5.779235214948339e-34*state[90]*state[71];
  jacobian[90 * 96 + 90] = -5.779235214948339e-34*state[88]*state[71] - 1.952217851194305e-38*(state[2] * state[2]);
  jacobian[91 * 96 + 5] = -2.6e-22*state[91];
  jacobian[91 * 96 + 72] = -2.2e-10*state[91];
  jacobian[91 * 96 + 73] = 1.1101941762569073e-10*state[74];
  jacobian[91 * 96 + 74] = -2.0*state[91]*state[74]*(1.1101605816625855e-49*state[88] + 3.690770493620667e-30) - 2.0*state[91]*state[74]*(1.1101605816625853e-33*state[88] + 3.690770493620667e-30) + 1.1101941762569073e-10*state[73];
  jacobian[91 * 96 + 88] = -1.1101605816625853e-33*state[91]*(state[74] * state[74]);
  jacobian[91 * 96 + 91] = -1.0*(state[74] * state[74])*(1.1101605816625855e-49*state[88] + 3.690770493620667e-30) - 1.0*(state[74] * state[74])*(1.1101605816625853e-33*state[88] + 3.690770493620667e-30) - 2.6e-22*state[5] - 2.2e-10*state[72];
  jacobian[92 * 96 + 73] = -6.723044449434636e-15*state[92];
  jacobian[92 * 96 + 92] = -6.723044449434636e-15*state[73];
  jacobian[93 * 96 + 73] = -6.385339164031197e-15*state[93];
  jacobian[93 * 96 + 93] = -6.385339164031197e-15*state[73];
}
}  // namespace mkpp::detail::saprcnov
#ifdef MKPP_GENERATED_MECHANISM_NAMESPACE
}  // namespace MKPP_GENERATED_MECHANISM_NAMESPACE
#endif
