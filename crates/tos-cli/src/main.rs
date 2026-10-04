use serde::{Deserialize, de::DeserializeOwned};
use serde_json::{Value, json};
use std::{
    env, fs,
    io::{self, BufRead, Write},
    path::{Path, PathBuf},
};
use tos_core::{Command, Direction, Engine};

const DEFAULT_CAMPAIGN: &str = include_str!("../../../data/campaign.json");

fn main() {
    if let Err(error) = run() {
        eprintln!("tos: {error}");
        std::process::exit(1);
    }
}

fn run() -> Result<(), String> {
    let args: Vec<String> = env::args().skip(1).collect();
    let mode = args.first().map(String::as_str).unwrap_or("help");
    if mode == "help" || mode == "--help" || mode == "-h" {
        println!(
            "Tower of the Sorcerer — deterministic Rust engine\n\nUSAGE: tos <MODE> [OPTIONS]\n\n  serve           Serve the browser build on http://127.0.0.1:8080\n  play            Interactive terminal game (WASD, inspect X Y, save PATH)\n  state           Print complete initial state as JSON\n  headless        Read JSON commands from stdin; output state after each\n  replay PATH     Execute newline-delimited JSON actions and print final state\n  mcp             MCP server over stdio (JSON-RPC, no stdout logging)\n  validate        Validate campaign data\n\nOPTIONS:\n  --campaign PATH Load a custom campaign JSON instead of the embedded original\n  --save PATH     Restore a saved state before running\n  --port NUMBER   Browser server port (default 8080)\n  --web PATH      Browser assets directory (default ./web)\n\nMove command: {{\"type\":\"move\",\"direction\":\"up\"}}\nChoose command: {{\"type\":\"choose\",\"choice\":\"leave\"}}\nItem command: {{\"type\":\"use_item\",\"item\":\"orb_of_flying\",\"floor\":1}}"
        );
        return Ok(());
    }
    if mode == "serve" {
        let port: u16 = option(&args, "--port")
            .unwrap_or("8080")
            .parse()
            .map_err(|_| "Invalid port")?;
        let web = PathBuf::from(option(&args, "--web").unwrap_or("web"));
        return serve(&web, port);
    }
    let source = option(&args, "--campaign")
        .map(fs::read_to_string)
        .transpose()
        .map_err(|e| e.to_string())?;
    let mut engine = Engine::from_json(source.as_deref().unwrap_or(DEFAULT_CAMPAIGN))?;
    if let Some(path) = option(&args, "--save") {
        engine.load_json(&fs::read_to_string(path).map_err(|e| e.to_string())?)?;
    }
    match mode {
        "validate" => {
            println!(
                "Valid campaign: {} · {} floors · {} tile definitions · {} enemies · {} events",
                engine.campaign().title,
                engine.campaign().floors.len(),
                engine.campaign().tiles.len(),
                engine.campaign().enemies.len(),
                engine.campaign().events.len()
            );
            Ok(())
        }
        "state" => {
            println!("{}", engine.snapshot());
            Ok(())
        }
        "headless" => {
            for line in io::stdin().lock().lines() {
                let line = line.map_err(|e| e.to_string())?;
                if line.trim().is_empty() {
                    continue;
                }
                let result = engine.command_json(&line);
                match result {
                    Ok(()) => println!("{}", engine.snapshot()),
                    Err(error) => println!("{}", json!({"error":error.to_string()})),
                }
            }
            Ok(())
        }
        "replay" => {
            let path = args
                .get(1)
                .filter(|s| !s.starts_with("--"))
                .ok_or("replay requires a JSONL file")?;
            for (i, line) in fs::read_to_string(path)
                .map_err(|e| e.to_string())?
                .lines()
                .enumerate()
            {
                if line.trim().is_empty() || line.starts_with('#') {
                    continue;
                }
                engine
                    .command_json(line)
                    .map_err(|error| format!("Line {}: {error}", i + 1))?;
            }
            println!("{}", engine.snapshot());
            Ok(())
        }
        "play" => play(&mut engine),
        "mcp" => mcp(&mut engine),
        _ => Err(format!("Unknown mode {mode}; use tos --help")),
    }
}

