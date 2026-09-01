"""Unit tests for automated MKPP vs MICM comparison script (scripts/compare_micm.py)."""

import sys
from pathlib import Path

import pytest

REPO_ROOT = Path(__file__).resolve().parent.parent.parent
sys.path.insert(0, str(REPO_ROOT))

from scripts.compare_micm import run_micm_comparison  # noqa: E402


def test_legacy_comparison_is_explicitly_retired_for_fixture():
    """The historical wrapper cannot silently claim a MICM comparison."""
    mech_path = REPO_ROOT / "fixtures/micm-chapman/mechanism.json"
    env_path = REPO_ROOT / "fixtures/micm-chapman/test_env.json"

    with pytest.raises(RuntimeError, match="retired reference-only"):
        run_micm_comparison(mech_path=mech_path, env_path=env_path, cells=10, steps=10, dt=60.0)


def test_legacy_comparison_is_explicitly_retired_for_mkpp_input():
    """No mechanism format changes the reference-only status."""
    mech_path = REPO_ROOT / "mechanisms/openatmos/chapman/mechanism.json"

    with pytest.raises(RuntimeError, match="compare_solvers.py"):
        run_micm_comparison(mech_path=mech_path, cells=10, steps=10, dt=60.0)
