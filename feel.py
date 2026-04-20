# Layout positions and feel scoring for the Hands Down Vibranium layout.
# Shared between suggest-adaptives.py and suggest-combos.py.

import re
from pathlib import Path

# col 0-3 = left (pinky→index), 4-7 = right (index→pinky).
# Rows: 0=top, 1=top combo (between top+home), 2=home, 3=bottom combo (between home+bottom),
#       4=bottom, 5=thumb. Odd rows = combo positions.
LAYOUT = {
    # Top row
    'x': (1,0), 'w': (2,0),
    # Top combos (row 1)
    'p': (1,1), 'm': (2,1), 'v': (3,1),
    # Home row
    's': (0,2), 'c': (1,2), 'n': (2,2), 't': (3,2),
    'a': (4,2), 'e': (5,2), 'i': (6,2), 'h': (7,2),
    # Bottom combos (row 3)
    'z': (0,3), 'b': (1,3), 'g': (2,3), 'k': (3,3), 'j': (7,3),
    # Bottom row
    'f': (1,4), 'l': (2,4), 'd': (3,4),
    'u': (4,4), 'o': (5,4), 'y': (6,4),
    # Thumb
    'r': (3,5),
}

COMBO_KEYS = set('pbmgvkzj')

# Nine physical magic-key positions, keyed by README column name.
MAGIC_POSITIONS = {
    'magic_a': (5, 0),  # R.Mid top row
    'magic_b': (6, 0),  # R.Ring top row
    'magic_c': (0, 1),  # L.Pin top combo
    'magic_d': (5, 1),  # R.Mid top combo
    'magic_e': (6, 1),  # R.Ring top combo
    'magic_f': (7, 1),  # R.Pin top combo
    'magic_g': (4, 3),  # R.Ind bottom combo
    'magic_h': (5, 3),  # R.Mid bottom combo
    'magic_i': (6, 3),  # R.Ring bottom combo
}


def is_thumb(pos):
    return pos[1] == 5


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
    # row_diff >= 3 always scissors. row_diff == 2 upward is scissors when
    # reaching into the top region (b[1] < 2, e.g. cw) OR when pinky is involved
    # (e.g. yh: ring-bottom → pinky-home, pinky stretches past ring).
    # Plain middle/index motions like lt (bottom → home) are natural.
    if not (same_hand and col_diff <= 1):
        return False
    if row_diff >= 3:
        return True
    if row_diff == 2 and b[1] < a[1]:
        pinky = a[0] in (0, 7) or b[0] in (0, 7)
        return b[1] < 2 or pinky
    return False


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
    """Regular key followed by an adjacent-column combo key on the same hand —
    the combo's fingers conflict with the preceding keypress. Distant columns
    (e.g. pinky s → index-combo k) don't share fingers, not awkward."""
    if a_char in COMBO_KEYS or b_char not in COMBO_KEYS:
        return False
    a_pos, b_pos = LAYOUT[a_char], LAYOUT[b_char]
    if is_thumb(a_pos) or is_thumb(b_pos):
        return False
    same_hand = (a_pos[0] < 4) == (b_pos[0] < 4)
    return same_hand and abs(a_pos[0] - b_pos[0]) <= 1


def is_combo_combo(a_char, b_char):
    """Two consecutive combo keys on the same hand — awkward to type back-to-back."""
    if a_char not in COMBO_KEYS or b_char not in COMBO_KEYS:
        return False
    a_pos, b_pos = LAYOUT[a_char], LAYOUT[b_char]
    if is_thumb(a_pos) or is_thumb(b_pos):
        return False
    return (a_pos[0] < 4) == (b_pos[0] < 4)


def is_bad(a, b):
    return is_sfb(a, b) or is_scissors(a, b)


def feel_score(a_char, b_char, combo_target_penalty=True):
    """Lower = better feel for the physical motion a_char → b_char.

    Row scheme: 0=top, 1=top combo, 2=home, 3=bottom combo, 4=bottom, 5=thumb.
    Adjacent rows differ by 1 (home↔combo) or 2 (home↔top/bottom).

      0 = good inward same-hand roll
      1 = alternation or outward
      2 = big reach (row_diff >= 3) same-hand outward, with d-exception
      0 also covers: big reach inward, with d-exception
      3 = adjacent finger with row change + pinky; combo-adjacent going up
     99 = row_diff > 3 (top↔bottom) without d exception
    Combo key as physical target: floor of 3.
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

        if row_diff > 3 and 'd' not in (a_char, b_char):
            return 99

        if row_diff > 3:
            score = 2 if not inward else 0
        elif col_diff == 1 and row_diff > 0:
            pinky = (a_pos[0] in (0, 7) or b_pos[0] in (0, 7))
            score = 3 if pinky else 1
        elif col_diff >= 2 and row_diff >= 2 and b_pos[1] < a_pos[1] and b_pos[1] != 2:
            # Upward diagonal reach same-hand (e.g. sw: pinky-home → middle-top).
            # Downward diagonals are natural curls (sd: pinky-home → index-bottom).
            # Reaching TO home row is also natural (oh/uh → pinky-home).
            pinky = (a_pos[0] in (0, 7) or b_pos[0] in (0, 7))
            score = 3 if pinky else 2
        elif inward:
            score = 0
        else:
            score = 1

    if b_char in COMBO_KEYS and combo_target_penalty:
        score = max(score, 3)

    # Home row as rest position (row 2). Combo key followed by moving further up/out penalises.
    combo_rest_row = max(a_pos[1], 2)
    if a_char in COMBO_KEYS and b_pos[0] < 4 and b_pos[1] < combo_rest_row:
        col_diff = abs(a_pos[0] - b_pos[0])
        score = 3 if col_diff == 1 else score + 1

    if is_combo_adjacent(a_char, b_char):
        if b_pos[1] >= max(2, a_pos[1]):
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
