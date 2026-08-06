import os
import subprocess


def test_chapman_generation():
    mech_path = "tests/integration/e2e_validation/data/chapman.yaml"
    env_path = "tests/integration/e2e_validation/data/env.yaml"
    output_dir = "build/mkpp-generated"

    # Create a dummy env.yaml
    with open(env_path, "w") as f:
        f.write("mpi: {gather_to_root: false}\n")

    os.makedirs(output_dir, exist_ok=True)

    # Run MKPP compiler
    result = subprocess.run(
        [".venv/bin/mkpp", "compile", mech_path, "--test-env", env_path, "--out", output_dir],
        capture_output=True,
        text=True,
    )

    assert result.returncode == 0, f"MKPP generation failed: {result.stderr}"
    assert os.path.exists(os.path.join(output_dir, "ChapmanCycle.hpp")), "ChapmanCycle.hpp was not generated"
