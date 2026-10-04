//! Authored campaign data and validation at the content boundary.
use super::domain::{EnemySpecial, KeyColor, Stat, TileKind};
use serde::{Deserialize, Serialize};
use serde_json::Value;
use std::collections::{BTreeMap, BTreeSet};

#[derive(Clone, Debug, Default, Serialize, Deserialize, PartialEq)]
pub struct Keys {
    pub yellow: i64,
    pub blue: i64,
    pub red: i64,
}

#[derive(Clone, Debug, Default, Serialize, Deserialize, PartialEq)]
pub struct Player {
    pub floor: i32,
    pub x: usize,
    pub y: usize,
    pub hp: i64,
    pub attack: i64,
    pub defense: i64,
    #[serde(default)]
    pub gold: i64,
    #[serde(default)]
    pub keys: Keys,
    #[serde(default, alias = "items")]
    pub inventory: Vec<String>,
    #[serde(default)]
    pub item_charges: BTreeMap<String, u32>,
    /// Displayed equipment changes on every pickup. Its stat bonus has already
    /// been added to attack/defense; replacing a slot never subtracts a bonus.
    #[serde(default)]
    pub weapon: Option<String>,
    #[serde(default)]
    pub shield: Option<String>,
}

impl Player {
    /// Keep collected tags for scripts and persistent abilities, separately
    /// from the most recently collected weapon and shield displayed to players.
    pub(crate) fn grant_item(&mut self, item: &str, campaign: &Campaign) {
        match campaign.equipment_stat(item) {
            Some(Stat::Attack) => self.weapon = Some(item.to_owned()),
            Some(Stat::Defense) => self.shield = Some(item.to_owned()),
            _ => (),
        }
        if !self.inventory.iter().any(|owned| owned == item) {
            self.inventory.push(item.to_owned());
        }
    }

    pub(crate) fn remove_item(&mut self, item: &str) {
        self.inventory.retain(|owned| owned != item);
        if self.weapon.as_deref() == Some(item) {
            self.weapon = None;
        }
        if self.shield.as_deref() == Some(item) {
            self.shield = None;
        }
    }

    pub(crate) fn clear_inventory(&mut self) {
        self.inventory.clear();
        self.item_charges.clear();
        self.weapon = None;
        self.shield = None;
    }

    pub(crate) fn infer_equipment(&mut self, campaign: &Campaign, weapon: bool, shield: bool) {
        // Old saves stored each equipment ID only once. Their exact last pickup
        // cannot be recovered after recollection, so use the last retained tag.
        for item in &self.inventory {
            match campaign.equipment_stat(item) {
                Some(Stat::Attack) if weapon => self.weapon = Some(item.clone()),
                Some(Stat::Defense) if shield => self.shield = Some(item.clone()),
                _ => (),
            }
        }
    }
}

#[derive(Clone, Debug, Default, Serialize, Deserialize)]
pub struct TileDef {
    pub name: String,
    pub kind: TileKind,
    #[serde(default)]
    pub description: String,
    #[serde(default)]
    pub enemy: Option<String>,
    /// Divide raw encounter gold before item multipliers; omitted means 1.
    #[serde(
        default,
        deserialize_with = "deserialize_reward_divisor",
        skip_serializing_if = "default_reward_divisor"
    )]
    pub reward_divisor: Option<i64>,
    #[serde(default)]
    pub key: Option<KeyColor>,
    #[serde(default)]
    pub amount: i64,
    #[serde(default)]
    pub stat: Option<Stat>,
    #[serde(default)]
    pub item: Option<String>,
    #[serde(default)]
    pub target_floor: Option<i32>,
    #[serde(default)]
    pub sprite: Value,
    #[serde(default)]
    pub offers: Vec<Value>,
    #[serde(default)]
    pub effects: Vec<Value>,
    #[serde(default)]
    pub text: String,
    #[serde(default)]
    pub passable: bool,
    #[serde(flatten)]
    pub extra: BTreeMap<String, Value>,
}

