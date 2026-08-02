import re
import sys

with open("mkpp-generated/gocart.hpp", "r") as f:
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
