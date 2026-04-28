# Suggest Adaptives — Agent Brief

See [design-philosophy.md](design-philosophy.md) for layout key positions, motion quality rules, and corpus location.

## Goal

Find new adaptive key candidates that:

1. Resolve a bad motion (SFB, scissors, or same-key double) in a common bigram
2. Don't sacrifice a common physical bigram (the trigger+adaptive_key pair)
3. Don't introduce new SFBs on the following keypress

Same-key double case: bigram `(a, a)` like "ll". Adaptive `a + c → a` means typing "ac" produces "aa" (first `a` already in buffer, physical `c` replaced with `a`). Avoids same-finger double-tap.

## How Adaptives Work

`trigger` + `physical_key` → `output` (instead of physical_key's normal character)

Existing: `n` + `h` → `g` (typing "nh" outputs "ng", avoiding the n↔l SFB for "ng" ... actually n and g are both col 2, so this resolves that SFB).

## Algorithm

For each bigram `(a, b)` sorted by frequency where `motion(a→b)` is bad (SFB, scissors, or `a == b` double):

1. Find candidate physical keys `c` where:
   - `c ≠ a`, `c ≠ b`, `c` is a single-key letter (not combo-only)
   - `motion(a→c)` is good (not SFB, not scissors)
   - `freq(a, c)` is low — not breaking a common bigram (heuristic: < 10% of `freq(a, b)`)
2. For each candidate `c`, count following-SFBs:
   - From trigrams `"a b x"` (top 5 by freq), check if `motion(c→x_key)` is bad
3. Rank by: fewer following-SFBs first, lower `freq(a,c)` sacrifice second

## Implementation

**File:** `suggest_adaptives.py`
**Run:** `mise run suggest-adaptives` (or `python3 suggest_adaptives.py`)

**Output format (one block per bad bigram):**

```text
Bigram 'ua' (0.508%) — SFB (both col 4, R.Index)
  u + e → a  sacrifice 'ue' (0.104%)  following-bad: 0/5
  u + o → a  sacrifice 'uo' (0.001%)  following-bad: 1/5

Bigram 'll' (0.423%) — double (same key)
  l + r → l  sacrifice 'lr' (0.02%)   following-bad: 0/5
```
