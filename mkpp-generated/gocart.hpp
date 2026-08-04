#pragma once
#include <Kokkos_Core.hpp>
// Generated solver for gocart
// SZA Workload Sorted: true
// Hysteresis/Spline Continuous Transition: true
namespace mkpp {
// Pure Kokkos abstractions (no raw pragmas allowed)
// Bidirectional Host Interface (Zero-Copy)
using concentrations_view_t = Kokkos::View<double****, Kokkos::LayoutLeft, Kokkos::MemoryUnmanaged>;
template <typename DeviceType>
struct SolverKernels {
    template <class StateView, class RateView>
    KOKKOS_INLINE_FUNCTION
    void compute_rates(const StateView& state, RateView& F_block) const {
        F_block(0) = -5.0442046141041832e-12 * state(3) * state(0) +
                     2.0000000000000002e-5 * state(2) -
                     3.3000000000000001e-12 * state(0) * state(4);
        F_block(1) = -3.3571944693753379e-14 * state(3) * state(1);
        F_block(2) =
            -0.0025000000000000001 * state(2) * state(4) - 1.0000000000000001e-5 * state(2);
        F_block(3) = -3.3571944693753379e-14 * state(3) * state(1) -
                     5.0442046141041832e-12 * state(3) * state(0);
        F_block(4) = 3.3571944693753379e-14 * state(3) * state(1) +
                     5.0442046141041832e-12 * state(3) * state(0) -
                     2.5000000000000001e-5 * state(10) * state(4) -
                     2.5000000000000001e-5 * state(11) * state(4) -
                     2.5000000000000001e-5 * state(12) * state(4) -
                     2.5000000000000001e-5 * state(13) * state(4) -
                     2.5000000000000001e-5 * state(14) * state(4) -
                     0.0025000000000000001 * state(2) * state(4) -
                     3.3000000000000001e-12 * state(0) * state(4) -
                     0.00025000000000000001 * state(4) * state(15) -
                     0.00025000000000000001 * state(4) * state(16) -
                     0.00025000000000000001 * state(4) * state(17) -
                     0.00025000000000000001 * state(4) * state(18) -
                     0.00025000000000000001 * state(4) * state(19);
        F_block(5) = 2.5000000000000001e-5 * state(10) * state(4) +
                     2.5000000000000001e-5 * state(11) * state(4) +
                     2.5000000000000001e-5 * state(12) * state(4) +
                     2.5000000000000001e-5 * state(13) * state(4) +
                     2.5000000000000001e-5 * state(14) * state(4) +
                     0.0025000000000000001 * state(2) * state(4) -
                     1.0 * state(20) * state(21) * state(5) * Rate_27 +
                     3.3000000000000001e-12 * state(0) * state(4) +
                     0.00025000000000000001 * state(4) * state(15) +
                     0.00025000000000000001 * state(4) * state(16) +
                     0.00025000000000000001 * state(4) * state(17) +
                     0.00025000000000000001 * state(4) * state(18) +
                     0.00025000000000000001 * state(4) * state(19);
        F_block(6) = -5.0000000000000004e-6 * state(6);
        F_block(7) = 5.0000000000000004e-6 * state(6);
        F_block(8) = -5.0000000000000004e-6 * state(8);
        F_block(9) = 5.0000000000000004e-6 * state(8);
        F_block(10) = 0.0;
        F_block(11) = 0.0;
        F_block(12) = 0.0;
        F_block(13) = 0.0;
        F_block(14) = 0.0;
        F_block(15) = 0.0;
        F_block(16) = 0.0;
        F_block(17) = 0.0;
        F_block(18) = 0.0;
        F_block(19) = 0.0;
        F_block(20) = -0.025000000000000001 * state(10) * state(20) -
                      0.025000000000000001 * state(11) * state(20) -
                      0.025000000000000001 * state(12) * state(20) -
                      0.025000000000000001 * state(13) * state(20) -
                      0.025000000000000001 * state(14) * state(20) -
                      1.0 * state(20) * state(21) * state(5) * Rate_27 -
                      0.025000000000000001 * state(20) * state(15) -
                      0.025000000000000001 * state(20) * state(16) -
                      0.025000000000000001 * state(20) * state(17) -
                      0.025000000000000001 * state(20) * state(18) -
                      0.025000000000000001 * state(20) * state(19);
        F_block(21) = -1.0 * state(20) * state(21) * state(5) * Rate_27;
        F_block(22) = 1.0 * state(20) * state(21) * state(5) * Rate_27;
        F_block(23) = 0.025000000000000001 * state(10) * state(20) +
                      0.025000000000000001 * state(13) * state(20) +
                      1.0 * state(20) * state(21) * state(5) * Rate_27 +
                      0.025000000000000001 * state(20) * state(16) +
                      0.025000000000000001 * state(20) * state(19);
        F_block(24) = 0.025000000000000001 * state(11) * state(20) +
                      0.025000000000000001 * state(14) * state(20) +
                      0.025000000000000001 * state(20) * state(17);
        F_block(25) = 0.025000000000000001 * state(12) * state(20) +
                      0.025000000000000001 * state(20) * state(15) +
                      0.025000000000000001 * state(20) * state(18);
    }

    template <class StateView, class JacView>
    KOKKOS_INLINE_FUNCTION
    void compute_jacobian(const StateView& state, JacView& J_block) const {
        J_block(0, 0) = -5.0442046141041832e-12 * state(3) - 3.3000000000000001e-12 * state(4);
        J_block(0, 2) = 2.0000000000000002e-5;
        J_block(0, 3) = -5.0442046141041832e-12 * state(0);
        J_block(0, 4) = -3.3000000000000001e-12 * state(0);
        J_block(1, 1) = -3.3571944693753379e-14 * state(3);
        J_block(1, 3) = -3.3571944693753379e-14 * state(1);
        J_block(2, 2) = -0.0025000000000000001 * state(4) - 1.0000000000000001e-5;
        J_block(2, 4) = -0.0025000000000000001 * state(2);
        J_block(3, 0) = -5.0442046141041832e-12 * state(3);
        J_block(3, 1) = -3.3571944693753379e-14 * state(3);
        J_block(3, 3) = -3.3571944693753379e-14 * state(1) - 5.0442046141041832e-12 * state(0);
        J_block(4, 0) = 5.0442046141041832e-12 * state(3) - 3.3000000000000001e-12 * state(4);
        J_block(4, 1) = 3.3571944693753379e-14 * state(3);
        J_block(4, 2) = -0.0025000000000000001 * state(4);
        J_block(4, 3) = 3.3571944693753379e-14 * state(1) + 5.0442046141041832e-12 * state(0);
        J_block(4, 4) = -2.5000000000000001e-5 * state(10) - 2.5000000000000001e-5 * state(11) -
                        2.5000000000000001e-5 * state(12) - 2.5000000000000001e-5 * state(13) -
                        2.5000000000000001e-5 * state(14) - 0.0025000000000000001 * state(2) -
                        3.3000000000000001e-12 * state(0) - 0.00025000000000000001 * state(15) -
                        0.00025000000000000001 * state(16) - 0.00025000000000000001 * state(17) -
                        0.00025000000000000001 * state(18) - 0.00025000000000000001 * state(19);
        J_block(4, 10) = -2.5000000000000001e-5 * state(4);
        J_block(4, 11) = -2.5000000000000001e-5 * state(4);
        J_block(4, 12) = -2.5000000000000001e-5 * state(4);
        J_block(4, 13) = -2.5000000000000001e-5 * state(4);
        J_block(4, 14) = -2.5000000000000001e-5 * state(4);
        J_block(4, 15) = -0.00025000000000000001 * state(4);
        J_block(4, 16) = -0.00025000000000000001 * state(4);
        J_block(4, 17) = -0.00025000000000000001 * state(4);
        J_block(4, 18) = -0.00025000000000000001 * state(4);
        J_block(4, 19) = -0.00025000000000000001 * state(4);
        J_block(5, 0) = 3.3000000000000001e-12 * state(4);
        J_block(5, 2) = 0.0025000000000000001 * state(4);
        J_block(5, 4) = 2.5000000000000001e-5 * state(10) + 2.5000000000000001e-5 * state(11) +
                        2.5000000000000001e-5 * state(12) + 2.5000000000000001e-5 * state(13) +
                        2.5000000000000001e-5 * state(14) + 0.0025000000000000001 * state(2) +
                        3.3000000000000001e-12 * state(0) + 0.00025000000000000001 * state(15) +
                        0.00025000000000000001 * state(16) + 0.00025000000000000001 * state(17) +
                        0.00025000000000000001 * state(18) + 0.00025000000000000001 * state(19);
        J_block(5, 5) = -1.0 * state(20) * state(21) * Rate_27;
        J_block(5, 10) = 2.5000000000000001e-5 * state(4);
        J_block(5, 11) = 2.5000000000000001e-5 * state(4);
        J_block(5, 12) = 2.5000000000000001e-5 * state(4);
        J_block(5, 13) = 2.5000000000000001e-5 * state(4);
        J_block(5, 14) = 2.5000000000000001e-5 * state(4);
        J_block(5, 15) = 0.00025000000000000001 * state(4);
        J_block(5, 16) = 0.00025000000000000001 * state(4);
        J_block(5, 17) = 0.00025000000000000001 * state(4);
        J_block(5, 18) = 0.00025000000000000001 * state(4);
        J_block(5, 19) = 0.00025000000000000001 * state(4);
        J_block(5, 20) = -1.0 * state(21) * state(5) * Rate_27;
        J_block(5, 21) = -1.0 * state(20) * state(5) * Rate_27;
        J_block(6, 6) = -5.0000000000000004e-6;
        J_block(7, 6) = 5.0000000000000004e-6;
        J_block(8, 8) = -5.0000000000000004e-6;
        J_block(9, 8) = 5.0000000000000004e-6;
        J_block(20, 5) = -1.0 * state(20) * state(21) * Rate_27;
        J_block(20, 10) = -0.025000000000000001 * state(20);
        J_block(20, 11) = -0.025000000000000001 * state(20);
        J_block(20, 12) = -0.025000000000000001 * state(20);
        J_block(20, 13) = -0.025000000000000001 * state(20);
        J_block(20, 14) = -0.025000000000000001 * state(20);
        J_block(20, 15) = -0.025000000000000001 * state(20);
        J_block(20, 16) = -0.025000000000000001 * state(20);
        J_block(20, 17) = -0.025000000000000001 * state(20);
        J_block(20, 18) = -0.025000000000000001 * state(20);
        J_block(20, 19) = -0.025000000000000001 * state(20);
        J_block(20, 20) = -0.025000000000000001 * state(10) - 0.025000000000000001 * state(11) -
                          0.025000000000000001 * state(12) - 0.025000000000000001 * state(13) -
                          0.025000000000000001 * state(14) - 1.0 * state(21) * state(5) * Rate_27 -
                          0.025000000000000001 * state(15) - 0.025000000000000001 * state(16) -
                          0.025000000000000001 * state(17) - 0.025000000000000001 * state(18) -
                          0.025000000000000001 * state(19);
        J_block(20, 21) = -1.0 * state(20) * state(5) * Rate_27;
        J_block(21, 5) = -1.0 * state(20) * state(21) * Rate_27;
        J_block(21, 20) = -1.0 * state(21) * state(5) * Rate_27;
        J_block(21, 21) = -1.0 * state(20) * state(5) * Rate_27;
        J_block(22, 5) = 1.0 * state(20) * state(21) * Rate_27;
        J_block(22, 20) = 1.0 * state(21) * state(5) * Rate_27;
        J_block(22, 21) = 1.0 * state(20) * state(5) * Rate_27;
        J_block(23, 5) = 1.0 * state(20) * state(21) * Rate_27;
        J_block(23, 10) = 0.025000000000000001 * state(20);
        J_block(23, 13) = 0.025000000000000001 * state(20);
        J_block(23, 16) = 0.025000000000000001 * state(20);
        J_block(23, 19) = 0.025000000000000001 * state(20);
        J_block(23, 20) = 0.025000000000000001 * state(10) + 0.025000000000000001 * state(13) +
                          1.0 * state(21) * state(5) * Rate_27 + 0.025000000000000001 * state(16) +
                          0.025000000000000001 * state(19);
        J_block(23, 21) = 1.0 * state(20) * state(5) * Rate_27;
        J_block(24, 11) = 0.025000000000000001 * state(20);
        J_block(24, 14) = 0.025000000000000001 * state(20);
        J_block(24, 17) = 0.025000000000000001 * state(20);
        J_block(24, 20) = 0.025000000000000001 * state(11) + 0.025000000000000001 * state(14) +
                          0.025000000000000001 * state(17);
        J_block(25, 12) = 0.025000000000000001 * state(20);
        J_block(25, 15) = 0.025000000000000001 * state(20);
        J_block(25, 18) = 0.025000000000000001 * state(20);
        J_block(25, 20) = 0.025000000000000001 * state(12) + 0.025000000000000001 * state(15) +
                          0.025000000000000001 * state(18);
    }

