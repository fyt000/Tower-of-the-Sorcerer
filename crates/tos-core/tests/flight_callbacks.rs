//! Original Flight UI world writes are shared by direct GUI/MCP travel.
use serde_json::{Value, json};
use tos_core::Engine;

fn campaign() -> Value {
    serde_json::from_str(include_str!("../../../data/campaign.json")).unwrap()
}

fn prepare(from: i32, highest: i32, changes: &[(i32, usize, usize, u16)]) -> Engine {
    let mut value = campaign();
    value["rules"]["flying_requires_stairs"] = json!(false);
    let mut engine = Engine::from_json(&value.to_string()).unwrap();
    let mut save: Value = serde_json::from_str(&engine.save_json()).unwrap();
    save["player"]["floor"] = json!(from);
    save["player"]["x"] = json!(0);
    save["player"]["y"] = json!(0);
    save["player"]["inventory"] = json!(["flying_orb"]);
    save["highest_stair_floor"] = json!(highest);
    save["visited_floors"] = json!([from, highest]);
    for &(floor, x, y, tile) in changes {
        save["floors"][floor.to_string()][y * 11 + x] = json!(tile);
    }
    engine.load_json(&save.to_string()).unwrap();
    engine
}

fn fly(engine: &mut Engine, to: i32) {
    engine
        .command(json!({"type":"use_item","item":"flying_orb","floor":to}))
        .unwrap();
    assert_eq!(engine.snapshot()["last_action"]["ok"], true);
    assert_eq!(engine.player().floor, to);
}

#[test]
fn upward_monotonic_selection_runs_exact_tunnel_guard_at_35() {
    for (from, to, tunnel, thief, expected) in [
        (34, 35, 6, 21, 6),
        (34, 36, 6, 21, 6),
        (34, 36, 8, 21, 21),
        (34, 36, 6, 19, 19),
        (36, 35, 6, 21, 21),
        (35, 36, 6, 21, 21),
        // Reproduce the original numeric guard, including this unusual sum.
        (34, 36, 8, 19, 6),
    ] {
        let mut engine = prepare(from, 40, &[(35, 3, 8, tunnel), (2, 10, 10, thief)]);
        fly(&mut engine, to);
        assert_eq!(engine.tile_at(2, 10, 10), Some(expected), "{from}->{to}");
    }
}

#[test]
fn changed_confirmation_cleans_existing_fairies_except_selected_floor() {
    for (to, expected25, expected49) in [(24, 6, 6), (25, 23, 6), (49, 6, 23)] {
        let mut engine = prepare(26, 49, &[(25, 5, 6, 23), (49, 5, 1, 23)]);
        fly(&mut engine, to);
        assert_eq!(engine.tile_at(25, 5, 6), Some(expected25));
        assert_eq!(engine.tile_at(49, 5, 1), Some(expected49));
    }
    let mut engine = prepare(26, 49, &[(25, 5, 6, 8), (49, 5, 1, 6)]);
    fly(&mut engine, 24);
    assert_eq!(engine.tile_at(25, 5, 6), Some(8));
    assert_eq!(engine.tile_at(49, 5, 1), Some(6));
}

#[test]
fn same_floor_and_rejected_flight_leave_context_unchanged() {
    let changes = [
        (25, 5, 6, 23),
        (49, 5, 1, 23),
        (2, 10, 10, 21),
        (35, 3, 8, 6),
    ];
    let mut engine = prepare(24, 49, &changes);
    fly(&mut engine, 24);
    assert_eq!((engine.player().x, engine.player().y), (0, 0));
    for (floor, x, y, tile) in changes {
        assert_eq!(engine.tile_at(floor, x, y), Some(tile));
    }
    engine
        .command(json!({"type":"use_item","item":"flying_orb","floor":44}))
        .unwrap();
    assert_eq!(engine.snapshot()["last_action"]["ok"], false);
    for (floor, x, y, tile) in changes {
        assert_eq!(engine.tile_at(floor, x, y), Some(tile));
    }
}

