"""SymPy-to-C expression formatting and peephole optimizations.

Converts symbolic ODE right-hand-side and Jacobian expressions into
C++ code strings suitable for Kokkos device kernels.
"""

import math
import re


def _fold_numeric_falloff_powers(code: str) -> str:
    """Fold pure numeric falloff powers emitted by SymPy's C printer."""
    number = r"[-+]?(?:\d+\.\d*|\d*\.\d+|\d+)(?:[eE][-+]?\d+)?"
    pattern = re.compile(
        rf"pow\(({number}),\s*1\.0/\(1\.0 \+ ({number})/pow\(M_LN10, 2\)\)\)"
    )

    def replace(match):
        base = float(match.group(1))
        coefficient = float(match.group(2))
        exponent = 1.0 / (1.0 + coefficient / (math.log(10.0) ** 2))
        return f"{base ** exponent:.17g}"

    return pattern.sub(replace, code)


def _strength_reduce_squares(code: str) -> str:
    """Replace generated pow(x, 2) terms with explicit multiplication."""
    term = r"(?:state\(\d+\)|Ynew_\d+|S_\d+)"
    return re.sub(rf"pow\(({term}), 2\)", r"\1 * \1", code)


def format_eqn(eqn_str, species_list, state_var="state", use_parentheses=True):
    import sympy as sp

    # 1. Clean up double negatives first because sympy might fail to parse `--` in strings
    s = str(eqn_str).replace('--', '+').replace('^+', '^').replace('**+', '**')
    if s == '0': return '0.0'

    # 2. Try to use SymPy's C-code generator for robust math formatting
    try:
        expr = sp.sympify(s)
        # Substitute legacy KPP dummy vars to 1.0 before C-code generation
        subs_dict = {
            # Legacy KPP dummy/fixed species (not real state variables)
            sp.Symbol('C_DummyCH4'): 1.0,
            sp.Symbol('C_DummyNMVOC'): 1.0,
            sp.Symbol('C_FixedOH'): 1.0,
            sp.Symbol('C_FixedCl'): 1.0,
            # Environmental parameters (not species concentrations)
            # NOTE: SUN is NOT substituted — photolysis rates are runtime J-values from Cloud-J
            sp.Symbol('TEMP'): 300.0,
            sp.Symbol('temp'): 300.0,
            sp.Symbol('Temp'): 300.0,
            sp.Symbol('S_a'): 1.0,
            sp.Symbol('v_gas'): 1.0,
        }

        expr = expr.subs(subs_dict)
        s = sp.ccode(expr)
        s = _fold_numeric_falloff_powers(s)
    except Exception as e:
        # Fallback to regex if sympy fails
        s = re.sub(r'([a-zA-Z0-9_\(\)\.\+\-\*\/]+)\*\*(\-?\d+\.\d+|\-?\d+)', r'pow(\1, \2)', s)
        s = s.replace('Temp', '300.0')
        s = s.replace('S_a', '1.0')
        s = s.replace('v_gas', '1.0')
        s = _fold_numeric_falloff_powers(s)

    # 3. Map the C_X species symbols from the SymPy AST directly into the state indices or variables.
    sorted_sp = sorted(list(enumerate(species_list)), key=lambda x: len(x[1].name), reverse=True)
    for idx_s, sp in sorted_sp:
        if use_parentheses:
            repl = f"{state_var}({idx_s})"
        else:
            repl = f"{state_var}_{idx_s}"
        s = re.sub(r'\bC_' + sp.name + r'(?!\w)', repl, s)

    # 4. Map J_<idx> photolysis symbols to the jvals array (Cloud-J runtime input)
    s = re.sub(r'\bJ_(\d+)\b', r'jvals[\1]', s)

    s = _strength_reduce_squares(s)

    return s
