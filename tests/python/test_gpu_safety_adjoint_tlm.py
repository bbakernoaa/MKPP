"""
GPU safety assertions for adjoint/TLM generated code.

**Validates: Requirements 8.1, 6.3**

Verifies:
1. No heap allocation (new, malloc, std::vector) in generated adjoint/TLM code
2. No I/O (std::cout, printf) in generated adjoint/TLM code
3. No exceptions (throw, std::exception) in generated adjoint/TLM code
4. KOKKOS_INLINE_FUNCTION annotation present on all adjoint/TLM functions
5. Existing integrate() output is unchanged when --adjoint is enabled (no regression)

These are static code analysis tests (not runtime). They exercise the code generator
for all 5 Rosenbrock solver variants.
"""

import re

import pytest
from mkpp.codegen import SOLVER_COEFFICIENTS, generate_headers
from mkpp.parser import load_mechanism

ALL_SOLVERS = list(SOLVER_COEFFICIENTS.keys())

# Forbidden patterns for GPU-safe code (Req 8.1)
FORBIDDEN_PATTERNS = [
    ("new ", "heap allocation via 'new'"),
    ("malloc", "heap allocation via 'malloc'"),
    ("std::vector", "heap allocation via 'std::vector'"),
    ("std::cout", "I/O via 'std::cout'"),
    ("printf", "I/O via 'printf'"),
    ("throw", "exception via 'throw'"),
    ("std::exception", "exception handling via 'std::exception'"),
]


# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------


def _load_chapman():
    """Load the Chapman mechanism for testing."""
    return load_mechanism("mechanisms/chapman.yaml")


def _generate_adjoint_code(mech, solver_name: str, tmp_dir: str) -> str:
    """Generate the C++ header with adjoint=True."""
    results = generate_headers(mech, out_dir=tmp_dir, solver_name=solver_name, adjoint=True)
    with open(results["header"]) as f:
        return f.read()


def _generate_forward_only_code(mech, solver_name: str, tmp_dir: str) -> str:
    """Generate the C++ header with adjoint=False (forward-only)."""
    results = generate_headers(mech, out_dir=tmp_dir, solver_name=solver_name, adjoint=False)
    with open(results["header"]) as f:
        return f.read()


def _extract_function_body(code: str, func_name: str) -> str:
    """Extract the body of a function from generated C++ code.

    Finds the function by matching 'void|int <func_name>(' and returns everything
    from the opening brace of the function body to its matching closing brace.
    """
    pattern = re.compile(rf"\b(?:int|void)\s+{re.escape(func_name)}\s*\(", re.DOTALL)
    match = pattern.search(code)
    if not match:
        return ""

    pos = match.start()
    brace_start = code.index("{", pos)

    depth = 0
    for i in range(brace_start, len(code)):
        if code[i] == "{":
            depth += 1
        elif code[i] == "}":
            depth -= 1
            if depth == 0:
                return code[brace_start + 1 : i]

    return ""


def _extract_integrate_body(code: str) -> str:
    """Extract the integrate() function body (not integrate_fwd_checkpoint, etc.).

    We search for 'void integrate(' making sure it's NOT prefixed by
    integrate_fwd_checkpoint, integrate_adj, integrate_tlm, or integrate_with_reduction.
    """
    # Find all 'void integrate(' occurrences and pick the one that is plain integrate()
    pattern = re.compile(r"KOKKOS_INLINE_FUNCTION\s+void\s+integrate\s*\(", re.DOTALL)
    for match in pattern.finditer(code):
        # Verify this isn't part of a longer name by checking what comes before
        start = match.start()
        # Look backward for any preceding identifier characters
        preceding = code[max(0, start - 30) : start]
        if any(prefix in preceding for prefix in ["_fwd_checkpoint", "_adj", "_tlm", "_with_reduction"]):
            continue
        # This is the plain integrate() - extract its body
        pos = match.start()
        brace_start = code.index("{", pos)
        depth = 0
        for i in range(brace_start, len(code)):
            if code[i] == "{":
                depth += 1
            elif code[i] == "}":
                depth -= 1
                if depth == 0:
                    return code[brace_start + 1 : i]
    return ""


