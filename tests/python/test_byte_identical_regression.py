"""
Byte-identical regression tests for the Jinja2 template code generation pipeline.

Verifies that the template engine produces deterministic, self-consistent output
for known mechanisms. Each test generates headers twice and asserts exact string
equality, confirming that the pipeline is fully deterministic.

Additionally, structural assertions verify the output contains expected patterns
specific to each mechanism, catching regressions in template rendering logic.

**Validates: Requirements 5.1, 5.2, 5.3**
"""

import tempfile
from pathlib import Path

import pytest
from mkpp.codegen import generate_headers
from mkpp.parser import load_mechanism

# ---------------------------------------------------------------------------
# Paths to mechanism YAML files
# ---------------------------------------------------------------------------
MECHANISMS_DIR = Path(__file__).resolve().parents[2] / "mechanisms"
CHAPMAN_PATH = MECHANISMS_DIR / "chapman.yaml"
GOCART_PATH = MECHANISMS_DIR / "gocart.yaml"


# ---------------------------------------------------------------------------
# Helper: generate header content for a mechanism
# ---------------------------------------------------------------------------


def _generate_header(mech, solver_name: str = "ros3", adjoint: bool = False) -> str:
    """Generate a header and return the full text content."""
    with tempfile.TemporaryDirectory() as tmpdir:
        result = generate_headers(mech, out_dir=tmpdir, solver_name=solver_name, adjoint=adjoint)
        with open(result["header"]) as f:
            return f.read()


# ---------------------------------------------------------------------------
# Test: Chapman mechanism byte-identical regression
# ---------------------------------------------------------------------------


class TestChapmanByteIdentical:
    """Verify Chapman mechanism produces byte-identical output across generations."""

    @pytest.fixture(scope="class")
    def chapman_mechanism(self):
        """Load the Chapman mechanism."""
        if not CHAPMAN_PATH.exists():
            pytest.skip(f"Chapman mechanism file not found at {CHAPMAN_PATH}")
        return load_mechanism(str(CHAPMAN_PATH))

    def test_chapman_deterministic_output(self, chapman_mechanism):
        """Generate Chapman header twice and assert exact string equality.

        **Validates: Requirement 5.1**
        """
        output_1 = _generate_header(chapman_mechanism)
        output_2 = _generate_header(chapman_mechanism)

        assert output_1 == output_2, (
            "Chapman header generation is non-deterministic. " "Two successive generations produced different output."
        )

    def test_chapman_structural_invariants(self, chapman_mechanism):
        """Verify Chapman header contains expected structural patterns.

        **Validates: Requirement 5.1**
        """
        content = _generate_header(chapman_mechanism)

        # Basic C++ structure
        assert "#pragma once" in content
        assert "#include <Kokkos_Core.hpp>" in content
        assert "namespace mkpp" in content

        # Chapman has 4 species
        assert "NUM_SPECIES = 4" in content

        # Expected function signatures
        assert "compute_rates" in content
        assert "compute_jacobian" in content
        assert "integrate" in content
        assert "integrate_with_reduction" in content

        # Solver comment (ros3 default)
        assert "ROS-3" in content
        assert "3-stage" in content

        # Stage markers (3 stages x 2 integration functions)
        assert "// --- Stage 1 ---" in content
        assert "// --- Stage 2 ---" in content
        assert "// --- Stage 3 ---" in content

        # LU factorization variables (mechanism-specific)
        assert "double W_" in content
        assert "double U_" in content

    def test_chapman_non_empty_output(self, chapman_mechanism):
        """Verify Chapman header is non-empty and reasonably sized.

        **Validates: Requirement 5.1**
        """
        content = _generate_header(chapman_mechanism)

        # Chapman with 4 species should produce a non-trivial header
        assert len(content) > 5000, (
            f"Chapman header is unexpectedly small ({len(content)} chars). " "Expected > 5000 chars for a 4-species mechanism."
        )


# ---------------------------------------------------------------------------
# Test: GOCART mechanism byte-identical regression
# ---------------------------------------------------------------------------


class TestGocartByteIdentical:
    """Verify GOCART mechanism produces byte-identical output across generations."""

    @pytest.fixture(scope="class")
    def gocart_mechanism(self):
        """Load the GOCART mechanism."""
        if not GOCART_PATH.exists():
            pytest.skip(f"GOCART mechanism file not found at {GOCART_PATH}")
        return load_mechanism(str(GOCART_PATH))

    def test_gocart_deterministic_output(self, gocart_mechanism):
        """Generate GOCART header twice and assert exact string equality.

        **Validates: Requirement 5.2**
        """
        output_1 = _generate_header(gocart_mechanism)
        output_2 = _generate_header(gocart_mechanism)

        assert output_1 == output_2, (
            "GOCART header generation is non-deterministic. " "Two successive generations produced different output."
        )

    def test_gocart_structural_invariants(self, gocart_mechanism):
        """Verify GOCART header contains expected structural patterns.

        **Validates: Requirement 5.2**
        """
        content = _generate_header(gocart_mechanism)

        # Basic C++ structure
        assert "#pragma once" in content
        assert "#include <Kokkos_Core.hpp>" in content
        assert "namespace mkpp" in content

        # GOCART has 26 species
        assert "NUM_SPECIES = 26" in content

        # Expected function signatures
        assert "compute_rates" in content
        assert "compute_jacobian" in content
        assert "integrate" in content
        assert "integrate_with_reduction" in content

        # GOCART has equilibrium
        assert "compute_equilibrium_partition" in content

        # Solver comment (ros3 default)
        assert "ROS-3" in content

    def test_gocart_non_empty_output(self, gocart_mechanism):
        """Verify GOCART header is non-empty and appropriately large.

        **Validates: Requirement 5.2**
        """
        content = _generate_header(gocart_mechanism)

        # GOCART with 26 species produces a large header
        assert len(content) > 100000, (
            f"GOCART header is unexpectedly small ({len(content)} chars). "
            "Expected > 100000 chars for a 26-species mechanism with equilibrium."
        )


