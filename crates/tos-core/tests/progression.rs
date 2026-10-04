//! Original campaign transition scenarios with explicit expected outcomes.
//! Saves position/strengthen the hero to isolate events; these are not a claim
//! of a natural, unassisted full-tower route. Original addresses are documented
//! in docs/mechanics.md and in each event's data provenance.
use serde_json::{Value, json};
use tos_core::Engine;

fn original() -> Engine {
    Engine::from_json(include_str!("../../../data/campaign.json")).unwrap()
}

fn edit_save(game: &mut Engine, edit: impl FnOnce(&mut Value)) {
    let mut save: Value = serde_json::from_str(&game.save_json()).unwrap();
    edit(&mut save);
    game.load_json(&save.to_string()).unwrap();
}

fn place(game: &mut Engine, floor: i32, x: usize, y: usize) {
    edit_save(game, |save| {
        save["player"]["floor"] = json!(floor);
        save["player"]["x"] = json!(x);
        save["player"]["y"] = json!(y);
        save["pending_interaction"] = Value::Null;
        save["pending_tile"] = Value::Null;
    });
}

fn step(game: &mut Engine, direction: &str) {
    game.command(json!({"type":"move","direction":direction}))
        .unwrap();
}

fn fight_from_below(game: &mut Engine, floor: i32, x: usize, y: usize) {
    place(game, floor, x, y + 1);
    step(game, "up");
}

fn log_contains(game: &Engine, text: &str) -> bool {
    game.snapshot()["log"]
        .as_array()
        .unwrap()
        .iter()
        .any(|line| line.as_str().unwrap().contains(text))
}

#[test]
fn floor_10_only_the_eight_arena_guards_gate_the_skeleton_boss() {
    let mut game = original();
    edit_save(&mut game, |save| {
        save["player"]["attack"] = json!(200);
        save["player"]["defense"] = json!(200);
        save["player"]["gold"] = json!(0);
    });
    place(&mut game, 10, 5, 5);
    step(&mut game, "up");
    assert_eq!(game.tile_at(10, 5, 0), Some(81));
    assert_eq!(game.tile_at(10, 5, 2), Some(4));
    assert_eq!(game.tile_at(10, 5, 6), Some(4));
    assert!(log_contains(&game, "Go and fight! Skeleton Soldiers!"));

    // moncheck reads eight staged guards, not the unrelated side monsters.
    let guards = [
        (4, 3),
        (5, 3),
        (6, 3),
        (4, 4),
        (6, 4),
        (4, 5),
        (5, 5),
        (6, 5),
    ];
    for (number, (x, y)) in guards.into_iter().enumerate() {
        fight_from_below(&mut game, 10, x, y);
        if number < 7 {
            assert_eq!(game.tile_at(10, 5, 2), Some(4));
        }
    }
    assert_eq!(game.tile_at(10, 5, 2), Some(6));
    assert_eq!(game.tile_at(10, 0, 5), Some(77));
    assert_eq!(game.tile_at(10, 3, 10), Some(69));
    assert_eq!(game.player().gold, 52); // Six Skeleton C + two Skeleton B.

    fight_from_below(&mut game, 10, 5, 0);
    assert_eq!(game.player().gold, 82);
    assert_eq!(game.tile_at(10, 5, 2), Some(23));
    assert_eq!(game.tile_at(10, 5, 6), Some(6));
    assert_eq!(game.tile_at(10, 3, 3), Some(6));
    assert_eq!(game.tile_at(10, 7, 3), Some(6));
    assert_eq!(game.tile_at(10, 5, 10), Some(11));
    assert_eq!(game.tile_at(10, 0, 2), Some(34));
    assert_eq!(game.tile_at(10, 10, 2), Some(35));
}

#[test]
fn floor_20_vampire_transformation_and_cross_combat_unlock_original_rewards() {
    let mut game = original();
    edit_save(&mut game, |save| {
        save["player"]["hp"] = json!(2000);
        save["player"]["attack"] = json!(140);
        save["player"]["defense"] = json!(110);
        save["player"]["gold"] = json!(0);
        save["player"]["inventory"] = json!(["cross"]);
    });
    place(&mut game, 20, 5, 8);
    step(&mut game, "up");
    assert_eq!(game.tile_at(20, 5, 5), Some(95));
    assert_eq!(game.tile_at(20, 5, 8), Some(4));
    for (x, y) in [
        (4, 4),
        (5, 4),
        (6, 4),
        (4, 5),
        (6, 5),
        (4, 6),
        (5, 6),
        (6, 6),
    ] {
        assert_eq!(game.tile_at(20, x, y), Some(6));
    }
    assert!(log_contains(&game, "as immortal as god"));

    // Cross: (140*2 - 66)=214 per hit; two retaliations of (199-110).
    fight_from_below(&mut game, 20, 5, 5);
    assert_eq!(game.player().hp, 1822);
    assert_eq!(game.player().gold, 144);
    assert_eq!(game.tile_at(20, 5, 4), Some(23));
    assert_eq!(game.tile_at(20, 5, 2), Some(6));
    assert_eq!(game.tile_at(20, 5, 8), Some(6));
    assert_eq!(game.tile_at(20, 5, 0), Some(11));
    assert_eq!(game.tile_at(20, 3, 4), Some(34));
    assert_eq!(game.tile_at(20, 7, 6), Some(35));
    assert!(log_contains(&game, "I've never dreamed I'd be defeated"));
}

