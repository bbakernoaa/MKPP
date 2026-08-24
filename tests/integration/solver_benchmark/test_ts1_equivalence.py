"""RED integration contracts for the mandatory MICM/MKPP TS1 track."""

from __future__ import annotations

import json
from pathlib import Path

import pytest
import yaml

from mkpp.benchmark.accuracy import assess_trajectory_accuracy
from mkpp.benchmark.admission import ChemistryObservation, compare_chemistry

ROOT = Path(__file__).resolve().parents[3]
BENCHMARK_ROOT = ROOT / "benchmarks" / "solver_comparison"
MANIFEST_PATH = BENCHMARK_ROOT / "manifests" / "ts1-v1.yaml"
SCENARIO_PATH = BENCHMARK_ROOT / "scenarios" / "ts1-measurement-v1.yaml"
MICM_TS1_BUILD = BENCHMARK_ROOT / "runners" / "micm" / "ts1" / "CMakeLists.txt"
MICM_RUNNER = BENCHMARK_ROOT / "runners" / "micm" / "main.cpp"
MKPP_RUNNER = BENCHMARK_ROOT / "runners" / "mkpp" / "main.cpp"
MKPP_BINDING = BENCHMARK_ROOT / "runners" / "mkpp" / "ts1_binding.json"
SHARED_OPENATMOS_SOURCE = BENCHMARK_ROOT / "sources" / "ts1" / "musica-config" / "ts1.json"


def _load_yaml(path: Path) -> dict[str, object]:
    assert path.is_file(), f"missing governed TS1 artifact: {path}"
    document = yaml.safe_load(path.read_text(encoding="utf-8"))
    assert isinstance(document, dict)
    return document


def _observation(scale: float = 1.0) -> ChemistryObservation:
    return ChemistryObservation(
        rate_ids=("J_NO2", "R_O3_NO", "R_HO2_NO"),
        rates=(1.0e-3 * scale, 2.0e-12 * scale, 8.0e-12 * scale),
        species_ids=("NO", "NO2", "O3"),
        rhs=(1.5e6 * scale, -1.0e6 * scale, -5.0e5 * scale),
        jacobian=(
            (-2.0e-3 * scale, 1.0e-3 * scale, -2.0e-12 * scale),
            (2.0e-3 * scale, -1.0e-3 * scale, 2.0e-12 * scale),
            (-1.0e-3 * scale, 0.0, -2.0e-12 * scale),
        ),
        thresholded_sparsity=((0, 0), (0, 1), (0, 2), (1, 0), (1, 1), (1, 2), (2, 0), (2, 2)),
        independent_jacobian=(
            (-2.0e-3 * scale, 1.0e-3 * scale, -2.0e-12 * scale),
            (2.0e-3 * scale, -1.0e-3 * scale, 2.0e-12 * scale),
            (-1.0e-3 * scale, 0.0, -2.0e-12 * scale),
        ),
    )


@pytest.mark.parametrize(
    ("solver", "source_path", "identity_tokens"),
    [
        ("micm", MICM_RUNNER, ("micm", "Solve(")),
        ("mkpp", MKPP_RUNNER, ("mkpp", "MechanismRegistry", "execute")),
    ],
)
def test_ts1_uses_real_native_solver_paths(
    solver: str, source_path: Path, identity_tokens: tuple[str, ...]
) -> None:
    assert source_path.is_file(), f"missing real {solver} runner"
    source = source_path.read_text(encoding="utf-8")
    for token in identity_tokens:
        assert token in source
    assert f'"{solver}"' in source

    if solver == "micm":
        assert MICM_TS1_BUILD.is_file(), "TS1 must bind pinned generated MICM chemistry to the real runner"
        assert "ts1" in MICM_TS1_BUILD.read_text(encoding="utf-8").lower()
    else:
        assert "ts1" in source.lower(), "MKPP runner must explicitly support the TS1 host-registry path"


