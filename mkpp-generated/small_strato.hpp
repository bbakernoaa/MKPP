#pragma once
#include <Kokkos_Core.hpp>
// Generated solver for small_strato
// Hysteresis/Spline Continuous Transition: true
namespace mkpp {
  // Pure Kokkos abstractions (no raw pragmas allowed)
  // Bidirectional Host Interface (Zero-Copy)
  using concentrations_view_t = Kokkos::View<double****, Kokkos::LayoutLeft, Kokkos::MemoryUnmanaged>;
  template<typename DeviceType>
  struct SolverKernels {
      template <class StateView, class RateView>
      KOKKOS_INLINE_FUNCTION void compute_rates(const StateView& state, RateView& F_block, const double* jvals) const {
          F_block(0) = 7.1100000000000005e-11*state(5)*state(1) - 1.0690000000000001e-11*state(4)*state(0) + 1.0*state(4)*jvals[3] - 8.0180000000000003e-17*state(0)*state(6) - 1.576e-15*state(0)*state(2) + 2.0*state(6)*jvals[0] + 1.0*state(2)*jvals[1];
          F_block(1) = -7.1100000000000005e-11*state(5)*state(1) - 1.2e-10*state(1)*state(2) + 1.0*state(2)*jvals[2];
          F_block(2) = -6.0620000000000003e-15*state(3)*state(2) + 8.0180000000000003e-17*state(0)*state(6) - 1.576e-15*state(0)*state(2) - 1.2e-10*state(1)*state(2) - 1.0*state(2)*jvals[1] - 1.0*state(2)*jvals[2];
          F_block(3) = -6.0620000000000003e-15*state(3)*state(2) + 1.0690000000000001e-11*state(4)*state(0) + 1.0*state(4)*jvals[3];
          F_block(4) = 6.0620000000000003e-15*state(3)*state(2) - 1.0690000000000001e-11*state(4)*state(0) - 1.0*state(4)*jvals[3];
          F_block(5) = 0.0;
          F_block(6) = 0.0;
      }

      template <class StateView, class JacView>
      KOKKOS_INLINE_FUNCTION void compute_jacobian(const StateView& state, JacView& J_block, const double* jvals) const {
          J_block(0, 0) = -1.0690000000000001e-11*state(4) - 8.0180000000000003e-17*state(6) - 1.576e-15*state(2);
          J_block(0, 1) = 7.1100000000000005e-11*state(5);
          J_block(0, 2) = -1.576e-15*state(0) + 1.0*jvals[1];
          J_block(0, 4) = -1.0690000000000001e-11*state(0) + 1.0*jvals[3];
          J_block(0, 5) = 7.1100000000000005e-11*state(1);
          J_block(0, 6) = -8.0180000000000003e-17*state(0) + 2.0*jvals[0];
          J_block(1, 1) = -7.1100000000000005e-11*state(5) - 1.2e-10*state(2);
          J_block(1, 2) = -1.2e-10*state(1) + 1.0*jvals[2];
          J_block(1, 5) = -7.1100000000000005e-11*state(1);
          J_block(2, 0) = 8.0180000000000003e-17*state(6) - 1.576e-15*state(2);
          J_block(2, 1) = -1.2e-10*state(2);
          J_block(2, 2) = -6.0620000000000003e-15*state(3) - 1.576e-15*state(0) - 1.2e-10*state(1) - 1.0*jvals[1] - 1.0*jvals[2];
          J_block(2, 3) = -6.0620000000000003e-15*state(2);
          J_block(2, 6) = 8.0180000000000003e-17*state(0);
          J_block(3, 0) = 1.0690000000000001e-11*state(4);
          J_block(3, 2) = -6.0620000000000003e-15*state(3);
          J_block(3, 3) = -6.0620000000000003e-15*state(2);
          J_block(3, 4) = 1.0690000000000001e-11*state(0) + 1.0*jvals[3];
          J_block(4, 0) = -1.0690000000000001e-11*state(4);
          J_block(4, 2) = 6.0620000000000003e-15*state(3);
          J_block(4, 3) = 6.0620000000000003e-15*state(2);
          J_block(4, 4) = -1.0690000000000001e-11*state(0) - 1.0*jvals[3];
      }

      template <class StateView, class JacView>
      KOKKOS_INLINE_FUNCTION void compute_adjoint(const StateView& state, JacView& J_adj_block, const double* jvals) const {
          J_adj_block(0, 0) = -1.0690000000000001e-11*state(4) - 8.0180000000000003e-17*state(6) - 1.576e-15*state(2);
          J_adj_block(0, 2) = 8.0180000000000003e-17*state(6) - 1.576e-15*state(2);
          J_adj_block(0, 3) = 1.0690000000000001e-11*state(4);
          J_adj_block(0, 4) = -1.0690000000000001e-11*state(4);
          J_adj_block(1, 0) = 7.1100000000000005e-11*state(5);
          J_adj_block(1, 1) = -7.1100000000000005e-11*state(5) - 1.2e-10*state(2);
          J_adj_block(1, 2) = -1.2e-10*state(2);
          J_adj_block(2, 0) = -1.576e-15*state(0) + 1.0*jvals[1];
          J_adj_block(2, 1) = -1.2e-10*state(1) + 1.0*jvals[2];
          J_adj_block(2, 2) = -6.0620000000000003e-15*state(3) - 1.576e-15*state(0) - 1.2e-10*state(1) - 1.0*jvals[1] - 1.0*jvals[2];
          J_adj_block(2, 3) = -6.0620000000000003e-15*state(3);
          J_adj_block(2, 4) = 6.0620000000000003e-15*state(3);
          J_adj_block(3, 2) = -6.0620000000000003e-15*state(2);
          J_adj_block(3, 3) = -6.0620000000000003e-15*state(2);
          J_adj_block(3, 4) = 6.0620000000000003e-15*state(2);
          J_adj_block(4, 0) = -1.0690000000000001e-11*state(0) + 1.0*jvals[3];
          J_adj_block(4, 3) = 1.0690000000000001e-11*state(0) + 1.0*jvals[3];
          J_adj_block(4, 4) = -1.0690000000000001e-11*state(0) - 1.0*jvals[3];
          J_adj_block(5, 0) = 7.1100000000000005e-11*state(1);
          J_adj_block(5, 1) = -7.1100000000000005e-11*state(1);
          J_adj_block(6, 0) = -8.0180000000000003e-17*state(0) + 2.0*jvals[0];
          J_adj_block(6, 2) = 8.0180000000000003e-17*state(0);
      }

