#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.11"
# dependencies = ["wordfreq"]
# ///

"""Implementation for `mise run find-available-chords`."""

from __future__ import annotations

import argparse
import math
import re
import subprocess
import sys
from dataclasses import dataclass
from pathlib import Path

from wordfreq import word_frequency

ROOT = Path(__file__).resolve().parent.parent
if str(ROOT) not in sys.path:
    sys.path.insert(0, str(ROOT))

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
README = ROOT / "README.md"

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
    frequency_override: float | None = None
    source_label: str = "general"
    representation: str | None = None


@dataclass(frozen=True)
class MagicSlot:
    row: str
    column: str
    row_kind: str
    feel: float
    opposite_hand: bool
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
    source_label: str


@dataclass(frozen=True)
class PhysicalAction:
    kind: str
    name: str
    pos: tuple[int, int]


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Find free magic-table placements for candidate outputs."
    )
    parser.add_argument("--readme", type=Path, default=README, help="Path to README.md")
    parser.add_argument("words", nargs="*", help="Explicit words or phrases to rank into free magic slots")
    parser.add_argument(
        "--words-file",
        type=Path,
        help="Optional newline-delimited word list; blank lines and # comments are ignored.",
    )
    parser.add_argument(
        "--old-chords-file",
        type=Path,
        help="Optional file containing the old chord table or raw README excerpt.",
    )
    parser.add_argument(
        "--candidates-file",
        type=Path,
        help="Optional TSV/text file of corpus candidates (count/freq/word) to rank instead of old chords.",
    )
    parser.add_argument(
        "--source-weights",
        help="Comma-separated source weights for candidates files, e.g. general=1.0,source=1.7",
    )
    parser.add_argument(
        "--source-cap",
        help="Comma-separated source caps after ranking, e.g. source=5,chat_local=20",
    )
    parser.add_argument(
        "--old-chord-ref",
        default=DEFAULT_OLD_CHORD_REF,
        help=f"Git ref used when --old-chords-file is omitted (default: {DEFAULT_OLD_CHORD_REF})",
    )
    parser.add_argument("--limit", type=int, default=50, help="Rows to print")
    parser.add_argument(
        "--budget",
        type=int,
        default=174,
        help="Maximum number of assignments to keep after ranking (default: 174, matching old chord budget)",
    )
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
    parser.add_argument(
        "--rearrange-current",
        action="store_true",
        help="Rank current multi-character magic entries as move candidates, not just free-slot placements.",
    )
    return parser.parse_args()


def load_explicit_words(args: argparse.Namespace) -> list[str]:
    words = list(args.words)
    if args.words_file:
        for raw_line in args.words_file.read_text().splitlines():
            line = raw_line.strip()
            if not line or line.startswith("#"):
                continue
            words.append(line)
    seen: set[str] = set()
    ordered: list[str] = []
    for word in words:
        normalized = word.strip().lower()
        if not normalized or normalized in seen:
            continue
        seen.add(normalized)
        ordered.append(normalized)
    return ordered


def load_adaptive_blocks(readme: Path) -> set[tuple[str, str]]:
    blocked = set()
    in_table = False
    for line in readme.read_text().splitlines():
        if "## Adaptives" in line:
            in_table = True
            continue
        if in_table and line.startswith("##"):
            break
        if not in_table:
            continue
        match = re.match(r"\|\s*(\w)\s*\|\s*(\w+)\s*\|\s*(\w)\s*\|", line)
        if not match:
            continue
        trigger, physical, output = match.group(1), match.group(2), match.group(3)
        if len(physical) == 1 and physical != output:
            blocked.add((trigger, physical))
    return blocked


def output_difficulty(
    output: str,
    adaptives: dict[tuple[str, str], str],
    blocked_pairs: set[tuple[str, str]],
    magic_rows: dict[str, dict[str, str]],
) -> float:
    word = output.lower()
    keys = [c for c in actual_keystrokes(word, adaptives) if c in LAYOUT]
    if len(keys) < 2:
        return 1.0
    scores = [min(feel_score(a, b), 5) for a, b in zip(keys, keys[1:])]
    output_chars = [c for c in word if c in LAYOUT]
    blocked_count = 0
    for index, (a, b) in enumerate(zip(output_chars, output_chars[1:])):
        if (a, b) in blocked_pairs:
            scores[index] = max(scores[index], 5)
            blocked_count += 1
    baseline = sum(scores) / len(scores)
    bad_transition_count = sum(1 for score in scores if score >= 3.0)
    return baseline * difficulty_multiplier(
        word,
        adaptives,
        magic_rows,
        blocked_count=blocked_count,
        bad_transition_count=bad_transition_count,
    )


