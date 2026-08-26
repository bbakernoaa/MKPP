"""
Integration tests for each solver variant.

Exercises the full code generation pipeline for all 5 Rosenbrock solvers (ros2, ros3,
ros4, rodas3, rodas4), verifying:
- Generated headers are non-empty and well-formed (proper C++ structure)
- Stage counts match the tableau definition
- Gamma[0] value matches the tableau
- ELO exponent comment is correct
- Basic syntactic correctness (matching braces, no unclosed strings, proper structure)

**Validates: Requirements 3.1, 7.1, 7.2, 7.3**
"""

import re

import pytest

from mkpp.codegen import SOLVER_COEFFICIENTS, generate_headers
from mkpp.lowering import compute_symbolic_lu_decomposition, prepare_unified_jacobian
from mkpp.model import (
    AerosolRepresentation,
    MechanismDefinition,
    PhaseMode,
    ReactionDefinition,
    SpeciesDefinition,
)

# ---------------------------------------------------------------------------
# Test mechanism builder
# ---------------------------------------------------------------------------


def _build_test_mechanism():
    """Build a 3-species mechanism with a non-trivial Jacobian for integration testing."""
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
        name="integration_test_mech",
        description="Mechanism for solver integration testing",
        aerosol_representation=AerosolRepresentation.BULK,
        species=[sp_a, sp_b, sp_c],
        phases=[],
        reactions=[rxn1, rxn2],
    )


def _generate_for_solver(solver_name: str, tmp_dir: str) -> str:
    """Generate the C++ header for the given solver and return the code as a string."""
    mech = _build_test_mechanism()
    lowering_data = prepare_unified_jacobian(mech)
    plan = compute_symbolic_lu_decomposition(lowering_data["jacobian_matrix"], lowering_data["species_map"])
    mech.metadata = {
        "sympy_metadata": lowering_data,
        "symbolic_lu_plan": plan,
    }

    artifacts = generate_headers(mech, out_dir=tmp_dir, solver_name=solver_name)
    with open(artifacts["header"]) as f:
        return f.read()


# ---------------------------------------------------------------------------
# Integration tests parametrized over all 5 solvers
# ---------------------------------------------------------------------------

ALL_SOLVERS = list(SOLVER_COEFFICIENTS.keys())


