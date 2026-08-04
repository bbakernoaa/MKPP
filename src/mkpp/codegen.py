"""MKPP Code Generation Orchestrator.

This module provides the top-level `generate_headers` function that emits
Kokkos C++ solver headers from a parsed mechanism definition. It delegates
to focused submodules for tableau definitions, expression formatting, and
stage emission.

Public API (backward-compatible):
    - generate_headers
    - SOLVER_COEFFICIENTS
    - RosenbrockTableau
    - format_eqn
    - get_A, get_C
"""

import hashlib
import json
from pathlib import Path

from .format_eqn import format_eqn
from .model import MechanismDefinition
from .rosenbrock import SOLVER_COEFFICIENTS, RosenbrockTableau, get_A, get_C
from .symbolic_emit import (
    _emit_rosenbrock_adjoint_stages,
    _emit_rosenbrock_stages,
    _emit_rosenbrock_tlm_stages,
)

# Re-export public API for backward compatibility
__all__ = [
    "generate_headers",
    "SOLVER_COEFFICIENTS",
    "RosenbrockTableau",
    "format_eqn",
    "get_A",
    "get_C",
]


def generate_headers(
    mech: MechanismDefinition,
    out_dir: str = "src/solvers",
    suffix: str = "",
    solver_name: str = "ros3",
    adjoint: bool = False,
) -> dict[str, str]:
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
    if sympy_meta is None and mech.species:
        from .lowering import prepare_unified_jacobian

        sympy_meta = prepare_unified_jacobian(mech)

    # 1. Deterministic header emission
    header_path = out_path / f"{mech.name}{suffix}.hpp"
    with open(header_path, "w") as f:
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

        # Emit CheckpointBuffer struct when adjoint mode is enabled (D5, Req 4.1, 4.3, 4.4)
        if adjoint:
            N = len(mech.species)
            f.write("  // Checkpoint buffer for discrete adjoint/TLM integration\n")
            f.write(
                "  // Recompute-J strategy: only state is stored, Jacobian recomputed from saved state\n"
            )
            f.write("  struct CheckpointBuffer {\n")
            f.write("      static constexpr int MAX_STEPS = 200;\n")
            f.write(f"      static constexpr int NUM_SPECIES = {N};\n")
            f.write("      int num_steps = 0;\n")
            f.write("      double h[MAX_STEPS];\n")
            f.write(
                "      double state[MAX_STEPS][NUM_SPECIES];  // saved concentrations at step entry\n"
            )
            f.write("  };\n\n")

        f.write("  template<typename DeviceType>\n")
        f.write("  struct SolverKernels {\n")

        # 1. compute_rates
        f.write("      template <class StateView, class RateView>\n")
        f.write(
            "      KOKKOS_INLINE_FUNCTION void compute_rates(const StateView& state, RateView& F_block, const double* jvals) const {\n"
        )
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
        f.write(
            "      KOKKOS_INLINE_FUNCTION void compute_jacobian(const StateView& state, JacView& J_block, const double* jvals) const {\n"
        )
        if sympy_meta and "jacobian_matrix" in sympy_meta:
            J = sympy_meta["jacobian_matrix"]
            for i in range(J.shape[0]):
                for j in range(J.shape[1]):
                    if J[i, j] != 0:
                        eqn = format_eqn(
                            J[i, j], mech.species, state_var="state", use_parentheses=True
                        )
                        f.write(f"          J_block({i}, {j}) = {eqn};\n")
        f.write("      }\n\n")

        # 3. compute_adjoint
        f.write("      template <class StateView, class JacView>\n")
        f.write(
            "      KOKKOS_INLINE_FUNCTION void compute_adjoint(const StateView& state, JacView& J_adj_block, const double* jvals) const {\n"
        )
        if sympy_meta and "adjoint_matrix" in sympy_meta:
            J_adj = sympy_meta["adjoint_matrix"]
            for i in range(J_adj.shape[0]):
                for j in range(J_adj.shape[1]):
                    if J_adj[i, j] != 0:
                        eqn = format_eqn(
                            J_adj[i, j], mech.species, state_var="state", use_parentheses=True
                        )
                        f.write(f"          J_adj_block({i}, {j}) = {eqn};\n")
        f.write("      }\n\n")

        # 4. compute_tlm
        f.write("      template <class StateView, class DeltaView, class RateView>\n")
        f.write(
            "      KOKKOS_INLINE_FUNCTION void compute_tlm(const StateView& state, const DeltaView& delta_C, RateView& dF_block, const double* jvals) const {\n"
        )
        if sympy_meta and "jacobian_matrix" in sympy_meta:
            J = sympy_meta["jacobian_matrix"]
            for i in range(J.shape[0]):
                f.write(f"          dF_block({i}) = 0.0;\n")
                for j in range(J.shape[1]):
                    if J[i, j] != 0:
                        eqn = format_eqn(
                            J[i, j], mech.species, state_var="state", use_parentheses=True
                        )
                        f.write(f"          dF_block({i}) += ({eqn}) * delta_C({j});\n")
        f.write("      }\n\n")

        # 5. project_mass_conservation
        f.write("      template <class StateView, class MassView>\n")
        f.write(
            "      KOKKOS_INLINE_FUNCTION void project_mass_conservation(StateView& C_projected, const StateView& C, const MassView& m_0) const {\n"
        )
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
            f.write("      // Photolysis reactions (Cloud-J input mapping):\n")
            for pr in photolysis_reactions_meta:
                reactants_str = ", ".join(
                    f"{k}"
                    for k in (
                        pr["reactants"].keys()
                        if isinstance(pr["reactants"], dict)
                        else pr["reactants"]
                    )
                )
                products_str = ", ".join(
                    f"{k}"
                    for k in (
                        pr["products"].keys()
                        if isinstance(pr["products"], dict)
                        else pr["products"]
                    )
                )
                f.write(
                    f"      //   jvals[{pr['photo_idx']}] = {reactants_str} -> {products_str}  (original A: {pr['original_A']})\n"
                )
            f.write(f"      static constexpr int NUM_PHOTOLYSIS = {num_photolysis};\n\n")

        # 6. integrate (AOT Symbolic LU, generic Rosenbrock solver)
        f.write("      template <class StateView>\n")
        f.write(
            "      KOKKOS_INLINE_FUNCTION void integrate(double dt_total, StateView& state, const double* jvals) const {\n"
        )
        f.write(f"          const int NUM_SPECIES = {N};\n")
        f.write(
            f"          // {tableau.name} coefficients ({tableau.stages}-stage, order {tableau.ELO:.0f})\n"
        )
        gamma = tableau.Gamma[0]
        f.write(f"          const double g = {gamma:.17g};\n")
        f.write("          const double safety = 0.9;\n")
        f.write("          const double max_growth = 6.0;\n")
        f.write("          const double min_shrink = 0.2;\n")
        f.write("          double t = 0.0;\n")
        f.write(
            "          double dt = Kokkos::fmin(dt_total, 1.0);  // conservative initial step\n\n"
        )
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

            lu_plan = compute_symbolic_lu_decomposition(
                sympy_meta["jacobian_matrix"], [s.name for s in mech.species]
            )

        # Pre-compute transposed LU plan when adjoint mode is enabled (task 5.3)
        # This must be done once, before emitting adjoint functions that need W^{-T} solves.
        if adjoint and lu_plan:
            from .lowering import compute_transposed_lu_plan

            compute_transposed_lu_plan(lu_plan)

        # Determine permutation for state access
        _perm = lu_plan.permutation if lu_plan and lu_plan.permutation else None

        if _perm:
            f.write("          // NOTE: State access uses permuted species ordering\n")

        for i in range(N):
            src_idx = _perm[i] if _perm else i
            f.write(f"          const double S_{i} = state({src_idx});\n")
        f.write("\n")

        if lu_plan:
            import re as _re_w

            # Jacobian Non-Zeros
            f.write(
                "          // Analytical Jacobian & Iteration Matrix W = inv_g_dt*I - J (sparse)\n"
            )
            non_zero_jac_set = set()
            for i, j, expr_str in lu_plan.non_zero_jacobian:
                non_zero_jac_set.add((i, j))
                eqn = format_eqn(expr_str, mech.species, state_var="S", use_parentheses=False)
                f.write(f"          double J_{i}_{j} = {eqn};\n")

            # Determine which W entries are actually needed by the LU plan
            needed_w = set()
            for _i in range(N):
                needed_w.add((_i, _i))  # Diagonal always needed
            for _kind, _i, _j, _expr_str in lu_plan.lu_expressions_ordered:
                for _m in _re_w.finditer(r"W_(\d+)_(\d+)", _expr_str):
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
            f.write("\n          // Symbolic Doolittle Sparse LU Factorization\n")
            # Emit block boundary comments if block structure is present
            if lu_plan.blocks and len(lu_plan.blocks) > 1:
                _emitted_block_header = set()
                for kind, i, j, expr_str in lu_plan.lu_expressions_ordered:
                    # Find which block this expression belongs to
                    for block_num, block_indices in enumerate(lu_plan.blocks):
                        if i in block_indices:
                            if block_num not in _emitted_block_header:
                                _emitted_block_header.add(block_num)
                                block_species_names = [
                                    lu_plan.species_map[idx] for idx in block_indices
                                ]
                                f.write(
                                    f"          // Block {block_num}: species [{', '.join(block_species_names)}]\n"
                                )
                            break
                    f.write(f"          double {kind}_{i}_{j} = {expr_str};\n")
            else:
                for kind, i, j, expr_str in lu_plan.lu_expressions_ordered:
                    f.write(f"          double {kind}_{i}_{j} = {expr_str};\n")

            # Emit all stage computations using the generic Rosenbrock emitter
            _emit_rosenbrock_stages(
                f, tableau, N, lu_plan, sympy_meta, mech, _perm, is_reduction=False
            )

        # Close while loop
        f.write("          } // end while (t < dt_total)\n")
        f.write("      }\n\n")

        # 7. integrate_with_reduction (Auto-Reduction Kernel)
        f.write("      template <class StateView>\n")
        f.write("      KOKKOS_INLINE_FUNCTION void integrate_with_reduction(\n")
        f.write(
            "          double dt_total, StateView& state, const double* jvals, double importance_threshold) const\n"
        )
        f.write("      {\n")
        f.write(f"          const int NUM_SPECIES = {N};\n")
        # Use the same tableau gamma as integrate()
        gamma = tableau.Gamma[0]
        f.write(f"          const double g = {gamma:.17g};\n")
        f.write("          const double safety = 0.9;\n")
        f.write("          const double max_growth = 6.0;\n")
        f.write("          const double min_shrink = 0.2;\n\n")
        f.write("          bool active[NUM_SPECIES];\n")
        f.write("          double t = 0.0;\n")
        f.write(
            "          double dt = Kokkos::fmin(dt_total, 1.0);  // conservative initial step\n\n"
        )
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
            import re as _re_w

            # Stage 1 Rates F1 (needed for importance evaluation)
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
                f.write(
                    f"          active[{i}] = (Kokkos::fabs(F1_{i}) / (atol[{i}] + rtol[{i}] * Kokkos::fabs(state({state_idx}))) >= importance_threshold);\n"
                )

            # Jacobian Non-Zeros with frozen species handling
            f.write(
                "\n          // 3. Analytical Jacobian & Iteration Matrix W (identity for frozen species)\n"
            )
            non_zero_jac_set = set()
            for i, j, expr_str in lu_plan.non_zero_jacobian:
                non_zero_jac_set.add((i, j))
                eqn = format_eqn(expr_str, mech.species, state_var="S", use_parentheses=False)
                f.write(f"          double J_{i}_{j} = {eqn};\n")

            # Emit W with conditional logic for frozen species (sparse: only needed entries)
            needed_w2 = set()
            for _i in range(N):
                needed_w2.add((_i, _i))  # Diagonal always needed
            # Gather W references from LU expressions (annotated or plain)
            if lu_plan.annotated_expressions:
                for ann_expr in lu_plan.annotated_expressions:
                    for _m in _re_w.finditer(r"W_(\d+)_(\d+)", ann_expr.expr):
                        needed_w2.add((int(_m.group(1)), int(_m.group(2))))
            else:
                for _kind, _i, _j, _expr_str in lu_plan.lu_expressions_ordered:
                    for _m in _re_w.finditer(r"W_(\d+)_(\d+)", _expr_str):
                        needed_w2.add((int(_m.group(1)), int(_m.group(2))))

            for i, j in sorted(needed_w2):
                if i == j:
                    if (i, i) in non_zero_jac_set:
                        f.write(
                            f"          double W_{i}_{i} = active[{i}] ? (inv_g_dt - J_{i}_{i}) : 1.0;\n"
                        )
                    else:
                        f.write(f"          double W_{i}_{i} = active[{i}] ? inv_g_dt : 1.0;\n")
                elif (i, j) in non_zero_jac_set:
                    f.write(
                        f"          double W_{i}_{j} = (active[{i}] && active[{j}]) ? (-J_{i}_{j}) : 0.0;\n"
                    )
                else:
                    # Fill-in dependency: W referenced by LU but no Jacobian entry
                    f.write(f"          double W_{i}_{j} = 0.0;\n")

            # Symbolic LU Factorization with conditional skip for frozen species
            f.write(
                "\n          // 4. Symbolic LU Factorization (conditional skip for frozen species)\n"
            )

            # Use annotated expressions if available for conditional skipping
            if lu_plan.annotated_expressions:
                for ann_expr in lu_plan.annotated_expressions:
                    deps = ann_expr.depends_on
                    if deps:
                        cond_parts = [f"active[{d}]" for d in sorted(deps)]
                        cond = " && ".join(cond_parts)
                        f.write(
                            f"          double {ann_expr.kind}_{ann_expr.row}_{ann_expr.col} = ({cond}) ? ({ann_expr.expr}) : "
                        )
                        # For U diagonal, frozen → 1.0; for off-diag → 0.0
                        if ann_expr.row == ann_expr.col:
                            f.write("1.0;\n")
                        else:
                            f.write("0.0;\n")
                    else:
                        f.write(
                            f"          double {ann_expr.kind}_{ann_expr.row}_{ann_expr.col} = {ann_expr.expr};\n"
                        )
            else:
                # Fallback: emit without conditional skip (use normal LU)
                for kind, i, j, expr_str in lu_plan.lu_expressions_ordered:
                    f.write(f"          double {kind}_{i}_{j} = {expr_str};\n")

            # Emit generic Rosenbrock stages using the same tableau as integrate()
            _emit_rosenbrock_stages(
                f,
                tableau,
                N,
                lu_plan,
                sympy_meta,
                mech,
                _perm,
                is_reduction=True,
                skip_first_f_eval=True,
            )

        # Close while loop for integrate_with_reduction
        f.write("          } // end while (t < dt_total)\n")
        f.write("      }\n")

        # 8. integrate_fwd_checkpoint (gated behind adjoint=True)
        # Same Rosenbrock integration as integrate() but saves checkpoint data
        # after each accepted step for use by adjoint/TLM integrators.
        if adjoint:
            f.write("\n      // Forward integration with checkpointing for adjoint/TLM\n")
            f.write(
                "      // Saves step size h and state at each accepted step into CheckpointBuffer.\n"
            )
            f.write("      // Returns number of accepted steps, or -1 if MAX_STEPS exceeded.\n")
            f.write("      template <class StateView>\n")
            f.write("      KOKKOS_INLINE_FUNCTION int integrate_fwd_checkpoint(\n")
            f.write("          double dt_total, StateView& state, const double* jvals,\n")
            f.write("          CheckpointBuffer& chk) const\n")
            f.write("      {\n")
            f.write(f"          const int NUM_SPECIES = {N};\n")
            f.write(
                f"          // {tableau.name} coefficients ({tableau.stages}-stage, order {tableau.ELO:.0f})\n"
            )
            gamma = tableau.Gamma[0]
            f.write(f"          const double g = {gamma:.17g};\n")
            f.write("          const double safety = 0.9;\n")
            f.write("          const double max_growth = 6.0;\n")
            f.write("          const double min_shrink = 0.2;\n")
            f.write("          int ierr = 0;\n")
            f.write("          chk.num_steps = 0;\n")
            f.write("          double t = 0.0;\n")
            f.write(
                "          double dt = Kokkos::fmin(dt_total, 1.0);  // conservative initial step\n\n"
            )
            f.write("          while (t < dt_total) {\n")
            f.write("          dt = Kokkos::min(dt, dt_total - t);\n")
            f.write("          const double inv_g_dt = 1.0 / (g * dt);\n\n")
            f.write("          // 0. Hoist state values into scalar registers\n")

            if _perm:
                f.write("          // NOTE: State access uses permuted species ordering\n")

            for i in range(N):
                src_idx = _perm[i] if _perm else i
                f.write(f"          const double S_{i} = state({src_idx});\n")
            f.write("\n")

            if lu_plan:
                import re as _re_w

                # Jacobian Non-Zeros
                f.write(
                    "          // Analytical Jacobian & Iteration Matrix W = inv_g_dt*I - J (sparse)\n"
                )
                non_zero_jac_set_chk = set()
                for i, j, expr_str in lu_plan.non_zero_jacobian:
                    non_zero_jac_set_chk.add((i, j))
                    eqn = format_eqn(expr_str, mech.species, state_var="S", use_parentheses=False)
                    f.write(f"          double J_{i}_{j} = {eqn};\n")

                # Determine which W entries are actually needed by the LU plan
                needed_w_chk = set()
                for _i in range(N):
                    needed_w_chk.add((_i, _i))  # Diagonal always needed
                for _kind, _i, _j, _expr_str in lu_plan.lu_expressions_ordered:
                    for _m in _re_w.finditer(r"W_(\d+)_(\d+)", _expr_str):
                        needed_w_chk.add((int(_m.group(1)), int(_m.group(2))))

                for i, j in sorted(needed_w_chk):
                    if i == j:
                        if (i, i) in non_zero_jac_set_chk:
                            f.write(f"          double W_{i}_{i} = inv_g_dt - J_{i}_{i};\n")
                        else:
                            f.write(f"          double W_{i}_{i} = inv_g_dt;\n")
                    elif (i, j) in non_zero_jac_set_chk:
                        f.write(f"          double W_{i}_{j} = -J_{i}_{j};\n")
                    else:
                        f.write(f"          double W_{i}_{j} = 0.0;\n")

                # Symbolic LU Factorization
                f.write("\n          // Symbolic Doolittle Sparse LU Factorization\n")
                if lu_plan.blocks and len(lu_plan.blocks) > 1:
                    _emitted_block_header_chk = set()
                    for kind, i, j, expr_str in lu_plan.lu_expressions_ordered:
                        for block_num, block_indices in enumerate(lu_plan.blocks):
                            if i in block_indices:
                                if block_num not in _emitted_block_header_chk:
                                    _emitted_block_header_chk.add(block_num)
                                    block_species_names = [
                                        lu_plan.species_map[idx] for idx in block_indices
                                    ]
                                    f.write(
                                        f"          // Block {block_num}: species [{', '.join(block_species_names)}]\n"
                                    )
                                break
                        f.write(f"          double {kind}_{i}_{j} = {expr_str};\n")
                else:
                    for kind, i, j, expr_str in lu_plan.lu_expressions_ordered:
                        f.write(f"          double {kind}_{i}_{j} = {expr_str};\n")

                # Emit all stage computations with checkpoint=True
                _emit_rosenbrock_stages(
                    f,
                    tableau,
                    N,
                    lu_plan,
                    sympy_meta,
                    mech,
                    _perm,
                    is_reduction=False,
                    checkpoint=True,
                )

            # Close while loop
            f.write("          } // end while (t < dt_total)\n")
            f.write("          return chk.num_steps;\n")
            f.write("      }\n")

            # 9. integrate_adj (Discrete Adjoint backward integration)
            # Walks backward through checkpoint buffer, accumulating adjoint variable λ.
            # Requirement 2.5: function signature with template params StateView, AdjView.
            # Requirement 6.2: emitted when --adjoint is enabled.
            f.write(
                "\n      // Discrete adjoint backward integration through checkpointed trajectory\n"
            )
            f.write(
                "      // Walks backward through saved steps, accumulating adjoint variable lambda.\n"
            )
            f.write("      template <class StateView, class AdjView>\n")
            f.write("      KOKKOS_INLINE_FUNCTION void integrate_adj(\n")
            f.write("          double dt_total, const StateView& state_final,\n")
            f.write("          AdjView& lambda, const double* jvals,\n")
            f.write("          const CheckpointBuffer& chk) const\n")
            f.write("      {\n")
            gamma = tableau.Gamma[0]
            f.write(f"          const double g = {gamma:.17g};\n")
            # Emit the adjoint stage logic (runtime backward loop, Python-time stage unrolling)
            _emit_rosenbrock_adjoint_stages(f, tableau, N, lu_plan, sympy_meta, mech, _perm)
            f.write("      }\n")

            # 10. integrate_tlm (TLM forward propagation, Req 3.4, 6.2)
            # Propagates perturbation δC forward through checkpointed Rosenbrock steps.
            f.write("\n      // Tangent Linear Model: forward propagation of perturbation δC\n")
            f.write("      // Uses checkpoint buffer from integrate_fwd_checkpoint().\n")
            f.write("      template <class StateView, class PertView>\n")
            f.write("      KOKKOS_INLINE_FUNCTION void integrate_tlm(\n")
            f.write("          double dt_total, const StateView& state_0,\n")
            f.write("          PertView& delta_C, const double* jvals,\n")
            f.write("          const CheckpointBuffer& chk) const\n")
            f.write("      {\n")
            gamma = tableau.Gamma[0]
            f.write(f"          const double g = {gamma:.17g};\n\n")

            # Declare local aliases for delta_C: dC_k = delta_C(k)
            # The TLM stage emitter uses dC_k naming for the perturbation vector
            f.write("          // Local aliases for delta_C (TLM stages use dC_k naming)\n")
            for k in range(N):
                f.write(f"          double dC_{k} = delta_C({k});\n")
            f.write("\n")

            # Emit TLM stage logic (runtime forward loop, Python-time stage unrolling)
            _emit_rosenbrock_tlm_stages(f, tableau, N, lu_plan, sympy_meta, mech, _perm)

            # Write back final delta_C values to the output view
            f.write("\n          // Write back final δC to output view\n")
            for k in range(N):
                f.write(f"          delta_C({k}) = dC_{k};\n")

            f.write("      }\n")

        f.write("  };\n")
        f.write("}\n")

    # 2. Manifest metadata emission (T008)
    manifest = {
        "mechanism": mech.name,
        "aerosol_representation": mech.aerosol_representation.value,
        "checksum": hashlib.sha256(mech.name.encode()).hexdigest(),  # Simplified checksum for MVP
        "artifacts": [
            {"kind": "header", "file": header_path.name},
            {"kind": "adjoint_tlm_record", "differentiable": True},
        ],
    }

    if getattr(mech, "host_interface", None) and mech.host_interface.arrays:
        manifest["host_interface"] = {
            arr.name: {
                "rank": arr.rank,
                "layout": arr.layout,
                "lifetime": "unmanaged_borrowed_from_host"
                if arr.ownership == "host"
                else "device_owned",
            }
            for arr in mech.host_interface.arrays
        }

    partition_meta = getattr(mech, "partition_metadata", None)
    if partition_meta:
        manifest["solver_partition"] = partition_meta

    manifest_path = out_path / "manifest.json"
    with open(manifest_path, "w") as f:
        json.dump(manifest, f, indent=2)

    return {"header": str(header_path), "manifest": str(manifest_path)}