fn option<'a>(args: &'a [String], name: &str) -> Option<&'a str> {
    args.iter()
        .position(|s| s == name)
        .and_then(|i| args.get(i + 1))
        .map(String::as_str)
}

fn play(engine: &mut Engine) -> Result<(), String> {
    loop {
        let state = engine.snapshot();
        let p = engine.player();
        println!(
            "\nFloor {} · HP {} · ATK {} · DEF {} · Gold {} · Keys {}/{}/{}",
            p.floor, p.hp, p.attack, p.defense, p.gold, p.keys.yellow, p.keys.blue, p.keys.red
        );
        for y in 0..engine.campaign().height {
            for x in 0..engine.campaign().width {
                if p.x == x && p.y == y {
                    print!("@ ");
                    continue;
                }
                let id = engine
                    .tile_at(p.floor, x, y)
                    .ok_or("Current floor is missing a tile")?;
                let tile = engine
                    .campaign()
                    .tiles
                    .get(&id.to_string())
                    .ok_or("Current floor references an undefined tile")?;
                let glyph = match tile.kind.as_str() {
                    "wall" | "hidden_wall" => "#",
                    "enemy" => "M",
                    "door" => "D",
                    "stairs_up" => "<",
                    "stairs_down" => ">",
                    "key" => "k",
                    "potion" => "+",
                    "gem" => "*",
                    "item" | "equipment" => "!",
                    "npc" | "shop" | "altar" | "merchant" => "?",
                    "special_door" => "=",
                    "lava" => "~",
                    _ => "·",
                };
                print!("{glyph} ");
            }
            println!();
        }
        if let Some(dialog) = state["pending_interaction"].as_object() {
            println!(
                "{}: {}",
                dialog["title"].as_str().unwrap_or(""),
                dialog["text"].as_str().unwrap_or("")
            );
            if let Some(choices) = dialog
                .get("choices")
                .or_else(|| dialog.get("offers"))
                .and_then(Value::as_array)
            {
                for choice in choices {
                    println!(
                        "  choose {} — {}",
                        choice["id"].as_str().unwrap_or(""),
                        choice["label"].as_str().unwrap_or("")
                    );
                }
            }
        }
        if let Some(message) = state["last_action"]["message"].as_str() {
            println!("{message}");
        }
        print!("WASD / inspect X Y / choose ID / use ITEM [FLOOR] / save PATH / quit > ");
        io::stdout().flush().map_err(|e| e.to_string())?;
        let mut line = String::new();
        if io::stdin()
            .read_line(&mut line)
            .map_err(|e| e.to_string())?
            == 0
        {
            return Ok(());
        }
        let words: Vec<&str> = line.split_whitespace().collect();
        let Some(first) = words.first().copied() else {
            continue;
        };
        let command = match first {
            "quit" | "q" => return Ok(()),
            "w" | "up" => Command::Move {
                direction: Direction::Up,
            },
            "s" | "down" => Command::Move {
                direction: Direction::Down,
            },
            "a" | "left" => Command::Move {
                direction: Direction::Left,
            },
            "d" | "right" => Command::Move {
                direction: Direction::Right,
            },
            "inspect" => {
                if let (Some(x), Some(y)) = (
                    words.get(1).and_then(|s| s.parse::<usize>().ok()),
                    words.get(2).and_then(|s| s.parse::<usize>().ok()),
                ) {
                    println!("{}", engine.inspect(x, y));
                }
                continue;
            }
            "save" => {
                if let Some(path) = words.get(1) {
                    fs::write(path, engine.save_json()).map_err(|e| e.to_string())?;
                    println!("Saved {path}");
                }
                continue;
            }
            "choose" => Command::Choose {
                choice: words.get(1).copied().unwrap_or("leave").into(),
            },
            "cancel" => Command::Cancel,
            "use" => {
                let floor = match words.get(2).map(|s| s.parse::<i32>()).transpose() {
                    Ok(floor) => floor,
                    Err(error) => {
                        println!("Invalid destination floor: {error}");
                        continue;
                    }
                };
                Command::UseItem {
                    item: words.get(1).copied().unwrap_or("").into(),
                    floor,
                }
            }
            _ => {
                println!("Unknown command");
                continue;
            }
        };
        if let Err(error) = engine.execute(command) {
            println!("{error}");
        }
    }
}

