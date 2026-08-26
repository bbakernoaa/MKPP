"""Validation tests for readable generated factorization plans."""

import json

import pytest
from mkpp.codegen import generate_headers
from mkpp.factorization_plan import FactorizationBlock, FactorizationPlan, make_factorization_plan
from mkpp.parser import load_mechanism
from mkpp.template_context import build_template_context


def test_plan_is_a_complete_permutation_with_contiguous_blocks():
    operations = [{"kind": "U", "i": 0, "j": 0, "expr": "w[0]"} for _ in range(5)]
    plan = make_factorization_plan("test", 4, operations, block_size=2)
    assert plan.elimination_order == (0, 1, 2, 3)
    assert [block.operation_count for block in plan.blocks] == [2, 2, 1]


def test_plan_rejects_forward_dependencies():
    plan = FactorizationPlan("bad", 1, (0,), 1, (FactorizationBlock(0, 0, 1, (0,)),))
    with pytest.raises(ValueError, match="FATAL ERROR"):
        plan.validate()


def test_plan_extracts_cross_block_symbolic_dependencies():
    operations = [
        {"kind": "U", "i": 0, "j": 0, "expr": "w[0]"},
        {"kind": "L", "i": 1, "j": 0, "expr": "U_0_0"},
    ]
    plan = make_factorization_plan("test", 2, operations, block_size=1)
    assert plan.blocks[1].dependencies == (0,)


def test_template_context_extracts_plan_from_symbolic_lu():
    mechanism = load_mechanism("mechanisms/openatmos/chapman/mechanism.json")
    context = build_template_context(mechanism)
    plan = context["factorization_plan"]
    assert plan.mechanism == "chapman"
    assert plan.operation_count == len(context["compiled_lu_expressions"])
    plan.validate()


def test_generation_emits_readable_plan_artifacts(tmp_path):
    mechanism = load_mechanism("mechanisms/openatmos/chapman/mechanism.json")
    results = generate_headers(mechanism, out_dir=tmp_path)
    document = json.loads((tmp_path / "chapman" / "factorization_plan.json").read_text())
    description = (tmp_path / "chapman" / "factorization_plan.md").read_text()
    assert results["factorization_plan"].endswith("chapman/factorization_plan.json")
    assert document["mechanism"] == "chapman"
    assert document["operation_count"] > 0
    assert document["fill_in_count"] >= 0
    assert "| Block |" in description
