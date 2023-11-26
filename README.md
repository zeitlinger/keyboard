# APTex keyboard

Features

- 34 keys
- [APTex](https://github.com/Apsu/APTex) layout with slight modifications
- Home row mods (Alt, Ctrl, Shift) on all layers, except the base layer 
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
- [TODos](TODO.md)

## Modifiers

| Modifier | Finger |
|----------|--------|
| Alt      | Ring   |
| Ctrl     | Middle |
| Shift    | Index  |

## Layout

How to read this layout:

- 💎 = combo key (e.g. middle and index finger in top row pressed together produce "b")
- 🪜 = transparent key
- Alt = capitalized words are layer names
- /+Ctrl = tab-mod - / on tab and CTRL on hold
- C-w = Ctrl-w (same for Alt and Shift)
- "that" = combo that produces "that"
- The symbol table at the bottom shows the meaning of the symbols used in the layout.

> **Note**: The layout is generated from this file directly.

| Layer  | L. Pin. | L. Ring | L. Mid. | L. Ind. | R. Ind. | R. Mid. | R. Ring | R. Pin. |
|:------:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|
|  Base  |    /    |    w    |    m    |    f    |    y    |    o    |    u    |    -    |
|  Base  |    r    |    s    |    t    |    h    |    n    |    a    |    i    |    l    |
|  Base  | b+Mouse |  c+Sym  |    g    |    d    |    p    |    '    |  ,+Sym  |  .+Fn   |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |         |         |   💎    |    z    |         |    ö    |    ü    |         |
|  Base  |         |         |         |         |         |    ä    |         |    ß    |
|  Base  |         |         |         |         |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |         |   💎    |    v    |         |         |         |         |         |
|  Base  |         |         |         |         |         |         |         |         |
|  Base  |         |         |         |         |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |   💎    |    q    |         |         |         |         |         |         |
|  Base  |         |         |         |         |         |         |         |         |
|  Base  |         |         |         |         |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |         |         |         |         |         |         |         |         |
|  Base  |         |         |         |         |         |         |         |         |
|  Base  |         |         |   💎    |    k    |  bspc   |   💎    |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |         |         |         |         |         |         |         |         |
|  Base  |         |         |         |         |         |         |         |         |
|  Base  |         |   💎    |    j    |    x    |         |   tab   |   💎    |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |         |         |         |         |         |         |         |         |
|  Base  |         | altTab  |  copy   |   A-w   |         |         |         |         |
|  Base  |   💎    | ctrlTab |  paste  | CS-f12  |         |         |   ↩️️   |   💎    |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |         |         |         |         |         |         |         |         |
|  Base  |         |         |   💎    |   cut   |         |         |         |         |
|  Base  |   💎    |         |         |         |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |         |         |         |         |         |         |         |         |
|  Base  |         |         |         |         |         |         |         |         |
|  Base  |   💎    |         |   💎    | S-paste |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |         |         |         |  "qu"   |  "ny"   |         |         |         |
|  Base  |         |         |         |   💎    |   💎    |         |         |
|  Base  |         |         |         |         |  "yp"   |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |         |         |  "tm"   |         |         |  "oa"   |         |         |
|  Base  |         |         |   💎    |         |         |   💎    |         |         |
|  Base  |         |         |  "cs"   |         |         |  "ing"  |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |         |  "ws"   |         |         |         |         |  "ui"   |         |
|  Base  |         |   💎    |         |         |         |         |   💎    |         |
|  Base  |         |  "sc"   |         |         |         |         |  "ion"  |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |  "sw"   |         |         |         |         |         |         |  "l."   |
|  Base  |   💎    |         |         |         |         |         |         |   💎    |
|  Base  |  "br"   |         |         |         |         |         |         |  .spc   |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Shift  |   🪜    |   🪜    |   🪜    |   🪜    |   🪜    |   🪜    |   🪜    |   🪜    |
| Shift  | r+Media |    s    |    t    | h+Shift | n+Shift |    a    |    i    |   🪜    |
| Shift  |   🪜    |   🪜    |   🪜    |   🪜    |   🪜    |   🪜    |   🪜    |   🪜    |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| NumNav |    8    |    7    |    6    |    5    |  ⬅️⬅️   |  ⬆️⬆️   |  ⬇️⬇️   |  ➡️➡️   |
| NumNav |    4    |    3    |    2    |    1    |   ⬅️    |   ⬆️    |   ⬇️    |   ➡️    |
| NumNav |   prt   |   tab   |   esc   |    9    |   ↩️️   |   ins   |   del   |   win   |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|   Fn   |   f8    |   f7    |   f6    |   f5    |         |         |         |         |
|   Fn   |   f4    |   f3    |   f2    |   f1    |         |         |         |         |    
|   Fn   |   f12   |   f11   |   f10   |   f9    |         |         |         |   🪜    |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Mouse  |         |         |         |         |  🖱️3   |  🖱️1   |  🖱️2   |         |
| Mouse  |         |         |         |         |  🖱️⬅️  |  🖱️⬆️  |  🖱️⬇️  |  🖱️➡️  |    
| Mouse  |         |   🪜    |  🖱️1   |  🖱️2   | 🖲️️⬅️  | 🖲️️⬆️  | 🖲️️⬇️  | 🖲️️➡️  |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Sym   |         |    ~    |    +    |    %    |    !    |    {    |    }    |         |
|  Sym   |    $    |    (    |    )    |    :    |    ;    |    [    |    ]    |    \    |    
|  Sym   |    ^    |    #    |    @    |    *    |    `    |    =    |  pipe   |    &    |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Media  |         |         |         |         |         |         |         |         |
| Media  |   🪜    |         |         |         |         |         |         |         |
| Media  |         |         |         |         |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Alt   |         |         |         |         |         |         |         |         |
|  Alt   |         |   🪜    |   tab   |  S-tab  |         |         |         |         |
|  Alt   |   🪜    |         |         |         |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Ctrl  |         |         |         |         |         |         |         |         |
|  Ctrl  |         |         |         |         |         |         |         |         |
|  Ctrl  |   🪜    |   🪜    |   tab   |  S-tab  |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |

| Thumb  | Left Inner | Left Outer | Right Outer |        Right Inner         |
|:------:|:----------:|:----------:|:-----------:|:--------------------------:|
|  Base  |   Shift    |    spc     |      e      | ComboLayer:Sym bspc+NumNav |
| Shift  |     🪜     |     🪜     |     🪜      |            bspc            |  
| NumNav |    tab     |     0      |     🪜      |             🪜             | 

| Modifiers |  Left   | Right   |
|:---------:|:-------:|---------|
|   Base    |         |         |
|   Shift   | HomeRow | HomeRow |  
|  NumNav   | HomeRow | HomeRow | 
|    Fn     |         | HomeRow |  
|   Mouse   | HomeRow |         |  
|    Sym    | HomeRow | HomeRow | 
|   Media   |         |         |
|    Alt    |         |         |
|   Ctrl    |         |         |

| Symbol  | Command    |
|---------|------------|
| ⬅️      | KC_LEFT    |
| ⬅️⬅️    | KC_HOME    |
| ⬇️      | KC_DOWN    |
| ⬇️⬇️    | KC_PGDN    |
| ⬆️      | KC_UP      |
| ⬆️⬆️    | KC_PGUP    |
| ➡️      | KC_RIGHT   |
| ➡️➡️    | KC_END     |
| ins     | KC_INS     |
| del     | KC_DEL     |
| spc     | KC_SPC     |
| esc     | KC_ESC     |
| ↩️️     | KC_ENT     |
| bspc    | KC_BSPC    |
| win     | KC_LGUI    |
| tab     | KC_TAB     |
| prt     | KC_PSCR    |
| pipe    | KC_PIPE    |
| 🖱️⬅️   | KC_MS_L    |
| 🖱️⬇️   | KC_MS_D    |
| 🖱️⬆️   | KC_MS_U    |
| 🖱️➡️   | KC_MS_R    |
| 🖲️️⬅️  | KC_WH_L    |
| 🖲️️⬇️  | KC_WH_D    |
| 🖲️️⬆️  | KC_WH_U    |
| 🖲️️➡️  | KC_WH_R    |
| 🖱️1    | KC_BTN1    |
| 🖱️2    | KC_BTN2    |
| 🖱️3    | KC_BTN3    |
| redo    | RCS(KC_Z)  |
| undo    | LCTL(KC_Z) |
| copy    | LCTL(KC_C) |
| paste   | LCTL(KC_V) |
| S-paste | RCS(KC_V)  |
| cut     | LCTL(KC_X) |
| ä       | RALT(KC_Q) |
| ö       | RALT(KC_P) |
| ü       | RALT(KC_Y) |
| ß       | RALT(KC_S) |
| 🪜      | KC_TRNS    |
| altTab  | KC_F22     |
| ctrlTab | KC_F23     |
| .spc    | KC_F24     |
