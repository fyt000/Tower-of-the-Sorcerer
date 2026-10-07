# Original data and assets

The supported original EXE supplies **51 floor records, 33 monster rows and 268
dialogue/status strings**. Each floor has two stair-landing bytes followed by
121 row-major tile IDs. The C++ core compiles these constants from the original
executable; it does not read Rust campaign JSON at runtime.

| Original input | Use |
|---|---|
| Map initializer in `TSW.exe` | Floor layout and stair landing headers |
| Monster table at file offset `0x88D10` | Shared HP, attack, defense and gold rows |
| Delphi form string list | Dialogue and status text |
| `Data3/Chtable.oz`, `Chtableb.oz` | BMP sprite atlas and background masks |
| `Data3/*.bmp` | Panels, capture/title artwork and red backside variants |
| `Data2/End*.bmp` | Ending animation frames |
| `Midi/*.mid`, `Wav/*.wav` | Original music and effects |
| Form `TTSW10`, Image21/Image33 | Ending story/card, embedded in the replacement |

The game uses the original Data3 artwork at its 40-pixel logical tile size.
The original alternate Data artwork and preferences are not used by the modern
GUI. GeneralUser GS supplies MIDI instruments independently of Windows MIDI.
The replacement loads the original media directly; PNG extraction remains useful
for the Rust UI and for independent asset comparisons.

From the repository root:

```powershell
python -m pip install -r tools/requirements.txt
python tools/extract_original.py --source "D:/Program Files (x86)/Tower of the Sorcerer"
python cpp/tools/extract_ui.py --exe "D:/Program Files (x86)/Tower of the Sorcerer/TSW.exe"
```

The first script refreshes extraction evidence and local media while preserving
an existing editable Rust campaign. `--regenerate-campaign` explicitly replaces
that campaign. `data/extraction-manifest.json` records source hashes; the C++
form manifest records bitmap hashes and reviewed offsets. Extracted media and
the original executable are excluded from Git.

Original `TSW.txt` and `Tsw.hlp` also supply the Rust player help under `data/help`
and `web/help*.html`. `tools/extract_help.py` maintains that help separately from
the C++ core. Attribution and dependency licenses are in [THIRD_PARTY.md](../THIRD_PARTY.md).

## Original saves

`Savedat/save1.dat` through `save8.dat` are raw little-endian records with no
header, encryption or serialized monster table. The original shared writer is
`0x47EADC`; the loader is `0x47E7D4`.

| File offset | Bytes | Content |
|---|---:|---|
| `0` | 6,273 | 51 floors, each two stair landings and 121 tile IDs |
| `6,273` | 684 | 171 signed 32-bit hero/state words |
| Total | **6,957** | The format written by both executables |

Within the hero record, byte offset 628 must equal `-4`. Offsets 656 and 660
hold wrapping 32-bit sums over the first 164 words: an ordinary sum and an
alternating `+word0 -word1 +word2 ...` sum. These legacy checksums do not protect
maps or the final hero words. The C++ loader also checks mapped fields, tile IDs
and stair/coordinate bounds before replacing live state. It retains unmapped
words so importing and rewriting a valid original record does not erase them.
As in the original's fixed-size reads, trailing bytes are ignored; none are added.

The original loader rebuilds the shared Zeno row from seal and cycle flags in
`0x455B49..0x455B9F`. Unsealed: `8000/5000/1000`. Sealed:
`800/500/100 × (cycle_factor_minus_one + 1)`. Ordinary combat applies cycle
scaling again, including the original backside load quirk. Other monster rows
come from constants. Core fidelity takes precedence over preserving a runtime
row that the original itself discards on loading.

New manual, quick and Fairy files use these original records. Earlier `TOSB` v1
C++ snapshots remain readable and use the original monster reconstruction on
import; saving converts them to the original layout. Numbered saves read and
write the same `Savedat/save1.dat` through `save8.dat` files beside the executable.
The slot picker uses only that directory (or an explicit `--save-dir`), with no
search for other locations or earlier C++ names. See [controls and saves](../cpp/README.md).

## Original MIDI playback

`0x47C2BC` selects `.mid` files and calls VCL MediaPlayer; the EXE imports
`mciSendCommandA` from `winmm.dll`. Its resources contain no SoundFont, and no
`sfbk` bank signature is present. Playback uses Windows MCI and its selected
MIDI output device. [Microsoft's MIDI playback example](https://learn.microsoft.com/en-us/windows/win32/multimedia/playing-a-midi-file)
documents this path. Device instrument/controller support can affect playback;
specific missing notes have not been established by an audible comparison.
The C++ replacement embeds GeneralUser GS and synthesizes the same MIDI files
through TinySoundFont, independently of the selected Windows MIDI device.
