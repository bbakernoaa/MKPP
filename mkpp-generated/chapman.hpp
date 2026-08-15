#pragma once
#include <Kokkos_Core.hpp>
// Generated solver for chapman
// SZA Workload Sorted: true
// Hysteresis/Spline Continuous Transition: true
namespace mkpp {
  // Pure Kokkos abstractions (no raw pragmas allowed)

  /**
   * @brief Strongly typed enum for species indexing into state vectors.
   */
  enum Species : int {
      O = 0,
      O2 = 1,
      O3 = 2,
      M = 3
  };

  // Bidirectional Host Interface (Zero-Copy)
  using concentrations_view_t = Kokkos::View<double****, Kokkos::LayoutLeft, Kokkos::MemoryUnmanaged>;
  template<typename DeviceType>
  struct SolverKernels {
      /**
       * @brief Evaluates the rate-of-change vector F(i) = dC_i / dt.
       *
       * @tparam StateView Kokkos View type for species concentrations [NUM_SPECIES].
       * @tparam RateView Kokkos View type for output rate-of-change vector [NUM_SPECIES].
       * @param state Input concentration vector [NUM_SPECIES].
       * @param F_block Output rate-of-change vector [NUM_SPECIES].
       * @param jvals Array of photolysis rate constants [NUM_PHOTOLYSIS].
       */
      template <class StateView, class RateView>
      KOKKOS_INLINE_FUNCTION void compute_rates(const StateView& state, RateView& F_block, const double* jvals) const {
          // --- Rate-of-Change Vector F_block ---
          // F_block(O): d[O]/dt
          F_block(Species::O) = -6.0e-34*state(3)*state(0)*state(1) - 7.9999999999999998e-12*state(0)*state(2) + 2.0*state(1)*jvals[0] + 1.0*state(2)*jvals[1];
          // F_block(O2): d[O2]/dt
          F_block(Species::O2) = 0.0;
          // F_block(O3): d[O3]/dt
          F_block(Species::O3) = 6.0e-34*state(3)*state(0)*state(1) - 7.9999999999999998e-12*state(0)*state(2) - 1.0*state(2)*jvals[1];
          // F_block(M): d[M]/dt
          F_block(Species::M) = 0.0;
      }

      /**
       * @brief Evaluates the sparse analytical Jacobian matrix J(i, j) = dF_i / dC_j.
       *
       * @tparam StateView Kokkos View type for species concentrations [NUM_SPECIES].
       * @tparam JacView Kokkos View type for output 2D Jacobian matrix [NUM_SPECIES x NUM_SPECIES].
       * @param state Input concentration vector [NUM_SPECIES].
       * @param J_block Output 2D Jacobian matrix [NUM_SPECIES x NUM_SPECIES].
       * @param jvals Array of photolysis rate constants [NUM_PHOTOLYSIS].
       */
      template <class StateView, class JacView>
      KOKKOS_INLINE_FUNCTION void compute_jacobian(const StateView& state, JacView& J_block, const double* jvals) const {
          // --- Sparse Analytical Jacobian Entries J_block(i, j) ---
          // J(O, O): d(d[O]/dt) / d[O]
          J_block(Species::O, Species::O) = -6.0e-34*state(3)*state(1) - 7.9999999999999998e-12*state(2);
          // J(O, O2): d(d[O]/dt) / d[O2]
          J_block(Species::O, Species::O2) = -6.0e-34*state(3)*state(0) + 2.0*jvals[0];
          // J(O, O3): d(d[O]/dt) / d[O3]
          J_block(Species::O, Species::O3) = -7.9999999999999998e-12*state(0) + 1.0*jvals[1];
          // J(O, M): d(d[O]/dt) / d[M]
          J_block(Species::O, Species::M) = -6.0e-34*state(0)*state(1);
          // J(O3, O): d(d[O3]/dt) / d[O]
          J_block(Species::O3, Species::O) = 6.0e-34*state(3)*state(1) - 7.9999999999999998e-12*state(2);
          // J(O3, O2): d(d[O3]/dt) / d[O2]
          J_block(Species::O3, Species::O2) = 6.0e-34*state(3)*state(0);
          // J(O3, O3): d(d[O3]/dt) / d[O3]
          J_block(Species::O3, Species::O3) = -7.9999999999999998e-12*state(0) - 1.0*jvals[1];
          // J(O3, M): d(d[O3]/dt) / d[M]
          J_block(Species::O3, Species::M) = 6.0e-34*state(0)*state(1);
      }

