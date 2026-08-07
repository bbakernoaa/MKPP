"""Unit tests for scaffold block macros (Task 2.6).

Tests render each Jinja2 macro with minimal context and verify expected
C++ patterns are present in the output.

Macros tested:
  - w_matrix.j2        (emit_w_matrix)
  - lu_factorize.j2    (emit_lu_factorize)
  - lu_solve_forward.j2 (emit_forward_sub)
  - lu_solve_backward.j2 (emit_backward_sub)
  - lu_solve_transpose.j2 (emit_transpose_solve)

Requirements: 9.3
"""

import pytest
from mkpp.template_engine import TemplateEngine

# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------


@pytest.fixture
def engine():
    """TemplateEngine with default template directory."""
    return TemplateEngine()


def render_macro(engine, macro_import, macro_call, context):
    """Render a macro by creating a wrapper template string.

    Parameters
    ----------
    engine : TemplateEngine
        The template engine instance.
    macro_import : str
        Jinja2 import statement (e.g. '{%- from "macros/w_matrix.j2" import emit_w_matrix -%}')
    macro_call : str
        Jinja2 macro call expression.
    context : dict
        Variables passed to the template.

    Returns
    -------
    str
        Rendered output.
    """
    wrapper = f"{macro_import}\n{macro_call}"
    template = engine.env.from_string(wrapper)
    return template.render(**context)


# ---------------------------------------------------------------------------
# Tests: w_matrix.j2
# ---------------------------------------------------------------------------


class TestWMatrixMacro:
    """Tests for emit_w_matrix macro (Requirements 3.1, 3.6, 3.7)."""

    def test_emits_diagonal_with_jacobian(self, engine):
        """Diagonal entry with non-zero Jacobian emits W_i_i = inv_var - J_i_i."""
        result = render_macro(
            engine,
            '{%- from "macros/w_matrix.j2" import emit_w_matrix -%}',
            "{{ emit_w_matrix(needed_w, non_zero_jac_set, inv_var, N) }}",
            {
                "needed_w": [(0, 0)],
                "non_zero_jac_set": {(0, 0)},
                "inv_var": "inv_g_h",
                "N": 2,
            },
        )
        assert "double W_0_0 = inv_g_h - J_0_0;" in result

    def test_emits_diagonal_without_jacobian(self, engine):
        """Diagonal entry without Jacobian emits W_i_i = inv_var."""
        result = render_macro(
            engine,
            '{%- from "macros/w_matrix.j2" import emit_w_matrix -%}',
            "{{ emit_w_matrix(needed_w, non_zero_jac_set, inv_var, N) }}",
            {
                "needed_w": [(1, 1)],
                "non_zero_jac_set": set(),
                "inv_var": "inv_g_h",
                "N": 2,
            },
        )
        assert "double W_1_1 = inv_g_h;" in result

    def test_emits_off_diagonal_with_jacobian(self, engine):
        """Off-diagonal entry with non-zero Jacobian emits W_i_j = -J_i_j."""
        result = render_macro(
            engine,
            '{%- from "macros/w_matrix.j2" import emit_w_matrix -%}',
            "{{ emit_w_matrix(needed_w, non_zero_jac_set, inv_var, N) }}",
            {
                "needed_w": [(0, 1)],
                "non_zero_jac_set": {(0, 1)},
                "inv_var": "inv_g_h",
                "N": 2,
            },
        )
        assert "double W_0_1 = -J_0_1;" in result

    def test_emits_off_diagonal_without_jacobian(self, engine):
        """Off-diagonal entry without Jacobian emits W_i_j = 0.0."""
        result = render_macro(
            engine,
            '{%- from "macros/w_matrix.j2" import emit_w_matrix -%}',
            "{{ emit_w_matrix(needed_w, non_zero_jac_set, inv_var, N) }}",
            {
                "needed_w": [(0, 1)],
                "non_zero_jac_set": set(),
                "inv_var": "inv_g_h",
                "N": 2,
            },
        )
        assert "double W_0_1 = 0.0;" in result

    def test_reduction_mode_diagonal(self, engine):
        """Reduction mode diagonal emits active[i] ? (inv_var - J_i_i) : inv_var."""
        result = render_macro(
            engine,
            '{%- from "macros/w_matrix.j2" import emit_w_matrix -%}',
            "{{ emit_w_matrix(needed_w, non_zero_jac_set, inv_var, N, is_reduction=true) }}",
            {
                "needed_w": [(0, 0)],
                "non_zero_jac_set": {(0, 0)},
                "inv_var": "inv_g_h",
                "N": 2,
            },
        )
        assert "active[0]" in result
        assert "inv_g_h - J_0_0" in result
        assert ": inv_g_h;" in result

    def test_reduction_mode_off_diagonal(self, engine):
        """Reduction mode off-diagonal emits active[i] ? (-J_i_j) : 0.0."""
        result = render_macro(
            engine,
            '{%- from "macros/w_matrix.j2" import emit_w_matrix -%}',
            "{{ emit_w_matrix(needed_w, non_zero_jac_set, inv_var, N, is_reduction=true) }}",
            {
                "needed_w": [(1, 0)],
                "non_zero_jac_set": {(1, 0)},
                "inv_var": "inv_g_h",
                "N": 2,
            },
        )
        assert "active[1]" in result
        assert "-J_1_0" in result
        assert ": 0.0;" in result

    def test_block_boundary_comments(self, engine):
        """Block-boundary comments appear when blocks are provided."""
        result = render_macro(
            engine,
            '{%- from "macros/w_matrix.j2" import emit_w_matrix -%}',
            "{{ emit_w_matrix(needed_w, non_zero_jac_set, inv_var, N, blocks=blocks) }}",
            {
                "needed_w": [(0, 0), (1, 1), (2, 2), (3, 3)],
                "non_zero_jac_set": {(0, 0), (1, 1), (2, 2), (3, 3)},
                "inv_var": "inv_g_h",
                "N": 4,
                "blocks": [
                    {"indices": [0, 1], "species_names": ["A", "B"]},
                    {"indices": [2, 3], "species_names": ["C", "D"]},
                ],
            },
        )
        assert "// Block" in result
        assert "A, B" in result
        assert "C, D" in result

    def test_multiple_entries(self, engine):
        """Multiple W entries are all emitted."""
        result = render_macro(
            engine,
            '{%- from "macros/w_matrix.j2" import emit_w_matrix -%}',
            "{{ emit_w_matrix(needed_w, non_zero_jac_set, inv_var, N) }}",
            {
                "needed_w": [(0, 0), (0, 1), (1, 0), (1, 1)],
                "non_zero_jac_set": {(0, 0), (0, 1), (1, 0), (1, 1)},
                "inv_var": "inv_g_h",
                "N": 2,
            },
        )
        assert "double W_0_0" in result
        assert "double W_0_1" in result
        assert "double W_1_0" in result
        assert "double W_1_1" in result


