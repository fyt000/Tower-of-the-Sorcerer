//! Built-in original items and compiled custom item effects.
//! Item IDs are authored resource identifiers, unlike closed operation tags.
use crate::{
    Engine, KeyColor, Stat, TileKind, events::TriggerKind, flight::FloorTravel, original::*,
};
use serde_json::{Value, json};

impl Engine {
    /// Player-facing help for an already owned item. Keep this separate from
    /// authored effects: script conditions and acquisition locations are not
    /// item instructions.
    pub(crate) fn item_usage(&self, item: &str) -> Value {
        let mut usage = match item {
            "hero_orb" | "monster_book" => {
                let description = if self.campaign.rules["forecast_requires_item"]
                    .as_str()
                    .is_none_or(|required| required == item)
                {
                    "Enemy statistics and battle forecasts are available in inspection."
                } else {
                    "Passive reference item; this campaign's enemy forecasts require a different item."
                };
                let mut usage = passive_usage(description);
                if item == "hero_orb" && self.campaign.rules["save_requires_hero_orb"] == true {
                    usage["description"] = json!(format!(
                        "{description} Also enables manual save checkpoints."
                    ));
                }
                usage
            }
            "wisdom_orb" => active_usage(
                item,
                "Review hints first heard while owning this orb; reusable.",
                false,
                &["Earlier conversations are not added retroactively. Only recorded hints appear."],
            ),
            "cross" | "dragon_slayer" => {
                let (rule, default, enemies) = if item == "cross" {
                    ("cross_multiplier", CROSS_MULTIPLIER, "undead")
                } else {
                    (
                        "dragon_slayer_multiplier",
                        DRAGON_SLAYER_MULTIPLIER,
                        "dragons",
                    )
                };
                let multiplier = self.campaign.rules[rule]
                    .as_i64()
                    .unwrap_or(default)
                    .clamp(1, 1000);
                let mut usage = passive_usage(&format!(
                    "Multiplies attack by {multiplier} against {enemies} during combat."
                ));
                if self.campaign.rules["base_attack_guard"]
                    .as_bool()
                    .unwrap_or(true)
                {
                    usage["restrictions"] =
                        json!(["Base attack must still exceed the enemy's defense."]);
                }
                usage
            }
            "lucky_gold" => passive_usage(
                "Doubles gold from combat victories; bomb rewards use the normal gold amount.",
            ),
            "sacred_shield" => passive_usage(
                "Prevents magical field damage from movement near magicians and sorcerers.",
            ),
            "orb_of_flying" | "floor_wand" | "flying_orb" => {
                let original_selection = self.campaign.rules["flying_original_selection"]
                    .as_bool()
                    .unwrap_or(false);
                let mut usage = active_usage(
                    item,
                    if original_selection {
                        "Travel within the unlocked floor range; reusable."
                    } else {
                        "Travel to a previously visited floor; reusable."
                    },
                    false,
                    if original_selection {
                        &[
                            "Destination must be listed in this orb's available floor selector.",
                            "Only floors unlocked through stairs can be selected.",
                        ]
                    } else {
                        &["Destination must be a visited floor."]
                    },
                );
                let destinations = self.flying_destinations();
                let target = destinations
                    .iter()
                    .copied()
                    .find(|floor| *floor != self.state.player.floor)
                    .or_else(|| destinations.first().copied());
                if let Some(target) = target {
                    usage["command"]["floor"] = json!(target);
                } else {
                    usage.as_object_mut().unwrap().remove("command");
                }
                usage["allowed_floors"] = json!(destinations);
                usage["target_floor"] = json!(if original_selection {
                    "available_floor"
                } else {
                    "visited_floor"
                });
                if self.campaign.rules["flying_requires_stairs"]
                    .as_bool()
                    .unwrap_or(true)
                {
                    usage["restrictions"].as_array_mut().unwrap().push(json!(
                        "Stand on or orthogonally beside an up/down staircase."
                    ));
                }
                usage
            }
            "mattock" => active_usage(
                item,
                "Break adjacent ordinary walls in the four cardinal directions; consumed even if none can be broken.",
                true,
                &["Special walls are excluded."],
            ),
            "magic_key" => active_usage(
                item,
                "Open every yellow door on the current floor without spending keys; consumed even if there are no yellow doors.",
                true,
                &[],
            ),
            "bomb" => active_usage(
                item,
                "Destroy susceptible enemies immediately beside you in the four cardinal directions and collect their normal gold; consumed even if none are destroyed.",
                true,
                &["Some enemy types resist bombs."],
            ),
            "holy_water" | "elixir" => active_usage(
                item,
                &format!(
                    "Adds attack × {ELIXIR_ATTACK_FACTOR} + defense × {ELIXIR_DEFENSE_FACTOR} HP."
                ),
                true,
                &[],
            ),
            "orb_of_ascending" | "up_wing" | "orb_of_descending" | "down_wing" => {
                let direction = if ["orb_of_ascending", "up_wing"].contains(&item) {
                    "up"
                } else {
                    "down"
                };
                active_usage(
                    item,
                    &format!("Move one floor {direction} at the same coordinates."),
                    true,
                    &[
                        "The destination must exist and be an ordinary passage, not an occupied tile.",
                    ],
                )
            }
            "warp_staff" => {
                let mut usage = active_usage(
                    item,
                    "Warp to the point mirrored through the center of the current floor.",
                    true,
                    &[
                        "Landing requires an ordinary passage. A charge is spent even if blocked; the final charge consumes the staff.",
                    ],
                );
                usage["remaining_charges"] = json!(
                    self.state
                        .player
                        .item_charges
                        .get(item)
                        .copied()
                        .unwrap_or(WARP_STAFF_CHARGES)
                );
                usage
            }
            "super_mattock" => active_usage(
                item,
                "Remove every ordinary wall on the current floor; consumed even if there are none.",
                true,
                &["Special walls are excluded."],
            ),
            "snow_crystal" => active_usage(
                item,
                "Cool immediately adjacent lava in the four cardinal directions; reusable.",
                false,
                &["Requires lava immediately beside you."],
            ),
            _ => {
                if let Some(definition) = self.campaign.items.get(item) {
                    let description = definition["description"]
                        .as_str()
                        .filter(|description| !description.trim().is_empty())
                        .unwrap_or_else(|| {
                            if self
                                .scripts
                                .item_effects
                                .get(item)
                                .is_some_and(|effects| !effects.is_empty())
                            {
                                "Use this item's configured ability."
                            } else {
                                "Using this item has no configured effect."
                            }
                        });
                    active_usage(
                        item,
                        description,
                        definition["consumable"].as_bool().unwrap_or(true),
                        &[],
                    )
                } else if self.campaign.tiles.values().any(|tile| {
                    tile.kind == TileKind::Equipment && tile.item.as_deref() == Some(item)
                }) {
                    passive_usage(
                        "Equipment bonuses were applied when collected; no activation is required.",
                    )
                } else {
                    json!({"description":"This item has no configured action.",
                        "activation":"none","consumable":false,"restrictions":[]})
                }
            }
        };
        if usage["activation"] == "use_item" {
            usage["restrictions"]
                .as_array_mut()
                .unwrap()
                .push(json!("Close any open conversation before use."));
        }
        usage
    }

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
            "wisdom_orb" => {
                consume = false;
                self.present(json!({"type":"journal","entries":self.player_journal()}));
                self.log("Reviewed the Orb of Wisdom's recorded hints.");
            }
            "hero_orb" | "monster_book" | "cross" | "dragon_slayer" | "lucky_gold"
            | "sacred_shield" => {
                consume = false;
                self.log("The item is always active.");
            }
            "orb_of_flying" | "floor_wand" | "flying_orb" => {
                let target = target_floor.ok_or("Choose a destination floor")?;
                let original_selection = self.campaign.rules["flying_original_selection"]
                    .as_bool()
                    .unwrap_or(false);
                if !self.flying_destinations().contains(&target) {
                    return self.block(if original_selection {
                        "That floor is unavailable in the Orb of Flying's selector."
                    } else {
                        "The Orb of Flying only reaches visited floors."
                    });
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
                if original_selection && target == floor {
                    self.log("The Orb of Flying leaves you on the current floor.");
                } else {
                    self.change_floor(
                        target,
                        if target > floor {
                            TileKind::StairsDown
                        } else {
                            TileKind::StairsUp
                        },
                        FloorTravel::Flight,
                    )?;
                }
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
                        && self.item_breaks_wall(id)
                    {
                        self.clear(floor, nx, ny);
                        count += 1;
                    }
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
                self.log(format!(
                    "The Magic Key opened {count} yellow doors on this floor."
                ));
            }
            "bomb" => {
                let mut count = 0;
                let mut reward = 0;
                for (nx, ny) in [
                    (x.wrapping_sub(1), y),
                    (x + 1, y),
                    (x, y.wrapping_sub(1)),
                    (x, y + 1),
                ] {
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
                            self.run_events(TriggerKind::EnemyDefeated, floor, nx, ny, Some(id));
                        }
                    }
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
                    if self.item_breaks_wall(*id) {
                        self.clear(floor, i % self.campaign.width, i / self.campaign.width);
                        count += 1;
                    }
                }
                self.log(format!("The Super Mattock removed {count} walls."));
            }
            "snow_crystal" => {
                consume = false;
                let neighbors = [
                    (x.wrapping_sub(1), y),
                    (x + 1, y),
                    (x, y.wrapping_sub(1)),
                    (x, y + 1),
                ];
                let mut count = 0;
                for (nx, ny) in neighbors {
                    if let Some(id) = self.tile_at(floor, nx, ny)
                        && self.campaign.tiles[&id.to_string()].kind == TileKind::Lava
                    {
                        self.clear(floor, nx, ny);
                        count += 1;
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

    fn item_breaks_wall(&self, id: u16) -> bool {
        self.campaign.tiles[&id.to_string()].kind == TileKind::Wall
            && self.campaign.rules["wall_break_tile_ranges"]
                .as_array()
                .is_none_or(|ranges| {
                    ranges.iter().any(|range| {
                        range[0]
                            .as_u64()
                            .is_some_and(|minimum| u64::from(id) >= minimum)
                            && range[1]
                                .as_u64()
                                .is_some_and(|maximum| u64::from(id) <= maximum)
                    })
                })
    }

    pub(crate) fn flying_destinations(&self) -> Vec<i32> {
        if self.campaign.rules["flying_original_selection"]
            .as_bool()
            .unwrap_or(false)
        {
            let highest = self.highest_stair_floor();
            let mut floors: Vec<_> = self
                .campaign
                .floors
                .iter()
                .map(|floor| floor.id)
                .filter(|floor| *floor >= 1 && *floor <= highest && *floor != 44)
                .collect();
            floors.sort_unstable();
            floors
        } else {
            self.state.visited_floors.iter().copied().collect()
        }
    }

    pub(crate) fn highest_stair_floor(&self) -> i32 {
        self.state.highest_stair_floor.unwrap_or_else(|| {
            self.state
                .visited_floors
                .iter()
                .copied()
                .max()
                .unwrap_or(self.state.player.floor)
        })
    }
}

fn passive_usage(description: &str) -> Value {
    json!({"description":description,"activation":"passive",
        "consumable":false,"restrictions":[]})
}

fn active_usage(item: &str, description: &str, consumable: bool, restrictions: &[&str]) -> Value {
    json!({"description":description,"activation":"use_item","consumable":consumable,
        "command":{"type":"use_item","item":item},"restrictions":restrictions})
}
