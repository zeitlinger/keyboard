Hold Keys
- U = Upper
- L = Lower
- I = Upper + Extra
- E = Extra
- O = Other

| Layer   | Keys | 4&nbsp;(tab) | 3&nbsp;(2) | 2&nbsp;(3) | 1&nbsp;(r) | 1&nbsp;(o) | 2&nbsp;(-) | 3&nbsp;(=) | 4&nbsp;(\) |
|---------|------|--------------|------------|------------|------------|------------|------------|------------|------------|
| Hold    |      | E            | I          | L          | U          | U          | L          | I          | E          |
| Letter0 |      | a            | r          | s          | t          | n          | e          | i          | o          |
| Letter1 | U    | q            | w          | f          | p          | l          | u          | y          | , "        |
| Letter2 | L    | z            | x          | c          | v          | h          | , <        | . >        | / ?        |
| Letter3 | UL   | spc          | g          | d          | b          | j          | m          | k          | ; :        |
| Paren   | E    | ` ~          | 9 (        | 0 )        | - _        | = +        | [ {        | ] }        | \ &#124;   |
| Num     | I    | 1 !          | 2 @        | 3 #        | 4 $        | 5 %        | 6 ^        | 7 &        | 8 *        |
| Fun1    | LE   | f1           | f2         | f3         | f4         | f5         | f6         | f7         | f8         |
| Fun2    | LI   | f9           | f10        | f11        | f12        | ↩️️        | bspc       | del        | ins        |
| Nav     | O    | ä            | ö          | ü          | ß          | ⬅️         | ⬇️         | ⬆️         | ➡️         |
| Nav2    | OU   | caps         | prnt       | esc        | tab        | home       | pgdn       | pgup       | end        |
| NavVI   | OE   |              |            |            |            | h          | j          | k          | l          |
| Mouse1  | OL   | 🖱️d         | 🖱️r       | 🖱️m       | 🖱️l       | 🖱️⬅️      | 🖱️⬇️      | 🖱️⬆️      | 🖱️➡️      |   
| Mouse2  | OLU  |              |            | 🖱️b       | 🖱️f       | 🖲️️⬅️     | 🖲️️⬇️     | 🖲️️⬆️     | 🖲️️➡️     |
| Mouse3  | OLE  |              |            |            |            | 🖱️⬅️⬅️    | 🖱️⬇️⬇️    | 🖱️⬆️⬆️    | 🖱️➡️➡️    |   
| Media   | OI   | lrld         | 🎤         | 🔇         | ⏯️         | ⏮️         | 🔈         | 🔊         | ⏭️         |
| System  | OLI  |              |            |            |            |            | 🔅         | 🔆         |            |

Thumb positions

| Thumb Pos | L (met)  | L (alt) | L (spc) | R (ralt) | R (prnt) | R (rctl) |
|-----------|----------|---------|---------|----------|----------|----------|
| Tab       | esc      | tab     | spc     | ↩️️      | bspc     | del      |
| Hold      | ctl+shft | ctl     | shft    | alt      | E        | I        |

| Option       | Value |
|--------------|-------|
| Enter Layout | caps  |
| Exit Layout  | caps  |
| Tap Timeout  | 100   |
| Hold Timeout | 200   |

- [keycodes](https://github.com/jtroo/kanata/blob/main/src/keys/mod.rs)
- [commands](https://github.com/jtroo/kanata/blob/main/docs/config.adoc#configuration)

| Alias                 | Command                            |
|-----------------------|------------------------------------|
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
