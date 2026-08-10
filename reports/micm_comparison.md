# MKPP vs MICM / OpenAtmos Comparison Report

Automated comparison of MKPP Ahead-Of-Time (AOT) Kokkos chemistry solver against MICM-compatible reference kinetics.

## Summary

| Mechanism | Species | Reactions | MKPP Time (ms) | Ref Time (ms) | Speedup | Accuracy Status |
| :--- | :---: | :---: | :---: | :---: | :---: | :---: |
| `mechanism` | 4 | 4 | 1.46 | 3.41 | 2.34x | ✅ PASS |
| `chapman` | 4 | 4 | 30.73 | 88.93 | 2.89x | ✅ PASS |
| `small_strato` | 7 | 10 | 44.53 | 1.44 | 0.03x | ✅ PASS |
| `gocart` | 26 | 27 | 1464.09 | 7.08 | 0.00x | ✅ PASS |
| `carbon` | 11 | 5 | 26.88 | 102.43 | 3.81x | ✅ PASS |

## Detailed Mechanism Results

### Mechanism: `mechanism`

- **Path**: `/Users/barry/Documents/MKPP/fixtures/micm-chapman/mechanism.json`
- **Grid Cells**: 1,000
- **Timesteps**: 100 (dt = 60.0 s)
- **Jacobian Non-Zeros**: 8
- **Throughput**: 6.86e+07 cell-steps/sec

#### Species Accuracy Table

| Species | Computed | Expected | Abs Error | Rel Error | Status |
| :--- | :---: | :---: | :---: | :---: | :---: |
| `O` | 1.000000e+00 | 1.000000e+00 | 8.88e-16 | 8.88e-16 | PASS |
| `O2` | 2.100001e-01 | 2.100001e-01 | 1.50e-15 | 7.14e-15 | PASS |
| `O3` | 1.000000e+00 | 1.000000e+00 | 5.55e-16 | 5.55e-16 | PASS |
| `M` | 1.000000e+00 | 1.000000e+00 | 0.00e+00 | 0.00e+00 | PASS |

### Mechanism: `chapman`

- **Path**: `/Users/barry/Documents/MKPP/mechanisms/chapman.yaml`
- **Grid Cells**: 1,000
- **Timesteps**: 100 (dt = 60.0 s)
- **Jacobian Non-Zeros**: 8
- **Throughput**: 3.25e+06 cell-steps/sec

#### Species Accuracy Table

| Species | Computed | Expected | Abs Error | Rel Error | Status |
| :--- | :---: | :---: | :---: | :---: | :---: |
| `O` | 2.211488e+00 | 2.211488e+00 | 0.00e+00 | 0.00e+00 | PASS |
| `O2` | 1.890538e+00 | 1.890538e+00 | 0.00e+00 | 0.00e+00 | PASS |
| `O3` | 2.478752e-03 | 2.478752e-03 | 0.00e+00 | 0.00e+00 | PASS |
| `M` | 1.000000e+00 | 1.000000e+00 | 0.00e+00 | 0.00e+00 | PASS |

### Mechanism: `small_strato`

- **Path**: `/Users/barry/Documents/MKPP/mechanisms/small_strato.yaml`
- **Grid Cells**: 1,000
- **Timesteps**: 100 (dt = 60.0 s)
- **Jacobian Non-Zeros**: 22
- **Throughput**: 2.25e+06 cell-steps/sec

#### Species Accuracy Table

| Species | Computed | Expected | Abs Error | Rel Error | Status |
| :--- | :---: | :---: | :---: | :---: | :---: |
| `O` | 1.000000e+00 | 1.000000e+00 | 0.00e+00 | 0.00e+00 | PASS |
| `O1D` | 9.999989e-01 | 9.999989e-01 | 0.00e+00 | 0.00e+00 | PASS |
| `O3` | 9.999993e-01 | 9.999993e-01 | 0.00e+00 | 0.00e+00 | PASS |
| `NO` | 1.000000e+00 | 1.000000e+00 | 0.00e+00 | 0.00e+00 | PASS |
| `NO2` | 9.999999e-01 | 9.999999e-01 | 0.00e+00 | 0.00e+00 | PASS |
| `M` | 1.000000e+00 | 1.000000e+00 | 0.00e+00 | 0.00e+00 | PASS |
| `O2` | 1.000002e+00 | 1.000002e+00 | 0.00e+00 | 0.00e+00 | PASS |

### Mechanism: `gocart`

- **Path**: `/Users/barry/Documents/MKPP/mechanisms/gocart.yaml`
- **Grid Cells**: 1,000
- **Timesteps**: 100 (dt = 60.0 s)
- **Jacobian Non-Zeros**: 111
- **Throughput**: 6.83e+04 cell-steps/sec

#### Species Accuracy Table

