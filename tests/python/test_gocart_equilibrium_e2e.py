"""End-to-end compilation test: GOCART with EQUILIBRIUM produces valid C++ header.

This integration test compiles the GOCART mechanism (26 species, with EQUILIBRIUM block)
through the full MKPP pipeline and verifies the generated C++ header is valid.

Validates: Requirements 1-5
"""

import re
import tempfile
from pathlib import Path

import pytest
from mkpp.codegen import generate_headers
from mkpp.parser import load_mechanism

# ---------------------------------------------------------------------------
# Path to the GOCART mechanism YAML
# ---------------------------------------------------------------------------
GOCART_PATH = Path(__file__).resolve().parents[2] / "mechanisms" / "gocart.yaml"


@pytest.fixture(scope="module")
def gocart_header_content() -> str:
    """Load GOCART mechanism and generate the C++ header through the full pipeline."""
    if not GOCART_PATH.exists():
        pytest.skip(f"GOCART mechanism file not found at {GOCART_PATH}")

    mech = load_mechanism(str(GOCART_PATH))

    with tempfile.TemporaryDirectory() as tmpdir:
        results = generate_headers(mech, out_dir=tmpdir, solver_name="ros3")
        header_path = Path(results["header"])
        assert header_path.exists(), f"Generated header not found at {header_path}"
        return header_path.read_text()


@pytest.fixture(scope="module")
def gocart_mechanism():
    """Load the GOCART mechanism definition."""
    if not GOCART_PATH.exists():
        pytest.skip(f"GOCART mechanism file not found at {GOCART_PATH}")
    return load_mechanism(str(GOCART_PATH))


class TestGocartCompilesWithEquilibrium:
    """Test that GOCART mechanism with EQUILIBRIUM block compiles to a valid header."""

    def test_header_file_produced(self, gocart_header_content):
        """Verify the output header file exists and is non-empty."""
        assert len(gocart_header_content) > 0, "Generated header is empty"

    def test_equilibrium_input_enum(self, gocart_header_content):
        """Verify the header contains the EquilibriumInput enum."""
        assert "enum class EquilibriumInput" in gocart_header_content, "EquilibriumInput enum not found in generated header"
        assert "Temperature = 0" in gocart_header_content
        assert "RelativeHumidity = 1" in gocart_header_content

    def test_compute_equilibrium_partition_function(self, gocart_header_content):
        """Verify the header contains the compute_equilibrium_partition function."""
        assert (
            "compute_equilibrium_partition" in gocart_header_content
        ), "compute_equilibrium_partition function not found in generated header"

    def test_temp_in_function_signatures(self, gocart_header_content):
        """Verify 'const double temp' appears in function signatures."""
        assert "const double temp" in gocart_header_content, "'const double temp' not found in generated function signatures"

    def test_check_mass_balance_diagnostic(self, gocart_header_content):
        """Verify check_mass_balance is emitted under MKPP_DIAGNOSTICS."""
        assert "check_mass_balance" in gocart_header_content, "check_mass_balance diagnostic function not found"
        # Verify it's inside the MKPP_DIAGNOSTICS guard
        diag_start = gocart_header_content.index("#ifdef MKPP_DIAGNOSTICS")
        diag_end = gocart_header_content.index("#endif // MKPP_DIAGNOSTICS")
        diagnostics_section = gocart_header_content[diag_start:diag_end]
        assert "check_mass_balance" in diagnostics_section

    def test_tanh_in_equilibrium_expressions(self, gocart_header_content):
        """Verify tanh appears in the generated code (regime blending expressions)."""
        assert "tanh" in gocart_header_content, "tanh not found - equilibrium regime blending should use tanh"

    def test_exp_in_vant_hoff_constants(self, gocart_header_content):
        """Verify exp appears in the generated code (van't Hoff temperature dependence)."""
        assert "exp" in gocart_header_content, "exp not found - van't Hoff equilibrium constants should use exp()"

    def test_no_rate_n_for_equilibrium_species(self, gocart_header_content):
        """Property 10: No Rate_N symbols for equilibrium-covered species.

        The equilibrium species (NH3, NH4a, HNO3, NO3an1-3, SO4) should not
        use Rate_N/jvals mappings. Only photolysis reactions should use jvals.
        """
        # Rate_N pattern maps to jvals[N] in the emitted code
        # The equilibrium species should NOT produce Rate_N references
        # But jvals[0] should still exist for the photolysis reaction (H2O2 -> 2 OH)
        rate_n_matches = re.findall(r"Rate_\d+", gocart_header_content)
        assert len(rate_n_matches) == 0, (
            f"Found Rate_N symbols in generated code: {rate_n_matches}. "
            "Equilibrium species should not use opaque Rate_N symbols."
        )

    def test_basic_cpp_structure(self, gocart_header_content):
        """Verify basic C++ structure is valid."""
        assert "#pragma once" in gocart_header_content
        assert "#include <Kokkos_Core.hpp>" in gocart_header_content
        assert "namespace mkpp" in gocart_header_content
        assert "KOKKOS_INLINE_FUNCTION" in gocart_header_content


