"""Unit tests for adjoint/TLM mathematical correctness with equilibrium reactions.

Task 8.5 — Verifies the MATHEMATICAL properties of the adjoint and TLM
at the symbolic level. Unlike task 8.1/8.2 tests (which verify C++ code
generation), these tests work directly with the SymPy Jacobian matrix from
`prepare_unified_jacobian()` to confirm:

1. The adjoint matrix IS the Jacobian transpose (J^T)
2. Equilibrium introduces non-zero off-diagonal entries in J and J^T
3. Equilibrium coupling is bidirectional (J[i,j] != 0 implies J[j,i] != 0)
4. Transposing twice recovers the original ((J^T)^T == J)
5. Numerical evaluation of the Jacobian is well-conditioned (no NaN/Inf)

These are universal mathematical properties that hold regardless of the
code generation backend.

Requirements referenced: 6.1, 6.2, 6.4
"""

import pytest
import sympy as sp
from mkpp.lowering import prepare_unified_jacobian
from mkpp.model import (
    AerosolRepresentation,
    EquilibriumDefinition,
    MechanismDefinition,
    PhaseMode,
    SpeciesDefinition,
)

# ---------------------------------------------------------------------------
# Mechanism fixture
# ---------------------------------------------------------------------------


def _mechanism_with_equilibrium() -> MechanismDefinition:
    """Build a mechanism with equilibrium reactions for adjoint/TLM testing.

    Uses the species names expected by the NH4_NO3_SO4 equilibrium model:
    - reduced_nitrogen: NH3 (gas) + NH4a (aerosol)
    - oxidized_nitrogen: HNO3 (gas) + NO3an1 (aerosol)
    - sulfate: SO2 (gas) + SO4 (aerosol)

    The equilibrium model returns partition expressions keyed by these exact
    species names, so the mechanism must match them.
    """
    return MechanismDefinition(
        name="adj_tlm_math_test",
        description="Mathematical adjoint/TLM test with equilibrium",
        aerosol_representation=AerosolRepresentation.BULK,
        species=[
            SpeciesDefinition(name="NH3", phase=PhaseMode.GAS, elements={"N": 1, "H": 3}),
            SpeciesDefinition(name="NH4a", phase=PhaseMode.AEROSOL, elements={"N": 1, "H": 4}),
            SpeciesDefinition(name="HNO3", phase=PhaseMode.GAS, elements={"N": 1, "O": 3, "H": 1}),
            SpeciesDefinition(name="NO3an1", phase=PhaseMode.AEROSOL, elements={"N": 1, "O": 3}),
            SpeciesDefinition(name="SO2", phase=PhaseMode.GAS, elements={"S": 1, "O": 2}),
            SpeciesDefinition(name="SO4", phase=PhaseMode.AEROSOL, elements={"S": 1, "O": 4}),
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
            )
        ],
    )


@pytest.fixture
def jacobian_result():
    """Prepare the unified Jacobian result for the equilibrium mechanism."""
    mech = _mechanism_with_equilibrium()
    return prepare_unified_jacobian(mech)


# ---------------------------------------------------------------------------
# Test 1: Adjoint matrix is Jacobian transpose
# ---------------------------------------------------------------------------


class TestAdjointIsJacobianTranspose:
    """Verify adjoint_matrix == jacobian_matrix.T for equilibrium mechanism.

    Validates: Requirements 6.1, 6.2
    """

    def test_adjoint_matrix_is_jacobian_transpose(self, jacobian_result):
        """Verify adjoint_matrix == jacobian_matrix.T element-by-element.

        The adjoint of the linearized system is defined as the transpose of
        the Jacobian. This is the foundational property that makes adjoint
        sensitivity analysis correct.
        """
        J = jacobian_result["jacobian_matrix"]
        J_T = jacobian_result["adjoint_matrix"]

        N = J.shape[0]
        assert J.shape == J_T.shape, f"Jacobian and adjoint should have same shape. " f"J: {J.shape}, J^T: {J_T.shape}"

        for i in range(N):
            for j in range(N):
                diff = sp.simplify(J[i, j] - J_T[j, i])
                assert diff == 0, (
                    f"adjoint_matrix[{j},{i}] should equal jacobian_matrix[{i},{j}]. "
                    f"J[{i},{j}] = {J[i, j]}, J^T[{j},{i}] = {J_T[j, i]}, "
                    f"difference = {diff}"
                )


# ---------------------------------------------------------------------------
# Test 2: Adjoint matrix contains equilibrium entries
# ---------------------------------------------------------------------------


