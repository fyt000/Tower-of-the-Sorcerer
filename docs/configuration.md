# Campaign configuration

`data/campaign.json` is the editable game definition. The native executable embeds it at build time; the browser fetches `web/campaign.json`, copied by the build script. Browser menu → Load custom campaign accepts an independent JSON campaign. CLI `--campaign PATH` loads a file instead of the embedded default.

## Top-level contract

Required properties are `id`, `title`, `width`, `height`, `start`, `floors`, `tiles`, and `enemies`. Optional properties are `rules`, `events`, `interactions`, and `items`. Unknown metadata properties are preserved where useful. Dimensions must be 1–64, with 1–256 distinct floors. Each floor must contain exactly `width × height` numeric tile IDs; every used ID must exist in `tiles`. Player and enemy statistics are checked before a campaign or save is accepted.

`start` has `floor`, `x`, `y`, `hp`, `attack`, `defense`, `gold`, `keys: {yellow, blue, red}`, and `inventory: [item IDs]`. Optional `item_charges` is an object mapping item IDs to charge counts. Coordinates start at zero at the top left.

## Floors and tiles

Each floor is `{id, title, tiles, arrival_up?, arrival_down?}`. Tiles are row-major: `tiles[y * width + x]`. Stair arrival coordinates use `{x, y}`. `arrival_up` is where the hero lands after climbing into this floor; `arrival_down` is where the hero lands after descending into it.

Tile definitions use their numeric ID as an object key:

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

Supported kinds: `floor`/`empty`, `wall`, `hidden_wall`, `door`, `special_door`, `lava`, `decoration`, `enemy`, `key`, `potion`, `gem`, `stat`, `gold`, `equipment`, `item`, `stairs_up`, `stairs_down`, `npc`, `merchant`, `shop`, `altar`, `fairy`, `trigger`, and `win`. Unrecognized kinds block movement unless `passable` is true. `hidden_wall` becomes the configured empty tile when touched. `special_door` opens through events.

Doors and keys specify `key: "yellow" | "blue" | "red"`. Pickups specify `stat`, `amount`, optional `scaled`, and optional `item`. Item tiles specify an item ID. Stair tiles can specify `target_floor`. Extra `effects` are applied on collection/interaction. Equipment amounts are additive, as verified in the original executable.

Enemies define `{name, hp, attack, defense, gold, special?}`. Special values include `undead`, `dragon`, `magician_a`, `magician_b`, `sorcerer`, and `boss`. Numeric sprite rectangles are presentation data and do not affect the simulation.

A large enemy's encounter tile can define `footprint: {width, height, offset_x, offset_y, tiles}`. The offsets locate the encounter tile inside its rectangular body; `tiles` lists the occupied body IDs to clear after victory. For example, the original Dragon's encounter tile 122 uses a 3×3 footprint with offsets `(1,2)` and body IDs 115–132. This lets the engine clear the body before applying configured loot, without clearing unrelated creatures elsewhere on the floor.

## Rules

`empty_tile` must point to a defined tile. `area_scaling` is an ordered list of `{max_floor, multiplier}` controlling scaled pickups and altar ATK/DEF. Altar rules are `altar_base_cost`, `altar_hp_gain`, `altar_attack_gain`, and `altar_defense_gain`. The original cost formula is `base × (n² + n + 2)`, with one shared purchase count across altars.

`stair_links` maps `"floor:up"` or `"floor:down"` to a destination floor, such as `{"43:up":45,"45:down":43}`. `flying_requires_stairs` controls the Flying Orb's stair restriction. `bomb_tile_ranges` can specify inclusive numeric tile ranges eligible for destruction.

`hero_attacks_first` defaults to true. `cross_multiplier` and `dragon_slayer_multiplier` default to 2, and `base_attack_guard` defaults to true to preserve the original Cross/Dragon Slayer restriction. `magician_a_damage` and `magician_b_damage` default to 200 and 100. These are consumed by the shared Rust engine, so customized combat still matches across browser, CLI, and MCP.

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

Offers can have `cost_increment`, `conditions`, and `once`. A sale uses cost zero plus conditions verifying available keys and effects subtracting keys/adding gold. Altar offers are calculated from shared counters and rules by Rust. Ordinary dialog is acknowledged with choice `leave`; cancel dismisses it without applying acknowledgement effects.

## Events

An event includes `id`, `trigger`, optional `conditions`, ordered `effects`, and optional `once` (default true). Flags and counters persist in saves.

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

`source`, executable addresses, and untranslated instruction metadata are evidence fields, not commands. Review them when modifying original progression. After editing, run `tos validate --campaign data/campaign.json`, the Rust tests, then rebuild the browser package.

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

`rules.presentation.floor_transition_ms` defaults to 450 ms for stairs and
wings. Their presentation includes `style: "original_spiral"`, the direction,
and `sound: "kai"`. Scripted teleport effects can supply `transition` and
`duration_ms`; capture uses `"capture"`, while the floor-24 time gate uses
`"time_gate"` with a short span for each intermediate floor.
`rules.presentation.combat_strike_ms` defaults to 450 ms per actual strike
(the original High setting). Battle events expose `hit_sound`, `strike_ms`,
and sound/overlay/damage phases; their durations cover the complete alternating
turn count instead of compressing every long fight into six seconds.

The original campaign uses these additional cinematic fields:

- `magic`: `floor`, `x`, `y`, `frames` (dither-mask tile IDs), `color_tile`, and
  `underlying_tile`; an optional `targets` array applies a materialization to
  multiple original positions.
- `title`: `asset`, `target_asset`, mask `frames`, and optional `sound_cue` with
  `sound_offsets_ms`. Capture uses the original title-to-vortex sequence.
- `scan`: `asset`, `background_asset`, `text`, and `translation_key`. Capture
  reveals the original incantation over its vortex background.
- `transformation`: `floor`, center coordinates, `width`, `height`,
  `from_tiles`, target `tile`, and `original_frames`. Floor 20 retains the
  Vampire's nine-cell body and original 32 blend records.
- `tile_reveal`: `floor`, coordinates, `from_tile`, target `tile`, and
  `original_steps`. A following `set_tile` commits the same deterministic
  outcome for browser, native, headless, and MCP consumers.

`original_frames` and `original_steps` record extraction evidence; durations
remain explicit presentation settings. These fields do not change combat,
event conditions, rewards, or persisted game state.
