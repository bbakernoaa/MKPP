import pytest
from mkpp.parser import parse_mechanism_micm

def test_parse_complex_troe_parameters():
    data = {
        "species": [{"name": "O"}, {"name": "O2"}, {"name": "O3"}, {"name": "M"}],
        "reactions": [
            {
                "type": "TROE",
                "reactants": {"O": {}, "O2": {}},
                "products": {"O3": {}},
                "k0": {"A": 1.0, "B": 2.0, "C": 3.0},
                "kinf": {"A": 4.0, "B": 5.0, "C": 6.0},
                "Fc": 0.6, "N": 1.0
            }
        ]
    }
    
    mech = parse_mechanism_micm("test", data)
    assert mech.reactions[0].reaction_type == "TROE"
    assert "k0" in mech.reactions[0].parameters
    assert mech.reactions[0].parameters["k0"]["A"] == 1.0
    assert mech.reactions[0].parameters["kinf"]["C"] == 6.0
