"""Tests for the --migrate-equilibrium CLI flag (Task 9.1)."""

import warnings
from pathlib import Path

import pytest
import yaml
from mkpp.cli import main, migrate_equilibrium


def _make_mech_with_phase_change(tmp_path: Path) -> Path:
    """Create a minimal mechanism YAML with a PHASE_CHANGE reaction for NH4/NO3/SO4."""
    mech_data = {
        "species": [
            {"name": "NH3"},
            {"name": "NH4a"},
            {"name": "HNO3"},
            {"name": "NO3an1"},
            {"name": "SO4"},
            {"name": "O3"},
        ],
        "reactions": [
            {
                "type": "PHASE_CHANGE",
                "reactants": {"NH3": 1.0, "HNO3": 1.0, "SO4": 1.0},
                "products": {"NH4a": 1.0, "NO3an1": 1.0},
                "description": "ISORROPIA equilibration",
                "continuous_transition": True,
            },
            {
                "type": "ARRHENIUS",
                "reactants": {"O3": 1.0},
                "products": {},
                "A": 1.0,
            },
        ],
    }
    mech_file = tmp_path / "mechanism.yaml"
    mech_file.write_text(yaml.dump(mech_data, default_flow_style=False, sort_keys=False))
    return mech_file


def test_migrate_equilibrium_removes_phase_change(tmp_path):
    """PHASE_CHANGE for NH4/NO3/SO4 species is removed and EQUILIBRIUM block added."""
    mech_file = _make_mech_with_phase_change(tmp_path)

    with warnings.catch_warnings(record=True) as w:
        warnings.simplefilter("always")
        result = migrate_equilibrium(str(mech_file))

    assert result is not None
    output_path = Path(result)
    assert output_path.exists()
    assert output_path.name == "mechanism_equilibrium.yaml"

    with open(result) as f:
        output_data = yaml.safe_load(f)

    reaction_types = [r["type"] for r in output_data["reactions"]]
    assert "EQUILIBRIUM" in reaction_types
    assert "PHASE_CHANGE" not in reaction_types
    # Non-NH4/NO3/SO4 reactions preserved
    assert "ARRHENIUS" in reaction_types


def test_migrate_equilibrium_emits_deprecation_warning(tmp_path):
    """Migration emits a DeprecationWarning about PHASE_CHANGE."""
    mech_file = _make_mech_with_phase_change(tmp_path)

    with warnings.catch_warnings(record=True) as w:
        warnings.simplefilter("always")
        migrate_equilibrium(str(mech_file))

    deprecation_warnings = [x for x in w if issubclass(x.category, DeprecationWarning)]
    assert len(deprecation_warnings) == 1
    assert "PHASE_CHANGE" in str(deprecation_warnings[0].message)
    assert "deprecated" in str(deprecation_warnings[0].message)


def test_migrate_equilibrium_idempotent(tmp_path):
    """If mechanism already has EQUILIBRIUM, migration returns None."""
    mech_file = _make_mech_with_phase_change(tmp_path)

    # First migration
    with warnings.catch_warnings(record=True):
        warnings.simplefilter("always")
        result = migrate_equilibrium(str(mech_file))

    # Second migration on the output: should be idempotent
    result2 = migrate_equilibrium(result)
    assert result2 is None


def test_migrate_equilibrium_no_phase_change(tmp_path):
    """If no PHASE_CHANGE reactions for NH4/NO3/SO4 species, returns None."""
    mech_data = {
        "species": [{"name": "O3"}, {"name": "NO2"}],
        "reactions": [
            {"type": "ARRHENIUS", "reactants": {"O3": 1.0}, "products": {"NO2": 1.0}, "A": 1.0},
        ],
    }
    mech_file = tmp_path / "mechanism.yaml"
    mech_file.write_text(yaml.dump(mech_data, default_flow_style=False, sort_keys=False))

    result = migrate_equilibrium(str(mech_file))
    assert result is None


