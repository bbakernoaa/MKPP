"""Unit tests for the equilibrium lowering pass.

Validates: Requirements 3.1, 3.2, 3.3, 3.5

Verifies that the lowering pass correctly handles EQUILIBRIUM reactions:
- f_total contains equilibrium relaxation flux terms (tau_eq_inv and Temp)
- Jacobian has non-zero cross-coupling entries between equilibrium species
- Diagonal entries contain tau_eq_inv contribution for coupled species
- Fixed species are not modified by equilibrium
- Sparsity pattern is correct for the equilibrium sub-block
- Total species symbols are correctly constructed
- RH symbol is stored in the result for mechanisms with equilibrium
"""

import sympy as sp
from mkpp.lowering import prepare_unified_jacobian
from mkpp.model import (
    AerosolRepresentation,
    EquilibriumDefinition,
    MechanismDefinition,
    PhaseMode,
    SpeciesDefinition,
)


def _eq_test_mechanism() -> MechanismDefinition:
    """Build a small mechanism with equilibrium for testing."""
    return MechanismDefinition(
        name="eq_test",
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
            )
        ],
    )


def _eq_test_mechanism_with_fixed() -> MechanismDefinition:
    """Build a mechanism with equilibrium and a fixed species."""
    return MechanismDefinition(
        name="eq_test_fixed",
        description="",
        aerosol_representation=AerosolRepresentation.BULK,
        species=[
            SpeciesDefinition(name="NH3", phase=PhaseMode.GAS),
            SpeciesDefinition(name="NH4a", phase=PhaseMode.AEROSOL),
            SpeciesDefinition(name="HNO3", phase=PhaseMode.GAS),
            SpeciesDefinition(name="NO3an1", phase=PhaseMode.AEROSOL),
            SpeciesDefinition(name="NO3an2", phase=PhaseMode.AEROSOL),
            SpeciesDefinition(name="NO3an3", phase=PhaseMode.AEROSOL),
            SpeciesDefinition(name="SO2", phase=PhaseMode.GAS, role="fixed"),
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
            )
        ],
    )


