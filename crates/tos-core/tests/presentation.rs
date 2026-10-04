use serde_json::{Value, json};
use tos_core::Engine;

fn corridor() -> Engine {
    Engine::from_json(&json!({"id":"presentation","title":"Test","width":5,"height":1,
        "start":{"floor":1,"x":0,"y":0,"hp":100,"attack":10,"defense":5,"gold":7,"inventory":[],"keys":{"yellow":1,"blue":0,"red":0}},
        "rules":{"empty_tile":6,"forecast_requires_item":"hero_orb","backside":{"enabled":true,"multiplier":44}},
        "floors":[{"id":1,"tiles":[6,6,61,6,29]}],
        "tiles":{"6":{"name":"Road","kind":"floor"},"61":{"name":"Slime","kind":"enemy","enemy":"slime"},"29":{"name":"Key","kind":"key","amount":1}},
        "enemies":{"slime":{"name":"Slime","hp":20,"attack":8,"defense":1,"gold":2}},
        "events":[]}).to_string()).unwrap()
}
fn step(game: &mut Engine, direction: &str) {
    game.command(json!({"type":"move","direction":direction}))
        .unwrap();
}
fn edit(game: &mut Engine, change: impl FnOnce(&mut Value)) {
    let mut save: Value = serde_json::from_str(&game.save_json()).unwrap();
    change(&mut save);
    game.load_json(&save.to_string()).unwrap();
}

#[test]
fn click_route_stops_before_an_intermediate_enemy_but_can_target_it() {
    let mut game = corridor();
    assert_eq!(game.path_to(4, 0), vec!["right"]);
    assert_eq!(game.path_to(2, 0), vec!["right", "right"]);
    for direction in game.path_to(4, 0) {
        step(&mut game, &direction);
    }
    assert_eq!(game.player().x, 1);
    assert_eq!(game.player().hp, 100);
    assert_eq!(game.tile_at(1, 2, 0), Some(61));
}

#[test]
fn hero_orb_gate_applies_to_both_inspection_and_snapshot() {
    let mut game = corridor();
    assert_eq!(game.inspect(2, 0)["details_locked"], true);
    assert!(game.inspect(2, 0)["enemy"].is_null());
    assert_eq!(game.snapshot()["enemies"], json!([]));
    edit(&mut game, |save| {
        save["player"]["inventory"] = json!(["wisdom_orb"])
    });
    assert!(game.inspect(2, 0)["enemy"].is_null());
    edit(&mut game, |save| {
        save["player"]["inventory"] = json!(["hero_orb"])
    });
    assert_eq!(game.inspect(2, 0)["enemy"]["damage"], 6);
    assert_eq!(game.snapshot()["enemies"].as_array().unwrap().len(), 1);
}

#[test]
fn combat_timeline_describes_the_same_calculation_as_headless_state() {
    let mut game = corridor();
    step(&mut game, "right");
    step(&mut game, "right");
    let snapshot = game.snapshot();
    let timeline = snapshot["last_action"]["presentation"].as_array().unwrap();
    let battle = timeline.iter().find(|e| e["type"] == "battle").unwrap();
    assert_eq!(battle["hero_hp"], 100);
    assert_eq!(battle["enemy_hp"], 20);
    assert_eq!(battle["hero_hit"], 9);
    assert_eq!(battle["enemy_hit"], 3);
    assert_eq!(battle["rounds"], 2);
    assert_eq!(battle["hero_strikes"], 3);
    assert_eq!(battle["enemy_strikes"], 2);
    assert_eq!(game.player().hp, 94);
    assert_eq!(game.player().gold, 9);
    assert!(
        timeline
            .iter()
            .any(|e| e["type"] == "audio" && e["name"] == "taisen")
    );
    let saved = game.save_json();
    let mut restored = corridor();
    restored.load_json(&saved).unwrap();
    assert_eq!(restored.player().hp, 94);
}

#[test]
fn fatal_and_enemy_first_animation_turns_end_at_the_actual_lethal_strike() {
    let mut game = corridor();
    edit(&mut game, |s| {
        s["player"]["hp"] = json!(3);
        s["player"]["x"] = json!(1);
    });
    step(&mut game, "right");
    let state = game.snapshot();
    let battle = state["last_action"]["presentation"]
        .as_array()
        .unwrap()
        .iter()
        .find(|e| e["type"] == "battle")
        .unwrap();
    assert_eq!(battle["hero_strikes"], 1);
    assert_eq!(battle["enemy_strikes"], 1);
    assert_eq!(state["status"], "lost");
    let mut campaign = serde_json::to_value(corridor().campaign).unwrap();
    campaign["events"] = json!([{"id":"ambush","trigger":{"type":"step","floor":1,"x":1,"y":0},"effects":[{"type":"battle_at","floor":1,"x":2,"y":0,"first_strike":true}]}]);
    let mut game = Engine::from_json(&campaign.to_string()).unwrap();
    step(&mut game, "right");
    let state = game.snapshot();
    let battle = state["last_action"]["presentation"]
        .as_array()
        .unwrap()
        .iter()
        .find(|e| e["type"] == "battle")
        .unwrap();
    assert_eq!(battle["enemy_first"], true);
    assert_eq!(battle["hero_strikes"], 3);
    assert_eq!(battle["enemy_strikes"], 3);
    assert_eq!(game.player().hp, 91);
}

#[test]
fn backside_scales_monster_statistics_but_preserves_gold_reward() {
    let mut game = corridor();
    edit(&mut game, |save| {
        save["cycle"] = json!(2);
        save["player"]["inventory"] = json!(["hero_orb"]);
    });
    let enemy = game.inspect(2, 0)["enemy"].clone();
    assert_eq!(enemy["hp"], 880);
    assert_eq!(enemy["attack"], 352);
    assert_eq!(enemy["defense"], 44);
    assert_eq!(enemy["gold"], 2);
    let saved = game.save_json();
    let mut restored = corridor();
    restored.load_json(&saved).unwrap();
    assert_eq!(restored.snapshot()["cycle"], 2);
}

#[test]
fn presentation_effects_are_ordered_but_do_not_delay_the_simulation() {
    let mut definition: Value = serde_json::to_value(corridor().campaign).unwrap();
    definition["events"] = json!([{"id":"scene","trigger":{"type":"step","floor":1,"x":1,"y":0},"effects":[
        {"type":"sound","cue":"3f"},{"type":"wait","ms":200},{"type":"message","text":"A trap!","dialogue_id":9},{"type":"set_tile","floor":1,"x":4,"y":0,"tile":6}]}]);
    let mut game = Engine::from_json(&definition.to_string()).unwrap();
    step(&mut game, "right");
    assert_eq!(game.tile_at(1, 4, 0), Some(6));
    let snapshot = game.snapshot();
    let types: Vec<_> = snapshot["last_action"]["presentation"]
        .as_array()
        .unwrap()
        .iter()
        .map(|e| e["type"].as_str().unwrap())
        .collect();
    assert_eq!(types, vec!["move", "audio", "wait", "dialogue", "tile"]);
}
