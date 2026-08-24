"""Fail-fast orchestration helpers for isolated native solver runners."""

from __future__ import annotations

import json
import os
import subprocess
from collections.abc import Mapping
from dataclasses import dataclass
from typing import Any

from mkpp.benchmark.accuracy import TrajectoryAccuracyResult
from mkpp.benchmark.adapters.base import AdapterProtocol, PreparedAdapterRun
from mkpp.benchmark.admission import ChemistryAssessment
from mkpp.benchmark.calibration import FrozenConfiguration
from mkpp.benchmark.models import RunStatus, SolverId, SolverRun
from mkpp.benchmark.reference import ReferenceAttemptsResult
from mkpp.benchmark.report import validate_ts1_report
from mkpp.benchmark.schema import SchemaValidationError, validate_runner_result


class NativeRunnerError(RuntimeError):
    """A retained, actionable native-runner protocol failure."""

    def __init__(self, solver_id: SolverId, diagnostic: str, *, stderr: str = "") -> None:
        safe_stderr = stderr.strip()
        suffix = f"; stderr: {safe_stderr}" if safe_stderr else ""
        super().__init__(f"FATAL ERROR: {solver_id.value} native runner {diagnostic}{suffix}")
        self.solver_id = solver_id
        self.diagnostic = diagnostic
        self.stderr = safe_stderr


@dataclass(frozen=True, slots=True)
class ChapmanFlowResult:
    """Retained outcome of the ordered Chapman scientific gates."""

    eligible: bool
    eligible_runs: tuple[SolverRun, ...]
    reasons: tuple[str, ...]

    @property
    def speedup_allowed(self) -> bool:
        return self.eligible


@dataclass(frozen=True, slots=True)
class Ts1FlowResult:
    """Mandatory two-solver TS1 result, including explicit ineligibility."""

    scientific: ChapmanFlowResult
    report: Mapping[str, Any]


def require_requested_solvers(
    requested_solvers: tuple[SolverId, ...],
    adapters: Mapping[SolverId, AdapterProtocol],
) -> tuple[AdapterProtocol, ...]:
    """Resolve every requested solver or stop before any campaign work begins."""

    missing_solvers = tuple(solver for solver in requested_solvers if solver not in adapters)
    if missing_solvers:
        names = ", ".join(solver.value for solver in missing_solvers)
        raise RuntimeError(f"FATAL ERROR: missing requested solver adapters: {names}")
    return tuple(adapters[solver] for solver in requested_solvers)


def assess_chapman_flow(
    *,
    preflight_passed: bool,
    requested_solvers: tuple[SolverId, ...],
    adapters: Mapping[SolverId, AdapterProtocol],
    chemistry: Mapping[SolverId, ChemistryAssessment],
    reference: ReferenceAttemptsResult,
    frozen_configurations: Mapping[SolverId, FrozenConfiguration],
    trajectory_accuracy: Mapping[SolverId, TrajectoryAccuracyResult],
    runs: Mapping[SolverId, SolverRun],
) -> ChapmanFlowResult:
    """Apply Chapman gates in constitutional order and withhold unsafe ratios."""

    reasons: list[str] = []
    if not preflight_passed:
        return ChapmanFlowResult(False, (), ("preflight failed",))

    # This raises before admission if any requested subject is unavailable.
    require_requested_solvers(requested_solvers, adapters)
    for solver in requested_solvers:
        assessment = chemistry.get(solver)
        if assessment is None:
            reasons.append(f"{solver.value}: missing chemistry admission evidence")
        elif not assessment.eligible:
            reasons.extend(f"{solver.value}: {reason}" for reason in assessment.reasons)
    if reasons:
        return ChapmanFlowResult(False, (), tuple(reasons))

    if not reference.qualified:
        return ChapmanFlowResult(False, (), ("independent reference is unqualified",))

    eligible_runs: list[SolverRun] = []
    for solver in requested_solvers:
        frozen = frozen_configurations.get(solver)
        accuracy = trajectory_accuracy.get(solver)
        run = runs.get(solver)
        if frozen is None:
            reasons.append(f"{solver.value}: no frozen calibration configuration")
            continue
        if accuracy is None or not accuracy.eligible:
            reasons.append(f"{solver.value}: trajectory accuracy is ineligible")
            continue
        if run is None or run.status is not RunStatus.SUCCESS:
            reasons.append(f"{solver.value}: no successful retained native run")
            continue
        if run.configuration.sha256 != frozen.configuration_sha256:
            reasons.append(f"{solver.value}: measurement configuration differs from calibration")
            continue
        eligible_runs.append(run)

    eligible = not reasons and len(eligible_runs) == len(requested_solvers)
    return ChapmanFlowResult(eligible, tuple(eligible_runs) if eligible else (), tuple(reasons))


