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
            # Legacy KPP dummy/fixed species (not real state variables)
            sp.Symbol('C_DummyCH4'): 1.0,
            sp.Symbol('C_DummyNMVOC'): 1.0,
            sp.Symbol('C_FixedOH'): 1.0,
            sp.Symbol('C_FixedCl'): 1.0,
            # Environmental parameters (not species concentrations)
            sp.Symbol('SUN'): 1.0,
            sp.Symbol('TEMP'): 300.0,
            sp.Symbol('temp'): 300.0,
            sp.Symbol('Temp'): 300.0,
            sp.Symbol('S_a'): 1.0,
            sp.Symbol('v_gas'): 1.0,
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

        # 6a. Per-species tolerance arrays (atol, rtol)
        N = len(mech.species)
        # Source tolerances from mechanism metadata or use defaults
        default_atol = 100.0  # molecules/cm3, atmospheric chemistry standard
        default_rtol = 1e-2  # 1% relative tolerance, suitable for atmospheric chemistry
        atol_values = None
        rtol_values = None
        if isinstance(getattr(mech, "metadata", None), dict):
            atol_values = mech.metadata.get("atol")
            rtol_values = mech.metadata.get("rtol")
        if atol_values is None:
            atol_values = [default_atol] * N
        if rtol_values is None:
            rtol_values = [default_rtol] * N
        # Ensure exactly N entries
        atol_values = list(atol_values)[:N]
        rtol_values = list(rtol_values)[:N]
        while len(atol_values) < N:
            atol_values.append(default_atol)
        while len(rtol_values) < N:
            rtol_values.append(default_rtol)

        atol_str = ", ".join(f"{v}" for v in atol_values)
        rtol_str = ", ".join(f"{v}" for v in rtol_values)
        f.write(f"      static constexpr int NUM_SPECIES = {N};\n")
        f.write(f"      static constexpr double atol[NUM_SPECIES] = {{ {atol_str} }};\n")
        f.write(f"      static constexpr double rtol[NUM_SPECIES] = {{ {rtol_str} }};\n\n")

        # 6. integrate (AOT Symbolic LU, ROS-3: 3-stage, 3rd order, L-stable, Sandu & Sander 2006)
        f.write("      template <class StateView>\n")
        f.write("      KOKKOS_INLINE_FUNCTION void integrate(double dt_total, StateView& state) const {\n")
        f.write(f"          const int NUM_SPECIES = {N};\n")
        f.write("          // ROS-3 coefficients (Sandu & Sander 2006, KPP Ros3 subroutine)\n")
        f.write("          const double g = 0.43586652150845899941601945119356;\n")
        f.write("          const double ros_A21 = 1.0;\n")
        f.write("          const double ros_A31 = 1.0;\n")
        f.write("          const double ros_A32 = 0.0;\n")
        f.write("          const double ros_C21 = -1.0156171083877702091975600115545;\n")
        f.write("          const double ros_C31 =  4.0759956452537699824805835358067;\n")
        f.write("          const double ros_C32 =  9.2076794298330791242156818474003;\n")
        f.write("          const double ros_M1 = 1.0;\n")
        f.write("          const double ros_M2 = 6.1697947043828245592553615689730;\n")
        f.write("          const double ros_M3 = -0.42772256543218573326238373806514;\n")
        f.write("          const double ros_E1 = 0.5;\n")
        f.write("          const double ros_E2 = -2.9079558716805469821718236208017;\n")
        f.write("          const double ros_E3 = 0.22354069897811569627360909276199;\n")
        f.write("          const double safety = 0.9;\n")
        f.write("          const double max_growth = 6.0;\n")
        f.write("          const double min_shrink = 0.2;\n")
        f.write("          double t = 0.0;\n")
        f.write("          double dt = dt_total;\n\n")
        f.write("          while (t < dt_total) {\n")
        f.write("          dt = Kokkos::min(dt, dt_total - t);\n")
        f.write("          const double inv_g_dt = 1.0 / (g * dt);\n\n")
        f.write("          // 0. Hoist state values into scalar registers\n")

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

        # Determine permutation for state access
        _perm = lu_plan.permutation if lu_plan and lu_plan.permutation else None

        if _perm:
            f.write("          // NOTE: State access uses permuted species ordering\n")

        for i in range(N):
            src_idx = _perm[i] if _perm else i
            f.write(f"          const double S_{i} = state({src_idx});\n")
        f.write("\n")

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
            # Emit block boundary comments if block structure is present
            if lu_plan.blocks and len(lu_plan.blocks) > 1:
                _emitted_block_header = set()
                for kind, i, j, expr_str in lu_plan.lu_expressions_ordered:
                    # Find which block this expression belongs to
                    for block_num, block_indices in enumerate(lu_plan.blocks):
                        if i in block_indices:
                            if block_num not in _emitted_block_header:
                                _emitted_block_header.add(block_num)
                                block_species_names = [lu_plan.species_map[idx] for idx in block_indices]
                                f.write(f"          // Block {block_num}: species [{', '.join(block_species_names)}]\n")
                            break
                    f.write(f"          double {kind}_{i}_{j} = {expr_str};\n")
            else:
                for kind, i, j, expr_str in lu_plan.lu_expressions_ordered:
                    f.write(f"          double {kind}_{i}_{j} = {expr_str};\n")

            # Stage 1 Forward & Backward Substitution
            f.write("\n          // 4. Forward & Backward Substitution for Stage K1\n")
            import re
            if lu_plan.blocks and len(lu_plan.blocks) > 1:
                _emitted_fwd_block = set()
                for i, expr_str in lu_plan.forward_sub_steps:
                    for block_num, block_indices in enumerate(lu_plan.blocks):
                        if i in block_indices:
                            if block_num not in _emitted_fwd_block:
                                _emitted_fwd_block.add(block_num)
                                block_species_names = [lu_plan.species_map[idx] for idx in block_indices]
                                f.write(f"          // Block {block_num}: forward sub [{', '.join(block_species_names)}]\n")
                            break
                    s = re.sub(r'\bb_(\d+)\b', r'F1_\1', expr_str)
                    s = re.sub(r'\by_(\d+)\b', r'y1_\1', s)
                    f.write(f"          double y1_{i} = {s};\n")
                _emitted_bwd_block = set()
                for i, expr_str in lu_plan.backward_sub_steps:
                    for block_num, block_indices in enumerate(lu_plan.blocks):
                        if i in block_indices:
                            if block_num not in _emitted_bwd_block:
                                _emitted_bwd_block.add(block_num)
                                block_species_names = [lu_plan.species_map[idx] for idx in block_indices]
                                f.write(f"          // Block {block_num}: backward sub [{', '.join(block_species_names)}]\n")
                            break
                    s = expr_str
                    s = re.sub(r'\by_(\d+)\b', r'y1_\1', s)
                    s = re.sub(r'\bx_(\d+)\b', r'K1_\1', s)
                    f.write(f"          double K1_{i} = {s};\n")
            else:
                for i, expr_str in lu_plan.forward_sub_steps:
                    s = re.sub(r'\bb_(\d+)\b', r'F1_\1', expr_str)
                    s = re.sub(r'\by_(\d+)\b', r'y1_\1', s)
                    f.write(f"          double y1_{i} = {s};\n")
                for i, expr_str in lu_plan.backward_sub_steps:
                    s = expr_str  # FIX: initialize from current step's expression
                    s = re.sub(r'\by_(\d+)\b', r'y1_\1', s)
                    s = re.sub(r'\bx_(\d+)\b', r'K1_\1', s)
                    f.write(f"          double K1_{i} = {s};\n")

            # Intermediate State Y2 = Y + A(2,1)*K1 = Y + K1
            f.write("\n          // 5. Intermediate State Y2 = Y + K1\n")
            for i in range(N):
                f.write(f"          double Y2_{i} = S_{i} + ros_A21 * K1_{i};\n")

            # Stage 2 Rates F2 & Substitution for K2
            f.write("\n          // 6. Stage 2 Rates (F2) at Y2, and solve for K2\n")
            if sympy_meta:
                for i in range(len(F)):
                    eqn = format_eqn(F[i], mech.species, state_var="Y2", use_parentheses=False)
                    f.write(f"          double F2_{i} = {eqn};\n")
                f.write("\n")
                for i in range(len(F)):
                    f.write(f"          double rhs2_{i} = F2_{i} + (ros_C21 / dt) * K1_{i};\n")

            if lu_plan.blocks and len(lu_plan.blocks) > 1:
                _emitted_fwd2_block = set()
                for i, expr_str in lu_plan.forward_sub_steps:
                    for block_num, block_indices in enumerate(lu_plan.blocks):
                        if i in block_indices:
                            if block_num not in _emitted_fwd2_block:
                                _emitted_fwd2_block.add(block_num)
                                block_species_names = [lu_plan.species_map[idx] for idx in block_indices]
                                f.write(f"          // Block {block_num}: K2 forward sub [{', '.join(block_species_names)}]\n")
                            break
                    s = re.sub(r'\bb_(\d+)\b', r'rhs2_\1', expr_str)
                    s = re.sub(r'\by_(\d+)\b', r'y2_\1', s)
                    f.write(f"          double y2_{i} = {s};\n")
                _emitted_bwd2_block = set()
                for i, expr_str in lu_plan.backward_sub_steps:
                    for block_num, block_indices in enumerate(lu_plan.blocks):
                        if i in block_indices:
                            if block_num not in _emitted_bwd2_block:
                                _emitted_bwd2_block.add(block_num)
                                block_species_names = [lu_plan.species_map[idx] for idx in block_indices]
                                f.write(f"          // Block {block_num}: K2 backward sub [{', '.join(block_species_names)}]\n")
                            break
                    s = expr_str
                    s = re.sub(r'\by_(\d+)\b', r'y2_\1', s)
                    s = re.sub(r'\bx_(\d+)\b', r'K2_\1', s)
                    f.write(f"          double K2_{i} = {s};\n")
            else:
                for i, expr_str in lu_plan.forward_sub_steps:
                    s = re.sub(r'\bb_(\d+)\b', r'rhs2_\1', expr_str)
                    s = re.sub(r'\by_(\d+)\b', r'y2_\1', s)
                    f.write(f"          double y2_{i} = {s};\n")
                for i, expr_str in lu_plan.backward_sub_steps:
                    s = expr_str  # FIX: initialize from current step's expression
                    s = re.sub(r'\by_(\d+)\b', r'y2_\1', s)
                    s = re.sub(r'\bx_(\d+)\b', r'K2_\1', s)
                    f.write(f"          double K2_{i} = {s};\n")

            # Stage 3: RHS3 = F2 + C31/dt*K1 + C32/dt*K2, solve W*K3 = RHS3
            # (NewF(3)=false: reuse F2 from Stage 2)
            f.write("\n          // 7. Stage 3: RHS3 = F2 + C31/dt*K1 + C32/dt*K2 (NewF=false, reuse F2)\n")
            for i in range(N):
                f.write(f"          double rhs3_{i} = F2_{i} + (ros_C31 / dt) * K1_{i} + (ros_C32 / dt) * K2_{i};\n")

            # Stage 3 forward/backward substitution
            if lu_plan.blocks and len(lu_plan.blocks) > 1:
                _emitted_fwd3_block = set()
                for i, expr_str in lu_plan.forward_sub_steps:
                    for block_num, block_indices in enumerate(lu_plan.blocks):
                        if i in block_indices:
                            if block_num not in _emitted_fwd3_block:
                                _emitted_fwd3_block.add(block_num)
                                block_species_names = [lu_plan.species_map[idx] for idx in block_indices]
                                f.write(f"          // Block {block_num}: K3 forward sub [{', '.join(block_species_names)}]\n")
                            break
                    s = re.sub(r'\bb_(\d+)\b', r'rhs3_\1', expr_str)
                    s = re.sub(r'\by_(\d+)\b', r'y3_\1', s)
                    f.write(f"          double y3_{i} = {s};\n")
                _emitted_bwd3_block = set()
                for i, expr_str in lu_plan.backward_sub_steps:
                    for block_num, block_indices in enumerate(lu_plan.blocks):
                        if i in block_indices:
                            if block_num not in _emitted_bwd3_block:
                                _emitted_bwd3_block.add(block_num)
                                block_species_names = [lu_plan.species_map[idx] for idx in block_indices]
                                f.write(f"          // Block {block_num}: K3 backward sub [{', '.join(block_species_names)}]\n")
                            break
                    s = expr_str
                    s = re.sub(r'\by_(\d+)\b', r'y3_\1', s)
                    s = re.sub(r'\bx_(\d+)\b', r'K3_\1', s)
                    f.write(f"          double K3_{i} = {s};\n")
            else:
                for i, expr_str in lu_plan.forward_sub_steps:
                    s = re.sub(r'\bb_(\d+)\b', r'rhs3_\1', expr_str)
                    s = re.sub(r'\by_(\d+)\b', r'y3_\1', s)
                    f.write(f"          double y3_{i} = {s};\n")
                for i, expr_str in lu_plan.backward_sub_steps:
                    s = expr_str
                    s = re.sub(r'\by_(\d+)\b', r'y3_\1', s)
                    s = re.sub(r'\bx_(\d+)\b', r'K3_\1', s)
                    f.write(f"          double K3_{i} = {s};\n")

            # Error Estimation (ROS-3: Yerr = E1*K1 + E2*K2 + E3*K3, L2 norm)
            f.write("\n          // 8. Error Estimation (ROS-3 embedded method, L2 norm)\n")
            f.write("          double err_norm_sq = 0.0;\n")
            for i in range(N):
                state_idx = _perm[i] if _perm else i
                f.write(f"          {{\n")
                f.write(f"              double Ynew_i = S_{i} + ros_M1 * K1_{i} + ros_M2 * K2_{i} + ros_M3 * K3_{i};\n")
                f.write(f"              double ymax = Kokkos::fmax(Kokkos::fabs(state({state_idx})), Kokkos::fabs(Ynew_i));\n")
                f.write(f"              double sci = atol[{i}] + rtol[{i}] * ymax;\n")
                f.write(f"              double yerr_i = ros_E1 * K1_{i} + ros_E2 * K2_{i} + ros_E3 * K3_{i};\n")
                f.write(f"              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);\n")
                f.write(f"          }}\n")
            f.write(f"          double err_norm = Kokkos::sqrt(err_norm_sq / {N});\n")
            f.write("          err_norm = Kokkos::fmax(err_norm, 1.0e-10);\n")

            # Step Size Control (1/ELO = 1/3 for 3rd order)
            f.write("\n          // 9. Step Size Control (3rd order: exponent = 1/3)\n")
            f.write("          double factor = safety / Kokkos::cbrt(err_norm);\n")
            f.write("          factor = Kokkos::fmax(min_shrink, Kokkos::fmin(factor, max_growth));\n\n")
            f.write("          if (err_norm <= 1.0) {\n")
            for i in range(N):
                state_idx = _perm[i] if _perm else i
                f.write(f"              state({state_idx}) += ros_M1 * K1_{i} + ros_M2 * K2_{i} + ros_M3 * K3_{i};\n")
            f.write("              t += dt;\n")
            f.write("              dt *= factor;\n")
            f.write("          } else {\n")
            f.write("              dt *= factor;\n")
            f.write("          }\n")

        # Close while loop
        f.write("          } // end while (t < dt_total)\n")
        f.write("      }\n\n")

        # 7. integrate_with_reduction (Auto-Reduction Kernel)
        f.write("      template <class StateView>\n")
        f.write("      KOKKOS_INLINE_FUNCTION void integrate_with_reduction(\n")
        f.write("          double dt_total, StateView& state, double importance_threshold) const\n")
        f.write("      {\n")
        f.write(f"          const int NUM_SPECIES = {N};\n")
        f.write("          const double g = 1.70710678118654752440;\n")
        f.write("          const double ros_A0 = 1.0 / g;\n")
        f.write("          const double ros_C0 = -2.0 / g;\n")
        f.write("          const double ros_M0 = 3.0 / (2.0 * g);\n")
        f.write("          const double ros_M1 = 1.0 / (2.0 * g);\n")
        f.write("          const double safety = 0.9;\n")
        f.write("          const double max_growth = 6.0;\n")
        f.write("          const double min_shrink = 0.2;\n\n")
        f.write("          bool active[NUM_SPECIES];\n")
        f.write("          double t = 0.0;\n")
        f.write("          double dt = dt_total;\n\n")
        f.write("          // Initialize all species as active\n")
        for i in range(N):
            f.write(f"          active[{i}] = true;\n")
        f.write("\n")
        f.write("          while (t < dt_total) {\n")
        f.write("          dt = Kokkos::min(dt, dt_total - t);\n")
        f.write("          const double inv_g_dt = 1.0 / (g * dt);\n\n")

        # Hoist state values
        f.write("          // 0. Hoist state values into scalar registers\n")
        if _perm:
            f.write("          // NOTE: State access uses permuted species ordering\n")
        for i in range(N):
            src_idx = _perm[i] if _perm else i
            f.write(f"          const double S_{i} = state({src_idx});\n")
        f.write("\n")

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

            # Importance evaluation and active/frozen classification
            f.write("\n          // 2. Evaluate importance and update active set\n")
            for i in range(N):
                state_idx = _perm[i] if _perm else i
                f.write(f"          active[{i}] = (Kokkos::fabs(F1_{i}) / (atol[{i}] + rtol[{i}] * Kokkos::fabs(state({state_idx}))) >= importance_threshold);\n")

            # Jacobian Non-Zeros with frozen species handling
            f.write("\n          // 3. Analytical Jacobian & Iteration Matrix W (identity for frozen species)\n")
            non_zero_jac_set = set()
            for i, j, expr_str in lu_plan.non_zero_jacobian:
                non_zero_jac_set.add((i, j))
                eqn = format_eqn(expr_str, mech.species, state_var="S", use_parentheses=False)
                f.write(f"          double J_{i}_{j} = {eqn};\n")

            # Emit W with conditional logic for frozen species
            for i in range(N):
                for j in range(N):
                    if i == j:
                        if (i, i) in non_zero_jac_set:
                            f.write(f"          double W_{i}_{i} = active[{i}] ? (inv_g_dt - J_{i}_{i}) : 1.0;\n")
                        else:
                            f.write(f"          double W_{i}_{i} = active[{i}] ? inv_g_dt : 1.0;\n")
                    elif (i, j) in non_zero_jac_set:
                        f.write(f"          double W_{i}_{j} = (active[{i}] && active[{j}]) ? (-J_{i}_{j}) : 0.0;\n")

            # Symbolic LU Factorization with conditional skip for frozen species
            f.write("\n          // 4. Symbolic LU Factorization (conditional skip for frozen species)\n")

            # Use annotated expressions if available for conditional skipping
            if lu_plan.annotated_expressions:
                for ann_expr in lu_plan.annotated_expressions:
                    deps = ann_expr.depends_on
                    if deps:
                        cond_parts = [f"active[{d}]" for d in sorted(deps)]
                        cond = " && ".join(cond_parts)
                        f.write(f"          double {ann_expr.kind}_{ann_expr.row}_{ann_expr.col} = ({cond}) ? ({ann_expr.expr}) : ")
                        # For U diagonal, frozen → 1.0; for off-diag → 0.0
                        if ann_expr.row == ann_expr.col:
                            f.write("1.0;\n")
                        else:
                            f.write("0.0;\n")
                    else:
                        f.write(f"          double {ann_expr.kind}_{ann_expr.row}_{ann_expr.col} = {ann_expr.expr};\n")
            else:
                # Fallback: emit without conditional skip (use normal LU)
                for kind, i, j, expr_str in lu_plan.lu_expressions_ordered:
                    f.write(f"          double {kind}_{i}_{j} = {expr_str};\n")

            # Forward & Backward Substitution for K1 with frozen species getting K1=0
            f.write("\n          // 5. Forward & Backward Substitution for K1 (frozen species get K1=0)\n")
            import re
            for i, expr_str in lu_plan.forward_sub_steps:
                s = re.sub(r'\bb_(\d+)\b', r'F1_\1', expr_str)
                s = re.sub(r'\by_(\d+)\b', r'y1_\1', s)
                f.write(f"          double y1_{i} = active[{i}] ? ({s}) : 0.0;\n")
            for i, expr_str in lu_plan.backward_sub_steps:
                s = expr_str
                s = re.sub(r'\by_(\d+)\b', r'y1_\1', s)
                s = re.sub(r'\bx_(\d+)\b', r'K1_\1', s)
                f.write(f"          double K1_{i} = active[{i}] ? ({s}) : 0.0;\n")

            # Fused Intermediate State Ynew
            f.write("\n          // 6. Fused Intermediate State Ynew\n")
            for i in range(N):
                f.write(f"          double Ynew_{i} = S_{i} + ros_A0 * K1_{i};\n")

            # Stage 2 Rates F2 & Substitution (frozen species get K2=0)
            f.write("\n          // 7. Stage 2 Rates (F2) & Substitution for K2 (frozen species get K2=0)\n")
            if sympy_meta:
                for i in range(len(F)):
                    eqn = format_eqn(F[i], mech.species, state_var="Ynew", use_parentheses=False)
                    f.write(f"          double F2_{i} = {eqn};\n")
                    f.write(f"          double rhs2_{i} = F2_{i} + (ros_C0 / dt) * K1_{i};\n")

            for i, expr_str in lu_plan.forward_sub_steps:
                s = re.sub(r'\bb_(\d+)\b', r'rhs2_\1', expr_str)
                s = re.sub(r'\by_(\d+)\b', r'y2_\1', s)
                f.write(f"          double y2_{i} = active[{i}] ? ({s}) : 0.0;\n")
            for i, expr_str in lu_plan.backward_sub_steps:
                s = expr_str
                s = re.sub(r'\by_(\d+)\b', r'y2_\1', s)
                s = re.sub(r'\bx_(\d+)\b', r'K2_\1', s)
                f.write(f"          double K2_{i} = active[{i}] ? ({s}) : 0.0;\n")

            # Error Estimation (KPP-compatible: embedded formula with L2 norm)
            f.write("\n          // 8. Error Estimation (KPP ROS-2 embedded method, L2 norm)\n")
            f.write("          const double ros_E0 = ros_M1;  // 1/(2*g)\n")
            f.write("          const double ros_E1 = ros_M1;  // 1/(2*g)\n")
            f.write("          double err_norm_sq = 0.0;\n")
            for i in range(N):
                state_idx = _perm[i] if _perm else i
                f.write(f"          {{\n")
                f.write(f"              double Ynew_i = state({state_idx}) + ros_M0 * K1_{i} + ros_M1 * K2_{i};\n")
                f.write(f"              double ymax = Kokkos::fmax(Kokkos::fabs(state({state_idx})), Kokkos::fabs(Ynew_i));\n")
                f.write(f"              double sci = atol[{i}] + rtol[{i}] * ymax;\n")
                f.write(f"              double yerr_i = ros_E0 * K1_{i} + ros_E1 * K2_{i};\n")
                f.write(f"              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);\n")
                f.write(f"          }}\n")
            f.write(f"          double err_norm = Kokkos::sqrt(err_norm_sq / {N});\n")
            f.write("          err_norm = Kokkos::fmax(err_norm, 1.0e-10);\n")

            # Step Size Control (only update active species on accept)
            f.write("\n          // 9. Step Size Control (only active species update state)\n")
            f.write("          double factor = safety / Kokkos::pow(err_norm, 0.5);\n")
            f.write("          factor = Kokkos::fmax(min_shrink, Kokkos::fmin(factor, max_growth));\n\n")
            f.write("          if (err_norm <= 1.0) {\n")
            for i in range(N):
                state_idx = _perm[i] if _perm else i
                f.write(f"              if (active[{i}]) state({state_idx}) += ros_M0 * K1_{i} + ros_M1 * K2_{i};\n")
            f.write("              t += dt;\n")
            f.write("              dt *= factor;\n")
            f.write("          } else {\n")
            f.write("              dt *= factor;\n")
            f.write("          }\n")

        # Close while loop for integrate_with_reduction
        f.write("          } // end while (t < dt_total)\n")
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
