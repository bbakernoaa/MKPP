"""
Property-based test for reduction integrator consistency.

**Validates: Requirements 6.1, 6.2**

Property 9: Reduction integrator consistency
For any solver, the coefficient literals, stage count, and error exponent in
integrate_with_reduction() are identical to those in integrate().
"""
import re
import tempfile

import pytest

from mkpp.codegen import SOLVER_COEFFICIENTS, generate_headers
from mkpp.lowering import prepare_unified_jacobian, compute_symbolic_lu_decomposition
from mkpp.model import (
    MechanismDefinition,
    SpeciesDefinition,
    ReactionDefinition,
    PhaseMode,
    AerosolRepresentation,
)


# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------


def _build_test_mechanism():
    """Build a minimal 3-species mechanism for code generation testing."""
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
        name="test_reduction_consistency",
        description="Mechanism for reduction integrator consistency test",
        aerosol_representation=AerosolRepresentation.BULK,
        species=[sp_a, sp_b, sp_c],
        phases=[],
        reactions=[rxn1, rxn2],
    )


def _generate_code_for_solver(solver_name: str) -> str:
    """Generate the full C++ header for the given solver and return as string."""
    mech = _build_test_mechanism()
    lowering_data = prepare_unified_jacobian(mech)
    plan = compute_symbolic_lu_decomposition(
        lowering_data["jacobian_matrix"], lowering_data["species_map"]
    )
    mech.metadata = {
        "sympy_metadata": lowering_data,
        "symbolic_lu_plan": plan,
    }

    with tempfile.TemporaryDirectory() as tmp_dir:
        artifacts = generate_headers(mech, out_dir=tmp_dir, solver_name=solver_name)
        with open(artifacts["header"], "r") as f:
            return f.read()


def _split_integrate_functions(code: str) -> tuple:
    """Split generated code into integrate() and integrate_with_reduction() sections.

    Returns (integrate_code, reduction_code) as strings.
    """
    # Find the integrate() function start
    integrate_start = code.find("KOKKOS_INLINE_FUNCTION void integrate(")
    assert integrate_start != -1, "integrate() function not found in generated code"

    # Find the integrate_with_reduction() function start
    reduction_start = code.find("KOKKOS_INLINE_FUNCTION void integrate_with_reduction(")
    assert reduction_start != -1, (
        "integrate_with_reduction() function not found in generated code"
    )

    # integrate() body is between its start and the start of integrate_with_reduction()
    integrate_code = code[integrate_start:reduction_start]

    # integrate_with_reduction() body is from its start to end of file (or next function)
    reduction_code = code[reduction_start:]

    return integrate_code, reduction_code


def _extract_gamma_value(code_section: str) -> float:
    """Extract the gamma value (const double g = ...) from a code section."""
    match = re.search(r"const double g = ([^;]+);", code_section)
    assert match is not None, "Gamma value 'const double g = ...' not found"
    return float(match.group(1))


def _count_stage_comments(code_section: str) -> int:
    """Count the number of '// --- Stage N ---' comments in a code section."""
    return len(re.findall(r"// --- Stage \d+ ---", code_section))


def _extract_stage_numbers(code_section: str) -> list:
    """Extract the sequence of stage numbers from stage comments."""
    matches = re.findall(r"// --- Stage (\d+) ---", code_section)
    return [int(m) for m in matches]


def _extract_step_control_exponent_line(code_section: str) -> str:
    """Extract the step size control line that contains the exponent."""
    # Look for the step-size control comment and the following factor computation
    match = re.search(
        r"// Step Size Control \(order (\d+): exponent = [^)]+\)\n\s+(.*factor.*)",
        code_section,
    )
    if match:
        return match.group(2).strip()
    # Fallback: look for the factor assignment line
    match = re.search(r"double factor = safety.*err_norm.*;\n?", code_section)
    if match:
        return match.group(0).strip()
    return ""


