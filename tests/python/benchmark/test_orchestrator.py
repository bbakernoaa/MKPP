"""Tests for native JSON runner orchestration and retained failures."""

from __future__ import annotations

import sys
from pathlib import Path

import pytest

from mkpp.benchmark.adapters.base import PreparedAdapterRun
from mkpp.benchmark.models import SolverId
from mkpp.benchmark.orchestrator import NativeRunnerError, invoke_json_runner

from .test_runner_result_schema import valid_runner_result


def _prepared(tmp_path: Path, source: str) -> PreparedAdapterRun:
    script = tmp_path / "runner.py"
    script.write_text(source, encoding="utf-8")
    return PreparedAdapterRun(
        request=None,  # type: ignore[arg-type]
        command=(sys.executable, str(script)),
        working_directory=str(tmp_path),
    )


def test_invokes_real_runner_and_validates_single_json_document(tmp_path: Path) -> None:
    result = valid_runner_result()
    prepared = _prepared(tmp_path, f"import json\nprint(json.dumps({result!r}))\n")

    assert invoke_json_runner(prepared, SolverId.MKPP, timeout_seconds=5) == result


@pytest.mark.parametrize(
    ("source", "message"),
    [
        ("raise SystemExit(7)\n", "code 7"),
        ("print('not json')\n", "JSON"),
        ("print('{}')\nprint('{}')\n", "exactly one"),
    ],
)
def test_runner_failures_are_actionable(tmp_path: Path, source: str, message: str) -> None:
    prepared = _prepared(tmp_path, source)

    with pytest.raises(NativeRunnerError, match=message):
        invoke_json_runner(prepared, SolverId.MICM, timeout_seconds=5)


def test_timeout_is_fatal_and_names_solver(tmp_path: Path) -> None:
    prepared = _prepared(tmp_path, "import time\ntime.sleep(5)\n")

    with pytest.raises(NativeRunnerError, match=r"FATAL ERROR:.*kpp.*timed out"):
        invoke_json_runner(prepared, SolverId.KPP, timeout_seconds=0.01)


def test_environment_is_extended_without_losing_required_process_state(tmp_path: Path) -> None:
    result = valid_runner_result()
    source = (
        "import json, os\n"
        "assert os.environ['BENCHMARK_SENTINEL'] == 'present'\n"
        f"print(json.dumps({result!r}))\n"
    )
    prepared = PreparedAdapterRun(
        request=None,  # type: ignore[arg-type]
        command=(sys.executable, str(tmp_path / "runner.py")),
        working_directory=str(tmp_path),
        environment=(("BENCHMARK_SENTINEL", "present"),),
    )
    (tmp_path / "runner.py").write_text(source, encoding="utf-8")

    assert invoke_json_runner(prepared, SolverId.MKPP, timeout_seconds=5)["status"] == "success"
