/* THIS FILE WAS GENERATED!
 *
 * ${generationNote}
 */

int alternateLayer = -1;

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    switch(index) {
${timeouts}
    default:
        return COMBO_TERM;
    }
}

bool process_record_generated(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        switch (keycode) {
${oneShotOnUpLayerReleased}
        }
    }
    if (alternateLayer >= 0 && record->event.pressed) {
        switch (alternateLayer) {
${oneShotOnUpLayerKey}
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
            if (get_repeat_key_count() > 0) {
                switch (keycode) {
${repeat}
                }
            }
            switch (keycode) {
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

uint16_t get_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
    switch (keycode) {
${altRepeat}
    }

    return KC_TRNS;
}
