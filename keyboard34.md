Hold Keys
- Y = Symbol
- O = Mouse
- V = Navigation
- N = Number
- F = FN Keys
- U = Umlaute                  

```                   
```



| Layer    | Keys | 4    | 3    | 2    | 1    | 1e   | 1e   | 1       | 2       | 3       | 4        |
|----------|------|------|------|------|------|------|------|---------|---------|---------|----------|
| Hold     |      |      |      |      |      |      |      |         |         |         |          |
| Hold     |      | ctl  | alt  | V    | Y    |      |      | N       | F       | alt     | ctl      |
| Hold     |      |      |      |      |      |      |      |         |         |         |          |
| Position |      | tab  | q    | w    | e    | r    | u    | i       | o       | p       | [        |
| Position |      | caps | a    | s    | d    | f    | j    | k       | l       | ;       | '        |
| Position |      | shft | z    | x    | c    | v    | m    | ,       | .       | /       | rshft    |
| Base     |      | x    | l    | d    | p    | g    | z    | k       | o       | u       | ; :      |
| Base     |      | n    | r    | t    | s    | w    | y    | h       | e       | i       | a        |
| Base     |      | q    | j    | m    | c    | v    | b    | f       | ' "     | , !     | . ?      |
| Umlaute  | U    | esc  |      | del  | meta | prnt |      |         |         |         |          |
| Umlaute  | U    | ü    | ö    | ä    | ß    |      |      |         |         |         |          |
| Umlaute  | U    |      | spc  | tab  |      | caps |      |         |         |         |          |
| Numbers  | N    |      | 7    | 8    | 9    |      |      |         |         |         |          |
| Numbers  | N    | 0    | 1    | 2    | 3    |      |      |         |         |         |          |
| Numbers  | N    |      | 4    | 5    | 6    |      |      |         |         |         |          |
| FN       | F    | f12  | f7   | f8   | f9   |      |      |         |         |         |          |
| FN       | F    | f11  | f1   | f2   | f3   |      |      |         |         |         |          |
| FN       | F    | f10  | f4   | f5   | f6   |      |      |         |         |         |          |
| Symbol   | Y    |      |      |      |      |      |      | = +     | [ {     | ] }     | ` ~      |
| Symbol   | Y    |      |      |      |      |      |      | - _     | ( <     | ) >     | \ &#124; |
| Symbol   | Y    |      |      |      |      |      |      | $ *     | @ #     | & %     | / ^      |
| Nav      | V    |      |      |      |      |      | redo | paste   | copy    | cut     | undo     |
| Nav      | V    |      |      |      |      |      |      | ⬅️      | ⬇️      | ⬆️      | ➡️       |
| Nav      | V    |      |      |      |      |      | ins  | home    | pgdn    | pgup    | end      |
| Mouse    | O    |      |      |      |      |      |      | 🖱️⬅️⬅️ | 🖱️⬇️⬇️ | 🖱️⬆️⬆️ | 🖱️➡️➡️  |   
| Mouse    | O    | 🖱️d | 🖱️r | 🖱️m | 🖱️l |      |      | 🖱️⬅️   | 🖱️⬇️   | 🖱️⬆️   | 🖱️➡️    |   
| Mouse    | O    |      |      | 🖱️b | 🖱️f |      |      | 🖲️️⬅️  | 🖲️️⬇️  | 🖲️️⬆️  | 🖲️️➡️   |
| System   | YV   |      |      |      |      |      |      |         | 🔅      | 🔆      |          |
| System   | YV   |      |      |      |      |      |      | ⏮️      | 🔈      | 🔊      | ⏭️       |
| System   | YV   |      |      |      |      |      |      | lrld    | 🎤      | 🔇      | ⏯️       |       

Thumb positions

| Thumb Pos | L (alt) | L (spc) | R (ralt) | R (prnt) |
|-----------|---------|---------|----------|----------|
| Tab       | tab     | spc     | ↩️️      | bspc     |
| Hold      | O       | shft    | U        | shft     |

| Option       | Value |
|--------------|-------|
| Enter Layout | caps  |
| Exit Layout  | `     |
| Tap Timeout  | 100   |
| Hold Timeout | 200   |

- [keycodes](https://github.com/jtroo/kanata/blob/main/src/keys/mod.rs)
- [commands](https://github.com/jtroo/kanata/blob/main/docs/config.adoc#configuration)

| Alias    | Command                            |
|----------|------------------------------------|
| redo     | C-S-z                              |
| undo     | C-z                                |
| copy     | C-c                                |
| paste    | C-v                                |
| cut      | C-x                                |
| mb-left  | mouseleft                          |
| mb-mid   | mousemid                           |
| mb-right | mouseright                         |
| mb-dleft | (multi mouseleft mouseleft)        |
| mb-back  | mousebackward                      |
| mb-forw  | mouseforward                       |
| wh-up    | (mwheel-up 50 120)                 |
| wh-down  | (mwheel-down 50 120)               |
| wh-left  | (mwheel-left 50 120)               |
| wh-right | (mwheel-right 50 120)              |
| m-up     | (movemouse-up 1 1)                 |
| m-left   | (movemouse-left 1 1)               |
| m-down   | (movemouse-down 1 1)               |
| m-right  | (movemouse-right 1 1)              |
| ma-up    | (movemouse-accel-up 1 1000 1 5)    |
| ma-left  | (movemouse-accel-left 1 1000 1 5)  |
| ma-down  | (movemouse-accel-down 1 1000 1 5)  |
| ma-right | (movemouse-accel-right 1 1000 1 5) |       
| mute-mic | (arbitrary-code 248)               |
| ä        | (unicode ä)                        |
| ö        | (unicode ö)                        |
| ü        | (unicode ü)                        |
| ß        | (unicode ß)                        |


| Symbol  | Command  |
|---------|----------|
| `       | grv      |
| ↩️️     | ent      |
| ⬅️      | left     |
| ⬇️      | down     |
| ⬆️      | up       |
| ➡️      | rght     |
| 🖱️⬅️   | m-left   |
| 🖱️⬇️   | m-down   |
| 🖱️⬆️   | m-up     |
| 🖱️➡️   | m-right  |
| 🖱️⬅️⬅️ | ma-left  |
| 🖱️⬇️⬇️ | ma-down  |
| 🖱️⬆️⬆️ | ma-up    |
| 🖱️➡️➡️ | ma-right |
| 🖲️️⬅️  | wh-left  |
| 🖲️️⬇️  | wh-down  |
| 🖲️️⬆️  | wh-up    |
| 🖲️️➡️  | wh-right |
| 🖱️d    | mb-dleft |
| 🖱️l    | mb-left  |
| 🖱️m    | mb-mid   |
| 🖱️r    | mb-right |
| 🖱️b    | mb-back  |
| 🖱️f    | mb-forw  |
| 🔇      | mute     |
| 🎤      | mute-mic |
| ⏯️      | pp       |
| ⏮️      | prev     |
| ⏭️      | next     |
| 🔊      | volu     |
| 🔈      | voldwn   |
| 🔆      | brup     |
| 🔅      | brdown   |
