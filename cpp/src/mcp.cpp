#include "tsw/mcp.hpp"
#include "mcp_internal.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>

namespace tsw {
namespace {
using namespace mcp_detail;
constexpr std::size_t MaxMessageBytes = 8 * 1024 * 1024;
constexpr std::size_t MaxCheckpoints = 64, MaxReplayInputs = 100000;

void object_arguments(const Json& args, std::initializer_list<std::string_view> allowed) {
    if (!args.is_object())
        throw std::runtime_error("Arguments must be an object");
    for (const auto& [key, value] : args.get_object()) {
        (void)value;
        if (std::find(allowed.begin(), allowed.end(), key) == allowed.end())
            throw std::runtime_error("Unknown argument: " + key);
    }
}

const Json& field(const Json& args, std::string_view name) {
    if (!args.contains(name))
        throw std::runtime_error("Missing argument: " + std::string(name));
    return args[name];
}

std::string string_field(const Json& args, std::string_view name) {
    const auto& value = field(args, name);
    if (!value.is_string())
        throw std::runtime_error(std::string(name) + " must be a string");
    return value.get<std::string>();
}

int integer_field(const Json& args, std::string_view name, int minimum, int maximum) {
    const auto& value = field(args, name);
    if ((!value.holds<std::uint64_t>() && !value.holds<std::int64_t>()) ||
        (value.holds<std::uint64_t>() && value.get<std::uint64_t>() > std::uint64_t(maximum)) ||
        (value.holds<std::int64_t>() &&
         (value.get<std::int64_t>() < minimum || value.get<std::int64_t>() > maximum)))
        throw std::runtime_error(std::string(name) + " must be an integer from " + std::to_string(minimum) +
                                 " through " + std::to_string(maximum));
    const int result = value.as<int>();
    if (result < minimum)
        throw std::runtime_error(std::string(name) + " is out of range");
    return result;
}

std::string detail_field(const Json& args, std::string_view fallback) {
    const auto detail = args.contains("detail") ? string_field(args, "detail") : std::string(fallback);
    if (detail != "summary" && detail != "compact" && detail != "full")
        throw std::runtime_error("detail must be summary, compact or full");
    return detail;
}

SaveKind save_kind(const Json& args) {
    if (!args.contains("kind"))
        return SaveKind::Slot;
    const auto kind = string_field(args, "kind");
    if (kind == "slot")
        return SaveKind::Slot;
    if (kind == "checkpoint")
        return SaveKind::Checkpoint;
    throw std::runtime_error("kind must be slot or checkpoint (original raw Fairy format)");
}

std::filesystem::path path_field(const Json& args) {
    const auto path = string_field(args, "path");
    if (path.empty() || path.find('\0') != std::string::npos)
        throw std::runtime_error("path must be a nonempty filesystem path without NUL characters");
    return std::filesystem::path(std::u8string(path.begin(), path.end()));
}

PlayerInput player_action(const Json& value, bool developer, const Game& game) {
    if (!value.is_object())
        throw std::runtime_error("action must be an object");
    if (value.contains("floor"))
        integer_field(value, "floor", 1, 50);
    auto input = parse_input(dump(value));
    if (input.kind == InputKind::Rankings)
        throw std::runtime_error("Ranking table updates belong to replay recordings");
    if (!developer && (input.kind == InputKind::Save || input.kind == InputKind::Reload) &&
        game.inventory(Item::HeroOrb) <= 0)
        throw std::runtime_error("The Orb of the Hero is required to save");
    return input;
}

std::string history_text(const Session& session) {
    if (!session.recorder.active())
        throw std::runtime_error(
            "No complete recording for this game. Start a new game or load a recorded save.");
    std::ostringstream output;
    write_replay(output, session.recorder.history());
    return output.str();
}

std::string read_text(const std::filesystem::path& path) {
    if (std::filesystem::file_size(path) > MaxMessageBytes)
        throw std::runtime_error("Replay file exceeds 8 MiB");
    std::ifstream file(path, std::ios::binary);
    if (!file)
        throw std::runtime_error("Unable to open replay file");
    std::string result{std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
    if (file.bad())
        throw std::runtime_error("Unable to read replay file");
    return result;
}

Json integer_schema(int minimum, int maximum) {
    return Json{{"type", "integer"}, {"minimum", minimum}, {"maximum", maximum}};
}

Json object_schema(Json properties = Json::object_t{}, Json::array_t required = {}) {
    return Json{{"type", "object"},
                {"properties", properties},
                {"required", required},
                {"additionalProperties", false}};
}

Json definitions(bool developer) {
    Json::array_t tools;
    auto tool = [&](std::string_view name, std::string_view description, Json schema, bool read_only) {
        tools.emplace_back(
            Json{{"name", name},
                 {"description", description},
                 {"inputSchema", schema},
                 {"annotations", Json{{"readOnlyHint", read_only}, {"openWorldHint", false}}}});
    };
    const auto floor = integer_schema(0, FloorCount - 1);
    const Json detail{{"type", "string"}, {"enum", Json::array_t{"summary", "compact", "full"}}};
    const auto coordinates = Json{{"x", integer_schema(0, BoardWidth - 1)},
                                  {"y", integer_schema(0, BoardWidth - 1)},
                                  {"map_floor", floor}};
    tool("game_state",
         "Read current-floor destinations and reachable events. Default compact gives floor.points with "
         "descriptions/forecasts in tile_types by ID, and walkable rows (. road, # obstacle). Full includes "
         "raw maps and developer diagnostics.",
         object_schema(Json{{"map_floor", floor}, {"detail", detail}}), true);
    tool("inspect_tile",
         "Inspect a square without acting. Enemy forecasts require the Hero Orb; hidden walls keep their "
         "visible appearance. Remote floors require developer mode or an open Flight preview.",
         object_schema(coordinates, {"x", "y"}), true);
    tool("plan_path",
         "Plan through apparent road, with an obstacle allowed as the last input. Returns a closest road "
         "prefix if unreachable. Does not move or predict script/hazard effects.",
         object_schema(Json{{"x", integer_schema(0, 10)}, {"y", integer_schema(0, 10)}}, {"x", "y"}), true);
    tool("navigate",
         "Walk to a selected square using native inputs. Crosses only apparent road; intervening events "
         "require separate choices. Default interact activates the endpoint and enters opened doors. "
         "Stops on scripts, hazards, shops or floor changes. Unreachable targets do not move the hero.",
         object_schema(Json{{"x", integer_schema(0, 10)},
                            {"y", integer_schema(0, 10)},
                            {"floor", floor},
                            {"interact", Json{{"type", "boolean"}}},
                            {"detail", detail}},
                       {"x", "y"}),
         false);
    const auto action = action_schema();
    tool("game_action",
         "Apply one native input. Default summary returns stats, inventory and changed tiles; floor changes "
         "return compact destinations. Use navigate for walking. Shops require a listed choose ID.",
         object_schema(Json{{"action", action}, {"detail", detail}}, {"action"}), false);
    auto step_actions = action_schema();
    std::erase_if(step_actions["oneOf"].get_array(), [](const Json& alternative) {
        const auto name = alternative["properties"]["type"]["const"].get<std::string>();
        return name == "new_game" || name == "save" || name == "reload";
    });
    const Json step_schema{
        {"oneOf", Json::array_t{object_schema(Json{{"type", Json{{"const", "navigate"}}},
                                                   {"floor", floor},
                                                   {"x", integer_schema(0, 10)},
                                                   {"y", integer_schema(0, 10)},
                                                   {"interact", Json{{"type", "boolean"}}}},
                                              {"type", "floor", "x", "y"}),
                                object_schema(Json{{"type", Json{{"const", "action"}}},
                                                   {"floor", floor},
                                                   {"action", step_actions}},
                                              {"type", "floor", "action"})}}};
    tool("run_steps",
         "Execute 1-32 explicit navigation/action steps, each guarded by the current floor. "
         "Validates all syntax first. Stops after damage, death, a shop/Flight interaction, floor/cycle "
         "change, refused action or interrupted navigation; completed inputs remain recorded. "
         "Returns progress and final state. No planner scripts, automatic farming, resets, saves or reloads.",
         object_schema(
             Json{{"steps",
                   Json{{"type", "array"}, {"minItems", 1}, {"maxItems", 32}, {"items", step_schema}}},
                  {"detail", detail}},
             {"steps"}),
         false);
    tool("new_game", "Start a new journey and recording. Existing session checkpoints remain available.",
         object_schema(Json{{"detail", detail}}), false);
    const auto kind = Json{{"type", "string"},
                           {"enum", Json::array_t{"slot", "checkpoint"}},
                           {"description", "slot: checksummed original .dat; checkpoint: raw Fairy .dat"}};
    auto save = object_schema(Json{{"path", Json{{"type", "string"}, {"minLength", 1}}}, {"kind", kind}});
    save["dependentRequired"] = Json{{"kind", Json::array_t{"path"}}};
    tool("save_game",
         "Create an opaque session checkpoint (including open shops and Flight), up to 64 per connection. "
         "With path, write an original .dat file and replay companion at an idle command boundary, even "
         "when checkpoints are full (checkpoint is then null). Requires the Hero Orb in normal mode. "
         "Session checkpoints expire at disconnect; files persist.",
         save, false);
    auto load = object_schema(Json{{"checkpoint", Json{{"type", "string"}}},
                                   {"path", Json{{"type", "string"}, {"minLength", 1}}},
                                   {"kind", kind},
                                   {"detail", detail}});
    load["oneOf"] = Json::array_t{Json{{"required", Json::array_t{"checkpoint"}}},
                                  Json{{"required", Json::array_t{"path"}}}};
    load["dependentRequired"] = Json{{"kind", Json::array_t{"path"}}};
    tool("load_game",
         "Restore exactly one session checkpoint or original save path. Native file loads use the original "
         "reconstruction rules and resume an available replay companion. A failed load preserves the current "
         "session.",
         load, false);
    auto replay = object_schema(Json{{"path", Json{{"type", "string"}, {"minLength", 1}}},
                                     {"replay", Json{{"type", "string"}, {"maxLength", MaxMessageBytes}}},
                                     {"limit", integer_schema(0, int(MaxReplayInputs))},
                                     {"detail", detail}});
    replay["oneOf"] =
        Json::array_t{Json{{"required", Json::array_t{"path"}}}, Json{{"required", Json::array_t{"replay"}}}};
    tool("replay_game",
         "Reconstruct a JSONL recording from path or inline replay, beginning with new_game. limit selects a "
         "prefix for rewind/inspection. On success it becomes the live session and recording, ready for "
         "takeover. On failure the current session is preserved.",
         replay, false);
    tool("export_replay",
         "Export native input history. With path, returns file metadata without echoing JSONL; set "
         "include_replay to also return its text. Without path, returns inline JSONL.",
         object_schema(Json{{"path", Json{{"type", "string"}, {"minLength", 1}}},
                            {"include_replay", Json{{"type", "boolean"}}}}),
         false);
    if (developer)
        tool("simulate_actions",
             "Run at most 1000 actions on a complete copy of the native session. Does not change live state, "
             "recording, dialogue continuations or saves.",
             object_schema(Json{{"actions", Json{{"type", "array"}, {"maxItems", 1000}, {"items", action}}},
                                {"detail", detail}},
                           {"actions"}),
             true);
    return Json{{"tools", tools}};
}

Json error_response(Json id, int code, std::string_view message) {
    return Json{{"jsonrpc", "2.0"}, {"id", id}, {"error", Json{{"code", code}, {"message", message}}}};
}
} // namespace

struct McpServer::Impl {
    bool developer{}, initialized{}, ready{}, runtime_bridge{};
    Session session;
    std::map<std::string, Session> checkpoints;
    std::uint64_t next_checkpoint{};
    Json catalog;