# ---------------------------------------------------------------------------
# Tests: GPU safety for adjoint/TLM functions (Req 8.1)
# ---------------------------------------------------------------------------


@pytest.mark.parametrize("solver_name", ALL_SOLVERS)
class TestAdjointTLMGPUSafety:
    """GPU safety invariants for adjoint/TLM generated code.

    Verifies that integrate_adj(), integrate_tlm(), and integrate_fwd_checkpoint()
    contain no heap allocation, no I/O, no exceptions, and are annotated with
    KOKKOS_INLINE_FUNCTION.
    """

    def test_integrate_adj_no_forbidden_patterns(self, solver_name: str, tmp_path):
        """integrate_adj() contains no heap allocation, I/O, or exceptions.

        **Validates: Requirements 8.1**
        """
        mech = _load_chapman()
        code = _generate_adjoint_code(mech, solver_name, str(tmp_path))
        body = _extract_function_body(code, "integrate_adj")
        assert body, f"[{solver_name}] integrate_adj() not found in generated code"

        for pattern, description in FORBIDDEN_PATTERNS:
            assert pattern not in body, (
                f"[{solver_name}] integrate_adj() contains forbidden pattern: " f"{description} ('{pattern}')"
            )

    def test_integrate_tlm_no_forbidden_patterns(self, solver_name: str, tmp_path):
        """integrate_tlm() contains no heap allocation, I/O, or exceptions.

        **Validates: Requirements 8.1**
        """
        mech = _load_chapman()
        code = _generate_adjoint_code(mech, solver_name, str(tmp_path))
        body = _extract_function_body(code, "integrate_tlm")
        assert body, f"[{solver_name}] integrate_tlm() not found in generated code"

        for pattern, description in FORBIDDEN_PATTERNS:
            assert pattern not in body, (
                f"[{solver_name}] integrate_tlm() contains forbidden pattern: " f"{description} ('{pattern}')"
            )

    def test_integrate_fwd_checkpoint_no_forbidden_patterns(self, solver_name: str, tmp_path):
        """integrate_fwd_checkpoint() contains no heap allocation, I/O, or exceptions.

        **Validates: Requirements 8.1**
        """
        mech = _load_chapman()
        code = _generate_adjoint_code(mech, solver_name, str(tmp_path))
        body = _extract_function_body(code, "integrate_fwd_checkpoint")
        assert body, f"[{solver_name}] integrate_fwd_checkpoint() not found in generated code"

        for pattern, description in FORBIDDEN_PATTERNS:
            assert pattern not in body, (
                f"[{solver_name}] integrate_fwd_checkpoint() contains forbidden pattern: " f"{description} ('{pattern}')"
            )

    def test_integrate_adj_kokkos_annotation(self, solver_name: str, tmp_path):
        """integrate_adj() has KOKKOS_INLINE_FUNCTION annotation.

        **Validates: Requirements 8.1**
        """
        mech = _load_chapman()
        code = _generate_adjoint_code(mech, solver_name, str(tmp_path))

        pattern = re.compile(
            r"KOKKOS_INLINE_FUNCTION[^;]*?\bvoid\s+integrate_adj\s*\(",
            re.DOTALL,
        )
        assert pattern.search(code), f"[{solver_name}] integrate_adj() missing KOKKOS_INLINE_FUNCTION annotation"

    def test_integrate_tlm_kokkos_annotation(self, solver_name: str, tmp_path):
        """integrate_tlm() has KOKKOS_INLINE_FUNCTION annotation.

        **Validates: Requirements 8.1**
        """
        mech = _load_chapman()
        code = _generate_adjoint_code(mech, solver_name, str(tmp_path))

        pattern = re.compile(
            r"KOKKOS_INLINE_FUNCTION[^;]*?\bvoid\s+integrate_tlm\s*\(",
            re.DOTALL,
        )
        assert pattern.search(code), f"[{solver_name}] integrate_tlm() missing KOKKOS_INLINE_FUNCTION annotation"

    def test_integrate_fwd_checkpoint_kokkos_annotation(self, solver_name: str, tmp_path):
        """integrate_fwd_checkpoint() has KOKKOS_INLINE_FUNCTION annotation.

        **Validates: Requirements 8.1**
        """
        mech = _load_chapman()
        code = _generate_adjoint_code(mech, solver_name, str(tmp_path))

        pattern = re.compile(
            r"KOKKOS_INLINE_FUNCTION[^;]*?\b(?:int|void)\s+integrate_fwd_checkpoint\s*\(",
            re.DOTALL,
        )
        assert pattern.search(code), f"[{solver_name}] integrate_fwd_checkpoint() missing KOKKOS_INLINE_FUNCTION annotation"


