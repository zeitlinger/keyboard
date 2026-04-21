#!/usr/bin/env python3

# [MISE] description="Rank free magic-table slots for old chords or local source-word candidates. Example: mise run find-available-chords -- --candidates-file source_words.tsv --limit 50"

import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parents[2]))

from scripts.find_available_chords import main  # noqa: E402


if __name__ == "__main__":
    main()
