import re
import sys
import os

repo_root = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
gocart_header = os.path.join(repo_root, "mkpp-generated", "gocart.hpp")

with open(gocart_header, "r") as f:
    content = f.read().lower()

emission_terms = ["emission", "saltation", "threshold velocity", "dust flux", "ustar", "u_thresh", "rustar", "fecandrylimit", "fecan", "gwettop", "roughness"]

found_terms = []
for term in emission_terms:
    if term in content:
        found_terms.append(term)

if found_terms:
    print(f"FAILED: Found emission-related terms in generated code: {found_terms}")
    sys.exit(1)
else:
    print("SUCCESS: No emission or saltation terms found in generated code.")
    sys.exit(0)