def output_frequency(output: str) -> float:
    words = re.findall(r"[a-z']+", output.lower())
    if not words:
        return 1e-9
    return max(max(word_frequency(word, "en"), 1e-9) for word in words)


def candidate_frequency(entry: ChordEntry) -> float:
    return entry.frequency_override if entry.frequency_override is not None else output_frequency(entry.output)


def parse_source_weights(raw: str | None) -> dict[str, float]:
    if not raw:
        return {}
    weights = {}
    for part in raw.split(","):
        if not part.strip():
            continue
        name, sep, value = part.partition("=")
        if not sep:
            raise ValueError(f"invalid source weight '{part}', expected name=value")
        weights[name.strip()] = float(value.strip())
    return weights


def weighted_frequency(entry: ChordEntry, source_weights: dict[str, float]) -> float:
    base = candidate_frequency(entry)
    weighted = base * source_weights.get(entry.source_label, 1.0)
    return math.log1p(weighted * 1_000_000)


def is_word_output(output: str) -> bool:
    words = re.findall(r"[a-z']+", output.lower())
    return bool(words)


def parse_source_caps(raw: str | None) -> dict[str, int]:
    if not raw:
        return {}
    caps = {}
    for part in raw.split(","):
        if not part.strip():
            continue
        name, sep, value = part.partition("=")
        if not sep:
            raise ValueError(f"invalid source cap '{part}', expected name=value")
        caps[name.strip()] = int(value.strip())
    return caps


def assignment_value(
    entry: ChordEntry,
    slot: MagicSlot,
    adaptives: dict[tuple[str, str], str],
    blocked_pairs: set[tuple[str, str]],
    magic_rows: dict[str, dict[str, str]],
    source_weights: dict[str, float],
) -> tuple[float, float, float, int]:
    saved = len(entry.output) - 2
    if saved < 1:
        return 0.0, 0.0, 0.0, saved
    freq = weighted_frequency(entry, source_weights)
    difficulty = output_difficulty(entry.output, adaptives, blocked_pairs, magic_rows)
    hand_bonus = 1.35 if is_word_output(entry.output) and slot.opposite_hand else 0.75 if is_word_output(entry.output) else 1.0
    value = saved ** 2 * freq * difficulty * hand_bonus / (slot.feel + 1)
    return value, freq, difficulty, saved


def load_old_chords(args: argparse.Namespace) -> list[ChordEntry]:
    explicit_words = load_explicit_words(args)
    if explicit_words:
        return [
            ChordEntry(
                chord="input",
                output=word,
                status="",
                source_label="input",
            )
            for word in explicit_words
        ]
    if args.rearrange_current:
        return load_current_magic_words(args.readme)
    if args.candidates_file:
        return parse_candidates_file(args.candidates_file)
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
                    source_label="general",
                )
            )
    return rows


def parse_candidates_file(path: Path) -> list[ChordEntry]:
    rows: list[ChordEntry] = []
    for raw_line in path.read_text().splitlines():
        line = raw_line.strip()
        if not line or line.startswith("#"):
            continue

        parts = line.split("\t")
        if len(parts) >= 4:
            count_text, freq_text, source_label, output = parts[0], parts[1], parts[2], "\t".join(parts[3:])
            try:
                frequency = float(freq_text)
            except ValueError:
                continue
        elif len(parts) >= 3:
            count_text, freq_text, output = parts[0], parts[1], "\t".join(parts[2:])
            source_label = "source"
            try:
                frequency = float(freq_text)
            except ValueError:
                continue
        else:
            match = re.match(r"(\d+)\s+([0-9.]+)\s+(.+)", line)
            if not match:
                continue
            count_text, freq_text, output = match.group(1), match.group(2), match.group(3)
            frequency = float(freq_text)
            source_label = "source"

        rows.append(
            ChordEntry(
                chord=f"src:{count_text}",
                output=output.strip(),
                status="",
                frequency_override=frequency,
                source_label=source_label.strip(),
            )
        )
    return rows


