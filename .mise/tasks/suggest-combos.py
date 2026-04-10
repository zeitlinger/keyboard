#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.11"
# dependencies = ["wordfreq", "rich"]
# ///

# [MISE] description="Suggest chords to add, ranked by typing benefit"

"""Rank all chord candidates (unplanned + missing words) by typing benefit.

Unplanned chords already have assignments. Missing words are paired with the
best available free chord (better words get easier chords, greedily).

Without --apply: show suggestions only.
With --apply N: mark/add top N as 'plan' in README.md.
"""

import argparse
import bisect
import os
import re
import sys
from collections import Counter
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parents[2]))
from feel import feel_score, LAYOUT, COMBO_KEYS, load_adaptives, actual_keystrokes

from wordfreq import word_frequency

README = Path(__file__).parents[2] / "README.md"

SAVED_MIN   = 3
TRIGGER_COST = 1  # chord mode activation is a combo keypress — subtract from savings
SOURCE_MIN  = 200
VOWEL_MIN   = 0.2
TOP_MISSING = 200   # how many missing words to consider for assignment


# ── Scoring ───────────────────────────────────────────────────────────────────

def chord_feel_score(chord: str) -> int:
    keys = [c for c in chord if c in LAYOUT]
    base = feel_score(keys[0], keys[1]) if len(keys) >= 2 else 0
    # Combo key as chord starter (2+ char chord): harder to time precisely
    if len(chord) >= 2 and chord[0] in COMBO_KEYS:
        return max(base, 2)
    # Punctuation: harder to remember
    if any(not c.isalpha() for c in chord):
        return max(base, 2)
    return base


def output_difficulty(output: str, adaptives: dict) -> float:
    keys = [c for c in actual_keystrokes(output.lower(), adaptives) if c in LAYOUT]
    if len(keys) < 2:
        return 1.0
    scores = [min(feel_score(a, b), 5) for a, b in zip(keys, keys[1:])]
    return sum(scores) / len(scores)


def chord_value(chord: str, output: str, adaptives: dict) -> float:
    freq = max(word_frequency(w, "en") for w in output.split())
    saved = len(output) - len(chord) - TRIGGER_COST
    if saved < SAVED_MIN:
        return 0.0
    return saved**2 * freq * output_difficulty(output, adaptives) / (chord_feel_score(chord) + 1)


# ── Chord table ───────────────────────────────────────────────────────────────

def parse_chord_table() -> list[tuple[int, str, str, str]]:
    rows = []
    in_table = False
    for i, line in enumerate(README.read_text().splitlines()):
        if "## Chord Table" in line:
            in_table = True
            continue
        if in_table and line.startswith("##"):
            break
        if not in_table:
            continue
        m = re.match(r"\|\s*([a-z,./]+)\s*\|\s*\"([^\"]+)\"\s*\|\s*(yes|plan|done)?\s*\|", line)
        if m:
            rows.append((i, m.group(1).strip(), m.group(2).strip(), m.group(3) or ""))
    return rows


def available_free_chords(used: set[str]) -> list[str]:
    """All chord sequences available per find_available_chords.py, minus already used."""
    candidates = []
    rolls = {'s': 'cnt', 'c': 'nt', 'n': 'td', 'f': 'ld', 'l': 'd'}
    for left in 'scntfldzbgkpmxwvr':
        candidates.append(left)
        candidates.append('r' + left)
        candidates.append(left + left)
        for right in 'aeihy,.juor':
            candidates.append(left + right)
        for right in rolls.get(left, ''):
            candidates.append(left + right)
    return [c for c in set(candidates) if c not in used]


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

