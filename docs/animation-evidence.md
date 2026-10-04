# Original animation and sound evidence

This audit reads the installed English Tower of the Sorcerer for Windows 1.2
executable and bitmaps without launching or modifying the installation. It does
not use the older Cocos implementation. Executable virtual addresses below refer
to `TSW.exe`, SHA-256
`41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779`.

The Delphi method table contains the original method names and pointers; these
were read before following their instructions. For example, file offsets
`0x413be`, `0x41114`, `0x41127`, `0x41215`, `0x40e22`, and `0x4136a` identify
`Timer1Timer`, `yusyahyouji1`, `yusyahyouji`, `imagework`, `kaidanwork`, and
`taisen`. The `kaidanwork` entry's method pointer is `0x442dc8`.

## Stationary monster and NPC animation

`mhyouji` at `0x442c38..0x442d4e` draws each map cell into two board bitmaps.
The first uses its original image-list index; the second uses the offset from
`imagework` at `0x454c10..0x454d9e`. `Timer1Timer` at
`0x443120..0x44339f` alternates these bitmaps by toggling byte `0x48c5d2`.
The cell coordinates are identical in the two draws. No lateral translation,
sine-wave displacement, or board-cell movement implements this animation.

| Initial original atlas cells | Alternate frame |
| --- | --- |
| Merchant/NPC first poses 19, 21, 23, 25, 27 | Next cell, +1 |
| Ordinary enemy first poses 61, 63, …, 95 | Next cell, +1 |
| Giant Octopus footprint 97–105 | Corresponding cell 106–114, +9 |
| Dragon footprint 115–123 | Corresponding cell 124–132, +9 |
| Later ordinary enemy first poses 133, 135, …, 157 | Next cell, +1 |
| Lava 13 | Alternate lava 160 |
| Star void 14 | Alternate star void 161 |

The original dispatcher literally adds one for the paired ranges and assumes
the map contains the first pose. The shared renderer's `Art::animated_sprite`
also accepts the alternate pose as input: it normalizes a paired cell to the
same two-frame sequence, avoiding an unintended adjacent monster when a person
selects the alternate artwork in the editor. It maps original 40-pixel,
grid-aligned atlas rectangles or numeric cell IDs and leaves custom rectangles
unchanged. All nine large-creature cells share the same phase.

## Walking, standing, and turning

The walking and idle poses are distinct. Each directional color cell below is
followed by its monochrome silhouette mask, and transparency is the inverse of
that mask.

| Direction | Walking poses | Standing pose | Damaged pose |
| --- | --- | --- | --- |
| Down | 185, 187 | 189 | 191 |
| Left | 193, 195 | 197 | 199 |
| Right | 201, 203 | 205 | 207 |
| Up | 209, 211 | 213 | 215 |

`yusyahyouji1` at `0x4433a4..0x443644` prepares the two walking frames at
the current tile. Its directional source values are 250/252, 258/260,
266/268, and 274/276. `yusyahyouji` at `0x443648` subtracts 66 to obtain the
zero-based image-list index, giving the one-based atlas cells above.

`yusyaidou` at `0x443808` alternates the walking poses while interpolating
between cells. `idou` at `0x44c04c` calls `yusyahyouji1` again on arrival
(`0x44c1ee..0x44c1f0`). The next ambient timer redraw sets source values
254, 262, 270, or 278 at `0x4431d3..0x443214` and
`0x4432fb..0x44333c`, giving standing cells 189, 197, 205, and 213. Both
ambient buffers use the same standing pose, so the hero stops wiggling.

Keyboard direction changes write `0x4b87e8` before testing the destination or
the board edge: up at `0x460c8b`, left at `0x460d94`, right at `0x460e40`,
and down in the following branch. A brick wall, tile 8, dispatches directly
from `handan`'s table at `0x4444e3` to its return at `0x448fbc`; it does not
call the walking routine. The following ambient tick shows the new direction's
standing pose. A blocked turn therefore changes facing without moving or
starting a perpetual walk cycle.

## Speed presets and battle strikes

The Delphi form initializes its ambient timer to 500 ms, but the speed settings
replace that interval. `speedhigh`, `speedmiddle`, and `speedlow` at
`0x47f47c`, `0x47f4e0`, and `0x47f544` assign 150, 250, and 350 ms
respectively to the ambient, event, and repeat-input timers. The executable's
initial option byte at `0x489b9f` is 1, selecting High. The shared renderer
defaults to High's 150 ms ambient interval, adjustable through
`rules.presentation.ambient_frame_ms` and the animation-speed setting. A
250 ms interval corresponds to Medium. Display speed does not change engine
turns or the damage formula.

