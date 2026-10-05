//! Regressions for presentation omitted by ordinary actions and event extraction.
use serde_json::{Value, json};
use tos_core::Engine;

fn room() -> Value {
    let mut campaign: Value =
        serde_json::from_str(include_str!("../../../data/campaign.json")).unwrap();
    campaign["id"] = json!("animation-room");
    campaign["width"] = json!(5);
    campaign["height"] = json!(5);
    campaign["floors"] = json!([{"id":1,"tiles":vec![6;25]}]);
    campaign["events"] = json!([]);
    campaign["interactions"] = json!([]);
    campaign["rules"] = json!({"empty_tile":6,"wall_break_tile_ranges":[[8,8]]});
    campaign["start"] = json!({"floor":1,"x":2,"y":2,"hp":10000,"attack":1000,"defense":1000,
        "keys":{"yellow":1,"blue":1,"red":1},"inventory":[]});
    campaign
}

fn game(campaign: &Value) -> Engine {
    Engine::from_json(&campaign.to_string()).unwrap()
}

fn command(game: &mut Engine, action: Value) -> Vec<Value> {
    game.command(action).unwrap();
    game.snapshot()["last_action"]["presentation"]
        .as_array()
        .unwrap()
        .clone()
}

fn edit(game: &mut Engine, change: impl FnOnce(&mut Value)) {
    let mut saved: Value = serde_json::from_str(&game.save_json()).unwrap();
    change(&mut saved);
    game.load_json(&saved.to_string()).unwrap();
}

#[test]
fn every_key_door_opens_before_the_hero_walks_and_blocked_doors_stay_closed() {
    for (tile, key) in [(1, "yellow"), (2, "blue"), (3, "red")] {
        let mut campaign = room();
        campaign["floors"][0]["tiles"][13] = json!(tile);
        campaign["rules"]["presentation"]["tile_transition_ms"] = json!(320);
        let mut engine = game(&campaign);
        let effects = command(&mut engine, json!({"type":"move","direction":"right"}));
        assert_eq!(effects[0]["kind"], "tile_reveal");
        assert_eq!(effects[0]["style"], "door_open");
        assert_eq!(effects[0]["from_tile"], tile);
        assert_eq!(effects[0]["tile"], 6);
        assert_eq!(effects[0]["duration_ms"], 320);
        assert_eq!(effects[0]["sound_cue"], "open");
        assert_eq!(effects[1]["type"], "tile");
        assert_eq!(effects[2]["type"], "move");
        assert_eq!(engine.tile_at(1, 3, 2), Some(6));
        assert_eq!(engine.player().x, 3);
        assert_eq!(engine.snapshot()["player"]["keys"][key], 0);
        campaign["start"]["keys"][key] = json!(0);
        let mut blocked = game(&campaign);
        assert!(command(&mut blocked, json!({"type":"move","direction":"right"})).is_empty());
        assert_eq!(blocked.tile_at(1, 3, 2), Some(tile));
        assert_eq!(blocked.player().x, 2);
    }
}

#[test]
fn secret_passage_and_both_pickaxes_collapse_each_target_before_its_clear() {
    let mut campaign = room();
    campaign["floors"][0]["tiles"][13] = json!(9);
    let mut engine = game(&campaign);
    let secret = command(&mut engine, json!({"type":"move","direction":"right"}));
    assert_eq!(secret[0]["style"], "wall_collapse");
    assert_eq!(secret[0]["from_tile"], 9);
    assert_eq!(secret[1]["type"], "tile");
    for item in ["mattock", "super_mattock"] {
        let mut campaign = room();
        campaign["start"]["inventory"] = json!([item]);
        for index in [7, 11, 13, 17, 0] {
            campaign["floors"][0]["tiles"][index] = json!(8);
        }
        campaign["floors"][0]["tiles"][1] = json!(10);
        let mut engine = game(&campaign);
        let effects = command(&mut engine, json!({"type":"use_item","item":item}));
        let expected = if item == "mattock" { 4 } else { 5 };
        assert_eq!(effects.len(), expected * 2);
        for pair in effects.as_chunks::<2>().0 {
            assert_eq!(pair[0]["style"], "wall_collapse");
            assert_eq!(pair[0]["from_tile"], 8);
            assert_eq!(pair[1]["type"], "tile");
            assert_eq!(pair[0]["x"], pair[1]["x"]);
            assert_eq!(pair[0]["y"], pair[1]["y"]);
        }
        assert_eq!(engine.tile_at(1, 1, 0), Some(10));
        assert!(!engine.player().inventory.iter().any(|owned| owned == item));
    }
}

