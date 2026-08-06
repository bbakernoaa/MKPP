"""Verification test for task 4.2: equilibrium Jacobian assembly.

Verifies that prepare_unified_jacobian() correctly includes equilibrium
derivatives and stores EquilibriumSymbolicResult in the result dict.

Requirements referenced: 3.1, 3.2, 3.3, 3.5
"""

import sympy as sp
from mkpp.lowering import prepare_unified_jacobian
from mkpp.model import (
    AerosolRepresentation,
    EquilibriumDefinition,
    EquilibriumSymbolicResult,
    MechanismDefinition,
    PhaseMode,
    ReactionDefinition,
    SpeciesDefinition,
)


def _minimal_eq_mechanism(include_kinetic: bool = False) -> MechanismDefinition:
    """Build a minimal mechanism with equilibrium reactions (2 species for speed)."""
    reactions = []
    if include_kinetic:
        reactions.append(
            ReactionDefinition(
                reaction_type="ARRHENIUS",
                reactants=["NH3"],
                products=["NH4a"],
                rate_expression="",
                parameters={"A": "1e-12", "B": "0", "C": "0"},
            )
        )

    return MechanismDefinition(
        name="eq_test",
        description="Test equilibrium Jacobian",
        aerosol_representation=AerosolRepresentation.BULK,
        species=[
            SpeciesDefinition(name="NH3", phase=PhaseMode.GAS, elements={"N": 1}),
            SpeciesDefinition(name="NH4a", phase=PhaseMode.AEROSOL, elements={"N": 1}),
        ],
        phases=[],
        reactions=reactions,
        equilibrium_reactions=[
            EquilibriumDefinition(
                system="NH4_NO3_SO4",
                total_species={
                    "reduced_nitrogen": ["NH3", "NH4a"],
                    "oxidized_nitrogen": [],
                    "sulfate": [],
                },
            )
        ],
    )


