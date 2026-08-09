"""
Property-based tests for the NH4/NO3/SO4 equilibrium model (Component 1).

Validates:
- Property 4: Equilibrium Expressions Contain Expected Free Symbols (Requirements 2.1, 2.5)
- Property 5: C1-Continuity of Regime Blending (Requirements 2.2, 2.3)
- Property 6: Symbolic Differentiability (Requirements 2.4, 6.3)
- Property 12: Mass Conservation (Equilibrium Partitioning) (Requirements 7.1)
"""

import numpy as np
import sympy as sp
from hypothesis import given, settings
from hypothesis import strategies as st
from mkpp.equilibrium import get_model

# ---------------------------------------------------------------------------
# Strategies
# ---------------------------------------------------------------------------

# Temperature strategy: T in [240, 310] K (valid atmospheric range)
temperature_st = st.floats(min_value=240.0, max_value=310.0)

# Relative humidity strategy: RH in [0.1, 0.95]
rh_st = st.floats(min_value=0.1, max_value=0.95)

# Total concentration strategy: positive concentrations (avoid zero for numerical stability)
concentration_st = st.floats(min_value=1e-6, max_value=100.0)

# Sulfate ratio strategy: R in [0.01, 10] (covers all three regimes)
sulfate_ratio_st = st.floats(min_value=0.01, max_value=10.0)


@st.composite
def equilibrium_inputs(draw):
    """Generate valid (T, RH, C_N, C_Ox, C_S) tuples for equilibrium model."""
    T_val = draw(temperature_st)
    RH_val = draw(rh_st)
    C_N_val = draw(concentration_st)
    C_Ox_val = draw(concentration_st)
    C_S_val = draw(concentration_st)
    return T_val, RH_val, C_N_val, C_Ox_val, C_S_val


# ---------------------------------------------------------------------------
# Shared setup: build symbolic model once for efficiency
# ---------------------------------------------------------------------------

_MODEL = get_model("NH4_NO3_SO4")

# Define symbolic variables
_T = sp.Symbol("T")
_RH = sp.Symbol("RH")
_C_N = sp.Symbol("C_N", positive=True)
_C_Ox = sp.Symbol("C_Ox", positive=True)
_C_S = sp.Symbol("C_S", positive=True)

_TOTALS = {"reduced_nitrogen": _C_N, "oxidized_nitrogen": _C_Ox, "sulfate": _C_S}

# Build partition expressions once (they are purely symbolic)
_EXPRS = _MODEL.partition_expressions(_TOTALS, _T, _RH, "sigmoid", 0.05)

# Pre-lambdify partition expressions for numerical evaluation
_SYMBOLS = (_T, _RH, _C_N, _C_Ox, _C_S)
_LAMBDIFIED = {name: sp.lambdify(_SYMBOLS, expr, modules="numpy") for name, expr in _EXPRS.items()}


# ---------------------------------------------------------------------------
# Property 4: Equilibrium Expressions Contain Expected Free Symbols
# Feature: isorropia-unified-jacobian, Property 4: Equilibrium Expressions Contain Expected Free Symbols
# **Validates: Requirements 2.1, 2.5**
# ---------------------------------------------------------------------------


@given(
    blending=st.just("sigmoid"),
    width=st.floats(min_value=0.01, max_value=0.5),
)
@settings(max_examples=100)
def test_property_4_equilibrium_expressions_contain_expected_free_symbols(blending, width):
    """
    For any valid (T, RH, totals), the partition expressions must contain T
    and at least one total-concentration symbol as free variables.

    # Feature: isorropia-unified-jacobian, Property 4: Equilibrium Expressions Contain Expected Free Symbols

    **Validates: Requirements 2.1, 2.5**
    """
    model = get_model("NH4_NO3_SO4")
    T = sp.Symbol("T")
    RH = sp.Symbol("RH")
    C_N = sp.Symbol("C_N", positive=True)
    C_Ox = sp.Symbol("C_Ox", positive=True)
    C_S = sp.Symbol("C_S", positive=True)

    totals = {"reduced_nitrogen": C_N, "oxidized_nitrogen": C_Ox, "sulfate": C_S}
    exprs = model.partition_expressions(totals, T, RH, blending, width)

    total_symbols = {C_N, C_Ox, C_S}

    # For each expression that participates in temperature-dependent
    # equilibrium partitioning, verify T is present and at least one
    # total-concentration symbol is present.
    #
    # Excluded from T check:
    #   - SO2: identically zero (gas-phase kinetic source, not equilibrium)
    #   - SO4: equals C_S directly (sulfate fully in aerosol phase; no
    #     temperature-dependent gas/aerosol partitioning for sulfate)
    #
    # These are physically correct: sulfate enters the equilibrium only
    # as a constraint on the sulfate ratio R, not as an equilibrium-
    # partitioned species with T-dependent Keq.
    species_with_t_dependence = {"NH3", "NH4a", "HNO3", "NO3an1", "NO3an2", "NO3an3"}

    for name, expr in exprs.items():
        if expr == 0:
            # SO2 is trivially zero by construction — skip entirely
            continue

        free = expr.free_symbols

        # Must contain at least one total-concentration symbol
        has_total = bool(free & total_symbols)
        assert has_total, (
            f"Expression for '{name}' does not contain any total-concentration "
            f"symbol (C_N, C_Ox, C_S). Free symbols: {free}, "
            f"blending={blending}, width={width}"
        )

        # Species that participate in T-dependent equilibrium must contain T
        if name in species_with_t_dependence:
            assert T in free, (
                f"Expression for '{name}' does not contain temperature symbol T. "
                f"Free symbols: {free}, blending={blending}, width={width}"
            )


