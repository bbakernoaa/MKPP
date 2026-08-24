#include <micm/CPU.hpp>
#include <micm/process/chemical_reaction_builder.hpp>
#include <micm/util/types.hpp>

#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <exception>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

constexpr const char* kZeroSha256 = "0000000000000000000000000000000000000000000000000000000000000000";
constexpr const char* kSolverId = "micm";

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

std::string json_escape(const std::string& value) {
  std::ostringstream result;
  for (const unsigned char character : value) {
    switch (character) {
      case '\\': result << "\\\\"; break;
      case '"': result << "\\\""; break;
      case '\n': result << "\\n"; break;
      case '\r': result << "\\r"; break;
      case '\t': result << "\\t"; break;
      default:
        if (character < 0x20) {
          result << "\\u" << std::hex << std::setw(4) << std::setfill('0') << static_cast<int>(character);
        } else {
          result << character;
        }
    }
  }
  return result.str();
}

void synchronize_solver() {
  // MICM's CPU Solve call is synchronous. The fence makes that completion
  // boundary explicit and prevents compiler motion across the measured region.
  std::atomic_thread_fence(std::memory_order_seq_cst);
}

}  // namespace

int main() {
  try {
    const int num_cells = environment_integer("NUM_CELLS", 1);
    const int num_steps = environment_integer("NUM_STEPS", 1);
    const double dt = environment_double("DT_SECONDS", 60.0);
    const double j1 = environment_double("J1", 1.0e-12);
    const double j3 = environment_double("J3", 1.0e-4);
    if (num_cells < 1 || num_steps < 1 || !std::isfinite(dt) || dt <= 0.0) {
      throw std::invalid_argument("NUM_CELLS, NUM_STEPS, and DT_SECONDS must be positive");
    }

    micm::Species O("O"), O2("O2"), O3("O3"), M("M");
    micm::Phase gas_phase{"gas", std::vector<micm::PhaseSpecies>{O, O2, O3, M}};
    micm::System system{gas_phase};

    const micm::Process reaction_J1 = micm::ChemicalReactionBuilder()
        .SetReactants({O2})
        .SetProducts({micm::StoichSpecies(O, 2), micm::StoichSpecies(O2, 1)})
        .SetRateConstant(micm::UserDefinedRateConstantParameters{.label_ = "J1"})
        .SetPhase(gas_phase)
        .Build();
    const micm::Process reaction_O3_formation = micm::ChemicalReactionBuilder()
        .SetReactants({O, O2, M})
        .SetProducts({micm::StoichSpecies(O3, 1), micm::StoichSpecies(O2, 1), micm::StoichSpecies(M, 1)})
        .SetRateConstant(micm::ArrheniusRateConstantParameters{.A_ = 6.0e-34})
        .SetPhase(gas_phase)
        .Build();
    const micm::Process reaction_J3 = micm::ChemicalReactionBuilder()
        .SetReactants({O3})
        .SetProducts({micm::StoichSpecies(O, 1), micm::StoichSpecies(O2, 1)})
        .SetRateConstant(micm::UserDefinedRateConstantParameters{.label_ = "J3"})
        .SetPhase(gas_phase)
        .Build();
    const micm::Process reaction_O_O3 = micm::ChemicalReactionBuilder()
        .SetReactants({O, O3})
        .SetProducts({micm::StoichSpecies(O2, 2)})
        .SetRateConstant(micm::ArrheniusRateConstantParameters{.A_ = 8.0e-12})
        .SetPhase(gas_phase)
        .Build();

    auto parameters = micm::RosenbrockSolverParameters::ThreeStageRosenbrockParameters();
    const std::vector<micm::Process> reactions = {
        reaction_J1, reaction_O3_formation, reaction_J3, reaction_O_O3};
    auto solver = micm::CpuSolverBuilder<micm::RosenbrockSolverParameters>(parameters)
                      .SetSystem(system)
                      .SetReactions(reactions)
                      .SetIgnoreUnusedSpecies(true)
                      .Build();
    auto state = solver.GetState(num_cells);

    // Canonical-to-native species_map / species_index resolution is always by
    // name. No cross-solver raw-index assumption is permitted.
    const std::map<std::string, std::size_t> species_index = {
        {"O", state.variable_map_.at("O")},
        {"O2", state.variable_map_.at("O2")},
        {"O3", state.variable_map_.at("O3")},
        {"M", state.variable_map_.at("M")},
    };

    const auto reset_state = [&]() {
      for (int cell = 0; cell < num_cells; ++cell) {
        state.conditions_[cell].temperature_ = 288.15;
        state.conditions_[cell].pressure_ = 101325.0;
        state.variables_[cell][species_index.at("O")] = 1.0e10;
        state.variables_[cell][species_index.at("O2")] = 2.0e10;
        state.variables_[cell][species_index.at("O3")] = 3.0e10;
        state.variables_[cell][species_index.at("M")] = 4.0e10;
      }
      state.SetCustomRateParameter("J1", std::vector<double>(num_cells, j1));
      state.SetCustomRateParameter("J3", std::vector<double>(num_cells, j3));
      solver.UpdateStateParameters(state);
    };

    reset_state();
    const auto warmup_result = solver.Solve(dt, state);  // real MICM warmup, outside timing
    if (warmup_result.state_ != micm::SolverState::Converged) {
      throw std::runtime_error("MICM warmup did not converge: " + micm::SolverStateToString(warmup_result.state_));
    }
    reset_state();            // reset before every timed sample
    synchronize_solver();

    micm::SolverStats work{};
    const auto start_timing = std::chrono::steady_clock::now();
    for (int step = 0; step < num_steps; ++step) {
      const auto solve_result = solver.Solve(dt, state);  // real pinned MICM Solve call
      if (solve_result.state_ != micm::SolverState::Converged) {
        throw std::runtime_error("MICM Solve did not converge: " + micm::SolverStateToString(solve_result.state_));
      }
      work.function_calls_ += solve_result.stats_.function_calls_;
      work.jacobian_updates_ += solve_result.stats_.jacobian_updates_;
      work.number_of_steps_ += solve_result.stats_.number_of_steps_;
      work.accepted_ += solve_result.stats_.accepted_;
      work.rejected_ += solve_result.stats_.rejected_;
      work.decompositions_ += solve_result.stats_.decompositions_;
      work.solves_ += solve_result.stats_.solves_;
    }
    synchronize_solver();
    const auto stop_timing = std::chrono::steady_clock::now();
    const double elapsed_ms = std::chrono::duration<double, std::milli>(stop_timing - start_timing).count();

    const std::string campaign_id = environment_string("CAMPAIGN_ID", "chapman-smoke");
    const std::string run_id = environment_string("RUN_ID", "micm-chapman-0");
    const int block = environment_integer("BLOCK_ID", 0);
    const int order_position = environment_integer("ORDER_POSITION", 0);
    const double final_time = dt * num_steps;

    // stdout is reserved for exactly one JSON runner-result object. All
    // diagnostics and fatal errors are written to stderr.
    std::ostringstream json;
    json << std::setprecision(17)
         << "{\"schema_version\":1,\"campaign_id\":\"" << json_escape(campaign_id)
         << "\",\"run_id\":\"" << json_escape(run_id) << "\",\"block\":" << block
         << ",\"order_position\":" << order_position
         << ",\"solver\":{\"id\":\"" << kSolverId << "\",\"version\":\"" << MICM_BENCHMARK_VERSION
         << "\",\"revision\":\"" << MICM_BENCHMARK_REVISION
         << "\",\"backend\":\"cpu\",\"method\":\"three-stage-rosenbrock\"}"
         << ",\"manifest\":{\"id\":\"chapman\",\"version\":\"1\",\"sha256\":\"" << kZeroSha256 << "\"}"
         << ",\"scenario\":{\"id\":\"chapman-default\",\"version\":\"1\",\"sha256\":\"" << kZeroSha256 << "\"}"
         << ",\"configuration\":{\"id\":\"micm-ros3-default\",\"sha256\":\"" << kZeroSha256
         << "\",\"frozen\":true,\"controls\":{\"dt_seconds\":" << dt << "}}"
         << ",\"build\":{\"binary_sha256\":\"" << kZeroSha256 << "\",\"asset_sha256\":[\"" << kZeroSha256
         << "\"],\"compiler\":\"c++20\",\"flags\":[],\"precision\":\"binary64\"}"
         << ",\"resources\":{\"hardware_id\":\"local\",\"physical_cores\":1,\"threads\":1,"
            "\"affinity\":\"unspecified\",\"numa_policy\":\"unspecified\"}"
         << ",\"timing\":{\"boundary\":\"steady_state_solve\",\"elapsed_ms\":" << elapsed_ms
         << ",\"cell_steps\":" << (num_cells * num_steps)
         << ",\"clock\":\"std::chrono::steady_clock\",\"synchronized\":true,"
            "\"synchronization\":\"synchronous MICM CPU Solve plus atomic fence\",\"lifecycle_ms\":{}}"
         << ",\"state\":{\"checkpoints\":[{\"time_seconds\":" << final_time << ",\"values\":{";
    bool first = true;
    for (const char* name : {"O", "O2", "O3", "M"}) {
      if (!first) json << ',';
      first = false;
      json << '\"' << name << "\":" << state.variables_[0][species_index.at(name)];
    }
    json << "}}]},\"work\":{"
         << "\"rhs_calls\":{\"available\":true,\"value\":" << work.function_calls_ << "},"
         << "\"jacobian_builds\":{\"available\":true,\"value\":" << work.jacobian_updates_ << "},"
         << "\"internal_steps\":{\"available\":true,\"value\":" << work.number_of_steps_ << "},"
         << "\"accepted_steps\":{\"available\":true,\"value\":" << work.accepted_ << "},"
         << "\"rejected_steps\":{\"available\":true,\"value\":" << work.rejected_ << "},"
         << "\"factorizations\":{\"available\":true,\"value\":" << work.decompositions_ << "},"
         << "\"linear_solves\":{\"available\":true,\"value\":" << work.solves_ << "}},"
         << "\"status\":\"success\",\"diagnostics\":[]}";
    std::cout << json.str() << '\n';
    return 0;
  } catch (const std::exception& error) {
    std::cerr << "FATAL ERROR: MICM Chapman runner failed: " << error.what() << '\n';
    return 5;
  }
}
