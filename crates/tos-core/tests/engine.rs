use serde_json::{Value, json};
use tos_core::{Enemy, Engine, Player, forecast};

fn fixture() -> Value {
    json!({"id":"test","title":"Rule verification","width":5,"height":5,
      "start":{"floor":1,"x":0,"y":0,"hp":100,"attack":10,"defense":5,"gold":100,"keys":{"yellow":0,"blue":0,"red":0},"inventory":[]},
      "rules":{"empty_tile":6},
      "floors":[{"id":1,"tiles":[6,29,1,61,6, 6,15,6,6,6, 8,6,6,6,6, 6,6,6,6,6, 6,6,6,6,11]},
                {"id":2,"arrival_up":{"x":1,"y":0},"arrival_down":{"x":1,"y":0},"tiles":[12,6,6,6,6, 6,15,6,6,6, 6,6,6,6,6, 6,6,6,6,6, 6,6,6,6,6]}],
      "tiles":{"6":{"name":"Road","kind":"floor"},"8":{"name":"Wall","kind":"wall"},"29":{"name":"Yellow key","kind":"key","key":"yellow","amount":1},"1":{"name":"Yellow door","kind":"door","key":"yellow"},"61":{"name":"Slime","kind":"enemy","enemy":"slime"},"15":{"name":"Altar","kind":"altar"},"11":{"name":"Up","kind":"stairs_up"},"12":{"name":"Down","kind":"stairs_down"}},
      "enemies":{"slime":{"name":"Slime","hp":20,"attack":8,"defense":1,"gold":2}},"events":[]})
}
fn game(value: &Value) -> Engine {
    Engine::from_json(&value.to_string()).unwrap()
}
fn move_to(engine: &mut Engine, direction: &str) {
    engine
        .command(json!({"type":"move","direction":direction}))
        .unwrap();
}
fn teleport(engine: &mut Engine, floor: i32, x: usize, y: usize) {
    let mut save: Value = serde_json::from_str(&engine.save_json()).unwrap();
    save["player"]["floor"] = json!(floor);
    save["player"]["x"] = json!(x);
    save["player"]["y"] = json!(y);
    engine.load_json(&save.to_string()).unwrap();
}