The ordinary battle queue builder, `taisen` at `0x44a480..0x44b6aa`, queues
audio opcode 1, operand 3, for **every** hero and enemy strike. For example,
the first strike sound is written at `0x44b467..0x44b47e`, and the repeated
hero/enemy sound records occur at `0x44b59f..0x44b5ac` and
`0x44b682..0x44b699`. The audio dispatcher selects the dedicated
`taisen.wav` player (`0x4527e0..0x4527f3`). Battle sound must not be played
only once at encounter start or on an unrelated flashing clock.

Enemy damage uses the original starburst color cell **184** with its preceding
mask **183**. Hero damage uses the damaged directional pose above and its
following mask. These are masked sprite replacements/overlays; there is no
gold line from the hero to the enemy or expanding ring in the original routine.

An isolated Unicorn probe of `taisen` with three hero strikes and two enemy
strikes produced five identical six-record patterns, alternating the target
damage operation:

```text
[1,   3,   0]  play taisen.wav
[0,   0,   0]  wait
[9, 104, 183]  render masked burst at encounter cell 104
[0,   6, 184]  underlying road and burst color operands for the previous record
[5, 104, 183]  apply hero's damage to enemy HP
[0,   0,   0]  wait

[1,   3,   0]  play taisen.wav
[0,   0,   0]  wait
[9, 104, 216]  render upward damaged hero with mask 216
[0,   6, 215]  underlying road and damaged hero color operands
[4, 104,   0]  apply enemy's damage to hero HP
[0,   0,   0]  wait
```

`timer2timer` at `0x45265c..0x4526bd` processes two queue records per timer
tick. The six-record strike therefore spans three ticks: sound, then burst,
then the displayed HP calculation. This gives approximate nominal strike
durations 450/750/1050 ms under High/Medium/Low settings. The implementation
can choose configurable durations, but compressing an arbitrarily long fight
into a fixed total loses the original per-strike rhythm and audio.

The original `taisen` calls `idou` before a winnable fight, so its hero and
monster overlays alternate at the encounter cell. A renderer that retains the
hero's approach position until victory has different spatial presentation;
this distinction should not be confused with the damage formula or strike
ordering. Dedicated hit textures in `assets.rs` recover the original artwork
without committing generated bitmap assets.

## Stairs: spiral cover and reveal

`kaidanwork` at `0x442dc8..0x442f7c` prepares two groups of 121 records with
opcode 21 and subcodes 0/1. The queue is consumed in reverse insertion order,
so execution visits order indices 1 through 121 during the cover phase and
then again during the reveal phase. The lookup table at `0x489b20` contains
the row-major cell indices:

```text
  0, 11, 22, 33, 44, 55, 66, 77, 88, 99,110,111,112,113,114,115,116,
117,118,119,120,109, 98, 87, 76, 65, 54, 43, 32, 21, 10,  9,  8,  7,
  6,  5,  4,  3,  2,  1, 12, 23, 34, 45, 56, 67, 78, 89,100,101,102,
103,104,105,106,107,108, 97, 86, 75, 64, 53, 42, 31, 20, 19, 18, 17,
 16, 15, 14, 13, 24, 35, 46, 57, 68, 79, 90, 91, 92, 93, 94, 95, 96,
 85, 74, 63, 52, 41, 30, 29, 28, 27, 26, 25, 36, 47, 58, 69, 80, 81,
 82, 83, 84, 73, 62, 51, 40, 39, 38, 37, 48, 59, 70, 71, 72, 61, 50,
 49, 60
```

This follows the left edge downward, the bottom edge rightward, the right edge
upward, and the top edge leftward, then repeats on each inset rectangle.
`stair_wipe_order(width, height)` generates that exact table for an 11×11
floor and also supports edited rectangular floors.

The opcode-21 handler at `0x45433b` maps each order index to a position.
Subcode 0 draws image-list index `0x9e` at `0x4543d2..0x4543f5`, which is
one-based atlas cell **159**, the crossed-swords cover tile. Subcode 1 draws
the destination floor tile at `0x4544d9..0x45451c` and the hero when revealing
its landing cell (`0x45459b..0x4545ae`). The original result is a two-phase
spiral mosaic, rather than a vertical pan, generic black fade, or centered
floor-number overlay. The associated sound record is opcode 1, operand 9,
which selects **kai.wav**.

The stair builder temporarily sets the event-timer interval to 2/6/10 ms
according to the speed preset (`0x442f1d..0x442f6c`). The handler coalesces an
adjacent matching opcode-21 record, and the timer calls the handler twice per
tick. The nominal raster wipe is consequently much faster than ordinary battle
beats. Windows timer granularity and queued extra operations affect exact
elapsed time; order and artwork are confirmed, while a modern overall duration
is a configurable presentation choice.

## Reproduce the probes

Install the existing research dependencies from `tools/requirements.txt`.
`tools/original_event_probe.py` reads the PE into an isolated Unicorn memory
space; it skips helper calls and reports them, so probe results must be
interpreted together with the rendering instructions above.

