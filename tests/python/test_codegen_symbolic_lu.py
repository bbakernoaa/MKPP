import pytest
import sympy as sp
from mkpp.model import (
    MechanismDefinition, SpeciesDefinition, ReactionDefinition, PhaseMode, AerosolRepresentation, SymbolicLUPlan
)
from mkpp.lowering import prepare_unified_jacobian, compute_symbolic_lu_decomposition
from mkpp.codegen import format_eqn, generate_headers


def build_simple_2sp_mechanism():
    """Simple 2-species irreversible decay: A -> B with rate k*A."""
    sp_a = SpeciesDefinition(name="A", phase=PhaseMode.GAS)
    sp_b = SpeciesDefinition(name="B", phase=PhaseMode.GAS)
    rxn = ReactionDefinition(
        reaction_type="ARRHENIUS",
        reactants={"A": 1.0},
        products={"B": 1.0},
        rate_expression="k*A",
        parameters={"A": 1e-2, "B": 0.0, "C": 0.0},
        stiff=True
    )
    return MechanismDefinition(
        name="test_2sp",
        description="2 species test mechanism",
        aerosol_representation=AerosolRepresentation.BULK,
        species=[sp_a, sp_b],
        phases=[],
        reactions=[rxn]
    )


def build_chapman_toy_mechanism():
    """Toy Chapman mechanism: O, O3, O1D."""
    sp_o = SpeciesDefinition(name="O", phase=PhaseMode.GAS)
    sp_o3 = SpeciesDefinition(name="O3", phase=PhaseMode.GAS)
    sp_o1d = SpeciesDefinition(name="O1D", phase=PhaseMode.GAS)

    r1 = ReactionDefinition(
        reaction_type="PHOTOLYSIS",
        reactants={"O3": 1.0},
        products={"O1D": 1.0, "O": 1.0},
        rate_expression="J1*O3",
        parameters={"A": "J1"},
        stiff=True
    )
    r2 = ReactionDefinition(
        reaction_type="ARRHENIUS",
        reactants={"O": 1.0, "O3": 1.0},
        products={"O": 2.0},
        rate_expression="k2*O*O3",
        parameters={"A": 1e-15, "B": 0.0, "C": 0.0},
        stiff=True
    )
    return MechanismDefinition(
        name="chapman_toy",
        description="Chapman toy mechanism",
        aerosol_representation=AerosolRepresentation.BULK,
        species=[sp_o, sp_o3, sp_o1d],
        phases=[],
        reactions=[r1, r2]
    )


def test_symbolic_lu_plan_structure():
    """Verify SymbolicLUPlan generation for 2x2 mechanism."""
    mech = build_simple_2sp_mechanism()
    lowering_data = prepare_unified_jacobian(mech)
    J = lowering_data["jacobian_matrix"]

    plan = compute_symbolic_lu_decomposition(J, lowering_data["species_map"])
    assert isinstance(plan, SymbolicLUPlan)
    assert plan.num_species == 2
    assert len(plan.l_expressions) > 0
    assert len(plan.u_expressions) > 0
    assert len(plan.forward_sub_steps) == 2
    assert len(plan.backward_sub_steps) == 2


def test_codegen_zero_thread_arrays_and_loops(tmp_path):
    """Verify generated header contains zero thread-local array declarations and zero loops."""
    mech = build_chapman_toy_mechanism()
    lowering_data = prepare_unified_jacobian(mech)
    plan = compute_symbolic_lu_decomposition(lowering_data["jacobian_matrix"], lowering_data["species_map"])

    mech.metadata["sympy_metadata"] = lowering_data
    mech.metadata["symbolic_lu_plan"] = plan

    artifacts = generate_headers(mech, out_dir=str(tmp_path))
    header_path = artifacts["header"]

    with open(header_path, 'r') as f:
        code = f.read()

    # Check zero thread local arrays
    assert "double Jac[" not in code
    assert "double W[" not in code
    assert "double K1[" not in code
    assert "double K2[" not in code
    assert "double Ynew[" not in code
    assert "double F1[" not in code
    assert "double F2[" not in code

    # Check zero for loops in integrate and solver kernels
    assert "for (" not in code
    assert "for(" not in code

    # Check subview templated interface
    assert "template <class StateView>" in code
    assert "double* state" not in code


