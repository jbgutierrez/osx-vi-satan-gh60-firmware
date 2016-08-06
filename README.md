# OSX/Vi flavored Satan GH60 firmware

This is an unconventional layout for the Satan GH60 PCB.
As an OSX user in love with the vi editor I like Apple's keyboard but, it seems like something is missing.

Let's try a few tweaks!

## Goals

* Navigate interfaces faster reducing hands movement
* Reduce finger strain through alternative shortcuts

## Design Principles

* Customizations should not interfere with exiting keyboard shortcuts/behaviours
* Alternative key strokes should be placed when original ones are hard to remember or awkward to type
- Minimal response times should be maintained therefore multiaction keys should be avoided

## Layers

### Base Layer

* [Layout](http://www.keyboard-layout-editor.com/#/gists/68883db060f32a591c0c847f7d6b33c7)

* Honors ANSI layout with no modification (with the exception of `Caps Lock`)
* `Caps Lock` cycles through programs

### Arrow Layer

* [Layout](http://www.keyboard-layout-editor.com/#/gists/909582620181ef0aac54f6435a1d4a7e)

* Closely mimics the behaviour of [TouchCursor](http://martin-stone.github.io/touchcursor/) software from a vi user point of view. Motion keys are provided `h`, `j`, `k`, `l`, `b`, `w`, `ctrl-u` and `ctrl-d` to improve cursor navigation. You can even enter `visual mode` with `v` and select text while hitting motion keys. Keys `y`, `space`, `delete` reset `visual mode`.

* `esc` deactivates layer.

### Media and Mouse Layer

* [Layout](http://www.keyboard-layout-editor.com/#/gists/aa973f0375b23a91f77178d47396fc25)

* Right and left click are conveniently placed at `d` and `f` keys to keep both hands at the home row while controlling your mouse. Diagonal mouse movements are also provided.

* Media controls are placed in a position that resambles Apple's keyboard.

* `esc` deactivates layer

## Opinionated enhancements

### Tap-dancing keys

* Shift, Alt, and Control modifiers are one-shot. When tapped, they are considered active for the immediate next key stroke. When double tapped, they toggle on, until a third, single tap sometime later. When held, they act as expected.

* Tapping `;` key once yields `;`, tapping it twice yields `:`.

### Leader key sequences

The following key sequences are provided:

* `c` activates cursor layer
* `d` shows desktop
* `e` launches exposé and enters mouse layer
* `l` locks screen
* `m` activates mouse and media layer
* `p` types password (see `secrets.h`)
* `s` saves screenshot
* `ss` saves screenshot of selected area
* `u` types username (see `secrets.h`)

### Holding key actions

* Keys on the number row double as function keys when held

### One-shot keys

* `` ` ``, `^` and `~` don't need to hit `space`

## Building

_TODO: One of these days_

## License

The files in this project are licensed under the MIT license
See http://opensource.org/licenses/MIT

Happy hacking!
