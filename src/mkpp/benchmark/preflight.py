"""Constitutional preflight gates for governed solver comparisons."""

from __future__ import annotations

import hashlib
import re
from collections.abc import Callable, Iterable
from dataclasses import dataclass
from enum import IntEnum, StrEnum
from pathlib import Path

_SHA256_PATTERN = re.compile(r"^[0-9a-f]{64}$")


class ExitCode(IntEnum):
    """Public CLI exit codes defined by the solver-comparison contract."""

    SUCCESS = 0
    INPUT = 2
    ENVIRONMENT = 3
    SCIENCE = 4
    RUNTIME = 5


class GateStage(StrEnum):
    """Mandatory NCO EE2 execution order."""

    ENVIRONMENT = "environment"
    STATIC = "static"
    TEST = "test"
    POLICY = "policy"
    BUILD = "build"


_GATE_ORDER = {
    GateStage.ENVIRONMENT: 0,
    GateStage.STATIC: 1,
    GateStage.TEST: 2,
    GateStage.POLICY: 3,
    GateStage.BUILD: 4,
}


class FailureKind(StrEnum):
    INPUT = "input"
    ENVIRONMENT = "environment"
    SCIENCE = "science"
    RUNTIME = "runtime"


_EXIT_CODES = {
    FailureKind.INPUT: ExitCode.INPUT,
    FailureKind.ENVIRONMENT: ExitCode.ENVIRONMENT,
    FailureKind.SCIENCE: ExitCode.SCIENCE,
    FailureKind.RUNTIME: ExitCode.RUNTIME,
}


class PreflightError(RuntimeError):
    """A fatal, user-actionable preflight failure."""

    def __init__(self, message: str, *, kind: FailureKind = FailureKind.INPUT) -> None:
        rendered = message if message.startswith("FATAL ERROR:") else f"FATAL ERROR: {message}"
        super().__init__(rendered)
        self.kind = kind
        self.exit_code = _EXIT_CODES[kind]


@dataclass(frozen=True, slots=True)
class PreflightGate:
    """One named validation action in the mandatory gate sequence."""

    name: str
    stage: GateStage
    check: Callable[[], None]


def exit_code_for(error: BaseException) -> ExitCode:
    """Map a governed failure to its stable CLI exit code."""

    if isinstance(error, PreflightError):
        return error.exit_code
    return ExitCode.RUNTIME


def run_preflight_gates(gates: Iterable[PreflightGate]) -> None:
    """Execute gates in constitutional order and stop on the first failure."""

    ordered = sorted(gates, key=lambda gate: _GATE_ORDER[gate.stage])
    for gate in ordered:
        try:
            gate.check()
        except PreflightError:
            raise
        except Exception as exc:
            kind = FailureKind.ENVIRONMENT if gate.stage is GateStage.ENVIRONMENT else FailureKind.RUNTIME
            raise PreflightError(f"{gate.stage.value} gate '{gate.name}' failed: {exc}", kind=kind) from exc


def resolve_relative_asset(root: Path, relative_path: str) -> Path:
    """Resolve an existing asset while preventing traversal and symlink escape."""

    root = Path(root).resolve()
    candidate_text = str(relative_path)
    candidate = Path(candidate_text)
    if candidate.is_absolute() or candidate_text.startswith("~") or ".." in candidate.parts:
        raise PreflightError(f"unsafe asset path '{candidate_text}'")

    resolved = (root / candidate).resolve()
    if not resolved.is_relative_to(root):
        raise PreflightError(f"asset path '{candidate_text}' resolves outside declared root")
    if not resolved.is_file():
        raise PreflightError(f"asset path '{candidate_text}' does not identify an existing file")
    return resolved


def verify_asset_hash(path: Path, expected_sha256: str) -> str:
    """Verify an asset's canonical lowercase SHA-256 digest."""

    path = Path(path)
    if not _SHA256_PATTERN.fullmatch(expected_sha256):
        raise PreflightError("expected sha256 must contain exactly 64 lowercase hexadecimal characters")
    if not path.is_file():
        raise PreflightError(f"asset path '{path}' does not identify an existing file")

    digest = hashlib.sha256()
    try:
        with path.open("rb") as stream:
            for chunk in iter(lambda: stream.read(1024 * 1024), b""):
                digest.update(chunk)
    except OSError as exc:
        raise PreflightError(f"cannot read asset path '{path}': {exc}") from exc

    observed = digest.hexdigest()
    if observed != expected_sha256:
        raise PreflightError(f"sha256 mismatch for asset '{path}': expected {expected_sha256}, observed {observed}")
    return observed
