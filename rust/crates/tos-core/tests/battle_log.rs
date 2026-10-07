//! Historical battle facts remain tied to their activity after save and trim.
use serde_json::{Value, json};
use tos_core::Engine;

fn fixture() -> Value {
    json!({"id":"battle-log","title":"Battle record test","width":5,"height":1,
        "start":{"floor":1,"x":0,"y":0,"hp":100,"attack":10,"defense":5,"gold":7},
        "rules":{"empty_tile":6,"forecast_requires_item":"hero_orb"},
        "floors":[{"id":1,"tiles":[6,61,6,61,61]}],
        "tiles":{"6":{"name":"Road","kind":"floor"},
            "61":{"name":"Slime","kind":"enemy","enemy":"private_enemy_script_key"}},
        "enemies":{"private_enemy_script_key":{"name":"Slime","hp":20,"attack":8,"defense":1,"gold":2}},
        "events":[]})
}

fn engine(campaign: &Value) -> Engine {
    Engine::from_json(&campaign.to_string()).unwrap()
}

fn step(game: &mut Engine, direction: &str) {
    game.command(json!({"type":"move","direction":direction}))
        .unwrap();
}

fn only_record(game: &Engine) -> Value {
    let view = game.player_observation();
    let records = view["battle_log"].as_array().unwrap();
    assert_eq!(records.len(), 1);
    records[0].clone()
}

#[test]
fn resolved_battle_records_actual_stats_and_is_public_without_hero_orb() {
    let mut game = engine(&fixture());
    assert_eq!(game.player_observation()["battle_log"], json!([]));
    assert!(game.inspect(1, 0)["enemy"].is_null());
    assert_eq!(game.player_observation()["battle_log"], json!([]));
    step(&mut game, "right");
    let record = only_record(&game);
    assert_eq!(
        record,
        json!({"log_id":1,"cycle":1,"floor":1,"x":1,"y":0,
        "enemy_name":"Slime","enemy_hp":20,"enemy_attack":8,"enemy_defense":1,
        "hero_before":{"hp":100,"attack":10,"defense":5,"gold":7},
        "hero_after_hp":94,"damage":6,"reward":2,"hero_hit":9,"enemy_hit":3,
        "rounds":2,"hero_strikes":3,"enemy_strikes":2,"enemy_first":false,"outcome":"defeated"})
    );
    assert!(!record.to_string().contains("private_enemy_script_key"));
    assert!(record.get("inventory").is_none());
    assert!(!game.forecasts_unlocked());
    let snapshot = game.snapshot();
    let effect = snapshot["last_action"]["presentation"]
        .as_array()
        .unwrap()
        .iter()
        .find(|effect| effect["type"] == "battle")
        .unwrap();
    assert_eq!(effect["battle_log"], record);
    assert_eq!(effect["activity"], snapshot["log"][1]);
    assert_eq!(effect["enemy_attack"], 8);
    assert_eq!(effect["enemy_defense"], 1);
    assert_eq!(effect["gold"], 2);
}

#[test]
fn actual_damage_is_capped_at_remaining_hp_and_blocked_contact_has_no_battle_record() {
    let mut campaign = fixture();
    campaign["start"]["attack"] = json!(1);
    let mut blocked = engine(&campaign);
    step(&mut blocked, "right");
    assert_eq!(blocked.player_observation()["battle_log"], json!([]));
    assert_eq!(blocked.player().hp, 100);

    campaign["start"]["attack"] = json!(10);
    campaign["start"]["hp"] = json!(3);
    let mut fatal = engine(&campaign);
    step(&mut fatal, "right");
    let record = only_record(&fatal);
    assert_eq!(record["damage"], 3);
    assert_eq!(record["hero_after_hp"], 0);
    assert_eq!(record["reward"], 0);
    assert_eq!(record["outcome"], "lost");
    assert_eq!(record["hero_strikes"], 1);
    assert_eq!(record["enemy_strikes"], 1);
    assert_eq!(
        record["rounds"], 1,
        "fatal history records only executed turns"
    );
    let mut restored = engine(&campaign);
    restored.load_json(&fatal.save_json()).unwrap();
    assert_eq!(only_record(&restored), record);
}

#[test]
fn unnamed_custom_enemy_uses_its_visible_contact_name_in_portable_history() {
    let mut campaign = fixture();
    campaign["enemies"]["private_enemy_script_key"]["name"] = json!("");
    let mut game = engine(&campaign);
    step(&mut game, "right");
    let record = only_record(&game);
    assert_eq!(record["enemy_name"], "Slime");
    let mut restored = engine(&campaign);
    restored.load_json(&game.save_json()).unwrap();
    assert_eq!(only_record(&restored), record);
}