def test_view_interface_contract_signatures(tmp_path):
    """Verify that all generated solver kernel signatures use templated view abstractions."""
    mech = build_simple_2sp_mechanism()
    lowering_data = prepare_unified_jacobian(mech)
    mech.metadata["sympy_metadata"] = lowering_data

    artifacts = generate_headers(mech, out_dir=str(tmp_path))
    header_path = artifacts["header"]

    with open(header_path, 'r') as f:
        code = f.read()

    assert "template <class StateView, class RateView>" in code
    assert "template <class StateView, class JacView>" in code
    assert "template <class StateView, class DeltaView, class RateView>" in code
    assert "template <class StateView, class MassView>" in code
    assert "template <class StateView>" in code
    assert "double* state" not in code
    assert "double* F_block" not in code


def test_stage_loop_fusion_and_scalar_vars(tmp_path):
    """Verify ROS-2 stage equations and state updates are unrolled into fused scalar variables."""
    mech = build_chapman_toy_mechanism()
    lowering_data = prepare_unified_jacobian(mech)
    mech.metadata["sympy_metadata"] = lowering_data

    artifacts = generate_headers(mech, out_dir=str(tmp_path))
    header_path = artifacts["header"]

    with open(header_path, 'r') as f:
        code = f.read()

    assert "const double S_0 = state(0);" in code
    assert "double F1_0 =" in code
    assert "double K1_0 =" in code
    assert "double Ynew_0 = S_0 + ros_A0 * K1_0;" in code
    assert "double F2_0 =" in code
    assert "double K2_0 =" in code
    assert "state(0) += ros_M0 * K1_0 + ros_M1 * K2_0;" in code


def test_stage_two_backward_solve_preserves_planner_indices(tmp_path):
    """Verify K2 declarations use symbolic LU row indices, not emission order."""
    mech = build_chapman_toy_mechanism()
    lowering_data = prepare_unified_jacobian(mech)
    plan = SymbolicLUPlan(
        num_species=3,
        species_map=["O", "O3", "O1D"],
        lu_expressions_ordered=[
            ("U", 0, 0, "W_0_0"),
            ("U", 1, 1, "W_1_1"),
            ("U", 2, 2, "W_2_2"),
        ],
        forward_sub_steps=[
            (0, "b_0"),
            (1, "b_1"),
            (2, "b_2"),
        ],
        backward_sub_steps=[
            (2, "y_2 / U_2_2"),
            (1, "y_1 / U_1_1"),
            (0, "y_0 / U_0_0"),
        ],
    )
    mech.metadata["sympy_metadata"] = lowering_data
    mech.metadata["symbolic_lu_plan"] = plan

    artifacts = generate_headers(mech, out_dir=str(tmp_path))
    header_path = artifacts["header"]

    with open(header_path, 'r') as f:
        code = f.read()

    assert "double K2_2 = y2_2 / U_2_2;" in code
    assert "double K2_1 = y2_1 / U_1_1;" in code
    assert "double K2_0 = y2_0 / U_0_0;" in code


def test_format_eqn_folds_numeric_falloff_power():
    """Verify pure numeric falloff powers are folded during AOT emission."""
    species = [SpeciesDefinition(name="A", phase=PhaseMode.GAS)]
    eqn = "0.59999999999999998**(1.0/(1.0 + 996.21549899816557/log(10)**2))*C_A"

    code = format_eqn(eqn, species)

    assert "state(0)" in code
    assert "pow(0.59999999999999998" not in code
    assert "M_LN10" not in code


def test_format_eqn_strength_reduces_state_squares():
    """Verify generated concentration squares do not call runtime pow."""
    species = [SpeciesDefinition(name="A", phase=PhaseMode.GAS)]

    code = format_eqn("C_A**2", species)

    assert "pow(" not in code
    assert "state(0) * state(0)" in code

    scalar_code = format_eqn("C_A**2", species, state_var="S", use_parentheses=False)
    assert "pow(" not in scalar_code
    assert "S_0 * S_0" in scalar_code

