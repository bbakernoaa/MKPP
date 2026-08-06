"""Unit tests for code emission with equilibrium.

Validates: Requirements 4.1, 5.4, 7.5, 8.2

Verifies that the code generator correctly emits:
- EquilibriumInput enum when equilibrium reactions are present
- temp/rh parameters in compute_rates, compute_jacobian, and integrate signatures
- check_mass_balance and check_charge_balance under #ifdef MKPP_DIAGNOSTICS
- Backward compatibility: no temp/rh or enum when equilibrium is absent
- Local aliases for temp/rh inside function bodies
"""

from mkpp.codegen import generate_headers
from mkpp.model import (
    AerosolRepresentation,
    MechanismDefinition,
    PhaseMode,
    SpeciesDefinition,
)


def _make_plain_mechanism() -> MechanismDefinition:
    """Build a mechanism without equilibrium reactions for backward compat tests."""
    return MechanismDefinition(
        name="plain_codegen_test",
        description="Test mechanism without equilibrium",
        aerosol_representation=AerosolRepresentation.BULK,
        species=[
            SpeciesDefinition(name="O3", phase=PhaseMode.GAS),
            SpeciesDefinition(name="O", phase=PhaseMode.GAS),
        ],
        phases=[],
        reactions=[],
        equilibrium_reactions=[],
    )


def _generate_plain_header_content(mech: MechanismDefinition, tmp_path) -> str:
    """Generate headers and return the header file content as a string."""
    results = generate_headers(mech, out_dir=str(tmp_path))
    with open(results["header"]) as f:
        return f.read()


