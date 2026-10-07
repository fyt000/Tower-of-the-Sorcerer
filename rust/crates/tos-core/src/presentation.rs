//! Ordered, typed renderer messages describe committed results;
//! the UI owns timing and never mutates gameplay through an animation callback.
use crate::{
    Direction, Enemy, EnemySpecial, Engine, Forecast, Player,
    battle_log::{BattleHeroStats, BattleLogEntry, BattleOutcome},
    original::*,
};
use serde::{Deserialize, Serialize};
use serde_json::{Value, json};
use std::collections::BTreeMap;

#[derive(Clone, Debug, Serialize, Deserialize)]
pub(crate) struct ActionResult {
    pub ok: bool,
    #[serde(rename = "type", skip_serializing_if = "Option::is_none")]
    pub kind: Option<String>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub message: Option<String>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub presentation: Option<Vec<Presentation>>,
}

impl ActionResult {
    pub fn message(text: &str) -> Self {
        Self {
            ok: true,
            kind: None,
            message: Some(text.into()),
            presentation: None,
        }
    }

    pub fn command(kind: &str) -> Self {
        Self {
            ok: true,
            kind: Some(kind.into()),
            message: None,
            presentation: Some(vec![]),
        }
    }
}

#[derive(Clone, Debug, Serialize, Deserialize)]
#[serde(tag = "type", rename_all = "snake_case")]
pub(crate) enum Presentation {
    Dialogue {
        text: String,
        dialogue_id: Option<u32>,
        duration_ms: u64,
        log_id: Option<u64>,
        activity: String,
    },
    Wait {
        duration_ms: u64,
    },
    Audio {
        name: String,
    },
    Journal {
        entries: Vec<Value>,
    },
    Move {
        from: Location,
        to: Location,
        direction: Direction,
        duration_ms: u64,
    },
    Tile {
        floor: i32,
        x: usize,
        y: usize,
        tile: u16,
        duration_ms: u64,
    },
    MoveTile {
        floor: i32,
        from_x: usize,
        from_y: usize,
        x: usize,
        y: usize,
        tile: u16,
        duration_ms: u64,
    },
    Floor {
        from: i32,
        to: i32,
        x: usize,
        y: usize,
        player: Player,
        tiles: Vec<u16>,
        direction: Direction,
        style: String,
        sound: String,
        duration_ms: u64,
    },
    Battle(Box<BattlePresentation>),
    Damage(StrikePresentation),
    Cinematic(Cinematic),
}

#[derive(Clone, Debug, Serialize, Deserialize)]
pub(crate) struct Location {
    pub floor: i32,
    pub x: usize,
    pub y: usize,
}

#[derive(Clone, Debug, Serialize, Deserialize)]
pub(crate) struct StrikePresentation {
    pub floor: i32,
    pub x: usize,
    pub y: usize,
    pub hero_hp: i64,
    pub enemy_hp: i64,
    pub hero_hit: i64,
    pub enemy_hit: i64,
    pub hero_strikes: i64,
    pub enemy_strikes: i64,
    pub enemy_first: bool,
    pub strike_ms: u64,
    pub hit_sound: String,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub sound_phase: Option<f64>,
    pub overlay_phase: f64,
    pub overlay_end_phase: f64,
    pub damage_phase: f64,
    pub duration_ms: u64,
}

#[derive(Clone, Debug, Serialize, Deserialize)]
pub(crate) struct BattlePresentation {
    #[serde(flatten)]
    pub strike: StrikePresentation,
    pub enemy_name: String,
    pub enemy_attack: i64,
    pub enemy_defense: i64,
    pub gold: i64,
    pub rounds: i64,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub log_id: Option<u64>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub damage: Option<i64>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub reward: Option<i64>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub hero_after_hp: Option<i64>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub activity: Option<String>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub battle_log: Option<BattleLogEntry>,
}

/// Only the tile transition affects how the next state write is presented.
/// Other cinematic kinds and artwork parameters remain renderer extensions.
#[derive(Clone, Debug, PartialEq, Eq)]
pub(crate) enum CinematicKind {
    TileReveal,
    Other(String),
}

impl CinematicKind {
    pub fn as_str(&self) -> &str {
        match self {
            Self::TileReveal => "tile_reveal",
            Self::Other(kind) => kind,
        }
    }
}

impl Serialize for CinematicKind {
    fn serialize<S: serde::Serializer>(&self, serializer: S) -> Result<S::Ok, S::Error> {
        serializer.serialize_str(self.as_str())
    }
}

impl<'de> Deserialize<'de> for CinematicKind {
    fn deserialize<D: serde::Deserializer<'de>>(deserializer: D) -> Result<Self, D::Error> {
        let kind = String::deserialize(deserializer)?;
        Ok(if kind == "tile_reveal" {
            Self::TileReveal
        } else {
            Self::Other(kind)
        })
    }
}

