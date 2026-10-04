use serde_json::{Value, json};
use std::{
    env, fs,
    io::{self, BufRead, Write},
    path::{Path, PathBuf},
};
use tos_core::Engine;

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
                engine.campaign.title,
                engine.campaign.floors.len(),
                engine.campaign.tiles.len(),
                engine.campaign.enemies.len(),
                engine.campaign.events.len()
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
                let result = serde_json::from_str(&line)
                    .map_err(|e| e.to_string())
                    .and_then(|command| engine.command(command));
                match result {
                    Ok(()) => println!("{}", engine.snapshot()),
                    Err(error) => println!("{}", json!({"error":error})),
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
                engine.command(
                    serde_json::from_str(line).map_err(|e| format!("Line {}: {e}", i + 1))?,
                )?;
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
        let tiles = state["tiles"].as_array().unwrap();
        for y in 0..engine.campaign.height {
            for x in 0..engine.campaign.width {
                if p.x == x && p.y == y {
                    print!("@ ");
                    continue;
                }
                let id = tiles[y * engine.campaign.width + x]
                    .as_u64()
                    .unwrap()
                    .to_string();
                let tile = &engine.campaign.tiles[&id];
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
            for choice in dialog["choices"].as_array().unwrap() {
                println!(
                    "  choose {} — {}",
                    choice["id"].as_str().unwrap_or(""),
                    choice["label"].as_str().unwrap_or("")
                );
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
            "w" | "up" => json!({"type":"move","direction":"up"}),
            "s" | "down" => json!({"type":"move","direction":"down"}),
            "a" | "left" => json!({"type":"move","direction":"left"}),
            "d" | "right" => json!({"type":"move","direction":"right"}),
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
            "choose" => json!({"type":"choose","choice":words.get(1).unwrap_or(&"leave")}),
            "cancel" => json!({"type":"cancel"}),
            "use" => {
                json!({"type":"use_item","item":words.get(1).unwrap_or(&""),"floor":words.get(2).and_then(|s|s.parse::<i32>().ok())})
            }
            _ => {
                println!("Unknown command");
                continue;
            }
        };
        if let Err(error) = engine.command(command) {
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
    json!([
        {"name":"game_state","description":"Read complete deterministic game state, map, inventory and combat forecasts.","inputSchema":{"type":"object","properties":{},"additionalProperties":false},"annotations":{"readOnlyHint":true}},
        {"name":"inspect_tile","description":"Inspect a tile and predict exact combat damage without taking an action.","inputSchema":{"type":"object","properties":{"x":{"type":"integer","minimum":0},"y":{"type":"integer","minimum":0}},"required":["x","y"],"additionalProperties":false},"annotations":{"readOnlyHint":true}},
        {"name":"plan_path","description":"Plan a click route through clear road. An obstacle can be the final action, never an intermediate step. Unreachable targets return the closest reachable road prefix.","inputSchema":{"type":"object","properties":{"x":{"type":"integer","minimum":0},"y":{"type":"integer","minimum":0}},"required":["x","y"],"additionalProperties":false},"annotations":{"readOnlyHint":true}},
        {"name":"game_action","description":"Commit one game action. Move, choose a shop/dialogue response, cancel, or use an item.","inputSchema":{"type":"object","properties":{"action":{"type":"object","properties":{"type":{"enum":["move","choose","cancel","use_item"]},"direction":{"enum":["up","down","left","right"]},"choice":{"type":"string"},"item":{"type":"string"},"floor":{"type":"integer"}},"required":["type"]}},"required":["action"]}},
        {"name":"simulate_actions","description":"Simulate up to 1000 actions on a copy and return the resulting state. Does not modify the session.","inputSchema":{"type":"object","properties":{"actions":{"type":"array","maxItems":1000,"items":{"type":"object"}}},"required":["actions"]},"annotations":{"readOnlyHint":true}},
        {"name":"save_game","description":"Export a portable JSON save including flags and changed floors.","inputSchema":{"type":"object","properties":{},"additionalProperties":false},"annotations":{"readOnlyHint":true}},
        {"name":"load_game","description":"Restore an exported save for this campaign revision.","inputSchema":{"type":"object","properties":{"save":{"type":"string"}},"required":["save"]}},
        {"name":"new_game","description":"Reset the current session to the campaign's initial state.","inputSchema":{"type":"object","properties":{},"additionalProperties":false}}
    ])
}

fn call_tool(engine: &mut Engine, name: &str, args: &Value) -> Result<Value, String> {
    match name {
        "game_state" => Ok(engine.snapshot()),
        "plan_path" => {
            let x = args["x"]
                .as_u64()
                .ok_or("x must be a nonnegative integer")? as usize;
            let y = args["y"]
                .as_u64()
                .ok_or("y must be a nonnegative integer")? as usize;
            Ok(json!({"directions":engine.path_to(x,y),"floor":engine.player().floor}))
        }
        "inspect_tile" => Ok(engine.inspect(
            args["x"]
                .as_u64()
                .ok_or("x must be a nonnegative integer")? as usize,
            args["y"]
                .as_u64()
                .ok_or("y must be a nonnegative integer")? as usize,
        )),
        "game_action" => {
            engine.command(args.get("action").ok_or("Missing action")?.clone())?;
            Ok(engine.snapshot())
        }
        "simulate_actions" => {
            let actions = args["actions"]
                .as_array()
                .ok_or("actions must be an array")?;
            if actions.len() > 1000 {
                return Err("Maximum 1000 simulated actions".into());
            }
            let mut simulation = engine.clone();
            for action in actions {
                simulation.command(action.clone())?;
            }
            Ok(simulation.snapshot())
        }
        "save_game" => Ok(json!({"save":engine.save_json()})),
        "load_game" => {
            engine.load_json(args["save"].as_str().ok_or("save must be a JSON string")?)?;
            Ok(engine.snapshot())
        }
        "new_game" => {
            engine.command(json!({"type":"new_game"}))?;
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
                match call_tool(
                    engine,
                    params["name"].as_str().unwrap_or(""),
                    &params["arguments"],
                ) {
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
                        serde_json::to_value(&engine.campaign).map_err(|e| e.to_string())
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
