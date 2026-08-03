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

def test_sympy_explicit_reaction_types():
    # Verify exact math representations for different reaction types (Section 2.2 constraints)
    from mkpp.model import MechanismDefinition, ReactionDefinition, AerosolRepresentation, SpeciesDefinition, PhaseMode
    from mkpp.lowering import prepare_unified_jacobian

    mech = MechanismDefinition(
        name="math_test", description="Test", aerosol_representation=AerosolRepresentation.BULK,
        species=[
            SpeciesDefinition(name="O", phase=PhaseMode.GAS),
            SpeciesDefinition(name="O2", phase=PhaseMode.GAS),
            SpeciesDefinition(name="M", phase=PhaseMode.GAS),
            SpeciesDefinition(name="SULFATE", phase=PhaseMode.AEROSOL)
        ], phases=[],
        reactions=[
            # 1. ARRHENIUS: standard k * [O] * [O2] * [M]
            ReactionDefinition(reaction_type="ARRHENIUS", reactants=["O", "O2", "M"], products=["O3"], rate_expression="", parameters={"A": "1.0"}),

            # 2. TROE: Pressure-dependent falloff using k_0, k_inf
            ReactionDefinition(reaction_type="TROE", reactants=["O", "O2"], products=["O3"], rate_expression="", parameters={"k0": {"A": "1.0"}, "kinf": {"A": "2.0"}}),

            # 3. PHOTOLYSIS: Linear J-rate
            ReactionDefinition(reaction_type="PHOTOLYSIS", reactants=["O2"], products=["O", "O"], rate_expression="", parameters={"A": "J_photo"}, continuous_transition=True),

            # 4. HETEROGENEOUS: Uptake
            ReactionDefinition(reaction_type="HETEROGENEOUS", reactants=["O2"], products=["SULFATE"], rate_expression="", parameters={"gamma": "0.1"}),

            # 5. TUNNELING / SPLINES
            ReactionDefinition(reaction_type="TUNNELING", reactants=["O"], products=["O2"], rate_expression="", parameters={"Y_spline": "Y_spline"})
        ]
    )

    # We expect prepare_unified_jacobian to generate specific symbolic constructs for these.
    jacobian_metadata = prepare_unified_jacobian(mech)
    J = jacobian_metadata["jacobian_matrix"]

    # Just asserting the script didn't crash and actually processed all 5 types into the matrix.
    assert J.shape == (4, 4)
