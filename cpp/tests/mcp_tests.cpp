#include "tsw/game_state.hpp"
#include "tsw/mcp.hpp"
#include "tsw/replay.hpp"
#include <catch2/catch_test_macros.hpp>
#include <chrono>
#include <fstream>
#include <glaze/json.hpp>
#include <glaze/json/generic.hpp>
#include <sstream>
#include <utility>

using namespace tsw;

namespace {
using Json = glz::generic_u64;

std::string encode(const Json& value) {
    return glz::write_json(value).value();
}

Json decode(std::string_view text) {
    Json value;
    REQUIRE_FALSE(glz::read_json(value, text));
    return value;
}

struct Client {
    McpServer server;
    int next_id{};

    Client(bool developer = false, Game game = Game{}, bool runtime_bridge = false)
        : server(developer, std::move(game), runtime_bridge) {
        const auto initialized =
            rpc("initialize", Json{{"protocolVersion", "2025-11-25"},
                                   {"capabilities", Json::object_t{}},
                                   {"clientInfo", Json{{"name", "test"}, {"version", "1"}}}});
        REQUIRE(initialized["result"]["protocolVersion"].get<std::string>() == "2025-11-25");
        REQUIRE_FALSE(server.respond(R"({"jsonrpc":"2.0","method":"notifications/initialized"})"));
    }

    Json rpc(std::string_view method, Json params = Json::object_t{}) {
        const auto response = server.respond(
            encode(Json{{"jsonrpc", "2.0"}, {"id", ++next_id}, {"method", method}, {"params", params}}));
        REQUIRE(response);
        auto parsed = decode(*response);
        REQUIRE(parsed["id"].as<int>() == next_id);
        return parsed;
    }

    Json raw_tool(std::string_view name, Json args = Json::object_t{}) {
        return rpc("tools/call", Json{{"name", name}, {"arguments", args}});
    }

    Json tool(std::string_view name, Json args = Json::object_t{}) {
        // Existing fidelity assertions deliberately exercise the full legacy projection.
        if ((name == "game_state" || name == "game_action" || name == "new_game" || name == "load_game" ||
             name == "replay_game" || name == "simulate_actions") &&
            !args.contains("detail"))
            args["detail"] = "full";
        if (name == "export_replay" && args.contains("path") && !args.contains("include_replay"))
            args["include_replay"] = true;
        auto response = raw_tool(name, args);
        INFO(encode(response));
        REQUIRE_FALSE(response.contains("error"));
        REQUIRE_FALSE(response["result"]["isError"].get<bool>());
        const auto& result = response["result"];
        REQUIRE(encode(decode(result["content"][0]["text"].get<std::string>())) ==
                encode(result["structuredContent"]));
        return result["structuredContent"];
    }

    Json act(std::string_view source) { return tool("game_action", Json{{"action", decode(source)}}); }
};

Game room(bool orb = true) {
    Game game;
    game.hero.x = game.hero.y = 5;
    game.hero.gold = 100;
    game.floors[1].tiles.fill(Road);
    game.inventory(Item::HeroOrb) = orb ? 1 : 0;
    return game;
}

struct Directory {
    std::filesystem::path path =
        std::filesystem::path(TSW_TEST_TEMP) /
        ("mcp-" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));

    Directory() { std::filesystem::create_directories(path); }

    ~Directory() {
        std::error_code ignored;
        std::filesystem::remove_all(path, ignored);
    }

    std::string file(std::string_view name) const { return (path / name).generic_string(); }
};
} // namespace

TEST_CASE("MCP validates envelopes and negotiates its stdio lifecycle", "[mcp]") {
    McpServer server;
    for (auto request : {"not json", "{} trailing", "{\"jsonrpc\":\"2.0\"} trailing"}) {
        const auto reply = server.respond(request);
        REQUIRE(reply);
        REQUIRE(decode(*reply)["error"]["code"].as<int>() == -32700);
    }
    for (auto request :
         {"[]", "null", "{}", R"({"jsonrpc":"1.0","id":1,"method":"ping"})",
          R"({"jsonrpc":"2.0","id":null,"method":"ping"})", R"({"jsonrpc":"2.0","id":true,"method":"ping"})"})
        REQUIRE(decode(*server.respond(request))["error"]["code"].as<int>() == -32600);
    REQUIRE(decode(*server.respond(R"({"jsonrpc":"2.0","id":1,"method":"tools/list"})"))["error"]["code"]
                .as<int>() == -32000);
    const auto ping = decode(*server.respond(R"({"jsonrpc":"2.0","id":9007199254740993,"method":"ping"})"));
    REQUIRE(ping["id"].get<std::uint64_t>() == 9007199254740993ULL);
    const auto init = decode(*server.respond(
        R"({"jsonrpc":"2.0","id":"init","method":"initialize","params":{"protocolVersion":"future","capabilities":{},"clientInfo":{"name":"test","version":"1"}}})"));
    REQUIRE(init["id"].get<std::string>() == "init");
    REQUIRE(init["result"]["protocolVersion"].get<std::string>() == "2025-11-25");
    REQUIRE_FALSE(server.respond(R"({"jsonrpc":"2.0","method":"notifications/initialized"})"));
    REQUIRE_FALSE(
        server.respond(R"({"jsonrpc":"2.0","method":"notifications/cancelled","params":{"requestId":1}})"));
    REQUIRE_FALSE(server.respond(R"({"jsonrpc":"2.0","id":1,"result":{}})"));
    REQUIRE(decode(*server.respond(R"({"jsonrpc":"2.0","id":2,"method":"missing"})"))["error"]["code"]
                .as<int>() == -32601);
    REQUIRE(
        decode(*server.respond(
            R"({"jsonrpc":"2.0","id":3,"method":"tools/call","params":{"name":"missing"}})"))["error"]["code"]
            .as<int>() == -32602);
}

TEST_CASE("MCP normal observations conceal secrets and gate forecasts and simulations", "[mcp]") {
    auto game = room(false);
    game.tile_at(1, 5, 4) = SecretWall;
    game.tile_at(1, 6, 4) = HiddenObject;
    game.tile_at(1, 4, 4) = SpecialRoad;
    game.tile_at(1, 4, 5) = GreenSlime;
    Client client(false, game);
    const auto state = client.tool("game_state");
    REQUIRE(state["width"].as<int>() == 11);
    REQUIRE(state["map"].get_array().size() == CellCount);
    REQUIRE(state["map"][cell(5, 4)].as<int>() == Wall);
    REQUIRE(state["map"][cell(6, 4)].as<int>() == Wall);
    REQUIRE(state["map"][cell(4, 4)].as<int>() == Road);
    REQUIRE_FALSE(state.contains("floors"));
    REQUIRE_FALSE(state.contains("hero_state"));
    REQUIRE_FALSE(state["forecasts_unlocked"].get<bool>());
    REQUIRE(client.tool("inspect_tile", Json{{"x", 4}, {"y", 5}})["details_locked"].get<bool>());
    REQUIRE_FALSE(client.tool("inspect_tile", Json{{"x", 4}, {"y", 5}}).contains("enemy"));
    REQUIRE(client.raw_tool("save_game")["result"]["isError"].get<bool>());
    REQUIRE(client.raw_tool("game_state", Json{{"map_floor", 50}})["result"]["isError"].get<bool>());
    REQUIRE(client.raw_tool("simulate_actions", Json{{"actions", Json::array_t{}}}).contains("error"));
    REQUIRE(client.rpc("tools/list")["result"]["tools"].get_array().size() == 11);
    Client developer(true, game);
    const auto diagnostic = developer.tool("game_state", Json{{"map_floor", 1}});
    REQUIRE(diagnostic["map"][cell(5, 4)].as<int>() == SecretWall);
    REQUIRE(diagnostic["floors"].get_array().size() == FloorCount);
    REQUIRE(diagnostic["monsters"].get_array().size() == 33);
    REQUIRE(developer.rpc("tools/list")["result"]["tools"].get_array().size() == 12);
}

