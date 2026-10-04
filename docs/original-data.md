# Original data, extraction, and fidelity

The default campaign is derived from the user's installed English **Tower of the Sorcerer for Windows 1.2**, rather than a ten-floor remake. All **51 original floor records**, **33 enemy stat rows**, and **268 dialogue entries** were recovered. The original installation was read without modifying or launching it. The user's Cocos2d-x implementation was not read or copied during this extraction.

The installation's `Readme.txt` identifies Oz & Kenichi as the copyright holders, Shigemasa Ozawa as publisher, Borland Delphi 2.0J as the development environment, and April 28, 2000 as its last update. The executable used here is `TSW.exe`, with SHA-256:

```text
41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
```

## Reproduce the extraction

```powershell
python -m pip install -r tools/requirements.txt
python tools/extract_original.py --source "D:\Program Files (x86)\Tower of the Sorcerer"
```

`tools/extract_original.py` requires Python and Pillow. It extracts constants and converts bitmap assets; it does not run the old executable. An ordinary run refreshes the evidence and assets but preserves existing `data/campaign.json` and `data/interactions.json` so that campaign edits survive.

For explicit regeneration of the playable campaign from the extracted defaults:

```powershell
python tools/extract_original.py --regenerate-campaign
```

That flag replaces `data/campaign.json`, while retaining and merging the separately maintained `data/events.json` and `data/interactions.json`. The event reconstruction is a separate tool, `tools/extract_original_events.py`, whose dependencies and limitations are documented in [mechanics.md](mechanics.md). Run the browser build after changing the campaign, because the build copies the edited JSON to `web/campaign.json` and regenerates the WebAssembly package.

## Map evidence

`TTSW10.syokidata1` starts at virtual address `0x455CB8`. Its initializer lies in executable file range `[0x550B8, 0x5FFD8)` and writes to map base `0x4B8934`. The extractor recognizes these x86 constant-byte instructions:

```text
C6 00 imm8             mov byte [eax], imm8
C6 40 disp8 imm8       mov byte [eax + disp8], imm8
C6 80 disp32 imm8      mov byte [eax + disp32], imm8
```

It verifies that each offset from 0 through 6272 is assigned exactly once. Missing or repeated assignments stop extraction with an error. This yields 51 records of 123 bytes, including hidden floor 0 and floor 50.

Each record contains two landing indices followed by 121 row-major tile bytes. Landing index zero means the top-left tile; coordinates are `x = index % 11`, `y = index / 11`. The first header gives the hero's position after arriving upward from the previous floor, and the second after arriving downward from the next floor. These are preserved as `arrival_up` and `arrival_down` in the campaign. Normal stairs use explicit links from floor 43 to 45 and back, skipping hidden floor 44.

| Evidence file | Contents |
|---|---|
| `data/original-map-bytes.bin` | All 6273 initializer bytes, with both headers retained. |
| `data/original-maps.json` | The same maps as readable original tile IDs and landing indices. |
| `data/original-map-evidence.json` | One record per assignment: executable file offset, map byte offset, and value. |
| `data/campaign.json` | Editable rules, semantic tile definitions, maps, events, interactions, and enemy definitions. |

All map coordinates in JSON are zero-based. Tile IDs remain the original numeric values; floor tile arrays are `tiles[y * width + x]`.

## Enemy stats and identities

The original enemy table begins at file offset `0x88D10`, virtual address `0x489910`. Each of its 33 rows is four little-endian 32-bit unsigned integers: HP, attack, defense, and gold. `data/original-enemies.json` retains the extracted values alongside the verified identity.

Names were verified against `TTSW10.monname`, virtual address `0x44B6F4`, which selects dialogue entry `94 + monster_index`. In particular, row 15 is **Zeno** `(8000, 5000, 1000, 500)`, row 16 **Magic Sergeant** `(230, 450, 100, 100)`, row 17 **Vampire** `(444, 199, 66, 144)`, and row 26 **Great Magic Master** `(4500, 560, 310, 1000)`. These names and rows must not be interchanged with those of other remakes.

| Original tile IDs | Enemy table row |
|---|---|
| 61–96 | `(tile_id - 61) / 2`, integer division. |
| 97–105 | Giant Octopus, row 18. |
| 122 | Dragon, row 19. |
| 133–158 | `(tile_id - 93) / 2`, integer division. |

The remaining large-creature sprite cells, IDs 106–121 and 123–132, are occupied visual cells rather than separate dragon encounters. Their campaign definitions block walking and the engine clears the associated footprint when the large enemy is defeated. The `footprint` metadata gives its 3×3 bounds, the attacked cell's offset inside those bounds, and the original sprite IDs eligible for removal. This clears the dragon's visual body while keeping separate creatures on the same floor intact. Cross applies to Zombie, Zombie Knight, and Vampire; Dragon Slayer applies to Dragon. Normal combat and bomb eligibility are independently configured to preserve their distinct original behavior.

## Dialogue and NPCs

