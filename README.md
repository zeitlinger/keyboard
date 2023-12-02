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

Base Layer Modifiers

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
            
| Base Layer Thumb Mod Combos | Fingers             | Timeout Delta |
|-----------------------------|---------------------|:-------------:|
| Timeout                     | 35                  |               |
| Alt                         | Ring                |               |
| Shift                       | Middle              |               |
| Ctrl                        | Index               |               |
| Ctrl-Shift                  | Middle, Index       |               |
| Alt-Shift                   | Ring, Middle        |               |
| Ctrl-Alt                    | Ring, Index         |               |
| Ctrl-Alt-Shift              | Ring, Middle, Index |               |

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
- Fn = capitalized words are layer names
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
|  Base  | b+SymR  |    c    |    g    |    d    |    p    |    '    | ,+SymL  |  .+Fn   |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |         |         |   💎    |    z    |    ß    |    ö    |    ü    |         |
|  Base  |         |         |         |         |    -    |    ä    |    _    |    &    |
|  Base  |         |         |         |         |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |         |         |         |         |         |         |         |         |
|  Base  |   💎    |   tab   |         |         |         |         |         |         |
|  Base  |         |         |         |         |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |         |   💎    |    v    |   f4    |         |   💎    | ↩️️ 20  |         |
|  Base  |         |         |         |         |         |         |         |         |
|  Base  |         |         |         |         |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |   💎    |    q    |         |         |         |         |         |         |
|  Base  |         |         |         |         |         |         |         |         |
|  Base  |         |         |         |         |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |         |         |         |         |         |         |         |         |          
|  Base  |         |         |         |         |         |         |         |         |
|  Base  |         |         |         |         |    !    |   💎    |   💎    |    ?    |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |         |         |         |         |         |         |         |         |
|  Base  |         |         |         |         |         |         |         |         |
|  Base  |         |         |   💎    |  k 80   |  aRep   |   💎    |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |         |         |         |         |         |         |         |         |
|  Base  |         |         |         |         |         |         |         |         |
|  Base  |         |   💎    |    j    |    x    |         |   rep   |   💎    |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Base  |         |         |         |         |         |         |         |         |
|  Base  |         |         |  A-f7   | S-paste |         |         |         |         |
|  Base  |   💎    | cut 100 |  copy   |  paste  |         |         |  capsW  |   💎    |
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
|  Mods  |         |         |         |         |         |         |         |         |
|  Mods  |         |         |         |         |         |         |         |         |
|  Mods  |         |         |         |         |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Shift  |         |         |         |         |         |         |         |         |
| Shift  | r+Media |         |         |         |         |         |         |         |
| Shift  |         |         |         |         |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| NumNav |         |    6    |    5    |         |   esc   |  ⬆️⬆️   |  ⬇️⬇️   |         |
| NumNav |    4    |    3    |    2    |    1    |   ⬅️    |   ⬆️    |   ⬇️    |   ➡️    |
| NumNav |         |    9    |    8    |    7    |  ⬅️⬅️   |  bspc   |   del   |  ➡️➡️   |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|   Fn   |         |   f6    |   f5    |         |         |         |         |         |
|   Fn   |   f4    |   f3    |   f2    |   f1    |         |         |         |         |    
|   Fn   |   f10   |   f9    |   f8    |   f7    |         |         |         |    ❌    |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Mouse  |         |         |         |         |  🖱️3   |  🖱️1   |  🖱️2   |         |
| Mouse  |         |         |  🖱️2   |  🖱️1   |  🖱️⬅️  |  🖱️⬆️  |  🖱️⬇️  |  🖱️➡️  |    
| Mouse  |         |         |         |         | 🖲️️⬅️  | 🖲️️⬆️  | 🖲️️⬇️  | 🖲️️➡️  |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Sym   |         |    ~    |    +    |    %    |    /    |    {    |    }    |         |
|  Sym   |    $    |    (    |    )    |    :    |    ;    |    [    |    ]    |    \    |    
|  Sym   |    ^    |    #    |    @    |    *    |    `    |    "    |    =    |  pipe   |        
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  SymL  |         |         |         |         |         |         |         |         |
|  SymL  |         |         |         |         |         |         |         |         |
|  SymL  |         |         |         |         |         |         |    ❌    |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  SymR  |         |         |         |         |         |         |         |         |
|  SymR  |         |  A-f4   |   win   |   C-w   |         |         |         |         |
|  SymR  |    ❌    |   alt   | s/undo  | c/redo  |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Media  |         |         |   prt   |         |         |   🔅    |   🔆    |         |
| Media  |    ❌    |   🔈    |   🔊    |   🔇    |   ⏯️    |   ⏮️    |   ⏭️    |         |
| Media  |         |         |         |         |         |         |         |         |
|        | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |

| Thumb  | Left Inner |         Left Outer         | Right Outer |        Right Inner         |
|:------:|:----------:|:--------------------------:|:-----------:|:--------------------------:|
|  Base  |   Shift    | HomeRowThumbCombo:Mods spc |      e      | ComboLayer:Sym bspc+NumNav |
|  Base  |     💎     |                            |             |           Mouse            |
|  Mods  |            |                            |             |            tab             |
| Shift  |     ❌      |             ❌              |             |            spc             |
| NumNav |    ins     |             0              |      ❌      |             ❌              | 
|   Fn   |            |            f11             |     f12     |                            |
|  SymL  |            |                            |             |                            |
|  SymR  |    undo    |            tab             |     spc     |            redo            |

| LayerOptions | Modifiers Left |  Modifiers Right   | Fallback Left | Fallback Right | Flags  |
|:------------:|:--------------:|:------------------:|:-------------:|:--------------:|--------|
|     Base     |                |                    |               |                |        |
|     Mods     |    HomeRow     |      HomeRow       |     Base      |      Base      |        |  
|    Shift     |    HomeRow     |      HomeRow       |     Base      |      Base      |        |  
|    NumNav    |    HomeRow     |      HomeRow       |               |                |        | 
|      Fn      |                | HomeRow, BottomRow |               |                |        |  
|    Mouse     |    HomeRow     |                    |               |                |        |  
|     Sym      |                |                    |               |                | Hidden | 
|     SymL     |                |                    |      Sym      |                |        | 
|     SymR     |   BottomRow    |                    |               |      Sym       |        | 
|    Media     |                |                    |               |                |        |

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
| sTab    | LSFT(KC_TAB)        |
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
| undo    | LCTL(KC_Z)          |
| c/redo  | LCTL(KC_AGAIN)      |
| s/undo  | LSFT(KC_UNDO)       |
| copy    | LCTL(KC_C)          |
| paste   | LCTL(KC_V)          |
| S-paste | RCS(KC_V)           |
| cut     | LCTL(KC_X)          |
| ä       | RALT(KC_Q)          |
| ö       | RALT(KC_P)          |                                         
| ü       | RALT(KC_Y)          |
| ß       | RALT(KC_S)          |
| '       | RALT(KC_QUOTE)      |
| "       | RALT(KC_DQUO)       |
| `       | RALT(KC_GRV)        |
| ~       | RALT(KC_TILD)       |
| ^       | RALT(KC_CIRC)       |
| 🪜      | KC_TRNS             |
| rep     | QK_REPEAT_KEY       |
| aRep    | QK_ALT_REPEAT_KEY   |
| capsW   | QK_CAPS_WORD_TOGGLE |
| Mouse   | custom:MOUSE        |
| .spc    | custom:DOT_SPC      |
                                                                
