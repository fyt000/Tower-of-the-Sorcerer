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
python baseline/tools/extract_ui.py --exe "D:/Program Files (x86)/Tower of the Sorcerer/TSW.exe"
```

The first script refreshes extraction evidence and local media while preserving
an existing editable Rust campaign. `--regenerate-campaign` explicitly replaces
that campaign. `data/extraction-manifest.json` records source hashes; the C++
form manifest records bitmap hashes and reviewed offsets. Extracted media and
the original executable are excluded from Git.

Original `TSW.txt` and `Tsw.hlp` also supply the Rust player help under `data/help`
and `web/help*.html`. `tools/extract_help.py` maintains that help separately from
the C++ core. Attribution and dependency licenses are in [THIRD_PARTY.md](../THIRD_PARTY.md).
