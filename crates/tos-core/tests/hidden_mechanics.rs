//! Original Windows branch scenarios. Edited saves isolate the original map
//! and callbacks; they do not constitute a natural full-tower playthrough.
use serde_json::{Value, json};
use tos_core::Engine;

fn original() -> Engine {
    Engine::from_json(include_str!("../../../data/campaign.json")).unwrap()
}

fn edit(game: &mut Engine, update: impl FnOnce(&mut Value)) {
    let mut save: Value = serde_json::from_str(&game.save_json()).unwrap();
    update(&mut save);
    game.load_json(&save.to_string()).unwrap();
}

fn place(game: &mut Engine, floor: i32, x: usize, y: usize) {
    edit(game, |save| {
        save["player"]["floor"] = json!(floor);
        save["player"]["x"] = json!(x);
        save["player"]["y"] = json!(y);
        save["pending_interaction"] = Value::Null;
        save["pending_tile"] = Value::Null;
    });
}

fn command(game: &mut Engine, command: Value) {
    game.command(command).unwrap();
}

fn step(game: &mut Engine, direction: &str) {
    command(game, json!({"type":"move","direction":direction}));
}

fn continue_dialogue(game: &mut Engine) {
    command(game, json!({"type":"choose","choice":"leave"}));
}

fn restore(game: &mut Engine) {
    let save = game.save_json();
    *game = original();
    game.load_json(&save).unwrap();
    assert_eq!(game.save_json(), save);
}

fn dialogue(id: usize) -> String {
    let dialogues: Value =
        serde_json::from_str(include_str!("../../../data/original-dialogue.json")).unwrap();
    dialogues[id]["text"].as_str().unwrap().to_owned()
}

fn speech(game: &Engine, id: usize) {
    assert_eq!(game.snapshot()["pending_interaction"]["text"], dialogue(id));
}

#[test]
fn prison_thief_has_two_conversations_and_all_five_departure_moves() {
    let mut game = original();
    place(&mut game, 2, 2, 7);
    step(&mut game, "up");
    speech(&game, 3);
    restore(&mut game); // Continue must still run the pending original callback.
    continue_dialogue(&mut game);
    assert_eq!(game.tile_at(2, 1, 6), Some(6));
    assert_eq!(game.tile_at(2, 2, 6), Some(6));
    assert_eq!(game.tile_at(2, 0, 7), Some(21));
    let state = game.snapshot();
    let moves: Vec<_> = state["last_action"]["presentation"]
        .as_array()
        .unwrap()
        .iter()
        .filter(|e| e["type"] == "move_tile")
        .collect();
    assert_eq!(moves.len(), 3);
    for (movement, (from_x, from_y, x, y)) in
        moves.iter().zip([(2, 6, 1, 6), (1, 6, 0, 6), (0, 6, 0, 7)])
    {
        assert_eq!(movement["tile"], 21);
        assert_eq!(movement["from_x"], from_x);
        assert_eq!(movement["from_y"], from_y);
        assert_eq!(movement["x"], x);
        assert_eq!(movement["y"], y);
    }
    place(&mut game, 2, 0, 6);
    step(&mut game, "down");
    assert_eq!(
        game.snapshot()["pending_interaction"]["text"],
        format!("{} {}", dialogue(4), dialogue(57))
    );
    restore(&mut game);
    continue_dialogue(&mut game);
    for y in [7, 8, 9] {
        assert_eq!(game.tile_at(2, 0, y), Some(6));
    }
    assert_eq!(
        game.snapshot()["last_action"]["presentation"]
            .as_array()
            .unwrap()
            .iter()
            .filter(|e| e["type"] == "move_tile")
            .count(),
        2
    );
    let save: Value = serde_json::from_str(&game.save_json()).unwrap();
    assert_eq!(save["event_counts"]["thief_opens_prison_tunnel"], 1);
    assert_eq!(save["event_counts"]["thief_leaves_prison"], 1);
}

