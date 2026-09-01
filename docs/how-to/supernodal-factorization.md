# Inspect and test plan-backed factorization

Generated mechanisms keep their public header at `mkpp-generated/<mechanism>.hpp`
and implementation assets under `mkpp-generated/<mechanism>/`. Each mechanism
also emits `factorization_plan.json` and `factorization_plan.md`.

The sparse plan-backed LU backend is the default. The unrolled LU implementation
is retained as a reference backend and can be selected with:

```sh
cmake -S . -B build -DCMAKE_CXX_FLAGS=-DMKPP_USE_UNROLLED_REFERENCE
```

Compare identical TS1 controls with
`benchmarks/supernodal_factorization/main.py --reference ... --candidate ...`.
Promote the candidate only after forward, adjoint, TLM, numerical-parity, and
CPU-throughput gates pass. CUDA/HIP execution remains deferred until hardware
is available.
