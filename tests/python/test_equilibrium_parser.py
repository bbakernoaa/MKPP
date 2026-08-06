"""Unit tests for the EQUILIBRIUM YAML parser.

Validates: Requirements 1.1, 1.2, 1.3, 1.4, 1.5
"""

import pytest
from mkpp.model import CompilationError, EquilibriumDefinition
from mkpp.parser import parse_mechanism_micm


def _base_species():
    """Return a minimal species list for EQUILIBRIUM testing."""
    return [
        {"name": "NH3"},
        {"name": "NH4a"},
        {"name": "HNO3"},
        {"name": "NO3an1"},
        {"name": "NO3an2"},
        {"name": "NO3an3"},
        {"name": "SO2"},
        {"name": "SO4"},
        {"name": "O3"},
    ]


def _base_equilibrium_reaction():
    """Return a valid EQUILIBRIUM reaction block."""
    return {
        "type": "EQUILIBRIUM",
        "system": "NH4_NO3_SO4",
        "total_species": {
            "reduced_nitrogen": {"gas": "NH3", "aerosol": ["NH4a"]},
            "oxidized_nitrogen": {
                "gas": "HNO3",
                "aerosol": ["NO3an1", "NO3an2", "NO3an3"],
            },
            "sulfate": {"gas": "SO2", "aerosol": ["SO4"]},
        },
        "equilibrium_constants": {
            "Kp_NH4NO3": {"A": 4.39e-17, "dH": -74735.0, "Tref": 298.15},
            "Kp_NH4HSO4": {"A": 1.086e-2, "dH": -40000.0, "Tref": 298.15},
            "Kp_NH42SO4": {"A": 1.817e-25, "dH": -160000.0, "Tref": 298.15},
        },
    }


def test_parse_equilibrium_basic():
    """Parse a valid EQUILIBRIUM block and verify EquilibriumDefinition fields."""
    data = {
        "species": _base_species(),
        "reactions": [_base_equilibrium_reaction()],
    }

    mech = parse_mechanism_micm("test_eq", data)

    assert len(mech.equilibrium_reactions) == 1
    eq = mech.equilibrium_reactions[0]
    assert isinstance(eq, EquilibriumDefinition)
    assert eq.system == "NH4_NO3_SO4"
    assert "reduced_nitrogen" in eq.total_species
    assert "oxidized_nitrogen" in eq.total_species
    assert "sulfate" in eq.total_species
    # Verify equilibrium constants are preserved
    assert "Kp_NH4NO3" in eq.equilibrium_constants
    assert eq.equilibrium_constants["Kp_NH4NO3"]["A"] == pytest.approx(4.39e-17)
    assert eq.equilibrium_constants["Kp_NH4NO3"]["dH"] == pytest.approx(-74735.0)
    assert eq.equilibrium_constants["Kp_NH4NO3"]["Tref"] == pytest.approx(298.15)
    assert eq.continuous_transition is True


def test_parse_equilibrium_defaults():
    """Verify defaults: regime_blending='sigmoid', transition_width=0.05, activity_model='fixed', continuous_transition=True."""
    data = {
        "species": _base_species(),
        "reactions": [_base_equilibrium_reaction()],
    }

    mech = parse_mechanism_micm("test_defaults", data)
    eq = mech.equilibrium_reactions[0]

    assert eq.regime_blending == "sigmoid"
    assert eq.transition_width == pytest.approx(0.05)
    assert eq.activity_model == "fixed"
    assert eq.continuous_transition is True


def test_parse_equilibrium_species_validation():
    """EQUILIBRIUM referencing non-existent species raises CompilationError."""
    reaction = _base_equilibrium_reaction()
    # Introduce a species name that doesn't exist in the species list
    reaction["total_species"]["reduced_nitrogen"]["aerosol"] = ["NONEXISTENT_SPECIES"]

    data = {
        "species": _base_species(),
        "reactions": [reaction],
    }

    with pytest.raises(CompilationError) as exc_info:
        parse_mechanism_micm("test_invalid_species", data)

    assert "NONEXISTENT_SPECIES" in str(exc_info.value)


