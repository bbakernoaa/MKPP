# Implementation Plan: MkDocs, mkdocstrings & GitHub Pages Documentation Pipeline

**Spec Document:** `docs/superpowers/specs/2026-08-06-mkdocs-github-pages-design.md`  
**Plan Location:** `docs/superpowers/plans/2026-08-06-mkdocs-github-pages-plan.md`

---

## File Structure & Responsibilities

| File Path | Action | Description / Responsibility |
| :--- | :--- | :--- |
| `pyproject.toml` | Modify | Add `[project.optional-dependencies]` section with `docs` dependencies (`mkdocs-material`, `mkdocstrings[python]`, `mkdocs-katex-plugin`) |
| `environment.yml` | Modify | Add `mkdocs-material`, `mkdocstrings-python`, and `mkdocstrings` under conda/pip dependencies |
| `mkdocs.yml` | Create | Root configuration for MkDocs site, Material theme, KaTeX math, superfences, and Diátaxis navigation tree |
| `docs/js/katex.js` | Create | KaTeX auto-render initialization script for mathematical equation rendering |
| `docs/reference/api/cli.md` | Create | Autodoc stub for `mkpp.cli` module using `mkdocstrings` |
| `docs/reference/api/parser.md` | Create | Autodoc stub for `mkpp.parser` module using `mkdocstrings` |
| `docs/reference/api/lowering.md` | Create | Autodoc stub for `mkpp.lowering` module using `mkdocstrings` |
| `docs/reference/api/codegen.md` | Create | Autodoc stub for `mkpp.codegen` module using `mkdocstrings` |
| `docs/reference/api/amore.md` | Create | Autodoc stub for `mkpp.amore` module using `mkdocstrings` |
| `.github/workflows/deploy-docs.yml` | Create | GitHub Actions workflow for building and deploying static MkDocs site to GitHub Pages |

---

## Tasks

### Task 1: Update Project Dependency Specifications

**Files:**
- `pyproject.toml`
- `environment.yml`

**Step 1: Edit `pyproject.toml`**
Add optional dependencies group for documentation:
```toml
[project.optional-dependencies]
docs = [
    "mkdocs-material>=9.5",
    "mkdocstrings[python]>=0.25",
    "mkdocs-katex-plugin",
]
```

**Step 2: Edit `environment.yml`**
Add `mkdocs-material`, `mkdocstrings-python`, and `mkdocstrings` under pip/conda packages.

**Step 3: Verification**
Run `pip install -e .[docs]` and verify installation succeeds without version conflicts.

---

### Task 2: Create KaTeX JS Helper & `mkdocs.yml` Configuration

**Files:**
- `docs/js/katex.js`
- `mkdocs.yml`

**Step 1: Create `docs/js/katex.js`**
```js
document.addEventListener("DOMContentLoaded", function() {
  renderMathInElement(document.body, {
    delimiters: [
      {left: "$$", right: "$$", display: true},
      {left: "$", right: "$", display: false},
      {left: "\\(", right: "\\)", display: false},
      {left: "\\[", right: "\\]", display: true}
    ]
  });
});
```

**Step 2: Create `mkdocs.yml`**
Configure Material theme, dark/light palette, KaTeX math extensions, superfences (Mermaid diagrams), search, mkdocstrings, and full Diátaxis navigation tree.

**Step 3: Verification**
Run `mkdocs build --strict` locally and check output directory generation.

---

### Task 3: Add Python API Autodoc Stubs

**Files:**
- `docs/reference/api/cli.md`
- `docs/reference/api/parser.md`
- `docs/reference/api/lowering.md`
- `docs/reference/api/codegen.md`
- `docs/reference/api/amore.md`

**Step 1: Create API markdown stubs**
Add `::: mkpp.<module>` directives into each API reference document.

**Step 2: Verification**
Run `mkdocs build --strict` and verify that Python docstrings from `src/mkpp/` are extracted and rendered without warnings or missing module errors.

---

### Task 4: Create GitHub Actions Pages Deployment Workflow

**Files:**
- `.github/workflows/deploy-docs.yml`

**Step 1: Create `.github/workflows/deploy-docs.yml`**
Configure GitHub v2 Pages Deployment Action with `actions/upload-pages-artifact@v3` and `actions/deploy-pages@v4`.

**Step 2: Verification**
Verify workflow YAML syntax with pre-commit or action linter.

---

### Task 5: End-to-End Build Verification

**Step 1: Run full strict build**
```bash
mkdocs build --strict
```

**Step 2: Run local preview server**
```bash
mkdocs serve
```
Verify math equations, Mermaid diagrams, navigation links, dark mode toggle, and API references.
