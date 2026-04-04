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

| Magic | Magic A  | Magic B  | Magic C |
|:-----:|:--------:|:--------:|:-------:|
|   a   |          |    u     |    u    |
|   b   |    l     | "ecause" |    l    |
|   c   |    k     |    p     |    k    |
|   d   | "oesn't" |  "oes"   | "on't"  |
|   e   |    o     |          |    o    |
|   f   |    f     |   "or"   |         |
|   g   |    n     |    k     |    l    |
|   h   |    y     |   "ey"   |         |
|   i   |    '     |  "'ve"   |         |
|   j   |  "ust"   |          |         |
|   k   |    n     |  "now"   |    n    |
|   l   |    p     |    m     |    v    |
|   m   |    b     |  "ent"   |    l    |
|   n   |    g     |    k     |  "ly"   |
|   o   |    e     |          |         |
|   p   |    l     |    s     |    l    |
|   q   |          |          |         |
|   r   |    k     |          |         |
|   s   |    p     |  "ion"   |    p    |
|   t   |  "ion"   |  "ing"   |  "ion"  |
|   u   |          |    a     |         |
|   v   |   "er"   |   "en"   |         |
|   w   |    n     |    s     |         |
|   x   |    p     |    c     |         |
|   y   |          |          |         |
|   z   |          |          |         |
|  spc  |  "the "  |  dotSpc  | "the "  |
|  tab  |  "the "  |  "and "  |         |
|  ↩️️  |  "the "  |  "and "  |         |
|   ~   |    /     |          |         |
|   ,   | " but "  | " and "  |         |
|   .   |    /     |   "./"   |         |
|   -   |    >     |          |         |
|   =   |    >     |          |         |
|   !   |    =     |          |         |

## Chord Table

> **📖 [Complete Chord Mode Documentation](CHORD_MODE.md)**  
> Learn how to use chords to type 220+ common words with just two letters!  
> Includes usage guide, capitalization, customization, and more.
 
- Used = has been incorporated into daily routine (plan means those are next to learn)

