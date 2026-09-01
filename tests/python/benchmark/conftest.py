"""Skip policy for benchmark contract tests that need local-only schemas.

The JSON Schema documents under ``specs/020-solver-benchmark-comparison/contracts``
are local design artifacts: ``specs/`` is git-ignored, so CI checkouts never
contain them.  ``mkpp.benchmark.schema`` fails loudly (``RuntimeError: FATAL
ERROR: cannot load benchmark schema ...``) when a validation call cannot read
those files, which would surface in CI as misleading test failures.

``pytest_collection_modifyitems`` is used instead of ``collect_ignore`` because
the CTest smoke target invokes pytest with explicit file paths, which bypass
directory-level ignore rules.  Tests that do not require the contracts (for
example ``test_admission.py``) still run everywhere.
"""

from pathlib import Path

import pytest

_CONTRACTS = Path(__file__).resolve().parents[3] / "specs" / "020-solver-benchmark-comparison" / "contracts"

_SCHEMA_DEPENDENT_FILES = frozenset(
    {
        "test_cli.py",
        "test_manifest_schema.py",
        "test_orchestrator.py",
        "test_runner_result_schema.py",
        "test_scenario_schema.py",
        "test_ts1_manifest.py",
        "test_ts1_scenario.py",
    }
)

_SKIP_REASON = "local-only specs/020 contract schemas absent from this checkout (specs/ is git-ignored)"


def pytest_collection_modifyitems(config, items):
    if _CONTRACTS.is_dir():
        return
    skip = pytest.mark.skip(reason=_SKIP_REASON)
    for item in items:
        # ``item.path`` is the stable pathlib attribute (``item.fspath`` was
        # removed in pytest 8; CI runs pytest 9).
        if Path(item.path).name in _SCHEMA_DEPENDENT_FILES:
            item.add_marker(skip)
