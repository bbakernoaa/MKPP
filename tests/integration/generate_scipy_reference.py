#!/usr/bin/env python3
"""Generate SciPy reference solution for the Chapman mechanism.

This script solves the Chapman mechanism ODE system using scipy.integrate.solve_ivp
with tight tolerances (Radau method, rtol=1e-12, atol=1e-12) to produce a reference
solution for validating the compiled MKPP C++ solver.

The Chapman mechanism (simplified atmospheric ozone chemistry):
  Species: O (index 0), O2 (index 1), O3 (index 2), M (index 3)

  Reactions:
    R1: O2 --hv--> 2 O           (photolysis, jvals[0])
    R2: O + O2 + M --> O3 + M    (Arrhenius, k = 6.0e-34)
    R3: O3 --hv--> O + O2        (photolysis, jvals[1])
    R4: O + O3 --> 2 O2           (Arrhenius, k = 8.0e-12)

  In the MKPP generated code, O2 (index 1) and M (index 3) are treated as
  constant background species (dO2/dt = 0, dM/dt = 0). Only O and O3 evolve.

Output:
  tests/integration/e2e_validation/data/chapman_reference.json

Usage:
  python tests/integration/generate_scipy_reference.py
"""

import json
from datetime import datetime, timezone
from pathlib import Path

import numpy as np
from scipy.integrate import solve_ivp


def chapman_ode(t, y, jvals):
    """Chapman mechanism ODE system matching MKPP generated code.

    Parameters
    ----------
    t : float
        Time (unused, autonomous system).
    y : array_like
        State vector [O, O2, O3, M] in molecules/cm3.
    jvals : array_like
        Photolysis rates [j_O2, j_O3] in s^-1.

    Returns
    -------
    dydt : ndarray
        Time derivatives for each species.
    """
    O, O2, O3, M = y
    j_O2 = jvals[0]
    j_O3 = jvals[1]

    # Rate constants (from mechanism YAML)
    k2 = 6.0e-34   # O + O2 + M -> O3 + M
    k4 = 8.0e-12   # O + O3 -> 2 O2

    # Production and loss rates matching generated compute_rates:
    # F_block(0) = -k2*M*O*O2 - k4*O*O3 + 2*O2*j_O2 + O3*j_O3
    # F_block(1) = 0.0  (O2 constant)
    # F_block(2) = k2*M*O*O2 - k4*O*O3 - O3*j_O3
    # F_block(3) = 0.0  (M constant)

    dO_dt = -k2 * M * O * O2 - k4 * O * O3 + 2.0 * O2 * j_O2 + O3 * j_O3
    dO2_dt = 0.0
    dO3_dt = k2 * M * O * O2 - k4 * O * O3 - O3 * j_O3
    dM_dt = 0.0

    return np.array([dO_dt, dO2_dt, dO3_dt, dM_dt])


def generate_reference():
    """Solve Chapman ODE and write reference JSON."""
    # Initial conditions matching the C++ e2e test
    initial_conditions = [1.0e10, 2.0e10, 3.0e10, 4.0e10]  # O, O2, O3, M

    # Photolysis rates matching the C++ e2e test
    jvals = [2.0e-5, 0.001]  # j_O2, j_O3

    # Time span: 1 hour (matching dt=3600 in C++ test)
    time_span = [0.0, 3600.0]

    # Solve with tight tolerances for reference accuracy
    scipy_config = {
        "method": "Radau",
        "rtol": 1e-12,
        "atol": 1e-12,
    }

    y0 = np.array(initial_conditions)

    result = solve_ivp(
        fun=lambda t, y: chapman_ode(t, y, jvals),
        t_span=time_span,
        y0=y0,
        method=scipy_config["method"],
        rtol=scipy_config["rtol"],
        atol=scipy_config["atol"],
        dense_output=True,
    )

    if not result.success:
        raise RuntimeError(f"SciPy solve_ivp failed: {result.message}")

    # Extract final concentrations
    expected_final = result.y[:, -1].tolist()

    # Build reference JSON
    reference = {
        "mechanism": "chapman",
        "solver": "ros3",
        "species": ["O", "O2", "O3", "M"],
        "initial_conditions": initial_conditions,
        "jvals": jvals,
        "time_span": time_span,
        "scipy_config": scipy_config,
        "expected_final": expected_final,
        "generated_by": "tests/integration/generate_scipy_reference.py",
        "timestamp": datetime.now(timezone.utc).isoformat(),
    }

    # Write to output location
    script_dir = Path(__file__).parent
    output_dir = script_dir / "e2e_validation" / "data"
    output_dir.mkdir(parents=True, exist_ok=True)
    output_path = output_dir / "chapman_reference.json"

    with open(output_path, "w") as f:
        json.dump(reference, f, indent=4)

    print(f"Reference solution written to: {output_path}")
    print(f"Species: {reference['species']}")
    print(f"Initial: {reference['initial_conditions']}")
    print(f"Final:   {reference['expected_final']}")
    print(f"Time span: {reference['time_span']} seconds")
    print(f"jvals: {reference['jvals']}")
    print(f"SciPy steps: {result.t.size}")

    return reference


if __name__ == "__main__":
    generate_reference()