| Chord | output                          | Used |
|-------|---------------------------------|------|
| b     | "about"                         |      |
| b,    | "observability"                 |      |
| b.    | "boolean"                       |      |
| be    | "began"                         |      |
| bh    | "behind"                        |      |
| bi    | "being"                         |      |
| bj    | "between"                       |      |
| bo    | "become"                        |      |
| br    | "break"                         |      |
| bu    | "business"                      |      |
| by    | "body"                          |      |
| c     | "could"                         |      |
| c,    | "couldn't"                      |      |
| c.    | "const"                         |      |
| ca    | "actually"                      |      |
| ce    | "service"                       |      |
| ch    | "research"                      |      |
| ci    | "click"                         |      |
| cj    | "project"                       |      |
| cn    | "been"                          |      |
| co    | "continue"                      |      |
| cr    | "across"                        |      |
| cu    | "current"                       |      |
| cy    | "policy"                        |      |
| d     | "didn't"                        | plan |
| d,    | "hadn't"                        |      |
| da    | "describe"                      |      |
| dd    | "zeitlinger@gmail.com"          |      |
| di    | "during"                        |      |
| dj    | "build"                         |      |
| do    | "import"                        |      |
| dr    | "their"                         |      |
| du    | "products"                      |      |
| dy    | "already"                       |      |
| f     | "from"                          |      |
| f,    | "fails"                         |      |
| f.    | "false"                         |      |
| fa    | "after"                         |      |
| fe    | "feel"                          |      |
| ff    | "gregor.zeitlinger@grafana.com" |      |
| fh    | "then"                          |      |
| fi    | "first"                         |      |
| fj    | "finger"                        |      |
| fl    | "have"                          |      |
| fo    | "information"                   |      |
| fr    | "software"                      |      |
| fu    | "found"                         |      |
| fy    | "forty"                         |      |
| g     | "again"                         |      |
| g.    | "Grafana"                       |      |
| ga    | "glance"                        |      |
| gg    | "Gregor"                        |      |
| gi    | "giving"                        |      |
| gj    | "general"                       |      |
| go    | "global"                        | plan |
| gr    | "great"                         |      |
| gu    | "guess"                         |      |
| gy    | "every"                         |      |
| k     | "question"                      |      |
| k,    | "config"                        |      |
| k.    | "key"                           |      |
| ka    | "make"                          |      |
| ke    | "keep"                          |      |
| kh    | "check"                         |      |
| ki    | "kind"                          |      |
| kj    | "java"                          |      |
| ko    | "know"                          |      |
| kr    | "work"                          |      |
| ku    | "caller"                        |      |
| ky    | "quickly"                       |      |
| l     | "like"                          |      |
| l,    | "level"                         |      |
| l.    | "class"                         |      |
| la    | "language"                      | plan |
| ld    | "with"                          |      |
| le    | "leave"                         |      |
| lh    | "health"                        |      |
| li    | "light"                         |      |
| lj    | "large"                         |      |
| ll    | "gregor@zeitlinger.de"          |      |
| lo    | "along"                         |      |
| lr    | "later"                         |      |
| lu    | "almost"                        |      |
| ly    | "only"                          |      |
| m     | "more"                          |      |
| m,    | "lgtm"                          |      |
| m.    | "method"                        |      |
| ma    | "some"                          |      |
| me    | "message"                       |      |
| mh    | "might"                         |      |
| mi    | "minute"                        |      |
| mj    | "major"                         |      |
| mo    | "feature"                       |      |
| mu    | "music"                         |      |
| my    | "myself"                        |      |
| n     | "understand"                    |      |
| n,    | "single"                        |      |
| na    | "anyway"                        |      |
| nd    | "instead"                       |      |
| ne    | "number"                        |      |
| nh    | "anything"                      |      |
| ni    | "into"                          |      |
| nj    | "issues"                        |      |
| no    | "another"                       |      |
| nu    | "enough"                        |      |
| ny    | "company"                       |      |
| p     | "people"                        |      |
| p,    | "please"                        |      |
| p.    | "promise"                       |      |
| pa    | "privacy"                       |      |
| pe    | "place"                         |      |
| pi    | "point"                         |      |
| pj    | "problem"                       |      |
| po    | "product"                       |      |
| pp    | "Prometheus"                    |      |
| pr    | "parent"                        |      |
| pu    | "public"                        |      |
| py    | "probably"                      |      |
| r     | "really"                        |      |
| r,    | "route"                         |      |
| r.    | "error"                         |      |
| ra    | "program"                       |      |
| re    | "ready"                         |      |
| rg    | "rights"                        |      |
| rh    | "review"                        |      |
| ri    | "right"                         |      |
| rj    | "return"                        |      |
| rl    | "query"                         |      |
| ro    | "around"                        |      |
| rs    | "request"                       |      |
| rt    | "they"                          |      |
| ru    | "true"                          |      |
| ry    | "years"                         |      |
| rz    | "realize"                       |      |
| s     | "should"                        |      |
| s,    | "wasn't"                        |      |
| s.    | "string"                        |      |
| sa    | "same"                          |      |
| sc    | "this"                          |      |
| se    | "search"                        |      |
| sh    | "share"                         |      |
| si    | "someone"                       |      |
| sj    | "subject"                       |      |
| so    | "slowly"                        |      |
| sr    | "surprise"                      |      |
| su    | "support"                       |      |
| ss    | "something"                     |      |
| sy    | "system"                        |      |
| t     | "think"                         |      |
| t,    | "tenant"                        |      |
| t.    | "type"                          |      |
| ta    | "today"                         |      |
| te    | "these"                         |      |
| th    | "other"                         |      |
| ti    | "time"                          |      |
| tj    | "through"                       |      |
| to    | "thought"                       |      |
| tr    | "there"                         |      |
| tt    | "OpenTelemetry"                 |      |
| tu    | "though"                        |      |
| ty    | "thank you"                     |      |
| v     | "even"                          |      |
| v,    | "contrib"                       |      |
| v.    | "void"                          |      |
| va    | "available"                     |      |
| ve    | "very"                          |      |
| vh    | "version"                       |      |
| vi    | "services"                      |      |
| vj    | "notice"                        |      |
| vo    | "over"                          |      |
| vr    | "never"                         |      |
| vu    | "value"                         |      |
| vy    | "everything"                    |      |
| w     | "would"                         |      |
| w,    | "wouldn't"                      |      |
| w.    | "await"                         |      |
| wa    | "walk"                          |      |
| we    | "when"                          |      |
| wh    | "which"                         |      |
| wi    | "will"                          |      |
| wj    | "wrong"                         |      |
| wo    | "without"                       |      |
| wr    | "where"                         |      |
| wu    | "internal"                      |      |
| wy    | "worry"                         |      |
| x     | "context"                       |      |
| x.    | "export"                        |      |
| xa    | "example"                       |      |
| xe    | "execute"                       |      |
| xh    | "https"                         |      |
| xi    | "existing"                      |      |
| xj    | "exception"                     |      |
| xr    | "resource"                      |      |
| xu    | "actual"                        |      |
| xy    | "telemetry"                     |      |
| z,    | "smile"                         |      |
| z.    | "async"                         |      |
| za    | "organize"                      |      |
| ze    | "GitHub"                        |      |
| zh    | "Spring starter"                |      |
| zi    | "spring"                        |      |
| zj    | "javaagent"                     |      |
| zo    | "Grafana Labs"                  |      |
| zu    | "Spring Boot"                   |      |
| zy    | "declarative config"            | yes  |
| zz    | "Zeitlinger"                    |      |

## Layout

| Layer | L. Pin. | L. Ring | L. Mid. | L. Ind. | R. Ind. | R. Mid. | R. Ring | R. Pin. |
|:-----:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|
| Base  |   esc   |    x    |    w    |  dead3  |  dead2  |    '    | magicC  |  dead1  |
| Base  |    s    |    c    |    n    |    t    |    a    |    e    |    i    |    h    |
| Base  | *Right  |    f    |    l    |    d    |    u    |    o    |    y    |  *Left  |
| Base  |         |         |  *Nav   |    r    |   spc   | *FnSym  |         |         |
|       | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Base  |         |         |         |    v    |   ing   |         |         |         |
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
| magicA  | custom:MAGIC_A                  |
| magicB  | custom:MAGIC_B                  |
| magicC  | custom:MAGIC_C                  |
| chord   | custom:CHORD_KEY     NoHold     |
| tab ➡️  | custom:NEXT_TAB      NoHold     |
| win ➡️  | custom:NEXT_WINDOW   NoHold     |
| n't     | custom:N_T                      |
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