def test_ts1_bindings_map_canonical_species_by_name_without_raw_index_assumptions() -> None:
    manifest = _load_yaml(MANIFEST_PATH)
    canonical_names = {species["id"] for species in manifest["canonical_species"]}
    assert len(canonical_names) == 210

    bindings = manifest["bindings"]
    assert set(bindings) == {"micm", "mkpp"}
    for solver in ("micm", "mkpp"):
        species_map = bindings[solver]["species_map"]
        assert set(species_map) == canonical_names
        assert len(set(species_map.values())) == 210
        assert all(isinstance(canonical, str) and isinstance(native, str) for canonical, native in species_map.items())
        assert not any(isinstance(native, int) for native in species_map.values())

    assert MKPP_BINDING.is_file()
    binding = json.loads(MKPP_BINDING.read_text(encoding="utf-8"))
    assert binding["species_map"] == bindings["mkpp"]["species_map"]


def test_ts1_mkpp_uses_the_same_openatmos_reaction_source_as_micm() -> None:
    """The two native paths must not drift through a separately converted YAML."""
    source = json.loads(SHARED_OPENATMOS_SOURCE.read_text(encoding="utf-8"))
    assert len(source["species"]) == 210
    assert len(source["reactions"]) == 547
    binding = json.loads(MKPP_BINDING.read_text(encoding="utf-8"))
    assert binding["source"] == str(SHARED_OPENATMOS_SOURCE.relative_to(ROOT))
    manifest = _load_yaml(MANIFEST_PATH)
    assert str(SHARED_OPENATMOS_SOURCE.relative_to(ROOT)) in manifest["bindings"]["mkpp"]["assets"]


def test_ts1_micm_and_mkpp_use_the_same_named_photolysis_forcing() -> None:
    manifest = _load_yaml(MANIFEST_PATH)
    scenario = _load_yaml(SCENARIO_PATH)
    required_forcing = {item["id"] for item in manifest["photolysis_inputs"]}
    assert required_forcing
    assert set(scenario["forcing"]) == required_forcing

    micm_map = manifest["bindings"]["micm"]["photolysis_map"]
    mkpp_map = manifest["bindings"]["mkpp"]["photolysis_map"]
    assert set(micm_map) == required_forcing
    assert set(mkpp_map) == required_forcing
    assert micm_map == mkpp_map

    for forcing_name in sorted(required_forcing):
        points = scenario["forcing"][forcing_name]["points"]
        assert any(point["value"] > 0.0 for point in points)


@pytest.mark.parametrize("solver", ["micm", "mkpp"])
def test_ts1_rate_rhs_and_jacobian_parity_seams_are_independently_eligible(solver: str) -> None:
    canonical = _observation()
    subject = _observation(1.0 + 1.0e-13)

    assessment = compare_chemistry(
        reference=canonical,
        subject=subject,
        physics_floors={"rates": 1.0e-20, "rhs": 1.0e-2, "jacobian": 1.0e-18},
    )

    assert assessment.eligible, f"{solver} TS1 chemistry parity failed: {assessment.reasons}"
    assert assessment.rate_metrics.maximum <= 1.0
    assert assessment.rhs_metrics.wrms <= 0.1
    assert assessment.jacobian_metrics.maximum <= 1.0
    assert assessment.sparsity_matches
    assert assessment.independent_jacobian_maximum <= 10.0


@pytest.mark.parametrize("solver", ["micm", "mkpp"])
def test_ts1_named_checkpoint_trajectory_passes_shared_accuracy_budget(solver: str) -> None:
    reference = {
        0: {
            60.0: {"NO": 1.0e10, "NO2": 2.0e10, "O3": 8.0e11},
            600.0: {"NO": 1.2e10, "NO2": 1.8e10, "O3": 7.9e11},
        }
    }
    subject = {
        0: {
            checkpoint: {name: value * (1.0 + 1.0e-8) for name, value in state.items()}
            for checkpoint, state in reference[0].items()
        }
    }

    result = assess_trajectory_accuracy(
        subject,
        reference,
        atol_by_species={"NO": 1.0e4, "NO2": 1.0e4, "O3": 1.0e5},
        rtol=1.0e-6,
    )

    assert result.eligible, f"{solver} TS1 checkpoint accuracy failed: {result.diagnostics}"
    assert {error.species_id for error in result.scaled_errors} == {"NO", "NO2", "O3"}
    assert {error.checkpoint_seconds for error in result.scaled_errors} == {60.0, 600.0}
