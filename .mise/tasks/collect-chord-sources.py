#!/usr/bin/env python3

# [MISE] description="Refresh local chat/source/github TSV corpora for chord ranking"

from __future__ import annotations

import subprocess
from pathlib import Path


def run(cmd: list[str]) -> None:
    subprocess.run(cmd, check=True)


def run_optional(cmd: list[str], label: str) -> None:
    try:
        subprocess.run(cmd, check=True)
    except subprocess.CalledProcessError:
        print(f"skipping {label}")


def main() -> None:
    source_root = str(Path.home() / "source")
    run(
        [
            "mise",
            "run",
            "extract-local-chat-words",
            "--",
            "--output",
            "local_chat_words.tsv",
            "--limit",
            "700",
            "--min-count",
            "3",
            "--min-english-freq",
            "1e-6",
            "--min-length",
            "3",
            "--max-length",
            "24",
            "--include-covered",
        ]
    )

    run(
        [
            "mise",
            "run",
            "extract-source-words",
            "--",
            source_root,
            "--output",
            "source_words.tsv",
            "--limit",
            "700",
            "--min-count",
            "3",
            "--min-length",
            "4",
            "--max-length",
            "24",
            "--include-covered",
        ]
    )

    run_optional(
        [
            "mise",
            "run",
            "extract-github-words",
            "--",
            "--output",
            "github_words.tsv",
            "--limit",
            "700",
            "--min-count",
            "3",
            "--min-length",
            "3",
            "--max-length",
            "24",
            "--max-items",
            "500",
            "--include-covered",
        ],
        "github corpus",
    )


if __name__ == "__main__":
    main()
