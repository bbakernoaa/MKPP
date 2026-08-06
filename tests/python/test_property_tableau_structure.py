"""
Property-based test for Rosenbrock tableau structural consistency.

**Validates: Requirements 2.1, 2.2**

Property 2: Tableau structural consistency
For any solver name in the valid set, the corresponding RosenbrockTableau entry satisfies:
  len(A) == len(C) == stages*(stages-1)//2
  len(M) == len(E) == len(Alpha) == len(Gamma) == len(NewF) == stages
"""

import pytest
from mkpp.codegen import SOLVER_COEFFICIENTS, RosenbrockTableau


@pytest.mark.parametrize("solver_name", list(SOLVER_COEFFICIENTS.keys()))
def test_property_2_tableau_structural_consistency(solver_name: str):
    """
    For any solver name in the valid set, the corresponding RosenbrockTableau
    entry satisfies the structural invariants.

    **Validates: Requirements 2.1, 2.2**
    """
    tableau = SOLVER_COEFFICIENTS[solver_name]

    # Verify the tableau is a RosenbrockTableau instance
    assert isinstance(tableau, RosenbrockTableau), f"{solver_name}: expected RosenbrockTableau, got {type(tableau)}"

    stages = tableau.stages

    # stages must be a positive integer
    assert isinstance(stages, int), f"{solver_name}: stages must be an int, got {type(stages)}"
    assert stages > 0, f"{solver_name}: stages must be positive, got {stages}"

    # Strictly lower-triangular arrays: len == stages*(stages-1)//2
    expected_tri = stages * (stages - 1) // 2
    assert len(tableau.A) == expected_tri, f"{solver_name}: len(A)={len(tableau.A)} != stages*(stages-1)//2={expected_tri}"
    assert len(tableau.C) == expected_tri, f"{solver_name}: len(C)={len(tableau.C)} != stages*(stages-1)//2={expected_tri}"

    # Stage-length arrays: len == stages
    assert len(tableau.M) == stages, f"{solver_name}: len(M)={len(tableau.M)} != stages={stages}"
    assert len(tableau.E) == stages, f"{solver_name}: len(E)={len(tableau.E)} != stages={stages}"
    assert len(tableau.Alpha) == stages, f"{solver_name}: len(Alpha)={len(tableau.Alpha)} != stages={stages}"
    assert len(tableau.Gamma) == stages, f"{solver_name}: len(Gamma)={len(tableau.Gamma)} != stages={stages}"
    assert len(tableau.NewF) == stages, f"{solver_name}: len(NewF)={len(tableau.NewF)} != stages={stages}"

    # ELO must be a positive float
    assert isinstance(tableau.ELO, float), f"{solver_name}: ELO must be a float, got {type(tableau.ELO)}"
    assert tableau.ELO > 0.0, f"{solver_name}: ELO must be positive, got {tableau.ELO}"
