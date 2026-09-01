"""Contract tests for canonical solver-comparison manifests."""

from __future__ import annotations

from copy import deepcopy

import pytest
from mkpp.benchmark.manifest import validate_manifest

SHA_A = "a" * 64
SHA_B = "b" * 64


@pytest.fixture
def valid_manifest() -> dict:
    return {
        "schema_version": 1,
        "mechanism_id": "chapman",
        "version": "1.0.0",
        "canonical_source": [{"path": "sources/chapman/mechanism.yaml", "revision": "v1", "sha256": SHA_A}],
        "canonical_species": [
            {
                "id": "O",
                "role": "active",
                "phase": "gas",
                "unit": "molecule cm-3",
                "scale": 1.0e10,
                "aliases": ["O3P"],
            },
            {
                "id": "O2",
                "role": "fixed",
                "phase": "gas",
                "unit": "molecule cm-3",
                "scale": 5.0e18,
                "aliases": ["oxygen"],
            },
        ],
        "chemistry_sha256": SHA_B,
        "photolysis_inputs": [{"id": "J_O2", "unit": "s-1"}],
        "required_solvers": ["micm", "kpp", "mkpp"],
        "bindings": {
            solver: {
                "revision": f"{solver}-pinned-revision",
                "assets": [f"bindings/{solver}/chapman"],
                "species_map": {"O": "O", "O2": "O2"},
                "photolysis_map": {"J_O2": "J_O2"},
                "evidence": [f"audits/{solver}-chapman.json"],
            }
            for solver in ("micm", "kpp", "mkpp")
        },
        "admission_status": "draft",
    }


def test_valid_manifest_is_accepted(valid_manifest: dict) -> None:
    validate_manifest(valid_manifest)


@pytest.mark.parametrize("bad_hash", ["abc", "A" * 64, "g" * 64, "a" * 63])
def test_manifest_rejects_invalid_hashes(valid_manifest: dict, bad_hash: str) -> None:
    manifest = deepcopy(valid_manifest)
    manifest["chemistry_sha256"] = bad_hash
    with pytest.raises(ValueError, match="sha256|hash"):
        validate_manifest(manifest)


def test_manifest_rejects_alias_collision(valid_manifest: dict) -> None:
    manifest = deepcopy(valid_manifest)
    manifest["canonical_species"][1]["aliases"] = ["O3P"]
    with pytest.raises(ValueError, match="alias|O3P"):
        validate_manifest(manifest)


@pytest.mark.parametrize("field,value", [("role", "background"), ("unit", ""), ("scale", 0.0)])
def test_manifest_rejects_invalid_species_metadata(valid_manifest: dict, field: str, value: object) -> None:
    manifest = deepcopy(valid_manifest)
    manifest["canonical_species"][0][field] = value
    with pytest.raises(ValueError, match=f"{field}|species"):
        validate_manifest(manifest)


def test_manifest_rejects_missing_required_solver_binding(valid_manifest: dict) -> None:
    manifest = deepcopy(valid_manifest)
    del manifest["bindings"]["kpp"]
    with pytest.raises(ValueError, match="binding|kpp"):
        validate_manifest(manifest)


def test_manifest_rejects_non_bijective_active_species_map(valid_manifest: dict) -> None:
    manifest = deepcopy(valid_manifest)
    manifest["canonical_species"][1]["role"] = "active"
    manifest["bindings"]["micm"]["species_map"] = {"O": "X", "O2": "X"}
    with pytest.raises(ValueError, match="bijective|species_map|mapping"):
        validate_manifest(manifest)


def test_ts1_forbids_kpp_requirement_or_binding(valid_manifest: dict) -> None:
    manifest = deepcopy(valid_manifest)
    manifest["mechanism_id"] = "ts1"
    manifest["required_solvers"] = ["micm", "mkpp"]
    manifest["bindings"] = {solver: manifest["bindings"][solver] for solver in ("micm", "mkpp")}
    validate_manifest(manifest)

    manifest["required_solvers"].append("kpp")
    manifest["bindings"]["kpp"] = deepcopy(valid_manifest["bindings"]["kpp"])
    with pytest.raises(ValueError, match="TS1|ts1|KPP|kpp"):
        validate_manifest(manifest)


def test_manifest_rejects_unknown_fields(valid_manifest: dict) -> None:
    manifest = deepcopy(valid_manifest)
    manifest["unexpected"] = True
    with pytest.raises(ValueError, match="unexpected|additional|unknown"):
        validate_manifest(manifest)
