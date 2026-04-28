#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.11"
# ///

"""Implementation for `mise run merge-word-lists`.

This module lives under `scripts/`; use the `mise` task as the public entrypoint.
"""

from __future__ import annotations

import argparse
from collections import defaultdict
from dataclasses import dataclass
from pathlib import Path


@dataclass(frozen=True)
class Row:
    count: int
    freq: float
    source: str
    word: str


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Merge multiple word-list TSVs into one candidate file for find_available_chords.py."
    )
    parser.add_argument(
        "inputs",
        nargs="+",
        type=Path,
        help="Input TSVs with columns count, freq, source, word",
    )
    parser.add_argument(
        "--output", type=Path, default=Path("merged_words.tsv"), help="Output TSV path"
    )
    parser.add_argument(
        "--limit", type=int, default=1000, help="Maximum merged rows to write"
    )
    parser.add_argument(
        "--source-weight",
        action="append",
        default=[],
        help="Optional source weight note to carry in the output summary, e.g. general=1.0",
    )
    return parser.parse_args()


def parse_rows(path: Path) -> list[Row]:
    rows = []
    for raw_line in path.read_text().splitlines():
        line = raw_line.strip()
        if not line or line.startswith("#"):
            continue
        parts = line.split("\t")
        if len(parts) < 4:
            continue
        count, freq, source, word = parts[0], parts[1], parts[2], "\t".join(parts[3:])
        rows.append(Row(count=int(count), freq=float(freq), source=source, word=word))
    return rows


def merge_rows(inputs: list[Path]) -> list[Row]:
    merged: dict[str, dict[str, float | int | str]] = defaultdict(
        lambda: {"count": 0, "freq": 0.0, "source": ""}
    )
    for path in inputs:
        for row in parse_rows(path):
            current = merged[row.word]
            current["count"] += row.count
            current["freq"] += row.freq
            sources = set(filter(None, current["source"].split("+")))
            sources.add(row.source)
            current["source"] = "+".join(sorted(sources))
    return [
        Row(
            count=int(values["count"]),
            freq=float(values["freq"]),
            source=str(values["source"]),
            word=word,
        )
        for word, values in merged.items()
    ]


def write_rows(path: Path, rows: list[Row]) -> None:
    lines = ["# count\tfreq\tsource\tword"]
    lines.extend(
        f"{row.count}\t{row.freq:.12f}\t{row.source}\t{row.word}" for row in rows
    )
    path.write_text("\n".join(lines) + "\n")


def main() -> None:
    args = parse_args()
    rows = merge_rows(args.inputs)
    rows.sort(key=lambda row: (-row.freq, -row.count, row.word))
    rows = rows[: args.limit]
    write_rows(args.output, rows)
    print(f"wrote {len(rows)} rows to {args.output}")
    if args.source_weight:
        print("suggested source weights:")
        for item in args.source_weight:
            print(f"  {item}")
    print("top rows:")
    for row in rows[:20]:
        print(f"  {row.count:>8}  {row.freq:.8f}  {row.source:<16} {row.word}")


if __name__ == "__main__":
    main()