# ---------------------------------------------------------------------------
# Tests: lu_factorize.j2
# ---------------------------------------------------------------------------


class TestLUFactorizeMacro:
    """Tests for emit_lu_factorize macro (Requirements 3.2, 3.6)."""

    def test_emits_L_entries(self, engine):
        """Emits double L_i_j = expr for L-type entries."""
        result = render_macro(
            engine,
            '{%- from "macros/lu_factorize.j2" import emit_lu_factorize -%}',
            "{{ emit_lu_factorize(lu_expressions) }}",
            {
                "lu_expressions": [
                    {"kind": "L", "i": 1, "j": 0, "expr": "W_1_0 / U_0_0"},
                ],
            },
        )
        assert "double L_1_0 = W_1_0 / U_0_0;" in result

    def test_emits_U_entries(self, engine):
        """Emits double U_i_j = expr for U-type entries."""
        result = render_macro(
            engine,
            '{%- from "macros/lu_factorize.j2" import emit_lu_factorize -%}',
            "{{ emit_lu_factorize(lu_expressions) }}",
            {
                "lu_expressions": [
                    {"kind": "U", "i": 0, "j": 0, "expr": "W_0_0"},
                    {"kind": "U", "i": 1, "j": 1, "expr": "W_1_1 - L_1_0 * U_0_1"},
                ],
            },
        )
        assert "double U_0_0 = W_0_0;" in result
        assert "double U_1_1 = W_1_1 - L_1_0 * U_0_1;" in result

    def test_mixed_L_and_U_entries(self, engine):
        """Both L and U entries are emitted in order."""
        lu_expressions = [
            {"kind": "U", "i": 0, "j": 0, "expr": "W_0_0"},
            {"kind": "L", "i": 1, "j": 0, "expr": "W_1_0 / U_0_0"},
            {"kind": "U", "i": 0, "j": 1, "expr": "W_0_1"},
            {"kind": "U", "i": 1, "j": 1, "expr": "W_1_1 - L_1_0 * U_0_1"},
        ]
        result = render_macro(
            engine,
            '{%- from "macros/lu_factorize.j2" import emit_lu_factorize -%}',
            "{{ emit_lu_factorize(lu_expressions) }}",
            {"lu_expressions": lu_expressions},
        )
        assert "double U_0_0 = W_0_0;" in result
        assert "double L_1_0 = W_1_0 / U_0_0;" in result
        assert "double U_0_1 = W_0_1;" in result
        assert "double U_1_1 = W_1_1 - L_1_0 * U_0_1;" in result

    def test_block_boundary_comments(self, engine):
        """Block-boundary comments appear when blocks are provided."""
        result = render_macro(
            engine,
            '{%- from "macros/lu_factorize.j2" import emit_lu_factorize -%}',
            "{{ emit_lu_factorize(lu_expressions, blocks=blocks) }}",
            {
                "lu_expressions": [
                    {"kind": "U", "i": 0, "j": 0, "expr": "W_0_0"},
                    {"kind": "U", "i": 1, "j": 1, "expr": "W_1_1"},
                    {"kind": "U", "i": 2, "j": 2, "expr": "W_2_2"},
                    {"kind": "U", "i": 3, "j": 3, "expr": "W_3_3"},
                ],
                "blocks": [
                    {"indices": [0, 1], "species_names": ["O", "O3"]},
                    {"indices": [2, 3], "species_names": ["NO", "NO2"]},
                ],
            },
        )
        assert "// Block 0" in result
        assert "O, O3" in result
        assert "// Block 1" in result
        assert "NO, NO2" in result


