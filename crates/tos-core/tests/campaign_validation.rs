//! Imports reject invalid behavior before a running session can use defaults.
use serde_json::{Value, json};
use tos_core::{Campaign, Engine};

fn fixture() -> Value {
    json!({
        "id":"validation", "title":"Validation", "width":2, "height":2,
        "start":{"floor":1,"x":0,"y":0,"hp":100,"attack":10,"defense":5},
        "floors":[{"id":1,"tiles":[6,19,6,6]}],
        "tiles":{
            "6":{"name":"Road","kind":"floor"},
            "19":{"name":"Merchant","kind":"npc"},
            "61":{"name":"Slime","kind":"enemy","enemy":"slime"}
        },
        "enemies":{"slime":{"name":"Slime","hp":20,"attack":8,"defense":1,"gold":2}},
        "rules":{"empty_tile":6}
    })
}

fn rejected(value: &Value) -> String {
    match Engine::from_json(&value.to_string()) {
        Ok(_) => panic!("Malformed campaign was accepted: {value}"),
        Err(error) => error,
    }
}

#[test]
fn typed_constructor_checks_invariants_before_creating_a_session() {
    let valid: Campaign = serde_json::from_value(fixture()).unwrap();
    Engine::new(valid.clone()).unwrap();

    let mut outside_map = valid.clone();
    outside_map.start.x = outside_map.width;
    let error = Engine::new(outside_map)
        .err()
        .expect("Constructor bypassed geometry validation");
    assert!(error.contains("start"), "{error}");

    let mut missing_enemy = valid.clone();
    missing_enemy.tiles.get_mut("61").unwrap().enemy = None;
    let error = Engine::new(missing_enemy)
        .err()
        .expect("Constructor accepted an unbound enemy tile");
    assert!(error.contains("tiles.61.enemy"), "{error}");

    let mut malformed_rule = valid;
    malformed_rule.rules = json!({"empty_tile":"6"});
    let error = Engine::new(malformed_rule)
        .err()
        .expect("Constructor bypassed rule type validation");
    assert!(error.contains("rules.empty_tile"), "{error}");
}

#[test]
fn wrong_typed_optional_rules_are_errors_instead_of_defaults() {
    for (key, bad_value) in [
        ("hero_attacks_first", json!("false")),
        ("empty_tile", json!("6")),
        ("altar_base_cost", json!(true)),
        ("cross_multiplier", json!(2.5)),
        ("area_scaling", json!({"max_floor":10,"multiplier":2})),
        ("backside", json!([])),
        ("presentation", json!("fast")),
        ("audio", json!(false)),
    ] {
        let mut value = fixture();
        value["rules"][key] = bad_value;
        let error = rejected(&value);
        assert!(error.contains(key), "{key}: {error}");
    }
    let mut value = fixture();
    value["rules"]["hero_attacks_first"] = Value::Null;
    assert!(rejected(&value).contains("hero_attacks_first"));
}

#[test]
fn nested_rule_types_ranges_and_references_are_checked() {
    for rules in [
        json!({"empty_tile":6,"backside":{"enabled":"true"}}),
        json!({"empty_tile":6,"area_scaling":[{"max_floor":"10","multiplier":2}]}),
        json!({"empty_tile":6,"area_scaling":[{"max_floor":10,"multiplier":0}]}),
        json!({"empty_tile":6,"area_scaling":[{"max_floor":10,"multiplier":2},{"max_floor":5,"multiplier":1}]}),
        json!({"empty_tile":6,"stair_links":{"1:up":2}}),
        json!({"empty_tile":6,"stair_links":{"1:sideways":1}}),
        json!({"empty_tile":6,"bomb_tile_ranges":[[61,"96"]]}),
        json!({"empty_tile":6,"bomb_tile_ranges":[[96,61]]}),
        json!({"empty_tile":6,"presentation":{"combat_strike_ms":"450"}}),
        json!({"empty_tile":6,"audio":{"floor_music":[{"min_floor":5,"max_floor":1,"file":"theme"}]}}),
    ] {
        let mut value = fixture();
        value["rules"] = rules;
        rejected(&value);
    }
}

#[test]
fn cleared_cells_require_an_ordinary_passage_tile() {
    for definition in [
        json!({"name":"Lava","kind":"lava"}),
        json!({"name":"Enemy","kind":"enemy","enemy":"slime"}),
        json!({"name":"Door","kind":"door","key":"yellow"}),
    ] {
        let mut value = fixture();
        value["tiles"]["6"] = definition;
        let error = rejected(&value);
        assert!(error.contains("rules.empty_tile"), "{error}");
    }

    Engine::from_json(&fixture().to_string()).unwrap();
    let mut default_zero = fixture();
    default_zero.as_object_mut().unwrap().remove("rules");
    default_zero["tiles"]["0"] = json!({"name":"Empty","kind":"empty"});
    Engine::from_json(&default_zero.to_string()).unwrap();

    let mut decoration = fixture();
    decoration["tiles"]["6"]["kind"] = json!("decoration");
    Engine::from_json(&decoration.to_string()).unwrap();
}

