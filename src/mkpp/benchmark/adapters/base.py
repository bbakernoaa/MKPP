"""Common lifecycle contract for native MICM, KPP, and MKPP adapters."""

from __future__ import annotations

from dataclasses import dataclass
from typing import Protocol, runtime_checkable

from mkpp.benchmark.models import SolverId, SolverRun, TimingBoundary


@dataclass(frozen=True, slots=True)
class AdapterProbe:
    """Identity observed from a native runner before campaign execution."""

    solver_id: SolverId
    version: str
    revision: str
    executable_fingerprint: str
    backend: str
    capabilities: tuple[str, ...] = ()


@dataclass(frozen=True, slots=True)
class AdapterRunRequest:
    """Resolved identifiers and ordering metadata for one native run."""

    campaign_id: str
    run_id: str
    block_id: int
    repetition: int
    order_position: int
    manifest_id: str
    scenario_id: str
    configuration_id: str
    timing_boundary: TimingBoundary


@dataclass(frozen=True, slots=True)
class PreparedAdapterRun:
    """A validated native invocation ready to enter the measured lifecycle."""

    request: AdapterRunRequest
    command: tuple[str, ...]
    working_directory: str
    environment: tuple[tuple[str, str], ...] = ()
    input_sha256: str = ""


class AdapterError(RuntimeError):
    """Base class for deterministic, actionable adapter failures."""

    phase = "adapter"

    def __init__(
        self,
        solver_id: SolverId,
        diagnostic: str,
        *,
        context: tuple[str, ...] = (),
    ) -> None:
        if not diagnostic.strip():
            raise ValueError("adapter error diagnostic must not be empty")
        self.solver_id = solver_id
        self.diagnostic = diagnostic
        self.context = context
        context_text = f" ({'; '.join(context)})" if context else ""
        super().__init__(f"FATAL ERROR: {solver_id.value} adapter {self.phase} failed: " f"{diagnostic}{context_text}")


class ProbeError(AdapterError):
    """The native runner identity or availability could not be established."""

    phase = "probe"


class SupportError(AdapterError):
    """The adapter cannot faithfully execute the requested scientific case."""

    phase = "support validation"


class PreparationError(AdapterError):
    """Validated native inputs or build artifacts could not be prepared."""

    phase = "preparation"


class ExecutionError(AdapterError):
    """The native runner failed or returned unusable result evidence."""

    phase = "execution"


@runtime_checkable
class AdapterProtocol(Protocol):
    """Required lifecycle implemented by each real native solver adapter.

    Implementations must not substitute another solver. Each failure phase raises
    its corresponding :class:`AdapterError` subtype so orchestration can retain
    an actionable ineligible result and stop the affected run immediately.
    """

    solver_id: SolverId

    def probe(self) -> AdapterProbe:
        """Return verified native solver, executable, and backend identity."""
        ...

    def validate_support(self, request: AdapterRunRequest) -> None:
        """Fail unless this adapter supports every resolved request dimension."""
        ...

    def prepare(self, request: AdapterRunRequest) -> PreparedAdapterRun:
        """Resolve immutable inputs and native invocation outside timing."""
        ...

    def run(self, prepared: PreparedAdapterRun) -> SolverRun:
        """Execute the prepared native runner and return retained raw evidence."""
        ...


__all__ = [
    "AdapterError",
    "AdapterProbe",
    "AdapterProtocol",
    "AdapterRunRequest",
    "ExecutionError",
    "PreparationError",
    "PreparedAdapterRun",
    "ProbeError",
    "SupportError",
]