fn default_reward_divisor(value: &Option<i64>) -> bool {
    value.is_none_or(|divisor| divisor == 1)
}

fn deserialize_reward_divisor<'de, D>(deserializer: D) -> Result<Option<i64>, D::Error>
where
    D: serde::Deserializer<'de>,
{
    i64::deserialize(deserializer).map(Some)
}

#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct Enemy {
    pub name: String,
    pub hp: i64,
    pub attack: i64,
    pub defense: i64,
    pub gold: i64,
    #[serde(default)]
    pub special: EnemySpecial,
}

#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct Floor {
    pub id: i32,
    #[serde(default)]
    pub title: String,
    pub tiles: Vec<u16>,
    #[serde(default)]
    pub arrival_up: Option<Position>,
    #[serde(default)]
    pub arrival_down: Option<Position>,
}

#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct Position {
    pub x: usize,
    pub y: usize,
}

#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct Campaign {
    pub id: String,
    pub title: String,
    pub width: usize,
    pub height: usize,
    pub start: Player,
    pub floors: Vec<Floor>,
    pub tiles: BTreeMap<String, TileDef>,
    pub enemies: BTreeMap<String, Enemy>,
    #[serde(default)]
    pub rules: Value,
    #[serde(default)]
    pub events: Vec<Value>,
    #[serde(default)]
    pub items: BTreeMap<String, Value>,
    #[serde(default)]
    pub interactions: Vec<Value>,
    #[serde(flatten)]
    pub metadata: BTreeMap<String, Value>,
}

/// A simulation/save envelope, not a statistic from the original game.
/// Bounded inputs keep subsequent saturating arithmetic and forecasts useful.
pub(crate) const MAX_STAT: i64 = 1_000_000_000;
/// Editor/import limits bound map allocations; the original is 11 × 11 × 51.
const MAX_MAP_SIDE: usize = 64;
const MAX_FLOORS: usize = 256;
/// Combat and backside multipliers already use this simulation safety limit.
const MAX_MULTIPLIER: i64 = 1000;

impl Campaign {
    /// Weapon/shield equipment uses dedicated slots. Other custom equipment,
    /// such as an HP amulet, remains visible in special inventory.
    pub fn is_equipment(&self, item: &str) -> bool {
        matches!(
            self.equipment_stat(item),
            Some(Stat::Attack | Stat::Defense)
        )
    }

    fn equipment_stat(&self, item: &str) -> Option<Stat> {
        self.tiles
            .values()
            .find(|tile| tile.kind == TileKind::Equipment && tile.item.as_deref() == Some(item))
            .map(|tile| tile.stat.unwrap_or(Stat::Attack))
            .or(match item {
                "sword_1" | "sword_2" | "sword_3" | "sword_4" | "sword_5" => Some(Stat::Attack),
                "shield_1" | "shield_2" | "shield_3" | "shield_4" | "sacred_shield" => {
                    Some(Stat::Defense)
                }
                _ => None,
            })
    }

    pub(crate) fn initial_player(&self) -> Player {
        let mut player = self.start.clone();
        player.infer_equipment(self, player.weapon.is_none(), player.shield.is_none());
        player
    }

    pub(crate) fn validate_equipment(&self, player: &Player) -> Result<(), String> {
        for (name, item, stat) in [
            ("weapon", &player.weapon, Stat::Attack),
            ("shield", &player.shield, Stat::Defense),
        ] {
            if let Some(item) = item
                && self.equipment_stat(item) != Some(stat)
            {
                return Err(format!("player.{name}: {item} is not matching equipment"));
            }
        }
        Ok(())
    }

