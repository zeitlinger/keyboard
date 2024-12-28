# Hands Down Vibranium Keyboard

### Credits

- [Hands Down Keyboard Layout](https://sites.google.com/alanreiser.com/handsdown)
- [The T-34 keyboard layout](https://www.jonashietala.se/blog/2021/06/03/the-t-34-keyboard-layout/)
- [X-Case](https://github.com/andrewjrae/kyria-keymap#x-case)

### Notes

- The keyboard layout is generated using [generateKeyboard](src/main/kotlin/generateKeyboard.kt) from this file.  => link to [Generator](#generator)
- The generated keyboard can be found in the qmk directory.
- tested with [Ferris Sweep](https://keebmaker.com/products/ferris-sweep) keyboard

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
- FnSym = capitalized words are layer names - if they are a key, the layer is activated as toggled or one shot layer (if the "OneShot" flag is set in the layer flags)
- *Mouse = layer is active while key is held
- C-w = Ctrl-w (same for Alt and Shift)
- f12+Num = tab-mod - f12 on tap and Num on hold
- "that" = combo that produces "that"
- The symbol table at the bottom shows the meaning of the symbols used in the layout.

Currently unused features:

- /+Ctrl = tab-mod - / on tab and CTRL on hold
- $Mouse = layer is active while key is held (double tap to lock layer)
- #Mouse = toggle layer
- @Num = layer is active for the next keypress
- Sym/Nav = layer is active for the next keypress: 
  If the activation key is still down when the next key is pressed, the Nav layer is used, otherwise the Sym layer is used

> **Note**: The layout is generated from this file directly.

| Repeat | Alt Repeat  | Repeat Key |
|:------:|:-----------:|:----------:|
|   a    |      u      |            |
|   b    |      l      |  "ecause"  |
|   c    |      k      |            |
|   d    |      v      |   "oes"    |
|   e    |      o      |            |
|   f    |      f      |    "or"    |
|   g    |      n      |     l      |
|   h    |    "ey"     |     y      |
|   i    |             |            |
|   j    |             |   "ust"    |
|   k    |      n      |   "now"    |
|   l    |      p      |     m      |
|   m    |      b      |   "ent"    |
|   n    |      l      |     k      |
|   o    |      e      |            |
|   p    |      l      |     s      |
|   q    |    "ua"     |            |
|   r    |      k      |            |
|   s    |      p      |     s      |
|   t    |    "ion"    |   "ing"    |
|   u    |      a      |            |
|   v    |    "er"     |    "en"    |
|   w    |      n      |     s      |
|   x    |      p      |     c      |
|   y    |             |     i      |
|   z    | "eitlinger" |     i      |
|  spc   |   "the "    |   "and "   |
|  tab   |   "the "    |   "and "   |
|  ↩️️   |   "the "    |   "and "   |
|   ~    |      /      |            |
|   ,    |   " but "   |  " and "   |
|   .    |      /      |    "./"    |
|   -    |      >      |            |
|   =    |      >      |            |
|   !    |      =      |            |

| Layer | L. Pin. | L. Ring | L. Mid. | L. Ind. | R. Ind. | R. Mid. | R. Ring | R. Pin. |
|:-----:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|
| Base  |   esc   |    p    |    m    | altRep  |  dead2  | repeat  | altRep  |  dead1  |
| Base  |    s    |    c    |    n    |    t    |    a    |    e    |    i    |    h    |
| Base  | *Right  |    f    |    l    |    d    |    u    |    o    |    y    |  *Left  |
| Base  |         |         |  *Nav   |    r    |   spc   | *FnSym  |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Base  |         |         |         |    v    |  "ing"  |         |         |         |
| Base  |         |         |         |   💎    |   💎    |         |         |         |
| Base  |         |         |         |    k    |  "ion"  |         |         |         |
| Base  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Base  |         |         |         |         |         |         |         |         |
| Base  |         |         |         |         |         |         |         |         |
| Base  |         |         |         |   💎    |         |         |         |         |
| Base  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Base  |         |         |    w    |         |         |    '    |         |         |
| Base  |         |         |   💎    |         |         |   💎    |         |         |
| Base  |         |         |    g    |         |         |    ,    |         |         |
| Base  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Base  |         |    x    |         |         |         |         |    q    |         |
| Base  |         |   💎    |         |         |         |         |   💎    |         |
| Base  |         |    b    |         |         |         |         |    .    |         |
| Base  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Base  |  "qu"   |         |         |         |         |         |         |   ng    |
| Base  |   💎    |         |         |         |         |         |         |   💎    |
| Base  |    z    |         |         |         |         |         |         |    j    |
| Base  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Right |         |         |         |         |  dead3  |    "    |  A-➡️   |         |
| Right |         |  CS-f   |  A-f7   |   C-r   |         |         |         |         |
| Right |   🛑    |   🛑    |   🛑    |   🛑    |         |         |         |    ?    |
| Right |         |         |         |         |   spc   |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Right |         |         |         |         |    `    |         |         |         |
| Right |         |         |         |   💎    |   💎    |         |    ß    |         |
| Right |         |         |         |   C-f   |    @    |         |         |         |
| Right |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Right |         |         |         |         |         |   n't   |         |         |
| Right |         |         |   💎    |         |    ä    |   💎    |    ö    |         |
| Right |         |         |   C-e   |         |         |    !    |         |         |
| Right |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Right |         |         |         |         |         |         |         |         |
| Right |         |   💎    |         |         |         |         |   💎    |    ü    |
| Right |         |  CS-r   |         |         |         |         |  .spc   |         |
| Right |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Right |         |         |         |         |         |         |         |         |
| Right |         |         |         |         |         |         |         |         |
| Right |         |         |         |         |    Ä    |   💎    |    Ö    |         |
| Right |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Right |         |         |         |         |         |         |         |         |
| Right |         |         |         |         |         |         |         |         |
| Right |         |         |         |         |         |         |   💎    |    Ü    |         
| Right |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| RMods |         |         |         |         |         |         |         |         |
| RMods |         |         |         |         |         |         |         |         |
| RMods |   🛑    |   🛑    |   🛑    |   🛑    |         |         |         |         |
| RMods |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Left  |         |         |         |         |         |         |         |         |
| Left  |         |         |         |         |         |         | *Media  |         |
| Left  |    :    |         |         |         |   🛑    |   🛑    |   🛑    |   🛑    |
| Left  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Left  |         | sl/case |   💎    |         |         |         |         |         |
| Left  |         |         |         |         |         |         |         |         |
| Left  |         |         |         |         |         |         |         |         |
| Left  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Left  |         |         |         |         |         |         |         |         |
| Left  |         | PasCase |         |   💎    |         |         |         |         |
| Left  |         |         |         |         |         |         |         |         |
| Left  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Left  |         |         |         |         |         |         |         |         |
| Left  |         | SN_CASE |   💎    |  CapW   |         |         |         |         |
| Left  |         |         |         |         |         |         |         |         |
| Left  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Left  |  "Qu"   |         |         |         |         |         |         |         |
| Left  |   💎    | kb-case |         |         |         |         |         |         |
| Left  |         |         |         |         |         |         |         |         |
| Left  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Left  |         |         |         |         |         |         |         |         |
| Left  |         |         |         |         |         |         |         |         |
| Left  |         | camCase |         |   💎    |         |         |         |         |
| Left  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Left  |         |         |         |         |         |         |         |         |
| Left  |         |         |         |         |         |         |         |         |
| Left  |         | sn_case |   💎    |  CapsL  |         |         |         |         |
| Left  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Left  |         |         |         |         |         |         |         |         |
| Left  |         |         |         |         |         |         |         |         |
| Left  |   💎    | do.case |         |         |         |         |         |         |
| Left  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| LMods |         |         |         |         |         |         |         |         |
| LMods |         |         |         |         |         |         |         |         |
| LMods |         |         |         |         |   🛑    |   🛑    |   🛑    |   🛑    |
| LMods |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| FnSym |  dead2  |   f10   |   f9    |   win   |  dead3  |    (    |    )    |  dead1  |
| FnSym |   f4    |   f3    |   f2    |   f1    |    -    |    {    |    }    |  CapW   |
| FnSym |   f8    |   f7    |   f6    |   f5    |    _    |    =    |    +    |    /    |
| FnSym |         |         | f11+Num |   f12   |   🛑    |   🛑    |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| FnSym |         |         |         |    ^    |    !    |         |         |         |
| FnSym |         |         |         |   💎    |   💎    |         |         |         |
| FnSym |         |         |         |    %    |    ~    |         |         |         |
| FnSym |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| FnSym |         |         |    *    |         |         |    <    |         |         |
| FnSym |         |         |   💎    |         |         |   💎    |         |         |
| FnSym |         |         |    #    |         |         |    [    |         |         |
| FnSym |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| FnSym |         |  pipe   |         |         |         |         |    >    |         |
| FnSym |         |   💎    |         |         |         |         |   💎    |         |
| FnSym |         |    &    |         |         |         |         |    ]    |         |
| FnSym |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| FnSym |    @    |         |         |         |         |         |         |    ;    |
| FnSym |   💎    |         |         |         |         |         |         |   💎    |
| FnSym |    $    |         |         |         |         |         |         |    \    |
| FnSym |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Nav  |   spc   |   C-x   |   C-v   |  CS-z   |         |   esc   |   ins   |         |
|  Nav  |  copy   |   🛑    |   🛑    |   🛑    |   ⬅️    |   ⬇️    |   ⬆️    |   ➡️    |
|  Nav  |   C-z   |   C-w   | tab ➡️  | win ➡️  |   ↩️️   |  bspc   |   del   |   spc   |
|  Nav  |         |         |   🛑    |   🛑    |   tab   | st+Num  |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Nav  |         |         |         |  CS-v   |         |         |         |         |
|  Nav  |         |         |         |   💎    |   💎    |         |         |         |
|  Nav  |         |         |         |         |  ⬅️⬅️   |         |         |         |
|  Nav  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Nav  |         |         |         |         |         |   C-[   |         |         |
|  Nav  |         |         |   💎    |         |   A-[   |   💎    |   A-]   |         |
|  Nav  |         |         |   C-d   |         |         |  ⬇️⬇️   |         |         |
|  Nav  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Nav  |         |   C-a   |         |         |         |         |   C-]   |         |
|  Nav  |         |   💎    |         |         |         |         |   💎    |         |
|  Nav  |         |   C-k   |         |         |         |         |  ⬆️⬆️   |         |
|  Nav  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Nav  |         |         |         |         |         |         |         |         |
|  Nav  |   💎    |         |         |         |         |         |         |   💎    |
|  Nav  |   C-n   |         |         |         |         |         |         |  ➡️➡️   |
|  Nav  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Nav  |         |         |         |         |         |         |         |         |
|  Nav  |         |         |         |         |         |         |         |         |
|  Nav  |         |         |         |         |         |   C-/   |   💎    |         |
|  Nav  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Num  |         |    %    |    :    |         |         |    *    |    -    |         |
|  Num  |    4    |    3    |    2    |    1    |    0    |    9    |    .    |    ,    |
|  Num  |    8    |    7    |    6    |    5    |    _    |    =    |    +    |    /    |
|  Num  |         |         |   🛑    |   🛑    |   🛑    |   🛑    |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Media |         |   🔅    |   🔆    |         |         |         |         |         |
| Media |   prt   |   🔈    |   🔊    |   🔇    |         |   🛑    |         |         |
| Media |   ver   |   ⏮️    |   ⏭️    |   ⏯️    |         |         |         |   🛑    |
| Media |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |

## Options

The order of the options is also the order of the layers in the layer stack.

| LayerOptions | Modifiers Left  | Modifiers Right | Fallback Left | Fallback Right | Flags            | Combo Timeout |
|:------------:|:---------------:|:---------------:|:-------------:|:--------------:|------------------|:-------------:|
|     Base     |                 |                 |               |                |                  |      200      |
|     Left     |                 | BottomRow+LMods |     Base      |                | Shifted          |      500      |
|    Right     | BottomRow+RMods |                 |               |      Base      | Shifted          |      500      |
|    LMods     |                 | BottomRow+LMods |     Base      |                |                  |               |
|    RMods     | BottomRow+RMods |                 |               |      Base      |                  |               |
|     Nav      |     HomeRow     |                 |               |                | DirectComboLeft  |      500      |
|    FnSym     |     HomeRow     |     HomeRow     |               |                | DirectComboRight |      500      |
|     Num      |     HomeRow     |     HomeRow     |               |                |                  |               |
|    Media     |                 |                 |               |                |                  |               |

## Symbols

| Symbol  | Command                     |
|---------|-----------------------------|
| ⬅️      | KC_LEFT                     |
| ⬅️⬅️    | KC_HOME                     |
| ⬇️      | KC_DOWN                     |
| ⬇️⬇️    | KC_PGDN                     |
| ⬆️      | KC_UP                       |
| ⬆️⬆️    | KC_PGUP                     |
| ➡️      | KC_RIGHT                    |
| ➡️➡️    | KC_END                      |
| ins     | KC_INS                      |
| del     | KC_DEL                      |
| spc     | KC_SPC                      |
| esc     | KC_ESC                      |
| ↩️️     | KC_ENT                      |
| bspc    | KC_BSPC                     |
| win     | KC_LGUI                     |
| tab     | KC_TAB                      |
| st      | S(KC_TAB)                   |
| prt     | KC_PSCR                     |
| pipe    | KC_PIPE                     |
| 🔇      | KC_MUTE                     |
| ⏯️      | KC_MPLY                     |
| ⏮️      | KC_MPRV                     |
| ⏭️      | KC_MNXT                     |
| 🔊      | KC_VOLU                     |
| 🔈      | KC_VOLD                     |
| 🔆      | KC_BRIU                     |
| 🔅      | KC_BRID                     |
| copy    | C(KC_C)                     |
| ä       | UP(UMLAUT_a, UMLAUT_A)      |
| ö       | UP(UMLAUT_o, UMLAUT_O)      |
| ü       | UP(UMLAUT_u, UMLAUT_U)      |
| Ä       | UM(UMLAUT_A)                |
| Ö       | UM(UMLAUT_O)                |
| Ü       | UM(UMLAUT_U)                |
| ß       | UM(UMLAUT_s)                |
| repeat  | QK_REPEAT_KEY               |
| altRep  | QK_ALT_REPEAT_KEY           |
| tab ➡️  | custom:NEXT_TAB      NoHold |
| win ➡️  | custom:NEXT_WINDOW   NoHold |
| .spc    | custom:DOT_SPC              |
| n't     | custom:N_T                  |
| ver     | custom:PRINT_VERSION        |
| CapsL   | KC_CAPS                     |
| CapW    | custom:CAPS_WORDS           |
| sn_case | custom:SNAKE_CASE           |
| SN_CASE | custom:SCREAMING_SNAKE_CASE |
| camCase | custom:CAMEL_CASE           |
| PasCase | custom:PASCAL_CASE          |
| sl/case | custom:SLASH_CASE           |
| do.case | custom:DOT_CASE             |
| kb-case | custom:KEBAP_CASE           |
| dead1   | custom:DEAD1                |
| dead2   | custom:DEAD2                |
| dead3   | custom:DEAD3                |

## Generator

- should be usable with any keyboard layout

qmk flash -kb ferris/sweep -km zeitlinger -bl avrdude-split-left
