//! Historical facts from resolved battles, associated with retained activities.
use crate::{Engine, campaign::MAX_STAT, domain::GameStatus};
use serde::{Deserialize, Serialize};
use serde_json::json;

#[derive(Clone, Debug, PartialEq, Eq, Serialize, Deserialize)]
#[serde(deny_unknown_fields)]
pub(crate) struct BattleHeroStats {
    pub(crate) hp: i64,
    pub(crate) attack: i64,
    pub(crate) defense: i64,
    pub(crate) gold: i64,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq, Serialize, Deserialize)]
#[serde(rename_all = "snake_case")]
pub(crate) enum BattleOutcome {
    Defeated,
    Lost,
}

/// A record contains no enemy key, script flags, inventory or undiscovered data.
/// `log_id == log_start + activity_index` identifies its existing text entry.
#[derive(Clone, Debug, PartialEq, Eq, Serialize, Deserialize)]
#[serde(deny_unknown_fields)]
pub(crate) struct BattleLogEntry {
    pub(crate) log_id: u64,
    pub(crate) cycle: u32,
    pub(crate) floor: i32,
    pub(crate) x: usize,
    pub(crate) y: usize,
    pub(crate) enemy_name: String,
    pub(crate) enemy_hp: i64,
    pub(crate) enemy_attack: i64,
    pub(crate) enemy_defense: i64,
    pub(crate) hero_before: BattleHeroStats,
    pub(crate) hero_after_hp: i64,
    pub(crate) damage: i64,
    pub(crate) reward: i64,
    pub(crate) hero_hit: i64,
    pub(crate) enemy_hit: i64,
    /// Actual enemy turns, including an opening strike and stopping at death.
    pub(crate) rounds: i64,
    pub(crate) hero_strikes: i64,
    pub(crate) enemy_strikes: i64,
    pub(crate) enemy_first: bool,
    pub(crate) outcome: BattleOutcome,
}

impl Engine {
    /// Call immediately after the battle's activity text, before later events
    /// can change hero stats. Capped gold and lethal HP loss are actual deltas.
    pub(crate) fn record_battle_log(&mut self, mut entry: BattleLogEntry) {
        entry.log_id = self
            .latest_log_id()
            .expect("resolved battle has an activity entry");
        entry.hero_after_hp = self.state.player.hp;
        entry.damage = entry.hero_before.hp - entry.hero_after_hp;
        entry.reward = self.state.player.gold - entry.hero_before.gold;
        entry.outcome = if self.state.status == GameStatus::Lost {
            BattleOutcome::Lost
        } else {
            BattleOutcome::Defeated
        };
        // A self-contained effect lets animated views add only this battle's
        // completed record without copying future activities from the snapshot.
        if let Some(effect) = self.last_action["presentation"]
            .as_array_mut()
            .and_then(|effects| effects.iter_mut().rev().find(|e| e["type"] == "battle"))
        {
            effect["log_id"] = json!(entry.log_id);
            effect["damage"] = json!(entry.damage);
            effect["reward"] = json!(entry.reward);
            effect["hero_after_hp"] = json!(entry.hero_after_hp);
            effect["activity"] = json!(self.state.log.last());
            effect["battle_log"] = json!(entry);
        }
        self.state.battle_log.push(entry);
    }

    pub(crate) fn validate_battle_log(&self, save: &crate::persistence::Save) -> bool {
        let Some(log_end) = save.log_start.checked_add(save.log.len() as u64) else {
            return false;
        };
        let mut previous = None;
        save.battle_log.iter().all(|entry| {
            let valid = entry.log_id >= save.log_start
                && entry.log_id < log_end
                && previous.is_none_or(|id| entry.log_id > id)
                && (1..=save.cycle).contains(&entry.cycle)
                && save.floors.contains_key(&entry.floor)
                && entry.x < self.campaign.width
                && entry.y < self.campaign.height
                && !entry.enemy_name.trim().is_empty()
                && (1..=MAX_STAT).contains(&entry.enemy_hp)
                && (1..=MAX_STAT).contains(&entry.hero_before.hp)
                && [
                    entry.enemy_attack,
                    entry.enemy_defense,
                    entry.hero_before.attack,
                    entry.hero_before.defense,
                    entry.hero_before.gold,
                    entry.hero_after_hp,
                    entry.damage,
                    entry.reward,
                ]
                .iter()
                .all(|stat| (0..=MAX_STAT).contains(stat))
                && entry.hero_after_hp + entry.damage == entry.hero_before.hp
                && entry.hero_before.gold + entry.reward <= MAX_STAT
                && (0..=MAX_STAT * 1000).contains(&entry.hero_hit)
                && [
                    entry.enemy_hit,
                    entry.rounds,
                    entry.hero_strikes,
                    entry.enemy_strikes,
                ]
                .iter()
                .all(|stat| (0..=MAX_STAT).contains(stat))
                && match entry.outcome {
                    BattleOutcome::Lost => entry.hero_after_hp == 0 && entry.reward == 0,
                    BattleOutcome::Defeated => entry.hero_after_hp > 0,
                };
            previous = Some(entry.log_id);
            valid
        })
    }
}
