// Generated compiled rates kernel chunk 1
// for saprcnov.  This file is part of the required compiled-artifact
// pathway; do not include mechanism expressions in host-model translation units.
#include <cmath>
#ifdef MKPP_GENERATED_MECHANISM_NAMESPACE
namespace MKPP_GENERATED_MECHANISM_NAMESPACE {
#endif
namespace mkpp::detail::saprcnov {
void compute_rates_chunk_1(
    const double* state, double* rates,
    const double* jvals, double temp, double rh) {
  (void)temp;
  (void)rh;
  rates[32] = 6.429930443696398e-13*state[43]*state[73] + 2.6136e-12*state[44]*state[73] - 5e-11*state[32]*state[73] - 1.0*state[32]*jvals[27];
  rates[33] = 3.0363560428566324e-13*state[43]*state[73] + 2.4552e-12*state[44]*state[73] - 5e-11*state[33]*state[73] - 1.0*state[33]*jvals[28];
  rates[34] = -2.0561750478098976e-16*state[34]*state[4] - 1.5952863708481567e-18*state[34]*state[0] - 7.300989470508634e-13*state[34]*state[71] - 8.516484783702303e-12*state[34]*state[73];
  rates[35] = -6.743292787591701e-13*state[35]*state[4] - 1.2892715504723044e-17*state[35]*state[0] - 3.6e-11*state[35]*state[71] - 9.823028118683033e-11*state[35]*state[73];
  rates[36] = -2.5782107442488564e-13*state[36]*state[73];
  rates[37] = 0.0;
  rates[38] = -2.2e-10*state[38]*state[0] - 1.0397235138850452e-12*state[38]*state[73];
  rates[39] = -2.2e-10*state[39]*state[4] - 2.2e-10*state[39]*state[0] - 2.2e-10*state[39]*state[71] - 2.2e-10*state[39]*state[73];
  rates[40] = -2.376820605559698e-12*state[40]*state[73];
  rates[41] = -4.381991182753123e-12*state[41]*state[73];
  rates[42] = -9.340281903931486e-12*state[42]*state[73];
  rates[43] = -5.953639299718887e-12*state[43]*state[73];
  rates[44] = -2.64e-11*state[44]*state[73];
  rates[45] = -1.2617098778225188e-14*state[4]*state[45] - 1.068880518793357e-17*state[0]*state[45] - 4.899510211900024e-12*state[71]*state[45] - 3.2202745814368784e-11*state[73]*state[45];
  rates[46] = -7.265e-13*state[4]*state[46] - 1.0699657989316303e-16*state[0]*state[46] - 2.085e-11*state[71]*state[46] - 6.31893118434083e-11*state[73]*state[46];
  rates[47] = -6.582509288533075e-12*state[4]*state[47] - 6.879071828881775e-17*state[0]*state[47] - 3.27e-11*state[71]*state[47] - 8.250463214849593e-11*state[73]*state[47];
  rates[48] = 5.72e-14*state[27]*state[4] + 2.4e-11*state[3]*state[87] + 6.447337475673071e-15*state[4]*state[45] + 2.332065e-13*state[4]*state[46] + 1.8167725636351285e-12*state[4]*state[47] - 5.382e-12*state[73]*state[48] - 1.0*state[48]*jvals[26];
  rates[49] = 3.803841922183774e-11*state[85]*state[3];
  rates[50] = 1.0121186809522107e-13*state[43]*state[73] + 0.001*state[85] - 3.78e-12*state[4]*state[50] - 2.63e-11*state[73]*state[50];
  rates[51] = 2.7650681711472972e-28*pow(0.3, 1.0/(pow(log(2.297278400416822e-17*state[88]), 2)/(M_LN10 * M_LN10) + 1.0))*state[88]*state[82]*state[3]/(2.297278400416822e-17*state[88] + 1.0) - 2067421938757232.8*pow(0.3, 1.0/(pow(log(1.774055673318577e+35*state[88]), 2)/(M_LN10 * M_LN10) + 1.0))*state[88]*state[51]/(1.774055673318577e+35*state[88] + 1.0);
  rates[52] = 1.2066992504885926e-11*state[3]*state[67] - 0.0004530596386760636*state[52];
  rates[53] = 1.37e-11*state[83]*state[3] - 0.0003197388982666857*state[53];
  rates[54] = -0.0003630752223904921*state[54];
  rates[55] = -7e-07*state[55];
  rates[56] = -7e-07*state[56];
  rates[57] = -7e-07*state[57];
  rates[58] = -7e-07*state[58];
  rates[59] = -7e-07*state[59];
  rates[60] = -7e-07*state[60];
  rates[61] = -7e-07*state[61];
  rates[62] = -7e-07*state[62];
  rates[63] = -7e-07*state[63];
}
}  // namespace mkpp::detail::saprcnov
#ifdef MKPP_GENERATED_MECHANISM_NAMESPACE
}  // namespace MKPP_GENERATED_MECHANISM_NAMESPACE
#endif
