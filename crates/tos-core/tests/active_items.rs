//! Regression cases for original item rules recovered from installed TSW.exe.
use serde_json::{Value, json};
use tos_core::Engine;

fn fixture(item: &str) -> Value {
    json!({
        "id":"original-item-rules","title":"Active item rules","width":5,"height":5,
        "start":{"floor":1,"x":2,"y":2,"hp":100,"attack":10,"defense":5,
            "inventory":[item]},
        "floors":[{"id":1,"tiles":vec![6;25]}],
        "rules":{"empty_tile":6,"wall_break_tile_ranges":[[8,8]]},
        "tiles":{
            "6":{"name":"Road","kind":"floor"},
            "8":{"name":"Ordinary wall","kind":"wall"},
            "9":{"name":"Hidden wall","kind":"hidden_wall"},
            "10":{"name":"Scripted wall","kind":"wall"},
            "13":{"name":"Lava","kind":"lava"},
            "61":{"name":"Slime","kind":"enemy","enemy":"slime"},
            "91":{"name":"Resistant enemy","kind":"enemy","enemy":"resistant"},
            "98":{"name":"Large creature body","kind":"wall"}
        },
        "enemies":{
            "slime":{"name":"Slime","hp":20,"attack":8,"defense":1,"gold":2},
            "resistant":{"name":"Resistant enemy","hp":20,"attack":8,"defense":1,"gold":9}
        }
    })
}

fn set_tile(value: &mut Value, x: usize, y: usize, tile: u16) {
    value["floors"][0]["tiles"][y * 5 + x] = json!(tile);
}

fn game(value: Value) -> Engine {
    Engine::from_json(&value.to_string()).unwrap()
}

fn use_item(engine: &mut Engine, item: &str) {
    engine
        .command(json!({"type":"use_item","item":item}))
        .unwrap();
}

#[test]
fn bomb_excludes_diagonal_and_distant_enemies_and_keeps_raw_rewards() {
    let mut value = fixture("bomb");
    value["start"]["inventory"] = json!(["bomb", "lucky_gold"]);
    for (x, y, tile) in [
        (2, 1, 61),
        (3, 2, 61),
        (2, 3, 61),
        (1, 2, 91),
        (3, 3, 61),
        (4, 2, 61),
    ] {
        set_tile(&mut value, x, y, tile);
    }
    let mut engine = game(value);
    use_item(&mut engine, "bomb");
    for (x, y) in [(2, 1), (3, 2), (2, 3)] {
        assert_eq!(engine.tile_at(1, x, y), Some(6));
    }
    for (x, y, tile) in [(1, 2, 91), (3, 3, 61), (4, 2, 61)] {
        assert_eq!(engine.tile_at(1, x, y), Some(tile));
    }
    assert_eq!(engine.player().gold, 6);
    assert_eq!(engine.player().hp, 100);
    assert_eq!(engine.player().inventory, vec!["lucky_gold"]);
}

#[test]
fn original_bomb_eligibility_matches_every_defined_original_tile_and_animation_frame() {
    let evidence: Value =
        serde_json::from_str(include_str!("../../../data/original-door-bomb-audit.json")).unwrap();
    let original = Engine::from_json(include_str!("../../../data/campaign.json")).unwrap();
    for (id, definition) in &original.campaign().tiles {
        let tile = id.parse::<usize>().unwrap();
        let allowed = evidence["tile_classifier"][tile]["kind"] == 2;
        let mut engine = original.clone();
        let mut saved: Value = serde_json::from_str(&engine.save_json()).unwrap();
        saved["player"]["floor"] = json!(1);
        saved["player"]["x"] = json!(5);
        saved["player"]["y"] = json!(5);
        saved["player"]["gold"] = json!(1000);
        saved["player"]["inventory"] = json!(["bomb", "lucky_gold"]);
        saved["cycle"] = json!(3);
        saved["floors"]["1"] = json!(vec![6; 121]);
        saved["floors"]["1"][49] = json!(tile);
        saved["floors"]["1"][72] = json!(61); // Diagonal control
        engine.load_json(&saved.to_string()).unwrap();
        use_item(&mut engine, "bomb");
        assert_eq!(
            engine.tile_at(1, 5, 4),
            Some(if allowed { 6 } else { tile as u16 }),
            "tile {tile}: {}",
            definition.name
        );
        let reward = if allowed {
            original.campaign().enemies[definition.enemy.as_ref().unwrap()].gold
        } else {
            0
        };
        assert_eq!(engine.player().gold, 1000 + reward, "tile {tile}");
        assert_eq!(engine.tile_at(1, 6, 6), Some(61));
        assert_eq!(engine.player().inventory, vec!["lucky_gold"]);
    }
}

