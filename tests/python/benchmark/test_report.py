"""Report derivation keeps scientific eligibility and timing boundaries visible."""

from __future__ import annotations

import json
from pathlib import Path

import pytest

from mkpp.benchmark.report import (
    derive_pairwise_comparison,
    read_raw_results,
    render_csv_report,
    render_json_report,
    render_markdown_report,
)


def test_raw_reader_retains_each_jsonl_record_in_order(tmp_path: Path) -> None:
    path = tmp_path / "raw.jsonl"
    path.write_text('{"run":"first"}\n{"run":"second"}\n', encoding="utf-8")
    assert tuple(dict(row) for row in read_raw_results(path)) == ({"run": "first"}, {"run": "second"})


def test_pairwise_ratio_names_its_baseline_and_withholds_ineligible_pairs() -> None:
    comparison = derive_pairwise_comparison(
        baseline_solver_id="micm",
        candidate_solver_id="mkpp",
        baseline_seconds=(4.0, 6.0),
        candidate_seconds=(2.0, 3.0),
        eligible=True,
        seed=11,
    )
    assert comparison["ratio_direction"] == "micm_seconds / mkpp_seconds"
    assert comparison["median_ratio"] == 2.0

    withheld = derive_pairwise_comparison(
        baseline_solver_id="micm",
        candidate_solver_id="mkpp",
        baseline_seconds=(4.0,),
        candidate_seconds=(2.0,),
        eligible=False,
        seed=11,
        withheld_reason="trajectory accuracy failed",
    )
    assert withheld["status"] == "withheld"
    assert withheld["median_ratio"] is None


def test_markdown_report_keeps_solve_and_lifecycle_sections_separate() -> None:
    text = render_markdown_report(
        {
            "mechanism_id": "ts1",
            "admission_status": "chemistry_verified",
            "admission_reason": "KPP is not admitted",
            "steady_state_solve": [
                {
                    "baseline_solver_id": "micm",
                    "candidate_solver_id": "mkpp",
                    "status": "eligible",
                    "median_ratio": 2.0,
                    "ratio_direction": "micm_seconds / mkpp_seconds",
                }
            ],
            "lifecycle": [
                {
                    "baseline_solver_id": "micm",
                    "candidate_solver_id": "mkpp",
                    "status": "withheld",
                    "median_ratio": None,
                    "withheld_reason": "not collected",
                }
            ],
        }
    )
    assert "## Steady-state solve" in text
    assert "## Lifecycle" in text
    assert "micm_seconds / mkpp_seconds" in text
    assert "KPP is not admitted" in text


def test_raw_reader_rejects_non_object_records(tmp_path: Path) -> None:
    path = tmp_path / "raw.jsonl"
    path.write_text(json.dumps(["not", "an", "object"]) + "\n", encoding="utf-8")
    try:
        read_raw_results(path)
    except ValueError as error:
        assert "object" in str(error)
    else:
        raise AssertionError("non-object raw evidence must be rejected")


def test_raw_reader_returns_immutable_nested_evidence(tmp_path: Path) -> None:
    path = tmp_path / "raw.jsonl"
    path.write_text('{"nested":{"sample":[1]}}\n', encoding="utf-8")
    record = read_raw_results(path)[0]
    with pytest.raises(TypeError):
        record["new"] = "value"  # type: ignore[index]
    assert record["nested"]["sample"] == (1,)


def test_json_and_csv_reports_preserve_boundaries_and_uncertainty() -> None:
    document = {
        "mechanism_id": "chapman",
        "admission_status": "chemistry_verified",
        "admission_reason": "all gates passed",
        "steady_state_solve": [
            {
                "baseline_solver_id": "micm",
                "candidate_solver_id": "mkpp",
                "ratio_direction": "micm_seconds / mkpp_seconds",
                "status": "eligible",
                "median_ratio": 1.2,
                "bootstrap_interval": (1.1, 1.3),
            }
        ],
        "lifecycle": [],
    }
    json_report = json.loads(render_json_report(document))
    assert json_report["steady_state_solve"][0]["bootstrap_interval"] == [1.1, 1.3]
    assert json_report["admission_reason"] == "all gates passed"
    csv = render_csv_report(document)
    assert "steady_state_solve" in csv
    assert "1.1" in csv
    assert "lifecycle" not in csv
