//! Deterministic, platform-independent Tower of the Sorcerer simulation.
//! Campaign geometry, tile behavior, statistics, shops and events come from JSON.
use serde::{Deserialize, Serialize};
use serde_json::{Value, json};
use std::collections::{BTreeMap, BTreeSet, VecDeque};

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
}

#[derive(Clone, Debug, Default, Serialize, Deserialize)]
pub struct TileDef {
    pub name: String,
    pub kind: String,
    #[serde(default)]
    pub description: String,
    #[serde(default)]
    pub enemy: Option<String>,
    #[serde(default)]
    pub key: Option<String>,
    #[serde(default)]
    pub amount: i64,
    #[serde(default)]
    pub stat: Option<String>,
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

#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct Enemy {
    pub name: String,
    pub hp: i64,
    pub attack: i64,
    pub defense: i64,
    pub gold: i64,
    #[serde(default)]
    pub special: String,
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

impl Campaign {
    pub fn validate(&self) -> Result<(), String> {
        if self.id.is_empty()
            || self.width == 0
            || self.height == 0
            || self.width > 64
            || self.height > 64
        {
            return Err("Campaign must have an ID and dimensions between 1 and 64".into());
        }
        if self.floors.is_empty() || self.floors.len() > 256 {
            return Err("Campaign must contain 1–256 floors".into());
        }
        let mut ids = BTreeSet::new();
        for floor in &self.floors {
            if !ids.insert(floor.id) || floor.tiles.len() != self.width * self.height {
                return Err(format!(
                    "Floor {} is duplicated or has incorrect dimensions",
                    floor.id
                ));
            }
            for tile in &floor.tiles {
                if !self.tiles.contains_key(&tile.to_string()) {
                    return Err(format!(
                        "Floor {} references undefined tile {}",
                        floor.id, tile
                    ));
                }
            }
        }
        if !ids.contains(&self.start.floor)
            || self.start.x >= self.width
            || self.start.y >= self.height
        {
            return Err("Starting location is outside the campaign".into());
        }
        validate_player(&self.start)?;
        for (id, tile) in &self.tiles {
            if let Some(enemy) = &tile.enemy
                && !self.enemies.contains_key(enemy)
            {
                return Err(format!("Tile {id} references undefined enemy {enemy}"));
            }
        }
        for enemy in self.enemies.values() {
            if enemy.hp <= 0
                || enemy.hp > 1_000_000_000
                || [enemy.attack, enemy.defense, enemy.gold]
                    .iter()
                    .any(|v| *v < 0 || *v > 1_000_000_000)
            {
                return Err(format!("Invalid statistics for {}", enemy.name));
            }
        }
        let empty = self.rules["empty_tile"].as_u64().unwrap_or(0).to_string();
        if !self.tiles.contains_key(&empty) {
            return Err("rules.empty_tile references an undefined tile".into());
        }
        for floor in &self.floors {
            for position in [&floor.arrival_up, &floor.arrival_down]
                .into_iter()
                .flatten()
            {
                if position.x >= self.width || position.y >= self.height {
                    return Err(format!(
                        "Floor {} has invalid stair arrival metadata",
                        floor.id
                    ));
                }
            }
        }
        for event in &self.events {
            let trigger = &event["trigger"];
            if ![
                "step",
                "bump",
                "enter_floor",
                "enemy_defeated",
                "interact",
                "door_opened",
            ]
            .contains(&trigger["type"].as_str().unwrap_or(""))
            {
                return Err(format!("Event {} has an unknown trigger", event["id"]));
            }
            self.validate_effects(
                event["effects"]
                    .as_array()
                    .map(Vec::as_slice)
                    .unwrap_or(&[]),
            )?;
        }
        for tile in self.tiles.values() {
            if !(-1_000_000_000..=1_000_000_000).contains(&tile.amount) {
                return Err(format!(
                    "Pickup amount is outside the supported range: {}",
                    tile.name
                ));
            }
            self.validate_effects(&tile.effects)?;
            for offer in &tile.offers {
                self.validate_offer(offer)?;
            }
        }
        for interaction in &self.interactions {
            if !ids.contains(&(interaction["floor"].as_i64().unwrap_or(i64::MIN) as i32))
                || interaction["x"]
                    .as_u64()
                    .is_none_or(|x| x >= self.width as u64)
                || interaction["y"]
                    .as_u64()
                    .is_none_or(|y| y >= self.height as u64)
            {
                return Err("Interaction has an invalid floor or position".into());
            }
            self.validate_effects(
                interaction["effects"]
                    .as_array()
                    .map(Vec::as_slice)
                    .unwrap_or(&[]),
            )?;
            if let Some(offers) = interaction["offers"].as_array() {
                for offer in offers {
                    self.validate_offer(offer)?;
                }
            }
        }
        Ok(())
    }

    fn validate_offer(&self, offer: &Value) -> Result<(), String> {
        if ["cost", "cost_increment"].iter().any(|key| {
            offer[*key]
                .as_i64()
                .is_some_and(|cost| !(0..=1_000_000_000).contains(&cost))
        }) {
            return Err("Shop cost and increments must be between 0 and 1,000,000,000; represent sales with effects".into());
        }
        self.validate_effects(
            offer["effects"]
                .as_array()
                .map(Vec::as_slice)
                .unwrap_or(&[]),
        )
    }

    fn validate_effects(&self, effects: &[Value]) -> Result<(), String> {
        for effect in effects {
            let kind = effect["type"].as_str().unwrap_or("");
            if ![
                "message",
                "flag",
                "set_tile",
                "add_stat",
                "set_stat",
                "multiply_stat",
                "give_item",
                "remove_item",
                "clear_inventory",
                "teleport",
                "win",
                "set_enemy",
                "battle_at",
                "set_charges",
                "set_visited",
                "wait",
                "sound",
                "cinematic",
                "move_tile",
                "next_cycle",
            ]
            .contains(&kind)
            {
                return Err(format!("Unknown campaign effect: {kind}"));
            }
            if ["set_tile", "teleport", "battle_at"].contains(&kind)
                && (effect["floor"]
                    .as_i64()
                    .is_some_and(|floor| !self.floors.iter().any(|f| i64::from(f.id) == floor))
                    || effect["x"].as_u64().is_none_or(|x| x >= self.width as u64)
                    || effect["y"].as_u64().is_none_or(|y| y >= self.height as u64))
            {
                return Err(format!("{kind} effect targets an invalid position"));
            }
            if kind == "move_tile"
                && (effect["floor"]
                    .as_i64()
                    .is_some_and(|floor| !self.floors.iter().any(|f| i64::from(f.id) == floor))
                    || ["x", "from_x"]
                        .iter()
                        .any(|key| effect[*key].as_u64().is_none_or(|x| x >= self.width as u64))
                    || ["y", "from_y"].iter().any(|key| {
                        effect[*key]
                            .as_u64()
                            .is_none_or(|y| y >= self.height as u64)
                    }))
            {
                return Err("move_tile effect targets an invalid position".into());
            }
            if kind == "set_tile"
                && !self.tiles.contains_key(
                    &effect["tile"]
                        .as_u64()
                        .ok_or("set_tile requires a numeric tile")?
                        .to_string(),
                )
            {
                return Err("set_tile effect references an undefined tile".into());
            }
            if ["add_stat", "set_stat", "multiply_stat"].contains(&kind)
                && !["hp", "attack", "defense", "gold", "yellow", "blue", "red"]
                    .contains(&effect["stat"].as_str().unwrap_or(""))
            {
                return Err("Stat effect references an undefined statistic".into());
            }
            if kind == "set_enemy"
                && !self
                    .enemies
                    .contains_key(effect["enemy"].as_str().unwrap_or(""))
            {
                return Err("set_enemy references an undefined enemy".into());
            }
        }
        Ok(())
    }
}

fn validate_player(player: &Player) -> Result<(), String> {
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
    .any(|v| *v < 0 || *v > 1_000_000_000)
    {
        return Err("Player statistics must be between 0 and 1,000,000,000".into());
    }
    Ok(())
}

#[derive(Clone, Debug, Serialize, Deserialize)]
struct Save {
    version: u32,
    campaign_id: String,
    campaign_fingerprint: String,
    player: Player,
    floors: BTreeMap<i32, Vec<u16>>,
    visited_floors: BTreeSet<i32>,
    flags: BTreeSet<String>,
    event_counts: BTreeMap<String, u32>,
    shop_visits: BTreeMap<String, i64>,
    log: Vec<String>,
    status: String,
    steps: u64,
    pending_interaction: Option<Value>,
    pending_tile: Option<(i32, usize, usize)>,
    #[serde(default)]
    enemy_overrides: BTreeMap<String, Enemy>,
    #[serde(default = "first_cycle")]
    cycle: u32,
}

fn first_cycle() -> u32 {
    1
}

#[derive(Clone, Debug, Serialize)]
pub struct Forecast {
    pub name: String,
    pub hp: i64,
    pub attack: i64,
    pub defense: i64,
    pub gold: i64,
    pub damage: Option<i64>,
    pub can_win: bool,
    pub reason: String,
    pub rounds: i64,
}

/// Hero strikes first; the last strike never receives a counterattack.
pub fn forecast(player: &Player, enemy: &Enemy) -> Forecast {
    forecast_with_rules(player, enemy, &Value::Null)
}

fn forecast_with_rules(player: &Player, enemy: &Enemy, rules: &Value) -> Forecast {
    let base_damage = player.attack - enemy.defense;
    let multiplier = match enemy.special.as_str() {
        "undead" if player.inventory.iter().any(|s| s == "cross") => rules["cross_multiplier"]
            .as_i64()
            .unwrap_or(2)
            .clamp(1, 1000),
        "dragon" if player.inventory.iter().any(|s| s == "dragon_slayer") => {
            rules["dragon_slayer_multiplier"]
                .as_i64()
                .unwrap_or(2)
                .clamp(1, 1000)
        }
        _ => 1,
    };
    let hit = player.attack.saturating_mul(multiplier) - enemy.defense;
    let can_attack =
        hit > 0 && (base_damage > 0 || !rules["base_attack_guard"].as_bool().unwrap_or(true));
    let rounds = if can_attack {
        (enemy.hp - 1) / hit
            + if rules["hero_attacks_first"].as_bool().unwrap_or(true) {
                0
            } else {
                1
            }
    } else {
        0
    };
    let damage = can_attack.then(|| rounds.saturating_mul((enemy.attack - player.defense).max(0)));
    let can_win = damage.is_some_and(|d| d < player.hp);
    Forecast {
        name: enemy.name.clone(),
        hp: enemy.hp,
        attack: enemy.attack,
        defense: enemy.defense,
        gold: enemy.gold
            * if player.inventory.iter().any(|item| item == "lucky_gold") {
                2
            } else {
                1
            },
        damage,
        can_win,
        rounds,
        reason: if !can_attack {
            "Your attack cannot penetrate this enemy's defense.".into()
        } else if !can_win {
            "This battle would be fatal.".into()
        } else {
            String::new()
        },
    }
}

#[derive(Clone)]
pub struct Engine {
    pub campaign: Campaign,
    state: Save,
    last_action: Value,
}

impl Engine {
    pub fn from_json(source: &str) -> Result<Self, String> {
        let campaign: Campaign =
            serde_json::from_str(source).map_err(|e| format!("Invalid campaign: {e}"))?;
        campaign.validate()?;
        Ok(Self::new(campaign))
    }

