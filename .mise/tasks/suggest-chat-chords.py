#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.11"
# ///

# [MISE] description="Extract cleaned local chat words and rank them into free magic slots. Example: mise run suggest-chat-chords -- --limit 80 --min-difficulty 1.5"

from __future__ import annotations

import argparse
import os
import subprocess
import tempfile
from pathlib import Path


ROOT = Path(__file__).parents[2]
EXTRACT = ROOT / "scripts" / "extract_local_chat_words.py"
RANK = ROOT / "scripts" / "find_available_chords.py"


def parse_args() -> tuple[argparse.Namespace, list[str]]:
    parser = argparse.ArgumentParser(
        description="Extract cleaned local chat words, then rank them into available magic slots."
    )
    parser.add_argument(
        "--candidates-file",
        type=Path,
        help="Optional TSV output path for the extracted chat candidates. Defaults to a temporary file.",
    )
    parser.add_argument(
        "--extract-limit",
        type=int,
        default=700,
        help="Maximum number of extracted chat rows to keep (default: 700)",
    )
    parser.add_argument(
        "--extract-min-count",
        type=int,
        default=3,
        help="Minimum token count for extracted chat words (default: 3)",
    )
    parser.add_argument(
        "--extract-min-english-freq",
        type=float,
        default=1e-6,
        help="Minimum wordfreq English frequency for extracted words (default: 1e-6)",
    )
    parser.add_argument(
        "--extract-min-length",
        type=int,
        default=3,
        help="Minimum extracted word length (default: 3)",
    )
    parser.add_argument(
        "--extract-max-length",
        type=int,
        default=24,
        help="Maximum extracted word length (default: 24)",
    )
    parser.add_argument(
        "--history",
        type=Path,
        default=Path.home() / ".codex" / "history.jsonl",
        help="Primary Codex history file to scan (default: ~/.codex/history.jsonl)",
    )
    parser.add_argument(
        "--sessions",
        type=Path,
        default=Path.home() / ".codex" / "sessions",
        help="Codex sessions directory to scan (default: ~/.codex/sessions)",
    )
    args, find_args = parser.parse_known_args()
    return args, find_args


def main() -> None:
    args, find_args = parse_args()

    if args.candidates_file is None:
        handle = tempfile.NamedTemporaryFile(prefix="chat_chords_", suffix=".tsv", delete=False)
        handle.close()
        candidates_file = Path(handle.name)
    else:
        candidates_file = args.candidates_file

    env = os.environ.copy()
    env["PYTHONPATH"] = str(ROOT) if not env.get("PYTHONPATH") else f"{ROOT}:{env['PYTHONPATH']}"

    extract_cmd = [
        "uv",
        "run",
        str(EXTRACT),
        str(args.history),
        str(args.sessions),
        "--output",
        str(candidates_file),
        "--limit",
        str(args.extract_limit),
        "--min-count",
        str(args.extract_min_count),
        "--min-english-freq",
        str(args.extract_min_english_freq),
        "--min-length",
        str(args.extract_min_length),
        "--max-length",
        str(args.extract_max_length),
    ]
    subprocess.run(extract_cmd, cwd=ROOT, env=env, check=True)

    rank_cmd = [
        "uv",
        "run",
        str(RANK),
        "--candidates-file",
        str(candidates_file),
        *find_args,
    ]
    subprocess.run(rank_cmd, cwd=ROOT, env=env, check=True)


if __name__ == "__main__":
    main()
