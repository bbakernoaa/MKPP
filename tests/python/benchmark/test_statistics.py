"""Robust, seeded summaries for paired timing samples."""

from __future__ import annotations

import pytest
from mkpp.benchmark.statistics import (
    bootstrap_median_interval,
    paired_ratio_summary,
    robust_summary,
)


def test_robust_summary_reports_median_iqr_and_mad_without_outlier_discard() -> None:
    summary = robust_summary((1.0, 2.0, 3.0, 4.0, 1000.0))
    assert summary.median == 3.0
    assert summary.iqr == 2.0
    assert summary.mad == 1.0
    assert summary.samples == (1.0, 2.0, 3.0, 4.0, 1000.0)


def test_seeded_10000_resample_bootstrap_is_reproducible() -> None:
    values = (1.0, 2.0, 3.0, 4.0, 5.0)
    assert bootstrap_median_interval(values, seed=9) == bootstrap_median_interval(values, seed=9)


def test_paired_ratio_uses_each_block_and_rejects_nonmatching_lengths() -> None:
    summary = paired_ratio_summary((10.0, 20.0, 40.0), (5.0, 10.0, 20.0), seed=1)
    assert summary.raw_ratios == (2.0, 2.0, 2.0)
    assert summary.median_ratio == 2.0
    with pytest.raises(ValueError, match="same number"):
        paired_ratio_summary((10.0,), (5.0, 10.0), seed=1)
