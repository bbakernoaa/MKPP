#pragma once
#include <Kokkos_Core.hpp>
// Generated solver for saprc99_mini
// SZA Workload Sorted: true
// Hysteresis/Spline Continuous Transition: true
namespace mkpp {
  // Pure Kokkos abstractions (no raw pragmas allowed)

  /**
   * @brief Strongly typed enum for species indexing into state vectors.
   */
  enum Species : int {
      O3 = 0,
      H2O2 = 1,
      NO = 2,
      NO2 = 3,
      NO3 = 4,
      N2O5 = 5,
      HONO = 6,
      HNO3 = 7,
      HNO4 = 8,
      O3P = 9,
      OH = 10,
      HO2 = 11,
      AIR = 12,
      O2 = 13,
      H2O = 14,
      M = 15,
      N2 = 16
  };

#ifdef MKPP_ENABLE_ADJOINT
  // Checkpoint buffer for discrete adjoint/TLM integration
  // Recompute-J strategy: only state is stored, Jacobian recomputed from saved state
  struct CheckpointBuffer {
      static constexpr int MAX_STEPS = 200;
      static constexpr int NUM_SPECIES = 17;
      int num_steps = 0;
      double h[MAX_STEPS];
      double state[MAX_STEPS][NUM_SPECIES];  // saved concentrations at step entry
  };
#endif

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
          // F_block(O3): d[O3]/dt
          F_block(Species::O3) = 5.6800000000000035e-34*state(12)*state(13)*state(9) - 1.8706578944791917e-14*state(2)*state(0) - 3.7190909690468382e-17*state(3)*state(0) - 8.3355554445074843e-15*state(0)*state(9);
          // F_block(H2O2): d[H2O2]/dt
          F_block(Species::H2O2) = -1.0*state(1)*jvals[3] + 1.0*state(11)*(4.7653762320694437e-32*state(12) + 1.6994829027540494e-12);
          // F_block(NO): d[NO]/dt
          F_block(Species::NO) = 1.0*state(6)*jvals[1] - 2.5972503599796067e-11*state(2)*state(4) - 1.8706578944791917e-14*state(2)*state(0) + 1.0*state(3)*jvals[0];
          // F_block(NO2): d[NO2]/dt
          F_block(Species::NO2) = 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)*state(5)/(1.3459847134690284e-18*state(12) + 1.0) - 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)*state(3)*state(4)/(1.3846843902855162e-18*state(12) + 1.0) + 1.0*state(7)*jvals[2] + 5.1945007199592134e-11*state(2)*state(4) + 1.8706578944791917e-14*state(2)*state(0) - 3.7190909690468382e-17*state(3)*state(0) - 1.0*state(3)*jvals[0];
          // F_block(NO3): d[NO3]/dt
          F_block(Species::NO3) = 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)*state(5)/(1.3459847134690284e-18*state(12) + 1.0) - 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)*state(3)*state(4)/(1.3846843902855162e-18*state(12) + 1.0) + 1.0*state(7)*state(10)*(2.1296027497121323e-32*state(12)/(4.2746565719581312e-19*state(12) + 1.0) + 9.8568101265494379e-14) - 2.5972503599796067e-11*state(2)*state(4) + 3.7190909690468382e-17*state(3)*state(0);
          // F_block(N2O5): d[N2O5]/dt
          F_block(Species::N2O5) = -1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)*state(5)/(1.3459847134690284e-18*state(12) + 1.0) + 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)*state(3)*state(4)/(1.3846843902855162e-18*state(12) + 1.0);
          // F_block(HONO): d[HONO]/dt
          F_block(Species::HONO) = -1.0*state(6)*jvals[1];
          // F_block(HNO3): d[HNO3]/dt
          F_block(Species::HNO3) = -1.0*state(7)*state(10)*(2.1296027497121323e-32*state(12)/(4.2746565719581312e-19*state(12) + 1.0) + 9.8568101265494379e-14) - 1.0*state(7)*jvals[2];
          // F_block(HNO4): d[HNO4]/dt
          F_block(Species::HNO4) = 0.0;
          // F_block(O3P): d[O3P]/dt
          F_block(Species::O3P) = -5.6800000000000035e-34*state(12)*state(13)*state(9) + 1.0*state(3)*jvals[0] - 8.3355554445074843e-15*state(0)*state(9);
          // F_block(OH): d[OH]/dt
          F_block(Species::OH) = 2.0*state(1)*jvals[3] - 1.0*state(7)*state(10)*(2.1296027497121323e-32*state(12)/(4.2746565719581312e-19*state(12) + 1.0) + 9.8568101265494379e-14) + 1.0*state(7)*jvals[2] + 1.0*state(6)*jvals[1];
          // F_block(HO2): d[HO2]/dt
          F_block(Species::HO2) = -1.0*state(11)*(4.7653762320694437e-32*state(12) + 1.6994829027540494e-12);
          // F_block(AIR): d[AIR]/dt
          F_block(Species::AIR) = 0.0;
          // F_block(O2): d[O2]/dt
          F_block(Species::O2) = 0.0;
          // F_block(H2O): d[H2O]/dt
          F_block(Species::H2O) = 0.0;
          // F_block(M): d[M]/dt
          F_block(Species::M) = 0.0;
          // F_block(N2): d[N2]/dt
          F_block(Species::N2) = 0.0;
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
          // J(O3, O3): d(d[O3]/dt) / d[O3]
          J_block(Species::O3, Species::O3) = -1.8706578944791917e-14*state(2) - 3.7190909690468382e-17*state(3) - 8.3355554445074843e-15*state(9);
          // J(O3, NO): d(d[O3]/dt) / d[NO]
          J_block(Species::O3, Species::NO) = -1.8706578944791917e-14*state(0);
          // J(O3, NO2): d(d[O3]/dt) / d[NO2]
          J_block(Species::O3, Species::NO2) = -3.7190909690468382e-17*state(0);
          // J(O3, O3P): d(d[O3]/dt) / d[O3P]
          J_block(Species::O3, Species::O3P) = 5.6800000000000035e-34*state(12)*state(13) - 8.3355554445074843e-15*state(0);
          // J(O3, AIR): d(d[O3]/dt) / d[AIR]
          J_block(Species::O3, Species::AIR) = 5.6800000000000035e-34*state(13)*state(9);
          // J(O3, O2): d(d[O3]/dt) / d[O2]
          J_block(Species::O3, Species::O2) = 5.6800000000000035e-34*state(12)*state(9);
          // J(H2O2, H2O2): d(d[H2O2]/dt) / d[H2O2]
          J_block(Species::H2O2, Species::H2O2) = -1.0*jvals[3];
          // J(H2O2, HO2): d(d[H2O2]/dt) / d[HO2]
          J_block(Species::H2O2, Species::HO2) = 4.7653762320694437e-32*state(12) + 1.6994829027540494e-12;
          // J(H2O2, AIR): d(d[H2O2]/dt) / d[AIR]
          J_block(Species::H2O2, Species::AIR) = 4.7653762320694437e-32*state(11);
          // J(NO, O3): d(d[NO]/dt) / d[O3]
          J_block(Species::NO, Species::O3) = -1.8706578944791917e-14*state(2);
          // J(NO, NO): d(d[NO]/dt) / d[NO]
          J_block(Species::NO, Species::NO) = -2.5972503599796067e-11*state(4) - 1.8706578944791917e-14*state(0);
          // J(NO, NO2): d(d[NO]/dt) / d[NO2]
          J_block(Species::NO, Species::NO2) = 1.0*jvals[0];
          // J(NO, NO3): d(d[NO]/dt) / d[NO3]
          J_block(Species::NO, Species::NO3) = -2.5972503599796067e-11*state(2);
          // J(NO, HONO): d(d[NO]/dt) / d[HONO]
          J_block(Species::NO, Species::HONO) = 1.0*jvals[1];
          // J(NO2, O3): d(d[NO2]/dt) / d[O3]
          J_block(Species::NO2, Species::O3) = 1.8706578944791917e-14*state(2) - 3.7190909690468382e-17*state(3);
          // J(NO2, NO): d(d[NO2]/dt) / d[NO]
          J_block(Species::NO2, Species::NO) = 5.1945007199592134e-11*state(4) + 1.8706578944791917e-14*state(0);
          // J(NO2, NO2): d(d[NO2]/dt) / d[NO2]
          J_block(Species::NO2, Species::NO2) = -2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)*state(4)/(1.3846843902855162e-18*state(12) + 1.0) - 3.7190909690468382e-17*state(0) - 1.0*jvals[0];
          // J(NO2, NO3): d(d[NO2]/dt) / d[NO3]
          J_block(Species::NO2, Species::NO3) = -2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)*state(3)/(1.3846843902855162e-18*state(12) + 1.0) + 5.1945007199592134e-11*state(2);
          // J(NO2, N2O5): d(d[NO2]/dt) / d[N2O5]
          J_block(Species::NO2, Species::N2O5) = 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)/(1.3459847134690284e-18*state(12) + 1.0);
          // J(NO2, HNO3): d(d[NO2]/dt) / d[HNO3]
          J_block(Species::NO2, Species::HNO3) = 1.0*jvals[2];
          // J(NO2, AIR): d(d[NO2]/dt) / d[AIR]
          J_block(Species::NO2, Species::AIR) = -1.6029099488139965e-37*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)*state(5)/pow(1.3459847134690284e-18*state(12) + 1.0, 2) + 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(5)/(1.3459847134690284e-18*state(12) + 1.0) + 1.9018580488528996e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(5)*log(1.3459847134690284e-18*state(12))/((1.3459847134690284e-18*state(12) + 1.0)*pow(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10)) + 3.8321461055530778e-48*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)*state(3)*state(4)/pow(1.3846843902855162e-18*state(12) + 1.0, 2) - 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(3)*state(4)/(1.3846843902855162e-18*state(12) + 1.0) - 4.4197770694650986e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(3)*state(4)*log(1.3846843902855162e-18*state(12))/((1.3846843902855162e-18*state(12) + 1.0)*pow(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10));
          // J(NO3, O3): d(d[NO3]/dt) / d[O3]
          J_block(Species::NO3, Species::O3) = 3.7190909690468382e-17*state(3);
          // J(NO3, NO): d(d[NO3]/dt) / d[NO]
          J_block(Species::NO3, Species::NO) = -2.5972503599796067e-11*state(4);
          // J(NO3, NO2): d(d[NO3]/dt) / d[NO2]
          J_block(Species::NO3, Species::NO2) = -2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)*state(4)/(1.3846843902855162e-18*state(12) + 1.0) + 3.7190909690468382e-17*state(0);
          // J(NO3, NO3): d(d[NO3]/dt) / d[NO3]
          J_block(Species::NO3, Species::NO3) = -2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)*state(3)/(1.3846843902855162e-18*state(12) + 1.0) - 2.5972503599796067e-11*state(2);
          // J(NO3, N2O5): d(d[NO3]/dt) / d[N2O5]
          J_block(Species::NO3, Species::N2O5) = 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)/(1.3459847134690284e-18*state(12) + 1.0);
          // J(NO3, HNO3): d(d[NO3]/dt) / d[HNO3]
          J_block(Species::NO3, Species::HNO3) = 1.0*state(10)*(2.1296027497121323e-32*state(12)/(4.2746565719581312e-19*state(12) + 1.0) + 9.8568101265494379e-14);
          // J(NO3, OH): d(d[NO3]/dt) / d[OH]
          J_block(Species::NO3, Species::OH) = 1.0*state(7)*(2.1296027497121323e-32*state(12)/(4.2746565719581312e-19*state(12) + 1.0) + 9.8568101265494379e-14);
          // J(NO3, AIR): d(d[NO3]/dt) / d[AIR]
          J_block(Species::NO3, Species::AIR) = -1.6029099488139965e-37*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)*state(5)/pow(1.3459847134690284e-18*state(12) + 1.0, 2) + 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(5)/(1.3459847134690284e-18*state(12) + 1.0) + 1.9018580488528996e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(5)*log(1.3459847134690284e-18*state(12))/((1.3459847134690284e-18*state(12) + 1.0)*pow(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10)) + 3.8321461055530778e-48*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)*state(3)*state(4)/pow(1.3846843902855162e-18*state(12) + 1.0, 2) - 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(3)*state(4)/(1.3846843902855162e-18*state(12) + 1.0) - 4.4197770694650986e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(3)*state(4)*log(1.3846843902855162e-18*state(12))/((1.3846843902855162e-18*state(12) + 1.0)*pow(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10)) + 1.0*state(7)*state(10)*(-9.1033203897170818e-51*state(12)/pow(4.2746565719581312e-19*state(12) + 1.0, 2) + 2.1296027497121323e-32/(4.2746565719581312e-19*state(12) + 1.0));
          // J(N2O5, NO2): d(d[N2O5]/dt) / d[NO2]
          J_block(Species::N2O5, Species::NO2) = 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)*state(4)/(1.3846843902855162e-18*state(12) + 1.0);
          // J(N2O5, NO3): d(d[N2O5]/dt) / d[NO3]
          J_block(Species::N2O5, Species::NO3) = 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)*state(3)/(1.3846843902855162e-18*state(12) + 1.0);
          // J(N2O5, N2O5): d(d[N2O5]/dt) / d[N2O5]
          J_block(Species::N2O5, Species::N2O5) = -1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)/(1.3459847134690284e-18*state(12) + 1.0);
          // J(N2O5, AIR): d(d[N2O5]/dt) / d[AIR]
          J_block(Species::N2O5, Species::AIR) = 1.6029099488139965e-37*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)*state(5)/pow(1.3459847134690284e-18*state(12) + 1.0, 2) - 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(5)/(1.3459847134690284e-18*state(12) + 1.0) - 1.9018580488528996e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(5)*log(1.3459847134690284e-18*state(12))/((1.3459847134690284e-18*state(12) + 1.0)*pow(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10)) - 3.8321461055530778e-48*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)*state(3)*state(4)/pow(1.3846843902855162e-18*state(12) + 1.0, 2) + 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(3)*state(4)/(1.3846843902855162e-18*state(12) + 1.0) + 4.4197770694650986e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(3)*state(4)*log(1.3846843902855162e-18*state(12))/((1.3846843902855162e-18*state(12) + 1.0)*pow(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10));
          // J(HONO, HONO): d(d[HONO]/dt) / d[HONO]
          J_block(Species::HONO, Species::HONO) = -1.0*jvals[1];
          // J(HNO3, HNO3): d(d[HNO3]/dt) / d[HNO3]
          J_block(Species::HNO3, Species::HNO3) = -1.0*state(10)*(2.1296027497121323e-32*state(12)/(4.2746565719581312e-19*state(12) + 1.0) + 9.8568101265494379e-14) - 1.0*jvals[2];
          // J(HNO3, OH): d(d[HNO3]/dt) / d[OH]
          J_block(Species::HNO3, Species::OH) = -1.0*state(7)*(2.1296027497121323e-32*state(12)/(4.2746565719581312e-19*state(12) + 1.0) + 9.8568101265494379e-14);
          // J(HNO3, AIR): d(d[HNO3]/dt) / d[AIR]
          J_block(Species::HNO3, Species::AIR) = -1.0*state(7)*state(10)*(-9.1033203897170818e-51*state(12)/pow(4.2746565719581312e-19*state(12) + 1.0, 2) + 2.1296027497121323e-32/(4.2746565719581312e-19*state(12) + 1.0));
          // J(O3P, O3): d(d[O3P]/dt) / d[O3]
          J_block(Species::O3P, Species::O3) = -8.3355554445074843e-15*state(9);
          // J(O3P, NO2): d(d[O3P]/dt) / d[NO2]
          J_block(Species::O3P, Species::NO2) = 1.0*jvals[0];
          // J(O3P, O3P): d(d[O3P]/dt) / d[O3P]
          J_block(Species::O3P, Species::O3P) = -5.6800000000000035e-34*state(12)*state(13) - 8.3355554445074843e-15*state(0);
          // J(O3P, AIR): d(d[O3P]/dt) / d[AIR]
          J_block(Species::O3P, Species::AIR) = -5.6800000000000035e-34*state(13)*state(9);
          // J(O3P, O2): d(d[O3P]/dt) / d[O2]
          J_block(Species::O3P, Species::O2) = -5.6800000000000035e-34*state(12)*state(9);
          // J(OH, H2O2): d(d[OH]/dt) / d[H2O2]
          J_block(Species::OH, Species::H2O2) = 2.0*jvals[3];
          // J(OH, HONO): d(d[OH]/dt) / d[HONO]
          J_block(Species::OH, Species::HONO) = 1.0*jvals[1];
          // J(OH, HNO3): d(d[OH]/dt) / d[HNO3]
          J_block(Species::OH, Species::HNO3) = -1.0*state(10)*(2.1296027497121323e-32*state(12)/(4.2746565719581312e-19*state(12) + 1.0) + 9.8568101265494379e-14) + 1.0*jvals[2];
          // J(OH, OH): d(d[OH]/dt) / d[OH]
          J_block(Species::OH, Species::OH) = -1.0*state(7)*(2.1296027497121323e-32*state(12)/(4.2746565719581312e-19*state(12) + 1.0) + 9.8568101265494379e-14);
          // J(OH, AIR): d(d[OH]/dt) / d[AIR]
          J_block(Species::OH, Species::AIR) = -1.0*state(7)*state(10)*(-9.1033203897170818e-51*state(12)/pow(4.2746565719581312e-19*state(12) + 1.0, 2) + 2.1296027497121323e-32/(4.2746565719581312e-19*state(12) + 1.0));
          // J(HO2, HO2): d(d[HO2]/dt) / d[HO2]
          J_block(Species::HO2, Species::HO2) = -4.7653762320694437e-32*state(12) - 1.6994829027540494e-12;
          // J(HO2, AIR): d(d[HO2]/dt) / d[AIR]
          J_block(Species::HO2, Species::AIR) = -4.7653762320694437e-32*state(11);
      }

#ifdef MKPP_ENABLE_ADJOINT
      template <class StateView, class JacView>
      KOKKOS_INLINE_FUNCTION void compute_adjoint(const StateView& state, JacView& J_adj_block, const double* jvals) const {
          // --- Sparse Analytical Adjoint Jacobian Entries J_adj_block(i, j) = J^T(i, j) ---
          // J^T(O3, O3): d(d[O3]/dt) / d[O3]
          J_adj_block(Species::O3, Species::O3) = -1.8706578944791917e-14*state(2) - 3.7190909690468382e-17*state(3) - 8.3355554445074843e-15*state(9);
          // J^T(O3, NO): d(d[NO]/dt) / d[O3]
          J_adj_block(Species::O3, Species::NO) = -1.8706578944791917e-14*state(2);
          // J^T(O3, NO2): d(d[NO2]/dt) / d[O3]
          J_adj_block(Species::O3, Species::NO2) = 1.8706578944791917e-14*state(2) - 3.7190909690468382e-17*state(3);
          // J^T(O3, NO3): d(d[NO3]/dt) / d[O3]
          J_adj_block(Species::O3, Species::NO3) = 3.7190909690468382e-17*state(3);
          // J^T(O3, O3P): d(d[O3P]/dt) / d[O3]
          J_adj_block(Species::O3, Species::O3P) = -8.3355554445074843e-15*state(9);
          // J^T(H2O2, H2O2): d(d[H2O2]/dt) / d[H2O2]
          J_adj_block(Species::H2O2, Species::H2O2) = -1.0*jvals[3];
          // J^T(H2O2, OH): d(d[OH]/dt) / d[H2O2]
          J_adj_block(Species::H2O2, Species::OH) = 2.0*jvals[3];
          // J^T(NO, O3): d(d[O3]/dt) / d[NO]
          J_adj_block(Species::NO, Species::O3) = -1.8706578944791917e-14*state(0);
          // J^T(NO, NO): d(d[NO]/dt) / d[NO]
          J_adj_block(Species::NO, Species::NO) = -2.5972503599796067e-11*state(4) - 1.8706578944791917e-14*state(0);
          // J^T(NO, NO2): d(d[NO2]/dt) / d[NO]
          J_adj_block(Species::NO, Species::NO2) = 5.1945007199592134e-11*state(4) + 1.8706578944791917e-14*state(0);
          // J^T(NO, NO3): d(d[NO3]/dt) / d[NO]
          J_adj_block(Species::NO, Species::NO3) = -2.5972503599796067e-11*state(4);
          // J^T(NO2, O3): d(d[O3]/dt) / d[NO2]
          J_adj_block(Species::NO2, Species::O3) = -3.7190909690468382e-17*state(0);
          // J^T(NO2, NO): d(d[NO]/dt) / d[NO2]
          J_adj_block(Species::NO2, Species::NO) = 1.0*jvals[0];
          // J^T(NO2, NO2): d(d[NO2]/dt) / d[NO2]
          J_adj_block(Species::NO2, Species::NO2) = -2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)*state(4)/(1.3846843902855162e-18*state(12) + 1.0) - 3.7190909690468382e-17*state(0) - 1.0*jvals[0];
          // J^T(NO2, NO3): d(d[NO3]/dt) / d[NO2]
          J_adj_block(Species::NO2, Species::NO3) = -2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)*state(4)/(1.3846843902855162e-18*state(12) + 1.0) + 3.7190909690468382e-17*state(0);
          // J^T(NO2, N2O5): d(d[N2O5]/dt) / d[NO2]
          J_adj_block(Species::NO2, Species::N2O5) = 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)*state(4)/(1.3846843902855162e-18*state(12) + 1.0);
          // J^T(NO2, O3P): d(d[O3P]/dt) / d[NO2]
          J_adj_block(Species::NO2, Species::O3P) = 1.0*jvals[0];
          // J^T(NO3, NO): d(d[NO]/dt) / d[NO3]
          J_adj_block(Species::NO3, Species::NO) = -2.5972503599796067e-11*state(2);
          // J^T(NO3, NO2): d(d[NO2]/dt) / d[NO3]
          J_adj_block(Species::NO3, Species::NO2) = -2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)*state(3)/(1.3846843902855162e-18*state(12) + 1.0) + 5.1945007199592134e-11*state(2);
          // J^T(NO3, NO3): d(d[NO3]/dt) / d[NO3]
          J_adj_block(Species::NO3, Species::NO3) = -2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)*state(3)/(1.3846843902855162e-18*state(12) + 1.0) - 2.5972503599796067e-11*state(2);
          // J^T(NO3, N2O5): d(d[N2O5]/dt) / d[NO3]
          J_adj_block(Species::NO3, Species::N2O5) = 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)*state(3)/(1.3846843902855162e-18*state(12) + 1.0);
          // J^T(N2O5, NO2): d(d[NO2]/dt) / d[N2O5]
          J_adj_block(Species::N2O5, Species::NO2) = 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)/(1.3459847134690284e-18*state(12) + 1.0);
          // J^T(N2O5, NO3): d(d[NO3]/dt) / d[N2O5]
          J_adj_block(Species::N2O5, Species::NO3) = 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)/(1.3459847134690284e-18*state(12) + 1.0);
          // J^T(N2O5, N2O5): d(d[N2O5]/dt) / d[N2O5]
          J_adj_block(Species::N2O5, Species::N2O5) = -1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)/(1.3459847134690284e-18*state(12) + 1.0);
          // J^T(HONO, NO): d(d[NO]/dt) / d[HONO]
          J_adj_block(Species::HONO, Species::NO) = 1.0*jvals[1];
          // J^T(HONO, HONO): d(d[HONO]/dt) / d[HONO]
          J_adj_block(Species::HONO, Species::HONO) = -1.0*jvals[1];
          // J^T(HONO, OH): d(d[OH]/dt) / d[HONO]
          J_adj_block(Species::HONO, Species::OH) = 1.0*jvals[1];
          // J^T(HNO3, NO2): d(d[NO2]/dt) / d[HNO3]
          J_adj_block(Species::HNO3, Species::NO2) = 1.0*jvals[2];
          // J^T(HNO3, NO3): d(d[NO3]/dt) / d[HNO3]
          J_adj_block(Species::HNO3, Species::NO3) = 1.0*state(10)*(2.1296027497121323e-32*state(12)/(4.2746565719581312e-19*state(12) + 1.0) + 9.8568101265494379e-14);
          // J^T(HNO3, HNO3): d(d[HNO3]/dt) / d[HNO3]
          J_adj_block(Species::HNO3, Species::HNO3) = -1.0*state(10)*(2.1296027497121323e-32*state(12)/(4.2746565719581312e-19*state(12) + 1.0) + 9.8568101265494379e-14) - 1.0*jvals[2];
          // J^T(HNO3, OH): d(d[OH]/dt) / d[HNO3]
          J_adj_block(Species::HNO3, Species::OH) = -1.0*state(10)*(2.1296027497121323e-32*state(12)/(4.2746565719581312e-19*state(12) + 1.0) + 9.8568101265494379e-14) + 1.0*jvals[2];
          // J^T(O3P, O3): d(d[O3]/dt) / d[O3P]
          J_adj_block(Species::O3P, Species::O3) = 5.6800000000000035e-34*state(12)*state(13) - 8.3355554445074843e-15*state(0);
          // J^T(O3P, O3P): d(d[O3P]/dt) / d[O3P]
          J_adj_block(Species::O3P, Species::O3P) = -5.6800000000000035e-34*state(12)*state(13) - 8.3355554445074843e-15*state(0);
          // J^T(OH, NO3): d(d[NO3]/dt) / d[OH]
          J_adj_block(Species::OH, Species::NO3) = 1.0*state(7)*(2.1296027497121323e-32*state(12)/(4.2746565719581312e-19*state(12) + 1.0) + 9.8568101265494379e-14);
          // J^T(OH, HNO3): d(d[HNO3]/dt) / d[OH]
          J_adj_block(Species::OH, Species::HNO3) = -1.0*state(7)*(2.1296027497121323e-32*state(12)/(4.2746565719581312e-19*state(12) + 1.0) + 9.8568101265494379e-14);
          // J^T(OH, OH): d(d[OH]/dt) / d[OH]
          J_adj_block(Species::OH, Species::OH) = -1.0*state(7)*(2.1296027497121323e-32*state(12)/(4.2746565719581312e-19*state(12) + 1.0) + 9.8568101265494379e-14);
          // J^T(HO2, H2O2): d(d[H2O2]/dt) / d[HO2]
          J_adj_block(Species::HO2, Species::H2O2) = 4.7653762320694437e-32*state(12) + 1.6994829027540494e-12;
          // J^T(HO2, HO2): d(d[HO2]/dt) / d[HO2]
          J_adj_block(Species::HO2, Species::HO2) = -4.7653762320694437e-32*state(12) - 1.6994829027540494e-12;
          // J^T(AIR, O3): d(d[O3]/dt) / d[AIR]
          J_adj_block(Species::AIR, Species::O3) = 5.6800000000000035e-34*state(13)*state(9);
          // J^T(AIR, H2O2): d(d[H2O2]/dt) / d[AIR]
          J_adj_block(Species::AIR, Species::H2O2) = 4.7653762320694437e-32*state(11);
          // J^T(AIR, NO2): d(d[NO2]/dt) / d[AIR]
          J_adj_block(Species::AIR, Species::NO2) = -1.6029099488139965e-37*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)*state(5)/pow(1.3459847134690284e-18*state(12) + 1.0, 2) + 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(5)/(1.3459847134690284e-18*state(12) + 1.0) + 1.9018580488528996e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(5)*log(1.3459847134690284e-18*state(12))/((1.3459847134690284e-18*state(12) + 1.0)*pow(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10)) + 3.8321461055530778e-48*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)*state(3)*state(4)/pow(1.3846843902855162e-18*state(12) + 1.0, 2) - 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(3)*state(4)/(1.3846843902855162e-18*state(12) + 1.0) - 4.4197770694650986e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(3)*state(4)*log(1.3846843902855162e-18*state(12))/((1.3846843902855162e-18*state(12) + 1.0)*pow(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10));
          // J^T(AIR, NO3): d(d[NO3]/dt) / d[AIR]
          J_adj_block(Species::AIR, Species::NO3) = -1.6029099488139965e-37*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)*state(5)/pow(1.3459847134690284e-18*state(12) + 1.0, 2) + 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(5)/(1.3459847134690284e-18*state(12) + 1.0) + 1.9018580488528996e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(5)*log(1.3459847134690284e-18*state(12))/((1.3459847134690284e-18*state(12) + 1.0)*pow(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10)) + 3.8321461055530778e-48*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)*state(3)*state(4)/pow(1.3846843902855162e-18*state(12) + 1.0, 2) - 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(3)*state(4)/(1.3846843902855162e-18*state(12) + 1.0) - 4.4197770694650986e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(3)*state(4)*log(1.3846843902855162e-18*state(12))/((1.3846843902855162e-18*state(12) + 1.0)*pow(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10)) + 1.0*state(7)*state(10)*(-9.1033203897170818e-51*state(12)/pow(4.2746565719581312e-19*state(12) + 1.0, 2) + 2.1296027497121323e-32/(4.2746565719581312e-19*state(12) + 1.0));
          // J^T(AIR, N2O5): d(d[N2O5]/dt) / d[AIR]
          J_adj_block(Species::AIR, Species::N2O5) = 1.6029099488139965e-37*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)*state(5)/pow(1.3459847134690284e-18*state(12) + 1.0, 2) - 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(5)/(1.3459847134690284e-18*state(12) + 1.0) - 1.9018580488528996e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(5)*log(1.3459847134690284e-18*state(12))/((1.3459847134690284e-18*state(12) + 1.0)*pow(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10)) - 3.8321461055530778e-48*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)*state(3)*state(4)/pow(1.3846843902855162e-18*state(12) + 1.0, 2) + 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(3)*state(4)/(1.3846843902855162e-18*state(12) + 1.0) + 4.4197770694650986e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(3)*state(4)*log(1.3846843902855162e-18*state(12))/((1.3846843902855162e-18*state(12) + 1.0)*pow(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10));
          // J^T(AIR, HNO3): d(d[HNO3]/dt) / d[AIR]
          J_adj_block(Species::AIR, Species::HNO3) = -1.0*state(7)*state(10)*(-9.1033203897170818e-51*state(12)/pow(4.2746565719581312e-19*state(12) + 1.0, 2) + 2.1296027497121323e-32/(4.2746565719581312e-19*state(12) + 1.0));
          // J^T(AIR, O3P): d(d[O3P]/dt) / d[AIR]
          J_adj_block(Species::AIR, Species::O3P) = -5.6800000000000035e-34*state(13)*state(9);
          // J^T(AIR, OH): d(d[OH]/dt) / d[AIR]
          J_adj_block(Species::AIR, Species::OH) = -1.0*state(7)*state(10)*(-9.1033203897170818e-51*state(12)/pow(4.2746565719581312e-19*state(12) + 1.0, 2) + 2.1296027497121323e-32/(4.2746565719581312e-19*state(12) + 1.0));
          // J^T(AIR, HO2): d(d[HO2]/dt) / d[AIR]
          J_adj_block(Species::AIR, Species::HO2) = -4.7653762320694437e-32*state(11);
          // J^T(O2, O3): d(d[O3]/dt) / d[O2]
          J_adj_block(Species::O2, Species::O3) = 5.6800000000000035e-34*state(12)*state(9);
          // J^T(O2, O3P): d(d[O3P]/dt) / d[O2]
          J_adj_block(Species::O2, Species::O3P) = -5.6800000000000035e-34*state(12)*state(9);
      }
#endif

