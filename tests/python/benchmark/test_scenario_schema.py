"""Contract tests for canonical solver-comparison scenarios."""

from __future__ import annotations

import math
from copy import deepcopy

import pytest
from mkpp.benchmark.scenario import forcing_segments, validate_scenario, validate_scenario_pair

SHA = "c" * 64


@pytest.fixture
def valid_scenario() -> dict:
    return {
        "schema_version": 1,
        "scenario_id": "chapman-calibration-v1",
        "version": "1.0.0",
        "mechanism": {"id": "chapman", "version": "1.0.0", "sha256": SHA},
        "role": "calibration",
        "initial_state": {
            "O": {"value": 1.0e10, "unit": "molecule cm-3"},
            "O2": {"value": 5.0e18, "unit": "molecule cm-3"},
        },
        "environment": {
            "temperature": {"value": 288.15, "unit": "K"},
            "pressure": {"value": 101325.0, "unit": "Pa"},
        },
        "forcing": {
            "J_O2": {
                "unit": "s-1",
                "points": [
                    {"time_seconds": 0.0, "value": 1.0e-12},
                    {"time_seconds": 600.0, "value": 2.0e-12},
                ],
            }
        },
        "integration": {
            "start_seconds": 0.0,
            "horizon_seconds": 600.0,
            "checkpoints_seconds": [60.0, 300.0, 600.0],
            "forcing_boundaries_seconds": [0.0, 600.0],
        },
        "workload": {"cells": [1, 10], "ensemble_seed": 1701},
        "accuracy": {
            "rtol": 1.0e-6,
            "atol_by_species": {"O": 1.0e2, "O2": 1.0e8},
            "positivity_policy": "nonnegative_with_scaled_roundoff",
            "conservation_checks": ["oxygen_atoms"],
        },
        "reference": {"implementation": "scipy-radau", "max_refinements": 3},
    }


def test_valid_scenario_is_accepted(valid_scenario: dict) -> None:
    validate_scenario(valid_scenario)


@pytest.mark.parametrize("value", [math.nan, math.inf, -math.inf])
def test_scenario_rejects_non_finite_values(valid_scenario: dict, value: float) -> None:
    scenario = deepcopy(valid_scenario)
    scenario["initial_state"]["O"]["value"] = value
    with pytest.raises(ValueError, match="finite|initial_state|value"):
        validate_scenario(scenario)


def test_scenario_requires_named_forcing(valid_scenario: dict) -> None:
    scenario = deepcopy(valid_scenario)
    scenario["forcing"] = [{"value": 1.0e-12}]
    with pytest.raises(ValueError, match="forcing|named|object"):
        validate_scenario(scenario)


def test_scenario_rejects_forcing_without_unit(valid_scenario: dict) -> None:
    scenario = deepcopy(valid_scenario)
    del scenario["forcing"]["J_O2"]["unit"]
    with pytest.raises(ValueError, match="forcing|unit"):
        validate_scenario(scenario)


@pytest.mark.parametrize(
    "mutate",
    [
        lambda s: s["accuracy"].update(rtol=0.0),
        lambda s: s["accuracy"].update(atol_by_species={}),
        lambda s: s["accuracy"]["atol_by_species"].update(O=-1.0),
        lambda s: s["accuracy"].pop("positivity_policy"),
        lambda s: s["accuracy"].pop("conservation_checks"),
    ],
)
def test_scenario_rejects_invalid_accuracy_budget(valid_scenario: dict, mutate) -> None:
    scenario = deepcopy(valid_scenario)
    mutate(scenario)
    with pytest.raises(ValueError, match="accuracy|rtol|atol|positivity|conservation"):
        validate_scenario(scenario)


def test_scenario_rejects_non_finite_environment(valid_scenario: dict) -> None:
    scenario = deepcopy(valid_scenario)
    scenario["environment"]["temperature"]["value"] = math.nan
    with pytest.raises(ValueError, match="finite|environment|temperature"):
        validate_scenario(scenario)


def test_calibration_and_measurement_must_have_distinct_ids_and_seeds(
    valid_scenario: dict,
) -> None:
    calibration = deepcopy(valid_scenario)
    measurement = deepcopy(valid_scenario)
    measurement["role"] = "measurement"

    with pytest.raises(ValueError, match="distinct|scenario_id|seed|overlap"):
        validate_scenario_pair(calibration, measurement)

    measurement["scenario_id"] = "chapman-measurement-v1"
    with pytest.raises(ValueError, match="distinct|seed|overlap"):
        validate_scenario_pair(calibration, measurement)

    measurement["workload"]["ensemble_seed"] = 2718
    validate_scenario_pair(calibration, measurement)


def test_scenario_rejects_unknown_fields(valid_scenario: dict) -> None:
    scenario = deepcopy(valid_scenario)
    scenario["unexpected"] = True
    with pytest.raises(ValueError, match="unexpected|additional|unknown"):
        validate_scenario(scenario)


def test_forcing_segments_materialize_one_shared_piecewise_schedule(valid_scenario: dict) -> None:
    scenario = deepcopy(valid_scenario)
    scenario["forcing"]["J_O2"]["points"] = [
        {"time_seconds": 0.0, "value": 1.0e-12},
        {"time_seconds": 300.0, "value": 2.0e-12},
        {"time_seconds": 600.0, "value": 3.0e-12},
    ]
    scenario["integration"]["forcing_boundaries_seconds"] = [0.0, 300.0, 600.0]
    segments = forcing_segments(scenario)
    assert [(segment.start_seconds, segment.end_seconds) for segment in segments] == [
        (0.0, 300.0),
        (300.0, 600.0),
    ]
    assert segments[0].values == {"J_O2": pytest.approx(1.0e-12)}
    assert segments[1].values == {"J_O2": pytest.approx(2.0e-12)}


def test_forcing_segments_reject_underspecified_boundary_value(valid_scenario: dict) -> None:
    scenario = deepcopy(valid_scenario)
    scenario["integration"]["forcing_boundaries_seconds"] = [0.0, 300.0, 600.0]
    with pytest.raises(ValueError, match="missing value"):
        forcing_segments(scenario)
