# APTex keyboard
   
## Overview

TODO: update overview

### Goals

- Fast typing
  - No home row mods on base layer that easily interfere with typing
  - No auto shift or tap dance
  - combos for the most common bigrams and trigrams
  - combos for the most common same finger bigrams
- No lateral movement
  - Inner columns are not used
- All modifiers can be used with all keys
  - All modifiers except GUI can be used with all keys
- Support for German umlauts and the most common IntelliJ shortcuts

### Features

- 34 keys, but only 26 keys are needed for typing
- [APTex](https://github.com/Apsu/APTex) layout with slight modifications
- Home row mods (Alt, Ctrl, Shift) on all layers, except the base layer where combos are used instead to avoid timing issues (see [Modifiers](#modifiers))
- In the base layer, you have to press space and the modifier key at the same time to activate the modifier.
  This is to avoid accidental activation of the modifier.
- In the shift layer, you can disable shift with the index finger that would usually enable shift.
- Combos for keys in the two center columns,
  so lateral movement is not needed, except for special combos like `Ctrl+B`
- Combos for the most common bigrams, reducing SFBs from 0.70% to 0.26% (all bigrams with a frequency of 0.020% or higher are covered with combos)
- Combos for the most common trigrams
- "Next sentence" key (". ", capitalizes the next letter)
- Needs https://github.com/bdaase/remove-alt-tab-delay on Ubuntu

### Credits

- [The T-34 keyboard layout](https://www.jonashietala.se/blog/2021/06/03/the-t-34-keyboard-layout/)
- [APTex](https://github.com/Apsu/APTex)
- [X-Case](https://github.com/andrewjrae/kyria-keymap#x-case)    

### Notes

- The keyboard layout is generated using [generateKeyboard](generateKeyboard.kt) from this file.  => link to [Generator](#generator)
- The generated keyboard can be found in a
  [fork of mini-ryoku](https://github.com/zeitlinger/mini-ryoku/blob/gregor/qmk/layout.h), because this is easy to
  integrate with many keyboards
  (tested with [Ferris Sweep](https://keebmaker.com/products/ferris-sweep)).
- Use [US international keyboard layout with dead keys](https://dry.sailingissues.com/us-international-keyboard-layout.html) for German umlauts.
- [TODos](TODO.md)

## Modifiers
    
TODO: update this section 

For the base layer, there are several options for modifiers for different typing speeds and personal preferences:

- One shot mods with a low timeout - so they don't interfere with typing fast 
  (currently only used for alt, ctrl and shift, but not any combination of those)
- Thumb combos - they can be pressed more easily compared to the one shot mods - 
  if you want slower typing speed (currently used)
- Mod layer - an extra layer with home row mods, which are even easier to press than the thumb combos
  (currently unused)
- One shot mods on a layer

Then you can also enable Home row mods "Layer Options" (currently disabled, because of timing issues).

You can edit the tables to adjust the modifiers to your needs.

### One Shot Mods

Remove this table to disable one shot mods.

| Base Layer One Shot Mod Combos | Fingers             | Timeout Delta |
|--------------------------------|---------------------|:-------------:|
| Timeout                        | 12                  |               |

| Ctrl                           | Middle, Index       |               |
| Shift                          | Ring, Middle        |               |
| Alt                            | Ring, Index         |      10       |
| Ctrl-Shift                     | Ring, Middle, Index |      10       |

more combos if you want to use the pinky finger for mods:

| Ctrl-Shift                     | Middle, Lower Index |      20       |
| Alt-Shift                      | Ring, Lower Index   |      20       |
| Ctrl-Alt                       | Pinky, Lower Index  |      20       |
| Ctrl-Alt-Shift                 | Pinky, Middle       |      30       |

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
| Ctrl               | Middle |
| Shift              | Index  |

### Window and Tab switching

- win ➡️ and  tab ➡️ are used to Short windows and tabs.
- Once you press any of those keys, you're in switcher mode, where all other keys are replaced by shift-tab.
- Switcher mode is exited when you go back to the base layer.

## Layer Navigation

TODO: update this section 
                
For most cases, the modifiers are pressed with the same hand that was used to activate a layer. 
For example, if you want to press shift+left, you press 

- left inner thumb
- then left middle finger (on home row)
- then the left button on the right side (index finger on home row)
                           
The only exception to this rule are modifiers for the base layer, where you have multiple options:

- You can use home row one shot combos for single modifiers (e.g. left ring finger + left middle finger for shift)
- For shift-N, use the following sequence
  - right inner thumb (for Fn layer)
  - left middle finger (this will activate the base layer with home row mods and activate shift at the same time)
  - right index finger (for N)
- for ctrl-shift-N, use the following sequence
  - right inner thumb (for Fn layer)
  - left middle finger (this will activate the base layer with home row mods and activate shift at the same time)
  - left index finger (for ctrl) - you can press this key before the middle finger
  - right index finger (for N) 

Here's the navigation tree:
       
- Base Layer
  - Left inner thumb: `TabNav`
    - Left Pinky: `Nav2` 
      - this is a two-step activation, but it's very easy to combine with mods, because it's a rolling sequence
    - Any home row mod on the right side: `BaseMods` - base Layer with home row mods
      - this can be used for the base layer with modifiers on the left side, e.g. ctrl-alt-r
  - Right inner thumb: `Fn`
    - Right pinky: `Num`
    - Right lower pinky: `Media`
    - Any home row mod on the left side: `BaseMods` - base Layer with home row mods
  - Combos for symbols numbers and symbols and `Mouse` layer
  - 
## Layout

How to read this layout:

- 💎 = combo key (e.g. middle and index finger in top row pressed together produce "b")
- 🛑 = key can't be used because the layer was activated with that key or because it's reserved for a modifier
- empty = use key from base layer
- FnBra = capitalized words are layer names - if they are a key, the layer is activated as toggled or one shot layer (if the "OneShot" flag is set in the layer flags)
- /+Ctrl = tab-mod - / on tab and CTRL on hold
- *Mouse = layer is active while key is held
- C-w = Ctrl-w (same for Alt and Shift)
- -- = deactivate current layer
- "that" = combo that produces "that"
- 80 custom timeout for combo
- The symbol table at the bottom shows the meaning of the symbols used in the layout.

> **Note**: The layout is generated from this file directly.

| Layer  | L. Pin. | L. Ring | L. Mid. | L. Ind. | R. Ind. | R. Mid. | R. Ring | R. Pin. |
|:------:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|
|  Base  |         |    w    |    m    |    p    |    y    |    o    |    u    |         |
|  Base  |    r    |    s    |    t    |    h    | Leader  |    a    |    i    |    l    |
|  Base  |    b    |    c    |    g    |    d    |    n    |   rep   |  aRep   |    f    |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |         |   💎    |  Mouse  |   f4    |         |         |         |         |
|  Base  |         |         |         |         |         |         |         |         |
|  Base  |         |         |         |         |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |         |         |         |         |         |         |         |         |
|  Base  |         |         |         |         |         |         |         |         |
|  Base  |         |         |   💎    |   win   |  bspc   |   💎    |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |         |         |         |         |         |         |         |         |
|  Base  |         |         |         |         |         |         |         |         |
|  Base  |         |   💎    |  CS-f   |  O-🖱️  |   esc   |   tab   |   💎    |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |         |         |         |         |         |         |         |         |
|  Base  |         |         |  A-f7   |  S-pst  |         |         |         |         |
|  Base  |   💎    |   cut   |  copy   |  paste  |         |         |   ↩️️   |   💎    |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |         |         |         |  "ph"   |  "ny"   |         |         |         |
|  Base  |         |         |         |   💎    |   💎    |         |         |         |
|  Base  |         |         |         |   n'    |  "ay"   |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |         |         |  "nv"   |         |         |  "oa"   |         |         |
|  Base  |         |         |   💎    |         |         |   💎    |         |         |
|  Base  |         |         |  "qu"   |         |         |  "ing"  |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |         |  "ws"   |         |         |         |         |  "ui"   |         |
|  Base  |         |   💎    |         |         |         |         |   💎    |         |
|  Base  |         |  "sc"   |         |         |         |         |  "ion"  |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |  "kn"   |         |         |         |         |         |         |  "nk"   |
|  Base  |   💎    |         |         |         |         |         |         |   💎    |
|  Base  |  "br"   |         |         |         |         |         |         |  "fl"   |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Leader |         | Umlaut  |    v    |    q    |  Media  |  Short  |    '    |         |
| Leader |   Fn    | A-Right | C-Right | S-Right |    -    | S-Left  | C-Left  | A-Left  |
| Leader |    z    |    j    |    k    |   Nav   |  Smile  |    ,    |    .    |    x    |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Right  |         |         |         |         |         |         |         |         |
| Right  |         |   🛑    |   🛑    |   🛑    |    e    |         |         |         |
| Right  |         |         |         |         |         |    ,    |    .    |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Left  |         |         |         |         |         |         |         |         |
|  Left  |         |         |         |         |   ins   | OSM(S)  | OSM(C)  | OSM(A)  |
|  Left  |         |         |         |         |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Short  |         |  -C-w   |  -undo  |  -redo  |         |         |         |         |
| Short  |  CA-[   | tab ➡️  | win ➡️  |  CA-]   |         |         |         |         |
| Short  | -S-pst  |  -cut   |  -copy  | -paste  |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Nav   |         |         |         |         |   esc   |  Short  |   ins   |         |
|  Nav   |  *Nav2  |   🛑    |   🛑    |   🛑    |   ⬅️    |   ⬆️    |   ⬇️    |   ➡️    |
|  Nav   |         |         |         |         |   ↩️️   |  bspc   |   del   |   esc   |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Nav2  |         |         |         |         |         |         |         |         |
|  Nav2  |   🛑    |   🛑    |   🛑    |   🛑    |  ⬅️⬅️   |  ⬆️⬆️   |  ⬇️⬇️   |  ➡️➡️   |
|  Nav2  |         |         |         |         |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| CurBra |         |    {    |    }    |         |         |    [    |    ]    |         |
| CurBra |    #    |   🛑    |   🛑    |   🛑    |    ;    |    -    |    !    |    ?    |
| CurBra |         |  pipe   |    *    |    +    |    `    |    =    |    \    |    /    |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Umlaut |         | PasCase | SN_CASE |         |         |    ö    |    ü    |         |
| Umlaut | sl/case | camCase | sn_case |  CAPSW  |    :    |    ä    |    _    |    ~    |
| Umlaut | do.case |  CAPSL  | kb-case |         |    &    |    ^    |    %    |    ß    |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| ParNum |         |    (    |    )    |         |    4    |    5    |    6    |         | 
| ParNum |    $    |   🛑    |   🛑    |   🛑    |    0    |    1    |    2    |    3    |  
| ParNum |         |         |         |    @    |    7    |    8    |    9    |         | 
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|   Fn   |         |         |         |         |   f4    |   f5    |   f6    |         |
|   Fn   |         |   🛑    |   🛑    |   🛑    |   f10   |   f1    |   f2    |   f3    |
|   Fn   |         |         |         |         |   f7    |   f8    |   f9    |   f11   |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Mouse  |         |  🖱️3   |  🖱️2   |  🖱️1   |         |  Short  |  🖱️3   |         |
| Mouse  | *Mouse2 | KC_ACL0 | KC_ACL1 | KC_ACL2 |  🖱️⬅️  |  🖱️⬆️  |  🖱️⬇️  |  🖱️➡️  |
| Mouse  |         |   🛑    |   🛑    |   🛑    |  🖱️2   |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Mouse2 |         |         |         |         |         |         |         |         |
| Mouse2 |   🛑    |         |         |         | 🖲️️⬅️  | 🖲️️⬆️  | 🖲️️⬇️  | 🖲️️➡️  |
| Mouse2 |         |         |         |         |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Media  |         |   🔅    |   🔆    |         |   🛑    |  -prt   |   ⏯️    |         |
| Media  |         |   🔈    |   🔊    |         |         |         |         |  -ver   |
| Media  |         |   ⏮️    |   ⏭️    |         |         |         |         |         | 
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |

| Thumb  | Left Inner |        Left Outer        |      Right Outer       | Right Inner |
|:------:|:----------:|:------------------------:|:----------------------:|:-----------:|
|  Base  |   Short    |           spc            |           e            |             |
|        | ---------- | ------------------------ | ---------------------- | ----------- |
|  Left  |            |           spc            |          ↩️️           |             |
|        | ---------- | ------------------------ | ---------------------- | ----------- |
| Right  |            |          ParNum          |         CurBra         |             |
|        | ---------- | ------------------------ | ---------------------- | ----------- |
| Mouse  |   Short    |            --            |          🖱️1          |             |
|        | ---------- | ------------------------ | ---------------------- | ----------- |
| Leader |            |          ParNum          |         CurBra         |             |
|        | ---------- | ------------------------ | ---------------------- | ----------- |
|   Fn   |            |            --            |          f12           |             |
|        | ---------- | ------------------------ | ---------------------- | ----------- |
| Smile  |            |            --            |                        |             |
|        | ---------- | ------------------------ | ---------------------- | ----------- |
| Short  |     --     |            --            |                        |             |
|        | ---------- | ------------------------ | ---------------------- | ----------- |
|  Nav   |   Short    |            --            |          tab           |             |
|        | ---------- | ------------------------ | ---------------------- | ----------- |
| Media  |            |            --            |           🔇           |             |
|        | ---------- | ------------------------ | ---------------------- | ----------- |
| ParNum |            |            --            |          tab           |             |
|        | ---------- | ------------------------ | ---------------------- | ----------- |
| CurBra |            |           .spc           |                        |             |
|        | ---------- | ------------------------ | ---------------------- | ----------- |
| Umlaut |            |            --            |           "            |             |
|        | ---------- | ------------------------ | ---------------------- | ----------- |
 
## Options

The order of the options is also the order of the layers in the layer stack.

A note on layer names:

Par = Parentheses        (
Cur = Curly Parentheses  {
Bra = Brackets           [

| LayerOptions |  Modifiers Left  | Modifiers Right | Fallback Left | Fallback Right | Flags      |
|:------------:|:----------------:|:---------------:|:-------------:|:--------------:|------------|
|     Base     |                  |                 |               |                |            |
|    Leader    |                  |                 |               |                | OneShot    |
|     Left     |                  |                 |     Base      |     Leader     | OneShot    |
|    Right     |  OneShotHomeRow  |                 |    Leader     |      Base      | OneShot    |
|      Fn      |  OneShotHomeRow  |                 |               |                | OneShot    |
|    Mouse     | OneShotBottomRow |                 |               |                |            |
|    Mouse2    |                  |                 |               |                |            |
|     Nav      |  OneShotHomeRow  |                 |     Short     |                | No OneShot |
|    Short     |                  |                 |               |                |            |
|     Nav2     |  OneShotHomeRow  |                 |               |                |            |
|    ParNum    |  OneShotHomeRow  |                 |               |                | OneShot    |
|    CurBra    |  OneShotHomeRow  |                 |               |                | OneShot    |
|    Media     |                  |                 |               |                |            |
|    Smile     |                  |                 |               |                |            |
|    Umlaut    |                  |                 |               |                | OneShot    |
                                                                                                         

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
