"""Run after `mise run generate`: python -m unittest scripts.test_literal_shift."""

import string
import subprocess
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


class LiteralShiftTest(unittest.TestCase):
    @staticmethod
    def layer_keys(layout, name):
        block = layout.split(f"[_{name}] =", 1)[1].split("\n\t[", 1)[0]
        body = block.split("LAYOUT_split_3x5_2(", 1)[1].rsplit(")", 1)[0]
        keys = []
        current = []
        depth = 0
        for char in body:
            if char == "," and depth == 0:
                key = "".join(current).strip()
                if key:
                    keys.append(key)
                current = []
                continue
            if char == "(":
                depth += 1
            elif char == ")":
                depth -= 1
            current.append(char)
        key = "".join(current).strip()
        if key:
            keys.append(key)
        return keys

    def test_backspace_in_ordinary_magic_rows(self):
        generated = (ROOT / "qmk/generated.c").read_text()
        magic = generated.split("case MAGIC_J: {", 1)[1].split("case MAGIC_K: {", 1)[0]
        for preceding in ("KC_TAB", "KC_ENT", "KC_SPC"):
            with self.subTest(preceding=preceding):
                self.assertIn(
                    f"case {preceding}: magic_tap_repeatable(KC_BSPC); break;",
                    magic,
                )
        # Keep the existing suffix behavior separate and unchanged.
        suffix = generated.split("static bool process_magic_suffix(", 1)[1].split(
            "static bool is_magic_keycode(", 1
        )[0]
        self.assertIn("tap_code16(KC_BSPC); return true;", suffix)

    def test_layer_entry_and_regular_shift(self):
        layout = (ROOT / "qmk/layout.h").read_text()
        for shifted, literal, letter in (
            ("LEFT", "LLIT", "T"),
            ("RIGHT", "RLIT", "H"),
        ):
            with self.subTest(hand=shifted):
                shifted_keys = layout.split(f"[_{shifted}] =", 1)[1].split("\n\t[", 1)[
                    0
                ]
                literal_keys = layout.split(f"[_{literal}] =", 1)[1].split("\n\t[", 1)[
                    0
                ]
                self.assertIn(f"S(KC_{letter})", shifted_keys)
                self.assertIn(f"MO(_{literal})", shifted_keys)
                self.assertNotIn(f"LM(_{literal}, MOD_LSFT)", shifted_keys)
                self.assertIn(f"KC_{letter}", literal_keys)
                self.assertNotIn(f"S(KC_{letter})", literal_keys)
                # Shifted layers retain their original shared modifier layer.
                for mod in ("MOD_LCTL", "MOD_LALT"):
                    shared = "LMODS" if shifted == "LEFT" else "RMODS"
                    self.assertIn(f"LM(_{shared}, {mod})", shifted_keys)

                # Literal Ctrl/Alt are encoded directly as shifted modifiers.
                self.assertNotIn("LM(_", literal_keys)

        left_shifted = self.layer_keys(layout, "LEFT")
        self.assertEqual(left_shifted[26], "MO(_LLIT)")
        self.assertEqual(
            left_shifted[27:29], ["LM(_LMODS, MOD_LCTL)", "LM(_LMODS, MOD_LALT)"]
        )
        right_shifted = self.layer_keys(layout, "RIGHT")
        self.assertEqual(right_shifted[23], "MO(_RLIT)")
        self.assertEqual(
            right_shifted[21:23], ["LM(_RMODS, MOD_LALT)", "LM(_RMODS, MOD_LCTL)"]
        )

        # The shared layers still expose their original three home-row mods.
        for layer in ("LMODS", "RMODS"):
            keys = layout.split(f"[_{layer}] =", 1)[1].split("\n\t[", 1)[0]
            for mod in ("MOD_LSFT", "MOD_LCTL", "MOD_LALT"):
                self.assertIn(f"LM(_{layer}, {mod})", keys)

        # The literal layers mirror their shared counterparts at every typing
        # position; only the modifier cells are replaced (and Shift is absent).
        left_shared = self.layer_keys(layout, "LMODS")
        left_literal = self.layer_keys(layout, "LLIT")
        self.assertEqual(len(left_shared), len(left_literal))
        left_mod_cells = {26, 27, 28}
        self.assertEqual(
            [key for i, key in enumerate(left_shared) if i not in left_mod_cells],
            [key for i, key in enumerate(left_literal) if i not in left_mod_cells],
        )
        self.assertEqual(left_literal[26:29], ["KC_NO", "S(KC_LCTL)", "S(KC_LALT)"])
        self.assertEqual(left_literal[13], "KC_T")

        right_shared = self.layer_keys(layout, "RMODS")
        right_literal = self.layer_keys(layout, "RLIT")
        self.assertEqual(len(right_shared), len(right_literal))
        right_mod_cells = {21, 22, 23}
        self.assertEqual(
            [key for i, key in enumerate(right_shared) if i not in right_mod_cells],
            [key for i, key in enumerate(right_literal) if i not in right_mod_cells],
        )
        self.assertEqual(right_literal[21:24], ["S(KC_LALT)", "S(KC_LCTL)", "KC_NO"])
        self.assertEqual(right_literal[17], "KC_E")

        keymap_c = (ROOT / "qmk/keymap.c").read_text()
        self.assertNotIn("update_literal_shift", keymap_c)
        self.assertNotIn("is_literal_layer", keymap_c)
        self.assertNotIn("post_process_record_user", keymap_c)

    def test_letter_combos_use_the_adaptive_guard(self):
        combos = (ROOT / "qmk/combos.c").read_text()
        self.assertIn("if (!process_record_generated(keycode, &record))", combos)
        for letter in ("B", "K", "P"):
            self.assertIn(
                f"combo_tap_logical(combo_active_layer() == _LEFT ? S(KC_{letter}) : KC_{letter})",
                combos,
            )
        self.assertIn("active_layer == _LMODS || active_layer == _RMODS", combos)
        self.assertIn("active_layer == _LLIT || active_layer == _RLIT", combos)

    def test_generated_adaptive_logic(self):
        generated = (ROOT / "qmk/generated.c").read_text()
        # Compile the actual generated adaptive path, not a Python reimplementation.
        start = generated.index("bool process_record_generated(")
        end = generated.index("    if (record->tap.count)", start)
        adaptive_path = generated[start:end] + "    return true;\n}\n"
        start = generated.index("static inline uint16_t unshift_letter_keycode(")
        end = generated.index(
            "static inline uint16_t maybe_shift_letter_keycode(", start
        )
        unshift = generated[start:end]
        keycodes = ", ".join(
            f"KC_{letter} = {i + 4}" for i, letter in enumerate(string.ascii_uppercase)
        )
        harness = """
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
enum { _BASE, _LEFT, _RIGHT, _LMODS, _RMODS, _LLIT, _RLIT };
#define S(key) ((key) | 0x200)
typedef struct { struct { bool pressed; } event; } keyrecord_t;
static int layer;
static uint16_t prev_keycode;
static uint16_t output[16];
static unsigned count;
static void tap_code16(uint16_t keycode) { output[count++] = keycode; }
static bool tap_adaptive(uint16_t pressed, uint16_t resolved) {
    (void)pressed;
    tap_code16(resolved);
    return false;
}
"""
        harness += f"enum {{ {keycodes} }};\n" + unshift + adaptive_path
        harness += """
static void press(uint16_t keycode) {
    keyrecord_t record = {.event.pressed = true};
    if (process_record_generated(keycode, &record)) tap_code16(keycode);
    prev_keycode = output[count - 1];
}
static void reset(int active_layer) { layer = active_layer; prev_keycode = 0; count = 0; }
int main(void) {
    reset(_BASE);
    press(KC_S); press(KC_D);
    assert(count == 2 && output[0] == KC_S && output[1] == KC_P);
    for (int side = _LMODS; side <= _RLIT; ++side) {
        reset(side);
        press(KC_S); press(KC_D); press(KC_K);
        assert(count == 3 && output[0] == KC_S && output[1] == KC_D && output[2] == KC_K);
        reset(side);
        press(KC_N); press(KC_P); // P is a combo; n+p must not adapt to nk.
        assert(count == 2 && output[1] == KC_P);
        reset(side);
        press(KC_X); press(KC_H); // Multi-letter x+h -> pl must also be bypassed.
        assert(count == 2 && output[1] == KC_H);
        reset(side);
        press(KC_T);
        assert(count == 1 && output[0] == KC_T);
    }
    reset(_LEFT);
    press(S(KC_S)); press(S(KC_D));
    assert(count == 2 && output[1] == S(KC_D));
    layer = _LLIT;
    press(KC_T);
    assert(output[2] == KC_T);
    layer = _LEFT; // Releasing the index key restores the pinky-held layer.
    press(S(KC_T));
    assert(output[3] == S(KC_T));
    layer = _BASE;
    press(KC_S); press(KC_D);
    assert(output[5] == KC_P);
    reset(_BASE);
    keyrecord_t release = {.event.pressed = false};
    prev_keycode = KC_S;
    assert(process_record_generated(KC_D, &release));
    assert(count == 0);
}
"""
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "literal_shift.c"
            binary = Path(directory) / "literal_shift"
            source.write_text(harness)
            subprocess.run(
                [
                    "cc",
                    "-std=c99",
                    "-Wall",
                    "-Wextra",
                    "-Werror",
                    str(source),
                    "-o",
                    str(binary),
                ],
                check=True,
            )
            subprocess.run([str(binary)], check=True)


if __name__ == "__main__":
    unittest.main()
