"""Safe scalar expression lowering for state-dependent reaction laws.

Author: MKPP contributors. History: 2026-10, modal process YAML support.
Usage: compile mechanism expressions; no runtime I/O or Python evaluation.
"""

import ast
import math
import operator

import sympy as sp


def parse_rate_expression(source: str | float, symbols: dict[str, sp.Expr]) -> sp.Expr:
    """Build a SymPy expression from an allowlisted arithmetic syntax.

    Parameters
    ----------
    source : str or float
        Arithmetic expression with declared names and supported math functions.
    symbols : dict[str, sympy.Expr]
        State/environment symbols and previously expanded rate definitions.

    Returns
    -------
    sympy.Expr
        Expression sharing the exact symbols used for Jacobian differentiation.

    Raises
    ------
    ValueError
        If the expression contains unknown names, unsafe syntax, or nonfinite values.
    """
    functions = {
        "exp": sp.exp,
        "log": sp.log,
        "sqrt": sp.sqrt,
        "tanh": sp.tanh,
        "sin": sp.sin,
        "cos": sp.cos,
        "Abs": sp.Abs,
        "Piecewise": sp.Piecewise,
    }
    arithmetic = {
        ast.Add: operator.add,
        ast.Sub: operator.sub,
        ast.Mult: operator.mul,
        ast.Div: operator.truediv,
        ast.Pow: operator.pow,
    }
    comparisons = {ast.Lt: sp.Lt, ast.LtE: sp.Le, ast.Gt: sp.Gt, ast.GtE: sp.Ge, ast.Eq: sp.Eq, ast.NotEq: sp.Ne}

    def visit(node):
        if isinstance(node, ast.Constant):
            if isinstance(node.value, bool):
                return sp.true if node.value else sp.false
            if type(node.value) in (int, float) and math.isfinite(node.value):
                return sp.Integer(node.value) if isinstance(node.value, int) else sp.Float(node.value)
        elif isinstance(node, ast.Name) and node.id in symbols:
            return symbols[node.id]
        elif isinstance(node, ast.BinOp) and type(node.op) in arithmetic:
            return arithmetic[type(node.op)](visit(node.left), visit(node.right))
        elif isinstance(node, ast.UnaryOp) and isinstance(node.op, ast.UAdd | ast.USub):
            value = visit(node.operand)
            return value if isinstance(node.op, ast.UAdd) else -value
        elif isinstance(node, ast.Compare) and len(node.ops) == 1 and type(node.ops[0]) in comparisons:
            return comparisons[type(node.ops[0])](visit(node.left), visit(node.comparators[0]))
        elif isinstance(node, ast.BoolOp) and isinstance(node.op, ast.And | ast.Or):
            function = sp.And if isinstance(node.op, ast.And) else sp.Or
            return function(*(visit(value) for value in node.values))
        elif isinstance(node, ast.Tuple):
            return tuple(visit(value) for value in node.elts)
        elif isinstance(node, ast.Call) and isinstance(node.func, ast.Name) and not node.keywords:
            if node.func.id in functions:
                return functions[node.func.id](*(visit(arg) for arg in node.args))
        raise ValueError(f"FATAL ERROR: unsupported syntax or unknown name in rate expression: {ast.dump(node)}")

    if not isinstance(source, str | int | float) or isinstance(source, bool):
        raise ValueError("FATAL ERROR: rate expression must be a string or finite number")
    try:
        tree = ast.parse(str(source), mode="eval")
        if len(list(ast.walk(tree))) > 2048:
            raise ValueError("rate expression exceeds 2048 syntax nodes")
        expression = visit(tree.body)
        if not isinstance(expression, sp.Expr) or expression.has(sp.nan, sp.zoo, sp.oo, -sp.oo, sp.I):
            raise ValueError("rate expression must be a finite real scalar")
        # C printers cannot emit arbitrary Python functions or unresolved symbols.
        sp.ccode(expression)
        return expression
    except (SyntaxError, TypeError, ZeroDivisionError, OverflowError, RecursionError) as exc:
        raise ValueError(f"FATAL ERROR: invalid rate expression: {source}") from exc


def expand_rate_definitions(definitions: dict, symbols: dict[str, sp.Expr]) -> dict[str, sp.Expr]:
    """Expand ordered scalar definitions with no runtime parameters.

    Parameters
    ----------
    definitions : dict
        Names and expressions in dependency order; forward references are rejected.
    symbols : dict[str, sympy.Expr]
        Reserved state and environment symbols.

    Returns
    -------
    dict[str, sympy.Expr]
        Original symbols plus expanded definitions, retaining state derivatives.
    """
    if not isinstance(definitions, dict):
        raise ValueError("FATAL ERROR: rate_definitions must be a mapping")
    expanded = dict(symbols)
    reserved = {"exp", "log", "sqrt", "tanh", "sin", "cos", "Abs", "Piecewise", "True", "False"}
    for name, source in definitions.items():
        if not isinstance(name, str) or not name.isidentifier() or name in expanded or name in reserved:
            raise ValueError(f"FATAL ERROR: invalid or reserved rate definition: {name}")
        expanded[name] = parse_rate_expression(source, expanded)
    return expanded
