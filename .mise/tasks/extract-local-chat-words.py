#!/usr/bin/env python3

# [MISE] description="Extract local Codex/Claude chat words for magic-word ranking. Example: mise run extract-local-chat-words -- --output local_chat_words.tsv --limit 500 --min-count 3"

import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parents[2]))

from extract_local_chat_words import main  # noqa: E402


if __name__ == "__main__":
    main()
