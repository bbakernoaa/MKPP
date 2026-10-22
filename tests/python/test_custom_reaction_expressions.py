"""Custom modal reaction laws: safe parsing, conservation and compiled derivatives.

Author: MKPP contributors. History: 2026-10. Usage: pytest; temporary outputs only.
"""

import ctypes
import math
import os
import re
import shutil
import subprocess
from pathlib import Path

import pytest
import sympy as sp
from mkpp.codegen import generate_headers
from mkpp.expressions import parse_rate_expression
from mkpp.lowering import prepare_unified_jacobian
from mkpp.model import CompilationError, PhaseMode
from mkpp.parser import load_mechanism, parse_mechanism_micm


def mechanism(reactions, definitions=None):
    """Construct a small mechanism with a conserved transfer pair and number."""
    return parse_mechanism_micm(
        "custom_test",
        {
            "species": [{"name": name} for name in ("gas", "particle", "number")],
            "rate_definitions": definitions or {},
            "reactions": reactions,
        },
    )


def test_nested_parameters_and_full_flux_jacobian():
    mech = mechanism(
        [
            {
                "type": "CUSTOM",
                "reactants": {"gas": 1},
                "products": {"particle": 1},
                "parameters": {"rate_basis": "flux", "rate_expression": "uptake*(C_gas - 0.2*C_particle)"},
            }
        ],
        {"uptake": "0.001*C_number"},
    )
    result = prepare_unified_jacobian(mech)
    gas, particle, number = (sp.Symbol("C_" + s, real=True, nonnegative=True) for s in ("gas", "particle", "number"))
    rhs = result["f_implicit"] + result["f_explicit"]
    flux = 0.001 * number * (gas - 0.2 * particle)
    assert sp.simplify(rhs[0] + flux) == 0
    assert sp.simplify(rhs[0] + rhs[1]) == 0
    assert rhs[2] == 0
    assert sp.simplify(result["jacobian_matrix"][1, 2] - sp.diff(flux, number)) == 0


def test_openatmos_phase_annotations_for_modal_species():
    mech = parse_mechanism_micm(
        "phases",
        {
            "species": [
                {"name": "vapor", "phase": "gas"},
                {"name": "material", "phase": "aerosol"},
                {"name": "water", "phase": "aqueous"},
                {"name": "legacy"},
            ]
        },
    )
    assert [species.phase for species in mech.species] == [
        PhaseMode.GAS,
        PhaseMode.AEROSOL,
        PhaseMode.AQUEOUS,
        PhaseMode.GAS,
    ]
    with pytest.raises(CompilationError, match="Invalid phase"):
        parse_mechanism_micm("bad_phase", {"species": [{"name": "x", "phase": "ice"}]})


def test_nucleation_stoichiometry_independent_of_order():
    mech = mechanism(
        [
            {
                "type": "CUSTOM",
                "reactants": {"gas": 100},
                "products": {"particle": 100, "number": 1},
                "parameters": {"rate_expression": "1e-5", "reaction_orders": {"gas": 1.5}},
            }
        ]
    )
    result = prepare_unified_jacobian(mech)
    rhs = result["f_implicit"] + result["f_explicit"]
    assert sp.simplify(rhs[0] + rhs[1]) == 0
    assert sp.simplify(rhs[1] - 100 * rhs[2]) == 0
    assert result["rate_flux_exprs"][0].has(sp.Pow(sp.Symbol("C_gas", real=True, nonnegative=True), sp.Rational(3, 2)))


@pytest.mark.parametrize(
    "expression",
    ["__import__('os')", "C_gas.__class__", "C_gas[0]", "lambda: 1", "unknown + 1", "1e309", "1/0", "sqrt(-1)", "exp(x=1)"],
)
def test_reject_unsafe_or_unknown_expression(expression):
    with pytest.raises(ValueError):
        parse_rate_expression(expression, {"C_gas": sp.Symbol("C_gas")})


