//! Presentation scenarios against extracted executable evidence. These place
//! the hero at the trigger to test ordering, not an unassisted tower route.
use serde_json::{Value, json};
use tos_core::Engine;

fn original_at(floor: i32, x: usize, y: usize) -> Engine {
    let mut game = Engine::from_json(include_str!("../../../data/campaign.json")).unwrap();
    let mut save: Value = serde_json::from_str(&game.save_json()).unwrap();
    save["player"]["floor"] = json!(floor);
    save["player"]["x"] = json!(x);
    save["player"]["y"] = json!(y);
    game.load_json(&save.to_string()).unwrap();
    game
}

fn step(game: &mut Engine, direction: &str) -> Value {
    game.command(json!({"type":"move","direction":direction}))
        .unwrap();
    game.snapshot()
}

#[test]
fn capture_materializes_zeno_then_shows_title_before_the_prison_wakeup() {
    let mut game = original_at(3, 4, 9);
    let state = step(&mut game, "up");
    let timeline = state["last_action"]["presentation"].as_array().unwrap();
    let position = |kind: &str| timeline.iter().position(|e| e["kind"] == kind).unwrap();
    let summon = &timeline[position("magic")];
    assert_eq!(
        (summon["x"].as_u64(), summon["y"].as_u64()),
        (Some(4), Some(6))
    );
    assert_eq!(summon["color_tile"], 91);
    assert_eq!(summon["underlying_tile"], 6);
    assert_eq!(summon["frames"], json!((166..=182).collect::<Vec<_>>()));
    let speech = timeline.iter().position(|e| e["dialogue_id"] == 9).unwrap();
    let prison = timeline
        .iter()
        .position(|e| e["type"] == "floor" && e["to"] == 2)
        .unwrap();
    assert!(position("magic") < speech);
    assert!(speech < position("title"));
    assert!(position("title") < position("scan"));
    assert!(position("scan") < prison);
    assert_eq!(timeline[prison]["style"], "capture");
    assert_eq!(timeline[prison]["sound"], "none");
    assert_eq!(
        timeline[position("title")]["sound_offsets_ms"]
            .as_array()
            .unwrap()
            .len(),
        16
    );
    assert_eq!((game.player().floor, game.player().hp), (2, 400));
    assert_eq!(game.tile_at(3, 4, 6), Some(6));
    assert!(timeline[prison + 1..].iter().any(|e| e["dialogue_id"] == 3));
}

#[test]
fn skeleton_guard_march_keeps_all_forty_three_original_moves() {
    let mut game = original_at(10, 5, 5);
    let state = step(&mut game, "up");
    let timeline = state["last_action"]["presentation"].as_array().unwrap();
    let movements: Vec<_> = timeline
        .iter()
        .filter(|e| e["type"] == "move_tile")
        .collect();
    assert_eq!(movements.len(), 43);
    assert_eq!(movements[0]["tile"], 81); // Boss retreats to the top of the arena.
    assert_eq!(game.tile_at(10, 5, 0), Some(81));
    assert_eq!(game.tile_at(10, 5, 2), Some(4));
    assert_eq!(game.tile_at(10, 5, 6), Some(4));
}

#[test]
fn vampire_body_changes_after_the_original_transformation_span() {
    let mut game = original_at(20, 5, 8);
    let state = step(&mut game, "up");
    let timeline = state["last_action"]["presentation"].as_array().unwrap();
    let transform = timeline
        .iter()
        .position(|e| e["kind"] == "transformation")
        .unwrap();
    assert_eq!(
        timeline[transform]["original_frames"],
        json!((1..=32).collect::<Vec<_>>())
    );
    assert_eq!(
        timeline[transform]["from_tiles"].as_array().unwrap().len(),
        9
    );
    let body = timeline
        .iter()
        .position(|e| e["type"] == "tile" && e["x"] == 5 && e["y"] == 5 && e["tile"] == 95)
        .unwrap();
    assert!(transform < body);
    assert_eq!(game.tile_at(20, 5, 5), Some(95));
    assert_eq!(game.tile_at(20, 4, 4), Some(6));
}

#[test]
fn decoy_zeno_and_eight_sorcerers_retain_their_materialization_masks() {
    let mut game = original_at(49, 5, 4);
    let state = step(&mut game, "down");
    let timeline = state["last_action"]["presentation"].as_array().unwrap();
    let magic: Vec<_> = timeline.iter().filter(|e| e["kind"] == "magic").collect();
    assert_eq!(magic.len(), 2);
    assert_eq!(magic[0]["color_tile"], 91);
    assert_eq!(
        (magic[0]["x"].as_u64(), magic[0]["y"].as_u64()),
        (Some(5), Some(2))
    );
    assert_eq!(magic[1]["color_tile"], 93);
    assert_eq!(
        magic[1]["frames"],
        json!([167, 169, 171, 173, 175, 177, 179, 182])
    );
    assert_eq!(
        magic[1]["targets"],
        json!([
            {"x":4,"y":1}, {"x":5,"y":1}, {"x":6,"y":1}, {"x":6,"y":2},
            {"x":6,"y":3}, {"x":5,"y":3}, {"x":4,"y":3}, {"x":4,"y":2}
        ])
    );
    assert_eq!(game.tile_at(49, 5, 2), Some(91));
    for (x, y) in [
        (4, 1),
        (5, 1),
        (6, 1),
        (4, 2),
        (6, 2),
        (4, 3),
        (5, 3),
        (6, 3),
    ] {
        assert_eq!(game.tile_at(49, x, y), Some(93));
    }
}
