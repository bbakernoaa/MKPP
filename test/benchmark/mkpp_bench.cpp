/**
 * @file mkpp_bench.cpp
 * @brief Unified C++ performance and instruction profiling benchmark executable for MKPP.
 */

#include <Kokkos_Core.hpp>

#include <chrono>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#ifdef MKPP_USE_CALLGRIND
#include <valgrind/callgrind.h>
#endif

namespace mech_chapman {
#include "chapman.hpp"
}  // namespace mech_chapman

namespace mech_gocart {
#include "gocart.hpp"
}  // namespace mech_gocart

namespace mech_saprc99 {
#include "saprc99.hpp"
}  // namespace mech_saprc99

namespace mech_t1 {
#include "t1.hpp"
}  // namespace mech_t1

using ExecSpace = Kokkos::DefaultExecutionSpace;

/**
 * @brief Kokkos parallel functor executing Rosenbrock integration over grid cells.
 * 
 * @tparam SolverKernelsType Generated mechanism SolverKernels struct.
 * @tparam IsGocart Boolean flag indicating whether mechanism requires temperature and relative humidity.
 */
template <typename SolverKernelsType, bool IsGocart = false>
struct IntegrationFunctor {
    using ViewType = Kokkos::View<double**, Kokkos::LayoutLeft, typename ExecSpace::memory_space>;
    ViewType m_state;
    double m_dt;
    const double* m_jvals;
    double m_temp;
    double m_rh;

    /**
     * @brief Construct a new Integration Functor object.
     * 
     * @param state Multidimensional Kokkos View holding concentrations [cells, species].
     * @param dt Time step size [s].
     * @param jvals Photolysis rates array pointer.
     * @param temp Ambient temperature [K] (used for GOCART).
     * @param rh Relative humidity [fraction] (used for GOCART).
     */
    IntegrationFunctor(ViewType state, double dt, const double* jvals, double temp = 288.15, double rh = 0.5)
        : m_state(state), m_dt(dt), m_jvals(jvals), m_temp(temp), m_rh(rh) {}

    /**
     * @brief Kokkos operator executing integration for a single grid cell.
     * 
     * @param cell_idx Cell index in grid range.
     */
    KOKKOS_INLINE_FUNCTION
    void operator()(const int cell_idx) const {
        auto sub_state = Kokkos::subview(m_state, cell_idx, Kokkos::ALL());
        SolverKernelsType solver;
        if constexpr (IsGocart) {
            solver.integrate(m_dt, sub_state, m_jvals, m_temp, m_rh);
        } else {
            solver.integrate(m_dt, sub_state, m_jvals);
        }
    }
};

/**
 * @brief Runs benchmark integration loop and measures execution performance.
 * 
 * @tparam SolverKernelsType Generated mechanism SolverKernels type.
 * @tparam IsGocart Boolean flag indicating whether mechanism is GOCART.
 * @param name Name of the mechanism.
 * @param num_cells Number of grid cells.
 * @param num_steps Number of integration time steps.
 * @param dt Time step size [s].
 */