@pytest.mark.parametrize(
    "parameters",
    [
        {"rate_expression": "1", "rate_basis": "unknown"},
        {"rate_expression": "1", "rate_basis": "flux", "reaction_orders": {}},
        {"rate_expression": "1", "reaction_orders": {"missing": 1}},
        {"rate_expression": "1", "reaction_orders": {"gas": -1}},
        {"rate_expression": "1", "reaction_orders": {"gas": float("nan")}},
        {},
    ],
)
def test_reject_invalid_rate_contract(parameters):
    with pytest.raises(ValueError):
        prepare_unified_jacobian(
            mechanism(
                [
                    {
                        "type": "CUSTOM",
                        "reactants": {"gas": 1},
                        "products": {"particle": 1},
                        "parameters": parameters,
                    }
                ]
            )
        )


def test_reject_conflicting_parameter_forms_and_forward_definitions():
    with pytest.raises(CompilationError, match="Conflicting"):
        mechanism([{"type": "ARRHENIUS", "A": 1, "parameters": {"A": 2}}])
    for definitions in ({"a": "b", "b": "1"}, {"C_gas": 1}, {"exp": 1}):
        with pytest.raises(ValueError):
            prepare_unified_jacobian(mechanism([], definitions))


def compiled_evaluator(mech, tmp_path):
    """Compile generated rate/Jacobian kernels and return their C entry point."""
    compiler = shutil.which("c++")
    if compiler is None:
        pytest.skip("C++ compiler required for generated kernel check")
    prefixes = [
        os.environ.get("Kokkos_ROOT", ""),
        *os.environ.get("CMAKE_PREFIX_PATH", "").split(os.pathsep),
        "/opt/kokkos",
        "/workspace/dependencies/install-ci",
    ]
    includes = [Path(prefix) / "include" for prefix in prefixes if prefix]
    kokkos_include = next((path for path in includes if (path / "Kokkos_Core.hpp").is_file()), None)
    if kokkos_include is None:
        pytest.skip("Kokkos headers required for generated kernel check")
    generate_headers(mech, out_dir=str(tmp_path))
    sources = sorted(tmp_path.glob("**/rates.cpp")) + sorted(tmp_path.glob("**/jacobian.cpp"))
    assert sources
    calls = []
    for path in sources:
        text = path.with_suffix(".hpp").read_text()
        target = "rates" if path.name == "rates.cpp" else "jacobian"
        for name in re.findall(r"\b(compute_\w+_chunk_\d+)\s*\(", text):
            calls.append(f"{name}(state,{target},nullptr,0,0,0);")
    assert calls
    wrapper = tmp_path / "wrapper.cpp"
    wrapper.write_text(
        f'#include "{mech.name}/rates.hpp"\n#include "{mech.name}/jacobian.hpp"\n'
        'extern "C" void evaluate(const double*s,double*r,double*j){'
        f"using namespace mkpp::generated::{mech.name}::detail;"
        "StrideView<const double,1> state(s,1); StrideView<double,1> rates(r,1);"
        f"StrideView<double,2> jacobian(j,{len(mech.species)},1);" + "".join(calls) + "}"
    )
    library = tmp_path / "kernels.so"
    subprocess.run(
        [
            compiler,
            "-std=c++23",
            "-fopenmp",
            "-shared",
            "-fPIC",
            "-I",
            str(kokkos_include),
            "-I",
            str(tmp_path),
            *map(str, sources),
            str(wrapper),
            "-o",
            str(library),
        ],
        check=True,
    )
    evaluate = ctypes.CDLL(str(library)).evaluate
    pointer = ctypes.POINTER(ctypes.c_double)
    evaluate.argtypes = [pointer, pointer, pointer]
    evaluate.restype = None
    return evaluate


def test_compiled_piecewise_flux_and_jacobian(tmp_path):
    mech = mechanism(
        [
            {
                "type": "CUSTOM",
                "reactants": {"gas": 1},
                "products": {"particle": 1},
                "parameters": {"rate_basis": "flux", "rate_expression": "flux"},
            }
        ],
        {"flux": "Piecewise((0.001*C_gas/C_number, C_number > 0), (0, True))"},
    )
    evaluate = compiled_evaluator(mech, tmp_path)
    for number in (0.0, 4.0):
        state = (ctypes.c_double * 3)(10.0, 2.0, number)
        rhs, jac = (ctypes.c_double * 3)(), (ctypes.c_double * 9)()
        evaluate(state, rhs, jac)
        assert rhs[0] == pytest.approx(-0.01 / number if number else 0)
        assert rhs[0] + rhs[1] == 0
        assert jac[2] == pytest.approx(0.01 / number**2 if number else 0)


