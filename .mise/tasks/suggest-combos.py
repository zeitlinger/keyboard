#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.11"
# dependencies = ["wordfreq", "rich"]
# ///

# [MISE] description="Suggest magic-key expansions to add, ranked by typing benefit"

"""Rank magic-key (preceding-letter × magic column) candidates by typing benefit.

A magic expansion costs 2 keystrokes: the preceding letter plus one of the
nine magic keys. The cell emits a suffix (prefix-stripped against the
preceding letter when it matches) or a single character.

Without --apply: show suggestions only.
With --apply N: insert top N as new cells in the Magic Keys table.
"""

import argparse
import os
import re
import sys
from collections import Counter
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parents[2]))
from feel import (
    LAYOUT, COMBO_KEYS, MAGIC_POSITIONS, feel_score,
    load_adaptives, actual_keystrokes,
)

from wordfreq import word_frequency

README = Path(__file__).parents[2] / "README.md"

VARIANTS = tuple(f'magic_{c}' for c in 'abcdefghi')

SAVED_MIN   = 3
SOURCE_MIN  = 200
VOWEL_MIN   = 0.2
TOP_MISSING = 200


# ── Scoring ───────────────────────────────────────────────────────────────────

def magic_feel_score(prev: str, magic: str) -> int:
    """Feel of rolling from `prev` (letter) to `magic` column.

    Row scheme: combos at odd rows (1, 3), non-combos at even (0, 2, 4, 5=thumb).
    """
    if prev not in LAYOUT:
        return 2  # punctuation / special: arbitrary mid value
    a_pos = LAYOUT[prev]
    b_pos = MAGIC_POSITIONS[magic]
    if (a_pos[0] < 4) != (b_pos[0] < 4):
        return 1  # cross-hand: alternation
    col_diff = abs(a_pos[0] - b_pos[0])
    row_diff = abs(a_pos[1] - b_pos[1])
    if col_diff == 0:
        return 99 if row_diff == 0 else 3   # SFB — same column same-hand
    if row_diff > 3:
        return 99  # top ↔ bottom extreme
    if col_diff == 1 and row_diff >= 2:
        return 3   # scissors (skipping a row between adjacent fingers)
    if col_diff == 1 and row_diff >= 1:
        pinky = a_pos[0] in (0, 7) or b_pos[0] in (0, 7)
        return 2 if pinky else 1
    inward = b_pos[0] > a_pos[0] if a_pos[0] < 4 else b_pos[0] < a_pos[0]
    return 0 if inward else 1


def output_difficulty(output: str, adaptives: dict) -> float:
    keys = [c for c in actual_keystrokes(output.lower(), adaptives) if c in LAYOUT]
    if len(keys) < 2:
        return 1.0
    scores = [min(feel_score(a, b), 5) for a, b in zip(keys, keys[1:])]
    return sum(scores) / len(scores)


def magic_value(prev: str, magic: str, output: str, adaptives: dict) -> float:
    """Value of using (prev + magic) to produce `output`.

    Only sensible when `output` starts with `prev` (generator prefix-strips);
    otherwise the emit prepends junk to the preceding letter.
    """
    if not output or not output.lower().startswith(prev.lower()):
        return 0.0
    freq = max(word_frequency(w, "en") for w in output.split())
    saved = len(output) - 2  # 2 keystrokes: prev + magic
    if saved < SAVED_MIN:
        return 0.0
    return saved**2 * freq * output_difficulty(output, adaptives) / (magic_feel_score(prev, magic) + 1)


# ── Magic table ───────────────────────────────────────────────────────────────

def parse_magic_table() -> tuple[dict[tuple[str, str], tuple[int, str]], int]:
    """Return (cells, table_end_line) where cells maps (prev, magic_col) → (line_index, raw_value)."""
    cells = {}
    in_table = False
    table_end = None
    row_re = re.compile(r'^\|\s*(\w)\s*\|' + r'([^|]*)\|' * len(VARIANTS))
    for i, line in enumerate(README.read_text().splitlines()):
        if '## Magic Keys' in line:
            in_table = True
            continue
        if in_table:
            if line.startswith('##'):
                table_end = i
                break
            m = row_re.match(line)
            if m and len(m.group(1)) == 1:
                prev = m.group(1)
                for idx, col in enumerate(VARIANTS):
                    raw = m.group(idx + 2).strip()
                    if raw:
                        cells[(prev, col)] = (i, raw)
    return cells, table_end or len(README.read_text().splitlines())


def parse_cell(raw: str) -> str:
    """Return the emitted text (without surrounding quotes)."""
    if raw.startswith('"') and raw.endswith('"'):
        return raw[1:-1]
    return raw


def used_outputs(cells: dict) -> set[str]:
    return {parse_cell(raw) for _, raw in cells.values()}


# ── Source corpus ─────────────────────────────────────────────────────────────

def build_source_corpus() -> Counter:
    counts: Counter = Counter()
    exts = {".go", ".java", ".py", ".kt", ".ts", ".js", ".md",
            ".yaml", ".yml", ".toml", ".sh"}
    skip = {".git", "node_modules", "vendor", "target", "build", ".venv"}
    for root, dirs, files in os.walk(Path.home() / "source"):
        dirs[:] = [d for d in dirs if d not in skip]
        for f in files:
            if Path(f).suffix in exts:
                try:
                    text = (Path(root) / f).read_text(errors="ignore")
                    for w in re.findall(r"[a-z]{5,20}", text.lower()):
                        counts[w] += 1
                except OSError:
                    pass
    return counts