fn serve(root: &Path, port: u16) -> Result<(), String> {
    let root = root
        .canonicalize()
        .map_err(|e| format!("Browser build missing: {e}; run npm run build"))?;
    if !root.join("pkg/tos_ui_bg.wasm").exists() {
        return Err("WebAssembly build missing; run npm run build first".into());
    }
    let server = tiny_http::Server::http(("127.0.0.1", port)).map_err(|e| e.to_string())?;
    println!("Tower of the Sorcerer is running at http://127.0.0.1:{port}");
    for request in server.incoming_requests() {
        let url = request.url().split('?').next().unwrap_or("/");
        let relative = if url == "/" {
            "index.html"
        } else {
            url.trim_start_matches('/')
        };
        let path = root.join(relative);
        let allowed = !relative.contains('\\')
            && !relative.contains('%')
            && path.canonicalize().is_ok_and(|p| p.starts_with(&root));
        let response = if allowed {
            match fs::read(&path) {
                Ok(body) => {
                    let content_type = match path.extension().and_then(|s| s.to_str()).unwrap_or("")
                    {
                        "html" => "text/html; charset=utf-8",
                        "js" | "mjs" => "text/javascript; charset=utf-8",
                        "css" => "text/css; charset=utf-8",
                        "json" => "application/json",
                        "wasm" => "application/wasm",
                        "png" => "image/png",
                        "svg" => "image/svg+xml",
                        "wav" => "audio/wav",
                        _ => "application/octet-stream",
                    };
                    tiny_http::Response::from_data(body)
                        .with_header(
                            tiny_http::Header::from_bytes("Content-Type", content_type).unwrap(),
                        )
                        .with_header(
                            tiny_http::Header::from_bytes("Cache-Control", "no-cache").unwrap(),
                        )
                }
                Err(_) => tiny_http::Response::from_string("Not found").with_status_code(404),
            }
        } else {
            tiny_http::Response::from_string("Not found").with_status_code(404)
        };
        let _ = request.respond(response);
    }
    Ok(())
}

fn tool_definitions() -> Value {
    let action_schema = Command::json_schema();
    json!([
        {"name":"game_state","description":"Read complete deterministic game state, map, inventory and combat forecasts.","inputSchema":{"type":"object","properties":{},"additionalProperties":false},"annotations":{"readOnlyHint":true}},
        {"name":"inspect_tile","description":"Inspect a tile and predict exact combat damage without taking an action.","inputSchema":{"type":"object","properties":{"x":{"type":"integer","minimum":0},"y":{"type":"integer","minimum":0}},"required":["x","y"],"additionalProperties":false},"annotations":{"readOnlyHint":true}},
        {"name":"plan_path","description":"Plan a click route through clear road. An obstacle can be the final action, never an intermediate step. Unreachable targets return the closest reachable road prefix.","inputSchema":{"type":"object","properties":{"x":{"type":"integer","minimum":0},"y":{"type":"integer","minimum":0}},"required":["x","y"],"additionalProperties":false},"annotations":{"readOnlyHint":true}},
        {"name":"game_action","description":"Commit one game action. Move, choose a shop/dialogue response, cancel, use an item, or reset the journey.","inputSchema":{"type":"object","properties":{"action":action_schema},"required":["action"],"additionalProperties":false}},
        {"name":"simulate_actions","description":"Simulate up to 1000 actions on a copy and return the resulting state. Does not modify the session.","inputSchema":{"type":"object","properties":{"actions":{"type":"array","maxItems":1000,"items":action_schema}},"required":["actions"],"additionalProperties":false},"annotations":{"readOnlyHint":true}},
        {"name":"save_game","description":"Export a portable JSON save including flags and changed floors.","inputSchema":{"type":"object","properties":{},"additionalProperties":false},"annotations":{"readOnlyHint":true}},
        {"name":"load_game","description":"Restore an exported save for this campaign revision.","inputSchema":{"type":"object","properties":{"save":{"type":"string"}},"required":["save"],"additionalProperties":false}},
        {"name":"new_game","description":"Reset the current session to the campaign's initial state.","inputSchema":{"type":"object","properties":{},"additionalProperties":false}}
    ])
}

