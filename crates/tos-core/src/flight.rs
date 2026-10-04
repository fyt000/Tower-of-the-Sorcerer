//! Authored floor-travel callbacks recovered from the original Flight controls.
//! A direct flight chooses a monotonic selector path and then confirms it.
use crate::{Campaign, Engine};
use serde::Deserialize;

#[derive(Clone, Copy, Debug, Eq, PartialEq)]
pub(crate) enum FloorTravel {
    Stairs,
    Flight,
}

#[derive(Clone, Debug, Deserialize)]
#[serde(deny_unknown_fields)]
pub(crate) struct FloorTravelCallback {
    when: TravelTrigger,
    tile_sum: Option<TileSum>,
    writes: Vec<TileWrite>,
}

#[derive(Clone, Debug, Deserialize)]
#[serde(tag = "type", rename_all = "snake_case", deny_unknown_fields)]
enum TravelTrigger {
    UpwardFlightPreview {
        floor: i32,
    },
    FlightConfirm {
        except_floor: Option<i32>,
        below_floor: Option<i32>,
        highest_stair_floor: Option<i32>,
    },
    StairsDown {
        from_floor: i32,
        to_floor: i32,
        highest_stair_floor: Option<i32>,
    },
}

#[derive(Clone, Debug, Deserialize)]
#[serde(deny_unknown_fields)]
struct Cell {
    floor: i32,
    x: usize,
    y: usize,
}

#[derive(Clone, Debug, Deserialize)]
#[serde(deny_unknown_fields)]
struct TileSum {
    cells: Vec<Cell>,
    equals: u32,
}

#[derive(Clone, Debug, Deserialize)]
#[serde(deny_unknown_fields)]
struct TileWrite {
    floor: i32,
    x: usize,
    y: usize,
    tile: u16,
    if_tile: Option<u16>,
}

pub(crate) fn parse_callbacks(campaign: &Campaign) -> Result<Vec<FloorTravelCallback>, String> {
    let Some(value) = campaign.rules.get("floor_travel_callbacks") else {
        return Ok(vec![]);
    };
    let callbacks: Vec<FloorTravelCallback> = serde_json::from_value(value.clone())
        .map_err(|error| format!("rules.floor_travel_callbacks: {error}"))?;
    let floor_exists = |floor: i32, path: &str| {
        if campaign.floors.iter().any(|entry| entry.id == floor) {
            Ok(())
        } else {
            Err(format!("{path}: references unknown floor {floor}"))
        }
    };
    let position_exists = |floor: i32, x: usize, y: usize, path: &str| {
        floor_exists(floor, path)?;
        if x < campaign.width && y < campaign.height {
            Ok(())
        } else {
            Err(format!("{path}: coordinates are outside the campaign"))
        }
    };
    for (index, callback) in callbacks.iter().enumerate() {
        let path = format!("rules.floor_travel_callbacks[{index}]");
        match callback.when {
            TravelTrigger::UpwardFlightPreview { floor } => floor_exists(floor, &path)?,
            TravelTrigger::FlightConfirm {
                except_floor,
                below_floor,
                highest_stair_floor,
            } => {
                for floor in [except_floor, below_floor, highest_stair_floor]
                    .into_iter()
                    .flatten()
                {
                    floor_exists(floor, &path)?;
                }
            }
            TravelTrigger::StairsDown {
                from_floor,
                to_floor,
                highest_stair_floor,
            } => {
                floor_exists(from_floor, &path)?;
                floor_exists(to_floor, &path)?;
                if from_floor <= to_floor {
                    return Err(format!("{path}: stairs_down must descend"));
                }
                if let Some(floor) = highest_stair_floor {
                    floor_exists(floor, &path)?;
                }
            }
        }
        if let Some(sum) = &callback.tile_sum {
            if sum.cells.is_empty() {
                return Err(format!("{path}.tile_sum.cells: must not be empty"));
            }
            for (index, cell) in sum.cells.iter().enumerate() {
                position_exists(
                    cell.floor,
                    cell.x,
                    cell.y,
                    &format!("{path}.tile_sum.cells[{index}]"),
                )?;
            }
        }
        for (index, write) in callback.writes.iter().enumerate() {
            let path = format!("{path}.writes[{index}]");
            position_exists(write.floor, write.x, write.y, &path)?;
            for tile in [Some(write.tile), write.if_tile].into_iter().flatten() {
                if !campaign.tiles.contains_key(&tile.to_string()) {
                    return Err(format!("{path}: references undefined tile {tile}"));
                }
            }
        }
    }
    Ok(callbacks)
}

pub(crate) fn validate_callbacks(campaign: &Campaign) -> Result<(), String> {
    parse_callbacks(campaign).map(|_| ())
}

impl Engine {
    pub(crate) fn apply_floor_travel_callbacks(&mut self, from: i32, to: i32, travel: FloorTravel) {
        if from == to
            || !self.campaign.rules["flying_original_selection"]
                .as_bool()
                .unwrap_or(false)
        {
            return;
        }
        let highest = self.highest_stair_floor();
        let callbacks = self.scripts.floor_travel_callbacks.clone();
        // Preview changes precede confirmation even when an author lists the
        // callback records in a different order. Only selectable floors occur
        // on the original monotonic Up path (not its skipped floor 44).
        for preview in [true, false] {
            for callback in &callbacks {
                let matches = match callback.when {
                    TravelTrigger::UpwardFlightPreview { floor } => {
                        preview
                            && travel == FloorTravel::Flight
                            && from < floor
                            && floor <= to
                            && self.flying_destinations().contains(&floor)
                    }
                    TravelTrigger::FlightConfirm {
                        except_floor,
                        below_floor,
                        highest_stair_floor,
                    } => {
                        !preview
                            && travel == FloorTravel::Flight
                            && except_floor != Some(to)
                            && below_floor.is_none_or(|floor| to < floor)
                            && highest_stair_floor.is_none_or(|floor| highest == floor)
                    }
                    TravelTrigger::StairsDown {
                        from_floor,
                        to_floor,
                        highest_stair_floor,
                    } => {
                        !preview
                            && travel == FloorTravel::Stairs
                            && from == from_floor
                            && to == to_floor
                            && highest_stair_floor.is_none_or(|floor| highest == floor)
                    }
                };
                if !matches {
                    continue;
                }
                if callback.tile_sum.as_ref().is_some_and(|sum| {
                    sum.cells
                        .iter()
                        .map(|cell| {
                            u64::from(
                                self.tile_at(cell.floor, cell.x, cell.y)
                                    .expect("validated callback cell"),
                            )
                        })
                        .sum::<u64>()
                        != u64::from(sum.equals)
                }) {
                    continue;
                }
                for write in &callback.writes {
                    if write.if_tile.is_none_or(|tile| {
                        self.tile_at(write.floor, write.x, write.y) == Some(tile)
                    }) {
                        self.set_tile(write.floor, write.x, write.y, write.tile);
                    }
                }
            }
        }
    }
}