#[test]
fn returned_thief_opens_dragon_bypass_on_continue_and_has_persistent_repeat_speeches() {
    let mut game = original();
    // The separately tested 32F Knight retreat returns him to this square.
    edit(&mut game, |save| save["floors"]["2"][120] = json!(21));
    place(&mut game, 2, 9, 10);
    step(&mut game, "right");
    speech(&game, 5);
    assert_eq!(game.tile_at(35, 3, 8), Some(8));
    restore(&mut game);
    continue_dialogue(&mut game);
    assert_eq!(game.tile_at(35, 3, 8), Some(6));
    assert_eq!(game.tile_at(35, 4, 9), Some(21));
    assert_eq!(game.tile_at(2, 10, 10), Some(21));
    restore(&mut game);
    step(&mut game, "right");
    speech(&game, 6);
    continue_dialogue(&mut game);
    assert_eq!(game.snapshot()["last_action"]["presentation"], json!([]));
    place(&mut game, 35, 5, 9);
    step(&mut game, "left");
    speech(&game, 31);
    continue_dialogue(&mut game);
    assert_eq!(game.tile_at(2, 10, 10), Some(6));
    restore(&mut game);
    step(&mut game, "left");
    speech(&game, 32);
    continue_dialogue(&mut game);
    assert_eq!(game.tile_at(35, 4, 9), Some(21));
    let save: Value = serde_json::from_str(&game.save_json()).unwrap();
    assert_eq!(save["event_counts"]["thief_opens_floor_35_tunnel"], 1);
}

#[test]
fn floor_29_thief_finishes_without_completing_floor_23_walls() {
    let mut game = original();
    let original_23 = game
        .campaign()
        .floors
        .iter()
        .find(|f| f.id == 23)
        .unwrap()
        .tiles
        .clone();
    place(&mut game, 29, 5, 2);
    step(&mut game, "down");
    speech(&game, 26);
    continue_dialogue(&mut game);
    assert_eq!(game.tile_at(29, 5, 3), Some(21));
    edit(&mut game, |save| save["highest_stair_floor"] = json!(29));
    place(&mut game, 29, 1, 10);
    step(&mut game, "left"); // The real down stair starts tunnel completion.
    assert_eq!(game.player().floor, 28);
    assert_eq!(game.tile_at(29, 5, 2), Some(6));
    assert_eq!(game.tile_at(29, 5, 3), Some(6));
    assert_eq!(game.tile_at(29, 6, 1), Some(21));
    place(&mut game, 29, 5, 1);
    step(&mut game, "right");
    speech(&game, 27);
    continue_dialogue(&mut game);
    restore(&mut game);
    step(&mut game, "right");
    speech(&game, 28);
    continue_dialogue(&mut game);
    let save: Value = serde_json::from_str(&game.save_json()).unwrap();
    assert_eq!(save["floors"]["23"], json!(original_23));
}

#[test]
fn floor_40_respawns_precleared_troops_and_fights_all_thirteen_waves() {
    for precleared in [1, 12] {
        let mut game = original();
        let troops: Vec<_> = game
            .campaign()
            .floors
            .iter()
            .find(|f| f.id == 40)
            .unwrap()
            .tiles
            .iter()
            .enumerate()
            .filter(|(i, t)| **t >= 135 && **t <= 141 && i / 11 <= 3)
            .map(|(i, _)| i)
            .collect();
        assert_eq!(troops.len(), 12);
        edit(&mut game, |save| {
            for index in troops.iter().take(precleared) {
                save["floors"]["40"][*index] = json!(6);
            }
            save["player"]["hp"] = json!(10000);
            save["player"]["attack"] = json!(300);
            save["player"]["defense"] = json!(100);
            save["player"]["gold"] = json!(0);
            save["player"]["inventory"] = json!([]);
        });
        restore(&mut game);
        place(&mut game, 40, 5, 7);
        step(&mut game, "up");
        assert_eq!((game.player().hp, game.player().gold), (7280, 700));
        let state = game.snapshot();
        let battles: Vec<_> = state["last_action"]["presentation"]
            .as_array()
            .unwrap()
            .iter()
            .filter(|e| e["type"] == "battle")
            .collect();
        assert_eq!(battles.len(), 13);
        assert!(battles.iter().all(|e| e["enemy_first"] == true));
        assert_eq!(game.tile_at(40, 5, 0), Some(11));
        assert_eq!(game.tile_at(40, 5, 5), Some(23));
    }
}

