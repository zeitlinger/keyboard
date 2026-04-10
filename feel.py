# Layout positions and feel scoring for the Hands Down Vibranium layout.
# Shared between suggest-adaptives.py and train.py.

import re
from pathlib import Path

# col 0-3 = left (pinky→index), 4-7 = right (index→pinky); row 0=top 1=home 2=bottom 3=thumb
LAYOUT = {
    's': (0,1), 'c': (1,1), 'n': (2,1), 't': (3,1),
    'a': (4,1), 'e': (5,1), 'i': (6,1), 'h': (7,1),
    'f': (1,2), 'l': (2,2), 'd': (3,2),
    'u': (4,2), 'o': (5,2), 'y': (6,2),
    'x': (1,0), 'w': (2,0),
    'r': (3,3),  # left thumb
    # Combo keys (vertical combos) — inner columns
    'p': (1,0), 'b': (1,2),   # ring finger top/bottom combo
    'm': (2,0), 'g': (2,2),   # middle finger top/bottom combo
    'v': (3,0), 'k': (3,2),   # index finger top/bottom combo
    # Combo keys — pinky columns
    'z': (0,2),               # left pinky bottom combo
    'q': (7,0), 'j': (7,2),   # right pinky top/bottom combo
}

COMBO_KEYS = set('pbmgvkzqj')


def is_thumb(pos):
    return pos[1] == 3


def is_sfb(a, b):
    if is_thumb(a) or is_thumb(b):
        return False
    return a[0] == b[0]


def is_scissors(a, b):
    if is_thumb(a) or is_thumb(b):
        return False
    same_hand = (a[0] < 4) == (b[0] < 4)
    col_diff = abs(a[0] - b[0])
    row_diff = abs(a[1] - b[1])
    return same_hand and col_diff <= 1 and row_diff >= 2


def is_combo_adjacent(a_char, b_char):
    """Combo key followed by outward-adjacent single key is bad."""
    a_pos, b_pos = LAYOUT[a_char], LAYOUT[b_char]
    if is_thumb(a_pos) or is_thumb(b_pos):
        return False
    same_hand = (a_pos[0] < 4) == (b_pos[0] < 4)
    adjacent = abs(a_pos[0] - b_pos[0]) == 1
    outward = b_pos[0] < a_pos[0]
    return (a_char in COMBO_KEYS and b_char not in COMBO_KEYS
            and same_hand and adjacent and outward)


def is_combo_preceded(a_char, b_char):
    """Regular key followed by a combo key on the same hand."""
    if a_char in COMBO_KEYS or b_char not in COMBO_KEYS:
        return False
    a_pos, b_pos = LAYOUT[a_char], LAYOUT[b_char]
    if is_thumb(a_pos) or is_thumb(b_pos):
        return False
    return (a_pos[0] < 4) == (b_pos[0] < 4)


def is_bad(a, b):
    return is_sfb(a, b) or is_scissors(a, b)


def feel_score(a_char, b_char):
    """Lower = better feel for the physical motion a_char → b_char.

      0 = good inward same-hand roll
      1 = alternation or outward
      2 = combo-adjacent to same/lower row; or row_diff > 1 with d-exception, outward (stretch)
      0 also covers: row_diff > 1 with d-exception, inward (big roll, still comfortable)
      3 = adjacent finger (col_diff=1) with row change + pinky; or combo-adjacent moving up/to top row
     99 = row_diff > 1 without d exception (uncomfortable reach)
    Combo key as physical target: floor of 3 (never better than "ok").
    """
    a_pos, b_pos = LAYOUT[a_char], LAYOUT[b_char]
    row_diff = abs(a_pos[1] - b_pos[1])

    if is_thumb(a_pos) or is_thumb(b_pos):
        score = 1
    elif (a_pos[0] < 4) != (b_pos[0] < 4):
        score = 1
    else:
        col_diff = abs(a_pos[0] - b_pos[0])
        inward = b_pos[0] > a_pos[0]

        if row_diff > 1 and 'd' not in (a_char, b_char):
            return 99

        if row_diff > 1:
            score = 2 if not inward else 0
        elif col_diff == 1 and row_diff > 0:
            pinky = (a_pos[0] in (0, 7) or b_pos[0] in (0, 7))
            score = 3 if pinky else 1
        elif inward:
            score = 0
        else:
            score = 1

    if b_char in COMBO_KEYS:
        score = max(score, 3)

    combo_rest_row = max(a_pos[1], 1)
    if a_char in COMBO_KEYS and b_pos[0] < 4 and b_pos[1] < combo_rest_row:
        col_diff = abs(a_pos[0] - b_pos[0])
        score = 3 if col_diff == 1 else score + 1

    if is_combo_adjacent(a_char, b_char):
        if b_pos[1] >= max(1, a_pos[1]):
            score = max(score, 2)
        else:
            score = max(score, 3)

    return score


def load_adaptives(readme: Path) -> dict[tuple[str, str], str]:
    """Parse Adaptives table → {(prev_output, desired_output): physical_key}.

    This is the reverse of suggest-adaptives.py's (trigger, key)→output mapping,
    oriented for converting output words to actual keystroke sequences.
    """
    result = {}
    in_table = False
    for line in readme.read_text().splitlines():
        if '## Adaptives' in line:
            in_table = True
            continue
        if in_table:
            if line.startswith('##'):
                break
            m = re.match(r'\|\s*(\w)\s*\|\s*(\w)\s*\|\s*(\w)\s*\|', line)
            if m:
                trigger, key, output = m.group(1), m.group(2), m.group(3)
                result[(trigger, output)] = key
    return result


def actual_keystrokes(output: str, adaptives: dict[tuple[str, str], str]) -> list[str]:
    """Convert an output string to its physical keystroke sequence, applying adaptives."""
    keys = []
    for i, char in enumerate(output):
        if i > 0:
            keys.append(adaptives.get((output[i - 1], char), char))
        else:
            keys.append(char)
    return keys