def test_parse_equilibrium_phase_change_conflict():
    """PHASE_CHANGE + EQUILIBRIUM with overlapping species raises CompilationError."""
    phase_change_reaction = {
        "type": "PHASE_CHANGE",
        "reactants": {"NH3": {}},
        "products": {"NH4a": {}},
    }
    equilibrium_reaction = _base_equilibrium_reaction()

    data = {
        "species": _base_species(),
        "reactions": [phase_change_reaction, equilibrium_reaction],
    }

    with pytest.raises(CompilationError) as exc_info:
        parse_mechanism_micm("test_conflict", data)

    # Should mention the conflicting species
    error_msg = str(exc_info.value)
    assert "PHASE_CHANGE" in error_msg or "EQUILIBRIUM" in error_msg


def test_parse_equilibrium_constant_validation():
    """Equilibrium constant missing A/dH/Tref raises CompilationError."""
    reaction = _base_equilibrium_reaction()
    # Remove required field 'Tref' from one constant
    del reaction["equilibrium_constants"]["Kp_NH4NO3"]["Tref"]

    data = {
        "species": _base_species(),
        "reactions": [reaction],
    }

    with pytest.raises(CompilationError) as exc_info:
        parse_mechanism_micm("test_missing_const", data)

    assert "Kp_NH4NO3" in str(exc_info.value)


def test_parse_equilibrium_not_in_reactions_list():
    """Verify EQUILIBRIUM blocks don't appear in mech.reactions, only in mech.equilibrium_reactions."""
    data = {
        "species": _base_species(),
        "reactions": [
            _base_equilibrium_reaction(),
            {
                "type": "ARRHENIUS",
                "reactants": {"O3": {}},
                "products": {"SO2": {}},
                "A": 1.0e-10,
            },
        ],
    }

    mech = parse_mechanism_micm("test_separation", data)

    # Only the ARRHENIUS reaction should be in mech.reactions
    assert len(mech.reactions) == 1
    assert mech.reactions[0].reaction_type == "ARRHENIUS"

    # The EQUILIBRIUM block should be in equilibrium_reactions
    assert len(mech.equilibrium_reactions) == 1
    assert mech.equilibrium_reactions[0].system == "NH4_NO3_SO4"


def test_parse_equilibrium_total_species_flattening():
    """Verify nested total_species YAML is flattened to dict[str, list[str]]."""
    data = {
        "species": _base_species(),
        "reactions": [_base_equilibrium_reaction()],
    }

    mech = parse_mechanism_micm("test_flattening", data)
    eq = mech.equilibrium_reactions[0]

    # total_species should be flattened: element -> [gas, aerosol1, aerosol2, ...]
    assert eq.total_species["reduced_nitrogen"] == ["NH3", "NH4a"]
    assert eq.total_species["oxidized_nitrogen"] == [
        "HNO3",
        "NO3an1",
        "NO3an2",
        "NO3an3",
    ]
    assert eq.total_species["sulfate"] == ["SO2", "SO4"]


def test_parse_equilibrium_backward_compat():
    """Mechanism with no EQUILIBRIUM blocks parses normally with empty equilibrium_reactions list."""
    data = {
        "species": [{"name": "O3"}, {"name": "O"}, {"name": "O2"}],
        "reactions": [
            {
                "type": "ARRHENIUS",
                "reactants": {"O3": {}},
                "products": {"O": {}, "O2": {}},
                "A": 1.0e-5,
            }
        ],
    }

    mech = parse_mechanism_micm("test_backward_compat", data)

    assert mech.equilibrium_reactions == []
    assert len(mech.reactions) == 1
    assert mech.reactions[0].reaction_type == "ARRHENIUS"
