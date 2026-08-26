"""
GPU safety verification for generated integrator code across all solvers.

**Validates: Requirements 5.1, 5.2, 5.3, 5.4**

Property 8: GPU safety invariants
For any solver and any mechanism, the generated integrate() code contains no dynamic
allocations (new, malloc, std::vector), no runtime-indexed stage arrays, and includes
the KOKKOS_INLINE_FUNCTION annotation.

Validates that generated C++ code contains:
- No dynamic memory allocations (new, malloc, std::vector)
- No runtime-indexed stage arrays (all stage variables are named scalars)
- No runtime loops over stages (all stage logic is fully unrolled)
- Stage variables follow naming convention: K{n}_{i}, Y{n}_{i}, F{n}_{i}
- KOKKOS_INLINE_FUNCTION annotation before integrate() and integrate_with_reduction()
"""

import re
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


def _build_test_mechanism():
    """Build a minimal 3-species mechanism with a non-trivial Jacobian for testing."""
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
        name="gpu_safety_test",
        description="Mechanism for GPU safety invariant testing",
        aerosol_representation=AerosolRepresentation.BULK,
        species=[sp_o, sp_o3, sp_o1d],
        phases=[],
        reactions=[r1, r2],
    )


def _generate_code_for_solver(solver_name: str) -> str:
    """Generate the C++ header for the given solver and return the code as a string."""
    mech = _build_test_mechanism()
    lowering_data = prepare_unified_jacobian(mech)
    plan = compute_symbolic_lu_decomposition(lowering_data["jacobian_matrix"], lowering_data["species_map"])
    mech.metadata["sympy_metadata"] = lowering_data
    mech.metadata["symbolic_lu_plan"] = plan

    with tempfile.TemporaryDirectory() as tmp_dir:
        artifacts = generate_headers(mech, out_dir=tmp_dir, solver_name=solver_name)
        with open(artifacts["header"]) as f:
            return f.read()


