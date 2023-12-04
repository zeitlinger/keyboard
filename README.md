# APTex keyboard

Features

- 34 keys
- [APTex](https://github.com/Apsu/APTex) layout with slight modifications
- Home row mods (Alt, Ctrl, Shift) on all layers, except the base layer where combos are used instead to avoid timing issues (see [Modifiers](#modifiers))
- In the base layer, you have to press space and the modifier key at the same time to activate the modifier.
  This is to avoid accidental activation of the modifier.
- In the shift layer, you can disable shift with the index finger that would usually enable shift.
- Combos for keys in the two center columns,
  so lateral movement is not needed, except for special combos like `Ctrl+B`
- Combos for the most common bigrams, reducing SFBs from 0.70% to 0.26%
- Combos for the most common trigrams
- "Next sentence" key (". ", capitalizes the next letter)

Notes

- The keyboard layout is generated using [generateKeyboard](generateKeyboard.kt) from this file.
- The generated keyboard can be found in a
  [fork of mini-ryoku](https://github.com/zeitlinger/mini-ryoku/blob/main/qmk/layout.h), because this is easy to
  integrate with many keyboards
  (tested with [Ferris Sweep](https://keebmaker.com/products/ferris-sweep)).
- Use [US international keyboard layout with dead keys](https://dry.sailingissues.com/us-international-keyboard-layout.html) for German umlauts.
- [TODos](TODO.md)

## Modifiers

For the base layer, there are several options for modifiers for different typing speeds and personal preferences:

- One shot mods with a low timeout - so they don't interfere with typing fast
- Thumb combos - they can be pressed more easily compared to the one shot mods - if you want slower typing speed
- Mod layer - an extra layer with home row mods, which are even easier to press than the thumb combos  

Then you can also enable Home row mods "Layer Options" (currently disabled, because of timing issues).
                                                                                                      
You can edit the tables to adjust the modifiers to your needs.

### One Shot Mods

Remove this table to disable one shot mods.

| Base Layer One Shot Mod Combos | Fingers                    | Timeout Delta |
|--------------------------------|----------------------------|:-------------:|
| Timeout                        | 10                         |               |
| Shift                          | Ring, Middle               |               |
| Ctrl                           | Middle, Index              |               |
| Alt                            | Ring, Index                |      10       |
| Ctrl-Shift                     | Ring, Middle, Index        |               |
| Alt-Shift                      | Pinky, Ring, Middle        |               |
| Ctrl-Alt                       | Pinky, Index               |      20       |
| Ctrl-Alt-Shift                 | Pinky, Ring, Middle, Index |               |
                                                                                           
### Thumb Combos

- The thumb is defined in the layout table below as "HomeRowThumbCombo".
- The other fingers are the same as in the table above.

Remove this table to disable thumb combos.

| Base Layer Thumb Mod Combos | Fingers             |
|-----------------------------|---------------------|
| Timeout                     | 35                  |

### Mod Layer

The Mod layer is defined in the Layer table below as "Mod".

### Home Row Mods

On all other layers, the modifiers are as shown in the table below.

| Home Row Modifiers | Finger |
|--------------------|--------|
| Alt                | Ring   |
| Shift              | Middle |
| Ctrl               | Index  |

## Layout

How to read this layout:

- 💎 = combo key (e.g. middle and index finger in top row pressed together produce "b")
- 🪜 = transparent key
- ❌ = key can't be used because the layer was activated with that key
- empty = use key from base layer
- FnBra = capitalized words are layer names
- /+Ctrl = tab-mod - / on tab and CTRL on hold
- C-w = Ctrl-w (same for Alt and Shift)
- "that" = combo that produces "that"
- 80 custom timeout for combo
- The symbol table at the bottom shows the meaning of the symbols used in the layout.

> **Note**: The layout is generated from this file directly.
                                                                      
| Layer  | L. Pin. | L. Ring | L. Mid. | L. Ind. | R. Ind. | R. Mid. | R. Ring | R. Pin. |
|:------:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|
|  Base  |    /    |    w    |    m    |    f    |    y    |    o    |    u    |    -    |
|  Base  |    r    |    s    |    t    |    h    |    n    |    a    |    i    |    l    |
|  Base  |  b+Tab  |    c    |    g    |    d    |    p    |   rep   |    ,    |  .+Fn   |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |         |         |   💎    |    z    |         |    ö    |    ü    |         |
|  Base  |         |         |         |         |         |    ä    |         |    ß    |
|  Base  |         |         |         |         |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |         |   💎    |    v    |   f4    |         |         |         |         |
|  Base  |         |         |         |         |         |         |         |         |
|  Base  |         |         |         |         |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |   💎    |    q    |         |         |         |         |         |         |
|  Base  |         |         |         |         |         |         |         |         |
|  Base  |         |         |         |         |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |         |         |         |         |         |         |         |         |
|  Base  |         |         |         |         |         |         |         |         |
|  Base  |         |         |   💎    |  k 80   |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |         |         |         |         |         |         |         |         |
|  Base  |         |         |         |         |         |         |         |         |
|  Base  |         |   💎    |    j    |    x    |         |  capsW  |   💎    |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |         |         |         |         |         |         |         |         |
|  Base  |         |         |  A-f7   | S-paste |         |         |         |         |
|  Base  |   💎    | cut 100 |  copy   |  paste  |         |         |   ↩️️   |   💎    |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |         |         |         |  "for"  |  "ny"   |         |         |         |
|  Base  |         |         |         |   💎    |   💎    |         |         |         |
|  Base  |         |         |         |  "qu"   |  "ent"  |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |         |         | "the "  |         |         |  "oa"   |         |         |
|  Base  |         |         |   💎    |         |         |   💎    |         |         |
|  Base  |         |         | "and "  |         |         |  "ing"  |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |         |  "ws"   |         |         |         |         |  "ui"   |         |
|  Base  |         |   💎    |         |         |         |         |   💎    |         |
|  Base  |         |  "sc"   |         |         |         |         |  "ion"  |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |  "tio"  |         |         |         |         |         |         |  "l."   |
|  Base  |   💎    |         |         |         |         |         |         |   💎    |
|  Base  |  "br"   |         |         |         |         |         |         |  .spc   |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| ParNav |         |  redo   |  undo   |    @    |   esc   |  ⬆️⬆️   |  ⬇️⬇️   |         |
| ParNav | $+ctrl  |    (    |    )    |   tab   |   ⬅️    |   ⬆️    |   ⬇️    |   ➡️    |
| ParNav |    #    |    &    |    *    |  sTab   |   ↩️️   |   del   |  ⬅️⬅️   |  ➡️➡️   | 
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| FnBra  |         |   f6    |   f5    |         |    `    |    -    |    =    |         |
| FnBra  |   f4    |   f3    |   f2    |   f1    |    '    |    [    |    ]    |    \    |    
| FnBra  |   f10   |   f9    |   f8    |   f7    |    ;    |  aRep   |    !    |    /    |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| NumCur |         |    6    |    5    |    ^    |    ~    |    _    |    +    |         |
| NumCur |    4    |    3    |    2    |    1    |    "    |    {    |    }    |  pipe   |
| NumCur |    %    |    9    |    8    |    7    |    :    |    <    |    >    |    ?    |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Mouse  |         |         |         |         |  🖱️3   |  🖱️1   |  🖱️2   |         |
| Mouse  |  Media  |  🖱️3   |  🖱️2   |  🖱️1   |  🖱️⬅️  |  🖱️⬆️  |  🖱️⬇️  |  🖱️➡️  |    
| Mouse  |         |         |         |         | 🖲️️⬅️  | 🖲️️⬆️  | 🖲️️⬇️  | 🖲️️➡️  |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Tab   |         |         |         |         |         |         |         |         |
|  Tab   |         |  A-f4   |   win   |   C-w   |         |         |         |         |
|  Tab   |    ❌    |         |         |         |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| ParBra |         |         |         |         |         |         |         |         |
| ParBra |         |         |         |         |         |         |         |         |
| ParBra |         |         |         |         |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|   Fn   |         |         |         |         |         |         |         |         |
|   Fn   |         |         |         |         |  OSM-C  |  OSM-S  |  OSM-A  |         |
|   Fn   |         |         |         |         |  OSM-C  |  OSM-S  |  OSM-A  |    ❌    |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Media  |         |         |   prt   |         |         |   🔅    |   🔆    |         |
| Media  |    ❌    |   🔈    |   🔊    |   🔇    |   ⏯️    |   ⏮️    |   ⏭️    |         |
| Media  |         |         |         |         |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |

| Thumb  | Left Inner |        Left Outer        |      Right Outer       | Right Inner |                         
|:------:|:----------:|:------------------------:|:----------------------:|:-----------:|
|  Base  | tab+ParNav | ComboLayer:ParBra,20 spc | ComboLayer:NumCur,20 e | bspc+NumCur |
|  Base  |     💎     |                          |                        |    Mouse    |
|  Base  |            |            0             |                        |     💎      |
| ParNav |     ❌      |            ❌             |          tab           |    bspc     | 
 | NumCur |    spc     |            0             |           ❌            |      ❌      |
|   Fn   |            |           f11            |          f12           |             |
|  Tab   |    sTab    |           tab            |          undo          |    redo     |

## Options

A note on layer names:

Par = Parentheses        (
Cur = Curly Parentheses  {
Bra = Brackets           [

| LayerOptions | Modifiers Left |  Modifiers Right   | Fallback Left | Fallback Right | Flags  |
|:------------:|:--------------:|:------------------:|:-------------:|:--------------:|--------|
|     Base     |                |                    |               |                |        |
|    ParNav    |    HomeRow     |                    |               |                |        |
|    FnBra     |                |                    |               |                | Hidden |
|    NumCur    |                |      HomeRow       |               |                |        |
|      Fn      |                | HomeRow, BottomRow |     FnBra     |                |        |
|    Mouse     |    HomeRow     |                    |               |                |        |
|     Tab      |   BottomRow    |                    |               |     FnBra      |        |
|    Media     |                |                    |               |                |        |
|    ParBra    |                |                    |    ParNav     |     FnBra      | Hidden | 

| Symbol  | Command             |                                     
|---------|---------------------|
| ⬅️      | KC_LEFT             |
| ⬅️⬅️    | KC_HOME             |                                     
| ⬇️      | KC_DOWN             |
| ⬇️⬇️    | KC_PGDN             |
| ⬆️      | KC_UP               |
| ⬆️⬆️    | KC_PGUP             |
| ➡️      | KC_RIGHT            |
| ➡️➡️    | KC_END              |
| ins     | KC_INS              |
| del     | KC_DEL              |
| spc     | KC_SPC              |
| esc     | KC_ESC              |
| ↩️️     | KC_ENT              |                           
| bspc    | KC_BSPC             |
| win     | KC_LGUI             |
| alt     | KC_LALT             |
| tab     | KC_TAB              |
| sTab    | S(KC_TAB)           |
| prt     | KC_PSCR             |
| pipe    | KC_PIPE             |
| 🖱️⬅️   | KC_MS_L             |
| 🖱️⬇️   | KC_MS_D             |
| 🖱️⬆️   | KC_MS_U             |
| 🖱️➡️   | KC_MS_R             |
| 🖲️️⬅️  | KC_WH_L             |
| 🖲️️⬇️  | KC_WH_D             |
| 🖲️️⬆️  | KC_WH_U             |        
| 🖲️️➡️  | KC_WH_R             |
| 🖱️1    | KC_BTN1             |
| 🖱️2    | KC_BTN2             |
| 🖱️3    | KC_BTN3             |
| 🔇      | KC_MUTE             |
| ⏯️      | KC_MPLY             |
| ⏮️      | KC_MPRV             |
| ⏭️      | KC_MNXT             |
| 🔊      | KC_VOLU             |
| 🔈      | KC_VOLD             |
| 🔆      | KC_BRIU             |
| 🔅      | KC_BRID             |
| redo    | RCS(KC_Z)           |
| undo    | C(KC_Z)             |
| $+ctrl  | CTL_T(KC_DLR)       |
| copy    | C(KC_C)             |
| paste   | C(KC_V)             |
| S-paste | RCS(KC_V)           |
| cut     | C(KC_X)             |
| ä       | ALGR(KC_Q)          |
| ö       | ALGR(KC_P)          |                                         
| ü       | ALGR(KC_Y)          |
| ß       | ALGR(KC_S)          |
| '       | ALGR(KC_QUOTE)      |
| "       | ALGR(KC_DQUO)       |
| `       | ALGR(KC_GRV)        |
| ~       | ALGR(KC_TILD)       |
| ^       | ALGR(KC_CIRC)       |
| 🪜      | KC_TRNS             |
| rep     | QK_REPEAT_KEY       |
| aRep    | QK_ALT_REPEAT_KEY   |
| capsW   | QK_CAPS_WORD_TOGGLE |
| Mouse   | custom:MOUSE        |
| .spc    | custom:DOT_SPC      |
| OSM-A   | OSM(MOD_LALT)       |
| OSM-S   | OSM(MOD_LSFT)       |
| OSM-C   | OSM(MOD_LCTL)       |
