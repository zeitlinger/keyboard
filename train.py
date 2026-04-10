#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.11"
# dependencies = ["rich", "wordfreq"]
# ///

import json
import random
import re
import sys
from datetime import datetime, timezone
from pathlib import Path

from rich.console import Console
from rich.panel import Panel
from rich.text import Text
from wordfreq import word_frequency
from feel import feel_score, LAYOUT, load_adaptives, actual_keystrokes


def chord_feel(chord: str) -> int:
    """Feel score for pressing the chord keys (lower = easier)."""
    keys = [c for c in chord if c in LAYOUT]
    if len(keys) < 2:
        return 0
    return feel_score(keys[0], keys[1])


def output_difficulty(output: str, adaptives: dict) -> float:
    """Average bigram feel of actually typing the output (after applying adaptives). Higher = harder."""
    keys = [c for c in actual_keystrokes(output.lower(), adaptives) if c in LAYOUT]
    if len(keys) < 2:
        return 1.0
    scores = [min(feel_score(a, b), 5) for a, b in zip(keys, keys[1:])]
    return sum(scores) / len(scores)


def chord_value(chord: str, output: str, adaptives: dict) -> float:
    """Higher = more worth learning. Saved keystrokes × frequency × output difficulty, penalised by chord feel."""
    freq = max(word_frequency(w, "en") for w in output.split())
    saved = len(output) - len(chord)
    if saved < 3:
        return 0.0
    return saved**2 * freq * output_difficulty(output, adaptives) / (chord_feel(chord) + 1)


STATS_FILE = Path(__file__).parent / "chord_stats.json"
README = Path(__file__).parent / "README.md"

ACTIVE_SET_SIZE = 5
GRADUATION_STREAK = 3
REVIEW_PROBABILITY = 0.1
STALE_DAYS = 7

console = Console()
tty = open("/dev/tty")


def clear_screen() -> None:
    print("\033[H\033[2J\033[3J", end="", flush=True)


def tty_input() -> str:
    line = tty.readline()
    if not line:
        raise EOFError
    return line.rstrip("\n")


def now_iso() -> str:
    return datetime.now(timezone.utc).isoformat()


def days_since(iso: str) -> float:
    return (datetime.now(timezone.utc) - datetime.fromisoformat(iso)).total_seconds() / 86400


# ── README I/O ────────────────────────────────────────────────────────────────

def parse_chord_table() -> list[tuple[int, str, str, str]]:
    """Return list of (line_idx, chord, output, status) for all chord rows."""
    rows = []
    in_table = False
    for i, line in enumerate(README.read_text().splitlines()):
        if "## Chord Table" in line:
            in_table = True
            continue
        if in_table and line.startswith("##"):
            break
        if not in_table:
            continue
        m = re.match(r"\|\s*([a-z,./]+)\s*\|\s*\"([^\"]+)\"\s*\|\s*(yes|plan|done)?\s*\|", line)
        if m:
            rows.append((i, m.group(1).strip(), m.group(2).strip(), m.group(3) or ""))
    return rows


def set_chord_status_in_readme(chord: str, status: str) -> None:
    lines = README.read_text().splitlines(keepends=True)
    in_table = False
    for i, line in enumerate(lines):
        if "## Chord Table" in line:
            in_table = True
            continue
        if in_table and line.startswith("##"):
            break
        if not in_table:
            continue
        m = re.match(r"(\|\s*" + re.escape(chord) + r"\s*\|\s*\"[^\"]+\"\s*\|\s*)(yes|plan|done)?(\s*\|)", line)
        if m:
            lines[i] = m.group(1) + status + m.group(3) + "\n"
            break
    README.write_text("".join(lines))




def add_next_plan_chord(chords: dict[str, str], all_chords: list[str]) -> tuple[str, str] | None:
    """Pick the most common unplanned chord, mark it plan in README, return (chord, output)."""
    rows = parse_chord_table()
    adaptives = load_adaptives(README)
    unplanned = [(chord_value(chord, output, adaptives), chord, output) for _, chord, output, status in rows if not status]
    if not unplanned:
        return None
    unplanned.sort(reverse=True)
    _, chord, output = unplanned[0]
    set_chord_status_in_readme(chord, "plan")
    chords[chord] = output
    all_chords.append(chord)
    return chord, output


def promote_chord(chord: str, chords: dict[str, str], all_chords: list[str], active: list[str]) -> None:
    """Promote a mastered chord to done in README, then add the next plan chord."""
    set_chord_status_in_readme(chord, "done")
    result = add_next_plan_chord(chords, all_chords)
    if result:
        new_chord, new_output = result
        console.print(f"  [dim]→ Added: {new_output} ({new_chord})[/]")


# ── Stats ─────────────────────────────────────────────────────────────────────

def load_chords() -> dict[str, str]:
    rows = parse_chord_table()
    return {chord: output for _, chord, output, status in rows if status in ("yes", "plan", "done")}


def load_stats() -> dict:
    if STATS_FILE.exists():
        return json.loads(STATS_FILE.read_text())
    return {}


def save_stats(stats: dict) -> None:
    STATS_FILE.write_text(json.dumps(stats, indent=2))


def is_mastered(entry: dict) -> bool:
    return entry.get("streak", 0) >= GRADUATION_STREAK


def is_stale(entry: dict) -> bool:
    last = entry.get("last_seen")
    return last is None or days_since(last) >= STALE_DAYS


def record_answer(stats: dict, chord: str, correct: bool) -> dict:
    entry = stats.setdefault(chord, {"correct": 0, "total": 0, "streak": 0})
    entry["total"] += 1
    entry["last_seen"] = now_iso()
    if correct:
        entry["correct"] += 1
        entry["streak"] = entry.get("streak", 0) + 1
    else:
        entry["streak"] = 0
    return entry


