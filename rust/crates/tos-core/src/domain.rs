//! Closed vocabularies for simulation behavior.
//!
//! IDs, prose and presentation metadata remain authored strings. Behavior tags
//! are enums so a typo is rejected during import instead of becoming a no-op.

use serde::{Deserialize, Serialize};
use std::fmt;

/// Closed save/runtime states keep an invalid status out of a loaded session.
#[derive(Clone, Copy, Debug, Serialize, Deserialize, PartialEq, Eq)]
#[serde(rename_all = "snake_case")]
pub(crate) enum GameStatus {
    Playing,
    Won,
    Lost,
}

macro_rules! vocabulary {
    ($name:ident { $($variant:ident => $text:literal),+ $(,)? }) => {
        impl $name {
            pub const fn as_str(self) -> &'static str {
                match self { $(Self::$variant => $text),+ }
            }
        }

        impl fmt::Display for $name {
            fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
                f.write_str(self.as_str())
            }
        }

        // Editor/UI labels still compare to JSON's spelling. Runtime dispatch
        // uses exhaustive enum matches; these impls do not permit construction
        // from arbitrary strings.
        impl PartialEq<&str> for $name {
            fn eq(&self, other: &&str) -> bool { self.as_str() == *other }
        }

        impl PartialEq<str> for $name {
            fn eq(&self, other: &str) -> bool { self.as_str() == other }
        }
    };
}

#[derive(Clone, Copy, Debug, Default, Serialize, Deserialize, PartialEq, Eq)]
#[serde(rename_all = "snake_case")]
pub enum TileKind {
    #[default]
    Empty,
    Floor,
    Decoration,
    Wall,
    Solid,
    Lava,
    Barrier,
    HiddenWall,
    Door,
    SpecialDoor,
    Key,
    Enemy,
    Monster,
    Potion,
    Gem,
    Stat,
    Equipment,
    Gold,
    Item,
    StairsUp,
    StairsDown,
    Stairs,
    Npc,
    Shop,
    Altar,
    Merchant,
    Fairy,
    Win,
    Trigger,
}

vocabulary!(TileKind {
    Empty => "empty", Floor => "floor", Decoration => "decoration",
    Wall => "wall", Solid => "solid", Lava => "lava", Barrier => "barrier",
    HiddenWall => "hidden_wall", Door => "door", SpecialDoor => "special_door",
    Key => "key", Enemy => "enemy", Monster => "monster", Potion => "potion",
    Gem => "gem", Stat => "stat", Equipment => "equipment", Gold => "gold",
    Item => "item", StairsUp => "stairs_up", StairsDown => "stairs_down",
    Stairs => "stairs", Npc => "npc", Shop => "shop", Altar => "altar",
    Merchant => "merchant", Fairy => "fairy", Win => "win", Trigger => "trigger",
});

#[derive(Clone, Copy, Debug, Default, Serialize, Deserialize, PartialEq, Eq)]
#[serde(rename_all = "snake_case")]
pub enum EnemySpecial {
    /// Existing campaigns encode an ordinary monster as the empty string.
    #[default]
    #[serde(rename = "")]
    Normal,
    Undead,
    Dragon,
    MagicianA,
    MagicianB,
    Sorcerer,
    Boss,
}

vocabulary!(EnemySpecial {
    Normal => "", Undead => "undead", Dragon => "dragon",
    MagicianA => "magician_a", MagicianB => "magician_b",
    Sorcerer => "sorcerer", Boss => "boss",
});

#[derive(Clone, Copy, Debug, Serialize, Deserialize, PartialEq, Eq)]
#[serde(rename_all = "snake_case")]
pub enum Stat {
    Hp,
    Attack,
    Defense,
    Gold,
    Yellow,
    Blue,
    Red,
}

vocabulary!(Stat {
    Hp => "hp", Attack => "attack", Defense => "defense", Gold => "gold",
    Yellow => "yellow", Blue => "blue", Red => "red",
});

#[derive(Clone, Copy, Debug, Serialize, Deserialize, PartialEq, Eq)]
#[serde(rename_all = "snake_case")]
pub enum KeyColor {
    Yellow,
    Blue,
    Red,
}

vocabulary!(KeyColor { Yellow => "yellow", Blue => "blue", Red => "red" });

impl KeyColor {
    pub const fn stat(self) -> Stat {
        match self {
            Self::Yellow => Stat::Yellow,
            Self::Blue => Stat::Blue,
            Self::Red => Stat::Red,
        }
    }
}
