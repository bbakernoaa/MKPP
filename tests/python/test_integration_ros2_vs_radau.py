"""
Integration test: ROS-3 adaptive solver vs scipy Radau reference.

Tests the ALGORITHM correctness of the ROS-3 adaptive Rosenbrock solver
by implementing a pure-Python version matching the generated C++ logic,
and comparing against scipy's Radau solver on the small_strato mechanism.

Uses the actual small_strato.yaml mechanism (7 species, 10 reactions).

ROS-3 is a 3-stage, 3rd order, L-stable Rosenbrock method from KPP
(Sandu & Sander 2006).

Validates: Requirements 2.7
"""

import numpy as np
import pytest
from scipy.integrate import solve_ivp

# ---------------------------------------------------------------------------
# small_strato mechanism: 7 species, 10 reactions
# Species order from YAML: O, O1D, O3, NO, NO2, M, O2
# M and O2 are fixed species (concentration held constant)
# ---------------------------------------------------------------------------

# Species indices (matching YAML order)
IDX_O = 0
IDX_O1D = 1
IDX_O3 = 2
IDX_NO = 3
IDX_NO2 = 4
IDX_M = 5
IDX_O2 = 6

NUM_SPECIES = 7

# SUN parameter for photolysis (daytime, representative value)
SUN = 1.0

# Rate constants from small_strato.yaml (evaluated with SUN=1.0):
K1 = 2.643e-10 * SUN**3  # R1: photolysis of O2
K2 = 8.018e-17  # R2: O + O2 -> O3
K3 = 6.120e-04 * SUN  # R3: photolysis of O3
K4 = 1.576e-15  # R4: O + O3 -> 2O2
K5 = 1.070e-03 * SUN**2  # R5: photolysis of O3 (O1D channel)
K6 = 7.110e-11  # R6: O1D + M -> O + M
K7 = 1.200e-10  # R7: O1D + O3 -> 2O2
K8 = 6.062e-15  # R8: NO + O3 -> NO2 + O2
K9 = 1.069e-11  # R9: NO2 + O -> NO + O2
K10 = 1.289e-02 * SUN  # R10: photolysis of NO2


def small_strato_rhs(t, y):
    """
    Rate equations for the small_strato mechanism (7 species, 10 reactions).
    """
    o, o1d, o3, no, no2, m, o2 = y

    o = max(o, 0.0)
    o1d = max(o1d, 0.0)
    o3 = max(o3, 0.0)
    no = max(no, 0.0)
    no2 = max(no2, 0.0)
    m = max(m, 0.0)
    o2 = max(o2, 0.0)

    r1 = K1 * o2
    r2 = K2 * o * o2
    r3 = K3 * o3
    r4 = K4 * o * o3
    r5 = K5 * o3
    r6 = K6 * o1d * m
    r7 = K7 * o1d * o3
    r8 = K8 * no * o3
    r9 = K9 * no2 * o
    r10 = K10 * no2

    dydt = np.zeros(NUM_SPECIES)

    # dO/dt: produced by R1(*2), R3, R6, R10; consumed by R2, R4, R9
    dydt[IDX_O] = 2.0 * r1 - r2 + r3 - r4 + r6 - r9 + r10

    # dO1D/dt: produced by R5; consumed by R6, R7
    dydt[IDX_O1D] = r5 - r6 - r7

    # dO3/dt: produced by R2; consumed by R3, R4, R5, R7, R8
    dydt[IDX_O3] = r2 - r3 - r4 - r5 - r7 - r8

    # dNO/dt: produced by R9, R10; consumed by R8
    dydt[IDX_NO] = -r8 + r9 + r10

    # dNO2/dt: produced by R8; consumed by R9, R10
    dydt[IDX_NO2] = r8 - r9 - r10

    # dM/dt = 0 (fixed)
    dydt[IDX_M] = 0.0

    # dO2/dt = 0 (fixed)
    dydt[IDX_O2] = 0.0

    return dydt


