"""Tests for build-time differentiability verification of equilibrium expressions.

Validates: Requirements 6.3, 6.4

Verifies that:
- The standard NH4/NO3/SO4 model passes differentiability verification
- Non-differentiable expressions (Piecewise, Abs) are caught at build time
- The prepare_adjoint_and_tlm function rejects equilibrium without continuous_transition
"""

import pytest
import sympy as sp
from mkpp.lowering import prepare_adjoint_and_tlm, prepare_unified_jacobian
from mkpp.model import (
    AerosolRepresentation,
    EquilibriumDefinition,
    MechanismDefinition,
    PhaseMode,
    SpeciesDefinition,
)


def _standard_eq_mechanism() -> MechanismDefinition:
    """Build the standard NH4/NO3/SO4 equilibrium mechanism for testing."""
    return MechanismDefinition(
        name="eq_differentiability_test",
        description="",
        aerosol_representation=AerosolRepresentation.BULK,
        species=[
            SpeciesDefinition(name="NH3", phase=PhaseMode.GAS),
            SpeciesDefinition(name="NH4a", phase=PhaseMode.AEROSOL),
            SpeciesDefinition(name="HNO3", phase=PhaseMode.GAS),
            SpeciesDefinition(name="NO3an1", phase=PhaseMode.AEROSOL),
            SpeciesDefinition(name="NO3an2", phase=PhaseMode.AEROSOL),
            SpeciesDefinition(name="NO3an3", phase=PhaseMode.AEROSOL),
            SpeciesDefinition(name="SO2", phase=PhaseMode.GAS),
            SpeciesDefinition(name="SO4", phase=PhaseMode.AEROSOL),
        ],
        phases=[],
        reactions=[],
        equilibrium_reactions=[
            EquilibriumDefinition(
                system="NH4_NO3_SO4",
                total_species={
                    "reduced_nitrogen": ["NH3", "NH4a"],
                    "oxidized_nitrogen": ["HNO3", "NO3an1", "NO3an2", "NO3an3"],
                    "sulfate": ["SO2", "SO4"],
                },
                continuous_transition=True,
            )
        ],
    )


class TestDifferentiabilityVerification:
    """Tests for build-time differentiability checks in the lowering pass."""

    def test_standard_model_passes_verification(self):
        """The standard NH4/NO3/SO4 model uses smooth sigmoid blending
        and should pass all differentiability checks without raising."""
        mech = _standard_eq_mechanism()
        # Should not raise - all expressions are smooth (tanh-based)
        result = prepare_unified_jacobian(mech)

        # Verify the result contains equilibrium data (verification passed)
        assert "equilibrium_results" in result
        assert len(result["equilibrium_results"]) == 1

    def test_equilibrium_expressions_have_no_derivative_wrappers(self):
        """Verify that all partition expressions can be differentiated
        without leaving unevaluated Derivative wrappers."""
        mech = _standard_eq_mechanism()
        result = prepare_unified_jacobian(mech)

        eq_result = result["equilibrium_results"][0]
        species_symbols = {s.name: sp.Symbol(f"C_{s.name}", real=True, nonnegative=True) for s in mech.species}

        for sp_name, expr in eq_result.partition_exprs.items():
            for sym_name, sym in species_symbols.items():
                deriv = sp.diff(expr, sym)
                assert not deriv.has(sp.Derivative), (
                    f"Derivative of equilibrium expression for '{sp_name}' "
                    f"w.r.t. '{sym_name}' contains unevaluated Derivative wrapper: {deriv}"
                )

    def test_equilibrium_expressions_have_no_piecewise(self):
        """Verify that no partition expression derivatives contain Piecewise."""
        mech = _standard_eq_mechanism()
        result = prepare_unified_jacobian(mech)

        eq_result = result["equilibrium_results"][0]
        species_symbols = {s.name: sp.Symbol(f"C_{s.name}", real=True, nonnegative=True) for s in mech.species}

        for sp_name, expr in eq_result.partition_exprs.items():
            for sym_name, sym in species_symbols.items():
                deriv = sp.diff(expr, sym)
                assert not deriv.has(sp.Piecewise), (
                    f"Derivative of equilibrium expression for '{sp_name}' " f"w.r.t. '{sym_name}' contains Piecewise: {deriv}"
                )

    def test_equilibrium_expressions_have_no_abs(self):
        """Verify that no partition expression derivatives contain Abs."""
        mech = _standard_eq_mechanism()
        result = prepare_unified_jacobian(mech)

        eq_result = result["equilibrium_results"][0]
        species_symbols = {s.name: sp.Symbol(f"C_{s.name}", real=True, nonnegative=True) for s in mech.species}

        for sp_name, expr in eq_result.partition_exprs.items():
            for sym_name, sym in species_symbols.items():
                deriv = sp.diff(expr, sym)
                assert not deriv.has(sp.Abs), (
                    f"Derivative of equilibrium expression for '{sp_name}' " f"w.r.t. '{sym_name}' contains Abs: {deriv}"
                )


class TestAdjointTLMEquilibriumValidation:
    """Tests for prepare_adjoint_and_tlm equilibrium checks."""

    def test_continuous_transition_passes(self):
        """Equilibrium with continuous_transition=True should pass."""
        mech = _standard_eq_mechanism()
        result = prepare_adjoint_and_tlm(mech)
        assert result["adjoint_ready"] is True
        assert result["tlm_ready"] is True

    def test_discontinuous_equilibrium_rejected(self):
        """Equilibrium with continuous_transition=False should be rejected."""
        mech = MechanismDefinition(
            name="eq_discontinuous_test",
            description="",
            aerosol_representation=AerosolRepresentation.BULK,
            species=[
                SpeciesDefinition(name="NH3", phase=PhaseMode.GAS),
                SpeciesDefinition(name="NH4a", phase=PhaseMode.AEROSOL),
                SpeciesDefinition(name="HNO3", phase=PhaseMode.GAS),
                SpeciesDefinition(name="NO3an1", phase=PhaseMode.AEROSOL),
                SpeciesDefinition(name="NO3an2", phase=PhaseMode.AEROSOL),
                SpeciesDefinition(name="NO3an3", phase=PhaseMode.AEROSOL),
                SpeciesDefinition(name="SO2", phase=PhaseMode.GAS),
                SpeciesDefinition(name="SO4", phase=PhaseMode.AEROSOL),
            ],
            phases=[],
            reactions=[],
            equilibrium_reactions=[
                EquilibriumDefinition(
                    system="NH4_NO3_SO4",
                    total_species={
                        "reduced_nitrogen": ["NH3", "NH4a"],
                        "oxidized_nitrogen": ["HNO3", "NO3an1", "NO3an2", "NO3an3"],
                        "sulfate": ["SO2", "SO4"],
                    },
                    continuous_transition=False,
                )
            ],
        )

        with pytest.raises(ValueError, match="requires continuous_transition=True"):
            prepare_adjoint_and_tlm(mech)

    def test_no_equilibrium_passes(self):
        """Mechanism without equilibrium should pass adjoint/TLM checks."""
        mech = MechanismDefinition(
            name="no_eq_test",
            description="",
            aerosol_representation=AerosolRepresentation.BULK,
            species=[
                SpeciesDefinition(name="O3", phase=PhaseMode.GAS),
                SpeciesDefinition(name="NO2", phase=PhaseMode.GAS),
            ],
            phases=[],
            reactions=[],
            equilibrium_reactions=[],
        )
        result = prepare_adjoint_and_tlm(mech)
        assert result["adjoint_ready"] is True
        assert result["tlm_ready"] is True