def test_migrate_equilibrium_preserves_non_nh4_phase_change(tmp_path):
    """PHASE_CHANGE reactions that don't overlap with NH4/NO3/SO4 are preserved."""
    mech_data = {
        "species": [
            {"name": "NH3"},
            {"name": "NH4a"},
            {"name": "HNO3"},
            {"name": "NO3an1"},
            {"name": "SO4"},
            {"name": "O3"},
            {"name": "HCl"},
            {"name": "Cla"},
        ],
        "reactions": [
            {
                "type": "PHASE_CHANGE",
                "reactants": {"NH3": 1.0, "HNO3": 1.0},
                "products": {"NH4a": 1.0, "NO3an1": 1.0},
                "continuous_transition": True,
            },
            {
                "type": "PHASE_CHANGE",
                "reactants": {"HCl": 1.0},
                "products": {"Cla": 1.0},
                "continuous_transition": True,
            },
        ],
    }
    mech_file = tmp_path / "mechanism.yaml"
    mech_file.write_text(yaml.dump(mech_data, default_flow_style=False, sort_keys=False))

    with warnings.catch_warnings(record=True):
        warnings.simplefilter("always")
        result = migrate_equilibrium(str(mech_file))

    assert result is not None
    with open(result) as f:
        output_data = yaml.safe_load(f)

    reaction_types = [r["type"] for r in output_data["reactions"]]
    # The HCl PHASE_CHANGE should still be there (not in NH4/NO3/SO4 system)
    assert reaction_types.count("PHASE_CHANGE") == 1
    assert "EQUILIBRIUM" in reaction_types


def test_migrate_equilibrium_equilibrium_block_structure(tmp_path):
    """The inserted EQUILIBRIUM block has the correct standard structure."""
    mech_file = _make_mech_with_phase_change(tmp_path)

    with warnings.catch_warnings(record=True):
        warnings.simplefilter("always")
        result = migrate_equilibrium(str(mech_file))

    with open(result) as f:
        output_data = yaml.safe_load(f)

    eq_blocks = [r for r in output_data["reactions"] if r["type"] == "EQUILIBRIUM"]
    assert len(eq_blocks) == 1
    eq = eq_blocks[0]

    assert eq["system"] == "NH4_NO3_SO4"
    assert eq["regime_blending"] == "sigmoid"
    assert eq["transition_width"] == 0.05
    assert eq["continuous_transition"] is True
    assert "Kp_NH4NO3" in eq["equilibrium_constants"]
    assert "Kp_NH4HSO4" in eq["equilibrium_constants"]
    assert "Kp_NH42SO4" in eq["equilibrium_constants"]
    assert eq["total_species"]["reduced_nitrogen"]["gas"] == "NH3"


def test_cli_migrate_equilibrium_flag_parsed(tmp_path, capsys, monkeypatch):
    """The --migrate-equilibrium flag is parsed and passed to run_compiler."""

    mech_file = tmp_path / "mech.yaml"
    mech_file.write_text("species: [{name: O3}]\nreactions: []")
    env_file = tmp_path / "env.yaml"
    env_file.write_text("mpi: {gather_to_root: false}")

    # Capture kwargs passed to run_compiler
    captured_kwargs = []

    def mock_run_compiler(*args, **kwargs):
        captured_kwargs.append(kwargs)

    monkeypatch.setattr("mkpp.cli.run_compiler", mock_run_compiler)

    with pytest.raises(SystemExit) as e:
        main(
            [
                "compile",
                str(mech_file),
                "--test-env",
                str(env_file),
                "--migrate-equilibrium",
            ]
        )

    assert e.value.code == 0
    assert len(captured_kwargs) == 1
    assert captured_kwargs[0]["migrate_equilibrium_flag"] is True


def test_cli_migrate_equilibrium_flag_defaults_false(tmp_path, capsys, monkeypatch):
    """Without --migrate-equilibrium, flag defaults to False."""
    mech_file = tmp_path / "mech.yaml"
    mech_file.write_text("species: [{name: O3}]\nreactions: []")
    env_file = tmp_path / "env.yaml"
    env_file.write_text("mpi: {gather_to_root: false}")

    captured_kwargs = []

    def mock_run_compiler(*args, **kwargs):
        captured_kwargs.append(kwargs)

    monkeypatch.setattr("mkpp.cli.run_compiler", mock_run_compiler)

    with pytest.raises(SystemExit) as e:
        main(["compile", str(mech_file), "--test-env", str(env_file)])

    assert e.value.code == 0
    assert captured_kwargs[0]["migrate_equilibrium_flag"] is False


def test_migrate_equilibrium_prints_summary(tmp_path, capsys):
    """Migration prints a summary to stderr."""
    mech_file = _make_mech_with_phase_change(tmp_path)

    with warnings.catch_warnings(record=True):
        warnings.simplefilter("always")
        migrate_equilibrium(str(mech_file))

    captured = capsys.readouterr()
    assert "[migrate-equilibrium] Migration summary:" in captured.err
    assert "PHASE_CHANGE" in captured.err
    assert "NH4_NO3_SO4" in captured.err
