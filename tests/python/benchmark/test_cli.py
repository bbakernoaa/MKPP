"""The command line lists and validates inputs but never fabricates evidence."""

from __future__ import annotations

import json
import subprocess
from pathlib import Path

from mkpp.benchmark import cli
from mkpp.benchmark.cli import EXIT_ENVIRONMENT, main


def test_list_mechanisms_includes_the_ts1_two_way_scope(capsys: object) -> None:
    assert main(["--list-mechanisms"]) == 0
    output = capsys.readouterr().out  # type: ignore[attr-defined]
    assert '"mechanism_id": "ts1"' in output
    assert '"micm"' in output and '"mkpp"' in output


def test_campaign_validation_resolves_all_immutable_inputs(capsys: object) -> None:
    assert main(["--validate", "--campaign", "benchmarks/solver_comparison/campaigns/cpu-primary-v1.yaml"]) == 0
    assert '"campaign_id": "cpu-primary-v1"' in capsys.readouterr().out  # type: ignore[attr-defined]


def test_campaign_execution_fails_without_silent_or_partial_output(tmp_path: Path, capsys: object) -> None:
    output = tmp_path / "raw.jsonl"
    assert (
        main(["--campaign", "benchmarks/solver_comparison/campaigns/cpu-primary-v1.yaml", "--output", str(output)])
        == EXIT_ENVIRONMENT
    )
    assert not output.exists()
    assert "runner set is not exact" in capsys.readouterr().err  # type: ignore[attr-defined]


def test_campaign_execution_retains_only_real_named_runner_results(tmp_path: Path, monkeypatch) -> None:
    campaign = tmp_path / "campaign.yaml"
    campaign.write_text(
        "\n".join(
            (
                "campaign_id: test-ts1",
                "targets:",
                "  - manifest: benchmarks/solver_comparison/manifests/ts1-v1.yaml",
                "    scenarios:",
                "      - benchmarks/solver_comparison/scenarios/ts1-calibration-v1.yaml",
                "      - benchmarks/solver_comparison/scenarios/ts1-measurement-v1.yaml",
                "resources:",
                "  primary: {physical_cores: 1, threads: 1}",
                "",
            )
        ),
        encoding="utf-8",
    )
    runners = []
    for solver in ("micm", "mkpp"):
        executable = tmp_path / solver
        executable.write_text("#!/bin/sh\n", encoding="utf-8")
        executable.chmod(0o755)
        runners.append(f"{solver}={executable}")

    def completed(command, **_):
        solver = Path(command[0]).name
        sha = "0" * 64
        result = {
            "schema_version": 1,
            "campaign_id": "test-ts1",
            "run_id": solver,
            "block": 0,
            "order_position": 0,
            "solver": {"id": solver, "version": "1", "revision": "pinned", "backend": "cpu", "method": "ros3"},
            "manifest": {"id": "ts1", "version": "1", "sha256": sha},
            "scenario": {"id": "ts1-measurement-v1", "version": "1", "sha256": sha},
            "configuration": {"id": "frozen", "sha256": sha, "frozen": True, "controls": {}},
            "build": {"binary_sha256": sha, "asset_sha256": [sha], "compiler": "c++", "flags": [], "precision": "binary64"},
            "resources": {"hardware_id": "test", "physical_cores": 1, "threads": 1, "affinity": "core", "numa_policy": "local"},
            "timing": {
                "boundary": "steady_state_solve",
                "elapsed_ms": 1.0,
                "cell_steps": 1,
                "clock": "steady",
                "synchronized": True,
                "synchronization": "fence",
                "lifecycle_ms": {},
            },
            "state": {"checkpoints": [{"time_seconds": 1.0, "values": {"O3": 1.0}}]},
            "work": {"rhs": {"available": True, "value": 1}},
            "status": "success",
            "diagnostics": [],
        }
        return subprocess.CompletedProcess(command, 0, json.dumps(result), "")

    monkeypatch.setattr(cli.subprocess, "run", completed)
    output = tmp_path / "raw.jsonl"
    report = tmp_path / "summary.md"
    arguments = ["--campaign", str(campaign), "--output", str(output), "--report", str(report)]
    assert main([*arguments, *sum((["--runner", item] for item in runners), [])]) == 0
    assert [json.loads(line)["solver"]["id"] for line in output.read_text().splitlines()] == ["micm", "mkpp"]
    assert "raw_evidence_retained" in report.read_text(encoding="utf-8")
