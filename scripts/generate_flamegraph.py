#!/usr/bin/env python3
"""Convert Callgrind profile files into interactive SVG Flamegraphs.

Parses Callgrind .out files, reconstructs function call stacks, folds
callstacks into instruction counts, and renders a standalone, interactive
SVG flamegraph with hover tooltips and domain-specific color coding.
"""

from __future__ import annotations

import argparse
from dataclasses import dataclass, field
import html
from pathlib import Path
import sys


@dataclass
class CallgrindFunc:
    """Representation of a function in a Callgrind profile."""

    name: str
    self_cost: int = 0
    callees: dict[str, int] = field(default_factory=dict)
    callers: dict[str, int] = field(default_factory=dict)


def _parse_fn_name(val: str, fn_map: dict[str, str]) -> str:
    """Parse fn= or cfn= line value, handling compressed ID references."""
    val = val.strip()
    if val.startswith("("):
        closing = val.find(")")
        if closing != -1:
            fn_id = val[1:closing]
            rest = val[closing + 1 :].strip()
            if rest:
                fn_map[fn_id] = rest
                return rest
            elif fn_id in fn_map:
                return fn_map[fn_id]
            else:
                return f"fn_{fn_id}"
    return val


def parse_callgrind(content: str) -> dict[str, CallgrindFunc]:
    """Parse Callgrind file content into function call relationship dictionary."""
    funcs: dict[str, CallgrindFunc] = {}
    fn_map: dict[str, str] = {}

    current_fn: str | None = None
    current_cfn: str | None = None
    pending_calls: bool = False

    def get_func(name: str) -> CallgrindFunc:
        if name not in funcs:
            funcs[name] = CallgrindFunc(name=name)
        return funcs[name]

    for line in content.splitlines():
        line = line.strip()
        if not line or line.startswith("#"):
            continue

        if line.startswith("summary:"):
            continue

        if line.startswith("fn="):
            current_fn = _parse_fn_name(line[3:], fn_map)
            current_cfn = None
            pending_calls = False
            if current_fn:
                get_func(current_fn)
            continue

        if line.startswith("cfn="):
            current_cfn = _parse_fn_name(line[4:], fn_map)
            if current_cfn:
                get_func(current_cfn)
            continue

        if line.startswith("calls="):
            pending_calls = True
            continue

        # Skip headers / directives containing '='
        if "=" in line and not line[0].isdigit():
            continue

        # Parse cost lines
        parts = line.split()
        if parts and parts[0].isdigit():
            if len(parts) == 1:
                cost = int(parts[0])
            else:
                try:
                    cost = int(parts[1])
                except ValueError:
                    continue

            if pending_calls and current_fn and current_cfn:
                f_curr = get_func(current_fn)
                f_curr.callees[current_cfn] = f_curr.callees.get(current_cfn, 0) + cost

                f_callee = get_func(current_cfn)
                f_callee.callers[current_fn] = f_callee.callers.get(current_fn, 0) + cost

                pending_calls = False
            elif current_fn:
                f_curr = get_func(current_fn)
                f_curr.self_cost += cost

    return funcs


def extract_summary_total(content: str) -> int | None:
    """Extract total instruction count from summary: directive if present."""
    for line in content.splitlines():
        line = line.strip()
        if line.startswith("summary:"):
            parts = line.split()
            if len(parts) >= 2:
                try:
                    return int(parts[1])
                except ValueError:
                    pass
    return None