#ifdef MKPP_ENABLE_ADJOINT
      template <class StateView, class DeltaView, class RateView>
      KOKKOS_INLINE_FUNCTION void compute_tlm(const StateView& state, const DeltaView& delta_C, RateView& dF_block, const double* jvals) const {
          dF_block(0) = 0.0;
          dF_block(0) += (-1.8706578944791917e-14*state(2) - 3.7190909690468382e-17*state(3) - 8.3355554445074843e-15*state(9)) * delta_C(0);
          dF_block(0) += (-1.8706578944791917e-14*state(0)) * delta_C(2);
          dF_block(0) += (-3.7190909690468382e-17*state(0)) * delta_C(3);
          dF_block(0) += (5.6800000000000035e-34*state(12)*state(13) - 8.3355554445074843e-15*state(0)) * delta_C(9);
          dF_block(0) += (5.6800000000000035e-34*state(13)*state(9)) * delta_C(12);
          dF_block(0) += (5.6800000000000035e-34*state(12)*state(9)) * delta_C(13);
          dF_block(1) = 0.0;
          dF_block(1) += (-1.0*jvals[3]) * delta_C(1);
          dF_block(1) += (4.7653762320694437e-32*state(12) + 1.6994829027540494e-12) * delta_C(11);
          dF_block(1) += (4.7653762320694437e-32*state(11)) * delta_C(12);
          dF_block(2) = 0.0;
          dF_block(2) += (-1.8706578944791917e-14*state(2)) * delta_C(0);
          dF_block(2) += (-2.5972503599796067e-11*state(4) - 1.8706578944791917e-14*state(0)) * delta_C(2);
          dF_block(2) += (1.0*jvals[0]) * delta_C(3);
          dF_block(2) += (-2.5972503599796067e-11*state(2)) * delta_C(4);
          dF_block(2) += (1.0*jvals[1]) * delta_C(6);
          dF_block(3) = 0.0;
          dF_block(3) += (1.8706578944791917e-14*state(2) - 3.7190909690468382e-17*state(3)) * delta_C(0);
          dF_block(3) += (5.1945007199592134e-11*state(4) + 1.8706578944791917e-14*state(0)) * delta_C(2);
          dF_block(3) += (-2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)*state(4)/(1.3846843902855162e-18*state(12) + 1.0) - 3.7190909690468382e-17*state(0) - 1.0*jvals[0]) * delta_C(3);
          dF_block(3) += (-2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)*state(3)/(1.3846843902855162e-18*state(12) + 1.0) + 5.1945007199592134e-11*state(2)) * delta_C(4);
          dF_block(3) += (1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)/(1.3459847134690284e-18*state(12) + 1.0)) * delta_C(5);
          dF_block(3) += (1.0*jvals[2]) * delta_C(7);
          dF_block(3) += (-1.6029099488139965e-37*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)*state(5)/pow(1.3459847134690284e-18*state(12) + 1.0, 2) + 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(5)/(1.3459847134690284e-18*state(12) + 1.0) + 1.9018580488528996e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(5)*log(1.3459847134690284e-18*state(12))/((1.3459847134690284e-18*state(12) + 1.0)*pow(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10)) + 3.8321461055530778e-48*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)*state(3)*state(4)/pow(1.3846843902855162e-18*state(12) + 1.0, 2) - 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(3)*state(4)/(1.3846843902855162e-18*state(12) + 1.0) - 4.4197770694650986e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(3)*state(4)*log(1.3846843902855162e-18*state(12))/((1.3846843902855162e-18*state(12) + 1.0)*pow(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10))) * delta_C(12);
          dF_block(4) = 0.0;
          dF_block(4) += (3.7190909690468382e-17*state(3)) * delta_C(0);
          dF_block(4) += (-2.5972503599796067e-11*state(4)) * delta_C(2);
          dF_block(4) += (-2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)*state(4)/(1.3846843902855162e-18*state(12) + 1.0) + 3.7190909690468382e-17*state(0)) * delta_C(3);
          dF_block(4) += (-2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)*state(3)/(1.3846843902855162e-18*state(12) + 1.0) - 2.5972503599796067e-11*state(2)) * delta_C(4);
          dF_block(4) += (1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)/(1.3459847134690284e-18*state(12) + 1.0)) * delta_C(5);
          dF_block(4) += (1.0*state(10)*(2.1296027497121323e-32*state(12)/(4.2746565719581312e-19*state(12) + 1.0) + 9.8568101265494379e-14)) * delta_C(7);
          dF_block(4) += (1.0*state(7)*(2.1296027497121323e-32*state(12)/(4.2746565719581312e-19*state(12) + 1.0) + 9.8568101265494379e-14)) * delta_C(10);
          dF_block(4) += (-1.6029099488139965e-37*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)*state(5)/pow(1.3459847134690284e-18*state(12) + 1.0, 2) + 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(5)/(1.3459847134690284e-18*state(12) + 1.0) + 1.9018580488528996e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(5)*log(1.3459847134690284e-18*state(12))/((1.3459847134690284e-18*state(12) + 1.0)*pow(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10)) + 3.8321461055530778e-48*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)*state(3)*state(4)/pow(1.3846843902855162e-18*state(12) + 1.0, 2) - 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(3)*state(4)/(1.3846843902855162e-18*state(12) + 1.0) - 4.4197770694650986e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(3)*state(4)*log(1.3846843902855162e-18*state(12))/((1.3846843902855162e-18*state(12) + 1.0)*pow(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10)) + 1.0*state(7)*state(10)*(-9.1033203897170818e-51*state(12)/pow(4.2746565719581312e-19*state(12) + 1.0, 2) + 2.1296027497121323e-32/(4.2746565719581312e-19*state(12) + 1.0))) * delta_C(12);
          dF_block(5) = 0.0;
          dF_block(5) += (2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)*state(4)/(1.3846843902855162e-18*state(12) + 1.0)) * delta_C(3);
          dF_block(5) += (2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)*state(3)/(1.3846843902855162e-18*state(12) + 1.0)) * delta_C(4);
          dF_block(5) += (-1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)/(1.3459847134690284e-18*state(12) + 1.0)) * delta_C(5);
          dF_block(5) += (1.6029099488139965e-37*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)*state(5)/pow(1.3459847134690284e-18*state(12) + 1.0, 2) - 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(5)/(1.3459847134690284e-18*state(12) + 1.0) - 1.9018580488528996e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(5)*log(1.3459847134690284e-18*state(12))/((1.3459847134690284e-18*state(12) + 1.0)*pow(pow(log(1.3459847134690284e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10)) - 3.8321461055530778e-48*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(12)*state(3)*state(4)/pow(1.3846843902855162e-18*state(12) + 1.0, 2) + 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(3)*state(4)/(1.3846843902855162e-18*state(12) + 1.0) + 4.4197770694650986e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0))*state(3)*state(4)*log(1.3846843902855162e-18*state(12))/((1.3846843902855162e-18*state(12) + 1.0)*pow(pow(log(1.3846843902855162e-18*state(12)), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10))) * delta_C(12);
          dF_block(6) = 0.0;
          dF_block(6) += (-1.0*jvals[1]) * delta_C(6);
          dF_block(7) = 0.0;
          dF_block(7) += (-1.0*state(10)*(2.1296027497121323e-32*state(12)/(4.2746565719581312e-19*state(12) + 1.0) + 9.8568101265494379e-14) - 1.0*jvals[2]) * delta_C(7);
          dF_block(7) += (-1.0*state(7)*(2.1296027497121323e-32*state(12)/(4.2746565719581312e-19*state(12) + 1.0) + 9.8568101265494379e-14)) * delta_C(10);
          dF_block(7) += (-1.0*state(7)*state(10)*(-9.1033203897170818e-51*state(12)/pow(4.2746565719581312e-19*state(12) + 1.0, 2) + 2.1296027497121323e-32/(4.2746565719581312e-19*state(12) + 1.0))) * delta_C(12);
          dF_block(8) = 0.0;
          dF_block(9) = 0.0;
          dF_block(9) += (-8.3355554445074843e-15*state(9)) * delta_C(0);
          dF_block(9) += (1.0*jvals[0]) * delta_C(3);
          dF_block(9) += (-5.6800000000000035e-34*state(12)*state(13) - 8.3355554445074843e-15*state(0)) * delta_C(9);
          dF_block(9) += (-5.6800000000000035e-34*state(13)*state(9)) * delta_C(12);
          dF_block(9) += (-5.6800000000000035e-34*state(12)*state(9)) * delta_C(13);
          dF_block(10) = 0.0;
          dF_block(10) += (2.0*jvals[3]) * delta_C(1);
          dF_block(10) += (1.0*jvals[1]) * delta_C(6);
          dF_block(10) += (-1.0*state(10)*(2.1296027497121323e-32*state(12)/(4.2746565719581312e-19*state(12) + 1.0) + 9.8568101265494379e-14) + 1.0*jvals[2]) * delta_C(7);
          dF_block(10) += (-1.0*state(7)*(2.1296027497121323e-32*state(12)/(4.2746565719581312e-19*state(12) + 1.0) + 9.8568101265494379e-14)) * delta_C(10);
          dF_block(10) += (-1.0*state(7)*state(10)*(-9.1033203897170818e-51*state(12)/pow(4.2746565719581312e-19*state(12) + 1.0, 2) + 2.1296027497121323e-32/(4.2746565719581312e-19*state(12) + 1.0))) * delta_C(12);
          dF_block(11) = 0.0;
          dF_block(11) += (-4.7653762320694437e-32*state(12) - 1.6994829027540494e-12) * delta_C(11);
          dF_block(11) += (-4.7653762320694437e-32*state(11)) * delta_C(12);
          dF_block(12) = 0.0;
          dF_block(13) = 0.0;
          dF_block(14) = 0.0;
          dF_block(15) = 0.0;
          dF_block(16) = 0.0;
      }
