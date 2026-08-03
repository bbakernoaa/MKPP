import json
import hashlib
import math
from pathlib import Path
from typing import Dict
from .model import MechanismDefinition


def _fold_numeric_falloff_powers(code: str) -> str:
    """Fold pure numeric falloff powers emitted by SymPy's C printer."""
    import re

    number = r"[-+]?(?:\d+\.\d*|\d*\.\d+|\d+)(?:[eE][-+]?\d+)?"
    pattern = re.compile(
        rf"pow\(({number}),\s*1\.0/\(1\.0 \+ ({number})/pow\(M_LN10, 2\)\)\)"
    )

    def replace(match):
        base = float(match.group(1))
        coefficient = float(match.group(2))
        exponent = 1.0 / (1.0 + coefficient / (math.log(10.0) ** 2))
        return f"{base ** exponent:.17g}"

    return pattern.sub(replace, code)


def _strength_reduce_squares(code: str) -> str:
    """Replace generated pow(x, 2) terms with explicit multiplication."""
    import re

    term = r"(?:state\(\d+\)|Ynew_\d+|S_\d+)"
    return re.sub(rf"pow\(({term}), 2\)", r"\1 * \1", code)


def format_eqn(eqn_str, species_list, state_var="state", use_parentheses=True):
    import sympy as sp
    import re

    # 1. Clean up double negatives first because sympy might fail to parse `--` in strings
    s = str(eqn_str).replace('--', '+').replace('^+', '^').replace('**+', '**')
    if s == '0': return '0.0'

    # 2. Try to use SymPy's C-code generator for robust math formatting
    try:
        expr = sp.sympify(s)
        # Substitute legacy KPP dummy vars to 1.0 before C-code generation
        subs_dict = {
            sp.Symbol('C_DummyCH4'): 1.0,
            sp.Symbol('C_DummyNMVOC'): 1.0,
            sp.Symbol('C_FixedOH'): 1.0,
            sp.Symbol('C_FixedCl'): 1.0,
            sp.Symbol('C_CO'): 1.0,
            sp.Symbol('C_NO2'): 1.0,
            sp.Symbol('C_NO'): 1.0,
            sp.Symbol('C_CH4'): 1.0,
            sp.Symbol('C_N2O'): 1.0,
            sp.Symbol('C_H2O'): 1.0,
            sp.Symbol('C_H2'): 1.0,
            sp.Symbol('C_CO2'): 1.0,
            sp.Symbol('C_O1D'): 1.0,
            sp.Symbol('SUN'): 1.0,
            sp.Symbol('TEMP'): 300.0,
            sp.Symbol('temp'): 300.0,
            sp.Symbol('Temp'): 300.0,
            sp.Symbol('S_a'): 1.0,
            sp.Symbol('v_gas'): 1.0
        }

        expr = expr.subs(subs_dict)
        s = sp.ccode(expr)
        s = _fold_numeric_falloff_powers(s)
    except Exception as e:
        # Fallback to regex if sympy fails
        s = re.sub(r'([a-zA-Z0-9_\(\)\.\+\-\*\/]+)\*\*(\-?\d+\.\d+|\-?\d+)', r'pow(\1, \2)', s)
        s = s.replace('Temp', '300.0')
        s = s.replace('S_a', '1.0')
        s = s.replace('v_gas', '1.0')
        s = _fold_numeric_falloff_powers(s)

    # 3. Map the C_X species symbols from the SymPy AST directly into the state indices or variables.
    sorted_sp = sorted(list(enumerate(species_list)), key=lambda x: len(x[1].name), reverse=True)
    for idx_s, sp in sorted_sp:
        if use_parentheses:
            repl = f"{state_var}({idx_s})"
        else:
            repl = f"{state_var}_{idx_s}"
        s = re.sub(r'\bC_' + sp.name + r'(?!\w)', repl, s)

    s = _strength_reduce_squares(s)

    return s

