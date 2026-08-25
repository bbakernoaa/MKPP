"""Semantic validation for immutable benchmark scenarios."""

from __future__ import annotations

import math
from collections.abc import Mapping, Sequence
from dataclasses import dataclass
from typing import Any

from mkpp.benchmark.schema import SchemaValidationError
from mkpp.benchmark.schema import validate_scenario as validate_scenario_schema


@dataclass(frozen=True, slots=True)
class ForcingSegment:
    """One left-closed, right-open constant-forcing integration interval.

    The scenario contract represents a discontinuous forcing schedule: a point
    at a forcing boundary supplies the value for the following interval.  This
    compact representation is the only form native benchmark runners receive,
    preventing per-runner YAML parsing or mechanism-specific defaults.
    """

    start_seconds: float
    end_seconds: float
    values: Mapping[str, float]


def _require_text(value: Any, location: str) -> str:
    if not isinstance(value, str) or not value.strip():
        raise SchemaValidationError(f"{location}: value must be a non-empty string")
    return value


def _require_finite_number(value: Any, location: str) -> float:
    if isinstance(value, bool) or not isinstance(value, int | float) or not math.isfinite(value):
        raise SchemaValidationError(f"{location}: value must be a finite number")
    return float(value)


def _validate_quantity(quantity: Any, location: str) -> None:
    if not isinstance(quantity, Mapping):
        raise SchemaValidationError(f"{location}: quantity must be an object with value and unit")
    if set(quantity) != {"value", "unit"}:
        raise SchemaValidationError(f"{location}: quantity must contain exactly value and unit")
    _require_finite_number(quantity["value"], f"{location}.value")
    _require_text(quantity["unit"], f"{location}.unit")


def _validate_named_quantities(values: Any, location: str) -> None:
    if not isinstance(values, Mapping) or not values:
        raise SchemaValidationError(f"{location}: values must be a non-empty named object")
    for name, quantity in values.items():
        _require_text(name, f"{location}.name")
        _validate_quantity(quantity, f"{location}.{name}")


def _validate_forcing(forcing: Any, start: float, end: float) -> None:
    if not isinstance(forcing, Mapping):
        raise SchemaValidationError("forcing: forcing inputs must be a named object")
    for forcing_id, definition in forcing.items():
        location = f"forcing.{forcing_id}"
        _require_text(forcing_id, "forcing.name")
        if not isinstance(definition, Mapping):
            raise SchemaValidationError(f"{location}: forcing definition must be an object")
        _require_text(definition.get("unit"), f"{location}.unit")
        has_constant = "constant" in definition
        has_points = "points" in definition
        if has_constant == has_points:
            raise SchemaValidationError(f"{location}: define exactly one of constant or points")
        if has_constant:
            _require_finite_number(definition["constant"], f"{location}.constant")
            continue

        points = definition["points"]
        if not isinstance(points, Sequence) or isinstance(points, str | bytes) or not points:
            raise SchemaValidationError(f"{location}.points: must be a non-empty sequence")
        times: list[float] = []
        for index, point in enumerate(points):
            point_location = f"{location}.points.{index}"
            if not isinstance(point, Mapping) or set(point) != {"time_seconds", "value"}:
                raise SchemaValidationError(f"{point_location}: point must contain time_seconds and value")
            time = _require_finite_number(point["time_seconds"], f"{point_location}.time_seconds")
            _require_finite_number(point["value"], f"{point_location}.value")
            if time < start or time > end:
                raise SchemaValidationError(f"{point_location}.time_seconds: outside integration interval")
            times.append(time)
        if times != sorted(set(times)):
            raise SchemaValidationError(f"{location}.points: times must be strictly increasing and unique")


def forcing_segments(document: Mapping[str, Any]) -> tuple[ForcingSegment, ...]:
    """Materialize the canonical piecewise-constant forcing schedule.

    This deliberately operates on validated OpenAtmos/MICM-format scenario
    data. Constants are copied to every segment; point values apply from their
    declared time up to the next forcing boundary.  A scenario that omits a
    forcing value at a required boundary is rejected rather than silently
    interpolated differently by each solver.
    """

    scenario = validate_scenario(document)
    integration = scenario["integration"]
    start = float(integration["start_seconds"])
    end = start + float(integration["horizon_seconds"])
    boundaries = tuple(sorted(set((start, *integration["forcing_boundaries_seconds"], end))))
    if boundaries[0] != start or boundaries[-1] != end:
        raise SchemaValidationError("forcing boundaries must include integration start and end")

    values_by_name: dict[str, dict[float, float]] = {}
    constants: dict[str, float] = {}
    for name, definition in scenario["forcing"].items():
        if "constant" in definition:
            constants[name] = float(definition["constant"])
        else:
            values_by_name[name] = {
                float(point["time_seconds"]): float(point["value"])
                for point in definition["points"]
            }

    segments: list[ForcingSegment] = []
    for segment_start, segment_end in zip(boundaries[:-1], boundaries[1:], strict=True):
        values = dict(constants)
        for name, points in values_by_name.items():
            if segment_start not in points:
                raise SchemaValidationError(
                    f"forcing.{name}: missing value at forcing boundary {segment_start:g}"
                )
            values[name] = points[segment_start]
        segments.append(ForcingSegment(float(segment_start), float(segment_end), values))
    return tuple(segments)


