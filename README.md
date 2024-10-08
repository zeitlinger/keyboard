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
- $Mouse = layer is active while key is held (double tap to lock layer)
- #Mouse = toggle layer
- @Num = layer is active for the next keypress
- Sym/Nav = layer is active for the next keypress: 
  If the activation key is still down when the next key is pressed, the Nav layer is used, otherwise the Sym layer is used
- C-w = Ctrl-w (same for Alt and Shift)
- "that" = combo that produces "that"
- The symbol table at the bottom shows the meaning of the symbols used in the layout.

> **Note**: The layout is generated from this file directly.

| Repeat | Alt Repeat  | Repeat Key |
|:------:|:-----------:|:----------:|
|   a    |      u      |            |
|   b    |      l      |  "ecause"  |
|   c    |      k      |            |
|   d    |    "oes"    |     v      |
|   e    |      o      |            |
|   f    |      f      |    "or"    |
|   g    |      n      |     l      |
|   h    |    "ey"     |   "ave"    |
|   i    |      z      |            |
|   j    |    "ust"    |            |
|   k    |      n      |   "now"    |
|   l    |      l      |     m      |
|   m    |      b      |   "ent"    |
|   n    |      g      |     k      |
|   o    |      e      |            |
|   p    |      l      |     s      |
|   q    |    "ua"     |            |
|   r    |      k      |            |
|   s    |      p      |   "ion"    |
|   t    |    "ion"    |   "ing"    |
|   u    |      a      |            |
|   v    |    "er"     |    "en"    |
|   w    |      n      |     s      |
|   x    |      p      |     c      |
|   y    |             |     i      |
|   z    | "eitlinger" |     i      |
|  spc   |    "the"    |   "and"    |
|  tab   |    "the"    |   "and"    |
|  ↩️️   |    "the"    |   "and"    |
|   ~    |      /      |            |
|   ,    |   " but"    |   " and"   |
|   .    |      /      |    "./"    |
|   -    |      >      |            |
|   =    |      >      |            |