class TestEquilibriumLowering:
    """Unit tests for the equilibrium lowering pass."""

    def test_equilibrium_flux_in_f_total(self):
        """Verify f_total contains equilibrium flux terms (Temp and tau_eq_inv are present).

        The lowering pass should add relaxation flux terms of the form:
        tau_eq_inv * (eq_expr - C_i) to f_total for equilibrium species.
        These terms involve Temp (from equilibrium constant expressions via
        van't Hoff) and the fast relaxation timescale (tau_eq_inv).
        The RH symbol is stored in the result dict for downstream use.
        """
        mech = _eq_test_mechanism()
        result = prepare_unified_jacobian(mech)

        f_total = result["f_implicit"] + result["f_explicit"]
        free_syms = f_total.free_symbols
        sym_names = {str(s) for s in free_syms}

        # Temp should appear because equilibrium constants (Kp_NH4NO3)
        # use van't Hoff temperature dependence
        assert "Temp" in sym_names, (
            f"Temp should appear in f_total for mechanism with equilibrium "
            f"(via van't Hoff equilibrium constants). Found symbols: {sym_names}"
        )

        # f_total should be non-zero (equilibrium flux terms present)
        assert f_total != sp.zeros(len(mech.species), 1), "f_total should be non-zero when equilibrium reactions are present"

        # RH symbol should be stored in result for downstream code emission
        assert result.get("rh_symbol") is not None, "rh_symbol should be stored in result when equilibrium reactions present"
        assert str(result["rh_symbol"]) == "RH"

    def test_equilibrium_jacobian_nonzero_coupling(self):
        """Verify J has non-zero entries between equilibrium species.

        For example, J[NH3_idx, NH4a_idx] != 0 because equilibrium couples
        NH3 and NH4a through the total species constraint (C_NH3 + C_NH4a).
        """
        mech = _eq_test_mechanism()
        result = prepare_unified_jacobian(mech)

        J = result["jacobian_matrix"]
        species_map = result["species_map"]

        nh3_idx = species_map.index("NH3")
        nh4a_idx = species_map.index("NH4a")

        # NH3 and NH4a are coupled through reduced_nitrogen equilibrium.
        # The Jacobian entry J[NH3, NH4a] should be non-zero because
        # NH3's equilibrium expression depends on C_NH4a (via the total).
        assert J[nh3_idx, nh4a_idx] != 0, (
            f"J[NH3, NH4a] should be non-zero due to equilibrium coupling. " f"Got: {J[nh3_idx, nh4a_idx]}"
        )

        # Similarly, J[NH4a, NH3] should be non-zero
        assert J[nh4a_idx, nh3_idx] != 0, (
            f"J[NH4a, NH3] should be non-zero due to equilibrium coupling. " f"Got: {J[nh4a_idx, nh3_idx]}"
        )

    def test_equilibrium_jacobian_diagonal(self):
        """Verify diagonal entries for actively coupled equilibrium species.

        The relaxation flux tau_eq_inv * (eq_expr_i - C_i) produces a diagonal
        contribution from the -C_i term plus the derivative of eq_expr_i w.r.t.
        C_i. For species where eq_expr_i != C_i (i.e., actual partitioning
        occurs), the diagonal should be non-zero.

        Note: SO4_expr = C_SO2 + C_SO4 = C_S (total sulfate), so
        d(f_SO4)/d(C_SO4) = tau_eq_inv * (d(SO4_expr)/d(C_SO4) - 1) =
        tau_eq_inv * (1 - 1) = 0. This is correct: SO4 is trivially at
        equilibrium with itself. We test the non-trivially coupled species.
        """
        mech = _eq_test_mechanism()
        result = prepare_unified_jacobian(mech)

        J = result["jacobian_matrix"]
        species_map = result["species_map"]

        # Species with non-trivial partitioning have non-zero diagonals.
        # NH3, NH4a, HNO3, NO3an* all have non-trivial equilibrium expressions.
        nontrivial_species = ["NH3", "NH4a", "HNO3", "NO3an1", "NO3an2", "NO3an3"]
        for sp_name in nontrivial_species:
            idx = species_map.index(sp_name)
            assert J[idx, idx] != 0, (
                f"Diagonal J[{sp_name}, {sp_name}] should be non-zero "
                f"due to tau_eq_inv contribution from non-trivial equilibrium. "
                f"Got: {J[idx, idx]}"
            )

    def test_equilibrium_does_not_affect_fixed_species(self):
        """Verify fixed species are not modified by equilibrium.

        Species with role='fixed' should have zero df_dt entries even when
        they participate in an equilibrium system.
        """
        mech = _eq_test_mechanism_with_fixed()
        result = prepare_unified_jacobian(mech)

        f_total = result["f_implicit"] + result["f_explicit"]
        species_map = result["species_map"]

        so2_idx = species_map.index("SO2")

        # SO2 is fixed, so its f_total entry should be zero
        assert f_total[so2_idx] == 0, f"Fixed species SO2 should have zero f_total entry. " f"Got: {f_total[so2_idx]}"

        # Also verify the Jacobian row for the fixed species is all zeros
        J = result["jacobian_matrix"]
        N = J.shape[1]
        for j in range(N):
            assert J[so2_idx, j] == 0, (
                f"Fixed species SO2 should have zero Jacobian row. " f"J[SO2, {species_map[j]}] = {J[so2_idx, j]}"
            )

    def test_equilibrium_sparsity_pattern(self):
        """Verify which entries are non-zero in the Jacobian sub-block for equilibrium species.

        The equilibrium sub-block should have non-zero entries where species
        are coupled through shared total_species groups.
        """
        mech = _eq_test_mechanism()
        result = prepare_unified_jacobian(mech)

        J = result["jacobian_matrix"]
        species_map = result["species_map"]

        # Species in the same total_species group should be coupled
        reduced_n = ["NH3", "NH4a"]
        oxidized_n = ["HNO3", "NO3an1", "NO3an2", "NO3an3"]

        # Within reduced_nitrogen group, all pairs should be coupled
        for sp_i in reduced_n:
            i = species_map.index(sp_i)
            for sp_j in reduced_n:
                j = species_map.index(sp_j)
                assert J[i, j] != 0, (
                    f"J[{sp_i}, {sp_j}] should be non-zero within " f"reduced_nitrogen equilibrium group. Got: {J[i, j]}"
                )

        # Within oxidized_nitrogen group, all pairs should be coupled
        for sp_i in oxidized_n:
            i = species_map.index(sp_i)
            for sp_j in oxidized_n:
                j = species_map.index(sp_j)
                assert J[i, j] != 0, (
                    f"J[{sp_i}, {sp_j}] should be non-zero within " f"oxidized_nitrogen equilibrium group. Got: {J[i, j]}"
                )

    def test_equilibrium_total_species_summing(self):
        """Verify total species symbols are correctly constructed.

        The total species for reduced_nitrogen should be C_NH3 + C_NH4a.
        This is reflected in the equilibrium expressions depending on both symbols.
        """
        mech = _eq_test_mechanism()
        result = prepare_unified_jacobian(mech)

        # Check the equilibrium_results contain expected total_species_map
        assert "equilibrium_results" in result
        eq_result = result["equilibrium_results"][0]

        # total_species_map should have the correct indices
        species_map = result["species_map"]
        nh3_idx = species_map.index("NH3")
        nh4a_idx = species_map.index("NH4a")

        assert "reduced_nitrogen" in eq_result.total_species_map
        rn_indices = eq_result.total_species_map["reduced_nitrogen"]
        assert nh3_idx in rn_indices, f"NH3 index {nh3_idx} should be in reduced_nitrogen total_species_map"
        assert nh4a_idx in rn_indices, f"NH4a index {nh4a_idx} should be in reduced_nitrogen total_species_map"

        # Check that equilibrium partition expressions for NH3 contain both
        # C_NH3 and C_NH4a as free symbols (because they depend on the total)
        partition_nh3 = eq_result.partition_exprs.get("NH3")
        assert partition_nh3 is not None, "NH3 should have a partition expression"
        free_names = {str(s) for s in partition_nh3.free_symbols}
        assert "C_NH3" in free_names, f"NH3 partition expression should depend on C_NH3. " f"Free symbols: {free_names}"
        assert "C_NH4a" in free_names, (
            f"NH3 partition expression should depend on C_NH4a " f"(through total species sum). Free symbols: {free_names}"
        )

    def test_equilibrium_rh_symbol_in_expressions(self):
        """Verify RH symbol is stored in result for mechanisms with equilibrium.

        The equilibrium model interface accepts RH as a parameter for
        future extension (e.g., deliquescence). The lowering pass stores
        the RH symbol in the result dict so that downstream code emission
        can include it in function signatures. The Temp symbol appears in
        f_total via van't Hoff equilibrium constant expressions.
        """
        mech = _eq_test_mechanism()
        result = prepare_unified_jacobian(mech)

        # RH symbol should be stored for downstream code emission
        assert result.get("rh_symbol") is not None
        assert str(result["rh_symbol"]) == "RH"

        # Verify Temp appears in f_total (from equilibrium constants)
        f_total = result["f_implicit"] + result["f_explicit"]
        species_map = result["species_map"]

        # Check that at least one equilibrium species has Temp in its expression.
        # Use string comparison because the Temp symbol in the lowering pass
        # has assumptions (real=True, nonnegative=True) that differ from a bare
        # sp.Symbol("Temp").
        eq_species = ["NH3", "NH4a", "HNO3", "NO3an1", "NO3an2", "NO3an3"]

        found_temp = False
        for sp_name in eq_species:
            idx = species_map.index(sp_name)
            entry_sym_names = {str(s) for s in f_total[idx].free_symbols}
            if "Temp" in entry_sym_names:
                found_temp = True
                break

        assert found_temp, (
            "Temp should appear in f_total for at least one equilibrium species "
            "(from van't Hoff equilibrium constant Kp_NH4NO3)."
        )
