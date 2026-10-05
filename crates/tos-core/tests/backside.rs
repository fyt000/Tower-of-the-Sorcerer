//! Original-campaign scenarios for the item unlock and replay/backside tower.
//! Explicit scenario saves isolate mechanics; these are not a natural full route.
use serde_json::{Value, json};
use tos_core::Engine;

fn original() -> Engine {
    Engine::from_json(include_str!("../../../data/campaign.json")).unwrap()
}

fn edit(game: &mut Engine, change: impl FnOnce(&mut Value)) {
    let mut save: Value = serde_json::from_str(&game.save_json()).unwrap();
    change(&mut save);
    game.load_json(&save.to_string()).unwrap();
}

fn place(save: &mut Value, floor: i32, x: usize, y: usize) {
    save["player"]["floor"] = json!(floor);
    save["player"]["x"] = json!(x);
    save["player"]["y"] = json!(y);
    save["pending_interaction"] = Value::Null;
    save["pending_tile"] = Value::Null;
}

fn step(game: &mut Engine, direction: &str) {
    game.command(json!({"type":"move","direction":direction}))
        .unwrap();
}

fn choose(game: &mut Engine, choice: &str) {
    game.command(json!({"type":"choose","choice":choice}))
        .unwrap();
}

#[test]
fn original_old_man_gift_unlocks_inspection_and_cannot_be_claimed_twice() {
    let mut game = original();
    edit(&mut game, |save| {
        place(save, 3, 9, 3);
        save["player"]["inventory"] = json!(["wisdom_orb"]);
    });
    assert!(game.inspect(6, 4)["enemy"].is_null());
    assert_eq!(game.inspect(6, 4)["details_locked"], true);
    assert_eq!(game.snapshot()["enemies"], json!([]));
    step(&mut game, "right");
    assert_eq!(game.snapshot()["pending_interaction"]["title"], "Old man");
    choose(&mut game, "accept");
    assert!(game.player().inventory.contains(&"hero_orb".to_owned()));
    assert_eq!(game.inspect(6, 4)["enemy"]["hp"], 35);
    assert_eq!(game.inspect(6, 4)["enemy"]["attack"], 18);
    assert_eq!(game.inspect(6, 4)["enemy"]["defense"], 1);
    assert_eq!(game.inspect(6, 4)["details_locked"], false);
    let pending = game.snapshot()["pending_interaction"].clone();
    assert!(
        !pending["choices"]
            .as_array()
            .unwrap()
            .iter()
            .any(|choice| choice["id"] == "accept")
    );
    let save = game.save_json();
    let mut restored = original();
    restored.load_json(&save).unwrap();
    assert_eq!(restored.inspect(6, 4)["enemy"]["hp"], 35);
}

#[test]
fn backside_capture_preserves_stats_gold_and_keys_but_steals_every_item() {
    let mut game = original();
    edit(&mut game, |save| {
        save["cycle"] = json!(2);
        place(save, 3, 4, 9);
        save["player"]["hp"] = json!(12345);
        save["player"]["attack"] = json!(321);
        save["player"]["defense"] = json!(456);
        save["player"]["gold"] = json!(789);
        save["player"]["keys"] = json!({"yellow":3,"blue":2,"red":1});
        save["player"]["inventory"] = json!([
            "sword_5",
            "sacred_shield",
            "hero_orb",
            "cross",
            "warp_staff"
        ]);
        save["player"]["item_charges"] = json!({"warp_staff":2});
    });
    step(&mut game, "up");
    assert_eq!(
        (game.player().floor, game.player().x, game.player().y),
        (2, 2, 7)
    );
    assert_eq!(
        (
            game.player().hp,
            game.player().attack,
            game.player().defense,
            game.player().gold
        ),
        (12345, 321, 456, 789)
    );
    assert_eq!(
        (
            game.player().keys.yellow,
            game.player().keys.blue,
            game.player().keys.red
        ),
        (3, 2, 1)
    );
    assert!(game.player().inventory.is_empty());
    assert!(game.player().item_charges.is_empty());
    assert!(!game.forecasts_unlocked());
    let snapshot = game.snapshot();
    let presentation = snapshot["last_action"]["presentation"].as_array().unwrap();
    assert!(
        presentation
            .iter()
            .any(|event| event["type"] == "cinematic" && event["kind"] == "magic")
    );
    assert!(
        presentation
            .iter()
            .any(|event| event["type"] == "cinematic" && event["kind"] == "capture")
    );
    assert!(
        presentation
            .iter()
            .any(|event| event["type"] == "audio" && event["name"] == "3f")
    );
    for id in [9, 10, 0, 1, 2, 3] {
        assert!(
            presentation
                .iter()
                .any(|event| event["type"] == "dialogue" && event["dialogue_id"] == id)
        );
    }
}

