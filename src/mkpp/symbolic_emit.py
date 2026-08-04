"""Symbolic Rosenbrock stage emission for AOT C++ code generation.

Emits fully-unrolled Rosenbrock stage computations as C++ scalar code.
All stage logic is unrolled at Python (code-generation) time — no runtime
loops over stages exist in the emitted C++.
"""

import re

from .rosenbrock import RosenbrockTableau, get_A, get_C
from .format_eqn import format_eqn


def _emit_rosenbrock_adjoint_stages(f, tableau, N, lu_plan, sympy_meta, mech, perm):
    """Emit fully-unrolled Rosenbrock discrete adjoint stage computations.

    Emits a runtime backward loop over checkpointed steps, with the adjoint
    stage computations (i = s, s-1, ..., 1) fully unrolled at Python/code-gen
    time. Each adjoint stage variable u_i_k becomes a named C++ scalar.

    The discrete adjoint formula (Sandu et al., 2003):
      For each accepted step (backward):
        u_s = λ_{n+1}
        For i = s, s-1, ..., 1:
          v_i = M_i * u_s + Σ_{j=i+1}^{s} [ A_{j,i} * J^T * u_j + C_{j,i}/h * u_j ]
          u_i = W^{-T} * v_i
        λ_n = λ_{n+1} + Σ_{i=1}^{s} u_i

    Parameters
    ----------
    f : file handle
        Open file to write C++ code into.
    tableau : RosenbrockTableau
        Coefficient tableau for the selected solver.
    N : int
        Number of species.
    lu_plan : SymbolicLUPlan
        Symbolic LU factorization plan (with transposed steps populated).
    sympy_meta : dict
        Mechanism metadata containing jacobian_matrix.
    mech : MechanismDefinition
        Mechanism definition (for species list and format_eqn).
    perm : list or None
        Species permutation for state access (from LU plan), or None.

    Requirements: 2.1, 2.2, 2.3, 2.4
    """
    gamma = tableau.Gamma[0]
    S = tableau.stages

    # --- Runtime backward loop over checkpointed steps ---
    f.write("\n          // --- Discrete Adjoint: backward integration over checkpointed steps ---\n")
    f.write("          for (int step = chk.num_steps - 1; step >= 0; step--) {\n")

    # Load step size from checkpoint
    f.write("              const double h = chk.h[step];\n")
    f.write("              const double inv_g_h = 1.0 / (g * h);\n\n")

    # Reload state from checkpoint into scalars for Jacobian computation
    f.write("              // Reload checkpointed state\n")
    for i in range(N):
        f.write(f"              const double S_{i} = chk.state[step][{i}];\n")
    f.write("\n")

    # Compute Jacobian at saved state using the analytical expressions
    # We emit the Jacobian entries inline (same as forward, but operating on saved state)
    f.write("              // Recompute Jacobian at checkpointed state (recompute-J strategy, D1)\n")
    non_zero_jac_set = set()
    for i, j, expr_str in lu_plan.non_zero_jacobian:
        non_zero_jac_set.add((i, j))
        eqn = format_eqn(expr_str, mech.species, state_var="S", use_parentheses=False)
        f.write(f"              double J_{i}_{j} = {eqn};\n")

    # Form W = (1/(gamma*h))*I - J (sparse)
    f.write("\n              // Form iteration matrix W = (1/(gamma*h))*I - J\n")
    needed_w = set()
    for _i in range(N):
        needed_w.add((_i, _i))  # Diagonal always needed
    for _kind, _i, _j, _expr_str in lu_plan.lu_expressions_ordered:
        for _m in re.finditer(r'W_(\d+)_(\d+)', _expr_str):
            needed_w.add((int(_m.group(1)), int(_m.group(2))))

    for i, j in sorted(needed_w):
        if i == j:
            if (i, i) in non_zero_jac_set:
                f.write(f"              double W_{i}_{i} = inv_g_h - J_{i}_{i};\n")
            else:
                f.write(f"              double W_{i}_{i} = inv_g_h;\n")
        elif (i, j) in non_zero_jac_set:
            f.write(f"              double W_{i}_{j} = -J_{i}_{j};\n")
        else:
            f.write(f"              double W_{i}_{j} = 0.0;\n")

    # Symbolic LU factorization (same as forward, recomputed at each step)
    f.write("\n              // Symbolic LU Factorization (recomputed at each adjoint step)\n")
    if lu_plan.blocks and len(lu_plan.blocks) > 1:
        _emitted_block_header = set()
        for kind, i, j, expr_str in lu_plan.lu_expressions_ordered:
            for block_num, block_indices in enumerate(lu_plan.blocks):
                if i in block_indices:
                    if block_num not in _emitted_block_header:
                        _emitted_block_header.add(block_num)
                        block_species_names = [lu_plan.species_map[idx] for idx in block_indices]
                        f.write(f"              // Block {block_num}: species [{', '.join(block_species_names)}]\n")
                    break
            f.write(f"              double {kind}_{i}_{j} = {expr_str};\n")
    else:
        for kind, i, j, expr_str in lu_plan.lu_expressions_ordered:
            f.write(f"              double {kind}_{i}_{j} = {expr_str};\n")

    # --- Unroll adjoint stages at Python time ---
    # Discrete adjoint formula (Sandu et al.):
    #   lam = lambda_{n+1} (driving vector, constant for this step)
    #   For i = s, s-1, ..., 1:
    #     v_i_k = M[i-1] * lam_k + Σ_{j=i+1}^{s} [ A(j,i) * (J^T * u_j)_k + C(j,i)/h * u_j_k ]
    #     u_i = W^{-T} * v_i
    #   lambda_n = lambda_{n+1} + Σ_{i=1}^{s} u_i_k
    f.write(f"\n              // --- Adjoint stage unrolling (s={S} stages, backward) ---\n")
    f.write("              // Driving vector: lam_k = lambda_{n+1} (constant for this step)\n")
    for k in range(N):
        f.write(f"              const double lam_{k} = lambda({k});\n")

    # Build set of non-zero Jacobian positions for sparse J^T * vector
    non_zero_jac_entries = set()
    for i, j, _expr in lu_plan.non_zero_jacobian:
        non_zero_jac_entries.add((i, j))

    # Unroll stages i = s, s-1, ..., 1
    for stage in range(S, 0, -1):
        f.write(f"\n              // Adjoint stage {stage}\n")

        # Compute v{stage}_k = M[stage-1] * lam_k
        #   + Σ_{j=stage+1}^{S} [ A(j,stage) * (J^T * u_j)_k + C(j,stage)/h * u_j_k ]
        f.write(f"              // v{stage}: RHS for W^{{-T}} solve\n")
        m_val = tableau.M[stage - 1]

        for k in range(N):
            terms = []
            # M_i * lam_k term
            if m_val != 0.0:
                if m_val == 1.0:
                    terms.append(f"lam_{k}")
                else:
                    terms.append(f"{m_val:.17g} * lam_{k}")

            # Sum over j > i (previously solved stages)
            for j in range(stage + 1, S + 1):
                # A(j, stage) * (J^T * u_j)_k
                # (J^T * u_j)_k = Σ_col J[col, k] * u_j_col = Σ_col J_col_k * u_j_col
                # i.e., column k of J transposed = row k of J^T = column k of J
                # Actually J^T[k, col] = J[col, k]
                # So (J^T * u_j)_k = Σ_col J^T[k,col] * u_j_col = Σ_col J[col,k] * u_j_col
                a_val = get_A(tableau, j, stage)  # A(j, i) where j > i=stage
                c_val = get_C(tableau, j, stage)  # C(j, i) where j > i=stage

                if a_val != 0.0:
                    # (J^T * u_j)_k = Σ_col J[col,k] * u_j_col (sparse)
                    jt_terms = []
                    for col in range(N):
                        if (col, k) in non_zero_jac_entries:  # J[col, k] exists
                            jt_terms.append(f"J_{col}_{k} * u{j}_{col}")
                    if jt_terms:
                        jt_expr = " + ".join(jt_terms)
                        if a_val == 1.0:
                            terms.append(f"({jt_expr})")
                        else:
                            terms.append(f"{a_val:.17g} * ({jt_expr})")

                if c_val != 0.0:
                    # C(j,i)/h * u_j_k
                    terms.append(f"({c_val:.17g} / h) * u{j}_{k}")

            if terms:
                v_expr = " + ".join(terms)
            else:
                v_expr = "0.0"
            f.write(f"              double v{stage}_{k} = {v_expr};\n")

        # Solve W^{-T} * u_stage = v_stage using transposed LU
        f.write(f"              // W^{{-T}} solve for u{stage}\n")
        _emit_lu_solve_transpose(
            f, lu_plan,
            rhs_prefix=f"v{stage}",
            y_prefix=f"yt{stage}",
            k_prefix=f"u{stage}",
            indent="              ",
        )

    # --- After all stages: accumulate lambda update ---
    # λ_n = λ_{n+1} + Σ_{i=1}^{s} u_i_k
    f.write(f"\n              // --- Lambda update: lambda_n = lambda_{{n+1}} + Σ u_i ---\n")
    for k in range(N):
        u_terms = [f"u{i}_{k}" for i in range(1, S + 1)]
        u_sum = " + ".join(u_terms)
        f.write(f"              lambda({k}) = lam_{k} + {u_sum};\n")

    # Close the runtime loop over checkpoint steps
    f.write("          } // end for (step)\n")


