#!/usr/bin/env python3
"""Convert legacy MKPP YAML chemistry into canonical OpenAtmos JSON.

The legacy YAML is migration input only.  The emitted JSON retains every
species role, stoichiometric coefficient, rate-law parameter, and reaction
ordering.  Photolysis expressions become named host forcing inputs: a host must
evaluate the recorded legacy expression (for example ``A * SUN * SUN``) and
supply that value under the emitted forcing name.
"""

from __future__ import annotations

import argparse
import hashlib
import json
from collections.abc import Mapping, Sequence
from pathlib import Path
from typing import Any

import yaml


def _terms(values: Mapping[str, Any]) -> list[dict[str, Any]]:
    return [
        {"species name": str(name), "coefficient": float(coefficient)}
        for name, coefficient in values.items()
    ]


def convert(document: Mapping[str, Any], source_name: str, source_sha256: str) -> dict[str, Any]:
    """Return one OpenAtmos mechanism document without changing rate semantics."""

    species = []
    for entry in document.get("species", ()):  # type: ignore[union-attr]
        converted = {"name": str(entry["name"])}
        if entry.get("type"):
            converted["type"] = str(entry["type"])
        species.append(converted)

    reactions = []
    photolysis_forcing: dict[str, str] = {}
    ignored = {"type", "reactants", "products", "stiff", "continuous_transition"}
    for index, reaction in enumerate(document.get("reactions", ())):  # type: ignore[union-attr]
        converted: dict[str, Any] = {
            "type": str(reaction["type"]),
            "reactants": _terms(reaction.get("reactants", {})),
            "products": _terms(reaction.get("products", {})),
            "gas phase": "gas",
        }
        if converted["type"].upper() == "PHOTOLYSIS":
            forcing_name = f"j_{source_name}_{index:04d}"
            converted["name"] = forcing_name
            converted["scaling factor"] = 1.0
            photolysis_forcing[forcing_name] = str(reaction.get("A", "1.0"))
        else:
            for key, value in reaction.items():
                if key not in ignored:
                    converted[key] = value
        reactions.append(converted)

    return {
        "name": str(document["name"]),
        "description": str(document.get("description", "")),
        "phases": [{"name": "gas"}],
        "species": species,
        "reactions": reactions,
        "metadata": {
            "migration": "legacy-mkpp-yaml-to-openatmos-v1",
            "mkpp_mechanism_id": Path(source_name).stem,
            "legacy_source": source_name,
            "legacy_source_sha256": source_sha256,
            "photolysis_host_forcing_expressions": photolysis_forcing,
        },
    }


def main(argv: Sequence[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("source", type=Path)
    parser.add_argument("--output", required=True, type=Path)
    args = parser.parse_args(argv)
    source_bytes = args.source.read_bytes()
    document = yaml.safe_load(source_bytes)
    if not isinstance(document, Mapping) or "name" not in document:
        raise SystemExit("legacy YAML must be a mechanism object with a name")
    converted = convert(document, args.source.name, hashlib.sha256(source_bytes).hexdigest())
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(converted, indent=2, sort_keys=True) + "\n", encoding="utf-8")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
