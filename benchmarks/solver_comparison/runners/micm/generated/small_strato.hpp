// Generated from canonical OpenAtmos JSON. Do not edit.
#pragma once

#include <micm/CPU.hpp>
#include <cmath>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

namespace bench::small_strato {

inline const micm::PhaseSpecies& PhaseSpeciesByName(const micm::Phase& phase, std::string_view name) {
  for (const auto& value : phase.phase_species_) if (value.species_.name_ == name) return value;
  throw std::runtime_error("OpenAtmos binding species lookup failed: " + std::string(name));
}
inline const micm::Species& SpeciesByName(const micm::Phase& phase, std::string_view name) {
  return PhaseSpeciesByName(phase, name).species_;
}

inline micm::Phase CreateGasPhase() {
  std::vector<micm::PhaseSpecies> species;
  { auto value = micm::Species("O");
    species.emplace_back(value); }
  { auto value = micm::Species("O1D");
    species.emplace_back(value); }
  { auto value = micm::Species("O3");
    species.emplace_back(value); }
  { auto value = micm::Species("NO");
    species.emplace_back(value); }
  { auto value = micm::Species("NO2");
    species.emplace_back(value); }
  { auto value = micm::Species("M");
    value.SetThirdBody();
    species.emplace_back(value); }
  { auto value = micm::Species("O2");
    species.emplace_back(value); }
  return micm::Phase{"gas", species};
}

inline std::vector<micm::Process> CreateProcesses(const micm::Phase& gas_phase) {
  std::vector<micm::Process> processes;
  processes.reserve(10);
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "O2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "O"), 2.0 } })
    .SetRateConstant(micm::UserDefinedRateConstantParameters{ .label_ = "j_small_strato.yaml_0000" })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "O"), SpeciesByName(gas_phase, "O2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "O3"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 8.018e-17, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "O3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "O"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "O2"), 1.0 } })
    .SetRateConstant(micm::UserDefinedRateConstantParameters{ .label_ = "j_small_strato.yaml_0002" })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "O"), SpeciesByName(gas_phase, "O3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "O2"), 2.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.576e-15, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "O3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "O1D"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "O2"), 1.0 } })
    .SetRateConstant(micm::UserDefinedRateConstantParameters{ .label_ = "j_small_strato.yaml_0004" })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "O1D"), SpeciesByName(gas_phase, "M") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "O"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "M"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 7.11e-11, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "O1D"), SpeciesByName(gas_phase, "O3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "O2"), 2.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.2e-10, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "NO"), SpeciesByName(gas_phase, "O3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "NO2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "O2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 6.062e-15, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "NO2"), SpeciesByName(gas_phase, "O") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "NO"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "O2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.069e-11, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "NO2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "NO"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "O"), 1.0 } })
    .SetRateConstant(micm::UserDefinedRateConstantParameters{ .label_ = "j_small_strato.yaml_0009" })
.SetPhase(gas_phase).Build());
  return processes;
}

}  // namespace bench::small_strato
