//! Player knowledge is a separate boundary from diagnostic snapshots and saves.
//! Never serialize authored scripts or runtime bookkeeping into this view.
use crate::{Engine, Stat, TileDef, TileKind, original::BRICK_WALL_TILE};
use serde_json::{Map, Value, json};
use std::collections::BTreeSet;

impl Engine {
    /// The current board, visible results and choices available to a player.
    /// Coordinates are zero-based; `tiles[y * width + x]` indexes the board.
    pub fn player_observation(&self) -> Value {
        let snapshot = self.snapshot();
        let p = &self.state.player;
        let tiles: Vec<u16> = self.state.floors[&p.floor]
            .iter()
            .map(|id| self.player_tile_id(*id))
            .collect();
        let mut tile_defs = Map::new();
        for id in tiles.iter().copied().collect::<BTreeSet<_>>() {
            tile_defs.insert(id.to_string(), self.player_tile_definition(id));
        }
        let mut observation = public_fields(
            &snapshot,
            &[
                "campaign_id",
                "title",
                "floor",
                "width",
                "height",
                "player",
                "visited_floors",
                "inventory_items",
                "equipment",
                "abilities",
                "last_encounter",
                "log",
                "log_start",
                "battle_log",
                "journal",
                "journal_unlocked",
                "save_unlocked",
                "status",
                "steps",
                "cycle",
                "forecasts_unlocked",
            ],
        );
        observation["coordinates"] = json!({"origin":"top_left","indexing":"tiles[y * width + x]","x_increases":"right","y_increases":"down"});
        observation["tiles"] = json!(tiles);
        observation["tile_defs"] = json!(tile_defs);
        observation["floors"] = json!(
            self.campaign
                .floors
                .iter()
                .filter(|floor| self.state.visited_floors.contains(&floor.id))
                .map(|floor| json!({"id":floor.id,"title":floor.title,"visited":true}))
                .collect::<Vec<_>>()
        );
        observation["inventory_items"] = json!(
            snapshot["inventory_items"]
                .as_array()
                .into_iter()
                .flatten()
                .map(|item| {
                    let mut visible =
                        public_fields(item, &["id", "name", "usable", "charges", "usage"]);
                    visible["sprite"] = public_sprite(&item["sprite"]);
                    visible
                })
                .collect::<Vec<_>>()
        );
        // Historical gear tags are private script/ability state; current
        // equipment and persistent protection have their own visible fields.
        observation["player"]["inventory"] = json!(
            p.inventory
                .iter()
                .filter(|item| !self.campaign.is_equipment(item))
                .collect::<Vec<_>>()
        );
        for slot in ["weapon", "shield"] {
            let item = &snapshot["equipment"][slot];
            if item.is_object() {
                let mut visible =
                    public_fields(item, &["id", "name", "usable", "charges", "usage"]);
                visible["sprite"] = public_sprite(&item["sprite"]);
                observation["equipment"][slot] = visible;
            }
        }
        observation["pending_interaction"] = self.player_interaction();
        observation["last_action"] = self.player_last_action();
        // Advance forecasts require Hero; raw last-contact stats do not.
        observation["enemies"] = snapshot["enemies"].clone();
        observation
    }

    /// Inspect appearances and unlocked forecasts, without identifying a secret.
    pub fn inspect_player_tile(&self, x: usize, y: usize) -> Value {
        let Some(id) = self.tile_at(self.state.player.floor, x, y) else {
            return json!({"error":"Outside map"});
        };
        let public_id = self.player_tile_id(id);
        let mut result = self.player_tile_definition(public_id);
        result["id"] = json!(public_id);
        result["x"] = json!(x);
        result["y"] = json!(y);
        let inspection = self.inspect(x, y);
        if self.campaign.tiles[&id.to_string()].enemy.is_some() {
            result["enemy"] = inspection["enemy"].clone();
            result["details_locked"] = inspection["details_locked"].clone();
            result["encountered_enemy"] = inspection["encountered_enemy"].clone();
        }
        result
    }

    fn player_tile_id(&self, id: u16) -> u16 {
        let def = &self.campaign.tiles[&id.to_string()];
        // The extracted original has separate atlas cells and behavior IDs for
        // identical brick artwork. Neither those IDs nor their names are clues.
        if matches!(id, 8..=10)
            && matches!(def.kind, TileKind::Wall | TileKind::HiddenWall)
            && self
                .campaign
                .tiles
                .get(&BRICK_WALL_TILE.to_string())
                .is_some_and(|wall| wall.kind == TileKind::Wall)
        {
            return BRICK_WALL_TILE;
        }
        let appearance_kind = match def.kind {
            TileKind::HiddenWall | TileKind::Wall => TileKind::Wall,
            TileKind::Trigger => TileKind::Floor,
            _ => return id,
        };
        let same_appearance = self
            .campaign
            .tiles
            .iter()
            .filter(|(_, candidate)| {
                candidate.kind == appearance_kind && candidate.sprite == def.sprite
            })
            .filter_map(|(candidate, _)| candidate.parse::<u16>().ok())
            .min();
        same_appearance.unwrap_or_else(|| {
            if def.kind == TileKind::HiddenWall {
                self.campaign
                    .tiles
                    .iter()
                    .filter(|(_, candidate)| candidate.kind == TileKind::Wall)
                    .filter_map(|(candidate, _)| candidate.parse::<u16>().ok())
                    .min()
                    .unwrap_or(id)
            } else if def.kind == TileKind::Trigger {
                self.empty_tile()
            } else {
                id
            }
        })
    }

