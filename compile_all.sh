#!/bin/bash

# Activate the virtual environment
source .venv/bin/activate
export PYTHONPATH=src

# List of mechanism YAML files
MECHANISMS=(
    "mechanisms/chapman.yaml"
    "mechanisms/small_strato.yaml"
    "mechanisms/carbon.yaml"
    "mechanisms/gocart.yaml"
    "mechanisms/saprc99.yaml"
    "mechanisms/saprcnov.yaml"
)

TEST_ENV="tests/integration/e2e_validation/data/env.yaml"
OUT_DIR="mkpp-generated/"

# Compile each mechanism
for MECH in "${MECHANISMS[@]}"; do
    echo "========================================"
    echo "Compiling $MECH..."
    echo "========================================"
    if [ "$MECH" = "mechanisms/saprc99.yaml" ]; then
        python3 -m mkpp.cli compile "$MECH" --test-env "$TEST_ENV" --out "$OUT_DIR" --lump "mechanisms/lumping_rules_saprc99.yaml"
    else
        python3 -m mkpp.cli compile "$MECH" --test-env "$TEST_ENV" --out "$OUT_DIR"
    fi
    if [ $? -ne 0 ]; then
        echo "Error compiling $MECH"
        exit 1
    fi
done

echo "All mechanisms compiled successfully."
