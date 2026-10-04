//! Current weapon/shield presentation is separate from accumulated pickup stats.
use serde_json::{Value, json};
use tos_core::Engine;

fn fixture() -> Engine {
    Engine::from_json(&json!({
        "id":"equipment-slots","title":"Equipment slots","width":4,"height":3,
        "start":{"floor":1,"x":0,"y":1,"hp":1000,"attack":100,"defense":100,
            "inventory":["sword_5","sacred_shield","strip","clearer"]},
        "rules":{"empty_tile":0,"backside":{"enabled":true}},
        "floors":[{"id":1,"tiles":[0,0,0,0,0,51,56,61,0,0,0,0]}],
        "tiles":{
            "0":{"name":"Road","kind":"floor"},
            "51":{"name":"Iron Sword","kind":"equipment","item":"sword_1","stat":"attack","amount":10},
            "55":{"name":"Sacred Sword","kind":"equipment","item":"sword_5","stat":"attack","amount":100},
            "56":{"name":"Iron Shield","kind":"equipment","item":"shield_1","stat":"defense","amount":10},
            "60":{"name":"Sacred Shield","kind":"equipment","item":"sacred_shield","stat":"defense","amount":100},
            "61":{"name":"Magician","kind":"enemy","enemy":"mage"}
        },
        "enemies":{"mage":{"name":"Magician","hp":100,"attack":100,"defense":50,"gold":1,"special":"magician_a"}},
        "items":{
            "strip":{"consumable":true,"effects":[{"type":"remove_item","item":"sword_1"},{"type":"remove_item","item":"shield_1"}]},
            "clearer":{"consumable":true,"effects":[{"type":"clear_inventory"}]}
        },
        "events":[{"id":"cycle","trigger":{"type":"step","floor":1,"x":3,"y":2},"effects":[{"type":"next_cycle"}]}]
    }).to_string()).unwrap()
}

fn step(game: &mut Engine, direction: &str) {
    game.command(json!({"type":"move","direction":direction}))
        .unwrap();
}

#[test]
fn initial_slots_show_authored_gear_without_reapplying_bonuses() {
    let game = fixture();
    assert_eq!(game.player().weapon.as_deref(), Some("sword_5"));
    assert_eq!(game.player().shield.as_deref(), Some("sacred_shield"));
    assert_eq!((game.player().attack, game.player().defense), (100, 100));
    assert_eq!(
        game.snapshot()["equipment"]["weapon"]["name"],
        "Sacred Sword"
    );
    assert_eq!(
        game.snapshot()["equipment"]["shield"]["id"],
        "sacred_shield"
    );
    assert!(
        game.snapshot()["inventory_items"]
            .as_array()
            .unwrap()
            .iter()
            .all(|item| { item["id"] != "sword_5" && item["id"] != "sacred_shield" })
    );
}

#[test]
fn custom_equipment_without_a_weapon_or_shield_slot_remains_visible_inventory() {
    let mut campaign = serde_json::to_value(fixture().campaign()).unwrap();
    campaign["tiles"]["90"] = json!({
        "name":"Vital Amulet","kind":"equipment","item":"amulet","stat":"hp","amount":25,
    });
    campaign["floors"][0]["tiles"][5] = json!(90);
    let mut game = Engine::from_json(&campaign.to_string()).unwrap();
    step(&mut game, "right");
    assert_eq!(game.player().hp, 1025);
    assert_eq!(game.player().weapon.as_deref(), Some("sword_5"));
    assert_eq!(game.player().shield.as_deref(), Some("sacred_shield"));
    assert!(!game.campaign().is_equipment("amulet"));
    let observation = game.player_observation();
    assert!(
        observation["player"]["inventory"]
            .as_array()
            .unwrap()
            .iter()
            .any(|item| item == "amulet")
    );
    let item = observation["inventory_items"]
        .as_array()
        .unwrap()
        .iter()
        .find(|item| item["id"] == "amulet")
        .unwrap();
    assert_eq!(item["name"], "Vital Amulet");
    assert_eq!(item["usage"]["activation"], "passive");
}

