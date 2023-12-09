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

int target_layer_on_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    ${targetLayerOnHold}
    default:
        return -1;
    }
}

