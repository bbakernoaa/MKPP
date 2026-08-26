# TS1 CPU factorization comparison

Controls: one cell, three steps, one warmup, two repetitions, `dt=10`, cece-dev
OpenMP host.

| Backend | Runs (ms) | Median (ms) | Relative throughput |
|---|---:|---:|---:|
| Unrolled reference | 1290.50, 1215.72, 1220.88 | 1220.88 | 100.0% |
| Sparse plan candidate | 1162.73, 1246.59, 1167.14 | 1167.14 | 104.6% |

The candidate’s controlled TS1 checkpoint parity error was `0.0`. This short
campaign is directional; the longer six-step campaign measured 97.1% of the
reference and remains the conservative acceptance result.

Longer campaign: one cell, 12 steps, two warmups, five repetitions, `dt=10`,
three independent runs per backend. Reference timings were 1516.72, 1482.70,
and 1534.42 ms (median 1516.72 ms). Candidate timings were 1467.00, 1586.24,
and 1541.35 ms (median 1541.35 ms), or 98.4% of reference throughput.
