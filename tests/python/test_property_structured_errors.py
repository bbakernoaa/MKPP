"""Property-based tests for structured error messages (CompilationError).

**Validates: Requirements 1.7**

Tests that CompilationError instances always contain the required fields
and that serialization methods preserve them correctly.
"""

from hypothesis import given, settings
from hypothesis import strategies as st
from mkpp.model import CompilationError

# --- Strategies ---

VALID_STAGES = st.sampled_from(["parsing", "validation", "lowering", "codegen"])

NON_EMPTY_TEXT = st.text(min_size=1, max_size=200).filter(lambda s: s.strip())

OPTIONAL_REACTION_INDEX = st.one_of(st.none(), st.integers(min_value=0, max_value=1000))

OPTIONAL_SPECIES_NAME = st.one_of(st.none(), st.text(min_size=1, max_size=50).filter(lambda s: s.strip()))

OPTIONAL_YAML_LOCATION = st.one_of(
    st.none(),
    st.builds(
        lambda f, l, c: f"{f}:{l}:{c}",
        st.text(
            min_size=1,
            max_size=30,
            alphabet=st.characters(whitelist_categories=("L", "N"), whitelist_characters="._-/"),
        ),
        st.integers(min_value=1, max_value=10000),
        st.integers(min_value=1, max_value=500),
    ),
)

# Strategy that guarantees at least one identifying field is present
AT_LEAST_ONE_IDENTIFIER = st.one_of(
    # reaction_index is present
    st.tuples(
        st.integers(min_value=0, max_value=1000),
        OPTIONAL_SPECIES_NAME,
    ),
    # species_name is present
    st.tuples(
        OPTIONAL_REACTION_INDEX,
        st.text(min_size=1, max_size=50).filter(lambda s: s.strip()),
    ),
)


@given(
    stage=VALID_STAGES,
    message=NON_EMPTY_TEXT,
    reaction_index=OPTIONAL_REACTION_INDEX,
    species_name=OPTIONAL_SPECIES_NAME,
    yaml_location=OPTIONAL_YAML_LOCATION,
)
@settings(deadline=None)
def test_to_dict_always_includes_stage_and_message(stage, message, reaction_index, species_name, yaml_location):
    """Property 1: to_dict() always includes stage and message fields.

    **Validates: Requirements 1.7**
    """
    err = CompilationError(
        stage=stage,
        message=message,
        reaction_index=reaction_index,
        species_name=species_name,
        yaml_location=yaml_location,
    )
    d = err.to_dict()

    assert "stage" in d, "to_dict() must include 'stage'"
    assert "message" in d, "to_dict() must include 'message'"
    assert d["stage"] == stage
    assert d["message"] == message
    assert d["stage"] in ("parsing", "validation", "lowering", "codegen")
    assert len(d["message"]) > 0


@given(
    stage=VALID_STAGES,
    message=NON_EMPTY_TEXT,
    reaction_index=OPTIONAL_REACTION_INDEX,
    species_name=OPTIONAL_SPECIES_NAME,
    yaml_location=OPTIONAL_YAML_LOCATION,
)
@settings(deadline=None)
def test_str_always_includes_stage_and_message(stage, message, reaction_index, species_name, yaml_location):
    """Property 1: __str__() always includes stage and message.

    **Validates: Requirements 1.7**
    """
    err = CompilationError(
        stage=stage,
        message=message,
        reaction_index=reaction_index,
        species_name=species_name,
        yaml_location=yaml_location,
    )
    s = str(err)

    assert stage in s, f"__str__() must include stage '{stage}'"
    assert message in s, "__str__() must include message"


@given(
    stage=VALID_STAGES,
    message=NON_EMPTY_TEXT,
    identifiers=AT_LEAST_ONE_IDENTIFIER,
    yaml_location=OPTIONAL_YAML_LOCATION,
)
@settings(deadline=None)
def test_at_least_one_identifying_field_present(stage, message, identifiers, yaml_location):
    """Property 1: When constructed with at least one identifier, to_dict()
    reflects at least one of reaction_index or species_name.

    **Validates: Requirements 1.7**
    """
    reaction_index, species_name = identifiers
    err = CompilationError(
        stage=stage,
        message=message,
        reaction_index=reaction_index,
        species_name=species_name,
        yaml_location=yaml_location,
    )
    d = err.to_dict()

    has_reaction = "reaction_index" in d
    has_species = "species_name" in d

    assert (
        has_reaction or has_species
    ), "At least one identifying field (reaction_index or species_name) must be present in to_dict()"


@given(
    stage=VALID_STAGES,
    message=NON_EMPTY_TEXT,
    reaction_index=st.integers(min_value=0, max_value=1000),
    species_name=st.text(min_size=1, max_size=50).filter(lambda s: s.strip()),
    yaml_location=OPTIONAL_YAML_LOCATION,
)
@settings(deadline=None)
def test_to_dict_optional_fields_included_when_set(stage, message, reaction_index, species_name, yaml_location):
    """Property 1: When optional fields are non-None, to_dict() includes them.

    **Validates: Requirements 1.7**
    """
    err = CompilationError(
        stage=stage,
        message=message,
        reaction_index=reaction_index,
        species_name=species_name,
        yaml_location=yaml_location,
    )
    d = err.to_dict()

    # Required fields always present
    assert d["stage"] == stage
    assert d["message"] == message

    # Optional fields present when non-None
    assert d["reaction_index"] == reaction_index
    assert d["species_name"] == species_name

    if yaml_location is not None:
        assert d["yaml_location"] == yaml_location
