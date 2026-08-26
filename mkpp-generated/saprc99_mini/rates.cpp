// Generated compiled rates kernel chunk 0
// for saprc99_mini.  This file is part of the required compiled-artifact
// pathway; do not include mechanism expressions in host-model translation units.
#include <cmath>
namespace mkpp::generated::saprc99_mini::detail {
void compute_rates_chunk_0(
    const double* state, double* rates,
    const double* jvals, double temp, double rh) {
  (void)temp;
  (void)rh;
  rates[0] = 6.358515026553832e-34*state[12]*state[13]*state[9] - 1.5503623719243584e-14*state[2]*state[0] - 2.6508709957531697e-17*state[3]*state[0] - 6.2848533514771804e-15*state[0]*state[9];
  rates[1] = -1.0*state[1]*jvals[3] + 1.0*state[11]*(5.465512373221516e-32*state[12] + 1.845172665362734e-12);
  rates[2] = 1.0*state[6]*jvals[1] - 2.636710937705471e-11*state[2]*state[4] - 1.5503623719243584e-14*state[2]*state[0] + 1.0*state[3]*jvals[0];
  rates[3] = 32941423097200.93*pow(0.45, 1.0/(pow(log(6.755293737545229e-19*state[12]), 2)/(M_LN10 * M_LN10) + 1.0))*state[12]*state[5]/(6.755293737545229e-19*state[12] + 1.0) - 2.8342174538324383e-30*pow(0.45, 1.0/(pow(log(1.4180926593376776e-18*state[12]), 2)/(M_LN10 * M_LN10) + 1.0))*state[12]*state[3]*state[4]/(1.4180926593376776e-18*state[12] + 1.0) + 1.0*state[7]*jvals[2] + 5.273421875410942e-11*state[2]*state[4] + 1.5503623719243584e-14*state[2]*state[0] - 2.6508709957531697e-17*state[3]*state[0] - 1.0*state[3]*jvals[0];
  rates[4] = 32941423097200.93*pow(0.45, 1.0/(pow(log(6.755293737545229e-19*state[12]), 2)/(M_LN10 * M_LN10) + 1.0))*state[12]*state[5]/(6.755293737545229e-19*state[12] + 1.0) - 2.8342174538324383e-30*pow(0.45, 1.0/(pow(log(1.4180926593376776e-18*state[12]), 2)/(M_LN10 * M_LN10) + 1.0))*state[12]*state[3]*state[4]/(1.4180926593376776e-18*state[12] + 1.0) + 1.0*state[7]*state[10]*(2.3521256735322904e-32*state[12]/(3.8755615852907066e-19*state[12] + 1.0) + 1.097666311281924e-13) - 2.636710937705471e-11*state[2]*state[4] + 2.6508709957531697e-17*state[3]*state[0];
  rates[5] = -32941423097200.93*pow(0.45, 1.0/(pow(log(6.755293737545229e-19*state[12]), 2)/(M_LN10 * M_LN10) + 1.0))*state[12]*state[5]/(6.755293737545229e-19*state[12] + 1.0) + 2.8342174538324383e-30*pow(0.45, 1.0/(pow(log(1.4180926593376776e-18*state[12]), 2)/(M_LN10 * M_LN10) + 1.0))*state[12]*state[3]*state[4]/(1.4180926593376776e-18*state[12] + 1.0);
  rates[6] = -1.0*state[6]*jvals[1];
  rates[7] = -1.0*state[7]*state[10]*(2.3521256735322904e-32*state[12]/(3.8755615852907066e-19*state[12] + 1.0) + 1.097666311281924e-13) - 1.0*state[7]*jvals[2];
  rates[8] = 0.0;
  rates[9] = -6.358515026553832e-34*state[12]*state[13]*state[9] + 1.0*state[3]*jvals[0] - 6.2848533514771804e-15*state[0]*state[9];
  rates[10] = 2.0*state[1]*jvals[3] - 1.0*state[7]*state[10]*(2.3521256735322904e-32*state[12]/(3.8755615852907066e-19*state[12] + 1.0) + 1.097666311281924e-13) + 1.0*state[7]*jvals[2] + 1.0*state[6]*jvals[1];
  rates[11] = -1.0*state[11]*(5.465512373221516e-32*state[12] + 1.845172665362734e-12);
  rates[12] = 0.0;
  rates[13] = -6.358515026553832e-34*state[12]*state[13]*state[9] + 1.0*state[11]*(5.465512373221516e-32*state[12] + 1.845172665362734e-12) + 1.2569706702954361e-14*state[0]*state[9];
  rates[14] = 0.0;
  rates[15] = 0.0;
  rates[16] = 0.0;
}
}  // namespace mkpp::generated::saprc99_mini::detail
