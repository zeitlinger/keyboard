#!/usr/bin/env python3

# [MISE] description="Suggest new adaptive key candidates based on corpus bigram analysis"

"""Find adaptive key candidates that resolve SFBs/scissors without introducing new ones.

See agents/suggest-adaptives.md for algorithm details.
"""

import argparse
import json
import re
import sys
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


def load_magic_table():
    """Parse the Magic Keys table → dict of trigger -> {'A': val, 'B': val, 'C': val}.

    Values are the raw cell text (single char or quoted string or empty string).
    """
    table = {}
    in_table = False
    for line in README.read_text().splitlines():
        if '## Magic Keys' in line:
            in_table = True
            continue
        if in_table:
            if line.startswith('##'):
                break
            m = re.match(r'\|\s*(\w)\s*\|([^|]*)\|([^|]*)\|([^|]*)\|', line)
            if m:
                trigger = m.group(1)
                table[trigger] = {
                    'A': m.group(2).strip().strip('"'),
                    'B': m.group(3).strip().strip('"'),
                    'C': m.group(4).strip().strip('"'),
                }
    return table


def load_magic_coverage(magic_table):
    """Return set of (trigger, output) pairs covered by magic (single-char outputs only)."""
    covered = set()
    for trigger, variants in magic_table.items():
        for val in variants.values():
            if len(val) == 1 and val.isalpha():
                covered.add((trigger, val))
    return covered


# Physical positions of the three magic key variants.
# magicA: R.Ind. combo row (col 4, row 2 approx)
# magicB: R.Mid. combo row (col 5, row 2 approx)
# magicC: R.Ring top row   (col 6, row 0)
MAGIC_POSITIONS = {'A': (4, 2), 'B': (5, 2), 'C': (6, 0)}

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


def slot_feel_score(trigger, variant):
    if trigger not in LAYOUT:
        return 1
    trigger_pos = LAYOUT[trigger]
    pos = MAGIC_POSITIONS[variant]
    row_diff = abs(trigger_pos[1] - pos[1])
    if (trigger_pos[0] < 4) != (pos[0] < 4):
        return 1
    if row_diff > 1:
        return 99
    col_diff = abs(trigger_pos[0] - pos[0])
    inward = pos[0] > trigger_pos[0]
    if col_diff == 1 and row_diff > 0:
        return 2 if (trigger_pos[0] in (0, 7) or pos[0] in (0, 7)) else 1
    return 0 if inward else 1


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


