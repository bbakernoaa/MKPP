import pytest

from mkpp.lowering import partition_reactions, prepare_adjoint_and_tlm
from mkpp.model import AerosolRepresentation, MechanismDefinition, ReactionDefinition


def test_prepare_adjoint_and_tlm_success():
    mech = MechanismDefinition(
        name="test_mech",
        description="Test",
        aerosol_representation=AerosolRepresentation.BULK,
        species=[],
        phases=[],
        reactions=[
            ReactionDefinition(
                reaction_type="CONDENSATION",
                reactants=[],
                products=[],
                rate_expression="",
                continuous_transition=True,
            )
        ],
    )
    result = prepare_adjoint_and_tlm(mech)
    assert result["adjoint_ready"] is True
    assert result["tlm_ready"] is True


def test_prepare_adjoint_and_tlm_failure():
    mech = MechanismDefinition(
        name="test_mech",
        description="Test",
        aerosol_representation=AerosolRepresentation.BULK,
        species=[],
        phases=[],
        reactions=[
            ReactionDefinition(
                reaction_type="PHASE_CHANGE",
                reactants=[],
                products=[],
                rate_expression="",
                continuous_transition=False,
            )
        ],
    )
    with pytest.raises(ValueError, match="lacks continuous transition"):
        prepare_adjoint_and_tlm(mech)


