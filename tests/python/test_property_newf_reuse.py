"""
Property-based test for NewF=false reuse behavior.

**Validates: Requirements 3.2**

Property 5: NewF=false reuses prior function evaluation
For any solver and any stage i where NewF[i] is false, the generated code for
stage i+1 does not emit a new rate computation but reuses the function evaluation
variable from stage i.
"""

import re
import tempfile

import pytest
from mkpp.codegen import SOLVER_COEFFICIENTS, generate_headers
from mkpp.model import (
    AerosolRepresentation,
    MechanismDefinition,
    PhaseMode,
    SpeciesDefinition,
    SymbolicLUPlan,
)


def _build_mechanism_with_lu_plan(n_species: int = 2) -> MechanismDefinition:
    """
    Build a minimal mechanism with a trivial diagonal LU plan so that
    the codegen emits full Rosenbrock stage logic.
    """
    species = [SpeciesDefinition(name=f"sp_{i}", phase=PhaseMode.GAS) for i in range(n_species)]
    mech = MechanismDefinition(
        name="test_newf",
        description="Test mechanism for NewF reuse property",
        aerosol_representation=AerosolRepresentation.BULK,
        species=species,
        phases=[],
        reactions=[],
    )

    # Construct a trivial diagonal LU plan (identity-like W matrix)
    species_map = [f"sp_{i}" for i in range(n_species)]
    plan = SymbolicLUPlan(
        num_species=n_species,
        species_map=species_map,
        non_zero_jacobian=[(i, i, f"C_{i}") for i in range(n_species)],
        l_expressions=[],
        u_expressions=[(i, i, f"W_{i}_{i}") for i in range(n_species)],
        lu_expressions_ordered=[("U", i, i, f"W_{i}_{i}") for i in range(n_species)],
        forward_sub_steps=[(i, f"b_{i}") for i in range(n_species)],
        backward_sub_steps=[(i, f"y_{i} / U_{i}_{i}") for i in reversed(range(n_species))],
    )

    mech.metadata = {
        "symbolic_lu_plan": plan,
    }
    return mech


def _generate_code(solver_name: str) -> str:
    """Generate header code for the given solver using a minimal mechanism with LU plan."""
    mech = _build_mechanism_with_lu_plan()
    with tempfile.TemporaryDirectory() as tmp_dir:
        artifacts = generate_headers(mech, out_dir=tmp_dir, solver_name=solver_name)
        header_path = artifacts["header"]
        with open(header_path) as f:
            return f.read()


# Solvers with NewF=false stages and the expected reuse behavior:
# - ros3: NewF = [True, True, False] -> stage 3 reuses F2
# - ros4: NewF = [True, True, True, False] -> stage 4 reuses F3
# - rodas3: NewF = [True, False, True, True] -> stage 2 reuses F1
SOLVERS_WITH_NEWF_FALSE = [
    ("ros3", 3, 2),  # (solver, stage_with_reuse, prior_F_stage)
    ("ros4", 4, 3),  # stage 4 reuses F3
    ("rodas3", 2, 1),  # stage 2 reuses F1
]


@pytest.mark.parametrize(
    "solver_name,reuse_stage,prior_f_stage",
    SOLVERS_WITH_NEWF_FALSE,
    ids=[s[0] for s in SOLVERS_WITH_NEWF_FALSE],
)
def test_property_5_newf_false_no_fresh_evaluation(
    solver_name: str, reuse_stage: int, prior_f_stage: int
):
    """
    For solvers with NewF=false stages, the generated code should NOT emit
    a fresh F evaluation (F{reuse_stage}_0 = ...) for that stage.

    **Validates: Requirements 3.2**
    """
    code = _generate_code(solver_name)

    # Verify that there is NO declaration of F{reuse_stage}_*
    # A fresh F evaluation would look like: "double F{reuse_stage}_0 = ..."
    fresh_f_pattern = re.compile(rf"\bdouble\s+F{reuse_stage}_\d+\s*=")
    fresh_f_matches = fresh_f_pattern.findall(code)
    assert len(fresh_f_matches) == 0, (
        f"{solver_name}: Found fresh F{reuse_stage} evaluation when NewF[{reuse_stage - 1}]=false. "
        f"Matches: {fresh_f_matches[:5]}"
    )


