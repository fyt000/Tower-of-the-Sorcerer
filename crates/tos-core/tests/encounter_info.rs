//! Original enemy contact reveals raw stats before Hero unlocks forecasts.
use serde_json::{Value, json};
use tos_core::Engine;

fn fixture(hp: i64, attack: i64) -> Engine {
    Engine::from_json(&json!({
        "id":"contact-info","title":"Contact info","width":4,"height":2,
        "start":{"floor":1,"x":0,"y":0,"hp":hp,"attack":attack,"defense":3},
        "rules":{"empty_tile":0,"forecast_requires_item":"hero_orb","backside":{"enabled":true}},
        "floors":[{"id":1,"tiles":[0,1,0,2,0,0,0,0]}],
        "tiles":{"0":{"name":"Road","kind":"floor"},
            "1":{"name":"Guard","kind":"enemy","enemy":"guard"},
            "2":{"name":"Slime","kind":"enemy","enemy":"slime"}},
        "enemies":{"guard":{"name":"Guard","hp":35,"attack":5,"defense":10,"gold":9},
            "slime":{"name":"Slime","hp":20,"attack":4,"defense":1,"gold":3}},
        "events":[]
    }).to_string()).unwrap()
}

fn step(game: &mut Engine, direction: &str) {
    game.command(json!({"type":"move","direction":direction}))
        .unwrap();
}

#[test]
fn blocked_contact_reveals_only_three_raw_stats_and_never_unlocks_other_enemies() {
    let mut game = fixture(100, 10);
    assert!(game.player_observation()["last_encounter"].is_null());
    assert!(game.inspect_player_tile(1, 0)["encountered_enemy"].is_null());
    step(&mut game, "right");
    let view = game.player_observation();
    assert_eq!(view["last_action"]["ok"], false);
    assert_eq!(
        view["last_encounter"],
        json!({"cycle":1,"floor":1,"x":1,"y":0,"tile":1,
        "enemy_name":"Guard","hp":35,"attack":5,"defense":10})
    );
    assert_eq!(game.player().x, 0);
    assert_eq!(view["enemies"], json!([]));
    assert_eq!(view["forecasts_unlocked"], false);
    assert_eq!(
        game.inspect_player_tile(1, 0)["encountered_enemy"],
        view["last_encounter"]
    );
    assert!(game.inspect_player_tile(1, 0)["enemy"].is_null());
    assert!(game.inspect_player_tile(3, 0)["encountered_enemy"].is_null());
    for hidden in ["gold", "damage", "rounds", "can_win", "special"] {
        assert!(
            view["last_encounter"].get(hidden).is_none(),
            "leaked {hidden}"
        );
    }
}

#[test]
fn last_contact_persists_after_walking_save_and_worker_reload_and_is_replaced_on_contact() {
    let mut game = fixture(100, 10);
    step(&mut game, "right");
    let first = game.player_observation()["last_encounter"].clone();
    step(&mut game, "down");
    assert_eq!(game.player_observation()["last_encounter"], first);
    let mut restored = fixture(100, 10);
    restored.load_json(&game.save_json()).unwrap();
    assert_eq!(restored.player_observation()["last_encounter"], first);
    restored
        .restore_runtime_checkpoint_json(&game.runtime_checkpoint_json())
        .unwrap();
    assert_eq!(restored.player_observation(), game.player_observation());
    for _ in 0..3 {
        step(&mut restored, "right");
    }
    step(&mut restored, "up");
    assert_eq!(
        restored.player_observation()["last_encounter"]["enemy_name"],
        "Slime"
    );
    assert_eq!(restored.snapshot()["tiles"][3], 0);
    assert!(
        restored
            .inspect_player_tile(3, 0)
            .get("encountered_enemy")
            .is_none()
    );
    restored.command(json!({"type":"new_game"})).unwrap();
    assert!(restored.player_observation()["last_encounter"].is_null());
}

#[test]
fn fatal_contact_and_bump_stat_changes_use_actual_encounter_stats() {
    let mut game = fixture(2, 11);
    step(&mut game, "right");
    assert_eq!(game.player_observation()["status"], "lost");
    assert_eq!((game.player().x, game.player().y), (1, 0));
    assert_eq!(game.player_observation()["last_encounter"]["hp"], 35);

    let mut campaign = serde_json::to_value(fixture(100, 10).campaign()).unwrap();
    campaign["events"] = json!([{"id":"transformation","trigger":{"type":"bump","floor":1,"x":1,"y":0},
        "effects":[{"type":"set_enemy","enemy":"guard","hp":88,"attack":12,"defense":15}]}]);
    let mut transformed = Engine::from_json(&campaign.to_string()).unwrap();
    step(&mut transformed, "right");
    assert_eq!(transformed.player_observation()["last_encounter"]["hp"], 88);
    assert_eq!(
        transformed.player_observation()["last_encounter"]["attack"],
        12
    );
    assert_eq!(
        transformed.player_observation()["last_encounter"]["defense"],
        15
    );
}

#[test]
fn unnamed_custom_enemies_still_create_portable_contact_records() {
    let mut campaign = serde_json::to_value(fixture(100, 10).campaign()).unwrap();
    campaign["enemies"]["guard"]["name"] = json!("");
    for (tile_name, expected) in [("Guard", "Guard"), ("", "Enemy")] {
        campaign["tiles"]["1"]["name"] = json!(tile_name);
        let mut game = Engine::from_json(&campaign.to_string()).unwrap();
        step(&mut game, "right");
        assert_eq!(
            game.player_observation()["last_encounter"]["enemy_name"],
            expected
        );
        let save = game.save_json();
        game.load_json(&save).unwrap();
        assert_eq!(game.save_json(), save);
    }
}

#[test]
fn scripted_battles_reveal_contact_stats_and_legacy_saves_have_no_invented_encounter() {
    let mut campaign = serde_json::to_value(fixture(100, 20).campaign()).unwrap();
    campaign["events"] = json!([{"id":"ambush","trigger":{"type":"step","floor":1,"x":0,"y":1},
        "effects":[{"type":"battle_at","floor":1,"x":1,"y":0,"first_strike":true}]}]);
    let mut game = Engine::from_json(&campaign.to_string()).unwrap();
    step(&mut game, "down");
    assert_eq!(
        game.player_observation()["last_encounter"]["enemy_name"],
        "Guard"
    );
    let before = game.save_json();
    let mut save: Value = serde_json::from_str(&before).unwrap();
    save["last_encounter"]["x"] = json!(99);
    assert!(
        game.load_json(&save.to_string())
            .unwrap_err()
            .contains("last encounter")
    );
    assert_eq!(game.save_json(), before);
    save.as_object_mut().unwrap().remove("last_encounter");
    game.load_json(&save.to_string()).unwrap();
    assert!(game.player_observation()["last_encounter"].is_null());
}
