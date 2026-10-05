//! Campaign scripts are decoded once at the input boundary. Gameplay matches
//! enums; string IDs identify campaign resources and never select operations.
//!
//! Cinematic payloads intentionally remain extensible JSON: the renderer owns
//! their presentation fields, and they cannot mutate simulation state.
use crate::campaign::MAX_STAT;
use crate::domain::GameStatus;
use crate::domain::Stat;
use crate::persistence::MAX_CYCLE;
use crate::presentation::{Cinematic, CinematicKind, Presentation};
use crate::{Campaign, Engine, Position, forecast_with_rules};
use serde::{Deserialize, Serialize};
use serde_json::{Value, json};
use std::collections::BTreeMap;

/// Presentation waits are bounded to keep an imported scene from stalling play.
const MAX_WAIT_MS: u64 = 30_000;
/// Default duration for an authored tile move. Extracted scenes supply their
/// own durations; this fallback belongs to the presentation configuration.
fn default_queue_ms() -> u64 {
    120
}
fn default_true() -> bool {
    true
}
fn default_transition() -> String {
    "original_spiral".into()
}

#[derive(Clone, Copy, Debug, Eq, PartialEq, Serialize, Deserialize)]
#[serde(rename_all = "snake_case")]
pub enum TriggerKind {
    Step,
    Bump,
    EnterFloor,
    StairsUp,
    EnemyDefeated,
    /// Floor-state callback after a completed battle or one entire Bomb use.
    PostCombat,
    Interact,
    /// A keyed door was contacted, including an attempt without a key.
    /// Runs after resolving the key/opening and before entering the square.
    DoorAttempted,
    DoorOpened,
}

#[derive(Clone, Debug, Serialize, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct Trigger {
    #[serde(rename = "type")]
    pub kind: TriggerKind,
    pub floor: Option<i32>,
    pub x: Option<usize>,
    pub y: Option<usize>,
    pub tile: Option<u16>,
    #[serde(default, skip_serializing_if = "Option::is_none")]
    pub positions: Option<Vec<Position>>,
}

impl Trigger {
    pub fn matches(
        &self,
        kind: TriggerKind,
        floor: i32,
        x: usize,
        y: usize,
        tile: Option<u16>,
    ) -> bool {
        self.kind == kind
            && self.floor.is_none_or(|v| v == floor)
            && self.x.is_none_or(|v| v == x)
            && self.y.is_none_or(|v| v == y)
            && self.tile.is_none_or(|v| Some(v) == tile)
            && self.positions.as_ref().is_none_or(|positions| {
                positions
                    .iter()
                    .any(|position| position.x == x && position.y == y)
            })
    }
}

#[derive(Clone, Debug, Serialize, Deserialize)]
#[serde(tag = "type", rename_all = "snake_case", deny_unknown_fields)]
pub enum Condition {
    Flag {
        flag: String,
        #[serde(default = "default_true")]
        value: bool,
    },
    HasItem {
        item: String,
    },
    Tile {
        floor: Option<i32>,
        x: usize,
        y: usize,
        tile: u16,
    },
    NoEnemies {
        floor: Option<i32>,
    },
    StatAtLeast {
        stat: Stat,
        amount: i64,
    },
    StatAtMost {
        stat: Stat,
        amount: i64,
    },
    CycleAtLeast {
        #[serde(alias = "amount")]
        cycle: u32,
    },
    CycleAtMost {
        #[serde(alias = "amount")]
        cycle: u32,
    },
    Any {
        conditions: Vec<Condition>,
    },
}

#[derive(Clone, Debug, Serialize)]
pub struct ConditionalEffect {
    #[serde(default)]
    pub conditions: Vec<Condition>,
    #[serde(flatten)]
    pub operation: Effect,
}

impl<'de> Deserialize<'de> for ConditionalEffect {
    fn deserialize<D: serde::Deserializer<'de>>(deserializer: D) -> Result<Self, D::Error> {
        use serde::de::Error;
        let value = Value::deserialize(deserializer)?;
        let object = value
            .as_object()
            .ok_or_else(|| D::Error::custom("effect must be an object"))?;
        let conditions = match object.get("conditions") {
            Some(value) => serde_json::from_value(value.clone()).map_err(D::Error::custom)?,
            None => vec![],
        };
        let operation: Effect = serde_json::from_value(value.clone()).map_err(D::Error::custom)?;
        if let Some(fields) = operation.field_names() {
            for key in object.keys() {
                if !["type", "conditions", "original_queue_id", "source"].contains(&key.as_str())
                    && !fields.contains(&key.as_str())
                {
                    return Err(D::Error::custom(format!("unknown effect field {key:?}")));
                }
            }
        }
        Ok(Self {
            conditions,
            operation,
        })
    }
}

impl From<Effect> for ConditionalEffect {
    fn from(operation: Effect) -> Self {
        Self {
            conditions: vec![],
            operation,
        }
    }
}