    pub fn new(campaign: Campaign) -> Self {
        let fingerprint =
            fingerprint(&serde_json::to_string(&campaign).expect("campaign serialization"));
        let state = Save {
            version: 1,
            campaign_id: campaign.id.clone(),
            campaign_fingerprint: fingerprint,
            player: campaign.start.clone(),
            floors: campaign
                .floors
                .iter()
                .map(|f| (f.id, f.tiles.clone()))
                .collect(),
            visited_floors: BTreeSet::from([campaign.start.floor]),
            flags: BTreeSet::new(),
            event_counts: BTreeMap::new(),
            shop_visits: BTreeMap::new(),
            log: vec![
                "Your journey begins. Every battle is deterministic; plan your route carefully."
                    .into(),
            ],
            status: "playing".into(),
            steps: 0,
            pending_interaction: None,
            pending_tile: None,
            enemy_overrides: BTreeMap::new(),
            cycle: 1,
        };
        Self {
            campaign,
            state,
            last_action: json!({"ok":true,"message":"Journey started"}),
        }
    }

    pub fn player(&self) -> &Player {
        &self.state.player
    }

    pub fn save_json(&self) -> String {
        serde_json::to_string(&self.state).expect("save serialization")
    }

    pub fn load_json(&mut self, source: &str) -> Result<(), String> {
        let save: Save = serde_json::from_str(source).map_err(|e| format!("Invalid save: {e}"))?;
        if save.cycle == 0
            || save.cycle > 1000
            || save.version != 1
            || save.campaign_id != self.campaign.id
            || save.campaign_fingerprint != self.state.campaign_fingerprint
        {
            return Err("Save belongs to a different campaign or campaign revision".into());
        }
        validate_player(&save.player)?;
        if save.player.x >= self.campaign.width
            || save.player.y >= self.campaign.height
            || !save.floors.contains_key(&save.player.floor)
        {
            return Err("Save contains an invalid player location".into());
        }
        if save.floors.len() != self.campaign.floors.len()
            || self
                .campaign
                .floors
                .iter()
                .any(|f| !save.floors.contains_key(&f.id))
        {
            return Err("Save floor set differs from the campaign".into());
        }
        for tiles in save.floors.values() {
            if tiles.len() != self.campaign.width * self.campaign.height
                || tiles
                    .iter()
                    .any(|id| !self.campaign.tiles.contains_key(&id.to_string()))
            {
                return Err("Save contains invalid floor tiles".into());
            }
        }
        if !["playing", "won", "lost"].contains(&save.status.as_str()) {
            return Err("Invalid save status".into());
        }
        if save
            .visited_floors
            .iter()
            .any(|floor| !save.floors.contains_key(floor))
            || save.shop_visits.values().any(|n| *n < 0 || *n > 1_000_000)
        {
            return Err("Save contains invalid visits or shop counters".into());
        }
        for (key, enemy) in &save.enemy_overrides {
            if !self.campaign.enemies.contains_key(key)
                || enemy.hp <= 0
                || [enemy.hp, enemy.attack, enemy.defense, enemy.gold]
                    .iter()
                    .any(|n| *n < 0 || *n > 1_000_000_000)
            {
                return Err("Save contains invalid enemy statistics".into());
            }
        }
        if save.pending_interaction.is_some() != save.pending_tile.is_some() {
            return Err("Save has an incomplete interaction".into());
        }
        if let Some((floor, x, y)) = save.pending_tile
            && (!save.floors.contains_key(&floor)
                || x >= self.campaign.width
                || y >= self.campaign.height)
        {
            return Err("Save has an invalid interaction position".into());
        }
        self.state = save;
        self.last_action = json!({"ok":true,"message":"Save loaded"});
        Ok(())
    }

    pub fn snapshot(&self) -> Value {
        let p = &self.state.player;
        let tiles = &self.state.floors[&p.floor];
        let enemies: Vec<Value> = tiles
            .iter()
            .enumerate()
            .filter_map(|(i, id)| {
                if self.noncombat_encounter(
                    p.floor,
                    i % self.campaign.width,
                    i / self.campaign.width,
                    *id,
                ) {
                    return None;
                }
                let def = self.campaign.tiles.get(&id.to_string())?;
                if !self.forecasts_unlocked() {
                    return None;
                }
                let enemy = self.encounter_enemy(
                    def.enemy.as_ref()?,
                    p.floor,
                    i % self.campaign.width,
                    i / self.campaign.width,
                    *id,
                )?;
                let mut value =
                    serde_json::to_value(forecast_with_rules(p, &enemy, &self.campaign.rules))
                        .ok()?;
                value["x"] = json!(i % self.campaign.width);
                value["y"] = json!(i / self.campaign.width);
                value["id"] = json!(id);
                Some(value)
            })
            .collect();
        json!({
            "campaign_id": self.campaign.id, "title": self.campaign.title,
            "floor": p.floor, "width": self.campaign.width, "height": self.campaign.height,
            "tiles": tiles, "tile_defs": self.campaign.tiles, "player": p,
            "enemies": enemies, "floors": self.campaign.floors.iter().map(|f| json!({"id":f.id,"title":f.title,"visited":self.state.visited_floors.contains(&f.id)})).collect::<Vec<_>>(),
            "visited_floors": self.state.visited_floors, "pending_interaction": self.state.pending_interaction,
            "inventory_items":p.inventory.iter().map(|item|{
                let definition=self.campaign.tiles.values().find(|def|def.item.as_ref()==Some(item));
                let usable=definition.is_none_or(|def|def.kind!="equipment") && !["hero_orb","wisdom_orb","monster_book","cross","dragon_slayer","lucky_gold","sacred_shield"].contains(&item.as_str());
                json!({"id":item,"name":definition.map(|def|def.name.as_str()).unwrap_or(item),"sprite":definition.map(|def|&def.sprite),"usable":usable,"charges":p.item_charges.get(item)})
            }).collect::<Vec<_>>(),
            "log": self.state.log, "status": self.state.status, "steps": self.state.steps,
            "flags": self.state.flags, "last_action": self.last_action,
            "cycle": self.state.cycle, "backside_multiplier": self.cycle_multiplier(),
            "forecasts_unlocked": self.forecasts_unlocked(),
        })
    }

