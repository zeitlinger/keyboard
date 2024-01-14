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

#define ALL_ONESHOT_MASK ~0
layer_state_t oneshot_mask = ALL_ONESHOT_MASK;

void toggle_layer(uint8_t layer) {
    layer_invert(layer);
    oneshot_mask |= (1 << layer);
}

bool is_layer_off_key(uint16_t keycode, uint8_t layer) {
    ${layerOffKeys}
    return false;
}

bool is_oneshot_layer(uint8_t layer) {
    switch (layer) {
    ${oneshotLayers}
    }
    return false;
}

bool process_record_generated(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        uint8_t layer = get_highest_layer(layer_state);
        if (is_oneshot_layer(layer)) {
            oneshot_mask &= ~(1 << layer);
        } else {
            if (oneshot_mask != ALL_ONESHOT_MASK) {
                layer_and(oneshot_mask);
                oneshot_mask = ALL_ONESHOT_MASK;
            }
            if (is_layer_off_key(keycode, layer)) {
                layer_off(layer);
            }
        }
    }

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
