#pragma once
#include <Kokkos_Core.hpp>

#include <string>

namespace mkpp {
namespace host {

/// @brief Serial host integrator for single-thread CPU benchmark parity.
/// @tparam SolverKernelsType Generated solver kernel type callable on host.
/// @tparam StateViewType Kokkos view type containing cell-major concentrations.
/// @param state Four-dimensional concentration view with cell extent in dimension 0.
/// @param dt Integration timestep in seconds.
/// @param steps Number of timesteps to integrate per cell.
/// @param jvals Pointer to Cloud-J photolysis rate array (may be nullptr if no photolysis).
template <typename SolverKernelsType, typename StateViewType>
void execute_mechanism_serial_steps(StateViewType state, const double dt, const int steps,
                                    const double* jvals = nullptr) {
    const int num_cells = state.extent(0);

    for (int cell_idx = 0; cell_idx < num_cells; ++cell_idx) {
        SolverKernelsType solver;
        auto sub_state = Kokkos::subview(state, cell_idx, Kokkos::ALL(), 0, 0);
        for (int step = 0; step < steps; ++step) { solver.integrate(dt, sub_state, jvals); }
    }
}

/// @brief Serial host integrator for a single timestep.
/// @tparam SolverKernelsType Generated solver kernel type callable on host.
/// @tparam StateViewType Kokkos view type containing cell-major concentrations.
/// @param state Four-dimensional concentration view with cell extent in dimension 0.
/// @param dt Integration timestep in seconds.
/// @param jvals Pointer to Cloud-J photolysis rate array (may be nullptr if no photolysis).
template <typename SolverKernelsType, typename StateViewType>
void execute_mechanism_serial(StateViewType state, const double dt, const double* jvals = nullptr) {
    execute_mechanism_serial_steps<SolverKernelsType>(state, dt, 1, jvals);
}

template <typename SolverKernelsType, typename StateViewType>
struct TiledCellIntegrator {
    StateViewType m_state;
    double m_dt;
    const double* m_jvals;

    TiledCellIntegrator(StateViewType s, double dt, const double* jvals = nullptr)
        : m_state(s), m_dt(dt), m_jvals(jvals) {}

    KOKKOS_INLINE_FUNCTION
    void operator()(const int cell_idx) const {
        SolverKernelsType solver;
        auto sub_state = Kokkos::subview(m_state, cell_idx, Kokkos::ALL(), 0, 0);
        solver.integrate(m_dt, sub_state, m_jvals);
    }
};

template <typename SolverKernelsType, typename StateViewType>
struct TiledCellTimeIntegrator {
    StateViewType m_state;
    double m_dt;
    int m_steps;
    const double* m_jvals;

    TiledCellTimeIntegrator(StateViewType s, double dt, int steps, const double* jvals = nullptr)
        : m_state(s), m_dt(dt), m_steps(steps), m_jvals(jvals) {}

    KOKKOS_INLINE_FUNCTION
    void operator()(const int cell_idx) const {
        SolverKernelsType solver;
        auto sub_state = Kokkos::subview(m_state, cell_idx, Kokkos::ALL(), 0, 0);
        for (int step = 0; step < m_steps; ++step) { solver.integrate(m_dt, sub_state, m_jvals); }
    }
};

/// @brief Integrate all requested timesteps with a single Kokkos launch.
/// @tparam SolverKernelsType Generated solver kernel type callable in the active execution space.
/// @tparam StateViewType Kokkos view type containing cell-major concentrations.
/// @param name Mechanism name used for Kokkos profiling labels.
/// @param state Four-dimensional concentration view with cell extent in dimension 0.
/// @param dt Integration timestep in seconds.
/// @param steps Number of timesteps to integrate per cell.
/// @param jvals Pointer to Cloud-J photolysis rate array (may be nullptr if no photolysis).
template <typename SolverKernelsType, typename StateViewType>
void execute_mechanism_steps(const std::string& name, StateViewType state, const double dt,
                             const int steps, const double* jvals = nullptr) {
    using ExecSpace = Kokkos::DefaultExecutionSpace;
    const int num_cells = state.extent(0);

    Kokkos::parallel_for(
        "MKPP_Grid_Dispatch_" + name,
        Kokkos::RangePolicy<ExecSpace>(0, num_cells, Kokkos::ChunkSize(64)),
        TiledCellTimeIntegrator<SolverKernelsType, StateViewType>(state, dt, steps, jvals));
}

template <typename SolverKernelsType, typename StateViewType>
void execute_mechanism(const std::string& name, StateViewType state, double dt,
                       const double* jvals = nullptr) {
    execute_mechanism_steps<SolverKernelsType>(name, state, dt, 1, jvals);
}

}  // namespace host

/// @brief Core handle implementation structure for MKPP Host Model API C ABI wrappers.
struct mkpp_handle_impl {
    std::size_t num_cells{0};
    std::size_t num_species{0};
    std::size_t num_reactions{0};
    std::size_t num_photolysis{0};
    bool is_initialized{false};

    // Unmanaged 2D view over host model species concentrations (num_cells, num_species)
    Kokkos::View<double**, Kokkos::LayoutLeft, Kokkos::HostSpace, Kokkos::MemoryUnmanaged> species_conc;

    // Unmanaged 1D views over host model meteorology (num_cells)
    Kokkos::View<double*, Kokkos::LayoutLeft, Kokkos::HostSpace, Kokkos::MemoryUnmanaged> temperature;
    Kokkos::View<double*, Kokkos::LayoutLeft, Kokkos::HostSpace, Kokkos::MemoryUnmanaged> pressure;
    Kokkos::View<double*, Kokkos::LayoutLeft, Kokkos::HostSpace, Kokkos::MemoryUnmanaged> air_density;

    // Unmanaged 2D view over host model photolysis rates (num_cells, num_photolysis)
    Kokkos::View<double**, Kokkos::LayoutLeft, Kokkos::HostSpace, Kokkos::MemoryUnmanaged> photolysis_rates;

    // Allocated scratch workspace memory for internal solver calculations
    Kokkos::View<double**, Kokkos::LayoutLeft> workspace_scratch;

    // Human-readable error diagnostic message for last failure
    std::string last_error_msg;

    void set_error(const std::string& msg) {
        last_error_msg = msg;
    }
};

}  // namespace mkpp