#[test]
fn unknown_behavior_tags_and_invalid_tile_fields_are_rejected() {
    let mut value = fixture();
    value["tiles"]["6"]["kind"] = json!("flor");
    rejected(&value);
    let mut value = fixture();
    value["enemies"]["slime"]["special"] = json!("undead_typo");
    rejected(&value);
    for (key, bad_value) in [
        ("key", json!("purple")),
        ("stat", json!("strength")),
        ("scaled", json!("yes")),
        ("disappear", json!(1)),
        ("target_floor", json!(2)),
        ("footprint", json!({"width":0,"height":1,"tiles":[61]})),
    ] {
        let mut value = fixture();
        value["tiles"]["61"][key] = bad_value;
        rejected(&value);
    }
}

#[test]
fn malformed_merged_interaction_is_not_silently_ignored() {
    for patch in [
        json!({"floor":1,"x":1,"y":0,"name":42}),
        json!({"floor":1,"x":1,"y":0,"kind":"npc_typo"}),
        json!({"floor":1,"x":1,"y":0,"effects":"give_item"}),
        json!({"floor":1,"x":1,"y":0,"offers":{}}),
        json!({"floor":4_294_967_297_i64,"x":1,"y":0}),
    ] {
        let mut value = fixture();
        value["interactions"] = json!([patch]);
        rejected(&value);
    }
}

#[test]
fn invalid_offer_and_custom_item_behavior_are_rejected() {
    for offer in [
        json!({"cost":"10","effects":[]}),
        json!({"cost_increment":-1,"effects":[]}),
        json!({"once":"true","effects":[]}),
        json!({"effects":{}}),
        json!({"effects":[],"conditions":"always"}),
        json!({"effects":[],"conditions":[{"type":"any","conditions":[{"type":"stat_at_least","stat":"attack","amount":"10"}]}]}),
        json!({"id":"leave","effects":[]}),
    ] {
        let mut value = fixture();
        value["tiles"]["19"]["offers"] = json!([offer]);
        rejected(&value);
    }
    for definition in [
        json!({"effects":"heal"}),
        json!({"effects":[{"type":"add_stat","stat":"hp","amount":"10"}]}),
        json!({"effects":[],"consumable":"false"}),
    ] {
        let mut value = fixture();
        value["items"] = json!({"potion":definition});
        rejected(&value);
    }
}

#[test]
fn triggers_and_nested_effect_conditions_are_validated_recursively() {
    for event in [
        json!({"trigger":{"type":"step","floor":"1"},"effects":[]}),
        json!({"trigger":{"type":"step","tile":999},"effects":[]}),
        json!({"trigger":{"type":"step"},"once":"false","effects":[]}),
        json!({"trigger":{"type":"step"},"effects":null}),
        json!({"trigger":{"type":"step"},"effects":[{"type":"flag","flag":"ready","conditions":{}}]}),
        json!({"trigger":{"type":"step"},"effects":[{"type":"flag","flag":"ready","conditions":[{"type":"any","conditions":[{"type":"tile","x":0,"y":0,"tile":"6"}]}]}]}),
    ] {
        let mut value = fixture();
        value["events"] = json!([event]);
        rejected(&value);
    }
}

#[test]
fn duplicate_event_offer_and_interaction_keys_are_rejected() {
    let mut value = fixture();
    value["events"] = json!([
        {"id":"same","trigger":{"type":"step"},"effects":[]},
        {"id":"same","trigger":{"type":"bump"},"effects":[]}
    ]);
    rejected(&value);
    let mut value = fixture();
    value["tiles"]["19"]["offers"] = json!([{"id":"same","effects":[]},{"id":"same","effects":[]}]);
    rejected(&value);
    let mut value = fixture();
    value["interactions"] = json!([{"floor":1,"x":1,"y":0},{"floor":1,"x":1,"y":0}]);
    rejected(&value);
}

#[test]
fn metadata_and_original_behavior_spellings_survive_round_trip() {
    let mut value = fixture();
    value["author"] = json!({"name":"Example","tools":["editor"]});
    value["rules"]["research"] = json!({"unrecognized":true});
    value["tiles"]["19"]["source"] = json!("Recovered address");
    value["enemies"]["slime"]["special"] = json!("");
    value["tiles"]["19"]["offers"] =
        json!([{"id":"gift","effects":[{"type":"give_item","item":"custom_badge"}]}]);
    let campaign: Campaign = serde_json::from_value(value).unwrap();
    campaign.validate().unwrap();
    let canonical = serde_json::to_value(&campaign).unwrap();
    assert_eq!(canonical["author"]["name"], "Example");
    assert_eq!(canonical["rules"]["research"]["unrecognized"], true);
    assert_eq!(canonical["tiles"]["19"]["source"], "Recovered address");
    assert_eq!(canonical["enemies"]["slime"]["special"], "");
    let reparsed: Campaign = serde_json::from_value(canonical.clone()).unwrap();
    assert_eq!(serde_json::to_value(reparsed).unwrap(), canonical);
}

#[test]
fn typed_campaign_preserves_the_published_save_fingerprint() {
    let campaign: Campaign =
        serde_json::from_str(include_str!("../../../data/campaign.json")).unwrap();
    let engine = Engine::new(campaign).unwrap();
    let saved: Value = serde_json::from_str(&engine.save_json()).unwrap();
    // Behavior enums must preserve their canonical JSON spellings. Explicit
    // item and animation fidelity rules revise the bundled campaign. The GUI keeps
    // known previous revisions recoverable through its tested migration.
    assert_eq!(saved["campaign_fingerprint"], "abd9d284f2e9b303");
}
