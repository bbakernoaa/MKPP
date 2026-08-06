"""Equilibrium model subpackage.

Provides analytical equilibrium partitioning models for inline
thermodynamic coupling in the unified Jacobian.
"""

from mkpp.equilibrium.base import EquilibriumModel
from mkpp.equilibrium.registry import get_model

__all__ = ["EquilibriumModel", "get_model"]