#[derive(Clone, Debug, Serialize, Deserialize)]
#[serde(tag = "type", rename_all = "snake_case")]
pub enum Effect {
    Message {
        text: String,
        #[serde(default)]
        dialogue_id: Option<u32>,
        #[serde(default)]
        duration_ms: u64,
    },
    Wait {
        ms: u64,
    },
    Sound {
        cue: String,
    },
    Cinematic {
        #[serde(flatten)]
        scene: Cinematic,
    },
    MoveTile {
        floor: Option<i32>,
        from_x: usize,
        from_y: usize,
        x: usize,
        y: usize,
        #[serde(default = "default_queue_ms")]
        duration_ms: u64,
    },
    NextCycle,
    Flag {
        flag: String,
        #[serde(default = "default_true")]
        value: bool,
    },
    SetTile {
        floor: Option<i32>,
        x: usize,
        y: usize,
        tile: u16,
    },
    AddStat {
        stat: Stat,
        amount: i64,
    },
    SetStat {
        stat: Stat,
        amount: i64,
    },
    MultiplyStat {
        stat: Stat,
        numerator: i64,
        denominator: i64,
    },
    GiveItem {
        item: String,
    },
    RemoveItem {
        item: String,
    },
    ClearInventory,
    SetCharges {
        item: String,
        charges: u32,
    },
    SetVisited {
        floors: Vec<i32>,
    },
    SetHighestStairFloor {
        floor: i32,
    },
    SetEnemy {
        enemy: String,
        hp: Option<i64>,
        attack: Option<i64>,
        defense: Option<i64>,
        gold: Option<i64>,
    },
    /// Scale the current shared HP/ATK/DEF row; gold is unchanged.
    MultiplyEnemy {
        enemy: String,
        numerator: i64,
        denominator: i64,
    },
    BattleAt {
        floor: Option<i32>,
        x: usize,
        y: usize,
        #[serde(default)]
        first_strike: bool,
    },
    Teleport {
        floor: Option<i32>,
        x: usize,
        y: usize,
        #[serde(default = "default_transition")]
        transition: String,
        duration_ms: Option<u64>,
    },
    Win,
}

impl Effect {
    /// Presentation payloads are extensible; state-changing operations have a
    /// closed schema. This catches a misspelled `conditions` or optional field
    /// instead of silently applying an unconditional effect/default value.
    fn field_names(&self) -> Option<&'static [&'static str]> {
        Some(match self {
            Self::Message { .. } => &["text", "dialogue_id", "duration_ms"],
            Self::Wait { .. } => &["ms"],
            Self::Sound { .. } => &["cue"],
            Self::Cinematic { .. } => return None,
            // `tile` is recovered provenance; the moving source tile wins.
            Self::MoveTile { .. } => {
                &["floor", "from_x", "from_y", "x", "y", "duration_ms", "tile"]
            }
            Self::NextCycle | Self::ClearInventory | Self::Win => &[],
            Self::Flag { .. } => &["flag", "value"],
            Self::SetTile { .. } => &["floor", "x", "y", "tile"],
            Self::AddStat { .. } | Self::SetStat { .. } => &["stat", "amount"],
            Self::MultiplyStat { .. } => &["stat", "numerator", "denominator"],
            Self::GiveItem { .. } | Self::RemoveItem { .. } => &["item"],
            Self::SetCharges { .. } => &["item", "charges"],
            Self::SetVisited { .. } => &["floors"],
            Self::SetHighestStairFloor { .. } => &["floor"],
            Self::SetEnemy { .. } => &["enemy", "hp", "attack", "defense", "gold"],
            Self::MultiplyEnemy { .. } => &["enemy", "numerator", "denominator"],
            Self::BattleAt { .. } => &["floor", "x", "y", "first_strike"],
            Self::Teleport { .. } => &["floor", "x", "y", "transition", "duration_ms"],
        })
    }
}

#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct Event {
    #[serde(default)]
    pub id: Option<String>,
    #[serde(default = "default_true")]
    pub once: bool,
    pub trigger: Trigger,
    #[serde(default)]
    pub conditions: Vec<Condition>,
    pub effects: Vec<ConditionalEffect>,
}

#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct Offer {
    pub id: Option<String>,
    #[serde(default = "default_offer_label")]
    pub label: String,
    #[serde(default)]
    pub cost: i64,
    #[serde(default)]
    pub cost_increment: i64,
    #[serde(default)]
    pub once: bool,
    #[serde(default)]
    pub conditions: Vec<Condition>,
    pub effects: Vec<ConditionalEffect>,
}
fn default_offer_label() -> String {
    "Purchase".into()
}

impl Offer {
    pub fn id_at(&self, index: usize) -> String {
        self.id.clone().unwrap_or_else(|| index.to_string())
    }
    pub fn cost_at(&self, visits: i64) -> i64 {
        self.cost
            .saturating_add(self.cost_increment.saturating_mul(visits))
    }
}