#[test]
fn floor_40_all_thirteen_first_strike_fights_have_exact_damage_and_gold() {
    let mut game = original();
    edit_save(&mut game, |save| {
        save["player"]["hp"] = json!(10000);
        save["player"]["attack"] = json!(300);
        save["player"]["defense"] = json!(100);
        save["player"]["gold"] = json!(0);
        save["player"]["inventory"] = json!([]);
    });
    place(&mut game, 40, 5, 7);
    step(&mut game, "up");
    // Three each of Ghost Soldier, Soldier, Swordsman, Knight, then Golden Knight.
    // Enemy-first damage: 3*(80+100+580+130)+50 = 2720.
    // Gold: 3*(35+45+55+65)+100 = 700.
    assert_eq!(game.player().hp, 7280);
    assert_eq!(game.player().gold, 700);
    assert_eq!(game.snapshot()["status"], "playing");
    let ambushes = game.snapshot()["log"]
        .as_array()
        .unwrap()
        .iter()
        .filter(|line| line.as_str().unwrap().starts_with("Ambush:"))
        .count();
    assert_eq!(ambushes, 13);
    assert_eq!(game.tile_at(40, 5, 0), Some(11));
    assert_eq!(game.tile_at(40, 5, 5), Some(23));
    assert_eq!(game.tile_at(40, 5, 7), Some(6));
    assert_eq!(game.tile_at(40, 1, 1), Some(34));
    assert_eq!(game.tile_at(40, 9, 1), Some(35));

    let save = game.save_json();
    let mut restored = original();
    restored.load_json(&save).unwrap();
    assert_eq!(restored.save_json(), save);
    place(&mut restored, 40, 5, 7);
    step(&mut restored, "up");
    assert_eq!(restored.player().hp, 7280);
    assert_eq!(restored.player().gold, 700);
}

#[test]
fn floor_40_lethal_wave_stops_before_later_fights_and_rewards() {
    let mut game = original();
    edit_save(&mut game, |save| {
        save["player"]["hp"] = json!(300);
        save["player"]["attack"] = json!(300);
        save["player"]["defense"] = json!(100);
        save["player"]["gold"] = json!(0);
        save["player"]["inventory"] = json!([]);
    });
    place(&mut game, 40, 5, 7);
    step(&mut game, "up");
    assert_eq!(game.player().hp, 0);
    assert_eq!(game.snapshot()["status"], "lost");
    assert_eq!(game.player().gold, 105); // Three Ghost Soldiers; first Soldier is lethal.
    assert_eq!(game.tile_at(40, 5, 7), Some(4));
    assert_ne!(game.tile_at(40, 5, 0), Some(11));
    assert_ne!(game.tile_at(40, 5, 5), Some(23));
}

fn stage_zeno(game: &mut Engine) {
    edit_save(game, |save| {
        save["player"]["hp"] = json!(50000);
        save["player"]["attack"] = json!(1200);
        save["player"]["defense"] = json!(300);
        save["player"]["gold"] = json!(0);
    });
    place(game, 49, 5, 4);
    edit_save(game, |save| {
        save["player"]["inventory"] = json!(["hero_orb"]);
    });
    step(game, "down");
}