def generate_headers(mech: MechanismDefinition, out_dir: str = "src/solvers", suffix: str = "") -> Dict[str, str]:
    """Emit the Kokkos headers and manifest artifact."""
    if not mech or not mech.species:
        raise ValueError("Cannot generate headers for empty mechanism")

    out_path = Path(out_dir)
    out_path.mkdir(parents=True, exist_ok=True)

    # Retrieve sympy_metadata safely whether stored as attribute or in mech.metadata dict
    sympy_meta = None
    if getattr(mech, "metadata", None) and isinstance(mech.metadata, dict):
        sympy_meta = mech.metadata.get("sympy_metadata")
    if sympy_meta is None:
        sympy_meta = getattr(mech, "sympy_metadata", None)

    # 1. Deterministic header emission
    header_path = out_path / f"{mech.name}{suffix}.hpp"
    with open(header_path, 'w') as f:
        f.write("#pragma once\n")
        f.write("#include <Kokkos_Core.hpp>\n")
        f.write(f"// Generated solver for {mech.name}\n")

        # T027: Emit workload-sorting annotations for downstream runtime
        partition_meta = getattr(mech, "partition_metadata", None)
        if partition_meta and partition_meta.get("sza_sorted"):
            f.write("// SZA Workload Sorted: true\n")

        # T033: Emit continuous-thermodynamics annotations
        has_continuous_rxns = any(r.continuous_transition for r in mech.reactions)
        if has_continuous_rxns:
            f.write("// Hysteresis/Spline Continuous Transition: true\n")

        f.write("namespace mkpp {\n")
        f.write("  // Pure Kokkos abstractions (no raw pragmas allowed)\n")

        # T021: Zero-copy unmanaged views for host interaction (e.g. Fortran LayoutLeft)
        if getattr(mech, "host_interface", None) and mech.host_interface.arrays:
            f.write("  // Bidirectional Host Interface (Zero-Copy)\n")
            for arr in mech.host_interface.arrays:
                f.write(f"  using {arr.name}_view_t = Kokkos::View<double")
                f.write("*" * arr.rank)
                f.write(f", Kokkos::{arr.layout}, Kokkos::MemoryUnmanaged>;\n")

        f.write("  template<typename DeviceType>\n")
        f.write("  struct SolverKernels {\n")

        # 1. compute_rates
        f.write("      template <class StateView, class RateView>\n")
        f.write("      KOKKOS_INLINE_FUNCTION void compute_rates(const StateView& state, RateView& F_block) const {\n")
        if sympy_meta:
            if "f_implicit" in sympy_meta and "f_explicit" in sympy_meta:
                F = sympy_meta["f_implicit"] + sympy_meta["f_explicit"]
            elif "f_vector" in sympy_meta:
                F = sympy_meta["f_vector"]
            else:
                F = []
            for i in range(len(F)):
                eqn = format_eqn(F[i], mech.species, state_var="state", use_parentheses=True)
                f.write(f"          F_block({i}) = {eqn};\n")
        f.write("      }\n\n")

        # 2. compute_jacobian
        f.write("      template <class StateView, class JacView>\n")
        f.write("      KOKKOS_INLINE_FUNCTION void compute_jacobian(const StateView& state, JacView& J_block) const {\n")
        if sympy_meta and "jacobian_matrix" in sympy_meta:
            J = sympy_meta["jacobian_matrix"]
            for i in range(J.shape[0]):
                for j in range(J.shape[1]):
                    if J[i, j] != 0:
                        eqn = format_eqn(J[i, j], mech.species, state_var="state", use_parentheses=True)
                        f.write(f"          J_block({i}, {j}) = {eqn};\n")
        f.write("      }\n\n")

        # 3. compute_adjoint
        f.write("      template <class StateView, class JacView>\n")
        f.write("      KOKKOS_INLINE_FUNCTION void compute_adjoint(const StateView& state, JacView& J_adj_block) const {\n")
        if sympy_meta and "adjoint_matrix" in sympy_meta:
            J_adj = sympy_meta["adjoint_matrix"]
            for i in range(J_adj.shape[0]):
                for j in range(J_adj.shape[1]):
                    if J_adj[i, j] != 0:
                        eqn = format_eqn(J_adj[i, j], mech.species, state_var="state", use_parentheses=True)
                        f.write(f"          J_adj_block({i}, {j}) = {eqn};\n")
        f.write("      }\n\n")

        # 4. compute_tlm
        f.write("      template <class StateView, class DeltaView, class RateView>\n")
        f.write("      KOKKOS_INLINE_FUNCTION void compute_tlm(const StateView& state, const DeltaView& delta_C, RateView& dF_block) const {\n")
        if sympy_meta and "jacobian_matrix" in sympy_meta:
            J = sympy_meta["jacobian_matrix"]
            for i in range(J.shape[0]):
                f.write(f"          dF_block({i}) = 0.0;\n")
                for j in range(J.shape[1]):
                    if J[i, j] != 0:
                        eqn = format_eqn(J[i, j], mech.species, state_var="state", use_parentheses=True)
                        f.write(f"          dF_block({i}) += ({eqn}) * delta_C({j});\n")
        f.write("      }\n\n")

        # 5. project_mass_conservation
        f.write("      template <class StateView, class MassView>\n")
        f.write("      KOKKOS_INLINE_FUNCTION void project_mass_conservation(StateView& C_projected, const StateView& C, const MassView& m_0) const {\n")
        f.write("          // C_projected = C - E^T (E E^T)^-1 (E C - m_0)\n")
        if sympy_meta and "mass_projector" in sympy_meta:
            P = sympy_meta["mass_projector"]
            elements = sympy_meta["element_map"]
            for i, elem in enumerate(elements):
                f.write(f"          double delta_m_{i} = -m_0({i});\n")
                for j, sp_name in enumerate(sympy_meta["species_map"]):
                    s_def = next(s for s in mech.species if s.name == sp_name)
                    if elem in s_def.elements:
                        f.write(f"          delta_m_{i} += {s_def.elements[elem]} * C({j});\n")
            for i in range(P.shape[0]):
                f.write(f"          C_projected({i}) = C({i});\n")
                for j in range(P.shape[1]):
                    if P[i, j] != 0:
                        f.write(f"          C_projected({i}) -= ({P[i, j]}) * delta_m_{j};\n")
        f.write("      }\n\n")

        # 6. integrate (AOT Symbolic LU, Pure Scalar Register Allocation, Fused Stages, Subview Interface)
        f.write("      template <class StateView>\n")
        f.write("      KOKKOS_INLINE_FUNCTION void integrate(double dt, StateView& state) const {\n")
        N = len(mech.species)
        f.write(f"          const int NUM_SPECIES = {N};\n")
        f.write("          const double g = 1.70710678118654752440;\n")
        f.write("          const double ros_A0 = 1.0 / g;\n")
        f.write("          const double ros_C0 = -2.0 / g;\n")
        f.write("          const double ros_M0 = 3.0 / (2.0 * g);\n")
        f.write("          const double ros_M1 = 1.0 / (2.0 * g);\n")
        f.write("          const double inv_g_dt = 1.0 / (g * dt);\n\n")
        f.write("          // 0. Hoist state values into scalar registers\n")
        for i in range(N):
            f.write(f"          const double S_{i} = state({i});\n")
        f.write("\n")

        lu_plan = None
        if isinstance(getattr(mech, "metadata", None), dict):
            lu_plan = mech.metadata.get("symbolic_lu_plan")
        if lu_plan is None and sympy_meta and "symbolic_lu_plan" in sympy_meta:
            lu_plan = sympy_meta["symbolic_lu_plan"]
        if lu_plan is None and getattr(mech, "symbolic_lu_plan", None):
            lu_plan = getattr(mech, "symbolic_lu_plan", None)

        if not lu_plan and sympy_meta and "jacobian_matrix" in sympy_meta:
            from .lowering import compute_symbolic_lu_decomposition
            lu_plan = compute_symbolic_lu_decomposition(sympy_meta["jacobian_matrix"], [s.name for s in mech.species])

        if lu_plan:
            # Stage 1 Rates F1
            f.write("          // 1. Stage 1 Rates (F1)\n")
            if sympy_meta:
                if "f_implicit" in sympy_meta and "f_explicit" in sympy_meta:
                    F = sympy_meta["f_implicit"] + sympy_meta["f_explicit"]
                elif "f_vector" in sympy_meta:
                    F = sympy_meta["f_vector"]
                else:
                    F = [0] * N
                for i in range(len(F)):
                    eqn = format_eqn(F[i], mech.species, state_var="S", use_parentheses=False)
                    f.write(f"          double F1_{i} = {eqn};\n")

            # Jacobian Non-Zeros
            f.write("\n          // 2. Analytical Jacobian & Iteration Matrix W = inv_g_dt*I - J\n")
            non_zero_jac_set = set()
            for i, j, expr_str in lu_plan.non_zero_jacobian:
                non_zero_jac_set.add((i, j))
                eqn = format_eqn(expr_str, mech.species, state_var="S", use_parentheses=False)
                f.write(f"          double J_{i}_{j} = {eqn};\n")

            for i in range(N):
                for j in range(N):
                    if i == j:
                        if (i, i) in non_zero_jac_set:
                            f.write(f"          double W_{i}_{i} = inv_g_dt - J_{i}_{i};\n")
                        else:
                            f.write(f"          double W_{i}_{i} = inv_g_dt;\n")
                    elif (i, j) in non_zero_jac_set:
                        f.write(f"          double W_{i}_{j} = -J_{i}_{j};\n")

            # Symbolic LU Factorization
            f.write("\n          // 3. Symbolic Doolittle Sparse LU Factorization\n")
            for kind, i, j, expr_str in lu_plan.lu_expressions_ordered:
                f.write(f"          double {kind}_{i}_{j} = {expr_str};\n")

            # Stage 1 Forward & Backward Substitution
            f.write("\n          // 4. Forward & Backward Substitution for Stage K1\n")
            import re
            for i, expr_str in lu_plan.forward_sub_steps:
                s = re.sub(r'\bb_(\d+)\b', r'F1_\1', expr_str)
                s = re.sub(r'\by_(\d+)\b', r'y1_\1', s)
                f.write(f"          double y1_{i} = {s};\n")
            for i, expr_str in lu_plan.backward_sub_steps:
                s = re.sub(r'\by_(\d+)\b', r'y1_\1', s)
                s = re.sub(r'\bx_(\d+)\b', r'K1_\1', s)
                f.write(f"          double K1_{i} = {s};\n")

            # Fused Intermediate State Ynew
            f.write("\n          // 5. Fused Intermediate State Ynew\n")
            for i in range(N):
                f.write(f"          double Ynew_{i} = S_{i} + ros_A0 * K1_{i};\n")

            # Stage 2 Rates F2 & Substitution
            f.write("\n          // 6. Stage 2 Rates (F2) & Substitution for Stage K2\n")
            if sympy_meta:
                for i in range(len(F)):
                    eqn = format_eqn(F[i], mech.species, state_var="Ynew", use_parentheses=False)
                    f.write(f"          double F2_{i} = {eqn};\n")
                    f.write(f"          double rhs2_{i} = F2_{i} + (ros_C0 / dt) * K1_{i};\n")

            for i, expr_str in lu_plan.forward_sub_steps:
                s = re.sub(r'\bb_(\d+)\b', r'rhs2_\1', expr_str)
                s = re.sub(r'\by_(\d+)\b', r'y2_\1', s)
                f.write(f"          double y2_{i} = {s};\n")
            for i, expr_str in lu_plan.backward_sub_steps:
                s = re.sub(r'\by_(\d+)\b', r'y2_\1', expr_str)
                s = re.sub(r'\bx_(\d+)\b', r'K2_\1', s)
                f.write(f"          double K2_{i} = {s};\n")

            # Final Fused State Update
            f.write("\n          // 7. Final Fused State Update\n")
            for i in range(N):
                f.write(f"          state({i}) += ros_M0 * K1_{i} + ros_M1 * K2_{i};\n")

        f.write("      }\n")
        f.write("  };\n")
        f.write("}\n")

    # 2. Manifest metadata emission (T008)
    manifest = {
        "mechanism": mech.name,
        "aerosol_representation": mech.aerosol_representation.value,
        "checksum": hashlib.sha256(mech.name.encode()).hexdigest(), # Simplified checksum for MVP
        "artifacts": [
            {"kind": "header", "file": header_path.name},
            {"kind": "adjoint_tlm_record", "differentiable": True}
        ]
    }

    if getattr(mech, "host_interface", None) and mech.host_interface.arrays:
        manifest["host_interface"] = {
            arr.name: {
                "rank": arr.rank,
                "layout": arr.layout,
                "lifetime": "unmanaged_borrowed_from_host" if arr.ownership == "host" else "device_owned"
            }
            for arr in mech.host_interface.arrays
        }

    partition_meta = getattr(mech, "partition_metadata", None)
    if partition_meta:
        manifest["solver_partition"] = partition_meta

    manifest_path = out_path / "manifest.json"
    with open(manifest_path, 'w') as f:
        json.dump(manifest, f, indent=2)

    return {"header": str(header_path), "manifest": str(manifest_path)}