      template <class StateView, class JacView>
      KOKKOS_INLINE_FUNCTION void compute_adjoint(const StateView& state, JacView& J_adj_block, const double* jvals) const {
      }

      template <class StateView, class DeltaView, class RateView>
      KOKKOS_INLINE_FUNCTION void compute_tlm(const StateView& state, const DeltaView& delta_C, RateView& dF_block, const double* jvals) const {
          dF_block(0) = 0.0;
          dF_block(0) += (-6.0e-34*state(3)*state(1) - 7.9999999999999998e-12*state(2)) * delta_C(0);
          dF_block(0) += (-6.0e-34*state(3)*state(0) + 2.0*jvals[0]) * delta_C(1);
          dF_block(0) += (-7.9999999999999998e-12*state(0) + 1.0*jvals[1]) * delta_C(2);
          dF_block(0) += (-6.0e-34*state(0)*state(1)) * delta_C(3);
          dF_block(1) = 0.0;
          dF_block(2) = 0.0;
          dF_block(2) += (6.0e-34*state(3)*state(1) - 7.9999999999999998e-12*state(2)) * delta_C(0);
          dF_block(2) += (6.0e-34*state(3)*state(0)) * delta_C(1);
          dF_block(2) += (-7.9999999999999998e-12*state(0) - 1.0*jvals[1]) * delta_C(2);
          dF_block(2) += (6.0e-34*state(0)*state(1)) * delta_C(3);
          dF_block(3) = 0.0;
      }

      template <class StateView, class MassView>
      KOKKOS_INLINE_FUNCTION void project_mass_conservation(StateView& C_projected, const StateView& C, const MassView& m_0) const {
          // C_projected = C - E^T (E E^T)^-1 (E C - m_0)
      }

      static constexpr int NUM_SPECIES = 4;
      static constexpr double atol[NUM_SPECIES] = { 1e-12, 1e-12, 1e-12, 1e-12 };
      static constexpr double rtol[NUM_SPECIES] = { 1e-08, 1e-08, 1e-08, 1e-08 };