class TestAdjointContainsEquilibriumEntries:
    """Verify J^T has non-zero off-diagonal entries from equilibrium coupling.

    Validates: Requirements 6.1
    """

    def test_adjoint_matrix_contains_equilibrium_entries(self, jacobian_result):
        """Verify J^T has non-zero off-diagonal entries from equilibrium coupling.

        Equilibrium partitioning between NH3 and NH4a means:
        - J[NH3, NH4a] != 0 (NH3 depends on NH4a through total species)
        - J^T[NH4a, NH3] = J[NH3, NH4a] != 0

        The adjoint propagates sensitivities backward through this coupling,
        so it MUST contain these entries.
        """
        J_T = jacobian_result["adjoint_matrix"]
        species_map = jacobian_result["species_map"]

        nh3_idx = species_map.index("NH3")
        nh4a_idx = species_map.index("NH4a")

        # J^T[NH4a, NH3] = J[NH3, NH4a] should be non-zero
        assert J_T[nh4a_idx, nh3_idx] != 0, (
            f"J^T[NH4a, NH3] should be non-zero due to equilibrium coupling. " f"Got: {J_T[nh4a_idx, nh3_idx]}"
        )

        # J^T[NH3, NH4a] = J[NH4a, NH3] should be non-zero
        assert J_T[nh3_idx, nh4a_idx] != 0, (
            f"J^T[NH3, NH4a] should be non-zero due to equilibrium coupling. " f"Got: {J_T[nh3_idx, nh4a_idx]}"
        )

        # Count total off-diagonal non-zero entries in J^T
        N = J_T.shape[0]
        off_diag_count = 0
        for i in range(N):
            for j in range(N):
                if i != j and J_T[i, j] != 0:
                    off_diag_count += 1

        assert off_diag_count > 0, "Adjoint matrix should have non-zero off-diagonal entries " "from equilibrium coupling"


# ---------------------------------------------------------------------------
# Test 3: TLM Jacobian contains equilibrium entries
# ---------------------------------------------------------------------------


class TestTLMJacobianContainsEquilibriumEntries:
    """Verify J has non-zero off-diagonal entries from equilibrium coupling.

    Validates: Requirements 6.2
    """

    def test_tlm_jacobian_contains_equilibrium_entries(self, jacobian_result):
        """Verify J has non-zero off-diagonal entries from equilibrium coupling.

        The TLM computes J * delta_C. For this to correctly propagate
        perturbations through equilibrium coupling, J must contain off-diagonal
        entries between coupled species.
        """
        J = jacobian_result["jacobian_matrix"]
        species_map = jacobian_result["species_map"]

        nh3_idx = species_map.index("NH3")
        nh4a_idx = species_map.index("NH4a")
        hno3_idx = species_map.index("HNO3")
        no3an1_idx = species_map.index("NO3an1")

        # Within reduced_nitrogen group: NH3 <-> NH4a coupling
        assert J[nh3_idx, nh4a_idx] != 0, (
            f"J[NH3, NH4a] should be non-zero for TLM equilibrium coupling. " f"Got: {J[nh3_idx, nh4a_idx]}"
        )
        assert J[nh4a_idx, nh3_idx] != 0, (
            f"J[NH4a, NH3] should be non-zero for TLM equilibrium coupling. " f"Got: {J[nh4a_idx, nh3_idx]}"
        )

        # Within oxidized_nitrogen group: HNO3 <-> NO3an1 coupling
        assert J[hno3_idx, no3an1_idx] != 0, (
            f"J[HNO3, NO3an1] should be non-zero for TLM equilibrium coupling. " f"Got: {J[hno3_idx, no3an1_idx]}"
        )
        assert J[no3an1_idx, hno3_idx] != 0, (
            f"J[NO3an1, HNO3] should be non-zero for TLM equilibrium coupling. " f"Got: {J[no3an1_idx, hno3_idx]}"
        )


# ---------------------------------------------------------------------------
# Test 4: Equilibrium Jacobian symmetry pattern (bidirectional coupling)
# ---------------------------------------------------------------------------


