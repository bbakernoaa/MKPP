#!/usr/bin/env python3
"""Generate auditable MICM process bindings from canonical OpenAtmos JSON."""

from __future__ import annotations

import argparse
import json
from collections.abc import Mapping, Sequence
from pathlib import Path
from typing import Any


def _number(value: Any, default: float = 0.0) -> str:
    raw = default if value is None else value
    if isinstance(raw, str):
        # Some legacy KPP translations retain a harmless trailing decimal point
        # (for example ``0.0.``). Normalize syntax only; never alter its value.
        raw = raw.rstrip(".") if raw.count(".") > 1 else raw
    return repr(float(raw))


def _quoted(value: str) -> str:
    return json.dumps(value)


def _species(name: str) -> str:
    return f"SpeciesByName(gas_phase, {_quoted(name)})"


def _terms(values: Sequence[Mapping[str, Any]], products: bool) -> str:
    rendered = []
    for term in values:
        species, coefficient = str(term["species name"]), _number(term.get("coefficient", 1.0))
        rendered.append(f"micm::StoichSpecies{{ {_species(species)}, {coefficient} }}" if products else _species(species))
    return ", ".join(rendered)


def _rate(reaction: Mapping[str, Any]) -> str:
    rate_type = str(reaction["type"]).upper()
    if rate_type == "ARRHENIUS":
        return (
            "micm::ArrheniusRateConstantParameters{ "
            + ", ".join(
                f".{key}_ = {_number(reaction.get(key), default)}"
                for key, default in (("A", 1.0), ("B", 0.0), ("C", 0.0), ("D", 300.0), ("E", 0.0))
            )
            + " }"
        )
    if rate_type == "TROE":
        return (
            "micm::TroeRateConstantParameters{ "
            + ", ".join(
                f".{key}_ = {_number(reaction.get(key), default)}"
                for key, default in (
                    ("k0_A", 1.0),
                    ("k0_B", 0.0),
                    ("k0_C", 0.0),
                    ("kinf_A", 1.0),
                    ("kinf_B", 0.0),
                    ("kinf_C", 0.0),
                    ("Fc", 0.6),
                    ("N", 1.0),
                )
            )
            + " }"
        )
    if rate_type == "PHOTOLYSIS":
        return f"micm::UserDefinedRateConstantParameters{{ .label_ = {_quoted(str(reaction['name']))} }}"
    if rate_type in {"EP2", "EP3"}:
        fields = ("A0", "C0", "A2", "C2", "A3", "C3") if rate_type == "EP2" else ("A1", "C1", "A2", "C2")
        values = {field: _number(reaction.get(field)) for field in fields}
        if rate_type == "EP2":
            expression = (
                f"const auto k0 = {values['A0']} * std::exp({values['C0']} / c.temperature_); "
                f"const auto k2 = {values['A2']} * std::exp({values['C2']} / c.temperature_); "
                f"const auto k3 = {values['A3']} * std::exp({values['C3']} / c.temperature_) * c.air_density_; "
                "return k0 + k3 / (1.0 + k3 / k2);"
            )
        else:
            expression = (
                f"return {values['A1']} * std::exp({values['C1']} / c.temperature_) + "
                f"{values['A2']} * std::exp({values['C2']} / c.temperature_) * c.air_density_;"
            )
        return (
            "micm::LambdaRateConstantParameters{ .label_ = "
            f"{_quoted('openatmos_' + rate_type.lower())}, .lambda_function_ = [](const micm::Conditions& c) {{ {expression} }} }}"
        )
    raise ValueError(f"unsupported OpenAtmos rate law {rate_type}")


def render(document: Mapping[str, Any], namespace: str) -> str:
    """Render a header whose process definitions are a direct OpenAtmos projection."""

    lines = [
        "// Generated from canonical OpenAtmos JSON. Do not edit.",
        "#pragma once",
        "",
        "#include <micm/CPU.hpp>",
        "#include <cmath>",
        "#include <stdexcept>",
        "#include <string>",
        "#include <string_view>",
        "#include <vector>",
        "",
        f"namespace bench::{namespace} {{",
        "",
        "inline const micm::PhaseSpecies& PhaseSpeciesByName(const micm::Phase& phase, std::string_view name) {",
        "  for (const auto& value : phase.phase_species_) if (value.species_.name_ == name) return value;",
        '  throw std::runtime_error("OpenAtmos binding species lookup failed: " + std::string(name));',
        "}",
        "inline const micm::Species& SpeciesByName(const micm::Phase& phase, std::string_view name) {",
        "  return PhaseSpeciesByName(phase, name).species_;",
        "}",
        "",
        "inline micm::Phase CreateGasPhase() {",
        "  std::vector<micm::PhaseSpecies> species;",
    ]
    for entry in document["species"]:
        name = str(entry["name"])
        lines.append(f"  {{ auto value = micm::Species({_quoted(name)});")
        if name in {"M", "AIR"}:
            lines.append("    value.SetThirdBody();")
        lines.append("    species.emplace_back(value); }")
    lines += [
        '  return micm::Phase{"gas", species};',
        "}",
        "",
        "inline std::vector<micm::Process> CreateProcesses(const micm::Phase& gas_phase) {",
        "  std::vector<micm::Process> processes;",
        f"  processes.reserve({len(document['reactions'])});",
    ]
    for reaction in document["reactions"]:
        lines += [
            "  processes.push_back(micm::ChemicalReactionBuilder()",
            f"    .SetReactants({{ {_terms(reaction['reactants'], False)} }})",
            f"    .SetProducts({{ {_terms(reaction['products'], True)} }})",
            f"    .SetRateConstant({_rate(reaction)})",
            ".SetPhase(gas_phase).Build());",
        ]
    lines += ["  return processes;", "}", "", f"}}  // namespace bench::{namespace}", ""]
    return "\n".join(lines)


def main(argv: Sequence[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("source", type=Path)
    parser.add_argument("--namespace", required=True)
    parser.add_argument("--output", required=True, type=Path)
    args = parser.parse_args(argv)
    document = json.loads(args.source.read_text(encoding="utf-8"))
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(render(document, args.namespace), encoding="utf-8")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