def small_strato_jacobian(t, y):
    """
    Analytical Jacobian for the small_strato mechanism.
    """
    o, o1d, o3, no, no2, m, o2 = y
    o = max(o, 0.0)
    o1d = max(o1d, 0.0)
    o3 = max(o3, 0.0)
    no = max(no, 0.0)
    no2 = max(no2, 0.0)
    m = max(m, 0.0)
    o2 = max(o2, 0.0)

    J = np.zeros((NUM_SPECIES, NUM_SPECIES))

    # dO/dt = 2*K1*o2 - K2*o*o2 + K3*o3 - K4*o*o3 + K6*o1d*m - K9*no2*o + K10*no2
    J[IDX_O, IDX_O] = -K2 * o2 - K4 * o3 - K9 * no2
    J[IDX_O, IDX_O1D] = K6 * m
    J[IDX_O, IDX_O3] = K3 - K4 * o
    J[IDX_O, IDX_NO2] = -K9 * o + K10
    J[IDX_O, IDX_M] = K6 * o1d
    J[IDX_O, IDX_O2] = 2.0 * K1 - K2 * o

    # dO1D/dt = K5*o3 - K6*o1d*m - K7*o1d*o3
    J[IDX_O1D, IDX_O1D] = -K6 * m - K7 * o3
    J[IDX_O1D, IDX_O3] = K5 - K7 * o1d
    J[IDX_O1D, IDX_M] = -K6 * o1d

    # dO3/dt = K2*o*o2 - K3*o3 - K4*o*o3 - K5*o3 - K7*o1d*o3 - K8*no*o3
    J[IDX_O3, IDX_O] = K2 * o2 - K4 * o3
    J[IDX_O3, IDX_O1D] = -K7 * o3
    J[IDX_O3, IDX_O3] = -K3 - K4 * o - K5 - K7 * o1d - K8 * no
    J[IDX_O3, IDX_NO] = -K8 * o3
    J[IDX_O3, IDX_O2] = K2 * o

    # dNO/dt = -K8*no*o3 + K9*no2*o + K10*no2
    J[IDX_NO, IDX_O] = K9 * no2
    J[IDX_NO, IDX_O3] = -K8 * no
    J[IDX_NO, IDX_NO] = -K8 * o3
    J[IDX_NO, IDX_NO2] = K9 * o + K10

    # dNO2/dt = K8*no*o3 - K9*no2*o - K10*no2
    J[IDX_NO2, IDX_O] = -K9 * no2
    J[IDX_NO2, IDX_O3] = K8 * no
    J[IDX_NO2, IDX_NO] = K8 * o3
    J[IDX_NO2, IDX_NO2] = -K9 * o - K10

    return J


# Alias for backward compatibility (other tests import this name)
small_strato_rhs_correct = small_strato_rhs


# ---------------------------------------------------------------------------
# Pure-Python ROS-2 adaptive solver (kept for auto-reduction test compatibility)
# ---------------------------------------------------------------------------


def ros2_adaptive_solve(f_func, jac_func, y0, t_span, atol, rtol):
    """
    Pure-Python implementation of the ROS-2 adaptive Rosenbrock solver.
    Kept for backward compatibility with auto-reduction tests.
    """
    g = 1.0 + 1.0 / np.sqrt(2.0)
    ros_A0 = 1.0 / g
    ros_C0 = -2.0 / g
    ros_M0 = 3.0 / (2.0 * g)
    ros_M1 = 1.0 / (2.0 * g)

    safety = 0.9
    max_growth = 6.0
    min_shrink = 0.2

    N = len(y0)
    t_start, t_end = t_span
    dt_total = t_end - t_start

    state = y0.copy()
    t = 0.0
    dt = dt_total

    max_iterations = 1_000_000

    for _ in range(max_iterations):
        if t >= dt_total:
            break

        dt = min(dt, dt_total - t)
        inv_g_dt = 1.0 / (g * dt)

        F1 = f_func(t_start + t, state)
        J = jac_func(t_start + t, state)

        W = inv_g_dt * np.eye(N) - J
        K1 = np.linalg.solve(W, F1)

        Ynew = state + ros_A0 * K1
        F2 = f_func(t_start + t, Ynew)
        rhs2 = F2 + (ros_C0 / dt) * K1
        K2 = np.linalg.solve(W, rhs2)

        err_norm_sq = 0.0
        for i in range(N):
            Ynew_i = state[i] + ros_M0 * K1[i] + ros_M1 * K2[i]
            ymax = max(abs(state[i]), abs(Ynew_i))
            sci = atol[i] + rtol[i] * ymax
            yerr_i = (1.0 / (2.0 * g)) * K1[i] + (1.0 / (2.0 * g)) * K2[i]
            err_norm_sq += (yerr_i / sci) ** 2
        err_norm = max(np.sqrt(err_norm_sq / N), 1e-10)

        factor = safety / err_norm**0.5
        factor = max(min_shrink, min(factor, max_growth))

        if err_norm <= 1.0:
            state += ros_M0 * K1 + ros_M1 * K2
            t += dt
            dt *= factor
        else:
            dt *= factor

    return state


