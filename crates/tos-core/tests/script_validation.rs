//! Script import is a trust boundary: malformed authoring data must fail before
//! an engine can evaluate conditions or mutate the world.
use serde_json::{Value, json};
use tos_core::Engine;

fn campaign() -> Value {
    json!({
        "id":"script-validation", "title":"Script boundary", "width":3,"height":3,
        "start":{"floor":1,"x":0,"y":0,"hp":100,"attack":10,"defense":5,"gold":10},
        "floors":[{"id":1,"tiles":[6,6,61,6,6,6,6,6,6]}],
        "rules":{"empty_tile":6},
        "tiles":{"6":{"name":"Road","kind":"floor"},"61":{"name":"Slime","kind":"enemy","enemy":"slime"}},
        "enemies":{"slime":{"name":"Slime","hp":20,"attack":8,"defense":1,"gold":2}},
        "events":[]
    })
}

fn event(effects: Value) -> Value {
    json!({"id":"script","trigger":{"type":"step","floor":1,"x":1,"y":0},"effects":effects})
}

fn rejects(value: &Value, contains: &str) {
    let error = match Engine::from_json(&value.to_string()) {
        Ok(_) => panic!("malformed campaign was accepted: {value}"),
        Err(error) => error,
    };
    assert!(
        error.contains(contains),
        "{error:?} should identify {contains:?}"
    );
}

#[test]
fn malformed_conditions_never_default_to_true() {
    for conditions in [
        Value::Null,
        json!(true),
        json!({"type":"flag","flag":"gate"}),
        json!("always"),
    ] {
        let mut value = campaign();
        let mut script = event(json!([]));
        script["conditions"] = conditions;
        value["events"] = json!([script]);
        rejects(&value, "events[0]");
    }
    let mut value = campaign();
    value["events"] = json!([event(json!([{
        "type":"add_stat","stat":"gold","amount":99,
        "conditions":[{"type":"any","conditions":{"type":"flag","flag":"gate"}}]
    }]))]);
    rejects(&value, "events[0]");
}

#[test]
fn required_parameters_and_exact_types_are_checked_on_import() {
    for effect in [
        json!({"type":"set_stat","stat":"hp"}),
        json!({"type":"multiply_stat","stat":"hp","numerator":103,"denominator":0}),
        json!({"type":"multiply_stat","stat":"hp","numerator":103,"denominator":-1}),
        json!({"type":"multiply_enemy","enemy":"slime","numerator":1,"denominator":0}),
        json!({"type":"multiply_enemy","enemy":"unknown","numerator":1,"denominator":10}),
        json!({"type":"multiply_enemy","enemy":"slime","numerator":"10","denominator":1}),
        json!({"type":"add_stat","stat":"gold","amount":"100"}),
        json!({"type":"give_item"}),
        json!({"type":"set_charges","item":"quest_token","charges":4294967296_u64}),
        json!({"type":"set_enemy","enemy":"slime"}),
        json!({"type":"set_enemy","enemy":"slime","hp":0}),
        json!({"type":"battle_at","floor":1,"x":2}),
        json!({"type":"wait"}),
        json!({"type":"flag","flag":"gate","value":"false"}),
        json!({"type":"cinematic","kind":"magic","duration_ms":"120"}),
        json!({"type":"cinematic","kind":"magic","frames":["166"]}),
        json!({"type":"cinematic","kind":"magic","duration_ms":100,"sound_offsets_ms":[101]}),
    ] {
        let mut value = campaign();
        value["events"] = json!([event(json!([effect]))]);
        rejects(&value, "events[0]");
    }
}

#[test]
fn misspelled_operations_conditions_and_optional_fields_are_rejected() {
    for effect in [
        json!({"type":"add_stats","stat":"gold","amount":1}),
        json!({"type":"add_stat","stat":"golds","amount":1}),
        json!({"type":"add_stat","stat":"gold","amount":1,"condition":[]}),
        json!({"type":"flag","flag":"gate","vale":false}),
        json!({"type":"add_stat","stat":"gold","amount":1,"conditions":[{"type":"flagg","flag":"gate"}]}),
    ] {
        let mut value = campaign();
        value["events"] = json!([event(json!([effect]))]);
        rejects(&value, "events[0]");
    }
    let mut value = campaign();
    value["events"] = json!([{"trigger":{"type":"steppe"},"effects":[]}]);
    rejects(&value, "events[0]");
}

