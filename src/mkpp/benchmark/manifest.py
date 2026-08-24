"""Semantic validation and canonical identity helpers for mechanism manifests."""

from __future__ import annotations

import hashlib
import json
from collections.abc import Mapping
from pathlib import PurePosixPath
from typing import Any

from mkpp.benchmark.schema import SchemaValidationError
from mkpp.benchmark.schema import validate_manifest as validate_manifest_schema

_SOLVERS = frozenset({"micm", "kpp", "mkpp"})
_UNPINNED_REVISIONS = frozenset({"head", "latest", "main", "master", "tip", "unpinned"})


def canonical_sha256(document: Mapping[str, Any]) -> str:
    """Return a stable SHA-256 digest for a JSON-compatible document."""

    payload = json.dumps(
        document,
        allow_nan=False,
        ensure_ascii=False,
        separators=(",", ":"),
        sort_keys=True,
    ).encode("utf-8")
    return hashlib.sha256(payload).hexdigest()


def _require_text(value: Any, location: str) -> str:
    if not isinstance(value, str) or not value.strip():
        raise SchemaValidationError(f"{location}: value must be a non-empty string")
    return value


def _require_pinned_revision(value: Any, location: str) -> None:
    revision = _require_text(value, location)
    if revision.strip().lower() in _UNPINNED_REVISIONS:
        raise SchemaValidationError(f"{location}: revision must be pinned, not {revision!r}")


def _require_relative_path(value: Any, location: str) -> None:
    text = _require_text(value, location)
    path = PurePosixPath(text.replace("\\", "/"))
    if path.is_absolute() or ".." in path.parts:
        raise SchemaValidationError(f"{location}: asset path must be repository-relative and may not contain '..'")


def _validate_species(manifest: Mapping[str, Any]) -> tuple[set[str], set[str]]:
    canonical_ids: set[str] = set()
    all_names: dict[str, str] = {}
    active_ids: set[str] = set()

    for index, species in enumerate(manifest["canonical_species"]):
        location = f"canonical_species.{index}"
        species_id = _require_text(species["id"], f"{location}.id")
        _require_text(species["phase"], f"{location}.phase")
        _require_text(species["unit"], f"{location}.unit")
        if species_id in canonical_ids:
            raise SchemaValidationError(f"{location}.id: duplicate canonical species {species_id!r}")
        canonical_ids.add(species_id)
        if species["role"] == "active":
            active_ids.add(species_id)

        for name in (species_id, *species.get("aliases", ())):
            _require_text(name, f"{location}.aliases")
            owner = all_names.get(name)
            if owner is not None:
                raise SchemaValidationError(
                    f"{location}.aliases: alias/name {name!r} collides with canonical species {owner!r}"
                )
            all_names[name] = species_id

    return canonical_ids, active_ids


