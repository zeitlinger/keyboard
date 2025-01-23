#include QMK_KEYBOARD_H


/* THIS FILE WAS GENERATED!
 *
 * ${generationNote}
 */

#define VERSION_STRING "${versionString}"

${layerNumbers}

${triLayer}

enum custom_keycodes {
	${custom0} = SAFE_RANGE,
	${customRest}
};

${customHandlers}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
${layers}
};
