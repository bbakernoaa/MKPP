// Generated compiled rates kernel chunk 0
// for carbon.  This file is part of the required compiled-artifact
// pathway; do not include mechanism expressions in host-model translation units.
#include <cmath>
#ifdef MKPP_GENERATED_MECHANISM_NAMESPACE
namespace MKPP_GENERATED_MECHANISM_NAMESPACE {
#endif
namespace mkpp::detail::carbon {
void compute_rates_chunk_0(
    const double* state, double* rates,
    const double* jvals, double temp, double rh) {
  (void)temp;
  (void)rh;
  rates[0] = -1.0665177283814332e-13*state[0];
  rates[1] = 38199.012 - 7.3679649e-14*state[1];
  rates[2] = 4.2566446e-15;
  rates[3] = 38199.012;
  rates[4] = 6.3627720033519555e-15*state[0];
  rates[5] = 1.0028900083479136e-13*state[0];
  rates[6] = 7.3679649e-14*state[1];
  rates[7] = -6.3627720033519555e-15*state[0] - 7.3679649e-14*state[1];
  rates[8] = -1.0028900083479136e-13*state[0];
  rates[9] = -4.2566446e-15;
  rates[10] = -38199.012;
}
}  // namespace mkpp::detail::carbon
#ifdef MKPP_GENERATED_MECHANISM_NAMESPACE
}  // namespace MKPP_GENERATED_MECHANISM_NAMESPACE
#endif
