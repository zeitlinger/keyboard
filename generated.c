/* THIS FILE WAS GENERATED!
 *
 * ${generationNote}
 */

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    switch(index) {
    ${timeouts}
    default:
        return COMBO_TERM;
    }
}

bool process_record_generated(uint16_t keycode, keyrecord_t *record) {
    if (record->tap.count) {
        if (record->event.pressed) {
            switch (keycode) {
            ${customKeycodesOnTapPressed}
            default:
                break;
            }
        }
    } else {
        if (record->event.pressed) {
            switch (keycode) {
            ${targetLayerOnHoldPressed}
            default:
                break;
            }
        } else {
            switch (keycode) {
            ${targetLayerOnHoldReleased}
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

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    if (!layer_state_is(_BASE)) {
        switch (combo_index) {
        ${disableComboOnNonBaseLayer}
        }
    }

    return true;
}
