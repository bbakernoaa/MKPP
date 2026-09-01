# Plan-backed factorization candidate status

The sparse plan-backed path is now the default. The unrolled implementation is
retained as an explicit reference backend.

## Evidence (2026-08-26)

- Chapman, one cell, one ROS3 step, `dt=1`: checkpoint values were bitwise
  identical to the unrolled reference.
- TS1, one cell, one ROS3 step, `dt=1`: maximum relative checkpoint error was
  `0.0` across the emitted species values.
- Chapman timing was `2.80 ms` for the candidate versus `0.36 ms` for the
  reference in the same container run.  This fails the 90%-of-reference CPU
  acceptance gate.

## Decision

The unrolled implementation is selected with `MKPP_USE_UNROLLED_REFERENCE` for
reference comparisons.

## Sparse-plan traversal update

The initial dense traversal was replaced by a generated sparse L/U-pattern
traversal.  On TS1 (one cell, six steps, two warmups, five repetitions,
`dt=10`) it produced a maximum relative checkpoint error of `0.0`.  The
reported solve timing was `3017.23 ms` versus `2975.04 ms` for the unrolled
reference: 98.6% of reference throughput in this controlled sample.

Forward, adjoint/TLM parity and the longer CPU campaign support the default
selection; GPU execution remains deferred.

The corrected sparse traversal was rerun with the same controls: TS1, one cell,
six steps, two warmups, five repetitions, `dt=10`.  It measured `3139.46 ms`
versus `3048.90 ms` for the reference (97.1% of reference throughput) with
maximum relative state error `0.0`.

A completed three-run campaign (TS1, one cell, three steps, one warmup, two
repetitions, `dt=10`) produced reference timings of 1290.50, 1215.72, and
1220.88 ms (median 1220.88 ms), and candidate timings of 1162.73, 1246.59,
and 1167.14 ms (median 1167.14 ms).  The candidate median was 104.6% of the
reference.  This short campaign is directional because it uses fewer steps;
the longer campaign remains the acceptance evidence.
