"""RED reporting contracts for the mandatory two-solver TS1 track."""

from __future__ import annotations

from copy import deepcopy
from importlib import import_module
from typing import Any

import pytest


def _valid_ts1_report() -> dict[str, Any]:
    return {
        "mechanism_id": "ts1",
        "required_solvers": ["micm", "mkpp"],
        "results": [
            {"solver_id": "micm", "status": "eligible", "throughput": 1.0},
            {"solver_id": "mkpp", "status": "eligible", "throughput": 2.0},
        ],
        "comparisons": [
            {
                "baseline_solver_id": "micm",
                "candidate_solver_id": "mkpp",
                "status": "eligible",
                "median_ratio": 2.0,
            }
        ],
        "claims": ["TS1 MICM/MKPP two-way comparison"],
    }


def _validate(document: dict[str, Any]) -> None:
    reporting = import_module("mkpp.benchmark.report")
    reporting.validate_ts1_report(document)


def test_ts1_report_requires_exactly_micm_and_mkpp() -> None:
    _validate(_valid_ts1_report())

    for missing_solver in ("micm", "mkpp"):
        report = _valid_ts1_report()
        report["required_solvers"].remove(missing_solver)
        report["results"] = [
            result for result in report["results"] if result["solver_id"] != missing_solver
        ]
        with pytest.raises(ValueError, match="TS1|MICM|MKPP|exactly|required"):
            _validate(report)


@pytest.mark.parametrize("placeholder", [None, "N/A", "unavailable", 0.0])
def test_ts1_report_rejects_every_kpp_placeholder(placeholder: object) -> None:
    report = _valid_ts1_report()
    report["results"].append(
        {"solver_id": "kpp", "status": "absent", "throughput": placeholder}
    )

    with pytest.raises(ValueError, match="TS1|KPP|placeholder|forbidden"):
        _validate(report)


def test_ts1_report_rejects_comparisons_that_include_kpp() -> None:
    report = _valid_ts1_report()
    report["comparisons"].append(
        {
            "baseline_solver_id": "kpp",
            "candidate_solver_id": "mkpp",
            "status": "withheld",
            "median_ratio": None,
        }
    )

    with pytest.raises(ValueError, match="TS1|KPP|comparison|forbidden"):
        _validate(report)


@pytest.mark.parametrize(
    "claim",
    [
        "TS1 three-way solver evidence",
        "MICM vs KPP vs MKPP",
        "all three solvers agree",
    ],
)
def test_ts1_report_cannot_claim_three_way_evidence(claim: str) -> None:
    report = deepcopy(_valid_ts1_report())
    report["claims"].append(claim)

    with pytest.raises(ValueError, match="TS1|three-way|three solvers|KPP"):
        _validate(report)
