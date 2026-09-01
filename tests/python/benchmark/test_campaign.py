"""Campaign eligibility checks for comparable paired performance evidence."""

from __future__ import annotations

import pytest
from mkpp.benchmark.models import (
    BuildProvenance,
    CampaignStatus,
    HashIdentity,
    ResourcePolicy,
    RunStatus,
    SolverId,
    SolverRun,
    TimingBoundary,
)
from mkpp.benchmark.orchestrator import advance_campaign_status, assess_repeatability, require_comparable_pairs


def run(
    solver: SolverId,
    block: int,
    *,
    matching_key: str = "a" * 64,
    boundary: TimingBoundary = TimingBoundary.STEADY_STATE_SOLVE,
    cores: int = 1,
    threads: int = 1,
    elapsed: float = 2.0,
) -> SolverRun:
    identity = HashIdentity("chapman", "v1", "b" * 64)
    resources = ResourcePolicy("host", "cpu", cores, threads, "core", "local")
    return SolverRun(
        "campaign",
        f"{solver.value}-{block}",
        block,
        1,
        0,
        matching_key,
        solver,
        identity,
        identity,
        identity,
        BuildProvenance("c" * 64, (), "cc", (), "double"),
        resources,
        boundary,
        10,
        elapsed,
        "steady",
        True,
        "none",
        (),
        (),
        (),
        RunStatus.SUCCESS,
    )


def test_pairs_require_matching_key_resources_and_timing_boundary() -> None:
    baseline = (run(SolverId.MICM, 0), run(SolverId.MICM, 1))
    candidate = (run(SolverId.MKPP, 0), run(SolverId.MKPP, 1))
    assert require_comparable_pairs(baseline, candidate) == (0, 1)

    with pytest.raises(ValueError, match="matching key"):
        require_comparable_pairs(baseline, (run(SolverId.MKPP, 0, matching_key="d" * 64), candidate[1]))
    with pytest.raises(ValueError, match="resources"):
        require_comparable_pairs(baseline, (run(SolverId.MKPP, 0, threads=2), candidate[1]))
    with pytest.raises(ValueError, match="timing boundary"):
        require_comparable_pairs(baseline, (run(SolverId.MKPP, 0, boundary=TimingBoundary.LIFECYCLE), candidate[1]))


def test_primary_cpu_policy_requires_one_physical_core_and_thread() -> None:
    with pytest.raises(ValueError, match="one physical core"):
        require_comparable_pairs((run(SolverId.MICM, 0, cores=2),), (run(SolverId.MKPP, 0, cores=2),), primary_cpu=True)


def test_repeatability_is_within_five_percent_of_prior_median() -> None:
    assert assess_repeatability((100.0, 101.0), (102.0, 98.0))
    assert not assess_repeatability((100.0,), (106.0,))


def test_campaign_lifecycle_is_ordered_and_cannot_skip_scientific_gates() -> None:
    assert advance_campaign_status(CampaignStatus.CONFIGURED) is CampaignStatus.PREFLIGHT_PASSED
    with pytest.raises(ValueError, match="cannot transition"):
        advance_campaign_status(CampaignStatus.CONFIGURED, CampaignStatus.MEASURING)
