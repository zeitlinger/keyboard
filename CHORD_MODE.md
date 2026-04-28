# Chord Mode

This file keeps the old name, but the trie-based chord subsystem is gone. The current feature is a
9-key magic expansion system driven by the `Magic Keys` table in [README.md](README.md#magic-keys).

## Overview

Each physical magic key checks the previously emitted key and dispatches from there.

- Runtime entry point: generated `case MAGIC_*` blocks in `qmk/generated.c`
- Dispatch source: `switch (get_last_keycode())`
- Source of truth: `README.md` `Magic Keys` table
- Follow-up suffix logic: `process_suffix()` in `qmk/keymap.c`

The basic pattern is:

1. Type a normal key.
2. Press one of the nine magic keys.
3. Firmware looks at the previous key and emits the cell content for that `(prev, magic)` pair.

Examples from the current table:

- `b` then `magic_d` -> `because`
- `t` then `magic_d` -> `tion`
- `n` then `magic_d` -> `qu`
- `,` then `magic_b` -> ` and `

## Cell Semantics

Rows are preceding keys. Columns are the nine physical magic keys.

### Single-character cell

Single-character cells tap that keycode directly.

- `a` + `magic_c` with cell `e` -> `ae`
- `t` + `magic_h` with cell `,` -> `t,`

These do not enable suffix chaining. Pressing the same magic again replays just the emitted letter
or symbol, without repeating any setup backspace from the original expansion.

### Bare word cell

Bare multi-character cells are treated as word expansions.

- Generator emits the text plus a trailing space.
- Firmware enables the suffix state machine with the word's final character.

Examples:

- `b` + `magic_d` with cell `because` emits `ecause` because the previous `b` is stripped
- `j` + `magic_d` with cell `just` emits `ust`
- `spc` + `magic_d` with cell `the` emits `the`

### Quoted string cell

Quoted strings are literal output. They do not get an automatic trailing space and they do not
enable suffix state.

Rules:

- Previous key is a letter and the string starts with that letter: strip the prefix
- Previous key is a letter and the string does not start with that letter: send backspace, then the
  full string
- Previous key is not a letter: append the string as-is

Examples:

- `n` + `magic_d` with cell `"qu"` -> backspace + `qu`
- `,` + `magic_b` with cell `" and "` -> append ` and `
- `.` + `magic_d` with cell `"./"` -> append `./`

### Bracket token cell

Bracketed names call a named handler instead of sending raw text.

Current handler:

- `[dotSpc]` -> backspace, send `.`, enable one-shot shift, clear suffix state

## Suffix Chaining

When a bare-word magic fires, `qmk/keymap.c` enters suffix mode. The next magic press can rewrite
the trailing space into a suffix or punctuation.

Supported suffix follow-ups:

- `magic_g` -> `ed`, except after a word ending in `e` where it becomes `d`
- `magic_e` -> `ly`
- `magic_b` -> `s`
- `magic_d` -> `n't`
- `ing` key -> `ing`, with a second backspace when the prior letter is a vowel
- `magic_i` -> `.` and one-shot shift
- `magic_h` -> `,`

Examples:

- `b` + `magic_d` -> `because`, then `magic_b` -> `because`
- `j` + `magic_d` -> `just`, then `magic_g` -> `justed`
- `spc` + `magic_d` -> `the`, then `magic_i` -> `the.` with shift armed
- `u` + `magic_i` -> `update`, then `magic_g` -> `updated`

Suffix mode exits on any non-suffix key.

## Cross-Magic Chaining

Magic keys also become the new remembered key. That means a magic can dispatch from a previous
magic, not only from letters or punctuation.

Bare-word and literal-string magics still set the remembered key to the magic trigger:

```c
set_last_keycode(MAGIC_X);
```

That allows a dedicated `magic` row in the table for cross-magic expansions and punctuation flows.

## Generator Behavior

The generator logic lives in `src/main/kotlin/Generate.kt`.

Relevant rules:

- `addMagic()` reads the `Magic` table from `README.md`
- `addMagicEntry()` decides whether a cell becomes tap, `SEND_STRING`, backspace+string, or a
  named handler
- Bare words get `set_suffix_state(...)`
- Quoted strings stay literal

Generated output lands in `qmk/generated.c`. Do not edit that file directly.

## Editing

To change magic behavior:

1. Edit the `Magic Keys` table in `README.md`.
2. Regenerate with `mise run generate`.
3. Flash with `mise run flash` if needed.

The table in `README.md` is the source of truth.
