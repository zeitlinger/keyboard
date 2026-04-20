#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.11"
# dependencies = ["wordfreq"]
# ///

from __future__ import annotations

import argparse
import re
import subprocess
from dataclasses import dataclass
from pathlib import Path

from wordfreq import word_frequency

from feel import (
    LAYOUT,
    MAGIC_POSITIONS,
    actual_keystrokes,
    feel_score,
    feel_score_positions,
    load_adaptives,
)


DEFAULT_OLD_CHORD_REF = "21f2800^"
LETTER_ROWS = [chr(code) for code in range(ord("a"), ord("z") + 1)]
NON_LETTER_ROWS = ["spc", "tab", "↩️️", "~", ",", ".", "-", "=", "!"]
README = Path(__file__).parent / "README.md"

# Approximate physical positions for keys that can precede a magic press.
PRECEDING_POSITIONS = {
    **LAYOUT,
    "q": (5, 0),
    "spc": (4, 5),
    "tab": (7, 4),
    "↩️️": (4, 4),
    "~": (4, 1),
    ",": (5, 3),
    ".": (6, 3),
    "-": (3, 1),
    "=": (7, 2),
    "!": (5, 2),
}


@dataclass(frozen=True)
class ChordEntry:
    chord: str
    output: str
    status: str


@dataclass(frozen=True)
class MagicSlot:
    row: str
    column: str
    row_kind: str
    feel: float
    starts_with_row: bool
    representation: str


@dataclass(frozen=True)
class Assignment:
    output: str
    slot: MagicSlot
    value: float
    frequency: float
    difficulty: float
    saved: int
    source_chord: str


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Greedy assignment of old chord outputs into free magic-table slots."
    )
    parser.add_argument("--readme", type=Path, default=README, help="Path to README.md")
    parser.add_argument(
        "--old-chords-file",
        type=Path,
        help="Optional file containing the old chord table or raw README excerpt.",
    )
    parser.add_argument(
        "--old-chord-ref",
        default=DEFAULT_OLD_CHORD_REF,
        help=f"Git ref used when --old-chords-file is omitted (default: {DEFAULT_OLD_CHORD_REF})",
    )
    parser.add_argument("--limit", type=int, default=50, help="Rows to print")
    parser.add_argument(
        "--apply",
        type=int,
        metavar="N",
        help="Write the top N greedy assignments into README.md",
    )
    parser.add_argument(
        "--letters-only",
        action="store_true",
        help="Restrict candidate slots to letter rows only",
    )
    parser.add_argument(
        "--include-filled",
        action="store_true",
        help="Print occupied slots in the summary",
    )
    return parser.parse_args()


def output_difficulty(output: str, adaptives: dict[tuple[str, str], str]) -> float:
    keys = [c for c in actual_keystrokes(output.lower(), adaptives) if c in LAYOUT]
    if len(keys) < 2:
        return 1.0
    scores = [min(feel_score(a, b), 5) for a, b in zip(keys, keys[1:])]
    return sum(scores) / len(scores)


def output_frequency(output: str) -> float:
    words = re.findall(r"[a-z']+", output.lower())
    if not words:
        return 1e-9
    return max(word_frequency(word, "en") for word in words)


def assignment_value(
    output: str,
    slot: MagicSlot,
    adaptives: dict[tuple[str, str], str],
) -> tuple[float, float, float, int]:
    saved = len(output) - 2
    if saved < 1:
        return 0.0, 0.0, 0.0, saved
    freq = output_frequency(output)
    difficulty = output_difficulty(output, adaptives)
    value = saved ** 2 * freq * difficulty / (slot.feel + 1)
    return value, freq, difficulty, saved


def load_old_chords(args: argparse.Namespace) -> list[ChordEntry]:
    if args.old_chords_file:
        text = args.old_chords_file.read_text()
    else:
        text = subprocess.check_output(
            ["git", "show", f"{args.old_chord_ref}:README.md"],
            text=True,
            cwd=Path(__file__).parent,
        )
    return parse_chord_table(text)