#[test]
fn original_bomb_boundaries_match_all_121_executable_coordinate_cases() {
    let evidence: Value =
        serde_json::from_str(include_str!("../../../data/original-door-bomb-audit.json")).unwrap();
    let original = Engine::from_json(include_str!("../../../data/campaign.json")).unwrap();
    for case in evidence["bomb_coordinate_cases"].as_array().unwrap() {
        let (x, y) = (
            case["x"].as_u64().unwrap() as usize,
            case["y"].as_u64().unwrap() as usize,
        );
        let mut engine = original.clone();
        let mut saved: Value = serde_json::from_str(&engine.save_json()).unwrap();
        saved["player"]["floor"] = json!(1);
        saved["player"]["x"] = json!(x);
        saved["player"]["y"] = json!(y);
        saved["player"]["gold"] = json!(1000);
        saved["player"]["inventory"] = json!(["bomb"]);
        saved["floors"]["1"] = json!(vec![61; 121]);
        saved["floors"]["1"][y * 11 + x] = json!(6);
        engine.load_json(&saved.to_string()).unwrap();
        use_item(&mut engine, "bomb");
        for index in 0..121 {
            let removed = case["removed_indices"]
                .as_array()
                .unwrap()
                .contains(&json!(index));
            let expected = if removed || index == y * 11 + x {
                6
            } else {
                61
            };
            assert_eq!(
                engine.tile_at(1, index % 11, index / 11),
                Some(expected),
                "Bomb at ({x},{y}), tile {index}"
            );
        }
        assert_eq!(json!(engine.player().gold), case["gold_after"]);
    }
}

#[test]
fn snow_crystal_cools_only_immediate_neighbors_and_remains_reusable() {
    let mut value = fixture("snow_crystal");
    for (x, y) in [(2, 1), (3, 2), (2, 3), (1, 2), (3, 3), (4, 2)] {
        set_tile(&mut value, x, y, 13);
    }
    let mut engine = game(value);
    use_item(&mut engine, "snow_crystal");
    for (x, y) in [(2, 1), (3, 2), (2, 3), (1, 2)] {
        assert_eq!(engine.tile_at(1, x, y), Some(6));
    }
    for (x, y) in [(3, 3), (4, 2)] {
        assert_eq!(
            engine.tile_at(1, x, y),
            Some(13),
            "Connected lava beyond one cell must remain"
        );
    }
    engine
        .command(json!({"type":"move","direction":"right"}))
        .unwrap();
    use_item(&mut engine, "snow_crystal");
    assert_eq!(engine.tile_at(1, 3, 3), Some(6));
    assert_eq!(engine.tile_at(1, 4, 2), Some(6));
    assert_eq!(engine.player().inventory, vec!["snow_crystal"]);
}

#[test]
fn original_mattocks_exclude_scripted_walls_hidden_walls_and_creature_bodies() {
    for item in ["mattock", "super_mattock"] {
        let mut value = fixture(item);
        for (x, y, tile) in [(3, 2, 8), (1, 2, 10), (2, 1, 9), (2, 3, 98), (4, 4, 8)] {
            set_tile(&mut value, x, y, tile);
        }
        let mut engine = game(value);
        use_item(&mut engine, item);
        assert_eq!(engine.tile_at(1, 3, 2), Some(6));
        assert_eq!(
            engine.tile_at(1, 4, 4),
            Some(if item == "super_mattock" { 6 } else { 8 })
        );
        for (x, y, tile) in [(1, 2, 10), (2, 1, 9), (2, 3, 98)] {
            assert_eq!(
                engine.tile_at(1, x, y),
                Some(tile),
                "{item} broke a special wall"
            );
        }
        assert!(engine.player().inventory.is_empty());
    }
}