    Impl(bool developer_access, Game game, bool bridge)
        : developer(developer_access), runtime_bridge(bridge), session(std::move(game)),
          catalog(definitions(developer_access)) {}

    int map_floor(const Json& args) const {
        const int current = session.flight >= 0 ? session.flight : session.game.hero.floor;
        const int floor = args.contains("map_floor") ? integer_field(args, "map_floor", 0, 50) : current;
        if (!developer && floor != current && floor != session.game.hero.floor)
            throw std::runtime_error("Only the current floor and open Flight preview are visible");
        return floor;
    }

    void load_file(const std::filesystem::path& path, SaveKind kind) {
        Session restored;
        restored.recorder.load(restored.game, path, kind);
        restored.game.rankings = load_rankings(path.parent_path());
        restored.recorder.rankings(restored.game.rankings);
        // A recorded load carries its deterministic action count. An unrecorded
        // native save starts a new observation timeline with recording inactive.
        for (const auto& action : restored.recorder.history()) {
            if (action.kind == InputKind::NewGame)
                restored.steps = 0;
            else
                ++restored.steps;
        }
        restored.last_action =
            Json{{"action", parse(input_json({InputKind::Reload, Direction::Up, Item::HeroOrb, -1, kind}))},
                 {"ok", true},
                 {"accepted", true},
                 {"moved", false},
                 {"messages", Json::array_t{restored.game.status}},
                 {"message", restored.game.status}};
        session = std::move(restored);
    }

