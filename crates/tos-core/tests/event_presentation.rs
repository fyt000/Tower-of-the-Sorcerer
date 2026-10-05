//! Ordered presentation for world actions, items and scripted events.
//! Isolated scenarios check rendering messages against executable evidence.
use serde_json::{Value, json};
use tos_core::Engine;

fn original_at(floor: i32, x: usize, y: usize) -> Engine {
    let mut game = Engine::from_json(include_str!("../../../data/campaign.json")).unwrap();
    let mut save: Value = serde_json::from_str(&game.save_json()).unwrap();
    save["player"]["floor"] = json!(floor);
    save["player"]["x"] = json!(x);
    save["player"]["y"] = json!(y);
    game.load_json(&save.to_string()).unwrap();
    game
}

fn step(game: &mut Engine, direction: &str) -> Value {
    game.command(json!({"type":"move","direction":direction}))
        .unwrap();
    game.snapshot()
}

#[test]
fn capture_materializes_zeno_then_shows_title_before_the_prison_wakeup() {
    let mut game = original_at(3, 4, 9);
    let state = step(&mut game, "up");
    let timeline = state["last_action"]["presentation"].as_array().unwrap();
    let position = |kind: &str| timeline.iter().position(|e| e["kind"] == kind).unwrap();
    let summon = &timeline[position("magic")];
    assert_eq!(
        (summon["x"].as_u64(), summon["y"].as_u64()),
        (Some(4), Some(6))
    );
    assert_eq!(summon["color_tile"], 91);
    assert_eq!(summon["underlying_tile"], 6);
    assert_eq!(summon["frames"], json!((166..=182).collect::<Vec<_>>()));
    let speech = timeline.iter().position(|e| e["dialogue_id"] == 9).unwrap();
    let prison = timeline
        .iter()
        .position(|e| e["type"] == "floor" && e["to"] == 2)
        .unwrap();
    assert!(position("magic") < speech);
    assert!(speech < position("title"));
    assert!(position("title") < position("scan"));
    assert!(position("scan") < prison);
    assert_eq!(timeline[prison]["style"], "capture");
    assert_eq!(timeline[prison]["sound"], "none");
    assert_eq!(
        timeline[position("title")]["sound_offsets_ms"]
            .as_array()
            .unwrap()
            .len(),
        16
    );
    assert_eq!((game.player().floor, game.player().hp), (2, 400));
    assert_eq!(game.tile_at(3, 4, 6), Some(6));
    assert!(timeline[prison + 1..].iter().any(|e| e["dialogue_id"] == 3));
}

#[test]
fn skeleton_guard_march_keeps_all_forty_three_original_moves() {
    let mut game = original_at(10, 5, 5);
    let state = step(&mut game, "up");
    let timeline = state["last_action"]["presentation"].as_array().unwrap();
    let movements: Vec<_> = timeline
        .iter()
        .filter(|e| e["type"] == "move_tile")
        .collect();
    assert_eq!(movements.len(), 43);
    assert_eq!(movements[0]["tile"], 81); // Boss retreats to the top of the arena.
    assert_eq!(game.tile_at(10, 5, 0), Some(81));
    assert_eq!(game.tile_at(10, 5, 2), Some(4));
    assert_eq!(game.tile_at(10, 5, 6), Some(4));
}

#[test]
fn vampire_body_changes_after_the_original_transformation_span() {
    let mut game = original_at(20, 5, 8);
    let state = step(&mut game, "up");
    let timeline = state["last_action"]["presentation"].as_array().unwrap();
    let transform = timeline
        .iter()
        .position(|e| e["kind"] == "transformation")
        .unwrap();
    assert_eq!(
        timeline[transform]["original_frames"],
        json!((1..=32).collect::<Vec<_>>())
    );
    assert_eq!(
        timeline[transform]["from_tiles"].as_array().unwrap().len(),
        9
    );
    let body = timeline
        .iter()
        .position(|e| e["type"] == "tile" && e["x"] == 5 && e["y"] == 5 && e["tile"] == 95)
        .unwrap();
    assert!(transform < body);
    assert_eq!(game.tile_at(20, 5, 5), Some(95));
    assert_eq!(game.tile_at(20, 4, 4), Some(6));
}

