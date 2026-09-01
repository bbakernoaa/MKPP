"""
Property-based tests for auto-reduction (Component 5).

Validates:
- Property 14: Auto-reduction freeze correctness (Requirements 5.3, 5.4)
- Property 15: Auto-reduction re-activation (Requirements 5.5, 5.6)
"""

import numpy as np
from hypothesis import assume, given, settings
from hypothesis import strategies as st

# ---------------------------------------------------------------------------
# Pure-Python auto-reduced ROS-2 single step implementation
# ---------------------------------------------------------------------------


def auto_reduced_ros2_step(state, f_func, jac_func, dt, atol, rtol, threshold):
    """
    One step of an auto-reduced ROS-2 Rosenbrock solver.

    Species with importance below threshold are frozen:
    - Their Jacobian rows/columns are zeroed (identity diagonal)
    - K1, K2 are forced to zero
    - Their state does not change

    Returns
    -------
    state_new : ndarray
        Updated state (frozen species unchanged)
    K1 : ndarray
        Stage 1 increment (zero for frozen species)
    K2 : ndarray
        Stage 2 increment (zero for frozen species)
    active : ndarray of bool
        Active mask (True = active, False = frozen)
    """
    N = len(state)
    g = 1.0 + 1.0 / np.sqrt(2.0)
    ros_A0 = 1.0 / g
    ros_C0 = -2.0 / g
    ros_M0 = 3.0 / (2.0 * g)
    ros_M1 = 1.0 / (2.0 * g)

    # Stage 1 rates
    F1 = f_func(state)

    # Determine active set based on importance
    active = np.array([abs(F1[i]) / (atol[i] + rtol[i] * abs(state[i])) >= threshold for i in range(N)])

    # Build Jacobian
    J = jac_func(state)

    # Zero rows/cols for frozen species
    for i in range(N):
        if not active[i]:
            J[i, :] = 0.0
            J[:, i] = 0.0

    # Form iteration matrix W = (1/(g*dt))*I - J
    inv_g_dt = 1.0 / (g * dt)
    W = inv_g_dt * np.eye(N) - J

    # Set identity rows for frozen species
    for i in range(N):
        if not active[i]:
            W[i, :] = 0.0
            W[i, i] = 1.0

    # Solve W * K1 = F1
    K1 = np.linalg.solve(W, F1)

    # Force K1=0 for frozen species
    K1[~active] = 0.0

    # Intermediate state for Stage 2
    Ynew = state + ros_A0 * K1

    # Stage 2 rates
    F2 = f_func(Ynew)
    rhs2 = F2 + (ros_C0 / dt) * K1

    # Solve W * K2 = rhs2
    K2 = np.linalg.solve(W, rhs2)

    # Force K2=0 for frozen species
    K2[~active] = 0.0

    # Update state (only active species change)
    state_new = state.copy()
    state_new += ros_M0 * K1 + ros_M1 * K2

    return state_new, K1, K2, active


# ---------------------------------------------------------------------------
# Strategies
# ---------------------------------------------------------------------------


@st.composite
def random_auto_reduction_scenario(draw, min_n=3, max_n=10):
    """
    Generate a random auto-reduction test scenario:
    - N-dimensional state vector
    - Diagonal Jacobian with known rates (for easy verification)
    - Importance values partially below threshold (some frozen species)
    """
    N = draw(st.integers(min_value=min_n, max_value=max_n))

    # Random positive state values (concentrations are positive)
    state = np.array([draw(st.floats(min_value=1.0, max_value=1e6)) for _ in range(N)])

    # Random diagonal rates (negative for stability, representing decay)
    rates = np.array([draw(st.floats(min_value=-10.0, max_value=-0.01)) for _ in range(N)])

    # The RHS for a diagonal system is: f(state) = rates * state
    # Importance_i = |rates[i] * state[i]| / (atol[i] + rtol[i] * |state[i]|)
    # We want SOME species to be frozen (importance < threshold)
    # and SOME to be active (importance >= threshold)

    # Choose a threshold that splits the species
    atol = np.full(N, 1e-3)
    rtol = np.full(N, 1e-4)

    importance = np.array([abs(rates[i] * state[i]) / (atol[i] + rtol[i] * abs(state[i])) for i in range(N)])

    # Pick threshold so at least 1 species is frozen and at least 1 is active
    sorted_imp = np.sort(importance)
    # Threshold between the smallest and largest importance
    # Ensure at least one frozen and one active
    lo = float(sorted_imp[0]) + 1e-10
    hi = float(sorted_imp[-1]) - 1e-10
    if N >= 2 and lo < hi:
        # Pick a threshold between the min and max importances
        threshold = draw(st.floats(min_value=lo, max_value=hi))
    else:
        # All importances equal or too close; skip this case
        threshold = float(sorted_imp[0]) + 1.0  # All frozen

    # Time step
    dt = draw(st.floats(min_value=0.01, max_value=10.0))

    return N, state, rates, atol, rtol, threshold, dt