#[derive(Clone, Debug, Deserialize)]
struct InteractionScript {
    floor: i32,
    x: usize,
    y: usize,
    effects: Option<Vec<ConditionalEffect>>,
    offers: Option<Vec<Offer>>,
    #[serde(flatten)]
    view: crate::content::InteractionOverrides,
}

#[derive(Clone, Debug, Deserialize)]
pub(crate) struct CustomItem {
    #[serde(default)]
    pub effects: Vec<ConditionalEffect>,
    #[serde(default = "consumable_item")]
    pub consumable: bool,
}

fn consumable_item() -> bool {
    true
}

/// Derived, validated gameplay data. The original Campaign remains the wire
/// format so editor round trips and save fingerprints retain authored metadata.
#[derive(Clone, Debug, Default)]
pub(crate) struct CompiledScripts {
    pub events: Vec<Event>,
    tile_effects: BTreeMap<u16, Vec<ConditionalEffect>>,
    tile_offers: BTreeMap<u16, Vec<Offer>>,
    tile_behaviors: BTreeMap<u16, crate::content::TileBehavior>,
    interactions: Vec<InteractionScript>,
    pub items: BTreeMap<String, CustomItem>,
    pub floor_travel_callbacks: Vec<crate::flight::FloorTravelCallback>,
}

fn decode<T: serde::de::DeserializeOwned>(value: Value, path: &str) -> Result<T, String> {
    serde_json::from_value(value).map_err(|e| format!("{path}: {e}"))
}

impl CompiledScripts {
    pub fn compile(campaign: &Campaign) -> Result<Self, String> {
        let mut result = Self {
            floor_travel_callbacks: crate::flight::parse_callbacks(campaign)?,
            ..Self::default()
        };
        for (index, value) in campaign.events.iter().enumerate() {
            let path = format!("events[{index}]");
            let event: Event = decode(value.clone(), &path)?;
            event.validate(campaign, &path)?;
            result.events.push(event);
        }
        for (id, tile) in &campaign.tiles {
            let id_number = id.parse::<u16>().map_err(|e| format!("tiles.{id}: {e}"))?;
            let behavior = decode(
                serde_json::to_value(&tile.extra).expect("JSON metadata"),
                &format!("tiles.{id}"),
            )?;
            result.tile_behaviors.insert(id_number, behavior);
            let effects = parse_effects(campaign, &tile.effects, &format!("tiles.{id}.effects"))?;
            let offers = parse_offers(campaign, &tile.offers, &format!("tiles.{id}.offers"))?;
            result.tile_effects.insert(id_number, effects);
            result.tile_offers.insert(id_number, offers);
        }
        for (index, value) in campaign.interactions.iter().enumerate() {
            let path = format!("interactions[{index}]");
            let interaction: InteractionScript = decode(value.clone(), &path)?;
            validate_position(
                campaign,
                Some(interaction.floor),
                Some(interaction.x),
                Some(interaction.y),
                &path,
            )?;
            if let Some(effects) = &interaction.effects {
                validate_typed_effects(campaign, effects, &format!("{path}.effects"))?;
            }
            if let Some(offers) = &interaction.offers {
                for (index, offer) in offers.iter().enumerate() {
                    offer.validate(campaign, &format!("{path}.offers[{index}]"))?;
                }
            }
            result.interactions.push(interaction);
        }
        for (id, value) in &campaign.items {
            let path = format!("items.{id}");
            let item: CustomItem = decode(value.clone(), &path)?;
            validate_typed_effects(campaign, &item.effects, &format!("{path}.effects"))?;
            result.items.insert(id.clone(), item);
        }
        Ok(result)
    }

    pub fn tile_effects(&self, tile: u16) -> &[ConditionalEffect] {
        self.tile_effects
            .get(&tile)
            .map(Vec::as_slice)
            .unwrap_or(&[])
    }

    pub fn tile_behavior(&self, tile: u16) -> &crate::content::TileBehavior {
        &self.tile_behaviors[&tile]
    }

    pub fn interaction_view(
        &self,
        floor: i32,
        x: usize,
        y: usize,
        tile: u16,
        base: &crate::TileDef,
    ) -> crate::content::InteractionView {
        self.interactions
            .iter()
            .find(|entry| entry.floor == floor && entry.x == x && entry.y == y)
            .map(|entry| entry.view.clone())
            .unwrap_or_default()
            .resolve(base, self.tile_behavior(tile))
    }

    /// Location overrides replace only explicitly supplied fields, just as the
    /// authored interaction object replaces fields of the underlying tile.
    pub fn interaction_script(
        &self,
        floor: i32,
        x: usize,
        y: usize,
        tile: u16,
    ) -> (Vec<ConditionalEffect>, Vec<Offer>) {
        let local = self
            .interactions
            .iter()
            .find(|entry| entry.floor == floor && entry.x == x && entry.y == y);
        let effects = local
            .and_then(|entry| entry.effects.as_ref())
            .or_else(|| self.tile_effects.get(&tile))
            .cloned()
            .unwrap_or_default();
        let offers = local
            .and_then(|entry| entry.offers.as_ref())
            .or_else(|| self.tile_offers.get(&tile))
            .cloned()
            .unwrap_or_default();
        (effects, offers)
    }
}

