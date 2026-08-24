"""Immutable domain models for reproducible solver benchmark campaigns.

The models deliberately use tuples of named records instead of mutable mappings.
This keeps a resolved campaign safe to hash, retain, and pass between validation
and reporting without allowing its scientific inputs to change in place.
"""

from __future__ import annotations

from dataclasses import dataclass
from enum import StrEnum

Scalar = int | float | str | bool


class SolverId(StrEnum):
    MICM = "micm"
    KPP = "kpp"
    MKPP = "mkpp"


class SpeciesRole(StrEnum):
    ACTIVE = "active"
    FIXED = "fixed"
    DIAGNOSTIC = "diagnostic"


class AdmissionStatus(StrEnum):
    DRAFT = "draft"
    MAPPING_VERIFIED = "mapping_verified"
    CHEMISTRY_VERIFIED = "chemistry_verified"
    TRAJECTORY_VERIFIED = "trajectory_verified"
    ADMITTED = "admitted"
    INELIGIBLE = "ineligible"


class ScenarioRole(StrEnum):
    CALIBRATION = "calibration"
    MEASUREMENT = "measurement"


class ConfigurationStatus(StrEnum):
    CANDIDATE = "candidate"
    CALIBRATION_PASSED = "calibration_passed"
    SELECTED = "selected"
    FROZEN = "frozen"


class CampaignStatus(StrEnum):
    CONFIGURED = "configured"
    PREFLIGHT_PASSED = "preflight_passed"
    ADMITTED = "admitted"
    REFERENCE_QUALIFIED = "reference_qualified"
    CALIBRATED = "calibrated"
    MEASURING = "measuring"
    ASSESSED = "assessed"
    REVIEWED = "reviewed"
    PUBLISHED = "published"


class RunStatus(StrEnum):
    SUCCESS = "success"
    FAILED = "failed"
    INVALID = "invalid"
    INELIGIBLE = "ineligible"


class QualificationStatus(StrEnum):
    QUALIFIED = "qualified"
    UNQUALIFIED = "unqualified"


class ComparisonStatus(StrEnum):
    ELIGIBLE = "eligible"
    WITHHELD = "withheld"


class TimingBoundary(StrEnum):
    STEADY_STATE_SOLVE = "steady_state_solve"
    LIFECYCLE = "lifecycle"


@dataclass(frozen=True, slots=True)
class NamedValue:
    name: str
    value: Scalar


@dataclass(frozen=True, slots=True)
class Quantity:
    value: float
    unit: str


@dataclass(frozen=True, slots=True)
class HashIdentity:
    id: str
    version: str
    sha256: str


@dataclass(frozen=True, slots=True)
class SourceAsset:
    path: str
    revision: str
    sha256: str


@dataclass(frozen=True, slots=True)
class SpeciesDefinition:
    id: str
    role: SpeciesRole
    phase: str
    unit: str
    scale: float
    aliases: tuple[str, ...] = ()


@dataclass(frozen=True, slots=True)
class StoichiometricTerm:
    species_id: str
    coefficient: float


@dataclass(frozen=True, slots=True)
class ReactionDefinition:
    id: str
    reactants: tuple[StoichiometricTerm, ...]
    products: tuple[StoichiometricTerm, ...]
    rate_law_id: str
    rate_scale: float = 1.0
    rate_parameters: tuple[NamedValue, ...] = ()


@dataclass(frozen=True, slots=True)
class PhotolysisInput:
    id: str
    unit: str


@dataclass(frozen=True, slots=True)
class NameMapping:
    canonical_id: str
    native_id: str


@dataclass(frozen=True, slots=True)
class UnitTransform:
    canonical_id: str
    native_unit: str
    scale: float = 1.0
    offset: float = 0.0


@dataclass(frozen=True, slots=True)
class Capability:
    name: str
    supported: bool
    reason: str | None = None


@dataclass(frozen=True, slots=True)
class SolverBinding:
    solver_id: SolverId
    version: str
    revision: str
    input_assets: tuple[SourceAsset, ...]
    importer_assets: tuple[SourceAsset, ...] = ()
    generator_assets: tuple[SourceAsset, ...] = ()
    generated_assets: tuple[SourceAsset, ...] = ()
    executable_fingerprint: str = ""
    build_fingerprint: str = ""
    species_mapping: tuple[NameMapping, ...] = ()
    role_mapping: tuple[NameMapping, ...] = ()
    photolysis_mapping: tuple[NameMapping, ...] = ()
    unit_transforms: tuple[UnitTransform, ...] = ()
    reaction_audit_evidence: tuple[str, ...] = ()
    rate_law_audit_evidence: tuple[str, ...] = ()
    capabilities: tuple[Capability, ...] = ()


