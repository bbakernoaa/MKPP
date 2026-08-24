"""Eligibility-preserving report validation and derivation."""

from __future__ import annotations

import re
from collections.abc import Mapping, Sequence
from typing import Any

_TS1_SOLVERS = {"micm", "mkpp"}


def validate_ts1_report(document: Mapping[str, Any]) -> Mapping[str, Any]:
    """Reject any TS1 report that implies an unavailable KPP comparison."""

    if str(document.get("mechanism_id", "")).lower() != "ts1":
        raise ValueError("TS1 report must identify mechanism_id 'ts1'")
    required = document.get("required_solvers")
    if not isinstance(required, Sequence) or isinstance(required, str | bytes):
        raise ValueError("TS1 requires exactly MICM and MKPP")
    if set(required) != _TS1_SOLVERS or len(required) != 2:
        raise ValueError("TS1 requires exactly MICM and MKPP")

    results = document.get("results")
    if not isinstance(results, Sequence) or isinstance(results, str | bytes):
        raise ValueError("TS1 results must contain exactly MICM and MKPP")
    result_solvers = {entry.get("solver_id") for entry in results if isinstance(entry, Mapping)}
    if result_solvers != _TS1_SOLVERS or len(results) != 2:
        raise ValueError("TS1 KPP result or placeholder is forbidden; results require MICM and MKPP only")

    comparisons = document.get("comparisons", ())
    if not isinstance(comparisons, Sequence) or isinstance(comparisons, str | bytes):
        raise ValueError("TS1 comparisons must be a sequence")
    for comparison in comparisons:
        if not isinstance(comparison, Mapping):
            raise ValueError("TS1 comparison must be an object")
        participants = {
            comparison.get("baseline_solver_id"),
            comparison.get("candidate_solver_id"),
        }
        if participants != _TS1_SOLVERS:
            raise ValueError("TS1 KPP comparison is forbidden")

    claims = document.get("claims", ())
    if not isinstance(claims, Sequence) or isinstance(claims, str | bytes):
        raise ValueError("TS1 claims must be a sequence")
    forbidden_phrases = ("three-way", "three solvers")
    for claim in claims:
        normalized = str(claim).lower()
        if any(phrase in normalized for phrase in forbidden_phrases) or re.search(
            r"(?<!m)\bkpp\b", normalized
        ):
            raise ValueError("TS1 cannot make a three-way or KPP claim")
    return document


__all__ = ["validate_ts1_report"]