pub(crate) fn validate_event(campaign: &Campaign, value: &Value, path: &str) -> Result<(), String> {
    decode::<Event>(value.clone(), path)?.validate(campaign, path)
}

pub(crate) fn validate_effects(
    campaign: &Campaign,
    values: &[Value],
    path: &str,
) -> Result<(), String> {
    parse_effects(campaign, values, path).map(|_| ())
}

pub(crate) fn validate_offer(campaign: &Campaign, value: &Value, path: &str) -> Result<(), String> {
    decode::<Offer>(value.clone(), path)?.validate(campaign, path)
}

fn parse_effects(
    campaign: &Campaign,
    values: &[Value],
    path: &str,
) -> Result<Vec<ConditionalEffect>, String> {
    let effects: Vec<ConditionalEffect> = values
        .iter()
        .enumerate()
        .map(|(index, value)| decode(value.clone(), &format!("{path}[{index}]")))
        .collect::<Result<_, _>>()?;
    validate_typed_effects(campaign, &effects, path)?;
    Ok(effects)
}

fn parse_offers(campaign: &Campaign, values: &[Value], path: &str) -> Result<Vec<Offer>, String> {
    values
        .iter()
        .enumerate()
        .map(|(index, value)| {
            let path = format!("{path}[{index}]");
            let offer: Offer = decode(value.clone(), &path)?;
            offer.validate(campaign, &path)?;
            Ok(offer)
        })
        .collect()
}

fn validate_position(
    campaign: &Campaign,
    floor: Option<i32>,
    x: Option<usize>,
    y: Option<usize>,
    path: &str,
) -> Result<(), String> {
    if floor.is_some_and(|floor| !campaign.floors.iter().any(|f| f.id == floor))
        || x.is_some_and(|x| x >= campaign.width)
        || y.is_some_and(|y| y >= campaign.height)
    {
        return Err(format!(
            "{path}: floor or coordinates are outside the campaign"
        ));
    }
    Ok(())
}
fn validate_tile(campaign: &Campaign, tile: u16, path: &str) -> Result<(), String> {
    if campaign.tiles.contains_key(&tile.to_string()) {
        Ok(())
    } else {
        Err(format!("{path}: references undefined tile {tile}"))
    }
}
fn validate_item(_campaign: &Campaign, item: &str, path: &str) -> Result<(), String> {
    // Inventory IDs may also be script-defined quest markers. Only active item
    // behaviors need a definition in Campaign::items; tags need a nonempty ID.
    validate_name(item, path)
}
fn validate_name(value: &str, path: &str) -> Result<(), String> {
    if value.trim().is_empty() {
        Err(format!("{path}: identifier must not be empty"))
    } else {
        Ok(())
    }
}
fn validate_amount(amount: i64, negative_allowed: bool, path: &str) -> Result<(), String> {
    let minimum = if negative_allowed { -MAX_STAT } else { 0 };
    if (minimum..=MAX_STAT).contains(&amount) {
        Ok(())
    } else {
        Err(format!(
            "{path}: amount must be between {minimum} and {MAX_STAT}"
        ))
    }
}

impl Event {
    fn validate(&self, campaign: &Campaign, path: &str) -> Result<(), String> {
        if let Some(id) = &self.id {
            validate_name(id, &format!("{path}.id"))?;
        }
        validate_position(
            campaign,
            self.trigger.floor,
            self.trigger.x,
            self.trigger.y,
            &format!("{path}.trigger"),
        )?;
        if let Some(tile) = self.trigger.tile {
            validate_tile(campaign, tile, &format!("{path}.trigger.tile"))?;
        }
        if let Some(positions) = &self.trigger.positions {
            if positions.is_empty() || self.trigger.x.is_some() || self.trigger.y.is_some() {
                return Err(format!(
                    "{path}.trigger.positions: provide nonempty positions instead of x/y"
                ));
            }
            for (index, position) in positions.iter().enumerate() {
                validate_position(
                    campaign,
                    self.trigger.floor,
                    Some(position.x),
                    Some(position.y),
                    &format!("{path}.trigger.positions[{index}]"),
                )?;
            }
        }
        validate_typed_conditions(campaign, &self.conditions, &format!("{path}.conditions"))?;
        validate_typed_effects(campaign, &self.effects, &format!("{path}.effects"))
    }
}

impl Offer {
    fn validate(&self, campaign: &Campaign, path: &str) -> Result<(), String> {
        if let Some(id) = &self.id {
            validate_name(id, &format!("{path}.id"))?;
        }
        validate_amount(self.cost, false, &format!("{path}.cost"))?;
        validate_amount(
            self.cost_increment,
            false,
            &format!("{path}.cost_increment"),
        )?;
        validate_typed_conditions(campaign, &self.conditions, &format!("{path}.conditions"))?;
        validate_typed_effects(campaign, &self.effects, &format!("{path}.effects"))
    }
}