# ---------------------------------------------------------------------------
# Tests: lu_solve_forward.j2
# ---------------------------------------------------------------------------


class TestForwardSubMacro:
    """Tests for emit_forward_sub macro (Requirements 3.3, 3.6, 3.7)."""

    def test_emits_variable_declarations_with_prefix_substitution(self, engine):
        """Forward sub emits double y_prefix_i = expr with b→rhs_prefix."""
        result = render_macro(
            engine,
            '{%- from "macros/lu_solve_forward.j2" import emit_forward_sub -%}',
            "{{ emit_forward_sub(steps, rhs_prefix, y_prefix) }}",
            {
                "steps": [
                    {"i": 0, "raw_expr": "b_0"},
                    {"i": 1, "raw_expr": "b_1 - L_1_0 * y_0"},
                ],
                "rhs_prefix": "F1",
                "y_prefix": "y1",
            },
        )
        assert "double y1_0 = F1_0;" in result
        assert "double y1_1 = F1_1 - L_1_0 * y1_0;" in result

    def test_reduction_mode_adds_active_guards(self, engine):
        """Reduction mode wraps expressions with active[i] ? (expr) : 0.0."""
        result = render_macro(
            engine,
            '{%- from "macros/lu_solve_forward.j2" import emit_forward_sub -%}',
            "{{ emit_forward_sub(steps, rhs_prefix, y_prefix, is_reduction=true) }}",
            {
                "steps": [
                    {"i": 0, "raw_expr": "b_0"},
                    {"i": 1, "raw_expr": "b_1 - L_1_0 * y_0"},
                ],
                "rhs_prefix": "F1",
                "y_prefix": "y1",
            },
        )
        assert "active[0]" in result
        assert "active[1]" in result
        assert ": 0.0;" in result
        # The expression should still have substituted prefixes
        assert "F1_0" in result
        assert "F1_1 - L_1_0 * y1_0" in result

    def test_block_boundary_comments(self, engine):
        """Block-boundary comments emitted for forward sub when blocks provided."""
        result = render_macro(
            engine,
            '{%- from "macros/lu_solve_forward.j2" import emit_forward_sub -%}',
            "{{ emit_forward_sub(steps, rhs_prefix, y_prefix, blocks=blocks) }}",
            {
                "steps": [
                    {"i": 0, "raw_expr": "b_0"},
                    {"i": 1, "raw_expr": "b_1"},
                    {"i": 2, "raw_expr": "b_2"},
                    {"i": 3, "raw_expr": "b_3"},
                ],
                "rhs_prefix": "F1",
                "y_prefix": "y1",
                "blocks": [
                    {"indices": [0, 1], "species_names": ["A", "B"]},
                    {"indices": [2, 3], "species_names": ["C", "D"]},
                ],
            },
        )
        assert "// Block" in result
        assert "A, B" in result
        assert "C, D" in result

    def test_custom_prefixes(self, engine):
        """Different prefix names are correctly substituted."""
        result = render_macro(
            engine,
            '{%- from "macros/lu_solve_forward.j2" import emit_forward_sub -%}',
            "{{ emit_forward_sub(steps, rhs_prefix, y_prefix) }}",
            {
                "steps": [
                    {"i": 0, "raw_expr": "b_0"},
                ],
                "rhs_prefix": "rhs2",
                "y_prefix": "yt2",
            },
        )
        assert "double yt2_0 = rhs2_0;" in result