#[test]
fn script_references_and_positions_are_checked_before_execution() {
    for effect in [
        json!({"type":"set_tile","floor":2,"x":0,"y":0,"tile":6}),
        json!({"type":"set_tile","floor":1,"x":3,"y":0,"tile":6}),
        json!({"type":"set_tile","floor":1,"x":0,"y":0,"tile":7}),
        json!({"type":"move_tile","floor":1,"from_x":99,"from_y":0,"x":0,"y":0}),
        json!({"type":"set_enemy","enemy":"unknown","attack":1}),
        json!({"type":"set_visited","floors":[1,2]}),
    ] {
        let mut value = campaign();
        value["events"] = json!([event(json!([effect]))]);
        rejects(&value, "events[0]");
    }
    let mut value = campaign();
    value["events"] = json!([{
        "trigger":{"type":"step","tile":65536},"effects":[]
    }]);
    rejects(&value, "events[0]");
}

#[test]
fn typed_nested_conditions_control_world_mutations() {
    let mut value = campaign();
    value["events"] = json!([{
        "id":"conditional","once":false,"trigger":{"type":"step","floor":1,"x":1,"y":0},
        "conditions":[{"type":"any","conditions":[
            {"type":"flag","flag":"awarded","value":false},
            {"type":"stat_at_least","stat":"gold","amount":100}
        ]}],
        "effects":[{"type":"add_stat","stat":"attack","amount":3},{"type":"flag","flag":"awarded"}]
    }]);
    let mut engine = Engine::from_json(&value.to_string()).unwrap();
    engine
        .command(json!({"type":"move","direction":"right"}))
        .unwrap();
    assert_eq!(engine.player().attack, 13);
    engine
        .command(json!({"type":"move","direction":"left"}))
        .unwrap();
    engine
        .command(json!({"type":"move","direction":"right"}))
        .unwrap();
    assert_eq!(
        engine.player().attack,
        13,
        "both nested alternatives now fail"
    );
}

#[test]
fn alternative_trigger_positions_share_one_persistent_event_count() {
    let mut value = campaign();
    value["events"] = json!([{"id":"two_entrances","trigger":{"type":"step","floor":1,
        "positions":[{"x":1,"y":0},{"x":0,"y":1}]},
        "effects":[{"type":"add_stat","stat":"attack","amount":3}]}]);
    let mut engine = Engine::from_json(&value.to_string()).unwrap();
    for direction in ["right", "left"] {
        engine
            .command(json!({"type":"move","direction":direction}))
            .unwrap();
    }
    let saved = engine.save_json();
    engine.load_json(&saved).unwrap();
    engine
        .command(json!({"type":"move","direction":"down"}))
        .unwrap();
    assert_eq!(engine.player().attack, 13);
    let saved: Value = serde_json::from_str(&engine.save_json()).unwrap();
    assert_eq!(saved["event_counts"]["two_entrances"], 1);
}

#[test]
fn quest_tags_and_renderer_payloads_remain_extensible() {
    let mut value = campaign();
    value["events"] = json!([event(json!([
        {"type":"give_item","item":"custom_quest_badge"},
        {"type":"cinematic","kind":"custom_renderer_scene","contrast":0.5,"asset":"custom-scene","duration_ms":80}
    ]))]);
    let mut engine = Engine::from_json(&value.to_string()).unwrap();
    engine
        .command(json!({"type":"move","direction":"right"}))
        .unwrap();
    assert!(
        engine
            .player()
            .inventory
            .iter()
            .any(|item| item == "custom_quest_badge")
    );
    let state = engine.snapshot();
    let timeline = state["last_action"]["presentation"].as_array().unwrap();
    let scene = timeline
        .iter()
        .find(|effect| effect["type"] == "cinematic")
        .unwrap();
    assert_eq!(scene["kind"], "custom_renderer_scene");
    assert_eq!(scene["contrast"], 0.5);
}

fn zero_tile_campaign() -> Value {
    json!({
        "id":"zero-road","title":"Custom passage IDs","width":3,"height":3,
        "start":{"floor":2,"x":0,"y":0,"hp":100,"attack":10,"defense":5,
            "inventory":["warp_staff","up_wing","down_wing"]},
        "floors":[
            {"id":1,"tiles":[0,0,0,0,0,0,0,0,0]},
            {"id":2,"tiles":[0,0,0,0,0,0,0,0,0]},
            {"id":3,"tiles":[0,0,0,0,0,0,0,0,0]}
        ],
        "tiles":{"0":{"name":"Passage","kind":"floor"},"1":{"name":"Wall","kind":"wall"}},
        "enemies":{},"rules":{}
    })
}

