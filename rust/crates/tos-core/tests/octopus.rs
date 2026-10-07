//! Original executable assertions are reproduced on the imported floor15.
//! These scenario saves isolate contact cells; they are not a natural route.
use serde_json::{Value, json};
use tos_core::Engine;

fn original_value() -> Value {
    serde_json::from_str(include_str!("../../../../data/campaign.json")).unwrap()
}

fn scenario(campaign: &Value, tile: u16, lucky: bool, cycle: u32) -> Engine {
    let mut game = Engine::from_json(&campaign.to_string()).unwrap();
    let mut save: Value = serde_json::from_str(&game.save_json()).unwrap();
    let index = usize::from(tile - 97);
    let factor = if cycle > 1 { 44 } else { 1 };
    save["cycle"] = json!(cycle);
    save["player"]["floor"] = json!(15);
    save["player"]["x"] = json!(4 + index % 3);
    save["player"]["y"] = json!(4 + index / 3);
    save["player"]["hp"] = json!(10000 * factor);
    save["player"]["attack"] = json!(420 * factor);
    save["player"]["defense"] = json!(100 * factor);
    save["player"]["gold"] = json!(0);
    save["player"]["inventory"] = if lucky {
        json!(["hero_orb", "lucky_gold"])
    } else {
        json!(["hero_orb"])
    };
    save["player"]["weapon"] = Value::Null;
    save["player"]["shield"] = Value::Null;
    save["pending_interaction"] = Value::Null;
    save["pending_tile"] = Value::Null;
    save["visited_floors"] = json!([1, 15]);
    game.load_json(&save.to_string()).unwrap();
    game
}

fn step(game: &mut Engine, direction: &str) {
    game.command(json!({"type":"move","direction":direction}))
        .unwrap();
}

fn inspect_gold(game: &Engine, tile: u16) -> i64 {
    let index = usize::from(tile - 97);
    game.inspect(4 + index % 3, 3 + index / 3)["enemy"]["gold"]
        .as_i64()
        .unwrap()
}

fn remaining_cells(game: &Engine) -> usize {
    (3..=5)
        .flat_map(|y| (4..=6).map(move |x| (x, y)))
        .filter(|&(x, y)| {
            game.tile_at(15, x, y)
                .is_some_and(|id| (97..=105).contains(&id))
        })
        .count()
}

#[test]
fn every_original_part_uses_full_stats_but_only_bottom_center_clears_the_creature() {
    let campaign = original_value();
    for lucky in [false, true] {
        for tile in 97..=105 {
            let mut game = scenario(&campaign, tile, lucky, 1);
            let gold = (if tile == 104 { 100 } else { 50 }) * if lucky { 2 } else { 1 };
            assert_eq!(inspect_gold(&game, tile), gold);
            let index = usize::from(tile - 97);
            let forecast = game.inspect(4 + index % 3, 3 + index / 3)["enemy"].clone();
            assert_eq!(forecast["hp"], 1200);
            assert_eq!(forecast["attack"], 180);
            assert_eq!(forecast["defense"], 20);
            assert_eq!(forecast["damage"], 160);
            let from_snapshot = game.snapshot()["enemies"]
                .as_array()
                .unwrap()
                .iter()
                .find(|enemy| enemy["id"] == tile)
                .unwrap()["gold"]
                .clone();
            assert_eq!(from_snapshot, gold);
            step(&mut game, "up");
            assert_eq!(game.player().hp, 9840, "tile{tile}");
            assert_eq!(game.player().gold, gold, "tile{tile}");
            let cleared = game.snapshot()["last_action"]["presentation"]
                .as_array()
                .unwrap()
                .iter()
                .filter(|effect| effect["type"] == "tile")
                .count();
            assert_eq!(
                cleared,
                if tile == 104 { 9 } else { 1 },
                "one update per changed cell"
            );
            assert_eq!(
                remaining_cells(&game),
                if tile == 104 { 0 } else { 8 },
                "tile{tile}"
            );
        }
    }
}

#[test]
fn defeating_parts_does_not_weaken_remaining_parts_and_survives_save_load() {
    let campaign = original_value();
    let mut game = scenario(&campaign, 103, false, 1);
    step(&mut game, "up");
    assert_eq!(game.player().gold, 50);
    assert_eq!(remaining_cells(&game), 8);
    let checkpoint = game.save_json();
    game.load_json(&checkpoint).unwrap();
    step(&mut game, "down");
    step(&mut game, "right");
    let body = game.inspect(5, 5)["enemy"].clone();
    assert_eq!(
        (body["hp"].clone(), body["damage"].clone()),
        (json!(1200), json!(160))
    );
    step(&mut game, "up");
    assert_eq!(game.player().hp, 9680);
    assert_eq!(game.player().gold, 150);
    assert_eq!(remaining_cells(&game), 0);
}

