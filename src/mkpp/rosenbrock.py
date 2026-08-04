"""Rosenbrock solver coefficient tableaux and accessor utilities.

This module defines the immutable coefficient tableaux for all supported
Rosenbrock solvers (ROS-2, ROS-3, ROS-4, RODAS-3, RODAS-4) and provides
index-based accessors for the lower-triangular A and C coefficient matrices.
"""

from dataclasses import dataclass


@dataclass(frozen=True)
class RosenbrockTableau:
    """Immutable coefficient tableau for a Rosenbrock solver."""

    name: str
    stages: int
    A: list[float]  # Strictly lower-triangular, row-wise: A(2,1), A(3,1), A(3,2), ...
    C: list[float]  # Same storage as A
    M: list[float]  # Solution update weights, length = stages
    E: list[float]  # Error estimate weights, length = stages
    Alpha: list[float]  # Stage time offsets, length = stages
    Gamma: list[float]  # Gamma sums, length = stages
    NewF: list[bool]  # Whether stage i needs a fresh F evaluation
    ELO: float  # Estimator of local order (main + embedded + 1)


SOLVER_COEFFICIENTS: dict[str, RosenbrockTableau] = {
    "ros2": RosenbrockTableau(
        name="ROS-2",
        stages=2,
        A=[1.7071067811865475244],  # 1/g where g = 1 + 1/sqrt(2)
        C=[-1.1715728752538099024],  # -2/g
        M=[0.87867965644035742774, 0.29289321881345247560],  # 3/(2g), 1/(2g)
        E=[0.29289321881345247560, 0.29289321881345247560],  # 1/(2g), 1/(2g)
        Alpha=[0.0, 1.0],
        Gamma=[1.7071067811865475244, -1.7071067811865475244],  # g, -g
        NewF=[True, True],
        ELO=2.0,
    ),
    "ros3": RosenbrockTableau(
        name="ROS-3",
        stages=3,
        A=[1.0, 1.0, 0.0],
        C=[-1.0156171083877702092, 4.0759956452537699825, 9.2076794298330791242],
        M=[1.0, 6.1697947043828245593, -0.42772256543218573326],
        E=[0.5, -2.9079558716805469822, 0.22354069897811569627],
        Alpha=[0.0, 0.43586652150845899942, 0.43586652150845899942],
        Gamma=[0.43586652150845899942, 0.24291996454816804367, 2.1851380027664058512],
        NewF=[True, True, False],
        ELO=3.0,
    ),
    "ros4": RosenbrockTableau(
        name="ROS-4",
        stages=4,
        A=[2.0, 1.867943637803922, 0.2344449711399156, 1.867943637803922, 0.2344449711399156, 0.0],
        C=[
            -7.137615036412310,
            2.580708087951457,
            0.6515950076447975,
            -2.137148994382534,
            -0.3214669691237626,
            -0.6949742501781779,
        ],
        M=[2.255570073418735, 0.2870493262186792, 0.4353179431840180, 1.093502252409163],
        E=[-0.2815431932141155, -0.07276199124938920, -0.1082196201495311, -1.093502252409163],
        Alpha=[0.0, 1.145640000000000, 0.6552168638155900, 0.6552168638155900],
        Gamma=[0.5728200000000000, -1.769193891319233, 0.7592633437920482, -0.1049021087100450],
        NewF=[True, True, True, False],
        ELO=4.0,
    ),
    "rodas3": RosenbrockTableau(
        name="RODAS-3",
        stages=4,
        A=[0.0, 2.0, 0.0, 2.0, 0.0, 1.0],
        C=[4.0, 1.0, -1.0, 1.0, -1.0, -8.0 / 3.0],
        M=[2.0, 0.0, 1.0, 1.0],
        E=[0.0, 0.0, 0.0, 1.0],
        Alpha=[0.0, 0.0, 1.0, 1.0],
        Gamma=[0.5, 1.5, 0.0, 0.0],
        NewF=[True, False, True, True],
        ELO=3.0,
    ),
    "rodas4": RosenbrockTableau(
        name="RODAS-4",
        stages=6,
        A=[
            1.544000000000000,
            0.9466785280815826,
            0.2557011698983284,
            3.314825187068521,
            2.896124015972201,
            0.9986419139977817,
            1.221224509226641,
            6.019134481288629,
            12.53708332932087,
            -0.6878860361058950,
            1.221224509226641,
            6.019134481288629,
            12.53708332932087,
            -0.6878860361058950,
            1.0,
        ],
        C=[
            -5.668800000000000,
            -2.430093356833875,
            -0.2063599157091915,
            -0.1073529058151375,
            -9.594562251023355,
            -20.47028614809616,
            7.496443313967647,
            -10.24680431464352,
            -33.99990352819905,
            11.70890893206160,
            8.083246795921522,
            -7.981132988064893,
            -31.52159432874371,
            16.31930543123136,
            -6.058818238834054,
        ],
        M=[1.221224509226641, 6.019134481288629, 12.53708332932087, -0.6878860361058950, 1.0, 1.0],
        E=[0.0, 0.0, 0.0, 0.0, 0.0, 1.0],
        Alpha=[0.0, 0.386, 0.210, 0.630, 1.0, 1.0],
        Gamma=[
            0.2500000000000000,
            -0.1043000000000000,
            0.1035000000000000,
            -0.03620000000000023,
            0.0,
            0.0,
        ],
        NewF=[True, True, True, True, True, True],
        ELO=4.0,
    ),
}


def get_A(tableau: RosenbrockTableau, i: int, j: int) -> float:
    """Get A(i,j) from row-wise lower-triangular storage. i,j are 1-indexed; i > j."""
    return tableau.A[(i - 1) * (i - 2) // 2 + j - 1]


def get_C(tableau: RosenbrockTableau, i: int, j: int) -> float:
    """Get C(i,j) from row-wise lower-triangular storage. i,j are 1-indexed; i > j."""
    return tableau.C[(i - 1) * (i - 2) // 2 + j - 1]


# Module-level assertions verifying array length invariants for each tableau
for _solver_name, _tableau in SOLVER_COEFFICIENTS.items():
    _s = _tableau.stages
    _expected_tri = _s * (_s - 1) // 2
    assert (
        len(_tableau.A) == _expected_tri
    ), f"{_solver_name}: len(A)={len(_tableau.A)} != stages*(stages-1)//2={_expected_tri}"
    assert (
        len(_tableau.C) == _expected_tri
    ), f"{_solver_name}: len(C)={len(_tableau.C)} != stages*(stages-1)//2={_expected_tri}"
    assert len(_tableau.M) == _s, f"{_solver_name}: len(M)={len(_tableau.M)} != stages={_s}"
    assert len(_tableau.E) == _s, f"{_solver_name}: len(E)={len(_tableau.E)} != stages={_s}"
    assert (
        len(_tableau.Alpha) == _s
    ), f"{_solver_name}: len(Alpha)={len(_tableau.Alpha)} != stages={_s}"
    assert (
        len(_tableau.Gamma) == _s
    ), f"{_solver_name}: len(Gamma)={len(_tableau.Gamma)} != stages={_s}"
    assert (
        len(_tableau.NewF) == _s
    ), f"{_solver_name}: len(NewF)={len(_tableau.NewF)} != stages={_s}"
# Clean up loop variables from module namespace
del _solver_name, _tableau, _s, _expected_tri
