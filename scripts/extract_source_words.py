#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.11"
# ///

"""Implementation for `mise run extract-source-words`."""

from __future__ import annotations

import argparse
import fnmatch
import re
from collections import Counter
from pathlib import Path


ROOT = Path(__file__).parent.parent
README = ROOT / "README.md"
DEFAULT_ROOT = Path.home() / "source"
DEFAULT_OUTPUT = ROOT / "source_words.tsv"
DEFAULT_EXTENSIONS = {
    "bash", "c", "cc", "conf", "cpp", "cs", "go", "gradle", "groovy",
    "h", "hh", "hpp", "java", "js", "json", "jsx", "kts", "kt",
    "properties", "proto", "py", "rb", "rs", "scala", "sh", "sql",
    "swift", "toml", "ts", "tsx", "yaml", "yml",
}

IGNORE_DIRS = {
    ".git",
    ".idea",
    ".next",
    ".turbo",
    ".venv",
    "__pycache__",
    "build",
    "coverage",
    "dist",
    "node_modules",
    "out",
    "target",
    "vendor",
}

STOP_WORDS = {
    "about", "after", "again", "against", "all", "also", "another", "any", "are", "around",
    "been", "before", "being", "between", "both", "but", "can", "come", "could", "did",
    "does", "down", "during", "each", "even", "every", "first", "for", "from", "get", "good",
    "got", "had", "has", "have", "here", "him", "his", "how", "however", "into", "its",
    "just", "last", "long", "made", "many", "may", "might", "more", "most", "much", "not",
    "now", "off", "old", "only", "other", "our", "out", "over", "put", "said", "see",
    "should", "some", "still", "such", "than", "that", "their", "them", "then", "there",
    "these", "they", "this", "those", "through", "time", "too", "under", "upon", "very",
    "was", "way", "well", "were", "what", "when", "where", "which", "while", "who", "why",
    "will", "with", "without", "would", "you", "your",
}

WORD_RE = re.compile(r"[a-z][a-z']{2,}")
CAMEL_RE_1 = re.compile(r"([a-z0-9])([A-Z])")
CAMEL_RE_2 = re.compile(r"([A-Z]+)([A-Z][a-z])")
MAGIC_ROW_RE = re.compile(r"^\|\s*([^|]+?)\s*\|(.*)\|$")


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Extract common words from local source trees for magic-word ranking."
    )
    parser.add_argument(
        "roots",
        nargs="*",
        type=Path,
        default=[DEFAULT_ROOT],
        help=f"Directories to scan (default: {DEFAULT_ROOT})",
    )
    parser.add_argument("--readme", type=Path, default=README, help="README used for current magic coverage")
    parser.add_argument("--output", type=Path, default=DEFAULT_OUTPUT, help="TSV output path")
    parser.add_argument("--source-label", default="source", help="Source label written into the TSV")
    parser.add_argument("--limit", type=int, default=500, help="Maximum number of rows to write")
    parser.add_argument("--min-count", type=int, default=2, help="Minimum token count to include")
    parser.add_argument("--min-length", type=int, default=4, help="Minimum word length")
    parser.add_argument("--max-length", type=int, default=24, help="Maximum word length")
    parser.add_argument(
        "--extensions",
        help="Comma-separated file extensions to include, e.g. py,kt,java,ts,tsx,js,go,rs,c,h,md",
    )
    parser.add_argument(
        "--exclude-glob",
        action="append",
        default=[],
        help="Glob to exclude relative paths, repeatable, e.g. '*/content/*' or '*/docs/*'",
    )
    parser.add_argument(
        "--markdown-only",
        action="store_true",
        help="Shortcut for --extensions md,markdown",
    )
    parser.add_argument(
        "--include-covered",
        action="store_true",
        help="Keep words already present in the current Magic Keys table",
    )
    return parser.parse_args()


def split_identifier_text(text: str) -> str:
    text = CAMEL_RE_2.sub(r"\1 \2", text)
    text = CAMEL_RE_1.sub(r"\1 \2", text)
    return text.replace("_", " ").replace("-", " ")


def parse_extensions(args: argparse.Namespace) -> set[str] | None:
    if args.markdown_only:
        return {"md", "markdown"}
    if not args.extensions:
        return DEFAULT_EXTENSIONS
    return {ext.strip().lower().lstrip(".") for ext in args.extensions.split(",") if ext.strip()}


