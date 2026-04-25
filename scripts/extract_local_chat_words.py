#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.11"
# ///

"""Implementation for `mise run extract-local-chat-words`."""

from __future__ import annotations

import argparse
import html
import json
import re
from collections import Counter
from pathlib import Path

from scripts.extract_source_words import current_magic_words


ROOT = Path(__file__).parent.parent
README = ROOT / "README.md"
DEFAULT_OUTPUT = ROOT / "local_chat_words.tsv"
DEFAULT_ROOT_CANDIDATES = [Path.home() / ".codex" / "history.jsonl"]
WORD_RE = re.compile(r"[a-z]+(?:'[a-z]+)*")
CODE_FENCE_RE = re.compile(r"```.*?```", re.DOTALL)
INLINE_CODE_RE = re.compile(r"`[^`\n]+`")
HTML_TAG_RE = re.compile(r"<[^>]+>")
URL_RE = re.compile(r"https?://\S+")
PATH_RE = re.compile(r"(?:/[A-Za-z0-9._-]+){2,}")
BRACKET_TAG_RE = re.compile(r"\[[^\]\n]{1,40}\]")
SHELL_TRANSCRIPT_RE = re.compile(r"(?m)^\s*\[[^\]\n]{1,40}\]\s+\$.*$")
STRUCTURED_LOG_JSON_RE = re.compile(
    r'\{[^{}\n]*"(?:hostname|pid|logContext|renovateVersion|time|level|msg)"\s*:[^{}\n]*\}'
)
STOP_WORDS = {
    "a", "an", "and", "as", "at", "be", "by", "for", "from", "in", "into", "is", "it", "of",
    "on", "or", "the", "to", "was", "were", "with",
}
CONTRACTION_NORMALIZATIONS = {
    "cant": "can't",
    "couldnt": "couldn't",
    "didnt": "didn't",
    "dont": "don't",
    "isnt": "isn't",
    "shouldnt": "shouldn't",
    "wasnt": "wasn't",
    "wont": "won't",
    "wouldnt": "wouldn't",
}


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Extract common words from local Codex/Claude-style chat transcripts for magic-word ranking."
    )
    parser.add_argument(
        "roots",
        nargs="*",
        type=Path,
        help="Files or directories to scan. Defaults to local Codex history/sessions and Downloads/Claude.html if present.",
    )
    parser.add_argument("--readme", type=Path, default=README, help="README used for current magic coverage")
    parser.add_argument("--output", type=Path, default=DEFAULT_OUTPUT, help="TSV output path")
    parser.add_argument("--source-label", default="chat_local", help="Source label written into the TSV")
    parser.add_argument("--limit", type=int, default=500, help="Maximum number of rows to write")
    parser.add_argument("--min-count", type=int, default=2, help="Minimum token count to include")
    parser.add_argument("--min-length", type=int, default=3, help="Minimum word length")
    parser.add_argument("--max-length", type=int, default=24, help="Maximum word length")
    parser.add_argument(
        "--include-covered",
        action="store_true",
        help="Keep words already present in the current Magic Keys table",
    )
    return parser.parse_args()


def default_roots() -> list[Path]:
    return [path for path in DEFAULT_ROOT_CANDIDATES if path.exists()]


def iter_files(roots: list[Path]):
    for root in roots:
        expanded = root.expanduser()
        if not expanded.exists():
            continue
        if expanded.is_file():
            yield expanded
            continue
        for path in expanded.rglob("*"):
            if path.is_file():
                yield path


def read_text(path: Path) -> str | None:
    try:
        data = path.read_bytes()
    except OSError:
        return None
    if b"\0" in data:
        return None
    return data.decode("utf-8", errors="ignore")


def flatten_content(content: object) -> list[str]:
    if isinstance(content, str):
        return [content]
    if isinstance(content, list):
        texts: list[str] = []
        for item in content:
            texts.extend(flatten_content(item))
        return texts
    if isinstance(content, dict):
        texts: list[str] = []
        if content.get("type") in {"input_text", "output_text", "text"} and isinstance(content.get("text"), str):
            texts.append(content["text"])
        for key in ("text", "message", "content"):
            if key in content:
                texts.extend(flatten_content(content[key]))
        return texts
    return []


def extract_codex_session_text(path: Path, text: str) -> list[str]:
    messages: list[str] = []
    for raw_line in text.splitlines():
        raw_line = raw_line.strip()
        if not raw_line:
            continue
        try:
            row = json.loads(raw_line)
        except json.JSONDecodeError:
            continue
        if row.get("type") == "response_item":
            payload = row.get("payload", {})
            if payload.get("type") == "message" and payload.get("role") == "user":
                messages.extend(flatten_content(payload.get("content")))
    return messages


