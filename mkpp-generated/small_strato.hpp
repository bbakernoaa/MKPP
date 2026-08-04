#pragma once
#include <Kokkos_Core.hpp>
// Generated solver for small_strato
// SZA Workload Sorted: true
// Hysteresis/Spline Continuous Transition: true
namespace mkpp {
  // Pure Kokkos abstractions (no raw pragmas allowed)
  // Bidirectional Host Interface (Zero-Copy)
  using concentrations_view_t = Kokkos::View<double****, Kokkos::LayoutLeft, Kokkos::MemoryUnmanaged>;
  template<typename DeviceType>
  struct SolverKernels {
      template <class StateView, class RateView>
      KOKKOS_INLINE_FUNCTION void compute_rates(const StateView& state, RateView& F_block) const {
          F_block(0) = 7.1100000000000005e-11*state(5)*state(1) - 1.0690000000000001e-11*state(4)*state(0) + 0.01289*state(4) - 8.0180000000000003e-17*state(0)*state(6) - 1.576e-15*state(0)*state(2) + 5.2860000000000002e-10*state(6) + 0.00061200000000000002*state(2);
          F_block(1) = -7.1100000000000005e-11*state(5)*state(1) - 1.2e-10*state(1)*state(2) + 0.00107*state(2);
          F_block(2) = -6.0620000000000003e-15*state(3)*state(2) + 8.0180000000000003e-17*state(0)*state(6) - 1.576e-15*state(0)*state(2) - 1.2e-10*state(1)*state(2) - 0.0016819999999999999*state(2);
          F_block(3) = -6.0620000000000003e-15*state(3)*state(2) + 1.0690000000000001e-11*state(4)*state(0) + 0.01289*state(4);
          F_block(4) = 6.0620000000000003e-15*state(3)*state(2) - 1.0690000000000001e-11*state(4)*state(0) - 0.01289*state(4);
          F_block(5) = 0.0;
          F_block(6) = 0.0;
      }

      template <class StateView, class JacView>
      KOKKOS_INLINE_FUNCTION void compute_jacobian(const StateView& state, JacView& J_block) const {
          J_block(0, 0) = -1.0690000000000001e-11*state(4) - 8.0180000000000003e-17*state(6) - 1.576e-15*state(2);
          J_block(0, 1) = 7.1100000000000005e-11*state(5);
          J_block(0, 2) = 0.00061200000000000002 - 1.576e-15*state(0);
          J_block(0, 4) = 0.01289 - 1.0690000000000001e-11*state(0);
          J_block(0, 5) = 7.1100000000000005e-11*state(1);
          J_block(0, 6) = 5.2860000000000002e-10 - 8.0180000000000003e-17*state(0);
          J_block(1, 1) = -7.1100000000000005e-11*state(5) - 1.2e-10*state(2);
          J_block(1, 2) = 0.00107 - 1.2e-10*state(1);
          J_block(1, 5) = -7.1100000000000005e-11*state(1);
          J_block(2, 0) = 8.0180000000000003e-17*state(6) - 1.576e-15*state(2);
          J_block(2, 1) = -1.2e-10*state(2);
          J_block(2, 2) = -6.0620000000000003e-15*state(3) - 1.576e-15*state(0) - 1.2e-10*state(1) - 0.0016819999999999999;
          J_block(2, 3) = -6.0620000000000003e-15*state(2);
          J_block(2, 6) = 8.0180000000000003e-17*state(0);
          J_block(3, 0) = 1.0690000000000001e-11*state(4);
          J_block(3, 2) = -6.0620000000000003e-15*state(3);
          J_block(3, 3) = -6.0620000000000003e-15*state(2);
          J_block(3, 4) = 1.0690000000000001e-11*state(0) + 0.01289;
          J_block(4, 0) = -1.0690000000000001e-11*state(4);
          J_block(4, 2) = 6.0620000000000003e-15*state(3);
          J_block(4, 3) = 6.0620000000000003e-15*state(2);
          J_block(4, 4) = -1.0690000000000001e-11*state(0) - 0.01289;
      }

      template <class StateView, class JacView>
      KOKKOS_INLINE_FUNCTION void compute_adjoint(const StateView& state, JacView& J_adj_block) const {
      }