# ---------------------------------------------------------------------------
# Tests: lu_solve_backward.j2
# ---------------------------------------------------------------------------


class TestBackwardSubMacro:
    """Tests for emit_backward_sub macro (Requirements 3.4, 3.6, 3.7)."""

    def test_emits_variable_declarations_with_prefix_substitution(self, engine):
        """Backward sub emits double x_prefix_i = expr with y→y_prefix."""
        result = render_macro(
            engine,
            '{%- from "macros/lu_solve_backward.j2" import emit_backward_sub -%}',
            "{{ emit_backward_sub(steps, y_prefix, x_prefix) }}",
            {
                "steps": [
                    {"i": 2, "raw_expr": "y_2 / U_2_2"},
                    {"i": 1, "raw_expr": "(y_1 - U_1_2 * x_2) / U_1_1"},
                    {"i": 0, "raw_expr": "(y_0 - U_0_1 * x_1 - U_0_2 * x_2) / U_0_0"},
                ],
                "y_prefix": "y1",
                "x_prefix": "K1",
            },
        )
        assert "double K1_2 = y1_2 / U_2_2;" in result
        assert "double K1_1 = (y1_1 - U_1_2 * K1_2) / U_1_1;" in result
        assert "double K1_0 = (y1_0 - U_0_1 * K1_1 - U_0_2 * K1_2) / U_0_0;" in result

    def test_reduction_mode_adds_active_guards(self, engine):
        """Reduction mode wraps backward sub expressions with active[i] guards."""
        result = render_macro(
            engine,
            '{%- from "macros/lu_solve_backward.j2" import emit_backward_sub -%}',
            "{{ emit_backward_sub(steps, y_prefix, x_prefix, is_reduction=true) }}",
            {
                "steps": [
                    {"i": 1, "raw_expr": "y_1 / U_1_1"},
                    {"i": 0, "raw_expr": "(y_0 - U_0_1 * x_1) / U_0_0"},
                ],
                "y_prefix": "y1",
                "x_prefix": "K1",
            },
        )
        assert "active[1]" in result
        assert "active[0]" in result
        assert ": 0.0;" in result
        assert "y1_1 / U_1_1" in result

    def test_block_boundary_comments(self, engine):
        """Block-boundary comments emitted for backward sub when blocks provided."""
        result = render_macro(
            engine,
            '{%- from "macros/lu_solve_backward.j2" import emit_backward_sub -%}',
            "{{ emit_backward_sub(steps, y_prefix, x_prefix, blocks=blocks) }}",
            {
                "steps": [
                    {"i": 3, "raw_expr": "y_3 / U_3_3"},
                    {"i": 2, "raw_expr": "y_2 / U_2_2"},
                    {"i": 1, "raw_expr": "y_1 / U_1_1"},
                    {"i": 0, "raw_expr": "y_0 / U_0_0"},
                ],
                "y_prefix": "y1",
                "x_prefix": "K1",
                "blocks": [
                    {"indices": [0, 1], "species_names": ["A", "B"]},
                    {"indices": [2, 3], "species_names": ["C", "D"]},
                ],
            },
        )
        assert "// Block" in result
        assert "backward sub" in result

    def test_custom_prefixes(self, engine):
        """Different prefix names are correctly substituted in backward sub."""
        result = render_macro(
            engine,
            '{%- from "macros/lu_solve_backward.j2" import emit_backward_sub -%}',
            "{{ emit_backward_sub(steps, y_prefix, x_prefix) }}",
            {
                "steps": [
                    {"i": 0, "raw_expr": "y_0 / U_0_0"},
                ],
                "y_prefix": "yt2",
                "x_prefix": "u2",
            },
        )
        assert "double u2_0 = yt2_0 / U_0_0;" in result


# ---------------------------------------------------------------------------
# Tests: lu_solve_transpose.j2
# ---------------------------------------------------------------------------


