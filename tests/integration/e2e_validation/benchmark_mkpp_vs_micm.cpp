#include <Kokkos_Core.hpp>

#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>

// MICM includes
#include <micm/CPU.hpp>
#include <micm/process/chemical_reaction_builder.hpp>
#include <micm/util/types.hpp>

// MKPP includes
#include "chapman.hpp"

using ExecSpace = Kokkos::DefaultExecutionSpace;

// ---------------------------------------------------------------------------
// MKPP Functor
// ---------------------------------------------------------------------------
struct MKPPDualFunctor {
    using ViewType = Kokkos::View<double**, Kokkos::LayoutLeft, typename ExecSpace::memory_space>;
    ViewType m_state;
    double m_dt;
    const double* m_jvals;

    MKPPDualFunctor(ViewType state, double dt, const double* jvals)
        : m_state(state), m_dt(dt), m_jvals(jvals) {}

    KOKKOS_INLINE_FUNCTION
    void operator()(const int cell_idx) const {
        auto sub_state = Kokkos::subview(m_state, cell_idx, Kokkos::ALL());
        mkpp::SolverKernels<ExecSpace> solver;
        solver.integrate(m_dt, sub_state, m_jvals);
    }
};

// ---------------------------------------------------------------------------
// Direct C++ Benchmark
// ---------------------------------------------------------------------------
int main(int argc, char* argv[]) {
    Kokkos::initialize(argc, argv);
    {
        const int num_cells = 1000;
        const int num_steps = 100;
        const double dt = 60.0;

        std::cout << "==========================================================================" << std::endl;
        std::cout << "      Direct C++ Benchmark: MKPP vs NCAR/MICM (Chapman Mechanism)       " << std::endl;
        std::cout << "==========================================================================" << std::endl;
        std::cout << "Grid Cells : " << num_cells << std::endl;
        std::cout << "Timesteps  : " << num_steps << std::endl;
        std::cout << "Step Size  : " << dt << " s\n" << std::endl;

        // 1. Setup MICM System
        micm::Species o("O"), o2("O2"), o3("O3"), m("M");
        micm::Phase gas_phase{"gas", std::vector<micm::PhaseSpecies>{o, o2, o3, m}};
        micm::System system{gas_phase};

        micm::Process r1 = micm::ChemicalReactionBuilder()
            .SetReactants({o2})
            .SetProducts({micm::StoichSpecies(o, 2)})
            .SetRateConstant(micm::UserDefinedRateConstantParameters{.label_ = "J1"})
            .SetPhase(gas_phase)
            .Build();

        micm::Process r2 = micm::ChemicalReactionBuilder()
            .SetReactants({o, o2, m})
            .SetProducts({micm::StoichSpecies(o3, 1), micm::StoichSpecies(m, 1)})
            .SetRateConstant(micm::ArrheniusRateConstantParameters{.A_ = 6.0e-34})
            .SetPhase(gas_phase)
            .Build();

        micm::Process r3 = micm::ChemicalReactionBuilder()
            .SetReactants({o3})
            .SetProducts({micm::StoichSpecies(o, 1), micm::StoichSpecies(o2, 1)})
            .SetRateConstant(micm::UserDefinedRateConstantParameters{.label_ = "J3"})
            .SetPhase(gas_phase)
            .Build();

        micm::Process r4 = micm::ChemicalReactionBuilder()
            .SetReactants({o, o3})
            .SetProducts({micm::StoichSpecies(o2, 2)})
            .SetRateConstant(micm::ArrheniusRateConstantParameters{.A_ = 8.0e-12})
            .SetPhase(gas_phase)
            .Build();

        std::vector<micm::Process> reactions{r1, r2, r3, r4};
        micm::RosenbrockSolverParameters params = micm::RosenbrockSolverParameters::ThreeStageRosenbrockParameters();

        auto micm_solver = micm::CpuSolverBuilder<micm::RosenbrockSolverParameters>(params)
                    .SetSystem(system)
                    .SetReactions(reactions)
                    .SetIgnoreUnusedSpecies(true)
                    .Build();

        auto micm_state = micm_solver.GetState();
        micm_state.SetAbsoluteTolerances(std::vector<double>(4, 1.0e-12));
        micm_state.SetRelativeTolerance(1.0e-4);
        micm_state.conditions_[0].temperature_ = 288.15;
        micm_state.conditions_[0].pressure_ = 101325.0; // Pa
        micm_state.SetCustomRateParameter("J1", 1.0e-12);
        micm_state.SetCustomRateParameter("J3", 1.0e-4);

        micm_state.variables_[0] = {1.0e10, 2.0e10, 3.0e10, 4.0e10}; // [O, O2, O3, M]

        // 2. Warmup MICM
        micm_solver.Solve(dt, micm_state);

        // 3. Benchmark MICM
        auto start_micm = std::chrono::high_resolution_clock::now();
        for (int cell = 0; cell < num_cells; ++cell) {
            auto s = micm_solver.GetState();
            s.conditions_[0].temperature_ = 288.15;
            s.conditions_[0].pressure_ = 101325.0;
            s.SetCustomRateParameter("J1", 1.0e-12);
            s.SetCustomRateParameter("J3", 1.0e-4);
            s.variables_[0] = {1.0e10, 2.0e10, 3.0e10, 4.0e10};
            for (int step = 0; step < num_steps; ++step) {
                micm_solver.Solve(dt, s);
            }
        }
        auto end_micm = std::chrono::high_resolution_clock::now();
        double micm_time_ms = std::chrono::duration<double, std::milli>(end_micm - start_micm).count();

        // 4. Setup MKPP
        using ViewType = Kokkos::View<double**, Kokkos::LayoutLeft, typename ExecSpace::memory_space>;
        ViewType mkpp_state("state", num_cells, 4);
        Kokkos::View<double*, typename ExecSpace::memory_space> mkpp_jvals("jvals", 2);

        auto h_state = Kokkos::create_mirror_view(mkpp_state);
        auto h_jvals = Kokkos::create_mirror_view(mkpp_jvals);

        h_jvals(0) = 1.0e-12; // J1
        h_jvals(1) = 1.0e-4;  // J3
        Kokkos::deep_copy(mkpp_jvals, h_jvals);

        for (int i = 0; i < num_cells; ++i) {
            h_state(i, 0) = 1.0e10; // O
            h_state(i, 1) = 2.0e10; // O2
            h_state(i, 2) = 3.0e10; // O3
            h_state(i, 3) = 4.0e10; // M
        }
        Kokkos::deep_copy(mkpp_state, h_state);

        // 5. Warmup MKPP
        Kokkos::parallel_for("warmup", Kokkos::RangePolicy<ExecSpace>(0, num_cells),
                             MKPPDualFunctor(mkpp_state, dt, mkpp_jvals.data()));
        Kokkos::fence();

        // 6. Benchmark MKPP
        auto start_mkpp = std::chrono::high_resolution_clock::now();
        for (int step = 0; step < num_steps; ++step) {
            Kokkos::parallel_for("step", Kokkos::RangePolicy<ExecSpace>(0, num_cells),
                                 MKPPDualFunctor(mkpp_state, dt, mkpp_jvals.data()));
        }
        Kokkos::fence();
        auto end_mkpp = std::chrono::high_resolution_clock::now();
        double mkpp_time_ms = std::chrono::duration<double, std::milli>(end_mkpp - start_mkpp).count();

        // 7. Results
        std::cout << std::left << std::setw(28) << "Metric"
                  << std::left << std::setw(18) << "MKPP C++ (AOT)"
                  << std::left << std::setw(18) << "MICM C++"
                  << std::left << std::setw(18) << "Speedup" << std::endl;
        std::cout << std::string(80, '-') << std::endl;

        std::cout << std::left << std::setw(28) << "Execution Time (ms)"
                  << std::left << std::setw(18) << std::fixed << std::setprecision(2) << mkpp_time_ms
                  << std::left << std::setw(18) << std::fixed << std::setprecision(2) << micm_time_ms
                  << std::left << std::setw(18) << std::fixed << std::setprecision(2) << (micm_time_ms / mkpp_time_ms) << "x" << std::endl;

        double mkpp_throughput = (num_cells * num_steps) / (mkpp_time_ms / 1000.0);
        double micm_throughput = (num_cells * num_steps) / (micm_time_ms / 1000.0);

        std::cout << std::left << std::setw(28) << "Throughput (cell-st/s)"
                  << std::left << std::setw(18) << std::scientific << std::setprecision(2) << mkpp_throughput
                  << std::left << std::setw(18) << std::scientific << std::setprecision(2) << micm_throughput
                  << "--" << std::endl;

        std::cout << "==========================================================================" << std::endl;
    }
    Kokkos::finalize();
    return 0;
}
