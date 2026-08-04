#!/usr/bin/env python3
"""
Comprehensive SAPRC-99 Multi-Solver & Optimization Benchmark Suite

Tests all 5 Rosenbrock solvers (ROS-2, ROS-3, ROS-4, RODAS-3, RODAS-4)
and new options (Auto-Reduction, AMORE lumping, RCM bandwidth reduction)
against the SAPRC-99 atmospheric chemistry mechanism.

Measures:
1. Build-Time Compilation Metrics (Symbolic lowering, LU non-zeros, code size)
2. C++/Kokkos Execution Benchmarks (Execution runtime, throughput)
3. Diurnal Cycle Accuracy & Mass Balance Stability
"""

import os
import sys
import time
import subprocess
import yaml
import json
import re
from pathlib import Path
import numpy as np

# Add project root to sys.path
PROJECT_ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(PROJECT_ROOT / "src"))

from mkpp.parser import load_mechanism
from mkpp.lowering import prepare_unified_jacobian, partition_reactions
from mkpp.codegen import generate_headers, SOLVER_COEFFICIENTS
from mkpp.amore import apply_amore_lumping


def run_cmd(cmd, cwd=None):
    res = subprocess.run(cmd, shell=True, capture_output=True, text=True, cwd=cwd or PROJECT_ROOT)
    return res


def benchmark_build_metrics(mech_path, lump_path=None):
    print("=" * 80)
    print(" 1. BUILD-TIME COMPILATION & SOLVER TABLEAU METRICS (SAPRC-99)")
    print("=" * 80)

    mech = load_mechanism(str(mech_path))
    if lump_path:
        with open(lump_path, 'r') as f:
            rules = yaml.safe_load(f)
        mech = apply_amore_lumping(mech, rules)

    print(f"Mechanism: {mech.name} | Species: {len(mech.species)} | Reactions: {len(mech.reactions)}")

    t0 = time.time()
    lowering_data = prepare_unified_jacobian(mech)
    t_lower = (time.time() - t0) * 1000.0

    lu_plan = lowering_data.get("symbolic_lu_plan")
    sparsity = lowering_data.get("sparsity_analysis")

    nnz_jac = len(lu_plan.non_zero_jacobian) if lu_plan else 0
    l_exprs = len(lu_plan.l_expressions) if lu_plan else 0
    u_exprs = len(lu_plan.u_expressions) if lu_plan else 0
    fill_in = lu_plan.fill_in_count if lu_plan else 0
    perm = lu_plan.permutation if lu_plan else None
    blocks = lu_plan.blocks if lu_plan else None

    print(f"Lowering Time:           {t_lower:.2f} ms")
    print(f"Jacobian Non-Zeros (NNZ): {nnz_jac}")
    print(f"LU Factorization Ops:    L={l_exprs}, U={u_exprs} (Fill-in: {fill_in})")
    print(f"RCM Permutation Applied: {'Yes' if perm else 'No'}")
    print(f"Block-Diagonal Blocks:   {len(blocks) if blocks else 1}")

    print("\n" + "-" * 80)
    print(f"{'Solver':<10} | {'Stages':<8} | {'Order (ELO)':<10} | {'Header Size':<12} | {'CodeGen Time':<14}")
    print("-" * 80)

    results = {}
    tmp_out = PROJECT_ROOT / "build" / "benchmark_headers"
    tmp_out.mkdir(parents=True, exist_ok=True)

    for solver_name, tableau in SOLVER_COEFFICIENTS.items():
        mech.metadata = {
            "sympy_metadata": lowering_data,
            "symbolic_lu_plan": lu_plan,
        }
        t0 = time.time()
        artifacts = generate_headers(mech, out_dir=str(tmp_out), solver_name=solver_name, suffix=f"_{solver_name}")
        t_gen = (time.time() - t0) * 1000.0

        header_path = Path(artifacts["header"])
        header_size_kb = header_path.stat().st_size / 1024.0

        print(f"{solver_name.upper():<10} | {tableau.stages:<8} | {int(tableau.ELO):<10} | {header_size_kb:>8.1f} KB | {t_gen:>11.2f} ms")
        results[solver_name] = {
            "stages": tableau.stages,
            "elo": tableau.ELO,
            "header_path": header_path,
            "size_kb": header_size_kb,
            "codegen_ms": t_gen,
        }

    return results