    /// Validate authored behavior before the engine compiles or runs scripts.
    ///
    /// Unknown metadata remains intact. Known optional fields may be absent, but
    /// a supplied value must have the documented type rather than taking a
    /// fallback intended for an omitted field.
    pub fn validate(&self) -> Result<(), String> {
        if self.id.trim().is_empty()
            || !(1..=MAX_MAP_SIDE).contains(&self.width)
            || !(1..=MAX_MAP_SIDE).contains(&self.height)
        {
            return Err(format!(
                "Campaign must have an ID and dimensions between 1 and {MAX_MAP_SIDE}"
            ));
        }
        if !(1..=MAX_FLOORS).contains(&self.floors.len()) {
            return Err(format!("Campaign must contain 1–{MAX_FLOORS} floors"));
        }

        let mut floor_ids = BTreeSet::new();
        for (index, floor) in self.floors.iter().enumerate() {
            let path = format!("floors[{index}]");
            if !floor_ids.insert(floor.id) {
                return Err(format!("{path}.id: duplicate floor {}", floor.id));
            }
            if floor.tiles.len() != self.width * self.height {
                return Err(format!(
                    "{path}.tiles: expected {} cells",
                    self.width * self.height
                ));
            }
            for tile in &floor.tiles {
                self.validate_tile_id(*tile, &format!("{path}.tiles"))?;
            }
            for (name, position) in [
                ("arrival_up", &floor.arrival_up),
                ("arrival_down", &floor.arrival_down),
            ] {
                if let Some(position) = position {
                    self.validate_position(
                        floor.id,
                        position.x,
                        position.y,
                        &format!("{path}.{name}"),
                    )?;
                }
            }
        }
        self.validate_position(self.start.floor, self.start.x, self.start.y, "start")?;
        validate_player(&self.start)?;
        self.validate_equipment(&self.start)?;

        for (id, enemy) in &self.enemies {
            validate_name(id, &format!("enemies.{id}"))?;
            if !(1..=MAX_STAT).contains(&enemy.hp)
                || [enemy.attack, enemy.defense, enemy.gold]
                    .iter()
                    .any(|v| !(0..=MAX_STAT).contains(v))
            {
                return Err(format!(
                    "enemies.{id}: invalid statistics for {}",
                    enemy.name
                ));
            }
        }
        for (id, tile) in &self.tiles {
            let numeric_id = id
                .parse::<u16>()
                .map_err(|e| format!("tiles.{id}: expected a numeric tile ID: {e}"))?;
            // The simulation indexes definitions using a cell's canonical ID.
            // "06" would otherwise load successfully but never be found as "6".
            if numeric_id.to_string() != *id {
                return Err(format!(
                    "tiles.{id}: tile IDs must use their canonical decimal spelling"
                ));
            }
            self.validate_tile(tile, &format!("tiles.{id}"))?;
        }
        self.validate_rules()?;

        let mut event_ids = BTreeSet::new();
        for (index, event) in self.events.iter().enumerate() {
            let path = format!("events[{index}]");
            crate::events::validate_event(self, event, &path)?;
            let key = event
                .get("id")
                .and_then(Value::as_str)
                .map(str::to_owned)
                .unwrap_or_else(|| index.to_string());
            if !event_ids.insert(key.clone()) {
                return Err(format!("{path}.id: duplicate event counter key {key:?}"));
            }
        }

        let mut locations = BTreeSet::new();
        for (index, value) in self.interactions.iter().enumerate() {
            let path = format!("interactions[{index}]");
            let local = object(value, &path)?;
            let floor: i32 = required(local, "floor", &path)?;
            let x: usize = required(local, "x", &path)?;
            let y: usize = required(local, "y", &path)?;
            self.validate_position(floor, x, y, &path)?;
            if !locations.insert((floor, x, y)) {
                return Err(format!("{path}: duplicate interaction at {floor}:{x}:{y}"));
            }
            let floor_data = self
                .floors
                .iter()
                .find(|f| f.id == floor)
                .ok_or_else(|| format!("{path}.floor: undefined floor"))?;
            let tile_id = floor_data.tiles[y * self.width + x];
            let base = self
                .tiles
                .get(&tile_id.to_string())
                .ok_or_else(|| format!("{path}: undefined tile"))?;
            let mut merged = serde_json::to_value(base).map_err(|e| format!("{path}: {e}"))?;
            for (key, field) in local {
                if !["floor", "x", "y"].contains(&key.as_str()) {
                    merged[key] = field.clone();
                }
            }
            // Validate the actual object the interaction code will deserialize.
            // A malformed override previously fell back to the base NPC silently.
            let definition: TileDef = decode(&merged, &path)?;
            self.validate_tile(&definition, &path)?;
        }

        for (id, value) in &self.items {
            let path = format!("items.{id}");
            validate_name(id, &path)?;
            let definition = object(value, &path)?;
            optional::<bool>(definition, "consumable", &path)?;
            if let Some(value) = definition.get("effects") {
                let effects: Vec<Value> = decode(value, &format!("{path}.effects"))?;
                crate::events::validate_effects(self, &effects, &format!("{path}.effects"))?;
            }
        }
        Ok(())
    }

