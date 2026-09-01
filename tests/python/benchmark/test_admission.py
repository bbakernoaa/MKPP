"""Scientific chemistry-admission tests for solver bindings."""

from __future__ import annotations

import pytest
from mkpp.benchmark.admission import (
    ChemistryObservation,
    build_audit_states,
    compare_chemistry,
)


def observation(
    *,
    rates: tuple[float, ...] = (1.0e-4, 6.0e-34, 2.0e-4, 8.0e-12),
    rhs: tuple[float, ...] = (2.0e6, -2.0e6),
    jacobian: tuple[tuple[float, ...], ...] = ((-2.0e-4, 1.0e-4), (2.0e-4, -1.0e-4)),
    sparsity: tuple[tuple[int, int], ...] = ((0, 0), (0, 1), (1, 0), (1, 1)),
    independent_jacobian: tuple[tuple[float, ...], ...] | None = None,
) -> ChemistryObservation:
    return ChemistryObservation(
        rate_ids=("J1", "R2", "J3", "R4"),
        rates=rates,
        species_ids=("O", "O3"),
        rhs=rhs,
        jacobian=jacobian,
        thresholded_sparsity=sparsity,
        independent_jacobian=independent_jacobian or jacobian,
    )


def test_builds_required_deterministic_audit_state_set() -> None:
    initial = {"O": 1.0e10, "O2": 2.0e10, "O3": 3.0e10, "M": 4.0e10}
    checkpoints = [
        {"O": 1.1e10, "O2": 2.0e10, "O3": 2.9e10, "M": 4.0e10},
        {"O": 1.2e10, "O2": 2.0e10, "O3": 2.8e10, "M": 4.0e10},
    ]

    first = build_audit_states(initial, checkpoints, perturbation_seed=17)
    second = build_audit_states(initial, checkpoints, perturbation_seed=17)

    assert first == second
    assert first[0].kind == "initial"
    assert sum(state.kind == "checkpoint" for state in first) == 2
    assert sum(state.kind == "perturbed" for state in first) >= 8
    assert all(value > 0.0 for state in first for value in state.values.values())


def test_matching_rates_rhs_jacobian_and_structure_are_eligible() -> None:
    assessment = compare_chemistry(
        reference=observation(),
        subject=observation(),
        physics_floors={"rates": 1.0e-40, "rhs": 1.0e-6, "jacobian": 1.0e-15},
    )

    assert assessment.eligible is True
    assert assessment.rate_metrics.maximum == 0.0
    assert assessment.rhs_metrics.wrms == 0.0
    assert assessment.jacobian_metrics.maximum == 0.0
    assert assessment.sparsity_matches is True
    assert assessment.independent_jacobian_maximum == 0.0


def test_physics_floor_keeps_trace_rate_comparison_finite_and_meaningful() -> None:
    reference = observation(rates=(0.0, 1.0e-40, 2.0e-4, 8.0e-12))
    subject = observation(rates=(5.0e-42, 1.05e-40, 2.0e-4, 8.0e-12))

    assessment = compare_chemistry(
        reference=reference,
        subject=subject,
        physics_floors={"rates": 1.0e-40, "rhs": 1.0e-6, "jacobian": 1.0e-15},
    )

    assert assessment.rate_metrics.maximum <= 1.0
    assert assessment.rate_metrics.wrms <= 0.1
    assert assessment.eligible is True


@pytest.mark.parametrize("quantity", ["rates", "rhs", "jacobian"])
def test_each_numeric_parity_gate_can_make_binding_ineligible(quantity: str) -> None:
    changes = {
        "rates": {"rates": (1.0e-4, 6.0e-34, 2.0e-4, 8.0e-10)},
        "rhs": {"rhs": (2.0e6, -1.0e5)},
        "jacobian": {"jacobian": ((-2.0e-4, 1.0e-4), (2.0e-4, -9.0e-3))},
    }
    assessment = compare_chemistry(
        reference=observation(),
        subject=observation(**changes[quantity]),
        physics_floors={"rates": 1.0e-40, "rhs": 1.0e-6, "jacobian": 1.0e-15},
    )

    assert assessment.eligible is False
    assert any(quantity in reason for reason in assessment.reasons)


def test_structure_comparison_is_exact_after_thresholding() -> None:
    subject = observation(sparsity=((0, 0), (0, 1), (1, 1)))

    assessment = compare_chemistry(
        reference=observation(),
        subject=subject,
        physics_floors={"rates": 1.0e-40, "rhs": 1.0e-6, "jacobian": 1.0e-15},
    )

    assert assessment.sparsity_matches is False
    assert assessment.missing_sparsity == ((1, 0),)
    assert assessment.eligible is False


def test_rejects_rate_or_species_identity_permutation_even_if_values_match() -> None:
    subject = ChemistryObservation(
        rate_ids=("R2", "J1", "J3", "R4"),
        rates=observation().rates,
        species_ids=("O3", "O"),
        rhs=observation().rhs,
        jacobian=observation().jacobian,
        thresholded_sparsity=observation().thresholded_sparsity,
        independent_jacobian=observation().independent_jacobian,
    )

    with pytest.raises(ValueError, match="identity"):
        compare_chemistry(
            reference=observation(),
            subject=subject,
            physics_floors={"rates": 1.0e-40, "rhs": 1.0e-6, "jacobian": 1.0e-15},
        )


def test_independent_jacobian_check_has_separate_maximum_gate() -> None:
    subject = observation(independent_jacobian=((-2.0e-4, 1.0e-4), (2.0e-4, -1.0e-2)))

    assessment = compare_chemistry(
        reference=observation(),
        subject=subject,
        physics_floors={"rates": 1.0e-40, "rhs": 1.0e-6, "jacobian": 1.0e-15},
    )

    assert assessment.independent_jacobian_maximum > 10.0
    assert assessment.eligible is False
