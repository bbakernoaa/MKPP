"""Canonical chemistry parity gates used before solver admission."""

from __future__ import annotations

import math
import random
from collections.abc import Mapping
from dataclasses import dataclass
from types import MappingProxyType

_SYMMETRIC_RELATIVE_SCALE = 5.0e-11


@dataclass(frozen=True, slots=True)
class AuditState:
    """One deterministic, physically valid state used for chemistry audits."""

    kind: str
    values: Mapping[str, float]


@dataclass(frozen=True, slots=True)
class ChemistryObservation:
    """Canonical rates, tendency, and Jacobian observed from one binding."""

    rate_ids: tuple[str, ...]
    rates: tuple[float, ...]
    species_ids: tuple[str, ...]
    rhs: tuple[float, ...]
    jacobian: tuple[tuple[float, ...], ...]
    thresholded_sparsity: tuple[tuple[int, int], ...]
    independent_jacobian: tuple[tuple[float, ...], ...]


@dataclass(frozen=True, slots=True)
class NormalizedMetrics:
    maximum: float
    wrms: float


@dataclass(frozen=True, slots=True)
class ChemistryAssessment:
    eligible: bool
    rate_metrics: NormalizedMetrics
    rhs_metrics: NormalizedMetrics
    jacobian_metrics: NormalizedMetrics
    sparsity_matches: bool
    missing_sparsity: tuple[tuple[int, int], ...]
    extra_sparsity: tuple[tuple[int, int], ...]
    independent_jacobian_maximum: float
    reasons: tuple[str, ...]


def _immutable_state(kind: str, values: Mapping[str, float]) -> AuditState:
    checked: dict[str, float] = {}
    for name, value in values.items():
        numeric = float(value)
        if not math.isfinite(numeric) or numeric <= 0.0:
            raise ValueError(f"audit state species '{name}' must be finite and positive")
        checked[name] = numeric
    return AuditState(kind=kind, values=MappingProxyType(checked))


def build_audit_states(
    initial_state: Mapping[str, float],
    checkpoint_states: list[Mapping[str, float]] | tuple[Mapping[str, float], ...],
    *,
    perturbation_seed: int,
    perturbation_count: int = 8,
) -> tuple[AuditState, ...]:
    """Build initial, checkpoint, and deterministic perturbed audit states."""

    if perturbation_count < 8:
        raise ValueError("chemistry admission requires at least eight perturbed audit states")
    species = tuple(initial_state)
    if not species:
        raise ValueError("audit state cannot be empty")

    states = [_immutable_state("initial", initial_state)]
    for checkpoint in checkpoint_states:
        if tuple(checkpoint) != species:
            raise ValueError("checkpoint species identity must match the initial audit state")
        states.append(_immutable_state("checkpoint", checkpoint))

    randomizer = random.Random(perturbation_seed)
    for _ in range(perturbation_count):
        perturbed = {name: float(initial_state[name]) * math.exp(randomizer.uniform(-0.35, 0.35)) for name in species}
        states.append(_immutable_state("perturbed", perturbed))
    return tuple(states)


def _flatten(matrix: tuple[tuple[float, ...], ...]) -> tuple[float, ...]:
    return tuple(value for row in matrix for value in row)


def _metrics(reference: tuple[float, ...], subject: tuple[float, ...], floor: float) -> NormalizedMetrics:
    if len(reference) != len(subject):
        raise ValueError("chemistry observation dimensions must match")
    if not math.isfinite(floor) or floor <= 0.0:
        raise ValueError("physics scale floor must be finite and positive")
    normalized: list[float] = []
    for expected, actual in zip(reference, subject, strict=True):
        if not math.isfinite(expected) or not math.isfinite(actual):
            raise ValueError("chemistry observations must be finite")
        denominator = floor + _SYMMETRIC_RELATIVE_SCALE * max(abs(expected), abs(actual))
        normalized.append(abs(actual - expected) / denominator)
    if not normalized:
        raise ValueError("chemistry observation cannot be empty")
    return NormalizedMetrics(
        maximum=max(normalized),
        wrms=math.sqrt(sum(value * value for value in normalized) / len(normalized)),
    )


def compare_chemistry(
    *,
    reference: ChemistryObservation,
    subject: ChemistryObservation,
    physics_floors: Mapping[str, float],
) -> ChemistryAssessment:
    """Compare one solver binding with canonical chemistry admission evidence."""

    if reference.rate_ids != subject.rate_ids or reference.species_ids != subject.species_ids:
        raise ValueError("canonical rate and species identity/order must match")
    required_floors = {"rates", "rhs", "jacobian"}
    if not required_floors.issubset(physics_floors):
        raise ValueError("physics floors must cover rates, rhs, and jacobian")

    rate_metrics = _metrics(reference.rates, subject.rates, physics_floors["rates"])
    rhs_metrics = _metrics(reference.rhs, subject.rhs, physics_floors["rhs"])
    jacobian_metrics = _metrics(_flatten(reference.jacobian), _flatten(subject.jacobian), physics_floors["jacobian"])
    independent_metrics = _metrics(
        _flatten(subject.jacobian),
        _flatten(subject.independent_jacobian),
        physics_floors["jacobian"],
    )

    reference_sparsity = set(reference.thresholded_sparsity)
    subject_sparsity = set(subject.thresholded_sparsity)
    missing = tuple(sorted(reference_sparsity - subject_sparsity))
    extra = tuple(sorted(subject_sparsity - reference_sparsity))

    reasons: list[str] = []
    for name, metrics in (
        ("rates", rate_metrics),
        ("rhs", rhs_metrics),
        ("jacobian", jacobian_metrics),
    ):
        if metrics.maximum > 1.0 or metrics.wrms > 0.1:
            reasons.append(f"{name} parity gate failed")
    if missing or extra:
        reasons.append("jacobian sparsity structure differs")
    if independent_metrics.maximum > 10.0:
        reasons.append("independent jacobian check failed")

    return ChemistryAssessment(
        eligible=not reasons,
        rate_metrics=rate_metrics,
        rhs_metrics=rhs_metrics,
        jacobian_metrics=jacobian_metrics,
        sparsity_matches=not missing and not extra,
        missing_sparsity=missing,
        extra_sparsity=extra,
        independent_jacobian_maximum=independent_metrics.maximum,
        reasons=tuple(reasons),
    )