#[test]
fn decoy_zeno_and_eight_sorcerers_retain_their_materialization_masks() {
    let mut game = original_at(49, 5, 4);
    let state = step(&mut game, "down");
    let timeline = state["last_action"]["presentation"].as_array().unwrap();
    let magic: Vec<_> = timeline.iter().filter(|e| e["kind"] == "magic").collect();
    assert_eq!(magic.len(), 2);
    assert_eq!(magic[0]["color_tile"], 91);
    assert_eq!(
        (magic[0]["x"].as_u64(), magic[0]["y"].as_u64()),
        (Some(5), Some(2))
    );
    assert_eq!(magic[1]["color_tile"], 93);
    assert_eq!(
        magic[1]["frames"],
        json!([167, 169, 171, 173, 175, 177, 179, 182])
    );
    assert_eq!(
        magic[1]["targets"],
        json!([
            {"x":4,"y":1}, {"x":5,"y":1}, {"x":6,"y":1}, {"x":6,"y":2},
            {"x":6,"y":3}, {"x":5,"y":3}, {"x":4,"y":3}, {"x":4,"y":2}
        ])
    );
    assert_eq!(game.tile_at(49, 5, 2), Some(91));
    for (x, y) in [
        (4, 1),
        (5, 1),
        (6, 1),
        (4, 2),
        (6, 2),
        (4, 3),
        (5, 3),
        (6, 3),
    ] {
        assert_eq!(game.tile_at(49, x, y), Some(93));
    }
}

fn room() -> Value {
    let mut campaign: Value =
        serde_json::from_str(include_str!("../../../data/campaign.json")).unwrap();
    campaign["id"] = json!("animation-room");
    campaign["width"] = json!(5);
    campaign["height"] = json!(5);
    campaign["floors"] = json!([{"id":1,"tiles":vec![6;25]}]);
    campaign["events"] = json!([]);
    campaign["interactions"] = json!([]);
    campaign["rules"] = json!({"empty_tile":6,"wall_break_tile_ranges":[[8,8]]});
    campaign["start"] = json!({"floor":1,"x":2,"y":2,"hp":10000,"attack":1000,"defense":1000,
        "keys":{"yellow":1,"blue":1,"red":1},"inventory":[]});
    campaign
}

fn game(campaign: &Value) -> Engine {
    Engine::from_json(&campaign.to_string()).unwrap()
}

fn command(game: &mut Engine, action: Value) -> Vec<Value> {
    game.command(action).unwrap();
    game.snapshot()["last_action"]["presentation"]
        .as_array()
        .unwrap()
        .clone()
}

fn edit(game: &mut Engine, change: impl FnOnce(&mut Value)) {
    let mut saved: Value = serde_json::from_str(&game.save_json()).unwrap();
    change(&mut saved);
    game.load_json(&saved.to_string()).unwrap();
}

#[test]
fn every_key_door_opens_before_the_hero_walks_and_blocked_doors_stay_closed() {
    for (tile, key) in [(1, "yellow"), (2, "blue"), (3, "red")] {
        let mut campaign = room();
        campaign["floors"][0]["tiles"][13] = json!(tile);
        campaign["rules"]["presentation"]["tile_transition_ms"] = json!(320);
        let mut engine = game(&campaign);
        let effects = command(&mut engine, json!({"type":"move","direction":"right"}));
        assert_eq!(effects[0]["kind"], "tile_reveal");
        assert_eq!(effects[0]["style"], "door_open");
        assert_eq!(effects[0]["from_tile"], tile);
        assert_eq!(effects[0]["tile"], 6);
        assert_eq!(effects[0]["duration_ms"], 320);
        assert_eq!(effects[0]["sound_cue"], "open");
        assert_eq!(effects[1]["type"], "tile");
        assert_eq!(effects[2]["type"], "move");
        assert_eq!(engine.tile_at(1, 3, 2), Some(6));
        assert_eq!(engine.player().x, 3);
        assert_eq!(engine.snapshot()["player"]["keys"][key], 0);
        campaign["start"]["keys"][key] = json!(0);
        let mut blocked = game(&campaign);
        assert!(command(&mut blocked, json!({"type":"move","direction":"right"})).is_empty());
        assert_eq!(blocked.tile_at(1, 3, 2), Some(tile));
        assert_eq!(blocked.player().x, 2);
    }
}

