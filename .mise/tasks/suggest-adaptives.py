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

sys.path.insert(0, str(Path(__file__).parents[2]))
from feel import LAYOUT, COMBO_KEYS, is_thumb, is_sfb, is_scissors, is_combo_adjacent, is_combo_preceded, is_bad, feel_score  # noqa: E402

CORPUS = Path.home() / "source/genkey/corpora/shai-iweb.json"
README = Path(__file__).parents[2] / "README.md"


def load_existing_adaptives():
    """Parse the Adaptives table from README.md.

    Returns:
        existing: dict of (trigger, physical) → output for single-key adaptives
        compensation: set of (trigger, output) pairs covered by multi-key adaptives (e.g. qu)
    """
    existing = {}
    compensation = set()
    in_table = False
    for line in README.read_text().splitlines():
        if '## Adaptives' in line:
            in_table = True
            continue
        if in_table:
            if line.startswith('##'):
                break
            m = re.match(r'\|\s*(\w)\s*\|\s*(\w+)\s*\|\s*(\w)\s*\|', line)
            if m:
                trigger, key, output = m.group(1), m.group(2), m.group(3)
                if len(key) == 1:
                    existing[(trigger, key)] = output
                else:
                    compensation.add((trigger, output))
    return existing, compensation


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


def compute_lead_variants(magic_table):
    """For each single-char output letter, determine which variant (A/B/C) it appears on most.

    Returns:
        leads: dict of output_char → preferred variant (e.g. {'h': 'C', 'd': 'A'})
        lead_counts: dict of output_char → count on lead variant (e.g. {'h': 5, 'd': 2})
    """
    from collections import Counter
    counts = {}  # output -> Counter({variant: count})
    for trigger, variants in magic_table.items():
        for v, val in variants.items():
            if len(val) == 1 and val.isalpha():
                counts.setdefault(val, Counter())[v] += 1
    leads = {ch: counter.most_common(1)[0][0] for ch, counter in counts.items()}
    lead_counts = {ch: counter[leads[ch]] for ch, counter in counts.items()}
    return leads, lead_counts


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

MIN_FREQ_PCT = 0.01      # ignore bad bigrams below this frequency
MAX_MAGIC_SACRIFICE_PCT = MIN_FREQ_PCT  # sacrifice bigrams below this can be covered by adding a magic entry
MAX_RECOMMEND_FEEL = 2     # only recommend adding adaptives with feel <= this


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