#[test]
fn hero_first_formula_and_lethal_boundary() {
    let p = Player {
        hp: 7,
        attack: 10,
        defense: 5,
        ..Default::default()
    };
    let e = Enemy {
        name: "Slime".into(),
        hp: 20,
        attack: 8,
        defense: 1,
        gold: 2,
        special: String::new(),
    };
    assert_eq!(forecast(&p, &e).damage, Some(6));
    assert!(forecast(&p, &e).can_win);
    let p = Player { hp: 6, ..p };
    assert!(!forecast(&p, &e).can_win);
    let e = Enemy { hp: 9, ..e };
    assert_eq!(forecast(&p, &e).damage, Some(0));
}
#[test]
fn cross_doubles_attack_but_preserves_original_base_attack_guard() {
    let p = Player {
        hp: 100,
        attack: 10,
        defense: 5,
        inventory: vec!["cross".into()],
        ..Default::default()
    };
    let e = Enemy {
        name: "Zombie".into(),
        hp: 30,
        attack: 8,
        defense: 9,
        gold: 1,
        special: "undead".into(),
    };
    assert_eq!(forecast(&p, &e).damage, Some(6));
    assert_eq!(forecast(&p, &Enemy { defense: 10, ..e }).damage, None);
}
#[test]
fn key_door_and_battle_are_committed_once() {
    let mut e = game(&fixture());
    move_to(&mut e, "right");
    assert_eq!(e.player().keys.yellow, 1);
    move_to(&mut e, "right");
    assert_eq!(e.player().keys.yellow, 0);
    move_to(&mut e, "right");
    assert_eq!(e.player().hp, 94);
    assert_eq!(e.player().gold, 102);
    move_to(&mut e, "left");
    move_to(&mut e, "right");
    assert_eq!(e.player().gold, 102);
}
#[test]
fn blocked_moves_do_not_advance_or_damage_player() {
    let mut e = game(&fixture());
    let initial = e.save_json();
    move_to(&mut e, "left");
    assert_eq!(initial, e.save_json());
    move_to(&mut e, "down");
    let save = e.save_json();
    move_to(&mut e, "down");
    assert_eq!(save, e.save_json());
}
#[test]
fn altar_cost_is_quadratic_and_shared_between_floors() {
    let mut e = game(&fixture());
    move_to(&mut e, "down");
    move_to(&mut e, "right");
    assert_eq!(
        e.snapshot()["pending_interaction"]["choices"][0]["cost"],
        20
    );
    e.command(json!({"type":"choose","choice":"defense"}))
        .unwrap();
    assert_eq!(e.player().defense, 9);
    assert_eq!(e.player().gold, 80);
    e.command(json!({"type":"cancel"})).unwrap();
    teleport(&mut e, 2, 0, 1);
    move_to(&mut e, "right");
    assert_eq!(
        e.snapshot()["pending_interaction"]["choices"][0]["cost"],
        40
    );
    e.command(json!({"type":"choose","choice":"hp"})).unwrap();
    assert_eq!(e.player().hp, 300);
    assert_eq!(e.player().gold, 40);
    assert_eq!(
        e.snapshot()["pending_interaction"]["choices"][0]["cost"],
        80
    );
}
#[test]
fn save_round_trip_preserves_pending_shop_flags_and_changed_tiles() {
    let mut e = game(&fixture());
    move_to(&mut e, "right");
    move_to(&mut e, "down");
    let mut restored = game(&fixture());
    restored.load_json(&e.save_json()).unwrap();
    assert_eq!(e.save_json(), restored.save_json());
    e.command(json!({"type":"choose","choice":"attack"}))
        .unwrap();
    restored
        .command(json!({"type":"choose","choice":"attack"}))
        .unwrap();
    assert_eq!(e.save_json(), restored.save_json());
}
#[test]
fn invalid_save_is_rejected_without_mutating_session() {
    let mut e = game(&fixture());
    let before = e.save_json();
    let mut invalid: Value = serde_json::from_str(&before).unwrap();
    invalid["player"]["x"] = json!(99);
    assert!(e.load_json(&invalid.to_string()).is_err());
    assert_eq!(before, e.save_json());
    let mut campaign = fixture();
    campaign["title"] = json!("Changed revision");
    assert!(game(&campaign).load_json(&before).is_err());
}
#[test]
fn original_stair_arrival_metadata_is_used() {
    let mut e = game(&fixture());
    teleport(&mut e, 1, 3, 4);
    move_to(&mut e, "right");
    assert_eq!((e.player().floor, e.player().x, e.player().y), (2, 1, 0));
}
#[test]
fn event_teleports_are_not_overwritten_by_movement_and_fire_once() {
    let mut value = fixture();
    value["events"] = json!([{"id":"ambush","trigger":{"type":"enemy_defeated","floor":1,"x":3,"y":0},"effects":[{"type":"teleport","floor":2,"x":2,"y":2},{"type":"add_stat","stat":"attack","amount":5},{"type":"flag","flag":"escaped"}]}]);
    let mut e = game(&value);
    teleport(&mut e, 1, 2, 0);
    move_to(&mut e, "right");
    assert_eq!((e.player().floor, e.player().x, e.player().y), (2, 2, 2));
    assert_eq!(e.player().attack, 15);
    assert_eq!(e.snapshot()["flags"][0], "escaped");
}
#[test]
fn forced_first_strike_and_runtime_enemy_stats_persist() {
    let mut value = fixture();
    value["events"] = json!([{"trigger":{"type":"step","floor":1,"x":0,"y":1},"effects":[{"type":"set_enemy","enemy":"slime","hp":10,"attack":10},{"type":"battle_at","floor":1,"x":3,"y":0,"first_strike":true}]}]);
    let mut e = game(&value);
    move_to(&mut e, "down");
    assert_eq!(e.player().hp, 90);
    assert_eq!(e.tile_at(1, 3, 0), Some(6));
    let mut restored = game(&value);
    restored.load_json(&e.save_json()).unwrap();
    assert_eq!(e.save_json(), restored.save_json());
}
#[test]
fn fatal_battle_ends_game_and_does_not_award_gold() {
    let mut value = fixture();
    value["start"]["hp"] = json!(6);
    let mut e = game(&value);
    teleport(&mut e, 1, 2, 0);
    move_to(&mut e, "right");
    assert_eq!(e.player().hp, 0);
    assert_eq!(e.snapshot()["status"], "lost");
    assert_eq!(e.player().gold, 100);
}
#[test]
fn elixir_matches_verified_original_formula() {
    let mut value = fixture();
    value["start"]["inventory"] = json!(["elixir"]);
    let mut e = game(&value);
    e.command(json!({"type":"use_item","item":"elixir"}))
        .unwrap();
    assert_eq!(e.player().hp, 225);
    assert!(e.player().inventory.is_empty());
}
#[test]
fn wing_checks_same_position_on_destination_and_preserves_item_on_failure() {
    let mut value = fixture();
    value["start"]["inventory"] = json!(["up_wing"]);
    let mut e = game(&value);
    e.command(json!({"type":"use_item","item":"up_wing"}))
        .unwrap();
    assert_eq!(e.player().floor, 1);
    assert_eq!(e.player().inventory.len(), 1);
    teleport(&mut e, 1, 2, 2);
    e.command(json!({"type":"use_item","item":"up_wing"}))
        .unwrap();
    assert_eq!((e.player().floor, e.player().x, e.player().y), (2, 2, 2));
    assert!(e.player().inventory.is_empty());
}
#[test]
fn imported_original_has_all_maps_and_verified_enemy_identities() {
    let engine = Engine::from_json(include_str!("../../../data/campaign.json")).unwrap();
    assert_eq!(engine.campaign.floors.len(), 51);
    assert_eq!(engine.campaign.enemies.len(), 33);
    let vampire = &engine.campaign.enemies[engine.campaign.tiles["95"].enemy.as_ref().unwrap()];
    assert_eq!(
        (vampire.hp, vampire.attack, vampire.defense),
        (444, 199, 66)
    );
    assert_eq!(vampire.special, "undead");
    assert_eq!(
        engine
            .campaign
            .floors
            .iter()
            .find(|f| f.id == 0)
            .unwrap()
            .tiles
            .len(),
        121
    );
}