def apply_to_readme(add, keep, magic_remove, magic_add_new, magic_table):
    """Apply recommended adaptive and magic key changes to README.md."""
    content = README.read_text()
    lines = content.splitlines(keepends=True)

    # Build new adaptive table rows (add + keep, sorted)
    all_adaptives = sorted(set(add) | set(keep))

    def fmt_adaptive_row(a, c, b):
        return f"|{a.center(11)}|{c.center(5)}|{b.center(8)}|\n"

    # Build working magic table: original → apply removes → apply adds
    working_magic = {t: dict(variants) for t, variants in magic_table.items()}

    for (trigger, variant), _output in magic_remove.items():
        working_magic.setdefault(trigger, {'A': '', 'B': '', 'C': ''})[variant] = ''

    for (trigger, output), _reason in sorted(magic_add_new.items()):
        row = working_magic.get(trigger, {'A': '', 'B': '', 'C': ''})
        free = [v for v in ('A', 'B', 'C') if not row.get(v)]
        if free:
            best = min(free, key=lambda v: slot_feel_score(trigger, v))
            working_magic.setdefault(trigger, {'A': '', 'B': '', 'C': ''})
            working_magic[trigger][best] = output
        else:
            val_to_variants = {}
            for v in ('A', 'B', 'C'):
                val = row.get(v, '')
                if val:
                    val_to_variants.setdefault(val, []).append(v)
            replaced = False
            for val, variants_list in val_to_variants.items():
                if len(variants_list) >= 2:
                    variants_by_feel = sorted(variants_list, key=lambda v: slot_feel_score(trigger, v))
                    drop_v = variants_by_feel[-1]
                    working_magic[trigger][drop_v] = output
                    replaced = True
                    break
            if not replaced:
                print(f"WARNING: no magic slot for {trigger} → {output}, skipping", file=sys.stderr)

    def fmt_magic_val(val, width):
        if not val:
            return ' ' * width
        display = f'"{val}"' if len(val) > 1 else val
        return display.center(width)

    def fmt_magic_row(trigger, variants):
        A = variants.get('A', '')
        B = variants.get('B', '')
        C = variants.get('C', '')
        return f"|{trigger.center(7)}|{fmt_magic_val(A,10)}|{fmt_magic_val(B,10)}|{fmt_magic_val(C,9)}|\n"

    # Rewrite file
    new_lines = []
    section = None
    adaptive_header_done = False

    for line in lines:
        stripped = line.rstrip('\n')

        if stripped.startswith('## Magic Keys'):
            section = 'magic'
            new_lines.append(line)
            continue
        elif stripped.startswith('## Adaptives'):
            section = 'adaptives'
            adaptive_header_done = False
            new_lines.append(line)
            continue
        elif stripped.startswith('## '):
            section = None
            new_lines.append(line)
            continue

        if section == 'magic':
            m = re.match(r'\|\s*(\w)\s*\|([^|]*)\|([^|]*)\|([^|]*)\|', stripped)
            if m and len(m.group(1)) == 1:
                trigger = m.group(1)
                if trigger in working_magic:
                    new_lines.append(fmt_magic_row(trigger, working_magic[trigger]))
                    continue
            new_lines.append(line)
            continue

        if section == 'adaptives':
            if stripped.startswith('|:-'):
                new_lines.append(line)
                for a, c, b in all_adaptives:
                    new_lines.append(fmt_adaptive_row(a, c, b))
                adaptive_header_done = True
                continue
            elif adaptive_header_done:
                if stripped.startswith('|'):
                    continue  # skip old data rows
                new_lines.append(line)
                continue
            else:
                new_lines.append(line)
                continue

        new_lines.append(line)

    README.write_text(''.join(new_lines))
    print(f"Applied changes to {README}")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--apply', action='store_true', help='Apply recommended changes to README.md')
    args = parser.parse_args()

    existing = load_existing_adaptives()
    magic_table = load_magic_table()
    magic_covered = load_magic_coverage(magic_table)

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
            # Sacrifice is acceptable if the bad bigram can be typed via magic,
            # OR if this is an existing adaptive whose trigger+physical pair already
            # has a recovery magic key (happens after --apply on a re-run).
            is_existing = (a, c) in existing
            magic_free = (
                ((a, b) in magic_covered or (is_existing and (a, c) in magic_covered))
                and pct(sacrifice) < MAX_MAGIC_SACRIFICE_PCT
            )
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
            candidates.append((c, sacrifice, bad_following, feel, same_hand, magic_free))

        candidates.sort(key=lambda x: (x[3], x[4], x[2], x[1]))

        if not candidates:
            print("  (no candidates)")
        else:
            best_candidate[(a, b)] = candidates[0][0]
            valid_candidates[(a, b)] = {c for c, _, _, _, _, _ in candidates}
            all_candidates[(a, b)] = candidates  # full sorted list for conflict resolution
            for c, sacrifice, bad_following, feel, _, mfree in candidates[:50]:
                marker = " *" if (a, c) in existing else ""
                follower_str = f"{bad_following}/{len(followers)}" if followers else "n/a"
                sac_str = f"{pct(sacrifice):.3f}%" + (" (magic)" if mfree else "")
                print(f"  {a} + {c} → {b}   feel={feel}  sacrifice '{a}{c}' {sac_str}"
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

    # --- Recommended changes (greedy assignment) ---
    # Assign candidates greedily by bigram frequency; fall back when (a, c) already taken.
    # If an existing adaptive already covers (a, b) with equal or better feel, keep it.
    recommended = {}  # (trigger, physical) -> output
    for a, b, _ in bad:  # already sorted by frequency descending
        candidates_list = all_candidates.get((a, b), [])
        by_key = {cand[0]: cand for cand in candidates_list}

        # If existing already has a valid candidate for this output, prefer it unless
        # a strictly better-feel new candidate exists.
        existing_for_output = [(a, c_ex) for (a_ex, c_ex), b_ex in existing.items() if a_ex == a and b_ex == b and c_ex in by_key]
        if existing_for_output:
            best_new_feel = min((by_key[c][3] for c in by_key if (a, c) not in existing and existing.get((a, c)) is None), default=999)
            existing_feel = min(by_key[c_ex][3] for _, c_ex in existing_for_output)
            if best_new_feel >= existing_feel:
                # Existing is at least as good; record it as recommended and skip new
                for _, c_ex in existing_for_output:
                    recommended[(a, c_ex)] = b
                continue

        for c, _, _, feel, _, _ in candidates_list:
            if feel > MAX_RECOMMEND_FEEL:
                break  # list is sorted by feel; no point continuing
            existing_output = existing.get((a, c))
            already_taken = (a, c) in recommended or (
                existing_output is not None and existing_output != b
            )
            if not already_taken:
                recommended[(a, c)] = b
                break

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

    # --- Pre-compute magic slot availability before printing adaptives ---

    covered_outputs = set()  # (trigger, output) pairs covered by add+keep adaptives
    for (a, c), b in recommended.items():
        covered_outputs.add((a, b))
    for (a, c), b in existing.items():
        if (a, c) not in remove_set:
            covered_outputs.add((a, b))

    # Magic entries to ADD: bad bigrams with no good adaptive, or lost from removed adaptives
    magic_add = {}   # (trigger, output) -> reason
    for a, b, bigram_freq in bad:
        if (a, b) in covered_outputs:
            continue
        best_feel = min((cand[3] for cand in all_candidates.get((a, b), [])), default=999)
        if best_feel > MAX_RECOMMEND_FEEL:
            magic_add[(a, b)] = f"bad bigram '{a}{b}' {pct(bigram_freq):.3f}%, best adaptive feel={best_feel}"
    for a, c, b in remove:
        if (a, b) not in covered_outputs and (a, b) not in magic_add:
            magic_add[(a, b)] = f"removed adaptive '{a}+{c}→{b}'"

    # Recovery magic: new adaptives intercept trigger+physical → the original ac sequence
    # is now lost; suggest magic trigger→physical so it can still be typed.
    for (a, c), b in recommended.items():
        if (a, c) in existing:
            continue  # existing adaptive already had this interception
        sacrifice = bigrams.get(f"{a}{c}", 0)
        if sacrifice > 0 and (a, c) not in magic_covered:
            magic_add.setdefault((a, c), f"recovery: '{a}{c}' intercepted by {a}+{c}→{b} adaptive ({pct(sacrifice):.3f}%)")

    # Magic entries to REMOVE: single-char entries where an adaptive now covers (trigger, output).
    # Once we commit to adding the adaptive, the magic it relied on for sacrifice justification
    # can be freed — the adaptive is the new owner of that (trigger, output) pair.
    magic_remove = {}  # (trigger, variant) -> output
    for trigger, variants in magic_table.items():
        for variant, val in variants.items():
            if len(val) == 1 and val.isalpha() and (trigger, val) in covered_outputs:
                magic_remove[(trigger, variant)] = val

    # Effective magic table after removals — used for slot availability in Add
    effective_magic_table = {
        t: {v: val for v, val in variants.items() if (t, v) not in magic_remove}
        for t, variants in magic_table.items()
    }

    magic_remove_pairs = {(t, val) for (t, v), val in magic_remove.items()}

    # Magic entries to KEEP: relied on by adaptive recommendations (magic_free candidates)
    # but not already being removed.
    magic_keep = {}  # (trigger, output) -> [adaptive descriptions]
    for a, b, _ in bad:
        for cand in all_candidates.get((a, b), []):
            c, sacrifice, _, feel, _, mfree = cand
            if (mfree and (a, c) in recommended and recommended[(a, c)] == b
                    and (a, b) not in magic_remove_pairs):
                magic_keep.setdefault((a, b), []).append(f"{a}+{c}→{b}")

    def best_magic_slot(trigger):
        """Return (variant, replace_note) for the best available slot.

        Considers: genuinely free slots, then duplicate-value slots (one can be dropped).
        Returns (variant, None) for free slot, (variant, 'replace Magic X=val') for duplicate.
        Returns None if no slot can be found.
        """
        row = effective_magic_table.get(trigger, {})
        free = [v for v in ('A', 'B', 'C') if not row.get(v)]
        if free:
            best = min(free, key=lambda v: slot_feel_score(trigger, v))
            return (best, None)
        # Look for duplicate values — one can be dropped to free a slot
        val_to_variants = {}
        for v in ('A', 'B', 'C'):
            val = row.get(v, '')
            if val:
                val_to_variants.setdefault(val, []).append(v)
        for val, variants in val_to_variants.items():
            if len(variants) >= 2:
                # Keep the better-feel one, free the worse one
                variants_by_feel = sorted(variants, key=lambda v: slot_feel_score(trigger, v))
                keep_v, drop_v = variants_by_feel[0], variants_by_feel[-1]
                return (drop_v, f"replace Magic {drop_v}={val} (dup of {keep_v})")
        return None

    # Adaptives that have no possible magic recovery slot — drop them
    no_recovery = {}  # (a, c) -> b
    for (a, c), b in list(recommended.items()):
        if (a, c) in existing:
            continue
        sacrifice = bigrams.get(f"{a}{c}", 0)
        if sacrifice > 0 and (a, c) not in magic_covered:
            if best_magic_slot(a) is None:
                no_recovery[(a, c)] = b

    for key in no_recovery:
        del recommended[key]

    add = [(a, c, b) for (a, c), b in recommended.items() if (a, c) not in existing]

    # Drop recovery magic entries for removed adaptives
    no_recovery_pairs = {(a, c) for a, c in no_recovery}
    magic_add_new = {k: v for k, v in magic_add.items()
                     if k not in magic_covered and k not in no_recovery_pairs}
    magic_add_exists = {k: v for k, v in magic_add.items() if k in magic_covered}

    # --- Print adaptive recommendations ---
    print("\n=== Recommended Changes ===\n")

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

    # --- Print magic recommendations ---
    print("\n=== Magic Keys Recommended Changes ===\n")

    if no_recovery:
        print("Skipped (no magic recovery slot):")
        for (a, c), b in sorted(no_recovery.items()):
            row = magic_table.get(a, {})
            taken = ', '.join(f"{v}={row[v]}" for v in ('A', 'B', 'C') if row.get(v))
            print(f"  {a} + {c} → {b}   (magic {a}: {taken})")
        print()

    if magic_add_new:
        print("Add:")
        for (trigger, output), reason in sorted(magic_add_new.items()):
            result = best_magic_slot(trigger)
            if result:
                variant, note = result
                slot_str = f" → Magic {variant}" + (f" ({note})" if note else "")
            else:
                row = effective_magic_table.get(trigger, {})
                taken = ', '.join(f"{v}={row[v]}" for v in ('A', 'B', 'C') if row.get(v))
                slot_str = f" (no free slot: {taken})"
            print(f"  {trigger} → {output}{slot_str}   [{reason}]")
    else:
        print("Add: (none)")

    if magic_remove:
        print("\nRemove (now served by adaptive):")
        # Group by trigger for readability
        by_trigger = {}
        for (trigger, variant), output in sorted(magic_remove.items()):
            by_trigger.setdefault(trigger, []).append(f"Magic {variant}={output}")
        for trigger, entries in sorted(by_trigger.items()):
            print(f"  {trigger}: {', '.join(entries)}")

    if magic_keep:
        print("\nKeep (relied on by adaptive recommendations):")
        for (trigger, output), adaptives in sorted(magic_keep.items()):
            print(f"  {trigger} → {output}   [enables {', '.join(adaptives)}]")

    if magic_add_exists:
        print("\nAlready in table (add section covered):")
        for (trigger, output), reason in sorted(magic_add_exists.items()):
            print(f"  {trigger} → {output}   [{reason}]")

    if args.apply:
        apply_to_readme(add, keep, magic_remove, magic_add_new, magic_table)


if __name__ == '__main__':
    main()
