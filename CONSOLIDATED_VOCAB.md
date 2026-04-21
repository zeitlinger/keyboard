# Consolidated Vocabulary

The goal is not to choose between general English words and local technical vocabulary.
The goal is to rank both with the same slot-scoring formula and then bias the result with
explicit source weights.

## Idea

Each candidate word gets:

- `saved`: `len(word) - 2`
- `freq`: how often it appears in the source corpus
- `difficulty`: how awkward it is to type normally
- `feel`: how good the proposed magic slot is
- `source`: where the word came from, e.g. `general` or `source`

`find_available_chords.py` ranks by:

`saved^2 * freq * difficulty / (feel + 1)`

When a candidate file includes a `source` column, you can bias one source over another with:

`--source-weights general=1.0,source=1.7`

That means:

- a general-English word keeps its raw frequency
- a repo-local/source word gets multiplied by `1.7`

This lets both vocabularies compete in one queue without hard-separating them.

## Workflow

1. Extract local repo vocabulary.

```bash
mise run extract-source-words -- ~/source \
  --output source_words.tsv \
  --limit 500 \
  --min-count 3 \
  --min-length 4 \
  --max-length 24
```

2. Prepare a general-English TSV in the same format:

```text
# count  freq        source   word
1000     0.01000000  general  because
950      0.00950000  general  people
```

3. Merge both lists.

```bash
mise run merge-word-lists -- general_words.tsv source_words.tsv --output merged_words.tsv
```

4. Rank all candidates together.

```bash
mise run find-available-chords -- --candidates-file merged_words.tsv --source-weights general=1.0,source=1.7 --limit 50
```

5. Apply only the top subset you want to test.

```bash
mise run find-available-chords -- --candidates-file merged_words.tsv --source-weights general=1.0,source=1.7 --apply 20
```

## Interpreting Results

- If a technical term outranks a common English word, keep it above.
- If a common English word outranks a niche repo term, keep it above.
- The source weight is the only deliberate bias. Everything else should come from
  keystroke savings, typing difficulty, and slot feel.

## Notes

- Prefer `mise run ...` for these helper workflows. The implementations live under `scripts/`; the `mise` tasks are the intended entrypoints.

- `scripts/extract_source_words.py` now writes TSV as:

```text
# count  freq        source   word
123      0.00123456  source   opentelemetry
```

- `scripts/find_available_chords.py` still accepts the older three-column format, but the
  four-column format is preferred for consolidation.

## Current Recommendation

For now, use `general` vocabulary only as the default ranking input.

Reason:

- the local `source` corpus is currently too skewed toward repo/docs vocabulary
- the local `chat_local` corpus is currently too small and too biased by recent project work
- mixing them in right now over-promotes technical/project-specific terms relative to the words that are broadly useful day to day

Practical baseline:

1. rank from the old/general-English list only
2. review and apply from that baseline
3. revisit consolidated ranking later, once the personal corpora are larger and cleaner

When revisiting later:

- keep `general` as the baseline
- add only a small curated technical overlay, or a much cleaner/larger personal chat corpus
- avoid relying on raw local corpus counts without additional filtering/caps

## Personal Entries

For personal names, prefer storing and ranking the lowercase form for now, e.g. `gregor`.

Later enhancement:

- allow a dedicated capitalized variant from the same memory slot, e.g. `g + magic_*` producing `Gregor`

For names and mail addresses, mnemonic placement is more important than raw ergonomic score.
It is fine to reserve a small set of easy-to-remember "memory helper" slots for these, even if the
scorer would choose slightly better generic positions elsewhere.

## Magic Mnemonics

As a further memory helper, the magic columns can also be treated as "nearby base-key groups".

Examples:

- `magic_i` feels like `i/y`
- `magic_h` feels like `e/o`
- `magic_g` feels like `a/u`

This is a soft mnemonic, not a hard rule. It is useful when two placements are otherwise close:

- prefer the magic whose nearby-letter feel matches the word better
- use it especially for conversational words and memory-helper entries

The placement helper script includes this only as a small bonus, so it nudges close decisions
without overpowering row preference or ergonomic feel.
