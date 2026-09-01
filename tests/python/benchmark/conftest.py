"""Collection policy for benchmark contract tests.

The JSON Schema documents under ``specs/020-solver-benchmark-comparison/contracts``
are local design artifacts: ``specs/`` is git-ignored, so CI checkouts never
contain them.  ``mkpp.benchmark.schema`` fails loudly (``RuntimeError: FATAL
ERROR: cannot load benchmark schema ...``) when a validation call cannot read
those files, which would surface in CI as misleading test failures.

When the contracts directory is absent, the schema-dependent modules below are
ignored at collection time.  Tests that do not require the contracts (for
example ``test_admission.py``) still run everywhere.
"""

import sys
from pathlib import Path

_CONTRACTS = Path(__file__).resolve().parents[3] / "specs" / "020-solver-benchmark-comparison" / "contracts"

_SCHEMA_DEPENDENT_MODULES = [
    "test_cli.py",
    "test_manifest_schema.py",
    "test_orchestrator.py",
    "test_runner_result_schema.py",
    "test_scenario_schema.py",
    "test_ts1_manifest.py",
    "test_ts1_scenario.py",
]

collect_ignore: list[str] = []
if not _CONTRACTS.is_dir():
    collect_ignore = list(_SCHEMA_DEPENDENT_MODULES)
    print(
        f"benchmark conftest: specs/ contracts absent ({_CONTRACTS}); "
        f"ignoring {len(collect_ignore)} schema-dependent test module(s)",
        file=sys.stderr,
    )