#[test]
fn division_precedes_lucky_gold_and_backside_scales_stats_without_scaling_rewards() {
    let mut campaign = original_value();
    campaign["enemies"]["giant_octopus"]["gold"] = json!(101);
    for cycle in [1, 2] {
        for lucky in [false, true] {
            for tile in [103, 104, 105] {
                let mut game = scenario(&campaign, tile, lucky, cycle);
                let gold = (if tile == 104 { 101 } else { 50 }) * if lucky { 2 } else { 1 };
                assert_eq!(inspect_gold(&game, tile), gold);
                step(&mut game, "up");
                assert_eq!(game.player().gold, gold);
                assert_eq!(game.player().hp, 9840 * if cycle == 1 { 1 } else { 44 });
                assert_eq!(remaining_cells(&game), if tile == 104 { 0 } else { 8 });
            }
        }
    }
}

#[test]
fn reward_divisor_is_generic_validated_and_default_serialization_is_unchanged() {
    for invalid in [
        json!(0),
        json!(-1),
        json!(null),
        json!(true),
        json!(2.5),
        json!("2"),
    ] {
        let mut campaign = original_value();
        campaign["tiles"]["103"]["reward_divisor"] = invalid;
        assert!(Engine::from_json(&campaign.to_string()).is_err());
    }
    let mut campaign = original_value();
    campaign["tiles"]["61"]["reward_divisor"] = json!(3);
    // A configurable custom enemy part does not depend on the original name.
    let key = campaign["tiles"]["61"]["enemy"]
        .as_str()
        .unwrap()
        .to_owned();
    campaign["enemies"][&key] = json!({
        "name":"Custom part", "hp":1200, "attack":180, "defense":20, "gold":101
    });
    let floor = campaign["floors"]
        .as_array_mut()
        .unwrap()
        .iter_mut()
        .find(|f| f["id"] == 15)
        .unwrap();
    floor["tiles"][5 * 11 + 4] = json!(61);
    let mut game = scenario(&campaign, 103, true, 1);
    assert_eq!(game.campaign().tiles["61"].reward_divisor, Some(3));
    assert_eq!(inspect_gold(&game, 103), 66);
    step(&mut game, "up");
    assert_eq!(game.player().gold, 66);
    assert_eq!(game.player().hp, 9840);
    let mut one = original_value();
    one["tiles"]["61"]["reward_divisor"] = json!(1);
    let canonical =
        serde_json::to_value(Engine::from_json(&one.to_string()).unwrap().campaign()).unwrap();
    assert!(canonical["tiles"]["61"].get("reward_divisor").is_none());
}

#[test]
fn whole_creature_clear_matches_the_original_unconditional_footprint_writes() {
    let mut campaign = original_value();
    let floor = campaign["floors"]
        .as_array_mut()
        .unwrap()
        .iter_mut()
        .find(|f| f["id"] == 15)
        .unwrap();
    // Inject another valid tile: original opcode17 still writes road there.
    floor["tiles"][3 * 11 + 4] = json!(1);
    let mut game = scenario(&campaign, 104, false, 1);
    step(&mut game, "up");
    assert_eq!(game.tile_at(15, 4, 3), Some(6));
    assert_eq!(remaining_cells(&game), 0);
}

#[test]
fn blocked_and_fatal_contacts_keep_every_octopus_cell_and_give_no_reward() {
    let campaign = original_value();
    for tile in [103, 104, 105] {
        for fatal in [false, true] {
            let mut game = scenario(&campaign, tile, false, 1);
            let mut save: Value = serde_json::from_str(&game.save_json()).unwrap();
            if fatal {
                save["player"]["hp"] = json!(160);
            } else {
                save["player"]["attack"] = json!(20);
            }
            game.load_json(&save.to_string()).unwrap();
            step(&mut game, "up");
            assert_eq!(game.player().gold, 0);
            assert_eq!(remaining_cells(&game), 9);
            assert_eq!(game.player().hp, if fatal { 0 } else { 10000 });
            let index = usize::from(tile - 97);
            assert_eq!(game.player().x, 4 + index % 3);
            assert_eq!(game.player().y, (if fatal { 3 } else { 4 }) + index / 3);
        }
    }
}