    pub fn inspect(&self, x: usize, y: usize) -> Value {
        let Some(id) = self.tile_at(self.state.player.floor, x, y) else {
            return json!({"error":"Outside map"});
        };
        let def = &self.campaign.tiles[&id.to_string()];
        let noncombat = self.noncombat_encounter(self.state.player.floor, x, y, id);
        let enemy = def
            .enemy
            .as_ref()
            .and_then(|key| self.encounter_enemy(key, self.state.player.floor, x, y, id))
            .filter(|_| !noncombat && self.forecasts_unlocked())
            .map(|e| forecast_with_rules(&self.state.player, &e, &self.campaign.rules));
        let concealed = def.kind == "hidden_wall";
        json!({"id":id,"x":x,"y":y,"name":if concealed{"Brick wall"}else{&def.name},"description":if concealed{"A solid wall."}else if noncombat{"Approach this character to complete the adventure."}else{&def.description},"kind":if concealed{"wall"}else if noncombat{"npc"}else{&def.kind},"enemy":enemy,"details_locked":def.enemy.is_some() && !noncombat && !self.forecasts_unlocked()})
    }

    fn noncombat_encounter(&self, floor: i32, x: usize, y: usize, tile: u16) -> bool {
        self.campaign.events.iter().any(|event| {
            let trigger = &event["trigger"];
            trigger["type"].as_str() == Some("bump")
                && trigger["floor"]
                    .as_i64()
                    .is_none_or(|f| f == i64::from(floor))
                && trigger["x"].as_u64().is_none_or(|v| v == x as u64)
                && trigger["y"].as_u64().is_none_or(|v| v == y as u64)
                && trigger["tile"]
                    .as_u64()
                    .is_none_or(|v| v == u64::from(tile))
                && event["effects"].as_array().is_some_and(|effects| {
                    effects.iter().any(|effect| {
                        ["win", "next_cycle"].contains(&effect["type"].as_str().unwrap_or(""))
                    })
                })
                && self.conditions_pass(&event["conditions"])
        })
    }

    pub fn command(&mut self, command: Value) -> Result<(), String> {
        let kind = command["type"]
            .as_str()
            .ok_or("Command needs a string type")?;
        self.last_action = json!({"ok":true,"type":kind,"presentation":[]});
        if kind == "new_game" {
            *self = Self::new(self.campaign.clone());
            return Ok(());
        }
        if kind == "cancel" {
            self.state.pending_interaction = None;
            self.state.pending_tile = None;
            return Ok(());
        }
        if self.state.status != "playing" {
            return self.block("This journey has ended. Start a new game or load a save.");
        }
        match kind {
            "move" => {
                if self.state.pending_interaction.is_some() {
                    return self.block("Finish or dismiss the current conversation first.");
                }
                let (dx, dy) = match command["direction"].as_str() {
                    Some("up") => (0, -1),
                    Some("down") => (0, 1),
                    Some("left") => (-1, 0),
                    Some("right") => (1, 0),
                    _ => return Err("Direction must be up, down, left or right".into()),
                };
                self.move_player(dx, dy)
            }
            "choose" => self.choose(command["choice"].as_str().ok_or("Choice needs an ID")?),
            "use_item" => self.use_item(
                command["item"].as_str().ok_or("Item needs an ID")?,
                &command,
            ),
            _ => Err(format!("Unknown command type: {kind}")),
        }
    }

    fn block(&mut self, message: &str) -> Result<(), String> {
        self.last_action["ok"] = json!(false);
        self.last_action["message"] = json!(message);
        Ok(())
    }

    fn enemy(&self, key: &str) -> Option<Enemy> {
        let mut enemy = self
            .state
            .enemy_overrides
            .get(key)
            .or_else(|| self.campaign.enemies.get(key))
            .cloned()?;
        let factor = self.cycle_multiplier();
        enemy.hp = enemy.hp.saturating_mul(factor).min(1_000_000_000);
        enemy.attack = enemy.attack.saturating_mul(factor).min(1_000_000_000);
        enemy.defense = enemy.defense.saturating_mul(factor).min(1_000_000_000);
        Some(enemy)
    }

    /// Preview stat changes performed by the encounter's bump handler on a copy.
    /// This keeps location-specific bosses consistent with their actual battle.
    fn encounter_enemy(
        &self,
        key: &str,
        floor: i32,
        x: usize,
        y: usize,
        tile: u16,
    ) -> Option<Enemy> {
        let changes_stats = self.campaign.events.iter().any(|event| {
            let trigger = &event["trigger"];
            trigger["type"] == "bump"
                && trigger["floor"]
                    .as_i64()
                    .is_none_or(|f| f == i64::from(floor))
                && trigger["x"].as_u64().is_none_or(|v| v == x as u64)
                && trigger["y"].as_u64().is_none_or(|v| v == y as u64)
                && trigger["tile"]
                    .as_u64()
                    .is_none_or(|v| v == u64::from(tile))
                && self.conditions_pass(&event["conditions"])
                && event["effects"].as_array().is_some_and(|effects| {
                    effects
                        .iter()
                        .any(|effect| effect["type"] == "set_enemy" && effect["enemy"] == key)
                })
        });
        if changes_stats {
            let mut preview = self.clone();
            preview.run_events("bump", floor, x, y, Some(tile));
            preview.enemy(key)
        } else {
            self.enemy(key)
        }
    }

    pub fn forecasts_unlocked(&self) -> bool {
        self.campaign.rules["forecast_requires_item"]
            .as_str()
            .is_none_or(|item| {
                self.state
                    .player
                    .inventory
                    .iter()
                    .any(|owned| owned == item)
            })
    }

    pub fn cycle_multiplier(&self) -> i64 {
        if self.state.cycle > 1 {
            self.campaign.rules["backside"]["multiplier"]
                .as_i64()
                .unwrap_or(44)
                .clamp(1, 1000)
        } else {
            1
        }
    }

    fn present(&mut self, effect: Value) {
        if !self.last_action["presentation"].is_array() {
            self.last_action["presentation"] = json!([]);
        }
        self.last_action["presentation"]
            .as_array_mut()
            .unwrap()
            .push(effect);
    }

    fn present_move(&mut self, from: &Player, x: usize, y: usize, dx: isize, dy: isize) {
        self.present(json!({"type":"move","from":{"floor":from.floor,"x":from.x,"y":from.y},"to":{"floor":from.floor,"x":x,"y":y},"direction":if dx>0{"right"}else if dx<0{"left"}else if dy>0{"down"}else{"up"},"duration_ms":110}));
    }

    fn present_floor(&mut self, from: i32, transition: &str, duration_ms: Option<u64>) {
        let target = self.state.player.floor;
        self.present(json!({"type":"floor","from":from,"to":target,
            "x":self.state.player.x,"y":self.state.player.y,
            "player":self.state.player,"tiles":self.state.floors.get(&target),
            "direction":if target>=from{"up"}else{"down"},
            "style":transition,"sound":if transition=="original_spiral"{"kai"}else{"none"},
            "duration_ms":duration_ms.or_else(||self.campaign.rules["presentation"]["floor_transition_ms"].as_u64()).unwrap_or(450).clamp(30,10_000)}));
    }

    fn present_battle(
        &mut self,
        enemy: &Enemy,
        battle: &Forecast,
        floor: i32,
        x: usize,
        y: usize,
        enemy_first: bool,
    ) {
        let multiplier = match enemy.special.as_str() {
            "undead" if self.state.player.inventory.iter().any(|i| i == "cross") => {
                self.campaign.rules["cross_multiplier"]
                    .as_i64()
                    .unwrap_or(2)
            }
            "dragon"
                if self
                    .state
                    .player
                    .inventory
                    .iter()
                    .any(|i| i == "dragon_slayer") =>
            {
                self.campaign.rules["dragon_slayer_multiplier"]
                    .as_i64()
                    .unwrap_or(2)
            }
            _ => 1,
        };
        let hero_hit = (self.state.player.attack.saturating_mul(multiplier) - enemy.defense).max(1);
        let enemy_hit = (enemy.attack - self.state.player.defense).max(0);
        let base_hero_first = self.campaign.rules["hero_attacks_first"]
            .as_bool()
            .unwrap_or(true);
        let first = enemy_first || !base_hero_first;
        let mut hero_strikes = (enemy.hp - 1) / hero_hit + 1;
        let mut enemy_strikes = battle.rounds + i64::from(enemy_first && base_hero_first);
        if enemy_hit > 0 && enemy_strikes.saturating_mul(enemy_hit) >= self.state.player.hp {
            enemy_strikes = (self.state.player.hp - 1) / enemy_hit + 1;
            hero_strikes = enemy_strikes - i64::from(first);
        }
        let strike_ms = self.campaign.rules["presentation"]["combat_strike_ms"]
            .as_u64()
            .unwrap_or(450)
            .clamp(60, 3_000);
        let duration_ms =
            (hero_strikes.saturating_add(enemy_strikes).max(1) as u64).saturating_mul(strike_ms);
        self.present(json!({"type":"battle","enemy_name":enemy.name,"enemy_hp":enemy.hp,"hero_hp":self.state.player.hp,"hero_hit":hero_hit,"enemy_hit":enemy_hit,"rounds":battle.rounds,"hero_strikes":hero_strikes,"enemy_strikes":enemy_strikes,"enemy_first":first,"floor":floor,"x":x,"y":y,
            "strike_ms":strike_ms,"hit_sound":"taisen","sound_phase":0.0,"overlay_phase":1.0/3.0,"damage_phase":2.0/3.0,"duration_ms":duration_ms}));
    }

