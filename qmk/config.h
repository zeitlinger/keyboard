#pragma once

// Configure the global tapping term (default: 200ms)
#define TAPPING_TERM 200
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY

#define TAPPING_TOGGLE 2

#define EXTRA_SHORT_COMBOS
#define COMBO_COUNT 92
#define COMBO_SHOULD_TRIGGER
// Optional prototype path for migrating one combo at a time to a custom
// position-based matcher. Leave disabled unless actively testing.
#define USE_CUSTOM_COMBO_POC
#define CUSTOM_COMBO_TERM 50
// Combo trigger keycodes are always read from the Base layer regardless of the
// active layer. process_combo_event picks the output keycode per layer
// (e.g. emit S(KC_P) on _LEFT), so we no longer need S_*/DS_* shadow
// combos.
#define COMBO_ONLY_FROM_LAYER 0

#define UNICODE_SELECTED_MODES UNICODE_MODE_LINUX

#define TRI_LAYER_LOWER_LAYER 1
#define TRI_LAYER_UPPER_LAYER 6
#define TRI_LAYER_ADJUST_LAYER 7

#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