class TestEquilibriumCodegen:
    """Unit tests for code emission with equilibrium reactions.

    Uses the session-scoped `eq_generated_header` fixture from conftest.py
    to avoid redundant expensive code generation on every test.
    """

    def test_equilibrium_input_enum_emitted(self, eq_generated_header):
        """Verify EquilibriumInput enum is emitted in the generated header.

        Validates: Requirement 5.4
        """
        content = eq_generated_header

        assert (
            "enum class EquilibriumInput" in content
        ), "EquilibriumInput enum should be emitted when equilibrium reactions are present"
        assert "Temperature = 0" in content
        assert "RelativeHumidity = 1" in content
        assert "COUNT = 2" in content

    def test_compute_rates_signature_with_equilibrium(self, eq_generated_header):
        """Verify compute_rates has temp/rh parameters when equilibrium is present.

        Validates: Requirement 4.1
        """
        content = eq_generated_header

        # The compute_rates signature should include temp and rh
        assert "void compute_rates(" in content
        # Find the compute_rates signature and check for temp/rh params
        rates_idx = content.index("void compute_rates(")
        # Get the full signature (up to the opening brace)
        sig_end = content.index("{", rates_idx)
        signature = content[rates_idx:sig_end]
        assert "const double temp" in signature, f"compute_rates should have 'temp' parameter. Signature: {signature}"
        assert "const double rh" in signature, f"compute_rates should have 'rh' parameter. Signature: {signature}"

    def test_compute_jacobian_signature_with_equilibrium(self, eq_generated_header):
        """Verify compute_jacobian has temp/rh parameters when equilibrium is present.

        Validates: Requirement 4.1
        """
        content = eq_generated_header

        assert "void compute_jacobian(" in content
        jac_idx = content.index("void compute_jacobian(")
        sig_end = content.index("{", jac_idx)
        signature = content[jac_idx:sig_end]
        assert "const double temp" in signature, f"compute_jacobian should have 'temp' parameter. Signature: {signature}"
        assert "const double rh" in signature, f"compute_jacobian should have 'rh' parameter. Signature: {signature}"

    def test_integrate_signature_with_equilibrium(self, eq_generated_header):
        """Verify integrate has temp/rh parameters when equilibrium is present.

        Validates: Requirement 4.1
        """
        content = eq_generated_header

        assert "void integrate(" in content
        integrate_idx = content.index("void integrate(")
        sig_end = content.index("{", integrate_idx)
        signature = content[integrate_idx:sig_end]
        assert "const double temp" in signature, f"integrate should have 'temp' parameter. Signature: {signature}"
        assert "const double rh" in signature, f"integrate should have 'rh' parameter. Signature: {signature}"

    def test_check_mass_balance_emitted(self, eq_generated_header):
        """Verify check_mass_balance is emitted under #ifdef MKPP_DIAGNOSTICS.

        Validates: Requirement 7.5
        """
        content = eq_generated_header

        # check_mass_balance should be present
        assert "check_mass_balance(" in content, "check_mass_balance should be emitted for equilibrium mechanisms"

        # It should be inside a MKPP_DIAGNOSTICS ifdef block
        diag_start = content.index("#ifdef MKPP_DIAGNOSTICS")
        diag_end = content.index("#endif // MKPP_DIAGNOSTICS")
        diagnostics_section = content[diag_start:diag_end]

        assert "check_mass_balance(" in diagnostics_section, "check_mass_balance should be inside #ifdef MKPP_DIAGNOSTICS block"

    def test_check_charge_balance_emitted(self, eq_generated_header):
        """Verify check_charge_balance is emitted under #ifdef MKPP_DIAGNOSTICS.

        Validates: Requirement 8.2
        """
        content = eq_generated_header

        # check_charge_balance should be present
        assert "check_charge_balance(" in content, "check_charge_balance should be emitted for equilibrium mechanisms"

        # It should be inside a MKPP_DIAGNOSTICS ifdef block
        diag_start = content.index("#ifdef MKPP_DIAGNOSTICS")
        diag_end = content.index("#endif // MKPP_DIAGNOSTICS")
        diagnostics_section = content[diag_start:diag_end]

        assert "check_charge_balance(" in diagnostics_section, "check_charge_balance should be inside #ifdef MKPP_DIAGNOSTICS block"

    def test_backward_compat_no_equilibrium(self, tmp_path):
        """Verify that without equilibrium, no temp/rh in signatures and no EquilibriumInput enum.

        Validates: Requirements 5.4, 8.2 (backward compatibility)
        """
        mech = _make_plain_mechanism()
        content = _generate_plain_header_content(mech, tmp_path)

        # No EquilibriumInput enum
        assert "EquilibriumInput" not in content, "EquilibriumInput enum should NOT be emitted without equilibrium reactions"

        # compute_rates signature should NOT have temp/rh
        rates_idx = content.index("void compute_rates(")
        sig_end = content.index("{", rates_idx)
        rates_sig = content[rates_idx:sig_end]
        assert "const double temp" not in rates_sig, "compute_rates should NOT have 'temp' parameter without equilibrium"
        assert "const double rh" not in rates_sig, "compute_rates should NOT have 'rh' parameter without equilibrium"

        # compute_jacobian signature should NOT have temp/rh
        jac_idx = content.index("void compute_jacobian(")
        sig_end = content.index("{", jac_idx)
        jac_sig = content[jac_idx:sig_end]
        assert "const double temp" not in jac_sig, "compute_jacobian should NOT have 'temp' parameter without equilibrium"
        assert "const double rh" not in jac_sig, "compute_jacobian should NOT have 'rh' parameter without equilibrium"

        # No diagnostic functions
        assert "check_mass_balance" not in content
        assert "check_charge_balance" not in content
        assert "MKPP_DIAGNOSTICS" not in content

    def test_temp_rh_local_aliases(self, eq_generated_header):
        """Verify 'const double Temp = temp;' and 'const double RH = rh;' in function bodies.

        Validates: Requirement 4.1 (temp/rh are aliased for use in equilibrium expressions)
        """
        content = eq_generated_header

        assert "const double Temp = temp;" in content, "Generated code should contain 'const double Temp = temp;' alias"
        assert "const double RH = rh;" in content, "Generated code should contain 'const double RH = rh;' alias"
