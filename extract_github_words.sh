#!/usr/bin/env bash
set -euo pipefail

exec mise run extract-github-words -- "$@"
