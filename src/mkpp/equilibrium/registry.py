"""Equilibrium model registry.

Provides lookup of equilibrium model implementations by system name.
"""

from __future__ import annotations

from mkpp.equilibrium.base import EquilibriumModel
from mkpp.model import CompilationError

# Supported equilibrium system names mapped to their module and class.
_SUPPORTED_SYSTEMS: dict[str, tuple[str, str]] = {
    "NH4_NO3_SO4": ("mkpp.equilibrium.nh4_no3_so4", "NH4NO3SO4Model"),
}


def get_model(system: str) -> EquilibriumModel:
    """Look up and return an equilibrium model instance by system name.

    Parameters
    ----------
    system : str
        Equilibrium system identifier (e.g. "NH4_NO3_SO4").

    Returns
    -------
    EquilibriumModel
        An instance of the corresponding equilibrium model.

    Raises
    ------
    CompilationError
        If ``system`` is not a supported equilibrium system.
    """
    if system not in _SUPPORTED_SYSTEMS:
        supported = ", ".join(sorted(_SUPPORTED_SYSTEMS.keys()))
        raise CompilationError(
            stage="validation",
            message=(f"Unknown equilibrium system '{system}'. Supported: {supported}"),
        )

    module_path, class_name = _SUPPORTED_SYSTEMS[system]

    # Lazy import to avoid circular dependencies and allow the model
    # module (nh4_no3_so4.py) to be created in a later task.
    import importlib

    module = importlib.import_module(module_path)
    model_cls = getattr(module, class_name)
    return model_cls()
