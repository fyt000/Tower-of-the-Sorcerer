//! The Wisdom Orb records first-heard clues while owned, independently of logs.
use serde_json::{Value, json};
use tos_core::Engine;

fn fixture() -> Engine {
    Engine::from_json(
        &json!({
            "id":"journal-fixture","title":"Journal fixture","width":4,"height":2,
            "start":{"floor":1,"x":0,"y":1,"hp":100,"attack":10,"defense":3,"gold":10,"inventory":["hero_orb","wisdom_orb"]},
            "rules":{"empty_tile":0,"backside":{"enabled":true}},
            "floors":[{"id":1,"title":"Entrance","tiles":[1,1,0,0,0,0,0,0]},
                {"id":2,"title":"Unvisited room","tiles":[2,0,0,0,0,0,0,0]}],
            "tiles":{
                "0":{"name":"Road","kind":"floor"},
                "1":{"name":"Old man","kind":"npc","text":"A door listens for the missing hour.",
                    "source":"private NPC provenance","dialogue_ids":[42],
                    "after_text":{"flag":"paid_for_clue","text":"The hour is written where the lantern points."},
                    "offers":[{"id":"clue","label":"Buy another clue","cost":2,"once":true,
                        "effects":[{"type":"flag","flag":"paid_for_clue"}]}]},
                "2":{"name":"Unseen speaker","kind":"npc","text":"UNENCOUNTERED DIALOGUE"}
            },
            "enemies":{},
            "events":[{"id":"private_script_id","once":true,
                "trigger":{"type":"step","floor":1,"x":1,"y":1},
                "effects":[{"type":"message","text":"Follow the shadow beyond noon.","dialogue_id":555},
                    {"type":"cinematic","kind":"private_scene_key","text":"A visible inscription: four stones remember.",
                        "source":"private scene provenance","answer":"UNENCOUNTERED ANSWER"}]},
                {"id":"cycle_gate","once":true,"trigger":{"type":"step","floor":1,"x":3,"y":1},
                    "effects":[{"type":"next_cycle"}]}]
        })
        .to_string(),
    )
    .unwrap()
}

fn command(game: &mut Engine, action: Value) {
    game.command(action).unwrap();
}

fn step(game: &mut Engine, direction: &str) {
    command(game, json!({"type":"move","direction":direction}));
}

fn journal(game: &Engine) -> Vec<Value> {
    game.player_observation()["journal"]
        .as_array()
        .expect("player observations expose the encountered journal")
        .clone()
}

fn texts(entries: &[Value]) -> Vec<&str> {
    entries
        .iter()
        .map(|entry| entry["text"].as_str().unwrap())
        .collect()
}

fn encounter_all_clues(game: &mut Engine) {
    step(game, "up");
    command(game, json!({"type":"choose","choice":"clue"}));
    command(game, json!({"type":"choose","choice":"leave"}));
    step(game, "right");
}

#[test]
fn owned_orb_records_npc_clues_without_recording_generic_scripts() {
    let mut game = fixture();
    assert!(journal(&game).is_empty());
    let _ = game.inspect_player_tile(0, 0);
    let _ = game.inspect(0, 0);
    assert!(
        journal(&game).is_empty(),
        "inspection does not open dialogue"
    );

    step(&mut game, "up");
    let first = journal(&game);
    assert_eq!(
        first,
        vec![json!({
            "cycle":1,"floor":1,"x":0,"y":0,"title":"Old man",
            "text":"A door listens for the missing hour."
        })]
    );
    command(&mut game, json!({"type":"cancel"}));
    assert_eq!(journal(&game), first, "dismissing speech cannot erase it");
    step(&mut game, "up");
    assert_eq!(
        journal(&game),
        first,
        "reopening the same speech is deduplicated"
    );
    command(&mut game, json!({"type":"choose","choice":"clue"}));
    assert_eq!(
        texts(&journal(&game)),
        [
            "A door listens for the missing hour.",
            "The hour is written where the lantern points."
        ]
    );
    command(&mut game, json!({"type":"choose","choice":"leave"}));
    let paid = journal(&game);
    step(&mut game, "up");
    assert_eq!(
        journal(&game),
        paid,
        "reopening paid speech is deduplicated"
    );
    command(&mut game, json!({"type":"cancel"}));
    step(&mut game, "right");
    let entries = journal(&game);
    assert_eq!(
        texts(&entries),
        [
            "A door listens for the missing hour.",
            "The hour is written where the lantern points."
        ]
    );
    for entry in &entries {
        assert!(!entry["title"].as_str().unwrap().is_empty());
        assert_eq!(
            entry
                .as_object()
                .unwrap()
                .keys()
                .map(String::as_str)
                .collect::<Vec<_>>(),
            ["cycle", "floor", "text", "title", "x", "y"]
        );
    }
    let serialized = serde_json::to_string(&entries).unwrap();
    for secret in ["UNENCOUNTERED", "private", "paid_for_clue", "dialogue_id"] {
        assert!(!serialized.contains(secret), "journal leaked {secret}");
    }
    assert_eq!(game.snapshot()["journal"], json!(entries));
}

