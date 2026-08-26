// Generated compiled rates kernel chunk 0
// for carbon.  This file is part of the required compiled-artifact
// pathway; do not include mechanism expressions in host-model translation units.
#include <cmath>
namespace mkpp::generated::carbon::detail {
void compute_rates_chunk_0(
    const double* state, double* rates,
    const double* jvals, double temp, double rh) {
  (void)temp;
  (void)rh;
  rates[0] = -9.078100602113127e-14*state[0];
  rates[1] = 38199.012 - 7.3679649e-14*state[1];
  rates[2] = 4.2566446e-15;
  rates[3] = 38199.012;
  rates[4] = 5.175092354113148e-15*state[0];
  rates[5] = 8.560591366701813e-14*state[0];
  rates[6] = 7.3679649e-14*state[1];
  rates[7] = -5.175092354113148e-15*state[0] - 7.3679649e-14*state[1];
  rates[8] = -8.560591366701813e-14*state[0];
  rates[9] = -4.2566446e-15;
  rates[10] = -38199.012;
}
}  // namespace mkpp::generated::carbon::detail