#[test]
fn secret_passage_and_both_pickaxes_collapse_each_target_before_its_clear() {
    let mut campaign = room();
    campaign["floors"][0]["tiles"][13] = json!(9);
    let mut engine = game(&campaign);
    let secret = command(&mut engine, json!({"type":"move","direction":"right"}));
    assert_eq!(secret[0]["style"], "wall_collapse");
    assert_eq!(secret[0]["from_tile"], 9);
    assert_eq!(secret[1]["type"], "tile");
    for item in ["mattock", "super_mattock"] {
        let mut campaign = room();
        campaign["start"]["inventory"] = json!([item]);
        for index in [7, 11, 13, 17, 0] {
            campaign["floors"][0]["tiles"][index] = json!(8);
        }
        campaign["floors"][0]["tiles"][1] = json!(10);
        let mut engine = game(&campaign);
        let effects = command(&mut engine, json!({"type":"use_item","item":item}));
        let expected = if item == "mattock" { 4 } else { 5 };
        assert_eq!(effects.len(), expected * 2);
        for pair in effects.as_chunks::<2>().0 {
            assert_eq!(pair[0]["style"], "wall_collapse");
            assert_eq!(pair[0]["from_tile"], 8);
            assert_eq!(pair[1]["type"], "tile");
            assert_eq!(pair[0]["x"], pair[1]["x"]);
            assert_eq!(pair[0]["y"], pair[1]["y"]);
        }
        assert_eq!(engine.tile_at(1, 1, 0), Some(10));
        assert!(!engine.player().inventory.iter().any(|owned| owned == item));
    }
}

#[test]
fn magic_key_uses_the_same_door_motion_without_spending_normal_keys() {
    let mut campaign = room();
    campaign["start"]["inventory"] = json!(["magic_key"]);
    for index in [0, 7, 13] {
        campaign["floors"][0]["tiles"][index] = json!(1);
    }
    campaign["floors"][0]["tiles"][1] = json!(2);
    let mut engine = game(&campaign);
    let effects = command(&mut engine, json!({"type":"use_item","item":"magic_key"}));
    assert_eq!(
        effects
            .iter()
            .filter(|fx| fx["style"] == "door_open")
            .count(),
        3
    );
    assert_eq!(engine.snapshot()["player"]["keys"]["yellow"], 1);
    assert_eq!(engine.tile_at(1, 1, 0), Some(2));
}

#[test]
fn bomb_dissolves_enemies_before_the_guard_gate_animation_and_rewards() {
    let mut campaign = room();
    campaign["start"]["inventory"] = json!(["bomb"]);
    campaign["floors"][0]["tiles"][13] = json!(61);
    campaign["floors"][0]["tiles"][0] = json!(4);
    campaign["events"] = json!([{"id":"guard","trigger":{"type":"enemy_defeated"},
        "effects":[{"type":"set_tile","floor":1,"x":0,"y":0,"tile":6}]}]);
    let mut engine = game(&campaign);
    let effects = command(&mut engine, json!({"type":"use_item","item":"bomb"}));
    assert_eq!(effects[0]["kind"], "magic");
    assert_eq!(effects[0]["underlying_tile"], 61);
    assert_eq!(effects[0]["color_tile"], 6);
    assert_eq!(effects[0]["frames"], json!([166, 170, 174, 178, 182]));
    assert_eq!(
        effects[0]["sound_offsets_ms"],
        json!([0, 150, 300, 450, 600])
    );
    assert_eq!(effects[1]["type"], "tile");
    assert_eq!(effects[2]["style"], "gate_open");
    assert_eq!(engine.tile_at(1, 0, 0), Some(6));
    assert_eq!(engine.player().gold, 1);
}