# ---------------------------------------------------------------------------
# Test: Chapman with adjoint mode byte-identical regression
# ---------------------------------------------------------------------------


class TestChapmanAdjointByteIdentical:
    """Verify Chapman+adjoint produces byte-identical output across generations."""

    @pytest.fixture(scope="class")
    def chapman_mechanism(self):
        """Load the Chapman mechanism."""
        if not CHAPMAN_PATH.exists():
            pytest.skip(f"Chapman mechanism file not found at {CHAPMAN_PATH}")
        return load_mechanism(str(CHAPMAN_PATH))

    def test_chapman_adjoint_deterministic_output(self, chapman_mechanism):
        """Generate Chapman+adjoint header twice and assert exact string equality.

        **Validates: Requirement 5.3**
        """
        output_1 = _generate_header(chapman_mechanism, adjoint=True)
        output_2 = _generate_header(chapman_mechanism, adjoint=True)

        assert output_1 == output_2, (
            "Chapman+adjoint header generation is non-deterministic. " "Two successive generations produced different output."
        )

    def test_chapman_adjoint_structural_invariants(self, chapman_mechanism):
        """Verify Chapman+adjoint header contains adjoint-specific patterns.

        **Validates: Requirement 5.3**
        """
        content = _generate_header(chapman_mechanism, adjoint=True)

        # Basic C++ structure
        assert "#pragma once" in content
        assert "#include <Kokkos_Core.hpp>" in content
        assert "namespace mkpp" in content

        # Chapman has 4 species
        assert "NUM_SPECIES = 4" in content

        # Standard functions present
        assert "compute_rates" in content
        assert "compute_jacobian" in content
        assert "integrate" in content
        assert "integrate_with_reduction" in content

        # Adjoint-specific functions and structures
        assert "integrate_fwd_checkpoint" in content
        assert "integrate_adj" in content
        assert "integrate_tlm" in content
        assert "compute_adjoint" in content
        assert "compute_tlm" in content

        # CheckpointBuffer struct for adjoint
        assert "struct CheckpointBuffer" in content
        assert "static constexpr int MAX_STEPS = 200;" in content

    def test_chapman_adjoint_larger_than_non_adjoint(self, chapman_mechanism):
        """Verify adjoint output is larger than non-adjoint (more functions).

        **Validates: Requirement 5.3**
        """
        content_standard = _generate_header(chapman_mechanism, adjoint=False)
        content_adjoint = _generate_header(chapman_mechanism, adjoint=True)

        assert len(content_adjoint) > len(content_standard), (
            "Adjoint header should be larger than standard header due to "
            "additional functions (integrate_fwd_checkpoint, integrate_adj, integrate_tlm)."
        )

    def test_chapman_adjoint_non_empty_output(self, chapman_mechanism):
        """Verify Chapman+adjoint header is non-empty and appropriately sized.

        **Validates: Requirement 5.3**
        """
        content = _generate_header(chapman_mechanism, adjoint=True)

        # Adjoint adds ~3 more functions, so header should be substantially larger
        assert len(content) > 20000, (
            f"Chapman+adjoint header is unexpectedly small ({len(content)} chars). "
            "Expected > 20000 chars for a 4-species mechanism with adjoint."
        )


# ---------------------------------------------------------------------------
# Cross-mechanism consistency test
# ---------------------------------------------------------------------------


class TestCrossMechanismConsistency:
    """Verify consistent output properties across all tested mechanisms."""

    @pytest.fixture(scope="class")
    def chapman_mechanism(self):
        if not CHAPMAN_PATH.exists():
            pytest.skip(f"Chapman mechanism file not found at {CHAPMAN_PATH}")
        return load_mechanism(str(CHAPMAN_PATH))

    @pytest.fixture(scope="class")
    def gocart_mechanism(self):
        if not GOCART_PATH.exists():
            pytest.skip(f"GOCART mechanism file not found at {GOCART_PATH}")
        return load_mechanism(str(GOCART_PATH))

    def test_adjoint_false_excludes_adjoint_functions(self, chapman_mechanism):
        """When adjoint=False, no adjoint-specific functions should appear.

        **Validates: Requirements 5.1, 5.3**
        """
        content = _generate_header(chapman_mechanism, adjoint=False)

        assert "integrate_fwd_checkpoint" not in content
        assert "integrate_adj" not in content
        assert "integrate_tlm" not in content
        assert "CheckpointBuffer" not in content

    def test_different_mechanisms_produce_different_output(self, chapman_mechanism, gocart_mechanism):
        """Different mechanisms must produce different headers.

        **Validates: Requirements 5.1, 5.2**
        """
        chapman_output = _generate_header(chapman_mechanism)
        gocart_output = _generate_header(gocart_mechanism)

        assert chapman_output != gocart_output, (
            "Chapman and GOCART mechanisms produced identical headers. " "This indicates a bug in the template rendering pipeline."
        )