def apply_changes(to_plan: list[str], to_add: list[tuple[str, str]]) -> None:
    """Mark existing chords as plan; insert new chord→output rows alphabetically."""
    lines = README.read_text().splitlines(keepends=True)
    to_plan_set = set(to_plan)

    # Mark existing unplanned as plan
    in_table = False
    table_end = None
    for i, line in enumerate(lines):
        if "## Chord Table" in line:
            in_table = True
            continue
        if in_table and line.startswith("##"):
            table_end = i
            break
        if not in_table:
            continue
        m = re.match(r"(\|\s*([a-z,./]+)\s*\|\s*\"[^\"]+\"\s*\|\s*)(yes|plan|done)?(\s*\|)", line)
        if m and m.group(2).strip() in to_plan_set:
            lines[i] = m.group(1) + "plan" + m.group(4) + "\n"

    # Insert new entries alphabetically within the table
    if to_add and table_end is not None:
        # Collect existing chord positions for insertion sort
        chord_lines: list[tuple[str, int]] = []
        in_table = False
        for i, line in enumerate(lines):
            if "## Chord Table" in line:
                in_table = True
                continue
            if in_table and line.startswith("##"):
                break
            if not in_table:
                continue
            m = re.match(r"\|\s*([a-z,./]+)\s*\|", line)
            if m:
                chord_lines.append((m.group(1).strip(), i))

        # Insert each new entry alphabetically, updating positions as we go
        existing_chords = [chord for chord, _ in chord_lines]
        existing_positions = [pos for _, pos in chord_lines]
        for chord, output in sorted(set(to_add)):  # set() deduplicates
            # Find insertion index: after last existing chord that sorts <= chord
            insert_line = table_end
            for i, (ec, lp) in enumerate(zip(existing_chords, existing_positions)):
                if ec <= chord:
                    insert_line = lp + 1
            new_line = f'| {chord:<6} | "{output}" | plan |\n'
            lines.insert(insert_line, new_line)
            # Shift all positions after the insertion point
            existing_positions = [p + 1 if p >= insert_line else p for p in existing_positions]
            table_end += 1

    README.write_text("".join(lines))


# ── Main ──────────────────────────────────────────────────────────────────────

def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--apply", type=int, metavar="N",
                        help="Mark/add top N candidates as plan in README.md")
    args = parser.parse_args()

    adaptives = load_adaptives(README)
    rows = parse_chord_table()
    used_chords  = {chord for _, chord, _, _ in rows}
    used_outputs = {output for _, _, output, _ in rows}

    # ── Unplanned (already in table, no status) ────────────────────────────
    candidates: list[tuple[float, str, str, str]] = []  # (value, chord, output, kind)
    for _, chord, output, status in rows:
        if not status:
            val = chord_value(chord, output, adaptives)
            if val > 0:
                candidates.append((val, chord, output, "unplanned"))

    # ── Missing words — greedy chord assignment ────────────────────────────
    print("Building source corpus…", end="", flush=True)
    counts = build_source_corpus()
    print(f" {len(counts):,} unique words")

    total = sum(counts.values())
    missing_words: list[tuple[float, str]] = []  # (potential_value, word)
    for word, count in counts.items():
        if word in used_outputs or not looks_real(word, counts):
            continue
        saved = len(word) - 2  # best case: 1-char chord
        if saved < SAVED_MIN:
            continue
        freq = count / total
        diff = output_difficulty(word, adaptives)
        missing_words.append((saved**2 * freq * diff, word))

    missing_words.sort(reverse=True)

    # Greedily assign best available chord to each word
    free = available_free_chords(used_chords)
    # Easiest chords first; prefer letter-only over punctuation at equal feel
    free.sort(key=lambda c: (chord_feel_score(c), any(not ch.isalpha() for ch in c), len(c)))

    assigned_free = list(free)
    for _, word in missing_words[:TOP_MISSING]:
        if not assigned_free:
            break
        best_chord = max(assigned_free, key=lambda c: chord_value(c, word, adaptives))
        val = chord_value(best_chord, word, adaptives)
        if val > 0:
            candidates.append((val, best_chord, word, "new"))
            assigned_free.remove(best_chord)

    # ── Display ────────────────────────────────────────────────────────────
    candidates.sort(reverse=True)

    print(f"\n{'':2}{'chord':8} {'output':28} {'score':8} {'saved':6} {'feel':5} {'':4}")
    print(f"  {'-'*62}")
    for val, chord, output, kind in candidates[:30]:
        saved = len(output) - len(chord)
        feel  = chord_feel_score(chord)
        tag   = " *" if kind == "new" else ""
        print(f"  {chord:8} {output:28} {val:8.2e} {saved:6} {feel:5}{tag}")
    print("\n  * = new entry (not yet in chord table)")

    # ── Apply ──────────────────────────────────────────────────────────────
    if args.apply:
        n = args.apply
        top = candidates[:n]
        to_plan = [chord for _, chord, _, kind in top if kind == "unplanned"]
        to_add  = [(chord, output) for _, chord, output, kind in top if kind == "new"]
        apply_changes(to_plan, to_add)
        print(f"\nApplied {n} changes:")
        if to_plan:
            print(f"  Marked as plan: {', '.join(to_plan)}")
        if to_add:
            print(f"  Added new:      {', '.join(f'{c}→{o}' for c, o in to_add)}")
        print("Run 'mise run generate' to rebuild firmware.")


if __name__ == "__main__":
    main()
