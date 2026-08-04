import pytest
import yaml
from mkpp.model import AerosolRepresentation, MechanismDefinition, PhaseMode
from mkpp.parser import parse_mechanism_micm
from mkpp.validation import sanitize_path, validate_mechanism


def test_sanitize_path_rejects_traversal():
    with pytest.raises(ValueError, match="Directory traversal"):
        sanitize_path("../secret/file.yaml")
    with pytest.raises(ValueError, match="Directory traversal"):
        sanitize_path("/absolute/unauthorized/path.yaml")
    assert sanitize_path("valid/path.yaml") == "valid/path.yaml"
    assert sanitize_path("./valid/path.yaml") == "./valid/path.yaml"


def test_parse_micm_mechanism():
    yaml_content = """
    species:
      - name: O3
        type: CHEM_SPEC
      - name: O2
        type: CHEM_SPEC
      - name: O
        type: CHEM_SPEC
    phases:
      - name: gas
        species: [O3, O2, O]
    reactions:
      - type: ARRHENIUS
        reactants:
          O: {}
          O2: {}
          M: {}
        products:
          O3: {}
          M: {}
        A: 6.0e-34
    """
    raw_data = yaml.safe_load(yaml_content)
    mech = parse_mechanism_micm("test_mech", raw_data)
    assert len(mech.species) == 3
    assert mech.species[0].name == "O3"
    assert len(mech.phases) == 1
    assert mech.phases[0].name == "gas"
    assert len(mech.reactions) == 1
    assert mech.reactions[0].reaction_type == "ARRHENIUS"
    assert "O2" in mech.reactions[0].reactants
    assert "O3" in mech.reactions[0].products


def test_validate_mechanism_missing_species():
    yaml_content = """
    species:
      - name: O2
        type: CHEM_SPEC
    phases: []
    reactions:
      - type: ARRHENIUS
        reactants:
          O: {}
          O2: {}
        products:
          O3: {}
        A: 1.0
    """
    raw_data = yaml.safe_load(yaml_content)
    mech = parse_mechanism_micm("bad_mech", raw_data)
    with pytest.raises(ValueError, match="Unknown reactant 'O' in reaction"):
        validate_mechanism(mech)


from mkpp.validation import validate_fuzzer_stiffness, validate_mpi_safety


def test_validate_fuzzer_stiffness():
    # Fuzzer stiffness exceeding threshold must exit with non-zero status (T042)
    with pytest.raises(SystemExit) as e:
        validate_fuzzer_stiffness(max_condition_number=1e15, threshold=1e12)
    assert e.value.code != 0


def test_validate_mpi_safety():
    # MPI Safety check must reject root-rank aggregation (T043)
    with pytest.raises(ValueError, match="Root-rank aggregation is strictly forbidden"):
        validate_mpi_safety({"mpi": {"gather_to_root": True}})

    assert validate_mpi_safety({"mpi": {"gather_to_root": False}}) is True


def test_validate_mechanism_strict():
    from mkpp.model import MechanismDefinition, PhaseMode, SpeciesDefinition

    # Valid but missing description
    mech = MechanismDefinition(
        name="test_mech",
        description="",  # Empty description
        aerosol_representation=AerosolRepresentation.BULK,
        species=[SpeciesDefinition(name="O3", phase=PhaseMode.GAS)],
        phases=[],
        reactions=[],
    )

    # Should pass in non-strict mode
    validate_mechanism(mech, strict=False)

    # Should fail in strict mode
    with pytest.raises(ValueError, match="Strict mode requires a mechanism description"):
        validate_mechanism(mech, strict=True)


def test_host_interface_schema_validation():
    from mkpp.model import MechanismDefinition, PhaseMode, SpeciesDefinition

    # Missing required host interface definition should fail preflight
    mech = MechanismDefinition(
        name="test_mech",
        description="Test",
        aerosol_representation=AerosolRepresentation.BULK,
        species=[SpeciesDefinition(name="O3", phase=PhaseMode.GAS)],
        phases=[],
        reactions=[],
    )
    from mkpp.validation import validate_host_interface

    with pytest.raises(ValueError, match="Host interface schema is missing required arrays"):
        validate_host_interface(mech)


