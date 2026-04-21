#!/usr/bin/env python3

# [MISE] description="Suggest practical placements for an explicit magic-word list. Example: mise run suggest-magic-placements -- --prefer-row 'thank you=t' --prefer-row 'gregor=z' thank you gregor"

import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parents[2]))

from suggest_magic_placements import main  # noqa: E402


if __name__ == "__main__":
    main()