#[derive(Clone, Debug, Serialize, Deserialize)]
pub(crate) struct Cinematic {
    pub kind: CinematicKind,
    #[serde(
        default,
        deserialize_with = "present_value",
        skip_serializing_if = "Option::is_none"
    )]
    pub floor: Option<i32>,
    #[serde(
        default,
        deserialize_with = "present_value",
        skip_serializing_if = "Option::is_none"
    )]
    pub x: Option<usize>,
    #[serde(
        default,
        deserialize_with = "present_value",
        skip_serializing_if = "Option::is_none"
    )]
    pub y: Option<usize>,
    #[serde(
        default,
        deserialize_with = "present_value",
        skip_serializing_if = "Option::is_none"
    )]
    pub from_tile: Option<u16>,
    #[serde(
        default,
        deserialize_with = "present_value",
        skip_serializing_if = "Option::is_none"
    )]
    pub tile: Option<u16>,
    #[serde(flatten)]
    pub artwork: BTreeMap<String, Value>,
}

fn present_value<'de, D: serde::Deserializer<'de>, T: Deserialize<'de>>(
    deserializer: D,
) -> Result<Option<T>, D::Error> {
    T::deserialize(deserializer).map(Some)
}

impl Engine {
    pub(crate) fn present(&mut self, effect: Presentation) {
        if self.rules.wisdom_dialogue_range.is_some()
            && let Presentation::Dialogue {
                text, dialogue_id, ..
            } = &effect
        {
            let player = &self.state.player;
            let (floor, x, y) =
                self.state
                    .pending_tile
                    .unwrap_or((player.floor, player.x, player.y));
            let title = self
                .state
                .pending_interaction
                .as_ref()
                .and_then(|interaction| interaction["title"].as_str())
                .unwrap_or("Dialogue")
                .to_string();
            self.record_journal(floor, x, y, &title, text, *dialogue_id);
        }
        self.last_action
            .presentation
            .get_or_insert_default()
            .push(effect);
    }

    pub(crate) fn present_move(&mut self, from: &Player, x: usize, y: usize, dx: isize, dy: isize) {
        self.present(Presentation::Move {
            from: Location {
                floor: from.floor,
                x: from.x,
                y: from.y,
            },
            to: Location {
                floor: from.floor,
                x,
                y,
            },
            direction: if dx > 0 {
                Direction::Right
            } else if dx < 0 {
                Direction::Left
            } else if dy > 0 {
                Direction::Down
            } else {
                Direction::Up
            },
            duration_ms: WALK_STEP_MS,
        });
    }

    pub(crate) fn present_tile_transition(
        &mut self,
        floor: i32,
        x: usize,
        y: usize,
        tile: u16,
        style: &str,
    ) {
        let from_tile = self
            .tile_at(floor, x, y)
            .expect("validated transition tile");
        let duration_ms = self.rules.presentation.tile_transition_ms;
        self.present(Presentation::Cinematic(Cinematic {
            kind: CinematicKind::TileReveal, floor: Some(floor), x: Some(x), y: Some(y), from_tile: Some(from_tile), tile: Some(tile),
            artwork: serde_json::from_value(json!({"style":style,"original_steps":16,"duration_ms":duration_ms,"sound_cue":"open","sound_offsets_ms":[0]})).expect("artwork object"),
        }));
    }

    pub(crate) fn break_wall(&mut self, floor: i32, x: usize, y: usize) {
        self.present_tile_transition(floor, x, y, self.empty_tile(), "wall_collapse");
        self.clear(floor, x, y);
    }

    pub(crate) fn present_bomb(&mut self, floor: i32, x: usize, y: usize) {
        // toroad2 (0x44bc34): five inverse-mask frames replace the enemy
        // with road. The original repeats open.wav at every mask frame.
        self.present(Presentation::Cinematic(Cinematic {
            kind: CinematicKind::Other("magic".into()), floor: Some(floor), x: Some(x), y: Some(y), from_tile: None, tile: Some(self.empty_tile()),
            artwork: serde_json::from_value(json!({"style":"dissolve","underlying_tile":self.tile_at(floor,x,y),"color_tile":self.empty_tile(),"frames":[166,170,174,178,182],"duration_ms":750,"sound_cue":"open","sound_offsets_ms":[0,150,300,450,600]})).expect("artwork object"),
        }));
    }

