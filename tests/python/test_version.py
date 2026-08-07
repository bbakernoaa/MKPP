import re
import tomllib
from pathlib import Path

import mkpp

SEMVER_REGEX = (
    r"^(0|[1-9]\d*)\.(0|[1-9]\d*)\.(0|[1-9]\d*)"
    r"(?:-((?:0|[1-9]\d*|\d*[a-zA-Z-][0-9a-zA-Z-]*)(?:\.(?:0|[1-9]\d*|\d*[a-zA-Z-][0-9a-zA-Z-]*))*))?"
    r"(?:\+([0-9a-zA-Z-]+(?:\.[0-9a-zA-Z-]+)*))?$"
)


def test_pyproject_semver():
    pyproject_path = Path(__file__).parents[2] / "pyproject.toml"
    with open(pyproject_path, "rb") as f:
        data = tomllib.load(f)
    ver = data["project"]["version"]
    assert re.match(SEMVER_REGEX, ver), f"Version '{ver}' in pyproject.toml is not valid SemVer"


def test_module_version():
    assert hasattr(mkpp, "__version__")
    assert re.match(SEMVER_REGEX, mkpp.__version__), f"__version__ '{mkpp.__version__}' is not valid SemVer"
