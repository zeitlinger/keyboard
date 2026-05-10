#!/usr/bin/env python3

# [MISE] description="Suggest new adaptive key candidates based on corpus bigram analysis"

"""Find adaptive key candidates that resolve SFBs/scissors without introducing new ones.

See agents/suggest-adaptives.md for algorithm details.
"""

import argparse
import json
import re
import sys
from collections import Counter
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parents[2]))
from feel import (
    LAYOUT,
    COMBO_KEYS,
    MAGIC_POSITIONS,
    is_thumb,
    is_sfb,
    is_scissors,
    is_combo_adjacent,
    is_combo_preceded,
    is_combo_combo,
    is_bad,
    feel_score,
)  # noqa: E402

CORPUS = Path.home() / "source/genkey/corpora/shai-iweb.json"
README = Path(__file__).parents[2] / "README.md"

# Variant names as they appear in the Magic Keys table header.
# Keep this in sync with the physical slot map instead of hardcoding a width.
VARIANTS = tuple(sorted(MAGIC_POSITIONS))
ADAPTIVE_ROW_RE = re.compile(r"\|\s*(\w)\s*\|\s*(\w+)\s*\|\s*(\w)\s*\|")
MAGIC_ROW_RE = re.compile(r"^\|\s*(\w)\s*\|" + r"([^|]*)\|" * len(VARIANTS))
ALIGNMENT_CELL_RE = re.compile(r":?-+:?")


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
        if "## Adaptives" in line:
            in_table = True
            continue
        if in_table:
            if line.startswith("##"):
                break
            m = ADAPTIVE_ROW_RE.match(line)
            if m:
                trigger, key, output = m.group(1), m.group(2), m.group(3)
                if len(key) == 1:
                    existing[(trigger, key)] = output
                else:
                    compensation.add((trigger, output))
    return existing, compensation


def empty_magic_row():
    return {v: "" for v in VARIANTS}


def split_markdown_row(line):
    return [cell.strip() for cell in line.strip().strip("|").split("|")]


def is_alignment_row(line):
    cells = split_markdown_row(line)
    return bool(cells) and all(ALIGNMENT_CELL_RE.fullmatch(cell) for cell in cells)


def rewrite_markdown_row(template_line, cells):
    raw = template_line.rstrip("\n").strip()
    raw_cells = raw.strip("|").split("|")
    widths = [len(cell) for cell in raw_cells]
    padded = [
        f" {cell} ".center(width) if width > 0 else cell
        for cell, width in zip(cells, widths)
    ]
    return "|" + "|".join(padded) + "|\n"


def parse_multi_char_adaptives(lines):
    in_adaptives = False
    rows = []
    for line in lines:
        stripped = line.rstrip("\n")
        if stripped.startswith("## Adaptives"):
            in_adaptives = True
            continue
        if in_adaptives and stripped.startswith("## "):
            break
        if not in_adaptives:
            continue
        if m := ADAPTIVE_ROW_RE.match(stripped):
            if len(m.group(2)) > 1:
                rows.append((m.group(1), m.group(2), m.group(3)))
    return rows


def load_magic_table():
    """Parse the Magic Keys table.

    Returns:
        table: dict of trigger -> {'magic_a': val, ...}
        quoted: set of (trigger, variant) pairs that were explicitly quoted in README

    Values are unquoted plain strings. The reserved `magic` row (cross-magic suffixes)
    and the header row are skipped.
    """
    table = {}
    quoted = set()
    in_table = False
    for line in README.read_text().splitlines():
        if "## Magic Keys" in line:
            in_table = True
            continue
        if in_table:
            if line.startswith("##"):
                break
            m = MAGIC_ROW_RE.match(line)
            if m:
                trigger = m.group(1)
                table[trigger] = {
                    v: m.group(i + 2).strip().strip('"') for i, v in enumerate(VARIANTS)
                }
                for i, v in enumerate(VARIANTS):
                    raw = m.group(i + 2).strip()
                    if raw.startswith('"') and raw.endswith('"'):
                        quoted.add((trigger, v))
    return table, quoted


RIGHT_HAND_VARIANTS = tuple(v for v in VARIANTS if MAGIC_POSITIONS[v][0] >= 4)


def compute_lead_variants(magic_table):
    """For each single-char output letter, determine which right-hand magic column
    it appears on most. Left-hand variants (magic_c) are excluded — resort can only
    improve feel within the same hand, and right-hand triggers dominate.

    Returns:
        leads: dict of output_char → preferred variant (e.g. {'h': 'magic_b', 'd': 'magic_e'})
        lead_counts: dict of output_char → count on lead variant
    """
    counts = {}  # output -> Counter({variant: count})
    for trigger, variants in magic_table.items():
        for v, val in variants.items():
            if v not in RIGHT_HAND_VARIANTS:
                continue
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


def is_adaptive_recoverable(trigger, output, existing_adaptives, recommended_adaptives):
    """True if literal trigger+output can already be typed via another adaptive.

    Example: if o+o→e intercepts literal 'oo', but o+h→o exists, then 'oo' is
    still recoverable as physical o+h and needs no extra magic recovery.
    """
    for (a, physical), emitted in {
        **existing_adaptives,
        **recommended_adaptives,
    }.items():
        if a == trigger and physical != output and emitted == output:
            return True
    return False