TEST_CASE("MCP forecasts and owned item clues use native values", "[mcp]") {
    auto game = room();
    game.hero.attack = 50;
    game.hero.defense = 30;
    game.monsters[0] = {100, 80, 20, 12};
    game.tile_at(1, 5, 4) = GreenSlime;
    game.inventory(Item::WisdomOrb) = 1;
    game.hero.wisdom_hints[0] = 2;
    Client client(false, game);
    const auto tile = client.tool("inspect_tile", Json{{"x", 5}, {"y", 4}});
    REQUIRE(tile["enemy"]["forecast"]["damage"].as<int>() == game.forecast(GreenSlime).damage);
    REQUIRE(tile["enemy"]["forecast"]["hero_hits"].as<int>() == 4);
    const auto state = client.tool("game_state");
    REQUIRE(state["wisdom_clues"][0]["text"].get<std::string>() == Game::original_dialogue(62));
    REQUIRE(state["inventory_items"].get_array().size() == 2);
    REQUIRE(state["inventory_items"][0]["usage"].is_string());
    const auto forecast = tile["enemy"]["forecast"]["damage"].as<int>();
    const auto after = client.act(R"({"type":"move","direction":"up"})");
    REQUIRE(after["hero"]["hp"].as<int>() == game.hero.hp - forecast);
    REQUIRE(after["last_encounter"]["damage"].as<int>() == forecast);
}

TEST_CASE("MCP first-cycle 50F Zeno is an available ending trigger", "[mcp][navigation][scenes]") {
    for (int tile : {int(Zeno), Zeno + 1}) {
        for (bool orb : {false, true}) {
            CAPTURE(tile, orb);
            auto game = room(orb);
            game.hero.floor = game.hero.highest_floor = 50;
            game.hero.hp = game.hero.attack = game.hero.defense = 1;
            game.floors[50].tiles.fill(Road);
            game.tile_at(50, 5, 4) = static_cast<std::uint8_t>(tile);
            REQUIRE_FALSE(game.forecast(tile).penetrates);
            Client client(false, game);
            const auto inspected = client.tool("inspect_tile", Json{{"x", 5}, {"y", 4}});
            REQUIRE(inspected["name"].get<std::string>() == Game::monster_name(ZenoRow));
            REQUIRE(inspected["kind"].get<std::string>() == "trigger");
            REQUIRE(inspected["interaction"].get<std::string>() == "ending");
            REQUIRE(inspected["hp_cost"].as<int>() == 0);
            REQUIRE(inspected["available"].get<bool>());
            REQUIRE_FALSE(inspected.contains("enemy"));
            REQUIRE_FALSE(inspected.contains("details_locked"));
            const auto full = client.tool("game_state");
            REQUIRE(full["tile_defs"][std::to_string(tile)]["kind"].get<std::string>() == "trigger");
            REQUIRE(full["enemies"].get_array().empty());
            const auto compact = client.tool("game_state", Json{{"detail", "compact"}});
            const auto type = compact["tile_types"][std::to_string(tile)];
            REQUIRE(type["kind"].get<std::string>() == "trigger");
            REQUIRE(type["interaction"].get<std::string>() == "ending");
            REQUIRE(type["hp_cost"].as<int>() == 0);
            REQUIRE(type["available"].get<bool>());
            REQUIRE_FALSE(type.contains("enemy"));
            REQUIRE(compact["floor"]["points"][0]["reachable"].get<bool>());
            const auto after = client.tool("navigate", Json{{"x", 5}, {"y", 4}, {"detail", "full"}});
            REQUIRE(after["navigation"]["reached"].get<bool>());
            REQUIRE(after["navigation"]["inputs"].as<int>() == 1);
            REQUIRE(after["hero"]["hp"].as<int>() == 1);
            REQUIRE(after["hero"]["floor"].as<int>() == 1);
            REQUIRE(after["cycle"]["factor"].as<int>() == 44);
            REQUIRE(after["last_encounter"].is_null());
        }
    }
}

TEST_CASE("MCP 49F and later-cycle Zeno retain combat forecasts", "[mcp][combat][scenes]") {
    for (int tile : {int(Zeno), Zeno + 1}) {
        for (const auto [floor, cycle] : {std::pair{49, 0}, std::pair{49, 43}, std::pair{50, 43}}) {
            CAPTURE(tile, floor, cycle);
            auto game = room();
            game.hero.floor = game.hero.highest_floor = floor;
            game.hero.cycle_factor_minus_one = cycle;
            game.floors[floor].tiles.fill(Road);
            game.tile_at(floor, 5, 4) = static_cast<std::uint8_t>(tile);
            REQUIRE_FALSE(game.forecast(tile).penetrates);
            Client client(false, game);
            const auto inspected = client.tool("inspect_tile", Json{{"x", 5}, {"y", 4}});
            REQUIRE(inspected["kind"].get<std::string>() == "enemy");
            REQUIRE_FALSE(inspected.contains("interaction"));
            REQUIRE_FALSE(inspected["enemy"]["forecast"]["penetrates"].get<bool>());
            const auto compact = client.tool("game_state", Json{{"detail", "compact"}});
            REQUIRE_FALSE(compact["tile_types"][std::to_string(tile)]["available"].get<bool>());
            REQUIRE(client.tool("game_state")["enemies"].get_array().size() == 1);
        }
    }
}

TEST_CASE("MCP defaults omit diagnostic towers and group repeated enemies", "[mcp][navigation]") {
    Client client(true);
    const auto compact = client.raw_tool("game_state")["result"]["structuredContent"];
    REQUIRE(compact["detail"].get<std::string>() == "compact");
    REQUIRE_FALSE(compact.contains("floors"));
    REQUIRE_FALSE(compact.contains("map"));
    REQUIRE_FALSE(compact.contains("log"));
    REQUIRE(compact["floor"]["walkable_rows"].get_array().size() == 11);
    int enemy_types = 0;
    for (const auto& [id, type] : compact["tile_types"].get_object())
        if (type.contains("enemy"))
            ++enemy_types;
    REQUIRE(enemy_types == 6);
    for (const auto& point : compact["floor"]["points"].get_array()) {
        const auto type = compact["tile_types"][std::to_string(point["id"].as<int>())];
        const auto inspected = client.tool("inspect_tile", Json{{"x", point["x"]}, {"y", point["y"]}});
        REQUIRE(type["name"].get<std::string>() == inspected["name"].get<std::string>());
        REQUIRE(type["kind"].get<std::string>() == inspected["kind"].get<std::string>());
        REQUIRE_FALSE(point.contains("name"));
        REQUIRE_FALSE(point.contains("enemy"));
        if (type.contains("enemy"))
            REQUIRE(encode(type["enemy"]["forecast"]) == encode(inspected["enemy"]["forecast"]));
        if (type.contains("amount"))
            REQUIRE(type["amount"].as<int>() == inspected["amount"].as<int>());
    }
    Client normal;
    const auto normal_compact = normal.raw_tool("game_state")["result"]["structuredContent"];
    REQUIRE(encode(normal_compact).size() < encode(normal.tool("game_state")).size());
    REQUIRE(encode(compact).size() * 3 < encode(client.tool("game_state")).size());
    const auto action = client.raw_tool(
        "game_action",
        Json{{"action", decode(R"({"type":"move","direction":"up"})")}})["result"]["structuredContent"];
    REQUIRE(action["detail"].get<std::string>() == "summary");
    REQUIRE_FALSE(action.contains("floor"));
    REQUIRE(action.contains("changes"));
    REQUIRE(encode(action).size() < 1500);
    REQUIRE(client.raw_tool("game_state", Json{{"detail", "typo"}})["result"]["isError"].get<bool>());
}