def parse_chord_table(text: str) -> list[ChordEntry]:
    rows: list[ChordEntry] = []
    in_table = False
    for line in text.splitlines():
        if "## Chord Table" in line:
            in_table = True
            continue
        if in_table and line.startswith("##"):
            break
        if not in_table:
            continue
        match = re.match(
            r'\|\s*([a-z,./]+)\s*\|\s*"([^"]+)"\s*\|\s*(yes|plan|done)?\s*\|',
            line,
        )
        if match:
            rows.append(
                ChordEntry(
                    chord=match.group(1),
                    output=match.group(2),
                    status=match.group(3) or "",
                )
            )
    return rows


def magic_table_bounds(lines: list[str]) -> tuple[int, int]:
    start = next(i for i, line in enumerate(lines) if line.startswith("| Magic |"))
    end = start + 2
    while end < len(lines) and lines[end].startswith("|"):
        end += 1
    return start, end


def split_table_line(line: str) -> list[str]:
    return [cell.strip() for cell in line.strip().strip("|").split("|")]


def parse_magic_table_from_lines(
    lines: list[str],
) -> tuple[list[str], dict[str, tuple[int, list[str]]], list[str]]:
    start, end = magic_table_bounds(lines)
    header = split_table_line(lines[start])[1:]
    rows: dict[str, tuple[int, list[str]]] = {}
    for index in range(start + 2, end):
        cells = split_table_line(lines[index])
        rows[cells[0]] = (index, cells[1:])
    return header, rows, lines


def parse_magic_table(readme: Path) -> tuple[list[str], dict[str, tuple[int, list[str]]], list[str]]:
    return parse_magic_table_from_lines(readme.read_text().splitlines())


def format_magic_row(row_name: str, cells: list[str]) -> str:
    padded = [f"{row_name:^5}"] + [f"{cell:^9}" if cell else " " * 9 for cell in cells]
    return "| " + " | ".join(padded) + " |"


def literal_cell(output: str) -> str:
    bare_word = len(output) > 1 and " " not in output and not output.startswith("[")
    if bare_word and re.fullmatch(r"[A-Za-z0-9'@._/-]+", output):
        return output
    return f'"{output} "'


def magic_feel_score(prev: str, column: str, starts_with_prev: bool) -> float:
    prev_pos = PRECEDING_POSITIONS.get(prev)
    magic_pos = MAGIC_POSITIONS[column]
    if prev_pos is None:
        score = 1.5
    else:
        score = float(feel_score_positions(prev_pos, magic_pos))
    if not starts_with_prev:
        score += 0.5
    return score


def candidate_slots(
    output: str,
    header: list[str],
    rows: dict[str, tuple[int, list[str]]],
    *,
    letters_only: bool,
) -> list[MagicSlot]:
    allowed_rows = LETTER_ROWS if letters_only else LETTER_ROWS + NON_LETTER_ROWS
    slots: list[MagicSlot] = []
    for row in allowed_rows:
        current = rows.get(row)
        current_cells = current[1] if current else [""] * len(header)
        for index, column in enumerate(header):
            if current_cells[index]:
                continue
            starts_with_row = len(row) == 1 and output.lower().startswith(row)
            slots.append(
                MagicSlot(
                    row=row,
                    column=column,
                    row_kind="letter" if len(row) == 1 and row.isalpha() else "non-letter",
                    feel=magic_feel_score(row, column, starts_with_row),
                    starts_with_row=starts_with_row,
                    representation=literal_cell(output),
                )
            )
    return slots


