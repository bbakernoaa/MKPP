---
type: tutorial
category: tutorials
tags: [benchmark, micm, kpp, mkpp, reproducibility]
---

# Benchmarking MICM, KPP, and MKPP

This workflow is for fair, reproducible solver comparisons. A headline ratio is
only valid when it is derived from retained native-runner evidence after the
chemistry, trajectory, configuration, and resource gates have passed.

Start by inspecting and validating the immutable inputs:

```bash
python scripts/compare_solvers.py --list-mechanisms
python scripts/compare_solvers.py \
  --validate --campaign benchmarks/solver_comparison/campaigns/cpu-primary-v1.yaml
```

Each mechanism manifest identifies the canonical reaction/species source,
binding revisions, and required solvers. Every solver must receive the same
canonical chemistry and host-supplied atmospheric state (temperature, pressure,
and named forcing). TS1 is explicitly two-way—MICM and MKPP only—until KPP has
an independently admitted binding. It must never contain a KPP placeholder.

Before timing, the campaign verifies mappings, reaction/rate-law audit evidence,
an independent reference, calibration, and trajectory accuracy. A failed or
missing runner result is retained as a failure and withholds the affected ratio;
it is never replaced by another solver or copied state.

The primary CPU result uses one physical core and one thread for every paired
solver. It collects balanced, block-paired repetitions (15 by default; at least
10 publishable), with stable warmups and a fixed bootstrap seed. Solve and
lifecycle timing boundaries remain separate. A ratio is always named as
`baseline_seconds / candidate_seconds`, so a value above one means the
candidate was faster than the stated baseline.

Raw JSONL is append-only. Markdown, JSON, and optional CSV reports are
reproducible derivations that preserve admission status, uncertainty intervals,
and withholding reasons. Do not infer performance from diagnostic scripts or
from a non-publishable smoke run on uncontrolled hardware.

The native campaign executor is intentionally fail-closed while its configured
runner routing is incomplete: validation may succeed, but it will not write
partial JSONL evidence. This protects the comparison from accidental surrogate
or incomplete results.