fn validate_typed_conditions(
    campaign: &Campaign,
    conditions: &[Condition],
    path: &str,
) -> Result<(), String> {
    for (index, condition) in conditions.iter().enumerate() {
        let path = format!("{path}[{index}]");
        match condition {
            Condition::Flag { flag, .. } => validate_name(flag, &format!("{path}.flag"))?,
            Condition::HasItem { item } => validate_item(campaign, item, &format!("{path}.item"))?,
            Condition::Tile { floor, x, y, tile } => {
                validate_position(campaign, *floor, Some(*x), Some(*y), &path)?;
                validate_tile(campaign, *tile, &format!("{path}.tile"))?;
            }
            Condition::NoEnemies { floor } => {
                validate_position(campaign, *floor, None, None, &path)?
            }
            Condition::StatAtLeast { amount, .. } | Condition::StatAtMost { amount, .. } => {
                validate_amount(*amount, true, &format!("{path}.amount"))?
            }
            Condition::CycleAtLeast { cycle } | Condition::CycleAtMost { cycle } => {
                // Save format bounds cycles at 1000 to keep backside scaling finite.
                if !(1..=MAX_CYCLE).contains(cycle) {
                    return Err(format!("{path}.cycle: must be between 1 and {MAX_CYCLE}"));
                }
            }
            Condition::Any { conditions } => {
                validate_typed_conditions(campaign, conditions, &format!("{path}.conditions"))?
            }
        }
    }
    Ok(())
}

fn validate_cinematic(
    campaign: &Campaign,
    payload: &BTreeMap<String, Value>,
    path: &str,
) -> Result<(), String> {
    // The renderer can add custom fields/kinds, but misshapen known fields must
    // fail at import rather than silently fall back to the renderer's defaults.
    let field = |name: &str| format!("{path}.{name}");
    let duration = payload
        .get("duration_ms")
        .map(|v| decode::<u64>(v.clone(), &field("duration_ms")))
        .transpose()?;
    if duration.is_some_and(|ms| ms > MAX_WAIT_MS) {
        return Err(format!("{path}.duration_ms: exceeds {MAX_WAIT_MS}"));
    }
    let floor = payload
        .get("floor")
        .map(|v| decode::<i32>(v.clone(), &field("floor")))
        .transpose()?;
    let x = payload
        .get("x")
        .map(|v| decode::<usize>(v.clone(), &field("x")))
        .transpose()?;
    let y = payload
        .get("y")
        .map(|v| decode::<usize>(v.clone(), &field("y")))
        .transpose()?;
    validate_position(campaign, floor, x, y, path)?;
    for (name, maximum) in [("width", campaign.width), ("height", campaign.height)] {
        if let Some(value) = payload.get(name) {
            let size: usize = decode(value.clone(), &field(name))?;
            if size == 0 || size > maximum {
                return Err(format!("{}: must be between 1 and {maximum}", field(name)));
            }
        }
    }
    for name in [
        "scene",
        "asset",
        "target_asset",
        "background_asset",
        "text",
        "translation_key",
        "sound_cue",
        "style",
    ] {
        if let Some(value) = payload.get(name) {
            decode::<String>(value.clone(), &field(name))?;
        }
    }
    // Atlas cells are presentation resources, not simulation tile definitions.
    for name in ["tile", "color_tile", "from_tile", "underlying_tile"] {
        if let Some(value) = payload.get(name) {
            decode::<u16>(value.clone(), &field(name))?;
        }
    }
    for name in ["frames", "from_tiles", "original_frames"] {
        if let Some(value) = payload.get(name) {
            decode::<Vec<u16>>(value.clone(), &field(name))?;
        }
    }
    if let Some(value) = payload.get("targets") {
        let targets: Vec<crate::Position> = decode(value.clone(), &field("targets"))?;
        for (index, target) in targets.iter().enumerate() {
            validate_position(
                campaign,
                floor,
                Some(target.x),
                Some(target.y),
                &format!("{path}.targets[{index}]"),
            )?;
        }
    }
    if let Some(value) = payload.get("sound_offsets_ms") {
        let offsets: Vec<u64> = decode(value.clone(), &field("sound_offsets_ms"))?;
        if offsets
            .iter()
            .any(|offset| *offset > duration.unwrap_or(MAX_WAIT_MS))
        {
            return Err(format!(
                "{path}.sound_offsets_ms: cue occurs after the scene duration"
            ));
        }
    }
    Ok(())
}

