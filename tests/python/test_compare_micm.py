"""Unit tests for automated MKPP vs MICM comparison script (scripts/compare_micm.py)."""

import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent.parent
sys.path.insert(0, str(REPO_ROOT))

from scripts.compare_micm import run_micm_comparison  # noqa: E402


def test_run_micm_comparison_chapman_fixture():
    """Verify run_micm_comparison on fixture MICM Chapman mechanism."""
    mech_path = REPO_ROOT / "fixtures/micm-chapman/mechanism.json"
    env_path = REPO_ROOT / "fixtures/micm-chapman/test_env.json"

    res = run_micm_comparison(
        mech_path=mech_path,
        env_path=env_path,
        cells=10,
        steps=10,
        dt=60.0,
    )

    assert res["mechanism"] == "mechanism"
    assert res["structural"]["num_species"] == 4
    assert res["structural"]["num_reactions"] == 4
    assert res["structural"]["jacobian_non_zeros"] == 8
    assert res["accuracy"]["overall_passed"] is True
    assert len(res["accuracy"]["species_results"]) == 4


def test_run_micm_comparison_mkpp_chapman():
    """Verify run_micm_comparison on MKPP chapman.yaml mechanism."""
    mech_path = REPO_ROOT / "mechanisms/chapman.yaml"

    res = run_micm_comparison(
        mech_path=mech_path,
        cells=10,
        steps=10,
        dt=60.0,
    )

    assert res["structural"]["num_species"] == 4
    assert res["accuracy"]["overall_passed"] is True
