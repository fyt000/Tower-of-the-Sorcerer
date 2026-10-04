# Campaign configuration

`data/campaign.json` is the editable game definition. Browser and native executables embed it at build time and can load an independent campaign through Settings → Import, a dropped JSON file, or the campaign editor. Imported campaigns persist in browser or native storage. CLI `--campaign PATH` loads a file instead of the embedded default.

## Top-level contract

Required properties are `id`, `title`, `width`, `height`, `start`, `floors`, `tiles`, and `enemies`. Optional properties are `rules`, `events`, `interactions`, and `items`. Unknown metadata properties are preserved where useful. Dimensions must be 1–64, with 1–256 distinct floors. Each floor must contain exactly `width × height` numeric tile IDs; every used ID must exist in `tiles`. Player and enemy statistics are checked before a campaign or save is accepted.

`start` has `floor`, `x`, `y`, `hp`, `attack`, `defense`, `gold`, `keys: {yellow, blue, red}`, and `inventory: [item IDs]`. Optional `item_charges` is an object mapping item IDs to charge counts. Coordinates start at zero at the top left.

Both `Engine::from_json` and the Rust constructor `Engine::new(Campaign)` validate the complete campaign before creating a session. JSON imports first decode the typed fields, then check geometry, references, rules, offers and scripts. Events, conditions and effects are compiled into Rust enums once; gameplay dispatches those enums. Browser, native, CLI and MCP use this same boundary.

Omitting a field with a documented default uses that default. Supplying a malformed value fails validation: `"hero_attacks_first": "false"` is a string and cannot become the Boolean default `true`; `"conditions": {}` cannot become an empty condition list. Integer fields require JSON integers, Boolean fields require `true` or `false`, and lists require arrays. Nullable optional references such as `target_floor` can use `null` to mean absent. Omitted `rules` is represented internally as `null`; supplied known properties inside a rules object must have their documented types.

Campaign IDs, item IDs and flag names must contain non-whitespace characters. Player statistics and key counts are between zero and 1,000,000,000; enemy HP is between one and that limit. These numerical and map-size limits bound imported simulation data and allocations. They are named constants in Rust, rather than statistics recovered from the original game.

## Floors and tiles

Each floor is `{id, title, tiles, arrival_up?, arrival_down?}`. Tiles are row-major: `tiles[y * width + x]`. Stair arrival coordinates use `{x, y}`. `arrival_up` is where the hero lands after climbing into this floor; `arrival_down` is where the hero lands after descending into it.

Tile definitions use their numeric ID as an object key. IDs must use canonical decimal spelling between `0` and `65535`; `"6"` is valid and `"06"` is rejected because map cells look up the canonical ID:

```json
{
  "34": {
    "name": "Red crystal",
    "kind": "gem",
    "stat": "attack",
    "amount": 1,
    "scaled": true,
    "sprite": { "x": 0, "y": 120, "w": 40, "h": 40 }
  },
  "61": {
    "name": "Green Slime",
    "kind": "enemy",
    "enemy": "green_slime",
    "sprite": { "x": 200, "y": 200, "w": 40, "h": 40 }
  }
}
```

Supported kinds: `floor`/`empty`, `wall`/`solid`, `barrier`, `hidden_wall`, `door`, `special_door`, `lava`, `decoration`, `enemy`/`monster`, `key`, `potion`, `gem`, `stat`, `gold`, `equipment`, `item`, `stairs_up`, `stairs_down`, `stairs`, `npc`, `merchant`, `shop`, `altar`, `fairy`, `trigger`, and `win`. These spellings decode to the closed Rust `TileKind` enum; an unrecognized kind is an import error. `hidden_wall` becomes the configured empty tile when touched. `special_door` opens through events. Generic `stairs` can specify `direction: "up" | "down"`.

