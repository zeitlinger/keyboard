#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.11"
# dependencies = ["rich", "wordfreq"]
# ///

from __future__ import annotations

import json
import random
import re
import sys
from dataclasses import dataclass
from datetime import datetime, timezone
from pathlib import Path

from rich.console import Console
from rich.panel import Panel
from rich.text import Text

from feel import load_adaptives
from scripts.find_available_chords import (
    README,
    load_adaptive_blocks,
    magic_feel_score,
    magic_rows_map,
    output_difficulty,
    output_frequency,
    parse_magic_table,
)


@dataclass(frozen=True)
class MagicEntry:
    output: str
    triggers: tuple[str, ...]
    best_trigger: str
    value: float


STATS_FILE = Path(__file__).parent / "magic_stats.json"

ACTIVE_SET_SIZE = 5
GRADUATION_STREAK = 3
REVIEW_PROBABILITY = 0.1
STALE_DAYS = 7

console = Console()
_tty = None


def clear_screen() -> None:
    print("\033[H\033[2J\033[3J", end="", flush=True)


def tty_input() -> str:
    global _tty
    if _tty is None:
        _tty = open("/dev/tty")
    line = _tty.readline()
    if not line:
        raise EOFError
    return line.rstrip("\n")


def now_iso() -> str:
    return datetime.now(timezone.utc).isoformat()


def days_since(iso: str) -> float:
    return (datetime.now(timezone.utc) - datetime.fromisoformat(iso)).total_seconds() / 86400


def canonical_trigger(row: str, column: str) -> str:
    return f"{row}+{column.removeprefix('magic_')}"


def normalize_output(cell: str) -> str | None:
    text = cell.strip()
    if not text or text.startswith("["):
        return None
    if text.startswith('"') and text.endswith('"'):
        text = text[1:-1]
    text = text.strip()
    if len(text) <= 1:
        return None
    if not re.search(r"[A-Za-z]", text):
        return None
    return text


def trigger_aliases(trigger: str) -> set[str]:
    row, column = trigger.split("+", 1)
    letter = column.strip()
    aliases = {
        trigger.lower(),
        f"{row}{letter}".lower(),
        f"{row} {letter}".lower(),
        f"{row}+{letter}".lower(),
        f"{row} + {letter}".lower(),
        f"{row}+magic_{letter}".lower(),
        f"{row} magic_{letter}".lower(),
    }
    return aliases


def normalize_answer(answer: str) -> str:
    text = answer.strip().lower()
    if not text:
        return text
    text = text.replace("magic_", "")
    text = re.sub(r"\s+", "", text)
    if "+" not in text:
        if text.startswith("spc") and len(text) > 3:
            text = f"spc+{text[3:]}"
        elif text.startswith("tab") and len(text) > 3:
            text = f"tab+{text[3:]}"
        elif text.startswith("↩️️") and len(text) > 1:
            text = f"↩️️+{text[1:]}"
        elif len(text) >= 2:
            text = f"{text[:-1]}+{text[-1]}"
    return text


def parse_magic_entries() -> list[MagicEntry]:
    header, rows, _ = parse_magic_table(README)
    adaptives = load_adaptives(README)
    blocked_pairs = load_adaptive_blocks(README)
    magic_rows = magic_rows_map(header, rows)

    grouped: dict[str, list[tuple[str, float]]] = {}
    for row_name, (_, cells) in rows.items():
        for index, raw_cell in enumerate(cells):
            output = normalize_output(raw_cell)
            if output is None:
                continue
            column = header[index]
            trigger = canonical_trigger(row_name, column)
            starts_with_row = len(row_name) == 1 and output.lower().startswith(row_name)
            difficulty = output_difficulty(output, adaptives, blocked_pairs, magic_rows)
            saved = max(1, len(output) - 2)
            frequency = output_frequency(output)
            feel = magic_feel_score(row_name, column, starts_with_row)
            value = saved ** 2 * frequency * difficulty / (feel + 1)
            grouped.setdefault(output, []).append((trigger, value))

    entries: list[MagicEntry] = []
    for output, trigger_rows in grouped.items():
        ranked = sorted(trigger_rows, key=lambda item: item[1], reverse=True)
        entries.append(
            MagicEntry(
                output=output,
                triggers=tuple(trigger for trigger, _ in ranked),
                best_trigger=ranked[0][0],
                value=ranked[0][1],
            )
        )
    entries.sort(key=lambda entry: entry.value, reverse=True)
    return entries


def load_entries() -> dict[str, MagicEntry]:
    return {entry.output: entry for entry in parse_magic_entries()}


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


def record_answer(stats: dict, output: str, correct: bool) -> dict:
    entry = stats.setdefault(output, {"correct": 0, "total": 0, "streak": 0})
    entry["total"] += 1
    entry["last_seen"] = now_iso()
    if correct:
        entry["correct"] += 1
        entry["streak"] = entry.get("streak", 0) + 1
    else:
        entry["streak"] = 0
    return entry