template <typename SolverKernelsType, bool IsGocart = false>
void run_benchmark(const std::string& name, int num_cells, int num_steps, double dt) {
    const int num_species = SolverKernelsType::NUM_SPECIES;

    using ViewType = Kokkos::View<double**, Kokkos::LayoutLeft, typename ExecSpace::memory_space>;
    ViewType state("state", num_cells, num_species);

    // Photolysis rates buffer (jvals)
    Kokkos::View<double*, typename ExecSpace::memory_space> jvals_dev("jvals", 256);
    auto host_jvals = Kokkos::create_mirror_view(jvals_dev);
    for (int j = 0; j < 256; ++j) {
        host_jvals(j) = 1.0e-5;
    }
    Kokkos::deep_copy(jvals_dev, host_jvals);

    // Initialize state concentrations
    auto host_state = Kokkos::create_mirror_view(state);
    for (int i = 0; i < num_cells; ++i) {
        for (int k = 0; k < num_species; ++k) {
            host_state(i, k) = 1.0e6;
        }
    }
    Kokkos::deep_copy(state, host_state);

    IntegrationFunctor<SolverKernelsType, IsGocart> functor(state, dt, jvals_dev.data());

    // Warmup step
    Kokkos::parallel_for("warmup", Kokkos::RangePolicy<ExecSpace>(0, num_cells), functor);
    Kokkos::fence();

    // Start benchmark & Callgrind instrumentation
    auto start = std::chrono::high_resolution_clock::now();

#ifdef MKPP_USE_CALLGRIND
    CALLGRIND_START_INSTRUMENTATION;
    CALLGRIND_TOGGLE_COLLECT;
#endif

    for (int step = 0; step < num_steps; ++step) {
        Kokkos::parallel_for("integrate", Kokkos::RangePolicy<ExecSpace>(0, num_cells), functor);
        Kokkos::fence();
    }

#ifdef MKPP_USE_CALLGRIND
    CALLGRIND_TOGGLE_COLLECT;
    CALLGRIND_STOP_INSTRUMENTATION;
#endif

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> elapsed = end - start;
    double elapsed_ms = elapsed.count();
    double total_cell_steps = static_cast<double>(num_cells) * num_steps;
    double throughput = (elapsed_ms > 0.0) ? (total_cell_steps / (elapsed_ms / 1000.0)) : 0.0;

    std::cout << "==========================================================================" << std::endl;
    std::cout << "                      MKPP Benchmark: " << name << std::endl;
    std::cout << "==========================================================================" << std::endl;
    std::cout << "Mechanism        : " << name << std::endl;
    std::cout << "Species Count    : " << num_species << std::endl;
    std::cout << "Grid Cells       : " << num_cells << std::endl;
    std::cout << "Timesteps        : " << num_steps << std::endl;
    std::cout << "Step Size        : " << dt << " s" << std::endl;
    std::cout << "Execution time   : " << std::fixed << std::setprecision(3) << elapsed_ms << " ms" << std::endl;
    std::cout << "Throughput       : " << std::scientific << std::setprecision(3) << throughput << " cell-steps/s" << std::endl;
    std::cout << "==========================================================================" << std::endl;
}

/**
 * @brief Main entry point for MKPP benchmark CLI.
 * 
 * @param argc Command line argument count.
 * @param argv Command line argument values.
 * @return int Exit code (0 for success).
 */
int main(int argc, char* argv[]) {
    Kokkos::initialize(argc, argv);
    int exit_code = 0;
    {
        std::string mechanism = "chapman";
        int num_cells = 10000;
        int num_steps = 30;
        double dt = 60.0;

        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg == "--mechanism" && i + 1 < argc) {
                mechanism = argv[++i];
            } else if (arg == "--cells" && i + 1 < argc) {
                num_cells = std::stoi(argv[++i]);
            } else if (arg == "--steps" && i + 1 < argc) {
                num_steps = std::stoi(argv[++i]);
            } else if (arg == "--dt" && i + 1 < argc) {
                dt = std::stod(argv[++i]);
            } else if (arg == "-h" || arg == "--help") {
                std::cout << "Usage: " << argv[0] << " [options]\n"
                          << "Options:\n"
                          << "  --mechanism chapman|gocart|saprc99|t1 (default: chapman)\n"
                          << "  --cells N                             (default: 10000)\n"
                          << "  --steps N                             (default: 30)\n"
                          << "  --dt DT                               (default: 60.0)\n";
                Kokkos::finalize();
                return 0;
            }
        }

        if (mechanism == "chapman") {
            run_benchmark<mech_chapman::mkpp::SolverKernels<ExecSpace>, false>("chapman", num_cells, num_steps, dt);
        } else if (mechanism == "gocart") {
            run_benchmark<mech_gocart::mkpp::SolverKernels<ExecSpace>, true>("gocart", num_cells, num_steps, dt);
        } else if (mechanism == "saprc99") {
            run_benchmark<mech_saprc99::mkpp::SolverKernels<ExecSpace>, false>("saprc99", num_cells, num_steps, dt);
        } else if (mechanism == "t1") {
            run_benchmark<mech_t1::mkpp::SolverKernels<ExecSpace>, false>("t1", num_cells, num_steps, dt);
        } else {
            std::cerr << "FATAL ERROR: Unknown mechanism '" << mechanism << "'. Supported: chapman, gocart, saprc99, t1\n";
            exit_code = 1;
        }
    }
    Kokkos::finalize();
    return exit_code;
}