    fn player_tile_definition(&self, id: u16) -> Value {
        let def = &self.campaign.tiles[&id.to_string()];
        let kind = match def.kind {
            TileKind::HiddenWall => TileKind::Wall,
            TileKind::Trigger => TileKind::Floor,
            kind => kind,
        };
        let mut result = json!({
            "name":if def.kind == TileKind::HiddenWall {"Brick wall"} else {&def.name},
            "kind":kind,"sprite":public_sprite(&def.sprite),
        });
        if !def.description.is_empty() && def.kind != TileKind::HiddenWall {
            result["description"] = json!(def.description);
        }
        match kind {
            TileKind::Door => result["key"] = json!(def.key.unwrap_or(crate::KeyColor::Yellow)),
            TileKind::Key => {
                result["key"] = json!(def.key.unwrap_or(crate::KeyColor::Yellow));
                result["amount"] = json!(def.amount.max(1));
            }
            TileKind::Potion
            | TileKind::Gem
            | TileKind::Stat
            | TileKind::Equipment
            | TileKind::Gold => {
                let (stat, amount) = self.player_pickup(def);
                result["stat"] = json!(stat);
                result["amount"] = json!(amount);
                if let Some(item) = &def.item {
                    result["item"] = json!(item);
                }
            }
            TileKind::Item => {
                if let Some(item) = &def.item {
                    result["item"] = json!(item);
                }
            }
            _ => {}
        }
        result
    }

    fn player_pickup(&self, def: &TileDef) -> (Stat, i64) {
        let stat = def.stat.unwrap_or(match def.kind {
            TileKind::Potion => Stat::Hp,
            TileKind::Gold => Stat::Gold,
            _ => Stat::Attack,
        });
        let mut amount = def.amount;
        if def
            .extra
            .get("scaled")
            .and_then(Value::as_bool)
            .unwrap_or(false)
        {
            amount = amount.saturating_mul(self.area_multiplier(self.state.player.floor));
        }
        if stat != Stat::Gold {
            amount = amount.saturating_mul(self.cycle_multiplier());
        }
        (stat, amount)
    }

    fn player_interaction(&self) -> Value {
        let Some(interaction) = &self.state.pending_interaction else {
            return Value::Null;
        };
        let mut result = public_fields(interaction, &["title", "text"]);
        result["choices"] = json!(
            interaction["choices"]
                .as_array()
                .into_iter()
                .flatten()
                .map(|choice| {
                    let mut choice = public_fields(choice, &["id", "label", "cost"]);
                    if let Some(cost) = choice["cost"].as_i64() {
                        choice["affordable"] = json!(self.state.player.gold >= cost);
                    }
                    choice
                })
                .collect::<Vec<_>>()
        );
        result
    }

    fn player_last_action(&self) -> Value {
        let mut action = public_fields(&self.last_action, &["ok", "type", "message"]);
        let timeline = self.last_action["presentation"].as_array();
        let mut visible_floor = timeline
            .into_iter()
            .flatten()
            .find_map(|effect| match effect["type"].as_str() {
                Some("floor") => effect["from"].as_i64(),
                Some("move") => effect["from"]["floor"].as_i64(),
                Some("battle") => effect["floor"].as_i64(),
                _ => None,
            })
            .unwrap_or(i64::from(self.state.player.floor));
        let mut presentation = vec![];
        for effect in timeline.into_iter().flatten() {
            let Some(kind) = effect["type"].as_str() else {
                continue;
            };
            let fields: &[&str] = match kind {
                "dialogue" => &["type", "text", "duration_ms"],
                "journal" => &["type", "entries"],
                "move" => &["type", "direction", "duration_ms"],
                "floor" => &["type", "from", "to", "x", "y", "direction", "duration_ms"],
                "tile" => &["type", "floor", "x", "y", "duration_ms"],
                "move_tile" => &["type", "floor", "from_x", "from_y", "x", "y", "duration_ms"],
                "battle" => &["type", "enemy_name", "floor", "x", "y", "duration_ms"],
                "cinematic" => &["type", "text", "x", "y", "duration_ms"],
                "audio" => &["type", "name"],
                "wait" => &["type", "duration_ms"],
                _ => continue,
            };
            if matches!(kind, "tile" | "move_tile")
                && effect["floor"].as_i64() != Some(visible_floor)
            {
                continue;
            }
            let mut public = public_fields(effect, fields);
            if kind == "move" {
                public["from"] = public_fields(&effect["from"], &["floor", "x", "y"]);
                public["to"] = public_fields(&effect["to"], &["floor", "x", "y"]);
            }
            if kind == "floor" {
                visible_floor = effect["to"].as_i64().unwrap_or(visible_floor);
                if let Some(tiles) = effect["tiles"].as_array() {
                    public["tiles"] = json!(
                        tiles
                            .iter()
                            .filter_map(Value::as_u64)
                            .filter_map(|id| u16::try_from(id).ok())
                            .map(|id| self.player_tile_id(id))
                            .collect::<Vec<_>>()
                    );
                }
            }
            if matches!(kind, "tile" | "move_tile")
                && let Some(id) = effect["tile"]
                    .as_u64()
                    .and_then(|id| u16::try_from(id).ok())
            {
                public["tile"] = json!(self.player_tile_id(id));
            }
            presentation.push(public);
        }
        action["presentation"] = json!(presentation);
        action
    }
}

fn public_fields(value: &Value, fields: &[&str]) -> Value {
    let mut result = Map::new();
    for field in fields {
        if let Some(value) = value.get(*field) {
            result.insert((*field).into(), value.clone());
        }
    }
    Value::Object(result)
}

fn public_sprite(sprite: &Value) -> Value {
    if sprite.is_object() {
        public_fields(sprite, &["x", "y", "w", "h"])
    } else if sprite.is_u64() {
        sprite.clone()
    } else {
        Value::Null
    }
}
