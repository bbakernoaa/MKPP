"""Unit tests for generate_flamegraph.py script."""

import subprocess
import sys
from pathlib import Path

# Ensure repository root and scripts directory are in sys.path
repo_root = Path(__file__).resolve().parent.parent.parent
scripts_dir = repo_root / "scripts"
if str(scripts_dir) not in sys.path:
    sys.path.insert(0, str(scripts_dir))

import generate_flamegraph  # type: ignore  # noqa: E402

MOCK_CALLGRIND = """# callgrind format
events: Ir
summary: 1000

fn=(1) main
10 100
cfn=(2) solver_step
calls=1 0
15 500
20 50

fn=(2) solver_step
30 200
cfn=(3) Kokkos_kernel
calls=1 0
35 300

fn=(3) Kokkos_kernel
40 300
"""


def test_parse_callgrind():
    parsed = generate_flamegraph.parse_callgrind(MOCK_CALLGRIND)
    assert "main" in parsed
    assert "solver_step" in parsed
    assert "Kokkos_kernel" in parsed

    # Check self costs
    assert parsed["main"].self_cost == 150
    assert parsed["solver_step"].self_cost == 200
    assert parsed["Kokkos_kernel"].self_cost == 300

    # Check callees
    assert parsed["main"].callees.get("solver_step") == 500
    assert parsed["solver_step"].callees.get("Kokkos_kernel") == 300


def test_fold_stacks():
    parsed = generate_flamegraph.parse_callgrind(MOCK_CALLGRIND)
    folded = generate_flamegraph.fold_callstacks(parsed)

    assert "main" in folded or "main;solver_step" in folded
    total_instructions = sum(folded.values())
    # Total self costs: 150 + 200 + 300 = 650
    assert abs(total_instructions - 650) < 1.0


def test_generate_svg_flamegraph(tmp_path):
    out_svg = tmp_path / "flamegraph.svg"
    parsed = generate_flamegraph.parse_callgrind(MOCK_CALLGRIND)
    folded = generate_flamegraph.fold_callstacks(parsed)

    generate_flamegraph.render_svg(
        folded=folded,
        out_path=out_svg,
        title="Test Flamegraph",
        total_instructions=1000,
    )

    assert out_svg.exists()
    content = out_svg.read_text(encoding="utf-8")
    assert "<svg" in content
    assert "</svg>" in content
    assert "<rect" in content
    assert "Test Flamegraph" in content
    assert "Kokkos_kernel" in content
    assert "solver_step" in content


def test_cli_execution(tmp_path):
    cg_file = tmp_path / "test.out"
    cg_file.write_text(MOCK_CALLGRIND, encoding="utf-8")
    svg_file = tmp_path / "test.svg"

    script_path = scripts_dir / "generate_flamegraph.py"
    cmd = [
        sys.executable,
        str(script_path),
        "--callgrind",
        str(cg_file),
        "--out",
        str(svg_file),
        "--title",
        "CLI Test Title",
    ]
    res = subprocess.run(cmd, capture_output=True, text=True)
    assert res.returncode == 0, f"Stderr: {res.stderr}"
    assert svg_file.exists()
    content = svg_file.read_text(encoding="utf-8")
    assert "<svg" in content
    assert "CLI Test Title" in content
