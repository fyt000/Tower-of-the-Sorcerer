#include "tsw/mcp.hpp"
#include "tsw/replay.hpp"
#include <charconv>
#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace {
std::size_t number(std::string_view text) {
    std::size_t value{};
    const auto [end, error] = std::from_chars(text.data(), text.data() + text.size(), value);
    if (error != std::errc{} || end != text.data() + text.size())
        throw std::runtime_error("Expected a nonnegative integer: " + std::string(text));
    return value;
}
} // namespace

int main(int argc, char** argv) try {
    using namespace tsw;
    const std::string mode = argc > 1 ? argv[1] : "--help";
    if (mode == "--help" || mode == "help") {
        std::cout
            << "Tower of the Sorcerer gameplay CLI\n"
               "tsw_cli state [--load FILE] [--checkpoint] [--map-floor N]\n"
               "tsw_cli replay FILE [--limit N] [--load FILE] [--checkpoint] [--map-floor N]\n"
               "tsw_cli headless [--load FILE] [--checkpoint] [--map-floor N]\n"
               "tsw_cli mcp [--developer] [--load FILE] [--checkpoint]\n"
               "Replay reads JSONL player commands and prints final gameplay values.\n"
               "Headless reads stdin and prints values after each command.\n"
               "MCP serves newline-delimited JSON-RPC on stdin/stdout, with save/load and replay tools.\n"
               "--limit stops replay after N commands for inspecting a prefix.\n"
               "--checkpoint reads the original raw Fairy format.\n";
        return 0;
    }
    if (mode != "state" && mode != "replay" && mode != "headless" && mode != "mcp")
        throw std::runtime_error("Unknown mode: " + mode);
    std::filesystem::path replay, load;
    int next = 2, map_floor = -1;
    auto limit = std::numeric_limits<std::size_t>::max();
    SaveKind kind = SaveKind::Slot;
    bool developer = false, runtime_bridge = false;
    if (mode == "replay") {
        if (argc <= next || std::string_view(argv[next]).starts_with("--"))
            throw std::runtime_error("replay requires a JSONL file");
        replay = argv[next++];
    }
    for (; next < argc; ++next) {
        const std::string option = argv[next];
        if (option == "--checkpoint")
            kind = SaveKind::Checkpoint;
        else if (option == "--developer" && mode == "mcp")
            developer = true;
        else if (option == "--runtime-bridge" && mode == "mcp")
            runtime_bridge = true;
        else if (option == "--load" && next + 1 < argc)
            load = argv[++next];
        else if (option == "--limit" && mode == "replay" && next + 1 < argc)
            limit = number(argv[++next]);
        else if (option == "--map-floor" && mode != "mcp" && next + 1 < argc) {
            const auto floor = number(argv[++next]);
            if (floor >= FloorCount)
                throw std::runtime_error("Map floor must be 0..50");
            map_floor = static_cast<int>(floor);
        } else
            throw std::runtime_error("Unknown or incomplete option: " + option);
    }
    if (kind == SaveKind::Checkpoint && load.empty())
        throw std::runtime_error("--checkpoint requires --load FILE");
    if (mode == "mcp") {
        McpServer server(developer, Game{}, runtime_bridge);
        if (!load.empty())
            server.load(load, kind);
        serve_mcp(server, std::cin, std::cout);
        return 0;
    }
    Game game;
    int flight = -1;
    if (!load.empty()) {
        game.load(load, kind);
        game.rankings = load_rankings(load.parent_path());
    }
    std::ifstream recording;
    if (mode == "replay") {
        recording.open(replay, std::ios::binary);
        if (!recording)
            throw std::runtime_error("Unable to open recording: " + replay.string());
    }
    if (mode != "state") {
        auto& input = mode == "replay" ? static_cast<std::istream&>(recording) : std::cin;
        std::size_t line_number{}, commands{};
        while (commands < limit) {
            const auto action = read_replay_input(input, line_number);
            if (!action)
                break;
            try {
                execute_input(game, flight, *action);
                ++commands;
                if (mode == "headless")
                    std::cout << gameplay_json(game, flight, map_floor) << '\n' << std::flush;
            } catch (const std::exception& error) {
                throw std::runtime_error("Line " + std::to_string(line_number) + ": " + error.what());
            }
        }
        if (input.bad())
            throw std::runtime_error("Unable to read recording");
    }
    if (mode != "headless")
        std::cout << gameplay_json(game, flight, map_floor) << '\n';
    return 0;
} catch (const std::exception& error) {

    std::cerr << error.what() << '\n';
    return 1;
}
