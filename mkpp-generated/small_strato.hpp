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
          F_block(0) = 7.1100000000000005e-11*state(5) - 8.0180000000000003e-17*state(0)*state(6) - 1.576e-15*state(0)*state(2) - 1.0690000000000001e-11*state(0) + 5.2860000000000002e-10*state(6) + 0.00061200000000000002*state(2) + 0.01289;
          F_block(1) = -7.1100000000000005e-11*state(5) + 0.00106999988*state(2);
          F_block(2) = 8.0180000000000003e-17*state(0)*state(6) - 1.576e-15*state(0)*state(2) - 0.0016820001200060618*state(2);
          F_block(3) = 1.0690000000000001e-11*state(0) - 6.0620000000000003e-15*state(2) + 0.01289;
          F_block(4) = -1.0690000000000001e-11*state(0) + 6.0620000000000003e-15*state(2) - 0.01289;
          F_block(5) = 0.0;
          F_block(6) = 0.0;
      }

      template <class StateView, class JacView>
      KOKKOS_INLINE_FUNCTION void compute_jacobian(const StateView& state, JacView& J_block) const {
          J_block(0, 0) = -8.0180000000000003e-17*state(6) - 1.576e-15*state(2) - 1.0690000000000001e-11;
          J_block(0, 1) = 7.1100000000000005e-11*state(5);
          J_block(0, 2) = 0.00061200000000000002 - 1.576e-15*state(0);
          J_block(0, 4) = 0.01289 - 1.0690000000000001e-11*state(0);
          J_block(0, 5) = 7.1100000000000005e-11;
          J_block(0, 6) = 5.2860000000000002e-10 - 8.0180000000000003e-17*state(0);
          J_block(1, 1) = -7.1100000000000005e-11*state(5) - 1.2e-10*state(2);
          J_block(1, 2) = 0.00106999988;
          J_block(1, 5) = -7.1100000000000005e-11;
          J_block(2, 0) = 8.0180000000000003e-17*state(6) - 1.576e-15*state(2);
          J_block(2, 1) = -1.2e-10*state(2);
          J_block(2, 2) = -1.576e-15*state(0) - 0.0016820001200060618;
          J_block(2, 3) = -6.0620000000000003e-15*state(2);
          J_block(2, 6) = 8.0180000000000003e-17*state(0);
          J_block(3, 0) = 1.0690000000000001e-11;
          J_block(3, 2) = -6.0620000000000003e-15;
          J_block(3, 3) = -6.0620000000000003e-15*state(2);
          J_block(3, 4) = 1.0690000000000001e-11*state(0) + 0.01289;
          J_block(4, 0) = -1.0690000000000001e-11;
          J_block(4, 2) = 6.0620000000000003e-15;
          J_block(4, 3) = 6.0620000000000003e-15*state(2);
          J_block(4, 4) = -1.0690000000000001e-11*state(0) - 0.01289;
      }

      template <class StateView, class JacView>
      KOKKOS_INLINE_FUNCTION void compute_adjoint(const StateView& state, JacView& J_adj_block) const {
          J_adj_block(0, 0) = -8.0180000000000003e-17*state(6) - 1.576e-15*state(2) - 1.0690000000000001e-11;
          J_adj_block(0, 2) = 8.0180000000000003e-17*state(6) - 1.576e-15*state(2);
          J_adj_block(0, 3) = 1.0690000000000001e-11;
          J_adj_block(0, 4) = -1.0690000000000001e-11;
          J_adj_block(1, 0) = 7.1100000000000005e-11*state(5);
          J_adj_block(1, 1) = -7.1100000000000005e-11*state(5) - 1.2e-10*state(2);
          J_adj_block(1, 2) = -1.2e-10*state(2);
          J_adj_block(2, 0) = 0.00061200000000000002 - 1.576e-15*state(0);
          J_adj_block(2, 1) = 0.00106999988;
          J_adj_block(2, 2) = -1.576e-15*state(0) - 0.0016820001200060618;
          J_adj_block(2, 3) = -6.0620000000000003e-15;
          J_adj_block(2, 4) = 6.0620000000000003e-15;
          J_adj_block(3, 2) = -6.0620000000000003e-15*state(2);
          J_adj_block(3, 3) = -6.0620000000000003e-15*state(2);
          J_adj_block(3, 4) = 6.0620000000000003e-15*state(2);
          J_adj_block(4, 0) = 0.01289 - 1.0690000000000001e-11*state(0);
          J_adj_block(4, 3) = 1.0690000000000001e-11*state(0) + 0.01289;
          J_adj_block(4, 4) = -1.0690000000000001e-11*state(0) - 0.01289;
          J_adj_block(5, 0) = 7.1100000000000005e-11;
          J_adj_block(5, 1) = -7.1100000000000005e-11;
          J_adj_block(6, 0) = 5.2860000000000002e-10 - 8.0180000000000003e-17*state(0);
          J_adj_block(6, 2) = 8.0180000000000003e-17*state(0);
      }

      template <class StateView, class DeltaView, class RateView>
      KOKKOS_INLINE_FUNCTION void compute_tlm(const StateView& state, const DeltaView& delta_C, RateView& dF_block) const {
          dF_block(0) = 0.0;
          dF_block(0) += (-8.0180000000000003e-17*state(6) - 1.576e-15*state(2) - 1.0690000000000001e-11) * delta_C(0);
          dF_block(0) += (7.1100000000000005e-11*state(5)) * delta_C(1);
          dF_block(0) += (0.00061200000000000002 - 1.576e-15*state(0)) * delta_C(2);
          dF_block(0) += (0.01289 - 1.0690000000000001e-11*state(0)) * delta_C(4);
          dF_block(0) += (7.1100000000000005e-11) * delta_C(5);
          dF_block(0) += (5.2860000000000002e-10 - 8.0180000000000003e-17*state(0)) * delta_C(6);
          dF_block(1) = 0.0;
          dF_block(1) += (-7.1100000000000005e-11*state(5) - 1.2e-10*state(2)) * delta_C(1);
          dF_block(1) += (0.00106999988) * delta_C(2);
          dF_block(1) += (-7.1100000000000005e-11) * delta_C(5);
          dF_block(2) = 0.0;
          dF_block(2) += (8.0180000000000003e-17*state(6) - 1.576e-15*state(2)) * delta_C(0);
          dF_block(2) += (-1.2e-10*state(2)) * delta_C(1);
          dF_block(2) += (-1.576e-15*state(0) - 0.0016820001200060618) * delta_C(2);
          dF_block(2) += (-6.0620000000000003e-15*state(2)) * delta_C(3);
          dF_block(2) += (8.0180000000000003e-17*state(0)) * delta_C(6);
          dF_block(3) = 0.0;
          dF_block(3) += (1.0690000000000001e-11) * delta_C(0);
          dF_block(3) += (-6.0620000000000003e-15) * delta_C(2);
          dF_block(3) += (-6.0620000000000003e-15*state(2)) * delta_C(3);
          dF_block(3) += (1.0690000000000001e-11*state(0) + 0.01289) * delta_C(4);
          dF_block(4) = 0.0;
          dF_block(4) += (-1.0690000000000001e-11) * delta_C(0);
          dF_block(4) += (6.0620000000000003e-15) * delta_C(2);
          dF_block(4) += (6.0620000000000003e-15*state(2)) * delta_C(3);
          dF_block(4) += (-1.0690000000000001e-11*state(0) - 0.01289) * delta_C(4);
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

      template <class StateView>
      KOKKOS_INLINE_FUNCTION void integrate(double dt, StateView& state) const {
          const int NUM_SPECIES = 7;
          const double g = 1.70710678118654752440;
          const double ros_A0 = 1.0 / g;
          const double ros_C0 = -2.0 / g;
          const double ros_M0 = 3.0 / (2.0 * g);
          const double ros_M1 = 1.0 / (2.0 * g);
          const double inv_g_dt = 1.0 / (g * dt);

          // 1. Stage 1 Rates (F1)
          double F1_0 = 7.1100000000000005e-11*state(5) - 8.0180000000000003e-17*state(0)*state(6) - 1.576e-15*state(0)*state(2) - 1.0690000000000001e-11*state(0) + 5.2860000000000002e-10*state(6) + 0.00061200000000000002*state(2) + 0.01289;
          double F1_1 = -7.1100000000000005e-11*state(5) + 0.00106999988*state(2);
          double F1_2 = 8.0180000000000003e-17*state(0)*state(6) - 1.576e-15*state(0)*state(2) - 0.0016820001200060618*state(2);
          double F1_3 = 1.0690000000000001e-11*state(0) - 6.0620000000000003e-15*state(2) + 0.01289;
          double F1_4 = -1.0690000000000001e-11*state(0) + 6.0620000000000003e-15*state(2) - 0.01289;
          double F1_5 = 0.0;
          double F1_6 = 0.0;

          // 2. Analytical Jacobian & Iteration Matrix W = inv_g_dt*I - J
          double J_0_0 = -8.0180000000000003e-17*state(6) - 1.576e-15*state(2) - 1.0690000000000001e-11;
          double J_0_1 = 7.1100000000000005e-11*state(5);
          double J_0_2 = 0.00061200000000000002 - 1.576e-15*state(0);
          double J_0_4 = 0.01289 - 1.0690000000000001e-11*state(0);
          double J_0_5 = 7.1100000000000005e-11;
          double J_0_6 = 5.2860000000000002e-10 - 8.0180000000000003e-17*state(0);
          double J_1_1 = -7.1100000000000005e-11*state(5) - 1.2e-10*state(2);
          double J_1_2 = 0.00106999988;
          double J_1_5 = -7.1100000000000005e-11;
          double J_2_0 = 8.0180000000000003e-17*state(6) - 1.576e-15*state(2);
          double J_2_1 = -1.2e-10*state(2);
          double J_2_2 = -1.576e-15*state(0) - 0.0016820001200060618;
          double J_2_3 = -6.0620000000000003e-15*state(2);
          double J_2_6 = 8.0180000000000003e-17*state(0);
          double J_3_0 = 1.0690000000000001e-11;
          double J_3_2 = -6.0620000000000003e-15;
          double J_3_3 = -6.0620000000000003e-15*state(2);
          double J_3_4 = 1.0690000000000001e-11*state(0) + 0.01289;
          double J_4_0 = -1.0690000000000001e-11;
          double J_4_2 = 6.0620000000000003e-15;
          double J_4_3 = 6.0620000000000003e-15*state(2);
          double J_4_4 = -1.0690000000000001e-11*state(0) - 0.01289;
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
          double K1_0 = F1_6;
          double K1_1 = F1_6;
          double K1_2 = F1_6;
          double K1_3 = F1_6;
          double K1_4 = F1_6;
          double K1_5 = F1_6;
          double K1_6 = F1_6;

          // 5. Fused Intermediate State Ynew
          double Ynew_0 = state(0) + ros_A0 * K1_0;
          double Ynew_1 = state(1) + ros_A0 * K1_1;
          double Ynew_2 = state(2) + ros_A0 * K1_2;
          double Ynew_3 = state(3) + ros_A0 * K1_3;
          double Ynew_4 = state(4) + ros_A0 * K1_4;
          double Ynew_5 = state(5) + ros_A0 * K1_5;
          double Ynew_6 = state(6) + ros_A0 * K1_6;

          // 6. Stage 2 Rates (F2) & Substitution for Stage K2
          double F2_0 = 7.1100000000000005e-11*Ynew_5 - 8.0180000000000003e-17*Ynew_0*Ynew_6 - 1.576e-15*Ynew_0*Ynew_2 - 1.0690000000000001e-11*Ynew_0 + 5.2860000000000002e-10*Ynew_6 + 0.00061200000000000002*Ynew_2 + 0.01289;
          double rhs2_0 = F2_0 + (ros_C0 / dt) * K1_0;
          double F2_1 = -7.1100000000000005e-11*Ynew_5 + 0.00106999988*Ynew_2;
          double rhs2_1 = F2_1 + (ros_C0 / dt) * K1_1;
          double F2_2 = 8.0180000000000003e-17*Ynew_0*Ynew_6 - 1.576e-15*Ynew_0*Ynew_2 - 0.0016820001200060618*Ynew_2;
          double rhs2_2 = F2_2 + (ros_C0 / dt) * K1_2;
          double F2_3 = 1.0690000000000001e-11*Ynew_0 - 6.0620000000000003e-15*Ynew_2 + 0.01289;
          double rhs2_3 = F2_3 + (ros_C0 / dt) * K1_3;
          double F2_4 = -1.0690000000000001e-11*Ynew_0 + 6.0620000000000003e-15*Ynew_2 - 0.01289;
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
          double K2_0 = (y2_0 - U_0_1 * K2_1 - U_0_2 * K2_2 - U_0_4 * K2_4 - U_0_5 * K2_5 - U_0_6 * K2_6) / U_0_0;
          double K2_1 = (y2_1 - U_1_2 * K2_2 - U_1_5 * K2_5) / U_1_1;
          double K2_2 = (y2_2 - U_2_3 * K2_3 - U_2_4 * K2_4 - U_2_5 * K2_5 - U_2_6 * K2_6) / U_2_2;
          double K2_3 = (y2_3 - U_3_4 * K2_4 - U_3_5 * K2_5 - U_3_6 * K2_6) / U_3_3;
          double K2_4 = (y2_4 - U_4_5 * K2_5 - U_4_6 * K2_6) / U_4_4;
          double K2_5 = y2_5 / U_5_5;
          double K2_6 = y2_6 / U_6_6;

          // 7. Final Fused State Update
          state(0) += ros_M0 * K1_0 + ros_M1 * K2_0;
          state(1) += ros_M0 * K1_1 + ros_M1 * K2_1;
          state(2) += ros_M0 * K1_2 + ros_M1 * K2_2;
          state(3) += ros_M0 * K1_3 + ros_M1 * K2_3;
          state(4) += ros_M0 * K1_4 + ros_M1 * K2_4;
          state(5) += ros_M0 * K1_5 + ros_M1 * K2_5;
          state(6) += ros_M0 * K1_6 + ros_M1 * K2_6;
      }
  };
}