class TestEquilibriumJacobianAssembly:
    """Test that equilibrium derivatives are included in the unified Jacobian."""

    def test_equilibrium_results_present(self):
        """Verify equilibrium_results key exists when equilibrium reactions present."""
        mech = _minimal_eq_mechanism()
        result = prepare_unified_jacobian(mech)

        assert "equilibrium_results" in result
        assert isinstance(result["equilibrium_results"], list)
        assert len(result["equilibrium_results"]) == 1

    def test_rh_symbol_present(self):
        """Verify rh_symbol is stored when equilibrium reactions present."""
        mech = _minimal_eq_mechanism()
        result = prepare_unified_jacobian(mech)

        assert "rh_symbol" in result
        assert result["rh_symbol"] is not None
        assert str(result["rh_symbol"]) == "RH"

    def test_equilibrium_symbolic_result_structure(self):
        """Verify EquilibriumSymbolicResult has correct structure."""
        mech = _minimal_eq_mechanism()
        result = prepare_unified_jacobian(mech)

        eq_result = result["equilibrium_results"][0]
        assert isinstance(eq_result, EquilibriumSymbolicResult)

        # partition_exprs should contain species from the model
        assert "NH3" in eq_result.partition_exprs
        assert "NH4a" in eq_result.partition_exprs

        # total_species_map should map elements to indices
        assert "reduced_nitrogen" in eq_result.total_species_map
        assert eq_result.total_species_map["reduced_nitrogen"] == [0, 1]

        # equilibrium_constants should have van't Hoff constants
        assert "Kp_NH4NO3" in eq_result.equilibrium_constants
        assert "Kp_NH4HSO4" in eq_result.equilibrium_constants
        assert "Kp_NH42SO4" in eq_result.equilibrium_constants

    def test_equilibrium_jacobian_entries_nonempty(self):
        """Verify equilibrium-specific Jacobian entries are non-empty."""
        mech = _minimal_eq_mechanism()
        result = prepare_unified_jacobian(mech)

        eq_result = result["equilibrium_results"][0]
        # The NH4/NO3/SO4 model with 2 species (NH3, NH4a) produces
        # non-zero derivatives for the partition expressions
        assert len(eq_result.jacobian_entries) > 0

        # Each entry is (i, j, derivative_expr) tuple
        for entry in eq_result.jacobian_entries:
            assert len(entry) == 3
            i, j, deriv = entry
            assert isinstance(i, int)
            assert isinstance(j, int)
            assert deriv != 0  # Only non-zero entries stored

    def test_unified_jacobian_nonzero_with_equilibrium(self):
        """Verify the full Jacobian has non-zero entries from equilibrium coupling."""
        mech = _minimal_eq_mechanism()
        result = prepare_unified_jacobian(mech)

        J = result["jacobian_matrix"]
        N = J.shape[0]
        assert N == 2  # 2 species

        # The Jacobian should have non-zero entries because equilibrium
        # relaxation flux tau_eq_inv * (eq_expr - C_i) produces coupling
        nonzero_count = sum(1 for i in range(N) for j in range(N) if J[i, j] != 0)
        assert nonzero_count > 0, "Jacobian should have non-zero entries from equilibrium"

    def test_jacobian_contains_temp_symbol(self):
        """Verify Temp appears in Jacobian free symbols (from equilibrium constants)."""
        mech = _minimal_eq_mechanism()
        result = prepare_unified_jacobian(mech)

        J = result["jacobian_matrix"]
        N = J.shape[0]
        all_free = set()
        for i in range(N):
            for j in range(N):
                if J[i, j] != 0:
                    all_free.update(J[i, j].free_symbols)

        free_names = {str(s) for s in all_free}
        assert "Temp" in free_names, f"Temp should appear in equilibrium Jacobian entries, " f"found: {free_names}"

    def test_jacobian_shape_matches_species(self):
        """Verify Jacobian has correct shape with equilibrium."""
        mech = _minimal_eq_mechanism()
        result = prepare_unified_jacobian(mech)

        N = len(mech.species)
        J = result["jacobian_matrix"]
        assert J.shape == (N, N)

    def test_rh_symbol_none_without_equilibrium(self):
        """Verify rh_symbol is None when no equilibrium reactions."""
        mech = MechanismDefinition(
            name="kinetic_only",
            description="No equilibrium",
            aerosol_representation=AerosolRepresentation.BULK,
            species=[
                SpeciesDefinition(name="O", phase=PhaseMode.GAS, elements={"O": 1}),
                SpeciesDefinition(name="O2", phase=PhaseMode.GAS, elements={"O": 2}),
            ],
            phases=[],
            reactions=[
                ReactionDefinition(
                    reaction_type="ARRHENIUS",
                    reactants=["O"],
                    products=["O2"],
                    rate_expression="",
                    parameters={"A": "1.0", "B": "0", "C": "0"},
                ),
            ],
            equilibrium_reactions=[],
        )
        result = prepare_unified_jacobian(mech)
        assert result["rh_symbol"] is None
        assert "equilibrium_results" not in result

    def test_kinetic_plus_equilibrium_jacobian(self):
        """Verify Jacobian has both kinetic and equilibrium entries."""
        mech = _minimal_eq_mechanism(include_kinetic=True)
        result = prepare_unified_jacobian(mech)

        J = result["jacobian_matrix"]
        # With both kinetic (ARRHENIUS) and equilibrium reactions,
        # the Jacobian should have contributions from both
        N = J.shape[0]
        nonzero_count = sum(1 for i in range(N) for j in range(N) if J[i, j] != 0)
        assert nonzero_count > 0

    def test_equilibrium_constants_are_sympy_exprs(self):
        """Verify equilibrium constants are SymPy expressions (not floats)."""
        mech = _minimal_eq_mechanism()
        result = prepare_unified_jacobian(mech)

        eq_result = result["equilibrium_results"][0]
        for name, expr in eq_result.equilibrium_constants.items():
            # Should be SymPy expressions containing Temp
            assert isinstance(expr, sp.Expr), f"Equilibrium constant {name} should be SymPy Expr, got {type(expr)}"
            # Van't Hoff expressions should contain Temp
            free_names = {str(s) for s in expr.free_symbols}
            assert "Temp" in free_names, f"Equilibrium constant {name} should depend on Temp"
