"""Backward compatibility tests for mechanisms without EQUILIBRIUM reactions.

Validates: Requirements 3.4, 11.1

Ensures that mechanisms with only kinetic reactions (no EQUILIBRIUM) produce
output IDENTICAL to the pre-equilibrium behavior:
- No RH symbol introduced
- No equilibrium_results key in output
- PHASE_CHANGE reactions still produce Rate_N symbols
- Jacobian is purely a function of kinetic rates
"""

from mkpp.lowering import prepare_unified_jacobian
from mkpp.model import (
    AerosolRepresentation,
    MechanismDefinition,
    PhaseMode,
    ReactionDefinition,
    SpeciesDefinition,
)


def _kinetic_only_mechanism() -> MechanismDefinition:
    """Build a mechanism with various kinetic reaction types but NO EQUILIBRIUM."""
    return MechanismDefinition(
        name="kinetic_only",
        description="Kinetic-only mechanism for backward compat testing",
        aerosol_representation=AerosolRepresentation.BULK,
        species=[
            SpeciesDefinition(name="O", phase=PhaseMode.GAS, elements={"O": 1}),
            SpeciesDefinition(name="O2", phase=PhaseMode.GAS, elements={"O": 2}),
            SpeciesDefinition(name="O3", phase=PhaseMode.GAS, elements={"O": 3}),
            SpeciesDefinition(name="M", phase=PhaseMode.GAS, elements={}),
        ],
        phases=[],
        reactions=[
            # PHOTOLYSIS
            ReactionDefinition(
                reaction_type="PHOTOLYSIS",
                reactants=["O2"],
                products=["O", "O"],
                rate_expression="",
                parameters={"A": "J1"},
                continuous_transition=True,
            ),
            # ARRHENIUS
            ReactionDefinition(
                reaction_type="ARRHENIUS",
                reactants=["O", "O2", "M"],
                products=["O3", "M"],
                rate_expression="",
                parameters={"A": "1.0", "B": "0.0", "C": "200.0"},
            ),
            # TROE
            ReactionDefinition(
                reaction_type="TROE",
                reactants=["O3", "O"],
                products=["O2", "O2"],
                rate_expression="",
                parameters={"k0": {"A": "1.0"}, "kinf": {"A": "2.0"}, "Fc": "0.6"},
            ),
        ],
        equilibrium_reactions=[],  # Explicitly empty
    )


def _mechanism_with_phase_change() -> MechanismDefinition:
    """Build a mechanism with PHASE_CHANGE reactions but NO EQUILIBRIUM."""
    return MechanismDefinition(
        name="phase_change_mech",
        description="Mechanism with PHASE_CHANGE for backward compat testing",
        aerosol_representation=AerosolRepresentation.BULK,
        species=[
            SpeciesDefinition(name="NH3", phase=PhaseMode.GAS, elements={"N": 1, "H": 3}),
            SpeciesDefinition(name="NH4a", phase=PhaseMode.AEROSOL, elements={"N": 1, "H": 4}),
            SpeciesDefinition(name="HNO3", phase=PhaseMode.GAS, elements={"N": 1, "O": 3, "H": 1}),
            SpeciesDefinition(name="NO3a", phase=PhaseMode.AEROSOL, elements={"N": 1, "O": 3}),
        ],
        phases=[],
        reactions=[
            # PHASE_CHANGE: NH3 -> NH4a (opaque rate)
            ReactionDefinition(
                reaction_type="PHASE_CHANGE",
                reactants=["NH3"],
                products=["NH4a"],
                rate_expression="",
                parameters={},
                continuous_transition=True,
            ),
            # PHASE_CHANGE: HNO3 -> NO3a (opaque rate)
            ReactionDefinition(
                reaction_type="PHASE_CHANGE",
                reactants=["HNO3"],
                products=["NO3a"],
                rate_expression="",
                parameters={},
                continuous_transition=True,
            ),
        ],
        equilibrium_reactions=[],  # Explicitly empty
    )


