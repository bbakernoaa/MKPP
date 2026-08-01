import argparse
import re
import yaml
from pathlib import Path

def parse_spc(filepath):
    species = []
    with open(filepath, 'r') as f:
        content = f.read()
    
    # Simple regex to catch species defs
    for line in content.split('\n'):
        line = line.strip()
        if not line or line.startswith('#'): continue
        if '=' in line and ';' in line and ('IGNORE' in line or 'H' in line or 'O' in line or 'C' in line):
            sp_name = line.split('=')[0].strip()
            species.append({"name": sp_name})
    return species

def parse_eqn(filepath):
    reactions = []
    with open(filepath, 'r') as f:
        # Strip newlines and spaces that break line parsing
        content = f.read().replace('\\\n', '')

    for line in content.split('\n'):
        line = line.strip()
        if not line or line.startswith('#'): continue
        if '=' in line and ':' in line and line.endswith(';'):
            # <label> A + B = C : RATE ;
            match = re.match(r'(?:<[^>]+>\s*)?([^=]+)=([^:]+):\s*(.+);', line)
            if match:
                react_str = match.group(1).strip()
                prod_str = match.group(2).strip()
                rate_str = match.group(3).strip()
                
                # Parse reactants
                reactants = {}
                for r in react_str.split('+'):
                    r = r.strip()
                    if not r: continue
                    # Handle stoichiometric coeffs
                    s_match = re.match(r'(\d*\.?\d*)\s*([A-Za-z0-9_]+)', r)
                    if s_match:
                        coeff = float(s_match.group(1)) if s_match.group(1) else 1.0
                        sp = s_match.group(2)
                        reactants[sp] = reactants.get(sp, 0.0) + coeff
                    else:
                        reactants[r] = reactants.get(r, 0.0) + 1.0
                        
                # Parse products
                products = {}
                for p in prod_str.split('+'):
                    p = p.strip()
                    if not p: continue
                    # Handle stoichiometric coeffs
                    s_match = re.match(r'(\d*\.?\d*)\s*([A-Za-z0-9_]+)', p)
                    if s_match:
                        coeff = float(s_match.group(1)) if s_match.group(1) else 1.0
                        sp = s_match.group(2)
                        products[sp] = products.get(sp, 0.0) + coeff
                    else:
                        products[p] = products.get(p, 0.0) + 1.0

                # Determine type
                rtype = "ARRHENIUS"
                if 'hv' in reactants:
                    rtype = "PHOTOLYSIS"
                    del reactants['hv']
                    
                rxn = {
                    "type": rtype,
                    "reactants": {k: float(v) for k,v in reactants.items()},
                    "products": {k: float(v) for k,v in products.items()}
                }
                
                # Simplify the rate parsing by just saving the string as A for now, 
                # this allows us to compile it while we parse raw KPP rate macros
                # Extract rate and convert macros
                if rate_str.startswith("ARR_ab("):
                    args = rate_str.replace("ARR_ab(", "").replace(")", "").split(",")
                    if len(args) >= 2:
                        rxn["A"] = args[0].strip().replace("e0", "")
                        rxn["B"] = 0.0
                        rxn["C"] = args[1].strip().replace("e0", "")
                elif rate_str.startswith("ARR_ac("):
                    args = rate_str.replace("ARR_ac(", "").replace(")", "").split(",")
                    if len(args) >= 2:
                        rxn["A"] = args[0].strip().replace("e0", "")
                        rxn["B"] = args[1].strip().replace("e0", "")
                        rxn["C"] = 0.0
                elif rate_str.startswith("ARR_abc("):
                    args = rate_str.replace("ARR_abc(", "").replace(")", "").split(",")
                    if len(args) >= 3:
                        rxn["A"] = args[0].strip().replace("e0", "")
                        rxn["C"] = args[1].strip().replace("e0", "")
                        rxn["B"] = args[2].strip().replace("e0", "")
                elif rate_str.startswith("("):
                    rxn["A"] = rate_str.replace("(", "").replace(")", "").replace("e0", "")
                else:
                    rxn["A"] = rate_str.replace("*(SUN/60.0e0)", "").replace("e0", "").replace("*(SUN/60.0)", "")
                
                if rtype == "PHOTOLYSIS":
                    rxn["continuous_transition"] = True
                    rxn["stiff"] = False
                else:
                    rxn["stiff"] = True
                    
                reactions.append(rxn)
    return reactions

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("name")
    parser.add_argument("spc")
    parser.add_argument("eqn")
    parser.add_argument("out")
    args = parser.parse_args()
    
    species = parse_spc(args.spc)
    reactions = parse_eqn(args.eqn)
    
    doc = {
        "name": args.name,
        "description": f"Translated from {args.name} KPP mechanism",
        "species": species,
        "reactions": reactions,
        "host_interface": {
            "arrays": [
                {
                    "name": "concentrations",
                    "rank": 4,
                    "layout": "LayoutLeft",
                    "extent": [5, 10, 10, 1]
                }
            ]
        }
    }
    
    with open(args.out, 'w') as f:
        yaml.dump(doc, f, sort_keys=False)
        
    print(f"Translated {args.name} -> {args.out}")

if __name__ == "__main__":
    main()
