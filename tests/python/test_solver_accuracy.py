import pytest
import numpy as np
import scipy.integrate as integrate
from mkpp.model import (
    MechanismDefinition, SpeciesDefinition, ReactionDefinition, PhaseMode, AerosolRepresentation
)
from mkpp.lowering import prepare_unified_jacobian, compute_symbolic_lu_decomposition


def reference_rosenbrock3_step(y0, dt, f_func, jac_func):
    """
    Reference dense Rosenbrock-3 integrator step for verification.
    ROS-3: 3-stage, 3rd order, L-stable (Sandu & Sander 2006, KPP).
    gamma = 0.43586652150845899941601945119356
    """
    gamma = 0.43586652150845899941601945119356

    ros_A21 = 1.0
    ros_C21 = -1.0156171083877702091975600115545
    ros_C31 = 4.0759956452537699824805835358067
    ros_C32 = 9.2076794298330791242156818474003
    ros_M1 = 1.0
    ros_M2 = 6.1697947043828245592553615689730
    ros_M3 = -0.42772256543218573326238373806514

    N = len(y0)
    F1 = f_func(y0)
    J = jac_func(y0)

    W = (1.0 / (gamma * dt)) * np.eye(N) - J

    # Stage 1: W * K1 = F1
    K1 = np.linalg.solve(W, F1)

    # Stage 2: Y2 = Y + A21*K1, evaluate F2
    Y2 = y0 + ros_A21 * K1
    F2 = f_func(Y2)
    rhs2 = F2 + (ros_C21 / dt) * K1
    K2 = np.linalg.solve(W, rhs2)

    # Stage 3: NewF=false, reuse F2
    rhs3 = F2 + (ros_C31 / dt) * K1 + (ros_C32 / dt) * K2
    K3 = np.linalg.solve(W, rhs3)

    # Update
    y_next = y0 + ros_M1 * K1 + ros_M2 * K2 + ros_M3 * K3
    return y_next


def test_reference_ros3_fixture():
    """Verify reference Rosenbrock-3 step function against scipy Radau for stiff decay with substepping."""
    def f_func(y):
        return np.array([-100.0 * y[0], 100.0 * y[0] - 1.0 * y[1]])

    def jac_func(y):
        return np.array([[-100.0, 0.0], [100.0, -1.0]])

    y0 = np.array([1.0, 0.0])
    dt = 0.001
    num_steps = 10

    y_ros3 = y0.copy()
    for _ in range(num_steps):
        y_ros3 = reference_rosenbrock3_step(y_ros3, dt, f_func, jac_func)

    t_end = dt * num_steps
    sol = integrate.solve_ivp(
        lambda t, y: f_func(y),
        (0, t_end),
        y0,
        method='Radau',
        rtol=1e-10,
        atol=1e-12
    )
    y_ref = sol.y[:, -1]

    # ROS-3 is 3rd order, so with dt=0.001 on a stiff system it should
    # agree well with the reference after 10 steps
    np.testing.assert_allclose(y_ros3, y_ref, rtol=1e-3, atol=1e-4)
