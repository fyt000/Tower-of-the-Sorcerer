//! Known tile and conversation behavior compiled from authored metadata.
//! Campaign JSON retains extensions verbatim; gameplay consumes these types.
use crate::{TileDef, TileKind};
use serde::Deserialize;

#[derive(Clone, Debug, Default, Deserialize)]
pub(crate) struct TileBehavior {
    #[serde(default)]
    pub scaled: bool,
    #[serde(default)]
    pub disappear: bool,
    pub direction: Option<StairDirection>,
    pub footprint: Option<Footprint>,
    pub after_text: Option<AfterText>,
    #[serde(default)]
    pub dialogue_ids: Vec<u32>,
}

#[derive(Clone, Copy, Debug, Deserialize, PartialEq, Eq)]
#[serde(rename_all = "snake_case")]
pub(crate) enum StairDirection {
    Up,
    Down,
}

#[derive(Clone, Debug, Deserialize)]
pub(crate) struct Footprint {
    pub width: usize,
    pub height: usize,
    #[serde(default)]
    pub offset_x: usize,
    #[serde(default)]
    pub offset_y: usize,
    pub tiles: Vec<u16>,
    #[serde(default)]
    pub clear_all: bool,
}

#[derive(Clone, Debug, Deserialize)]
pub(crate) struct AfterText {
    pub flag: String,
    pub text: String,
}

/// Location overrides replace only the fields the author supplied. Effects and
/// offers are compiled separately, and original artwork remains in Campaign.
#[derive(Clone, Debug, Default, Deserialize)]
pub(crate) struct InteractionOverrides {
    kind: Option<TileKind>,
    name: Option<String>,
    text: Option<String>,
    description: Option<String>,
    after_text: Option<AfterText>,
    dialogue_ids: Option<Vec<u32>>,
    disappear: Option<bool>,
}

#[derive(Clone, Debug)]
pub(crate) struct InteractionView {
    pub kind: TileKind,
    pub name: String,
    pub text: String,
    pub after_text: Option<AfterText>,
    pub dialogue_ids: Vec<u32>,
    pub disappear: bool,
}

impl InteractionOverrides {
    pub fn resolve(&self, base: &TileDef, behavior: &TileBehavior) -> InteractionView {
        let text = self.text.as_ref().unwrap_or(&base.text);
        InteractionView {
            kind: self.kind.unwrap_or(base.kind),
            name: self.name.as_ref().unwrap_or(&base.name).clone(),
            text: if text.is_empty() {
                self.description.as_ref().unwrap_or(&base.description)
            } else {
                text
            }
            .clone(),
            after_text: self
                .after_text
                .as_ref()
                .or(behavior.after_text.as_ref())
                .cloned(),
            dialogue_ids: self
                .dialogue_ids
                .as_ref()
                .unwrap_or(&behavior.dialogue_ids)
                .clone(),
            disappear: self.disappear.unwrap_or(behavior.disappear),
        }
    }
}
