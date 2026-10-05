//! Ordered renderer messages. These JSON payloads describe committed results;
//! the UI owns timing and never mutates gameplay through an animation callback.
use crate::{
    Enemy, EnemySpecial, Engine, Forecast, Player,
    battle_log::{BattleHeroStats, BattleLogEntry, BattleOutcome},
    original::*,
};
use serde_json::{Value, json};

impl Engine {
    pub(crate) fn present(&mut self, effect: Value) {
        if self.campaign.rules["wisdom_dialogue_range"].is_array()
            && effect["type"] == "dialogue"
            && let Some(text) = effect["text"].as_str()
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
            let dialogue_id = effect["dialogue_id"]
                .as_u64()
                .and_then(|id| u32::try_from(id).ok());
            self.record_journal(floor, x, y, &title, text, dialogue_id);
        }
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
        let duration_ms = self.campaign.rules["presentation"]["tile_transition_ms"]
            .as_u64()
            .unwrap_or(400)
            .clamp(60, 3_000);
        self.present(
            json!({"type":"cinematic","kind":"tile_reveal","style":style,
            "floor":floor,"x":x,"y":y,"from_tile":from_tile,"tile":tile,
            "original_steps":16,"duration_ms":duration_ms,
            "sound_cue":"open","sound_offsets_ms":[0]}),
        );
    }

    pub(crate) fn break_wall(&mut self, floor: i32, x: usize, y: usize) {
        self.present_tile_transition(floor, x, y, self.empty_tile(), "wall_collapse");
        self.clear(floor, x, y);
    }

    pub(crate) fn present_bomb(&mut self, floor: i32, x: usize, y: usize) {
        // toroad2 (0x44bc34): five inverse-mask frames replace the enemy
        // with road. The original repeats open.wav at every mask frame.
        self.present(json!({"type":"cinematic","kind":"magic","style":"dissolve",
            "floor":floor,"x":x,"y":y,"underlying_tile":self.tile_at(floor,x,y),
            "color_tile":self.empty_tile(),"tile":self.empty_tile(),"frames":[166,170,174,178,182],
            "duration_ms":750,"sound_cue":"open","sound_offsets_ms":[0,150,300,450,600]}));
    }

    pub(crate) fn present_magic_damage(&mut self, floor: i32, x: usize, y: usize, damage: i64) {
        // madoushi1 (0x44c464) queues open.wav, the directional damaged
        // hero/mask pair, and the HP display update at the entered square.
        self.present(json!({"type":"damage","floor":floor,"x":x,"y":y,
            "hero_hp":self.state.player.hp,"enemy_hp":0,"hero_hit":0,"enemy_hit":damage,
            "hero_strikes":0,"enemy_strikes":1,"enemy_first":true,
            "strike_ms":450,"hit_sound":"open","overlay_phase":1.0/3.0,
            "overlay_end_phase":2.0/3.0,"damage_phase":2.0/3.0,"duration_ms":450}));
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
                self.campaign.rules["cross_multiplier"]
                    .as_i64()
                    .unwrap_or(CROSS_MULTIPLIER)
                    .clamp(1, 1000)
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
                    .clamp(1, 1000)
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
        self.present(json!({"type":"battle","enemy_name":enemy_name,"enemy_hp":enemy.hp,"enemy_attack":enemy.attack,"enemy_defense":enemy.defense,"gold":battle.gold,"hero_hp":self.state.player.hp,"hero_hit":hero_hit,"enemy_hit":enemy_hit,"rounds":battle.rounds,"hero_strikes":hero_strikes,"enemy_strikes":enemy_strikes,"enemy_first":first,"floor":floor,"x":x,"y":y,
            "strike_ms":strike_ms,"hit_sound":"taisen","sound_phase":0.0,"overlay_phase":1.0/3.0,"overlay_end_phase":2.0/3.0,"damage_phase":2.0/3.0,"duration_ms":duration_ms}));
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
