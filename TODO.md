# TODO — chord-fold cleanup

## State

Chord subsystem replaced by 9-magic system. Generator supports:
- Single-char cells → tap.
- Quoted cells starting with prev letter → strip prefix, emit rest.
- Quoted cells not starting with prev letter (prev IS a letter) → `tap_code16(KC_BSPC); SEND_STRING(cell)`.
- Quoted cells where prev is not a letter (spc, punct) → append as-is.

Capacity: 160 free letter-row slots + 67 non-letter → 227 total. 174 old chord words fit.

Old chord table (174 entries) preserved at `git show 21f2800^:README.md` lines 153-337.

## Pending

### 1. Migrate old chord words into magic table — `find_available_chords.py` rewrite

Goal: assign each of 174 old chord words to a `(prev, magic_col)` slot.

- Parse old chord table from `git show 21f2800^:README.md` (or extract to `old_chords.txt`).
- Score each word: `saved² × freq × difficulty / (magic_feel_score + 1)`
  - `saved = len(word) - 2` (two keystrokes: prev + magic)
  - Word-starts-with-prev cells are cheaper (no bs) — add small bonus or lower feel penalty.
- Greedy assign: sort words by value; for each, pick best-feel free slot (any prev letter, any magic col).
- `--apply N` writes top N to Magic Keys table rows; create missing rows (z) as needed.
- Reuse `feel.py` (`LAYOUT`, `MAGIC_POSITIONS`, feel math) and mirror `suggest-combos.py` CLI.

### 2. `CHORD_MODE.md` rewrite

Currently references deleted chord subsystem. Rewrite to explain the magic-key flow:
- 9 magic keys, each physical key triggers a `switch(get_last_keycode())` dispatch.
- Cell conventions (strip / bs / append).
- Cross-magic chaining via `magic` row.

### 3. `train.py` vocab update

Train on magic-key vocabulary (preceding-letter + magic-col → word), not old chord triggers.

### 4. Docs audit

- `README.md` line 11 still references `[Chord Mode](CHORD_MODE.md)` — rewrite after (2).
- Check `DESIGN_PHILOSOPHY.md` for stale chord mentions.

### 5. (nit) Derive `MAGIC_POSITIONS` from Layout table

`feel.py` hardcodes `MAGIC_POSITIONS` — the Layout table already has each magic's physical position. Parse it once instead.
