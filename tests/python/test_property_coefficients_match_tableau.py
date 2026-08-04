"""
Property-based test for generated coefficients matching tableau.

**Validates: Requirements 3.3, 3.4, 3.5, 3.6, 3.7**

Property 6: Generated coefficients match tableau
For any solver, the M, E, A, C, and Gamma[0] coefficient literals emitted in the
generated C++ code are numerically equal (within floating-point representation)
to the values stored in SOLVER_COEFFICIENTS[solver_name].
"""

import re
import tempfile

import pytest
import sympy as sp
from mkpp.codegen import SOLVER_COEFFICIENTS, generate_headers, get_A, get_C
from mkpp.lowering import compute_symbolic_lu_decomposition
from mkpp.model import (
    AerosolRepresentation,
    MechanismDefinition,
    PhaseMode,
    SpeciesDefinition,
)

# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------


def _build_test_mechanism(n_species: int = 3):
    """Build a minimal mechanism with n_species species and a non-trivial Jacobian."""
    species = [SpeciesDefinition(name=f"sp_{i}", phase=PhaseMode.GAS) for i in range(n_species)]

    # Build a sparse Jacobian with some non-zero off-diagonal entries
    entries = []
    for i in range(n_species):
        row = []
        for j in range(n_species):
            if i == j:
                # Diagonal: negative self-decay
                val = -sp.Float(1.0) * sp.Symbol(f"sp_{i}", positive=True) - sp.Float(0.1)
            elif abs(i - j) == 1:
                # Adjacent species coupling
                val = sp.Float(0.5) * sp.Symbol(f"sp_{j}", positive=True)
            else:
                val = sp.Integer(0)
            row.append(val)
        entries.append(row)

    matrix = sp.Matrix(entries)
    species_map = [f"sp_{i}" for i in range(n_species)]

    plan = compute_symbolic_lu_decomposition(matrix, species_map)

    # ODE RHS: simple decay + coupling
    f_vector = []
    for i in range(n_species):
        expr = -sp.Symbol(f"sp_{i}") * sp.Float(0.1)
        if i > 0:
            expr += sp.Symbol(f"sp_{i-1}") * sp.Float(0.05)
        f_vector.append(expr)

    sympy_meta = {
        "species_map": species_map,
        "f_implicit": sp.Matrix(f_vector),
        "f_explicit": sp.Matrix([sp.Integer(0)] * n_species),
        "jacobian_matrix": matrix,
        "adjoint_matrix": matrix.T,
        "mass_projector": sp.zeros(n_species, 1),
        "element_map": [],
    }

    mech = MechanismDefinition(
        name="test_coeff_match",
        description="Test mechanism for coefficient matching",
        aerosol_representation=AerosolRepresentation.BULK,
        species=species,
        phases=[],
        reactions=[],
    )
    mech.metadata = {
        "sympy_metadata": sympy_meta,
        "symbolic_lu_plan": plan,
    }

    return mech


def _generate_code_for_solver(solver_name: str) -> str:
    """Generate C++ code for the given solver and return the full source text."""
    mech = _build_test_mechanism(n_species=3)
    with tempfile.TemporaryDirectory() as tmp_dir:
        artifacts = generate_headers(mech, out_dir=tmp_dir, solver_name=solver_name)
        header_path = artifacts["header"]
        with open(header_path) as f:
            return f.read()


def _extract_float_literals_from_line(line: str) -> list:
    """Extract all floating-point literals from a C++ code line.

    Matches patterns like: 1.0, -0.5, 1.7071067811865475e+00, 0.43586652150845900
    """
    # Match floating point numbers (possibly negative, possibly with exponent)
    pattern = r"[-+]?\d+\.\d+(?:[eE][-+]?\d+)?"
    return [float(m) for m in re.findall(pattern, line)]


def _values_match(expected: float, actual: float, rel_tol: float = 1e-14) -> bool:
    """Compare two floats with relative tolerance, handling zero."""
    if expected == 0.0 and actual == 0.0:
        return True
    if expected == 0.0:
        return abs(actual) < 1e-15
    return abs(actual - expected) / abs(expected) <= rel_tol


