"""Content-addressable cache for MKPP lowering results."""

import hashlib
import pickle
from dataclasses import dataclass
from pathlib import Path
from typing import Any, List, Optional, Tuple

import importlib.metadata


@dataclass
class CacheKey:
    """Identifies a unique compilation input."""

    yaml_hash: str  # SHA-256 hex digest of file contents
    mkpp_version: str  # package version string


@dataclass
class CacheEntry:
    """Stores all expensive lowering results for a given input."""

    key: CacheKey
    species_map: List[str]
    jacobian_matrix: Any  # sp.Matrix (pickled)
    lu_plan: Any  # SymbolicLUPlan
    f_implicit: Any  # sp.Matrix
    f_explicit: Any  # sp.Matrix
    cse_replacements: Optional[List[Tuple[Any, Any]]] = None
    cse_reduced: Optional[List[Any]] = None


class CacheManager:
    """Content-addressable disk cache for lowering artifacts.

    Cache files live under ``cache_dir`` (default ``.mkpp_cache/``) and are
    keyed by the first 16 hex characters of the SHA-256 of the input YAML
    concatenated with the MKPP version string.
    """

    def __init__(self, cache_dir: Path = Path(".mkpp_cache")):
        self.cache_dir = cache_dir

    def compute_key(self, yaml_path: Path) -> CacheKey:
        """SHA-256 of file contents + MKPP version string."""
        file_bytes = yaml_path.read_bytes()
        try:
            version = importlib.metadata.version("mkpp")
        except importlib.metadata.PackageNotFoundError:
            version = "dev"
        hash_input = file_bytes + version.encode()
        yaml_hash = hashlib.sha256(hash_input).hexdigest()
        return CacheKey(yaml_hash=yaml_hash, mkpp_version=version)

    def lookup(self, key: CacheKey) -> Optional[CacheEntry]:
        """Return deserialized entry or None. Handle corruption gracefully."""
        path = self._key_to_path(key)
        if not path.exists():
            return None
        try:
            with open(path, "rb") as f:
                entry = pickle.load(f)
            if not isinstance(entry, CacheEntry):
                path.unlink()
                return None
            return entry
        except (
            pickle.UnpicklingError,
            EOFError,
            AttributeError,
            ModuleNotFoundError,
        ):
            path.unlink(missing_ok=True)
            return None

    def store(self, key: CacheKey, entry: CacheEntry) -> Path:
        """Serialize with pickle, return cache file path."""
        self.cache_dir.mkdir(parents=True, exist_ok=True)
        path = self._key_to_path(key)
        with open(path, "wb") as f:
            pickle.dump(entry, f, protocol=pickle.HIGHEST_PROTOCOL)
        return path

    def _key_to_path(self, key: CacheKey) -> Path:
        return self.cache_dir / f"{key.yaml_hash[:16]}.pkl"
