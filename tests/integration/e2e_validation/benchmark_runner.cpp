#include <Kokkos_Core.hpp>

#include <chrono>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "saprc99.hpp"

using ExecSpace = Kokkos::DefaultExecutionSpace;

template <typename SolverKernelsType>
struct DiurnalCellFunctor {
    using ViewType = Kokkos::View<double**, Kokkos::LayoutLeft, typename ExecSpace::memory_space>;
    ViewType m_state;
    double m_dt;
    const double* m_jvals;

    DiurnalCellFunctor(ViewType state, double dt, const double* jvals)
        : m_state(state), m_dt(dt), m_jvals(jvals) {}

    KOKKOS_INLINE_FUNCTION
    void operator()(const int cell_idx) const {
        auto sub_state = Kokkos::subview(m_state, cell_idx, Kokkos::ALL());
        SolverKernelsType solver;
        solver.integrate(m_dt, sub_state, m_jvals);
    }
};

template <typename SolverKernelsType>
double run_diurnal_benchmark(int num_cells, int num_species, int num_steps, double dt,
                             std::vector<double>& final_state_out) {
    using ViewType = Kokkos::View<double**, Kokkos::LayoutLeft, typename ExecSpace::memory_space>;
    ViewType state("state", num_cells, num_species);

    // Zero jvals (photolysis rates set to zero for benchmark timing)
    Kokkos::View<double*, typename ExecSpace::memory_space> jvals_dev("jvals", 64);

    // Initialize initial concentrations matching KPP initial conditions
    auto host_state = Kokkos::create_mirror_view(state);
    const double cfactor = 2.447600e+13;

    for (int i = 0; i < num_cells; ++i) {
        for (int k = 0; k < num_species; ++k) host_state(i, k) = 0.0;

        // Match saprc99 initial conditions
        if (num_species >= 79) {
            host_state(i, 1) = (6.77e-4) * cfactor;
            host_state(i, 2) = (1.16e-3) * cfactor;
            host_state(i, 3) = (3.92e-4) * cfactor;
            host_state(i, 7) = (0.2) * cfactor;
            host_state(i, 8) = (5.e-2) * cfactor;
            host_state(i, 10) = (1.167e-2) * cfactor;
            host_state(i, 68) = (1.0e-1) * cfactor;   // NO
            host_state(i, 69) = (5.0e-2) * cfactor;   // NO2
            host_state(i, 74) = (1.0e+6) * cfactor;   // AIR
            host_state(i, 75) = (2.09e+5) * cfactor;  // O2
            host_state(i, 76) = (2.0e+04) * cfactor;  // H2O
            host_state(i, 78) = (1.0e0) * cfactor;    // CH4
        } else {
            for (int k = 0; k < num_species; ++k) host_state(i, k) = 1.0e8;
        }
    }
    Kokkos::deep_copy(state, host_state);

    // Warmup step
    Kokkos::parallel_for("warmup", Kokkos::RangePolicy<ExecSpace>(0, num_cells),
                         DiurnalCellFunctor<SolverKernelsType>(state, dt, jvals_dev.data()));
    Kokkos::fence();

    auto start = std::chrono::high_resolution_clock::now();
    for (int step = 0; step < num_steps; ++step) {
        Kokkos::parallel_for("diurnal_step", Kokkos::RangePolicy<ExecSpace>(0, num_cells),
                             DiurnalCellFunctor<SolverKernelsType>(state, dt, jvals_dev.data()));
    }
    Kokkos::fence();
    auto end = std::chrono::high_resolution_clock::now();

    Kokkos::deep_copy(host_state, state);
    final_state_out.resize(num_species);
    for (int k = 0; k < num_species; ++k) { final_state_out[k] = host_state(0, k); }

    std::chrono::duration<double, std::milli> elapsed = end - start;
    return elapsed.count();
}

int main(int argc, char** argv) {
    int num_cells = 1000;
    int num_steps = 1440;
    std::string mode = "full";  // "full" or "lumped"
    std::string csv_out = "";

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--cells" && i + 1 < argc) num_cells = std::stoi(argv[++i]);
        if (arg == "--steps" && i + 1 < argc) num_steps = std::stoi(argv[++i]);
        if (arg == "--mode" && i + 1 < argc) mode = argv[++i];
        if (arg == "--output" && i + 1 < argc) csv_out = argv[++i];
    }

    Kokkos::initialize(argc, argv);
    {
        std::vector<double> final_state;
        double time_ms = 0.0;

        if (mode == "lumped") {
            time_ms = run_diurnal_benchmark<mkpp::SolverKernels<ExecSpace>>(
                num_cells, 35, num_steps, 60.0, final_state);
        } else {
            time_ms = run_diurnal_benchmark<mkpp::SolverKernels<ExecSpace>>(
                num_cells, 79, num_steps, 60.0, final_state);
        }

        std::cout << "CELLS=" << num_cells << ", STEPS=" << num_steps << ", MODE=" << mode
                  << ", TIME_MS=" << std::fixed << std::setprecision(2) << time_ms
                  << ", THROUGHPUT=" << std::scientific << std::setprecision(3)
                  << ((double)num_cells * num_steps) / (time_ms / 1000.0) << "\n";

        if (!csv_out.empty()) {
            std::ofstream out(csv_out);
            out << "species_idx,concentration\n";
            for (size_t k = 0; k < final_state.size(); ++k) {
                out << k << "," << std::scientific << std::setprecision(12) << final_state[k]
                    << "\n";
            }
            out.close();
        }
    }
    Kokkos::finalize();
    return 0;
}
