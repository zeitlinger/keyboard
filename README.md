# APTex keyboard

Features

- 34 keys
- [APTex](https://github.com/Apsu/APTex) layout with slight modifications
- Home row mods (Alt, Ctrl, Shift) on all layers, 
  except the base layer where combos are used instead to avoid timing issues (see [Modifiers](#modifiers))
- Combos for keys in the two center columns, 
  so lateral movement is not needed, except for special combos like `Ctrl+B`
- Combos for the most common bigrams, reducing SFBs from 0.70% to 0.26%
- Combos for the most common trigrams
- "Next sentence" key (". ", capitalizes the next letter)

Notes
  
- The keyboard layout is generated using [generateKeyboard](generateKeyboard.kt) from this file.
- The generated keyboard can be found in a 
  [fork of mini-ryoku](https://github.com/zeitlinger/mini-ryoku/blob/main/qmk/layout.h), because this is easy to integrate with many keyboards (Tested with Ferris Sweep).
- [TODos](TODO.md)

## Modifiers

Base Layer Modifiers
                    
| Modifiers      | Fingers                    |
|----------------|----------------------------|
| Shift          | Middle, Index              |
| Ctrl           | Ring, Middle               |
| Alt            | Pinky, Ring                |
| Ctrl-Shift     | Ring, Middle, Index        |
| Alt-Shift      | Pinky, Index               |
| Ctrl-Alt       | Pinky, Ring, Middle        |
| Ctrl-Alt-Shift | Pinky, Ring, Middle, Index |

Modifier for all other layers
                 
| Modifier | Finger |
|----------|--------|
| Alt      | Ring   |
| Ctrl     | Middle |
| Shift    | Index  |

                        
## Layout
                                                                            
How to read this layout:
                      
- 💎 = combo key (e.g. middle and index finger in top row pressed together produce "b")
- 🪜 = transparent key
- "that" = combo that produces "that"
- The symbol table at the bottom shows the meaning of the symbols used in the layout.

> **Note**: The layout is generated from this file directly.

| Layer  |   Left Pinky   | L. Ring | L. Mid. |   Left Index   | L. Index | R. Index |  Right Index   | R. Mid. | R. Ring | R. Pin. |
|:------:|:--------------:|:-------:|:-------:|:--------------:|:--------:|:--------:|:--------------:|:-------:|:-------:|:-------:|
|  Base  |       /        |    c    |    m    |       f        |    q     |    z     |       y        |    o    |    u    |    -    |
|  Base  |       r        |    s    |    t    |       h        |    v     |    b     |       n        |    a    |    i    |    l    |
|  Base  |       x        |    w    |    g    |       d        |    k     |    j     |       p        |    '    |    ,    |    .    |
|        | -------------- | ------- | ------- | -------------- | -------- | -------- | -------------  | ------- | ------- | ------- |
|  Base  |                |         |         |                |          |    ß     |       💎       |         |         |         |
|  Base  |                |         |         |                |          |          |                |         |         |         |
|  Base  |                |         |         |                |          |          |                |         |         |         |
|        | -------------- | ------- | ------- | -------------- | -------- | -------- | -------------  | ------- | ------- | ------- |
|  Base  |                |         |   💎    |       b        |          |          |       ä        |   💎    |         |         |
|  Base  |                |         |         |                |          |          |                |         |         |         |
|  Base  |                |         |         |                |          |          |                |         |         |         |
|        | -------------- | ------- | ------- | -------------- | -------- | -------- | -------------  | ------- | ------- | ------- |
|  Base  |                |   💎    |    v    |                |          |          |                |    ö    |   💎    |         |
|  Base  |                |         |         |                |          |          |                |         |         |         |
|  Base  |                |         |         |                |          |          |                |         |         |         |
|        | -------------- | ------- | ------- | -------------- | -------- | -------- | -------------  | ------- | ------- | ------- |
|  Base  |       💎       |    z    |         |                |          |          |                |         |    ü    |   💎    |
|  Base  |                |         |         |                |          |          |                |         |         |         |
|  Base  |                |         |         |                |          |          |                |         |         |         |
|        | -------------- | ------- | ------- | -------------- | -------- | -------- | -------------  | ------- | ------- | ------- |
|  Base  |                |         |         |                |          |          |                |         |         |         |
|  Base  |                |         |         |                |          |          |                |         |         |         |
|  Base  |                |         |   💎    |       k        |          |          |      Bspc      |   💎    |         |         |
|        | -------------- | ------- | ------- | -------------- | -------- | -------- | -------------  | ------- | ------- | ------- |
|  Base  |                |         |         |                |          |          |                |         |         |         |
|  Base  |                |         |         |                |          |          |                |         |         |         |
|  Base  |                |   💎    |    j    |                |          |          |                |   Del   |   💎    |         |
|        | -------------- | ------- | ------- | -------------- | -------- | -------- | -------------  | ------- | ------- | ------- |
|  Base  |                |         |         |                |          |          |                |         |         |         |
|  Base  |                |         |         |                |          |          |                |         |         |         |
|  Base  |       💎       |    q    |         |                |          |          |                |         |   ↩️️   |   💎    |
|        | -------------- | ------- | ------- | -------------- | -------- | -------- | -------------  | ------- | ------- | ------- |
|  Base  |                |         |         |       💎       |          |          |       💎       |         |         |         |
|  Base  |                |         |         |     "tha"      |          |          |      "ny"      |         |         |         |
|  Base  |                |         |         |                |          |          |                |         |         |         |
|        | -------------- | ------- | ------- | -------------- | -------- | -------- | -------------  | ------- | ------- | ------- |
|  Base  |                |         |   💎    |                |          |          |                |   💎    |         |         |
|  Base  |                |         |  "the"  |                |          |          |                |  "oa"   |         |         |
|  Base  |                |         |         |                |          |          |                |         |         |         |
|        | -------------- | ------- | ------- | -------------- | -------- | -------- | -------------  | ------- | ------- | ------- |
|  Base  |                |   💎    |         |                |          |          |                |         |   💎    |         |
|  Base  |                |  "sc"   |         |                |          |          |                |         |  "ui"   |         |
|  Base  |                |         |         |                |          |          |                |         |         |         |
|        | -------------- | ------- | ------- | -------------- | -------- | -------- | -------------  | ------- | ------- | ------- |
|  Base  |       💎       |         |         |                |          |          |                |         |         |   💎    |
|  Base  |     "hat"      |         |         |                |          |          |                |         |         |  "her"  |
|  Base  |                |         |         |                |          |          |                |         |         |         |
|        | -------------- | ------- | ------- | -------------- | -------- | -------- | -------------  | ------- | ------- | ------- |
|  Base  |                |         |         |                |          |          |                |         |         |         |
|  Base  |                |         |         |     "for"      |          |          |     "ent"      |         |         |         |
|  Base  |                |         |         |       💎       |          |          |       💎       |         |         |         |
|        | -------------- | ------- | ------- | -------------- | -------- | -------- | -------------  | ------- | ------- | ------- |
|  Base  |                |         |         |                |          |          |                |         |         |         |
|  Base  |                |         |  "ing"  |                |          |          |                |  "and"  |         |         |
|  Base  |                |         |   💎    |                |          |          |                |   💎    |         |         |
|        | -------------- | ------- | ------- | -------------- | -------- | -------- | -------------  | ------- | ------- | ------- |
|  Base  |                |         |         |                |          |          |                |         |         |         |
|  Base  |                |  "you"  |         |                |          |          |                |         |  "ion"  |         |
|  Base  |                |   💎    |         |                |          |          |                |         |   💎    |         |
|        | -------------- | ------- | ------- | -------------- | -------- | -------- | -------------  | ------- | ------- | ------- |
|  Base  |                |         |         |                |          |          |                |         |         |         |
|  Base  |     "tio"      |         |         |                |          |          |                |         |         |  .spc   |
|  Base  |       💎       |         |         |                |          |          |                |         |         |   💎    |
|        | -------------- | ------- | ------- | -------------- | -------- | -------- | -------------  | ------- | ------- | ------- |
| Shift  |       🪜       |   🪜    |   🪜    |       🪜       |    🪜    |    🪜    |       🪜       |   🪜    |   🪜    |   🪜    |
| Shift  | LT(Media,KC_R) |    s    |    t    | LT(Shift,KC_H) |    🪜    |    🪜    | LT(Shift,KC_N) |    a    |    i    |   🪜    |
| Shift  |       🪜       |   🪜    |   🪜    |       🪜       |    🪜    |    🪜    |       🪜       |   🪜    |   🪜    |   🪜    |
|        | -------------- | ------- | ------- | -------------- | -------- | -------- | -------------  | ------- | ------- | ------- |
| NumNav |       8        |    7    |    6    |       5        |    ❌     |   Prt    |      ⬅️⬅️      |  ⬆️⬆️   |  ⬇️⬇️   |  ➡️➡️   |
| NumNav |       4        |    3    |    2    |       1        |    %     |   Esc    |       ⬅️       |   ⬆️    |   ⬇️    |   ➡️    |
| NumNav |       ^        |    @    |    #    |       9        |    ❌     |    ❌     |      ↩️️       |   Ins   |   Del   |   Win   |
|        | -------------- | ------- | ------- | -------------- | -------- | -------- | -------------  | ------- | ------- | ------- |
| ComboM |                |         |         |                |          |          |                |         |         |         |
| ComboM |                |         |         |                |          |          |                |         |         |         |
| ComboM |                |         |         |                |          |          |                |         |         |         |
|        | -------------- | ------- | ------- | -------------- | -------- | -------- | -------------  | ------- | ------- | ------- |
| FnSym  |       f8       |   f7    |   f6    |       f5       |    ❌     |    ä     |       !        |    (    |    )    |    *    |
| FnSym  |       f4       |   f3    |   f2    |       f1       |    ß     |    ö     |       ;        |    [    |    ]    |    \    |    
| FnSym  |      f12       |   f11   |   f10   |       f9       |    ❌     |    ü     |       =        |    ~    |    $    |    &    |
|        | -------------- | ------- | ------- | -------------- | -------- | -------- | -------------  | ------- | ------- | ------- |
| Media  |                |         |         |                |          |          |                |         |         |         |
| Media  |                |         |         |                |          |          |                |         |         |         |
| Media  |                |         |         |                |          |          |                |         |         |         |
|        | -------------- | ------- | ------- | -------------- | -------- | -------- | -------------  | ------- | ------- | ------- |

| Thumb  | Left Inner | Left Outer |    Right Outer     | Right Inner |
|:------:|:----------:|:----------:|:------------------:|:-----------:|
|  Base  |    Spc     |   MO(1)    | LT(NumNav,KC_BSPC) |      e      |
|  Base  | MO(ComboM) |     💎     |         💎         |  MO(FnSym)  |
| Shift  |     🪜     |     🪜     |        Bspc        |     🪜      |
| NumNav |     0      |    Tab     |         🪜         |     🪜      |
| ComboM |     🪜     |     🪜     |                    |             |
| FnSym  |    Spc     |            |         🪜         |     🪜      |
| Media  |    Spc     |            |                    |             |

| Symbol  | Command     |
|---------|-------------|
| ⬅️      | KC_LEFT     |
| ⬅️⬅️    | KC_HOME     |
| ⬇️      | KC_DOWN     |
| ⬇️⬇️    | KC_PGDN     |
| ⬆️      | KC_UP       |
| ⬆️⬆️    | KC_PGUP     |
| ➡️      | KC_RIGHT    |
| ➡️➡️    | KC_END      |
| Ins     | KC_INS      |
| Del     | KC_DEL      |
| Spc     | KC_SPC      |
| Esc     | KC_ESC      |
| ↩️️     | KC_ENT      |
| Bspc    | KC_BSPC     |
| Win     | KC_LGUI     |
| Tab     | KC_TAB      |
| Prt     | KC_PSCR     |
| 🖱️⬅️   | KC_MS_L     |
| 🖱️⬇️   | KC_MS_D     |
| 🖱️⬆️   | KC_MS_U     |
| 🖱️➡️   | KC_MS_R     |
| 🖲️️⬅️  | KC_WH_L     |
| 🖲️️⬇️  | KC_WH_D     |
| 🖲️️⬆️  | KC_WH_U     |
| 🖲️️➡️  | KC_WH_R     |
| 🖱️1    | KC_BTN1     |
| 🖱️2    | KC_BTN2     |
| 🖱️3    | KC_BTN3     |
| redo    | RCS(KC_Z)   |
| undo    | LCTL(KC_Z)  |
| copy    | LCTL(KC_C)  |
| paste   | LCTL(KC_V)  |
| S-paste | RCS(KC_V)   |
| cut     | LCTL(KC_X)  |
| A-F7    | LALT(KC_F7) |
| ä       | RALT(KC_Q)  |
| ö       | RALT(KC_P)  |
| ü       | RALT(KC_Y)  |
| ß       | RALT(KC_S)  |
| 🪜      | KC_TRNS     |
| .spc    | KC_F24      |