# ── Active set ────────────────────────────────────────────────────────────────

def update_active_set(active: list[str], stats: dict, all_chords: list[str]) -> None:
    for chord in [c for c in active if is_mastered(stats.get(c, {}))]:
        active.remove(chord)
    unseen = [c for c in all_chords if c not in active and not is_mastered(stats.get(c, {}))]
    while len(active) < ACTIVE_SET_SIZE and unseen:
        active.append(unseen.pop(0))


def pick_chord(active: list[str], stats: dict, all_chords: list[str], last: str | None) -> str:
    mastered = [c for c in all_chords if is_mastered(stats.get(c, {}))]
    stale = [c for c in mastered if is_stale(stats.get(c, {}))]

    pool = list(dict.fromkeys(active + stale))
    if not stale and mastered and random.random() < REVIEW_PROBABILITY:
        pool = mastered
    if not pool:
        pool = mastered or all_chords

    candidates = [c for c in pool if c != last] or pool

    weights = []
    for k in candidates:
        s = stats.get(k, {})
        if is_mastered(s) and is_stale(s):
            last_seen = s.get("last_seen")
            age = days_since(last_seen) if last_seen else STALE_DAYS * 10
            w = min(age / STALE_DAYS, 3.0)
        else:
            total = s.get("total", 0)
            correct = s.get("correct", 0)
            accuracy = correct / total if total else 0.0
            w = max(0.1, 1.0 - accuracy)
        weights.append(w)

    return random.choices(candidates, weights=weights, k=1)[0]


# ── Display ───────────────────────────────────────────────────────────────────

def header_panel(active: list[str], stats: dict, all_chords: list[str]) -> Panel:
    chord_stats = [v for v in stats.values() if isinstance(v, dict)]
    mastered = [c for c in all_chords if is_mastered(stats.get(c, {}))]
    stale_count = sum(1 for c in mastered if is_stale(stats.get(c, {})))
    total_attempts = sum(v.get("total", 0) for v in chord_stats)
    total_correct = sum(v.get("correct", 0) for v in chord_stats)
    acc = f"{total_correct/total_attempts:.0%}" if total_attempts else "—"

    text = Text()
    text.append(f"Mastered: {len(mastered)}/{len(all_chords)}", style="bold cyan")
    text.append(f"   Active: {len(active)}", style="dim")
    if stale_count:
        text.append(f"   Refresh: {stale_count}", style="bold yellow")
    text.append(f"   Acc: {acc}", style="dim")
    return Panel(text, title="[bold blue]Chord Trainer[/]", expand=False)


def show_chord_prompt(chords: dict, chord: str, stats: dict, panel) -> None:
    s = stats.get(chord, {})
    total = s.get("total", 0)
    correct = s.get("correct", 0)
    chord_streak = s.get("streak", 0)

    clear_screen()
    console.print(panel)

    if is_mastered(s):
        if is_stale(s):
            last = s.get("last_seen")
            age = f"{days_since(last):.0f}d ago" if last else "never"
            chord_info = f"  [bold yellow]refresh ({age})[/]"
        else:
            chord_info = f"  [dim]review ({correct}/{total})[/]"
    elif total:
        pips = "●" * chord_streak + "○" * (GRADUATION_STREAK - chord_streak)
        chord_info = f"  [dim]{pips} {correct}/{total}[/]"
    else:
        chord_info = "  [dim]new[/]"

    console.print(f"  Type:  [bold white]{chords[chord]}[/]{chord_info}")
    console.print()
    console.print("  [blue]>[/] ", end="")


# ── Main loop ─────────────────────────────────────────────────────────────────

def run() -> None:
    chords = load_chords()
    if not chords:
        console.print("[bold yellow]No chords found in README.md[/]")
        sys.exit(1)

    stats = load_stats()
    all_chords = list(chords)

    active: list[str] = stats.get("_active", [])
    active = [c for c in active if c in chords]
    unmastered_new = [c for c in all_chords if c not in active and not is_mastered(stats.get(c, {}))]
    while len(active) < ACTIVE_SET_SIZE and unmastered_new:
        active.append(unmastered_new.pop(0))

    last_chord: str | None = None
    try:
        while True:
            update_active_set(active, stats, all_chords)
            mastered_chords = [c for c in all_chords if is_mastered(stats.get(c, {}))]
            if not active and not mastered_chords:
                console.print("\n[bold cyan]All chords mastered![/]")
                break

            chord = pick_chord(active, stats, all_chords, last_chord)
            last_chord = chord

            show_chord_prompt(chords, chord, stats, header_panel(active, stats, all_chords))
            answer = tty_input().strip()
            if answer == "q":
                break

            entry = record_answer(stats, chord, answer == chords[chord])
            if answer == chords[chord]:
                if entry["streak"] == GRADUATION_STREAK:
                    console.print(f"  [bold cyan]✓ Mastered! ({chord} → {chords[chord]})[/]")
                    promote_chord(chord, chords, all_chords, active)
                else:
                    console.print("  [bold white]✓ Correct![/]")
            else:
                console.print(f"  [bold yellow]✗  '{chords[chord]}' needs chord: {chord}  (you typed: {answer or '?'})[/]")
                console.print()
                console.print("  [dim]press enter to continue[/] ", end="")
                tty_input()

            stats["_active"] = active
            save_stats(stats)

    except (KeyboardInterrupt, EOFError):
        pass

    stats["_active"] = active
    save_stats(stats)
    console.print("\n[dim]Stats saved.[/]")


if __name__ == "__main__":
    run()
