//! Save-file decoding and validation. Loading is atomic: no playable state is
//! replaced until campaign identity, geometry and statistics have been checked.
use crate::campaign::{MAX_STAT, validate_player};
use crate::domain::GameStatus;
use crate::{Enemy, Engine, Player};
use serde::{Deserialize, Serialize};
use serde_json::{Value, json};
use std::collections::{BTreeMap, BTreeSet};

/// Version 1 is the shipped save wire format. Change this only with migration.
pub(crate) const SAVE_VERSION: u32 = 1;
/// Application guard on repeated backside cycles, rather than an original-game
/// rule. It limits scaling and accepts all existing generated saves.
pub(crate) const MAX_CYCLE: u32 = 1_000;
/// A defensive save-input bound for per-shop purchases (including altar visits).
const MAX_SHOP_VISITS: i64 = 1_000_000;

/// Only speech or inscriptions already encountered by this player.
#[derive(Clone, Debug, PartialEq, Eq, Serialize, Deserialize)]
#[serde(deny_unknown_fields)]
pub(crate) struct JournalEntry {
    pub(crate) cycle: u32,
    pub(crate) floor: i32,
    pub(crate) x: usize,
    pub(crate) y: usize,
    pub(crate) title: String,
    pub(crate) text: String,
    #[serde(default, skip_serializing_if = "Option::is_none")]
    pub(crate) dialogue_id: Option<u32>,
}

/// Raw information observed through real enemy contact, independent of Hero.
#[derive(Clone, Debug, PartialEq, Eq, Serialize, Deserialize)]
#[serde(deny_unknown_fields)]
pub(crate) struct Encounter {
    pub(crate) cycle: u32,
    pub(crate) floor: i32,
    pub(crate) x: usize,
    pub(crate) y: usize,
    pub(crate) tile: u16,
    pub(crate) enemy_name: String,
    pub(crate) hp: i64,
    pub(crate) attack: i64,
    pub(crate) defense: i64,
}

#[derive(Clone, Debug, Serialize, Deserialize)]
pub(crate) struct Save {
    pub(crate) version: u32,
    pub(crate) campaign_id: String,
    pub(crate) campaign_fingerprint: String,
    pub(crate) player: Player,
    pub(crate) floors: BTreeMap<i32, Vec<u16>>,
    pub(crate) visited_floors: BTreeSet<i32>,
    /// The original Flight Orb's upper bound advances through stairs, not wings.
    /// Legacy saves omit this; their highest visited floor supplies a fallback.
    #[serde(default)]
    pub(crate) highest_stair_floor: Option<i32>,
    pub(crate) flags: BTreeSet<String>,
    pub(crate) event_counts: BTreeMap<String, u32>,
    pub(crate) shop_visits: BTreeMap<String, i64>,
    pub(crate) log: Vec<String>,
    /// Stable ID of log[0]; old save files begin at zero.
    #[serde(default)]
    pub(crate) log_start: u64,
    #[serde(default)]
    pub(crate) battle_log: Vec<crate::battle_log::BattleLogEntry>,
    #[serde(default)]
    pub(crate) journal: Vec<JournalEntry>,
    #[serde(default)]
    pub(crate) last_encounter: Option<Encounter>,
    pub(crate) status: GameStatus,
    pub(crate) steps: u64,
    pub(crate) pending_interaction: Option<Value>,
    pub(crate) pending_tile: Option<(i32, usize, usize)>,
    #[serde(default)]
    pub(crate) enemy_overrides: BTreeMap<String, Enemy>,
    #[serde(default = "first_cycle")]
    pub(crate) cycle: u32,
}

fn first_cycle() -> u32 {
    1
}

/// Internal worker replacement format; portable player saves stay unchanged.
#[derive(Serialize, Deserialize)]
#[serde(deny_unknown_fields)]
struct RuntimeCheckpoint {
    version: u32,
    save: String,
    last_action: Value,
}

impl Engine {
    /// The original Hero Orb unlocks player-created save points. Internal
    /// autosaves and worker replacement still serialize their state directly.
    pub fn save_unlocked(&self) -> bool {
        !self.campaign.rules["save_requires_hero_orb"]
            .as_bool()
            .unwrap_or(false)
            || self
                .state
                .player
                .inventory
                .iter()
                .any(|item| item == "hero_orb")
    }

    pub fn ensure_player_save_allowed(&self) -> Result<(), String> {
        if self.save_unlocked() {
            Ok(())
        } else {
            Err("The Hero Orb is required to save your game.".into())
        }
    }

    /// Preserve the latest action/dialogue timeline as well as the playable save.
    pub fn runtime_checkpoint_json(&self) -> String {
        serde_json::to_string(&RuntimeCheckpoint {
            version: 1,
            save: self.save_json(),
            last_action: self.last_action.clone(),
        })
        .expect("Runtime checkpoint has an infallible JSON representation")
    }

    /// Validate on a copy so an incompatible rebuilt worker cannot lose progress.
    pub fn restore_runtime_checkpoint_json(&mut self, source: &str) -> Result<(), String> {
        let checkpoint: RuntimeCheckpoint = serde_json::from_str(source)
            .map_err(|error| format!("Invalid runtime checkpoint: {error}"))?;
        if checkpoint.version != 1 || !checkpoint.last_action.is_object() {
            return Err("Unsupported runtime checkpoint".into());
        }
        let mut restored = self.clone();
        restored.load_json(&checkpoint.save)?;
        restored.last_action = checkpoint.last_action;
        *self = restored;
        Ok(())
    }

    pub fn save_json(&self) -> String {
        // This concrete structure contains only JSON-supported fields; it has
        // no fallible custom serializers, unsupported map keys or NaN floats.
        serde_json::to_string(&self.state).expect("Save has an infallible JSON representation")
    }