def load_current_magic_words(readme: Path) -> list[ChordEntry]:
    header, rows, _ = parse_magic_table(readme)
    entries: list[ChordEntry] = []
    for row_name, (_, cells) in rows.items():
        for index, cell in enumerate(cells):
            if not cell or cell.startswith("["):
                continue
            raw = cell[1:-1] if cell.startswith('"') and cell.endswith('"') else cell
            if len(raw) <= 2:
                continue
            entries.append(
                ChordEntry(
                    chord=f"{row_name}:{header[index]}",
                    output=raw.lower(),
                    status="current",
                    source_label="current",
                    representation=cell,
                )
            )
    return entries


def magic_table_bounds(lines: list[str]) -> tuple[int, int]:
    start = next(
        i
        for i, line in enumerate(lines)
        if line.startswith("|") and split_table_line(line) and split_table_line(line)[0] == "Magic"
    )
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


def magic_rows_map(
    header: list[str],
    rows: dict[str, tuple[int, list[str]]],
) -> dict[str, dict[str, str]]:
    return {
        row: {column: cells[index] for index, column in enumerate(header) if cells[index]}
        for row, (_, cells) in rows.items()
    }


def format_magic_row(row_name: str, cells: list[str]) -> str:
    def fmt_row_label(label: str) -> str:
        return f" {label:^5} "

    def fmt_cell(cell: str) -> str:
        if not cell:
            return " " * 9
        if len(cell) <= 7:
            return f" {cell:^7} "
        return f" {cell} "

    return "|" + "|".join([fmt_row_label(row_name)] + [fmt_cell(cell) for cell in cells]) + "|"


def literal_cell(output: str) -> str:
    bare_word = len(output) > 1 and " " not in output and not output.startswith("[")
    if bare_word and re.fullmatch(r"[A-Za-z0-9'@._/-]+", output):
        return output
    return f'"{output} "'


def magic_feel_score(prev: str, column: str, starts_with_prev: bool) -> tuple[float, bool]:
    prev_pos = PRECEDING_POSITIONS.get(prev)
    magic_pos = MAGIC_POSITIONS[column]
    opposite_hand = False
    if prev_pos is None:
        score = 1.5
    else:
        score = float(feel_score_positions(prev_pos, magic_pos))
        prev_left = prev_pos[0] < 4
        magic_left = magic_pos[0] < 4
        opposite_hand = prev_left != magic_left
        if prev_left == magic_left:
            score += 0.8
        else:
            score -= 0.3
    if column in {"magic_c", "magic_f"}:
        score += 1.2
    if not starts_with_prev:
        score += 0.5
    return max(0.0, score), opposite_hand


def candidate_slots(
    output: str,
    representation: str,
    header: list[str],
    rows: dict[str, tuple[int, list[str]]],
    *,
    letters_only: bool,
    allow_occupied: bool = False,
    movable_slots: set[tuple[str, str]] | None = None,
) -> list[MagicSlot]:
    allowed_rows = LETTER_ROWS if letters_only else LETTER_ROWS + NON_LETTER_ROWS
    slots: list[MagicSlot] = []
    for row in allowed_rows:
        current = rows.get(row)
        current_cells = current[1] if current else [""] * len(header)
        for index, column in enumerate(header):
            slot_key = (row, column)
            if current_cells[index] and not allow_occupied:
                continue
            if current_cells[index] and allow_occupied and movable_slots is not None and slot_key not in movable_slots:
                continue
            starts_with_row = len(row) == 1 and output.lower().startswith(row)
            feel, opposite_hand = magic_feel_score(row, column, starts_with_row)
            slots.append(
                MagicSlot(
                    row=row,
                    column=column,
                    row_kind="letter" if len(row) == 1 and row.isalpha() else "non-letter",
                    feel=feel,
                    opposite_hand=opposite_hand,
                    starts_with_row=starts_with_row,
                    representation=representation,
                )
            )
    return slots


