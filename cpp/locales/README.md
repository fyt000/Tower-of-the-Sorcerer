# C++ language catalogs

Settings → Language selects five languages; the preference is saved in
`Savedat/settings.json`. `--language` overrides it for one launch:

| ID | Catalog | Source |
|---|---|---|
| `en` | `en-original.json` | Existing English TSW 1.2, unchanged |
| `ja` | `ja.json` | Extracted Japanese MTW 1.6a, with explicit ID alignment |
| `en-ja` | `en-ja.json` | English translated directly from Japanese |
| `zh-Hans-ja` | `zh-Hans-ja.json` | Simplified Chinese translated directly from Japanese |
| `zh-Hans-en` | `zh-Hans-en.json` | Simplified Chinese translated from current English |

```powershell
./build/cpp/vs/Release/tsw_game.exe --language ja
./build/cpp/vs/Release/tsw_game.exe --language en-ja
./build/cpp/vs/Release/tsw_game.exe --language zh-Hans-ja
./build/cpp/vs/Release/tsw_game.exe --language zh-Hans-en
```

Every catalog contains all 268 dialogue-table entries, including intentional empty
entries and status fragments, plus C++ UI strings, 15 item names and descriptions,
33 monster names, the opening passage and the ending story. Modern C++ controls and help text are
translated as interface copy; they are not claimed to be original Japanese text.
Text-bearing HUD labels, the opening passage and the ending story receive translated overlays.
Decorative title artwork, final-card artwork and credits remain original.

Localization is applied at presentation time. Game state, commands, save formats,
replay hashes, recorded speech, CLI and MCP observations keep canonical English.
Switching language works during a conversation or replay. No Rust source or Rust
translation catalog is used. Unknown diagnostics retain their original text;
user-entered ranking names and replay paths bypass translation.

Recovered text-table indices are zero-based; queued `Op::Dialogue` speech IDs
are one-based, and their continuation stages add 10. Named entries and range
offsets in `src/dialogue_ids.hpp` document the IDs used for dynamic dialogue,
Wisdom Orb hints, merchant offers and status messages.

The Fairy assembles score evaluations from entries 220–236 and leaderboard
announcements from 244–245. `src/fairy_dialogue.hpp` names each fragment and
preserves the recovered score thresholds. Composition normalizes padding at
word/sentence joins: the two English catalogs use a single space, while Japanese
and Chinese join directly. Numeric suffixes retain their catalog punctuation and
spacing (for example, ` points.`, `. I'll record...` or `点です。`). The recovered
catalogs themselves remain unchanged.

Japanese glyphs come from Windows Yu Gothic (fallback: MS Gothic), and Chinese
glyphs from Microsoft YaHei. The first face of a `.ttc` collection is adapted in
memory for raylib; font files are not modified or redistributed. For portable
builds, set `TSW_CJK_FONT` to a local `.ttf`, `.otf` or `.ttc` font covering both
languages. The renderer loads the catalog's Unicode glyphs and wraps unspaced CJK
text at UTF-8 boundaries.

## Sources and alignment