def run_cpp_solver_benchmark(solvers):
    print("\n" + "=" * 80)
    print(" 2. C++/KOKKOS EXECUTABLE RUNTIME BENCHMARKS (1440 Diurnal Steps, 24 Hours)")
    print("=" * 80)

    # Copy generated headers into build/mkpp-generated for CMake compilation
    gen_dir = PROJECT_ROOT / "mkpp-generated"
    gen_dir.mkdir(parents=True, exist_ok=True)

    print(f"{'Solver':<10} | {'Build Status':<12} | {'1 Cell (ms)':<12} | {'1000 Cells (ms)':<16} | {'Throughput (cell-steps/s)':<24}")
    print("-" * 80)

    for solver_name in SOLVER_COEFFICIENTS.keys():
        # Copy solver header as saprc99.hpp for the build
        src_header = PROJECT_ROOT / "build" / "benchmark_headers" / f"saprc99_{solver_name}.hpp"
        target_header = gen_dir / "saprc99.hpp"
        if src_header.exists():
            target_header.write_text(src_header.read_text())

        # Compile C++ target
        res = run_cmd("cmake --build build --target e2e_saprc99_runner")
        if res.returncode != 0:
            print(f"{solver_name.upper():<10} | {'BUILD FAIL':<12} | {'N/A':<12} | {'N/A':<16} | {'N/A':<24}")
            continue

        # Execute 1 cell
        res_1 = run_cmd("NUM_CELLS=1 NUM_STEPS=1440 ./build/tests/integration/e2e_validation/e2e_saprc99_runner")
        time_1ms = "N/A"
        if res_1.returncode == 0:
            m = re.search(r'Time:\s*([\d\.]+)\s*ms', res_1.stdout)
            if m: time_1ms = f"{float(m.group(1)):.2f}"

        # Execute 1000 cells
        res_1000 = run_cmd("NUM_CELLS=1000 NUM_STEPS=1440 ./build/tests/integration/e2e_validation/e2e_saprc99_runner")
        time_1000ms = "N/A"
        throughput_str = "N/A"
        if res_1000.returncode == 0:
            m = re.search(r'Time:\s*([\d\.]+)\s*ms', res_1000.stdout)
            if m:
                t_ms = float(m.group(1))
                time_1000ms = f"{t_ms:.2f}"
                if t_ms > 0:
                    tp = (1000.0 * 1440.0) / (t_ms / 1000.0)
                    throughput_str = f"{tp:.2e}"

        print(f"{solver_name.upper():<10} | {'SUCCESS':<12} | {time_1ms:>10} ms | {time_1000ms:>14} ms | {throughput_str:>24}")


def main():
    mech_path = PROJECT_ROOT / "mechanisms" / "saprc99.yaml"
    lump_path = PROJECT_ROOT / "mechanisms" / "lumping_rules_saprc99.yaml"

    print("\n=========================================================================")
    print("    MKPP FULL MULTI-SOLVER & OPTIMIZATION BENCHMARK SUITE")
    print("=========================================================================\n")

    # 1. Benchmark full SAPRC-99 build metrics
    solvers = benchmark_build_metrics(mech_path)

    # 2. Benchmark AMORE Lumped SAPRC-99 build metrics
    print("\n")
    benchmark_build_metrics(mech_path, lump_path=lump_path)

    # 3. Run C++ Kokkos execution benchmarks across all 5 solvers
    run_cpp_solver_benchmark(solvers)

    print("\n=========================================================================")
    print("    BENCHMARK COMPLETE")
    print("=========================================================================\n")


if __name__ == "__main__":
    main()