@pytest.mark.parametrize("solver_name", ALL_SOLVERS)
class TestSolverIntegration:
    """Full-pipeline integration tests for each Rosenbrock solver variant."""

    def test_generated_file_is_nonempty(self, solver_name: str, tmp_path):
        """Generated header file is non-empty."""
        code = _generate_for_solver(solver_name, str(tmp_path))
        assert len(code) > 0, f"[{solver_name}] Generated header is empty"

    def test_has_pragma_once(self, solver_name: str, tmp_path):
        """Generated header starts with #pragma once."""
        code = _generate_for_solver(solver_name, str(tmp_path))
        assert "#pragma once" in code, f"[{solver_name}] Missing #pragma once include guard"

    def test_has_kokkos_include(self, solver_name: str, tmp_path):
        """Generated header includes Kokkos_Core.hpp."""
        code = _generate_for_solver(solver_name, str(tmp_path))
        assert "#include <Kokkos_Core.hpp>" in code, f"[{solver_name}] Missing Kokkos_Core.hpp include"

    def test_has_class_structure(self, solver_name: str, tmp_path):
        """Generated header contains a class definition."""
        code = _generate_for_solver(solver_name, str(tmp_path))
        # Look for class or struct definition
        assert re.search(r"\b(class|struct)\s+\w+", code), f"[{solver_name}] No class/struct definition found in generated header"

    def test_has_template_declarations(self, solver_name: str, tmp_path):
        """Generated header contains template declarations for integrate functions."""
        code = _generate_for_solver(solver_name, str(tmp_path))
        assert "template" in code, f"[{solver_name}] No template declarations found"

    def test_stage_count_matches_tableau(self, solver_name: str, tmp_path):
        """
        Stage comments in generated code match the tableau's stage count.

        The generated code emits '// --- Stage N ---' comments for each stage in
        both integrate() and integrate_with_reduction().

        **Validates: Requirements 3.1**
        """
        tableau = SOLVER_COEFFICIENTS[solver_name]
        code = _generate_for_solver(solver_name, str(tmp_path))

        stage_comments = re.findall(r"// --- Stage \d+ ---", code)
        # Expect stages in both integrate() and integrate_with_reduction()
        # Forward, reduction, and compiler-guarded checkpoint variants are
        # emitted into the stable mechanism header.
        expected_total = 3 * tableau.stages
        assert len(stage_comments) == expected_total, (
            f"[{solver_name}] Expected {expected_total} stage comments "
            f"(3 functions x {tableau.stages} stages), found {len(stage_comments)}"
        )

    def test_gamma_value_matches_tableau(self, solver_name: str, tmp_path):
        """
        The emitted gamma constant matches Gamma[0] from the tableau.

        **Validates: Requirements 7.2, 7.3**
        """
        tableau = SOLVER_COEFFICIENTS[solver_name]
        code = _generate_for_solver(solver_name, str(tmp_path))

        # Gamma[0] appears as: const double g = <value>;
        g_match = re.search(r"const double g = ([^;]+);", code)
        assert g_match is not None, f"[{solver_name}] 'const double g = ...' not found in generated code"
        g_value = float(g_match.group(1))
        expected_g = tableau.Gamma[0]
        rel_err = abs(g_value - expected_g) / abs(expected_g) if expected_g != 0 else abs(g_value)
        assert rel_err < 1e-14, (
            f"[{solver_name}] Gamma[0] mismatch: expected {expected_g:.17g}, " f"got {g_value:.17g} (rel_err={rel_err:.2e})"
        )

    def test_elo_exponent_comment_correct(self, solver_name: str, tmp_path):
        """
        The step-size control comment emits the correct ELO order and exponent.

        **Validates: Requirements 7.2, 7.3**
        """
        tableau = SOLVER_COEFFICIENTS[solver_name]
        code = _generate_for_solver(solver_name, str(tmp_path))
        expected_elo = int(tableau.ELO)
        expected_exponent = 1.0 / tableau.ELO

        # Match: // Step Size Control (order N: exponent = 1/N = <value>)
        comment_pattern = re.compile(r"// Step Size Control \(order (\d+): exponent = 1/(\d+) = ([\d.e+-]+)\)")
        matches = comment_pattern.findall(code)
        assert len(matches) >= 1, f"[{solver_name}] No step-size control comment found"

        order_str, divisor_str, exponent_str = matches[0]
        assert int(order_str) == expected_elo, f"[{solver_name}] ELO order mismatch: expected {expected_elo}, got {order_str}"
        assert int(divisor_str) == expected_elo, f"[{solver_name}] ELO divisor mismatch: expected {expected_elo}, got {divisor_str}"
        actual_exponent = float(exponent_str)
        assert abs(actual_exponent - expected_exponent) < 1e-10, (
            f"[{solver_name}] Exponent value mismatch: " f"expected {expected_exponent}, got {actual_exponent}"
        )

    def test_matching_braces(self, solver_name: str, tmp_path):
        """
        Generated code has balanced curly braces (no unclosed blocks).

        Basic syntactic correctness check.
        """
        code = _generate_for_solver(solver_name, str(tmp_path))
        open_braces = code.count("{")
        close_braces = code.count("}")
        assert open_braces == close_braces, f"[{solver_name}] Unbalanced braces: {open_braces} open vs {close_braces} close"

    def test_no_unclosed_strings(self, solver_name: str, tmp_path):
        """
        Generated code has no unclosed string literals.

        Checks that double-quote characters are balanced (ignoring those in comments).
        """
        code = _generate_for_solver(solver_name, str(tmp_path))
        # Remove single-line comments to avoid false positives from comment strings
        code_no_comments = re.sub(r"//[^\n]*", "", code)
        # Count double quotes (should be even for properly paired strings)
        quote_count = code_no_comments.count('"')
        assert quote_count % 2 == 0, (
            f"[{solver_name}] Odd number of double-quote characters ({quote_count}): " f"possible unclosed string literal"
        )

    def test_no_obviously_broken_syntax(self, solver_name: str, tmp_path):
        """
        Generated code has no obviously broken syntax patterns.

        Checks for common code generation errors.
        """
        code = _generate_for_solver(solver_name, str(tmp_path))

        # No empty statements that look like bugs (bare semicolons on their own line)
        # (excluding valid patterns like for(;;) or empty bodies)
        lines = code.split("\n")
        for i, line in enumerate(lines):
            stripped = line.strip()
            # A line that is just ';' with no context is suspicious
            if stripped == ";":
                # Check if previous line ends with ')' (e.g., while(...)\n;) which is valid
                prev = lines[i - 1].strip() if i > 0 else ""
                if not prev.endswith(")"):
                    pytest.fail(f"[{solver_name}] Suspicious bare semicolon on line {i+1}")

        # No consecutive closing braces without content in between
        # (this catches accidental empty blocks from bad generation)
        assert "{{" not in code.replace("{ {", ""), f"[{solver_name}] Found '{{{{' pattern suggesting malformed block structure"

    def test_integrate_function_present(self, solver_name: str, tmp_path):
        """Generated code contains both integrate() and integrate_with_reduction()."""
        code = _generate_for_solver(solver_name, str(tmp_path))

        integrate_pattern = re.compile(r"\bvoid\s+integrate\s*\(")
        assert integrate_pattern.search(code), f"[{solver_name}] integrate() function not found"

        reduction_pattern = re.compile(r"\bvoid\s+integrate_with_reduction\s*\(")
        assert reduction_pattern.search(code), f"[{solver_name}] integrate_with_reduction() function not found"

    def test_kokkos_inline_function_present(self, solver_name: str, tmp_path):
        """Generated code uses KOKKOS_INLINE_FUNCTION annotation."""
        code = _generate_for_solver(solver_name, str(tmp_path))
        assert "KOKKOS_INLINE_FUNCTION" in code, f"[{solver_name}] KOKKOS_INLINE_FUNCTION annotation not found"

    def test_stage_variables_declared(self, solver_name: str, tmp_path):
        """
        Each stage has its K variables declared (K1_0, K2_0, etc.).

        **Validates: Requirements 3.1**
        """
        tableau = SOLVER_COEFFICIENTS[solver_name]
        code = _generate_for_solver(solver_name, str(tmp_path))

        for stage in range(1, tableau.stages + 1):
            k_var = f"K{stage}_0"
            assert k_var in code, f"[{solver_name}] Stage variable '{k_var}' not found in generated code"

    def test_no_dynamic_allocations(self, solver_name: str, tmp_path):
        """
        Generated code contains no dynamic memory allocations.

        **Validates: Requirements 7.2, 7.3 (GPU-safe code for all solvers)**
        """
        code = _generate_for_solver(solver_name, str(tmp_path))
        assert "new " not in code, f"[{solver_name}] Contains 'new ' (dynamic allocation)"
        assert "malloc(" not in code, f"[{solver_name}] Contains 'malloc(' (dynamic allocation)"
        assert "std::vector" not in code, f"[{solver_name}] Contains 'std::vector'"

    def test_solution_update_uses_m_coefficients(self, solver_name: str, tmp_path):
        """
        Solution update line references the correct number of K stage variables.

        **Validates: Requirements 3.1, 7.2**
        """
        tableau = SOLVER_COEFFICIENTS[solver_name]
        code = _generate_for_solver(solver_name, str(tmp_path))

        # Find state update lines
        state_update_lines = [line.strip() for line in code.split("\n") if "state(" in line and "+=" in line]
        assert len(state_update_lines) > 0, f"[{solver_name}] No state update lines found"

        # Count how many non-zero M coefficients there are
        non_zero_m = sum(1 for m in tableau.M if m != 0.0)

        # The first state update line should reference K variables
        first_update = state_update_lines[0]
        k_refs = re.findall(r"K\d+_\d+", first_update)
        assert len(k_refs) == non_zero_m, (
            f"[{solver_name}] Expected {non_zero_m} K-variable references in "
            f"solution update, found {len(k_refs)} in: {first_update}"
        )

    def test_error_estimate_present(self, solver_name: str, tmp_path):
        """Generated code computes error estimate (yerr variables)."""
        code = _generate_for_solver(solver_name, str(tmp_path))
        assert "yerr_i" in code or "double yerr" in code, f"[{solver_name}] No error estimate computation found"
