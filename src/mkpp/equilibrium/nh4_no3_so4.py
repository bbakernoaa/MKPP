"""NH4/NO3/SO4 analytical equilibrium model (ISORROPIA-Lite).

Provides smooth, C1-continuous partition expressions for the
ammonium-nitrate-sulfate thermodynamic system using algebraic sigmoid
regime blending. All expressions are SymPy primitives suitable
for symbolic differentiation in the unified Jacobian.
"""

from __future__ import annotations

import sympy as sp

from mkpp.equilibrium.base import EquilibriumModel

# Gas constant [J/(mol·K)]
_R = 8.314

# Reference temperature [K]
_TREF = 298.15

# Van't Hoff parameters: (A at Tref, dH in J/mol)
_VANTHOFF = {
    "Kp_NH4NO3": (4.39e-17, -74735.0),
    "Kp_NH4HSO4": (1.086e-2, -40000.0),
    "Kp_NH42SO4": (1.817e-25, -160000.0),
}


class NH4NO3SO4Model(EquilibriumModel):
    """Analytical equilibrium model for the NH4/NO3/SO4 system.

    Implements ISORROPIA-Lite style partitioning using smooth
    sigmoid regime blending based on the sulfate ratio
    R = C_reduced_nitrogen_total / C_sulfate_total.

    Three regimes:
      - R < 1  (sulfate-rich): nitrogen bound primarily as NH4HSO4
      - 1 <= R < 2 (ammonia-rich): sulfate saturated as (NH4)2SO4
      - R >= 2 (ammonia-rich with nitrate): NH4NO3 formation

    Transitions between regimes are blended with algebraic sigmoid functions
    to ensure C1-continuity.
    """

    def species_map(self) -> dict[str, list[str]]:
        """Return element-to-species mapping.

        Returns
        -------
        dict[str, list[str]]
            Element name -> list of participating species
            (gas-phase first, then aerosol-phase species).

        Notes
        -----
        The "sulfate" element is included so that the total C_S symbol is
        available for computing the sulfate ratio R = C_N / C_S used in
        regime blending. However, SO2 and SO4 are kinetically controlled
        (SO2 -> SO4 via oxidation) and are NOT relaxed toward equilibrium
        partition expressions. Only reduced_nitrogen and oxidized_nitrogen
        species participate in thermodynamic equilibrium partitioning.
        """
        return {
            "reduced_nitrogen": ["NH3", "NH4a"],
            "oxidized_nitrogen": ["HNO3", "NO3an1", "NO3an2", "NO3an3"],
            "sulfate": ["SO2", "SO4"],
        }

    def equilibrium_constants(self, T: sp.Symbol) -> dict[str, sp.Expr]:
        """Return van't Hoff equilibrium constant expressions.

        Keq(T) = A * exp(-dH/R * (1/T - 1/Tref))

        Parameters
        ----------
        T : sp.Symbol
            Temperature symbol (Kelvin).

        Returns
        -------
        dict[str, sp.Expr]
            Equilibrium constant name -> SymPy expression.
        """
        constants: dict[str, sp.Expr] = {}
        for name, (A, dH) in _VANTHOFF.items():
            constants[name] = sp.Float(A) * sp.exp(sp.Float(-dH / _R) * (1 / T - sp.Float(1 / _TREF)))
        return constants

    def partition_expressions(
        self,
        totals: dict[str, sp.Symbol],
        T: sp.Symbol,
        RH: sp.Symbol,
        blending: str = "sigmoid",
        width: float = 0.05,
    ) -> dict[str, sp.Expr]:
        """Produce smooth partition expressions for each species.

        Uses sulfate-ratio-based regime blending with algebraic sigmoid transitions.
        All expressions use only SymPy primitives — no Piecewise, Abs, Max, or Min.

        Conservation is enforced by construction: within each element,
        one species is computed as (total - sum of others).

        Parameters
        ----------
        totals : dict[str, sp.Symbol]
            Element name -> SymPy symbol for total concentration.
        T : sp.Symbol
            Temperature symbol (Kelvin).
        RH : sp.Symbol
            Relative humidity symbol (fraction, 0-1).
        blending : str
            Blending function type ("sigmoid", default "sigmoid").
        width : float
            Transition width in sulfate-ratio units (default 0.05).

        Returns
        -------
        dict[str, sp.Expr]
            Species name -> SymPy expression for concentration.
        """
        C_N = totals["reduced_nitrogen"]
        C_Ox = totals["oxidized_nitrogen"]
        C_S = totals["sulfate"]

        # Equilibrium constants
        Keq = self.equilibrium_constants(T)
        Kp_NH4NO3 = Keq["Kp_NH4NO3"]

        # ----------------------------------------------------------
        # Sulfate ratio: R = C_reduced_nitrogen / C_sulfate
        # Add a small epsilon to avoid singularity at C_S = 0.
        # ----------------------------------------------------------
        _eps = sp.Float(1e-30)
        R = C_N / (C_S + _eps)

        # ----------------------------------------------------------
        # Regime blending weights using algebraic sigmoid:
        # w1 = weight for regime "R >= 1" (transition at R=1)
        # w2 = weight for regime "R >= 2" (transition at R=2)
        #
        # w_i(R) = 0.5 * (1 + u / sqrt(1 + u^2)), where u = (R - R_0) / width
        # Smooth C^inf algebraic blending: avoids transcendental tanh,
        # yielding fast SymPy differentiation, hardware-accelerated C++
        # evaluation, and compact expression trees.
        # ----------------------------------------------------------
        inv_width = sp.Float(1.0 / width)
        u1 = (R - 1) * inv_width
        u2 = (R - 2) * inv_width

        w1 = sp.Rational(1, 2) * (1 + u1 / sp.sqrt(1 + u1**2))
        w2 = sp.Rational(1, 2) * (1 + u2 / sp.sqrt(1 + u2**2))

        # ----------------------------------------------------------
        # REGIME definitions for reduced nitrogen:
        #
        # R < 2 (regimes 1 and 2): All nitrogen is captured by sulfate
        #   - R < 1: sulfate-rich, NH4 forms NH4HSO4
        #   - 1 <= R < 2: transition, NH4 forms mix of NH4HSO4/(NH4)2SO4
        #   In both sub-regimes: NH4a = C_N, NH3 ~ 0
        #
        # R >= 2 (regime 3): Ammonia-rich with nitrate
        #   - Sulfate fully neutralized as (NH4)2SO4: uses 2*C_S of NH4
        #   - Excess NH3 available for NH4NO3 formation or gas phase
        #
        # The only transition that affects gas/aerosol partitioning of
        # reduced N is at R=2. The R=1 boundary affects internal aerosol
        # speciation (not modeled here) and nitrate formation.
        # ----------------------------------------------------------

        # Regime for R < 2 (sulfate-dominated): all N goes to aerosol
        # NH3_low = 0, NH4a_low = C_N (implicit via blending below)

        # ----------------------------------------------------------
        # Regime for R >= 2: Ammonia-rich with nitrate
        # Sulfate fully neutralized: NH4_from_sulfate = 2*C_S
        # Excess NH3 can form NH4NO3: NH3(g) + HNO3(g) <-> NH4NO3(s)
        #
        # Available NH3 for nitrate formation: excess = C_N - 2*C_S
        # Available HNO3: C_Ox (total oxidized nitrogen)
        #
        # At equilibrium: Kp = [NH3_gas] * [HNO3_gas]
        # Let X = moles condensed as NH4NO3:
        #   NH3_gas = excess - X,  HNO3_gas = C_Ox - X
        #   Kp = (excess - X)(C_Ox - X)
        #
        # Solving the quadratic:
        #   X = 0.5 * [(excess + C_Ox) - sqrt((excess - C_Ox)^2 + 4*Kp)]
        #
        # This is:
        #   - Naturally bounded: X <= min(excess, C_Ox)
        #   - C1-continuous: discriminant > 0 always (since Kp > 0)
        #   - Uses only sp.sqrt (no Piecewise/Abs/Max/Min)
        # ----------------------------------------------------------
        excess_NH3 = C_N - 2 * C_S

        # Discriminant is always positive since 4*Kp > 0
        discriminant = (excess_NH3 - C_Ox) ** 2 + 4 * Kp_NH4NO3
        X_raw = sp.Rational(1, 2) * ((excess_NH3 + C_Ox) - sp.sqrt(discriminant))

        # Smooth non-negative floor: X_raw can be negative when
        # excess_NH3 < 0 (i.e. R < 2). Apply C1-continuous soft-plus:
        #   smooth_pos(x) = 0.5*(x + sqrt(x^2 + eps^2))
        # This approaches max(x, 0) as eps -> 0, stays differentiable.
        _smooth_eps = sp.Float(1e-20)
        NH4_from_nitrate = sp.Rational(1, 2) * (X_raw + sp.sqrt(X_raw**2 + _smooth_eps))

        # Gas-phase NH3 in the high-R regime:
        # NH3_high = excess_NH3 - NH4_from_nitrate
        # Apply smooth_pos to guarantee non-negativity during blending.
        NH3_high_raw = excess_NH3 - NH4_from_nitrate
        NH3_high = sp.Rational(1, 2) * (NH3_high_raw + sp.sqrt(NH3_high_raw**2 + _smooth_eps))

        # ----------------------------------------------------------
        # Blend regimes for reduced nitrogen
        #
        # Rather than blending NH4a (which can overshoot C_N), we
        # blend the gas-phase NH3 and derive NH4a by conservation:
        #   NH3_low = 0 (sulfate-dominated: all N in aerosol)
        #   NH3_high = excess - X (ammonia-rich: leftover in gas)
        #   NH3 = (1 - w2)*0 + w2*NH3_high = w2 * NH3_high
        #   NH4a = C_N - NH3  (conservation)
        #
        # This ensures NH3 >= 0 and NH4a <= C_N at all times.
        # ----------------------------------------------------------
        NH3_expr = w2 * NH3_high

        # Conservation: NH4a = C_N - NH3
        NH4a_expr = C_N - NH3_expr

        # ----------------------------------------------------------
        # Oxidized nitrogen partitioning
        # ----------------------------------------------------------
        # Nitrate aerosol formation requires:
        #   1. R >= 1 (w1): sulfate sufficiently neutralized to allow
        #      nitrate competition for NH4
        #   2. R >= 2 (w2): excess NH3 available for NH4NO3 formation
        #
        # NH4_from_nitrate (= X from the quadratic) gives the moles
        # of NH4NO3 condensed. Each mol NH4NO3 removes one mol NO3
        # from gas phase. We gate by w1*w2 to smoothly activate:
        # - w1 gates whether the aerosol is neutralized enough
        # - w2 gates whether excess NH3 is available
        # ----------------------------------------------------------
        total_NO3_aerosol = w1 * w2 * NH4_from_nitrate

        # Equal distribution across 3 aerosol nitrate bins
        NO3an1_expr = total_NO3_aerosol * sp.Rational(1, 3)
        NO3an2_expr = total_NO3_aerosol * sp.Rational(1, 3)
        NO3an3_expr = total_NO3_aerosol * sp.Rational(1, 3)

        # Conservation: HNO3 = C_Ox - (NO3an1 + NO3an2 + NO3an3)
        HNO3_expr = C_Ox - total_NO3_aerosol

        # ----------------------------------------------------------
        # Sulfate partitioning — NOT included in equilibrium expressions
        # ----------------------------------------------------------
        # SO2 and SO4 are kinetically controlled in GOCART: SO2 is
        # oxidized to SO4 via kinetic pathways (OH, H2O2, O3).
        # Their partitioning is NOT thermodynamic equilibrium.
        # Including them here would cause the relaxation term
        # tau_eq_inv * (eq_expr - C_species) to erroneously drive
        # SO2 to zero (since eq_expr=0) or transfer mass from SO2
        # to SO4 at the relaxation timescale, dominating the actual
        # kinetic oxidation pathways.
        #
        # The sulfate element is still listed in species_map() so
        # that the total C_S symbol is available for computing the
        # sulfate ratio R = C_N / C_S used in regime blending.
        # ----------------------------------------------------------

        return {
            "NH3": NH3_expr,
            "NH4a": NH4a_expr,
            "HNO3": HNO3_expr,
            "NO3an1": NO3an1_expr,
            "NO3an2": NO3an2_expr,
            "NO3an3": NO3an3_expr,
        }
