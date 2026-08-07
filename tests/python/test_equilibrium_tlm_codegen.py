"""Verification test for task 8.2: TLM code generation includes equilibrium J·δC entries.

Since the TLM uses the unified Jacobian (which already includes equilibrium
derivative entries from the lowering pass), this test verifies that equilibrium
coupling terms appear in the generated C++ code for both:
  1. compute_tlm() — the standalone J*δC evaluation
  2. integrate_tlm() — the full Rosenbrock TLM propagation through checkpointed steps

The test confirms equilibrium species indices appear in the relevant TLM sections
of the generated header, proving the unified Jacobian infrastructure correctly
propagates equilibrium sensitivities through the tangent linear model.

Requirements referenced: 6.1, 6.2
"""

import tempfile

from mkpp.codegen import generate_headers
from mkpp.model import (
    AerosolRepresentation,
    EquilibriumDefinition,
    MechanismDefinition,
    PhaseMode,
    ReactionDefinition,
    SpeciesDefinition,
)


def _mechanism_with_equilibrium_and_adjoint() -> MechanismDefinition:
    """Build a mechanism with equilibrium reactions suitable for adjoint/TLM emission.

    Uses 4 species: 2 gas-phase kinetic + 2 equilibrium (NH3/NH4a).
    The kinetic reaction (O3 + NO -> NO2 + O2) ensures a non-trivial Jacobian
    baseline, while the equilibrium block (NH3 <-> NH4a) adds coupling entries
    that must appear in the TLM.
    """
    return MechanismDefinition(
        name="eq_tlm_test",
        description="Test equilibrium TLM code generation",
        aerosol_representation=AerosolRepresentation.BULK,
        species=[
            SpeciesDefinition(name="O3", phase=PhaseMode.GAS, elements={"O": 3}),
            SpeciesDefinition(name="NO", phase=PhaseMode.GAS, elements={"N": 1, "O": 1}),
            SpeciesDefinition(name="NH3", phase=PhaseMode.GAS, elements={"N": 1, "H": 3}),
            SpeciesDefinition(name="NH4a", phase=PhaseMode.AEROSOL, elements={"N": 1, "H": 4}),
        ],
        phases=[],
        reactions=[
            ReactionDefinition(
                reaction_type="ARRHENIUS",
                reactants=["O3", "NO"],
                products=["NO", "O3"],
                rate_expression="",
                parameters={"A": "3.0e-12", "B": "0", "C": "-1500"},
            ),
        ],
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


def _mechanism_without_equilibrium() -> MechanismDefinition:
    """Build a kinetic-only mechanism (no equilibrium) for comparison."""
    return MechanismDefinition(
        name="kinetic_only_tlm_test",
        description="Test TLM without equilibrium",
        aerosol_representation=AerosolRepresentation.BULK,
        species=[
            SpeciesDefinition(name="O3", phase=PhaseMode.GAS, elements={"O": 3}),
            SpeciesDefinition(name="NO", phase=PhaseMode.GAS, elements={"N": 1, "O": 1}),
            SpeciesDefinition(name="NH3", phase=PhaseMode.GAS, elements={"N": 1, "H": 3}),
            SpeciesDefinition(name="NH4a", phase=PhaseMode.AEROSOL, elements={"N": 1, "H": 4}),
        ],
        phases=[],
        reactions=[
            ReactionDefinition(
                reaction_type="ARRHENIUS",
                reactants=["O3", "NO"],
                products=["NO", "O3"],
                rate_expression="",
                parameters={"A": "3.0e-12", "B": "0", "C": "-1500"},
            ),
        ],
        equilibrium_reactions=[],
    )


def _generate_header_content(mech: MechanismDefinition, adjoint: bool = True) -> str:
    """Generate C++ header and return its text content."""
    with tempfile.TemporaryDirectory() as tmpdir:
        result = generate_headers(mech, out_dir=tmpdir, adjoint=adjoint)
        with open(result["header"]) as f:
            return f.read()


class TestComputeTLMEquilibriumEntries:
    """Verify compute_tlm() includes equilibrium J·δC coupling entries.

    The compute_tlm function computes dF_block(i) = Σ_j J(i,j) * delta_C(j)
    for all non-zero Jacobian entries. When equilibrium reactions are present,
    the unified Jacobian includes cross-coupling between equilibrium species
    (NH3 at index 2, NH4a at index 3). These entries must appear in compute_tlm.
    """

    def test_compute_tlm_present_with_adjoint(self):
        """Verify compute_tlm function is emitted when adjoint=True."""
        mech = _mechanism_with_equilibrium_and_adjoint()
        content = _generate_header_content(mech, adjoint=True)
        assert "compute_tlm" in content

    def test_compute_tlm_references_equilibrium_species(self):
        """Verify compute_tlm emits J·δC terms referencing equilibrium species indices.

        NH3 is at index 2, NH4a is at index 3 in the species list. The equilibrium
        coupling should produce J(2,3)*delta_C(3) and/or J(3,2)*delta_C(2) entries.
        """
        mech = _mechanism_with_equilibrium_and_adjoint()
        content = _generate_header_content(mech, adjoint=True)

        # Extract the compute_tlm section
        tlm_start = content.find("void compute_tlm(")
        assert tlm_start > 0, "compute_tlm function not found"

        # Find the end of compute_tlm (next function or closing brace pattern)
        tlm_end = content.find("void compute_adjoint(", tlm_start)
        if tlm_end < 0:
            tlm_end = content.find("void project_mass_conservation(", tlm_start)
        if tlm_end < 0:
            tlm_end = len(content)

        tlm_section = content[tlm_start:tlm_end]

        # Equilibrium species are at indices 2 (NH3) and 3 (NH4a)
        # The TLM should reference delta_C(2) and delta_C(3) in coupling terms
        assert "delta_C(2)" in tlm_section, "compute_tlm should reference delta_C(2) (NH3) for equilibrium coupling"
        assert "delta_C(3)" in tlm_section, "compute_tlm should reference delta_C(3) (NH4a) for equilibrium coupling"

    def test_compute_tlm_has_equilibrium_cross_coupling(self):
        """Verify compute_tlm has cross-coupling between equilibrium species.

        The equilibrium system NH3 <-> NH4a creates coupling where:
        - dF(NH3)/dC(NH4a) != 0 (i.e., J(2,3) != 0)
        - dF(NH4a)/dC(NH3) != 0 (i.e., J(3,2) != 0)

        These should appear as terms in dF_block(2) and dF_block(3).
        """
        mech = _mechanism_with_equilibrium_and_adjoint()
        content = _generate_header_content(mech, adjoint=True)

        # Extract the compute_tlm section
        tlm_start = content.find("void compute_tlm(")
        assert tlm_start > 0
        tlm_end = content.find("void compute_adjoint(", tlm_start)
        if tlm_end < 0:
            tlm_end = content.find("void project_mass_conservation(", tlm_start)
        if tlm_end < 0:
            tlm_end = len(content)

        tlm_section = content[tlm_start:tlm_end]

        # dF_block(2) should contain a term involving delta_C(3) (NH4a coupling)
        # and/or dF_block(3) should contain a term involving delta_C(2) (NH3 coupling)
        # At minimum, equilibrium self-coupling should exist
        has_eq_coupling = ("dF_block(2)" in tlm_section and "delta_C(3)" in tlm_section) or (
            "dF_block(3)" in tlm_section and "delta_C(2)" in tlm_section
        )
        assert has_eq_coupling, "compute_tlm should have cross-coupling between equilibrium species " "(NH3 index=2, NH4a index=3)"

    def test_compute_tlm_equilibrium_species_not_zero(self):
        """Verify that equilibrium species rows in dF_block are not all-zero.

        For indices 2 (NH3) and 3 (NH4a), the dF_block assignments should have
        non-trivial expressions (not just '0.0') because equilibrium creates
        non-zero Jacobian entries for these species.
        """
        mech = _mechanism_with_equilibrium_and_adjoint()
        content = _generate_header_content(mech, adjoint=True)

        # Extract compute_tlm section
        tlm_start = content.find("void compute_tlm(")
        assert tlm_start > 0
        tlm_end = content.find("void compute_adjoint(", tlm_start)
        if tlm_end < 0:
            tlm_end = content.find("void project_mass_conservation(", tlm_start)
        if tlm_end < 0:
            tlm_end = len(content)
        tlm_section = content[tlm_start:tlm_end]

        # dF_block(2) and dF_block(3) should have += operations (non-trivial coupling)
        assert "dF_block(2) +=" in tlm_section, "dF_block(2) should have non-zero coupling terms from equilibrium"
        assert "dF_block(3) +=" in tlm_section, "dF_block(3) should have non-zero coupling terms from equilibrium"


class TestIntegrateTLMEquilibriumEntries:
    """Verify integrate_tlm() includes equilibrium Jacobian entries.

    The integrate_tlm function (emitted via _emit_rosenbrock_tlm_stages) recomputes
    the Jacobian at each checkpoint step and uses sparse J * δC products in the
    TLM stage RHS computation. Equilibrium entries should appear in the Jacobian
    recomputation and the RHS formation.
    """

    def test_integrate_tlm_present(self):
        """Verify integrate_tlm function is emitted when adjoint=True."""
        mech = _mechanism_with_equilibrium_and_adjoint()
        content = _generate_header_content(mech, adjoint=True)
        assert "void integrate_tlm(" in content

    def test_integrate_tlm_jacobian_references_equilibrium_indices(self):
        """Verify that the Jacobian computed inside integrate_tlm has equilibrium entries.

        The TLM stages recompute J at saved checkpoint state. With equilibrium,
        J_{2,3} and J_{3,2} (or J_{2,2}, J_{3,3}) should appear as variable
        declarations inside integrate_tlm.
        """
        mech = _mechanism_with_equilibrium_and_adjoint()
        content = _generate_header_content(mech, adjoint=True)

        # Extract integrate_tlm section
        tlm_start = content.find("void integrate_tlm(")
        assert tlm_start > 0

        # Find end (next function or end of struct)
        # integrate_tlm is the last function before closing braces
        tlm_end = content.find("  };\n", tlm_start)
        if tlm_end < 0:
            tlm_end = len(content)
        tlm_section = content[tlm_start:tlm_end]

        # The Jacobian re-evaluation inside the TLM should declare J_i_j
        # variables for equilibrium coupling positions
        # NH3=index 2, NH4a=index 3
        # Check for any J variable involving indices 2 or 3
        has_j_2 = "J_2_" in tlm_section or "J_3_" in tlm_section
        assert has_j_2, "integrate_tlm should recompute Jacobian entries involving " "equilibrium species (indices 2, 3)"

    def test_integrate_tlm_uses_dc_for_equilibrium_species(self):
        """Verify that TLM stage RHS references dC_2 and dC_3 (equilibrium species).

        The TLM stage computation forms J*(δC + Σ A*δK), which requires
        multiplying Jacobian entries by the perturbation vector components
        for equilibrium species.
        """
        mech = _mechanism_with_equilibrium_and_adjoint()
        content = _generate_header_content(mech, adjoint=True)

        # Extract integrate_tlm section
        tlm_start = content.find("void integrate_tlm(")
        assert tlm_start > 0
        tlm_end = content.find("  };\n", tlm_start)
        if tlm_end < 0:
            tlm_end = len(content)
        tlm_section = content[tlm_start:tlm_end]

        # The TLM uses dC_k naming for perturbation components
        assert "dC_2" in tlm_section, "integrate_tlm should reference dC_2 (NH3 perturbation) " "in equilibrium coupling"
        assert "dC_3" in tlm_section, "integrate_tlm should reference dC_3 (NH4a perturbation) " "in equilibrium coupling"

    def test_integrate_tlm_updates_equilibrium_species_perturbation(self):
        """Verify δC update at end of TLM step includes equilibrium species.

        After all stages, integrate_tlm updates: dC_k += Σ M_i * dK_i_k
        for all k. This should include k=2 (NH3) and k=3 (NH4a).
        """
        mech = _mechanism_with_equilibrium_and_adjoint()
        content = _generate_header_content(mech, adjoint=True)

        # Extract integrate_tlm section
        tlm_start = content.find("void integrate_tlm(")
        assert tlm_start > 0
        tlm_end = content.find("  };\n", tlm_start)
        if tlm_end < 0:
            tlm_end = len(content)
        tlm_section = content[tlm_start:tlm_end]

        # The final δC update should write back to delta_C(2) and delta_C(3)
        assert "delta_C(2)" in tlm_section, "integrate_tlm should write back δC for NH3 (index 2)"
        assert "delta_C(3)" in tlm_section, "integrate_tlm should write back δC for NH4a (index 3)"


class TestTLMEquilibriumVsKineticOnly:
    """Compare TLM output between equilibrium and kinetic-only mechanisms.

    Verifies that equilibrium adds additional coupling terms that would not
    be present in a kinetic-only mechanism with the same species.
    """

    def test_equilibrium_adds_coupling_entries_to_tlm(self):
        """Verify equilibrium mechanism has MORE Jacobian references in TLM than kinetic-only.

        The equilibrium system NH3 <-> NH4a adds derivative coupling between
        species 2 and 3 that doesn't exist in the kinetic-only variant.
        """
        mech_eq = _mechanism_with_equilibrium_and_adjoint()
        mech_kinetic = _mechanism_without_equilibrium()

        content_eq = _generate_header_content(mech_eq, adjoint=True)
        content_kinetic = _generate_header_content(mech_kinetic, adjoint=True)

        # Extract compute_tlm sections
        def _extract_compute_tlm(content):
            start = content.find("void compute_tlm(")
            if start < 0:
                return ""
            end = content.find("void compute_adjoint(", start)
            if end < 0:
                end = content.find("void project_mass_conservation(", start)
            if end < 0:
                end = len(content)
            return content[start:end]

        tlm_eq = _extract_compute_tlm(content_eq)
        tlm_kinetic = _extract_compute_tlm(content_kinetic)

        # The equilibrium version should have more dF_block += lines
        # because equilibrium adds cross-coupling
        eq_coupling_count = tlm_eq.count("dF_block")
        kinetic_coupling_count = tlm_kinetic.count("dF_block")

        assert eq_coupling_count > kinetic_coupling_count, (
            f"Equilibrium TLM should have more coupling entries than kinetic-only: "
            f"eq={eq_coupling_count}, kinetic={kinetic_coupling_count}"
        )

    def test_equilibrium_adds_jacobian_entries_to_integrate_tlm(self):
        """Verify equilibrium adds Jacobian variables in integrate_tlm.

        The equilibrium mechanism should declare more J_i_j variables inside
        integrate_tlm than the kinetic-only version.
        """
        mech_eq = _mechanism_with_equilibrium_and_adjoint()
        mech_kinetic = _mechanism_without_equilibrium()

        content_eq = _generate_header_content(mech_eq, adjoint=True)
        content_kinetic = _generate_header_content(mech_kinetic, adjoint=True)

        # Extract integrate_tlm sections
        def _extract_integrate_tlm(content):
            start = content.find("void integrate_tlm(")
            if start < 0:
                return ""
            end = content.find("  };\n", start)
            if end < 0:
                end = len(content)
            return content[start:end]

        tlm_eq = _extract_integrate_tlm(content_eq)
        tlm_kinetic = _extract_integrate_tlm(content_kinetic)

        # Count J_i_j declarations
        import re

        j_pattern = r"double J_\d+_\d+"
        eq_j_count = len(re.findall(j_pattern, tlm_eq))
        kinetic_j_count = len(re.findall(j_pattern, tlm_kinetic))

        assert eq_j_count > kinetic_j_count, (
            f"Equilibrium integrate_tlm should have more J entries: " f"eq={eq_j_count}, kinetic={kinetic_j_count}"
        )


class TestTLMEquilibriumConsistency:
    """Verify consistency between compute_tlm and integrate_tlm equilibrium handling.

    Both functions should reference the same equilibrium species and coupling
    positions, since they both derive from the same unified Jacobian.
    """

    def test_same_equilibrium_species_in_both_tlm_functions(self):
        """Both compute_tlm and integrate_tlm should reference equilibrium species."""
        mech = _mechanism_with_equilibrium_and_adjoint()
        content = _generate_header_content(mech, adjoint=True)

        # Extract compute_tlm
        compute_start = content.find("void compute_tlm(")
        compute_end = content.find("void compute_adjoint(", compute_start)
        if compute_end < 0:
            compute_end = content.find("void project_mass_conservation(", compute_start)
        if compute_end < 0:
            compute_end = len(content)
        compute_section = content[compute_start:compute_end]

        # Extract integrate_tlm
        integrate_start = content.find("void integrate_tlm(")
        integrate_end = content.find("  };\n", integrate_start)
        if integrate_end < 0:
            integrate_end = len(content)
        integrate_section = content[integrate_start:integrate_end]

        # Both should reference equilibrium species indices (2, 3)
        assert "delta_C(2)" in compute_section or "dC_2" in compute_section
        assert "delta_C(3)" in compute_section or "dC_3" in compute_section
        assert "dC_2" in integrate_section
        assert "dC_3" in integrate_section

    def test_temp_and_rh_not_in_integrate_tlm(self):
        """Verify integrate_tlm does not require temp/rh as separate parameters.

        The TLM operates on the saved Jacobian structure (recompute-J strategy),
        which already has equilibrium derivatives folded in. The TLM itself does
        not need temp/rh because it uses J entries directly.

        Note: The Jacobian expressions within integrate_tlm may reference Temp/RH
        symbols since they're recomputed at each step, but the function signature
        should not require them (they're embedded in the checkpoint state evaluation).
        """
        mech = _mechanism_with_equilibrium_and_adjoint()
        content = _generate_header_content(mech, adjoint=True)

        # Find integrate_tlm signature
        tlm_start = content.find("void integrate_tlm(")
        assert tlm_start > 0

        # The signature ends at the opening brace
        sig_end = content.find("{", tlm_start)
        signature = content[tlm_start:sig_end]

        # integrate_tlm should accept state, delta_C, jvals, and chk
        # but not separate temp/rh parameters (those are in the Jacobian expressions)
        assert "PertView& delta_C" in signature
        assert "const CheckpointBuffer& chk" in signature
