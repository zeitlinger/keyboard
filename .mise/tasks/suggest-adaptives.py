#!/usr/bin/env python3

# [MISE] description="Suggest new adaptive key candidates based on corpus bigram analysis"

"""Find adaptive key candidates that resolve SFBs/scissors without introducing new ones.

See agents/suggest-adaptives.md for algorithm details.
"""

import json
import re
from pathlib import Path

CORPUS = Path.home() / "source/genkey/corpora/shai-iweb.json"
README = Path(__file__).parents[2] / "README.md"


def load_existing_adaptives():
    """Parse the Adaptives table from README.md → dict of (trigger, physical) → output."""
    existing = {}
    in_table = False
    for line in README.read_text().splitlines():
        if '## Adaptives' in line:
            in_table = True
            continue
        if in_table:
            if line.startswith('##'):
                break
            m = re.match(r'\|\s*(\w)\s*\|\s*(\w)\s*\|\s*(\w)\s*\|', line)
            if m:
                existing[(m.group(1), m.group(2))] = m.group(3)
    return existing


def load_magic_coverage():
    """Parse the Magic Keys table → set of (trigger, output) pairs covered by magic.

    A magic entry covers the sacrifice: if magic already maps trigger→output,
    typing trigger+physical_key won't lose any intended bigrams.
    Only single-char outputs count (multi-char strings are expansions, not bigram coverage).
    """
    covered = set()
    in_table = False
    for line in README.read_text().splitlines():
        if '## Magic Keys' in line:
            in_table = True
            continue
        if in_table:
            if line.startswith('##'):
                break
            # | trigger | Magic A | Magic B | Magic C |
            m = re.match(r'\|\s*(\w)\s*\|([^|]*)\|([^|]*)\|([^|]*)\|', line)
            if m:
                trigger = m.group(1)
                for col in (m.group(2), m.group(3), m.group(4)):
                    val = col.strip().strip('"')
                    if len(val) == 1 and val.isalpha():
                        covered.add((trigger, val))
    return covered

# Single-key base layer positions: char -> (col, row)
# Col 0-3 = left hand (pinky->index), 4-7 = right hand (index->pinky)
# Row 0 = top, 1 = home, 2 = bottom, 3 = thumb (separate finger, excluded from SFB)
LAYOUT = {
    's': (0,1), 'c': (1,1), 'n': (2,1), 't': (3,1),
    'a': (4,1), 'e': (5,1), 'i': (6,1), 'h': (7,1),
    'f': (1,2), 'l': (2,2), 'd': (3,2),
    'u': (4,2), 'o': (5,2), 'y': (6,2),
    'x': (1,0), 'w': (2,0),
    'r': (3,3),  # left thumb
    # Combo keys (vertical combos; row = approximate position in combo table)
    'p': (1,0), 'b': (1,2),   # ring finger top/bottom combo
    'm': (2,0), 'g': (2,2),   # middle finger top/bottom combo
    'v': (3,0), 'k': (3,2),   # index finger top/bottom combo
}

COMBO_KEYS = set('pbmgvk')

MIN_FREQ_PCT = 0.020       # ignore bad bigrams below this frequency
MAX_SACRIFICE_DOUBLE = 0.005  # for double-letter bigrams, require near-zero sacrifice
MAX_MAGIC_SACRIFICE_PCT = 0.030  # sacrifice bigrams below this can be covered by adding a magic entry
MAX_RECOMMEND_FEEL = 1     # only recommend adding adaptives with feel <= this


def is_thumb(pos):
    return pos[1] == 3


def is_sfb(a, b):
    if is_thumb(a) or is_thumb(b):
        return False  # thumb is a separate finger from index
    return a[0] == b[0]


def is_scissors(a, b):
    if is_thumb(a) or is_thumb(b):
        return False
    same_hand = (a[0] < 4) == (b[0] < 4)
    col_diff = abs(a[0] - b[0])
    row_diff = abs(a[1] - b[1])
    return same_hand and col_diff <= 1 and row_diff >= 2


def is_combo_adjacent(a_char, b_char):
    """Combo key followed by adjacent single key is bad — combo fingers still in motion."""
    a_pos, b_pos = LAYOUT[a_char], LAYOUT[b_char]
    if is_thumb(a_pos) or is_thumb(b_pos):
        return False
    same_hand = (a_pos[0] < 4) == (b_pos[0] < 4)
    adjacent = abs(a_pos[0] - b_pos[0]) == 1
    return (a_char in COMBO_KEYS and b_char not in COMBO_KEYS
            and same_hand and adjacent)


