"""RED admission contracts for the canonical TS1 mechanism manifest."""

from __future__ import annotations

from copy import deepcopy

import pytest

from mkpp.benchmark.manifest import validate_manifest

SHA_A = "a" * 64
SHA_B = "b" * 64


def _without_reaction_contract(manifest: dict) -> dict:
    """Exercise existing cross-field rules without masking on the RED reaction field."""

    copy = deepcopy(manifest)
    del copy["reactions"]
    return copy


@pytest.fixture
def ts1_manifest() -> dict:
    species = [
        {
            "id": f"S{i:03d}",
            "role": "active",
            "phase": "gas",
            "unit": "molecule cm-3",
            "scale": 1.0e8,
            "aliases": [f"TS1_{i:03d}"],
        }
        for i in range(210)
    ]
    species[4].update(id="O2", role="fixed", aliases=["molecular_oxygen"])
    species[10].update(id="N2", role="fixed", aliases=["molecular_nitrogen"])
    reactions = [
        {
            "id": f"R{i:03d}",
            "reactants": [{"species_id": species[i % 210]["id"], "coefficient": 1.0}],
            "products": [{"species_id": species[(i + 1) % 210]["id"], "coefficient": 1.0}],
            "rate_law_id": "ARR",
            "rate_scale": 1.0e-12,
        }
        for i in range(547)
    ]
    canonical_ids = [entry["id"] for entry in species]
    return {
        "schema_version": 1,
        "mechanism_id": "ts1",
        "version": "1.0.0",
        "canonical_source": [
            {"path": "sources/ts1/ts1.json", "revision": "musica-ts1-v1", "sha256": SHA_A}
        ],
        "canonical_species": species,
        "reactions": reactions,
        "chemistry_sha256": SHA_B,
        "photolysis_inputs": [
            {"id": "J_NO2", "unit": "s-1"},
            {"id": "J_O3_A", "unit": "s-1"},
            {"id": "J_O3_B", "unit": "s-1"},
        ],
        "required_solvers": ["micm", "mkpp"],
        "bindings": {
            solver: {
                "revision": f"{solver}-ts1-pinned",
                "assets": [f"bindings/{solver}/ts1"],
                "species_map": {name: f"{solver}_{name}" for name in canonical_ids},
                "photolysis_map": {
                    "J_NO2": f"{solver}_J_NO2",
                    "J_O3_A": f"{solver}_J_O3_A",
                    "J_O3_B": f"{solver}_J_O3_B",
                },
                "evidence": [f"audits/{solver}-ts1.json"],
            }
            for solver in ("micm", "mkpp")
        },
        "admission_status": "draft",
    }


def test_complete_ts1_manifest_has_exact_scientific_dimensions(ts1_manifest: dict) -> None:
    validate_manifest(ts1_manifest)

    assert len(ts1_manifest["canonical_species"]) == 210
    assert len(ts1_manifest["reactions"]) == 547


def test_ts1_rejects_wrong_species_count(ts1_manifest: dict) -> None:
    manifest = deepcopy(ts1_manifest)
    removed = manifest["canonical_species"].pop()["id"]
    for binding in manifest["bindings"].values():
        del binding["species_map"][removed]

    with pytest.raises(ValueError, match="210"):
        validate_manifest(manifest)


def test_ts1_rejects_wrong_reaction_count(ts1_manifest: dict) -> None:
    manifest = deepcopy(ts1_manifest)
    manifest["reactions"].pop()

    with pytest.raises(ValueError, match="547"):
        validate_manifest(manifest)


def test_ts1_active_species_maps_are_bijective(ts1_manifest: dict) -> None:
    manifest = _without_reaction_contract(ts1_manifest)
    active = [species["id"] for species in manifest["canonical_species"] if species["role"] == "active"]
    manifest["bindings"]["micm"]["species_map"][active[1]] = manifest["bindings"]["micm"][
        "species_map"
    ][active[0]]

    with pytest.raises(ValueError, match="bijective|mapping"):
        validate_manifest(manifest)


@pytest.mark.parametrize(("field", "value"), [("role", "background"), ("phase", "")])
def test_ts1_rejects_invalid_species_role_or_phase(
    ts1_manifest: dict, field: str, value: str
) -> None:
    manifest = _without_reaction_contract(ts1_manifest)
    manifest["canonical_species"][0][field] = value

    with pytest.raises(ValueError, match=f"{field}|species"):
        validate_manifest(manifest)


def test_ts1_requires_complete_named_photolysis_mapping(ts1_manifest: dict) -> None:
    manifest = _without_reaction_contract(ts1_manifest)
    del manifest["bindings"]["mkpp"]["photolysis_map"]["J_O3_B"]

    with pytest.raises(ValueError, match="photolysis|J_O3_B"):
        validate_manifest(manifest)


@pytest.mark.parametrize("location", ["required_solvers", "bindings"])
def test_ts1_explicitly_forbids_kpp(ts1_manifest: dict, location: str) -> None:
    manifest = _without_reaction_contract(ts1_manifest)
    if location == "required_solvers":
        manifest[location].append("kpp")
    else:
        manifest[location]["kpp"] = deepcopy(manifest[location]["micm"])

    with pytest.raises(ValueError, match="TS1|ts1|KPP|kpp"):
        validate_manifest(manifest)


def test_ts1_requires_exactly_micm_and_mkpp(ts1_manifest: dict) -> None:
    manifest = _without_reaction_contract(ts1_manifest)
    manifest["required_solvers"] = ["micm"]

    with pytest.raises(ValueError, match="MICM|micm|MKPP|mkpp|exactly"):
        validate_manifest(manifest)
