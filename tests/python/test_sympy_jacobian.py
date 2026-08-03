import pytest
from mkpp.model import MechanismDefinition, ReactionDefinition, AerosolRepresentation, SpeciesDefinition, PhaseMode
from mkpp.lowering import prepare_unified_jacobian

def test_prepare_unified_jacobian_exact_equations():
    # Construct a mechanism with the 5 exact equations
    mech = MechanismDefinition(
        name="test_mech", description="Test", aerosol_representation=AerosolRepresentation.BULK,
        species=[
            SpeciesDefinition(name="O", phase=PhaseMode.GAS),
            SpeciesDefinition(name="O2", phase=PhaseMode.GAS),
            SpeciesDefinition(name="O3", phase=PhaseMode.GAS),
            SpeciesDefinition(name="M", phase=PhaseMode.GAS),
            SpeciesDefinition(name="SULFATE", phase=PhaseMode.AEROSOL)
        ],
        phases=[],
        reactions=[
            # 1. PHOTOLYSIS: O2 + hv -> 2O
            ReactionDefinition(reaction_type="PHOTOLYSIS", reactants=["O2"], products=["O", "O"], rate_expression="", parameters={"A": "J1"}, continuous_transition=True),

            # 2. ARRHENIUS: O + O2 + M -> O3 + M
            ReactionDefinition(reaction_type="ARRHENIUS", reactants=["O", "O2", "M"], products=["O3", "M"], rate_expression="", parameters={"A": "1.0", "B": "0.0", "C": "200.0"}),

            # 3. TROE: O3 + O -> 2O2
            ReactionDefinition(reaction_type="TROE", reactants=["O3", "O"], products=["O2", "O2"], rate_expression="", parameters={"k0": {"A": "1.0"}, "kinf": {"A": "2.0"}, "Fc": "0.6", "N": "1.0"}),

            # 4. HETEROGENEOUS: O2 -> SULFATE
            ReactionDefinition(reaction_type="HETEROGENEOUS", reactants=["O2"], products=["SULFATE"], rate_expression="", parameters={"gamma": "0.1"}),

            # 5. TUNNELING (SOA Splines): O -> O2
            ReactionDefinition(reaction_type="TUNNELING", reactants=["O"], products=["O2"], rate_expression="", parameters={"Y_spline": "Y_NOx"})
        ]
    )

    jacobian_metadata = prepare_unified_jacobian(mech)

    J = jacobian_metadata["jacobian_matrix"]
    # Verify that the array isn't just full of "Rate_0_J1" stubs but actually
    # constructed complex equations containing SymPy functions like 'exp', 'log', and 'Temp'.
    matrix_str = str(J)

    assert "J_0" in matrix_str
    assert "Temp" in matrix_str
    assert "exp" in matrix_str
    assert "k0" in matrix_str or "kinf" in matrix_str or "Fc" in matrix_str or "log" in matrix_str
    assert "gamma" in matrix_str or "v_gas" in matrix_str or "S_a" in matrix_str
    assert "Y_NOx" in matrix_str
