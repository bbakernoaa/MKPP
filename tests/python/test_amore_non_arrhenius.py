import pytest
from mkpp.amore import apply_amore_lumping
from mkpp.model import (
    AerosolRepresentation,
    MechanismDefinition,
    PhaseMode,
    ReactionDefinition,
    SpeciesDefinition,
)


def test_amore_non_arrhenius_troe_lumping():
    # Mechanism with 2 explicit species mapping to 1 surrogate SURR
    mech = MechanismDefinition(
        name="test_troe_lump",
        description="Test TROE lumping",
        aerosol_representation=AerosolRepresentation.BULK,
        phases=[],
        species=[
            SpeciesDefinition(name="EX1", phase=PhaseMode.GAS, elements={"C": 3}),
            SpeciesDefinition(name="EX2", phase=PhaseMode.GAS, elements={"C": 3}),
            SpeciesDefinition(name="OH", phase=PhaseMode.GAS),
            SpeciesDefinition(name="PROD1", phase=PhaseMode.GAS),
            SpeciesDefinition(name="PROD2", phase=PhaseMode.GAS),
        ],
        reactions=[
            ReactionDefinition(
                reaction_type="TROE",
                reactants={"EX1": 1, "OH": 1},
                products={"PROD1": 1.0},
                rate_expression="troe1",
                parameters={
                    "k0": {"A": 1.0e-28, "B": 0.0, "C": 0.0},
                    "kinf": {"A": 1.0e-11, "B": 0.0, "C": 0.0},
                    "Fc": 0.6,
                },
            ),
            ReactionDefinition(
                reaction_type="TROE",
                reactants={"EX2": 1, "OH": 1},
                products={"PROD2": 1.0},
                rate_expression="troe2",
                parameters={
                    "k0": {"A": 3.0e-28, "B": 0.0, "C": 0.0},
                    "kinf": {"A": 3.0e-11, "B": 0.0, "C": 0.0},
                    "Fc": 0.6,
                },
            ),
        ],
    )

    rules = {"SURR": ["EX1", "EX2"]}
    lumped_mech = apply_amore_lumping(mech, rules)

    assert len(lumped_mech.reactions) == 1
    r = lumped_mech.reactions[0]
    assert r.reaction_type == "TROE"
    assert "SURR" in r.reactants
    assert "OH" in r.reactants
    # Check parameters were merged cleanly without dictionary string corruptions
    assert isinstance(r.parameters["k0"], dict)
    assert pytest.approx(r.parameters["k0"]["A"]) == 2.0e-28
    assert pytest.approx(r.parameters["kinf"]["A"]) == 2.0e-11
    # Check products were averaged
    assert r.products.get("PROD1") == 0.5
    assert r.products.get("PROD2") == 0.5
