#pragma once

// Configure the global tapping term (default: 200ms)
#define TAPPING_TERM 200
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY

#define TAPPING_TOGGLE 2

#define EXTRA_SHORT_COMBOS
#define COMBO_COUNT ${comboCount}
// Combo trigger keycodes are always read from _BASE regardless of the
// active layer. process_combo_event picks the output keycode per layer
// (e.g. emit S(KC_P) on _LEFT), so we no longer need S_*/DS_* shadow
// combos.
#define COMBO_ONLY_FROM_LAYER _BASE

#define UNICODE_SELECTED_MODES UNICODE_MODE_LINUX

${triLayer}

#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