def _validate_time_axis(document: Mapping[str, Any]) -> tuple[float, float]:
    integration = document["integration"]
    start = _require_finite_number(integration["start_seconds"], "integration.start_seconds")
    horizon = _require_finite_number(integration["horizon_seconds"], "integration.horizon_seconds")
    end = start + horizon

    checkpoints = [
        _require_finite_number(value, f"integration.checkpoints_seconds.{index}")
        for index, value in enumerate(integration["checkpoints_seconds"])
    ]
    boundaries = [
        _require_finite_number(value, f"integration.forcing_boundaries_seconds.{index}")
        for index, value in enumerate(integration["forcing_boundaries_seconds"])
    ]
    if checkpoints != sorted(set(checkpoints)):
        raise SchemaValidationError("integration.checkpoints_seconds: values must be strictly increasing and unique")
    if any(value <= start or value > end for value in checkpoints):
        raise SchemaValidationError("integration.checkpoints_seconds: checkpoints must be after start and no later than end")
    if checkpoints[-1] != end:
        raise SchemaValidationError("integration.checkpoints_seconds: final checkpoint must equal integration end")
    if boundaries != sorted(set(boundaries)):
        raise SchemaValidationError("integration.forcing_boundaries_seconds: values must be increasing and unique")
    if any(value < start or value > end for value in boundaries):
        raise SchemaValidationError("integration.forcing_boundaries_seconds: boundary outside integration interval")
    return start, end


def _validate_accuracy(document: Mapping[str, Any]) -> None:
    accuracy = document["accuracy"]
    _require_text(accuracy["positivity_policy"], "accuracy.positivity_policy")
    if any(not isinstance(item, str) or not item.strip() for item in accuracy["conservation_checks"]):
        raise SchemaValidationError("accuracy.conservation_checks: entries must be non-empty strings")
    state_names = set(document["initial_state"])
    atol_names = set(accuracy["atol_by_species"])
    if atol_names != state_names:
        missing = state_names - atol_names
        extra = atol_names - state_names
        detail = f"missing={sorted(missing)}, extra={sorted(extra)}"
        raise SchemaValidationError(f"accuracy.atol_by_species: must match initial-state species ({detail})")


def validate_scenario(document: Mapping[str, Any]) -> Mapping[str, Any]:
    """Validate structural, finite-value, forcing, time, and accuracy invariants."""

    validate_scenario_schema(document)
    _require_text(document["scenario_id"], "scenario_id")
    _require_text(document["version"], "version")
    _validate_named_quantities(document["initial_state"], "initial_state")
    _validate_named_quantities(document["environment"], "environment")
    start, end = _validate_time_axis(document)
    _validate_forcing(document["forcing"], start, end)
    _validate_accuracy(document)
    if document["mechanism"]["id"].lower() == "ts1":
        state = document["initial_state"]
        if len(state) != 210:
            raise SchemaValidationError("TS1 initial_state must contain exactly 210 named species")
        background = {"O2", "N2", "M", "S004", "S010"}
        active_nonzero = sum(
            quantity["value"] > 0.0 for name, quantity in state.items() if name not in background
        )
        if active_nonzero < 8:
            raise SchemaValidationError("TS1 requires a nontrivial state with at least 8 active species")
        # TS1 has two scientifically distinct O3 photolysis channels; never
        # collapse them into a single solver-specific shortcut.
        required_forcing = {"jno2", "jo3_a", "jo3_b"}
        missing_forcing = required_forcing - set(document["forcing"])
        if missing_forcing:
            raise SchemaValidationError(
                f"TS1 photolysis forcing is incomplete: missing {sorted(missing_forcing)}"
            )
    boundaries = set(document["integration"]["forcing_boundaries_seconds"])
    checkpoints = set(document["integration"]["checkpoints_seconds"])
    missing_checkpoints = boundaries - {start} - checkpoints
    if missing_checkpoints:
        raise SchemaValidationError(
            "integration checkpoints must include every forcing boundary; "
            f"missing={sorted(missing_checkpoints)}"
        )
    _require_text(document["reference"]["implementation"], "reference.implementation")
    return document


def validate_scenario_pair(
    calibration: Mapping[str, Any], measurement: Mapping[str, Any]
) -> tuple[Mapping[str, Any], Mapping[str, Any]]:
    """Require a calibration/measurement pair with disjoint identities and seeds."""

    validate_scenario(calibration)
    validate_scenario(measurement)
    if calibration["role"] != "calibration" or measurement["role"] != "measurement":
        raise SchemaValidationError("scenario pair: expected calibration followed by measurement role")
    if calibration["mechanism"] != measurement["mechanism"]:
        raise SchemaValidationError("scenario pair: mechanism identities must match")
    if calibration["scenario_id"] == measurement["scenario_id"]:
        raise SchemaValidationError("scenario_id: calibration and measurement identities must be distinct")
    if calibration["workload"]["ensemble_seed"] == measurement["workload"]["ensemble_seed"]:
        raise SchemaValidationError("ensemble_seed: calibration and measurement seeds must be distinct")
    if calibration["forcing"] != measurement["forcing"]:
        raise SchemaValidationError("scenario pair: forcing identity must be identical")
    return calibration, measurement


__all__ = ["validate_scenario", "validate_scenario_pair"]