fn validate_typed_effects(
    campaign: &Campaign,
    effects: &[ConditionalEffect],
    path: &str,
) -> Result<(), String> {
    for (index, effect) in effects.iter().enumerate() {
        let path = format!("{path}[{index}]");
        validate_typed_conditions(campaign, &effect.conditions, &format!("{path}.conditions"))?;
        match &effect.operation {
            Effect::SetTile { floor, x, y, tile } => {
                validate_position(campaign, *floor, Some(*x), Some(*y), &path)?;
                validate_tile(campaign, *tile, &format!("{path}.tile"))?;
            }
            Effect::MoveTile {
                floor,
                from_x,
                from_y,
                x,
                y,
                duration_ms,
            } => {
                validate_position(campaign, *floor, Some(*from_x), Some(*from_y), &path)?;
                validate_position(campaign, *floor, Some(*x), Some(*y), &path)?;
                if *duration_ms > MAX_WAIT_MS {
                    return Err(format!("{path}.duration_ms: exceeds {MAX_WAIT_MS}"));
                }
            }
            Effect::Teleport {
                floor,
                x,
                y,
                transition,
                duration_ms,
            } => {
                validate_position(campaign, *floor, Some(*x), Some(*y), &path)?;
                if !["original_spiral", "capture", "fade", "time_gate"]
                    .contains(&transition.as_str())
                {
                    return Err(format!(
                        "{path}.transition: unknown transition {transition:?}"
                    ));
                }
                if duration_ms.is_some_and(|value| value > MAX_WAIT_MS) {
                    return Err(format!("{path}.duration_ms: exceeds {MAX_WAIT_MS}"));
                }
            }
            Effect::BattleAt { floor, x, y, .. } => {
                validate_position(campaign, *floor, Some(*x), Some(*y), &path)?
            }
            Effect::Flag { flag, .. } => validate_name(flag, &format!("{path}.flag"))?,
            Effect::AddStat { amount, .. } => {
                validate_amount(*amount, true, &format!("{path}.amount"))?
            }
            Effect::SetStat { amount, .. } => {
                validate_amount(*amount, false, &format!("{path}.amount"))?
            }
            Effect::MultiplyStat {
                numerator,
                denominator,
                ..
            }
            | Effect::MultiplyEnemy {
                numerator,
                denominator,
                ..
            } => {
                if let Effect::MultiplyEnemy { enemy, .. } = &effect.operation
                    && !campaign.enemies.contains_key(enemy)
                {
                    return Err(format!(
                        "{path}.enemy: references undefined enemy {enemy:?}"
                    ));
                }
                validate_amount(*numerator, false, &format!("{path}.numerator"))?;
                if !(1..=MAX_STAT).contains(denominator) {
                    return Err(format!(
                        "{path}.denominator: must be between 1 and {MAX_STAT}"
                    ));
                }
            }
            Effect::GiveItem { item }
            | Effect::RemoveItem { item }
            | Effect::SetCharges { item, .. } => {
                validate_item(campaign, item, &format!("{path}.item"))?
            }
            Effect::SetVisited { floors } => {
                for floor in floors {
                    validate_position(
                        campaign,
                        Some(*floor),
                        None,
                        None,
                        &format!("{path}.floors"),
                    )?;
                }
            }
            Effect::SetHighestStairFloor { floor } => {
                validate_position(campaign, Some(*floor), None, None, &format!("{path}.floor"))?;
            }
            Effect::SetEnemy {
                enemy,
                hp,
                attack,
                defense,
                gold,
            } => {
                if !campaign.enemies.contains_key(enemy) {
                    return Err(format!(
                        "{path}.enemy: references undefined enemy {enemy:?}"
                    ));
                }
                if [hp, attack, defense, gold].iter().all(|v| v.is_none()) {
                    return Err(format!("{path}: set_enemy needs at least one statistic"));
                }
                if let Some(hp) = hp
                    && !(1..=MAX_STAT).contains(hp)
                {
                    return Err(format!("{path}.hp: must be between 1 and {MAX_STAT}"));
                }
                for (name, value) in [("attack", attack), ("defense", defense), ("gold", gold)] {
                    if let Some(value) = value {
                        validate_amount(*value, false, &format!("{path}.{name}"))?;
                    }
                }
            }
            Effect::Wait { ms } => {
                if *ms > MAX_WAIT_MS {
                    return Err(format!("{path}.ms: exceeds {MAX_WAIT_MS}"));
                }
            }
            Effect::Message { duration_ms, .. } => {
                if *duration_ms > MAX_WAIT_MS {
                    return Err(format!("{path}.duration_ms: exceeds {MAX_WAIT_MS}"));
                }
            }
            Effect::Sound { cue } => validate_name(cue, &format!("{path}.cue"))?,
            Effect::Cinematic { scene } => {
                validate_name(scene.kind.as_str(), &format!("{path}.kind"))?;
                let payload = serde_json::from_value(json!(scene)).expect("cinematic object");
                validate_cinematic(campaign, &payload, &path)?;
            }
            Effect::ClearInventory | Effect::NextCycle | Effect::Win => (),
        }
    }
    Ok(())
}

