"""
Test: forward checkpoint produces identical final state as integrate().

Verifies that the generated integrate_fwd_checkpoint() produces a final state
that is IDENTICAL to integrate() for the same initial conditions. The only
difference between the two functions is that integrate_fwd_checkpoint()
additionally writes to CheckpointBuffer after each accepted step.

This is a Python-level test that compares the GENERATED CODE structure/logic,
verifying that the core Rosenbrock stage computation, state update, and step-size
control logic in integrate_fwd_checkpoint() is byte-for-byte identical to
integrate().

**Validates: Requirements 1.4, 6.2, 6.3**
"""

import re

import pytest
from mkpp.codegen import SOLVER_COEFFICIENTS, generate_headers
from mkpp.parser import load_mechanism

# ---------------------------------------------------------------------------
# Mechanism builders
# ---------------------------------------------------------------------------


def _build_chapman_mechanism():
    """Build a Chapman-like mechanism (4 species) for testing."""
    return load_mechanism("mechanisms/openatmos/chapman/mechanism.json")


def _build_saprc99_mechanism():
    """Load the SAPRC-99 mechanism for testing."""
    return load_mechanism("mechanisms/openatmos/saprc99_mini/mechanism.json")


def _generate_with_adjoint(mech, solver_name: str, tmp_dir: str) -> str:
    """Generate the C++ header with adjoint=True for the given solver."""
    results = generate_headers(mech, out_dir=tmp_dir, solver_name=solver_name, adjoint=True)
    with open(results["header"]) as f:
        return f.read()


# ---------------------------------------------------------------------------
# Helper: extract function bodies from generated code
# ---------------------------------------------------------------------------


def _extract_function_body(code: str, func_name: str) -> str:
    """Extract the body of a function from generated C++ code.

    Finds the function by matching 'void <func_name>(' and returns everything
    from the opening brace of the function body to its matching closing brace.
    """
    # Find the function signature
    pattern = re.compile(rf"\b(?:int|void)\s+{re.escape(func_name)}\s*\(", re.DOTALL)
    match = pattern.search(code)
    if not match:
        return ""

    # Find the opening brace of the function body
    pos = match.start()
    brace_start = code.index("{", pos)

    # Track braces to find the matching close
    depth = 0
    for i in range(brace_start, len(code)):
        if code[i] == "{":
            depth += 1
        elif code[i] == "}":
            depth -= 1
            if depth == 0:
                return code[brace_start + 1 : i]

    return ""


def _extract_stage_lines(body: str) -> list:
    """Extract lines relevant to Rosenbrock stage computation.

    Returns all non-blank, non-comment lines that participate in:
    - State hoisting (S_i = ...)
    - Jacobian computation (J_i_j = ...)
    - W-matrix formation (W_i_j = ...)
    - LU factorization (L_i_j = ..., U_i_j = ...)
    - Rate evaluations (F1_i = ..., F2_i = ...)
    - Intermediate state (Y2_i = ..., Y3_i = ...)
    - RHS formation (rhs2_i = ..., rhs3_i = ...)
    - Forward/backward substitution (y1_i = ..., K1_i = ...)
    - Solution update (state(...) += ...)
    - Error estimation (yerr, err_norm, etc.)
    - Step size control (factor, safety, etc.)
    """
    lines = []
    for line in body.split("\n"):
        stripped = line.strip()
        # Skip blank lines
        if not stripped:
            continue
        # Skip pure comments
        if stripped.startswith("//"):
            continue
        # Skip checkpoint-related lines
        if any(
            kw in stripped
            for kw in [
                "chk.",
                "CheckpointBuffer",
                "num_steps",
                "ierr",
                "// Save checkpoint",
                "return -1",
                "return chk",
            ]
        ):
            continue
        lines.append(stripped)
    return lines


def _extract_core_arithmetic(body: str) -> list:
    """Extract the core arithmetic/computation lines, excluding:
    - function preamble (const int NUM_SPECIES, g, safety, etc. declarations)
    - checkpoint-specific code
    - return statements specific to checkpoint variant
    """
    lines = []
    for line in body.split("\n"):
        stripped = line.strip()
        if not stripped:
            continue
        if stripped.startswith("//"):
            continue
        # Skip checkpoint-specific lines
        if any(
            kw in stripped
            for kw in [
                "chk.",
                "CheckpointBuffer",
                "ierr",
                "// Save checkpoint",
                "return -1",
                "return chk",
                "int ierr",
                "chk.num_steps",
            ]
        ):
            continue
        lines.append(stripped)
    return lines


