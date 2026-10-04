//! Movement, obstacle-limited routes, stair arrivals and movement hazards.
use crate::domain::GameStatus;
use crate::{
    EnemySpecial, Engine, KeyColor, Stat, TileKind, events::TriggerKind, forecast_with_rules,
    original::*,
};
use serde_json::{Value, json};
use std::collections::{BTreeMap, VecDeque};

impl Engine {
    /// Plan through clear road only. An obstacle may be the final action, never an intermediate step.
    /// Unreachable destinations return the reachable road prefix closest to the requested square.
    pub fn path_to(&self, x: usize, y: usize) -> Vec<String> {
        if x >= self.campaign.width
            || y >= self.campaign.height
            || self.state.pending_interaction.is_some()
            || self.state.status != GameStatus::Playing
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
                if next != target
                    && !matches!(
                        def.kind,
                        TileKind::Empty
                            | TileKind::Floor
                            | TileKind::Decoration
                            | TileKind::Trigger
                    )
                {
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

    pub(crate) fn move_player(&mut self, dx: isize, dy: isize) -> Result<(), String> {
        let p = self.state.player.clone();
        let cycle = self.state.cycle;
        let (x, y) = (p.x.checked_add_signed(dx), p.y.checked_add_signed(dy));
        let (Some(x), Some(y)) = (x, y) else {
            return self.block("The edge of the tower blocks your path.");
        };
        let floor = p.floor;
        let Some(original_id) = self.tile_at(floor, x, y) else {
            return self.block("The edge of the tower blocks your path.");
        };
        self.run_events(TriggerKind::Bump, floor, x, y, Some(original_id));
        if self.state.status != GameStatus::Playing
            || self.state.cycle != cycle
            || self.state.player.floor != floor
            || self.state.player.x != p.x
            || self.state.player.y != p.y
        {
            return Ok(());
        }
        let id = self
            .tile_at(floor, x, y)
            .ok_or("Event changed the destination unexpectedly")?;
        if id != original_id && self.campaign.tiles[&id.to_string()].kind == TileKind::Enemy {
            return self.block("A hidden enemy has been revealed.");
        }
        let def = self.campaign.tiles[&id.to_string()].clone();
        let mut entered = true;
        match def.kind {
            TileKind::Empty | TileKind::Floor | TileKind::Decoration => {}
            TileKind::Wall | TileKind::Solid | TileKind::Lava | TileKind::Barrier => {
                if !def.passable {
                    return self.block("A wall blocks your path.");
                }
            }
            TileKind::HiddenWall => {
                self.clear(floor, x, y);
                self.log("You discovered a hidden passage.");
            }
            TileKind::Door => {
                let key = def.key.unwrap_or(KeyColor::Yellow);
                let count = self.key_mut(key);
                if *count <= 0 {
                    return self.block(&format!("You need a {key} key."));
                }
                *count -= 1;
                self.clear(floor, x, y);
                self.log(format!("Opened the {key} door."));
                self.run_events(TriggerKind::DoorOpened, floor, x, y, Some(id));
            }
            TileKind::SpecialDoor => return self.block("This gate opens through a floor event."),
            TileKind::Key => {
                self.add_stat(
                    def.key.unwrap_or(KeyColor::Yellow).stat(),
                    def.amount.max(1),
                );
                self.clear(floor, x, y);
                self.log(format!("Collected {}.", def.name));
            }
            TileKind::Enemy | TileKind::Monster => {
                let enemy = self
                    .enemy_for_tile(def.enemy.as_deref().ok_or("Enemy tile has no enemy")?, id)
                    .ok_or("Unknown enemy")?;
                self.record_enemy_encounter(&enemy, floor, x, y, id);
                let battle = forecast_with_rules(&self.state.player, &enemy, &self.campaign.rules);
                let Some(damage) = battle.damage else {
                    return self.block(&battle.reason);
                };
                // Original taisen enters after the attack guard, before its
                // lethality check, including a fight that will kill the hero.
                self.present_move(&p, x, y, dx, dy);
                self.state.player.x = x;
                self.state.player.y = y;
                let battle_record = self.present_battle(&enemy, &battle, floor, x, y, false);
                if damage >= self.state.player.hp {
                    // Original permits fatal battles; forecasts let the player plan before committing.
                    self.state.player.hp = 0;
                    self.state.status = GameStatus::Lost;
                    self.log(format!(
                        "{} defeated you. Restore a save to try another route.",
                        enemy.name
                    ));
                    self.record_battle_log(battle_record);
                    return Ok(());
                }
                self.state.player.hp -= damage;
                let reward = battle.gold;
                self.add_stat(Stat::Gold, reward);
                self.clear(floor, x, y);
                if def.extra.contains_key("footprint") {
                    self.clear_large_monster(floor, &def, x, y);
                }
                self.log(format!(
                    "Defeated {}: −{} HP, +{} gold.",
                    enemy.name, damage, reward
                ));
                self.record_battle_log(battle_record);
                self.run_events(TriggerKind::EnemyDefeated, floor, x, y, Some(id));
                entered = false;
            }
            TileKind::Potion
            | TileKind::Gem
            | TileKind::Stat
            | TileKind::Equipment
            | TileKind::Gold => {
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
                    amount = amount.saturating_mul(self.area_multiplier(floor));
                }
                if stat != "gold" {
                    amount = amount.saturating_mul(self.cycle_multiplier());
                }
                self.add_stat(stat, amount);
                if let Some(item) = &def.item {
                    self.give_item(item);
                }
                self.clear(floor, x, y);
                self.log(format!("Collected {}: +{} {}.", def.name, amount, stat));
            }
            TileKind::Item => {
                self.give_item(def.item.as_deref().unwrap_or(&def.name));
                if def.item.as_deref() == Some("warp_staff") {
                    self.state
                        .player
                        .item_charges
                        .insert("warp_staff".into(), WARP_STAFF_CHARGES);
                }
                self.clear(floor, x, y);
                self.log(format!("Acquired {}.", def.name));
            }
            TileKind::StairsUp | TileKind::StairsDown | TileKind::Stairs => {
                let up = def.kind == TileKind::StairsUp
                    || def.extra.get("direction").and_then(Value::as_str) == Some("up");
                let link = format!("{floor}:{}", if up { "up" } else { "down" });
                let target = def
                    .target_floor
                    .or_else(|| {
                        self.campaign.rules["stair_links"][link]
                            .as_i64()
                            .map(|v| v as i32)
                    })
                    .or_else(|| floor.checked_add(if up { 1 } else { -1 }));
                let Some(target) = target else {
                    return self.block("The stairway goes no further.");
                };
                if !self.state.floors.contains_key(&target) {
                    return self.block("The stairway goes no further.");
                }
                self.change_floor(
                    target,
                    if up {
                        TileKind::StairsDown
                    } else {
                        TileKind::StairsUp
                    },
                    crate::flight::FloorTravel::Stairs,
                )?;
                entered = false;
            }
            TileKind::Npc
            | TileKind::Shop
            | TileKind::Altar
            | TileKind::Merchant
            | TileKind::Fairy => {
                self.open_interaction(floor, x, y, &def);
                return Ok(());
            }
            TileKind::Win => {
                self.state.status = GameStatus::Won;
                self.log("The sorcerer's tower has been conquered.");
            }
            TileKind::Trigger => {}
        }
        // The accepted action counts once, including an encounter that ends or
        // redirects the journey. A script owns its relocation; ordinary walking
        // must not overwrite a teleport or continue in a newly reset tower.
        self.state.steps = self.state.steps.saturating_add(1);
        let location = (
            self.state.player.floor,
            self.state.player.x,
            self.state.player.y,
        );
        if self.state.status == GameStatus::Lost
            || self.state.cycle != cycle
            || (entered && location != (p.floor, p.x, p.y))
            || (matches!(def.kind, TileKind::Enemy | TileKind::Monster)
                && location != (floor, x, y))
        {
            return Ok(());
        }
        let effects = self.scripts.tile_effects(id).to_vec();
        self.apply_effects(&effects);
        if self.state.status != GameStatus::Playing
            || self.state.cycle != cycle
            || location
                != (
                    self.state.player.floor,
                    self.state.player.x,
                    self.state.player.y,
                )
        {
            return Ok(());
        }
        if entered {
            self.state.player.x = x;
            self.state.player.y = y;
            self.present_move(&p, x, y, dx, dy);
        }
        if matches!(
            def.kind,
            TileKind::Key
                | TileKind::Potion
                | TileKind::Gem
                | TileKind::Stat
                | TileKind::Equipment
                | TileKind::Gold
                | TileKind::Item
        ) {
            self.present(json!({"type":"audio","name":"get"}));
        } else if def.kind == TileKind::Door {
            self.present(json!({"type":"audio","name":"open"}));
        }
        self.run_events(
            TriggerKind::Step,
            self.state.player.floor,
            self.state.player.x,
            self.state.player.y,
            Some(id),
        );
        self.apply_hazards();
        Ok(())
    }

    pub(crate) fn change_floor(
        &mut self,
        target: i32,
        arrival_kind: TileKind,
        travel: crate::flight::FloorTravel,
    ) -> Result<(), String> {
        let tiles = self.state.floors.get(&target).ok_or("Unknown floor")?;
        let metadata = self
            .campaign
            .floors
            .iter()
            .find(|f| f.id == target)
            .and_then(|f| {
                if arrival_kind == TileKind::StairsDown {
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
                    matches!(
                        self.campaign.tiles[&id.to_string()].kind,
                        TileKind::Empty | TileKind::Floor
                    )
                })
            })
            .ok_or("Destination floor has no arrival tile")?;
        let from = self.state.player.floor;
        if travel == crate::flight::FloorTravel::Stairs && target > from {
            self.state.highest_stair_floor = Some(self.highest_stair_floor().max(target));
        }
        self.apply_floor_travel_callbacks(from, target, travel);
        self.state.player.floor = target;
        self.state.player.x = index % self.campaign.width;
        self.state.player.y = index / self.campaign.width;
        self.present_floor(from, "original_spiral", None);
        self.state.visited_floors.insert(target);
        self.log(format!("Entered floor {target}."));
        self.run_events(
            TriggerKind::EnterFloor,
            target,
            self.state.player.x,
            self.state.player.y,
            None,
        );
        Ok(())
    }

