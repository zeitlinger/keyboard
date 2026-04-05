# Layout Design Facts (AI reference)

## Hardware

- Ferris Sweep, 34 keys, 17/hand, inner columns unused → effectively 14/hand
- Kailh Choc Light Blue (gChoc), 20gf linear — enables vertical combos
- 10° tent, -10° negative tilt, wrist rests

## Key Position Preference

Row comfort (best→worst): home (1) > bottom (2) > top (0). No inner columns.
Top row: middle + ring finger OK; index + pinky avoid (use combos instead).
Bottom row preferred over top row (curl vs. stretch).

## Base Layout (8 columns, row/col 0-indexed)

Col 0-3 = left hand (pinky→index), col 4-7 = right hand (index→pinky).
Row 0 = top, 1 = home, 2 = bottom, 3 = thumb.

| Char | Col | Row | Finger     |
|------|-----|-----|------------|
| s    | 0   | 1   | L. Pinky   |
| c    | 1   | 1   | L. Ring    |
| n    | 2   | 1   | L. Middle  |
| t    | 3   | 1   | L. Index   |
| a    | 4   | 1   | R. Index   |
| e    | 5   | 1   | R. Middle  |
| i    | 6   | 1   | R. Ring    |
| h    | 7   | 1   | R. Pinky   |
| f    | 1   | 2   | L. Ring    |
| l    | 2   | 2   | L. Middle  |
| d    | 3   | 2   | L. Index   |
| u    | 4   | 2   | R. Index   |
| o    | 5   | 2   | R. Middle  |
| y    | 6   | 2   | R. Ring    |
| x    | 1   | 0   | L. Ring    |
| w    | 2   | 0   | L. Middle  |
| r    | 3   | 3   | L. Index (thumb) |

Letters only via combo (not single-key): j, b, g, k, p, m, v, q, z

**Combo keys** — vertical combos (home+top or home+bottom on the same finger). Approximate positions:

| Char | Col | Row | Combo           |
|------|-----|-----|-----------------|
| p    | 1   | 0   | L. Ring top     |
| b    | 1   | 2   | L. Ring bottom  |
| m    | 2   | 0   | L. Middle top   |
| g    | 2   | 2   | L. Middle bottom|
| v    | 3   | 0   | L. Index top    |
| k    | 3   | 2   | L. Index bottom |

The "combo row" (p, m, v across cols 1-2-3 at row 0, or b, g, k at row 2) forms natural inward rolls on the left hand. These are valid adaptive physical keys and can be used as adaptive triggers.

## Physical Keyboard Geometry (Ferris Sweep)

The Ferris Sweep has **aggressive columnar stagger** — each column sits at a different height matching natural finger lengths. This means grid distance understates actual physical movement for cross-column+cross-row transitions:

- **Pinky column (col 0) sits lowest**, ring (col 1) higher, middle (col 2) highest on the left hand.
- A move like `s` (pinky home) → `x` (ring top) feels much longer than one grid step because the stagger already raises the ring column — you're fighting the geometry rather than using it.
- General rule: **same-hand transitions that cross both column and row boundaries on the pinky/ring side are worse than they appear on paper.** Flag `sx`, `xs`, and similar pinky↔ring cross-row bigrams as bad even if the raw row/col diff looks small.
- **Combo → outward-adjacent single key is bad**: after pressing a combo (e.g. `p` = ring top+home), moving to the adjacent key toward the pinky is uncomfortable — combo fingers still in motion, and the stagger works against you. Example: `p` (ring combo, col 1) → `s` (pinky, col 0) is bad. But inward rolls (`bl`, `pn`, `nv`) are fine — the col stagger actually helps those. Thumb keys are a separate category and unaffected by this rule.

## Motion Quality

**Good (best→acceptable):**
1. Hand alternation
2. Inward rolls (toward center, same hand)
3. Outward rolls (away from center, same hand)

**Bad:**
- **SFB** (same-finger bigram): same column, any row. Pairs in this layout: c↔f↔x (col 1), n↔l↔w (col 2), t↔d (col 3), a↔u (col 4), e↔o (col 5), i↔y (col 6)
- **Scissors**: |row diff| ≥ 2 AND |col diff| ≤ 1 AND same hand. Example: d(3,2)→w(2,0), u(4,2)→'(5,0)
- **Redirect**: same hand, direction reverses (not a roll)

## Feature Roles

- **Magic keys**: resolve SFBs and common bigrams via context-aware output (e.g. n+magicA→ng)
- **Adaptives**: regular key outputs differently after specific trigger (e.g. n+h→g for "ng")
- **Combos**: two keys simultaneously → one output (marked 💎 in layout)
- **Chords**: two-key sequences → common words (220+ words, chord mode layer)
- **Layers**: Left/Right (shift variants), Nav, FnSym, Num (tri-layer), Case, Media
- **No HRM on base layer** — shift on both pinkies (bottom row); other mods when shift held

## Corpus

`/home/gregor/source/genkey/corpora/shai-iweb.json` — keys: `letters`, `bigrams`, `trigrams`, `skipgrams` (raw counts). Total: ~341M bigrams, ~255M trigrams.
Genkey binary: `/home/gregor/source/genkey/genkey`