#[test]
fn magic_field_shows_the_damage_pose_after_walking_and_respects_the_shield() {
    let mut campaign = room();
    campaign["floors"][0]["tiles"][8] = json!(151); // Magician beside destination.
    for protected in [false, true] {
        campaign["start"]["inventory"] = if protected {
            json!(["sacred_shield"])
        } else {
            json!([])
        };
        let mut engine = game(&campaign);
        let effects = command(&mut engine, json!({"type":"move","direction":"right"}));
        assert_eq!(effects[0]["type"], "move");
        if protected {
            assert!(!effects.iter().any(|fx| fx["type"] == "damage"));
            assert_eq!(engine.player().hp, 10000);
        } else {
            assert_eq!(effects[1]["type"], "damage");
            assert_eq!(effects[1]["x"], 3);
            assert_eq!(effects[1]["hero_hp"], 10000);
            assert_eq!(effects[1]["enemy_hit"], 200);
            assert_eq!(engine.player().hp, 9800);
        }
    }
}

#[test]
fn floor_47_magicians_retreat_after_the_hit_and_also_retreat_with_sacred_shield() {
    for protected in [false, true] {
        let mut engine = original_at(47, 5, 6);
        edit(&mut engine, |saved| {
            saved["floors"]["47"] = json!(vec![6; 121]);
            saved["floors"]["47"][61] = json!(151);
            saved["player"]["hp"] = json!(1000);
            saved["player"]["inventory"] = if protected {
                json!(["sacred_shield"])
            } else {
                json!([])
            };
        });
        let effects = command(&mut engine, json!({"type":"move","direction":"up"}));
        assert_eq!(engine.player().hp, if protected { 1000 } else { 800 });
        assert_eq!(engine.tile_at(47, 6, 5), Some(6));
        assert_eq!(engine.tile_at(47, 7, 5), Some(151));
        let motion = effects
            .iter()
            .position(|cue| cue["type"] == "move_tile")
            .unwrap();
        assert_eq!(effects[motion]["from_x"], 6);
        assert_eq!(effects[motion]["x"], 7);
        assert_eq!(effects[motion]["tile"], 151);
        assert_eq!(effects[motion - 2]["name"], "get");
        assert_eq!(effects[motion - 1]["duration_ms"], 25);
        assert_eq!(effects[motion + 1]["duration_ms"], 25);
        let damage = effects.iter().position(|cue| cue["type"] == "damage");
        assert_eq!(damage.is_some(), !protected);
        assert!(damage.is_none_or(|index| index < motion));
        // The moving tile message owns both writes; generic clear/open cues
        // must not animate the same magician a second time.
        assert!(!effects.iter().any(|cue| cue["type"] == "tile"));
    }
}

#[test]
fn magician_retreat_checks_both_coordinates_and_an_ordinary_road_destination() {
    for (floor, hero, magician, target, target_tile, retreat) in [
        (47, (5, 0), (6, 0), (7, 0), 6, true),
        (47, (5, 10), (4, 10), (3, 10), 6, true),
        (47, (5, 8), (5, 9), (5, 10), 6, true),
        (47, (5, 2), (5, 1), (5, 0), 6, true),
        (47, (9, 5), (10, 5), (0, 6), 6, false),
        (47, (1, 5), (0, 5), (10, 4), 6, false),
        (47, (5, 5), (6, 5), (7, 5), 8, false),
        (46, (5, 5), (6, 5), (7, 5), 6, false),
    ] {
        // Approach from an ordinary road, including when the target is on
        // the first/last row or the magician is above/below the hero.
        let (start, direction) = if magician.1 != hero.1 {
            ((hero.0 - 1, hero.1), "right")
        } else if hero.1 == 0 {
            ((hero.0, 1), "up")
        } else {
            ((hero.0, hero.1 - 1), "down")
        };
        let mut engine = original_at(floor, start.0, start.1);
        edit(&mut engine, |saved| {
            saved["floors"][floor.to_string()] = json!(vec![6; 121]);
            saved["floors"][floor.to_string()][magician.1 * 11 + magician.0] = json!(151);
            saved["floors"][floor.to_string()][target.1 * 11 + target.0] = json!(target_tile);
        });
        let effects = command(&mut engine, json!({"type":"move","direction":direction}));
        assert_eq!(
            engine.tile_at(floor, magician.0, magician.1),
            Some(if retreat { 6 } else { 151 }),
            "floor={floor} hero={hero:?} magician={magician:?}"
        );
        assert_eq!(
            effects.iter().any(|cue| cue["type"] == "move_tile"),
            retreat
        );
        assert_eq!(
            engine.tile_at(floor, target.0, target.1),
            Some(if retreat { 151 } else { target_tile })
        );
    }
}