@dataclass(frozen=True, slots=True)
class MechanismManifest:
    schema_version: int
    mechanism_id: str
    version: str
    canonical_sources: tuple[SourceAsset, ...]
    chemistry_sha256: str
    species: tuple[SpeciesDefinition, ...]
    reactions: tuple[ReactionDefinition, ...]
    photolysis_inputs: tuple[PhotolysisInput, ...]
    required_solvers: tuple[SolverId, ...]
    bindings: tuple[SolverBinding, ...]
    admission_status: AdmissionStatus = AdmissionStatus.DRAFT
    admission_evidence: tuple[str, ...] = ()


@dataclass(frozen=True, slots=True)
class ForcingPoint:
    time_seconds: float
    value: float


@dataclass(frozen=True, slots=True)
class ForcingInput:
    id: str
    unit: str
    constant: float | None = None
    series: tuple[ForcingPoint, ...] = ()


@dataclass(frozen=True, slots=True)
class AccuracyBudget:
    rtol: float
    atol_by_species: tuple[tuple[str, float], ...]
    positivity_policy: str
    conservation_checks: tuple[str, ...] = ()


@dataclass(frozen=True, slots=True)
class ReferenceControls:
    implementation: str
    max_refinements: int
    controls: tuple[NamedValue, ...] = ()


@dataclass(frozen=True, slots=True)
class BenchmarkScenario:
    schema_version: int
    scenario_id: str
    version: str
    sha256: str
    mechanism: HashIdentity
    role: ScenarioRole
    initial_state: tuple[tuple[str, Quantity], ...]
    concentration_scales: tuple[tuple[str, float], ...]
    environment: tuple[tuple[str, Quantity], ...]
    forcing: tuple[ForcingInput, ...]
    start_seconds: float
    horizon_seconds: float
    forcing_boundaries_seconds: tuple[float, ...]
    checkpoints_seconds: tuple[float, ...]
    cells: tuple[int, ...]
    ensemble_seed: int
    accuracy: AccuracyBudget
    reference: ReferenceControls


@dataclass(frozen=True, slots=True)
class SolverConfiguration:
    configuration_id: str
    sha256: str
    solver_id: SolverId
    method: str
    tolerance_multiplier: float
    tolerance_vector: tuple[tuple[str, float], ...]
    minimum_step: float | None
    maximum_step: float | None
    controller: str
    linear_solver: str
    jacobian_reuse: str
    precision: str
    policy_flags: tuple[NamedValue, ...]
    status: ConfigurationStatus = ConfigurationStatus.CANDIDATE


@dataclass(frozen=True, slots=True)
class ResourcePolicy:
    hardware_id: str
    backend: str
    physical_cores: int
    threads: int
    affinity: str
    numa_policy: str
    telemetry_limits: tuple[NamedValue, ...] = ()
    floating_point_policy: tuple[str, ...] = ()


@dataclass(frozen=True, slots=True)
class SamplingPolicy:
    pilot_iterations: int
    warmups: int
    minimum_sample_seconds: float
    repetitions: int
    ordering_seed: int
    bootstrap_seed: int


@dataclass(frozen=True, slots=True)
class BenchmarkCampaign:
    campaign_id: str
    version: str
    sha256: str
    manifests: tuple[HashIdentity, ...]
    scenarios: tuple[HashIdentity, ...]
    solvers: tuple[SolverId, ...]
    configurations: tuple[HashIdentity, ...]
    resources: ResourcePolicy
    timing_boundaries: tuple[TimingBoundary, ...]
    sampling: SamplingPolicy
    raw_output_path: str
    report_output_path: str | None = None
    status: CampaignStatus = CampaignStatus.CONFIGURED


@dataclass(frozen=True, slots=True)
class BuildProvenance:
    binary_sha256: str
    asset_sha256: tuple[str, ...]
    compiler: str
    flags: tuple[str, ...]
    precision: str


@dataclass(frozen=True, slots=True)
class StateCheckpoint:
    time_seconds: float
    values: tuple[tuple[str, float], ...]


@dataclass(frozen=True, slots=True)
class WorkCounter:
    name: str
    available: bool
    value: float | None = None
    unavailable_reason: str | None = None