    pub fn load_json(&mut self, source: &str) -> Result<(), String> {
        let mut save: Save =
            serde_json::from_str(source).map_err(|e| format!("Invalid save: {e}"))?;
        if !(1..=MAX_CYCLE).contains(&save.cycle)
            || save.version != SAVE_VERSION
            || save.campaign_id != self.campaign.id
            || save.campaign_fingerprint != self.state.campaign_fingerprint
        {
            return Err("Save belongs to a different campaign or campaign revision".into());
        }
        validate_player(&save.player)?;
        self.campaign.validate_equipment(&save.player)?;
        let source_value: Value =
            serde_json::from_str(source).map_err(|e| format!("Invalid save: {e}"))?;
        // A null slot is intentional. Only pre-slot save files are inferred,
        // without reapplying any previously collected stat bonuses.
        save.player.infer_equipment(
            &self.campaign,
            source_value["player"].get("weapon").is_none(),
            source_value["player"].get("shield").is_none(),
        );
        if save.player.x >= self.campaign.width
            || save.player.y >= self.campaign.height
            || !save.floors.contains_key(&save.player.floor)
        {
            return Err("Save contains an invalid player location".into());
        }
        if save.floors.len() != self.campaign.floors.len()
            || self
                .campaign
                .floors
                .iter()
                .any(|f| !save.floors.contains_key(&f.id))
        {
            return Err("Save floor set differs from the campaign".into());
        }
        for tiles in save.floors.values() {
            if tiles.len() != self.campaign.width * self.campaign.height
                || tiles
                    .iter()
                    .any(|id| !self.campaign.tiles.contains_key(&id.to_string()))
            {
                return Err("Save contains invalid floor tiles".into());
            }
        }
        if save
            .visited_floors
            .iter()
            .any(|floor| !save.floors.contains_key(floor))
            || save
                .shop_visits
                .values()
                .any(|n| !(0..=MAX_SHOP_VISITS).contains(n))
        {
            return Err("Save contains invalid visits or shop counters".into());
        }
        if save
            .highest_stair_floor
            .is_some_and(|floor| !save.floors.contains_key(&floor))
        {
            return Err("Save contains an invalid highest stair floor".into());
        }
        if !self.validate_battle_log(&save) {
            return Err("Save contains an invalid battle log or activity identifier".into());
        }
        if save.journal.iter().any(|entry| {
            entry.cycle == 0
                || entry.cycle > save.cycle
                || !save.floors.contains_key(&entry.floor)
                || entry.x >= self.campaign.width
                || entry.y >= self.campaign.height
                || entry.title.trim().is_empty()
                || entry.text.trim().is_empty()
                || entry
                    .dialogue_id
                    .is_some_and(|id| !self.wisdom_clue_id(Some(id)))
        }) {
            return Err("Save contains an invalid journal entry".into());
        }
        if save.last_encounter.as_ref().is_some_and(|encounter| {
            encounter.cycle != save.cycle
                || !save.floors.contains_key(&encounter.floor)
                || encounter.x >= self.campaign.width
                || encounter.y >= self.campaign.height
                || !self
                    .campaign
                    .tiles
                    .get(&encounter.tile.to_string())
                    .is_some_and(|tile| tile.enemy.is_some())
                || encounter.enemy_name.trim().is_empty()
                || !(1..=MAX_STAT).contains(&encounter.hp)
                || !(0..=MAX_STAT).contains(&encounter.attack)
                || !(0..=MAX_STAT).contains(&encounter.defense)
        }) {
            return Err("Save contains an invalid last encounter".into());
        }
        for (key, enemy) in &save.enemy_overrides {
            if !self.campaign.enemies.contains_key(key)
                || enemy.hp <= 0
                || [enemy.hp, enemy.attack, enemy.defense, enemy.gold]
                    .iter()
                    .any(|n| !(0..=MAX_STAT).contains(n))
            {
                return Err("Save contains invalid enemy statistics".into());
            }
        }
        if save.pending_interaction.is_some() != save.pending_tile.is_some() {
            return Err("Save has an incomplete interaction".into());
        }
        if let Some((floor, x, y)) = save.pending_tile
            && (!save.floors.contains_key(&floor)
                || x >= self.campaign.width
                || y >= self.campaign.height)
        {
            return Err("Save has an invalid interaction position".into());
        }
        // Rejected data leaves both the world and the last action unchanged.
        self.state = save;
        self.last_action = json!({"ok":true,"message":"Save loaded"});
        Ok(())
    }
}

/// Standard 64-bit FNV-1a constants. This existing algorithm is part of save
/// compatibility, so replacing it with DefaultHasher would invalidate saves.
const FNV_OFFSET_BASIS: u64 = 0xcbf2_9ce4_8422_2325;
const FNV_PRIME: u64 = 0x0000_0100_0000_01b3;

/// Stable FNV-1a over the serialized canonical campaign, independent of host or
/// WASM hashers. The output remains the shipped 16-digit lowercase hex string.
pub(crate) fn fingerprint(source: &str) -> String {
    let mut hash = FNV_OFFSET_BASIS;
    for byte in source.bytes() {
        hash ^= u64::from(byte);
        hash = hash.wrapping_mul(FNV_PRIME);
    }
    format!("{hash:016x}")
}

#[cfg(test)]
mod tests {
    use super::fingerprint;

    #[test]
    fn standard_fnv_vectors_preserve_the_shipped_hash_format() {
        assert_eq!(fingerprint(""), "cbf29ce484222325");
        assert_eq!(fingerprint("a"), "af63dc4c8601ec8c");
        assert_eq!(fingerprint("hello"), "a430d84680aabd0b");
    }
}
