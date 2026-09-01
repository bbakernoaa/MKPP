---
type: tutorial
category: tutorials
tags: [benchmark, micm, c++, performance]
---

# Historical MKPP/MICM diagnostic

This page documents a retired diagnostic path. It must not be used to claim an
MKPP-versus-MICM speedup or a solver-comparison result.

`scripts/compare_micm.py` parses a mechanism and constructs an independent
SciPy reference. It does not execute MICM, and it deliberately fails when a
real named MKPP checkpoint result is unavailable. Its historical throughput and
speedup examples were therefore not fair solver-comparison evidence.

Use the governed solver-comparison workflow instead:

```bash
python scripts/compare_solvers.py --list-mechanisms
python scripts/compare_solvers.py \
  --validate --campaign benchmarks/solver_comparison/campaigns/cpu-primary-v1.yaml
```

The governed workflow requires real MICM, KPP (where admitted), and MKPP
runners; pinned canonical chemistry; matching resources; scientific admission;
and retained JSONL evidence. TS1 remains a MICM/MKPP-only comparison until a
KPP binding is explicitly admitted. See
[Benchmarking MICM, KPP, and MKPP](benchmark-micm-kpp-mkpp.md) for the
publication methodology.

The legacy script may still be useful while developing its independent
reference equations, but treat every result as reference-only diagnostics.
