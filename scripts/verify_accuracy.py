#!/usr/bin/env python
"""
Accuracy verification: MKPP C++ solver vs KPP Fortran baseline.
Runs the MKPP solver for 1440 steps (24-hour diurnal cycle) and compares
final concentrations against the KPP Fortran reference.
"""

import csv
import os
import subprocess
import sys

import numpy as np

REPO_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))

# SAPRC-99 species names in MKPP index order (from the OpenAtmos mechanism).
MKPP_SPECIES = [
    "O3",
    "H2O2",
    "NO",
    "NO2",
    "NO3",
    "N2O5",
    "HONO",
    "HNO3",
    "HNO4",
    "SO2",
    "H2SO4",
    "CO",
    "HCHO",
    "CCHO",
    "RCHO",
    "ACET",
    "MEK",
    "HCOOH",
    "MEOH",
    "CCO_OH",
    "RCO_OH",
    "GLY",
    "MGLY",
    "BACL",
    "CRES",
    "BALD",
    "ISOPROD",
    "METHACRO",
    "MVK",
    "PROD2",
    "DCB1",
    "DCB2",
    "DCB3",
    "ETHENE",
    "ISOPRENE",
    "ALK1",
    "ALK2",
    "ALK3",
    "ALK4",
    "ALK5",
    "ARO1",
    "ARO2",
    "OLE1",
    "OLE2",
    "TERP",
    "RNO3",
    "NPHE",
    "PHEN",
    "PAN",
    "PAN2",
    "PBZN",
    "MA_PAN",
    "CCO_OOH",
    "RCO_O2",
    "RCO_OOH",
    "XN",
    "XC",
    "O3P",
    "O1D",
    "OH",
    "HO2",
    "C_O2",
    "COOH",
    "ROOH",
    "RO2_R",
    "R2O2",
    "RO2_N",
    "HOCOO",
    "CCO_O2",
    "BZCO_O2",
    "BZNO2_O",
    "BZ_O",
    "MA_RCO3",
    "TBU_O",
    "AIR",
    "O2",
    "H2O",
    "H2",
    "CH4",
]


def run_mkpp_runner():
    """Run MKPP e2e_saprc99_runner with 1440 diurnal steps."""
    runner = os.path.join(REPO_ROOT, "build/tests/integration/e2e_validation/e2e_saprc99_runner")
    if not os.path.exists(runner):
        print(f"ERROR: Runner not found at {runner}")
        print("Build with: cd build && cmake --build . --target e2e_saprc99_runner")
        return None

    cwd = os.path.join(REPO_ROOT, "build/tests/integration/e2e_validation")
    env = os.environ.copy()
    env["NUM_CELLS"] = "1"
    env["NUM_STEPS"] = "1440"
    env["OMP_NUM_THREADS"] = "1"
    env["MKPP_EXECUTION_MODE"] = "serial"

    print("Running MKPP C++ solver (1 cell x 1440 steps = 24-hour diurnal)...")
    result = subprocess.run([runner], env=env, cwd=cwd, capture_output=True, text=True, timeout=120)

    if result.returncode != 0:
        print(f"ERROR: Runner failed with code {result.returncode}")
        print(result.stderr[:500])
        return None

    for line in result.stdout.split("\n"):
        if "Time:" in line or "mode:" in line:
            print(f"  {line.strip()}")

    output_path = os.path.join(cwd, "e2e_output.csv")
    if not os.path.exists(output_path):
        print(f"ERROR: Output not found at {output_path}")
        return None

    return output_path


def load_mkpp_output(path):
    """Load MKPP output concentrations from CSV. Returns dict {int_index: concentration}."""
    conc = {}
    with open(path) as f:
        reader = csv.DictReader(f)
        for row in reader:
            ts = row.get("time_step", "").strip()
            sp = row.get("species_name", "").strip()
            c = row.get("concentration", "").strip()
            if ts and sp and c:
                try:
                    conc[int(sp)] = float(c)
                except (ValueError, KeyError):
                    pass
    return conc


def load_kpp_fortran_output(path):
    """Load KPP Fortran output. Returns dict {species_name: concentration}."""
    conc = {}
    with open(path) as f:
        reader = csv.DictReader(f)
        for row in reader:
            name = row.get("species_name", "").strip()
            c = row.get("concentration", "").strip()
            if name and c:
                try:
                    conc[name] = float(c)
                except ValueError:
                    pass
    return conc


def load_kpp_baseline_csv(path):
    """Load KPP baseline from the mixed-format CSV (Jacobian + concentrations).
    Returns dict {int_index: concentration}."""
    conc = {}
    with open(path) as f:
        reader = csv.DictReader(f)
        for row in reader:
            ts = row.get("time_step", "").strip()
            sp = row.get("species_name", "").strip()
            c = row.get("concentration", "").strip()
            # Only parse concentration rows (have time_step, species_name, concentration)
            if ts and sp and c:
                try:
                    conc[int(sp)] = float(c)
                except (ValueError, KeyError):
                    pass
    return conc