class TestEquilibriumJacobianSymmetryPattern:
    """Verify bidirectional coupling within the same equilibrium group.

    For species sharing a total species constraint (e.g., NH3 and NH4a share
    reduced_nitrogen = C_NH3 + C_NH4a), the coupling is inherently bidirectional:
    J[i,j] != 0 implies J[j,i] != 0.

    Note: This symmetry holds WITHIN a group because both species contribute to
    the same total. Cross-group coupling (e.g., NH3 depending on SO4 through the
    sulfate ratio R) need not be symmetric because SO2's equilibrium expression
    is trivially zero.

    Validates: Requirements 6.1, 6.4
    """

    def test_equilibrium_jacobian_symmetry_pattern(self, jacobian_result):
        """Verify J[i,j] != 0 implies J[j,i] != 0 within equilibrium groups.

        For the NH3 <-> NH4a equilibrium (reduced_nitrogen group), both
        species share the total (C_NH3 + C_NH4a). This means:
        - d(f_NH3)/d(C_NH4a) != 0  AND  d(f_NH4a)/d(C_NH3) != 0
        - The coupling is inherently bidirectional within the group.
        """
        J = jacobian_result["jacobian_matrix"]
        species_map = jacobian_result["species_map"]

        # Check bidirectional coupling within reduced_nitrogen group
        nh3_idx = species_map.index("NH3")
        nh4a_idx = species_map.index("NH4a")

        # NH3 <-> NH4a: if one direction has coupling, both should
        if J[nh3_idx, nh4a_idx] != 0:
            assert J[nh4a_idx, nh3_idx] != 0, (
                "Bidirectional coupling violated within reduced_nitrogen: " "J[NH3, NH4a] != 0 but J[NH4a, NH3] == 0"
            )
        if J[nh4a_idx, nh3_idx] != 0:
            assert J[nh3_idx, nh4a_idx] != 0, (
                "Bidirectional coupling violated within reduced_nitrogen: " "J[NH4a, NH3] != 0 but J[NH3, NH4a] == 0"
            )

        # Check bidirectional coupling within oxidized_nitrogen group
        hno3_idx = species_map.index("HNO3")
        no3an1_idx = species_map.index("NO3an1")

        if J[hno3_idx, no3an1_idx] != 0:
            assert J[no3an1_idx, hno3_idx] != 0, (
                "Bidirectional coupling violated within oxidized_nitrogen: " "J[HNO3, NO3an1] != 0 but J[NO3an1, HNO3] == 0"
            )
        if J[no3an1_idx, hno3_idx] != 0:
            assert J[hno3_idx, no3an1_idx] != 0, (
                "Bidirectional coupling violated within oxidized_nitrogen: " "J[NO3an1, HNO3] != 0 but J[HNO3, NO3an1] == 0"
            )

        # Verify the coupling is actually present (not trivially true because both are zero)
        assert J[nh3_idx, nh4a_idx] != 0, "NH3 <-> NH4a coupling should exist in the Jacobian"
        assert J[nh4a_idx, nh3_idx] != 0, "NH4a <-> NH3 coupling should exist in the Jacobian"


# ---------------------------------------------------------------------------
# Test 5: Adjoint of adjoint returns original ((J^T)^T == J)
# ---------------------------------------------------------------------------


class TestAdjointAdjointReturnsOriginal:
    """Verify (J^T)^T == J — transposing twice recovers the Jacobian.

    This is a fundamental property of the transpose operation and confirms
    the adjoint matrix is correctly computed.

    Validates: Requirements 6.1, 6.4
    """

    def test_adjoint_adjoint_returns_original(self, jacobian_result):
        """Verify (J^T)^T == J element-by-element.

        If we take the adjoint of the adjoint, we should get back the
        original Jacobian. This confirms no information is lost in the
        transpose operation.
        """
        J = jacobian_result["jacobian_matrix"]
        J_T = jacobian_result["adjoint_matrix"]
        J_T_T = J_T.transpose()

        N = J.shape[0]
        for i in range(N):
            for j in range(N):
                diff = sp.simplify(J[i, j] - J_T_T[i, j])
                assert diff == 0, (
                    f"(J^T)^T[{i},{j}] should equal J[{i},{j}]. "
                    f"J[{i},{j}] = {J[i, j]}, (J^T)^T[{i},{j}] = {J_T_T[i, j]}, "
                    f"difference = {diff}"
                )


# ---------------------------------------------------------------------------
# Test 6: Numerical evaluation is well-conditioned
# ---------------------------------------------------------------------------