class TestKineticOnlyBackwardCompat:
    """Tests ensuring kinetic-only mechanisms are unaffected by equilibrium code."""

    def test_no_rh_symbol_in_f_total(self):
        """RH symbol must NOT appear in f_total for kinetic-only mechanisms."""
        mech = _kinetic_only_mechanism()
        result = prepare_unified_jacobian(mech)

        # Get all free symbols in f_total (which is f_implicit + f_explicit)
        f_total = result["f_implicit"] + result["f_explicit"]
        free_syms = f_total.free_symbols
        sym_names = {str(s) for s in free_syms}

        assert "RH" not in sym_names, f"RH symbol should not appear in kinetic-only f_total, " f"found symbols: {sym_names}"

    def test_no_rh_symbol_in_jacobian(self):
        """RH symbol must NOT appear in the Jacobian for kinetic-only mechanisms."""
        mech = _kinetic_only_mechanism()
        result = prepare_unified_jacobian(mech)

        J = result["jacobian_matrix"]
        free_syms = J.free_symbols
        sym_names = {str(s) for s in free_syms}

        assert "RH" not in sym_names, f"RH symbol should not appear in kinetic-only Jacobian, " f"found symbols: {sym_names}"

    def test_no_equilibrium_results_key(self):
        """Result dict must NOT contain 'equilibrium_results' key for kinetic-only mechanisms."""
        mech = _kinetic_only_mechanism()
        result = prepare_unified_jacobian(mech)

        assert result.get("equilibrium_results") is None, "kinetic-only mechanism should not produce 'equilibrium_results'"

    def test_no_rh_symbol_key(self):
        """Result dict must NOT contain 'rh_symbol' key for kinetic-only mechanisms."""
        mech = _kinetic_only_mechanism()
        result = prepare_unified_jacobian(mech)

        assert result.get("rh_symbol") is None, "kinetic-only mechanism should not produce 'rh_symbol'"

    def test_jacobian_shape_matches_species(self):
        """Jacobian must have shape (N, N) where N is number of species."""
        mech = _kinetic_only_mechanism()
        result = prepare_unified_jacobian(mech)

        N = len(mech.species)
        J = result["jacobian_matrix"]
        assert J.shape == (N, N), f"Expected ({N}, {N}), got {J.shape}"

    def test_kinetic_jacobian_contains_expected_symbols(self):
        """Verify kinetic-only Jacobian contains standard kinetic symbols (Temp, exp, etc.)."""
        mech = _kinetic_only_mechanism()
        result = prepare_unified_jacobian(mech)

        J = result["jacobian_matrix"]
        j_str = str(J)

        # Kinetic reactions produce Temp-dependent and photolysis-dependent entries
        assert "Temp" in j_str or "J_0" in j_str, "Kinetic Jacobian should reference standard kinetic symbols"


class TestPhaseChangeBackwardCompat:
    """Tests ensuring PHASE_CHANGE reactions still produce Rate_N symbols."""

    def test_phase_change_produces_rate_n_symbols(self):
        """PHASE_CHANGE reactions must still emit Rate_N symbols in the Jacobian."""
        mech = _mechanism_with_phase_change()
        result = prepare_unified_jacobian(mech)

        J = result["jacobian_matrix"]
        j_str = str(J)

        # PHASE_CHANGE reactions (at indices 0 and 1) should produce Rate_0, Rate_1
        assert "Rate_0" in j_str, f"PHASE_CHANGE reaction at index 0 should produce Rate_0 symbol. " f"Jacobian contains: {j_str}"
        assert "Rate_1" in j_str, f"PHASE_CHANGE reaction at index 1 should produce Rate_1 symbol. " f"Jacobian contains: {j_str}"

    def test_phase_change_no_rh_symbol(self):
        """PHASE_CHANGE mechanisms without EQUILIBRIUM must not introduce RH."""
        mech = _mechanism_with_phase_change()
        result = prepare_unified_jacobian(mech)

        f_total = result["f_implicit"] + result["f_explicit"]
        free_syms = f_total.free_symbols
        sym_names = {str(s) for s in free_syms}

        assert "RH" not in sym_names, f"PHASE_CHANGE-only mechanism should not have RH in f_total, " f"found symbols: {sym_names}"

    def test_phase_change_no_equilibrium_results(self):
        """PHASE_CHANGE mechanisms must not produce equilibrium_results."""
        mech = _mechanism_with_phase_change()
        result = prepare_unified_jacobian(mech)

        assert result.get("equilibrium_results") is None, "PHASE_CHANGE-only mechanism should not produce 'equilibrium_results'"

    def test_phase_change_rate_symbols_in_f_total(self):
        """Rate_N symbols must appear in f_total for PHASE_CHANGE reactions."""
        mech = _mechanism_with_phase_change()
        result = prepare_unified_jacobian(mech)

        f_total = result["f_implicit"] + result["f_explicit"]
        f_str = str(f_total)

        assert "Rate_0" in f_str, "Rate_0 should appear in f_total for PHASE_CHANGE reaction"
        assert "Rate_1" in f_str, "Rate_1 should appear in f_total for PHASE_CHANGE reaction"

    def test_phase_change_jacobian_shape(self):
        """Jacobian shape must match species count for PHASE_CHANGE mechanism."""
        mech = _mechanism_with_phase_change()
        result = prepare_unified_jacobian(mech)

        N = len(mech.species)
        J = result["jacobian_matrix"]
        assert J.shape == (N, N), f"Expected ({N}, {N}), got {J.shape}"