    /// Plan through clear road only. An obstacle may be the final action, never an intermediate step.
    /// Unreachable destinations return the reachable road prefix closest to the requested square.
    pub fn path_to(&self, x: usize, y: usize) -> Vec<String> {
        if x >= self.campaign.width
            || y >= self.campaign.height
            || self.state.pending_interaction.is_some()
            || self.state.status != "playing"
        {
            return vec![];
        }
        let width = self.campaign.width;
        let start = self.state.player.y * width + self.state.player.x;
        let target = y * width + x;
        let mut previous = BTreeMap::from([(start, (start, ""))]);
        let mut queue = VecDeque::from([start]);
        let mut best = start;
        while let Some(index) = queue.pop_front() {
            let distance = |i: usize| (i % width).abs_diff(x) + (i / width).abs_diff(y);
            if distance(index) < distance(best) {
                best = index;
            }
            if index == target {
                best = index;
                break;
            }
            for (dx, dy, direction) in [
                (0isize, -1isize, "up"),
                (-1, 0, "left"),
                (1, 0, "right"),
                (0, 1, "down"),
            ] {
                let (Some(nx), Some(ny)) = (
                    (index % width).checked_add_signed(dx),
                    (index / width).checked_add_signed(dy),
                ) else {
                    continue;
                };
                let Some(id) = self.tile_at(self.state.player.floor, nx, ny) else {
                    continue;
                };
                let next = ny * width + nx;
                if previous.contains_key(&next) {
                    continue;
                }
                let def = &self.campaign.tiles[&id.to_string()];
                if next != target && !["empty", "floor", "trigger"].contains(&def.kind.as_str()) {
                    continue;
                }
                previous.insert(next, (index, direction));
                queue.push_back(next);
            }
        }
        let mut route = vec![];
        while best != start {
            let (prev, direction) = previous[&best];
            route.push(direction.to_owned());
            best = prev;
        }
        route.reverse();
        route
    }

    fn log(&mut self, text: impl Into<String>) {
        let text = text.into();
        self.last_action["message"] = json!(text);
        self.state.log.push(text);
        if self.state.log.len() > 100 {
            self.state.log.remove(0);
        }
    }

    pub fn tile_at(&self, floor: i32, x: usize, y: usize) -> Option<u16> {
        if x >= self.campaign.width || y >= self.campaign.height {
            return None;
        }
        self.state
            .floors
            .get(&floor)?
            .get(y * self.campaign.width + x)
            .copied()
    }

    fn clear(&mut self, floor: i32, x: usize, y: usize) {
        let empty = self.campaign.rules["empty_tile"].as_u64().unwrap_or(0) as u16;
        self.set_tile(floor, x, y, empty);
    }

    fn set_tile(&mut self, floor: i32, x: usize, y: usize, tile: u16) {
        if x < self.campaign.width
            && y < self.campaign.height
            && self.campaign.tiles.contains_key(&tile.to_string())
            && let Some(tiles) = self.state.floors.get_mut(&floor)
        {
            tiles[y * self.campaign.width + x] = tile;
            self.present(
                json!({"type":"tile","floor":floor,"x":x,"y":y,"tile":tile,"duration_ms":60}),
            );
        }
    }

    fn move_player(&mut self, dx: isize, dy: isize) -> Result<(), String> {
        let p = self.state.player.clone();
        let (x, y) = (p.x.checked_add_signed(dx), p.y.checked_add_signed(dy));
        let (Some(x), Some(y)) = (x, y) else {
            return self.block("The edge of the tower blocks your path.");
        };
        let floor = p.floor;
        let Some(original_id) = self.tile_at(floor, x, y) else {
            return self.block("The edge of the tower blocks your path.");
        };
        self.run_events("bump", floor, x, y, Some(original_id));
        if self.state.status != "playing"
            || self.state.player.floor != floor
            || self.state.player.x != p.x
            || self.state.player.y != p.y
        {
            return Ok(());
        }
        let id = self
            .tile_at(floor, x, y)
            .ok_or("Event changed the destination unexpectedly")?;
        if id != original_id && self.campaign.tiles[&id.to_string()].kind == "enemy" {
            return self.block("A hidden enemy has been revealed.");
        }
        let def = self.campaign.tiles[&id.to_string()].clone();
        let mut entered = true;
        match def.kind.as_str() {
            "empty" | "floor" | "decoration" => {}
            "wall" | "solid" | "lava" | "barrier" => {
                if !def.passable {
                    return self.block("A wall blocks your path.");
                }
            }
            "hidden_wall" => {
                self.clear(floor, x, y);
                self.log("You discovered a hidden passage.");
            }
            "door" => {
                let key = def.key.as_deref().unwrap_or("yellow");
                let count = self.key_mut(key)?;
                if *count <= 0 {
                    return self.block(&format!("You need a {key} key."));
                }
                *count -= 1;
                self.clear(floor, x, y);
                self.log(format!("Opened the {key} door."));
                self.run_events("door_opened", floor, x, y, Some(id));
            }
            "special_door" => return self.block("This gate opens through a floor event."),
            "key" => {
                self.add_stat(def.key.as_deref().unwrap_or("yellow"), def.amount.max(1))?;
                self.clear(floor, x, y);
                self.log(format!("Collected {}.", def.name));
            }
            "enemy" | "monster" => {
                let enemy = self
                    .enemy(def.enemy.as_deref().ok_or("Enemy tile has no enemy")?)
                    .ok_or("Unknown enemy")?;
                let battle = forecast_with_rules(&self.state.player, &enemy, &self.campaign.rules);
                if battle.damage.is_none() {
                    return self.block(&battle.reason);
                }
                let damage = battle.damage.unwrap();
                self.present_battle(&enemy, &battle, floor, x, y, false);
                if damage >= self.state.player.hp {
                    // Original permits fatal battles; forecasts let the player plan before committing.
                    self.state.player.hp = 0;
                    self.state.status = "lost".into();
                    self.log(format!(
                        "{} defeated you. Restore a save to try another route.",
                        enemy.name
                    ));
                    return Ok(());
                }
                self.state.player.hp -= damage;
                let reward = enemy.gold
                    * if self
                        .state
                        .player
                        .inventory
                        .iter()
                        .any(|i| i == "lucky_gold")
                    {
                        2
                    } else {
                        1
                    };
                self.add_stat("gold", reward)?;
                self.clear(floor, x, y);
                if def.extra.contains_key("footprint") {
                    self.clear_large_monster(floor, &def, x, y);
                }
                self.state.player.x = x;
                self.state.player.y = y;
                self.present_move(&p, x, y, dx, dy);
                self.log(format!(
                    "Defeated {}: −{} HP, +{} gold.",
                    enemy.name, damage, reward
                ));
                self.run_events("enemy_defeated", floor, x, y, Some(id));
                entered = false;
            }
            "potion" | "gem" | "stat" | "equipment" | "gold" => {
                let stat = def.stat.as_deref().unwrap_or(if def.kind == "potion" {
                    "hp"
                } else if def.kind == "gold" {
                    "gold"
                } else {
                    "attack"
                });
                let mut amount = def.amount;
                if def
                    .extra
                    .get("scaled")
                    .and_then(Value::as_bool)
                    .unwrap_or(false)
                {
                    amount = amount.saturating_mul(self.area_multiplier(floor));
                }
                if stat != "gold" {
                    amount = amount.saturating_mul(self.cycle_multiplier());
                }
                self.add_stat(stat, amount)?;
                if let Some(item) = &def.item {
                    self.give_item(item);
                }
                self.clear(floor, x, y);
                self.log(format!("Collected {}: +{} {}.", def.name, amount, stat));
            }
            "item" => {
                self.give_item(def.item.as_deref().unwrap_or(&def.name));
                if def.item.as_deref() == Some("warp_staff") {
                    self.state
                        .player
                        .item_charges
                        .insert("warp_staff".into(), 3);
                }
                self.clear(floor, x, y);
                self.log(format!("Acquired {}.", def.name));
            }
            "stairs_up" | "stairs_down" | "stairs" => {
                let up = def.kind == "stairs_up"
                    || def.extra.get("direction").and_then(Value::as_str) == Some("up");
                let link = format!("{floor}:{}", if up { "up" } else { "down" });
                let target = def
                    .target_floor
                    .or_else(|| {
                        self.campaign.rules["stair_links"][link]
                            .as_i64()
                            .map(|v| v as i32)
                    })
                    .unwrap_or(floor + if up { 1 } else { -1 });
                if !self.state.floors.contains_key(&target) {
                    return self.block("The stairway goes no further.");
                }
                self.change_floor(target, if up { "stairs_down" } else { "stairs_up" })?;
                entered = false;
            }
            "npc" | "shop" | "altar" | "merchant" | "fairy" => {
                let local_def = self.interaction_def(floor, x, y, &def);
                self.open_interaction(floor, x, y, &local_def);
                return Ok(());
            }
            "win" => {
                self.state.status = "won".into();
                self.log("The sorcerer's tower has been conquered.");
            }
            "trigger" => {}
            _ => {
                if !def.passable {
                    return self.block(&format!("{} blocks the way.", def.name));
                }
            }
        }
        if !def.effects.is_empty() {
            self.apply_effects(&def.effects);
        }
        if entered {
            self.state.player.x = x;
            self.state.player.y = y;
            self.present_move(&p, x, y, dx, dy);
        }
        if ["key", "potion", "gem", "stat", "equipment", "gold", "item"]
            .contains(&def.kind.as_str())
        {
            self.present(json!({"type":"audio","name":"get"}));
        } else if def.kind == "door" {
            self.present(json!({"type":"audio","name":"open"}));
        }
        self.run_events(
            "step",
            self.state.player.floor,
            self.state.player.x,
            self.state.player.y,
            Some(id),
        );
        self.state.steps += 1;
        self.apply_hazards();
        Ok(())
    }

