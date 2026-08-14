#!/usr/bin/env python3
"""Compare baseline vs PR Callgrind instruction profile summaries for MKPP.

Exits with code 1 if any mechanism regresses beyond specified tolerance (%),
otherwise exits with code 0.
"""

from __future__ import annotations

import argparse
from pathlib import Path
import sys


def parse_summary_file(filepath: Path) -> dict[str, int]:
    """Parse a Callgrind summary file or profile_mkpp.sh TSV output.

    Parameters
    ----------
    filepath : Path
        Path to the summary or Callgrind output file.

    Returns
    -------
    dict[str, int]
        Mapping of mechanism name to instruction count.

    Raises
    ------
    FileNotFoundError
        If the input file does not exist.
    ValueError
        If no valid instruction counts could be parsed.
    """
    if not filepath.exists():
        raise FileNotFoundError(f"Summary file not found: {filepath}")

    results: dict[str, int] = {}
    content = filepath.read_text(encoding="utf-8").strip()

    for line in content.splitlines():
        line = line.strip()
        if not line or line.startswith("#"):
            continue

        parts = line.split()
        if parts[0].lower() in ("mechanism", "mech"):
            continue

        if line.startswith("summary:"):
            # Callgrind raw output file
            mech_name = filepath.stem.replace("cg_", "")
            try:
                results[mech_name] = int(parts[1])
            except (IndexError, ValueError) as err:
                raise ValueError(f"Failed to parse summary line in {filepath}: {line}") from err
            continue

        if len(parts) >= 2:
            mech_name = parts[0].strip(":,")
            # Try last column or 4th column for instruction count
            count_str = parts[-1].replace(",", "")
            if not count_str.isdigit() and len(parts) >= 4:
                count_str = parts[3].replace(",", "")

            try:
                results[mech_name] = int(count_str)
            except ValueError:
                continue

    if not results:
        raise ValueError(f"No valid mechanism instruction counts parsed from {filepath}")

    return results


def compare_profiles(
    base_file: Path,
    pr_file: Path,
    tolerance: float = 0.0,
) -> bool:
    """Compare baseline and PR instruction profile counts.

    Parameters
    ----------
    base_file : Path
        Path to baseline profile summary file.
    pr_file : Path
        Path to PR profile summary file.
    tolerance : float
        Maximum allowed percentage increase before marking regression (default: 0.0).

    Returns
    -------
    bool
        True if all mechanisms passed (no regression > tolerance), False if regressed.
    """
    base_data = parse_summary_file(base_file)
    pr_data = parse_summary_file(pr_file)

    all_mechs = sorted(set(base_data.keys()) | set(pr_data.keys()))
    has_regression = False

    print("=" * 88)
    print("                      MKPP Instruction Profile Comparison")
    print("=" * 88)
    print(
        f"{'Mechanism':<14} {'Base Instr':<18} {'PR Instr':<18} {'Delta':<14} {'Delta %':<10} {'Status':<8}"
    )
    print("-" * 88)

    for mech in all_mechs:
        base_cnt = base_data.get(mech)
        pr_cnt = pr_data.get(mech)

        if base_cnt is None and pr_cnt is not None:
            print(f"{mech:<14} {'N/A':<18} {pr_cnt:<18,d} {'N/A':<14} {'N/A':<10} {'NEW':<8}")
            continue

        if base_cnt is not None and pr_cnt is None:
            print(f"{mech:<14} {base_cnt:<18,d} {'N/A':<18} {'N/A':<14} {'N/A':<10} {'MISSING':<8}")
            has_regression = True
            continue

        if base_cnt is None or pr_cnt is None:
            continue

        delta = pr_cnt - base_cnt
        delta_pct = (delta / base_cnt * 100.0) if base_cnt > 0 else 0.0
        delta_str = f"{delta:+d}"

        if delta_pct > tolerance:
            status = "REGRESSED"
            has_regression = True
        else:
            status = "PASS"

        print(
            f"{mech:<14} {base_cnt:<18,d} {pr_cnt:<18,d} {delta_str:<14} {delta_pct:>+7.2f}%   {status:<8}"
        )

    print("=" * 88)
    print(f"Tolerance threshold : {tolerance:.2f}%")
    if has_regression:
        print("Overall Status      : REGRESSED (One or more mechanisms exceeded tolerance)")
    else:
        print("Overall Status      : PASS (All mechanisms within tolerance)")
    print("=" * 88)

    return not has_regression


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Compare baseline vs PR Callgrind instruction profile summaries."
    )
    parser.add_argument("base_file", type=Path, help="Path to baseline profile summary file")
    parser.add_argument("pr_file", type=Path, help="Path to PR profile summary file")
    parser.add_argument(
        "--tolerance",
        type=float,
        default=0.0,
        help="Allowed percentage instruction count increase (regression threshold %%, default: 0.0)",
    )

    args = parser.parse_args()

    try:
        success = compare_profiles(args.base_file, args.pr_file, tolerance=args.tolerance)
    except Exception as err:
        print(f"FATAL ERROR: {err}", file=sys.stderr)
        sys.exit(1)

    sys.exit(0 if success else 1)


if __name__ == "__main__":
    main()