    fn validate_position(&self, floor: i32, x: usize, y: usize, path: &str) -> Result<(), String> {
        if !self.floors.iter().any(|f| f.id == floor) || x >= self.width || y >= self.height {
            return Err(format!(
                "{path}: floor or coordinates are outside the campaign"
            ));
        }
        Ok(())
    }

    fn validate_tile_id(&self, tile: u16, path: &str) -> Result<(), String> {
        if !self.tiles.contains_key(&tile.to_string()) {
            return Err(format!("{path}: references undefined tile {tile}"));
        }
        Ok(())
    }

    fn validate_tile(&self, tile: &TileDef, path: &str) -> Result<(), String> {
        if let Some(enemy) = &tile.enemy
            && !self.enemies.contains_key(enemy)
        {
            return Err(format!(
                "{path}.enemy: references undefined enemy {enemy:?}"
            ));
        }
        if matches!(tile.kind, TileKind::Enemy | TileKind::Monster) && tile.enemy.is_none() {
            return Err(format!("{path}.enemy: enemy tiles require an enemy ID"));
        }
        if let Some(divisor) = tile.reward_divisor
            && (!(1..=MAX_STAT).contains(&divisor)
                || !matches!(tile.kind, TileKind::Enemy | TileKind::Monster))
        {
            return Err(format!(
                "{path}.reward_divisor: enemy encounters require an integer between 1 and {MAX_STAT}"
            ));
        }
        if let Some(item) = &tile.item {
            // Items can be custom passive inventory tags, not only built-in tools.
            validate_name(item, &format!("{path}.item"))?;
        }
        if !(-MAX_STAT..=MAX_STAT).contains(&tile.amount) {
            return Err(format!(
                "{path}.amount: must be between -{MAX_STAT} and {MAX_STAT}"
            ));
        }
        if let Some(target) = tile.target_floor
            && !self.floors.iter().any(|f| f.id == target)
        {
            return Err(format!(
                "{path}.target_floor: references undefined floor {target}"
            ));
        }
        for key in ["scaled", "disappear"] {
            if let Some(value) = tile.extra.get(key) {
                decode::<bool>(value, &format!("{path}.{key}"))?;
            }
        }
        if let Some(after_text) = tile.extra.get("after_text") {
            let after_text = object(after_text, &format!("{path}.after_text"))?;
            let flag: String = required(after_text, "flag", &format!("{path}.after_text"))?;
            validate_name(&flag, &format!("{path}.after_text.flag"))?;
            required::<String>(after_text, "text", &format!("{path}.after_text"))?;
        }
        if matches!(
            tile.kind,
            TileKind::Stairs | TileKind::StairsUp | TileKind::StairsDown
        ) && let Some(direction) = tile.extra.get("direction")
        {
            let direction: String = decode(direction, &format!("{path}.direction"))?;
            if !["up", "down"].contains(&direction.as_str()) {
                return Err(format!("{path}.direction: expected up or down"));
            }
        }
        if let Some(footprint) = tile.extra.get("footprint") {
            self.validate_footprint(footprint, &format!("{path}.footprint"))?;
        }
        self.validate_sprite(&tile.sprite, &format!("{path}.sprite"))?;
        crate::events::validate_effects(self, &tile.effects, &format!("{path}.effects"))?;
        self.validate_offers(&tile.offers, &format!("{path}.offers"))
    }

