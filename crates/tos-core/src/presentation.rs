//! Ordered renderer messages. These JSON payloads describe committed results;
//! the UI owns timing and never mutates gameplay through an animation callback.
use crate::{Enemy, EnemySpecial, Engine, Forecast, Player, original::*};
use serde_json::{Value, json};

impl Engine {
    pub(crate) fn present(&mut self, effect: Value) {
        if !self.last_action["presentation"].is_array() {
            self.last_action["presentation"] = json!([]);
        }
        self.last_action["presentation"]
            .as_array_mut()
            .expect("presentation was initialized as an array immediately above")
            .push(effect);
    }

    pub(crate) fn present_move(&mut self, from: &Player, x: usize, y: usize, dx: isize, dy: isize) {
        self.present(json!({"type":"move","from":{"floor":from.floor,"x":from.x,"y":from.y},"to":{"floor":from.floor,"x":x,"y":y},"direction":if dx>0{"right"}else if dx<0{"left"}else if dy>0{"down"}else{"up"},"duration_ms":WALK_STEP_MS}));
    }

    pub(crate) fn present_floor(&mut self, from: i32, transition: &str, duration_ms: Option<u64>) {
        let target = self.state.player.floor;
        self.present(json!({"type":"floor","from":from,"to":target,
            "x":self.state.player.x,"y":self.state.player.y,
            "player":self.state.player,"tiles":self.state.floors.get(&target),
            "direction":if target>=from{"up"}else{"down"},
            "style":transition,"sound":if transition=="original_spiral"{"kai"}else{"none"},
            "duration_ms":duration_ms.or_else(||self.campaign.rules["presentation"]["floor_transition_ms"].as_u64()).unwrap_or(FLOOR_TRANSITION_MS).clamp(30,10_000)}));
    }

    pub(crate) fn present_battle(
        &mut self,
        enemy: &Enemy,
        battle: &Forecast,
        floor: i32,
        x: usize,
        y: usize,
        enemy_first: bool,
    ) {
        let multiplier = match enemy.special {
            EnemySpecial::Undead if self.state.player.inventory.iter().any(|i| i == "cross") => {
                self.campaign.rules["cross_multiplier"]
                    .as_i64()
                    .unwrap_or(CROSS_MULTIPLIER)
            }
            EnemySpecial::Dragon
                if self
                    .state
                    .player
                    .inventory
                    .iter()
                    .any(|i| i == "dragon_slayer") =>
            {
                self.campaign.rules["dragon_slayer_multiplier"]
                    .as_i64()
                    .unwrap_or(DRAGON_SLAYER_MULTIPLIER)
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
            .unwrap_or(COMBAT_STRIKE_MS)
            .clamp(60, 3_000);
        let duration_ms =
            (hero_strikes.saturating_add(enemy_strikes).max(1) as u64).saturating_mul(strike_ms);
        self.present(json!({"type":"battle","enemy_name":enemy.name,"enemy_hp":enemy.hp,"hero_hp":self.state.player.hp,"hero_hit":hero_hit,"enemy_hit":enemy_hit,"rounds":battle.rounds,"hero_strikes":hero_strikes,"enemy_strikes":enemy_strikes,"enemy_first":first,"floor":floor,"x":x,"y":y,
            "strike_ms":strike_ms,"hit_sound":"taisen","sound_phase":0.0,"overlay_phase":1.0/3.0,"damage_phase":2.0/3.0,"duration_ms":duration_ms}));
    }
}