class TestGocartEquilibriumNoGpuViolations:
    """Verify the generated functions have no forbidden GPU keywords in derivative code."""

    def test_compute_rates_no_forbidden_keywords(self, gocart_header_content):
        """Verify compute_rates has no if/else/switch/new/malloc/throw."""
        # Extract the compute_rates function body
        rates_start = gocart_header_content.index("void compute_rates(")
        # Find the closing brace for this function (count braces)
        body_start = gocart_header_content.index("{", rates_start)
        rates_body = _extract_function_body(gocart_header_content, body_start)

        _assert_no_forbidden_keywords(rates_body, "compute_rates")

    def test_compute_jacobian_no_forbidden_keywords(self, gocart_header_content):
        """Verify compute_jacobian has no if/else/switch/new/malloc/throw."""
        jac_start = gocart_header_content.index("void compute_jacobian(")
        body_start = gocart_header_content.index("{", jac_start)
        jac_body = _extract_function_body(gocart_header_content, body_start)

        _assert_no_forbidden_keywords(jac_body, "compute_jacobian")


class TestGocartEquilibriumBackwardCompat:
    """Verify the GOCART mechanism still has all 26 species and kinetic reactions."""

    def test_gocart_has_26_species(self, gocart_mechanism):
        """Verify the loaded GOCART mechanism still has all 26 species."""
        assert len(gocart_mechanism.species) == 26, f"GOCART should have 26 species, got {len(gocart_mechanism.species)}"

    def test_kinetic_reactions_preserved(self, gocart_mechanism):
        """Verify kinetic reactions are preserved alongside the equilibrium block."""
        # GOCART has multiple kinetic reactions (ARRHENIUS, HETEROGENEOUS, PHOTOLYSIS)
        assert len(gocart_mechanism.reactions) > 0, "GOCART should still have kinetic reactions"

        # Check specific reaction types are present
        reaction_types = {r.reaction_type for r in gocart_mechanism.reactions}
        assert "ARRHENIUS" in reaction_types, "ARRHENIUS reactions should be preserved"
        assert "HETEROGENEOUS" in reaction_types, "HETEROGENEOUS reactions should be preserved"
        assert "PHOTOLYSIS" in reaction_types, "PHOTOLYSIS reactions should be preserved"

    def test_equilibrium_block_present(self, gocart_mechanism):
        """Verify the EQUILIBRIUM block is correctly parsed."""
        assert len(gocart_mechanism.equilibrium_reactions) == 1, "GOCART should have exactly 1 EQUILIBRIUM block"
        eq = gocart_mechanism.equilibrium_reactions[0]
        assert eq.system == "NH4_NO3_SO4"

    def test_equilibrium_species_in_mechanism(self, gocart_mechanism):
        """Verify all equilibrium-participating species are in the mechanism."""
        species_names = {s.name for s in gocart_mechanism.species}
        equilibrium_species = {"NH3", "NH4a", "HNO3", "NO3an1", "NO3an2", "NO3an3", "SO2", "SO4"}
        missing = equilibrium_species - species_names
        assert not missing, f"Equilibrium species missing from mechanism: {missing}"

    def test_num_species_in_header(self, gocart_header_content):
        """Verify NUM_SPECIES = 26 in the generated header."""
        assert "NUM_SPECIES = 26" in gocart_header_content, "Generated header should have NUM_SPECIES = 26 for GOCART"


# ---------------------------------------------------------------------------
# Helper functions
# ---------------------------------------------------------------------------


def _extract_function_body(code: str, open_brace_idx: int) -> str:
    """Extract the function body between matching braces starting at open_brace_idx."""
    depth = 0
    start = open_brace_idx
    for i in range(open_brace_idx, len(code)):
        if code[i] == "{":
            depth += 1
        elif code[i] == "}":
            depth -= 1
            if depth == 0:
                return code[start : i + 1]
    return code[start:]  # fallback if braces don't match


def _assert_no_forbidden_keywords(code_body: str, function_name: str):
    """Assert that a code body contains no GPU-unsafe keywords."""
    # These keywords indicate branching, heap allocation, or exceptions
    # that are forbidden in KOKKOS_INLINE_FUNCTION GPU kernels
    forbidden = ["\\bif\\b", "\\belse\\b", "\\bswitch\\b", "\\bnew\\b", "\\bmalloc\\b", "\\bthrow\\b"]

    for pattern in forbidden:
        matches = re.findall(pattern, code_body)
        if matches:
            # Get a snippet around the first match for debugging
            keyword = pattern.replace("\\b", "")
            first_match = re.search(pattern, code_body)
            context_start = max(0, first_match.start() - 40)
            context_end = min(len(code_body), first_match.end() + 40)
            context = code_body[context_start:context_end]
            pytest.fail(f"Forbidden keyword '{keyword}' found in {function_name}. " f"Context: ...{context}...")
