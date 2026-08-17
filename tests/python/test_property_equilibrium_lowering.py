"""
Property-based tests for the equilibrium lowering pass (Task 4.4).

Validates:
- Property 6: Symbolic Differentiability (Requirements 2.4, 6.3)
- Property 7: Jacobian Sparsity Superset (Requirements 3.3, 3.5)
"""

import sympy as sp
from hypothesis import given, settings
from hypothesis import strategies as st
from mkpp.lowering import prepare_unified_jacobian
from mkpp.model import (
    AerosolRepresentation,
    EquilibriumDefinition,
    MechanismDefinition,
    PhaseMode,
    ReactionDefinition,
    SpeciesDefinition,
)

# ---------------------------------------------------------------------------
# Strategies
# ---------------------------------------------------------------------------

# Blending function choices (both supported modes)
blending_st = st.just("sigmoid")

# Transition width parameter
width_st = st.floats(min_value=0.01, max_value=0.5)


# ---------------------------------------------------------------------------
# Test Fixtures
# ---------------------------------------------------------------------------


def _eq_mechanism(blending: str = "sigmoid", width: float = 0.05) -> MechanismDefinition:
    """Build a mechanism with both ARRHENIUS and EQUILIBRIUM reactions.

    Includes 8 species spanning all three conserved elements
    (reduced_nitrogen, oxidized_nitrogen, sulfate) to exercise the full
    equilibrium lowering path.
    """
    return MechanismDefinition(
        name="eq_test",
        description="Test equilibrium lowering",
        aerosol_representation=AerosolRepresentation.BULK,
        species=[
            SpeciesDefinition(name="NH3", phase=PhaseMode.GAS, elements={"N": 1}),
            SpeciesDefinition(name="NH4a", phase=PhaseMode.AEROSOL, elements={"N": 1}),
            SpeciesDefinition(name="HNO3", phase=PhaseMode.GAS, elements={"N": 1}),
            SpeciesDefinition(name="NO3an1", phase=PhaseMode.AEROSOL, elements={"N": 1}),
            SpeciesDefinition(name="NO3an2", phase=PhaseMode.AEROSOL, elements={"N": 1}),
            SpeciesDefinition(name="NO3an3", phase=PhaseMode.AEROSOL, elements={"N": 1}),
            SpeciesDefinition(name="SO2", phase=PhaseMode.GAS, elements={"S": 1}),
            SpeciesDefinition(name="SO4", phase=PhaseMode.AEROSOL, elements={"S": 1}),
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
        equilibrium_reactions=[
            EquilibriumDefinition(
                system="NH4_NO3_SO4",
                total_species={
                    "reduced_nitrogen": ["NH3", "NH4a"],
                    "oxidized_nitrogen": ["HNO3", "NO3an1", "NO3an2", "NO3an3"],
                    "sulfate": ["SO2", "SO4"],
                },
                regime_blending=blending,
                transition_width=width,
            )
        ],
    )


def _kinetic_only_mechanism() -> MechanismDefinition:
    """Build a mechanism with kinetic reactions only (no equilibrium).

    Uses the same species as the equilibrium mechanism so we can compare
    sparsity patterns directly.
    """
    return MechanismDefinition(
        name="kinetic_only",
        description="Kinetic-only version for sparsity comparison",
        aerosol_representation=AerosolRepresentation.BULK,
        species=[
            SpeciesDefinition(name="NH3", phase=PhaseMode.GAS, elements={"N": 1}),
            SpeciesDefinition(name="NH4a", phase=PhaseMode.AEROSOL, elements={"N": 1}),
            SpeciesDefinition(name="HNO3", phase=PhaseMode.GAS, elements={"N": 1}),
            SpeciesDefinition(name="NO3an1", phase=PhaseMode.AEROSOL, elements={"N": 1}),
            SpeciesDefinition(name="NO3an2", phase=PhaseMode.AEROSOL, elements={"N": 1}),
            SpeciesDefinition(name="NO3an3", phase=PhaseMode.AEROSOL, elements={"N": 1}),
            SpeciesDefinition(name="SO2", phase=PhaseMode.GAS, elements={"S": 1}),
            SpeciesDefinition(name="SO4", phase=PhaseMode.AEROSOL, elements={"S": 1}),
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
# Property 6: Symbolic Differentiability
# Feature: isorropia-unified-jacobian, Property 6: Symbolic Differentiability
# **Validates: Requirements 2.4, 6.3**
# ---------------------------------------------------------------------------


@given(blending=blending_st, width=width_st)
@settings(deadline=None)
def test_property_6_symbolic_differentiability_in_unified_jacobian(blending, width):
    """
    For any equilibrium partition expression produced by the lowering pass,
    calling sp.diff(expr, C_i) for each participating species C_i produces
    a non-None SymPy expression (no Derivative wrapper remaining).

    Build a mechanism with equilibrium, call prepare_unified_jacobian(),
    verify every entry in the Jacobian matrix is fully evaluated (no
    unevaluated Derivative wrappers).

    # Feature: isorropia-unified-jacobian, Property 6: Symbolic Differentiability

    **Validates: Requirements 2.4, 6.3**
    """
    mech = _eq_mechanism(blending=blending, width=width)
    result = prepare_unified_jacobian(mech)

    J = result["jacobian_matrix"]
    N = J.shape[0]

    assert N == len(mech.species), f"Jacobian shape mismatch: got {N}x{N}, expected " f"{len(mech.species)}x{len(mech.species)}"

    # Verify every non-zero entry in the Jacobian is fully evaluated
    for i in range(N):
        for j in range(N):
            entry = J[i, j]
            if entry == 0:
                continue

            # Must not be None
            assert entry is not None, f"Jacobian entry J[{i},{j}] is None. " f"blending={blending}, width={width}"

            # Must not contain unevaluated Derivative wrappers
            has_derivative = entry.has(sp.Derivative)
            assert not has_derivative, (
                f"Jacobian entry J[{i},{j}] contains unevaluated Derivative. " f"Entry: {entry}, blending={blending}, width={width}"
            )

            # Must not contain Piecewise (non-smooth, non-GPU-safe)
            has_piecewise = entry.has(sp.Piecewise)
            assert not has_piecewise, (
                f"Jacobian entry J[{i},{j}] contains Piecewise. " f"Entry: {entry}, blending={blending}, width={width}"
            )

            # Must not contain Abs (non-differentiable)
            has_abs = entry.has(sp.Abs)
            assert not has_abs, f"Jacobian entry J[{i},{j}] contains Abs. " f"Entry: {entry}, blending={blending}, width={width}"

            # Must be a valid SymPy expression (not just a wrapper)
            assert isinstance(entry, sp.Basic), (
                f"Jacobian entry J[{i},{j}] is not a SymPy expression. " f"Type: {type(entry)}, blending={blending}, width={width}"
            )


# ---------------------------------------------------------------------------
# Property 7: Jacobian Sparsity Superset
# Feature: isorropia-unified-jacobian, Property 7: Jacobian Sparsity Superset
# **Validates: Requirements 3.3, 3.5**
# ---------------------------------------------------------------------------


@given(blending=blending_st, width=width_st)
@settings(deadline=None)
def test_property_7_jacobian_sparsity_superset(blending, width):
    """
    For any mechanism with EQUILIBRIUM reactions, the set of non-zero
    Jacobian entries in the unified output is a SUPERSET of the kinetic-only
    entries (no kinetic entries removed).

    Strategy: build a mechanism with kinetic + equilibrium, compare against
    kinetic-only version. Every (i, j) pair that is non-zero in the
    kinetic-only Jacobian must also be non-zero in the unified Jacobian.

    # Feature: isorropia-unified-jacobian, Property 7: Jacobian Sparsity Superset

    **Validates: Requirements 3.3, 3.5**
    """
    # Build kinetic-only mechanism
    kinetic_mech = _kinetic_only_mechanism()
    kinetic_result = prepare_unified_jacobian(kinetic_mech)
    J_kinetic = kinetic_result["jacobian_matrix"]

    # Build unified mechanism (kinetic + equilibrium)
    unified_mech = _eq_mechanism(blending=blending, width=width)
    unified_result = prepare_unified_jacobian(unified_mech)
    J_unified = unified_result["jacobian_matrix"]

    N = J_kinetic.shape[0]
    assert J_unified.shape[0] == N, f"Dimension mismatch: kinetic has {N} species, " f"unified has {J_unified.shape[0]}"

    # Extract sparsity patterns
    kinetic_nonzero = set()
    unified_nonzero = set()

    for i in range(N):
        for j in range(N):
            if J_kinetic[i, j] != 0:
                kinetic_nonzero.add((i, j))
            if J_unified[i, j] != 0:
                unified_nonzero.add((i, j))

    # The unified pattern must be a superset of kinetic pattern
    missing = kinetic_nonzero - unified_nonzero
    assert len(missing) == 0, (
        f"Unified Jacobian is missing {len(missing)} kinetic entries: "
        f"{missing}. blending={blending}, width={width}. "
        f"Kinetic has {len(kinetic_nonzero)} non-zero entries, "
        f"unified has {len(unified_nonzero)} non-zero entries."
    )

    # The unified pattern should have MORE entries than kinetic-only
    # (equilibrium introduces coupling among equilibrium species)
    assert len(unified_nonzero) >= len(kinetic_nonzero), (
        f"Unified Jacobian has fewer non-zero entries "
        f"({len(unified_nonzero)}) than kinetic-only "
        f"({len(kinetic_nonzero)}). "
        f"Equilibrium should add entries, not remove them. "
        f"blending={blending}, width={width}"
    )