def main():
    print("=" * 78)
    print("  MKPP vs KPP Accuracy Report - SAPRC-99 (79 species, 211 reactions)")
    print("  24-hour diurnal simulation, dt=60s, 1440 timesteps")
    print("=" * 78)
    print()

    # --- Run MKPP ---
    output_path = run_mkpp_runner()
    if output_path is None:
        sys.exit(1)

    mkpp_conc = load_mkpp_output(output_path)
    print(f"  Loaded {len(mkpp_conc)} species from MKPP output")

    # --- Load KPP reference ---
    # Prefer the real Fortran output if it exists
    kpp_fortran_path = os.path.join(REPO_ROOT, "kpp_legacy/saprc99_fortran_output.csv")
    baseline_csv_path = os.path.join(REPO_ROOT, "tests/integration/e2e_validation/data/kpp_baseline_saprc99.csv")

    kpp_conc_by_name = {}
    kpp_source = None

    if os.path.exists(kpp_fortran_path):
        kpp_conc_by_name = load_kpp_fortran_output(kpp_fortran_path)
        nonzero = sum(1 for v in kpp_conc_by_name.values() if abs(v) > 1e-30)
        if nonzero > 5:
            kpp_source = kpp_fortran_path
            print(f"  Loaded {len(kpp_conc_by_name)} species from KPP Fortran output ({nonzero} non-zero)")

    if kpp_source is None and os.path.exists(baseline_csv_path):
        baseline_conc = load_kpp_baseline_csv(baseline_csv_path)
        nonzero = sum(1 for v in baseline_conc.values() if abs(v) > 1e-30)
        if nonzero > 5:
            # Convert numeric indices to names using MKPP ordering
            for idx, val in baseline_conc.items():
                if idx < len(MKPP_SPECIES):
                    kpp_conc_by_name[MKPP_SPECIES[idx]] = val
            kpp_source = baseline_csv_path
            print(f"  Loaded {len(baseline_conc)} species from baseline CSV ({nonzero} non-zero)")

    if kpp_source is None:
        print()
        print("  WARNING: No valid KPP reference found (all zeros or missing).")
        print("  Showing MKPP results only for inspection.")
        print()

    # --- Print results ---
    print()
    print(f"{'Idx':>4} {'Species':<12} {'KPP Fortran':>18} {'MKPP C++':>18} {'Rel Diff':>14}")
    print("-" * 78)

    diffs = []
    n_spec = min(len(MKPP_SPECIES), max(mkpp_conc.keys(), default=0) + 1)

    for i in range(n_spec):
        name = MKPP_SPECIES[i]
        mkpp_val = mkpp_conc.get(i, 0.0)
        kpp_val = kpp_conc_by_name.get(name, 0.0)

        if abs(kpp_val) > 1e-30 and abs(mkpp_val) > 1e-30:
            rel_diff = abs(mkpp_val - kpp_val) / max(abs(kpp_val), abs(mkpp_val)) * 100.0
            diffs.append((name, rel_diff))
            diff_str = f"{rel_diff:12.6f}%"
        elif abs(kpp_val) < 1e-30 and abs(mkpp_val) < 1e-30:
            diff_str = "    both zero"
        elif abs(kpp_val) < 1e-30:
            diff_str = "  no KPP ref"
        else:
            diff_str = "  no MKPP val"

        # Print all rows with at least one non-zero value
        if abs(kpp_val) > 1e-30 or abs(mkpp_val) > 1e-10:
            print(f"{i:4d} {name:<12} {kpp_val:18.8e} {mkpp_val:18.8e} {diff_str}")

    print("-" * 78)

    if diffs:
        rel_diffs = [d for _, d in diffs]
        print(f"  Species with both non-zero: {len(diffs)}")
        print(f"  Mean relative difference:   {np.mean(rel_diffs):.6f}%")
        print(f"  Max relative difference:    {np.max(rel_diffs):.6f}%")
        print(f"  Median relative difference: {np.median(rel_diffs):.6f}%")

        # Show worst offenders
        worst = sorted(diffs, key=lambda x: x[1], reverse=True)[:10]
        print()
        print("  Top 10 largest discrepancies:")
        for name, d in worst:
            print(f"    {name:<12} {d:.6f}%")
    else:
        print("  No species with non-zero values in both files - cannot compute differences")

    print()

    # --- Summary ---
    if diffs:
        mean_diff = np.mean(rel_diffs)
        if mean_diff < 1.0:
            print("  CONCLUSION: EXCELLENT AGREEMENT (< 1% mean relative difference).")
        elif mean_diff < 10.0:
            print("  CONCLUSION: GOOD AGREEMENT (< 10% mean relative difference).")
            print("  Differences likely due to photolysis rate handling (continuous vs discrete).")
        else:
            print(f"  CONCLUSION: SIGNIFICANT DIFFERENCES ({mean_diff:.1f}% mean).")
            print("  Investigate solver tolerances, rate constant formulations, or initial conditions.")

    return 0


if __name__ == "__main__":
    sys.exit(main())
