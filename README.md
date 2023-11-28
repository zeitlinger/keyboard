# APTex keyboard

Features

- 34 keys
- [APTex](https://github.com/Apsu/APTex) layout with slight modifications
- Home row mods (Alt, Ctrl, Shift) on all layers, except the base layer 
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

Home row mods (Alt, Ctrl, Shift) on all layers, except the base layer.

If you want modifiers for the base layer, use the shift layer.
In the shift layer, you can disable shift with the index finger that would usually enable shift.

| Modifier | Finger |
|----------|--------|
| Alt      | Ring   |
| Ctrl     | Middle |
| Shift    | Index  |

## Layout

How to read this layout:

- 💎 = combo key (e.g. middle and index finger in top row pressed together produce "b")
- 🪜 = transparent key
- ❌ = key can't be used because the layer was activated with that key
- empty = use key from base layer
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
|  Base  | b+SymR  |    c    |    g    |    d    |    p    |    '    | ,+SymL  |  .+Fn   |
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
|  Base  |  Mouse  |   💎    |   💎    | CS-f12  |    _    |   💎    |   💎    |    -    |
|  Base  |         |         |         |         |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |         |         |         |         |         |         |         |         |
|  Base  |         |         |         |         |         |         |         |         |
|  Base  |         |         |         |         |    !    |   💎    |   💎    |    ?    |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |         |         |         |         |         |         |         |         |
|  Base  |         |         |         |         |         |         |         |         |
|  Base  |         |         |   💎    |    k    |  bspc   |   💎    |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |         |         |         |         |         |         |         |         |
|  Base  |         |         |         |         |         |         |         |         |
|  Base  |         |   💎    |    j    |    x    |         | repeat  |   💎    |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |         |         |         |         |         |         |         |         |
|  Base  |         |         |   cut   | S-paste |         |         |         |         |
|  Base  |   💎    |         |  copy   |  paste  |         |         |   ↩️️   |   💎    |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |         |         |         |  "for"  |  "ny"   |         |         |         |
|  Base  |         |         |         |   💎    |   💎    |         |         |
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
|  Mods  |         |         |         |         |         |         |         |         |
|  Mods  |         |         |         |         |         |         |         |         |
|  Mods  |         |         |         |         |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Shift  |         |         |         |         |         |         |         |         |
| Shift  | r+Media |    s    |    t    | h+Shift | n+Shift |    a    |    i    |         |
| Shift  |         |         |         |         |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| NumNav |         |    6    |    5    |         |   esc   |  ⬆️⬆️   |  ⬇️⬇️   |         |
| NumNav |    4    |    3    |    2    |    1    |   ⬅️    |   ⬆️    |   ⬇️    |   ➡️    |
| NumNav |         |    9    |    8    |    7    |  ⬅️⬅️   |   ins   |   del   |  ➡️➡️   |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|   Fn   |         |   f6    |   f5    |         |         |         |         |         |
|   Fn   |   f4    |   f3    |   f2    |   f1    |         |         |         |         |    
|   Fn   |   f10   |   f9    |   f8    |   f7    |         |         |         |    ❌    |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Mouse  |         |         |         |         |  🖱️3   |  🖱️1   |  🖱️2   |         |
| Mouse  |    ❌    |    ❌    |    ❌    |  🖱️1   |  🖱️⬅️  |  🖱️⬆️  |  🖱️⬇️  |  🖱️➡️  |    
| Mouse  |         |         |         |         | 🖲️️⬅️  | 🖲️️⬆️  | 🖲️️⬇️  | 🖲️️➡️  |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Sym   |         |    ~    |    +    |    %    |    /    |    {    |    }    |         |
|  Sym   |    $    |    (    |    )    |    :    |    ;    |    [    |    ]    |    \    |    
|  Sym   |    ^    |    #    |    @    |    *    |    `    |    =    |  pipe   |    &    |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  SymL  |         |         |         |         |         |         |         |         |
|  SymL  |         |         |         |         |         |         |         |         |
|  SymL  |         |         |         |         |         |         |    ❌    |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  SymR  |         |         |         |         |         |         |         |         |
|  SymR  |         |  A-f4   |   win   |   C-w   |         |         |         |         |
|  SymR  |    ❌    |         |         |         |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Media  |         |         |         |         |         |         |         |         |
| Media  |    ❌    |   prt   |         |         |         |         |         |         |
| Media  |         |         |         |         |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |

| Thumb  | Left Inner |      Left Outer      | Right Outer |        Right Inner         |
|:------:|:----------:|:--------------------:|:-----------:|:--------------------------:|
|  Base  |   Shift    | HomeRowMods:Mods spc |      e      | ComboLayer:Sym bspc+NumNav |
|  Mods  |            |                      |             |            tab             |
| NumNav |            |          0           |      ❌      |             ❌              | 
|   Fn   |            |         f11          |     f12     |                            |
|  SymL  |            |                      |             |                            |
|  SymR  |    undo    |         tab          |             |                            |

| Options | Modifiers Left |  Modifiers Right   | Fallback Left | Fallback Right | Flags  |
|:-------:|:--------------:|:------------------:|:-------------:|:--------------:|--------|
|  Base   |                |                    |               |                |        |
|  Shift  |    HomeRow     |      HomeRow       |     Base      |      Base      |        |  
|  Mods   |    HomeRow     |      HomeRow       |     Base      |      Base      |        |  
| NumNav  |    HomeRow     |      HomeRow       |               |                |        | 
|   Fn    |                | HomeRow, BottomRow |               |                |        |  
|  Mouse  |    HomeRow     |                    |               |                |        |  
|   Sym   |    HomeRow     |      HomeRow       |               |                | Hidden | 
|  SymL   |                |                    |      Sym      |                |        | 
|  SymR   |   BottomRow    |                    |               |      Sym       |        | 
|  Media  |                |                    |               |                |        |

| Symbol  | Command        |
|---------|----------------|
| ⬅️      | KC_LEFT        |
| ⬅️⬅️    | KC_HOME        |
| ⬇️      | KC_DOWN        |
| ⬇️⬇️    | KC_PGDN        |
| ⬆️      | KC_UP          |
| ⬆️⬆️    | KC_PGUP        |
| ➡️      | KC_RIGHT       |
| ➡️➡️    | KC_END         |
| ins     | KC_INS         |
| del     | KC_DEL         |
| spc     | KC_SPC         |
| esc     | KC_ESC         |
| ↩️️     | KC_ENT         |
| bspc    | KC_BSPC        |
| win     | KC_LGUI        |
| alt     | KC_LALT        |
| tab     | KC_TAB         |
| sTab    | LSFT(KC_TAB)   |
| prt     | KC_PSCR        |
| pipe    | KC_PIPE        |
| 🖱️⬅️   | KC_MS_L        |
| 🖱️⬇️   | KC_MS_D        |
| 🖱️⬆️   | KC_MS_U        |
| 🖱️➡️   | KC_MS_R        |
| 🖲️️⬅️  | KC_WH_L        |
| 🖲️️⬇️  | KC_WH_D        |
| 🖲️️⬆️  | KC_WH_U        |
| 🖲️️➡️  | KC_WH_R        |
| 🖱️1    | KC_BTN1        |
| 🖱️2    | KC_BTN2        |
| 🖱️3    | KC_BTN3        |
| redo    | RCS(KC_Z)      |
| undo    | LCTL(KC_Z)     |
| copy    | LCTL(KC_C)     |
| paste   | LCTL(KC_V)     |
| S-paste | RCS(KC_V)      |
| cut     | LCTL(KC_X)     |
| ä       | RALT(KC_Q)     |
| ö       | RALT(KC_P)     |
| ü       | RALT(KC_Y)     |
| ß       | RALT(KC_S)     |
| '       | RALT(KC_QUOTE) |
| "       | RSA(KC_QUOTE)  |
| `       | RALT(KC_TILD)  |
| ~       | RSA(KC_TILD)   |
| 🪜      | KC_TRNS        |
| repeat  | custom:REPEAT  |
| Mouse   | custom:MOUSE   |
| .spc    | custom:DOT_SPC |
