#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.11"
# ///

"""Implementation for `mise run extract-github-words`."""

from __future__ import annotations

import argparse
import json
import os
import re
import subprocess
import sys
import urllib.parse
import urllib.request
from collections import Counter
from dataclasses import dataclass
from pathlib import Path

from scripts.extract_source_words import current_magic_words


ROOT = Path(__file__).parent.parent
README = ROOT / "README.md"
DEFAULT_OUTPUT = ROOT / "github_words.tsv"
WORD_RE = re.compile(r"[a-z]+(?:'[a-z]+)*")
STOP_WORDS = {
    "a", "an", "and", "as", "at", "be", "by", "for", "from", "in", "into", "is", "it", "of",
    "on", "or", "the", "to", "was", "were", "with",
}


@dataclass(frozen=True)
class GithubItem:
    repository: str
    number: int
    is_pull_request: bool
    title: str
    body: str


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Extract authored GitHub words from issues, PRs, and comments for magic-word ranking."
    )
    parser.add_argument("--readme", type=Path, default=README, help="README used for current magic coverage")
    parser.add_argument("--output", type=Path, default=DEFAULT_OUTPUT, help="TSV output path")
    parser.add_argument("--source-label", default="chat", help="Source label written into the TSV")
    parser.add_argument("--username", help="GitHub username to extract for (defaults to authenticated user)")
    parser.add_argument(
        "--repo",
        action="append",
        default=[],
        help="Restrict to one or more repos (owner/name), repeatable",
    )
    parser.add_argument("--limit", type=int, default=500, help="Maximum number of rows to write")
    parser.add_argument("--min-count", type=int, default=2, help="Minimum token count to include")
    parser.add_argument("--min-length", type=int, default=3, help="Minimum word length")
    parser.add_argument("--max-length", type=int, default=24, help="Maximum word length")
    parser.add_argument(
        "--include-covered",
        action="store_true",
        help="Keep words already present in the current Magic Keys table",
    )
    parser.add_argument(
        "--max-items",
        type=int,
        default=500,
        help="Maximum unique issues/PRs to inspect for authored comments and reviews",
    )
    return parser.parse_args()


def github_token() -> str:
    token = os.environ.get("GITHUB_TOKEN")
    if token:
        return token
    result = subprocess.run(
        ["gh", "auth", "token"],
        check=True,
        capture_output=True,
        text=True,
    )
    return result.stdout.strip()


def github_get_json(path: str, *, params: dict[str, str | int] | None = None, token: str) -> tuple[object, dict[str, str]]:
    url = f"https://api.github.com{path}"
    if params:
        url += "?" + urllib.parse.urlencode(params)
    request = urllib.request.Request(
        url,
        headers={
            "Accept": "application/vnd.github+json",
            "Authorization": f"Bearer {token}",
            "X-GitHub-Api-Version": "2022-11-28",
        },
    )
    with urllib.request.urlopen(request) as response:
        body = response.read().decode("utf-8")
        headers = {key.lower(): value for key, value in response.headers.items()}
    return json.loads(body), headers


def paged_list(path: str, *, token: str) -> list[dict]:
    results: list[dict] = []
    page = 1
    while True:
        payload, _ = github_get_json(path, params={"per_page": 100, "page": page}, token=token)
        if not payload:
            return results
        assert isinstance(payload, list)
        results.extend(payload)
        if len(payload) < 100:
            return results
        page += 1


def authenticated_username(token: str) -> str:
    payload, _ = github_get_json("/user", token=token)
    return payload["login"]


def to_item(raw: dict) -> GithubItem:
    repository = raw["repository_url"].removeprefix("https://api.github.com/repos/")
    return GithubItem(
        repository=repository,
        number=raw["number"],
        is_pull_request="pull_request" in raw,
        title=raw.get("title") or "",
        body=raw.get("body") or "",
    )


def collect_items(username: str, repos: list[str], *, token: str, max_items: int) -> list[GithubItem]:
    merged: dict[tuple[str, int], GithubItem] = {}
    for raw in paged_list("/issues", token=token):
        item = to_item(raw)
        if repos and item.repository not in repos:
            continue
        merged[(item.repository, item.number)] = item
        if len(merged) >= max_items:
            break
    return list(merged.values())


def authored_texts(item: GithubItem, username: str, *, token: str) -> list[str]:
    texts = []
    issue_payload, _ = github_get_json(f"/repos/{item.repository}/issues/{item.number}", token=token)
    if issue_payload.get("user", {}).get("login") == username and item.title:
        texts.append(item.title)
    if issue_payload.get("user", {}).get("login") == username and item.body:
        texts.append(item.body)

    for comment in paged_list(f"/repos/{item.repository}/issues/{item.number}/comments", token=token):
        if comment.get("user", {}).get("login") == username and comment.get("body"):
            texts.append(comment["body"])

    if item.is_pull_request:
        for comment in paged_list(f"/repos/{item.repository}/pulls/{item.number}/comments", token=token):
            if comment.get("user", {}).get("login") == username and comment.get("body"):
                texts.append(comment["body"])
        for review in paged_list(f"/repos/{item.repository}/pulls/{item.number}/reviews", token=token):
            if review.get("user", {}).get("login") == username and review.get("body"):
                texts.append(review["body"])

    return texts


def count_words(
    texts: list[str],
    *,
    min_length: int,
    max_length: int,
) -> Counter[str]:
    counts: Counter[str] = Counter()
    for text in texts:
        for word in WORD_RE.findall(text.lower()):
            if word in STOP_WORDS:
                continue
            if not (min_length <= len(word) <= max_length):
                continue
            counts[word] += 1
    return counts


def write_output(output: Path, rows: list[tuple[int, float, str]], *, source_label: str) -> None:
    lines = ["# count\tfreq\tsource\tword"]
    lines.extend(f"{count}\t{freq:.12f}\t{source_label}\t{word}" for count, freq, word in rows)
    output.write_text("\n".join(lines) + "\n")


def main() -> None:
    args = parse_args()
    token = github_token()
    username = args.username or authenticated_username(token)
    items = collect_items(username, args.repo, token=token, max_items=args.max_items)

    texts: list[str] = []
    for item in items:
        texts.extend(authored_texts(item, username, token=token))

    counts = count_words(texts, min_length=args.min_length, max_length=args.max_length)
    covered = set() if args.include_covered else current_magic_words(args.readme)
    total = sum(counts.values()) or 1

    rows = [
        (count, count / total, word)
        for word, count in counts.most_common()
        if count >= args.min_count and word not in covered
    ][: args.limit]

    write_output(args.output, rows, source_label=args.source_label)
    print(f"wrote {len(rows)} rows to {args.output}")
    print(f"username: {username}")
    print(f"items scanned: {len(items)}")
    print(f"text fragments: {len(texts)}")
    print(f"total tokens: {total}")
    if args.repo:
        print(f"repos: {', '.join(args.repo)}")
    if not args.include_covered:
        print(f"excluded current magic words: {len(covered)}")
    print("top rows:")
    for count, freq, word in rows[:20]:
        print(f"  {count:>6}  {freq:.8f}  {word}")


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        sys.exit(130)
