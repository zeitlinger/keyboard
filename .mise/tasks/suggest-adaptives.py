#!/usr/bin/env python3

# [MISE] description="Suggest new adaptive key candidates based on corpus bigram analysis"

"""Find adaptive key candidates that resolve SFBs/scissors without introducing new ones.

See agents/suggest-adaptives.md for algorithm details.
"""

import json
from pathlib import Path

CORPUS = Path.home() / "source/genkey/corpora/shai-iweb.json"

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

# Existing adaptives (trigger+physical_key) — skip
EXISTING = {'nh'}


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
    """Combo key followed by outward-adjacent single key is bad — combo fingers still in motion.
    Inward rolls (bl, pn, nv) are fine due to col stagger; only flag outward (toward pinky)."""
    a_pos, b_pos = LAYOUT[a_char], LAYOUT[b_char]
    if is_thumb(a_pos) or is_thumb(b_pos):
        return False  # thumb is a separate motion category
    same_hand = (a_pos[0] < 4) == (b_pos[0] < 4)
    adjacent = abs(a_pos[0] - b_pos[0]) == 1
    outward = a_pos[0] > b_pos[0]  # left hand: decreasing col = toward pinky
    return (a_char in COMBO_KEYS and b_char not in COMBO_KEYS
            and same_hand and adjacent and outward)


def is_bad(a, b):
    return is_sfb(a, b) or is_scissors(a, b)


def is_bad_chars(a_char, b_char):
    return is_bad(LAYOUT[a_char], LAYOUT[b_char]) or is_combo_adjacent(a_char, b_char)


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
    return ""


def main():
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
            if f"{a}{b}" in EXISTING:
                continue
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

    for a, b, bigram_freq in bad:
        pos_a = LAYOUT[a]
        print(f"\nBigram '{a}{b}' ({pct(bigram_freq):.3f}%) — {bad_reason_chars(a, b)}:")

        followers = sorted(
            [(tg, cnt) for tg, cnt in trigrams.items()
             if len(tg) == 3 and tg[0] == a and tg[1] == b],
            key=lambda x: -x[1]
        )[:5]

        candidates = []
        for c, pos_c in LAYOUT.items():
            if c in (a, b):
                continue
            if c in COMBO_KEYS:
                continue  # combo keys are awkward as physical adaptive keys
            if is_bad(pos_a, pos_c):
                continue
            sacrifice = bigrams.get(f"{a}{c}", 0)
            is_double = a == b
            max_sacrifice = total * MAX_SACRIFICE_DOUBLE / 100 if is_double else bigram_freq / 10
            if sacrifice >= max_sacrifice:
                continue
            bad_following = sum(
                1 for tg, _ in followers
                if tg[2] in LAYOUT and is_bad_chars(c, tg[2])
            )
            candidates.append((c, sacrifice, bad_following))

        candidates.sort(key=lambda x: (x[2], x[1]))

        if not candidates:
            print("  (no candidates)")
        else:
            for c, sacrifice, bad_following in candidates[:5]:
                follower_str = f"{bad_following}/{len(followers)}" if followers else "n/a"
                print(f"  {a} + {c} → {b}   sacrifice '{a}{c}' {pct(sacrifice):.3f}%"
                      f"   following-bad: {follower_str}")

    # --- Combo-roll adaptive opportunities ---
    print("\n=== Combo-Roll Adaptive Opportunities ===")
    print("(bad bigrams resolvable by rolling trigger→combo-key)\n")

    # For each bad bigram (a, b), find combo-key physical keys that form a good roll from a
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
                continue  # large row difference makes combo-combo rolls uncomfortable (e.g. pk: top→bottom)
            sacrifice = bigrams.get(f"{a}{c}", 0)
            if sacrifice >= bigram_freq / 10:
                continue
            bad_following = sum(
                1 for tg, _ in followers
                if tg[2] in LAYOUT and is_bad_chars(c, tg[2])
            )
            combo_hits.append((a, c, b, bigram_freq, sacrifice, bad_following, len(followers)))

    combo_hits.sort(key=lambda x: (-x[3], x[5], x[4]))  # by bigram freq, then quality

    for a, c, b, bigram_freq, sacrifice, bad_following, n_followers in combo_hits:
        follower_str = f"{bad_following}/{n_followers}" if n_followers else "n/a"
        reason = bad_reason_chars(a, b)
        print(f"  {a} + {c} → {b}   [{reason} {pct(bigram_freq):.3f}%]"
              f"   sacrifice '{a}{c}' {pct(sacrifice):.3f}%   following-bad: {follower_str}")


if __name__ == '__main__':
    main()
