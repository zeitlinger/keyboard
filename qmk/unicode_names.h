#pragma once

// Shared so both keymap.c (defines unicode_map[]) and combos.c
// (uses UM()/UP() in combo outputs) see the same indices.
enum unicode_names {
    UMLAUT_A,
    UMLAUT_a,
    UMLAUT_O,
    UMLAUT_o,
    UMLAUT_U,
    UMLAUT_u,
    UMLAUT_s,
    SMILEY,
};