TEST_CASE("MCP destination movement records native pickup and both door contacts", "[mcp][navigation]") {
    Client client(true), manual(true);
    const auto picked = client.tool("navigate", Json{{"floor", 1}, {"x", 4}, {"y", 9}});
    REQUIRE(picked["navigation"]["reached"].get<bool>());
    REQUIRE(picked["navigation"]["inputs"].as<int>() == 2);
    REQUIRE(picked["changes"]["stats"]["yellow_keys"].as<int>() == 1);
    manual.act(R"({"type":"move","direction":"up"})");
    manual.act(R"({"type":"move","direction":"left"})");
    const auto opened = client.tool("navigate", Json{{"x", 5}, {"y", 8}});
    REQUIRE(opened["navigation"]["inputs"].as<int>() == 3);
    REQUIRE(opened["hero"]["y"].as<int>() == 8);
    manual.act(R"({"type":"move","direction":"right"})");
    manual.act(R"({"type":"move","direction":"up"})");
    manual.act(R"({"type":"move","direction":"up"})");
    REQUIRE(encode(client.tool("game_state")) == encode(manual.tool("game_state")));
    REQUIRE(encode(client.tool("export_replay")) == encode(manual.tool("export_replay")));
}

TEST_CASE("MCP navigation leaves intervening strategic events to the player", "[mcp][navigation]") {
    auto game = room(false);
    game.floors[1].tiles.fill(Wall);
    for (int y = 2; y <= 5; ++y)
        game.tile_at(1, 5, y) = Road;
    game.tile_at(1, 5, 3) = YellowKey;
    Client client(false, game);
    const auto before = client.tool("game_state");
    const auto blocked = client.tool("navigate", Json{{"x", 5}, {"y", 2}});
    REQUIRE_FALSE(blocked["navigation"]["reached"].get<bool>());
    REQUIRE(blocked["navigation"]["inputs"].as<int>() == 0);
    REQUIRE(encode(client.tool("game_state")) == encode(before));
    const auto approach = client.tool("navigate", Json{{"x", 5}, {"y", 3}, {"interact", false}});
    REQUIRE(approach["hero"]["y"].as<int>() == 4);
    REQUIRE(approach["hero"]["yellow_keys"].as<int>() == 0);
    REQUIRE(
        client.raw_tool("navigate", Json{{"floor", 2}, {"x", 5}, {"y", 3}})["result"]["isError"].get<bool>());
    REQUIRE(client.raw_tool("navigate", Json{{"x", 5}, {"y", 3}, {"interact", "yes"}})["result"]["isError"]
                .get<bool>());
}

TEST_CASE("MCP navigation interrupts concealed scripts and retains settled speech", "[mcp][navigation]") {
    Game game;
    game.hero.floor = game.hero.highest_floor = 3;
    game.hero.x = 4;
    game.hero.y = 10;
    Client client(false, game);
    const auto result = client.tool("navigate", Json{{"floor", 3}, {"x", 4}, {"y", 4}});
    REQUIRE(result["hero"]["floor"].as<int>() == 2);
    REQUIRE(result["hero"]["hp"].as<int>() == 400);
    REQUIRE(result["navigation"]["reason"].get<std::string>() == "interrupted");
    REQUIRE_FALSE(result["navigation"]["reached"].get<bool>());
    REQUIRE_FALSE(result["navigation"]["messages"].get_array().empty());
    REQUIRE(result["detail"].get<std::string>() == "compact");
}

TEST_CASE("MCP navigation opens shops and stops after hazard damage", "[mcp][navigation]") {
    auto game = room();
    game.tile_at(1, 5, 3) = Altar;
    Client shop(false, game);
    const auto opened = shop.tool("navigate", Json{{"x", 5}, {"y", 3}});
    REQUIRE(opened["phase"].get<std::string>() == "shop");
    REQUIRE(opened["pending_interaction"]["choices"].get_array().size() == 4);
    REQUIRE(shop.tool("navigate", Json{{"x", 4}, {"y", 5}})["navigation"]["inputs"].as<int>() == 0);
    game.tile_at(1, 5, 3) = Road;
    game.hero.equipment_found[SacredShieldFlag] = 0;
    game.tile_at(1, 6, 4) = MagicianA;
    Client hazard(false, game);
    const auto interrupted = hazard.tool("navigate", Json{{"x", 5}, {"y", 2}});
    REQUIRE(interrupted["navigation"]["reason"].get<std::string>() == "interrupted");
    REQUIRE(interrupted["hero"]["y"].as<int>() == 4);
    REQUIRE(interrupted["hero"]["hp"].as<int>() < game.hero.hp);
}

TEST_CASE("MCP replay file exports avoid echoing entire recordings by default", "[mcp]") {
    Client client(true);
    Directory directory;
    const auto exported = client.raw_tool(
        "export_replay", Json{{"path", directory.file("run.jsonl")}})["result"]["structuredContent"];
    REQUIRE_FALSE(exported.contains("replay"));
    REQUIRE(exported["inputs"].as<int>() == 1);
    REQUIRE(std::filesystem::file_size(directory.file("run.jsonl")) ==
            exported["bytes"].get<std::uint64_t>());
    REQUIRE(client.tool("export_replay").contains("replay"));
}

TEST_CASE("MCP actions report wall refusal and preserve native door contacts", "[mcp]") {
    auto game = room();
    game.tile_at(1, 5, 4) = Wall;
    game.tile_at(1, 4, 5) = YellowDoor;
    game.hero.yellow_keys = 1;
    Client client(false, game);
    auto state = client.act(R"({"type":"move","direction":"up"})");
    REQUIRE_FALSE(state["last_action"]["ok"].get<bool>());
    state = client.act(R"({"type":"move","direction":"left"})");
    REQUIRE(state["last_action"]["ok"].get<bool>());
    REQUIRE_FALSE(state["last_action"]["moved"].get<bool>());
    REQUIRE(state["hero"]["x"].as<int>() == 5);
    REQUIRE(state["hero"]["yellow_keys"].as<int>() == 0);
    REQUIRE(state["map"][cell(4, 5)].as<int>() == Road);
    state = client.act(R"({"type":"move","direction":"left"})");
    REQUIRE(state["hero"]["x"].as<int>() == 4);
    const auto history = client.tool("export_replay");
    std::istringstream inputs(history["replay"].get<std::string>());
    REQUIRE(read_replay(inputs).size() == 4);
}

TEST_CASE("MCP refusal feedback does not report a locked door or impenetrable enemy as successful", "[mcp]") {
    auto game = room();
    game.tile_at(1, 5, 4) = YellowDoor;
    game.tile_at(1, 4, 5) = Rock;
    game.hero.attack = 1;
    Client client(false, game);
    auto state = client.act(R"({"type":"move","direction":"up"})");
    REQUIRE_FALSE(state["last_action"]["ok"].get<bool>());
    REQUIRE(state["map"][cell(5, 4)].as<int>() == YellowDoor);
    state = client.act(R"({"type":"move","direction":"left"})");
    REQUIRE_FALSE(state["last_action"]["ok"].get<bool>());
    REQUIRE(state["last_action"]["message"].get<std::string>() ==
            "Your attack cannot penetrate this enemy's defense.");
    REQUIRE(state["hero"]["x"].as<int>() == 5);
}