# ---------------------------------------------------------------------------
# Property 6: Generated coefficients match tableau
# **Validates: Requirements 3.3, 3.4, 3.5, 3.6, 3.7**
# ---------------------------------------------------------------------------


@pytest.mark.parametrize("solver_name", list(SOLVER_COEFFICIENTS.keys()))
def test_property_6_gamma0_in_generated_code(solver_name: str):
    """
    For any solver, the Gamma[0] constant emitted as `g` in the generated C++ code
    is numerically equal to SOLVER_COEFFICIENTS[solver_name].Gamma[0].

    **Validates: Requirements 3.7**
    """
    tableau = SOLVER_COEFFICIENTS[solver_name]
    code = _generate_code_for_solver(solver_name)

    # Gamma[0] appears as: const double g = <value>;
    g_match = re.search(r"const double g = ([^;]+);", code)
    assert g_match is not None, f"{solver_name}: 'const double g = ...' not found in generated code"
    g_value = float(g_match.group(1))
    expected_g = tableau.Gamma[0]
    assert _values_match(
        expected_g, g_value
    ), f"{solver_name}: Gamma[0] mismatch: expected {expected_g:.17g}, got {g_value:.17g}"


@pytest.mark.parametrize("solver_name", list(SOLVER_COEFFICIENTS.keys()))
def test_property_6_m_coefficients_in_generated_code(solver_name: str):
    """
    For any solver, the M coefficient literals emitted in the solution update line
    are numerically equal to SOLVER_COEFFICIENTS[solver_name].M.

    **Validates: Requirements 3.3**
    """
    tableau = SOLVER_COEFFICIENTS[solver_name]
    code = _generate_code_for_solver(solver_name)

    # M coefficients appear in the solution update:
    # state(X) += <M[0]> * K1_Y + <M[1]> * K2_Y + ...
    # Look for lines matching: state(...) +=
    state_update_lines = [
        line.strip() for line in code.split("\n") if "state(" in line and "+=" in line
    ]
    assert len(state_update_lines) > 0, f"{solver_name}: No state update lines found"

    # Extract the M coefficients from the first state update line (species 0)
    # Pattern: <coeff> * K<stage>_0
    first_update = state_update_lines[0]
    extracted_m = _extract_m_coefficients(first_update, tableau.stages)

    # Verify each non-zero M coefficient
    non_zero_m = [(j, tableau.M[j]) for j in range(tableau.stages) if tableau.M[j] != 0.0]
    assert len(extracted_m) == len(non_zero_m), (
        f"{solver_name}: Expected {len(non_zero_m)} M terms, found {len(extracted_m)} "
        f"in line: {first_update}"
    )

    for (j, expected_val), (stage_found, actual_val) in zip(non_zero_m, extracted_m):
        assert stage_found == j + 1, f"{solver_name}: Expected K{j+1} term, found K{stage_found}"
        assert _values_match(expected_val, actual_val), (
            f"{solver_name}: M[{j}] mismatch: expected {expected_val:.17g}, "
            f"got {actual_val:.17g}"
        )


