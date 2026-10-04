//! Deterministic, platform-independent Tower of the Sorcerer simulation.
//! Campaign geometry, tile behavior, statistics, shops and events come from JSON.
mod battle_log;
mod campaign;
mod combat;
mod command;
mod domain;
mod events;
mod flight;
mod interactions;
mod items;
mod navigation;
mod observation;
mod original;
mod persistence;
mod presentation;
mod stats;
use persistence::{Encounter, JournalEntry, MAX_CYCLE, SAVE_VERSION, Save, fingerprint};

use campaign::MAX_STAT;
pub use campaign::{Campaign, Enemy, Floor, Keys, Player, Position, TileDef};
use combat::forecast_with_rules;
pub use combat::{Forecast, forecast};
pub use command::{Command, CommandError, Direction};
use domain::GameStatus;
pub use domain::{EnemySpecial, KeyColor, Stat, TileKind};
use events::{CompiledScripts, Effect, TriggerKind};
use original::*;
use serde_json::{Value, json};
use std::collections::{BTreeMap, BTreeSet};

#[derive(Clone)]
pub struct Engine {
    campaign: Campaign,
    scripts: CompiledScripts,
    state: Save,
    last_action: Value,
}

impl Engine {
    pub fn from_json(source: &str) -> Result<Self, String> {
        let campaign: Campaign =
            serde_json::from_str(source).map_err(|e| format!("Invalid campaign: {e}"))?;
        Self::new(campaign)
    }

    /// Validate authored input before constructing any playable state.
    pub fn new(campaign: Campaign) -> Result<Self, String> {
        campaign.validate()?;
        let scripts = CompiledScripts::compile(&campaign)?;
        let source = serde_json::to_string(&campaign)
            .expect("Campaign fields have an infallible JSON representation");
        let start = serde_json::to_string(&campaign.start)
            .expect("Player fields have an infallible JSON representation");
        // Saves need explicit null slots, but an empty authored slot has the
        // same campaign identity as older campaigns that omitted these fields.
        let canonical_start = start
            .replace(",\"weapon\":null", "")
            .replace(",\"shield\":null", "");
        let fingerprint = fingerprint(&source.replacen(
            &format!("\"start\":{start}"),
            &format!("\"start\":{canonical_start}"),
            1,
        ));
        let state = Self::initial_state(&campaign, fingerprint);
        Ok(Self {
            campaign,
            scripts,
            state,
            last_action: json!({"ok":true,"message":"Journey started"}),
        })
    }

    // Reset from already validated data; replaying a campaign never reparses it.
    fn initial_state(campaign: &Campaign, fingerprint: String) -> Save {
        Save {
            version: SAVE_VERSION,
            campaign_id: campaign.id.clone(),
            campaign_fingerprint: fingerprint,
            player: campaign.initial_player(),
            floors: campaign
                .floors
                .iter()
                .map(|f| (f.id, f.tiles.clone()))
                .collect(),
            visited_floors: BTreeSet::from([campaign.start.floor]),
            highest_stair_floor: Some(campaign.start.floor),
            flags: BTreeSet::new(),
            event_counts: BTreeMap::new(),
            shop_visits: BTreeMap::new(),
            log: vec![
                "Your journey begins. Every battle is deterministic; plan your route carefully."
                    .into(),
            ],
            log_start: 0,
            battle_log: vec![],
            journal: vec![],
            last_encounter: None,
            status: GameStatus::Playing,
            steps: 0,
            pending_interaction: None,
            pending_tile: None,
            enemy_overrides: BTreeMap::new(),
            cycle: 1,
        }
    }

    /// Campaign editing happens outside the engine, followed by reconstruction.
    /// A shared reference keeps the compiled behavior consistent with its source.
    pub fn campaign(&self) -> &Campaign {
        &self.campaign
    }

