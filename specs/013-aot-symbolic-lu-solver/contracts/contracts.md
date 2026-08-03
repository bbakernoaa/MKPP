# Interfaces & Contracts: AOT Symbolic LU Kokkos ODE Solver

## 1. C++ Generated Header API Contract

Every generated chemical mechanism header (e.g., `saprc99.hpp`, `chapman.hpp`) MUST adhere to the following templated Kokkos functor interface.

```cpp
#pragma once
#include <Kokkos_Core.hpp>

namespace mkpp {

template <typename DeviceType>
struct SolverKernels {
    // ------------------------------------------------------------------------
    // Rate Evaluation: Accepts generic state and rate views/subviews.
    // Zero raw double* pointers permitted.
    // ------------------------------------------------------------------------
    template <class StateView, class RateView>
    KOKKOS_INLINE_FUNCTION void compute_rates(const StateView& state, RateView& rates) const {
        // Pure scalar assignments for F_0, F_1, ... F_{N-1}
    }

    // ------------------------------------------------------------------------
    // Analytical Non-Zero Jacobian Evaluation
    // ------------------------------------------------------------------------
    template <class StateView, class JacView>
    KOKKOS_INLINE_FUNCTION void compute_jacobian(const StateView& state, JacView& J) const {
        // Pure scalar assignments for non-zero J_{i,j}
    }

    // ------------------------------------------------------------------------
    // ODE Integrator (Rosenbrock-2): Fully Unrolled, Array-less, Zero Loops
    // ------------------------------------------------------------------------
    template <class StateView>
    KOKKOS_INLINE_FUNCTION void integrate(double dt, StateView& state) const {
        const int NUM_SPECIES = /* N */;
        const double g = 1.70710678118654752440; // 1 + 1/sqrt(2)
        const double ros_A0 = 1.0 / g;
        const double ros_C0 = -2.0 / g;
        const double ros_M0 = 3.0 / (2.0 * g);
        const double ros_M1 = 1.0 / (2.0 * g);
        const double inv_g_dt = 1.0 / (g * dt);

        // 1. Evaluate Stage 1 Rates (F1) into scalar variables
        // double F1_0 = ...; double F1_1 = ...;

        // 2. Evaluate Non-Zero Jacobian & Iteration Matrix W = (1/(g*dt))*I - J
        // double J_0_0 = ...; double W_0_0 = inv_g_dt - J_0_0;

        // 3. Symbolic Sparse Doolittle LU Factorization (Zero Loops)
        // double L_1_0 = W_1_0 / W_0_0;
        // double U_1_1 = W_1_1 - L_1_0 * W_0_1;

        // 4. Forward & Backward Substitution for Stage K1 (Zero Loops)
        // double y_0 = F1_0;
        // double K1_1 = (y_1 - L_1_0 * y_0) / U_1_1;

        // 5. Fused Intermediate State Update Ynew
        // double Ynew_0 = state(0) + ros_A0 * K1_0;

        // 6. Stage 2 Rates F2 & Substitution for Stage K2
        // double F2_0 = ...;
        // double rhs2_0 = F2_0 + (ros_C0 / dt) * K1_0;
        // double K2_0 = ...;

        // 7. Final Fused State Update
        // state(0) += ros_M0 * K1_0 + ros_M1 * K2_0;
    }
};

} // namespace mkpp
```

---

## 2. Python Generator API Contract

The Python generator function in `src/mkpp/codegen.py` MUST provide the following interface signature:

```python
def generate_headers(
    mech: MechanismDefinition,
    out_dir: str = "src/solvers",
    suffix: str = ""
) -> Dict[str, str]:
    """
    Emits C++ Kokkos ODE solver headers with AOT symbolic sparse LU decomposition,
    register-mapped scalar unrolling, and zero thread-local arrays.

    Args:
        mech: Loaded chemical mechanism definition containing species and reactions.
        out_dir: Output directory path for header emission.
        suffix: Optional filename suffix.

    Returns:
        Dict[str, str]: Map of artifact names to emitted absolute file paths.
    """
```
