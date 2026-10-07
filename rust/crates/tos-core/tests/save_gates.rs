//! Player save points obey original item gates; private persistence remains safe.
use serde_json::{Value, json};
use tos_core::Engine;

#[test]
fn original_hero_orb_unlocks_saving_without_gating_worker_replacement() {
    let mut game = Engine::from_json(include_str!("../../../../data/campaign.json")).unwrap();
    assert!(!game.save_unlocked());
    assert!(game.ensure_player_save_allowed().is_err());
    let before = game.snapshot();
    let checkpoint = game.runtime_checkpoint_json();
    game.command(json!({"type":"move","direction":"up"}))
        .unwrap();
    game.restore_runtime_checkpoint_json(&checkpoint).unwrap();
    assert_eq!(
        game.snapshot(),
        before,
        "hot reload must preserve a session before the save item is acquired"
    );

    let mut setup: Value = serde_json::from_str(&game.save_json()).unwrap();
    setup["player"]["floor"] = json!(3);
    setup["player"]["x"] = json!(9);
    setup["player"]["y"] = json!(3);
    game.load_json(&setup.to_string()).unwrap();
    game.command(json!({"type":"move","direction":"right"}))
        .unwrap();
    game.command(json!({"type":"choose","choice":"accept"}))
        .unwrap();
    assert!(game.save_unlocked());
    game.ensure_player_save_allowed().unwrap();
    let saved = game.save_json();
    let mut restored = Engine::from_json(include_str!("../../../../data/campaign.json")).unwrap();
    restored.load_json(&saved).unwrap();
    assert!(restored.save_unlocked());
    game.command(json!({"type":"new_game"})).unwrap();
    assert!(!game.save_unlocked());
}

#[test]
fn custom_campaigns_can_enable_the_original_gate_or_leave_saves_unrestricted() {
    let mut source = json!({
        "id":"save-fixture","title":"Save fixture","width":1,"height":1,
        "start":{"floor":1,"x":0,"y":0,"hp":100,"attack":10,"defense":10},
        "rules":{"empty_tile":0},"floors":[{"id":1,"tiles":[0]}],
        "tiles":{"0":{"name":"Road","kind":"floor"}},"enemies":{},
        "items":{"strip":{"consumable":true,"effects":[{"type":"remove_item","item":"hero_orb"}]}},
        "events":[]
    });
    assert!(
        Engine::from_json(&source.to_string())
            .unwrap()
            .save_unlocked()
    );
    source["rules"]["save_requires_hero_orb"] = json!(true);
    assert!(
        !Engine::from_json(&source.to_string())
            .unwrap()
            .save_unlocked()
    );
    source["start"]["inventory"] = json!(["hero_orb", "strip"]);
    let mut game = Engine::from_json(&source.to_string()).unwrap();
    assert!(game.save_unlocked());
    game.command(json!({"type":"use_item","item":"strip"}))
        .unwrap();
    assert!(!game.save_unlocked(), "item theft removes the save ability");
    source["rules"]["save_requires_hero_orb"] = json!(false);
    source["start"]["inventory"] = json!([]);
    Engine::from_json(&source.to_string())
        .unwrap()
        .ensure_player_save_allowed()
        .unwrap();
}
