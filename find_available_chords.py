#!/usr/bin/env python3
import re

# Read README
with open('/home/gregor/source/keyboard/README.md', 'r') as f:
    lines = f.readlines()

# Find used chords
used_chords = set()
in_table = False
for line in lines:
    if '## Chord Table' in line:
        in_table = True
        continue
    if in_table and line.startswith('##'):
        break
    if in_table:
        match = re.match(r'\|\s*([a-z,.]+)\s*\|', line)
        if match:
            used_chords.add(match.group(1).strip())

print(f"Found {len(used_chords)} used chords")

# Find available left->right chords

available = []
for left in 'scntfldzbgkpmxwvr':
    available.append(left)

    # available.append(left + 'r')
    available.append('r'  + left)
    # available.append(left + left)

    for right in 'aeihy,.juor':
        available.append(left + right)

    # add good rolls
    rolls = {
        's': 'c',
        'c': 'ns',
        'n': 'tds',
        'f': 'lt',
        'l': 'dcs',
        't': 'ncs',
    }
    if left in rolls:
        for right in rolls[left]:
            available.append(left + right)

# remove duplicates
available = list(set(available))

for u in used_chords:
    if u not in available:
        print(f"Used chord not in available: {u}")

for a in available:
    if a not in used_chords:
        print(f"Available chord: {a}")
