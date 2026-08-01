import pytest
from mkpp.model import MechanismDefinition, ReactionDefinition, AerosolRepresentation
from mkpp.lowering import partition_reactions, prepare_adjoint_and_tlm

def test_prepare_adjoint_and_tlm_success():
    mech = MechanismDefinition(
        name="test_mech", description="Test",
        aerosol_representation=AerosolRepresentation.BULK,
        species=[], phases=[],
        reactions=[
            ReactionDefinition(reaction_type="CONDENSATION", reactants=[], products=[], rate_expression="", continuous_transition=True)
        ]
    )
    result = prepare_adjoint_and_tlm(mech)
    assert result["adjoint_ready"] is True
    assert result["tlm_ready"] is True

def test_prepare_adjoint_and_tlm_failure():
    mech = MechanismDefinition(
        name="test_mech", description="Test",
        aerosol_representation=AerosolRepresentation.BULK,
        species=[], phases=[],
        reactions=[
            ReactionDefinition(reaction_type="PHASE_CHANGE", reactants=[], products=[], rate_expression="", continuous_transition=False)
        ]
    )
    with pytest.raises(ValueError, match="lacks continuous transition"):
        prepare_adjoint_and_tlm(mech)

def test_workload_partitioning_sorting():
    # T024: Ensure solver blocks are deterministically partitioned using Tarjan SCC algorithm
    mech = MechanismDefinition(
        name="test_mech", description="Test", aerosol_representation=AerosolRepresentation.BULK,
        species=[], phases=[],
        reactions=[
            # Cyclic (Stiff) Reactions: O -> O3 -> O
            ReactionDefinition(reaction_type="ARRHENIUS", reactants=["O"], products=["O3"], rate_expression="B"),
            ReactionDefinition(reaction_type="PHOTOLYSIS", reactants=["O3"], products=["O"], rate_expression="A"),
            # Linear (Explicit) Reaction: VOC -> SOA
            ReactionDefinition(reaction_type="CONDENSATION", reactants=["VOC"], products=["SOA"], rate_expression="C"),
        ]
    )
    blocks = partition_reactions(mech)
    
    # Must contain metadata for SZA sorting and micro-blocks
    assert "metadata" in blocks
    assert blocks["metadata"]["sza_sorted"] is True
    assert blocks["metadata"]["scc_count"] == 1  # 1 strongly connected component (O <-> O3)
    
    # Cyclic reactions should be dynamically assigned to implicit
    assert len(blocks["implicit"]) == 2
    # Linear/Slow reactions should be assigned to explicit
    assert len(blocks["explicit"]) == 1
    assert blocks["explicit"][0].reaction_type == "CONDENSATION"
    
    # Deterministic sorting (ARRHENIUS should sort before PHOTOLYSIS alphabetically)
    assert blocks["implicit"][0].reaction_type == "ARRHENIUS"
    assert blocks["implicit"][1].reaction_type == "PHOTOLYSIS"