#[test]
fn first_ending_resets_maps_flags_counters_keys_and_gold_while_carrying_stats() {
    let mut game = original();
    edit(&mut game, |save| {
        place(save, 50, 5, 5);
        save["floors"]["50"][49] = json!(91);
        save["floors"]["1"][0] = json!(6);
        save["player"]["hp"] = json!(12345);
        save["player"]["attack"] = json!(321);
        save["player"]["defense"] = json!(456);
        save["player"]["gold"] = json!(789);
        save["player"]["keys"] = json!({"yellow":3,"blue":2,"red":1});
        save["player"]["inventory"] = json!(["hero_orb", "cross", "warp_staff"]);
        save["player"]["item_charges"] = json!({"warp_staff":2});
        save["flags"] = json!(["captured", "decoy_zeno_defeated"]);
        save["event_counts"] = json!({"capture_on_floor_3":1,"floor_49_dice_seal":1});
        save["shop_visits"] = json!({"altar":7});
        save["visited_floors"] = json!([1, 3, 25, 49, 50]);
    });
    step(&mut game, "up");
    assert_eq!(game.snapshot()["cycle"], 2);
    assert_eq!(game.snapshot()["backside_multiplier"], 44);
    assert_eq!(game.snapshot()["status"], "playing");
    assert_eq!(
        (game.player().floor, game.player().x, game.player().y),
        (1, 5, 10)
    );
    assert_eq!(
        (
            game.player().hp,
            game.player().attack,
            game.player().defense,
            game.player().gold
        ),
        (12345, 321, 456, 0)
    );
    assert_eq!(
        (
            game.player().keys.yellow,
            game.player().keys.blue,
            game.player().keys.red
        ),
        (0, 0, 0)
    );
    assert_eq!(game.player().inventory, vec!["sword_5", "sacred_shield"]);
    let save: Value = serde_json::from_str(&game.save_json()).unwrap();
    assert_eq!(save["shop_visits"], json!({}));
    assert_eq!(save["event_counts"], json!({}));
    assert_eq!(save["flags"], json!(["backside"]));
    assert_eq!(save["visited_floors"], json!([1]));
    for floor in &game.campaign().floors {
        assert_eq!(save["floors"][floor.id.to_string()], json!(floor.tiles));
    }
    assert!(
        !game.snapshot()["last_action"]["presentation"]
            .as_array()
            .unwrap()
            .iter()
            .any(|event| event["type"] == "battle")
    );
}

#[test]
fn backside_zeno_is_a_normal_fight_and_third_cycle_retains_gold_and_specials() {
    let mut game = original();
    edit(&mut game, |save| {
        save["cycle"] = json!(2);
        place(save, 50, 5, 5);
        save["floors"]["50"][49] = json!(91);
        save["player"]["hp"] = json!(1_000_000);
        save["player"]["attack"] = json!(1_000_000);
        save["player"]["defense"] = json!(1_000_000);
        save["player"]["gold"] = json!(7);
        save["player"]["inventory"] = json!(["hero_orb", "sacred_shield", "warp_staff"]);
        save["player"]["item_charges"] = json!({"warp_staff":2});
    });
    assert_eq!(game.inspect(5, 4)["kind"], "enemy");
    step(&mut game, "up");
    assert_eq!(game.snapshot()["cycle"], 3);
    assert_eq!(game.snapshot()["backside_multiplier"], 44);
    assert_eq!(
        (game.player().floor, game.player().x, game.player().y),
        (1, 5, 10)
    );
    assert_eq!(game.player().gold, 507);
    assert!(game.player().inventory.contains(&"hero_orb".to_owned()));
    assert!(game.player().inventory.contains(&"warp_staff".to_owned()));
    assert_eq!(game.player().item_charges["warp_staff"], 2);
    let snapshot = game.snapshot();
    let battle = snapshot["last_action"]["presentation"]
        .as_array()
        .unwrap()
        .iter()
        .find(|event| event["type"] == "battle")
        .unwrap();
    assert_eq!(battle["enemy_hp"], 44_000);
    assert_eq!(battle["hero_hit"], 994_500);
    assert_eq!(battle["enemy_hit"], 0);
    assert_eq!(game.player().hp, 1_000_000);
    let save = game.save_json();
    let mut restored = original();
    restored.load_json(&save).unwrap();
    assert_eq!(restored.snapshot()["cycle"], 3);
    assert_eq!(restored.player().gold, 507);
}