def _extract_m_coefficient_lines(code_section: str) -> list:
    """Extract state update lines (state(...) += ...) to verify M coefficients."""
    return [
        line.strip()
        for line in code_section.split("\n")
        if "state(" in line and "+=" in line
    ]


def _extract_yerr_lines(code_section: str) -> list:
    """Extract error estimate lines (double yerr_i = ...) to verify E coefficients."""
    return [
        line.strip()
        for line in code_section.split("\n")
        if "double yerr_i" in line
    ]


def _extract_float_literals_from_lines(lines: list) -> list:
    """Extract all floating-point literals from a list of code lines."""
    all_floats = []
    pattern = r"[-+]?\d+\.\d+(?:[eE][-+]?\d+)?"
    for line in lines:
        all_floats.extend(float(m) for m in re.findall(pattern, line))
    return all_floats


# ---------------------------------------------------------------------------
# Property 9: Reduction integrator consistency
# **Validates: Requirements 6.1, 6.2**
# ---------------------------------------------------------------------------


@pytest.mark.parametrize("solver_name", list(SOLVER_COEFFICIENTS.keys()))
def test_property_9_same_gamma_value(solver_name: str):
    """
    For any solver, integrate_with_reduction() uses the same gamma value
    (const double g = ...) as integrate().

    **Validates: Requirements 6.1, 6.2**
    """
    code = _generate_code_for_solver(solver_name)
    integrate_code, reduction_code = _split_integrate_functions(code)

    gamma_integrate = _extract_gamma_value(integrate_code)
    gamma_reduction = _extract_gamma_value(reduction_code)

    assert gamma_integrate == gamma_reduction, (
        f"[{solver_name}] Gamma mismatch: integrate() has g={gamma_integrate:.17g}, "
        f"integrate_with_reduction() has g={gamma_reduction:.17g}"
    )


@pytest.mark.parametrize("solver_name", list(SOLVER_COEFFICIENTS.keys()))
def test_property_9_same_stage_count(solver_name: str):
    """
    For any solver, integrate_with_reduction() has the same number of stages
    (same number of '// --- Stage N ---' comments) as integrate().

    **Validates: Requirements 6.1, 6.2**
    """
    tableau = SOLVER_COEFFICIENTS[solver_name]
    code = _generate_code_for_solver(solver_name)
    integrate_code, reduction_code = _split_integrate_functions(code)

    stages_integrate = _count_stage_comments(integrate_code)
    stages_reduction = _count_stage_comments(reduction_code)

    assert stages_integrate == tableau.stages, (
        f"[{solver_name}] integrate() has {stages_integrate} stages, "
        f"expected {tableau.stages}"
    )
    assert stages_reduction == tableau.stages, (
        f"[{solver_name}] integrate_with_reduction() has {stages_reduction} stages, "
        f"expected {tableau.stages}"
    )
    assert stages_integrate == stages_reduction, (
        f"[{solver_name}] Stage count mismatch: integrate() has {stages_integrate}, "
        f"integrate_with_reduction() has {stages_reduction}"
    )


@pytest.mark.parametrize("solver_name", list(SOLVER_COEFFICIENTS.keys()))
def test_property_9_same_stage_numbering(solver_name: str):
    """
    For any solver, integrate_with_reduction() uses the same stage numbering
    sequence (1, 2, ..., S) as integrate().

    **Validates: Requirements 6.1, 6.2**
    """
    code = _generate_code_for_solver(solver_name)
    integrate_code, reduction_code = _split_integrate_functions(code)

    stages_integrate = _extract_stage_numbers(integrate_code)
    stages_reduction = _extract_stage_numbers(reduction_code)

    assert stages_integrate == stages_reduction, (
        f"[{solver_name}] Stage numbering mismatch: "
        f"integrate() has {stages_integrate}, "
        f"integrate_with_reduction() has {stages_reduction}"
    )