TEST_CASE("MCP retains automatically settled speech", "[mcp]") {
    auto game = room();
    game.hero.floor = game.hero.highest_floor = 4;
    game.floors[4].tiles.fill(Road);
    game.tile_at(4, 5, 4) = OldMan;
    game.inventory(Item::WisdomOrb) = 1;
    Client client(false, game);
    const auto state = client.act(R"({"type":"move","direction":"up"})");
    REQUIRE(state["dialogue"].is_null());
    REQUIRE(state["last_action"]["messages"][0].get<std::string>() == Game::original_dialogue(62));
    REQUIRE(state["log"][0]["text"].get<std::string>() == Game::original_dialogue(62));
    REQUIRE(state["wisdom_clues"].get_array().size() == 1);
}

TEST_CASE("MCP path planning stays on apparent road and returns the nearest reachable prefix", "[mcp]") {
    auto game = room();
    game.floors[1].tiles.fill(Wall);
    game.tile_at(1, 5, 5) = Road;
    game.tile_at(1, 5, 4) = Road;
    game.tile_at(1, 5, 3) = YellowKey;
    game.tile_at(1, 5, 2) = Road;
    Client client(false, game);
    const auto before = client.tool("game_state");
    const auto blocked = client.tool("plan_path", Json{{"x", 5}, {"y", 2}});
    REQUIRE_FALSE(blocked["reached"].get<bool>());
    REQUIRE(blocked["directions"].get_array().size() == 1);
    REQUIRE(blocked["directions"][0].get<std::string>() == "up");
    REQUIRE(blocked["endpoint"]["y"].as<int>() == 4);
    const auto contact = client.tool("plan_path", Json{{"x", 5}, {"y", 3}});
    REQUIRE(contact["reached"].get<bool>());
    REQUIRE(contact["directions"].get_array().size() == 2);
    REQUIRE(encode(client.tool("game_state")) == encode(before));
}

TEST_CASE("MCP checkpoints restore private shop state recording and observation timeline", "[mcp][saves]") {
    auto game = room();
    game.tile_at(1, 5, 4) = Altar;
    Client client(false, game);
    const auto shop = client.act(R"({"type":"move","direction":"up"})");
    REQUIRE(shop["pending_interaction"]["choices"][1]["id"].get<std::string>() == "1");
    REQUIRE(shop["pending_interaction"]["choices"][1]["cost"].as<int>() == 20);
    REQUIRE(shop["pending_interaction"]["choices"][1]["affordable"].get<bool>());
    const auto saved = client.tool("save_game");
    REQUIRE_FALSE(saved["persistent"].get<bool>());
    const auto purchased = client.act(R"({"type":"choose","choice":"attack"})");
    REQUIRE(purchased["hero"]["attack"].as<int>() == 102);
    REQUIRE(purchased["hero"]["gold"].as<int>() == 80);
    client.tool("new_game");
    REQUIRE(encode(client.tool("load_game", Json{{"checkpoint", saved["checkpoint"]}})) == encode(shop));
    REQUIRE(encode(client.act(R"({"type":"choose","choice":"attack"})")) == encode(purchased));
    const auto current = client.tool("game_state");
    REQUIRE(client.raw_tool("load_game", Json{{"checkpoint", "missing"}})["result"]["isError"].get<bool>());
    REQUIRE(encode(client.tool("game_state")) == encode(current));
}

TEST_CASE("MCP Flight observation and both actions enforce staircase entry", "[mcp][flight]") {
    auto game = room();
    game.inventory(Item::FlightOrb) = 1;
    game.hero.highest_floor = 2;
    for (bool developer : {false, true}) {
        Client client(developer, game);
        const auto state = client.tool("game_state");
        REQUIRE_FALSE(state["inventory_items"][1]["usable"].get<bool>());
        for (const auto action :
             {R"({"type":"flight_open"})", R"({"type":"use_item","item":"flying_orb","floor":2})"}) {
            const auto rejected = client.act(action);
            REQUIRE(rejected["flight"].as<int>() == -1);
            REQUIRE(encode(rejected["hero"]) == encode(state["hero"]));
            REQUIRE_FALSE(rejected["last_action"]["ok"].get<bool>());
        }
    }
    game.tile_at(1, 4, 5) = StairsUp;
    Client client(false, game);
    REQUIRE(client.tool("game_state")["inventory_items"][1]["usable"].get<bool>());
    client.act(R"({"type":"flight_open"})");
    const auto preview = client.act(R"({"type":"flight_up"})");
    const auto refused = client.act(R"({"type":"use_item","item":"hero_orb"})");
    REQUIRE_FALSE(refused["last_action"]["ok"].get<bool>());
    REQUIRE(refused["flight"].as<int>() == 2);
    REQUIRE(encode(refused["hero"]) == encode(preview["hero"]));
}

TEST_CASE("MCP Flight checkpoints retain previews and cancellation", "[mcp][saves]") {
    auto game = room();
    game.tile_at(1, 4, 5) = StairsUp;
    game.inventory(Item::FlightOrb) = 1;
    game.hero.highest_floor = 45;
    Client client(false, game);
    client.act(R"({"type":"flight_open"})");
    const auto preview = client.act(R"({"type":"flight_up"})");
    REQUIRE(preview["flight"].as<int>() == 2);
    REQUIRE(preview["map_floor"].as<int>() == 2);
    const auto saved = client.tool("save_game");
    client.act(R"({"type":"cancel"})");
    REQUIRE(encode(client.tool("load_game", Json{{"checkpoint", saved["checkpoint"]}})) == encode(preview));
    const auto landed = client.act(R"({"type":"flight_confirm"})");
    REQUIRE(landed["hero"]["floor"].as<int>() == 2);
    REQUIRE(landed["flight"].as<int>() == -1);
    for (const auto& destination : landed["flight_destinations"].get_array())
        REQUIRE(destination.as<int>() != 44);
}

TEST_CASE("MCP native file saves preserve bytes formats and reject failed loads", "[mcp][saves]") {
    Directory temporary;
    for (auto kind : {SaveKind::Slot, SaveKind::Checkpoint}) {
        const auto path = temporary.file(kind == SaveKind::Slot ? "slot.dat" : "fairy.dat");
        Client client(true, room());
        const auto saved = client.tool(
            "save_game", Json{{"path", path}, {"kind", kind == SaveKind::Slot ? "slot" : "checkpoint"}});
        REQUIRE(saved["persistent"].get<bool>());
        REQUIRE(saved["checkpoint"].is_string());
        REQUIRE(std::filesystem::file_size(path) == 6957);
        REQUIRE(std::filesystem::exists(recording_path(path)));
        Game native;
        native.load(path, kind);
        REQUIRE(native.hero.x == 5);
        REQUIRE(native.inventory(Item::HeroOrb) == 1);
        client.act(R"({"type":"move","direction":"left"})");
        const auto loaded = client.tool(
            "load_game", Json{{"path", path}, {"kind", kind == SaveKind::Slot ? "slot" : "checkpoint"}});
        REQUIRE(loaded["hero"]["x"].as<int>() == 5);
        REQUIRE(loaded["recording"]["active"].get<bool>());
        const auto before = client.tool("game_state");
        const auto damaged = temporary.file("broken.dat");
        std::ofstream(damaged, std::ios::binary) << "broken";
        REQUIRE(client.raw_tool("load_game", Json{{"path", damaged}})["result"]["isError"].get<bool>());
        REQUIRE(encode(client.tool("game_state")) == encode(before));
    }
}

