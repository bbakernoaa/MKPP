"""Unit tests for the NH4/NO3/SO4 equilibrium model.

Validates Requirements: 2.1, 2.2, 2.5
"""

import numpy as np
import pytest
import sympy as sp
from mkpp.equilibrium import EquilibriumModel, get_model
from mkpp.equilibrium.nh4_no3_so4 import NH4NO3SO4Model
from mkpp.model import CompilationError

# ---------------------------------------------------------------------------
# Fixtures
# ---------------------------------------------------------------------------


@pytest.fixture
def model():
    """Return an instance of the NH4NO3SO4Model."""
    return NH4NO3SO4Model()


@pytest.fixture
def symbols():
    """Return standard SymPy symbols for testing."""
    T = sp.Symbol("T", positive=True)
    RH = sp.Symbol("RH", positive=True)
    C_N = sp.Symbol("C_N", positive=True)
    C_Ox = sp.Symbol("C_Ox", positive=True)
    C_S = sp.Symbol("C_S", positive=True)
    return T, RH, C_N, C_Ox, C_S


# ---------------------------------------------------------------------------
# Test 1: species_map structure
# ---------------------------------------------------------------------------


def test_species_map_structure(model):
    """Verify species_map returns expected keys and values."""
    smap = model.species_map()

    # Expect exactly these conserved-element keys
    assert set(smap.keys()) == {"reduced_nitrogen", "oxidized_nitrogen", "sulfate"}

    # Each element maps to a list of species (gas + aerosol)
    assert smap["reduced_nitrogen"] == ["NH3", "NH4a"]
    assert smap["oxidized_nitrogen"] == ["HNO3", "NO3an1", "NO3an2", "NO3an3"]
    assert smap["sulfate"] == ["SO2", "SO4"]


# ---------------------------------------------------------------------------
# Test 2: equilibrium constants at Tref
# ---------------------------------------------------------------------------


def test_equilibrium_constants_at_tref(model):
    """Verify Keq(298.15) returns correct A values (within float tolerance)."""
    T = sp.Symbol("T", positive=True)
    keq_exprs = model.equilibrium_constants(T)

    # Expected reference values (at Tref=298.15K, the exponential term == 1)
    expected = {
        "Kp_NH4NO3": 4.39e-17,
        "Kp_NH4HSO4": 1.086e-2,
        "Kp_NH42SO4": 1.817e-25,
    }

    for name, A_expected in expected.items():
        assert name in keq_exprs, f"Missing equilibrium constant: {name}"
        val = float(keq_exprs[name].subs(T, 298.15))
        assert val == pytest.approx(A_expected, rel=1e-6), f"{name} at Tref: got {val}, expected {A_expected}"


# ---------------------------------------------------------------------------
# Test 3: equilibrium constants temperature dependence
# ---------------------------------------------------------------------------


def test_equilibrium_constants_temperature_dependence(model):
    """Verify Keq increases or decreases with T consistent with dH sign.

    For ISORROPIA-Lite dissociation reactions:
      Keq(T) = A * exp(-dH/R * (1/T - 1/Tref))

    With negative dH (exothermic dissociation):
      -dH/R is positive, and (1/T - 1/Tref) is negative when T > Tref
      => exponential term < 1 => Keq(T > Tref) < Keq(Tref)
      Conversely, Keq(T < Tref) > Keq(Tref)
    """
    T = sp.Symbol("T", positive=True)
    keq_exprs = model.equilibrium_constants(T)

    # All three reactions have negative dH in our model
    T_low = 270.0
    T_high = 320.0

    for name, expr in keq_exprs.items():
        val_low = float(expr.subs(T, T_low))
        val_ref = float(expr.subs(T, 298.15))
        val_high = float(expr.subs(T, T_high))

        # For negative dH: Keq should decrease as T increases
        assert val_low > val_ref > val_high, (
            f"{name}: expected Keq to decrease with T (negative dH), "
            f"got Keq({T_low})={val_low:.4e}, Keq(298.15)={val_ref:.4e}, "
            f"Keq({T_high})={val_high:.4e}"
        )


# ---------------------------------------------------------------------------
# Test 4: partition expressions in sulfate-rich regime (R < 1)
# ---------------------------------------------------------------------------


def test_partition_expressions_sulfate_rich_regime(model, symbols):
    """R < 1: verify NH3 ~ 0, NH4a ~ C_N numerically."""
    T, RH, C_N, C_Ox, C_S = symbols

    totals = {
        "reduced_nitrogen": C_N,
        "oxidized_nitrogen": C_Ox,
        "sulfate": C_S,
    }
    exprs = model.partition_expressions(totals, T, RH, blending="sigmoid", width=0.05)

    # Evaluate at conditions where R = C_N / C_S < 1
    # e.g., C_N = 1e-9, C_S = 5e-9 => R = 0.2
    subs = {C_N: 1e-9, C_Ox: 1e-9, C_S: 5e-9, T: 298.15, RH: 0.5}

    nh3_val = float(exprs["NH3"].subs(subs))
    nh4a_val = float(exprs["NH4a"].subs(subs))

    # In sulfate-rich regime, essentially all nitrogen is in aerosol
    assert nh3_val == pytest.approx(0.0, abs=1e-15), f"NH3 should be ~0 in sulfate-rich regime, got {nh3_val}"
    assert nh4a_val == pytest.approx(float(subs[C_N]), rel=1e-6), f"NH4a should be ~C_N in sulfate-rich regime, got {nh4a_val}"


