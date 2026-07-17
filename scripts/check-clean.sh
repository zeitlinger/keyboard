#!/usr/bin/env bash
set -euo pipefail

repo_root=$(git rev-parse --show-toplevel)
cd "$repo_root"

changes=$(git status --porcelain)
if [[ -n "$changes" ]]; then
    printf 'Cannot flash with uncommitted changes:\n%s\n' "$changes" >&2
    exit 1
fi
