"""MICM native runner binding."""

from mkpp.benchmark.adapters._native import NativeExecutableAdapter
from mkpp.benchmark.models import SolverId


class MicmAdapter(NativeExecutableAdapter):
    """Adapter that accepts evidence only from the MICM executable."""

    def __init__(self, **kwargs: object) -> None:
        super().__init__(solver_id=SolverId.MICM, **kwargs)  # type: ignore[arg-type]


__all__ = ["MicmAdapter"]