impl Engine {
    pub(crate) fn run_events(
        &mut self,
        kind: TriggerKind,
        floor: i32,
        x: usize,
        y: usize,
        tile: Option<u16>,
    ) {
        if self.state.status != GameStatus::Playing {
            return;
        }
        let cycle = self.state.cycle;
        // Effects mutate the world and may recursively trigger other scripts.
        // Clone matching event records to avoid keeping a campaign borrow alive.
        let events = self.scripts.events.clone();
        for (index, event) in events.iter().enumerate() {
            if !event.trigger.matches(kind, floor, x, y, tile) {
                continue;
            }
            let key = event.id.clone().unwrap_or_else(|| index.to_string());
            if event.once && self.state.event_counts.contains_key(&key) {
                continue;
            }
            if !self.conditions_pass(&event.conditions) {
                continue;
            }
            let count = self.state.event_counts.entry(key).or_default();
            *count = count.saturating_add(1);
            self.apply_effects(&event.effects);
            // Finish the current event's authored tail (including ending
            // presentation), then stop dispatching independent trigger records.
            if self.state.cycle != cycle || self.state.status != GameStatus::Playing {
                break;
            }
        }
    }

    pub(crate) fn conditions_pass(&self, conditions: &[Condition]) -> bool {
        conditions
            .iter()
            .all(|condition| self.condition_passes(condition))
    }

    fn condition_passes(&self, condition: &Condition) -> bool {
        let current_floor = self.state.player.floor;
        match condition {
            Condition::Flag { flag, value } => self.state.flags.contains(flag) == *value,
            Condition::HasItem { item } => self.state.player.inventory.contains(item),
            Condition::Tile { floor, x, y, tile } => {
                self.tile_at(floor.unwrap_or(current_floor), *x, *y) == Some(*tile)
            }
            Condition::NoEnemies { floor } => self
                .state
                .floors
                .get(&floor.unwrap_or(current_floor))
                .is_some_and(|tiles| {
                    !tiles
                        .iter()
                        .any(|id| self.campaign.tiles[&id.to_string()].enemy.is_some())
                }),
            Condition::StatAtLeast { stat, amount } => self.stat_value(*stat) >= *amount,
            Condition::StatAtMost { stat, amount } => self.stat_value(*stat) <= *amount,
            Condition::CycleAtLeast { cycle } => self.state.cycle >= *cycle,
            Condition::CycleAtMost { cycle } => self.state.cycle <= *cycle,
            Condition::Any { conditions } => conditions.iter().any(|c| self.condition_passes(c)),
        }
    }

    pub(crate) fn apply_effects(&mut self, effects: &[ConditionalEffect]) {
        for effect in effects {
            if self.state.status == GameStatus::Lost {
                break;
            }
            if !self.conditions_pass(&effect.conditions) {
                continue;
            }
            match &effect.operation {
                Effect::Message {
                    text,
                    dialogue_id,
                    duration_ms,
                } => {
                    self.log(text);
                    self.present(Presentation::Dialogue {
                        text: text.clone(),
                        dialogue_id: *dialogue_id,
                        duration_ms: *duration_ms,
                        log_id: self.latest_log_id(),
                        activity: text.clone(),
                    });
                }
                Effect::Wait { ms } => self.present(Presentation::Wait { duration_ms: *ms }),
                Effect::Sound { cue } => self.present(Presentation::Audio { name: cue.clone() }),
                Effect::Cinematic { scene } => {
                    let mut scene = scene.clone();
                    if scene.kind == CinematicKind::TileReveal
                        && let (Some(x), Some(y)) = (scene.x, scene.y)
                    {
                        let floor = scene.floor.unwrap_or(self.state.player.floor);
                        scene.floor = Some(floor);
                        // Gates created by an earlier trigger are absent in the
                        // initial map. Animate the current gate, never its old
                        // extraction-time road sprite.
                        scene.from_tile = self.tile_at(floor, x, y);
                    }
                    self.present(Presentation::Cinematic(scene));
                }
                Effect::MoveTile {
                    floor,
                    from_x,
                    from_y,
                    x,
                    y,
                    duration_ms,
                } => {
                    let floor = floor.unwrap_or(self.state.player.floor);
                    // One move presentation owns both writes. Emitting
                    // separate tile effects would reveal the destination
                    // before the movement animation has arrived there.
                    self.move_tile(floor, (*from_x, *from_y), (*x, *y), *duration_ms);
                }
                Effect::NextCycle => self.next_cycle(),
                Effect::Flag { flag, value } => {
                    if *value {
                        self.state.flags.insert(flag.clone());
                    } else {
                        self.state.flags.remove(flag);
                    }
                }
                Effect::SetTile { floor, x, y, tile } => {
                    self.set_tile(floor.unwrap_or(self.state.player.floor), *x, *y, *tile)
                }
                Effect::AddStat { stat, amount } => {
                    self.set_stat(*stat, self.stat_value(*stat).saturating_add(*amount))
                }
                Effect::SetStat { stat, amount } => self.set_stat(*stat, *amount),
                Effect::MultiplyStat {
                    stat,
                    numerator,
                    denominator,
                } => self.set_stat(
                    *stat,
                    self.stat_value(*stat).saturating_mul(*numerator) / *denominator,
                ),
                Effect::GiveItem { item } => self.give_item(item),
                Effect::RemoveItem { item } => self.state.player.remove_item(item),
                Effect::ClearInventory => self.state.player.clear_inventory(),
                Effect::SetCharges { item, charges } => {
                    self.state
                        .player
                        .item_charges
                        .insert(item.clone(), *charges);
                }
                Effect::SetVisited { floors } => {
                    self.state.visited_floors = floors.iter().copied().collect();
                    self.state.visited_floors.insert(self.state.player.floor);
                }
                Effect::SetHighestStairFloor { floor } => {
                    self.state.highest_stair_floor = Some(*floor);
                }
                Effect::SetEnemy {
                    enemy: key,
                    hp,
                    attack,
                    defense,
                    gold,
                } => {
                    let mut enemy = self
                        .state
                        .enemy_overrides
                        .get(key)
                        .or_else(|| self.campaign.enemies.get(key))
                        .expect("compiled set_enemy references a validated enemy")
                        .clone();
                    if let Some(value) = hp {
                        enemy.hp = *value;
                    }
                    if let Some(value) = attack {
                        enemy.attack = *value;
                    }
                    if let Some(value) = defense {
                        enemy.defense = *value;
                    }
                    if let Some(value) = gold {
                        enemy.gold = *value;
                    }
                    self.state.enemy_overrides.insert(key.clone(), enemy);
                }
                Effect::MultiplyEnemy {
                    enemy: key,
                    numerator,
                    denominator,
                } => {
                    // Work on the shared, unscaled row. Encounter resolution
                    // applies the cycle multiplier once, after this operation.
                    let mut enemy = self
                        .state
                        .enemy_overrides
                        .get(key)
                        .or_else(|| self.campaign.enemies.get(key))
                        .expect("compiled multiply_enemy references a validated enemy")
                        .clone();
                    let scale = |value: i64| {
                        (value.saturating_mul(*numerator) / *denominator).clamp(0, MAX_STAT)
                    };
                    enemy.hp = scale(enemy.hp).max(1);
                    enemy.attack = scale(enemy.attack);
                    enemy.defense = scale(enemy.defense);
                    self.state.enemy_overrides.insert(key.clone(), enemy);
                }
                Effect::BattleAt {
                    floor,
                    x,
                    y,
                    first_strike,
                } => self.forced_battle_at(*floor, *x, *y, *first_strike),
                Effect::Teleport {
                    floor,
                    x,
                    y,
                    transition,
                    duration_ms,
                } => {
                    let floor = floor.unwrap_or(self.state.player.floor);
                    let from = self.state.player.floor;
                    self.state.player.floor = floor;
                    self.state.player.x = *x;
                    self.state.player.y = *y;
                    self.present_floor(from, transition, *duration_ms);
                    self.state.visited_floors.insert(floor);
                }
                Effect::Win => {
                    self.state.status = GameStatus::Won;
                    self.log("You conquered the Tower of the Sorcerer.");
                }
            }
        }
    }