def apply_to_readme(add, keep, magic_remove, magic_add_new, magic_table, magic_swaps=None):
    """Apply recommended adaptive and magic key changes to README.md."""
    lead_variants, lead_counts = compute_lead_variants(magic_table)
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
        lead_v = lead_variants.get(output)
        if free:
            if lead_v in free:
                best = lead_v
            elif lead_v:
                # Displace occupant if output has stronger claim on the lead slot
                occupant = row.get(lead_v, '')
                occ_clean = occupant.strip('"') if occupant else ''
                if (len(occ_clean) == 1 and occ_clean.isalpha()
                        and (lead_variants.get(occ_clean) != lead_v
                             or lead_counts.get(output, 0) > lead_counts.get(occ_clean, 0))):
                    displace_to = min(free, key=lambda v: slot_feel_score(trigger, v))
                    row[displace_to] = occupant
                    best = lead_v
                else:
                    best = min(free, key=lambda v: slot_feel_score(trigger, v))
            else:
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

    # Apply lead-variant swaps
    for trigger, src_v, dest_v, output in (magic_swaps or []):
        row = working_magic.get(trigger, {'A': '', 'B': '', 'C': ''})
        row[src_v], row[dest_v] = row[dest_v], row[src_v]
        working_magic[trigger] = row

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
                # Collect multi-char adaptive rows (e.g. qu compensation) from original
                multi_char = []
                for orig_line in lines:
                    orig_stripped = orig_line.rstrip('\n')
                    m = re.match(r'\|\s*(\w)\s*\|\s*(\w+)\s*\|\s*(\w)\s*\|', orig_stripped)
                    if m and len(m.group(2)) > 1:
                        multi_char.append((m.group(1), m.group(2), m.group(3)))
                # Merge and sort all adaptive rows together
                all_rows = sorted(set(all_adaptives) | set(multi_char))
                for a, c, b in all_rows:
                    new_lines.append(fmt_adaptive_row(a, c, b))
                adaptive_header_done = True
                continue
            elif adaptive_header_done:
                if stripped.startswith('|'):
                    continue  # skip old data rows (already rewritten above)
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

    existing, compensation = load_existing_adaptives()
    magic_table = load_magic_table()
    magic_covered = load_magic_coverage(magic_table)

    with open(CORPUS) as f:
        corpus = json.load(f)

    bigrams = corpus['bigrams']
    trigrams = corpus['trigrams']
    total = corpus['Total']  # total characters, matching genkey's denominator

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
            if is_bad(LAYOUT[a], LAYOUT[c]) or is_combo_preceded(a, c):
                continue  # combo-adjacent handled by feel_score, not filtered here
            sacrifice = bigrams.get(f"{a}{c}", 0)
            # Sacrifice is acceptable if the bad bigram can be typed via magic,
            # OR if this is an existing adaptive whose trigger+physical pair already
            # has a recovery magic key (happens after --apply on a re-run).
            is_existing = (a, c) in existing
            magic_free = (
                ((a, b) in magic_covered or (is_existing and (a, c) in magic_covered))
                and pct(sacrifice) < MAX_MAGIC_SACRIFICE_PCT
            )
            if not magic_free and sacrifice >= bigram_freq / 10 and pct(sacrifice) >= MIN_FREQ_PCT:
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
        if c not in by_key:
            return False  # existing key was a deliberate user choice outside valid candidates
        feel_old = by_key[c][3]
        feel_new = by_key[c_new][3] if c_new in by_key else 999
        return feel_new < feel_old

    # Use is_bad_chars (not bad_set) so existing adaptives are only removed if the bigram
    # is not physically bad at all — frequency threshold applies to new suggestions, not
    # to keeping deliberate user choices.
    remove = [
        (a, c, b) for (a, c), b in existing.items()
        if not is_bad_chars(a, b)
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
    # Skip if a compensation adaptive (e.g. qu) already covers this pair.
    for (a, c), b in recommended.items():
        if (a, c) in existing:
            continue  # handled by the kept-adaptives loop below
        sacrifice = bigrams.get(f"{a}{c}", 0)
        if sacrifice > 0 and (a, c) not in magic_covered and (a, c) not in compensation:
            magic_add.setdefault((a, c), f"recovery: '{a}{c}' intercepted by {a}+{c}→{b} adaptive ({pct(sacrifice):.3f}%)")

    # Recovery magic for existing kept adaptives that were never given a recovery key.
    for a, c, b in keep:
        sacrifice = bigrams.get(f"{a}{c}", 0)
        if sacrifice > 0 and (a, c) not in magic_covered and (a, c) not in compensation:
            magic_add.setdefault((a, c), f"recovery: '{a}{c}' intercepted by existing {a}+{c}→{b} adaptive ({pct(sacrifice):.3f}%)")

    # Magic entries to REMOVE: single-char entries where an adaptive now covers (trigger, output).
    # Once we commit to adding the adaptive, the magic it relied on for sacrifice justification
    # can be freed — the adaptive is the new owner of that (trigger, output) pair.
    # Also free recovery magic for removed adaptives: if adaptive a+c→b is removed, the
    # magic entry for (a, c) that allowed typing "ac" is no longer needed.
    magic_remove = {}  # (trigger, variant) -> output
    freed_by_removal = {(a, c) for a, c, _ in remove}  # recovery keys no longer needed
    for trigger, variants in magic_table.items():
        for variant, val in variants.items():
            if len(val) == 1 and val.isalpha() and (trigger, val) in covered_outputs:
                magic_remove[(trigger, variant)] = val
            elif (trigger, val) in freed_by_removal and (trigger, val) not in magic_add:
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

    lead_variants, lead_counts = compute_lead_variants(magic_table)

    def best_magic_slot(trigger, output=None):
        """Return (variant, replace_note) for the best available slot.

        Considers: genuinely free slots, then duplicate-value slots (one can be dropped).
        Prefers the lead variant for the output letter when available.
        Returns (variant, None) for free slot, (variant, 'replace Magic X=val') for duplicate.
        Returns None if no slot can be found.
        """
        lead_v = lead_variants.get(output) if output else None
        row = effective_magic_table.get(trigger, {})
        free = [v for v in ('A', 'B', 'C') if not row.get(v)]
        if free:
            if lead_v in free:
                return (lead_v, None)
            # Lead slot occupied — displace occupant if output has a stronger claim
            # (more entries on lead variant, or occupant doesn't lead this slot at all)
            if lead_v and lead_v not in free:
                occupant = row.get(lead_v, '')
                occupant_clean = occupant.strip('"') if occupant else ''
                if (len(occupant_clean) == 1 and occupant_clean.isalpha()
                        and (lead_variants.get(occupant_clean) != lead_v
                             or lead_counts.get(output, 0) > lead_counts.get(occupant_clean, 0))):
                    # Occupant doesn't lead this slot; displace it to a free slot
                    displace_to = min(free, key=lambda v: slot_feel_score(trigger, v))
                    return (lead_v, f"displace {lead_v}={occupant} to {displace_to}")
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
            if best_magic_slot(a, c) is None:
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
            result = best_magic_slot(trigger, output)
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
        # Group by variant (A/B/C) to help with learning
        by_variant = {'A': [], 'B': [], 'C': []}
        for (trigger, output), adaptives in sorted(magic_keep.items()):
            row = magic_table.get(trigger, {})
            variants = [v for v in ('A', 'B', 'C') if row.get(v) == output]
            for v in variants:
                by_variant[v].append((trigger, output, adaptives))
        for variant in ('A', 'B', 'C'):
            entries = by_variant[variant]
            if entries:
                print(f"  Magic {variant}:")
                for trigger, output, adaptives in entries:
                    print(f"    {trigger} → {output}   [enables {', '.join(adaptives)}]")

    if magic_add_exists:
        print("\nAlready in table (add section covered):")
        for (trigger, output), reason in sorted(magic_add_exists.items()):
            print(f"  {trigger} → {output}   [{reason}]")

    # --- Current magic table grouped by variant ---
    print("\n=== Current Magic Table (single-char, by variant) ===\n")
    for variant in ('A', 'B', 'C'):
        entries = []
        for trigger in sorted(magic_table):
            val = magic_table[trigger].get(variant, '')
            if len(val) == 1 and val.isalpha():
                entries.append(f"{trigger}→{val}")
        if entries:
            print(f"  Magic {variant}: {', '.join(entries)}")

    # --- Lead magic per trigger key ---
    print("\n=== Lead Magic per Output Key ===\n")
    output_variants: dict[str, set[str]] = {}
    for trigger, variants in magic_table.items():
        for v, val in variants.items():
            if len(val) == 1 and val.isalpha() and val not in COMBO_KEYS:
                output_variants.setdefault(val, set()).add(v)
    for letter in sorted(output_variants):
        used = ', '.join(v for v in ('A', 'B', 'C') if v in output_variants[letter])
        print(f"  {letter}: {used}")

    # --- Resort suggestions: move single-char entries to their lead variant ---
    magic_swaps = []  # (trigger, src_variant, dest_variant, output)
    for trigger, variants in magic_table.items():
        for v, val in variants.items():
            if len(val) == 1 and val.isalpha() and val in lead_variants:
                target_v = lead_variants[val]
                if target_v != v:
                    target_val = variants.get(target_v, '')
                    # Can move if target slot is empty
                    if not target_val:
                        magic_swaps.append((trigger, v, target_v, val))
                    # Can swap if target has a single-char that prefers our slot,
                    # or if we have a stronger lead count on the target variant
                    elif (len(target_val) == 1 and target_val.isalpha()
                          and target_val in lead_variants
                          and (lead_variants[target_val] == v
                               or lead_counts.get(val, 0) > lead_counts.get(target_val, 0))):
                        # Only add the swap once (from the first entry's perspective)
                        swap_key = tuple(sorted([(trigger, v, val), (trigger, target_v, target_val)]))
                        if not any((s[0], s[1]) == (swap_key[0][0], swap_key[0][1]) for s in magic_swaps):
                            magic_swaps.append((trigger, v, target_v, val))

    if magic_swaps:
        print("\n  Resort (move to lead variant):")
        for trigger, src_v, dest_v, output in sorted(magic_swaps):
            dest_val = magic_table[trigger].get(dest_v, '')
            if not dest_val:
                print(f"    {trigger}: {src_v}={output} → {dest_v} (empty)")
            else:
                print(f"    {trigger}: {src_v}={output} ↔ {dest_v}={dest_val} (swap)")

    if args.apply:
        apply_to_readme(add, keep, magic_remove, magic_add_new, magic_table, magic_swaps)


if __name__ == '__main__':
    main()
