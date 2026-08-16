#!/bin/bash
# ==============================================================================
# MKPP Mechanism Compilation Script
#
# Compiles all atmospheric chemical mechanisms into optimized C++ Kokkos headers
# with full feature support (Adjoint/TLM, Manifest, Analysis Report, SymPy CSE).
# ==============================================================================

set -euo pipefail

main() {
    # Ensure execution from repository root
    local script_dir
    script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
    local repo_root
    repo_root="$(cd "${script_dir}/.." && pwd)"
    cd "${repo_root}" || exit 1

    local python_bin=".venv/bin/python"
    if [[ ! -f "${python_bin}" ]]; then
        python_bin="python3"
    fi

    local test_env="tests/integration/e2e_validation/data/env.yaml"
    if [[ ! -f "${test_env}" ]]; then
        test_env="example_env.yaml"
    fi

    local out_dir="mkpp-generated/"
    mkdir -p "${out_dir}"

    local mechanisms=(
        "mechanisms/chapman.yaml"
        "mechanisms/small_strato.yaml"
        "mechanisms/carbon.yaml"
        "mechanisms/gocart.yaml"
        "mechanisms/saprc99.yaml"
        "mechanisms/saprcnov.yaml"
        "mechanisms/saprc99_mini.yaml"
        "mechanisms/t1.yaml"
    )

    local mech
    for mech in "${mechanisms[@]}"; do
        if [[ ! -f "${mech}" ]]; then
            echo "WARNING: Mechanism file ${mech} not found, skipping."
            continue
        fi

        echo "========================================"
        echo "Compiling ${mech}..."
        echo "========================================"

        if ! "${python_bin}" -m mkpp.cli compile "${mech}" \
            --test-env "${test_env}" \
            --out "${out_dir}" \
            --adjoint \
            --emit-manifest \
            --report \
            --verbose; then
            echo "FATAL ERROR: Failed to compile ${mech}"
            exit 1
        fi
    done

    echo "========================================"
    echo "All mechanisms compiled successfully."
    echo "========================================"
}

main "$@"
