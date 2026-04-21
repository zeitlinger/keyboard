#!/usr/bin/env python3

# [MISE] description="Extract common local source words for magic-word ranking. Example: mise run extract-source-words -- ~/source --output source_words.tsv --limit 500 --min-count 3"

import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parents[2]))

from extract_source_words import main  # noqa: E402


if __name__ == "__main__":
    main()
