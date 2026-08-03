import pytest
import numpy as np
import scipy.integrate as integrate
from mkpp.model import (
    MechanismDefinition, SpeciesDefinition, ReactionDefinition, PhaseMode, AerosolRepresentation
)
from mkpp.lowering import prepare_unified_jacobian, compute_symbolic_lu_decomposition


def reference_rosenbrock2_step(y0, dt, f_func, jac_func):
    """
    Reference dense Rosenbrock-2 integrator step for verification.
    gamma = 1 + 1/sqrt(2)
    """
    g = 1.0 + 1.0 / np.sqrt(2.0)
    ros_A0 = 1.0 / g
    ros_C0 = -2.0 / g
    ros_M0 = 3.0 / (2.0 * g)
    ros_M1 = 1.0 / (2.0 * g)

    N = len(y0)
    F1 = f_func(y0)
    J = jac_func(y0)

    W = (1.0 / (g * dt)) * np.eye(N) - J

    # K1 solve: W * K1 = F1
    K1 = np.linalg.solve(W, F1)

    Ynew = y0 + ros_A0 * K1
    F2 = f_func(Ynew)

    # K2 solve: W * K2 = F2 + (ros_C0 / dt) * K1
    rhs2 = F2 + (ros_C0 / dt) * K1
    K2 = np.linalg.solve(W, rhs2)

    y_next = y0 + ros_M0 * K1 + ros_M1 * K2
    return y_next


def test_reference_ros2_fixture():
    """Verify reference Rosenbrock-2 step function against scipy Radau for stiff decay with substepping."""
    def f_func(y):
        return np.array([-100.0 * y[0], 100.0 * y[0] - 1.0 * y[1]])

    def jac_func(y):
        return np.array([[-100.0, 0.0], [100.0, -1.0]])

    y0 = np.array([1.0, 0.0])
    dt = 0.0001
    num_steps = 100

    y_ros2 = y0.copy()
    for _ in range(num_steps):
        y_ros2 = reference_rosenbrock2_step(y_ros2, dt, f_func, jac_func)

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

    np.testing.assert_allclose(y_ros2, y_ref, rtol=1e-3, atol=1e-4)

