"""
Property-based test for round-trip equivalence (Property 1).

# Feature: jinja2-codegen-templates, Property 1: Template rendering round-trip equivalence

For any valid MechanismDefinition and solver configuration, the template engine
output must be deterministic and structurally valid:
- build_template_context + render("header.j2", context) produces valid C++ that
  contains all expected functions
- The output is deterministic: rendering the same context twice produces
  byte-identical output
- The output is non-empty and contains expected structural patterns

Since both code paths are now unified (the old imperative path has been replaced),
round-trip equivalence is validated by ensuring that:
1. Hypothesis-generated mechanism configurations render successfully
2. Rendering is deterministic (render twice -> same result)
3. Output contains structurally correct C++ (expected patterns present)

**Validates: Requirements 5.1, 5.2, 5.3, 6.2**
"""

import re
import tempfile

from hypothesis import given, settings
from hypothesis import strategies as st
from mkpp.codegen import generate_headers
from mkpp.model import (
    AerosolRepresentation,
    MechanismDefinition,
    PhaseMode,
    ReactionDefinition,
    SpeciesDefinition,
)
from mkpp.rosenbrock import SOLVER_COEFFICIENTS
from mkpp.template_context import build_template_context
from mkpp.template_engine import TemplateEngine

# ---------------------------------------------------------------------------
# Strategies: Generate valid MechanismDefinition instances
# ---------------------------------------------------------------------------


@st.composite
def mechanism_strategy(draw):
    """Generate a valid MechanismDefinition with varying configurations.

    Covers:
    - Different numbers of species (2-6)
    - With/without photolysis reactions
    - Different solver names (ros2, ros3, ros4, rodas3, rodas4)
    - With/without adjoint mode

    Produces a tuple of (mechanism, solver_name, adjoint_flag).
    """
    # Number of species (keep small for speed - symbolic LU is expensive)
    n_species = draw(st.integers(min_value=2, max_value=6))

    # Generate species with unique names
    species_names = [f"SP{i}" for i in range(n_species)]
    species = [
        SpeciesDefinition(
            name=name,
            phase=PhaseMode.GAS,
            elements={"C": 1} if draw(st.booleans()) else {},
        )
        for name in species_names
    ]

    # Generate kinetic reactions (at least 1, up to n_species - 1)
    n_reactions = draw(st.integers(min_value=1, max_value=max(1, n_species - 1)))
    reactions = []
    for r_idx in range(n_reactions):
        # Pick reactant and product from available species
        reactant_idx = draw(st.integers(min_value=0, max_value=n_species - 1))
        product_idx = draw(st.integers(min_value=0, max_value=n_species - 1).filter(lambda x, ri=reactant_idx: x != ri))
        reactions.append(
            ReactionDefinition(
                reaction_type="ARRHENIUS",
                reactants={species_names[reactant_idx]: 1.0},
                products={species_names[product_idx]: 1.0},
                rate_expression=f"k{r_idx}*{species_names[reactant_idx]}",
                parameters={"A": 1e-3, "B": 0.0, "C": 0.0},
                stiff=True,
            )
        )

    # Optionally add photolysis reactions
    has_photolysis = draw(st.booleans())
    if has_photolysis and n_species >= 2:
        n_photo = draw(st.integers(min_value=1, max_value=min(2, n_species - 1)))
        for p_idx in range(n_photo):
            reactant_idx = p_idx % n_species
            product_idx = (p_idx + 1) % n_species
            reactions.append(
                ReactionDefinition(
                    reaction_type="PHOTOLYSIS",
                    reactants={species_names[reactant_idx]: 1.0},
                    products={species_names[product_idx]: 1.0},
                    rate_expression=f"jval{p_idx}*{species_names[reactant_idx]}",
                    parameters={"A": 1.0e-5, "jval_index": p_idx},
                    stiff=True,
                )
            )

    # Build mechanism
    mech = MechanismDefinition(
        name=f"test_roundtrip_{n_species}sp",
        description="Generated mechanism for round-trip property test",
        aerosol_representation=AerosolRepresentation.BULK,
        species=species,
        phases=[],
        reactions=reactions,
    )

    # Solver selection
    solver_name = draw(st.sampled_from(list(SOLVER_COEFFICIENTS.keys())))

    # Adjoint mode
    adjoint = draw(st.booleans())

    return mech, solver_name, adjoint


# ---------------------------------------------------------------------------
# Property 1: Template rendering round-trip equivalence
# **Validates: Requirements 5.1, 5.2, 5.3, 6.2**
# ---------------------------------------------------------------------------