| Layer | L. Pin. | L. Ring | L. Mid. | L. Ind. | R. Ind. | R. Mid. | R. Ring | R. Pin. |
|:-----:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|
| Base  |   esc   |    p    |    m    |   win   |   f16   | repeat  | altRep  |  reset  |
| Base  |    s    |    c    |    n    |    t    |    a    |    e    |    i    |    h    |
| Base  | *Right  |    f    |    l    |    d    |    u    |    o    |    y    |  *Left  |
| Base  |         |         |  *Nav   |    r    |   spc   |   *Fn   |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Base  |         |         |         |    v    |  "ing"  |         |         |         |
| Base  |         |         |         |   💎    |   💎    |         |         |         |
| Base  |         |         |         |    k    |  "ion"  |         |         |         |
| Base  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Base  |         |         |    w    |         |         |    '    |         |         |
| Base  |         |         |   💎    |         |         |   💎    |         |         |
| Base  |         |         |    g    |         |         |    ,    |         |         |
| Base  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Base  |         |    x    |         |         |         |         |    z    |         |
| Base  |         |   💎    |         |         |         |         |   💎    |         |
| Base  |         |    b    |         |         |         |         |    .    |         |
| Base  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Base  |         |         |         |         |         |         |         |         |
| Base  |   💎    |         |         |         |         |         |         |   💎    |
| Base  |    q    |         |         |         |         |         |         |    j    |
| Base  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Right |         |         |         |         |         |   n't   |  A-➡️   |         |
| Right |         |  *Case  |    9    |    0    |         |         |         |         |
| Right |   🛑    |   🛑    |   🛑    |   🛑    |         |         |         |    ?    |
| Right |         |         |    1    |    2    |   spc   |    3    |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Right |         |         |         |         |         |         |         |         |
| Right |         |         |         |         |         |         |   💎    |         |
| Right |         |         |         |         |         |         |  .spc   |         |
| Right |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| RMods |         |         |         |         |         |         |         |         |
| RMods |         |         |         |         |         |         |         |         |
| RMods |   🛑    |   🛑    |   🛑    |   🛑    |         |         |         |         |
| RMods |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Left  |         |         |         |         |         |         |         |         |
| Left  |         |         |         |         |    5    |    6    | *Media  |         |
| Left  |    :    |         |         |         |   🛑    |   🛑    |   🛑    |   🛑    |
| Left  |         |         |    4    |         |    7    |    8    |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| LMods |         |         |         |         |         |         |         |         |
| LMods |         |         |         |         |         |         |         |         |
| LMods |         |         |         |         |   🛑    |   🛑    |   🛑    |   🛑    |
| LMods |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Fn   |         |   f10   |   f9    |         |         |    (    |    )    |         |
|  Fn   |   f4    |   f3    |   f2    |   f1    |    -    |    [    |    ]    |  ;+Num  |
|  Fn   |   f8    |   f7    |   f6    |   f5    |    `    |    "    |    =    |    /    |
|  Fn   |         |         |  *Sym   |   f12   |   🛑    |   🛑    |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Fn   |         |         |         |         |         |         |         |         |
|  Fn   |         |         |   💎    |         |         |         |         |         |
|  Fn   |         |         |   f11   |         |         |         |         |         |
|  Fn   |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Sym  |         |  pipe   |    *    |         |         |    <    |    >    |         |
|  Sym  |    $    |    #    |    @    |    !    |    _    |    {    |    }    |    :    |
|  Sym  |         |    &    |    ^    |    %    |    ~    |    \    |    +    |    ?    |
|  Sym  |         |         |   🛑    |   🛑    |   🛑    |   🛑    |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Nav  |   spc   |   C-x   |   C-v   |  CS-z   |   🔇    |   esc   |   ins   |         |
|  Nav  | cp+Nav2 |   🛑    |   🛑    |   🛑    |   ⬅️    |   ⬆️    |   ⬇️    |   ➡️    |
|  Nav  |   C-z   |   C-w   | tab ➡️  | win ➡️  |   ↩️️   |  bspc   |   del   |   spc   |
|  Nav  |         |         |   --    |   🛑    |   tab   |  *Sym   |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Nav  |         |         |         |  CS-v   |    ä    |         |         |         |
|  Nav  |         |         |         |   💎    |   💎    |         |         |         |
|  Nav  |         |         |         |   C-r   |    ü    |         |         |         |
|  Nav  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Nav  |         |         |   C-f   |         |         |    ö    |         |         |
|  Nav  |         |         |   💎    |         |         |   💎    |         |         |
|  Nav  |         |         |   C-d   |         |         |    ß    |         |         |
|  Nav  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Nav  |         |   C-a   |         |         |         |         |         |         |
|  Nav  |         |   💎    |         |         |         |         |         |         |
|  Nav  |         |   C-y   |         |         |         |         |         |         |
|  Nav  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Nav  |         |         |         |         |         |         |         |         |
|  Nav  |   💎    |   C-k   |         |         |         |         |         |         |
|  Nav  |   C-n   |         |         |         |         |         |         |         |
|  Nav  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Nav  |         |  CS-f   |   💎    |         |         |         |         |         |
|  Nav  |         |         |         |         |         |         |         |         |
|  Nav  |         |         |         |         |         |         |         |         |
|  Nav  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Nav  |         |         |         |         |         |         |         |         |
|  Nav  |         |         |         |         |         |         |         |         |
|  Nav  |  A-f7   |   💎    |         |         |         |         |         |         |
|  Nav  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Nav2  |         |         |         |         |         |   C-[   |   C-]   |         |
| Nav2  |   🛑    |   🛑    |   🛑    |   🛑    |  ⬅️⬅️   |  ⬆️⬆️   |  ⬇️⬇️   |  ➡️➡️   |
| Nav2  |         |         |         |         |         |         |         |         |
| Nav2  |         |         |         |         |   C-/   |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Num  |         |    ,    |    9    |         |         |         |         |         |
|  Num  |    4    |    3    |    2    |    1    |         |         |         |         |
|  Num  |    8    |    7    |    6    |    5    |         |         |         |         |
|  Num  |         |         |    .    |    0    |   🛑    |   🛑    |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Case  |         |         |         |         |         | PasCase | SN_CASE |         |
| Case  |         |         |         |         | sl/case | camCase | sn_case |  CAPW   |
| Case  |         |         |         |         | do.case |  CAPSL  | kb-case |         |
| Case  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Media |         |   🔅    |   🔆    |         |         |         |         |         |
| Media |   prt   |   🔈    |   🔊    |   🔇    |         |   🛑    |         |         |
| Media |   ver   |   ⏮️    |   ⏭️    |   ⏯️    |         |         |         |   🛑    |
| Media |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |

## Options

The order of the options is also the order of the layers in the layer stack.

| LayerOptions | Modifiers Left  |  Modifiers Right  | Fallback Left | Fallback Right | Flags       | Combo Timeout |
|:------------:|:---------------:|:-----------------:|:-------------:|:--------------:|-------------|:-------------:|
|     Base     |                 |                   |               |                |             |      200      |
|     Left     |                 |  BottomRow+LMods  |     Base      |                | Shifted     |      200      |
|    Right     | BottomRow+RMods |                   |               |      Base      | Shifted     |      200      |
|    LMods     |                 |  BottomRow+LMods  |     Base      |                |             |               |
|    RMods     | BottomRow+RMods |                   |               |      Base      |             |               |
|     Nav      |     HomeRow     |                   |               |                | DirectCombo |      200      |
|     Nav2     |     HomeRow     |                   |               |                |             |               |
|      Fn      |     HomeRow     |      HomeRow      |               |                | DirectCombo |      200      |
|     Num      |                 |      HomeRow      |               |                |             |               |
|     Case     |                 |                   |               |                |             |               |
|    Media     |                 |                   |               |                |             |               |
|     Sym      |                 |                   |               |                | DirectCombo |      200      |

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
| 🔇      | KC_MUTE                               |
| ⏯️      | KC_MPLY                               |
| ⏮️      | KC_MPRV                               |
| ⏭️      | KC_MNXT                               |
| 🔊      | KC_VOLU                               |
| 🔈      | KC_VOLD                               |
| 🔆      | KC_BRIU                               |
| 🔅      | KC_BRID                               |
| reset   | QK_BOOT                               |
| cp      | C(KC_C)                               |
| ä       | UP(UMLAUT_a, UMLAUT_A)                |
| ö       | UP(UMLAUT_o, UMLAUT_O)                |
| ü       | UP(UMLAUT_u, UMLAUT_U)                |
| ß       | UM(UMLAUT_s)                          |
| repeat  | QK_REPEAT_KEY                         |
| altRep  | QK_ALT_REPEAT_KEY                     |
| tab ➡️  | custom:NEXT_TAB      NoHold           |
| win ➡️  | custom:NEXT_WINDOW   NoHold           |
| .spc    | custom:DOT_SPC                        |
| n't     | custom:N_T                            |
| ver     | custom:PRINT_VERSION                  |
| CAPSL   | KC_CAPS                               |
| CAPW    | custom:CAPS_WORDS                     |
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
