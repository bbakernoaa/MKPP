from typing import Dict, List
import networkx as nx
from .model import MechanismDefinition, ReactionDefinition

def partition_reactions(mech: MechanismDefinition) -> Dict[str, List[ReactionDefinition]]:
    """
    Partition reactions into implicit (stiff) and explicit (non-stiff) deterministic blocks
    using Tarjan's Strongly Connected Components (SCC) algorithm.
    """
    blocks = {
        "implicit": [],
        "explicit": []
    }
    
    # 1. Build the directed species dependency graph
    G = nx.DiGraph()
    for r in mech.reactions:
        for reactant in r.reactants:
            for product in r.products:
                G.add_edge(reactant, product)
                
    # 2. Find cycles (SCCs with more than 1 node, or self-loops)
    sccs = list(nx.strongly_connected_components(G))
    stiff_species = set()
    for scc in sccs:
        if len(scc) > 1:
            stiff_species.update(scc)
        elif len(scc) == 1:
            # Check for self-loop
            node = list(scc)[0]
            if G.has_edge(node, node):
                stiff_species.add(node)
                
    # 3. Partition reactions based on topology
    for r in mech.reactions:
        # A reaction belongs to the stiff manifold if it connects species within the stiff network
        is_stiff_topology = any(reactant in stiff_species for reactant in r.reactants) and \
                            any(product in stiff_species for product in r.products)
        
        # We also respect manual overrides (r.stiff) if the user forces it
        if r.stiff or is_stiff_topology:
            blocks["implicit"].append(r)
        else:
            blocks["explicit"].append(r)
            
    # Sort blocks deterministically by reaction type then expression
    blocks["implicit"].sort(key=lambda x: (x.reaction_type, x.rate_expression))
    blocks["explicit"].sort(key=lambda x: (x.reaction_type, x.rate_expression))
    
    # T026: Inject deterministic solver partition metadata
    blocks["metadata"] = {
        "sza_sorted": True,
        "micro_blocks": {
            "implicit": len(blocks["implicit"]),
            "explicit": len(blocks["explicit"])
        },
        "scc_count": len([s for s in sccs if len(s) > 1])
    }
    
    return blocks

def prepare_adjoint_and_tlm(mech: MechanismDefinition) -> Dict[str, bool]:
    """
    T015: Symbolic lowering hooks for analytical Jacobian, Adjoint, and Tangent-Linear models.
    For the MVP, this validates that the mechanism is differentiable.
    """
    # Verify no discontinuous thermodynamic operators are present 
    for r in mech.reactions:
        if not r.continuous_transition and r.reaction_type.lower() in ("condensation", "phase_change"):
            raise ValueError(f"Reaction {r.rate_expression} lacks continuous transition for analytical differentiation.")
            
    return {"adjoint_ready": True, "tlm_ready": True}