#[test]
fn floor_49_edge_battles_apply_four_pincers_unless_sacred_shield_was_obtained() {
    for protected in [false, true] {
        let mut game = original();
        edit(&mut game, |save| {
            save["player"]["hp"] = json!(10001);
            save["player"]["attack"] = json!(10000);
            save["player"]["defense"] = json!(10000);
            save["player"]["inventory"] = if protected {
                json!(["sacred_shield", "shield_1"])
            } else {
                json!([])
            };
        });
        place(&mut game, 49, 5, 4);
        step(&mut game, "down");
        assert_eq!(game.player().hp, 10001);
        for (number, (x, y)) in [(5, 1), (4, 2), (6, 2), (5, 3)].into_iter().enumerate() {
            place(&mut game, 49, x, y + 1);
            step(&mut game, "up");
            assert_eq!(
                game.player().hp,
                if protected {
                    10001
                } else {
                    10001 >> (number + 1)
                }
            );
            restore(&mut game);
        }
        for (x, y) in [(4, 1), (6, 1), (4, 3), (6, 3)] {
            assert_eq!(game.tile_at(49, x, y), Some(93));
        }
        let save: Value = serde_json::from_str(&game.save_json()).unwrap();
        assert_eq!(save["enemy_overrides"]["zeno"]["hp"], 800);
    }
}

#[test]
fn princess_speaks_before_boss_victory_but_only_opens_portal_after_it() {
    let mut game = original();
    place(&mut game, 26, 5, 6);
    step(&mut game, "up");
    speech(&game, 24);
    continue_dialogue(&mut game);
    assert_eq!(game.tile_at(24, 5, 0), Some(6));
    assert_eq!(game.tile_at(50, 5, 4), Some(21));
    assert!(
        game.snapshot()["last_action"]["presentation"]
            .as_array()
            .unwrap()
            .iter()
            .any(|e| e["dialogue_id"] == 25 && e["text"] == dialogue(25))
    );
    restore(&mut game);
    edit(&mut game, |save| save["floors"]["25"][60] = json!(6));
    step(&mut game, "up");
    speech(&game, 24);
    continue_dialogue(&mut game);
    assert_eq!(game.tile_at(24, 5, 0), Some(7));
    assert_eq!(game.tile_at(24, 5, 1), Some(6));
    assert_eq!(game.tile_at(50, 4, 8), Some(14));
}

#[test]
fn floor_36_all_four_hidden_passages_are_walkable_and_persist() {
    let mut game = original();
    // Five connected cells per corner passage, rather than four single holes.
    let passages = [
        [
            (3, 1, "down"),
            (3, 2, "down"),
            (3, 3, "left"),
            (2, 3, "left"),
            (1, 3, "up"),
        ],
        [
            (7, 1, "down"),
            (7, 2, "down"),
            (7, 3, "right"),
            (8, 3, "right"),
            (9, 3, "up"),
        ],
        [
            (1, 7, "right"),
            (2, 7, "right"),
            (3, 7, "down"),
            (3, 8, "down"),
            (3, 9, "left"),
        ],
        [
            (9, 7, "left"),
            (8, 7, "left"),
            (7, 7, "down"),
            (7, 8, "down"),
            (7, 9, "right"),
        ],
    ];
    for path in passages {
        for (x, y, direction) in path {
            assert_eq!(game.tile_at(36, x, y), Some(9));
            let (from_x, from_y) = match direction {
                "up" => (x, y + 1),
                "down" => (x, y - 1),
                "left" => (x + 1, y),
                "right" => (x - 1, y),
                _ => unreachable!(),
            };
            place(&mut game, 36, from_x, from_y);
            step(&mut game, direction);
            assert_eq!((game.player().x, game.player().y), (x, y));
            assert_eq!(game.tile_at(36, x, y), Some(6));
        }
        restore(&mut game);
    }
}

