from unittest.mock import patch

from mkpp.parser import load_mechanism
from mkpp.reporting import write_report


def test_write_report_without_matplotlib(tmp_path):
    mech = load_mechanism("mechanisms/openatmos/chapman/mechanism.json")
    with patch("mkpp.reporting.HAS_MATPLOTLIB", False):
        write_report(mech, {}, tmp_path)

    report_file = tmp_path / "report_chapman.md"
    assert report_file.exists()
    assert "# MKPP Mechanism Diagnostic Report: chapman" in report_file.read_text()
    assert not (tmp_path / "network_graph_chapman.png").exists()


def test_write_report_with_matplotlib_if_installed(tmp_path):
    mech = load_mechanism("mechanisms/openatmos/chapman/mechanism.json")
    write_report(mech, {}, tmp_path)

    report_file = tmp_path / "report_chapman.md"
    assert report_file.exists()
