"""The checked-in chemistry catalog is complete OpenAtmos input."""

from __future__ import annotations

import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT))


def _openatmos(name: str) -> dict:
    source = ROOT / "mechanisms" / "openatmos" / name / "mechanism.json"
    return json.loads(source.read_text(encoding="utf-8"))


def test_small_strato_is_openatmos_with_named_host_forcing() -> None:
    openatmos = _openatmos("small_strato")
    assert len(openatmos["species"]) == 7
    assert len(openatmos["reactions"]) == 10
    forcing = openatmos["metadata"]["photolysis_host_forcing_expressions"]
    assert any("SUN" in expression for expression in forcing.values())


def test_saprc99_is_openatmos_with_fixed_roles_and_complex_rate_laws() -> None:
    openatmos = _openatmos("saprc99")
    fixed = {species["name"] for species in openatmos["species"] if species.get("type") == "FIXED"}
    rate_laws = {reaction["type"] for reaction in openatmos["reactions"]}
    assert {"M", "N2", "RO2"} <= fixed
    assert {"TROE", "EP2", "EP3"} <= rate_laws
    assert len(openatmos["reactions"]) == 211
