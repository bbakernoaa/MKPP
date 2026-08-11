"""Python integration test wrapper for compiled C++ validation.

Orchestrates:
  1. Generate the Chapman header using mkpp's generate_headers
  2. CMake configure the test project in tests/integration/e2e_validation/
  3. Build the test executable
  4. Run CTest to validate solver output against SciPy reference

Validates: Requirements 8.2, 8.3, 8.4
"""

import os
import shutil
import subprocess
from pathlib import Path

import pytest

# Project root is two levels up from this file's directory (tests/python/)
PROJECT_ROOT = Path(__file__).resolve().parent.parent.parent
E2E_DIR = PROJECT_ROOT / "tests" / "integration" / "e2e_validation"
GENERATED_DIR = PROJECT_ROOT / "mkpp-generated"


def _kokkos_available() -> bool:
    """Check if Kokkos is available for compilation.

    Checks:
    1. Kokkos_DIR environment variable is set and points to a valid directory
    2. cmake can find the Kokkos package via a dry-run configure
    """
    # Check environment variable first (fast path)
    kokkos_dir = os.environ.get("Kokkos_DIR", "")
    if kokkos_dir and Path(kokkos_dir).is_dir():
        return True

    # Fallback: try a minimal cmake find_package check
    cmake = shutil.which("cmake")
    if cmake is None:
        return False

    try:
        result = subprocess.run(
            [
                cmake,
                "--find-package",
                "-DNAME=Kokkos",
                "-DCOMPILER_ID=GNU",
                "-DLANGUAGE=CXX",
                "-DMODE=EXIST",
            ],
            capture_output=True,
            text=True,
            timeout=30,
        )
        return result.returncode == 0
    except (subprocess.TimeoutExpired, OSError):
        return False


@pytest.mark.slow
class TestCompiledValidation:
    """End-to-end compiled C++ validation of generated MKPP headers."""

    @pytest.fixture(autouse=True)
    def _skip_without_kokkos(self):
        """Skip all tests in this class when Kokkos is not available."""
        if not _kokkos_available():
            pytest.skip(
                "Kokkos not found: set Kokkos_DIR environment variable or "
                "ensure Kokkos CMake package is installed. "
                "Compiled integration tests require Kokkos for GPU/CPU execution."
            )

    @pytest.fixture
    def build_dir(self, tmp_path):
        """Provide a clean temporary build directory."""
        build = tmp_path / "build"
        build.mkdir()
        return build

    def _generate_chapman_header(self):
        """Generate Chapman header using mkpp's generate_headers."""
        from mkpp.codegen import generate_headers
        from mkpp.parser import load_mechanism

        mech_yaml = E2E_DIR / "data" / "chapman.yaml"
        mech = load_mechanism(str(mech_yaml))
        result = generate_headers(mech, out_dir=str(GENERATED_DIR))
        header_path = Path(result["header"])
        assert header_path.exists(), f"Chapman header was not generated at expected path: {header_path}"
        return header_path

    def _cmake_configure(self, build_dir: Path) -> subprocess.CompletedProcess:
        """Run CMake configure step for the e2e validation project."""
        cmd = [
            "cmake",
            "-S",
            str(PROJECT_ROOT),
            "-B",
            str(build_dir),
            "-DBUILD_TESTING=ON",
            "-DCMAKE_BUILD_TYPE=Release",
        ]

        # Pass Kokkos_DIR if set in environment
        kokkos_dir = os.environ.get("Kokkos_DIR")
        if kokkos_dir:
            cmd.append(f"-DKokkos_DIR={kokkos_dir}")

        result = subprocess.run(
            cmd,
            capture_output=True,
            text=True,
            timeout=120,
            cwd=str(PROJECT_ROOT),
        )
        return result

    def _cmake_build(self, build_dir: Path, target: str = None) -> subprocess.CompletedProcess:
        """Run CMake build step."""
        cmd = ["cmake", "--build", str(build_dir), "--config", "Release", "--parallel"]
        if target:
            cmd.extend(["--target", target])

        result = subprocess.run(
            cmd,
            capture_output=True,
            text=True,
            timeout=300,
            cwd=str(PROJECT_ROOT),
        )
        return result

    def _run_ctest(self, build_dir: Path, test_name: str = None) -> subprocess.CompletedProcess:
        """Run CTest to execute compiled tests."""
        cmd = ["ctest", "--test-dir", str(build_dir), "--output-on-failure"]
        if test_name:
            cmd.extend(["-R", test_name])

        result = subprocess.run(
            cmd,
            capture_output=True,
            text=True,
            timeout=120,
            cwd=str(build_dir),
        )
        return result

    def test_chapman_header_compiles(self, build_dir):
        """Verify that the generated Chapman header compiles successfully.

        This test exercises the full pipeline:
        1. Generate Chapman .hpp via template engine
        2. CMake configure with BUILD_TESTING=ON
        3. Build the e2e_chapman_runner target
        4. Report compile errors on failure
        """
        # Step 1: Generate the Chapman header
        self._generate_chapman_header()

        # Step 2: CMake configure
        configure_result = self._cmake_configure(build_dir)
        assert configure_result.returncode == 0, (
            f"CMake configure failed:\n" f"STDOUT:\n{configure_result.stdout}\n" f"STDERR:\n{configure_result.stderr}"
        )

        # Step 3: Build the Chapman test target
        build_result = self._cmake_build(build_dir, target="e2e_chapman_runner")
        if build_result.returncode != 0:
            # Report compilation errors with full context
            pytest.fail(
                f"Chapman header compilation failed.\n\n"
                f"BUILD STDOUT:\n{build_result.stdout}\n\n"
                f"BUILD STDERR:\n{build_result.stderr}\n\n"
                f"This indicates the generated C++ header has syntax or "
                f"type errors. Check mkpp-generated/chapman.hpp."
            )

    def test_scipy_validation_passes(self, build_dir):
        """Run the full compiled validation against SciPy reference.

        Orchestrates the end-to-end pipeline:
        1. Generate Chapman header
        2. CMake configure + build test_scipy_validation
        3. Run CTest mkpp_scipy_validation test
        4. Validate solver output matches SciPy Radau reference
        """
        # Step 1: Generate the Chapman header
        self._generate_chapman_header()

        # Step 2: CMake configure
        configure_result = self._cmake_configure(build_dir)
        assert configure_result.returncode == 0, (
            f"CMake configure failed:\n" f"STDOUT:\n{configure_result.stdout}\n" f"STDERR:\n{configure_result.stderr}"
        )

        # Step 3: Build the scipy validation test target
        build_result = self._cmake_build(build_dir, target="test_scipy_validation")
        if build_result.returncode != 0:
            pytest.fail(
                f"Build failed. Compilation errors:\n\n" f"STDOUT:\n{build_result.stdout}\n\n" f"STDERR:\n{build_result.stderr}"
            )

        # Step 4: Run CTest for scipy validation
        ctest_result = self._run_ctest(build_dir, test_name="mkpp_scipy_validation")
        assert ctest_result.returncode == 0, (
            f"CTest mkpp_scipy_validation failed:\n" f"STDOUT:\n{ctest_result.stdout}\n" f"STDERR:\n{ctest_result.stderr}"
        )