def _validate_bindings(
    manifest: Mapping[str, Any], canonical_ids: set[str], active_ids: set[str]
) -> None:
    bindings = manifest["bindings"]
    required_solvers = set(manifest["required_solvers"])
    missing = required_solvers - set(bindings)
    if missing:
        raise SchemaValidationError(f"bindings: missing required solver binding(s): {', '.join(sorted(missing))}")

    unknown_solvers = set(bindings) - _SOLVERS
    if unknown_solvers:
        raise SchemaValidationError(f"bindings: unknown solver binding(s): {', '.join(sorted(unknown_solvers))}")

    photolysis_ids = {entry["id"] for entry in manifest["photolysis_inputs"]}
    for solver, binding in bindings.items():
        location = f"bindings.{solver}"
        _require_pinned_revision(binding["revision"], f"{location}.revision")
        for index, asset in enumerate(binding["assets"]):
            if isinstance(asset, str):
                _require_relative_path(asset, f"{location}.assets.{index}")
            elif isinstance(asset, Mapping) and "path" in asset:
                _require_relative_path(asset["path"], f"{location}.assets.{index}.path")
            else:
                raise SchemaValidationError(f"{location}.assets.{index}: asset must identify a relative path")

        species_map = binding["species_map"]
        unknown_species = set(species_map) - canonical_ids
        if unknown_species:
            raise SchemaValidationError(
                f"{location}.species_map: unknown canonical species: {', '.join(sorted(unknown_species))}"
            )
        missing_active = active_ids - set(species_map)
        if missing_active:
            raise SchemaValidationError(
                f"{location}.species_map: missing active species: {', '.join(sorted(missing_active))}"
            )
        active_native = [species_map[species_id] for species_id in sorted(active_ids)]
        if any(not isinstance(name, str) or not name.strip() for name in active_native):
            raise SchemaValidationError(f"{location}.species_map: native species names must be non-empty")
        if len(active_native) != len(set(active_native)):
            raise SchemaValidationError(f"{location}.species_map: active mapping must be bijective")

        photolysis_map = binding["photolysis_map"]
        if set(photolysis_map) != photolysis_ids:
            raise SchemaValidationError(
                f"{location}.photolysis_map: mapping keys must exactly match named photolysis inputs"
            )
        native_photolysis = list(photolysis_map.values())
        if any(not isinstance(name, str) or not name.strip() for name in native_photolysis):
            raise SchemaValidationError(f"{location}.photolysis_map: native names must be non-empty")
        if len(native_photolysis) != len(set(native_photolysis)):
            raise SchemaValidationError(f"{location}.photolysis_map: mapping must be bijective")


def _validate_reactions(manifest: Mapping[str, Any], canonical_ids: set[str]) -> None:
    reaction_ids: set[str] = set()
    for index, reaction in enumerate(manifest.get("reactions", ())):
        location = f"reactions.{index}"
        reaction_id = _require_text(reaction["id"], f"{location}.id")
        if reaction_id in reaction_ids:
            raise SchemaValidationError(f"{location}.id: duplicate reaction {reaction_id!r}")
        reaction_ids.add(reaction_id)
        for side in ("reactants", "products"):
            for term_index, term in enumerate(reaction[side]):
                species_id = term["species_id"]
                if species_id not in canonical_ids:
                    raise SchemaValidationError(
                        f"{location}.{side}.{term_index}: unknown canonical species {species_id!r}"
                    )


def validate_manifest(document: Mapping[str, Any]) -> Mapping[str, Any]:
    """Validate structural and cross-field mechanism-manifest invariants."""

    validate_manifest_schema(document)

    for index, source in enumerate(document["canonical_source"]):
        location = f"canonical_source.{index}"
        _require_relative_path(source["path"], f"{location}.path")
        _require_pinned_revision(source["revision"], f"{location}.revision")

    for index, photo in enumerate(document["photolysis_inputs"]):
        _require_text(photo["id"], f"photolysis_inputs.{index}.id")
        _require_text(photo["unit"], f"photolysis_inputs.{index}.unit")

    canonical_ids, active_ids = _validate_species(document)
    if document["mechanism_id"].lower() == "ts1" and "reactions" in document:
        if len(document["canonical_species"]) != 210:
            raise SchemaValidationError("TS1: canonical manifest must contain exactly 210 species")
        if len(document["reactions"]) != 547:
            raise SchemaValidationError("TS1: canonical manifest must contain exactly 547 reactions")
    _validate_reactions(document, canonical_ids)
    _validate_bindings(document, canonical_ids, active_ids)

    if document["mechanism_id"].lower() == "ts1":
        if "kpp" in document["required_solvers"] or "kpp" in document["bindings"]:
            raise SchemaValidationError("TS1: KPP is forbidden until a separately admitted KPP binding exists")
        if set(document["required_solvers"]) != {"micm", "mkpp"}:
            raise SchemaValidationError("TS1: required solvers must be exactly MICM and MKPP")

    return document


__all__ = ["canonical_sha256", "validate_manifest"]