@given(data=mechanism_strategy())
@settings(max_examples=100, deadline=None)
def test_property_1_roundtrip_equivalence(data):
    """
    For any valid MechanismDefinition and solver configuration:
    1. build_template_context succeeds without error
    2. Rendering header.j2 with the context produces non-empty output
    3. Rendering is deterministic (byte-identical on repeated invocations)
    4. Output contains expected structural C++ patterns

    **Validates: Requirements 5.1, 5.2, 5.3, 6.2**
    """
    mech, solver_name, adjoint = data

    # Step 1: Build template context (must not raise)
    context = build_template_context(mech, solver_name, adjoint=adjoint)

    # Step 2: Render header.j2 (must produce non-empty output)
    engine = TemplateEngine()
    output_1 = engine.render("header.j2", context)

    assert output_1, (
        f"Rendered output is empty for mechanism with {len(mech.species)} species, " f"solver={solver_name}, adjoint={adjoint}"
    )

    # Step 3: Determinism - render again and verify byte-identical output
    output_2 = engine.render("header.j2", context)

    assert output_1 == output_2, (
        f"Non-deterministic rendering detected!\n"
        f"Config: {len(mech.species)} species, solver={solver_name}, adjoint={adjoint}\n"
        f"First render length: {len(output_1)}\n"
        f"Second render length: {len(output_2)}\n"
        f"First difference at position: {_first_diff_pos(output_1, output_2)}"
    )

    # Step 4: Structural correctness - verify expected C++ patterns
    # 4a: Must have #pragma once
    assert "#pragma once" in output_1, "Missing #pragma once in rendered output"

    # 4b: Must have namespace declaration
    assert "namespace" in output_1, "Missing namespace declaration in rendered output"

    # 4c: Must have struct declaration (SolverKernels)
    assert "struct" in output_1, "Missing struct declaration in rendered output"

    # 4d: Must contain core function signatures
    assert "compute_rates" in output_1, "Missing compute_rates function in rendered output"
    assert "compute_jacobian" in output_1, "Missing compute_jacobian function in rendered output"
    assert "integrate" in output_1, "Missing integrate function in rendered output"

    # 4e: When adjoint is enabled, must contain adjoint functions
    if adjoint:
        assert "integrate_adj" in output_1, "Missing integrate_adj function when adjoint=True"
        assert "integrate_tlm" in output_1, "Missing integrate_tlm function when adjoint=True"
        assert "integrate_fwd_checkpoint" in output_1, "Missing integrate_fwd_checkpoint function when adjoint=True"

    # 4f: Must contain W-matrix entries (W_i_j declarations)
    w_pattern = re.compile(r"double\s+W_\d+_\d+\s*=")
    assert w_pattern.search(output_1), "Missing W-matrix declarations (double W_i_j = ...) in rendered output"

    # 4g: Must contain LU factorization entries
    lu_pattern = re.compile(r"double\s+[LU]_\d+_\d+\s*=")
    assert lu_pattern.search(output_1), "Missing LU factorization declarations in rendered output"


@given(data=mechanism_strategy())
@settings(max_examples=100, deadline=None)
def test_property_1_generate_headers_deterministic(data):
    """
    For any valid MechanismDefinition and solver configuration, calling
    generate_headers twice produces byte-identical header files.

    This validates the full pipeline (context construction + rendering + file I/O)
    is deterministic end-to-end.

    **Validates: Requirements 5.1, 5.2, 5.3, 6.2**
    """
    mech, solver_name, adjoint = data

    with tempfile.TemporaryDirectory() as tmp1, tempfile.TemporaryDirectory() as tmp2:
        # Generate headers via the public API twice
        result1 = generate_headers(mech, out_dir=tmp1, solver_name=solver_name, adjoint=adjoint)
        result2 = generate_headers(mech, out_dir=tmp2, solver_name=solver_name, adjoint=adjoint)

        # Read both outputs
        with open(result1["header"]) as f:
            header1 = f.read()
        with open(result2["header"]) as f:
            header2 = f.read()

    assert header1 == header2, (
        f"generate_headers produced non-deterministic output!\n"
        f"Config: {len(mech.species)} species, solver={solver_name}, adjoint={adjoint}\n"
        f"First header length: {len(header1)}\n"
        f"Second header length: {len(header2)}\n"
        f"First difference at position: {_first_diff_pos(header1, header2)}"
    )


# ---------------------------------------------------------------------------
# Helper functions
# ---------------------------------------------------------------------------


def _first_diff_pos(s1: str, s2: str) -> str:
    """Find the position and context of the first difference between two strings."""
    for i, (c1, c2) in enumerate(zip(s1, s2)):
        if c1 != c2:
            context_start = max(0, i - 20)
            context_end = min(len(s1), i + 20)
            return f"position {i}: " f"'{s1[context_start:context_end]}' vs " f"'{s2[context_start:context_end]}'"
    if len(s1) != len(s2):
        return f"strings differ in length: {len(s1)} vs {len(s2)}"
    return "no differences found"