def _normalize_function_body(body: str) -> list:
    """Normalize a function body for comparison.

    Strips checkpoint-related lines and normalizes whitespace,
    giving us the core computational logic that must be identical.

    The checkpoint variant has an additional bounds-check block:
        if (chk.num_steps >= CheckpointBuffer::MAX_STEPS) {
            ierr = 1;
            return -1;
        }
    This entire block (including its braces) must be filtered out.
    """
    lines = []
    in_checkpoint_block = False
    checkpoint_brace_depth = 0
    for line in body.split("\n"):
        stripped = line.strip()
        # Skip blank lines
        if not stripped:
            continue
        # Skip pure comments unless they're stage markers
        if stripped.startswith("//"):
            # Keep stage markers and computation-related comments
            if "Stage" in stripped or "Step Size" in stripped:
                lines.append(stripped)
            continue
        # Detect start of checkpoint bounds-check block
        if any(
            kw in stripped
            for kw in [
                "chk.num_steps >= CheckpointBuffer::MAX_STEPS",
                "if (chk.num_steps >= ",
            ]
        ):
            in_checkpoint_block = True
            checkpoint_brace_depth = 0
            # Count braces on this line
            checkpoint_brace_depth += stripped.count("{") - stripped.count("}")
            continue
        # If we're inside a checkpoint block, skip until braces balance
        if in_checkpoint_block:
            checkpoint_brace_depth += stripped.count("{") - stripped.count("}")
            if checkpoint_brace_depth <= 0:
                in_checkpoint_block = False
            continue
        # Skip other checkpoint-specific lines
        if any(
            kw in stripped
            for kw in [
                "chk.",
                "CheckpointBuffer",
                "num_steps >= ",
                "ierr",
                "// Save checkpoint",
                "return -1;",
                "return chk.num_steps;",
                "int ierr = 0;",
                "chk.num_steps = 0;",
            ]
        ):
            continue
        lines.append(stripped)
    return lines


# ---------------------------------------------------------------------------
# Test: integrate_fwd_checkpoint has identical stage logic as integrate
# ---------------------------------------------------------------------------

ALL_SOLVERS = list(SOLVER_COEFFICIENTS.keys())