#[test]
fn identical_dialogue_at_different_locations_keeps_each_encounter() {
    let mut game = fixture();
    step(&mut game, "up");
    command(&mut game, json!({"type":"cancel"}));
    step(&mut game, "right");
    step(&mut game, "up");
    let entries = journal(&game);
    let repeated: Vec<_> = entries
        .iter()
        .filter(|entry| entry["text"] == "A door listens for the missing hour.")
        .collect();
    assert_eq!(repeated.len(), 2);
    assert_eq!(repeated[0]["x"], 0);
    assert_eq!(repeated[1]["x"], 1);
    command(&mut game, json!({"type":"cancel"}));
    step(&mut game, "up");
    assert_eq!(journal(&game), entries);
}

#[test]
fn journal_survives_log_eviction_save_load_and_legacy_saves() {
    let mut game = fixture();
    encounter_all_clues(&mut game);
    let encountered = journal(&game);
    for _ in 0..125 {
        command(&mut game, json!({"type":"use_item","item":"hero_orb"}));
    }
    let view = game.player_observation();
    assert_eq!(view["log"].as_array().unwrap().len(), 100);
    assert!(
        view["log"]
            .as_array()
            .unwrap()
            .iter()
            .all(|line| line == "The item is always active.")
    );
    assert_eq!(
        journal(&game),
        encountered,
        "clues remain after every original log message was evicted"
    );
    let saved = game.save_json();
    let mut restored = fixture();
    restored.load_json(&saved).unwrap();
    assert_eq!(restored.save_json(), saved);
    assert_eq!(journal(&restored), encountered);

    let mut legacy: Value = serde_json::from_str(&saved).unwrap();
    legacy.as_object_mut().unwrap().remove("journal");
    restored.load_json(&legacy.to_string()).unwrap();
    assert!(
        journal(&restored).is_empty(),
        "old saves default to an empty journal without inventing encountered text"
    );
}

#[test]
fn cycle_transition_clears_clues_and_first_heard_flags_then_new_game_clears_them() {
    let mut game = fixture();
    encounter_all_clues(&mut game);
    let first_cycle = journal(&game);
    step(&mut game, "right");
    step(&mut game, "right");
    assert_eq!(game.player_observation()["cycle"], 2);
    assert!(!first_cycle.is_empty());
    assert!(journal(&game).is_empty());
    step(&mut game, "up");
    let entries = journal(&game);
    assert_eq!(entries.len(), 1);
    assert_eq!(entries.last().unwrap()["cycle"], 2);
    assert_eq!(entries.last().unwrap()["text"], first_cycle[0]["text"]);
    command(&mut game, json!({"type":"new_game"}));
    assert_eq!(game.player_observation()["cycle"], 1);
    assert!(journal(&game).is_empty());
}

fn set_wisdom(game: &mut Engine, owned: bool) {
    let mut saved: Value = serde_json::from_str(&game.save_json()).unwrap();
    let inventory = saved["player"]["inventory"].as_array_mut().unwrap();
    inventory.retain(|item| item != "wisdom_orb");
    if owned {
        inventory.push(json!("wisdom_orb"));
    }
    game.load_json(&saved.to_string()).unwrap();
}

#[test]
fn journal_requires_ownership_and_cannot_recover_a_clue_first_heard_before_acquisition() {
    let mut game = fixture();
    set_wisdom(&mut game, false);
    assert_eq!(game.snapshot()["journal_unlocked"], false);
    command(&mut game, json!({"type":"use_item","item":"wisdom_orb"}));
    assert_eq!(game.snapshot()["last_action"]["ok"], false);
    step(&mut game, "up");
    assert!(journal(&game).is_empty());
    command(&mut game, json!({"type":"cancel"}));
    set_wisdom(&mut game, true);
    assert_eq!(game.snapshot()["journal_unlocked"], true);
    step(&mut game, "up");
    assert!(
        journal(&game).is_empty(),
        "rereading cannot backfill an old clue"
    );
    command(&mut game, json!({"type":"choose","choice":"clue"}));
    assert_eq!(
        texts(&journal(&game)),
        ["The hour is written where the lantern points."]
    );
    command(&mut game, json!({"type":"cancel"}));
    let recorded = journal(&game);
    command(&mut game, json!({"type":"use_item","item":"wisdom_orb"}));
    let snapshot = game.snapshot();
    assert_eq!(snapshot["last_action"]["ok"], true);
    assert_eq!(
        snapshot["last_action"]["presentation"],
        json!([{"type":"journal","entries":recorded}])
    );
    assert!(
        game.player()
            .inventory
            .iter()
            .any(|item| item == "wisdom_orb")
    );
    set_wisdom(&mut game, false);
    assert!(
        journal(&game).is_empty(),
        "stored clues are inaccessible without the orb"
    );
    set_wisdom(&mut game, true);
    assert_eq!(journal(&game), recorded);
}

fn original() -> Engine {
    Engine::from_json(include_str!("../../../data/campaign.json")).unwrap()
}

