//! Tests against the imported campaign, rather than a simplified fixture.
//! Scenario saves place the hero near late-game events without claiming an
//! independently validated, unassisted playthrough of the entire tower.
use serde_json::{Value, json};
use std::collections::{BTreeMap, VecDeque};
use tos_core::Engine;

fn original() -> Engine {
    Engine::from_json(include_str!("../../../data/campaign.json")).unwrap()
}

fn command(engine: &mut Engine, command: Value) {
    engine.command(command).unwrap();
}

fn step(engine: &mut Engine, direction: &str) {
    command(engine, json!({"type":"move","direction":direction}));
}

fn edit_save(engine: &mut Engine, edit: impl FnOnce(&mut Value)) {
    let mut save: Value = serde_json::from_str(&engine.save_json()).unwrap();
    edit(&mut save);
    // Keep the engine-created campaign fingerprint and all other session data.
    engine.load_json(&save.to_string()).unwrap();
}

fn place(engine: &mut Engine, floor: i32, x: usize, y: usize) {
    edit_save(engine, |save| {
        save["player"]["floor"] = json!(floor);
        save["player"]["x"] = json!(x);
        save["player"]["y"] = json!(y);
        save["pending_interaction"] = Value::Null;
        save["pending_tile"] = Value::Null;
    });
}

/// Find a short route over the actual imported map. Stairs and conversations
/// are excluded as intermediate nodes because they interrupt ordinary walking.
fn walk_to(engine: &mut Engine, target: (usize, usize)) {
    let start = (engine.player().x, engine.player().y);
    let floor = engine.player().floor;
    let mut previous = BTreeMap::from([(start, (start, ""))]);
    let mut queue = VecDeque::from([start]);
    while let Some((x, y)) = queue.pop_front() {
        if (x, y) == target {
            break;
        }
        for (direction, dx, dy) in [
            ("up", 0, -1),
            ("right", 1, 0),
            ("down", 0, 1),
            ("left", -1, 0),
        ] {
            let (Some(nx), Some(ny)) = (x.checked_add_signed(dx), y.checked_add_signed(dy)) else {
                continue;
            };
            let Some(tile) = engine.tile_at(floor, nx, ny) else {
                continue;
            };
            let definition = &engine.campaign().tiles[&tile.to_string()];
            let traversable = match definition.kind.as_str() {
                "floor" | "empty" | "key" | "potion" | "gem" | "item" | "equipment" | "trigger" => {
                    true
                }
                // The test route oracle uses source data. Player-facing inspection is
                // intentionally unavailable before the old man's Hero Orb reward.
                "enemy" => definition
                    .enemy
                    .as_ref()
                    .and_then(|id| engine.campaign().enemies.get(id))
                    .is_some_and(|enemy| tos_core::forecast(engine.player(), enemy).can_win),
                "door" => match definition.key.map(|key| key.as_str()) {
                    Some("yellow") => engine.player().keys.yellow > 0,
                    Some("blue") => engine.player().keys.blue > 0,
                    Some("red") => engine.player().keys.red > 0,
                    _ => false,
                },
                "stairs_up" | "stairs_down" => (nx, ny) == target,
                _ => false,
            };
            if traversable && !previous.contains_key(&(nx, ny)) {
                previous.insert((nx, ny), ((x, y), direction));
                queue.push_back((nx, ny));
            }
        }
    }
    assert!(
        previous.contains_key(&target),
        "No route on floor {floor} to {target:?}"
    );
    let mut cursor = target;
    let mut route = Vec::new();
    while cursor != start {
        let (parent, direction) = previous[&cursor];
        route.push(direction);
        cursor = parent;
    }
    for direction in route.into_iter().rev() {
        step(engine, direction);
        assert_eq!(engine.snapshot()["status"], "playing");
    }
}

fn has_choice(engine: &Engine, id: &str) -> bool {
    engine.snapshot()["pending_interaction"]["choices"]
        .as_array()
        .is_some_and(|choices| choices.iter().any(|choice| choice["id"] == id))
}

