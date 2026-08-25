"""RED scenario contracts for nontrivial, held-out TS1 campaigns."""

from __future__ import annotations

from copy import deepcopy

import pytest
from mkpp.benchmark.scenario import validate_scenario, validate_scenario_pair

SHA = "c" * 64


@pytest.fixture
def ts1_calibration() -> dict:
    initial_state = {f"S{i:03d}": {"value": 1.0e6 + i, "unit": "molecule cm-3"} for i in range(210)}
    initial_state["S004"]["value"] = 5.1e18
    initial_state["S010"]["value"] = 1.9e19
    atols = {name: 1.0 for name in initial_state}
    return {
        "schema_version": 1,
        "scenario_id": "ts1-calibration-v1",
        "version": "1.0.0",
        "mechanism": {"id": "ts1", "version": "1.0.0", "sha256": SHA},
        "role": "calibration",
        "initial_state": initial_state,
        "environment": {
            "temperature": {"value": 288.15, "unit": "K"},
            "pressure": {"value": 101325.0, "unit": "Pa"},
        },
        "forcing": {
            "jno2": {
                "unit": "s-1",
                "points": [
                    {"time_seconds": 0.0, "value": 1.0e-3},
                    {"time_seconds": 300.0, "value": 2.0e-3},
                    {"time_seconds": 600.0, "value": 1.0e-3},
                ],
            },
            "jo3_a": {"unit": "s-1", "constant": 1.0e-5},
            "jo3_b": {"unit": "s-1", "constant": 2.0e-5},
        },
        "integration": {
            "start_seconds": 0.0,
            "horizon_seconds": 600.0,
            "checkpoints_seconds": [60.0, 300.0, 600.0],
            "forcing_boundaries_seconds": [0.0, 300.0, 600.0],
        },
        "workload": {"cells": [1, 10, 100], "ensemble_seed": 1701},
        "accuracy": {
            "rtol": 1.0e-6,
            "atol_by_species": atols,
            "positivity_policy": "nonnegative_with_scaled_roundoff",
            "conservation_checks": [],
        },
        "reference": {"implementation": "scipy-radau", "max_refinements": 3},
    }


def test_nontrivial_ts1_scenario_is_valid_and_complete(ts1_calibration: dict) -> None:
    validate_scenario(ts1_calibration)

    state = ts1_calibration["initial_state"]
    chemically_active = [entry for name, entry in state.items() if name not in {"S004", "S010"}]
    assert len(state) == 210
    assert sum(entry["value"] > 0 for entry in chemically_active) >= 8
    assert set(ts1_calibration["forcing"]) == {"jno2", "jo3_a", "jo3_b"}


def test_ts1_rejects_background_only_initial_state(ts1_calibration: dict) -> None:
    scenario = deepcopy(ts1_calibration)
    for species, quantity in scenario["initial_state"].items():
        if species not in {"S004", "S010"}:
            quantity["value"] = 0.0

    with pytest.raises(ValueError, match="TS1|ts1|nontrivial|active"):
        validate_scenario(scenario)


def test_ts1_requires_all_named_photolysis_forcing(ts1_calibration: dict) -> None:
    scenario = deepcopy(ts1_calibration)
    del scenario["forcing"]["jo3_b"]

    with pytest.raises(ValueError, match="forcing|jo3_b|photolysis"):
        validate_scenario(scenario)


def test_every_forcing_boundary_is_a_checkpoint(ts1_calibration: dict) -> None:
    scenario = deepcopy(ts1_calibration)
    scenario["integration"]["checkpoints_seconds"].remove(300.0)

    with pytest.raises(ValueError, match="checkpoint|forcing|boundary|300"):
        validate_scenario(scenario)


def test_ts1_calibration_and_measurement_are_held_out(ts1_calibration: dict) -> None:
    measurement = deepcopy(ts1_calibration)
    measurement["scenario_id"] = "ts1-measurement-v1"
    measurement["role"] = "measurement"
    measurement["workload"]["ensemble_seed"] = 2718

    validate_scenario_pair(ts1_calibration, measurement)


@pytest.mark.parametrize("overlap", ["scenario_id", "ensemble_seed"])
def test_ts1_rejects_calibration_measurement_overlap(ts1_calibration: dict, overlap: str) -> None:
    measurement = deepcopy(ts1_calibration)
    measurement["scenario_id"] = "ts1-measurement-v1"
    measurement["role"] = "measurement"
    measurement["workload"]["ensemble_seed"] = 2718
    if overlap == "scenario_id":
        measurement["scenario_id"] = ts1_calibration["scenario_id"]
    else:
        measurement["workload"]["ensemble_seed"] = ts1_calibration["workload"]["ensemble_seed"]

    with pytest.raises(ValueError, match="distinct|scenario_id|seed|overlap"):
        validate_scenario_pair(ts1_calibration, measurement)


def test_ts1_calibration_and_measurement_forcing_identity_must_match(
    ts1_calibration: dict,
) -> None:
    measurement = deepcopy(ts1_calibration)
    measurement["scenario_id"] = "ts1-measurement-v1"
    measurement["role"] = "measurement"
    measurement["workload"]["ensemble_seed"] = 2718
    measurement["forcing"]["jno2"]["points"][1]["value"] = 9.0e-3

    with pytest.raises(ValueError, match="forcing|identical|identity"):
        validate_scenario_pair(ts1_calibration, measurement)