// MCP envelopes are transport data. Reject unknown or mistyped arguments here;
// the engine then receives the same Command used by keyboard and browser input.
#[derive(Deserialize)]
#[serde(deny_unknown_fields)]
struct ActionArguments {
    action: Command,
}

#[derive(Deserialize)]
#[serde(deny_unknown_fields)]
struct SimulationArguments {
    actions: Vec<Command>,
}

#[derive(Deserialize)]
#[serde(deny_unknown_fields)]
struct TileArguments {
    x: usize,
    y: usize,
}

#[derive(Deserialize)]
#[serde(deny_unknown_fields)]
struct SaveArguments {
    save: String,
}

#[derive(Deserialize)]
#[serde(deny_unknown_fields)]
struct EmptyArguments {}

fn arguments<T: DeserializeOwned>(value: &Value) -> Result<T, String> {
    serde_json::from_value(value.clone())
        .map_err(|error| format!("Invalid tool arguments: {error}"))
}

fn call_tool(engine: &mut Engine, name: &str, args: &Value) -> Result<Value, String> {
    match name {
        "game_state" => {
            arguments::<EmptyArguments>(args)?;
            Ok(engine.snapshot())
        }
        "plan_path" => {
            let TileArguments { x, y } = arguments(args)?;
            Ok(json!({"directions":engine.path_to(x,y),"floor":engine.player().floor}))
        }
        "inspect_tile" => {
            let TileArguments { x, y } = arguments(args)?;
            Ok(engine.inspect(x, y))
        }
        "game_action" => {
            let ActionArguments { action } = arguments(args)?;
            engine.execute(action)?;
            Ok(engine.snapshot())
        }
        "simulate_actions" => {
            let SimulationArguments { actions } = arguments(args)?;
            if actions.len() > 1000 {
                return Err("Maximum 1000 simulated actions".into());
            }
            let mut simulation = engine.clone();
            for action in actions {
                simulation.execute(action)?;
            }
            Ok(simulation.snapshot())
        }
        "save_game" => {
            arguments::<EmptyArguments>(args)?;
            Ok(json!({"save":engine.save_json()}))
        }
        "load_game" => {
            let SaveArguments { save } = arguments(args)?;
            engine.load_json(&save)?;
            Ok(engine.snapshot())
        }
        "new_game" => {
            arguments::<EmptyArguments>(args)?;
            engine.execute(Command::NewGame)?;
            Ok(engine.snapshot())
        }
        _ => Err(format!("Unknown tool {name}")),
    }
}