@pytest.mark.parametrize("solver_name", ALL_SOLVERS)
class TestForwardCheckpointEquivalenceChapman:
    """Verify integrate_fwd_checkpoint() produces identical state updates as integrate()
    for the Chapman mechanism across all solver variants."""

    def test_integrate_fwd_checkpoint_present(self, solver_name: str, tmp_path):
        """integrate_fwd_checkpoint function is emitted when adjoint=True."""
        mech = _build_chapman_mechanism()
        code = _generate_with_adjoint(mech, solver_name, str(tmp_path))
        assert "integrate_fwd_checkpoint" in code, f"[{solver_name}] integrate_fwd_checkpoint not found in generated code"

    def test_integrate_still_present(self, solver_name: str, tmp_path):
        """Original integrate() is unchanged when adjoint=True (Req 6.3)."""
        mech = _build_chapman_mechanism()
        code = _generate_with_adjoint(mech, solver_name, str(tmp_path))
        # integrate() must still be present
        assert re.search(r"\bvoid\s+integrate\s*\(", code), f"[{solver_name}] Original integrate() missing when adjoint=True"

    def test_same_stage_count(self, solver_name: str, tmp_path):
        """Both functions have the same number of stage computations."""
        mech = _build_chapman_mechanism()
        code = _generate_with_adjoint(mech, solver_name, str(tmp_path))
        tableau = SOLVER_COEFFICIENTS[solver_name]

        integrate_body = _extract_function_body(code, "integrate")
        checkpoint_body = _extract_function_body(code, "integrate_fwd_checkpoint")

        # Count stage markers in each
        integrate_stages = re.findall(r"// --- Stage \d+ ---", integrate_body)
        checkpoint_stages = re.findall(r"// --- Stage \d+ ---", checkpoint_body)

        assert len(integrate_stages) == tableau.stages, (
            f"[{solver_name}] integrate() has {len(integrate_stages)} stages, " f"expected {tableau.stages}"
        )
        assert len(checkpoint_stages) == tableau.stages, (
            f"[{solver_name}] integrate_fwd_checkpoint() has {len(checkpoint_stages)} stages, " f"expected {tableau.stages}"
        )

    def test_same_gamma_constant(self, solver_name: str, tmp_path):
        """Both functions use the same gamma constant from the tableau."""
        mech = _build_chapman_mechanism()
        code = _generate_with_adjoint(mech, solver_name, str(tmp_path))

        integrate_body = _extract_function_body(code, "integrate")
        checkpoint_body = _extract_function_body(code, "integrate_fwd_checkpoint")

        # Extract gamma values
        g_pattern = re.compile(r"const double g = ([^;]+);")
        g_integrate = g_pattern.search(integrate_body)
        g_checkpoint = g_pattern.search(checkpoint_body)

        assert g_integrate is not None, f"[{solver_name}] No gamma in integrate()"
        assert g_checkpoint is not None, f"[{solver_name}] No gamma in integrate_fwd_checkpoint()"
        assert g_integrate.group(1) == g_checkpoint.group(1), (
            f"[{solver_name}] Gamma mismatch: integrate={g_integrate.group(1)}, " f"checkpoint={g_checkpoint.group(1)}"
        )

    def test_identical_state_update_expressions(self, solver_name: str, tmp_path):
        """State update lines (state(...) += ...) are identical in both functions."""
        mech = _build_chapman_mechanism()
        code = _generate_with_adjoint(mech, solver_name, str(tmp_path))

        integrate_body = _extract_function_body(code, "integrate")
        checkpoint_body = _extract_function_body(code, "integrate_fwd_checkpoint")

        # Extract state update lines
        update_pattern = re.compile(r"state\(\d+\)\s*\+=\s*[^;]+;")
        integrate_updates = update_pattern.findall(integrate_body)
        checkpoint_updates = update_pattern.findall(checkpoint_body)

        assert len(integrate_updates) > 0, f"[{solver_name}] No state updates found in integrate()"
        assert integrate_updates == checkpoint_updates, (
            f"[{solver_name}] State update expressions differ between "
            f"integrate() and integrate_fwd_checkpoint().\n"
            f"  integrate:  {integrate_updates}\n"
            f"  checkpoint: {checkpoint_updates}"
        )

    def test_identical_k_variable_computations(self, solver_name: str, tmp_path):
        """K stage variables (K1_0, K2_0, ...) are computed identically."""
        mech = _build_chapman_mechanism()
        code = _generate_with_adjoint(mech, solver_name, str(tmp_path))

        integrate_body = _extract_function_body(code, "integrate")
        checkpoint_body = _extract_function_body(code, "integrate_fwd_checkpoint")

        # Extract all K variable assignment lines
        k_pattern = re.compile(r"double K\d+_\d+ = [^;]+;")
        integrate_k = k_pattern.findall(integrate_body)
        checkpoint_k = k_pattern.findall(checkpoint_body)

        assert len(integrate_k) > 0, f"[{solver_name}] No K variables found in integrate()"
        assert integrate_k == checkpoint_k, (
            f"[{solver_name}] K variable computations differ.\n"
            f"  integrate count:  {len(integrate_k)}\n"
            f"  checkpoint count: {len(checkpoint_k)}\n"
            f"  First difference at index: "
            f"{next((i for i, (a, b) in enumerate(zip(integrate_k, checkpoint_k)) if a != b), 'length mismatch')}"
        )

    def test_identical_error_estimation(self, solver_name: str, tmp_path):
        """Error estimation logic is identical in both functions."""
        mech = _build_chapman_mechanism()
        code = _generate_with_adjoint(mech, solver_name, str(tmp_path))

        integrate_body = _extract_function_body(code, "integrate")
        checkpoint_body = _extract_function_body(code, "integrate_fwd_checkpoint")

        # Extract error norm computation
        err_pattern = re.compile(r"double err_norm[^;]*;")
        integrate_err = err_pattern.findall(integrate_body)
        checkpoint_err = err_pattern.findall(checkpoint_body)

        assert integrate_err == checkpoint_err, f"[{solver_name}] Error estimation differs"

    def test_identical_step_size_control(self, solver_name: str, tmp_path):
        """Step size control factor computation is identical."""
        mech = _build_chapman_mechanism()
        code = _generate_with_adjoint(mech, solver_name, str(tmp_path))

        integrate_body = _extract_function_body(code, "integrate")
        checkpoint_body = _extract_function_body(code, "integrate_fwd_checkpoint")

        # Extract factor computation line
        factor_pattern = re.compile(r"double factor = [^;]+;")
        integrate_factor = factor_pattern.findall(integrate_body)
        checkpoint_factor = factor_pattern.findall(checkpoint_body)

        assert integrate_factor == checkpoint_factor, (
            f"[{solver_name}] Step size control differs.\n"
            f"  integrate:  {integrate_factor}\n"
            f"  checkpoint: {checkpoint_factor}"
        )

    def test_checkpoint_saves_h_and_state(self, solver_name: str, tmp_path):
        """integrate_fwd_checkpoint() saves h and state into checkpoint buffer."""
        mech = _build_chapman_mechanism()
        code = _generate_with_adjoint(mech, solver_name, str(tmp_path))

        checkpoint_body = _extract_function_body(code, "integrate_fwd_checkpoint")

        # Must save step size
        assert "chk.h[chk.num_steps] = dt;" in checkpoint_body, f"[{solver_name}] Checkpoint does not save step size h"
        # Must save state
        assert "chk.state[chk.num_steps]" in checkpoint_body, f"[{solver_name}] Checkpoint does not save state"
        # Must increment step counter
        assert "chk.num_steps++" in checkpoint_body, f"[{solver_name}] Checkpoint does not increment num_steps"

    def test_checkpoint_bounds_check(self, solver_name: str, tmp_path):
        """integrate_fwd_checkpoint() checks MAX_STEPS bounds (Req 1.3)."""
        mech = _build_chapman_mechanism()
        code = _generate_with_adjoint(mech, solver_name, str(tmp_path))

        checkpoint_body = _extract_function_body(code, "integrate_fwd_checkpoint")

        # Must check against MAX_STEPS
        assert "MAX_STEPS" in checkpoint_body, f"[{solver_name}] Checkpoint does not check MAX_STEPS bound"
        # Must fail loudly (return -1 or assert)
        assert "return -1" in checkpoint_body, f"[{solver_name}] Checkpoint does not fail loudly on overflow"

    def test_only_difference_is_checkpoint_logic(self, solver_name: str, tmp_path):
        """The ONLY difference between the two functions is checkpoint save logic.

        This is the key property: after removing checkpoint-specific lines,
        the normalized function bodies should be identical for all computational
        lines.
        """
        mech = _build_chapman_mechanism()
        code = _generate_with_adjoint(mech, solver_name, str(tmp_path))

        integrate_body = _extract_function_body(code, "integrate")
        checkpoint_body = _extract_function_body(code, "integrate_fwd_checkpoint")

        # Normalize both bodies (strip comments, checkpoint lines, blank lines)
        integrate_normalized = _normalize_function_body(integrate_body)
        checkpoint_normalized = _normalize_function_body(checkpoint_body)

        # Find lines present in checkpoint but not in integrate (should be empty)
        # and lines in integrate not in checkpoint (should be empty)
        # We compare ordered sequences — same computation in same order.
        integrate_set = integrate_normalized
        checkpoint_set = checkpoint_normalized

        # The core computation lines must match exactly in order
        mismatches = []
        max_len = max(len(integrate_set), len(checkpoint_set))
        for i in range(max_len):
            a = integrate_set[i] if i < len(integrate_set) else "<missing>"
            b = checkpoint_set[i] if i < len(checkpoint_set) else "<missing>"
            if a != b:
                mismatches.append((i, a, b))
                if len(mismatches) >= 5:
                    break

        assert not mismatches, (
            f"[{solver_name}] Core computation differs between integrate() and "
            f"integrate_fwd_checkpoint() (showing up to 5 mismatches):\n"
            + "\n".join(f"  Line {i}: integrate='{a}' vs checkpoint='{b}'" for i, a, b in mismatches)
        )


