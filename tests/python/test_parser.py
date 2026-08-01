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
                "k0_A": 1.0, "k0_B": 2.0, "k0_C": 3.0,
                "kinf_A": 4.0, "kinf_B": 5.0, "kinf_C": 6.0,
                "Fc": 0.6, "N": 1.0
            }
        ]
    }
    
    mech = parse_mechanism_micm("test", data)
    assert mech.reactions[0].reaction_type == "TROE"
    assert "k0_A" in mech.reactions[0].parameters
    assert mech.reactions[0].parameters["k0_A"] == "1.0"
