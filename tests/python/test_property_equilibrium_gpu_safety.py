"""
Property-based tests for GPU safety and unrolled emission (Task 6.4).

Validates:
- Property 8: GPU Code Compliance (No Branching, No Allocation)
  (Requirements 4.1, 4.2, 4.3, 4.4, 4.5)
- Property 9: Unrolled Emission (No Runtime Loops)
  (Requirements 4.3, 4.5)
"""

import re
import tempfile

import pytest
from hypothesis import given, settings
from hypothesis import strategies as st
from mkpp.codegen import generate_headers
from mkpp.model import (
    AerosolRepresentation,
    EquilibriumDefinition,
    MechanismDefinition,
    PhaseMode,
    SpeciesDefinition,
)

# ---------------------------------------------------------------------------
# Strategies
# ---------------------------------------------------------------------------

# Blending function choices
blending_st = st.just("sigmoid")

# Transition width parameter
width_st = st.floats(min_value=0.01, max_value=0.5)

# ---------------------------------------------------------------------------
# Test Fixtures
# ---------------------------------------------------------------------------


def _mechanism_with_equilibrium(blending: str = "sigmoid", width: float = 0.05) -> MechanismDefinition:
    """Build a mechanism with equilibrium reactions for GPU safety testing."""
    return MechanismDefinition(
        name="gpu_safe_test",
        description="GPU safety property test mechanism",
        aerosol_representation=AerosolRepresentation.BULK,
        species=[
            SpeciesDefinition(name="NH3", phase=PhaseMode.GAS, elements={"N": 1}),
            SpeciesDefinition(name="NH4a", phase=PhaseMode.AEROSOL, elements={"N": 1}),
            SpeciesDefinition(name="HNO3", phase=PhaseMode.GAS, elements={"N": 1}),
            SpeciesDefinition(name="NO3an1", phase=PhaseMode.AEROSOL, elements={"N": 1}),
            SpeciesDefinition(name="SO2", phase=PhaseMode.GAS, elements={"S": 1}),
            SpeciesDefinition(name="SO4", phase=PhaseMode.AEROSOL, elements={"S": 1}),
        ],
        phases=[],
        reactions=[],
        equilibrium_reactions=[
            EquilibriumDefinition(
                system="NH4_NO3_SO4",
                total_species={
                    "reduced_nitrogen": ["NH3", "NH4a"],
                    "oxidized_nitrogen": ["HNO3", "NO3an1"],
                    "sulfate": ["SO2", "SO4"],
                },
                regime_blending=blending,
                transition_width=width,
            )
        ],
    )


# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------

# Forbidden keywords for GPU compliance
FORBIDDEN_KEYWORDS = ["if", "else", "switch", "new", "malloc", "std::vector", "throw", "virtual"]


def _generate_header(mech: MechanismDefinition) -> str:
    """Generate the C++ header and return its text content."""
    with tempfile.TemporaryDirectory() as tmpdir:
        result = generate_headers(mech, out_dir=tmpdir)
        with open(result["header"]) as f:
            return f.read()


def _strip_preprocessor_and_diagnostics(code: str) -> str:
    """Remove preprocessor directives and MKPP_DIAGNOSTICS blocks from code.

    Excludes:
    - Lines starting with #ifdef or #endif
    - Content inside #ifdef MKPP_DIAGNOSTICS ... #endif blocks
    """
    lines = code.split("\n")
    result = []
    in_diagnostics_block = False

    for line in lines:
        stripped = line.strip()

        # Track MKPP_DIAGNOSTICS blocks
        if stripped == "#ifdef MKPP_DIAGNOSTICS":
            in_diagnostics_block = True
            continue
        if in_diagnostics_block:
            if stripped == "#endif" or stripped == "#endif // MKPP_DIAGNOSTICS":
                in_diagnostics_block = False
            continue

        # Skip other preprocessor directives
        if stripped.startswith("#ifdef") or stripped.startswith("#endif"):
            continue

        result.append(line)

    return "\n".join(result)


def _extract_function_body(code: str, function_name: str) -> str | None:
    """Extract the body of a specific function from the generated code.

    Returns the function body text, or None if not found.
    Uses brace-counting to find the complete function body.
    """
    # Find the function declaration
    pattern = rf"KOKKOS_INLINE_FUNCTION\s+void\s+{function_name}\s*\("
    match = re.search(pattern, code)
    if not match:
        # Try without KOKKOS_INLINE_FUNCTION for nested functions
        pattern = rf"\bvoid\s+{function_name}\s*\("
        match = re.search(pattern, code)
        if not match:
            return None

    # Find the opening brace
    start = match.start()
    brace_pos = code.find("{", start)
    if brace_pos < 0:
        return None

    # Count braces to find the matching closing brace
    depth = 0
    for i in range(brace_pos, len(code)):
        if code[i] == "{":
            depth += 1
        elif code[i] == "}":
            depth -= 1
            if depth == 0:
                return code[brace_pos : i + 1]

    return None


# ---------------------------------------------------------------------------
# Property 8: GPU Code Compliance (No Branching, No Allocation)
# Feature: isorropia-unified-jacobian, Property 8: GPU Code Compliance
# **Validates: Requirements 4.1, 4.2, 4.3, 4.4, 4.5**
# ---------------------------------------------------------------------------


