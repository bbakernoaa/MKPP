// Generated compiled rates kernel chunk 6
// for ts1.  This file is part of the required compiled-artifact
// pathway; do not include mechanism expressions in host-model translation units.
#include <cmath>
#ifdef MKPP_GENERATED_MECHANISM_NAMESPACE
namespace MKPP_GENERATED_MECHANISM_NAMESPACE {
#endif
namespace mkpp::detail::ts1 {
void compute_rates_chunk_6(
    const double* state, double* rates,
    const double* jvals, double temp, double rh) {
  (void)temp;
  (void)rh;
  rates[192] = 1994639.86332894*pow(0.6, 1.0/(pow(log(4.040251326996292*state[209]), 2)/(M_LN10 * M_LN10) + 1.0))*state[135]*state[209]*state[182]/(4.040251326996292*state[209] + 1.0) + 7226.568912*state[122]*state[187] + 1.0*state[114]*jvals[79] + 1.0*state[123]*jvals[60] + 1.0*state[125]*jvals[76] + 1.0*state[126]*jvals[7] + 699673.0723038338*state[85]*state[133] + 1.0665790921384848*state[100]*state[187] + 6.6844500511711775*state[132]*state[187] + 44109993.76292367*state[133]*state[89] + 363.208417615364*state[133]*state[181] + 95635.79925884458*state[133]*state[104] + 5037237.706154684*state[133]*state[182] + 1.0*state[133]*jvals[12] + 1.0*state[133]*jvals[81] + 1.0*state[194]*jvals[94] + 305459.07165518985*state[61]*state[89] + 8430997.064*state[62]*state[140] + 6697889.613700743*state[62]*state[169] + 1646.4388095406098*state[102]*state[181] + 8185284.465643598*state[102]*state[182] + 1.0*state[102]*jvals[2] + 1151789.8277025437*state[121]*state[140] + 6443121.379726825*state[121]*state[161] + 1151789.8277025437*state[121]*state[169] + 1.0*state[60]*jvals[4] - 1.0*state[192]*state[182]*jvals[545] + 1.0*state[117]*jvals[98] + 8474526.087803893*state[197]*state[154] + 11946346.47935517*state[197]*state[84] + 1.0*state[153]*jvals[112] + 6925461.874*state[149]*state[182] + 1.0*state[149]*jvals[53] + 8474526.087803893*state[154]*state[142] + 8474526.087803893*state[154]*state[145] + 1.0*state[174]*jvals[84] + 7.721088703561247*state[158]*state[187] + 0.7887101300694561*state[173]*state[187] + 1.0*state[173]*jvals[21] + 5438783.424099084*state[140]*state[84] + 1445313.7824*state[140]*state[181] + 11946346.47935517*state[142]*state[84] + 11946346.47935517*state[145]*state[84] + 54.23074498998498*state[43]*state[187] + 3.1267342206134505*state[16]*state[187] + 1.0*state[16]*jvals[62] + 4625873.391855703*state[84]*state[161] + 5438783.424099084*state[84]*state[169] + 1445313.7824*state[181]*state[169] + 7895.549698937078*state[104]*state[35] + 1198.087152040758*state[35]*state[182] + 1.0*state[35]*jvals[113] + 20475278.584*state[182]*state[171] + 1.0*state[207]*jvals[10] + 1.0*state[203]*jvals[5] + 1.0*state[64]*jvals[101] + 1.0*state[171]*jvals[65];
  rates[193] = 6.6844500511711775*state[132]*state[187] + 6443121.379726825*state[62]*state[121] + 8474526.087803893*state[62]*state[154] - 415108.6847156083*state[193]*state[182] + 8474526.087803893*state[154]*state[144];
  rates[194] = 963542.5216*state[0]*state[182] + 1.0*state[0]*jvals[59] + 4034834.3092*state[199]*state[84] + 1.0*state[196]*jvals[37] + 210774.9266*state[99]*state[181] + 40950.557168*(state[101] * state[101]) + 120442.8152*state[101]*state[121] + 5325918.339095465*state[101]*state[84] + 1921210.2821068927*state[112]*state[182] + 4475696.870055676*state[129]*state[182] + 1.0*state[129]*jvals[97] + 6.6844500511711775*state[132]*state[187] + 4625873.391855703*state[120]*state[84] - 1439.7277033291768*state[194]*state[181] - 9018881.56452629*state[194]*state[182] - 1.0*state[194]*jvals[94] + 4323025.918522997*state[139]*state[84] + 4725565.058571535*state[154]*state[146] + 1.0*state[174]*jvals[84] + 4625873.391855703*state[146]*state[84] + 1.0*state[172]*jvals[72] + 3.1267342206134505*state[16]*state[187] + 4625873.391855703*state[84]*state[167] + 1.0*state[204]*jvals[25];
  rates[195] = 5325918.339095465*state[8]*state[84] + 1.0*state[198]*jvals[33] + 1.0*state[114]*jvals[79] - 1.0*state[195]*jvals[95] + 5325918.339095465*state[84]*state[160] + 5325918.339095465*state[84]*state[162] + 1.0*state[189]*jvals[109] + 1.0*state[190]*jvals[3];
  rates[196] = 4725565.058571535*state[199]*state[154] - 4475696.870055676*state[196]*state[182] - 1.0*state[196]*jvals[37];
  rates[197] = -36418127.23213432*pow(0.6, 1.0/(pow(log(6.442495091740848*state[209]), 2)/(M_LN10 * M_LN10) + 1.0))*state[197]*state[209]*state[69]/(6.442495091740848*state[209] + 1.0) + 1.0*state[124]*jvals[49] - 8474526.087803893*state[197]*state[154] - 11946346.47935517*state[197]*state[84];
  rates[198] = 4725565.058571535*state[8]*state[154] - 4475696.870055676*state[198]*state[182] - 1.0*state[198]*jvals[33];
  rates[199] = -4725565.058571535*state[199]*state[154] - 4636580.686170274*state[199]*state[84] + 4475696.870055676*state[196]*state[182] + 2107749.266*state[127]*state[182];
  rates[200] = 70370.28424268606*pow(0.6, 1.0/(pow(log(0.029158990152935344*state[209]), 2)/(M_LN10 * M_LN10) + 1.0))*state[154]*state[209]*state[69]/(0.029158990152935344*state[209] + 1.0) - 4.194644432663864e+29*pow(0.6, 1.0/(pow(log(0.029158990152935344*state[209]), 2)/(M_LN10 * M_LN10) + 1.0))*state[200]*state[209]/(0.029158990152935344*state[209] + 1.0) - 2096564.4733879878*state[200]*state[182] - 1.0*state[200]*jvals[44] - 1.0*state[200]*jvals[50];
  rates[201] = 4725565.058571535*state[120]*state[154] - 4475696.870055676*state[201]*state[182] - 1.0*state[201]*jvals[16];
  rates[202] = -94621.95887234774*state[202]*state[182];
  rates[203] = 4725565.058571535*state[154]*state[161] - 13850923.748*state[182]*state[203] - 1.0*state[203]*jvals[5];
  rates[204] = 4725565.058571535*state[154]*state[167] - 4475696.870055676*state[182]*state[204] - 1.0*state[204]*jvals[25];
  rates[205] = 5736.453728556309*state[132]*state[181] + 24088563.04*state[33]*state[182] + 24088563.04*state[176]*state[182] + 42154985.32*state[151]*state[182] + 60221407.6*state[206]*state[182] - 403483.43092*state[205]*state[182] - 1.0*state[205]*jvals[19];
  rates[206] = 8430997.064*state[62]*state[47] + 1151789.8277025437*state[121]*state[47] + 5438783.424099084*state[47]*state[84] + 1445313.7824*state[47]*state[181] - 60221407.6*state[206]*state[182] - 1.0*state[206]*jvals[83] - 1.0*state[206]*jvals[370];
  rates[207] = 3333756.5029597976*state[182]*state[168] + 10237639.292*state[182]*state[166] - 1.0*state[207]*jvals[10];
  rates[208] = -6.34e-08*state[208];
  rates[209] = 0.0;
}
}  // namespace mkpp::detail::ts1
#ifdef MKPP_GENERATED_MECHANISM_NAMESPACE
}  // namespace MKPP_GENERATED_MECHANISM_NAMESPACE
#endif