def fold_callstacks(funcs: dict[str, CallgrindFunc]) -> dict[str, float]:
    """Convert function graph into folded callstacks dictionary."""
    folded: dict[str, float] = {}

    def traverse(path: list[str], weight: float) -> None:
        curr_name = path[-1]
        fn_obj = funcs[curr_name]

        self_c = float(fn_obj.self_cost)
        callee_sum = float(sum(fn_obj.callees.values()))
        total_denom = self_c + callee_sum

        if total_denom <= 0:
            stack_str = ";".join(path)
            folded[stack_str] = folded.get(stack_str, 0.0) + weight
            return

        self_portion = weight * (self_c / total_denom)
        if self_portion > 0:
            stack_str = ";".join(path)
            folded[stack_str] = folded.get(stack_str, 0.0) + self_portion

        for callee, call_cost in fn_obj.callees.items():
            if call_cost <= 0:
                continue
            child_weight = weight * (float(call_cost) / total_denom)
            if child_weight <= 0:
                continue

            if callee in path:
                stack_str = ";".join(path)
                folded[stack_str] = folded.get(stack_str, 0.0) + child_weight
            else:
                traverse(path + [callee], child_weight)

    roots = []
    for name, fn_obj in funcs.items():
        tot_inc = sum(fn_obj.callers.values())
        tot_out = sum(fn_obj.callees.values())
        if tot_inc == 0 or tot_inc < fn_obj.self_cost + tot_out:
            roots.append((name, fn_obj))

    if not roots and funcs:
        top_fn = max(
            funcs.keys(),
            key=lambda k: funcs[k].self_cost + sum(funcs[k].callees.values()),
        )
        roots = [(top_fn, funcs[top_fn])]

    for r_name, r_obj in roots:
        tot_inc = sum(r_obj.callers.values())
        tot_out = sum(r_obj.callees.values())
        if tot_inc == 0:
            w = float(r_obj.self_cost + tot_out)
        else:
            w = float(max(0, r_obj.self_cost + tot_out - tot_inc))

        if w > 0:
            traverse([r_name], w)

    return folded


class FrameNode:
    """Tree node for hierarchy construction and SVG layout."""

    def __init__(self, name: str) -> None:
        self.name: str = name
        self.self_count: float = 0.0
        self.total_count: float = 0.0
        self.children: dict[str, FrameNode] = {}


def _pick_color(name: str) -> str:
    lname = name.lower()
    if any(k in lname for k in ("kokkos", "team", "parallel", "gpu", "cuda")):
        return "#4292c6" if "team" in lname else "#2171b5"
    if any(k in lname for k in ("rosenbrock", "ros", "kpp", "jac", "jacobian", "solver")):
        return "#ef3b2c" if "jac" in lname else "#f16913"

    h = abs(hash(name))
    hue = 15 + (h % 40)
    sat = 65 + ((h >> 3) % 25)
    light = 55 + ((h >> 6) % 20)
    return f"hsl({hue}, {sat}%, {light}%)"


