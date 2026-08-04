"""
Property-based test for step-size exponent matching ELO.

**Validates: Requirements 4.1, 4.2, 4.3**

Property 7: Step-size exponent matches ELO
For any solver, the step-size control exponent emitted in the generated code
equals 1.0 / tableau.ELO.
"""

import re
import tempfile

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
        name="test_step_size_exponent",
        description="Toy mechanism for step-size exponent property test",
        aerosol_representation=AerosolRepresentation.BULK,
        species=[sp_a, sp_b, sp_c],
        phases=[],
        reactions=[rxn1, rxn2],
    )


def _generate_code_for_solver(solver_name: str) -> str:
    """Generate C++ code for the given solver and return the full source text."""
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
        header_path = artifacts["header"]
        with open(header_path) as f:
            return f.read()


@pytest.mark.parametrize("solver_name", list(SOLVER_COEFFICIENTS.keys()))
def test_property_7_step_size_comment_mentions_correct_order(solver_name: str):
    """
    For any solver, the step-size control comment mentions the correct order
    (ELO value) and the correct exponent 1/ELO.

    **Validates: Requirements 4.1, 4.2, 4.3**
    """
    tableau = SOLVER_COEFFICIENTS[solver_name]
    code = _generate_code_for_solver(solver_name)
    elo_exponent = 1.0 / tableau.ELO

    # The generated code emits a comment like:
    # // Step Size Control (order 3: exponent = 1/3 = 0.33333333333333331)
    comment_pattern = re.compile(
        r"// Step Size Control \(order (\d+): exponent = 1/(\d+) = ([\d.e+-]+)\)"
    )
    matches = comment_pattern.findall(code)
    assert (
        len(matches) >= 1
    ), f"Solver '{solver_name}': No step-size control comment found in generated code"

    for order_str, divisor_str, exponent_str in matches:
        # Verify the order matches ELO
        assert int(order_str) == int(tableau.ELO), (
            f"Solver '{solver_name}': Comment says order {order_str}, "
            f"expected {int(tableau.ELO)}"
        )
        # Verify the divisor matches ELO
        assert int(divisor_str) == int(tableau.ELO), (
            f"Solver '{solver_name}': Comment says 1/{divisor_str}, "
            f"expected 1/{int(tableau.ELO)}"
        )
        # Verify the exponent value is numerically correct
        actual_exponent = float(exponent_str)
        assert abs(actual_exponent - elo_exponent) < 1e-10, (
            f"Solver '{solver_name}': Comment exponent value {actual_exponent} "
            f"does not match 1/ELO = {elo_exponent}"
        )


@pytest.mark.parametrize("solver_name", list(SOLVER_COEFFICIENTS.keys()))
def test_property_7_step_size_exponent_matches_elo(solver_name: str):
    """
    For any solver, the step-size control exponent emitted in the generated code
    equals 1.0 / tableau.ELO. Specifically:
    - ELO=2 (ros2): uses Kokkos::sqrt(err_norm) — equivalent to exponent 0.5
    - ELO=3 (ros3, rodas3): uses Kokkos::cbrt(err_norm) — equivalent to exponent 1/3
    - ELO=4 (ros4, rodas4): uses Kokkos::pow(err_norm, -0.25) — literal 0.25 exponent

    **Validates: Requirements 4.1, 4.2, 4.3**
    """
    tableau = SOLVER_COEFFICIENTS[solver_name]
    code = _generate_code_for_solver(solver_name)
    elo_exponent = 1.0 / tableau.ELO

    if tableau.ELO == 2.0:
        # For ELO=2, the code uses: safety / Kokkos::sqrt(err_norm)
        # which is equivalent to safety * err_norm^(-1/2), exponent = 0.5
        assert "Kokkos::sqrt(err_norm)" in code, (
            f"Solver '{solver_name}' (ELO=2): Expected 'Kokkos::sqrt(err_norm)' "
            f"for exponent 1/2, not found in generated code"
        )
        # Verify it's in the factor computation line
        factor_pattern = re.compile(r"double factor = safety / Kokkos::sqrt\(err_norm\)")
        assert factor_pattern.search(code) is not None, (
            f"Solver '{solver_name}' (ELO=2): Expected "
            f"'double factor = safety / Kokkos::sqrt(err_norm)'"
        )

    elif tableau.ELO == 3.0:
        # For ELO=3, the code uses: safety / Kokkos::cbrt(err_norm)
        # which is equivalent to safety * err_norm^(-1/3), exponent = 1/3
        assert "Kokkos::cbrt(err_norm)" in code, (
            f"Solver '{solver_name}' (ELO=3): Expected 'Kokkos::cbrt(err_norm)' "
            f"for exponent 1/3, not found in generated code"
        )
        # Verify it's in the factor computation line
        factor_pattern = re.compile(r"double factor = safety / Kokkos::cbrt\(err_norm\)")
        assert factor_pattern.search(code) is not None, (
            f"Solver '{solver_name}' (ELO=3): Expected "
            f"'double factor = safety / Kokkos::cbrt(err_norm)'"
        )

    else:
        # For ELO=4, the code uses: safety * Kokkos::pow(err_norm, -0.25...)
        # The exponent literal should be 1/ELO = 0.25
        pow_pattern = re.compile(r"double factor = safety \* Kokkos::pow\(err_norm, -([\d.e+-]+)\)")
        pow_match = pow_pattern.search(code)
        assert pow_match is not None, (
            f"Solver '{solver_name}' (ELO={tableau.ELO}): Expected "
            f"'double factor = safety * Kokkos::pow(err_norm, -{elo_exponent})' "
            f"not found in generated code"
        )
        actual_literal = float(pow_match.group(1))
        assert abs(actual_literal - elo_exponent) < 1e-10, (
            f"Solver '{solver_name}' (ELO={tableau.ELO}): "
            f"Pow exponent literal {actual_literal} does not match "
            f"1/ELO = {elo_exponent}"
        )


@pytest.mark.parametrize("solver_name", list(SOLVER_COEFFICIENTS.keys()))
def test_property_7_both_functions_use_same_exponent(solver_name: str):
    """
    For any solver, both integrate() and integrate_with_reduction() use the same
    step-size control exponent (1/ELO).

    **Validates: Requirements 4.1, 4.2, 4.3**
    """
    tableau = SOLVER_COEFFICIENTS[solver_name]
    code = _generate_code_for_solver(solver_name)

    # The step-size comment appears once per function (integrate + integrate_with_reduction)
    comment_pattern = re.compile(
        r"// Step Size Control \(order (\d+): exponent = 1/(\d+) = ([\d.e+-]+)\)"
    )
    matches = comment_pattern.findall(code)

    # Should appear exactly twice (once in each function)
    assert len(matches) == 2, (
        f"Solver '{solver_name}': Expected 2 step-size control comments "
        f"(one per function), found {len(matches)}"
    )

    # Both should have identical ELO and exponent values
    order_1, divisor_1, exp_1 = matches[0]
    order_2, divisor_2, exp_2 = matches[1]
    assert order_1 == order_2, (
        f"Solver '{solver_name}': Mismatched orders between integrate() "
        f"and integrate_with_reduction(): {order_1} vs {order_2}"
    )
    assert divisor_1 == divisor_2, (
        f"Solver '{solver_name}': Mismatched divisors between functions: "
        f"{divisor_1} vs {divisor_2}"
    )
    assert exp_1 == exp_2, (
        f"Solver '{solver_name}': Mismatched exponents between functions: " f"{exp_1} vs {exp_2}"
    )