Doors and keys specify `key: "yellow" | "blue" | "red"`, represented by `KeyColor` in Rust. Pickups specify `stat`, `amount`, optional Boolean `scaled`, and optional `item`. `Stat` accepts `hp`, `attack`, `defense`, `gold`, `yellow`, `blue`, or `red`; unknown stat/key names fail decoding. Item tiles specify an item ID. Stair tiles can specify `target_floor`, which must exist. Enemy tiles require an `enemy` ID resolving to an enemy definition. Extra `effects` are applied on collection/interaction. Equipment amounts are additive, as verified in the original executable.

Enemies define `{name, hp, attack, defense, gold, special?}`. `EnemySpecial` accepts the ordinary empty string `""` (also the default when omitted), `undead`, `dragon`, `magician_a`, `magician_b`, `sorcerer`, or `boss`. Unknown special names fail decoding. Sprites can use a numeric atlas-cell ID or `{x,y,w,h}` pixel rectangles. Supplied rectangle values must be numbers, with nonnegative coordinates and positive sizes; these are presentation data and do not alter combat.

A large enemy's encounter tile can define `footprint: {width, height, offset_x, offset_y, tiles}`. The offsets locate the encounter tile inside its rectangular body; `tiles` lists the occupied body IDs to clear after victory. For example, the original Dragon's encounter tile 122 uses a 3×3 footprint with offsets `(1,2)` and body IDs 115–132. This lets the engine clear the body before applying configured loot, without clearing unrelated creatures elsewhere on the floor.

## Rules

`empty_tile` must point to a defined ordinary passage tile of kind `empty`, `floor`, or `decoration` (its omitted default is ID zero). Clearing creatures, doors, pickups and lava replaces them with this tile. An enemy, door or lava replacement is rejected; replacing cleared lava with lava would prevent the Snow Crystal's flood fill from terminating. `area_scaling` is an ordered list of `{max_floor, multiplier}` controlling scaled pickups and altar ATK/DEF. Its integer thresholds must increase, and multipliers must be between 1 and 1000. Altar rules are `altar_base_cost`, `altar_hp_gain`, `altar_attack_gain`, and `altar_defense_gain`. These integer costs/gains are between zero and 1,000,000,000. The original cost formula is `base × (n² + n + 2)`, with one shared purchase count across altars.

`stair_links` maps `"floor:up"` or `"floor:down"` to an integer destination floor, such as `{"43:up":45,"45:down":43}`. Both source and destination floors must exist. `flying_requires_stairs` controls the Flying Orb's stair restriction. `bomb_tile_ranges` can specify inclusive numeric tile ranges eligible for destruction; each entry must be `[minimum, maximum]` with valid tile-ID integers and `minimum <= maximum`.

`hero_attacks_first` defaults to true. `cross_multiplier` and `dragon_slayer_multiplier` default to 2 and accept integers between 1 and 1000. `base_attack_guard` defaults to true to preserve the original Cross/Dragon Slayer restriction. `magician_a_damage` and `magician_b_damage` default to 200 and 100; configured damage is an integer between zero and 1,000,000,000. These are consumed by the shared Rust engine, so customized combat still matches across browser, CLI, and MCP.

The event engine is shared across browser, CLI, and MCP. Rules which describe presentation convenience or original evidence but are not consumed by the engine are metadata; do not assume that adding an arbitrary rule key changes behavior.

## NPCs and offers

Tile definitions can include `text`, `description`, `offers`, `effects`, and `disappear`. Use `interactions` to override a particular NPC instance by position; this avoids changing every merchant that shares one original sprite.

```json
{
  "floor": 6,
  "x": 5,
  "y": 5,
  "name": "Key merchant",
  "text": "A key may open the path you need.",
  "offers": [
    {
      "id": "buy_blue",
      "label": "Buy a blue key",
      "cost": 50,
      "once": true,
      "effects": [{"type":"add_stat","stat":"blue","amount":1}]
    }
  ]
}
```

