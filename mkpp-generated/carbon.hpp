#pragma once
#include <Kokkos_Core.hpp>
// Generated solver for carbon
// SZA Workload Sorted: true
namespace mkpp {
// Pure Kokkos abstractions (no raw pragmas allowed)
// Bidirectional Host Interface (Zero-Copy)
using concentrations_view_t = Kokkos::View<double****, Kokkos::LayoutLeft, Kokkos::MemoryUnmanaged>;
template <typename DeviceType>
struct SolverKernels {
    template <class StateView, class RateView>
    KOKKOS_INLINE_FUNCTION
    void compute_rates(const StateView& state, RateView& F_block) const {
        F_block(0) = 0.0;
        F_block(1) = 38199.012000000002;
        F_block(2) = 4.2566445999999996e-15;
        F_block(3) = 38199.012000000002;
        F_block(4) = 6.6007061575166499e-15;
        F_block(5) = 1.0315008299507354e-13;
        F_block(6) = 7.3679649000000001e-14;
        F_block(7) = -8.0280355157516646e-14;
        F_block(8) = -1.0315008299507354e-13;
        F_block(9) = -4.2566445999999996e-15;
        F_block(10) = -38199.012000000002;
    }

    template <class StateView, class JacView>
    KOKKOS_INLINE_FUNCTION
    void compute_jacobian(const StateView& state, JacView& J_block) const {
        J_block(1, 1) = -7.3679649000000001e-14;
        J_block(1, 7) = -7.3679649000000001e-14;
        J_block(1, 9) = 4.2566445999999996e-15;
        J_block(1, 10) = 38199.012000000002;
        J_block(2, 9) = 4.2566445999999996e-15;
        J_block(3, 10) = 38199.012000000002;
        J_block(4, 0) = 6.6007061575166499e-15;
        J_block(4, 7) = 6.6007061575166499e-15;
        J_block(5, 0) = 1.0315008299507354e-13;
        J_block(5, 8) = 1.0315008299507354e-13;
        J_block(6, 1) = 7.3679649000000001e-14;
        J_block(6, 7) = 7.3679649000000001e-14;
        J_block(7, 0) = -6.6007061575166499e-15;
        J_block(7, 1) = -7.3679649000000001e-14;
        J_block(7, 7) = -8.0280355157516646e-14;
        J_block(8, 0) = -1.0315008299507354e-13;
        J_block(8, 8) = -1.0315008299507354e-13;
        J_block(9, 9) = -4.2566445999999996e-15;
        J_block(10, 10) = -38199.012000000002;
    }

    template <class StateView, class JacView>
    KOKKOS_INLINE_FUNCTION
    void compute_adjoint(const StateView& state, JacView& J_adj_block) const {
        J_adj_block(0, 4) = 6.6007061575166499e-15;
        J_adj_block(0, 5) = 1.0315008299507354e-13;
        J_adj_block(0, 7) = -6.6007061575166499e-15;
        J_adj_block(0, 8) = -1.0315008299507354e-13;
        J_adj_block(1, 1) = -7.3679649000000001e-14;
        J_adj_block(1, 6) = 7.3679649000000001e-14;
        J_adj_block(1, 7) = -7.3679649000000001e-14;
        J_adj_block(7, 1) = -7.3679649000000001e-14;
        J_adj_block(7, 4) = 6.6007061575166499e-15;
        J_adj_block(7, 6) = 7.3679649000000001e-14;
        J_adj_block(7, 7) = -8.0280355157516646e-14;
        J_adj_block(8, 5) = 1.0315008299507354e-13;
        J_adj_block(8, 8) = -1.0315008299507354e-13;
        J_adj_block(9, 1) = 4.2566445999999996e-15;
        J_adj_block(9, 2) = 4.2566445999999996e-15;
        J_adj_block(9, 9) = -4.2566445999999996e-15;
        J_adj_block(10, 1) = 38199.012000000002;
        J_adj_block(10, 3) = 38199.012000000002;
        J_adj_block(10, 10) = -38199.012000000002;
    }

