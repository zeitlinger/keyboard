Hold Keys
- L = Symbol
- O = Mouse
- V = Navigation
- N = Number
- F = FN Keys
- U = Umlaute                  

```                   
```



| Layer    | Keys | 4    | 3    | 2    | 1    | 1e   | 1e   | 1       | 2       | 3       | 4        |
|----------|------|------|------|------|------|------|------|---------|---------|---------|----------|
| Position |      | tab  | q    | w    | e    | r    | u    | i       | o       | p       | [        |
| Position |      | caps | a    | s    | d    | f    | j    | k       | l       | ;       | '        |
| Position |      | shft | z    | x    | c    | v    | m    | ,       | .       | /       | rshft    |
| Hold     |      | ctl  | alt  | Y    | V    |      |      | N       | F       | alt     | ctl      |
| Base     |      | x    | l    | d    | p    | g    | z    | k       | o       | u       | ; :      |
| Base     |      | n    | r    | t    | s    | w    | y    | h       | e       | i       | a        |
| Base     |      | q    | j    | m    | c    | v    | b    | f       | ' "     | , !     | . ?      |
| Umlaute  | U    | esc  |      | del  | meta | prnt |      |         |         |         |          |
| Umlaute  | U    | ü    | ö    | ä    | ß    |      |      |         |         |         |          |
| Umlaute  | U    |      | spc  | tab  |  ️️  | caps |      |         |         |         |          |
| Numbers  | N    |      | 7    | 8    | 9    |      |      |         |         |         |          |
| Numbers  | N    | 0    | 1    | 2    | 3    |      |      |         |         |         |          |
| Numbers  | N    |      | 4    | 5    | 6    |      |      |         |         |         |          |
| FN Keys  | F    | f12  | f7   | f8   | f9   |      |      |         |         |         |          |
| FN Keys  | F    | f11  | f1   | f2   | f3   |      |      |         |         |         |          |
| FN Keys  | F    | f10  | f4   | f5   | f6   |      |      |         |         |         |          |
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
| Media    | YV   |      |      |      | ️    |      |      | ⏮️      | 🔈      | 🔊      | ⏭️       |
| Media    | YV   |      |      |      |      |      |      | lrld    | 🎤      | 🔇      | ⏯️       |       

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

| Alias                 | Command                            |
|-----------------------|------------------------------------|
| redo                  | C-S-z                              |
| undo                  | C-z                                |
| copy                  | C-c                                |
| paste                 | C-v                                |
| cut                   | C-x                                |
| mouse-double-left     | (multi mouseleft mouseleft)        |
| mwheel-up             | (mwheel-up 50 120)                 |
| mwheel-down           | (mwheel-down 50 120)               |
| mwheel-left           | (mwheel-left 50 120)               |
| mwheel-right          | (mwheel-right 50 120)              |
| movemouse-up          | (movemouse-up 1 1)                 |
| movemouse-left        | (movemouse-left 1 1)               |
| movemouse-down        | (movemouse-down 1 1)               |
| movemouse-right       | (movemouse-right 1 1)              |
| movemouse-accel-up    | (movemouse-accel-up 1 1000 1 5)    |
| movemouse-accel-left  | (movemouse-accel-left 1 1000 1 5)  |
| movemouse-accel-down  | (movemouse-accel-down 1 1000 1 5)  |
| movemouse-accel-right | (movemouse-accel-right 1 1000 1 5) |       
| mute-mic              | (arbitrary-code 248)               |
| ä                     | (unicode ä)                        |
| ö                     | (unicode ö)                        |
| ü                     | (unicode ü)                        |
| ß                     | (unicode ß)                        |


| Symbol  | Command               |
|---------|-----------------------|
| `       | grv                   |
| ↩️️     | ent                   |
| ⬅️      | left                  |
| ⬇️      | down                  |
| ⬆️      | up                    |
| ➡️      | rght                  |
| 🖱️⬅️   | movemouse-left        |
| 🖱️⬇️   | movemouse-down        |
| 🖱️⬆️   | movemouse-up          |
| 🖱️➡️   | movemouse-right       |
| 🖱️⬅️⬅️ | movemouse-accel-left  |
| 🖱️⬇️⬇️ | movemouse-accel-down  |
| 🖱️⬆️⬆️ | movemouse-accel-up    |
| 🖱️➡️➡️ | movemouse-accel-right |
| 🖲️️⬅️  | mwheel-left           |
| 🖲️️⬇️  | mwheel-down           |
| 🖲️️⬆️  | mwheel-up             |
| 🖲️️➡️  | mwheel-right          |
| 🖱️d    | mouse-double-left     |
| 🖱️l    | mouseleft             |
| 🖱️m    | mousemid              |
| 🖱️r    | mouseright            |
| 🖱️b    | mousebackward         |
| 🖱️f    | mouseforward          |
| 🔇      | mute                  |
| 🎤      | mute-mic              |
| ⏯️      | pp                    |
| ⏮️      | prev                  |
| ⏭️      | next                  |
| 🔊      | volu                  |
| 🔈      | voldwn                |
| 🔆      | brup                  |
| 🔅      | brdown                |