@pytest.mark.parametrize("solver_name", list(SOLVER_COEFFICIENTS.keys()))
def test_property_6_e_coefficients_in_generated_code(solver_name: str):
    """
    For any solver, the E coefficient literals emitted in the error estimate
    are numerically equal to SOLVER_COEFFICIENTS[solver_name].E.

    **Validates: Requirements 3.4**
    """
    tableau = SOLVER_COEFFICIENTS[solver_name]
    code = _generate_code_for_solver(solver_name)

    # E coefficients appear in: double yerr_i = <E[0]> * K1_0 + <E[1]> * K2_0 + ...
    yerr_lines = [line.strip() for line in code.split("\n") if "double yerr_i" in line]
    assert len(yerr_lines) > 0, f"{solver_name}: No yerr_i lines found"

    # Use the first yerr line (species 0)
    first_yerr = yerr_lines[0]
    extracted_e = _extract_stage_coefficients(first_yerr, tableau.stages, species_idx=0)

    # Verify each non-zero E coefficient
    non_zero_e = [(j, tableau.E[j]) for j in range(tableau.stages) if tableau.E[j] != 0.0]
    assert len(extracted_e) == len(non_zero_e), (
        f"{solver_name}: Expected {len(non_zero_e)} E terms, found {len(extracted_e)} "
        f"in line: {first_yerr}"
    )

    for (j, expected_val), (stage_found, actual_val) in zip(non_zero_e, extracted_e):
        assert (
            stage_found == j + 1
        ), f"{solver_name}: Expected K{j+1} term in yerr, found K{stage_found}"
        assert _values_match(expected_val, actual_val), (
            f"{solver_name}: E[{j}] mismatch: expected {expected_val:.17g}, "
            f"got {actual_val:.17g}"
        )


@pytest.mark.parametrize("solver_name", list(SOLVER_COEFFICIENTS.keys()))
def test_property_6_a_coefficients_in_generated_code(solver_name: str):
    """
    For any solver, the A coefficient literals emitted in intermediate state
    computations are numerically equal to the values from the tableau.

    **Validates: Requirements 3.5**
    """
    tableau = SOLVER_COEFFICIENTS[solver_name]
    code = _generate_code_for_solver(solver_name)

    # A coefficients appear in: double Y<stage>_<i> = S_<i> + <A(stage,j)> * K<j>_<i>
    # Check for each stage > 1
    for stage in range(2, tableau.stages + 1):
        # Find lines declaring Y<stage>_0 (first species)
        y_pattern = re.compile(rf"double Y{stage}_0\s*=\s*(.+);")
        y_matches = [m for m in y_pattern.finditer(code)]
        if not y_matches:
            # If A coefficients for this stage are all zero, Y may just be S_0
            all_zero = all(get_A(tableau, stage, j) == 0.0 for j in range(1, stage))
            if all_zero:
                continue
            pytest.fail(
                f"{solver_name}: Y{stage}_0 declaration not found, but A "
                f"has non-zero entries for stage {stage}"
            )

        y_expr = y_matches[0].group(1)

        # Extract coefficients from the A terms
        for j in range(1, stage):
            a_val = get_A(tableau, stage, j)
            if a_val == 0.0:
                continue

            # Look for the K<j>_0 term in this expression
            # Pattern: <coeff> * K<j>_0, or just K<j>_0 if coeff is 1.0
            k_pattern = re.compile(rf"([-+]?\d+\.?\d*(?:[eE][-+]?\d+)?)\s*\*\s*K{j}_0")
            k_match = k_pattern.search(y_expr)
            if k_match:
                actual_val = float(k_match.group(1))
            else:
                # Check if K<j>_0 appears without a coefficient (implies 1.0)
                if f"K{j}_0" in y_expr:
                    # Could be "+ K<j>_0" meaning coeff = 1.0
                    actual_val = 1.0
                else:
                    pytest.fail(
                        f"{solver_name}: A({stage},{j}) = {a_val:.17g} but K{j}_0 "
                        f"not found in Y{stage}_0 = {y_expr}"
                    )

            assert _values_match(a_val, actual_val), (
                f"{solver_name}: A({stage},{j}) mismatch: "
                f"expected {a_val:.17g}, got {actual_val:.17g}"
            )