def matches_excludes(path: Path, root: Path, exclude_globs: list[str]) -> bool:
    rel = str(path.relative_to(root))
    return any(fnmatch.fnmatch(rel, pattern) for pattern in exclude_globs)


def iter_files(roots: list[Path], *, extensions: set[str] | None, exclude_globs: list[str]):
    for root in roots:
        root = root.expanduser()
        if root.is_file():
            if extensions and root.suffix.lower().lstrip(".") not in extensions:
                continue
            yield root
            continue
        for path in root.rglob("*"):
            if not path.is_file():
                continue
            if any(part in IGNORE_DIRS for part in path.parts):
                continue
            if extensions and path.suffix.lower().lstrip(".") not in extensions:
                continue
            if matches_excludes(path, root, exclude_globs):
                continue
            yield path


def is_probably_binary(data: bytes) -> bool:
    return b"\0" in data


def read_text(path: Path) -> str | None:
    try:
        data = path.read_bytes()
    except OSError:
        return None
    if is_probably_binary(data):
        return None
    return data.decode("utf-8", errors="ignore")


def current_magic_words(readme: Path) -> set[str]:
    covered = set()
    in_table = False
    for line in readme.read_text().splitlines():
        if "## Magic Keys" in line:
            in_table = True
            continue
        if in_table and line.startswith("##"):
            break
        if not in_table:
            continue
        match = MAGIC_ROW_RE.match(line)
        if not match:
            continue
        row_name = match.group(1).strip()
        if row_name in {"Magic", ":-----:"}:
            continue
        cells = [cell.strip() for cell in match.group(2).split("|")]
        for cell in cells:
            if not cell:
                continue
            value = cell.strip('"')
            if len(value) > 1 and " " not in value and not value.startswith("["):
                covered.add(value.lower())
    return covered


def count_words(
    roots: list[Path],
    *,
    min_length: int,
    max_length: int,
    extensions: set[str] | None,
    exclude_globs: list[str],
) -> Counter[str]:
    counts: Counter[str] = Counter()
    for path in iter_files(roots, extensions=extensions, exclude_globs=exclude_globs):
        text = read_text(path)
        if not text:
            continue
        normalized = split_identifier_text(text).lower()
        for word in WORD_RE.findall(normalized):
            if word in STOP_WORDS:
                continue
            if not is_candidate_word(word):
                continue
            if not (min_length <= len(word) <= max_length):
                continue
            counts[word] += 1
    return counts


def is_candidate_word(word: str) -> bool:
    bare = word.replace("'", "")
    if len(set(bare)) <= 2 and len(bare) >= 6:
        return False
    if len(bare) >= 6 and not any(vowel in bare for vowel in "aeiouy"):
        return False
    if set(bare) <= set("drwxstlp"):
        return False
    return True


def write_output(output: Path, rows: list[tuple[int, float, str]], *, source_label: str) -> None:
    lines = ["# count\tfreq\tsource\tword"]
    lines.extend(f"{count}\t{freq:.12f}\t{source_label}\t{word}" for count, freq, word in rows)
    output.write_text("\n".join(lines) + "\n")


def main() -> None:
    args = parse_args()
    extensions = parse_extensions(args)
    counts = count_words(
        args.roots,
        min_length=args.min_length,
        max_length=args.max_length,
        extensions=extensions,
        exclude_globs=args.exclude_glob,
    )
    covered = set() if args.include_covered else current_magic_words(args.readme)
    total = sum(counts.values()) or 1

    rows = [
        (count, count / total, word)
        for word, count in counts.most_common()
        if count >= args.min_count and word not in covered
    ][: args.limit]

    write_output(args.output, rows, source_label=args.source_label)
    print(f"wrote {len(rows)} rows to {args.output}")
    print(f"total tokens: {total}")
    if extensions:
        print(f"extensions: {', '.join(sorted(extensions))}")
    if args.exclude_glob:
        print(f"exclude globs: {', '.join(args.exclude_glob)}")
    if not args.include_covered:
        print(f"excluded current magic words: {len(covered)}")
    print("top rows:")
    for count, freq, word in rows[:20]:
        print(f"  {count:>6}  {freq:.8f}  {word}")


if __name__ == "__main__":
    main()