#endif

      template <class StateView, class MassView>
      KOKKOS_INLINE_FUNCTION void project_mass_conservation(StateView& C_projected, const StateView& C, const MassView& m_0) const {
          // C_projected = C - E^T (E E^T)^-1 (E C - m_0)
      }

      static constexpr int NUM_SPECIES = 17;
      static constexpr double atol[NUM_SPECIES] = { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 };
      static constexpr double rtol[NUM_SPECIES] = { 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001 };

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
          const int NUM_SPECIES = 17;
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
          const double S_0 = state(Species::N2);  // [N2]
          const double S_1 = state(Species::M);  // [M]
          const double S_2 = state(Species::H2O);  // [H2O]
          const double S_3 = state(Species::HNO4);  // [HNO4]
          const double S_4 = state(Species::NO);  // [NO]
          const double S_5 = state(Species::O2);  // [O2]
          const double S_6 = state(Species::HONO);  // [HONO]
          const double S_7 = state(Species::NO3);  // [NO3]
          const double S_8 = state(Species::NO2);  // [NO2]
          const double S_9 = state(Species::O3);  // [O3]
          const double S_10 = state(Species::O3P);  // [O3P]
          const double S_11 = state(Species::HNO3);  // [HNO3]
          const double S_12 = state(Species::N2O5);  // [N2O5]
          const double S_13 = state(Species::OH);  // [OH]
          const double S_14 = state(Species::AIR);  // [AIR]
          const double S_15 = state(Species::H2O2);  // [H2O2]
          const double S_16 = state(Species::HO2);  // [HO2]

          // Analytical Jacobian & Iteration Matrix W = inv_g_dt*I - J (sparse)
          double J_4_4 = -2.5972503599796067e-11*S_7 - 1.8706578944791917e-14*S_9;
          double J_4_6 = 1.0*jvals[1];
          double J_4_7 = -2.5972503599796067e-11*S_4;
          double J_4_8 = 1.0*jvals[0];
          double J_4_9 = -1.8706578944791917e-14*S_4;
          double J_6_6 = -1.0*jvals[1];
          double J_7_4 = -2.5972503599796067e-11*S_7;
          double J_7_7 = -2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_8/(1.3846843902855162e-18*S_14 + 1.0) - 2.5972503599796067e-11*S_4;
          double J_7_8 = -2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_7/(1.3846843902855162e-18*S_14 + 1.0) + 3.7190909690468382e-17*S_9;
          double J_7_9 = 3.7190909690468382e-17*S_8;
          double J_7_11 = 1.0*S_13*(2.1296027497121323e-32*S_14/(4.2746565719581312e-19*S_14 + 1.0) + 9.8568101265494379e-14);
          double J_7_12 = 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14/(1.3459847134690284e-18*S_14 + 1.0);
          double J_7_13 = 1.0*S_11*(2.1296027497121323e-32*S_14/(4.2746565719581312e-19*S_14 + 1.0) + 9.8568101265494379e-14);
          double J_7_14 = -1.6029099488139965e-37*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_12/pow(1.3459847134690284e-18*S_14 + 1.0, 2) + 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_12/(1.3459847134690284e-18*S_14 + 1.0) + 1.9018580488528996e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_12*log(1.3459847134690284e-18*S_14)/((1.3459847134690284e-18*S_14 + 1.0)*pow(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10)) + 3.8321461055530778e-48*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_8*S_7/pow(1.3846843902855162e-18*S_14 + 1.0, 2) - 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_8*S_7/(1.3846843902855162e-18*S_14 + 1.0) - 4.4197770694650986e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_8*S_7*log(1.3846843902855162e-18*S_14)/((1.3846843902855162e-18*S_14 + 1.0)*pow(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10)) + 1.0*S_11*S_13*(-9.1033203897170818e-51*S_14/pow(4.2746565719581312e-19*S_14 + 1.0, 2) + 2.1296027497121323e-32/(4.2746565719581312e-19*S_14 + 1.0));
          double J_8_4 = 5.1945007199592134e-11*S_7 + 1.8706578944791917e-14*S_9;
          double J_8_7 = -2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_8/(1.3846843902855162e-18*S_14 + 1.0) + 5.1945007199592134e-11*S_4;
          double J_8_8 = -2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_7/(1.3846843902855162e-18*S_14 + 1.0) - 3.7190909690468382e-17*S_9 - 1.0*jvals[0];
          double J_8_9 = 1.8706578944791917e-14*S_4 - 3.7190909690468382e-17*S_8;
          double J_8_11 = 1.0*jvals[2];
          double J_8_12 = 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14/(1.3459847134690284e-18*S_14 + 1.0);
          double J_8_14 = -1.6029099488139965e-37*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_12/pow(1.3459847134690284e-18*S_14 + 1.0, 2) + 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_12/(1.3459847134690284e-18*S_14 + 1.0) + 1.9018580488528996e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_12*log(1.3459847134690284e-18*S_14)/((1.3459847134690284e-18*S_14 + 1.0)*pow(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10)) + 3.8321461055530778e-48*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_8*S_7/pow(1.3846843902855162e-18*S_14 + 1.0, 2) - 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_8*S_7/(1.3846843902855162e-18*S_14 + 1.0) - 4.4197770694650986e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_8*S_7*log(1.3846843902855162e-18*S_14)/((1.3846843902855162e-18*S_14 + 1.0)*pow(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10));
          double J_9_4 = -1.8706578944791917e-14*S_9;
          double J_9_5 = 5.6800000000000035e-34*S_14*S_10;
          double J_9_8 = -3.7190909690468382e-17*S_9;
          double J_9_9 = -1.8706578944791917e-14*S_4 - 3.7190909690468382e-17*S_8 - 8.3355554445074843e-15*S_10;
          double J_9_10 = 5.6800000000000035e-34*S_14*S_5 - 8.3355554445074843e-15*S_9;
          double J_9_14 = 5.6800000000000035e-34*S_5*S_10;
          double J_10_5 = -5.6800000000000035e-34*S_14*S_10;
          double J_10_8 = 1.0*jvals[0];
          double J_10_9 = -8.3355554445074843e-15*S_10;
          double J_10_10 = -5.6800000000000035e-34*S_14*S_5 - 8.3355554445074843e-15*S_9;
          double J_10_14 = -5.6800000000000035e-34*S_5*S_10;
          double J_11_11 = -1.0*S_13*(2.1296027497121323e-32*S_14/(4.2746565719581312e-19*S_14 + 1.0) + 9.8568101265494379e-14) - 1.0*jvals[2];
          double J_11_13 = -1.0*S_11*(2.1296027497121323e-32*S_14/(4.2746565719581312e-19*S_14 + 1.0) + 9.8568101265494379e-14);
          double J_11_14 = -1.0*S_11*S_13*(-9.1033203897170818e-51*S_14/pow(4.2746565719581312e-19*S_14 + 1.0, 2) + 2.1296027497121323e-32/(4.2746565719581312e-19*S_14 + 1.0));
          double J_12_7 = 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_8/(1.3846843902855162e-18*S_14 + 1.0);
          double J_12_8 = 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_7/(1.3846843902855162e-18*S_14 + 1.0);
          double J_12_12 = -1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14/(1.3459847134690284e-18*S_14 + 1.0);
          double J_12_14 = 1.6029099488139965e-37*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_12/pow(1.3459847134690284e-18*S_14 + 1.0, 2) - 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_12/(1.3459847134690284e-18*S_14 + 1.0) - 1.9018580488528996e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_12*log(1.3459847134690284e-18*S_14)/((1.3459847134690284e-18*S_14 + 1.0)*pow(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10)) - 3.8321461055530778e-48*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_8*S_7/pow(1.3846843902855162e-18*S_14 + 1.0, 2) + 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_8*S_7/(1.3846843902855162e-18*S_14 + 1.0) + 4.4197770694650986e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_8*S_7*log(1.3846843902855162e-18*S_14)/((1.3846843902855162e-18*S_14 + 1.0)*pow(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10));
          double J_13_6 = 1.0*jvals[1];
          double J_13_11 = -1.0*S_13*(2.1296027497121323e-32*S_14/(4.2746565719581312e-19*S_14 + 1.0) + 9.8568101265494379e-14) + 1.0*jvals[2];
          double J_13_13 = -1.0*S_11*(2.1296027497121323e-32*S_14/(4.2746565719581312e-19*S_14 + 1.0) + 9.8568101265494379e-14);
          double J_13_14 = -1.0*S_11*S_13*(-9.1033203897170818e-51*S_14/pow(4.2746565719581312e-19*S_14 + 1.0, 2) + 2.1296027497121323e-32/(4.2746565719581312e-19*S_14 + 1.0));
          double J_13_15 = 2.0*jvals[3];
          double J_15_14 = 4.7653762320694437e-32*S_16;
          double J_15_15 = -1.0*jvals[3];
          double J_15_16 = 4.7653762320694437e-32*S_14 + 1.6994829027540494e-12;
          double J_16_14 = -4.7653762320694437e-32*S_16;
          double J_16_16 = -4.7653762320694437e-32*S_14 - 1.6994829027540494e-12;
          double W_0_0 = inv_g_dt;
          double W_1_1 = inv_g_dt;
          double W_2_2 = inv_g_dt;
          double W_3_3 = inv_g_dt;
          double W_4_4 = inv_g_dt - J_4_4;
          double W_4_6 = -J_4_6;
          double W_4_7 = -J_4_7;
          double W_4_8 = -J_4_8;
          double W_4_9 = -J_4_9;
          double W_5_5 = inv_g_dt;
          double W_6_6 = inv_g_dt - J_6_6;
          double W_7_4 = -J_7_4;
          double W_7_7 = inv_g_dt - J_7_7;
          double W_7_8 = -J_7_8;
          double W_7_9 = -J_7_9;
          double W_7_11 = -J_7_11;
          double W_7_12 = -J_7_12;
          double W_7_13 = -J_7_13;
          double W_7_14 = -J_7_14;
          double W_8_4 = -J_8_4;
          double W_8_7 = -J_8_7;
          double W_8_8 = inv_g_dt - J_8_8;
          double W_8_9 = -J_8_9;
          double W_8_11 = -J_8_11;
          double W_8_12 = -J_8_12;
          double W_8_14 = -J_8_14;
          double W_9_4 = -J_9_4;
          double W_9_5 = -J_9_5;
          double W_9_8 = -J_9_8;
          double W_9_9 = inv_g_dt - J_9_9;
          double W_9_10 = -J_9_10;
          double W_9_14 = -J_9_14;
          double W_10_5 = -J_10_5;
          double W_10_8 = -J_10_8;
          double W_10_9 = -J_10_9;
          double W_10_10 = inv_g_dt - J_10_10;
          double W_10_14 = -J_10_14;
          double W_11_11 = inv_g_dt - J_11_11;
          double W_11_13 = -J_11_13;
          double W_11_14 = -J_11_14;
          double W_12_7 = -J_12_7;
          double W_12_8 = -J_12_8;
          double W_12_12 = inv_g_dt - J_12_12;
          double W_12_14 = -J_12_14;
          double W_13_6 = -J_13_6;
          double W_13_11 = -J_13_11;
          double W_13_13 = inv_g_dt - J_13_13;
          double W_13_14 = -J_13_14;
          double W_13_15 = -J_13_15;
          double W_14_14 = inv_g_dt;
          double W_15_14 = -J_15_14;
          double W_15_15 = inv_g_dt - J_15_15;
          double W_15_16 = -J_15_16;
          double W_16_14 = -J_16_14;
          double W_16_16 = inv_g_dt - J_16_16;

          // Symbolic Doolittle Sparse LU Factorization
          // Block 0: species [N2, H2O, HNO4, NO, O2, O3]
          double U_0_0 = W_0_0;
          // Block 1: species [M]
          double U_1_1 = W_1_1;
          double U_2_2 = W_2_2;
          double U_3_3 = W_3_3;
          double U_4_4 = W_4_4;
          double U_4_6 = W_4_6;
          double U_4_7 = W_4_7;
          double U_4_8 = W_4_8;
          double U_4_9 = W_4_9;
          // Block 3: species [NO3, O3P]
          double L_7_4 = (W_7_4) / U_4_4;
          // Block 4: species [NO2]
          double L_8_4 = (W_8_4) / U_4_4;
          double L_9_4 = (W_9_4) / U_4_4;
          double U_5_5 = W_5_5;
          double L_9_5 = (W_9_5) / U_5_5;
          double L_10_5 = (W_10_5) / U_5_5;
          // Block 2: species [HONO]
          double U_6_6 = W_6_6;
          double L_7_6 = (0.0 - L_7_4 * U_4_6) / U_6_6;
          double L_8_6 = (0.0 - L_8_4 * U_4_6) / U_6_6;
          double L_9_6 = (0.0 - L_9_4 * U_4_6) / U_6_6;
          // Block 7: species [OH]
          double L_13_6 = (W_13_6) / U_6_6;
          double U_7_7 = W_7_7 - L_7_4 * U_4_7;
          double U_7_8 = W_7_8 - L_7_4 * U_4_8;
          double U_7_9 = W_7_9 - L_7_4 * U_4_9;
          double U_7_11 = W_7_11;
          double U_7_12 = W_7_12;
          double U_7_13 = W_7_13;
          double U_7_14 = W_7_14;
          double L_8_7 = (W_8_7 - L_8_4 * U_4_7) / U_7_7;
          double L_9_7 = (0.0 - L_9_4 * U_4_7) / U_7_7;
          // Block 6: species [N2O5]
          double L_12_7 = (W_12_7) / U_7_7;
          double U_8_8 = W_8_8 - L_8_4 * U_4_8 - L_8_7 * U_7_8;
          double U_8_9 = W_8_9 - L_8_4 * U_4_9 - L_8_7 * U_7_9;
          double U_8_11 = W_8_11 - L_8_7 * U_7_11;
          double U_8_12 = W_8_12 - L_8_7 * U_7_12;
          double U_8_13 = 0.0 - L_8_7 * U_7_13;
          double U_8_14 = W_8_14 - L_8_7 * U_7_14;
          double L_9_8 = (W_9_8 - L_9_4 * U_4_8 - L_9_7 * U_7_8) / U_8_8;
          double L_10_8 = (W_10_8) / U_8_8;
          double L_12_8 = (W_12_8 - L_12_7 * U_7_8) / U_8_8;
          double U_9_9 = W_9_9 - L_9_4 * U_4_9 - L_9_7 * U_7_9 - L_9_8 * U_8_9;
          double U_9_10 = W_9_10;
          double U_9_11 = 0.0 - L_9_7 * U_7_11 - L_9_8 * U_8_11;
          double U_9_12 = 0.0 - L_9_7 * U_7_12 - L_9_8 * U_8_12;
          double U_9_13 = 0.0 - L_9_7 * U_7_13 - L_9_8 * U_8_13;
          double U_9_14 = W_9_14 - L_9_7 * U_7_14 - L_9_8 * U_8_14;
          double L_10_9 = (W_10_9 - L_10_8 * U_8_9) / U_9_9;
          double L_12_9 = (0.0 - L_12_7 * U_7_9 - L_12_8 * U_8_9) / U_9_9;
          double U_10_10 = W_10_10 - L_10_9 * U_9_10;
          double U_10_11 = 0.0 - L_10_8 * U_8_11 - L_10_9 * U_9_11;
          double U_10_12 = 0.0 - L_10_8 * U_8_12 - L_10_9 * U_9_12;
          double U_10_13 = 0.0 - L_10_8 * U_8_13 - L_10_9 * U_9_13;
          double U_10_14 = W_10_14 - L_10_8 * U_8_14 - L_10_9 * U_9_14;
          double L_12_10 = (0.0 - L_12_9 * U_9_10) / U_10_10;
          // Block 5: species [HNO3]
          double U_11_11 = W_11_11;
          double U_11_13 = W_11_13;
          double U_11_14 = W_11_14;
          double L_12_11 = (0.0 - L_12_7 * U_7_11 - L_12_8 * U_8_11 - L_12_9 * U_9_11 - L_12_10 * U_10_11) / U_11_11;
          double L_13_11 = (W_13_11) / U_11_11;
          double U_12_12 = W_12_12 - L_12_7 * U_7_12 - L_12_8 * U_8_12 - L_12_9 * U_9_12 - L_12_10 * U_10_12;
          double U_12_13 = 0.0 - L_12_7 * U_7_13 - L_12_8 * U_8_13 - L_12_9 * U_9_13 - L_12_10 * U_10_13 - L_12_11 * U_11_13;
          double U_12_14 = W_12_14 - L_12_7 * U_7_14 - L_12_8 * U_8_14 - L_12_9 * U_9_14 - L_12_10 * U_10_14 - L_12_11 * U_11_14;
          double U_13_13 = W_13_13 - L_13_11 * U_11_13;
          double U_13_14 = W_13_14 - L_13_11 * U_11_14;
          double U_13_15 = W_13_15;
          // Block 8: species [AIR]
          double U_14_14 = W_14_14;
          // Block 9: species [H2O2]
          double L_15_14 = (W_15_14) / U_14_14;
          // Block 10: species [HO2]
          double L_16_14 = (W_16_14) / U_14_14;
          double U_15_15 = W_15_15;
          double U_15_16 = W_15_16;
          double U_16_16 = W_16_16;


          // --- Stage 1 ---
          // Rate evaluation F1 at S
          double F1_0 = 0.0;
          double F1_1 = 0.0;
          double F1_2 = 0.0;
          double F1_3 = 0.0;
          double F1_4 = 1.0*S_6*jvals[1] - 2.5972503599796067e-11*S_4*S_7 - 1.8706578944791917e-14*S_4*S_9 + 1.0*S_8*jvals[0];
          double F1_5 = 0.0;
          double F1_6 = -1.0*S_6*jvals[1];
          double F1_7 = 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_12/(1.3459847134690284e-18*S_14 + 1.0) - 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_8*S_7/(1.3846843902855162e-18*S_14 + 1.0) + 1.0*S_11*S_13*(2.1296027497121323e-32*S_14/(4.2746565719581312e-19*S_14 + 1.0) + 9.8568101265494379e-14) - 2.5972503599796067e-11*S_4*S_7 + 3.7190909690468382e-17*S_8*S_9;
          double F1_8 = 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_12/(1.3459847134690284e-18*S_14 + 1.0) - 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_8*S_7/(1.3846843902855162e-18*S_14 + 1.0) + 1.0*S_11*jvals[2] + 5.1945007199592134e-11*S_4*S_7 + 1.8706578944791917e-14*S_4*S_9 - 3.7190909690468382e-17*S_8*S_9 - 1.0*S_8*jvals[0];
          double F1_9 = 5.6800000000000035e-34*S_14*S_5*S_10 - 1.8706578944791917e-14*S_4*S_9 - 3.7190909690468382e-17*S_8*S_9 - 8.3355554445074843e-15*S_9*S_10;
          double F1_10 = -5.6800000000000035e-34*S_14*S_5*S_10 + 1.0*S_8*jvals[0] - 8.3355554445074843e-15*S_9*S_10;
          double F1_11 = -1.0*S_11*S_13*(2.1296027497121323e-32*S_14/(4.2746565719581312e-19*S_14 + 1.0) + 9.8568101265494379e-14) - 1.0*S_11*jvals[2];
          double F1_12 = -1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_12/(1.3459847134690284e-18*S_14 + 1.0) + 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_8*S_7/(1.3846843902855162e-18*S_14 + 1.0);
          double F1_13 = 2.0*S_15*jvals[3] - 1.0*S_11*S_13*(2.1296027497121323e-32*S_14/(4.2746565719581312e-19*S_14 + 1.0) + 9.8568101265494379e-14) + 1.0*S_11*jvals[2] + 1.0*S_6*jvals[1];
          double F1_14 = 0.0;
          double F1_15 = -1.0*S_15*jvals[3] + 1.0*S_16*(4.7653762320694437e-32*S_14 + 1.6994829027540494e-12);
          double F1_16 = -1.0*S_16*(4.7653762320694437e-32*S_14 + 1.6994829027540494e-12);
          // Block 0: K1 forward sub [N2, H2O, HNO4, NO, O2, O3]
          double y1_0 = F1_0;
          // Block 1: K1 forward sub [M]
          double y1_1 = F1_1;
          double y1_2 = F1_2;
          double y1_3 = F1_3;
          double y1_4 = F1_4;
          double y1_5 = F1_5;
          // Block 2: K1 forward sub [HONO]
          double y1_6 = F1_6;
          // Block 3: K1 forward sub [NO3, O3P]
          double y1_7 = F1_7 - L_7_4 * y1_4 - L_7_6 * y1_6;
          // Block 4: K1 forward sub [NO2]
          double y1_8 = F1_8 - L_8_4 * y1_4 - L_8_6 * y1_6 - L_8_7 * y1_7;
          double y1_9 = F1_9 - L_9_4 * y1_4 - L_9_5 * y1_5 - L_9_6 * y1_6 - L_9_7 * y1_7 - L_9_8 * y1_8;
          double y1_10 = F1_10 - L_10_5 * y1_5 - L_10_8 * y1_8 - L_10_9 * y1_9;
          // Block 5: K1 forward sub [HNO3]
          double y1_11 = F1_11;
          // Block 6: K1 forward sub [N2O5]
          double y1_12 = F1_12 - L_12_7 * y1_7 - L_12_8 * y1_8 - L_12_9 * y1_9 - L_12_10 * y1_10 - L_12_11 * y1_11;
          // Block 7: K1 forward sub [OH]
          double y1_13 = F1_13 - L_13_6 * y1_6 - L_13_11 * y1_11;
          // Block 8: K1 forward sub [AIR]
          double y1_14 = F1_14;
          // Block 9: K1 forward sub [H2O2]
          double y1_15 = F1_15 - L_15_14 * y1_14;
          // Block 10: K1 forward sub [HO2]
          double y1_16 = F1_16 - L_16_14 * y1_14;
          // Block 10: K1 backward sub [HO2]
          double K1_16 = y1_16 / U_16_16;
          // Block 9: K1 backward sub [H2O2]
          double K1_15 = (y1_15 - U_15_16 * K1_16) / U_15_15;
          // Block 8: K1 backward sub [AIR]
          double K1_14 = y1_14 / U_14_14;
          // Block 7: K1 backward sub [OH]
          double K1_13 = (y1_13 - U_13_14 * K1_14 - U_13_15 * K1_15) / U_13_13;
          // Block 6: K1 backward sub [N2O5]
          double K1_12 = (y1_12 - U_12_13 * K1_13 - U_12_14 * K1_14) / U_12_12;
          // Block 5: K1 backward sub [HNO3]
          double K1_11 = (y1_11 - U_11_13 * K1_13 - U_11_14 * K1_14) / U_11_11;
          // Block 3: K1 backward sub [NO3, O3P]
          double K1_10 = (y1_10 - U_10_11 * K1_11 - U_10_12 * K1_12 - U_10_13 * K1_13 - U_10_14 * K1_14) / U_10_10;
          // Block 0: K1 backward sub [N2, H2O, HNO4, NO, O2, O3]
          double K1_9 = (y1_9 - U_9_10 * K1_10 - U_9_11 * K1_11 - U_9_12 * K1_12 - U_9_13 * K1_13 - U_9_14 * K1_14) / U_9_9;
          // Block 4: K1 backward sub [NO2]
          double K1_8 = (y1_8 - U_8_9 * K1_9 - U_8_11 * K1_11 - U_8_12 * K1_12 - U_8_13 * K1_13 - U_8_14 * K1_14) / U_8_8;
          double K1_7 = (y1_7 - U_7_8 * K1_8 - U_7_9 * K1_9 - U_7_11 * K1_11 - U_7_12 * K1_12 - U_7_13 * K1_13 - U_7_14 * K1_14) / U_7_7;
          // Block 2: K1 backward sub [HONO]
          double K1_6 = y1_6 / U_6_6;
          double K1_5 = y1_5 / U_5_5;
          double K1_4 = (y1_4 - U_4_6 * K1_6 - U_4_7 * K1_7 - U_4_8 * K1_8 - U_4_9 * K1_9) / U_4_4;
          double K1_3 = y1_3 / U_3_3;
          double K1_2 = y1_2 / U_2_2;
          // Block 1: K1 backward sub [M]
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
          // Rate evaluation F2 at Y2
          double F2_0 = 0.0;
          double F2_1 = 0.0;
          double F2_2 = 0.0;
          double F2_3 = 0.0;
          double F2_4 = 1.0*Y2_6*jvals[1] - 2.5972503599796067e-11*Y2_4*Y2_7 - 1.8706578944791917e-14*Y2_4*Y2_9 + 1.0*Y2_8*jvals[0];
          double F2_5 = 0.0;
          double F2_6 = -1.0*Y2_6*jvals[1];
          double F2_7 = 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*Y2_14), 2)/(M_LN10 * M_LN10) + 1.0))*Y2_14*Y2_12/(1.3459847134690284e-18*Y2_14 + 1.0) - 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*Y2_14), 2)/(M_LN10 * M_LN10) + 1.0))*Y2_14*Y2_8*Y2_7/(1.3846843902855162e-18*Y2_14 + 1.0) + 1.0*Y2_11*Y2_13*(2.1296027497121323e-32*Y2_14/(4.2746565719581312e-19*Y2_14 + 1.0) + 9.8568101265494379e-14) - 2.5972503599796067e-11*Y2_4*Y2_7 + 3.7190909690468382e-17*Y2_8*Y2_9;
          double F2_8 = 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*Y2_14), 2)/(M_LN10 * M_LN10) + 1.0))*Y2_14*Y2_12/(1.3459847134690284e-18*Y2_14 + 1.0) - 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*Y2_14), 2)/(M_LN10 * M_LN10) + 1.0))*Y2_14*Y2_8*Y2_7/(1.3846843902855162e-18*Y2_14 + 1.0) + 1.0*Y2_11*jvals[2] + 5.1945007199592134e-11*Y2_4*Y2_7 + 1.8706578944791917e-14*Y2_4*Y2_9 - 3.7190909690468382e-17*Y2_8*Y2_9 - 1.0*Y2_8*jvals[0];
          double F2_9 = 5.6800000000000035e-34*Y2_14*Y2_5*Y2_10 - 1.8706578944791917e-14*Y2_4*Y2_9 - 3.7190909690468382e-17*Y2_8*Y2_9 - 8.3355554445074843e-15*Y2_9*Y2_10;
          double F2_10 = -5.6800000000000035e-34*Y2_14*Y2_5*Y2_10 + 1.0*Y2_8*jvals[0] - 8.3355554445074843e-15*Y2_9*Y2_10;
          double F2_11 = -1.0*Y2_11*Y2_13*(2.1296027497121323e-32*Y2_14/(4.2746565719581312e-19*Y2_14 + 1.0) + 9.8568101265494379e-14) - 1.0*Y2_11*jvals[2];
          double F2_12 = -1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*Y2_14), 2)/(M_LN10 * M_LN10) + 1.0))*Y2_14*Y2_12/(1.3459847134690284e-18*Y2_14 + 1.0) + 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*Y2_14), 2)/(M_LN10 * M_LN10) + 1.0))*Y2_14*Y2_8*Y2_7/(1.3846843902855162e-18*Y2_14 + 1.0);
          double F2_13 = 2.0*Y2_15*jvals[3] - 1.0*Y2_11*Y2_13*(2.1296027497121323e-32*Y2_14/(4.2746565719581312e-19*Y2_14 + 1.0) + 9.8568101265494379e-14) + 1.0*Y2_11*jvals[2] + 1.0*Y2_6*jvals[1];
          double F2_14 = 0.0;
          double F2_15 = -1.0*Y2_15*jvals[3] + 1.0*Y2_16*(4.7653762320694437e-32*Y2_14 + 1.6994829027540494e-12);
          double F2_16 = -1.0*Y2_16*(4.7653762320694437e-32*Y2_14 + 1.6994829027540494e-12);
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
          // Block 0: K2 forward sub [N2, H2O, HNO4, NO, O2, O3]
          double y2_0 = rhs2_0;
          // Block 1: K2 forward sub [M]
          double y2_1 = rhs2_1;
          double y2_2 = rhs2_2;
          double y2_3 = rhs2_3;
          double y2_4 = rhs2_4;
          double y2_5 = rhs2_5;
          // Block 2: K2 forward sub [HONO]
          double y2_6 = rhs2_6;
          // Block 3: K2 forward sub [NO3, O3P]
          double y2_7 = rhs2_7 - L_7_4 * y2_4 - L_7_6 * y2_6;
          // Block 4: K2 forward sub [NO2]
          double y2_8 = rhs2_8 - L_8_4 * y2_4 - L_8_6 * y2_6 - L_8_7 * y2_7;
          double y2_9 = rhs2_9 - L_9_4 * y2_4 - L_9_5 * y2_5 - L_9_6 * y2_6 - L_9_7 * y2_7 - L_9_8 * y2_8;
          double y2_10 = rhs2_10 - L_10_5 * y2_5 - L_10_8 * y2_8 - L_10_9 * y2_9;
          // Block 5: K2 forward sub [HNO3]
          double y2_11 = rhs2_11;
          // Block 6: K2 forward sub [N2O5]
          double y2_12 = rhs2_12 - L_12_7 * y2_7 - L_12_8 * y2_8 - L_12_9 * y2_9 - L_12_10 * y2_10 - L_12_11 * y2_11;
          // Block 7: K2 forward sub [OH]
          double y2_13 = rhs2_13 - L_13_6 * y2_6 - L_13_11 * y2_11;
          // Block 8: K2 forward sub [AIR]
          double y2_14 = rhs2_14;
          // Block 9: K2 forward sub [H2O2]
          double y2_15 = rhs2_15 - L_15_14 * y2_14;
          // Block 10: K2 forward sub [HO2]
          double y2_16 = rhs2_16 - L_16_14 * y2_14;
          // Block 10: K2 backward sub [HO2]
          double K2_16 = y2_16 / U_16_16;
          // Block 9: K2 backward sub [H2O2]
          double K2_15 = (y2_15 - U_15_16 * K2_16) / U_15_15;
          // Block 8: K2 backward sub [AIR]
          double K2_14 = y2_14 / U_14_14;
          // Block 7: K2 backward sub [OH]
          double K2_13 = (y2_13 - U_13_14 * K2_14 - U_13_15 * K2_15) / U_13_13;
          // Block 6: K2 backward sub [N2O5]
          double K2_12 = (y2_12 - U_12_13 * K2_13 - U_12_14 * K2_14) / U_12_12;
          // Block 5: K2 backward sub [HNO3]
          double K2_11 = (y2_11 - U_11_13 * K2_13 - U_11_14 * K2_14) / U_11_11;
          // Block 3: K2 backward sub [NO3, O3P]
          double K2_10 = (y2_10 - U_10_11 * K2_11 - U_10_12 * K2_12 - U_10_13 * K2_13 - U_10_14 * K2_14) / U_10_10;
          // Block 0: K2 backward sub [N2, H2O, HNO4, NO, O2, O3]
          double K2_9 = (y2_9 - U_9_10 * K2_10 - U_9_11 * K2_11 - U_9_12 * K2_12 - U_9_13 * K2_13 - U_9_14 * K2_14) / U_9_9;
          // Block 4: K2 backward sub [NO2]
          double K2_8 = (y2_8 - U_8_9 * K2_9 - U_8_11 * K2_11 - U_8_12 * K2_12 - U_8_13 * K2_13 - U_8_14 * K2_14) / U_8_8;
          double K2_7 = (y2_7 - U_7_8 * K2_8 - U_7_9 * K2_9 - U_7_11 * K2_11 - U_7_12 * K2_12 - U_7_13 * K2_13 - U_7_14 * K2_14) / U_7_7;
          // Block 2: K2 backward sub [HONO]
          double K2_6 = y2_6 / U_6_6;
          double K2_5 = y2_5 / U_5_5;
          double K2_4 = (y2_4 - U_4_6 * K2_6 - U_4_7 * K2_7 - U_4_8 * K2_8 - U_4_9 * K2_9) / U_4_4;
          double K2_3 = y2_3 / U_3_3;
          double K2_2 = y2_2 / U_2_2;
          // Block 1: K2 backward sub [M]
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
          // Block 0: K3 forward sub [N2, H2O, HNO4, NO, O2, O3]
          double y3_0 = rhs3_0;
          // Block 1: K3 forward sub [M]
          double y3_1 = rhs3_1;
          double y3_2 = rhs3_2;
          double y3_3 = rhs3_3;
          double y3_4 = rhs3_4;
          double y3_5 = rhs3_5;
          // Block 2: K3 forward sub [HONO]
          double y3_6 = rhs3_6;
          // Block 3: K3 forward sub [NO3, O3P]
          double y3_7 = rhs3_7 - L_7_4 * y3_4 - L_7_6 * y3_6;
          // Block 4: K3 forward sub [NO2]
          double y3_8 = rhs3_8 - L_8_4 * y3_4 - L_8_6 * y3_6 - L_8_7 * y3_7;
          double y3_9 = rhs3_9 - L_9_4 * y3_4 - L_9_5 * y3_5 - L_9_6 * y3_6 - L_9_7 * y3_7 - L_9_8 * y3_8;
          double y3_10 = rhs3_10 - L_10_5 * y3_5 - L_10_8 * y3_8 - L_10_9 * y3_9;
          // Block 5: K3 forward sub [HNO3]
          double y3_11 = rhs3_11;
          // Block 6: K3 forward sub [N2O5]
          double y3_12 = rhs3_12 - L_12_7 * y3_7 - L_12_8 * y3_8 - L_12_9 * y3_9 - L_12_10 * y3_10 - L_12_11 * y3_11;
          // Block 7: K3 forward sub [OH]
          double y3_13 = rhs3_13 - L_13_6 * y3_6 - L_13_11 * y3_11;
          // Block 8: K3 forward sub [AIR]
          double y3_14 = rhs3_14;
          // Block 9: K3 forward sub [H2O2]
          double y3_15 = rhs3_15 - L_15_14 * y3_14;
          // Block 10: K3 forward sub [HO2]
          double y3_16 = rhs3_16 - L_16_14 * y3_14;
          // Block 10: K3 backward sub [HO2]
          double K3_16 = y3_16 / U_16_16;
          // Block 9: K3 backward sub [H2O2]
          double K3_15 = (y3_15 - U_15_16 * K3_16) / U_15_15;
          // Block 8: K3 backward sub [AIR]
          double K3_14 = y3_14 / U_14_14;
          // Block 7: K3 backward sub [OH]
          double K3_13 = (y3_13 - U_13_14 * K3_14 - U_13_15 * K3_15) / U_13_13;
          // Block 6: K3 backward sub [N2O5]
          double K3_12 = (y3_12 - U_12_13 * K3_13 - U_12_14 * K3_14) / U_12_12;
          // Block 5: K3 backward sub [HNO3]
          double K3_11 = (y3_11 - U_11_13 * K3_13 - U_11_14 * K3_14) / U_11_11;
          // Block 3: K3 backward sub [NO3, O3P]
          double K3_10 = (y3_10 - U_10_11 * K3_11 - U_10_12 * K3_12 - U_10_13 * K3_13 - U_10_14 * K3_14) / U_10_10;
          // Block 0: K3 backward sub [N2, H2O, HNO4, NO, O2, O3]
          double K3_9 = (y3_9 - U_9_10 * K3_10 - U_9_11 * K3_11 - U_9_12 * K3_12 - U_9_13 * K3_13 - U_9_14 * K3_14) / U_9_9;
          // Block 4: K3 backward sub [NO2]
          double K3_8 = (y3_8 - U_8_9 * K3_9 - U_8_11 * K3_11 - U_8_12 * K3_12 - U_8_13 * K3_13 - U_8_14 * K3_14) / U_8_8;
          double K3_7 = (y3_7 - U_7_8 * K3_8 - U_7_9 * K3_9 - U_7_11 * K3_11 - U_7_12 * K3_12 - U_7_13 * K3_13 - U_7_14 * K3_14) / U_7_7;
          // Block 2: K3 backward sub [HONO]
          double K3_6 = y3_6 / U_6_6;
          double K3_5 = y3_5 / U_5_5;
          double K3_4 = (y3_4 - U_4_6 * K3_6 - U_4_7 * K3_7 - U_4_8 * K3_8 - U_4_9 * K3_9) / U_4_4;
          double K3_3 = y3_3 / U_3_3;
          double K3_2 = y3_2 / U_2_2;
          // Block 1: K3 backward sub [M]
          double K3_1 = y3_1 / U_1_1;
          double K3_0 = y3_0 / U_0_0;

          // --- Solution update and error estimation ---
          double err_norm_sq = 0.0;
          {
              double Ynew_i = S_0 + K1_0 + 6.1697947043828245 * K2_0 + -0.42772256543218573 * K3_0;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(16)), Kokkos::fabs(Ynew_i));
              double sci = atol[0] + rtol[0] * ymax;
              double yerr_i = 0.5 * K1_0 + -2.9079558716805471 * K2_0 + 0.22354069897811571 * K3_0;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_1 + K1_1 + 6.1697947043828245 * K2_1 + -0.42772256543218573 * K3_1;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(15)), Kokkos::fabs(Ynew_i));
              double sci = atol[1] + rtol[1] * ymax;
              double yerr_i = 0.5 * K1_1 + -2.9079558716805471 * K2_1 + 0.22354069897811571 * K3_1;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_2 + K1_2 + 6.1697947043828245 * K2_2 + -0.42772256543218573 * K3_2;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(14)), Kokkos::fabs(Ynew_i));
              double sci = atol[2] + rtol[2] * ymax;
              double yerr_i = 0.5 * K1_2 + -2.9079558716805471 * K2_2 + 0.22354069897811571 * K3_2;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_3 + K1_3 + 6.1697947043828245 * K2_3 + -0.42772256543218573 * K3_3;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(8)), Kokkos::fabs(Ynew_i));
              double sci = atol[3] + rtol[3] * ymax;
              double yerr_i = 0.5 * K1_3 + -2.9079558716805471 * K2_3 + 0.22354069897811571 * K3_3;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_4 + K1_4 + 6.1697947043828245 * K2_4 + -0.42772256543218573 * K3_4;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(2)), Kokkos::fabs(Ynew_i));
              double sci = atol[4] + rtol[4] * ymax;
              double yerr_i = 0.5 * K1_4 + -2.9079558716805471 * K2_4 + 0.22354069897811571 * K3_4;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_5 + K1_5 + 6.1697947043828245 * K2_5 + -0.42772256543218573 * K3_5;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(13)), Kokkos::fabs(Ynew_i));
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
          {
              double Ynew_i = S_7 + K1_7 + 6.1697947043828245 * K2_7 + -0.42772256543218573 * K3_7;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(4)), Kokkos::fabs(Ynew_i));
              double sci = atol[7] + rtol[7] * ymax;
              double yerr_i = 0.5 * K1_7 + -2.9079558716805471 * K2_7 + 0.22354069897811571 * K3_7;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_8 + K1_8 + 6.1697947043828245 * K2_8 + -0.42772256543218573 * K3_8;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(3)), Kokkos::fabs(Ynew_i));
              double sci = atol[8] + rtol[8] * ymax;
              double yerr_i = 0.5 * K1_8 + -2.9079558716805471 * K2_8 + 0.22354069897811571 * K3_8;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_9 + K1_9 + 6.1697947043828245 * K2_9 + -0.42772256543218573 * K3_9;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(0)), Kokkos::fabs(Ynew_i));
              double sci = atol[9] + rtol[9] * ymax;
              double yerr_i = 0.5 * K1_9 + -2.9079558716805471 * K2_9 + 0.22354069897811571 * K3_9;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_10 + K1_10 + 6.1697947043828245 * K2_10 + -0.42772256543218573 * K3_10;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(9)), Kokkos::fabs(Ynew_i));
              double sci = atol[10] + rtol[10] * ymax;
              double yerr_i = 0.5 * K1_10 + -2.9079558716805471 * K2_10 + 0.22354069897811571 * K3_10;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_11 + K1_11 + 6.1697947043828245 * K2_11 + -0.42772256543218573 * K3_11;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(7)), Kokkos::fabs(Ynew_i));
              double sci = atol[11] + rtol[11] * ymax;
              double yerr_i = 0.5 * K1_11 + -2.9079558716805471 * K2_11 + 0.22354069897811571 * K3_11;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_12 + K1_12 + 6.1697947043828245 * K2_12 + -0.42772256543218573 * K3_12;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(5)), Kokkos::fabs(Ynew_i));
              double sci = atol[12] + rtol[12] * ymax;
              double yerr_i = 0.5 * K1_12 + -2.9079558716805471 * K2_12 + 0.22354069897811571 * K3_12;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_13 + K1_13 + 6.1697947043828245 * K2_13 + -0.42772256543218573 * K3_13;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(10)), Kokkos::fabs(Ynew_i));
              double sci = atol[13] + rtol[13] * ymax;
              double yerr_i = 0.5 * K1_13 + -2.9079558716805471 * K2_13 + 0.22354069897811571 * K3_13;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_14 + K1_14 + 6.1697947043828245 * K2_14 + -0.42772256543218573 * K3_14;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(12)), Kokkos::fabs(Ynew_i));
              double sci = atol[14] + rtol[14] * ymax;
              double yerr_i = 0.5 * K1_14 + -2.9079558716805471 * K2_14 + 0.22354069897811571 * K3_14;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_15 + K1_15 + 6.1697947043828245 * K2_15 + -0.42772256543218573 * K3_15;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(1)), Kokkos::fabs(Ynew_i));
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
          double err_norm = Kokkos::sqrt(err_norm_sq / 17);
          err_norm = Kokkos::fmax(err_norm, 1.0e-10);

          // Step Size Control (order 3: exponent = 1/3 = 0.33333333333333331)
          double factor = safety / Kokkos::cbrt(err_norm);
          factor = Kokkos::fmax(min_shrink, Kokkos::fmin(factor, max_growth));

          if (err_norm <= 1.0) {
              state(16) += K1_0 + 6.1697947043828245 * K2_0 + -0.42772256543218573 * K3_0;
              state(15) += K1_1 + 6.1697947043828245 * K2_1 + -0.42772256543218573 * K3_1;
              state(14) += K1_2 + 6.1697947043828245 * K2_2 + -0.42772256543218573 * K3_2;
              state(8) += K1_3 + 6.1697947043828245 * K2_3 + -0.42772256543218573 * K3_3;
              state(2) += K1_4 + 6.1697947043828245 * K2_4 + -0.42772256543218573 * K3_4;
              state(13) += K1_5 + 6.1697947043828245 * K2_5 + -0.42772256543218573 * K3_5;
              state(6) += K1_6 + 6.1697947043828245 * K2_6 + -0.42772256543218573 * K3_6;
              state(4) += K1_7 + 6.1697947043828245 * K2_7 + -0.42772256543218573 * K3_7;
              state(3) += K1_8 + 6.1697947043828245 * K2_8 + -0.42772256543218573 * K3_8;
              state(0) += K1_9 + 6.1697947043828245 * K2_9 + -0.42772256543218573 * K3_9;
              state(9) += K1_10 + 6.1697947043828245 * K2_10 + -0.42772256543218573 * K3_10;
              state(7) += K1_11 + 6.1697947043828245 * K2_11 + -0.42772256543218573 * K3_11;
              state(5) += K1_12 + 6.1697947043828245 * K2_12 + -0.42772256543218573 * K3_12;
              state(10) += K1_13 + 6.1697947043828245 * K2_13 + -0.42772256543218573 * K3_13;
              state(12) += K1_14 + 6.1697947043828245 * K2_14 + -0.42772256543218573 * K3_14;
              state(1) += K1_15 + 6.1697947043828245 * K2_15 + -0.42772256543218573 * K3_15;
              state(11) += K1_16 + 6.1697947043828245 * K2_16 + -0.42772256543218573 * K3_16;
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
          const int NUM_SPECIES = 17;
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
          active[11] = true;
          active[12] = true;
          active[13] = true;
          active[14] = true;
          active[15] = true;
          active[16] = true;

          while (t < dt_total) {
          dt = Kokkos::min(dt, dt_total - t);
          const double inv_g_dt = 1.0 / (g * dt);

          // 0. Hoist state values into scalar registers
          // NOTE: State access uses permuted species ordering
          const double S_0 = state(16);
          const double S_1 = state(15);
          const double S_2 = state(14);
          const double S_3 = state(8);
          const double S_4 = state(2);
          const double S_5 = state(13);
          const double S_6 = state(6);
          const double S_7 = state(4);
          const double S_8 = state(3);
          const double S_9 = state(0);
          const double S_10 = state(9);
          const double S_11 = state(7);
          const double S_12 = state(5);
          const double S_13 = state(10);
          const double S_14 = state(12);
          const double S_15 = state(1);
          const double S_16 = state(11);

          // 1. Stage 1 Rates (F1)
          double F1_0 = 0.0;
          double F1_1 = 0.0;
          double F1_2 = 0.0;
          double F1_3 = 0.0;
          double F1_4 = 1.0*S_6*jvals[1] - 2.5972503599796067e-11*S_4*S_7 - 1.8706578944791917e-14*S_4*S_9 + 1.0*S_8*jvals[0];
          double F1_5 = 0.0;
          double F1_6 = -1.0*S_6*jvals[1];
          double F1_7 = 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_12/(1.3459847134690284e-18*S_14 + 1.0) - 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_8*S_7/(1.3846843902855162e-18*S_14 + 1.0) + 1.0*S_11*S_13*(2.1296027497121323e-32*S_14/(4.2746565719581312e-19*S_14 + 1.0) + 9.8568101265494379e-14) - 2.5972503599796067e-11*S_4*S_7 + 3.7190909690468382e-17*S_8*S_9;
          double F1_8 = 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_12/(1.3459847134690284e-18*S_14 + 1.0) - 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_8*S_7/(1.3846843902855162e-18*S_14 + 1.0) + 1.0*S_11*jvals[2] + 5.1945007199592134e-11*S_4*S_7 + 1.8706578944791917e-14*S_4*S_9 - 3.7190909690468382e-17*S_8*S_9 - 1.0*S_8*jvals[0];
          double F1_9 = 5.6800000000000035e-34*S_14*S_5*S_10 - 1.8706578944791917e-14*S_4*S_9 - 3.7190909690468382e-17*S_8*S_9 - 8.3355554445074843e-15*S_9*S_10;
          double F1_10 = -5.6800000000000035e-34*S_14*S_5*S_10 + 1.0*S_8*jvals[0] - 8.3355554445074843e-15*S_9*S_10;
          double F1_11 = -1.0*S_11*S_13*(2.1296027497121323e-32*S_14/(4.2746565719581312e-19*S_14 + 1.0) + 9.8568101265494379e-14) - 1.0*S_11*jvals[2];
          double F1_12 = -1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_12/(1.3459847134690284e-18*S_14 + 1.0) + 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_8*S_7/(1.3846843902855162e-18*S_14 + 1.0);
          double F1_13 = 2.0*S_15*jvals[3] - 1.0*S_11*S_13*(2.1296027497121323e-32*S_14/(4.2746565719581312e-19*S_14 + 1.0) + 9.8568101265494379e-14) + 1.0*S_11*jvals[2] + 1.0*S_6*jvals[1];
          double F1_14 = 0.0;
          double F1_15 = -1.0*S_15*jvals[3] + 1.0*S_16*(4.7653762320694437e-32*S_14 + 1.6994829027540494e-12);
          double F1_16 = -1.0*S_16*(4.7653762320694437e-32*S_14 + 1.6994829027540494e-12);

          // 2. Evaluate importance and update active set
          active[0] = (Kokkos::fabs(F1_0) / (atol[0] + rtol[0] * Kokkos::fabs(state(16))) >= importance_threshold);
          active[1] = (Kokkos::fabs(F1_1) / (atol[1] + rtol[1] * Kokkos::fabs(state(15))) >= importance_threshold);
          active[2] = (Kokkos::fabs(F1_2) / (atol[2] + rtol[2] * Kokkos::fabs(state(14))) >= importance_threshold);
          active[3] = (Kokkos::fabs(F1_3) / (atol[3] + rtol[3] * Kokkos::fabs(state(8))) >= importance_threshold);
          active[4] = (Kokkos::fabs(F1_4) / (atol[4] + rtol[4] * Kokkos::fabs(state(2))) >= importance_threshold);
          active[5] = (Kokkos::fabs(F1_5) / (atol[5] + rtol[5] * Kokkos::fabs(state(13))) >= importance_threshold);
          active[6] = (Kokkos::fabs(F1_6) / (atol[6] + rtol[6] * Kokkos::fabs(state(6))) >= importance_threshold);
          active[7] = (Kokkos::fabs(F1_7) / (atol[7] + rtol[7] * Kokkos::fabs(state(4))) >= importance_threshold);
          active[8] = (Kokkos::fabs(F1_8) / (atol[8] + rtol[8] * Kokkos::fabs(state(3))) >= importance_threshold);
          active[9] = (Kokkos::fabs(F1_9) / (atol[9] + rtol[9] * Kokkos::fabs(state(0))) >= importance_threshold);
          active[10] = (Kokkos::fabs(F1_10) / (atol[10] + rtol[10] * Kokkos::fabs(state(9))) >= importance_threshold);
          active[11] = (Kokkos::fabs(F1_11) / (atol[11] + rtol[11] * Kokkos::fabs(state(7))) >= importance_threshold);
          active[12] = (Kokkos::fabs(F1_12) / (atol[12] + rtol[12] * Kokkos::fabs(state(5))) >= importance_threshold);
          active[13] = (Kokkos::fabs(F1_13) / (atol[13] + rtol[13] * Kokkos::fabs(state(10))) >= importance_threshold);
          active[14] = (Kokkos::fabs(F1_14) / (atol[14] + rtol[14] * Kokkos::fabs(state(12))) >= importance_threshold);
          active[15] = (Kokkos::fabs(F1_15) / (atol[15] + rtol[15] * Kokkos::fabs(state(1))) >= importance_threshold);
          active[16] = (Kokkos::fabs(F1_16) / (atol[16] + rtol[16] * Kokkos::fabs(state(11))) >= importance_threshold);

          // 3. Analytical Jacobian & Iteration Matrix W (identity for frozen species)
          double J_4_4 = -2.5972503599796067e-11*S_7 - 1.8706578944791917e-14*S_9;
          double J_4_6 = 1.0*jvals[1];
          double J_4_7 = -2.5972503599796067e-11*S_4;
          double J_4_8 = 1.0*jvals[0];
          double J_4_9 = -1.8706578944791917e-14*S_4;
          double J_6_6 = -1.0*jvals[1];
          double J_7_4 = -2.5972503599796067e-11*S_7;
          double J_7_7 = -2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_8/(1.3846843902855162e-18*S_14 + 1.0) - 2.5972503599796067e-11*S_4;
          double J_7_8 = -2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_7/(1.3846843902855162e-18*S_14 + 1.0) + 3.7190909690468382e-17*S_9;
          double J_7_9 = 3.7190909690468382e-17*S_8;
          double J_7_11 = 1.0*S_13*(2.1296027497121323e-32*S_14/(4.2746565719581312e-19*S_14 + 1.0) + 9.8568101265494379e-14);
          double J_7_12 = 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14/(1.3459847134690284e-18*S_14 + 1.0);
          double J_7_13 = 1.0*S_11*(2.1296027497121323e-32*S_14/(4.2746565719581312e-19*S_14 + 1.0) + 9.8568101265494379e-14);
          double J_7_14 = -1.6029099488139965e-37*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_12/pow(1.3459847134690284e-18*S_14 + 1.0, 2) + 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_12/(1.3459847134690284e-18*S_14 + 1.0) + 1.9018580488528996e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_12*log(1.3459847134690284e-18*S_14)/((1.3459847134690284e-18*S_14 + 1.0)*pow(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10)) + 3.8321461055530778e-48*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_8*S_7/pow(1.3846843902855162e-18*S_14 + 1.0, 2) - 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_8*S_7/(1.3846843902855162e-18*S_14 + 1.0) - 4.4197770694650986e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_8*S_7*log(1.3846843902855162e-18*S_14)/((1.3846843902855162e-18*S_14 + 1.0)*pow(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10)) + 1.0*S_11*S_13*(-9.1033203897170818e-51*S_14/pow(4.2746565719581312e-19*S_14 + 1.0, 2) + 2.1296027497121323e-32/(4.2746565719581312e-19*S_14 + 1.0));
          double J_8_4 = 5.1945007199592134e-11*S_7 + 1.8706578944791917e-14*S_9;
          double J_8_7 = -2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_8/(1.3846843902855162e-18*S_14 + 1.0) + 5.1945007199592134e-11*S_4;
          double J_8_8 = -2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_7/(1.3846843902855162e-18*S_14 + 1.0) - 3.7190909690468382e-17*S_9 - 1.0*jvals[0];
          double J_8_9 = 1.8706578944791917e-14*S_4 - 3.7190909690468382e-17*S_8;
          double J_8_11 = 1.0*jvals[2];
          double J_8_12 = 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14/(1.3459847134690284e-18*S_14 + 1.0);
          double J_8_14 = -1.6029099488139965e-37*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_12/pow(1.3459847134690284e-18*S_14 + 1.0, 2) + 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_12/(1.3459847134690284e-18*S_14 + 1.0) + 1.9018580488528996e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_12*log(1.3459847134690284e-18*S_14)/((1.3459847134690284e-18*S_14 + 1.0)*pow(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10)) + 3.8321461055530778e-48*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_8*S_7/pow(1.3846843902855162e-18*S_14 + 1.0, 2) - 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_8*S_7/(1.3846843902855162e-18*S_14 + 1.0) - 4.4197770694650986e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_8*S_7*log(1.3846843902855162e-18*S_14)/((1.3846843902855162e-18*S_14 + 1.0)*pow(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10));
          double J_9_4 = -1.8706578944791917e-14*S_9;
          double J_9_5 = 5.6800000000000035e-34*S_14*S_10;
          double J_9_8 = -3.7190909690468382e-17*S_9;
          double J_9_9 = -1.8706578944791917e-14*S_4 - 3.7190909690468382e-17*S_8 - 8.3355554445074843e-15*S_10;
          double J_9_10 = 5.6800000000000035e-34*S_14*S_5 - 8.3355554445074843e-15*S_9;
          double J_9_14 = 5.6800000000000035e-34*S_5*S_10;
          double J_10_5 = -5.6800000000000035e-34*S_14*S_10;
          double J_10_8 = 1.0*jvals[0];
          double J_10_9 = -8.3355554445074843e-15*S_10;
          double J_10_10 = -5.6800000000000035e-34*S_14*S_5 - 8.3355554445074843e-15*S_9;
          double J_10_14 = -5.6800000000000035e-34*S_5*S_10;
          double J_11_11 = -1.0*S_13*(2.1296027497121323e-32*S_14/(4.2746565719581312e-19*S_14 + 1.0) + 9.8568101265494379e-14) - 1.0*jvals[2];
          double J_11_13 = -1.0*S_11*(2.1296027497121323e-32*S_14/(4.2746565719581312e-19*S_14 + 1.0) + 9.8568101265494379e-14);
          double J_11_14 = -1.0*S_11*S_13*(-9.1033203897170818e-51*S_14/pow(4.2746565719581312e-19*S_14 + 1.0, 2) + 2.1296027497121323e-32/(4.2746565719581312e-19*S_14 + 1.0));
          double J_12_7 = 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_8/(1.3846843902855162e-18*S_14 + 1.0);
          double J_12_8 = 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_7/(1.3846843902855162e-18*S_14 + 1.0);
          double J_12_12 = -1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14/(1.3459847134690284e-18*S_14 + 1.0);
          double J_12_14 = 1.6029099488139965e-37*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_12/pow(1.3459847134690284e-18*S_14 + 1.0, 2) - 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_12/(1.3459847134690284e-18*S_14 + 1.0) - 1.9018580488528996e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_12*log(1.3459847134690284e-18*S_14)/((1.3459847134690284e-18*S_14 + 1.0)*pow(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10)) - 3.8321461055530778e-48*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_8*S_7/pow(1.3846843902855162e-18*S_14 + 1.0, 2) + 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_8*S_7/(1.3846843902855162e-18*S_14 + 1.0) + 4.4197770694650986e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_8*S_7*log(1.3846843902855162e-18*S_14)/((1.3846843902855162e-18*S_14 + 1.0)*pow(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10));
          double J_13_6 = 1.0*jvals[1];
          double J_13_11 = -1.0*S_13*(2.1296027497121323e-32*S_14/(4.2746565719581312e-19*S_14 + 1.0) + 9.8568101265494379e-14) + 1.0*jvals[2];
          double J_13_13 = -1.0*S_11*(2.1296027497121323e-32*S_14/(4.2746565719581312e-19*S_14 + 1.0) + 9.8568101265494379e-14);
          double J_13_14 = -1.0*S_11*S_13*(-9.1033203897170818e-51*S_14/pow(4.2746565719581312e-19*S_14 + 1.0, 2) + 2.1296027497121323e-32/(4.2746565719581312e-19*S_14 + 1.0));
          double J_13_15 = 2.0*jvals[3];
          double J_15_14 = 4.7653762320694437e-32*S_16;
          double J_15_15 = -1.0*jvals[3];
          double J_15_16 = 4.7653762320694437e-32*S_14 + 1.6994829027540494e-12;
          double J_16_14 = -4.7653762320694437e-32*S_16;
          double J_16_16 = -4.7653762320694437e-32*S_14 - 1.6994829027540494e-12;
          double W_0_0 = active[0] ? inv_g_dt : 1.0;
          double W_1_1 = active[1] ? inv_g_dt : 1.0;
          double W_2_2 = active[2] ? inv_g_dt : 1.0;
          double W_3_3 = active[3] ? inv_g_dt : 1.0;
          double W_4_4 = active[4] ? (inv_g_dt - J_4_4) : 1.0;
          double W_4_6 = (active[4] && active[6]) ? (-J_4_6) : 0.0;
          double W_4_7 = (active[4] && active[7]) ? (-J_4_7) : 0.0;
          double W_4_8 = (active[4] && active[8]) ? (-J_4_8) : 0.0;
          double W_4_9 = (active[4] && active[9]) ? (-J_4_9) : 0.0;
          double W_5_5 = active[5] ? inv_g_dt : 1.0;
          double W_6_6 = active[6] ? (inv_g_dt - J_6_6) : 1.0;
          double W_7_4 = (active[7] && active[4]) ? (-J_7_4) : 0.0;
          double W_7_7 = active[7] ? (inv_g_dt - J_7_7) : 1.0;
          double W_7_8 = (active[7] && active[8]) ? (-J_7_8) : 0.0;
          double W_7_9 = (active[7] && active[9]) ? (-J_7_9) : 0.0;
          double W_7_11 = (active[7] && active[11]) ? (-J_7_11) : 0.0;
          double W_7_12 = (active[7] && active[12]) ? (-J_7_12) : 0.0;
          double W_7_13 = (active[7] && active[13]) ? (-J_7_13) : 0.0;
          double W_7_14 = (active[7] && active[14]) ? (-J_7_14) : 0.0;
          double W_8_4 = (active[8] && active[4]) ? (-J_8_4) : 0.0;
          double W_8_7 = (active[8] && active[7]) ? (-J_8_7) : 0.0;
          double W_8_8 = active[8] ? (inv_g_dt - J_8_8) : 1.0;
          double W_8_9 = (active[8] && active[9]) ? (-J_8_9) : 0.0;
          double W_8_11 = (active[8] && active[11]) ? (-J_8_11) : 0.0;
          double W_8_12 = (active[8] && active[12]) ? (-J_8_12) : 0.0;
          double W_8_14 = (active[8] && active[14]) ? (-J_8_14) : 0.0;
          double W_9_4 = (active[9] && active[4]) ? (-J_9_4) : 0.0;
          double W_9_5 = (active[9] && active[5]) ? (-J_9_5) : 0.0;
          double W_9_8 = (active[9] && active[8]) ? (-J_9_8) : 0.0;
          double W_9_9 = active[9] ? (inv_g_dt - J_9_9) : 1.0;
          double W_9_10 = (active[9] && active[10]) ? (-J_9_10) : 0.0;
          double W_9_14 = (active[9] && active[14]) ? (-J_9_14) : 0.0;
          double W_10_5 = (active[10] && active[5]) ? (-J_10_5) : 0.0;
          double W_10_8 = (active[10] && active[8]) ? (-J_10_8) : 0.0;
          double W_10_9 = (active[10] && active[9]) ? (-J_10_9) : 0.0;
          double W_10_10 = active[10] ? (inv_g_dt - J_10_10) : 1.0;
          double W_10_14 = (active[10] && active[14]) ? (-J_10_14) : 0.0;
          double W_11_11 = active[11] ? (inv_g_dt - J_11_11) : 1.0;
          double W_11_13 = (active[11] && active[13]) ? (-J_11_13) : 0.0;
          double W_11_14 = (active[11] && active[14]) ? (-J_11_14) : 0.0;
          double W_12_7 = (active[12] && active[7]) ? (-J_12_7) : 0.0;
          double W_12_8 = (active[12] && active[8]) ? (-J_12_8) : 0.0;
          double W_12_12 = active[12] ? (inv_g_dt - J_12_12) : 1.0;
          double W_12_14 = (active[12] && active[14]) ? (-J_12_14) : 0.0;
          double W_13_6 = (active[13] && active[6]) ? (-J_13_6) : 0.0;
          double W_13_11 = (active[13] && active[11]) ? (-J_13_11) : 0.0;
          double W_13_13 = active[13] ? (inv_g_dt - J_13_13) : 1.0;
          double W_13_14 = (active[13] && active[14]) ? (-J_13_14) : 0.0;
          double W_13_15 = (active[13] && active[15]) ? (-J_13_15) : 0.0;
          double W_14_14 = active[14] ? inv_g_dt : 1.0;
          double W_15_14 = (active[15] && active[14]) ? (-J_15_14) : 0.0;
          double W_15_15 = active[15] ? (inv_g_dt - J_15_15) : 1.0;
          double W_15_16 = (active[15] && active[16]) ? (-J_15_16) : 0.0;
          double W_16_14 = (active[16] && active[14]) ? (-J_16_14) : 0.0;
          double W_16_16 = active[16] ? (inv_g_dt - J_16_16) : 1.0;

          // 4. Symbolic LU Factorization (conditional skip for frozen species)
          double U_0_0 = W_0_0;
          double U_1_1 = W_1_1;
          double U_2_2 = W_2_2;
          double U_3_3 = W_3_3;
          double U_4_4 = W_4_4;
          double U_4_6 = W_4_6;
          double U_4_7 = W_4_7;
          double U_4_8 = W_4_8;
          double U_4_9 = W_4_9;
          double L_7_4 = (W_7_4) / U_4_4;
          double L_8_4 = (W_8_4) / U_4_4;
          double L_9_4 = (W_9_4) / U_4_4;
          double U_5_5 = W_5_5;
          double L_9_5 = (W_9_5) / U_5_5;
          double L_10_5 = (W_10_5) / U_5_5;
          double U_6_6 = W_6_6;
          double L_7_6 = (0.0 - L_7_4 * U_4_6) / U_6_6;
          double L_8_6 = (0.0 - L_8_4 * U_4_6) / U_6_6;
          double L_9_6 = (0.0 - L_9_4 * U_4_6) / U_6_6;
          double L_13_6 = (W_13_6) / U_6_6;
          double U_7_7 = W_7_7 - L_7_4 * U_4_7;
          double U_7_8 = W_7_8 - L_7_4 * U_4_8;
          double U_7_9 = W_7_9 - L_7_4 * U_4_9;
          double U_7_11 = W_7_11;
          double U_7_12 = W_7_12;
          double U_7_13 = W_7_13;
          double U_7_14 = W_7_14;
          double L_8_7 = (W_8_7 - L_8_4 * U_4_7) / U_7_7;
          double L_9_7 = (0.0 - L_9_4 * U_4_7) / U_7_7;
          double L_12_7 = (W_12_7) / U_7_7;
          double U_8_8 = W_8_8 - L_8_4 * U_4_8 - L_8_7 * U_7_8;
          double U_8_9 = W_8_9 - L_8_4 * U_4_9 - L_8_7 * U_7_9;
          double U_8_11 = W_8_11 - L_8_7 * U_7_11;
          double U_8_12 = W_8_12 - L_8_7 * U_7_12;
          double U_8_13 = 0.0 - L_8_7 * U_7_13;
          double U_8_14 = W_8_14 - L_8_7 * U_7_14;
          double L_9_8 = (W_9_8 - L_9_4 * U_4_8 - L_9_7 * U_7_8) / U_8_8;
          double L_10_8 = (W_10_8) / U_8_8;
          double L_12_8 = (W_12_8 - L_12_7 * U_7_8) / U_8_8;
          double U_9_9 = W_9_9 - L_9_4 * U_4_9 - L_9_7 * U_7_9 - L_9_8 * U_8_9;
          double U_9_10 = W_9_10;
          double U_9_11 = 0.0 - L_9_7 * U_7_11 - L_9_8 * U_8_11;
          double U_9_12 = 0.0 - L_9_7 * U_7_12 - L_9_8 * U_8_12;
          double U_9_13 = 0.0 - L_9_7 * U_7_13 - L_9_8 * U_8_13;
          double U_9_14 = W_9_14 - L_9_7 * U_7_14 - L_9_8 * U_8_14;
          double L_10_9 = (W_10_9 - L_10_8 * U_8_9) / U_9_9;
          double L_12_9 = (0.0 - L_12_7 * U_7_9 - L_12_8 * U_8_9) / U_9_9;
          double U_10_10 = W_10_10 - L_10_9 * U_9_10;
          double U_10_11 = 0.0 - L_10_8 * U_8_11 - L_10_9 * U_9_11;
          double U_10_12 = 0.0 - L_10_8 * U_8_12 - L_10_9 * U_9_12;
          double U_10_13 = 0.0 - L_10_8 * U_8_13 - L_10_9 * U_9_13;
          double U_10_14 = W_10_14 - L_10_8 * U_8_14 - L_10_9 * U_9_14;
          double L_12_10 = (0.0 - L_12_9 * U_9_10) / U_10_10;
          double U_11_11 = W_11_11;
          double U_11_13 = W_11_13;
          double U_11_14 = W_11_14;
          double L_12_11 = (0.0 - L_12_7 * U_7_11 - L_12_8 * U_8_11 - L_12_9 * U_9_11 - L_12_10 * U_10_11) / U_11_11;
          double L_13_11 = (W_13_11) / U_11_11;
          double U_12_12 = W_12_12 - L_12_7 * U_7_12 - L_12_8 * U_8_12 - L_12_9 * U_9_12 - L_12_10 * U_10_12;
          double U_12_13 = 0.0 - L_12_7 * U_7_13 - L_12_8 * U_8_13 - L_12_9 * U_9_13 - L_12_10 * U_10_13 - L_12_11 * U_11_13;
          double U_12_14 = W_12_14 - L_12_7 * U_7_14 - L_12_8 * U_8_14 - L_12_9 * U_9_14 - L_12_10 * U_10_14 - L_12_11 * U_11_14;
          double U_13_13 = W_13_13 - L_13_11 * U_11_13;
          double U_13_14 = W_13_14 - L_13_11 * U_11_14;
          double U_13_15 = W_13_15;
          double U_14_14 = W_14_14;
          double L_15_14 = (W_15_14) / U_14_14;
          double L_16_14 = (W_16_14) / U_14_14;
          double U_15_15 = W_15_15;
          double U_15_16 = W_15_16;
          double U_16_16 = W_16_16;

          // --- Stage 1 ---
          // F1 already computed above (used for importance evaluation)
          // Block 0: K1 forward sub [N2, H2O, HNO4, NO, O2, O3]
          double y1_0 = active[0] ? (F1_0) : 0.0;
          // Block 1: K1 forward sub [M]
          double y1_1 = active[1] ? (F1_1) : 0.0;
          double y1_2 = active[2] ? (F1_2) : 0.0;
          double y1_3 = active[3] ? (F1_3) : 0.0;
          double y1_4 = active[4] ? (F1_4) : 0.0;
          double y1_5 = active[5] ? (F1_5) : 0.0;
          // Block 2: K1 forward sub [HONO]
          double y1_6 = active[6] ? (F1_6) : 0.0;
          // Block 3: K1 forward sub [NO3, O3P]
          double y1_7 = active[7] ? (F1_7 - L_7_4 * y1_4 - L_7_6 * y1_6) : 0.0;
          // Block 4: K1 forward sub [NO2]
          double y1_8 = active[8] ? (F1_8 - L_8_4 * y1_4 - L_8_6 * y1_6 - L_8_7 * y1_7) : 0.0;
          double y1_9 = active[9] ? (F1_9 - L_9_4 * y1_4 - L_9_5 * y1_5 - L_9_6 * y1_6 - L_9_7 * y1_7 - L_9_8 * y1_8) : 0.0;
          double y1_10 = active[10] ? (F1_10 - L_10_5 * y1_5 - L_10_8 * y1_8 - L_10_9 * y1_9) : 0.0;
          // Block 5: K1 forward sub [HNO3]
          double y1_11 = active[11] ? (F1_11) : 0.0;
          // Block 6: K1 forward sub [N2O5]
          double y1_12 = active[12] ? (F1_12 - L_12_7 * y1_7 - L_12_8 * y1_8 - L_12_9 * y1_9 - L_12_10 * y1_10 - L_12_11 * y1_11) : 0.0;
          // Block 7: K1 forward sub [OH]
          double y1_13 = active[13] ? (F1_13 - L_13_6 * y1_6 - L_13_11 * y1_11) : 0.0;
          // Block 8: K1 forward sub [AIR]
          double y1_14 = active[14] ? (F1_14) : 0.0;
          // Block 9: K1 forward sub [H2O2]
          double y1_15 = active[15] ? (F1_15 - L_15_14 * y1_14) : 0.0;
          // Block 10: K1 forward sub [HO2]
          double y1_16 = active[16] ? (F1_16 - L_16_14 * y1_14) : 0.0;

          // Block 10: K1 backward sub [HO2]
          double K1_16 = active[16] ? (y1_16 / U_16_16) : 0.0;
          // Block 9: K1 backward sub [H2O2]
          double K1_15 = active[15] ? ((y1_15 - U_15_16 * K1_16) / U_15_15) : 0.0;
          // Block 8: K1 backward sub [AIR]
          double K1_14 = active[14] ? (y1_14 / U_14_14) : 0.0;
          // Block 7: K1 backward sub [OH]
          double K1_13 = active[13] ? ((y1_13 - U_13_14 * K1_14 - U_13_15 * K1_15) / U_13_13) : 0.0;
          // Block 6: K1 backward sub [N2O5]
          double K1_12 = active[12] ? ((y1_12 - U_12_13 * K1_13 - U_12_14 * K1_14) / U_12_12) : 0.0;
          // Block 5: K1 backward sub [HNO3]
          double K1_11 = active[11] ? ((y1_11 - U_11_13 * K1_13 - U_11_14 * K1_14) / U_11_11) : 0.0;
          // Block 3: K1 backward sub [NO3, O3P]
          double K1_10 = active[10] ? ((y1_10 - U_10_11 * K1_11 - U_10_12 * K1_12 - U_10_13 * K1_13 - U_10_14 * K1_14) / U_10_10) : 0.0;
          // Block 0: K1 backward sub [N2, H2O, HNO4, NO, O2, O3]
          double K1_9 = active[9] ? ((y1_9 - U_9_10 * K1_10 - U_9_11 * K1_11 - U_9_12 * K1_12 - U_9_13 * K1_13 - U_9_14 * K1_14) / U_9_9) : 0.0;
          // Block 4: K1 backward sub [NO2]
          double K1_8 = active[8] ? ((y1_8 - U_8_9 * K1_9 - U_8_11 * K1_11 - U_8_12 * K1_12 - U_8_13 * K1_13 - U_8_14 * K1_14) / U_8_8) : 0.0;
          double K1_7 = active[7] ? ((y1_7 - U_7_8 * K1_8 - U_7_9 * K1_9 - U_7_11 * K1_11 - U_7_12 * K1_12 - U_7_13 * K1_13 - U_7_14 * K1_14) / U_7_7) : 0.0;
          // Block 2: K1 backward sub [HONO]
          double K1_6 = active[6] ? (y1_6 / U_6_6) : 0.0;
          double K1_5 = active[5] ? (y1_5 / U_5_5) : 0.0;
          double K1_4 = active[4] ? ((y1_4 - U_4_6 * K1_6 - U_4_7 * K1_7 - U_4_8 * K1_8 - U_4_9 * K1_9) / U_4_4) : 0.0;
          double K1_3 = active[3] ? (y1_3 / U_3_3) : 0.0;
          double K1_2 = active[2] ? (y1_2 / U_2_2) : 0.0;
          // Block 1: K1 backward sub [M]
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
          // Rate evaluation F2 at Y2
          double F2_0 = 0.0;
          double F2_1 = 0.0;
          double F2_2 = 0.0;
          double F2_3 = 0.0;
          double F2_4 = 1.0*Y2_6*jvals[1] - 2.5972503599796067e-11*Y2_4*Y2_7 - 1.8706578944791917e-14*Y2_4*Y2_9 + 1.0*Y2_8*jvals[0];
          double F2_5 = 0.0;
          double F2_6 = -1.0*Y2_6*jvals[1];
          double F2_7 = 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*Y2_14), 2)/(M_LN10 * M_LN10) + 1.0))*Y2_14*Y2_12/(1.3459847134690284e-18*Y2_14 + 1.0) - 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*Y2_14), 2)/(M_LN10 * M_LN10) + 1.0))*Y2_14*Y2_8*Y2_7/(1.3846843902855162e-18*Y2_14 + 1.0) + 1.0*Y2_11*Y2_13*(2.1296027497121323e-32*Y2_14/(4.2746565719581312e-19*Y2_14 + 1.0) + 9.8568101265494379e-14) - 2.5972503599796067e-11*Y2_4*Y2_7 + 3.7190909690468382e-17*Y2_8*Y2_9;
          double F2_8 = 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*Y2_14), 2)/(M_LN10 * M_LN10) + 1.0))*Y2_14*Y2_12/(1.3459847134690284e-18*Y2_14 + 1.0) - 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*Y2_14), 2)/(M_LN10 * M_LN10) + 1.0))*Y2_14*Y2_8*Y2_7/(1.3846843902855162e-18*Y2_14 + 1.0) + 1.0*Y2_11*jvals[2] + 5.1945007199592134e-11*Y2_4*Y2_7 + 1.8706578944791917e-14*Y2_4*Y2_9 - 3.7190909690468382e-17*Y2_8*Y2_9 - 1.0*Y2_8*jvals[0];
          double F2_9 = 5.6800000000000035e-34*Y2_14*Y2_5*Y2_10 - 1.8706578944791917e-14*Y2_4*Y2_9 - 3.7190909690468382e-17*Y2_8*Y2_9 - 8.3355554445074843e-15*Y2_9*Y2_10;
          double F2_10 = -5.6800000000000035e-34*Y2_14*Y2_5*Y2_10 + 1.0*Y2_8*jvals[0] - 8.3355554445074843e-15*Y2_9*Y2_10;
          double F2_11 = -1.0*Y2_11*Y2_13*(2.1296027497121323e-32*Y2_14/(4.2746565719581312e-19*Y2_14 + 1.0) + 9.8568101265494379e-14) - 1.0*Y2_11*jvals[2];
          double F2_12 = -1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*Y2_14), 2)/(M_LN10 * M_LN10) + 1.0))*Y2_14*Y2_12/(1.3459847134690284e-18*Y2_14 + 1.0) + 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*Y2_14), 2)/(M_LN10 * M_LN10) + 1.0))*Y2_14*Y2_8*Y2_7/(1.3846843902855162e-18*Y2_14 + 1.0);
          double F2_13 = 2.0*Y2_15*jvals[3] - 1.0*Y2_11*Y2_13*(2.1296027497121323e-32*Y2_14/(4.2746565719581312e-19*Y2_14 + 1.0) + 9.8568101265494379e-14) + 1.0*Y2_11*jvals[2] + 1.0*Y2_6*jvals[1];
          double F2_14 = 0.0;
          double F2_15 = -1.0*Y2_15*jvals[3] + 1.0*Y2_16*(4.7653762320694437e-32*Y2_14 + 1.6994829027540494e-12);
          double F2_16 = -1.0*Y2_16*(4.7653762320694437e-32*Y2_14 + 1.6994829027540494e-12);
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
          // Block 0: K2 forward sub [N2, H2O, HNO4, NO, O2, O3]
          double y2_0 = active[0] ? (rhs2_0) : 0.0;
          // Block 1: K2 forward sub [M]
          double y2_1 = active[1] ? (rhs2_1) : 0.0;
          double y2_2 = active[2] ? (rhs2_2) : 0.0;
          double y2_3 = active[3] ? (rhs2_3) : 0.0;
          double y2_4 = active[4] ? (rhs2_4) : 0.0;
          double y2_5 = active[5] ? (rhs2_5) : 0.0;
          // Block 2: K2 forward sub [HONO]
          double y2_6 = active[6] ? (rhs2_6) : 0.0;
          // Block 3: K2 forward sub [NO3, O3P]
          double y2_7 = active[7] ? (rhs2_7 - L_7_4 * y2_4 - L_7_6 * y2_6) : 0.0;
          // Block 4: K2 forward sub [NO2]
          double y2_8 = active[8] ? (rhs2_8 - L_8_4 * y2_4 - L_8_6 * y2_6 - L_8_7 * y2_7) : 0.0;
          double y2_9 = active[9] ? (rhs2_9 - L_9_4 * y2_4 - L_9_5 * y2_5 - L_9_6 * y2_6 - L_9_7 * y2_7 - L_9_8 * y2_8) : 0.0;
          double y2_10 = active[10] ? (rhs2_10 - L_10_5 * y2_5 - L_10_8 * y2_8 - L_10_9 * y2_9) : 0.0;
          // Block 5: K2 forward sub [HNO3]
          double y2_11 = active[11] ? (rhs2_11) : 0.0;
          // Block 6: K2 forward sub [N2O5]
          double y2_12 = active[12] ? (rhs2_12 - L_12_7 * y2_7 - L_12_8 * y2_8 - L_12_9 * y2_9 - L_12_10 * y2_10 - L_12_11 * y2_11) : 0.0;
          // Block 7: K2 forward sub [OH]
          double y2_13 = active[13] ? (rhs2_13 - L_13_6 * y2_6 - L_13_11 * y2_11) : 0.0;
          // Block 8: K2 forward sub [AIR]
          double y2_14 = active[14] ? (rhs2_14) : 0.0;
          // Block 9: K2 forward sub [H2O2]
          double y2_15 = active[15] ? (rhs2_15 - L_15_14 * y2_14) : 0.0;
          // Block 10: K2 forward sub [HO2]
          double y2_16 = active[16] ? (rhs2_16 - L_16_14 * y2_14) : 0.0;

          // Block 10: K2 backward sub [HO2]
          double K2_16 = active[16] ? (y2_16 / U_16_16) : 0.0;
          // Block 9: K2 backward sub [H2O2]
          double K2_15 = active[15] ? ((y2_15 - U_15_16 * K2_16) / U_15_15) : 0.0;
          // Block 8: K2 backward sub [AIR]
          double K2_14 = active[14] ? (y2_14 / U_14_14) : 0.0;
          // Block 7: K2 backward sub [OH]
          double K2_13 = active[13] ? ((y2_13 - U_13_14 * K2_14 - U_13_15 * K2_15) / U_13_13) : 0.0;
          // Block 6: K2 backward sub [N2O5]
          double K2_12 = active[12] ? ((y2_12 - U_12_13 * K2_13 - U_12_14 * K2_14) / U_12_12) : 0.0;
          // Block 5: K2 backward sub [HNO3]
          double K2_11 = active[11] ? ((y2_11 - U_11_13 * K2_13 - U_11_14 * K2_14) / U_11_11) : 0.0;
          // Block 3: K2 backward sub [NO3, O3P]
          double K2_10 = active[10] ? ((y2_10 - U_10_11 * K2_11 - U_10_12 * K2_12 - U_10_13 * K2_13 - U_10_14 * K2_14) / U_10_10) : 0.0;
          // Block 0: K2 backward sub [N2, H2O, HNO4, NO, O2, O3]
          double K2_9 = active[9] ? ((y2_9 - U_9_10 * K2_10 - U_9_11 * K2_11 - U_9_12 * K2_12 - U_9_13 * K2_13 - U_9_14 * K2_14) / U_9_9) : 0.0;
          // Block 4: K2 backward sub [NO2]
          double K2_8 = active[8] ? ((y2_8 - U_8_9 * K2_9 - U_8_11 * K2_11 - U_8_12 * K2_12 - U_8_13 * K2_13 - U_8_14 * K2_14) / U_8_8) : 0.0;
          double K2_7 = active[7] ? ((y2_7 - U_7_8 * K2_8 - U_7_9 * K2_9 - U_7_11 * K2_11 - U_7_12 * K2_12 - U_7_13 * K2_13 - U_7_14 * K2_14) / U_7_7) : 0.0;
          // Block 2: K2 backward sub [HONO]
          double K2_6 = active[6] ? (y2_6 / U_6_6) : 0.0;
          double K2_5 = active[5] ? (y2_5 / U_5_5) : 0.0;
          double K2_4 = active[4] ? ((y2_4 - U_4_6 * K2_6 - U_4_7 * K2_7 - U_4_8 * K2_8 - U_4_9 * K2_9) / U_4_4) : 0.0;
          double K2_3 = active[3] ? (y2_3 / U_3_3) : 0.0;
          double K2_2 = active[2] ? (y2_2 / U_2_2) : 0.0;
          // Block 1: K2 backward sub [M]
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
          // Block 0: K3 forward sub [N2, H2O, HNO4, NO, O2, O3]
          double y3_0 = active[0] ? (rhs3_0) : 0.0;
          // Block 1: K3 forward sub [M]
          double y3_1 = active[1] ? (rhs3_1) : 0.0;
          double y3_2 = active[2] ? (rhs3_2) : 0.0;
          double y3_3 = active[3] ? (rhs3_3) : 0.0;
          double y3_4 = active[4] ? (rhs3_4) : 0.0;
          double y3_5 = active[5] ? (rhs3_5) : 0.0;
          // Block 2: K3 forward sub [HONO]
          double y3_6 = active[6] ? (rhs3_6) : 0.0;
          // Block 3: K3 forward sub [NO3, O3P]
          double y3_7 = active[7] ? (rhs3_7 - L_7_4 * y3_4 - L_7_6 * y3_6) : 0.0;
          // Block 4: K3 forward sub [NO2]
          double y3_8 = active[8] ? (rhs3_8 - L_8_4 * y3_4 - L_8_6 * y3_6 - L_8_7 * y3_7) : 0.0;
          double y3_9 = active[9] ? (rhs3_9 - L_9_4 * y3_4 - L_9_5 * y3_5 - L_9_6 * y3_6 - L_9_7 * y3_7 - L_9_8 * y3_8) : 0.0;
          double y3_10 = active[10] ? (rhs3_10 - L_10_5 * y3_5 - L_10_8 * y3_8 - L_10_9 * y3_9) : 0.0;
          // Block 5: K3 forward sub [HNO3]
          double y3_11 = active[11] ? (rhs3_11) : 0.0;
          // Block 6: K3 forward sub [N2O5]
          double y3_12 = active[12] ? (rhs3_12 - L_12_7 * y3_7 - L_12_8 * y3_8 - L_12_9 * y3_9 - L_12_10 * y3_10 - L_12_11 * y3_11) : 0.0;
          // Block 7: K3 forward sub [OH]
          double y3_13 = active[13] ? (rhs3_13 - L_13_6 * y3_6 - L_13_11 * y3_11) : 0.0;
          // Block 8: K3 forward sub [AIR]
          double y3_14 = active[14] ? (rhs3_14) : 0.0;
          // Block 9: K3 forward sub [H2O2]
          double y3_15 = active[15] ? (rhs3_15 - L_15_14 * y3_14) : 0.0;
          // Block 10: K3 forward sub [HO2]
          double y3_16 = active[16] ? (rhs3_16 - L_16_14 * y3_14) : 0.0;

          // Block 10: K3 backward sub [HO2]
          double K3_16 = active[16] ? (y3_16 / U_16_16) : 0.0;
          // Block 9: K3 backward sub [H2O2]
          double K3_15 = active[15] ? ((y3_15 - U_15_16 * K3_16) / U_15_15) : 0.0;
          // Block 8: K3 backward sub [AIR]
          double K3_14 = active[14] ? (y3_14 / U_14_14) : 0.0;
          // Block 7: K3 backward sub [OH]
          double K3_13 = active[13] ? ((y3_13 - U_13_14 * K3_14 - U_13_15 * K3_15) / U_13_13) : 0.0;
          // Block 6: K3 backward sub [N2O5]
          double K3_12 = active[12] ? ((y3_12 - U_12_13 * K3_13 - U_12_14 * K3_14) / U_12_12) : 0.0;
          // Block 5: K3 backward sub [HNO3]
          double K3_11 = active[11] ? ((y3_11 - U_11_13 * K3_13 - U_11_14 * K3_14) / U_11_11) : 0.0;
          // Block 3: K3 backward sub [NO3, O3P]
          double K3_10 = active[10] ? ((y3_10 - U_10_11 * K3_11 - U_10_12 * K3_12 - U_10_13 * K3_13 - U_10_14 * K3_14) / U_10_10) : 0.0;
          // Block 0: K3 backward sub [N2, H2O, HNO4, NO, O2, O3]
          double K3_9 = active[9] ? ((y3_9 - U_9_10 * K3_10 - U_9_11 * K3_11 - U_9_12 * K3_12 - U_9_13 * K3_13 - U_9_14 * K3_14) / U_9_9) : 0.0;
          // Block 4: K3 backward sub [NO2]
          double K3_8 = active[8] ? ((y3_8 - U_8_9 * K3_9 - U_8_11 * K3_11 - U_8_12 * K3_12 - U_8_13 * K3_13 - U_8_14 * K3_14) / U_8_8) : 0.0;
          double K3_7 = active[7] ? ((y3_7 - U_7_8 * K3_8 - U_7_9 * K3_9 - U_7_11 * K3_11 - U_7_12 * K3_12 - U_7_13 * K3_13 - U_7_14 * K3_14) / U_7_7) : 0.0;
          // Block 2: K3 backward sub [HONO]
          double K3_6 = active[6] ? (y3_6 / U_6_6) : 0.0;
          double K3_5 = active[5] ? (y3_5 / U_5_5) : 0.0;
          double K3_4 = active[4] ? ((y3_4 - U_4_6 * K3_6 - U_4_7 * K3_7 - U_4_8 * K3_8 - U_4_9 * K3_9) / U_4_4) : 0.0;
          double K3_3 = active[3] ? (y3_3 / U_3_3) : 0.0;
          double K3_2 = active[2] ? (y3_2 / U_2_2) : 0.0;
          // Block 1: K3 backward sub [M]
          double K3_1 = active[1] ? (y3_1 / U_1_1) : 0.0;
          double K3_0 = active[0] ? (y3_0 / U_0_0) : 0.0;


          // --- Solution update and error estimation ---
          double err_norm_sq = 0.0;
          {
              double Ynew_i = S_0 + K1_0 + 6.1697947043828245 * K2_0 + -0.42772256543218573 * K3_0;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(16)), Kokkos::fabs(Ynew_i));
              double sci = atol[0] + rtol[0] * ymax;
              double yerr_i = 0.5 * K1_0 + -2.9079558716805471 * K2_0 + 0.22354069897811571 * K3_0;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_1 + K1_1 + 6.1697947043828245 * K2_1 + -0.42772256543218573 * K3_1;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(15)), Kokkos::fabs(Ynew_i));
              double sci = atol[1] + rtol[1] * ymax;
              double yerr_i = 0.5 * K1_1 + -2.9079558716805471 * K2_1 + 0.22354069897811571 * K3_1;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_2 + K1_2 + 6.1697947043828245 * K2_2 + -0.42772256543218573 * K3_2;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(14)), Kokkos::fabs(Ynew_i));
              double sci = atol[2] + rtol[2] * ymax;
              double yerr_i = 0.5 * K1_2 + -2.9079558716805471 * K2_2 + 0.22354069897811571 * K3_2;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_3 + K1_3 + 6.1697947043828245 * K2_3 + -0.42772256543218573 * K3_3;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(8)), Kokkos::fabs(Ynew_i));
              double sci = atol[3] + rtol[3] * ymax;
              double yerr_i = 0.5 * K1_3 + -2.9079558716805471 * K2_3 + 0.22354069897811571 * K3_3;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_4 + K1_4 + 6.1697947043828245 * K2_4 + -0.42772256543218573 * K3_4;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(2)), Kokkos::fabs(Ynew_i));
              double sci = atol[4] + rtol[4] * ymax;
              double yerr_i = 0.5 * K1_4 + -2.9079558716805471 * K2_4 + 0.22354069897811571 * K3_4;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_5 + K1_5 + 6.1697947043828245 * K2_5 + -0.42772256543218573 * K3_5;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(13)), Kokkos::fabs(Ynew_i));
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
          {
              double Ynew_i = S_7 + K1_7 + 6.1697947043828245 * K2_7 + -0.42772256543218573 * K3_7;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(4)), Kokkos::fabs(Ynew_i));
              double sci = atol[7] + rtol[7] * ymax;
              double yerr_i = 0.5 * K1_7 + -2.9079558716805471 * K2_7 + 0.22354069897811571 * K3_7;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_8 + K1_8 + 6.1697947043828245 * K2_8 + -0.42772256543218573 * K3_8;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(3)), Kokkos::fabs(Ynew_i));
              double sci = atol[8] + rtol[8] * ymax;
              double yerr_i = 0.5 * K1_8 + -2.9079558716805471 * K2_8 + 0.22354069897811571 * K3_8;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_9 + K1_9 + 6.1697947043828245 * K2_9 + -0.42772256543218573 * K3_9;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(0)), Kokkos::fabs(Ynew_i));
              double sci = atol[9] + rtol[9] * ymax;
              double yerr_i = 0.5 * K1_9 + -2.9079558716805471 * K2_9 + 0.22354069897811571 * K3_9;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_10 + K1_10 + 6.1697947043828245 * K2_10 + -0.42772256543218573 * K3_10;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(9)), Kokkos::fabs(Ynew_i));
              double sci = atol[10] + rtol[10] * ymax;
              double yerr_i = 0.5 * K1_10 + -2.9079558716805471 * K2_10 + 0.22354069897811571 * K3_10;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_11 + K1_11 + 6.1697947043828245 * K2_11 + -0.42772256543218573 * K3_11;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(7)), Kokkos::fabs(Ynew_i));
              double sci = atol[11] + rtol[11] * ymax;
              double yerr_i = 0.5 * K1_11 + -2.9079558716805471 * K2_11 + 0.22354069897811571 * K3_11;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_12 + K1_12 + 6.1697947043828245 * K2_12 + -0.42772256543218573 * K3_12;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(5)), Kokkos::fabs(Ynew_i));
              double sci = atol[12] + rtol[12] * ymax;
              double yerr_i = 0.5 * K1_12 + -2.9079558716805471 * K2_12 + 0.22354069897811571 * K3_12;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_13 + K1_13 + 6.1697947043828245 * K2_13 + -0.42772256543218573 * K3_13;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(10)), Kokkos::fabs(Ynew_i));
              double sci = atol[13] + rtol[13] * ymax;
              double yerr_i = 0.5 * K1_13 + -2.9079558716805471 * K2_13 + 0.22354069897811571 * K3_13;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_14 + K1_14 + 6.1697947043828245 * K2_14 + -0.42772256543218573 * K3_14;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(12)), Kokkos::fabs(Ynew_i));
              double sci = atol[14] + rtol[14] * ymax;
              double yerr_i = 0.5 * K1_14 + -2.9079558716805471 * K2_14 + 0.22354069897811571 * K3_14;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_15 + K1_15 + 6.1697947043828245 * K2_15 + -0.42772256543218573 * K3_15;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(1)), Kokkos::fabs(Ynew_i));
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
          double err_norm = Kokkos::sqrt(err_norm_sq / 17);
          err_norm = Kokkos::fmax(err_norm, 1.0e-10);

          // Step Size Control (order 3: exponent = 1/3 = 0.33333333333333331)
          double factor = safety / Kokkos::cbrt(err_norm);
          factor = Kokkos::fmax(min_shrink, Kokkos::fmin(factor, max_growth));

          if (err_norm <= 1.0) {
              if (active[0]) state(16) += K1_0 + 6.1697947043828245 * K2_0 + -0.42772256543218573 * K3_0;
              if (active[1]) state(15) += K1_1 + 6.1697947043828245 * K2_1 + -0.42772256543218573 * K3_1;
              if (active[2]) state(14) += K1_2 + 6.1697947043828245 * K2_2 + -0.42772256543218573 * K3_2;
              if (active[3]) state(8) += K1_3 + 6.1697947043828245 * K2_3 + -0.42772256543218573 * K3_3;
              if (active[4]) state(2) += K1_4 + 6.1697947043828245 * K2_4 + -0.42772256543218573 * K3_4;
              if (active[5]) state(13) += K1_5 + 6.1697947043828245 * K2_5 + -0.42772256543218573 * K3_5;
              if (active[6]) state(6) += K1_6 + 6.1697947043828245 * K2_6 + -0.42772256543218573 * K3_6;
              if (active[7]) state(4) += K1_7 + 6.1697947043828245 * K2_7 + -0.42772256543218573 * K3_7;
              if (active[8]) state(3) += K1_8 + 6.1697947043828245 * K2_8 + -0.42772256543218573 * K3_8;
              if (active[9]) state(0) += K1_9 + 6.1697947043828245 * K2_9 + -0.42772256543218573 * K3_9;
              if (active[10]) state(9) += K1_10 + 6.1697947043828245 * K2_10 + -0.42772256543218573 * K3_10;
              if (active[11]) state(7) += K1_11 + 6.1697947043828245 * K2_11 + -0.42772256543218573 * K3_11;
              if (active[12]) state(5) += K1_12 + 6.1697947043828245 * K2_12 + -0.42772256543218573 * K3_12;
              if (active[13]) state(10) += K1_13 + 6.1697947043828245 * K2_13 + -0.42772256543218573 * K3_13;
              if (active[14]) state(12) += K1_14 + 6.1697947043828245 * K2_14 + -0.42772256543218573 * K3_14;
              if (active[15]) state(1) += K1_15 + 6.1697947043828245 * K2_15 + -0.42772256543218573 * K3_15;
              if (active[16]) state(11) += K1_16 + 6.1697947043828245 * K2_16 + -0.42772256543218573 * K3_16;
              t += dt;
              dt *= factor;
          } else {
              dt *= factor;
          }
          } // end while (t < dt_total)
      }