def _emit_lu_solve_transpose(
    f,
    lu_plan,
    rhs_prefix: str,
    y_prefix: str,
    k_prefix: str,
    indent: str = "          ",
    is_reduction: bool = False,
) -> None:
    """Emit transposed forward and backward substitution for W^{-T} solve.

    Mirrors _emit_lu_solve() but uses the transposed substitution steps
    (lu_plan.transpose_forward_sub_steps and lu_plan.transpose_backward_sub_steps)
    which solve U^T * y = b followed by L^T * x = y (i.e., W^T * x = b).

    Maps the generic LU plan variables:
      b_i -> {rhs_prefix}_{i}
      y_i -> {y_prefix}_{i}
      x_i -> {k_prefix}_{i}

    Parameters
    ----------
    f : file handle
        Open file to write C++ code into.
    lu_plan : SymbolicLUPlan
        Symbolic LU factorization plan with transposed steps populated.
    rhs_prefix : str
        Variable prefix for right-hand-side vector (replaces b_i).
    y_prefix : str
        Variable prefix for intermediate vector (replaces y_i).
    k_prefix : str
        Variable prefix for solution vector (replaces x_i).
    indent : str
        Indentation string for emitted lines.
    is_reduction : bool
        If True, emit conditional active-species logic for auto-reduction variant.

    Requirements: 2.3, 5.2
    """
    if lu_plan.blocks and len(lu_plan.blocks) > 1:
        # Forward substitution (U^T * y = b) with block comments
        _emitted_fwd_block = set()
        for i, expr_str in lu_plan.transpose_forward_sub_steps:
            for block_num, block_indices in enumerate(lu_plan.blocks):
                if i in block_indices:
                    if block_num not in _emitted_fwd_block:
                        _emitted_fwd_block.add(block_num)
                        block_species_names = [lu_plan.species_map[idx] for idx in block_indices]
                        f.write(f"{indent}// Block {block_num}: {k_prefix} transpose forward sub [{', '.join(block_species_names)}]\n")
                    break
            s = re.sub(r'\bb_(\d+)\b', rf'{rhs_prefix}_\1', expr_str)
            s = re.sub(r'\by_(\d+)\b', rf'{y_prefix}_\1', s)
            if is_reduction:
                f.write(f"{indent}double {y_prefix}_{i} = active[{i}] ? ({s}) : 0.0;\n")
            else:
                f.write(f"{indent}double {y_prefix}_{i} = {s};\n")
        # Backward substitution (L^T * x = y) with block comments
        _emitted_bwd_block = set()
        for i, expr_str in lu_plan.transpose_backward_sub_steps:
            for block_num, block_indices in enumerate(lu_plan.blocks):
                if i in block_indices:
                    if block_num not in _emitted_bwd_block:
                        _emitted_bwd_block.add(block_num)
                        block_species_names = [lu_plan.species_map[idx] for idx in block_indices]
                        f.write(f"{indent}// Block {block_num}: {k_prefix} transpose backward sub [{', '.join(block_species_names)}]\n")
                    break
            s = expr_str
            s = re.sub(r'\by_(\d+)\b', rf'{y_prefix}_\1', s)
            s = re.sub(r'\bx_(\d+)\b', rf'{k_prefix}_\1', s)
            if is_reduction:
                f.write(f"{indent}double {k_prefix}_{i} = active[{i}] ? ({s}) : 0.0;\n")
            else:
                f.write(f"{indent}double {k_prefix}_{i} = {s};\n")
    else:
        # Forward substitution (U^T * y = b) — no block comments
        for i, expr_str in lu_plan.transpose_forward_sub_steps:
            s = re.sub(r'\bb_(\d+)\b', rf'{rhs_prefix}_\1', expr_str)
            s = re.sub(r'\by_(\d+)\b', rf'{y_prefix}_\1', s)
            if is_reduction:
                f.write(f"{indent}double {y_prefix}_{i} = active[{i}] ? ({s}) : 0.0;\n")
            else:
                f.write(f"{indent}double {y_prefix}_{i} = {s};\n")
        # Backward substitution (L^T * x = y) — no block comments
        for i, expr_str in lu_plan.transpose_backward_sub_steps:
            s = expr_str
            s = re.sub(r'\by_(\d+)\b', rf'{y_prefix}_\1', s)
            s = re.sub(r'\bx_(\d+)\b', rf'{k_prefix}_\1', s)
            if is_reduction:
                f.write(f"{indent}double {k_prefix}_{i} = active[{i}] ? ({s}) : 0.0;\n")
            else:
                f.write(f"{indent}double {k_prefix}_{i} = {s};\n")