      template <class StateView, class DeltaView, class RateView>
      KOKKOS_INLINE_FUNCTION void compute_tlm(const StateView& state, const DeltaView& delta_C, RateView& dF_block, const double* jvals) const {
          dF_block(0) = 0.0;
          dF_block(0) += (-1.0690000000000001e-11*state(4) - 8.0180000000000003e-17*state(6) - 1.576e-15*state(2)) * delta_C(0);
          dF_block(0) += (7.1100000000000005e-11*state(5)) * delta_C(1);
          dF_block(0) += (-1.576e-15*state(0) + 1.0*jvals[1]) * delta_C(2);
          dF_block(0) += (-1.0690000000000001e-11*state(0) + 1.0*jvals[3]) * delta_C(4);
          dF_block(0) += (7.1100000000000005e-11*state(1)) * delta_C(5);
          dF_block(0) += (-8.0180000000000003e-17*state(0) + 2.0*jvals[0]) * delta_C(6);
          dF_block(1) = 0.0;
          dF_block(1) += (-7.1100000000000005e-11*state(5) - 1.2e-10*state(2)) * delta_C(1);
          dF_block(1) += (-1.2e-10*state(1) + 1.0*jvals[2]) * delta_C(2);
          dF_block(1) += (-7.1100000000000005e-11*state(1)) * delta_C(5);
          dF_block(2) = 0.0;
          dF_block(2) += (8.0180000000000003e-17*state(6) - 1.576e-15*state(2)) * delta_C(0);
          dF_block(2) += (-1.2e-10*state(2)) * delta_C(1);
          dF_block(2) += (-6.0620000000000003e-15*state(3) - 1.576e-15*state(0) - 1.2e-10*state(1) - 1.0*jvals[1] - 1.0*jvals[2]) * delta_C(2);
          dF_block(2) += (-6.0620000000000003e-15*state(2)) * delta_C(3);
          dF_block(2) += (8.0180000000000003e-17*state(0)) * delta_C(6);
          dF_block(3) = 0.0;
          dF_block(3) += (1.0690000000000001e-11*state(4)) * delta_C(0);
          dF_block(3) += (-6.0620000000000003e-15*state(3)) * delta_C(2);
          dF_block(3) += (-6.0620000000000003e-15*state(2)) * delta_C(3);
          dF_block(3) += (1.0690000000000001e-11*state(0) + 1.0*jvals[3]) * delta_C(4);
          dF_block(4) = 0.0;
          dF_block(4) += (-1.0690000000000001e-11*state(4)) * delta_C(0);
          dF_block(4) += (6.0620000000000003e-15*state(3)) * delta_C(2);
          dF_block(4) += (6.0620000000000003e-15*state(2)) * delta_C(3);
          dF_block(4) += (-1.0690000000000001e-11*state(0) - 1.0*jvals[3]) * delta_C(4);
          dF_block(5) = 0.0;
          dF_block(6) = 0.0;
      }

      template <class StateView, class MassView>
      KOKKOS_INLINE_FUNCTION void project_mass_conservation(StateView& C_projected, const StateView& C, const MassView& m_0) const {
          // C_projected = C - E^T (E E^T)^-1 (E C - m_0)
          C_projected(0) = C(0);
          C_projected(1) = C(1);
          C_projected(2) = C(2);
          C_projected(3) = C(3);
          C_projected(4) = C(4);
          C_projected(5) = C(5);
          C_projected(6) = C(6);
      }

      static constexpr int NUM_SPECIES = 7;
      static constexpr double atol[NUM_SPECIES] = { 100.0, 100.0, 100.0, 100.0, 100.0, 100.0, 100.0 };
      static constexpr double rtol[NUM_SPECIES] = { 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01 };

      // Photolysis reactions (Cloud-J input mapping):
      //   jvals[0] = O2 -> O  (original A: 2.643E-10 * SUN*SUN*SUN)
      //   jvals[1] = O3 -> O, O2  (original A: 6.120E-04 * SUN)
      //   jvals[2] = O3 -> O1D, O2  (original A: 1.070E-03 * SUN*SUN)
      //   jvals[3] = NO2 -> NO, O  (original A: 1.289E-02 * SUN)
      static constexpr int NUM_PHOTOLYSIS = 4;