    bool has_tool(std::string_view name) const {
        for (const auto& tool : catalog["tools"].get_array())
            if (tool["name"].get<std::string>() == name)
                return true;
        return false;
    }

    Json call(std::string_view name, const Json& args) {
        if (name == "game_state") {
            object_arguments(args, {"map_floor", "detail"});
            return observe(session, developer, map_floor(args), detail_field(args, "compact"));
        }
        if (name == "inspect_tile") {
            object_arguments(args, {"x", "y", "map_floor"});
            return inspect(session.game, developer, map_floor(args), integer_field(args, "x", 0, 10),
                           integer_field(args, "y", 0, 10));
        }
        if (name == "plan_path") {
            object_arguments(args, {"x", "y"});
            return plan(session, integer_field(args, "x", 0, 10), integer_field(args, "y", 0, 10));
        }
        if (name == "navigate") {
            object_arguments(args, {"x", "y", "floor", "interact", "detail"});
            if (args.contains("floor") && integer_field(args, "floor", 0, 50) != session.game.hero.floor)
                throw std::runtime_error("Navigation floor does not match the current hero floor");
            if (args.contains("interact") && !args["interact"].is_boolean())
                throw std::runtime_error("interact must be a boolean");
            const auto detail = detail_field(args, "summary");
            auto next = session;
            const auto navigation =
                navigate(next, developer, integer_field(args, "x", 0, 10), integer_field(args, "y", 0, 10),
                         !args.contains("interact") || args["interact"].get<bool>());
            const bool floor_changed = next.game.hero.floor != session.game.hero.floor;
            auto result =
                observe(next, developer, -1, detail == "summary" && floor_changed ? "compact" : detail);
            result["navigation"] = navigation;
            result["changes"] = changes(session, next, developer);
            if (detail != "full")
                result.get_object().erase("last_action"); // Aggregate all movement feedback once.
            session = std::move(next);
            return result;
        }
        if (name == "game_action" || name == "new_game") {
            object_arguments(args, name == "new_game"
                                       ? std::initializer_list<std::string_view>{"detail"}
                                       : std::initializer_list<std::string_view>{"action", "detail"});
            const auto detail = detail_field(args, name == "new_game" ? "compact" : "summary");
            const auto input = name == "new_game"
                                   ? PlayerInput{}
                                   : player_action(field(args, "action"), developer, session.game);
            auto next = session;
            next.act(input);
            const bool floor_changed = next.game.hero.floor != session.game.hero.floor;
            auto result =
                observe(next, developer, -1, detail == "summary" && floor_changed ? "compact" : detail);
            if (detail != "full" && name != "new_game")
                result["changes"] = changes(session, next, developer);
            session = std::move(next);
            return result;
        }
        if (name == "run_steps") {
            object_arguments(args, {"steps", "detail"});
            const auto detail = detail_field(args, "summary");
            const auto& steps = field(args, "steps");
            if (!steps.is_array() || steps.get_array().empty() || steps.get_array().size() > 32)
                throw std::runtime_error("steps must contain 1-32 entries");

            struct Step {
                int floor, x{}, y{};
                bool navigation{}, interact = true;
                PlayerInput action;
            };

            std::vector<Step> parsed;
            // Reject malformed later entries before executing any part of the batch.
            for (const auto& value : steps.get_array()) {
                const auto type = string_field(value, "type");
                Step step{integer_field(value, "floor", 0, 50)};
                if (type == "navigate") {
                    object_arguments(value, {"type", "floor", "x", "y", "interact"});
                    step.navigation = true;
                    step.x = integer_field(value, "x", 0, 10);
                    step.y = integer_field(value, "y", 0, 10);
                    if (value.contains("interact")) {
                        if (!value["interact"].is_boolean())
                            throw std::runtime_error("interact must be a boolean");
                        step.interact = value["interact"].get<bool>();
                    }
                } else if (type == "action") {
                    object_arguments(value, {"type", "floor", "action"});
                    step.action = player_action(field(value, "action"), developer, session.game);
                    if (step.action.kind == InputKind::NewGame || step.action.kind == InputKind::Save ||
                        step.action.kind == InputKind::Reload)
                        throw std::runtime_error("run_steps does not accept resets, saves or reloads");
                } else {
                    throw std::runtime_error("Step type must be navigate or action");
                }
                parsed.push_back(step);
            }
            auto next = session;
            Json::array_t outcomes;
            std::string reason = "completed";
            int stopped_at = -1;
            for (std::size_t i = 0; i < parsed.size(); ++i) {
                const auto& step = parsed[i];
                const auto before = next.game.hero;
                if (step.floor != before.floor) {
                    reason = "floor_mismatch";
                    stopped_at = int(i);
                    break;
                }
                Json outcome{{"index", i}};
                if (step.navigation) {
                    const auto navigation = navigate(next, developer, step.x, step.y, step.interact);
                    outcome["navigation"] = navigation;
                    const auto why = navigation["reason"].get<std::string>();
                    if (why != "arrived" && why != "ready_to_interact")
                        reason = why;
                } else {
                    next.act(step.action);
                    outcome["last_action"] = next.last_action;
                    if (!next.last_action["ok"].get<bool>())
                        reason = "refused";
                }
                outcomes.push_back(std::move(outcome));
                if (next.game.visual.dead || next.game.hero.hp <= 0)
                    reason = "dead";
                else if (next.game.hero.cycle_factor_minus_one != before.cycle_factor_minus_one ||
                         next.game.hero.later_cycle != before.later_cycle)
                    reason = "cycle_changed";
                else if (next.game.hero.floor != before.floor)
                    reason = "floor_changed";
                else if (next.game.hero.hp < before.hp)
                    reason = "damage";
                else if (next.game.busy() || next.flight >= 0)
                    reason = "interaction_open";
                if (reason != "completed") {
                    stopped_at = int(i);
                    break;
                }
            }
            auto result = observe(
                next, developer, -1,
                detail == "summary" && next.game.hero.floor != session.game.hero.floor ? "compact" : detail);
            result["changes"] = changes(session, next, developer);
            result["batch"] = Json{{"complete", stopped_at < 0},
                                   {"reason", reason},
                                   {"executed_steps", outcomes.size()},
                                   {"stopped_at", stopped_at},
                                   {"results", outcomes}};
            session = std::move(next);
            return result;
        }
        if (name == "simulate_actions") {
            object_arguments(args, {"actions", "detail"});
            const auto detail = detail_field(args, "compact");
            const auto& actions = field(args, "actions");
            if (!actions.is_array() || actions.get_array().size() > 1000)
                throw std::runtime_error("actions must be an array with at most 1000 inputs");
            auto simulation = session;
            for (const auto& action : actions.get_array())
                simulation.act(player_action(action, developer, simulation.game));
            return observe(simulation, developer, -1, detail);
        }
        if (name == "save_game") {
            object_arguments(args, {"path", "kind"});
            if (session.game.hero.hp <= 0 || (!developer && session.game.inventory(Item::HeroOrb) <= 0))
                throw std::runtime_error("A living hero with the Orb of the Hero is required to save");
            const bool checkpoint_available = checkpoints.size() < MaxCheckpoints;
            if (!checkpoint_available && !args.contains("path"))
                throw std::runtime_error(
                    "Maximum 64 session checkpoints; supply path for a persistent save or load an existing "
                    "checkpoint");
            auto next = session;
            Json result{{"checkpoint", Json{}}, {"persistent", args.contains("path")}};
            if (args.contains("path")) {
                if (session.flight >= 0)
                    throw std::runtime_error("Close the Flight selector before writing a native save");
                const auto path = path_field(args);
                if (std::filesystem::exists(path) && !std::filesystem::is_regular_file(path))
                    throw std::runtime_error("Native save path must name a regular file");
                const auto kind = save_kind(args);
                next.recorder.save(next.game, path, kind);
                ++next.steps;
                next.last_action = Json{
                    {"action", parse(input_json({InputKind::Save, Direction::Up, Item::HeroOrb, -1, kind}))},
                    {"ok", true},
                    {"accepted", true},
                    {"moved", false},
                    {"messages", Json::array_t{}},
                    {"message", "Native save written."}};
                result["path"] = string_field(args, "path");
                result["kind"] = kind == SaveKind::Slot ? "slot" : "checkpoint";
                result["recording"] = next.recorder.active();
            } else if (args.contains("kind"))
                throw std::runtime_error(
                    "kind requires path; a session checkpoint is a complete native copy");
            if (checkpoint_available) {
                const auto id = "checkpoint-" + std::to_string(next_checkpoint + 1);
                checkpoints.emplace(id, next);
                ++next_checkpoint;
                result["checkpoint"] = id;
            }
            session = std::move(next);
            return result;
        }
        if (name == "load_game") {
            object_arguments(args, {"checkpoint", "path", "kind", "detail"});
            const auto detail = detail_field(args, "compact");
            if (args.contains("checkpoint") == args.contains("path"))
                throw std::runtime_error("Supply exactly one of checkpoint or path");
            if (args.contains("checkpoint")) {
                if (args.contains("kind"))
                    throw std::runtime_error("kind is only used for native file loads");
                const auto found = checkpoints.find(string_field(args, "checkpoint"));
                if (found == checkpoints.end())
                    throw std::runtime_error("Unknown session checkpoint");
                session = found->second;
            } else {
                if (session.flight >= 0)
                    throw std::runtime_error("Close the Flight selector before loading a native save");
                load_file(path_field(args), save_kind(args));
            }
            return observe(session, developer, -1, detail);
        }
        if (name == "replay_game") {
            object_arguments(args, {"path", "replay", "limit", "detail"});
            const auto detail = detail_field(args, "compact");
            if (args.contains("path") == args.contains("replay"))
                throw std::runtime_error("Supply exactly one of path or replay");
            const auto source =
                args.contains("path") ? read_text(path_field(args)) : string_field(args, "replay");
            if (source.size() > MaxMessageBytes)
                throw std::runtime_error("Replay exceeds 8 MiB");
            std::istringstream recording(source);
            const auto inputs = read_replay(recording);
            if (inputs.empty() || inputs.front().kind != InputKind::NewGame)
                throw std::runtime_error("Replay must begin with a new_game input");
            if (inputs.size() > MaxReplayInputs)
                throw std::runtime_error("Replay exceeds 100000 inputs");
            const auto limit = args.contains("limit")
                                   ? std::size_t(integer_field(args, "limit", 0, int(MaxReplayInputs)))
                                   : inputs.size();
            const auto count = std::min(limit, inputs.size());
            Session reconstructed;
            ReplayPlayer player(inputs);
            player.seek(reconstructed.game, reconstructed.flight, count,
                        [&](const PlayerInput& input, const InputOutcome& outcome) {
                            reconstructed.record(input, outcome);
                        });
            auto result = observe(reconstructed, developer, -1, detail);
            result["replay"] =
                Json{{"executed", count}, {"total", inputs.size()}, {"complete", count == inputs.size()}};
            session = std::move(reconstructed);
            return result;
        }
        if (name == "export_replay") {
            object_arguments(args, {"path", "include_replay"});
            if (args.contains("include_replay") && !args["include_replay"].is_boolean())
                throw std::runtime_error("include_replay must be a boolean");
            const auto source = history_text(session);
            Json result{{"inputs", session.recorder.history().size()}, {"bytes", source.size()}};
            if ((!args.contains("path") && !args.contains("include_replay")) ||
                (args.contains("include_replay") && args["include_replay"].get<bool>()))
                result["replay"] = source;
            if (args.contains("path")) {
                const auto path = path_field(args);
                if (!path.parent_path().empty())
                    std::filesystem::create_directories(path.parent_path());
                std::ofstream output(path, std::ios::binary | std::ios::trunc);
                output << source;
                output.flush();
                if (!output)
                    throw std::runtime_error("Unable to write replay file");
                result["path"] = string_field(args, "path");
            }
            return result;
        }
        throw std::runtime_error("Unknown tool");
    }
};

McpServer::McpServer(bool developer, Game game, bool runtime_bridge)
    : impl_(std::make_unique<Impl>(developer, std::move(game), runtime_bridge)) {}

McpServer::~McpServer() = default;

void McpServer::load(const std::filesystem::path& path, SaveKind kind) {
    impl_->load_file(path, kind);
}

std::optional<std::string> McpServer::respond(std::string_view source) {
    using namespace mcp_detail;
    Json request;
    try {
        if (source.size() > MaxMessageBytes)
            return dump(error_response(Json{}, -32600, "Request exceeds 8 MiB"));
        request = parse(source);
    } catch (const std::exception&) {
        return dump(error_response(Json{}, -32700, "Parse error"));
    }
    Json id;
    if (request.contains("id"))
        id = request["id"];
    if (!request.is_object() || !request.contains("jsonrpc") || !request["jsonrpc"].is_string() ||
        request["jsonrpc"].get<std::string>() != "2.0" ||
        (request.contains("id") && !id.is_string() && !id.holds<std::uint64_t>() &&
         !id.holds<std::int64_t>()))
        return dump(error_response(Json{}, -32600, "Invalid Request"));
    // This server sends no requests. Unsolicited responses have nothing to complete.
    if (!request.contains("method") && (request.contains("result") || request.contains("error")))
        return std::nullopt;
    if (!request.contains("method") || !request["method"].is_string())
        return dump(error_response(id, -32600, "Invalid Request"));
    const auto method = request["method"].get<std::string>();
    if (!request.contains("id")) {
        if (method == "notifications/initialized" && impl_->initialized &&
            (!request.contains("params") || request["params"].is_object()))
            impl_->ready = true;
        return std::nullopt;
    }
    const Json params = request.contains("params") ? request["params"] : Json(Json::object_t{});
    if (!params.is_object())
        return dump(error_response(id, -32602, "params must be an object"));
    Json result;
    try {
        if (method == "initialize") {
            if (impl_->initialized)
                return dump(error_response(id, -32600, "Already initialized"));
            auto version = string_field(params, "protocolVersion");
            if (!field(params, "capabilities").is_object() || !field(params, "clientInfo").is_object())
                throw std::runtime_error("capabilities and clientInfo must be objects");
            string_field(params["clientInfo"], "name");
            string_field(params["clientInfo"], "version");
            constexpr std::array<std::string_view, 4> versions{"2024-11-05", "2025-03-26", "2025-06-18",
                                                               "2025-11-25"};
            if (std::find(versions.begin(), versions.end(), version) == versions.end())
                version = "2025-11-25";
            result = Json{
                {"protocolVersion", version},
                {"capabilities", Json{{"tools", Json::object_t{}}, {"resources", Json::object_t{}}}},
                {"serverInfo", Json{{"name", "tower-of-the-sorcerer-cpp"}, {"version", "0.11"}}},
                {"instructions",
                 "Use compact game_state floor.points and tile_types[id] to choose events, then "
                 "navigate(x,y); ordinary walking "
                 "is handled by the server. Coordinates are 0..10 from top left. Navigation stops at "
                 "unexpected "
                 "events and never crosses unselected obstacles. Default action responses are summaries; "
                 "detail=full opts into raw maps/diagnostics. All execution and replays use native inputs. "
                 "Shops require a listed choose ID. Forecasts/saves require the Hero Orb in normal mode; "
                 "developer mode reveals secrets. Save with an absolute path for persistence."}};
            impl_->initialized = true;
        } else if (method == "ping")
            result = Json::object_t{};
        else if (!impl_->ready)
            return dump(error_response(id, -32000, "Initialize and send notifications/initialized first"));
        else if (impl_->runtime_bridge && (method == "runtime/checkpoint" || method == "runtime/restore")) {
            object_arguments(params, {"path"});
            const auto path = path_field(params);
            if (method == "runtime/checkpoint")
                checkpoint_runtime(path, impl_->developer, impl_->session, impl_->checkpoints,
                                   impl_->next_checkpoint);
            else {
                try {
                    restore_runtime(path, impl_->developer, impl_->session, impl_->checkpoints,
                                    impl_->next_checkpoint);
                } catch (const IncompatibleRuntimeCheckpoint& error) {
                    auto response = error_response(id, -32003, error.what());
                    response["error"]["data"] =
                        Json{{"kind", "session_incompatible"}, {"session_continuable", false}};
                    return dump(response);
                }
            }
            result = Json{{"restored", method == "runtime/restore"}, {"version", 1}};
        } else if (method == "tools/list")
            result = impl_->catalog;
        else if (method == "tools/call") {
            const auto name = string_field(params, "name");
            if (!impl_->has_tool(name))
                return dump(error_response(id, -32602, "Unknown tool: " + name));
            const auto args = params.contains("arguments") ? params["arguments"] : Json(Json::object_t{});
            try {
                const auto value = impl_->call(name, args);
                result = Json{{"content", Json::array_t{Json{{"type", "text"}, {"text", dump(value)}}}},
                              {"structuredContent", value},
                              {"isError", false}};
            } catch (const std::exception& error) {
                result = Json{{"content", Json::array_t{Json{{"type", "text"}, {"text", error.what()}}}},
                              {"isError", true}};
            }
        } else if (method == "resources/list")
            result = Json{{"resources", Json::array_t{Json{{"uri", "tos://state"},
                                                           {"name", "Current C++ game state"},
                                                           {"mimeType", "application/json"}},
                                                      Json{{"uri", "tos://rules"},
                                                           {"name", "Native player input rules"},
                                                           {"mimeType", "application/json"}},
                                                      Json{{"uri", "tos://replay"},
                                                           {"name", "Active replay history"},
                                                           {"mimeType", "application/x-ndjson"}}}}};
        else if (method == "resources/templates/list")
            result = Json{{"resourceTemplates", Json::array_t{}}};
        else if (method == "resources/read") {
            const auto uri = string_field(params, "uri");
            std::string content, mime = "application/json";
            if (uri == "tos://state")
                content = dump(observe(impl_->session, impl_->developer, -1, "compact"));
            else if (uri == "tos://rules")
                content = dump(Json{{"action_schema", action_schema()},
                                    {"save_formats", Json::array_t{"slot", "checkpoint"}},
                                    {"native_save_bytes", 6957},
                                    {"session_checkpoint_limit", MaxCheckpoints}});
            else if (uri == "tos://replay") {
                content = history_text(impl_->session);
                mime = "application/x-ndjson";
            } else
                return dump(error_response(id, -32002, "Unknown resource: " + uri));
            result =
                Json{{"contents", Json::array_t{Json{{"uri", uri}, {"mimeType", mime}, {"text", content}}}}};
        } else
            return dump(error_response(id, -32601, "Method not found"));
    } catch (const std::exception& error) {
        return dump(error_response(id, -32602, error.what()));
    }
    return dump(Json{{"jsonrpc", "2.0"}, {"id", id}, {"result", result}});
}

void serve_mcp(McpServer& server, std::istream& input, std::ostream& output) {
    std::string line;
    while (std::getline(input, line)) {
        if (line.find_first_not_of(" \t\r") == std::string::npos)
            continue;
        if (const auto response = server.respond(line)) {
            output << *response << '\n' << std::flush;
            if (!output)
                throw std::runtime_error("Unable to write MCP response");
        }
    }
    if (input.bad())
        throw std::runtime_error("Unable to read MCP request");
}
} // namespace tsw