    template <class StateView, class DeltaView, class RateView>
    KOKKOS_INLINE_FUNCTION
    void compute_tlm(const StateView& state, const DeltaView& delta_C, RateView& dF_block) const {
        dF_block(0) = 0.0;
        dF_block(1) = 0.0;
        dF_block(1) += (-7.3679649000000001e-14) * delta_C(1);
        dF_block(1) += (-7.3679649000000001e-14) * delta_C(7);
        dF_block(1) += (4.2566445999999996e-15) * delta_C(9);
        dF_block(1) += (38199.012000000002) * delta_C(10);
        dF_block(2) = 0.0;
        dF_block(2) += (4.2566445999999996e-15) * delta_C(9);
        dF_block(3) = 0.0;
        dF_block(3) += (38199.012000000002) * delta_C(10);
        dF_block(4) = 0.0;
        dF_block(4) += (6.6007061575166499e-15) * delta_C(0);
        dF_block(4) += (6.6007061575166499e-15) * delta_C(7);
        dF_block(5) = 0.0;
        dF_block(5) += (1.0315008299507354e-13) * delta_C(0);
        dF_block(5) += (1.0315008299507354e-13) * delta_C(8);
        dF_block(6) = 0.0;
        dF_block(6) += (7.3679649000000001e-14) * delta_C(1);
        dF_block(6) += (7.3679649000000001e-14) * delta_C(7);
        dF_block(7) = 0.0;
        dF_block(7) += (-6.6007061575166499e-15) * delta_C(0);
        dF_block(7) += (-7.3679649000000001e-14) * delta_C(1);
        dF_block(7) += (-8.0280355157516646e-14) * delta_C(7);
        dF_block(8) = 0.0;
        dF_block(8) += (-1.0315008299507354e-13) * delta_C(0);
        dF_block(8) += (-1.0315008299507354e-13) * delta_C(8);
        dF_block(9) = 0.0;
        dF_block(9) += (-4.2566445999999996e-15) * delta_C(9);
        dF_block(10) = 0.0;
        dF_block(10) += (-38199.012000000002) * delta_C(10);
    }

