"""
Regression test verifying default `ros3` output is unchanged.

**Validates: Requirements 8.1, 8.2**

Ensures that:
1. Generating headers with solver_name="ros3" (explicit) and without specifying
   solver_name (relying on the default parameter) produce identical output.
2. The generated output contains expected Ros3-specific characteristics:
   - 3 stages
   - Gamma[0] = 0.43586652150845899942 (the Ros3 gamma)
   - 3-stage forward/backward substitution blocks
   - Kokkos::cbrt in step control (ELO=3)
"""

import re
import tempfile

from mkpp.codegen import SOLVER_COEFFICIENTS, generate_headers
from mkpp.lowering import compute_symbolic_lu_decomposition, prepare_unified_jacobian
from mkpp.model import (
    AerosolRepresentation,
    MechanismDefinition,
    PhaseMode,
    ReactionDefinition,
    SpeciesDefinition,
)


def _build_toy_mechanism():
    """Build a simple 3-species toy mechanism for regression testing."""
    sp_a = SpeciesDefinition(name="A", phase=PhaseMode.GAS)
    sp_b = SpeciesDefinition(name="B", phase=PhaseMode.GAS)
    sp_c = SpeciesDefinition(name="C", phase=PhaseMode.GAS)
    rxn1 = ReactionDefinition(
        reaction_type="ARRHENIUS",
        reactants={"A": 1.0},
        products={"B": 1.0},
        rate_expression="k1*A",
        parameters={"A": 1e-2, "B": 0.0, "C": 0.0},
        stiff=True,
    )
    rxn2 = ReactionDefinition(
        reaction_type="ARRHENIUS",
        reactants={"B": 1.0},
        products={"C": 1.0},
        rate_expression="k2*B",
        parameters={"A": 1e-3, "B": 0.0, "C": 0.0},
        stiff=True,
    )
    return MechanismDefinition(
        name="test_ros3_default",
        description="Toy mechanism for Ros3 default regression test",
        aerosol_representation=AerosolRepresentation.BULK,
        species=[sp_a, sp_b, sp_c],
        phases=[],
        reactions=[rxn1, rxn2],
    )


def _prepare_mechanism():
    """Build and prepare the mechanism with lowering data for code generation."""
    mech = _build_toy_mechanism()
    lowering_data = prepare_unified_jacobian(mech)
    plan = compute_symbolic_lu_decomposition(lowering_data["jacobian_matrix"], lowering_data["species_map"])
    mech.metadata = {
        "sympy_metadata": lowering_data,
        "symbolic_lu_plan": plan,
    }
    return mech


def _generate_header_content(mech, solver_name=None):
    """Generate header and return file content. If solver_name is None, use default."""
    with tempfile.TemporaryDirectory() as tmp_dir:
        if solver_name is not None:
            artifacts = generate_headers(mech, out_dir=tmp_dir, solver_name=solver_name)
        else:
            artifacts = generate_headers(mech, out_dir=tmp_dir)
        with open(artifacts["header"]) as f:
            return f.read()


class TestRos3DefaultRegression:
    """Regression tests ensuring default ros3 output is unchanged."""

    def test_default_equals_explicit_ros3(self):
        """
        Generating headers without --solver flag produces output identical
        to explicitly specifying --solver ros3.

        **Validates: Requirements 8.1, 8.2**
        """
        mech = _prepare_mechanism()

        # Generate with explicit ros3
        content_explicit = _generate_header_content(mech, solver_name="ros3")

        # Generate with default (no solver_name specified)
        content_default = _generate_header_content(mech)

        assert content_explicit == content_default, (
            "Output with solver_name='ros3' differs from default (no solver_name). "
            "The default solver must remain ros3 for backward compatibility."
        )

    def test_ros3_has_three_stages(self):
        """
        The default Ros3 output contains exactly 3 stage computation blocks
        in each integrator function.

        **Validates: Requirements 8.1**
        """
        mech = _prepare_mechanism()
        code = _generate_header_content(mech)

        # Count stage comments in the entire file (integrate + integrate_with_reduction)
        stage_comments = re.findall(r"// --- Stage \d+ ---", code)
        # 3 stages x 2 functions = 6 total stage markers
        assert len(stage_comments) == 9, f"Expected 9 stage markers (3 stages x 3 functions), found {len(stage_comments)}"

        # Verify stages are numbered 1, 2, 3 in each function
        stage_numbers = [int(re.search(r"Stage (\d+)", c).group(1)) for c in stage_comments]
        assert stage_numbers == [
            1,
            2,
            3,
            1,
            2,
            3,
            1,
            2,
            3,
        ], f"Stage numbering mismatch. Expected [1, 2, 3, 1, 2, 3, 1, 2, 3], got {stage_numbers}"

    def test_ros3_gamma_value(self):
        """
        The default output contains the Ros3 gamma value.

        **Validates: Requirements 8.1**
        """
        mech = _prepare_mechanism()
        code = _generate_header_content(mech)

        # The Ros3 gamma is stored as 0.435866521508459 in the tableau,
        # and emitted using :.17g formatting. Verify the value appears in
        # the generated code as the 'g' constant.
        ros3_gamma = SOLVER_COEFFICIENTS["ros3"].Gamma[0]
        gamma_str = f"{ros3_gamma:.17g}"
        assert gamma_str in code, (
            f"Expected Ros3 gamma value '{gamma_str}' not found in generated code. " "The default solver output may have changed."
        )

    def test_ros3_cbrt_step_control(self):
        """
        The default Ros3 output uses Kokkos::cbrt for step control (ELO=3).

        **Validates: Requirements 8.1**
        """
        mech = _prepare_mechanism()
        code = _generate_header_content(mech)

        # ELO=3 means exponent = 1/3, implemented as cbrt
        assert "Kokkos::cbrt(err_norm)" in code, (
            "Expected 'Kokkos::cbrt(err_norm)' in step control for Ros3 (ELO=3). " "The default solver output may have changed."
        )

        # Verify the complete factor computation line
        factor_pattern = re.compile(r"double factor = safety / Kokkos::cbrt\(err_norm\)")
        assert factor_pattern.search(code) is not None, (
            "Expected 'double factor = safety / Kokkos::cbrt(err_norm)' " "in step control for Ros3 (ELO=3)."
        )

    def test_ros3_three_stage_substitution_blocks(self):
        """
        The default output contains forward/backward substitution blocks for
        all 3 Ros3 stages (K1, K2, K3 variable declarations).

        **Validates: Requirements 8.1**
        """
        mech = _prepare_mechanism()
        code = _generate_header_content(mech)

        N = len(mech.species)  # 3 species

        # Verify K stage variables exist for all 3 stages
        for stage in range(1, 4):
            for species_idx in range(N):
                k_var = f"K{stage}_{species_idx}"
                assert k_var in code, (
                    f"Expected stage variable '{k_var}' not found in generated code. "
                    f"Ros3 should have 3 complete stage computation blocks."
                )

        # Verify no K4 variables exist (would indicate a different solver)
        assert "K4_0" not in code, (
            "Found K4_0 in default output — this suggests a 4+ stage solver, " "not the expected Ros3 (3 stages)."
        )

    def test_ros3_solver_comment(self):
        """
        The generated header contains a comment identifying the Ros3 solver.

        **Validates: Requirements 8.1**
        """
        mech = _prepare_mechanism()
        code = _generate_header_content(mech)

        # The code emits a comment with the solver name and characteristics
        assert "ROS-3" in code, "Expected 'ROS-3' identifier in generated code comment."
        assert "3-stage" in code, "Expected '3-stage' descriptor in generated code comment."
