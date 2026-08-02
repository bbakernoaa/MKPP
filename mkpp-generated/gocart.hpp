#pragma once
#include <Kokkos_Core.hpp>
// Generated solver for gocart
// SZA Workload Sorted: true
// Hysteresis/Spline Continuous Transition: true
namespace mkpp {
  // Pure Kokkos abstractions (no raw pragmas allowed)
  // Bidirectional Host Interface (Zero-Copy)
  using concentrations_view_t = Kokkos::View<double****, Kokkos::LayoutLeft, Kokkos::MemoryUnmanaged>;
  template<typename DeviceType>
  struct SolverKernels {
      KOKKOS_INLINE_FUNCTION void lu_decompose(double* A, int N, int* indx) const {
          for (int i = 0; i < N; i++) {
              double max_val = 0.0;
              int max_idx = i;
              for (int k = i; k < N; k++) {
                  double val = A[k * N + i];
                  if (val < 0) val = -val;
                  if (val > max_val) { max_val = val; max_idx = k; }
              }
              indx[i] = max_idx;
              if (max_idx != i) {
                  for (int j = 0; j < N; j++) {
                      double temp = A[i * N + j];
                      A[i * N + j] = A[max_idx * N + j];
                      A[max_idx * N + j] = temp;
                  }
              }
              for (int j = i + 1; j < N; j++) {
                  A[j * N + i] /= A[i * N + i];
                  for (int k = i + 1; k < N; k++) {
                      A[j * N + k] -= A[j * N + i] * A[i * N + k];
                  }
              }
          }
      }

      KOKKOS_INLINE_FUNCTION void lu_solve(double* A, int N, int* indx, double* b) const {
          for (int i = 0; i < N; i++) {
              int ip = indx[i];
              double sum = b[ip];
              b[ip] = b[i];
              for (int j = 0; j < i; j++) {
                  sum -= A[i * N + j] * b[j];
              }
              b[i] = sum;
          }
          for (int i = N - 1; i >= 0; i--) {
              double sum = b[i];
              for (int j = i + 1; j < N; j++) {
                  sum -= A[i * N + j] * b[j];
              }
              b[i] = sum / A[i * N + i];
          }
      }

      KOKKOS_INLINE_FUNCTION void integrate(double dt, double* state) const {
          const int NUM_SPECIES = 26;
          const double g = 1.70710678118655;
          const double ros_A[1] = {1.0/g};
          const double ros_C[1] = {-2.0/g};
          const double ros_M[2] = {3.0/(2.0*g), 1.0/(2.0*g)};
          
          double Ynew[100];
          double F1[100], F2[100];
          double K1[100], K2[100];
          double Jac[10000] = {0.0};
          double W[10000];
          int indx[100];
          
          compute_rates(state, F1);
          compute_jacobian(state, Jac);
          
          for(int i=0; i<NUM_SPECIES; i++) {
              for(int j=0; j<NUM_SPECIES; j++) {
                  W[i*NUM_SPECIES + j] = -Jac[i*NUM_SPECIES + j];
                  if (i==j) W[i*NUM_SPECIES + j] += 1.0/(g*dt);
              }
          }
          lu_decompose(W, NUM_SPECIES, indx);
          
          for(int i=0; i<NUM_SPECIES; i++) K1[i] = F1[i];
          lu_solve(W, NUM_SPECIES, indx, K1);
          
          for(int i=0; i<NUM_SPECIES; i++) Ynew[i] = state[i] + ros_A[0] * K1[i];
          compute_rates(Ynew, F2);
          
          for(int i=0; i<NUM_SPECIES; i++) {
              K2[i] = F2[i] + (ros_C[0]/dt) * K1[i];
          }
          lu_solve(W, NUM_SPECIES, indx, K2);
          
          for(int i=0; i<NUM_SPECIES; i++) {
              state[i] += ros_M[0] * K1[i] + ros_M[1] * K2[i];
          }
      }

      KOKKOS_INLINE_FUNCTION void compute_rates(double* state, double* F_block) const {
      }