@pytest.mark.slow
@given(blending=blending_st, width=width_st)
@settings(max_examples=100, deadline=None)
def test_property_8_gpu_code_compliance(blending, width):
    """
    For any generated C++ code fragment for a mechanism with equilibrium,
    the text SHALL NOT contain `if`, `else`, `switch`, `new`, `malloc`,
    `std::vector`, `throw`, or `virtual` keywords.

    Generate the header for a mechanism with equilibrium, scan the emitted text.
    EXCLUDE lines starting with `#ifdef` or `#endif` and content inside
    `#ifdef MKPP_DIAGNOSTICS` blocks (diagnostics are allowed to branch).
    EXCLUDE the `integrate_with_reduction` function (it uses `active[i] ?`
    ternaries by design).

    We specifically check the equilibrium-related functions: `compute_rates`,
    `compute_jacobian`, and `compute_equilibrium_partition`. The `integrate()`
    function uses `if (err_norm <= 1.0)` for adaptive step-size control which
    is expected Rosenbrock error control, not equilibrium branching.

    # Feature: isorropia-unified-jacobian, Property 8: GPU Code Compliance

    **Validates: Requirements 4.1, 4.2, 4.3, 4.4, 4.5**
    """
    mech = _mechanism_with_equilibrium(blending=blending, width=width)
    code = _generate_header(mech)

    # Check specific equilibrium-related functions for GPU safety
    # The integrate() function legitimately uses if/else for Rosenbrock error control
    # (step acceptance/rejection), so we focus on the derivative computation functions
    functions_to_check = [
        "compute_rates",
        "compute_jacobian",
        "compute_equilibrium_partition",
    ]

    for func_name in functions_to_check:
        body = _extract_function_body(code, func_name)
        if body is None:
            if func_name in ("compute_rates", "compute_jacobian"):
                raise AssertionError(f"Function '{func_name}' not found in generated code " f"(blending={blending}, width={width})")
            continue

        # Strip preprocessor guards and diagnostics from function body
        filtered_body = _strip_preprocessor_and_diagnostics(body)

        # Check for forbidden keywords using word-boundary regex
        for keyword in FORBIDDEN_KEYWORDS:
            pattern = rf"\b{re.escape(keyword)}\b"
            matches = list(re.finditer(pattern, filtered_body))

            # Filter out false positives
            real_matches = []
            for m in matches:
                # Skip if "new" is part of an identifier like "Ynew_"
                if keyword == "new":
                    if m.start() > 0 and (filtered_body[m.start() - 1].isalnum() or filtered_body[m.start() - 1] == "_"):
                        continue
                    if m.end() < len(filtered_body) and (filtered_body[m.end()].isalnum() or filtered_body[m.end()] == "_"):
                        continue
                real_matches.append(m)

            assert len(real_matches) == 0, (
                f"Function '{func_name}' (with equilibrium, blending={blending}, "
                f"width={width}) contains forbidden GPU keyword '{keyword}'. "
                f"Found {len(real_matches)} occurrence(s). "
                f"First context: ...{filtered_body[max(0, real_matches[0].start()-40):real_matches[0].end()+40]}..."
                if real_matches
                else ""
            )


# ---------------------------------------------------------------------------
# Property 9: Unrolled Emission (No Runtime Loops)
# Feature: isorropia-unified-jacobian, Property 9: Unrolled Emission
# **Validates: Requirements 4.3, 4.5**
# ---------------------------------------------------------------------------


@pytest.mark.slow
@given(blending=blending_st, width=width_st)
@settings(max_examples=100, deadline=None)
def test_property_9_unrolled_emission(blending, width):
    """
    For any equilibrium system, the emitted equilibrium derivative block
    SHALL NOT contain `for` or `while` loop constructs - all derivatives
    are emitted as individual scalar assignments.

    Note: The `integrate()` function DOES have a `while (t < dt_total)` loop -
    that's the time-stepping loop, not a species loop. The point is that
    per-species arithmetic is unrolled, not looped. So we check the
    `compute_rates`, `compute_jacobian`, and `compute_equilibrium_partition`
    functions specifically (not `integrate`).

    # Feature: isorropia-unified-jacobian, Property 9: Unrolled Emission

    **Validates: Requirements 4.3, 4.5**
    """
    mech = _mechanism_with_equilibrium(blending=blending, width=width)
    code = _generate_header(mech)

    # Check specific functions that should have fully unrolled emission
    functions_to_check = [
        "compute_rates",
        "compute_jacobian",
        "compute_equilibrium_partition",
    ]

    for func_name in functions_to_check:
        body = _extract_function_body(code, func_name)
        if body is None:
            # compute_equilibrium_partition might not be present in all configs,
            # but compute_rates and compute_jacobian should always be there
            if func_name in ("compute_rates", "compute_jacobian"):
                raise AssertionError(f"Function '{func_name}' not found in generated code " f"(blending={blending}, width={width})")
            continue

        # Check for 'for' loops - these should not exist in unrolled functions
        for_matches = re.findall(r"\bfor\s*\(", body)
        assert len(for_matches) == 0, (
            f"Function '{func_name}' contains {len(for_matches)} 'for' loop(s). "
            f"All per-species arithmetic should be unrolled as scalar assignments. "
            f"blending={blending}, width={width}"
        )

        # Check for 'while' loops - these should not exist in these functions
        while_matches = re.findall(r"\bwhile\s*\(", body)
        assert len(while_matches) == 0, (
            f"Function '{func_name}' contains {len(while_matches)} 'while' loop(s). "
            f"All per-species arithmetic should be unrolled as scalar assignments. "
            f"blending={blending}, width={width}"
        )