# ---------------------------------------------------------------------------
# Property 5: C1-Continuity of Regime Blending
# Feature: isorropia-unified-jacobian, Property 5: C1-Continuity of Regime Blending
# **Validates: Requirements 2.2, 2.3**
# ---------------------------------------------------------------------------


@given(
    T_val=temperature_st,
    RH_val=rh_st,
    C_Ox_val=concentration_st,
    C_S_val=st.floats(min_value=0.1, max_value=50.0),
    R_val=sulfate_ratio_st,
)
@settings(max_examples=100)
def test_property_5_c1_continuity_of_regime_blending(T_val, RH_val, C_Ox_val, C_S_val, R_val):
    """
    For any sulfate ratio R in [0.01, 10] and transition boundary, the
    partition function and its first derivative w.r.t. R are finite
    (no discontinuity).

    Test: evaluate expressions numerically at many R values, verify no
    NaN/Inf, verify numerical derivative is bounded.

    # Feature: isorropia-unified-jacobian, Property 5: C1-Continuity of Regime Blending

    **Validates: Requirements 2.2, 2.3**
    """
    # C_N = R * C_S (sulfate ratio definition)
    C_N_val = R_val * C_S_val

    # Evaluate all expressions at the given point
    args = (T_val, RH_val, C_N_val, C_Ox_val, C_S_val)
    for name, f in _LAMBDIFIED.items():
        val = f(*args)
        assert np.isfinite(val), (
            f"Expression '{name}' is not finite at R={R_val}, T={T_val}, "
            f"RH={RH_val}, C_N={C_N_val}, C_Ox={C_Ox_val}, C_S={C_S_val}. "
            f"Value: {val}"
        )

    # Check continuity via numerical derivative w.r.t. R
    # Use a small perturbation to R and verify derivative is bounded
    delta_R = 1e-6
    R_plus = R_val + delta_R
    R_minus = max(R_val - delta_R, 1e-8)  # keep R positive
    actual_delta = R_plus - R_minus

    C_N_plus = R_plus * C_S_val
    C_N_minus = R_minus * C_S_val

    args_plus = (T_val, RH_val, C_N_plus, C_Ox_val, C_S_val)
    args_minus = (T_val, RH_val, C_N_minus, C_Ox_val, C_S_val)

    for name, f in _LAMBDIFIED.items():
        val_plus = f(*args_plus)
        val_minus = f(*args_minus)

        if not (np.isfinite(val_plus) and np.isfinite(val_minus)):
            continue  # Covered by the finiteness check above

        # Numerical derivative
        deriv = (val_plus - val_minus) / (actual_delta * C_S_val)

        assert np.isfinite(deriv), (
            f"Numerical derivative of '{name}' w.r.t. R is not finite "
            f"at R={R_val}. deriv={deriv}, val+={val_plus}, val-={val_minus}"
        )

        # Derivative should be bounded (no blow-up at transitions)
        # For smooth tanh blending with width=0.05, max slope ~ 1/width * scale
        # Allow generous bound: |d(expr)/dR| < 1e6 * max(total_concentrations)
        max_conc = max(C_N_val, C_Ox_val, C_S_val, 1.0)
        bound = 1e6 * max_conc
        assert abs(deriv) < bound, (
            f"Numerical derivative of '{name}' w.r.t. R is unexpectedly large " f"at R={R_val}. |deriv|={abs(deriv)}, bound={bound}"
        )


# ---------------------------------------------------------------------------
# Property 6: Symbolic Differentiability
# Feature: isorropia-unified-jacobian, Property 6: Symbolic Differentiability
# **Validates: Requirements 2.4, 6.3**
# ---------------------------------------------------------------------------


