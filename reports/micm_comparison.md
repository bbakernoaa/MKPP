# MKPP vs MICM / OpenAtmos Comparison Report

Automated comparison of MKPP Ahead-Of-Time (AOT) Kokkos chemistry solver against MICM-compatible reference kinetics.

## Summary

| Mechanism | Species | Reactions | MKPP Time (ms) | Ref Time (ms) | Speedup | Accuracy Status |
| :--- | :---: | :---: | :---: | :---: | :---: | :---: |
| `mechanism` | 4 | 4 | 10.92 | 290.94 | 26.64x | ✅ PASS |
| `chapman` | 4 | 4 | 60.77 | 447.21 | 7.36x | ✅ PASS |
| `small_strato` | 7 | 10 | 89.80 | 1569.72 | 17.48x | ✅ PASS |
| `gocart` | 26 | 27 | 2022.00 | 552.97 | 0.27x | ✅ PASS |
| `carbon` | 11 | 5 | 29.45 | 769.13 | 26.12x | ✅ PASS |

## Detailed Mechanism Results

### Mechanism: `mechanism`

- **Path**: `/Users/barry/Documents/MKPP/fixtures/micm-chapman/mechanism.json`
- **Grid Cells**: 1,000
- **Timesteps**: 100 (dt = 60.0 s)
- **Jacobian Non-Zeros**: 8
- **Throughput**: 9.16e+06 cell-steps/sec

#### Species Accuracy Table

| Species | Computed | Expected | Abs Error | Rel Error | Status |
| :--- | :---: | :---: | :---: | :---: | :---: |
| `O` | 1.724144e+07 | 1.724138e+07 | 6.25e+01 | 3.63e-06 | PASS |
| `O2` | 1.655171e+08 | 1.655172e+08 | 1.25e+02 | 7.55e-07 | PASS |
| `O3` | 1.724144e+07 | 1.724138e+07 | 6.25e+01 | 3.63e-06 | PASS |
| `M` | 1.000000e+08 | 1.000000e+08 | 0.00e+00 | 0.00e+00 | PASS |

### Mechanism: `chapman`

- **Path**: `/Users/barry/Documents/MKPP/mechanisms/chapman.yaml`
- **Grid Cells**: 1,000
- **Timesteps**: 100 (dt = 60.0 s)
- **Jacobian Non-Zeros**: 8
- **Throughput**: 1.65e+06 cell-steps/sec

#### Species Accuracy Table

| Species | Computed | Expected | Abs Error | Rel Error | Status |
| :--- | :---: | :---: | :---: | :---: | :---: |
| `O` | 1.352038e+08 | 1.352038e+08 | 0.00e+00 | 0.00e+00 | PASS |
| `O2` | 2.323970e+08 | 2.323970e+08 | 0.00e+00 | 0.00e+00 | PASS |
| `O3` | 7.603071e+02 | 7.603071e+02 | 0.00e+00 | 0.00e+00 | PASS |
| `M` | 1.000000e+08 | 1.000000e+08 | 0.00e+00 | 0.00e+00 | PASS |

### Mechanism: `small_strato`

- **Path**: `/Users/barry/Documents/MKPP/mechanisms/small_strato.yaml`
- **Grid Cells**: 1,000
- **Timesteps**: 100 (dt = 60.0 s)
- **Jacobian Non-Zeros**: 22
- **Throughput**: 1.11e+06 cell-steps/sec

#### Species Accuracy Table

| Species | Computed | Expected | Abs Error | Rel Error | Status |
| :--- | :---: | :---: | :---: | :---: | :---: |
| `O` | 4.750039e+07 | 4.750039e+07 | 0.00e+00 | 0.00e+00 | PASS |
| `O1D` | 4.121883e-20 | 4.121883e-20 | 0.00e+00 | 0.00e+00 | PASS |
| `O3` | 4.568039e+07 | 4.568039e+07 | 0.00e+00 | 0.00e+00 | PASS |
| `NO` | 1.981629e+08 | 1.981629e+08 | 0.00e+00 | 0.00e+00 | PASS |
| `NO2` | 1.837132e+06 | 1.837132e+06 | 0.00e+00 | 0.00e+00 | PASS |
| `M` | 1.000000e+08 | 1.000000e+08 | 0.00e+00 | 0.00e+00 | PASS |
| `O2` | 3.068106e+08 | 3.068106e+08 | 0.00e+00 | 0.00e+00 | PASS |

### Mechanism: `gocart`

- **Path**: `/Users/barry/Documents/MKPP/mechanisms/gocart.yaml`
- **Grid Cells**: 1,000
- **Timesteps**: 100 (dt = 60.0 s)
- **Jacobian Non-Zeros**: 111
- **Throughput**: 4.95e+04 cell-steps/sec

#### Species Accuracy Table