@st.composite
def random_reactivation_scenario(draw, min_n=3, max_n=8):
    """
    Generate a scenario where a species transitions from frozen to active
    across two consecutive steps by changing rates.

    Step 1: species i has low rate (frozen)
    Step 2: species i has high rate (active)
    """
    N = draw(st.integers(min_value=min_n, max_value=max_n))

    # Random positive state
    state = np.array([draw(st.floats(min_value=1.0, max_value=1e4)) for _ in range(N)])

    atol = np.full(N, 1e-3)
    rtol = np.full(N, 1e-4)

    # Choose one species to transition (frozen → active)
    transition_idx = draw(st.integers(min_value=0, max_value=N - 1))

    # Set a moderate threshold
    threshold = 10.0

    # Rates for step 1: transition species has very small rate (frozen)
    rates_step1 = np.array([draw(st.floats(min_value=-10.0, max_value=-1.0)) for _ in range(N)])
    # Make transition species have very small rate so importance < threshold
    # importance = |rate * state| / (atol + rtol * |state|)
    # We want importance < threshold
    # => |rate| < threshold * (atol + rtol * state) / state
    max_rate_for_frozen = threshold * (atol[transition_idx] + rtol[transition_idx] * state[transition_idx]) / state[transition_idx]
    rates_step1[transition_idx] = -max_rate_for_frozen * 0.01  # Well below threshold

    # Rates for step 2: transition species has large rate (active)
    rates_step2 = rates_step1.copy()
    # Make transition species importance > threshold
    min_rate_for_active = threshold * (atol[transition_idx] + rtol[transition_idx] * state[transition_idx]) / state[transition_idx]
    rates_step2[transition_idx] = -min_rate_for_active * 100.0  # Well above threshold

    # Time step
    dt = draw(st.floats(min_value=0.1, max_value=1.0))

    return N, state, rates_step1, rates_step2, atol, rtol, threshold, dt, transition_idx


# ---------------------------------------------------------------------------
# Helper: build f_func and jac_func for a diagonal system
# ---------------------------------------------------------------------------


def make_diagonal_system(rates):
    """
    Create f_func and jac_func for a simple diagonal ODE system:
        dy/dt = rates * y  (element-wise)

    The Jacobian is a diagonal matrix with the rates on the diagonal.
    """
    rates = np.array(rates, dtype=float)

    def f_func(state):
        return rates * state

    def jac_func(state):
        return np.diag(rates)

    return f_func, jac_func


# ---------------------------------------------------------------------------
# Property 14: Auto-reduction freeze correctness
# **Validates: Requirements 5.3, 5.4**
# ---------------------------------------------------------------------------


@given(data=random_auto_reduction_scenario(min_n=3, max_n=10))
@settings(deadline=None)
def test_property_14_auto_reduction_freeze_correctness(data):
    """
    For any mechanism state where species i has importance_i < threshold,
    the auto-reduced solver produces K1_i = 0, K2_i = 0, and state_new[i] == state[i].

    Uses a simple diagonal ODE system (dy/dt = rates * y) with a diagonal
    Jacobian for straightforward verification.

    **Validates: Requirements 5.3, 5.4**
    """
    N, state, rates, atol, rtol, threshold, dt = data

    # Build system functions
    f_func, jac_func = make_diagonal_system(rates)

    # Compute expected importance to determine which species are frozen
    F1 = f_func(state)
    expected_active = np.array([abs(F1[i]) / (atol[i] + rtol[i] * abs(state[i])) >= threshold for i in range(N)])

    # Need at least one frozen species for this test to be meaningful
    assume(not np.all(expected_active))
    # Need at least one active species so the linear solve is well-conditioned
    assume(np.any(expected_active))

    # Run auto-reduced step
    state_new, K1, K2, active = auto_reduced_ros2_step(state, f_func, jac_func, dt, atol, rtol, threshold)

    # Verify active mask matches our expectation
    np.testing.assert_array_equal(
        active,
        expected_active,
        err_msg="Active mask doesn't match expected importance classification",
    )

    # For all frozen species: K1=0, K2=0, state unchanged
    for i in range(N):
        if not active[i]:
            assert K1[i] == 0.0, f"Frozen species {i}: K1[{i}] = {K1[i]} != 0.0"
            assert K2[i] == 0.0, f"Frozen species {i}: K2[{i}] = {K2[i]} != 0.0"
            assert state_new[i] == state[i], f"Frozen species {i}: state changed from {state[i]} to {state_new[i]}"


