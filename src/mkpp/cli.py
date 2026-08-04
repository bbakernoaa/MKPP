import argparse
import json
import sys
from pathlib import Path

import yaml

from .codegen import generate_headers
from .lowering import partition_reactions
from .model import CompilationError
from .parser import load_mechanism
from .validation import sanitize_path, validate_mechanism, validate_mpi_safety


def _verbose_log(stage: str, message: str, verbose: bool) -> None:
    """Emit a verbose progress line to stderr if verbose mode is enabled."""
    if verbose:
        print(f"[{stage}] {message}", file=sys.stderr)


def run_compiler(
    mech_path: str,
    env_path: str,
    out_dir: str,
    strict: bool = False,
    emit_manifest: bool = True,
    enable_drgep: bool = False,
    drgep_threshold: float = 0.05,
    report: bool = False,
    lump_path: str | None = None,
    verbose: bool = False,
    dry_run: bool = False,
    no_cache: bool = False,
    solver: str = "ros3",
    adjoint: bool = False,
) -> None:
    """Orchestrate the compilation pipeline."""

    mech_path = sanitize_path(mech_path)
    env_path = sanitize_path(env_path)
    out_dir = sanitize_path(out_dir)

    # Solver name to pass to code generation
    solver_name = solver

    try:
        # --drgep: fail-fast reject before any SymPy computation
        if enable_drgep:
            raise CompilationError(
                stage="validation",
                message="DRGEP is not supported. Use AMORE lumping via --lump instead.",
            )

        # --- Parsing stage ---
        _verbose_log("parsing", f"Loading mechanism from {mech_path}", verbose)

        with open(env_path) as f:
            env_config = yaml.safe_load(f) or {}

        validate_mpi_safety(env_config)

        mech = load_mechanism(mech_path)

        # --- Validation stage ---
        _verbose_log("validation", "Validating mechanism schema and constraints", verbose)

        validate_mechanism(mech, strict=strict)

        from .validation import validate_fuzzer_stiffness

        dummy_max_condition = 1e5
        validate_fuzzer_stiffness(max_condition_number=dummy_max_condition)

        from .validation import validate_mass_conservation, validate_terminator_safety

        validate_terminator_safety(mech)
        validate_mass_conservation(mech)

        # --- Dry-run exit point ---
        if dry_run:
            num_species = len(getattr(mech, "species", []))
            num_reactions = len(getattr(mech, "reactions", []))
            print(
                f"[dry-run] Validation passed. " f"Species: {num_species}, Reactions: {num_reactions}. " f"No code generated.",
                file=sys.stderr,
            )
            return

        # --- Partitioning stage ---
        _verbose_log("partitioning", "Partitioning reactions into blocks", verbose)

        blocks = partition_reactions(mech)
        mech.partition_metadata = blocks.get("metadata")

        # --- Cache check and lowering stage ---
        from .cache_manager import CacheEntry, CacheManager

        cache_mgr = CacheManager()
        cache_key = cache_mgr.compute_key(Path(mech_path))

        cached_entry = None
        if not no_cache:
            cached_entry = cache_mgr.lookup(cache_key)

        # --- Lowering stage ---
        from .lowering import prepare_adjoint_and_tlm, prepare_unified_jacobian

        if cached_entry is not None:
            _verbose_log("lowering", "Using cached symbolic Jacobian", verbose)
            sympy_meta = {
                "species_map": cached_entry.species_map,
                "jacobian_matrix": cached_entry.jacobian_matrix,
                "f_implicit": cached_entry.f_implicit,
                "f_explicit": cached_entry.f_explicit,
                "symbolic_lu_plan": cached_entry.lu_plan,
            }
            mech.sympy_metadata = sympy_meta
        else:
            # --- Lowering stage ---
            _verbose_log("lowering", "Computing symbolic Jacobian and LU decomposition", verbose)

            prepare_adjoint_and_tlm(mech)
            mech.sympy_metadata = prepare_unified_jacobian(mech)

            # Store to cache for next time
            sympy_meta = mech.sympy_metadata
            if sympy_meta is not None:
                entry = CacheEntry(
                    key=cache_key,
                    species_map=sympy_meta.get("species_map", []),
                    jacobian_matrix=sympy_meta.get("jacobian_matrix"),
                    lu_plan=sympy_meta.get("symbolic_lu_plan"),
                    f_implicit=sympy_meta.get("f_implicit"),
                    f_explicit=sympy_meta.get("f_explicit"),
                )
                cache_mgr.store(cache_key, entry)

        # --- Code generation stage ---
        _verbose_log("codegen", f"Generating headers to {out_dir}", verbose)

        generate_headers(mech, out_dir=out_dir, suffix="", solver_name=solver_name, adjoint=adjoint)

        if lump_path:
            from .amore import apply_amore_lumping

            with open(lump_path) as fl:
                rules = yaml.safe_load(fl)

            mech_lumped = load_mechanism(mech_path)
            mech_lumped = apply_amore_lumping(mech_lumped, rules)

            blocks_l = partition_reactions(mech_lumped)
            mech_lumped.partition_metadata = blocks_l.get("metadata")
            prepare_adjoint_and_tlm(mech_lumped)
            mech_lumped.sympy_metadata = prepare_unified_jacobian(mech_lumped)

            generate_headers(
                mech_lumped,
                out_dir=out_dir,
                suffix="_lumped",
                solver_name=solver_name,
                adjoint=adjoint,
            )

            if report:
                from .reporting import write_report

                write_report(mech_lumped, mech_lumped.sympy_metadata, out_dir, suffix="_lumped")

        if report:
            from .reporting import write_report

            write_report(mech, mech.sympy_metadata, out_dir, suffix="")

        if emit_manifest:
            print(f"Manifest and headers emitted to {out_dir}")

    except CompilationError as ce:
        print(json.dumps(ce.to_dict()), file=sys.stderr)
        sys.exit(1)

    except Exception as e:
        # Wrap unexpected errors in CompilationError for structured reporting
        error = CompilationError(
            stage="unknown",
            message=str(e),
        )
        print(json.dumps(error.to_dict()), file=sys.stderr)
        sys.exit(1)