      template <class StateView, class DeltaView, class RateView>
      KOKKOS_INLINE_FUNCTION void compute_tlm(const StateView& state, const DeltaView& delta_C, RateView& dF_block) const {
          dF_block(0) = 0.0;
          dF_block(0) += (-1.0690000000000001e-11*state(4) - 8.0180000000000003e-17*state(6) - 1.576e-15*state(2)) * delta_C(0);
          dF_block(0) += (7.1100000000000005e-11*state(5)) * delta_C(1);
          dF_block(0) += (0.00061200000000000002 - 1.576e-15*state(0)) * delta_C(2);
          dF_block(0) += (0.01289 - 1.0690000000000001e-11*state(0)) * delta_C(4);
          dF_block(0) += (7.1100000000000005e-11*state(1)) * delta_C(5);
          dF_block(0) += (5.2860000000000002e-10 - 8.0180000000000003e-17*state(0)) * delta_C(6);
          dF_block(1) = 0.0;
          dF_block(1) += (-7.1100000000000005e-11*state(5) - 1.2e-10*state(2)) * delta_C(1);
          dF_block(1) += (0.00107 - 1.2e-10*state(1)) * delta_C(2);
          dF_block(1) += (-7.1100000000000005e-11*state(1)) * delta_C(5);
          dF_block(2) = 0.0;
          dF_block(2) += (8.0180000000000003e-17*state(6) - 1.576e-15*state(2)) * delta_C(0);
          dF_block(2) += (-1.2e-10*state(2)) * delta_C(1);
          dF_block(2) += (-6.0620000000000003e-15*state(3) - 1.576e-15*state(0) - 1.2e-10*state(1) - 0.0016819999999999999) * delta_C(2);
          dF_block(2) += (-6.0620000000000003e-15*state(2)) * delta_C(3);
          dF_block(2) += (8.0180000000000003e-17*state(0)) * delta_C(6);
          dF_block(3) = 0.0;
          dF_block(3) += (1.0690000000000001e-11*state(4)) * delta_C(0);
          dF_block(3) += (-6.0620000000000003e-15*state(3)) * delta_C(2);
          dF_block(3) += (-6.0620000000000003e-15*state(2)) * delta_C(3);
          dF_block(3) += (1.0690000000000001e-11*state(0) + 0.01289) * delta_C(4);
          dF_block(4) = 0.0;
          dF_block(4) += (-1.0690000000000001e-11*state(4)) * delta_C(0);
          dF_block(4) += (6.0620000000000003e-15*state(3)) * delta_C(2);
          dF_block(4) += (6.0620000000000003e-15*state(2)) * delta_C(3);
          dF_block(4) += (-1.0690000000000001e-11*state(0) - 0.01289) * delta_C(4);
          dF_block(5) = 0.0;
          dF_block(6) = 0.0;
      }

      template <class StateView, class MassView>
      KOKKOS_INLINE_FUNCTION void project_mass_conservation(StateView& C_projected, const StateView& C, const MassView& m_0) const {
          // C_projected = C - E^T (E E^T)^-1 (E C - m_0)
      }

      static constexpr int NUM_SPECIES = 7;
      static constexpr double atol[NUM_SPECIES] = { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 };
      static constexpr double rtol[NUM_SPECIES] = { 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001 };

