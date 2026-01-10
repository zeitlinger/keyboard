# Hands Down Vibranium Keyboard

### Credits

- [Hands Down Keyboard Layout](https://sites.google.com/alanreiser.com/handsdown)
- [The T-34 keyboard layout](https://www.jonashietala.se/blog/2021/06/03/the-t-34-keyboard-layout/)
- [X-Case](https://github.com/andrewjrae/kyria-keymap#x-case)

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

## Layout

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
  
- Magic A = Magic Key A
- Magic A (2) = 2nd press of Magic Key A
-  

| Magic |   Magic A   | Magic B  | Magic C |
|:-----:|:-----------:|:--------:|:-------:|
|   a   |             |          |    u    |
|   b   |      l      | "ecause" |    l    |
|   c   |      k      |    p     |    k    |
|   d   |  "oesn't"   |  "oes"   | "on't"  |
|   e   |      o      |          |    o    |
|   f   |      f      |   "or"   |         |
|   g   |      n      |    k     |    l    |
|   h   |      y      |   "ey"   |         |
|   i   |      '      |  "'ve"   |         |
|   j   |    "ust"    |          |         |
|   k   |      n      |  "now"   |    n    |
|   l   |      p      |    m     |    v    |
|   m   |      b      |  "ent"   |    b    |
|   n   |      g      |    k     |  "ly"   |
|   o   |      e      |          |         |
|   p   |      l      |    s     |    l    |
|   q   |             |          |         |
|   r   |      k      |          |         |
|   s   |      p      |  "ion"   |    p    |
|   t   |    "ion"    |  "ing"   |  "ion"  |
|   u   |             |          |    a    |
|   v   |    "er"     |   "en"   |         |
|   w   |      n      |    s     |         |
|   x   |      p      |    c     |         |
|   y   |             |          |         |
|   z   | "eitlinger" |          |         |
|  spc  |   "the "    |  dotSpc  | "the "  |
|  tab  |   "the "    |  "and "  |         |
|  ↩️️  |   "the "    |  "and "  |         |
|   ~   |      /      |          |         |
|   ,   |   " but "   | " and "  |         |
|   .   |      /      |   "./"   |         |
|   -   |      >      |          |         |
|   =   |      >      |          |         |
|   !   |      =      |          |         |

| Chord | output        |
|-------|---------------|
| bi    | "been"        |
| bk    | "back"        |
| ba    | "about"       |
| be    | "because"     |
| bd    | "before"      |
| bl    | "believe"     |
| bt    | "better"      |
| bw    | "between"     |
| bh    | "behind"      |
| bn    | "black"       |
| br    | "break"       |
| bu    | "business"    |
| cu    | "could"       |
| ca    | "actually"    |
| ce    | "service"     |
| ch    | "research"    |
| ci    | "click"       |
| cl    | "couple"      |
| cn    | "change"      |
| co    | "continue"    |
| cq    | "course"      |
| cv    | "cover"       |
| cr    | "across"      |
| ct    | "caught"      |
| cd    | "couldn't"    |
| cy    | "policy"      |
| di    | "didn't"      |
| da    | "today"       |
| dc    | "decide"      |
| de    | "video"       |
| df    | "different"   |
| dn    | "hadn't"      |
| du    | "products"    |
| dy    | "already"     |
| fo    | "from"        |
| fa    | "family"      |
| ft    | "father"      |
| fg    | "figure"      |
| fn    | "finally"     |
| fi    | "finger"      |
| fs    | "finish"      |
| fl    | "follow"      |
| fe    | "information" |
| fw    | "software"    |
| fu    | "found"       |
| ga    | "again"       |
| ge    | "began"       |
| gj    | "general"     |
| gh    | "rights"      |
| gz    | "glance"      |
| go    | "group"       |
| gr    | "great"       |
| gd    | "ground"      |
| gs    | "against"     |
| gu    | "guess"       |
| ke    | "question"    |
| ky    | "quickly"     |
| le    | "length"      |
| lk    | "like"        |
| la    | "laugh"       |
| lj    | "leave"       |
| lf    | "himself"     |
| lh    | "health"      |
| li    | "light"       |
| lz    | "almost"      |
| lo    | "along"       |
| lq    | "listen"      |
| lt    | "little"      |
| ly    | "always"      |
| mq    | "more"        |
| me    | "message"     |
| mh    | "might"       |
| mi    | "minute"      |
| mz    | "moment"      |
| ma    | "someone"     |
| ms    | "items"       |
| mu    | "music"       |
| my    | "myself"      |
| na    | "anyway"      |
| nc    | "links"       |
| nd    | "understand"  |
| nh    | "anything"    |
| ni    | "university"  |
| no    | "another"     |
| nu    | "enough"      |
| ns    | "answer"      |
| nq    | "inside"      |
| nj    | "instead"     |
| nt    | "nothing"     |
| nz    | "number"      |
| ny    | "company"     |
| np    | "anyone"      |
| pe    | "people"      |
| pa    | "privacy"     |
| pr    | "parent"      |
| pq    | "place"       |
| pl    | "please"      |
| pn    | "happen"      |
| ps    | "person"      |
| po    | "product"     |
| pz    | "problem"     |
| pt    | "pretty"      |
| py    | "probably"    |
| pu    | "public"      |
| re    | "really"      |
| ra    | "program"     |
| rw    | "order"       |
| rj    | "ready"       |
| rm    | "remember"    |
| rp    | "reply"       |
| rs    | "there's"     |
| rz    | "return"      |
| rh    | "review"      |
| ri    | "right"       |
| rl    | "world"       |
| rn    | "morning"     |
| ro    | "around"      |
| ry    | "years"       |
| rq    | "everyone"    |
| sa    | "should"      |
| se    | "search"      |
| sc    | "second"      |
| si    | "silence"     |
| sl    | "slightly"    |
| so    | "slowly"      |
| sn    | "wasn't"      |
| sm    | "something"   |
| st    | "stood"       |
| su    | "support"     |
| sd    | "suddenly"    |
| sp    | "suppose"     |
| sr    | "surprise"    |
| sy    | "system"      |
| ti    | "think"       |
| ta    | "contact"     |
| tb    | "table"       |
| tc    | "watch"       |
| th    | "thanks"      |
| to    | "thought"     |
| tz    | "through"     |
| te    | "notice"      |
| tn    | "thing"       |
| tu    | "though"      |
| tg    | "together"    |
| tw    | "toward"      |
| ts    | "that's"      |
| ty    | "thank you"   |
| ve    | "have"        |
| va    | "available"   |
| vi    | "services"    |
| vy    | "everything"  |
| wq    | "would"       |
| wa    | "walk"        |
| wh    | "which"       |
| wt    | "what's"      |
| wr    | "where"       |
| wi    | "window"      |
| wo    | "without"     |
| wz    | "wrong"       |
| ws    | "reviews"     |
| wu    | "wouldn't"    |
| wy    | "worry"       |
| za    | "realize"     |

| Layer | L. Pin. | L. Ring | L. Mid. | L. Ind. | R. Ind. | R. Mid. | R. Ring | R. Pin. |
|:-----:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|
| Base  |   esc   |    x    |    w    |  dead3  |  dead2  |    '    | magicC  |  dead1  |
| Base  |    s    |    c    |    n    |    t    |    a    |    e    |    i    |    h    |
| Base  | *Right  |    f    |    l    |    d    |    u    |    o    |    y    |  *Left  |
| Base  |         |         |  *Nav   |    r    |   spc   | *FnSym  |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Base  |         |         |         |    v    |  "ing"  |         |         |         |
| Base  |         |         |         |   💎    |   💎    |         |         |         |
| Base  |         |         |         |    k    | magicA  |         |         |         |
| Base  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Base  |         |         |    m    |         |         | magicB  |         |         |
| Base  |         |         |   💎    |         |         |   💎    |         |         |
| Base  |         |         |    g    |         |         |    ,    |         |         |
| Base  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Base  |         |    p    |         |         |         |         |  chord  |         |
| Base  |         |   💎    |         |         |         |         |   💎    |         |
| Base  |         |    b    |         |         |         |         |    .    |         |
| Base  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Base  |  "qu"   |         |         |         |         |         |         |    q    |
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
|  Nav  |  CS-e   |         |         |         |         |         |         |    ß    |
|  Nav  |   💎    |         |         |         |         |         |         |   💎    |
|  Nav  |   C-e   |         |         |         |         |         |         |  ➡️➡️   |
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
| CNum  |         |         |         |         |         |         |         |         |
| CNum  |         |         |         |   💎    |         |         |         |         |
| CNum  |         |         |         |  goog@  |         |         |         |         |
| CNum  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| CNum  |         |         |         |         |         |         |         |         |
| CNum  |         |         |   💎    |         |         |         |         |         |
| CNum  |         |         |  zeit@  |         |         |         |         |         |
| CNum  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| CNum  |         |         |         |         |         |         |         |         |
| CNum  |         |   💎    |         |         |         |         |         |         |
| CNum  |         |  gra@   |         |         |         |         |         |         |
| CNum  |         |         |         |         |         |         |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| CNum  |         |         |         |         |         |         |         |         |
| CNum  |   💎    |         |         |         |         |         |         |         |
| CNum  |   GZ    |         |         |         |         |         |         |         |
| CNum  |         |         |         |         |         |         |         |         |
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
| magicA  | custom:MAGIC_A                  |
| magicB  | custom:MAGIC_B                  |
| magicC  | custom:MAGIC_C                  |
| chord   | custom:CHORD_KEY     NoHold     |
| tab ➡️  | custom:NEXT_TAB      NoHold     |
| win ➡️  | custom:NEXT_WINDOW   NoHold     |
| n't     | custom:N_T                      |
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
| GZ      | "Gregor Zeitlinger"             |
| gra@    | "gregor.zeitlinger@grafana.com" |
| zeit@   | "gregor@zeitlinger.de"          |
| goog@   | "zeitlinger@gmail.com"          |

## Generator

- should be usable with any keyboard layout

QMK: https://github.com/zeitlinger/qmk_firmware/tree/ferris

- run `mise run install` to install the dependencies in QMK directory
- run `mise run flash` to flash the keyboard in this directory
