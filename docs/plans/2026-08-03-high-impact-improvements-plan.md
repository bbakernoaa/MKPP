# High-Impact MKPP Core Improvements Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Implement 4 core high-impact improvements across MKPP: multi-solver tableau code generation, RCM reordering & block-sparse LU lowering, Python AST flux lowering deduplication, and thermodynamically accurate non-Arrhenius AMORE mechanism reduction.

**Architecture:**
1. `codegen.py`: Refactor C++/Kokkos header emission so stage unrolling and step-size control adapt dynamically to any selected `RosenbrockTableau` (`ros2`, `ros3`, `ros4`, `rodas3`, `rodas4`).
2. `lowering.py`: Connect `SparsityOptimizer`'s RCM bandwidth reduction and block-diagonal decomposition directly to symbolic LU decomposition and header generation.
3. `lowering.py`: Extract unified reaction flux evaluation (`_evaluate_reaction_fluxes`) to eliminate AST traversing duplication.
4. `amore.py`: Enhance non-Arrhenius parameter merging to fit/composite rate parameters over atmospheric T/P grids ($200\text{K}-300\text{K}$, $100-1000\text{hPa}$).

**Tech Stack:** Python 3.10+, SymPy, NetworkX, Kokkos C++23, pytest.

## Global Constraints

- Preserve complete backward compatibility for existing CLI and Python API (`mkpp.codegen`, `mkpp.lowering`, `mkpp.amore`).
- Ensure all generated C++ headers compile cleanly without syntax errors or missing variable declarations.
- Maintain strict numerical reproducibility and pass the full pytest suite (`pytest tests/python/`).

---

### Task 1: Generalize Main C++/Kokkos Header Emission for All Rosenbrock Tableaus

**Files:**
- Modify: `src/mkpp/codegen.py`
- Test: `tests/python/test_codegen.py`

**Interfaces:**
- Consumes: `SOLVER_COEFFICIENTS` dict in `src/mkpp/codegen.py` containing `RosenbrockTableau` definitions for `ros2`, `ros3`, `ros4`, `rodas3`, `rodas4`.
- Produces: Dynamic C++/Kokkos solver `integrate()` and `integrate_with_reduction()` kernels matching the chosen solver's stage count, coefficients, and embedded error order exponent (`1.0 / tableau.ELO`).

- [ ] **Step 1: Write the failing test**

```python
# Add test in tests/python/test_codegen.py verifying header generation for all solvers
def test_all_rosenbrock_tableaus_codegen(tmp_path):
    from mkpp.codegen import generate_kokkos_header, SOLVER_COEFFICIENTS
    from mkpp.model import MechanismDefinition, SpeciesDefinition, ReactionDefinition

    mech = MechanismDefinition(
        name="test_mech",
        species=[SpeciesDefinition(name="A"), SpeciesDefinition(name="B")],
        reactions=[
            ReactionDefinition(
                reactants={"A": 1},
                products={"B": 1},
                reaction_type="ARRHENIUS",
                parameters={"A": 1e-2, "B": 0.0, "C": 0.0}
            )
        ]
    )

    for solver_name in ["ros2", "ros3", "ros4", "rodas3", "rodas4"]:
        res = generate_kokkos_header(mech, out_dir=str(tmp_path), solver_name=solver_name, suffix=f"_{solver_name}")
        header_file = tmp_path / f"test_mech_{solver_name}.hpp"
        assert header_file.exists()
        content = header_file.read_text()
        # Verify tableau-specific coefficients are emitted
        tableau = SOLVER_COEFFICIENTS[solver_name]
        assert f"// Generated solver for test_mech" in content
        assert f"const int STAGES = {tableau.stages}" in content or f"ros_M{tableau.stages}" in content
```

- [ ] **Step 2: Run test to make sure it fails**

```bash
/Users/barry/Documents/MKPP/.venv/bin/python -m pytest tests/python/test_codegen.py -k test_all_rosenbrock_tableaus_codegen
```

- [ ] **Step 3: Implement dynamic stage unrolling in `codegen.py`**

Refactor `generate_kokkos_header` in `src/mkpp/codegen.py` so `integrate` uses `_emit_rosenbrock_stages()` or dynamically writes stages for any selected `tableau` (`ros2`, `ros3`, `ros4`, `rodas3`, `rodas4`).

- [ ] **Step 4: Run tests and make sure they pass**

```bash
/Users/barry/Documents/MKPP/.venv/bin/python -m pytest tests/python/test_codegen.py
```

- [ ] **Step 5: Commit changes**

```bash
git commit -am "feat(codegen): dynamic C++ header emission for all Rosenbrock tableaus"
```

---

### Task 2: Enable RCM Reordering & Block-Sparse LU Decomposition in Symbolic Lowering Pipeline