MIN_FREQ_PCT = 0.01  # ignore bad bigrams below this frequency
MAX_MAGIC_SACRIFICE_PCT = (
    MIN_FREQ_PCT  # sacrifice bigrams below this can be covered by adding a magic entry
)
MAX_RECOMMEND_FEEL = 2  # only recommend adding adaptives with feel <= this
MAX_RECOMMEND_FF = 1.5  # reject candidates whose follow-through is awkward (ll → lly)
MAX_RECOMMEND_FF_COMBO = (
    2.0  # curated combo-second-key shapes can tolerate a bit more follow-through cost
)
DOUBLE_NERF = 1.0  # doubles get effective_freq = actual / DOUBLE_NERF (nerfs doubles vs other adaptives)


def slot_feel_score(trigger, variant):
    """Lower = better. Alt-hand always best. Same-hand scored by Manhattan
    distance — farther reach = worse feel. Pinky involvement adds penalty."""
    if trigger not in LAYOUT:
        return 1
    t_pos = LAYOUT[trigger]
    m_pos = MAGIC_POSITIONS[variant]
    if (t_pos[0] < 4) != (m_pos[0] < 4):
        return 0
    col_diff = abs(t_pos[0] - m_pos[0])
    row_diff = abs(t_pos[1] - m_pos[1])
    if col_diff == 0:
        return 99  # same column = SFB-like
    pinky = t_pos[0] in (0, 7) or m_pos[0] in (0, 7)
    return col_diff + row_diff + (1 if pinky else 0)


def combo_roll_feel(trigger, target):
    """Feel for using a combo key as adaptive physical target.

    Combo-row adaptives are only valid as same-hand rolls. They should still be
    scored separately from ordinary keys so we can distinguish acceptable rolls
    like n→p from worse outward/downward reaches like n→b.
    """
    base = feel_score(trigger, target, combo_target_penalty=False)
    t_pos = LAYOUT[trigger]
    c_pos = LAYOUT[target]
    same_hand = (t_pos[0] < 4) == (c_pos[0] < 4)
    if not same_hand:
        return 99
    # Home/top into an outward lower combo is noticeably worse than the
    # corresponding top-combo motion, e.g. n→b is bad while n→p is acceptable.
    if c_pos[1] > t_pos[1] and c_pos[0] < t_pos[0] and abs(c_pos[0] - t_pos[0]) == 1:
        base += 1
    return base


def is_allowed_combo_adaptive_target(trigger, target):
    """Curated combo-second-key shapes that are acceptable for new adaptives."""
    if target not in COMBO_KEYS:
        return False
    t_pos = LAYOUT[trigger]
    c_pos = LAYOUT[target]
    if (t_pos[0] < 4) != (c_pos[0] < 4):
        return False
    if abs(t_pos[0] - c_pos[0]) != 1:
        return False
    return (t_pos[1], c_pos[1]) == (2, 1) or (t_pos[1], c_pos[1]) == (4, 3)


def is_bad_chars(a_char, b_char):
    return (
        is_bad(LAYOUT[a_char], LAYOUT[b_char])
        or is_combo_adjacent(a_char, b_char)
        or is_combo_preceded(a_char, b_char)
        or is_combo_combo(a_char, b_char)
    )


def bad_reason(a, b):
    if is_sfb(a, b):
        return f"SFB col {a[0]}"
    if is_scissors(a, b):
        return "scissors"
    return ""


def bad_reason_chars(a_char, b_char):
    if a_char == b_char:
        return "double"
    r = bad_reason(LAYOUT[a_char], LAYOUT[b_char])
    if r:
        return r
    if is_combo_adjacent(a_char, b_char):
        return "combo-adjacent"
    if is_combo_preceded(a_char, b_char):
        return "combo-preceded"
    if is_combo_combo(a_char, b_char):
        return "combo-combo"
    return ""


