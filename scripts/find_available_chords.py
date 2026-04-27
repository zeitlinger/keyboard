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
    key_press_cost,
    load_adaptives,
    plain_typing_effort,
)


DEFAULT_OLD_CHORD_REF = "21f2800^"
LETTER_ROWS = [chr(code) for code in range(ord("a"), ord("z") + 1)]
NON_LETTER_ROWS = ["spc", "tab", "↩️️", "~", ",", ".", "-", "=", "!"]
README = ROOT / "README.md"
CHORD_SYNCHRONIZATION_COST = 3.0
CHORD_MEMORY_TAX = 3.0

MAGIC_HINT_LETTERS = {
    "magic_a": ("a", "u"),
    "magic_b": ("i",),
    "magic_c": ("x", "s"),
    "magic_d": ("e", "o"),
    "magic_e": ("i", "y"),
    "magic_f": ("h",),
    "magic_g": ("x", "s"),
    "magic_h": ("a", "u"),
    "magic_i": ("e", "o"),
    "magic_j": ("i", "y"),
    "magic_k": ("h",),
}

LETTER_DISTINCTIVENESS = {
    "a": 0.15,
    "b": 0.85,
    "c": 0.55,
    "d": 0.35,
    "e": 0.05,
    "f": 0.65,
    "g": 0.95,
    "h": 0.30,
    "i": 0.10,
    "j": 1.25,
    "k": 1.10,
    "l": 0.20,
    "m": 0.60,
    "n": 0.15,
    "o": 0.10,
    "p": 0.75,
    "q": 1.30,
    "r": 0.20,
    "s": 0.15,
    "t": 0.10,
    "u": 0.15,
    "v": 1.00,
    "w": 0.60,
    "x": 1.35,
    "y": 0.55,
    "z": 1.20,
}


