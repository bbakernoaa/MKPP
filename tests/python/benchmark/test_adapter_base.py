"""Unit tests for the native solver adapter lifecycle contract."""

from dataclasses import FrozenInstanceError

import pytest

from mkpp.benchmark.adapters.base import (
    AdapterError,
    AdapterProbe,
    AdapterProtocol,
    AdapterRunRequest,
    ExecutionError,
    PreparationError,
    PreparedAdapterRun,
    ProbeError,
    SupportError,
)
from mkpp.benchmark.models import SolverId, TimingBoundary


class CompleteAdapter:
    solver_id = SolverId.MKPP

    def probe(self) -> AdapterProbe:
        return AdapterProbe(SolverId.MKPP, "1.0", "abc", "binary", "cpu")

    def validate_support(self, request: AdapterRunRequest) -> None:
        del request

    def prepare(self, request: AdapterRunRequest) -> PreparedAdapterRun:
        return PreparedAdapterRun(request=request, command=("mkpp-runner",), working_directory="build")

    def run(self, prepared: PreparedAdapterRun):
        del prepared
        return None


def test_complete_adapter_satisfies_runtime_protocol() -> None:
    assert isinstance(CompleteAdapter(), AdapterProtocol)


def test_incomplete_adapter_does_not_satisfy_runtime_protocol() -> None:
    class IncompleteAdapter:
        solver_id = SolverId.KPP

        def probe(self) -> AdapterProbe:
            raise NotImplementedError

    assert not isinstance(IncompleteAdapter(), AdapterProtocol)


def test_probe_and_prepared_run_are_immutable() -> None:
    probe = AdapterProbe(SolverId.MICM, "1.0", "abc", "binary", "cpu")
    request = AdapterRunRequest(
        campaign_id="campaign",
        run_id="run",
        block_id=0,
        repetition=0,
        order_position=0,
        manifest_id="chapman",
        scenario_id="measurement",
        configuration_id="micm-frozen",
        timing_boundary=TimingBoundary.STEADY_STATE_SOLVE,
    )
    prepared = PreparedAdapterRun(request, ("micm-runner", "--json"), "build")

    with pytest.raises(FrozenInstanceError):
        probe.version = "changed"  # type: ignore[misc]
    with pytest.raises(FrozenInstanceError):
        prepared.command = ("other",)  # type: ignore[misc]


@pytest.mark.parametrize("error_type", [ProbeError, SupportError, PreparationError, ExecutionError])
def test_adapter_errors_are_typed_and_fail_fast(error_type: type[AdapterError]) -> None:
    error = error_type(SolverId.KPP, "actionable diagnostic", context=("mechanism=chapman",))

    assert isinstance(error, AdapterError)
    assert str(error).startswith("FATAL ERROR:")
    assert "kpp" in str(error)
    assert "actionable diagnostic" in str(error)
    assert error.solver_id is SolverId.KPP
    assert error.context == ("mechanism=chapman",)


def test_adapter_error_rejects_empty_diagnostic() -> None:
    with pytest.raises(ValueError, match="diagnostic"):
        ExecutionError(SolverId.MKPP, "")