#[test]
fn backside_potions_gems_and_equipment_use_multiplier_and_original_area() {
    // Keep original tile definitions; put each pickup next to a scenario hero.
    for (floor, tile, hp, attack, defense) in [
        (1, 32, 2200, 0, 0),
        (21, 33, 26400, 0, 0),
        (1, 34, 0, 44, 0),
        (1, 35, 0, 0, 44),
        (1, 51, 0, 440, 0),
        (1, 56, 0, 0, 440),
    ] {
        let mut game = original();
        edit(&mut game, |save| {
            save["cycle"] = json!(2);
            place(save, floor, 0, 0);
            save["floors"][floor.to_string()][0] = json!(6);
            save["floors"][floor.to_string()][1] = json!(tile);
            save["player"]["hp"] = json!(100_000);
            save["player"]["attack"] = json!(500);
            save["player"]["defense"] = json!(500);
        });
        step(&mut game, "right");
        assert_eq!(
            (
                game.player().hp,
                game.player().attack,
                game.player().defense
            ),
            (100_000 + hp, 500 + attack, 500 + defense),
            "floor{floor} tile{tile}"
        );
        assert_eq!(game.tile_at(floor, 1, 0), Some(6));
    }
}

#[test]
fn backside_altar_scales_all_gains_while_preserving_quadratic_price() {
    for (choice, hp, attack, defense) in [
        ("hp", 4400, 0, 0),
        ("attack", 0, 88, 0),
        ("defense", 0, 0, 176),
    ] {
        let mut game = original();
        edit(&mut game, |save| {
            save["cycle"] = json!(2);
            place(save, 4, 5, 1);
            save["player"]["hp"] = json!(1000);
            save["player"]["attack"] = json!(100);
            save["player"]["defense"] = json!(100);
            save["player"]["gold"] = json!(100);
        });
        step(&mut game, "up");
        assert_eq!(
            game.snapshot()["pending_interaction"]["choices"][0]["cost"],
            20
        );
        choose(&mut game, choice);
        assert_eq!(
            (
                game.player().hp,
                game.player().attack,
                game.player().defense
            ),
            (1000 + hp, 100 + attack, 100 + defense)
        );
        assert_eq!(game.player().gold, 80);
        assert_eq!(
            game.snapshot()["pending_interaction"]["choices"][0]["cost"],
            40
        );
    }
}

#[test]
fn backside_magician_hazards_scale_and_sorcerer_pincer_remains_half_current_hp() {
    for (neighbors, expected_hp) in [
        (vec![(0, 1, 151)], 11_200),
        (vec![(0, 1, 153)], 15_600),
        (vec![(0, 1, 93), (2, 1, 93)], 10_000),
    ] {
        let mut game = original();
        edit(&mut game, |save| {
            save["cycle"] = json!(2);
            place(save, 1, 1, 2);
            save["player"]["hp"] = json!(20_000);
            save["player"]["inventory"] = json!([]);
            save["floors"]["1"] = json!(vec![6; 121]);
            for (x, y, tile) in neighbors {
                save["floors"]["1"][y * 11 + x] = json!(tile);
            }
        });
        step(&mut game, "up");
        assert_eq!(game.player().hp, expected_hp);
    }
}

