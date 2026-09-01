"""RED regression tests for previously misleading comparison shortcuts."""

from __future__ import annotations

from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
LEGACY_COMPARISON = ROOT / "scripts" / "compare_micm.py"
LEGACY_TS1 = ROOT / "tests" / "integration" / "e2e_validation" / "benchmark_mkpp_vs_micm_ts1.cpp"
ADAPTERS = ROOT / "src" / "mkpp" / "benchmark" / "adapters"
ORCHESTRATOR = ROOT / "src" / "mkpp" / "benchmark" / "orchestrator.py"


def test_scipy_radau_is_never_presented_as_micm() -> None:
    source = LEGACY_COMPARISON.read_text(encoding="utf-8")

    assert "SciPy Radau / MICM" not in source
    assert "MICM-compatible reference" not in source


def test_scipy_bdf_is_never_used_as_an_mkpp_fallback() -> None:
    source = LEGACY_COMPARISON.read_text(encoding="utf-8")

    assert 'method="BDF"' not in source
    assert "sol_mkpp = solve_ivp" not in source


def test_subject_state_is_never_copied_from_the_reference() -> None:
    source = LEGACY_COMPARISON.read_text(encoding="utf-8")

    assert "Final state from reference comparison" not in source
    assert "final_mkpp = final_ref" not in source


def test_cross_solver_state_comparison_never_assumes_raw_index_identity() -> None:
    source = LEGACY_TS1.read_text(encoding="utf-8")

    assert "s.variables_[cell][spec]" not in source
    assert "for (int spec = 0; spec < num_species; ++spec)" not in source


def test_every_requested_solver_has_a_real_adapter_and_cannot_be_silently_omitted() -> None:
    for solver in ("micm", "kpp", "mkpp"):
        adapter = ADAPTERS / f"{solver}.py"
        assert adapter.is_file(), f"missing required {solver} adapter"
        source = adapter.read_text(encoding="utf-8").lower()
        assert "surrogate" not in source
        assert "silent" not in source

    orchestration = ORCHESTRATOR.read_text(encoding="utf-8").lower()
    assert "requested_solvers" in orchestration
    assert "missing_solvers" in orchestration
    assert "fatal error:" in orchestration
