"""
Property-based test for LU plan independence from solver choice.

**Validates: Requirements 7.2, 7.3**

Property 10: LU plan independence from solver choice
For any two solvers applied to the same mechanism, the symbolic LU factorization
expressions (L and U entries) in the generated code are identical.
"""

import tempfile

import pytest
from mkpp.codegen import SOLVER_COEFFICIENTS, generate_headers
from mkpp.lowering import compute_symbolic_lu_decomposition, prepare_unified_jacobian
from mkpp.model import (
    AerosolRepresentation,
    MechanismDefinition,
    PhaseMode,
    ReactionDefinition,
    SpeciesDefinition,
)

# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------

ALL_SOLVERS = list(SOLVER_COEFFICIENTS.keys())


def _build_chapman_mechanism():
    """Build a 3-species Chapman-like mechanism with non-trivial Jacobian sparsity."""
    sp_o = SpeciesDefinition(name="O", phase=PhaseMode.GAS)
    sp_o3 = SpeciesDefinition(name="O3", phase=PhaseMode.GAS)
    sp_o1d = SpeciesDefinition(name="O1D", phase=PhaseMode.GAS)

    r1 = ReactionDefinition(
        reaction_type="PHOTOLYSIS",
        reactants={"O3": 1.0},
        products={"O1D": 1.0, "O": 1.0},
        rate_expression="J1*O3",
        parameters={"A": "J1"},
        stiff=True,
    )
    r2 = ReactionDefinition(
        reaction_type="ARRHENIUS",
        reactants={"O": 1.0, "O3": 1.0},
        products={"O": 2.0},
        rate_expression="k2*O*O3",
        parameters={"A": 1e-15, "B": 0.0, "C": 0.0},
        stiff=True,
    )
    return MechanismDefinition(
        name="lu_plan_test",
        description="Chapman toy for LU plan independence testing",
        aerosol_representation=AerosolRepresentation.BULK,
        species=[sp_o, sp_o3, sp_o1d],
        phases=[],
        reactions=[r1, r2],
    )


def _build_chain_mechanism():
    """Build a 4-species chain mechanism A->B->C->D for broader coverage."""
    species = [
        SpeciesDefinition(name="A", phase=PhaseMode.GAS),
        SpeciesDefinition(name="B", phase=PhaseMode.GAS),
        SpeciesDefinition(name="C", phase=PhaseMode.GAS),
        SpeciesDefinition(name="D", phase=PhaseMode.GAS),
    ]

    reactions = [
        ReactionDefinition(
            reaction_type="ARRHENIUS",
            reactants={"A": 1.0},
            products={"B": 1.0},
            rate_expression="k1*A",
            parameters={"A": 1e-2, "B": 0.0, "C": 0.0},
            stiff=True,
        ),
        ReactionDefinition(
            reaction_type="ARRHENIUS",
            reactants={"B": 1.0},
            products={"C": 1.0},
            rate_expression="k2*B",
            parameters={"A": 1e-3, "B": 0.0, "C": 0.0},
            stiff=True,
        ),
        ReactionDefinition(
            reaction_type="ARRHENIUS",
            reactants={"C": 1.0},
            products={"D": 1.0},
            rate_expression="k3*C",
            parameters={"A": 5e-4, "B": 0.0, "C": 0.0},
            stiff=True,
        ),
    ]

    return MechanismDefinition(
        name="chain_lu_test",
        description="Chain mechanism for LU plan independence testing",
        aerosol_representation=AerosolRepresentation.BULK,
        species=species,
        phases=[],
        reactions=reactions,
    )


def _extract_lu_section(code: str) -> str:
    """
    Extract the Symbolic Doolittle Sparse LU Factorization section from generated code.

    Returns only the lines declaring L_i_j and U_i_j expressions, which should be
    identical across all solvers for the same mechanism.
    """
    lines = code.split("\n")
    lu_lines = []
    in_lu_section = False

    for line in lines:
        if "// Symbolic Doolittle Sparse LU Factorization" in line:
            # Start of a new LU section (there may be multiple: integrate + integrate_with_reduction)
            # We only need the first one since both functions use the same LU plan
            if not in_lu_section and not lu_lines:
                in_lu_section = True
            continue

        if in_lu_section:
            stripped = line.strip()
            # LU section contains lines like "double U_0_0 = W_0_0;"
            # and "double L_1_0 = (W_1_0) / U_0_0;"
            # Also may contain block comments like "// Block 0: species [...]"
            if stripped.startswith("double U_") or stripped.startswith("double L_"):
                lu_lines.append(stripped)
            elif stripped.startswith("// Block"):
                lu_lines.append(stripped)
            elif stripped == "":
                # Skip blank lines within section
                continue
            else:
                # End of LU section (next section begins)
                break

    return "\n".join(lu_lines)


def _generate_for_all_solvers(mech: MechanismDefinition) -> dict:
    """Generate headers for all 5 solvers and return a dict {solver_name: code_string}."""
    lowering_data = prepare_unified_jacobian(mech)
    plan = compute_symbolic_lu_decomposition(
        lowering_data["jacobian_matrix"], lowering_data["species_map"]
    )
    mech.metadata["sympy_metadata"] = lowering_data
    mech.metadata["symbolic_lu_plan"] = plan

    results = {}
    for solver_name in ALL_SOLVERS:
        with tempfile.TemporaryDirectory() as tmp_dir:
            artifacts = generate_headers(mech, out_dir=tmp_dir, solver_name=solver_name)
            with open(artifacts["header"]) as f:
                results[solver_name] = f.read()

    return results