#[test]
fn custom_campaigns_can_use_non_original_wall_ids_and_disable_breaking_explicitly() {
    for item in ["mattock", "super_mattock"] {
        for disabled in [false, true] {
            let mut value = fixture(item);
            value["rules"]
                .as_object_mut()
                .unwrap()
                .remove("wall_break_tile_ranges");
            value["tiles"]["20"] = json!({"name":"Custom wall","kind":"wall"});
            set_tile(&mut value, 3, 2, 20);
            if disabled {
                value["rules"]["wall_break_tile_ranges"] = json!([]);
            }
            let mut engine = game(value);
            use_item(&mut engine, item);
            assert_eq!(engine.tile_at(1, 3, 2), Some(if disabled { 20 } else { 6 }));
            assert!(engine.player().inventory.is_empty());
        }
    }
}

#[test]
fn empty_uses_consume_the_four_original_consumable_tools() {
    for item in ["mattock", "super_mattock", "magic_key", "bomb"] {
        let mut engine = game(fixture(item));
        use_item(&mut engine, item);
        assert!(
            engine.player().inventory.is_empty(),
            "Empty {item} use must consume it"
        );
        assert_eq!(engine.snapshot()["last_action"]["ok"], true);
        assert_eq!((engine.player().hp, engine.player().gold), (100, 0));
    }
}

#[test]
fn malformed_wall_break_ranges_are_rejected_before_gameplay() {
    for ranges in [
        json!([[8, "8"]]),
        json!([[8, 7]]),
        json!([[8, 8, 8]]),
        json!([[8.0, 8]]),
        json!([[0, 65536]]),
        json!({"min":8,"max":8}),
    ] {
        let mut value = fixture("mattock");
        value["rules"]["wall_break_tile_ranges"] = ranges;
        let error = match Engine::from_json(&value.to_string()) {
            Ok(_) => panic!("Malformed ranges accepted"),
            Err(error) => error,
        };
        assert!(error.contains("wall_break_tile_ranges"), "{error}");
    }
}

#[test]
fn original_flight_uses_unlocked_range_excludes_zero_and_44_and_preserves_same_floor_position() {
    let mut value = fixture("flying_orb");
    value["rules"]["flying_requires_stairs"] = json!(false);
    value["rules"]["flying_original_selection"] = json!(true);
    for floor in [0, 2, 3, 44, 45] {
        value["floors"]
            .as_array_mut()
            .unwrap()
            .push(json!({"id":floor,"tiles":vec![6;25],
            "arrival_up":{"x":0,"y":0},"arrival_down":{"x":4,"y":4}}));
    }
    value["start"]["floor"] = json!(3);
    let mut engine = game(value);
    let mut save: Value = serde_json::from_str(&engine.save_json()).unwrap();
    save["visited_floors"] = json!([0, 1, 3, 44, 45]);
    save["highest_stair_floor"] = json!(45);
    engine.load_json(&save.to_string()).unwrap();
    let usage = &engine.player_observation()["inventory_items"][0]["usage"];
    assert_eq!(usage["allowed_floors"], json!([1, 2, 3, 45]));
    assert_eq!(usage["target_floor"], "available_floor");
    engine
        .command(json!({"type":"use_item","item":"flying_orb","floor":3}))
        .unwrap();
    assert_eq!(
        (engine.player().floor, engine.player().x, engine.player().y),
        (3, 2, 2)
    );
    for target in [0, 44] {
        engine
            .command(json!({"type":"use_item","item":"flying_orb","floor":target}))
            .unwrap();
        assert_eq!(engine.snapshot()["last_action"]["ok"], false);
        assert_eq!(engine.player().floor, 3);
    }
    engine
        .command(json!({"type":"use_item","item":"flying_orb","floor":2}))
        .unwrap();
    assert_eq!(engine.snapshot()["last_action"]["ok"], true);
    assert_eq!(
        (engine.player().floor, engine.player().x, engine.player().y),
        (2, 4, 4)
    );
    assert!(
        engine.player_observation()["visited_floors"]
            .as_array()
            .unwrap()
            .contains(&json!(2))
    );
    assert_eq!(engine.player().inventory, vec!["flying_orb"]);
}

