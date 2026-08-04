import json
import hashlib
import math
from dataclasses import dataclass
from pathlib import Path
from typing import Dict, List
from .model import MechanismDefinition


# ---------------------------------------------------------------------------
# Rosenbrock Coefficient Tableau Storage
# ---------------------------------------------------------------------------

@dataclass(frozen=True)
class RosenbrockTableau:
    """Immutable coefficient tableau for a Rosenbrock solver."""
    name: str
    stages: int
    A: List[float]       # Strictly lower-triangular, row-wise: A(2,1), A(3,1), A(3,2), ...
    C: List[float]       # Same storage as A
    M: List[float]       # Solution update weights, length = stages
    E: List[float]       # Error estimate weights, length = stages
    Alpha: List[float]   # Stage time offsets, length = stages
    Gamma: List[float]   # Gamma sums, length = stages
    NewF: List[bool]     # Whether stage i needs a fresh F evaluation
    ELO: float           # Estimator of local order (main + embedded + 1)


SOLVER_COEFFICIENTS: Dict[str, RosenbrockTableau] = {
    "ros2": RosenbrockTableau(
        name="ROS-2",
        stages=2,
        A=[1.7071067811865475244],  # 1/g where g = 1 + 1/sqrt(2)
        C=[-1.1715728752538099024],  # -2/g
        M=[0.87867965644035742774, 0.29289321881345247560],  # 3/(2g), 1/(2g)
        E=[0.29289321881345247560, 0.29289321881345247560],  # 1/(2g), 1/(2g)
        Alpha=[0.0, 1.0],
        Gamma=[1.7071067811865475244, -1.7071067811865475244],  # g, -g
        NewF=[True, True],
        ELO=2.0,
    ),
    "ros3": RosenbrockTableau(
        name="ROS-3",
        stages=3,
        A=[1.0, 1.0, 0.0],
        C=[-1.0156171083877702092, 4.0759956452537699825, 9.2076794298330791242],
        M=[1.0, 6.1697947043828245593, -0.42772256543218573326],
        E=[0.5, -2.9079558716805469822, 0.22354069897811569627],
        Alpha=[0.0, 0.43586652150845899942, 0.43586652150845899942],
        Gamma=[0.43586652150845899942, 0.24291996454816804367, 2.1851380027664058512],
        NewF=[True, True, False],
        ELO=3.0,
    ),
    "ros4": RosenbrockTableau(
        name="ROS-4",
        stages=4,
        A=[2.0, 1.867943637803922, 0.2344449711399156,
           1.867943637803922, 0.2344449711399156, 0.0],
        C=[-7.137615036412310, 2.580708087951457, 0.6515950076447975,
           -2.137148994382534, -0.3214669691237626, -0.6949742501781779],
        M=[2.255570073418735, 0.2870493262186792,
           0.4353179431840180, 1.093502252409163],
        E=[-0.2815431932141155, -0.07276199124938920,
           -0.1082196201495311, -1.093502252409163],
        Alpha=[0.0, 1.145640000000000, 0.6552168638155900, 0.6552168638155900],
        Gamma=[0.5728200000000000, -1.769193891319233,
               0.7592633437920482, -0.1049021087100450],
        NewF=[True, True, True, False],
        ELO=4.0,
    ),
    "rodas3": RosenbrockTableau(
        name="RODAS-3",
        stages=4,
        A=[0.0, 2.0, 0.0, 2.0, 0.0, 1.0],
        C=[4.0, 1.0, -1.0, 1.0, -1.0, -8.0/3.0],
        M=[2.0, 0.0, 1.0, 1.0],
        E=[0.0, 0.0, 0.0, 1.0],
        Alpha=[0.0, 0.0, 1.0, 1.0],
        Gamma=[0.5, 1.5, 0.0, 0.0],
        NewF=[True, False, True, True],
        ELO=3.0,
    ),
    "rodas4": RosenbrockTableau(
        name="RODAS-4",
        stages=6,
        A=[1.544000000000000,
           0.9466785280815826, 0.2557011698983284,
           3.314825187068521, 2.896124015972201, 0.9986419139977817,
           1.221224509226641, 6.019134481288629, 12.53708332932087, -0.6878860361058950,
           1.221224509226641, 6.019134481288629, 12.53708332932087, -0.6878860361058950, 1.0],
        C=[-5.668800000000000,
           -2.430093356833875, -0.2063599157091915,
           -0.1073529058151375, -9.594562251023355, -20.47028614809616,
            7.496443313967647, -10.24680431464352, -33.99990352819905, 11.70890893206160,
            8.083246795921522, -7.981132988064893, -31.52159432874371, 16.31930543123136, -6.058818238834054],
        M=[1.221224509226641, 6.019134481288629, 12.53708332932087, -0.6878860361058950, 1.0, 1.0],
        E=[0.0, 0.0, 0.0, 0.0, 0.0, 1.0],
        Alpha=[0.0, 0.386, 0.210, 0.630, 1.0, 1.0],
        Gamma=[0.2500000000000000, -0.1043000000000000,
               0.1035000000000000, -0.03620000000000023, 0.0, 0.0],
        NewF=[True, True, True, True, True, True],
        ELO=4.0,
    ),
}