    fn area_multiplier(&self, floor: i32) -> i64 {
        self.campaign.rules["area_scaling"]
            .as_array()
            .and_then(|entries| {
                entries
                    .iter()
                    .find(|entry| floor <= entry["max_floor"].as_i64().unwrap_or(50) as i32)
            })
            .and_then(|v| v["multiplier"].as_i64())
            .unwrap_or(((floor.max(1) - 1) / 10 + 1) as i64)
    }

    fn change_floor(&mut self, target: i32, arrival_kind: &str) -> Result<(), String> {
        let tiles = self.state.floors.get(&target).ok_or("Unknown floor")?;
        let metadata = self
            .campaign
            .floors
            .iter()
            .find(|f| f.id == target)
            .and_then(|f| {
                if arrival_kind == "stairs_down" {
                    f.arrival_up.as_ref()
                } else {
                    f.arrival_down.as_ref()
                }
            });
        let index = metadata
            .map(|p| p.y * self.campaign.width + p.x)
            .or_else(|| {
                tiles
                    .iter()
                    .position(|id| self.campaign.tiles[&id.to_string()].kind == arrival_kind)
            })
            .or_else(|| {
                tiles.iter().position(|id| {
                    ["empty", "floor"].contains(&self.campaign.tiles[&id.to_string()].kind.as_str())
                })
            })
            .ok_or("Destination floor has no arrival tile")?;
        let from = self.state.player.floor;
        self.state.player.floor = target;
        self.state.player.x = index % self.campaign.width;
        self.state.player.y = index / self.campaign.width;
        self.present_floor(from, "original_spiral", None);
        self.state.visited_floors.insert(target);
        self.log(format!("Entered floor {target}."));
        self.run_events(
            "enter_floor",
            target,
            self.state.player.x,
            self.state.player.y,
            None,
        );
        Ok(())
    }

    fn key_mut(&mut self, key: &str) -> Result<&mut i64, String> {
        match key {
            "yellow" => Ok(&mut self.state.player.keys.yellow),
            "blue" => Ok(&mut self.state.player.keys.blue),
            "red" => Ok(&mut self.state.player.keys.red),
            _ => Err(format!("Unknown key: {key}")),
        }
    }

    fn add_stat(&mut self, stat: &str, amount: i64) -> Result<(), String> {
        let value = match stat {
            "hp" => &mut self.state.player.hp,
            "attack" => &mut self.state.player.attack,
            "defense" => &mut self.state.player.defense,
            "gold" => &mut self.state.player.gold,
            "yellow" | "blue" | "red" => self.key_mut(stat)?,
            _ => return Err(format!("Unknown stat: {stat}")),
        };
        *value = value.saturating_add(amount).clamp(0, 1_000_000_000);
        Ok(())
    }

    fn give_item(&mut self, item: &str) {
        if !self.state.player.inventory.iter().any(|s| s == item) {
            self.state.player.inventory.push(item.to_string());
        }
    }

    fn clear_large_monster(&mut self, floor: i32, def: &TileDef, x: usize, y: usize) {
        let Some(footprint) = def.extra.get("footprint") else {
            return;
        };
        let Some(left) = x.checked_sub(footprint["offset_x"].as_u64().unwrap_or(0) as usize) else {
            return;
        };
        let Some(top) = y.checked_sub(footprint["offset_y"].as_u64().unwrap_or(0) as usize) else {
            return;
        };
        let width = footprint["width"]
            .as_u64()
            .unwrap_or(1)
            .min(self.campaign.width as u64) as usize;
        let height = footprint["height"]
            .as_u64()
            .unwrap_or(1)
            .min(self.campaign.height as u64) as usize;
        for ny in top..top + height {
            for nx in left..left + width {
                if let Some(id) = self.tile_at(floor, nx, ny)
                    && footprint["tiles"].as_array().is_some_and(|tiles| {
                        tiles
                            .iter()
                            .any(|tile| tile.as_u64() == Some(u64::from(id)))
                    })
                {
                    self.clear(floor, nx, ny);
                }
            }
        }
    }

    fn interaction_def(&self, floor: i32, x: usize, y: usize, def: &TileDef) -> TileDef {
        let mut value = serde_json::to_value(def).expect("tile serialization");
        if let Some(local) = self.campaign.interactions.iter().find(|v| {
            v["floor"].as_i64() == Some(i64::from(floor))
                && v["x"].as_u64() == Some(x as u64)
                && v["y"].as_u64() == Some(y as u64)
        }) && let Some(object) = local.as_object()
        {
            for (key, entry) in object {
                if !["floor", "x", "y"].contains(&key.as_str()) {
                    value[key] = entry.clone();
                }
            }
        }
        serde_json::from_value(value).unwrap_or_else(|_| def.clone())
    }

    fn altar_offers(&self, floor: i32) -> Vec<Value> {
        let n = self.state.shop_visits.get("altar").copied().unwrap_or(0);
        let cost = self.campaign.rules["altar_base_cost"]
            .as_i64()
            .unwrap_or(10)
            .max(0)
            .saturating_mul(n * n + n + 2);
        let area = self.area_multiplier(floor);
        let hp = self.campaign.rules["altar_hp_gain"].as_i64().unwrap_or(100)
            * (n + 1)
            * self.cycle_multiplier();
        let attack = self.campaign.rules["altar_attack_gain"]
            .as_i64()
            .unwrap_or(2)
            * area
            * self.cycle_multiplier();
        let defense = self.campaign.rules["altar_defense_gain"]
            .as_i64()
            .unwrap_or(4)
            * area
            * self.cycle_multiplier();
        [("hp",hp),("attack",attack),("defense",defense)].iter().map(|(stat,amount)|json!({"id":stat,"label":format!("+{amount} {stat}"),"cost":cost,"effects":[{"type":"add_stat","stat":stat,"amount":amount}]})).collect()
    }

    fn open_interaction(&mut self, floor: i32, x: usize, y: usize, def: &TileDef) {
        let key = format!("{floor}:{x}:{y}");
        let visits = self.state.shop_visits.get(&key).copied().unwrap_or(0);
        let offers = if def.kind == "altar" {
            self.altar_offers(floor)
        } else {
            def.offers.clone()
        };
        let choices: Vec<Value> = offers.iter().enumerate().filter(|(i,offer)|{
            let id=offer["id"].as_str().map(str::to_owned).unwrap_or(i.to_string());
            (!offer["once"].as_bool().unwrap_or(false) || !self.state.shop_visits.contains_key(&format!("{key}:offer:{id}"))) && self.conditions_pass(&offer["conditions"])
        }).map(|(i, offer)| {
            let cost = offer["cost"].as_i64().unwrap_or(0) + offer["cost_increment"].as_i64().unwrap_or(0) * visits;
            json!({"id":offer["id"].as_str().map(str::to_owned).unwrap_or(i.to_string()),"label":format!("{} · {} gold",offer["label"].as_str().unwrap_or("Purchase"),cost),"cost":cost})
        }).chain(std::iter::once(json!({"id":"leave","label":"Continue"}))).collect();
        let after = def.extra.get("after_text");
        let text = after
            .filter(|entry| {
                self.state
                    .flags
                    .contains(entry["flag"].as_str().unwrap_or(""))
            })
            .and_then(|entry| entry["text"].as_str())
            .unwrap_or(if def.text.is_empty() {
                &def.description
            } else {
                &def.text
            });
        self.state.pending_interaction =
            Some(json!({"title":def.name,"text":text,"choices":choices}));
        self.state.pending_tile = Some((floor, x, y));
    }