# ---------------------------------------------------------------------------
# Property 15: Auto-reduction re-activation
# **Validates: Requirements 5.5, 5.6**
# ---------------------------------------------------------------------------


@given(data=random_reactivation_scenario(min_n=3, max_n=8))
@settings(deadline=None)
def test_property_15_auto_reduction_reactivation(data):
    """
    For any species i that was frozen on step 1 (importance < threshold) but
    has importance >= threshold on step 2, the solver correctly transitions
    that species from frozen to active:
    - Step 1: species i is frozen → K1=0, K2=0, state unchanged
    - Step 2: species i is active → participates in full solve (K != 0 generally)

    Uses a diagonal system where rates change between steps to simulate
    changing chemical activity.

    **Validates: Requirements 5.5, 5.6**
    """
    N, state, rates_step1, rates_step2, atol, rtol, threshold, dt, transition_idx = data

    # --- Step 1: species at transition_idx should be frozen ---
    f_func1, jac_func1 = make_diagonal_system(rates_step1)

    state_new1, K1_step1, K2_step1, active_step1 = auto_reduced_ros2_step(state, f_func1, jac_func1, dt, atol, rtol, threshold)

    # Verify transition species is frozen on step 1
    assert not active_step1[transition_idx], (
        f"Species {transition_idx} should be frozen on step 1 but is active. "
        f"Rate={rates_step1[transition_idx]}, state={state[transition_idx]}, "
        f"importance={abs(rates_step1[transition_idx] * state[transition_idx]) / (atol[transition_idx] + rtol[transition_idx] * abs(state[transition_idx]))}, "
        f"threshold={threshold}"
    )

    # Verify frozen properties on step 1
    assert K1_step1[transition_idx] == 0.0, f"Frozen species {transition_idx} on step 1: K1 = {K1_step1[transition_idx]} != 0.0"
    assert K2_step1[transition_idx] == 0.0, f"Frozen species {transition_idx} on step 1: K2 = {K2_step1[transition_idx]} != 0.0"
    assert state_new1[transition_idx] == state[transition_idx], (
        f"Frozen species {transition_idx} on step 1: state changed from " f"{state[transition_idx]} to {state_new1[transition_idx]}"
    )

    # --- Step 2: species at transition_idx should be active (with new rates) ---
    f_func2, jac_func2 = make_diagonal_system(rates_step2)

    state_new2, K1_step2, K2_step2, active_step2 = auto_reduced_ros2_step(state_new1, f_func2, jac_func2, dt, atol, rtol, threshold)

    # Verify transition species is active on step 2
    assert active_step2[transition_idx], (
        f"Species {transition_idx} should be active on step 2 but is frozen. "
        f"Rate={rates_step2[transition_idx]}, state={state_new1[transition_idx]}, "
        f"importance={abs(rates_step2[transition_idx] * state_new1[transition_idx]) / (atol[transition_idx] + rtol[transition_idx] * abs(state_new1[transition_idx]))}, "
        f"threshold={threshold}"
    )

    # When active, K1 and K2 should generally be non-zero
    # (for a diagonal system with non-zero rate and non-zero state, K1 != 0)
    # The rate for the transition species is large enough that F1 != 0
    # and since it's active, the solve should give non-zero K1
    F1_step2 = f_func2(state_new1)
    if abs(F1_step2[transition_idx]) > 1e-15:
        assert K1_step2[transition_idx] != 0.0, (
            f"Active species {transition_idx} on step 2: K1 = 0 despite non-zero F1 = {F1_step2[transition_idx]}. "
            f"Species should participate in the solve after re-activation."
        )