#[test]
fn long_combat_keeps_one_bounded_presentation_and_exact_damage() {
    let mut campaign = room();
    campaign["start"]["hp"] = json!(10000);
    campaign["start"]["attack"] = json!(11);
    campaign["start"]["defense"] = json!(10);
    campaign["enemies"]["green_slime"] =
        json!({"name":"Long fight", "hp":3000,"attack":11,"defense":10,"gold":3});
    campaign["floors"][0]["tiles"][13] = json!(61);
    let mut engine = game(&campaign);
    let effects = command(&mut engine, json!({"type":"move","direction":"right"}));
    assert_eq!(engine.player().hp, 7001);
    assert_eq!(engine.player().gold, 3);
    assert!(effects.len() < 10);
    let battle: Vec<_> = effects
        .iter()
        .filter(|cue| cue["type"] == "battle")
        .collect();
    assert_eq!(battle.len(), 1);
    assert_eq!(battle[0]["hero_strikes"], 3000);
    assert_eq!(battle[0]["enemy_strikes"], 2999);
    assert_eq!(battle[0]["damage"], 2999);
    let checkpoint = engine.runtime_checkpoint_json();
    let mut restored = game(&campaign);
    restored
        .restore_runtime_checkpoint_json(&checkpoint)
        .unwrap();
    assert_eq!(restored.snapshot(), engine.snapshot());
}

#[test]
fn typed_runtime_checkpoint_roundtrips_every_original_cinematic_field() {
    let mut engine = original_at(10, 5, 5);
    step(&mut engine, "up");
    let checkpoint = engine.runtime_checkpoint_json();
    let mut restored = original_at(1, 5, 10);
    restored
        .restore_runtime_checkpoint_json(&checkpoint)
        .unwrap();
    assert_eq!(restored.snapshot(), engine.snapshot());
    // A prior long queue cannot leave a phantom cue in the next action.
    edit(&mut restored, |saved| {
        saved["player"]["floor"] = json!(49);
        saved["player"]["x"] = json!(5);
        saved["player"]["y"] = json!(4);
    });
    let after_long_action = step(&mut restored, "down");
    let mut fresh = original_at(49, 5, 4);
    let after_fresh_action = step(&mut fresh, "down");
    let cues = |state: &Value| {
        state["last_action"]["presentation"]
            .as_array()
            .unwrap()
            .iter()
            .cloned()
            .map(|mut cue| {
                // Log identities naturally differ after the earlier encounter.
                cue.as_object_mut().unwrap().remove("log_id");
                cue
            })
            .collect::<Vec<_>>()
    };
    assert_eq!(cues(&after_long_action), cues(&after_fresh_action));
}