`source/japanese-source.json` retains the 268 original entries, their file offsets
and exact CP932 bytes, and 221 text properties from the binary Delphi forms.
It also preserves 129 structurally valid Japanese Delphi AnsiString literal
candidates, including item names and runtime prompts; this is extraction evidence,
not a claim that every candidate is displayed during play.
`source/japanese-documents.json` contains five supplied `.txt`/`.cnt` documents
decoded from CP932. The ending prose is manually transcribed and visually checked
from Image21's 640 × 400 bitmap; it is identified separately from extracted strings.
`source/japanese-help.json` extracts 48 nonempty visible topics from MTW.HLP using
[helpdeco](https://github.com/pmachapman/helpdeco)'s RTF export, then decodes CP932
byte runs. It omits embedded pictures, hotspots and hidden macros. The opening
passage is manually transcribed and visually checked from `Group10/Open2.bmp`,
with its bitmap hash retained in `japanese-source.json`. The supplied
manuals and WinHelp prose are source references, not additional translated manuals.

The outer archive identifies itself as **魔法の塔 for Windows Ver1.6a**, by
**Oz & Kenichi**. SHA-256:
`dd1e03d87453eb14fd0175a2ac80ef8a9095090e7f4d72c3d40b8b82c354beba`.
The unpacked `Mtw.exe` SHA-256 is
`9985d47483504489993c8db1fb7c088ccec69499843aafb5ae2a87423aa86cf9`.
The README lists an April 2000 package. Its version number should not be treated
as the same release sequence as the English TSW 1.2 installation.

IDs 0–262 correspond directly. English splits the final Japanese thief speech:

| C++/English ID | Japanese source ID | Mapping |
|---|---|---|
| 263 | 263 | Complete thief speech, including the floor-25/time-gate clue |
| 264 | 263 | Clue clause alone, for the English continuation entry |
| 265 | 264 | Cannot load this data |
| 266 | 265 | Magician A, 8,800 HP damage |
| 267 | 266 | Magician B, 4,400 HP damage |

Japanese source ID 267 is empty and remains in the source extraction. The
Japanese-based catalogs show the full clue at C++ ID 263 because the existing
floor-50 interaction displays that entry. Conversations 4, 16 and 54 have final
paragraphs at 57, 58 and 59; the C++ concatenation order is preserved.

Japanese calls the current blue-key category **purple**. Japanese-based dialogue
preserves that description; Chinese from English uses **blue**. Japanese says Zeno
will **absorb the hero's power**, while English proposes **working together**.
The Japanese staff is **omnipotent**; English calls it **omniscient**. These
differences remain in the respective translations. ウェポナー and インテリオン keep
the established English spellings Weaponer and Intellion; Chinese transliterates
them as 威波纳 and 因特里昂. Japanese slime abbreviations remain verbatim in Japanese;
expanded English names use established monster identities. NPC advice is
translated as written, including claims that differ from the C++ mechanics;
the C++ item descriptions explain actual C++ behavior.

## Chinese terminology

`source/html5-terminology.json` retains the name fields from `tswh5.zip`'s
`TSWH5/project/items.js` and `TSWH5/project/enemys.js`, with the archive hash.
Both Chinese catalogs use these names. Examples:

| C++ name | TSWH5 name | TSWH5 key |
|---|---|---|
| Orb of the Hero | 勇者灵球 | `book` |
| Orb of Wisdom | 智慧灵球 | `notebook` |
| Elixir | 圣水 | `superPotion` |
| Mattock | 破墙镐 | `pickaxe` |
| Bomb | 破坏爆弹 | `bomb` |
| Warp Staff | 瞬移之翼 | `centerFly` |
| Ascent Wing | 升华之翼 | `upFly` |
| Descent Wing | 降临之翼 | `downFly` |
| Dragon Slayer | 屠龙匕首 | `dagger` |
| Super Mattock | 鹤嘴锄 | `earthquake` |
| Zeno | 魔导师泽诺 | `redKing` |
| Zombie Knight | 丧尸武士 | `zombieKnight` |
| Great Magic Master | 大魔导师 | `magicMaster` |

Only terminology is taken from HTML5. Its gameplay changes and prose do not
replace either requested translation source.

## Reproduce extraction and compilation

The download is LHA containing an InstallShield 3 `_SETUP.1`. It was unpacked
without running the installer or original game. Use 7-Zip for the outer layer and
[idecomp](https://github.com/lephilousophe/idecomp) for the inner layer, in a private
build directory. Idecomp's name-length assertion confuses CP932 bytes with
character count; `-O` bypasses that assertion. Our text extractor then validates
the executable hash, Delphi resource structure and complete dialogue table.

```powershell
& 'C:/Program Files/7-Zip/7z.exe' x D:/Downloads/mtw16a.exe -obuild/localization/installer -y
# In build/localization, with idecomp outside shipped source:
python -O PATH/idecomp.py -e cp932 installer/_SETUP.1 '*.exe' '*.txt' '*.cnt' '*.hlp' '*open2.bmp'
# Back at the repository root:
python cpp/tools/extract_japanese.py build/localization/Group1/Mtw.exe --html5 D:/Downloads/tswh5.zip --opening-bmp build/localization/Group10/Open2.bmp
python cpp/tools/compile_locales.py
python cpp/tools/compile_locales.py --check
```

To include WinHelp prose, export `MTW.HLP` with helpdeco `/r /y` from a private
directory, then add `--help-rtf PATH/MTW.rtf` to the extraction command. Unix builds
of helpdeco use `-r -y`. The Windows helper was built with its supplied VS2026
project; it stays under `build/localization/` and is not a game dependency.

Edit UTF-8 JSON catalogs, then regenerate `cpp/src/localization_data.hpp`.
Checked-in compiled data makes releases self-contained and headless builds
independent of Python. The generator checks the baseline against the C++ original
constants and rejects missing dialogue or UI keys. `dialogue-comparison.tsv` gives
a side-by-side view of all five text sets.

Original text and documents remain attributable to Oz & Kenichi and the original
authors; they are not relicensed under the remake's MIT license. HTML5 names are
retained as provenance. The new translations are drafts for review, with source
text alongside them. This change bundles no original executable, installer,
font, audio or HTML5 implementation.