    fn apply_hazards(&mut self) {
        // A winning step can still have authored ending presentation, but the
        // ordinary movement hazard must not turn the finished win into a loss.
        if self.state.status != GameStatus::Playing {
            return;
        }
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
            damage += match special_at(x, y) {
                EnemySpecial::MagicianA => {
                    self.campaign.rules["magician_a_damage"]
                        .as_i64()
                        .unwrap_or(MAGICIAN_A_DAMAGE)
                        .max(0)
                        * self.cycle_multiplier()
                }
                EnemySpecial::MagicianB => {
                    self.campaign.rules["magician_b_damage"]
                        .as_i64()
                        .unwrap_or(MAGICIAN_B_DAMAGE)
                        .max(0)
                        * self.cycle_multiplier()
                }
                _ => 0,
            };
        }
        if (special_at(p.x.wrapping_sub(1), p.y) == EnemySpecial::Sorcerer
            && special_at(p.x + 1, p.y) == EnemySpecial::Sorcerer)
            || (special_at(p.x, p.y.wrapping_sub(1)) == EnemySpecial::Sorcerer
                && special_at(p.x, p.y + 1) == EnemySpecial::Sorcerer)
        {
            damage += (p.hp + 1) / 2;
        }
        if damage > 0 {
            self.state.player.hp = (self.state.player.hp - damage).max(0);
            self.log(format!("Magic field: −{damage} HP."));
        }
        if self.state.player.hp == 0 {
            self.state.status = GameStatus::Lost;
        }
    }
}