#[test]
fn recovered_guard_events_keep_each_original_gate_motion_exactly_once() {
    let campaign: Value =
        serde_json::from_str(include_str!("../../../data/campaign.json")).unwrap();
    for event in campaign["events"]
        .as_array()
        .unwrap()
        .iter()
        .filter(|event| {
            event["id"].as_str().unwrap_or("").contains("guards_")
                && event["effects"]
                    .as_array()
                    .unwrap()
                    .iter()
                    .any(|fx| fx["original_mode"].is_number())
                && event["conditions"]
                    .as_array()
                    .unwrap()
                    .iter()
                    .all(|condition| condition["type"] == "tile")
        })
    {
        let floor = event["trigger"]["floor"].as_i64().unwrap() as i32;
        let guard = event["conditions"]
            .as_array()
            .unwrap()
            .iter()
            .find(|condition| {
                let x = condition["x"].as_u64().unwrap() as usize;
                let y = condition["y"].as_u64().unwrap() as usize;
                let map = campaign["floors"]
                    .as_array()
                    .unwrap()
                    .iter()
                    .find(|map| map["id"] == floor)
                    .unwrap();
                let tile = map["tiles"][y * 11 + x].to_string();
                campaign["tiles"][tile]["kind"] == "enemy"
            })
            .unwrap();
        let (gx, gy) = (
            guard["x"].as_u64().unwrap() as usize,
            guard["y"].as_u64().unwrap() as usize,
        );
        let mut engine = game(&campaign);
        let original_guard = engine.tile_at(floor, gx, gy).unwrap();
        let (hx, direction) = if gx > 0 {
            (gx - 1, "right")
        } else {
            (gx + 1, "left")
        };
        edit(&mut engine, |saved| {
            for condition in event["conditions"].as_array().unwrap() {
                let cf = condition["floor"].as_i64().unwrap().to_string();
                let index = condition["y"].as_u64().unwrap() as usize * 11
                    + condition["x"].as_u64().unwrap() as usize;
                saved["floors"][cf][index] = condition["tile"].clone();
            }
            saved["floors"][floor.to_string()][gy * 11 + gx] = json!(original_guard);
            saved["floors"][floor.to_string()][gy * 11 + hx] = json!(6);
            saved["player"]["floor"] = json!(floor);
            saved["player"]["x"] = json!(hx);
            saved["player"]["y"] = json!(gy);
            saved["player"]["attack"] = json!(100000);
            saved["player"]["defense"] = json!(100000);
        });
        let effects = command(&mut engine, json!({"type":"move","direction":direction}));
        for scene in event["effects"]
            .as_array()
            .unwrap()
            .iter()
            .filter(|fx| fx["original_mode"].is_number())
        {
            let matches: Vec<_> = effects
                .iter()
                .filter(|fx| {
                    fx["kind"] == "tile_reveal" && fx["x"] == scene["x"] && fx["y"] == scene["y"]
                })
                .collect();
            assert_eq!(
                matches.len(),
                1,
                "{} at {},{}",
                event["id"],
                scene["x"],
                scene["y"]
            );
            assert_eq!(matches[0]["style"], scene["style"]);
            assert_eq!(
                matches[0]["original_frames"],
                json!((1..=16).collect::<Vec<_>>())
            );
        }
        assert!(
            effects
                .iter()
                .any(|fx| fx["type"] == "audio" && fx["name"] == "open")
        );
    }
}

#[test]
fn hidden_magician_reveal_keeps_its_predicate_cue_and_approach_position() {
    let campaign: Value =
        serde_json::from_str(include_str!("../../../data/campaign.json")).unwrap();
    let mut engine = game(&campaign);
    edit(&mut engine, |saved| {
        saved["player"]["floor"] = json!(41);
        saved["player"]["x"] = json!(8);
        saved["player"]["y"] = json!(1);
    });
    let blocked = command(&mut engine, json!({"type":"move","direction":"right"}));
    assert!(blocked.is_empty());
    assert_eq!(engine.tile_at(41, 9, 1), Some(10));
    edit(&mut engine, |saved| saved["floors"]["41"][12] = json!(6));
    let reveal = command(&mut engine, json!({"type":"move","direction":"right"}));
    assert_eq!(reveal[0], json!({"type":"audio","name":"get"}));
    assert_eq!(reveal[1]["type"], "tile");
    assert_eq!(engine.tile_at(41, 9, 1), Some(151));
    assert_eq!(engine.player().x, 8);
    assert!(reveal.iter().all(|effect| effect["type"] != "battle"));
}
