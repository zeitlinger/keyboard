# Hands Down Vibranium Keyboard

### Credits

- [Hands Down Keyboard Layout](https://sites.google.com/alanreiser.com/handsdown)
- [The T-34 keyboard layout](https://www.jonashietala.se/blog/2021/06/03/the-t-34-keyboard-layout/)
- [X-Case](https://github.com/andrewjrae/kyria-keymap#x-case)

### Features

- **[Chord Mode](CHORD_MODE.md)** - Type 220+ common words with just two letters! See the [complete documentation](CHORD_MODE.md) for details.
- **[Design Philosophy](DESIGN_PHILOSOPHY.md)** - Learn about the hardware, ergonomics, and design principles behind this layout
- **Home Row Mods** - Modifiers on home row for ergonomic access
- **Window/Tab Switching** - Fast application and tab switching
- **X-Case** - Multiple case conversion modes (camelCase, snake_case, etc.)

### Notes

- The keyboard layout is generated using [generateKeyboard](src/main/kotlin/generateKeyboard.kt)
  from this file. => link to [Generator](#generator)
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

- win ➡️ and tab ➡️ are used to Short windows and tabs.
- Once you press any of those keys, you're in switcher mode, where all other keys are replaced by
  shift-tab.
- Switcher mode is exited when you go back to the base layer.

## Definition

How to read this layout:

- 💎 = combo key (e.g. middle and index finger in top row pressed together produce "b")
- 🛑 = key can't be used because the layer was activated with that key or because it's reserved for a
  modifier
- empty = use key from base layer
- FnSym = capitalized words are layer names - if they are a key, the layer is activated as toggled
  or one shot layer (if the "OneShot" flag is set in the layer flags)
- *Mouse = layer is active while key is held
- C-w = Ctrl-w (same for Alt and Shift)
- f12+Num = tab-mod - f12 on tap and Num on hold
- "that" = combo that produces "that"
- [ { = { is the shifted key of [, so it's used when Shift is held (only for information)
- The symbol table at the bottom shows the meaning of the symbols used in the layout.

Currently unused features:

- /+Ctrl = tab-mod - / on tab and CTRL on hold
- $Mouse = layer is active while key is held (double tap to lock layer)
- #Mouse = toggle layer
- @Num = layer is active for the next keypress
- Sym/Nav = layer is active for the next keypress:
  If the activation key is still down when the next key is pressed, the Nav layer is used, otherwise
  the Sym layer is used

> **Note**: The layout is generated from this file directly.
 
## Magic Keys

Rows = preceding key. Columns = the nine physical magic keys, row-wise from top-left:
- magic_a: old `'` position (R.Mid. top row)
- magic_b: old magicC position (R.Ring top row) — legacy magicC content
- magic_c: old `qu` position (L.Pin. top combo)
- magic_d: old magicB position (R.Mid. upper combo) — legacy magicB content
- magic_e: old magicA position (R.Ring upper combo) — legacy magicA content
- magic_f: old `q` position (R.Pin. top combo)
- magic_g: old chord-key position (R.Ind. thumb combo)
- magic_h: old `,` position (R.Mid. lower combo)
- magic_i: old `.` position (R.Ring lower combo)

Cell = what to emit.
- Single-char cells append (e.g. `a` + `e` yields `ae`).
- Quoted strings:
  - Preceding key is a letter and cell starts with it → generator strips the prefix. `b` + `"because"` emits `ecause`, yielding `because`.
  - Preceding key is a letter and cell does *not* start with it → generator backspaces the preceding letter then emits the cell. `z` + `"another"` yields `another`.
  - Preceding key is not a letter (spc, punctuation) → cell appends as-is. `spc` + `"the "` yields ` the `.

Special row `magic` = suffix. Cell fires when the preceding keypress was any other magic (e.g. `magic_a` + `magic_b` with `"ly"` in the `magic` row / `magic_b` column emits ` ly` after magic_a's word).

| Magic | magic_a | magic_b | magic_c | magic_d | magic_e | magic_f | magic_g | magic_h | magic_i |
|:-----:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|
| magic |         |         |         |         |         |         |         |         |         |
|  a   |         |         |    e    |         |         |         |         |         |         |
|  b   |         |         |         |"because"|    d    |         |         |         |         |
|  c   |         |         |         |    p    |    d    |         |         |   !     |    ?    |
|  d   |         |    h    |         |"doesn't"|    f    |         |         |         |         |
|  e   |         |         |    h    |         |         |         |         |         |         |
|  f   |         |    f    |         |         |         |         |         |         |         |
|  g   |         |    f    |         |    k    |    d    |         |         |         |         |
|  h   |         |         |         |         |    y    |         |         |         |         |
|  i   |         |         |         | "I've"  |    '    |         |         |         |         |
|  j   |         |         |         | "just"  |         |         |         |         |         |
|  k   |         |    h    |         | "know"  |    x    |         |         |         |         |
|  l   |         |    h    |         |    r    |    c    |         |         |         |         |
|  m   |         |    h    |         |  "ment" |    l    |         |         |         |         |
|  n   |    r    |    h    |         |   "qu"  |    x    |         |   q     |   '     |    "    |
|  o   |         |         |    h    |         |         |         |         |         |         |
|  p   |         |    m    |         |    n    |    d    |         |         |         |         |
|  r   |         |         |         |    k    |         |         |         |         |         |
|  s   |         |    r    |         | "sion"  |    d    |         |         |         |         |
|  t   |         |         |         | "tion"  |    x    |         |         |   ,     |    .    |
|  u   |         |         |    h    |         |         |         |         |         |         |
|  v   |         |         |         |         |         |         |         |         |         |
|  w   |         |         |         |    s    |    x    |         |         |         |         |
|  x   |         |    w    |         |    r    |    d    |         |         |         |         |
|  y   |         |         |    x    |         |         |         |         |         |         |
| spc  |         | dotSpc  |         | "the "  |         |         |         |         |         |
| tab  |         | "and "  |         | "the "  |         |         |         |         |         |
| ↩️️  |         | "and "  |         | "the "  |         |         |         |         |         |
|  ~   |         |         |         |         |    /    |         |         |         |         |
|  ,   |         | " and " |         | " but " |         |         |         |         |         |
|  .   |         |         |         |  "./"   |    /    |         |         |         |         |
|  -   |         |         |         |         |    >    |         |         |         |         |
|  =   |         |         |         |         |    >    |         |         |         |         |
|  !   |         |         |         |         |    =    |         |         |         |         |

## Adaptives

| Adaptives | Key | Output |
|:---------:|:---:|:------:|
|     a     |  e  |   u    |
|     b     |  d  |   s    |
|     c     |  d  |   k    |
|     d     |  f  |   v    |
|     d     |  h  |   g    |
|     e     |  h  |   o    |
|     g     |  d  |   n    |
|     g     |  f  |   l    |
|     k     |  h  |   n    |
|     l     |  c  |   m    |
|     l     |  h  |   v    |
|     l     |  r  |   p    |
|     m     |  h  |   b    |
|     n     |  h  |   g    |
|     n     |  r  |   k    |
|     n     |  x  |   l    |
|     o     |  h  |   e    |
|     p     |  d  |   l    |
|     p     |  n  |   s    |
|     s     |  d  |   p    |
|     s     |  r  |   k    |
|     t     |  x  |   m    |
|     u     |  h  |   a    |
|     w     |  x  |   n    |
|     x     |  d  |   c    |
|     x     |  w  |   p    |
|     y     |  x  |   i    |

## Layout

| Layer | L. Pin. | L. Ring | L. Mid. | L. Ind. | R. Ind. | R. Mid. | R. Ring | R. Pin. |
|:-----:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|
| Base  |   esc   |    x    |    w    |  dead3  |  dead2  | magic_a | magic_b |  dead1  |
| Base  |    s    |    c    |    n    |    t    |    a    |    e    |    i    |    h    |
| Base  | *Right  |    f    |    l    |    d    |    u    |    o    |    y    |  *Left  |
| Base  |         |         |  *Nav   |    r    |   spc   | *FnSym  |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Base  |         |         |         |    v    |   ing   |         |         |         |
| Base  |         |         |         |   💎    |   💎    |         |         |         |
| Base  |         |         |         |    k    | magic_g |         |         |         |
| Base  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Base  |         |         |    m    |         |         | magic_d |         |         |
| Base  |         |         |   💎    |         |         |   💎    |         |         |
| Base  |         |         |    g    |         |         | magic_h |         |         |
| Base  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Base  |         |    p    |         |         |         |         | magic_e |         |
| Base  |         |   💎    |         |         |         |         |   💎    |         |
| Base  |         |    b    |         |         |         |         | magic_i |         |
| Base  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Base  | magic_c |         |         |         |         |         |         | magic_f |
| Base  |   💎    |         |         |         |         |         |         |   💎    |
| Base  |    z    |         |         |         |         |         |         |    j    |
| Base  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Right |         |         |         |         |  dead3  |    "    |  A-➡️   |         |
| Right |         |         |   C-f   |   C-r   |         |         |         |         |
| Right |   🛑    |   🛑    |   🛑    |   🛑    |         |         |         |    _    |
| Right |         |         |  A-f7   |   C-n   |    [    |    ]    |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Right |         |         |         |         |    `    |         |         |         |
| Right |         |         |         |   💎    |   💎    |         |         |         |
| Right |         |         |         |  CS-r   |    @    |         |         |         |
| Right |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Right |         |         |         |         |         |   n't   |         |         |
| Right |         |         |   💎    |         |         |   💎    |         |         |
| Right |         |         |  CS-f   |         |         |    !    |         |         |
| Right |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Right |         |         |         |         |         |         |    \    |         |
| Right |         |         |         |         |         |         |   💎    |         |
| Right |         |         |         |         |         |         |    ?    |         |
| Right |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| RMods |         |         |         |         |         |         |         |         |
| RMods |         |         |         |         |         |         |         |         |
| RMods |   🛑    |   🛑    |   🛑    |   🛑    |         |         |         |    =    |
| RMods |         |         |         |         |    [    |    ]    |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Left  |         |         |         |         |  dead1  |         |         |         |
| Left  |         |         |         |         |  *CNum  |  *Case  |   *Mm   |         |
| Left  |    :    |         |         |         |   🛑    |   🛑    |   🛑    |   🛑    |
| Left  |         |         |    ;    |         |  *ANum  |  *Num   |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Left  |  "Qu"   |         |         |         |         |         |         |         |
| Left  |   💎    |         |         |         |         |         |         |         |
| Left  |         |         |         |         |         |         |         |         |
| Left  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| LMods |         |         |         |         |         |         |         |         |
| LMods |         |         |         |         |         |         |         |         |
| LMods |    -    |         |         |         |   🛑    |   🛑    |   🛑    |   🛑    |
| LMods |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| FnSym |  dead2  |   f10   |   f9    |  dead2  |  dead3  |    (    |    )    |  dead1  |
| FnSym |   f4    |   f3    |   f2    |   f1    |   🛑    |   🛑    |   🛑    | =+Num2  |
| FnSym |   f8    |   f7    |   f6    |   f5    |    -    |    {    |    }    |  *Num   |
| FnSym |         |         |         |   f12   |   🛑    |   🛑    |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| FnSym |         |         |         |    ➖    |   win   |         |         |         |
| FnSym |         |         |         |   💎    |   💎    |         |         |         |
| FnSym |         |         |         |    ➕    |    ~    |         |         |         |
| FnSym |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| FnSym |         |         |    *    |         |         |    <    |         |         |
| FnSym |         |         |   💎    |         |         |   💎    |         |         |
| FnSym |         |         |   f11   |         |         |    /    |         |         |
| FnSym |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| FnSym |         |  pipe   |         |         |         |         |    >    |         |
| FnSym |         |   💎    |         |         |         |         |   💎    |         |
| FnSym |         |    &    |         |         |         |         |    #    |         |
| FnSym |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| FnSym |   😀    |         |         |         |         |         |         |    ^    |
| FnSym |   💎    |         |         |         |         |         |         |   💎    |
| FnSym |    $    |         |         |         |         |         |         |    %    |
| FnSym |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Nav  |  dead3  |   C-x   |   C-v   |  CS-z   |  dead1  |   esc   |   ins   |  dead2  |
|  Nav  |  copy   |   🛑    |   🛑    |   🛑    |   ⬅️    |   ⬇️    |   ⬆️    |   ➡️    |
|  Nav  |   C-z   |   C-w   | tab ➡️  | win ➡️  |   ↩️️   |  bspc   |   del   |   tab   |
|  Nav  |         |         |   🛑    |   🛑    |   spc   |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Nav  |         |         |         |  CS-v   |    ü    |         |         |         |
|  Nav  |         |         |         |   💎    |   💎    |         |         |         |
|  Nav  |         |         |         |   C-y   |  ⬅️⬅️   |         |         |         |
|  Nav  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Nav  |         |         |   C-a   |         |         |    ö    |         |         |
|  Nav  |         |         |   💎    |         |         |   💎    |         |         |
|  Nav  |         |         |   C-d   |         |         |  ⬇️⬇️   |         |         |
|  Nav  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Nav  |         |  CS-n   |         |         |         |         |    ä    |         |
|  Nav  |         |   💎    |         |         |         |         |   💎    |         |
|  Nav  |         |   C-k   |         |         |         |         |  ⬆️⬆️   |         |
|  Nav  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Nav  |   C-e   |         |         |         |         |         |         |    ß    |
|  Nav  |   💎    |         |         |         |         |         |         |   💎    |
|  Nav  |  CS-c   |         |         |         |         |         |         |  ➡️➡️   |
|  Nav  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Nav  |         |         |         |         |         |         |         |         |
|  Nav  |         |         |         |         |  CA-b   |   💎    |  A-f12  |         |
|  Nav  |         |         |         |         |         |         |         |         |
|  Nav  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Nav  |         |         |         |         |         |         |         |         |
|  Nav  |         |         |         |         |   C-b   |         |   💎    |         |
|  Nav  |         |         |         |         |         |         |         |         |
|  Nav  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Nav  |         |         |         |         |         |         |         |         |
|  Nav  |         |         |         |         |         |         |         |         |
|  Nav  |         |         |         |         |  C-f12  |   💎    |   C-/   |         |
|  Nav  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Nav  |         |         |         |         |         |         |         |         |
|  Nav  |         |         |         |         |         |         |         |         |
|  Nav  |         |         |         |         |   C-p   |         |   💎    |         |
|  Nav  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Num  |  dead1  |    ,    |    9    |  dead2  |         |         |         |         |
|  Num  |    4    |    3    |    2    |    1    |         |         |         |         |
|  Num  |    8    |    7    |    6    |    5    |         |         |         |         |
|  Num  |         |         |    .    |    0    |   🛑    |   🛑    |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Num  |         |         |         |  CS-v   |         |         |         |         |
|  Num  |         |         |         |   💎    |         |         |         |         |
|  Num  |         |         |         |   C-g   |         |         |         |         |
|  Num  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Num  |         |         |  A-f1   |         |         |         |         |         |
|  Num  |         |         |   💎    |         |         |         |         |         |
|  Num  |         |         |  CA-l   |         |         |         |         |         |
|  Num  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Num  |         |  AS-x   |         |         |         |         |         |         |
|  Num  |         |   💎    |         |         |         |         |         |         |
|  Num  |         |  AS-b   |         |         |         |         |         |         |
|  Num  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Num  |         |         |         |         |         |         |         |         |
|  Num  |   💎    |         |         |         |         |         |         |         |
|  Num  |  AS-s   |         |         |         |         |         |         |         |
|  Num  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| ANum  |         |         |         |         |         |         |         |         |
| ANum  |   A-4   |   A-3   |   A-2   |   A-1   |         |         |         |         |
| ANum  |   A-8   |   A-7   |   A-6   |   A-5   |         |         |         |         |
| ANum  |         |         |   A-9   |   A-0   |   🛑    |   🛑    |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| CNum  |         |         |         |         |         |         |         |         |
| CNum  |   C-4   |   C-3   |   C-2   |   C-1   |         |         |         |         |
| CNum  |   C-8   |   C-7   |   C-6   |   C-5   |         |         |         |         |
| CNum  |         |         |   C-9   |   C-0   |   🛑    |   🛑    |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
|  Mm   |         |   🔅    |   🔆    |         |         |         |         |         |
|  Mm   |   prt   |   🔈    |   🔊    |   🔇    |         |         |         |   🛑    |
|  Mm   |   ver   |   ⏮️    |   ⏭️    |   ⏯️    |         |         |         |         |
|  Mm   |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Case  |         |         |         |         |         |         |         |         |
| Case  | sl/case | PasCase |  CapW   | SN_CASE |         |         |         |         |
| Case  | do.case | camCase | kb-case | sn_case |         |         |         |         |
| Case  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |

## Options

The order of the options is also the order of the layers in the layer stack.

| LayerOptions | Modifiers Left  | Modifiers Right | Fallback Left | Fallback Right | Flags            | Combo Timeout |
|:------------:|:---------------:|:---------------:|:-------------:|:--------------:|------------------|:-------------:|
|     Base     |                 |                 |               |                |                  |      200      |
|     Left     |                 | BottomRow+LMods |     Base      |                | Shifted          |      200      |
|    Right     | BottomRow+RMods |                 |               |      Base      | Shifted          |      200      |
|    LMods     |                 | BottomRow+LMods |     Base      |                |                  |               |
|    RMods     | BottomRow+RMods |                 |               |      Base      |                  |               |
|     Nav      |     HomeRow     |                 |               |                | DirectComboLeft  |      200      |
|    FnSym     |                 |     HomeRow     |               |                | DirectComboRight |      200      |
|     Num      |                 |                 |               |                | TriLayer         |      200      |
|     Num2     |                 |     HomeRow     |      Num      |                |                  |               |
|     ANum     |                 |                 |               |                |                  |               |
|     CNum     |                 |                 |               |                |                  |      200      |
|      Mm      |                 |                 |               |                |                  |               |
|     Case     |                 |                 |               |                |                  |               |

## Symbols

| Symbol  | Command                         |
|---------|---------------------------------|
| ⬅️      | KC_LEFT                         |
| ⬅️⬅️    | KC_HOME                         |
| ⬇️      | KC_DOWN                         |
| ⬇️⬇️    | KC_PGDN                         |
| ⬆️      | KC_UP                           |
| ⬆️⬆️    | KC_PGUP                         |
| ➡️      | KC_RIGHT                        |
| ➡️➡️    | KC_END                          |
| ➖       | KC_KP_MINUS                     |
| ➕       | KC_KP_PLUS                      |
| ins     | KC_INS                          |
| del     | KC_DEL                          |
| spc     | KC_SPC                          |
| esc     | KC_ESC                          |
| ↩️️     | KC_ENT                          |
| bspc    | KC_BSPC                         |
| win     | KC_LGUI                         |
| tab     | KC_TAB                          |
| prt     | KC_PSCR                         |
| pipe    | KC_PIPE                         |
| 🔇      | KC_MUTE                         |
| ⏯️      | KC_MPLY                         |
| ⏮️      | KC_MPRV                         |
| ⏭️      | KC_MNXT                         |
| 🔊      | KC_VOLU                         |
| 🔈      | KC_VOLD                         |
| 🔆      | KC_BRIU                         |
| 🔅      | KC_BRID                         |
| copy    | C(KC_C)                         |
| ä       | UP(UMLAUT_a, UMLAUT_A)          |
| ö       | UP(UMLAUT_o, UMLAUT_O)          |
| ü       | UP(UMLAUT_u, UMLAUT_U)          |
| ß       | UM(UMLAUT_s)                    |
| 😀      | UM(SMILEY)                      |
| magic_a | magic:MAGIC_A                   |
| magic_b | magic:MAGIC_B                   |
| magic_c | magic:MAGIC_C                   |
| magic_d | magic:MAGIC_D:qu                |
| magic_e | magic:MAGIC_E                   |
| magic_f | magic:MAGIC_F                   |
| magic_g | magic:MAGIC_G                   |
| magic_h | magic:MAGIC_H                   |
| magic_i | magic:MAGIC_I                   |
| tab ➡️  | custom:NEXT_TAB      NoHold     |
| win ➡️  | custom:NEXT_WINDOW   NoHold     |
| n't     | custom:N_T                      |
| qu      | custom:ADPT_QU                  |
| ing     | custom:ING                      |
| ver     | custom:PRINT_VERSION            |
| CapW    | custom:CAPS_WORDS               |
| sn_case | custom:SNAKE_CASE               |
| SN_CASE | custom:SCREAMING_SNAKE_CASE     |
| camCase | custom:CAMEL_CASE               |
| PasCase | custom:PASCAL_CASE              |
| sl/case | custom:SLASH_CASE               |
| do.case | custom:DOT_CASE                 |
| kb-case | custom:KEBAP_CASE               |
| dead1   | custom:DEAD1                    |
| dead2   | custom:DEAD2                    |
| dead3   | custom:DEAD3                    |

## Generator

- should be usable with any keyboard layout

QMK: https://github.com/zeitlinger/qmk_firmware/tree/ferris

- run `mise run install` to install the dependencies in QMK directory
- run `mise run flash` to flash the keyboard in this directory
