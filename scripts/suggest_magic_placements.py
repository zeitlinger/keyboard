#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.11"
# dependencies = ["wordfreq"]
# ///

"""Implementation for `mise run suggest-magic-placements`."""

from __future__ import annotations

import argparse
from dataclasses import dataclass
from pathlib import Path

from feel import load_adaptives
from scripts.find_available_chords import (
    LETTER_ROWS,
    README,
    MagicSlot,
    candidate_slots,
    load_adaptive_blocks,
    magic_rows_map,
    output_difficulty,
    parse_magic_table,
)

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


@dataclass(frozen=True)
class PlacementRequest:
    word: str
    preferred_row: str | None = None
    discouraged_rows: tuple[str, ...] = ()


@dataclass(frozen=True)
class PlacementCandidate:
    word: str
    slot: MagicSlot
    score: float
    difficulty: float
    preferred_row: str | None


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Suggest practical magic-table placements for an explicit word list."
    )
    parser.add_argument("--readme", type=Path, default=README, help="Path to README.md")
    parser.add_argument("words", nargs="*", help="Words or phrases to place")
    parser.add_argument(
        "--words-file",
        type=Path,
        help="Optional newline-delimited word list; blank lines and # comments are ignored",
    )
    parser.add_argument(
        "--prefer-row",
        action="append",
        default=[],
        help="Prefer a specific row for one word, e.g. 'thank you=t' or 'gregor=z'",
    )
    parser.add_argument(
        "--top", type=int, default=3, help="Alternatives to print per word"
    )
    parser.add_argument(
        "--letters-only",
        action="store_true",
        help="Restrict placements to letter rows only",
    )
    return parser.parse_args()


def load_words(args: argparse.Namespace) -> list[str]:
    words = list(args.words)
    if args.words_file:
        for raw_line in args.words_file.read_text().splitlines():
            line = raw_line.strip()
            if not line or line.startswith("#"):
                continue
            words.append(line)
    seen = set()
    ordered = []
    for word in words:
        lowered = word.lower()
        if lowered in seen:
            continue
        seen.add(lowered)
        ordered.append(lowered)
    return ordered


def parse_preferred_rows(raw_items: list[str]) -> dict[str, str]:
    preferred = {}
    for item in raw_items:
        word, sep, row = item.partition("=")
        if not sep:
            raise ValueError(f"invalid --prefer-row '{item}', expected word=row")
        preferred[word.strip().lower()] = row.strip()
    return preferred


def default_discouraged_rows() -> tuple[str, ...]:
    # `q` is not on the main layer, so it should only be used deliberately.
    return ("q",)


def row_bonus(
    word: str,
    slot: MagicSlot,
    preferred_row: str | None,
    discouraged_rows: tuple[str, ...],
    existing_rows: set[str],
) -> float:
    if preferred_row:
        if slot.row == preferred_row:
            return 2.2
        return 0.85
    bonus = 1.0
    if slot.row not in existing_rows:
        bonus *= 0.82
    if slot.row in discouraged_rows:
        bonus *= 0.55
    if len(slot.row) == 1 and word.startswith(slot.row):
        bonus *= 1.5
    return bonus


def magic_hint_bonus(word: str, slot: MagicSlot) -> float:
    hints = MAGIC_HINT_LETTERS.get(slot.column, ())
    compact = word.replace(" ", "")
    if not hints or not compact:
        return 1.0
    if any(compact.endswith(hint) for hint in hints):
        return 1.14
    if any(hint in compact for hint in hints):
        return 1.05
    return 1.0


def placement_score(
    word: str,
    slot: MagicSlot,
    difficulty: float,
    preferred_row: str | None,
    discouraged_rows: tuple[str, ...],
    existing_rows: set[str],
) -> float:
    saved = max(1, len(word) - 2)
    return (
        (saved**2)
        * difficulty
        * row_bonus(word, slot, preferred_row, discouraged_rows, existing_rows)
        * magic_hint_bonus(word, slot)
        / (slot.feel + 1)
    )


def occupied_cells(
    header: list[str],
    rows: dict[str, tuple[int, list[str]]],
    *,
    row_names: list[str],
) -> list[str]:
    lines = []
    for row_name in row_names:
        current = rows.get(row_name)
        if not current:
            lines.append(f"{row_name}: <row not present; will be added on apply>")
            continue
        cells = current[1]
        used = [
            f"{column}={cells[index]}"
            for index, column in enumerate(header)
            if cells[index]
        ]
        lines.append(f"{row_name}: " + (", ".join(used) if used else "<all free>"))
    return lines