    fn choose(&mut self, choice: &str) -> Result<(), String> {
        let Some((floor, x, y)) = self.state.pending_tile else {
            return self.block("There is no conversation to respond to.");
        };
        let id = self
            .tile_at(floor, x, y)
            .ok_or("Interaction location is invalid")?;
        let def = self.interaction_def(floor, x, y, &self.campaign.tiles[&id.to_string()]);
        if choice == "leave" {
            if def.offers.is_empty() {
                self.apply_effects(&def.effects);
                self.run_events("interact", floor, x, y, Some(id));
                if def
                    .extra
                    .get("disappear")
                    .and_then(Value::as_bool)
                    .unwrap_or(false)
                {
                    self.clear(floor, x, y);
                }
            }
            self.state.pending_interaction = None;
            self.state.pending_tile = None;
            return Ok(());
        }
        let offers = if def.kind == "altar" {
            self.altar_offers(floor)
        } else {
            def.offers.clone()
        };
        let offer = offers
            .iter()
            .enumerate()
            .find(|(i, o)| o["id"].as_str().map(str::to_owned).unwrap_or(i.to_string()) == choice)
            .map(|(_, o)| o.clone())
            .ok_or("Unknown offer")?;
        let key = if def.kind == "altar" {
            "altar".into()
        } else {
            format!("{floor}:{x}:{y}")
        };
        let offer_key = format!("{key}:offer:{choice}");
        if offer["once"].as_bool().unwrap_or(false)
            && self.state.shop_visits.contains_key(&offer_key)
        {
            return self.block("This offer has already been purchased.");
        }
        let visits = self.state.shop_visits.get(&key).copied().unwrap_or(0);
        let cost = offer["cost"].as_i64().unwrap_or(0)
            + offer["cost_increment"].as_i64().unwrap_or(0) * visits;
        if self.state.player.gold < cost {
            return self.block("You do not have enough gold.");
        }
        if let Some(conditions) = offer.get("conditions")
            && !self.conditions_pass(conditions)
        {
            return self.block("You do not meet the requirements for this trade.");
        }
        self.state.player.gold -= cost;
        self.apply_effects(
            offer["effects"]
                .as_array()
                .map(Vec::as_slice)
                .unwrap_or(&[]),
        );
        self.state.shop_visits.insert(key, visits + 1);
        self.log(format!(
            "{} purchased for {cost} gold.",
            offer["label"].as_str().unwrap_or("Upgrade")
        ));
        if offer["once"].as_bool().unwrap_or(false) {
            self.state.shop_visits.insert(offer_key, 1);
        }
        self.open_interaction(floor, x, y, &def);
        Ok(())
    }

    fn use_item(&mut self, item: &str, command: &Value) -> Result<(), String> {
        if !self.state.player.inventory.iter().any(|s| s == item) {
            return self.block("You do not own that item.");
        }
        if self.state.pending_interaction.is_some() {
            return self.block("Dismiss the conversation before using an item.");
        }
        let floor = self.state.player.floor;
        let (x, y) = (self.state.player.x, self.state.player.y);
        let mut consume = true;
        match item {
            "hero_orb" | "monster_book" | "wisdom_orb" | "cross" | "dragon_slayer"
            | "lucky_gold" | "sacred_shield" => {
                consume = false;
                self.log("The item is always active.");
            }
            "orb_of_flying" | "floor_wand" | "flying_orb" => {
                let target = command["floor"]
                    .as_i64()
                    .ok_or("Choose a destination floor")? as i32;
                if !self.state.visited_floors.contains(&target) {
                    return self.block("The Orb of Flying only reaches visited floors.");
                }
                let adjacent_stairs = [
                    (x, y),
                    (x.wrapping_sub(1), y),
                    (x + 1, y),
                    (x, y.wrapping_sub(1)),
                    (x, y + 1),
                ]
                .iter()
                .any(|(nx, ny)| {
                    self.tile_at(floor, *nx, *ny).is_some_and(|id| {
                        ["stairs_up", "stairs_down"]
                            .contains(&self.campaign.tiles[&id.to_string()].kind.as_str())
                    })
                });
                if self.campaign.rules["flying_requires_stairs"]
                    .as_bool()
                    .unwrap_or(true)
                    && !adjacent_stairs
                {
                    return self.block("Stand beside a staircase to use the Orb of Flying.");
                }
                self.change_floor(
                    target,
                    if target > floor {
                        "stairs_down"
                    } else {
                        "stairs_up"
                    },
                )?;
                consume = false;
            }
            "mattock" => {
                let mut count = 0;
                for (nx, ny) in [
                    (x.wrapping_sub(1), y),
                    (x + 1, y),
                    (x, y.wrapping_sub(1)),
                    (x, y + 1),
                ] {
                    if let Some(id) = self.tile_at(floor, nx, ny)
                        && self.campaign.tiles[&id.to_string()].kind == "wall"
                    {
                        self.clear(floor, nx, ny);
                        count += 1;
                    }
                }
                if count == 0 {
                    return self.block("No adjacent walls to break.");
                }
                self.log(format!("The mattock broke {count} walls."));
            }
            "magic_key" => {
                let tiles = self.state.floors[&floor].clone();
                let mut count = 0;
                for (i, id) in tiles.iter().enumerate() {
                    let def = &self.campaign.tiles[&id.to_string()];
                    if def.kind == "door" && def.key.as_deref() == Some("yellow") {
                        self.clear(floor, i % self.campaign.width, i / self.campaign.width);
                        count += 1;
                    }
                }
                if count == 0 {
                    return self.block("No yellow doors on this floor.");
                }
                self.log("The Magic Key opened every yellow door on this floor.");
            }
            "bomb" => {
                let mut count = 0;
                let mut reward = 0;
                for ny in y.saturating_sub(1)..=(y + 1).min(self.campaign.height - 1) {
                    for nx in x.saturating_sub(1)..=(x + 1).min(self.campaign.width - 1) {
                        if let Some(id) = self.tile_at(floor, nx, ny)
                            && self.campaign.tiles[&id.to_string()].kind == "enemy"
                        {
                            let allowed = self.campaign.rules["bomb_tile_ranges"]
                                .as_array()
                                .map(|ranges| {
                                    ranges.iter().any(|range| {
                                        range[0].as_u64().is_some_and(|v| u64::from(id) >= v)
                                            && range[1].as_u64().is_some_and(|v| u64::from(id) <= v)
                                    })
                                })
                                .unwrap_or(
                                    (61..=90).contains(&id)
                                        || (93..=96).contains(&id)
                                        || (133..=144).contains(&id)
                                        || (147..=158).contains(&id),
                                );
                            if allowed {
                                reward += self.campaign.tiles[&id.to_string()]
                                    .enemy
                                    .as_ref()
                                    .and_then(|e| self.enemy(e))
                                    .map(|e| e.gold)
                                    .unwrap_or(0);
                                self.clear(floor, nx, ny);
                                count += 1;
                                self.run_events("enemy_defeated", floor, nx, ny, Some(id));
                            }
                        }
                    }
                }
                if count == 0 {
                    return self.block("No nearby enemies can be destroyed.");
                }
                self.add_stat("gold", reward)?;
                self.log(format!(
                    "The bomb destroyed {count} enemies: +{reward} gold."
                ));
            }
            "holy_water" | "elixir" => {
                let hp = self
                    .state
                    .player
                    .attack
                    .saturating_mul(10)
                    .saturating_add(self.state.player.defense.saturating_mul(5));
                self.add_stat("hp", hp)?;
                self.log(format!("The elixir restored {hp} HP."));
            }
            "orb_of_ascending" | "orb_of_descending" | "up_wing" | "down_wing" => {
                let target = floor
                    + if ["orb_of_ascending", "up_wing"].contains(&item) {
                        1
                    } else {
                        -1
                    };
                if !self.tile_at(target, x, y).is_some_and(|id| {
                    id == self.campaign.rules["empty_tile"].as_u64().unwrap_or(6) as u16
                }) {
                    return self.block(
                        "The destination must be an ordinary passage at the same coordinates.",
                    );
                }
                self.state.player.floor = target;
                self.state.visited_floors.insert(target);
                self.present_floor(floor, "original_spiral", None);
                self.run_events("enter_floor", target, x, y, None);
                self.log(format!("The wing carried you to floor {target}."));
            }
            "warp_staff" => {
                let charges = self
                    .state
                    .player
                    .item_charges
                    .entry("warp_staff".into())
                    .or_insert(3);
                if *charges == 0 {
                    return self.block("The Warp Staff has no charges remaining.");
                }
                *charges -= 1;
                consume = *charges == 0;
                let (nx, ny) = (self.campaign.width - 1 - x, self.campaign.height - 1 - y);
                if self.tile_at(floor, nx, ny)
                    == Some(self.campaign.rules["empty_tile"].as_u64().unwrap_or(6) as u16)
                {
                    self.state.player.x = nx;
                    self.state.player.y = ny;
                    self.run_events("step", floor, nx, ny, None);
                    self.log("The Warp Staff carried you across the floor.");
                } else {
                    self.log("The Warp Staff used a charge, but the destination is blocked.");
                }
            }
            "super_mattock" => {
                let tiles = self.state.floors[&floor].clone();
                let mut count = 0;
                for (i, id) in tiles.iter().enumerate() {
                    if self.campaign.tiles[&id.to_string()].kind == "wall" && *id == 8 {
                        self.clear(floor, i % self.campaign.width, i / self.campaign.width);
                        count += 1;
                    }
                }
                if count == 0 {
                    return self.block("There are no ordinary walls to remove.");
                }
                self.log(format!("The Super Mattock removed {count} walls."));
            }
            "snow_crystal" => {
                consume = false;
                let mut pending = vec![
                    (x.wrapping_sub(1), y),
                    (x + 1, y),
                    (x, y.wrapping_sub(1)),
                    (x, y + 1),
                ];
                let mut count = 0;
                while let Some((nx, ny)) = pending.pop() {
                    if let Some(id) = self.tile_at(floor, nx, ny)
                        && self.campaign.tiles[&id.to_string()].kind == "lava"
                    {
                        self.clear(floor, nx, ny);
                        count += 1;
                        pending.extend([
                            (nx.wrapping_sub(1), ny),
                            (nx + 1, ny),
                            (nx, ny.wrapping_sub(1)),
                            (nx, ny + 1),
                        ]);
                    }
                }
                if count == 0 {
                    return self.block("There is no adjacent lava to cool.");
                }
                self.log(format!("The Snow Crystal cooled {count} lava tiles."));
            }
            _ => {
                let def =
                    self.campaign.items.get(item).cloned().ok_or_else(|| {
                        format!("Item {item} is passive or has no configured action")
                    })?;
                self.apply_effects(def["effects"].as_array().map(Vec::as_slice).unwrap_or(&[]));
                consume = def["consumable"].as_bool().unwrap_or(true);
            }
        }
        if consume {
            self.state.player.inventory.retain(|s| s != item);
        }
        Ok(())
    }

