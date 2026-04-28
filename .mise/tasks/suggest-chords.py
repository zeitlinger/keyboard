#!/usr/bin/env python3

# [MISE] description="Suggest budgeted chord adds/removes from existing TSV sources; forwards --apply"

from __future__ import annotations

import os
import subprocess
import sys
import tempfile
from pathlib import Path


ROOT = Path(__file__).parents[2]
MERGE = ROOT / "scripts" / "merge_word_lists.py"
RANK = ROOT / "scripts" / "find_available_chords.py"

GENERAL_WORDS = ROOT / "general_words.tsv"
SOURCE_WORDS = ROOT / "source_words.tsv"
LOCAL_CHAT_WORDS = ROOT / "local_chat_words.tsv"
GITHUB_WORDS = ROOT / "github_words.tsv"

SOURCE_FILES = [
    ("general", GENERAL_WORDS),
    ("source", SOURCE_WORDS),
    ("chat_local", LOCAL_CHAT_WORDS),
    ("github", GITHUB_WORDS),
]
DEFAULT_SOURCE_WEIGHTS = {
    "general": "1.0",
    "source": "1.7",
    "chat_local": "1.2",
    "github": "1.0",
}
SOURCE_LABEL_ALIASES = {
    "chat": "github",
}


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


def set_flag(args: list[str], flag: str, value: str) -> None:
    for index, item in enumerate(args):
        if item == flag:
            if index + 1 < len(args):
                args[index + 1] = value
            else:
                args.append(value)
            return
        if item.startswith(flag + "="):
            args[index] = f"{flag}={value}"
            return
    args.extend([flag, value])


def normalized_source_weights(present_labels: list[str], explicit: str | None) -> str:
    canonical_labels = [
        SOURCE_LABEL_ALIASES.get(label, label) for label in present_labels
    ]
    if explicit is None:
        return ",".join(
            f"{label}={DEFAULT_SOURCE_WEIGHTS.get(label, '1.0')}"
            for label in canonical_labels
        )

    weights: dict[str, str] = {}
    for part in explicit.split(","):
        chunk = part.strip()
        if not chunk:
            continue
        name, sep, value = chunk.partition("=")
        if not sep:
            raise SystemExit(f"invalid --source-weights entry: {chunk}")
        canonical_name = SOURCE_LABEL_ALIASES.get(name.strip(), name.strip())
        weights[canonical_name] = value.strip()

    for label in canonical_labels:
        weights.setdefault(label, "0")

    return ",".join(f"{label}={weights[label]}" for label in canonical_labels)


def explicit_source_weights(raw: str | None) -> dict[str, float]:
    if raw is None:
        return {}
    weights: dict[str, float] = {}
    for part in raw.split(","):
        chunk = part.strip()
        if not chunk:
            continue
        name, sep, value = chunk.partition("=")
        if not sep:
            raise SystemExit(f"invalid --source-weights entry: {chunk}")
        canonical_name = SOURCE_LABEL_ALIASES.get(name.strip(), name.strip())
        weights[canonical_name] = float(value.strip())
    return weights


def merged_source_labels(path: Path) -> list[str]:
    labels: set[str] = set()
    for raw_line in path.read_text().splitlines():
        line = raw_line.strip()
        if not line or line.startswith("#"):
            continue
        parts = line.split("\t")
        if len(parts) < 4:
            continue
        for label in parts[2].split("+"):
            label = label.strip()
            if label:
                labels.add(label)
    return sorted(labels)


def run(cmd: list[str], *, env: dict[str, str]) -> None:
    subprocess.run(cmd, cwd=ROOT, env=env, check=True)


def main() -> None:
    rank_args = list(sys.argv[1:])

    env = os.environ.copy()
    env["PYTHONPATH"] = (
        str(ROOT) if not env.get("PYTHONPATH") else f"{ROOT}:{env['PYTHONPATH']}"
    )

    explicit_weights = explicit_source_weights(
        flag_value(rank_args, "--source-weights")
    )
    selected_sources = [
        (label, path)
        for label, path in SOURCE_FILES
        if path.exists()
        and (not explicit_weights or explicit_weights.get(label, 0.0) > 0.0)
    ]
    inputs = [path for _, path in selected_sources]
    if not inputs:
        names = ", ".join(path.name for _, path in SOURCE_FILES)
        raise SystemExit(f"no source TSVs found; expected any of: {names}")

    present_labels = [label for label, _ in selected_sources]
    print("using sources:")
    for label, path in selected_sources:
        print(f"  {label:<10} {path.name}")

    with tempfile.TemporaryDirectory(prefix="suggest_chords_") as temp_dir_name:
        merged_file = Path(temp_dir_name) / "merged.tsv"
        run(
            [
                "uv",
                "run",
                str(MERGE),
                *[str(path) for path in inputs],
                "--output",
                str(merged_file),
                "--limit",
                "1500",
            ],
            env=env,
        )

        actual_labels = merged_source_labels(merged_file)
        ensure_flag(rank_args, "--candidates-file", str(merged_file))
        # ensure_flag(rank_args, "--include-current")
        # ensure_flag(rank_args, "--allow-replacement")
        # ensure_flag(rank_args, "--show-delta")
        # ensure_flag(rank_args, "--new-only")
        set_flag(
            rank_args,
            "--source-weights",
            normalized_source_weights(
                actual_labels, flag_value(rank_args, "--source-weights")
            ),
        )
        if flag_value(rank_args, "--limit") is None:
            ensure_flag(
                rank_args, "--limit", flag_value(rank_args, "--budget") or "174"
            )

        run(["uv", "run", str(RANK), *rank_args], env=env)


if __name__ == "__main__":
    main()
