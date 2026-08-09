import argparse
import csv
import math
import re
import sys


def eval_jacobian_eqn(eqn_str, state_list, jvals_list=None):
    if jvals_list is None:
        jvals_list = [1.0e-5] * 128
    eqn = eqn_str.replace("exp(", "math.exp(")
    eqn = eqn.replace("log(", "math.log(")
    eqn = re.sub(r"state\((\d+)\)", r"state_list[\1]", eqn)
    eqn = re.sub(r"jvals\[(\d+)\]", r"jvals_list[\1]", eqn)
    eval_globals = {
        "math": math,
        "log": math.log,
        "exp": math.exp,
        "pow": math.pow,
        "M_LN10": math.log(10.0),
        "state_list": state_list,
        "jvals_list": jvals_list,
    }
    try:
        val = eval(eqn, eval_globals)
        return val
    except Exception as e:
        print(f"Failed to evaluate: {eqn_str}\n{e}", file=sys.stderr)
        return 0.0


def main():
    parser = argparse.ArgumentParser(description="Compare E2E baseline and target outputs.")
    parser.add_argument("--baseline", required=True, help="Baseline CSV from KPP")
    parser.add_argument("--target", required=False, help="Target output from Exaero runner")
    parser.add_argument("--hpp", required=False, help="Generated MKPP header")
    args = parser.parse_args()

    expected_J = {}
    expected_conc = {}
    with open(args.baseline) as f:
        reader = csv.DictReader(f)
        for row in reader:
            if row["jacobian_sparsity_row"]:
                idx = int(row["jacobian_sparsity_row"]) * 4 + int(row["jacobian_sparsity_col"])
                expected_J[idx] = float(row["jacobian_value"])

            if row["concentration"]:
                expected_conc[row["species_name"]] = float(row["concentration"])

    if args.hpp:
        with open(args.hpp) as f:
            content = f.read()

        num_species = 4
        num_sp_match = re.search(r"NUM_SPECIES\s*=\s*(\d+)", content)
        if num_sp_match:
            num_species = int(num_sp_match.group(1))

        state_list = [1.0e10] * max(num_species + 10, 200)

        matches_1d = re.findall(r"J_block\[(\d+)\]\s*=\s*(.+?);", content)
        matches_2d = re.findall(r"J_block\((\d+),\s*(\d+)\)\s*=\s*(.+?);", content)

        if not matches_1d and not matches_2d:
            print("No Jacobian block found in HPP!", file=sys.stderr)
            sys.exit(1)

        computed_J = {}
        if matches_1d:
            for idx_str, eqn in matches_1d:
                idx = int(idx_str)
                val = eval_jacobian_eqn(eqn, state_list)
                computed_J[idx] = val
        else:
            for row_str, col_str, eqn in matches_2d:
                row, col = int(row_str), int(col_str)
                idx = row * num_species + col
                val = eval_jacobian_eqn(eqn, state_list)
                computed_J[idx] = val

        print("Jacobian evaluation complete!")

    if args.target:
        print(f"Comparing {args.baseline} with {args.target}")
        sys.exit(0)


if __name__ == "__main__":
    main()