    fn apply_hazards(&mut self) {
        let p = self.state.player.clone();
        if p.inventory.iter().any(|s| s == "sacred_shield") {
            return;
        }
        let special_at = |x: usize, y: usize| {
            self.tile_at(p.floor, x, y)
                .and_then(|id| self.campaign.tiles[&id.to_string()].enemy.as_ref())
                .and_then(|id| self.enemy(id))
                .map(|e| e.special)
                .unwrap_or_default()
        };
        let mut damage = 0;
        for (x, y) in [
            (p.x.wrapping_sub(1), p.y),
            (p.x + 1, p.y),
            (p.x, p.y.wrapping_sub(1)),
            (p.x, p.y + 1),
        ] {
            damage += match special_at(x, y).as_str() {
                "magician_a" => {
                    self.campaign.rules["magician_a_damage"]
                        .as_i64()
                        .unwrap_or(200)
                        .max(0)
                        * self.cycle_multiplier()
                }
                "magician_b" => {
                    self.campaign.rules["magician_b_damage"]
                        .as_i64()
                        .unwrap_or(100)
                        .max(0)
                        * self.cycle_multiplier()
                }
                _ => 0,
            };
        }
        if (special_at(p.x.wrapping_sub(1), p.y) == "sorcerer"
            && special_at(p.x + 1, p.y) == "sorcerer")
            || (special_at(p.x, p.y.wrapping_sub(1)) == "sorcerer"
                && special_at(p.x, p.y + 1) == "sorcerer")
        {
            damage += (p.hp + 1) / 2;
        }
        if damage > 0 {
            self.state.player.hp = (self.state.player.hp - damage).max(0);
            self.log(format!("Magic field: −{damage} HP."));
        }
        if self.state.player.hp == 0 {
            self.state.status = "lost".into();
        }
    }

    fn run_events(&mut self, kind: &str, floor: i32, x: usize, y: usize, tile: Option<u16>) {
        let cycle = self.state.cycle;
        let events = self.campaign.events.clone();
        for (index, event) in events.iter().enumerate() {
            let trigger = &event["trigger"];
            if trigger["type"].as_str() != Some(kind)
                || trigger["floor"]
                    .as_i64()
                    .is_some_and(|f| f != i64::from(floor))
                || trigger["x"].as_u64().is_some_and(|v| v != x as u64)
                || trigger["y"].as_u64().is_some_and(|v| v != y as u64)
                || trigger["tile"]
                    .as_u64()
                    .is_some_and(|v| Some(v as u16) != tile)
            {
                continue;
            }
            let key = event["id"]
                .as_str()
                .map(str::to_owned)
                .unwrap_or(index.to_string());
            if event["once"].as_bool().unwrap_or(true) && self.state.event_counts.contains_key(&key)
            {
                continue;
            }
            if !self.conditions_pass(&event["conditions"]) {
                continue;
            }
            *self.state.event_counts.entry(key).or_default() += 1;
            self.apply_effects(
                event["effects"]
                    .as_array()
                    .map(Vec::as_slice)
                    .unwrap_or(&[]),
            );
            if self.state.cycle != cycle {
                break;
            }
        }
    }

    fn conditions_pass(&self, conditions: &Value) -> bool {
        conditions.as_array().is_none_or(|list| {
            list.iter().all(|c| match c["type"].as_str().unwrap_or("") {
                "flag" => {
                    self.state.flags.contains(c["flag"].as_str().unwrap_or(""))
                        == c["value"].as_bool().unwrap_or(true)
                }
                "has_item" => self
                    .state
                    .player
                    .inventory
                    .iter()
                    .any(|i| Some(i.as_str()) == c["item"].as_str()),
                "tile" => self
                    .tile_at(
                        c["floor"]
                            .as_i64()
                            .unwrap_or(i64::from(self.state.player.floor))
                            as i32,
                        c["x"].as_u64().unwrap_or(0) as usize,
                        c["y"].as_u64().unwrap_or(0) as usize,
                    )
                    .is_some_and(|t| Some(u64::from(t)) == c["tile"].as_u64()),
                "no_enemies" => self
                    .state
                    .floors
                    .get(
                        &(c["floor"]
                            .as_i64()
                            .unwrap_or(i64::from(self.state.player.floor))
                            as i32),
                    )
                    .is_some_and(|tiles| {
                        !tiles
                            .iter()
                            .any(|id| self.campaign.tiles[&id.to_string()].enemy.is_some())
                    }),
                "stat_at_least" => self
                    .stat_value(c["stat"].as_str().unwrap_or(""))
                    .is_some_and(|value| value >= c["amount"].as_i64().unwrap_or(i64::MAX)),
                "stat_at_most" => self
                    .stat_value(c["stat"].as_str().unwrap_or(""))
                    .is_some_and(|value| value <= c["amount"].as_i64().unwrap_or(i64::MIN)),
                "cycle_at_least" => {
                    u64::from(self.state.cycle)
                        >= c["cycle"]
                            .as_u64()
                            .or_else(|| c["amount"].as_u64())
                            .unwrap_or(1)
                }
                "cycle_at_most" => {
                    u64::from(self.state.cycle)
                        <= c["cycle"]
                            .as_u64()
                            .or_else(|| c["amount"].as_u64())
                            .unwrap_or(1)
                }
                "any" => c["conditions"].as_array().is_some_and(|conditions| {
                    conditions
                        .iter()
                        .any(|condition| self.conditions_pass(&json!([condition])))
                }),
                _ => false,
            })
        })
    }

    fn stat_value(&self, stat: &str) -> Option<i64> {
        let p = &self.state.player;
        match stat {
            "hp" => Some(p.hp),
            "attack" => Some(p.attack),
            "defense" => Some(p.defense),
            "gold" => Some(p.gold),
            "yellow" => Some(p.keys.yellow),
            "blue" => Some(p.keys.blue),
            "red" => Some(p.keys.red),
            _ => None,
        }
    }

