#pragma once
#include <Kokkos_Core.hpp>
// Generated solver for gocart
// Hysteresis/Spline Continuous Transition: true
namespace mkpp {
  // Pure Kokkos abstractions (no raw pragmas allowed)
  // Bidirectional Host Interface (Zero-Copy)
  using concentrations_view_t = Kokkos::View<double****, Kokkos::LayoutLeft, Kokkos::MemoryUnmanaged>;
  template<typename DeviceType>
  struct SolverKernels {
      template <class StateView, class RateView>
      KOKKOS_INLINE_FUNCTION void compute_rates(const StateView& state, RateView& F_block, const double* jvals) const {
          F_block(0) = -5.0442046141041832e-12*state(3)*state(0) + 2.0*state(2)*jvals[0] - 3.3000000000000001e-12*state(0)*state(4);
          F_block(1) = -3.3571944693753379e-14*state(3)*state(1);
          F_block(2) = -0.0025000000000000001*state(2)*state(4) - 1.0*state(2)*jvals[0];
          F_block(3) = -3.3571944693753379e-14*state(3)*state(1) - 5.0442046141041832e-12*state(3)*state(0);
          F_block(4) = 3.3571944693753379e-14*state(3)*state(1) + 5.0442046141041832e-12*state(3)*state(0) - 2.5000000000000001e-5*state(10)*state(4) - 2.5000000000000001e-5*state(11)*state(4) - 2.5000000000000001e-5*state(12)*state(4) - 2.5000000000000001e-5*state(13)*state(4) - 2.5000000000000001e-5*state(14)*state(4) - 0.0025000000000000001*state(2)*state(4) - 3.3000000000000001e-12*state(0)*state(4) - 0.00025000000000000001*state(4)*state(15) - 0.00025000000000000001*state(4)*state(16) - 0.00025000000000000001*state(4)*state(17) - 0.00025000000000000001*state(4)*state(18) - 0.00025000000000000001*state(4)*state(19);
          F_block(5) = 2.5000000000000001e-5*state(10)*state(4) + 2.5000000000000001e-5*state(11)*state(4) + 2.5000000000000001e-5*state(12)*state(4) + 2.5000000000000001e-5*state(13)*state(4) + 2.5000000000000001e-5*state(14)*state(4) + 0.0025000000000000001*state(2)*state(4) - 1.0*state(20)*state(21)*state(5)*jvals[27] + 3.3000000000000001e-12*state(0)*state(4) + 0.00025000000000000001*state(4)*state(15) + 0.00025000000000000001*state(4)*state(16) + 0.00025000000000000001*state(4)*state(17) + 0.00025000000000000001*state(4)*state(18) + 0.00025000000000000001*state(4)*state(19);
          F_block(6) = -5.0000000000000004e-6*state(6);
          F_block(7) = 5.0000000000000004e-6*state(6);
          F_block(8) = -5.0000000000000004e-6*state(8);
          F_block(9) = 5.0000000000000004e-6*state(8);
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
          F_block(20) = -0.025000000000000001*state(10)*state(20) - 0.025000000000000001*state(11)*state(20) - 0.025000000000000001*state(12)*state(20) - 0.025000000000000001*state(13)*state(20) - 0.025000000000000001*state(14)*state(20) - 1.0*state(20)*state(21)*state(5)*jvals[27] - 0.025000000000000001*state(20)*state(15) - 0.025000000000000001*state(20)*state(16) - 0.025000000000000001*state(20)*state(17) - 0.025000000000000001*state(20)*state(18) - 0.025000000000000001*state(20)*state(19);
          F_block(21) = -1.0*state(20)*state(21)*state(5)*jvals[27];
          F_block(22) = 1.0*state(20)*state(21)*state(5)*jvals[27];
          F_block(23) = 0.025000000000000001*state(10)*state(20) + 0.025000000000000001*state(13)*state(20) + 1.0*state(20)*state(21)*state(5)*jvals[27] + 0.025000000000000001*state(20)*state(16) + 0.025000000000000001*state(20)*state(19);
          F_block(24) = 0.025000000000000001*state(11)*state(20) + 0.025000000000000001*state(14)*state(20) + 0.025000000000000001*state(20)*state(17);
          F_block(25) = 0.025000000000000001*state(12)*state(20) + 0.025000000000000001*state(20)*state(15) + 0.025000000000000001*state(20)*state(18);
      }

      template <class StateView, class JacView>
      KOKKOS_INLINE_FUNCTION void compute_jacobian(const StateView& state, JacView& J_block, const double* jvals) const {
          J_block(0, 0) = -5.0442046141041832e-12*state(3) - 3.3000000000000001e-12*state(4);
          J_block(0, 2) = 2.0*jvals[0];
          J_block(0, 3) = -5.0442046141041832e-12*state(0);
          J_block(0, 4) = -3.3000000000000001e-12*state(0);
          J_block(1, 1) = -3.3571944693753379e-14*state(3);
          J_block(1, 3) = -3.3571944693753379e-14*state(1);
          J_block(2, 2) = -0.0025000000000000001*state(4) - 1.0*jvals[0];
          J_block(2, 4) = -0.0025000000000000001*state(2);
          J_block(3, 0) = -5.0442046141041832e-12*state(3);
          J_block(3, 1) = -3.3571944693753379e-14*state(3);
          J_block(3, 3) = -3.3571944693753379e-14*state(1) - 5.0442046141041832e-12*state(0);
          J_block(4, 0) = 5.0442046141041832e-12*state(3) - 3.3000000000000001e-12*state(4);
          J_block(4, 1) = 3.3571944693753379e-14*state(3);
          J_block(4, 2) = -0.0025000000000000001*state(4);
          J_block(4, 3) = 3.3571944693753379e-14*state(1) + 5.0442046141041832e-12*state(0);
          J_block(4, 4) = -2.5000000000000001e-5*state(10) - 2.5000000000000001e-5*state(11) - 2.5000000000000001e-5*state(12) - 2.5000000000000001e-5*state(13) - 2.5000000000000001e-5*state(14) - 0.0025000000000000001*state(2) - 3.3000000000000001e-12*state(0) - 0.00025000000000000001*state(15) - 0.00025000000000000001*state(16) - 0.00025000000000000001*state(17) - 0.00025000000000000001*state(18) - 0.00025000000000000001*state(19);
          J_block(4, 10) = -2.5000000000000001e-5*state(4);
          J_block(4, 11) = -2.5000000000000001e-5*state(4);
          J_block(4, 12) = -2.5000000000000001e-5*state(4);
          J_block(4, 13) = -2.5000000000000001e-5*state(4);
          J_block(4, 14) = -2.5000000000000001e-5*state(4);
          J_block(4, 15) = -0.00025000000000000001*state(4);
          J_block(4, 16) = -0.00025000000000000001*state(4);
          J_block(4, 17) = -0.00025000000000000001*state(4);
          J_block(4, 18) = -0.00025000000000000001*state(4);
          J_block(4, 19) = -0.00025000000000000001*state(4);
          J_block(5, 0) = 3.3000000000000001e-12*state(4);
          J_block(5, 2) = 0.0025000000000000001*state(4);
          J_block(5, 4) = 2.5000000000000001e-5*state(10) + 2.5000000000000001e-5*state(11) + 2.5000000000000001e-5*state(12) + 2.5000000000000001e-5*state(13) + 2.5000000000000001e-5*state(14) + 0.0025000000000000001*state(2) + 3.3000000000000001e-12*state(0) + 0.00025000000000000001*state(15) + 0.00025000000000000001*state(16) + 0.00025000000000000001*state(17) + 0.00025000000000000001*state(18) + 0.00025000000000000001*state(19);
          J_block(5, 5) = -1.0*state(20)*state(21)*jvals[27];
          J_block(5, 10) = 2.5000000000000001e-5*state(4);
          J_block(5, 11) = 2.5000000000000001e-5*state(4);
          J_block(5, 12) = 2.5000000000000001e-5*state(4);
          J_block(5, 13) = 2.5000000000000001e-5*state(4);
          J_block(5, 14) = 2.5000000000000001e-5*state(4);
          J_block(5, 15) = 0.00025000000000000001*state(4);
          J_block(5, 16) = 0.00025000000000000001*state(4);
          J_block(5, 17) = 0.00025000000000000001*state(4);
          J_block(5, 18) = 0.00025000000000000001*state(4);
          J_block(5, 19) = 0.00025000000000000001*state(4);
          J_block(5, 20) = -1.0*state(21)*state(5)*jvals[27];
          J_block(5, 21) = -1.0*state(20)*state(5)*jvals[27];
          J_block(6, 6) = -5.0000000000000004e-6;
          J_block(7, 6) = 5.0000000000000004e-6;
          J_block(8, 8) = -5.0000000000000004e-6;
          J_block(9, 8) = 5.0000000000000004e-6;
          J_block(20, 5) = -1.0*state(20)*state(21)*jvals[27];
          J_block(20, 10) = -0.025000000000000001*state(20);
          J_block(20, 11) = -0.025000000000000001*state(20);
          J_block(20, 12) = -0.025000000000000001*state(20);
          J_block(20, 13) = -0.025000000000000001*state(20);
          J_block(20, 14) = -0.025000000000000001*state(20);
          J_block(20, 15) = -0.025000000000000001*state(20);
          J_block(20, 16) = -0.025000000000000001*state(20);
          J_block(20, 17) = -0.025000000000000001*state(20);
          J_block(20, 18) = -0.025000000000000001*state(20);
          J_block(20, 19) = -0.025000000000000001*state(20);
          J_block(20, 20) = -0.025000000000000001*state(10) - 0.025000000000000001*state(11) - 0.025000000000000001*state(12) - 0.025000000000000001*state(13) - 0.025000000000000001*state(14) - 1.0*state(21)*state(5)*jvals[27] - 0.025000000000000001*state(15) - 0.025000000000000001*state(16) - 0.025000000000000001*state(17) - 0.025000000000000001*state(18) - 0.025000000000000001*state(19);
          J_block(20, 21) = -1.0*state(20)*state(5)*jvals[27];
          J_block(21, 5) = -1.0*state(20)*state(21)*jvals[27];
          J_block(21, 20) = -1.0*state(21)*state(5)*jvals[27];
          J_block(21, 21) = -1.0*state(20)*state(5)*jvals[27];
          J_block(22, 5) = 1.0*state(20)*state(21)*jvals[27];
          J_block(22, 20) = 1.0*state(21)*state(5)*jvals[27];
          J_block(22, 21) = 1.0*state(20)*state(5)*jvals[27];
          J_block(23, 5) = 1.0*state(20)*state(21)*jvals[27];
          J_block(23, 10) = 0.025000000000000001*state(20);
          J_block(23, 13) = 0.025000000000000001*state(20);
          J_block(23, 16) = 0.025000000000000001*state(20);
          J_block(23, 19) = 0.025000000000000001*state(20);
          J_block(23, 20) = 0.025000000000000001*state(10) + 0.025000000000000001*state(13) + 1.0*state(21)*state(5)*jvals[27] + 0.025000000000000001*state(16) + 0.025000000000000001*state(19);
          J_block(23, 21) = 1.0*state(20)*state(5)*jvals[27];
          J_block(24, 11) = 0.025000000000000001*state(20);
          J_block(24, 14) = 0.025000000000000001*state(20);
          J_block(24, 17) = 0.025000000000000001*state(20);
          J_block(24, 20) = 0.025000000000000001*state(11) + 0.025000000000000001*state(14) + 0.025000000000000001*state(17);
          J_block(25, 12) = 0.025000000000000001*state(20);
          J_block(25, 15) = 0.025000000000000001*state(20);
          J_block(25, 18) = 0.025000000000000001*state(20);
          J_block(25, 20) = 0.025000000000000001*state(12) + 0.025000000000000001*state(15) + 0.025000000000000001*state(18);
      }

      template <class StateView, class JacView>
      KOKKOS_INLINE_FUNCTION void compute_adjoint(const StateView& state, JacView& J_adj_block, const double* jvals) const {
          J_adj_block(0, 0) = -5.0442046141041832e-12*state(3) - 3.3000000000000001e-12*state(4);
          J_adj_block(0, 3) = -5.0442046141041832e-12*state(3);
          J_adj_block(0, 4) = 5.0442046141041832e-12*state(3) - 3.3000000000000001e-12*state(4);
          J_adj_block(0, 5) = 3.3000000000000001e-12*state(4);
          J_adj_block(1, 1) = -3.3571944693753379e-14*state(3);
          J_adj_block(1, 3) = -3.3571944693753379e-14*state(3);
          J_adj_block(1, 4) = 3.3571944693753379e-14*state(3);
          J_adj_block(2, 0) = 2.0*jvals[0];
          J_adj_block(2, 2) = -0.0025000000000000001*state(4) - 1.0*jvals[0];
          J_adj_block(2, 4) = -0.0025000000000000001*state(4);
          J_adj_block(2, 5) = 0.0025000000000000001*state(4);
          J_adj_block(3, 0) = -5.0442046141041832e-12*state(0);
          J_adj_block(3, 1) = -3.3571944693753379e-14*state(1);
          J_adj_block(3, 3) = -3.3571944693753379e-14*state(1) - 5.0442046141041832e-12*state(0);
          J_adj_block(3, 4) = 3.3571944693753379e-14*state(1) + 5.0442046141041832e-12*state(0);
          J_adj_block(4, 0) = -3.3000000000000001e-12*state(0);
          J_adj_block(4, 2) = -0.0025000000000000001*state(2);
          J_adj_block(4, 4) = -2.5000000000000001e-5*state(10) - 2.5000000000000001e-5*state(11) - 2.5000000000000001e-5*state(12) - 2.5000000000000001e-5*state(13) - 2.5000000000000001e-5*state(14) - 0.0025000000000000001*state(2) - 3.3000000000000001e-12*state(0) - 0.00025000000000000001*state(15) - 0.00025000000000000001*state(16) - 0.00025000000000000001*state(17) - 0.00025000000000000001*state(18) - 0.00025000000000000001*state(19);
          J_adj_block(4, 5) = 2.5000000000000001e-5*state(10) + 2.5000000000000001e-5*state(11) + 2.5000000000000001e-5*state(12) + 2.5000000000000001e-5*state(13) + 2.5000000000000001e-5*state(14) + 0.0025000000000000001*state(2) + 3.3000000000000001e-12*state(0) + 0.00025000000000000001*state(15) + 0.00025000000000000001*state(16) + 0.00025000000000000001*state(17) + 0.00025000000000000001*state(18) + 0.00025000000000000001*state(19);
          J_adj_block(5, 5) = -1.0*state(20)*state(21)*jvals[27];
          J_adj_block(5, 20) = -1.0*state(20)*state(21)*jvals[27];
          J_adj_block(5, 21) = -1.0*state(20)*state(21)*jvals[27];
          J_adj_block(5, 22) = 1.0*state(20)*state(21)*jvals[27];
          J_adj_block(5, 23) = 1.0*state(20)*state(21)*jvals[27];
          J_adj_block(6, 6) = -5.0000000000000004e-6;
          J_adj_block(6, 7) = 5.0000000000000004e-6;
          J_adj_block(8, 8) = -5.0000000000000004e-6;
          J_adj_block(8, 9) = 5.0000000000000004e-6;
          J_adj_block(10, 4) = -2.5000000000000001e-5*state(4);
          J_adj_block(10, 5) = 2.5000000000000001e-5*state(4);
          J_adj_block(10, 20) = -0.025000000000000001*state(20);
          J_adj_block(10, 23) = 0.025000000000000001*state(20);
          J_adj_block(11, 4) = -2.5000000000000001e-5*state(4);
          J_adj_block(11, 5) = 2.5000000000000001e-5*state(4);
          J_adj_block(11, 20) = -0.025000000000000001*state(20);
          J_adj_block(11, 24) = 0.025000000000000001*state(20);
          J_adj_block(12, 4) = -2.5000000000000001e-5*state(4);
          J_adj_block(12, 5) = 2.5000000000000001e-5*state(4);
          J_adj_block(12, 20) = -0.025000000000000001*state(20);
          J_adj_block(12, 25) = 0.025000000000000001*state(20);
          J_adj_block(13, 4) = -2.5000000000000001e-5*state(4);
          J_adj_block(13, 5) = 2.5000000000000001e-5*state(4);
          J_adj_block(13, 20) = -0.025000000000000001*state(20);
          J_adj_block(13, 23) = 0.025000000000000001*state(20);
          J_adj_block(14, 4) = -2.5000000000000001e-5*state(4);
          J_adj_block(14, 5) = 2.5000000000000001e-5*state(4);
          J_adj_block(14, 20) = -0.025000000000000001*state(20);
          J_adj_block(14, 24) = 0.025000000000000001*state(20);
          J_adj_block(15, 4) = -0.00025000000000000001*state(4);
          J_adj_block(15, 5) = 0.00025000000000000001*state(4);
          J_adj_block(15, 20) = -0.025000000000000001*state(20);
          J_adj_block(15, 25) = 0.025000000000000001*state(20);
          J_adj_block(16, 4) = -0.00025000000000000001*state(4);
          J_adj_block(16, 5) = 0.00025000000000000001*state(4);
          J_adj_block(16, 20) = -0.025000000000000001*state(20);
          J_adj_block(16, 23) = 0.025000000000000001*state(20);
          J_adj_block(17, 4) = -0.00025000000000000001*state(4);
          J_adj_block(17, 5) = 0.00025000000000000001*state(4);
          J_adj_block(17, 20) = -0.025000000000000001*state(20);
          J_adj_block(17, 24) = 0.025000000000000001*state(20);
          J_adj_block(18, 4) = -0.00025000000000000001*state(4);
          J_adj_block(18, 5) = 0.00025000000000000001*state(4);
          J_adj_block(18, 20) = -0.025000000000000001*state(20);
          J_adj_block(18, 25) = 0.025000000000000001*state(20);
          J_adj_block(19, 4) = -0.00025000000000000001*state(4);
          J_adj_block(19, 5) = 0.00025000000000000001*state(4);
          J_adj_block(19, 20) = -0.025000000000000001*state(20);
          J_adj_block(19, 23) = 0.025000000000000001*state(20);
          J_adj_block(20, 5) = -1.0*state(21)*state(5)*jvals[27];
          J_adj_block(20, 20) = -0.025000000000000001*state(10) - 0.025000000000000001*state(11) - 0.025000000000000001*state(12) - 0.025000000000000001*state(13) - 0.025000000000000001*state(14) - 1.0*state(21)*state(5)*jvals[27] - 0.025000000000000001*state(15) - 0.025000000000000001*state(16) - 0.025000000000000001*state(17) - 0.025000000000000001*state(18) - 0.025000000000000001*state(19);
          J_adj_block(20, 21) = -1.0*state(21)*state(5)*jvals[27];
          J_adj_block(20, 22) = 1.0*state(21)*state(5)*jvals[27];
          J_adj_block(20, 23) = 0.025000000000000001*state(10) + 0.025000000000000001*state(13) + 1.0*state(21)*state(5)*jvals[27] + 0.025000000000000001*state(16) + 0.025000000000000001*state(19);
          J_adj_block(20, 24) = 0.025000000000000001*state(11) + 0.025000000000000001*state(14) + 0.025000000000000001*state(17);
          J_adj_block(20, 25) = 0.025000000000000001*state(12) + 0.025000000000000001*state(15) + 0.025000000000000001*state(18);
          J_adj_block(21, 5) = -1.0*state(20)*state(5)*jvals[27];
          J_adj_block(21, 20) = -1.0*state(20)*state(5)*jvals[27];
          J_adj_block(21, 21) = -1.0*state(20)*state(5)*jvals[27];
          J_adj_block(21, 22) = 1.0*state(20)*state(5)*jvals[27];
          J_adj_block(21, 23) = 1.0*state(20)*state(5)*jvals[27];
      }

