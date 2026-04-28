# TODO

## Current Follow-ups

### 1. `CHORD_MODE.md` rewrite

The old chord subsystem is gone. The doc still needs to explain the current magic-key flow:

- 9 magic keys and row-based dispatch
- cell semantics for bare words, quoted literals, and bracket handlers
- suffix chaining and the `magic` row behavior

### 2. Docs audit

Check the remaining docs for stale chord wording:

- `README.md`
- `DESIGN_PHILOSOPHY.md`
- `CHORD_MODE.md` itself after the rewrite

### 3. Derive `MAGIC_POSITIONS` from layout data

`feel.py` still hardcodes `MAGIC_POSITIONS`. The layout table already knows
where the magic keys live, so this should eventually be derived once and
shared.

## Recently Finished

- old chord words migrated into the Magic table
- helper workflows consolidated behind `mise` tasks
- `train.py` updated to train current magic-word vocabulary instead of the deleted Chord Table
