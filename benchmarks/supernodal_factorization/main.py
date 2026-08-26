"""Run identical reference/candidate TS1 solver controls and report medians."""

from __future__ import annotations

import argparse
import json
import statistics
import subprocess


def run(binary: str, args: list[str]) -> tuple[float, dict]:
    output = subprocess.check_output([binary, *args], text=True)
    document = json.loads(output)
    return float(document["timing"]["elapsed_ms"]), document


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--reference", required=True)
    parser.add_argument("--candidate", required=True)
    parser.add_argument("--runs", type=int, default=3)
    parser.add_argument("--steps", type=int, default=12)
    parser.add_argument("--repetitions", type=int, default=5)
    parser.add_argument("--dt", type=float, default=10.0)
    options = parser.parse_args()
    controls = ["--mechanism", "ts1", "--cells", "1", "--steps", str(options.steps),
                "--warmups", "2", "--repetitions", str(options.repetitions), "--dt", str(options.dt)]
    results = {}
    for label, binary in (("reference", options.reference), ("candidate", options.candidate)):
        timings = [run(binary, controls)[0] for _ in range(options.runs)]
        results[label] = {"timings_ms": timings, "median_ms": statistics.median(timings)}
    results["candidate_fraction_of_reference"] = results["reference"]["median_ms"] / results["candidate"]["median_ms"]
    print(json.dumps(results, indent=2, sort_keys=True))


if __name__ == "__main__":
    main()
