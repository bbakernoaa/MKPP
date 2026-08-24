#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <exception>
#include <iomanip>
#include <iostream>
#include <map>
#include <micm/CPU.hpp>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "generated_micm_ts1.hpp"

namespace {

int environment_integer(const char* name, int fallback) {
    const char* value = std::getenv(name);
    return value == nullptr ? fallback : std::stoi(value);
}

double environment_double(const char* name, double fallback) {
    const char* value = std::getenv(name);
    return value == nullptr ? fallback : std::stod(value);
}

void synchronize_completion() {
    std::atomic_thread_fence(std::memory_order_seq_cst);
}

std::string json_escape(const std::string& value) {
    std::ostringstream escaped;
    for (const unsigned char character : value) {
        if (character == '\\' || character == '"') escaped << '\\';
        escaped << character;
    }
    return escaped.str();
}

}  // namespace

int main() {
    try {
        constexpr const char* zero_sha =
            "0000000000000000000000000000000000000000000000000000000000000000";
        constexpr const char* solver_id = "micm";
        constexpr const char* mechanism_id = "ts1";
        const int cells = environment_integer("NUM_CELLS", 1);
        const int steps = environment_integer("NUM_STEPS", 1);
        const int repetitions = environment_integer("REPETITIONS", 1);
        const double dt = environment_double("DT_SECONDS", 60.0);
        if (cells < 1 || steps < 1 || repetitions < 1 || !std::isfinite(dt) || dt <= 0.0) {
            throw std::invalid_argument("positive cells, steps, repetitions, and dt are required");
        }

        auto parameters = micm::RosenbrockSolverParameters::ThreeStageRosenbrockParameters();
        auto solver =
            bench::Ts1::Build(micm::CpuSolverBuilder<micm::RosenbrockSolverParameters>(parameters));
        auto state = solver.GetState(cells);

        // The generated pinned binding initializes all 210 species and every named
        // photolysis/custom parameter by canonical name. No raw index is used.
        const auto reset_state = [&]() {
            bench::Ts1::InitState(state, cells);
            solver.UpdateStateParameters(state);
        };

        reset_state();
        const auto warmup = solver.Solve(dt, state);  // real MICM TS1 Solve
        if (warmup.state_ != micm::SolverState::Converged) {
            throw std::runtime_error("TS1 warmup did not converge");
        }

        micm::SolverStats work{};
        double elapsed_ms = 0.0;
        for (int repetition = 0; repetition < repetitions; ++repetition) {
            reset_state();  // reset before every timed sample
            synchronize_completion();
            const auto start_timing = std::chrono::steady_clock::now();
            for (int step = 0; step < steps; ++step) {
                const auto result = solver.Solve(dt, state);  // real pinned MICM Solve
                if (result.state_ != micm::SolverState::Converged) {
                    throw std::runtime_error("TS1 Solve did not converge");
                }
                work.function_calls_ += result.stats_.function_calls_;
                work.jacobian_updates_ += result.stats_.jacobian_updates_;
                work.number_of_steps_ += result.stats_.number_of_steps_;
            }
            synchronize_completion();  // synchronous MICM CPU completion boundary
            const auto stop_timing = std::chrono::steady_clock::now();
            elapsed_ms +=
                std::chrono::duration<double, std::milli>(stop_timing - start_timing).count();
        }

        // Stable canonical name order in JSON, independent of MICM's native map.
        std::map<std::string, std::size_t> species_map;
        for (const auto& [name, native_index] : state.variable_map_)
            species_map.emplace(name, native_index);
        // M is the canonical fixed third body. MICM parameterizes it from
        // Conditions::air_density_ rather than storing it in variable_map_.
        if (species_map.size() != 209 || species_map.contains("M"))
            throw std::runtime_error("TS1 binding does not expose 209 active names plus fixed M");

        std::ostringstream json;
        json << std::setprecision(17)
             << "{\"schema_version\":1,\"campaign_id\":\"ts1-smoke\",\"run_id\":\"micm-ts1-0\","
                "\"block\":0,\"order_position\":0,\"solver\":{\"id\":\""
             << solver_id << "\",\"version\":\"" << MICM_BENCHMARK_VERSION << "\",\"revision\":\""
             << MICM_BENCHMARK_REVISION
             << "\",\"backend\":\"cpu\",\"method\":\"three-stage-rosenbrock\"},"
                "\"manifest\":{\"id\":\""
             << mechanism_id << "\",\"version\":\"1\",\"sha256\":\"" << zero_sha
             << "\"},\"scenario\":{\"id\":\"ts1-default\",\"version\":\"1\",\"sha256\":\""
             << zero_sha << "\"},\"configuration\":{\"id\":\"micm-ts1-ros3\",\"sha256\":\""
             << zero_sha << "\",\"frozen\":true,\"controls\":{\"dt_seconds\":" << dt
             << "}},\"build\":{\"binary_sha256\":\"" << zero_sha << "\",\"asset_sha256\":[\""
             << zero_sha
             << "\"],\"compiler\":\"c++20\",\"flags\":[],\"precision\":\"binary64\"},"
                "\"resources\":{\"hardware_id\":\"local\",\"physical_cores\":1,\"threads\":1,"
                "\"affinity\":\"unspecified\",\"numa_policy\":\"unspecified\"},"
                "\"timing\":{\"boundary\":\"steady_state_solve\",\"elapsed_ms\":"
             << elapsed_ms << ",\"cell_steps\":" << cells * steps * repetitions
             << ",\"clock\":\"std::chrono::steady_clock\",\"synchronized\":true,"
                "\"synchronization\":\"synchronous MICM CPU Solve plus atomic "
                "fence\",\"lifecycle_ms\":{}},"
                "\"state\":{\"checkpoints\":[{\"time_seconds\":"
             << steps * dt << ",\"values\":{";
        bool first = true;
        for (const auto& [name, native_index] : species_map) {
            if (!first) json << ',';
            first = false;
            json << '"' << json_escape(name) << "\":" << state.variables_[0][native_index];
        }
        json << ",\"M\":" << state.conditions_[0].air_density_;
        json << "}}]},\"work\":{\"rhs_evaluations\":{\"available\":true,\"value\":"
             << work.function_calls_ << "},\"jacobian_evaluations\":{\"available\":true,\"value\":"
             << work.jacobian_updates_ << "}},\"status\":\"success\",\"diagnostics\":[]}";
        std::cout << json.str() << '\n';  // stdout is exactly one JSON result
        return EXIT_SUCCESS;
    } catch (const std::exception& error) {
        std::cerr << "FATAL ERROR: MICM TS1 runner: " << error.what() << '\n';
        return EXIT_FAILURE;
    }
}