def _emit_rosenbrock_stages(
    f,
    tableau: RosenbrockTableau,
    N: int,
    lu_plan,
    sympy_meta,
    mech,
    perm,
    is_reduction: bool = False,
    skip_first_f_eval: bool = False,
    checkpoint: bool = False,
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
    skip_first_f_eval : bool
        If True, skip F1 evaluation at stage 1 (assumes F1_i variables are already
        declared in scope, e.g. for integrate_with_reduction where F1 is computed
        in the preamble for importance evaluation).
    checkpoint : bool
        If True, emit checkpoint save logic after each accepted step (save h and
        state into CheckpointBuffer). Used by integrate_fwd_checkpoint().
    """

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
            if stage == 1 and skip_first_f_eval:
                # F1 already declared in the preamble (e.g. for importance evaluation)
                f.write(f"          // F1 already computed above (used for importance evaluation)\n")
            elif stage == 1:
                # For stage 1, evaluate at the initial state S
                state_var = "S"
                f.write(f"          // Rate evaluation F{stage} at {state_var}\n")
                for i in range(N):
                    eqn = format_eqn(F_exprs[i], mech.species, state_var=state_var, use_parentheses=False)
                    f.write(f"          double F{stage}_{i} = {eqn};\n")
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
    # Checkpoint save: store h and current state into checkpoint buffer
    if checkpoint:
        f.write("              // Save checkpoint data for adjoint/TLM\n")
        f.write("              if (chk.num_steps >= CheckpointBuffer::MAX_STEPS) {\n")
        f.write("                  ierr = 1;  // Exceeded MAX_STEPS budget\n")
        f.write("                  return -1;\n")
        f.write("              }\n")
        f.write("              chk.h[chk.num_steps] = dt;\n")
        for i in range(N):
            state_idx = perm[i] if perm else i
            f.write(f"              chk.state[chk.num_steps][{i}] = state({state_idx});\n")
        f.write("              chk.num_steps++;\n")
    f.write("              t += dt;\n")
    f.write("              dt *= factor;\n")
    f.write("          } else {\n")
    f.write("              dt *= factor;\n")
    f.write("          }\n")


def _emit_rosenbrock_tlm_stages(
    f,
    tableau: RosenbrockTableau,
    N: int,
    lu_plan,
    sympy_meta,
    mech,
    perm,
) -> None:
    """Emit the TLM (Tangent Linear Model) forward propagation through checkpointed steps.

    Emits a runtime loop over checkpointed forward steps. At each step:
      1. Load h and state from checkpoint buffer
      2. Call compute_jacobian() on the saved state to get J values
      3. Form W = (1/(gamma*h))*I - J and emit symbolic LU factorization
      4. Unroll TLM stages i = 1, ..., s at code-gen time:
         - RHS_i = J * (δC + Σ_{j<i} A_{i,j} * δK_j) + Σ_{j<i} C_{i,j}/h * δK_j
         - Solve W * δK_i = RHS_i using non-transposed LU
      5. After all stages: δC += Σ M_i * δK_i

    The per-species arithmetic within each stage is unrolled at Python time (no runtime
    species loops); only the checkpoint-step loop is a runtime loop.

    Parameters
    ----------
    f : file handle
        Open file to write C++ code into.
    tableau : RosenbrockTableau
        Coefficient tableau for the selected solver.
    N : int
        Number of species.
    lu_plan : SymbolicLUPlan
        Symbolic LU factorization plan.
    sympy_meta : dict
        Mechanism metadata (unused here — J is recomputed at runtime via compute_jacobian).
    mech : MechanismDefinition
        Mechanism definition (for species list).
    perm : list or None
        Species permutation for state access (from LU plan), or None.

    Requirements: 3.1, 3.2, 3.3
    """
    gamma = tableau.Gamma[0]
    S = tableau.stages

    # Build set of non-zero Jacobian entries for sparse J*vector product
    non_zero_jac_entries = {}  # (i, j) -> True, for sparse J*vector
    for i, j, _expr_str in lu_plan.non_zero_jacobian:
        non_zero_jac_entries[(i, j)] = True

    # Determine which W entries are needed by the LU plan
    needed_w = set()
    for _i in range(N):
        needed_w.add((_i, _i))  # Diagonal always needed
    for _kind, _i, _j, _expr_str in lu_plan.lu_expressions_ordered:
        for _m in re.finditer(r'W_(\d+)_(\d+)', _expr_str):
            needed_w.add((int(_m.group(1)), int(_m.group(2))))

    # --- Runtime loop over checkpointed steps (forward direction) ---
    f.write("\n          // === TLM Forward Propagation ===\n")
    f.write("          for (int step = 0; step < chk.num_steps; step++) {\n")
    f.write("              const double h = chk.h[step];\n")
    f.write("              const double inv_g_h = 1.0 / ({:.17g} * h);\n".format(gamma))
    f.write("\n")

    # Load saved state into local scalars (same S_k naming as forward solver)
    f.write("              // Reload checkpointed state\n")
    for i in range(N):
        f.write(f"              const double S_{i} = chk.state[step][{i}];\n")
    f.write("\n")

    # Compute Jacobian at the checkpointed state inline using format_eqn.
    # Uses the same pattern as the adjoint function: evaluate J from saved state S_k.
    f.write("              // Recompute Jacobian at checkpointed state (recompute-J strategy, D1)\n")
    for i, j, expr_str in lu_plan.non_zero_jacobian:
        if mech is not None and hasattr(mech, 'species') and mech.species:
            jac_expr = format_eqn(expr_str, mech.species, state_var="S", use_parentheses=False)
        else:
            # Fallback for testing: expressions are already in S_k format
            jac_expr = expr_str
        f.write(f"              double J_{i}_{j} = {jac_expr};\n")
    f.write("\n")

    # Form W = (1/(gamma*h))*I - J (sparse)
    f.write("              // Form iteration matrix W = inv_g_h*I - J\n")
    non_zero_jac_set = set((i, j) for i, j, _ in lu_plan.non_zero_jacobian)
    for i, j in sorted(needed_w):
        if i == j:
            if (i, i) in non_zero_jac_set:
                f.write(f"              double W_{i}_{i} = inv_g_h - J_{i}_{i};\n")
            else:
                f.write(f"              double W_{i}_{i} = inv_g_h;\n")
        elif (i, j) in non_zero_jac_set:
            f.write(f"              double W_{i}_{j} = -J_{i}_{j};\n")
        else:
            f.write(f"              double W_{i}_{j} = 0.0;\n")
    f.write("\n")

    # Emit symbolic LU factorization (same as forward solver)
    f.write("              // Symbolic LU Factorization\n")
    if lu_plan.blocks and len(lu_plan.blocks) > 1:
        _emitted_block_header = set()
        for kind, i, j, expr_str in lu_plan.lu_expressions_ordered:
            for block_num, block_indices in enumerate(lu_plan.blocks):
                if i in block_indices:
                    if block_num not in _emitted_block_header:
                        _emitted_block_header.add(block_num)
                        block_species_names = [lu_plan.species_map[idx] for idx in block_indices]
                        f.write(f"              // Block {block_num}: [{', '.join(block_species_names)}]\n")
                    break
            f.write(f"              double {kind}_{i}_{j} = {expr_str};\n")
    else:
        for kind, i, j, expr_str in lu_plan.lu_expressions_ordered:
            f.write(f"              double {kind}_{i}_{j} = {expr_str};\n")
    f.write("\n")

    # --- TLM Stage Unrolling (Python-time) ---
    # For each stage i = 1, ..., s:
    #   RHS_i_k = [J * (δC + Σ_{j<i} A_{i,j} * δK_j)]_k + Σ_{j<i} C_{i,j}/h * δK_j_k
    #   Solve: W * δK_i = RHS_i
    for stage in range(1, S + 1):
        f.write(f"\n              // --- TLM Stage {stage} ---\n")

        # Build the argument to J*(...): arg_k = δC_k + Σ_{j<i} A_{i,j} * δK_j_k
        # Then form RHS_k = Σ_col J_{k,col} * arg_col + Σ_{j<i} C_{i,j}/h * δK_j_k
        f.write(f"              // RHS: J*(δC + Σ A_{{i,j}}*δK_j) + Σ C_{{i,j}}/h*δK_j\n")

        if stage == 1:
            # No previous stages: arg = δC, no C-sum
            # RHS_k = Σ_col J_{k,col} * δC_col  (sparse J*δC)
            for k in range(N):
                # Compute J[k,:] * δC (sparse)
                j_terms = []
                for col in range(N):
                    if (k, col) in non_zero_jac_entries:
                        j_terms.append(f"J_{k}_{col} * dC_{col}")
                if j_terms:
                    rhs_expr = " + ".join(j_terms)
                else:
                    rhs_expr = "0.0"
                f.write(f"              double tlm_rhs{stage}_{k} = {rhs_expr};\n")
        else:
            # General case: arg_col = δC_col + Σ_{j<i} A_{i,j} * δK_j_col
            # First compute the argument vector inline, then J*arg + C-sum
            # To avoid N extra temporaries, we fuse J*arg + C-sum directly into RHS
            for k in range(N):
                terms = []

                # J[k,:] * (δC + Σ A_{i,j} * δK_j) — expand inline
                for col in range(N):
                    if (k, col) in non_zero_jac_entries:
                        # J_{k,col} * (δC_col + Σ_{j<i} A_{i,j} * δK_j_col)
                        inner_parts = [f"dC_{col}"]
                        for j in range(1, stage):
                            a_val = get_A(tableau, stage, j)
                            if a_val != 0.0:
                                if a_val == 1.0:
                                    inner_parts.append(f"dK{j}_{col}")
                                else:
                                    inner_parts.append(f"{a_val:.17g} * dK{j}_{col}")
                        inner_expr = " + ".join(inner_parts)
                        if len(inner_parts) == 1:
                            terms.append(f"J_{k}_{col} * {inner_expr}")
                        else:
                            terms.append(f"J_{k}_{col} * ({inner_expr})")

                # Σ_{j<i} C_{i,j}/h * δK_j_k
                for j in range(1, stage):
                    c_val = get_C(tableau, stage, j)
                    if c_val != 0.0:
                        terms.append(f"({c_val:.17g} / h) * dK{j}_{k}")

                if terms:
                    rhs_expr = " + ".join(terms)
                else:
                    rhs_expr = "0.0"
                f.write(f"              double tlm_rhs{stage}_{k} = {rhs_expr};\n")

        # Solve W * δK_i = RHS using non-transposed LU solve
        # Use the same pattern as _emit_lu_solve in the forward solver
        rhs_prefix = f"tlm_rhs{stage}"
        y_prefix = f"tlm_y{stage}"
        k_prefix = f"dK{stage}"

        f.write(f"              // Solve W * dK{stage} = tlm_rhs{stage}\n")
        if lu_plan.blocks and len(lu_plan.blocks) > 1:
            # Forward substitution with block comments
            _emitted_fwd_block = set()
            for i, expr_str in lu_plan.forward_sub_steps:
                for block_num, block_indices in enumerate(lu_plan.blocks):
                    if i in block_indices:
                        if block_num not in _emitted_fwd_block:
                            _emitted_fwd_block.add(block_num)
                            block_species_names = [lu_plan.species_map[idx] for idx in block_indices]
                            f.write(f"              // Block {block_num}: {k_prefix} forward sub [{', '.join(block_species_names)}]\n")
                        break
                s = re.sub(r'\bb_(\d+)\b', rf'{rhs_prefix}_\1', expr_str)
                s = re.sub(r'\by_(\d+)\b', rf'{y_prefix}_\1', s)
                f.write(f"              double {y_prefix}_{i} = {s};\n")
            # Backward substitution with block comments
            _emitted_bwd_block = set()
            for i, expr_str in lu_plan.backward_sub_steps:
                for block_num, block_indices in enumerate(lu_plan.blocks):
                    if i in block_indices:
                        if block_num not in _emitted_bwd_block:
                            _emitted_bwd_block.add(block_num)
                            block_species_names = [lu_plan.species_map[idx] for idx in block_indices]
                            f.write(f"              // Block {block_num}: {k_prefix} backward sub [{', '.join(block_species_names)}]\n")
                        break
                s = expr_str
                s = re.sub(r'\by_(\d+)\b', rf'{y_prefix}_\1', s)
                s = re.sub(r'\bx_(\d+)\b', rf'{k_prefix}_\1', s)
                f.write(f"              double {k_prefix}_{i} = {s};\n")
        else:
            # Forward substitution (no block comments)
            for i, expr_str in lu_plan.forward_sub_steps:
                s = re.sub(r'\bb_(\d+)\b', rf'{rhs_prefix}_\1', expr_str)
                s = re.sub(r'\by_(\d+)\b', rf'{y_prefix}_\1', s)
                f.write(f"              double {y_prefix}_{i} = {s};\n")
            # Backward substitution (no block comments)
            for i, expr_str in lu_plan.backward_sub_steps:
                s = expr_str
                s = re.sub(r'\by_(\d+)\b', rf'{y_prefix}_\1', s)
                s = re.sub(r'\bx_(\d+)\b', rf'{k_prefix}_\1', s)
                f.write(f"              double {k_prefix}_{i} = {s};\n")

    # --- After all stages: Update δC ---
    # δC_new = δC + Σ_{i=1}^{s} M_i * δK_i
    f.write("\n              // --- δC update: δC += Σ M_i * δK_i ---\n")
    for k in range(N):
        m_terms = []
        for j in range(S):
            if tableau.M[j] != 0.0:
                if tableau.M[j] == 1.0:
                    m_terms.append(f"dK{j+1}_{k}")
                else:
                    m_terms.append(f"{tableau.M[j]:.17g} * dK{j+1}_{k}")
        if m_terms:
            m_expr = " + ".join(m_terms)
            f.write(f"              dC_{k} += {m_expr};\n")

    # Close the runtime loop over checkpoint steps
    f.write("          } // end for (step)\n")
