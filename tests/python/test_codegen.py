import pytest
from mkpp.codegen import generate_headers

def test_generate_headers_empty():
    with pytest.raises(ValueError, match="Cannot generate headers for empty mechanism"):
        generate_headers({})

from mkpp.model import MechanismDefinition, AerosolRepresentation, SpeciesDefinition, PhaseMode

def test_generate_headers_no_raw_pragmas(tmp_path):
    mech = MechanismDefinition(
        name="test_mech",
        description="Test",
        aerosol_representation=AerosolRepresentation.BULK,
        species=[],
        phases=[],
        reactions=[]
    )
    
    # We must append a dummy species so it passes the empty check
    from mkpp.model import SpeciesDefinition, PhaseMode
    mech.species.append(SpeciesDefinition(name="O3", phase=PhaseMode.GAS))
    
    out_dir = tmp_path / "build"
    results = generate_headers(mech, out_dir=str(out_dir))
    
    header_path = results["header"]
    with open(header_path, 'r') as f:
        content = f.read()
        
    # T047 Negative check: no OpenMP or OpenACC pragmas allowed
    assert "#pragma omp" not in content
    assert "#pragma acc" not in content
    assert "Kokkos_Core.hpp" in content

import json

def test_generate_headers_adjoint_metadata(tmp_path):
    mech = MechanismDefinition(
        name="test_mech", description="Test",
        aerosol_representation=AerosolRepresentation.BULK,
        species=[], phases=[], reactions=[]
    )
    from mkpp.model import SpeciesDefinition, PhaseMode
    mech.species.append(SpeciesDefinition(name="O3", phase=PhaseMode.GAS))
    
    out_dir = tmp_path / "build"
    results = generate_headers(mech, out_dir=str(out_dir))
    
    # Assert generated header has Adjoint/TLM kernels
    with open(results["header"], 'r') as f:
        content = f.read()
    assert "compute_adjoint" in content
    assert "compute_tlm" in content
    assert "KokkosBatched_LU" in content
    
    # Assert manifest records the Adjoint/TLM capability
    with open(results["manifest"], 'r') as f:
        manifest = json.load(f)
    artifacts = manifest.get("artifacts", [])
    assert any(a.get("kind") == "adjoint_tlm_record" and a.get("differentiable") for a in artifacts)

def test_zero_copy_manifest_metadata(tmp_path):
    mech = MechanismDefinition(
        name="test_mech", description="Test", aerosol_representation=AerosolRepresentation.BULK,
        species=[SpeciesDefinition(name="O3", phase=PhaseMode.GAS)], phases=[], reactions=[]
    )
    
    # Inject dummy host interface schema
    from mkpp.model import HostInterfaceSchema, ArrayDefinition
    mech.host_interface = HostInterfaceSchema(
        arrays=[ArrayDefinition(name="cloud_liquid_water", rank=3, layout="LayoutLeft")]
    )
    
    out_dir = tmp_path / "build"
    results = generate_headers(mech, out_dir=str(out_dir))
    
    # Verify unmanaged view declaration in headers
    with open(results["header"], 'r') as f:
        content = f.read()
    assert "Kokkos::View" in content
    assert "Kokkos::MemoryUnmanaged" in content
    assert "Kokkos::LayoutLeft" in content
    
    # Verify schema mapping in manifest
    with open(results["manifest"], 'r') as f:
        manifest = json.load(f)
    assert "host_interface" in manifest
    assert manifest["host_interface"]["cloud_liquid_water"]["layout"] == "LayoutLeft"
    assert "lifetime" in manifest["host_interface"]["cloud_liquid_water"]
    assert manifest["host_interface"]["cloud_liquid_water"]["lifetime"] == "unmanaged_borrowed_from_host"
