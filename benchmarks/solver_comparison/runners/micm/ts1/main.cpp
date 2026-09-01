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

std::string environment_string(const char* name, const char* fallback) {
    const char* value = std::getenv(name);
    return value == nullptr ? fallback : value;
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
        const int warmups = environment_integer("WARMUPS", 1);
        const int repetitions = environment_integer("REPETITIONS", 1);
        const double dt = environment_double("DT_SECONDS", 60.0);
        if (cells < 1 || steps < 1 || warmups < 1 || repetitions < 1 || !std::isfinite(dt) || dt <= 0.0) {
            throw std::invalid_argument("positive cells, steps, warmups, repetitions, and dt are required");
        }

        auto parameters = micm::RosenbrockSolverParameters::ThreeStageRosenbrockParameters();
        parameters.max_number_of_steps_ = bench::Ts1::kSolverMaxSteps;
        auto solver =
            bench::Ts1::Build(micm::CpuSolverBuilder<micm::RosenbrockSolverParameters>(parameters));
        auto state = solver.GetState(cells);
        // The shared TS1 environment owns equivalence tolerances.  They are
        // numerical controls, not chemistry-specific runner adjustments.
        state.SetRelativeTolerance(bench::Ts1::kSolverRtol);
        state.SetAbsoluteTolerances(std::vector<micm::Real>(state.variables_.NumColumns(), bench::Ts1::kSolverAtol));

        // The generated pinned binding initializes all 210 species and every named
        // photolysis/custom parameter by canonical name. No raw index is used.
        const auto reset_state = [&]() {
            bench::Ts1::InitState(state, cells);
            solver.UpdateStateParameters(state);
        };
        const auto solve_schedule = [&]() {
            for (micm::Index segment = 0; segment < bench::Ts1::kForcingSegmentCount; ++segment) {
                bench::Ts1::ApplyForcingSegment(state, cells, segment);
                solver.UpdateStateParameters(state);
                const auto result = solver.Solve(bench::Ts1::kForcingSegmentDurations[segment], state);
                if (result.state_ != micm::SolverState::Converged)
                    throw std::runtime_error("TS1 scheduled Solve did not converge");
            }
        };

        reset_state();
        if (std::getenv("EMIT_INITIAL_RATE_CONSTANTS") != nullptr) {
            std::cout << std::setprecision(17) << '[';
            for (std::size_t index = 0; index < state.rate_constants_.NumColumns(); ++index) {
                if (index != 0) std::cout << ',';
                std::cout << state.rate_constants_[0][index];
            }
            std::cout << "]\n";
            return EXIT_SUCCESS;
        }
        // Emit exactly the initial chemical tendency when requested.  This is
        // diagnostic-only and deliberately runs before either solver takes an
        // integration step, so it is a fair MKPP/MICM chemistry audit.
        if (std::getenv("EMIT_INITIAL_RHS") != nullptr) {
            micm::Matrix<micm::Real> forcing(cells, state.variables_.NumColumns(), 0.0);
            solver.solver_.rates_.AddForcingTerms(state, state.variables_, forcing);
            std::map<std::string, std::size_t> species_map;
            for (const auto& [name, native_index] : state.variable_map_)
                species_map.emplace(name, native_index);
            std::cout << std::setprecision(17) << '{';
            bool first = true;
            for (const auto& [name, native_index] : species_map) {
                if (!first) std::cout << ',';
                first = false;
                std::cout << '"' << json_escape(name) << "\":" << forcing[0][native_index];
            }
            std::cout << ",\"M\":0}\n";
            return EXIT_SUCCESS;
        }
        for (int warmup_index = 0; warmup_index < warmups; ++warmup_index) {
            reset_state();
            solve_schedule();
        }

        micm::SolverStats work{};
        double elapsed_ms = 0.0;
        for (int repetition = 0; repetition < repetitions; ++repetition) {
            reset_state();  // reset before every timed sample
            synchronize_completion();
            const auto start_timing = std::chrono::steady_clock::now();
            solve_schedule();
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

        const std::string campaign_id = environment_string("CAMPAIGN_ID", "ts1-smoke");
        const std::string run_id = environment_string("RUN_ID", "micm-ts1-0");
        const int block = environment_integer("BLOCK_ID", 0);
        const int order_position = environment_integer("ORDER_POSITION", 0);
        const std::string manifest_version = environment_string("MANIFEST_VERSION", "1.0.0");
        const std::string manifest_sha256 = environment_string("MANIFEST_SHA256", zero_sha);
        const std::string scenario_id = environment_string("SCENARIO_ID", "ts1-measurement-v1");
        const std::string scenario_version = environment_string("SCENARIO_VERSION", "1.0.0");
        const std::string scenario_sha256 = environment_string("SCENARIO_SHA256", zero_sha);
        const std::string configuration_id = environment_string("CONFIGURATION_ID", "micm-ts1-ros3");
        const std::string configuration_sha256 = environment_string("CONFIGURATION_SHA256", zero_sha);
        double schedule_seconds = 0.0;
        for (micm::Index segment = 0; segment < bench::Ts1::kForcingSegmentCount; ++segment)
            schedule_seconds += bench::Ts1::kForcingSegmentDurations[segment];
        std::ostringstream json;
        json << std::setprecision(17)
             << "{\"schema_version\":1,\"campaign_id\":\"" << json_escape(campaign_id) << "\",\"run_id\":\"" << json_escape(run_id) << "\","
                "\"block\":" << block << ",\"order_position\":" << order_position << ",\"solver\":{\"id\":\""
             << solver_id << "\",\"version\":\"" << MICM_BENCHMARK_VERSION << "\",\"revision\":\""
             << MICM_BENCHMARK_REVISION
             << "\",\"backend\":\"cpu\",\"method\":\"three-stage-rosenbrock\"},"
                "\"manifest\":{\"id\":\""
             << mechanism_id << "\",\"version\":\"" << json_escape(manifest_version) << "\",\"sha256\":\"" << json_escape(manifest_sha256)
             << "\"},\"scenario\":{\"id\":\"" << json_escape(scenario_id) << "\",\"version\":\"" << json_escape(scenario_version) << "\",\"sha256\":\""
             << json_escape(scenario_sha256) << "\"},\"configuration\":{\"id\":\"" << json_escape(configuration_id) << "\",\"sha256\":\""
             << json_escape(configuration_sha256) << "\",\"frozen\":true,\"controls\":{\"schedule_segments\":"
             << bench::Ts1::kForcingSegmentCount << ",\"schedule_seconds\":" << schedule_seconds
             << "}},\"build\":{\"binary_sha256\":\"" << zero_sha << "\",\"asset_sha256\":[\""
             << zero_sha
             << "\"],\"compiler\":\"c++20\",\"flags\":[],\"precision\":\"binary64\"},"
                "\"resources\":{\"hardware_id\":\"local\",\"physical_cores\":1,\"threads\":1,"
                "\"affinity\":\"unspecified\",\"numa_policy\":\"unspecified\"},"
                "\"timing\":{\"boundary\":\"steady_state_solve\",\"elapsed_ms\":"
             << elapsed_ms << ",\"cell_steps\":" << cells * bench::Ts1::kForcingSegmentCount * repetitions
             << ",\"clock\":\"std::chrono::steady_clock\",\"synchronized\":true,"
                "\"synchronization\":\"synchronous MICM CPU Solve plus atomic "
                "fence\",\"lifecycle_ms\":{}},"
                "\"state\":{\"checkpoints\":[{\"time_seconds\":"
             << schedule_seconds << ",\"values\":{";
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