#[test]
fn warp_staff_lands_on_the_default_empty_tile_in_custom_campaigns() {
    let mut engine = Engine::from_json(&zero_tile_campaign().to_string()).unwrap();
    engine
        .command(json!({"type":"use_item","item":"warp_staff"}))
        .unwrap();
    assert_eq!(
        (engine.player().floor, engine.player().x, engine.player().y),
        (2, 2, 2)
    );
    assert_eq!(engine.player().item_charges["warp_staff"], 2);
    assert!(
        engine
            .player()
            .inventory
            .iter()
            .any(|item| item == "warp_staff")
    );

    // The empty-tile correction must not make an occupied destination valid.
    let mut blocked = zero_tile_campaign();
    blocked["floors"][1]["tiles"][8] = json!(1);
    let mut engine = Engine::from_json(&blocked.to_string()).unwrap();
    engine
        .command(json!({"type":"use_item","item":"warp_staff"}))
        .unwrap();
    assert_eq!((engine.player().x, engine.player().y), (0, 0));
    assert_eq!(
        engine.player().item_charges["warp_staff"],
        2,
        "original blocked-warp behavior still spends a charge"
    );
}

#[test]
fn both_wings_land_on_the_default_empty_tile_and_consume_themselves() {
    let source = zero_tile_campaign().to_string();
    for (item, destination) in [("up_wing", 3), ("down_wing", 1)] {
        let mut engine = Engine::from_json(&source).unwrap();
        engine
            .command(json!({"type":"use_item","item":item}))
            .unwrap();
        assert_eq!(
            (engine.player().floor, engine.player().x, engine.player().y),
            (destination, 0, 0)
        );
        assert!(!engine.player().inventory.iter().any(|entry| entry == item));
        let state = engine.snapshot();
        assert!(
            state["visited_floors"]
                .as_array()
                .unwrap()
                .contains(&json!(destination))
        );
        assert!(
            state["last_action"]["presentation"]
                .as_array()
                .unwrap()
                .iter()
                .any(|effect| effect["type"] == "floor" && effect["to"] == destination)
        );
    }

    let mut blocked = zero_tile_campaign();
    blocked["floors"][2]["tiles"][0] = json!(1);
    let mut engine = Engine::from_json(&blocked.to_string()).unwrap();
    engine
        .command(json!({"type":"use_item","item":"up_wing"}))
        .unwrap();
    assert_eq!(engine.player().floor, 2);
    assert!(
        engine
            .player()
            .inventory
            .iter()
            .any(|item| item == "up_wing")
    );
    assert_eq!(engine.snapshot()["last_action"]["ok"], false);
}

#[test]
fn tile_teleports_keep_their_destination_without_an_extra_step_trigger() {
    for destination_floor in [1, 2] {
        let mut value = campaign();
        value["floors"]
            .as_array_mut()
            .unwrap()
            .push(json!({"id":2,"tiles":[6,6,6,6,6,6,6,6,6]}));
        value["tiles"]["50"] = json!({"name":"Portal","kind":"trigger","effects":[
            {"type":"teleport","floor":destination_floor,"x":2,"y":2}
        ]});
        value["floors"][0]["tiles"][1] = json!(50);
        value["events"] = json!([{
            "id":"spurious_arrival_step","trigger":{"type":"step","floor":destination_floor,"x":2,"y":2},
            "effects":[{"type":"flag","flag":"stepped_after_teleport"}]
        }]);
        let mut engine = Engine::from_json(&value.to_string()).unwrap();
        engine
            .command(json!({"type":"move","direction":"right"}))
            .unwrap();
        assert_eq!(
            (engine.player().floor, engine.player().x, engine.player().y),
            (destination_floor, 2, 2)
        );
        let state = engine.snapshot();
        assert_eq!(state["steps"], 1);
        assert!(
            !state["flags"]
                .as_array()
                .unwrap()
                .contains(&json!("stepped_after_teleport"))
        );
        let timeline = state["last_action"]["presentation"].as_array().unwrap();
        assert!(
            timeline
                .iter()
                .any(|cue| cue["type"] == "floor" && cue["x"] == 2 && cue["y"] == 2)
        );
        assert!(
            !timeline.iter().any(|cue| cue["type"] == "move"),
            "ordinary walking must not overwrite the portal"
        );
    }
}

