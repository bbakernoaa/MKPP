"""
Integration test: auto-reduced ROS-2 solver vs full ROS-2 solver.

Validates that an auto-reduced Rosenbrock solver (which dynamically freezes
species with low importance) produces results within atol/rtol tolerances
compared to the full unreduced solver on the small_strato mechanism.

Uses the same small_strato mechanism as test_integration_ros2_vs_radau.py.

Validates: Requirements 5.7
"""

import os
import sys

import numpy as np
import pytest

# Add tests/python to path so we can import sibling test modules
sys.path.insert(0, os.path.dirname(__file__))

from test_integration_ros2_vs_radau import (
    NUM_SPECIES,
    ros2_adaptive_solve,
    small_strato_jacobian,
    small_strato_rhs_correct,
)

# ---------------------------------------------------------------------------
# Pure-Python ROS-2 adaptive solver WITH auto-reduction
# ---------------------------------------------------------------------------


def ros2_adaptive_solve_with_reduction(f_func, jac_func, y0, t_span, atol, rtol, importance_threshold):
    """
    Pure-Python ROS-2 adaptive Rosenbrock solver with auto-reduction.

    Same algorithm as ros2_adaptive_solve, but before each step:
    1. Evaluate species importance: importance_i = |F_i| / (atol_i + rtol_i * |C_i|)
    2. Classify species as active (importance >= threshold) or frozen (importance < threshold)
    3. For frozen species: zero their Jacobian rows/cols, set W diagonal to 1/(g*dt),
       and set K1=K2=0 (preserving their concentration unchanged)
    4. Re-activate species whose importance rises above threshold on next step.

    Parameters
    ----------
    f_func : callable
        RHS function f(t, y) -> dy/dt array
    jac_func : callable
        Jacobian function jac(t, y) -> J matrix
    y0 : ndarray
        Initial state vector
    t_span : tuple
        (t_start, t_end)
    atol : ndarray
        Per-species absolute tolerance
    rtol : ndarray
        Per-species relative tolerance
    importance_threshold : float
        Species with importance below this are frozen

    Returns
    -------
    y_final : ndarray
        State vector at t_end
    """
    # ROS-2 constants
    g = 1.0 + 1.0 / np.sqrt(2.0)  # gamma ~ 1.7071
    ros_A0 = 1.0 / g
    ros_C0 = -2.0 / g
    ros_M0 = 3.0 / (2.0 * g)
    ros_M1 = 1.0 / (2.0 * g)

    # Step control parameters
    safety = 0.9
    max_growth = 5.0
    min_shrink = 0.2

    N = len(y0)
    t_start, t_end = t_span
    dt_total = t_end - t_start

    state = y0.copy()
    t = 0.0
    dt = dt_total  # initial trial step

    max_iterations = 1_000_000  # safety limit

    for _ in range(max_iterations):
        if t >= dt_total:
            break

        dt = min(dt, dt_total - t)
        inv_g_dt = 1.0 / (g * dt)

        # Stage 1: evaluate RHS at current state
        F1 = f_func(t_start + t, state)

        # Classify species as active or frozen based on importance
        # importance_i = |dC_i/dt| / (atol_i + rtol_i * |C_i|)
        importance = np.zeros(N)
        for i in range(N):
            scale_i = atol[i] + rtol[i] * abs(state[i])
            importance[i] = abs(F1[i]) / scale_i

        active = importance >= importance_threshold
        frozen = ~active

        # Get Jacobian
        J = jac_func(t_start + t, state)

        # Zero Jacobian rows and columns for frozen species
        J_reduced = J.copy()
        for i in range(N):
            if frozen[i]:
                J_reduced[i, :] = 0.0
                J_reduced[:, i] = 0.0

        # Form iteration matrix W = (1/(g*dt))*I - J_reduced
        W = inv_g_dt * np.eye(N) - J_reduced

        # For frozen species, the row in W is just inv_g_dt on the diagonal
        # (since we zeroed J rows/cols). Set W diagonal to 1 for frozen species
        # so that solving W*K = F gives K=F for frozen, but we override K=0 below.
        for i in range(N):
            if frozen[i]:
                W[i, :] = 0.0
                W[i, i] = 1.0

        # Solve W * K1 = F1_modified
        # For frozen species, set RHS to 0 so K1=0
        F1_modified = F1.copy()
        for i in range(N):
            if frozen[i]:
                F1_modified[i] = 0.0

        K1 = np.linalg.solve(W, F1_modified)

        # Safety: ensure K1=0 for frozen species
        for i in range(N):
            if frozen[i]:
                K1[i] = 0.0

        # Intermediate state for Stage 2
        Ynew = state + ros_A0 * K1

        # Stage 2
        F2 = f_func(t_start + t, Ynew)

        # Form rhs2, zeroing frozen species
        rhs2 = F2 + (ros_C0 / dt) * K1
        for i in range(N):
            if frozen[i]:
                rhs2[i] = 0.0

        # Solve W * K2 = rhs2
        K2 = np.linalg.solve(W, rhs2)

        # Safety: ensure K2=0 for frozen species
        for i in range(N):
            if frozen[i]:
                K2[i] = 0.0

        # Error estimation (infinity norm) — only over active species
        err_norm = 0.0
        for i in range(N):
            if active[i]:
                sci = atol[i] + rtol[i] * abs(state[i])
                err_i = abs(K1[i] - K2[i]) / sci
                if err_i > err_norm:
                    err_norm = err_i

        # If all species are frozen, accept the step trivially
        if not np.any(active):
            t += dt
            continue

        # Step size control
        factor = safety * (1.0 / max(err_norm, 1e-10)) ** 0.5
        factor = max(min_shrink, min(factor, max_growth))

        if err_norm <= 1.0:
            # Accept step: update state (frozen species unchanged since K=0)
            state += ros_M0 * K1 + ros_M1 * K2
            t += dt
            dt *= factor
        else:
            # Reject step, shrink dt
            dt *= factor

    return state