      template <class StateView>
      KOKKOS_INLINE_FUNCTION void integrate(double dt_total, StateView& state) const {
          const int NUM_SPECIES = 7;
          const double g = 1.70710678118654752440;
          const double ros_A0 = 1.0 / g;
          const double ros_C0 = -2.0 / g;
          const double ros_M0 = 3.0 / (2.0 * g);
          const double ros_M1 = 1.0 / (2.0 * g);
          const double safety = 0.9;
          const double max_growth = 5.0;
          const double min_shrink = 0.2;
          double t = 0.0;
          double dt = dt_total;

          while (t < dt_total) {
          dt = Kokkos::min(dt, dt_total - t);
          const double inv_g_dt = 1.0 / (g * dt);

          // 0. Hoist state values into scalar registers
          const double S_0 = state(0);
          const double S_1 = state(1);
          const double S_2 = state(2);
          const double S_3 = state(3);
          const double S_4 = state(4);
          const double S_5 = state(5);
          const double S_6 = state(6);

          // 1. Stage 1 Rates (F1)
          double F1_0 = 7.1100000000000005e-11*S_5*S_1 - 1.0690000000000001e-11*S_4*S_0 + 0.01289*S_4 - 8.0180000000000003e-17*S_0*S_6 - 1.576e-15*S_0*S_2 + 5.2860000000000002e-10*S_6 + 0.00061200000000000002*S_2;
          double F1_1 = -7.1100000000000005e-11*S_5*S_1 - 1.2e-10*S_1*S_2 + 0.00107*S_2;
          double F1_2 = -6.0620000000000003e-15*S_3*S_2 + 8.0180000000000003e-17*S_0*S_6 - 1.576e-15*S_0*S_2 - 1.2e-10*S_1*S_2 - 0.0016819999999999999*S_2;
          double F1_3 = -6.0620000000000003e-15*S_3*S_2 + 1.0690000000000001e-11*S_4*S_0 + 0.01289*S_4;
          double F1_4 = 6.0620000000000003e-15*S_3*S_2 - 1.0690000000000001e-11*S_4*S_0 - 0.01289*S_4;
          double F1_5 = 0.0;
          double F1_6 = 0.0;

          // 2. Analytical Jacobian & Iteration Matrix W = inv_g_dt*I - J
          double J_0_0 = -1.0690000000000001e-11*S_4 - 8.0180000000000003e-17*S_6 - 1.576e-15*S_2;
          double J_0_1 = 7.1100000000000005e-11*S_5;
          double J_0_2 = 0.00061200000000000002 - 1.576e-15*S_0;
          double J_0_4 = 0.01289 - 1.0690000000000001e-11*S_0;
          double J_0_5 = 7.1100000000000005e-11*S_1;
          double J_0_6 = 5.2860000000000002e-10 - 8.0180000000000003e-17*S_0;
          double J_1_1 = -7.1100000000000005e-11*S_5 - 1.2e-10*S_2;
          double J_1_2 = 0.00107 - 1.2e-10*S_1;
          double J_1_5 = -7.1100000000000005e-11*S_1;
          double J_2_0 = 8.0180000000000003e-17*S_6 - 1.576e-15*S_2;
          double J_2_1 = -1.2e-10*S_2;
          double J_2_2 = -6.0620000000000003e-15*S_3 - 1.576e-15*S_0 - 1.2e-10*S_1 - 0.0016819999999999999;
          double J_2_3 = -6.0620000000000003e-15*S_2;
          double J_2_6 = 8.0180000000000003e-17*S_0;
          double J_3_0 = 1.0690000000000001e-11*S_4;
          double J_3_2 = -6.0620000000000003e-15*S_3;
          double J_3_3 = -6.0620000000000003e-15*S_2;
          double J_3_4 = 1.0690000000000001e-11*S_0 + 0.01289;
          double J_4_0 = -1.0690000000000001e-11*S_4;
          double J_4_2 = 6.0620000000000003e-15*S_3;
          double J_4_3 = 6.0620000000000003e-15*S_2;
          double J_4_4 = -1.0690000000000001e-11*S_0 - 0.01289;
          double W_0_0 = inv_g_dt - J_0_0;
          double W_0_1 = -J_0_1;
          double W_0_2 = -J_0_2;
          double W_0_4 = -J_0_4;
          double W_0_5 = -J_0_5;
          double W_0_6 = -J_0_6;
          double W_1_1 = inv_g_dt - J_1_1;
          double W_1_2 = -J_1_2;
          double W_1_5 = -J_1_5;
          double W_2_0 = -J_2_0;
          double W_2_1 = -J_2_1;
          double W_2_2 = inv_g_dt - J_2_2;
          double W_2_3 = -J_2_3;
          double W_2_6 = -J_2_6;
          double W_3_0 = -J_3_0;
          double W_3_2 = -J_3_2;
          double W_3_3 = inv_g_dt - J_3_3;
          double W_3_4 = -J_3_4;
          double W_4_0 = -J_4_0;
          double W_4_2 = -J_4_2;
          double W_4_3 = -J_4_3;
          double W_4_4 = inv_g_dt - J_4_4;
          double W_5_5 = inv_g_dt;
          double W_6_6 = inv_g_dt;

          // 3. Symbolic Doolittle Sparse LU Factorization
          double U_0_0 = W_0_0;
          double U_0_1 = W_0_1;
          double U_0_2 = W_0_2;
          double U_0_4 = W_0_4;
          double U_0_5 = W_0_5;
          double U_0_6 = W_0_6;
          double L_2_0 = (W_2_0) / U_0_0;
          double L_3_0 = (W_3_0) / U_0_0;
          double L_4_0 = (W_4_0) / U_0_0;
          double U_1_1 = W_1_1;
          double U_1_2 = W_1_2;
          double U_1_5 = W_1_5;
          double L_2_1 = (W_2_1 - L_2_0 * U_0_1) / U_1_1;
          double L_3_1 = (0.0 - L_3_0 * U_0_1) / U_1_1;
          double L_4_1 = (0.0 - L_4_0 * U_0_1) / U_1_1;
          double U_2_2 = W_2_2 - L_2_0 * U_0_2 - L_2_1 * U_1_2;
          double U_2_3 = W_2_3;
          double U_2_4 = 0.0 - L_2_0 * U_0_4;
          double U_2_5 = 0.0 - L_2_0 * U_0_5 - L_2_1 * U_1_5;
          double U_2_6 = W_2_6 - L_2_0 * U_0_6;
          double L_3_2 = (W_3_2 - L_3_0 * U_0_2 - L_3_1 * U_1_2) / U_2_2;
          double L_4_2 = (W_4_2 - L_4_0 * U_0_2 - L_4_1 * U_1_2) / U_2_2;
          double U_3_3 = W_3_3 - L_3_2 * U_2_3;
          double U_3_4 = W_3_4 - L_3_0 * U_0_4 - L_3_2 * U_2_4;
          double U_3_5 = 0.0 - L_3_0 * U_0_5 - L_3_1 * U_1_5 - L_3_2 * U_2_5;
          double U_3_6 = 0.0 - L_3_0 * U_0_6 - L_3_2 * U_2_6;
          double L_4_3 = (W_4_3 - L_4_2 * U_2_3) / U_3_3;
          double U_4_4 = W_4_4 - L_4_0 * U_0_4 - L_4_2 * U_2_4 - L_4_3 * U_3_4;
          double U_4_5 = 0.0 - L_4_0 * U_0_5 - L_4_1 * U_1_5 - L_4_2 * U_2_5 - L_4_3 * U_3_5;
          double U_4_6 = 0.0 - L_4_0 * U_0_6 - L_4_2 * U_2_6 - L_4_3 * U_3_6;
          double U_5_5 = W_5_5;
          double U_6_6 = W_6_6;

          // 4. Forward & Backward Substitution for Stage K1
          double y1_0 = F1_0;
          double y1_1 = F1_1;
          double y1_2 = F1_2 - L_2_0 * y1_0 - L_2_1 * y1_1;
          double y1_3 = F1_3 - L_3_0 * y1_0 - L_3_1 * y1_1 - L_3_2 * y1_2;
          double y1_4 = F1_4 - L_4_0 * y1_0 - L_4_1 * y1_1 - L_4_2 * y1_2 - L_4_3 * y1_3;
          double y1_5 = F1_5;
          double y1_6 = F1_6;
          double K1_6 = y1_6 / U_6_6;
          double K1_5 = y1_5 / U_5_5;
          double K1_4 = (y1_4 - U_4_5 * K1_5 - U_4_6 * K1_6) / U_4_4;
          double K1_3 = (y1_3 - U_3_4 * K1_4 - U_3_5 * K1_5 - U_3_6 * K1_6) / U_3_3;
          double K1_2 = (y1_2 - U_2_3 * K1_3 - U_2_4 * K1_4 - U_2_5 * K1_5 - U_2_6 * K1_6) / U_2_2;
          double K1_1 = (y1_1 - U_1_2 * K1_2 - U_1_5 * K1_5) / U_1_1;
          double K1_0 = (y1_0 - U_0_1 * K1_1 - U_0_2 * K1_2 - U_0_4 * K1_4 - U_0_5 * K1_5 - U_0_6 * K1_6) / U_0_0;

          // 5. Fused Intermediate State Ynew
          double Ynew_0 = S_0 + ros_A0 * K1_0;
          double Ynew_1 = S_1 + ros_A0 * K1_1;
          double Ynew_2 = S_2 + ros_A0 * K1_2;
          double Ynew_3 = S_3 + ros_A0 * K1_3;
          double Ynew_4 = S_4 + ros_A0 * K1_4;
          double Ynew_5 = S_5 + ros_A0 * K1_5;
          double Ynew_6 = S_6 + ros_A0 * K1_6;

          // 6. Stage 2 Rates (F2) & Substitution for Stage K2
          double F2_0 = 7.1100000000000005e-11*Ynew_5*Ynew_1 - 1.0690000000000001e-11*Ynew_4*Ynew_0 + 0.01289*Ynew_4 - 8.0180000000000003e-17*Ynew_0*Ynew_6 - 1.576e-15*Ynew_0*Ynew_2 + 5.2860000000000002e-10*Ynew_6 + 0.00061200000000000002*Ynew_2;
          double rhs2_0 = F2_0 + (ros_C0 / dt) * K1_0;
          double F2_1 = -7.1100000000000005e-11*Ynew_5*Ynew_1 - 1.2e-10*Ynew_1*Ynew_2 + 0.00107*Ynew_2;
          double rhs2_1 = F2_1 + (ros_C0 / dt) * K1_1;
          double F2_2 = -6.0620000000000003e-15*Ynew_3*Ynew_2 + 8.0180000000000003e-17*Ynew_0*Ynew_6 - 1.576e-15*Ynew_0*Ynew_2 - 1.2e-10*Ynew_1*Ynew_2 - 0.0016819999999999999*Ynew_2;
          double rhs2_2 = F2_2 + (ros_C0 / dt) * K1_2;
          double F2_3 = -6.0620000000000003e-15*Ynew_3*Ynew_2 + 1.0690000000000001e-11*Ynew_4*Ynew_0 + 0.01289*Ynew_4;
          double rhs2_3 = F2_3 + (ros_C0 / dt) * K1_3;
          double F2_4 = 6.0620000000000003e-15*Ynew_3*Ynew_2 - 1.0690000000000001e-11*Ynew_4*Ynew_0 - 0.01289*Ynew_4;
          double rhs2_4 = F2_4 + (ros_C0 / dt) * K1_4;
          double F2_5 = 0.0;
          double rhs2_5 = F2_5 + (ros_C0 / dt) * K1_5;
          double F2_6 = 0.0;
          double rhs2_6 = F2_6 + (ros_C0 / dt) * K1_6;
          double y2_0 = rhs2_0;
          double y2_1 = rhs2_1;
          double y2_2 = rhs2_2 - L_2_0 * y2_0 - L_2_1 * y2_1;
          double y2_3 = rhs2_3 - L_3_0 * y2_0 - L_3_1 * y2_1 - L_3_2 * y2_2;
          double y2_4 = rhs2_4 - L_4_0 * y2_0 - L_4_1 * y2_1 - L_4_2 * y2_2 - L_4_3 * y2_3;
          double y2_5 = rhs2_5;
          double y2_6 = rhs2_6;
          double K2_6 = y2_6 / U_6_6;
          double K2_5 = y2_5 / U_5_5;
          double K2_4 = (y2_4 - U_4_5 * K2_5 - U_4_6 * K2_6) / U_4_4;
          double K2_3 = (y2_3 - U_3_4 * K2_4 - U_3_5 * K2_5 - U_3_6 * K2_6) / U_3_3;
          double K2_2 = (y2_2 - U_2_3 * K2_3 - U_2_4 * K2_4 - U_2_5 * K2_5 - U_2_6 * K2_6) / U_2_2;
          double K2_1 = (y2_1 - U_1_2 * K2_2 - U_1_5 * K2_5) / U_1_1;
          double K2_0 = (y2_0 - U_0_1 * K2_1 - U_0_2 * K2_2 - U_0_4 * K2_4 - U_0_5 * K2_5 - U_0_6 * K2_6) / U_0_0;

          // 7. Error Estimation
          double err_norm = 0.0;
          {
              double sci = atol[0] + rtol[0] * Kokkos::fabs(state(0));
              double err_i = Kokkos::fabs(K1_0 - K2_0) / sci;
              if (err_i > err_norm) err_norm = err_i;
          }
          {
              double sci = atol[1] + rtol[1] * Kokkos::fabs(state(1));
              double err_i = Kokkos::fabs(K1_1 - K2_1) / sci;
              if (err_i > err_norm) err_norm = err_i;
          }
          {
              double sci = atol[2] + rtol[2] * Kokkos::fabs(state(2));
              double err_i = Kokkos::fabs(K1_2 - K2_2) / sci;
              if (err_i > err_norm) err_norm = err_i;
          }
          {
              double sci = atol[3] + rtol[3] * Kokkos::fabs(state(3));
              double err_i = Kokkos::fabs(K1_3 - K2_3) / sci;
              if (err_i > err_norm) err_norm = err_i;
          }
          {
              double sci = atol[4] + rtol[4] * Kokkos::fabs(state(4));
              double err_i = Kokkos::fabs(K1_4 - K2_4) / sci;
              if (err_i > err_norm) err_norm = err_i;
          }
          {
              double sci = atol[5] + rtol[5] * Kokkos::fabs(state(5));
              double err_i = Kokkos::fabs(K1_5 - K2_5) / sci;
              if (err_i > err_norm) err_norm = err_i;
          }
          {
              double sci = atol[6] + rtol[6] * Kokkos::fabs(state(6));
              double err_i = Kokkos::fabs(K1_6 - K2_6) / sci;
              if (err_i > err_norm) err_norm = err_i;
          }

          // 8. Step Size Control
          double factor = safety * Kokkos::pow(1.0 / Kokkos::max(err_norm, 1e-10), 0.5);
          factor = Kokkos::max(min_shrink, Kokkos::min(factor, max_growth));

          if (err_norm <= 1.0) {
              state(0) += ros_M0 * K1_0 + ros_M1 * K2_0;
              state(1) += ros_M0 * K1_1 + ros_M1 * K2_1;
              state(2) += ros_M0 * K1_2 + ros_M1 * K2_2;
              state(3) += ros_M0 * K1_3 + ros_M1 * K2_3;
              state(4) += ros_M0 * K1_4 + ros_M1 * K2_4;
              state(5) += ros_M0 * K1_5 + ros_M1 * K2_5;
              state(6) += ros_M0 * K1_6 + ros_M1 * K2_6;
              t += dt;
              dt *= factor;
          } else {
              dt *= factor;
          }
          } // end while (t < dt_total)
      }

