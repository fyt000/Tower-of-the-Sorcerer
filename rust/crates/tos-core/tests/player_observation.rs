//! The player view must preserve discovery without exposing authoring metadata.
use serde_json::{Value, json};
use tos_core::{Command, Direction, Engine};

fn fixture() -> Engine {
    Engine::from_json(&json!({
        "id":"observation-fixture","title":"Observation fixture","width":6,"height":2,
        "start":{"floor":1,"x":0,"y":1,"hp":100,"attack":10,"defense":3,"gold":5,"keys":{"yellow":0,"blue":0,"red":0}},
        "rules":{"empty_tile":6,"forecast_requires_item":"hero_orb"},
        "floors":[{"id":1,"title":"Entrance","tiles":[8,9,10,19,61,29,6,6,6,6,6,162]},
            {"id":2,"title":"A secret destination","tiles":[6,6,6,6,6,6,6,6,6,6,6,6]}],
        "tiles":{
            "6":{"name":"Road","kind":"floor","sprite":{"x":0,"y":0,"w":40,"h":40}},
            "8":{"name":"Brick wall","kind":"wall","sprite":{"x":280,"y":0,"w":40,"h":40}},
            "9":{"name":"Secret wall","kind":"hidden_wall","sprite":{"x":320,"y":0,"w":40,"h":40}},
            "10":{"name":"Scripted wall","kind":"wall","sprite":{"x":360,"y":0,"w":40,"h":40}},
            "19":{"name":"Old man","kind":"npc","text":"The walls can remember footsteps.",
                "source":"private NPC address","dialogue_ids":[123],"after_text":{"flag":"secret_answer","text":"Unseen answer"},
                "offers":[{"id":"gift","label":"Receive the orb","cost":0,"once":true,"effects":[{"type":"give_item","item":"hero_orb"}]},
                    {"id":"expensive","label":"An expensive gift","cost":10,"effects":[]}]},
            "61":{"name":"Slime","kind":"enemy","enemy":"private_monster_key","sprite":61},
            "29":{"name":"Yellow key","kind":"key","key":"yellow","amount":1},
            "162":{"name":"Private trigger location","kind":"trigger","source":"private trigger source",
                "sprite":{"x":0,"y":0,"w":40,"h":40}}
        },
        "enemies":{"private_monster_key":{"name":"Slime","hp":35,"attack":5,"defense":1,"gold":1}},
        "events":[{"id":"secret_event_answer","once":true,"trigger":{"type":"bump","floor":1,"x":2,"y":0},
            "effects":[{"type":"flag","flag":"private_solution_flag"},
                {"type":"message","text":"The old stones whisper: seek the missing hour.","dialogue_id":555},
                {"type":"set_tile","floor":2,"x":0,"y":0,"tile":9},
                {"type":"set_tile","floor":1,"x":2,"y":0,"tile":9},
                {"type":"cinematic","kind":"private_scene_key","text":"A visible inscription.",
                    "source":"private provenance","answer":"private_solution","underlying_tile":9}]}]
    }).to_string()).unwrap()
}

fn move_to(game: &mut Engine, direction: Direction) {
    game.execute(Command::Move { direction }).unwrap();
}

#[test]
fn hidden_and_scripted_bricks_have_the_same_public_identity_until_bumped() {
    let mut game = fixture();
    let view = game.player_observation();
    assert_eq!(
        &view["tiles"].as_array().unwrap()[0..3],
        &[json!(8), json!(8), json!(8)]
    );
    for x in 0..3 {
        let tile = game.inspect_player_tile(x, 0);
        assert_eq!(tile["id"], 8);
        assert_eq!(tile["name"], "Brick wall");
        assert_eq!(tile["kind"], "wall");
        assert_eq!(tile["sprite"], view["tile_defs"]["8"]["sprite"]);
    }
    assert!(view["tile_defs"].get("9").is_none());
    assert!(view["tile_defs"].get("10").is_none());
    assert_eq!(view["tiles"][11], 6, "a scripted road is an ordinary road");
    // Diagnostic snapshots remain deliberately complete for UI/editor callers.
    assert_eq!(game.snapshot()["tiles"][1], 9);
    assert_eq!(game.inspect(1, 0)["id"], 9);
    move_to(&mut game, Direction::Right);
    move_to(&mut game, Direction::Up);
    assert_eq!((game.player().x, game.player().y), (1, 0));
    assert_eq!(game.inspect_player_tile(1, 0)["kind"], "floor");
    assert_eq!(
        game.player_observation()["last_action"]["message"],
        "You discovered a hidden passage."
    );
}

