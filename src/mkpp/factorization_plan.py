"""Validated, reviewable metadata for a generated sparse factorization."""

from __future__ import annotations

import re
from collections.abc import Iterable
from dataclasses import dataclass


@dataclass(frozen=True)
class FactorizationBlock:
    ordinal: int
    first_operation: int
    operation_count: int
    dependencies: tuple[int, ...] = ()

    def validate(self) -> None:
        if self.ordinal < 0 or self.first_operation < 0 or self.operation_count <= 0:
            raise ValueError("FATAL ERROR: factorization block has an invalid operation range")
        if any(dependency < 0 or dependency >= self.ordinal for dependency in self.dependencies):
            raise ValueError("FATAL ERROR: factorization block has a forward or invalid dependency")


@dataclass(frozen=True)
class FactorizationPlan:
    mechanism: str
    species_count: int
    elimination_order: tuple[int, ...]
    operation_count: int
    blocks: tuple[FactorizationBlock, ...]
    fill_in_count: int = 0

    def validate(self) -> None:
        if self.species_count <= 0:
            raise ValueError("FATAL ERROR: factorization plan species count must be positive")
        if tuple(sorted(self.elimination_order)) != tuple(range(self.species_count)):
            raise ValueError("FATAL ERROR: factorization plan elimination order is not a complete permutation")
        expected = 0
        for ordinal, block in enumerate(self.blocks):
            if block.ordinal != ordinal or block.first_operation != expected:
                raise ValueError("FATAL ERROR: factorization blocks are not contiguous and ordered")
            block.validate()
            expected += block.operation_count
        if expected != self.operation_count:
            raise ValueError("FATAL ERROR: factorization plan blocks do not cover all operations")
        if self.fill_in_count < 0:
            raise ValueError("FATAL ERROR: factorization plan fill-in count must not be negative")


def make_factorization_plan(
    mechanism: str,
    species_count: int,
    operations: Iterable[dict[str, object]],
    block_size: int = 256,
    elimination_order: Iterable[int] | None = None,
    fill_in_count: int = 0,
) -> FactorizationPlan:
    operations = tuple(operations)
    operation_count = len(operations)
    if block_size <= 0:
        raise ValueError("FATAL ERROR: factorization plan block size must be positive")
    producers: dict[tuple[str, int, int], int] = {}
    dependencies_by_block: list[set[int]] = [set() for _ in range((operation_count + block_size - 1) // block_size)]
    reference_pattern = re.compile(r"\b([LU])_(\d+)_(\d+)\b")
    for operation_index, operation in enumerate(operations):
        try:
            kind = str(operation["kind"])
            row = int(operation["i"])
            column = int(operation["j"])
            expression = str(operation["expr"])
        except (KeyError, TypeError, ValueError) as error:
            raise ValueError("FATAL ERROR: factorization operation is malformed") from error
        if kind not in {"L", "U"} or not (0 <= row < species_count and 0 <= column < species_count):
            raise ValueError("FATAL ERROR: factorization operation references matrix storage out of range")
        current_block = operation_index // block_size
        for reference in reference_pattern.finditer(expression):
            producer = producers.get((reference[1], int(reference[2]), int(reference[3])))
            if producer is None:
                continue
            producer_block = producer // block_size
            if producer_block > current_block:
                raise ValueError("FATAL ERROR: factorization operation has a forward dependency")
            if producer_block != current_block:
                dependencies_by_block[current_block].add(producer_block)
        producers[(kind, row, column)] = operation_index
    blocks = tuple(
        FactorizationBlock(
            index // block_size,
            index,
            min(block_size, operation_count - index),
            tuple(sorted(dependencies_by_block[index // block_size])),
        )
        for index in range(0, operation_count, block_size)
    )
    plan = FactorizationPlan(
        mechanism,
        species_count,
        tuple(range(species_count)) if elimination_order is None else tuple(elimination_order),
        operation_count,
        blocks,
        fill_in_count,
    )
    plan.validate()
    return plan
