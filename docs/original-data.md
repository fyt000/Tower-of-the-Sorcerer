# Original game data

## Assets and extraction

The English 1.2 EXE supplies 51 floors, 33 monster rows and 268 text strings.
A floor is two stair-landing bytes followed by 121 row-major tile IDs.
See [research preparation](decompilation.md#prepare-data-and-decompilation).

| Input | Content |
|---|---|
| EXE map initializer | Maps and stair landings |
| EXE file offset `0x88D10` | Monster HP/attack/defense/gold |
| Delphi form string list | Dialogue and status text |
| `Data3/Chtable.oz`, `Chtableb.oz`, `*.bmp` | Sprites, masks and panels |
| `Data2/End*.bmp` | Ending frames |
| `Midi/`, `Wav/` | Music and effects |
| `TTSW10.Image21`, `Image33` | Embedded ending story/card |

C++ uses the original Data3 art at 40-pixel logical tiles; extracted PNGs go to
`build/assets/`. Alternate Data art/display settings belong to Delphi. Delphi
uses Windows MCI; C++ synthesizes MIDI with TinySoundFont/GeneralUser GS.
Original-media [attribution](../THIRD_PARTY.md) still applies.

## Original saves

Writer: `0x47EADC`; loader: `0x47E7D4`. Numbered slots are little-endian records:

| Offset | Bytes | Content |
|---|---:|---|
| 0 | 6,273 | 51 floor records |
| 6,273 | 684 | 171 signed 32-bit hero/state words |
| Total | **6,957** | No header or serialized monster table |

Within hero data, byte offset 628 must be `-4`. Offsets 656/660 contain wrapping
32-bit ordinary and alternating (`+word0 -word1 ...`) sums over the first 164
words. Maps and final words are excluded. Trailing bytes are ignored.

Loading reconstructs Zeno's base HP/ATK/DEF from flags: unsealed
`8000/5000/1000`; sealed `800/500/100 * cycle_factor`. Combat scales it again,
retaining the backside load quirk. Other monster rows come from constants.

The Fairy's `save0.dat` uses the same layout without refreshing/checking sums.
C++ writes it after her scene and validates field/tile bounds before restoring;
numbered slots additionally require valid checksums. C++ preserves unmapped
words when rewriting. [Save locations and companions](../cpp/README.md#saves-and-replay).

## Rankings

Five ten-entry tables correspond to 10F, 20F, 25F, 40F and 49F.
`option1.dat`–`option5.dat` are 288-byte numeric records; `option11.dat`–`option51.dat`
contain ten CRLF-separated names. C++ restores defaults on invalid input.
Rankings persist independently of game slots.

## Regenerate compiled data

`python cpp/tools/extract_constants.py ORIGINAL_TSW.exe` refreshes maps, monsters
and text. The build uses `cpp/tools/extract_ui.py` for ending pictures and
save/load menu resources. Help extraction uses `tools/extract_help.py`;
[localization](../cpp/locales/README.md) has Japanese extraction commands.