    pub(crate) fn present_magic_damage(&mut self, floor: i32, x: usize, y: usize, damage: i64) {
        // madoushi1 (0x44c464) queues open.wav, the directional damaged
        // hero/mask pair, and the HP display update at the entered square.
        self.present(Presentation::Damage(StrikePresentation {
            floor,
            x,
            y,
            hero_hp: self.state.player.hp,
            enemy_hp: 0,
            hero_hit: 0,
            enemy_hit: damage,
            hero_strikes: 0,
            enemy_strikes: 1,
            enemy_first: true,
            strike_ms: 450,
            hit_sound: "open".into(),
            sound_phase: None,
            overlay_phase: 1.0 / 3.0,
            overlay_end_phase: 2.0 / 3.0,
            damage_phase: 2.0 / 3.0,
            duration_ms: 450,
        }));
    }

    pub(crate) fn present_floor(&mut self, from: i32, transition: &str, duration_ms: Option<u64>) {
        let target = self.state.player.floor;
        self.present(Presentation::Floor {
            from,
            to: target,
            x: self.state.player.x,
            y: self.state.player.y,
            player: self.state.player.clone(),
            tiles: self.state.floors[&target].clone(),
            direction: if target >= from {
                Direction::Up
            } else {
                Direction::Down
            },
            style: transition.into(),
            sound: if transition == "original_spiral" {
                "kai"
            } else {
                "none"
            }
            .into(),
            duration_ms: duration_ms
                .unwrap_or(self.rules.presentation.floor_transition_ms)
                .clamp(30, 10_000),
        });
    }

    pub(crate) fn present_battle(
        &mut self,
        enemy: &Enemy,
        battle: &Forecast,
        floor: i32,
        x: usize,
        y: usize,
        enemy_first: bool,
    ) -> BattleLogEntry {
        let enemy_name = self
            .state
            .last_encounter
            .as_ref()
            .filter(|entry| (entry.floor, entry.x, entry.y) == (floor, x, y))
            .map(|entry| entry.enemy_name.clone())
            .unwrap_or_else(|| enemy.name.clone());
        let multiplier = match enemy.special {
            EnemySpecial::Undead if self.state.player.inventory.iter().any(|i| i == "cross") => {
                self.rules.cross_multiplier
            }
            EnemySpecial::Dragon
                if self
                    .state
                    .player
                    .inventory
                    .iter()
                    .any(|i| i == "dragon_slayer") =>
            {
                self.rules.dragon_slayer_multiplier
            }
            _ => 1,
        };
        let hero_hit = (self.state.player.attack.saturating_mul(multiplier) - enemy.defense).max(1);
        let enemy_hit = (enemy.attack - self.state.player.defense).max(0);
        let base_hero_first = self.rules.hero_attacks_first;
        let first = enemy_first || !base_hero_first;
        let mut hero_strikes = (enemy.hp - 1) / hero_hit + 1;
        let mut enemy_strikes = battle.rounds + i64::from(enemy_first && base_hero_first);
        if enemy_hit > 0 && enemy_strikes.saturating_mul(enemy_hit) >= self.state.player.hp {
            enemy_strikes = (self.state.player.hp - 1) / enemy_hit + 1;
            hero_strikes = enemy_strikes - i64::from(first);
        }
        let strike_ms = self.rules.presentation.combat_strike_ms;
        let duration_ms =
            (hero_strikes.saturating_add(enemy_strikes).max(1) as u64).saturating_mul(strike_ms);
        self.present(Presentation::Battle(Box::new(BattlePresentation {
            strike: StrikePresentation {
                floor,
                x,
                y,
                hero_hp: self.state.player.hp,
                enemy_hp: enemy.hp,
                hero_hit,
                enemy_hit,
                hero_strikes,
                enemy_strikes,
                enemy_first: first,
                strike_ms,
                hit_sound: "taisen".into(),
                sound_phase: Some(0.0),
                overlay_phase: 1.0 / 3.0,
                overlay_end_phase: 2.0 / 3.0,
                damage_phase: 2.0 / 3.0,
                duration_ms,
            },
            enemy_name: enemy_name.clone(),
            enemy_attack: enemy.attack,
            enemy_defense: enemy.defense,
            gold: battle.gold,
            rounds: battle.rounds,
            log_id: None,
            damage: None,
            reward: None,
            hero_after_hp: None,
            activity: None,
            battle_log: None,
        })));
        BattleLogEntry {
            log_id: 0,
            cycle: self.state.cycle,
            floor,
            x,
            y,
            enemy_name,
            enemy_hp: enemy.hp,
            enemy_attack: enemy.attack,
            enemy_defense: enemy.defense,
            hero_before: BattleHeroStats {
                hp: self.state.player.hp,
                attack: self.state.player.attack,
                defense: self.state.player.defense,
                gold: self.state.player.gold,
            },
            hero_after_hp: self.state.player.hp,
            damage: 0,
            reward: 0,
            hero_hit,
            enemy_hit,
            rounds: enemy_strikes,
            hero_strikes,
            enemy_strikes,
            enemy_first: first,
            outcome: BattleOutcome::Defeated,
        }
    }
}