def get_A(tableau: RosenbrockTableau, i: int, j: int) -> float:
    """Get A(i,j) from row-wise lower-triangular storage. i,j are 1-indexed; i > j."""
    return tableau.A[(i - 1) * (i - 2) // 2 + j - 1]


def get_C(tableau: RosenbrockTableau, i: int, j: int) -> float:
    """Get C(i,j) from row-wise lower-triangular storage. i,j are 1-indexed; i > j."""
    return tableau.C[(i - 1) * (i - 2) // 2 + j - 1]


# Module-level assertions verifying array length invariants for each tableau
for _solver_name, _tableau in SOLVER_COEFFICIENTS.items():
    _s = _tableau.stages
    _expected_tri = _s * (_s - 1) // 2
    assert len(_tableau.A) == _expected_tri, (
        f"{_solver_name}: len(A)={len(_tableau.A)} != stages*(stages-1)//2={_expected_tri}"
    )
    assert len(_tableau.C) == _expected_tri, (
        f"{_solver_name}: len(C)={len(_tableau.C)} != stages*(stages-1)//2={_expected_tri}"
    )
    assert len(_tableau.M) == _s, (
        f"{_solver_name}: len(M)={len(_tableau.M)} != stages={_s}"
    )
    assert len(_tableau.E) == _s, (
        f"{_solver_name}: len(E)={len(_tableau.E)} != stages={_s}"
    )
    assert len(_tableau.Alpha) == _s, (
        f"{_solver_name}: len(Alpha)={len(_tableau.Alpha)} != stages={_s}"
    )
    assert len(_tableau.Gamma) == _s, (
        f"{_solver_name}: len(Gamma)={len(_tableau.Gamma)} != stages={_s}"
    )
    assert len(_tableau.NewF) == _s, (
        f"{_solver_name}: len(NewF)={len(_tableau.NewF)} != stages={_s}"
    )
# Clean up loop variables from module namespace
del _solver_name, _tableau, _s, _expected_tri


# ---------------------------------------------------------------------------
# Generic Rosenbrock stage emission
# ---------------------------------------------------------------------------


def _emit_rosenbrock_stages(
    f,
    tableau: RosenbrockTableau,
    N: int,
    lu_plan,
    sympy_meta,
    mech,
    perm,
    is_reduction: bool = False,
) -> None:
    """Emit fully-unrolled Rosenbrock stage computations for any supported solver.

    This function generalizes the existing hardcoded 3-stage Ros3 logic into a
    Python-time loop that unrolls S stages into named C++ scalar variables.
    All stage logic is fully unrolled at code-generation time — no runtime loops
    over stages exist in the emitted C++.

    Parameters
    ----------
    f : file handle
        Open file to write C++ code into.
    tableau : RosenbrockTableau
        Coefficient tableau for the selected solver.
    N : int
        Number of species.
    lu_plan : SymbolicLUPlan
        Symbolic LU factorization plan (solver-independent).
    sympy_meta : dict
        Mechanism metadata containing f_vector/f_implicit+f_explicit and jacobian_matrix.
    mech : MechanismDefinition
        Mechanism definition (for species list and format_eqn).
    perm : list or None
        Species permutation for state access (from LU plan), or None.
    is_reduction : bool
        If True, emit conditional active-species logic for auto-reduction variant.
    """
    import re

    # Resolve the ODE right-hand-side expressions
    if sympy_meta:
        if "f_implicit" in sympy_meta and "f_explicit" in sympy_meta:
            F_exprs = sympy_meta["f_implicit"] + sympy_meta["f_explicit"]
        elif "f_vector" in sympy_meta:
            F_exprs = sympy_meta["f_vector"]
        else:
            F_exprs = [0] * N
    else:
        F_exprs = [0] * N

    gamma = tableau.Gamma[0]
    S = tableau.stages

    # --- Helper: emit forward/backward substitution for a given stage ---
    def _emit_lu_solve(stage_num, rhs_prefix, y_prefix, k_prefix):
        """Emit forward and backward substitution for one stage solve.

        Maps the generic LU plan variables:
          b_i -> {rhs_prefix}_{i}
          y_i -> {y_prefix}_{i}
          x_i -> {k_prefix}_{i}
        """
        if lu_plan.blocks and len(lu_plan.blocks) > 1:
            # Forward substitution with block comments
            _emitted_fwd_block = set()
            for i, expr_str in lu_plan.forward_sub_steps:
                for block_num, block_indices in enumerate(lu_plan.blocks):
                    if i in block_indices:
                        if block_num not in _emitted_fwd_block:
                            _emitted_fwd_block.add(block_num)
                            block_species_names = [lu_plan.species_map[idx] for idx in block_indices]
                            f.write(f"          // Block {block_num}: {k_prefix} forward sub [{', '.join(block_species_names)}]\n")
                        break
                s = re.sub(r'\bb_(\d+)\b', rf'{rhs_prefix}_\1', expr_str)
                s = re.sub(r'\by_(\d+)\b', rf'{y_prefix}_\1', s)
                if is_reduction:
                    f.write(f"          double {y_prefix}_{i} = active[{i}] ? ({s}) : 0.0;\n")
                else:
                    f.write(f"          double {y_prefix}_{i} = {s};\n")
            # Backward substitution with block comments
            _emitted_bwd_block = set()
            for i, expr_str in lu_plan.backward_sub_steps:
                for block_num, block_indices in enumerate(lu_plan.blocks):
                    if i in block_indices:
                        if block_num not in _emitted_bwd_block:
                            _emitted_bwd_block.add(block_num)
                            block_species_names = [lu_plan.species_map[idx] for idx in block_indices]
                            f.write(f"          // Block {block_num}: {k_prefix} backward sub [{', '.join(block_species_names)}]\n")
                        break
                s = expr_str
                s = re.sub(r'\by_(\d+)\b', rf'{y_prefix}_\1', s)
                s = re.sub(r'\bx_(\d+)\b', rf'{k_prefix}_\1', s)
                if is_reduction:
                    f.write(f"          double {k_prefix}_{i} = active[{i}] ? ({s}) : 0.0;\n")
                else:
                    f.write(f"          double {k_prefix}_{i} = {s};\n")
        else:
            # Forward substitution (no block comments)
            for i, expr_str in lu_plan.forward_sub_steps:
                s = re.sub(r'\bb_(\d+)\b', rf'{rhs_prefix}_\1', expr_str)
                s = re.sub(r'\by_(\d+)\b', rf'{y_prefix}_\1', s)
                if is_reduction:
                    f.write(f"          double {y_prefix}_{i} = active[{i}] ? ({s}) : 0.0;\n")
                else:
                    f.write(f"          double {y_prefix}_{i} = {s};\n")
            # Backward substitution (no block comments)
            for i, expr_str in lu_plan.backward_sub_steps:
                s = expr_str
                s = re.sub(r'\by_(\d+)\b', rf'{y_prefix}_\1', s)
                s = re.sub(r'\bx_(\d+)\b', rf'{k_prefix}_\1', s)
                if is_reduction:
                    f.write(f"          double {k_prefix}_{i} = active[{i}] ? ({s}) : 0.0;\n")
                else:
                    f.write(f"          double {k_prefix}_{i} = {s};\n")

    # Track which F variable name is current (for NewF=false reuse)
    current_F_prefix = None

    # --- Stage loop (Python-time unrolling) ---
    for stage in range(1, S + 1):
        f.write(f"\n          // --- Stage {stage} ---\n")

        # 1. Compute intermediate state Y_stage if stage > 1
        if stage > 1:
            # Y_stage[i] = S_i + sum(A(stage,j) * K_j[i] for j in 1..stage-1)
            f.write(f"          // Intermediate state Y{stage}\n")
            for i in range(N):
                terms = []
                for j in range(1, stage):
                    a_val = get_A(tableau, stage, j)
                    if a_val != 0.0:
                        terms.append((a_val, f"K{j}_{i}"))
                if not terms:
                    # All A coefficients are zero — Y equals S
                    f.write(f"          double Y{stage}_{i} = S_{i};\n")
                elif len(terms) == 1 and terms[0][0] == 1.0:
                    f.write(f"          double Y{stage}_{i} = S_{i} + {terms[0][1]};\n")
                else:
                    sum_expr = " + ".join(
                        f"{a:.17g} * {kvar}" if a != 1.0 else kvar
                        for a, kvar in terms
                    )
                    f.write(f"          double Y{stage}_{i} = S_{i} + {sum_expr};\n")

        # 2. Evaluate F_stage if NewF[stage-1] is True, else reuse previous
        if tableau.NewF[stage - 1]:
            F_prefix = f"F{stage}"
            if stage == 1:
                # For stage 1, evaluate at the initial state S
                state_var = "S"
            else:
                state_var = f"Y{stage}"
            f.write(f"          // Rate evaluation F{stage} at {state_var}\n")
            for i in range(N):
                eqn = format_eqn(F_exprs[i], mech.species, state_var=state_var, use_parentheses=False)
                f.write(f"          double F{stage}_{i} = {eqn};\n")
            current_F_prefix = F_prefix
        else:
            # Reuse the previous stage's F evaluation
            f.write(f"          // NewF=false: reuse {current_F_prefix} for stage {stage}\n")
            # current_F_prefix remains unchanged

        # 3. Form RHS: rhs_stage[i] = F_current[i] + sum(C(stage,j)/dt * K_j[i] for j in 1..stage-1)
        rhs_prefix = f"rhs{stage}"
        if stage == 1:
            # For stage 1, the C sum is empty: rhs = F1
            # We use F1 directly as the RHS (no separate rhs variable needed for stage 1)
            rhs_prefix = current_F_prefix
        else:
            f.write(f"          // RHS for stage {stage}\n")
            for i in range(N):
                c_terms = []
                for j in range(1, stage):
                    c_val = get_C(tableau, stage, j)
                    if c_val != 0.0:
                        c_terms.append((c_val, f"K{j}_{i}"))
                if not c_terms:
                    f.write(f"          double rhs{stage}_{i} = {current_F_prefix}_{i};\n")
                else:
                    sum_expr = " + ".join(
                        f"({c:.17g} / dt) * {kvar}" for c, kvar in c_terms
                    )
                    f.write(f"          double rhs{stage}_{i} = {current_F_prefix}_{i} + {sum_expr};\n")

        # 4. Solve W * K_stage = rhs_stage using pre-computed LU plan
        y_prefix = f"y{stage}"
        k_prefix = f"K{stage}"
        _emit_lu_solve(stage, rhs_prefix, y_prefix, k_prefix)

    # --- After all stages: Solution update and error estimation ---
    f.write(f"\n          // --- Solution update and error estimation ---\n")

    # Compute error norm (fused with solution update for cache efficiency)
    f.write("          double err_norm_sq = 0.0;\n")
    for i in range(N):
        state_idx = perm[i] if perm else i
        # Solution update: Ynew[i] = S_i + sum(M[j] * K_{j+1}[i] for j in range(stages))
        m_terms = []
        for j in range(S):
            if tableau.M[j] != 0.0:
                m_terms.append((tableau.M[j], f"K{j+1}_{i}"))
        if m_terms:
            m_expr = " + ".join(
                f"{m:.17g} * {kvar}" if m != 1.0 else kvar
                for m, kvar in m_terms
            )
        else:
            m_expr = "0.0"

        # Error estimate: Yerr[i] = sum(E[j] * K_{j+1}[i] for j in range(stages))
        e_terms = []
        for j in range(S):
            if tableau.E[j] != 0.0:
                e_terms.append((tableau.E[j], f"K{j+1}_{i}"))
        if e_terms:
            e_expr = " + ".join(
                f"{e:.17g} * {kvar}" if e != 1.0 else kvar
                for e, kvar in e_terms
            )
        else:
            e_expr = "0.0"

        f.write(f"          {{\n")
        f.write(f"              double Ynew_i = S_{i} + {m_expr};\n")
        f.write(f"              double ymax = Kokkos::fmax(Kokkos::fabs(state({state_idx})), Kokkos::fabs(Ynew_i));\n")
        f.write(f"              double sci = atol[{i}] + rtol[{i}] * ymax;\n")
        f.write(f"              double yerr_i = {e_expr};\n")
        f.write(f"              err_norm_sq += (yerr_i / sci) * (yerr_i / sci);\n")
        f.write(f"          }}\n")

    f.write(f"          double err_norm = Kokkos::sqrt(err_norm_sq / {N});\n")
    f.write("          err_norm = Kokkos::fmax(err_norm, 1.0e-10);\n")

    # Step-size control with 1/ELO exponent as a literal
    elo_exponent = 1.0 / tableau.ELO
    f.write(f"\n          // Step Size Control (order {tableau.ELO:.0f}: exponent = 1/{tableau.ELO:.0f} = {elo_exponent:.17g})\n")
    # Use specialized functions for common exponents
    if tableau.ELO == 2.0:
        f.write("          double factor = safety / Kokkos::sqrt(err_norm);\n")
    elif tableau.ELO == 3.0:
        f.write("          double factor = safety / Kokkos::cbrt(err_norm);\n")
    else:
        f.write(f"          double factor = safety * Kokkos::pow(err_norm, -{elo_exponent:.17g});\n")
    f.write("          factor = Kokkos::fmax(min_shrink, Kokkos::fmin(factor, max_growth));\n\n")

    # Accept/reject logic
    f.write("          if (err_norm <= 1.0) {\n")
    for i in range(N):
        state_idx = perm[i] if perm else i
        # Recompute update terms for state assignment
        m_terms = []
        for j in range(S):
            if tableau.M[j] != 0.0:
                m_terms.append((tableau.M[j], f"K{j+1}_{i}"))
        if m_terms:
            m_expr = " + ".join(
                f"{m:.17g} * {kvar}" if m != 1.0 else kvar
                for m, kvar in m_terms
            )
        else:
            m_expr = "0.0"

        if is_reduction:
            f.write(f"              if (active[{i}]) state({state_idx}) += {m_expr};\n")
        else:
            f.write(f"              state({state_idx}) += {m_expr};\n")
    f.write("              t += dt;\n")
    f.write("              dt *= factor;\n")
    f.write("          } else {\n")
    f.write("              dt *= factor;\n")
    f.write("          }\n")


# ---------------------------------------------------------------------------
# Code generation utilities
# ---------------------------------------------------------------------------


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
            # NOTE: SUN is NOT substituted — photolysis rates are runtime J-values from Cloud-J
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

    # 4. Map J_<idx> photolysis symbols to the jvals array (Cloud-J runtime input)
    s = re.sub(r'\bJ_(\d+)\b', r'jvals[\1]', s)

    s = _strength_reduce_squares(s)

    return s

def generate_headers(
    mech: MechanismDefinition,
    out_dir: str = "src/solvers",
    suffix: str = "",
    solver_name: str = "ros3",
) -> Dict[str, str]:
    """Emit the Kokkos headers and manifest artifact."""
    if not mech or not mech.species:
        raise ValueError("Cannot generate headers for empty mechanism")

    # Look up the coefficient tableau for the selected solver
    tableau = SOLVER_COEFFICIENTS[solver_name]

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
        f.write("      KOKKOS_INLINE_FUNCTION void compute_rates(const StateView& state, RateView& F_block, const double* jvals) const {\n")
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
        f.write("      KOKKOS_INLINE_FUNCTION void compute_jacobian(const StateView& state, JacView& J_block, const double* jvals) const {\n")
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
        f.write("      KOKKOS_INLINE_FUNCTION void compute_adjoint(const StateView& state, JacView& J_adj_block, const double* jvals) const {\n")
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
        f.write("      KOKKOS_INLINE_FUNCTION void compute_tlm(const StateView& state, const DeltaView& delta_C, RateView& dF_block, const double* jvals) const {\n")
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

        # Photolysis metadata (Cloud-J input mapping)
        num_photolysis = 0
        photolysis_reactions_meta = []
        if sympy_meta:
            num_photolysis = sympy_meta.get("photolysis_count", 0)
            photolysis_reactions_meta = sympy_meta.get("photolysis_reactions", [])

        if num_photolysis > 0:
            f.write(f"      // Photolysis reactions (Cloud-J input mapping):\n")
            for pr in photolysis_reactions_meta:
                reactants_str = ", ".join(f"{k}" for k in (pr["reactants"].keys() if isinstance(pr["reactants"], dict) else pr["reactants"]))
                products_str = ", ".join(f"{k}" for k in (pr["products"].keys() if isinstance(pr["products"], dict) else pr["products"]))
                f.write(f"      //   jvals[{pr['photo_idx']}] = {reactants_str} -> {products_str}  (original A: {pr['original_A']})\n")
            f.write(f"      static constexpr int NUM_PHOTOLYSIS = {num_photolysis};\n\n")

        # 6. integrate (AOT Symbolic LU, ROS-3: 3-stage, 3rd order, L-stable, Sandu & Sander 2006)
        f.write("      template <class StateView>\n")
        f.write("      KOKKOS_INLINE_FUNCTION void integrate(double dt_total, StateView& state, const double* jvals) const {\n")
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
        f.write("          double dt = Kokkos::fmin(dt_total, 1.0);  // conservative initial step\n\n")
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
            f.write("\n          // 2. Analytical Jacobian & Iteration Matrix W = inv_g_dt*I - J (sparse)\n")
            non_zero_jac_set = set()
            for i, j, expr_str in lu_plan.non_zero_jacobian:
                non_zero_jac_set.add((i, j))
                eqn = format_eqn(expr_str, mech.species, state_var="S", use_parentheses=False)
                f.write(f"          double J_{i}_{j} = {eqn};\n")

            # Determine which W entries are actually needed by the LU plan
            import re as _re_w
            needed_w = set()
            for _i in range(N):
                needed_w.add((_i, _i))  # Diagonal always needed
            for _kind, _i, _j, _expr_str in lu_plan.lu_expressions_ordered:
                for _m in _re_w.finditer(r'W_(\d+)_(\d+)', _expr_str):
                    needed_w.add((int(_m.group(1)), int(_m.group(2))))

            for i, j in sorted(needed_w):
                if i == j:
                    if (i, i) in non_zero_jac_set:
                        f.write(f"          double W_{i}_{i} = inv_g_dt - J_{i}_{i};\n")
                    else:
                        f.write(f"          double W_{i}_{i} = inv_g_dt;\n")
                elif (i, j) in non_zero_jac_set:
                    f.write(f"          double W_{i}_{j} = -J_{i}_{j};\n")
                else:
                    # Fill-in dependency: W referenced by LU but no Jacobian entry
                    f.write(f"          double W_{i}_{j} = 0.0;\n")

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
        f.write("          double dt_total, StateView& state, const double* jvals, double importance_threshold) const\n")
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
        f.write("          double dt = Kokkos::fmin(dt_total, 1.0);  // conservative initial step\n\n")
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

            # Emit W with conditional logic for frozen species (sparse: only needed entries)
            import re as _re_w
            needed_w2 = set()
            for _i in range(N):
                needed_w2.add((_i, _i))  # Diagonal always needed
            # Gather W references from LU expressions (annotated or plain)
            if lu_plan.annotated_expressions:
                for ann_expr in lu_plan.annotated_expressions:
                    for _m in _re_w.finditer(r'W_(\d+)_(\d+)', ann_expr.expr):
                        needed_w2.add((int(_m.group(1)), int(_m.group(2))))
            else:
                for _kind, _i, _j, _expr_str in lu_plan.lu_expressions_ordered:
                    for _m in _re_w.finditer(r'W_(\d+)_(\d+)', _expr_str):
                        needed_w2.add((int(_m.group(1)), int(_m.group(2))))

            for i, j in sorted(needed_w2):
                if i == j:
                    if (i, i) in non_zero_jac_set:
                        f.write(f"          double W_{i}_{i} = active[{i}] ? (inv_g_dt - J_{i}_{i}) : 1.0;\n")
                    else:
                        f.write(f"          double W_{i}_{i} = active[{i}] ? inv_g_dt : 1.0;\n")
                elif (i, j) in non_zero_jac_set:
                    f.write(f"          double W_{i}_{j} = (active[{i}] && active[{j}]) ? (-J_{i}_{j}) : 0.0;\n")
                else:
                    # Fill-in dependency: W referenced by LU but no Jacobian entry
                    f.write(f"          double W_{i}_{j} = 0.0;\n")

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
