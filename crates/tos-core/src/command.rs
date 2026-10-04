//! Validated input shared by the CLI, browser, native UI and MCP adapter.
//!
//! JSON belongs at those adapters. The simulation dispatches an enum, so a typo
//! or missing argument cannot become a partially applied game action.
use serde::{Deserialize, Deserializer, Serialize, de};
use serde_json::{Value, json};
use std::{error::Error, fmt, str::FromStr};

#[derive(Clone, Copy, Debug, Deserialize, Serialize, PartialEq, Eq)]
#[serde(rename_all = "snake_case")]
pub enum Direction {
    Up,
    Down,
    Left,
    Right,
}

impl FromStr for Direction {
    type Err = &'static str;

    fn from_str(value: &str) -> Result<Self, Self::Err> {
        match value {
            "up" => Ok(Self::Up),
            "down" => Ok(Self::Down),
            "left" => Ok(Self::Left),
            "right" => Ok(Self::Right),
            _ => Err("Direction must be up, down, left or right"),
        }
    }
}

impl Direction {
    pub const fn as_str(self) -> &'static str {
        match self {
            Self::Up => "up",
            Self::Down => "down",
            Self::Left => "left",
            Self::Right => "right",
        }
    }

    pub const fn delta(self) -> (i32, i32) {
        match self {
            Self::Up => (0, -1),
            Self::Down => (0, 1),
            Self::Left => (-1, 0),
            Self::Right => (1, 0),
        }
    }
}

/// The wire format keeps the original `type` tag and command field names.
/// Unknown fields are rejected so misspelled arguments cannot silently vanish.
#[derive(Clone, Debug, Serialize, PartialEq, Eq)]
#[serde(tag = "type", rename_all = "snake_case")]
pub enum Command {
    Move {
        direction: Direction,
    },
    Choose {
        choice: String,
    },
    UseItem {
        item: String,
        #[serde(skip_serializing_if = "Option::is_none")]
        floor: Option<i32>,
    },
    Cancel,
    NewGame,
}

// Serde's internally tagged *unit* variants ignore extra fields, including when
// the enum has deny_unknown_fields. Empty struct variants enforce the closed
// wire schema without making Rust callers write `Command::Cancel {}`.
#[derive(Deserialize)]
#[serde(tag = "type", rename_all = "snake_case", deny_unknown_fields)]
enum WireCommand {
    Move {
        direction: Direction,
    },
    Choose {
        #[serde(deserialize_with = "nonempty_identifier")]
        choice: String,
    },
    UseItem {
        #[serde(deserialize_with = "nonempty_identifier")]
        item: String,
        #[serde(default)]
        floor: Option<i32>,
    },
    Cancel {},
    NewGame {},
}

impl<'de> Deserialize<'de> for Command {
    fn deserialize<D>(deserializer: D) -> Result<Self, D::Error>
    where
        D: Deserializer<'de>,
    {
        Ok(match WireCommand::deserialize(deserializer)? {
            WireCommand::Move { direction } => Self::Move { direction },
            WireCommand::Choose { choice } => Self::Choose { choice },
            WireCommand::UseItem { item, floor } => Self::UseItem { item, floor },
            WireCommand::Cancel {} => Self::Cancel,
            WireCommand::NewGame {} => Self::NewGame,
        })
    }
}

impl Command {
    pub fn from_json(source: &str) -> Result<Self, CommandError> {
        let command: Self = serde_json::from_str(source).map_err(CommandError::InvalidJson)?;
        command.validate()?;
        Ok(command)
    }

    pub fn from_value(value: Value) -> Result<Self, CommandError> {
        let command: Self = serde_json::from_value(value).map_err(CommandError::InvalidJson)?;
        command.validate()?;
        Ok(command)
    }

    /// Also check Rust callers, which can construct enum fields without serde.
    /// Item ownership, reachable floors and current conversations are gameplay
    /// decisions and remain in the engine after this input check.
    pub fn validate(&self) -> Result<(), CommandError> {
        match self {
            Self::Choose { choice } if choice.trim().is_empty() => {
                Err(CommandError::EmptyIdentifier("choice"))
            }
            Self::UseItem { item, .. } if item.trim().is_empty() => {
                Err(CommandError::EmptyIdentifier("item"))
            }
            Self::UseItem { item, floor: None }
                if matches!(item.as_str(), "orb_of_flying" | "floor_wand" | "flying_orb") =>
            {
                Err(CommandError::MissingDestinationFloor)
            }
            _ => Ok(()),
        }
    }

    pub const fn kind(&self) -> &'static str {
        match self {
            Self::Move { .. } => "move",
            Self::Choose { .. } => "choose",
            Self::UseItem { .. } => "use_item",
            Self::Cancel => "cancel",
            Self::NewGame => "new_game",
        }
    }

    /// MCP advertises this same boundary rather than a looser bag of fields.
    pub fn json_schema() -> Value {
        json!({"oneOf":[
            {"type":"object","properties":{"type":{"const":"move"},"direction":{"enum":["up","down","left","right"]}},"required":["type","direction"],"additionalProperties":false},
            {"type":"object","properties":{"type":{"const":"choose"},"choice":{"type":"string","minLength":1,"pattern":"\\S"}},"required":["type","choice"],"additionalProperties":false},
            {"type":"object","properties":{"type":{"const":"use_item"},"item":{"type":"string","minLength":1,"pattern":"\\S"},"floor":{"type":["integer","null"],"minimum":i32::MIN,"maximum":i32::MAX}},"required":["type","item"],"additionalProperties":false,
             "allOf":[{"if":{"properties":{"item":{"enum":["orb_of_flying","floor_wand","flying_orb"]}}},"then":{"required":["floor"],"properties":{"floor":{"type":"integer"}}}}]},
            {"type":"object","properties":{"type":{"const":"cancel"}},"required":["type"],"additionalProperties":false},
            {"type":"object","properties":{"type":{"const":"new_game"}},"required":["type"],"additionalProperties":false}
        ]})
    }
}

fn nonempty_identifier<'de, D>(deserializer: D) -> Result<String, D::Error>
where
    D: Deserializer<'de>,
{
    let identifier = String::deserialize(deserializer)?;
    if identifier.trim().is_empty() {
        return Err(de::Error::custom(
            "identifier must contain non-whitespace characters",
        ));
    }
    Ok(identifier)
}

/// Malformed input is separate from a valid action blocked by game rules.
/// A blocked action succeeds at this boundary and is reported in `last_action`.
#[derive(Debug)]
pub enum CommandError {
    InvalidJson(serde_json::Error),
    EmptyIdentifier(&'static str),
    MissingDestinationFloor,
    Execution(String),
}

impl fmt::Display for CommandError {
    fn fmt(&self, formatter: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            Self::InvalidJson(error) => write!(formatter, "Invalid command: {error}"),
            Self::EmptyIdentifier(field) => write!(formatter, "Command {field} must not be empty"),
            Self::MissingDestinationFloor => {
                formatter.write_str("Flying item command requires a destination floor")
            }
            Self::Execution(error) => formatter.write_str(error),
        }
    }
}

impl Error for CommandError {
    fn source(&self) -> Option<&(dyn Error + 'static)> {
        match self {
            Self::InvalidJson(error) => Some(error),
            _ => None,
        }
    }
}