TEST_CASE("MCP persistent saves remain available at the session checkpoint limit", "[mcp][saves]") {
    Directory temporary;
    Client client(false, room());
    const auto initial = client.tool("game_state");
    for (int i = 1; i <= 64; ++i)
        REQUIRE(client.tool("save_game")["checkpoint"].get<std::string>() ==
                "checkpoint-" + std::to_string(i));
    REQUIRE(client.raw_tool("save_game")["result"]["isError"].get<bool>());
    REQUIRE(encode(client.tool("game_state")) == encode(initial));
    client.act(R"({"type":"move","direction":"left"})");
    const auto before_failure = client.tool("game_state");
    REQUIRE(client.raw_tool("save_game", Json{{"path", temporary.path.generic_string()}})["result"]["isError"]
                .get<bool>());
    REQUIRE(encode(client.tool("game_state")) == encode(before_failure));
    for (auto kind : {SaveKind::Slot, SaveKind::Checkpoint}) {
        CAPTURE(kind);
        const auto path = temporary.file(kind == SaveKind::Slot ? "slot.dat" : "fairy.dat");
        const Json arguments{{"path", path}, {"kind", kind == SaveKind::Slot ? "slot" : "checkpoint"}};
        for (int write = 0; write < 2; ++write) {
            const auto steps = client.tool("game_state")["steps"].as<int>();
            const auto saved = client.tool("save_game", arguments);
            REQUIRE(saved["persistent"].get<bool>());
            REQUIRE(saved["checkpoint"].is_null());
            REQUIRE(saved["recording"].get<bool>());
            REQUIRE(client.tool("game_state")["steps"].as<int>() == steps + 1);
            REQUIRE(std::filesystem::file_size(path) == 6957);
            REQUIRE(std::filesystem::exists(recording_path(path)));
            Game native;
            native.load(path, kind);
            REQUIRE(native.hero.x == 4);
            client.act(R"({"type":"move","direction":"left"})");
            const auto loaded = client.tool("load_game", arguments);
            REQUIRE(loaded["hero"]["x"].as<int>() == 4);
            REQUIRE(loaded["recording"]["active"].get<bool>());
        }
    }
    for (const auto id : {"checkpoint-1", "checkpoint-64"})
        REQUIRE(encode(client.tool("load_game", Json{{"checkpoint", id}})) == encode(initial));
    REQUIRE(client.raw_tool("save_game")["result"]["isError"].get<bool>());
}

TEST_CASE("MCP recorded saves and reload branches reproduce exact native save bytes",
          "[mcp][saves][replay]") {
    Directory temporary;
    Client client(true);
    client.act(R"({"type":"move","direction":"up"})");
    client.tool("save_game", Json{{"path", temporary.file("slot.dat")}});
    client.act(R"({"type":"move","direction":"left"})");
    client.tool("load_game", Json{{"path", temporary.file("slot.dat")}});
    client.act(R"({"type":"move","direction":"left"})");
    const auto checkpoint_path = temporary.file("fairy.dat");
    client.tool("save_game", Json{{"path", checkpoint_path}, {"kind", "checkpoint"}});
    const auto history = client.tool("export_replay")["replay"].get<std::string>();
    std::istringstream inputs(history);
    Game replayed;
    int flight = -1;
    for (const auto& input : read_replay(inputs)) {
        apply_input(replayed, flight, input);
        settle_action(replayed);
    }
    std::ostringstream bytes(std::ios::out | std::ios::binary);
    replayed.save(bytes, SaveKind::Checkpoint);
    std::ifstream saved(checkpoint_path, std::ios::binary);
    const std::string expected{std::istreambuf_iterator<char>(saved), std::istreambuf_iterator<char>()};
    REQUIRE(bytes.str() == expected);
    REQUIRE(bytes.str().size() == 6957);
    std::istringstream prefix(history);
    const auto actions = read_replay(prefix);
    REQUIRE(actions.size() == 6);
    REQUIRE(actions[2].kind == InputKind::Save);
    REQUIRE(actions[3].kind == InputKind::Reload);
}

TEST_CASE("MCP loading an unrecorded native save reports recording unavailable", "[mcp][saves]") {
    Directory temporary;
    auto native = room();
    const auto path = temporary.file("foreign.dat");
    native.save(path);
    Client client(true);
    const auto loaded = client.tool("load_game", Json{{"path", path}});
    REQUIRE_FALSE(loaded["recording"]["active"].get<bool>());
    REQUIRE(client.raw_tool("export_replay")["result"]["isError"].get<bool>());
    const auto resaved = client.tool("save_game", Json{{"path", temporary.file("unrecorded.dat")}});
    REQUIRE_FALSE(resaved["recording"].get<bool>());
    REQUIRE_FALSE(std::filesystem::exists(recording_path(temporary.file("unrecorded.dat"))));
}

TEST_CASE("MCP file loads and runtime migration retain custom Fairy rankings", "[mcp][rankings]") {
    Directory temporary;
    auto game = room();
    game.hero.floor = game.hero.highest_floor = 10;
    game.floors[10].tiles.fill(Road);
    game.tile_at(10, 5, 4) = Fairy;
    auto table = default_rankings(1);
    for (auto& entry : table)
        entry.score = 500;
    write_rankings(temporary.path, 1, table);
    const auto path = temporary.file("fairy-before.dat");
    game.save(path);
    Client client(true, Game{}, true);
    client.tool("load_game", Json{{"path", path}});
    const auto runtime = temporary.file("rankings-runtime.json");
    REQUIRE(client.rpc("runtime/checkpoint", Json{{"path", runtime}}).contains("result"));
    Client migrated(true, Game{}, true);
    REQUIRE(migrated.rpc("runtime/restore", Json{{"path", runtime}}).contains("result"));
    migrated.act(R"({"type":"move","direction":"up"})");
    const auto after = temporary.file("fairy-after.dat");
    migrated.tool("save_game", Json{{"path", after}});
    Game saved;
    saved.load(after);
    REQUIRE(saved.hero.fairy_score == 415);
    REQUIRE(saved.hero.fairy_rank == 0);
}

TEST_CASE("MCP preserves ranking context across new game and rejects live table injection",
          "[mcp][rankings][replay]") {
    auto game = room();
    game.rankings[0][0].score = 500;
    Client client(false, game);
    client.tool("new_game");
    const auto source = client.tool("export_replay")["replay"].get<std::string>();
    std::istringstream stream(source);
    const auto history = read_replay(stream);
    REQUIRE(history.size() == 2);
    REQUIRE(history[0].kind == InputKind::NewGame);
    REQUIRE(history[1].kind == InputKind::Rankings);
    REQUIRE(history[1].rankings);
    REQUIRE(*history[1].rankings == game.rankings);
    const auto before = client.tool("game_state");
    const auto result = client.raw_tool("game_action", Json{{"action", decode(input_json(history[1]))}});
    REQUIRE(result["result"]["isError"].get<bool>());
    REQUIRE(encode(client.tool("game_state")) == encode(before));
    client.tool("replay_game", Json{{"replay", source}});
    REQUIRE(client.tool("export_replay")["replay"].get<std::string>() == source);
}

TEST_CASE("MCP file saving refuses directory targets without replacing them or changing the session",
          "[mcp][saves]") {
    Directory temporary;
    const auto folder = temporary.file("directory.dat");
    std::filesystem::create_directory(folder);
    Client client(true);
    const auto before = client.tool("game_state");
    REQUIRE(client.raw_tool("save_game", Json{{"path", folder}})["result"]["isError"].get<bool>());
    REQUIRE(std::filesystem::is_directory(folder));
    REQUIRE_FALSE(std::filesystem::exists(folder + ".bak"));
    REQUIRE(encode(client.tool("game_state")) == encode(before));
}