#[test]
fn original_opening_reaches_capture_and_escapes_through_played_moves() {
    let mut game = original();
    assert_eq!(
        (game.player().floor, game.player().x, game.player().y),
        (1, 5, 10)
    );
    assert!(game.player().inventory.contains(&"sword_5".to_owned()));

    // Take the nearby yellow key, open the central door, and climb naturally.
    walk_to(&mut game, (4, 9));
    assert_eq!(game.player().keys.yellow, 1);
    walk_to(&mut game, (0, 0));
    assert_eq!(
        (game.player().floor, game.player().x, game.player().y),
        (2, 0, 1)
    );
    assert_eq!(game.player().keys.yellow, 0);
    walk_to(&mut game, (0, 10));
    assert_eq!(
        (game.player().floor, game.player().x, game.player().y),
        (3, 1, 10)
    );
    walk_to(&mut game, (4, 8));

    assert_eq!(
        (game.player().floor, game.player().x, game.player().y),
        (2, 2, 7)
    );
    assert_eq!(
        (
            game.player().hp,
            game.player().attack,
            game.player().defense
        ),
        (400, 10, 10)
    );
    assert!(!game.player().inventory.contains(&"sword_5".to_owned()));
    assert!(
        !game
            .player()
            .inventory
            .contains(&"sacred_shield".to_owned())
    );
    assert!(
        game.snapshot()["flags"]
            .as_array()
            .unwrap()
            .contains(&json!("captured"))
    );

    step(&mut game, "up");
    assert!(has_choice(&game, "leave"));
    command(&mut game, json!({"type":"choose","choice":"leave"}));
    assert_eq!(game.tile_at(2, 1, 6), Some(6));
    assert_eq!(game.tile_at(2, 2, 6), Some(6));
    step(&mut game, "up");
    step(&mut game, "left");
    step(&mut game, "left");
    assert_eq!((game.player().x, game.player().y), (0, 6));
    assert_eq!(game.player().hp, 400);
}

#[test]
fn original_key_sale_is_repeatable_and_gratitude_gift_is_once_only() {
    let mut game = original();
    place(&mut game, 28, 7, 4);
    edit_save(&mut game, |save| {
        save["player"]["keys"]["yellow"] = json!(2);
        save["player"]["gold"] = json!(0);
    });
    step(&mut game, "up");
    for gold in [100, 200] {
        assert!(has_choice(&game, "trade"));
        command(&mut game, json!({"type":"choose","choice":"trade"}));
        assert_eq!(game.player().gold, gold);
    }
    assert_eq!(game.player().keys.yellow, 0);
    assert!(!has_choice(&game, "trade"));
    command(&mut game, json!({"type":"choose","choice":"trade"}));
    assert_eq!(game.player().gold, 200);
    assert_eq!(game.player().keys.yellow, 0);

    place(&mut game, 2, 9, 6);
    step(&mut game, "right");
    command(&mut game, json!({"type":"choose","choice":"accept"}));
    assert_eq!((game.player().attack, game.player().defense), (103, 103));
    assert_eq!(game.tile_at(2, 10, 6), Some(25));
    assert!(!has_choice(&game, "accept"));
    // A direct command cannot bypass the absence of an already-used choice.
    command(&mut game, json!({"type":"choose","choice":"accept"}));
    assert_eq!((game.player().attack, game.player().defense), (103, 103));

    let mut restored = original();
    restored.load_json(&game.save_json()).unwrap();
    assert_eq!(restored.save_json(), game.save_json());
    assert!(!has_choice(&restored, "accept"));
}

#[test]
fn both_original_prison_guards_are_required_to_open_all_six_bars() {
    let mut game = original();
    edit_save(&mut game, |save| {
        save["player"]["attack"] = json!(200);
        save["player"]["defense"] = json!(200);
    });
    place(&mut game, 2, 4, 1);
    step(&mut game, "right");
    assert_eq!(game.tile_at(2, 5, 1), Some(6));
    assert_eq!(game.tile_at(2, 4, 4), Some(5));
    step(&mut game, "right");
    step(&mut game, "right");
    assert_eq!(game.tile_at(2, 7, 1), Some(6));
    for y in [4, 7, 10] {
        for x in [4, 8] {
            assert_eq!(game.tile_at(2, x, y), Some(6));
        }
    }
}