class TestTransposeSolveMacro:
    """Tests for emit_transpose_solve macro (Requirement 3.5)."""

    def test_emits_forward_and_backward_passes(self, engine):
        """Transpose solve emits both forward (U^T*y=b) and backward (L^T*x=y) passes."""
        result = render_macro(
            engine,
            '{%- from "macros/lu_solve_transpose.j2" import emit_transpose_solve -%}',
            "{{ emit_transpose_solve(fwd_steps, bwd_steps, rhs_prefix, y_prefix, x_prefix) }}",
            {
                "fwd_steps": [
                    {"i": 0, "raw_expr": "b_0 / U_0_0"},
                    {"i": 1, "raw_expr": "(b_1 - U_0_1 * y_0) / U_1_1"},
                ],
                "bwd_steps": [
                    {"i": 1, "raw_expr": "y_1"},
                    {"i": 0, "raw_expr": "y_0 - L_1_0 * x_1"},
                ],
                "rhs_prefix": "v1",
                "y_prefix": "yt1",
                "x_prefix": "u1",
            },
        )
        # Forward pass: rhs (b) substituted with v1, y with yt1
        assert "double yt1_0 = v1_0 / U_0_0;" in result
        assert "double yt1_1 = (v1_1 - U_0_1 * yt1_0) / U_1_1;" in result
        # Backward pass: y substituted with yt1, x with u1
        assert "double u1_1 = yt1_1;" in result
        assert "double u1_0 = yt1_0 - L_1_0 * u1_1;" in result

    def test_prefix_substitution(self, engine):
        """Custom prefixes are correctly applied in transpose solve."""
        result = render_macro(
            engine,
            '{%- from "macros/lu_solve_transpose.j2" import emit_transpose_solve -%}',
            "{{ emit_transpose_solve(fwd_steps, bwd_steps, rhs_prefix, y_prefix, x_prefix) }}",
            {
                "fwd_steps": [
                    {"i": 0, "raw_expr": "b_0"},
                ],
                "bwd_steps": [
                    {"i": 0, "raw_expr": "y_0"},
                ],
                "rhs_prefix": "adj_rhs",
                "y_prefix": "adj_y",
                "x_prefix": "adj_x",
            },
        )
        assert "double adj_y_0 = adj_rhs_0;" in result
        assert "double adj_x_0 = adj_y_0;" in result

    def test_reduction_mode(self, engine):
        """Transpose solve with is_reduction=true wraps with active guards."""
        result = render_macro(
            engine,
            '{%- from "macros/lu_solve_transpose.j2" import emit_transpose_solve -%}',
            "{{ emit_transpose_solve(fwd_steps, bwd_steps, rhs_prefix, y_prefix, x_prefix, is_reduction=true) }}",
            {
                "fwd_steps": [
                    {"i": 0, "raw_expr": "b_0"},
                    {"i": 1, "raw_expr": "b_1 - U_0_1 * y_0"},
                ],
                "bwd_steps": [
                    {"i": 1, "raw_expr": "y_1"},
                    {"i": 0, "raw_expr": "y_0 - L_1_0 * x_1"},
                ],
                "rhs_prefix": "v1",
                "y_prefix": "yt1",
                "x_prefix": "u1",
            },
        )
        assert "active[0]" in result
        assert "active[1]" in result
        assert ": 0.0;" in result

    def test_block_boundary_comments(self, engine):
        """Transpose solve emits block-boundary comments when blocks provided."""
        result = render_macro(
            engine,
            '{%- from "macros/lu_solve_transpose.j2" import emit_transpose_solve -%}',
            "{{ emit_transpose_solve(fwd_steps, bwd_steps, rhs_prefix, y_prefix, x_prefix, blocks=blocks) }}",
            {
                "fwd_steps": [
                    {"i": 0, "raw_expr": "b_0"},
                    {"i": 1, "raw_expr": "b_1"},
                    {"i": 2, "raw_expr": "b_2"},
                    {"i": 3, "raw_expr": "b_3"},
                ],
                "bwd_steps": [
                    {"i": 3, "raw_expr": "y_3"},
                    {"i": 2, "raw_expr": "y_2"},
                    {"i": 1, "raw_expr": "y_1"},
                    {"i": 0, "raw_expr": "y_0"},
                ],
                "rhs_prefix": "v1",
                "y_prefix": "yt1",
                "x_prefix": "u1",
                "blocks": [
                    {"indices": [0, 1], "species_names": ["A", "B"]},
                    {"indices": [2, 3], "species_names": ["C", "D"]},
                ],
            },
        )
        assert "// Block" in result
        assert "transpose" in result
        assert "A, B" in result
        assert "C, D" in result