def assess_ts1_flow(
    *,
    requested_solvers: tuple[SolverId, ...],
    **flow_evidence: Any,
) -> Ts1FlowResult:
    """Enforce the mandatory MICM/MKPP TS1 scope and derive no KPP placeholder."""

    required = {SolverId.MICM, SolverId.MKPP}
    if set(requested_solvers) != required or len(requested_solvers) != 2:
        raise ValueError("TS1 requires exactly MICM and MKPP; KPP is forbidden until admitted")
    scientific = assess_chapman_flow(
        requested_solvers=requested_solvers,
        **flow_evidence,
    )
    results = [
        {
            "solver_id": solver.value,
            "status": "eligible" if scientific.eligible else "ineligible",
            "throughput": None,
        }
        for solver in requested_solvers
    ]
    comparisons = [
        {
            "baseline_solver_id": SolverId.MICM.value,
            "candidate_solver_id": SolverId.MKPP.value,
            "status": "eligible" if scientific.eligible else "withheld",
            "median_ratio": None,
        }
    ]
    report: Mapping[str, Any] = {
        "mechanism_id": "ts1",
        "required_solvers": [solver.value for solver in requested_solvers],
        "results": results,
        "comparisons": comparisons,
        "claims": ["TS1 MICM/MKPP two-way comparison"],
        "diagnostics": list(scientific.reasons),
    }
    validate_ts1_report(report)
    return Ts1FlowResult(scientific=scientific, report=report)


def invoke_json_runner(
    prepared: PreparedAdapterRun,
    solver_id: SolverId,
    *,
    timeout_seconds: float,
) -> Mapping[str, Any]:
    """Invoke one prepared runner and return its validated single JSON result.

    Process startup belongs to adapter/lifecycle evidence, never the primary solve
    timing. Runner stdout is reserved for exactly one JSON document; stderr is
    retained only as a diagnostic and cannot replace structured evidence.
    """

    if timeout_seconds <= 0:
        raise ValueError("timeout_seconds must be positive")
    if not prepared.command:
        raise NativeRunnerError(solver_id, "has an empty command")

    environment = os.environ.copy()
    environment.update(dict(prepared.environment))
    try:
        completed = subprocess.run(
            prepared.command,
            cwd=prepared.working_directory,
            env=environment,
            capture_output=True,
            text=True,
            timeout=timeout_seconds,
            check=False,
        )
    except subprocess.TimeoutExpired as exc:
        raise NativeRunnerError(solver_id, f"timed out after {timeout_seconds:g} seconds") from exc
    except OSError as exc:
        raise NativeRunnerError(solver_id, f"could not start: {exc}") from exc

    if completed.returncode != 0:
        raise NativeRunnerError(
            solver_id,
            f"exited with code {completed.returncode}",
            stderr=completed.stderr,
        )

    output = completed.stdout.strip()
    if not output:
        raise NativeRunnerError(solver_id, "returned no JSON result", stderr=completed.stderr)
    try:
        result = json.loads(output)
    except json.JSONDecodeError as exc:
        raise NativeRunnerError(
            solver_id,
            "did not return exactly one valid JSON document",
            stderr=completed.stderr,
        ) from exc
    if not isinstance(result, dict):
        raise NativeRunnerError(solver_id, "JSON result must be an object", stderr=completed.stderr)
    try:
        validate_runner_result(result)
    except SchemaValidationError as exc:
        raise NativeRunnerError(
            solver_id,
            f"returned schema-invalid JSON: {exc}",
            stderr=completed.stderr,
        ) from exc

    observed_solver = result["solver"]["id"]
    if observed_solver != solver_id.value:
        raise NativeRunnerError(
            solver_id,
            f"identity mismatch: runner reported '{observed_solver}'",
            stderr=completed.stderr,
        )
    return result


__all__ = [
    "ChapmanFlowResult",
    "NativeRunnerError",
    "Ts1FlowResult",
    "assess_chapman_flow",
    "assess_ts1_flow",
    "invoke_json_runner",
    "require_requested_solvers",
]
