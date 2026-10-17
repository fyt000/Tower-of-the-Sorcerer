# Language catalogs

Select **Settings → Language** or pass `--language ID` for one launch.

| ID | Catalog | Source |
|---|---|---|
| `en` | `en-original.json` | English TSW 1.2 |
| `ja` | `ja.json` | Japanese MTW 1.6a |
| `en-ja` | `en-ja.json` | English from Japanese |
| `zh-Hans-ja` | `zh-Hans-ja.json` | Chinese from Japanese |
| `zh-Hans-en` | `zh-Hans-en.json` | Chinese from English |

Catalogs cover 268 dialogue entries, UI, items, monsters and story overlays.
Artwork/credits stay original. Localization affects presentation; state, saves,
replays, CLI and MCP retain canonical English. Chinese names follow TSWH5;
its gameplay and prose are not translation sources.

Desktop CJK fonts use installed Yu Gothic/MS Gothic or Microsoft YaHei. Override
with `TSW_CJK_FONT` pointing to a local TTF/OTF/TTC. Android also reads system fonts.
The [web build](../../docs/cross-platform.md#browser-fonts-and-settings) supplies
redistributable Noto Sans CJK subsets and loads the selected language on demand.

## Editing and alignment

Edit UTF-8 catalogs, then run:

```powershell
python cpp/tools/compile_locales.py
python cpp/tools/compile_locales.py --check
```

This regenerates tracked `cpp/src/localization_data.hpp`; checking needs no
extraction cache. Dialogue IDs are zero-based, queued speech IDs one-based,
continuation stages speech ID + 10; see [dialogue_ids.hpp](../include/tsw/dialogue_ids.hpp).

Japanese source IDs 0–262 align directly. C++ 263 contains Japanese 263's full
thief speech; 264 repeats its clue clause; C++ 265–267 map to Japanese 264–266.
Japanese 267 is empty. Preserve original wording differences, including purple
versus blue keys. New translations remain drafts; original text retains its
[authors' attribution](../THIRD_PARTY.md).

## Reproduce extraction and compilation

Local `source/` evidence is ignored. Extract the Japanese LHA with 7-Zip and
InstallShield payload with [idecomp](https://github.com/lephilousophe/idecomp):

```powershell
& 'C:/Program Files/7-Zip/7z.exe' x PATH/mtw16a.exe -obuild/localization/installer -y
# From build/localization; -O bypasses idecomp's CP932 filename-length assertion:
python -O PATH/idecomp.py -e cp932 installer/_SETUP.1 '*.exe' '*.txt' '*.cnt' '*.hlp' '*open2.bmp'
# From the repository root:
python cpp/tools/extract_japanese.py build/localization/Group1/Mtw.exe --html5 PATH/tswh5.zip --opening-bmp build/localization/Group10/Open2.bmp
```

The extractor validates the EXE hash and dialogue/form structure. Source JSON
retains CP932 bytes, offsets, documents and literal candidates; candidates are
not proof of displayed text. Opening/ending bitmap prose was transcribed and
visually checked. Optional WinHelp extraction uses [helpdeco](https://github.com/pmachapman/helpdeco)
RTF export (`/r /y`, Unix `-r -y`) and `--help-rtf PATH/MTW.rtf`.
The comparison TSV is generated under `build/reports/localization/`.