def is_combo_preceded(a_char, b_char):
    """Regular key followed by a combo key on the same hand — timing conflict for the combo."""
    if a_char in COMBO_KEYS or b_char not in COMBO_KEYS:
        return False
    a_pos, b_pos = LAYOUT[a_char], LAYOUT[b_char]
    if is_thumb(a_pos) or is_thumb(b_pos):
        return False
    return (a_pos[0] < 4) == (b_pos[0] < 4)


def is_bad(a, b):
    return is_sfb(a, b) or is_scissors(a, b)


def feel_score(a_char, b_char):
    """Lower = better feel for the physical motion a_char → b_char.

    Combo followed by:
      0 = good inward same-hand roll
      1 = alternation or outward same-hand roll
      2 = adjacent finger (col_diff=1) with row change, pinky involved
     99 = row_diff > 1 without d exception (uncomfortable reach)
    Combo key as physical target: floor of 2 (never better than "ok").
    """
    a_pos, b_pos = LAYOUT[a_char], LAYOUT[b_char]
    row_diff = abs(a_pos[1] - b_pos[1])

    # Thumb is its own finger — treat as alternation
    if is_thumb(a_pos) or is_thumb(b_pos):
        score = 1
    # Different hands: alternation
    elif (a_pos[0] < 4) != (b_pos[0] < 4):
        score = 1
    else:
        # Same hand
        col_diff = abs(a_pos[0] - b_pos[0])
        inward = b_pos[0] > a_pos[0]  # left hand: increasing col = toward index

        # row_diff > 1 is bad unless one key is 'd' (index bottom, most dexterous)
        if row_diff > 1 and 'd' not in (a_char, b_char):
            return 99

        if col_diff == 1 and row_diff > 0:
            pinky = (a_pos[0] in (0, 7) or b_pos[0] in (0, 7))
            score = 2 if pinky else 1  # adjacent+row_change: worse when pinky involved
        elif inward:
            score = 0
        else:
            score = 1

    if b_char in COMBO_KEYS:
        score = max(score, 2)

    return score


def is_bad_chars(a_char, b_char):
    return (is_bad(LAYOUT[a_char], LAYOUT[b_char])
            or is_combo_adjacent(a_char, b_char)
            or is_combo_preceded(a_char, b_char))


def bad_reason(a, b):
    if is_sfb(a, b):
        return f"SFB col {a[0]}"
    if is_scissors(a, b):
        return "scissors"
    return ""


def bad_reason_chars(a_char, b_char):
    r = bad_reason(LAYOUT[a_char], LAYOUT[b_char])
    if r:
        return r
    if is_combo_adjacent(a_char, b_char):
        return "combo-adjacent"
    if is_combo_preceded(a_char, b_char):
        return "combo-preceded"
    return ""