#[test]
fn magic_key_uses_the_same_door_motion_without_spending_normal_keys() {
    let mut campaign = room();
    campaign["start"]["inventory"] = json!(["magic_key"]);
    for index in [0, 7, 13] {
        campaign["floors"][0]["tiles"][index] = json!(1);
    }
    campaign["floors"][0]["tiles"][1] = json!(2);
    let mut engine = game(&campaign);
    let effects = command(&mut engine, json!({"type":"use_item","item":"magic_key"}));
    assert_eq!(
        effects
            .iter()
            .filter(|fx| fx["style"] == "door_open")
            .count(),
        3
    );
    assert_eq!(engine.snapshot()["player"]["keys"]["yellow"], 1);
    assert_eq!(engine.tile_at(1, 1, 0), Some(2));
}

#[test]
fn bomb_dissolves_enemies_before_the_guard_gate_animation_and_rewards() {
    let mut campaign = room();
    campaign["start"]["inventory"] = json!(["bomb"]);
    campaign["floors"][0]["tiles"][13] = json!(61);
    campaign["floors"][0]["tiles"][0] = json!(4);
    campaign["events"] = json!([{"id":"guard","trigger":{"type":"enemy_defeated"},
        "effects":[{"type":"set_tile","floor":1,"x":0,"y":0,"tile":6}]}]);
    let mut engine = game(&campaign);
    let effects = command(&mut engine, json!({"type":"use_item","item":"bomb"}));
    assert_eq!(effects[0]["kind"], "magic");
    assert_eq!(effects[0]["underlying_tile"], 61);
    assert_eq!(effects[0]["color_tile"], 6);
    assert_eq!(effects[0]["frames"], json!([166, 170, 174, 178, 182]));
    assert_eq!(
        effects[0]["sound_offsets_ms"],
        json!([0, 150, 300, 450, 600])
    );
    assert_eq!(effects[1]["type"], "tile");
    assert_eq!(effects[2]["style"], "gate_open");
    assert_eq!(engine.tile_at(1, 0, 0), Some(6));
    assert_eq!(engine.player().gold, 1);
}

#[test]
fn magic_field_shows_the_damage_pose_after_walking_and_respects_the_shield() {
    let mut campaign = room();
    campaign["floors"][0]["tiles"][8] = json!(151); // Magician beside destination.
    for protected in [false, true] {
        campaign["start"]["inventory"] = if protected {
            json!(["sacred_shield"])
        } else {
            json!([])
        };
        let mut engine = game(&campaign);
        let effects = command(&mut engine, json!({"type":"move","direction":"right"}));
        assert_eq!(effects[0]["type"], "move");
        if protected {
            assert!(!effects.iter().any(|fx| fx["type"] == "damage"));
            assert_eq!(engine.player().hp, 10000);
        } else {
            assert_eq!(effects[1]["type"], "damage");
            assert_eq!(effects[1]["x"], 3);
            assert_eq!(effects[1]["hero_hp"], 10000);
            assert_eq!(effects[1]["enemy_hit"], 200);
            assert_eq!(engine.player().hp, 9800);
        }
    }
}