#[test]
fn encounter_changes_body_part_divisor_lucky_gold_and_stat_cap_are_recorded_as_played() {
    let mut campaign = fixture();
    campaign["tiles"]["61"]["reward_divisor"] = json!(2);
    campaign["start"]["inventory"] = json!(["lucky_gold"]);
    campaign["start"]["gold"] = json!(999_999_999);
    campaign["events"] = json!([{"trigger":{"type":"bump","floor":1,"x":1,"y":0},
        "effects":[{"type":"set_enemy","enemy":"private_enemy_script_key","hp":10,"attack":10,"defense":2,"gold":6}]}]);
    let mut game = engine(&campaign);
    step(&mut game, "right");
    let record = only_record(&game);
    assert_eq!(record["enemy_hp"], 10);
    assert_eq!(record["enemy_attack"], 10);
    assert_eq!(record["enemy_defense"], 2);
    assert_eq!(record["damage"], 5);
    assert_eq!(
        record["reward"], 1,
        "only the capped credited gold is an actual reward"
    );
    assert_eq!(game.player().gold, 1_000_000_000);
    let snapshot = game.snapshot();
    let effect = snapshot["last_action"]["presentation"]
        .as_array()
        .unwrap()
        .iter()
        .find(|effect| effect["type"] == "battle")
        .unwrap();
    assert_eq!(
        effect["gold"], 6,
        "body-part half reward is doubled by Lucky Gold"
    );
    assert_eq!(effect["reward"], 1);
}

#[test]
fn each_fight_in_a_scripted_sequence_keeps_its_own_result_and_animation_association() {
    let mut campaign = fixture();
    campaign["events"] = json!([{"trigger":{"type":"step","floor":1,"x":1,"y":0},
        "effects":[{"type":"battle_at","floor":1,"x":3,"y":0,"first_strike":true},
            {"type":"battle_at","floor":1,"x":4,"y":0,"first_strike":true}]}]);
    let mut game = engine(&campaign);
    step(&mut game, "right");
    let snapshot = game.snapshot();
    let records = snapshot["battle_log"].as_array().unwrap();
    assert_eq!(records.len(), 3);
    assert_eq!(records[0]["hero_before"]["hp"], 100);
    assert_eq!(records[1]["hero_before"]["hp"], 94);
    assert_eq!(records[2]["hero_before"]["hp"], 85);
    assert_eq!(game.player().hp, 76);
    assert_eq!(game.player().gold, 13);
    let effects: Vec<_> = snapshot["last_action"]["presentation"]
        .as_array()
        .unwrap()
        .iter()
        .filter(|effect| effect["type"] == "battle")
        .collect();
    assert_eq!(effects.len(), 3);
    for (index, (record, effect)) in records.iter().zip(effects).enumerate() {
        assert_eq!(record["log_id"], index + 1);
        assert_eq!(effect["battle_log"], *record);
        assert_eq!(effect["activity"], snapshot["log"][index + 1]);
        assert_eq!(record["damage"], if index == 0 { 6 } else { 9 });
        assert_eq!(record["enemy_strikes"], if index == 0 { 2 } else { 3 });
        assert_eq!(record["rounds"], record["enemy_strikes"]);
    }
    let mut restored = engine(&campaign);
    restored.load_json(&game.save_json()).unwrap();
    assert_eq!(restored.snapshot()["battle_log"], snapshot["battle_log"]);
}

#[test]
fn identical_dialogue_strings_have_distinct_ids_among_multiple_battle_effects() {
    let mut campaign = fixture();
    campaign["events"] = json!([{"trigger":{"type":"step","floor":1,"x":1,"y":0},
        "effects":[{"type":"message","text":"The same words."},
            {"type":"battle_at","floor":1,"x":3,"y":0,"first_strike":true},
            {"type":"message","text":"The same words."}]}]);
    let mut game = engine(&campaign);
    step(&mut game, "right");
    let snapshot = game.snapshot();
    let dialogues: Vec<_> = snapshot["last_action"]["presentation"]
        .as_array()
        .unwrap()
        .iter()
        .filter(|effect| effect["type"] == "dialogue")
        .collect();
    assert_eq!(dialogues.len(), 2);
    assert_eq!(dialogues[0]["log_id"], 2);
    assert_eq!(dialogues[1]["log_id"], 4);
    for dialogue in dialogues {
        assert_eq!(dialogue["activity"], "The same words.");
        let index = dialogue["log_id"].as_u64().unwrap() as usize;
        assert_eq!(dialogue["activity"], snapshot["log"][index]);
    }
    assert_eq!(snapshot["battle_log"][0]["log_id"], 1);
    assert_eq!(snapshot["battle_log"][1]["log_id"], 3);
}

