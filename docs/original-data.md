# Original data and assets

The supported EXE supplies **51 floor records, 33 monster rows, and 268
text strings**. A floor record contains two stair-landing bytes followed by
121 row-major tile IDs. C++ compiles these constants from the executable.

| Input | Content |
|---|---|
| `TSW.exe` map initializer | Floor layouts and stair landings |
| Monster table at file offset `0x88D10` | Shared HP, attack, defense, and gold rows |
| Delphi form string list | Dialogue and status text |
| `Data3/Chtable.oz`, `Chtableb.oz` | BMP sprite atlas and background masks |
| `Data3/*.bmp` | Panels, titles, and red backside variants |
| `Data2/End*.bmp` | Ending animation frames |
| `Midi/*.mid`, `Wav/*.wav` | Music and effects |
| `TTSW10.Image21`, `Image33` | Embedded ending story and card |

The C++ GUI uses Data3 artwork at a 40-pixel logical tile size and loads the
installation's media directly. PNG extraction supports the Rust UI and asset
comparisons; the alternate Data artwork and display preferences belong to the
Delphi game.

Run extraction from the repository root:

```powershell
python -m pip install -r tools/requirements.txt
python tools/extract_original.py --source "D:/Program Files (x86)/Tower of the Sorcerer"
python cpp/tools/extract_ui.py --exe "D:/Program Files (x86)/Tower of the Sorcerer/TSW.exe"
```

`extract_original.py` preserves an existing editable Rust campaign unless
`--regenerate-campaign` is supplied. Source hashes are in
[extraction-manifest.json](../data/extraction-manifest.json); the form manifest
records bitmap hashes and reviewed offsets. Extracted media and executables
are excluded from Git. `extract_help.py` maintains Rust help from `TSW.txt` and
`Tsw.hlp`. Attribution and dependency licenses are in
[THIRD_PARTY.md](../THIRD_PARTY.md).

## Original saves

`Savedat/save1.dat` through `save8.dat` are little-endian records without a
header or serialized monster table. Writer entry: `0x47EADC`; loader: `0x47E7D4`.

| File offset | Bytes | Content |
|---|---:|---|
| `0` | 6,273 | 51 floor records |
| `6,273` | 684 | 171 signed 32-bit hero/state words |
| Total | **6,957** | Save record |

Hero byte offset 628 must be `-4`. Offsets 656 and 660 hold wrapping 32-bit
sums over the first 164 words: ordinary and alternating
`+word0 -word1 +word2 ...`. These checks exclude maps and the final hero words.
The C++ loader additionally validates mapped fields, tiles, and coordinate
bounds before replacing state, and preserves unmapped words when rewriting.
Trailing bytes are ignored, matching the fixed-size reads.

Loading rebuilds Zeno's shared HP/ATK/DEF row from cycle and seal flags:
unsealed `8000/5000/1000`; sealed `800/500/100 × (cycle_factor_minus_one + 1)`.
Combat applies cycle scaling again, preserving the backside load quirk.
Other monster rows come from constants.

The Fairy writes the same records to `Savedat/save0.dat` without updating
checksum words; recovery reads them without a checksum gate. The C++ checkpoint
is written after her scene finishes. F8 restores it with field and bounds
validation, while numbered slots require valid checksums. Slots use the
executable's `Savedat` directory or explicit `--save-dir`; see
[controls and saves](../cpp/README.md).

## Original MIDI playback

The Delphi game uses VCL MediaPlayer and Windows MCI (`mciSendCommandA`) for
MIDI; the executable contains no SoundFont. Playback depends on the selected
Windows MIDI device, as described in
[Microsoft's MIDI example](https://learn.microsoft.com/en-us/windows/win32/multimedia/playing-a-midi-file).
C++ synthesizes the same files with TinySoundFont and embedded GeneralUser GS.
Device instrument/controller differences are possible; audible equivalence
has not been established.
