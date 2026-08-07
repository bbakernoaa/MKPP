"""MKPP Code Generation Orchestrator.

This module provides the top-level `generate_headers` function that emits
Kokkos C++ solver headers from a parsed mechanism definition. It delegates
to the Jinja2 template engine for C++ emission and to focused submodules
for tableau definitions and expression formatting.

Public API (backward-compatible):
    - generate_headers
    - generate_host_api_headers
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
from .template_context import build_template_context
from .template_engine import TemplateEngine

# Re-export public API for backward compatibility
__all__ = [
    "generate_headers",
    "generate_host_api_headers",
    "SOLVER_COEFFICIENTS",
    "RosenbrockTableau",
    "format_eqn",
    "get_A",
    "get_C",
]


def generate_host_api_headers(
    mech: MechanismDefinition,
    out_dir: str = "src/solvers",
    solver_name: str = "ros3",
) -> dict[str, str]:
    """Emit the C, C++, and Fortran host API headers and wrappers for a mechanism."""
    if not mech or not mech.species:
        raise ValueError("Cannot generate host API headers for empty mechanism")

    out_path = Path(out_dir)
    out_path.mkdir(parents=True, exist_ok=True)

    context = build_template_context(mech, solver_name=solver_name)
    engine = TemplateEngine()

    rendered = {
        "c_header": ("mkpp.h", engine.render("host_api/mkpp.h.j2", context)),
        "fortran_module": ("mkpp_mod.f90", engine.render("host_api/mkpp_mod.f90.j2", context)),
        "cpp_header": ("mkpp.hpp", engine.render("host_api/mkpp.hpp.j2", context)),
        "c_api_source": ("mkpp_c_api.cpp", engine.render("host_api/mkpp_c_api.cpp.j2", context)),
    }

    results = {}
    for key, (filename, content) in rendered.items():
        file_path = out_path / filename
        with open(file_path, "w") as f:
            f.write(content)
        results[key] = str(file_path)

    return results


def generate_headers(
    mech: MechanismDefinition,
    out_dir: str = "src/solvers",
    suffix: str = "",
    solver_name: str = "ros3",
    adjoint: bool = False,
    generate_host_api: bool = False,
) -> dict[str, str]:
    """Emit the Kokkos headers and manifest artifact."""
    if not mech or not mech.species:
        raise ValueError("Cannot generate headers for empty mechanism")

    out_path = Path(out_dir)
    out_path.mkdir(parents=True, exist_ok=True)

    # 1. Build template context (handles all data preparation)
    context = build_template_context(mech, solver_name, adjoint=adjoint)
    # Add suffix to context for filename generation
    context["suffix"] = suffix

    # 2. Render the header via Jinja2 template engine
    engine = TemplateEngine()
    header_text = engine.render("header.j2", context)

    # 3. Write rendered output to the same file path as before
    header_path = out_path / f"{mech.name}{suffix}.hpp"
    with open(header_path, "w") as f:
        f.write(header_text)

    results = {"header": str(header_path)}

    if generate_host_api:
        api_results = generate_host_api_headers(mech, out_dir=out_dir, solver_name=solver_name)
        results.update(api_results)

    # 4. Manifest metadata emission (unchanged logic)
    manifest = {
        "mechanism": mech.name,
        "aerosol_representation": mech.aerosol_representation.value,
        "checksum": hashlib.sha256(mech.name.encode()).hexdigest(),
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

    manifest_path = out_path / f"{mech.name}_manifest.json"
    with open(manifest_path, "w") as f:
        json.dump(manifest, f, indent=2)

    results["manifest"] = str(manifest_path)
    return results