Offers require an `effects` array, which can be empty, and can have `cost_increment`, `conditions`, and Boolean `once`. Costs and increments are integers between zero and 1,000,000,000. A sale uses cost zero plus conditions verifying available keys and effects subtracting keys/adding gold. Altar offers are calculated from shared counters and rules by Rust. Ordinary dialog is acknowledged with choice `leave`; cancel dismisses it without applying acknowledgement effects. Offer IDs must be unique within a conversation and cannot be `leave`; omitted IDs use their zero-based array index. Explicit stable IDs are preferable when a campaign will evolve.

Interaction locations must be unique. Validation merges each location override into its underlying tile definition and checks the result, including its kind, field types, references, effects and offers. A malformed override fails import instead of quietly restoring the unmodified NPC.

Item IDs are resource names and inventory tags. They can represent built-in tools, configured custom items or passive story rewards such as `custom_badge`; every tag need not have an entry in `items`. Configured custom actions use an object such as `"items": {"healing_scroll": {"consumable": true, "effects": [{"type":"add_stat","stat":"hp","amount":100}]}}`. Supplied `consumable` must be a Boolean and `effects` must be an array of validated effects.

## Events

An event includes optional `id`, `trigger`, optional `conditions`, required ordered `effects`, and optional Boolean `once` (default true). Flags and counters persist in saves. Event IDs must be unique; omitted IDs use their zero-based array index, so an explicit ID must not collide with another event's generated index either.

```json
{
  "id": "open_guarded_gate",
  "trigger": {"type":"enemy_defeated","floor":8},
  "conditions": [
    {"type":"tile","floor":8,"x":8,"y":4,"tile":6},
    {"type":"tile","floor":8,"x":10,"y":4,"tile":6}
  ],
  "effects": [
    {"type":"set_tile","floor":8,"x":9,"y":4,"tile":6},
    {"type":"message","text":"The guarded gate opens."}
  ]
}
```

Triggers: `step`, `bump`, `door_opened`, `enter_floor`, `enemy_defeated`, and `interact`. Optional `floor`, `x`, `y`, and `tile` restrict the trigger. `bump` runs at the intended destination before collision handling, enabling scripted walls and concealed encounters. `door_opened` runs after a colored door consumes its key. `interact` occurs when the player acknowledges an NPC conversation. Events run in file order; an event is marked as executed before its effects, preventing recursive forced battles from repeating it.

Conditions are ANDed. Supported conditions are `flag` (with optional Boolean `value`, default true), `has_item`, `tile`, `no_enemies`, `stat_at_least` and `stat_at_most` (with `stat` and `amount`), `cycle_at_least` and `cycle_at_most` (with `amount`), and `any` (with an array of alternative `conditions`). A condition must match before the event's counter changes. Individual effects can also have a `conditions` array; this is used to preserve combat stats during the backside capture. Offers whose conditions fail are omitted; direct attempts to purchase them also fail. Purchased merchants can provide a different clue through `after_text: {flag, text}`.

Trigger and condition objects have closed schemas: unknown fields are errors. Nested `any` conditions receive the same recursive type, coordinate and reference validation as top-level conditions. Cycle conditions accept `cycle` or its legacy alias `amount`, between 1 and 1000. Omitted condition lists mean no restrictions; supplied lists must be arrays, including at every nested level.

Effects:

