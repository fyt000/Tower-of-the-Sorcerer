//! Item instructions must describe playable commands without disclosing scripts.
use serde_json::{Value, json};
use tos_core::{Command, Engine};

fn fixture(inventory: &[&str]) -> Value {
    json!({
        "id":"item-help","title":"Item help fixture","width":3,"height":3,
        "start":{"floor":2,"x":0,"y":0,"hp":100,"attack":10,"defense":5,
            "inventory":inventory},
        "floors":[
            {"id":1,"tiles":[0,0,0,0,0,0,0,0,0]},
            {"id":2,"tiles":[0,0,0,0,0,0,0,0,0]},
            {"id":3,"tiles":[0,0,0,0,0,0,0,0,0]}
        ],
        "tiles":{
            "0":{"name":"Road","kind":"floor"},
            "8":{"name":"Brick","kind":"wall"},
            "11":{"name":"Up stair","kind":"stairs_up"},
            "14":{"name":"Blade","kind":"equipment","stat":"attack","amount":5,"item":"blade"}
        },
        "enemies":{},"rules":{"flying_requires_stairs":false}
    })
}

fn game(value: Value) -> Engine {
    Engine::from_json(&value.to_string()).unwrap()
}

fn owned_item(engine: &Engine, item: &str) -> Value {
    let observation = engine.player_observation();
    let visible = observation["inventory_items"]
        .as_array()
        .unwrap()
        .iter()
        .chain(observation["equipment"].as_object().unwrap().values())
        .find(|visible| visible["id"] == item)
        .unwrap()
        .clone();
    let snapshot = engine.snapshot();
    let internal = snapshot["inventory_items"]
        .as_array()
        .unwrap()
        .iter()
        .chain(snapshot["equipment"].as_object().unwrap().values())
        .find(|visible| visible["id"] == item)
        .unwrap();
    assert_eq!(
        visible["usage"], internal["usage"],
        "GUI and MCP should share help"
    );
    visible
}

fn contains_restriction(usage: &Value, needle: &str) -> bool {
    usage["restrictions"]
        .as_array()
        .unwrap()
        .iter()
        .any(|restriction| restriction.as_str().unwrap().contains(needle))
}

#[test]
fn all_builtin_aliases_offer_commands_with_the_real_input_schema() {
    let active = [
        "wisdom_orb",
        "orb_of_flying",
        "floor_wand",
        "flying_orb",
        "mattock",
        "magic_key",
        "bomb",
        "holy_water",
        "elixir",
        "orb_of_ascending",
        "orb_of_descending",
        "up_wing",
        "down_wing",
        "warp_staff",
        "super_mattock",
        "snow_crystal",
    ];
    let passive = [
        "hero_orb",
        "monster_book",
        "cross",
        "dragon_slayer",
        "lucky_gold",
        "sacred_shield",
    ];
    let inventory: Vec<&str> = active.iter().chain(passive.iter()).copied().collect();
    let engine = game(fixture(&inventory));
    for item in active {
        let visible = owned_item(&engine, item);
        let usage = &visible["usage"];
        assert_eq!(visible["usable"], true, "{item}");
        assert_eq!(usage["activation"], "use_item", "{item}");
        assert_eq!(usage["command"]["item"], item);
        Command::from_value(usage["command"].clone()).unwrap();
    }
    for item in passive {
        let visible = owned_item(&engine, item);
        assert_eq!(visible["usable"], false, "{item}");
        assert_eq!(visible["usage"]["activation"], "passive", "{item}");
        assert_eq!(visible["usage"]["consumable"], false, "{item}");
        assert!(visible["usage"].get("command").is_none(), "{item}");
    }
}

#[test]
fn flight_help_tracks_runtime_stair_rules_and_can_be_submitted() {
    for requires_stairs in [true, false] {
        let mut value = fixture(&["floor_wand"]);
        value["rules"]["flying_requires_stairs"] = json!(requires_stairs);
        if requires_stairs {
            value["floors"][1]["tiles"][1] = json!(11);
        }
        let mut engine = game(value);
        let usage = owned_item(&engine, "floor_wand")["usage"].clone();
        assert_eq!(usage["consumable"], false);
        assert_eq!(usage["target_floor"], "visited_floor");
        assert_eq!(usage["command"]["floor"], 2);
        assert_eq!(contains_restriction(&usage, "staircase"), requires_stairs);
        engine.command(usage["command"].clone()).unwrap();
        assert_eq!(engine.snapshot()["last_action"]["ok"], true);
        assert!(engine.player().inventory.contains(&"floor_wand".into()));
    }
}

