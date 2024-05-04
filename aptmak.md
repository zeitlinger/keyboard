# APTmak keyboard

### Home Row Mods

On all other layers, the modifiers are as shown in the table below.

| Home Row Modifiers | Finger |
|--------------------|--------|
| Alt                | Ring   |
| Ctrl               | Middle |
| Shift              | Index  |

## Layout

How to read this layout:

- 💎 = combo key (e.g. middle and index finger in top row pressed together produce "b")
- 🛑 = key can't be used because the layer was activated with that key or because it's reserved for a modifier
- empty = use key from base layer
- FnBra = capitalized words are layer names - if they are a key, the layer is activated as toggled or one shot layer (if the "OneShot" flag is set in the layer flags)
- /+Ctrl = tab-mod - / on tab and CTRL on hold
- *Mouse = layer is active while key is held
- C-w = Ctrl-w (same for Alt and Shift)
- "that" = combo that produces "that"
- 80 custom timeout for combo
- The symbol table at the bottom shows the meaning of the symbols used in the layout.

> **Note**: The layout is generated from this file directly.

| Layer | L. Pin. | L. Ring | L. Mid. | L. Ind. |       |   | R. Ind. | R. Mid. | R. Ring | R. Pin. |
|:-----:|:-------:|:-------:|:-------:|:-------:|-------|---|:-------:|:-------:|:-------:|:-------:|
| Base  |         |    f    |    g    |    p    |       |   |    l    |    u    |    y    |         |
| Base  |    r    |    s    |    t    |    h    |       |   |    n    |    a    |    i    |    o    |
| Base  |    w    |    c    |  l-sft  |    d    |       |   |    m    |  r-sft  |    ,    |    .    |
|       | ------- | ------- | ------- | ------- | -     | - | ------- | ------- | ------- | ------- |
| Base  |         |         |         |    v    |       |   |    q    |         |         |         |
| Base  |         |         |         |   💎    |       |   |   💎    |         |         |         |
| Base  |         |         |         |    b    |       |   |         |         |         |         |
|       | ------- | ------- | ------- | ------- |       |   | ------- | ------- | ------- | ------- |
| Base  |         |         |    k    |         |       |   |         |  "ua"   |         |         |
| Base  |         |         |   💎    |         |       |   |         |   💎    |         |         |
| Base  |         |         |  "cr"   |         |       |   |         |  "au"   |         |         |
|       | ------- | ------- | ------- | ------- |       |   | ------- | ------- | ------- | ------- |
| Base  |         |  "fr"   |         |         |       |   |         |         |  "you"  |         |
| Base  |         |   💎    |         |         |       |   |         |         |   💎    |         |
| Base  |         |  "sc"   |         |         |       |   |         |         |    j    |         |
|       | ------- | ------- | ------- | ------- |       |   | ------- | ------- | ------- | ------- |
| Base  |         |         |         |         |       |   |         |         |         |         |
| Base  |   💎    |         |         |         |       |   |         |         |         |   💎    |
| Base  |    z    |         |         |         |       |   |         |         |         |    x    |
|       | ------- | ------- | ------- | ------- |       |   | ------- | ------- | ------- | ------- |
|  Nav  |         | tab ➡️  | win ➡️  |  undo   | redo  |   |   esc   |         |   ins   |         |
|  Nav  |  *Nav2  |   🛑    |   🛑    |   🛑    |       |   |   ⬅️    |   ⬆️    |   ⬇️    |   ➡️    |
|  Nav  |   C-w   |   cut   |  copy   |  paste  | S-pst |   |   ↩️️   |  bspc   |   del   |   spc   |
|       | ------- | ------- | ------- | ------- |       |   | ------- | ------- | ------- | ------- |
| Nav2  |         |         |         |         |       |   |         |         |         |         |
| Nav2  |   🛑    |   🛑    |   🛑    |   🛑    |       |   |  ⬅️⬅️   |  ⬆️⬆️   |  ⬇️⬇️   |  ➡️➡️   |
| Nav2  |         |         |         |         |       |   |         |         |         |         |
|       | ------- | ------- | ------- | ------- |       |   | ------- | ------- | ------- | ------- |
|  Sym  |         |    6    |    5    |    4    |       |   |    `    |    (    |    )    |    \    |
|  Sym  |    3    |    2    |    1    |    0    |       |   |    "    |    [    |    ]    |  '+Fn   |
|  Sym  |         |    9    |    8    |    7    |       |   |    ;    |    -    |    =    |    /    |
|       | ------- | ------- | ------- | ------- |       |   | ------- | ------- | ------- | ------- |
|  Fn   |         |   f6    |   f5    |   f4    |       |   |         |         |         |         |
|  Fn   |   f3    |   f2    |   f1    |   f10   |       |   |   🛑    |   🛑    |   🛑    |   🛑    |
|  Fn   |   f11   |   f9    |   f8    |   f7    |       |   |         |         |         |         |
|       | ------- | ------- | ------- | ------- |       |   | ------- | ------- | ------- | ------- |

| Thumb | Left Inner |        Left Outer        |      Right Outer       | Right Inner |
|:-----:|:----------:|:------------------------:|:----------------------:|:-----------:|
| Base  |    Nav     |           spc            |           e            |     Sym     |
|       | ---------- | ------------------------ | ---------------------- | ----------- |
|  Nav  |     🛑     |            🛑            |          tab           |             |
|       | ---------- | ------------------------ | ---------------------- | ----------- |
|  Sym  |            |                          |           🛑           |     🛑      |
|       | ---------- | ------------------------ | ---------------------- | ----------- |
 
## Options

The order of the options is also the order of the layers in the layer stack.

| LayerOptions | Modifiers Left | Modifiers Right | Fallback Left | Fallback Right | Flags |
|:------------:|:--------------:|:---------------:|:-------------:|:--------------:|-------|
|     Base     |                |                 |               |                |       | 
|     Nav      | OneShotHomeRow |                 |               |                |       |
|     Nav2     | OneShotHomeRow |                 |               |                |       |
|     Sym      |    HomeRow     |     HomeRow     |               |                |       |
|      Fn      |                | OneShotHomeRow  |               |                |       |

## Symbols

| Symbol  | Command                               |
|---------|---------------------------------------|
| ⬅️      | KC_LEFT                               |
| ⬅️⬅️    | KC_HOME                               |
| ⬇️      | KC_DOWN                               |
| ⬇️⬇️    | KC_PGDN                               |
| ⬆️      | KC_UP                                 |
| ⬆️⬆️    | KC_PGUP                               |
| ➡️      | KC_RIGHT                              |
| ➡️➡️    | KC_END                                |
| l-sft   | KC_LSFT                               |
| r-sft   | KC_RSFT                               |
| ins     | KC_INS                                |
| del     | KC_DEL                                |
| spc     | KC_SPC                                |
| esc     | KC_ESC                                |
| ↩️️     | KC_ENT                                |
| bspc    | KC_BSPC                               |
| win     | KC_LGUI                               |
| tab     | KC_TAB                                |
| prt     | KC_PSCR                               |
| pipe    | KC_PIPE                               |
| 🖱️⬅️   | KC_MS_L                               |
| 🖱️⬇️   | KC_MS_D                               |
| 🖱️⬆️   | KC_MS_U                               |
| 🖱️➡️   | KC_MS_R                               |
| 🖲️️⬅️  | KC_WH_L                               |
| 🖲️️⬇️  | KC_WH_D                               |
| 🖲️️⬆️  | KC_WH_U                               |
| 🖲️️➡️  | KC_WH_R                               |
| 🖱️1    | KC_BTN1                               |
| 🖱️2    | KC_BTN2                               |
| 🖱️3    | KC_BTN3                               |
| 🔇      | KC_MUTE                               |
| ⏯️      | KC_MPLY                               |
| ⏮️      | KC_MPRV                               |
| ⏭️      | KC_MNXT                               |
| 🔊      | KC_VOLU                               |
| 🔈      | KC_VOLD                               |
| 🔆      | KC_BRIU                               |
| 🔅      | KC_BRID                               |
| redo    | RCS(KC_Z)                             |
| undo    | C(KC_Z)                               |
| S-pst   | RCS(KC_V)                             |
| cut     | C(KC_X)                               |
| copy    | C(KC_C)                               |
| paste   | C(KC_V)                               |
| ä       | ALGR(KC_Q)                            |
| ö       | ALGR(KC_P)                            |
| ü       | ALGR(KC_Y)                            |
| ß       | ALGR(KC_S)                            |
| '       | ALGR(KC_QUOTE)                        |
| `       | ALGR(KC_GRV)                          |
| ~       | ALGR(KC_TILD)                         |
| ^       | ALGR(KC_CIRC)                         |
| <       | <implicit>                            |
| >       | <implicit>                            |
| rep     | QK_REPEAT_KEY                         |
| aRep    | QK_ALT_REPEAT_KEY                     |
| tab ➡️  | custom:NEXT_TAB                       |
| win ➡️  | custom:NEXT_WINDOW                    |
| O-🖱️   | custom:ONE_SHOT_MOUSE LayerHint:Mouse |
| .spc    | custom:DOT_SPC                        |
| n'      | custom:N_APOS                         |
| ver     | custom:PRINT_VERSION                  |
| CAPSL   | KC_CAPS                               |
| CAPSW   | custom:CAPS_WORDS                     |
| sn_case | custom:SNAKE_CASE                     |
| SN_CASE | custom:SCREAMING_SNAKE_CASE           |
| camCase | custom:CAMEL_CASE                     |
| PasCase | custom:PASCAL_CASE                    |
| sl/case | custom:SLASH_CASE                     |
| do.case | custom:DOT_CASE                       |
| kb-case | custom:KEBAP_CASE                     |
| OSM(S)  | OSM(MOD_LSFT)                         |
| OSM(C)  | OSM(MOD_LCTL)                         |
| OSM(A)  | OSM(MOD_LALT)                         |


## Generator

- should be usable with any keyboard layout

qmk flash -kb ferris/sweep -km zeitlinger -bl avrdude-split-left
