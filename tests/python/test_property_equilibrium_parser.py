"""
Property-based tests for EQUILIBRIUM parser validation.

Validates:
- Property 1: Equilibrium Declaration Parsing Completeness (Requirements 1.1)
- Property 2: Species Validation Rejects Invalid References (Requirements 1.3)
- Property 3: PHASE_CHANGE / EQUILIBRIUM Conflict Detection (Requirements 1.4)
"""

import pytest
from hypothesis import given, settings
from hypothesis import strategies as st
from mkpp.model import CompilationError
from mkpp.parser import parse_mechanism_micm

# ---------------------------------------------------------------------------
# Strategies
# ---------------------------------------------------------------------------

# Valid species name: alphabetic, 1-8 characters
SPECIES_NAME = st.text(
    alphabet=st.characters(whitelist_categories=("Lu", "Ll"), whitelist_characters="0123456789_"),
    min_size=2,
    max_size=8,
).filter(lambda s: s[0].isalpha())

# Generate a list of unique species names
SPECIES_LIST = st.lists(SPECIES_NAME, min_size=4, max_size=12, unique=True)


@st.composite
def valid_equilibrium_data(draw):
    """
    Generate a valid EQUILIBRIUM YAML-like dict with randomized species.
    Returns (data_dict, expected_species_count, expected_constants_count).
    """
    # Draw species names ensuring we have enough for gas + aerosol assignments
    all_species = draw(st.lists(SPECIES_NAME, min_size=6, max_size=15, unique=True))

    # Partition species into elements: at least 2 elements, each with 1 gas + 1-3 aerosol
    num_elements = draw(st.integers(min_value=2, max_value=min(4, len(all_species) // 2)))

    # Assign species to elements
    remaining = list(all_species)
    total_species_dict = {}
    element_names = [f"element_{i}" for i in range(num_elements)]
    all_participating_species = []

    for elem_name in element_names:
        # Need at least 1 gas + 1 aerosol per element = 2 species minimum
        if len(remaining) < 2:
            break
        gas = remaining.pop(0)
        num_aerosol = draw(st.integers(min_value=1, max_value=min(3, len(remaining))))
        aerosol = [remaining.pop(0) for _ in range(num_aerosol)]
        total_species_dict[elem_name] = {"gas": gas, "aerosol": aerosol}
        all_participating_species.append(gas)
        all_participating_species.extend(aerosol)

    # Generate equilibrium constants
    num_constants = draw(st.integers(min_value=1, max_value=4))
    eq_constants = {}
    for i in range(num_constants):
        const_name = f"Kp_{i}"
        eq_constants[const_name] = {
            "A": draw(st.floats(min_value=1e-30, max_value=1e10, allow_nan=False, allow_infinity=False)),
            "dH": draw(st.floats(min_value=-200000.0, max_value=200000.0, allow_nan=False, allow_infinity=False)),
            "Tref": draw(st.floats(min_value=250.0, max_value=350.0, allow_nan=False, allow_infinity=False)),
        }

    # Build the species list (all species including non-participating ones)
    species_defs = [{"name": sp} for sp in all_species]

    # Build the reaction
    reaction = {
        "type": "EQUILIBRIUM",
        "system": "NH4_NO3_SO4",
        "total_species": total_species_dict,
        "equilibrium_constants": eq_constants,
    }

    data = {
        "species": species_defs,
        "reactions": [reaction],
    }

    return data, len(all_participating_species), num_constants


@st.composite
def equilibrium_data_with_invalid_species(draw):
    """
    Generate a valid EQUILIBRIUM block, then inject one non-existent species name.
    Returns the data dict with the invalid reference.
    """
    # Start with a known-good structure
    base_species = draw(st.lists(SPECIES_NAME, min_size=5, max_size=10, unique=True))
    species_names_set = set(base_species)

    # Generate a species name that is NOT in the list
    invalid_name = draw(SPECIES_NAME.filter(lambda s: s not in species_names_set))

    # Pick at least 2 valid species for gas/aerosol
    gas_sp = base_species[0]
    aerosol_sp = [base_species[1]]

    # Decide where to inject the invalid name: gas or aerosol
    inject_in_gas = draw(st.booleans())

    if inject_in_gas:
        total_species = {
            "element_0": {"gas": invalid_name, "aerosol": aerosol_sp},
            "element_1": {"gas": base_species[2], "aerosol": [base_species[3]]},
        }
    else:
        total_species = {
            "element_0": {"gas": gas_sp, "aerosol": [invalid_name]},
            "element_1": {"gas": base_species[2], "aerosol": [base_species[3]]},
        }

    eq_constants = {
        "Kp_test": {"A": 1.0e-10, "dH": -50000.0, "Tref": 298.15},
    }

    reaction = {
        "type": "EQUILIBRIUM",
        "system": "NH4_NO3_SO4",
        "total_species": total_species,
        "equilibrium_constants": eq_constants,
    }

    data = {
        "species": [{"name": sp} for sp in base_species],
        "reactions": [reaction],
    }

    return data


@st.composite
def mechanism_with_phase_change_equilibrium_conflict(draw):
    """
    Generate a mechanism with both PHASE_CHANGE and EQUILIBRIUM reactions
    where at least one species overlaps.
    """
    # Generate species
    all_species = draw(st.lists(SPECIES_NAME, min_size=6, max_size=12, unique=True))

    # Pick overlapping species: at least one species appears in both PHASE_CHANGE and EQUILIBRIUM
    overlap_sp = all_species[0]
    aerosol_sp = [all_species[2]]

    # Build PHASE_CHANGE reaction referencing the overlap species
    phase_change_reaction = {
        "type": "PHASE_CHANGE",
        "reactants": {overlap_sp: 1.0},
        "products": {all_species[3]: 1.0},
        "A": "1.0e-5",
    }

    # Build EQUILIBRIUM reaction also referencing the overlap species
    total_species = {
        "element_0": {"gas": overlap_sp, "aerosol": aerosol_sp},
        "element_1": {"gas": all_species[4], "aerosol": [all_species[5]]},
    }

    eq_constants = {
        "Kp_test": {"A": 1.0e-10, "dH": -50000.0, "Tref": 298.15},
    }

    equilibrium_reaction = {
        "type": "EQUILIBRIUM",
        "system": "NH4_NO3_SO4",
        "total_species": total_species,
        "equilibrium_constants": eq_constants,
    }

    data = {
        "species": [{"name": sp} for sp in all_species],
        "reactions": [phase_change_reaction, equilibrium_reaction],
    }

    return data


# ---------------------------------------------------------------------------
# Property Tests
# ---------------------------------------------------------------------------


# Feature: isorropia-unified-jacobian, Property 1: Equilibrium Declaration Parsing Completeness
@given(eq_data=valid_equilibrium_data())
@settings(deadline=None)
def test_equilibrium_declaration_parsing_completeness(eq_data):
    """Property 1: For any well-formed EQUILIBRIUM YAML block with N participating species
    and M equilibrium constants, the parser extracts exactly N species entries and M constant
    definitions without data loss.

    **Validates: Requirements 1.1**
    """
    data, expected_species_count, expected_constants_count = eq_data

    mech = parse_mechanism_micm("test_mech", data)

    # Parser should extract exactly one equilibrium reaction
    assert len(mech.equilibrium_reactions) == 1

    eq_def = mech.equilibrium_reactions[0]

    # Count participating species across all elements in total_species
    actual_species_count = 0
    for sp_list in eq_def.total_species.values():
        actual_species_count += len(sp_list)

    assert (
        actual_species_count == expected_species_count
    ), f"Expected {expected_species_count} participating species, got {actual_species_count}"

    # Count equilibrium constants
    actual_constants_count = len(eq_def.equilibrium_constants)
    assert (
        actual_constants_count == expected_constants_count
    ), f"Expected {expected_constants_count} equilibrium constants, got {actual_constants_count}"

    # Verify system name preserved
    assert eq_def.system == "NH4_NO3_SO4"


# Feature: isorropia-unified-jacobian, Property 2: Species Validation Rejects Invalid References
@given(data=equilibrium_data_with_invalid_species())
@settings(deadline=None)
def test_species_validation_rejects_invalid_references(data):
    """Property 2: For any EQUILIBRIUM block that references at least one species name NOT in
    the mechanism species list, the parser raises CompilationError.

    **Validates: Requirements 1.3**
    """
    with pytest.raises(CompilationError) as exc_info:
        parse_mechanism_micm("test_mech", data)

    # Verify it's a parsing/validation-stage error
    assert exc_info.value.stage in ("parsing", "validation")
    assert "unknown species" in exc_info.value.message.lower() or "unknown" in exc_info.value.message.lower()


# Feature: isorropia-unified-jacobian, Property 3: PHASE_CHANGE / EQUILIBRIUM Conflict Detection
@given(data=mechanism_with_phase_change_equilibrium_conflict())
@settings(deadline=None)
def test_phase_change_equilibrium_conflict_detection(data):
    """Property 3: For any mechanism with both PHASE_CHANGE and EQUILIBRIUM reactions where
    species overlap, parser raises CompilationError.

    **Validates: Requirements 1.4**
    """
    with pytest.raises(CompilationError) as exc_info:
        parse_mechanism_micm("test_mech", data)

    # Verify the error mentions the conflict
    assert exc_info.value.stage == "validation"
    assert "PHASE_CHANGE" in exc_info.value.message or "EQUILIBRIUM" in exc_info.value.message