fn mcp(engine: &mut Engine) -> Result<(), String> {
    for line in io::stdin().lock().lines() {
        let line = line.map_err(|e| e.to_string())?;
        if line.trim().is_empty() {
            continue;
        }
        let request: Value = match serde_json::from_str(&line) {
            Ok(v) => v,
            Err(_) => {
                println!(
                    "{}",
                    json!({"jsonrpc":"2.0","id":null,"error":{"code":-32700,"message":"Parse error"}})
                );
                continue;
            }
        };
        let Some(id) = request.get("id").cloned() else {
            continue;
        };
        let params = &request["params"];
        let result = match request["method"].as_str().unwrap_or("") {
            "initialize" => {
                let requested = params["protocolVersion"].as_str().unwrap_or("2025-11-25");
                let version = if ["2024-11-05", "2025-03-26", "2025-06-18", "2025-11-25"]
                    .contains(&requested)
                {
                    requested
                } else {
                    "2025-11-25"
                };
                Ok(
                    json!({"protocolVersion":version,"capabilities":{"tools":{},"resources":{}},"serverInfo":{"name":"tower-of-the-sorcerer","version":env!("CARGO_PKG_VERSION")},"instructions":"Read game_state and inspect_tile before acting. All interfaces share the Rust rules engine. simulate_actions supports reversible route planning; saves include persistent events."}),
                )
            }
            "ping" => Ok(json!({})),
            "tools/list" => Ok(json!({"tools":tool_definitions()})),
            "tools/call" => {
                let args = params
                    .get("arguments")
                    .cloned()
                    .unwrap_or_else(|| json!({}));
                match call_tool(engine, params["name"].as_str().unwrap_or(""), &args) {
                    Ok(value) => Ok(
                        json!({"content":[{"type":"text","text":value.to_string()}],"structuredContent":value,"isError":false}),
                    ),
                    Err(error) => {
                        Ok(json!({"content":[{"type":"text","text":error}],"isError":true}))
                    }
                }
            }
            "resources/list" => Ok(
                json!({"resources":[{"uri":"tos://state","name":"Current game state","mimeType":"application/json"},{"uri":"tos://campaign","name":"Campaign configuration","mimeType":"application/json"}]}),
            ),
            "resources/read" => {
                let uri = params["uri"].as_str().unwrap_or("");
                let value = match uri {
                    "tos://state" => Ok(engine.snapshot()),
                    "tos://campaign" => {
                        serde_json::to_value(engine.campaign()).map_err(|e| e.to_string())
                    }
                    _ => Err("Unknown resource".into()),
                };
                value.map(|v|json!({"contents":[{"uri":uri,"mimeType":"application/json","text":v.to_string()}]}))
            }
            _ => Err("Method not found".into()),
        };
        let response = match result {
            Ok(value) => json!({"jsonrpc":"2.0","id":id,"result":value}),
            Err(error) => {
                json!({"jsonrpc":"2.0","id":id,"error":{"code":if error=="Method not found"{-32601}else{-32602},"message":error}})
            }
        };
        println!("{response}");
        io::stdout().flush().map_err(|e| e.to_string())?;
    }
    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn mcp_action_schema_and_runtime_share_the_command_contract() {
        let definitions = tool_definitions();
        let action = definitions
            .as_array()
            .unwrap()
            .iter()
            .find(|tool| tool["name"] == "game_action")
            .unwrap();
        assert_eq!(
            action["inputSchema"]["properties"]["action"],
            Command::json_schema()
        );
        assert_eq!(action["inputSchema"]["additionalProperties"], false);

        let mut engine = Engine::from_json(DEFAULT_CAMPAIGN).unwrap();
        for args in [
            json!({"action":{"type":"move"}}),
            json!({"action":{"type":"move","direction":"up","typo":true}}),
            json!({"action":{"type":"choose","choice":" "}}),
            json!({"action":{"type":"use_item","item":"flying_orb","floor":2147483648_i64}}),
            json!({"action":{"type":"use_item","item":"flying_orb"}}),
            json!({"action":{"type":"cancel","choice":"leave"}}),
            json!({"action":{"type":"new_game","unexpected":true}}),
            json!({"action":{"type":"cancel"},"extra":true}),
        ] {
            let before = engine.snapshot();
            let save = engine.save_json();
            assert!(
                call_tool(&mut engine, "game_action", &args).is_err(),
                "accepted {args}"
            );
            assert_eq!(engine.snapshot(), before);
            assert_eq!(engine.save_json(), save);
        }
    }

    #[test]
    fn invalid_simulation_cannot_modify_the_live_session() {
        let mut engine = Engine::from_json(DEFAULT_CAMPAIGN).unwrap();
        let before = engine.snapshot();
        assert!(
            call_tool(
                &mut engine,
                "simulate_actions",
                &json!({"actions":[
                    {"type":"move","direction":"up"},
                    {"type":"use_item","item":"flying_orb"}
                ]})
            )
            .is_err()
        );
        assert_eq!(engine.snapshot(), before);
    }
}
