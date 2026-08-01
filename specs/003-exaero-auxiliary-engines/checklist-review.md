# Review Report: 003-exaero-auxiliary-engines

## Overview
Implementation verification for `003-exaero-auxiliary-engines` against spec and constitution.

## Findings

### Critical

**Missing NaN/Inf Validation on Input Boundaries (Confidence: 100)**
- **File**: `src/exaero/src/auxiliary_engines.cpp`
- **Issue**: Task `T017` was marked complete ("Implement pre-dispatch validation checks for NaN/Inf conditions on incoming arrays") and the project constitution demands evaluating NaN/Inf on all input boundaries. However, `PhotolysisFunctor` and `ThermoFunctor` pass the raw `.data()` pointers to the external Fortran drivers without any numerical validation, which could crash the Fortran solver if corrupted data is ingested.
- **Recommendation**: Add a validation step or assertion inside the `operator()` of both functors to ensure no `NaN` or `Inf` values exist in the `state.meteorology` or `state.concentrations` arrays before passing them to the Fortran routines. Or, use a Kokkos parallel reduction beforehand.

### Important

**No Missing Data Handlers (Confidence: 85)**
- **File**: `src/exaero/src/auxiliary_engines.cpp`
- **Issue**: The spec edge case asks "How does the system handle missing or corrupted input arrays from the C++ driver...". The current implementation assumes `state.meteorology` and `state.concentrations` are always valid. There is no null-pointer checking on the `.data()` pointers.
- **Recommendation**: Add a check `if (!state.meteorology.data()) { /* handle error */ }` prior to dispatching to the Fortran libraries.

### Suggestion

**Test Suite Coverage of Dummy Operations (Confidence: 80)**
- **File**: `src/exaero/tests/test_auxiliary_engines.cpp`
- **Issue**: The test verifies the pointers match, but doesn't explicitly verify the behavior when the engines are disabled via CMake vs enabled.
- **Recommendation**: Add preprocessor macros in the test suite to assert the execution path depending on `EXAERO_WITH_CLOUDJ` and `EXAERO_WITH_ISORROPIALITE`.