    fn apply_effects(&mut self, effects: &[Value]) {
        for effect in effects {
            if self.state.status == "lost" {
                break;
            }
            if !self.conditions_pass(&effect["conditions"]) {
                continue;
            }
            match effect["type"].as_str().unwrap_or("") {
                "message" => {
                    self.log(effect["text"].as_str().unwrap_or(""));
                    self.present(json!({"type":"dialogue","text":effect["text"],"dialogue_id":effect["dialogue_id"],"duration_ms":effect["duration_ms"].as_u64().unwrap_or(0)}));
                },
                "wait" => self.present(json!({"type":"wait","duration_ms":effect["ms"].as_u64().unwrap_or(120).min(30_000)})),
                "sound" => self.present(json!({"type":"audio","name":effect["cue"]})),
                "cinematic" => self.present(effect.clone()),
                "move_tile" => {
                    let floor = effect["floor"].as_i64().unwrap_or(i64::from(self.state.player.floor)) as i32;
                    let from_x = effect["from_x"].as_u64().unwrap_or(0) as usize;
                    let from_y = effect["from_y"].as_u64().unwrap_or(0) as usize;
                    let x = effect["x"].as_u64().unwrap_or(0) as usize;
                    let y = effect["y"].as_u64().unwrap_or(0) as usize;
                    if let Some(tile) = self.tile_at(floor, from_x, from_y)
                        && x < self.campaign.width && y < self.campaign.height {
                            if let Some(tiles) = self.state.floors.get_mut(&floor) {
                                tiles[from_y * self.campaign.width + from_x] = self.campaign.rules["empty_tile"].as_u64().unwrap_or(0) as u16;
                                tiles[y * self.campaign.width + x] = tile;
                            }
                            self.present(json!({"type":"move_tile","floor":floor,"from_x":from_x,"from_y":from_y,"x":x,"y":y,"tile":tile,"duration_ms":effect["duration_ms"].as_u64().unwrap_or(120)}));
                    }
                },
                "next_cycle" => self.next_cycle(),
                "flag" => {
                    let key = effect["flag"].as_str().unwrap_or("").to_string();
                    if effect["value"].as_bool().unwrap_or(true) {
                        self.state.flags.insert(key);
                    } else {
                        self.state.flags.remove(&key);
                    }
                }
                "set_tile" => self.set_tile(
                    effect["floor"]
                        .as_i64()
                        .unwrap_or(i64::from(self.state.player.floor)) as i32,
                    effect["x"].as_u64().unwrap_or(0) as usize,
                    effect["y"].as_u64().unwrap_or(0) as usize,
                    effect["tile"].as_u64().unwrap_or(0) as u16,
                ),
                "add_stat" => {
                    let _ = self.add_stat(
                        effect["stat"].as_str().unwrap_or("hp"),
                        effect["amount"].as_i64().unwrap_or(0),
                    );
                }
                "set_stat" => {
                    let stat = effect["stat"].as_str().unwrap_or("hp");
                    let old = match stat {
                        "hp" => self.state.player.hp,
                        "attack" => self.state.player.attack,
                        "defense" => self.state.player.defense,
                        "gold" => self.state.player.gold,
                        "yellow" => self.state.player.keys.yellow,
                        "blue" => self.state.player.keys.blue,
                        "red" => self.state.player.keys.red,
                        _ => 0,
                    };
                    let _ = self.add_stat(
                        stat,
                        effect["amount"].as_i64().unwrap_or(0).saturating_sub(old),
                    );
                }
                "multiply_stat" => {
                    let stat = effect["stat"].as_str().unwrap_or("hp");
                    let old = self.stat_value(stat).unwrap_or(0);
                    let numerator = effect["numerator"].as_i64().unwrap_or(1);
                    let denominator = effect["denominator"].as_i64().unwrap_or(1).max(1);
                    let _ = self.add_stat(stat, old.saturating_mul(numerator) / denominator - old);
                }
                "give_item" => self.give_item(effect["item"].as_str().unwrap_or("")),
                "remove_item" => self
                    .state
                    .player
                    .inventory
                    .retain(|s| Some(s.as_str()) != effect["item"].as_str()),
                "clear_inventory" => {
                    self.state.player.inventory.clear();
                    self.state.player.item_charges.clear();
                }
                "set_charges" => {
                    self.state.player.item_charges.insert(
                        effect["item"].as_str().unwrap_or("").into(),
                        effect["charges"]
                            .as_u64()
                            .unwrap_or(0)
                            .min(u64::from(u32::MAX)) as u32,
                    );
                }
                "set_visited" => {
                    if let Some(floors) = effect["floors"].as_array() {
                        self.state.visited_floors = floors
                            .iter()
                            .filter_map(Value::as_i64)
                            .map(|v| v as i32)
                            .filter(|floor| self.state.floors.contains_key(floor))
                            .collect();
                        self.state.visited_floors.insert(self.state.player.floor);
                    }
                }
                "set_enemy" => {
                    let key = effect["enemy"].as_str().unwrap_or("");
                    if let Some(mut enemy) = self.state.enemy_overrides.get(key).or_else(||self.campaign.enemies.get(key)).cloned() {
                        for stat in ["hp", "attack", "defense", "gold"] {
                            if let Some(value) = effect[stat].as_i64() {
                                match stat {
                                    "hp" => enemy.hp = value.max(1),
                                    "attack" => enemy.attack = value.max(0),
                                    "defense" => enemy.defense = value.max(0),
                                    _ => enemy.gold = value.max(0),
                                }
                            }
                        }
                        self.state.enemy_overrides.insert(key.into(), enemy);
                    }
                }
                "battle_at" => self.forced_battle(effect),
                "teleport" => {
                    let floor = effect["floor"]
                        .as_i64()
                        .unwrap_or(i64::from(self.state.player.floor))
                        as i32;
                    let x = effect["x"].as_u64().unwrap_or(0) as usize;
                    let y = effect["y"].as_u64().unwrap_or(0) as usize;
                    if self.tile_at(floor, x, y).is_some() {
                        let from = self.state.player.floor;
                        self.state.player.floor = floor;
                        self.state.player.x = x;
                        self.state.player.y = y;
                        self.present_floor(from, effect["transition"].as_str().unwrap_or("original_spiral"), effect["duration_ms"].as_u64());
                        self.state.visited_floors.insert(floor);
                    }
                }
                "win" => {
                    self.state.status = "won".into();
                    self.log("You conquered the Tower of the Sorcerer.");
                }
                _ => {}
            }
        }
    }

    fn forced_battle(&mut self, effect: &Value) {
        let floor = effect["floor"]
            .as_i64()
            .unwrap_or(i64::from(self.state.player.floor)) as i32;
        let x = effect["x"].as_u64().unwrap_or(self.state.player.x as u64) as usize;
        let y = effect["y"].as_u64().unwrap_or(self.state.player.y as u64) as usize;
        let Some(id) = self.tile_at(floor, x, y) else {
            return;
        };
        let def = self.campaign.tiles[&id.to_string()].clone();
        let Some(enemy) = def.enemy.as_ref().and_then(|key| self.enemy(key)) else {
            return;
        };
        let result = forecast_with_rules(&self.state.player, &enemy, &self.campaign.rules);
        self.present_battle(
            &enemy,
            &result,
            floor,
            x,
            y,
            effect["first_strike"].as_bool().unwrap_or(false),
        );
        let damage = result
            .damage
            .unwrap_or(self.state.player.hp)
            .saturating_add(
                if effect["first_strike"].as_bool().unwrap_or(false)
                    && self.campaign.rules["hero_attacks_first"]
                        .as_bool()
                        .unwrap_or(true)
                {
                    (enemy.attack - self.state.player.defense).max(0)
                } else {
                    0
                },
            );
        if damage >= self.state.player.hp {
            self.state.player.hp = 0;
            self.state.status = "lost".into();
            self.log(format!("{} defeated you in the ambush.", enemy.name));
            return;
        }
        self.state.player.hp -= damage;
        let gold = enemy.gold
            * if self
                .state
                .player
                .inventory
                .iter()
                .any(|i| i == "lucky_gold")
            {
                2
            } else {
                1
            };
        let _ = self.add_stat("gold", gold);
        self.clear(floor, x, y);
        if def.extra.contains_key("footprint") {
            self.clear_large_monster(floor, &def, x, y);
        }
        self.log(format!(
            "Ambush: defeated {} (−{damage} HP, +{gold} gold).",
            enemy.name
        ));
        self.run_events("enemy_defeated", floor, x, y, Some(id));
    }

    fn next_cycle(&mut self) {
        if !self.campaign.rules["backside"]["enabled"]
            .as_bool()
            .unwrap_or(false)
        {
            self.state.status = "won".into();
            self.log("You conquered the Tower of the Sorcerer.");
            return;
        }
        let player = self.state.player.clone();
        let cycle = self.state.cycle.saturating_add(1).min(1000);
        let mut fresh = Self::new(self.campaign.clone()).state;
        fresh.cycle = cycle;
        if self.campaign.rules["backside"]["carry_stats"]
            .as_bool()
            .unwrap_or(true)
        {
            fresh.player.hp = player.hp;
            fresh.player.attack = player.attack;
            fresh.player.defense = player.defense;
        }
        if cycle > 2
            || !self.campaign.rules["backside"]["reset_gold"]
                .as_bool()
                .unwrap_or(true)
        {
            fresh.player.gold = player.gold;
        }
        if cycle > 2 {
            for item in player.inventory {
                if !fresh.player.inventory.contains(&item) {
                    fresh.player.inventory.push(item);
                }
            }
            fresh.player.item_charges = player.item_charges;
        }
        fresh.flags.insert("backside".into());
        fresh.log = self.state.log.clone();
        fresh.steps = self.state.steps;
        self.state = fresh;
        self.present(json!({"type":"floor","from":player.floor,"to":self.state.player.floor,"x":self.state.player.x,"y":self.state.player.y,"player":self.state.player,"tiles":self.state.floors.get(&self.state.player.floor),"style":"fade","sound":"none","direction":"down","duration_ms":900}));
        self.log(format!(
            "Entered the backside tower, cycle {cycle}. Monster and treasure statistics are ×{}.",
            self.cycle_multiplier()
        ));
    }
}

/// Stable FNV-1a over the canonical campaign, independent of host/wasm hashers.
fn fingerprint(source: &str) -> String {
    let mut hash = 0xcbf29ce484222325u64;
    for byte in source.bytes() {
        hash ^= u64::from(byte);
        hash = hash.wrapping_mul(0x100000001b3);
    }
    format!("{hash:016x}")
}
