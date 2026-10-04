use serde_json::{Value, json};
use tos_core::{Command, CommandError, Direction, Engine};

fn engine() -> Engine {
    Engine::from_json(
        &json!({
            "id":"command-boundary","title":"Command boundary","width":3,"height":3,
            "start":{"floor":1,"x":1,"y":1,"hp":100,"attack":10,"defense":5},
            "floors":[{"id":1,"tiles":[0,0,0, 1,0,3, 0,2,0]}],
            "tiles":{
                "0":{"name":"Road","kind":"floor"},
                "1":{"name":"Wall","kind":"wall"},
                "2":{"name":"Old man","kind":"npc","text":"Welcome."},
                "3":{"name":"Yellow key","kind":"key","key":"yellow","amount":1}
            },
            "enemies":{},"rules":{"empty_tile":0}
        })
        .to_string(),
    )
    .unwrap()
}

#[test]
fn malformed_commands_never_mutate_the_game_or_last_action() {
    let malformed = [
        "not json",
        "null",
        "[]",
        "{}",
        r#"{"type":17}"#,
        r#"{"type":"teleport","floor":2}"#,
        r#"{"type":"move"}"#,
        r#"{"type":"move","direction":"diagonal"}"#,
        r#"{"type":"move","direction":0}"#,
        r#"{"type":"move","direction":"up","direction":"down"}"#,
        r#"{"type":"move","direction":"up","floor":1}"#,
        r#"{"type":"choose"}"#,
        r#"{"type":"choose","choice":""}"#,
        r#"{"type":"choose","choice":"  \t "}"#,
        r#"{"type":"use_item"}"#,
        r#"{"type":"use_item","item":false}"#,
        r#"{"type":"use_item","item":" "}"#,
        r#"{"type":"use_item","item":"mattock","floor":"1"}"#,
        r#"{"type":"use_item","item":"mattock","floor":1.5}"#,
        r#"{"type":"use_item","item":"mattock","floor":2147483648}"#,
        r#"{"type":"use_item","item":"flying_orb"}"#,
        r#"{"type":"use_item","item":"floor_wand","floor":null}"#,
        r#"{"type":"cancel","choice":"leave"}"#,
        r#"{"type":"new_game","unexpected":true}"#,
    ];
    for pending_conversation in [false, true] {
        let mut game = engine();
        if pending_conversation {
            game.execute(Command::Move {
                direction: Direction::Down,
            })
            .unwrap();
            assert!(game.snapshot()["pending_interaction"].is_object());
        }
        for source in malformed {
            let before = game.snapshot();
            let save = game.save_json();
            assert!(game.command_json(source).is_err(), "accepted {source}");
            assert_eq!(game.snapshot(), before, "changed snapshot for {source}");
            assert_eq!(game.save_json(), save, "changed save for {source}");

            // Value compatibility callers receive exactly the same validation.
            // Value has already discarded duplicate object keys, so duplicate
            // field rejection is exercised by the raw JSON boundary above.
            if !source.contains(r#""direction":"up","direction""#)
                && let Ok(value) = serde_json::from_str::<Value>(source)
            {
                assert!(game.command(value).is_err(), "accepted Value {source}");
                assert_eq!(game.snapshot(), before);
                assert_eq!(game.save_json(), save);
            }
        }
    }
}

#[test]
fn typed_rust_callers_cannot_bypass_identifier_validation() {
    let mut game = engine();
    for command in [
        Command::Choose {
            choice: String::new(),
        },
        Command::UseItem {
            item: "  ".into(),
            floor: None,
        },
        Command::UseItem {
            item: "orb_of_flying".into(),
            floor: None,
        },
    ] {
        let before = game.snapshot();
        assert!(game.execute(command).is_err());
        assert_eq!(game.snapshot(), before);
    }
}

#[test]
fn json_compatibility_and_typed_dispatch_have_identical_results() {
    let mut typed = engine();
    let mut raw_json = engine();
    let mut compatibility = engine();
    let commands = [
        Command::Move {
            direction: Direction::Right,
        },
        Command::Move {
            direction: Direction::Left,
        },
        Command::Move {
            direction: Direction::Down,
        },
        Command::Choose {
            choice: "leave".into(),
        },
        Command::UseItem {
            item: "mattock".into(),
            floor: None,
        },
        Command::Cancel,
        Command::NewGame,
    ];
    for command in commands {
        let source = serde_json::to_string(&command).unwrap();
        assert_eq!(Command::from_json(&source).unwrap(), command);
        typed.execute(command).unwrap();
        raw_json.command_json(&source).unwrap();
        compatibility
            .command(serde_json::from_str(&source).unwrap())
            .unwrap();
        assert_eq!(raw_json.snapshot(), typed.snapshot());
        assert_eq!(compatibility.snapshot(), typed.snapshot());
        assert_eq!(raw_json.save_json(), typed.save_json());
    }
}

#[test]
fn a_wall_is_a_valid_game_action_and_not_an_input_error() {
    let mut game = engine();
    let before_player = game.snapshot()["player"].clone();
    game.command_json(r#"{"type":"move","direction":"left"}"#)
        .unwrap();
    assert_eq!(game.snapshot()["player"], before_player);
    assert_eq!(game.snapshot()["last_action"]["ok"], false);
    assert!(game.snapshot()["last_action"]["message"].is_string());

    assert!(matches!(
        game.command_json(r#"{"type":"move","direction":"LEFT"}"#),
        Err(CommandError::InvalidJson(_))
    ));
}

#[test]
fn destination_floor_is_an_i32_and_required_only_by_flying_items() {
    assert_eq!(
        Command::from_json(r#"{"type":"use_item","item":"flying_orb","floor":-1}"#).unwrap(),
        Command::UseItem {
            item: "flying_orb".into(),
            floor: Some(-1)
        }
    );
    assert!(Command::from_json(r#"{"type":"use_item","item":"mattock"}"#).is_ok());
    assert!(Command::from_json(r#"{"type":"use_item","item":"mattock","floor":null}"#).is_ok());
    assert!(matches!(
        Command::from_json(r#"{"type":"use_item","item":"flying_orb"}"#),
        Err(CommandError::MissingDestinationFloor)
    ));
}

#[test]
fn unknown_offer_is_a_blocked_action_and_keeps_the_shop_available() {
    let mut campaign = serde_json::to_value(engine().campaign()).unwrap();
    campaign["start"]["gold"] = json!(20);
    campaign["tiles"]["2"] = json!({
        "name":"Shopkeeper","kind":"shop","text":"Buy an attack upgrade?",
        "offers":[{"id":"attack","label":"Attack +1","cost":5,
                   "effects":[{"type":"add_stat","stat":"attack","amount":1}]}]
    });
    let mut game = Engine::from_json(&campaign.to_string()).unwrap();
    game.execute(Command::Move {
        direction: Direction::Down,
    })
    .unwrap();
    let conversation = game.snapshot()["pending_interaction"].clone();
    assert_eq!(conversation["choices"][0]["id"], "attack");
    let save = game.save_json();

    // This identifier is syntactically valid; availability is a game rule.
    game.command_json(r#"{"type":"choose","choice":"does-not-exist"}"#)
        .unwrap();
    assert_eq!(game.snapshot()["last_action"]["ok"], false);
    assert_eq!(game.snapshot()["last_action"]["message"], "Unknown offer");
    assert_eq!(game.snapshot()["pending_interaction"], conversation);
    assert_eq!(game.save_json(), save);

    game.execute(Command::Choose {
        choice: "attack".into(),
    })
    .unwrap();
    assert_eq!(game.player().attack, 11);
    assert_eq!(game.player().gold, 15);
}

#[test]
fn owned_custom_passive_tag_is_blocked_without_consuming_it() {
    let mut campaign = serde_json::to_value(engine().campaign()).unwrap();
    campaign["start"]["inventory"] = json!(["custom_passive_tag"]);
    campaign["tiles"]["4"] = json!({
        "name":"Keepsake","kind":"equipment","item":"custom_passive_tag"
    });
    let mut game = Engine::from_json(&campaign.to_string()).unwrap();
    let save = game.save_json();

    game.command_json(r#"{"type":"use_item","item":"custom_passive_tag"}"#)
        .unwrap();
    assert_eq!(game.snapshot()["last_action"]["ok"], false);
    assert_eq!(
        game.snapshot()["last_action"]["message"],
        "Item custom_passive_tag is passive or has no configured action"
    );
    assert_eq!(game.player().inventory, ["custom_passive_tag"]);
    assert_eq!(game.save_json(), save);
}