def physical_key_for_output(prev_output: str | None, current_output: str, adaptives: dict[tuple[str, str], str]) -> str | None:
    key = adaptives.get((prev_output, current_output), current_output) if prev_output else current_output
    return key if key in LAYOUT else None


def action_transition_cost(previous: PhysicalAction, current: PhysicalAction) -> float:
    if previous.kind == "key" and current.kind == "key":
        return float(min(feel_score(previous.name, current.name), 5))
    cost = float(feel_score_positions(previous.pos, current.pos))
    same_hand = (previous.pos[0] < 4) == (current.pos[0] < 4)
    if previous.kind == "key" and current.kind == "magic" and same_hand:
        cost += 2.0
    if previous.kind == "magic" and current.kind == "key" and same_hand:
        cost += 1.0
    return cost


def magic_emitted_suffix(prev_output: str, cell: str) -> str | None:
    if not cell or cell.startswith("["):
        return None
    if len(cell) == 1:
        return cell
    raw = cell[1:-1] if cell.startswith('"') and cell.endswith('"') else cell
    if raw.startswith(prev_output):
        return raw[len(prev_output):]
    return None


def plain_segment_cost(
    prev_output: str,
    emitted: str,
    next_output: str | None,
    adaptives: dict[tuple[str, str], str],
) -> float:
    previous_action = PhysicalAction("key", physical_key_for_output(None, prev_output, adaptives) or prev_output, LAYOUT[physical_key_for_output(None, prev_output, adaptives) or prev_output])
    current_prev_output = prev_output
    cost = 0.0
    for char in emitted:
        key = physical_key_for_output(current_prev_output, char, adaptives)
        if key is None:
            return 0.0
        action = PhysicalAction("key", key, LAYOUT[key])
        cost += action_transition_cost(previous_action, action)
        previous_action = action
        current_prev_output = char
    if next_output:
        key = physical_key_for_output(current_prev_output, next_output, adaptives)
        if key is not None:
            cost += action_transition_cost(previous_action, PhysicalAction("key", key, LAYOUT[key]))
    return cost


def magic_segment_penalty(word: str, index: int, adaptives: dict[tuple[str, str], str], magic_rows: dict[str, dict[str, str]]) -> float:
    prev_output = word[index - 1]
    prev_key = physical_key_for_output(word[index - 2] if index > 1 else None, prev_output, adaptives)
    if prev_key is None:
        return 0.0
    best_extra = 0.0
    for column, cell in magic_rows.get(prev_output, {}).items():
        emitted = magic_emitted_suffix(prev_output, cell)
        if not emitted or not word.startswith(emitted, index):
            continue
        next_index = index + len(emitted)
        next_output = word[next_index] if next_index < len(word) else None
        plain_cost = plain_segment_cost(prev_output, emitted, next_output, adaptives)
        magic_cost = action_transition_cost(
            PhysicalAction("key", prev_key, LAYOUT[prev_key]),
            PhysicalAction("magic", column, MAGIC_POSITIONS[column]),
        )
        if next_output:
            next_key = physical_key_for_output(emitted[-1], next_output, adaptives)
            if next_key is not None:
                magic_cost += action_transition_cost(
                    PhysicalAction("magic", column, MAGIC_POSITIONS[column]),
                    PhysicalAction("key", next_key, LAYOUT[next_key]),
                )
        best_extra = max(best_extra, max(0.0, magic_cost - plain_cost))
    return best_extra


def magic_penalty_multiplier(word: str, adaptives: dict[tuple[str, str], str], magic_rows: dict[str, dict[str, str]]) -> float:
    extras = [magic_segment_penalty(word, index, adaptives, magic_rows) for index in range(1, len(word))]
    total_extra = sum(extra for extra in extras if extra > 0)
    transitions = max(1, len(word) - 1)
    return 1.0 + (total_extra / transitions)


def difficulty_multiplier(
    word: str,
    adaptives: dict[tuple[str, str], str],
    magic_rows: dict[str, dict[str, str]],
    *,
    blocked_count: int,
    bad_transition_count: int,
) -> float:
    magic_multiplier = magic_penalty_multiplier(word, adaptives, magic_rows)
    spread = 1.0 + (magic_multiplier - 1.0) * 1.2
    if blocked_count:
        spread *= 1.0 + (0.8 * blocked_count)
    if bad_transition_count:
        spread *= 1.0 + (0.2 * bad_transition_count)
    return min(spread, 6.0)


