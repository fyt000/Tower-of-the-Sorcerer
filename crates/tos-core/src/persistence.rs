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

#[derive(Clone, Debug, Serialize, Deserialize)]
pub(crate) struct Save {
    pub(crate) version: u32,
    pub(crate) campaign_id: String,
    pub(crate) campaign_fingerprint: String,
    pub(crate) player: Player,
    pub(crate) floors: BTreeMap<i32, Vec<u16>>,
    pub(crate) visited_floors: BTreeSet<i32>,
    pub(crate) flags: BTreeSet<String>,
    pub(crate) event_counts: BTreeMap<String, u32>,
    pub(crate) shop_visits: BTreeMap<String, i64>,
    pub(crate) log: Vec<String>,
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

impl Engine {
    pub fn save_json(&self) -> String {
        // This concrete structure contains only JSON-supported fields; it has
        // no fallible custom serializers, unsupported map keys or NaN floats.
        serde_json::to_string(&self.state).expect("Save has an infallible JSON representation")
    }

    pub fn load_json(&mut self, source: &str) -> Result<(), String> {
        let save: Save = serde_json::from_str(source).map_err(|e| format!("Invalid save: {e}"))?;
        if !(1..=MAX_CYCLE).contains(&save.cycle)
            || save.version != SAVE_VERSION
            || save.campaign_id != self.campaign.id
            || save.campaign_fingerprint != self.state.campaign_fingerprint
        {
            return Err("Save belongs to a different campaign or campaign revision".into());
        }
        validate_player(&save.player)?;
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
