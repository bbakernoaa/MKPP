"""
Property-based test for W-entry coverage (Property 4).

# Feature: jinja2-codegen-templates, Property 4: Scaffold block W-entry coverage

For any LU_Plan with N species and a set of LU expressions, the set of W_i_j
declarations emitted by `w_matrix.j2` must be a superset of all W_i_j tokens
referenced in the LU factorization expressions — ensuring no undeclared-variable
errors in the generated C++.

**Validates: Requirements 3.1, 3.6**
"""

import re

from hypothesis import given, settings
from hypothesis import strategies as st
from mkpp.template_engine import TemplateEngine

# ---------------------------------------------------------------------------
# Strategies
# ---------------------------------------------------------------------------


@st.composite
def random_lu_plan(draw, min_n=2, max_n=8):
    """Generate a random LU plan with a sparsity pattern and LU expressions.

    Produces:
    - N: number of species
    - non_zero_jac_set: set of (i, j) positions with non-zero Jacobian
    - lu_expressions: list of dicts with {kind, i, j, expr} that reference W_i_j entries
    - needed_w: the set of W entries that should be declared (derived from
      diagonal entries + W references in lu_expressions)

    The sparsity pattern is random: diagonal entries are always present,
    off-diagonal entries appear with a drawn density. LU expressions reference
    W entries consistent with the sparsity pattern plus fill-in positions.
    """
    n = draw(st.integers(min_value=min_n, max_value=max_n))

    # Generate non-zero Jacobian structure: diagonal always present,
    # off-diagonal with random density
    density = draw(st.floats(min_value=0.1, max_value=0.7))
    non_zero_jac_set = set()
    for i in range(n):
        non_zero_jac_set.add((i, i))  # Diagonal always non-zero
    for i in range(n):
        for j in range(n):
            if i != j:
                if draw(st.floats(min_value=0.0, max_value=1.0)) < density:
                    non_zero_jac_set.add((i, j))

    # Generate LU expressions that reference W_i_j entries.
    # In a real Doolittle factorization:
    #   L_i_j (i > j) depends on W_i_j and products of L_i_k * U_k_j
    #   U_i_j (i <= j) depends on W_i_j and products of L_i_k * U_k_j
    # W entries referenced are those where the original matrix has non-zeros
    # or where fill-in occurs during elimination.
    lu_expressions = []
    w_refs_in_exprs = set()

    for i in range(n):
        for j in range(i, n):
            # U_i_j: references W_i_j always
            w_ref = (i, j)
            w_refs_in_exprs.add(w_ref)
            # Build a plausible expression
            terms = [f"W_{i}_{j}"]
            # May subtract L_i_k * U_k_j for k < i
            for k in range(i):
                if draw(st.booleans()):
                    terms.append(f"L_{i}_{k} * U_{k}_{j}")
            expr = " - ".join(terms) if len(terms) > 1 else terms[0]
            lu_expressions.append(
                {
                    "kind": "U",
                    "i": i,
                    "j": j,
                    "expr": expr,
                }
            )

    for i in range(n):
        for j in range(i):
            # L_i_j: references W_i_j, divided by U_j_j
            # Only emit if there's a structural non-zero or fill-in
            if (i, j) in non_zero_jac_set or draw(st.booleans()):
                w_ref = (i, j)
                w_refs_in_exprs.add(w_ref)
                terms = [f"W_{i}_{j}"]
                for k in range(j):
                    if draw(st.booleans()):
                        terms.append(f"L_{i}_{k} * U_{k}_{j}")
                expr_numer = " - ".join(terms) if len(terms) > 1 else terms[0]
                expr = f"({expr_numer}) / U_{j}_{j}"
                lu_expressions.append(
                    {
                        "kind": "L",
                        "i": i,
                        "j": j,
                        "expr": expr,
                    }
                )

    # Compute needed_w: diagonal entries + all W entries referenced in LU expressions
    needed_w = set()
    for i in range(n):
        needed_w.add((i, i))  # Diagonal always needed
    for entry in lu_expressions:
        for m in re.finditer(r"W_(\d+)_(\d+)", entry["expr"]):
            needed_w.add((int(m.group(1)), int(m.group(2))))

    return n, non_zero_jac_set, lu_expressions, sorted(needed_w)


# ---------------------------------------------------------------------------
# Property 4: Scaffold block W-entry coverage
# **Validates: Requirements 3.1, 3.6**
# ---------------------------------------------------------------------------


@given(data=random_lu_plan(min_n=2, max_n=8))
@settings(max_examples=100, deadline=None)
def test_property_4_w_entry_coverage(data):
    """
    For any LU plan, the set of W_i_j declarations emitted by `w_matrix.j2`
    must be a superset of all W_i_j tokens referenced in LU factorization
    expressions.

    This ensures no undeclared-variable errors in the generated C++.

    **Validates: Requirements 3.1, 3.6**
    """
    n, non_zero_jac_set, lu_expressions, needed_w = data

    # Render w_matrix.j2 macro by importing and calling it via a wrapper template
    engine = TemplateEngine()
    wrapper = (
        '{%- from "macros/w_matrix.j2" import emit_w_matrix -%}\n' "{{ emit_w_matrix(needed_w, non_zero_jac_set, inv_var, N) }}"
    )
    template = engine.env.from_string(wrapper)
    rendered = template.render(
        needed_w=needed_w,
        non_zero_jac_set=non_zero_jac_set,
        inv_var="inv_g_h",
        N=n,
    )

    # Extract W_i_j declarations from rendered output
    # Pattern: "double W_i_j = ..."
    declared_w = set()
    for m in re.finditer(r"double\s+W_(\d+)_(\d+)\s*=", rendered):
        declared_w.add((int(m.group(1)), int(m.group(2))))

    # Extract W_i_j references from all LU expressions
    referenced_w = set()
    for entry in lu_expressions:
        for m in re.finditer(r"W_(\d+)_(\d+)", entry["expr"]):
            referenced_w.add((int(m.group(1)), int(m.group(2))))

    # Property: declared W entries must be a superset of referenced W entries
    missing = referenced_w - declared_w
    assert missing == set(), (
        f"W-entry coverage violation: LU expressions reference W entries "
        f"that are not declared by w_matrix.j2.\n"
        f"Missing declarations: {sorted(missing)}\n"
        f"Declared: {sorted(declared_w)}\n"
        f"Referenced: {sorted(referenced_w)}\n"
        f"N={n}, needed_w={needed_w}"
    )
