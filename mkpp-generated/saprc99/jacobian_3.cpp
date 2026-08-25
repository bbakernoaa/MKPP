// Generated compiled jacobian kernel chunk 3
// for saprc99.  This file is part of the required compiled-artifact
// pathway; do not include mechanism expressions in host-model translation units.
#include <cmath>
#ifdef MKPP_GENERATED_MECHANISM_NAMESPACE
namespace MKPP_GENERATED_MECHANISM_NAMESPACE {
#endif
namespace mkpp::detail::saprc99 {
void compute_jacobian_chunk_3(
    const double* state, double* jacobian,
    const double* jvals, double temp, double rh) {
  (void)temp;
  (void)rh;
  jacobian[66 * 82 + 59] = 2.183419379158595e-14*state[36] + 1.6637744238917885e-13*state[37] + 6.266247391336966e-13*state[38] + 3.241077820664226e-12*state[39] + 6.549003229690776e-14*state[40] + 2.376e-13*state[41] + 9.13541615037522e-12*state[34] + 2.5379e-12*state[26] + 4.9591128344452724e-14*state[16] + 4.729270071282155e-13*state[28] + 2.898247123293191e-12*state[42] + 5.1815235711594795e-12*state[43] + 1.05e-12*state[29] + 2e-14*state[14] + 1.3494e-12*state[45] + 2.0626158037123982e-11*state[44];
  jacobian[66 * 82 + 60] = -1.487214735018438e-11*state[66];
  jacobian[66 * 82 + 61] = -2e-13*state[66];
  jacobian[66 * 82 + 64] = -3.5e-14*state[66];
  jacobian[66 * 82 + 66] = -7.5e-12*state[69] - 7.5e-12*state[68] - 2e-13*state[61] - 1.487214735018438e-11*state[60] - 7.5e-12*state[72] - 9.031312353614072e-12*state[2] - 2.3e-12*state[4] - 7.5e-12*state[53] - 1.4e-13*state[66] - 3.5e-14*state[64];
  jacobian[66 * 82 + 68] = -7.5e-12*state[66];
  jacobian[66 * 82 + 69] = -7.5e-12*state[66];
  jacobian[66 * 82 + 72] = -7.5e-12*state[66];
  jacobian[67 * 82 + 2] = -7.282790513557887e-12*state[67];
  jacobian[67 * 82 + 12] = 7.891617058121771e-14*state[60];
  jacobian[67 * 82 + 60] = 7.891617058121771e-14*state[12];
  jacobian[67 * 82 + 67] = -7.282790513557887e-12*state[2] - 152.6846694291373;
  jacobian[68 * 82 + 0] = 1.4658531445363335e-17*state[43] + 8.461258349524583e-18*state[44];
  jacobian[68 * 82 + 2] = -2.1334567916429005e-11*state[68] + 2.795769818335074e-11*state[72];
  jacobian[68 * 82 + 3] = -2.7650681711472972e-28*pow(0.3, 1.0/(pow(log(2.297278400416822e-17*state[74]), 2)/(M_LN10 * M_LN10) + 1.0))*state[74]*state[68]/(2.297278400416822e-17*state[74] + 1.0);
  jacobian[68 * 82 + 4] = 2.733975964953383e-15*state[13] - 4e-12*state[68] + 4e-12*state[72] + 2.4311548026210594e-15*state[22];
  jacobian[68 * 82 + 13] = 2.733975964953383e-15*state[4] + 1.583957717435914e-11*state[59];
  jacobian[68 * 82 + 15] = 1.9228466663970293e-13*state[59] + 1.0*jvals[14];
  jacobian[68 * 82 + 16] = 5.809246463207319e-13*state[59] + 1.0*jvals[15];
  jacobian[68 * 82 + 22] = 2.4311548026210594e-15*state[4] + 1.5e-11*state[59] + 1.0*jvals[20];
  jacobian[68 * 82 + 23] = 2.0*jvals[21];
  jacobian[68 * 82 + 26] = 0.467*jvals[25];
  jacobian[68 * 82 + 27] = 0.67*jvals[23];
  jacobian[68 * 82 + 28] = 1.2769029192461818e-11*state[59];
  jacobian[68 * 82 + 29] = 4.35e-13*state[59] + 0.667*jvals[26];
  jacobian[68 * 82 + 31] = 5e-11*state[59] + 0.5*jvals[28];
  jacobian[68 * 82 + 32] = 5e-11*state[59] + 0.5*jvals[29];
  jacobian[68 * 82 + 38] = 4.8201903010284345e-14*state[59];
  jacobian[68 * 82 + 43] = 1.4658531445363335e-17*state[0];
  jacobian[68 * 82 + 44] = 8.461258349524583e-18*state[0];
  jacobian[68 * 82 + 48] = 2067421938757232.8*pow(0.3, 1.0/(pow(log(1.774055673318577e+35*state[74]), 2)/(M_LN10 * M_LN10) + 1.0))*state[74]/(1.774055673318577e+35*state[74] + 1.0);
  jacobian[68 * 82 + 53] = -1.5513629410090206e-11*state[68] + 1.5513629410090206e-11*state[72];
  jacobian[68 * 82 + 59] = 1.9228466663970293e-13*state[15] + 4.8201903010284345e-14*state[38] + 1.583957717435914e-11*state[13] + 5e-11*state[31] + 5e-11*state[32] + 5.809246463207319e-13*state[16] + 1.5e-11*state[22] + 1.2769029192461818e-11*state[28] + 4.35e-13*state[29];
  jacobian[68 * 82 + 60] = -1.4072281644582305e-11*state[68];
  jacobian[68 * 82 + 61] = -9.629149289021505e-12*state[68];
  jacobian[68 * 82 + 64] = -7.5e-12*state[68];
  jacobian[68 * 82 + 66] = -7.5e-12*state[68];
  jacobian[68 * 82 + 68] = -2.7650681711472972e-28*pow(0.3, 1.0/(pow(log(2.297278400416822e-17*state[74]), 2)/(M_LN10 * M_LN10) + 1.0))*state[74]*state[3]/(2.297278400416822e-17*state[74] + 1.0) - 1.5513629410090206e-11*state[69] - 6.205451764036082e-11*state[68] - 9.629149289021505e-12*state[61] - 1.4072281644582305e-11*state[60] - 2.1334567916429005e-11*state[2] - 4e-12*state[4] - 1.5513629410090206e-11*state[53] - 7.5e-12*state[66] - 7.5e-12*state[64];
  jacobian[68 * 82 + 69] = -1.5513629410090206e-11*state[68] + 1.5513629410090206e-11*state[72];
  jacobian[68 * 82 + 72] = 1.5513629410090206e-11*state[69] + 6.205451764036082e-11*state[72] + 2.795769818335074e-11*state[2] + 4e-12*state[4] + 1.5513629410090206e-11*state[53];
  jacobian[68 * 82 + 74] = 6.352131385256731e-45*pow(0.3, 1.0/(pow(log(2.297278400416822e-17*state[74]), 2)/(M_LN10 * M_LN10) + 1.0))*state[74]*state[68]*state[3]/pow(2.297278400416822e-17*state[74] + 1.0, 2) - 2.7650681711472972e-28*pow(0.3, 1.0/(pow(log(2.297278400416822e-17*state[74]), 2)/(M_LN10 * M_LN10) + 1.0))*state[68]*state[3]/(2.297278400416822e-17*state[74] + 1.0) - 6.658133760337192e-28*pow(0.3, 1.0/(pow(log(2.297278400416822e-17*state[74]), 2)/(M_LN10 * M_LN10) + 1.0))*state[68]*state[3]*log(2.297278400416822e-17*state[74])/((2.297278400416822e-17*state[74] + 1.0)*pow(pow(log(2.297278400416822e-17*state[74]), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10)) - 3.6677216195955553e+50*pow(0.3, 1.0/(pow(log(1.774055673318577e+35*state[74]), 2)/(M_LN10 * M_LN10) + 1.0))*state[74]*state[48]/pow(1.774055673318577e+35*state[74] + 1.0, 2) + 2067421938757232.8*pow(0.3, 1.0/(pow(log(1.774055673318577e+35*state[74]), 2)/(M_LN10 * M_LN10) + 1.0))*state[48]/(1.774055673318577e+35*state[74] + 1.0) + 4978239578661030.0*pow(0.3, 1.0/(pow(log(1.774055673318577e+35*state[74]), 2)/(M_LN10 * M_LN10) + 1.0))*state[48]*log(1.774055673318577e+35*state[74])/((1.774055673318577e+35*state[74] + 1.0)*pow(pow(log(1.774055673318577e+35*state[74]), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10));
  jacobian[69 * 82 + 2] = -2.795769818335074e-11*state[69];
  jacobian[69 * 82 + 3] = -1.37e-11*state[69];
  jacobian[69 * 82 + 4] = 2.626123356623336e-15*state[25] - 4e-12*state[69];
  jacobian[69 * 82 + 25] = 2.626123356623336e-15*state[4] + 1.29e-11*state[59];
  jacobian[69 * 82 + 50] = 0.0003197388982666857;
  jacobian[69 * 82 + 53] = -1.5513629410090206e-11*state[69];
  jacobian[69 * 82 + 59] = 1.29e-11*state[25];
  jacobian[69 * 82 + 60] = -1.4072281644582305e-11*state[69];
  jacobian[69 * 82 + 61] = -9.629149289021505e-12*state[69];
  jacobian[69 * 82 + 64] = -7.5e-12*state[69];
  jacobian[69 * 82 + 66] = -7.5e-12*state[69];
  jacobian[69 * 82 + 68] = -1.5513629410090206e-11*state[69];
  jacobian[69 * 82 + 69] = -6.205451764036082e-11*state[69] - 1.5513629410090206e-11*state[68] - 9.629149289021505e-12*state[61] - 1.4072281644582305e-11*state[60] - 1.5513629410090206e-11*state[72] - 2.795769818335074e-11*state[2] - 1.37e-11*state[3] - 4e-12*state[4] - 1.5513629410090206e-11*state[53] - 7.5e-12*state[66] - 7.5e-12*state[64];
  jacobian[69 * 82 + 72] = -1.5513629410090206e-11*state[69];
  jacobian[70 * 82 + 3] = -1001.3980443151514*state[70];
  jacobian[70 * 82 + 4] = 3.78e-12*state[46];
  jacobian[70 * 82 + 46] = 3.78e-12*state[4];
  jacobian[70 * 82 + 60] = -3.803841922183774e-11*state[70];
  jacobian[70 * 82 + 70] = -3.803841922183774e-11*state[60] - 1001.3980443151514*state[3] - 1.487214735018438e-11;
  jacobian[71 * 82 + 2] = 2.795769818335074e-11*state[69];
  jacobian[71 * 82 + 3] = -3.803841922183774e-11*state[71];
  jacobian[71 * 82 + 4] = 4e-12*state[69] + 1.37e-11*state[24] + 3.78e-12*state[47];
  jacobian[71 * 82 + 24] = 1.37e-11*state[4] + 1.008e-11*state[59];
  jacobian[71 * 82 + 47] = 3.78e-12*state[4] + 6.312e-12*state[59];
  jacobian[71 * 82 + 53] = 1.5513629410090206e-11*state[69];
  jacobian[71 * 82 + 59] = 1.008e-11*state[24] + 6.312e-12*state[47];
  jacobian[71 * 82 + 60] = -1.487214735018438e-11*state[71];
  jacobian[71 * 82 + 68] = 1.5513629410090206e-11*state[69];
  jacobian[71 * 82 + 69] = 6.205451764036082e-11*state[69] + 1.5513629410090206e-11*state[68] + 1.5513629410090206e-11*state[72] + 2.795769818335074e-11*state[2] + 4e-12*state[4] + 1.5513629410090206e-11*state[53];
  jacobian[71 * 82 + 71] = -1.487214735018438e-11*state[60] - 3.803841922183774e-11*state[3] - 0.001;
  jacobian[71 * 82 + 72] = 1.5513629410090206e-11*state[69];
  jacobian[72 * 82 + 0] = 2.475401376906824e-18*state[34];
  jacobian[72 * 82 + 2] = -2.795769818335074e-11*state[72];
  jacobian[72 * 82 + 3] = -1.2066992504885926e-11*state[72];
  jacobian[72 * 82 + 4] = 1.5e-14*state[26] - 4e-12*state[72] + 2.295706961427809e-15*state[27];
  jacobian[72 * 82 + 26] = 1.5e-14*state[4] + 1.78891e-11*state[59];
  jacobian[72 * 82 + 27] = 2.295706961427809e-15*state[4] + 1.67822418171901e-11*state[59] + 0.33*jvals[23];
  jacobian[72 * 82 + 28] = 0.3*jvals[24];
  jacobian[72 * 82 + 34] = 2.475401376906824e-18*state[0] + 8.64e-12*state[57];
  jacobian[72 * 82 + 51] = 0.0003630752223904921;
  jacobian[72 * 82 + 53] = -1.5513629410090206e-11*state[72];
  jacobian[72 * 82 + 57] = 8.64e-12*state[34];
  jacobian[72 * 82 + 59] = 1.78891e-11*state[26] + 1.67822418171901e-11*state[27];
  jacobian[72 * 82 + 60] = -1.4072281644582305e-11*state[72];
  jacobian[72 * 82 + 61] = -9.629149289021505e-12*state[72];
  jacobian[72 * 82 + 64] = -7.5e-12*state[72];
  jacobian[72 * 82 + 66] = -7.5e-12*state[72];
  jacobian[72 * 82 + 68] = -1.5513629410090206e-11*state[72];
  jacobian[72 * 82 + 69] = -1.5513629410090206e-11*state[72];
  jacobian[72 * 82 + 72] = -1.5513629410090206e-11*state[69] - 1.5513629410090206e-11*state[68] - 9.629149289021505e-12*state[61] - 1.4072281644582305e-11*state[60] - 6.205451764036082e-11*state[72] - 2.795769818335074e-11*state[2] - 1.2066992504885926e-11*state[3] - 4e-12*state[4] - 1.5513629410090206e-11*state[53] - 7.5e-12*state[66] - 7.5e-12*state[64];
  jacobian[73 * 82 + 3] = -2.4e-11*state[73];
  jacobian[73 * 82 + 37] = 5.609296629120887e-13*state[59];
  jacobian[73 * 82 + 59] = 5.609296629120887e-13*state[37];
  jacobian[73 * 82 + 73] = -2.4e-11*state[3] - 1001.3980443151514;
  jacobian[75 * 82 + 0] = 1.597572121590464e-14*state[57];
  jacobian[75 * 82 + 2] = -3.90443570238861e-38*state[2]*state[75];
  jacobian[75 * 82 + 57] = -5.779235214948339e-34*state[74]*state[75] + 1.597572121590464e-14*state[0];
  jacobian[75 * 82 + 59] = 1.1101941762569073e-10*state[60];
  jacobian[75 * 82 + 60] = 1.1101941762569073e-10*state[59];
  jacobian[75 * 82 + 74] = -5.779235214948339e-34*state[75]*state[57];
  jacobian[75 * 82 + 75] = -5.779235214948339e-34*state[74]*state[57] - 1.952217851194305e-38*(state[2] * state[2]);
  jacobian[76 * 82 + 5] = -2.6e-22*state[76];
  jacobian[76 * 82 + 58] = -2.2e-10*state[76];
  jacobian[76 * 82 + 59] = 1.1101941762569073e-10*state[60];
  jacobian[76 * 82 + 60] = -2.0*state[76]*state[60]*(1.1101605816625855e-49*state[74] + 3.690770493620667e-30) + 1.1101941762569073e-10*state[59];
  jacobian[76 * 82 + 74] = -1.1101605816625855e-49*state[76]*(state[60] * state[60]);
  jacobian[76 * 82 + 76] = -1.0*(state[60] * state[60])*(1.1101605816625855e-49*state[74] + 3.690770493620667e-30) - 2.6e-22*state[5] - 2.2e-10*state[58];
  jacobian[77 * 82 + 59] = -6.723044449434636e-15*state[77];
  jacobian[77 * 82 + 77] = -6.723044449434636e-15*state[59];
  jacobian[78 * 82 + 59] = -6.385339164031197e-15*state[78];
  jacobian[78 * 82 + 78] = -6.385339164031197e-15*state[59];
}
}  // namespace mkpp::detail::saprc99
#ifdef MKPP_GENERATED_MECHANISM_NAMESPACE
}  // namespace MKPP_GENERATED_MECHANISM_NAMESPACE
#endif
