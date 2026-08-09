"""Abstract base class for equilibrium models."""

from abc import ABC, abstractmethod

import sympy as sp


class EquilibriumModel(ABC):
    """Base interface for analytical equilibrium partitioning models.

    Subclasses provide SymPy expressions for gas/aerosol partitioning
    as functions of total species concentrations, temperature, and
    relative humidity. The expressions must be C1-continuous and
    symbolically differentiable for inclusion in the unified Jacobian.
    """

    @abstractmethod
    def species_map(self) -> dict[str, list[str]]:
        """Map element -> [gas, aerosol] species names.

        Returns
        -------
        dict[str, list[str]]
            Mapping from conserved element name (e.g. "reduced_nitrogen")
            to the list of species participating in that element's
            equilibrium (gas-phase first, then aerosol-phase species).
        """

    @abstractmethod
    def partition_expressions(
        self,
        totals: dict[str, sp.Symbol],
        T: sp.Symbol,
        RH: sp.Symbol,
        blending: str = "sigmoid",
        width: float = 0.05,
    ) -> dict[str, sp.Expr]:
        """Return SymPy expressions for each partitioned species.

        Parameters
        ----------
        totals : dict[str, sp.Symbol]
            Mapping from element name to the SymPy symbol representing
            the total concentration for that element.
        T : sp.Symbol
            Temperature symbol (Kelvin).
        RH : sp.Symbol
            Relative humidity symbol (fraction, 0-1).
        blending : str
            Regime blending function type ("sigmoid").
        width : float
            Transition width for regime blending (in ratio units).

        Returns
        -------
        dict[str, sp.Expr]
            Mapping from species name to SymPy expression giving that
            species' concentration as a function of totals, T, and RH.
        """

    @abstractmethod
    def equilibrium_constants(self, T: sp.Symbol) -> dict[str, sp.Expr]:
        """Return temperature-dependent equilibrium constants as SymPy expressions.

        Parameters
        ----------
        T : sp.Symbol
            Temperature symbol (Kelvin).

        Returns
        -------
        dict[str, sp.Expr]
            Mapping from equilibrium constant name (e.g. "Kp_NH4NO3")
            to its van't Hoff SymPy expression as a function of T.
        """