    template <class StateView, class JacView>
    KOKKOS_INLINE_FUNCTION
    void compute_adjoint(const StateView& state, JacView& J_adj_block) const {
        J_adj_block(0, 0) = -5.0442046141041832e-12 * state(3) - 3.3000000000000001e-12 * state(4);
        J_adj_block(0, 3) = -5.0442046141041832e-12 * state(3);
        J_adj_block(0, 4) = 5.0442046141041832e-12 * state(3) - 3.3000000000000001e-12 * state(4);
        J_adj_block(0, 5) = 3.3000000000000001e-12 * state(4);
        J_adj_block(1, 1) = -3.3571944693753379e-14 * state(3);
        J_adj_block(1, 3) = -3.3571944693753379e-14 * state(3);
        J_adj_block(1, 4) = 3.3571944693753379e-14 * state(3);
        J_adj_block(2, 0) = 2.0000000000000002e-5;
        J_adj_block(2, 2) = -0.0025000000000000001 * state(4) - 1.0000000000000001e-5;
        J_adj_block(2, 4) = -0.0025000000000000001 * state(4);
        J_adj_block(2, 5) = 0.0025000000000000001 * state(4);
        J_adj_block(3, 0) = -5.0442046141041832e-12 * state(0);
        J_adj_block(3, 1) = -3.3571944693753379e-14 * state(1);
        J_adj_block(3, 3) = -3.3571944693753379e-14 * state(1) - 5.0442046141041832e-12 * state(0);
        J_adj_block(3, 4) = 3.3571944693753379e-14 * state(1) + 5.0442046141041832e-12 * state(0);
        J_adj_block(4, 0) = -3.3000000000000001e-12 * state(0);
        J_adj_block(4, 2) = -0.0025000000000000001 * state(2);
        J_adj_block(4, 4) = -2.5000000000000001e-5 * state(10) - 2.5000000000000001e-5 * state(11) -
                            2.5000000000000001e-5 * state(12) - 2.5000000000000001e-5 * state(13) -
                            2.5000000000000001e-5 * state(14) - 0.0025000000000000001 * state(2) -
                            3.3000000000000001e-12 * state(0) - 0.00025000000000000001 * state(15) -
                            0.00025000000000000001 * state(16) -
                            0.00025000000000000001 * state(17) -
                            0.00025000000000000001 * state(18) - 0.00025000000000000001 * state(19);
        J_adj_block(4, 5) = 2.5000000000000001e-5 * state(10) + 2.5000000000000001e-5 * state(11) +
                            2.5000000000000001e-5 * state(12) + 2.5000000000000001e-5 * state(13) +
                            2.5000000000000001e-5 * state(14) + 0.0025000000000000001 * state(2) +
                            3.3000000000000001e-12 * state(0) + 0.00025000000000000001 * state(15) +
                            0.00025000000000000001 * state(16) +
                            0.00025000000000000001 * state(17) +
                            0.00025000000000000001 * state(18) + 0.00025000000000000001 * state(19);
        J_adj_block(5, 5) = -1.0 * state(20) * state(21) * Rate_27;
        J_adj_block(5, 20) = -1.0 * state(20) * state(21) * Rate_27;
        J_adj_block(5, 21) = -1.0 * state(20) * state(21) * Rate_27;
        J_adj_block(5, 22) = 1.0 * state(20) * state(21) * Rate_27;
        J_adj_block(5, 23) = 1.0 * state(20) * state(21) * Rate_27;
        J_adj_block(6, 6) = -5.0000000000000004e-6;
        J_adj_block(6, 7) = 5.0000000000000004e-6;
        J_adj_block(8, 8) = -5.0000000000000004e-6;
        J_adj_block(8, 9) = 5.0000000000000004e-6;
        J_adj_block(10, 4) = -2.5000000000000001e-5 * state(4);
        J_adj_block(10, 5) = 2.5000000000000001e-5 * state(4);
        J_adj_block(10, 20) = -0.025000000000000001 * state(20);
        J_adj_block(10, 23) = 0.025000000000000001 * state(20);
        J_adj_block(11, 4) = -2.5000000000000001e-5 * state(4);
        J_adj_block(11, 5) = 2.5000000000000001e-5 * state(4);
        J_adj_block(11, 20) = -0.025000000000000001 * state(20);
        J_adj_block(11, 24) = 0.025000000000000001 * state(20);
        J_adj_block(12, 4) = -2.5000000000000001e-5 * state(4);
        J_adj_block(12, 5) = 2.5000000000000001e-5 * state(4);
        J_adj_block(12, 20) = -0.025000000000000001 * state(20);
        J_adj_block(12, 25) = 0.025000000000000001 * state(20);
        J_adj_block(13, 4) = -2.5000000000000001e-5 * state(4);
        J_adj_block(13, 5) = 2.5000000000000001e-5 * state(4);
        J_adj_block(13, 20) = -0.025000000000000001 * state(20);
        J_adj_block(13, 23) = 0.025000000000000001 * state(20);
        J_adj_block(14, 4) = -2.5000000000000001e-5 * state(4);
        J_adj_block(14, 5) = 2.5000000000000001e-5 * state(4);
        J_adj_block(14, 20) = -0.025000000000000001 * state(20);
        J_adj_block(14, 24) = 0.025000000000000001 * state(20);
        J_adj_block(15, 4) = -0.00025000000000000001 * state(4);
        J_adj_block(15, 5) = 0.00025000000000000001 * state(4);
        J_adj_block(15, 20) = -0.025000000000000001 * state(20);
        J_adj_block(15, 25) = 0.025000000000000001 * state(20);
        J_adj_block(16, 4) = -0.00025000000000000001 * state(4);
        J_adj_block(16, 5) = 0.00025000000000000001 * state(4);
        J_adj_block(16, 20) = -0.025000000000000001 * state(20);
        J_adj_block(16, 23) = 0.025000000000000001 * state(20);
        J_adj_block(17, 4) = -0.00025000000000000001 * state(4);
        J_adj_block(17, 5) = 0.00025000000000000001 * state(4);
        J_adj_block(17, 20) = -0.025000000000000001 * state(20);
        J_adj_block(17, 24) = 0.025000000000000001 * state(20);
        J_adj_block(18, 4) = -0.00025000000000000001 * state(4);
        J_adj_block(18, 5) = 0.00025000000000000001 * state(4);
        J_adj_block(18, 20) = -0.025000000000000001 * state(20);
        J_adj_block(18, 25) = 0.025000000000000001 * state(20);
        J_adj_block(19, 4) = -0.00025000000000000001 * state(4);
        J_adj_block(19, 5) = 0.00025000000000000001 * state(4);
        J_adj_block(19, 20) = -0.025000000000000001 * state(20);
        J_adj_block(19, 23) = 0.025000000000000001 * state(20);
        J_adj_block(20, 5) = -1.0 * state(21) * state(5) * Rate_27;
        J_adj_block(20, 20) = -0.025000000000000001 * state(10) - 0.025000000000000001 * state(11) -
                              0.025000000000000001 * state(12) - 0.025000000000000001 * state(13) -
                              0.025000000000000001 * state(14) -
                              1.0 * state(21) * state(5) * Rate_27 -
                              0.025000000000000001 * state(15) - 0.025000000000000001 * state(16) -
                              0.025000000000000001 * state(17) - 0.025000000000000001 * state(18) -
                              0.025000000000000001 * state(19);
        J_adj_block(20, 21) = -1.0 * state(21) * state(5) * Rate_27;
        J_adj_block(20, 22) = 1.0 * state(21) * state(5) * Rate_27;
        J_adj_block(20, 23) = 0.025000000000000001 * state(10) + 0.025000000000000001 * state(13) +
                              1.0 * state(21) * state(5) * Rate_27 +
                              0.025000000000000001 * state(16) + 0.025000000000000001 * state(19);
        J_adj_block(20, 24) = 0.025000000000000001 * state(11) + 0.025000000000000001 * state(14) +
                              0.025000000000000001 * state(17);
        J_adj_block(20, 25) = 0.025000000000000001 * state(12) + 0.025000000000000001 * state(15) +
                              0.025000000000000001 * state(18);
        J_adj_block(21, 5) = -1.0 * state(20) * state(5) * Rate_27;
        J_adj_block(21, 20) = -1.0 * state(20) * state(5) * Rate_27;
        J_adj_block(21, 21) = -1.0 * state(20) * state(5) * Rate_27;
        J_adj_block(21, 22) = 1.0 * state(20) * state(5) * Rate_27;
        J_adj_block(21, 23) = 1.0 * state(20) * state(5) * Rate_27;
    }

