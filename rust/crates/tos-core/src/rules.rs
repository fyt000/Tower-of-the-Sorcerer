//! Compile authored JSON options once. Gameplay reads typed rules; the original
//! JSON stays in Campaign for editing, extension metadata and save identity.
use crate::EnemySpecial;
use crate::original::*;
use serde::Deserialize;
use serde_json::Value;
use std::collections::BTreeMap;

#[derive(Clone, Debug, Deserialize)]
#[serde(default)]
pub(crate) struct Rules {
    pub empty_tile: u16,
    pub hero_attacks_first: bool,
    pub base_attack_guard: bool,
    pub cross_multiplier: i64,
    pub dragon_slayer_multiplier: i64,
    pub magician_a_damage: i64,
    pub magician_b_damage: i64,
    pub altar_base_cost: i64,
    pub altar_hp_gain: i64,
    pub altar_attack_gain: i64,
    pub altar_defense_gain: i64,
    pub forecast_requires_item: Option<String>,
    pub save_requires_hero_orb: bool,
    pub flying_requires_stairs: bool,
    pub flying_original_selection: bool,
    pub wisdom_dialogue_range: Option<[u32; 2]>,
    pub area_scaling: Vec<AreaScaling>,
    pub bomb_tile_ranges: Vec<[u16; 2]>,
    pub wall_break_tile_ranges: Option<Vec<[u16; 2]>>,
    pub magician_retreat: Option<MagicianRetreat>,
    #[serde(deserialize_with = "stair_links")]
    pub stair_links: BTreeMap<(i32, bool), i32>,
    pub backside: Backside,
    pub presentation: Timing,
}

impl Rules {
    pub fn compile(source: &Value) -> Result<Self, String> {
        if source.is_null() {
            Ok(Self::default())
        } else {
            serde_json::from_value(source.clone()).map_err(|error| format!("rules: {error}"))
        }
    }
}

impl Default for Rules {
    fn default() -> Self {
        Self {
            empty_tile: 0,
            hero_attacks_first: true,
            base_attack_guard: true,
            cross_multiplier: CROSS_MULTIPLIER,
            dragon_slayer_multiplier: DRAGON_SLAYER_MULTIPLIER,
            magician_a_damage: MAGICIAN_A_DAMAGE,
            magician_b_damage: MAGICIAN_B_DAMAGE,
            altar_base_cost: ALTAR_BASE_COST,
            altar_hp_gain: ALTAR_HP_GAIN,
            altar_attack_gain: ALTAR_ATTACK_GAIN,
            altar_defense_gain: ALTAR_DEFENSE_GAIN,
            forecast_requires_item: None,
            save_requires_hero_orb: false,
            flying_requires_stairs: true,
            flying_original_selection: false,
            wisdom_dialogue_range: None,
            area_scaling: vec![],
            bomb_tile_ranges: BOMB_TILE_RANGES.into_iter().map(|(a, b)| [a, b]).collect(),
            wall_break_tile_ranges: None,
            magician_retreat: None,
            stair_links: BTreeMap::new(),
            backside: Backside::default(),
            presentation: Timing::default(),
        }
    }
}

#[derive(Clone, Debug, Deserialize)]
#[serde(deny_unknown_fields)]
pub(crate) struct MagicianRetreat {
    pub floor: i32,
    pub special: EnemySpecial,
    #[serde(default)]
    pub bounds: RetreatBounds,
}

#[derive(Clone, Copy, Debug, Default, Deserialize, PartialEq, Eq)]
#[serde(rename_all = "snake_case")]
pub(crate) enum RetreatBounds {
    #[default]
    Corrected,
    Original,
}

#[derive(Clone, Debug, Deserialize)]
pub(crate) struct AreaScaling {
    pub max_floor: i32,
    pub multiplier: i64,
}

#[derive(Clone, Debug, Deserialize)]
#[serde(default)]
pub(crate) struct Backside {
    pub enabled: bool,
    pub carry_stats: bool,
    pub reset_gold: bool,
    pub multiplier: i64,
}

impl Default for Backside {
    fn default() -> Self {
        Self {
            enabled: false,
            carry_stats: true,
            reset_gold: true,
            multiplier: BACKSIDE_MULTIPLIER,
        }
    }
}

#[derive(Clone, Debug, Deserialize)]
#[serde(default)]
pub(crate) struct Timing {
    pub tile_transition_ms: u64,
    pub combat_strike_ms: u64,
    pub floor_transition_ms: u64,
}

impl Default for Timing {
    fn default() -> Self {
        Self {
            tile_transition_ms: 400,
            combat_strike_ms: COMBAT_STRIKE_MS,
            floor_transition_ms: FLOOR_TRANSITION_MS,
        }
    }
}

fn stair_links<'de, D: serde::Deserializer<'de>>(
    deserializer: D,
) -> Result<BTreeMap<(i32, bool), i32>, D::Error> {
    use serde::de::Error;
    BTreeMap::<String, i32>::deserialize(deserializer)?
        .into_iter()
        .map(|(key, target)| {
            let (floor, direction) = key
                .split_once(':')
                .ok_or_else(|| D::Error::custom("expected floor:up or floor:down"))?;
            let floor = floor.parse().map_err(D::Error::custom)?;
            let up = match direction {
                "up" => true,
                "down" => false,
                _ => return Err(D::Error::custom("invalid stair direction")),
            };
            Ok(((floor, up), target))
        })
        .collect()
}