      template <class StateView>
      KOKKOS_INLINE_FUNCTION void integrate_with_reduction(
          double dt_total, StateView& state, double importance_threshold) const
      {
          const int NUM_SPECIES = 7;
          const double g = 1.70710678118654752440;
          const double ros_A0 = 1.0 / g;
          const double ros_C0 = -2.0 / g;
          const double ros_M0 = 3.0 / (2.0 * g);
          const double ros_M1 = 1.0 / (2.0 * g);
          const double safety = 0.9;
          const double max_growth = 5.0;
          const double min_shrink = 0.2;

          bool active[NUM_SPECIES];
          double t = 0.0;
          double dt = dt_total;

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
          const double S_0 = state(0);
          const double S_1 = state(1);
          const double S_2 = state(2);
          const double S_3 = state(3);
          const double S_4 = state(4);
          const double S_5 = state(5);
          const double S_6 = state(6);

          // 1. Stage 1 Rates (F1)
          double F1_0 = 7.1100000000000005e-11*S_5*S_1 - 1.0690000000000001e-11*S_4*S_0 + 0.01289*S_4 - 8.0180000000000003e-17*S_0*S_6 - 1.576e-15*S_0*S_2 + 5.2860000000000002e-10*S_6 + 0.00061200000000000002*S_2;
          double F1_1 = -7.1100000000000005e-11*S_5*S_1 - 1.2e-10*S_1*S_2 + 0.00107*S_2;
          double F1_2 = -6.0620000000000003e-15*S_3*S_2 + 8.0180000000000003e-17*S_0*S_6 - 1.576e-15*S_0*S_2 - 1.2e-10*S_1*S_2 - 0.0016819999999999999*S_2;
          double F1_3 = -6.0620000000000003e-15*S_3*S_2 + 1.0690000000000001e-11*S_4*S_0 + 0.01289*S_4;
          double F1_4 = 6.0620000000000003e-15*S_3*S_2 - 1.0690000000000001e-11*S_4*S_0 - 0.01289*S_4;
          double F1_5 = 0.0;
          double F1_6 = 0.0;

          // 2. Evaluate importance and update active set
          active[0] = (Kokkos::fabs(F1_0) / (atol[0] + rtol[0] * Kokkos::fabs(state(0))) >= importance_threshold);
          active[1] = (Kokkos::fabs(F1_1) / (atol[1] + rtol[1] * Kokkos::fabs(state(1))) >= importance_threshold);
          active[2] = (Kokkos::fabs(F1_2) / (atol[2] + rtol[2] * Kokkos::fabs(state(2))) >= importance_threshold);
          active[3] = (Kokkos::fabs(F1_3) / (atol[3] + rtol[3] * Kokkos::fabs(state(3))) >= importance_threshold);
          active[4] = (Kokkos::fabs(F1_4) / (atol[4] + rtol[4] * Kokkos::fabs(state(4))) >= importance_threshold);
          active[5] = (Kokkos::fabs(F1_5) / (atol[5] + rtol[5] * Kokkos::fabs(state(5))) >= importance_threshold);
          active[6] = (Kokkos::fabs(F1_6) / (atol[6] + rtol[6] * Kokkos::fabs(state(6))) >= importance_threshold);

          // 3. Analytical Jacobian & Iteration Matrix W (identity for frozen species)
          double J_0_0 = -1.0690000000000001e-11*S_4 - 8.0180000000000003e-17*S_6 - 1.576e-15*S_2;
          double J_0_1 = 7.1100000000000005e-11*S_5;
          double J_0_2 = 0.00061200000000000002 - 1.576e-15*S_0;
          double J_0_4 = 0.01289 - 1.0690000000000001e-11*S_0;
          double J_0_5 = 7.1100000000000005e-11*S_1;
          double J_0_6 = 5.2860000000000002e-10 - 8.0180000000000003e-17*S_0;
          double J_1_1 = -7.1100000000000005e-11*S_5 - 1.2e-10*S_2;
          double J_1_2 = 0.00107 - 1.2e-10*S_1;
          double J_1_5 = -7.1100000000000005e-11*S_1;
          double J_2_0 = 8.0180000000000003e-17*S_6 - 1.576e-15*S_2;
          double J_2_1 = -1.2e-10*S_2;
          double J_2_2 = -6.0620000000000003e-15*S_3 - 1.576e-15*S_0 - 1.2e-10*S_1 - 0.0016819999999999999;
          double J_2_3 = -6.0620000000000003e-15*S_2;
          double J_2_6 = 8.0180000000000003e-17*S_0;
          double J_3_0 = 1.0690000000000001e-11*S_4;
          double J_3_2 = -6.0620000000000003e-15*S_3;
          double J_3_3 = -6.0620000000000003e-15*S_2;
          double J_3_4 = 1.0690000000000001e-11*S_0 + 0.01289;
          double J_4_0 = -1.0690000000000001e-11*S_4;
          double J_4_2 = 6.0620000000000003e-15*S_3;
          double J_4_3 = 6.0620000000000003e-15*S_2;
          double J_4_4 = -1.0690000000000001e-11*S_0 - 0.01289;
          double W_0_0 = active[0] ? (inv_g_dt - J_0_0) : 1.0;
          double W_0_1 = (active[0] && active[1]) ? (-J_0_1) : 0.0;
          double W_0_2 = (active[0] && active[2]) ? (-J_0_2) : 0.0;
          double W_0_4 = (active[0] && active[4]) ? (-J_0_4) : 0.0;
          double W_0_5 = (active[0] && active[5]) ? (-J_0_5) : 0.0;
          double W_0_6 = (active[0] && active[6]) ? (-J_0_6) : 0.0;
          double W_1_1 = active[1] ? (inv_g_dt - J_1_1) : 1.0;
          double W_1_2 = (active[1] && active[2]) ? (-J_1_2) : 0.0;
          double W_1_5 = (active[1] && active[5]) ? (-J_1_5) : 0.0;
          double W_2_0 = (active[2] && active[0]) ? (-J_2_0) : 0.0;
          double W_2_1 = (active[2] && active[1]) ? (-J_2_1) : 0.0;
          double W_2_2 = active[2] ? (inv_g_dt - J_2_2) : 1.0;
          double W_2_3 = (active[2] && active[3]) ? (-J_2_3) : 0.0;
          double W_2_6 = (active[2] && active[6]) ? (-J_2_6) : 0.0;
          double W_3_0 = (active[3] && active[0]) ? (-J_3_0) : 0.0;
          double W_3_2 = (active[3] && active[2]) ? (-J_3_2) : 0.0;
          double W_3_3 = active[3] ? (inv_g_dt - J_3_3) : 1.0;
          double W_3_4 = (active[3] && active[4]) ? (-J_3_4) : 0.0;
          double W_4_0 = (active[4] && active[0]) ? (-J_4_0) : 0.0;
          double W_4_2 = (active[4] && active[2]) ? (-J_4_2) : 0.0;
          double W_4_3 = (active[4] && active[3]) ? (-J_4_3) : 0.0;
          double W_4_4 = active[4] ? (inv_g_dt - J_4_4) : 1.0;
          double W_5_5 = active[5] ? inv_g_dt : 1.0;
          double W_6_6 = active[6] ? inv_g_dt : 1.0;

          // 4. Symbolic LU Factorization (conditional skip for frozen species)
          double U_0_0 = W_0_0;
          double U_0_1 = W_0_1;
          double U_0_2 = W_0_2;
          double U_0_4 = W_0_4;
          double U_0_5 = W_0_5;
          double U_0_6 = W_0_6;
          double L_2_0 = (W_2_0) / U_0_0;
          double L_3_0 = (W_3_0) / U_0_0;
          double L_4_0 = (W_4_0) / U_0_0;
          double U_1_1 = W_1_1;
          double U_1_2 = W_1_2;
          double U_1_5 = W_1_5;
          double L_2_1 = (W_2_1 - L_2_0 * U_0_1) / U_1_1;
          double L_3_1 = (0.0 - L_3_0 * U_0_1) / U_1_1;
          double L_4_1 = (0.0 - L_4_0 * U_0_1) / U_1_1;
          double U_2_2 = W_2_2 - L_2_0 * U_0_2 - L_2_1 * U_1_2;
          double U_2_3 = W_2_3;
          double U_2_4 = 0.0 - L_2_0 * U_0_4;
          double U_2_5 = 0.0 - L_2_0 * U_0_5 - L_2_1 * U_1_5;
          double U_2_6 = W_2_6 - L_2_0 * U_0_6;
          double L_3_2 = (W_3_2 - L_3_0 * U_0_2 - L_3_1 * U_1_2) / U_2_2;
          double L_4_2 = (W_4_2 - L_4_0 * U_0_2 - L_4_1 * U_1_2) / U_2_2;
          double U_3_3 = W_3_3 - L_3_2 * U_2_3;
          double U_3_4 = W_3_4 - L_3_0 * U_0_4 - L_3_2 * U_2_4;
          double U_3_5 = 0.0 - L_3_0 * U_0_5 - L_3_1 * U_1_5 - L_3_2 * U_2_5;
          double U_3_6 = 0.0 - L_3_0 * U_0_6 - L_3_2 * U_2_6;
          double L_4_3 = (W_4_3 - L_4_2 * U_2_3) / U_3_3;
          double U_4_4 = W_4_4 - L_4_0 * U_0_4 - L_4_2 * U_2_4 - L_4_3 * U_3_4;
          double U_4_5 = 0.0 - L_4_0 * U_0_5 - L_4_1 * U_1_5 - L_4_2 * U_2_5 - L_4_3 * U_3_5;
          double U_4_6 = 0.0 - L_4_0 * U_0_6 - L_4_2 * U_2_6 - L_4_3 * U_3_6;
          double U_5_5 = W_5_5;
          double U_6_6 = W_6_6;

          // 5. Forward & Backward Substitution for K1 (frozen species get K1=0)
          double y1_0 = active[0] ? (F1_0) : 0.0;
          double y1_1 = active[1] ? (F1_1) : 0.0;
          double y1_2 = active[2] ? (F1_2 - L_2_0 * y1_0 - L_2_1 * y1_1) : 0.0;
          double y1_3 = active[3] ? (F1_3 - L_3_0 * y1_0 - L_3_1 * y1_1 - L_3_2 * y1_2) : 0.0;
          double y1_4 = active[4] ? (F1_4 - L_4_0 * y1_0 - L_4_1 * y1_1 - L_4_2 * y1_2 - L_4_3 * y1_3) : 0.0;
          double y1_5 = active[5] ? (F1_5) : 0.0;
          double y1_6 = active[6] ? (F1_6) : 0.0;
          double K1_6 = active[6] ? (y1_6 / U_6_6) : 0.0;
          double K1_5 = active[5] ? (y1_5 / U_5_5) : 0.0;
          double K1_4 = active[4] ? ((y1_4 - U_4_5 * K1_5 - U_4_6 * K1_6) / U_4_4) : 0.0;
          double K1_3 = active[3] ? ((y1_3 - U_3_4 * K1_4 - U_3_5 * K1_5 - U_3_6 * K1_6) / U_3_3) : 0.0;
          double K1_2 = active[2] ? ((y1_2 - U_2_3 * K1_3 - U_2_4 * K1_4 - U_2_5 * K1_5 - U_2_6 * K1_6) / U_2_2) : 0.0;
          double K1_1 = active[1] ? ((y1_1 - U_1_2 * K1_2 - U_1_5 * K1_5) / U_1_1) : 0.0;
          double K1_0 = active[0] ? ((y1_0 - U_0_1 * K1_1 - U_0_2 * K1_2 - U_0_4 * K1_4 - U_0_5 * K1_5 - U_0_6 * K1_6) / U_0_0) : 0.0;

          // 6. Fused Intermediate State Ynew
          double Ynew_0 = S_0 + ros_A0 * K1_0;
          double Ynew_1 = S_1 + ros_A0 * K1_1;
          double Ynew_2 = S_2 + ros_A0 * K1_2;
          double Ynew_3 = S_3 + ros_A0 * K1_3;
          double Ynew_4 = S_4 + ros_A0 * K1_4;
          double Ynew_5 = S_5 + ros_A0 * K1_5;
          double Ynew_6 = S_6 + ros_A0 * K1_6;

          // 7. Stage 2 Rates (F2) & Substitution for K2 (frozen species get K2=0)
          double F2_0 = 7.1100000000000005e-11*Ynew_5*Ynew_1 - 1.0690000000000001e-11*Ynew_4*Ynew_0 + 0.01289*Ynew_4 - 8.0180000000000003e-17*Ynew_0*Ynew_6 - 1.576e-15*Ynew_0*Ynew_2 + 5.2860000000000002e-10*Ynew_6 + 0.00061200000000000002*Ynew_2;
          double rhs2_0 = F2_0 + (ros_C0 / dt) * K1_0;
          double F2_1 = -7.1100000000000005e-11*Ynew_5*Ynew_1 - 1.2e-10*Ynew_1*Ynew_2 + 0.00107*Ynew_2;
          double rhs2_1 = F2_1 + (ros_C0 / dt) * K1_1;
          double F2_2 = -6.0620000000000003e-15*Ynew_3*Ynew_2 + 8.0180000000000003e-17*Ynew_0*Ynew_6 - 1.576e-15*Ynew_0*Ynew_2 - 1.2e-10*Ynew_1*Ynew_2 - 0.0016819999999999999*Ynew_2;
          double rhs2_2 = F2_2 + (ros_C0 / dt) * K1_2;
          double F2_3 = -6.0620000000000003e-15*Ynew_3*Ynew_2 + 1.0690000000000001e-11*Ynew_4*Ynew_0 + 0.01289*Ynew_4;
          double rhs2_3 = F2_3 + (ros_C0 / dt) * K1_3;
          double F2_4 = 6.0620000000000003e-15*Ynew_3*Ynew_2 - 1.0690000000000001e-11*Ynew_4*Ynew_0 - 0.01289*Ynew_4;
          double rhs2_4 = F2_4 + (ros_C0 / dt) * K1_4;
          double F2_5 = 0.0;
          double rhs2_5 = F2_5 + (ros_C0 / dt) * K1_5;
          double F2_6 = 0.0;
          double rhs2_6 = F2_6 + (ros_C0 / dt) * K1_6;
          double y2_0 = active[0] ? (rhs2_0) : 0.0;
          double y2_1 = active[1] ? (rhs2_1) : 0.0;
          double y2_2 = active[2] ? (rhs2_2 - L_2_0 * y2_0 - L_2_1 * y2_1) : 0.0;
          double y2_3 = active[3] ? (rhs2_3 - L_3_0 * y2_0 - L_3_1 * y2_1 - L_3_2 * y2_2) : 0.0;
          double y2_4 = active[4] ? (rhs2_4 - L_4_0 * y2_0 - L_4_1 * y2_1 - L_4_2 * y2_2 - L_4_3 * y2_3) : 0.0;
          double y2_5 = active[5] ? (rhs2_5) : 0.0;
          double y2_6 = active[6] ? (rhs2_6) : 0.0;
          double K2_6 = active[6] ? (y2_6 / U_6_6) : 0.0;
          double K2_5 = active[5] ? (y2_5 / U_5_5) : 0.0;
          double K2_4 = active[4] ? ((y2_4 - U_4_5 * K2_5 - U_4_6 * K2_6) / U_4_4) : 0.0;
          double K2_3 = active[3] ? ((y2_3 - U_3_4 * K2_4 - U_3_5 * K2_5 - U_3_6 * K2_6) / U_3_3) : 0.0;
          double K2_2 = active[2] ? ((y2_2 - U_2_3 * K2_3 - U_2_4 * K2_4 - U_2_5 * K2_5 - U_2_6 * K2_6) / U_2_2) : 0.0;
          double K2_1 = active[1] ? ((y2_1 - U_1_2 * K2_2 - U_1_5 * K2_5) / U_1_1) : 0.0;
          double K2_0 = active[0] ? ((y2_0 - U_0_1 * K2_1 - U_0_2 * K2_2 - U_0_4 * K2_4 - U_0_5 * K2_5 - U_0_6 * K2_6) / U_0_0) : 0.0;

          // 8. Error Estimation
          double err_norm = 0.0;
          {
              double sci = atol[0] + rtol[0] * Kokkos::fabs(state(0));
              double err_i = Kokkos::fabs(K1_0 - K2_0) / sci;
              if (err_i > err_norm) err_norm = err_i;
          }
          {
              double sci = atol[1] + rtol[1] * Kokkos::fabs(state(1));
              double err_i = Kokkos::fabs(K1_1 - K2_1) / sci;
              if (err_i > err_norm) err_norm = err_i;
          }
          {
              double sci = atol[2] + rtol[2] * Kokkos::fabs(state(2));
              double err_i = Kokkos::fabs(K1_2 - K2_2) / sci;
              if (err_i > err_norm) err_norm = err_i;
          }
          {
              double sci = atol[3] + rtol[3] * Kokkos::fabs(state(3));
              double err_i = Kokkos::fabs(K1_3 - K2_3) / sci;
              if (err_i > err_norm) err_norm = err_i;
          }
          {
              double sci = atol[4] + rtol[4] * Kokkos::fabs(state(4));
              double err_i = Kokkos::fabs(K1_4 - K2_4) / sci;
              if (err_i > err_norm) err_norm = err_i;
          }
          {
              double sci = atol[5] + rtol[5] * Kokkos::fabs(state(5));
              double err_i = Kokkos::fabs(K1_5 - K2_5) / sci;
              if (err_i > err_norm) err_norm = err_i;
          }
          {
              double sci = atol[6] + rtol[6] * Kokkos::fabs(state(6));
              double err_i = Kokkos::fabs(K1_6 - K2_6) / sci;
              if (err_i > err_norm) err_norm = err_i;
          }

          // 9. Step Size Control (only active species update state)
          double factor = safety * Kokkos::pow(1.0 / Kokkos::max(err_norm, 1e-10), 0.5);
          factor = Kokkos::max(min_shrink, Kokkos::min(factor, max_growth));

          if (err_norm <= 1.0) {
              if (active[0]) state(0) += ros_M0 * K1_0 + ros_M1 * K2_0;
              if (active[1]) state(1) += ros_M0 * K1_1 + ros_M1 * K2_1;
              if (active[2]) state(2) += ros_M0 * K1_2 + ros_M1 * K2_2;
              if (active[3]) state(3) += ros_M0 * K1_3 + ros_M1 * K2_3;
              if (active[4]) state(4) += ros_M0 * K1_4 + ros_M1 * K2_4;
              if (active[5]) state(5) += ros_M0 * K1_5 + ros_M1 * K2_5;
              if (active[6]) state(6) += ros_M0 * K1_6 + ros_M1 * K2_6;
              t += dt;
              dt *= factor;
          } else {
              dt *= factor;
          }
          } // end while (t < dt_total)
      }
  };
}