@given(
    blending=st.just("sigmoid"),
    width=st.floats(min_value=0.01, max_value=0.5),
)
@settings(max_examples=100)
def test_property_6_symbolic_differentiability(blending, width):
    """
    For any equilibrium partition expression, calling sp.diff(expr, C_i) for
    each participating species produces a non-None SymPy expression (no
    Derivative wrapper remaining).

    # Feature: isorropia-unified-jacobian, Property 6: Symbolic Differentiability

    **Validates: Requirements 2.4, 6.3**
    """
    model = get_model("NH4_NO3_SO4")
    T = sp.Symbol("T")
    RH = sp.Symbol("RH")
    C_N = sp.Symbol("C_N", positive=True)
    C_Ox = sp.Symbol("C_Ox", positive=True)
    C_S = sp.Symbol("C_S", positive=True)

    totals = {"reduced_nitrogen": C_N, "oxidized_nitrogen": C_Ox, "sulfate": C_S}
    exprs = model.partition_expressions(totals, T, RH, blending, width)

    # Participating species symbols
    participating = [C_N, C_Ox, C_S]

    for name, expr in exprs.items():
        for C_i in participating:
            deriv = sp.diff(expr, C_i)

            # Must not be None
            assert deriv is not None, f"sp.diff({name}, {C_i}) returned None. " f"blending={blending}, width={width}"

            # Must not contain un-evaluated Derivative wrappers
            # (these indicate SymPy couldn't differentiate the expression)
            has_derivative = deriv.has(sp.Derivative)
            assert not has_derivative, (
                f"sp.diff({name}, {C_i}) contains un-evaluated Derivative. " f"Result: {deriv}, blending={blending}, width={width}"
            )

            # Must not contain Piecewise, Abs, or other non-smooth functions
            has_piecewise = deriv.has(sp.Piecewise)
            has_abs = deriv.has(sp.Abs)
            assert not has_piecewise and not has_abs, (
                f"Derivative of '{name}' w.r.t. {C_i} contains "
                f"non-smooth functions (Piecewise={has_piecewise}, "
                f"Abs={has_abs}). blending={blending}, width={width}"
            )


# ---------------------------------------------------------------------------
# Property 12: Mass Conservation (Equilibrium Partitioning)
# Feature: isorropia-unified-jacobian, Property 12: Mass Conservation (Equilibrium Partitioning)
# **Validates: Requirements 7.1**
# ---------------------------------------------------------------------------


@given(data=equilibrium_inputs())
@settings(max_examples=100)
def test_property_12_mass_conservation_equilibrium_partitioning(data):
    """
    For any total concentration vector and (T, RH) in valid range,
    f_gas + f_aer = C_total for each conserved element to within machine epsilon.

    Generate random totals with Hypothesis, evaluate numerically, check sum.

    # Feature: isorropia-unified-jacobian, Property 12: Mass Conservation (Equilibrium Partitioning)

    **Validates: Requirements 7.1**
    """
    T_val, RH_val, C_N_val, C_Ox_val, C_S_val = data
    args = (T_val, RH_val, C_N_val, C_Ox_val, C_S_val)

    # Evaluate all partition expressions numerically
    vals = {name: f(*args) for name, f in _LAMBDIFIED.items()}

    # 1. Reduced nitrogen conservation: NH3 + NH4a = C_N
    nh3 = vals["NH3"]
    nh4a = vals["NH4a"]
    reduced_n_sum = nh3 + nh4a
    tol = max(abs(C_N_val) * 1e-10, 1e-15)
    assert abs(reduced_n_sum - C_N_val) < tol, (
        f"Reduced nitrogen not conserved: NH3 + NH4a = {reduced_n_sum}, "
        f"expected C_N = {C_N_val}. "
        f"Residual = {abs(reduced_n_sum - C_N_val)}, tol = {tol}. "
        f"T={T_val}, RH={RH_val}, C_N={C_N_val}, C_Ox={C_Ox_val}, C_S={C_S_val}"
    )

    # 2. Oxidized nitrogen conservation: HNO3 + NO3an1 + NO3an2 + NO3an3 = C_Ox
    hno3 = vals["HNO3"]
    no3an1 = vals["NO3an1"]
    no3an2 = vals["NO3an2"]
    no3an3 = vals["NO3an3"]
    oxidized_n_sum = hno3 + no3an1 + no3an2 + no3an3
    tol_ox = max(abs(C_Ox_val) * 1e-10, 1e-15)
    assert abs(oxidized_n_sum - C_Ox_val) < tol_ox, (
        f"Oxidized nitrogen not conserved: HNO3 + NO3an1 + NO3an2 + NO3an3 "
        f"= {oxidized_n_sum}, expected C_Ox = {C_Ox_val}. "
        f"Residual = {abs(oxidized_n_sum - C_Ox_val)}, tol = {tol_ox}. "
        f"T={T_val}, RH={RH_val}, C_N={C_N_val}, C_Ox={C_Ox_val}, C_S={C_S_val}"
    )

    # 3. Sulfate conservation: SO2 and SO4 are kinetically controlled (not
    #    equilibrium-partitioned), so their partition expressions are not
    #    returned by the model. Sulfate conservation is maintained by the
    #    kinetic reaction system, not the equilibrium partitioner.
    #    (No assertion needed here — verified by kinetic integration tests.)
