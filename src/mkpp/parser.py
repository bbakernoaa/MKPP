import json
from pathlib import Path
from typing import Any

import yaml

from .model import (
    AerosolRepresentation,
    CompilationError,
    EquilibriumDefinition,
    MechanismDefinition,
    PhaseDefinition,
    PhaseMode,
    ReactionDefinition,
    SolverMode,
    SpeciesDefinition,
)


def parse_mechanism_micm(name: str, data: dict[str, Any]) -> MechanismDefinition:
    """Parse MICM/OpenAtmos standard dictionary into internal model."""
    if "species" not in data or not data["species"]:
        raise ValueError("MICM data must define at least one species")

    species = []
    for s in data.get("species", []):
        sp_name = s.get("name")
        if not sp_name:
            raise ValueError("Species must have a name")
        # Default to GAS if not specified in basic MICM
        phase = PhaseMode.GAS
        sp_type = str(s.get("type", "")).lower()
        sp_role = str(s.get("role", "")).lower()
        if sp_name in ("AIR", "O2", "H2O", "H2", "CH4", "M", "N2", "RO2") or sp_type == "fixed" or sp_role == "fixed":
            role = "fixed"
        else:
            role = "variable"
        species.append(
            SpeciesDefinition(
                name=sp_name,
                phase=phase,
                role=role,
                solver_atol=s.get("_atol"),
                solver_rtol=s.get("_rtol"),
            )
        )

    phases = []
    for p in data.get("phases", []):
        phases.append(PhaseDefinition(name=p.get("name"), solver_mode=SolverMode.IMPLICIT))

    # Build species name set for validation
    species_names = {s.name for s in species}

    reactions = []
    equilibrium_reactions: list[EquilibriumDefinition] = []

    for r in data.get("reactions", []):
        rtype = r.get("type", "UNKNOWN")

        if rtype == "EQUILIBRIUM":
            # Parse EQUILIBRIUM block into EquilibriumDefinition
            system = r.get("system", "")
            raw_total_species = r.get("total_species", {})
            regime_blending = r.get("regime_blending", "sigmoid")
            transition_width = r.get("transition_width", 0.05)
            activity_model = r.get("activity_model", "fixed")
            eq_constants = r.get("equilibrium_constants", {})
            continuous_transition = r.get("continuous_transition", True)

            # Flatten total_species: each element maps to [gas_species, *aerosol_species]
            total_species: dict[str, list[str]] = {}
            for element_name, element_data in raw_total_species.items():
                gas_sp = element_data.get("gas", "")
                aerosol_sp = element_data.get("aerosol", [])
                if isinstance(aerosol_sp, str):
                    aerosol_sp = [aerosol_sp]
                flat_list = [gas_sp] + aerosol_sp
                total_species[element_name] = flat_list

            # Validate all referenced species exist in the mechanism species list
            for element_name, sp_list in total_species.items():
                for sp_name in sp_list:
                    if sp_name not in species_names:
                        raise CompilationError(
                            stage="parsing",
                            message=f"EQUILIBRIUM references unknown species '{sp_name}' " f"in element '{element_name}'",
                            species_name=sp_name,
                        )

            # Validate equilibrium constants have required params (A, dH, Tref)
            for const_name, const_params in eq_constants.items():
                for required_field in ("A", "dH", "Tref"):
                    if required_field not in const_params:
                        raise CompilationError(
                            stage="validation",
                            message=f"Equilibrium constant '{const_name}' requires A, dH, Tref parameters",
                        )

            equilibrium_reactions.append(
                EquilibriumDefinition(
                    system=system,
                    total_species=total_species,
                    regime_blending=regime_blending,
                    transition_width=transition_width,
                    activity_model=activity_model,
                    equilibrium_constants=eq_constants,
                    continuous_transition=continuous_transition,
                    relaxation_timescale_inv=r.get("relaxation_timescale_inv", 1e6),
                )
            )
            # EQUILIBRIUM is not a kinetic reaction — do NOT add to reactions list
            continue

        reactants = r.get("reactants", {})
        products = r.get("products", {})

        # Extract all potential rate parameters instead of just A
        # For MICM compliance, parameters can include k0, kinf, Fc, gamma, etc.
        parameters = {}
        for k, v in r.items():
            if k not in ("type", "reactants", "products", "stiff", "continuous_transition"):
                parameters[k] = v

        # Maintain backwards compat for the simple tests
        base_rate = str(r.get("A", ""))

        reactions.append(
            ReactionDefinition(
                reaction_type=rtype,
                reactants=reactants,
                products=products,
                rate_expression=base_rate,
                parameters=parameters,
                stiff=r.get("stiff", False),
                continuous_transition=r.get("continuous_transition", False),
            )
        )

    # Detect PHASE_CHANGE / EQUILIBRIUM conflicts: collect species from each
    phase_change_species: set[str] = set()
    for rxn in reactions:
        if rxn.reaction_type == "PHASE_CHANGE":
            phase_change_species.update(rxn.reactants.keys())
            phase_change_species.update(rxn.products.keys())

    equilibrium_species: set[str] = set()
    for eq_def in equilibrium_reactions:
        for sp_list in eq_def.total_species.values():
            equilibrium_species.update(sp_list)

    overlap = phase_change_species & equilibrium_species
    if overlap:
        conflict_name = sorted(overlap)[0]
        raise CompilationError(
            stage="validation",
            message=f"Species '{conflict_name}' cannot have both " f"PHASE_CHANGE and EQUILIBRIUM declarations",
            species_name=conflict_name,
        )

    from .model import ArrayDefinition, HostInterfaceSchema

    host_interface = None
    if "host_interface" in data and "arrays" in data["host_interface"]:
        arrays = []
        for arr_data in data["host_interface"]["arrays"]:
            arrays.append(
                ArrayDefinition(
                    name=arr_data.get("name", "unknown"),
                    rank=arr_data.get("rank", 0),
                    layout=arr_data.get("layout", "LayoutLeft"),
                    extent=arr_data.get("extent"),
                    unit=arr_data.get("unit", "unknown"),
                    ownership=arr_data.get("ownership", "host"),
                )
            )
        host_interface = HostInterfaceSchema(arrays=arrays)

    return MechanismDefinition(
        name=name,
        description=data.get("description", ""),
        aerosol_representation=AerosolRepresentation.BULK,
        species=species,
        phases=phases,
        reactions=reactions,
        host_interface=host_interface,
        equilibrium_reactions=equilibrium_reactions,
        metadata=data.get("metadata", {}),
    )


def load_mechanism(path: str) -> MechanismDefinition:
    p = Path(path)
    with open(p) as f:
        if p.suffix in [".yaml", ".yml"]:
            data = yaml.safe_load(f)
        else:
            data = json.load(f)
    return parse_mechanism_micm(p.stem, data)