#[test]
fn recovered_guard_events_keep_each_original_gate_motion_exactly_once() {
    let campaign: Value =
        serde_json::from_str(include_str!("../../../data/campaign.json")).unwrap();
    for event in campaign["events"]
        .as_array()
        .unwrap()
        .iter()
        .filter(|event| {
            event["id"].as_str().unwrap_or("").contains("guards_")
                && event["effects"]
                    .as_array()
                    .unwrap()
                    .iter()
                    .any(|fx| fx["original_mode"].is_number())
                && event["conditions"]
                    .as_array()
                    .unwrap()
                    .iter()
                    .all(|condition| condition["type"] == "tile")
        })
    {
        let floor = event["trigger"]["floor"].as_i64().unwrap() as i32;
        let guard = event["conditions"]
            .as_array()
            .unwrap()
            .iter()
            .find(|condition| {
                let x = condition["x"].as_u64().unwrap() as usize;
                let y = condition["y"].as_u64().unwrap() as usize;
                let map = campaign["floors"]
                    .as_array()
                    .unwrap()
                    .iter()
                    .find(|map| map["id"] == floor)
                    .unwrap();
                let tile = map["tiles"][y * 11 + x].to_string();
                campaign["tiles"][tile]["kind"] == "enemy"
            })
            .unwrap();
        let (gx, gy) = (
            guard["x"].as_u64().unwrap() as usize,
            guard["y"].as_u64().unwrap() as usize,
        );
        let mut engine = game(&campaign);
        let original_guard = engine.tile_at(floor, gx, gy).unwrap();
        let (hx, direction) = if gx > 0 {
            (gx - 1, "right")
        } else {
            (gx + 1, "left")
        };
        edit(&mut engine, |saved| {
            for condition in event["conditions"].as_array().unwrap() {
                let cf = condition["floor"].as_i64().unwrap().to_string();
                let index = condition["y"].as_u64().unwrap() as usize * 11
                    + condition["x"].as_u64().unwrap() as usize;
                saved["floors"][cf][index] = condition["tile"].clone();
            }
            saved["floors"][floor.to_string()][gy * 11 + gx] = json!(original_guard);
            saved["floors"][floor.to_string()][gy * 11 + hx] = json!(6);
            saved["player"]["floor"] = json!(floor);
            saved["player"]["x"] = json!(hx);
            saved["player"]["y"] = json!(gy);
            saved["player"]["attack"] = json!(100000);
            saved["player"]["defense"] = json!(100000);
        });
        let effects = command(&mut engine, json!({"type":"move","direction":direction}));
        for scene in event["effects"]
            .as_array()
            .unwrap()
            .iter()
            .filter(|fx| fx["original_mode"].is_number())
        {
            let matches: Vec<_> = effects
                .iter()
                .filter(|fx| {
                    fx["kind"] == "tile_reveal" && fx["x"] == scene["x"] && fx["y"] == scene["y"]
                })
                .collect();
            assert_eq!(
                matches.len(),
                1,
                "{} at {},{}",
                event["id"],
                scene["x"],
                scene["y"]
            );
            assert_eq!(matches[0]["style"], scene["style"]);
            assert_eq!(
                matches[0]["original_frames"],
                json!((1..=16).collect::<Vec<_>>())
            );
        }
        assert!(
            effects
                .iter()
                .any(|fx| fx["type"] == "audio" && fx["name"] == "open")
        );
    }
}

#[test]
fn hidden_magician_reveal_keeps_its_predicate_cue_and_approach_position() {
    let campaign: Value =
        serde_json::from_str(include_str!("../../../data/campaign.json")).unwrap();
    let mut engine = game(&campaign);
    edit(&mut engine, |saved| {
        saved["player"]["floor"] = json!(41);
        saved["player"]["x"] = json!(8);
        saved["player"]["y"] = json!(1);
    });
    let blocked = command(&mut engine, json!({"type":"move","direction":"right"}));
    assert!(blocked.is_empty());
    assert_eq!(engine.tile_at(41, 9, 1), Some(10));
    edit(&mut engine, |saved| saved["floors"]["41"][12] = json!(6));
    let reveal = command(&mut engine, json!({"type":"move","direction":"right"}));
    assert_eq!(reveal[0], json!({"type":"audio","name":"get"}));
    assert_eq!(reveal[1]["type"], "tile");
    assert_eq!(engine.tile_at(41, 9, 1), Some(151));
    assert_eq!(engine.player().x, 8);
    assert!(reveal.iter().all(|effect| effect["type"] != "battle"));
}
