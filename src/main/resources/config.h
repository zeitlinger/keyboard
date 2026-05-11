#pragma once

// Configure the global tapping term (default: 200ms)
#define TAPPING_TERM 200
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY

#define TAPPING_TOGGLE 2

#define EXTRA_SHORT_COMBOS
// Custom combo matcher buffers the first key press and resolves combos by
// physical key position instead of QMK's keycode-based combo engine.
#define CUSTOM_COMBO_TERM 50

#define UNICODE_SELECTED_MODES UNICODE_MODE_LINUX

${triLayer}

#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