# ---------------------------------------------------------------------------
# Pure-Python ROS-3 adaptive solver (matching generated C++ logic)
# ---------------------------------------------------------------------------


def ros3_adaptive_solve(f_func, jac_func, y0, t_span, atol, rtol):
    """
    Pure-Python implementation of the ROS-3 adaptive Rosenbrock solver.

    Matches the algorithm emitted by codegen.py (Sandu & Sander 2006, KPP Ros3):
    - 3 stages, 3rd order, L-stable
    - gamma = 0.43586652150845899941601945119356
    - Adaptive step control: safety=0.9, max_growth=6.0, min_shrink=0.2
    - Error exponent: 1/3 (3rd order)
    """
    # ROS-3 constants (from KPP Ros3 subroutine)
    gamma = 0.43586652150845899941601945119356

    ros_A21 = 1.0

    ros_C21 = -1.0156171083877702091975600115545
    ros_C31 = 4.0759956452537699824805835358067
    ros_C32 = 9.2076794298330791242156818474003

    ros_M1 = 1.0
    ros_M2 = 6.1697947043828245592553615689730
    ros_M3 = -0.42772256543218573326238373806514

    ros_E1 = 0.5
    ros_E2 = -2.9079558716805469821718236208017
    ros_E3 = 0.22354069897811569627360909276199

    # Step control parameters
    safety = 0.9
    max_growth = 6.0
    min_shrink = 0.2

    N = len(y0)
    t_start, t_end = t_span
    dt_total = t_end - t_start

    state = y0.copy()
    t = 0.0
    dt = dt_total  # initial trial step

    max_iterations = 1_000_000

    for _ in range(max_iterations):
        if t >= dt_total:
            break

        dt = min(dt, dt_total - t)
        inv_g_dt = 1.0 / (gamma * dt)

        # Stage 1
        F1 = f_func(t_start + t, state)
        J = jac_func(t_start + t, state)

        # Form iteration matrix W = (1/(gamma*dt))*I - J
        W = inv_g_dt * np.eye(N) - J

        # Solve W * K1 = F1
        K1 = np.linalg.solve(W, F1)

        # Stage 2: Y2 = Y + A21*K1
        Y2 = state + ros_A21 * K1
        F2 = f_func(t_start + t, Y2)

        # RHS2 = F2 + C21/dt * K1
        rhs2 = F2 + (ros_C21 / dt) * K1
        K2 = np.linalg.solve(W, rhs2)

        # Stage 3: Y3 = Y + A31*K1 + A32*K2 = Y + K1 (since A32=0)
        # NewF(3) = false: reuse F2
        F3 = F2  # reuse

        # RHS3 = F3 + C31/dt * K1 + C32/dt * K2
        rhs3 = F3 + (ros_C31 / dt) * K1 + (ros_C32 / dt) * K2
        K3 = np.linalg.solve(W, rhs3)

        # New solution
        Ynew = state + ros_M1 * K1 + ros_M2 * K2 + ros_M3 * K3

        # Error estimation (L2 norm)
        err_norm_sq = 0.0
        for i in range(N):
            ymax = max(abs(state[i]), abs(Ynew[i]))
            sci = atol[i] + rtol[i] * ymax
            yerr_i = ros_E1 * K1[i] + ros_E2 * K2[i] + ros_E3 * K3[i]
            err_norm_sq += (yerr_i / sci) ** 2
        err_norm = max(np.sqrt(err_norm_sq / N), 1e-10)

        # Step size control (3rd order: exponent = 1/3)
        factor = safety / err_norm ** (1.0 / 3.0)
        factor = max(min_shrink, min(factor, max_growth))

        if err_norm <= 1.0:
            state = Ynew.copy()
            t += dt
            dt *= factor
        else:
            dt *= factor

    return state


