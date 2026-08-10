#!/usr/bin/env bash
# Wrapper script to run automated MKPP vs MICM / OpenAtmos comparison suite.

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
cd "$REPO_ROOT"

REPORTS_DIR="${REPO_ROOT}/reports"
mkdir -p "$REPORTS_DIR"

OUT_MD="${REPORTS_DIR}/micm_comparison.md"
OUT_JSON="${REPORTS_DIR}/micm_comparison.json"

echo "=========================================================================="
echo "      Running Automated MKPP vs MICM / OpenAtmos Comparison Suite       "
echo "=========================================================================="

python3 "${SCRIPT_DIR}/compare_micm.py" \
    --all \
    --cells 1000 \
    --steps 100 \
    --dt 60.0 \
    --out-md "$OUT_MD" \
    --out-json "$OUT_JSON" "$@"

echo "Comparison suite complete."
echo "Markdown report written to: $OUT_MD"
echo "JSON report written to: $OUT_JSON"