TEST_CASE("MCP replay prefixes takeover and simulation remain isolated", "[mcp][replay]") {
    Client client(true);
    const std::string recording = "{\"type\":\"new_game\"}\n{\"type\":\"move\",\"direction\":\"up\"}\n{"
                                  "\"type\":\"move\",\"direction\":\"left\"}\n";
    auto state = client.tool("replay_game", Json{{"replay", recording}, {"limit", 2}});
    REQUIRE(state["hero"]["y"].as<int>() == 9);
    REQUIRE(state["replay"]["executed"].as<int>() == 2);
    REQUIRE_FALSE(state["replay"]["complete"].get<bool>());
    const auto before = client.tool("game_state");
    const auto simulated =
        client.tool("simulate_actions",
                    Json{{"actions", Json::array_t{decode(R"({"type":"move","direction":"left"})")}}});
    REQUIRE(encode(client.tool("game_state")) == encode(before));
    REQUIRE(encode(client.act(R"({"type":"move","direction":"left"})")) == encode(simulated));
    const auto history = client.tool("export_replay");
    REQUIRE(history["replay"].get<std::string>() == recording);
    state = client.tool("game_state");
    REQUIRE(client
                .raw_tool("replay_game",
                          Json{{"replay", recording + "{\"type\":\"flight_up\"}\n"}})["result"]["isError"]
                .get<bool>());
    REQUIRE(encode(client.tool("game_state")) == encode(state));
    REQUIRE(client
                .raw_tool("replay_game",
                          Json{{"replay", recording + "bad json\n"}, {"limit", 1}})["result"]["isError"]
                .get<bool>());
    REQUIRE(encode(client.tool("game_state")) == encode(state));
}

TEST_CASE("MCP validates tool arguments without changing state", "[mcp]") {
    Client client(true);
    const auto before = client.tool("game_state");
    for (auto args : {"null", "[]", R"({"extra":1})", R"({"map_floor":-1})", R"({"map_floor":1.5})"})
        REQUIRE(client.raw_tool("game_state", decode(args))["result"]["isError"].get<bool>());
    for (auto action :
         {R"({"type":"move","direction":"north"})", R"({"type":"move","direction":"up","extra":true})",
          R"({"type":"use_item","item":"flying_orb","floor":1.5})", R"({"type":"move"})"})
        REQUIRE(client.raw_tool("game_action", Json{{"action", decode(action)}})["result"]["isError"]
                    .get<bool>());
    REQUIRE(encode(client.tool("game_state")) == encode(before));
    const auto resources = client.rpc("resources/list");
    REQUIRE(resources["result"]["resources"].get_array().size() == 3);
    const auto state_resource = client.rpc("resources/read", Json{{"uri", "tos://state"}});
    REQUIRE(encode(decode(state_resource["result"]["contents"][0]["text"].get<std::string>())) ==
            encode(client.tool("game_state", Json{{"detail", "compact"}})));
    REQUIRE(client.rpc("resources/read", Json{{"uri", "tos://missing"}})["error"]["code"].as<int>() ==
            -32002);
}

TEST_CASE("MCP runtime migration is private and works before the Hero Orb", "[mcp][runtime]") {
    Directory directory;
    const auto path = directory.file("runtime.json");
    Client ordinary(true);
    for (const auto method : {"runtime/checkpoint", "runtime/restore"})
        REQUIRE(ordinary.rpc(method, Json{{"path", path}})["error"]["code"].as<int>() == -32601);
    REQUIRE_FALSE(std::filesystem::exists(path));
    Client source(false, room(false), true), target(false, Game{}, true);
    source.act(R"({"type":"move","direction":"left"})");
    REQUIRE_FALSE(source.tool("game_state")["save_unlocked"].get<bool>());
    const auto expected = source.tool("game_state");
    REQUIRE(source.rpc("runtime/checkpoint", Json{{"path", path}}).contains("result"));
    REQUIRE(target.rpc("runtime/restore", Json{{"path", path}})["result"]["restored"].get<bool>());
    REQUIRE(encode(target.tool("game_state")) == encode(expected));
    REQUIRE(encode(target.tool("export_replay")) == encode(source.tool("export_replay")));
}

TEST_CASE("MCP runtime migration preserves shops Flight and checkpoint identities", "[mcp][runtime]") {
    Directory directory;
    const auto path = directory.file("runtime.json");
    auto game = room();
    game.tile_at(1, 4, 5) = StairsUp;
    game.inventory(Item::FlightOrb) = 1;
    game.hero.highest_floor = 4;
    game.tile_at(1, 5, 4) = Altar;
    game.save(directory.file("native.dat"));
    Client source(true, game, true), target(true, Game{}, true);
    const auto shop = source.act(R"({"type":"move","direction":"up"})");
    const auto id = source.tool("save_game")["checkpoint"];
    source.act(R"({"type":"choose","choice":"leave"})");
    source.act(R"({"type":"flight_open"})");
    const auto preview = source.act(R"({"type":"flight_up"})");
    REQUIRE(source.raw_tool("load_game", Json{{"path", directory.file("native.dat")}})["result"]["isError"]
                .get<bool>());
    REQUIRE(encode(source.tool("game_state")) == encode(preview));
    const auto flight_id = source.tool("save_game")["checkpoint"];
    REQUIRE(source.rpc("runtime/checkpoint", Json{{"path", path}}).contains("result"));
    const auto first = target.rpc("runtime/restore", Json{{"path", path}});
    INFO(encode(first));
    REQUIRE(first.contains("result"));
    REQUIRE(encode(target.tool("game_state")) == encode(preview));
    REQUIRE(encode(target.tool("load_game", Json{{"checkpoint", id}})) == encode(shop));
    source.tool("load_game", Json{{"checkpoint", id}});
    REQUIRE(encode(target.act(R"({"type":"choose","choice":"attack"})")) ==
            encode(source.act(R"({"type":"choose","choice":"attack"})")));
    REQUIRE(encode(target.tool("load_game", Json{{"checkpoint", flight_id}})) == encode(preview));
    REQUIRE(target.tool("save_game")["checkpoint"].get<std::string>() == "checkpoint-3");
}

TEST_CASE("MCP runtime migration retains merchant offer and original checksum words", "[mcp][runtime]") {
    Directory directory;
    const auto runtime = directory.file("runtime.json");
    auto game = room();
    game.hero.floor = game.hero.highest_floor = 6;
    game.floors[6].tiles.fill(Road);
    game.tile_at(6, 5, 4) = Merchant;
    Client source(true, game, true), target(true, Game{}, true);
    source.tool("save_game", Json{{"path", directory.file("seed.dat")}});
    const auto shop = source.act(R"({"type":"move","direction":"up"})");
    REQUIRE(shop["phase"].get<std::string>() == "shop");
    REQUIRE(source.rpc("runtime/checkpoint", Json{{"path", runtime}}).contains("result"));
    REQUIRE(target.rpc("runtime/restore", Json{{"path", runtime}}).contains("result"));
    REQUIRE(encode(target.act(R"({"type":"choose","choice":"accept"})")) ==
            encode(source.act(R"({"type":"choose","choice":"accept"})")));
    source.tool("save_game", Json{{"path", directory.file("source.dat")}, {"kind", "checkpoint"}});
    target.tool("save_game", Json{{"path", directory.file("target.dat")}, {"kind", "checkpoint"}});
    std::ifstream original(directory.file("source.dat"), std::ios::binary);
    std::ifstream migrated(directory.file("target.dat"), std::ios::binary);
    REQUIRE(std::string(std::istreambuf_iterator<char>(original), {}) ==
            std::string(std::istreambuf_iterator<char>(migrated), {}));
}