def apply_to_readme(
    add, keep, magic_remove, magic_add_new, magic_table, quoted_magic, magic_swaps=None
):
    """Apply recommended adaptive and magic key changes to README.md."""
    lead_variants, lead_counts = compute_lead_variants(magic_table)
    content = README.read_text()
    lines = content.splitlines(keepends=True)

    # Build new adaptive table rows (add + keep, sorted)
    all_adaptives = sorted(set(add) | set(keep))
    multi_char_adaptives = parse_multi_char_adaptives(lines)

    def fmt_adaptive_row(a, c, b):
        return f"|     {a}     |  {c}  |   {b}    |\n"

    def fmt_adaptive_rule():
        return "| :-------: | :-: | :----: |\n"

    # Build working magic table: original → apply removes → apply adds
    working_magic = {t: dict(variants) for t, variants in magic_table.items()}

    for (trigger, variant), _output in magic_remove.items():
        working_magic.setdefault(trigger, empty_magic_row())[variant] = ""

    for (trigger, output), _reason in sorted(magic_add_new.items()):
        row = working_magic.get(trigger, empty_magic_row())
        free = [v for v in VARIANTS if not row.get(v)]
        lead_v = lead_variants.get(output)
        if free:
            if lead_v in free and slot_feel_score(trigger, lead_v) == 0:
                best = lead_v
            else:
                best = min(free, key=lambda v: slot_feel_score(trigger, v))
            working_magic.setdefault(trigger, empty_magic_row())
            working_magic[trigger][best] = output
        else:
            val_to_variants = {}
            for v in VARIANTS:
                val = row.get(v, "")
                if val:
                    val_to_variants.setdefault(val, []).append(v)
            replaced = False
            for val, variants_list in val_to_variants.items():
                if len(variants_list) >= 2:
                    variants_by_feel = sorted(
                        variants_list, key=lambda v: slot_feel_score(trigger, v)
                    )
                    drop_v = variants_by_feel[-1]
                    working_magic[trigger][drop_v] = output
                    replaced = True
                    break
            if not replaced:
                print(
                    f"WARNING: no magic slot for {trigger} → {output}, skipping",
                    file=sys.stderr,
                )

    # Apply lead-variant swaps
    for trigger, src_v, dest_v, output in magic_swaps or []:
        row = working_magic.get(trigger, empty_magic_row())
        row[src_v], row[dest_v] = row[dest_v], row[src_v]
        working_magic[trigger] = row

    def fmt_magic_val(trigger, variant, val):
        if not val:
            return ""
        if (trigger, variant) in quoted_magic:
            return f'"{val}"'
        return val

    def fmt_magic_row(template_line, trigger, variants):
        cells = [trigger] + [
            fmt_magic_val(trigger, v, variants.get(v, "")) for v in VARIANTS
        ]
        return rewrite_markdown_row(template_line, cells)

    # Rewrite file
    new_lines = []
    section = None
    adaptive_header_done = False

    for line in lines:
        stripped = line.rstrip("\n")

        if stripped.startswith("## Magic Keys"):
            section = "magic"
            new_lines.append(line)
            continue
        elif stripped.startswith("## Adaptives"):
            section = "adaptives"
            adaptive_header_done = False
            new_lines.append(line)
            continue
        elif stripped.startswith("## "):
            section = None
            new_lines.append(line)
            continue

        if section == "magic":
            m = MAGIC_ROW_RE.match(stripped)
            if m and len(m.group(1)) == 1:
                trigger = m.group(1)
                if trigger in working_magic:
                    current_variants = {
                        v: m.group(i + 2).strip().strip('"')
                        for i, v in enumerate(VARIANTS)
                    }
                    if current_variants == working_magic[trigger]:
                        new_lines.append(line)
                    else:
                        new_lines.append(
                            fmt_magic_row(line, trigger, working_magic[trigger])
                        )
                    continue
            new_lines.append(line)
            continue

        if section == "adaptives":
            if is_alignment_row(stripped):
                new_lines.append(fmt_adaptive_rule())
                # Merge and sort all adaptive rows together
                all_rows = sorted(set(all_adaptives) | set(multi_char_adaptives))
                for a, c, b in all_rows:
                    new_lines.append(fmt_adaptive_row(a, c, b))
                adaptive_header_done = True
                continue
            elif adaptive_header_done:
                if stripped.startswith("|"):
                    continue  # skip old data rows (already rewritten above)
                new_lines.append(line)
                continue
            else:
                new_lines.append(line)
                continue

        new_lines.append(line)

    README.write_text("".join(new_lines))
    print(f"Applied changes to {README}")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--apply", action="store_true", help="Apply recommended changes to README.md"
    )
    args = parser.parse_args()

    existing, compensation = load_existing_adaptives()
    existing_physical = {
        (trigger, output): key for (trigger, key), output in existing.items()
    }
    magic_table, quoted_magic = load_magic_table()
    magic_covered = load_magic_coverage(magic_table)

    with open(CORPUS) as f:
        corpus = json.load(f)

    bigrams = corpus["bigrams"]
    trigrams = corpus["trigrams"]
    total = corpus["Total"]  # total characters, matching genkey's denominator

    def pct(count):
        return count / total * 100

    # --- Bad bigrams ---
    bad = []
    for a in LAYOUT:
        for b in LAYOUT:
            if is_bad_chars(a, b):
                freq = bigrams.get(f"{a}{b}", 0)
                if freq > 0:
                    bad.append((a, b, freq))

    bad = [(a, b, freq) for a, b, freq in bad if pct(freq) >= MIN_FREQ_PCT]

    def effective_gain(a, b, freq):
        return freq / DOUBLE_NERF if a == b else freq

    # Include existing adaptives' target bigrams so they can compete for slots
    # on equal footing with current bad bigrams (user-curated choices matter).
    bad_keys = {(a, b) for a, b, _ in bad}
    for (a, c), b in existing.items():
        if (a, b) not in bad_keys:
            freq = bigrams.get(f"{a}{b}", 0)
            if freq > 0:
                bad.append((a, b, freq))
                bad_keys.add((a, b))

    bad.sort(key=lambda x: -effective_gain(*x))
    recommendable_bad = [(a, b, freq) for a, b, freq in bad if a != b]
    doubled_bigrams = [(a, b, freq) for a, b, freq in bad if a == b]

    print("=== Bad Bigrams (SFB / scissors / combo-adjacent) ===\n")
    for a, b, freq in bad:
        print(f"  {a}{b}  {pct(freq):.3f}%  {bad_reason_chars(a, b)}")

    if doubled_bigrams:
        print(
            "\n=== Doubled Letters (reported only; not recommended automatically) ===\n"
        )
        for a, b, freq in doubled_bigrams:
            print(f"  {a}{b}  {pct(freq):.3f}%  {bad_reason_chars(a, b)}")

    # --- Adaptive candidates for bad bigrams ---
    print("\n=== Adaptive Candidates for Bad Bigrams ===")

    # all_candidates[(a, b)] = [(c, sacrifice, bad_following, feel), ...] sorted
    all_candidates = {}

    for a, b, bigram_freq in recommendable_bad:
        print(
            f"\nBigram '{a}{b}' ({pct(bigram_freq):.3f}%) — {bad_reason_chars(a, b)}:"
        )

        followers = sorted(
            [
                (tg, cnt)
                for tg, cnt in trigrams.items()
                if len(tg) == 3 and tg[0] == a and tg[1] == b
            ],
            key=lambda x: -x[1],
        )[:5]

        candidates = []
        for c in LAYOUT:
            if c in (a, b):
                continue
            combo_roll = c in COMBO_KEYS
            if combo_roll:
                if not is_allowed_combo_adaptive_target(a, c):
                    continue
            elif is_bad(LAYOUT[a], LAYOUT[c]) or is_combo_preceded(a, c):
                continue  # combo-adjacent handled by feel_score, not filtered here
            sacrifice = bigrams.get(f"{a}{c}", 0)
            # Sacrifice is acceptable if the bad bigram can be typed via magic,
            # OR if this is an existing adaptive whose trigger+physical pair already
            # has a recovery magic key (happens after --apply on a re-run).
            is_existing = (a, c) in existing
            magic_free = (
                (a, b) in magic_covered or (is_existing and (a, c) in magic_covered)
            ) and pct(sacrifice) < MAX_MAGIC_SACRIFICE_PCT
            # Gain must be >= 2x sacrifice — magic recovery is harder to type
            # than the intercepted sequence, so net-positive alone isn't enough.
            if not magic_free and sacrifice * 2 >= bigram_freq:
                continue

            def follower_physical_key(follower_output):
                return existing_physical.get((b, follower_output), follower_output)

            physical_followers = [
                (follower_physical_key(tg[2]), cnt)
                for tg, cnt in followers
                if tg[2] in LAYOUT and follower_physical_key(tg[2]) in LAYOUT
            ]
            bad_following = sum(
                1
                for follower_key, _ in physical_followers
                if is_bad_chars(c, follower_key)
            )
            # Weighted following-feel: captures awkward-but-not-bad motions (e.g. 'h→y' in 'lly').
            weight_total = sum(cnt for _, cnt in physical_followers) or 1
            # Strip combo-target penalty: the follower key here is the physical key
            # actually pressed after b, after resolving any existing b+output adaptive.
            following_feel = (
                sum(
                    feel_score(c, follower_key, combo_target_penalty=False) * cnt
                    for follower_key, cnt in physical_followers
                )
                / weight_total
            )
            feel = combo_roll_feel(a, c) if combo_roll else feel_score(a, c)
            same_hand = (LAYOUT[a][0] < 4) == (LAYOUT[c][0] < 4)
            candidates.append(
                (
                    c,
                    sacrifice,
                    bad_following,
                    feel,
                    same_hand,
                    magic_free,
                    following_feel,
                )
            )

        # Rank primarily by motion quality. If sacrifice can be recovered by magic,
        # tiny corpus deltas are mostly moot, so prefer cleaner physical motion and
        # follow-through over a slightly smaller intercepted bigram.
        # Otherwise include sacrifice as the primary cost.
        FEEL_COST = 0.005 * total / 100  # 0.005% of corpus per feel level

        def candidate_sort_key(candidate):
            (
                c,
                sacrifice,
                bad_following,
                feel,
                _same_hand,
                magic_free,
                following_feel,
            ) = candidate
            a_pos, c_pos = LAYOUT[a], LAYOUT[c]
            row_diff = abs(a_pos[1] - c_pos[1])
            col_diff = abs(a_pos[0] - c_pos[0])
            motion_tier = 2
            if row_diff == 0:
                motion_tier = 0
            elif is_thumb(c_pos):
                motion_tier = 1
            if magic_free:
                return (
                    feel,
                    motion_tier,
                    row_diff,
                    bad_following,
                    following_feel,
                    col_diff,
                    sacrifice,
                )
            return (
                sacrifice + FEEL_COST * feel,
                motion_tier,
                row_diff,
                bad_following,
                following_feel,
                col_diff,
            )

        candidates.sort(key=candidate_sort_key)

        if not candidates:
            print("  (no candidates)")
        else:
            all_candidates[(a, b)] = (
                candidates  # full sorted list for conflict resolution
            )
            for (
                c,
                sacrifice,
                bad_following,
                feel,
                _,
                mfree,
                following_feel,
            ) in candidates[:50]:
                marker = " *" if (a, c) in existing else ""
                follower_str = (
                    f"{bad_following}/{len(followers)}" if followers else "n/a"
                )
                sac_str = f"{pct(sacrifice):.3f}%" + (" (magic)" if mfree else "")
                print(
                    f"  {a} + {c} → {b}   feel={feel}  sacrifice '{a}{c}' {sac_str}"
                    f"   following-bad: {follower_str}  ff={following_feel:.2f}{marker}"
                )

    # --- Combo-roll adaptive opportunities ---
    print("\n=== Combo-Roll Adaptive Opportunities ===")
    print("(bad bigrams resolvable by rolling trigger→combo-key)\n")

    combo_hits = []
    for a, b, bigram_freq in recommendable_bad:
        followers = sorted(
            [
                (tg, cnt)
                for tg, cnt in trigrams.items()
                if len(tg) == 3 and tg[0] == a and tg[1] == b
            ],
            key=lambda x: -x[1],
        )[:5]

        for c in COMBO_KEYS:
            if c in (a, b):
                continue
            if not is_allowed_combo_adaptive_target(a, c):
                continue
            sacrifice = bigrams.get(f"{a}{c}", 0)
            if sacrifice * 2 >= bigram_freq:
                continue
            bad_following = sum(
                1 for tg, _ in followers if tg[2] in LAYOUT and is_bad_chars(c, tg[2])
            )
            combo_hits.append(
                (a, c, b, bigram_freq, sacrifice, bad_following, len(followers))
            )

    combo_hits.sort(key=lambda x: (-x[3], x[5], x[4]))

    for a, c, b, bigram_freq, sacrifice, bad_following, n_followers in combo_hits:
        marker = " *" if (a, c) in existing else ""
        follower_str = f"{bad_following}/{n_followers}" if n_followers else "n/a"
        reason = bad_reason_chars(a, b)
        print(
            f"  {a} + {c} → {b}   [{reason} {pct(bigram_freq):.3f}%]"
            f"   sacrifice '{a}{c}' {pct(sacrifice):.3f}%   following-bad: {follower_str}{marker}"
        )

    # --- Recommended changes (greedy assignment) ---
    # Assign candidates greedily by effective-gain order; fall back when (a, c)
    # is already claimed. Existing adaptives compete normally and can be displaced
    # if a higher-value output wants the same slot.
    bad_freq = {(a, b): freq for a, b, freq in recommendable_bad}
    recommended = {}  # (trigger, physical) -> output
    # Existing adaptives already cover these outputs; don't propose duplicates
    # on a different physical key unless we are explicitly remapping/replacing.
    recommended_outputs = {
        (a, b) for (a, _c), b in existing.items()
    }  # (trigger, output)
    for a, b, _ in recommendable_bad:  # already sorted by frequency descending
        if (a, b) in recommended_outputs:
            continue
        candidates_list = all_candidates.get((a, b), [])

        # Higher effective-gain bigrams claim slots first (doubles nerfed by DOUBLE_NERF);
        # existing adaptives for lower-gain outputs naturally lose the slot via iteration order.
        for c, _, _, feel, _, _, ff in candidates_list:
            ff_limit = MAX_RECOMMEND_FF_COMBO if c in COMBO_KEYS else MAX_RECOMMEND_FF
            if feel > MAX_RECOMMEND_FEEL or ff > ff_limit:
                continue
            if c in COMBO_KEYS and feel > 1:
                continue
            if (a, c) in recommended:
                continue  # already claimed this run
            recommended[(a, c)] = b
            recommended_outputs.add((a, b))
            break

    # Build index: for each (trigger, output), which physical key is recommended?
    recommended_physical = {}  # (a, b) -> c
    for (a, c), b in recommended.items():
        recommended_physical[(a, b)] = c

    def existing_superseded(a, c, b):
        """True if a different candidate was recommended for the same (trigger, output)."""
        c_new = recommended_physical.get((a, b))
        if c_new is None or c_new == c:
            return False
        by_key = {cand[0]: cand for cand in all_candidates.get((a, b), [])}
        if c not in by_key:
            return False  # existing key was a deliberate user choice outside valid candidates
        if c in COMBO_KEYS:
            return False  # preserve existing combo-roll choices unless their slot is reused
        old_cand = by_key[c]
        new_cand = by_key.get(c_new)
        if new_cand is None:
            return False
        old_feel = old_cand[3]
        new_feel = new_cand[3]
        return new_feel < old_feel

    def slot_displaced(a, c, b):
        """True if (a, c) slot was reassigned to a different output by a higher-freq bigram."""
        new_b = recommended.get((a, c))
        return new_b is not None and new_b != b

    # Only remove existing adaptives that are superseded (better-feel alternative for same
    # output) or displaced (slot reassigned to a higher-gain bigram). Respect user choices
    # even for bigrams that don't match is_bad_chars — they were deliberate.
    remove = [
        (a, c, b)
        for (a, c), b in existing.items()
        if existing_superseded(a, c, b) or slot_displaced(a, c, b)
    ]

    remove_set = {(a, c) for a, c, _ in remove}
    keep = [(a, c, b) for (a, c), b in existing.items() if (a, c) not in remove_set]
    # Only truly lost adaptives free their recovery magic. Remapped slots still
    # intercept physical a+c, so the recovery entry is still needed.
    lost_pairs = {
        (a, c)
        for a, c, b in remove
        if not ((a, c) in recommended and recommended[(a, c)] != b)
    }

    def build_magic_plan(
        current_recommended, current_keep, current_remove, current_lost_pairs
    ):
        """Build magic add/remove/keep decisions from the finalized adaptive state."""
        covered_outputs = set()  # (trigger, output) pairs covered by add+keep adaptives
        for (a, _c), b in current_recommended.items():
            covered_outputs.add((a, b))
        for a, _c, b in current_keep:
            covered_outputs.add((a, b))

        magic_add = {}  # (trigger, output) -> reason
        for a, b, bigram_freq in recommendable_bad:
            if (a, b) in covered_outputs:
                continue
            acceptable = [
                cand
                for cand in all_candidates.get((a, b), [])
                if cand[3] <= MAX_RECOMMEND_FEEL
                and cand[6]
                <= (
                    MAX_RECOMMEND_FF_COMBO
                    if cand[0] in COMBO_KEYS
                    else MAX_RECOMMEND_FF
                )
            ]
            if not acceptable:
                best_feel = min(
                    (cand[3] for cand in all_candidates.get((a, b), [])), default=999
                )
                magic_add[(a, b)] = (
                    f"bad bigram '{a}{b}' {pct(bigram_freq):.3f}%, best adaptive feel={best_feel}"
                )

        for (a, c), b in current_recommended.items():
            if (a, c) in existing:
                continue
            sacrifice = bigrams.get(f"{a}{c}", 0)
            if (
                sacrifice > 0
                and (a, c) not in magic_covered
                and (a, c) not in compensation
                and not is_adaptive_recoverable(a, c, existing, current_recommended)
            ):
                magic_add.setdefault(
                    (a, c),
                    f"recovery: '{a}{c}' intercepted by {a}+{c}→{b} adaptive ({pct(sacrifice):.3f}%)",
                )

        for a, c, b in current_keep:
            sacrifice = bigrams.get(f"{a}{c}", 0)
            if (
                sacrifice > 0
                and (a, c) not in magic_covered
                and (a, c) not in compensation
                and not is_adaptive_recoverable(a, c, existing, current_recommended)
            ):
                magic_add.setdefault(
                    (a, c),
                    f"recovery: '{a}{c}' intercepted by existing {a}+{c}→{b} adaptive ({pct(sacrifice):.3f}%)",
                )

        magic_remove = {}  # (trigger, variant) -> output
        orphaned_removed_outputs = {
            (a, b)
            for a, _c, b in current_remove
            if (a, b) not in covered_outputs and (a, b) not in magic_add
        }
        for trigger, variants in magic_table.items():
            for variant, val in variants.items():
                if (
                    len(val) == 1
                    and val.isalpha()
                    and (trigger, val) in covered_outputs
                ):
                    magic_remove[(trigger, variant)] = val
                elif (
                    len(val) == 1
                    and val.isalpha()
                    and (trigger, val) in orphaned_removed_outputs
                ):
                    magic_remove[(trigger, variant)] = val
                elif (trigger, val) in current_lost_pairs and (
                    trigger,
                    val,
                ) not in magic_add:
                    magic_remove[(trigger, variant)] = val

        effective_magic_table = {
            t: {v: val for v, val in variants.items() if (t, v) not in magic_remove}
            for t, variants in magic_table.items()
        }
        magic_remove_pairs = {(t, val) for (t, v), val in magic_remove.items()}

        magic_keep = {}
        for a, b, _ in recommendable_bad:
            for cand in all_candidates.get((a, b), []):
                c, _sacrifice, _bad_following, _feel, _same_hand, mfree, _ff = cand
                if (
                    mfree
                    and (a, c) in current_recommended
                    and current_recommended[(a, c)] == b
                    and (a, b) not in magic_remove_pairs
                ):
                    magic_keep.setdefault((a, b), []).append(f"{a}+{c}→{b}")

        return magic_add, magic_remove, effective_magic_table, magic_keep

    # --- Pre-compute magic slot availability before printing adaptives ---
    magic_add, magic_remove, effective_magic_table, magic_keep = build_magic_plan(
        recommended, keep, remove, lost_pairs
    )

    lead_variants, lead_counts = compute_lead_variants(magic_table)

    def best_magic_slot(trigger, output=None):
        """Return (variant, replace_note) for the best available slot.

        Lead variant is preferred only when it costs no feel (slot_feel_score == 0).
        Otherwise pick the minimum-feel free slot.
        Returns (variant, None) for free slot, (variant, 'replace Magic X=val') for duplicate.
        Returns None if no slot can be found.
        """
        lead_v = lead_variants.get(output) if output else None
        row = effective_magic_table.get(trigger, {})
        free = [v for v in VARIANTS if not row.get(v)]
        if free:
            if lead_v in free and slot_feel_score(trigger, lead_v) == 0:
                return (lead_v, None)
            best = min(free, key=lambda v: slot_feel_score(trigger, v))
            return (best, None)
        # Look for duplicate values — one can be dropped to free a slot
        val_to_variants = {}
        for v in VARIANTS:
            val = row.get(v, "")
            if val:
                val_to_variants.setdefault(val, []).append(v)
        for val, variants in val_to_variants.items():
            if len(variants) >= 2:
                # Keep the better-feel one, free the worse one
                variants_by_feel = sorted(
                    variants, key=lambda v: slot_feel_score(trigger, v)
                )
                keep_v, drop_v = variants_by_feel[0], variants_by_feel[-1]
                return (drop_v, f"replace {drop_v}={val} (dup of {keep_v})")
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

    # Existing occupied slots are deliberate choices. Do not steal one for a
    # lower-value output just because the greedy pass found a cheaper physical
    # path for the existing output elsewhere (e.g. keep o+h→o over o+h→e).
    for (a, c), old_b in existing.items():
        new_b = recommended.get((a, c))
        if new_b is None or new_b == old_b:
            continue
        old_gain = bad_freq.get((a, old_b), bigrams.get(f"{a}{old_b}", 0))
        new_gain = bad_freq.get((a, new_b), bigrams.get(f"{a}{new_b}", 0))
        if old_gain >= new_gain:
            del recommended[(a, c)]
            recommended_outputs.discard((a, new_b))

    remove = [
        (a, c, b)
        for (a, c), b in existing.items()
        if existing_superseded(a, c, b) or slot_displaced(a, c, b)
    ]
    remove_set = {(a, c) for a, c, _ in remove}
    keep = [(a, c, b) for (a, c), b in existing.items() if (a, c) not in remove_set]
    lost_pairs = {
        (a, c)
        for a, c, b in remove
        if not ((a, c) in recommended and recommended[(a, c)] != b)
    }

    # Include slots whose output differs from existing (displacement of lower-freq adaptive).
    add = [(a, c, b) for (a, c), b in recommended.items() if existing.get((a, c)) != b]

    # Rebuild magic decisions from the finalized adaptive state. The earlier pass
    # is only for slot-availability checks during pruning.
    magic_add, magic_remove, effective_magic_table, magic_keep = build_magic_plan(
        recommended, keep, remove, lost_pairs
    )

    # Drop recovery magic entries for removed adaptives
    no_recovery_pairs = {(a, c) for a, c in no_recovery}
    magic_add_new = {
        k: v
        for k, v in magic_add.items()
        if k not in magic_covered and k not in no_recovery_pairs
    }
    magic_add_exists = {k: v for k, v in magic_add.items() if k in magic_covered}

    # --- Print adaptive recommendations ---
    print("\n=== Recommended Changes ===\n")

    if add:
        print("Add:")
        for a, c, b in sorted(add):
            gained = bad_freq.get((a, b), 0)
            paid = bigrams.get(f"{a}{c}", 0)
            print(
                f"  {a} + {c} → {b}   gain {pct(gained):.3f}%  paid {pct(paid):.3f}%  net {pct(gained - paid):+.3f}%"
            )
    else:
        print("Add: (none)")

    if keep:
        print("\nKeep (existing, still justified):")
        for a, c, b in sorted(keep):
            print(f"  {a} + {c} → {b}")

    lost = [(a, c, b) for a, c, b in remove if (a, c) in lost_pairs]
    remapped = [(a, c, b) for a, c, b in remove if (a, c) not in lost_pairs]

    def fmt_removed(a, c, b):
        gained = bad_freq.get((a, b), bigrams.get(f"{a}{b}", 0))
        paid = bigrams.get(f"{a}{c}", 0)
        return f"  {a} + {c} → {b}   gain {pct(gained):.3f}%  paid {pct(paid):.3f}%  net {pct(gained - paid):+.3f}%"

    if remapped:
        print("\nRemapped (slot reused for different output):")
        for a, c, b in sorted(remapped):
            new_b = recommended[(a, c)]
            new_gain = bad_freq.get((a, new_b), 0)
            old_gain = bad_freq.get((a, b), bigrams.get(f"{a}{b}", 0))
            delta = new_gain - old_gain
            print(
                f"{fmt_removed(a, c, b)}   → now {a}+{c}→{new_b}  Δgain {pct(delta):+.3f}%"
            )

    if lost:
        print("\nLost (slot freed, bigram falls to magic):")
        for a, c, b in sorted(lost):
            print(fmt_removed(a, c, b))

    if not remove:
        print("\nRemove: (none)")

    # --- Print magic recommendations ---
    print("\n=== Magic Keys Recommended Changes ===\n")

    if no_recovery:
        print("Skipped (no magic recovery slot):")
        for (a, c), b in sorted(no_recovery.items()):
            row = magic_table.get(a, {})
            taken = ", ".join(f"{v}={row[v]}" for v in VARIANTS if row.get(v))
            print(f"  {a} + {c} → {b}   (magic {a}: {taken})")
        print()

    if magic_add_new:
        print("Add:")
        for (trigger, output), reason in sorted(magic_add_new.items()):
            result = best_magic_slot(trigger, output)
            if result:
                variant, note = result
                slot_str = f" → {variant}" + (f" ({note})" if note else "")
            else:
                row = effective_magic_table.get(trigger, {})
                taken = ", ".join(f"{v}={row[v]}" for v in VARIANTS if row.get(v))
                slot_str = f" (no free slot: {taken})"
            print(f"  {trigger} → {output}{slot_str}   [{reason}]")
    else:
        print("Add: (none)")

    if magic_remove:
        print("\nRemove (now served by adaptive):")
        by_trigger = {}
        for (trigger, variant), output in sorted(magic_remove.items()):
            by_trigger.setdefault(trigger, []).append(f"{variant}={output}")
        for trigger, entries in sorted(by_trigger.items()):
            print(f"  {trigger}: {', '.join(entries)}")

    if magic_keep:
        print("\nKeep (relied on by adaptive recommendations):")
        by_variant = {v: [] for v in VARIANTS}
        for (trigger, output), adaptives in sorted(magic_keep.items()):
            row = magic_table.get(trigger, {})
            for v in VARIANTS:
                if row.get(v) == output:
                    by_variant[v].append((trigger, output, adaptives))
        for variant in VARIANTS:
            entries = by_variant[variant]
            if entries:
                print(f"  {variant}:")
                for trigger, output, adaptives in entries:
                    print(
                        f"    {trigger} → {output}   [enables {', '.join(adaptives)}]"
                    )

    if magic_add_exists:
        print("\nAlready in table (add section covered):")
        for (trigger, output), reason in sorted(magic_add_exists.items()):
            print(f"  {trigger} → {output}   [{reason}]")

    # --- Current magic table grouped by variant ---
    print("\n=== Current Magic Table (single-char, by variant) ===\n")
    for variant in VARIANTS:
        entries = []
        for trigger in sorted(magic_table):
            val = magic_table[trigger].get(variant, "")
            if len(val) == 1 and val.isalpha():
                entries.append(f"{trigger}→{val}")
        if entries:
            print(f"  {variant}: {', '.join(entries)}")

    # --- Lead magic per trigger key ---
    print("\n=== Lead Magic per Output Key ===\n")
    output_variants: dict[str, set[str]] = {}
    for trigger, variants in magic_table.items():
        for v, val in variants.items():
            if v not in RIGHT_HAND_VARIANTS:
                continue
            if len(val) == 1 and val.isalpha() and val not in COMBO_KEYS:
                output_variants.setdefault(val, set()).add(v)
    for letter in sorted(output_variants):
        used = ", ".join(v for v in VARIANTS if v in output_variants[letter])
        print(f"  {letter}: {used}")

    # --- Resort suggestions: move single-char entries to their lead variant ---
    magic_swaps = []  # (trigger, src_variant, dest_variant, output)
    for trigger, variants in magic_table.items():
        for v, val in variants.items():
            if len(val) == 1 and val.isalpha() and val in lead_variants:
                target_v = lead_variants[val]
                if target_v != v:
                    # Don't resort away from a better-feel slot (e.g. alt-hand feel=0).
                    src_feel = slot_feel_score(trigger, v)
                    dest_feel = slot_feel_score(trigger, target_v)
                    if dest_feel >= src_feel:
                        continue
                    target_val = variants.get(target_v, "")
                    # Can move if target slot is empty
                    if not target_val:
                        magic_swaps.append((trigger, v, target_v, val))
                    # Can swap if target has a single-char that prefers our slot,
                    # or if we have a stronger lead count on the target variant
                    elif (
                        len(target_val) == 1
                        and target_val.isalpha()
                        and target_val in lead_variants
                        and (
                            lead_variants[target_val] == v
                            or lead_counts.get(val, 0) > lead_counts.get(target_val, 0)
                        )
                    ):
                        # Only add the swap once (from the first entry's perspective)
                        swap_key = tuple(
                            sorted([(trigger, v, val), (trigger, target_v, target_val)])
                        )
                        if not any(
                            (s[0], s[1]) == (swap_key[0][0], swap_key[0][1])
                            for s in magic_swaps
                        ):
                            magic_swaps.append((trigger, v, target_v, val))

    if magic_swaps:
        print("\n  Resort (move to lead variant):")
        for trigger, src_v, dest_v, output in sorted(magic_swaps):
            dest_val = magic_table[trigger].get(dest_v, "")
            if not dest_val:
                print(f"    {trigger}: {src_v}={output} → {dest_v} (empty)")
            else:
                print(f"    {trigger}: {src_v}={output} ↔ {dest_v}={dest_val} (swap)")

    if args.apply:
        apply_to_readme(
            add,
            keep,
            magic_remove,
            magic_add_new,
            magic_table,
            quoted_magic,
            magic_swaps,
        )


if __name__ == "__main__":
    main()