| Type | Properties |
| --- | --- |
| `message` | `text`, optional zero-based `dialogue_id` for original dialogue evidence |
| `flag` | `flag`, optional Boolean `value` |
| `set_tile` | `floor`, `x`, `y`, `tile` |
| `add_stat` / `set_stat` | `stat`, `amount` |
| `multiply_stat` | `stat`, integer `numerator`, integer `denominator` |
| `give_item` / `remove_item` | `item` |
| `clear_inventory` | No extra properties |
| `set_charges` | `item`, `charges` |
| `set_visited` | `floors` array |
| `teleport` | `floor`, `x`, `y` |
| `set_enemy` | `enemy`, any of `hp`, `attack`, `defense`, `gold` |
| `battle_at` | `floor`, `x`, `y`, optional Boolean `first_strike` |
| `win` | No extra properties |
| `next_cycle` | Reset maps, flags, shops and keys using `rules.backside`; preserve combat stats when configured |
| `wait` | `ms`, presentation only |
| `sound` | `cue`, extracted WAV basename, `music-start` / `music-stop`, or `music:ID` mapped by `rules.audio.music_cues` |
| `cinematic` | `kind`, `duration_ms`, optional original instruction metadata |
| `move_tile` | `floor`, `from_x`, `from_y`, `x`, `y`, optional `tile`, `duration_ms`: move one original sprite cell |

Statistics are `hp`, `attack`, `defense`, `gold`, `yellow`, `blue`, and `red`. Forced battles can give the enemy an initial attack, matching original ambush sequences. Runtime enemy changes are session state and survive save/load. Any failed campaign validation reports an error before replacing a running browser session.

State-changing effect objects have closed operation fields, so misspellings such as `condition` or `vale` are rejected. `source` and `original_queue_id` remain accepted provenance fields. Numeric effect amounts are checked against the simulation bounds; multiply denominators must be positive, floor/tile/enemy references must exist, and positions must lie inside the map. A missing effect `floor` means the hero's current floor. A forced battle requires explicit `x` and `y` coordinates.

Campaign metadata, extra tile properties, rule metadata, event/offer metadata and cinematic payloads remain extensible and survive editor round trips. Metadata does not add simulation behavior: new gameplay operations require a corresponding Rust enum variant and implementation. Cinematics describe renderer behavior and can use additional presentation fields, while known fields such as durations, positions and frame arrays are still checked. `source`, executable addresses, and untranslated instruction metadata are evidence fields. Review them when modifying original progression.

Validation errors identify the relevant boundary or field. Examples of rejected input include:

| Malformed value | Reported boundary or reason |
| --- | --- |
| `"hero_attacks_first": "false"` | `rules.hero_attacks_first`: expected a Boolean |
| `"conditions": {}` in an event | `events[0]`: expected a condition array |
| `{"type":"set_tile","x":0,"y":0,"tile":999}` when tile 999 is undefined | `events[0].effects[0].tile`: undefined tile |
| `"kind": "enmey"` | Unknown `TileKind` variant during JSON decoding |
| An interaction with `"name": 42` | `interactions[0]`: merged tile cannot decode its string name |
| Two offers with ID `buy_blue` | Duplicate offer ID; the second cannot silently shadow the first |

After editing, run `tos validate --campaign data/campaign.json`, the Rust tests, then rebuild the browser package. Rust callers also receive constructor errors when they assemble an invalid `Campaign` directly.

## Visual editing and localization

Open **Campaign editor** in the browser/native interface, or launch the native
executable with `--editor` (`npm run editor`). The editor works on a draft; play
and export validate the entire campaign before replacing a session or creating
JSON. It includes a floor canvas and tile palette, floor metadata/arrivals,
enemy statistics, starting player settings, tile/item definitions, shops,
interactions and event forms. Undo restores prior edits. Advanced fields remain
available for custom rules without requiring raw JSON for ordinary map/enemy work.

The browser imports a campaign into browser storage. **Export campaign** downloads
a JSON file; to make it the project's default, save it as `data/campaign.json`
and rebuild. Native export writes the selected campaign JSON to the working
directory. Each campaign revision has a different save fingerprint.

English and Simplified Chinese dictionaries live under `data/locales/` and are
compiled into the shared UI. They translate UI labels, original entity names and
original dialogue. Unknown custom-campaign prose falls back to its authored text.
Add dictionary keys/translations to support another locale. The Chinese font is
installed locally by `python tools/setup_assets.py --font-only`.