# ---------------------------------------------------------------------------
# Test
# ---------------------------------------------------------------------------


@pytest.mark.slow
def test_ros3_adaptive_vs_radau_small_strato():
    """
    Integration test: ROS-3 adaptive solver vs scipy Radau on the small_strato
    mechanism (7 species: O, O1D, O3, NO, NO2, M, O2) over 3600 seconds.

    This validates the algorithm correctness of the ROS-3 solver by comparing
    its output against scipy's Radau solver (a high-order implicit method)
    on realistic atmospheric chemistry timescales.

    ROS-3 is 3rd order (vs ROS-2's 2nd order) so we expect better accuracy
    with fewer steps.
    """
    # Initial conditions (molecules/cm^3, typical stratospheric ~25km values)
    y0 = np.array(
        [
            1.0e6,  # O: atomic oxygen, short-lived radical
            1.0e4,  # O1D: excited oxygen, very short-lived
            5.0e12,  # O3: ozone, ~5 ppmv at 25 km
            1.0e9,  # NO: ~1 ppbv
            5.0e9,  # NO2: ~5 ppbv
            8.0e17,  # M: third body (air density at ~25 km)
            4.0e17,  # O2: molecular oxygen at ~25 km
        ]
    )

    t_end = 3600.0  # 1 hour integration

    # Per-species tolerances
    atol = np.full(NUM_SPECIES, 1e-3)
    rtol = np.full(NUM_SPECIES, 1e-4)

    # --- Reference solution: scipy Radau (high accuracy) ---
    sol_ref = solve_ivp(
        small_strato_rhs,
        (0.0, t_end),
        y0,
        method="Radau",
        jac=small_strato_jacobian,
        rtol=1e-10,
        atol=1e-12,
        dense_output=False,
    )
    assert sol_ref.success, f"Radau solver failed: {sol_ref.message}"
    y_ref = sol_ref.y[:, -1]

    # --- ROS-3 adaptive solver ---
    y_ros3 = ros3_adaptive_solve(
        small_strato_rhs,
        small_strato_jacobian,
        y0,
        (0.0, t_end),
        atol=atol,
        rtol=rtol,
    )

    # --- Comparison ---
    # ROS-3 is 3rd order, so we expect tighter agreement than ROS-2.
    # Allow factor of 20 slack (less than the 50x needed for 2nd order ROS-2).
    species_names = ["O", "O1D", "O3", "NO", "NO2", "M", "O2"]
    for i in range(NUM_SPECIES):
        tol_i = atol[i] + rtol[i] * abs(y_ref[i])
        diff = abs(y_ros3[i] - y_ref[i])
        assert diff < 20.0 * tol_i, (
            f"Species {species_names[i]} (idx {i}): ROS-3 result {y_ros3[i]:.6e} "
            f"differs from Radau reference {y_ref[i]:.6e} by {diff:.6e} "
            f"(> 20 * tol = {20.0 * tol_i:.6e})"
        )

    # Also verify with numpy's assert_allclose at the specified tolerances
    np.testing.assert_allclose(
        y_ros3,
        y_ref,
        atol=1e-3,
        rtol=1e-4,
        err_msg="ROS-3 adaptive solver disagrees with Radau reference " "beyond atol=1e-3, rtol=1e-4 for small_strato mechanism",
    )