TEST_CASE("MCP runtime restore rejects corrupt incompatible and incomplete files atomically",
          "[mcp][runtime]") {
    Directory directory;
    const auto path = directory.file("runtime.json");
    Client source(true, room(), true), target(true, Game{}, true), normal(false, Game{}, true);
    source.tool("save_game");
    REQUIRE(source.rpc("runtime/checkpoint", Json{{"path", path}}).contains("result"));
    std::ifstream file(path);
    const std::string bytes{std::istreambuf_iterator<char>(file), {}};
    auto valid = decode(bytes);
    const auto before = target.tool("game_state");
    const auto wrong_mode = normal.rpc("runtime/restore", Json{{"path", path}});
    REQUIRE(wrong_mode["error"]["data"]["kind"].get<std::string>() == "session_incompatible");
    REQUIRE_FALSE(wrong_mode["error"]["data"]["session_continuable"].get<bool>());
    for (int problem = 0; problem < 12; ++problem) {
        auto broken = valid;
        if (problem == 0)
            broken["version"] = 99;
        else if (problem == 1)
            broken["session"]["game"]["hero"]["x"] = 100;
        else if (problem == 2)
            broken["next_checkpoint"] = 0;
        else if (problem == 3)
            broken["session"]["history"] = Json::array_t{"{\"type\":\"flight_up\"}"};
        else if (problem == 4)
            broken["session"]["game"].get_object().erase("hero");
        else if (problem == 5)
            broken["session"]["game"]["extra"] = 1;
        else if (problem == 7)
            broken["session"]["game"]["hero"]["items"].get_array().pop_back();
        else if (problem == 8)
            broken["session"]["game"]["floors"].get_array().pop_back();
        else if (problem == 9)
            broken["session"]["game"].get_object().erase("fight");
        else if (problem == 10) {
            broken["session"]["game"]["visual"]["last_defeated"] =
                broken["session"]["game"]["visual"]["battle_enemy"];
            broken["session"]["game"]["visual"]["last_defeated"]["row"] = 999;
        } else if (problem == 11)
            broken["session"]["game"].get_object().erase("rankings");
        std::ofstream(path, std::ios::binary | std::ios::trunc)
            << (problem == 6 ? "{broken" : encode(broken));
        INFO(problem);
        const auto rejected = target.rpc("runtime/restore", Json{{"path", path}});
        REQUIRE(rejected.contains("error"));
        const bool incompatible = problem == 0 || problem == 4 || problem == 5 || problem == 7 ||
                                  problem == 8 || problem == 9 || problem == 11;
        REQUIRE(rejected["error"].contains("data") == incompatible);
        if (incompatible) {
            REQUIRE(rejected["error"]["code"].as<int>() == -32003);
            REQUIRE(rejected["error"]["data"]["kind"].get<std::string>() == "session_incompatible");
            REQUIRE_FALSE(rejected["error"]["data"]["session_continuable"].get<bool>());
        }
        REQUIRE(encode(target.tool("game_state")) == encode(before));
    }
}

TEST_CASE("Complete game snapshots preserve pending combat speech and death", "[mcp][runtime]") {
    auto game = room(false);
    game.tile_at(1, 5, 4) = GreenSlime;
    game.monsters[0] = {1000, 120, 20, 17};
    game.monsters[ZenoRow] = {987, 234, 111, 80};
    REQUIRE(game.move(Direction::Up));
    game.run_one();
    const auto pending = GameState::capture(game);
    auto restored = pending.restore();
    REQUIRE(glz::write_json(GameState::capture(restored)).value() == glz::write_json(pending).value());
    game.finish_commands(true);
    restored.finish_commands(true);
    REQUIRE(glz::write_json(GameState::capture(restored)).value() ==
            glz::write_json(GameState::capture(game)).value());
    game.push(Op::Defeat);
    game.finish_commands();
    REQUIRE(GameState::capture(game).restore().hero.hp == 0);
    game.new_game();
    game.push(Op::Dialogue, 1);
    game.finish_commands();
    auto speech = GameState::capture(game).restore();
    game.finish_commands(true);
    speech.finish_commands(true);
    REQUIRE(glz::write_json(GameState::capture(speech)).value() ==
            glz::write_json(GameState::capture(game)).value());
}

TEST_CASE("MCP altar decorations are omitted from interaction destinations", "[mcp][navigation][tiles]") {
    auto game = room();
    game.tile_at(1, 5, 4) = Altar;
    game.tile_at(1, 4, 5) = AltarTop;
    game.tile_at(1, 6, 5) = AltarSide;
    Client client(false, game);
    REQUIRE(client.tool("inspect_tile", Json{{"x", 5}, {"y", 4}})["kind"].get<std::string>() == "npc");
    for (int x : {4, 6}) {
        const auto inspected = client.tool("inspect_tile", Json{{"x", x}, {"y", 5}});
        REQUIRE(inspected["name"].get<std::string>() == "Altar");
        REQUIRE(inspected["kind"].get<std::string>() == "decoration");
        const auto refused = client.tool("navigate", Json{{"x", x}, {"y", 5}});
        REQUIRE(refused["navigation"]["reason"].get<std::string>() == "not_a_destination");
        REQUIRE_FALSE(refused["navigation"]["reached"].get<bool>());
        REQUIRE(refused["navigation"]["inputs"].as<int>() == 0);
    }
    const auto compact = client.tool("game_state", Json{{"detail", "compact"}});
    REQUIRE(compact["floor"]["points"].get_array().size() == 1);
    REQUIRE(compact["floor"]["points"][0]["id"].as<int>() == Altar);
    REQUIRE_FALSE(compact["tile_types"].contains(std::to_string(AltarTop)));
    REQUIRE_FALSE(compact["tile_types"].contains(std::to_string(AltarSide)));
    const auto opened = client.tool("navigate", Json{{"x", 5}, {"y", 4}});
    REQUIRE(opened["navigation"]["reached"].get<bool>());
    REQUIRE(opened["phase"].get<std::string>() == "shop");
    REQUIRE(opened["pending_interaction"]["choices"].get_array().size() == 4);
}

TEST_CASE("MCP alternate monster pieces expose forecasts and navigate into combat", "[mcp][combat][tiles]") {
    for (int tile : {106, 107, 108, 109, 110, 111, 112, 113, 114, 158}) {
        CAPTURE(tile);
        auto game = room();
        game.monsters[OctopusRow] = game.monsters[32] = {250, 130, 10, 44};
        game.tile_at(1, 5, 4) = static_cast<std::uint8_t>(tile);
        const int expected_row = tile == 158 ? 32 : OctopusRow;
        Client client(false, game);
        const auto inspected = client.tool("inspect_tile", Json{{"x", 5}, {"y", 4}});
        REQUIRE(inspected["kind"].get<std::string>() == "enemy");
        REQUIRE(inspected["name"].get<std::string>() == Game::monster_name(expected_row));
        REQUIRE(inspected["enemy"]["row"].as<int>() == expected_row);
        REQUIRE(inspected["enemy"]["forecast"]["penetrates"].get<bool>());
        REQUIRE(inspected["enemy"]["forecast"]["survivable"].get<bool>());
        REQUIRE(inspected["enemy"]["forecast"]["hero_hits"].as<int>() == 3);
        REQUIRE(inspected["enemy"]["forecast"]["damage"].as<int>() == 60);
        const auto full = client.tool("game_state");
        REQUIRE(full["enemies"].get_array().size() == 1);
        REQUIRE(full["enemies"][0]["enemy"]["row"].as<int>() == expected_row);
        const auto compact = client.tool("game_state", Json{{"detail", "compact"}});
        REQUIRE(compact["floor"]["points"].get_array().size() == 1);
        REQUIRE(compact["floor"]["points"][0]["id"].as<int>() == tile);
        REQUIRE(compact["floor"]["points"][0]["reachable"].get<bool>());
        const auto type = compact["tile_types"][std::to_string(tile)];
        REQUIRE(type["kind"].get<std::string>() == "enemy");
        REQUIRE(type["available"].get<bool>());
        REQUIRE(type["enemy"]["forecast"]["damage"].as<int>() == 60);
        const auto after = client.tool("navigate", Json{{"x", 5}, {"y", 4}});
        REQUIRE(after["navigation"]["reached"].get<bool>());
        REQUIRE(after["navigation"]["inputs"].as<int>() == 1);
        REQUIRE(after["phase"].get<std::string>() == "playing");
        REQUIRE(after["hero"]["x"].as<int>() == 5);
        REQUIRE(after["hero"]["y"].as<int>() == 4);
        REQUIRE(after["hero"]["hp"].as<int>() == 940);
        REQUIRE(after["hero"]["gold"].as<int>() == 100 + (tile == 158 ? 44 : 22));
        const auto completed = client.tool("game_state");
        REQUIRE(completed["map"][cell(5, 4)].as<int>() == Road);
        REQUIRE(completed["last_encounter"]["name"].get<std::string>() == Game::monster_name(expected_row));
        REQUIRE(completed["last_encounter"]["damage"].as<int>() == 60);
    }
}

