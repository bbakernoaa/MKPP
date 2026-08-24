"""KPP native runner binding."""

from mkpp.benchmark.adapters._native import NativeExecutableAdapter
from mkpp.benchmark.models import SolverId


class KppAdapter(NativeExecutableAdapter):
    """Adapter that accepts evidence only from the KPP executable."""

    def __init__(self, **kwargs: object) -> None:
        super().__init__(solver_id=SolverId.KPP, **kwargs)  # type: ignore[arg-type]


__all__ = ["KppAdapter"]