#[test]
fn backside_enemy_gold_and_three_percent_old_man_gift_are_not_scaled() {
    let mut game = original();
    edit(&mut game, |save| {
        save["cycle"] = json!(2);
        place(save, 1, 0, 0);
        save["floors"]["1"][1] = json!(61);
        save["player"]["attack"] = json!(100_000);
        save["player"]["inventory"] = json!(["hero_orb"]);
        save["player"]["gold"] = json!(7);
    });
    assert_eq!(game.inspect(1, 0)["enemy"]["hp"], 1540);
    assert_eq!(game.inspect(1, 0)["enemy"]["attack"], 792);
    assert_eq!(game.inspect(1, 0)["enemy"]["gold"], 1);
    step(&mut game, "right");
    assert_eq!(game.player().gold, 8);
    let npc = game
        .campaign()
        .interactions
        .iter()
        .find(|npc| npc["floor"] == 2 && npc["name"] == "Old man")
        .unwrap()
        .clone();
    let x = npc["x"].as_u64().unwrap() as usize;
    let y = npc["y"].as_u64().unwrap() as usize;
    edit(&mut game, |save| {
        place(save, 2, x, y + 1);
        save["player"]["attack"] = json!(1000);
        save["player"]["defense"] = json!(2000);
    });
    step(&mut game, "up");
    choose(&mut game, "accept");
    assert_eq!((game.player().attack, game.player().defense), (1030, 2060));
}

#[test]
fn backside_zeno_inspection_previews_encounter_stats_without_mutation() {
    let mut game = original();
    edit(&mut game, |save| {
        save["cycle"] = json!(2);
        place(save, 50, 5, 5);
        save["floors"]["50"][49] = json!(91);
        save["player"]["hp"] = json!(100_000);
        save["player"]["attack"] = json!(10_000);
        save["player"]["defense"] = json!(20_000);
        save["player"]["inventory"] = json!(["hero_orb"]);
        save["enemy_overrides"]["zeno"] =
            json!({"name":"Zeno", "hp":800, "attack":500, "defense":100, "gold":500});
    });
    let before = game.save_json();
    let preview = game.inspect(5, 4)["enemy"].clone();
    assert_eq!(
        (
            preview["hp"].as_i64(),
            preview["attack"].as_i64(),
            preview["defense"].as_i64()
        ),
        (Some(44_000), Some(27_500), Some(5_500))
    );
    let snapshot = game.snapshot();
    let listed = snapshot["enemies"]
        .as_array()
        .unwrap()
        .iter()
        .find(|e| e["x"] == 5 && e["y"] == 4)
        .unwrap();
    assert_eq!(listed["damage"], preview["damage"]);
    assert_eq!(game.save_json(), before);
    step(&mut game, "up");
    let action = game.snapshot();
    let battle = action["last_action"]["presentation"]
        .as_array()
        .unwrap()
        .iter()
        .find(|e| e["type"] == "battle")
        .unwrap();
    assert_eq!(battle["enemy_hp"], preview["hp"]);
    assert_eq!(battle["enemy_hit"], json!(7_500));
    // The post-victory replay carries the exact HP left by the forecasted fight.
    assert_eq!(
        game.player().hp,
        100_000 - preview["damage"].as_i64().unwrap()
    );
}