      KOKKOS_INLINE_FUNCTION void compute_jacobian(double* state, double* J_block) const {
          J_block[0] = -1.0*3.3e-12*state[4];
          J_block[4] = -1.0*3.3e-12*state[0];
          J_block[104] = -1.0*3.3e-12*state[4];
          J_block[108] = -0.25*0.0001*state[10]*1.0*1.0 - 0.25*0.0001*state[11]*1.0*1.0 - 0.25*0.0001*state[12]*1.0*1.0 - 0.25*0.0001*state[13]*1.0*1.0 - 0.25*0.0001*state[14]*1.0*1.0 - 0.25*0.001*state[15]*1.0*1.0 - 0.25*0.001*state[16]*1.0*1.0 - 0.25*0.001*state[17]*1.0*1.0 - 0.25*0.001*state[18]*1.0*1.0 - 0.25*0.001*state[19]*1.0*1.0 - 1.0*3.3e-12*state[0];
          J_block[114] = -0.25*0.0001*state[4]*1.0*1.0;
          J_block[115] = -0.25*0.0001*state[4]*1.0*1.0;
          J_block[116] = -0.25*0.0001*state[4]*1.0*1.0;
          J_block[117] = -0.25*0.0001*state[4]*1.0*1.0;
          J_block[118] = -0.25*0.0001*state[4]*1.0*1.0;
          J_block[119] = -0.25*0.001*state[4]*1.0*1.0;
          J_block[120] = -0.25*0.001*state[4]*1.0*1.0;
          J_block[121] = -0.25*0.001*state[4]*1.0*1.0;
          J_block[122] = -0.25*0.001*state[4]*1.0*1.0;
          J_block[123] = -0.25*0.001*state[4]*1.0*1.0;
          J_block[130] = 1.0*3.3e-12*state[4];
          J_block[134] = 0.25*0.0001*state[10]*1.0*1.0 + 0.25*0.0001*state[11]*1.0*1.0 + 0.25*0.0001*state[12]*1.0*1.0 + 0.25*0.0001*state[13]*1.0*1.0 + 0.25*0.0001*state[14]*1.0*1.0 + 0.25*0.001*state[15]*1.0*1.0 + 0.25*0.001*state[16]*1.0*1.0 + 0.25*0.001*state[17]*1.0*1.0 + 0.25*0.001*state[18]*1.0*1.0 + 0.25*0.001*state[19]*1.0*1.0 + 1.0*3.3e-12*state[0];
          J_block[140] = 0.25*0.0001*state[4]*1.0*1.0;
          J_block[141] = 0.25*0.0001*state[4]*1.0*1.0;
          J_block[142] = 0.25*0.0001*state[4]*1.0*1.0;
          J_block[143] = 0.25*0.0001*state[4]*1.0*1.0;
          J_block[144] = 0.25*0.0001*state[4]*1.0*1.0;
          J_block[145] = 0.25*0.001*state[4]*1.0*1.0;
          J_block[146] = 0.25*0.001*state[4]*1.0*1.0;
          J_block[147] = 0.25*0.001*state[4]*1.0*1.0;
          J_block[148] = 0.25*0.001*state[4]*1.0*1.0;
          J_block[149] = 0.25*0.001*state[4]*1.0*1.0;
          J_block[530] = -0.25*0.1*state[20]*1.0*1.0;
          J_block[531] = -0.25*0.1*state[20]*1.0*1.0;
          J_block[532] = -0.25*0.1*state[20]*1.0*1.0;
          J_block[533] = -0.25*0.1*state[20]*1.0*1.0;
          J_block[534] = -0.25*0.1*state[20]*1.0*1.0;
          J_block[535] = -0.25*0.1*state[20]*1.0*1.0;
          J_block[536] = -0.25*0.1*state[20]*1.0*1.0;
          J_block[537] = -0.25*0.1*state[20]*1.0*1.0;
          J_block[538] = -0.25*0.1*state[20]*1.0*1.0;
          J_block[539] = -0.25*0.1*state[20]*1.0*1.0;
          J_block[540] = -0.25*0.1*state[10]*1.0*1.0 - 0.25*0.1*state[11]*1.0*1.0 - 0.25*0.1*state[12]*1.0*1.0 - 0.25*0.1*state[13]*1.0*1.0 - 0.25*0.1*state[14]*1.0*1.0 - 0.25*0.1*state[15]*1.0*1.0 - 0.25*0.1*state[16]*1.0*1.0 - 0.25*0.1*state[17]*1.0*1.0 - 0.25*0.1*state[18]*1.0*1.0 - 0.25*0.1*state[19]*1.0*1.0;
          J_block[608] = 0.25*0.1*state[20]*1.0*1.0;
          J_block[611] = 0.25*0.1*state[20]*1.0*1.0;
          J_block[614] = 0.25*0.1*state[20]*1.0*1.0;
          J_block[617] = 0.25*0.1*state[20]*1.0*1.0;
          J_block[618] = 0.25*0.1*state[10]*1.0*1.0 + 0.25*0.1*state[13]*1.0*1.0 + 0.25*0.1*state[16]*1.0*1.0 + 0.25*0.1*state[19]*1.0*1.0;
          J_block[635] = 0.25*0.1*state[20]*1.0*1.0;
          J_block[638] = 0.25*0.1*state[20]*1.0*1.0;
          J_block[641] = 0.25*0.1*state[20]*1.0*1.0;
          J_block[644] = 0.25*0.1*state[11]*1.0*1.0 + 0.25*0.1*state[14]*1.0*1.0 + 0.25*0.1*state[17]*1.0*1.0;
          J_block[662] = 0.25*0.1*state[20]*1.0*1.0;
          J_block[665] = 0.25*0.1*state[20]*1.0*1.0;
          J_block[668] = 0.25*0.1*state[20]*1.0*1.0;
          J_block[670] = 0.25*0.1*state[12]*1.0*1.0 + 0.25*0.1*state[15]*1.0*1.0 + 0.25*0.1*state[18]*1.0*1.0;
      }
      KOKKOS_INLINE_FUNCTION void compute_adjoint(double* state, double* J_adj_block) const {
          J_adj_block[0] = -1.0*3.3e-12*state[4];
          J_adj_block[4] = -1.0*3.3e-12*state[4];
          J_adj_block[5] = 1.0*3.3e-12*state[4];
          J_adj_block[104] = -1.0*3.3e-12*state[0];
          J_adj_block[108] = -0.25*0.0001*state[10]*1.0*1.0 - 0.25*0.0001*state[11]*1.0*1.0 - 0.25*0.0001*state[12]*1.0*1.0 - 0.25*0.0001*state[13]*1.0*1.0 - 0.25*0.0001*state[14]*1.0*1.0 - 0.25*0.001*state[15]*1.0*1.0 - 0.25*0.001*state[16]*1.0*1.0 - 0.25*0.001*state[17]*1.0*1.0 - 0.25*0.001*state[18]*1.0*1.0 - 0.25*0.001*state[19]*1.0*1.0 - 1.0*3.3e-12*state[0];
          J_adj_block[109] = 0.25*0.0001*state[10]*1.0*1.0 + 0.25*0.0001*state[11]*1.0*1.0 + 0.25*0.0001*state[12]*1.0*1.0 + 0.25*0.0001*state[13]*1.0*1.0 + 0.25*0.0001*state[14]*1.0*1.0 + 0.25*0.001*state[15]*1.0*1.0 + 0.25*0.001*state[16]*1.0*1.0 + 0.25*0.001*state[17]*1.0*1.0 + 0.25*0.001*state[18]*1.0*1.0 + 0.25*0.001*state[19]*1.0*1.0 + 1.0*3.3e-12*state[0];
          J_adj_block[264] = -0.25*0.0001*state[4]*1.0*1.0;
          J_adj_block[265] = 0.25*0.0001*state[4]*1.0*1.0;
          J_adj_block[280] = -0.25*0.1*state[20]*1.0*1.0;
          J_adj_block[283] = 0.25*0.1*state[20]*1.0*1.0;
          J_adj_block[290] = -0.25*0.0001*state[4]*1.0*1.0;
          J_adj_block[291] = 0.25*0.0001*state[4]*1.0*1.0;
          J_adj_block[306] = -0.25*0.1*state[20]*1.0*1.0;
          J_adj_block[310] = 0.25*0.1*state[20]*1.0*1.0;
          J_adj_block[316] = -0.25*0.0001*state[4]*1.0*1.0;
          J_adj_block[317] = 0.25*0.0001*state[4]*1.0*1.0;
          J_adj_block[332] = -0.25*0.1*state[20]*1.0*1.0;
          J_adj_block[337] = 0.25*0.1*state[20]*1.0*1.0;
          J_adj_block[342] = -0.25*0.0001*state[4]*1.0*1.0;
          J_adj_block[343] = 0.25*0.0001*state[4]*1.0*1.0;
          J_adj_block[358] = -0.25*0.1*state[20]*1.0*1.0;
          J_adj_block[361] = 0.25*0.1*state[20]*1.0*1.0;
          J_adj_block[368] = -0.25*0.0001*state[4]*1.0*1.0;
          J_adj_block[369] = 0.25*0.0001*state[4]*1.0*1.0;
          J_adj_block[384] = -0.25*0.1*state[20]*1.0*1.0;
          J_adj_block[388] = 0.25*0.1*state[20]*1.0*1.0;
          J_adj_block[394] = -0.25*0.001*state[4]*1.0*1.0;
          J_adj_block[395] = 0.25*0.001*state[4]*1.0*1.0;
          J_adj_block[410] = -0.25*0.1*state[20]*1.0*1.0;
          J_adj_block[415] = 0.25*0.1*state[20]*1.0*1.0;
          J_adj_block[420] = -0.25*0.001*state[4]*1.0*1.0;
          J_adj_block[421] = 0.25*0.001*state[4]*1.0*1.0;
          J_adj_block[436] = -0.25*0.1*state[20]*1.0*1.0;
          J_adj_block[439] = 0.25*0.1*state[20]*1.0*1.0;
          J_adj_block[446] = -0.25*0.001*state[4]*1.0*1.0;
          J_adj_block[447] = 0.25*0.001*state[4]*1.0*1.0;
          J_adj_block[462] = -0.25*0.1*state[20]*1.0*1.0;
          J_adj_block[466] = 0.25*0.1*state[20]*1.0*1.0;
          J_adj_block[472] = -0.25*0.001*state[4]*1.0*1.0;
          J_adj_block[473] = 0.25*0.001*state[4]*1.0*1.0;
          J_adj_block[488] = -0.25*0.1*state[20]*1.0*1.0;
          J_adj_block[493] = 0.25*0.1*state[20]*1.0*1.0;
          J_adj_block[498] = -0.25*0.001*state[4]*1.0*1.0;
          J_adj_block[499] = 0.25*0.001*state[4]*1.0*1.0;
          J_adj_block[514] = -0.25*0.1*state[20]*1.0*1.0;
          J_adj_block[517] = 0.25*0.1*state[20]*1.0*1.0;
          J_adj_block[540] = -0.25*0.1*state[10]*1.0*1.0 - 0.25*0.1*state[11]*1.0*1.0 - 0.25*0.1*state[12]*1.0*1.0 - 0.25*0.1*state[13]*1.0*1.0 - 0.25*0.1*state[14]*1.0*1.0 - 0.25*0.1*state[15]*1.0*1.0 - 0.25*0.1*state[16]*1.0*1.0 - 0.25*0.1*state[17]*1.0*1.0 - 0.25*0.1*state[18]*1.0*1.0 - 0.25*0.1*state[19]*1.0*1.0;
          J_adj_block[543] = 0.25*0.1*state[10]*1.0*1.0 + 0.25*0.1*state[13]*1.0*1.0 + 0.25*0.1*state[16]*1.0*1.0 + 0.25*0.1*state[19]*1.0*1.0;
          J_adj_block[544] = 0.25*0.1*state[11]*1.0*1.0 + 0.25*0.1*state[14]*1.0*1.0 + 0.25*0.1*state[17]*1.0*1.0;
          J_adj_block[545] = 0.25*0.1*state[12]*1.0*1.0 + 0.25*0.1*state[15]*1.0*1.0 + 0.25*0.1*state[18]*1.0*1.0;
      }
      KOKKOS_INLINE_FUNCTION void compute_tlm(double* state, double* delta_C, double* dF_block) const {
          dF_block[0] = 0.0;
          dF_block[0] += (-1.0*3.3e-12*state[4]) * delta_C[0];
          dF_block[0] += (-1.0*3.3e-12*state[0]) * delta_C[4];
          dF_block[1] = 0.0;
          dF_block[2] = 0.0;
          dF_block[3] = 0.0;
          dF_block[4] = 0.0;
          dF_block[4] += (-1.0*3.3e-12*state[4]) * delta_C[0];
          dF_block[4] += (-0.25*0.0001*state[10]*1.0*1.0 - 0.25*0.0001*state[11]*1.0*1.0 - 0.25*0.0001*state[12]*1.0*1.0 - 0.25*0.0001*state[13]*1.0*1.0 - 0.25*0.0001*state[14]*1.0*1.0 - 0.25*0.001*state[15]*1.0*1.0 - 0.25*0.001*state[16]*1.0*1.0 - 0.25*0.001*state[17]*1.0*1.0 - 0.25*0.001*state[18]*1.0*1.0 - 0.25*0.001*state[19]*1.0*1.0 - 1.0*3.3e-12*state[0]) * delta_C[4];
          dF_block[4] += (-0.25*0.0001*state[4]*1.0*1.0) * delta_C[10];
          dF_block[4] += (-0.25*0.0001*state[4]*1.0*1.0) * delta_C[11];
          dF_block[4] += (-0.25*0.0001*state[4]*1.0*1.0) * delta_C[12];
          dF_block[4] += (-0.25*0.0001*state[4]*1.0*1.0) * delta_C[13];
          dF_block[4] += (-0.25*0.0001*state[4]*1.0*1.0) * delta_C[14];
          dF_block[4] += (-0.25*0.001*state[4]*1.0*1.0) * delta_C[15];
          dF_block[4] += (-0.25*0.001*state[4]*1.0*1.0) * delta_C[16];
          dF_block[4] += (-0.25*0.001*state[4]*1.0*1.0) * delta_C[17];
          dF_block[4] += (-0.25*0.001*state[4]*1.0*1.0) * delta_C[18];
          dF_block[4] += (-0.25*0.001*state[4]*1.0*1.0) * delta_C[19];
          dF_block[5] = 0.0;
          dF_block[5] += (1.0*3.3e-12*state[4]) * delta_C[0];
          dF_block[5] += (0.25*0.0001*state[10]*1.0*1.0 + 0.25*0.0001*state[11]*1.0*1.0 + 0.25*0.0001*state[12]*1.0*1.0 + 0.25*0.0001*state[13]*1.0*1.0 + 0.25*0.0001*state[14]*1.0*1.0 + 0.25*0.001*state[15]*1.0*1.0 + 0.25*0.001*state[16]*1.0*1.0 + 0.25*0.001*state[17]*1.0*1.0 + 0.25*0.001*state[18]*1.0*1.0 + 0.25*0.001*state[19]*1.0*1.0 + 1.0*3.3e-12*state[0]) * delta_C[4];
          dF_block[5] += (0.25*0.0001*state[4]*1.0*1.0) * delta_C[10];
          dF_block[5] += (0.25*0.0001*state[4]*1.0*1.0) * delta_C[11];
          dF_block[5] += (0.25*0.0001*state[4]*1.0*1.0) * delta_C[12];
          dF_block[5] += (0.25*0.0001*state[4]*1.0*1.0) * delta_C[13];
          dF_block[5] += (0.25*0.0001*state[4]*1.0*1.0) * delta_C[14];
          dF_block[5] += (0.25*0.001*state[4]*1.0*1.0) * delta_C[15];
          dF_block[5] += (0.25*0.001*state[4]*1.0*1.0) * delta_C[16];
          dF_block[5] += (0.25*0.001*state[4]*1.0*1.0) * delta_C[17];
          dF_block[5] += (0.25*0.001*state[4]*1.0*1.0) * delta_C[18];
          dF_block[5] += (0.25*0.001*state[4]*1.0*1.0) * delta_C[19];
          dF_block[6] = 0.0;
          dF_block[7] = 0.0;
          dF_block[8] = 0.0;
          dF_block[9] = 0.0;
          dF_block[10] = 0.0;
          dF_block[11] = 0.0;
          dF_block[12] = 0.0;
          dF_block[13] = 0.0;
          dF_block[14] = 0.0;
          dF_block[15] = 0.0;
          dF_block[16] = 0.0;
          dF_block[17] = 0.0;
          dF_block[18] = 0.0;
          dF_block[19] = 0.0;
          dF_block[20] = 0.0;
          dF_block[20] += (-0.25*0.1*state[20]*1.0*1.0) * delta_C[10];
          dF_block[20] += (-0.25*0.1*state[20]*1.0*1.0) * delta_C[11];
          dF_block[20] += (-0.25*0.1*state[20]*1.0*1.0) * delta_C[12];
          dF_block[20] += (-0.25*0.1*state[20]*1.0*1.0) * delta_C[13];
          dF_block[20] += (-0.25*0.1*state[20]*1.0*1.0) * delta_C[14];
          dF_block[20] += (-0.25*0.1*state[20]*1.0*1.0) * delta_C[15];
          dF_block[20] += (-0.25*0.1*state[20]*1.0*1.0) * delta_C[16];
          dF_block[20] += (-0.25*0.1*state[20]*1.0*1.0) * delta_C[17];
          dF_block[20] += (-0.25*0.1*state[20]*1.0*1.0) * delta_C[18];
          dF_block[20] += (-0.25*0.1*state[20]*1.0*1.0) * delta_C[19];
          dF_block[20] += (-0.25*0.1*state[10]*1.0*1.0 - 0.25*0.1*state[11]*1.0*1.0 - 0.25*0.1*state[12]*1.0*1.0 - 0.25*0.1*state[13]*1.0*1.0 - 0.25*0.1*state[14]*1.0*1.0 - 0.25*0.1*state[15]*1.0*1.0 - 0.25*0.1*state[16]*1.0*1.0 - 0.25*0.1*state[17]*1.0*1.0 - 0.25*0.1*state[18]*1.0*1.0 - 0.25*0.1*state[19]*1.0*1.0) * delta_C[20];
          dF_block[21] = 0.0;
          dF_block[22] = 0.0;
          dF_block[23] = 0.0;
          dF_block[23] += (0.25*0.1*state[20]*1.0*1.0) * delta_C[10];
          dF_block[23] += (0.25*0.1*state[20]*1.0*1.0) * delta_C[13];
          dF_block[23] += (0.25*0.1*state[20]*1.0*1.0) * delta_C[16];
          dF_block[23] += (0.25*0.1*state[20]*1.0*1.0) * delta_C[19];
          dF_block[23] += (0.25*0.1*state[10]*1.0*1.0 + 0.25*0.1*state[13]*1.0*1.0 + 0.25*0.1*state[16]*1.0*1.0 + 0.25*0.1*state[19]*1.0*1.0) * delta_C[20];
          dF_block[24] = 0.0;
          dF_block[24] += (0.25*0.1*state[20]*1.0*1.0) * delta_C[11];
          dF_block[24] += (0.25*0.1*state[20]*1.0*1.0) * delta_C[14];
          dF_block[24] += (0.25*0.1*state[20]*1.0*1.0) * delta_C[17];
          dF_block[24] += (0.25*0.1*state[11]*1.0*1.0 + 0.25*0.1*state[14]*1.0*1.0 + 0.25*0.1*state[17]*1.0*1.0) * delta_C[20];
          dF_block[25] = 0.0;
          dF_block[25] += (0.25*0.1*state[20]*1.0*1.0) * delta_C[12];
          dF_block[25] += (0.25*0.1*state[20]*1.0*1.0) * delta_C[15];
          dF_block[25] += (0.25*0.1*state[20]*1.0*1.0) * delta_C[18];
          dF_block[25] += (0.25*0.1*state[12]*1.0*1.0 + 0.25*0.1*state[15]*1.0*1.0 + 0.25*0.1*state[18]*1.0*1.0) * delta_C[20];
      }
      KOKKOS_INLINE_FUNCTION void project_mass_conservation(double* C_projected, double* C, double* m_0) const {
          // C_projected = C - E^T (E E^T)^-1 (E C - m_0)
          double delta_m[100] = {0.0};
          C_projected[0] = C[0];
          C_projected[1] = C[1];
          C_projected[2] = C[2];
          C_projected[3] = C[3];
          C_projected[4] = C[4];
          C_projected[5] = C[5];
          C_projected[6] = C[6];
          C_projected[7] = C[7];
          C_projected[8] = C[8];
          C_projected[9] = C[9];
          C_projected[10] = C[10];
          C_projected[11] = C[11];
          C_projected[12] = C[12];
          C_projected[13] = C[13];
          C_projected[14] = C[14];
          C_projected[15] = C[15];
          C_projected[16] = C[16];
          C_projected[17] = C[17];
          C_projected[18] = C[18];
          C_projected[19] = C[19];
          C_projected[20] = C[20];
          C_projected[21] = C[21];
          C_projected[22] = C[22];
          C_projected[23] = C[23];
          C_projected[24] = C[24];
          C_projected[25] = C[25];
      }
  };
}