    fn validate_offers(&self, offers: &[Value], path: &str) -> Result<(), String> {
        let mut keys = BTreeSet::new();
        for (index, offer) in offers.iter().enumerate() {
            let path = format!("{path}[{index}]");
            crate::events::validate_offer(self, offer, &path)?;
            let key = offer
                .get("id")
                .and_then(Value::as_str)
                .map(str::to_owned)
                .unwrap_or_else(|| index.to_string());
            if key == "leave" || !keys.insert(key.clone()) {
                return Err(format!("{path}.id: duplicate or reserved offer ID {key:?}"));
            }
        }
        Ok(())
    }

    fn validate_footprint(&self, value: &Value, path: &str) -> Result<(), String> {
        let footprint = object(value, path)?;
        optional::<bool>(footprint, "clear_all", path)?;
        let width: usize = required(footprint, "width", path)?;
        let height: usize = required(footprint, "height", path)?;
        if !(1..=self.width).contains(&width) || !(1..=self.height).contains(&height) {
            return Err(format!(
                "{path}: footprint dimensions are outside the campaign"
            ));
        }
        for (key, dimension) in [("offset_x", width), ("offset_y", height)] {
            if optional::<usize>(footprint, key, path)?.is_some_and(|value| value >= dimension) {
                return Err(format!(
                    "{path}.{key}: offset must lie inside its footprint"
                ));
            }
        }
        let tiles: Vec<u16> = required(footprint, "tiles", path)?;
        for tile in tiles {
            self.validate_tile_id(tile, &format!("{path}.tiles"))?;
        }
        Ok(())
    }

    fn validate_sprite(&self, value: &Value, path: &str) -> Result<(), String> {
        if value.is_null() {
            return Ok(());
        }
        if value.is_object() {
            let rect = object(value, path)?;
            // Custom rectangles may be fractional; the renderer accepts pixels.
            for key in ["x", "y", "w", "h"] {
                if let Some(value) = optional::<f64>(rect, key, path)?
                    && (value < 0.0 || (!matches!(key, "x" | "y") && value == 0.0))
                {
                    return Err(format!(
                        "{path}.{key}: sprite coordinates must be nonnegative and sizes positive"
                    ));
                }
            }
        } else {
            decode::<u16>(value, path)?;
        }
        Ok(())
    }