@pytest.mark.parametrize(
    "solver_name,reuse_stage,prior_f_stage",
    SOLVERS_WITH_NEWF_FALSE,
    ids=[s[0] for s in SOLVERS_WITH_NEWF_FALSE],
)
def test_property_5_newf_false_reuse_comment(
    solver_name: str, reuse_stage: int, prior_f_stage: int
):
    """
    For solvers with NewF=false stages, the generated code should contain
    a comment indicating reuse of the prior F evaluation.

    **Validates: Requirements 3.2**
    """
    code = _generate_code(solver_name)

    # The codegen emits: "// NewF=false: reuse F{prior_f_stage} for stage {reuse_stage}"
    reuse_comment_pattern = re.compile(
        rf"NewF=false:\s*reuse\s+F{prior_f_stage}\s+for\s+stage\s+{reuse_stage}"
    )
    assert (
        reuse_comment_pattern.search(code) is not None
    ), f"{solver_name}: Missing 'NewF=false: reuse F{prior_f_stage} for stage {reuse_stage}' comment"


@pytest.mark.parametrize(
    "solver_name,reuse_stage,prior_f_stage",
    SOLVERS_WITH_NEWF_FALSE,
    ids=[s[0] for s in SOLVERS_WITH_NEWF_FALSE],
)
def test_property_5_newf_false_rhs_references_prior_f(
    solver_name: str, reuse_stage: int, prior_f_stage: int
):
    """
    For solvers with NewF=false stages, the RHS formation for that stage should
    reference the prior stage's F variable (F{prior_f_stage}_*), not F{reuse_stage}_*.

    **Validates: Requirements 3.2**
    """
    code = _generate_code(solver_name)

    # The RHS for the reuse stage should reference F{prior_f_stage}
    # Look for rhs{reuse_stage}_* lines that reference F{prior_f_stage}_*
    rhs_lines = [
        line
        for line in code.split("\n")
        if f"rhs{reuse_stage}_" in line and "=" in line and "//" not in line.split("=")[0]
    ]
    assert len(rhs_lines) > 0, f"{solver_name}: No rhs{reuse_stage} lines found in generated code"

    # At least one rhs line should reference the prior F variable
    has_prior_f_ref = any(f"F{prior_f_stage}_" in line for line in rhs_lines)
    assert has_prior_f_ref, (
        f"{solver_name}: rhs{reuse_stage} lines don't reference F{prior_f_stage}. "
        f"Lines: {rhs_lines[:3]}"
    )

    # Verify none of the rhs lines reference the non-existent F{reuse_stage}
    has_reuse_stage_f_ref = any(f"F{reuse_stage}_" in line for line in rhs_lines)
    assert not has_reuse_stage_f_ref, (
        f"{solver_name}: rhs{reuse_stage} lines incorrectly reference F{reuse_stage} "
        f"(should use F{prior_f_stage}). Lines: {rhs_lines[:3]}"
    )


# Negative control: solvers with all NewF=True should have ALL F stages evaluated
SOLVERS_ALL_NEWF_TRUE = ["ros2", "rodas4"]


@pytest.mark.parametrize("solver_name", SOLVERS_ALL_NEWF_TRUE)
def test_property_5_negative_control_all_newf_true(solver_name: str):
    """
    For solvers where all NewF entries are True, every stage should have
    its own fresh F evaluation (F{stage}_0 declaration exists for all stages).

    **Validates: Requirements 3.2**
    """
    code = _generate_code(solver_name)
    tableau = SOLVER_COEFFICIENTS[solver_name]

    for stage in range(1, tableau.stages + 1):
        # Each stage should have a fresh F evaluation
        fresh_f_pattern = re.compile(rf"\bdouble\s+F{stage}_0\s*=")
        assert (
            fresh_f_pattern.search(code) is not None
        ), f"{solver_name}: Missing F{stage}_0 declaration even though NewF[{stage - 1}]=True"