@pytest.mark.parametrize("solver_name", list(SOLVER_COEFFICIENTS.keys()))
def test_property_9_same_step_size_exponent(solver_name: str):
    """
    For any solver, integrate_with_reduction() uses the same step-size control
    exponent (derived from 1/ELO) as integrate().

    **Validates: Requirements 6.1, 6.2**
    """
    code = _generate_code_for_solver(solver_name)
    integrate_code, reduction_code = _split_integrate_functions(code)

    exponent_integrate = _extract_step_control_exponent_line(integrate_code)
    exponent_reduction = _extract_step_control_exponent_line(reduction_code)

    assert exponent_integrate != "", (
        f"[{solver_name}] Step control exponent not found in integrate()"
    )
    assert exponent_reduction != "", (
        f"[{solver_name}] Step control exponent not found in integrate_with_reduction()"
    )
    assert exponent_integrate == exponent_reduction, (
        f"[{solver_name}] Step-size exponent mismatch:\n"
        f"  integrate():                {exponent_integrate}\n"
        f"  integrate_with_reduction(): {exponent_reduction}"
    )


@pytest.mark.parametrize("solver_name", list(SOLVER_COEFFICIENTS.keys()))
def test_property_9_same_m_coefficients(solver_name: str):
    """
    For any solver, integrate_with_reduction() uses the same M coefficient
    values in its state update as integrate().

    **Validates: Requirements 6.1, 6.2**
    """
    code = _generate_code_for_solver(solver_name)
    integrate_code, reduction_code = _split_integrate_functions(code)

    m_lines_integrate = _extract_m_coefficient_lines(integrate_code)
    m_lines_reduction = _extract_m_coefficient_lines(reduction_code)

    assert len(m_lines_integrate) > 0, (
        f"[{solver_name}] No M coefficient lines found in integrate()"
    )
    assert len(m_lines_reduction) > 0, (
        f"[{solver_name}] No M coefficient lines found in integrate_with_reduction()"
    )

    # Extract floating-point literals from M coefficient lines
    m_floats_integrate = _extract_float_literals_from_lines(m_lines_integrate)
    m_floats_reduction = _extract_float_literals_from_lines(m_lines_reduction)

    assert m_floats_integrate == m_floats_reduction, (
        f"[{solver_name}] M coefficient values differ between functions:\n"
        f"  integrate():                {m_floats_integrate[:10]}...\n"
        f"  integrate_with_reduction(): {m_floats_reduction[:10]}..."
    )


@pytest.mark.parametrize("solver_name", list(SOLVER_COEFFICIENTS.keys()))
def test_property_9_same_e_coefficients(solver_name: str):
    """
    For any solver, integrate_with_reduction() uses the same E coefficient
    values in its error estimate as integrate().

    **Validates: Requirements 6.1, 6.2**
    """
    code = _generate_code_for_solver(solver_name)
    integrate_code, reduction_code = _split_integrate_functions(code)

    e_lines_integrate = _extract_yerr_lines(integrate_code)
    e_lines_reduction = _extract_yerr_lines(reduction_code)

    assert len(e_lines_integrate) > 0, (
        f"[{solver_name}] No E coefficient (yerr_i) lines found in integrate()"
    )
    assert len(e_lines_reduction) > 0, (
        f"[{solver_name}] No E coefficient (yerr_i) lines found in integrate_with_reduction()"
    )

    # Extract floating-point literals from E coefficient lines
    e_floats_integrate = _extract_float_literals_from_lines(e_lines_integrate)
    e_floats_reduction = _extract_float_literals_from_lines(e_lines_reduction)

    assert e_floats_integrate == e_floats_reduction, (
        f"[{solver_name}] E coefficient values differ between functions:\n"
        f"  integrate():                {e_floats_integrate[:10]}...\n"
        f"  integrate_with_reduction(): {e_floats_reduction[:10]}..."
    )