#[test]
fn lower_pickups_replace_display_slots_but_add_stats_and_preserve_magic_protection() {
    let mut game = fixture();
    step(&mut game, "right");
    step(&mut game, "right");
    assert_eq!(game.player().weapon.as_deref(), Some("sword_1"));
    assert_eq!(game.player().shield.as_deref(), Some("shield_1"));
    assert_eq!((game.player().attack, game.player().defense), (110, 110));
    assert_eq!(
        game.player().hp,
        1000,
        "Sacred Shield's collected protection survives a lower shield"
    );
    assert!(
        game.player()
            .inventory
            .iter()
            .any(|item| item == "sacred_shield")
    );
    assert_eq!(
        game.player_observation()["player"]["inventory"],
        json!(["strip", "clearer"])
    );
    assert_eq!(
        game.player_observation()["abilities"]["field_magic_protection"],
        true
    );
}

#[test]
fn slot_removal_stays_empty_after_save_and_does_not_change_accumulated_stats() {
    let mut game = fixture();
    step(&mut game, "right");
    step(&mut game, "right");
    game.command(json!({"type":"use_item","item":"strip"}))
        .unwrap();
    assert_eq!(
        (game.player().weapon.as_ref(), game.player().shield.as_ref()),
        (None, None)
    );
    let save = game.save_json();
    let mut restored = fixture();
    restored.load_json(&save).unwrap();
    assert_eq!(
        (
            restored.player().weapon.as_ref(),
            restored.player().shield.as_ref()
        ),
        (None, None)
    );
    assert_eq!(
        (restored.player().attack, restored.player().defense),
        (110, 110)
    );
    assert!(
        restored
            .player()
            .inventory
            .iter()
            .any(|item| item == "sacred_shield")
    );
    restored
        .command(json!({"type":"use_item","item":"clearer"}))
        .unwrap();
    assert!(restored.player().inventory.is_empty());
    assert_eq!(
        (
            restored.player().weapon.as_ref(),
            restored.player().shield.as_ref()
        ),
        (None, None)
    );
}

#[test]
fn legacy_inventory_infers_slots_once_without_reapplying_pickup_bonuses() {
    let mut game = fixture();
    step(&mut game, "right");
    step(&mut game, "right");
    let mut save: Value = serde_json::from_str(&game.save_json()).unwrap();
    save["player"].as_object_mut().unwrap().remove("weapon");
    save["player"].as_object_mut().unwrap().remove("shield");
    let mut restored = fixture();
    restored.load_json(&save.to_string()).unwrap();
    assert_eq!(restored.player().weapon.as_deref(), Some("sword_1"));
    assert_eq!(restored.player().shield.as_deref(), Some("shield_1"));
    assert_eq!(
        (restored.player().attack, restored.player().defense),
        (110, 110)
    );
}

#[test]
fn a_new_cycle_restores_original_start_slots_and_carries_total_stats() {
    let mut game = fixture();
    step(&mut game, "right");
    step(&mut game, "right");
    step(&mut game, "down");
    step(&mut game, "right");
    assert_eq!(game.snapshot()["cycle"], 2);
    assert_eq!(game.player().weapon.as_deref(), Some("sword_5"));
    assert_eq!(game.player().shield.as_deref(), Some("sacred_shield"));
    assert_eq!((game.player().attack, game.player().defense), (110, 110));
}

#[test]
fn invalid_slot_import_leaves_state_untouched() {
    let mut game = fixture();
    let before = game.save_json();
    let mut save: Value = serde_json::from_str(&before).unwrap();
    save["player"]["weapon"] = json!("shield_1");
    assert!(
        game.load_json(&save.to_string())
            .unwrap_err()
            .contains("weapon")
    );
    assert_eq!(game.save_json(), before);
}

#[test]
fn original_capture_clears_both_slots_in_each_cycle() {
    for cycle in [1, 2] {
        let mut game = Engine::from_json(include_str!("../../../data/campaign.json")).unwrap();
        let mut save: Value = serde_json::from_str(&game.save_json()).unwrap();
        save["cycle"] = json!(cycle);
        save["player"]["floor"] = json!(3);
        save["player"]["x"] = json!(4);
        save["player"]["y"] = json!(9);
        game.load_json(&save.to_string()).unwrap();
        step(&mut game, "up");
        assert_eq!(game.player().floor, 2);
        assert_eq!(
            (game.player().weapon.as_ref(), game.player().shield.as_ref()),
            (None, None)
        );
        assert_eq!(
            game.player_observation()["abilities"]["field_magic_protection"],
            false
        );
    }
}