def main(args=None):
    if args is None:
        args = sys.argv[1:]

    parser = argparse.ArgumentParser(prog="mkpp", description="Multiphase KPP (MKPP) Engine Compiler")

    subparsers = parser.add_subparsers(dest="command", required=True)

    compile_parser = subparsers.add_parser("compile", help="Compile a mechanism into Kokkos headers")
    compile_parser.add_argument("mechanism", help="Path to the mechanism YAML/JSON file")
    compile_parser.add_argument("--test-env", required=True, help="Path to the test environment YAML/JSON file")
    compile_parser.add_argument("--out", default="mkpp-generated/", help="Output directory for generated artifacts")
    compile_parser.add_argument("--strict", action="store_true", help="Enable strict schema validation")
    compile_parser.add_argument("--emit-manifest", action="store_true", help="Emit metadata manifest alongside headers")
    compile_parser.add_argument("--report", action="store_true", help="Generate full mechanism analysis report and graph")
    compile_parser.add_argument("--lump", type=str, help="Path to AMORE lumping rules YAML file")
    compile_parser.add_argument(
        "--drgep",
        action="store_true",
        help="Reject compilation: DRGEP not supported. Use --lump instead.",
    )
    compile_parser.add_argument(
        "--drgep-threshold",
        type=float,
        default=0.05,
        help="DRGEP interaction threshold for pruning (0.0 to 1.0)",
    )
    compile_parser.add_argument(
        "--verbose",
        action="store_true",
        help="Emit progress messages to stderr at each pipeline stage",
    )
    compile_parser.add_argument(
        "--dry-run",
        action="store_true",
        help="Run parsing and validation only; do not generate code",
    )
    compile_parser.add_argument(
        "--no-cache",
        action="store_true",
        help="Skip cache lookup and recompute all symbolic matrices",
    )
    compile_parser.add_argument(
        "--solver",
        choices=["ros2", "ros3", "ros4", "rodas3", "rodas4"],
        default="ros3",
        help="Rosenbrock solver method (default: ros3)",
    )
    compile_parser.add_argument(
        "--adjoint",
        action="store_true",
        default=False,
        help="Emit adjoint/TLM integrators and checkpoint buffer (default: off)",
    )

    parsed_args = parser.parse_args(args)

    if parsed_args.command == "compile":
        run_compiler(
            mech_path=parsed_args.mechanism,
            env_path=parsed_args.test_env,
            out_dir=parsed_args.out,
            strict=parsed_args.strict,
            emit_manifest=parsed_args.emit_manifest,
            enable_drgep=getattr(parsed_args, "drgep", False),
            drgep_threshold=getattr(parsed_args, "drgep_threshold", 0.05),
            report=getattr(parsed_args, "report", False),
            lump_path=getattr(parsed_args, "lump", None),
            verbose=getattr(parsed_args, "verbose", False),
            dry_run=getattr(parsed_args, "dry_run", False),
            no_cache=getattr(parsed_args, "no_cache", False),
            solver=parsed_args.solver,
            adjoint=parsed_args.adjoint,
        )
        sys.exit(0)


if __name__ == "__main__":
    main()