      /**
       * @brief Performs adaptive time-stepping Rosenbrock integration over dt_total.
       *
       * @tparam StateView Kokkos View type for species concentrations [NUM_SPECIES].
       * @param dt_total Total physical time step duration [s].
       * @param state Input/output species concentration vector [NUM_SPECIES].
       * @param jvals Array of photolysis rate constants [NUM_PHOTOLYSIS].
       */
      template <class StateView>
      KOKKOS_INLINE_FUNCTION void integrate(double dt_total, StateView& state, const double* jvals) const {
          const int NUM_SPECIES = 4;
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

          // --- 0. Hoist State Values into Scalar Registers ---
          // NOTE: State access uses permuted species ordering for RCM bandwidth reduction
          const double S_0 = state(Species::O2);  // [O2]
          const double S_1 = state(Species::O3);  // [O3]
          const double S_2 = state(Species::O);  // [O]
          const double S_3 = state(Species::M);  // [M]

          // Analytical Jacobian & Iteration Matrix W = inv_g_dt*I - J (sparse)
          double J_1_0 = 6.0e-34*S_3*S_2;
          double J_1_1 = -7.9999999999999998e-12*S_2 - 1.0*jvals[1];
          double J_1_2 = 6.0e-34*S_3*S_0 - 7.9999999999999998e-12*S_1;
          double J_1_3 = 6.0e-34*S_2*S_0;
          double J_2_0 = -6.0e-34*S_3*S_2 + 2.0*jvals[0];
          double J_2_1 = -7.9999999999999998e-12*S_2 + 1.0*jvals[1];
          double J_2_2 = -6.0e-34*S_3*S_0 - 7.9999999999999998e-12*S_1;
          double J_2_3 = -6.0e-34*S_2*S_0;
          double W_0_0 = inv_g_dt;
          double W_1_0 = -J_1_0;
          double W_1_1 = inv_g_dt - J_1_1;
          double W_1_2 = -J_1_2;
          double W_1_3 = -J_1_3;
          double W_2_0 = -J_2_0;
          double W_2_1 = -J_2_1;
          double W_2_2 = inv_g_dt - J_2_2;
          double W_2_3 = -J_2_3;
          double W_3_3 = inv_g_dt;

          // Symbolic Doolittle Sparse LU Factorization
          // Block 0: species [O2, O]
          double U_0_0 = W_0_0;
          // Block 1: species [O3]
          double L_1_0 = (W_1_0) / U_0_0;
          double L_2_0 = (W_2_0) / U_0_0;
          double U_1_1 = W_1_1;
          double U_1_2 = W_1_2;
          double U_1_3 = W_1_3;
          double L_2_1 = (W_2_1) / U_1_1;
          double U_2_2 = W_2_2 - L_2_1 * U_1_2;
          double U_2_3 = W_2_3 - L_2_1 * U_1_3;
          // Block 2: species [M]
          double U_3_3 = W_3_3;

          // --- Stage 1 ---
          // Rate evaluation F1 at S
          double F1_0 = 0.0;
          double F1_1 = 6.0e-34*S_3*S_2*S_0 - 7.9999999999999998e-12*S_2*S_1 - 1.0*S_1*jvals[1];
          double F1_2 = -6.0e-34*S_3*S_2*S_0 - 7.9999999999999998e-12*S_2*S_1 + 2.0*S_0*jvals[0] + 1.0*S_1*jvals[1];
          double F1_3 = 0.0;
          // Block 0: K1 forward sub [O2, O]
          double y1_0 = F1_0;
          // Block 1: K1 forward sub [O3]
          double y1_1 = F1_1 - L_1_0 * y1_0;
          double y1_2 = F1_2 - L_2_0 * y1_0 - L_2_1 * y1_1;
          // Block 2: K1 forward sub [M]
          double y1_3 = F1_3;
          // Block 2: K1 backward sub [M]
          double K1_3 = y1_3 / U_3_3;
          // Block 0: K1 backward sub [O2, O]
          double K1_2 = (y1_2 - U_2_3 * K1_3) / U_2_2;
          // Block 1: K1 backward sub [O3]
          double K1_1 = (y1_1 - U_1_2 * K1_2 - U_1_3 * K1_3) / U_1_1;
          double K1_0 = y1_0 / U_0_0;

          // --- Stage 2 ---
          // Intermediate state Y2
          double Y2_0 = S_0 + K1_0;
          double Y2_1 = S_1 + K1_1;
          double Y2_2 = S_2 + K1_2;
          double Y2_3 = S_3 + K1_3;
          // Rate evaluation F2 at Y2
          double F2_0 = 0.0;
          double F2_1 = 6.0e-34*Y2_3*Y2_2*Y2_0 - 7.9999999999999998e-12*Y2_2*Y2_1 - 1.0*Y2_1*jvals[1];
          double F2_2 = -6.0e-34*Y2_3*Y2_2*Y2_0 - 7.9999999999999998e-12*Y2_2*Y2_1 + 2.0*Y2_0*jvals[0] + 1.0*Y2_1*jvals[1];
          double F2_3 = 0.0;
          // RHS for stage 2
          double rhs2_0 = F2_0 + (-1.0156171083877703 / dt) * K1_0;
          double rhs2_1 = F2_1 + (-1.0156171083877703 / dt) * K1_1;
          double rhs2_2 = F2_2 + (-1.0156171083877703 / dt) * K1_2;
          double rhs2_3 = F2_3 + (-1.0156171083877703 / dt) * K1_3;
          // Block 0: K2 forward sub [O2, O]
          double y2_0 = rhs2_0;
          // Block 1: K2 forward sub [O3]
          double y2_1 = rhs2_1 - L_1_0 * y2_0;
          double y2_2 = rhs2_2 - L_2_0 * y2_0 - L_2_1 * y2_1;
          // Block 2: K2 forward sub [M]
          double y2_3 = rhs2_3;
          // Block 2: K2 backward sub [M]
          double K2_3 = y2_3 / U_3_3;
          // Block 0: K2 backward sub [O2, O]
          double K2_2 = (y2_2 - U_2_3 * K2_3) / U_2_2;
          // Block 1: K2 backward sub [O3]
          double K2_1 = (y2_1 - U_1_2 * K2_2 - U_1_3 * K2_3) / U_1_1;
          double K2_0 = y2_0 / U_0_0;

          // --- Stage 3 ---
          // Intermediate state Y3
          double Y3_0 = S_0 + K1_0;
          double Y3_1 = S_1 + K1_1;
          double Y3_2 = S_2 + K1_2;
          double Y3_3 = S_3 + K1_3;
          // NewF=false: reuse F2 for stage 3
          // RHS for stage 3
          double rhs3_0 = F2_0 + (4.0759956452537702 / dt) * K1_0 + (9.20767942983308 / dt) * K2_0;
          double rhs3_1 = F2_1 + (4.0759956452537702 / dt) * K1_1 + (9.20767942983308 / dt) * K2_1;
          double rhs3_2 = F2_2 + (4.0759956452537702 / dt) * K1_2 + (9.20767942983308 / dt) * K2_2;
          double rhs3_3 = F2_3 + (4.0759956452537702 / dt) * K1_3 + (9.20767942983308 / dt) * K2_3;
          // Block 0: K3 forward sub [O2, O]
          double y3_0 = rhs3_0;
          // Block 1: K3 forward sub [O3]
          double y3_1 = rhs3_1 - L_1_0 * y3_0;
          double y3_2 = rhs3_2 - L_2_0 * y3_0 - L_2_1 * y3_1;
          // Block 2: K3 forward sub [M]
          double y3_3 = rhs3_3;
          // Block 2: K3 backward sub [M]
          double K3_3 = y3_3 / U_3_3;
          // Block 0: K3 backward sub [O2, O]
          double K3_2 = (y3_2 - U_2_3 * K3_3) / U_2_2;
          // Block 1: K3 backward sub [O3]
          double K3_1 = (y3_1 - U_1_2 * K3_2 - U_1_3 * K3_3) / U_1_1;
          double K3_0 = y3_0 / U_0_0;

          // --- Solution update and error estimation ---
          double err_norm_sq = 0.0;
          {
              double Ynew_i = S_0 + K1_0 + 6.1697947043828245 * K2_0 + -0.42772256543218573 * K3_0;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(1)), Kokkos::fabs(Ynew_i));
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
              double ymax = Kokkos::fmax(Kokkos::fabs(state(0)), Kokkos::fabs(Ynew_i));
              double sci = atol[2] + rtol[2] * ymax;
              double yerr_i = 0.5 * K1_2 + -2.9079558716805471 * K2_2 + 0.22354069897811571 * K3_2;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_3 + K1_3 + 6.1697947043828245 * K2_3 + -0.42772256543218573 * K3_3;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(3)), Kokkos::fabs(Ynew_i));
              double sci = atol[3] + rtol[3] * ymax;
              double yerr_i = 0.5 * K1_3 + -2.9079558716805471 * K2_3 + 0.22354069897811571 * K3_3;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          double err_norm = Kokkos::sqrt(err_norm_sq / 4);
          err_norm = Kokkos::fmax(err_norm, 1.0e-10);

          // Step Size Control (order 3: exponent = 1/3 = 0.33333333333333331)
          double factor = safety / Kokkos::cbrt(err_norm);
          factor = Kokkos::fmax(min_shrink, Kokkos::fmin(factor, max_growth));

          if (err_norm <= 1.0) {
              state(1) += K1_0 + 6.1697947043828245 * K2_0 + -0.42772256543218573 * K3_0;
              state(2) += K1_1 + 6.1697947043828245 * K2_1 + -0.42772256543218573 * K3_1;
              state(0) += K1_2 + 6.1697947043828245 * K2_2 + -0.42772256543218573 * K3_2;
              state(3) += K1_3 + 6.1697947043828245 * K2_3 + -0.42772256543218573 * K3_3;
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
          const int NUM_SPECIES = 4;
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

          while (t < dt_total) {
          dt = Kokkos::min(dt, dt_total - t);
          const double inv_g_dt = 1.0 / (g * dt);

          // 0. Hoist state values into scalar registers
          // NOTE: State access uses permuted species ordering
          const double S_0 = state(1);
          const double S_1 = state(2);
          const double S_2 = state(0);
          const double S_3 = state(3);

          // 1. Stage 1 Rates (F1)
          double F1_0 = 0.0;
          double F1_1 = 6.0e-34*S_3*S_2*S_0 - 7.9999999999999998e-12*S_2*S_1 - 1.0*S_1*jvals[1];
          double F1_2 = -6.0e-34*S_3*S_2*S_0 - 7.9999999999999998e-12*S_2*S_1 + 2.0*S_0*jvals[0] + 1.0*S_1*jvals[1];
          double F1_3 = 0.0;

          // 2. Evaluate importance and update active set
          active[0] = (Kokkos::fabs(F1_0) / (atol[0] + rtol[0] * Kokkos::fabs(state(1))) >= importance_threshold);
          active[1] = (Kokkos::fabs(F1_1) / (atol[1] + rtol[1] * Kokkos::fabs(state(2))) >= importance_threshold);
          active[2] = (Kokkos::fabs(F1_2) / (atol[2] + rtol[2] * Kokkos::fabs(state(0))) >= importance_threshold);
          active[3] = (Kokkos::fabs(F1_3) / (atol[3] + rtol[3] * Kokkos::fabs(state(3))) >= importance_threshold);

          // 3. Analytical Jacobian & Iteration Matrix W (identity for frozen species)
          double J_1_0 = 6.0e-34*S_3*S_2;
          double J_1_1 = -7.9999999999999998e-12*S_2 - 1.0*jvals[1];
          double J_1_2 = 6.0e-34*S_3*S_0 - 7.9999999999999998e-12*S_1;
          double J_1_3 = 6.0e-34*S_2*S_0;
          double J_2_0 = -6.0e-34*S_3*S_2 + 2.0*jvals[0];
          double J_2_1 = -7.9999999999999998e-12*S_2 + 1.0*jvals[1];
          double J_2_2 = -6.0e-34*S_3*S_0 - 7.9999999999999998e-12*S_1;
          double J_2_3 = -6.0e-34*S_2*S_0;
          double W_0_0 = active[0] ? inv_g_dt : 1.0;
          double W_1_0 = (active[1] && active[0]) ? (-J_1_0) : 0.0;
          double W_1_1 = active[1] ? (inv_g_dt - J_1_1) : 1.0;
          double W_1_2 = (active[1] && active[2]) ? (-J_1_2) : 0.0;
          double W_1_3 = (active[1] && active[3]) ? (-J_1_3) : 0.0;
          double W_2_0 = (active[2] && active[0]) ? (-J_2_0) : 0.0;
          double W_2_1 = (active[2] && active[1]) ? (-J_2_1) : 0.0;
          double W_2_2 = active[2] ? (inv_g_dt - J_2_2) : 1.0;
          double W_2_3 = (active[2] && active[3]) ? (-J_2_3) : 0.0;
          double W_3_3 = active[3] ? inv_g_dt : 1.0;

          // 4. Symbolic LU Factorization (conditional skip for frozen species)
          double U_0_0 = W_0_0;
          double L_1_0 = (W_1_0) / U_0_0;
          double L_2_0 = (W_2_0) / U_0_0;
          double U_1_1 = W_1_1;
          double U_1_2 = W_1_2;
          double U_1_3 = W_1_3;
          double L_2_1 = (W_2_1) / U_1_1;
          double U_2_2 = W_2_2 - L_2_1 * U_1_2;
          double U_2_3 = W_2_3 - L_2_1 * U_1_3;
          double U_3_3 = W_3_3;

          // --- Stage 1 ---
          // F1 already computed above (used for importance evaluation)
          // Block 0: K1 forward sub [O2, O]
          double y1_0 = active[0] ? (F1_0) : 0.0;
          // Block 1: K1 forward sub [O3]
          double y1_1 = active[1] ? (F1_1 - L_1_0 * y1_0) : 0.0;
          double y1_2 = active[2] ? (F1_2 - L_2_0 * y1_0 - L_2_1 * y1_1) : 0.0;
          // Block 2: K1 forward sub [M]
          double y1_3 = active[3] ? (F1_3) : 0.0;

          // Block 2: K1 backward sub [M]
          double K1_3 = active[3] ? (y1_3 / U_3_3) : 0.0;
          // Block 0: K1 backward sub [O2, O]
          double K1_2 = active[2] ? ((y1_2 - U_2_3 * K1_3) / U_2_2) : 0.0;
          // Block 1: K1 backward sub [O3]
          double K1_1 = active[1] ? ((y1_1 - U_1_2 * K1_2 - U_1_3 * K1_3) / U_1_1) : 0.0;
          double K1_0 = active[0] ? (y1_0 / U_0_0) : 0.0;


          // --- Stage 2 ---
          // Intermediate state Y2
          double Y2_0 = S_0 + K1_0;
          double Y2_1 = S_1 + K1_1;
          double Y2_2 = S_2 + K1_2;
          double Y2_3 = S_3 + K1_3;
          // Rate evaluation F2 at Y2
          double F2_0 = 0.0;
          double F2_1 = 6.0e-34*Y2_3*Y2_2*Y2_0 - 7.9999999999999998e-12*Y2_2*Y2_1 - 1.0*Y2_1*jvals[1];
          double F2_2 = -6.0e-34*Y2_3*Y2_2*Y2_0 - 7.9999999999999998e-12*Y2_2*Y2_1 + 2.0*Y2_0*jvals[0] + 1.0*Y2_1*jvals[1];
          double F2_3 = 0.0;
          // RHS for stage 2
          double rhs2_0 = F2_0 + (-1.0156171083877703 / dt) * K1_0;
          double rhs2_1 = F2_1 + (-1.0156171083877703 / dt) * K1_1;
          double rhs2_2 = F2_2 + (-1.0156171083877703 / dt) * K1_2;
          double rhs2_3 = F2_3 + (-1.0156171083877703 / dt) * K1_3;
          // Block 0: K2 forward sub [O2, O]
          double y2_0 = active[0] ? (rhs2_0) : 0.0;
          // Block 1: K2 forward sub [O3]
          double y2_1 = active[1] ? (rhs2_1 - L_1_0 * y2_0) : 0.0;
          double y2_2 = active[2] ? (rhs2_2 - L_2_0 * y2_0 - L_2_1 * y2_1) : 0.0;
          // Block 2: K2 forward sub [M]
          double y2_3 = active[3] ? (rhs2_3) : 0.0;

          // Block 2: K2 backward sub [M]
          double K2_3 = active[3] ? (y2_3 / U_3_3) : 0.0;
          // Block 0: K2 backward sub [O2, O]
          double K2_2 = active[2] ? ((y2_2 - U_2_3 * K2_3) / U_2_2) : 0.0;
          // Block 1: K2 backward sub [O3]
          double K2_1 = active[1] ? ((y2_1 - U_1_2 * K2_2 - U_1_3 * K2_3) / U_1_1) : 0.0;
          double K2_0 = active[0] ? (y2_0 / U_0_0) : 0.0;


          // --- Stage 3 ---
          // Intermediate state Y3
          double Y3_0 = S_0 + K1_0;
          double Y3_1 = S_1 + K1_1;
          double Y3_2 = S_2 + K1_2;
          double Y3_3 = S_3 + K1_3;
          // NewF=false: reuse F2 for stage 3
          // RHS for stage 3
          double rhs3_0 = F2_0 + (4.0759956452537702 / dt) * K1_0 + (9.20767942983308 / dt) * K2_0;
          double rhs3_1 = F2_1 + (4.0759956452537702 / dt) * K1_1 + (9.20767942983308 / dt) * K2_1;
          double rhs3_2 = F2_2 + (4.0759956452537702 / dt) * K1_2 + (9.20767942983308 / dt) * K2_2;
          double rhs3_3 = F2_3 + (4.0759956452537702 / dt) * K1_3 + (9.20767942983308 / dt) * K2_3;
          // Block 0: K3 forward sub [O2, O]
          double y3_0 = active[0] ? (rhs3_0) : 0.0;
          // Block 1: K3 forward sub [O3]
          double y3_1 = active[1] ? (rhs3_1 - L_1_0 * y3_0) : 0.0;
          double y3_2 = active[2] ? (rhs3_2 - L_2_0 * y3_0 - L_2_1 * y3_1) : 0.0;
          // Block 2: K3 forward sub [M]
          double y3_3 = active[3] ? (rhs3_3) : 0.0;

          // Block 2: K3 backward sub [M]
          double K3_3 = active[3] ? (y3_3 / U_3_3) : 0.0;
          // Block 0: K3 backward sub [O2, O]
          double K3_2 = active[2] ? ((y3_2 - U_2_3 * K3_3) / U_2_2) : 0.0;
          // Block 1: K3 backward sub [O3]
          double K3_1 = active[1] ? ((y3_1 - U_1_2 * K3_2 - U_1_3 * K3_3) / U_1_1) : 0.0;
          double K3_0 = active[0] ? (y3_0 / U_0_0) : 0.0;


          // --- Solution update and error estimation ---
          double err_norm_sq = 0.0;
          {
              double Ynew_i = S_0 + K1_0 + 6.1697947043828245 * K2_0 + -0.42772256543218573 * K3_0;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(1)), Kokkos::fabs(Ynew_i));
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
              double ymax = Kokkos::fmax(Kokkos::fabs(state(0)), Kokkos::fabs(Ynew_i));
              double sci = atol[2] + rtol[2] * ymax;
              double yerr_i = 0.5 * K1_2 + -2.9079558716805471 * K2_2 + 0.22354069897811571 * K3_2;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_3 + K1_3 + 6.1697947043828245 * K2_3 + -0.42772256543218573 * K3_3;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(3)), Kokkos::fabs(Ynew_i));
              double sci = atol[3] + rtol[3] * ymax;
              double yerr_i = 0.5 * K1_3 + -2.9079558716805471 * K2_3 + 0.22354069897811571 * K3_3;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          double err_norm = Kokkos::sqrt(err_norm_sq / 4);
          err_norm = Kokkos::fmax(err_norm, 1.0e-10);

          // Step Size Control (order 3: exponent = 1/3 = 0.33333333333333331)
          double factor = safety / Kokkos::cbrt(err_norm);
          factor = Kokkos::fmax(min_shrink, Kokkos::fmin(factor, max_growth));

          if (err_norm <= 1.0) {
              if (active[0]) state(1) += K1_0 + 6.1697947043828245 * K2_0 + -0.42772256543218573 * K3_0;
              if (active[1]) state(2) += K1_1 + 6.1697947043828245 * K2_1 + -0.42772256543218573 * K3_1;
              if (active[2]) state(0) += K1_2 + 6.1697947043828245 * K2_2 + -0.42772256543218573 * K3_2;
              if (active[3]) state(3) += K1_3 + 6.1697947043828245 * K2_3 + -0.42772256543218573 * K3_3;
              t += dt;
              dt *= factor;
          } else {
              dt *= factor;
          }
          } // end while (t < dt_total)
      }
  };
}
