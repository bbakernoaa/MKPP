import os
import subprocess
import time

REPO_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))


def run_legacy_kpp(cells=100, steps=1440):
    """
    Run legacy Fortran KPP SAPRC-99 diurnal executable.
    The executable kpp_legacy/saprc99_diurnal.exe runs 100 cells over 1,440 timesteps.
    """
    kpp_dir = os.path.join(REPO_ROOT, "kpp_legacy")
    exe_path = os.path.join(kpp_dir, "saprc99_diurnal.exe")
    print(
        f"   [Legacy KPP] Launching saprc99_diurnal.exe ({cells} cells x {steps} timesteps)...",
        flush=True,
    )
    start = time.perf_counter()
    res = subprocess.run(
        [exe_path], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, cwd=kpp_dir
    )
    elapsed_ms = (time.perf_counter() - start) * 1000.0
    print(
        f"   [Legacy KPP] Completed in {elapsed_ms/1000.0:.2f} s ({elapsed_ms:.1f} ms)", flush=True
    )
    return elapsed_ms


def run_mkpp_runner(
    cells=1000, steps=1440, threads=8, label="MKPP Runner", execution_mode="kokkos"
):
    env = os.environ.copy()
    env["NUM_CELLS"] = str(cells)
    env["NUM_STEPS"] = str(steps)
    env["OMP_NUM_THREADS"] = str(threads)
    env["KOKKOS_NUM_THREADS"] = str(threads)
    env["MKPP_EXECUTION_MODE"] = execution_mode
    env["OMP_PROC_BIND"] = "spread"
    env["OMP_PLACES"] = "threads"
    env["OMP_DYNAMIC"] = "false"

    cmd_path = os.path.join(REPO_ROOT, "build/tests/integration/e2e_validation/e2e_saprc99_runner")
    cmd = [cmd_path]
    print(
        f"   [{label}] Launching e2e_saprc99_runner (cells={cells}, steps={steps}, threads={threads}, mode={execution_mode})...",
        flush=True,
    )
    start = time.perf_counter()
    res = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, env=env)
    elapsed_ms = (time.perf_counter() - start) * 1000.0

    for line in res.stdout.split("\n"):
        if "Time:" in line:
            try:
                kernel_ms = float(line.split("Time:")[1].strip().replace("ms", ""))
                print(
                    f"   [{label}] Kernel execution reported: {kernel_ms:.1f} ms (Total wall: {elapsed_ms:.1f} ms)",
                    flush=True,
                )
                return kernel_ms
            except Exception:
                pass
    print(f"   [{label}] Completed in {elapsed_ms/1000.0:.2f} s ({elapsed_ms:.1f} ms)", flush=True)
    return elapsed_ms


if __name__ == "__main__":
    print("==========================================================================", flush=True)
    print("      MKPP vs Legacy KPP Full Benchmark Report (SAPRC-99 Mechanism)      ", flush=True)
    print(
        "==========================================================================\n", flush=True
    )

    print("--- 1. Speed Comparison (100 Grid Cells x 1,440 Steps = 144k Steps) ---", flush=True)
    kpp_ms = run_legacy_kpp(cells=100, steps=1440)
    mkpp_ms = run_mkpp_runner(
        cells=100, steps=1440, threads=1, label="MKPP 100 cells", execution_mode="serial"
    )

    print(
        f"\nLegacy KPP (Sparse Fortran 90, 79 sp) : {kpp_ms/1000.0:8.2f} s ({kpp_ms:10.1f} ms)",
        flush=True,
    )
    print(
        f"MKPP Full (AOT C++ Kokkos, 79 sp)     : {mkpp_ms/1000.0:8.2f} s ({mkpp_ms:10.1f} ms) -> {kpp_ms/mkpp_ms:5.2f}x Speedup",
        flush=True,
    )

    scaling_steps = 100
    print(
        f"\n--- 2. Scalability Across Grid Cell Counts ({scaling_steps} Timesteps) ---", flush=True
    )
    print(f"{'Cells':>10} | {'MKPP Time (ms)':>15} | {'Throughput (cell-steps/s)':>25}", flush=True)
    print("-" * 60, flush=True)
    cell_counts = [1, 10, 100, 1000]
    for c in cell_counts:
        t_ms = run_mkpp_runner(
            cells=c,
            steps=scaling_steps,
            threads=1,
            label=f"Scaling {c} cells",
            execution_mode="serial",
        )
        tp = (c * scaling_steps) / (t_ms / 1000.0) if t_ms > 0 else 0
        print(f"{c:10d} | {t_ms:15.1f} | {tp:25.2e}", flush=True)

    print("\n--- 3. Multi-Thread OpenMP Scaling (10,000 Cells x 100 Timesteps) ---", flush=True)
    print(
        f"{'Threads':>10} | {'Time (ms)':>15} | {'Speedup':>12} | {'Efficiency (%)':>18}",
        flush=True,
    )
    print("-" * 60, flush=True)
    t1_time = None
    for threads in [1, 2, 4, 8, 16]:
        t_ms = run_mkpp_runner(
            cells=10000,
            steps=100,
            threads=threads,
            label=f"OpenMP {threads} threads",
            execution_mode="kokkos",
        )
        if threads == 1:
            t1_time = t_ms
            speedup = 1.0
            eff = 100.0
        else:
            speedup = t1_time / t_ms if t_ms > 0 else 0
            eff = (speedup / threads) * 100.0
        print(f"{threads:10d} | {t_ms:15.1f} | {speedup:12.2f}x | {eff:18.1f}%", flush=True)
