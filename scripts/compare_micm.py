#!/usr/bin/env python3
"""Retired reference-only diagnostic retained to fail with clear guidance.

This program never executes MICM and therefore cannot produce a fair
MICM/MKPP comparison or a performance claim. Use ``compare_solvers.py`` for
governed native-runner evidence.
"""

from __future__ import annotations

import argparse
from collections.abc import Sequence
from pathlib import Path
from typing import Any

_MESSAGE = (
    "FATAL ERROR: scripts/compare_micm.py is a retired reference-only diagnostic; "
    "use scripts/compare_solvers.py for native solver-comparison evidence"
)


def run_micm_comparison(*, mech_path: Path, **_: Any) -> dict[str, Any]:
    """Reject the historical API without fabricating MICM evidence."""

    del mech_path
    raise RuntimeError(_MESSAGE)


def main(argv: Sequence[str] | None = None) -> int:
    """Preserve an actionable command-line failure for legacy invocations."""

    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--mechanism", type=Path, help="Ignored legacy mechanism path")
    parser.parse_args(argv)
    print(_MESSAGE)
    return 5


if __name__ == "__main__":
    raise SystemExit(main())
