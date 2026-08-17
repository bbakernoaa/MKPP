#!/bin/bash
# ==============================================================================
# MKPP Valgrind Callgrind Instruction Profiling Script
#
# Runs valgrind callgrind profiling on mkpp_bench and extracts instruction
# counts into a TSV summary table.
# ==============================================================================

set -euo pipefail

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

extract_instruction_count() {
  local out_file="$1"
  local count=""

  if [[ -f "${out_file}" ]]; then
    count=$(grep "^summary:" "${out_file}" | awk '{print $2}' || true)
    if [[ -z "${count}" ]] && command -v callgrind_annotate &>/dev/null; then
      count=$(callgrind_annotate "${out_file}" 2>/dev/null | grep -i "PROGRAM TOTALS" | awk '{print $1}' | tr -d ',' || true)
    fi
  fi

  if [[ -z "${count}" ]]; then
    count="N/A"
  fi

  echo "${count}"
}

profile_mechanism() {
  local bench_bin="$1"
  local mech="$2"
  local cells="$3"
  local steps="$4"
  local out_dir="$5"

  local out_file="${out_dir}/cg_${mech}.out"

  valgrind --tool=callgrind --instr-atstart=no --callgrind-out-file="${out_file}" \
    "${bench_bin}" --mechanism "${mech}" --cells "${cells}" --steps "${steps}" &>/dev/null

  local instr_count
  instr_count=$(extract_instruction_count "${out_file}")

  printf "%s\t%s\t%s\t%s\n" "${mech}" "${cells}" "${steps}" "${instr_count}"
}

main() {
  local build_dir="${1:-${BUILD_DIR:-build}}"
  local cells="${2:-${CELLS:-2000}}"
  local steps="${3:-${STEPS:-5}}"
  local mechanism="${4:-${MECHANISM:-all}}"
  local out_dir="${5:-${OUT:-/tmp}}"

  if ! command -v valgrind &>/dev/null; then
    echo "FATAL ERROR: valgrind executable not found in PATH." >&2
    exit 1
  fi

  local bench_bin
  if ! bench_bin=$(find_benchmark_binary "${build_dir}"); then
    echo "FATAL ERROR: Benchmark binary 'mkpp_bench' not found in '${build_dir}'." >&2
    echo "Ensure MKPP was built with -DMKPP_ENABLE_BENCHMARK=ON." >&2
    exit 1
  fi

  mkdir -p "${out_dir}"

  local mechanisms=()
  if [[ "${mechanism}" == "all" ]]; then
    mechanisms=("chapman" "gocart" "saprc99" "ts1")
  elif [[ "${mechanism}" =~ ^(chapman|gocart|saprc99|ts1)$ ]]; then
    mechanisms=("${mechanism}")
  else
    echo "FATAL ERROR: Invalid mechanism '${mechanism}'. Allowed: all, chapman, gocart, saprc99, ts1." >&2
    exit 1
  fi

  printf "Mechanism\tCells\tSteps\tInstructionCount\n"

  local m
  for m in "${mechanisms[@]}"; do
    profile_mechanism "${bench_bin}" "${m}" "${cells}" "${steps}" "${out_dir}"
  done
}

main "$@"