    fn validate_rules(&self) -> Result<(), String> {
        crate::flight::validate_callbacks(self)?;
        // Serde's omitted Value is null; this represents an absent rules object.
        // Known properties inside an authored object do not accept null.
        let empty_rules = serde_json::Map::new();
        let rules = if self.rules.is_null() {
            &empty_rules
        } else {
            object(&self.rules, "rules")?
        };
        let empty = optional::<u16>(rules, "empty_tile", "rules")?.unwrap_or(0);
        self.validate_tile_id(empty, "rules.empty_tile")?;
        // Clearing a creature, door or lava must leave ordinary passage. In
        // particular, the Snow Crystal's flood fill terminates when cleared
        // cells stop being lava; replacing lava with lava would revisit forever.
        if self.tiles.get(&empty.to_string()).is_none_or(|tile| {
            !matches!(
                tile.kind,
                TileKind::Empty | TileKind::Floor | TileKind::Decoration
            )
        }) {
            return Err(
                "rules.empty_tile: must reference an empty, floor or decoration tile".into(),
            );
        }
        for key in [
            "hero_attacks_first",
            "base_attack_guard",
            "flying_requires_stairs",
            "flying_original_selection",
            "save_requires_hero_orb",
        ] {
            optional::<bool>(rules, key, "rules")?;
        }
        for key in [
            "altar_base_cost",
            "altar_hp_gain",
            "altar_attack_gain",
            "altar_defense_gain",
            "lava_damage",
            "magician_a_damage",
            "magician_b_damage",
        ] {
            integer_range(rules, key, "rules", 0, MAX_STAT)?;
        }
        for key in ["cross_multiplier", "dragon_slayer_multiplier"] {
            integer_range(rules, key, "rules", 1, MAX_MULTIPLIER)?;
        }
        if let Some(item) = optional::<String>(rules, "forecast_requires_item", "rules")? {
            validate_name(&item, "rules.forecast_requires_item")?;
        }
        if let Some(value) = rules.get("area_scaling") {
            let entries: Vec<Value> = decode(value, "rules.area_scaling")?;
            let mut previous = None;
            for (index, entry) in entries.iter().enumerate() {
                let path = format!("rules.area_scaling[{index}]");
                let entry = object(entry, &path)?;
                let maximum: i32 = required(entry, "max_floor", &path)?;
                if previous.is_some_and(|last| maximum <= last) {
                    return Err(format!(
                        "{path}.max_floor: scaling thresholds must increase"
                    ));
                }
                previous = Some(maximum);
                let multiplier: i64 = required(entry, "multiplier", &path)?;
                if !(1..=MAX_MULTIPLIER).contains(&multiplier) {
                    return Err(format!(
                        "{path}.multiplier: must be between 1 and {MAX_MULTIPLIER}"
                    ));
                }
            }
        }
        if let Some(value) = rules.get("stair_links") {
            for (key, target) in object(value, "rules.stair_links")? {
                let path = format!("rules.stair_links.{key}");
                let (floor, direction) = key
                    .split_once(':')
                    .ok_or_else(|| format!("{path}: expected floor:up or floor:down"))?;
                let floor: i32 = floor
                    .parse()
                    .map_err(|e| format!("{path}: invalid source floor: {e}"))?;
                let target: i32 = decode(target, &path)?;
                if !["up", "down"].contains(&direction)
                    || !self.floors.iter().any(|f| f.id == floor)
                    || !self.floors.iter().any(|f| f.id == target)
                {
                    return Err(format!("{path}: stair link direction or floor is invalid"));
                }
            }
        }
        for key in ["bomb_tile_ranges", "wall_break_tile_ranges"] {
            if let Some(value) = rules.get(key) {
                let path = format!("rules.{key}");
                let ranges: Vec<[u16; 2]> = decode(value, &path)?;
                if ranges.iter().any(|[minimum, maximum]| minimum > maximum) {
                    return Err(format!("{path}: each inclusive range must increase"));
                }
            }
        }
        if let Some(value) = rules.get("wisdom_dialogue_range") {
            let [minimum, maximum]: [u32; 2] = decode(value, "rules.wisdom_dialogue_range")?;
            if minimum > maximum {
                return Err("rules.wisdom_dialogue_range: inclusive range must increase".into());
            }
        }
        if let Some(value) = rules.get("backside") {
            let backside = object(value, "rules.backside")?;
            for key in [
                "enabled",
                "carry_stats",
                "reset_gold",
                "capture_preserves_stats",
            ] {
                optional::<bool>(backside, key, "rules.backside")?;
            }
            integer_range(backside, "multiplier", "rules.backside", 1, MAX_MULTIPLIER)?;
        }
        if let Some(value) = rules.get("presentation") {
            let presentation = object(value, "rules.presentation")?;
            // Existing renderer clamps: ambient 60–1000 ms, each battle strike
            // 60–3000 ms, floor wipe 30–10000 ms. Reject bad imports explicitly.
            for (key, minimum, maximum) in [
                ("ambient_frame_ms", 60, 1000),
                ("combat_strike_ms", 60, 3000),
                ("floor_transition_ms", 30, 10_000),
            ] {
                integer_range(presentation, key, "rules.presentation", minimum, maximum)?;
            }
        }
        if let Some(value) = rules.get("audio") {
            let audio = object(value, "rules.audio")?;
            if let Some(value) = audio.get("floor_music") {
                let entries: Vec<Value> = decode(value, "rules.audio.floor_music")?;
                for (index, entry) in entries.iter().enumerate() {
                    let path = format!("rules.audio.floor_music[{index}]");
                    let entry = object(entry, &path)?;
                    let minimum: i32 = required(entry, "min_floor", &path)?;
                    let maximum: i32 = required(entry, "max_floor", &path)?;
                    if minimum > maximum {
                        return Err(format!("{path}: floor range must increase"));
                    }
                    let file: String = required(entry, "file", &path)?;
                    validate_name(&file, &format!("{path}.file"))?;
                }
            }
            if let Some(value) = audio.get("music_cues") {
                for (key, file) in object(value, "rules.audio.music_cues")? {
                    let path = format!("rules.audio.music_cues.{key}");
                    let file: String = decode(file, &path)?;
                    validate_name(&file, &path)?;
                }
            }
        }
        Ok(())
    }
}

