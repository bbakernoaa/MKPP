"""Jinja2-based C++ code renderer for MKPP solver headers."""

from __future__ import annotations

import re
from pathlib import Path

from jinja2 import Environment, FileSystemLoader, StrictUndefined


def _sub_state_var(expr: str, new_prefix: str) -> str:
    """Replace state variable prefix S_ with a new prefix in formatted expressions.

    This is used when evaluating F-vector expressions at intermediate
    Rosenbrock stages (Y2, Y3, ...) rather than at the initial state (S).

    Parameters
    ----------
    expr : str
        C++ expression containing ``S_<digits>`` state variable references.
    new_prefix : str
        New prefix to use (e.g. ``"Y2"``, ``"Y3"``).

    Returns
    -------
    str
        Expression with ``S_<digits>`` replaced by ``{new_prefix}_<digits>``.
    """
    return re.sub(r"\bS_(\d+)\b", rf"{new_prefix}_\1", expr)


def _sub_prefixes(
    expr: str,
    rhs: str = "b",
    y: str = "y",
    x: str = "x",
) -> str:
    """Replace placeholder variable prefixes in LU substitution expressions.

    Performs regex-based substitution of generic variable names used in
    symbolic LU plan expressions with context-appropriate C++ variable
    prefixes. This is the Jinja2 filter equivalent of the ``re.sub`` calls
    in ``symbolic_emit.py``.

    Substitutions performed (in order):
      - ``b_<digits>`` → ``{rhs}_<digits>``  (RHS vector entries)
      - ``y_<digits>`` → ``{y}_<digits>``    (intermediate vector entries)
      - ``x_<digits>`` → ``{x}_<digits>``    (solution vector entries)

    Parameters
    ----------
    expr : str
        The raw expression string containing ``b_i``, ``y_i``, ``x_i``
        placeholders (e.g. ``"b_0 - L_1_0 * y_0"``).
    rhs : str
        Prefix to substitute for ``b`` (e.g. ``"rhs1"``, ``"F1"``).
    y : str
        Prefix to substitute for ``y`` (e.g. ``"y1"``, ``"yt1"``).
    x : str
        Prefix to substitute for ``x`` (e.g. ``"K1"``, ``"u1"``).

    Returns
    -------
    str
        The expression with all prefix substitutions applied.

    Examples
    --------
    >>> _sub_prefixes("b_0 - L_1_0 * y_0", rhs="F1", y="y1", x="K1")
    'F1_0 - L_1_0 * y1_0'
    >>> _sub_prefixes("y_2 / U_2_2", rhs="rhs1", y="y1", x="K1")
    'y1_2 / U_2_2'
    >>> _sub_prefixes("y_1 - U_1_0 * x_0", rhs="v1", y="yt1", x="u1")
    'yt1_1 - U_1_0 * u1_0'
    """
    result = re.sub(r"\bb_(\d+)\b", rf"{rhs}_\1", expr)
    result = re.sub(r"\by_(\d+)\b", rf"{y}_\1", result)
    result = re.sub(r"\bx_(\d+)\b", rf"{x}_\1", result)
    return result


class TemplateEngine:
    """Jinja2-based C++ code renderer for MKPP solver headers.

    Loads templates from a dedicated directory and renders them with
    StrictUndefined to catch missing context variables immediately.
    """

    def __init__(self, template_dir: Path | None = None):
        """Initialize with template directory.

        Parameters
        ----------
        template_dir : Path | None
            Path to the Jinja2 template directory. Defaults to
            ``src/mkpp/templates/`` relative to this module.

        Raises
        ------
        FileNotFoundError
            If the specified template directory does not exist.
        """
        if template_dir is None:
            template_dir = Path(__file__).parent / "templates"
        if not template_dir.is_dir():
            raise FileNotFoundError(
                f"Template directory not found: {template_dir}"
            )
        self.env = Environment(
            loader=FileSystemLoader(str(template_dir)),
            undefined=StrictUndefined,
            trim_blocks=True,
            lstrip_blocks=True,
            keep_trailing_newline=True,
        )
        # Register custom filters
        self.env.filters["sub_prefixes"] = _sub_prefixes
        self.env.filters["sub_state_var"] = _sub_state_var

    def render(self, template_name: str, context: dict) -> str:
        """Render a template with the given context dictionary.

        Parameters
        ----------
        template_name : str
            Name of the template file (relative to template_dir).
        context : dict
            Dictionary of variables to pass to the template.

        Returns
        -------
        str
            The rendered template output.

        Raises
        ------
        jinja2.TemplateNotFound
            If the template file does not exist.
        jinja2.UndefinedError
            If the template references a variable not present in context.
        """
        template = self.env.get_template(template_name)
        return template.render(**context)


def render_template(template_name: str, context: dict) -> str:
    """Convenience function for rendering a single template.

    Creates a TemplateEngine with the default template directory
    and renders the specified template with the given context.

    Parameters
    ----------
    template_name : str
        Name of the template file (relative to the default template dir).
    context : dict
        Dictionary of variables to pass to the template.

    Returns
    -------
    str
        The rendered template output.
    """
    engine = TemplateEngine()
    return engine.render(template_name, context)