      template <class StateView, class DeltaView, class RateView>
      KOKKOS_INLINE_FUNCTION void compute_tlm(const StateView& state, const DeltaView& delta_C, RateView& dF_block, const double* jvals) const {
          dF_block(0) = 0.0;
          dF_block(0) += (-5.0442046141041832e-12*state(3) - 3.3000000000000001e-12*state(4)) * delta_C(0);
          dF_block(0) += (2.0*jvals[0]) * delta_C(2);
          dF_block(0) += (-5.0442046141041832e-12*state(0)) * delta_C(3);
          dF_block(0) += (-3.3000000000000001e-12*state(0)) * delta_C(4);
          dF_block(1) = 0.0;
          dF_block(1) += (-3.3571944693753379e-14*state(3)) * delta_C(1);
          dF_block(1) += (-3.3571944693753379e-14*state(1)) * delta_C(3);
          dF_block(2) = 0.0;
          dF_block(2) += (-0.0025000000000000001*state(4) - 1.0*jvals[0]) * delta_C(2);
          dF_block(2) += (-0.0025000000000000001*state(2)) * delta_C(4);
          dF_block(3) = 0.0;
          dF_block(3) += (-5.0442046141041832e-12*state(3)) * delta_C(0);
          dF_block(3) += (-3.3571944693753379e-14*state(3)) * delta_C(1);
          dF_block(3) += (-3.3571944693753379e-14*state(1) - 5.0442046141041832e-12*state(0)) * delta_C(3);
          dF_block(4) = 0.0;
          dF_block(4) += (5.0442046141041832e-12*state(3) - 3.3000000000000001e-12*state(4)) * delta_C(0);
          dF_block(4) += (3.3571944693753379e-14*state(3)) * delta_C(1);
          dF_block(4) += (-0.0025000000000000001*state(4)) * delta_C(2);
          dF_block(4) += (3.3571944693753379e-14*state(1) + 5.0442046141041832e-12*state(0)) * delta_C(3);
          dF_block(4) += (-2.5000000000000001e-5*state(10) - 2.5000000000000001e-5*state(11) - 2.5000000000000001e-5*state(12) - 2.5000000000000001e-5*state(13) - 2.5000000000000001e-5*state(14) - 0.0025000000000000001*state(2) - 3.3000000000000001e-12*state(0) - 0.00025000000000000001*state(15) - 0.00025000000000000001*state(16) - 0.00025000000000000001*state(17) - 0.00025000000000000001*state(18) - 0.00025000000000000001*state(19)) * delta_C(4);
          dF_block(4) += (-2.5000000000000001e-5*state(4)) * delta_C(10);
          dF_block(4) += (-2.5000000000000001e-5*state(4)) * delta_C(11);
          dF_block(4) += (-2.5000000000000001e-5*state(4)) * delta_C(12);
          dF_block(4) += (-2.5000000000000001e-5*state(4)) * delta_C(13);
          dF_block(4) += (-2.5000000000000001e-5*state(4)) * delta_C(14);
          dF_block(4) += (-0.00025000000000000001*state(4)) * delta_C(15);
          dF_block(4) += (-0.00025000000000000001*state(4)) * delta_C(16);
          dF_block(4) += (-0.00025000000000000001*state(4)) * delta_C(17);
          dF_block(4) += (-0.00025000000000000001*state(4)) * delta_C(18);
          dF_block(4) += (-0.00025000000000000001*state(4)) * delta_C(19);
          dF_block(5) = 0.0;
          dF_block(5) += (3.3000000000000001e-12*state(4)) * delta_C(0);
          dF_block(5) += (0.0025000000000000001*state(4)) * delta_C(2);
          dF_block(5) += (2.5000000000000001e-5*state(10) + 2.5000000000000001e-5*state(11) + 2.5000000000000001e-5*state(12) + 2.5000000000000001e-5*state(13) + 2.5000000000000001e-5*state(14) + 0.0025000000000000001*state(2) + 3.3000000000000001e-12*state(0) + 0.00025000000000000001*state(15) + 0.00025000000000000001*state(16) + 0.00025000000000000001*state(17) + 0.00025000000000000001*state(18) + 0.00025000000000000001*state(19)) * delta_C(4);
          dF_block(5) += (-1.0*state(20)*state(21)*jvals[27]) * delta_C(5);
          dF_block(5) += (2.5000000000000001e-5*state(4)) * delta_C(10);
          dF_block(5) += (2.5000000000000001e-5*state(4)) * delta_C(11);
          dF_block(5) += (2.5000000000000001e-5*state(4)) * delta_C(12);
          dF_block(5) += (2.5000000000000001e-5*state(4)) * delta_C(13);
          dF_block(5) += (2.5000000000000001e-5*state(4)) * delta_C(14);
          dF_block(5) += (0.00025000000000000001*state(4)) * delta_C(15);
          dF_block(5) += (0.00025000000000000001*state(4)) * delta_C(16);
          dF_block(5) += (0.00025000000000000001*state(4)) * delta_C(17);
          dF_block(5) += (0.00025000000000000001*state(4)) * delta_C(18);
          dF_block(5) += (0.00025000000000000001*state(4)) * delta_C(19);
          dF_block(5) += (-1.0*state(21)*state(5)*jvals[27]) * delta_C(20);
          dF_block(5) += (-1.0*state(20)*state(5)*jvals[27]) * delta_C(21);
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
          dF_block(20) += (-1.0*state(20)*state(21)*jvals[27]) * delta_C(5);
          dF_block(20) += (-0.025000000000000001*state(20)) * delta_C(10);
          dF_block(20) += (-0.025000000000000001*state(20)) * delta_C(11);
          dF_block(20) += (-0.025000000000000001*state(20)) * delta_C(12);
          dF_block(20) += (-0.025000000000000001*state(20)) * delta_C(13);
          dF_block(20) += (-0.025000000000000001*state(20)) * delta_C(14);
          dF_block(20) += (-0.025000000000000001*state(20)) * delta_C(15);
          dF_block(20) += (-0.025000000000000001*state(20)) * delta_C(16);
          dF_block(20) += (-0.025000000000000001*state(20)) * delta_C(17);
          dF_block(20) += (-0.025000000000000001*state(20)) * delta_C(18);
          dF_block(20) += (-0.025000000000000001*state(20)) * delta_C(19);
          dF_block(20) += (-0.025000000000000001*state(10) - 0.025000000000000001*state(11) - 0.025000000000000001*state(12) - 0.025000000000000001*state(13) - 0.025000000000000001*state(14) - 1.0*state(21)*state(5)*jvals[27] - 0.025000000000000001*state(15) - 0.025000000000000001*state(16) - 0.025000000000000001*state(17) - 0.025000000000000001*state(18) - 0.025000000000000001*state(19)) * delta_C(20);
          dF_block(20) += (-1.0*state(20)*state(5)*jvals[27]) * delta_C(21);
          dF_block(21) = 0.0;
          dF_block(21) += (-1.0*state(20)*state(21)*jvals[27]) * delta_C(5);
          dF_block(21) += (-1.0*state(21)*state(5)*jvals[27]) * delta_C(20);
          dF_block(21) += (-1.0*state(20)*state(5)*jvals[27]) * delta_C(21);
          dF_block(22) = 0.0;
          dF_block(22) += (1.0*state(20)*state(21)*jvals[27]) * delta_C(5);
          dF_block(22) += (1.0*state(21)*state(5)*jvals[27]) * delta_C(20);
          dF_block(22) += (1.0*state(20)*state(5)*jvals[27]) * delta_C(21);
          dF_block(23) = 0.0;
          dF_block(23) += (1.0*state(20)*state(21)*jvals[27]) * delta_C(5);
          dF_block(23) += (0.025000000000000001*state(20)) * delta_C(10);
          dF_block(23) += (0.025000000000000001*state(20)) * delta_C(13);
          dF_block(23) += (0.025000000000000001*state(20)) * delta_C(16);
          dF_block(23) += (0.025000000000000001*state(20)) * delta_C(19);
          dF_block(23) += (0.025000000000000001*state(10) + 0.025000000000000001*state(13) + 1.0*state(21)*state(5)*jvals[27] + 0.025000000000000001*state(16) + 0.025000000000000001*state(19)) * delta_C(20);
          dF_block(23) += (1.0*state(20)*state(5)*jvals[27]) * delta_C(21);
          dF_block(24) = 0.0;
          dF_block(24) += (0.025000000000000001*state(20)) * delta_C(11);
          dF_block(24) += (0.025000000000000001*state(20)) * delta_C(14);
          dF_block(24) += (0.025000000000000001*state(20)) * delta_C(17);
          dF_block(24) += (0.025000000000000001*state(11) + 0.025000000000000001*state(14) + 0.025000000000000001*state(17)) * delta_C(20);
          dF_block(25) = 0.0;
          dF_block(25) += (0.025000000000000001*state(20)) * delta_C(12);
          dF_block(25) += (0.025000000000000001*state(20)) * delta_C(15);
          dF_block(25) += (0.025000000000000001*state(20)) * delta_C(18);
          dF_block(25) += (0.025000000000000001*state(12) + 0.025000000000000001*state(15) + 0.025000000000000001*state(18)) * delta_C(20);
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

      static constexpr int NUM_SPECIES = 26;
      static constexpr double atol[NUM_SPECIES] = { 100.0, 100.0, 100.0, 100.0, 100.0, 100.0, 100.0, 100.0, 100.0, 100.0, 100.0, 100.0, 100.0, 100.0, 100.0, 100.0, 100.0, 100.0, 100.0, 100.0, 100.0, 100.0, 100.0, 100.0, 100.0, 100.0 };
      static constexpr double rtol[NUM_SPECIES] = { 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01 };

      // Photolysis reactions (Cloud-J input mapping):
      //   jvals[0] = H2O2 -> OH  (original A: 1e-05)
      static constexpr int NUM_PHOTOLYSIS = 1;

      template <class StateView>
      KOKKOS_INLINE_FUNCTION void integrate(double dt_total, StateView& state, const double* jvals) const {
          const int NUM_SPECIES = 26;
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
          const double S_0 = state(8);
          const double S_1 = state(9);
          const double S_2 = state(6);
          const double S_3 = state(7);
          const double S_4 = state(0);
          const double S_5 = state(3);
          const double S_6 = state(2);
          const double S_7 = state(1);
          const double S_8 = state(23);
          const double S_9 = state(24);
          const double S_10 = state(21);
          const double S_11 = state(19);
          const double S_12 = state(17);
          const double S_13 = state(16);
          const double S_14 = state(14);
          const double S_15 = state(13);
          const double S_16 = state(11);
          const double S_17 = state(10);
          const double S_18 = state(22);
          const double S_19 = state(5);
          const double S_20 = state(4);
          const double S_21 = state(20);
          const double S_22 = state(15);
          const double S_23 = state(12);
          const double S_24 = state(18);
          const double S_25 = state(25);

          // Analytical Jacobian & Iteration Matrix W = inv_g_dt*I - J (sparse)
          double J_0_0 = -5.0000000000000004e-6;
          double J_1_0 = 5.0000000000000004e-6;
          double J_2_2 = -5.0000000000000004e-6;
          double J_3_2 = 5.0000000000000004e-6;
          double J_4_4 = -5.0442046141041832e-12*S_3 - 3.3000000000000001e-12*S_4;
          double J_4_5 = -5.0442046141041832e-12*S_0;
          double J_4_6 = 2.0*jvals[0];
          double J_4_20 = -3.3000000000000001e-12*S_0;
          double J_5_4 = -5.0442046141041832e-12*S_3;
          double J_5_5 = -3.3571944693753379e-14*S_1 - 5.0442046141041832e-12*S_0;
          double J_5_7 = -3.3571944693753379e-14*S_3;
          double J_6_6 = -0.0025000000000000001*S_4 - 1.0*jvals[0];
          double J_6_20 = -0.0025000000000000001*S_2;
          double J_7_5 = -3.3571944693753379e-14*S_1;
          double J_7_7 = -3.3571944693753379e-14*S_3;
          double J_8_10 = 1.0*S_20*S_5*jvals[27];
          double J_8_11 = 0.025000000000000001*S_20;
          double J_8_13 = 0.025000000000000001*S_20;
          double J_8_15 = 0.025000000000000001*S_20;
          double J_8_17 = 0.025000000000000001*S_20;
          double J_8_19 = 1.0*S_20*S_21*jvals[27];
          double J_8_21 = 0.025000000000000001*S_10 + 0.025000000000000001*S_13 + 1.0*S_21*S_5*jvals[27] + 0.025000000000000001*S_16 + 0.025000000000000001*S_19;
          double J_9_12 = 0.025000000000000001*S_20;
          double J_9_14 = 0.025000000000000001*S_20;
          double J_9_16 = 0.025000000000000001*S_20;
          double J_9_21 = 0.025000000000000001*S_11 + 0.025000000000000001*S_14 + 0.025000000000000001*S_17;
          double J_10_10 = -1.0*S_20*S_5*jvals[27];
          double J_10_19 = -1.0*S_20*S_21*jvals[27];
          double J_10_21 = -1.0*S_21*S_5*jvals[27];
          double J_18_10 = 1.0*S_20*S_5*jvals[27];
          double J_18_19 = 1.0*S_20*S_21*jvals[27];
          double J_18_21 = 1.0*S_21*S_5*jvals[27];
          double J_19_4 = 3.3000000000000001e-12*S_4;
          double J_19_6 = 0.0025000000000000001*S_4;
          double J_19_10 = -1.0*S_20*S_5*jvals[27];
          double J_19_11 = 0.00025000000000000001*S_4;
          double J_19_12 = 0.00025000000000000001*S_4;
          double J_19_13 = 0.00025000000000000001*S_4;
          double J_19_14 = 2.5000000000000001e-5*S_4;
          double J_19_15 = 2.5000000000000001e-5*S_4;
          double J_19_16 = 2.5000000000000001e-5*S_4;
          double J_19_17 = 2.5000000000000001e-5*S_4;
          double J_19_19 = -1.0*S_20*S_21*jvals[27];
          double J_19_20 = 2.5000000000000001e-5*S_10 + 2.5000000000000001e-5*S_11 + 2.5000000000000001e-5*S_12 + 2.5000000000000001e-5*S_13 + 2.5000000000000001e-5*S_14 + 0.0025000000000000001*S_2 + 3.3000000000000001e-12*S_0 + 0.00025000000000000001*S_15 + 0.00025000000000000001*S_16 + 0.00025000000000000001*S_17 + 0.00025000000000000001*S_18 + 0.00025000000000000001*S_19;
          double J_19_21 = -1.0*S_21*S_5*jvals[27];
          double J_19_22 = 0.00025000000000000001*S_4;
          double J_19_23 = 2.5000000000000001e-5*S_4;
          double J_19_24 = 0.00025000000000000001*S_4;
          double J_20_4 = 5.0442046141041832e-12*S_3 - 3.3000000000000001e-12*S_4;
          double J_20_5 = 3.3571944693753379e-14*S_1 + 5.0442046141041832e-12*S_0;
          double J_20_6 = -0.0025000000000000001*S_4;
          double J_20_7 = 3.3571944693753379e-14*S_3;
          double J_20_11 = -0.00025000000000000001*S_4;
          double J_20_12 = -0.00025000000000000001*S_4;
          double J_20_13 = -0.00025000000000000001*S_4;
          double J_20_14 = -2.5000000000000001e-5*S_4;
          double J_20_15 = -2.5000000000000001e-5*S_4;
          double J_20_16 = -2.5000000000000001e-5*S_4;
          double J_20_17 = -2.5000000000000001e-5*S_4;
          double J_20_20 = -2.5000000000000001e-5*S_10 - 2.5000000000000001e-5*S_11 - 2.5000000000000001e-5*S_12 - 2.5000000000000001e-5*S_13 - 2.5000000000000001e-5*S_14 - 0.0025000000000000001*S_2 - 3.3000000000000001e-12*S_0 - 0.00025000000000000001*S_15 - 0.00025000000000000001*S_16 - 0.00025000000000000001*S_17 - 0.00025000000000000001*S_18 - 0.00025000000000000001*S_19;
          double J_20_22 = -0.00025000000000000001*S_4;
          double J_20_23 = -2.5000000000000001e-5*S_4;
          double J_20_24 = -0.00025000000000000001*S_4;
          double J_21_10 = -1.0*S_20*S_5*jvals[27];
          double J_21_11 = -0.025000000000000001*S_20;
          double J_21_12 = -0.025000000000000001*S_20;
          double J_21_13 = -0.025000000000000001*S_20;
          double J_21_14 = -0.025000000000000001*S_20;
          double J_21_15 = -0.025000000000000001*S_20;
          double J_21_16 = -0.025000000000000001*S_20;
          double J_21_17 = -0.025000000000000001*S_20;
          double J_21_19 = -1.0*S_20*S_21*jvals[27];
          double J_21_21 = -0.025000000000000001*S_10 - 0.025000000000000001*S_11 - 0.025000000000000001*S_12 - 0.025000000000000001*S_13 - 0.025000000000000001*S_14 - 1.0*S_21*S_5*jvals[27] - 0.025000000000000001*S_15 - 0.025000000000000001*S_16 - 0.025000000000000001*S_17 - 0.025000000000000001*S_18 - 0.025000000000000001*S_19;
          double J_21_22 = -0.025000000000000001*S_20;
          double J_21_23 = -0.025000000000000001*S_20;
          double J_21_24 = -0.025000000000000001*S_20;
          double J_25_21 = 0.025000000000000001*S_12 + 0.025000000000000001*S_15 + 0.025000000000000001*S_18;
          double J_25_22 = 0.025000000000000001*S_20;
          double J_25_23 = 0.025000000000000001*S_20;
          double J_25_24 = 0.025000000000000001*S_20;
          double W_0_0 = inv_g_dt - J_0_0;
          double W_1_0 = -J_1_0;
          double W_1_1 = inv_g_dt;
          double W_2_2 = inv_g_dt - J_2_2;
          double W_3_2 = -J_3_2;
          double W_3_3 = inv_g_dt;
          double W_4_4 = inv_g_dt - J_4_4;
          double W_4_5 = -J_4_5;
          double W_4_6 = -J_4_6;
          double W_4_20 = -J_4_20;
          double W_5_4 = -J_5_4;
          double W_5_5 = inv_g_dt - J_5_5;
          double W_5_7 = -J_5_7;
          double W_6_6 = inv_g_dt - J_6_6;
          double W_6_20 = -J_6_20;
          double W_7_5 = -J_7_5;
          double W_7_7 = inv_g_dt - J_7_7;
          double W_8_8 = inv_g_dt;
          double W_8_10 = -J_8_10;
          double W_8_11 = -J_8_11;
          double W_8_13 = -J_8_13;
          double W_8_15 = -J_8_15;
          double W_8_17 = -J_8_17;
          double W_8_19 = -J_8_19;
          double W_8_21 = -J_8_21;
          double W_9_9 = inv_g_dt;
          double W_9_12 = -J_9_12;
          double W_9_14 = -J_9_14;
          double W_9_16 = -J_9_16;
          double W_9_21 = -J_9_21;
          double W_10_10 = inv_g_dt - J_10_10;
          double W_10_19 = -J_10_19;
          double W_10_21 = -J_10_21;
          double W_11_11 = inv_g_dt;
          double W_12_12 = inv_g_dt;
          double W_13_13 = inv_g_dt;
          double W_14_14 = inv_g_dt;
          double W_15_15 = inv_g_dt;
          double W_16_16 = inv_g_dt;
          double W_17_17 = inv_g_dt;
          double W_18_10 = -J_18_10;
          double W_18_18 = inv_g_dt;
          double W_18_19 = -J_18_19;
          double W_18_21 = -J_18_21;
          double W_19_4 = -J_19_4;
          double W_19_6 = -J_19_6;
          double W_19_10 = -J_19_10;
          double W_19_11 = -J_19_11;
          double W_19_12 = -J_19_12;
          double W_19_13 = -J_19_13;
          double W_19_14 = -J_19_14;
          double W_19_15 = -J_19_15;
          double W_19_16 = -J_19_16;
          double W_19_17 = -J_19_17;
          double W_19_19 = inv_g_dt - J_19_19;
          double W_19_20 = -J_19_20;
          double W_19_21 = -J_19_21;
          double W_19_22 = -J_19_22;
          double W_19_23 = -J_19_23;
          double W_19_24 = -J_19_24;
          double W_20_4 = -J_20_4;
          double W_20_5 = -J_20_5;
          double W_20_6 = -J_20_6;
          double W_20_7 = -J_20_7;
          double W_20_11 = -J_20_11;
          double W_20_12 = -J_20_12;
          double W_20_13 = -J_20_13;
          double W_20_14 = -J_20_14;
          double W_20_15 = -J_20_15;
          double W_20_16 = -J_20_16;
          double W_20_17 = -J_20_17;
          double W_20_20 = inv_g_dt - J_20_20;
          double W_20_22 = -J_20_22;
          double W_20_23 = -J_20_23;
          double W_20_24 = -J_20_24;
          double W_21_10 = -J_21_10;
          double W_21_11 = -J_21_11;
          double W_21_12 = -J_21_12;
          double W_21_13 = -J_21_13;
          double W_21_14 = -J_21_14;
          double W_21_15 = -J_21_15;
          double W_21_16 = -J_21_16;
          double W_21_17 = -J_21_17;
          double W_21_19 = -J_21_19;
          double W_21_21 = inv_g_dt - J_21_21;
          double W_21_22 = -J_21_22;
          double W_21_23 = -J_21_23;
          double W_21_24 = -J_21_24;
          double W_22_22 = inv_g_dt;
          double W_23_23 = inv_g_dt;
          double W_24_24 = inv_g_dt;
          double W_25_21 = -J_25_21;
          double W_25_22 = -J_25_22;
          double W_25_23 = -J_25_23;
          double W_25_24 = -J_25_24;
          double W_25_25 = inv_g_dt;

          // Symbolic Doolittle Sparse LU Factorization
          // Block 0: species [OC1, OC2, BC1, BC2, OH]
          double U_0_0 = W_0_0;
          double L_1_0 = (W_1_0) / U_0_0;
          double U_1_1 = W_1_1;
          double U_2_2 = W_2_2;
          double L_3_2 = (W_3_2) / U_2_2;
          double U_3_3 = W_3_3;
          double U_4_4 = W_4_4;
          double U_4_5 = W_4_5;
          double U_4_6 = W_4_6;
          double U_4_20 = W_4_20;
          // Block 1: species [DMS, SO2, HNO3]
          double L_5_4 = (W_5_4) / U_4_4;
          // Block 15: species [SO4]
          double L_19_4 = (W_19_4) / U_4_4;
          double L_20_4 = (W_20_4) / U_4_4;
          double U_5_5 = W_5_5 - L_5_4 * U_4_5;
          double U_5_6 = 0.0 - L_5_4 * U_4_6;
          double U_5_7 = W_5_7;
          double U_5_20 = 0.0 - L_5_4 * U_4_20;
          // Block 3: species [NO3]
          double L_7_5 = (W_7_5) / U_5_5;
          double L_19_5 = (0.0 - L_19_4 * U_4_5) / U_5_5;
          double L_20_5 = (W_20_5 - L_20_4 * U_4_5) / U_5_5;
          // Block 2: species [H2O2]
          double U_6_6 = W_6_6;
          double U_6_20 = W_6_20;
          double L_7_6 = (0.0 - L_7_5 * U_5_6) / U_6_6;
          double L_19_6 = (W_19_6 - L_19_4 * U_4_6 - L_19_5 * U_5_6) / U_6_6;
          double L_20_6 = (W_20_6 - L_20_4 * U_4_6 - L_20_5 * U_5_6) / U_6_6;
          double U_7_7 = W_7_7 - L_7_5 * U_5_7;
          double U_7_20 = 0.0 - L_7_5 * U_5_20 - L_7_6 * U_6_20;
          double L_19_7 = (0.0 - L_19_5 * U_5_7) / U_7_7;
          double L_20_7 = (W_20_7 - L_20_5 * U_5_7) / U_7_7;
          // Block 4: species [NO3an1]
          double U_8_8 = W_8_8;
          double U_8_10 = W_8_10;
          double U_8_11 = W_8_11;
          double U_8_13 = W_8_13;
          double U_8_15 = W_8_15;
          double U_8_17 = W_8_17;
          double U_8_19 = W_8_19;
          double U_8_21 = W_8_21;
          // Block 5: species [NO3an2]
          double U_9_9 = W_9_9;
          double U_9_12 = W_9_12;
          double U_9_14 = W_9_14;
          double U_9_16 = W_9_16;
          double U_9_21 = W_9_21;
          // Block 6: species [NH3]
          double U_10_10 = W_10_10;
          double U_10_19 = W_10_19;
          double U_10_21 = W_10_21;
          // Block 14: species [NH4a]
          double L_18_10 = (W_18_10) / U_10_10;
          double L_19_10 = (W_19_10) / U_10_10;
          double L_21_10 = (W_21_10) / U_10_10;
          // Block 7: species [SS5]
          double U_11_11 = W_11_11;
          double L_19_11 = (W_19_11) / U_11_11;
          double L_20_11 = (W_20_11) / U_11_11;
          double L_21_11 = (W_21_11) / U_11_11;
          // Block 8: species [SS3]
          double U_12_12 = W_12_12;
          double L_19_12 = (W_19_12) / U_12_12;
          double L_20_12 = (W_20_12) / U_12_12;
          double L_21_12 = (W_21_12) / U_12_12;
          // Block 9: species [SS2]
          double U_13_13 = W_13_13;
          double L_19_13 = (W_19_13) / U_13_13;
          double L_20_13 = (W_20_13) / U_13_13;
          double L_21_13 = (W_21_13) / U_13_13;
          // Block 10: species [DUST5]
          double U_14_14 = W_14_14;
          double L_19_14 = (W_19_14) / U_14_14;
          double L_20_14 = (W_20_14) / U_14_14;
          double L_21_14 = (W_21_14) / U_14_14;
          // Block 11: species [DUST4]
          double U_15_15 = W_15_15;
          double L_19_15 = (W_19_15) / U_15_15;
          double L_20_15 = (W_20_15) / U_15_15;
          double L_21_15 = (W_21_15) / U_15_15;
          // Block 12: species [DUST2]
          double U_16_16 = W_16_16;
          double L_19_16 = (W_19_16) / U_16_16;
          double L_20_16 = (W_20_16) / U_16_16;
          double L_21_16 = (W_21_16) / U_16_16;
          // Block 13: species [DUST1]
          double U_17_17 = W_17_17;
          double L_19_17 = (W_19_17) / U_17_17;
          double L_20_17 = (W_20_17) / U_17_17;
          double L_21_17 = (W_21_17) / U_17_17;
          double U_18_18 = W_18_18;
          double U_18_19 = W_18_19 - L_18_10 * U_10_19;
          double U_18_21 = W_18_21 - L_18_10 * U_10_21;
          double U_19_19 = W_19_19 - L_19_10 * U_10_19;
          double U_19_20 = W_19_20 - L_19_4 * U_4_20 - L_19_5 * U_5_20 - L_19_6 * U_6_20 - L_19_7 * U_7_20;
          double U_19_21 = W_19_21 - L_19_10 * U_10_21;
          double U_19_22 = W_19_22;
          double U_19_23 = W_19_23;
          double U_19_24 = W_19_24;
          double L_21_19 = (W_21_19 - L_21_10 * U_10_19) / U_19_19;
          double U_20_20 = W_20_20 - L_20_4 * U_4_20 - L_20_5 * U_5_20 - L_20_6 * U_6_20 - L_20_7 * U_7_20;
          double U_20_22 = W_20_22;
          double U_20_23 = W_20_23;
          double U_20_24 = W_20_24;
          double L_21_20 = (0.0 - L_21_19 * U_19_20) / U_20_20;
          double U_21_21 = W_21_21 - L_21_10 * U_10_21 - L_21_19 * U_19_21;
          double U_21_22 = W_21_22 - L_21_19 * U_19_22 - L_21_20 * U_20_22;
          double U_21_23 = W_21_23 - L_21_19 * U_19_23 - L_21_20 * U_20_23;
          double U_21_24 = W_21_24 - L_21_19 * U_19_24 - L_21_20 * U_20_24;
          // Block 19: species [NO3an3]
          double L_25_21 = (W_25_21) / U_21_21;
          // Block 16: species [SS1]
          double U_22_22 = W_22_22;
          double L_25_22 = (W_25_22 - L_25_21 * U_21_22) / U_22_22;
          // Block 17: species [DUST3]
          double U_23_23 = W_23_23;
          double L_25_23 = (W_25_23 - L_25_21 * U_21_23) / U_23_23;
          // Block 18: species [SS4]
          double U_24_24 = W_24_24;
          double L_25_24 = (W_25_24 - L_25_21 * U_21_24) / U_24_24;
          double U_25_25 = W_25_25;

          // --- Stage 1 ---
          // Rate evaluation F1 at S
          double F1_0 = -5.0442046141041832e-12*S_3*S_0 + 2.0*S_2*jvals[0] - 3.3000000000000001e-12*S_0*S_4;
          double F1_1 = -3.3571944693753379e-14*S_3*S_1;
          double F1_2 = -0.0025000000000000001*S_2*S_4 - 1.0*S_2*jvals[0];
          double F1_3 = -3.3571944693753379e-14*S_3*S_1 - 5.0442046141041832e-12*S_3*S_0;
          double F1_4 = 3.3571944693753379e-14*S_3*S_1 + 5.0442046141041832e-12*S_3*S_0 - 2.5000000000000001e-5*S_10*S_4 - 2.5000000000000001e-5*S_11*S_4 - 2.5000000000000001e-5*S_12*S_4 - 2.5000000000000001e-5*S_13*S_4 - 2.5000000000000001e-5*S_14*S_4 - 0.0025000000000000001*S_2*S_4 - 3.3000000000000001e-12*S_0*S_4 - 0.00025000000000000001*S_4*S_15 - 0.00025000000000000001*S_4*S_16 - 0.00025000000000000001*S_4*S_17 - 0.00025000000000000001*S_4*S_18 - 0.00025000000000000001*S_4*S_19;
          double F1_5 = 2.5000000000000001e-5*S_10*S_4 + 2.5000000000000001e-5*S_11*S_4 + 2.5000000000000001e-5*S_12*S_4 + 2.5000000000000001e-5*S_13*S_4 + 2.5000000000000001e-5*S_14*S_4 + 0.0025000000000000001*S_2*S_4 - 1.0*S_20*S_21*S_5*jvals[27] + 3.3000000000000001e-12*S_0*S_4 + 0.00025000000000000001*S_4*S_15 + 0.00025000000000000001*S_4*S_16 + 0.00025000000000000001*S_4*S_17 + 0.00025000000000000001*S_4*S_18 + 0.00025000000000000001*S_4*S_19;
          double F1_6 = -5.0000000000000004e-6*S_6;
          double F1_7 = 5.0000000000000004e-6*S_6;
          double F1_8 = -5.0000000000000004e-6*S_8;
          double F1_9 = 5.0000000000000004e-6*S_8;
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
          double F1_20 = -0.025000000000000001*S_10*S_20 - 0.025000000000000001*S_11*S_20 - 0.025000000000000001*S_12*S_20 - 0.025000000000000001*S_13*S_20 - 0.025000000000000001*S_14*S_20 - 1.0*S_20*S_21*S_5*jvals[27] - 0.025000000000000001*S_20*S_15 - 0.025000000000000001*S_20*S_16 - 0.025000000000000001*S_20*S_17 - 0.025000000000000001*S_20*S_18 - 0.025000000000000001*S_20*S_19;
          double F1_21 = -1.0*S_20*S_21*S_5*jvals[27];
          double F1_22 = 1.0*S_20*S_21*S_5*jvals[27];
          double F1_23 = 0.025000000000000001*S_10*S_20 + 0.025000000000000001*S_13*S_20 + 1.0*S_20*S_21*S_5*jvals[27] + 0.025000000000000001*S_20*S_16 + 0.025000000000000001*S_20*S_19;
          double F1_24 = 0.025000000000000001*S_11*S_20 + 0.025000000000000001*S_14*S_20 + 0.025000000000000001*S_20*S_17;
          double F1_25 = 0.025000000000000001*S_12*S_20 + 0.025000000000000001*S_20*S_15 + 0.025000000000000001*S_20*S_18;
          // Block 0: K1 forward sub [OC1, OC2, BC1, BC2, OH]
          double y1_0 = F1_0;
          double y1_1 = F1_1 - L_1_0 * y1_0;
          double y1_2 = F1_2;
          double y1_3 = F1_3 - L_3_2 * y1_2;
          double y1_4 = F1_4;
          // Block 1: K1 forward sub [DMS, SO2, HNO3]
          double y1_5 = F1_5 - L_5_4 * y1_4;
          // Block 2: K1 forward sub [H2O2]
          double y1_6 = F1_6;
          // Block 3: K1 forward sub [NO3]
          double y1_7 = F1_7 - L_7_5 * y1_5 - L_7_6 * y1_6;
          // Block 4: K1 forward sub [NO3an1]
          double y1_8 = F1_8;
          // Block 5: K1 forward sub [NO3an2]
          double y1_9 = F1_9;
          // Block 6: K1 forward sub [NH3]
          double y1_10 = F1_10;
          // Block 7: K1 forward sub [SS5]
          double y1_11 = F1_11;
          // Block 8: K1 forward sub [SS3]
          double y1_12 = F1_12;
          // Block 9: K1 forward sub [SS2]
          double y1_13 = F1_13;
          // Block 10: K1 forward sub [DUST5]
          double y1_14 = F1_14;
          // Block 11: K1 forward sub [DUST4]
          double y1_15 = F1_15;
          // Block 12: K1 forward sub [DUST2]
          double y1_16 = F1_16;
          // Block 13: K1 forward sub [DUST1]
          double y1_17 = F1_17;
          // Block 14: K1 forward sub [NH4a]
          double y1_18 = F1_18 - L_18_10 * y1_10;
          // Block 15: K1 forward sub [SO4]
          double y1_19 = F1_19 - L_19_4 * y1_4 - L_19_5 * y1_5 - L_19_6 * y1_6 - L_19_7 * y1_7 - L_19_10 * y1_10 - L_19_11 * y1_11 - L_19_12 * y1_12 - L_19_13 * y1_13 - L_19_14 * y1_14 - L_19_15 * y1_15 - L_19_16 * y1_16 - L_19_17 * y1_17;
          double y1_20 = F1_20 - L_20_4 * y1_4 - L_20_5 * y1_5 - L_20_6 * y1_6 - L_20_7 * y1_7 - L_20_11 * y1_11 - L_20_12 * y1_12 - L_20_13 * y1_13 - L_20_14 * y1_14 - L_20_15 * y1_15 - L_20_16 * y1_16 - L_20_17 * y1_17;
          double y1_21 = F1_21 - L_21_10 * y1_10 - L_21_11 * y1_11 - L_21_12 * y1_12 - L_21_13 * y1_13 - L_21_14 * y1_14 - L_21_15 * y1_15 - L_21_16 * y1_16 - L_21_17 * y1_17 - L_21_19 * y1_19 - L_21_20 * y1_20;
          // Block 16: K1 forward sub [SS1]
          double y1_22 = F1_22;
          // Block 17: K1 forward sub [DUST3]
          double y1_23 = F1_23;
          // Block 18: K1 forward sub [SS4]
          double y1_24 = F1_24;
          // Block 19: K1 forward sub [NO3an3]
          double y1_25 = F1_25 - L_25_21 * y1_21 - L_25_22 * y1_22 - L_25_23 * y1_23 - L_25_24 * y1_24;
          // Block 19: K1 backward sub [NO3an3]
          double K1_25 = y1_25 / U_25_25;
          // Block 18: K1 backward sub [SS4]
          double K1_24 = y1_24 / U_24_24;
          // Block 17: K1 backward sub [DUST3]
          double K1_23 = y1_23 / U_23_23;
          // Block 16: K1 backward sub [SS1]
          double K1_22 = y1_22 / U_22_22;
          // Block 1: K1 backward sub [DMS, SO2, HNO3]
          double K1_21 = (y1_21 - U_21_22 * K1_22 - U_21_23 * K1_23 - U_21_24 * K1_24) / U_21_21;
          double K1_20 = (y1_20 - U_20_22 * K1_22 - U_20_23 * K1_23 - U_20_24 * K1_24) / U_20_20;
          // Block 15: K1 backward sub [SO4]
          double K1_19 = (y1_19 - U_19_20 * K1_20 - U_19_21 * K1_21 - U_19_22 * K1_22 - U_19_23 * K1_23 - U_19_24 * K1_24) / U_19_19;
          // Block 14: K1 backward sub [NH4a]
          double K1_18 = (y1_18 - U_18_19 * K1_19 - U_18_21 * K1_21) / U_18_18;
          // Block 13: K1 backward sub [DUST1]
          double K1_17 = y1_17 / U_17_17;
          // Block 12: K1 backward sub [DUST2]
          double K1_16 = y1_16 / U_16_16;
          // Block 11: K1 backward sub [DUST4]
          double K1_15 = y1_15 / U_15_15;
          // Block 10: K1 backward sub [DUST5]
          double K1_14 = y1_14 / U_14_14;
          // Block 9: K1 backward sub [SS2]
          double K1_13 = y1_13 / U_13_13;
          // Block 8: K1 backward sub [SS3]
          double K1_12 = y1_12 / U_12_12;
          // Block 7: K1 backward sub [SS5]
          double K1_11 = y1_11 / U_11_11;
          // Block 6: K1 backward sub [NH3]
          double K1_10 = (y1_10 - U_10_19 * K1_19 - U_10_21 * K1_21) / U_10_10;
          // Block 5: K1 backward sub [NO3an2]
          double K1_9 = (y1_9 - U_9_12 * K1_12 - U_9_14 * K1_14 - U_9_16 * K1_16 - U_9_21 * K1_21) / U_9_9;
          // Block 4: K1 backward sub [NO3an1]
          double K1_8 = (y1_8 - U_8_10 * K1_10 - U_8_11 * K1_11 - U_8_13 * K1_13 - U_8_15 * K1_15 - U_8_17 * K1_17 - U_8_19 * K1_19 - U_8_21 * K1_21) / U_8_8;
          // Block 3: K1 backward sub [NO3]
          double K1_7 = (y1_7 - U_7_20 * K1_20) / U_7_7;
          // Block 2: K1 backward sub [H2O2]
          double K1_6 = (y1_6 - U_6_20 * K1_20) / U_6_6;
          double K1_5 = (y1_5 - U_5_6 * K1_6 - U_5_7 * K1_7 - U_5_20 * K1_20) / U_5_5;
          // Block 0: K1 backward sub [OC1, OC2, BC1, BC2, OH]
          double K1_4 = (y1_4 - U_4_5 * K1_5 - U_4_6 * K1_6 - U_4_20 * K1_20) / U_4_4;
          double K1_3 = y1_3 / U_3_3;
          double K1_2 = y1_2 / U_2_2;
          double K1_1 = y1_1 / U_1_1;
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
          double Y2_7 = S_7 + K1_7;
          double Y2_8 = S_8 + K1_8;
          double Y2_9 = S_9 + K1_9;
          double Y2_10 = S_10 + K1_10;
          double Y2_11 = S_11 + K1_11;
          double Y2_12 = S_12 + K1_12;
          double Y2_13 = S_13 + K1_13;
          double Y2_14 = S_14 + K1_14;
          double Y2_15 = S_15 + K1_15;
          double Y2_16 = S_16 + K1_16;
          double Y2_17 = S_17 + K1_17;
          double Y2_18 = S_18 + K1_18;
          double Y2_19 = S_19 + K1_19;
          double Y2_20 = S_20 + K1_20;
          double Y2_21 = S_21 + K1_21;
          double Y2_22 = S_22 + K1_22;
          double Y2_23 = S_23 + K1_23;
          double Y2_24 = S_24 + K1_24;
          double Y2_25 = S_25 + K1_25;
          // Rate evaluation F2 at Y2
          double F2_0 = -5.0442046141041832e-12*Y2_3*Y2_0 + 2.0*Y2_2*jvals[0] - 3.3000000000000001e-12*Y2_0*Y2_4;
          double F2_1 = -3.3571944693753379e-14*Y2_3*Y2_1;
          double F2_2 = -0.0025000000000000001*Y2_2*Y2_4 - 1.0*Y2_2*jvals[0];
          double F2_3 = -3.3571944693753379e-14*Y2_3*Y2_1 - 5.0442046141041832e-12*Y2_3*Y2_0;
          double F2_4 = 3.3571944693753379e-14*Y2_3*Y2_1 + 5.0442046141041832e-12*Y2_3*Y2_0 - 2.5000000000000001e-5*Y2_10*Y2_4 - 2.5000000000000001e-5*Y2_11*Y2_4 - 2.5000000000000001e-5*Y2_12*Y2_4 - 2.5000000000000001e-5*Y2_13*Y2_4 - 2.5000000000000001e-5*Y2_14*Y2_4 - 0.0025000000000000001*Y2_2*Y2_4 - 3.3000000000000001e-12*Y2_0*Y2_4 - 0.00025000000000000001*Y2_4*Y2_15 - 0.00025000000000000001*Y2_4*Y2_16 - 0.00025000000000000001*Y2_4*Y2_17 - 0.00025000000000000001*Y2_4*Y2_18 - 0.00025000000000000001*Y2_4*Y2_19;
          double F2_5 = 2.5000000000000001e-5*Y2_10*Y2_4 + 2.5000000000000001e-5*Y2_11*Y2_4 + 2.5000000000000001e-5*Y2_12*Y2_4 + 2.5000000000000001e-5*Y2_13*Y2_4 + 2.5000000000000001e-5*Y2_14*Y2_4 + 0.0025000000000000001*Y2_2*Y2_4 - 1.0*Y2_20*Y2_21*Y2_5*jvals[27] + 3.3000000000000001e-12*Y2_0*Y2_4 + 0.00025000000000000001*Y2_4*Y2_15 + 0.00025000000000000001*Y2_4*Y2_16 + 0.00025000000000000001*Y2_4*Y2_17 + 0.00025000000000000001*Y2_4*Y2_18 + 0.00025000000000000001*Y2_4*Y2_19;
          double F2_6 = -5.0000000000000004e-6*Y2_6;
          double F2_7 = 5.0000000000000004e-6*Y2_6;
          double F2_8 = -5.0000000000000004e-6*Y2_8;
          double F2_9 = 5.0000000000000004e-6*Y2_8;
          double F2_10 = 0.0;
          double F2_11 = 0.0;
          double F2_12 = 0.0;
          double F2_13 = 0.0;
          double F2_14 = 0.0;
          double F2_15 = 0.0;
          double F2_16 = 0.0;
          double F2_17 = 0.0;
          double F2_18 = 0.0;
          double F2_19 = 0.0;
          double F2_20 = -0.025000000000000001*Y2_10*Y2_20 - 0.025000000000000001*Y2_11*Y2_20 - 0.025000000000000001*Y2_12*Y2_20 - 0.025000000000000001*Y2_13*Y2_20 - 0.025000000000000001*Y2_14*Y2_20 - 1.0*Y2_20*Y2_21*Y2_5*jvals[27] - 0.025000000000000001*Y2_20*Y2_15 - 0.025000000000000001*Y2_20*Y2_16 - 0.025000000000000001*Y2_20*Y2_17 - 0.025000000000000001*Y2_20*Y2_18 - 0.025000000000000001*Y2_20*Y2_19;
          double F2_21 = -1.0*Y2_20*Y2_21*Y2_5*jvals[27];
          double F2_22 = 1.0*Y2_20*Y2_21*Y2_5*jvals[27];
          double F2_23 = 0.025000000000000001*Y2_10*Y2_20 + 0.025000000000000001*Y2_13*Y2_20 + 1.0*Y2_20*Y2_21*Y2_5*jvals[27] + 0.025000000000000001*Y2_20*Y2_16 + 0.025000000000000001*Y2_20*Y2_19;
          double F2_24 = 0.025000000000000001*Y2_11*Y2_20 + 0.025000000000000001*Y2_14*Y2_20 + 0.025000000000000001*Y2_20*Y2_17;
          double F2_25 = 0.025000000000000001*Y2_12*Y2_20 + 0.025000000000000001*Y2_20*Y2_15 + 0.025000000000000001*Y2_20*Y2_18;
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
          double rhs2_11 = F2_11 + (-1.0156171083877703 / dt) * K1_11;
          double rhs2_12 = F2_12 + (-1.0156171083877703 / dt) * K1_12;
          double rhs2_13 = F2_13 + (-1.0156171083877703 / dt) * K1_13;
          double rhs2_14 = F2_14 + (-1.0156171083877703 / dt) * K1_14;
          double rhs2_15 = F2_15 + (-1.0156171083877703 / dt) * K1_15;
          double rhs2_16 = F2_16 + (-1.0156171083877703 / dt) * K1_16;
          double rhs2_17 = F2_17 + (-1.0156171083877703 / dt) * K1_17;
          double rhs2_18 = F2_18 + (-1.0156171083877703 / dt) * K1_18;
          double rhs2_19 = F2_19 + (-1.0156171083877703 / dt) * K1_19;
          double rhs2_20 = F2_20 + (-1.0156171083877703 / dt) * K1_20;
          double rhs2_21 = F2_21 + (-1.0156171083877703 / dt) * K1_21;
          double rhs2_22 = F2_22 + (-1.0156171083877703 / dt) * K1_22;
          double rhs2_23 = F2_23 + (-1.0156171083877703 / dt) * K1_23;
          double rhs2_24 = F2_24 + (-1.0156171083877703 / dt) * K1_24;
          double rhs2_25 = F2_25 + (-1.0156171083877703 / dt) * K1_25;
          // Block 0: K2 forward sub [OC1, OC2, BC1, BC2, OH]
          double y2_0 = rhs2_0;
          double y2_1 = rhs2_1 - L_1_0 * y2_0;
          double y2_2 = rhs2_2;
          double y2_3 = rhs2_3 - L_3_2 * y2_2;
          double y2_4 = rhs2_4;
          // Block 1: K2 forward sub [DMS, SO2, HNO3]
          double y2_5 = rhs2_5 - L_5_4 * y2_4;
          // Block 2: K2 forward sub [H2O2]
          double y2_6 = rhs2_6;
          // Block 3: K2 forward sub [NO3]
          double y2_7 = rhs2_7 - L_7_5 * y2_5 - L_7_6 * y2_6;
          // Block 4: K2 forward sub [NO3an1]
          double y2_8 = rhs2_8;
          // Block 5: K2 forward sub [NO3an2]
          double y2_9 = rhs2_9;
          // Block 6: K2 forward sub [NH3]
          double y2_10 = rhs2_10;
          // Block 7: K2 forward sub [SS5]
          double y2_11 = rhs2_11;
          // Block 8: K2 forward sub [SS3]
          double y2_12 = rhs2_12;
          // Block 9: K2 forward sub [SS2]
          double y2_13 = rhs2_13;
          // Block 10: K2 forward sub [DUST5]
          double y2_14 = rhs2_14;
          // Block 11: K2 forward sub [DUST4]
          double y2_15 = rhs2_15;
          // Block 12: K2 forward sub [DUST2]
          double y2_16 = rhs2_16;
          // Block 13: K2 forward sub [DUST1]
          double y2_17 = rhs2_17;
          // Block 14: K2 forward sub [NH4a]
          double y2_18 = rhs2_18 - L_18_10 * y2_10;
          // Block 15: K2 forward sub [SO4]
          double y2_19 = rhs2_19 - L_19_4 * y2_4 - L_19_5 * y2_5 - L_19_6 * y2_6 - L_19_7 * y2_7 - L_19_10 * y2_10 - L_19_11 * y2_11 - L_19_12 * y2_12 - L_19_13 * y2_13 - L_19_14 * y2_14 - L_19_15 * y2_15 - L_19_16 * y2_16 - L_19_17 * y2_17;
          double y2_20 = rhs2_20 - L_20_4 * y2_4 - L_20_5 * y2_5 - L_20_6 * y2_6 - L_20_7 * y2_7 - L_20_11 * y2_11 - L_20_12 * y2_12 - L_20_13 * y2_13 - L_20_14 * y2_14 - L_20_15 * y2_15 - L_20_16 * y2_16 - L_20_17 * y2_17;
          double y2_21 = rhs2_21 - L_21_10 * y2_10 - L_21_11 * y2_11 - L_21_12 * y2_12 - L_21_13 * y2_13 - L_21_14 * y2_14 - L_21_15 * y2_15 - L_21_16 * y2_16 - L_21_17 * y2_17 - L_21_19 * y2_19 - L_21_20 * y2_20;
          // Block 16: K2 forward sub [SS1]
          double y2_22 = rhs2_22;
          // Block 17: K2 forward sub [DUST3]
          double y2_23 = rhs2_23;
          // Block 18: K2 forward sub [SS4]
          double y2_24 = rhs2_24;
          // Block 19: K2 forward sub [NO3an3]
          double y2_25 = rhs2_25 - L_25_21 * y2_21 - L_25_22 * y2_22 - L_25_23 * y2_23 - L_25_24 * y2_24;
          // Block 19: K2 backward sub [NO3an3]
          double K2_25 = y2_25 / U_25_25;
          // Block 18: K2 backward sub [SS4]
          double K2_24 = y2_24 / U_24_24;
          // Block 17: K2 backward sub [DUST3]
          double K2_23 = y2_23 / U_23_23;
          // Block 16: K2 backward sub [SS1]
          double K2_22 = y2_22 / U_22_22;
          // Block 1: K2 backward sub [DMS, SO2, HNO3]
          double K2_21 = (y2_21 - U_21_22 * K2_22 - U_21_23 * K2_23 - U_21_24 * K2_24) / U_21_21;
          double K2_20 = (y2_20 - U_20_22 * K2_22 - U_20_23 * K2_23 - U_20_24 * K2_24) / U_20_20;
          // Block 15: K2 backward sub [SO4]
          double K2_19 = (y2_19 - U_19_20 * K2_20 - U_19_21 * K2_21 - U_19_22 * K2_22 - U_19_23 * K2_23 - U_19_24 * K2_24) / U_19_19;
          // Block 14: K2 backward sub [NH4a]
          double K2_18 = (y2_18 - U_18_19 * K2_19 - U_18_21 * K2_21) / U_18_18;
          // Block 13: K2 backward sub [DUST1]
          double K2_17 = y2_17 / U_17_17;
          // Block 12: K2 backward sub [DUST2]
          double K2_16 = y2_16 / U_16_16;
          // Block 11: K2 backward sub [DUST4]
          double K2_15 = y2_15 / U_15_15;
          // Block 10: K2 backward sub [DUST5]
          double K2_14 = y2_14 / U_14_14;
          // Block 9: K2 backward sub [SS2]
          double K2_13 = y2_13 / U_13_13;
          // Block 8: K2 backward sub [SS3]
          double K2_12 = y2_12 / U_12_12;
          // Block 7: K2 backward sub [SS5]
          double K2_11 = y2_11 / U_11_11;
          // Block 6: K2 backward sub [NH3]
          double K2_10 = (y2_10 - U_10_19 * K2_19 - U_10_21 * K2_21) / U_10_10;
          // Block 5: K2 backward sub [NO3an2]
          double K2_9 = (y2_9 - U_9_12 * K2_12 - U_9_14 * K2_14 - U_9_16 * K2_16 - U_9_21 * K2_21) / U_9_9;
          // Block 4: K2 backward sub [NO3an1]
          double K2_8 = (y2_8 - U_8_10 * K2_10 - U_8_11 * K2_11 - U_8_13 * K2_13 - U_8_15 * K2_15 - U_8_17 * K2_17 - U_8_19 * K2_19 - U_8_21 * K2_21) / U_8_8;
          // Block 3: K2 backward sub [NO3]
          double K2_7 = (y2_7 - U_7_20 * K2_20) / U_7_7;
          // Block 2: K2 backward sub [H2O2]
          double K2_6 = (y2_6 - U_6_20 * K2_20) / U_6_6;
          double K2_5 = (y2_5 - U_5_6 * K2_6 - U_5_7 * K2_7 - U_5_20 * K2_20) / U_5_5;
          // Block 0: K2 backward sub [OC1, OC2, BC1, BC2, OH]
          double K2_4 = (y2_4 - U_4_5 * K2_5 - U_4_6 * K2_6 - U_4_20 * K2_20) / U_4_4;
          double K2_3 = y2_3 / U_3_3;
          double K2_2 = y2_2 / U_2_2;
          double K2_1 = y2_1 / U_1_1;
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
          double Y3_7 = S_7 + K1_7;
          double Y3_8 = S_8 + K1_8;
          double Y3_9 = S_9 + K1_9;
          double Y3_10 = S_10 + K1_10;
          double Y3_11 = S_11 + K1_11;
          double Y3_12 = S_12 + K1_12;
          double Y3_13 = S_13 + K1_13;
          double Y3_14 = S_14 + K1_14;
          double Y3_15 = S_15 + K1_15;
          double Y3_16 = S_16 + K1_16;
          double Y3_17 = S_17 + K1_17;
          double Y3_18 = S_18 + K1_18;
          double Y3_19 = S_19 + K1_19;
          double Y3_20 = S_20 + K1_20;
          double Y3_21 = S_21 + K1_21;
          double Y3_22 = S_22 + K1_22;
          double Y3_23 = S_23 + K1_23;
          double Y3_24 = S_24 + K1_24;
          double Y3_25 = S_25 + K1_25;
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
          double rhs3_11 = F2_11 + (4.0759956452537702 / dt) * K1_11 + (9.20767942983308 / dt) * K2_11;
          double rhs3_12 = F2_12 + (4.0759956452537702 / dt) * K1_12 + (9.20767942983308 / dt) * K2_12;
          double rhs3_13 = F2_13 + (4.0759956452537702 / dt) * K1_13 + (9.20767942983308 / dt) * K2_13;
          double rhs3_14 = F2_14 + (4.0759956452537702 / dt) * K1_14 + (9.20767942983308 / dt) * K2_14;
          double rhs3_15 = F2_15 + (4.0759956452537702 / dt) * K1_15 + (9.20767942983308 / dt) * K2_15;
          double rhs3_16 = F2_16 + (4.0759956452537702 / dt) * K1_16 + (9.20767942983308 / dt) * K2_16;
          double rhs3_17 = F2_17 + (4.0759956452537702 / dt) * K1_17 + (9.20767942983308 / dt) * K2_17;
          double rhs3_18 = F2_18 + (4.0759956452537702 / dt) * K1_18 + (9.20767942983308 / dt) * K2_18;
          double rhs3_19 = F2_19 + (4.0759956452537702 / dt) * K1_19 + (9.20767942983308 / dt) * K2_19;
          double rhs3_20 = F2_20 + (4.0759956452537702 / dt) * K1_20 + (9.20767942983308 / dt) * K2_20;
          double rhs3_21 = F2_21 + (4.0759956452537702 / dt) * K1_21 + (9.20767942983308 / dt) * K2_21;
          double rhs3_22 = F2_22 + (4.0759956452537702 / dt) * K1_22 + (9.20767942983308 / dt) * K2_22;
          double rhs3_23 = F2_23 + (4.0759956452537702 / dt) * K1_23 + (9.20767942983308 / dt) * K2_23;
          double rhs3_24 = F2_24 + (4.0759956452537702 / dt) * K1_24 + (9.20767942983308 / dt) * K2_24;
          double rhs3_25 = F2_25 + (4.0759956452537702 / dt) * K1_25 + (9.20767942983308 / dt) * K2_25;
          // Block 0: K3 forward sub [OC1, OC2, BC1, BC2, OH]
          double y3_0 = rhs3_0;
          double y3_1 = rhs3_1 - L_1_0 * y3_0;
          double y3_2 = rhs3_2;
          double y3_3 = rhs3_3 - L_3_2 * y3_2;
          double y3_4 = rhs3_4;
          // Block 1: K3 forward sub [DMS, SO2, HNO3]
          double y3_5 = rhs3_5 - L_5_4 * y3_4;
          // Block 2: K3 forward sub [H2O2]
          double y3_6 = rhs3_6;
          // Block 3: K3 forward sub [NO3]
          double y3_7 = rhs3_7 - L_7_5 * y3_5 - L_7_6 * y3_6;
          // Block 4: K3 forward sub [NO3an1]
          double y3_8 = rhs3_8;
          // Block 5: K3 forward sub [NO3an2]
          double y3_9 = rhs3_9;
          // Block 6: K3 forward sub [NH3]
          double y3_10 = rhs3_10;
          // Block 7: K3 forward sub [SS5]
          double y3_11 = rhs3_11;
          // Block 8: K3 forward sub [SS3]
          double y3_12 = rhs3_12;
          // Block 9: K3 forward sub [SS2]
          double y3_13 = rhs3_13;
          // Block 10: K3 forward sub [DUST5]
          double y3_14 = rhs3_14;
          // Block 11: K3 forward sub [DUST4]
          double y3_15 = rhs3_15;
          // Block 12: K3 forward sub [DUST2]
          double y3_16 = rhs3_16;
          // Block 13: K3 forward sub [DUST1]
          double y3_17 = rhs3_17;
          // Block 14: K3 forward sub [NH4a]
          double y3_18 = rhs3_18 - L_18_10 * y3_10;
          // Block 15: K3 forward sub [SO4]
          double y3_19 = rhs3_19 - L_19_4 * y3_4 - L_19_5 * y3_5 - L_19_6 * y3_6 - L_19_7 * y3_7 - L_19_10 * y3_10 - L_19_11 * y3_11 - L_19_12 * y3_12 - L_19_13 * y3_13 - L_19_14 * y3_14 - L_19_15 * y3_15 - L_19_16 * y3_16 - L_19_17 * y3_17;
          double y3_20 = rhs3_20 - L_20_4 * y3_4 - L_20_5 * y3_5 - L_20_6 * y3_6 - L_20_7 * y3_7 - L_20_11 * y3_11 - L_20_12 * y3_12 - L_20_13 * y3_13 - L_20_14 * y3_14 - L_20_15 * y3_15 - L_20_16 * y3_16 - L_20_17 * y3_17;
          double y3_21 = rhs3_21 - L_21_10 * y3_10 - L_21_11 * y3_11 - L_21_12 * y3_12 - L_21_13 * y3_13 - L_21_14 * y3_14 - L_21_15 * y3_15 - L_21_16 * y3_16 - L_21_17 * y3_17 - L_21_19 * y3_19 - L_21_20 * y3_20;
          // Block 16: K3 forward sub [SS1]
          double y3_22 = rhs3_22;
          // Block 17: K3 forward sub [DUST3]
          double y3_23 = rhs3_23;
          // Block 18: K3 forward sub [SS4]
          double y3_24 = rhs3_24;
          // Block 19: K3 forward sub [NO3an3]
          double y3_25 = rhs3_25 - L_25_21 * y3_21 - L_25_22 * y3_22 - L_25_23 * y3_23 - L_25_24 * y3_24;
          // Block 19: K3 backward sub [NO3an3]
          double K3_25 = y3_25 / U_25_25;
          // Block 18: K3 backward sub [SS4]
          double K3_24 = y3_24 / U_24_24;
          // Block 17: K3 backward sub [DUST3]
          double K3_23 = y3_23 / U_23_23;
          // Block 16: K3 backward sub [SS1]
          double K3_22 = y3_22 / U_22_22;
          // Block 1: K3 backward sub [DMS, SO2, HNO3]
          double K3_21 = (y3_21 - U_21_22 * K3_22 - U_21_23 * K3_23 - U_21_24 * K3_24) / U_21_21;
          double K3_20 = (y3_20 - U_20_22 * K3_22 - U_20_23 * K3_23 - U_20_24 * K3_24) / U_20_20;
          // Block 15: K3 backward sub [SO4]
          double K3_19 = (y3_19 - U_19_20 * K3_20 - U_19_21 * K3_21 - U_19_22 * K3_22 - U_19_23 * K3_23 - U_19_24 * K3_24) / U_19_19;
          // Block 14: K3 backward sub [NH4a]
          double K3_18 = (y3_18 - U_18_19 * K3_19 - U_18_21 * K3_21) / U_18_18;
          // Block 13: K3 backward sub [DUST1]
          double K3_17 = y3_17 / U_17_17;
          // Block 12: K3 backward sub [DUST2]
          double K3_16 = y3_16 / U_16_16;
          // Block 11: K3 backward sub [DUST4]
          double K3_15 = y3_15 / U_15_15;
          // Block 10: K3 backward sub [DUST5]
          double K3_14 = y3_14 / U_14_14;
          // Block 9: K3 backward sub [SS2]
          double K3_13 = y3_13 / U_13_13;
          // Block 8: K3 backward sub [SS3]
          double K3_12 = y3_12 / U_12_12;
          // Block 7: K3 backward sub [SS5]
          double K3_11 = y3_11 / U_11_11;
          // Block 6: K3 backward sub [NH3]
          double K3_10 = (y3_10 - U_10_19 * K3_19 - U_10_21 * K3_21) / U_10_10;
          // Block 5: K3 backward sub [NO3an2]
          double K3_9 = (y3_9 - U_9_12 * K3_12 - U_9_14 * K3_14 - U_9_16 * K3_16 - U_9_21 * K3_21) / U_9_9;
          // Block 4: K3 backward sub [NO3an1]
          double K3_8 = (y3_8 - U_8_10 * K3_10 - U_8_11 * K3_11 - U_8_13 * K3_13 - U_8_15 * K3_15 - U_8_17 * K3_17 - U_8_19 * K3_19 - U_8_21 * K3_21) / U_8_8;
          // Block 3: K3 backward sub [NO3]
          double K3_7 = (y3_7 - U_7_20 * K3_20) / U_7_7;
          // Block 2: K3 backward sub [H2O2]
          double K3_6 = (y3_6 - U_6_20 * K3_20) / U_6_6;
          double K3_5 = (y3_5 - U_5_6 * K3_6 - U_5_7 * K3_7 - U_5_20 * K3_20) / U_5_5;
          // Block 0: K3 backward sub [OC1, OC2, BC1, BC2, OH]
          double K3_4 = (y3_4 - U_4_5 * K3_5 - U_4_6 * K3_6 - U_4_20 * K3_20) / U_4_4;
          double K3_3 = y3_3 / U_3_3;
          double K3_2 = y3_2 / U_2_2;
          double K3_1 = y3_1 / U_1_1;
          double K3_0 = y3_0 / U_0_0;

          // --- Solution update and error estimation ---
          double err_norm_sq = 0.0;
          {
              double Ynew_i = S_0 + K1_0 + 6.1697947043828245 * K2_0 + -0.42772256543218573 * K3_0;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(8)), Kokkos::fabs(Ynew_i));
              double sci = atol[0] + rtol[0] * ymax;
              double yerr_i = 0.5 * K1_0 + -2.9079558716805471 * K2_0 + 0.22354069897811571 * K3_0;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_1 + K1_1 + 6.1697947043828245 * K2_1 + -0.42772256543218573 * K3_1;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(9)), Kokkos::fabs(Ynew_i));
              double sci = atol[1] + rtol[1] * ymax;
              double yerr_i = 0.5 * K1_1 + -2.9079558716805471 * K2_1 + 0.22354069897811571 * K3_1;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_2 + K1_2 + 6.1697947043828245 * K2_2 + -0.42772256543218573 * K3_2;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(6)), Kokkos::fabs(Ynew_i));
              double sci = atol[2] + rtol[2] * ymax;
              double yerr_i = 0.5 * K1_2 + -2.9079558716805471 * K2_2 + 0.22354069897811571 * K3_2;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_3 + K1_3 + 6.1697947043828245 * K2_3 + -0.42772256543218573 * K3_3;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(7)), Kokkos::fabs(Ynew_i));
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
              double ymax = Kokkos::fmax(Kokkos::fabs(state(3)), Kokkos::fabs(Ynew_i));
              double sci = atol[5] + rtol[5] * ymax;
              double yerr_i = 0.5 * K1_5 + -2.9079558716805471 * K2_5 + 0.22354069897811571 * K3_5;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_6 + K1_6 + 6.1697947043828245 * K2_6 + -0.42772256543218573 * K3_6;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(2)), Kokkos::fabs(Ynew_i));
              double sci = atol[6] + rtol[6] * ymax;
              double yerr_i = 0.5 * K1_6 + -2.9079558716805471 * K2_6 + 0.22354069897811571 * K3_6;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_7 + K1_7 + 6.1697947043828245 * K2_7 + -0.42772256543218573 * K3_7;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(1)), Kokkos::fabs(Ynew_i));
              double sci = atol[7] + rtol[7] * ymax;
              double yerr_i = 0.5 * K1_7 + -2.9079558716805471 * K2_7 + 0.22354069897811571 * K3_7;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_8 + K1_8 + 6.1697947043828245 * K2_8 + -0.42772256543218573 * K3_8;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(23)), Kokkos::fabs(Ynew_i));
              double sci = atol[8] + rtol[8] * ymax;
              double yerr_i = 0.5 * K1_8 + -2.9079558716805471 * K2_8 + 0.22354069897811571 * K3_8;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_9 + K1_9 + 6.1697947043828245 * K2_9 + -0.42772256543218573 * K3_9;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(24)), Kokkos::fabs(Ynew_i));
              double sci = atol[9] + rtol[9] * ymax;
              double yerr_i = 0.5 * K1_9 + -2.9079558716805471 * K2_9 + 0.22354069897811571 * K3_9;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_10 + K1_10 + 6.1697947043828245 * K2_10 + -0.42772256543218573 * K3_10;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(21)), Kokkos::fabs(Ynew_i));
              double sci = atol[10] + rtol[10] * ymax;
              double yerr_i = 0.5 * K1_10 + -2.9079558716805471 * K2_10 + 0.22354069897811571 * K3_10;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_11 + K1_11 + 6.1697947043828245 * K2_11 + -0.42772256543218573 * K3_11;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(19)), Kokkos::fabs(Ynew_i));
              double sci = atol[11] + rtol[11] * ymax;
              double yerr_i = 0.5 * K1_11 + -2.9079558716805471 * K2_11 + 0.22354069897811571 * K3_11;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_12 + K1_12 + 6.1697947043828245 * K2_12 + -0.42772256543218573 * K3_12;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(17)), Kokkos::fabs(Ynew_i));
              double sci = atol[12] + rtol[12] * ymax;
              double yerr_i = 0.5 * K1_12 + -2.9079558716805471 * K2_12 + 0.22354069897811571 * K3_12;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_13 + K1_13 + 6.1697947043828245 * K2_13 + -0.42772256543218573 * K3_13;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(16)), Kokkos::fabs(Ynew_i));
              double sci = atol[13] + rtol[13] * ymax;
              double yerr_i = 0.5 * K1_13 + -2.9079558716805471 * K2_13 + 0.22354069897811571 * K3_13;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_14 + K1_14 + 6.1697947043828245 * K2_14 + -0.42772256543218573 * K3_14;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(14)), Kokkos::fabs(Ynew_i));
              double sci = atol[14] + rtol[14] * ymax;
              double yerr_i = 0.5 * K1_14 + -2.9079558716805471 * K2_14 + 0.22354069897811571 * K3_14;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_15 + K1_15 + 6.1697947043828245 * K2_15 + -0.42772256543218573 * K3_15;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(13)), Kokkos::fabs(Ynew_i));
              double sci = atol[15] + rtol[15] * ymax;
              double yerr_i = 0.5 * K1_15 + -2.9079558716805471 * K2_15 + 0.22354069897811571 * K3_15;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_16 + K1_16 + 6.1697947043828245 * K2_16 + -0.42772256543218573 * K3_16;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(11)), Kokkos::fabs(Ynew_i));
              double sci = atol[16] + rtol[16] * ymax;
              double yerr_i = 0.5 * K1_16 + -2.9079558716805471 * K2_16 + 0.22354069897811571 * K3_16;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_17 + K1_17 + 6.1697947043828245 * K2_17 + -0.42772256543218573 * K3_17;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(10)), Kokkos::fabs(Ynew_i));
              double sci = atol[17] + rtol[17] * ymax;
              double yerr_i = 0.5 * K1_17 + -2.9079558716805471 * K2_17 + 0.22354069897811571 * K3_17;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_18 + K1_18 + 6.1697947043828245 * K2_18 + -0.42772256543218573 * K3_18;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(22)), Kokkos::fabs(Ynew_i));
              double sci = atol[18] + rtol[18] * ymax;
              double yerr_i = 0.5 * K1_18 + -2.9079558716805471 * K2_18 + 0.22354069897811571 * K3_18;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_19 + K1_19 + 6.1697947043828245 * K2_19 + -0.42772256543218573 * K3_19;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(5)), Kokkos::fabs(Ynew_i));
              double sci = atol[19] + rtol[19] * ymax;
              double yerr_i = 0.5 * K1_19 + -2.9079558716805471 * K2_19 + 0.22354069897811571 * K3_19;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_20 + K1_20 + 6.1697947043828245 * K2_20 + -0.42772256543218573 * K3_20;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(4)), Kokkos::fabs(Ynew_i));
              double sci = atol[20] + rtol[20] * ymax;
              double yerr_i = 0.5 * K1_20 + -2.9079558716805471 * K2_20 + 0.22354069897811571 * K3_20;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_21 + K1_21 + 6.1697947043828245 * K2_21 + -0.42772256543218573 * K3_21;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(20)), Kokkos::fabs(Ynew_i));
              double sci = atol[21] + rtol[21] * ymax;
              double yerr_i = 0.5 * K1_21 + -2.9079558716805471 * K2_21 + 0.22354069897811571 * K3_21;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_22 + K1_22 + 6.1697947043828245 * K2_22 + -0.42772256543218573 * K3_22;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(15)), Kokkos::fabs(Ynew_i));
              double sci = atol[22] + rtol[22] * ymax;
              double yerr_i = 0.5 * K1_22 + -2.9079558716805471 * K2_22 + 0.22354069897811571 * K3_22;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_23 + K1_23 + 6.1697947043828245 * K2_23 + -0.42772256543218573 * K3_23;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(12)), Kokkos::fabs(Ynew_i));
              double sci = atol[23] + rtol[23] * ymax;
              double yerr_i = 0.5 * K1_23 + -2.9079558716805471 * K2_23 + 0.22354069897811571 * K3_23;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_24 + K1_24 + 6.1697947043828245 * K2_24 + -0.42772256543218573 * K3_24;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(18)), Kokkos::fabs(Ynew_i));
              double sci = atol[24] + rtol[24] * ymax;
              double yerr_i = 0.5 * K1_24 + -2.9079558716805471 * K2_24 + 0.22354069897811571 * K3_24;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_25 + K1_25 + 6.1697947043828245 * K2_25 + -0.42772256543218573 * K3_25;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(25)), Kokkos::fabs(Ynew_i));
              double sci = atol[25] + rtol[25] * ymax;
              double yerr_i = 0.5 * K1_25 + -2.9079558716805471 * K2_25 + 0.22354069897811571 * K3_25;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          double err_norm = Kokkos::sqrt(err_norm_sq / 26);
          err_norm = Kokkos::fmax(err_norm, 1.0e-10);

          // Step Size Control (order 3: exponent = 1/3 = 0.33333333333333331)
          double factor = safety / Kokkos::cbrt(err_norm);
          factor = Kokkos::fmax(min_shrink, Kokkos::fmin(factor, max_growth));

          if (err_norm <= 1.0) {
              state(8) += K1_0 + 6.1697947043828245 * K2_0 + -0.42772256543218573 * K3_0;
              state(9) += K1_1 + 6.1697947043828245 * K2_1 + -0.42772256543218573 * K3_1;
              state(6) += K1_2 + 6.1697947043828245 * K2_2 + -0.42772256543218573 * K3_2;
              state(7) += K1_3 + 6.1697947043828245 * K2_3 + -0.42772256543218573 * K3_3;
              state(0) += K1_4 + 6.1697947043828245 * K2_4 + -0.42772256543218573 * K3_4;
              state(3) += K1_5 + 6.1697947043828245 * K2_5 + -0.42772256543218573 * K3_5;
              state(2) += K1_6 + 6.1697947043828245 * K2_6 + -0.42772256543218573 * K3_6;
              state(1) += K1_7 + 6.1697947043828245 * K2_7 + -0.42772256543218573 * K3_7;
              state(23) += K1_8 + 6.1697947043828245 * K2_8 + -0.42772256543218573 * K3_8;
              state(24) += K1_9 + 6.1697947043828245 * K2_9 + -0.42772256543218573 * K3_9;
              state(21) += K1_10 + 6.1697947043828245 * K2_10 + -0.42772256543218573 * K3_10;
              state(19) += K1_11 + 6.1697947043828245 * K2_11 + -0.42772256543218573 * K3_11;
              state(17) += K1_12 + 6.1697947043828245 * K2_12 + -0.42772256543218573 * K3_12;
              state(16) += K1_13 + 6.1697947043828245 * K2_13 + -0.42772256543218573 * K3_13;
              state(14) += K1_14 + 6.1697947043828245 * K2_14 + -0.42772256543218573 * K3_14;
              state(13) += K1_15 + 6.1697947043828245 * K2_15 + -0.42772256543218573 * K3_15;
              state(11) += K1_16 + 6.1697947043828245 * K2_16 + -0.42772256543218573 * K3_16;
              state(10) += K1_17 + 6.1697947043828245 * K2_17 + -0.42772256543218573 * K3_17;
              state(22) += K1_18 + 6.1697947043828245 * K2_18 + -0.42772256543218573 * K3_18;
              state(5) += K1_19 + 6.1697947043828245 * K2_19 + -0.42772256543218573 * K3_19;
              state(4) += K1_20 + 6.1697947043828245 * K2_20 + -0.42772256543218573 * K3_20;
              state(20) += K1_21 + 6.1697947043828245 * K2_21 + -0.42772256543218573 * K3_21;
              state(15) += K1_22 + 6.1697947043828245 * K2_22 + -0.42772256543218573 * K3_22;
              state(12) += K1_23 + 6.1697947043828245 * K2_23 + -0.42772256543218573 * K3_23;
              state(18) += K1_24 + 6.1697947043828245 * K2_24 + -0.42772256543218573 * K3_24;
              state(25) += K1_25 + 6.1697947043828245 * K2_25 + -0.42772256543218573 * K3_25;
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
          const int NUM_SPECIES = 26;
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
          active[11] = true;
          active[12] = true;
          active[13] = true;
          active[14] = true;
          active[15] = true;
          active[16] = true;
          active[17] = true;
          active[18] = true;
          active[19] = true;
          active[20] = true;
          active[21] = true;
          active[22] = true;
          active[23] = true;
          active[24] = true;
          active[25] = true;

          while (t < dt_total) {
          dt = Kokkos::min(dt, dt_total - t);
          const double inv_g_dt = 1.0 / (g * dt);

          // 0. Hoist state values into scalar registers
          // NOTE: State access uses permuted species ordering
          const double S_0 = state(8);
          const double S_1 = state(9);
          const double S_2 = state(6);
          const double S_3 = state(7);
          const double S_4 = state(0);
          const double S_5 = state(3);
          const double S_6 = state(2);
          const double S_7 = state(1);
          const double S_8 = state(23);
          const double S_9 = state(24);
          const double S_10 = state(21);
          const double S_11 = state(19);
          const double S_12 = state(17);
          const double S_13 = state(16);
          const double S_14 = state(14);
          const double S_15 = state(13);
          const double S_16 = state(11);
          const double S_17 = state(10);
          const double S_18 = state(22);
          const double S_19 = state(5);
          const double S_20 = state(4);
          const double S_21 = state(20);
          const double S_22 = state(15);
          const double S_23 = state(12);
          const double S_24 = state(18);
          const double S_25 = state(25);

          // 1. Stage 1 Rates (F1)
          double F1_0 = -5.0442046141041832e-12*S_3*S_0 + 2.0*S_2*jvals[0] - 3.3000000000000001e-12*S_0*S_4;
          double F1_1 = -3.3571944693753379e-14*S_3*S_1;
          double F1_2 = -0.0025000000000000001*S_2*S_4 - 1.0*S_2*jvals[0];
          double F1_3 = -3.3571944693753379e-14*S_3*S_1 - 5.0442046141041832e-12*S_3*S_0;
          double F1_4 = 3.3571944693753379e-14*S_3*S_1 + 5.0442046141041832e-12*S_3*S_0 - 2.5000000000000001e-5*S_10*S_4 - 2.5000000000000001e-5*S_11*S_4 - 2.5000000000000001e-5*S_12*S_4 - 2.5000000000000001e-5*S_13*S_4 - 2.5000000000000001e-5*S_14*S_4 - 0.0025000000000000001*S_2*S_4 - 3.3000000000000001e-12*S_0*S_4 - 0.00025000000000000001*S_4*S_15 - 0.00025000000000000001*S_4*S_16 - 0.00025000000000000001*S_4*S_17 - 0.00025000000000000001*S_4*S_18 - 0.00025000000000000001*S_4*S_19;
          double F1_5 = 2.5000000000000001e-5*S_10*S_4 + 2.5000000000000001e-5*S_11*S_4 + 2.5000000000000001e-5*S_12*S_4 + 2.5000000000000001e-5*S_13*S_4 + 2.5000000000000001e-5*S_14*S_4 + 0.0025000000000000001*S_2*S_4 - 1.0*S_20*S_21*S_5*jvals[27] + 3.3000000000000001e-12*S_0*S_4 + 0.00025000000000000001*S_4*S_15 + 0.00025000000000000001*S_4*S_16 + 0.00025000000000000001*S_4*S_17 + 0.00025000000000000001*S_4*S_18 + 0.00025000000000000001*S_4*S_19;
          double F1_6 = -5.0000000000000004e-6*S_6;
          double F1_7 = 5.0000000000000004e-6*S_6;
          double F1_8 = -5.0000000000000004e-6*S_8;
          double F1_9 = 5.0000000000000004e-6*S_8;
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
          double F1_20 = -0.025000000000000001*S_10*S_20 - 0.025000000000000001*S_11*S_20 - 0.025000000000000001*S_12*S_20 - 0.025000000000000001*S_13*S_20 - 0.025000000000000001*S_14*S_20 - 1.0*S_20*S_21*S_5*jvals[27] - 0.025000000000000001*S_20*S_15 - 0.025000000000000001*S_20*S_16 - 0.025000000000000001*S_20*S_17 - 0.025000000000000001*S_20*S_18 - 0.025000000000000001*S_20*S_19;
          double F1_21 = -1.0*S_20*S_21*S_5*jvals[27];
          double F1_22 = 1.0*S_20*S_21*S_5*jvals[27];
          double F1_23 = 0.025000000000000001*S_10*S_20 + 0.025000000000000001*S_13*S_20 + 1.0*S_20*S_21*S_5*jvals[27] + 0.025000000000000001*S_20*S_16 + 0.025000000000000001*S_20*S_19;
          double F1_24 = 0.025000000000000001*S_11*S_20 + 0.025000000000000001*S_14*S_20 + 0.025000000000000001*S_20*S_17;
          double F1_25 = 0.025000000000000001*S_12*S_20 + 0.025000000000000001*S_20*S_15 + 0.025000000000000001*S_20*S_18;

          // 2. Evaluate importance and update active set
          active[0] = (Kokkos::fabs(F1_0) / (atol[0] + rtol[0] * Kokkos::fabs(state(8))) >= importance_threshold);
          active[1] = (Kokkos::fabs(F1_1) / (atol[1] + rtol[1] * Kokkos::fabs(state(9))) >= importance_threshold);
          active[2] = (Kokkos::fabs(F1_2) / (atol[2] + rtol[2] * Kokkos::fabs(state(6))) >= importance_threshold);
          active[3] = (Kokkos::fabs(F1_3) / (atol[3] + rtol[3] * Kokkos::fabs(state(7))) >= importance_threshold);
          active[4] = (Kokkos::fabs(F1_4) / (atol[4] + rtol[4] * Kokkos::fabs(state(0))) >= importance_threshold);
          active[5] = (Kokkos::fabs(F1_5) / (atol[5] + rtol[5] * Kokkos::fabs(state(3))) >= importance_threshold);
          active[6] = (Kokkos::fabs(F1_6) / (atol[6] + rtol[6] * Kokkos::fabs(state(2))) >= importance_threshold);
          active[7] = (Kokkos::fabs(F1_7) / (atol[7] + rtol[7] * Kokkos::fabs(state(1))) >= importance_threshold);
          active[8] = (Kokkos::fabs(F1_8) / (atol[8] + rtol[8] * Kokkos::fabs(state(23))) >= importance_threshold);
          active[9] = (Kokkos::fabs(F1_9) / (atol[9] + rtol[9] * Kokkos::fabs(state(24))) >= importance_threshold);
          active[10] = (Kokkos::fabs(F1_10) / (atol[10] + rtol[10] * Kokkos::fabs(state(21))) >= importance_threshold);
          active[11] = (Kokkos::fabs(F1_11) / (atol[11] + rtol[11] * Kokkos::fabs(state(19))) >= importance_threshold);
          active[12] = (Kokkos::fabs(F1_12) / (atol[12] + rtol[12] * Kokkos::fabs(state(17))) >= importance_threshold);
          active[13] = (Kokkos::fabs(F1_13) / (atol[13] + rtol[13] * Kokkos::fabs(state(16))) >= importance_threshold);
          active[14] = (Kokkos::fabs(F1_14) / (atol[14] + rtol[14] * Kokkos::fabs(state(14))) >= importance_threshold);
          active[15] = (Kokkos::fabs(F1_15) / (atol[15] + rtol[15] * Kokkos::fabs(state(13))) >= importance_threshold);
          active[16] = (Kokkos::fabs(F1_16) / (atol[16] + rtol[16] * Kokkos::fabs(state(11))) >= importance_threshold);
          active[17] = (Kokkos::fabs(F1_17) / (atol[17] + rtol[17] * Kokkos::fabs(state(10))) >= importance_threshold);
          active[18] = (Kokkos::fabs(F1_18) / (atol[18] + rtol[18] * Kokkos::fabs(state(22))) >= importance_threshold);
          active[19] = (Kokkos::fabs(F1_19) / (atol[19] + rtol[19] * Kokkos::fabs(state(5))) >= importance_threshold);
          active[20] = (Kokkos::fabs(F1_20) / (atol[20] + rtol[20] * Kokkos::fabs(state(4))) >= importance_threshold);
          active[21] = (Kokkos::fabs(F1_21) / (atol[21] + rtol[21] * Kokkos::fabs(state(20))) >= importance_threshold);
          active[22] = (Kokkos::fabs(F1_22) / (atol[22] + rtol[22] * Kokkos::fabs(state(15))) >= importance_threshold);
          active[23] = (Kokkos::fabs(F1_23) / (atol[23] + rtol[23] * Kokkos::fabs(state(12))) >= importance_threshold);
          active[24] = (Kokkos::fabs(F1_24) / (atol[24] + rtol[24] * Kokkos::fabs(state(18))) >= importance_threshold);
          active[25] = (Kokkos::fabs(F1_25) / (atol[25] + rtol[25] * Kokkos::fabs(state(25))) >= importance_threshold);

          // 3. Analytical Jacobian & Iteration Matrix W (identity for frozen species)
          double J_0_0 = -5.0000000000000004e-6;
          double J_1_0 = 5.0000000000000004e-6;
          double J_2_2 = -5.0000000000000004e-6;
          double J_3_2 = 5.0000000000000004e-6;
          double J_4_4 = -5.0442046141041832e-12*S_3 - 3.3000000000000001e-12*S_4;
          double J_4_5 = -5.0442046141041832e-12*S_0;
          double J_4_6 = 2.0*jvals[0];
          double J_4_20 = -3.3000000000000001e-12*S_0;
          double J_5_4 = -5.0442046141041832e-12*S_3;
          double J_5_5 = -3.3571944693753379e-14*S_1 - 5.0442046141041832e-12*S_0;
          double J_5_7 = -3.3571944693753379e-14*S_3;
          double J_6_6 = -0.0025000000000000001*S_4 - 1.0*jvals[0];
          double J_6_20 = -0.0025000000000000001*S_2;
          double J_7_5 = -3.3571944693753379e-14*S_1;
          double J_7_7 = -3.3571944693753379e-14*S_3;
          double J_8_10 = 1.0*S_20*S_5*jvals[27];
          double J_8_11 = 0.025000000000000001*S_20;
          double J_8_13 = 0.025000000000000001*S_20;
          double J_8_15 = 0.025000000000000001*S_20;
          double J_8_17 = 0.025000000000000001*S_20;
          double J_8_19 = 1.0*S_20*S_21*jvals[27];
          double J_8_21 = 0.025000000000000001*S_10 + 0.025000000000000001*S_13 + 1.0*S_21*S_5*jvals[27] + 0.025000000000000001*S_16 + 0.025000000000000001*S_19;
          double J_9_12 = 0.025000000000000001*S_20;
          double J_9_14 = 0.025000000000000001*S_20;
          double J_9_16 = 0.025000000000000001*S_20;
          double J_9_21 = 0.025000000000000001*S_11 + 0.025000000000000001*S_14 + 0.025000000000000001*S_17;
          double J_10_10 = -1.0*S_20*S_5*jvals[27];
          double J_10_19 = -1.0*S_20*S_21*jvals[27];
          double J_10_21 = -1.0*S_21*S_5*jvals[27];
          double J_18_10 = 1.0*S_20*S_5*jvals[27];
          double J_18_19 = 1.0*S_20*S_21*jvals[27];
          double J_18_21 = 1.0*S_21*S_5*jvals[27];
          double J_19_4 = 3.3000000000000001e-12*S_4;
          double J_19_6 = 0.0025000000000000001*S_4;
          double J_19_10 = -1.0*S_20*S_5*jvals[27];
          double J_19_11 = 0.00025000000000000001*S_4;
          double J_19_12 = 0.00025000000000000001*S_4;
          double J_19_13 = 0.00025000000000000001*S_4;
          double J_19_14 = 2.5000000000000001e-5*S_4;
          double J_19_15 = 2.5000000000000001e-5*S_4;
          double J_19_16 = 2.5000000000000001e-5*S_4;
          double J_19_17 = 2.5000000000000001e-5*S_4;
          double J_19_19 = -1.0*S_20*S_21*jvals[27];
          double J_19_20 = 2.5000000000000001e-5*S_10 + 2.5000000000000001e-5*S_11 + 2.5000000000000001e-5*S_12 + 2.5000000000000001e-5*S_13 + 2.5000000000000001e-5*S_14 + 0.0025000000000000001*S_2 + 3.3000000000000001e-12*S_0 + 0.00025000000000000001*S_15 + 0.00025000000000000001*S_16 + 0.00025000000000000001*S_17 + 0.00025000000000000001*S_18 + 0.00025000000000000001*S_19;
          double J_19_21 = -1.0*S_21*S_5*jvals[27];
          double J_19_22 = 0.00025000000000000001*S_4;
          double J_19_23 = 2.5000000000000001e-5*S_4;
          double J_19_24 = 0.00025000000000000001*S_4;
          double J_20_4 = 5.0442046141041832e-12*S_3 - 3.3000000000000001e-12*S_4;
          double J_20_5 = 3.3571944693753379e-14*S_1 + 5.0442046141041832e-12*S_0;
          double J_20_6 = -0.0025000000000000001*S_4;
          double J_20_7 = 3.3571944693753379e-14*S_3;
          double J_20_11 = -0.00025000000000000001*S_4;
          double J_20_12 = -0.00025000000000000001*S_4;
          double J_20_13 = -0.00025000000000000001*S_4;
          double J_20_14 = -2.5000000000000001e-5*S_4;
          double J_20_15 = -2.5000000000000001e-5*S_4;
          double J_20_16 = -2.5000000000000001e-5*S_4;
          double J_20_17 = -2.5000000000000001e-5*S_4;
          double J_20_20 = -2.5000000000000001e-5*S_10 - 2.5000000000000001e-5*S_11 - 2.5000000000000001e-5*S_12 - 2.5000000000000001e-5*S_13 - 2.5000000000000001e-5*S_14 - 0.0025000000000000001*S_2 - 3.3000000000000001e-12*S_0 - 0.00025000000000000001*S_15 - 0.00025000000000000001*S_16 - 0.00025000000000000001*S_17 - 0.00025000000000000001*S_18 - 0.00025000000000000001*S_19;
          double J_20_22 = -0.00025000000000000001*S_4;
          double J_20_23 = -2.5000000000000001e-5*S_4;
          double J_20_24 = -0.00025000000000000001*S_4;
          double J_21_10 = -1.0*S_20*S_5*jvals[27];
          double J_21_11 = -0.025000000000000001*S_20;
          double J_21_12 = -0.025000000000000001*S_20;
          double J_21_13 = -0.025000000000000001*S_20;
          double J_21_14 = -0.025000000000000001*S_20;
          double J_21_15 = -0.025000000000000001*S_20;
          double J_21_16 = -0.025000000000000001*S_20;
          double J_21_17 = -0.025000000000000001*S_20;
          double J_21_19 = -1.0*S_20*S_21*jvals[27];
          double J_21_21 = -0.025000000000000001*S_10 - 0.025000000000000001*S_11 - 0.025000000000000001*S_12 - 0.025000000000000001*S_13 - 0.025000000000000001*S_14 - 1.0*S_21*S_5*jvals[27] - 0.025000000000000001*S_15 - 0.025000000000000001*S_16 - 0.025000000000000001*S_17 - 0.025000000000000001*S_18 - 0.025000000000000001*S_19;
          double J_21_22 = -0.025000000000000001*S_20;
          double J_21_23 = -0.025000000000000001*S_20;
          double J_21_24 = -0.025000000000000001*S_20;
          double J_25_21 = 0.025000000000000001*S_12 + 0.025000000000000001*S_15 + 0.025000000000000001*S_18;
          double J_25_22 = 0.025000000000000001*S_20;
          double J_25_23 = 0.025000000000000001*S_20;
          double J_25_24 = 0.025000000000000001*S_20;
          double W_0_0 = active[0] ? (inv_g_dt - J_0_0) : 1.0;
          double W_1_0 = (active[1] && active[0]) ? (-J_1_0) : 0.0;
          double W_1_1 = active[1] ? inv_g_dt : 1.0;
          double W_2_2 = active[2] ? (inv_g_dt - J_2_2) : 1.0;
          double W_3_2 = (active[3] && active[2]) ? (-J_3_2) : 0.0;
          double W_3_3 = active[3] ? inv_g_dt : 1.0;
          double W_4_4 = active[4] ? (inv_g_dt - J_4_4) : 1.0;
          double W_4_5 = (active[4] && active[5]) ? (-J_4_5) : 0.0;
          double W_4_6 = (active[4] && active[6]) ? (-J_4_6) : 0.0;
          double W_4_20 = (active[4] && active[20]) ? (-J_4_20) : 0.0;
          double W_5_4 = (active[5] && active[4]) ? (-J_5_4) : 0.0;
          double W_5_5 = active[5] ? (inv_g_dt - J_5_5) : 1.0;
          double W_5_7 = (active[5] && active[7]) ? (-J_5_7) : 0.0;
          double W_6_6 = active[6] ? (inv_g_dt - J_6_6) : 1.0;
          double W_6_20 = (active[6] && active[20]) ? (-J_6_20) : 0.0;
          double W_7_5 = (active[7] && active[5]) ? (-J_7_5) : 0.0;
          double W_7_7 = active[7] ? (inv_g_dt - J_7_7) : 1.0;
          double W_8_8 = active[8] ? inv_g_dt : 1.0;
          double W_8_10 = (active[8] && active[10]) ? (-J_8_10) : 0.0;
          double W_8_11 = (active[8] && active[11]) ? (-J_8_11) : 0.0;
          double W_8_13 = (active[8] && active[13]) ? (-J_8_13) : 0.0;
          double W_8_15 = (active[8] && active[15]) ? (-J_8_15) : 0.0;
          double W_8_17 = (active[8] && active[17]) ? (-J_8_17) : 0.0;
          double W_8_19 = (active[8] && active[19]) ? (-J_8_19) : 0.0;
          double W_8_21 = (active[8] && active[21]) ? (-J_8_21) : 0.0;
          double W_9_9 = active[9] ? inv_g_dt : 1.0;
          double W_9_12 = (active[9] && active[12]) ? (-J_9_12) : 0.0;
          double W_9_14 = (active[9] && active[14]) ? (-J_9_14) : 0.0;
          double W_9_16 = (active[9] && active[16]) ? (-J_9_16) : 0.0;
          double W_9_21 = (active[9] && active[21]) ? (-J_9_21) : 0.0;
          double W_10_10 = active[10] ? (inv_g_dt - J_10_10) : 1.0;
          double W_10_19 = (active[10] && active[19]) ? (-J_10_19) : 0.0;
          double W_10_21 = (active[10] && active[21]) ? (-J_10_21) : 0.0;
          double W_11_11 = active[11] ? inv_g_dt : 1.0;
          double W_12_12 = active[12] ? inv_g_dt : 1.0;
          double W_13_13 = active[13] ? inv_g_dt : 1.0;
          double W_14_14 = active[14] ? inv_g_dt : 1.0;
          double W_15_15 = active[15] ? inv_g_dt : 1.0;
          double W_16_16 = active[16] ? inv_g_dt : 1.0;
          double W_17_17 = active[17] ? inv_g_dt : 1.0;
          double W_18_10 = (active[18] && active[10]) ? (-J_18_10) : 0.0;
          double W_18_18 = active[18] ? inv_g_dt : 1.0;
          double W_18_19 = (active[18] && active[19]) ? (-J_18_19) : 0.0;
          double W_18_21 = (active[18] && active[21]) ? (-J_18_21) : 0.0;
          double W_19_4 = (active[19] && active[4]) ? (-J_19_4) : 0.0;
          double W_19_6 = (active[19] && active[6]) ? (-J_19_6) : 0.0;
          double W_19_10 = (active[19] && active[10]) ? (-J_19_10) : 0.0;
          double W_19_11 = (active[19] && active[11]) ? (-J_19_11) : 0.0;
          double W_19_12 = (active[19] && active[12]) ? (-J_19_12) : 0.0;
          double W_19_13 = (active[19] && active[13]) ? (-J_19_13) : 0.0;
          double W_19_14 = (active[19] && active[14]) ? (-J_19_14) : 0.0;
          double W_19_15 = (active[19] && active[15]) ? (-J_19_15) : 0.0;
          double W_19_16 = (active[19] && active[16]) ? (-J_19_16) : 0.0;
          double W_19_17 = (active[19] && active[17]) ? (-J_19_17) : 0.0;
          double W_19_19 = active[19] ? (inv_g_dt - J_19_19) : 1.0;
          double W_19_20 = (active[19] && active[20]) ? (-J_19_20) : 0.0;
          double W_19_21 = (active[19] && active[21]) ? (-J_19_21) : 0.0;
          double W_19_22 = (active[19] && active[22]) ? (-J_19_22) : 0.0;
          double W_19_23 = (active[19] && active[23]) ? (-J_19_23) : 0.0;
          double W_19_24 = (active[19] && active[24]) ? (-J_19_24) : 0.0;
          double W_20_4 = (active[20] && active[4]) ? (-J_20_4) : 0.0;
          double W_20_5 = (active[20] && active[5]) ? (-J_20_5) : 0.0;
          double W_20_6 = (active[20] && active[6]) ? (-J_20_6) : 0.0;
          double W_20_7 = (active[20] && active[7]) ? (-J_20_7) : 0.0;
          double W_20_11 = (active[20] && active[11]) ? (-J_20_11) : 0.0;
          double W_20_12 = (active[20] && active[12]) ? (-J_20_12) : 0.0;
          double W_20_13 = (active[20] && active[13]) ? (-J_20_13) : 0.0;
          double W_20_14 = (active[20] && active[14]) ? (-J_20_14) : 0.0;
          double W_20_15 = (active[20] && active[15]) ? (-J_20_15) : 0.0;
          double W_20_16 = (active[20] && active[16]) ? (-J_20_16) : 0.0;
          double W_20_17 = (active[20] && active[17]) ? (-J_20_17) : 0.0;
          double W_20_20 = active[20] ? (inv_g_dt - J_20_20) : 1.0;
          double W_20_22 = (active[20] && active[22]) ? (-J_20_22) : 0.0;
          double W_20_23 = (active[20] && active[23]) ? (-J_20_23) : 0.0;
          double W_20_24 = (active[20] && active[24]) ? (-J_20_24) : 0.0;
          double W_21_10 = (active[21] && active[10]) ? (-J_21_10) : 0.0;
          double W_21_11 = (active[21] && active[11]) ? (-J_21_11) : 0.0;
          double W_21_12 = (active[21] && active[12]) ? (-J_21_12) : 0.0;
          double W_21_13 = (active[21] && active[13]) ? (-J_21_13) : 0.0;
          double W_21_14 = (active[21] && active[14]) ? (-J_21_14) : 0.0;
          double W_21_15 = (active[21] && active[15]) ? (-J_21_15) : 0.0;
          double W_21_16 = (active[21] && active[16]) ? (-J_21_16) : 0.0;
          double W_21_17 = (active[21] && active[17]) ? (-J_21_17) : 0.0;
          double W_21_19 = (active[21] && active[19]) ? (-J_21_19) : 0.0;
          double W_21_21 = active[21] ? (inv_g_dt - J_21_21) : 1.0;
          double W_21_22 = (active[21] && active[22]) ? (-J_21_22) : 0.0;
          double W_21_23 = (active[21] && active[23]) ? (-J_21_23) : 0.0;
          double W_21_24 = (active[21] && active[24]) ? (-J_21_24) : 0.0;
          double W_22_22 = active[22] ? inv_g_dt : 1.0;
          double W_23_23 = active[23] ? inv_g_dt : 1.0;
          double W_24_24 = active[24] ? inv_g_dt : 1.0;
          double W_25_21 = (active[25] && active[21]) ? (-J_25_21) : 0.0;
          double W_25_22 = (active[25] && active[22]) ? (-J_25_22) : 0.0;
          double W_25_23 = (active[25] && active[23]) ? (-J_25_23) : 0.0;
          double W_25_24 = (active[25] && active[24]) ? (-J_25_24) : 0.0;
          double W_25_25 = active[25] ? inv_g_dt : 1.0;

          // 4. Symbolic LU Factorization (conditional skip for frozen species)
          double U_0_0 = W_0_0;
          double L_1_0 = (W_1_0) / U_0_0;
          double U_1_1 = W_1_1;
          double U_2_2 = W_2_2;
          double L_3_2 = (W_3_2) / U_2_2;
          double U_3_3 = W_3_3;
          double U_4_4 = W_4_4;
          double U_4_5 = W_4_5;
          double U_4_6 = W_4_6;
          double U_4_20 = W_4_20;
          double L_5_4 = (W_5_4) / U_4_4;
          double L_19_4 = (W_19_4) / U_4_4;
          double L_20_4 = (W_20_4) / U_4_4;
          double U_5_5 = W_5_5 - L_5_4 * U_4_5;
          double U_5_6 = 0.0 - L_5_4 * U_4_6;
          double U_5_7 = W_5_7;
          double U_5_20 = 0.0 - L_5_4 * U_4_20;
          double L_7_5 = (W_7_5) / U_5_5;
          double L_19_5 = (0.0 - L_19_4 * U_4_5) / U_5_5;
          double L_20_5 = (W_20_5 - L_20_4 * U_4_5) / U_5_5;
          double U_6_6 = W_6_6;
          double U_6_20 = W_6_20;
          double L_7_6 = (0.0 - L_7_5 * U_5_6) / U_6_6;
          double L_19_6 = (W_19_6 - L_19_4 * U_4_6 - L_19_5 * U_5_6) / U_6_6;
          double L_20_6 = (W_20_6 - L_20_4 * U_4_6 - L_20_5 * U_5_6) / U_6_6;
          double U_7_7 = W_7_7 - L_7_5 * U_5_7;
          double U_7_20 = 0.0 - L_7_5 * U_5_20 - L_7_6 * U_6_20;
          double L_19_7 = (0.0 - L_19_5 * U_5_7) / U_7_7;
          double L_20_7 = (W_20_7 - L_20_5 * U_5_7) / U_7_7;
          double U_8_8 = W_8_8;
          double U_8_10 = W_8_10;
          double U_8_11 = W_8_11;
          double U_8_13 = W_8_13;
          double U_8_15 = W_8_15;
          double U_8_17 = W_8_17;
          double U_8_19 = W_8_19;
          double U_8_21 = W_8_21;
          double U_9_9 = W_9_9;
          double U_9_12 = W_9_12;
          double U_9_14 = W_9_14;
          double U_9_16 = W_9_16;
          double U_9_21 = W_9_21;
          double U_10_10 = W_10_10;
          double U_10_19 = W_10_19;
          double U_10_21 = W_10_21;
          double L_18_10 = (W_18_10) / U_10_10;
          double L_19_10 = (W_19_10) / U_10_10;
          double L_21_10 = (W_21_10) / U_10_10;
          double U_11_11 = W_11_11;
          double L_19_11 = (W_19_11) / U_11_11;
          double L_20_11 = (W_20_11) / U_11_11;
          double L_21_11 = (W_21_11) / U_11_11;
          double U_12_12 = W_12_12;
          double L_19_12 = (W_19_12) / U_12_12;
          double L_20_12 = (W_20_12) / U_12_12;
          double L_21_12 = (W_21_12) / U_12_12;
          double U_13_13 = W_13_13;
          double L_19_13 = (W_19_13) / U_13_13;
          double L_20_13 = (W_20_13) / U_13_13;
          double L_21_13 = (W_21_13) / U_13_13;
          double U_14_14 = W_14_14;
          double L_19_14 = (W_19_14) / U_14_14;
          double L_20_14 = (W_20_14) / U_14_14;
          double L_21_14 = (W_21_14) / U_14_14;
          double U_15_15 = W_15_15;
          double L_19_15 = (W_19_15) / U_15_15;
          double L_20_15 = (W_20_15) / U_15_15;
          double L_21_15 = (W_21_15) / U_15_15;
          double U_16_16 = W_16_16;
          double L_19_16 = (W_19_16) / U_16_16;
          double L_20_16 = (W_20_16) / U_16_16;
          double L_21_16 = (W_21_16) / U_16_16;
          double U_17_17 = W_17_17;
          double L_19_17 = (W_19_17) / U_17_17;
          double L_20_17 = (W_20_17) / U_17_17;
          double L_21_17 = (W_21_17) / U_17_17;
          double U_18_18 = W_18_18;
          double U_18_19 = W_18_19 - L_18_10 * U_10_19;
          double U_18_21 = W_18_21 - L_18_10 * U_10_21;
          double U_19_19 = W_19_19 - L_19_10 * U_10_19;
          double U_19_20 = W_19_20 - L_19_4 * U_4_20 - L_19_5 * U_5_20 - L_19_6 * U_6_20 - L_19_7 * U_7_20;
          double U_19_21 = W_19_21 - L_19_10 * U_10_21;
          double U_19_22 = W_19_22;
          double U_19_23 = W_19_23;
          double U_19_24 = W_19_24;
          double L_21_19 = (W_21_19 - L_21_10 * U_10_19) / U_19_19;
          double U_20_20 = W_20_20 - L_20_4 * U_4_20 - L_20_5 * U_5_20 - L_20_6 * U_6_20 - L_20_7 * U_7_20;
          double U_20_22 = W_20_22;
          double U_20_23 = W_20_23;
          double U_20_24 = W_20_24;
          double L_21_20 = (0.0 - L_21_19 * U_19_20) / U_20_20;
          double U_21_21 = W_21_21 - L_21_10 * U_10_21 - L_21_19 * U_19_21;
          double U_21_22 = W_21_22 - L_21_19 * U_19_22 - L_21_20 * U_20_22;
          double U_21_23 = W_21_23 - L_21_19 * U_19_23 - L_21_20 * U_20_23;
          double U_21_24 = W_21_24 - L_21_19 * U_19_24 - L_21_20 * U_20_24;
          double L_25_21 = (W_25_21) / U_21_21;
          double U_22_22 = W_22_22;
          double L_25_22 = (W_25_22 - L_25_21 * U_21_22) / U_22_22;
          double U_23_23 = W_23_23;
          double L_25_23 = (W_25_23 - L_25_21 * U_21_23) / U_23_23;
          double U_24_24 = W_24_24;
          double L_25_24 = (W_25_24 - L_25_21 * U_21_24) / U_24_24;
          double U_25_25 = W_25_25;

          // --- Stage 1 ---
          // F1 already computed above (used for importance evaluation)
          // Block 0: K1 forward sub [OC1, OC2, BC1, BC2, OH]
          double y1_0 = active[0] ? (F1_0) : 0.0;
          double y1_1 = active[1] ? (F1_1 - L_1_0 * y1_0) : 0.0;
          double y1_2 = active[2] ? (F1_2) : 0.0;
          double y1_3 = active[3] ? (F1_3 - L_3_2 * y1_2) : 0.0;
          double y1_4 = active[4] ? (F1_4) : 0.0;
          // Block 1: K1 forward sub [DMS, SO2, HNO3]
          double y1_5 = active[5] ? (F1_5 - L_5_4 * y1_4) : 0.0;
          // Block 2: K1 forward sub [H2O2]
          double y1_6 = active[6] ? (F1_6) : 0.0;
          // Block 3: K1 forward sub [NO3]
          double y1_7 = active[7] ? (F1_7 - L_7_5 * y1_5 - L_7_6 * y1_6) : 0.0;
          // Block 4: K1 forward sub [NO3an1]
          double y1_8 = active[8] ? (F1_8) : 0.0;
          // Block 5: K1 forward sub [NO3an2]
          double y1_9 = active[9] ? (F1_9) : 0.0;
          // Block 6: K1 forward sub [NH3]
          double y1_10 = active[10] ? (F1_10) : 0.0;
          // Block 7: K1 forward sub [SS5]
          double y1_11 = active[11] ? (F1_11) : 0.0;
          // Block 8: K1 forward sub [SS3]
          double y1_12 = active[12] ? (F1_12) : 0.0;
          // Block 9: K1 forward sub [SS2]
          double y1_13 = active[13] ? (F1_13) : 0.0;
          // Block 10: K1 forward sub [DUST5]
          double y1_14 = active[14] ? (F1_14) : 0.0;
          // Block 11: K1 forward sub [DUST4]
          double y1_15 = active[15] ? (F1_15) : 0.0;
          // Block 12: K1 forward sub [DUST2]
          double y1_16 = active[16] ? (F1_16) : 0.0;
          // Block 13: K1 forward sub [DUST1]
          double y1_17 = active[17] ? (F1_17) : 0.0;
          // Block 14: K1 forward sub [NH4a]
          double y1_18 = active[18] ? (F1_18 - L_18_10 * y1_10) : 0.0;
          // Block 15: K1 forward sub [SO4]
          double y1_19 = active[19] ? (F1_19 - L_19_4 * y1_4 - L_19_5 * y1_5 - L_19_6 * y1_6 - L_19_7 * y1_7 - L_19_10 * y1_10 - L_19_11 * y1_11 - L_19_12 * y1_12 - L_19_13 * y1_13 - L_19_14 * y1_14 - L_19_15 * y1_15 - L_19_16 * y1_16 - L_19_17 * y1_17) : 0.0;
          double y1_20 = active[20] ? (F1_20 - L_20_4 * y1_4 - L_20_5 * y1_5 - L_20_6 * y1_6 - L_20_7 * y1_7 - L_20_11 * y1_11 - L_20_12 * y1_12 - L_20_13 * y1_13 - L_20_14 * y1_14 - L_20_15 * y1_15 - L_20_16 * y1_16 - L_20_17 * y1_17) : 0.0;
          double y1_21 = active[21] ? (F1_21 - L_21_10 * y1_10 - L_21_11 * y1_11 - L_21_12 * y1_12 - L_21_13 * y1_13 - L_21_14 * y1_14 - L_21_15 * y1_15 - L_21_16 * y1_16 - L_21_17 * y1_17 - L_21_19 * y1_19 - L_21_20 * y1_20) : 0.0;
          // Block 16: K1 forward sub [SS1]
          double y1_22 = active[22] ? (F1_22) : 0.0;
          // Block 17: K1 forward sub [DUST3]
          double y1_23 = active[23] ? (F1_23) : 0.0;
          // Block 18: K1 forward sub [SS4]
          double y1_24 = active[24] ? (F1_24) : 0.0;
          // Block 19: K1 forward sub [NO3an3]
          double y1_25 = active[25] ? (F1_25 - L_25_21 * y1_21 - L_25_22 * y1_22 - L_25_23 * y1_23 - L_25_24 * y1_24) : 0.0;
          // Block 19: K1 backward sub [NO3an3]
          double K1_25 = active[25] ? (y1_25 / U_25_25) : 0.0;
          // Block 18: K1 backward sub [SS4]
          double K1_24 = active[24] ? (y1_24 / U_24_24) : 0.0;
          // Block 17: K1 backward sub [DUST3]
          double K1_23 = active[23] ? (y1_23 / U_23_23) : 0.0;
          // Block 16: K1 backward sub [SS1]
          double K1_22 = active[22] ? (y1_22 / U_22_22) : 0.0;
          // Block 1: K1 backward sub [DMS, SO2, HNO3]
          double K1_21 = active[21] ? ((y1_21 - U_21_22 * K1_22 - U_21_23 * K1_23 - U_21_24 * K1_24) / U_21_21) : 0.0;
          double K1_20 = active[20] ? ((y1_20 - U_20_22 * K1_22 - U_20_23 * K1_23 - U_20_24 * K1_24) / U_20_20) : 0.0;
          // Block 15: K1 backward sub [SO4]
          double K1_19 = active[19] ? ((y1_19 - U_19_20 * K1_20 - U_19_21 * K1_21 - U_19_22 * K1_22 - U_19_23 * K1_23 - U_19_24 * K1_24) / U_19_19) : 0.0;
          // Block 14: K1 backward sub [NH4a]
          double K1_18 = active[18] ? ((y1_18 - U_18_19 * K1_19 - U_18_21 * K1_21) / U_18_18) : 0.0;
          // Block 13: K1 backward sub [DUST1]
          double K1_17 = active[17] ? (y1_17 / U_17_17) : 0.0;
          // Block 12: K1 backward sub [DUST2]
          double K1_16 = active[16] ? (y1_16 / U_16_16) : 0.0;
          // Block 11: K1 backward sub [DUST4]
          double K1_15 = active[15] ? (y1_15 / U_15_15) : 0.0;
          // Block 10: K1 backward sub [DUST5]
          double K1_14 = active[14] ? (y1_14 / U_14_14) : 0.0;
          // Block 9: K1 backward sub [SS2]
          double K1_13 = active[13] ? (y1_13 / U_13_13) : 0.0;
          // Block 8: K1 backward sub [SS3]
          double K1_12 = active[12] ? (y1_12 / U_12_12) : 0.0;
          // Block 7: K1 backward sub [SS5]
          double K1_11 = active[11] ? (y1_11 / U_11_11) : 0.0;
          // Block 6: K1 backward sub [NH3]
          double K1_10 = active[10] ? ((y1_10 - U_10_19 * K1_19 - U_10_21 * K1_21) / U_10_10) : 0.0;
          // Block 5: K1 backward sub [NO3an2]
          double K1_9 = active[9] ? ((y1_9 - U_9_12 * K1_12 - U_9_14 * K1_14 - U_9_16 * K1_16 - U_9_21 * K1_21) / U_9_9) : 0.0;
          // Block 4: K1 backward sub [NO3an1]
          double K1_8 = active[8] ? ((y1_8 - U_8_10 * K1_10 - U_8_11 * K1_11 - U_8_13 * K1_13 - U_8_15 * K1_15 - U_8_17 * K1_17 - U_8_19 * K1_19 - U_8_21 * K1_21) / U_8_8) : 0.0;
          // Block 3: K1 backward sub [NO3]
          double K1_7 = active[7] ? ((y1_7 - U_7_20 * K1_20) / U_7_7) : 0.0;
          // Block 2: K1 backward sub [H2O2]
          double K1_6 = active[6] ? ((y1_6 - U_6_20 * K1_20) / U_6_6) : 0.0;
          double K1_5 = active[5] ? ((y1_5 - U_5_6 * K1_6 - U_5_7 * K1_7 - U_5_20 * K1_20) / U_5_5) : 0.0;
          // Block 0: K1 backward sub [OC1, OC2, BC1, BC2, OH]
          double K1_4 = active[4] ? ((y1_4 - U_4_5 * K1_5 - U_4_6 * K1_6 - U_4_20 * K1_20) / U_4_4) : 0.0;
          double K1_3 = active[3] ? (y1_3 / U_3_3) : 0.0;
          double K1_2 = active[2] ? (y1_2 / U_2_2) : 0.0;
          double K1_1 = active[1] ? (y1_1 / U_1_1) : 0.0;
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
          double Y2_7 = S_7 + K1_7;
          double Y2_8 = S_8 + K1_8;
          double Y2_9 = S_9 + K1_9;
          double Y2_10 = S_10 + K1_10;
          double Y2_11 = S_11 + K1_11;
          double Y2_12 = S_12 + K1_12;
          double Y2_13 = S_13 + K1_13;
          double Y2_14 = S_14 + K1_14;
          double Y2_15 = S_15 + K1_15;
          double Y2_16 = S_16 + K1_16;
          double Y2_17 = S_17 + K1_17;
          double Y2_18 = S_18 + K1_18;
          double Y2_19 = S_19 + K1_19;
          double Y2_20 = S_20 + K1_20;
          double Y2_21 = S_21 + K1_21;
          double Y2_22 = S_22 + K1_22;
          double Y2_23 = S_23 + K1_23;
          double Y2_24 = S_24 + K1_24;
          double Y2_25 = S_25 + K1_25;
          // Rate evaluation F2 at Y2
          double F2_0 = -5.0442046141041832e-12*Y2_3*Y2_0 + 2.0*Y2_2*jvals[0] - 3.3000000000000001e-12*Y2_0*Y2_4;
          double F2_1 = -3.3571944693753379e-14*Y2_3*Y2_1;
          double F2_2 = -0.0025000000000000001*Y2_2*Y2_4 - 1.0*Y2_2*jvals[0];
          double F2_3 = -3.3571944693753379e-14*Y2_3*Y2_1 - 5.0442046141041832e-12*Y2_3*Y2_0;
          double F2_4 = 3.3571944693753379e-14*Y2_3*Y2_1 + 5.0442046141041832e-12*Y2_3*Y2_0 - 2.5000000000000001e-5*Y2_10*Y2_4 - 2.5000000000000001e-5*Y2_11*Y2_4 - 2.5000000000000001e-5*Y2_12*Y2_4 - 2.5000000000000001e-5*Y2_13*Y2_4 - 2.5000000000000001e-5*Y2_14*Y2_4 - 0.0025000000000000001*Y2_2*Y2_4 - 3.3000000000000001e-12*Y2_0*Y2_4 - 0.00025000000000000001*Y2_4*Y2_15 - 0.00025000000000000001*Y2_4*Y2_16 - 0.00025000000000000001*Y2_4*Y2_17 - 0.00025000000000000001*Y2_4*Y2_18 - 0.00025000000000000001*Y2_4*Y2_19;
          double F2_5 = 2.5000000000000001e-5*Y2_10*Y2_4 + 2.5000000000000001e-5*Y2_11*Y2_4 + 2.5000000000000001e-5*Y2_12*Y2_4 + 2.5000000000000001e-5*Y2_13*Y2_4 + 2.5000000000000001e-5*Y2_14*Y2_4 + 0.0025000000000000001*Y2_2*Y2_4 - 1.0*Y2_20*Y2_21*Y2_5*jvals[27] + 3.3000000000000001e-12*Y2_0*Y2_4 + 0.00025000000000000001*Y2_4*Y2_15 + 0.00025000000000000001*Y2_4*Y2_16 + 0.00025000000000000001*Y2_4*Y2_17 + 0.00025000000000000001*Y2_4*Y2_18 + 0.00025000000000000001*Y2_4*Y2_19;
          double F2_6 = -5.0000000000000004e-6*Y2_6;
          double F2_7 = 5.0000000000000004e-6*Y2_6;
          double F2_8 = -5.0000000000000004e-6*Y2_8;
          double F2_9 = 5.0000000000000004e-6*Y2_8;
          double F2_10 = 0.0;
          double F2_11 = 0.0;
          double F2_12 = 0.0;
          double F2_13 = 0.0;
          double F2_14 = 0.0;
          double F2_15 = 0.0;
          double F2_16 = 0.0;
          double F2_17 = 0.0;
          double F2_18 = 0.0;
          double F2_19 = 0.0;
          double F2_20 = -0.025000000000000001*Y2_10*Y2_20 - 0.025000000000000001*Y2_11*Y2_20 - 0.025000000000000001*Y2_12*Y2_20 - 0.025000000000000001*Y2_13*Y2_20 - 0.025000000000000001*Y2_14*Y2_20 - 1.0*Y2_20*Y2_21*Y2_5*jvals[27] - 0.025000000000000001*Y2_20*Y2_15 - 0.025000000000000001*Y2_20*Y2_16 - 0.025000000000000001*Y2_20*Y2_17 - 0.025000000000000001*Y2_20*Y2_18 - 0.025000000000000001*Y2_20*Y2_19;
          double F2_21 = -1.0*Y2_20*Y2_21*Y2_5*jvals[27];
          double F2_22 = 1.0*Y2_20*Y2_21*Y2_5*jvals[27];
          double F2_23 = 0.025000000000000001*Y2_10*Y2_20 + 0.025000000000000001*Y2_13*Y2_20 + 1.0*Y2_20*Y2_21*Y2_5*jvals[27] + 0.025000000000000001*Y2_20*Y2_16 + 0.025000000000000001*Y2_20*Y2_19;
          double F2_24 = 0.025000000000000001*Y2_11*Y2_20 + 0.025000000000000001*Y2_14*Y2_20 + 0.025000000000000001*Y2_20*Y2_17;
          double F2_25 = 0.025000000000000001*Y2_12*Y2_20 + 0.025000000000000001*Y2_20*Y2_15 + 0.025000000000000001*Y2_20*Y2_18;
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
          double rhs2_11 = F2_11 + (-1.0156171083877703 / dt) * K1_11;
          double rhs2_12 = F2_12 + (-1.0156171083877703 / dt) * K1_12;
          double rhs2_13 = F2_13 + (-1.0156171083877703 / dt) * K1_13;
          double rhs2_14 = F2_14 + (-1.0156171083877703 / dt) * K1_14;
          double rhs2_15 = F2_15 + (-1.0156171083877703 / dt) * K1_15;
          double rhs2_16 = F2_16 + (-1.0156171083877703 / dt) * K1_16;
          double rhs2_17 = F2_17 + (-1.0156171083877703 / dt) * K1_17;
          double rhs2_18 = F2_18 + (-1.0156171083877703 / dt) * K1_18;
          double rhs2_19 = F2_19 + (-1.0156171083877703 / dt) * K1_19;
          double rhs2_20 = F2_20 + (-1.0156171083877703 / dt) * K1_20;
          double rhs2_21 = F2_21 + (-1.0156171083877703 / dt) * K1_21;
          double rhs2_22 = F2_22 + (-1.0156171083877703 / dt) * K1_22;
          double rhs2_23 = F2_23 + (-1.0156171083877703 / dt) * K1_23;
          double rhs2_24 = F2_24 + (-1.0156171083877703 / dt) * K1_24;
          double rhs2_25 = F2_25 + (-1.0156171083877703 / dt) * K1_25;
          // Block 0: K2 forward sub [OC1, OC2, BC1, BC2, OH]
          double y2_0 = active[0] ? (rhs2_0) : 0.0;
          double y2_1 = active[1] ? (rhs2_1 - L_1_0 * y2_0) : 0.0;
          double y2_2 = active[2] ? (rhs2_2) : 0.0;
          double y2_3 = active[3] ? (rhs2_3 - L_3_2 * y2_2) : 0.0;
          double y2_4 = active[4] ? (rhs2_4) : 0.0;
          // Block 1: K2 forward sub [DMS, SO2, HNO3]
          double y2_5 = active[5] ? (rhs2_5 - L_5_4 * y2_4) : 0.0;
          // Block 2: K2 forward sub [H2O2]
          double y2_6 = active[6] ? (rhs2_6) : 0.0;
          // Block 3: K2 forward sub [NO3]
          double y2_7 = active[7] ? (rhs2_7 - L_7_5 * y2_5 - L_7_6 * y2_6) : 0.0;
          // Block 4: K2 forward sub [NO3an1]
          double y2_8 = active[8] ? (rhs2_8) : 0.0;
          // Block 5: K2 forward sub [NO3an2]
          double y2_9 = active[9] ? (rhs2_9) : 0.0;
          // Block 6: K2 forward sub [NH3]
          double y2_10 = active[10] ? (rhs2_10) : 0.0;
          // Block 7: K2 forward sub [SS5]
          double y2_11 = active[11] ? (rhs2_11) : 0.0;
          // Block 8: K2 forward sub [SS3]
          double y2_12 = active[12] ? (rhs2_12) : 0.0;
          // Block 9: K2 forward sub [SS2]
          double y2_13 = active[13] ? (rhs2_13) : 0.0;
          // Block 10: K2 forward sub [DUST5]
          double y2_14 = active[14] ? (rhs2_14) : 0.0;
          // Block 11: K2 forward sub [DUST4]
          double y2_15 = active[15] ? (rhs2_15) : 0.0;
          // Block 12: K2 forward sub [DUST2]
          double y2_16 = active[16] ? (rhs2_16) : 0.0;
          // Block 13: K2 forward sub [DUST1]
          double y2_17 = active[17] ? (rhs2_17) : 0.0;
          // Block 14: K2 forward sub [NH4a]
          double y2_18 = active[18] ? (rhs2_18 - L_18_10 * y2_10) : 0.0;
          // Block 15: K2 forward sub [SO4]
          double y2_19 = active[19] ? (rhs2_19 - L_19_4 * y2_4 - L_19_5 * y2_5 - L_19_6 * y2_6 - L_19_7 * y2_7 - L_19_10 * y2_10 - L_19_11 * y2_11 - L_19_12 * y2_12 - L_19_13 * y2_13 - L_19_14 * y2_14 - L_19_15 * y2_15 - L_19_16 * y2_16 - L_19_17 * y2_17) : 0.0;
          double y2_20 = active[20] ? (rhs2_20 - L_20_4 * y2_4 - L_20_5 * y2_5 - L_20_6 * y2_6 - L_20_7 * y2_7 - L_20_11 * y2_11 - L_20_12 * y2_12 - L_20_13 * y2_13 - L_20_14 * y2_14 - L_20_15 * y2_15 - L_20_16 * y2_16 - L_20_17 * y2_17) : 0.0;
          double y2_21 = active[21] ? (rhs2_21 - L_21_10 * y2_10 - L_21_11 * y2_11 - L_21_12 * y2_12 - L_21_13 * y2_13 - L_21_14 * y2_14 - L_21_15 * y2_15 - L_21_16 * y2_16 - L_21_17 * y2_17 - L_21_19 * y2_19 - L_21_20 * y2_20) : 0.0;
          // Block 16: K2 forward sub [SS1]
          double y2_22 = active[22] ? (rhs2_22) : 0.0;
          // Block 17: K2 forward sub [DUST3]
          double y2_23 = active[23] ? (rhs2_23) : 0.0;
          // Block 18: K2 forward sub [SS4]
          double y2_24 = active[24] ? (rhs2_24) : 0.0;
          // Block 19: K2 forward sub [NO3an3]
          double y2_25 = active[25] ? (rhs2_25 - L_25_21 * y2_21 - L_25_22 * y2_22 - L_25_23 * y2_23 - L_25_24 * y2_24) : 0.0;
          // Block 19: K2 backward sub [NO3an3]
          double K2_25 = active[25] ? (y2_25 / U_25_25) : 0.0;
          // Block 18: K2 backward sub [SS4]
          double K2_24 = active[24] ? (y2_24 / U_24_24) : 0.0;
          // Block 17: K2 backward sub [DUST3]
          double K2_23 = active[23] ? (y2_23 / U_23_23) : 0.0;
          // Block 16: K2 backward sub [SS1]
          double K2_22 = active[22] ? (y2_22 / U_22_22) : 0.0;
          // Block 1: K2 backward sub [DMS, SO2, HNO3]
          double K2_21 = active[21] ? ((y2_21 - U_21_22 * K2_22 - U_21_23 * K2_23 - U_21_24 * K2_24) / U_21_21) : 0.0;
          double K2_20 = active[20] ? ((y2_20 - U_20_22 * K2_22 - U_20_23 * K2_23 - U_20_24 * K2_24) / U_20_20) : 0.0;
          // Block 15: K2 backward sub [SO4]
          double K2_19 = active[19] ? ((y2_19 - U_19_20 * K2_20 - U_19_21 * K2_21 - U_19_22 * K2_22 - U_19_23 * K2_23 - U_19_24 * K2_24) / U_19_19) : 0.0;
          // Block 14: K2 backward sub [NH4a]
          double K2_18 = active[18] ? ((y2_18 - U_18_19 * K2_19 - U_18_21 * K2_21) / U_18_18) : 0.0;
          // Block 13: K2 backward sub [DUST1]
          double K2_17 = active[17] ? (y2_17 / U_17_17) : 0.0;
          // Block 12: K2 backward sub [DUST2]
          double K2_16 = active[16] ? (y2_16 / U_16_16) : 0.0;
          // Block 11: K2 backward sub [DUST4]
          double K2_15 = active[15] ? (y2_15 / U_15_15) : 0.0;
          // Block 10: K2 backward sub [DUST5]
          double K2_14 = active[14] ? (y2_14 / U_14_14) : 0.0;
          // Block 9: K2 backward sub [SS2]
          double K2_13 = active[13] ? (y2_13 / U_13_13) : 0.0;
          // Block 8: K2 backward sub [SS3]
          double K2_12 = active[12] ? (y2_12 / U_12_12) : 0.0;
          // Block 7: K2 backward sub [SS5]
          double K2_11 = active[11] ? (y2_11 / U_11_11) : 0.0;
          // Block 6: K2 backward sub [NH3]
          double K2_10 = active[10] ? ((y2_10 - U_10_19 * K2_19 - U_10_21 * K2_21) / U_10_10) : 0.0;
          // Block 5: K2 backward sub [NO3an2]
          double K2_9 = active[9] ? ((y2_9 - U_9_12 * K2_12 - U_9_14 * K2_14 - U_9_16 * K2_16 - U_9_21 * K2_21) / U_9_9) : 0.0;
          // Block 4: K2 backward sub [NO3an1]
          double K2_8 = active[8] ? ((y2_8 - U_8_10 * K2_10 - U_8_11 * K2_11 - U_8_13 * K2_13 - U_8_15 * K2_15 - U_8_17 * K2_17 - U_8_19 * K2_19 - U_8_21 * K2_21) / U_8_8) : 0.0;
          // Block 3: K2 backward sub [NO3]
          double K2_7 = active[7] ? ((y2_7 - U_7_20 * K2_20) / U_7_7) : 0.0;
          // Block 2: K2 backward sub [H2O2]
          double K2_6 = active[6] ? ((y2_6 - U_6_20 * K2_20) / U_6_6) : 0.0;
          double K2_5 = active[5] ? ((y2_5 - U_5_6 * K2_6 - U_5_7 * K2_7 - U_5_20 * K2_20) / U_5_5) : 0.0;
          // Block 0: K2 backward sub [OC1, OC2, BC1, BC2, OH]
          double K2_4 = active[4] ? ((y2_4 - U_4_5 * K2_5 - U_4_6 * K2_6 - U_4_20 * K2_20) / U_4_4) : 0.0;
          double K2_3 = active[3] ? (y2_3 / U_3_3) : 0.0;
          double K2_2 = active[2] ? (y2_2 / U_2_2) : 0.0;
          double K2_1 = active[1] ? (y2_1 / U_1_1) : 0.0;
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
          double Y3_7 = S_7 + K1_7;
          double Y3_8 = S_8 + K1_8;
          double Y3_9 = S_9 + K1_9;
          double Y3_10 = S_10 + K1_10;
          double Y3_11 = S_11 + K1_11;
          double Y3_12 = S_12 + K1_12;
          double Y3_13 = S_13 + K1_13;
          double Y3_14 = S_14 + K1_14;
          double Y3_15 = S_15 + K1_15;
          double Y3_16 = S_16 + K1_16;
          double Y3_17 = S_17 + K1_17;
          double Y3_18 = S_18 + K1_18;
          double Y3_19 = S_19 + K1_19;
          double Y3_20 = S_20 + K1_20;
          double Y3_21 = S_21 + K1_21;
          double Y3_22 = S_22 + K1_22;
          double Y3_23 = S_23 + K1_23;
          double Y3_24 = S_24 + K1_24;
          double Y3_25 = S_25 + K1_25;
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
          double rhs3_11 = F2_11 + (4.0759956452537702 / dt) * K1_11 + (9.20767942983308 / dt) * K2_11;
          double rhs3_12 = F2_12 + (4.0759956452537702 / dt) * K1_12 + (9.20767942983308 / dt) * K2_12;
          double rhs3_13 = F2_13 + (4.0759956452537702 / dt) * K1_13 + (9.20767942983308 / dt) * K2_13;
          double rhs3_14 = F2_14 + (4.0759956452537702 / dt) * K1_14 + (9.20767942983308 / dt) * K2_14;
          double rhs3_15 = F2_15 + (4.0759956452537702 / dt) * K1_15 + (9.20767942983308 / dt) * K2_15;
          double rhs3_16 = F2_16 + (4.0759956452537702 / dt) * K1_16 + (9.20767942983308 / dt) * K2_16;
          double rhs3_17 = F2_17 + (4.0759956452537702 / dt) * K1_17 + (9.20767942983308 / dt) * K2_17;
          double rhs3_18 = F2_18 + (4.0759956452537702 / dt) * K1_18 + (9.20767942983308 / dt) * K2_18;
          double rhs3_19 = F2_19 + (4.0759956452537702 / dt) * K1_19 + (9.20767942983308 / dt) * K2_19;
          double rhs3_20 = F2_20 + (4.0759956452537702 / dt) * K1_20 + (9.20767942983308 / dt) * K2_20;
          double rhs3_21 = F2_21 + (4.0759956452537702 / dt) * K1_21 + (9.20767942983308 / dt) * K2_21;
          double rhs3_22 = F2_22 + (4.0759956452537702 / dt) * K1_22 + (9.20767942983308 / dt) * K2_22;
          double rhs3_23 = F2_23 + (4.0759956452537702 / dt) * K1_23 + (9.20767942983308 / dt) * K2_23;
          double rhs3_24 = F2_24 + (4.0759956452537702 / dt) * K1_24 + (9.20767942983308 / dt) * K2_24;
          double rhs3_25 = F2_25 + (4.0759956452537702 / dt) * K1_25 + (9.20767942983308 / dt) * K2_25;
          // Block 0: K3 forward sub [OC1, OC2, BC1, BC2, OH]
          double y3_0 = active[0] ? (rhs3_0) : 0.0;
          double y3_1 = active[1] ? (rhs3_1 - L_1_0 * y3_0) : 0.0;
          double y3_2 = active[2] ? (rhs3_2) : 0.0;
          double y3_3 = active[3] ? (rhs3_3 - L_3_2 * y3_2) : 0.0;
          double y3_4 = active[4] ? (rhs3_4) : 0.0;
          // Block 1: K3 forward sub [DMS, SO2, HNO3]
          double y3_5 = active[5] ? (rhs3_5 - L_5_4 * y3_4) : 0.0;
          // Block 2: K3 forward sub [H2O2]
          double y3_6 = active[6] ? (rhs3_6) : 0.0;
          // Block 3: K3 forward sub [NO3]
          double y3_7 = active[7] ? (rhs3_7 - L_7_5 * y3_5 - L_7_6 * y3_6) : 0.0;
          // Block 4: K3 forward sub [NO3an1]
          double y3_8 = active[8] ? (rhs3_8) : 0.0;
          // Block 5: K3 forward sub [NO3an2]
          double y3_9 = active[9] ? (rhs3_9) : 0.0;
          // Block 6: K3 forward sub [NH3]
          double y3_10 = active[10] ? (rhs3_10) : 0.0;
          // Block 7: K3 forward sub [SS5]
          double y3_11 = active[11] ? (rhs3_11) : 0.0;
          // Block 8: K3 forward sub [SS3]
          double y3_12 = active[12] ? (rhs3_12) : 0.0;
          // Block 9: K3 forward sub [SS2]
          double y3_13 = active[13] ? (rhs3_13) : 0.0;
          // Block 10: K3 forward sub [DUST5]
          double y3_14 = active[14] ? (rhs3_14) : 0.0;
          // Block 11: K3 forward sub [DUST4]
          double y3_15 = active[15] ? (rhs3_15) : 0.0;
          // Block 12: K3 forward sub [DUST2]
          double y3_16 = active[16] ? (rhs3_16) : 0.0;
          // Block 13: K3 forward sub [DUST1]
          double y3_17 = active[17] ? (rhs3_17) : 0.0;
          // Block 14: K3 forward sub [NH4a]
          double y3_18 = active[18] ? (rhs3_18 - L_18_10 * y3_10) : 0.0;
          // Block 15: K3 forward sub [SO4]
          double y3_19 = active[19] ? (rhs3_19 - L_19_4 * y3_4 - L_19_5 * y3_5 - L_19_6 * y3_6 - L_19_7 * y3_7 - L_19_10 * y3_10 - L_19_11 * y3_11 - L_19_12 * y3_12 - L_19_13 * y3_13 - L_19_14 * y3_14 - L_19_15 * y3_15 - L_19_16 * y3_16 - L_19_17 * y3_17) : 0.0;
          double y3_20 = active[20] ? (rhs3_20 - L_20_4 * y3_4 - L_20_5 * y3_5 - L_20_6 * y3_6 - L_20_7 * y3_7 - L_20_11 * y3_11 - L_20_12 * y3_12 - L_20_13 * y3_13 - L_20_14 * y3_14 - L_20_15 * y3_15 - L_20_16 * y3_16 - L_20_17 * y3_17) : 0.0;
          double y3_21 = active[21] ? (rhs3_21 - L_21_10 * y3_10 - L_21_11 * y3_11 - L_21_12 * y3_12 - L_21_13 * y3_13 - L_21_14 * y3_14 - L_21_15 * y3_15 - L_21_16 * y3_16 - L_21_17 * y3_17 - L_21_19 * y3_19 - L_21_20 * y3_20) : 0.0;
          // Block 16: K3 forward sub [SS1]
          double y3_22 = active[22] ? (rhs3_22) : 0.0;
          // Block 17: K3 forward sub [DUST3]
          double y3_23 = active[23] ? (rhs3_23) : 0.0;
          // Block 18: K3 forward sub [SS4]
          double y3_24 = active[24] ? (rhs3_24) : 0.0;
          // Block 19: K3 forward sub [NO3an3]
          double y3_25 = active[25] ? (rhs3_25 - L_25_21 * y3_21 - L_25_22 * y3_22 - L_25_23 * y3_23 - L_25_24 * y3_24) : 0.0;
          // Block 19: K3 backward sub [NO3an3]
          double K3_25 = active[25] ? (y3_25 / U_25_25) : 0.0;
          // Block 18: K3 backward sub [SS4]
          double K3_24 = active[24] ? (y3_24 / U_24_24) : 0.0;
          // Block 17: K3 backward sub [DUST3]
          double K3_23 = active[23] ? (y3_23 / U_23_23) : 0.0;
          // Block 16: K3 backward sub [SS1]
          double K3_22 = active[22] ? (y3_22 / U_22_22) : 0.0;
          // Block 1: K3 backward sub [DMS, SO2, HNO3]
          double K3_21 = active[21] ? ((y3_21 - U_21_22 * K3_22 - U_21_23 * K3_23 - U_21_24 * K3_24) / U_21_21) : 0.0;
          double K3_20 = active[20] ? ((y3_20 - U_20_22 * K3_22 - U_20_23 * K3_23 - U_20_24 * K3_24) / U_20_20) : 0.0;
          // Block 15: K3 backward sub [SO4]
          double K3_19 = active[19] ? ((y3_19 - U_19_20 * K3_20 - U_19_21 * K3_21 - U_19_22 * K3_22 - U_19_23 * K3_23 - U_19_24 * K3_24) / U_19_19) : 0.0;
          // Block 14: K3 backward sub [NH4a]
          double K3_18 = active[18] ? ((y3_18 - U_18_19 * K3_19 - U_18_21 * K3_21) / U_18_18) : 0.0;
          // Block 13: K3 backward sub [DUST1]
          double K3_17 = active[17] ? (y3_17 / U_17_17) : 0.0;
          // Block 12: K3 backward sub [DUST2]
          double K3_16 = active[16] ? (y3_16 / U_16_16) : 0.0;
          // Block 11: K3 backward sub [DUST4]
          double K3_15 = active[15] ? (y3_15 / U_15_15) : 0.0;
          // Block 10: K3 backward sub [DUST5]
          double K3_14 = active[14] ? (y3_14 / U_14_14) : 0.0;
          // Block 9: K3 backward sub [SS2]
          double K3_13 = active[13] ? (y3_13 / U_13_13) : 0.0;
          // Block 8: K3 backward sub [SS3]
          double K3_12 = active[12] ? (y3_12 / U_12_12) : 0.0;
          // Block 7: K3 backward sub [SS5]
          double K3_11 = active[11] ? (y3_11 / U_11_11) : 0.0;
          // Block 6: K3 backward sub [NH3]
          double K3_10 = active[10] ? ((y3_10 - U_10_19 * K3_19 - U_10_21 * K3_21) / U_10_10) : 0.0;
          // Block 5: K3 backward sub [NO3an2]
          double K3_9 = active[9] ? ((y3_9 - U_9_12 * K3_12 - U_9_14 * K3_14 - U_9_16 * K3_16 - U_9_21 * K3_21) / U_9_9) : 0.0;
          // Block 4: K3 backward sub [NO3an1]
          double K3_8 = active[8] ? ((y3_8 - U_8_10 * K3_10 - U_8_11 * K3_11 - U_8_13 * K3_13 - U_8_15 * K3_15 - U_8_17 * K3_17 - U_8_19 * K3_19 - U_8_21 * K3_21) / U_8_8) : 0.0;
          // Block 3: K3 backward sub [NO3]
          double K3_7 = active[7] ? ((y3_7 - U_7_20 * K3_20) / U_7_7) : 0.0;
          // Block 2: K3 backward sub [H2O2]
          double K3_6 = active[6] ? ((y3_6 - U_6_20 * K3_20) / U_6_6) : 0.0;
          double K3_5 = active[5] ? ((y3_5 - U_5_6 * K3_6 - U_5_7 * K3_7 - U_5_20 * K3_20) / U_5_5) : 0.0;
          // Block 0: K3 backward sub [OC1, OC2, BC1, BC2, OH]
          double K3_4 = active[4] ? ((y3_4 - U_4_5 * K3_5 - U_4_6 * K3_6 - U_4_20 * K3_20) / U_4_4) : 0.0;
          double K3_3 = active[3] ? (y3_3 / U_3_3) : 0.0;
          double K3_2 = active[2] ? (y3_2 / U_2_2) : 0.0;
          double K3_1 = active[1] ? (y3_1 / U_1_1) : 0.0;
          double K3_0 = active[0] ? (y3_0 / U_0_0) : 0.0;

          // --- Solution update and error estimation ---
          double err_norm_sq = 0.0;
          {
              double Ynew_i = S_0 + K1_0 + 6.1697947043828245 * K2_0 + -0.42772256543218573 * K3_0;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(8)), Kokkos::fabs(Ynew_i));
              double sci = atol[0] + rtol[0] * ymax;
              double yerr_i = 0.5 * K1_0 + -2.9079558716805471 * K2_0 + 0.22354069897811571 * K3_0;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_1 + K1_1 + 6.1697947043828245 * K2_1 + -0.42772256543218573 * K3_1;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(9)), Kokkos::fabs(Ynew_i));
              double sci = atol[1] + rtol[1] * ymax;
              double yerr_i = 0.5 * K1_1 + -2.9079558716805471 * K2_1 + 0.22354069897811571 * K3_1;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_2 + K1_2 + 6.1697947043828245 * K2_2 + -0.42772256543218573 * K3_2;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(6)), Kokkos::fabs(Ynew_i));
              double sci = atol[2] + rtol[2] * ymax;
              double yerr_i = 0.5 * K1_2 + -2.9079558716805471 * K2_2 + 0.22354069897811571 * K3_2;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_3 + K1_3 + 6.1697947043828245 * K2_3 + -0.42772256543218573 * K3_3;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(7)), Kokkos::fabs(Ynew_i));
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
              double ymax = Kokkos::fmax(Kokkos::fabs(state(3)), Kokkos::fabs(Ynew_i));
              double sci = atol[5] + rtol[5] * ymax;
              double yerr_i = 0.5 * K1_5 + -2.9079558716805471 * K2_5 + 0.22354069897811571 * K3_5;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_6 + K1_6 + 6.1697947043828245 * K2_6 + -0.42772256543218573 * K3_6;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(2)), Kokkos::fabs(Ynew_i));
              double sci = atol[6] + rtol[6] * ymax;
              double yerr_i = 0.5 * K1_6 + -2.9079558716805471 * K2_6 + 0.22354069897811571 * K3_6;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_7 + K1_7 + 6.1697947043828245 * K2_7 + -0.42772256543218573 * K3_7;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(1)), Kokkos::fabs(Ynew_i));
              double sci = atol[7] + rtol[7] * ymax;
              double yerr_i = 0.5 * K1_7 + -2.9079558716805471 * K2_7 + 0.22354069897811571 * K3_7;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_8 + K1_8 + 6.1697947043828245 * K2_8 + -0.42772256543218573 * K3_8;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(23)), Kokkos::fabs(Ynew_i));
              double sci = atol[8] + rtol[8] * ymax;
              double yerr_i = 0.5 * K1_8 + -2.9079558716805471 * K2_8 + 0.22354069897811571 * K3_8;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_9 + K1_9 + 6.1697947043828245 * K2_9 + -0.42772256543218573 * K3_9;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(24)), Kokkos::fabs(Ynew_i));
              double sci = atol[9] + rtol[9] * ymax;
              double yerr_i = 0.5 * K1_9 + -2.9079558716805471 * K2_9 + 0.22354069897811571 * K3_9;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_10 + K1_10 + 6.1697947043828245 * K2_10 + -0.42772256543218573 * K3_10;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(21)), Kokkos::fabs(Ynew_i));
              double sci = atol[10] + rtol[10] * ymax;
              double yerr_i = 0.5 * K1_10 + -2.9079558716805471 * K2_10 + 0.22354069897811571 * K3_10;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_11 + K1_11 + 6.1697947043828245 * K2_11 + -0.42772256543218573 * K3_11;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(19)), Kokkos::fabs(Ynew_i));
              double sci = atol[11] + rtol[11] * ymax;
              double yerr_i = 0.5 * K1_11 + -2.9079558716805471 * K2_11 + 0.22354069897811571 * K3_11;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_12 + K1_12 + 6.1697947043828245 * K2_12 + -0.42772256543218573 * K3_12;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(17)), Kokkos::fabs(Ynew_i));
              double sci = atol[12] + rtol[12] * ymax;
              double yerr_i = 0.5 * K1_12 + -2.9079558716805471 * K2_12 + 0.22354069897811571 * K3_12;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_13 + K1_13 + 6.1697947043828245 * K2_13 + -0.42772256543218573 * K3_13;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(16)), Kokkos::fabs(Ynew_i));
              double sci = atol[13] + rtol[13] * ymax;
              double yerr_i = 0.5 * K1_13 + -2.9079558716805471 * K2_13 + 0.22354069897811571 * K3_13;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_14 + K1_14 + 6.1697947043828245 * K2_14 + -0.42772256543218573 * K3_14;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(14)), Kokkos::fabs(Ynew_i));
              double sci = atol[14] + rtol[14] * ymax;
              double yerr_i = 0.5 * K1_14 + -2.9079558716805471 * K2_14 + 0.22354069897811571 * K3_14;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_15 + K1_15 + 6.1697947043828245 * K2_15 + -0.42772256543218573 * K3_15;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(13)), Kokkos::fabs(Ynew_i));
              double sci = atol[15] + rtol[15] * ymax;
              double yerr_i = 0.5 * K1_15 + -2.9079558716805471 * K2_15 + 0.22354069897811571 * K3_15;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_16 + K1_16 + 6.1697947043828245 * K2_16 + -0.42772256543218573 * K3_16;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(11)), Kokkos::fabs(Ynew_i));
              double sci = atol[16] + rtol[16] * ymax;
              double yerr_i = 0.5 * K1_16 + -2.9079558716805471 * K2_16 + 0.22354069897811571 * K3_16;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_17 + K1_17 + 6.1697947043828245 * K2_17 + -0.42772256543218573 * K3_17;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(10)), Kokkos::fabs(Ynew_i));
              double sci = atol[17] + rtol[17] * ymax;
              double yerr_i = 0.5 * K1_17 + -2.9079558716805471 * K2_17 + 0.22354069897811571 * K3_17;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_18 + K1_18 + 6.1697947043828245 * K2_18 + -0.42772256543218573 * K3_18;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(22)), Kokkos::fabs(Ynew_i));
              double sci = atol[18] + rtol[18] * ymax;
              double yerr_i = 0.5 * K1_18 + -2.9079558716805471 * K2_18 + 0.22354069897811571 * K3_18;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_19 + K1_19 + 6.1697947043828245 * K2_19 + -0.42772256543218573 * K3_19;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(5)), Kokkos::fabs(Ynew_i));
              double sci = atol[19] + rtol[19] * ymax;
              double yerr_i = 0.5 * K1_19 + -2.9079558716805471 * K2_19 + 0.22354069897811571 * K3_19;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_20 + K1_20 + 6.1697947043828245 * K2_20 + -0.42772256543218573 * K3_20;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(4)), Kokkos::fabs(Ynew_i));
              double sci = atol[20] + rtol[20] * ymax;
              double yerr_i = 0.5 * K1_20 + -2.9079558716805471 * K2_20 + 0.22354069897811571 * K3_20;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_21 + K1_21 + 6.1697947043828245 * K2_21 + -0.42772256543218573 * K3_21;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(20)), Kokkos::fabs(Ynew_i));
              double sci = atol[21] + rtol[21] * ymax;
              double yerr_i = 0.5 * K1_21 + -2.9079558716805471 * K2_21 + 0.22354069897811571 * K3_21;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_22 + K1_22 + 6.1697947043828245 * K2_22 + -0.42772256543218573 * K3_22;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(15)), Kokkos::fabs(Ynew_i));
              double sci = atol[22] + rtol[22] * ymax;
              double yerr_i = 0.5 * K1_22 + -2.9079558716805471 * K2_22 + 0.22354069897811571 * K3_22;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_23 + K1_23 + 6.1697947043828245 * K2_23 + -0.42772256543218573 * K3_23;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(12)), Kokkos::fabs(Ynew_i));
              double sci = atol[23] + rtol[23] * ymax;
              double yerr_i = 0.5 * K1_23 + -2.9079558716805471 * K2_23 + 0.22354069897811571 * K3_23;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_24 + K1_24 + 6.1697947043828245 * K2_24 + -0.42772256543218573 * K3_24;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(18)), Kokkos::fabs(Ynew_i));
              double sci = atol[24] + rtol[24] * ymax;
              double yerr_i = 0.5 * K1_24 + -2.9079558716805471 * K2_24 + 0.22354069897811571 * K3_24;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_25 + K1_25 + 6.1697947043828245 * K2_25 + -0.42772256543218573 * K3_25;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(25)), Kokkos::fabs(Ynew_i));
              double sci = atol[25] + rtol[25] * ymax;
              double yerr_i = 0.5 * K1_25 + -2.9079558716805471 * K2_25 + 0.22354069897811571 * K3_25;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          double err_norm = Kokkos::sqrt(err_norm_sq / 26);
          err_norm = Kokkos::fmax(err_norm, 1.0e-10);

          // Step Size Control (order 3: exponent = 1/3 = 0.33333333333333331)
          double factor = safety / Kokkos::cbrt(err_norm);
          factor = Kokkos::fmax(min_shrink, Kokkos::fmin(factor, max_growth));

          if (err_norm <= 1.0) {
              if (active[0]) state(8) += K1_0 + 6.1697947043828245 * K2_0 + -0.42772256543218573 * K3_0;
              if (active[1]) state(9) += K1_1 + 6.1697947043828245 * K2_1 + -0.42772256543218573 * K3_1;
              if (active[2]) state(6) += K1_2 + 6.1697947043828245 * K2_2 + -0.42772256543218573 * K3_2;
              if (active[3]) state(7) += K1_3 + 6.1697947043828245 * K2_3 + -0.42772256543218573 * K3_3;
              if (active[4]) state(0) += K1_4 + 6.1697947043828245 * K2_4 + -0.42772256543218573 * K3_4;
              if (active[5]) state(3) += K1_5 + 6.1697947043828245 * K2_5 + -0.42772256543218573 * K3_5;
              if (active[6]) state(2) += K1_6 + 6.1697947043828245 * K2_6 + -0.42772256543218573 * K3_6;
              if (active[7]) state(1) += K1_7 + 6.1697947043828245 * K2_7 + -0.42772256543218573 * K3_7;
              if (active[8]) state(23) += K1_8 + 6.1697947043828245 * K2_8 + -0.42772256543218573 * K3_8;
              if (active[9]) state(24) += K1_9 + 6.1697947043828245 * K2_9 + -0.42772256543218573 * K3_9;
              if (active[10]) state(21) += K1_10 + 6.1697947043828245 * K2_10 + -0.42772256543218573 * K3_10;
              if (active[11]) state(19) += K1_11 + 6.1697947043828245 * K2_11 + -0.42772256543218573 * K3_11;
              if (active[12]) state(17) += K1_12 + 6.1697947043828245 * K2_12 + -0.42772256543218573 * K3_12;
              if (active[13]) state(16) += K1_13 + 6.1697947043828245 * K2_13 + -0.42772256543218573 * K3_13;
              if (active[14]) state(14) += K1_14 + 6.1697947043828245 * K2_14 + -0.42772256543218573 * K3_14;
              if (active[15]) state(13) += K1_15 + 6.1697947043828245 * K2_15 + -0.42772256543218573 * K3_15;
              if (active[16]) state(11) += K1_16 + 6.1697947043828245 * K2_16 + -0.42772256543218573 * K3_16;
              if (active[17]) state(10) += K1_17 + 6.1697947043828245 * K2_17 + -0.42772256543218573 * K3_17;
              if (active[18]) state(22) += K1_18 + 6.1697947043828245 * K2_18 + -0.42772256543218573 * K3_18;
              if (active[19]) state(5) += K1_19 + 6.1697947043828245 * K2_19 + -0.42772256543218573 * K3_19;
              if (active[20]) state(4) += K1_20 + 6.1697947043828245 * K2_20 + -0.42772256543218573 * K3_20;
              if (active[21]) state(20) += K1_21 + 6.1697947043828245 * K2_21 + -0.42772256543218573 * K3_21;
              if (active[22]) state(15) += K1_22 + 6.1697947043828245 * K2_22 + -0.42772256543218573 * K3_22;
              if (active[23]) state(12) += K1_23 + 6.1697947043828245 * K2_23 + -0.42772256543218573 * K3_23;
              if (active[24]) state(18) += K1_24 + 6.1697947043828245 * K2_24 + -0.42772256543218573 * K3_24;
              if (active[25]) state(25) += K1_25 + 6.1697947043828245 * K2_25 + -0.42772256543218573 * K3_25;
              t += dt;
              dt *= factor;
          } else {
              dt *= factor;
          }
          } // end while (t < dt_total)
      }
  };
}
