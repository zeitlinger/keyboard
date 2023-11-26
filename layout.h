#include QMK_KEYBOARD_H


/* THIS FILE WAS GENERATED!
 *
 * ${generationNote}
 */

${layerNumbers}

enum custom_keycodes {
	${custom0} = SAFE_RANGE,
	${customRest}
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
${layers}
};
