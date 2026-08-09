#pragma once
#include <Kokkos_Core.hpp>
// Generated solver for carbon
namespace mkpp {
  // Pure Kokkos abstractions (no raw pragmas allowed)
  // Bidirectional Host Interface (Zero-Copy)
  using concentrations_view_t = Kokkos::View<double****, Kokkos::LayoutLeft, Kokkos::MemoryUnmanaged>;
  template<typename DeviceType>
  struct SolverKernels {
      template <class StateView, class RateView>
      KOKKOS_INLINE_FUNCTION void compute_rates(const StateView& state, RateView& F_block, const double* jvals) const {
          F_block(0) = 0.0;
          F_block(1) = 38199.012000000002 - 7.3679649000000001e-14*state(1);
          F_block(2) = 4.2566445999999996e-15;
          F_block(3) = 38199.012000000002;
          F_block(4) = 6.6007061575166499e-15*state(0);
          F_block(5) = 1.0315008299507354e-13*state(0);
          F_block(6) = 7.3679649000000001e-14*state(1);
          F_block(7) = -6.6007061575166499e-15*state(0) - 7.3679649000000001e-14*state(1);
          F_block(8) = -1.0315008299507354e-13*state(0);
          F_block(9) = -4.2566445999999996e-15;
          F_block(10) = -38199.012000000002;
      }

      template <class StateView, class JacView>
      KOKKOS_INLINE_FUNCTION void compute_jacobian(const StateView& state, JacView& J_block, const double* jvals) const {
          J_block(1, 1) = -7.3679649000000001e-14;
          J_block(1, 7) = -7.3679649000000001e-14*state(1);
          J_block(1, 9) = 4.2566445999999996e-15;
          J_block(1, 10) = 38199.012000000002;
          J_block(2, 9) = 4.2566445999999996e-15;
          J_block(3, 10) = 38199.012000000002;
          J_block(4, 0) = 6.6007061575166499e-15;
          J_block(4, 7) = 6.6007061575166499e-15*state(0);
          J_block(5, 0) = 1.0315008299507354e-13;
          J_block(5, 8) = 1.0315008299507354e-13*state(0);
          J_block(6, 1) = 7.3679649000000001e-14;
          J_block(6, 7) = 7.3679649000000001e-14*state(1);
          J_block(7, 0) = -6.6007061575166499e-15;
          J_block(7, 1) = -7.3679649000000001e-14;
          J_block(7, 7) = -6.6007061575166499e-15*state(0) - 7.3679649000000001e-14*state(1);
          J_block(8, 0) = -1.0315008299507354e-13;
          J_block(8, 8) = -1.0315008299507354e-13*state(0);
          J_block(9, 9) = -4.2566445999999996e-15;
          J_block(10, 10) = -38199.012000000002;
      }

      template <class StateView, class JacView>
      KOKKOS_INLINE_FUNCTION void compute_adjoint(const StateView& state, JacView& J_adj_block, const double* jvals) const {
          J_adj_block(0, 4) = 6.6007061575166499e-15;
          J_adj_block(0, 5) = 1.0315008299507354e-13;
          J_adj_block(0, 7) = -6.6007061575166499e-15;
          J_adj_block(0, 8) = -1.0315008299507354e-13;
          J_adj_block(1, 1) = -7.3679649000000001e-14;
          J_adj_block(1, 6) = 7.3679649000000001e-14;
          J_adj_block(1, 7) = -7.3679649000000001e-14;
          J_adj_block(7, 1) = -7.3679649000000001e-14*state(1);
          J_adj_block(7, 4) = 6.6007061575166499e-15*state(0);
          J_adj_block(7, 6) = 7.3679649000000001e-14*state(1);
          J_adj_block(7, 7) = -6.6007061575166499e-15*state(0) - 7.3679649000000001e-14*state(1);
          J_adj_block(8, 5) = 1.0315008299507354e-13*state(0);
          J_adj_block(8, 8) = -1.0315008299507354e-13*state(0);
          J_adj_block(9, 1) = 4.2566445999999996e-15;
          J_adj_block(9, 2) = 4.2566445999999996e-15;
          J_adj_block(9, 9) = -4.2566445999999996e-15;
          J_adj_block(10, 1) = 38199.012000000002;
          J_adj_block(10, 3) = 38199.012000000002;
          J_adj_block(10, 10) = -38199.012000000002;
      }

      template <class StateView, class DeltaView, class RateView>
      KOKKOS_INLINE_FUNCTION void compute_tlm(const StateView& state, const DeltaView& delta_C, RateView& dF_block, const double* jvals) const {
          dF_block(0) = 0.0;
          dF_block(1) = 0.0;
          dF_block(1) += (-7.3679649000000001e-14) * delta_C(1);
          dF_block(1) += (-7.3679649000000001e-14*state(1)) * delta_C(7);
          dF_block(1) += (4.2566445999999996e-15) * delta_C(9);
          dF_block(1) += (38199.012000000002) * delta_C(10);
          dF_block(2) = 0.0;
          dF_block(2) += (4.2566445999999996e-15) * delta_C(9);
          dF_block(3) = 0.0;
          dF_block(3) += (38199.012000000002) * delta_C(10);
          dF_block(4) = 0.0;
          dF_block(4) += (6.6007061575166499e-15) * delta_C(0);
          dF_block(4) += (6.6007061575166499e-15*state(0)) * delta_C(7);
          dF_block(5) = 0.0;
          dF_block(5) += (1.0315008299507354e-13) * delta_C(0);
          dF_block(5) += (1.0315008299507354e-13*state(0)) * delta_C(8);
          dF_block(6) = 0.0;
          dF_block(6) += (7.3679649000000001e-14) * delta_C(1);
          dF_block(6) += (7.3679649000000001e-14*state(1)) * delta_C(7);
          dF_block(7) = 0.0;
          dF_block(7) += (-6.6007061575166499e-15) * delta_C(0);
          dF_block(7) += (-7.3679649000000001e-14) * delta_C(1);
          dF_block(7) += (-6.6007061575166499e-15*state(0) - 7.3679649000000001e-14*state(1)) * delta_C(7);
          dF_block(8) = 0.0;
          dF_block(8) += (-1.0315008299507354e-13) * delta_C(0);
          dF_block(8) += (-1.0315008299507354e-13*state(0)) * delta_C(8);
          dF_block(9) = 0.0;
          dF_block(9) += (-4.2566445999999996e-15) * delta_C(9);
          dF_block(10) = 0.0;
          dF_block(10) += (-38199.012000000002) * delta_C(10);
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
          C_projected(7) = C(7);
          C_projected(8) = C(8);
          C_projected(9) = C(9);
          C_projected(10) = C(10);
      }

      static constexpr int NUM_SPECIES = 11;
      static constexpr double atol[NUM_SPECIES] = { 100.0, 100.0, 100.0, 100.0, 100.0, 100.0, 100.0, 100.0, 100.0, 100.0, 100.0 };
      static constexpr double rtol[NUM_SPECIES] = { 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01 };

