"""
Property-based test for solver name validation.

**Validates: Requirements 1.1, 1.3**

Property 1: Solver name validation is exhaustive
For any string `s`, the CLI accepts `s` as a valid `--solver` value if and only if
`s` is in the set {"ros2", "ros3", "ros4", "rodas3", "rodas4"}.
"""

import pytest
from hypothesis import given, settings
from hypothesis import strategies as st
from mkpp.cli import main
from mkpp.codegen import SOLVER_COEFFICIENTS

# The canonical set of valid solver names per the spec
VALID_SOLVER_NAMES = {"ros2", "ros3", "ros4", "rodas3", "rodas4"}


# Strategy for generating arbitrary strings that are NOT valid solver names
invalid_solver_names = st.text(min_size=0, max_size=30).filter(
    lambda s: s not in VALID_SOLVER_NAMES
)


def test_valid_solver_set_matches_solver_coefficients():
    """
    The set of valid solver names accepted by the CLI must exactly match
    the keys in SOLVER_COEFFICIENTS.

    **Validates: Requirements 1.1**
    """
    assert set(SOLVER_COEFFICIENTS.keys()) == VALID_SOLVER_NAMES, (
        f"SOLVER_COEFFICIENTS keys {set(SOLVER_COEFFICIENTS.keys())} "
        f"do not match expected valid set {VALID_SOLVER_NAMES}"
    )


@pytest.mark.parametrize("solver_name", sorted(VALID_SOLVER_NAMES))
def test_valid_solver_names_accepted_by_cli(solver_name, monkeypatch):
    """
    For each valid solver name, the CLI accepts it without error (exit code 0).

    **Validates: Requirements 1.1**
    """
    # Mock run_compiler to avoid actual compilation
    monkeypatch.setattr("mkpp.cli.run_compiler", lambda *args, **kwargs: None)

    with pytest.raises(SystemExit) as exc_info:
        main(
            [
                "compile",
                "dummy.yaml",
                "--test-env",
                "env.yaml",
                "--out",
                "build",
                "--solver",
                solver_name,
            ]
        )

    assert exc_info.value.code == 0, (
        f"Valid solver name '{solver_name}' was rejected by CLI "
        f"(exit code {exc_info.value.code})"
    )


@given(solver_name=invalid_solver_names)
@settings(max_examples=100)
def test_invalid_solver_names_rejected_by_cli(solver_name):
    """
    For any string not in the valid solver set, the CLI rejects it with
    a non-zero exit code (argparse exits with code 2 for invalid choices).

    **Validates: Requirements 1.3**
    """
    with pytest.raises(SystemExit) as exc_info:
        main(
            [
                "compile",
                "dummy.yaml",
                "--test-env",
                "env.yaml",
                "--out",
                "build",
                "--solver",
                solver_name,
            ]
        )

    assert exc_info.value.code != 0, (
        f"Invalid solver name '{solver_name}' was accepted by CLI "
        f"(exit code {exc_info.value.code}), expected non-zero"
    )


@pytest.mark.parametrize("solver_name", ["ros5", "invalid", "", "ROS3", "Ros4", "RODAS3", " ros2"])
def test_specific_invalid_solver_names_rejected(solver_name):
    """
    Specific invalid solver names (including case variations, empty string,
    non-existent solvers) are rejected by the CLI.

    **Validates: Requirements 1.3**
    """
    with pytest.raises(SystemExit) as exc_info:
        main(
            [
                "compile",
                "dummy.yaml",
                "--test-env",
                "env.yaml",
                "--out",
                "build",
                "--solver",
                solver_name,
            ]
        )

    assert exc_info.value.code == 2, (
        f"Invalid solver name '{solver_name}' did not produce exit code 2 "
        f"(got {exc_info.value.code})"
    )