def greedy_assign(
    old_chords: list[ChordEntry],
    header: list[str],
    rows: dict[str, tuple[int, list[str]]],
    adaptives: dict[tuple[str, str], str],
    *,
    letters_only: bool,
) -> list[Assignment]:
    candidates: list[Assignment] = []
    for entry in old_chords:
        for slot in candidate_slots(entry.output, header, rows, letters_only=letters_only):
            value, freq, difficulty, saved = assignment_value(entry.output, slot, adaptives)
            if value <= 0:
                continue
            candidates.append(
                Assignment(
                    output=entry.output,
                    slot=slot,
                    value=value,
                    frequency=freq,
                    difficulty=difficulty,
                    saved=saved,
                    source_chord=entry.chord,
                )
            )

    candidates.sort(
        key=lambda item: (
            -item.value,
            item.slot.feel,
            item.slot.row_kind != "letter",
            item.slot.row,
            item.slot.column,
        )
    )

    used_words: set[str] = set()
    used_slots: set[tuple[str, str]] = set()
    assignments: list[Assignment] = []
    for candidate in candidates:
        slot_key = (candidate.slot.row, candidate.slot.column)
        if candidate.output in used_words or slot_key in used_slots:
            continue
        used_words.add(candidate.output)
        used_slots.add(slot_key)
        assignments.append(candidate)
    return assignments


def apply_assignments(readme: Path, header: list[str], count: int, assignments: list[Assignment]) -> None:
    _, rows, lines = parse_magic_table(readme)
    top = assignments[:count]

    for assignment in top:
        if assignment.slot.row not in rows:
            insert_at = next(
                (
                    rows[row][0] + 1
                    for row in reversed(LETTER_ROWS)
                    if row in rows and LETTER_ROWS.index(row) < LETTER_ROWS.index(assignment.slot.row)
                ),
                rows[next(row for row in NON_LETTER_ROWS if row in rows)][0],
            )
            lines.insert(insert_at, format_magic_row(assignment.slot.row, [""] * len(header)))
            _, rows, lines = parse_magic_table_from_lines(lines)

        row_index, cells = rows[assignment.slot.row]
        column_index = header.index(assignment.slot.column)
        if cells[column_index]:
            raise ValueError(
                f"Slot already occupied during apply: {assignment.slot.row}/{assignment.slot.column}"
            )
        cells[column_index] = assignment.slot.representation
        lines[row_index] = format_magic_row(assignment.slot.row, cells)
        _, rows, lines = parse_magic_table_from_lines(lines)

    readme.write_text("\n".join(lines) + "\n")


def print_summary(
    old_chords: list[ChordEntry],
    assignments: list[Assignment],
    header: list[str],
    rows: dict[str, tuple[int, list[str]]],
    *,
    limit: int,
    include_filled: bool,
) -> None:
    free_slots = sum(
        1
        for row in LETTER_ROWS + NON_LETTER_ROWS
        for index in range(len(header))
        if not (rows.get(row, (-1, [""] * len(header)))[1][index] if row in rows else "")
    )
    occupied_slots = sum(1 for _, cells in rows.values() for cell in cells if cell)
    print(
        f"old chords: {len(old_chords)}  assigned: {len(assignments)}  "
        f"free slots considered: {free_slots}  occupied: {occupied_slots}"
    )
    if include_filled:
        print()
        print("occupied slots:")
        for row_name, (_, cells) in rows.items():
            for column, value in zip(header, cells):
                if value:
                    print(f"  {row_name:>4} {column}: {value}")
        print()

    print("top assignments:")
    for assignment in assignments[:limit]:
        starts = "strip" if assignment.slot.starts_with_row else "bs"
        print(
            f"  {assignment.output:<24} <- {assignment.source_chord:<3}  "
            f"{assignment.slot.row:>4} {assignment.slot.column:<7} "
            f"feel={assignment.slot.feel:>4.1f} {starts:<5} "
            f"saved={assignment.saved:<2} diff={assignment.difficulty:>4.2f} "
            f"freq={assignment.frequency:.6f} value={assignment.value:.6f}"
        )


def main() -> None:
    args = parse_args()
    header, rows, _ = parse_magic_table(args.readme)
    adaptives = load_adaptives(args.readme)
    old_chords = load_old_chords(args)
    assignments = greedy_assign(
        old_chords,
        header,
        rows,
        adaptives,
        letters_only=args.letters_only,
    )

    print_summary(
        old_chords,
        assignments,
        header,
        rows,
        limit=args.limit,
        include_filled=args.include_filled,
    )

    if args.apply:
        apply_assignments(args.readme, header, args.apply, assignments)
        print()
        print(f"applied top {args.apply} assignments to {args.readme}")


if __name__ == "__main__":
    main()