#[test]
fn a_winning_step_keeps_its_authored_tail_and_cannot_lose_to_hazards() {
    let mut value = campaign();
    value["start"]["x"] = json!(1);
    value["start"]["y"] = json!(2);
    value["enemies"]["mage"] =
        json!({"name":"Mage","hp":20,"attack":8,"defense":1,"gold":2,"special":"magician_a"});
    value["tiles"]["2"] = json!({"name":"Mage","kind":"enemy","enemy":"mage"});
    value["floors"][0]["tiles"][3] = json!(2);
    value["floors"][0]["tiles"][5] = json!(2);
    value["events"] = json!([
        {"id":"ending","trigger":{"type":"step","floor":1,"x":1,"y":1},"effects":[
            {"type":"win"},{"type":"message","text":"Authored ending dialogue"},
            {"type":"flag","flag":"same_event_reward"}
        ]},
        {"id":"after_ending","trigger":{"type":"step","floor":1,"x":1,"y":1},"effects":[
            {"type":"flag","flag":"should_not_run"}
        ]}
    ]);
    let mut engine = Engine::from_json(&value.to_string()).unwrap();
    engine
        .command(json!({"type":"move","direction":"up"}))
        .unwrap();
    let state = engine.snapshot();
    assert_eq!(state["status"], "won");
    assert_eq!(
        engine.player().hp,
        100,
        "terminal victory must not take mage damage"
    );
    assert_eq!((engine.player().x, engine.player().y), (1, 1));
    assert!(
        state["flags"]
            .as_array()
            .unwrap()
            .contains(&json!("same_event_reward"))
    );
    assert!(
        !state["flags"]
            .as_array()
            .unwrap()
            .contains(&json!("should_not_run"))
    );
    assert!(
        state["last_action"]["presentation"]
            .as_array()
            .unwrap()
            .iter()
            .any(|cue| cue["type"] == "dialogue" && cue["text"] == "Authored ending dialogue")
    );
    let save: Value = serde_json::from_str(&engine.save_json()).unwrap();
    assert_eq!(save["event_counts"]["ending"], 1);
    assert!(save["event_counts"].get("after_ending").is_none());
}

#[test]
fn a_fatal_event_does_not_consume_later_matching_event_records() {
    let mut value = campaign();
    value["enemies"]["slime"]["attack"] = json!(1000);
    value["events"] = json!([
        {"id":"fatal","trigger":{"type":"step","floor":1,"x":1,"y":0},"effects":[
            {"type":"battle_at","floor":1,"x":2,"y":0},
            {"type":"message","text":"Cannot speak after defeat"}
        ]},
        {"id":"after_defeat","trigger":{"type":"step","floor":1,"x":1,"y":0},"effects":[
            {"type":"flag","flag":"should_not_run"}
        ]}
    ]);
    let mut engine = Engine::from_json(&value.to_string()).unwrap();
    engine
        .command(json!({"type":"move","direction":"right"}))
        .unwrap();
    let state = engine.snapshot();
    assert_eq!(state["status"], "lost");
    assert!(
        !state["last_action"]["presentation"]
            .as_array()
            .unwrap()
            .iter()
            .any(|cue| cue["text"] == "Cannot speak after defeat")
    );
    let save: Value = serde_json::from_str(&engine.save_json()).unwrap();
    assert_eq!(save["event_counts"]["fatal"], 1);
    assert!(save["event_counts"].get("after_defeat").is_none());
}

#[test]
fn decorative_passages_are_valid_click_route_intermediates() {
    let mut value = zero_tile_campaign();
    value["height"] = json!(1);
    for floor in value["floors"].as_array_mut().unwrap() {
        floor["tiles"] = json!([0, 2, 0]);
    }
    value["tiles"]["2"] = json!({"name":"Patterned passage","kind":"decoration"});
    let engine = Engine::from_json(&value.to_string()).unwrap();
    assert_eq!(engine.path_to(2, 0), vec!["right", "right"]);
}

#[test]
fn wings_and_stairs_stop_safely_at_extreme_floor_ids() {
    for (floor, item, stair_kind) in [
        (i32::MAX, "up_wing", "stairs_up"),
        (i32::MIN, "down_wing", "stairs_down"),
    ] {
        let mut value = zero_tile_campaign();
        value["start"]["floor"] = json!(floor);
        value["floors"] = json!([{"id":floor,"tiles":[0,2,0,0,0,0,0,0,0]}]);
        value["tiles"]["2"] = json!({"name":"Edge staircase","kind":stair_kind});
        let mut engine = Engine::from_json(&value.to_string()).unwrap();
        engine
            .command(json!({"type":"use_item","item":item}))
            .unwrap();
        assert_eq!(
            (engine.player().floor, engine.player().x, engine.player().y),
            (floor, 0, 0)
        );
        assert!(engine.player().inventory.iter().any(|entry| entry == item));
        assert_eq!(engine.snapshot()["last_action"]["ok"], false);
        engine
            .command(json!({"type":"move","direction":"right"}))
            .unwrap();
        assert_eq!(
            (engine.player().floor, engine.player().x, engine.player().y),
            (floor, 0, 0)
        );
        assert_eq!(engine.snapshot()["last_action"]["ok"], false);
    }
}