@pytest.mark.parametrize("solver_name", ALL_SOLVERS)
class TestForwardCheckpointEquivalenceSAPRC99:
    """Verify integrate_fwd_checkpoint() produces identical state updates as integrate()
    for the SAPRC-99 mechanism across all solver variants.

    SAPRC-99 is a larger mechanism (~80+ species) that exercises the code generation
    with a non-trivial Jacobian and LU plan.
    """

    def test_integrate_fwd_checkpoint_present(self, solver_name: str, tmp_path):
        """integrate_fwd_checkpoint function is emitted for SAPRC-99."""
        mech = _build_saprc99_mechanism()
        code = _generate_with_adjoint(mech, solver_name, str(tmp_path))
        assert "integrate_fwd_checkpoint" in code, f"[{solver_name}] integrate_fwd_checkpoint not found for SAPRC-99"

    def test_identical_state_update_expressions(self, solver_name: str, tmp_path):
        """State update lines are identical for SAPRC-99."""
        mech = _build_saprc99_mechanism()
        code = _generate_with_adjoint(mech, solver_name, str(tmp_path))

        integrate_body = _extract_function_body(code, "integrate")
        checkpoint_body = _extract_function_body(code, "integrate_fwd_checkpoint")

        # Extract state update lines
        update_pattern = re.compile(r"state\(\d+\)\s*\+=\s*[^;]+;")
        integrate_updates = update_pattern.findall(integrate_body)
        checkpoint_updates = update_pattern.findall(checkpoint_body)

        assert len(integrate_updates) > 0, f"[{solver_name}] No state updates found in integrate() for SAPRC-99"
        assert integrate_updates == checkpoint_updates, (
            f"[{solver_name}] State update expressions differ for SAPRC-99.\n"
            f"  integrate count:  {len(integrate_updates)}\n"
            f"  checkpoint count: {len(checkpoint_updates)}"
        )

    def test_identical_k_variable_count(self, solver_name: str, tmp_path):
        """K stage variable count matches for SAPRC-99."""
        mech = _build_saprc99_mechanism()
        code = _generate_with_adjoint(mech, solver_name, str(tmp_path))

        integrate_body = _extract_function_body(code, "integrate")
        checkpoint_body = _extract_function_body(code, "integrate_fwd_checkpoint")

        k_pattern = re.compile(r"double K\d+_\d+ = [^;]+;")
        integrate_k = k_pattern.findall(integrate_body)
        checkpoint_k = k_pattern.findall(checkpoint_body)

        assert len(integrate_k) == len(checkpoint_k), (
            f"[{solver_name}] K variable count differs for SAPRC-99: "
            f"integrate={len(integrate_k)}, checkpoint={len(checkpoint_k)}"
        )
        # Spot-check first and last K variables match
        if integrate_k:
            assert integrate_k[0] == checkpoint_k[0], f"[{solver_name}] First K variable differs for SAPRC-99"
            assert integrate_k[-1] == checkpoint_k[-1], f"[{solver_name}] Last K variable differs for SAPRC-99"

    def test_checkpoint_saves_correct_species_count(self, solver_name: str, tmp_path):
        """Checkpoint saves the correct number of species for SAPRC-99.

        The checkpoint saves state for all species in the generated solver's state
        vector (NUM_SPECIES as determined by the codegen). This matches the number
        of state update lines in integrate().
        """
        mech = _build_saprc99_mechanism()
        code = _generate_with_adjoint(mech, solver_name, str(tmp_path))

        checkpoint_body = _extract_function_body(code, "integrate_fwd_checkpoint")
        integrate_body = _extract_function_body(code, "integrate")

        # Count how many state saves there are
        save_pattern = re.compile(r"chk\.state\[chk\.num_steps\]\[\d+\]")
        saves = save_pattern.findall(checkpoint_body)

        # The number of state saves should match the number of state updates
        # in integrate() — one per species in the solver state vector
        update_pattern = re.compile(r"state\(\d+\)\s*\+=")
        integrate_updates = update_pattern.findall(integrate_body)
        expected_saves = len(integrate_updates)

        assert len(saves) == expected_saves, (
            f"[{solver_name}] SAPRC-99: expected {expected_saves} state saves "
            f"(matching integrate() state updates), got {len(saves)}"
        )
