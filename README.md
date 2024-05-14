# Hands Down Vibranium Keyboard

### Credits

- [Hands Down Keyboard Layout](https://sites.google.com/alanreiser.com/handsdown)
- [The T-34 keyboard layout](https://www.jonashietala.se/blog/2021/06/03/the-t-34-keyboard-layout/)
- [X-Case](https://github.com/andrewjrae/kyria-keymap#x-case)

### Notes

- The keyboard layout is generated using [generateKeyboard](generateKeyboard.kt) from this file.  => link to [Generator](#generator)
- The generated keyboard can be found in a
  [fork of mini-ryoku](https://github.com/zeitlinger/mini-ryoku/blob/gregor/qmk/layout.h), because this is easy to
  integrate with many keyboards
  (tested with [Ferris Sweep](https://keebmaker.com/products/ferris-sweep)).
- Use [US international keyboard layout with dead keys](https://dry.sailingissues.com/us-international-keyboard-layout.html) for German umlauts.

### Home Row Mods

On all other layers, the modifiers are as shown in the table below.

| Home Row Modifiers | Finger |
|--------------------|--------|
| Alt                | Ring   |
| Ctrl               | Middle |
| Shift              | Index  |

### Window and Tab switching

- win ➡️ and  tab ➡️ are used to Short windows and tabs.
- Once you press any of those keys, you're in switcher mode, where all other keys are replaced by shift-tab.
- Switcher mode is exited when you go back to the base layer.

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
- n @g = alt repeat key for "n" is "g". If you press "n" and then the alt repeat key, it will produce "ng"
- The symbol table at the bottom shows the meaning of the symbols used in the layout.

> **Note**: The layout is generated from this file directly.

| Layer  | L. Pin. | L. Ring | L. Mid. | L. Ind. | R. Ind. | R. Mid. | R. Ring | R. Pin. |
|:------:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|
|  Base  |   esc   |  w @s   |  m @p   |   spc   |   win   | repeat  | altRep  |         |
|  Base  |  s @p   |  c @k   |  n @g   |    t    |  a @u   |  e @o   |    i    |    h    |
|  Base  | *Right  |    f    |  l @k   |  d @g   |  u @a   |    o    |    y    |  *Left  |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |         |         |         |         |         |  O-🖱️  |   💎    |         |
|  Base  |         |         |         |         |         |         |         |         |
|  Base  |         |         |         |         |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |         |         |         |  g @l   |  "ua"   |         |         |         |
|  Base  |         |         |         |   💎    |   💎    |         |         |         |
|  Base  |         |         |         |    k    |  "ing"  |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |         |         |    x    |         |         |  .spc   |         |         |
|  Base  |         |         |   💎    |         |         |   💎    |         |         |
|  Base  |         |         |    v    |         |         |    q    |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |         |  b @l   |         |         |         |         |    j    |         |
|  Base  |         |   💎    |         |         |         |         |   💎    |         |
|  Base  |         |  p @m   |         |         |         |         |    ,    |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |         |         |         |         |         |         |         |         |
|  Base  |   💎    |         |         |         |         |         |         |   💎    |
|  Base  |    z    |         |         |         |         |         |         |  . @/   |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Right  |         |         |         |         |         |    '    |    "    |         |
| Right  |         |         | *Umlaut |  *Case  |         |         |         |         |
| Right  |   🛑    |         |         |         |         |         |         |    ?    |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Right  |         |         |         |         |         |         |   S-j   |         |
| Right  |         |         |         |         |         |         |   💎    |         |
| Right  |         |         |         |         |         |         |   S-q   |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Left  |         |         |         |         |         |         |         |         |
|  Left  |         |         |         |         |  *Sym   | *Media  |         |         |
|  Left  |    _    |         |         |         |         |         |         |   🛑    |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Left  |         |         |         |   S-g   |         |         |         |         |
|  Left  |         |         |         |   💎    |         |         |         |         |
|  Left  |         |         |         |   S-k   |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Left  |         |         |   S-x   |         |         |         |         |         |
|  Left  |         |         |   💎    |         |         |         |         |         |
|  Left  |         |         |   S-v   |         |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Left  |         |   S-b   |         |         |         |         |         |         |
|  Left  |         |   💎    |         |         |         |         |         |         |
|  Left  |         |   S-p   |         |         |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Left  |         |         |         |         |         |         |         |         |
|  Left  |   💎    |         |         |         |         |         |         |         |
|  Left  |   S-z   |         |         |         |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Nav   |         |         |         |   win   |         |   esc   |   ins   |         |
|  Nav   |  *Nav2  |   🛑    |   🛑    |   🛑    |   ⬅️    |   ⬆️    |   ⬇️    |   ➡️    |
|  Nav   |  undo   |   C-w   | tab ➡️  | win ➡️  |   ↩️️   |  bspc   |   del   |   spc   |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Nav   |         |         |         |  S-pst  |         |         |         |         |
|  Nav   |         |         |         |   💎    |         |         |         |         |
|  Nav   |         |         |         |   pst   |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Nav   |         |         |         |         |         |         |         |         |
|  Nav   |         |         |   💎    |         |         |         |         |         |
|  Nav   |         |         |  copy   |         |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Nav   |         |         |         |         |         |         |         |         |
|  Nav   |         |   💎    |         |         |         |         |         |         |
|  Nav   |         |   cut   |         |         |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Nav   |         |         |         |         |         |         |         |         |
|  Nav   |   💎    |         |         |         |         |         |         |         |
|  Nav   |  redo   |         |         |         |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Nav2  |         |         |         |         |         |         |         |         |
|  Nav2  |   🛑    |   🛑    |   🛑    |   🛑    |  ⬅️⬅️   |  ⬆️⬆️   |  ⬇️⬇️   |  ➡️➡️   |
|  Nav2  |         |         |         |         |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|   Fn   |         |   f10   |   f9    |         |         |         |         |         |
|   Fn   |   f4    |   f3    |   f2    |   f1    |   🛑    |   🛑    |   🛑    |   🛑    |
|   Fn   |   f8    |   f7    |   f6    |   f5    |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Num   |         |    \    |    9    |         |         |    {    |    }    |         |
|  Num   |    4    |    3    |    2    |    1    |    $    |    [    |    ]    |  ;+Fn   |
|  Num   |    8    |    7    |    6    |    5    |    `    |    -    |    =    |    /    |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Umlaut |         |         |         |         |         |         |         |         |
| Umlaut |         |         |   🛑    |  shift  |    ä    |    ß    |         |         |
| Umlaut |   🛑    |         |         |         |    ü    |    ö    |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Case  |         |         |         |         |         | PasCase | SN_CASE |         |
|  Case  |         |         |         |   🛑    | sl/case | camCase | sn_case |  CAPSW  |
|  Case  |   🛑    |         |         |         | do.case |  CAPSL  | kb-case |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Media  |  reset  |   🔅    |   🔆    |         |         |         |         |         |
| Media  |   prt   |   🔈    |   🔊    |   🔇    |         |   🛑    |         |         |
| Media  |   ver   |   ⏮️    |   ⏭️    |   ⏯️    |         |         |         |   🛑    |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Sym   |         |    <    |    >    |    %    |         |         |         |         |
|  Sym   |    *    |    (    |    )    |    !    |   🛑    |         |         |         |
|  Sym   |    &    |    @    |    #    |  ~ @/   |         |         |         |   🛑    |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Mouse  |         |  🖱️3   |  🖱️2   |  🖱️1   |         |         |  🖱️3   |         |
| Mouse  | *Mouse2 | KC_ACL0 | KC_ACL1 | KC_ACL2 |  🖱️⬅️  |  🖱️⬆️  |  🖱️⬇️  |  🖱️➡️  |
| Mouse  |         |   🛑    |   🛑    |   🛑    |  🖱️2   |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Mouse2 |         |         |         |         |         |         |         |         |
| Mouse2 |   🛑    |         |         |         | 🖲️️⬅️  | 🖲️️⬆️  | 🖲️️⬇️  | 🖲️️➡️  |
| Mouse2 |         |         |         |         |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |


| Thumb | Left Inner |        Left Outer        |      Right Outer       | Right Inner |
|:-----:|:----------:|:------------------------:|:----------------------:|:-----------:|
| Base  |    *Nav    |           r @k           |          spc           |    *Num     |
|       | ---------- | ------------------------ | ---------------------- | ----------- |
| Left  |            |                          |          spc           |             |
|       | ---------- | ------------------------ | ---------------------- | ----------- |
| Right |            |                          |                        |             |
|       | ---------- | ------------------------ | ---------------------- | ----------- |
|  Sym  |     ^      |            :             |           +            |    pipe     |
|       | ---------- | ------------------------ | ---------------------- | ----------- |
|  Nav  |     🛑     |            🛑            |          tab           |             |
|       | ---------- | ------------------------ | ---------------------- | ----------- |
|  Num  |            |            0             |           🛑           |     🛑      |
|       | ---------- | ------------------------ | ---------------------- | ----------- |
|  Fn   |    f11     |           f12            |                        |             |
|       | ---------- | ------------------------ | ---------------------- | ----------- |
| Mouse |            |            --            |          🖱️1          |             |
|       | ---------- | ------------------------ | ---------------------- | ----------- |

## Options

The order of the options is also the order of the layers in the layer stack.

| LayerOptions | Modifiers Left  | Modifiers Right | Fallback Left | Fallback Right | Flags   |
|:------------:|:---------------:|:---------------:|:-------------:|:--------------:|---------|
|     Base     |                 |                 |               |                |         |
|     Left     |                 | BottomRow+LMods |     Base      |                | Shifted |
|    Right     | BottomRow+RMods |                 |               |      Base      | Shifted |
|    LMods     |                 |    BottomRow    |     Base      |                |         |
|    RMods     |    BottomRow    |                 |               |      Base      |         |
|     Nav      |     HomeRow     |                 |               |                |         |
|     Nav2     |     HomeRow     |                 |               |                |         |
|     Sym      |                 |                 |               |                |         |
|     Num      |     HomeRow     |     HomeRow     |               |                |         |
|      Fn      |                 |     HomeRow     |               |                |         |
|    Mouse     |    BottomRow    |                 |               |                |         |
|    Mouse2    |                 |                 |               |                |         |
|     Case     |                 |                 |               |                |         |
|    Media     |                 |                 |               |                |         |
|    Umlaut    |                 |                 |               |                |         |

## Symbols

| Symbol  | Command                               |
|---------|---------------------------------------|
| shift   | KC_LSFT                               |
| ⬅️      | KC_LEFT                               |
| ⬅️⬅️    | KC_HOME                               |
| ⬇️      | KC_DOWN                               |
| ⬇️⬇️    | KC_PGDN                               |
| ⬆️      | KC_UP                                 |
| ⬆️⬆️    | KC_PGUP                               |
| ➡️      | KC_RIGHT                              |
| ➡️➡️    | KC_END                                |
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
| reset   | QK_BOOT                               |
| redo    | RCS(KC_Z)                             |
| undo    | C(KC_Z)                               |
| S-pst   | RCS(KC_V)                             |
| cut     | C(KC_X)                               |
| copy    | C(KC_C)                               |
| pst     | C(KC_V)                               |
| ä       | ALGR(KC_Q)                            |
| ö       | ALGR(KC_P)                            |
| ü       | ALGR(KC_Y)                            |
| ß       | ALGR(KC_S)                            |
| '       | ALGR(KC_QUOTE)                        |
| "       | ALGR(S(KC_QUOTE))                     |
| `       | ALGR(KC_GRV)                          |
| ~       | ALGR(KC_TILD)                         |
| ^       | ALGR(KC_CIRC)                         |
| repeat  | QK_REPEAT_KEY                         |
| altRep  | QK_ALT_REPEAT_KEY                     |
| tab ➡️  | custom:NEXT_TAB      NoHold           |
| win ➡️  | custom:NEXT_WINDOW   NoHold           |
| O-🖱️   | custom:ONE_SHOT_MOUSE LayerHint:Mouse |
| .spc    | custom:DOT_SPC                        |
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


## Generator

- should be usable with any keyboard layout

qmk flash -kb ferris/sweep -km zeitlinger -bl avrdude-split-left