def looks_real(word: str, counts: Counter) -> bool:
    vowels = sum(1 for c in word if c in "aeiou")
    return vowels / len(word) >= VOWEL_MIN and (
        word_frequency(word, "en") > 0 or counts[word] > SOURCE_MIN
    )


# ── README editing ────────────────────────────────────────────────────────────

def apply_changes(to_add: list[tuple[str, str, str]]) -> None:
    """Insert top candidates into the Magic Keys table.

    `to_add` entries: (prev_letter, magic_col, output).
    If the (prev, col) cell exists but is blank, fill it. If the `prev` row
    doesn't exist yet, we skip with a warning — authors maintain the row set.
    """
    lines = README.read_text().splitlines(keepends=True)
    row_re = re.compile(r'^(\|\s*(\w)\s*\|)(' + r'[^|]*\|' * len(VARIANTS) + r')')

    # Index existing rows by prev letter
    row_index: dict[str, int] = {}
    in_table = False
    for i, line in enumerate(lines):
        if '## Magic Keys' in line:
            in_table = True
            continue
        if in_table and line.startswith('##'):
            break
        if not in_table:
            continue
        m = row_re.match(line.rstrip('\n'))
        if m and len(m.group(2)) == 1:
            row_index[m.group(2)] = i

    skipped = []
    for prev, col, output in to_add:
        if prev not in row_index:
            skipped.append((prev, col, output))
            continue
        li = row_index[prev]
        line = lines[li].rstrip('\n')
        parts = line.split('|')  # ['', ' prev ', ' colA ', ..., ' colI ', '']
        col_idx = VARIANTS.index(col) + 2  # +1 for leading empty, +1 for prev
        if parts[col_idx].strip():
            continue  # already filled; don't clobber
        width = len(parts[col_idx])
        display = f'"{output}"' if len(output) > 1 else output
        parts[col_idx] = display.center(width)
        lines[li] = '|'.join(parts) + '\n'

    README.write_text(''.join(lines))
    if skipped:
        print(f"\nSkipped ({len(skipped)} — no row for preceding letter):")
        for prev, col, output in skipped:
            print(f"  {prev} + {col} → {output}")


# ── Main ──────────────────────────────────────────────────────────────────────

def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--apply", type=int, metavar="N",
                        help="Insert top N candidates into the Magic Keys table")
    args = parser.parse_args()

    adaptives = load_adaptives(README)
    cells, _ = parse_magic_table()
    existing_outputs = used_outputs(cells)
    used_slots = set(cells.keys())

    # ── Existing cells — rate each currently-in-table entry ───────────────
    candidates: list[tuple[float, str, str, str, str]] = []  # (value, prev, col, output, kind)
    for (prev, col), (_, raw) in cells.items():
        output = parse_cell(raw)
        if not output or output == 'dotSpc':
            continue
        val = magic_value(prev, col, output, adaptives)
        if val > 0:
            candidates.append((val, prev, col, output, "existing"))

    # ── Missing words — greedy slot assignment ────────────────────────────
    print("Building source corpus…", end="", flush=True)
    counts = build_source_corpus()
    print(f" {len(counts):,} unique words")

    total = sum(counts.values())
    missing_words: list[tuple[float, str]] = []
    for word, count in counts.items():
        if word in existing_outputs or not looks_real(word, counts):
            continue
        saved = len(word) - 2
        if saved < SAVED_MIN:
            continue
        freq = count / total
        diff = output_difficulty(word, adaptives)
        missing_words.append((saved**2 * freq * diff, word))
    missing_words.sort(reverse=True)

    # All free (prev, col) slots, easiest feel first
    free_slots = [
        (prev, col) for prev in LAYOUT for col in VARIANTS
        if (prev, col) not in used_slots and magic_feel_score(prev, col) < 3
    ]
    free_slots.sort(key=lambda pc: magic_feel_score(*pc))

    for _, word in missing_words[:TOP_MISSING]:
        prev = word[0]
        # Candidate slots for this word must have prev == word[0]
        slot_opts = [pc for pc in free_slots if pc[0] == prev]
        if not slot_opts:
            continue
        best = max(slot_opts, key=lambda pc: magic_value(pc[0], pc[1], word, adaptives))
        val = magic_value(best[0], best[1], word, adaptives)
        if val > 0:
            candidates.append((val, best[0], best[1], word, "new"))
            free_slots.remove(best)

    # ── Display ────────────────────────────────────────────────────────────
    candidates.sort(reverse=True)

    n = args.apply or 30
    top = candidates[:n]
    to_add = [(prev, col, output) for _, prev, col, output, kind in top if kind == "new"]

    print(f"\n  {'prev+magic':14} {'output':24} {'score':10} {'saved':6} {'feel':5}")
    print(f"  {'-'*64}")
    for val, prev, col, output, kind in candidates[:30]:
        saved = len(output) - 2
        feel = magic_feel_score(prev, col)
        tag  = " +" if kind == "new" else ""
        slot = f"{prev}+{col}"
        print(f"  {slot:14} {output:24} {val:10.2e} {saved:6} {feel:5}{tag}")
    print("\n  + = new suggestion (not yet in Magic Keys table)")

    # ── Apply ──────────────────────────────────────────────────────────────
    if args.apply:
        apply_changes(to_add)
        print(f"\nApplied {len(to_add)} new cells:")
        for prev, col, output in to_add:
            print(f"  {prev} + {col} → {output}")
        print("Run 'mise run generate' to rebuild firmware.")


if __name__ == "__main__":
    main()