#[test]
fn custom_flight_remains_visited_only_and_allows_visited_zero_or_44() {
    let mut value = fixture("orb_of_flying");
    value["rules"]["flying_requires_stairs"] = json!(false);
    for floor in [0, 2, 3, 44] {
        value["floors"]
            .as_array_mut()
            .unwrap()
            .push(json!({"id":floor,"tiles":vec![6;25]}));
    }
    let mut engine = game(value);
    let mut save: Value = serde_json::from_str(&engine.save_json()).unwrap();
    save["visited_floors"] = json!([0, 1, 3, 44]);
    engine.load_json(&save.to_string()).unwrap();
    let usage = &engine.player_observation()["inventory_items"][0]["usage"];
    assert_eq!(usage["allowed_floors"], json!([0, 1, 3, 44]));
    assert_eq!(usage["target_floor"], "visited_floor");
    engine
        .command(json!({"type":"use_item","item":"orb_of_flying","floor":2}))
        .unwrap();
    assert_eq!(engine.snapshot()["last_action"]["ok"], false);
    for target in [0, 44] {
        engine
            .command(json!({"type":"use_item","item":"orb_of_flying","floor":target}))
            .unwrap();
        assert_eq!(engine.snapshot()["last_action"]["ok"], true);
        assert_eq!(engine.player().floor, target);
    }
}

#[test]
fn flight_and_wisdom_rule_types_are_validated() {
    for (key, bad) in [
        ("flying_original_selection", json!("true")),
        ("wisdom_dialogue_range", json!([62, 61])),
        ("wisdom_dialogue_range", json!([62, 85, 86])),
        ("wisdom_dialogue_range", json!([-1, 85])),
        ("wisdom_dialogue_range", json!([62, "85"])),
        ("wisdom_dialogue_range", json!([62, 4294967296_u64])),
    ] {
        let mut value = fixture("flying_orb");
        value["rules"][key] = bad;
        let error = match Engine::from_json(&value.to_string()) {
            Ok(_) => panic!("Malformed {key} accepted"),
            Err(error) => error,
        };
        assert!(error.contains(key), "{error}");
    }
}

#[test]
fn wings_do_not_unlock_flight_destinations_until_a_stair_is_used_and_counter_survives_reload() {
    let mut value = fixture("up_wing");
    value["start"]["inventory"] = json!(["up_wing", "flying_orb"]);
    value["rules"]["flying_original_selection"] = json!(true);
    value["rules"]["flying_requires_stairs"] = json!(false);
    value["tiles"]["11"] = json!({"name":"Up stairs","kind":"stairs_up"});
    for floor in [2, 3] {
        let mut tiles = vec![6; 25];
        tiles[17] = 11;
        value["floors"]
            .as_array_mut()
            .unwrap()
            .push(json!({"id":floor,"tiles":tiles,
            "arrival_up":{"x":2,"y":2}}));
    }
    let mut engine = game(value.clone());
    use_item(&mut engine, "up_wing");
    assert_eq!(engine.player().floor, 2);
    let serialized = engine.save_json();
    assert_eq!(
        serde_json::from_str::<Value>(&serialized).unwrap()["highest_stair_floor"],
        1
    );
    let mut restored = game(value);
    restored.load_json(&serialized).unwrap();
    restored
        .command(json!({"type":"use_item","item":"flying_orb","floor":2}))
        .unwrap();
    assert_eq!(restored.snapshot()["last_action"]["ok"], false);
    restored
        .command(json!({"type":"move","direction":"down"}))
        .unwrap();
    assert_eq!(restored.player().floor, 3);
    assert_eq!(
        serde_json::from_str::<Value>(&restored.save_json()).unwrap()["highest_stair_floor"],
        3
    );
    restored
        .command(json!({"type":"use_item","item":"flying_orb","floor":2}))
        .unwrap();
    assert_eq!(restored.snapshot()["last_action"]["ok"], true);
    assert_eq!(restored.player().floor, 2);
    let checkpoint = restored.runtime_checkpoint_json();
    restored
        .restore_runtime_checkpoint_json(&checkpoint)
        .unwrap();
    assert_eq!(
        serde_json::from_str::<Value>(&restored.save_json()).unwrap()["highest_stair_floor"],
        3
    );
}

