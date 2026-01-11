#!/bin/bash

# Script to extract common words from GitHub issues using GitHub API
# Usage: ./extract_github_words.sh [github_token]

set -e

OUTPUT_FILE="github_words_analysis.txt"
TEMP_FILE="/tmp/github_issues_text.txt"

echo "=== GitHub Issues Word Frequency Analyzer (API) ==="
echo ""

# Check for GitHub token
GITHUB_TOKEN="${1:-${GITHUB_TOKEN}}"

if [ -z "$GITHUB_TOKEN" ]; then
    echo "❌ GitHub token required!"
    echo ""
    echo "Usage:"
    echo "  ./extract_github_words.sh YOUR_GITHUB_TOKEN"
    echo "  or set GITHUB_TOKEN environment variable"
    echo ""
    echo "Get a token from: https://github.com/settings/tokens"
    echo "Required scope: repo (for private repos) or public_repo (for public only)"
    exit 1
fi

echo "✓ GitHub token found"
echo ""
echo "Fetching your GitHub username..."

# Get authenticated user
USERNAME=$(curl -s -H "Authorization: token $GITHUB_TOKEN" \
    https://api.github.com/user | jq -r '.login')

if [ "$USERNAME" == "null" ] || [ -z "$USERNAME" ]; then
    echo "❌ Failed to authenticate with GitHub token"
    exit 1
fi

echo "✓ Authenticated as: $USERNAME"
echo ""
echo "Fetching issues created by you..."

# Clear temp file
> "$TEMP_FILE"

# Fetch issues (all pages)
page=1
total_issues=0
while true; do
    echo "  Fetching page $page..."

    response=$(curl -s -H "Authorization: token $GITHUB_TOKEN" \
        "https://api.github.com/search/issues?q=author:$USERNAME+type:issue&sort=updated&order=desc&per_page=100&page=$page")

    # Check if we have items
    items=$(echo "$response" | jq -r '.items | length')

    if [ "$items" == "0" ] || [ "$items" == "null" ]; then
        break
    fi

    # Extract title and body from each issue
    echo "$response" | jq -r '.items[] | "\(.title) \(.body // "")"' >> "$TEMP_FILE"

    total_issues=$((total_issues + items))

    # Check if there are more pages
    if [ "$items" -lt 100 ]; then
        break
    fi

    page=$((page + 1))
done

echo "✓ Fetched $total_issues issues"
echo ""
echo "Fetching comments on those issues..."

# Fetch comments for all issues
page=1
total_comments=0
while true; do
    echo "  Fetching comments page $page..."

    response=$(curl -s -H "Authorization: token $GITHUB_TOKEN" \
        "https://api.github.com/search/issues?q=commenter:$USERNAME+author:$USERNAME&sort=updated&order=desc&per_page=100&page=$page")

    items=$(echo "$response" | jq -r '.items | length')

    if [ "$items" == "0" ] || [ "$items" == "null" ]; then
        break
    fi

    # For each issue, get its comments by this user
    echo "$response" | jq -r '.items[].comments_url' | while read -r comments_url; do
        if [ ! -z "$comments_url" ]; then
            curl -s -H "Authorization: token $GITHUB_TOKEN" "$comments_url" | \
                jq -r ".[] | select(.user.login == \"$USERNAME\") | .body // \"\"" >> "$TEMP_FILE"
            total_comments=$((total_comments + 1))
        fi
    done

    if [ "$items" -lt 100 ]; then
        break
    fi

    page=$((page + 1))
done

echo "✓ Fetched comments from issues"
echo ""
echo "Analyzing word frequency..."

# Process the text file:
# 1. Convert to lowercase
# 2. Extract words (alphanumeric only, 3+ characters)
# 3. Remove common English stop words
# 4. Count frequency
# 5. Sort by frequency (most common first)

cat "$TEMP_FILE" | \
    tr '[:upper:]' '[:lower:]' | \
    grep -oE '\b[a-z]{3,}\b' | \
    grep -vwE '(the|and|for|are|but|not|you|all|can|was|with|have|this|from|that|been|has|more|will|when|your|they|which|their|what|there|than|into|could|other|some|these|only|time|very|would|about|after|first|also|many|over|such|should|where|most|before|because|between|without|through|during|against|every|another|being|however|then|them|than|were|each|said|does|both|under|while|last|might|still|those|just|good|made|much|even|any|his|her|our|out|who|him|see|now|did|get|may|down|way|been|long|come|here|well|back|its|own|upon|how|put|let|off|end|why|too|old|got)' | \
    sort | \
    uniq -c | \
    sort -rn | \
    head -100 > "$OUTPUT_FILE"

echo ""
echo "✓ Analysis complete!"
echo ""
echo "Top 100 most common words (excluding stop words):"
echo "================================================"
cat "$OUTPUT_FILE"

echo ""
echo ""
echo "Saved to: $OUTPUT_FILE"
echo ""
echo "Now analyzing which words are missing from your chord table..."

# Read current chord table words from README.md
CHORD_WORDS=$(grep -E '^\| [a-z]' README.md | awk -F'|' '{print $3}' | tr -d '"' | tr -d ' ' | sort -u)

echo ""
echo "=== Suggested words to add (not in chord table) ==="
echo "===================================================="

# Extract words that appear frequently but aren't in chord table
while read -r line; do
    count=$(echo "$line" | awk '{print $1}')
    word=$(echo "$line" | awk '{print $2}')

    # Check if word is NOT in chord table
    if ! echo "$CHORD_WORDS" | grep -qw "$word"; then
        # Check if word length is reasonable for chords (4-12 chars)
        word_len=${#word}
        if [ $word_len -ge 4 ] && [ $word_len -le 12 ]; then
            printf "%-6s %s\n" "$count" "$word"
        fi
    fi
done < "$OUTPUT_FILE" | head -50

echo ""
echo "=== Usage Notes ==="
echo "- Higher numbers = more frequent in your issues"
echo "- These words appear in your GitHub issues but not in your chord table"
echo "- Consider adding the most frequent ones that match good second letters: , . a e i h u o y j r"
echo ""