    template <class StateView, class DeltaView, class RateView>
    KOKKOS_INLINE_FUNCTION
    void compute_tlm(const StateView& state, const DeltaView& delta_C, RateView& dF_block) const {
        dF_block(0) = 0.0;
        dF_block(0) +=
            (-5.0442046141041832e-12 * state(3) - 3.3000000000000001e-12 * state(4)) * delta_C(0);
        dF_block(0) += (2.0000000000000002e-5) * delta_C(2);
        dF_block(0) += (-5.0442046141041832e-12 * state(0)) * delta_C(3);
        dF_block(0) += (-3.3000000000000001e-12 * state(0)) * delta_C(4);
        dF_block(1) = 0.0;
        dF_block(1) += (-3.3571944693753379e-14 * state(3)) * delta_C(1);
        dF_block(1) += (-3.3571944693753379e-14 * state(1)) * delta_C(3);
        dF_block(2) = 0.0;
        dF_block(2) += (-0.0025000000000000001 * state(4) - 1.0000000000000001e-5) * delta_C(2);
        dF_block(2) += (-0.0025000000000000001 * state(2)) * delta_C(4);
        dF_block(3) = 0.0;
        dF_block(3) += (-5.0442046141041832e-12 * state(3)) * delta_C(0);
        dF_block(3) += (-3.3571944693753379e-14 * state(3)) * delta_C(1);
        dF_block(3) +=
            (-3.3571944693753379e-14 * state(1) - 5.0442046141041832e-12 * state(0)) * delta_C(3);
        dF_block(4) = 0.0;
        dF_block(4) +=
            (5.0442046141041832e-12 * state(3) - 3.3000000000000001e-12 * state(4)) * delta_C(0);
        dF_block(4) += (3.3571944693753379e-14 * state(3)) * delta_C(1);
        dF_block(4) += (-0.0025000000000000001 * state(4)) * delta_C(2);
        dF_block(4) +=
            (3.3571944693753379e-14 * state(1) + 5.0442046141041832e-12 * state(0)) * delta_C(3);
        dF_block(4) += (-2.5000000000000001e-5 * state(10) - 2.5000000000000001e-5 * state(11) -
                        2.5000000000000001e-5 * state(12) - 2.5000000000000001e-5 * state(13) -
                        2.5000000000000001e-5 * state(14) - 0.0025000000000000001 * state(2) -
                        3.3000000000000001e-12 * state(0) - 0.00025000000000000001 * state(15) -
                        0.00025000000000000001 * state(16) - 0.00025000000000000001 * state(17) -
                        0.00025000000000000001 * state(18) - 0.00025000000000000001 * state(19)) *
                       delta_C(4);
        dF_block(4) += (-2.5000000000000001e-5 * state(4)) * delta_C(10);
        dF_block(4) += (-2.5000000000000001e-5 * state(4)) * delta_C(11);
        dF_block(4) += (-2.5000000000000001e-5 * state(4)) * delta_C(12);
        dF_block(4) += (-2.5000000000000001e-5 * state(4)) * delta_C(13);
        dF_block(4) += (-2.5000000000000001e-5 * state(4)) * delta_C(14);
        dF_block(4) += (-0.00025000000000000001 * state(4)) * delta_C(15);
        dF_block(4) += (-0.00025000000000000001 * state(4)) * delta_C(16);
        dF_block(4) += (-0.00025000000000000001 * state(4)) * delta_C(17);
        dF_block(4) += (-0.00025000000000000001 * state(4)) * delta_C(18);
        dF_block(4) += (-0.00025000000000000001 * state(4)) * delta_C(19);
        dF_block(5) = 0.0;
        dF_block(5) += (3.3000000000000001e-12 * state(4)) * delta_C(0);
        dF_block(5) += (0.0025000000000000001 * state(4)) * delta_C(2);
        dF_block(5) += (2.5000000000000001e-5 * state(10) + 2.5000000000000001e-5 * state(11) +
                        2.5000000000000001e-5 * state(12) + 2.5000000000000001e-5 * state(13) +
                        2.5000000000000001e-5 * state(14) + 0.0025000000000000001 * state(2) +
                        3.3000000000000001e-12 * state(0) + 0.00025000000000000001 * state(15) +
                        0.00025000000000000001 * state(16) + 0.00025000000000000001 * state(17) +
                        0.00025000000000000001 * state(18) + 0.00025000000000000001 * state(19)) *
                       delta_C(4);
        dF_block(5) += (-1.0 * state(20) * state(21) * Rate_27) * delta_C(5);
        dF_block(5) += (2.5000000000000001e-5 * state(4)) * delta_C(10);
        dF_block(5) += (2.5000000000000001e-5 * state(4)) * delta_C(11);
        dF_block(5) += (2.5000000000000001e-5 * state(4)) * delta_C(12);
        dF_block(5) += (2.5000000000000001e-5 * state(4)) * delta_C(13);
        dF_block(5) += (2.5000000000000001e-5 * state(4)) * delta_C(14);
        dF_block(5) += (0.00025000000000000001 * state(4)) * delta_C(15);
        dF_block(5) += (0.00025000000000000001 * state(4)) * delta_C(16);
        dF_block(5) += (0.00025000000000000001 * state(4)) * delta_C(17);
        dF_block(5) += (0.00025000000000000001 * state(4)) * delta_C(18);
        dF_block(5) += (0.00025000000000000001 * state(4)) * delta_C(19);
        dF_block(5) += (-1.0 * state(21) * state(5) * Rate_27) * delta_C(20);
        dF_block(5) += (-1.0 * state(20) * state(5) * Rate_27) * delta_C(21);
        dF_block(6) = 0.0;
        dF_block(6) += (-5.0000000000000004e-6) * delta_C(6);
        dF_block(7) = 0.0;
        dF_block(7) += (5.0000000000000004e-6) * delta_C(6);
        dF_block(8) = 0.0;
        dF_block(8) += (-5.0000000000000004e-6) * delta_C(8);
        dF_block(9) = 0.0;
        dF_block(9) += (5.0000000000000004e-6) * delta_C(8);
        dF_block(10) = 0.0;
        dF_block(11) = 0.0;
        dF_block(12) = 0.0;
        dF_block(13) = 0.0;
        dF_block(14) = 0.0;
        dF_block(15) = 0.0;
        dF_block(16) = 0.0;
        dF_block(17) = 0.0;
        dF_block(18) = 0.0;
        dF_block(19) = 0.0;
        dF_block(20) = 0.0;
        dF_block(20) += (-1.0 * state(20) * state(21) * Rate_27) * delta_C(5);
        dF_block(20) += (-0.025000000000000001 * state(20)) * delta_C(10);
        dF_block(20) += (-0.025000000000000001 * state(20)) * delta_C(11);
        dF_block(20) += (-0.025000000000000001 * state(20)) * delta_C(12);
        dF_block(20) += (-0.025000000000000001 * state(20)) * delta_C(13);
        dF_block(20) += (-0.025000000000000001 * state(20)) * delta_C(14);
        dF_block(20) += (-0.025000000000000001 * state(20)) * delta_C(15);
        dF_block(20) += (-0.025000000000000001 * state(20)) * delta_C(16);
        dF_block(20) += (-0.025000000000000001 * state(20)) * delta_C(17);
        dF_block(20) += (-0.025000000000000001 * state(20)) * delta_C(18);
        dF_block(20) += (-0.025000000000000001 * state(20)) * delta_C(19);
        dF_block(20) += (-0.025000000000000001 * state(10) - 0.025000000000000001 * state(11) -
                         0.025000000000000001 * state(12) - 0.025000000000000001 * state(13) -
                         0.025000000000000001 * state(14) - 1.0 * state(21) * state(5) * Rate_27 -
                         0.025000000000000001 * state(15) - 0.025000000000000001 * state(16) -
                         0.025000000000000001 * state(17) - 0.025000000000000001 * state(18) -
                         0.025000000000000001 * state(19)) *
                        delta_C(20);
        dF_block(20) += (-1.0 * state(20) * state(5) * Rate_27) * delta_C(21);
        dF_block(21) = 0.0;
        dF_block(21) += (-1.0 * state(20) * state(21) * Rate_27) * delta_C(5);
        dF_block(21) += (-1.0 * state(21) * state(5) * Rate_27) * delta_C(20);
        dF_block(21) += (-1.0 * state(20) * state(5) * Rate_27) * delta_C(21);
        dF_block(22) = 0.0;
        dF_block(22) += (1.0 * state(20) * state(21) * Rate_27) * delta_C(5);
        dF_block(22) += (1.0 * state(21) * state(5) * Rate_27) * delta_C(20);
        dF_block(22) += (1.0 * state(20) * state(5) * Rate_27) * delta_C(21);
        dF_block(23) = 0.0;
        dF_block(23) += (1.0 * state(20) * state(21) * Rate_27) * delta_C(5);
        dF_block(23) += (0.025000000000000001 * state(20)) * delta_C(10);
        dF_block(23) += (0.025000000000000001 * state(20)) * delta_C(13);
        dF_block(23) += (0.025000000000000001 * state(20)) * delta_C(16);
        dF_block(23) += (0.025000000000000001 * state(20)) * delta_C(19);
        dF_block(23) += (0.025000000000000001 * state(10) + 0.025000000000000001 * state(13) +
                         1.0 * state(21) * state(5) * Rate_27 + 0.025000000000000001 * state(16) +
                         0.025000000000000001 * state(19)) *
                        delta_C(20);
        dF_block(23) += (1.0 * state(20) * state(5) * Rate_27) * delta_C(21);
        dF_block(24) = 0.0;
        dF_block(24) += (0.025000000000000001 * state(20)) * delta_C(11);
        dF_block(24) += (0.025000000000000001 * state(20)) * delta_C(14);
        dF_block(24) += (0.025000000000000001 * state(20)) * delta_C(17);
        dF_block(24) += (0.025000000000000001 * state(11) + 0.025000000000000001 * state(14) +
                         0.025000000000000001 * state(17)) *
                        delta_C(20);
        dF_block(25) = 0.0;
        dF_block(25) += (0.025000000000000001 * state(20)) * delta_C(12);
        dF_block(25) += (0.025000000000000001 * state(20)) * delta_C(15);
        dF_block(25) += (0.025000000000000001 * state(20)) * delta_C(18);
        dF_block(25) += (0.025000000000000001 * state(12) + 0.025000000000000001 * state(15) +
                         0.025000000000000001 * state(18)) *
                        delta_C(20);
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
        C_projected(11) = C(11);
        C_projected(12) = C(12);
        C_projected(13) = C(13);
        C_projected(14) = C(14);
        C_projected(15) = C(15);
        C_projected(16) = C(16);
        C_projected(17) = C(17);
        C_projected(18) = C(18);
        C_projected(19) = C(19);
        C_projected(20) = C(20);
        C_projected(21) = C(21);
        C_projected(22) = C(22);
        C_projected(23) = C(23);
        C_projected(24) = C(24);
        C_projected(25) = C(25);
    }