TEST_CASE("MCP refuses inert dragon and stair-cover contacts", "[mcp][navigation][tiles]") {
    for (int tile : {123, 131, 159}) {
        CAPTURE(tile);
        auto game = room();
        game.tile_at(1, 5, 4) = static_cast<std::uint8_t>(tile);
        Client client(false, game);
        const auto inspected = client.tool("inspect_tile", Json{{"x", 5}, {"y", 4}});
        REQUIRE(inspected["kind"].get<std::string>() == "decoration");
        REQUIRE_FALSE(inspected.contains("enemy"));
        REQUIRE(client.tool("game_state")["enemies"].get_array().empty());
        REQUIRE(
            client.tool("game_state", Json{{"detail", "compact"}})["floor"]["points"].get_array().empty());
        const auto after = client.tool("navigate", Json{{"x", 5}, {"y", 4}});
        REQUIRE_FALSE(after["navigation"]["reached"].get<bool>());
        REQUIRE(after["navigation"]["reason"].get<std::string>() == "refused");
        REQUIRE(after["navigation"]["inputs"].as<int>() == 1);
        const auto completed = client.tool("game_state");
        REQUIRE_FALSE(completed["last_action"]["ok"].get<bool>());
        REQUIRE(after["hero"]["x"].as<int>() == 5);
        REQUIRE(after["hero"]["y"].as<int>() == 5);
        REQUIRE(after["hero"]["hp"].as<int>() == 1000);
        REQUIRE(after["hero"]["gold"].as<int>() == 100);
        REQUIRE(completed["map"][cell(5, 4)].as<int>() == tile);
    }
}

TEST_CASE("MCP explicit batches match individual inputs and preserve replay", "[mcp][batch]") {
    Client batch, single;
    const auto steps = decode(R"([
        {"type":"action","floor":1,"action":{"type":"move","direction":"up"}},
        {"type":"navigate","floor":1,"x":4,"y":9}
    ])");
    const auto result = batch.tool("run_steps", Json{{"steps", steps}, {"detail", "full"}});
    single.act(R"({"type":"move","direction":"up"})");
    const auto expected = single.tool("navigate", Json{{"floor", 1}, {"x", 4}, {"y", 9}, {"detail", "full"}});
    REQUIRE(result["batch"]["complete"].get<bool>());
    REQUIRE(result["batch"]["executed_steps"].as<int>() == 2);
    REQUIRE(encode(result["hero"]) == encode(expected["hero"]));
    REQUIRE(batch.tool("export_replay")["replay"].get<std::string>() ==
            single.tool("export_replay")["replay"].get<std::string>());
}

TEST_CASE("MCP batches validate the whole request before mutation", "[mcp][batch]") {
    Client client;
    const auto before = encode(client.tool("game_state"));
    for (const auto invalid :
         {R"({"type":"navigate","floor":1,"x":99,"y":0})",
          R"({"type":"action","floor":1,"action":{"type":"new_game"}})",
          R"({"type":"action","floor":1,"action":{"type":"reload","kind":"slot"}})",
          R"({"type":"navigate","x":0,"y":0})", R"({"type":"room","floor":1,"x":0,"y":0})"}) {
        Json::array_t steps{
            decode(R"({"type":"action","floor":1,"action":{"type":"move","direction":"up"}})"),
            decode(invalid)};
        REQUIRE(client.raw_tool("run_steps", Json{{"steps", steps}})["result"]["isError"].get<bool>());
        REQUIRE(encode(client.tool("game_state")) == before);
    }
    REQUIRE(client.raw_tool("run_steps", Json{{"steps", Json::array_t{}}})["result"]["isError"].get<bool>());
    Json::array_t too_many(33, decode(R"({"type":"navigate","floor":1,"x":0,"y":0})"));
    REQUIRE(client.raw_tool("run_steps", Json{{"steps", too_many}})["result"]["isError"].get<bool>());
}

TEST_CASE("MCP batches retain partial progress and stop at guards and shops", "[mcp][batch]") {
    auto game = room();
    Client client(false, game);
    const auto guarded = client.tool("run_steps", Json{{"steps", decode(R"([
        {"type":"navigate","floor":1,"x":4,"y":5},
        {"type":"navigate","floor":2,"x":3,"y":5}
    ])")}});
    REQUIRE_FALSE(guarded["batch"]["complete"].get<bool>());
    REQUIRE(guarded["batch"]["reason"].get<std::string>() == "floor_mismatch");
    REQUIRE(guarded["batch"]["stopped_at"].as<int>() == 1);
    REQUIRE(guarded["batch"]["executed_steps"].as<int>() == 1);
    REQUIRE(client.tool("game_state")["hero"]["x"].as<int>() == 4);

    game.tile_at(1, 5, 3) = Altar;
    Client shop(false, game);
    const auto opened = shop.tool("run_steps", Json{{"steps", decode(R"([
        {"type":"navigate","floor":1,"x":5,"y":3},
        {"type":"action","floor":1,"action":{"type":"choose","choice":"attack"}}
    ])")}});
    REQUIRE(opened["batch"]["reason"].get<std::string>() == "interaction_open");
    REQUIRE(opened["batch"]["executed_steps"].as<int>() == 1);
    REQUIRE(opened["hero"]["gold"].as<int>() == game.hero.gold);
    REQUIRE(opened["phase"].get<std::string>() == "shop");
}

TEST_CASE("MCP batches stop after damage and floor changes", "[mcp][batch]") {
    auto game = room();
    game.hero.equipment_found[SacredShieldFlag] = 0;
    game.tile_at(1, 6, 4) = MagicianA;
    Client hazard(false, game);
    const auto hurt = hazard.tool("run_steps", Json{{"steps", decode(R"([
        {"type":"navigate","floor":1,"x":5,"y":2},
        {"type":"navigate","floor":1,"x":4,"y":2}
    ])")}});
    REQUIRE(hurt["batch"]["reason"].get<std::string>() == "damage");
    REQUIRE(hurt["batch"]["executed_steps"].as<int>() == 1);
    REQUIRE(hurt["hero"]["y"].as<int>() == 4);

    game = room();
    game.tile_at(1, 5, 4) = StairsUp;
    Client stairs(false, game);
    const auto changed = stairs.tool("run_steps", Json{{"steps", decode(R"([
        {"type":"navigate","floor":1,"x":5,"y":4},
        {"type":"navigate","floor":2,"x":4,"y":2}
    ])")}});
    REQUIRE(changed["batch"]["reason"].get<std::string>() == "floor_changed");
    REQUIRE(changed["batch"]["executed_steps"].as<int>() == 1);
    REQUIRE(changed["hero"]["floor"].as<int>() == 2);
}
