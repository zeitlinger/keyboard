# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

Custom keyboard layout generator for the Hands Down Vibranium layout on a Ferris Sweep (34-key split keyboard). A Kotlin program reads the layout definition from `README.md` markdown tables and generates QMK firmware C code.

## Build & Flash

```bash
mise run generate    # Compile Kotlin and generate QMK files (mvn compile exec:java)
mise run flash       # Generate + flash firmware via QMK (avrdude-split-left)
```

Tools are managed by mise (Java, Maven, Python, jq, uv). Run `mise install` if needed.

## Architecture

**The README.md is the source of truth for the keyboard layout.** The generator parses its markdown tables (layout, options, symbols, magic keys, chords) and produces QMK C code.

### Generator (Kotlin, `src/main/kotlin/`)

- `generateKeyboard.kt` — Entry point (`main()`), core data types (`Layer`, `Key`, `KeyPosition`, `LayerOption`, etc.)
- `read.kt` — Parses markdown tables into layer data structures
- `generate.kt` — Produces QMK C layer definitions from parsed layers
- `combos.kt` — Generates combo definitions (`combos.def`)
- `chords.kt` — Generates chord mode C code
- `translate.kt` — Translates markdown symbols to QMK keycodes using the Symbols table
- `modifiers.kt` — Home row mod logic
- `options.kt` — Parses the LayerOptions table
- `hand.kt` — Left/right hand position logic
- `analyze.kt` — Layout statistics
- `version.kt` — Git version embedding

### Generated QMK output (`qmk/`)

- `generated.c` — Main generated file (layers, magic keys, chords, custom keycodes)
- `combos.def` — Generated combo definitions
- `keymap.c` — Hand-written QMK entry point that includes `generated.c`
- `casemodes.c/h` — Hand-written X-Case implementation
- `layout.h` — Hand-written layout helpers

The generator runs twice: once to `qmk/` (with placeholder version) and once to `target/qmk/` (with git version). Only `target/qmk/` should be used for actual firmware builds.

## Workflow

1. Edit layout tables in `README.md` (layers, combos, chords, magic keys, symbols, options)
2. Run `mise run generate` to regenerate `qmk/generated.c` and `qmk/combos.def`
3. Run `mise run flash` to build and flash

## Key Concepts

- **Layers**: Base, Left, Right, Nav, FnSym, Num, etc. — defined in Layout and Options tables
- **Combos**: Two keys pressed together produce a different output (marked with 💎 in layout)
- **Chords**: Two-letter sequences that expand to common words (Chord Table in README)
- **Magic keys**: Context-sensitive keys that output different characters based on the previous keypress
- **Dead keys**: Modifier keys (dead1/dead2/dead3) used for layer switching
- **X-Case**: Automatic case conversion modes (camelCase, snake_case, etc.)