def greedy_assign(
    old_chords: list[ChordEntry],
    header: list[str],
    rows: dict[str, tuple[int, list[str]]],
    adaptives: dict[tuple[str, str], str],
    blocked_pairs: set[tuple[str, str]],
    magic_rows: dict[str, dict[str, str]],
    source_weights: dict[str, float],
    source_caps: dict[str, int],
    *,
    letters_only: bool,
    budget: int,
    allow_occupied: bool = False,
    distinct_by_output: bool = True,
) -> list[Assignment]:
    movable_slots = None
    if allow_occupied:
        movable_slots = set()
        for entry in old_chords:
            if ":" not in entry.chord:
                continue
            row_name, column = entry.chord.split(":", 1)
            movable_slots.add((row_name, column))

    candidates: list[Assignment] = []
    for entry in old_chords:
        representation = entry.representation or literal_cell(entry.output)
        for slot in candidate_slots(
            entry.output,
            representation,
            header,
            rows,
            letters_only=letters_only,
            allow_occupied=allow_occupied,
            movable_slots=movable_slots,
        ):
            value, freq, difficulty, saved = assignment_value(
                entry, slot, adaptives, blocked_pairs, magic_rows, source_weights
            )
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
                    source_label=entry.source_label,
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

    used_entries: set[str] = set()
    used_slots: set[tuple[str, str]] = set()
    used_source_counts: dict[str, int] = {}
    assignments: list[Assignment] = []
    for candidate in candidates:
        slot_key = (candidate.slot.row, candidate.slot.column)
        entry_key = candidate.output if distinct_by_output else candidate.source_chord
        if entry_key in used_entries or slot_key in used_slots:
            continue
        candidate_sources = candidate.source_label.split("+")
        if any(
            used_source_counts.get(source, 0) >= source_caps[source]
            for source in candidate_sources
            if source in source_caps
        ):
            continue
        used_entries.add(entry_key)
        used_slots.add(slot_key)
        for source in candidate_sources:
            used_source_counts[source] = used_source_counts.get(source, 0) + 1
        assignments.append(candidate)
        if len(assignments) >= budget:
            break
    return assignments


def apply_assignments(
    readme: Path,
    header: list[str],
    count: int,
    assignments: list[Assignment],
    *,
    rearrange_current: bool = False,
    current_entries: list[ChordEntry] | None = None,
) -> None:
    _, rows, lines = parse_magic_table(readme)
    top = assignments[:count]

    if rearrange_current:
        assigned_sources = {assignment.source_chord for assignment in top}
        unassigned_entries: list[ChordEntry] = []
        for entry in current_entries or []:
            if ":" not in entry.chord:
                continue
            if entry.chord not in assigned_sources:
                unassigned_entries.append(entry)
            row_name, column = entry.chord.split(":", 1)
            row_index, cells = rows[row_name]
            column_index = header.index(column)
            cells[column_index] = ""
            lines[row_index] = format_magic_row(row_name, cells)
            _, rows, lines = parse_magic_table_from_lines(lines)
    else:
        unassigned_entries = []

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

    for entry in unassigned_entries:
        if ":" not in entry.chord or entry.representation is None:
            continue
        row_name, column = entry.chord.split(":", 1)
        row_index, cells = rows[row_name]
        column_index = header.index(column)
        if cells[column_index]:
            raise ValueError(f"Unassigned slot already occupied during restore: {row_name}/{column}")
        cells[column_index] = entry.representation
        lines[row_index] = format_magic_row(row_name, cells)
        _, rows, lines = parse_magic_table_from_lines(lines)

    readme.write_text("\n".join(lines) + "\n")