      template <class StateView>
      KOKKOS_INLINE_FUNCTION void integrate(double dt_total, StateView& state, const double* jvals) const {
          const int NUM_SPECIES = 7;
          // ROS-3 coefficients (3-stage, order 3)
          const double g = 0.435866521508459;
          const double safety = 0.9;
          const double max_growth = 6.0;
          const double min_shrink = 0.2;
          double t = 0.0;
          double dt = Kokkos::fmin(dt_total, 1.0);  // conservative initial step

          while (t < dt_total) {
          dt = Kokkos::min(dt, dt_total - t);
          const double inv_g_dt = 1.0 / (g * dt);

          // 0. Hoist state values into scalar registers
          // NOTE: State access uses permuted species ordering
          const double S_0 = state(5);
          const double S_1 = state(4);
          const double S_2 = state(3);
          const double S_3 = state(1);
          const double S_4 = state(0);
          const double S_5 = state(2);
          const double S_6 = state(6);

          // Analytical Jacobian & Iteration Matrix W = inv_g_dt*I - J (sparse)
          double J_1_1 = -1.0690000000000001e-11*S_4 - 1.0*jvals[3];
          double J_1_2 = 6.0620000000000003e-15*S_5;
          double J_1_4 = -1.0690000000000001e-11*S_1;
          double J_1_5 = 6.0620000000000003e-15*S_2;
          double J_2_1 = 1.0690000000000001e-11*S_4 + 1.0*jvals[3];
          double J_2_2 = -6.0620000000000003e-15*S_5;
          double J_2_4 = 1.0690000000000001e-11*S_1;
          double J_2_5 = -6.0620000000000003e-15*S_2;
          double J_3_0 = -7.1100000000000005e-11*S_3;
          double J_3_3 = -7.1100000000000005e-11*S_0 - 1.2e-10*S_5;
          double J_3_5 = -1.2e-10*S_3 + 1.0*jvals[2];
          double J_4_0 = 7.1100000000000005e-11*S_3;
          double J_4_1 = -1.0690000000000001e-11*S_4 + 1.0*jvals[3];
          double J_4_3 = 7.1100000000000005e-11*S_0;
          double J_4_4 = -1.0690000000000001e-11*S_1 - 8.0180000000000003e-17*S_6 - 1.576e-15*S_5;
          double J_4_5 = -1.576e-15*S_4 + 1.0*jvals[1];
          double J_4_6 = -8.0180000000000003e-17*S_4 + 2.0*jvals[0];
          double J_5_2 = -6.0620000000000003e-15*S_5;
          double J_5_3 = -1.2e-10*S_5;
          double J_5_4 = 8.0180000000000003e-17*S_6 - 1.576e-15*S_5;
          double J_5_5 = -6.0620000000000003e-15*S_2 - 1.576e-15*S_4 - 1.2e-10*S_3 - 1.0*jvals[1] - 1.0*jvals[2];
          double J_5_6 = 8.0180000000000003e-17*S_4;
          double W_0_0 = inv_g_dt;
          double W_1_1 = inv_g_dt - J_1_1;
          double W_1_2 = -J_1_2;
          double W_1_4 = -J_1_4;
          double W_1_5 = -J_1_5;
          double W_2_1 = -J_2_1;
          double W_2_2 = inv_g_dt - J_2_2;
          double W_2_4 = -J_2_4;
          double W_2_5 = -J_2_5;
          double W_3_0 = -J_3_0;
          double W_3_3 = inv_g_dt - J_3_3;
          double W_3_5 = -J_3_5;
          double W_4_0 = -J_4_0;
          double W_4_1 = -J_4_1;
          double W_4_3 = -J_4_3;
          double W_4_4 = inv_g_dt - J_4_4;
          double W_4_5 = -J_4_5;
          double W_4_6 = -J_4_6;
          double W_5_2 = -J_5_2;
          double W_5_3 = -J_5_3;
          double W_5_4 = -J_5_4;
          double W_5_5 = inv_g_dt - J_5_5;
          double W_5_6 = -J_5_6;
          double W_6_6 = inv_g_dt;

          // Symbolic Doolittle Sparse LU Factorization
          // Block 0: species [M, NO2, NO, O1D, O]
          double U_0_0 = W_0_0;
          double L_3_0 = (W_3_0) / U_0_0;
          double L_4_0 = (W_4_0) / U_0_0;
          double U_1_1 = W_1_1;
          double U_1_2 = W_1_2;
          double U_1_4 = W_1_4;
          double U_1_5 = W_1_5;
          double L_2_1 = (W_2_1) / U_1_1;
          double L_4_1 = (W_4_1) / U_1_1;
          double U_2_2 = W_2_2 - L_2_1 * U_1_2;
          double U_2_4 = W_2_4 - L_2_1 * U_1_4;
          double U_2_5 = W_2_5 - L_2_1 * U_1_5;
          double L_4_2 = (0.0 - L_4_1 * U_1_2) / U_2_2;
          // Block 1: species [O3]
          double L_5_2 = (W_5_2) / U_2_2;
          double U_3_3 = W_3_3;
          double U_3_5 = W_3_5;
          double L_4_3 = (W_4_3) / U_3_3;
          double L_5_3 = (W_5_3) / U_3_3;
          double U_4_4 = W_4_4 - L_4_1 * U_1_4 - L_4_2 * U_2_4;
          double U_4_5 = W_4_5 - L_4_1 * U_1_5 - L_4_2 * U_2_5 - L_4_3 * U_3_5;
          double U_4_6 = W_4_6;
          double L_5_4 = (W_5_4 - L_5_2 * U_2_4) / U_4_4;
          double U_5_5 = W_5_5 - L_5_2 * U_2_5 - L_5_3 * U_3_5 - L_5_4 * U_4_5;
          double U_5_6 = W_5_6 - L_5_4 * U_4_6;
          // Block 2: species [O2]
          double U_6_6 = W_6_6;

          // --- Stage 1 ---
          // Rate evaluation F1 at S
          double F1_0 = 0.0;
          double F1_1 = 6.0620000000000003e-15*S_2*S_5 - 1.0690000000000001e-11*S_1*S_4 - 1.0*S_1*jvals[3];
          double F1_2 = -6.0620000000000003e-15*S_2*S_5 + 1.0690000000000001e-11*S_1*S_4 + 1.0*S_1*jvals[3];
          double F1_3 = -7.1100000000000005e-11*S_0*S_3 - 1.2e-10*S_3*S_5 + 1.0*S_5*jvals[2];
          double F1_4 = 7.1100000000000005e-11*S_0*S_3 - 1.0690000000000001e-11*S_1*S_4 + 1.0*S_1*jvals[3] - 8.0180000000000003e-17*S_4*S_6 - 1.576e-15*S_4*S_5 + 2.0*S_6*jvals[0] + 1.0*S_5*jvals[1];
          double F1_5 = -6.0620000000000003e-15*S_2*S_5 + 8.0180000000000003e-17*S_4*S_6 - 1.576e-15*S_4*S_5 - 1.2e-10*S_3*S_5 - 1.0*S_5*jvals[1] - 1.0*S_5*jvals[2];
          double F1_6 = 0.0;
          // Block 0: K1 forward sub [M, NO2, NO, O1D, O]
          double y1_0 = F1_0;
          double y1_1 = F1_1;
          double y1_2 = F1_2 - L_2_1 * y1_1;
          double y1_3 = F1_3 - L_3_0 * y1_0;
          double y1_4 = F1_4 - L_4_0 * y1_0 - L_4_1 * y1_1 - L_4_2 * y1_2 - L_4_3 * y1_3;
          // Block 1: K1 forward sub [O3]
          double y1_5 = F1_5 - L_5_2 * y1_2 - L_5_3 * y1_3 - L_5_4 * y1_4;
          // Block 2: K1 forward sub [O2]
          double y1_6 = F1_6;
          // Block 2: K1 backward sub [O2]
          double K1_6 = y1_6 / U_6_6;
          // Block 1: K1 backward sub [O3]
          double K1_5 = (y1_5 - U_5_6 * K1_6) / U_5_5;
          // Block 0: K1 backward sub [M, NO2, NO, O1D, O]
          double K1_4 = (y1_4 - U_4_5 * K1_5 - U_4_6 * K1_6) / U_4_4;
          double K1_3 = (y1_3 - U_3_5 * K1_5) / U_3_3;
          double K1_2 = (y1_2 - U_2_4 * K1_4 - U_2_5 * K1_5) / U_2_2;
          double K1_1 = (y1_1 - U_1_2 * K1_2 - U_1_4 * K1_4 - U_1_5 * K1_5) / U_1_1;
          double K1_0 = y1_0 / U_0_0;

          // --- Stage 2 ---
          // Intermediate state Y2
          double Y2_0 = S_0 + K1_0;
          double Y2_1 = S_1 + K1_1;
          double Y2_2 = S_2 + K1_2;
          double Y2_3 = S_3 + K1_3;
          double Y2_4 = S_4 + K1_4;
          double Y2_5 = S_5 + K1_5;
          double Y2_6 = S_6 + K1_6;
          // Rate evaluation F2 at Y2
          double F2_0 = 0.0;
          double F2_1 = 6.0620000000000003e-15*Y2_2*Y2_5 - 1.0690000000000001e-11*Y2_1*Y2_4 - 1.0*Y2_1*jvals[3];
          double F2_2 = -6.0620000000000003e-15*Y2_2*Y2_5 + 1.0690000000000001e-11*Y2_1*Y2_4 + 1.0*Y2_1*jvals[3];
          double F2_3 = -7.1100000000000005e-11*Y2_0*Y2_3 - 1.2e-10*Y2_3*Y2_5 + 1.0*Y2_5*jvals[2];
          double F2_4 = 7.1100000000000005e-11*Y2_0*Y2_3 - 1.0690000000000001e-11*Y2_1*Y2_4 + 1.0*Y2_1*jvals[3] - 8.0180000000000003e-17*Y2_4*Y2_6 - 1.576e-15*Y2_4*Y2_5 + 2.0*Y2_6*jvals[0] + 1.0*Y2_5*jvals[1];
          double F2_5 = -6.0620000000000003e-15*Y2_2*Y2_5 + 8.0180000000000003e-17*Y2_4*Y2_6 - 1.576e-15*Y2_4*Y2_5 - 1.2e-10*Y2_3*Y2_5 - 1.0*Y2_5*jvals[1] - 1.0*Y2_5*jvals[2];
          double F2_6 = 0.0;
          // RHS for stage 2
          double rhs2_0 = F2_0 + (-1.0156171083877703 / dt) * K1_0;
          double rhs2_1 = F2_1 + (-1.0156171083877703 / dt) * K1_1;
          double rhs2_2 = F2_2 + (-1.0156171083877703 / dt) * K1_2;
          double rhs2_3 = F2_3 + (-1.0156171083877703 / dt) * K1_3;
          double rhs2_4 = F2_4 + (-1.0156171083877703 / dt) * K1_4;
          double rhs2_5 = F2_5 + (-1.0156171083877703 / dt) * K1_5;
          double rhs2_6 = F2_6 + (-1.0156171083877703 / dt) * K1_6;
          // Block 0: K2 forward sub [M, NO2, NO, O1D, O]
          double y2_0 = rhs2_0;
          double y2_1 = rhs2_1;
          double y2_2 = rhs2_2 - L_2_1 * y2_1;
          double y2_3 = rhs2_3 - L_3_0 * y2_0;
          double y2_4 = rhs2_4 - L_4_0 * y2_0 - L_4_1 * y2_1 - L_4_2 * y2_2 - L_4_3 * y2_3;
          // Block 1: K2 forward sub [O3]
          double y2_5 = rhs2_5 - L_5_2 * y2_2 - L_5_3 * y2_3 - L_5_4 * y2_4;
          // Block 2: K2 forward sub [O2]
          double y2_6 = rhs2_6;
          // Block 2: K2 backward sub [O2]
          double K2_6 = y2_6 / U_6_6;
          // Block 1: K2 backward sub [O3]
          double K2_5 = (y2_5 - U_5_6 * K2_6) / U_5_5;
          // Block 0: K2 backward sub [M, NO2, NO, O1D, O]
          double K2_4 = (y2_4 - U_4_5 * K2_5 - U_4_6 * K2_6) / U_4_4;
          double K2_3 = (y2_3 - U_3_5 * K2_5) / U_3_3;
          double K2_2 = (y2_2 - U_2_4 * K2_4 - U_2_5 * K2_5) / U_2_2;
          double K2_1 = (y2_1 - U_1_2 * K2_2 - U_1_4 * K2_4 - U_1_5 * K2_5) / U_1_1;
          double K2_0 = y2_0 / U_0_0;

          // --- Stage 3 ---
          // Intermediate state Y3
          double Y3_0 = S_0 + K1_0;
          double Y3_1 = S_1 + K1_1;
          double Y3_2 = S_2 + K1_2;
          double Y3_3 = S_3 + K1_3;
          double Y3_4 = S_4 + K1_4;
          double Y3_5 = S_5 + K1_5;
          double Y3_6 = S_6 + K1_6;
          // NewF=false: reuse F2 for stage 3
          // RHS for stage 3
          double rhs3_0 = F2_0 + (4.0759956452537702 / dt) * K1_0 + (9.20767942983308 / dt) * K2_0;
          double rhs3_1 = F2_1 + (4.0759956452537702 / dt) * K1_1 + (9.20767942983308 / dt) * K2_1;
          double rhs3_2 = F2_2 + (4.0759956452537702 / dt) * K1_2 + (9.20767942983308 / dt) * K2_2;
          double rhs3_3 = F2_3 + (4.0759956452537702 / dt) * K1_3 + (9.20767942983308 / dt) * K2_3;
          double rhs3_4 = F2_4 + (4.0759956452537702 / dt) * K1_4 + (9.20767942983308 / dt) * K2_4;
          double rhs3_5 = F2_5 + (4.0759956452537702 / dt) * K1_5 + (9.20767942983308 / dt) * K2_5;
          double rhs3_6 = F2_6 + (4.0759956452537702 / dt) * K1_6 + (9.20767942983308 / dt) * K2_6;
          // Block 0: K3 forward sub [M, NO2, NO, O1D, O]
          double y3_0 = rhs3_0;
          double y3_1 = rhs3_1;
          double y3_2 = rhs3_2 - L_2_1 * y3_1;
          double y3_3 = rhs3_3 - L_3_0 * y3_0;
          double y3_4 = rhs3_4 - L_4_0 * y3_0 - L_4_1 * y3_1 - L_4_2 * y3_2 - L_4_3 * y3_3;
          // Block 1: K3 forward sub [O3]
          double y3_5 = rhs3_5 - L_5_2 * y3_2 - L_5_3 * y3_3 - L_5_4 * y3_4;
          // Block 2: K3 forward sub [O2]
          double y3_6 = rhs3_6;
          // Block 2: K3 backward sub [O2]
          double K3_6 = y3_6 / U_6_6;
          // Block 1: K3 backward sub [O3]
          double K3_5 = (y3_5 - U_5_6 * K3_6) / U_5_5;
          // Block 0: K3 backward sub [M, NO2, NO, O1D, O]
          double K3_4 = (y3_4 - U_4_5 * K3_5 - U_4_6 * K3_6) / U_4_4;
          double K3_3 = (y3_3 - U_3_5 * K3_5) / U_3_3;
          double K3_2 = (y3_2 - U_2_4 * K3_4 - U_2_5 * K3_5) / U_2_2;
          double K3_1 = (y3_1 - U_1_2 * K3_2 - U_1_4 * K3_4 - U_1_5 * K3_5) / U_1_1;
          double K3_0 = y3_0 / U_0_0;

          // --- Solution update and error estimation ---
          double err_norm_sq = 0.0;
          {
              double Ynew_i = S_0 + K1_0 + 6.1697947043828245 * K2_0 + -0.42772256543218573 * K3_0;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(5)), Kokkos::fabs(Ynew_i));
              double sci = atol[0] + rtol[0] * ymax;
              double yerr_i = 0.5 * K1_0 + -2.9079558716805471 * K2_0 + 0.22354069897811571 * K3_0;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_1 + K1_1 + 6.1697947043828245 * K2_1 + -0.42772256543218573 * K3_1;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(4)), Kokkos::fabs(Ynew_i));
              double sci = atol[1] + rtol[1] * ymax;
              double yerr_i = 0.5 * K1_1 + -2.9079558716805471 * K2_1 + 0.22354069897811571 * K3_1;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_2 + K1_2 + 6.1697947043828245 * K2_2 + -0.42772256543218573 * K3_2;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(3)), Kokkos::fabs(Ynew_i));
              double sci = atol[2] + rtol[2] * ymax;
              double yerr_i = 0.5 * K1_2 + -2.9079558716805471 * K2_2 + 0.22354069897811571 * K3_2;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_3 + K1_3 + 6.1697947043828245 * K2_3 + -0.42772256543218573 * K3_3;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(1)), Kokkos::fabs(Ynew_i));
              double sci = atol[3] + rtol[3] * ymax;
              double yerr_i = 0.5 * K1_3 + -2.9079558716805471 * K2_3 + 0.22354069897811571 * K3_3;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_4 + K1_4 + 6.1697947043828245 * K2_4 + -0.42772256543218573 * K3_4;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(0)), Kokkos::fabs(Ynew_i));
              double sci = atol[4] + rtol[4] * ymax;
              double yerr_i = 0.5 * K1_4 + -2.9079558716805471 * K2_4 + 0.22354069897811571 * K3_4;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_5 + K1_5 + 6.1697947043828245 * K2_5 + -0.42772256543218573 * K3_5;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(2)), Kokkos::fabs(Ynew_i));
              double sci = atol[5] + rtol[5] * ymax;
              double yerr_i = 0.5 * K1_5 + -2.9079558716805471 * K2_5 + 0.22354069897811571 * K3_5;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_6 + K1_6 + 6.1697947043828245 * K2_6 + -0.42772256543218573 * K3_6;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(6)), Kokkos::fabs(Ynew_i));
              double sci = atol[6] + rtol[6] * ymax;
              double yerr_i = 0.5 * K1_6 + -2.9079558716805471 * K2_6 + 0.22354069897811571 * K3_6;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          double err_norm = Kokkos::sqrt(err_norm_sq / 7);
          err_norm = Kokkos::fmax(err_norm, 1.0e-10);

          // Step Size Control (order 3: exponent = 1/3 = 0.33333333333333331)
          double factor = safety / Kokkos::cbrt(err_norm);
          factor = Kokkos::fmax(min_shrink, Kokkos::fmin(factor, max_growth));

          if (err_norm <= 1.0) {
              state(5) += K1_0 + 6.1697947043828245 * K2_0 + -0.42772256543218573 * K3_0;
              state(4) += K1_1 + 6.1697947043828245 * K2_1 + -0.42772256543218573 * K3_1;
              state(3) += K1_2 + 6.1697947043828245 * K2_2 + -0.42772256543218573 * K3_2;
              state(1) += K1_3 + 6.1697947043828245 * K2_3 + -0.42772256543218573 * K3_3;
              state(0) += K1_4 + 6.1697947043828245 * K2_4 + -0.42772256543218573 * K3_4;
              state(2) += K1_5 + 6.1697947043828245 * K2_5 + -0.42772256543218573 * K3_5;
              state(6) += K1_6 + 6.1697947043828245 * K2_6 + -0.42772256543218573 * K3_6;
              t += dt;
              dt *= factor;
          } else {
              dt *= factor;
          }
          } // end while (t < dt_total)
      }

      template <class StateView>
      KOKKOS_INLINE_FUNCTION void integrate_with_reduction(
          double dt_total, StateView& state, const double* jvals, double importance_threshold) const
      {
          const int NUM_SPECIES = 7;
          // ROS-3 coefficients (3-stage, order 3)
          const double g = 0.435866521508459;
          const double safety = 0.9;
          const double max_growth = 6.0;
          const double min_shrink = 0.2;

          bool active[NUM_SPECIES];
          double t = 0.0;
          double dt = Kokkos::fmin(dt_total, 1.0);  // conservative initial step

          // Initialize all species as active
          active[0] = true;
          active[1] = true;
          active[2] = true;
          active[3] = true;
          active[4] = true;
          active[5] = true;
          active[6] = true;

          while (t < dt_total) {
          dt = Kokkos::min(dt, dt_total - t);
          const double inv_g_dt = 1.0 / (g * dt);

          // 0. Hoist state values into scalar registers
          // NOTE: State access uses permuted species ordering
          const double S_0 = state(5);
          const double S_1 = state(4);
          const double S_2 = state(3);
          const double S_3 = state(1);
          const double S_4 = state(0);
          const double S_5 = state(2);
          const double S_6 = state(6);

          // 1. Stage 1 Rates (F1)
          double F1_0 = 0.0;
          double F1_1 = 6.0620000000000003e-15*S_2*S_5 - 1.0690000000000001e-11*S_1*S_4 - 1.0*S_1*jvals[3];
          double F1_2 = -6.0620000000000003e-15*S_2*S_5 + 1.0690000000000001e-11*S_1*S_4 + 1.0*S_1*jvals[3];
          double F1_3 = -7.1100000000000005e-11*S_0*S_3 - 1.2e-10*S_3*S_5 + 1.0*S_5*jvals[2];
          double F1_4 = 7.1100000000000005e-11*S_0*S_3 - 1.0690000000000001e-11*S_1*S_4 + 1.0*S_1*jvals[3] - 8.0180000000000003e-17*S_4*S_6 - 1.576e-15*S_4*S_5 + 2.0*S_6*jvals[0] + 1.0*S_5*jvals[1];
          double F1_5 = -6.0620000000000003e-15*S_2*S_5 + 8.0180000000000003e-17*S_4*S_6 - 1.576e-15*S_4*S_5 - 1.2e-10*S_3*S_5 - 1.0*S_5*jvals[1] - 1.0*S_5*jvals[2];
          double F1_6 = 0.0;

          // 2. Evaluate importance and update active set
          active[0] = (Kokkos::fabs(F1_0) / (atol[0] + rtol[0] * Kokkos::fabs(state(5))) >= importance_threshold);
          active[1] = (Kokkos::fabs(F1_1) / (atol[1] + rtol[1] * Kokkos::fabs(state(4))) >= importance_threshold);
          active[2] = (Kokkos::fabs(F1_2) / (atol[2] + rtol[2] * Kokkos::fabs(state(3))) >= importance_threshold);
          active[3] = (Kokkos::fabs(F1_3) / (atol[3] + rtol[3] * Kokkos::fabs(state(1))) >= importance_threshold);
          active[4] = (Kokkos::fabs(F1_4) / (atol[4] + rtol[4] * Kokkos::fabs(state(0))) >= importance_threshold);
          active[5] = (Kokkos::fabs(F1_5) / (atol[5] + rtol[5] * Kokkos::fabs(state(2))) >= importance_threshold);
          active[6] = (Kokkos::fabs(F1_6) / (atol[6] + rtol[6] * Kokkos::fabs(state(6))) >= importance_threshold);

          // 3. Analytical Jacobian & Iteration Matrix W (identity for frozen species)
          double J_1_1 = -1.0690000000000001e-11*S_4 - 1.0*jvals[3];
          double J_1_2 = 6.0620000000000003e-15*S_5;
          double J_1_4 = -1.0690000000000001e-11*S_1;
          double J_1_5 = 6.0620000000000003e-15*S_2;
          double J_2_1 = 1.0690000000000001e-11*S_4 + 1.0*jvals[3];
          double J_2_2 = -6.0620000000000003e-15*S_5;
          double J_2_4 = 1.0690000000000001e-11*S_1;
          double J_2_5 = -6.0620000000000003e-15*S_2;
          double J_3_0 = -7.1100000000000005e-11*S_3;
          double J_3_3 = -7.1100000000000005e-11*S_0 - 1.2e-10*S_5;
          double J_3_5 = -1.2e-10*S_3 + 1.0*jvals[2];
          double J_4_0 = 7.1100000000000005e-11*S_3;
          double J_4_1 = -1.0690000000000001e-11*S_4 + 1.0*jvals[3];
          double J_4_3 = 7.1100000000000005e-11*S_0;
          double J_4_4 = -1.0690000000000001e-11*S_1 - 8.0180000000000003e-17*S_6 - 1.576e-15*S_5;
          double J_4_5 = -1.576e-15*S_4 + 1.0*jvals[1];
          double J_4_6 = -8.0180000000000003e-17*S_4 + 2.0*jvals[0];
          double J_5_2 = -6.0620000000000003e-15*S_5;
          double J_5_3 = -1.2e-10*S_5;
          double J_5_4 = 8.0180000000000003e-17*S_6 - 1.576e-15*S_5;
          double J_5_5 = -6.0620000000000003e-15*S_2 - 1.576e-15*S_4 - 1.2e-10*S_3 - 1.0*jvals[1] - 1.0*jvals[2];
          double J_5_6 = 8.0180000000000003e-17*S_4;
          double W_0_0 = active[0] ? inv_g_dt : 1.0;
          double W_1_1 = active[1] ? (inv_g_dt - J_1_1) : 1.0;
          double W_1_2 = (active[1] && active[2]) ? (-J_1_2) : 0.0;
          double W_1_4 = (active[1] && active[4]) ? (-J_1_4) : 0.0;
          double W_1_5 = (active[1] && active[5]) ? (-J_1_5) : 0.0;
          double W_2_1 = (active[2] && active[1]) ? (-J_2_1) : 0.0;
          double W_2_2 = active[2] ? (inv_g_dt - J_2_2) : 1.0;
          double W_2_4 = (active[2] && active[4]) ? (-J_2_4) : 0.0;
          double W_2_5 = (active[2] && active[5]) ? (-J_2_5) : 0.0;
          double W_3_0 = (active[3] && active[0]) ? (-J_3_0) : 0.0;
          double W_3_3 = active[3] ? (inv_g_dt - J_3_3) : 1.0;
          double W_3_5 = (active[3] && active[5]) ? (-J_3_5) : 0.0;
          double W_4_0 = (active[4] && active[0]) ? (-J_4_0) : 0.0;
          double W_4_1 = (active[4] && active[1]) ? (-J_4_1) : 0.0;
          double W_4_3 = (active[4] && active[3]) ? (-J_4_3) : 0.0;
          double W_4_4 = active[4] ? (inv_g_dt - J_4_4) : 1.0;
          double W_4_5 = (active[4] && active[5]) ? (-J_4_5) : 0.0;
          double W_4_6 = (active[4] && active[6]) ? (-J_4_6) : 0.0;
          double W_5_2 = (active[5] && active[2]) ? (-J_5_2) : 0.0;
          double W_5_3 = (active[5] && active[3]) ? (-J_5_3) : 0.0;
          double W_5_4 = (active[5] && active[4]) ? (-J_5_4) : 0.0;
          double W_5_5 = active[5] ? (inv_g_dt - J_5_5) : 1.0;
          double W_5_6 = (active[5] && active[6]) ? (-J_5_6) : 0.0;
          double W_6_6 = active[6] ? inv_g_dt : 1.0;

          // 4. Symbolic LU Factorization (conditional skip for frozen species)
          double U_0_0 = W_0_0;
          double L_3_0 = (W_3_0) / U_0_0;
          double L_4_0 = (W_4_0) / U_0_0;
          double U_1_1 = W_1_1;
          double U_1_2 = W_1_2;
          double U_1_4 = W_1_4;
          double U_1_5 = W_1_5;
          double L_2_1 = (W_2_1) / U_1_1;
          double L_4_1 = (W_4_1) / U_1_1;
          double U_2_2 = W_2_2 - L_2_1 * U_1_2;
          double U_2_4 = W_2_4 - L_2_1 * U_1_4;
          double U_2_5 = W_2_5 - L_2_1 * U_1_5;
          double L_4_2 = (0.0 - L_4_1 * U_1_2) / U_2_2;
          double L_5_2 = (W_5_2) / U_2_2;
          double U_3_3 = W_3_3;
          double U_3_5 = W_3_5;
          double L_4_3 = (W_4_3) / U_3_3;
          double L_5_3 = (W_5_3) / U_3_3;
          double U_4_4 = W_4_4 - L_4_1 * U_1_4 - L_4_2 * U_2_4;
          double U_4_5 = W_4_5 - L_4_1 * U_1_5 - L_4_2 * U_2_5 - L_4_3 * U_3_5;
          double U_4_6 = W_4_6;
          double L_5_4 = (W_5_4 - L_5_2 * U_2_4) / U_4_4;
          double U_5_5 = W_5_5 - L_5_2 * U_2_5 - L_5_3 * U_3_5 - L_5_4 * U_4_5;
          double U_5_6 = W_5_6 - L_5_4 * U_4_6;
          double U_6_6 = W_6_6;

          // --- Stage 1 ---
          // F1 already computed above (used for importance evaluation)
          // Block 0: K1 forward sub [M, NO2, NO, O1D, O]
          double y1_0 = active[0] ? (F1_0) : 0.0;
          double y1_1 = active[1] ? (F1_1) : 0.0;
          double y1_2 = active[2] ? (F1_2 - L_2_1 * y1_1) : 0.0;
          double y1_3 = active[3] ? (F1_3 - L_3_0 * y1_0) : 0.0;
          double y1_4 = active[4] ? (F1_4 - L_4_0 * y1_0 - L_4_1 * y1_1 - L_4_2 * y1_2 - L_4_3 * y1_3) : 0.0;
          // Block 1: K1 forward sub [O3]
          double y1_5 = active[5] ? (F1_5 - L_5_2 * y1_2 - L_5_3 * y1_3 - L_5_4 * y1_4) : 0.0;
          // Block 2: K1 forward sub [O2]
          double y1_6 = active[6] ? (F1_6) : 0.0;

          // Block 2: K1 backward sub [O2]
          double K1_6 = active[6] ? (y1_6 / U_6_6) : 0.0;
          // Block 1: K1 backward sub [O3]
          double K1_5 = active[5] ? ((y1_5 - U_5_6 * K1_6) / U_5_5) : 0.0;
          // Block 0: K1 backward sub [M, NO2, NO, O1D, O]
          double K1_4 = active[4] ? ((y1_4 - U_4_5 * K1_5 - U_4_6 * K1_6) / U_4_4) : 0.0;
          double K1_3 = active[3] ? ((y1_3 - U_3_5 * K1_5) / U_3_3) : 0.0;
          double K1_2 = active[2] ? ((y1_2 - U_2_4 * K1_4 - U_2_5 * K1_5) / U_2_2) : 0.0;
          double K1_1 = active[1] ? ((y1_1 - U_1_2 * K1_2 - U_1_4 * K1_4 - U_1_5 * K1_5) / U_1_1) : 0.0;
          double K1_0 = active[0] ? (y1_0 / U_0_0) : 0.0;


          // --- Stage 2 ---
          // Intermediate state Y2
          double Y2_0 = S_0 + K1_0;
          double Y2_1 = S_1 + K1_1;
          double Y2_2 = S_2 + K1_2;
          double Y2_3 = S_3 + K1_3;
          double Y2_4 = S_4 + K1_4;
          double Y2_5 = S_5 + K1_5;
          double Y2_6 = S_6 + K1_6;
          // Rate evaluation F2 at Y2
          double F2_0 = 0.0;
          double F2_1 = 6.0620000000000003e-15*Y2_2*Y2_5 - 1.0690000000000001e-11*Y2_1*Y2_4 - 1.0*Y2_1*jvals[3];
          double F2_2 = -6.0620000000000003e-15*Y2_2*Y2_5 + 1.0690000000000001e-11*Y2_1*Y2_4 + 1.0*Y2_1*jvals[3];
          double F2_3 = -7.1100000000000005e-11*Y2_0*Y2_3 - 1.2e-10*Y2_3*Y2_5 + 1.0*Y2_5*jvals[2];
          double F2_4 = 7.1100000000000005e-11*Y2_0*Y2_3 - 1.0690000000000001e-11*Y2_1*Y2_4 + 1.0*Y2_1*jvals[3] - 8.0180000000000003e-17*Y2_4*Y2_6 - 1.576e-15*Y2_4*Y2_5 + 2.0*Y2_6*jvals[0] + 1.0*Y2_5*jvals[1];
          double F2_5 = -6.0620000000000003e-15*Y2_2*Y2_5 + 8.0180000000000003e-17*Y2_4*Y2_6 - 1.576e-15*Y2_4*Y2_5 - 1.2e-10*Y2_3*Y2_5 - 1.0*Y2_5*jvals[1] - 1.0*Y2_5*jvals[2];
          double F2_6 = 0.0;
          // RHS for stage 2
          double rhs2_0 = F2_0 + (-1.0156171083877703 / dt) * K1_0;
          double rhs2_1 = F2_1 + (-1.0156171083877703 / dt) * K1_1;
          double rhs2_2 = F2_2 + (-1.0156171083877703 / dt) * K1_2;
          double rhs2_3 = F2_3 + (-1.0156171083877703 / dt) * K1_3;
          double rhs2_4 = F2_4 + (-1.0156171083877703 / dt) * K1_4;
          double rhs2_5 = F2_5 + (-1.0156171083877703 / dt) * K1_5;
          double rhs2_6 = F2_6 + (-1.0156171083877703 / dt) * K1_6;
          // Block 0: K2 forward sub [M, NO2, NO, O1D, O]
          double y2_0 = active[0] ? (rhs2_0) : 0.0;
          double y2_1 = active[1] ? (rhs2_1) : 0.0;
          double y2_2 = active[2] ? (rhs2_2 - L_2_1 * y2_1) : 0.0;
          double y2_3 = active[3] ? (rhs2_3 - L_3_0 * y2_0) : 0.0;
          double y2_4 = active[4] ? (rhs2_4 - L_4_0 * y2_0 - L_4_1 * y2_1 - L_4_2 * y2_2 - L_4_3 * y2_3) : 0.0;
          // Block 1: K2 forward sub [O3]
          double y2_5 = active[5] ? (rhs2_5 - L_5_2 * y2_2 - L_5_3 * y2_3 - L_5_4 * y2_4) : 0.0;
          // Block 2: K2 forward sub [O2]
          double y2_6 = active[6] ? (rhs2_6) : 0.0;

          // Block 2: K2 backward sub [O2]
          double K2_6 = active[6] ? (y2_6 / U_6_6) : 0.0;
          // Block 1: K2 backward sub [O3]
          double K2_5 = active[5] ? ((y2_5 - U_5_6 * K2_6) / U_5_5) : 0.0;
          // Block 0: K2 backward sub [M, NO2, NO, O1D, O]
          double K2_4 = active[4] ? ((y2_4 - U_4_5 * K2_5 - U_4_6 * K2_6) / U_4_4) : 0.0;
          double K2_3 = active[3] ? ((y2_3 - U_3_5 * K2_5) / U_3_3) : 0.0;
          double K2_2 = active[2] ? ((y2_2 - U_2_4 * K2_4 - U_2_5 * K2_5) / U_2_2) : 0.0;
          double K2_1 = active[1] ? ((y2_1 - U_1_2 * K2_2 - U_1_4 * K2_4 - U_1_5 * K2_5) / U_1_1) : 0.0;
          double K2_0 = active[0] ? (y2_0 / U_0_0) : 0.0;


          // --- Stage 3 ---
          // Intermediate state Y3
          double Y3_0 = S_0 + K1_0;
          double Y3_1 = S_1 + K1_1;
          double Y3_2 = S_2 + K1_2;
          double Y3_3 = S_3 + K1_3;
          double Y3_4 = S_4 + K1_4;
          double Y3_5 = S_5 + K1_5;
          double Y3_6 = S_6 + K1_6;
          // NewF=false: reuse F2 for stage 3
          // RHS for stage 3
          double rhs3_0 = F2_0 + (4.0759956452537702 / dt) * K1_0 + (9.20767942983308 / dt) * K2_0;
          double rhs3_1 = F2_1 + (4.0759956452537702 / dt) * K1_1 + (9.20767942983308 / dt) * K2_1;
          double rhs3_2 = F2_2 + (4.0759956452537702 / dt) * K1_2 + (9.20767942983308 / dt) * K2_2;
          double rhs3_3 = F2_3 + (4.0759956452537702 / dt) * K1_3 + (9.20767942983308 / dt) * K2_3;
          double rhs3_4 = F2_4 + (4.0759956452537702 / dt) * K1_4 + (9.20767942983308 / dt) * K2_4;
          double rhs3_5 = F2_5 + (4.0759956452537702 / dt) * K1_5 + (9.20767942983308 / dt) * K2_5;
          double rhs3_6 = F2_6 + (4.0759956452537702 / dt) * K1_6 + (9.20767942983308 / dt) * K2_6;
          // Block 0: K3 forward sub [M, NO2, NO, O1D, O]
          double y3_0 = active[0] ? (rhs3_0) : 0.0;
          double y3_1 = active[1] ? (rhs3_1) : 0.0;
          double y3_2 = active[2] ? (rhs3_2 - L_2_1 * y3_1) : 0.0;
          double y3_3 = active[3] ? (rhs3_3 - L_3_0 * y3_0) : 0.0;
          double y3_4 = active[4] ? (rhs3_4 - L_4_0 * y3_0 - L_4_1 * y3_1 - L_4_2 * y3_2 - L_4_3 * y3_3) : 0.0;
          // Block 1: K3 forward sub [O3]
          double y3_5 = active[5] ? (rhs3_5 - L_5_2 * y3_2 - L_5_3 * y3_3 - L_5_4 * y3_4) : 0.0;
          // Block 2: K3 forward sub [O2]
          double y3_6 = active[6] ? (rhs3_6) : 0.0;

          // Block 2: K3 backward sub [O2]
          double K3_6 = active[6] ? (y3_6 / U_6_6) : 0.0;
          // Block 1: K3 backward sub [O3]
          double K3_5 = active[5] ? ((y3_5 - U_5_6 * K3_6) / U_5_5) : 0.0;
          // Block 0: K3 backward sub [M, NO2, NO, O1D, O]
          double K3_4 = active[4] ? ((y3_4 - U_4_5 * K3_5 - U_4_6 * K3_6) / U_4_4) : 0.0;
          double K3_3 = active[3] ? ((y3_3 - U_3_5 * K3_5) / U_3_3) : 0.0;
          double K3_2 = active[2] ? ((y3_2 - U_2_4 * K3_4 - U_2_5 * K3_5) / U_2_2) : 0.0;
          double K3_1 = active[1] ? ((y3_1 - U_1_2 * K3_2 - U_1_4 * K3_4 - U_1_5 * K3_5) / U_1_1) : 0.0;
          double K3_0 = active[0] ? (y3_0 / U_0_0) : 0.0;


          // --- Solution update and error estimation ---
          double err_norm_sq = 0.0;
          {
              double Ynew_i = S_0 + K1_0 + 6.1697947043828245 * K2_0 + -0.42772256543218573 * K3_0;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(5)), Kokkos::fabs(Ynew_i));
              double sci = atol[0] + rtol[0] * ymax;
              double yerr_i = 0.5 * K1_0 + -2.9079558716805471 * K2_0 + 0.22354069897811571 * K3_0;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_1 + K1_1 + 6.1697947043828245 * K2_1 + -0.42772256543218573 * K3_1;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(4)), Kokkos::fabs(Ynew_i));
              double sci = atol[1] + rtol[1] * ymax;
              double yerr_i = 0.5 * K1_1 + -2.9079558716805471 * K2_1 + 0.22354069897811571 * K3_1;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_2 + K1_2 + 6.1697947043828245 * K2_2 + -0.42772256543218573 * K3_2;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(3)), Kokkos::fabs(Ynew_i));
              double sci = atol[2] + rtol[2] * ymax;
              double yerr_i = 0.5 * K1_2 + -2.9079558716805471 * K2_2 + 0.22354069897811571 * K3_2;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_3 + K1_3 + 6.1697947043828245 * K2_3 + -0.42772256543218573 * K3_3;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(1)), Kokkos::fabs(Ynew_i));
              double sci = atol[3] + rtol[3] * ymax;
              double yerr_i = 0.5 * K1_3 + -2.9079558716805471 * K2_3 + 0.22354069897811571 * K3_3;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_4 + K1_4 + 6.1697947043828245 * K2_4 + -0.42772256543218573 * K3_4;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(0)), Kokkos::fabs(Ynew_i));
              double sci = atol[4] + rtol[4] * ymax;
              double yerr_i = 0.5 * K1_4 + -2.9079558716805471 * K2_4 + 0.22354069897811571 * K3_4;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_5 + K1_5 + 6.1697947043828245 * K2_5 + -0.42772256543218573 * K3_5;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(2)), Kokkos::fabs(Ynew_i));
              double sci = atol[5] + rtol[5] * ymax;
              double yerr_i = 0.5 * K1_5 + -2.9079558716805471 * K2_5 + 0.22354069897811571 * K3_5;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_6 + K1_6 + 6.1697947043828245 * K2_6 + -0.42772256543218573 * K3_6;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(6)), Kokkos::fabs(Ynew_i));
              double sci = atol[6] + rtol[6] * ymax;
              double yerr_i = 0.5 * K1_6 + -2.9079558716805471 * K2_6 + 0.22354069897811571 * K3_6;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          double err_norm = Kokkos::sqrt(err_norm_sq / 7);
          err_norm = Kokkos::fmax(err_norm, 1.0e-10);

          // Step Size Control (order 3: exponent = 1/3 = 0.33333333333333331)
          double factor = safety / Kokkos::cbrt(err_norm);
          factor = Kokkos::fmax(min_shrink, Kokkos::fmin(factor, max_growth));

          if (err_norm <= 1.0) {
              if (active[0]) state(5) += K1_0 + 6.1697947043828245 * K2_0 + -0.42772256543218573 * K3_0;
              if (active[1]) state(4) += K1_1 + 6.1697947043828245 * K2_1 + -0.42772256543218573 * K3_1;
              if (active[2]) state(3) += K1_2 + 6.1697947043828245 * K2_2 + -0.42772256543218573 * K3_2;
              if (active[3]) state(1) += K1_3 + 6.1697947043828245 * K2_3 + -0.42772256543218573 * K3_3;
              if (active[4]) state(0) += K1_4 + 6.1697947043828245 * K2_4 + -0.42772256543218573 * K3_4;
              if (active[5]) state(2) += K1_5 + 6.1697947043828245 * K2_5 + -0.42772256543218573 * K3_5;
              if (active[6]) state(6) += K1_6 + 6.1697947043828245 * K2_6 + -0.42772256543218573 * K3_6;
              t += dt;
              dt *= factor;
          } else {
              dt *= factor;
          }
          } // end while (t < dt_total)
      }
  };
}
