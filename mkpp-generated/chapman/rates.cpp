// Generated compiled rates kernel chunk 0
// for chapman.  This file is part of the required compiled-artifact
// pathway; do not include mechanism expressions in host-model translation units.
#include <cmath>
namespace mkpp::generated::chapman::detail {
void compute_rates_chunk_0(
    const double* state, double* rates,
    const double* jvals, double temp, double rh) {
  (void)temp;
  (void)rh;
  rates[0] = -6e-34*state[3]*state[0]*state[1] - 8e-12*state[0]*state[2] + 2.0*state[1]*jvals[0] + 1.0*state[2]*jvals[1];
  rates[1] = -6e-34*state[3]*state[0]*state[1] + 1.6e-11*state[0]*state[2] - 1.0*state[1]*jvals[0] + 1.0*state[2]*jvals[1];
  rates[2] = 6e-34*state[3]*state[0]*state[1] - 8e-12*state[0]*state[2] - 1.0*state[2]*jvals[1];
  rates[3] = 0.0;
}
}  // namespace mkpp::generated::chapman::detail