#[test]
fn configured_combat_applies_identically_to_preview_and_action() {
    let mut value = fixture();
    value["rules"]["hero_attacks_first"] = json!(false);
    let mut e = game(&value);
    assert_eq!(e.inspect(3, 0)["enemy"]["damage"], 9);
    teleport(&mut e, 1, 2, 0);
    move_to(&mut e, "right");
    assert_eq!(e.player().hp, 91);
    value["rules"] = json!({"empty_tile":6,"cross_multiplier":3,"base_attack_guard":false});
    value["start"]["inventory"] = json!(["cross"]);
    value["enemies"]["slime"]["special"] = json!("undead");
    value["enemies"]["slime"]["defense"] = json!(10);
    let mut e = game(&value);
    assert_eq!(e.inspect(3, 0)["enemy"]["damage"], 0);
    teleport(&mut e, 1, 2, 0);
    move_to(&mut e, "right");
    assert_eq!(e.player().gold, 102);
}

#[test]
fn lucky_gold_reward_and_preview_match_and_bombs_keep_raw_rewards() {
    let mut value = fixture();
    value["start"]["inventory"] = json!(["lucky_gold", "bomb"]);
    let mut e = game(&value);
    assert_eq!(e.inspect(3, 0)["enemy"]["gold"], 4);
    teleport(&mut e, 1, 2, 0);
    move_to(&mut e, "right");
    assert_eq!(e.player().gold, 104);
    let mut e = game(&value);
    teleport(&mut e, 1, 2, 0);
    e.command(json!({"type":"use_item","item":"bomb"})).unwrap();
    assert_eq!(e.player().gold, 102);
    assert_eq!(e.player().hp, 100);
}

#[test]
fn one_time_merchants_remain_and_cannot_sell_twice() {
    let mut value = fixture();
    value["tiles"]["15"] = json!({"name":"Merchant","kind":"merchant","offers":[{"id":"blue","label":"Blue key","cost":20,"once":true,"effects":[{"type":"add_stat","stat":"blue","amount":1}]}]});
    let mut e = game(&value);
    move_to(&mut e, "down");
    move_to(&mut e, "right");
    e.command(json!({"type":"choose","choice":"blue"})).unwrap();
    assert_eq!(e.player().keys.blue, 1);
    assert_eq!(e.tile_at(1, 1, 1), Some(15));
    assert_eq!(
        e.snapshot()["pending_interaction"]["choices"]
            .as_array()
            .unwrap()
            .len(),
        1
    );
    e.command(json!({"type":"choose","choice":"blue"})).unwrap();
    assert_eq!(e.player().keys.blue, 1);
    assert_eq!(e.player().gold, 80);
}

#[test]
fn magic_hazards_apply_only_on_steps_and_sacred_shield_protects() {
    let mut value = fixture();
    value["floors"][0]["tiles"][2] = json!(6);
    value["start"]["hp"] = json!(1000);
    value["enemies"]["slime"]["special"] = json!("magician_a");
    let mut e = game(&value);
    teleport(&mut e, 1, 2, 1);
    move_to(&mut e, "up");
    assert_eq!(e.player().hp, 800);
    let mut value = fixture();
    value["floors"][0]["tiles"][2] = json!(6);
    value["start"]["inventory"] = json!(["sacred_shield"]);
    value["enemies"]["slime"]["special"] = json!("magician_a");
    let mut e = game(&value);
    teleport(&mut e, 1, 2, 1);
    move_to(&mut e, "up");
    assert_eq!(e.player().hp, 100);
}

#[test]
fn noncombat_completion_is_inspected_as_a_character_and_never_fights() {
    let mut value = fixture();
    value["events"] = json!([{"id":"completion","trigger":{"type":"bump","floor":1,"x":3,"y":0,"tile":61},"effects":[{"type":"win"}]}]);
    let mut e = game(&value);
    assert_eq!(e.inspect(3, 0)["kind"], "npc");
    assert!(e.inspect(3, 0)["enemy"].is_null());
    assert!(e.snapshot()["enemies"].as_array().unwrap().is_empty());
    teleport(&mut e, 1, 2, 0);
    move_to(&mut e, "right");
    assert_eq!(e.snapshot()["status"], "won");
    assert_eq!(e.player().hp, 100);
    assert_eq!(e.player().gold, 100);
}