      template <class StateView>
      KOKKOS_INLINE_FUNCTION void integrate(double dt_total, StateView& state, const double* jvals) const {
          const int NUM_SPECIES = 11;
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
          const double S_0 = state(3);
          const double S_1 = state(2);
          const double S_2 = state(10);
          const double S_3 = state(9);
          const double S_4 = state(1);
          const double S_5 = state(6);
          const double S_6 = state(7);
          const double S_7 = state(4);
          const double S_8 = state(0);
          const double S_9 = state(5);
          const double S_10 = state(8);

          // Analytical Jacobian & Iteration Matrix W = inv_g_dt*I - J (sparse)
          double J_0_0 = -4.2566445999999996e-15;
          double J_1_1 = -38199.012000000002;
          double J_2_2 = -1.0315008299507354e-13*S_8;
          double J_2_10 = -1.0315008299507354e-13;
          double J_3_2 = 1.0315008299507354e-13*S_8;
          double J_3_10 = 1.0315008299507354e-13;
          double J_4_0 = 4.2566445999999996e-15;
          double J_5_5 = -6.6007061575166499e-15*S_8 - 7.3679649000000001e-14*S_4;
          double J_5_7 = -7.3679649000000001e-14;
          double J_5_10 = -6.6007061575166499e-15;
          double J_6_5 = 6.6007061575166499e-15*S_8;
          double J_6_10 = 6.6007061575166499e-15;
          double J_7_0 = 4.2566445999999996e-15;
          double J_7_1 = 38199.012000000002;
          double J_7_5 = -7.3679649000000001e-14*S_4;
          double J_7_7 = -7.3679649000000001e-14;
          double J_8_1 = 38199.012000000002;
          double J_9_5 = 7.3679649000000001e-14*S_4;
          double J_9_7 = 7.3679649000000001e-14;
          double W_0_0 = inv_g_dt - J_0_0;
          double W_0_2 = 0.0;
          double W_1_1 = inv_g_dt - J_1_1;
          double W_1_3 = 0.0;
          double W_2_2 = inv_g_dt - J_2_2;
          double W_3_3 = inv_g_dt;
          double W_4_2 = 0.0;
          double W_4_3 = 0.0;
          double W_4_4 = inv_g_dt;
          double W_4_6 = 0.0;
          double W_5_4 = 0.0;
          double W_5_5 = inv_g_dt - J_5_5;
          double W_5_6 = 0.0;
          double W_6_4 = 0.0;
          double W_6_6 = inv_g_dt;
          double W_6_8 = 0.0;
          double W_7_6 = 0.0;
          double W_7_7 = inv_g_dt - J_7_7;
          double W_7_8 = 0.0;
          double W_8_8 = inv_g_dt;
          double W_9_8 = 0.0;
          double W_9_9 = inv_g_dt;
          double W_9_10 = 0.0;
          double W_10_8 = 0.0;
          double W_10_10 = inv_g_dt;

          // Symbolic Doolittle Sparse LU Factorization
          // Block 0: species [PCOfromNMVOC]
          double U_0_0 = W_0_0;
          double U_0_2 = W_0_2;
          // Block 1: species [PCOfromCH4, LCH4byOH]
          double U_1_1 = W_1_1;
          double U_1_3 = W_1_3;
          // Block 2: species [DummyNMVOC]
          double U_2_2 = W_2_2;
          // Block 4: species [CO]
          double L_4_2 = (W_4_2) / U_2_2;
          // Block 3: species [DummyCH4]
          double U_3_3 = W_3_3;
          double L_4_3 = (W_4_3) / U_3_3;
          double U_4_4 = W_4_4;
          double U_4_6 = W_4_6;
          // Block 5: species [LCObyOH]
          double L_5_4 = (W_5_4) / U_4_4;
          // Block 6: species [FixedOH]
          double L_6_4 = (W_6_4) / U_4_4;
          double U_5_5 = W_5_5;
          double U_5_6 = W_5_6 - L_5_4 * U_4_6;
          double U_6_6 = W_6_6 - L_6_4 * U_4_6;
          double U_6_8 = W_6_8;
          double L_7_6 = (W_7_6) / U_6_6;
          double U_7_7 = W_7_7;
          double U_7_8 = W_7_8 - L_7_6 * U_6_8;
          // Block 7: species [CH4]
          double U_8_8 = W_8_8;
          // Block 8: species [LCH4byCl]
          double L_9_8 = (W_9_8) / U_8_8;
          // Block 9: species [FixedCl]
          double L_10_8 = (W_10_8) / U_8_8;
          double U_9_9 = W_9_9;
          double U_9_10 = W_9_10;
          double U_10_10 = W_10_10;

          // --- Stage 1 ---
          // Rate evaluation F1 at S
          double F1_0 = 38199.012000000002;
          double F1_1 = 4.2566445999999996e-15;
          double F1_2 = -38199.012000000002;
          double F1_3 = -4.2566445999999996e-15;
          double F1_4 = 38199.012000000002 - 7.3679649000000001e-14*S_4;
          double F1_5 = 7.3679649000000001e-14*S_4;
          double F1_6 = -6.6007061575166499e-15*S_8 - 7.3679649000000001e-14*S_4;
          double F1_7 = 6.6007061575166499e-15*S_8;
          double F1_8 = 0.0;
          double F1_9 = 1.0315008299507354e-13*S_8;
          double F1_10 = -1.0315008299507354e-13*S_8;
          // Block 0: K1 forward sub [PCOfromNMVOC]
          double y1_0 = F1_0;
          // Block 1: K1 forward sub [PCOfromCH4, LCH4byOH]
          double y1_1 = F1_1;
          // Block 2: K1 forward sub [DummyNMVOC]
          double y1_2 = F1_2;
          // Block 3: K1 forward sub [DummyCH4]
          double y1_3 = F1_3;
          // Block 4: K1 forward sub [CO]
          double y1_4 = F1_4 - L_4_2 * y1_2 - L_4_3 * y1_3;
          // Block 5: K1 forward sub [LCObyOH]
          double y1_5 = F1_5 - L_5_4 * y1_4;
          // Block 6: K1 forward sub [FixedOH]
          double y1_6 = F1_6 - L_6_4 * y1_4;
          double y1_7 = F1_7 - L_7_6 * y1_6;
          // Block 7: K1 forward sub [CH4]
          double y1_8 = F1_8;
          // Block 8: K1 forward sub [LCH4byCl]
          double y1_9 = F1_9 - L_9_8 * y1_8;
          // Block 9: K1 forward sub [FixedCl]
          double y1_10 = F1_10 - L_10_8 * y1_8;
          // Block 9: K1 backward sub [FixedCl]
          double K1_10 = y1_10 / U_10_10;
          // Block 8: K1 backward sub [LCH4byCl]
          double K1_9 = (y1_9 - U_9_10 * K1_10) / U_9_9;
          // Block 7: K1 backward sub [CH4]
          double K1_8 = y1_8 / U_8_8;
          // Block 1: K1 backward sub [PCOfromCH4, LCH4byOH]
          double K1_7 = (y1_7 - U_7_8 * K1_8) / U_7_7;
          // Block 6: K1 backward sub [FixedOH]
          double K1_6 = (y1_6 - U_6_8 * K1_8) / U_6_6;
          // Block 5: K1 backward sub [LCObyOH]
          double K1_5 = (y1_5 - U_5_6 * K1_6) / U_5_5;
          // Block 4: K1 backward sub [CO]
          double K1_4 = (y1_4 - U_4_6 * K1_6) / U_4_4;
          // Block 3: K1 backward sub [DummyCH4]
          double K1_3 = y1_3 / U_3_3;
          // Block 2: K1 backward sub [DummyNMVOC]
          double K1_2 = y1_2 / U_2_2;
          double K1_1 = (y1_1 - U_1_3 * K1_3) / U_1_1;
          // Block 0: K1 backward sub [PCOfromNMVOC]
          double K1_0 = (y1_0 - U_0_2 * K1_2) / U_0_0;

          // --- Stage 2 ---
          // Intermediate state Y2
          double Y2_0 = S_0 + K1_0;
          double Y2_1 = S_1 + K1_1;
          double Y2_2 = S_2 + K1_2;
          double Y2_3 = S_3 + K1_3;
          double Y2_4 = S_4 + K1_4;
          double Y2_5 = S_5 + K1_5;
          double Y2_6 = S_6 + K1_6;
          double Y2_7 = S_7 + K1_7;
          double Y2_8 = S_8 + K1_8;
          double Y2_9 = S_9 + K1_9;
          double Y2_10 = S_10 + K1_10;
          // Rate evaluation F2 at Y2
          double F2_0 = 38199.012000000002;
          double F2_1 = 4.2566445999999996e-15;
          double F2_2 = -38199.012000000002;
          double F2_3 = -4.2566445999999996e-15;
          double F2_4 = 38199.012000000002 - 7.3679649000000001e-14*Y2_4;
          double F2_5 = 7.3679649000000001e-14*Y2_4;
          double F2_6 = -6.6007061575166499e-15*Y2_8 - 7.3679649000000001e-14*Y2_4;
          double F2_7 = 6.6007061575166499e-15*Y2_8;
          double F2_8 = 0.0;
          double F2_9 = 1.0315008299507354e-13*Y2_8;
          double F2_10 = -1.0315008299507354e-13*Y2_8;
          // RHS for stage 2
          double rhs2_0 = F2_0 + (-1.0156171083877703 / dt) * K1_0;
          double rhs2_1 = F2_1 + (-1.0156171083877703 / dt) * K1_1;
          double rhs2_2 = F2_2 + (-1.0156171083877703 / dt) * K1_2;
          double rhs2_3 = F2_3 + (-1.0156171083877703 / dt) * K1_3;
          double rhs2_4 = F2_4 + (-1.0156171083877703 / dt) * K1_4;
          double rhs2_5 = F2_5 + (-1.0156171083877703 / dt) * K1_5;
          double rhs2_6 = F2_6 + (-1.0156171083877703 / dt) * K1_6;
          double rhs2_7 = F2_7 + (-1.0156171083877703 / dt) * K1_7;
          double rhs2_8 = F2_8 + (-1.0156171083877703 / dt) * K1_8;
          double rhs2_9 = F2_9 + (-1.0156171083877703 / dt) * K1_9;
          double rhs2_10 = F2_10 + (-1.0156171083877703 / dt) * K1_10;
          // Block 0: K2 forward sub [PCOfromNMVOC]
          double y2_0 = rhs2_0;
          // Block 1: K2 forward sub [PCOfromCH4, LCH4byOH]
          double y2_1 = rhs2_1;
          // Block 2: K2 forward sub [DummyNMVOC]
          double y2_2 = rhs2_2;
          // Block 3: K2 forward sub [DummyCH4]
          double y2_3 = rhs2_3;
          // Block 4: K2 forward sub [CO]
          double y2_4 = rhs2_4 - L_4_2 * y2_2 - L_4_3 * y2_3;
          // Block 5: K2 forward sub [LCObyOH]
          double y2_5 = rhs2_5 - L_5_4 * y2_4;
          // Block 6: K2 forward sub [FixedOH]
          double y2_6 = rhs2_6 - L_6_4 * y2_4;
          double y2_7 = rhs2_7 - L_7_6 * y2_6;
          // Block 7: K2 forward sub [CH4]
          double y2_8 = rhs2_8;
          // Block 8: K2 forward sub [LCH4byCl]
          double y2_9 = rhs2_9 - L_9_8 * y2_8;
          // Block 9: K2 forward sub [FixedCl]
          double y2_10 = rhs2_10 - L_10_8 * y2_8;
          // Block 9: K2 backward sub [FixedCl]
          double K2_10 = y2_10 / U_10_10;
          // Block 8: K2 backward sub [LCH4byCl]
          double K2_9 = (y2_9 - U_9_10 * K2_10) / U_9_9;
          // Block 7: K2 backward sub [CH4]
          double K2_8 = y2_8 / U_8_8;
          // Block 1: K2 backward sub [PCOfromCH4, LCH4byOH]
          double K2_7 = (y2_7 - U_7_8 * K2_8) / U_7_7;
          // Block 6: K2 backward sub [FixedOH]
          double K2_6 = (y2_6 - U_6_8 * K2_8) / U_6_6;
          // Block 5: K2 backward sub [LCObyOH]
          double K2_5 = (y2_5 - U_5_6 * K2_6) / U_5_5;
          // Block 4: K2 backward sub [CO]
          double K2_4 = (y2_4 - U_4_6 * K2_6) / U_4_4;
          // Block 3: K2 backward sub [DummyCH4]
          double K2_3 = y2_3 / U_3_3;
          // Block 2: K2 backward sub [DummyNMVOC]
          double K2_2 = y2_2 / U_2_2;
          double K2_1 = (y2_1 - U_1_3 * K2_3) / U_1_1;
          // Block 0: K2 backward sub [PCOfromNMVOC]
          double K2_0 = (y2_0 - U_0_2 * K2_2) / U_0_0;

          // --- Stage 3 ---
          // Intermediate state Y3
          double Y3_0 = S_0 + K1_0;
          double Y3_1 = S_1 + K1_1;
          double Y3_2 = S_2 + K1_2;
          double Y3_3 = S_3 + K1_3;
          double Y3_4 = S_4 + K1_4;
          double Y3_5 = S_5 + K1_5;
          double Y3_6 = S_6 + K1_6;
          double Y3_7 = S_7 + K1_7;
          double Y3_8 = S_8 + K1_8;
          double Y3_9 = S_9 + K1_9;
          double Y3_10 = S_10 + K1_10;
          // NewF=false: reuse F2 for stage 3
          // RHS for stage 3
          double rhs3_0 = F2_0 + (4.0759956452537702 / dt) * K1_0 + (9.20767942983308 / dt) * K2_0;
          double rhs3_1 = F2_1 + (4.0759956452537702 / dt) * K1_1 + (9.20767942983308 / dt) * K2_1;
          double rhs3_2 = F2_2 + (4.0759956452537702 / dt) * K1_2 + (9.20767942983308 / dt) * K2_2;
          double rhs3_3 = F2_3 + (4.0759956452537702 / dt) * K1_3 + (9.20767942983308 / dt) * K2_3;
          double rhs3_4 = F2_4 + (4.0759956452537702 / dt) * K1_4 + (9.20767942983308 / dt) * K2_4;
          double rhs3_5 = F2_5 + (4.0759956452537702 / dt) * K1_5 + (9.20767942983308 / dt) * K2_5;
          double rhs3_6 = F2_6 + (4.0759956452537702 / dt) * K1_6 + (9.20767942983308 / dt) * K2_6;
          double rhs3_7 = F2_7 + (4.0759956452537702 / dt) * K1_7 + (9.20767942983308 / dt) * K2_7;
          double rhs3_8 = F2_8 + (4.0759956452537702 / dt) * K1_8 + (9.20767942983308 / dt) * K2_8;
          double rhs3_9 = F2_9 + (4.0759956452537702 / dt) * K1_9 + (9.20767942983308 / dt) * K2_9;
          double rhs3_10 = F2_10 + (4.0759956452537702 / dt) * K1_10 + (9.20767942983308 / dt) * K2_10;
          // Block 0: K3 forward sub [PCOfromNMVOC]
          double y3_0 = rhs3_0;
          // Block 1: K3 forward sub [PCOfromCH4, LCH4byOH]
          double y3_1 = rhs3_1;
          // Block 2: K3 forward sub [DummyNMVOC]
          double y3_2 = rhs3_2;
          // Block 3: K3 forward sub [DummyCH4]
          double y3_3 = rhs3_3;
          // Block 4: K3 forward sub [CO]
          double y3_4 = rhs3_4 - L_4_2 * y3_2 - L_4_3 * y3_3;
          // Block 5: K3 forward sub [LCObyOH]
          double y3_5 = rhs3_5 - L_5_4 * y3_4;
          // Block 6: K3 forward sub [FixedOH]
          double y3_6 = rhs3_6 - L_6_4 * y3_4;
          double y3_7 = rhs3_7 - L_7_6 * y3_6;
          // Block 7: K3 forward sub [CH4]
          double y3_8 = rhs3_8;
          // Block 8: K3 forward sub [LCH4byCl]
          double y3_9 = rhs3_9 - L_9_8 * y3_8;
          // Block 9: K3 forward sub [FixedCl]
          double y3_10 = rhs3_10 - L_10_8 * y3_8;
          // Block 9: K3 backward sub [FixedCl]
          double K3_10 = y3_10 / U_10_10;
          // Block 8: K3 backward sub [LCH4byCl]
          double K3_9 = (y3_9 - U_9_10 * K3_10) / U_9_9;
          // Block 7: K3 backward sub [CH4]
          double K3_8 = y3_8 / U_8_8;
          // Block 1: K3 backward sub [PCOfromCH4, LCH4byOH]
          double K3_7 = (y3_7 - U_7_8 * K3_8) / U_7_7;
          // Block 6: K3 backward sub [FixedOH]
          double K3_6 = (y3_6 - U_6_8 * K3_8) / U_6_6;
          // Block 5: K3 backward sub [LCObyOH]
          double K3_5 = (y3_5 - U_5_6 * K3_6) / U_5_5;
          // Block 4: K3 backward sub [CO]
          double K3_4 = (y3_4 - U_4_6 * K3_6) / U_4_4;
          // Block 3: K3 backward sub [DummyCH4]
          double K3_3 = y3_3 / U_3_3;
          // Block 2: K3 backward sub [DummyNMVOC]
          double K3_2 = y3_2 / U_2_2;
          double K3_1 = (y3_1 - U_1_3 * K3_3) / U_1_1;
          // Block 0: K3 backward sub [PCOfromNMVOC]
          double K3_0 = (y3_0 - U_0_2 * K3_2) / U_0_0;

          // --- Solution update and error estimation ---
          double err_norm_sq = 0.0;
          {
              double Ynew_i = S_0 + K1_0 + 6.1697947043828245 * K2_0 + -0.42772256543218573 * K3_0;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(3)), Kokkos::fabs(Ynew_i));
              double sci = atol[0] + rtol[0] * ymax;
              double yerr_i = 0.5 * K1_0 + -2.9079558716805471 * K2_0 + 0.22354069897811571 * K3_0;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_1 + K1_1 + 6.1697947043828245 * K2_1 + -0.42772256543218573 * K3_1;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(2)), Kokkos::fabs(Ynew_i));
              double sci = atol[1] + rtol[1] * ymax;
              double yerr_i = 0.5 * K1_1 + -2.9079558716805471 * K2_1 + 0.22354069897811571 * K3_1;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_2 + K1_2 + 6.1697947043828245 * K2_2 + -0.42772256543218573 * K3_2;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(10)), Kokkos::fabs(Ynew_i));
              double sci = atol[2] + rtol[2] * ymax;
              double yerr_i = 0.5 * K1_2 + -2.9079558716805471 * K2_2 + 0.22354069897811571 * K3_2;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_3 + K1_3 + 6.1697947043828245 * K2_3 + -0.42772256543218573 * K3_3;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(9)), Kokkos::fabs(Ynew_i));
              double sci = atol[3] + rtol[3] * ymax;
              double yerr_i = 0.5 * K1_3 + -2.9079558716805471 * K2_3 + 0.22354069897811571 * K3_3;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_4 + K1_4 + 6.1697947043828245 * K2_4 + -0.42772256543218573 * K3_4;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(1)), Kokkos::fabs(Ynew_i));
              double sci = atol[4] + rtol[4] * ymax;
              double yerr_i = 0.5 * K1_4 + -2.9079558716805471 * K2_4 + 0.22354069897811571 * K3_4;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_5 + K1_5 + 6.1697947043828245 * K2_5 + -0.42772256543218573 * K3_5;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(6)), Kokkos::fabs(Ynew_i));
              double sci = atol[5] + rtol[5] * ymax;
              double yerr_i = 0.5 * K1_5 + -2.9079558716805471 * K2_5 + 0.22354069897811571 * K3_5;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_6 + K1_6 + 6.1697947043828245 * K2_6 + -0.42772256543218573 * K3_6;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(7)), Kokkos::fabs(Ynew_i));
              double sci = atol[6] + rtol[6] * ymax;
              double yerr_i = 0.5 * K1_6 + -2.9079558716805471 * K2_6 + 0.22354069897811571 * K3_6;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_7 + K1_7 + 6.1697947043828245 * K2_7 + -0.42772256543218573 * K3_7;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(4)), Kokkos::fabs(Ynew_i));
              double sci = atol[7] + rtol[7] * ymax;
              double yerr_i = 0.5 * K1_7 + -2.9079558716805471 * K2_7 + 0.22354069897811571 * K3_7;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_8 + K1_8 + 6.1697947043828245 * K2_8 + -0.42772256543218573 * K3_8;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(0)), Kokkos::fabs(Ynew_i));
              double sci = atol[8] + rtol[8] * ymax;
              double yerr_i = 0.5 * K1_8 + -2.9079558716805471 * K2_8 + 0.22354069897811571 * K3_8;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_9 + K1_9 + 6.1697947043828245 * K2_9 + -0.42772256543218573 * K3_9;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(5)), Kokkos::fabs(Ynew_i));
              double sci = atol[9] + rtol[9] * ymax;
              double yerr_i = 0.5 * K1_9 + -2.9079558716805471 * K2_9 + 0.22354069897811571 * K3_9;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_10 + K1_10 + 6.1697947043828245 * K2_10 + -0.42772256543218573 * K3_10;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(8)), Kokkos::fabs(Ynew_i));
              double sci = atol[10] + rtol[10] * ymax;
              double yerr_i = 0.5 * K1_10 + -2.9079558716805471 * K2_10 + 0.22354069897811571 * K3_10;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          double err_norm = Kokkos::sqrt(err_norm_sq / 11);
          err_norm = Kokkos::fmax(err_norm, 1.0e-10);

          // Step Size Control (order 3: exponent = 1/3 = 0.33333333333333331)
          double factor = safety / Kokkos::cbrt(err_norm);
          factor = Kokkos::fmax(min_shrink, Kokkos::fmin(factor, max_growth));

          if (err_norm <= 1.0) {
              state(3) += K1_0 + 6.1697947043828245 * K2_0 + -0.42772256543218573 * K3_0;
              state(2) += K1_1 + 6.1697947043828245 * K2_1 + -0.42772256543218573 * K3_1;
              state(10) += K1_2 + 6.1697947043828245 * K2_2 + -0.42772256543218573 * K3_2;
              state(9) += K1_3 + 6.1697947043828245 * K2_3 + -0.42772256543218573 * K3_3;
              state(1) += K1_4 + 6.1697947043828245 * K2_4 + -0.42772256543218573 * K3_4;
              state(6) += K1_5 + 6.1697947043828245 * K2_5 + -0.42772256543218573 * K3_5;
              state(7) += K1_6 + 6.1697947043828245 * K2_6 + -0.42772256543218573 * K3_6;
              state(4) += K1_7 + 6.1697947043828245 * K2_7 + -0.42772256543218573 * K3_7;
              state(0) += K1_8 + 6.1697947043828245 * K2_8 + -0.42772256543218573 * K3_8;
              state(5) += K1_9 + 6.1697947043828245 * K2_9 + -0.42772256543218573 * K3_9;
              state(8) += K1_10 + 6.1697947043828245 * K2_10 + -0.42772256543218573 * K3_10;
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
          const int NUM_SPECIES = 11;
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
          active[7] = true;
          active[8] = true;
          active[9] = true;
          active[10] = true;

          while (t < dt_total) {
          dt = Kokkos::min(dt, dt_total - t);
          const double inv_g_dt = 1.0 / (g * dt);

          // 0. Hoist state values into scalar registers
          // NOTE: State access uses permuted species ordering
          const double S_0 = state(3);
          const double S_1 = state(2);
          const double S_2 = state(10);
          const double S_3 = state(9);
          const double S_4 = state(1);
          const double S_5 = state(6);
          const double S_6 = state(7);
          const double S_7 = state(4);
          const double S_8 = state(0);
          const double S_9 = state(5);
          const double S_10 = state(8);

          // 1. Stage 1 Rates (F1)
          double F1_0 = 38199.012000000002;
          double F1_1 = 4.2566445999999996e-15;
          double F1_2 = -38199.012000000002;
          double F1_3 = -4.2566445999999996e-15;
          double F1_4 = 38199.012000000002 - 7.3679649000000001e-14*S_4;
          double F1_5 = 7.3679649000000001e-14*S_4;
          double F1_6 = -6.6007061575166499e-15*S_8 - 7.3679649000000001e-14*S_4;
          double F1_7 = 6.6007061575166499e-15*S_8;
          double F1_8 = 0.0;
          double F1_9 = 1.0315008299507354e-13*S_8;
          double F1_10 = -1.0315008299507354e-13*S_8;

          // 2. Evaluate importance and update active set
          active[0] = (Kokkos::fabs(F1_0) / (atol[0] + rtol[0] * Kokkos::fabs(state(3))) >= importance_threshold);
          active[1] = (Kokkos::fabs(F1_1) / (atol[1] + rtol[1] * Kokkos::fabs(state(2))) >= importance_threshold);
          active[2] = (Kokkos::fabs(F1_2) / (atol[2] + rtol[2] * Kokkos::fabs(state(10))) >= importance_threshold);
          active[3] = (Kokkos::fabs(F1_3) / (atol[3] + rtol[3] * Kokkos::fabs(state(9))) >= importance_threshold);
          active[4] = (Kokkos::fabs(F1_4) / (atol[4] + rtol[4] * Kokkos::fabs(state(1))) >= importance_threshold);
          active[5] = (Kokkos::fabs(F1_5) / (atol[5] + rtol[5] * Kokkos::fabs(state(6))) >= importance_threshold);
          active[6] = (Kokkos::fabs(F1_6) / (atol[6] + rtol[6] * Kokkos::fabs(state(7))) >= importance_threshold);
          active[7] = (Kokkos::fabs(F1_7) / (atol[7] + rtol[7] * Kokkos::fabs(state(4))) >= importance_threshold);
          active[8] = (Kokkos::fabs(F1_8) / (atol[8] + rtol[8] * Kokkos::fabs(state(0))) >= importance_threshold);
          active[9] = (Kokkos::fabs(F1_9) / (atol[9] + rtol[9] * Kokkos::fabs(state(5))) >= importance_threshold);
          active[10] = (Kokkos::fabs(F1_10) / (atol[10] + rtol[10] * Kokkos::fabs(state(8))) >= importance_threshold);

          // 3. Analytical Jacobian & Iteration Matrix W (identity for frozen species)
          double J_0_0 = -4.2566445999999996e-15;
          double J_1_1 = -38199.012000000002;
          double J_2_2 = -1.0315008299507354e-13*S_8;
          double J_2_10 = -1.0315008299507354e-13;
          double J_3_2 = 1.0315008299507354e-13*S_8;
          double J_3_10 = 1.0315008299507354e-13;
          double J_4_0 = 4.2566445999999996e-15;
          double J_5_5 = -6.6007061575166499e-15*S_8 - 7.3679649000000001e-14*S_4;
          double J_5_7 = -7.3679649000000001e-14;
          double J_5_10 = -6.6007061575166499e-15;
          double J_6_5 = 6.6007061575166499e-15*S_8;
          double J_6_10 = 6.6007061575166499e-15;
          double J_7_0 = 4.2566445999999996e-15;
          double J_7_1 = 38199.012000000002;
          double J_7_5 = -7.3679649000000001e-14*S_4;
          double J_7_7 = -7.3679649000000001e-14;
          double J_8_1 = 38199.012000000002;
          double J_9_5 = 7.3679649000000001e-14*S_4;
          double J_9_7 = 7.3679649000000001e-14;
          double W_0_0 = active[0] ? (inv_g_dt - J_0_0) : 1.0;
          double W_0_2 = 0.0;
          double W_1_1 = active[1] ? (inv_g_dt - J_1_1) : 1.0;
          double W_1_3 = 0.0;
          double W_2_2 = active[2] ? (inv_g_dt - J_2_2) : 1.0;
          double W_3_3 = active[3] ? inv_g_dt : 1.0;
          double W_4_2 = 0.0;
          double W_4_3 = 0.0;
          double W_4_4 = active[4] ? inv_g_dt : 1.0;
          double W_4_6 = 0.0;
          double W_5_4 = 0.0;
          double W_5_5 = active[5] ? (inv_g_dt - J_5_5) : 1.0;
          double W_5_6 = 0.0;
          double W_6_4 = 0.0;
          double W_6_6 = active[6] ? inv_g_dt : 1.0;
          double W_6_8 = 0.0;
          double W_7_6 = 0.0;
          double W_7_7 = active[7] ? (inv_g_dt - J_7_7) : 1.0;
          double W_7_8 = 0.0;
          double W_8_8 = active[8] ? inv_g_dt : 1.0;
          double W_9_8 = 0.0;
          double W_9_9 = active[9] ? inv_g_dt : 1.0;
          double W_9_10 = 0.0;
          double W_10_8 = 0.0;
          double W_10_10 = active[10] ? inv_g_dt : 1.0;

          // 4. Symbolic LU Factorization (conditional skip for frozen species)
          double U_0_0 = W_0_0;
          double U_0_2 = W_0_2;
          double U_1_1 = W_1_1;
          double U_1_3 = W_1_3;
          double U_2_2 = W_2_2;
          double L_4_2 = (W_4_2) / U_2_2;
          double U_3_3 = W_3_3;
          double L_4_3 = (W_4_3) / U_3_3;
          double U_4_4 = W_4_4;
          double U_4_6 = W_4_6;
          double L_5_4 = (W_5_4) / U_4_4;
          double L_6_4 = (W_6_4) / U_4_4;
          double U_5_5 = W_5_5;
          double U_5_6 = W_5_6 - L_5_4 * U_4_6;
          double U_6_6 = W_6_6 - L_6_4 * U_4_6;
          double U_6_8 = W_6_8;
          double L_7_6 = (W_7_6) / U_6_6;
          double U_7_7 = W_7_7;
          double U_7_8 = W_7_8 - L_7_6 * U_6_8;
          double U_8_8 = W_8_8;
          double L_9_8 = (W_9_8) / U_8_8;
          double L_10_8 = (W_10_8) / U_8_8;
          double U_9_9 = W_9_9;
          double U_9_10 = W_9_10;
          double U_10_10 = W_10_10;

          // --- Stage 1 ---
          // F1 already computed above (used for importance evaluation)
          // Block 0: K1 forward sub [PCOfromNMVOC]
          double y1_0 = active[0] ? (F1_0) : 0.0;
          // Block 1: K1 forward sub [PCOfromCH4, LCH4byOH]
          double y1_1 = active[1] ? (F1_1) : 0.0;
          // Block 2: K1 forward sub [DummyNMVOC]
          double y1_2 = active[2] ? (F1_2) : 0.0;
          // Block 3: K1 forward sub [DummyCH4]
          double y1_3 = active[3] ? (F1_3) : 0.0;
          // Block 4: K1 forward sub [CO]
          double y1_4 = active[4] ? (F1_4 - L_4_2 * y1_2 - L_4_3 * y1_3) : 0.0;
          // Block 5: K1 forward sub [LCObyOH]
          double y1_5 = active[5] ? (F1_5 - L_5_4 * y1_4) : 0.0;
          // Block 6: K1 forward sub [FixedOH]
          double y1_6 = active[6] ? (F1_6 - L_6_4 * y1_4) : 0.0;
          double y1_7 = active[7] ? (F1_7 - L_7_6 * y1_6) : 0.0;
          // Block 7: K1 forward sub [CH4]
          double y1_8 = active[8] ? (F1_8) : 0.0;
          // Block 8: K1 forward sub [LCH4byCl]
          double y1_9 = active[9] ? (F1_9 - L_9_8 * y1_8) : 0.0;
          // Block 9: K1 forward sub [FixedCl]
          double y1_10 = active[10] ? (F1_10 - L_10_8 * y1_8) : 0.0;

          // Block 9: K1 backward sub [FixedCl]
          double K1_10 = active[10] ? (y1_10 / U_10_10) : 0.0;
          // Block 8: K1 backward sub [LCH4byCl]
          double K1_9 = active[9] ? ((y1_9 - U_9_10 * K1_10) / U_9_9) : 0.0;
          // Block 7: K1 backward sub [CH4]
          double K1_8 = active[8] ? (y1_8 / U_8_8) : 0.0;
          // Block 1: K1 backward sub [PCOfromCH4, LCH4byOH]
          double K1_7 = active[7] ? ((y1_7 - U_7_8 * K1_8) / U_7_7) : 0.0;
          // Block 6: K1 backward sub [FixedOH]
          double K1_6 = active[6] ? ((y1_6 - U_6_8 * K1_8) / U_6_6) : 0.0;
          // Block 5: K1 backward sub [LCObyOH]
          double K1_5 = active[5] ? ((y1_5 - U_5_6 * K1_6) / U_5_5) : 0.0;
          // Block 4: K1 backward sub [CO]
          double K1_4 = active[4] ? ((y1_4 - U_4_6 * K1_6) / U_4_4) : 0.0;
          // Block 3: K1 backward sub [DummyCH4]
          double K1_3 = active[3] ? (y1_3 / U_3_3) : 0.0;
          // Block 2: K1 backward sub [DummyNMVOC]
          double K1_2 = active[2] ? (y1_2 / U_2_2) : 0.0;
          double K1_1 = active[1] ? ((y1_1 - U_1_3 * K1_3) / U_1_1) : 0.0;
          // Block 0: K1 backward sub [PCOfromNMVOC]
          double K1_0 = active[0] ? ((y1_0 - U_0_2 * K1_2) / U_0_0) : 0.0;


          // --- Stage 2 ---
          // Intermediate state Y2
          double Y2_0 = S_0 + K1_0;
          double Y2_1 = S_1 + K1_1;
          double Y2_2 = S_2 + K1_2;
          double Y2_3 = S_3 + K1_3;
          double Y2_4 = S_4 + K1_4;
          double Y2_5 = S_5 + K1_5;
          double Y2_6 = S_6 + K1_6;
          double Y2_7 = S_7 + K1_7;
          double Y2_8 = S_8 + K1_8;
          double Y2_9 = S_9 + K1_9;
          double Y2_10 = S_10 + K1_10;
          // Rate evaluation F2 at Y2
          double F2_0 = 38199.012000000002;
          double F2_1 = 4.2566445999999996e-15;
          double F2_2 = -38199.012000000002;
          double F2_3 = -4.2566445999999996e-15;
          double F2_4 = 38199.012000000002 - 7.3679649000000001e-14*Y2_4;
          double F2_5 = 7.3679649000000001e-14*Y2_4;
          double F2_6 = -6.6007061575166499e-15*Y2_8 - 7.3679649000000001e-14*Y2_4;
          double F2_7 = 6.6007061575166499e-15*Y2_8;
          double F2_8 = 0.0;
          double F2_9 = 1.0315008299507354e-13*Y2_8;
          double F2_10 = -1.0315008299507354e-13*Y2_8;
          // RHS for stage 2
          double rhs2_0 = F2_0 + (-1.0156171083877703 / dt) * K1_0;
          double rhs2_1 = F2_1 + (-1.0156171083877703 / dt) * K1_1;
          double rhs2_2 = F2_2 + (-1.0156171083877703 / dt) * K1_2;
          double rhs2_3 = F2_3 + (-1.0156171083877703 / dt) * K1_3;
          double rhs2_4 = F2_4 + (-1.0156171083877703 / dt) * K1_4;
          double rhs2_5 = F2_5 + (-1.0156171083877703 / dt) * K1_5;
          double rhs2_6 = F2_6 + (-1.0156171083877703 / dt) * K1_6;
          double rhs2_7 = F2_7 + (-1.0156171083877703 / dt) * K1_7;
          double rhs2_8 = F2_8 + (-1.0156171083877703 / dt) * K1_8;
          double rhs2_9 = F2_9 + (-1.0156171083877703 / dt) * K1_9;
          double rhs2_10 = F2_10 + (-1.0156171083877703 / dt) * K1_10;
          // Block 0: K2 forward sub [PCOfromNMVOC]
          double y2_0 = active[0] ? (rhs2_0) : 0.0;
          // Block 1: K2 forward sub [PCOfromCH4, LCH4byOH]
          double y2_1 = active[1] ? (rhs2_1) : 0.0;
          // Block 2: K2 forward sub [DummyNMVOC]
          double y2_2 = active[2] ? (rhs2_2) : 0.0;
          // Block 3: K2 forward sub [DummyCH4]
          double y2_3 = active[3] ? (rhs2_3) : 0.0;
          // Block 4: K2 forward sub [CO]
          double y2_4 = active[4] ? (rhs2_4 - L_4_2 * y2_2 - L_4_3 * y2_3) : 0.0;
          // Block 5: K2 forward sub [LCObyOH]
          double y2_5 = active[5] ? (rhs2_5 - L_5_4 * y2_4) : 0.0;
          // Block 6: K2 forward sub [FixedOH]
          double y2_6 = active[6] ? (rhs2_6 - L_6_4 * y2_4) : 0.0;
          double y2_7 = active[7] ? (rhs2_7 - L_7_6 * y2_6) : 0.0;
          // Block 7: K2 forward sub [CH4]
          double y2_8 = active[8] ? (rhs2_8) : 0.0;
          // Block 8: K2 forward sub [LCH4byCl]
          double y2_9 = active[9] ? (rhs2_9 - L_9_8 * y2_8) : 0.0;
          // Block 9: K2 forward sub [FixedCl]
          double y2_10 = active[10] ? (rhs2_10 - L_10_8 * y2_8) : 0.0;

          // Block 9: K2 backward sub [FixedCl]
          double K2_10 = active[10] ? (y2_10 / U_10_10) : 0.0;
          // Block 8: K2 backward sub [LCH4byCl]
          double K2_9 = active[9] ? ((y2_9 - U_9_10 * K2_10) / U_9_9) : 0.0;
          // Block 7: K2 backward sub [CH4]
          double K2_8 = active[8] ? (y2_8 / U_8_8) : 0.0;
          // Block 1: K2 backward sub [PCOfromCH4, LCH4byOH]
          double K2_7 = active[7] ? ((y2_7 - U_7_8 * K2_8) / U_7_7) : 0.0;
          // Block 6: K2 backward sub [FixedOH]
          double K2_6 = active[6] ? ((y2_6 - U_6_8 * K2_8) / U_6_6) : 0.0;
          // Block 5: K2 backward sub [LCObyOH]
          double K2_5 = active[5] ? ((y2_5 - U_5_6 * K2_6) / U_5_5) : 0.0;
          // Block 4: K2 backward sub [CO]
          double K2_4 = active[4] ? ((y2_4 - U_4_6 * K2_6) / U_4_4) : 0.0;
          // Block 3: K2 backward sub [DummyCH4]
          double K2_3 = active[3] ? (y2_3 / U_3_3) : 0.0;
          // Block 2: K2 backward sub [DummyNMVOC]
          double K2_2 = active[2] ? (y2_2 / U_2_2) : 0.0;
          double K2_1 = active[1] ? ((y2_1 - U_1_3 * K2_3) / U_1_1) : 0.0;
          // Block 0: K2 backward sub [PCOfromNMVOC]
          double K2_0 = active[0] ? ((y2_0 - U_0_2 * K2_2) / U_0_0) : 0.0;


          // --- Stage 3 ---
          // Intermediate state Y3
          double Y3_0 = S_0 + K1_0;
          double Y3_1 = S_1 + K1_1;
          double Y3_2 = S_2 + K1_2;
          double Y3_3 = S_3 + K1_3;
          double Y3_4 = S_4 + K1_4;
          double Y3_5 = S_5 + K1_5;
          double Y3_6 = S_6 + K1_6;
          double Y3_7 = S_7 + K1_7;
          double Y3_8 = S_8 + K1_8;
          double Y3_9 = S_9 + K1_9;
          double Y3_10 = S_10 + K1_10;
          // NewF=false: reuse F2 for stage 3
          // RHS for stage 3
          double rhs3_0 = F2_0 + (4.0759956452537702 / dt) * K1_0 + (9.20767942983308 / dt) * K2_0;
          double rhs3_1 = F2_1 + (4.0759956452537702 / dt) * K1_1 + (9.20767942983308 / dt) * K2_1;
          double rhs3_2 = F2_2 + (4.0759956452537702 / dt) * K1_2 + (9.20767942983308 / dt) * K2_2;
          double rhs3_3 = F2_3 + (4.0759956452537702 / dt) * K1_3 + (9.20767942983308 / dt) * K2_3;
          double rhs3_4 = F2_4 + (4.0759956452537702 / dt) * K1_4 + (9.20767942983308 / dt) * K2_4;
          double rhs3_5 = F2_5 + (4.0759956452537702 / dt) * K1_5 + (9.20767942983308 / dt) * K2_5;
          double rhs3_6 = F2_6 + (4.0759956452537702 / dt) * K1_6 + (9.20767942983308 / dt) * K2_6;
          double rhs3_7 = F2_7 + (4.0759956452537702 / dt) * K1_7 + (9.20767942983308 / dt) * K2_7;
          double rhs3_8 = F2_8 + (4.0759956452537702 / dt) * K1_8 + (9.20767942983308 / dt) * K2_8;
          double rhs3_9 = F2_9 + (4.0759956452537702 / dt) * K1_9 + (9.20767942983308 / dt) * K2_9;
          double rhs3_10 = F2_10 + (4.0759956452537702 / dt) * K1_10 + (9.20767942983308 / dt) * K2_10;
          // Block 0: K3 forward sub [PCOfromNMVOC]
          double y3_0 = active[0] ? (rhs3_0) : 0.0;
          // Block 1: K3 forward sub [PCOfromCH4, LCH4byOH]
          double y3_1 = active[1] ? (rhs3_1) : 0.0;
          // Block 2: K3 forward sub [DummyNMVOC]
          double y3_2 = active[2] ? (rhs3_2) : 0.0;
          // Block 3: K3 forward sub [DummyCH4]
          double y3_3 = active[3] ? (rhs3_3) : 0.0;
          // Block 4: K3 forward sub [CO]
          double y3_4 = active[4] ? (rhs3_4 - L_4_2 * y3_2 - L_4_3 * y3_3) : 0.0;
          // Block 5: K3 forward sub [LCObyOH]
          double y3_5 = active[5] ? (rhs3_5 - L_5_4 * y3_4) : 0.0;
          // Block 6: K3 forward sub [FixedOH]
          double y3_6 = active[6] ? (rhs3_6 - L_6_4 * y3_4) : 0.0;
          double y3_7 = active[7] ? (rhs3_7 - L_7_6 * y3_6) : 0.0;
          // Block 7: K3 forward sub [CH4]
          double y3_8 = active[8] ? (rhs3_8) : 0.0;
          // Block 8: K3 forward sub [LCH4byCl]
          double y3_9 = active[9] ? (rhs3_9 - L_9_8 * y3_8) : 0.0;
          // Block 9: K3 forward sub [FixedCl]
          double y3_10 = active[10] ? (rhs3_10 - L_10_8 * y3_8) : 0.0;

          // Block 9: K3 backward sub [FixedCl]
          double K3_10 = active[10] ? (y3_10 / U_10_10) : 0.0;
          // Block 8: K3 backward sub [LCH4byCl]
          double K3_9 = active[9] ? ((y3_9 - U_9_10 * K3_10) / U_9_9) : 0.0;
          // Block 7: K3 backward sub [CH4]
          double K3_8 = active[8] ? (y3_8 / U_8_8) : 0.0;
          // Block 1: K3 backward sub [PCOfromCH4, LCH4byOH]
          double K3_7 = active[7] ? ((y3_7 - U_7_8 * K3_8) / U_7_7) : 0.0;
          // Block 6: K3 backward sub [FixedOH]
          double K3_6 = active[6] ? ((y3_6 - U_6_8 * K3_8) / U_6_6) : 0.0;
          // Block 5: K3 backward sub [LCObyOH]
          double K3_5 = active[5] ? ((y3_5 - U_5_6 * K3_6) / U_5_5) : 0.0;
          // Block 4: K3 backward sub [CO]
          double K3_4 = active[4] ? ((y3_4 - U_4_6 * K3_6) / U_4_4) : 0.0;
          // Block 3: K3 backward sub [DummyCH4]
          double K3_3 = active[3] ? (y3_3 / U_3_3) : 0.0;
          // Block 2: K3 backward sub [DummyNMVOC]
          double K3_2 = active[2] ? (y3_2 / U_2_2) : 0.0;
          double K3_1 = active[1] ? ((y3_1 - U_1_3 * K3_3) / U_1_1) : 0.0;
          // Block 0: K3 backward sub [PCOfromNMVOC]
          double K3_0 = active[0] ? ((y3_0 - U_0_2 * K3_2) / U_0_0) : 0.0;


          // --- Solution update and error estimation ---
          double err_norm_sq = 0.0;
          {
              double Ynew_i = S_0 + K1_0 + 6.1697947043828245 * K2_0 + -0.42772256543218573 * K3_0;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(3)), Kokkos::fabs(Ynew_i));
              double sci = atol[0] + rtol[0] * ymax;
              double yerr_i = 0.5 * K1_0 + -2.9079558716805471 * K2_0 + 0.22354069897811571 * K3_0;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_1 + K1_1 + 6.1697947043828245 * K2_1 + -0.42772256543218573 * K3_1;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(2)), Kokkos::fabs(Ynew_i));
              double sci = atol[1] + rtol[1] * ymax;
              double yerr_i = 0.5 * K1_1 + -2.9079558716805471 * K2_1 + 0.22354069897811571 * K3_1;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_2 + K1_2 + 6.1697947043828245 * K2_2 + -0.42772256543218573 * K3_2;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(10)), Kokkos::fabs(Ynew_i));
              double sci = atol[2] + rtol[2] * ymax;
              double yerr_i = 0.5 * K1_2 + -2.9079558716805471 * K2_2 + 0.22354069897811571 * K3_2;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_3 + K1_3 + 6.1697947043828245 * K2_3 + -0.42772256543218573 * K3_3;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(9)), Kokkos::fabs(Ynew_i));
              double sci = atol[3] + rtol[3] * ymax;
              double yerr_i = 0.5 * K1_3 + -2.9079558716805471 * K2_3 + 0.22354069897811571 * K3_3;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_4 + K1_4 + 6.1697947043828245 * K2_4 + -0.42772256543218573 * K3_4;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(1)), Kokkos::fabs(Ynew_i));
              double sci = atol[4] + rtol[4] * ymax;
              double yerr_i = 0.5 * K1_4 + -2.9079558716805471 * K2_4 + 0.22354069897811571 * K3_4;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_5 + K1_5 + 6.1697947043828245 * K2_5 + -0.42772256543218573 * K3_5;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(6)), Kokkos::fabs(Ynew_i));
              double sci = atol[5] + rtol[5] * ymax;
              double yerr_i = 0.5 * K1_5 + -2.9079558716805471 * K2_5 + 0.22354069897811571 * K3_5;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_6 + K1_6 + 6.1697947043828245 * K2_6 + -0.42772256543218573 * K3_6;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(7)), Kokkos::fabs(Ynew_i));
              double sci = atol[6] + rtol[6] * ymax;
              double yerr_i = 0.5 * K1_6 + -2.9079558716805471 * K2_6 + 0.22354069897811571 * K3_6;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_7 + K1_7 + 6.1697947043828245 * K2_7 + -0.42772256543218573 * K3_7;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(4)), Kokkos::fabs(Ynew_i));
              double sci = atol[7] + rtol[7] * ymax;
              double yerr_i = 0.5 * K1_7 + -2.9079558716805471 * K2_7 + 0.22354069897811571 * K3_7;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_8 + K1_8 + 6.1697947043828245 * K2_8 + -0.42772256543218573 * K3_8;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(0)), Kokkos::fabs(Ynew_i));
              double sci = atol[8] + rtol[8] * ymax;
              double yerr_i = 0.5 * K1_8 + -2.9079558716805471 * K2_8 + 0.22354069897811571 * K3_8;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_9 + K1_9 + 6.1697947043828245 * K2_9 + -0.42772256543218573 * K3_9;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(5)), Kokkos::fabs(Ynew_i));
              double sci = atol[9] + rtol[9] * ymax;
              double yerr_i = 0.5 * K1_9 + -2.9079558716805471 * K2_9 + 0.22354069897811571 * K3_9;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_10 + K1_10 + 6.1697947043828245 * K2_10 + -0.42772256543218573 * K3_10;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(8)), Kokkos::fabs(Ynew_i));
              double sci = atol[10] + rtol[10] * ymax;
              double yerr_i = 0.5 * K1_10 + -2.9079558716805471 * K2_10 + 0.22354069897811571 * K3_10;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          double err_norm = Kokkos::sqrt(err_norm_sq / 11);
          err_norm = Kokkos::fmax(err_norm, 1.0e-10);

          // Step Size Control (order 3: exponent = 1/3 = 0.33333333333333331)
          double factor = safety / Kokkos::cbrt(err_norm);
          factor = Kokkos::fmax(min_shrink, Kokkos::fmin(factor, max_growth));

          if (err_norm <= 1.0) {
              if (active[0]) state(3) += K1_0 + 6.1697947043828245 * K2_0 + -0.42772256543218573 * K3_0;
              if (active[1]) state(2) += K1_1 + 6.1697947043828245 * K2_1 + -0.42772256543218573 * K3_1;
              if (active[2]) state(10) += K1_2 + 6.1697947043828245 * K2_2 + -0.42772256543218573 * K3_2;
              if (active[3]) state(9) += K1_3 + 6.1697947043828245 * K2_3 + -0.42772256543218573 * K3_3;
              if (active[4]) state(1) += K1_4 + 6.1697947043828245 * K2_4 + -0.42772256543218573 * K3_4;
              if (active[5]) state(6) += K1_5 + 6.1697947043828245 * K2_5 + -0.42772256543218573 * K3_5;
              if (active[6]) state(7) += K1_6 + 6.1697947043828245 * K2_6 + -0.42772256543218573 * K3_6;
              if (active[7]) state(4) += K1_7 + 6.1697947043828245 * K2_7 + -0.42772256543218573 * K3_7;
              if (active[8]) state(0) += K1_8 + 6.1697947043828245 * K2_8 + -0.42772256543218573 * K3_8;
              if (active[9]) state(5) += K1_9 + 6.1697947043828245 * K2_9 + -0.42772256543218573 * K3_9;
              if (active[10]) state(8) += K1_10 + 6.1697947043828245 * K2_10 + -0.42772256543218573 * K3_10;
              t += dt;
              dt *= factor;
          } else {
              dt *= factor;
          }
          } // end while (t < dt_total)
      }
  };
}