# ---------------------------------------------------------------------------
# Test
# ---------------------------------------------------------------------------


@pytest.mark.slow
def test_auto_reduced_vs_full_solver_small_strato():
    """
    Integration test: auto-reduced ROS-2 solver vs full ROS-2 solver on the
    small_strato mechanism (7 species: O, O1D, O3, NO, NO2, M, O2) over 3600s.

    The auto-reduced solver dynamically freezes species with low importance
    (primarily M and O2, which are constant/fixed species with dC/dt=0).

    Validates that both solvers agree within atol=1e-3, rtol=1e-4.
    """
    # Initial conditions (molecules/cm^3, typical stratospheric ~25km values)
    y0 = np.array(
        [
            1.0e6,  # O: atomic oxygen
            1.0e4,  # O1D: excited oxygen
            5.0e12,  # O3: ozone
            1.0e9,  # NO
            5.0e9,  # NO2
            8.0e17,  # M: third body (fixed)
            4.0e17,  # O2: molecular oxygen (fixed)
        ]
    )

    t_end = 3600.0  # 1 hour integration

    # Per-species tolerances
    atol = np.full(NUM_SPECIES, 1e-3)
    rtol = np.full(NUM_SPECIES, 1e-4)

    # Importance threshold: species with importance below this are frozen.
    # M and O2 have dC/dt=0 so their importance is always 0, they will be frozen.
    importance_threshold = 0.01

    # --- Full ROS-2 solver (no reduction) ---
    y_full = ros2_adaptive_solve(
        small_strato_rhs_correct,
        small_strato_jacobian,
        y0,
        (0.0, t_end),
        atol=atol,
        rtol=rtol,
    )

    # --- Auto-reduced ROS-2 solver ---
    y_reduced = ros2_adaptive_solve_with_reduction(
        small_strato_rhs_correct,
        small_strato_jacobian,
        y0,
        (0.0, t_end),
        atol=atol,
        rtol=rtol,
        importance_threshold=importance_threshold,
    )

    # --- Comparison ---
    species_names = ["O", "O1D", "O3", "NO", "NO2", "M", "O2"]

    # Assert concentrations agree within atol=1e-3, rtol=1e-4
    np.testing.assert_allclose(
        y_reduced,
        y_full,
        atol=1e-3,
        rtol=1e-4,
        err_msg="Auto-reduced ROS-2 solver disagrees with full ROS-2 solver "
        "beyond atol=1e-3, rtol=1e-4 for small_strato mechanism",
    )

    # Also verify per-species with informative messages
    for i in range(NUM_SPECIES):
        tol_i = atol[i] + rtol[i] * abs(y_full[i])
        diff = abs(y_reduced[i] - y_full[i])
        assert diff < tol_i, (
            f"Species {species_names[i]} (idx {i}): auto-reduced result "
            f"{y_reduced[i]:.6e} differs from full solver {y_full[i]:.6e} "
            f"by {diff:.6e} (> tol = {tol_i:.6e})"
        )

    # Verify that M and O2 (fixed species) are exactly unchanged
    assert y_reduced[5] == y0[5], "M should be exactly unchanged (frozen species)"
    assert y_reduced[6] == y0[6], "O2 should be exactly unchanged (frozen species)"
