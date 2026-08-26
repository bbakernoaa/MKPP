"""Shared pytest fixtures for equilibrium test speed optimization.

Session-scoped fixtures compute expensive symbolic results ONCE and share
them across all test files that need them.
"""

import os
import tempfile

# Test workers must use a non-interactive backend.  Without this, parallel
# pytest workers on macOS may initialize AppKit and abort in headless runs.
os.environ.setdefault("MPLBACKEND", "Agg")

import pytest
from hypothesis import settings

from mkpp.model import (
    AerosolRepresentation,
    EquilibriumDefinition,
    MechanismDefinition,
    PhaseMode,
    ReactionDefinition,
    SpeciesDefinition,
)

# Configure Hypothesis profiles for test performance
# - default/dev: 25 examples for fast local testing and standard PR CI runs
# - thorough: 100 examples for deep fuzzing/nightly builds
DEFAULT_MAX_EXAMPLES = int(os.getenv("HYPOTHESIS_MAX_EXAMPLES", "25"))
settings.register_profile("default", max_examples=DEFAULT_MAX_EXAMPLES, deadline=None)
settings.register_profile("thorough", max_examples=100, deadline=None)
settings.load_profile(os.getenv("HYPOTHESIS_PROFILE", "default"))


@pytest.fixture(scope="session")
def eq_mechanism_8species():
    """Session-scoped: 8-species mechanism with equilibrium."""
    return MechanismDefinition(
        name="eq_session_test",
        description="Shared equilibrium test mechanism",
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
                reactants={"SO2": 1.0},
                products={"SO4": 1.0},
                rate_expression="",
                parameters={"A": "3.3e-12", "B": "0", "C": "0"},
            ),
        ],
        equilibrium_reactions=[
            EquilibriumDefinition(
                system="NH4_NO3_SO4",
                total_species={
                    "reduced_nitrogen": ["NH3", "NH4a"],
                    "oxidized_nitrogen": ["HNO3", "NO3an1", "NO3an2", "NO3an3"],
                    "sulfate": ["SO2", "SO4"],
                },
            )
        ],
    )


@pytest.fixture(scope="session")
def eq_jacobian_result(eq_mechanism_8species):
    """Session-scoped: unified Jacobian result (expensive SymPy computation)."""
    from mkpp.lowering import prepare_unified_jacobian

    return prepare_unified_jacobian(eq_mechanism_8species)


@pytest.fixture(scope="session")
def eq_generated_header(eq_mechanism_8species):
    """Session-scoped: generated C++ header text for equilibrium mechanism."""
    from mkpp.codegen import generate_headers

    with tempfile.TemporaryDirectory() as tmpdir:
        result = generate_headers(eq_mechanism_8species, out_dir=tmpdir)
        with open(result["header"]) as f:
            return f.read()


@pytest.fixture(scope="session")
def eq_generated_header_adjoint(eq_mechanism_8species):
    """Session-scoped: generated C++ header with adjoint=True."""
    from mkpp.codegen import generate_headers

    with tempfile.TemporaryDirectory() as tmpdir:
        result = generate_headers(eq_mechanism_8species, out_dir=tmpdir, adjoint=True)
        with open(result["header"]) as f:
            return f.read()
