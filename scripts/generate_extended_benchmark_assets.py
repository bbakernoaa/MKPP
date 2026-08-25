#!/usr/bin/env python3
"""Generate immutable draft benchmark assets from canonical OpenAtmos JSON."""
from __future__ import annotations

import hashlib
import json
from pathlib import Path

import yaml


ROOT = Path(__file__).resolve().parents[1]


def digest(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main() -> None:
    source = ROOT / "mechanisms" / "openatmos" / "saprc99" / "mechanism.json"
    document = json.loads(source.read_text())
    species = document["species"]
    fixed = {entry["name"] for entry in species if str(entry.get("type", "")).lower() == "fixed"}
    names = [entry["name"] for entry in species]
    photolysis = [str(reaction["name"]) for reaction in document["reactions"] if str(reaction["type"]).upper() == "PHOTOLYSIS"]
    sha = digest(source)
    manifest = {
        "schema_version": 1, "mechanism_id": "saprc99", "version": "1.0.0",
        "canonical_source": [{"path": "mechanisms/openatmos/saprc99/mechanism.json", "revision": "openatmos-v1", "sha256": sha}],
        "canonical_species": [{"id": name, "role": "fixed" if name in fixed else "active", "phase": "gas", "unit": "mol m-3", "scale": 1.0} for name in names],
        "chemistry_sha256": sha,
        "photolysis_inputs": [{"id": name, "unit": "s-1"} for name in photolysis],
        "required_solvers": ["micm", "mkpp"],
        "bindings": {solver: {"revision": "workspace", "assets": ["mechanisms/openatmos/saprc99/mechanism.json"], "species_map": {name: name for name in names}, "photolysis_map": {name: name for name in photolysis}} for solver in ("micm", "mkpp")},
        "admission_status": "draft",
    }
    initial = {name: {"value": 40.0 if name in fixed else 1.0e-12, "unit": "mol m-3"} for name in names}
    forcing = {name: {"unit": "s-1", "points": [{"time_seconds": 0.0, "value": 1.0e-6}, {"time_seconds": 300.0, "value": 1.05e-6}, {"time_seconds": 600.0, "value": 1.0e-6}]} for name in photolysis}
    base = {"schema_version": 1, "version": "1.0.0", "mechanism": {"id": "saprc99", "version": "1.0.0", "sha256": sha}, "initial_state": initial, "environment": {"temperature": {"value": 298.15, "unit": "K"}, "pressure": {"value": 101325.0, "unit": "Pa"}}, "forcing": forcing, "integration": {"start_seconds": 0.0, "horizon_seconds": 600.0, "checkpoints_seconds": [300.0, 600.0], "forcing_boundaries_seconds": [0.0, 300.0, 600.0]}, "accuracy": {"rtol": 1.0e-6, "atol_by_species": {name: 1.0e-15 for name in names}, "positivity_policy": "nonnegative_with_scaled_roundoff", "conservation_checks": []}, "reference": {"implementation": "scipy-radau", "max_refinements": 3}}
    for role, cells, seed in (("calibration", [1, 10], 1701), ("measurement", [1, 10, 100], 2718)):
        scenario = dict(base, scenario_id=f"saprc99-{role}-v1", role=role, workload={"cells": cells, "ensemble_seed": seed})
        (ROOT / "benchmarks/solver_comparison/scenarios" / f"saprc99-{role}-v1.yaml").write_text(yaml.safe_dump(scenario, sort_keys=False))
    (ROOT / "benchmarks/solver_comparison/manifests/saprc99-v1.yaml").write_text(yaml.safe_dump(manifest, sort_keys=False))


if __name__ == "__main__":
    main()