# ---------------------------------------------------------------------------
# Test 5: partition expressions in ammonia-rich regime (R > 2)
# ---------------------------------------------------------------------------


def test_partition_expressions_ammonia_rich_regime(model, symbols):
    """R > 2: verify NH3 > 0, NH4a < C_N numerically."""
    T, RH, C_N, C_Ox, C_S = symbols

    totals = {
        "reduced_nitrogen": C_N,
        "oxidized_nitrogen": C_Ox,
        "sulfate": C_S,
    }
    exprs = model.partition_expressions(totals, T, RH, blending="sigmoid", width=0.05)

    # Evaluate at conditions where R = C_N / C_S >> 2
    # e.g., C_N = 1e-8, C_S = 1e-9 => R = 10
    subs = {C_N: 1e-8, C_Ox: 1e-9, C_S: 1e-9, T: 298.15, RH: 0.5}

    nh3_val = float(exprs["NH3"].subs(subs))
    nh4a_val = float(exprs["NH4a"].subs(subs))
    c_n_val = float(subs[C_N])

    # In ammonia-rich regime, there should be gas-phase NH3
    assert nh3_val > 0, f"NH3 should be > 0 in ammonia-rich regime, got {nh3_val}"
    assert nh4a_val < c_n_val, f"NH4a should be < C_N in ammonia-rich regime, got {nh4a_val} vs C_N={c_n_val}"
    # Conservation: NH3 + NH4a = C_N
    assert nh3_val + nh4a_val == pytest.approx(c_n_val, rel=1e-10)


# ---------------------------------------------------------------------------
# Test 6: partition expressions contain no forbidden SymPy operations
# ---------------------------------------------------------------------------


def test_partition_expressions_no_forbidden_sympy_ops(model, symbols):
    """Verify no Piecewise, Abs, Max, Min in partition expressions."""
    T, RH, C_N, C_Ox, C_S = symbols

    totals = {
        "reduced_nitrogen": C_N,
        "oxidized_nitrogen": C_Ox,
        "sulfate": C_S,
    }
    exprs = model.partition_expressions(totals, T, RH, blending="sigmoid", width=0.05)

    forbidden_types = (sp.Piecewise, sp.Abs, sp.Max, sp.Min)

    for species_name, expr in exprs.items():
        # Walk the expression tree looking for forbidden operations
        for node in sp.preorder_traversal(expr):
            assert not isinstance(node, forbidden_types), (
                f"Expression for '{species_name}' contains forbidden " f"operation: {type(node).__name__}"
            )


# ---------------------------------------------------------------------------
# Test 7: partition expressions conservation (NH3 + NH4a == C_N)
# ---------------------------------------------------------------------------


def test_partition_expressions_conservation_exact(model, symbols):
    """Verify NH3 + NH4a == C_N symbolically or numerically at multiple points."""
    T, RH, C_N, C_Ox, C_S = symbols

    totals = {
        "reduced_nitrogen": C_N,
        "oxidized_nitrogen": C_Ox,
        "sulfate": C_S,
    }
    exprs = model.partition_expressions(totals, T, RH, blending="sigmoid", width=0.05)

    # Symbolic check: NH3 + NH4a should simplify to C_N
    residual = sp.simplify(exprs["NH3"] + exprs["NH4a"] - C_N)
    if residual == 0:
        # Perfect symbolic conservation
        return

    # If SymPy cannot fully simplify, verify numerically at multiple test points
    rng = np.random.default_rng(42)
    test_points = []
    for _ in range(20):
        cn = rng.uniform(1e-10, 1e-6)
        cox = rng.uniform(1e-10, 1e-6)
        cs = rng.uniform(1e-10, 1e-6)
        t_val = rng.uniform(240.0, 310.0)
        rh_val = rng.uniform(0.1, 0.95)
        test_points.append({C_N: cn, C_Ox: cox, C_S: cs, T: t_val, RH: rh_val})

    for pt in test_points:
        nh3_val = float(exprs["NH3"].subs(pt))
        nh4a_val = float(exprs["NH4a"].subs(pt))
        cn_val = float(pt[C_N])
        total = nh3_val + nh4a_val
        assert total == pytest.approx(cn_val, rel=1e-10), (
            f"Conservation violated: NH3({nh3_val}) + NH4a({nh4a_val}) = " f"{total} != C_N({cn_val}) at point {pt}"
        )


# ---------------------------------------------------------------------------
# Test 8: registry get_model
# ---------------------------------------------------------------------------


def test_registry_get_model():
    """Verify `get_model("NH4_NO3_SO4")` returns NH4NO3SO4Model instance."""
    model = get_model("NH4_NO3_SO4")
    assert isinstance(model, NH4NO3SO4Model)
    assert isinstance(model, EquilibriumModel)


# ---------------------------------------------------------------------------
# Test 9: registry unknown system raises
# ---------------------------------------------------------------------------


def test_registry_unknown_system_raises():
    """Verify `get_model("INVALID")` raises CompilationError."""
    with pytest.raises(CompilationError) as exc_info:
        get_model("INVALID")

    assert "Unknown equilibrium system" in exc_info.value.message
    assert "INVALID" in exc_info.value.message
    assert exc_info.value.stage == "validation"
