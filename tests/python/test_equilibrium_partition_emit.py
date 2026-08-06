"""Test for task 6.3: Emit standalone comparison function for validation mode.

Verifies that generate_headers() emits a `compute_equilibrium_partition` function
in the generated C++ header when equilibrium reactions are present.

Requirements referenced: 9.1
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


def _mechanism_with_equilibrium() -> MechanismDefinition:
    """Build a minimal mechanism with equilibrium reactions."""
    return MechanismDefinition(
        name="eq_partition_test",
        description="Test equilibrium partition function emission",
        aerosol_representation=AerosolRepresentation.BULK,
        species=[
            SpeciesDefinition(name="NH3", phase=PhaseMode.GAS, elements={"N": 1}),
            SpeciesDefinition(name="NH4a", phase=PhaseMode.AEROSOL, elements={"N": 1}),
        ],
        phases=[],
        reactions=[],
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
    """Build a minimal mechanism without equilibrium reactions."""
    return MechanismDefinition(
        name="no_eq_test",
        description="Test without equilibrium",
        aerosol_representation=AerosolRepresentation.BULK,
        species=[
            SpeciesDefinition(name="NH3", phase=PhaseMode.GAS, elements={"N": 1}),
            SpeciesDefinition(name="NH4a", phase=PhaseMode.AEROSOL, elements={"N": 1}),
        ],
        phases=[],
        reactions=[
            ReactionDefinition(
                reaction_type="ARRHENIUS",
                reactants=["NH3"],
                products=["NH4a"],
                rate_expression="",
                parameters={"A": "1e-12", "B": "0", "C": "0"},
            )
        ],
        equilibrium_reactions=[],
    )


class TestComputeEquilibriumPartitionEmission:
    """Test that compute_equilibrium_partition is emitted correctly."""

    def test_function_emitted_with_equilibrium(self):
        """Verify compute_equilibrium_partition is present when equilibrium reactions exist."""
        mech = _mechanism_with_equilibrium()
        with tempfile.TemporaryDirectory() as tmpdir:
            result = generate_headers(mech, out_dir=tmpdir)
            header_path = result["header"]
            with open(header_path) as f:
                content = f.read()

        assert "compute_equilibrium_partition" in content

    def test_function_not_emitted_without_equilibrium(self):
        """Verify compute_equilibrium_partition is NOT emitted without equilibrium reactions."""
        mech = _mechanism_without_equilibrium()
        with tempfile.TemporaryDirectory() as tmpdir:
            result = generate_headers(mech, out_dir=tmpdir)
            header_path = result["header"]
            with open(header_path) as f:
                content = f.read()

        assert "compute_equilibrium_partition" not in content

    def test_function_signature_correct(self):
        """Verify function signature includes temp and rh parameters."""
        mech = _mechanism_with_equilibrium()
        with tempfile.TemporaryDirectory() as tmpdir:
            result = generate_headers(mech, out_dir=tmpdir)
            header_path = result["header"]
            with open(header_path) as f:
                content = f.read()

        # Check function signature components
        assert "const StateView& state" in content
        assert "ResultView& eq_result" in content
        assert "const double temp" in content
        assert "const double rh" in content

    def test_function_is_kokkos_inline(self):
        """Verify function is marked as KOKKOS_INLINE_FUNCTION."""
        mech = _mechanism_with_equilibrium()
        with tempfile.TemporaryDirectory() as tmpdir:
            result = generate_headers(mech, out_dir=tmpdir)
            header_path = result["header"]
            with open(header_path) as f:
                content = f.read()

        # Find the section containing compute_equilibrium_partition
        idx = content.find("compute_equilibrium_partition")
        assert idx > 0
        # KOKKOS_INLINE_FUNCTION should appear just before the function
        preceding = content[max(0, idx - 200) : idx]
        assert "KOKKOS_INLINE_FUNCTION" in preceding

    def test_total_species_concentrations_emitted(self):
        """Verify total species sum computations are present."""
        mech = _mechanism_with_equilibrium()
        with tempfile.TemporaryDirectory() as tmpdir:
            result = generate_headers(mech, out_dir=tmpdir)
            header_path = result["header"]
            with open(header_path) as f:
                content = f.read()

        # The reduced_nitrogen total should be computed from state(0) + state(1)
        assert "C_total_reduced_nitrogen" in content

    def test_eq_result_assignments_emitted(self):
        """Verify eq_result assignments are present for equilibrium species."""
        mech = _mechanism_with_equilibrium()
        with tempfile.TemporaryDirectory() as tmpdir:
            result = generate_headers(mech, out_dir=tmpdir)
            header_path = result["header"]
            with open(header_path) as f:
                content = f.read()

        # Should have eq_result(0) and eq_result(1) for NH3 and NH4a
        assert "eq_result(0)" in content
        assert "eq_result(1)" in content

    def test_temp_and_rh_local_variables(self):
        """Verify Temp and RH local variables are declared for expression use."""
        mech = _mechanism_with_equilibrium()
        with tempfile.TemporaryDirectory() as tmpdir:
            result = generate_headers(mech, out_dir=tmpdir)
            header_path = result["header"]
            with open(header_path) as f:
                content = f.read()

        assert "const double Temp = temp;" in content
        assert "const double RH = rh;" in content
