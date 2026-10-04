//! Deterministic, platform-independent Tower of the Sorcerer simulation.
//! Campaign geometry, tile behavior, statistics, shops and events come from JSON.
mod campaign;
mod combat;
mod command;
mod domain;
mod events;
mod interactions;
mod items;
mod navigation;
mod original;
mod persistence;
mod presentation;
mod stats;
use persistence::{MAX_CYCLE, SAVE_VERSION, Save, fingerprint};

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
        let fingerprint = fingerprint(
            &serde_json::to_string(&campaign)
                .expect("Campaign fields have an infallible JSON representation"),
        );
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
            "inventory_items":p.inventory.iter().map(|item|{
                let definition=self.campaign.tiles.values().find(|def|def.item.as_ref()==Some(item));
                let usable=definition.is_none_or(|def|def.kind!=TileKind::Equipment) && !["hero_orb","wisdom_orb","monster_book","cross","dragon_slayer","lucky_gold","sacred_shield"].contains(&item.as_str());
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
        let concealed = def.kind == TileKind::HiddenWall;
        json!({"id":id,"x":x,"y":y,"name":if concealed{"Brick wall"}else{&def.name},"description":if concealed{"A solid wall."}else if noncombat{"Approach this character to complete the adventure."}else{&def.description},"kind":if concealed{"wall"}else if noncombat{"npc"}else{def.kind.as_str()},"enemy":enemy,"details_locked":def.enemy.is_some() && !noncombat && !self.forecasts_unlocked()})
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
        fresh.steps = self.state.steps;
        self.state = fresh;
        self.present(json!({"type":"floor","from":player.floor,"to":self.state.player.floor,"x":self.state.player.x,"y":self.state.player.y,"player":self.state.player,"tiles":self.state.floors.get(&self.state.player.floor),"style":"fade","sound":"none","direction":"down","duration_ms":900}));
        self.log(format!(
            "Entered the backside tower, cycle {cycle}. Monster and treasure statistics are ×{}.",
            self.cycle_multiplier()
        ));
    }
}
