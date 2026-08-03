from dataclasses import dataclass, field
from typing import Dict, List, Optional, Any, Set, Tuple
from enum import Enum


@dataclass
class CompilationError(Exception):
    """Structured error for compilation pipeline failures."""
    stage: str           # "parsing", "validation", "lowering", "codegen"
    message: str
    reaction_index: Optional[int] = None
    species_name: Optional[str] = None
    yaml_location: Optional[str] = None  # "file.yaml:line:col"

    def to_dict(self) -> Dict[str, Any]:
        """Return a JSON-serializable dictionary of the error fields."""
        d: Dict[str, Any] = {"stage": self.stage, "message": self.message}
        if self.reaction_index is not None:
            d["reaction_index"] = self.reaction_index
        if self.species_name is not None:
            d["species_name"] = self.species_name
        if self.yaml_location is not None:
            d["yaml_location"] = self.yaml_location
        return d

    def __str__(self) -> str:
        parts = [f"[{self.stage}] {self.message}"]
        if self.reaction_index is not None:
            parts.append(f"reaction_index={self.reaction_index}")
        if self.species_name is not None:
            parts.append(f"species={self.species_name}")
        if self.yaml_location is not None:
            parts.append(f"at {self.yaml_location}")
        return " | ".join(parts)

class PhaseMode(Enum):
    GAS = "gas"
    AEROSOL = "aerosol"
    AQUEOUS = "aqueous"
    MIXED = "mixed"

class SolverMode(Enum):
    IMPLICIT = "implicit"
    EXPLICIT = "explicit"
    COUPLED = "coupled"

class AerosolRepresentation(Enum):
    BULK = "bulk"
    MODAL = "modal"
    SECTIONAL = "sectional"

class ReactionType(Enum):
    ARRHENIUS = "ARRHENIUS"
    TROE = "TROE"
    PHOTOLYSIS = "PHOTOLYSIS"
    HETEROGENEOUS = "HETEROGENEOUS"
    TUNNELING = "TUNNELING"
    CONDENSATION = "CONDENSATION"
    PHASE_CHANGE = "PHASE_CHANGE"
    UNKNOWN = "UNKNOWN"

@dataclass
class SpeciesDefinition:
    name: str
    phase: PhaseMode
    elements: Dict[str, int] = field(default_factory=dict)
    role: Optional[str] = None

@dataclass
class PhaseDefinition:
    name: str
    solver_mode: SolverMode
    transport_model: Optional[str] = None
    continuity_model: Optional[str] = None

@dataclass
class ReactionDefinition:
    reaction_type: str  # e.g., ARRHENIUS, PHOTOLYSIS, TROE, EP2, EP3
    reactants: Dict[str, float]
    products: Dict[str, float]
    rate_expression: str
    parameters: Dict[str, Any] = field(default_factory=dict)
    unit_policy: str = "canonical"
    stiff: bool = False
    continuous_transition: bool = False

@dataclass
class ArrayDefinition:
    name: str
    rank: int
    layout: str = "LayoutLeft" # Default to Fortran-compatible column-major
    extent: Optional[List[int]] = None
    unit: str = "unknown"
    ownership: str = "host" # 'host' or 'device'

@dataclass
class HostInterfaceSchema:
    arrays: List[ArrayDefinition] = field(default_factory=list)

@dataclass
class MechanismDefinition:
    name: str
    description: str
    aerosol_representation: AerosolRepresentation
    species: List[SpeciesDefinition]
    phases: List[PhaseDefinition]
    reactions: List[ReactionDefinition]
    host_interface: Optional['HostInterfaceSchema'] = None
    units: str = "canonical"
    metadata: Dict[str, str] = field(default_factory=dict)

@dataclass
class TestEnvironmentDefinition:
    name: str
    initial_conditions: Dict[str, float]
    meteorology: Dict[str, float]
    photolysis: Dict[str, float]
    cloud_liquid_water: float
    bounds: Dict[str, Dict[str, float]]
    expected_outputs: Optional[Dict[str, float]] = None

@dataclass
class GeneratedArtifact:
    kind: str
    path: str
    dependencies: List[str]
    checksum: Optional[str] = None

@dataclass
class SymbolicLUPlan:
    num_species: int
    species_map: List[str]
    non_zero_jacobian: List[Tuple[int, int, str]] = field(default_factory=list)
    l_expressions: List[Tuple[int, int, str]] = field(default_factory=list)
    u_expressions: List[Tuple[int, int, str]] = field(default_factory=list)
    lu_expressions_ordered: List[Tuple[str, int, int, str]] = field(default_factory=list)
    forward_sub_steps: List[Tuple[int, str]] = field(default_factory=list)
    backward_sub_steps: List[Tuple[int, str]] = field(default_factory=list)
    permutation: Optional[List[int]] = None
    blocks: Optional[List[List[int]]] = None
    fill_in_count: int = 0
    annotated_expressions: Optional[List['AnnotatedLUExpression']] = None



@dataclass
class AnnotatedLUExpression:
    """LU expression with species-dependency metadata for auto-reduction."""
    kind: str              # "L" or "U"
    row: int
    col: int
    expr: str
    depends_on: Set[int]   # species indices whose activity affects this entry


@dataclass
class SparsityAnalysis:
    """Result of sparsity optimization pass."""
    original_nnz: int
    fill_in_positions: Set[Tuple[int, int]]
    total_nnz_after_fill: int
    permutation: List[int]
    inverse_permutation: List[int]
    blocks: List[List[int]]
    is_block_diagonal: bool
