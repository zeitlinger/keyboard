/* THIS FILE WAS GENERATED!
 *
 * ${generationNote}
 */

int layer = _BASE;

static bool magic_capitalize_next = false;
static bool magic_context_key_emitted = true;

${magicStringDecoder}
${magicCycleData}

// Two-variable tracking for real logical keys.
// prev_keycode = the prior resolved key press (what adaptives and magics check against).
// last_keycode = the most recent resolved key press (shifts to prev_keycode on the next keypress).
// Updated from the real trigger keycode, not the emitted adaptive/magic output,
// so context-sensitive logic can see through substitutions.
// Combo components like KC_C from P=KC_C+KC_X are never recorded — only KC_P is.
static uint16_t prev_keycode = KC_NO;
static uint16_t last_keycode = KC_NO;
static uint16_t last_magic_trigger = KC_NO;
static uint16_t last_magic_repeat_keycode = KC_NO;
static uint16_t magic_remembered_keycode = KC_NO;
static uint16_t magic_repeat_keycode = KC_NO;

static inline uint16_t unshift_letter_keycode(uint16_t keycode) {
    if (keycode >= S(KC_A) && keycode <= S(KC_Z)) {
        return keycode - S(KC_A) + KC_A;
    }
    return keycode;
}

static uint16_t magic_prepare_last_keycode(uint16_t keycode) {
    uint16_t unshifted = unshift_letter_keycode(keycode);
    magic_capitalize_next = unshifted != keycode;
    return unshifted;
}

static bool repeat_last_magic_key(uint16_t trigger) {
    if (last_magic_trigger != trigger || last_magic_repeat_keycode == KC_NO) {
        return false;
    }
    tap_code16(last_magic_repeat_keycode);
    set_last_keycode(last_magic_repeat_keycode);
    return true;
}

static bool repeat_magic_key(uint16_t keycode) {
    switch (keycode) {
${magicRepeats}
    default:
        return false;
    }
}

static void remember_real_keycode(uint16_t keycode) {
    prev_keycode = last_keycode;
    last_keycode = keycode;
    last_magic_trigger = KC_NO;
    last_magic_repeat_keycode = KC_NO;
#ifdef TRACE_LOGIC
    SEND_STRING("[R:");
    trace_keycode_label(keycode);
    SEND_STRING("|p=");
    trace_keycode_label(prev_keycode);
    SEND_STRING("|l=");
    trace_keycode_label(last_keycode);
    SEND_STRING("]");
#endif
}

bool tap(uint16_t keycode) {
    tap_code16(keycode);
    set_last_keycode(keycode);
    return false;
}

bool tap_adaptive(uint16_t pressed_keycode, uint16_t output_keycode) {
#ifdef TRACE_LOGIC
    SEND_STRING("[A:");
    trace_keycode_label(prev_keycode);
    SEND_STRING("+");
    trace_keycode_label(pressed_keycode);
    SEND_STRING(">");
    trace_keycode_label(output_keycode);
    SEND_STRING("]");
#endif
    remember_real_keycode(pressed_keycode);
    tap_code16(output_keycode);
    set_last_keycode(output_keycode);
    return false;
}

static inline void magic_replace_decode_send_cap(uint16_t offset, char suffix) {
    if (magic_context_key_emitted) {
        tap_code16(KC_BSPC);
    }
    magic_decode_send_cap(offset, suffix);
}

static void magic_tap_repeatable(uint16_t keycode) {
    tap_code16(keycode);
    magic_remembered_keycode = keycode;
    magic_repeat_keycode = keycode;
}

static inline void magic_replace_tap_repeatable(uint16_t keycode) {
    if (magic_context_key_emitted) {
        tap_code16(KC_BSPC);
    }
    magic_tap_repeatable(keycode);
}

static bool process_magic_suffix(uint16_t keycode) {
    switch (keycode) {
${magicSuffixes}
    default:
        return false;
    }
}

static bool is_magic_keycode(uint16_t keycode) {
    switch (keycode) {
${magicExclusions}
            return true;
    default:
        return false;
    }
}

static bool process_magic_key_with_context(uint16_t keycode, uint16_t context_keycode,
                                           bool allow_repeat, bool context_emitted) {
    magic_context_key_emitted = context_emitted;
#ifdef TRACE_LOGIC
    if (is_magic_keycode(keycode)) {
        SEND_STRING("[M:");
        trace_keycode_label(keycode);
        SEND_STRING("|ctx=");
        trace_keycode_label(context_keycode);
        SEND_STRING("|rep=");
        trace_bool_label(allow_repeat);
        SEND_STRING("|emit=");
        trace_bool_label(context_emitted);
        SEND_STRING("]");
    }
#endif
    switch (keycode) {
${magic}
    default:
        return true;
    }
}

bool process_record_generated(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
#ifdef TRACE_LOGIC
        SEND_STRING("[P:");
        trace_keycode_label(keycode);
        SEND_STRING("|p=");
        trace_keycode_label(prev_keycode);
        SEND_STRING("|l=");
        trace_keycode_label(last_keycode);
        if (record->tap.count) {
            SEND_STRING("|tap");
        }
        SEND_STRING("]");
#endif
        // Adaptive keys: runs after combo resolution in process_record_user,
        // so combo components are suppressed and prev_keycode reflects the
        // resolved combo keycode (e.g. KC_P not KC_C).
        uint16_t adaptive_prev_keycode = unshift_letter_keycode(prev_keycode);
        switch (keycode) {
${adaptives}
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
            if (!process_magic_key_with_context(keycode, last_keycode, true, true)) {
                return false;
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

bool remember_last_key_user(uint16_t keycode, keyrecord_t* record,
                            uint8_t* remembered_mods) {
    switch (keycode) {
${magicExclusions}
#ifdef TRACE_LOGIC
            SEND_STRING("[RX:");
            trace_keycode_label(keycode);
            SEND_STRING("]");
#endif
            return false;
    }

    remember_real_keycode(keycode);
    return true;  // Other keys can be repeated.
}