#[test]
fn sealed_zeno_stats_survive_repeated_restores_then_the_portal_restores_the_correct_cycle() {
    for cycle in [2, 3, 4] {
        let mut game = original();
        edit(&mut game, |save| {
            save["cycle"] = json!(cycle);
            place(save, 49, 5, 4);
            save["floors"]["49"][27] = json!(91);
            save["player"]["hp"] = json!(100_000);
            save["player"]["attack"] = json!(if cycle == 2 { 50_000 } else { 500_000 });
            save["player"]["defense"] = json!(if cycle == 2 { 5_000 } else { 500_000 });
            save["player"]["gold"] = json!(7);
            save["player"]["inventory"] = json!(["hero_orb"]);
            save["enemy_overrides"]["zeno"] =
                json!({"name":"Zeno","hp":800,"attack":500,"defense":100,"gold":500});
            save["flags"] = json!(["floor_49_zeno_sealed"]);
        });
        for _ in 0..4 {
            let before = game.save_json();
            let mut restored = original();
            restored.load_json(&before).unwrap();
            assert_eq!(restored.save_json(), before);
            let enemy = &restored.inspect(5, 2)["enemy"];
            assert_eq!(
                (
                    enemy["hp"].as_i64(),
                    enemy["attack"].as_i64(),
                    enemy["defense"].as_i64()
                ),
                (Some(35_200), Some(22_000), Some(4_400))
            );
            game = restored;
        }
        edit(&mut game, |save| {
            place(save, 24, 5, 1);
            save["floors"]["24"][5] = json!(7);
        });
        step(&mut game, "up");
        let snapshot = game.snapshot();
        let timeline = snapshot["last_action"]["presentation"].as_array().unwrap();
        if cycle == 2 {
            let moves: Vec<_> = timeline
                .iter()
                .filter(|cue| cue["type"] == "move_tile")
                .collect();
            assert_eq!(moves.len(), 2);
            assert_eq!(
                (
                    moves[0]["from_y"].as_u64(),
                    moves[0]["y"].as_u64(),
                    moves[1]["y"].as_u64()
                ),
                (Some(4), Some(5), Some(6))
            );
            let battle = timeline.iter().find(|cue| cue["type"] == "battle").unwrap();
            assert_eq!(battle["enemy_first"], true);
            assert_eq!(battle["enemy_hp"], 44_000);
            assert_eq!(battle["enemy_attack"], 27_500);
            assert_eq!(battle["damage"], 22_500);
            assert_eq!(game.player().hp, 77_500);
            assert_eq!(game.player().gold, 507);
            assert_eq!(game.player().floor, 1);
            assert_eq!(snapshot["cycle"], 3);
        } else {
            assert!(
                !timeline
                    .iter()
                    .any(|cue| cue["type"] == "move_tile" || cue["type"] == "battle")
            );
            assert_eq!(game.player().floor, 50);
            let enemy = &game.inspect(5, 4)["enemy"];
            assert_eq!(
                (
                    enemy["hp"].as_i64(),
                    enemy["attack"].as_i64(),
                    enemy["defense"].as_i64()
                ),
                (Some(352_000), Some(220_000), Some(44_000))
            );
            let saved = game.save_json();
            game.load_json(&saved).unwrap();
            assert_eq!(game.inspect(5, 4)["enemy"], *enemy);
            step(&mut game, "up");
            step(&mut game, "up");
            assert_eq!(game.snapshot()["cycle"], cycle + 1);
            assert_eq!(game.player().gold, 507);
        }
    }
}