def test_host_interface_schema_shape_and_units():
    from mkpp.model import ArrayDefinition, HostInterfaceSchema
    from mkpp.validation import validate_host_interface

    # Missing extent
    mech = MechanismDefinition(
        name="test",
        description="test",
        aerosol_representation="bulk",
        species=[],
        phases=[],
        reactions=[],
    )
    mech.host_interface = HostInterfaceSchema(
        arrays=[
            ArrayDefinition(name="cloud_liquid_water", rank=3, layout="LayoutLeft", unit="kg/kg")
        ]
    )
    with pytest.raises(
        ValueError,
        match="Host interface array 'cloud_liquid_water' must define extent vector matching rank 3",
    ):
        validate_host_interface(mech)

    # Mismatched rank and extent
    mech.host_interface.arrays[0].extent = [100, 100]  # Rank is 3, extent is 2
    with pytest.raises(ValueError, match="Extent length 2 does not match rank 3"):
        validate_host_interface(mech)

    # Valid
    mech.host_interface.arrays[0].extent = [100, 100, 30]
    mech.host_interface.arrays[0].ownership = "host"
    assert validate_host_interface(mech) is True


def test_parse_micm_host_interface():
    import yaml
    from mkpp.parser import parse_mechanism_micm

    yaml_content = """
    species: [{name: O3}]
    host_interface:
      arrays:
        - name: cloud_liquid_water
          rank: 3
          layout: LayoutLeft
          extent: [100, 100, 30]
          unit: kg/kg
          ownership: host
    """
    raw_data = yaml.safe_load(yaml_content)
    mech = parse_mechanism_micm("test_mech", raw_data)

    assert mech.host_interface is not None
    assert len(mech.host_interface.arrays) == 1

    arr = mech.host_interface.arrays[0]
    assert arr.name == "cloud_liquid_water"
    assert arr.rank == 3
    assert arr.layout == "LayoutLeft"
    assert arr.extent == [100, 100, 30]
    assert arr.unit == "kg/kg"
    assert arr.ownership == "host"


def test_host_interface_schema_units_and_c_compat():
    from mkpp.model import ArrayDefinition, HostInterfaceSchema
    from mkpp.validation import validate_host_interface

    mech = MechanismDefinition(
        name="test",
        description="test",
        aerosol_representation="bulk",
        species=[],
        phases=[],
        reactions=[],
    )
    mech.host_interface = HostInterfaceSchema(
        arrays=[
            ArrayDefinition(
                name="cloud_liquid_water",
                rank=3,
                extent=[100, 100, 30],
                layout="LayoutLeft",
                unit="unknown",
                ownership="host",
            )
        ]
    )

    # Missing canonical unit
    with pytest.raises(
        ValueError,
        match="Host interface array 'cloud_liquid_water' must define a known physical unit",
    ):
        validate_host_interface(mech)

    mech.host_interface.arrays[0].unit = "kg/kg"
    assert validate_host_interface(mech) is True


def test_sunrise_terminator_validation():
    # T028: Assert abrupt photolysis changes do not invalidate the partitioning contract
    from mkpp.model import ReactionDefinition
    from mkpp.validation import validate_terminator_safety

    mech = MechanismDefinition(
        name="test_mech",
        description="Test",
        aerosol_representation=AerosolRepresentation.BULK,
        species=[],
        phases=[],
        reactions=[
            # Photolysis without continuous transition across the terminator will crash the explicitly sorted chunks
            ReactionDefinition(
                reaction_type="PHOTOLYSIS",
                reactants=[],
                products=[],
                rate_expression="J",
                continuous_transition=False,
            )
        ],
    )

    with pytest.raises(
        ValueError, match="PHOTOLYSIS reactions must be marked with continuous_transition"
    ):
        validate_terminator_safety(mech)

    mech.reactions[0].continuous_transition = True
    assert validate_terminator_safety(mech) is True


def test_mass_conservation_and_aerosol_validation():
    # T029 and T034: Validate elemental mass balance and unsupported combinations
    from mkpp.model import ReactionDefinition, SpeciesDefinition
    from mkpp.validation import validate_mass_conservation

    mech = MechanismDefinition(
        name="test_mech",
        description="Test",
        aerosol_representation="bulk",
        species=[
            SpeciesDefinition(name="SO2", phase=PhaseMode.GAS, elements={"S": 1, "O": 2}),
            SpeciesDefinition(name="SO4", phase=PhaseMode.AEROSOL, elements={"S": 1, "O": 4}),
        ],
        phases=[],
        reactions=[
            ReactionDefinition(
                reaction_type="condensation",
                reactants=["SO2"],
                products=["SO4"],
                rate_expression="k",
            )
        ],
    )

    # Missing mass (1 S, 2 O -> 1 S, 4 O) should fail elemental balance
    with pytest.raises(ValueError, match="Elemental mass imbalance detected in reaction"):
        validate_mass_conservation(mech)

    # Correct it to balance elements (pseudo-chemistry for test)
    mech.species.append(SpeciesDefinition(name="O2", phase=PhaseMode.GAS, elements={"O": 2}))
    mech.reactions[0].reactants.append("O2")

    assert validate_mass_conservation(mech) is True