# ---------------------------------------------------------------------------
# Tests
# ---------------------------------------------------------------------------


class TestLUPlanIndependenceFromSolverChoice:
    """
    Property 10: LU plan independence from solver choice.

    For any two solvers applied to the same mechanism, the symbolic LU factorization
    expressions (L and U entries) in the generated code are identical.

    **Validates: Requirements 7.2, 7.3**
    """

    def test_lu_section_identical_across_solvers_chapman(self):
        """
        Verify LU factorization expressions are identical for all 5 solvers
        when applied to a Chapman-like mechanism.
        """
        mech = _build_chapman_mechanism()
        solver_codes = _generate_for_all_solvers(mech)

        # Extract LU section from each solver's generated code
        lu_sections = {}
        for solver_name, code in solver_codes.items():
            lu_section = _extract_lu_section(code)
            assert (
                lu_section
            ), f"[{solver_name}] No LU factorization section found in generated code"
            lu_sections[solver_name] = lu_section

        # Compare all solvers against the first (ros2)
        reference_solver = ALL_SOLVERS[0]
        reference_lu = lu_sections[reference_solver]

        for solver_name in ALL_SOLVERS[1:]:
            assert lu_sections[solver_name] == reference_lu, (
                f"LU factorization section differs between '{reference_solver}' and "
                f"'{solver_name}'.\n"
                f"--- {reference_solver} ---\n{reference_lu}\n"
                f"--- {solver_name} ---\n{lu_sections[solver_name]}"
            )

    def test_lu_section_identical_across_solvers_chain(self):
        """
        Verify LU factorization expressions are identical for all 5 solvers
        when applied to a 4-species chain mechanism.
        """
        mech = _build_chain_mechanism()
        solver_codes = _generate_for_all_solvers(mech)

        # Extract LU section from each solver's generated code
        lu_sections = {}
        for solver_name, code in solver_codes.items():
            lu_section = _extract_lu_section(code)
            assert (
                lu_section
            ), f"[{solver_name}] No LU factorization section found in generated code"
            lu_sections[solver_name] = lu_section

        # Compare all solvers against the first
        reference_solver = ALL_SOLVERS[0]
        reference_lu = lu_sections[reference_solver]

        for solver_name in ALL_SOLVERS[1:]:
            assert lu_sections[solver_name] == reference_lu, (
                f"LU factorization section differs between '{reference_solver}' and "
                f"'{solver_name}' for chain mechanism.\n"
                f"--- {reference_solver} ---\n{reference_lu}\n"
                f"--- {solver_name} ---\n{lu_sections[solver_name]}"
            )

    def test_lu_section_contains_expected_expressions(self):
        """
        Verify the extracted LU section contains L and/or U expressions,
        confirming extraction logic is working correctly.
        """
        mech = _build_chapman_mechanism()
        solver_codes = _generate_for_all_solvers(mech)

        for solver_name, code in solver_codes.items():
            lu_section = _extract_lu_section(code)

            # Must contain at least U expressions (diagonal is always present)
            u_lines = [l for l in lu_section.split("\n") if l.startswith("double U_")]
            assert len(u_lines) > 0, f"[{solver_name}] No U expressions found in LU section"

    @pytest.mark.parametrize(
        "solver_a,solver_b",
        [
            ("ros2", "rodas4"),  # Minimum vs maximum stages
            ("ros3", "rodas3"),  # Same stage count, different method family
            ("ros4", "rodas4"),  # Both 4th-order but different formulations
        ],
    )
    def test_lu_pairwise_independence(self, solver_a: str, solver_b: str):
        """
        Verify LU sections are identical for specific solver pairs that span
        the range of stage counts and method families.
        """
        mech = _build_chapman_mechanism()
        lowering_data = prepare_unified_jacobian(mech)
        plan = compute_symbolic_lu_decomposition(
            lowering_data["jacobian_matrix"], lowering_data["species_map"]
        )
        mech.metadata["sympy_metadata"] = lowering_data
        mech.metadata["symbolic_lu_plan"] = plan

        codes = {}
        for solver_name in (solver_a, solver_b):
            with tempfile.TemporaryDirectory() as tmp_dir:
                artifacts = generate_headers(mech, out_dir=tmp_dir, solver_name=solver_name)
                with open(artifacts["header"]) as f:
                    codes[solver_name] = f.read()

        lu_a = _extract_lu_section(codes[solver_a])
        lu_b = _extract_lu_section(codes[solver_b])

        assert lu_a, f"No LU section found for {solver_a}"
        assert lu_b, f"No LU section found for {solver_b}"
        assert lu_a == lu_b, (
            f"LU plan differs between '{solver_a}' (stages="
            f"{SOLVER_COEFFICIENTS[solver_a].stages}) and '{solver_b}' (stages="
            f"{SOLVER_COEFFICIENTS[solver_b].stages}).\n"
            f"--- {solver_a} ---\n{lu_a}\n"
            f"--- {solver_b} ---\n{lu_b}"
        )