@pytest.mark.parametrize("solver_name", list(SOLVER_COEFFICIENTS.keys()))
def test_property_6_c_coefficients_in_generated_code(solver_name: str):
    """
    For any solver, the C coefficient literals emitted in the RHS formation
    are numerically equal to the values from the tableau.

    **Validates: Requirements 3.6**
    """
    tableau = SOLVER_COEFFICIENTS[solver_name]
    code = _generate_code_for_solver(solver_name)

    # C coefficients appear in:
    # double rhs<stage>_<i> = F<x>_<i> + (<C(stage,j)> / dt) * K<j>_<i>
    # Check for each stage > 1
    for stage in range(2, tableau.stages + 1):
        # Find lines declaring rhs<stage>_0 (first species)
        rhs_pattern = re.compile(rf"double rhs{stage}_0\s*=\s*(.+);")
        rhs_matches = [m for m in rhs_pattern.finditer(code)]
        if not rhs_matches:
            # If all C for this stage are zero, rhs just equals F
            all_zero = all(get_C(tableau, stage, j) == 0.0 for j in range(1, stage))
            if all_zero:
                continue
            pytest.fail(
                f"{solver_name}: rhs{stage}_0 declaration not found, but C "
                f"has non-zero entries for stage {stage}"
            )

        rhs_expr = rhs_matches[0].group(1)

        # Extract C coefficients from the expression
        for j in range(1, stage):
            c_val = get_C(tableau, stage, j)
            if c_val == 0.0:
                continue

            # Pattern: (<C> / dt) * K<j>_0
            # The format is: (C_VALUE / dt) * K<j>_0
            c_pattern = re.compile(
                rf"\(?([-+]?\d+\.?\d*(?:[eE][-+]?\d+)?)\s*/\s*dt\)?\s*\*\s*K{j}_0"
            )
            c_match = c_pattern.search(rhs_expr)
            if c_match:
                actual_val = float(c_match.group(1))
            else:
                pytest.fail(
                    f"{solver_name}: C({stage},{j}) = {c_val:.17g} but matching "
                    f"pattern not found in rhs{stage}_0 = {rhs_expr}"
                )

            assert _values_match(c_val, actual_val), (
                f"{solver_name}: C({stage},{j}) mismatch: "
                f"expected {c_val:.17g}, got {actual_val:.17g}"
            )


# ---------------------------------------------------------------------------
# Extraction helpers
# ---------------------------------------------------------------------------


def _extract_m_coefficients(line: str, stages: int) -> list:
    """Extract (stage_num, coefficient_value) pairs from a state update line.

    Handles patterns like:
      state(0) += 1.0 * K1_0 + 6.169... * K2_0 + ...
      state(0) += K1_0 + K2_0  (coeff = 1.0 implicit)
    """
    results = []
    for stage in range(1, stages + 1):
        # Try to find: <coeff> * K<stage>_<species>
        pattern = re.compile(rf"([-+]?\s*\d+\.?\d*(?:[eE][-+]?\d+)?)\s*\*\s*K{stage}_\d+")
        match = pattern.search(line)
        if match:
            coeff_str = match.group(1).replace(" ", "")
            results.append((stage, float(coeff_str)))
        else:
            # Check for bare K<stage>_<species> (implies coeff=1.0)
            # Handle "+ K<stage>_" or "= K<stage>_" patterns
            bare_pattern = re.compile(rf"(?:^|[+=\s])\s*K{stage}_\d+")
            if bare_pattern.search(line):
                results.append((stage, 1.0))
    return results


def _extract_stage_coefficients(line: str, stages: int, species_idx: int = 0) -> list:
    """Extract (stage_num, coefficient_value) pairs from a line referencing K<stage>_<species>.

    Handles patterns like:
      double yerr_i = 0.5 * K1_0 + -2.907... * K2_0 + ...
    """
    results = []
    for stage in range(1, stages + 1):
        # Try to find: <coeff> * K<stage>_<species>
        pattern = re.compile(rf"([-+]?\s*\d+\.?\d*(?:[eE][-+]?\d+)?)\s*\*\s*K{stage}_{species_idx}")
        match = pattern.search(line)
        if match:
            coeff_str = match.group(1).replace(" ", "")
            results.append((stage, float(coeff_str)))
        else:
            # Check for bare K<stage>_<species> (implies coeff=1.0)
            bare_pattern = re.compile(rf"(?:^|[+=\s])\s*K{stage}_{species_idx}(?:\s|$|[+;])")
            if bare_pattern.search(line):
                results.append((stage, 1.0))
    return results
