#!/usr/bin/env python3

# [MISE] description="Suggest budgeted chord adds/removes from local chat + source corpora; forwards --apply"

from __future__ import annotations

import os
import subprocess
import sys
import tempfile
from pathlib import Path


ROOT = Path(__file__).parents[2]
EXTRACT_CHAT = ROOT / "scripts" / "extract_local_chat_words.py"
EXTRACT_SOURCE = ROOT / "scripts" / "extract_source_words.py"
MERGE = ROOT / "scripts" / "merge_word_lists.py"
RANK = ROOT / "scripts" / "find_available_chords.py"

CHAT_HISTORY = Path.home() / ".codex" / "history.jsonl"
CHAT_SESSIONS = Path.home() / ".codex" / "sessions"
SOURCE_ROOT = Path.home() / "source"

EXTRACT_LIMIT = 700
EXTRACT_MIN_COUNT = 3
EXTRACT_MIN_LENGTH = 3
EXTRACT_MAX_LENGTH = 24
CHAT_MIN_ENGLISH_FREQ = 1e-6


def ensure_flag(args: list[str], flag: str, *values: str) -> None:
    if flag in args:
        return
    args.append(flag)
    args.extend(values)


def flag_value(args: list[str], flag: str) -> str | None:
    for index, item in enumerate(args):
        if item == flag and index + 1 < len(args):
            return args[index + 1]
        if item.startswith(flag + "="):
            return item.split("=", 1)[1]
    return None


def run(cmd: list[str], *, env: dict[str, str]) -> None:
    subprocess.run(cmd, cwd=ROOT, env=env, check=True)


def main() -> None:
    rank_args = list(sys.argv[1:])

    env = os.environ.copy()
    env["PYTHONPATH"] = str(ROOT) if not env.get("PYTHONPATH") else f"{ROOT}:{env['PYTHONPATH']}"

    with tempfile.TemporaryDirectory(prefix="suggest_chords_") as temp_dir_name:
        temp_dir = Path(temp_dir_name)
        chat_file = temp_dir / "chat.tsv"
        source_file = temp_dir / "source.tsv"
        merged_file = temp_dir / "merged.tsv"

        run(
            [
                "uv",
                "run",
                str(EXTRACT_CHAT),
                str(CHAT_HISTORY),
                str(CHAT_SESSIONS),
                "--output",
                str(chat_file),
                "--source-label",
                "chat_local",
                "--limit",
                str(EXTRACT_LIMIT),
                "--min-count",
                str(EXTRACT_MIN_COUNT),
                "--min-english-freq",
                str(CHAT_MIN_ENGLISH_FREQ),
                "--min-length",
                str(EXTRACT_MIN_LENGTH),
                "--max-length",
                str(EXTRACT_MAX_LENGTH),
                "--include-covered",
            ],
            env=env,
        )

        run(
            [
                "uv",
                "run",
                str(EXTRACT_SOURCE),
                str(SOURCE_ROOT),
                "--output",
                str(source_file),
                "--source-label",
                "source",
                "--limit",
                str(EXTRACT_LIMIT),
                "--min-count",
                str(EXTRACT_MIN_COUNT),
                "--min-length",
                "4",
                "--max-length",
                str(EXTRACT_MAX_LENGTH),
                "--include-covered",
            ],
            env=env,
        )

        run(
            [
                "uv",
                "run",
                str(MERGE),
                str(chat_file),
                str(source_file),
                "--output",
                str(merged_file),
                "--limit",
                "1000",
            ],
            env=env,
        )

        ensure_flag(rank_args, "--candidates-file", str(merged_file))
        ensure_flag(rank_args, "--include-current")
        ensure_flag(rank_args, "--allow-replacement")
        ensure_flag(rank_args, "--show-delta")
        ensure_flag(rank_args, "--new-only")
        if flag_value(rank_args, "--limit") is None:
            ensure_flag(rank_args, "--limit", flag_value(rank_args, "--budget") or "174")

        run(["uv", "run", str(RANK), *rank_args], env=env)


if __name__ == "__main__":
    main()
