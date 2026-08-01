import networkx as nx
from .model import MechanismDefinition

def reduce_mechanism_drgep(mech: MechanismDefinition, threshold: float = 0.05) -> MechanismDefinition:
    """
    Direct Relation Graph with Error Propagation (DRGEP) method.
    Calculates species interaction coefficients, prunes those below the threshold,
    and returns a pruned mechanism definition.
    """
    G = nx.DiGraph()
    
    # 1. Add all species
    for sp in mech.species:
        G.add_node(sp.name)
        
    # 2. Add weighted edges based on reaction connectivity
    # For a real DRGEP, you calculate the specific reaction rates over a trajectory.
    # Because we are doing an AOT (Ahead-of-Time) reduction without dynamic simulation data,
    # we approximate the relationship using stoichiometric connectivity.
    for r in mech.reactions:
        for reactant, r_stoich in r.reactants.items():
            for product, p_stoich in r.products.items():
                if reactant == product: continue
                # Add directed dependency: Product depends on Reactant
                if not G.has_edge(reactant, product):
                    G.add_edge(reactant, product, weight=0.0)
                G[reactant][product]['weight'] += r_stoich * p_stoich
                
    # Normalize weights
    for node in G.nodes():
        total_weight = sum([data['weight'] for _, _, data in G.out_edges(node, data=True)])
        if total_weight > 0:
            for _, v, data in G.out_edges(node, data=True):
                data['weight'] /= total_weight
                
    # 3. Prune species below threshold
    # Since we lack error propagation logic over a time integration, we use simple degree pruning for the AOT fallback.
    pruned_species = set()
    for node in G.nodes():
        if G.out_degree(node) == 0 and G.in_degree(node) == 0:
            pruned_species.add(node)
            continue
        max_dependency = max([data['weight'] for _, _, data in G.in_edges(node, data=True)] + [0.0])
        if max_dependency < threshold:
            pruned_species.add(node)
            
    # Always keep target radicals/oxidants for integrity
    keep_list = {"OH", "HO2", "NO", "NO2", "O3", "O3P", "O1D"}
    for sp in list(pruned_species):
        if sp in keep_list:
            pruned_species.remove(sp)
            
    # Create new species list
    new_species = [s for s in mech.species if s.name not in pruned_species]
    
    # 4. Prune reactions where all reactants OR all products were pruned
    new_reactions = []
    for r in mech.reactions:
        reactants_exist = any(react not in pruned_species for react in r.reactants.keys())
        products_exist = any(prod not in pruned_species for prod in r.products.keys())
        # We drop the reaction if it's completely disconnected from the active graph
        if reactants_exist or products_exist:
            # We must also clean up the dicts so they don't reference pruned species in SymPy AST
            new_r = r
            new_r.reactants = {k: v for k, v in r.reactants.items() if k not in pruned_species}
            new_r.products = {k: v for k, v in r.products.items() if k not in pruned_species}
            if len(new_r.reactants) > 0 or len(new_r.products) > 0:
                new_reactions.append(new_r)
            
    mech.species = new_species
    mech.reactions = new_reactions
    return mech
