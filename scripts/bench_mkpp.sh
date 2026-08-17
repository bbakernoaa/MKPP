#!/bin/bash
# ==============================================================================
# MKPP Wall-Clock Benchmarking Script
#
# Runs wall-clock timing driver across requested mechanisms (chapman, gocart,
# saprc99, t1) using the mkpp_bench binary.
# ==============================================================================

set -euo pipefail

# Find benchmark binary in build directory
find_benchmark_binary() {
  local build_dir="$1"
  local candidates=(
    "${build_dir}/test/benchmark/mkpp_bench"
    "${build_dir}/bin/mkpp_bench"
    "${build_dir}/mkpp_bench"
  )
  local bin
  for bin in "${candidates[@]}"; do
    if [[ -f "${bin}" ]]; then
      echo "${bin}"
      return 0
    fi
  done
  return 1
}

run_mechanism_bench() {
  local bench_bin="$1"
  local mech="$2"
  local cells="$3"
  local steps="$4"

  local raw_output
  raw_output=$("${bench_bin}" --mechanism "${mech}" --cells "${cells}" --steps "${steps}" 2>&1)

  local time_ms
  time_ms=$(echo "${raw_output}" | grep "Execution time" | awk '{print $4}' || echo "N/A")

  local throughput
  throughput=$(echo "${raw_output}" | grep "Throughput" | awk '{print $3}' || echo "N/A")

  printf "%-12s %-10s %-10s %-16s %-20s\n" "${mech}" "${cells}" "${steps}" "${time_ms}" "${throughput}"
}

main() {
  local build_dir="${1:-build}"
  local cells="${2:-10000}"
  local steps="${3:-30}"
  local mechanism="${4:-all}"

  local bench_bin
  if ! bench_bin=$(find_benchmark_binary "${build_dir}"); then
    echo "FATAL ERROR: Benchmark binary 'mkpp_bench' not found in '${build_dir}'." >&2
    echo "Ensure MKPP was built with -DMKPP_ENABLE_BENCHMARK=ON." >&2
    exit 1
  fi

  local mechanisms=()
  if [[ "${mechanism}" == "all" ]]; then
    mechanisms=("chapman" "gocart" "saprc99" "ts1")
  elif [[ "${mechanism}" =~ ^(chapman|gocart|saprc99|ts1)$ ]]; then
    mechanisms=("${mechanism}")
  else
    echo "FATAL ERROR: Invalid mechanism '${mechanism}'. Allowed: all, chapman, gocart, saprc99, ts1." >&2
    exit 1
  fi

  echo "========================================================================================"
  echo "                                MKPP Benchmark Suite"
  echo "========================================================================================"
  printf "%-12s %-10s %-10s %-16s %-20s\n" "Mechanism" "Cells" "Steps" "Time (ms)" "Throughput (cell-st/s)"
  echo "----------------------------------------------------------------------------------------"

  local m
  for m in "${mechanisms[@]}"; do
    run_mechanism_bench "${bench_bin}" "${m}" "${cells}" "${steps}"
  done

  echo "========================================================================================"
}

main "$@"
