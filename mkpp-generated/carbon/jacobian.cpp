// Generated compiled jacobian kernel chunk 0
// for carbon.  This file is part of the required compiled-artifact
// pathway; do not include mechanism expressions in host-model translation units.
#include <cmath>
namespace mkpp::generated::carbon::detail {
void compute_jacobian_chunk_0(
    const double* state, double* jacobian,
    const double* jvals, double temp, double rh) {
  (void)temp;
  (void)rh;
  jacobian[0 * 11 + 0] = -9.078100602113127e-14;
  jacobian[0 * 11 + 7] = -5.175092354113148e-15*state[0];
  jacobian[0 * 11 + 8] = -8.560591366701813e-14*state[0];
  jacobian[1 * 11 + 1] = -7.3679649e-14;
  jacobian[1 * 11 + 7] = -7.3679649e-14*state[1];
  jacobian[1 * 11 + 9] = 4.2566446e-15;
  jacobian[1 * 11 + 10] = 38199.012;
  jacobian[2 * 11 + 9] = 4.2566446e-15;
  jacobian[3 * 11 + 10] = 38199.012;
  jacobian[4 * 11 + 0] = 5.175092354113148e-15;
  jacobian[4 * 11 + 7] = 5.175092354113148e-15*state[0];
  jacobian[5 * 11 + 0] = 8.560591366701813e-14;
  jacobian[5 * 11 + 8] = 8.560591366701813e-14*state[0];
  jacobian[6 * 11 + 1] = 7.3679649e-14;
  jacobian[6 * 11 + 7] = 7.3679649e-14*state[1];
  jacobian[7 * 11 + 0] = -5.175092354113148e-15;
  jacobian[7 * 11 + 1] = -7.3679649e-14;
  jacobian[7 * 11 + 7] = -5.175092354113148e-15*state[0] - 7.3679649e-14*state[1];
  jacobian[8 * 11 + 0] = -8.560591366701813e-14;
  jacobian[8 * 11 + 8] = -8.560591366701813e-14*state[0];
  jacobian[9 * 11 + 9] = -4.2566446e-15;
  jacobian[10 * 11 + 10] = -38199.012;
}
}  // namespace mkpp::generated::carbon::detail
