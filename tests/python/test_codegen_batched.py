"""Unit tests for AOT codegen with batched SIMD backends."""

from mkpp.codegen import generate_headers
from mkpp.model import AerosolRepresentation, MechanismDefinition, PhaseMode, SpeciesDefinition


def _create_dummy_mechanism() -> MechanismDefinition:
    sp1 = SpeciesDefinition(name="A", phase=PhaseMode.GAS)
    sp2 = SpeciesDefinition(name="B", phase=PhaseMode.GAS)
    return MechanismDefinition(
        name="dummy_batched",
        description="Dummy batched test mechanism",
        aerosol_representation=AerosolRepresentation.BULK,
        species=[sp1, sp2],
        phases=[],
        reactions=[],
    )


def test_native_simd_backend_default(tmp_path):
    mech = _create_dummy_mechanism()
    out_dir = str(tmp_path / "native_out")

    results = generate_headers(mech, out_dir=out_dir, simd_backend="native")

    header_file = results["header"]
    with open(header_file) as f:
        content = f.read()

    assert "KokkosBatched_Vector.hpp" not in content
    assert "MKPP_HAS_KOKKOS_KERNELS" not in content


def test_kokkos_batched_simd_backend_rendering(tmp_path):
    mech = _create_dummy_mechanism()
    out_dir = str(tmp_path / "kb_out")

    results = generate_headers(mech, out_dir=out_dir, simd_backend="kokkos_batched")

    header_file = results["header"]
    with open(header_file) as f:
        content = f.read()

    assert "KokkosBatched_Vector.hpp" in content
    assert "#ifndef MKPP_HAS_KOKKOS_KERNELS" in content
    assert "require KokkosKernels" in content
