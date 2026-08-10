import os
import subprocess

import matplotlib.pyplot as plt
import numpy as np


def run_benchmark(executable, cells, steps=100):
    cmd = [executable]
    env = os.environ.copy()
    env["NUM_CELLS"] = str(cells)
    env["NUM_STEPS"] = str(steps)

    res = subprocess.run(cmd, env=env, capture_output=True, text=True)

    mkpp_ms = None
    micm_ms = None

    for line in res.stdout.splitlines():
        if line.startswith("Execution Time (ms)"):
            parts = line.split()
            # Execution Time (ms)         MKPP_VAL    MICM_VAL    SPEEDUPx
            mkpp_ms = float(parts[3])
            micm_ms = float(parts[4])
            break

    return mkpp_ms, micm_ms


cell_counts = [10, 50, 100, 500, 1000, 2000, 5000, 10000]
steps = 100


def run_both(binary, cells, steps, title, out_file):
    mkpp_times = []
    micm_times = []

    print(f"Running benchmarks for {title}...")
    for c in cell_counts:
        print(f"Cells: {c}...")
        mkpp_t, micm_t = run_benchmark(binary, c, steps)
        mkpp_times.append(mkpp_t)
        micm_times.append(micm_t)

    mkpp_times = np.array(mkpp_times) / 1000.0  # ms to seconds
    micm_times = np.array(micm_times) / 1000.0  # ms to seconds

    plt.figure(figsize=(10, 6))

    plt.plot(cell_counts, micm_times, marker="o", label="MICM C++", color="blue", linewidth=2)
    plt.plot(cell_counts, mkpp_times, marker="s", label="MKPP C++ (AOT)", color="green", linewidth=2)

    plt.xscale("log")
    plt.yscale("log")

    plt.xlabel("Number of Grid Cells", fontsize=12)
    plt.ylabel(f"Execution Time (s) for {steps} steps", fontsize=12)
    plt.title(f"Performance Scaling: MKPP vs MICM ({title})", fontsize=14)
    plt.grid(True, which="both", ls="-", alpha=0.2)
    plt.legend(fontsize=12)

    plt.tight_layout()
    plt.savefig(out_file, dpi=300)
    print(f"Plot saved to {out_file}")


run_both(
    "./build/tests/integration/e2e_validation/benchmark_mkpp_vs_micm",
    1000,
    100,
    "Chapman Mechanism",
    "reports/performance_scaling_chapman.png",
)

# For T1, use 10 steps so it completes in a reasonable time for 10k cells
run_both(
    "./build/tests/integration/e2e_validation/benchmark_mkpp_vs_micm_t1",
    1000,
    10,
    "T1 Mechanism (210 spec, 547 rxn)",
    "reports/performance_scaling_t1.png",
)