class TestEquilibriumJacobianNumericalEvaluation:
    """Verify the Jacobian evaluates to finite values (no NaN/Inf).

    Substituting physically realistic values for all symbols should produce
    a well-conditioned matrix suitable for the Rosenbrock solver.

    Validates: Requirements 6.1, 6.2, 6.4
    """

    def test_equilibrium_jacobian_numerical_evaluation(self, jacobian_result):
        """Substitute numerical values and verify the Jacobian is well-conditioned.

        Uses physically realistic atmospheric conditions:
        - Temperature: 298.15 K
        - RH: 0.5
        - Species concentrations: 1e-9 mol/m3 (ppb-level)
        - tau_eq_inv: 1.0 (fast relaxation)
        """
        J = jacobian_result["jacobian_matrix"]
        species_map = jacobian_result["species_map"]

        # Collect all free symbols from the Jacobian
        all_symbols = set()
        N = J.shape[0]
        for i in range(N):
            for j in range(N):
                all_symbols |= J[i, j].free_symbols

        # Build a substitution dictionary with physically reasonable values
        subs = {}
        for sym in all_symbols:
            name = str(sym)
            if name == "Temp":
                subs[sym] = 298.15
            elif name == "RH":
                subs[sym] = 0.5
            elif name.startswith("C_"):
                # Concentration: 1 ppb equivalent (~1e-9 mol/m3)
                subs[sym] = 1.0e-9
            elif "tau_eq_inv" in name:
                # Fast equilibrium relaxation timescale
                subs[sym] = 1.0
            elif "transition_width" in name or "width" in name:
                subs[sym] = 0.05
            else:
                # Default to a small positive value for any unknown symbols
                subs[sym] = 1.0

        # Evaluate the Jacobian numerically
        J_num = J.subs(subs)

        # Verify all entries are finite (no NaN or Inf)
        for i in range(N):
            for j in range(N):
                val = complex(J_num[i, j])
                assert val.imag == 0, f"J[{species_map[i]}, {species_map[j]}] has imaginary component: {val}"
                real_val = val.real
                assert real_val == real_val, (  # NaN check: NaN != NaN
                    f"J[{species_map[i]}, {species_map[j]}] evaluated to NaN " f"with subs={subs}"
                )
                assert abs(real_val) < float("inf"), f"J[{species_map[i]}, {species_map[j]}] evaluated to Inf " f"with subs={subs}"

    def test_jacobian_has_nonzero_entries_after_evaluation(self, jacobian_result):
        """Verify that the Jacobian is not all-zeros after numerical evaluation.

        A well-conditioned Jacobian with equilibrium should have non-trivial
        values when evaluated at realistic conditions.
        """
        J = jacobian_result["jacobian_matrix"]
        species_map = jacobian_result["species_map"]
        N = J.shape[0]

        # Collect all free symbols
        all_symbols = set()
        for i in range(N):
            for j in range(N):
                all_symbols |= J[i, j].free_symbols

        # Build substitution with ammonia-rich conditions (R > 2)
        # so that the full equilibrium partitioning is active.
        # R = C_N / C_S = (C_NH3 + C_NH4a) / (C_SO2 + C_SO4)
        # We want R > 2, so set NH3/NH4a high relative to SO2/SO4.
        subs = {}
        for sym in all_symbols:
            name = str(sym)
            if name == "Temp":
                subs[sym] = 298.15
            elif name == "RH":
                subs[sym] = 0.5
            elif name == "C_NH3":
                subs[sym] = 5.0e-6  # High NH3 for ammonia-rich regime
            elif name == "C_NH4a":
                subs[sym] = 3.0e-6  # Substantial aerosol NH4
            elif name == "C_HNO3":
                subs[sym] = 2.0e-6
            elif name == "C_NO3an1":
                subs[sym] = 1.0e-6
            elif name == "C_SO2":
                subs[sym] = 1.0e-6  # Lower sulfate -> R > 2
            elif name == "C_SO4":
                subs[sym] = 1.0e-6
            elif name.startswith("C_"):
                subs[sym] = 1.0e-6
            else:
                # Default for any other symbol
                subs[sym] = 1.0

        J_num = J.subs(subs)

        # At least some entries should be non-zero
        nonzero_count = 0
        for i in range(N):
            for j in range(N):
                val = float(J_num[i, j])
                if abs(val) > 1e-30:
                    nonzero_count += 1

        assert nonzero_count > 0, (
            "Jacobian should have non-zero entries after numerical evaluation " "with realistic atmospheric conditions"
        )

        # In the ammonia-rich regime (R>2), the non-trivially partitioned
        # species (NH3, HNO3) should have non-zero diagonal entries.
        # NH3 and HNO3 are the gas-phase species whose equilibrium
        # expression genuinely depends on their own concentration through
        # the total species sum.
        for sp_name in ["NH3", "HNO3"]:
            idx = species_map.index(sp_name)
            val = float(J_num[idx, idx])
            assert abs(val) > 1e-30, (
                f"Diagonal J[{sp_name},{sp_name}] should be non-zero after " f"evaluation in ammonia-rich regime. Got: {val}"
            )

        # The overall Jacobian should have many non-zero entries
        # (equilibrium coupling produces a dense sub-block)
        assert nonzero_count >= 4, (
            f"Expected at least 4 non-zero Jacobian entries with equilibrium " f"coupling. Got: {nonzero_count}"
        )