def print_summary(
    candidates: list[ChordEntry],
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
        f"candidates: {len(candidates)}  assigned: {len(assignments)}  "
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
        hand = "opp" if assignment.slot.opposite_hand else "same"
        print(
            f"  {assignment.output:<24} <- {assignment.source_chord:<3}  "
            f"{assignment.slot.row:>4} {assignment.slot.column:<7} "
            f"feel={assignment.slot.feel:>4.1f} {hand:<4} {starts:<5} "
            f"saved={assignment.saved:<2} diff={assignment.difficulty:>4.2f} "
            f"freq={assignment.frequency:.6f} value={assignment.value:.6f}"
        )


def current_slot_from_source(
    source: str,
    header: list[str],
    rows: dict[str, tuple[int, list[str]]],
    output: str,
) -> MagicSlot | None:
    if ":" not in source:
        return None
    row, column = source.split(":", 1)
    current = rows.get(row)
    if current is None or column not in header:
        return None
    starts_with_row = len(row) == 1 and output.lower().startswith(row)
    feel, opposite_hand = magic_feel_score(row, column, starts_with_row)
    return MagicSlot(
        row=row,
        column=column,
        row_kind="letter" if len(row) == 1 and row.isalpha() else "non-letter",
        feel=feel,
        opposite_hand=opposite_hand,
        starts_with_row=starts_with_row,
        representation=literal_cell(output),
    )


def print_rearrangements(
    assignments: list[Assignment],
    header: list[str],
    rows: dict[str, tuple[int, list[str]]],
    adaptives: dict[tuple[str, str], str],
    blocked_pairs: set[tuple[str, str]],
    magic_rows: dict[str, dict[str, str]],
    source_weights: dict[str, float],
    *,
    limit: int,
) -> None:
    moves = []
    for assignment in assignments:
        source = assignment.source_chord
        current_slot = current_slot_from_source(source, header, rows, assignment.output)
        if current_slot is None:
            continue
        current_row, current_column = current_slot.row, current_slot.column
        if (current_row, current_column) == (assignment.slot.row, assignment.slot.column):
            continue
        current_value, _, _, _ = assignment_value(
            ChordEntry(
                chord=assignment.source_chord,
                output=assignment.output,
                status="current",
                source_label=assignment.source_label,
            ),
            current_slot,
            adaptives,
            blocked_pairs,
            magic_rows,
            source_weights,
        )
        if current_slot.opposite_hand:
            continue
        if not assignment.slot.opposite_hand:
            continue
        if assignment.value <= current_value * 1.05:
            continue
        moves.append((current_row, current_column, assignment))
    print()
    print("suggested rearrangements:")
    if not moves:
        print("  <none>")
        return
    for current_row, current_column, assignment in moves[:limit]:
        hand = "opp" if assignment.slot.opposite_hand else "same"
        print(
            f"  {assignment.output:<24} {current_row:>4} {current_column:<7} -> "
            f"{assignment.slot.row:>4} {assignment.slot.column:<7} "
            f"feel={assignment.slot.feel:>4.1f} {hand:<4} value={assignment.value:.6f}"
        )


def main() -> None:
    args = parse_args()
    header, rows, _ = parse_magic_table(args.readme)
    magic_rows = magic_rows_map(header, rows)
    adaptives = load_adaptives(args.readme)
    blocked_pairs = load_adaptive_blocks(args.readme)
    old_chords = load_old_chords(args)
    source_weights = parse_source_weights(args.source_weights)
    source_caps = parse_source_caps(args.source_cap)
    assignments = greedy_assign(
        old_chords,
        header,
        rows,
        adaptives,
        blocked_pairs,
        magic_rows,
        source_weights,
        source_caps,
        letters_only=args.letters_only,
        budget=args.budget,
        allow_occupied=args.rearrange_current,
        distinct_by_output=not args.rearrange_current,
    )

    print_summary(
        old_chords,
        assignments,
        header,
        rows,
        limit=args.limit,
        include_filled=args.include_filled,
    )
    if args.rearrange_current:
        print_rearrangements(
            assignments,
            header,
            rows,
            adaptives,
            blocked_pairs,
            magic_rows,
            source_weights,
            limit=args.limit,
        )

    if args.apply:
        apply_assignments(
            args.readme,
            header,
            args.apply,
            assignments,
            rearrange_current=args.rearrange_current,
            current_entries=old_chords if args.rearrange_current else None,
        )
        print()
        print(f"applied top {args.apply} assignments to {args.readme}")


if __name__ == "__main__":
    main()
