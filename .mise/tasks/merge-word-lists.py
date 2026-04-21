#!/usr/bin/env python3

# [MISE] description="Merge general and local vocabulary TSVs for weighted magic-word ranking. Example: mise run merge-word-lists -- general_words.tsv source_words.tsv --output merged_words.tsv"

import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parents[2]))

from scripts.merge_word_lists import main  # noqa: E402


if __name__ == "__main__":
    main()
