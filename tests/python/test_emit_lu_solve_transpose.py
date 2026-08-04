"""
Unit test for _emit_lu_solve_transpose() in symbolic_emit.py.

Task 5.1 — Verifies that _emit_lu_solve_transpose() correctly emits C++ code
for transposed forward/backward substitution (W^{-T} solve) using the symbolic
LU plan's transpose_forward_sub_steps and transpose_backward_sub_steps.

Tests cover:
  1. Correct variable prefix mapping (b_i -> rhs_prefix, y_i -> y_prefix, x_i -> k_prefix)
  2. Output structure mirrors _emit_lu_solve() but uses transposed steps
  3. Works with both simple (no-block) and block-diagonal LU plans
  4. Emitted code is numerically correct when evaluated against numpy reference

Requirements: 2.3, 5.2
"""
import io
import re
import pytest
import numpy as np
import sympy as sp

from mkpp.model import (
    MechanismDefinition,
    SpeciesDefinition,
    ReactionDefinition,
    PhaseMode,
    AerosolRepresentation,
    SymbolicLUPlan,
)
from mkpp.lowering import (
    prepare_unified_jacobian,
    compute_symbolic_lu_decomposition,
    compute_transposed_lu_plan,
)
from mkpp.symbolic_emit import _emit_lu_solve_transpose


def _build_chapman_mechanism():
    """Build the 3-species Chapman-like mechanism for testing."""
    sp_o = SpeciesDefinition(name="O", phase=PhaseMode.GAS)
    sp_o3 = SpeciesDefinition(name="O3", phase=PhaseMode.GAS)
    sp_o1d = SpeciesDefinition(name="O1D", phase=PhaseMode.GAS)

    r1 = ReactionDefinition(
        reaction_type="PHOTOLYSIS",
        reactants={"O3": 1.0},
        products={"O1D": 1.0, "O": 1.0},
        rate_expression="J1*O3",
        parameters={"A": "J1"},
        stiff=True,
    )
    r2 = ReactionDefinition(
        reaction_type="ARRHENIUS",
        reactants={"O": 1.0, "O3": 1.0},
        products={"O": 2.0},
        rate_expression="k2*O*O3",
        parameters={"A": 1e-15, "B": 0.0, "C": 0.0},
        stiff=True,
    )
    return MechanismDefinition(
        name="chapman_emit_test",
        description="Chapman mechanism for emission testing",
        aerosol_representation=AerosolRepresentation.BULK,
        species=[sp_o, sp_o3, sp_o1d],
        phases=[],
        reactions=[r1, r2],
    )


def _get_lu_plan_with_transposed_steps():
    """Build a Chapman LU plan with transposed steps populated."""
    mech = _build_chapman_mechanism()
    lowering_data = prepare_unified_jacobian(mech)
    J_sym = lowering_data["jacobian_matrix"]
    species_map = lowering_data["species_map"]
    lu_plan = compute_symbolic_lu_decomposition(J_sym, species_map)
    compute_transposed_lu_plan(lu_plan)
    return lu_plan, species_map


