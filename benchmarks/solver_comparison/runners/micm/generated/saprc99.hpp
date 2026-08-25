// Generated from canonical OpenAtmos JSON. Do not edit.
#pragma once

#include <micm/CPU.hpp>
#include <cmath>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

namespace bench::saprc99 {

inline const micm::PhaseSpecies& PhaseSpeciesByName(const micm::Phase& phase, std::string_view name) {
  for (const auto& value : phase.phase_species_) if (value.species_.name_ == name) return value;
  throw std::runtime_error("OpenAtmos binding species lookup failed: " + std::string(name));
}
inline const micm::Species& SpeciesByName(const micm::Phase& phase, std::string_view name) {
  return PhaseSpeciesByName(phase, name).species_;
}

inline micm::Phase CreateGasPhase() {
  std::vector<micm::PhaseSpecies> species;
  { auto value = micm::Species("O3");
    species.emplace_back(value); }
  { auto value = micm::Species("H2O2");
    species.emplace_back(value); }
  { auto value = micm::Species("NO");
    species.emplace_back(value); }
  { auto value = micm::Species("NO2");
    species.emplace_back(value); }
  { auto value = micm::Species("NO3");
    species.emplace_back(value); }
  { auto value = micm::Species("N2O5");
    species.emplace_back(value); }
  { auto value = micm::Species("HONO");
    species.emplace_back(value); }
  { auto value = micm::Species("HNO3");
    species.emplace_back(value); }
  { auto value = micm::Species("HNO4");
    species.emplace_back(value); }
  { auto value = micm::Species("SO2");
    species.emplace_back(value); }
  { auto value = micm::Species("H2SO4");
    species.emplace_back(value); }
  { auto value = micm::Species("CO");
    species.emplace_back(value); }
  { auto value = micm::Species("HCHO");
    species.emplace_back(value); }
  { auto value = micm::Species("CCHO");
    species.emplace_back(value); }
  { auto value = micm::Species("RCHO");
    species.emplace_back(value); }
  { auto value = micm::Species("ACET");
    species.emplace_back(value); }
  { auto value = micm::Species("MEK");
    species.emplace_back(value); }
  { auto value = micm::Species("HCOOH");
    species.emplace_back(value); }
  { auto value = micm::Species("MEOH");
    species.emplace_back(value); }
  { auto value = micm::Species("CCO_OH");
    species.emplace_back(value); }
  { auto value = micm::Species("RCO_OH");
    species.emplace_back(value); }
  { auto value = micm::Species("GLY");
    species.emplace_back(value); }
  { auto value = micm::Species("MGLY");
    species.emplace_back(value); }
  { auto value = micm::Species("BACL");
    species.emplace_back(value); }
  { auto value = micm::Species("CRES");
    species.emplace_back(value); }
  { auto value = micm::Species("BALD");
    species.emplace_back(value); }
  { auto value = micm::Species("ISOPROD");
    species.emplace_back(value); }
  { auto value = micm::Species("METHACRO");
    species.emplace_back(value); }
  { auto value = micm::Species("MVK");
    species.emplace_back(value); }
  { auto value = micm::Species("PROD2");
    species.emplace_back(value); }
  { auto value = micm::Species("DCB1");
    species.emplace_back(value); }
  { auto value = micm::Species("DCB2");
    species.emplace_back(value); }
  { auto value = micm::Species("DCB3");
    species.emplace_back(value); }
  { auto value = micm::Species("ETHENE");
    species.emplace_back(value); }
  { auto value = micm::Species("ISOPRENE");
    species.emplace_back(value); }
  { auto value = micm::Species("ALK1");
    species.emplace_back(value); }
  { auto value = micm::Species("ALK2");
    species.emplace_back(value); }
  { auto value = micm::Species("ALK3");
    species.emplace_back(value); }
  { auto value = micm::Species("ALK4");
    species.emplace_back(value); }
  { auto value = micm::Species("ALK5");
    species.emplace_back(value); }
  { auto value = micm::Species("ARO1");
    species.emplace_back(value); }
  { auto value = micm::Species("ARO2");
    species.emplace_back(value); }
  { auto value = micm::Species("OLE1");
    species.emplace_back(value); }
  { auto value = micm::Species("OLE2");
    species.emplace_back(value); }
  { auto value = micm::Species("TERP");
    species.emplace_back(value); }
  { auto value = micm::Species("RNO3");
    species.emplace_back(value); }
  { auto value = micm::Species("NPHE");
    species.emplace_back(value); }
  { auto value = micm::Species("PHEN");
    species.emplace_back(value); }
  { auto value = micm::Species("PAN");
    species.emplace_back(value); }
  { auto value = micm::Species("PAN2");
    species.emplace_back(value); }
  { auto value = micm::Species("PBZN");
    species.emplace_back(value); }
  { auto value = micm::Species("MA_PAN");
    species.emplace_back(value); }
  { auto value = micm::Species("CCO_OOH");
    species.emplace_back(value); }
  { auto value = micm::Species("RCO_O2");
    species.emplace_back(value); }
  { auto value = micm::Species("RCO_OOH");
    species.emplace_back(value); }
  { auto value = micm::Species("XN");
    species.emplace_back(value); }
  { auto value = micm::Species("XC");
    species.emplace_back(value); }
  { auto value = micm::Species("O3P");
    species.emplace_back(value); }
  { auto value = micm::Species("O1D");
    species.emplace_back(value); }
  { auto value = micm::Species("OH");
    species.emplace_back(value); }
  { auto value = micm::Species("HO2");
    species.emplace_back(value); }
  { auto value = micm::Species("C_O2");
    species.emplace_back(value); }
  { auto value = micm::Species("COOH");
    species.emplace_back(value); }
  { auto value = micm::Species("ROOH");
    species.emplace_back(value); }
  { auto value = micm::Species("RO2_R");
    species.emplace_back(value); }
  { auto value = micm::Species("R2O2");
    species.emplace_back(value); }
  { auto value = micm::Species("RO2_N");
    species.emplace_back(value); }
  { auto value = micm::Species("HOCOO");
    species.emplace_back(value); }
  { auto value = micm::Species("CCO_O2");
    species.emplace_back(value); }
  { auto value = micm::Species("BZCO_O2");
    species.emplace_back(value); }
  { auto value = micm::Species("BZNO2_O");
    species.emplace_back(value); }
  { auto value = micm::Species("BZ_O");
    species.emplace_back(value); }
  { auto value = micm::Species("MA_RCO3");
    species.emplace_back(value); }
  { auto value = micm::Species("TBU_O");
    species.emplace_back(value); }
  { auto value = micm::Species("AIR");
    value.SetThirdBody();
    species.emplace_back(value); }
  { auto value = micm::Species("O2");
    species.emplace_back(value); }
  { auto value = micm::Species("H2O");
    species.emplace_back(value); }
  { auto value = micm::Species("H2");
    species.emplace_back(value); }
  { auto value = micm::Species("CH4");
    species.emplace_back(value); }
  { auto value = micm::Species("M");
    value.SetThirdBody();
    species.emplace_back(value); }
  { auto value = micm::Species("N2");
    species.emplace_back(value); }
  { auto value = micm::Species("RO2");
    species.emplace_back(value); }
  return micm::Phase{"gas", species};
}

inline std::vector<micm::Process> CreateProcesses(const micm::Phase& gas_phase) {
  std::vector<micm::Process> processes;
  processes.reserve(211);
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "NO2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "NO"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "O3P"), 1.0 } })
    .SetRateConstant(micm::UserDefinedRateConstantParameters{ .label_ = "j_saprc99.yaml_0000" })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "O3P"), SpeciesByName(gas_phase, "O2"), SpeciesByName(gas_phase, "AIR") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "O3"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 5.68e-34, .B_ = -2.8, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "O3P"), SpeciesByName(gas_phase, "O3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "O2"), 2.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 8e-12, .B_ = 0.0, .C_ = -2060.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "O3P"), SpeciesByName(gas_phase, "NO"), SpeciesByName(gas_phase, "AIR") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "NO2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1e-31, .B_ = -1.6, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "O3P"), SpeciesByName(gas_phase, "NO2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "NO"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 6.5e-12, .B_ = 0.0, .C_ = 120.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "O3P"), SpeciesByName(gas_phase, "NO2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "NO3"), 1.0 } })
    .SetRateConstant(micm::TroeRateConstantParameters{ .k0_A_ = 9e-32, .k0_B_ = 0.0, .k0_C_ = 2.0, .kinf_A_ = 2.2e-11, .kinf_B_ = 0.0, .kinf_C_ = 0.0, .Fc_ = 0.8, .N_ = 1.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "O3"), SpeciesByName(gas_phase, "NO") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "NO2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.8e-12, .B_ = 0.0, .C_ = -1370.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "O3"), SpeciesByName(gas_phase, "NO2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "NO3"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.4e-13, .B_ = 0.0, .C_ = -2470.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "NO"), SpeciesByName(gas_phase, "NO3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "NO2"), 2.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.8e-11, .B_ = 0.0, .C_ = 110.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "NO"), SpeciesByName(gas_phase, "O2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "NO2"), 2.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 3.3e-39, .B_ = 0.0, .C_ = 530.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "NO2"), SpeciesByName(gas_phase, "NO3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "N2O5"), 1.0 } })
    .SetRateConstant(micm::TroeRateConstantParameters{ .k0_A_ = 2.8e-30, .k0_B_ = 0.0, .k0_C_ = 3.5, .kinf_A_ = 2e-12, .kinf_B_ = 0.0, .kinf_C_ = -0.2, .Fc_ = 0.45, .N_ = 1.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "N2O5") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "NO2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "NO3"), 1.0 } })
    .SetRateConstant(micm::TroeRateConstantParameters{ .k0_A_ = 0.001, .k0_B_ = 11000.0, .k0_C_ = 3.5, .kinf_A_ = 970000000000000.0, .kinf_B_ = 11080.0, .kinf_C_ = -0.1, .Fc_ = 0.45, .N_ = 1.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "N2O5"), SpeciesByName(gas_phase, "H2O") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HNO3"), 2.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 2.6e-22, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "NO2"), SpeciesByName(gas_phase, "NO3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "NO"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "NO2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 4.5e-14, .B_ = 0.0, .C_ = -1260.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "NO3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "NO"), 1.0 } })
    .SetRateConstant(micm::UserDefinedRateConstantParameters{ .label_ = "j_saprc99.yaml_0014" })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "NO3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "NO2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "O3P"), 1.0 } })
    .SetRateConstant(micm::UserDefinedRateConstantParameters{ .label_ = "j_saprc99.yaml_0015" })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "O3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "O3P"), 1.0 } })
    .SetRateConstant(micm::UserDefinedRateConstantParameters{ .label_ = "j_saprc99.yaml_0016" })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "O3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "O1D"), 1.0 } })
    .SetRateConstant(micm::UserDefinedRateConstantParameters{ .label_ = "j_saprc99.yaml_0017" })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "O1D"), SpeciesByName(gas_phase, "H2O") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "OH"), 2.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 2.2e-10, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "O1D"), SpeciesByName(gas_phase, "AIR") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "O3P"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 2.09e-11, .B_ = 0.0, .C_ = 95.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "OH"), SpeciesByName(gas_phase, "NO") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HONO"), 1.0 } })
    .SetRateConstant(micm::TroeRateConstantParameters{ .k0_A_ = 7e-31, .k0_B_ = 0.0, .k0_C_ = 2.6, .kinf_A_ = 3.6e-11, .kinf_B_ = 0.0, .kinf_C_ = 0.1, .Fc_ = 0.6, .N_ = 1.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "HONO") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "OH"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "NO"), 1.0 } })
    .SetRateConstant(micm::UserDefinedRateConstantParameters{ .label_ = "j_saprc99.yaml_0021" })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "HONO") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "NO2"), 1.0 } })
    .SetRateConstant(micm::UserDefinedRateConstantParameters{ .label_ = "j_saprc99.yaml_0022" })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "OH"), SpeciesByName(gas_phase, "HONO") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "NO2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 2.7e-12, .B_ = 0.0, .C_ = 260.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "OH"), SpeciesByName(gas_phase, "NO2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HNO3"), 1.0 } })
    .SetRateConstant(micm::TroeRateConstantParameters{ .k0_A_ = 2.43e-30, .k0_B_ = 0.0, .k0_C_ = 3.1, .kinf_A_ = 1.67e-11, .kinf_B_ = 0.0, .kinf_C_ = 2.1, .Fc_ = 0.6, .N_ = 1.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "OH"), SpeciesByName(gas_phase, "NO3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "NO2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 2e-11, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "OH"), SpeciesByName(gas_phase, "HNO3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "NO3"), 1.0 } })
    .SetRateConstant(micm::LambdaRateConstantParameters{ .label_ = "openatmos_ep2", .lambda_function_ = [](const micm::Conditions& c) { const auto k0 = 7.2e-15 * std::exp(785.0 / c.temperature_); const auto k2 = 4.1e-16 * std::exp(1440.0 / c.temperature_); const auto k3 = 1.9e-33 * std::exp(725.0 / c.temperature_) * c.air_density_; return k0 + k3 / (1.0 + k3 / k2); } })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "HNO3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "OH"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "NO2"), 1.0 } })
    .SetRateConstant(micm::UserDefinedRateConstantParameters{ .label_ = "j_saprc99.yaml_0027" })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "OH"), SpeciesByName(gas_phase, "CO") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 1.0 } })
    .SetRateConstant(micm::LambdaRateConstantParameters{ .label_ = "openatmos_ep3", .lambda_function_ = [](const micm::Conditions& c) { return 1.3e-13 * std::exp(0.0 / c.temperature_) + 3.19e-33 * std::exp(0.0 / c.temperature_) * c.air_density_; } })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "OH"), SpeciesByName(gas_phase, "O3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.9e-12, .B_ = 0.0, .C_ = -1000.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "HO2"), SpeciesByName(gas_phase, "NO") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "OH"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "NO2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 3.4e-12, .B_ = 0.0, .C_ = 270.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "HO2"), SpeciesByName(gas_phase, "NO2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HNO4"), 1.0 } })
    .SetRateConstant(micm::TroeRateConstantParameters{ .k0_A_ = 1.8e-31, .k0_B_ = 0.0, .k0_C_ = 3.2, .kinf_A_ = 4.7e-12, .kinf_B_ = 0.0, .kinf_C_ = 0.0, .Fc_ = 0.6, .N_ = 1.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "HNO4") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "NO2"), 1.0 } })
    .SetRateConstant(micm::TroeRateConstantParameters{ .k0_A_ = 4.1e-05, .k0_B_ = 10650.0, .k0_C_ = 0.0, .kinf_A_ = 5700000000000000.0, .kinf_B_ = 11170.0, .kinf_C_ = 0.0, .Fc_ = 0.5, .N_ = 1.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "HNO4") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 0.61 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "NO2"), 0.61 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "OH"), 0.39 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "NO3"), 0.39 } })
    .SetRateConstant(micm::UserDefinedRateConstantParameters{ .label_ = "j_saprc99.yaml_0033" })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "HNO4"), SpeciesByName(gas_phase, "OH") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "NO2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.5e-12, .B_ = 0.0, .C_ = 360.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "HO2"), SpeciesByName(gas_phase, "O3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "OH"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.4e-14, .B_ = 0.0, .C_ = -600.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "HO2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "H2O2"), 1.0 } })
    .SetRateConstant(micm::LambdaRateConstantParameters{ .label_ = "openatmos_ep3", .lambda_function_ = [](const micm::Conditions& c) { return 2.2e-13 * std::exp(600.0 / c.temperature_) + 1.85e-33 * std::exp(980.0 / c.temperature_) * c.air_density_; } })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "HO2"), SpeciesByName(gas_phase, "H2O") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "H2O2"), 1.0 } })
    .SetRateConstant(micm::LambdaRateConstantParameters{ .label_ = "openatmos_ep3", .lambda_function_ = [](const micm::Conditions& c) { return 3.08e-34 * std::exp(2800.0 / c.temperature_) + 2.59e-54 * std::exp(3180.0 / c.temperature_) * c.air_density_; } })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "NO3"), SpeciesByName(gas_phase, "HO2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "OH"), 0.8 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "NO2"), 0.8 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HNO3"), 0.2 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 4e-12, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "NO3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "NO2"), 2.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 8.5e-13, .B_ = 0.0, .C_ = -2450.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "H2O2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "OH"), 2.0 } })
    .SetRateConstant(micm::UserDefinedRateConstantParameters{ .label_ = "j_saprc99.yaml_0040" })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "H2O2"), SpeciesByName(gas_phase, "OH") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 2.9e-12, .B_ = 0.0, .C_ = -160.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "OH"), SpeciesByName(gas_phase, "HO2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "H2O"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "O2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 4.8e-11, .B_ = 0.0, .C_ = 250.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "OH"), SpeciesByName(gas_phase, "SO2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "H2SO4"), 1.0 } })
    .SetRateConstant(micm::TroeRateConstantParameters{ .k0_A_ = 4e-31, .k0_B_ = 0.0, .k0_C_ = 3.3, .kinf_A_ = 2e-12, .kinf_B_ = 0.0, .kinf_C_ = 0.0, .Fc_ = 0.45, .N_ = 1.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "OH"), SpeciesByName(gas_phase, "H2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 7.7e-12, .B_ = 0.0, .C_ = -2100.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "C_O2"), SpeciesByName(gas_phase, "NO") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "NO2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 2.8e-12, .B_ = 0.0, .C_ = 285.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "C_O2"), SpeciesByName(gas_phase, "HO2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "COOH"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 3.8e-13, .B_ = 0.0, .C_ = 780.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "C_O2"), SpeciesByName(gas_phase, "NO3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "NO2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.3e-12, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "C_O2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "MEOH"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 2.45e-14, .B_ = 0.0, .C_ = 710.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "C_O2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 2.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 2.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 5.9e-13, .B_ = 0.0, .C_ = -509.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "RO2_R"), SpeciesByName(gas_phase, "NO") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "NO2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 2.7e-12, .B_ = 0.0, .C_ = 360.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "RO2_R"), SpeciesByName(gas_phase, "HO2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "ROOH"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.9e-13, .B_ = 0.0, .C_ = 1300.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "RO2_R"), SpeciesByName(gas_phase, "NO3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "NO2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 2.3e-12, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "RO2_R"), SpeciesByName(gas_phase, "C_O2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 0.75 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MEOH"), 0.25 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 2e-13, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "RO2_R") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 3.5e-14, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "R2O2"), SpeciesByName(gas_phase, "NO") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "NO2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 2.7e-12, .B_ = 0.0, .C_ = 360.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "R2O2"), SpeciesByName(gas_phase, "HO2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.9e-13, .B_ = 0.0, .C_ = 1300.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "R2O2"), SpeciesByName(gas_phase, "NO3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "NO2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 2.3e-12, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "R2O2"), SpeciesByName(gas_phase, "C_O2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "C_O2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 2e-13, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "R2O2"), SpeciesByName(gas_phase, "RO2_R") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 3.5e-14, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "R2O2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "R2O2"), 2.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 0.0, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "RO2_N"), SpeciesByName(gas_phase, "NO") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RNO3"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 2.7e-12, .B_ = 0.0, .C_ = 360.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "RO2_N"), SpeciesByName(gas_phase, "HO2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "ROOH"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.9e-13, .B_ = 0.0, .C_ = 1300.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "RO2_N"), SpeciesByName(gas_phase, "C_O2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MEOH"), 0.25 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MEK"), 0.5 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "PROD2"), 0.5 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 0.75 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 2e-13, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "RO2_N"), SpeciesByName(gas_phase, "NO3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "NO2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MEK"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 2.3e-12, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "RO2_N"), SpeciesByName(gas_phase, "RO2_R") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MEK"), 0.5 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "PROD2"), 0.5 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 3.5e-14, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "RO2_N"), SpeciesByName(gas_phase, "R2O2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_N"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 3.5e-14, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "RO2_N") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "MEK"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "PROD2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 3.5e-14, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "CCO_O2"), SpeciesByName(gas_phase, "NO2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "PAN"), 1.0 } })
    .SetRateConstant(micm::TroeRateConstantParameters{ .k0_A_ = 2.7e-28, .k0_B_ = 0.0, .k0_C_ = 7.1, .kinf_A_ = 1.2e-11, .kinf_B_ = 0.0, .kinf_C_ = 0.9, .Fc_ = 0.3, .N_ = 1.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "PAN") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "CCO_O2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "NO2"), 1.0 } })
    .SetRateConstant(micm::TroeRateConstantParameters{ .k0_A_ = 0.0049, .k0_B_ = 12100.0, .k0_C_ = 0.0, .kinf_A_ = 4e+16, .kinf_B_ = 13600.0, .kinf_C_ = 0.0, .Fc_ = 0.3, .N_ = 1.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "CCO_O2"), SpeciesByName(gas_phase, "NO") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "C_O2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "NO2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 7.8e-12, .B_ = 0.0, .C_ = 300.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "CCO_O2"), SpeciesByName(gas_phase, "HO2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "CCO_OOH"), 0.75 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCO_OH"), 0.25 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "O3"), 0.25 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 4.3e-13, .B_ = 0.0, .C_ = 1040.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "CCO_O2"), SpeciesByName(gas_phase, "NO3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "C_O2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "NO2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 4e-12, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "CCO_O2"), SpeciesByName(gas_phase, "C_O2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "CCO_OH"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.8e-12, .B_ = 0.0, .C_ = 500.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "CCO_O2"), SpeciesByName(gas_phase, "RO2_R") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "CCO_OH"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 7.5e-12, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "CCO_O2"), SpeciesByName(gas_phase, "R2O2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "CCO_O2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 7.5e-12, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "CCO_O2"), SpeciesByName(gas_phase, "RO2_N") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "CCO_OH"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "PROD2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 7.5e-12, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "CCO_O2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "C_O2"), 2.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 2.9e-12, .B_ = 0.0, .C_ = 500.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "RCO_O2"), SpeciesByName(gas_phase, "NO2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "PAN2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.2e-11, .B_ = -0.9, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "PAN2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RCO_O2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "NO2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 2000000000000000.0, .B_ = 0.0, .C_ = -12800.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "RCO_O2"), SpeciesByName(gas_phase, "NO") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "NO2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCHO"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.25e-11, .B_ = 0.0, .C_ = 240.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "RCO_O2"), SpeciesByName(gas_phase, "HO2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RCO_OOH"), 0.75 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCO_OH"), 0.25 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "O3"), 0.25 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 4.3e-13, .B_ = 0.0, .C_ = 1040.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "RCO_O2"), SpeciesByName(gas_phase, "NO3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "NO2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCHO"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 4e-12, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "RCO_O2"), SpeciesByName(gas_phase, "C_O2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RCO_OH"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.8e-12, .B_ = 0.0, .C_ = 500.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "RCO_O2"), SpeciesByName(gas_phase, "RO2_R") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RCO_OH"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 7.5e-12, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "RCO_O2"), SpeciesByName(gas_phase, "R2O2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RCO_O2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 7.5e-12, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "RCO_O2"), SpeciesByName(gas_phase, "RO2_N") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RCO_OH"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "PROD2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 7.5e-12, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "RCO_O2"), SpeciesByName(gas_phase, "CCO_O2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "C_O2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCHO"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 2.9e-12, .B_ = 0.0, .C_ = 500.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "RCO_O2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "CCHO"), 2.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 2.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 2.9e-12, .B_ = 0.0, .C_ = 500.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "BZCO_O2"), SpeciesByName(gas_phase, "NO2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "PBZN"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.37e-11, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "PBZN") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "BZCO_O2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "NO2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 7.9e+16, .B_ = 0.0, .C_ = -14000.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "BZCO_O2"), SpeciesByName(gas_phase, "NO") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "NO2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "BZ_O"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "R2O2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.25e-11, .B_ = 0.0, .C_ = 240.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "BZCO_O2"), SpeciesByName(gas_phase, "HO2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RCO_OOH"), 0.75 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCO_OH"), 0.25 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "O3"), 0.25 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 4.3e-13, .B_ = 0.0, .C_ = 1040.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "BZCO_O2"), SpeciesByName(gas_phase, "NO3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "NO2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "BZ_O"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "R2O2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 4e-12, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "BZCO_O2"), SpeciesByName(gas_phase, "C_O2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RCO_OH"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.8e-12, .B_ = 0.0, .C_ = 500.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "BZCO_O2"), SpeciesByName(gas_phase, "RO2_R") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RCO_OH"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 7.5e-12, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "BZCO_O2"), SpeciesByName(gas_phase, "R2O2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "BZCO_O2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 7.5e-12, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "BZCO_O2"), SpeciesByName(gas_phase, "RO2_N") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RCO_OH"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "PROD2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 7.5e-12, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "BZCO_O2"), SpeciesByName(gas_phase, "CCO_O2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "C_O2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "BZ_O"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "R2O2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 2.9e-12, .B_ = 0.0, .C_ = 500.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "BZCO_O2"), SpeciesByName(gas_phase, "RCO_O2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "CCHO"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "BZ_O"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "R2O2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 2.9e-12, .B_ = 0.0, .C_ = 500.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "BZCO_O2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "BZ_O"), 2.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "R2O2"), 2.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 2.9e-12, .B_ = 0.0, .C_ = 500.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "MA_RCO3"), SpeciesByName(gas_phase, "NO2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "MA_PAN"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.2e-11, .B_ = -0.9, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "MA_PAN") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "MA_RCO3"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "NO2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.6e+16, .B_ = 0.0, .C_ = -13486.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "MA_RCO3"), SpeciesByName(gas_phase, "NO") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "NO2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCO_O2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.25e-11, .B_ = 0.0, .C_ = 240.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "MA_RCO3"), SpeciesByName(gas_phase, "HO2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RCO_OOH"), 0.75 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCO_OH"), 0.25 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "O3"), 0.25 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 4.3e-13, .B_ = 0.0, .C_ = 1040.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "MA_RCO3"), SpeciesByName(gas_phase, "NO3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "NO2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCO_O2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 4e-12, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "MA_RCO3"), SpeciesByName(gas_phase, "C_O2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RCO_OH"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.8e-12, .B_ = 0.0, .C_ = 500.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "MA_RCO3"), SpeciesByName(gas_phase, "RO2_R") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RCO_OH"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 7.5e-12, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "MA_RCO3"), SpeciesByName(gas_phase, "R2O2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "MA_RCO3"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 7.5e-12, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "MA_RCO3"), SpeciesByName(gas_phase, "RO2_N") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RCO_OH"), 2.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 7.5e-12, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "MA_RCO3"), SpeciesByName(gas_phase, "CCO_O2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "C_O2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCO_O2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 2.9e-12, .B_ = 0.0, .C_ = 500.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "MA_RCO3"), SpeciesByName(gas_phase, "RCO_O2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCO_O2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCHO"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 2.9e-12, .B_ = 0.0, .C_ = 500.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "MA_RCO3"), SpeciesByName(gas_phase, "BZCO_O2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCO_O2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "BZ_O"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "R2O2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 2.9e-12, .B_ = 0.0, .C_ = 500.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "MA_RCO3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 2.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCO_O2"), 2.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 2.9e-12, .B_ = 0.0, .C_ = 500.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "TBU_O"), SpeciesByName(gas_phase, "NO2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RNO3"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 2.4e-11, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "TBU_O") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "ACET"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "C_O2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 750000000000000.0, .B_ = 0.0, .C_ = -8152.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "BZ_O"), SpeciesByName(gas_phase, "NO2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "NPHE"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 2.3e-11, .B_ = 0.0, .C_ = 150.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "BZ_O"), SpeciesByName(gas_phase, "HO2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "PHEN"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.9e-13, .B_ = 0.0, .C_ = 1300.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "BZ_O") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "PHEN"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 0.001, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "BZNO2_O"), SpeciesByName(gas_phase, "NO2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "XN"), 2.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "XC"), 6.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 750000000000000.0, .B_ = 0.0, .C_ = -8152.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "BZNO2_O"), SpeciesByName(gas_phase, "HO2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "NPHE"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 2.3e-11, .B_ = 0.0, .C_ = 150.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "BZNO2_O") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "NPHE"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.9e-13, .B_ = 0.0, .C_ = 1300.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "HCHO") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 2.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CO"), 1.0 } })
    .SetRateConstant(micm::UserDefinedRateConstantParameters{ .label_ = "j_saprc99.yaml_0122" })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "HCHO") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "CO"), 1.0 } })
    .SetRateConstant(micm::UserDefinedRateConstantParameters{ .label_ = "j_saprc99.yaml_0123" })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "HCHO"), SpeciesByName(gas_phase, "OH") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CO"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 8.6e-12, .B_ = 0.0, .C_ = 20.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "HCHO"), SpeciesByName(gas_phase, "HO2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HOCOO"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 9.7e-15, .B_ = 0.0, .C_ = 625.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "HOCOO") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 2400000000000.0, .B_ = 0.0, .C_ = -7000.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "HOCOO"), SpeciesByName(gas_phase, "NO") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HCOOH"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "NO2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 2.8e-12, .B_ = 0.0, .C_ = 285.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "HCHO"), SpeciesByName(gas_phase, "NO3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HNO3"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CO"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 2e-12, .B_ = 0.0, .C_ = -2431.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "CCHO"), SpeciesByName(gas_phase, "OH") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "CCO_O2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 5.6e-12, .B_ = 0.0, .C_ = 310.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "CCHO") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "CO"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "C_O2"), 1.0 } })
    .SetRateConstant(micm::UserDefinedRateConstantParameters{ .label_ = "j_saprc99.yaml_0130" })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "CCHO"), SpeciesByName(gas_phase, "NO3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HNO3"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCO_O2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.4e-12, .B_ = 0.0, .C_ = -1860.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "RCHO"), SpeciesByName(gas_phase, "OH") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 0.034 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_N"), 0.001 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCO_O2"), 0.965 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CO"), 0.034 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCHO"), 0.034 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 2e-11, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "RCHO") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "CCHO"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CO"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 1.0 } })
    .SetRateConstant(micm::UserDefinedRateConstantParameters{ .label_ = "j_saprc99.yaml_0133" })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "RCHO"), SpeciesByName(gas_phase, "NO3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HNO3"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCO_O2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.4e-12, .B_ = 0.0, .C_ = -1771.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "ACET"), SpeciesByName(gas_phase, "OH") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCO_O2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "R2O2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.1e-12, .B_ = 0.0, .C_ = -520.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "ACET") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "CCO_O2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "C_O2"), 1.0 } })
    .SetRateConstant(micm::UserDefinedRateConstantParameters{ .label_ = "j_saprc99.yaml_0136" })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "MEK"), SpeciesByName(gas_phase, "OH") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 0.37 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_N"), 0.042 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "R2O2"), 0.616 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCO_O2"), 0.492 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCO_O2"), 0.096 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 0.115 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCHO"), 0.482 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCHO"), 0.37 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.3e-12, .B_ = 2.0, .C_ = -25.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "MEK") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "CCO_O2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCHO"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 1.0 } })
    .SetRateConstant(micm::UserDefinedRateConstantParameters{ .label_ = "j_saprc99.yaml_0138" })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "MEOH"), SpeciesByName(gas_phase, "OH") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 3.1e-12, .B_ = 2.0, .C_ = -360.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "COOH"), SpeciesByName(gas_phase, "OH") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 0.35 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "OH"), 0.35 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "C_O2"), 0.65 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 2.9e-12, .B_ = 0.0, .C_ = 190.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "COOH") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "OH"), 1.0 } })
    .SetRateConstant(micm::UserDefinedRateConstantParameters{ .label_ = "j_saprc99.yaml_0141" })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "ROOH"), SpeciesByName(gas_phase, "OH") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RCHO"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 0.34 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "OH"), 0.66 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.1e-11, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "ROOH") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RCHO"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "OH"), 1.0 } })
    .SetRateConstant(micm::UserDefinedRateConstantParameters{ .label_ = "j_saprc99.yaml_0143" })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "GLY") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "CO"), 2.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 2.0 } })
    .SetRateConstant(micm::UserDefinedRateConstantParameters{ .label_ = "j_saprc99.yaml_0144" })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "GLY") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CO"), 1.0 } })
    .SetRateConstant(micm::UserDefinedRateConstantParameters{ .label_ = "j_saprc99.yaml_0145" })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "GLY"), SpeciesByName(gas_phase, "OH") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 0.63 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CO"), 1.26 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCO_O2"), 0.37 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.1e-11, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "GLY"), SpeciesByName(gas_phase, "NO3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HNO3"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 0.63 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CO"), 1.26 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCO_O2"), 0.37 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 2.8e-12, .B_ = 0.0, .C_ = -2376.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "MGLY") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CO"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCO_O2"), 1.0 } })
    .SetRateConstant(micm::UserDefinedRateConstantParameters{ .label_ = "j_saprc99.yaml_0148" })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "MGLY"), SpeciesByName(gas_phase, "OH") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "CO"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCO_O2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.5e-11, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "MGLY"), SpeciesByName(gas_phase, "NO3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HNO3"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CO"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCO_O2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.4e-12, .B_ = 0.0, .C_ = -1895.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "BACL") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "CCO_O2"), 2.0 } })
    .SetRateConstant(micm::UserDefinedRateConstantParameters{ .label_ = "j_saprc99.yaml_0151" })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "PHEN"), SpeciesByName(gas_phase, "OH") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "BZ_O"), 0.24 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 0.76 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "GLY"), 0.23 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 2.63e-11, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "PHEN"), SpeciesByName(gas_phase, "NO3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HNO3"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "BZ_O"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 3.78e-12, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "CRES"), SpeciesByName(gas_phase, "OH") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "BZ_O"), 0.24 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 0.76 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MGLY"), 0.23 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 4.2e-11, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "CRES"), SpeciesByName(gas_phase, "NO3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HNO3"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "BZ_O"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.37e-11, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "NPHE"), SpeciesByName(gas_phase, "NO3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HNO3"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "BZNO2_O"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 3.78e-12, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "BALD"), SpeciesByName(gas_phase, "OH") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "BZCO_O2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.29e-11, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "BALD") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "XC"), 7.0 } })
    .SetRateConstant(micm::UserDefinedRateConstantParameters{ .label_ = "j_saprc99.yaml_0158" })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "BALD"), SpeciesByName(gas_phase, "NO3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HNO3"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "BZCO_O2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.4e-12, .B_ = 0.0, .C_ = -1872.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "METHACRO"), SpeciesByName(gas_phase, "OH") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 0.5 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CO"), 0.416 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 0.084 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MEK"), 0.416 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MGLY"), 0.084 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MA_RCO3"), 0.5 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.86e-11, .B_ = 0.0, .C_ = 176.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "METHACRO"), SpeciesByName(gas_phase, "O3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 0.008 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 0.1 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "OH"), 0.208 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCO_O2"), 0.1 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CO"), 0.45 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 0.2 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MGLY"), 0.9 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCOOH"), 0.333 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.36e-15, .B_ = 0.0, .C_ = -2114.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "METHACRO"), SpeciesByName(gas_phase, "NO3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HNO3"), 0.5 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 0.5 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CO"), 0.5 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MA_RCO3"), 0.5 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.5e-12, .B_ = 0.0, .C_ = -1726.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "METHACRO"), SpeciesByName(gas_phase, "O3P") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RCHO"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 6.34e-12, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "METHACRO") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 0.34 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 0.33 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "OH"), 0.33 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCO_O2"), 0.67 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CO"), 0.67 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 0.67 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MA_RCO3"), 0.33 } })
    .SetRateConstant(micm::UserDefinedRateConstantParameters{ .label_ = "j_saprc99.yaml_0164" })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "MVK"), SpeciesByName(gas_phase, "OH") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 0.3 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_N"), 0.025 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "R2O2"), 0.675 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCO_O2"), 0.675 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 0.3 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCHO"), 0.675 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MGLY"), 0.3 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 4.14e-12, .B_ = 0.0, .C_ = 453.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "MVK"), SpeciesByName(gas_phase, "O3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 0.064 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 0.05 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "OH"), 0.164 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCO_O2"), 0.05 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CO"), 0.475 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 0.1 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MGLY"), 0.95 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCOOH"), 0.351 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 7.51e-16, .B_ = 0.0, .C_ = -1520.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "MVK"), SpeciesByName(gas_phase, "O3P") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RCHO"), 0.45 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MEK"), 0.55 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 4.32e-12, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "MVK") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "C_O2"), 0.3 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CO"), 0.7 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "PROD2"), 0.7 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MA_RCO3"), 0.3 } })
    .SetRateConstant(micm::UserDefinedRateConstantParameters{ .label_ = "j_saprc99.yaml_0168" })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "ISOPROD"), SpeciesByName(gas_phase, "OH") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 0.67 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_N"), 0.041 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MA_RCO3"), 0.289 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CO"), 0.336 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 0.055 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCHO"), 0.129 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCHO"), 0.013 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MEK"), 0.15 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "PROD2"), 0.332 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "GLY"), 0.15 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MGLY"), 0.174 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 6.19e-11, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "ISOPROD"), SpeciesByName(gas_phase, "O3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 0.4 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 0.048 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCO_O2"), 0.048 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "OH"), 0.285 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CO"), 0.498 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 0.125 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCHO"), 0.047 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MEK"), 0.21 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "GLY"), 0.023 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MGLY"), 0.742 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCOOH"), 0.1 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCO_OH"), 0.372 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 4.18e-18, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "ISOPROD"), SpeciesByName(gas_phase, "NO3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 0.799 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_N"), 0.051 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MA_RCO3"), 0.15 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CO"), 0.572 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HNO3"), 0.15 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 0.227 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCHO"), 0.218 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MGLY"), 0.008 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RNO3"), 0.572 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1e-13, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "ISOPROD") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 1.233 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCO_O2"), 0.467 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCO_O2"), 0.3 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CO"), 1.233 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 0.3 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCHO"), 0.467 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MEK"), 0.233 } })
    .SetRateConstant(micm::UserDefinedRateConstantParameters{ .label_ = "j_saprc99.yaml_0172" })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "PROD2"), SpeciesByName(gas_phase, "OH") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 0.379 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 0.473 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_N"), 0.07 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCO_O2"), 0.029 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCO_O2"), 0.049 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 0.213 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCHO"), 0.084 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCHO"), 0.558 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MEK"), 0.115 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "PROD2"), 0.329 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.5e-11, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "PROD2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 0.96 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_N"), 0.04 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "R2O2"), 0.515 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCO_O2"), 0.667 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCO_O2"), 0.333 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 0.506 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCHO"), 0.246 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCHO"), 0.71 } })
    .SetRateConstant(micm::UserDefinedRateConstantParameters{ .label_ = "j_saprc99.yaml_0174" })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "RNO3"), SpeciesByName(gas_phase, "OH") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "NO2"), 0.338 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 0.113 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 0.376 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_N"), 0.173 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "R2O2"), 0.596 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 0.01 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCHO"), 0.439 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCHO"), 0.213 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "ACET"), 0.006 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MEK"), 0.177 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "PROD2"), 0.048 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RNO3"), 0.31 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 7.8e-12, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "RNO3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "NO2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 0.341 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 0.564 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_N"), 0.095 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "R2O2"), 0.152 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 0.134 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCHO"), 0.431 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCHO"), 0.147 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "ACET"), 0.02 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MEK"), 0.243 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "PROD2"), 0.435 } })
    .SetRateConstant(micm::UserDefinedRateConstantParameters{ .label_ = "j_saprc99.yaml_0176" })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "DCB1"), SpeciesByName(gas_phase, "OH") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RCHO"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CO"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 5e-11, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "DCB1"), SpeciesByName(gas_phase, "O3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 1.5 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "OH"), 0.5 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CO"), 1.5 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "GLY"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 2e-18, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "DCB2"), SpeciesByName(gas_phase, "OH") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "R2O2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCHO"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCO_O2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 5e-11, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "DCB2") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCO_O2"), 0.5 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 0.5 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CO"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "R2O2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "GLY"), 0.5 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MGLY"), 0.5 } })
    .SetRateConstant(micm::UserDefinedRateConstantParameters{ .label_ = "j_saprc99.yaml_0180" })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "DCB3"), SpeciesByName(gas_phase, "OH") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "R2O2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCHO"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCO_O2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 5e-11, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "DCB3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCO_O2"), 0.5 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 0.5 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CO"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "R2O2"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "GLY"), 0.5 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MGLY"), 0.5 } })
    .SetRateConstant(micm::UserDefinedRateConstantParameters{ .label_ = "j_saprc99.yaml_0182" })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "CH4"), SpeciesByName(gas_phase, "OH") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "C_O2"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 2.15e-12, .B_ = 0.0, .C_ = -1735.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "ETHENE"), SpeciesByName(gas_phase, "OH") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 1.61 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCHO"), 0.195 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.96e-12, .B_ = 0.0, .C_ = 438.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "ETHENE"), SpeciesByName(gas_phase, "O3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "OH"), 0.12 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 0.12 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CO"), 0.5 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCOOH"), 0.37 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 9.14e-15, .B_ = 0.0, .C_ = -2580.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "ETHENE"), SpeciesByName(gas_phase, "NO3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCHO"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 4.39e-13, .B_ = 2.0, .C_ = -2282.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "ETHENE"), SpeciesByName(gas_phase, "O3P") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 0.5 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 0.2 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "C_O2"), 0.3 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CO"), 0.491 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 0.191 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCHO"), 0.25 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "GLY"), 0.009 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.04e-11, .B_ = 0.0, .C_ = -792.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "ISOPRENE"), SpeciesByName(gas_phase, "OH") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 0.907 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_N"), 0.093 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "R2O2"), 0.079 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 0.624 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "METHACRO"), 0.23 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MVK"), 0.32 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "ISOPROD"), 0.357 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 2.5e-11, .B_ = 0.0, .C_ = 408.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "ISOPRENE"), SpeciesByName(gas_phase, "O3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "OH"), 0.266 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 0.066 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_N"), 0.008 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "R2O2"), 0.126 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MA_RCO3"), 0.192 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CO"), 0.275 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 0.592 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "PROD2"), 0.1 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "METHACRO"), 0.39 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MVK"), 0.16 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCOOH"), 0.204 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCO_OH"), 0.15 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 7.86e-15, .B_ = 0.0, .C_ = -1912.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "ISOPRENE"), SpeciesByName(gas_phase, "NO3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "NO2"), 0.187 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 0.749 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_N"), 0.064 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "R2O2"), 0.187 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "ISOPROD"), 0.936 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 3.03e-12, .B_ = 0.0, .C_ = -448.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "ISOPRENE"), SpeciesByName(gas_phase, "O3P") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_N"), 0.01 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "R2O2"), 0.24 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "C_O2"), 0.25 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MA_RCO3"), 0.24 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 0.24 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "PROD2"), 0.75 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 3.6e-11, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "TERP"), SpeciesByName(gas_phase, "OH") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 0.75 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_N"), 0.25 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "R2O2"), 0.5 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 0.276 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCHO"), 0.474 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "PROD2"), 0.276 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.83e-11, .B_ = 0.0, .C_ = 449.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "TERP"), SpeciesByName(gas_phase, "O3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "OH"), 0.567 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 0.033 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 0.031 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_N"), 0.18 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "R2O2"), 0.729 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCO_O2"), 0.123 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCO_O2"), 0.201 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CO"), 0.157 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 0.235 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCHO"), 0.205 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "ACET"), 0.13 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "PROD2"), 0.276 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "GLY"), 0.001 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "BACL"), 0.031 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCOOH"), 0.103 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCO_OH"), 0.189 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.08e-15, .B_ = 0.0, .C_ = -821.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "TERP"), SpeciesByName(gas_phase, "NO3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "NO2"), 0.474 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 0.276 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_N"), 0.25 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "R2O2"), 0.75 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCHO"), 0.474 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RNO3"), 0.276 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 3.66e-12, .B_ = 0.0, .C_ = 175.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "TERP"), SpeciesByName(gas_phase, "O3P") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RCHO"), 0.147 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "PROD2"), 0.853 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 3.27e-11, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "ALK1"), SpeciesByName(gas_phase, "OH") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 1.0 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCHO"), 1.0 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.37e-12, .B_ = 2.0, .C_ = -498.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "ALK2"), SpeciesByName(gas_phase, "OH") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "OH"), 0.246 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 0.121 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 0.612 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_N"), 0.021 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CO"), 0.16 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 0.039 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCHO"), 0.155 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "ACET"), 0.417 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "GLY"), 0.248 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCOOH"), 0.121 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 9.87e-12, .B_ = 0.0, .C_ = -671.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "ALK3"), SpeciesByName(gas_phase, "OH") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 0.695 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_N"), 0.07 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "R2O2"), 0.559 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "TBU_O"), 0.236 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 0.026 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCHO"), 0.445 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCHO"), 0.122 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "ACET"), 0.024 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MEK"), 0.332 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.019e-11, .B_ = 0.0, .C_ = -434.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "ALK4"), SpeciesByName(gas_phase, "OH") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 0.835 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_N"), 0.143 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "R2O2"), 0.936 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "C_O2"), 0.011 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCO_O2"), 0.011 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CO"), 0.002 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 0.024 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCHO"), 0.455 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCHO"), 0.244 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "ACET"), 0.452 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MEK"), 0.11 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "PROD2"), 0.125 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 5.946e-12, .B_ = 0.0, .C_ = -91.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "ALK5"), SpeciesByName(gas_phase, "OH") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 0.653 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_N"), 0.347 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "R2O2"), 0.948 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 0.026 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCHO"), 0.099 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCHO"), 0.204 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "ACET"), 0.072 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MEK"), 0.089 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "PROD2"), 0.417 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.112e-11, .B_ = 0.0, .C_ = -52.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "ARO1"), SpeciesByName(gas_phase, "OH") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 0.224 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 0.765 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_N"), 0.011 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "PROD2"), 0.055 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "GLY"), 0.118 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MGLY"), 0.119 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "PHEN"), 0.017 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CRES"), 0.207 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "BALD"), 0.059 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "DCB1"), 0.491 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "DCB2"), 0.108 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "DCB3"), 0.051 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.81e-12, .B_ = 0.0, .C_ = 355.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "ARO2"), SpeciesByName(gas_phase, "OH") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 0.187 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 0.804 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_N"), 0.009 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "GLY"), 0.097 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MGLY"), 0.287 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "BACL"), 0.087 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CRES"), 0.187 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "BALD"), 0.05 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "DCB1"), 0.561 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "DCB2"), 0.099 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "DCB3"), 0.093 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 2.64e-11, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "OLE1"), SpeciesByName(gas_phase, "OH") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 0.91 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_N"), 0.09 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "R2O2"), 0.205 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 0.732 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCHO"), 0.294 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCHO"), 0.497 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "ACET"), 0.005 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "PROD2"), 0.119 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 7.095e-12, .B_ = 0.0, .C_ = 451.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "OLE1"), SpeciesByName(gas_phase, "O3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "OH"), 0.155 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 0.056 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 0.022 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_N"), 0.001 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "C_O2"), 0.076 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CO"), 0.345 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 0.5 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCHO"), 0.154 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCHO"), 0.363 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "ACET"), 0.001 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "PROD2"), 0.215 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCOOH"), 0.185 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCO_OH"), 0.05 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCO_OH"), 0.119 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 2.617e-15, .B_ = 0.0, .C_ = -1640.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "OLE1"), SpeciesByName(gas_phase, "NO3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 0.824 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_N"), 0.176 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "R2O2"), 0.488 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCHO"), 0.009 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCHO"), 0.037 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "ACET"), 0.024 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RNO3"), 0.511 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 4.453e-14, .B_ = 0.0, .C_ = -376.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "OLE1"), SpeciesByName(gas_phase, "O3P") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RCHO"), 0.45 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MEK"), 0.437 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "PROD2"), 0.113 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.074e-11, .B_ = 0.0, .C_ = -234.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "OLE2"), SpeciesByName(gas_phase, "OH") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 0.918 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_N"), 0.082 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "R2O2"), 0.001 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 0.244 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCHO"), 0.732 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCHO"), 0.511 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "ACET"), 0.127 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MEK"), 0.072 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "BALD"), 0.061 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "METHACRO"), 0.025 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "ISOPROD"), 0.025 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 1.743e-11, .B_ = 0.0, .C_ = 384.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "OLE2"), SpeciesByName(gas_phase, "O3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "OH"), 0.378 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 0.003 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 0.033 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_N"), 0.002 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "R2O2"), 0.137 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "C_O2"), 0.197 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCO_O2"), 0.137 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCO_O2"), 0.006 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CO"), 0.265 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 0.269 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCHO"), 0.456 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCHO"), 0.305 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "ACET"), 0.045 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MEK"), 0.026 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "PROD2"), 0.043 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "BALD"), 0.042 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "METHACRO"), 0.026 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MVK"), 0.019 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCOOH"), 0.073 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCO_OH"), 0.129 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCO_OH"), 0.247 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 5.022e-16, .B_ = 0.0, .C_ = -461.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "OLE2"), SpeciesByName(gas_phase, "NO3") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "NO2"), 0.391 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 0.442 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_N"), 0.136 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "R2O2"), 0.711 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "C_O2"), 0.03 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "HCHO"), 0.079 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CCHO"), 0.507 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCHO"), 0.151 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "ACET"), 0.102 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MEK"), 0.001 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "BALD"), 0.015 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MVK"), 0.048 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RNO3"), 0.321 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 7.265e-13, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  processes.push_back(micm::ChemicalReactionBuilder()
    .SetReactants({ SpeciesByName(gas_phase, "OLE2"), SpeciesByName(gas_phase, "O3P") })
    .SetProducts({ micm::StoichSpecies{ SpeciesByName(gas_phase, "HO2"), 0.013 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_R"), 0.012 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RO2_N"), 0.001 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "CO"), 0.012 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "RCHO"), 0.069 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "MEK"), 0.659 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "PROD2"), 0.259 }, micm::StoichSpecies{ SpeciesByName(gas_phase, "METHACRO"), 0.012 } })
    .SetRateConstant(micm::ArrheniusRateConstantParameters{ .A_ = 2.085e-11, .B_ = 0.0, .C_ = 0.0, .D_ = 300.0, .E_ = 0.0 })
.SetPhase(gas_phase).Build());
  return processes;
}

}  // namespace bench::saprc99
