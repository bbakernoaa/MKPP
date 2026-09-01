"""MKPP native runner binding."""

from mkpp.benchmark.adapters._native import NativeExecutableAdapter
from mkpp.benchmark.models import SolverId


class MkppAdapter(NativeExecutableAdapter):
    """Adapter that accepts evidence only from the MKPP executable."""

    def __init__(self, **kwargs: object) -> None:
        super().__init__(solver_id=SolverId.MKPP, **kwargs)  # type: ignore[arg-type]


__all__ = ["MkppAdapter"]