#[test]
fn legacy_saves_fall_back_to_visited_floors_and_invalid_counters_are_rejected_atomically() {
    let mut value = fixture("flying_orb");
    value["rules"]["flying_original_selection"] = json!(true);
    value["rules"]["flying_requires_stairs"] = json!(false);
    value["floors"]
        .as_array_mut()
        .unwrap()
        .push(json!({"id":2,"tiles":vec![6;25]}));
    let mut engine = game(value);
    let mut save: Value = serde_json::from_str(&engine.save_json()).unwrap();
    save["visited_floors"] = json!([1, 2]);
    save.as_object_mut().unwrap().remove("highest_stair_floor");
    engine.load_json(&save.to_string()).unwrap();
    assert_eq!(
        engine.player_observation()["inventory_items"][0]["usage"]["allowed_floors"],
        json!([1, 2])
    );
    let before = engine.save_json();
    save["highest_stair_floor"] = json!(999);
    assert!(
        engine
            .load_json(&save.to_string())
            .unwrap_err()
            .contains("highest stair floor")
    );
    assert_eq!(engine.save_json(), before);
}

#[test]
fn original_capture_resets_stair_upper_bound_in_both_cycles_and_cycle_reset_returns_to_start() {
    let campaign: Value =
        serde_json::from_str(include_str!("../../../data/campaign.json")).unwrap();
    for cycle in [1, 2] {
        let mut engine = game(campaign.clone());
        let mut save: Value = serde_json::from_str(&engine.save_json()).unwrap();
        save["cycle"] = json!(cycle);
        save["highest_stair_floor"] = json!(45);
        save["player"]["floor"] = json!(3);
        save["player"]["x"] = json!(4);
        save["player"]["y"] = json!(7);
        save["visited_floors"] = json!([1, 2, 3, 45]);
        engine.load_json(&save.to_string()).unwrap();
        engine
            .command(json!({"type":"move","direction":"down"}))
            .unwrap();
        assert_eq!(engine.player().floor, 2);
        assert_eq!(
            serde_json::from_str::<Value>(&engine.save_json()).unwrap()["highest_stair_floor"],
            2
        );
    }
    let mut value = fixture("flying_orb");
    value["rules"]["backside"] = json!({"enabled":true});
    value["events"] = json!([{"trigger":{"type":"step","floor":1,"x":3,"y":2},
        "effects":[{"type":"next_cycle"}]}]);
    let mut engine = game(value);
    engine
        .command(json!({"type":"move","direction":"right"}))
        .unwrap();
    assert_eq!(engine.snapshot()["cycle"], 2);
    assert_eq!(
        serde_json::from_str::<Value>(&engine.save_json()).unwrap()["highest_stair_floor"],
        1
    );
}

#[test]
fn flight_help_does_not_name_excluded_hidden_floors_before_they_are_discovered() {
    let mut value = fixture("flying_orb");
    value["rules"]["flying_original_selection"] = json!(true);
    let engine = game(value);
    let help = engine.player_observation()["inventory_items"][0]["usage"].to_string();
    assert!(!help.contains("44"));
    assert!(!help.contains("hidden"));
    assert!(!help.contains("puzzle"));
}

#[test]
fn descending_stairs_from_a_wing_reached_floor_do_not_raise_the_flight_bound() {
    let mut value = fixture("up_wing");
    value["start"]["inventory"] = json!(["up_wing", "flying_orb"]);
    value["rules"]["flying_original_selection"] = json!(true);
    value["rules"]["flying_requires_stairs"] = json!(false);
    value["tiles"]["12"] = json!({"name":"Down stairs","kind":"stairs_down"});
    value["tiles"]["44"] = json!({"name":"Up wing","kind":"item","item":"up_wing"});
    let mut tiles = vec![6; 25];
    tiles[13] = 44;
    value["floors"]
        .as_array_mut()
        .unwrap()
        .push(json!({"id":2,"tiles":tiles}));
    let mut tiles = vec![6; 25];
    tiles[18] = 12;
    value["floors"]
        .as_array_mut()
        .unwrap()
        .push(json!({"id":3,"tiles":tiles}));
    let mut engine = game(value);
    use_item(&mut engine, "up_wing");
    engine
        .command(json!({"type":"move","direction":"right"}))
        .unwrap();
    use_item(&mut engine, "up_wing");
    assert_eq!(engine.player().floor, 3);
    engine
        .command(json!({"type":"move","direction":"down"}))
        .unwrap();
    assert_eq!(engine.player().floor, 2);
    assert_eq!(
        serde_json::from_str::<Value>(&engine.save_json()).unwrap()["highest_stair_floor"],
        1
    );
}