/// Isolate a real original NPC encounter from route prerequisites. The saved
/// world and dialogue definitions are original; only approach and resources
/// are arranged so the test measures journal behavior rather than combat.
fn approach_original(game: &mut Engine, interaction: &Value) {
    let floor = interaction["floor"].as_i64().unwrap();
    let x = interaction["x"].as_u64().unwrap() as usize;
    let y = interaction["y"].as_u64().unwrap() as usize;
    let px = if x == 0 { 1 } else { x - 1 };
    let mut saved: Value = serde_json::from_str(&game.save_json()).unwrap();
    saved["player"]["floor"] = json!(floor);
    saved["player"]["x"] = json!(px);
    saved["player"]["y"] = json!(y);
    saved["player"]["hp"] = json!(1_000_000);
    saved["player"]["gold"] = json!(1_000_000);
    saved["pending_interaction"] = Value::Null;
    saved["pending_tile"] = Value::Null;
    saved["floors"][floor.to_string()][y * game.campaign().width + px] = json!(6);
    let visited = saved["visited_floors"].as_array_mut().unwrap();
    if !visited.contains(&json!(floor)) {
        visited.push(json!(floor));
    }
    game.load_json(&saved.to_string()).unwrap();
    step(game, if x == 0 { "left" } else { "right" });
    assert!(
        game.snapshot()["pending_interaction"].is_object(),
        "failed to encounter {interaction}"
    );
}

fn original_clue_cases(game: &Engine) -> Vec<(u32, Value)> {
    let mut cases: Vec<_> = game
        .campaign()
        .interactions
        .iter()
        .filter_map(|interaction| {
            let clue = interaction["dialogue_ids"]
                .as_array()?
                .iter()
                .filter_map(Value::as_u64)
                .find(|id| (62..=85).contains(id))?;
            Some((clue as u32, interaction.clone()))
        })
        .collect();
    cases.sort_by_key(|(id, _)| *id);
    cases
}

#[test]
fn original_records_exactly_twenty_four_clue_slots_in_source_order() {
    let mut game = original();
    set_wisdom(&mut game, true);
    let cases = original_clue_cases(&game);
    assert_eq!(cases.len(), 24);
    for (_, interaction) in cases.iter().rev() {
        let before = journal(&game).len();
        approach_original(&mut game, interaction);
        if interaction["offers"]
            .as_array()
            .is_some_and(|offers| !offers.is_empty())
        {
            assert_eq!(
                journal(&game).len(),
                before,
                "a merchant sales pitch is not a recorded clue"
            );
            command(&mut game, json!({"type":"choose","choice":"trade"}));
        }
        assert_eq!(
            journal(&game).len(),
            before + 1,
            "original clue was not recorded: {interaction}"
        );
        command(&mut game, json!({"type":"cancel"}));
    }
    let expected: Vec<_> = cases
        .iter()
        .map(|(_, interaction)| {
            interaction["after_text"]["text"]
                .as_str()
                .or_else(|| interaction["text"].as_str())
                .unwrap()
        })
        .collect();
    let entries = journal(&game);
    assert_eq!(
        texts(&entries),
        expected,
        "journal order follows original slots, not visit order"
    );
    for entry in entries {
        assert_eq!(
            entry.as_object().unwrap().len(),
            6,
            "source metadata must stay private"
        );
    }
}

#[test]
fn original_pre_orb_clues_and_non_clue_speech_are_not_added_later() {
    let mut game = original();
    let cases = original_clue_cases(&game);
    approach_original(&mut game, &cases[0].1);
    command(&mut game, json!({"type":"cancel"}));
    set_wisdom(&mut game, true);
    approach_original(&mut game, &cases[0].1);
    assert!(journal(&game).is_empty());
    command(&mut game, json!({"type":"cancel"}));
    let non_clue = game
        .campaign()
        .interactions
        .iter()
        .find(|interaction| interaction["floor"] == 15 && interaction["name"] == "Thief")
        .unwrap()
        .clone();
    approach_original(&mut game, &non_clue);
    assert!(
        journal(&game).is_empty(),
        "the thief's speech is not one of the 24 Wisdom slots"
    );
    command(&mut game, json!({"type":"cancel"}));
    approach_original(&mut game, &cases[1].1);
    assert_eq!(journal(&game).len(), 1);
    assert_eq!(journal(&game)[0]["text"], cases[1].1["text"]);
}

#[test]
fn invalid_journal_save_entries_are_rejected_without_mutating_the_session() {
    let mut game = fixture();
    encounter_all_clues(&mut game);
    let before = game.save_json();
    let observation = game.player_observation();
    for (field, value) in [
        ("cycle", json!(0)),
        ("cycle", json!(2)),
        ("floor", json!(999)),
        ("x", json!(4)),
        ("y", json!(2)),
        ("title", json!("")),
        ("text", json!("")),
    ] {
        let mut invalid: Value = serde_json::from_str(&before).unwrap();
        invalid["journal"][0][field] = value.clone();
        assert!(
            game.load_json(&invalid.to_string()).is_err(),
            "accepted journal {field}={value}"
        );
        assert_eq!(game.save_json(), before);
        assert_eq!(game.player_observation(), observation);
    }
}