def test_generated_modal_example_conservation_shell_and_finite_differences(tmp_path):
    mech = load_mechanism(Path(__file__).parents[2] / "examples/modal_processes.yaml")
    evaluate = compiled_evaluator(mech, tmp_path)
    count = len(mech.species)
    index = {species.name: i for i, species in enumerate(mech.species)}

    def run(values):
        state = (ctypes.c_double * count)(*values)
        rhs, jac = (ctypes.c_double * count)(), (ctypes.c_double * (count * count))()
        evaluate(state, rhs, jac)
        assert all(math.isfinite(value) for value in (*rhs, *jac))
        return list(rhs), list(jac)

    # Condensation and evaporation branches, including the frozen coagulation
    # forcing derivative. Test away from branch boundaries for central differences.
    for gas_concentration in (1e6, 100.0):
        values = [1e5] * count
        values[index["H2SO4"]] = gas_concentration
        values[index["ORGANIC_VAPOR"]] = gas_concentration
        values[index["N_primary_carbon"]] = 1000.0
        values[index["COAG_VOLUME_RATE"]] = 1e-16
        rhs, jac = run(values)
        acid_rows = [index[name] for name in ("H2SO4", "ACID_aitken", "ACID_primary_carbon", "ACID_accumulation")]
        org_rows = [index[name] for name in ("ORGANIC_VAPOR", "ORGANIC_primary_carbon", "ORGANIC_accumulation")]
        for rows in (acid_rows, org_rows, [index["BC_primary_carbon"], index["BC_accumulation"]]):
            assert sum(rhs[row] for row in rows) == pytest.approx(0, abs=1e-8)
            for col in range(count):
                entries = [jac[row * count + col] for row in rows]
                assert abs(sum(entries)) <= 1e-12 * max(1.0, sum(abs(entry) for entry in entries))
        nucleation = 1e-8 * gas_concentration**1.5
        assert sum(rhs[index[name]] for name in ("N_aitken", "N_primary_carbon", "N_accumulation")) == pytest.approx(nucleation)
        assert rhs[index["COAG_VOLUME_RATE"]] == 0
        # Independent scalar shell calculation for the BC transfer (BC does not
        # condense). This checks the closure beyond symbolic differentiation.
        volume = 1e6 / 6.02214076e23 * 1e5 * (0.098079 / 1700 + 0.15 / 1800 + 0.012011 / 1000)
        log_width = math.log(1.6)
        radius = (volume / (4 * math.pi / 3 * 1e9 * math.exp(4.5 * log_width**2))) ** (1 / 3)
        uptake = 4 * math.pi * 8e-6 * 1e9 * radius * math.exp(0.5 * log_width**2)
        coating = (
            uptake * 1e6 / 6.02214076e23 * (gas_concentration * 0.098079 / 1700 + (gas_concentration - 0.2e5) * 0.15 / 1800) + 1e-16
        )
        shell = (
            4
            * math.pi
            * 1e9
            * (radius**2 * math.exp(2 * log_width**2) * 1e-9 + radius * math.exp(0.5 * log_width**2) * 1e-18 + 1e-27 / 3)
        )
        assert rhs[index["BC_accumulation"]] == pytest.approx(max(coating, 0) / shell * 1e5)
        for col in range(count):
            # Large frozen-forcing terms coexist with small gas derivatives;
            # use a step that resolves those derivatives above subtraction noise.
            step = abs(values[col]) * 1e-3
            plus, minus = list(values), list(values)
            plus[col] += step
            minus[col] -= step
            high, _ = run(plus)
            low, _ = run(minus)
            for row in range(count):
                assert jac[row * count + col] == pytest.approx((high[row] - low[row]) / (2 * step), rel=1e-4, abs=1e-8)
    empty = [0.0] * count
    empty[index["H2SO4"]] = 1e6
    empty[index["COAG_VOLUME_RATE"]] = 1e-16
    rhs, _ = run(empty)
    assert rhs[index["BC_accumulation"]] == 0
    assert rhs[index["N_accumulation"]] == 0
