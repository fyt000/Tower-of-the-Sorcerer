//! Built-in original items and compiled custom item effects.
//! Item IDs are authored resource identifiers, unlike closed operation tags.
use crate::{Engine, KeyColor, Stat, TileKind, events::TriggerKind, original::*};

impl Engine {
    pub(crate) fn use_item(&mut self, item: &str, target_floor: Option<i32>) -> Result<(), String> {
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
                let target = target_floor.ok_or("Choose a destination floor")?;
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
                        matches!(
                            self.campaign.tiles[&id.to_string()].kind,
                            TileKind::StairsUp | TileKind::StairsDown
                        )
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
                        TileKind::StairsDown
                    } else {
                        TileKind::StairsUp
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
                        && self.campaign.tiles[&id.to_string()].kind == TileKind::Wall
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
                    if def.kind == TileKind::Door && def.key == Some(KeyColor::Yellow) {
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
                            && self.campaign.tiles[&id.to_string()].kind == TileKind::Enemy
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
                                    BOMB_TILE_RANGES
                                        .iter()
                                        .any(|(first, last)| (*first..=*last).contains(&id)),
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
                                self.run_events(
                                    TriggerKind::EnemyDefeated,
                                    floor,
                                    nx,
                                    ny,
                                    Some(id),
                                );
                            }
                        }
                    }
                }
                if count == 0 {
                    return self.block("No nearby enemies can be destroyed.");
                }
                self.add_stat(Stat::Gold, reward);
                self.log(format!(
                    "The bomb destroyed {count} enemies: +{reward} gold."
                ));
            }
            "holy_water" | "elixir" => {
                let hp = self
                    .state
                    .player
                    .attack
                    .saturating_mul(ELIXIR_ATTACK_FACTOR)
                    .saturating_add(
                        self.state
                            .player
                            .defense
                            .saturating_mul(ELIXIR_DEFENSE_FACTOR),
                    );
                self.add_stat(Stat::Hp, hp);
                self.log(format!("The elixir restored {hp} HP."));
            }
            "orb_of_ascending" | "orb_of_descending" | "up_wing" | "down_wing" => {
                let target =
                    floor.checked_add(if ["orb_of_ascending", "up_wing"].contains(&item) {
                        1
                    } else {
                        -1
                    });
                let Some(target) = target else {
                    return self.block("The wing goes no further.");
                };
                if !self
                    .tile_at(target, x, y)
                    .is_some_and(|id| id == self.empty_tile())
                {
                    return self.block(
                        "The destination must be an ordinary passage at the same coordinates.",
                    );
                }
                self.state.player.floor = target;
                self.state.visited_floors.insert(target);
                self.present_floor(floor, "original_spiral", None);
                self.run_events(TriggerKind::EnterFloor, target, x, y, None);
                self.log(format!("The wing carried you to floor {target}."));
            }
            "warp_staff" => {
                let charges = self
                    .state
                    .player
                    .item_charges
                    .entry("warp_staff".into())
                    .or_insert(WARP_STAFF_CHARGES);
                if *charges == 0 {
                    return self.block("The Warp Staff has no charges remaining.");
                }
                *charges -= 1;
                consume = *charges == 0;
                let (nx, ny) = (self.campaign.width - 1 - x, self.campaign.height - 1 - y);
                if self.tile_at(floor, nx, ny) == Some(self.empty_tile()) {
                    self.state.player.x = nx;
                    self.state.player.y = ny;
                    self.run_events(TriggerKind::Step, floor, nx, ny, None);
                    self.log("The Warp Staff carried you across the floor.");
                } else {
                    self.log("The Warp Staff used a charge, but the destination is blocked.");
                }
            }
            "super_mattock" => {
                let tiles = self.state.floors[&floor].clone();
                let mut count = 0;
                for (i, id) in tiles.iter().enumerate() {
                    if self.campaign.tiles[&id.to_string()].kind == TileKind::Wall
                        && *id == BRICK_WALL_TILE
                    {
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
                        && self.campaign.tiles[&id.to_string()].kind == TileKind::Lava
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
                let Some(def) = self.campaign.items.get(item).cloned() else {
                    return self.block(&format!(
                        "Item {item} is passive or has no configured action"
                    ));
                };
                let effects = self
                    .scripts
                    .item_effects
                    .get(item)
                    .cloned()
                    .unwrap_or_default();
                self.apply_effects(&effects);
                consume = def["consumable"].as_bool().unwrap_or(true);
            }
        }
        if consume {
            self.state.player.inventory.retain(|s| s != item);
        }
        Ok(())
    }
}