#[test]
fn player_view_contains_only_observed_definitions_and_no_script_metadata() {
    let view = fixture().player_observation();
    assert!(view.get("flags").is_none());
    assert!(view.get("backside_multiplier").is_none());
    assert_eq!(view["floors"].as_array().unwrap().len(), 1);
    assert_eq!(view["floors"][0]["id"], 1);
    let serialized = view.to_string();
    for secret in [
        "private NPC address",
        "private_monster_key",
        "secret_answer",
        "Unseen answer",
        "secret_event_answer",
        "private_solution_flag",
        "Private trigger location",
        "A secret destination",
        "The walls can remember footsteps.",
    ] {
        assert!(!serialized.contains(secret), "leaked {secret}");
    }
    assert!(view["tile_defs"]["19"].get("text").is_none());
    assert!(view["tile_defs"]["19"].get("offers").is_none());
    assert_eq!(view["tile_defs"]["29"]["key"], "yellow");
    assert_eq!(view["tile_defs"]["29"]["amount"], 1);
    assert_eq!(view["coordinates"]["indexing"], "tiles[y * width + x]");
}

#[test]
fn dialogue_choices_and_orb_forecasts_become_available_through_played_actions() {
    let mut game = fixture();
    assert!(game.inspect_player_tile(4, 0)["enemy"].is_null());
    assert_eq!(game.inspect_player_tile(4, 0)["details_locked"], true);
    assert_eq!(game.player_observation()["enemies"], json!([]));
    for _ in 0..3 {
        move_to(&mut game, Direction::Right);
    }
    move_to(&mut game, Direction::Up);
    let dialogue = game.player_observation()["pending_interaction"].clone();
    assert_eq!(dialogue["text"], "The walls can remember footsteps.");
    assert_eq!(dialogue["choices"][0]["affordable"], true);
    assert_eq!(dialogue["choices"][1]["affordable"], false);
    game.execute(Command::Choose {
        choice: "gift".into(),
    })
    .unwrap();
    assert_eq!(game.inspect_player_tile(4, 0)["enemy"]["damage"], 6);
    assert_eq!(
        game.player_observation()["enemies"]
            .as_array()
            .unwrap()
            .len(),
        1
    );
    assert_eq!(
        game.player_observation()["inventory_items"][0]["id"],
        "hero_orb"
    );
    assert_eq!(
        game.player_observation()["inventory_items"][0]["usable"],
        false
    );
}

#[test]
fn visible_result_timeline_keeps_clues_and_masks_private_and_offscreen_changes() {
    let mut game = fixture();
    move_to(&mut game, Direction::Right);
    move_to(&mut game, Direction::Right);
    move_to(&mut game, Direction::Up);
    let view = game.player_observation();
    assert!(
        game.snapshot()["flags"]
            .as_array()
            .unwrap()
            .contains(&json!("private_solution_flag"))
    );
    let serialized = view.to_string();
    for secret in [
        "private_solution_flag",
        "private_scene_key",
        "private provenance",
        "private_solution",
        "underlying_tile",
        "dialogue_id",
    ] {
        assert!(!serialized.contains(secret), "leaked {secret}");
    }
    let timeline = view["last_action"]["presentation"].as_array().unwrap();
    assert!(timeline.iter().any(|effect| effect["type"] == "dialogue"
        && effect["text"] == "The old stones whisper: seek the missing hour."));
    assert!(
        timeline
            .iter()
            .any(|effect| effect["type"] == "cinematic"
                && effect["text"] == "A visible inscription.")
    );
    assert!(!timeline.iter().any(|effect| effect["floor"] == 2));
    assert!(
        timeline
            .iter()
            .filter(|effect| effect["type"] == "tile")
            .all(|effect| effect["tile"] == 8 || effect["tile"] == 6)
    );
}

#[test]
fn original_campaign_secret_wall_variants_are_masked_on_every_floor() {
    let game = Engine::from_json(include_str!("../../../../data/campaign.json")).unwrap();
    for floor in &game.campaign().floors {
        let mut original = game.clone();
        let mut save: Value = serde_json::from_str(&original.save_json()).unwrap();
        save["player"]["floor"] = json!(floor.id);
        original.load_json(&save.to_string()).unwrap();
        let view = original.player_observation();
        for (index, id) in floor.tiles.iter().enumerate() {
            if matches!(id, 8..=10) {
                assert_eq!(view["tiles"][index], 8, "floor {} index {index}", floor.id);
                assert_eq!(
                    original.inspect_player_tile(index % 11, index / 11)["name"],
                    "Brick wall"
                );
            }
        }
        assert!(view["tile_defs"].get("9").is_none());
        assert!(view["tile_defs"].get("10").is_none());
    }
}
