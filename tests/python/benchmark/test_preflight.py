"""Preflight tests for safe, reproducible benchmark assets."""

from __future__ import annotations

import hashlib
from pathlib import Path

import pytest
from mkpp.benchmark.preflight import (
    PreflightError,
    resolve_relative_asset,
    verify_asset_hash,
)


def _write_asset(root: Path, relative_path: str, content: bytes = b"canonical chemistry\n") -> Path:
    asset = root / relative_path
    asset.parent.mkdir(parents=True, exist_ok=True)
    asset.write_bytes(content)
    return asset


def test_resolves_existing_relative_asset_beneath_declared_root(tmp_path: Path) -> None:
    asset = _write_asset(tmp_path, "sources/chapman/chapman.eqn")

    assert resolve_relative_asset(tmp_path, "sources/chapman/chapman.eqn") == asset.resolve()


@pytest.mark.parametrize(
    "unsafe_path",
    [
        "/etc/passwd",
        "../outside.eqn",
        "sources/../../outside.eqn",
        "~/private.eqn",
    ],
)
def test_rejects_absolute_home_and_parent_traversal_paths(tmp_path: Path, unsafe_path: str) -> None:
    with pytest.raises(PreflightError, match=r"^FATAL ERROR:.*path"):
        resolve_relative_asset(tmp_path, unsafe_path)


def test_rejects_symlink_escape_from_declared_root(tmp_path: Path) -> None:
    outside = tmp_path.parent / f"{tmp_path.name}-outside.eqn"
    outside.write_text("outside chemistry\n")
    link = tmp_path / "escaped.eqn"
    try:
        link.symlink_to(outside)
    except OSError:
        pytest.skip("filesystem does not permit symlink creation")

    with pytest.raises(PreflightError, match=r"^FATAL ERROR:.*outside"):
        resolve_relative_asset(tmp_path, "escaped.eqn")


def test_missing_relative_asset_is_a_fatal_preflight_error(tmp_path: Path) -> None:
    with pytest.raises(PreflightError, match=r"^FATAL ERROR:.*missing.eqn"):
        resolve_relative_asset(tmp_path, "sources/missing.eqn")


def test_verifies_exact_sha256_for_resolved_asset(tmp_path: Path) -> None:
    content = b"A + hv = 2 B : J1;\n"
    asset = _write_asset(tmp_path, "sources/mechanism.eqn", content)
    expected = hashlib.sha256(content).hexdigest()

    assert verify_asset_hash(asset, expected) == expected


@pytest.mark.parametrize("bad_hash", ["", "abc", "A" * 64, "g" * 64])
def test_rejects_missing_or_noncanonical_expected_hash(tmp_path: Path, bad_hash: str) -> None:
    asset = _write_asset(tmp_path, "sources/mechanism.eqn")

    with pytest.raises(PreflightError, match=r"^FATAL ERROR:.*sha256"):
        verify_asset_hash(asset, bad_hash)


def test_hash_mismatch_names_asset_expected_and_observed_digest(tmp_path: Path) -> None:
    asset = _write_asset(tmp_path, "sources/mechanism.eqn", b"changed\n")
    expected = "0" * 64
    observed = hashlib.sha256(b"changed\n").hexdigest()

    with pytest.raises(PreflightError) as caught:
        verify_asset_hash(asset, expected)

    message = str(caught.value)
    assert message.startswith("FATAL ERROR:")
    assert str(asset) in message
    assert expected in message
    assert observed in message


def test_preflight_diagnostics_never_expose_asset_contents(tmp_path: Path) -> None:
    secret_marker = "DO-NOT-ECHO-CHEMISTRY-CONTENT"
    asset = _write_asset(tmp_path, "sources/mechanism.eqn", secret_marker.encode())

    with pytest.raises(PreflightError) as caught:
        verify_asset_hash(asset, "0" * 64)

    assert secret_marker not in str(caught.value)