#ifdef MKPP_ENABLE_ADJOINT


      // Forward integration with checkpointing for adjoint/TLM
      // Saves step size h and state at each accepted step into CheckpointBuffer.
      // Returns number of accepted steps, or -1 if MAX_STEPS exceeded.
      template <class StateView>
      KOKKOS_INLINE_FUNCTION int integrate_fwd_checkpoint(
          double dt_total, StateView& state, const double* jvals,
          CheckpointBuffer& chk) const
      {
          const int NUM_SPECIES = 17;
          // ROS-3 coefficients (3-stage, order 3)
          const double g = 0.435866521508459;
          const double safety = 0.9;
          const double max_growth = 6.0;
          const double min_shrink = 0.2;
          int ierr = 0;
          chk.num_steps = 0;
          double t = 0.0;
          double dt = Kokkos::fmin(dt_total, 1.0);  // conservative initial step

          while (t < dt_total) {
          dt = Kokkos::min(dt, dt_total - t);
          const double inv_g_dt = 1.0 / (g * dt);

          // 0. Hoist state values into scalar registers
          // NOTE: State access uses permuted species ordering
          const double S_0 = state(Species::N2);  // [N2]
          const double S_1 = state(Species::M);  // [M]
          const double S_2 = state(Species::H2O);  // [H2O]
          const double S_3 = state(Species::HNO4);  // [HNO4]
          const double S_4 = state(Species::NO);  // [NO]
          const double S_5 = state(Species::O2);  // [O2]
          const double S_6 = state(Species::HONO);  // [HONO]
          const double S_7 = state(Species::NO3);  // [NO3]
          const double S_8 = state(Species::NO2);  // [NO2]
          const double S_9 = state(Species::O3);  // [O3]
          const double S_10 = state(Species::O3P);  // [O3P]
          const double S_11 = state(Species::HNO3);  // [HNO3]
          const double S_12 = state(Species::N2O5);  // [N2O5]
          const double S_13 = state(Species::OH);  // [OH]
          const double S_14 = state(Species::AIR);  // [AIR]
          const double S_15 = state(Species::H2O2);  // [H2O2]
          const double S_16 = state(Species::HO2);  // [HO2]

          // Analytical Jacobian & Iteration Matrix W = inv_g_dt*I - J (sparse)
          double J_4_4 = -2.5972503599796067e-11*S_7 - 1.8706578944791917e-14*S_9;
          double J_4_6 = 1.0*jvals[1];
          double J_4_7 = -2.5972503599796067e-11*S_4;
          double J_4_8 = 1.0*jvals[0];
          double J_4_9 = -1.8706578944791917e-14*S_4;
          double J_6_6 = -1.0*jvals[1];
          double J_7_4 = -2.5972503599796067e-11*S_7;
          double J_7_7 = -2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_8/(1.3846843902855162e-18*S_14 + 1.0) - 2.5972503599796067e-11*S_4;
          double J_7_8 = -2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_7/(1.3846843902855162e-18*S_14 + 1.0) + 3.7190909690468382e-17*S_9;
          double J_7_9 = 3.7190909690468382e-17*S_8;
          double J_7_11 = 1.0*S_13*(2.1296027497121323e-32*S_14/(4.2746565719581312e-19*S_14 + 1.0) + 9.8568101265494379e-14);
          double J_7_12 = 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14/(1.3459847134690284e-18*S_14 + 1.0);
          double J_7_13 = 1.0*S_11*(2.1296027497121323e-32*S_14/(4.2746565719581312e-19*S_14 + 1.0) + 9.8568101265494379e-14);
          double J_7_14 = -1.6029099488139965e-37*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_12/pow(1.3459847134690284e-18*S_14 + 1.0, 2) + 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_12/(1.3459847134690284e-18*S_14 + 1.0) + 1.9018580488528996e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_12*log(1.3459847134690284e-18*S_14)/((1.3459847134690284e-18*S_14 + 1.0)*pow(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10)) + 3.8321461055530778e-48*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_8*S_7/pow(1.3846843902855162e-18*S_14 + 1.0, 2) - 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_8*S_7/(1.3846843902855162e-18*S_14 + 1.0) - 4.4197770694650986e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_8*S_7*log(1.3846843902855162e-18*S_14)/((1.3846843902855162e-18*S_14 + 1.0)*pow(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10)) + 1.0*S_11*S_13*(-9.1033203897170818e-51*S_14/pow(4.2746565719581312e-19*S_14 + 1.0, 2) + 2.1296027497121323e-32/(4.2746565719581312e-19*S_14 + 1.0));
          double J_8_4 = 5.1945007199592134e-11*S_7 + 1.8706578944791917e-14*S_9;
          double J_8_7 = -2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_8/(1.3846843902855162e-18*S_14 + 1.0) + 5.1945007199592134e-11*S_4;
          double J_8_8 = -2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_7/(1.3846843902855162e-18*S_14 + 1.0) - 3.7190909690468382e-17*S_9 - 1.0*jvals[0];
          double J_8_9 = 1.8706578944791917e-14*S_4 - 3.7190909690468382e-17*S_8;
          double J_8_11 = 1.0*jvals[2];
          double J_8_12 = 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14/(1.3459847134690284e-18*S_14 + 1.0);
          double J_8_14 = -1.6029099488139965e-37*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_12/pow(1.3459847134690284e-18*S_14 + 1.0, 2) + 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_12/(1.3459847134690284e-18*S_14 + 1.0) + 1.9018580488528996e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_12*log(1.3459847134690284e-18*S_14)/((1.3459847134690284e-18*S_14 + 1.0)*pow(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10)) + 3.8321461055530778e-48*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_8*S_7/pow(1.3846843902855162e-18*S_14 + 1.0, 2) - 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_8*S_7/(1.3846843902855162e-18*S_14 + 1.0) - 4.4197770694650986e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_8*S_7*log(1.3846843902855162e-18*S_14)/((1.3846843902855162e-18*S_14 + 1.0)*pow(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10));
          double J_9_4 = -1.8706578944791917e-14*S_9;
          double J_9_5 = 5.6800000000000035e-34*S_14*S_10;
          double J_9_8 = -3.7190909690468382e-17*S_9;
          double J_9_9 = -1.8706578944791917e-14*S_4 - 3.7190909690468382e-17*S_8 - 8.3355554445074843e-15*S_10;
          double J_9_10 = 5.6800000000000035e-34*S_14*S_5 - 8.3355554445074843e-15*S_9;
          double J_9_14 = 5.6800000000000035e-34*S_5*S_10;
          double J_10_5 = -5.6800000000000035e-34*S_14*S_10;
          double J_10_8 = 1.0*jvals[0];
          double J_10_9 = -8.3355554445074843e-15*S_10;
          double J_10_10 = -5.6800000000000035e-34*S_14*S_5 - 8.3355554445074843e-15*S_9;
          double J_10_14 = -5.6800000000000035e-34*S_5*S_10;
          double J_11_11 = -1.0*S_13*(2.1296027497121323e-32*S_14/(4.2746565719581312e-19*S_14 + 1.0) + 9.8568101265494379e-14) - 1.0*jvals[2];
          double J_11_13 = -1.0*S_11*(2.1296027497121323e-32*S_14/(4.2746565719581312e-19*S_14 + 1.0) + 9.8568101265494379e-14);
          double J_11_14 = -1.0*S_11*S_13*(-9.1033203897170818e-51*S_14/pow(4.2746565719581312e-19*S_14 + 1.0, 2) + 2.1296027497121323e-32/(4.2746565719581312e-19*S_14 + 1.0));
          double J_12_7 = 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_8/(1.3846843902855162e-18*S_14 + 1.0);
          double J_12_8 = 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_7/(1.3846843902855162e-18*S_14 + 1.0);
          double J_12_12 = -1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14/(1.3459847134690284e-18*S_14 + 1.0);
          double J_12_14 = 1.6029099488139965e-37*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_12/pow(1.3459847134690284e-18*S_14 + 1.0, 2) - 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_12/(1.3459847134690284e-18*S_14 + 1.0) - 1.9018580488528996e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_12*log(1.3459847134690284e-18*S_14)/((1.3459847134690284e-18*S_14 + 1.0)*pow(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10)) - 3.8321461055530778e-48*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_8*S_7/pow(1.3846843902855162e-18*S_14 + 1.0, 2) + 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_8*S_7/(1.3846843902855162e-18*S_14 + 1.0) + 4.4197770694650986e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_8*S_7*log(1.3846843902855162e-18*S_14)/((1.3846843902855162e-18*S_14 + 1.0)*pow(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10));
          double J_13_6 = 1.0*jvals[1];
          double J_13_11 = -1.0*S_13*(2.1296027497121323e-32*S_14/(4.2746565719581312e-19*S_14 + 1.0) + 9.8568101265494379e-14) + 1.0*jvals[2];
          double J_13_13 = -1.0*S_11*(2.1296027497121323e-32*S_14/(4.2746565719581312e-19*S_14 + 1.0) + 9.8568101265494379e-14);
          double J_13_14 = -1.0*S_11*S_13*(-9.1033203897170818e-51*S_14/pow(4.2746565719581312e-19*S_14 + 1.0, 2) + 2.1296027497121323e-32/(4.2746565719581312e-19*S_14 + 1.0));
          double J_13_15 = 2.0*jvals[3];
          double J_15_14 = 4.7653762320694437e-32*S_16;
          double J_15_15 = -1.0*jvals[3];
          double J_15_16 = 4.7653762320694437e-32*S_14 + 1.6994829027540494e-12;
          double J_16_14 = -4.7653762320694437e-32*S_16;
          double J_16_16 = -4.7653762320694437e-32*S_14 - 1.6994829027540494e-12;
          // Block 0: species [N2, H2O, HNO4, NO, O2, O3]
          double W_0_0 = inv_g_dt;
          // Block 1: species [M]
          double W_1_1 = inv_g_dt;
          // Block 0: species [N2, H2O, HNO4, NO, O2, O3]
          double W_2_2 = inv_g_dt;
          double W_3_3 = inv_g_dt;
          double W_4_4 = inv_g_dt - J_4_4;
          double W_4_6 = -J_4_6;
          double W_4_7 = -J_4_7;
          double W_4_8 = -J_4_8;
          double W_4_9 = -J_4_9;
          double W_5_5 = inv_g_dt;
          // Block 2: species [HONO]
          double W_6_6 = inv_g_dt - J_6_6;
          // Block 3: species [NO3, O3P]
          double W_7_4 = -J_7_4;
          double W_7_7 = inv_g_dt - J_7_7;
          double W_7_8 = -J_7_8;
          double W_7_9 = -J_7_9;
          double W_7_11 = -J_7_11;
          double W_7_12 = -J_7_12;
          double W_7_13 = -J_7_13;
          double W_7_14 = -J_7_14;
          // Block 4: species [NO2]
          double W_8_4 = -J_8_4;
          double W_8_7 = -J_8_7;
          double W_8_8 = inv_g_dt - J_8_8;
          double W_8_9 = -J_8_9;
          double W_8_11 = -J_8_11;
          double W_8_12 = -J_8_12;
          double W_8_14 = -J_8_14;
          // Block 0: species [N2, H2O, HNO4, NO, O2, O3]
          double W_9_4 = -J_9_4;
          double W_9_5 = -J_9_5;
          double W_9_8 = -J_9_8;
          double W_9_9 = inv_g_dt - J_9_9;
          double W_9_10 = -J_9_10;
          double W_9_14 = -J_9_14;
          // Block 3: species [NO3, O3P]
          double W_10_5 = -J_10_5;
          double W_10_8 = -J_10_8;
          double W_10_9 = -J_10_9;
          double W_10_10 = inv_g_dt - J_10_10;
          double W_10_14 = -J_10_14;
          // Block 5: species [HNO3]
          double W_11_11 = inv_g_dt - J_11_11;
          double W_11_13 = -J_11_13;
          double W_11_14 = -J_11_14;
          // Block 6: species [N2O5]
          double W_12_7 = -J_12_7;
          double W_12_8 = -J_12_8;
          double W_12_12 = inv_g_dt - J_12_12;
          double W_12_14 = -J_12_14;
          // Block 7: species [OH]
          double W_13_6 = -J_13_6;
          double W_13_11 = -J_13_11;
          double W_13_13 = inv_g_dt - J_13_13;
          double W_13_14 = -J_13_14;
          double W_13_15 = -J_13_15;
          // Block 8: species [AIR]
          double W_14_14 = inv_g_dt;
          // Block 9: species [H2O2]
          double W_15_14 = -J_15_14;
          double W_15_15 = inv_g_dt - J_15_15;
          double W_15_16 = -J_15_16;
          // Block 10: species [HO2]
          double W_16_14 = -J_16_14;
          double W_16_16 = inv_g_dt - J_16_16;

          // Symbolic Doolittle Sparse LU Factorization
          // Block 0: species [N2, H2O, HNO4, NO, O2, O3]
          double U_0_0 = W_0_0;
          // Block 1: species [M]
          double U_1_1 = W_1_1;
          double U_2_2 = W_2_2;
          double U_3_3 = W_3_3;
          double U_4_4 = W_4_4;
          double U_4_6 = W_4_6;
          double U_4_7 = W_4_7;
          double U_4_8 = W_4_8;
          double U_4_9 = W_4_9;
          // Block 3: species [NO3, O3P]
          double L_7_4 = (W_7_4) / U_4_4;
          // Block 4: species [NO2]
          double L_8_4 = (W_8_4) / U_4_4;
          double L_9_4 = (W_9_4) / U_4_4;
          double U_5_5 = W_5_5;
          double L_9_5 = (W_9_5) / U_5_5;
          double L_10_5 = (W_10_5) / U_5_5;
          // Block 2: species [HONO]
          double U_6_6 = W_6_6;
          double L_7_6 = (0.0 - L_7_4 * U_4_6) / U_6_6;
          double L_8_6 = (0.0 - L_8_4 * U_4_6) / U_6_6;
          double L_9_6 = (0.0 - L_9_4 * U_4_6) / U_6_6;
          // Block 7: species [OH]
          double L_13_6 = (W_13_6) / U_6_6;
          double U_7_7 = W_7_7 - L_7_4 * U_4_7;
          double U_7_8 = W_7_8 - L_7_4 * U_4_8;
          double U_7_9 = W_7_9 - L_7_4 * U_4_9;
          double U_7_11 = W_7_11;
          double U_7_12 = W_7_12;
          double U_7_13 = W_7_13;
          double U_7_14 = W_7_14;
          double L_8_7 = (W_8_7 - L_8_4 * U_4_7) / U_7_7;
          double L_9_7 = (0.0 - L_9_4 * U_4_7) / U_7_7;
          // Block 6: species [N2O5]
          double L_12_7 = (W_12_7) / U_7_7;
          double U_8_8 = W_8_8 - L_8_4 * U_4_8 - L_8_7 * U_7_8;
          double U_8_9 = W_8_9 - L_8_4 * U_4_9 - L_8_7 * U_7_9;
          double U_8_11 = W_8_11 - L_8_7 * U_7_11;
          double U_8_12 = W_8_12 - L_8_7 * U_7_12;
          double U_8_13 = 0.0 - L_8_7 * U_7_13;
          double U_8_14 = W_8_14 - L_8_7 * U_7_14;
          double L_9_8 = (W_9_8 - L_9_4 * U_4_8 - L_9_7 * U_7_8) / U_8_8;
          double L_10_8 = (W_10_8) / U_8_8;
          double L_12_8 = (W_12_8 - L_12_7 * U_7_8) / U_8_8;
          double U_9_9 = W_9_9 - L_9_4 * U_4_9 - L_9_7 * U_7_9 - L_9_8 * U_8_9;
          double U_9_10 = W_9_10;
          double U_9_11 = 0.0 - L_9_7 * U_7_11 - L_9_8 * U_8_11;
          double U_9_12 = 0.0 - L_9_7 * U_7_12 - L_9_8 * U_8_12;
          double U_9_13 = 0.0 - L_9_7 * U_7_13 - L_9_8 * U_8_13;
          double U_9_14 = W_9_14 - L_9_7 * U_7_14 - L_9_8 * U_8_14;
          double L_10_9 = (W_10_9 - L_10_8 * U_8_9) / U_9_9;
          double L_12_9 = (0.0 - L_12_7 * U_7_9 - L_12_8 * U_8_9) / U_9_9;
          double U_10_10 = W_10_10 - L_10_9 * U_9_10;
          double U_10_11 = 0.0 - L_10_8 * U_8_11 - L_10_9 * U_9_11;
          double U_10_12 = 0.0 - L_10_8 * U_8_12 - L_10_9 * U_9_12;
          double U_10_13 = 0.0 - L_10_8 * U_8_13 - L_10_9 * U_9_13;
          double U_10_14 = W_10_14 - L_10_8 * U_8_14 - L_10_9 * U_9_14;
          double L_12_10 = (0.0 - L_12_9 * U_9_10) / U_10_10;
          // Block 5: species [HNO3]
          double U_11_11 = W_11_11;
          double U_11_13 = W_11_13;
          double U_11_14 = W_11_14;
          double L_12_11 = (0.0 - L_12_7 * U_7_11 - L_12_8 * U_8_11 - L_12_9 * U_9_11 - L_12_10 * U_10_11) / U_11_11;
          double L_13_11 = (W_13_11) / U_11_11;
          double U_12_12 = W_12_12 - L_12_7 * U_7_12 - L_12_8 * U_8_12 - L_12_9 * U_9_12 - L_12_10 * U_10_12;
          double U_12_13 = 0.0 - L_12_7 * U_7_13 - L_12_8 * U_8_13 - L_12_9 * U_9_13 - L_12_10 * U_10_13 - L_12_11 * U_11_13;
          double U_12_14 = W_12_14 - L_12_7 * U_7_14 - L_12_8 * U_8_14 - L_12_9 * U_9_14 - L_12_10 * U_10_14 - L_12_11 * U_11_14;
          double U_13_13 = W_13_13 - L_13_11 * U_11_13;
          double U_13_14 = W_13_14 - L_13_11 * U_11_14;
          double U_13_15 = W_13_15;
          // Block 8: species [AIR]
          double U_14_14 = W_14_14;
          // Block 9: species [H2O2]
          double L_15_14 = (W_15_14) / U_14_14;
          // Block 10: species [HO2]
          double L_16_14 = (W_16_14) / U_14_14;
          double U_15_15 = W_15_15;
          double U_15_16 = W_15_16;
          double U_16_16 = W_16_16;

          // --- Stage 1 ---
          // Rate evaluation F1 at S
          double F1_0 = 0.0;
          double F1_1 = 0.0;
          double F1_2 = 0.0;
          double F1_3 = 0.0;
          double F1_4 = 1.0*S_6*jvals[1] - 2.5972503599796067e-11*S_4*S_7 - 1.8706578944791917e-14*S_4*S_9 + 1.0*S_8*jvals[0];
          double F1_5 = 0.0;
          double F1_6 = -1.0*S_6*jvals[1];
          double F1_7 = 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_12/(1.3459847134690284e-18*S_14 + 1.0) - 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_8*S_7/(1.3846843902855162e-18*S_14 + 1.0) + 1.0*S_11*S_13*(2.1296027497121323e-32*S_14/(4.2746565719581312e-19*S_14 + 1.0) + 9.8568101265494379e-14) - 2.5972503599796067e-11*S_4*S_7 + 3.7190909690468382e-17*S_8*S_9;
          double F1_8 = 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_12/(1.3459847134690284e-18*S_14 + 1.0) - 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_8*S_7/(1.3846843902855162e-18*S_14 + 1.0) + 1.0*S_11*jvals[2] + 5.1945007199592134e-11*S_4*S_7 + 1.8706578944791917e-14*S_4*S_9 - 3.7190909690468382e-17*S_8*S_9 - 1.0*S_8*jvals[0];
          double F1_9 = 5.6800000000000035e-34*S_14*S_5*S_10 - 1.8706578944791917e-14*S_4*S_9 - 3.7190909690468382e-17*S_8*S_9 - 8.3355554445074843e-15*S_9*S_10;
          double F1_10 = -5.6800000000000035e-34*S_14*S_5*S_10 + 1.0*S_8*jvals[0] - 8.3355554445074843e-15*S_9*S_10;
          double F1_11 = -1.0*S_11*S_13*(2.1296027497121323e-32*S_14/(4.2746565719581312e-19*S_14 + 1.0) + 9.8568101265494379e-14) - 1.0*S_11*jvals[2];
          double F1_12 = -1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_12/(1.3459847134690284e-18*S_14 + 1.0) + 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_8*S_7/(1.3846843902855162e-18*S_14 + 1.0);
          double F1_13 = 2.0*S_15*jvals[3] - 1.0*S_11*S_13*(2.1296027497121323e-32*S_14/(4.2746565719581312e-19*S_14 + 1.0) + 9.8568101265494379e-14) + 1.0*S_11*jvals[2] + 1.0*S_6*jvals[1];
          double F1_14 = 0.0;
          double F1_15 = -1.0*S_15*jvals[3] + 1.0*S_16*(4.7653762320694437e-32*S_14 + 1.6994829027540494e-12);
          double F1_16 = -1.0*S_16*(4.7653762320694437e-32*S_14 + 1.6994829027540494e-12);
          // Block 0: K1 forward sub [N2, H2O, HNO4, NO, O2, O3]
          double y1_0 = F1_0;
          // Block 1: K1 forward sub [M]
          double y1_1 = F1_1;
          double y1_2 = F1_2;
          double y1_3 = F1_3;
          double y1_4 = F1_4;
          double y1_5 = F1_5;
          // Block 2: K1 forward sub [HONO]
          double y1_6 = F1_6;
          // Block 3: K1 forward sub [NO3, O3P]
          double y1_7 = F1_7 - L_7_4 * y1_4 - L_7_6 * y1_6;
          // Block 4: K1 forward sub [NO2]
          double y1_8 = F1_8 - L_8_4 * y1_4 - L_8_6 * y1_6 - L_8_7 * y1_7;
          double y1_9 = F1_9 - L_9_4 * y1_4 - L_9_5 * y1_5 - L_9_6 * y1_6 - L_9_7 * y1_7 - L_9_8 * y1_8;
          double y1_10 = F1_10 - L_10_5 * y1_5 - L_10_8 * y1_8 - L_10_9 * y1_9;
          // Block 5: K1 forward sub [HNO3]
          double y1_11 = F1_11;
          // Block 6: K1 forward sub [N2O5]
          double y1_12 = F1_12 - L_12_7 * y1_7 - L_12_8 * y1_8 - L_12_9 * y1_9 - L_12_10 * y1_10 - L_12_11 * y1_11;
          // Block 7: K1 forward sub [OH]
          double y1_13 = F1_13 - L_13_6 * y1_6 - L_13_11 * y1_11;
          // Block 8: K1 forward sub [AIR]
          double y1_14 = F1_14;
          // Block 9: K1 forward sub [H2O2]
          double y1_15 = F1_15 - L_15_14 * y1_14;
          // Block 10: K1 forward sub [HO2]
          double y1_16 = F1_16 - L_16_14 * y1_14;

          // Block 10: K1 backward sub [HO2]
          double K1_16 = y1_16 / U_16_16;
          // Block 9: K1 backward sub [H2O2]
          double K1_15 = (y1_15 - U_15_16 * K1_16) / U_15_15;
          // Block 8: K1 backward sub [AIR]
          double K1_14 = y1_14 / U_14_14;
          // Block 7: K1 backward sub [OH]
          double K1_13 = (y1_13 - U_13_14 * K1_14 - U_13_15 * K1_15) / U_13_13;
          // Block 6: K1 backward sub [N2O5]
          double K1_12 = (y1_12 - U_12_13 * K1_13 - U_12_14 * K1_14) / U_12_12;
          // Block 5: K1 backward sub [HNO3]
          double K1_11 = (y1_11 - U_11_13 * K1_13 - U_11_14 * K1_14) / U_11_11;
          // Block 3: K1 backward sub [NO3, O3P]
          double K1_10 = (y1_10 - U_10_11 * K1_11 - U_10_12 * K1_12 - U_10_13 * K1_13 - U_10_14 * K1_14) / U_10_10;
          // Block 0: K1 backward sub [N2, H2O, HNO4, NO, O2, O3]
          double K1_9 = (y1_9 - U_9_10 * K1_10 - U_9_11 * K1_11 - U_9_12 * K1_12 - U_9_13 * K1_13 - U_9_14 * K1_14) / U_9_9;
          // Block 4: K1 backward sub [NO2]
          double K1_8 = (y1_8 - U_8_9 * K1_9 - U_8_11 * K1_11 - U_8_12 * K1_12 - U_8_13 * K1_13 - U_8_14 * K1_14) / U_8_8;
          double K1_7 = (y1_7 - U_7_8 * K1_8 - U_7_9 * K1_9 - U_7_11 * K1_11 - U_7_12 * K1_12 - U_7_13 * K1_13 - U_7_14 * K1_14) / U_7_7;
          // Block 2: K1 backward sub [HONO]
          double K1_6 = y1_6 / U_6_6;
          double K1_5 = y1_5 / U_5_5;
          double K1_4 = (y1_4 - U_4_6 * K1_6 - U_4_7 * K1_7 - U_4_8 * K1_8 - U_4_9 * K1_9) / U_4_4;
          double K1_3 = y1_3 / U_3_3;
          double K1_2 = y1_2 / U_2_2;
          // Block 1: K1 backward sub [M]
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
          // Rate evaluation F2 at Y2
          double F2_0 = 0.0;
          double F2_1 = 0.0;
          double F2_2 = 0.0;
          double F2_3 = 0.0;
          double F2_4 = 1.0*Y2_6*jvals[1] - 2.5972503599796067e-11*Y2_4*Y2_7 - 1.8706578944791917e-14*Y2_4*Y2_9 + 1.0*Y2_8*jvals[0];
          double F2_5 = 0.0;
          double F2_6 = -1.0*Y2_6*jvals[1];
          double F2_7 = 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*Y2_14), 2)/(M_LN10 * M_LN10) + 1.0))*Y2_14*Y2_12/(1.3459847134690284e-18*Y2_14 + 1.0) - 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*Y2_14), 2)/(M_LN10 * M_LN10) + 1.0))*Y2_14*Y2_8*Y2_7/(1.3846843902855162e-18*Y2_14 + 1.0) + 1.0*Y2_11*Y2_13*(2.1296027497121323e-32*Y2_14/(4.2746565719581312e-19*Y2_14 + 1.0) + 9.8568101265494379e-14) - 2.5972503599796067e-11*Y2_4*Y2_7 + 3.7190909690468382e-17*Y2_8*Y2_9;
          double F2_8 = 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*Y2_14), 2)/(M_LN10 * M_LN10) + 1.0))*Y2_14*Y2_12/(1.3459847134690284e-18*Y2_14 + 1.0) - 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*Y2_14), 2)/(M_LN10 * M_LN10) + 1.0))*Y2_14*Y2_8*Y2_7/(1.3846843902855162e-18*Y2_14 + 1.0) + 1.0*Y2_11*jvals[2] + 5.1945007199592134e-11*Y2_4*Y2_7 + 1.8706578944791917e-14*Y2_4*Y2_9 - 3.7190909690468382e-17*Y2_8*Y2_9 - 1.0*Y2_8*jvals[0];
          double F2_9 = 5.6800000000000035e-34*Y2_14*Y2_5*Y2_10 - 1.8706578944791917e-14*Y2_4*Y2_9 - 3.7190909690468382e-17*Y2_8*Y2_9 - 8.3355554445074843e-15*Y2_9*Y2_10;
          double F2_10 = -5.6800000000000035e-34*Y2_14*Y2_5*Y2_10 + 1.0*Y2_8*jvals[0] - 8.3355554445074843e-15*Y2_9*Y2_10;
          double F2_11 = -1.0*Y2_11*Y2_13*(2.1296027497121323e-32*Y2_14/(4.2746565719581312e-19*Y2_14 + 1.0) + 9.8568101265494379e-14) - 1.0*Y2_11*jvals[2];
          double F2_12 = -1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*Y2_14), 2)/(M_LN10 * M_LN10) + 1.0))*Y2_14*Y2_12/(1.3459847134690284e-18*Y2_14 + 1.0) + 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*Y2_14), 2)/(M_LN10 * M_LN10) + 1.0))*Y2_14*Y2_8*Y2_7/(1.3846843902855162e-18*Y2_14 + 1.0);
          double F2_13 = 2.0*Y2_15*jvals[3] - 1.0*Y2_11*Y2_13*(2.1296027497121323e-32*Y2_14/(4.2746565719581312e-19*Y2_14 + 1.0) + 9.8568101265494379e-14) + 1.0*Y2_11*jvals[2] + 1.0*Y2_6*jvals[1];
          double F2_14 = 0.0;
          double F2_15 = -1.0*Y2_15*jvals[3] + 1.0*Y2_16*(4.7653762320694437e-32*Y2_14 + 1.6994829027540494e-12);
          double F2_16 = -1.0*Y2_16*(4.7653762320694437e-32*Y2_14 + 1.6994829027540494e-12);
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
          // Block 0: K2 forward sub [N2, H2O, HNO4, NO, O2, O3]
          double y2_0 = rhs2_0;
          // Block 1: K2 forward sub [M]
          double y2_1 = rhs2_1;
          double y2_2 = rhs2_2;
          double y2_3 = rhs2_3;
          double y2_4 = rhs2_4;
          double y2_5 = rhs2_5;
          // Block 2: K2 forward sub [HONO]
          double y2_6 = rhs2_6;
          // Block 3: K2 forward sub [NO3, O3P]
          double y2_7 = rhs2_7 - L_7_4 * y2_4 - L_7_6 * y2_6;
          // Block 4: K2 forward sub [NO2]
          double y2_8 = rhs2_8 - L_8_4 * y2_4 - L_8_6 * y2_6 - L_8_7 * y2_7;
          double y2_9 = rhs2_9 - L_9_4 * y2_4 - L_9_5 * y2_5 - L_9_6 * y2_6 - L_9_7 * y2_7 - L_9_8 * y2_8;
          double y2_10 = rhs2_10 - L_10_5 * y2_5 - L_10_8 * y2_8 - L_10_9 * y2_9;
          // Block 5: K2 forward sub [HNO3]
          double y2_11 = rhs2_11;
          // Block 6: K2 forward sub [N2O5]
          double y2_12 = rhs2_12 - L_12_7 * y2_7 - L_12_8 * y2_8 - L_12_9 * y2_9 - L_12_10 * y2_10 - L_12_11 * y2_11;
          // Block 7: K2 forward sub [OH]
          double y2_13 = rhs2_13 - L_13_6 * y2_6 - L_13_11 * y2_11;
          // Block 8: K2 forward sub [AIR]
          double y2_14 = rhs2_14;
          // Block 9: K2 forward sub [H2O2]
          double y2_15 = rhs2_15 - L_15_14 * y2_14;
          // Block 10: K2 forward sub [HO2]
          double y2_16 = rhs2_16 - L_16_14 * y2_14;

          // Block 10: K2 backward sub [HO2]
          double K2_16 = y2_16 / U_16_16;
          // Block 9: K2 backward sub [H2O2]
          double K2_15 = (y2_15 - U_15_16 * K2_16) / U_15_15;
          // Block 8: K2 backward sub [AIR]
          double K2_14 = y2_14 / U_14_14;
          // Block 7: K2 backward sub [OH]
          double K2_13 = (y2_13 - U_13_14 * K2_14 - U_13_15 * K2_15) / U_13_13;
          // Block 6: K2 backward sub [N2O5]
          double K2_12 = (y2_12 - U_12_13 * K2_13 - U_12_14 * K2_14) / U_12_12;
          // Block 5: K2 backward sub [HNO3]
          double K2_11 = (y2_11 - U_11_13 * K2_13 - U_11_14 * K2_14) / U_11_11;
          // Block 3: K2 backward sub [NO3, O3P]
          double K2_10 = (y2_10 - U_10_11 * K2_11 - U_10_12 * K2_12 - U_10_13 * K2_13 - U_10_14 * K2_14) / U_10_10;
          // Block 0: K2 backward sub [N2, H2O, HNO4, NO, O2, O3]
          double K2_9 = (y2_9 - U_9_10 * K2_10 - U_9_11 * K2_11 - U_9_12 * K2_12 - U_9_13 * K2_13 - U_9_14 * K2_14) / U_9_9;
          // Block 4: K2 backward sub [NO2]
          double K2_8 = (y2_8 - U_8_9 * K2_9 - U_8_11 * K2_11 - U_8_12 * K2_12 - U_8_13 * K2_13 - U_8_14 * K2_14) / U_8_8;
          double K2_7 = (y2_7 - U_7_8 * K2_8 - U_7_9 * K2_9 - U_7_11 * K2_11 - U_7_12 * K2_12 - U_7_13 * K2_13 - U_7_14 * K2_14) / U_7_7;
          // Block 2: K2 backward sub [HONO]
          double K2_6 = y2_6 / U_6_6;
          double K2_5 = y2_5 / U_5_5;
          double K2_4 = (y2_4 - U_4_6 * K2_6 - U_4_7 * K2_7 - U_4_8 * K2_8 - U_4_9 * K2_9) / U_4_4;
          double K2_3 = y2_3 / U_3_3;
          double K2_2 = y2_2 / U_2_2;
          // Block 1: K2 backward sub [M]
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
          // Block 0: K3 forward sub [N2, H2O, HNO4, NO, O2, O3]
          double y3_0 = rhs3_0;
          // Block 1: K3 forward sub [M]
          double y3_1 = rhs3_1;
          double y3_2 = rhs3_2;
          double y3_3 = rhs3_3;
          double y3_4 = rhs3_4;
          double y3_5 = rhs3_5;
          // Block 2: K3 forward sub [HONO]
          double y3_6 = rhs3_6;
          // Block 3: K3 forward sub [NO3, O3P]
          double y3_7 = rhs3_7 - L_7_4 * y3_4 - L_7_6 * y3_6;
          // Block 4: K3 forward sub [NO2]
          double y3_8 = rhs3_8 - L_8_4 * y3_4 - L_8_6 * y3_6 - L_8_7 * y3_7;
          double y3_9 = rhs3_9 - L_9_4 * y3_4 - L_9_5 * y3_5 - L_9_6 * y3_6 - L_9_7 * y3_7 - L_9_8 * y3_8;
          double y3_10 = rhs3_10 - L_10_5 * y3_5 - L_10_8 * y3_8 - L_10_9 * y3_9;
          // Block 5: K3 forward sub [HNO3]
          double y3_11 = rhs3_11;
          // Block 6: K3 forward sub [N2O5]
          double y3_12 = rhs3_12 - L_12_7 * y3_7 - L_12_8 * y3_8 - L_12_9 * y3_9 - L_12_10 * y3_10 - L_12_11 * y3_11;
          // Block 7: K3 forward sub [OH]
          double y3_13 = rhs3_13 - L_13_6 * y3_6 - L_13_11 * y3_11;
          // Block 8: K3 forward sub [AIR]
          double y3_14 = rhs3_14;
          // Block 9: K3 forward sub [H2O2]
          double y3_15 = rhs3_15 - L_15_14 * y3_14;
          // Block 10: K3 forward sub [HO2]
          double y3_16 = rhs3_16 - L_16_14 * y3_14;

          // Block 10: K3 backward sub [HO2]
          double K3_16 = y3_16 / U_16_16;
          // Block 9: K3 backward sub [H2O2]
          double K3_15 = (y3_15 - U_15_16 * K3_16) / U_15_15;
          // Block 8: K3 backward sub [AIR]
          double K3_14 = y3_14 / U_14_14;
          // Block 7: K3 backward sub [OH]
          double K3_13 = (y3_13 - U_13_14 * K3_14 - U_13_15 * K3_15) / U_13_13;
          // Block 6: K3 backward sub [N2O5]
          double K3_12 = (y3_12 - U_12_13 * K3_13 - U_12_14 * K3_14) / U_12_12;
          // Block 5: K3 backward sub [HNO3]
          double K3_11 = (y3_11 - U_11_13 * K3_13 - U_11_14 * K3_14) / U_11_11;
          // Block 3: K3 backward sub [NO3, O3P]
          double K3_10 = (y3_10 - U_10_11 * K3_11 - U_10_12 * K3_12 - U_10_13 * K3_13 - U_10_14 * K3_14) / U_10_10;
          // Block 0: K3 backward sub [N2, H2O, HNO4, NO, O2, O3]
          double K3_9 = (y3_9 - U_9_10 * K3_10 - U_9_11 * K3_11 - U_9_12 * K3_12 - U_9_13 * K3_13 - U_9_14 * K3_14) / U_9_9;
          // Block 4: K3 backward sub [NO2]
          double K3_8 = (y3_8 - U_8_9 * K3_9 - U_8_11 * K3_11 - U_8_12 * K3_12 - U_8_13 * K3_13 - U_8_14 * K3_14) / U_8_8;
          double K3_7 = (y3_7 - U_7_8 * K3_8 - U_7_9 * K3_9 - U_7_11 * K3_11 - U_7_12 * K3_12 - U_7_13 * K3_13 - U_7_14 * K3_14) / U_7_7;
          // Block 2: K3 backward sub [HONO]
          double K3_6 = y3_6 / U_6_6;
          double K3_5 = y3_5 / U_5_5;
          double K3_4 = (y3_4 - U_4_6 * K3_6 - U_4_7 * K3_7 - U_4_8 * K3_8 - U_4_9 * K3_9) / U_4_4;
          double K3_3 = y3_3 / U_3_3;
          double K3_2 = y3_2 / U_2_2;
          // Block 1: K3 backward sub [M]
          double K3_1 = y3_1 / U_1_1;
          double K3_0 = y3_0 / U_0_0;


          // --- Solution update and error estimation ---
          double err_norm_sq = 0.0;
          {
              double Ynew_i = S_0 + K1_0 + 6.1697947043828245 * K2_0 + -0.42772256543218573 * K3_0;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(16)), Kokkos::fabs(Ynew_i));
              double sci = atol[0] + rtol[0] * ymax;
              double yerr_i = 0.5 * K1_0 + -2.9079558716805471 * K2_0 + 0.22354069897811571 * K3_0;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_1 + K1_1 + 6.1697947043828245 * K2_1 + -0.42772256543218573 * K3_1;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(15)), Kokkos::fabs(Ynew_i));
              double sci = atol[1] + rtol[1] * ymax;
              double yerr_i = 0.5 * K1_1 + -2.9079558716805471 * K2_1 + 0.22354069897811571 * K3_1;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_2 + K1_2 + 6.1697947043828245 * K2_2 + -0.42772256543218573 * K3_2;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(14)), Kokkos::fabs(Ynew_i));
              double sci = atol[2] + rtol[2] * ymax;
              double yerr_i = 0.5 * K1_2 + -2.9079558716805471 * K2_2 + 0.22354069897811571 * K3_2;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_3 + K1_3 + 6.1697947043828245 * K2_3 + -0.42772256543218573 * K3_3;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(8)), Kokkos::fabs(Ynew_i));
              double sci = atol[3] + rtol[3] * ymax;
              double yerr_i = 0.5 * K1_3 + -2.9079558716805471 * K2_3 + 0.22354069897811571 * K3_3;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_4 + K1_4 + 6.1697947043828245 * K2_4 + -0.42772256543218573 * K3_4;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(2)), Kokkos::fabs(Ynew_i));
              double sci = atol[4] + rtol[4] * ymax;
              double yerr_i = 0.5 * K1_4 + -2.9079558716805471 * K2_4 + 0.22354069897811571 * K3_4;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_5 + K1_5 + 6.1697947043828245 * K2_5 + -0.42772256543218573 * K3_5;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(13)), Kokkos::fabs(Ynew_i));
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
          {
              double Ynew_i = S_7 + K1_7 + 6.1697947043828245 * K2_7 + -0.42772256543218573 * K3_7;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(4)), Kokkos::fabs(Ynew_i));
              double sci = atol[7] + rtol[7] * ymax;
              double yerr_i = 0.5 * K1_7 + -2.9079558716805471 * K2_7 + 0.22354069897811571 * K3_7;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_8 + K1_8 + 6.1697947043828245 * K2_8 + -0.42772256543218573 * K3_8;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(3)), Kokkos::fabs(Ynew_i));
              double sci = atol[8] + rtol[8] * ymax;
              double yerr_i = 0.5 * K1_8 + -2.9079558716805471 * K2_8 + 0.22354069897811571 * K3_8;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_9 + K1_9 + 6.1697947043828245 * K2_9 + -0.42772256543218573 * K3_9;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(0)), Kokkos::fabs(Ynew_i));
              double sci = atol[9] + rtol[9] * ymax;
              double yerr_i = 0.5 * K1_9 + -2.9079558716805471 * K2_9 + 0.22354069897811571 * K3_9;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_10 + K1_10 + 6.1697947043828245 * K2_10 + -0.42772256543218573 * K3_10;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(9)), Kokkos::fabs(Ynew_i));
              double sci = atol[10] + rtol[10] * ymax;
              double yerr_i = 0.5 * K1_10 + -2.9079558716805471 * K2_10 + 0.22354069897811571 * K3_10;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_11 + K1_11 + 6.1697947043828245 * K2_11 + -0.42772256543218573 * K3_11;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(7)), Kokkos::fabs(Ynew_i));
              double sci = atol[11] + rtol[11] * ymax;
              double yerr_i = 0.5 * K1_11 + -2.9079558716805471 * K2_11 + 0.22354069897811571 * K3_11;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_12 + K1_12 + 6.1697947043828245 * K2_12 + -0.42772256543218573 * K3_12;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(5)), Kokkos::fabs(Ynew_i));
              double sci = atol[12] + rtol[12] * ymax;
              double yerr_i = 0.5 * K1_12 + -2.9079558716805471 * K2_12 + 0.22354069897811571 * K3_12;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_13 + K1_13 + 6.1697947043828245 * K2_13 + -0.42772256543218573 * K3_13;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(10)), Kokkos::fabs(Ynew_i));
              double sci = atol[13] + rtol[13] * ymax;
              double yerr_i = 0.5 * K1_13 + -2.9079558716805471 * K2_13 + 0.22354069897811571 * K3_13;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_14 + K1_14 + 6.1697947043828245 * K2_14 + -0.42772256543218573 * K3_14;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(12)), Kokkos::fabs(Ynew_i));
              double sci = atol[14] + rtol[14] * ymax;
              double yerr_i = 0.5 * K1_14 + -2.9079558716805471 * K2_14 + 0.22354069897811571 * K3_14;
              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);
          }
          {
              double Ynew_i = S_15 + K1_15 + 6.1697947043828245 * K2_15 + -0.42772256543218573 * K3_15;
              double ymax = Kokkos::fmax(Kokkos::fabs(state(1)), Kokkos::fabs(Ynew_i));
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
          double err_norm = Kokkos::sqrt(err_norm_sq / 17);
          err_norm = Kokkos::fmax(err_norm, 1.0e-10);

          // Step Size Control (order 3: exponent = 1/3 = 0.33333333333333331)
          double factor = safety / Kokkos::cbrt(err_norm);
          factor = Kokkos::fmax(min_shrink, Kokkos::fmin(factor, max_growth));

          if (err_norm <= 1.0) {
              state(16) += K1_0 + 6.1697947043828245 * K2_0 + -0.42772256543218573 * K3_0;
              state(15) += K1_1 + 6.1697947043828245 * K2_1 + -0.42772256543218573 * K3_1;
              state(14) += K1_2 + 6.1697947043828245 * K2_2 + -0.42772256543218573 * K3_2;
              state(8) += K1_3 + 6.1697947043828245 * K2_3 + -0.42772256543218573 * K3_3;
              state(2) += K1_4 + 6.1697947043828245 * K2_4 + -0.42772256543218573 * K3_4;
              state(13) += K1_5 + 6.1697947043828245 * K2_5 + -0.42772256543218573 * K3_5;
              state(6) += K1_6 + 6.1697947043828245 * K2_6 + -0.42772256543218573 * K3_6;
              state(4) += K1_7 + 6.1697947043828245 * K2_7 + -0.42772256543218573 * K3_7;
              state(3) += K1_8 + 6.1697947043828245 * K2_8 + -0.42772256543218573 * K3_8;
              state(0) += K1_9 + 6.1697947043828245 * K2_9 + -0.42772256543218573 * K3_9;
              state(9) += K1_10 + 6.1697947043828245 * K2_10 + -0.42772256543218573 * K3_10;
              state(7) += K1_11 + 6.1697947043828245 * K2_11 + -0.42772256543218573 * K3_11;
              state(5) += K1_12 + 6.1697947043828245 * K2_12 + -0.42772256543218573 * K3_12;
              state(10) += K1_13 + 6.1697947043828245 * K2_13 + -0.42772256543218573 * K3_13;
              state(12) += K1_14 + 6.1697947043828245 * K2_14 + -0.42772256543218573 * K3_14;
              state(1) += K1_15 + 6.1697947043828245 * K2_15 + -0.42772256543218573 * K3_15;
              state(11) += K1_16 + 6.1697947043828245 * K2_16 + -0.42772256543218573 * K3_16;
              // Save checkpoint data for adjoint/TLM
              if (chk.num_steps >= CheckpointBuffer::MAX_STEPS) {
                  ierr = 1;  // Exceeded MAX_STEPS budget
                  return -1;
              }
              chk.h[chk.num_steps] = dt;
              chk.state[chk.num_steps][0] = state(16);
              chk.state[chk.num_steps][1] = state(15);
              chk.state[chk.num_steps][2] = state(14);
              chk.state[chk.num_steps][3] = state(8);
              chk.state[chk.num_steps][4] = state(2);
              chk.state[chk.num_steps][5] = state(13);
              chk.state[chk.num_steps][6] = state(6);
              chk.state[chk.num_steps][7] = state(4);
              chk.state[chk.num_steps][8] = state(3);
              chk.state[chk.num_steps][9] = state(0);
              chk.state[chk.num_steps][10] = state(9);
              chk.state[chk.num_steps][11] = state(7);
              chk.state[chk.num_steps][12] = state(5);
              chk.state[chk.num_steps][13] = state(10);
              chk.state[chk.num_steps][14] = state(12);
              chk.state[chk.num_steps][15] = state(1);
              chk.state[chk.num_steps][16] = state(11);
              chk.num_steps++;
              t += dt;
              dt *= factor;
          } else {
              dt *= factor;
          }
          } // end while (t < dt_total)
          return chk.num_steps;
      }


      // Discrete adjoint backward integration through checkpointed trajectory
      // Walks backward through saved steps, accumulating adjoint variable lambda.
      template <class StateView, class AdjView>
      KOKKOS_INLINE_FUNCTION void integrate_adj(
          double dt_total, const StateView& state_final,
          AdjView& lambda, const double* jvals,
          const CheckpointBuffer& chk) const
      {
          const double g = 0.435866521508459;

          // --- Discrete Adjoint: backward integration over checkpointed steps ---
          for (int step = chk.num_steps - 1; step >= 0; step--) {
              const double h = chk.h[step];
              const double inv_g_h = 1.0 / (g * h);

              // Reload checkpointed state
              const double S_0 = chk.state[step][0];
              const double S_1 = chk.state[step][1];
              const double S_2 = chk.state[step][2];
              const double S_3 = chk.state[step][3];
              const double S_4 = chk.state[step][4];
              const double S_5 = chk.state[step][5];
              const double S_6 = chk.state[step][6];
              const double S_7 = chk.state[step][7];
              const double S_8 = chk.state[step][8];
              const double S_9 = chk.state[step][9];
              const double S_10 = chk.state[step][10];
              const double S_11 = chk.state[step][11];
              const double S_12 = chk.state[step][12];
              const double S_13 = chk.state[step][13];
              const double S_14 = chk.state[step][14];
              const double S_15 = chk.state[step][15];
              const double S_16 = chk.state[step][16];

              // Recompute Jacobian at checkpointed state (recompute-J strategy, D1)
              double J_4_4 = -2.5972503599796067e-11*S_7 - 1.8706578944791917e-14*S_9;
              double J_4_6 = 1.0*jvals[1];
              double J_4_7 = -2.5972503599796067e-11*S_4;
              double J_4_8 = 1.0*jvals[0];
              double J_4_9 = -1.8706578944791917e-14*S_4;
              double J_6_6 = -1.0*jvals[1];
              double J_7_4 = -2.5972503599796067e-11*S_7;
              double J_7_7 = -2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_8/(1.3846843902855162e-18*S_14 + 1.0) - 2.5972503599796067e-11*S_4;
              double J_7_8 = -2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_7/(1.3846843902855162e-18*S_14 + 1.0) + 3.7190909690468382e-17*S_9;
              double J_7_9 = 3.7190909690468382e-17*S_8;
              double J_7_11 = 1.0*S_13*(2.1296027497121323e-32*S_14/(4.2746565719581312e-19*S_14 + 1.0) + 9.8568101265494379e-14);
              double J_7_12 = 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14/(1.3459847134690284e-18*S_14 + 1.0);
              double J_7_13 = 1.0*S_11*(2.1296027497121323e-32*S_14/(4.2746565719581312e-19*S_14 + 1.0) + 9.8568101265494379e-14);
              double J_7_14 = -1.6029099488139965e-37*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_12/pow(1.3459847134690284e-18*S_14 + 1.0, 2) + 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_12/(1.3459847134690284e-18*S_14 + 1.0) + 1.9018580488528996e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_12*log(1.3459847134690284e-18*S_14)/((1.3459847134690284e-18*S_14 + 1.0)*pow(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10)) + 3.8321461055530778e-48*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_8*S_7/pow(1.3846843902855162e-18*S_14 + 1.0, 2) - 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_8*S_7/(1.3846843902855162e-18*S_14 + 1.0) - 4.4197770694650986e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_8*S_7*log(1.3846843902855162e-18*S_14)/((1.3846843902855162e-18*S_14 + 1.0)*pow(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10)) + 1.0*S_11*S_13*(-9.1033203897170818e-51*S_14/pow(4.2746565719581312e-19*S_14 + 1.0, 2) + 2.1296027497121323e-32/(4.2746565719581312e-19*S_14 + 1.0));
              double J_8_4 = 5.1945007199592134e-11*S_7 + 1.8706578944791917e-14*S_9;
              double J_8_7 = -2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_8/(1.3846843902855162e-18*S_14 + 1.0) + 5.1945007199592134e-11*S_4;
              double J_8_8 = -2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_7/(1.3846843902855162e-18*S_14 + 1.0) - 3.7190909690468382e-17*S_9 - 1.0*jvals[0];
              double J_8_9 = 1.8706578944791917e-14*S_4 - 3.7190909690468382e-17*S_8;
              double J_8_11 = 1.0*jvals[2];
              double J_8_12 = 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14/(1.3459847134690284e-18*S_14 + 1.0);
              double J_8_14 = -1.6029099488139965e-37*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_12/pow(1.3459847134690284e-18*S_14 + 1.0, 2) + 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_12/(1.3459847134690284e-18*S_14 + 1.0) + 1.9018580488528996e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_12*log(1.3459847134690284e-18*S_14)/((1.3459847134690284e-18*S_14 + 1.0)*pow(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10)) + 3.8321461055530778e-48*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_8*S_7/pow(1.3846843902855162e-18*S_14 + 1.0, 2) - 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_8*S_7/(1.3846843902855162e-18*S_14 + 1.0) - 4.4197770694650986e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_8*S_7*log(1.3846843902855162e-18*S_14)/((1.3846843902855162e-18*S_14 + 1.0)*pow(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10));
              double J_9_4 = -1.8706578944791917e-14*S_9;
              double J_9_5 = 5.6800000000000035e-34*S_14*S_10;
              double J_9_8 = -3.7190909690468382e-17*S_9;
              double J_9_9 = -1.8706578944791917e-14*S_4 - 3.7190909690468382e-17*S_8 - 8.3355554445074843e-15*S_10;
              double J_9_10 = 5.6800000000000035e-34*S_14*S_5 - 8.3355554445074843e-15*S_9;
              double J_9_14 = 5.6800000000000035e-34*S_5*S_10;
              double J_10_5 = -5.6800000000000035e-34*S_14*S_10;
              double J_10_8 = 1.0*jvals[0];
              double J_10_9 = -8.3355554445074843e-15*S_10;
              double J_10_10 = -5.6800000000000035e-34*S_14*S_5 - 8.3355554445074843e-15*S_9;
              double J_10_14 = -5.6800000000000035e-34*S_5*S_10;
              double J_11_11 = -1.0*S_13*(2.1296027497121323e-32*S_14/(4.2746565719581312e-19*S_14 + 1.0) + 9.8568101265494379e-14) - 1.0*jvals[2];
              double J_11_13 = -1.0*S_11*(2.1296027497121323e-32*S_14/(4.2746565719581312e-19*S_14 + 1.0) + 9.8568101265494379e-14);
              double J_11_14 = -1.0*S_11*S_13*(-9.1033203897170818e-51*S_14/pow(4.2746565719581312e-19*S_14 + 1.0, 2) + 2.1296027497121323e-32/(4.2746565719581312e-19*S_14 + 1.0));
              double J_12_7 = 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_8/(1.3846843902855162e-18*S_14 + 1.0);
              double J_12_8 = 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_7/(1.3846843902855162e-18*S_14 + 1.0);
              double J_12_12 = -1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14/(1.3459847134690284e-18*S_14 + 1.0);
              double J_12_14 = 1.6029099488139965e-37*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_12/pow(1.3459847134690284e-18*S_14 + 1.0, 2) - 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_12/(1.3459847134690284e-18*S_14 + 1.0) - 1.9018580488528996e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_12*log(1.3459847134690284e-18*S_14)/((1.3459847134690284e-18*S_14 + 1.0)*pow(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10)) - 3.8321461055530778e-48*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_8*S_7/pow(1.3846843902855162e-18*S_14 + 1.0, 2) + 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_8*S_7/(1.3846843902855162e-18*S_14 + 1.0) + 4.4197770694650986e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_8*S_7*log(1.3846843902855162e-18*S_14)/((1.3846843902855162e-18*S_14 + 1.0)*pow(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10));
              double J_13_6 = 1.0*jvals[1];
              double J_13_11 = -1.0*S_13*(2.1296027497121323e-32*S_14/(4.2746565719581312e-19*S_14 + 1.0) + 9.8568101265494379e-14) + 1.0*jvals[2];
              double J_13_13 = -1.0*S_11*(2.1296027497121323e-32*S_14/(4.2746565719581312e-19*S_14 + 1.0) + 9.8568101265494379e-14);
              double J_13_14 = -1.0*S_11*S_13*(-9.1033203897170818e-51*S_14/pow(4.2746565719581312e-19*S_14 + 1.0, 2) + 2.1296027497121323e-32/(4.2746565719581312e-19*S_14 + 1.0));
              double J_13_15 = 2.0*jvals[3];
              double J_15_14 = 4.7653762320694437e-32*S_16;
              double J_15_15 = -1.0*jvals[3];
              double J_15_16 = 4.7653762320694437e-32*S_14 + 1.6994829027540494e-12;
              double J_16_14 = -4.7653762320694437e-32*S_16;
              double J_16_16 = -4.7653762320694437e-32*S_14 - 1.6994829027540494e-12;

              // Form iteration matrix W = (1/(gamma*h))*I - J
              // Block 0: species [N2, H2O, HNO4, NO, O2, O3]
              double W_0_0 = inv_g_h;
              // Block 1: species [M]
              double W_1_1 = inv_g_h;
              // Block 0: species [N2, H2O, HNO4, NO, O2, O3]
              double W_2_2 = inv_g_h;
              double W_3_3 = inv_g_h;
              double W_4_4 = inv_g_h - J_4_4;
              double W_4_6 = -J_4_6;
              double W_4_7 = -J_4_7;
              double W_4_8 = -J_4_8;
              double W_4_9 = -J_4_9;
              double W_5_5 = inv_g_h;
              // Block 2: species [HONO]
              double W_6_6 = inv_g_h - J_6_6;
              // Block 3: species [NO3, O3P]
              double W_7_4 = -J_7_4;
              double W_7_7 = inv_g_h - J_7_7;
              double W_7_8 = -J_7_8;
              double W_7_9 = -J_7_9;
              double W_7_11 = -J_7_11;
              double W_7_12 = -J_7_12;
              double W_7_13 = -J_7_13;
              double W_7_14 = -J_7_14;
              // Block 4: species [NO2]
              double W_8_4 = -J_8_4;
              double W_8_7 = -J_8_7;
              double W_8_8 = inv_g_h - J_8_8;
              double W_8_9 = -J_8_9;
              double W_8_11 = -J_8_11;
              double W_8_12 = -J_8_12;
              double W_8_14 = -J_8_14;
              // Block 0: species [N2, H2O, HNO4, NO, O2, O3]
              double W_9_4 = -J_9_4;
              double W_9_5 = -J_9_5;
              double W_9_8 = -J_9_8;
              double W_9_9 = inv_g_h - J_9_9;
              double W_9_10 = -J_9_10;
              double W_9_14 = -J_9_14;
              // Block 3: species [NO3, O3P]
              double W_10_5 = -J_10_5;
              double W_10_8 = -J_10_8;
              double W_10_9 = -J_10_9;
              double W_10_10 = inv_g_h - J_10_10;
              double W_10_14 = -J_10_14;
              // Block 5: species [HNO3]
              double W_11_11 = inv_g_h - J_11_11;
              double W_11_13 = -J_11_13;
              double W_11_14 = -J_11_14;
              // Block 6: species [N2O5]
              double W_12_7 = -J_12_7;
              double W_12_8 = -J_12_8;
              double W_12_12 = inv_g_h - J_12_12;
              double W_12_14 = -J_12_14;
              // Block 7: species [OH]
              double W_13_6 = -J_13_6;
              double W_13_11 = -J_13_11;
              double W_13_13 = inv_g_h - J_13_13;
              double W_13_14 = -J_13_14;
              double W_13_15 = -J_13_15;
              // Block 8: species [AIR]
              double W_14_14 = inv_g_h;
              // Block 9: species [H2O2]
              double W_15_14 = -J_15_14;
              double W_15_15 = inv_g_h - J_15_15;
              double W_15_16 = -J_15_16;
              // Block 10: species [HO2]
              double W_16_14 = -J_16_14;
              double W_16_16 = inv_g_h - J_16_16;


              // Symbolic LU Factorization (recomputed at each adjoint step)
              // Block 0: species [N2, H2O, HNO4, NO, O2, O3]
              double U_0_0 = W_0_0;
              // Block 1: species [M]
              double U_1_1 = W_1_1;
              double U_2_2 = W_2_2;
              double U_3_3 = W_3_3;
              double U_4_4 = W_4_4;
              double U_4_6 = W_4_6;
              double U_4_7 = W_4_7;
              double U_4_8 = W_4_8;
              double U_4_9 = W_4_9;
              // Block 3: species [NO3, O3P]
              double L_7_4 = (W_7_4) / U_4_4;
              // Block 4: species [NO2]
              double L_8_4 = (W_8_4) / U_4_4;
              double L_9_4 = (W_9_4) / U_4_4;
              double U_5_5 = W_5_5;
              double L_9_5 = (W_9_5) / U_5_5;
              double L_10_5 = (W_10_5) / U_5_5;
              // Block 2: species [HONO]
              double U_6_6 = W_6_6;
              double L_7_6 = (0.0 - L_7_4 * U_4_6) / U_6_6;
              double L_8_6 = (0.0 - L_8_4 * U_4_6) / U_6_6;
              double L_9_6 = (0.0 - L_9_4 * U_4_6) / U_6_6;
              // Block 7: species [OH]
              double L_13_6 = (W_13_6) / U_6_6;
              double U_7_7 = W_7_7 - L_7_4 * U_4_7;
              double U_7_8 = W_7_8 - L_7_4 * U_4_8;
              double U_7_9 = W_7_9 - L_7_4 * U_4_9;
              double U_7_11 = W_7_11;
              double U_7_12 = W_7_12;
              double U_7_13 = W_7_13;
              double U_7_14 = W_7_14;
              double L_8_7 = (W_8_7 - L_8_4 * U_4_7) / U_7_7;
              double L_9_7 = (0.0 - L_9_4 * U_4_7) / U_7_7;
              // Block 6: species [N2O5]
              double L_12_7 = (W_12_7) / U_7_7;
              double U_8_8 = W_8_8 - L_8_4 * U_4_8 - L_8_7 * U_7_8;
              double U_8_9 = W_8_9 - L_8_4 * U_4_9 - L_8_7 * U_7_9;
              double U_8_11 = W_8_11 - L_8_7 * U_7_11;
              double U_8_12 = W_8_12 - L_8_7 * U_7_12;
              double U_8_13 = 0.0 - L_8_7 * U_7_13;
              double U_8_14 = W_8_14 - L_8_7 * U_7_14;
              double L_9_8 = (W_9_8 - L_9_4 * U_4_8 - L_9_7 * U_7_8) / U_8_8;
              double L_10_8 = (W_10_8) / U_8_8;
              double L_12_8 = (W_12_8 - L_12_7 * U_7_8) / U_8_8;
              double U_9_9 = W_9_9 - L_9_4 * U_4_9 - L_9_7 * U_7_9 - L_9_8 * U_8_9;
              double U_9_10 = W_9_10;
              double U_9_11 = 0.0 - L_9_7 * U_7_11 - L_9_8 * U_8_11;
              double U_9_12 = 0.0 - L_9_7 * U_7_12 - L_9_8 * U_8_12;
              double U_9_13 = 0.0 - L_9_7 * U_7_13 - L_9_8 * U_8_13;
              double U_9_14 = W_9_14 - L_9_7 * U_7_14 - L_9_8 * U_8_14;
              double L_10_9 = (W_10_9 - L_10_8 * U_8_9) / U_9_9;
              double L_12_9 = (0.0 - L_12_7 * U_7_9 - L_12_8 * U_8_9) / U_9_9;
              double U_10_10 = W_10_10 - L_10_9 * U_9_10;
              double U_10_11 = 0.0 - L_10_8 * U_8_11 - L_10_9 * U_9_11;
              double U_10_12 = 0.0 - L_10_8 * U_8_12 - L_10_9 * U_9_12;
              double U_10_13 = 0.0 - L_10_8 * U_8_13 - L_10_9 * U_9_13;
              double U_10_14 = W_10_14 - L_10_8 * U_8_14 - L_10_9 * U_9_14;
              double L_12_10 = (0.0 - L_12_9 * U_9_10) / U_10_10;
              // Block 5: species [HNO3]
              double U_11_11 = W_11_11;
              double U_11_13 = W_11_13;
              double U_11_14 = W_11_14;
              double L_12_11 = (0.0 - L_12_7 * U_7_11 - L_12_8 * U_8_11 - L_12_9 * U_9_11 - L_12_10 * U_10_11) / U_11_11;
              double L_13_11 = (W_13_11) / U_11_11;
              double U_12_12 = W_12_12 - L_12_7 * U_7_12 - L_12_8 * U_8_12 - L_12_9 * U_9_12 - L_12_10 * U_10_12;
              double U_12_13 = 0.0 - L_12_7 * U_7_13 - L_12_8 * U_8_13 - L_12_9 * U_9_13 - L_12_10 * U_10_13 - L_12_11 * U_11_13;
              double U_12_14 = W_12_14 - L_12_7 * U_7_14 - L_12_8 * U_8_14 - L_12_9 * U_9_14 - L_12_10 * U_10_14 - L_12_11 * U_11_14;
              double U_13_13 = W_13_13 - L_13_11 * U_11_13;
              double U_13_14 = W_13_14 - L_13_11 * U_11_14;
              double U_13_15 = W_13_15;
              // Block 8: species [AIR]
              double U_14_14 = W_14_14;
              // Block 9: species [H2O2]
              double L_15_14 = (W_15_14) / U_14_14;
              // Block 10: species [HO2]
              double L_16_14 = (W_16_14) / U_14_14;
              double U_15_15 = W_15_15;
              double U_15_16 = W_15_16;
              double U_16_16 = W_16_16;


              // --- Adjoint stage unrolling (s=3 stages, backward) ---
              // Driving vector: lam_k = lambda_{n+1} (constant for this step)
              const double lam_0 = lambda(0);
              const double lam_1 = lambda(1);
              const double lam_2 = lambda(2);
              const double lam_3 = lambda(3);
              const double lam_4 = lambda(4);
              const double lam_5 = lambda(5);
              const double lam_6 = lambda(6);
              const double lam_7 = lambda(7);
              const double lam_8 = lambda(8);
              const double lam_9 = lambda(9);
              const double lam_10 = lambda(10);
              const double lam_11 = lambda(11);
              const double lam_12 = lambda(12);
              const double lam_13 = lambda(13);
              const double lam_14 = lambda(14);
              const double lam_15 = lambda(15);
              const double lam_16 = lambda(16);

              // Adjoint stage 3
              // v3: RHS for W^{-T} solve
              double v3_0 = -0.42772256543218573 * lam_0;
              double v3_1 = -0.42772256543218573 * lam_1;
              double v3_2 = -0.42772256543218573 * lam_2;
              double v3_3 = -0.42772256543218573 * lam_3;
              double v3_4 = -0.42772256543218573 * lam_4;
              double v3_5 = -0.42772256543218573 * lam_5;
              double v3_6 = -0.42772256543218573 * lam_6;
              double v3_7 = -0.42772256543218573 * lam_7;
              double v3_8 = -0.42772256543218573 * lam_8;
              double v3_9 = -0.42772256543218573 * lam_9;
              double v3_10 = -0.42772256543218573 * lam_10;
              double v3_11 = -0.42772256543218573 * lam_11;
              double v3_12 = -0.42772256543218573 * lam_12;
              double v3_13 = -0.42772256543218573 * lam_13;
              double v3_14 = -0.42772256543218573 * lam_14;
              double v3_15 = -0.42772256543218573 * lam_15;
              double v3_16 = -0.42772256543218573 * lam_16;
              // W^{-T} solve for u3
              // Block 0: u3 transpose forward sub [N2, H2O, HNO4, NO, O2, O3]
              double yt3_0 = v3_0 / U_0_0;
              // Block 1: u3 transpose forward sub [M]
              double yt3_1 = v3_1 / U_1_1;
              double yt3_2 = v3_2 / U_2_2;
              double yt3_3 = v3_3 / U_3_3;
              double yt3_4 = v3_4 / U_4_4;
              double yt3_5 = v3_5 / U_5_5;
              // Block 2: u3 transpose forward sub [HONO]
              double yt3_6 = (v3_6 - U_4_6 * yt3_4) / U_6_6;
              // Block 3: u3 transpose forward sub [NO3, O3P]
              double yt3_7 = (v3_7 - U_4_7 * yt3_4) / U_7_7;
              // Block 4: u3 transpose forward sub [NO2]
              double yt3_8 = (v3_8 - U_4_8 * yt3_4 - U_7_8 * yt3_7) / U_8_8;
              double yt3_9 = (v3_9 - U_4_9 * yt3_4 - U_7_9 * yt3_7 - U_8_9 * yt3_8) / U_9_9;
              double yt3_10 = (v3_10 - U_9_10 * yt3_9) / U_10_10;
              // Block 5: u3 transpose forward sub [HNO3]
              double yt3_11 = (v3_11 - U_7_11 * yt3_7 - U_8_11 * yt3_8 - U_9_11 * yt3_9 - U_10_11 * yt3_10) / U_11_11;
              // Block 6: u3 transpose forward sub [N2O5]
              double yt3_12 = (v3_12 - U_7_12 * yt3_7 - U_8_12 * yt3_8 - U_9_12 * yt3_9 - U_10_12 * yt3_10) / U_12_12;
              // Block 7: u3 transpose forward sub [OH]
              double yt3_13 = (v3_13 - U_7_13 * yt3_7 - U_8_13 * yt3_8 - U_9_13 * yt3_9 - U_10_13 * yt3_10 - U_11_13 * yt3_11 - U_12_13 * yt3_12) / U_13_13;
              // Block 8: u3 transpose forward sub [AIR]
              double yt3_14 = (v3_14 - U_7_14 * yt3_7 - U_8_14 * yt3_8 - U_9_14 * yt3_9 - U_10_14 * yt3_10 - U_11_14 * yt3_11 - U_12_14 * yt3_12 - U_13_14 * yt3_13) / U_14_14;
              // Block 9: u3 transpose forward sub [H2O2]
              double yt3_15 = (v3_15 - U_13_15 * yt3_13) / U_15_15;
              // Block 10: u3 transpose forward sub [HO2]
              double yt3_16 = (v3_16 - U_15_16 * yt3_15) / U_16_16;
              // Block 10: u3 transpose backward sub [HO2]
              double u3_16 = yt3_16;
              // Block 9: u3 transpose backward sub [H2O2]
              double u3_15 = yt3_15;
              // Block 8: u3 transpose backward sub [AIR]
              double u3_14 = yt3_14 - L_15_14 * u3_15 - L_16_14 * u3_16;
              // Block 7: u3 transpose backward sub [OH]
              double u3_13 = yt3_13;
              // Block 6: u3 transpose backward sub [N2O5]
              double u3_12 = yt3_12;
              // Block 5: u3 transpose backward sub [HNO3]
              double u3_11 = yt3_11 - L_12_11 * u3_12 - L_13_11 * u3_13;
              // Block 3: u3 transpose backward sub [NO3, O3P]
              double u3_10 = yt3_10 - L_12_10 * u3_12;
              // Block 0: u3 transpose backward sub [N2, H2O, HNO4, NO, O2, O3]
              double u3_9 = yt3_9 - L_10_9 * u3_10 - L_12_9 * u3_12;
              // Block 4: u3 transpose backward sub [NO2]
              double u3_8 = yt3_8 - L_9_8 * u3_9 - L_10_8 * u3_10 - L_12_8 * u3_12;
              double u3_7 = yt3_7 - L_8_7 * u3_8 - L_9_7 * u3_9 - L_12_7 * u3_12;
              // Block 2: u3 transpose backward sub [HONO]
              double u3_6 = yt3_6 - L_7_6 * u3_7 - L_8_6 * u3_8 - L_9_6 * u3_9 - L_13_6 * u3_13;
              double u3_5 = yt3_5 - L_9_5 * u3_9 - L_10_5 * u3_10;
              double u3_4 = yt3_4 - L_7_4 * u3_7 - L_8_4 * u3_8 - L_9_4 * u3_9;
              double u3_3 = yt3_3;
              double u3_2 = yt3_2;
              // Block 1: u3 transpose backward sub [M]
              double u3_1 = yt3_1;
              double u3_0 = yt3_0;


              // Adjoint stage 2
              // v2: RHS for W^{-T} solve
              double v2_0 = 6.1697947043828245 * lam_0 + (9.20767942983308 / h) * u3_0;
              double v2_1 = 6.1697947043828245 * lam_1 + (9.20767942983308 / h) * u3_1;
              double v2_2 = 6.1697947043828245 * lam_2 + (9.20767942983308 / h) * u3_2;
              double v2_3 = 6.1697947043828245 * lam_3 + (9.20767942983308 / h) * u3_3;
              double v2_4 = 6.1697947043828245 * lam_4 + (9.20767942983308 / h) * u3_4;
              double v2_5 = 6.1697947043828245 * lam_5 + (9.20767942983308 / h) * u3_5;
              double v2_6 = 6.1697947043828245 * lam_6 + (9.20767942983308 / h) * u3_6;
              double v2_7 = 6.1697947043828245 * lam_7 + (9.20767942983308 / h) * u3_7;
              double v2_8 = 6.1697947043828245 * lam_8 + (9.20767942983308 / h) * u3_8;
              double v2_9 = 6.1697947043828245 * lam_9 + (9.20767942983308 / h) * u3_9;
              double v2_10 = 6.1697947043828245 * lam_10 + (9.20767942983308 / h) * u3_10;
              double v2_11 = 6.1697947043828245 * lam_11 + (9.20767942983308 / h) * u3_11;
              double v2_12 = 6.1697947043828245 * lam_12 + (9.20767942983308 / h) * u3_12;
              double v2_13 = 6.1697947043828245 * lam_13 + (9.20767942983308 / h) * u3_13;
              double v2_14 = 6.1697947043828245 * lam_14 + (9.20767942983308 / h) * u3_14;
              double v2_15 = 6.1697947043828245 * lam_15 + (9.20767942983308 / h) * u3_15;
              double v2_16 = 6.1697947043828245 * lam_16 + (9.20767942983308 / h) * u3_16;
              // W^{-T} solve for u2
              // Block 0: u2 transpose forward sub [N2, H2O, HNO4, NO, O2, O3]
              double yt2_0 = v2_0 / U_0_0;
              // Block 1: u2 transpose forward sub [M]
              double yt2_1 = v2_1 / U_1_1;
              double yt2_2 = v2_2 / U_2_2;
              double yt2_3 = v2_3 / U_3_3;
              double yt2_4 = v2_4 / U_4_4;
              double yt2_5 = v2_5 / U_5_5;
              // Block 2: u2 transpose forward sub [HONO]
              double yt2_6 = (v2_6 - U_4_6 * yt2_4) / U_6_6;
              // Block 3: u2 transpose forward sub [NO3, O3P]
              double yt2_7 = (v2_7 - U_4_7 * yt2_4) / U_7_7;
              // Block 4: u2 transpose forward sub [NO2]
              double yt2_8 = (v2_8 - U_4_8 * yt2_4 - U_7_8 * yt2_7) / U_8_8;
              double yt2_9 = (v2_9 - U_4_9 * yt2_4 - U_7_9 * yt2_7 - U_8_9 * yt2_8) / U_9_9;
              double yt2_10 = (v2_10 - U_9_10 * yt2_9) / U_10_10;
              // Block 5: u2 transpose forward sub [HNO3]
              double yt2_11 = (v2_11 - U_7_11 * yt2_7 - U_8_11 * yt2_8 - U_9_11 * yt2_9 - U_10_11 * yt2_10) / U_11_11;
              // Block 6: u2 transpose forward sub [N2O5]
              double yt2_12 = (v2_12 - U_7_12 * yt2_7 - U_8_12 * yt2_8 - U_9_12 * yt2_9 - U_10_12 * yt2_10) / U_12_12;
              // Block 7: u2 transpose forward sub [OH]
              double yt2_13 = (v2_13 - U_7_13 * yt2_7 - U_8_13 * yt2_8 - U_9_13 * yt2_9 - U_10_13 * yt2_10 - U_11_13 * yt2_11 - U_12_13 * yt2_12) / U_13_13;
              // Block 8: u2 transpose forward sub [AIR]
              double yt2_14 = (v2_14 - U_7_14 * yt2_7 - U_8_14 * yt2_8 - U_9_14 * yt2_9 - U_10_14 * yt2_10 - U_11_14 * yt2_11 - U_12_14 * yt2_12 - U_13_14 * yt2_13) / U_14_14;
              // Block 9: u2 transpose forward sub [H2O2]
              double yt2_15 = (v2_15 - U_13_15 * yt2_13) / U_15_15;
              // Block 10: u2 transpose forward sub [HO2]
              double yt2_16 = (v2_16 - U_15_16 * yt2_15) / U_16_16;
              // Block 10: u2 transpose backward sub [HO2]
              double u2_16 = yt2_16;
              // Block 9: u2 transpose backward sub [H2O2]
              double u2_15 = yt2_15;
              // Block 8: u2 transpose backward sub [AIR]
              double u2_14 = yt2_14 - L_15_14 * u2_15 - L_16_14 * u2_16;
              // Block 7: u2 transpose backward sub [OH]
              double u2_13 = yt2_13;
              // Block 6: u2 transpose backward sub [N2O5]
              double u2_12 = yt2_12;
              // Block 5: u2 transpose backward sub [HNO3]
              double u2_11 = yt2_11 - L_12_11 * u2_12 - L_13_11 * u2_13;
              // Block 3: u2 transpose backward sub [NO3, O3P]
              double u2_10 = yt2_10 - L_12_10 * u2_12;
              // Block 0: u2 transpose backward sub [N2, H2O, HNO4, NO, O2, O3]
              double u2_9 = yt2_9 - L_10_9 * u2_10 - L_12_9 * u2_12;
              // Block 4: u2 transpose backward sub [NO2]
              double u2_8 = yt2_8 - L_9_8 * u2_9 - L_10_8 * u2_10 - L_12_8 * u2_12;
              double u2_7 = yt2_7 - L_8_7 * u2_8 - L_9_7 * u2_9 - L_12_7 * u2_12;
              // Block 2: u2 transpose backward sub [HONO]
              double u2_6 = yt2_6 - L_7_6 * u2_7 - L_8_6 * u2_8 - L_9_6 * u2_9 - L_13_6 * u2_13;
              double u2_5 = yt2_5 - L_9_5 * u2_9 - L_10_5 * u2_10;
              double u2_4 = yt2_4 - L_7_4 * u2_7 - L_8_4 * u2_8 - L_9_4 * u2_9;
              double u2_3 = yt2_3;
              double u2_2 = yt2_2;
              // Block 1: u2 transpose backward sub [M]
              double u2_1 = yt2_1;
              double u2_0 = yt2_0;


              // Adjoint stage 1
              // v1: RHS for W^{-T} solve
              double v1_0 = lam_0 + (-1.0156171083877703 / h) * u2_0 + (4.0759956452537702 / h) * u3_0;
              double v1_1 = lam_1 + (-1.0156171083877703 / h) * u2_1 + (4.0759956452537702 / h) * u3_1;
              double v1_2 = lam_2 + (-1.0156171083877703 / h) * u2_2 + (4.0759956452537702 / h) * u3_2;
              double v1_3 = lam_3 + (-1.0156171083877703 / h) * u2_3 + (4.0759956452537702 / h) * u3_3;
              double v1_4 = lam_4 + (J_4_4 * u2_4 + J_7_4 * u2_7 + J_8_4 * u2_8 + J_9_4 * u2_9) + (-1.0156171083877703 / h) * u2_4 + (J_4_4 * u3_4 + J_7_4 * u3_7 + J_8_4 * u3_8 + J_9_4 * u3_9) + (4.0759956452537702 / h) * u3_4;
              double v1_5 = lam_5 + (J_9_5 * u2_9 + J_10_5 * u2_10) + (-1.0156171083877703 / h) * u2_5 + (J_9_5 * u3_9 + J_10_5 * u3_10) + (4.0759956452537702 / h) * u3_5;
              double v1_6 = lam_6 + (J_4_6 * u2_4 + J_6_6 * u2_6 + J_13_6 * u2_13) + (-1.0156171083877703 / h) * u2_6 + (J_4_6 * u3_4 + J_6_6 * u3_6 + J_13_6 * u3_13) + (4.0759956452537702 / h) * u3_6;
              double v1_7 = lam_7 + (J_4_7 * u2_4 + J_7_7 * u2_7 + J_8_7 * u2_8 + J_12_7 * u2_12) + (-1.0156171083877703 / h) * u2_7 + (J_4_7 * u3_4 + J_7_7 * u3_7 + J_8_7 * u3_8 + J_12_7 * u3_12) + (4.0759956452537702 / h) * u3_7;
              double v1_8 = lam_8 + (J_4_8 * u2_4 + J_7_8 * u2_7 + J_8_8 * u2_8 + J_9_8 * u2_9 + J_10_8 * u2_10 + J_12_8 * u2_12) + (-1.0156171083877703 / h) * u2_8 + (J_4_8 * u3_4 + J_7_8 * u3_7 + J_8_8 * u3_8 + J_9_8 * u3_9 + J_10_8 * u3_10 + J_12_8 * u3_12) + (4.0759956452537702 / h) * u3_8;
              double v1_9 = lam_9 + (J_4_9 * u2_4 + J_7_9 * u2_7 + J_8_9 * u2_8 + J_9_9 * u2_9 + J_10_9 * u2_10) + (-1.0156171083877703 / h) * u2_9 + (J_4_9 * u3_4 + J_7_9 * u3_7 + J_8_9 * u3_8 + J_9_9 * u3_9 + J_10_9 * u3_10) + (4.0759956452537702 / h) * u3_9;
              double v1_10 = lam_10 + (J_9_10 * u2_9 + J_10_10 * u2_10) + (-1.0156171083877703 / h) * u2_10 + (J_9_10 * u3_9 + J_10_10 * u3_10) + (4.0759956452537702 / h) * u3_10;
              double v1_11 = lam_11 + (J_7_11 * u2_7 + J_8_11 * u2_8 + J_11_11 * u2_11 + J_13_11 * u2_13) + (-1.0156171083877703 / h) * u2_11 + (J_7_11 * u3_7 + J_8_11 * u3_8 + J_11_11 * u3_11 + J_13_11 * u3_13) + (4.0759956452537702 / h) * u3_11;
              double v1_12 = lam_12 + (J_7_12 * u2_7 + J_8_12 * u2_8 + J_12_12 * u2_12) + (-1.0156171083877703 / h) * u2_12 + (J_7_12 * u3_7 + J_8_12 * u3_8 + J_12_12 * u3_12) + (4.0759956452537702 / h) * u3_12;
              double v1_13 = lam_13 + (J_7_13 * u2_7 + J_11_13 * u2_11 + J_13_13 * u2_13) + (-1.0156171083877703 / h) * u2_13 + (J_7_13 * u3_7 + J_11_13 * u3_11 + J_13_13 * u3_13) + (4.0759956452537702 / h) * u3_13;
              double v1_14 = lam_14 + (J_7_14 * u2_7 + J_8_14 * u2_8 + J_9_14 * u2_9 + J_10_14 * u2_10 + J_11_14 * u2_11 + J_12_14 * u2_12 + J_13_14 * u2_13 + J_15_14 * u2_15 + J_16_14 * u2_16) + (-1.0156171083877703 / h) * u2_14 + (J_7_14 * u3_7 + J_8_14 * u3_8 + J_9_14 * u3_9 + J_10_14 * u3_10 + J_11_14 * u3_11 + J_12_14 * u3_12 + J_13_14 * u3_13 + J_15_14 * u3_15 + J_16_14 * u3_16) + (4.0759956452537702 / h) * u3_14;
              double v1_15 = lam_15 + (J_13_15 * u2_13 + J_15_15 * u2_15) + (-1.0156171083877703 / h) * u2_15 + (J_13_15 * u3_13 + J_15_15 * u3_15) + (4.0759956452537702 / h) * u3_15;
              double v1_16 = lam_16 + (J_15_16 * u2_15 + J_16_16 * u2_16) + (-1.0156171083877703 / h) * u2_16 + (J_15_16 * u3_15 + J_16_16 * u3_16) + (4.0759956452537702 / h) * u3_16;
              // W^{-T} solve for u1
              // Block 0: u1 transpose forward sub [N2, H2O, HNO4, NO, O2, O3]
              double yt1_0 = v1_0 / U_0_0;
              // Block 1: u1 transpose forward sub [M]
              double yt1_1 = v1_1 / U_1_1;
              double yt1_2 = v1_2 / U_2_2;
              double yt1_3 = v1_3 / U_3_3;
              double yt1_4 = v1_4 / U_4_4;
              double yt1_5 = v1_5 / U_5_5;
              // Block 2: u1 transpose forward sub [HONO]
              double yt1_6 = (v1_6 - U_4_6 * yt1_4) / U_6_6;
              // Block 3: u1 transpose forward sub [NO3, O3P]
              double yt1_7 = (v1_7 - U_4_7 * yt1_4) / U_7_7;
              // Block 4: u1 transpose forward sub [NO2]
              double yt1_8 = (v1_8 - U_4_8 * yt1_4 - U_7_8 * yt1_7) / U_8_8;
              double yt1_9 = (v1_9 - U_4_9 * yt1_4 - U_7_9 * yt1_7 - U_8_9 * yt1_8) / U_9_9;
              double yt1_10 = (v1_10 - U_9_10 * yt1_9) / U_10_10;
              // Block 5: u1 transpose forward sub [HNO3]
              double yt1_11 = (v1_11 - U_7_11 * yt1_7 - U_8_11 * yt1_8 - U_9_11 * yt1_9 - U_10_11 * yt1_10) / U_11_11;
              // Block 6: u1 transpose forward sub [N2O5]
              double yt1_12 = (v1_12 - U_7_12 * yt1_7 - U_8_12 * yt1_8 - U_9_12 * yt1_9 - U_10_12 * yt1_10) / U_12_12;
              // Block 7: u1 transpose forward sub [OH]
              double yt1_13 = (v1_13 - U_7_13 * yt1_7 - U_8_13 * yt1_8 - U_9_13 * yt1_9 - U_10_13 * yt1_10 - U_11_13 * yt1_11 - U_12_13 * yt1_12) / U_13_13;
              // Block 8: u1 transpose forward sub [AIR]
              double yt1_14 = (v1_14 - U_7_14 * yt1_7 - U_8_14 * yt1_8 - U_9_14 * yt1_9 - U_10_14 * yt1_10 - U_11_14 * yt1_11 - U_12_14 * yt1_12 - U_13_14 * yt1_13) / U_14_14;
              // Block 9: u1 transpose forward sub [H2O2]
              double yt1_15 = (v1_15 - U_13_15 * yt1_13) / U_15_15;
              // Block 10: u1 transpose forward sub [HO2]
              double yt1_16 = (v1_16 - U_15_16 * yt1_15) / U_16_16;
              // Block 10: u1 transpose backward sub [HO2]
              double u1_16 = yt1_16;
              // Block 9: u1 transpose backward sub [H2O2]
              double u1_15 = yt1_15;
              // Block 8: u1 transpose backward sub [AIR]
              double u1_14 = yt1_14 - L_15_14 * u1_15 - L_16_14 * u1_16;
              // Block 7: u1 transpose backward sub [OH]
              double u1_13 = yt1_13;
              // Block 6: u1 transpose backward sub [N2O5]
              double u1_12 = yt1_12;
              // Block 5: u1 transpose backward sub [HNO3]
              double u1_11 = yt1_11 - L_12_11 * u1_12 - L_13_11 * u1_13;
              // Block 3: u1 transpose backward sub [NO3, O3P]
              double u1_10 = yt1_10 - L_12_10 * u1_12;
              // Block 0: u1 transpose backward sub [N2, H2O, HNO4, NO, O2, O3]
              double u1_9 = yt1_9 - L_10_9 * u1_10 - L_12_9 * u1_12;
              // Block 4: u1 transpose backward sub [NO2]
              double u1_8 = yt1_8 - L_9_8 * u1_9 - L_10_8 * u1_10 - L_12_8 * u1_12;
              double u1_7 = yt1_7 - L_8_7 * u1_8 - L_9_7 * u1_9 - L_12_7 * u1_12;
              // Block 2: u1 transpose backward sub [HONO]
              double u1_6 = yt1_6 - L_7_6 * u1_7 - L_8_6 * u1_8 - L_9_6 * u1_9 - L_13_6 * u1_13;
              double u1_5 = yt1_5 - L_9_5 * u1_9 - L_10_5 * u1_10;
              double u1_4 = yt1_4 - L_7_4 * u1_7 - L_8_4 * u1_8 - L_9_4 * u1_9;
              double u1_3 = yt1_3;
              double u1_2 = yt1_2;
              // Block 1: u1 transpose backward sub [M]
              double u1_1 = yt1_1;
              double u1_0 = yt1_0;


              // --- Lambda update: lambda_n = lambda_{n+1} + Σ u_i ---
              lambda(0) = lam_0 + u1_0 + u2_0 + u3_0;
              lambda(1) = lam_1 + u1_1 + u2_1 + u3_1;
              lambda(2) = lam_2 + u1_2 + u2_2 + u3_2;
              lambda(3) = lam_3 + u1_3 + u2_3 + u3_3;
              lambda(4) = lam_4 + u1_4 + u2_4 + u3_4;
              lambda(5) = lam_5 + u1_5 + u2_5 + u3_5;
              lambda(6) = lam_6 + u1_6 + u2_6 + u3_6;
              lambda(7) = lam_7 + u1_7 + u2_7 + u3_7;
              lambda(8) = lam_8 + u1_8 + u2_8 + u3_8;
              lambda(9) = lam_9 + u1_9 + u2_9 + u3_9;
              lambda(10) = lam_10 + u1_10 + u2_10 + u3_10;
              lambda(11) = lam_11 + u1_11 + u2_11 + u3_11;
              lambda(12) = lam_12 + u1_12 + u2_12 + u3_12;
              lambda(13) = lam_13 + u1_13 + u2_13 + u3_13;
              lambda(14) = lam_14 + u1_14 + u2_14 + u3_14;
              lambda(15) = lam_15 + u1_15 + u2_15 + u3_15;
              lambda(16) = lam_16 + u1_16 + u2_16 + u3_16;
          } // end for (step)
      }

      // Tangent Linear Model: forward propagation of perturbation δC
      // Uses checkpoint buffer from integrate_fwd_checkpoint().
      template <class StateView, class PertView>
      KOKKOS_INLINE_FUNCTION void integrate_tlm(
          double dt_total, const StateView& state_0,
          PertView& delta_C, const double* jvals,
          const CheckpointBuffer& chk) const
      {
          const double g = 0.435866521508459;

          // Local aliases for delta_C (TLM stages use dC_k naming)
          double dC_0 = delta_C(0);
          double dC_1 = delta_C(1);
          double dC_2 = delta_C(2);
          double dC_3 = delta_C(3);
          double dC_4 = delta_C(4);
          double dC_5 = delta_C(5);
          double dC_6 = delta_C(6);
          double dC_7 = delta_C(7);
          double dC_8 = delta_C(8);
          double dC_9 = delta_C(9);
          double dC_10 = delta_C(10);
          double dC_11 = delta_C(11);
          double dC_12 = delta_C(12);
          double dC_13 = delta_C(13);
          double dC_14 = delta_C(14);
          double dC_15 = delta_C(15);
          double dC_16 = delta_C(16);


          // === TLM Forward Propagation ===
          for (int step = 0; step < chk.num_steps; step++) {
              const double h = chk.h[step];
              const double inv_g_h = 1.0 / (0.435866521508459 * h);

              // Reload checkpointed state
              const double S_0 = chk.state[step][0];
              const double S_1 = chk.state[step][1];
              const double S_2 = chk.state[step][2];
              const double S_3 = chk.state[step][3];
              const double S_4 = chk.state[step][4];
              const double S_5 = chk.state[step][5];
              const double S_6 = chk.state[step][6];
              const double S_7 = chk.state[step][7];
              const double S_8 = chk.state[step][8];
              const double S_9 = chk.state[step][9];
              const double S_10 = chk.state[step][10];
              const double S_11 = chk.state[step][11];
              const double S_12 = chk.state[step][12];
              const double S_13 = chk.state[step][13];
              const double S_14 = chk.state[step][14];
              const double S_15 = chk.state[step][15];
              const double S_16 = chk.state[step][16];

              // Recompute Jacobian at checkpointed state (recompute-J strategy, D1)
              double J_4_4 = -2.5972503599796067e-11*S_7 - 1.8706578944791917e-14*S_9;
              double J_4_6 = 1.0*jvals[1];
              double J_4_7 = -2.5972503599796067e-11*S_4;
              double J_4_8 = 1.0*jvals[0];
              double J_4_9 = -1.8706578944791917e-14*S_4;
              double J_6_6 = -1.0*jvals[1];
              double J_7_4 = -2.5972503599796067e-11*S_7;
              double J_7_7 = -2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_8/(1.3846843902855162e-18*S_14 + 1.0) - 2.5972503599796067e-11*S_4;
              double J_7_8 = -2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_7/(1.3846843902855162e-18*S_14 + 1.0) + 3.7190909690468382e-17*S_9;
              double J_7_9 = 3.7190909690468382e-17*S_8;
              double J_7_11 = 1.0*S_13*(2.1296027497121323e-32*S_14/(4.2746565719581312e-19*S_14 + 1.0) + 9.8568101265494379e-14);
              double J_7_12 = 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14/(1.3459847134690284e-18*S_14 + 1.0);
              double J_7_13 = 1.0*S_11*(2.1296027497121323e-32*S_14/(4.2746565719581312e-19*S_14 + 1.0) + 9.8568101265494379e-14);
              double J_7_14 = -1.6029099488139965e-37*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_12/pow(1.3459847134690284e-18*S_14 + 1.0, 2) + 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_12/(1.3459847134690284e-18*S_14 + 1.0) + 1.9018580488528996e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_12*log(1.3459847134690284e-18*S_14)/((1.3459847134690284e-18*S_14 + 1.0)*pow(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10)) + 3.8321461055530778e-48*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_8*S_7/pow(1.3846843902855162e-18*S_14 + 1.0, 2) - 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_8*S_7/(1.3846843902855162e-18*S_14 + 1.0) - 4.4197770694650986e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_8*S_7*log(1.3846843902855162e-18*S_14)/((1.3846843902855162e-18*S_14 + 1.0)*pow(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10)) + 1.0*S_11*S_13*(-9.1033203897170818e-51*S_14/pow(4.2746565719581312e-19*S_14 + 1.0, 2) + 2.1296027497121323e-32/(4.2746565719581312e-19*S_14 + 1.0));
              double J_8_4 = 5.1945007199592134e-11*S_7 + 1.8706578944791917e-14*S_9;
              double J_8_7 = -2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_8/(1.3846843902855162e-18*S_14 + 1.0) + 5.1945007199592134e-11*S_4;
              double J_8_8 = -2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_7/(1.3846843902855162e-18*S_14 + 1.0) - 3.7190909690468382e-17*S_9 - 1.0*jvals[0];
              double J_8_9 = 1.8706578944791917e-14*S_4 - 3.7190909690468382e-17*S_8;
              double J_8_11 = 1.0*jvals[2];
              double J_8_12 = 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14/(1.3459847134690284e-18*S_14 + 1.0);
              double J_8_14 = -1.6029099488139965e-37*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_12/pow(1.3459847134690284e-18*S_14 + 1.0, 2) + 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_12/(1.3459847134690284e-18*S_14 + 1.0) + 1.9018580488528996e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_12*log(1.3459847134690284e-18*S_14)/((1.3459847134690284e-18*S_14 + 1.0)*pow(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10)) + 3.8321461055530778e-48*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_8*S_7/pow(1.3846843902855162e-18*S_14 + 1.0, 2) - 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_8*S_7/(1.3846843902855162e-18*S_14 + 1.0) - 4.4197770694650986e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_8*S_7*log(1.3846843902855162e-18*S_14)/((1.3846843902855162e-18*S_14 + 1.0)*pow(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10));
              double J_9_4 = -1.8706578944791917e-14*S_9;
              double J_9_5 = 5.6800000000000035e-34*S_14*S_10;
              double J_9_8 = -3.7190909690468382e-17*S_9;
              double J_9_9 = -1.8706578944791917e-14*S_4 - 3.7190909690468382e-17*S_8 - 8.3355554445074843e-15*S_10;
              double J_9_10 = 5.6800000000000035e-34*S_14*S_5 - 8.3355554445074843e-15*S_9;
              double J_9_14 = 5.6800000000000035e-34*S_5*S_10;
              double J_10_5 = -5.6800000000000035e-34*S_14*S_10;
              double J_10_8 = 1.0*jvals[0];
              double J_10_9 = -8.3355554445074843e-15*S_10;
              double J_10_10 = -5.6800000000000035e-34*S_14*S_5 - 8.3355554445074843e-15*S_9;
              double J_10_14 = -5.6800000000000035e-34*S_5*S_10;
              double J_11_11 = -1.0*S_13*(2.1296027497121323e-32*S_14/(4.2746565719581312e-19*S_14 + 1.0) + 9.8568101265494379e-14) - 1.0*jvals[2];
              double J_11_13 = -1.0*S_11*(2.1296027497121323e-32*S_14/(4.2746565719581312e-19*S_14 + 1.0) + 9.8568101265494379e-14);
              double J_11_14 = -1.0*S_11*S_13*(-9.1033203897170818e-51*S_14/pow(4.2746565719581312e-19*S_14 + 1.0, 2) + 2.1296027497121323e-32/(4.2746565719581312e-19*S_14 + 1.0));
              double J_12_7 = 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_8/(1.3846843902855162e-18*S_14 + 1.0);
              double J_12_8 = 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_7/(1.3846843902855162e-18*S_14 + 1.0);
              double J_12_12 = -1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14/(1.3459847134690284e-18*S_14 + 1.0);
              double J_12_14 = 1.6029099488139965e-37*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_12/pow(1.3459847134690284e-18*S_14 + 1.0, 2) - 1.1908827290339734e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_12/(1.3459847134690284e-18*S_14 + 1.0) - 1.9018580488528996e-19*pow(0.45000000000000001, 1.0/(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_12*log(1.3459847134690284e-18*S_14)/((1.3459847134690284e-18*S_14 + 1.0)*pow(pow(log(1.3459847134690284e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10)) - 3.8321461055530778e-48*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_14*S_8*S_7/pow(1.3846843902855162e-18*S_14 + 1.0, 2) + 2.7675231499958668e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_8*S_7/(1.3846843902855162e-18*S_14 + 1.0) + 4.4197770694650986e-30*pow(0.45000000000000001, 1.0/(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0))*S_8*S_7*log(1.3846843902855162e-18*S_14)/((1.3846843902855162e-18*S_14 + 1.0)*pow(pow(log(1.3846843902855162e-18*S_14), 2)/(M_LN10 * M_LN10) + 1.0, 2)*(M_LN10 * M_LN10));
              double J_13_6 = 1.0*jvals[1];
              double J_13_11 = -1.0*S_13*(2.1296027497121323e-32*S_14/(4.2746565719581312e-19*S_14 + 1.0) + 9.8568101265494379e-14) + 1.0*jvals[2];
              double J_13_13 = -1.0*S_11*(2.1296027497121323e-32*S_14/(4.2746565719581312e-19*S_14 + 1.0) + 9.8568101265494379e-14);
              double J_13_14 = -1.0*S_11*S_13*(-9.1033203897170818e-51*S_14/pow(4.2746565719581312e-19*S_14 + 1.0, 2) + 2.1296027497121323e-32/(4.2746565719581312e-19*S_14 + 1.0));
              double J_13_15 = 2.0*jvals[3];
              double J_15_14 = 4.7653762320694437e-32*S_16;
              double J_15_15 = -1.0*jvals[3];
              double J_15_16 = 4.7653762320694437e-32*S_14 + 1.6994829027540494e-12;
              double J_16_14 = -4.7653762320694437e-32*S_16;
              double J_16_16 = -4.7653762320694437e-32*S_14 - 1.6994829027540494e-12;

              // Form iteration matrix W = inv_g_h*I - J
              double W_0_0 = inv_g_h;
              double W_1_1 = inv_g_h;
              double W_2_2 = inv_g_h;
              double W_3_3 = inv_g_h;
              double W_4_4 = inv_g_h - J_4_4;
              double W_4_6 = -J_4_6;
              double W_4_7 = -J_4_7;
              double W_4_8 = -J_4_8;
              double W_4_9 = -J_4_9;
              double W_5_5 = inv_g_h;
              double W_6_6 = inv_g_h - J_6_6;
              double W_7_4 = -J_7_4;
              double W_7_7 = inv_g_h - J_7_7;
              double W_7_8 = -J_7_8;
              double W_7_9 = -J_7_9;
              double W_7_11 = -J_7_11;
              double W_7_12 = -J_7_12;
              double W_7_13 = -J_7_13;
              double W_7_14 = -J_7_14;
              double W_8_4 = -J_8_4;
              double W_8_7 = -J_8_7;
              double W_8_8 = inv_g_h - J_8_8;
              double W_8_9 = -J_8_9;
              double W_8_11 = -J_8_11;
              double W_8_12 = -J_8_12;
              double W_8_14 = -J_8_14;
              double W_9_4 = -J_9_4;
              double W_9_5 = -J_9_5;
              double W_9_8 = -J_9_8;
              double W_9_9 = inv_g_h - J_9_9;
              double W_9_10 = -J_9_10;
              double W_9_14 = -J_9_14;
              double W_10_5 = -J_10_5;
              double W_10_8 = -J_10_8;
              double W_10_9 = -J_10_9;
              double W_10_10 = inv_g_h - J_10_10;
              double W_10_14 = -J_10_14;
              double W_11_11 = inv_g_h - J_11_11;
              double W_11_13 = -J_11_13;
              double W_11_14 = -J_11_14;
              double W_12_7 = -J_12_7;
              double W_12_8 = -J_12_8;
              double W_12_12 = inv_g_h - J_12_12;
              double W_12_14 = -J_12_14;
              double W_13_6 = -J_13_6;
              double W_13_11 = -J_13_11;
              double W_13_13 = inv_g_h - J_13_13;
              double W_13_14 = -J_13_14;
              double W_13_15 = -J_13_15;
              double W_14_14 = inv_g_h;
              double W_15_14 = -J_15_14;
              double W_15_15 = inv_g_h - J_15_15;
              double W_15_16 = -J_15_16;
              double W_16_14 = -J_16_14;
              double W_16_16 = inv_g_h - J_16_16;

              // Symbolic LU Factorization
              // Block 0: species [N2, H2O, HNO4, NO, O2, O3]
              double U_0_0 = W_0_0;
              // Block 1: species [M]
              double U_1_1 = W_1_1;
              double U_2_2 = W_2_2;
              double U_3_3 = W_3_3;
              double U_4_4 = W_4_4;
              double U_4_6 = W_4_6;
              double U_4_7 = W_4_7;
              double U_4_8 = W_4_8;
              double U_4_9 = W_4_9;
              // Block 3: species [NO3, O3P]
              double L_7_4 = (W_7_4) / U_4_4;
              // Block 4: species [NO2]
              double L_8_4 = (W_8_4) / U_4_4;
              double L_9_4 = (W_9_4) / U_4_4;
              double U_5_5 = W_5_5;
              double L_9_5 = (W_9_5) / U_5_5;
              double L_10_5 = (W_10_5) / U_5_5;
              // Block 2: species [HONO]
              double U_6_6 = W_6_6;
              double L_7_6 = (0.0 - L_7_4 * U_4_6) / U_6_6;
              double L_8_6 = (0.0 - L_8_4 * U_4_6) / U_6_6;
              double L_9_6 = (0.0 - L_9_4 * U_4_6) / U_6_6;
              // Block 7: species [OH]
              double L_13_6 = (W_13_6) / U_6_6;
              double U_7_7 = W_7_7 - L_7_4 * U_4_7;
              double U_7_8 = W_7_8 - L_7_4 * U_4_8;
              double U_7_9 = W_7_9 - L_7_4 * U_4_9;
              double U_7_11 = W_7_11;
              double U_7_12 = W_7_12;
              double U_7_13 = W_7_13;
              double U_7_14 = W_7_14;
              double L_8_7 = (W_8_7 - L_8_4 * U_4_7) / U_7_7;
              double L_9_7 = (0.0 - L_9_4 * U_4_7) / U_7_7;
              // Block 6: species [N2O5]
              double L_12_7 = (W_12_7) / U_7_7;
              double U_8_8 = W_8_8 - L_8_4 * U_4_8 - L_8_7 * U_7_8;
              double U_8_9 = W_8_9 - L_8_4 * U_4_9 - L_8_7 * U_7_9;
              double U_8_11 = W_8_11 - L_8_7 * U_7_11;
              double U_8_12 = W_8_12 - L_8_7 * U_7_12;
              double U_8_13 = 0.0 - L_8_7 * U_7_13;
              double U_8_14 = W_8_14 - L_8_7 * U_7_14;
              double L_9_8 = (W_9_8 - L_9_4 * U_4_8 - L_9_7 * U_7_8) / U_8_8;
              double L_10_8 = (W_10_8) / U_8_8;
              double L_12_8 = (W_12_8 - L_12_7 * U_7_8) / U_8_8;
              double U_9_9 = W_9_9 - L_9_4 * U_4_9 - L_9_7 * U_7_9 - L_9_8 * U_8_9;
              double U_9_10 = W_9_10;
              double U_9_11 = 0.0 - L_9_7 * U_7_11 - L_9_8 * U_8_11;
              double U_9_12 = 0.0 - L_9_7 * U_7_12 - L_9_8 * U_8_12;
              double U_9_13 = 0.0 - L_9_7 * U_7_13 - L_9_8 * U_8_13;
              double U_9_14 = W_9_14 - L_9_7 * U_7_14 - L_9_8 * U_8_14;
              double L_10_9 = (W_10_9 - L_10_8 * U_8_9) / U_9_9;
              double L_12_9 = (0.0 - L_12_7 * U_7_9 - L_12_8 * U_8_9) / U_9_9;
              double U_10_10 = W_10_10 - L_10_9 * U_9_10;
              double U_10_11 = 0.0 - L_10_8 * U_8_11 - L_10_9 * U_9_11;
              double U_10_12 = 0.0 - L_10_8 * U_8_12 - L_10_9 * U_9_12;
              double U_10_13 = 0.0 - L_10_8 * U_8_13 - L_10_9 * U_9_13;
              double U_10_14 = W_10_14 - L_10_8 * U_8_14 - L_10_9 * U_9_14;
              double L_12_10 = (0.0 - L_12_9 * U_9_10) / U_10_10;
              // Block 5: species [HNO3]
              double U_11_11 = W_11_11;
              double U_11_13 = W_11_13;
              double U_11_14 = W_11_14;
              double L_12_11 = (0.0 - L_12_7 * U_7_11 - L_12_8 * U_8_11 - L_12_9 * U_9_11 - L_12_10 * U_10_11) / U_11_11;
              double L_13_11 = (W_13_11) / U_11_11;
              double U_12_12 = W_12_12 - L_12_7 * U_7_12 - L_12_8 * U_8_12 - L_12_9 * U_9_12 - L_12_10 * U_10_12;
              double U_12_13 = 0.0 - L_12_7 * U_7_13 - L_12_8 * U_8_13 - L_12_9 * U_9_13 - L_12_10 * U_10_13 - L_12_11 * U_11_13;
              double U_12_14 = W_12_14 - L_12_7 * U_7_14 - L_12_8 * U_8_14 - L_12_9 * U_9_14 - L_12_10 * U_10_14 - L_12_11 * U_11_14;
              double U_13_13 = W_13_13 - L_13_11 * U_11_13;
              double U_13_14 = W_13_14 - L_13_11 * U_11_14;
              double U_13_15 = W_13_15;
              // Block 8: species [AIR]
              double U_14_14 = W_14_14;
              // Block 9: species [H2O2]
              double L_15_14 = (W_15_14) / U_14_14;
              // Block 10: species [HO2]
              double L_16_14 = (W_16_14) / U_14_14;
              double U_15_15 = W_15_15;
              double U_15_16 = W_15_16;
              double U_16_16 = W_16_16;



              // --- TLM Stage 1 ---
              // RHS: J*(δC + Σ A_{i,j}*δK_j) + Σ C_{i,j}/h*δK_j
              double tlm_rhs1_0 = 0.0;
              double tlm_rhs1_1 = 0.0;
              double tlm_rhs1_2 = 0.0;
              double tlm_rhs1_3 = 0.0;
              double tlm_rhs1_4 = J_4_4 * dC_4 + J_4_6 * dC_6 + J_4_7 * dC_7 + J_4_8 * dC_8 + J_4_9 * dC_9;
              double tlm_rhs1_5 = 0.0;
              double tlm_rhs1_6 = J_6_6 * dC_6;
              double tlm_rhs1_7 = J_7_4 * dC_4 + J_7_7 * dC_7 + J_7_8 * dC_8 + J_7_9 * dC_9 + J_7_11 * dC_11 + J_7_12 * dC_12 + J_7_13 * dC_13 + J_7_14 * dC_14;
              double tlm_rhs1_8 = J_8_4 * dC_4 + J_8_7 * dC_7 + J_8_8 * dC_8 + J_8_9 * dC_9 + J_8_11 * dC_11 + J_8_12 * dC_12 + J_8_14 * dC_14;
              double tlm_rhs1_9 = J_9_4 * dC_4 + J_9_5 * dC_5 + J_9_8 * dC_8 + J_9_9 * dC_9 + J_9_10 * dC_10 + J_9_14 * dC_14;
              double tlm_rhs1_10 = J_10_5 * dC_5 + J_10_8 * dC_8 + J_10_9 * dC_9 + J_10_10 * dC_10 + J_10_14 * dC_14;
              double tlm_rhs1_11 = J_11_11 * dC_11 + J_11_13 * dC_13 + J_11_14 * dC_14;
              double tlm_rhs1_12 = J_12_7 * dC_7 + J_12_8 * dC_8 + J_12_12 * dC_12 + J_12_14 * dC_14;
              double tlm_rhs1_13 = J_13_6 * dC_6 + J_13_11 * dC_11 + J_13_13 * dC_13 + J_13_14 * dC_14 + J_13_15 * dC_15;
              double tlm_rhs1_14 = 0.0;
              double tlm_rhs1_15 = J_15_14 * dC_14 + J_15_15 * dC_15 + J_15_16 * dC_16;
              double tlm_rhs1_16 = J_16_14 * dC_14 + J_16_16 * dC_16;
              // Solve W * dK1 = tlm_rhs1
              // Block 0: dK1 forward sub [N2, H2O, HNO4, NO, O2, O3]
              double tlm_y1_0 = tlm_rhs1_0;
              // Block 1: dK1 forward sub [M]
              double tlm_y1_1 = tlm_rhs1_1;
              double tlm_y1_2 = tlm_rhs1_2;
              double tlm_y1_3 = tlm_rhs1_3;
              double tlm_y1_4 = tlm_rhs1_4;
              double tlm_y1_5 = tlm_rhs1_5;
              // Block 2: dK1 forward sub [HONO]
              double tlm_y1_6 = tlm_rhs1_6;
              // Block 3: dK1 forward sub [NO3, O3P]
              double tlm_y1_7 = tlm_rhs1_7 - L_7_4 * tlm_y1_4 - L_7_6 * tlm_y1_6;
              // Block 4: dK1 forward sub [NO2]
              double tlm_y1_8 = tlm_rhs1_8 - L_8_4 * tlm_y1_4 - L_8_6 * tlm_y1_6 - L_8_7 * tlm_y1_7;
              double tlm_y1_9 = tlm_rhs1_9 - L_9_4 * tlm_y1_4 - L_9_5 * tlm_y1_5 - L_9_6 * tlm_y1_6 - L_9_7 * tlm_y1_7 - L_9_8 * tlm_y1_8;
              double tlm_y1_10 = tlm_rhs1_10 - L_10_5 * tlm_y1_5 - L_10_8 * tlm_y1_8 - L_10_9 * tlm_y1_9;
              // Block 5: dK1 forward sub [HNO3]
              double tlm_y1_11 = tlm_rhs1_11;
              // Block 6: dK1 forward sub [N2O5]
              double tlm_y1_12 = tlm_rhs1_12 - L_12_7 * tlm_y1_7 - L_12_8 * tlm_y1_8 - L_12_9 * tlm_y1_9 - L_12_10 * tlm_y1_10 - L_12_11 * tlm_y1_11;
              // Block 7: dK1 forward sub [OH]
              double tlm_y1_13 = tlm_rhs1_13 - L_13_6 * tlm_y1_6 - L_13_11 * tlm_y1_11;
              // Block 8: dK1 forward sub [AIR]
              double tlm_y1_14 = tlm_rhs1_14;
              // Block 9: dK1 forward sub [H2O2]
              double tlm_y1_15 = tlm_rhs1_15 - L_15_14 * tlm_y1_14;
              // Block 10: dK1 forward sub [HO2]
              double tlm_y1_16 = tlm_rhs1_16 - L_16_14 * tlm_y1_14;
              // Block 10: dK1 backward sub [HO2]
              double dK1_16 = tlm_y1_16 / U_16_16;
              // Block 9: dK1 backward sub [H2O2]
              double dK1_15 = (tlm_y1_15 - U_15_16 * dK1_16) / U_15_15;
              // Block 8: dK1 backward sub [AIR]
              double dK1_14 = tlm_y1_14 / U_14_14;
              // Block 7: dK1 backward sub [OH]
              double dK1_13 = (tlm_y1_13 - U_13_14 * dK1_14 - U_13_15 * dK1_15) / U_13_13;
              // Block 6: dK1 backward sub [N2O5]
              double dK1_12 = (tlm_y1_12 - U_12_13 * dK1_13 - U_12_14 * dK1_14) / U_12_12;
              // Block 5: dK1 backward sub [HNO3]
              double dK1_11 = (tlm_y1_11 - U_11_13 * dK1_13 - U_11_14 * dK1_14) / U_11_11;
              // Block 3: dK1 backward sub [NO3, O3P]
              double dK1_10 = (tlm_y1_10 - U_10_11 * dK1_11 - U_10_12 * dK1_12 - U_10_13 * dK1_13 - U_10_14 * dK1_14) / U_10_10;
              // Block 0: dK1 backward sub [N2, H2O, HNO4, NO, O2, O3]
              double dK1_9 = (tlm_y1_9 - U_9_10 * dK1_10 - U_9_11 * dK1_11 - U_9_12 * dK1_12 - U_9_13 * dK1_13 - U_9_14 * dK1_14) / U_9_9;
              // Block 4: dK1 backward sub [NO2]
              double dK1_8 = (tlm_y1_8 - U_8_9 * dK1_9 - U_8_11 * dK1_11 - U_8_12 * dK1_12 - U_8_13 * dK1_13 - U_8_14 * dK1_14) / U_8_8;
              double dK1_7 = (tlm_y1_7 - U_7_8 * dK1_8 - U_7_9 * dK1_9 - U_7_11 * dK1_11 - U_7_12 * dK1_12 - U_7_13 * dK1_13 - U_7_14 * dK1_14) / U_7_7;
              // Block 2: dK1 backward sub [HONO]
              double dK1_6 = tlm_y1_6 / U_6_6;
              double dK1_5 = tlm_y1_5 / U_5_5;
              double dK1_4 = (tlm_y1_4 - U_4_6 * dK1_6 - U_4_7 * dK1_7 - U_4_8 * dK1_8 - U_4_9 * dK1_9) / U_4_4;
              double dK1_3 = tlm_y1_3 / U_3_3;
              double dK1_2 = tlm_y1_2 / U_2_2;
              // Block 1: dK1 backward sub [M]
              double dK1_1 = tlm_y1_1 / U_1_1;
              double dK1_0 = tlm_y1_0 / U_0_0;

              // --- TLM Stage 2 ---
              // RHS: J*(δC + Σ A_{i,j}*δK_j) + Σ C_{i,j}/h*δK_j
              double tlm_rhs2_0 = (-1.0156171083877703 / h) * dK1_0;
              double tlm_rhs2_1 = (-1.0156171083877703 / h) * dK1_1;
              double tlm_rhs2_2 = (-1.0156171083877703 / h) * dK1_2;
              double tlm_rhs2_3 = (-1.0156171083877703 / h) * dK1_3;
              double tlm_rhs2_4 = J_4_4 * (dC_4 + dK1_4) + J_4_6 * (dC_6 + dK1_6) + J_4_7 * (dC_7 + dK1_7) + J_4_8 * (dC_8 + dK1_8) + J_4_9 * (dC_9 + dK1_9) + (-1.0156171083877703 / h) * dK1_4;
              double tlm_rhs2_5 = (-1.0156171083877703 / h) * dK1_5;
              double tlm_rhs2_6 = J_6_6 * (dC_6 + dK1_6) + (-1.0156171083877703 / h) * dK1_6;
              double tlm_rhs2_7 = J_7_4 * (dC_4 + dK1_4) + J_7_7 * (dC_7 + dK1_7) + J_7_8 * (dC_8 + dK1_8) + J_7_9 * (dC_9 + dK1_9) + J_7_11 * (dC_11 + dK1_11) + J_7_12 * (dC_12 + dK1_12) + J_7_13 * (dC_13 + dK1_13) + J_7_14 * (dC_14 + dK1_14) + (-1.0156171083877703 / h) * dK1_7;
              double tlm_rhs2_8 = J_8_4 * (dC_4 + dK1_4) + J_8_7 * (dC_7 + dK1_7) + J_8_8 * (dC_8 + dK1_8) + J_8_9 * (dC_9 + dK1_9) + J_8_11 * (dC_11 + dK1_11) + J_8_12 * (dC_12 + dK1_12) + J_8_14 * (dC_14 + dK1_14) + (-1.0156171083877703 / h) * dK1_8;
              double tlm_rhs2_9 = J_9_4 * (dC_4 + dK1_4) + J_9_5 * (dC_5 + dK1_5) + J_9_8 * (dC_8 + dK1_8) + J_9_9 * (dC_9 + dK1_9) + J_9_10 * (dC_10 + dK1_10) + J_9_14 * (dC_14 + dK1_14) + (-1.0156171083877703 / h) * dK1_9;
              double tlm_rhs2_10 = J_10_5 * (dC_5 + dK1_5) + J_10_8 * (dC_8 + dK1_8) + J_10_9 * (dC_9 + dK1_9) + J_10_10 * (dC_10 + dK1_10) + J_10_14 * (dC_14 + dK1_14) + (-1.0156171083877703 / h) * dK1_10;
              double tlm_rhs2_11 = J_11_11 * (dC_11 + dK1_11) + J_11_13 * (dC_13 + dK1_13) + J_11_14 * (dC_14 + dK1_14) + (-1.0156171083877703 / h) * dK1_11;
              double tlm_rhs2_12 = J_12_7 * (dC_7 + dK1_7) + J_12_8 * (dC_8 + dK1_8) + J_12_12 * (dC_12 + dK1_12) + J_12_14 * (dC_14 + dK1_14) + (-1.0156171083877703 / h) * dK1_12;
              double tlm_rhs2_13 = J_13_6 * (dC_6 + dK1_6) + J_13_11 * (dC_11 + dK1_11) + J_13_13 * (dC_13 + dK1_13) + J_13_14 * (dC_14 + dK1_14) + J_13_15 * (dC_15 + dK1_15) + (-1.0156171083877703 / h) * dK1_13;
              double tlm_rhs2_14 = (-1.0156171083877703 / h) * dK1_14;
              double tlm_rhs2_15 = J_15_14 * (dC_14 + dK1_14) + J_15_15 * (dC_15 + dK1_15) + J_15_16 * (dC_16 + dK1_16) + (-1.0156171083877703 / h) * dK1_15;
              double tlm_rhs2_16 = J_16_14 * (dC_14 + dK1_14) + J_16_16 * (dC_16 + dK1_16) + (-1.0156171083877703 / h) * dK1_16;
              // Solve W * dK2 = tlm_rhs2
              // Block 0: dK2 forward sub [N2, H2O, HNO4, NO, O2, O3]
              double tlm_y2_0 = tlm_rhs2_0;
              // Block 1: dK2 forward sub [M]
              double tlm_y2_1 = tlm_rhs2_1;
              double tlm_y2_2 = tlm_rhs2_2;
              double tlm_y2_3 = tlm_rhs2_3;
              double tlm_y2_4 = tlm_rhs2_4;
              double tlm_y2_5 = tlm_rhs2_5;
              // Block 2: dK2 forward sub [HONO]
              double tlm_y2_6 = tlm_rhs2_6;
              // Block 3: dK2 forward sub [NO3, O3P]
              double tlm_y2_7 = tlm_rhs2_7 - L_7_4 * tlm_y2_4 - L_7_6 * tlm_y2_6;
              // Block 4: dK2 forward sub [NO2]
              double tlm_y2_8 = tlm_rhs2_8 - L_8_4 * tlm_y2_4 - L_8_6 * tlm_y2_6 - L_8_7 * tlm_y2_7;
              double tlm_y2_9 = tlm_rhs2_9 - L_9_4 * tlm_y2_4 - L_9_5 * tlm_y2_5 - L_9_6 * tlm_y2_6 - L_9_7 * tlm_y2_7 - L_9_8 * tlm_y2_8;
              double tlm_y2_10 = tlm_rhs2_10 - L_10_5 * tlm_y2_5 - L_10_8 * tlm_y2_8 - L_10_9 * tlm_y2_9;
              // Block 5: dK2 forward sub [HNO3]
              double tlm_y2_11 = tlm_rhs2_11;
              // Block 6: dK2 forward sub [N2O5]
              double tlm_y2_12 = tlm_rhs2_12 - L_12_7 * tlm_y2_7 - L_12_8 * tlm_y2_8 - L_12_9 * tlm_y2_9 - L_12_10 * tlm_y2_10 - L_12_11 * tlm_y2_11;
              // Block 7: dK2 forward sub [OH]
              double tlm_y2_13 = tlm_rhs2_13 - L_13_6 * tlm_y2_6 - L_13_11 * tlm_y2_11;
              // Block 8: dK2 forward sub [AIR]
              double tlm_y2_14 = tlm_rhs2_14;
              // Block 9: dK2 forward sub [H2O2]
              double tlm_y2_15 = tlm_rhs2_15 - L_15_14 * tlm_y2_14;
              // Block 10: dK2 forward sub [HO2]
              double tlm_y2_16 = tlm_rhs2_16 - L_16_14 * tlm_y2_14;
              // Block 10: dK2 backward sub [HO2]
              double dK2_16 = tlm_y2_16 / U_16_16;
              // Block 9: dK2 backward sub [H2O2]
              double dK2_15 = (tlm_y2_15 - U_15_16 * dK2_16) / U_15_15;
              // Block 8: dK2 backward sub [AIR]
              double dK2_14 = tlm_y2_14 / U_14_14;
              // Block 7: dK2 backward sub [OH]
              double dK2_13 = (tlm_y2_13 - U_13_14 * dK2_14 - U_13_15 * dK2_15) / U_13_13;
              // Block 6: dK2 backward sub [N2O5]
              double dK2_12 = (tlm_y2_12 - U_12_13 * dK2_13 - U_12_14 * dK2_14) / U_12_12;
              // Block 5: dK2 backward sub [HNO3]
              double dK2_11 = (tlm_y2_11 - U_11_13 * dK2_13 - U_11_14 * dK2_14) / U_11_11;
              // Block 3: dK2 backward sub [NO3, O3P]
              double dK2_10 = (tlm_y2_10 - U_10_11 * dK2_11 - U_10_12 * dK2_12 - U_10_13 * dK2_13 - U_10_14 * dK2_14) / U_10_10;
              // Block 0: dK2 backward sub [N2, H2O, HNO4, NO, O2, O3]
              double dK2_9 = (tlm_y2_9 - U_9_10 * dK2_10 - U_9_11 * dK2_11 - U_9_12 * dK2_12 - U_9_13 * dK2_13 - U_9_14 * dK2_14) / U_9_9;
              // Block 4: dK2 backward sub [NO2]
              double dK2_8 = (tlm_y2_8 - U_8_9 * dK2_9 - U_8_11 * dK2_11 - U_8_12 * dK2_12 - U_8_13 * dK2_13 - U_8_14 * dK2_14) / U_8_8;
              double dK2_7 = (tlm_y2_7 - U_7_8 * dK2_8 - U_7_9 * dK2_9 - U_7_11 * dK2_11 - U_7_12 * dK2_12 - U_7_13 * dK2_13 - U_7_14 * dK2_14) / U_7_7;
              // Block 2: dK2 backward sub [HONO]
              double dK2_6 = tlm_y2_6 / U_6_6;
              double dK2_5 = tlm_y2_5 / U_5_5;
              double dK2_4 = (tlm_y2_4 - U_4_6 * dK2_6 - U_4_7 * dK2_7 - U_4_8 * dK2_8 - U_4_9 * dK2_9) / U_4_4;
              double dK2_3 = tlm_y2_3 / U_3_3;
              double dK2_2 = tlm_y2_2 / U_2_2;
              // Block 1: dK2 backward sub [M]
              double dK2_1 = tlm_y2_1 / U_1_1;
              double dK2_0 = tlm_y2_0 / U_0_0;

              // --- TLM Stage 3 ---
              // RHS: J*(δC + Σ A_{i,j}*δK_j) + Σ C_{i,j}/h*δK_j
              double tlm_rhs3_0 = (4.0759956452537702 / h) * dK1_0 + (9.20767942983308 / h) * dK2_0;
              double tlm_rhs3_1 = (4.0759956452537702 / h) * dK1_1 + (9.20767942983308 / h) * dK2_1;
              double tlm_rhs3_2 = (4.0759956452537702 / h) * dK1_2 + (9.20767942983308 / h) * dK2_2;
              double tlm_rhs3_3 = (4.0759956452537702 / h) * dK1_3 + (9.20767942983308 / h) * dK2_3;
              double tlm_rhs3_4 = J_4_4 * (dC_4 + dK1_4) + J_4_6 * (dC_6 + dK1_6) + J_4_7 * (dC_7 + dK1_7) + J_4_8 * (dC_8 + dK1_8) + J_4_9 * (dC_9 + dK1_9) + (4.0759956452537702 / h) * dK1_4 + (9.20767942983308 / h) * dK2_4;
              double tlm_rhs3_5 = (4.0759956452537702 / h) * dK1_5 + (9.20767942983308 / h) * dK2_5;
              double tlm_rhs3_6 = J_6_6 * (dC_6 + dK1_6) + (4.0759956452537702 / h) * dK1_6 + (9.20767942983308 / h) * dK2_6;
              double tlm_rhs3_7 = J_7_4 * (dC_4 + dK1_4) + J_7_7 * (dC_7 + dK1_7) + J_7_8 * (dC_8 + dK1_8) + J_7_9 * (dC_9 + dK1_9) + J_7_11 * (dC_11 + dK1_11) + J_7_12 * (dC_12 + dK1_12) + J_7_13 * (dC_13 + dK1_13) + J_7_14 * (dC_14 + dK1_14) + (4.0759956452537702 / h) * dK1_7 + (9.20767942983308 / h) * dK2_7;
              double tlm_rhs3_8 = J_8_4 * (dC_4 + dK1_4) + J_8_7 * (dC_7 + dK1_7) + J_8_8 * (dC_8 + dK1_8) + J_8_9 * (dC_9 + dK1_9) + J_8_11 * (dC_11 + dK1_11) + J_8_12 * (dC_12 + dK1_12) + J_8_14 * (dC_14 + dK1_14) + (4.0759956452537702 / h) * dK1_8 + (9.20767942983308 / h) * dK2_8;
              double tlm_rhs3_9 = J_9_4 * (dC_4 + dK1_4) + J_9_5 * (dC_5 + dK1_5) + J_9_8 * (dC_8 + dK1_8) + J_9_9 * (dC_9 + dK1_9) + J_9_10 * (dC_10 + dK1_10) + J_9_14 * (dC_14 + dK1_14) + (4.0759956452537702 / h) * dK1_9 + (9.20767942983308 / h) * dK2_9;
              double tlm_rhs3_10 = J_10_5 * (dC_5 + dK1_5) + J_10_8 * (dC_8 + dK1_8) + J_10_9 * (dC_9 + dK1_9) + J_10_10 * (dC_10 + dK1_10) + J_10_14 * (dC_14 + dK1_14) + (4.0759956452537702 / h) * dK1_10 + (9.20767942983308 / h) * dK2_10;
              double tlm_rhs3_11 = J_11_11 * (dC_11 + dK1_11) + J_11_13 * (dC_13 + dK1_13) + J_11_14 * (dC_14 + dK1_14) + (4.0759956452537702 / h) * dK1_11 + (9.20767942983308 / h) * dK2_11;
              double tlm_rhs3_12 = J_12_7 * (dC_7 + dK1_7) + J_12_8 * (dC_8 + dK1_8) + J_12_12 * (dC_12 + dK1_12) + J_12_14 * (dC_14 + dK1_14) + (4.0759956452537702 / h) * dK1_12 + (9.20767942983308 / h) * dK2_12;
              double tlm_rhs3_13 = J_13_6 * (dC_6 + dK1_6) + J_13_11 * (dC_11 + dK1_11) + J_13_13 * (dC_13 + dK1_13) + J_13_14 * (dC_14 + dK1_14) + J_13_15 * (dC_15 + dK1_15) + (4.0759956452537702 / h) * dK1_13 + (9.20767942983308 / h) * dK2_13;
              double tlm_rhs3_14 = (4.0759956452537702 / h) * dK1_14 + (9.20767942983308 / h) * dK2_14;
              double tlm_rhs3_15 = J_15_14 * (dC_14 + dK1_14) + J_15_15 * (dC_15 + dK1_15) + J_15_16 * (dC_16 + dK1_16) + (4.0759956452537702 / h) * dK1_15 + (9.20767942983308 / h) * dK2_15;
              double tlm_rhs3_16 = J_16_14 * (dC_14 + dK1_14) + J_16_16 * (dC_16 + dK1_16) + (4.0759956452537702 / h) * dK1_16 + (9.20767942983308 / h) * dK2_16;
              // Solve W * dK3 = tlm_rhs3
              // Block 0: dK3 forward sub [N2, H2O, HNO4, NO, O2, O3]
              double tlm_y3_0 = tlm_rhs3_0;
              // Block 1: dK3 forward sub [M]
              double tlm_y3_1 = tlm_rhs3_1;
              double tlm_y3_2 = tlm_rhs3_2;
              double tlm_y3_3 = tlm_rhs3_3;
              double tlm_y3_4 = tlm_rhs3_4;
              double tlm_y3_5 = tlm_rhs3_5;
              // Block 2: dK3 forward sub [HONO]
              double tlm_y3_6 = tlm_rhs3_6;
              // Block 3: dK3 forward sub [NO3, O3P]
              double tlm_y3_7 = tlm_rhs3_7 - L_7_4 * tlm_y3_4 - L_7_6 * tlm_y3_6;
              // Block 4: dK3 forward sub [NO2]
              double tlm_y3_8 = tlm_rhs3_8 - L_8_4 * tlm_y3_4 - L_8_6 * tlm_y3_6 - L_8_7 * tlm_y3_7;
              double tlm_y3_9 = tlm_rhs3_9 - L_9_4 * tlm_y3_4 - L_9_5 * tlm_y3_5 - L_9_6 * tlm_y3_6 - L_9_7 * tlm_y3_7 - L_9_8 * tlm_y3_8;
              double tlm_y3_10 = tlm_rhs3_10 - L_10_5 * tlm_y3_5 - L_10_8 * tlm_y3_8 - L_10_9 * tlm_y3_9;
              // Block 5: dK3 forward sub [HNO3]
              double tlm_y3_11 = tlm_rhs3_11;
              // Block 6: dK3 forward sub [N2O5]
              double tlm_y3_12 = tlm_rhs3_12 - L_12_7 * tlm_y3_7 - L_12_8 * tlm_y3_8 - L_12_9 * tlm_y3_9 - L_12_10 * tlm_y3_10 - L_12_11 * tlm_y3_11;
              // Block 7: dK3 forward sub [OH]
              double tlm_y3_13 = tlm_rhs3_13 - L_13_6 * tlm_y3_6 - L_13_11 * tlm_y3_11;
              // Block 8: dK3 forward sub [AIR]
              double tlm_y3_14 = tlm_rhs3_14;
              // Block 9: dK3 forward sub [H2O2]
              double tlm_y3_15 = tlm_rhs3_15 - L_15_14 * tlm_y3_14;
              // Block 10: dK3 forward sub [HO2]
              double tlm_y3_16 = tlm_rhs3_16 - L_16_14 * tlm_y3_14;
              // Block 10: dK3 backward sub [HO2]
              double dK3_16 = tlm_y3_16 / U_16_16;
              // Block 9: dK3 backward sub [H2O2]
              double dK3_15 = (tlm_y3_15 - U_15_16 * dK3_16) / U_15_15;
              // Block 8: dK3 backward sub [AIR]
              double dK3_14 = tlm_y3_14 / U_14_14;
              // Block 7: dK3 backward sub [OH]
              double dK3_13 = (tlm_y3_13 - U_13_14 * dK3_14 - U_13_15 * dK3_15) / U_13_13;
              // Block 6: dK3 backward sub [N2O5]
              double dK3_12 = (tlm_y3_12 - U_12_13 * dK3_13 - U_12_14 * dK3_14) / U_12_12;
              // Block 5: dK3 backward sub [HNO3]
              double dK3_11 = (tlm_y3_11 - U_11_13 * dK3_13 - U_11_14 * dK3_14) / U_11_11;
              // Block 3: dK3 backward sub [NO3, O3P]
              double dK3_10 = (tlm_y3_10 - U_10_11 * dK3_11 - U_10_12 * dK3_12 - U_10_13 * dK3_13 - U_10_14 * dK3_14) / U_10_10;
              // Block 0: dK3 backward sub [N2, H2O, HNO4, NO, O2, O3]
              double dK3_9 = (tlm_y3_9 - U_9_10 * dK3_10 - U_9_11 * dK3_11 - U_9_12 * dK3_12 - U_9_13 * dK3_13 - U_9_14 * dK3_14) / U_9_9;
              // Block 4: dK3 backward sub [NO2]
              double dK3_8 = (tlm_y3_8 - U_8_9 * dK3_9 - U_8_11 * dK3_11 - U_8_12 * dK3_12 - U_8_13 * dK3_13 - U_8_14 * dK3_14) / U_8_8;
              double dK3_7 = (tlm_y3_7 - U_7_8 * dK3_8 - U_7_9 * dK3_9 - U_7_11 * dK3_11 - U_7_12 * dK3_12 - U_7_13 * dK3_13 - U_7_14 * dK3_14) / U_7_7;
              // Block 2: dK3 backward sub [HONO]
              double dK3_6 = tlm_y3_6 / U_6_6;
              double dK3_5 = tlm_y3_5 / U_5_5;
              double dK3_4 = (tlm_y3_4 - U_4_6 * dK3_6 - U_4_7 * dK3_7 - U_4_8 * dK3_8 - U_4_9 * dK3_9) / U_4_4;
              double dK3_3 = tlm_y3_3 / U_3_3;
              double dK3_2 = tlm_y3_2 / U_2_2;
              // Block 1: dK3 backward sub [M]
              double dK3_1 = tlm_y3_1 / U_1_1;
              double dK3_0 = tlm_y3_0 / U_0_0;

              // --- δC update: δC += Σ M_i * δK_i ---
              dC_0 += dK1_0 + 6.1697947043828245 * dK2_0 + -0.42772256543218573 * dK3_0;
              dC_1 += dK1_1 + 6.1697947043828245 * dK2_1 + -0.42772256543218573 * dK3_1;
              dC_2 += dK1_2 + 6.1697947043828245 * dK2_2 + -0.42772256543218573 * dK3_2;
              dC_3 += dK1_3 + 6.1697947043828245 * dK2_3 + -0.42772256543218573 * dK3_3;
              dC_4 += dK1_4 + 6.1697947043828245 * dK2_4 + -0.42772256543218573 * dK3_4;
              dC_5 += dK1_5 + 6.1697947043828245 * dK2_5 + -0.42772256543218573 * dK3_5;
              dC_6 += dK1_6 + 6.1697947043828245 * dK2_6 + -0.42772256543218573 * dK3_6;
              dC_7 += dK1_7 + 6.1697947043828245 * dK2_7 + -0.42772256543218573 * dK3_7;
              dC_8 += dK1_8 + 6.1697947043828245 * dK2_8 + -0.42772256543218573 * dK3_8;
              dC_9 += dK1_9 + 6.1697947043828245 * dK2_9 + -0.42772256543218573 * dK3_9;
              dC_10 += dK1_10 + 6.1697947043828245 * dK2_10 + -0.42772256543218573 * dK3_10;
              dC_11 += dK1_11 + 6.1697947043828245 * dK2_11 + -0.42772256543218573 * dK3_11;
              dC_12 += dK1_12 + 6.1697947043828245 * dK2_12 + -0.42772256543218573 * dK3_12;
              dC_13 += dK1_13 + 6.1697947043828245 * dK2_13 + -0.42772256543218573 * dK3_13;
              dC_14 += dK1_14 + 6.1697947043828245 * dK2_14 + -0.42772256543218573 * dK3_14;
              dC_15 += dK1_15 + 6.1697947043828245 * dK2_15 + -0.42772256543218573 * dK3_15;
              dC_16 += dK1_16 + 6.1697947043828245 * dK2_16 + -0.42772256543218573 * dK3_16;
          } // end for (step)

          // Write back final δC to output view
          delta_C(0) = dC_0;
          delta_C(1) = dC_1;
          delta_C(2) = dC_2;
          delta_C(3) = dC_3;
          delta_C(4) = dC_4;
          delta_C(5) = dC_5;
          delta_C(6) = dC_6;
          delta_C(7) = dC_7;
          delta_C(8) = dC_8;
          delta_C(9) = dC_9;
          delta_C(10) = dC_10;
          delta_C(11) = dC_11;
          delta_C(12) = dC_12;
          delta_C(13) = dC_13;
          delta_C(14) = dC_14;
          delta_C(15) = dC_15;
          delta_C(16) = dC_16;
      }
#endif
  };
}
