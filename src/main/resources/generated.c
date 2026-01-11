/* THIS FILE WAS GENERATED!
 *
 * ${generationNote}
 */

int alternateLayer = -1;
int layer = _BASE;
# #define CHORD_INACTIVE -10000
int chord_state = CHORD_INACTIVE; // -1 = root, other negative = transition states, non-negative = byte offsets
int chord_depth = 0; // Track number of letters in current chord

${chordDecoder}

int chord_transition(int state, uint16_t keycode) {
    switch (state) {
${chordTransitions}
    default:
        // Invalid transition, stop chord mode
        return CHORD_INACTIVE;
    }
    return CHORD_INACTIVE;
}

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    switch(index) {
${timeouts}
    default:
        return COMBO_TERM;
    }
}

bool tap(uint16_t keycode) {
    tap_code16(keycode);
    set_last_keycode(keycode);
    return false;
}

bool process_record_generated(uint16_t keycode, keyrecord_t *record) {
    if (alternateLayer >= 0 && record->event.pressed) {
        int al = alternateLayer;
        alternateLayer = -1;
        if (layer == _BASE) {
            switch (al) {
${oneShotOnUpLayerKey}
            }
        }
    } else if (layer == _BASE && record->event.pressed) {
        switch (keycode) {
${oneShotOnUpLayerPressed}
        }
    }

    if (record->tap.count) {
        if (record->event.pressed) {
            switch (keycode) {
${customKeycodesOnTapPress}
            default:
                break;
            }
        }
    } else {
        if (record->event.pressed) {
            switch (keycode) {
${magic}
${customKeycodesOnPress}
            default:
                break;
            }
        }
    }
    return true;
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
${holdOnOtherKeyPress}
    default:
        // Do not select the hold action when another key is pressed.
        return false;
    }
}

bool remember_last_key_user(uint16_t keycode, keyrecord_t* record,
                            uint8_t* remembered_mods) {
    switch (keycode) {
        case MAGIC_A:
        case MAGIC_B:
        case MAGIC_C:
            return false;
    }

    return true;  // Other keys can be repeated.
}