| Species | Computed | Expected | Abs Error | Rel Error | Status |
| :--- | :---: | :---: | :---: | :---: | :---: |
| `OH` | 1.116471e+00 | 1.116471e+00 | 0.00e+00 | 0.00e+00 | PASS |
| `NO3` | 1.000000e+00 | 1.000000e+00 | 0.00e+00 | 0.00e+00 | PASS |
| `H2O2` | 9.417645e-01 | 9.417645e-01 | 0.00e+00 | 0.00e+00 | PASS |
| `DMS` | 1.000000e+00 | 1.000000e+00 | 0.00e+00 | 0.00e+00 | PASS |
| `SO2` | 9.999999e-01 | 9.999999e-01 | 0.00e+00 | 0.00e+00 | PASS |
| `SO4` | 1.000000e+00 | 1.000000e+00 | 0.00e+00 | 0.00e+00 | PASS |
| `BC1` | 9.704455e-01 | 9.704455e-01 | 0.00e+00 | 0.00e+00 | PASS |
| `BC2` | 1.029554e+00 | 1.029554e+00 | 0.00e+00 | 0.00e+00 | PASS |
| `OC1` | 9.704455e-01 | 9.704455e-01 | 0.00e+00 | 0.00e+00 | PASS |
| `OC2` | 1.029554e+00 | 1.029554e+00 | 0.00e+00 | 0.00e+00 | PASS |
| `DUST1` | 1.000000e+00 | 1.000000e+00 | 0.00e+00 | 0.00e+00 | PASS |
| `DUST2` | 1.000000e+00 | 1.000000e+00 | 0.00e+00 | 0.00e+00 | PASS |
| `DUST3` | 1.000000e+00 | 1.000000e+00 | 0.00e+00 | 0.00e+00 | PASS |
| `DUST4` | 1.000000e+00 | 1.000000e+00 | 0.00e+00 | 0.00e+00 | PASS |
| `DUST5` | 1.000000e+00 | 1.000000e+00 | 0.00e+00 | 0.00e+00 | PASS |
| `SS1` | 1.000000e+00 | 1.000000e+00 | 0.00e+00 | 0.00e+00 | PASS |
| `SS2` | 1.000000e+00 | 1.000000e+00 | 0.00e+00 | 0.00e+00 | PASS |
| `SS3` | 1.000000e+00 | 1.000000e+00 | 0.00e+00 | 0.00e+00 | PASS |
| `SS4` | 1.000000e+00 | 1.000000e+00 | 0.00e+00 | 0.00e+00 | PASS |
| `SS5` | 1.000000e+00 | 1.000000e+00 | 0.00e+00 | 0.00e+00 | PASS |
| `HNO3` | 9.999999e-01 | 9.999999e-01 | 0.00e+00 | 0.00e+00 | PASS |
| `NH3` | 1.000000e+00 | 1.000000e+00 | 0.00e+00 | 0.00e+00 | PASS |
| `NH4a` | 1.000000e+00 | 1.000000e+00 | 0.00e+00 | 0.00e+00 | PASS |
| `NO3an1` | 1.000000e+00 | 1.000000e+00 | 0.00e+00 | 0.00e+00 | PASS |
| `NO3an2` | 1.000000e+00 | 1.000000e+00 | 0.00e+00 | 0.00e+00 | PASS |
| `NO3an3` | 1.000000e+00 | 1.000000e+00 | 0.00e+00 | 0.00e+00 | PASS |

### Mechanism: `carbon`

- **Path**: `/Users/barry/Documents/MKPP/mechanisms/carbon.yaml`
- **Grid Cells**: 1,000
- **Timesteps**: 100 (dt = 60.0 s)
- **Jacobian Non-Zeros**: 19
- **Throughput**: 3.72e+06 cell-steps/sec

#### Species Accuracy Table

| Species | Computed | Expected | Abs Error | Rel Error | Status |
| :--- | :---: | :---: | :---: | :---: | :---: |
| `CH4` | 1.000000e+00 | 1.000000e+00 | 0.00e+00 | 0.00e+00 | PASS |
| `CO` | 2.000000e+00 | 2.000000e+00 | 0.00e+00 | 0.00e+00 | PASS |
| `PCOfromCH4` | 1.000000e+00 | 1.000000e+00 | 0.00e+00 | 0.00e+00 | PASS |
| `PCOfromNMVOC` | 2.000000e+00 | 2.000000e+00 | 0.00e+00 | 0.00e+00 | PASS |
| `LCH4byOH` | 1.000000e+00 | 1.000000e+00 | 0.00e+00 | 0.00e+00 | PASS |
| `LCH4byCl` | 1.000000e+00 | 1.000000e+00 | 0.00e+00 | 0.00e+00 | PASS |
| `LCObyOH` | 1.000000e+00 | 1.000000e+00 | 0.00e+00 | 0.00e+00 | PASS |
| `FixedOH` | 1.000000e+00 | 1.000000e+00 | 0.00e+00 | 0.00e+00 | PASS |
| `FixedCl` | 1.000000e+00 | 1.000000e+00 | 0.00e+00 | 0.00e+00 | PASS |
| `DummyCH4` | 1.000000e+00 | 1.000000e+00 | 0.00e+00 | 0.00e+00 | PASS |
| `DummyNMVOC` | -4.258395e-53 | -4.258395e-53 | 0.00e+00 | 0.00e+00 | PASS |