`rules.forecast_requires_item` is `hero_orb` for the original campaign. Omit it
to provide unrestricted forecasts in a custom campaign. The engine applies this
gate to both `inspect` and the snapshot enemy list; the detailed view is unlocked
by accepting the floor-3 old man's gift.

The original backside configuration is:

```json
"backside": {
  "enabled": true,
  "multiplier": 44,
  "carry_stats": true,
  "reset_gold": true,
  "capture_preserves_stats": true
}
```

Monster HP/ATK/DEF, treasure combat-stat gains, altar gains and flat magic-field
damage scale; enemy gold and altar prices do not. Maps and event/altar counters
reset on completion. The first replay resets gold; later replays preserve gold
and carried special items until the next capture. The multiplier stays 44 for
later cycles. The original campaign's conditional capture effects enforce its
stat-preservation rule; custom capture effects should use the same cycle guards.
`capture_preserves_stats` records the original intent as metadata; changing that
key alone does not alter capture. Edit the per-effect cycle conditions to create
a different capture rule.

`rules.audio.floor_music` is an ordered list of `{min_floor, max_floor, file}`
where `file` is an extracted MIDI basename without `.mid`.
`rules.audio.music_cues` maps original scene music IDs to those basenames.
Presentation effects can customize `wait.ms`, `cinematic.duration_ms`, and
`move_tile.duration_ms`. The GUI's animation speed setting scales the timeline;
the durations approximate the original timer-driven scenes.

`rules.presentation.ambient_frame_ms` defaults to 150 ms and accepts integer values from 60–1000 ms.
It controls stationary enemy/NPC pose swaps and the hero's walking cadence and
brief return-to-idle delay. Custom sprite rectangles retain their authored art.

`rules.presentation.floor_transition_ms` defaults to 450 ms for stairs and
wings. Their presentation includes `style: "original_spiral"`, the direction,
and `sound: "kai"`. Scripted teleport effects can supply `transition` and
`duration_ms`; capture uses `"capture"`, while the floor-24 time gate uses
`"time_gate"` with a short span for each intermediate floor.
`rules.presentation.combat_strike_ms` defaults to 450 ms per actual strike
(the original High setting). Battle events expose `hit_sound`, `strike_ms`,
and sound/overlay/damage phases; their durations cover the complete alternating
turn count instead of compressing every long fight into six seconds.

Configured floor transitions accept 30–10,000 ms and combat strikes accept
60–3000 ms. These match the renderer's protective ranges; imports outside the
ranges now fail instead of depending on runtime clamping. Explicit script waits,
dialogue holds and cinematic/move durations are bounded to 30,000 ms.

The original campaign uses these additional cinematic fields:

- `magic`: `floor`, `x`, `y`, `frames` (dither-mask tile IDs), `color_tile`, and
  `underlying_tile`; an optional `targets` array applies a materialization to
  multiple original positions, swept in array order for each mask frame.
- `title`: `asset`, `target_asset`, mask `frames`, and optional `sound_cue` with
  `sound_offsets_ms`. Capture uses the original title-to-vortex sequence.
- `scan`: `asset`, `background_asset`, `text`, and `translation_key`. Capture
  reveals the original incantation over its vortex background.
- `transformation`: `floor`, center coordinates, `width`, `height`,
  `from_tiles`, target `tile`, and `original_frames`. Floor 20 retains the
  Vampire's nine-cell body and original 32 bat-convergence frames. The extracted
  background atlas supplies transparent masks while the bats move.
- `tile_reveal`: `floor`, coordinates, `from_tile`, target `tile`, and
  `original_steps`. A following `set_tile` commits the same deterministic
  outcome for browser, native, headless, and MCP consumers.

`original_frames` and `original_steps` record extraction evidence; durations
remain explicit presentation settings. These fields do not change combat,
event conditions, rewards, or persisted game state.