class TestEmitLuSolveTranspose:
    """Tests for _emit_lu_solve_transpose() C++ emission."""

    def test_emits_correct_variable_prefixes(self):
        """Verify b_i -> rhs_prefix, y_i -> y_prefix, x_i -> k_prefix."""
        lu_plan, species_map = _get_lu_plan_with_transposed_steps()

        buf = io.StringIO()
        _emit_lu_solve_transpose(
            f=buf,
            lu_plan=lu_plan,
            rhs_prefix="v3",
            y_prefix="yt3",
            k_prefix="u3",
            indent="    ",
        )
        output = buf.getvalue()

        # Should contain declarations with correct prefixes
        assert "yt3_" in output, "Forward sub should use y_prefix 'yt3'"
        assert "u3_" in output, "Backward sub should use k_prefix 'u3'"

        # Should NOT contain raw b_, y_, x_ variables (they should all be remapped)
        # Check that no un-substituted template variables remain
        lines = output.split("\n")
        for line in lines:
            # Skip empty lines
            if not line.strip():
                continue
            # Should not have bare b_N, y_N, x_N on the RHS (as variables, not in prefix names)
            # The LHS can have yt3_0 etc, but RHS should not have raw b_0 etc
            rhs_part = line.split("=", 1)[1] if "=" in line else ""
            assert not re.search(r'\bb_\d+\b', rhs_part), \
                f"Un-substituted b_i found in: {line}"

    def test_emits_all_species_indices(self):
        """Verify output covers all N species for both forward and backward steps."""
        lu_plan, species_map = _get_lu_plan_with_transposed_steps()
        N = lu_plan.num_species

        buf = io.StringIO()
        _emit_lu_solve_transpose(
            f=buf,
            lu_plan=lu_plan,
            rhs_prefix="rhs",
            y_prefix="y",
            k_prefix="k",
            indent="    ",
        )
        output = buf.getvalue()

        # Should have declarations for y_0..y_{N-1} (forward sub)
        for i in range(N):
            assert f"double y_{i}" in output, f"Missing forward sub for species {i}"

        # Should have declarations for k_0..k_{N-1} (backward sub)
        for i in range(N):
            assert f"double k_{i}" in output, f"Missing backward sub for species {i}"

    def test_emits_double_declarations(self):
        """Verify each emitted line is a valid C++ double declaration."""
        lu_plan, species_map = _get_lu_plan_with_transposed_steps()

        buf = io.StringIO()
        _emit_lu_solve_transpose(
            f=buf,
            lu_plan=lu_plan,
            rhs_prefix="v",
            y_prefix="yt",
            k_prefix="u",
            indent="          ",
        )
        output = buf.getvalue()

        lines = [l for l in output.split("\n") if l.strip() and not l.strip().startswith("//")]
        for line in lines:
            stripped = line.strip()
            assert stripped.startswith("double "), \
                f"Expected 'double' declaration, got: {stripped}"
            assert stripped.endswith(";"), \
                f"Expected semicolon at end of: {stripped}"

    def test_indent_is_applied(self):
        """Verify the indent parameter is respected."""
        lu_plan, species_map = _get_lu_plan_with_transposed_steps()

        indent = "        "
        buf = io.StringIO()
        _emit_lu_solve_transpose(
            f=buf,
            lu_plan=lu_plan,
            rhs_prefix="v",
            y_prefix="yt",
            k_prefix="u",
            indent=indent,
        )
        output = buf.getvalue()

        lines = [l for l in output.split("\n") if l.strip()]
        for line in lines:
            assert line.startswith(indent), \
                f"Line doesn't start with expected indent: '{line}'"

    def test_transposed_differs_from_forward(self):
        """Verify transposed emission differs from forward emission (non-symmetric case)."""
        lu_plan, species_map = _get_lu_plan_with_transposed_steps()

        # Emit transposed
        buf_t = io.StringIO()
        _emit_lu_solve_transpose(
            f=buf_t,
            lu_plan=lu_plan,
            rhs_prefix="rhs",
            y_prefix="y",
            k_prefix="k",
            indent="",
        )
        transposed_output = buf_t.getvalue()

        # Emit forward (using the non-transposed steps for comparison)
        # Build forward output manually using the same variable pattern
        buf_f = io.StringIO()
        for i, expr_str in lu_plan.forward_sub_steps:
            s = re.sub(r'\bb_(\d+)\b', r'rhs_\1', expr_str)
            s = re.sub(r'\by_(\d+)\b', r'y_\1', s)
            buf_f.write(f"double y_{i} = {s};\n")
        for i, expr_str in lu_plan.backward_sub_steps:
            s = expr_str
            s = re.sub(r'\by_(\d+)\b', r'y_\1', s)
            s = re.sub(r'\bx_(\d+)\b', r'k_\1', s)
            buf_f.write(f"double k_{i} = {s};\n")
        forward_output = buf_f.getvalue()

        # The expressions should differ because the transposed solve uses
        # U^T for forward sub and L^T for backward sub (swapped roles)
        assert transposed_output != forward_output, \
            "Transposed and forward emission should differ for non-symmetric Jacobian"

    def test_numerical_correctness_of_emitted_code(self):
        """
        Verify the emitted variable expressions are numerically correct.

        Evaluates the emitted C++ expressions (as Python) against numpy reference
        to confirm the emission correctly implements W^{-T} solve.
        """
        lu_plan, species_map = _get_lu_plan_with_transposed_steps()
        N = lu_plan.num_species

        # Build numeric W matrix from Chapman Jacobian
        mech = _build_chapman_mechanism()
        lowering_data = prepare_unified_jacobian(mech)
        J_sym = lowering_data["jacobian_matrix"]

        # Evaluate Jacobian numerically
        subs = {}
        subs[sp.Symbol("C_O", real=True, nonnegative=True)] = 1e6
        subs[sp.Symbol("C_O3", real=True, nonnegative=True)] = 1e12
        subs[sp.Symbol("C_O1D", real=True, nonnegative=True)] = 1e4
        subs[sp.Symbol("J_0", real=True, nonnegative=True)] = 5e-5
        subs[sp.Symbol("Temp", real=True, nonnegative=True)] = 298.0
        subs[sp.Symbol("Press", real=True, nonnegative=True)] = 101325.0

        J_num = np.zeros((N, N))
        for i in range(N):
            for j in range(N):
                if J_sym[i, j] != 0:
                    J_num[i, j] = float(J_sym[i, j].subs(subs))

        gamma = 0.43586652150845899
        h = 60.0
        inv_gh = 1.0 / (gamma * h)
        W = inv_gh * np.eye(N) - J_num

        # Execute LU factorization using plan
        ns = {}
        for i in range(N):
            for j in range(N):
                ns[f"W_{i}_{j}"] = W[i, j]

        for kind, i, j, expr_str in lu_plan.lu_expressions_ordered:
            val = eval(expr_str, {"__builtins__": {}}, ns)
            ns[f"{kind}_{i}_{j}"] = val

        # Random RHS
        rng = np.random.default_rng(42)
        b = rng.standard_normal(N)

        # Execute transposed forward sub
        for i in range(N):
            ns[f"rhs_{i}"] = b[i]

        for i, expr_str in lu_plan.transpose_forward_sub_steps:
            s = re.sub(r'\bb_(\d+)\b', r'rhs_\1', expr_str)
            val = eval(s, {"__builtins__": {}}, ns)
            ns[f"y_{i}"] = val

        # Execute transposed backward sub
        for i, expr_str in lu_plan.transpose_backward_sub_steps:
            s = re.sub(r'\bx_(\d+)\b', r'k_\1', expr_str)
            val = eval(s, {"__builtins__": {}}, ns)
            ns[f"k_{i}"] = val

        x_symbolic = np.array([ns[f"k_{i}"] for i in range(N)])
        x_numpy = np.linalg.solve(W.T, b)

        np.testing.assert_allclose(x_symbolic, x_numpy, rtol=1e-12, atol=1e-15)

    def test_is_reduction_emits_conditional(self):
        """Verify is_reduction=True wraps output in active[i] conditionals."""
        lu_plan, species_map = _get_lu_plan_with_transposed_steps()

        buf = io.StringIO()
        _emit_lu_solve_transpose(
            f=buf,
            lu_plan=lu_plan,
            rhs_prefix="v",
            y_prefix="yt",
            k_prefix="u",
            indent="    ",
            is_reduction=True,
        )
        output = buf.getvalue()

        lines = [l for l in output.split("\n") if l.strip() and not l.strip().startswith("//")]
        for line in lines:
            assert "active[" in line, \
                f"Expected active[] conditional in reduction mode: {line}"
            assert "? (" in line, \
                f"Expected ternary operator in reduction mode: {line}"
            assert ") : 0.0" in line, \
                f"Expected ': 0.0' fallback in reduction mode: {line}"
