"""Verification tests for adjoint code generation with equilibrium reactions.

Task 8.1 — Verifies that the adjoint code generator correctly includes
equilibrium Jacobian entries in J^T when equilibrium reactions are present.

The discrete adjoint (`integrate_adj`) uses `_emit_rosenbrock_adjoint_stages()`
which iterates over `lu_plan.non_zero_jacobian` entries. Since the unified
Jacobian already contains equilibrium entries (via the relaxation flux from
task 4.1/4.2), and the LU plan is derived from this Jacobian, the adjoint
code automatically includes equilibrium contributions.

This test verifies:
1. The generated adjoint code contains `tanh` (from regime blending)
2. The generated adjoint code contains `exp` (from van't Hoff constants)
3. J^T entries reference species that participate in equilibrium coupling

Requirements referenced: 6.1, 6.2, 6.3
"""

import re
import tempfile

import pytest
from mkpp.codegen import generate_headers
from mkpp.model import (
    AerosolRepresentation,
    MechanismDefinition,
    PhaseMode,
    ReactionDefinition,
    SpeciesDefinition,
)

# ---------------------------------------------------------------------------
# Mechanism fixtures
# ---------------------------------------------------------------------------


def _mechanism_without_equilibrium() -> MechanismDefinition:
    """Build a mechanism without equilibrium for comparison."""
    return MechanismDefinition(
        name="no_eq_adj_test",
        description="No equilibrium adjoint test",
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


# ---------------------------------------------------------------------------
# Helper functions
# ---------------------------------------------------------------------------


def _generate_adjoint_header(mech: MechanismDefinition) -> str:
    """Generate a C++ header with adjoint=True and return its content."""
    with tempfile.TemporaryDirectory() as tmpdir:
        result = generate_headers(mech, out_dir=tmpdir, adjoint=True)
        with open(result["header"]) as f:
            return f.read()


def _extract_function_body(code: str, func_name: str) -> str:
    """Extract the body of a named function from generated C++ code.

    Finds the function by matching the function name and returns the content
    between its opening and closing braces.
    """
    # Search for the function signature
    pattern = re.compile(rf"\b(?:int|void)\s+{re.escape(func_name)}\s*\(", re.DOTALL)
    match = pattern.search(code)
    if not match:
        return ""

    pos = match.start()
    # Find the opening brace
    brace_start = code.index("{", pos)

    depth = 0
    for i in range(brace_start, len(code)):
        if code[i] == "{":
            depth += 1
        elif code[i] == "}":
            depth -= 1
            if depth == 0:
                return code[brace_start + 1 : i]

    return ""


# ---------------------------------------------------------------------------
# Test class
# ---------------------------------------------------------------------------


class TestEquilibriumAdjointCodegen:
    """Verify that adjoint code generation correctly includes equilibrium terms.

    The adjoint function `integrate_adj` recomputes J at each checkpointed state
    using the same non_zero_jacobian entries from the unified LU plan. When
    equilibrium reactions are present, those entries include tanh (regime blending)
    and exp (van't Hoff) terms. The J^T * u products in adjoint stages then
    reference all species that participate in equilibrium coupling.

    Uses the session-scoped `eq_generated_header_adjoint` fixture from conftest.py
    to avoid redundant expensive code generation on every test.

    **Validates: Requirements 6.1, 6.2, 6.3**
    """

    @pytest.fixture(autouse=True)
    def setup_generated_code(self, eq_generated_header_adjoint):
        """Use session-scoped generated adjoint header."""
        self.code = eq_generated_header_adjoint
        self.adj_body = _extract_function_body(self.code, "integrate_adj")

    def test_integrate_adj_function_present(self):
        """Verify integrate_adj is emitted when adjoint=True with equilibrium."""
        assert "integrate_adj" in self.code, "integrate_adj function should be present in generated code"
        assert len(self.adj_body) > 0, "integrate_adj function body should not be empty"

    def test_adjoint_code_contains_regime_blending(self):
        """Verify adjoint Jacobian entries contain regime blending functions (sigmoid or tanh).

        The equilibrium model uses smooth blending:
            w_i(R) = 0.5 * (1 + u / sqrt(1 + u^2))  [sigmoid]
            or 0.5 * (1 + tanh(u))                 [tanh]
        When J is recomputed at each checkpointed state in the adjoint loop,
        these terms appear in the J entries.
        """
        assert "sqrt" in self.adj_body or "tanh" in self.adj_body, (
            "Generated adjoint code should contain regime blending functions (sqrt or tanh). "
            f"Adjoint body length: {len(self.adj_body)} chars"
        )

    def test_adjoint_code_contains_exp(self):
        """Verify adjoint Jacobian entries contain exp (van't Hoff constants).

        The equilibrium constants use van't Hoff temperature dependence:
            Keq = A * exp(-dH/R * (1/T - 1/Tref))
        These exp() calls appear in the Jacobian entries recomputed in the
        adjoint loop.
        """
        assert "exp" in self.adj_body, (
            "Generated adjoint code should contain 'exp' from equilibrium "
            "van't Hoff temperature-dependent equilibrium constants. "
            f"Adjoint body length: {len(self.adj_body)} chars"
        )

    def test_adjoint_jt_references_equilibrium_species(self):
        """Verify J^T entries reference species participating in equilibrium.

        The adjoint computes J^T * u_j products. For equilibrium coupling,
        J entries exist between coupled species (e.g., NH3 and NH4a are
        coupled through reduced_nitrogen). The J^T * u computation must
        reference at least two different species variables (S_i and S_j
        where i != j) from the equilibrium system.

        Species indices in this mechanism:
          NH3=0, NH4a=1, HNO3=2, NO3an1=3, NO3an2=4, NO3an3=5, SO2=6, SO4=7
        """
        # Look for J_i_j entries in the adjoint body where i != j
        # (cross-coupling between equilibrium species)
        j_pattern = re.compile(r"J_(\d+)_(\d+)")
        j_entries = j_pattern.findall(self.adj_body)

        # Filter for cross-coupling (off-diagonal) entries
        cross_entries = [(int(i), int(j)) for i, j in j_entries if i != j]

        assert len(cross_entries) > 0, (
            "Adjoint code should contain off-diagonal J entries (cross-coupling) "
            "between equilibrium species. No J_i_j with i!=j found."
        )

        # Verify that equilibrium species indices appear in cross-coupling
        # NH3=0, NH4a=1 are coupled through reduced_nitrogen
        eq_species_indices = {0, 1, 2, 3, 4, 5, 6, 7}
        found_eq_coupling = False
        for i, j in cross_entries:
            if i in eq_species_indices and j in eq_species_indices:
                found_eq_coupling = True
                break

        assert found_eq_coupling, (
            "Adjoint J^T entries should reference equilibrium species "
            "cross-coupling (e.g., J_0_1 for NH3<->NH4a coupling). "
            f"Cross entries found: {cross_entries[:10]}"
        )

    def test_adjoint_uses_saved_state_for_jacobian(self):
        """Verify the adjoint recomputes J using checkpointed state S_k variables.

        The adjoint loop loads S_0, S_1, ... from checkpoint and recomputes
        the Jacobian at that state. This is the recompute-J strategy (D1).
        """
        # The adjoint should load state from checkpoint
        assert "chk.state[step]" in self.adj_body, "Adjoint should reload checkpointed state for Jacobian recomputation"

        # Should declare S_k variables from checkpoint
        assert "const double S_0 = chk.state[step][0]" in self.adj_body, "Adjoint should declare S_0 from checkpointed state"

    def test_adjoint_includes_temp_rh_in_jacobian(self):
        """Verify equilibrium J entries use Temp and RH symbols.

        When equilibrium reactions are present, the Jacobian entries include
        expressions with Temp (from van't Hoff) and RH (from deliquescence).
        These must be available in the adjoint scope.
        """
        # Temp should appear in the adjoint body (used in equilibrium expressions)
        assert "Temp" in self.adj_body, (
            "Adjoint code should reference Temp variable for equilibrium " "van't Hoff temperature-dependent expressions"
        )

    def test_adjoint_backward_loop_structure(self):
        """Verify the adjoint has the expected backward loop structure.

        The discrete adjoint iterates backward over checkpointed steps:
          for (int step = chk.num_steps - 1; step >= 0; step--)
        """
        assert "step = chk.num_steps - 1" in self.adj_body, "Adjoint should iterate backward over checkpoint steps"
        assert "step >= 0" in self.adj_body, "Adjoint backward loop should terminate at step >= 0"

    def test_adjoint_not_present_without_adjoint_flag(self, eq_mechanism_8species):
        """Verify integrate_adj is NOT emitted when adjoint=False."""
        with tempfile.TemporaryDirectory() as tmpdir:
            result = generate_headers(eq_mechanism_8species, out_dir=tmpdir, adjoint=False)
            with open(result["header"]) as f:
                code = f.read()

        assert "integrate_adj" not in code, "integrate_adj should NOT be present when adjoint=False"

    def test_adjoint_transpose_solve_present(self):
        """Verify the adjoint uses transposed LU solve (W^{-T}).

        The adjoint stages solve W^{-T} * v_i = u_i, using the transposed
        forward and backward substitution steps from the LU plan.
        """
        # Look for the W^{-T} solve comment or pattern
        assert (
            "W^{-T}" in self.adj_body or "transpose" in self.adj_body.lower()
        ), "Adjoint should contain transposed solve (W^{-T}) for adjoint stages"

    def test_equilibrium_species_in_jt_product(self):
        """Verify the J^T * u product references multiple equilibrium species.

        In the adjoint stage computation:
          (J^T * u_j)_k = Σ_col J[col, k] * u_j_col
        For equilibrium coupling, J[col, k] != 0 when col and k are
        in the same equilibrium group. So the sum should include
        multiple u_j terms for different species.
        """
        # Look for J^T * u patterns: J_col_k * u<stage>_col
        jt_product_pattern = re.compile(r"J_(\d+)_(\d+)\s*\*\s*u\d+_(\d+)")
        matches = jt_product_pattern.findall(self.adj_body)

        assert len(matches) > 0, "Adjoint should contain J_col_k * u_stage_col products for J^T*u computation"

        # Verify multiple different species appear in the J^T products
        species_in_products = set()
        for col, k, u_col in matches:
            species_in_products.add(int(col))
            species_in_products.add(int(k))

        # Should reference at least 2 different species (equilibrium coupling)
        assert len(species_in_products) >= 2, (
            f"J^T*u products should reference multiple species for equilibrium "
            f"coupling. Found species indices: {species_in_products}"
        )

    def test_no_adjoint_without_equilibrium_has_no_tanh(self):
        """Verify a mechanism without equilibrium does NOT have tanh in adjoint."""
        mech = _mechanism_without_equilibrium()
        code = _generate_adjoint_header(mech)
        adj_body = _extract_function_body(code, "integrate_adj")

        # Without equilibrium, there should be no tanh (no regime blending)
        assert "tanh" not in adj_body, "Adjoint code without equilibrium should NOT contain tanh"


class TestEquilibriumTLMCodegen:
    """Verify that TLM code generation correctly includes equilibrium terms.

    The TLM function `integrate_tlm` computes J * δC forward through
    checkpointed steps. When equilibrium reactions are present, J contains
    equilibrium-derived entries with tanh and exp.

    Uses the session-scoped `eq_generated_header_adjoint` fixture from conftest.py
    to avoid redundant expensive code generation on every test.

    **Validates: Requirements 6.2**
    """

    @pytest.fixture(autouse=True)
    def setup_generated_code(self, eq_generated_header_adjoint):
        """Use session-scoped generated adjoint header."""
        self.code = eq_generated_header_adjoint
        self.tlm_body = _extract_function_body(self.code, "integrate_tlm")

    def test_integrate_tlm_function_present(self):
        """Verify integrate_tlm is emitted when adjoint=True with equilibrium."""
        assert "integrate_tlm" in self.code, "integrate_tlm function should be present in generated code"
        assert len(self.tlm_body) > 0, "integrate_tlm function body should not be empty"

    def test_tlm_code_contains_regime_blending(self):
        """Verify TLM Jacobian entries contain regime blending functions (sigmoid or tanh)."""
        assert (
            "sqrt" in self.tlm_body or "tanh" in self.tlm_body
        ), "Generated TLM code should contain regime blending functions (sqrt or tanh)"

    def test_tlm_code_contains_exp(self):
        """Verify TLM Jacobian entries contain exp (van't Hoff constants)."""
        assert "exp" in self.tlm_body, (
            "Generated TLM code should contain 'exp' from equilibrium " "van't Hoff temperature-dependent equilibrium constants"
        )

    def test_tlm_j_times_delta_c_references_equilibrium_species(self):
        """Verify J*δC product references equilibrium species coupling.

        TLM stage RHS computes: J_{k,col} * (dC_col + Σ A * dK_col)
        For equilibrium, J has cross-coupling entries.
        """
        j_pattern = re.compile(r"J_(\d+)_(\d+)")
        j_entries = j_pattern.findall(self.tlm_body)
        cross_entries = [(int(i), int(j)) for i, j in j_entries if i != j]

        assert len(cross_entries) > 0, (
            "TLM code should contain off-diagonal J entries for " "equilibrium cross-coupling in J*δC computation"
        )

    def test_tlm_includes_temp_symbol(self):
        """Verify TLM Jacobian expressions use Temp for equilibrium constants."""
        assert "Temp" in self.tlm_body, "TLM code should reference Temp variable for equilibrium expressions"