    pub fn player(&self) -> &Player {
        &self.state.player
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
                        .expect("Forecast fields have an infallible JSON representation");
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
            "inventory_items":p.inventory.iter().filter(|item|!self.campaign.is_equipment(item)).map(|item|self.owned_item_metadata(item)).collect::<Vec<_>>(),
            "equipment":{"weapon":p.weapon.as_deref().map(|item|self.owned_item_metadata(item)),"shield":p.shield.as_deref().map(|item|self.owned_item_metadata(item))},
            "abilities":{"field_magic_protection":p.inventory.iter().any(|item|item=="sacred_shield")},
            "last_encounter":self.state.last_encounter,
            "log": self.state.log, "log_start":self.state.log_start, "battle_log":self.state.battle_log,
            "status": self.state.status, "steps": self.state.steps,
            "journal": self.player_journal(), "journal_unlocked": self.journal_unlocked(),
            "save_unlocked": self.save_unlocked(),
            "flags": self.state.flags, "last_action": self.last_action,
            "cycle": self.state.cycle, "backside_multiplier": self.cycle_multiplier(),
            "forecasts_unlocked": self.forecasts_unlocked(),
        })
    }

    fn owned_item_metadata(&self, item: &str) -> Value {
        let definition = self
            .campaign
            .tiles
            .values()
            .find(|def| def.item.as_deref() == Some(item));
        let usage = self.item_usage(item);
        let usable = usage["activation"] == "use_item";
        let charges = usage
            .get("remaining_charges")
            .cloned()
            .unwrap_or_else(|| json!(self.state.player.item_charges.get(item)));
        json!({"id":item,"name":definition.map(|def|def.name.as_str()).unwrap_or(item),"sprite":definition.map(|def|&def.sprite),"usable":usable,"charges":charges,"usage":usage})
    }

    /// Contact reveals the three numbers shown by the original encounter form,
    /// before its attack/defense guard. It does not unlock advance forecasts.
    pub(crate) fn record_enemy_encounter(
        &mut self,
        enemy: &Enemy,
        floor: i32,
        x: usize,
        y: usize,
        tile: u16,
    ) {
        self.state.last_encounter = Some(Encounter {
            cycle: self.state.cycle,
            floor,
            x,
            y,
            tile,
            enemy_name: if enemy.name.trim().is_empty() {
                self.campaign
                    .tiles
                    .get(&tile.to_string())
                    .map(|definition| definition.name.trim())
                    .filter(|name| !name.is_empty())
                    .unwrap_or("Enemy")
                    .to_owned()
            } else {
                enemy.name.clone()
            },
            hp: enemy.hp,
            attack: enemy.attack,
            defense: enemy.defense,
        });
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
        let concealed = def.kind == TileKind::HiddenWall;
        let encountered_enemy = self.state.last_encounter.as_ref().filter(|encounter| {
            !noncombat
                && def.enemy.is_some()
                && encounter.floor == self.state.player.floor
                && encounter.x == x
                && encounter.y == y
                && encounter.tile == id
        });
        json!({"id":id,"x":x,"y":y,"name":if concealed{"Brick wall"}else{&def.name},"description":if concealed{"A solid wall."}else if noncombat{"Approach this character to complete the adventure."}else{&def.description},"kind":if concealed{"wall"}else if noncombat{"npc"}else{def.kind.as_str()},"enemy":enemy,"encountered_enemy":encountered_enemy,"details_locked":def.enemy.is_some() && !noncombat && !self.forecasts_unlocked()})
    }

    fn noncombat_encounter(&self, floor: i32, x: usize, y: usize, tile: u16) -> bool {
        self.scripts.events.iter().any(|event| {
            event
                .trigger
                .matches(TriggerKind::Bump, floor, x, y, Some(tile))
                && self.conditions_pass(&event.conditions)
                && event.effects.iter().any(|effect| {
                    matches!(effect.operation, Effect::Win | Effect::NextCycle)
                        && self.conditions_pass(&effect.conditions)
                })
        })
    }

    /// Compatibility boundary for callers already holding a JSON value.
    pub fn command(&mut self, value: Value) -> Result<(), String> {
        self.execute(Command::from_value(value).map_err(|error| error.to_string())?)
    }

    pub fn command_json(&mut self, source: &str) -> Result<(), CommandError> {
        self.execute(Command::from_json(source)?)
            .map_err(CommandError::Execution)
    }

    /// Malformed input is rejected before state or presentation is changed.
    /// A valid but blocked action returns Ok and sets last_action.ok to false.
    pub fn execute(&mut self, command: Command) -> Result<(), String> {
        command.validate().map_err(|error| error.to_string())?;
        self.last_action = json!({"ok":true,"type":command.kind(),"presentation":[]});
        match command {
            Command::NewGame => {
                self.state =
                    Self::initial_state(&self.campaign, self.state.campaign_fingerprint.clone());
                self.last_action = json!({"ok":true,"message":"Journey started"});
                Ok(())
            }
            Command::Cancel => {
                self.state.pending_interaction = None;
                self.state.pending_tile = None;
                Ok(())
            }
            _ if self.state.status != GameStatus::Playing => {
                self.block("This journey has ended. Start a new game or load a save.")
            }
            Command::Move { direction } => {
                if self.state.pending_interaction.is_some() {
                    return self.block("Finish or dismiss the current conversation first.");
                }
                let (dx, dy) = direction.delta();
                self.move_player(dx as isize, dy as isize)
            }
            Command::Choose { choice } => self.choose(&choice),
            Command::UseItem { item, floor } => self.use_item(&item, floor),
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
        enemy.hp = enemy.hp.saturating_mul(factor).min(MAX_STAT);
        enemy.attack = enemy.attack.saturating_mul(factor).min(MAX_STAT);
        enemy.defense = enemy.defense.saturating_mul(factor).min(MAX_STAT);
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
        let changes_stats = self.scripts.events.iter().any(|event| {
            event
                .trigger
                .matches(TriggerKind::Bump, floor, x, y, Some(tile))
                && self.conditions_pass(&event.conditions)
                && event.effects.iter().any(|effect| {
                    matches!(&effect.operation, Effect::SetEnemy { enemy, .. } if enemy == key)
                        && self.conditions_pass(&effect.conditions)
                })
        });

        if changes_stats {
            let mut preview = self.clone();
            preview.run_events(TriggerKind::Bump, floor, x, y, Some(tile));
            preview.enemy_for_tile(key, tile)
        } else {
            self.enemy_for_tile(key, tile)
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
                .unwrap_or(BACKSIDE_MULTIPLIER)
                .clamp(1, 1000)
        } else {
            1
        }
    }

    fn log(&mut self, text: impl Into<String>) {
        let text = text.into();
        self.last_action["message"] = json!(text);
        self.state.log.push(text);
        let trimmed = self.state.log.len().saturating_sub(100);
        if trimmed > 0 {
            self.state.log.drain(..trimmed);
            self.state.log_start = self.state.log_start.saturating_add(trimmed as u64);
            self.state
                .battle_log
                .retain(|entry| entry.log_id >= self.state.log_start);
        }
    }

    fn latest_log_id(&self) -> Option<u64> {
        self.state
            .log
            .len()
            .checked_sub(1)
            .and_then(|index| self.state.log_start.checked_add(index as u64))
    }

    /// The original Wisdom menu is available only while the orb is owned.
    pub fn journal_unlocked(&self) -> bool {
        self.state
            .player
            .inventory
            .iter()
            .any(|item| item == "wisdom_orb")
    }

    fn wisdom_clue_id(&self, dialogue_id: Option<u32>) -> bool {
        let Some(range) = self.campaign.rules["wisdom_dialogue_range"].as_array() else {
            return true;
        };
        dialogue_id.is_some_and(|id| {
            range[0].as_u64().is_some_and(|min| u64::from(id) >= min)
                && range[1].as_u64().is_some_and(|max| u64::from(id) <= max)
        })
    }

    /// Only public clue text is exposed; source dialogue IDs stay in the save.
    fn player_journal(&self) -> Vec<Value> {
        if !self.journal_unlocked() {
            return vec![];
        }
        self.state
            .journal
            .iter()
            .filter(|entry| self.wisdom_clue_id(entry.dialogue_id))
            .map(|entry| {
                json!({
                    "cycle":entry.cycle,"floor":entry.floor,"x":entry.x,"y":entry.y,
                    "title":entry.title,"text":entry.text
                })
            })
            .collect()
    }

    /// Original NPC flags distinguish first hearing before (1) and after (2)
    /// acquiring Wisdom. Previously heard clues are never backfilled.
    fn record_journal(
        &mut self,
        floor: i32,
        x: usize,
        y: usize,
        title: &str,
        text: &str,
        dialogue_id: Option<u32>,
    ) {
        if text.trim().is_empty() {
            return;
        }
        if !self.wisdom_clue_id(dialogue_id) {
            return;
        }
        let heard_key = if self.campaign.rules["wisdom_dialogue_range"].is_array() {
            format!(
                "wisdom_heard:{}",
                dialogue_id.expect("original clue ID was checked")
            )
        } else {
            format!("wisdom_heard:{floor}:{x}:{y}:{}", fingerprint(text))
        };
        if !self.state.flags.insert(heard_key) || !self.journal_unlocked() {
            return;
        }
        let entry = JournalEntry {
            cycle: self.state.cycle,
            floor,
            x,
            y,
            title: if title.trim().is_empty() {
                "Dialogue"
            } else {
                title
            }
            .into(),
            text: text.into(),
            dialogue_id,
        };
        if !self.state.journal.contains(&entry) {
            self.state.journal.push(entry);
            if self.campaign.rules["wisdom_dialogue_range"].is_array() {
                self.state.journal.sort_by_key(|entry| entry.dialogue_id);
            }
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

    /// Custom campaigns default to tile 0; the extracted original sets tile 6.
    /// Campaign validation guarantees this ID is defined and numeric.
    fn empty_tile(&self) -> u16 {
        self.campaign.rules["empty_tile"].as_u64().unwrap_or(0) as u16
    }

    fn clear(&mut self, floor: i32, x: usize, y: usize) {
        let empty = self.empty_tile();
        self.set_tile(floor, x, y, empty);
    }

    fn set_tile(&mut self, floor: i32, x: usize, y: usize, tile: u16) {
        // Script destinations are checked on import; movement callers only
        // clear squares returned by tile_at. A violation is a programming bug,
        // rather than a malformed campaign silently discarding its effect.
        assert!(
            x < self.campaign.width && y < self.campaign.height,
            "validated tile coordinates"
        );
        assert!(
            self.campaign.tiles.contains_key(&tile.to_string()),
            "validated tile ID"
        );
        let tiles = self
            .state
            .floors
            .get_mut(&floor)
            .expect("validated campaign/save floor");
        tiles[y * self.campaign.width + x] = tile;
        self.present(json!({"type":"tile","floor":floor,"x":x,"y":y,"tile":tile,"duration_ms":60}));
    }

    fn area_multiplier(&self, floor: i32) -> i64 {
        self.campaign.rules["area_scaling"]
            .as_array()
            .and_then(|entries| {
                entries.iter().find(|entry| {
                    floor
                        <= entry["max_floor"]
                            .as_i64()
                            .expect("area threshold was validated")
                            as i32
                })
            })
            .and_then(|v| v["multiplier"].as_i64())
            .unwrap_or(((floor.max(1) - 1) / FLOORS_PER_AREA + 1) as i64)
    }

    fn give_item(&mut self, item: &str) {
        self.state.player.grant_item(item, &self.campaign);
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
                    && id != self.empty_tile()
                    && (footprint["clear_all"].as_bool() == Some(true)
                        || footprint["tiles"].as_array().is_some_and(|tiles| {
                            tiles
                                .iter()
                                .any(|tile| tile.as_u64() == Some(u64::from(id)))
                        }))
                {
                    self.clear(floor, nx, ny);
                }
            }
        }
    }

    fn next_cycle(&mut self) {
        if !self.campaign.rules["backside"]["enabled"]
            .as_bool()
            .unwrap_or(false)
        {
            self.state.status = GameStatus::Won;
            self.log("You conquered the Tower of the Sorcerer.");
            return;
        }
        let player = self.state.player.clone();
        let cycle = self.state.cycle.saturating_add(1).min(MAX_CYCLE);
        let mut fresh =
            Self::initial_state(&self.campaign, self.state.campaign_fingerprint.clone());
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
        fresh.log_start = self.state.log_start;
        fresh.battle_log = self.state.battle_log.clone();
        fresh.steps = self.state.steps;
        self.state = fresh;
        self.present(json!({"type":"floor","from":player.floor,"to":self.state.player.floor,"x":self.state.player.x,"y":self.state.player.y,"player":self.state.player,"tiles":self.state.floors.get(&self.state.player.floor),"style":"fade","sound":"none","direction":"down","duration_ms":900}));
        self.log(format!(
            "Entered the backside tower, cycle {cycle}. Monster and treasure statistics are ×{}.",
            self.cycle_multiplier()
        ));
    }
}