    fn forced_battle_at(&mut self, floor: Option<i32>, x: usize, y: usize, first_strike: bool) {
        let floor = floor.unwrap_or(self.state.player.floor);
        let id = self
            .tile_at(floor, x, y)
            .expect("compiled battle_at position is within a validated floor");
        let def = self.campaign.tiles[&id.to_string()].clone();
        // A script may legitimately target a previously cleared monster square.
        let Some(key) = def.enemy.as_ref() else {
            return;
        };
        let enemy = self
            .enemy_for_tile(key, id)
            .expect("validated enemy tile references a defined enemy");
        self.record_enemy_encounter(&enemy, floor, x, y, id);
        let result = forecast_with_rules(&self.state.player, &enemy, &self.rules);
        let battle_record = self.present_battle(&enemy, &result, floor, x, y, first_strike);
        let damage = result
            .damage
            .unwrap_or(self.state.player.hp)
            .saturating_add(if first_strike && self.rules.hero_attacks_first {
                (enemy.attack - self.state.player.defense).max(0)
            } else {
                0
            });
        if damage >= self.state.player.hp {
            self.state.player.hp = 0;
            self.state.status = GameStatus::Lost;
            self.log(format!("{} defeated you in the ambush.", enemy.name));
            self.record_battle_log(battle_record);
            return;
        }
        self.state.player.hp -= damage;
        // Lucky Gold doubles the reward in the original game, independently of
        // the backside monster-stat multiplier.
        let gold = result.gold;
        self.set_stat(Stat::Gold, self.state.player.gold.saturating_add(gold));
        self.clear(floor, x, y);
        if let Some(footprint) = self.scripts.tile_behavior(id).footprint.clone() {
            self.clear_large_monster(floor, &footprint, x, y);
        }
        self.log(format!(
            "Ambush: defeated {} (−{damage} HP, +{gold} gold).",
            enemy.name
        ));
        self.record_battle_log(battle_record);
        let cycle = self.state.cycle;
        self.run_events(TriggerKind::EnemyDefeated, floor, x, y, Some(id));
        if self.state.cycle == cycle {
            self.run_events(TriggerKind::PostCombat, floor, x, y, None);
        }
    }
}