def update_active_set(active: list[str], stats: dict, all_outputs: list[str]) -> None:
    for output in [item for item in active if is_mastered(stats.get(item, {}))]:
        active.remove(output)
    unseen = [item for item in all_outputs if item not in active and not is_mastered(stats.get(item, {}))]
    while len(active) < ACTIVE_SET_SIZE and unseen:
        active.append(unseen.pop(0))


def pick_output(active: list[str], stats: dict, all_outputs: list[str], last: str | None) -> str:
    mastered = [item for item in all_outputs if is_mastered(stats.get(item, {}))]
    stale = [item for item in mastered if is_stale(stats.get(item, {}))]

    pool = list(dict.fromkeys(active + stale))
    if not stale and mastered and random.random() < REVIEW_PROBABILITY:
        pool = mastered
    if not pool:
        pool = mastered or all_outputs

    candidates = [item for item in pool if item != last] or pool

    weights = []
    for item in candidates:
        stat = stats.get(item, {})
        if is_mastered(stat) and is_stale(stat):
            last_seen = stat.get("last_seen")
            age = days_since(last_seen) if last_seen else STALE_DAYS * 10
            weight = min(age / STALE_DAYS, 3.0)
        else:
            total = stat.get("total", 0)
            correct = stat.get("correct", 0)
            accuracy = correct / total if total else 0.0
            weight = max(0.1, 1.0 - accuracy)
        weights.append(weight)

    return random.choices(candidates, weights=weights, k=1)[0]


def header_panel(active: list[str], stats: dict, all_outputs: list[str]) -> Panel:
    all_stats = [value for value in stats.values() if isinstance(value, dict)]
    mastered = [item for item in all_outputs if is_mastered(stats.get(item, {}))]
    stale_count = sum(1 for item in mastered if is_stale(stats.get(item, {})))
    total_attempts = sum(value.get("total", 0) for value in all_stats)
    total_correct = sum(value.get("correct", 0) for value in all_stats)
    accuracy = f"{total_correct / total_attempts:.0%}" if total_attempts else "—"

    text = Text()
    text.append(f"Mastered: {len(mastered)}/{len(all_outputs)}", style="bold cyan")
    text.append(f"   Active: {len(active)}", style="dim")
    if stale_count:
        text.append(f"   Refresh: {stale_count}", style="bold yellow")
    text.append(f"   Acc: {accuracy}", style="dim")
    return Panel(text, title="[bold blue]Magic Trainer[/]", expand=False)


def show_prompt(entries: dict[str, MagicEntry], output: str, stats: dict, panel: Panel) -> None:
    stat = stats.get(output, {})
    total = stat.get("total", 0)
    correct = stat.get("correct", 0)
    streak = stat.get("streak", 0)
    entry = entries[output]

    clear_screen()
    console.print(panel)

    if is_mastered(stat):
        if is_stale(stat):
            last = stat.get("last_seen")
            age = f"{days_since(last):.0f}d ago" if last else "never"
            info = f"  [bold yellow]refresh ({age})[/]"
        else:
            info = f"  [dim]review ({correct}/{total})[/]"
    elif total:
        pips = "●" * streak + "○" * (GRADUATION_STREAK - streak)
        info = f"  [dim]{pips} {correct}/{total}[/]"
    else:
        info = "  [dim]new[/]"

    console.print(f"  Type trigger for: [bold white]{output}[/]{info}")
    if len(entry.triggers) > 1:
        console.print(f"  [dim]Accepts any of: {', '.join(entry.triggers)}[/]")
    console.print()
    console.print("  [blue]>[/] ", end="")


def run() -> None:
    entries = load_entries()
    if not entries:
        console.print("[bold yellow]No multi-character magic entries found in README.md[/]")
        sys.exit(1)

    stats = load_stats()
    all_outputs = list(entries)

    active: list[str] = stats.get("_active", [])
    active = [item for item in active if item in entries]
    unmastered_new = [item for item in all_outputs if item not in active and not is_mastered(stats.get(item, {}))]
    while len(active) < ACTIVE_SET_SIZE and unmastered_new:
        active.append(unmastered_new.pop(0))

    last_output: str | None = None
    try:
        while True:
            update_active_set(active, stats, all_outputs)
            mastered = [item for item in all_outputs if is_mastered(stats.get(item, {}))]
            if not active and not mastered:
                console.print("\n[bold cyan]All magic entries mastered![/]")
                break

            output = pick_output(active, stats, all_outputs, last_output)
            last_output = output
            show_prompt(entries, output, stats, header_panel(active, stats, all_outputs))
            answer = tty_input().strip()
            if answer == "q":
                break

            normalized = normalize_answer(answer)
            accepted = {
                alias
                for trigger in entries[output].triggers
                for alias in trigger_aliases(trigger)
            }
            correct = normalized in accepted
            entry = record_answer(stats, output, correct)
            if correct:
                if entry["streak"] == GRADUATION_STREAK:
                    console.print(f"  [bold cyan]✓ Mastered! ({output} → {entries[output].best_trigger})[/]")
                else:
                    console.print("  [bold white]✓ Correct![/]")
            else:
                console.print(
                    f"  [bold yellow]✗  expected one of: {', '.join(entries[output].triggers)}  "
                    f"(you typed: {answer or '?'})[/]"
                )
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