#[test]
fn visiting_floor50_before_the_floor49_seal_preserves_the_weaker_shared_zeno_row() {
    for cycle in [1, 3, 4] {
        for seal_before_gate in [false, true] {
            let mut game = original();
            edit(&mut game, |save| {
                save["cycle"] = json!(cycle);
                place(save, 49, 5, 4);
                save["player"]["hp"] = json!(1_000_000);
                save["player"]["attack"] = json!(100_000);
                save["player"]["defense"] = json!(500_000);
                save["player"]["inventory"] =
                    json!(["hero_orb", "sacred_shield", "up_wing", "down_wing"]);
                save["floors"]["49"] = json!(vec![6; 121]);
                for index in [15, 17, 37, 39, 38] {
                    save["floors"]["49"][index] = json!(93);
                }
                save["floors"]["49"][27] = json!(91);
                save["floors"]["49"][71] = json!(4);
                // An unrelated fight can recheck the still-valid dice pattern.
                save["floors"]["49"][59] = json!(61);
            });
            if seal_before_gate {
                step(&mut game, "up");
                let saved: Value = serde_json::from_str(&game.save_json()).unwrap();
                assert_eq!(saved["enemy_overrides"]["zeno"]["hp"], 800);
            }
            edit(&mut game, |save| {
                place(save, 24, 5, 1);
                save["floors"]["24"][5] = json!(7);
            });
            step(&mut game, "up");
            assert_eq!(game.player().floor, 50);
            let factor = if cycle == 1 { 1 } else { 44 };
            let saved: Value = serde_json::from_str(&game.save_json()).unwrap();
            if cycle == 1 {
                assert_eq!(
                    saved["enemy_overrides"]["zeno"]["hp"]
                        .as_i64()
                        .unwrap_or(game.campaign().enemies["zeno"].hp),
                    8000
                );
            } else {
                assert_eq!(game.inspect(5, 4)["enemy"]["hp"], 8000 * factor);
            }
            assert!(
                !saved["flags"]
                    .as_array()
                    .unwrap()
                    .contains(&json!("floor_49_zeno_sealed"))
            );
            // Use the actual wings to return, leaving 49F Zeno alive.
            // The scenario gate lands at (5,6); (5,5) is road on both floors.
            step(&mut game, "up");
            assert_eq!((game.player().x, game.player().y), (5, 5));
            game.command(json!({"type":"use_item","item":"down_wing"}))
                .unwrap();
            assert_eq!(game.player().floor, 49);
            if seal_before_gate {
                step(&mut game, "left");
            } else {
                step(&mut game, "up");
                step(&mut game, "up");
            }
            let saved: Value = serde_json::from_str(&game.save_json()).unwrap();
            assert_eq!(saved["enemy_overrides"]["zeno"]["hp"], 800);
            assert_eq!(
                saved["event_counts"]["floor_49_dice_seal"],
                if seal_before_gate { 2 } else { 1 }
            );
            assert!(
                saved["flags"]
                    .as_array()
                    .unwrap()
                    .contains(&json!("floor_49_zeno_sealed"))
            );
            assert_eq!(game.tile_at(49, 5, 2), Some(91));
            if !seal_before_gate {
                step(&mut game, "down");
                step(&mut game, "down"); // (5,5), road inside the 50F room
            }
            game.command(json!({"type":"use_item","item":"up_wing"}))
                .unwrap();
            assert_eq!(game.player().floor, 50);
            // Save/restore and inspection must not undo or reapply the seal.
            let before = game.save_json();
            let mut restored = original();
            restored.load_json(&before).unwrap();
            game = restored;
            let preview = game.inspect(5, 4)["enemy"].clone();
            if cycle == 1 {
                assert!(preview.is_null());
            } else {
                assert_eq!(
                    (
                        preview["hp"].as_i64(),
                        preview["attack"].as_i64(),
                        preview["defense"].as_i64()
                    ),
                    (Some(800 * factor), Some(500 * factor), Some(100 * factor))
                );
            }
            assert_eq!(game.save_json(), before);
            if seal_before_gate {
                step(&mut game, "up"); // (4,4)
                step(&mut game, "right");
            } else {
                step(&mut game, "up");
            }
            let state = game.snapshot();
            let battle = state["last_action"]["presentation"]
                .as_array()
                .unwrap()
                .iter()
                .find(|e| e["type"] == "battle");
            if cycle == 1 {
                assert!(
                    battle.is_none(),
                    "Original first ending does not fight Zeno"
                );
            } else {
                assert_eq!(battle.unwrap()["enemy_hp"], 800 * factor);
            }
            assert_eq!(state["cycle"], cycle + 1);
        }
    }
}