| Species | Computed | Expected | Abs Error | Rel Error | Status |
| :--- | :---: | :---: | :---: | :---: | :---: |
| `OH` | 1.954421e+07 | 1.954421e+07 | 0.00e+00 | 0.00e+00 | PASS |
| `NO3` | 9.898037e+07 | 9.898037e+07 | 0.00e+00 | 0.00e+00 | PASS |
| `H2O2` | 8.284327e+07 | 8.284327e+07 | 0.00e+00 | 0.00e+00 | PASS |
| `DMS` | 3.213118e+07 | 3.213118e+07 | 0.00e+00 | 0.00e+00 | PASS |
| `SO2` | 3.598645e+06 | 3.598645e+06 | 0.00e+00 | 0.00e+00 | PASS |
| `SO4` | 2.642702e+08 | 2.642702e+08 | 0.00e+00 | 0.00e+00 | PASS |
| `BC1` | 9.704455e+07 | 9.704455e+07 | 0.00e+00 | 0.00e+00 | PASS |
| `BC2` | 1.029554e+08 | 1.029554e+08 | 0.00e+00 | 0.00e+00 | PASS |
| `OC1` | 9.704455e+07 | 9.704455e+07 | 0.00e+00 | 0.00e+00 | PASS |
| `OC2` | 1.029554e+08 | 1.029554e+08 | 0.00e+00 | 0.00e+00 | PASS |
| `DUST1` | 1.000000e+08 | 1.000000e+08 | 0.00e+00 | 0.00e+00 | PASS |
| `DUST2` | 1.000000e+08 | 1.000000e+08 | 0.00e+00 | 0.00e+00 | PASS |
| `DUST3` | 1.000000e+08 | 1.000000e+08 | 0.00e+00 | 0.00e+00 | PASS |
| `DUST4` | 1.000000e+08 | 1.000000e+08 | 0.00e+00 | 0.00e+00 | PASS |
| `DUST5` | 1.000000e+08 | 1.000000e+08 | 0.00e+00 | 0.00e+00 | PASS |
| `SS1` | 1.000000e+08 | 1.000000e+08 | 0.00e+00 | 0.00e+00 | PASS |
| `SS2` | 1.000000e+08 | 1.000000e+08 | 0.00e+00 | 0.00e+00 | PASS |
| `SS3` | 1.000000e+08 | 1.000000e+08 | 0.00e+00 | 0.00e+00 | PASS |
| `SS4` | 1.000000e+08 | 1.000000e+08 | 0.00e+00 | 0.00e+00 | PASS |
| `SS5` | 1.000000e+08 | 1.000000e+08 | 0.00e+00 | 0.00e+00 | PASS |
| `HNO3` | 2.478752e+05 | 2.478752e+05 | 0.00e+00 | 0.00e+00 | PASS |
| `NH3` | 1.000000e+08 | 1.000000e+08 | 0.00e+00 | 0.00e+00 | PASS |
| `NH4a` | 1.000000e+08 | 1.000000e+08 | 0.00e+00 | 0.00e+00 | PASS |
| `NO3an1` | 1.399008e+08 | 1.399008e+08 | 0.00e+00 | 0.00e+00 | PASS |
| `NO3an2` | 1.299256e+08 | 1.299256e+08 | 0.00e+00 | 0.00e+00 | PASS |
| `NO3an3` | 1.299256e+08 | 1.299256e+08 | 0.00e+00 | 0.00e+00 | PASS |

### Mechanism: `carbon`

- **Path**: `/Users/barry/Documents/MKPP/mechanisms/carbon.yaml`
- **Grid Cells**: 1,000
- **Timesteps**: 100 (dt = 60.0 s)
- **Jacobian Non-Zeros**: 19
- **Throughput**: 3.40e+06 cell-steps/sec

#### Species Accuracy Table

| Species | Computed | Expected | Abs Error | Rel Error | Status |
| :--- | :---: | :---: | :---: | :---: | :---: |
| `CH4` | 1.000000e+08 | 1.000000e+08 | 0.00e+00 | 0.00e+00 | PASS |
| `CO` | 1.917095e+08 | 1.917095e+08 | 0.00e+00 | 0.00e+00 | PASS |
| `PCOfromCH4` | 1.000000e+08 | 1.000000e+08 | 0.00e+00 | 0.00e+00 | PASS |
| `PCOfromNMVOC` | 2.000000e+08 | 2.000000e+08 | 0.00e+00 | 0.00e+00 | PASS |
| `LCH4byOH` | 1.000000e+08 | 1.000000e+08 | 0.00e+00 | 0.00e+00 | PASS |
| `LCH4byCl` | 1.000000e+08 | 1.000000e+08 | 0.00e+00 | 0.00e+00 | PASS |
| `LCObyOH` | 1.082905e+08 | 1.082905e+08 | 0.00e+00 | 0.00e+00 | PASS |
| `FixedOH` | 9.170955e+07 | 9.170955e+07 | 0.00e+00 | 0.00e+00 | PASS |
| `FixedCl` | 1.000000e+08 | 1.000000e+08 | 0.00e+00 | 0.00e+00 | PASS |
| `DummyCH4` | 1.000000e+08 | 1.000000e+08 | 0.00e+00 | 0.00e+00 | PASS |
| `DummyNMVOC` | 4.339868e-296 | 4.339868e-296 | 0.00e+00 | 0.00e+00 | PASS |
