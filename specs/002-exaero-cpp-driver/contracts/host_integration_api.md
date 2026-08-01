# Host Integration API Contract

## C-Compatible Entrypoints

The Exaero C++ utility exposes the following `extern "C"` interfaces for integration into Fortran (`ISO_C_BINDING`) and other native host models.

```cpp
#include <stdint.h>

extern "C" {

/**
 * @brief Initializes the Exaero utility, validating the registry and allocating persistent scratch views.
 * @param mechanism_name Null-terminated string matching an AOT-compiled mechanism (e.g. "ChapmanCycle").
 * @param total_cells Total size of the horizontal/vertical execution grid.
 * @return 0 on success, non-zero on fatal failure (e.g., mechanism not found).
 */
int exaero_init(const char* mechanism_name, int32_t total_cells);

/**
 * @brief Executes the active chemistry solver using Kokkos hierarchical parallelism.
 * @param conc_ptr Device pointer to the contiguous LayoutLeft concentration array.
 * @param met_ptr Device pointer to the contiguous LayoutLeft meteorology array (including SZA).
 * @param dt Physics timestep in seconds.
 * @return 0 on success, non-zero on numerical/execution failure.
 */
int exaero_solve(double* conc_ptr, double* met_ptr, double dt);

/**
 * @brief Cleans up persistent memory allocated during exaero_init.
 */
void exaero_finalize();

}
```