#[test]
fn original_stairs_skip_hidden_floor_44_in_both_directions() {
    let mut game = original();
    place(&mut game, 43, 0, 9);
    step(&mut game, "down");
    assert_eq!(
        (game.player().floor, game.player().x, game.player().y),
        (45, 1, 0)
    );
    step(&mut game, "left");
    assert_eq!(
        (game.player().floor, game.player().x, game.player().y),
        (43, 0, 9)
    );
    assert!(
        !game.snapshot()["visited_floors"]
            .as_array()
            .unwrap()
            .contains(&json!(44))
    );
}

#[test]
fn original_three_oclock_door_pattern_reveals_the_warp_staff() {
    let mut game = original();
    edit_save(&mut game, |save| {
        save["player"]["keys"]["yellow"] = json!(2)
    });
    place(&mut game, 39, 4, 1);
    step(&mut game, "left");
    assert_eq!(game.tile_at(39, 3, 3), Some(1));
    place(&mut game, 39, 4, 3);
    step(&mut game, "right");
    assert_eq!(game.tile_at(39, 3, 3), Some(43));
    assert_eq!(game.player().keys.yellow, 0);
}

#[test]
fn original_fairy_acknowledgement_clears_spawned_npc_without_changing_stats() {
    let mut game = original();
    place(&mut game, 10, 5, 3);
    edit_save(&mut game, |save| save["floors"]["10"][27] = json!(23));
    let stats = (
        game.player().hp,
        game.player().attack,
        game.player().defense,
    );
    step(&mut game, "up");
    assert!(has_choice(&game, "leave"));
    command(&mut game, json!({"type":"choose","choice":"leave"}));
    assert_eq!(game.tile_at(10, 5, 2), Some(6));
    assert_eq!(
        (
            game.player().hp,
            game.player().attack,
            game.player().defense
        ),
        stats
    );
}

#[test]
fn original_hidden_old_man_reveals_and_grants_one_elixir() {
    let mut game = original();
    place(&mut game, 16, 9, 10);
    assert_eq!(game.tile_at(16, 10, 10), Some(10));
    step(&mut game, "right");
    assert_eq!(game.tile_at(16, 10, 10), Some(25));
    assert!(has_choice(&game, "accept"));
    command(&mut game, json!({"type":"choose","choice":"accept"}));
    assert!(game.player().inventory.contains(&"elixir".to_owned()));
    assert!(!has_choice(&game, "accept"));
    command(&mut game, json!({"type":"choose","choice":"leave"}));
    command(&mut game, json!({"type":"use_item","item":"elixir"}));
    assert_eq!(game.player().hp, 2500);
    step(&mut game, "right");
    assert!(!has_choice(&game, "accept"));
    assert!(!game.player().inventory.contains(&"elixir".to_owned()));
}

#[test]
fn original_hidden_key_merchant_reveals_and_sells_repeatedly() {
    let mut game = original();
    place(&mut game, 12, 9, 0);
    edit_save(&mut game, |save| save["player"]["gold"] = json!(2000));
    assert_eq!(game.tile_at(12, 10, 0), Some(10));
    step(&mut game, "right");
    assert_eq!(game.tile_at(12, 10, 0), Some(19));
    for keys in [1, 2] {
        assert!(has_choice(&game, "trade"));
        command(&mut game, json!({"type":"choose","choice":"trade"}));
        assert_eq!(game.player().keys.yellow, keys);
    }
    assert_eq!(game.player().gold, 0);
    command(&mut game, json!({"type":"choose","choice":"trade"}));
    assert_eq!(game.player().keys.yellow, 2);
}

#[test]
fn original_dragon_battle_clears_its_body_and_reveals_the_snow_crystal() {
    let mut game = original();
    place(&mut game, 35, 5, 9);
    edit_save(&mut game, |save| {
        save["player"]["attack"] = json!(1000);
        save["player"]["defense"] = json!(1000);
    });
    // Attack the actual encounter tile from the ordinary southern passage.
    walk_to(&mut game, (5, 6));
    for y in 4..=6 {
        for x in 4..=6 {
            let expected = match (x, y) {
                (_, 4) => 33, // The original victory event spawns potions.
                (5, 5) => 47, // Snow Crystal reward.
                _ => 6,
            };
            assert_eq!(
                game.tile_at(35, x, y),
                Some(expected),
                "Dragon cell ({x},{y})"
            );
        }
    }
    assert_eq!(game.tile_at(35, 5, 2), Some(6));
    step(&mut game, "up");
    assert!(game.player().inventory.contains(&"snow_crystal".to_owned()));
}