#[test]
fn defeating_the_49f_decoy_after_the_gate_reseals_zeno_before_clearing_the_corners() {
    for cycle in [1, 3, 4] {
        let mut game = original();
        edit(&mut game, |save| {
            save["cycle"] = json!(cycle);
            place(save, 49, 5, 4);
            save["player"]["hp"] = json!(1_000_000);
            save["player"]["attack"] = json!(100_000);
            save["player"]["defense"] = json!(500_000);
            save["player"]["inventory"] =
                json!(["hero_orb", "sacred_shield", "up_wing", "down_wing"]);
            for index in [16, 26, 28, 49, 60] {
                save["floors"]["49"][index] = json!(6);
            }
            for index in [15, 17, 37, 39, 38] {
                save["floors"]["49"][index] = json!(93);
            }
            save["floors"]["49"][27] = json!(91);
            save["floors"]["49"][71] = json!(4);
        });
        step(&mut game, "up"); // Last edge kill seals the live decoy.
        assert_eq!(
            game.inspect(5, 2)["enemy"]["hp"],
            if cycle == 1 { 800 } else { 35200 }
        );
        edit(&mut game, |save| {
            place(save, 24, 5, 1);
            save["floors"]["24"][5] = json!(7);
        });
        step(&mut game, "up"); // Gate reverses the seal and reveals F50 Zeno.
        assert_eq!(game.player().floor, 50);
        step(&mut game, "up"); // (5,5), road on both floors.
        game.command(json!({"type":"use_item","item":"down_wing"}))
            .unwrap();
        assert_eq!(game.player().floor, 49);
        step(&mut game, "up");
        step(&mut game, "up");
        step(&mut game, "up"); // Defeat the now-full decoy at (5,2).
        let action = game.snapshot();
        let timeline = action["last_action"]["presentation"].as_array().unwrap();
        let battle = timeline.iter().find(|fx| fx["type"] == "battle").unwrap();
        assert_eq!(battle["enemy_hp"], if cycle == 1 { 8000 } else { 352000 });
        let saved: Value = serde_json::from_str(&game.save_json()).unwrap();
        assert_eq!(saved["enemy_overrides"]["zeno"]["hp"], 800);
        assert_eq!(saved["enemy_overrides"]["zeno"]["attack"], 500);
        assert_eq!(saved["enemy_overrides"]["zeno"]["defense"], 100);
        assert!(
            saved["flags"]
                .as_array()
                .unwrap()
                .contains(&json!("floor_49_zeno_sealed"))
        );
        assert_eq!(saved["event_counts"]["floor_49_dice_seal"], 2);
        assert_eq!(saved["event_counts"]["floor_49_decoy_zeno_defeated"], 1);
        assert!(
            !timeline.iter().any(|fx| fx["dialogue_id"] == 45),
            "Original reward builder overwrites the otherwise queued seal speech"
        );
        assert_eq!(game.tile_at(49, 5, 2), Some(6));
        assert_eq!(game.tile_at(49, 5, 1), Some(23));
        for index in [37, 39] {
            assert_eq!(game.tile_at(49, index % 11, index / 11), Some(6));
        }
        for _ in 0..3 {
            step(&mut game, "down");
        }
        game.command(json!({"type":"use_item","item":"up_wing"}))
            .unwrap();
        assert_eq!(game.player().floor, 50);
        let saved = game.save_json();
        game.load_json(&saved).unwrap();
        if cycle > 1 {
            assert_eq!(game.inspect(5, 4)["enemy"]["hp"], 35200);
        }
        step(&mut game, "up");
        let action = game.snapshot();
        let battle = action["last_action"]["presentation"]
            .as_array()
            .unwrap()
            .iter()
            .find(|fx| fx["type"] == "battle");
        if cycle == 1 {
            assert!(battle.is_none());
        } else {
            assert_eq!(battle.unwrap()["enemy_hp"], 35200);
        }
        assert_eq!(action["cycle"], cycle + 1);
    }
}

#[test]
fn second_cycle_zeno_ambush_can_be_lethal_before_the_replay_rewards() {
    let mut game = original();
    edit(&mut game, |save| {
        save["cycle"] = json!(2);
        place(save, 24, 5, 1);
        save["floors"]["24"][5] = json!(7);
        save["player"]["hp"] = json!(22_500);
        save["player"]["attack"] = json!(50_000);
        save["player"]["defense"] = json!(5_000);
        save["player"]["gold"] = json!(7);
    });
    step(&mut game, "up");
    assert_eq!(game.snapshot()["status"], "lost");
    assert_eq!(game.snapshot()["cycle"], 2);
    assert_eq!(game.player().hp, 0);
    assert_eq!(game.player().gold, 7);
    assert_eq!(game.tile_at(50, 5, 6), Some(91));
}

#[test]
fn floor_45_merchant_preserves_the_original_unscaled_trade() {
    for cycle in [1, 2, 3] {
        let mut game = original();
        let merchant = game
            .campaign()
            .interactions
            .iter()
            .find(|npc| npc["floor"] == 45 && npc["name"] == "Merchant")
            .unwrap()
            .clone();
        let x = merchant["x"].as_u64().unwrap() as usize;
        let y = merchant["y"].as_u64().unwrap() as usize;
        edit(&mut game, |save| {
            save["cycle"] = json!(cycle);
            place(save, 45, x, y + 1);
            save["player"]["hp"] = json!(1000);
            save["player"]["gold"] = json!(2000);
        });
        step(&mut game, "up");
        let snapshot = game.snapshot();
        let offer = snapshot["pending_interaction"]["choices"][0]["id"]
            .as_str()
            .unwrap();
        choose(&mut game, offer);
        assert_eq!(game.player().hp, 3000);
        assert_eq!(game.player().gold, 1000);
        choose(&mut game, offer);
        assert_eq!(game.player().hp, 3000);
        assert_eq!(game.player().gold, 1000);
    }
}