```python
import sys
sys.path.insert(0, "tools")
from original_event_probe import probe, pe

# Original battle queue with three hero hits, facing up, approaching slime61.
battle = probe(
    0x44a480, 1, 5, 10, [(1, 5, 9, 61)], end=0x44b6aa,
    globals=[(0x48c584, 104), (0x48c56c, 3), (0x48c568, 0),
             (0x4b87e8, 4)], include_presentation=True,
)
print(battle["queue"])
print(battle["calls"])

# The full original stair lookup table is directly readable PE data.
image = pe.get_memory_mapped_image()
print(list(image[0x89b20:0x89b20 + 121]))
```

## Floor-3 apparition and capture cutscene

The floor-3 summon helper `zenolivework` at `0x461a0c` emits sound record
`[1,7,0]` (`3f.wav`), followed by 17 overlay records with mask cells 166
through 182. Each is followed by `[0,6,91]`: underlying road cell 6 and
Zeno's color cell 91. Cell 166 is white and cell 182 is black; inverse-mask
alpha progressively reveals Zeno. Painting these cells directly would show
opaque noise squares, and replacing the sequence with rings changes its
visual meaning. `Art::masked_tile` retains the atlas pixels and caches the
requested color/mask combination on demand, so later original transformations
can use the same compositor without another list of extracted images.

The capture then includes a distinct cutscene:

1. Opcode 11/subcode 7 at `0x45345c` loads `Data3/title05.bmp`, via the
   literal filename at `0x454878`.
2. Opcode 11/subcode 12 calls `openning9` at `0x482e60`. Its mode comes
   from the following wait record's A operand. Mode 0 and frame operands
   232–247 select dither cells 167–182 after subtracting 66 from the source
   image-list value. The routine tiles those masks over 20 columns and 13
   rows (`0x483152..0x4831a8`), replacing the cached screen/title with the
   dark vortex in `Data3/open1.bmp` (filename constant `0x484758`).
3. Mode 1 initializes with frame operand 0, loading `open1.bmp` as the
   background and `Data3/open2.bmp` as the text-bearing source. The filename
   constant for `open2.bmp` is `0x484780`. The original queue then visits
   frame operands 100–405. At `0x48354f..0x4835be`, the bottom of the copy
   rectangle is that operand: the text-bearing image is revealed from top
   to bottom.
4. Final operand 500 exits the scan and restores the normal window/title;
   `opening31` then resets the hero's equipment and first-cycle stats before
   the prison wake-up conversation.

The baked English text in `open2.bmp` reads: “Now is the time to act. Using
omniscient power, I shall break the sacred sword and get great wisdom.” A
localized shared UI can use the original vortex image with translated text
drawn over it, retaining the reveal direction while supporting Chinese. It
should not show only a title card followed by a generic fade: that would omit
the original narrative shot. Original image filenames already convert to
ignored `web/assets/data3-*.png` through `tools/extract_original.py`.

The mode-1 scan sets its timer to 30/50/70 ms for the original speed presets
at `0x48351b..0x48354a`. Modern cutscene duration can remain configurable;
these constants are distinct from ordinary movement and battle timing.

No timing measurement from a live old-game window is claimed here. Confirmed
frame sources, masks, timer constants, queue order, and sound records are
separate evidence from the shared UI's final rendering and headless regression
checks. Later scripted-event coverage is audited separately in
`docs/mechanics.md` and its preserved event queue metadata.

## Shared presentation and ending boundary

The browser and native interface use these same Rust sprite/frame selections,
strike cues and spiral ordering. Conversations and NPC choices are anchored
inside the board. Ordinary movement accepts further keyboard or pointer input
without a walking overlay or direction-button panel; conversations, combat and
scripted scenes retain the ordered presentation required by their game state.

The first-cycle ending branch at `0x4463a1..0x448fbc` has been probed with the
original queue registers initialized. It emits **1,098 records**: 550 waits,
515 opcode-11 scene operations and 33 sounds, consisting of 17 `open.wav` and
16 `kai2.wav` cues. The subcode-12 renderer modes occur in this order:

| Mode | Frames | First/last parameter |
| --- | --- | --- |
| 2 | 16 | 232–247 |
| 6 | 17 | 1–17 |
| 4 | 77 | 1–400, using variable increments |
| 5 | 400 | 1–400 |
| 7 | 1 | 0 |
| 8 | 1 | 0 |

The final opcode 11/subcode 6 performs the replay reset. These stage counts and
the skipped calls are preserved in `data/original-event-audit.json`; run
`python tools/audit_original_events.py` to regenerate the report. The current
first-cycle ending deliberately uses a compact modern victory/credits scene
before the verified reset. Its complete original raster artwork composition
has not been reproduced. Exact ending artwork, fairy score/rank calculation,
Windows timer granularity and a natural full-tower playthrough remain distinct
validation work.