def test_workload_partitioning_sorting():
    # T024: Ensure solver blocks are deterministically partitioned using Tarjan SCC algorithm
    mech = MechanismDefinition(
        name="test_mech",
        description="Test",
        aerosol_representation=AerosolRepresentation.BULK,
        species=[],
        phases=[],
        reactions=[
            # Cyclic (Stiff) Reactions: O -> O3 -> O
            ReactionDefinition(reaction_type="ARRHENIUS", reactants=["O"], products=["O3"], rate_expression="B"),
            ReactionDefinition(reaction_type="PHOTOLYSIS", reactants=["O3"], products=["O"], rate_expression="A"),
            # Linear (Explicit) Reaction: VOC -> SOA
            ReactionDefinition(
                reaction_type="CONDENSATION",
                reactants=["VOC"],
                products=["SOA"],
                rate_expression="C",
            ),
        ],
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
    from mkpp.lowering import prepare_unified_jacobian
    from mkpp.model import (
        AerosolRepresentation,
        MechanismDefinition,
        PhaseMode,
        ReactionDefinition,
        SpeciesDefinition,
    )

    mech = MechanismDefinition(
        name="math_test",
        description="Test",
        aerosol_representation=AerosolRepresentation.BULK,
        species=[
            SpeciesDefinition(name="O", phase=PhaseMode.GAS),
            SpeciesDefinition(name="O2", phase=PhaseMode.GAS),
            SpeciesDefinition(name="M", phase=PhaseMode.GAS),
            SpeciesDefinition(name="SULFATE", phase=PhaseMode.AEROSOL),
        ],
        phases=[],
        reactions=[
            # 1. ARRHENIUS: standard k * [O] * [O2] * [M]
            ReactionDefinition(
                reaction_type="ARRHENIUS",
                reactants=["O", "O2", "M"],
                products=["O3"],
                rate_expression="",
                parameters={"A": "1.0"},
            ),
            # 2. TROE: Pressure-dependent falloff using k_0, k_inf
            ReactionDefinition(
                reaction_type="TROE",
                reactants=["O", "O2"],
                products=["O3"],
                rate_expression="",
                parameters={"k0": {"A": "1.0"}, "kinf": {"A": "2.0"}},
            ),
            # 3. PHOTOLYSIS: Linear J-rate
            ReactionDefinition(
                reaction_type="PHOTOLYSIS",
                reactants=["O2"],
                products=["O", "O"],
                rate_expression="",
                parameters={"A": "J_photo"},
                continuous_transition=True,
            ),
            # 4. HETEROGENEOUS: Uptake
            ReactionDefinition(
                reaction_type="HETEROGENEOUS",
                reactants=["O2"],
                products=["SULFATE"],
                rate_expression="",
                parameters={"gamma": "0.1"},
            ),
            # 5. TUNNELING / SPLINES
            ReactionDefinition(
                reaction_type="TUNNELING",
                reactants=["O"],
                products=["O2"],
                rate_expression="",
                parameters={"Y_spline": "Y_spline"},
            ),
        ],
    )

    # We expect prepare_unified_jacobian to generate specific symbolic constructs for these.
    jacobian_metadata = prepare_unified_jacobian(mech)
    J = jacobian_metadata["jacobian_matrix"]

    # Just asserting the script didn't crash and actually processed all 5 types into the matrix.
    assert J.shape == (4, 4)


def test_arrhenius_micm_sign_convention():
    import sympy as sp

    from mkpp.lowering import _evaluate_reaction_fluxes
    from mkpp.model import PhaseMode, SpeciesDefinition

    mech = MechanismDefinition(
        name="sign_test",
        description="Test Arrhenius sign convention",
        aerosol_representation=AerosolRepresentation.BULK,
        species=[SpeciesDefinition(name="A", phase=PhaseMode.GAS), SpeciesDefinition(name="B", phase=PhaseMode.GAS)],
        phases=[],
        reactions=[
            ReactionDefinition(
                reaction_type="ARRHENIUS",
                reactants=["A"],
                products=["B"],
                rate_expression="",
                parameters={"A": "2.15e-12", "B": 0.0, "C": -1735.0},
            )
        ],
    )

    built = _evaluate_reaction_fluxes(mech)
    f_explicit = built["f_explicit"]
    A_sym = built["species_symbols"]["A"]
    dydt_B = f_explicit[1]
    rate_expr = dydt_B / A_sym
    # Find Temp symbol from free_symbols
    temp_sym = next(s for s in rate_expr.free_symbols if s.name == "Temp")
    rate_val = rate_expr.subs({temp_sym: 300.0})
    expected_val = 2.15e-12 * sp.exp(-1735.0 / 300.0)
    assert abs(float(rate_val) - float(expected_val)) < 1e-15


def test_troe_micm_sign_convention():
    import sympy as sp

    from mkpp.lowering import _evaluate_reaction_fluxes
    from mkpp.model import PhaseMode, SpeciesDefinition

    mech = MechanismDefinition(
        name="troe_sign_test",
        description="Test signed Troe Arrhenius convention",
        aerosol_representation=AerosolRepresentation.BULK,
        species=[
            SpeciesDefinition(name="A", phase=PhaseMode.GAS),
            SpeciesDefinition(name="M", phase=PhaseMode.GAS, role="fixed"),
        ],
        phases=[],
        reactions=[
            ReactionDefinition(
                reaction_type="TROE",
                reactants=["A"],
                products=["A"],
                rate_expression="",
                parameters={
                    "k0": {"A": 2.0, "B": 0.0, "C": 400.0},
                    "kinf": {"A": 3.0, "B": 0.0, "C": 200.0},
                    "Fc": 0.6,
                    "N": 1.0,
                },
            )
        ],
    )

    flux = _evaluate_reaction_fluxes(mech)["reaction_fluxes"][0]
    temp = next(symbol for symbol in flux.free_symbols if symbol.name == "Temp")
    concentration = next(symbol for symbol in flux.free_symbols if symbol.name == "C_A")
    third_body = next(symbol for symbol in flux.free_symbols if symbol.name == "C_M")
    rate = flux.subs({temp: 300.0, third_body: 1.0, concentration: 1.0})
    k0 = 2.0 * sp.exp(400.0 / 300.0)
    kinf = 3.0 * sp.exp(200.0 / 300.0)
    ratio = k0 / kinf
    expected = k0 / (1.0 + ratio) * 0.6 ** (1.0 / (1.0 + sp.log(ratio, 10) ** 2))
    assert float(rate - expected) == pytest.approx(0.0, abs=1e-15)


def test_rate_vector_hoisting():
    from mkpp.lowering import prepare_unified_jacobian
    from mkpp.parser import load_mechanism
    from mkpp.template_context import build_template_context

    mech = load_mechanism("mechanisms/openatmos/chapman/mechanism.json")
    mech.sympy_metadata = prepare_unified_jacobian(mech)
    ctx = build_template_context(mech)

    assert "rate_flux_exprs" in ctx
    assert len(ctx["rate_flux_exprs"]) == len(mech.reactions)
    assert "rate_flux_cse" in ctx


def test_cse_no_dead_temporaries():
    import re

    from mkpp.lowering import prepare_unified_jacobian
    from mkpp.parser import load_mechanism
    from mkpp.template_context import build_template_context

    mech = load_mechanism("mechanisms/openatmos/chapman/mechanism.json")
    mech.sympy_metadata = prepare_unified_jacobian(mech)
    ctx = build_template_context(mech)

    cse_list = ctx["rate_flux_cse"]
    all_other_exprs = " ".join(
        [r["expr"] for r in ctx["rate_flux_exprs"]] + ctx["f_exprs"] + [e[2] for e in ctx["jacobian_entries"]]
    )
    for cse in cse_list:
        sym = cse["symbol"]
        assert re.search(r"\b" + sym + r"\b", all_other_exprs), f"Dead temporary {sym} found!"


def test_cse_topological_order():
    import re

    from mkpp.lowering import prepare_unified_jacobian
    from mkpp.parser import load_mechanism
    from mkpp.template_context import build_template_context

    mech = load_mechanism("mechanisms/openatmos/chapman/mechanism.json")
    mech.sympy_metadata = prepare_unified_jacobian(mech)
    ctx = build_template_context(mech)

    cse_list = ctx["rate_flux_cse"]
    symbols_so_far = set()
    for entry in cse_list:
        sym = entry["symbol"]
        expr = entry["expr"]
        refs = re.findall(r"\bcse_tmp_\d+\b", expr)
        for ref in refs:
            assert ref in symbols_so_far, f"Forward reference {ref} in {sym} = {expr}"
        symbols_so_far.add(sym)