def build_candidates(
    requests: list[PlacementRequest],
    *,
    header: list[str],
    rows: dict[str, tuple[int, list[str]]],
    adaptives: dict[tuple[str, str], str],
    blocked_pairs: set[tuple[str, str]],
    magic_rows: dict[str, dict[str, str]],
    letters_only: bool,
    existing_rows: set[str],
) -> list[PlacementCandidate]:
    candidates: list[PlacementCandidate] = []
    for request in requests:
        difficulty = output_difficulty(
            request.word, adaptives, blocked_pairs, magic_rows
        )
        for slot in candidate_slots(
            request.word, header, rows, letters_only=letters_only
        ):
            candidates.append(
                PlacementCandidate(
                    word=request.word,
                    slot=slot,
                    score=placement_score(
                        request.word,
                        slot,
                        difficulty,
                        request.preferred_row,
                        request.discouraged_rows,
                        existing_rows,
                    ),
                    difficulty=difficulty,
                    preferred_row=request.preferred_row,
                )
            )
    return candidates


def greedy_pick(candidates: list[PlacementCandidate]) -> list[PlacementCandidate]:
    ranked = sorted(
        candidates,
        key=lambda item: (
            -item.score,
            item.slot.feel,
            item.slot.row_kind != "letter",
            item.slot.row,
            item.slot.column,
        ),
    )
    picked: list[PlacementCandidate] = []
    used_words: set[str] = set()
    used_slots: set[tuple[str, str]] = set()
    for candidate in ranked:
        slot_key = (candidate.slot.row, candidate.slot.column)
        if candidate.word in used_words or slot_key in used_slots:
            continue
        picked.append(candidate)
        used_words.add(candidate.word)
        used_slots.add(slot_key)
    return picked


def print_report(
    requests: list[PlacementRequest],
    picked: list[PlacementCandidate],
    all_candidates: list[PlacementCandidate],
    *,
    top: int,
    header: list[str],
    rows: dict[str, tuple[int, list[str]]],
) -> None:
    picked_by_word = {candidate.word: candidate for candidate in picked}
    preferred_rows = [
        request.preferred_row for request in requests if request.preferred_row
    ]
    prefix_rows = [
        request.word[0]
        for request in requests
        if request.word and request.word[0] in LETTER_ROWS
    ]
    row_names = []
    for row_name in preferred_rows + prefix_rows:
        if row_name and row_name not in row_names:
            row_names.append(row_name)

    if row_names:
        print("occupied rows:")
        for line in occupied_cells(header, rows, row_names=row_names):
            print(f"  {line}")
        print()

    print("selected placements:")
    for request in requests:
        chosen = picked_by_word.get(request.word)
        if not chosen:
            print(f"  {request.word}: <no free slot>")
            continue
        preferred = (
            f" preferred={request.preferred_row}" if request.preferred_row else ""
        )
        print(
            f"  {request.word:24} -> {chosen.slot.row} {chosen.slot.column}"
            f" feel={chosen.slot.feel:.1f} diff={chosen.difficulty:.2f}{preferred}"
        )
        alternatives = [
            candidate
            for candidate in sorted(
                (item for item in all_candidates if item.word == request.word),
                key=lambda item: (
                    -item.score,
                    item.slot.feel,
                    item.slot.row,
                    item.slot.column,
                ),
            )
            if (candidate.slot.row, candidate.slot.column)
            != (chosen.slot.row, chosen.slot.column)
        ][:top]
        if alternatives:
            print(
                "    alternatives: "
                + ", ".join(
                    f"{alt.slot.row} {alt.slot.column} (feel={alt.slot.feel:.1f})"
                    for alt in alternatives
                )
            )


def main() -> None:
    args = parse_args()
    words = load_words(args)
    preferred_rows = parse_preferred_rows(args.prefer_row)
    discouraged = default_discouraged_rows()
    requests = [
        PlacementRequest(
            word=word,
            preferred_row=preferred_rows.get(word),
            discouraged_rows=discouraged,
        )
        for word in words
    ]

    header, rows, _ = parse_magic_table(args.readme)
    magic_rows = magic_rows_map(header, rows)
    adaptives = load_adaptives(args.readme)
    blocked_pairs = load_adaptive_blocks(args.readme)
    existing_rows = set(rows)

    candidates = build_candidates(
        requests,
        header=header,
        rows=rows,
        adaptives=adaptives,
        blocked_pairs=blocked_pairs,
        magic_rows=magic_rows,
        letters_only=args.letters_only,
        existing_rows=existing_rows,
    )
    picked = greedy_pick(candidates)
    print_report(requests, picked, candidates, top=args.top, header=header, rows=rows)


if __name__ == "__main__":
    main()