# ---------------------------------------------------------------------------
# Tests: integrate() unchanged when --adjoint is enabled (Req 6.3)
# ---------------------------------------------------------------------------


@pytest.mark.parametrize("solver_name", ALL_SOLVERS)
class TestIntegrateUnchangedWithAdjoint:
    """Verify that the existing integrate() function body is IDENTICAL whether
    generated with adjoint=False or adjoint=True.

    This ensures no regression for forward-only users when adjoint mode is enabled.

    **Validates: Requirements 6.3**
    """

    def test_integrate_body_identical(self, solver_name: str, tmp_path):
        """integrate() body is byte-for-byte identical with and without --adjoint.

        **Validates: Requirements 6.3**
        """
        mech = _load_chapman()

        # Generate without adjoint
        fwd_dir = str(tmp_path / "fwd")
        code_fwd = _generate_forward_only_code(mech, solver_name, fwd_dir)

        # Generate with adjoint
        adj_dir = str(tmp_path / "adj")
        code_adj = _generate_adjoint_code(mech, solver_name, adj_dir)

        # Extract integrate() body from both
        body_fwd = _extract_integrate_body(code_fwd)
        body_adj = _extract_integrate_body(code_adj)

        assert body_fwd, f"[{solver_name}] integrate() not found in forward-only code"
        assert body_adj, f"[{solver_name}] integrate() not found in adjoint-enabled code"

        # The bodies must be identical
        assert body_fwd == body_adj, (
            f"[{solver_name}] integrate() body differs between adjoint=False and adjoint=True.\n"
            f"This violates Requirement 6.3: existing integrate() must remain unchanged.\n"
            f"  Forward-only length: {len(body_fwd)} chars\n"
            f"  Adjoint-enabled length: {len(body_adj)} chars"
        )

    def test_integrate_with_reduction_body_identical(self, solver_name: str, tmp_path):
        """integrate_with_reduction() body is identical with and without --adjoint.

        **Validates: Requirements 6.3**
        """
        mech = _load_chapman()

        # Generate without adjoint
        fwd_dir = str(tmp_path / "fwd")
        code_fwd = _generate_forward_only_code(mech, solver_name, fwd_dir)

        # Generate with adjoint
        adj_dir = str(tmp_path / "adj")
        code_adj = _generate_adjoint_code(mech, solver_name, adj_dir)

        # Extract integrate_with_reduction() body from both
        body_fwd = _extract_function_body(code_fwd, "integrate_with_reduction")
        body_adj = _extract_function_body(code_adj, "integrate_with_reduction")

        assert body_fwd, f"[{solver_name}] integrate_with_reduction() not found in forward-only code"
        assert body_adj, f"[{solver_name}] integrate_with_reduction() not found in adjoint-enabled code"

        assert body_fwd == body_adj, (
            f"[{solver_name}] integrate_with_reduction() body differs between "
            f"adjoint=False and adjoint=True.\n"
            f"This violates Requirement 6.3."
        )
