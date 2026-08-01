# Data Model: Exaero C++ Utility

## Key Entities

### ExaeroContext (Persistent State)
Holds the persistent runtime configuration and scratch buffers to eliminate dynamic memory allocations during physics timesteps.
*   **Properties**: 
    *   `active_mechanism`: Identifier of the loaded solver target.
    *   `sza_sorted_indices`: Persistent `Kokkos::View<int*>` used to reorder execution based on SZA.
    *   `total_grid_cells`: The size of the integration domain.

### UnmanagedDeviceState (Zero-Copy Bridge)
The structure of arrays mapping directly to the Host Fortran pointers.
*   **Properties**:
    *   `concentrations`: `Kokkos::View<double****, Kokkos::LayoutLeft, Kokkos::MemoryUnmanaged>`
    *   `meteorology`: `Kokkos::View<double****, Kokkos::LayoutLeft, Kokkos::MemoryUnmanaged>`

## State Transitions
1.  **Utility Initialization**: Host calls `exaero_init(mechanism_name, n_cells)`. `ExaeroContext` is instantiated. Persistent sorting views are allocated. Registry validates `mechanism_name`.
2.  **Timestep Execution**: Host calls `exaero_solve(...)` passing raw pointers. Unmanaged Views are bound. SZA array is analyzed, and the persistent index map is updated. `Kokkos::TeamPolicy` dispatches the active mechanism.
3.  **Utility Teardown**: Host calls `exaero_finalize()`. `ExaeroContext` is destroyed.