    template <class StateView>
    KOKKOS_INLINE_FUNCTION
    void integrate(double dt, StateView& state) const {
        const int NUM_SPECIES = 26;
        const double g = 1.70710678118654752440;
        const double ros_A0 = 1.0 / g;
        const double ros_C0 = -2.0 / g;
        const double ros_M0 = 3.0 / (2.0 * g);
        const double ros_M1 = 1.0 / (2.0 * g);
        const double inv_g_dt = 1.0 / (g * dt);

        // 1. Stage 1 Rates (F1)
        double F1_0 = -5.0442046141041832e-12 * state(3) * state(0) +
                      2.0000000000000002e-5 * state(2) -
                      3.3000000000000001e-12 * state(0) * state(4);
        double F1_1 = -3.3571944693753379e-14 * state(3) * state(1);
        double F1_2 =
            -0.0025000000000000001 * state(2) * state(4) - 1.0000000000000001e-5 * state(2);
        double F1_3 = -3.3571944693753379e-14 * state(3) * state(1) -
                      5.0442046141041832e-12 * state(3) * state(0);
        double F1_4 = 3.3571944693753379e-14 * state(3) * state(1) +
                      5.0442046141041832e-12 * state(3) * state(0) -
                      2.5000000000000001e-5 * state(10) * state(4) -
                      2.5000000000000001e-5 * state(11) * state(4) -
                      2.5000000000000001e-5 * state(12) * state(4) -
                      2.5000000000000001e-5 * state(13) * state(4) -
                      2.5000000000000001e-5 * state(14) * state(4) -
                      0.0025000000000000001 * state(2) * state(4) -
                      3.3000000000000001e-12 * state(0) * state(4) -
                      0.00025000000000000001 * state(4) * state(15) -
                      0.00025000000000000001 * state(4) * state(16) -
                      0.00025000000000000001 * state(4) * state(17) -
                      0.00025000000000000001 * state(4) * state(18) -
                      0.00025000000000000001 * state(4) * state(19);
        double F1_5 = 2.5000000000000001e-5 * state(10) * state(4) +
                      2.5000000000000001e-5 * state(11) * state(4) +
                      2.5000000000000001e-5 * state(12) * state(4) +
                      2.5000000000000001e-5 * state(13) * state(4) +
                      2.5000000000000001e-5 * state(14) * state(4) +
                      0.0025000000000000001 * state(2) * state(4) -
                      1.0 * state(20) * state(21) * state(5) * Rate_27 +
                      3.3000000000000001e-12 * state(0) * state(4) +
                      0.00025000000000000001 * state(4) * state(15) +
                      0.00025000000000000001 * state(4) * state(16) +
                      0.00025000000000000001 * state(4) * state(17) +
                      0.00025000000000000001 * state(4) * state(18) +
                      0.00025000000000000001 * state(4) * state(19);
        double F1_6 = -5.0000000000000004e-6 * state(6);
        double F1_7 = 5.0000000000000004e-6 * state(6);
        double F1_8 = -5.0000000000000004e-6 * state(8);
        double F1_9 = 5.0000000000000004e-6 * state(8);
        double F1_10 = 0.0;
        double F1_11 = 0.0;
        double F1_12 = 0.0;
        double F1_13 = 0.0;
        double F1_14 = 0.0;
        double F1_15 = 0.0;
        double F1_16 = 0.0;
        double F1_17 = 0.0;
        double F1_18 = 0.0;
        double F1_19 = 0.0;
        double F1_20 = -0.025000000000000001 * state(10) * state(20) -
                       0.025000000000000001 * state(11) * state(20) -
                       0.025000000000000001 * state(12) * state(20) -
                       0.025000000000000001 * state(13) * state(20) -
                       0.025000000000000001 * state(14) * state(20) -
                       1.0 * state(20) * state(21) * state(5) * Rate_27 -
                       0.025000000000000001 * state(20) * state(15) -
                       0.025000000000000001 * state(20) * state(16) -
                       0.025000000000000001 * state(20) * state(17) -
                       0.025000000000000001 * state(20) * state(18) -
                       0.025000000000000001 * state(20) * state(19);
        double F1_21 = -1.0 * state(20) * state(21) * state(5) * Rate_27;
        double F1_22 = 1.0 * state(20) * state(21) * state(5) * Rate_27;
        double F1_23 = 0.025000000000000001 * state(10) * state(20) +
                       0.025000000000000001 * state(13) * state(20) +
                       1.0 * state(20) * state(21) * state(5) * Rate_27 +
                       0.025000000000000001 * state(20) * state(16) +
                       0.025000000000000001 * state(20) * state(19);
        double F1_24 = 0.025000000000000001 * state(11) * state(20) +
                       0.025000000000000001 * state(14) * state(20) +
                       0.025000000000000001 * state(20) * state(17);
        double F1_25 = 0.025000000000000001 * state(12) * state(20) +
                       0.025000000000000001 * state(20) * state(15) +
                       0.025000000000000001 * state(20) * state(18);

        // 2. Analytical Jacobian & Iteration Matrix W = inv_g_dt*I - J
        double J_0_0 = -5.0442046141041832e-12 * state(3) - 3.3000000000000001e-12 * state(4);
        double J_0_2 = 2.0000000000000002e-5;
        double J_0_3 = -5.0442046141041832e-12 * state(0);
        double J_0_4 = -3.3000000000000001e-12 * state(0);
        double J_1_1 = -3.3571944693753379e-14 * state(3);
        double J_1_3 = -3.3571944693753379e-14 * state(1);
        double J_2_2 = -0.0025000000000000001 * state(4) - 1.0000000000000001e-5;
        double J_2_4 = -0.0025000000000000001 * state(2);
        double J_3_0 = -5.0442046141041832e-12 * state(3);
        double J_3_1 = -3.3571944693753379e-14 * state(3);
        double J_3_3 = -3.3571944693753379e-14 * state(1) - 5.0442046141041832e-12 * state(0);
        double J_4_0 = 5.0442046141041832e-12 * state(3) - 3.3000000000000001e-12 * state(4);
        double J_4_1 = 3.3571944693753379e-14 * state(3);
        double J_4_2 = -0.0025000000000000001 * state(4);
        double J_4_3 = 3.3571944693753379e-14 * state(1) + 5.0442046141041832e-12 * state(0);
        double J_4_4 = -2.5000000000000001e-5 * state(10) - 2.5000000000000001e-5 * state(11) -
                       2.5000000000000001e-5 * state(12) - 2.5000000000000001e-5 * state(13) -
                       2.5000000000000001e-5 * state(14) - 0.0025000000000000001 * state(2) -
                       3.3000000000000001e-12 * state(0) - 0.00025000000000000001 * state(15) -
                       0.00025000000000000001 * state(16) - 0.00025000000000000001 * state(17) -
                       0.00025000000000000001 * state(18) - 0.00025000000000000001 * state(19);
        double J_4_10 = -2.5000000000000001e-5 * state(4);
        double J_4_11 = -2.5000000000000001e-5 * state(4);
        double J_4_12 = -2.5000000000000001e-5 * state(4);
        double J_4_13 = -2.5000000000000001e-5 * state(4);
        double J_4_14 = -2.5000000000000001e-5 * state(4);
        double J_4_15 = -0.00025000000000000001 * state(4);
        double J_4_16 = -0.00025000000000000001 * state(4);
        double J_4_17 = -0.00025000000000000001 * state(4);
        double J_4_18 = -0.00025000000000000001 * state(4);
        double J_4_19 = -0.00025000000000000001 * state(4);
        double J_5_0 = 3.3000000000000001e-12 * state(4);
        double J_5_2 = 0.0025000000000000001 * state(4);
        double J_5_4 = 2.5000000000000001e-5 * state(10) + 2.5000000000000001e-5 * state(11) +
                       2.5000000000000001e-5 * state(12) + 2.5000000000000001e-5 * state(13) +
                       2.5000000000000001e-5 * state(14) + 0.0025000000000000001 * state(2) +
                       3.3000000000000001e-12 * state(0) + 0.00025000000000000001 * state(15) +
                       0.00025000000000000001 * state(16) + 0.00025000000000000001 * state(17) +
                       0.00025000000000000001 * state(18) + 0.00025000000000000001 * state(19);
        double J_5_5 = -1.0 * state(20) * state(21) * Rate_27;
        double J_5_10 = 2.5000000000000001e-5 * state(4);
        double J_5_11 = 2.5000000000000001e-5 * state(4);
        double J_5_12 = 2.5000000000000001e-5 * state(4);
        double J_5_13 = 2.5000000000000001e-5 * state(4);
        double J_5_14 = 2.5000000000000001e-5 * state(4);
        double J_5_15 = 0.00025000000000000001 * state(4);
        double J_5_16 = 0.00025000000000000001 * state(4);
        double J_5_17 = 0.00025000000000000001 * state(4);
        double J_5_18 = 0.00025000000000000001 * state(4);
        double J_5_19 = 0.00025000000000000001 * state(4);
        double J_5_20 = -1.0 * state(21) * state(5) * Rate_27;
        double J_5_21 = -1.0 * state(20) * state(5) * Rate_27;
        double J_6_6 = -5.0000000000000004e-6;
        double J_7_6 = 5.0000000000000004e-6;
        double J_8_8 = -5.0000000000000004e-6;
        double J_9_8 = 5.0000000000000004e-6;
        double J_20_5 = -1.0 * state(20) * state(21) * Rate_27;
        double J_20_10 = -0.025000000000000001 * state(20);
        double J_20_11 = -0.025000000000000001 * state(20);
        double J_20_12 = -0.025000000000000001 * state(20);
        double J_20_13 = -0.025000000000000001 * state(20);
        double J_20_14 = -0.025000000000000001 * state(20);
        double J_20_15 = -0.025000000000000001 * state(20);
        double J_20_16 = -0.025000000000000001 * state(20);
        double J_20_17 = -0.025000000000000001 * state(20);
        double J_20_18 = -0.025000000000000001 * state(20);
        double J_20_19 = -0.025000000000000001 * state(20);
        double J_20_20 = -0.025000000000000001 * state(10) - 0.025000000000000001 * state(11) -
                         0.025000000000000001 * state(12) - 0.025000000000000001 * state(13) -
                         0.025000000000000001 * state(14) - 1.0 * state(21) * state(5) * Rate_27 -
                         0.025000000000000001 * state(15) - 0.025000000000000001 * state(16) -
                         0.025000000000000001 * state(17) - 0.025000000000000001 * state(18) -
                         0.025000000000000001 * state(19);
        double J_20_21 = -1.0 * state(20) * state(5) * Rate_27;
        double J_21_5 = -1.0 * state(20) * state(21) * Rate_27;
        double J_21_20 = -1.0 * state(21) * state(5) * Rate_27;
        double J_21_21 = -1.0 * state(20) * state(5) * Rate_27;
        double J_22_5 = 1.0 * state(20) * state(21) * Rate_27;
        double J_22_20 = 1.0 * state(21) * state(5) * Rate_27;
        double J_22_21 = 1.0 * state(20) * state(5) * Rate_27;
        double J_23_5 = 1.0 * state(20) * state(21) * Rate_27;
        double J_23_10 = 0.025000000000000001 * state(20);
        double J_23_13 = 0.025000000000000001 * state(20);
        double J_23_16 = 0.025000000000000001 * state(20);
        double J_23_19 = 0.025000000000000001 * state(20);
        double J_23_20 = 0.025000000000000001 * state(10) + 0.025000000000000001 * state(13) +
                         1.0 * state(21) * state(5) * Rate_27 + 0.025000000000000001 * state(16) +
                         0.025000000000000001 * state(19);
        double J_23_21 = 1.0 * state(20) * state(5) * Rate_27;
        double J_24_11 = 0.025000000000000001 * state(20);
        double J_24_14 = 0.025000000000000001 * state(20);
        double J_24_17 = 0.025000000000000001 * state(20);
        double J_24_20 = 0.025000000000000001 * state(11) + 0.025000000000000001 * state(14) +
                         0.025000000000000001 * state(17);
        double J_25_12 = 0.025000000000000001 * state(20);
        double J_25_15 = 0.025000000000000001 * state(20);
        double J_25_18 = 0.025000000000000001 * state(20);
        double J_25_20 = 0.025000000000000001 * state(12) + 0.025000000000000001 * state(15) +
                         0.025000000000000001 * state(18);
        double W_0_0 = inv_g_dt - J_0_0;
        double W_0_2 = -J_0_2;
        double W_0_3 = -J_0_3;
        double W_0_4 = -J_0_4;
        double W_1_1 = inv_g_dt - J_1_1;
        double W_1_3 = -J_1_3;
        double W_2_2 = inv_g_dt - J_2_2;
        double W_2_4 = -J_2_4;
        double W_3_0 = -J_3_0;
        double W_3_1 = -J_3_1;
        double W_3_3 = inv_g_dt - J_3_3;
        double W_4_0 = -J_4_0;
        double W_4_1 = -J_4_1;
        double W_4_2 = -J_4_2;
        double W_4_3 = -J_4_3;
        double W_4_4 = inv_g_dt - J_4_4;
        double W_4_10 = -J_4_10;
        double W_4_11 = -J_4_11;
        double W_4_12 = -J_4_12;
        double W_4_13 = -J_4_13;
        double W_4_14 = -J_4_14;
        double W_4_15 = -J_4_15;
        double W_4_16 = -J_4_16;
        double W_4_17 = -J_4_17;
        double W_4_18 = -J_4_18;
        double W_4_19 = -J_4_19;
        double W_5_0 = -J_5_0;
        double W_5_2 = -J_5_2;
        double W_5_4 = -J_5_4;
        double W_5_5 = inv_g_dt - J_5_5;
        double W_5_10 = -J_5_10;
        double W_5_11 = -J_5_11;
        double W_5_12 = -J_5_12;
        double W_5_13 = -J_5_13;
        double W_5_14 = -J_5_14;
        double W_5_15 = -J_5_15;
        double W_5_16 = -J_5_16;
        double W_5_17 = -J_5_17;
        double W_5_18 = -J_5_18;
        double W_5_19 = -J_5_19;
        double W_5_20 = -J_5_20;
        double W_5_21 = -J_5_21;
        double W_6_6 = inv_g_dt - J_6_6;
        double W_7_6 = -J_7_6;
        double W_7_7 = inv_g_dt;
        double W_8_8 = inv_g_dt - J_8_8;
        double W_9_8 = -J_9_8;
        double W_9_9 = inv_g_dt;
        double W_10_10 = inv_g_dt;
        double W_11_11 = inv_g_dt;
        double W_12_12 = inv_g_dt;
        double W_13_13 = inv_g_dt;
        double W_14_14 = inv_g_dt;
        double W_15_15 = inv_g_dt;
        double W_16_16 = inv_g_dt;
        double W_17_17 = inv_g_dt;
        double W_18_18 = inv_g_dt;
        double W_19_19 = inv_g_dt;
        double W_20_5 = -J_20_5;
        double W_20_10 = -J_20_10;
        double W_20_11 = -J_20_11;
        double W_20_12 = -J_20_12;
        double W_20_13 = -J_20_13;
        double W_20_14 = -J_20_14;
        double W_20_15 = -J_20_15;
        double W_20_16 = -J_20_16;
        double W_20_17 = -J_20_17;
        double W_20_18 = -J_20_18;
        double W_20_19 = -J_20_19;
        double W_20_20 = inv_g_dt - J_20_20;
        double W_20_21 = -J_20_21;
        double W_21_5 = -J_21_5;
        double W_21_20 = -J_21_20;
        double W_21_21 = inv_g_dt - J_21_21;
        double W_22_5 = -J_22_5;
        double W_22_20 = -J_22_20;
        double W_22_21 = -J_22_21;
        double W_22_22 = inv_g_dt;
        double W_23_5 = -J_23_5;
        double W_23_10 = -J_23_10;
        double W_23_13 = -J_23_13;
        double W_23_16 = -J_23_16;
        double W_23_19 = -J_23_19;
        double W_23_20 = -J_23_20;
        double W_23_21 = -J_23_21;
        double W_23_23 = inv_g_dt;
        double W_24_11 = -J_24_11;
        double W_24_14 = -J_24_14;
        double W_24_17 = -J_24_17;
        double W_24_20 = -J_24_20;
        double W_24_24 = inv_g_dt;
        double W_25_12 = -J_25_12;
        double W_25_15 = -J_25_15;
        double W_25_18 = -J_25_18;
        double W_25_20 = -J_25_20;
        double W_25_25 = inv_g_dt;

        // 3. Symbolic Doolittle Sparse LU Factorization
        double U_0_0 = W_0_0;
        double U_0_2 = W_0_2;
        double U_0_3 = W_0_3;
        double U_0_4 = W_0_4;
        double L_3_0 = (W_3_0) / U_0_0;
        double L_4_0 = (W_4_0) / U_0_0;
        double L_5_0 = (W_5_0) / U_0_0;
        double U_1_1 = W_1_1;
        double U_1_3 = W_1_3;
        double L_3_1 = (W_3_1) / U_1_1;
        double L_4_1 = (W_4_1) / U_1_1;
        double U_2_2 = W_2_2;
        double U_2_4 = W_2_4;
        double L_3_2 = (0.0 - L_3_0 * U_0_2) / U_2_2;
        double L_4_2 = (W_4_2 - L_4_0 * U_0_2) / U_2_2;
        double L_5_2 = (W_5_2 - L_5_0 * U_0_2) / U_2_2;
        double U_3_3 = W_3_3 - L_3_0 * U_0_3 - L_3_1 * U_1_3;
        double U_3_4 = 0.0 - L_3_0 * U_0_4 - L_3_2 * U_2_4;
        double L_4_3 = (W_4_3 - L_4_0 * U_0_3 - L_4_1 * U_1_3) / U_3_3;
        double L_5_3 = (0.0 - L_5_0 * U_0_3) / U_3_3;
        double U_4_4 = W_4_4 - L_4_0 * U_0_4 - L_4_2 * U_2_4 - L_4_3 * U_3_4;
        double U_4_10 = W_4_10;
        double U_4_11 = W_4_11;
        double U_4_12 = W_4_12;
        double U_4_13 = W_4_13;
        double U_4_14 = W_4_14;
        double U_4_15 = W_4_15;
        double U_4_16 = W_4_16;
        double U_4_17 = W_4_17;
        double U_4_18 = W_4_18;
        double U_4_19 = W_4_19;
        double L_5_4 = (W_5_4 - L_5_0 * U_0_4 - L_5_2 * U_2_4 - L_5_3 * U_3_4) / U_4_4;
        double U_5_5 = W_5_5;
        double U_5_10 = W_5_10 - L_5_4 * U_4_10;
        double U_5_11 = W_5_11 - L_5_4 * U_4_11;
        double U_5_12 = W_5_12 - L_5_4 * U_4_12;
        double U_5_13 = W_5_13 - L_5_4 * U_4_13;
        double U_5_14 = W_5_14 - L_5_4 * U_4_14;
        double U_5_15 = W_5_15 - L_5_4 * U_4_15;
        double U_5_16 = W_5_16 - L_5_4 * U_4_16;
        double U_5_17 = W_5_17 - L_5_4 * U_4_17;
        double U_5_18 = W_5_18 - L_5_4 * U_4_18;
        double U_5_19 = W_5_19 - L_5_4 * U_4_19;
        double U_5_20 = W_5_20;
        double U_5_21 = W_5_21;
        double L_20_5 = (W_20_5) / U_5_5;
        double L_21_5 = (W_21_5) / U_5_5;
        double L_22_5 = (W_22_5) / U_5_5;
        double L_23_5 = (W_23_5) / U_5_5;
        double U_6_6 = W_6_6;
        double L_7_6 = (W_7_6) / U_6_6;
        double U_7_7 = W_7_7;
        double U_8_8 = W_8_8;
        double L_9_8 = (W_9_8) / U_8_8;
        double U_9_9 = W_9_9;
        double U_10_10 = W_10_10;
        double L_20_10 = (W_20_10 - L_20_5 * U_5_10) / U_10_10;
        double L_21_10 = (0.0 - L_21_5 * U_5_10) / U_10_10;
        double L_22_10 = (0.0 - L_22_5 * U_5_10) / U_10_10;
        double L_23_10 = (W_23_10 - L_23_5 * U_5_10) / U_10_10;
        double U_11_11 = W_11_11;
        double L_20_11 = (W_20_11 - L_20_5 * U_5_11) / U_11_11;
        double L_21_11 = (0.0 - L_21_5 * U_5_11) / U_11_11;
        double L_22_11 = (0.0 - L_22_5 * U_5_11) / U_11_11;
        double L_23_11 = (0.0 - L_23_5 * U_5_11) / U_11_11;
        double L_24_11 = (W_24_11) / U_11_11;
        double U_12_12 = W_12_12;
        double L_20_12 = (W_20_12 - L_20_5 * U_5_12) / U_12_12;
        double L_21_12 = (0.0 - L_21_5 * U_5_12) / U_12_12;
        double L_22_12 = (0.0 - L_22_5 * U_5_12) / U_12_12;
        double L_23_12 = (0.0 - L_23_5 * U_5_12) / U_12_12;
        double L_25_12 = (W_25_12) / U_12_12;
        double U_13_13 = W_13_13;
        double L_20_13 = (W_20_13 - L_20_5 * U_5_13) / U_13_13;
        double L_21_13 = (0.0 - L_21_5 * U_5_13) / U_13_13;
        double L_22_13 = (0.0 - L_22_5 * U_5_13) / U_13_13;
        double L_23_13 = (W_23_13 - L_23_5 * U_5_13) / U_13_13;
        double U_14_14 = W_14_14;
        double L_20_14 = (W_20_14 - L_20_5 * U_5_14) / U_14_14;
        double L_21_14 = (0.0 - L_21_5 * U_5_14) / U_14_14;
        double L_22_14 = (0.0 - L_22_5 * U_5_14) / U_14_14;
        double L_23_14 = (0.0 - L_23_5 * U_5_14) / U_14_14;
        double L_24_14 = (W_24_14) / U_14_14;
        double U_15_15 = W_15_15;
        double L_20_15 = (W_20_15 - L_20_5 * U_5_15) / U_15_15;
        double L_21_15 = (0.0 - L_21_5 * U_5_15) / U_15_15;
        double L_22_15 = (0.0 - L_22_5 * U_5_15) / U_15_15;
        double L_23_15 = (0.0 - L_23_5 * U_5_15) / U_15_15;
        double L_25_15 = (W_25_15) / U_15_15;
        double U_16_16 = W_16_16;
        double L_20_16 = (W_20_16 - L_20_5 * U_5_16) / U_16_16;
        double L_21_16 = (0.0 - L_21_5 * U_5_16) / U_16_16;
        double L_22_16 = (0.0 - L_22_5 * U_5_16) / U_16_16;
        double L_23_16 = (W_23_16 - L_23_5 * U_5_16) / U_16_16;
        double U_17_17 = W_17_17;
        double L_20_17 = (W_20_17 - L_20_5 * U_5_17) / U_17_17;
        double L_21_17 = (0.0 - L_21_5 * U_5_17) / U_17_17;
        double L_22_17 = (0.0 - L_22_5 * U_5_17) / U_17_17;
        double L_23_17 = (0.0 - L_23_5 * U_5_17) / U_17_17;
        double L_24_17 = (W_24_17) / U_17_17;
        double U_18_18 = W_18_18;
        double L_20_18 = (W_20_18 - L_20_5 * U_5_18) / U_18_18;
        double L_21_18 = (0.0 - L_21_5 * U_5_18) / U_18_18;
        double L_22_18 = (0.0 - L_22_5 * U_5_18) / U_18_18;
        double L_23_18 = (0.0 - L_23_5 * U_5_18) / U_18_18;
        double L_25_18 = (W_25_18) / U_18_18;
        double U_19_19 = W_19_19;
        double L_20_19 = (W_20_19 - L_20_5 * U_5_19) / U_19_19;
        double L_21_19 = (0.0 - L_21_5 * U_5_19) / U_19_19;
        double L_22_19 = (0.0 - L_22_5 * U_5_19) / U_19_19;
        double L_23_19 = (W_23_19 - L_23_5 * U_5_19) / U_19_19;
        double U_20_20 = W_20_20 - L_20_5 * U_5_20;
        double U_20_21 = W_20_21 - L_20_5 * U_5_21;
        double L_21_20 = (W_21_20 - L_21_5 * U_5_20) / U_20_20;
        double L_22_20 = (W_22_20 - L_22_5 * U_5_20) / U_20_20;
        double L_23_20 = (W_23_20 - L_23_5 * U_5_20) / U_20_20;
        double L_24_20 = (W_24_20) / U_20_20;
        double L_25_20 = (W_25_20) / U_20_20;
        double U_21_21 = W_21_21 - L_21_5 * U_5_21 - L_21_20 * U_20_21;
        double L_22_21 = (W_22_21 - L_22_5 * U_5_21 - L_22_20 * U_20_21) / U_21_21;
        double L_23_21 = (W_23_21 - L_23_5 * U_5_21 - L_23_20 * U_20_21) / U_21_21;
        double L_24_21 = (0.0 - L_24_20 * U_20_21) / U_21_21;
        double L_25_21 = (0.0 - L_25_20 * U_20_21) / U_21_21;
        double U_22_22 = W_22_22;
        double U_23_23 = W_23_23;
        double U_24_24 = W_24_24;
        double U_25_25 = W_25_25;

        // 4. Forward & Backward Substitution for Stage K1
        double y1_0 = F1_0;
        double y1_1 = F1_1;
        double y1_2 = F1_2;
        double y1_3 = F1_3 - L_3_0 * y1_0 - L_3_1 * y1_1 - L_3_2 * y1_2;
        double y1_4 = F1_4 - L_4_0 * y1_0 - L_4_1 * y1_1 - L_4_2 * y1_2 - L_4_3 * y1_3;
        double y1_5 = F1_5 - L_5_0 * y1_0 - L_5_2 * y1_2 - L_5_3 * y1_3 - L_5_4 * y1_4;
        double y1_6 = F1_6;
        double y1_7 = F1_7 - L_7_6 * y1_6;
        double y1_8 = F1_8;
        double y1_9 = F1_9 - L_9_8 * y1_8;
        double y1_10 = F1_10;
        double y1_11 = F1_11;
        double y1_12 = F1_12;
        double y1_13 = F1_13;
        double y1_14 = F1_14;
        double y1_15 = F1_15;
        double y1_16 = F1_16;
        double y1_17 = F1_17;
        double y1_18 = F1_18;
        double y1_19 = F1_19;
        double y1_20 = F1_20 - L_20_5 * y1_5 - L_20_10 * y1_10 - L_20_11 * y1_11 - L_20_12 * y1_12 -
                       L_20_13 * y1_13 - L_20_14 * y1_14 - L_20_15 * y1_15 - L_20_16 * y1_16 -
                       L_20_17 * y1_17 - L_20_18 * y1_18 - L_20_19 * y1_19;
        double y1_21 = F1_21 - L_21_5 * y1_5 - L_21_10 * y1_10 - L_21_11 * y1_11 - L_21_12 * y1_12 -
                       L_21_13 * y1_13 - L_21_14 * y1_14 - L_21_15 * y1_15 - L_21_16 * y1_16 -
                       L_21_17 * y1_17 - L_21_18 * y1_18 - L_21_19 * y1_19 - L_21_20 * y1_20;
        double y1_22 = F1_22 - L_22_5 * y1_5 - L_22_10 * y1_10 - L_22_11 * y1_11 - L_22_12 * y1_12 -
                       L_22_13 * y1_13 - L_22_14 * y1_14 - L_22_15 * y1_15 - L_22_16 * y1_16 -
                       L_22_17 * y1_17 - L_22_18 * y1_18 - L_22_19 * y1_19 - L_22_20 * y1_20 -
                       L_22_21 * y1_21;
        double y1_23 = F1_23 - L_23_5 * y1_5 - L_23_10 * y1_10 - L_23_11 * y1_11 - L_23_12 * y1_12 -
                       L_23_13 * y1_13 - L_23_14 * y1_14 - L_23_15 * y1_15 - L_23_16 * y1_16 -
                       L_23_17 * y1_17 - L_23_18 * y1_18 - L_23_19 * y1_19 - L_23_20 * y1_20 -
                       L_23_21 * y1_21;
        double y1_24 = F1_24 - L_24_11 * y1_11 - L_24_14 * y1_14 - L_24_17 * y1_17 -
                       L_24_20 * y1_20 - L_24_21 * y1_21;
        double y1_25 = F1_25 - L_25_12 * y1_12 - L_25_15 * y1_15 - L_25_18 * y1_18 -
                       L_25_20 * y1_20 - L_25_21 * y1_21;
        double K1_0 = F1_25 - L_25_12 * y1_12 - L_25_15 * y1_15 - L_25_18 * y1_18 -
                      L_25_20 * y1_20 - L_25_21 * y1_21;
        double K1_1 = F1_25 - L_25_12 * y1_12 - L_25_15 * y1_15 - L_25_18 * y1_18 -
                      L_25_20 * y1_20 - L_25_21 * y1_21;
        double K1_2 = F1_25 - L_25_12 * y1_12 - L_25_15 * y1_15 - L_25_18 * y1_18 -
                      L_25_20 * y1_20 - L_25_21 * y1_21;
        double K1_3 = F1_25 - L_25_12 * y1_12 - L_25_15 * y1_15 - L_25_18 * y1_18 -
                      L_25_20 * y1_20 - L_25_21 * y1_21;
        double K1_4 = F1_25 - L_25_12 * y1_12 - L_25_15 * y1_15 - L_25_18 * y1_18 -
                      L_25_20 * y1_20 - L_25_21 * y1_21;
        double K1_5 = F1_25 - L_25_12 * y1_12 - L_25_15 * y1_15 - L_25_18 * y1_18 -
                      L_25_20 * y1_20 - L_25_21 * y1_21;
        double K1_6 = F1_25 - L_25_12 * y1_12 - L_25_15 * y1_15 - L_25_18 * y1_18 -
                      L_25_20 * y1_20 - L_25_21 * y1_21;
        double K1_7 = F1_25 - L_25_12 * y1_12 - L_25_15 * y1_15 - L_25_18 * y1_18 -
                      L_25_20 * y1_20 - L_25_21 * y1_21;
        double K1_8 = F1_25 - L_25_12 * y1_12 - L_25_15 * y1_15 - L_25_18 * y1_18 -
                      L_25_20 * y1_20 - L_25_21 * y1_21;
        double K1_9 = F1_25 - L_25_12 * y1_12 - L_25_15 * y1_15 - L_25_18 * y1_18 -
                      L_25_20 * y1_20 - L_25_21 * y1_21;
        double K1_10 = F1_25 - L_25_12 * y1_12 - L_25_15 * y1_15 - L_25_18 * y1_18 -
                       L_25_20 * y1_20 - L_25_21 * y1_21;
        double K1_11 = F1_25 - L_25_12 * y1_12 - L_25_15 * y1_15 - L_25_18 * y1_18 -
                       L_25_20 * y1_20 - L_25_21 * y1_21;
        double K1_12 = F1_25 - L_25_12 * y1_12 - L_25_15 * y1_15 - L_25_18 * y1_18 -
                       L_25_20 * y1_20 - L_25_21 * y1_21;
        double K1_13 = F1_25 - L_25_12 * y1_12 - L_25_15 * y1_15 - L_25_18 * y1_18 -
                       L_25_20 * y1_20 - L_25_21 * y1_21;
        double K1_14 = F1_25 - L_25_12 * y1_12 - L_25_15 * y1_15 - L_25_18 * y1_18 -
                       L_25_20 * y1_20 - L_25_21 * y1_21;
        double K1_15 = F1_25 - L_25_12 * y1_12 - L_25_15 * y1_15 - L_25_18 * y1_18 -
                       L_25_20 * y1_20 - L_25_21 * y1_21;
        double K1_16 = F1_25 - L_25_12 * y1_12 - L_25_15 * y1_15 - L_25_18 * y1_18 -
                       L_25_20 * y1_20 - L_25_21 * y1_21;
        double K1_17 = F1_25 - L_25_12 * y1_12 - L_25_15 * y1_15 - L_25_18 * y1_18 -
                       L_25_20 * y1_20 - L_25_21 * y1_21;
        double K1_18 = F1_25 - L_25_12 * y1_12 - L_25_15 * y1_15 - L_25_18 * y1_18 -
                       L_25_20 * y1_20 - L_25_21 * y1_21;
        double K1_19 = F1_25 - L_25_12 * y1_12 - L_25_15 * y1_15 - L_25_18 * y1_18 -
                       L_25_20 * y1_20 - L_25_21 * y1_21;
        double K1_20 = F1_25 - L_25_12 * y1_12 - L_25_15 * y1_15 - L_25_18 * y1_18 -
                       L_25_20 * y1_20 - L_25_21 * y1_21;
        double K1_21 = F1_25 - L_25_12 * y1_12 - L_25_15 * y1_15 - L_25_18 * y1_18 -
                       L_25_20 * y1_20 - L_25_21 * y1_21;
        double K1_22 = F1_25 - L_25_12 * y1_12 - L_25_15 * y1_15 - L_25_18 * y1_18 -
                       L_25_20 * y1_20 - L_25_21 * y1_21;
        double K1_23 = F1_25 - L_25_12 * y1_12 - L_25_15 * y1_15 - L_25_18 * y1_18 -
                       L_25_20 * y1_20 - L_25_21 * y1_21;
        double K1_24 = F1_25 - L_25_12 * y1_12 - L_25_15 * y1_15 - L_25_18 * y1_18 -
                       L_25_20 * y1_20 - L_25_21 * y1_21;
        double K1_25 = F1_25 - L_25_12 * y1_12 - L_25_15 * y1_15 - L_25_18 * y1_18 -
                       L_25_20 * y1_20 - L_25_21 * y1_21;

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
        double Ynew_11 = state(11) + ros_A0 * K1_11;
        double Ynew_12 = state(12) + ros_A0 * K1_12;
        double Ynew_13 = state(13) + ros_A0 * K1_13;
        double Ynew_14 = state(14) + ros_A0 * K1_14;
        double Ynew_15 = state(15) + ros_A0 * K1_15;
        double Ynew_16 = state(16) + ros_A0 * K1_16;
        double Ynew_17 = state(17) + ros_A0 * K1_17;
        double Ynew_18 = state(18) + ros_A0 * K1_18;
        double Ynew_19 = state(19) + ros_A0 * K1_19;
        double Ynew_20 = state(20) + ros_A0 * K1_20;
        double Ynew_21 = state(21) + ros_A0 * K1_21;
        double Ynew_22 = state(22) + ros_A0 * K1_22;
        double Ynew_23 = state(23) + ros_A0 * K1_23;
        double Ynew_24 = state(24) + ros_A0 * K1_24;
        double Ynew_25 = state(25) + ros_A0 * K1_25;

        // 6. Stage 2 Rates (F2) & Substitution for Stage K2
        double F2_0 = -5.0442046141041832e-12 * Ynew_3 * Ynew_0 + 2.0000000000000002e-5 * Ynew_2 -
                      3.3000000000000001e-12 * Ynew_0 * Ynew_4;
        double rhs2_0 = F2_0 + (ros_C0 / dt) * K1_0;
        double F2_1 = -3.3571944693753379e-14 * Ynew_3 * Ynew_1;
        double rhs2_1 = F2_1 + (ros_C0 / dt) * K1_1;
        double F2_2 = -0.0025000000000000001 * Ynew_2 * Ynew_4 - 1.0000000000000001e-5 * Ynew_2;
        double rhs2_2 = F2_2 + (ros_C0 / dt) * K1_2;
        double F2_3 =
            -3.3571944693753379e-14 * Ynew_3 * Ynew_1 - 5.0442046141041832e-12 * Ynew_3 * Ynew_0;
        double rhs2_3 = F2_3 + (ros_C0 / dt) * K1_3;
        double F2_4 =
            3.3571944693753379e-14 * Ynew_3 * Ynew_1 + 5.0442046141041832e-12 * Ynew_3 * Ynew_0 -
            2.5000000000000001e-5 * Ynew_10 * Ynew_4 - 2.5000000000000001e-5 * Ynew_11 * Ynew_4 -
            2.5000000000000001e-5 * Ynew_12 * Ynew_4 - 2.5000000000000001e-5 * Ynew_13 * Ynew_4 -
            2.5000000000000001e-5 * Ynew_14 * Ynew_4 - 0.0025000000000000001 * Ynew_2 * Ynew_4 -
            3.3000000000000001e-12 * Ynew_0 * Ynew_4 - 0.00025000000000000001 * Ynew_4 * Ynew_15 -
            0.00025000000000000001 * Ynew_4 * Ynew_16 - 0.00025000000000000001 * Ynew_4 * Ynew_17 -
            0.00025000000000000001 * Ynew_4 * Ynew_18 - 0.00025000000000000001 * Ynew_4 * Ynew_19;
        double rhs2_4 = F2_4 + (ros_C0 / dt) * K1_4;
        double F2_5 =
            2.5000000000000001e-5 * Ynew_10 * Ynew_4 + 2.5000000000000001e-5 * Ynew_11 * Ynew_4 +
            2.5000000000000001e-5 * Ynew_12 * Ynew_4 + 2.5000000000000001e-5 * Ynew_13 * Ynew_4 +
            2.5000000000000001e-5 * Ynew_14 * Ynew_4 + 0.0025000000000000001 * Ynew_2 * Ynew_4 -
            1.0 * Ynew_20 * Ynew_21 * Ynew_5 * Rate_27 + 3.3000000000000001e-12 * Ynew_0 * Ynew_4 +
            0.00025000000000000001 * Ynew_4 * Ynew_15 + 0.00025000000000000001 * Ynew_4 * Ynew_16 +
            0.00025000000000000001 * Ynew_4 * Ynew_17 + 0.00025000000000000001 * Ynew_4 * Ynew_18 +
            0.00025000000000000001 * Ynew_4 * Ynew_19;
        double rhs2_5 = F2_5 + (ros_C0 / dt) * K1_5;
        double F2_6 = -5.0000000000000004e-6 * Ynew_6;
        double rhs2_6 = F2_6 + (ros_C0 / dt) * K1_6;
        double F2_7 = 5.0000000000000004e-6 * Ynew_6;
        double rhs2_7 = F2_7 + (ros_C0 / dt) * K1_7;
        double F2_8 = -5.0000000000000004e-6 * Ynew_8;
        double rhs2_8 = F2_8 + (ros_C0 / dt) * K1_8;
        double F2_9 = 5.0000000000000004e-6 * Ynew_8;
        double rhs2_9 = F2_9 + (ros_C0 / dt) * K1_9;
        double F2_10 = 0.0;
        double rhs2_10 = F2_10 + (ros_C0 / dt) * K1_10;
        double F2_11 = 0.0;
        double rhs2_11 = F2_11 + (ros_C0 / dt) * K1_11;
        double F2_12 = 0.0;
        double rhs2_12 = F2_12 + (ros_C0 / dt) * K1_12;
        double F2_13 = 0.0;
        double rhs2_13 = F2_13 + (ros_C0 / dt) * K1_13;
        double F2_14 = 0.0;
        double rhs2_14 = F2_14 + (ros_C0 / dt) * K1_14;
        double F2_15 = 0.0;
        double rhs2_15 = F2_15 + (ros_C0 / dt) * K1_15;
        double F2_16 = 0.0;
        double rhs2_16 = F2_16 + (ros_C0 / dt) * K1_16;
        double F2_17 = 0.0;
        double rhs2_17 = F2_17 + (ros_C0 / dt) * K1_17;
        double F2_18 = 0.0;
        double rhs2_18 = F2_18 + (ros_C0 / dt) * K1_18;
        double F2_19 = 0.0;
        double rhs2_19 = F2_19 + (ros_C0 / dt) * K1_19;
        double F2_20 =
            -0.025000000000000001 * Ynew_10 * Ynew_20 - 0.025000000000000001 * Ynew_11 * Ynew_20 -
            0.025000000000000001 * Ynew_12 * Ynew_20 - 0.025000000000000001 * Ynew_13 * Ynew_20 -
            0.025000000000000001 * Ynew_14 * Ynew_20 - 1.0 * Ynew_20 * Ynew_21 * Ynew_5 * Rate_27 -
            0.025000000000000001 * Ynew_20 * Ynew_15 - 0.025000000000000001 * Ynew_20 * Ynew_16 -
            0.025000000000000001 * Ynew_20 * Ynew_17 - 0.025000000000000001 * Ynew_20 * Ynew_18 -
            0.025000000000000001 * Ynew_20 * Ynew_19;
        double rhs2_20 = F2_20 + (ros_C0 / dt) * K1_20;
        double F2_21 = -1.0 * Ynew_20 * Ynew_21 * Ynew_5 * Rate_27;
        double rhs2_21 = F2_21 + (ros_C0 / dt) * K1_21;
        double F2_22 = 1.0 * Ynew_20 * Ynew_21 * Ynew_5 * Rate_27;
        double rhs2_22 = F2_22 + (ros_C0 / dt) * K1_22;
        double F2_23 =
            0.025000000000000001 * Ynew_10 * Ynew_20 + 0.025000000000000001 * Ynew_13 * Ynew_20 +
            1.0 * Ynew_20 * Ynew_21 * Ynew_5 * Rate_27 + 0.025000000000000001 * Ynew_20 * Ynew_16 +
            0.025000000000000001 * Ynew_20 * Ynew_19;
        double rhs2_23 = F2_23 + (ros_C0 / dt) * K1_23;
        double F2_24 = 0.025000000000000001 * Ynew_11 * Ynew_20 +
                       0.025000000000000001 * Ynew_14 * Ynew_20 +
                       0.025000000000000001 * Ynew_20 * Ynew_17;
        double rhs2_24 = F2_24 + (ros_C0 / dt) * K1_24;
        double F2_25 = 0.025000000000000001 * Ynew_12 * Ynew_20 +
                       0.025000000000000001 * Ynew_20 * Ynew_15 +
                       0.025000000000000001 * Ynew_20 * Ynew_18;
        double rhs2_25 = F2_25 + (ros_C0 / dt) * K1_25;
        double y2_0 = rhs2_0;
        double y2_1 = rhs2_1;
        double y2_2 = rhs2_2;
        double y2_3 = rhs2_3 - L_3_0 * y2_0 - L_3_1 * y2_1 - L_3_2 * y2_2;
        double y2_4 = rhs2_4 - L_4_0 * y2_0 - L_4_1 * y2_1 - L_4_2 * y2_2 - L_4_3 * y2_3;
        double y2_5 = rhs2_5 - L_5_0 * y2_0 - L_5_2 * y2_2 - L_5_3 * y2_3 - L_5_4 * y2_4;
        double y2_6 = rhs2_6;
        double y2_7 = rhs2_7 - L_7_6 * y2_6;
        double y2_8 = rhs2_8;
        double y2_9 = rhs2_9 - L_9_8 * y2_8;
        double y2_10 = rhs2_10;
        double y2_11 = rhs2_11;
        double y2_12 = rhs2_12;
        double y2_13 = rhs2_13;
        double y2_14 = rhs2_14;
        double y2_15 = rhs2_15;
        double y2_16 = rhs2_16;
        double y2_17 = rhs2_17;
        double y2_18 = rhs2_18;
        double y2_19 = rhs2_19;
        double y2_20 = rhs2_20 - L_20_5 * y2_5 - L_20_10 * y2_10 - L_20_11 * y2_11 -
                       L_20_12 * y2_12 - L_20_13 * y2_13 - L_20_14 * y2_14 - L_20_15 * y2_15 -
                       L_20_16 * y2_16 - L_20_17 * y2_17 - L_20_18 * y2_18 - L_20_19 * y2_19;
        double y2_21 = rhs2_21 - L_21_5 * y2_5 - L_21_10 * y2_10 - L_21_11 * y2_11 -
                       L_21_12 * y2_12 - L_21_13 * y2_13 - L_21_14 * y2_14 - L_21_15 * y2_15 -
                       L_21_16 * y2_16 - L_21_17 * y2_17 - L_21_18 * y2_18 - L_21_19 * y2_19 -
                       L_21_20 * y2_20;
        double y2_22 = rhs2_22 - L_22_5 * y2_5 - L_22_10 * y2_10 - L_22_11 * y2_11 -
                       L_22_12 * y2_12 - L_22_13 * y2_13 - L_22_14 * y2_14 - L_22_15 * y2_15 -
                       L_22_16 * y2_16 - L_22_17 * y2_17 - L_22_18 * y2_18 - L_22_19 * y2_19 -
                       L_22_20 * y2_20 - L_22_21 * y2_21;
        double y2_23 = rhs2_23 - L_23_5 * y2_5 - L_23_10 * y2_10 - L_23_11 * y2_11 -
                       L_23_12 * y2_12 - L_23_13 * y2_13 - L_23_14 * y2_14 - L_23_15 * y2_15 -
                       L_23_16 * y2_16 - L_23_17 * y2_17 - L_23_18 * y2_18 - L_23_19 * y2_19 -
                       L_23_20 * y2_20 - L_23_21 * y2_21;
        double y2_24 = rhs2_24 - L_24_11 * y2_11 - L_24_14 * y2_14 - L_24_17 * y2_17 -
                       L_24_20 * y2_20 - L_24_21 * y2_21;
        double y2_25 = rhs2_25 - L_25_12 * y2_12 - L_25_15 * y2_15 - L_25_18 * y2_18 -
                       L_25_20 * y2_20 - L_25_21 * y2_21;
        double K2_0 = (y2_0 - U_0_2 * K2_2 - U_0_3 * K2_3 - U_0_4 * K2_4) / U_0_0;
        double K2_1 = (y2_1 - U_1_3 * K2_3) / U_1_1;
        double K2_2 = (y2_2 - U_2_4 * K2_4) / U_2_2;
        double K2_3 = (y2_3 - U_3_4 * K2_4) / U_3_3;
        double K2_4 = (y2_4 - U_4_10 * K2_10 - U_4_11 * K2_11 - U_4_12 * K2_12 - U_4_13 * K2_13 -
                       U_4_14 * K2_14 - U_4_15 * K2_15 - U_4_16 * K2_16 - U_4_17 * K2_17 -
                       U_4_18 * K2_18 - U_4_19 * K2_19) /
                      U_4_4;
        double K2_5 = (y2_5 - U_5_10 * K2_10 - U_5_11 * K2_11 - U_5_12 * K2_12 - U_5_13 * K2_13 -
                       U_5_14 * K2_14 - U_5_15 * K2_15 - U_5_16 * K2_16 - U_5_17 * K2_17 -
                       U_5_18 * K2_18 - U_5_19 * K2_19 - U_5_20 * K2_20 - U_5_21 * K2_21) /
                      U_5_5;
        double K2_6 = y2_6 / U_6_6;
        double K2_7 = y2_7 / U_7_7;
        double K2_8 = y2_8 / U_8_8;
        double K2_9 = y2_9 / U_9_9;
        double K2_10 = y2_10 / U_10_10;
        double K2_11 = y2_11 / U_11_11;
        double K2_12 = y2_12 / U_12_12;
        double K2_13 = y2_13 / U_13_13;
        double K2_14 = y2_14 / U_14_14;
        double K2_15 = y2_15 / U_15_15;
        double K2_16 = y2_16 / U_16_16;
        double K2_17 = y2_17 / U_17_17;
        double K2_18 = y2_18 / U_18_18;
        double K2_19 = y2_19 / U_19_19;
        double K2_20 = (y2_20 - U_20_21 * K2_21) / U_20_20;
        double K2_21 = y2_21 / U_21_21;
        double K2_22 = y2_22 / U_22_22;
        double K2_23 = y2_23 / U_23_23;
        double K2_24 = y2_24 / U_24_24;
        double K2_25 = y2_25 / U_25_25;

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
        state(11) += ros_M0 * K1_11 + ros_M1 * K2_11;
        state(12) += ros_M0 * K1_12 + ros_M1 * K2_12;
        state(13) += ros_M0 * K1_13 + ros_M1 * K2_13;
        state(14) += ros_M0 * K1_14 + ros_M1 * K2_14;
        state(15) += ros_M0 * K1_15 + ros_M1 * K2_15;
        state(16) += ros_M0 * K1_16 + ros_M1 * K2_16;
        state(17) += ros_M0 * K1_17 + ros_M1 * K2_17;
        state(18) += ros_M0 * K1_18 + ros_M1 * K2_18;
        state(19) += ros_M0 * K1_19 + ros_M1 * K2_19;
        state(20) += ros_M0 * K1_20 + ros_M1 * K2_20;
        state(21) += ros_M0 * K1_21 + ros_M1 * K2_21;
        state(22) += ros_M0 * K1_22 + ros_M1 * K2_22;
        state(23) += ros_M0 * K1_23 + ros_M1 * K2_23;
        state(24) += ros_M0 * K1_24 + ros_M1 * K2_24;
        state(25) += ros_M0 * K1_25 + ros_M1 * K2_25;
    }
};
}  // namespace mkpp