def main():
    existing = load_existing_adaptives()
    magic_covered = load_magic_coverage()

    with open(CORPUS) as f:
        corpus = json.load(f)

    bigrams = corpus['bigrams']
    trigrams = corpus['trigrams']
    total = sum(bigrams.values())

    def pct(count):
        return count / total * 100

    # --- Bad bigrams ---
    bad = []
    for a in LAYOUT:
        for b in LAYOUT:
            if a == b:
                continue  # same-letter bigrams need same-letter output — not useful
            if is_bad_chars(a, b):
                freq = bigrams.get(f"{a}{b}", 0)
                if freq > 0:
                    bad.append((a, b, freq))

    bad = [(a, b, freq) for a, b, freq in bad if pct(freq) >= MIN_FREQ_PCT]
    bad.sort(key=lambda x: -x[2])

    print("=== Bad Bigrams (SFB / scissors / combo-adjacent) ===\n")
    for a, b, freq in bad:
        print(f"  {a}{b}  {pct(freq):.3f}%  {bad_reason_chars(a, b)}")

    # --- Adaptive candidates for bad bigrams ---
    print("\n=== Adaptive Candidates for Bad Bigrams ===")

    # best_candidate[(a, b)] = c  — top pick per bad bigram
    best_candidate = {}
    # valid_candidates[(a, b)] = {c, ...} — all passing candidates per bad bigram
    valid_candidates = {}
    # all_candidates[(a, b)] = [(c, sacrifice, bad_following, feel), ...] sorted
    all_candidates = {}

    for a, b, bigram_freq in bad:
        pos_a = LAYOUT[a]
        print(f"\nBigram '{a}{b}' ({pct(bigram_freq):.3f}%) — {bad_reason_chars(a, b)}:")

        followers = sorted(
            [(tg, cnt) for tg, cnt in trigrams.items()
             if len(tg) == 3 and tg[0] == a and tg[1] == b],
            key=lambda x: -x[1]
        )[:5]

        candidates = []
        for c in LAYOUT:
            if c in (a, b):
                continue
            if is_bad_chars(a, c):
                continue
            sacrifice = bigrams.get(f"{a}{c}", 0)
            magic_free = (a, b) in magic_covered and pct(sacrifice) < MAX_MAGIC_SACRIFICE_PCT
            is_double = a == b
            max_sacrifice = total * MAX_SACRIFICE_DOUBLE / 100 if is_double else bigram_freq / 10
            if not magic_free and sacrifice >= max_sacrifice:
                continue
            bad_following = sum(
                1 for tg, _ in followers
                if tg[2] in LAYOUT and is_bad_chars(c, tg[2])
            )
            feel = feel_score(a, c)
            same_hand = (LAYOUT[a][0] < 4) == (LAYOUT[c][0] < 4)
            candidates.append((c, sacrifice, bad_following, feel, same_hand))

        candidates.sort(key=lambda x: (x[3], x[4], x[2], x[1]))

        if not candidates:
            print("  (no candidates)")
        else:
            best_candidate[(a, b)] = candidates[0][0]
            valid_candidates[(a, b)] = {c for c, _, _, _, _ in candidates}
            all_candidates[(a, b)] = candidates  # full sorted list for conflict resolution
            for c, sacrifice, bad_following, feel, _ in candidates[:50]:
                marker = " *" if (a, c) in existing else ""
                follower_str = f"{bad_following}/{len(followers)}" if followers else "n/a"
                print(f"  {a} + {c} → {b}   feel={feel}  sacrifice '{a}{c}' {pct(sacrifice):.3f}%"
                      f"   following-bad: {follower_str}{marker}")

    # --- Combo-roll adaptive opportunities ---
    print("\n=== Combo-Roll Adaptive Opportunities ===")
    print("(bad bigrams resolvable by rolling trigger→combo-key)\n")

    combo_hits = []
    for a, b, bigram_freq in bad:
        pos_a = LAYOUT[a]
        followers = sorted(
            [(tg, cnt) for tg, cnt in trigrams.items()
             if len(tg) == 3 and tg[0] == a and tg[1] == b],
            key=lambda x: -x[1]
        )[:5]

        for c in COMBO_KEYS:
            if c in (a, b):
                continue
            pos_c = LAYOUT[c]
            if is_bad(pos_a, pos_c):
                continue
            if abs(pos_a[1] - pos_c[1]) > 1:
                continue
            sacrifice = bigrams.get(f"{a}{c}", 0)
            if sacrifice >= bigram_freq / 10:
                continue
            bad_following = sum(
                1 for tg, _ in followers
                if tg[2] in LAYOUT and is_bad_chars(c, tg[2])
            )
            combo_hits.append((a, c, b, bigram_freq, sacrifice, bad_following, len(followers)))

    combo_hits.sort(key=lambda x: (-x[3], x[5], x[4]))

    for a, c, b, bigram_freq, sacrifice, bad_following, n_followers in combo_hits:
        marker = " *" if (a, c) in existing else ""
        follower_str = f"{bad_following}/{n_followers}" if n_followers else "n/a"
        reason = bad_reason_chars(a, b)
        print(f"  {a} + {c} → {b}   [{reason} {pct(bigram_freq):.3f}%]"
              f"   sacrifice '{a}{c}' {pct(sacrifice):.3f}%   following-bad: {follower_str}{marker}")

    # --- Recommended changes ---
    print("\n=== Recommended Changes ===\n")

    # Assign candidates greedily by bigram frequency; fall back when (a, c) already taken.
    # If an existing adaptive already covers (a, b) with equal or better feel, keep it.
    recommended = {}  # (trigger, physical) -> output
    for a, b, _ in bad:  # already sorted by frequency descending
        candidates_list = all_candidates.get((a, b), [])
        by_key = {cand[0]: cand for cand in candidates_list}

        # If existing already has a valid candidate for this output, prefer it unless
        # a strictly better-feel new candidate exists.
        existing_for_output = [(a, c_ex) for (a, c_ex), b_ex in existing.items() if b_ex == b and c_ex in by_key]
        if existing_for_output:
            best_new_feel = min((by_key[c][3] for c in by_key if (a, c) not in existing and existing.get((a, c)) is None), default=999)
            existing_feel = min(by_key[c_ex][3] for _, c_ex in existing_for_output)
            if best_new_feel >= existing_feel:
                # Existing is at least as good; record it as recommended and skip new
                for _, c_ex in existing_for_output:
                    recommended[(a, c_ex)] = b
                continue

        for c, _, _, feel, _ in candidates_list:
            if feel > MAX_RECOMMEND_FEEL:
                break  # list is sorted by feel; no point continuing
            existing_output = existing.get((a, c))
            already_taken = (a, c) in recommended or (
                existing_output is not None and existing_output != b
            )
            if not already_taken:
                recommended[(a, c)] = b
                break

    add = [(a, c, b) for (a, c), b in recommended.items() if (a, c) not in existing]

    # Build index: for each (trigger, output), which physical key is recommended?
    recommended_physical = {}  # (a, b) -> c
    for (a, c), b in recommended.items():
        recommended_physical[(a, b)] = c

    bad_set = {(a, b) for a, b, _ in bad}

    def existing_superseded(a, c, b):
        """True if a strictly better-feel candidate was recommended for the same (trigger, output)."""
        c_new = recommended_physical.get((a, b))
        if c_new is None or c_new == c:
            return False
        by_key = {cand[0]: cand for cand in all_candidates.get((a, b), [])}
        feel_old = by_key[c][3] if c in by_key else 999
        feel_new = by_key[c_new][3] if c_new in by_key else 999
        return feel_new < feel_old

    remove = [
        (a, c, b) for (a, c), b in existing.items()
        if (a, b) not in bad_set
        or c not in valid_candidates.get((a, b), set())
        or existing_superseded(a, c, b)
    ]

    remove_set = {(a, c) for a, c, _ in remove}
    keep = [(a, c, b) for (a, c), b in existing.items() if (a, c) not in remove_set]

    if add:
        print("Add:")
        for a, c, b in sorted(add):
            print(f"  {a} + {c} → {b}")
    else:
        print("Add: (none)")

    if keep:
        print("\nKeep (existing, still justified):")
        for a, c, b in sorted(keep):
            print(f"  {a} + {c} → {b}")

    if remove:
        print("\nRemove (no longer justified):")
        for a, c, b in sorted(remove):
            print(f"  {a} + {c} → {b}")
    else:
        print("\nRemove: (none)")

    # --- Suggested magic entries ---
    # Covers two cases:
    # 1. Bad bigrams with no feel<=MAX_RECOMMEND_FEEL adaptive candidate
    # 2. Outputs lost from removed adaptives (trigger, output) not covered by add/keep
    print("\n=== Suggested Magic Entries ===\n")

    covered_outputs = set()  # (trigger, output) pairs covered by add+keep
    for (a, c), b in recommended.items():
        covered_outputs.add((a, b))
    for (a, c), b in existing.items():
        if (a, c) not in remove_set:
            covered_outputs.add((a, b))

    magic_needed = {}  # (trigger, output) -> reason
    for a, b, bigram_freq in bad:
        if (a, b) in covered_outputs:
            continue
        best_feel = min((cand[3] for cand in all_candidates.get((a, b), [])), default=999)
        if best_feel > MAX_RECOMMEND_FEEL:
            magic_needed[(a, b)] = f"bad bigram '{a}{b}' {pct(bigram_freq):.3f}%, best adaptive feel={best_feel}"

    for a, c, b in remove:
        if (a, b) not in covered_outputs and (a, b) not in magic_needed:
            magic_needed[(a, b)] = f"removed adaptive '{a}+{c}→{b}'"

    if magic_needed:
        # Check which are already in magic table
        for (trigger, output), reason in sorted(magic_needed.items()):
            already = (trigger, output) in magic_covered
            marker = " (already in magic table)" if already else ""
            print(f"  {trigger} → {output}   [{reason}]{marker}")
    else:
        print("  (none)")


if __name__ == '__main__':
    main()