#[test]
fn floor_48_hidden_sorcerer_must_die_before_the_sacred_sword_gate_opens() {
    let mut game = original();
    edit(&mut game, |save| {
        save["player"]["attack"] = json!(10000);
        save["player"]["defense"] = json!(10000);
        save["player"]["inventory"] = json!([]);
    });
    place(&mut game, 48, 0, 1);
    assert_eq!(game.tile_at(48, 0, 0), Some(7));
    assert_eq!(game.tile_at(48, 7, 7), Some(4));
    step(&mut game, "up");
    assert_eq!(game.tile_at(48, 0, 0), Some(93));
    assert_eq!(game.tile_at(48, 7, 7), Some(4));
    restore(&mut game);
    step(&mut game, "down");
    step(&mut game, "up");
    assert_eq!(game.tile_at(48, 0, 0), Some(6));
    assert_eq!(game.tile_at(48, 7, 7), Some(6));
}

#[test]
fn octopus_approach_closes_retreat_and_nine_victories_award_five_hundred_gold() {
    let mut game = original();
    edit(&mut game, |save| {
        save["player"]["attack"] = json!(10000);
        save["player"]["defense"] = json!(10000);
        save["player"]["gold"] = json!(0);
        save["player"]["inventory"] = json!([]);
    });
    place(&mut game, 15, 5, 8);
    step(&mut game, "up");
    assert_eq!(game.tile_at(15, 5, 8), Some(4));
    // Leave the bottom-center mouth (104) until all eight parts are defeated.
    for tile in (97..=105).filter(|tile| *tile != 104).chain([104]) {
        let index = tile - 97;
        let (x, y) = (4 + index % 3, 3 + index / 3);
        place(&mut game, 15, x, y + 1);
        step(&mut game, "up");
        restore(&mut game);
    }
    assert_eq!(game.player().gold, 500);
    assert_eq!(game.tile_at(15, 5, 8), Some(6));
    assert_eq!(game.tile_at(15, 5, 4), Some(41));
    step(&mut game, "up");
    assert!(game.player().inventory.contains(&"mattock".to_owned()));
    for y in 3..=5 {
        for x in 4..=6 {
            assert_eq!(game.tile_at(15, x, y), Some(6));
        }
    }
}

#[test]
fn great_magic_master_drops_five_red_keys_for_the_four_original_princess_doors() {
    let mut game = original();
    assert_eq!(
        game.campaign()
            .floors
            .iter()
            .find(|f| f.id == 26)
            .unwrap()
            .tiles
            .iter()
            .filter(|t| **t == 3)
            .count(),
        4
    );
    edit(&mut game, |save| {
        save["player"]["attack"] = json!(10000);
        save["player"]["defense"] = json!(10000);
        save["player"]["keys"]["red"] = json!(0);
    });
    place(&mut game, 25, 5, 9);
    step(&mut game, "up");
    place(&mut game, 25, 5, 6);
    step(&mut game, "up");
    assert_eq!(game.tile_at(25, 5, 5), Some(6));
    let keys: Vec<_> = (0..121)
        .filter(|i| game.tile_at(25, i % 11, i / 11) == Some(30))
        .collect();
    assert_eq!(keys.len(), 5);
    for index in keys {
        place(&mut game, 25, index % 11, index / 11 + 1);
        step(&mut game, "up");
    }
    assert_eq!(game.player().keys.red, 5);
    restore(&mut game);
    for y in (6..=9).rev() {
        place(&mut game, 26, 5, y + 1);
        step(&mut game, "up");
    }
    assert_eq!(game.player().keys.red, 1);
}