#[test]
fn combat_help_uses_campaign_multipliers_and_guard() {
    let mut value = fixture(&["cross", "dragon_slayer"]);
    value["rules"]["cross_multiplier"] = json!(3);
    value["rules"]["dragon_slayer_multiplier"] = json!(4);
    value["rules"]["base_attack_guard"] = json!(false);
    let engine = game(value.clone());
    assert!(
        owned_item(&engine, "cross")["usage"]["description"]
            .as_str()
            .unwrap()
            .contains("by 3 against undead")
    );
    assert!(
        owned_item(&engine, "dragon_slayer")["usage"]["description"]
            .as_str()
            .unwrap()
            .contains("by 4 against dragons")
    );
    assert!(!contains_restriction(
        &owned_item(&engine, "cross")["usage"],
        "Base attack"
    ));
    value["rules"]["base_attack_guard"] = json!(true);
    assert!(contains_restriction(
        &owned_item(&game(value), "cross")["usage"],
        "Base attack"
    ));
}

#[test]
fn charged_staff_help_matches_blocked_uses_and_final_consumption() {
    let mut value = fixture(&["warp_staff"]);
    value["floors"][1]["tiles"][8] = json!(8);
    let mut engine = game(value);
    let usage = owned_item(&engine, "warp_staff")["usage"].clone();
    assert_eq!(usage["remaining_charges"], 3);
    assert!(contains_restriction(&usage, "even if blocked"));
    assert!(contains_restriction(&usage, "final charge consumes"));
    for remaining in [2, 1] {
        engine.command(usage["command"].clone()).unwrap();
        assert_eq!((engine.player().x, engine.player().y), (0, 0));
        assert_eq!(
            owned_item(&engine, "warp_staff")["usage"]["remaining_charges"],
            remaining
        );
    }
    engine.command(usage["command"].clone()).unwrap();
    assert!(!engine.player().inventory.contains(&"warp_staff".into()));
}

#[test]
fn healing_and_wing_help_match_consumption_and_ordinary_passage_requirement() {
    for item in ["holy_water", "elixir"] {
        let mut engine = game(fixture(&[item]));
        let usage = owned_item(&engine, item)["usage"].clone();
        assert_eq!(usage["description"], "Adds attack × 10 + defense × 5 HP.");
        engine.command(usage["command"].clone()).unwrap();
        assert_eq!(engine.player().hp, 225);
        assert!(engine.player().inventory.is_empty());
    }
    for (item, destination) in [
        ("up_wing", 3),
        ("orb_of_ascending", 3),
        ("down_wing", 1),
        ("orb_of_descending", 1),
    ] {
        let mut value = fixture(&[item]);
        let destination_index = (destination - 1) as usize;
        value["floors"][destination_index]["tiles"][0] = json!(11);
        let mut engine = game(value.clone());
        let usage = owned_item(&engine, item)["usage"].clone();
        assert!(contains_restriction(&usage, "ordinary passage"));
        engine.command(usage["command"].clone()).unwrap();
        assert_eq!(engine.player().floor, 2);
        assert!(engine.player().inventory.contains(&item.into()));
        value["floors"][destination_index]["tiles"][0] = json!(0);
        let mut engine = game(value);
        engine.command(usage["command"].clone()).unwrap();
        assert_eq!(engine.player().floor, destination);
        assert!(engine.player().inventory.is_empty());
    }
}

#[test]
fn custom_help_hides_scripts_and_unowned_catalogs_and_marks_unknown_tags_unusable() {
    let mut value = fixture(&["quest_badge", "blade", "tonic", "empty_token"]);
    value["items"] = json!({
        "tonic":{"description":"Restore some health; reusable.","consumable":false,
            "private_answer":"Never expose this answer", "effects":[
                {"type":"add_stat","stat":"hp","amount":5,
                    "conditions":[{"type":"flag","flag":"private_riddle_answer"}]}
            ]},
        "empty_token":{"consumable":true},
        "unowned_secret":{"description":"A secret ability","effects":[]}
    });
    let mut engine = game(value);
    let unknown = owned_item(&engine, "quest_badge");
    assert_eq!(unknown["usable"], false);
    assert_eq!(unknown["usage"]["activation"], "none");
    assert_eq!(
        owned_item(&engine, "blade")["usage"]["activation"],
        "passive"
    );
    let tonic = owned_item(&engine, "tonic");
    assert_eq!(tonic["usable"], true);
    assert_eq!(tonic["usage"]["consumable"], false);
    assert_eq!(
        tonic["usage"]["description"],
        "Restore some health; reusable."
    );
    let text = engine.player_observation()["inventory_items"].to_string();
    for hidden in [
        "private_answer",
        "Never expose",
        "private_riddle_answer",
        "conditions",
        "effects",
        "unowned_secret",
    ] {
        assert!(!text.contains(hidden), "help leaked {hidden}");
    }
    let empty = owned_item(&engine, "empty_token");
    assert_eq!(empty["usable"], true);
    assert_eq!(
        empty["usage"]["description"],
        "Using this item has no configured effect."
    );
    engine.command(empty["usage"]["command"].clone()).unwrap();
    assert!(!engine.player().inventory.contains(&"empty_token".into()));
}