#[test]
fn floor_49_dice_seal_weakens_zeno_and_survives_save_restore() {
    let mut game = original();
    stage_zeno(&mut game);
    assert_eq!(game.inspect(5, 2)["enemy"]["hp"], 8000);
    assert_eq!(game.inspect(5, 2)["enemy"]["can_win"], false);
    for (number, (x, y)) in [(5, 1), (4, 2), (6, 2), (5, 3)].into_iter().enumerate() {
        fight_from_below(&mut game, 49, x, y);
        if number < 3 {
            assert_eq!(game.inspect(5, 2)["enemy"]["hp"], 8000);
        }
    }
    let enemy = game.inspect(5, 2)["enemy"].clone();
    assert_eq!(enemy["hp"], 800);
    assert_eq!(enemy["attack"], 500);
    assert_eq!(enemy["defense"], 100);
    for (x, y) in [(4, 1), (6, 1), (4, 3), (6, 3)] {
        assert_eq!(game.tile_at(49, x, y), Some(93));
    }
    assert_eq!(game.player().gold, 400);
    let save = game.save_json();
    let mut restored = original();
    restored.load_json(&save).unwrap();
    assert_eq!(restored.inspect(5, 2)["enemy"], enemy);
    fight_from_below(&mut restored, 49, 5, 2);
    assert_eq!(restored.player().gold, 900);
    assert_eq!(restored.tile_at(49, 5, 6), Some(6));
    assert_eq!(restored.tile_at(49, 5, 1), Some(23));
    assert_eq!(restored.tile_at(49, 6, 1), Some(46));
    assert_eq!(restored.tile_at(49, 4, 1), Some(30));
    assert_eq!(restored.tile_at(49, 4, 3), Some(6));
    assert_eq!(restored.tile_at(49, 6, 3), Some(6));
    assert!(
        restored.snapshot()["flags"]
            .as_array()
            .unwrap()
            .contains(&json!("decoy_zeno_defeated"))
    );
}

#[test]
fn floor_49_killing_a_corner_prevents_the_dice_seal() {
    let mut game = original();
    stage_zeno(&mut game);
    fight_from_below(&mut game, 49, 4, 1);
    for (x, y) in [(5, 1), (4, 2), (6, 2), (5, 3)] {
        fight_from_below(&mut game, 49, x, y);
    }
    assert_eq!(game.inspect(5, 2)["enemy"]["hp"], 8000);
    assert_eq!(game.inspect(5, 2)["enemy"]["attack"], 5000);
    assert_eq!(game.inspect(5, 2)["enemy"]["defense"], 1000);
}

#[test]
fn princess_time_gate_runs_the_first_cycle_scene_on_floor_50() {
    let mut game = original();
    // This eligibility follows handan 0x4453C9: F25 boss cell must be road.
    // No Sacred Sword or decoy flag is inferred as an additional requirement.
    edit_save(&mut game, |save| {
        save["floors"]["25"][60] = json!(6);
        save["player"]["inventory"] = json!([]);
    });
    place(&mut game, 26, 5, 6);
    step(&mut game, "up");
    game.command(json!({"type":"choose","choice":"leave"}))
        .unwrap();
    assert_eq!(game.tile_at(24, 5, 0), Some(7));
    assert_eq!(game.tile_at(24, 5, 1), Some(6));
    assert_eq!(game.tile_at(50, 4, 8), Some(21));
    let ready = game.save_json();
    let mut restored = original();
    restored.load_json(&ready).unwrap();
    place(&mut restored, 24, 5, 1);
    step(&mut restored, "up");
    assert_eq!(
        (
            restored.player().floor,
            restored.player().x,
            restored.player().y
        ),
        (50, 5, 6)
    );
    assert_eq!(restored.tile_at(24, 5, 0), Some(6));
    assert_eq!(restored.tile_at(50, 5, 4), Some(91));
    assert_eq!(restored.snapshot()["status"], "playing");
    assert!(log_contains(
        &restored,
        "For that reason, I gave false information"
    ));
    assert!(log_contains(&restored, "recieve great enlightenment"));
    assert!(!log_contains(
        &restored,
        "I believe there is a sword on the 5th floor"
    ));
    let stats = (
        restored.player().hp,
        restored.player().attack,
        restored.player().defense,
        restored.player().gold,
    );
    step(&mut restored, "up");
    assert_eq!((restored.player().x, restored.player().y), (5, 5));
    step(&mut restored, "up"); // Touch Zeno: original first cycle completes without battle.
    assert_eq!(restored.snapshot()["status"], "playing");
    assert_eq!(restored.snapshot()["cycle"], 2);
    assert_eq!(
        (
            restored.player().floor,
            restored.player().x,
            restored.player().y
        ),
        (1, 5, 10)
    );
    assert_eq!(
        (
            restored.player().hp,
            restored.player().attack,
            restored.player().defense,
            restored.player().gold
        ),
        (stats.0, stats.1, stats.2, 0)
    );
    assert_eq!(
        restored.tile_at(50, 5, 4),
        Some(
            restored
                .campaign
                .floors
                .iter()
                .find(|f| f.id == 50)
                .unwrap()
                .tiles[49]
        )
    );
}