    template <class StateView, class MassView>
    KOKKOS_INLINE_FUNCTION
    void project_mass_conservation(StateView& C_projected, const StateView& C,
                                   const MassView& m_0) const {
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

    template <class StateView>
    KOKKOS_INLINE_FUNCTION
    void integrate(double dt, StateView& state) const {
        const int NUM_SPECIES = 11;
        const double g = 1.70710678118654752440;
        const double ros_A0 = 1.0 / g;
        const double ros_C0 = -2.0 / g;
        const double ros_M0 = 3.0 / (2.0 * g);
        const double ros_M1 = 1.0 / (2.0 * g);
        const double inv_g_dt = 1.0 / (g * dt);

        // 1. Stage 1 Rates (F1)
        double F1_0 = 0.0;
        double F1_1 = 38199.012000000002;
        double F1_2 = 4.2566445999999996e-15;
        double F1_3 = 38199.012000000002;
        double F1_4 = 6.6007061575166499e-15;
        double F1_5 = 1.0315008299507354e-13;
        double F1_6 = 7.3679649000000001e-14;
        double F1_7 = -8.0280355157516646e-14;
        double F1_8 = -1.0315008299507354e-13;
        double F1_9 = -4.2566445999999996e-15;
        double F1_10 = -38199.012000000002;

        // 2. Analytical Jacobian & Iteration Matrix W = inv_g_dt*I - J
        double J_1_1 = -7.3679649000000001e-14;
        double J_1_7 = -7.3679649000000001e-14;
        double J_1_9 = 4.2566445999999996e-15;
        double J_1_10 = 38199.012000000002;
        double J_2_9 = 4.2566445999999996e-15;
        double J_3_10 = 38199.012000000002;
        double J_4_0 = 6.6007061575166499e-15;
        double J_4_7 = 6.6007061575166499e-15;
        double J_5_0 = 1.0315008299507354e-13;
        double J_5_8 = 1.0315008299507354e-13;
        double J_6_1 = 7.3679649000000001e-14;
        double J_6_7 = 7.3679649000000001e-14;
        double J_7_0 = -6.6007061575166499e-15;
        double J_7_1 = -7.3679649000000001e-14;
        double J_7_7 = -8.0280355157516646e-14;
        double J_8_0 = -1.0315008299507354e-13;
        double J_8_8 = -1.0315008299507354e-13;
        double J_9_9 = -4.2566445999999996e-15;
        double J_10_10 = -38199.012000000002;
        double W_0_0 = inv_g_dt;
        double W_1_1 = inv_g_dt - J_1_1;
        double W_1_7 = -J_1_7;
        double W_1_9 = -J_1_9;
        double W_1_10 = -J_1_10;
        double W_2_2 = inv_g_dt;
        double W_2_9 = -J_2_9;
        double W_3_3 = inv_g_dt;
        double W_3_10 = -J_3_10;
        double W_4_0 = -J_4_0;
        double W_4_4 = inv_g_dt;
        double W_4_7 = -J_4_7;
        double W_5_0 = -J_5_0;
        double W_5_5 = inv_g_dt;
        double W_5_8 = -J_5_8;
        double W_6_1 = -J_6_1;
        double W_6_6 = inv_g_dt;
        double W_6_7 = -J_6_7;
        double W_7_0 = -J_7_0;
        double W_7_1 = -J_7_1;
        double W_7_7 = inv_g_dt - J_7_7;
        double W_8_0 = -J_8_0;
        double W_8_8 = inv_g_dt - J_8_8;
        double W_9_9 = inv_g_dt - J_9_9;
        double W_10_10 = inv_g_dt - J_10_10;

        // 3. Symbolic Doolittle Sparse LU Factorization
        double U_0_0 = W_0_0;
        double L_4_0 = (W_4_0) / U_0_0;
        double L_5_0 = (W_5_0) / U_0_0;
        double L_7_0 = (W_7_0) / U_0_0;
        double L_8_0 = (W_8_0) / U_0_0;
        double U_1_1 = W_1_1;
        double U_1_7 = W_1_7;
        double U_1_9 = W_1_9;
        double U_1_10 = W_1_10;
        double L_6_1 = (W_6_1) / U_1_1;
        double L_7_1 = (W_7_1) / U_1_1;
        double U_2_2 = W_2_2;
        double U_2_9 = W_2_9;
        double U_3_3 = W_3_3;
        double U_3_10 = W_3_10;
        double U_4_4 = W_4_4;
        double U_4_7 = W_4_7;
        double U_5_5 = W_5_5;
        double U_5_8 = W_5_8;
        double U_6_6 = W_6_6;
        double U_6_7 = W_6_7 - L_6_1 * U_1_7;
        double U_6_9 = 0.0 - L_6_1 * U_1_9;
        double U_6_10 = 0.0 - L_6_1 * U_1_10;
        double U_7_7 = W_7_7 - L_7_1 * U_1_7;
        double U_7_9 = 0.0 - L_7_1 * U_1_9;
        double U_7_10 = 0.0 - L_7_1 * U_1_10;
        double U_8_8 = W_8_8;
        double U_9_9 = W_9_9;
        double U_10_10 = W_10_10;

        // 4. Forward & Backward Substitution for Stage K1
        double y1_0 = F1_0;
        double y1_1 = F1_1;
        double y1_2 = F1_2;
        double y1_3 = F1_3;
        double y1_4 = F1_4 - L_4_0 * y1_0;
        double y1_5 = F1_5 - L_5_0 * y1_0;
        double y1_6 = F1_6 - L_6_1 * y1_1;
        double y1_7 = F1_7 - L_7_0 * y1_0 - L_7_1 * y1_1;
        double y1_8 = F1_8 - L_8_0 * y1_0;
        double y1_9 = F1_9;
        double y1_10 = F1_10;
        double K1_0 = F1_10;
        double K1_1 = F1_10;
        double K1_2 = F1_10;
        double K1_3 = F1_10;
        double K1_4 = F1_10;
        double K1_5 = F1_10;
        double K1_6 = F1_10;
        double K1_7 = F1_10;
        double K1_8 = F1_10;
        double K1_9 = F1_10;
        double K1_10 = F1_10;

        // 5. Fused Intermediate State Ynew
        double Ynew_0 = state(0) + ros_A0 * K1_0;
        double Ynew_1 = state(1) + ros_A0 * K1_1;
        double Ynew_2 = state(2) + ros_A0 * K1_2;
        double Ynew_3 = state(3) + ros_A0 * K1_3;
        double Ynew_4 = state(4) + ros_A0 * K1_4;
        double Ynew_5 = state(5) + ros_A0 * K1_5;
        double Ynew_6 = state(6) + ros_A0 * K1_6;
        double Ynew_7 = state(7) + ros_A0 * K1_7;
        double Ynew_8 = state(8) + ros_A0 * K1_8;
        double Ynew_9 = state(9) + ros_A0 * K1_9;
        double Ynew_10 = state(10) + ros_A0 * K1_10;

        // 6. Stage 2 Rates (F2) & Substitution for Stage K2
        double F2_0 = 0.0;
        double rhs2_0 = F2_0 + (ros_C0 / dt) * K1_0;
        double F2_1 = 38199.012000000002;
        double rhs2_1 = F2_1 + (ros_C0 / dt) * K1_1;
        double F2_2 = 4.2566445999999996e-15;
        double rhs2_2 = F2_2 + (ros_C0 / dt) * K1_2;
        double F2_3 = 38199.012000000002;
        double rhs2_3 = F2_3 + (ros_C0 / dt) * K1_3;
        double F2_4 = 6.6007061575166499e-15;
        double rhs2_4 = F2_4 + (ros_C0 / dt) * K1_4;
        double F2_5 = 1.0315008299507354e-13;
        double rhs2_5 = F2_5 + (ros_C0 / dt) * K1_5;
        double F2_6 = 7.3679649000000001e-14;
        double rhs2_6 = F2_6 + (ros_C0 / dt) * K1_6;
        double F2_7 = -8.0280355157516646e-14;
        double rhs2_7 = F2_7 + (ros_C0 / dt) * K1_7;
        double F2_8 = -1.0315008299507354e-13;
        double rhs2_8 = F2_8 + (ros_C0 / dt) * K1_8;
        double F2_9 = -4.2566445999999996e-15;
        double rhs2_9 = F2_9 + (ros_C0 / dt) * K1_9;
        double F2_10 = -38199.012000000002;
        double rhs2_10 = F2_10 + (ros_C0 / dt) * K1_10;
        double y2_0 = rhs2_0;
        double y2_1 = rhs2_1;
        double y2_2 = rhs2_2;
        double y2_3 = rhs2_3;
        double y2_4 = rhs2_4 - L_4_0 * y2_0;
        double y2_5 = rhs2_5 - L_5_0 * y2_0;
        double y2_6 = rhs2_6 - L_6_1 * y2_1;
        double y2_7 = rhs2_7 - L_7_0 * y2_0 - L_7_1 * y2_1;
        double y2_8 = rhs2_8 - L_8_0 * y2_0;
        double y2_9 = rhs2_9;
        double y2_10 = rhs2_10;
        double K2_0 = y2_0 / U_0_0;
        double K2_1 = (y2_1 - U_1_7 * K2_7 - U_1_9 * K2_9 - U_1_10 * K2_10) / U_1_1;
        double K2_2 = (y2_2 - U_2_9 * K2_9) / U_2_2;
        double K2_3 = (y2_3 - U_3_10 * K2_10) / U_3_3;
        double K2_4 = (y2_4 - U_4_7 * K2_7) / U_4_4;
        double K2_5 = (y2_5 - U_5_8 * K2_8) / U_5_5;
        double K2_6 = (y2_6 - U_6_7 * K2_7 - U_6_9 * K2_9 - U_6_10 * K2_10) / U_6_6;
        double K2_7 = (y2_7 - U_7_9 * K2_9 - U_7_10 * K2_10) / U_7_7;
        double K2_8 = y2_8 / U_8_8;
        double K2_9 = y2_9 / U_9_9;
        double K2_10 = y2_10 / U_10_10;

        // 7. Final Fused State Update
        state(0) += ros_M0 * K1_0 + ros_M1 * K2_0;
        state(1) += ros_M0 * K1_1 + ros_M1 * K2_1;
        state(2) += ros_M0 * K1_2 + ros_M1 * K2_2;
        state(3) += ros_M0 * K1_3 + ros_M1 * K2_3;
        state(4) += ros_M0 * K1_4 + ros_M1 * K2_4;
        state(5) += ros_M0 * K1_5 + ros_M1 * K2_5;
        state(6) += ros_M0 * K1_6 + ros_M1 * K2_6;
        state(7) += ros_M0 * K1_7 + ros_M1 * K2_7;
        state(8) += ros_M0 * K1_8 + ros_M1 * K2_8;
        state(9) += ros_M0 * K1_9 + ros_M1 * K2_9;
        state(10) += ros_M0 * K1_10 + ros_M1 * K2_10;
    }
};
}  // namespace mkpp