def mnemonic_row_bonus(output: str, row: str) -> float:
    if len(row) != 1 or not row.isalpha():
        return 1.0
    compact = "".join(char for char in output.lower() if char.isalpha())
    if not compact:
        return 1.0
    if row not in compact:
        return 0.45
    first_index = compact.index(row)
    count = compact.count(row)
    start_bonus = 0.52 if first_index == 0 else 0.0
    position_bonus = max(0.0, 0.38 - 0.06 * min(first_index, 5))
    repeat_bonus = min(0.15, 0.05 * (count - 1))
    row_score = start_bonus + position_bonus + repeat_bonus
    best_score = max(
        (0.52 if compact.index(letter) == 0 else 0.0)
        + max(0.0, 0.38 - 0.06 * min(compact.index(letter), 5))
        + min(0.15, 0.05 * (compact.count(letter) - 1))
        for letter in set(compact)
    )
    anchor_bonus = 0.42 if row_score >= best_score - 0.04 else 0.0
    return 1.0 + start_bonus + position_bonus + repeat_bonus + anchor_bonus

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
    plain_effort: float
    chord_effort: float
    effort_saved: float
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
        "--difficulty-power",
        type=float,
        default=1.35,
        help="Exponent applied to typing difficulty in the final score (default: 1.35)",
    )
    parser.add_argument(
        "--difficulty-cutoff",
        type=float,
        default=1.0,
        help="Only difficulty above this baseline is rewarded strongly (default: 1.0)",
    )
    parser.add_argument(
        "--min-difficulty",
        type=float,
        help="Exclude candidates whose raw difficulty is below this threshold.",
    )
    parser.add_argument(
        "--min-saved",
        type=int,
        default=2,
        help="Exclude candidates that save fewer than this many keystrokes (default: 2).",
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
        "--add",
        type=int,
        metavar="N",
        help=(
            "With --include-current and without replacement, pin current entries and add up to N new ones. "
            "This is shorthand for current_count + N without doing budget math manually."
        ),
    )
    parser.add_argument(
        "--apply",
        type=int,
        metavar="N",
        help="Write the top N greedy assignments into README.md",
    )
    parser.add_argument(
        "--letters-only",
        dest="letters_only",
        action="store_true",
        default=True,
        help="Restrict candidate slots to letter rows only (default)",
    )
    parser.add_argument(
        "--include-non-letters",
        dest="letters_only",
        action="store_false",
        help="Also consider non-letter trigger rows such as spc/tab/,/.",
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
    parser.add_argument(
        "--move-current-only",
        action="store_true",
        help="Reshuffle current multi-character magic entries among occupied slots without removals; may be combined with --add.",
    )
    parser.add_argument(
        "--include-current",
        action="store_true",
        help="Include current multi-character magic entries alongside the loaded candidates.",
    )
    parser.add_argument(
        "--allow-replacement",
        action="store_true",
        help="Allow candidates to use currently occupied magic slots, competing with current entries.",
    )
    parser.add_argument(
        "--new-only",
        action="store_true",
        help="Exclude candidates whose output already exists in the current Magic Keys table.",
    )
    parser.add_argument(
        "--show-delta",
        action="store_true",
        help="Show keep/move/add/remove summary relative to the current Magic Keys table.",
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
    return base * source_weights.get(entry.source_label, 1.0)


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
    difficulty_power: float,
    difficulty_cutoff: float,
    min_saved: int,
) -> tuple[float, float, float, float, float, int]:
    saved = len(entry.output) - 2
    if saved < min_saved:
        return 0.0, 0.0, 0.0, 0.0, 0.0, saved
    freq = weighted_frequency(entry, source_weights)
    plain_effort = plain_typing_effort(entry.output, adaptives, blocked_pairs=blocked_pairs)
    chord_effort = chord_typing_effort(slot)
    effort_saved = plain_effort - chord_effort
    net_gain = effort_saved - CHORD_MEMORY_TAX
    if net_gain <= 0:
        return 0.0, freq, plain_effort, chord_effort, net_gain, saved
    mnemonic_bonus = 1.0
    if is_word_output(entry.output) and len(slot.row) == 1 and slot.row.isalpha():
        compact = "".join(char for char in entry.output.lower() if char.isalpha())
        mnemonic_bonus *= mnemonic_row_bonus(entry.output, slot.row)
        hints = MAGIC_HINT_LETTERS.get(slot.column, ())
        if any(compact.endswith(hint) for hint in hints):
            mnemonic_bonus *= 1.10
        elif any(hint in compact for hint in hints):
            mnemonic_bonus *= 1.04
        if slot.column in {"magic_c", "magic_f"}:
            mnemonic_bonus = min(mnemonic_bonus, 1.12)
    value = freq * net_gain * mnemonic_bonus
    return value, freq, plain_effort, chord_effort, net_gain, saved


def load_old_chords(args: argparse.Namespace) -> list[ChordEntry]:
    explicit_words = load_explicit_words(args)
    if explicit_words:
        entries = [
            ChordEntry(
                chord="input",
                output=word,
                status="",
                source_label="input",
            )
            for word in explicit_words
        ]
    else:
        if args.rearrange_current:
            entries = load_current_magic_words(args.readme)
        elif args.candidates_file:
            entries = parse_candidates_file(args.candidates_file)
        else:
            if args.old_chords_file:
                text = args.old_chords_file.read_text()
            else:
                text = subprocess.check_output(
                    ["git", "show", f"{args.old_chord_ref}:README.md"],
                    text=True,
                    cwd=Path(__file__).parent,
                )
            entries = parse_chord_table(text)
    if args.new_only:
        existing_outputs = (
            current_magic_outputs(args.readme)
            | current_suffix_constructible_outputs(args.readme)
            | current_symbol_outputs(args.readme)
        )
        entries = [entry for entry in entries if entry.output.lower() not in existing_outputs]
    return entries


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


def corpus_frequency_overrides(entries: list[ChordEntry]) -> dict[str, tuple[float, str]]:
    overrides: dict[str, tuple[float, str]] = {}
    for entry in entries:
        if entry.frequency_override is None:
            continue
        current = overrides.get(entry.output)
        if current is None or entry.frequency_override > current[0]:
            overrides[entry.output] = (entry.frequency_override, entry.source_label)
    return overrides


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


def current_magic_outputs(readme: Path) -> set[str]:
    return {entry.output for entry in load_current_magic_words(readme)}


def current_row_counts(entries: list[ChordEntry]) -> dict[str, int]:
    counts: dict[str, int] = {}
    for entry in entries:
        if ":" not in entry.chord:
            continue
        row_name, _ = entry.chord.split(":", 1)
        counts[row_name] = counts.get(row_name, 0) + 1
    return counts


def candidate_row_targets(entries: list[ChordEntry], total_assignments: int) -> dict[str, int]:
    support_counts: dict[str, int] = {}
    for entry in entries:
        letters = {char for char in entry.output.lower() if char in LETTER_ROWS}
        for letter in letters:
            support_counts[letter] = support_counts.get(letter, 0) + 1

    if not support_counts or total_assignments <= 0:
        return {}

    total_support = sum(support_counts.values())
    raw_targets = {
        row: support_counts[row] * total_assignments / total_support
        for row in support_counts
    }
    targets = {row: int(raw_targets[row]) for row in raw_targets}
    assigned = sum(targets.values())

    ranked_remainders = sorted(
        ((raw_targets[row] - targets[row], row) for row in raw_targets),
        reverse=True,
    )
    for _, row in ranked_remainders:
        if assigned >= total_assignments:
            break
        targets[row] += 1
        assigned += 1

    return {row: count for row, count in targets.items() if count > 0}


def construct_magic_suffix_output(base: str, suffix: str) -> str | None:
    base = base.strip().lower()
    suffix = suffix.strip().lower()
    if not base or not suffix:
        return None
    if suffix == "ed":
        if base.endswith("e"):
            return f"{base[:-1]}ed"
        return f"{base}ed"
    if suffix in {".", ",", "?"}:
        return f"{base}{suffix}"
    return f"{base}{suffix}"


def construct_magic_ing_output(base: str) -> str | None:
    base = base.strip().lower()
    if not base:
        return None
    if base[-1] in "aeiou":
        return f"{base[:-1]}ing"
    return f"{base}ing"


def current_suffix_constructible_outputs(readme: Path) -> set[str]:
    _, rows, _ = parse_magic_table(readme)
    suffix_row = rows.get("suffix")
    if suffix_row is None:
        return set()

    suffixes: list[str] = []
    for cell in suffix_row[1]:
        if not cell or cell.startswith("["):
            continue
        raw = cell[1:-1] if cell.startswith('"') and cell.endswith('"') else cell
        raw = raw.strip().lower()
        if raw:
            suffixes.append(raw)

    outputs: set[str] = set()
    for row_name, (_, cells) in rows.items():
        if row_name == "suffix":
            continue
        for cell in cells:
            if not cell or cell.startswith("["):
                continue
            # Only bare multi-character cells activate the suffix state machine.
            if cell.startswith('"') and cell.endswith('"'):
                continue
            raw = cell.strip().lower()
            if len(raw) <= 1:
                continue
            ing_output = construct_magic_ing_output(raw)
            if ing_output:
                outputs.add(ing_output)
            for suffix in suffixes:
                constructed = construct_magic_suffix_output(raw, suffix)
                if constructed:
                    outputs.add(constructed)
    return outputs


def current_symbol_outputs(readme: Path) -> set[str]:
    outputs: set[str] = set()
    in_table = False
    for line in readme.read_text().splitlines():
        if line.startswith("| Symbol"):
            in_table = True
            continue
        if in_table and line.startswith("##"):
            break
        if not in_table or not line.startswith("|"):
            continue
        cells = split_table_line(line)
        if len(cells) < 2 or cells[0] in {"Symbol", "-------"}:
            continue
        command = cells[1].strip()
        if not command or command.startswith("KC_") or command.startswith("custom:") or command.startswith("magic:"):
            continue
        if command.startswith("UP(") or command.startswith("UM("):
            continue
        outputs.add(command.lower())
    return outputs


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


def chord_typing_effort(slot: MagicSlot) -> float:
    previous_pos = PRECEDING_POSITIONS.get(slot.row)
    if previous_pos is None:
        return 0.0
    previous_action = PhysicalAction("key", slot.row, previous_pos)
    magic_action = PhysicalAction("magic", slot.column, MAGIC_POSITIONS[slot.column])
    return (
        key_press_cost(previous_action.pos)
        + key_press_cost(magic_action.pos)
        + 1.6
        + action_transition_cost(previous_action, magic_action)
        + CHORD_SYNCHRONIZATION_COST
    )


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
    difficulty_power: float,
    difficulty_cutoff: float,
    min_difficulty: float | None,
    min_saved: int,
    allow_occupied: bool = False,
    distinct_by_output: bool = True,
    allow_zero_value: bool = False,
    row_balance_baseline: dict[str, int] | None = None,
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
            value, freq, plain_effort, chord_effort, effort_saved, saved = assignment_value(
                entry,
                slot,
                adaptives,
                blocked_pairs,
                magic_rows,
                source_weights,
                difficulty_power,
                difficulty_cutoff,
                min_saved,
            )
            if min_difficulty is not None and plain_effort < min_difficulty:
                continue
            if value < 0 or (value == 0 and not allow_zero_value):
                continue
            candidates.append(
                Assignment(
                    output=entry.output,
                    slot=slot,
                    value=value,
                    frequency=freq,
                    plain_effort=plain_effort,
                    chord_effort=chord_effort,
                    effort_saved=effort_saved,
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
    used_row_counts: dict[str, int] = {}
    assignments: list[Assignment] = []

    def row_balance_multiplier(row: str) -> float:
        if row_balance_baseline is None:
            return 1.0
        target = row_balance_baseline.get(row, 0)
        if target <= 0:
            return 1.0
        used = used_row_counts.get(row, 0)
        if used < target:
            return 1.0 + 0.08 * (target - used)
        if used > target:
            return max(0.7, 1.0 - 0.14 * (used - target))
        return 1.0

    def can_use(candidate: Assignment) -> bool:
        slot_key = (candidate.slot.row, candidate.slot.column)
        entry_key = candidate.output if distinct_by_output else candidate.source_chord
        if entry_key in used_entries or slot_key in used_slots:
            return False
        candidate_sources = candidate.source_label.split("+")
        if any(
            used_source_counts.get(source, 0) >= source_caps[source]
            for source in candidate_sources
            if source in source_caps
        ):
            return False
        return True

    if row_balance_baseline is None:
        for candidate in candidates:
            if not can_use(candidate):
                continue
            entry_key = candidate.output if distinct_by_output else candidate.source_chord
            used_entries.add(entry_key)
            used_slots.add((candidate.slot.row, candidate.slot.column))
            for source in candidate.source_label.split("+"):
                used_source_counts[source] = used_source_counts.get(source, 0) + 1
            used_row_counts[candidate.slot.row] = used_row_counts.get(candidate.slot.row, 0) + 1
            assignments.append(candidate)
            if len(assignments) >= budget:
                break
        return assignments

    while len(assignments) < budget:
        best_candidate: Assignment | None = None
        best_sort_key: tuple[float, float, bool, str, str] | None = None
        for candidate in candidates:
            if not can_use(candidate):
                continue
            adjusted_value = candidate.value * row_balance_multiplier(candidate.slot.row)
            sort_key = (
                adjusted_value,
                -candidate.slot.feel,
                candidate.slot.row_kind == "letter",
                candidate.slot.row,
                candidate.slot.column,
            )
            if best_sort_key is None or sort_key > best_sort_key:
                best_candidate = candidate
                best_sort_key = sort_key

        if best_candidate is None:
            break

        candidate = best_candidate
        entry_key = candidate.output if distinct_by_output else candidate.source_chord
        slot_key = (candidate.slot.row, candidate.slot.column)
        used_entries.add(entry_key)
        used_slots.add(slot_key)
        candidate_sources = candidate.source_label.split("+")
        for source in candidate_sources:
            used_source_counts[source] = used_source_counts.get(source, 0) + 1
        used_row_counts[candidate.slot.row] = used_row_counts.get(candidate.slot.row, 0) + 1
        assignments.append(candidate)
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
    letters_only: bool,
    limit: int,
    include_filled: bool,
) -> None:
    allowed_rows = LETTER_ROWS if letters_only else LETTER_ROWS + NON_LETTER_ROWS
    free_slots = sum(
        1
        for row in allowed_rows
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
            f"saved={assignment.saved:<2} plain={assignment.plain_effort:>4.2f} "
            f"chord={assignment.chord_effort:>4.2f} gain={assignment.effort_saved:>4.2f} "
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


def pinned_current_assignments(
    current_entries: list[ChordEntry],
    header: list[str],
    rows: dict[str, tuple[int, list[str]]],
    adaptives: dict[tuple[str, str], str],
    blocked_pairs: set[tuple[str, str]],
    magic_rows: dict[str, dict[str, str]],
    source_weights: dict[str, float],
    difficulty_power: float,
    difficulty_cutoff: float,
    min_saved: int,
) -> list[Assignment]:
    assignments: list[Assignment] = []
    for entry in current_entries:
        current_slot = current_slot_from_source(entry.chord, header, rows, entry.output)
        if current_slot is None:
            continue
        value, freq, plain_effort, chord_effort, effort_saved, saved = assignment_value(
            entry,
            current_slot,
            adaptives,
            blocked_pairs,
            magic_rows,
            source_weights,
            difficulty_power,
            difficulty_cutoff,
            min_saved,
        )
        assignments.append(
            Assignment(
                output=entry.output,
                slot=current_slot,
                value=value,
                frequency=freq,
                plain_effort=plain_effort,
                chord_effort=chord_effort,
                effort_saved=effort_saved,
                saved=saved,
                source_chord=entry.chord,
                source_label=entry.source_label,
            )
        )
    return assignments


def rows_with_assignments(
    header: list[str],
    rows: dict[str, tuple[int, list[str]]],
    assignments: list[Assignment],
) -> dict[str, tuple[int, list[str]]]:
    updated_rows = {row_name: (row_index, list(cells)) for row_name, (row_index, cells) in rows.items()}
    for row_name, (_, cells) in updated_rows.items():
        for index in range(len(cells)):
            cells[index] = ""
    for assignment in assignments:
        if assignment.slot.row not in updated_rows:
            updated_rows[assignment.slot.row] = (-1, [""] * len(header))
        row_index, cells = updated_rows[assignment.slot.row]
        column_index = header.index(assignment.slot.column)
        cells[column_index] = assignment.slot.representation
        updated_rows[assignment.slot.row] = (row_index, cells)
    return updated_rows


def print_rearrangements(
    assignments: list[Assignment],
    header: list[str],
    rows: dict[str, tuple[int, list[str]]],
    adaptives: dict[tuple[str, str], str],
    blocked_pairs: set[tuple[str, str]],
    magic_rows: dict[str, dict[str, str]],
    source_weights: dict[str, float],
    difficulty_power: float,
    difficulty_cutoff: float,
    min_saved: int,
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
        current_value, _, _, _, _, _ = assignment_value(
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
            difficulty_power,
            difficulty_cutoff,
            min_saved,
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


def print_delta_summary(
    current_entries: list[ChordEntry],
    assignments: list[Assignment],
) -> None:
    current_by_output = {entry.output: entry for entry in current_entries}
    selected_by_output = {assignment.output: assignment for assignment in assignments}

    kept_same: list[tuple[ChordEntry, Assignment]] = []
    moved: list[tuple[ChordEntry, Assignment]] = []
    added: list[Assignment] = []
    removed: list[ChordEntry] = []

    for output, assignment in selected_by_output.items():
        current = current_by_output.get(output)
        if current is None:
            added.append(assignment)
            continue
        if current.chord == f"{assignment.slot.row}:{assignment.slot.column}":
            kept_same.append((current, assignment))
        else:
            moved.append((current, assignment))

    for output, current in current_by_output.items():
        if output not in selected_by_output:
            removed.append(current)

    print()
    print(
        f"budget delta: keep={len(kept_same)} move={len(moved)} "
        f"add={len(added)} remove={len(removed)}"
    )

    print("kept:")
    if not kept_same:
        print("  <none>")
    else:
        for current, assignment in kept_same[:20]:
            print(
                f"  {assignment.output:<24} {assignment.slot.row:>4} {assignment.slot.column:<7} "
                f"value={assignment.value:.6f}"
            )

    print("moved:")
    if not moved:
        print("  <none>")
    else:
        for current, assignment in sorted(moved, key=lambda item: -item[1].value)[:20]:
            current_row, current_column = current.chord.split(":", 1)
            print(
                f"  {assignment.output:<24} {current_row:>4} {current_column:<7} -> "
                f"{assignment.slot.row:>4} {assignment.slot.column:<7} "
                f"value={assignment.value:.6f}"
            )

    print("add:")
    if not added:
        print("  <none>")
    else:
        for assignment in sorted(added, key=lambda item: -item.value):
            print(
                f"  {assignment.output:<24} {assignment.slot.row:>4} {assignment.slot.column:<7} "
                f"from={assignment.source_label:<16} value={assignment.value:.6f}"
            )

    print("remove:")
    if not removed:
        print("  <none>")
    else:
        for current in sorted(removed, key=lambda entry: entry.output):
            print(f"  {current.output:<24} {current.chord}")


def main() -> None:
    args = parse_args()
    header, rows, _ = parse_magic_table(args.readme)
    magic_rows = magic_rows_map(header, rows)
    adaptives = load_adaptives(args.readme)
    blocked_pairs = load_adaptive_blocks(args.readme)
    current_entries = load_current_magic_words(args.readme)
    if args.move_current_only:
        if args.allow_replacement or args.rearrange_current:
            raise SystemExit("--move-current-only cannot be combined with --allow-replacement/--rearrange-current")
        args.include_current = True
    if args.add is not None:
        if not args.include_current:
            raise SystemExit("--add requires --include-current")
        if args.allow_replacement or args.rearrange_current:
            raise SystemExit("--add is only supported without --allow-replacement/--rearrange-current")
        if args.add < 0:
            raise SystemExit("--add must be non-negative")
    old_chords = load_old_chords(args)
    if args.include_current:
        overrides = corpus_frequency_overrides(old_chords)
        enriched_current_entries: list[ChordEntry] = []
        for entry in current_entries:
            override = overrides.get(entry.output)
            if override is None:
                enriched_current_entries.append(entry)
                continue
            frequency_override, source_label = override
            enriched_current_entries.append(
                ChordEntry(
                    chord=entry.chord,
                    output=entry.output,
                    status=entry.status,
                    frequency_override=frequency_override,
                    source_label=source_label,
                    representation=entry.representation,
                )
            )
        old_chords.extend(enriched_current_entries)
    source_weights = parse_source_weights(args.source_weights)
    source_caps = parse_source_caps(args.source_cap)
    allow_occupied = args.rearrange_current or args.allow_replacement or args.move_current_only
    if args.move_current_only:
        current_assignments = greedy_assign(
            enriched_current_entries,
            header,
            rows,
            adaptives,
            blocked_pairs,
            magic_rows,
            source_weights,
            {},
            letters_only=args.letters_only,
            budget=len(enriched_current_entries),
            difficulty_power=args.difficulty_power,
            difficulty_cutoff=args.difficulty_cutoff,
            min_difficulty=args.min_difficulty,
            min_saved=args.min_saved,
            allow_occupied=True,
            distinct_by_output=False,
            allow_zero_value=True,
            row_balance_baseline=candidate_row_targets(enriched_current_entries, len(enriched_current_entries)),
        )
        if args.add is not None:
            addition_candidates = [entry for entry in old_chords if entry.status != "current"]
            reshuffled_rows = rows_with_assignments(header, rows, current_assignments)
            add_assignments = greedy_assign(
                addition_candidates,
                header,
                reshuffled_rows,
                adaptives,
                blocked_pairs,
                magic_rows,
                source_weights,
                source_caps,
                letters_only=args.letters_only,
                budget=args.add,
                difficulty_power=args.difficulty_power,
                difficulty_cutoff=args.difficulty_cutoff,
                min_difficulty=args.min_difficulty,
                min_saved=args.min_saved,
                allow_occupied=False,
                distinct_by_output=True,
            )
            assignments = current_assignments + add_assignments
        else:
            assignments = current_assignments
    elif args.include_current and not allow_occupied:
        pinned_assignments = pinned_current_assignments(
            enriched_current_entries,
            header,
            rows,
            adaptives,
            blocked_pairs,
            magic_rows,
            source_weights,
            args.difficulty_power,
            args.difficulty_cutoff,
            args.min_saved,
        )
        addition_candidates = [entry for entry in old_chords if entry.status != "current"]
        target_total = len(pinned_assignments) + args.add if args.add is not None else args.budget
        addition_budget = max(0, target_total - len(pinned_assignments))
        assignments = pinned_assignments + greedy_assign(
            addition_candidates,
            header,
            rows,
            adaptives,
            blocked_pairs,
            magic_rows,
            source_weights,
            source_caps,
            letters_only=args.letters_only,
            budget=addition_budget,
            difficulty_power=args.difficulty_power,
            difficulty_cutoff=args.difficulty_cutoff,
            min_difficulty=args.min_difficulty,
            min_saved=args.min_saved,
            allow_occupied=False,
            distinct_by_output=not args.rearrange_current,
        )
    else:
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
            difficulty_power=args.difficulty_power,
            difficulty_cutoff=args.difficulty_cutoff,
            min_difficulty=args.min_difficulty,
            min_saved=args.min_saved,
            allow_occupied=allow_occupied,
            distinct_by_output=not args.rearrange_current,
        )

    print_summary(
        old_chords,
        assignments,
        header,
        rows,
        letters_only=args.letters_only,
        limit=args.limit,
        include_filled=args.include_filled,
    )
    if args.rearrange_current or args.move_current_only:
        print_rearrangements(
            assignments,
            header,
            rows,
            adaptives,
            blocked_pairs,
            magic_rows,
            source_weights,
            args.difficulty_power,
            args.difficulty_cutoff,
            args.min_saved,
            limit=args.limit,
        )
    if args.show_delta:
        print_delta_summary(current_entries, assignments)

    if args.apply:
        apply_assignments(
            args.readme,
            header,
            args.apply,
            assignments,
            rearrange_current=allow_occupied,
            current_entries=current_entries if allow_occupied else None,
        )
        print()
        print(f"applied top {args.apply} assignments to {args.readme}")


if __name__ == "__main__":
    main()
