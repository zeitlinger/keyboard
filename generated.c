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

bool target_layer_on_hold(uint16_t keycode, keyrecord_t *record) {
    if (!record->tap.count) {
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

