#pragma once
#include <Kokkos_Core.hpp>
// Generated solver for chapman
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
          F_block(0) = -6.0e-34*state(3)*state(0)*state(1) - 7.9999999999999998e-12*state(0)*state(2) + 2.0000000000000002e-5*state(1) + 0.001*state(2);
          F_block(1) = 0.0;
          F_block(2) = 6.0e-34*state(3)*state(0)*state(1) - 7.9999999999999998e-12*state(0)*state(2) - 0.001*state(2);
          F_block(3) = 0.0;
      }

      template <class StateView, class JacView>
      KOKKOS_INLINE_FUNCTION void compute_jacobian(const StateView& state, JacView& J_block) const {
          J_block(0, 0) = -6.0e-34*state(3)*state(1) - 7.9999999999999998e-12*state(2);
          J_block(0, 1) = -6.0e-34*state(3)*state(0) + 2.0000000000000002e-5;
          J_block(0, 2) = 0.001 - 7.9999999999999998e-12*state(0);
          J_block(0, 3) = -6.0e-34*state(0)*state(1);
          J_block(2, 0) = 6.0e-34*state(3)*state(1) - 7.9999999999999998e-12*state(2);
          J_block(2, 1) = 6.0e-34*state(3)*state(0);
          J_block(2, 2) = -7.9999999999999998e-12*state(0) - 0.001;
          J_block(2, 3) = 6.0e-34*state(0)*state(1);
      }

      template <class StateView, class JacView>
      KOKKOS_INLINE_FUNCTION void compute_adjoint(const StateView& state, JacView& J_adj_block) const {
          J_adj_block(0, 0) = -6.0e-34*state(3)*state(1) - 7.9999999999999998e-12*state(2);
          J_adj_block(0, 2) = 6.0e-34*state(3)*state(1) - 7.9999999999999998e-12*state(2);
          J_adj_block(1, 0) = -6.0e-34*state(3)*state(0) + 2.0000000000000002e-5;
          J_adj_block(1, 2) = 6.0e-34*state(3)*state(0);
          J_adj_block(2, 0) = 0.001 - 7.9999999999999998e-12*state(0);
          J_adj_block(2, 2) = -7.9999999999999998e-12*state(0) - 0.001;
          J_adj_block(3, 0) = -6.0e-34*state(0)*state(1);
          J_adj_block(3, 2) = 6.0e-34*state(0)*state(1);
      }

      template <class StateView, class DeltaView, class RateView>
      KOKKOS_INLINE_FUNCTION void compute_tlm(const StateView& state, const DeltaView& delta_C, RateView& dF_block) const {
          dF_block(0) = 0.0;
          dF_block(0) += (-6.0e-34*state(3)*state(1) - 7.9999999999999998e-12*state(2)) * delta_C(0);
          dF_block(0) += (-6.0e-34*state(3)*state(0) + 2.0000000000000002e-5) * delta_C(1);
          dF_block(0) += (0.001 - 7.9999999999999998e-12*state(0)) * delta_C(2);
          dF_block(0) += (-6.0e-34*state(0)*state(1)) * delta_C(3);
          dF_block(1) = 0.0;
          dF_block(2) = 0.0;
          dF_block(2) += (6.0e-34*state(3)*state(1) - 7.9999999999999998e-12*state(2)) * delta_C(0);
          dF_block(2) += (6.0e-34*state(3)*state(0)) * delta_C(1);
          dF_block(2) += (-7.9999999999999998e-12*state(0) - 0.001) * delta_C(2);
          dF_block(2) += (6.0e-34*state(0)*state(1)) * delta_C(3);
          dF_block(3) = 0.0;
      }

      template <class StateView, class MassView>
      KOKKOS_INLINE_FUNCTION void project_mass_conservation(StateView& C_projected, const StateView& C, const MassView& m_0) const {
          // C_projected = C - E^T (E E^T)^-1 (E C - m_0)
          C_projected(0) = C(0);
          C_projected(1) = C(1);
          C_projected(2) = C(2);
          C_projected(3) = C(3);
      }

      template <class StateView>
      KOKKOS_INLINE_FUNCTION void integrate(double dt, StateView& state) const {
          const int NUM_SPECIES = 4;
          const double g = 1.70710678118654752440;
          const double ros_A0 = 1.0 / g;
          const double ros_C0 = -2.0 / g;
          const double ros_M0 = 3.0 / (2.0 * g);
          const double ros_M1 = 1.0 / (2.0 * g);
          const double inv_g_dt = 1.0 / (g * dt);

          // 1. Stage 1 Rates (F1)
          double F1_0 = -6.0e-34*state(3)*state(0)*state(1) - 7.9999999999999998e-12*state(0)*state(2) + 2.0000000000000002e-5*state(1) + 0.001*state(2);
          double F1_1 = 0.0;
          double F1_2 = 6.0e-34*state(3)*state(0)*state(1) - 7.9999999999999998e-12*state(0)*state(2) - 0.001*state(2);
          double F1_3 = 0.0;

          // 2. Analytical Jacobian & Iteration Matrix W = inv_g_dt*I - J
          double J_0_0 = -6.0e-34*state(3)*state(1) - 7.9999999999999998e-12*state(2);
          double J_0_1 = -6.0e-34*state(3)*state(0) + 2.0000000000000002e-5;
          double J_0_2 = 0.001 - 7.9999999999999998e-12*state(0);
          double J_0_3 = -6.0e-34*state(0)*state(1);
          double J_2_0 = 6.0e-34*state(3)*state(1) - 7.9999999999999998e-12*state(2);
          double J_2_1 = 6.0e-34*state(3)*state(0);
          double J_2_2 = -7.9999999999999998e-12*state(0) - 0.001;
          double J_2_3 = 6.0e-34*state(0)*state(1);
          double W_0_0 = inv_g_dt - J_0_0;
          double W_0_1 = -J_0_1;
          double W_0_2 = -J_0_2;
          double W_0_3 = -J_0_3;
          double W_1_1 = inv_g_dt;
          double W_2_0 = -J_2_0;
          double W_2_1 = -J_2_1;
          double W_2_2 = inv_g_dt - J_2_2;
          double W_2_3 = -J_2_3;
          double W_3_3 = inv_g_dt;

          // 3. Symbolic Doolittle Sparse LU Factorization
          double U_0_0 = W_0_0;
          double U_0_1 = W_0_1;
          double U_0_2 = W_0_2;
          double U_0_3 = W_0_3;
          double L_2_0 = (W_2_0) / U_0_0;
          double U_1_1 = W_1_1;
          double L_2_1 = (W_2_1 - L_2_0 * U_0_1) / U_1_1;
          double U_2_2 = W_2_2 - L_2_0 * U_0_2;
          double U_2_3 = W_2_3 - L_2_0 * U_0_3;
          double U_3_3 = W_3_3;

          // 4. Forward & Backward Substitution for Stage K1
          double y1_0 = F1_0;
          double y1_1 = F1_1;
          double y1_2 = F1_2 - L_2_0 * y1_0 - L_2_1 * y1_1;
          double y1_3 = F1_3;
          double K1_0 = F1_3;
          double K1_1 = F1_3;
          double K1_2 = F1_3;
          double K1_3 = F1_3;

          // 5. Fused Intermediate State Ynew
          double Ynew_0 = state(0) + ros_A0 * K1_0;
          double Ynew_1 = state(1) + ros_A0 * K1_1;
          double Ynew_2 = state(2) + ros_A0 * K1_2;
          double Ynew_3 = state(3) + ros_A0 * K1_3;

          // 6. Stage 2 Rates (F2) & Substitution for Stage K2
          double F2_0 = -6.0e-34*Ynew_3*Ynew_0*Ynew_1 - 7.9999999999999998e-12*Ynew_0*Ynew_2 + 2.0000000000000002e-5*Ynew_1 + 0.001*Ynew_2;
          double rhs2_0 = F2_0 + (ros_C0 / dt) * K1_0;
          double F2_1 = 0.0;
          double rhs2_1 = F2_1 + (ros_C0 / dt) * K1_1;
          double F2_2 = 6.0e-34*Ynew_3*Ynew_0*Ynew_1 - 7.9999999999999998e-12*Ynew_0*Ynew_2 - 0.001*Ynew_2;
          double rhs2_2 = F2_2 + (ros_C0 / dt) * K1_2;
          double F2_3 = 0.0;
          double rhs2_3 = F2_3 + (ros_C0 / dt) * K1_3;
          double y2_0 = rhs2_0;
          double y2_1 = rhs2_1;
          double y2_2 = rhs2_2 - L_2_0 * y2_0 - L_2_1 * y2_1;
          double y2_3 = rhs2_3;
          double K2_0 = (y2_0 - U_0_1 * K2_1 - U_0_2 * K2_2 - U_0_3 * K2_3) / U_0_0;
          double K2_1 = y2_1 / U_1_1;
          double K2_2 = (y2_2 - U_2_3 * K2_3) / U_2_2;
          double K2_3 = y2_3 / U_3_3;

          // 7. Final Fused State Update
          state(0) += ros_M0 * K1_0 + ros_M1 * K2_0;
          state(1) += ros_M0 * K1_1 + ros_M1 * K2_1;
          state(2) += ros_M0 * K1_2 + ros_M1 * K2_2;
          state(3) += ros_M0 * K1_3 + ros_M1 * K2_3;
      }
  };
}
