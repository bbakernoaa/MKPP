"""
Property-based test for stage count matching generated code.

**Validates: Requirements 3.1, 5.3**

Property 4: Stage count matches generated code
For any solver and any mechanism, the generated integrate() function contains
exactly tableau.stages forward/backward substitution blocks (one per stage solve).
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


def _build_toy_mechanism():
    """Build a simple 3-species toy mechanism for code generation testing."""
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
        name="test_stage_count",
        description="Toy mechanism for stage count property test",
        aerosol_representation=AerosolRepresentation.BULK,
        species=[sp_a, sp_b, sp_c],
        phases=[],
        reactions=[rxn1, rxn2],
    )


@pytest.mark.parametrize("solver_name", list(SOLVER_COEFFICIENTS.keys()))
def test_property_4_stage_count_matches_generated_code(solver_name: str):
    """
    For any solver and any mechanism, the generated integrate() function contains
    exactly tableau.stages forward/backward substitution blocks (one per stage solve).

    **Validates: Requirements 3.1, 5.3**
    """
    tableau = SOLVER_COEFFICIENTS[solver_name]

    # Build toy mechanism and prepare lowering data
    mech = _build_toy_mechanism()
    lowering_data = prepare_unified_jacobian(mech)
    plan = compute_symbolic_lu_decomposition(
        lowering_data["jacobian_matrix"], lowering_data["species_map"]
    )
    mech.metadata = {
        "sympy_metadata": lowering_data,
        "symbolic_lu_plan": plan,
    }

    # Generate headers with the selected solver
    with tempfile.TemporaryDirectory() as tmp_dir:
        artifacts = generate_headers(mech, out_dir=tmp_dir, solver_name=solver_name)
        header_path = artifacts["header"]
        with open(header_path) as f:
            code = f.read()

    # Count stage comments "// --- Stage N ---" in generated code
    stage_comments = re.findall(r"// --- Stage \d+ ---", code)

    # The integrate() and integrate_with_reduction() functions each emit
    # tableau.stages stage blocks. Count total and verify.
    # We expect exactly 2 * tableau.stages (one set per function).
    expected_total = 2 * tableau.stages
    assert len(stage_comments) == expected_total, (
        f"Solver '{solver_name}' (stages={tableau.stages}): "
        f"expected {expected_total} stage comments (2 functions x {tableau.stages} stages), "
        f"found {len(stage_comments)}"
    )

    # Additionally verify that within each function, stages are numbered 1..S sequentially
    # Extract stage numbers
    stage_numbers = [int(re.search(r"Stage (\d+)", c).group(1)) for c in stage_comments]
    expected_sequence = list(range(1, tableau.stages + 1)) * 2
    assert stage_numbers == expected_sequence, (
        f"Solver '{solver_name}': stage numbering mismatch. "
        f"Expected {expected_sequence}, got {stage_numbers}"
    )

    # Verify each stage has K{stage}_0 variable declarations (backward substitution output)
    for stage_num in range(1, tableau.stages + 1):
        k_var = f"K{stage_num}_0"
        assert (
            k_var in code
        ), f"Solver '{solver_name}': missing stage variable '{k_var}' in generated code"
