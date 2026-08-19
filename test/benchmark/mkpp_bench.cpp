/**
 * @file mkpp_bench.cpp
 * @brief Unified C++ performance and instruction profiling benchmark executable for MKPP using the mkpp_host interface.
 */

#include <Kokkos_Core.hpp>
#include <mkpp_host/mechanism_manager.hpp>

#include <chrono>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#ifdef MKPP_USE_CALLGRIND
#include <valgrind/callgrind.h>
#endif

using ExecSpace = Kokkos::DefaultExecutionSpace;

void run_benchmark(const std::string& name, int num_cells, int num_steps, double dt) {
    if (!mkpp::host::MechanismRegistry::has_mechanism(name)) {
        auto list = mkpp::host::MechanismRegistry::get_registered_mechanisms();
        std::string supported = "";
        for (size_t i = 0; i < list.size(); ++i) {
            supported += list[i] + (i + 1 < list.size() ? ", " : "");
        }
        std::cerr << "FATAL ERROR: Unknown mechanism '" << name << "'. Supported: " << supported << "\n";
        std::exit(1);
    }

    auto info = mkpp::host::MechanismRegistry::get_info(name);
    const int num_species = info.num_species;

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

    mkpp::host::HostExecutionParams params;
    params.dt = dt;
    params.jvals = jvals_dev.data();
    params.steps = 1;
    params.temp = 288.15;
    params.rh = 0.5;

    // Warmup step via mkpp_host
    mkpp::host::MechanismRegistry::execute(name, state, params);
    Kokkos::fence();

    params.steps = num_steps;

    // Start benchmark & Callgrind instrumentation
    auto start = std::chrono::high_resolution_clock::now();

#ifdef MKPP_USE_CALLGRIND
    CALLGRIND_START_INSTRUMENTATION;
    CALLGRIND_TOGGLE_COLLECT;
#endif

    mkpp::host::MechanismRegistry::execute(name, state, params);
    Kokkos::fence();

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

        auto registered = mkpp::host::MechanismRegistry::get_registered_mechanisms();
        std::string supported_str = "";
        for (size_t i = 0; i < registered.size(); ++i) {
            supported_str += registered[i] + (i + 1 < registered.size() ? "|" : "");
        }

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
                          << "  --mechanism " << supported_str << " (default: chapman)\n"
                          << "  --cells N                             (default: 10000)\n"
                          << "  --steps N                             (default: 30)\n"
                          << "  --dt DT                               (default: 60.0)\n";
                Kokkos::finalize();
                return 0;
            }
        }

        if (!mkpp::host::MechanismRegistry::has_mechanism(mechanism)) {
            std::string supported = "";
            for (size_t i = 0; i < registered.size(); ++i) {
                supported += registered[i] + (i + 1 < registered.size() ? ", " : "");
            }
            std::cerr << "FATAL ERROR: Unknown mechanism '" << mechanism << "'. Supported: " << supported << "\n";
            exit_code = 1;
        } else {
            run_benchmark(mechanism, num_cells, num_steps, dt);
        }
    }
    Kokkos::finalize();
    return exit_code;
}