def extract_history_text(path: Path, text: str) -> list[str]:
    messages: list[str] = []
    for raw_line in text.splitlines():
        raw_line = raw_line.strip()
        if not raw_line:
            continue
        try:
            row = json.loads(raw_line)
        except json.JSONDecodeError:
            continue
        if isinstance(row.get("text"), str):
            messages.append(row["text"])
    return messages


def extract_generic_jsonl_text(path: Path, text: str) -> list[str]:
    messages: list[str] = []
    for raw_line in text.splitlines():
        raw_line = raw_line.strip()
        if not raw_line:
            continue
        try:
            row = json.loads(raw_line)
        except json.JSONDecodeError:
            continue
        messages.extend(flatten_content(row))
    return messages


def extract_html_text(text: str) -> str:
    stripped = html.unescape(HTML_TAG_RE.sub(" ", text))
    return stripped


def clean_message(text: str) -> str:
    if text.startswith("# AGENTS.md instructions for "):
        return ""
    if text.startswith("<environment_context>"):
        return ""
    if text.startswith("<permissions instructions>"):
        return ""
    if text.startswith("## Skills\nA skill is "):
        return ""
    cleaned = SHELL_TRANSCRIPT_RE.sub(" ", text)
    cleaned = STRUCTURED_LOG_JSON_RE.sub(" ", cleaned)
    cleaned = CODE_FENCE_RE.sub(" ", cleaned)
    cleaned = INLINE_CODE_RE.sub(" ", cleaned)
    cleaned = URL_RE.sub(" ", cleaned)
    cleaned = PATH_RE.sub(" ", cleaned)
    cleaned = html.unescape(cleaned)
    cleaned = HTML_TAG_RE.sub(" ", cleaned)
    cleaned = BRACKET_TAG_RE.sub(" ", cleaned)
    cleaned = re.sub(r"AGENTS\.md instructions for \S+", " ", cleaned)
    cleaned = re.sub(r"(?m)^\s*>.*$", " ", cleaned)
    cleaned = re.sub(r"(?m)^\s*[-+*]\s+\S.*$", " ", cleaned)
    cleaned = re.sub(r"(?m)^\s*\d+\.\s+\S.*$", " ", cleaned)
    cleaned = re.sub(r"\s+", " ", cleaned)
    return cleaned.strip()


def extract_messages(path: Path, text: str) -> list[str]:
    if path.name == "history.jsonl":
        return extract_history_text(path, text)
    if path.suffix == ".jsonl" and "rollout-" in path.name:
        return extract_codex_session_text(path, text)
    if path.suffix == ".jsonl":
        return extract_generic_jsonl_text(path, text)
    if path.suffix in {".html", ".htm"}:
        return [extract_html_text(text)]
    return [text]


def count_words(
    roots: list[Path],
    *,
    min_length: int,
    max_length: int,
) -> tuple[Counter[str], int, int]:
    counts: Counter[str] = Counter()
    files_seen = 0
    messages_seen = 0
    for path in iter_files(roots):
        text = read_text(path)
        if not text:
            continue
        files_seen += 1
        for message in extract_messages(path, text):
            cleaned = clean_message(message)
            if not cleaned:
                continue
            messages_seen += 1
            for word in WORD_RE.findall(cleaned.lower()):
                word = CONTRACTION_NORMALIZATIONS.get(word, word)
                if word in STOP_WORDS:
                    continue
                if not (min_length <= len(word) <= max_length):
                    continue
                counts[word] += 1
    return counts, files_seen, messages_seen


def write_output(output: Path, rows: list[tuple[int, float, str]], *, source_label: str) -> None:
    lines = ["# count\tfreq\tsource\tword"]
    lines.extend(f"{count}\t{freq:.12f}\t{source_label}\t{word}" for count, freq, word in rows)
    output.write_text("\n".join(lines) + "\n")


def main() -> None:
    args = parse_args()
    roots = args.roots or default_roots()
    counts, files_seen, messages_seen = count_words(
        roots,
        min_length=args.min_length,
        max_length=args.max_length,
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
    print(f"roots: {', '.join(str(root) for root in roots)}")
    print(f"files scanned: {files_seen}")
    print(f"messages scanned: {messages_seen}")
    print(f"total tokens: {total}")
    if not args.include_covered:
        print(f"excluded current magic words: {len(covered)}")
    print("top rows:")
    for count, freq, word in rows[:20]:
        print(f"  {count:>6}  {freq:.8f}  {word}")


if __name__ == "__main__":
    main()
