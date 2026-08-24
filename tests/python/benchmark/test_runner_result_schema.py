"""Contract tests for native solver runner result documents."""

from __future__ import annotations

from copy import deepcopy

import pytest

from mkpp.benchmark.schema import SchemaValidationError, validate_runner_result

SHA_A = "a" * 64
SHA_B = "b" * 64
SHA_C = "c" * 64


def valid_runner_result() -> dict[str, object]:
    """Return a minimal result containing every required evidence category."""
    return {
        "schema_version": 1,
        "campaign_id": "cpu-primary-v1",
        "run_id": "chapman-mkpp-block-0",
        "block": 0,
        "order_position": 1,
        "solver": {
            "id": "mkpp",
            "version": "0.1.0",
            "revision": "0123456789abcdef",
            "backend": "serial-cpu",
            "method": "ros3",
        },
        "manifest": {"id": "chapman", "version": "1", "sha256": SHA_A},
        "scenario": {
            "id": "chapman-measurement",
            "version": "1",
            "sha256": SHA_B,
        },
        "configuration": {
            "id": "mkpp-ros3-equal-accuracy",
            "sha256": SHA_C,
            "frozen": True,
            "controls": {"rtol": 1.0e-6, "atol": 1.0e-12},
        },
        "build": {
            "binary_sha256": SHA_A,
            "asset_sha256": [SHA_B],
            "compiler": "clang++ 18.1.0",
            "flags": ["-O3", "-DNDEBUG"],
            "precision": "float64",
        },
        "resources": {
            "hardware_id": "test-host",
            "physical_cores": 1,
            "threads": 1,
            "affinity": "core:0",
            "numa_policy": "local",
        },
        "timing": {
            "boundary": "steady_state_solve",
            "elapsed_ms": 1250.0,
            "cell_steps": 100_000,
            "clock": "steady_clock",
            "synchronized": True,
            "synchronization": "Kokkos::fence",
            "lifecycle_ms": {
                "allocation": 2.0,
                "initialization": 1.5,
                "solve": 1250.0,
                "output": 0.5,
            },
        },
        "state": {
            "checkpoints": [
                {
                    "time_seconds": 60.0,
                    "values": {"O": 1.1e10, "O3": 2.9e10},
                },
                {
                    "time_seconds": 600.0,
                    "values": {"O": 1.2e10, "O3": 2.8e10},
                },
            ]
        },
        "work": {
            "rhs_evaluations": {"available": True, "value": 42},
            "rejected_steps": {
                "available": False,
                "reason": "runner does not expose this counter",
            },
        },
        "status": "success",
        "diagnostics": [],
    }


def test_accepts_complete_runner_result_with_auditable_evidence() -> None:
    result = valid_runner_result()

    assert validate_runner_result(result) == result


@pytest.mark.parametrize(
    "required_field",
    [
        "solver",
        "manifest",
        "scenario",
        "configuration",
        "build",
        "resources",
        "timing",
        "state",
        "work",
        "status",
        "diagnostics",
    ],
)
def test_rejects_missing_identity_provenance_or_result_evidence(required_field: str) -> None:
    result = valid_runner_result()
    del result[required_field]

    with pytest.raises(SchemaValidationError, match=required_field):
        validate_runner_result(result)


def test_rejects_unpinned_or_malformed_provenance_hashes() -> None:
    result = valid_runner_result()
    result["manifest"]["sha256"] = "not-a-sha256"  # type: ignore[index]

    with pytest.raises(SchemaValidationError, match="sha256"):
        validate_runner_result(result)


@pytest.mark.parametrize("elapsed_ms", [0.0, -1.0])
def test_rejects_nonpositive_elapsed_time(elapsed_ms: float) -> None:
    result = valid_runner_result()
    result["timing"]["elapsed_ms"] = elapsed_ms  # type: ignore[index]

    with pytest.raises(SchemaValidationError, match="elapsed_ms"):
        validate_runner_result(result)


def test_rejects_unsynchronized_steady_state_timing() -> None:
    result = valid_runner_result()
    result["timing"]["synchronized"] = False  # type: ignore[index]
    result["timing"]["synchronization"] = "none"  # type: ignore[index]

    with pytest.raises(SchemaValidationError, match="synchron"):
        validate_runner_result(result)


def test_rejects_empty_or_nonfinite_checkpoint_state() -> None:
    empty = valid_runner_result()
    empty["state"]["checkpoints"] = []  # type: ignore[index]
    with pytest.raises(SchemaValidationError, match="checkpoints"):
        validate_runner_result(empty)

    nonfinite = valid_runner_result()
    nonfinite["state"]["checkpoints"][0]["values"]["O"] = float("nan")  # type: ignore[index]
    with pytest.raises(SchemaValidationError, match="finite"):
        validate_runner_result(nonfinite)


def test_requires_unavailable_counter_to_explain_why() -> None:
    result = valid_runner_result()
    result["work"]["rejected_steps"] = {"available": False}  # type: ignore[index]

    with pytest.raises(SchemaValidationError, match="reason"):
        validate_runner_result(result)


@pytest.mark.parametrize("status", ["failed", "invalid", "ineligible"])
def test_nonsuccess_status_requires_actionable_diagnostics(status: str) -> None:
    result = valid_runner_result()
    result["status"] = status

    with pytest.raises(SchemaValidationError, match="diagnostics"):
        validate_runner_result(result)


def test_accepts_retained_failure_with_diagnostics() -> None:
    result = valid_runner_result()
    result["status"] = "failed"
    result["diagnostics"] = ["FATAL ERROR: native solver returned code 7"]

    assert validate_runner_result(result) == result


def test_rejects_unknown_fields_in_strict_result_contract() -> None:
    result = deepcopy(valid_runner_result())
    result["surrogate_solver"] = "scipy"

    with pytest.raises(SchemaValidationError, match="surrogate_solver"):
        validate_runner_result(result)
