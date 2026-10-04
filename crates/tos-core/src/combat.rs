//! Combat forecasting; one calculation shared by inspection and execution.
use crate::{Enemy, EnemySpecial, Engine, Player, original::*};
use serde::Serialize;
use serde_json::Value;

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

impl Engine {
    /// Resolve this tile's actual encounter before applying Lucky Gold.
    /// Stats remain the enemy row's full cycle-scaled values for body parts.
    pub(crate) fn enemy_for_tile(&self, key: &str, tile: u16) -> Option<Enemy> {
        let mut enemy = self.enemy(key)?;
        let definition = self.campaign.tiles.get(&tile.to_string())?;
        enemy.gold /= definition.reward_divisor.unwrap_or(1);
        Some(enemy)
    }
}

/// Hero strikes first; the last strike never receives a counterattack.
pub fn forecast(player: &Player, enemy: &Enemy) -> Forecast {
    forecast_with_rules(player, enemy, &Value::Null)
}

pub(crate) fn forecast_with_rules(player: &Player, enemy: &Enemy, rules: &Value) -> Forecast {
    let base_damage = player.attack - enemy.defense;
    let multiplier = match enemy.special {
        EnemySpecial::Undead if player.inventory.iter().any(|s| s == "cross") => {
            rules["cross_multiplier"]
                .as_i64()
                .unwrap_or(CROSS_MULTIPLIER)
                .clamp(1, 1000)
        }
        EnemySpecial::Dragon if player.inventory.iter().any(|s| s == "dragon_slayer") => {
            rules["dragon_slayer_multiplier"]
                .as_i64()
                .unwrap_or(DRAGON_SLAYER_MULTIPLIER)
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
