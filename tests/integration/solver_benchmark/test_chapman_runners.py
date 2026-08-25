"""RED contracts for the three real Chapman native runners."""

from __future__ import annotations

from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[3]
RUNNERS = ROOT / "benchmarks" / "solver_comparison" / "runners"


def _runner_source(solver: str) -> str:
    candidates = {
        "micm": (RUNNERS / "micm" / "main.cpp",),
        "kpp": (RUNNERS / "kpp" / "driver.f90", RUNNERS / "kpp" / "driver.c"),
        "mkpp": (RUNNERS / "mkpp" / "main.cpp",),
    }[solver]
    existing = next((path for path in candidates if path.is_file()), None)
    assert existing is not None, f"missing real {solver} Chapman runner: expected one of {candidates}"
    return existing.read_text(encoding="utf-8")


@pytest.mark.parametrize(
    ("solver", "identity_tokens"),
    [
        ("micm", ("micm", "Solve(")),
        ("kpp", ("kpp", "INTEGRATE")),
        ("mkpp", ("mkpp", "MechanismRegistry", "execute")),
    ],
)
def test_chapman_runner_executes_and_reports_actual_solver_identity(solver: str, identity_tokens: tuple[str, ...]) -> None:
    source = _runner_source(solver)

    for token in identity_tokens:
        assert token in source, f"{solver} runner lacks real-solver evidence {token!r}"
    assert f'"{solver}"' in source, f"{solver} runner must report its literal identity"


@pytest.mark.parametrize("solver", ["micm", "kpp", "mkpp"])
def test_chapman_runner_uses_named_species_and_photolysis_mapping(solver: str) -> None:
    source = _runner_source(solver)

    for canonical_name in ("O", "O2", "O3", "M", "J1", "J3"):
        assert canonical_name in source
    assert "species_map" in source.lower() or "species_index" in source.lower()


@pytest.mark.parametrize("solver", ["micm", "kpp", "mkpp"])
def test_chapman_runner_resets_state_outside_every_timed_sample(solver: str) -> None:
    source = _runner_source(solver).lower()

    assert "reset" in source
    assert source.index("reset") < source.index("start_timing")


@pytest.mark.parametrize("solver", ["micm", "kpp", "mkpp"])
def test_chapman_runner_reserves_stdout_for_one_json_result(solver: str) -> None:
    source = _runner_source(solver).lower()

    assert "json" in source
    assert "stderr" in source or "cerr" in source or "error_unit" in source
    assert "stdout" in source or "cout" in source or "output_unit" in source


@pytest.mark.parametrize("solver", ["micm", "kpp", "mkpp"])
def test_chapman_runner_exposes_exact_solve_timing_boundaries(solver: str) -> None:
    source = _runner_source(solver).lower()

    assert "steady_state_solve" in source
    assert "start_timing" in source and "stop_timing" in source
    assert "synchron" in source
    assert source.index("start_timing") < source.index("stop_timing")
