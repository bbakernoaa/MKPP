import json
import yaml
from pathlib import Path
from typing import Dict, Any

from .model import (
    MechanismDefinition, SpeciesDefinition, PhaseDefinition,
    ReactionDefinition, PhaseMode, SolverMode, AerosolRepresentation
)

def parse_mechanism_micm(name: str, data: Dict[str, Any]) -> MechanismDefinition:
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
        species.append(SpeciesDefinition(name=sp_name, phase=phase))

    phases = []
    for p in data.get("phases", []):
        phases.append(PhaseDefinition(
            name=p.get("name"),
            solver_mode=SolverMode.IMPLICIT
        ))

    reactions = []
    for r in data.get("reactions", []):
        rtype = r.get("type", "UNKNOWN")
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

        reactions.append(ReactionDefinition(
            reaction_type=rtype,
            reactants=reactants,
            products=products,
            rate_expression=base_rate,
            parameters=parameters,
            stiff=r.get("stiff", False),
            continuous_transition=r.get("continuous_transition", False)
        ))

    from .model import HostInterfaceSchema, ArrayDefinition
    host_interface = None
    if "host_interface" in data and "arrays" in data["host_interface"]:
        arrays = []
        for arr_data in data["host_interface"]["arrays"]:
            arrays.append(ArrayDefinition(
                name=arr_data.get("name", "unknown"),
                rank=arr_data.get("rank", 0),
                layout=arr_data.get("layout", "LayoutLeft"),
                extent=arr_data.get("extent"),
                unit=arr_data.get("unit", "unknown"),
                ownership=arr_data.get("ownership", "host")
            ))
        host_interface = HostInterfaceSchema(arrays=arrays)

    return MechanismDefinition(
        name=name,
        description=data.get("description", ""),
        aerosol_representation=AerosolRepresentation.BULK,
        species=species,
        phases=phases,
        reactions=reactions,
        host_interface=host_interface
    )

def load_mechanism(path: str) -> MechanismDefinition:
    p = Path(path)
    with open(p, 'r') as f:
        if p.suffix in ['.yaml', '.yml']:
            data = yaml.safe_load(f)
        else:
            data = json.load(f)
    return parse_mechanism_micm(p.stem, data)