def render_svg(
    folded: dict[str, float],
    out_path: Path,
    title: str = "MKPP Callgrind Flamegraph",
    total_instructions: int | None = None,
) -> None:
    """Render folded callstacks into an interactive SVG Flamegraph file."""
    root = FrameNode("root")
    for stack_str, count in folded.items():
        funcs = [f for f in stack_str.split(";") if f]
        curr = root
        curr.total_count += count
        for f in funcs:
            if f not in curr.children:
                curr.children[f] = FrameNode(f)
            curr = curr.children[f]
            curr.total_count += count
        curr.self_count += count

    if total_instructions is None or total_instructions <= 0:
        total_instructions = int(root.total_count)

    total_count_val = max(1.0, root.total_count)

    def get_max_depth(node: FrameNode, current_depth: int) -> int:
        if not node.children:
            return current_depth
        return max(get_max_depth(child, current_depth + 1) for child in node.children.values())

    max_depth = get_max_depth(root, 0)

    width = 1200
    margin_left = 10
    margin_right = 10
    usable_w = width - margin_left - margin_right
    frame_h = 18
    frame_gap = 1
    header_h = 60
    margin_bottom = 20
    height = header_h + (max_depth + 1) * (frame_h + frame_gap) + margin_bottom

    rects: list[str] = []
    frame_id = 0

    def collect_frames(node: FrameNode, depth: int, x_start: float) -> None:
        nonlocal frame_id
        sorted_children = sorted(node.children.values(), key=lambda c: c.total_count, reverse=True)

        curr_x = x_start
        for child in sorted_children:
            w = (child.total_count / total_count_val) * usable_w
            if w < 0.2:
                curr_x += w
                continue

            y = height - margin_bottom - (depth + 1) * (frame_h + frame_gap)
            pct = (child.total_count / total_count_val) * 100.0
            count_int = int(child.total_count)

            color = _pick_color(child.name)
            escaped_name = html.escape(child.name)
            tooltip = f"{escaped_name} ({count_int:,} instructions, {pct:.2f}% of total)"

            max_chars = int((w - 6) / 6.5)
            if max_chars >= 3:
                display_label = (
                    child.name[: max_chars - 2] + ".." if len(child.name) > max_chars else child.name
                )
            else:
                display_label = ""

            frame_id += 1
            clip_id = f"c{frame_id}"

            rect_svg = (
                f'  <g class="func-frame">\n'
                f"    <title>{tooltip}</title>\n"
                f'    <clipPath id="{clip_id}"><rect x="{curr_x:.2f}" y="{y:.2f}" width="{max(0, w - 1):.2f}" height="{frame_h}"/></clipPath>\n'
                f'    <rect x="{curr_x:.2f}" y="{y:.2f}" width="{max(0, w - 1):.2f}" height="{frame_h}" fill="{color}" stroke="#ffffff" stroke-width="0.5" rx="1"/>\n'
            )
            if display_label:
                rect_svg += f'    <text x="{curr_x + 3:.2f}" y="{y + 13:.2f}" font-size="11" fill="#111111" clip-path="url(#{clip_id})">{html.escape(display_label)}</text>\n'
            rect_svg += "  </g>\n"

            rects.append(rect_svg)

            collect_frames(child, depth + 1, curr_x)
            curr_x += w

    collect_frames(root, 0, margin_left)

    svg_header = f"""<?xml version="1.0" encoding="UTF-8" standalone="no"?>
<svg xmlns="http://www.w3.org/2000/svg" width="100%" height="{height}" viewBox="0 0 {width} {height}">
<style>
  .func-frame:hover rect {{
    filter: brightness(1.15);
    stroke: #000000;
    stroke-width: 1.0;
    cursor: pointer;
  }}
  text {{
    font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Helvetica, Arial, sans-serif;
    pointer-events: none;
  }}
  .title {{
    font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Helvetica, Arial, sans-serif;
    font-weight: bold;
    font-size: 16px;
    fill: #111827;
  }}
  .subtitle {{
    font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Helvetica, Arial, sans-serif;
    font-size: 12px;
    fill: #4b5563;
  }}
</style>
<rect width="{width}" height="{height}" fill="#f9fafb" />
<text x="{margin_left}" y="25" class="title">{html.escape(title)}</text>
<text x="{margin_left}" y="45" class="subtitle">Total Instructions: {int(total_instructions):,} | Samples width: 100%</text>
"""

    svg_content = svg_header + "".join(rects) + "</svg>\n"
    out_path.write_text(svg_content, encoding="utf-8")


def main() -> None:
    """CLI entrypoint for generating Flamegraph from Callgrind file."""
    parser = argparse.ArgumentParser(
        description="Convert Callgrind profile to interactive SVG Flamegraph."
    )
    parser.add_argument("--callgrind", required=True, type=Path, help="Path to Callgrind .out file")
    parser.add_argument("--out", required=True, type=Path, help="Path to output SVG flamegraph")
    parser.add_argument(
        "--title",
        type=str,
        default=None,
        help="Title for the Flamegraph SVG",
    )
    args = parser.parse_args()

    if not args.callgrind.exists():
        print(f"Error: Callgrind file not found: {args.callgrind}", file=sys.stderr)
        sys.exit(1)

    content = args.callgrind.read_text(encoding="utf-8", errors="replace")
    funcs = parse_callgrind(content)
    summary_total = extract_summary_total(content)
    folded = fold_callstacks(funcs)

    title = (
        args.title
        if args.title
        else f"MKPP Flamegraph - {args.callgrind.stem.replace('cg_', '')}"
    )

    args.out.parent.mkdir(parents=True, exist_ok=True)
    render_svg(
        folded=folded,
        out_path=args.out,
        title=title,
        total_instructions=summary_total,
    )
    print(f"Flamegraph successfully generated: {args.out}")


if __name__ == "__main__":
    main()