**Files:**
- Modify: `src/mkpp/lowering.py`
- Modify: `src/mkpp/codegen.py`
- Test: `tests/python/test_property_sparsity.py`
- Test: `tests/python/test_codegen.py`

**Interfaces:**
- Consumes: `SparsityOptimizer.analyze()` return value (`SparsityAnalysisResult` containing `permutation`, `blocks`, `is_block_diagonal`, `fill_in_count`).
- Produces: Permuted and block-decomposed `SymbolicLUPlan` attached to `prepare_unified_jacobian()` return dict and mechanism metadata.

- [ ] **Step 1: Write the failing test**

```python
def test_rcm_permutation_wired_into_lu_plan():
    from mkpp.lowering import prepare_unified_jacobian, SparsityOptimizer
    # Create mechanism with decoupled sparse Jacobian block structure
    # Assert that symbolic_lu_plan returned by prepare_unified_jacobian contains the permutation and blocks
```

- [ ] **Step 2: Run test to make sure it fails**

```bash
/Users/barry/Documents/MKPP/.venv/bin/python -m pytest tests/python/test_property_sparsity.py
```

- [ ] **Step 3: Pass RCM analysis results into `compute_symbolic_lu_decomposition`**

In `src/mkpp/lowering.py`:
- Update `prepare_unified_jacobian` and `prepare_unified_jacobian_parallel` to pass `permutation=analysis.permutation`, `blocks=analysis.blocks`, and `is_block_diagonal=analysis.is_block_diagonal` into `compute_symbolic_lu_decomposition`.
- In `src/mkpp/codegen.py`: Ensure state array indexing uses `_perm` properly for all stage vector loads and updates.

- [ ] **Step 4: Run tests to ensure pass**

```bash
/Users/barry/Documents/MKPP/.venv/bin/python -m pytest tests/python/
```

- [ ] **Step 5: Commit changes**

```bash
git commit -am "perf(lowering): wire RCM bandwidth reduction and block LU into symbolic lowering"
```

---

### Task 3: Refactor Reaction Flux Lowering AST Deduplication

**Files:**
- Modify: `src/mkpp/lowering.py`
- Test: `tests/python/test_codegen.py`

**Interfaces:**
- Consumes: `MechanismDefinition` reaction AST.
- Produces: `_evaluate_reaction_fluxes()` helper returning `(df_dt_implicit, df_dt_explicit, photolysis_reactions, photo_idx)`.

- [ ] **Step 1: Write unit test to verify flux equivalence**

```python
def test_reaction_flux_lowering_equivalence():
    # Verify prepare_unified_jacobian produces identical implicit and explicit ODE vectors before and after refactoring
```

- [ ] **Step 2: Extract `_evaluate_reaction_fluxes` in `lowering.py`**

Refactor `prepare_unified_jacobian` and `_build_f_total` in `src/mkpp/lowering.py` to use `_evaluate_reaction_fluxes`, removing ~120 lines of redundant code.

- [ ] **Step 3: Run pytest suite**

```bash
/Users/barry/Documents/MKPP/.venv/bin/python -m pytest tests/python/
```

- [ ] **Step 4: Commit changes**

```bash
git commit -am "refactor(lowering): extract reaction flux lowering helper function"
```

---

### Task 4: Thermodynamically Accurate Non-Arrhenius AMORE Mechanism Reduction

**Files:**
- Modify: `src/mkpp/amore.py`
- Test: `tests/python/test_amore_non_arrhenius.py`

**Interfaces:**
- Consumes: Dict of lumped surrogate mapping rules and `MechanismDefinition`.
- Produces: Merged `ReactionDefinition` with thermodynamically valid composite parameters for non-Arrhenius reactions (`TROE`, `FALLOFF`, `EP2`, `EP3`).

- [ ] **Step 1: Write failing test for non-Arrhenius lumping**

```python
def test_amore_non_arrhenius_troe_lumping():
    from mkpp.amore import apply_amore_lumping
    # Create mechanism with 2 Troe reactions mapping to same surrogate
    # Verify rate expressions do not cause invalid parameter division or unphysical yields
```

- [ ] **Step 2: Run test to make sure it fails**

```bash
/Users/barry/Documents/MKPP/.venv/bin/python -m pytest tests/python/test_amore_non_arrhenius.py
```

- [ ] **Step 3: Implement enhanced parameter merging for Troe/Falloff/EP2/EP3 in `amore.py`**

Refactor `apply_amore_lumping` in `src/mkpp/amore.py` to generate correct composite rate expressions for non-Arrhenius reactions.

- [ ] **Step 4: Run tests and verify success**

```bash
/Users/barry/Documents/MKPP/.venv/bin/python -m pytest tests/python/
```

- [ ] **Step 5: Commit changes**

```bash
git commit -am "feat(amore): add thermodynamically accurate non-Arrhenius reaction lumping"
```