#[test]
fn flight_relocates_thief_only_with_exact_stair_bound_and_lower_destination() {
    for (from, to, highest, moves) in [
        (29, 28, 29, true),
        (27, 28, 29, true),
        (29, 28, 30, false),
        (28, 29, 29, false),
        (28, 28, 29, false),
    ] {
        let mut engine = prepare(
            from,
            highest,
            &[(29, 5, 3, 21), (29, 5, 2, 8), (29, 6, 1, 6)],
        );
        fly(&mut engine, to);
        for (x, y, expected) in [
            (5, 3, if moves { 6 } else { 21 }),
            (5, 2, if moves { 6 } else { 8 }),
            (6, 1, if moves { 21 } else { 6 }),
        ] {
            assert_eq!(
                engine.tile_at(29, x, y),
                Some(expected),
                "{from}->{to}, highest={highest}"
            );
        }
    }
}

#[test]
fn normal_descent_relocates_thief_but_descent_wing_does_not() {
    for highest in [29, 30] {
        let mut engine = prepare(
            29,
            highest,
            &[(29, 1, 0, 12), (29, 5, 3, 21), (29, 5, 2, 8), (29, 6, 1, 6)],
        );
        engine
            .command(json!({"type":"move","direction":"right"}))
            .unwrap();
        assert_eq!(engine.player().floor, 28);
        assert_eq!(
            engine.tile_at(29, 6, 1),
            Some(if highest == 29 { 21 } else { 6 })
        );
    }
    let mut engine = prepare(
        29,
        29,
        &[(28, 0, 0, 6), (29, 5, 3, 21), (29, 5, 2, 8), (29, 6, 1, 6)],
    );
    let mut save: Value = serde_json::from_str(&engine.save_json()).unwrap();
    save["player"]["inventory"] = json!(["down_wing"]);
    engine.load_json(&save.to_string()).unwrap();
    engine
        .command(json!({"type":"use_item","item":"down_wing"}))
        .unwrap();
    assert_eq!(engine.player().floor, 28);
    assert_eq!(engine.tile_at(29, 6, 1), Some(6));
}

#[test]
fn callbacks_are_opt_in_persist_and_do_not_leak_through_player_help() {
    let mut value = campaign();
    value["rules"]["flying_original_selection"] = json!(false);
    value["rules"]["flying_requires_stairs"] = json!(false);
    let mut engine = Engine::from_json(&value.to_string()).unwrap();
    let mut save: Value = serde_json::from_str(&engine.save_json()).unwrap();
    save["player"]["inventory"] = json!(["flying_orb"]);
    save["player"]["floor"] = json!(26);
    save["visited_floors"] = json!([1, 24, 26]);
    save["floors"]["25"][6 * 11 + 5] = json!(23);
    engine.load_json(&save.to_string()).unwrap();
    fly(&mut engine, 24);
    assert_eq!(engine.tile_at(25, 5, 6), Some(23));

    let mut engine = prepare(34, 40, &[(35, 3, 8, 6), (2, 10, 10, 21)]);
    fly(&mut engine, 36);
    let checkpoint = engine.runtime_checkpoint_json();
    engine.restore_runtime_checkpoint_json(&checkpoint).unwrap();
    assert_eq!(engine.tile_at(2, 10, 10), Some(6));
    let player = engine.player_observation().to_string();
    assert!(!player.contains("floor_travel_callbacks"));
    assert!(!player.contains("tile_sum"));
    assert!(!player.contains("tunnel"));
}

#[test]
fn malformed_authored_callbacks_are_rejected_at_import() {
    for callback in [
        json!({"when":{"type":"flight_confirm","typo":25},"writes":[]}),
        json!({"when":{"type":"flight_confirm"},"writes":[{"floor":25,"x":11,"y":0,"tile":6}]}),
        json!({"when":{"type":"flight_confirm"},"writes":[{"floor":25,"x":0,"y":0,"tile":65000}]}),
        json!({"when":{"type":"flight_confirm","highest_stair_floor":99},"writes":[]}),
        json!({"when":{"type":"stairs_down","from_floor":28,"to_floor":29},"writes":[]}),
        json!({"when":{"type":"upward_flight_preview","floor":35},"tile_sum":{"cells":[],"equals":27},"writes":[]}),
    ] {
        let mut value = campaign();
        value["rules"]["floor_travel_callbacks"] = json!([callback]);
        let error = match Engine::from_json(&value.to_string()) {
            Ok(_) => panic!("Malformed callback accepted"),
            Err(error) => error,
        };
        assert!(error.contains("floor_travel_callbacks"), "{error}");
    }
}