@dataclass(frozen=True, slots=True)
class SolverRun:
    campaign_id: str
    run_id: str
    block_id: int
    repetition: int
    order_position: int
    matching_key_sha256: str
    solver_id: SolverId
    manifest: HashIdentity
    scenario: HashIdentity
    configuration: HashIdentity
    build: BuildProvenance
    resources: ResourcePolicy
    timing_boundary: TimingBoundary
    common_work_count: int
    elapsed_seconds: float
    clock: str
    synchronized: bool
    synchronization_method: str
    lifecycle_seconds: tuple[tuple[str, float], ...]
    checkpoints: tuple[StateCheckpoint, ...]
    work_counters: tuple[WorkCounter, ...]
    status: RunStatus
    diagnostics: tuple[str, ...] = ()
    exclusion_reason: str | None = None


@dataclass(frozen=True, slots=True)
class ErrorMetrics:
    wrms: float
    maximum: float


@dataclass(frozen=True, slots=True)
class ScientificCheck:
    name: str
    passed: bool
    detail: str = ""


@dataclass(frozen=True, slots=True)
class ReferenceAttempt:
    ordinal: int
    controls: tuple[NamedValue, ...]
    checkpoints: tuple[StateCheckpoint, ...]
    work_counters: tuple[WorkCounter, ...]
    status: RunStatus
    diagnostics: tuple[str, ...] = ()


@dataclass(frozen=True, slots=True)
class ReferenceQualification:
    qualification_id: str
    scenario: HashIdentity
    implementation: str
    implementation_revision: str
    attempts: tuple[ReferenceAttempt, ...]
    effective_controls: tuple[NamedValue, ...]
    r1_r2_errors: ErrorMetrics
    scientific_checks: tuple[ScientificCheck, ...]
    status: QualificationStatus


@dataclass(frozen=True, slots=True)
class QuantityAssessment:
    quantity: str
    normalization_scale: float
    errors: ErrorMetrics
    structurally_equal: bool


@dataclass(frozen=True, slots=True)
class ChemistryAssessment:
    assessment_id: str
    manifest: HashIdentity
    audit_state_id: str
    solver_ids: tuple[SolverId, ...]
    quantities: tuple[QuantityAssessment, ...]
    sparsity_equal: bool
    independent_jacobian_passed: bool
    scientific_checks: tuple[ScientificCheck, ...]
    eligible: bool
    diagnostics: tuple[str, ...] = ()


@dataclass(frozen=True, slots=True)
class ScaledSpeciesError:
    member: int
    checkpoint_seconds: float
    species_id: str
    scaled_error: float


@dataclass(frozen=True, slots=True)
class DistributionSummary:
    median: float
    p95: float
    maximum: float


@dataclass(frozen=True, slots=True)
class AccuracyAssessment:
    assessment_id: str
    run_id: str
    configuration: HashIdentity
    reference_qualification_id: str
    scaled_errors: tuple[ScaledSpeciesError, ...]
    error_summary: DistributionSummary
    aggregate_errors: ErrorMetrics
    positivity_passed: bool
    conservation_passed: bool
    finite_state_passed: bool
    solver_success: bool
    eligible: bool
    diagnostics: tuple[str, ...] = ()


@dataclass(frozen=True, slots=True)
class ConfidenceInterval:
    lower: float
    upper: float
    confidence: float = 0.95


@dataclass(frozen=True, slots=True)
class PerformanceSummary:
    summary_id: str
    matching_key_sha256: str
    solver_id: SolverId
    eligible_paired_block_ids: tuple[int, ...]
    median_seconds: float
    iqr_seconds: float
    mad_seconds: float
    bootstrap_interval: ConfidenceInterval
    throughput_cell_steps_per_second: float
    total_work: int
    work_counters: tuple[WorkCounter, ...]
    repeatability_passed: bool


@dataclass(frozen=True, slots=True)
class PairwiseComparison:
    comparison_id: str
    baseline_solver_id: SolverId
    candidate_solver_id: SolverId
    matching_key_sha256: str
    matching_proof: tuple[HashIdentity, ...]
    paired_raw_ratios: tuple[float, ...]
    median_ratio: float
    bootstrap_interval: ConfidenceInterval
    baseline_accuracy_assessment_id: str
    candidate_accuracy_assessment_id: str
    status: ComparisonStatus
    withheld_reason: str | None = None


__all__ = [name for name, value in tuple(globals().items()) if isinstance(value, type) and value.__module__ == __name__]