@pytest.mark.parametrize("solver_name", list(SOLVER_COEFFICIENTS.keys()))
class TestGPUSafetyInvariants:
    """GPU safety invariants verified across all five Rosenbrock solvers."""

    def test_no_dynamic_allocation(self, solver_name: str):
        """
        Verify generated code contains no dynamic memory allocations.

        The generated integrator must not use `new `, `malloc(`, or `std::vector`
        since these are incompatible with GPU kernel execution.

        **Validates: Requirements 5.2**
        """
        code = _generate_code_for_solver(solver_name)

        assert "new " not in code, f"[{solver_name}] Generated code contains 'new ' (dynamic allocation)"
        assert "malloc(" not in code, f"[{solver_name}] Generated code contains 'malloc(' (dynamic allocation)"
        assert "std::vector" not in code, f"[{solver_name}] Generated code contains 'std::vector' (dynamic allocation)"

    def test_no_runtime_indexed_stage_arrays(self, solver_name: str):
        """
        Verify no runtime-indexed stage arrays exist in generated code.

        All stage variables should be named scalars (e.g., K1_0, K2_0) rather than
        runtime-indexed arrays (e.g., K[i], stage_vec[i]).

        **Validates: Requirements 5.1**
        """
        code = _generate_code_for_solver(solver_name)

        # No array-indexed patterns for stage variables
        assert not re.search(r"\bK\[\s*\w+\s*\]", code), f"[{solver_name}] Generated code contains runtime-indexed K[i] array"
        assert not re.search(r"\bstage_vec\[", code), f"[{solver_name}] Generated code contains runtime-indexed stage_vec["
        assert not re.search(r"\bF\[\s*\w+\s*\]", code), f"[{solver_name}] Generated code contains runtime-indexed F[i] array"
        assert not re.search(r"\bY\[\s*\w+\s*\]", code), f"[{solver_name}] Generated code contains runtime-indexed Y[i] array"

    def test_no_runtime_loops_over_stages(self, solver_name: str):
        """
        Verify all stage logic is fully unrolled (no loops over stage count in generated C++).

        The Python-time unrolling should produce only unrolled C++ code with no
        for/while loops iterating over stages.

        **Validates: Requirements 5.3**
        """
        code = _generate_code_for_solver(solver_name)

        # The forward integrator is fully unrolled.  Checkpoint/adjoint replay
        # support intentionally contains bounded loops in the same header.
        integrate_code = code[code.index("void integrate(") : code.index("#ifdef MKPP_ENABLE_REDUCTION")]
        assert "for (" not in integrate_code, f"[{solver_name}] Generated integrate() contains 'for (' loop"
        assert "for(" not in integrate_code, f"[{solver_name}] Generated integrate() contains 'for(' loop"
        # No while loops over stages (the outer while(t < dt_total) is the time-stepping
        # loop which is acceptable, but there should be no stage-related while loops)
        assert not re.search(r"\bwhile\s*\(\s*stage", integrate_code), f"[{solver_name}] Generated integrate() contains stage loop"
        assert not re.search(
            r"\bfor\s*\(\s*int\s+stage", integrate_code
        ), f"[{solver_name}] Generated integrate() contains stage loop"

    def test_kokkos_inline_function_annotation(self, solver_name: str):
        """
        Verify KOKKOS_INLINE_FUNCTION annotation appears before integrate() and
        integrate_with_reduction() function definitions.

        The generated integrator must use KOKKOS_INLINE_FUNCTION to remain callable
        from GPU kernels.

        **Validates: Requirements 5.4**
        """
        code = _generate_code_for_solver(solver_name)

        # Check KOKKOS_INLINE_FUNCTION appears before integrate()
        # The pattern is: KOKKOS_INLINE_FUNCTION ... void integrate(
        integrate_pattern = re.compile(
            r"KOKKOS_INLINE_FUNCTION[^;]*?\bvoid\s+integrate\s*\(",
            re.DOTALL,
        )
        assert integrate_pattern.search(code), (
            f"[{solver_name}] Generated code missing KOKKOS_INLINE_FUNCTION " f"annotation before integrate() function"
        )

        # Check KOKKOS_INLINE_FUNCTION appears before integrate_with_reduction()
        reduction_pattern = re.compile(
            r"KOKKOS_INLINE_FUNCTION[^;]*?\bvoid\s+integrate_with_reduction\s*\(",
            re.DOTALL,
        )
        assert reduction_pattern.search(code), (
            f"[{solver_name}] Generated code missing KOKKOS_INLINE_FUNCTION "
            f"annotation before integrate_with_reduction() function"
        )

    def test_stage_variable_naming_convention(self, solver_name: str):
        """
        Verify all stage variables follow the naming convention:
        K{n}_{i}, Y{n}_{i}, F{n}_{i} where n is stage number and i is species index.

        **Validates: Requirements 5.1**
        """
        code = _generate_code_for_solver(solver_name)
        tableau = SOLVER_COEFFICIENTS[solver_name]

        # Verify K variables exist for each stage with proper naming
        for stage in range(1, tableau.stages + 1):
            pattern = rf"\bdouble K{stage}_\d+\b"
            matches = re.findall(pattern, code)
            assert len(matches) > 0, f"[{solver_name}] No K{stage}_* variables found for stage {stage}"

        # Verify F variables exist for stages where NewF is True
        for stage in range(1, tableau.stages + 1):
            if tableau.NewF[stage - 1]:
                pattern = rf"\bdouble F{stage}_\d+\b"
                matches = re.findall(pattern, code)
                assert len(matches) > 0, f"[{solver_name}] No F{stage}_* variables found for stage {stage} (NewF=True)"

        # Verify Y variables exist for stages > 1
        for stage in range(2, tableau.stages + 1):
            pattern = rf"\bdouble Y{stage}_\d+\b"
            matches = re.findall(pattern, code)
            assert len(matches) > 0, f"[{solver_name}] No Y{stage}_* variables found for stage {stage}"