#[test]
fn backside_transition_keeps_retained_history_from_the_previous_cycle() {
    let mut campaign = fixture();
    campaign["rules"]["backside"] = json!({"enabled":true,"multiplier":2});
    campaign["events"] = json!([{"trigger":{"type":"enemy_defeated","floor":1,"x":1,"y":0},
        "effects":[{"type":"next_cycle"}]}]);
    let mut game = engine(&campaign);
    step(&mut game, "right");
    let record = only_record(&game);
    assert_eq!(game.snapshot()["cycle"], 2);
    assert_eq!(record["cycle"], 1);
    assert_eq!(record["log_id"], 1);
    assert_eq!(record["enemy_hp"], 20);
    let mut restored = engine(&campaign);
    restored.load_json(&game.save_json()).unwrap();
    assert_eq!(only_record(&restored), record);
}

#[test]
fn stable_activity_ids_survive_trim_save_and_restore_without_stale_record_links() {
    let mut campaign = fixture();
    campaign["events"] = json!([{"once":false,"trigger":{"type":"step","floor":1,"x":0,"y":0},
        "effects":[{"type":"message","text":"Returned to the entrance."}]}]);
    let mut game = engine(&campaign);
    step(&mut game, "right");
    for _ in 0..99 {
        step(&mut game, "left");
        step(&mut game, "right");
    }
    let snapshot = game.snapshot();
    assert_eq!(snapshot["log_start"], 1);
    assert_eq!(snapshot["log"].as_array().unwrap().len(), 100);
    assert_eq!(only_record(&game)["log_id"], 1);
    assert!(
        snapshot["log"][0]
            .as_str()
            .unwrap()
            .starts_with("Defeated Slime")
    );
    let mut restored = engine(&campaign);
    restored.load_json(&game.save_json()).unwrap();
    assert_eq!(only_record(&restored), only_record(&game));
    step(&mut restored, "left");
    assert_eq!(restored.snapshot()["log_start"], 2);
    assert_eq!(restored.snapshot()["battle_log"], json!([]));
    for _ in 0..3 {
        step(&mut restored, "right");
    }
    assert_eq!(only_record(&restored)["log_id"], 102);
    assert_eq!(restored.snapshot()["log_start"], 3);
    assert_eq!(restored.snapshot()["log"].as_array().unwrap().len(), 100);
}

#[test]
fn old_saves_default_empty_and_invalid_historical_associations_are_rejected_atomically() {
    let campaign = fixture();
    let mut game = engine(&campaign);
    step(&mut game, "right");
    let save: Value = serde_json::from_str(&game.save_json()).unwrap();
    let mut legacy = save.clone();
    legacy.as_object_mut().unwrap().remove("log_start");
    legacy.as_object_mut().unwrap().remove("battle_log");
    let mut restored = engine(&campaign);
    restored.load_json(&legacy.to_string()).unwrap();
    assert_eq!(restored.snapshot()["log_start"], 0);
    assert_eq!(restored.snapshot()["battle_log"], json!([]));
    assert_eq!(restored.snapshot()["log"], save["log"]);
    for (key, invalid) in [
        ("log_id", json!(200)),
        ("damage", json!(1000)),
        ("reward", json!(-1)),
        ("floor", json!(500)),
        ("cycle", json!(2)),
    ] {
        let mut bad = save.clone();
        bad["battle_log"][0][key] = invalid;
        let before = restored.snapshot();
        assert!(restored.load_json(&bad.to_string()).is_err(), "{key}");
        assert_eq!(restored.snapshot(), before);
    }
    let mut duplicate = save.clone();
    duplicate["battle_log"]
        .as_array_mut()
        .unwrap()
        .push(save["battle_log"][0].clone());
    assert!(restored.load_json(&duplicate.to_string()).is_err());
    let mut overflow = save;
    overflow["log_start"] = json!(u64::MAX);
    assert!(restored.load_json(&overflow.to_string()).is_err());
}
