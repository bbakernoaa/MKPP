# Supernodal Factorization GPU Validation Status

**Status**: Deferred

No CUDA or AMD GPU is available in the current validation environment. No GPU
correctness or performance result is claimed for the namespaced generated
artifacts or the future plan-backed factorization backend.

Before promotion, run the multi-mechanism coexistence test, forward/adjoint/TLM
parity suite, and fixed-control TS1 throughput benchmark on each supported
CUDA and HIP execution space. Record compiler, Kokkos configuration, device,
mechanism revision, and median throughput beside the CPU reference result.