fn decode<T: serde::de::DeserializeOwned>(value: &Value, path: &str) -> Result<T, String> {
    serde_json::from_value(value.clone()).map_err(|e| format!("{path}: {e}"))
}
fn object<'a>(value: &'a Value, path: &str) -> Result<&'a serde_json::Map<String, Value>, String> {
    value
        .as_object()
        .ok_or_else(|| format!("{path}: expected an object"))
}
fn required<T: serde::de::DeserializeOwned>(
    fields: &serde_json::Map<String, Value>,
    key: &str,
    path: &str,
) -> Result<T, String> {
    let value = fields
        .get(key)
        .ok_or_else(|| format!("{path}.{key}: required field is missing"))?;
    decode(value, &format!("{path}.{key}"))
}
fn optional<T: serde::de::DeserializeOwned>(
    fields: &serde_json::Map<String, Value>,
    key: &str,
    path: &str,
) -> Result<Option<T>, String> {
    fields
        .get(key)
        .map(|value| decode(value, &format!("{path}.{key}")))
        .transpose()
}
fn integer_range(
    fields: &serde_json::Map<String, Value>,
    key: &str,
    path: &str,
    minimum: i64,
    maximum: i64,
) -> Result<(), String> {
    if optional::<i64>(fields, key, path)?
        .is_some_and(|value| !(minimum..=maximum).contains(&value))
    {
        return Err(format!(
            "{path}.{key}: must be between {minimum} and {maximum}"
        ));
    }
    Ok(())
}
fn validate_name(value: &str, path: &str) -> Result<(), String> {
    if value.trim().is_empty() {
        return Err(format!("{path}: identifier must not be empty"));
    }
    Ok(())
}

pub(crate) fn validate_player(player: &Player) -> Result<(), String> {
    if [
        player.hp,
        player.attack,
        player.defense,
        player.gold,
        player.keys.yellow,
        player.keys.blue,
        player.keys.red,
    ]
    .iter()
    .any(|value| !(0..=MAX_STAT).contains(value))
    {
        return Err(format!(
            "Player statistics must be between 0 and {MAX_STAT}"
        ));
    }
    for item in &player.inventory {
        validate_name(item, "player.inventory")?;
    }
    for item in [&player.weapon, &player.shield].into_iter().flatten() {
        validate_name(item, "player equipment")?;
    }
    for item in player.item_charges.keys() {
        validate_name(item, "player.item_charges")?;
    }
    Ok(())
}