The strings come from the executable's binary Delphi form resource. The extractor locates the `Items.Strings` property after file offset `0x122B20`, reads both Delphi short-string and long-string forms, decodes the English data as Windows-1252, and verifies the resulting list has exactly 268 entries. `data/original-dialogue.json` stores each zero-based entry ID, text, and file offset.

The original event queue's opcode 10 dialogue operand is **one-based**. Its display routine decrements the value before accessing the string list. Direct old-man and merchant string lookups use their actual string indices; they do not share that extra decrement. Certain queued conversations append a second hint, while fairy queue IDs select a score overlay instead of a text string. The event converter records both `dialogue_id` and `original_queue_id` where applicable so that these distinctions remain inspectable.

`data/interactions.json` attaches an NPC definition to an individual floor and coordinate. It includes original old-man hints, the floor-2 3% attack/defense gift, the floor-3 Hero Orb gift, fixed-price merchants, the repeatable floor-28 yellow-key sale, the hidden floor-12 key merchant, the hidden floor-16 Elixir gift, staged fairies, and the ending thief. The gifts and one-use trades retain their NPC after use and hide their used choice. Merchant `after_text` displays the original clue after purchase.

The hidden NPCs are supported by direct `handan` evidence: tile 10 reveals a merchant at floor 12 `(10,0)`, an old man at floor 16 `(10,10)`, a Cross at floor 19 `(5,2)`, and a Magician A at floor 41 `(9,1)` after the opposite magician is defeated. Floor 12's right-hand merchant offers yellow keys for 1000 gold each repeatedly; its left-hand merchant offers one red key for 800 gold.

The floor-24 time gate and first-cycle completion are separate transitions. The princess-doll branch at `0x445397` unlocks the gate when the floor-25 boss cell is road. The gate queues travel to floor 50, dialogue, and a Zeno at `(5,4)`; it does not finish the game by itself. In `handan` at `0x4463A1`, touching Zeno on floor 50 in the initial cycle enters an ending animation sequence, followed by replay reset `(opcode 11, subcode 6)`, instead of ordinary combat. The Rust campaign records that first-cycle completion as `won`. The original automatic transition into the alternate replay cycle is outside the supported initial campaign; it must not be approximated by requiring an ordinary victory over Zeno's 8000/5000/1000 stat row.

## Artwork and audio

`Data3/Chtable.oz` is a Windows bitmap despite its extension. It supplies the higher-resolution 40-pixel sprite atlas: **440 × 800 pixels**, 11 columns, 220 cells. Atlas IDs are one-based; tile `n` has pixel origin `(((n-1) % 11) * 40, ((n-1) / 11) * 40)`. `Data3/Chtableb.oz` supplies the associated mask/background atlas. The extractor also converts the other `Data3` bitmaps and `Data2` ending images, and copies the installation's WAV and MIDI files.

The standing hero comes from atlas cells **185 down, 193 left, 201 right, and 209 up**, each followed by its silhouette mask. The generated `hero-*.png` images use the inverse mask as alpha, giving the browser a transparent hero. Cell 159 is a crossed-swords combat symbol and is not a hero sprite.

`web/assets/manifest.json` specifies the atlas, tile size, column count, tile rectangles, floor background rectangle, directional hero sources, animation frame coordinates, and credits. `data/extraction-manifest.json` lists every generated asset, its original source path, and source checksum where applicable. Audio assets are preserved for further presentation work; retaining them does not establish reproduction of the original sound or MIDI timing.

The original artwork, music, maps, and text remain credited to **Oz & Kenichi / Shigemasa Ozawa**. Their installed readme describes the game as freeware and sets conditions on distribution of the original archive. That is not a general open-source or permissive asset license. The Rust implementation and the extracted original content have separate provenance; retain the attribution and review the original terms before publishing a redistribution.

## What has been verified

The shared Rust engine is tested against both small rule fixtures and the imported original campaign. The original-campaign tests play the opening through actual moves and map-based pathfinding: collect a yellow key, open the floor-1 door, climb through floors 2 and 3, trigger the capture, verify exact `400 HP / 10 ATK / 10 DEF` with stolen equipment removed, acknowledge the thief, and walk through the escape tunnel. Scenario saves then exercise the two-guard prison-bar condition, repeatable key sales, the once-only old-man gift, both hidden NPC reveals and their trades/gifts, stair links that skip floor 44, the floor-39 three-o'clock puzzle, clearing a spawned fairy without granting stats, and removing the dragon's full body before collecting its Snow Crystal reward.

These tests establish their stated transitions, rather than an unassisted solution of all fifty floors. The full original map and enemy data are recovered; the event data is an authored translation of original writes, predicates, and queue instructions. Animation and waits are collapsed into deterministic ordered state changes. Native, browser, and MCP clients use that same engine.

Remaining fidelity boundaries include the original fairy score/rank calculations and checkpoint interface, the alternate replay/backside-tower cycle and its scaling, exact presentation/audio timing, and a complete unassisted end-to-end playthrough. Boss/event scenarios and a successful scripted ending test are useful evidence, but they do not prove every original sequence or optimal route. Further confirmed behavior can be added through JSON event rules without rewriting the UI.
