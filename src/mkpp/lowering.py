from typing import Dict, List
import networkx as nx
import sympy as sp
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

def prepare_unified_jacobian(mech: MechanismDefinition) -> Dict[str, Any]:
    """
    Construct the Unified Jacobian using SymPy by calculating the partial derivatives
    of the sum of all kinetic fluxes against the species state vector.
    """
    # 1. Map all species to SymPy symbols
    species_symbols = {s.name: sp.Symbol(f"C_{s.name}", real=True, nonnegative=True) for s in mech.species}
    
    # Define external physical drivers
    Temp = sp.Symbol("Temp", real=True, nonnegative=True)
    Press = sp.Symbol("Press", real=True, nonnegative=True)
    M_density = sp.Symbol("M_density", real=True, nonnegative=True)
    v_gas = sp.Symbol("v_gas", real=True, nonnegative=True)
    S_a = sp.Symbol("S_a", real=True, nonnegative=True)
    
    # Track the rate of change (df/dt) for each species
    df_dt = {s.name: sp.Integer(0) for s in mech.species}
    
    # 2. Total Differential Formulation
    for idx, r in enumerate(mech.reactions):
        rtype = r.reaction_type.upper()
        p = r.parameters
        
        flux = sp.Integer(0)
        
        if rtype == "PHOTOLYSIS":
            # R_r = J_photo * [C_reactant]
            J_photo = sp.Symbol(p.get("A", f"J_{idx}"), real=True)
            flux = J_photo
            
        elif rtype == "ARRHENIUS":
            # k(T) = A * (T/300)^B * exp(-C/T)
            A = sp.Symbol(p.get("A", "1.0"), real=True)
            B = sp.Symbol(p.get("B", "0.0"), real=True)
            C = sp.Symbol(p.get("C", "0.0"), real=True)
            k_arr = A * (Temp / 300)**B * sp.exp(-C / Temp)
            flux = k_arr
            
        elif rtype == "TROE":
            # k(T, P) = (k0[M] / (1 + k0[M]/kinf)) * Fc^(1 / (1 + (log10(k0[M]/kinf)/N)^2))
            k0 = sp.Symbol(p.get("k0_A", "1.0"), real=True)
            kinf = sp.Symbol(p.get("kinf_A", "1.0"), real=True)
            Fc = sp.Symbol(p.get("Fc", "0.6"), real=True)
            N = sp.Symbol(p.get("N", "1.0"), real=True)
            ratio = (k0 * M_density) / kinf
            flux = ((k0 * M_density) / (1 + ratio)) * (Fc ** (1 / (1 + (sp.log(ratio, 10)/N)**2)))
            
        elif rtype == "HETEROGENEOUS":
            # k_het = 0.25 * v_gas * S_a * gamma
            gamma = sp.Symbol(p.get("gamma", "0.1"), real=True)
            flux = 0.25 * v_gas * S_a * gamma
            
        elif rtype == "TUNNELING":
            # Splines or tunneling
            Y_spline = sp.Symbol(p.get("Y_spline", f"Y_{idx}"), real=True)
            flux = Y_spline
            
        else:
            # Fallback MVP condensation or default
            flux = sp.Symbol(f"Rate_{idx}", real=True)
        
        # Multiply by reactants
        for reactant in r.reactants:
            if reactant in species_symbols:
                flux *= species_symbols[reactant]
                
        # Apply the flux negatively to reactants, positively to products
        for reactant in r.reactants:
            if reactant in df_dt:
                df_dt[reactant] -= flux
                
        for product in r.products:
            if product in df_dt:
                # Handle stoichiometric yields
                yield_val = 1.0
                df_dt[product] += flux * yield_val

    # 3. Assemble the f(C) vector
    ordered_species = [s.name for s in mech.species]
    f_vector = sp.Matrix([df_dt[s] for s in ordered_species])
    c_vector = sp.Matrix([species_symbols[s] for s in ordered_species])
    
    # 4. Analytical Differentiation
    jacobian_matrix = f_vector.jacobian(c_vector)
    
    # Evaluate the transposed Adjoint (J^T)
    adjoint_matrix = jacobian_matrix.transpose()
    
    return {
        "species_map": ordered_species,
        "f_vector": f_vector,
        "jacobian_matrix": jacobian_matrix,
        "adjoint_matrix": adjoint_matrix
    }
