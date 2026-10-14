#include "tsw/planner.hpp"
#include <cmath>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace tsw;
namespace route = tsw::planner;

namespace {
constexpr auto Help = R"(Native route planning tools (bounded, heuristic; no optimality claim)

  tsw_route inspect REPLAY [PREFIX]
  tsw_route verify REPLAY
  tsw_route search REPLAY PREFIX OUTPUT_PREFIX [--goal 11|21] [--purchases N]
                   [--width N] [--depth N] [--seconds N] [--results N] [--policy 0|1|2]
  tsw_route run REPLAY SCRIPT OUTPUT.jsonl
  tsw_route rebase ORIGINAL NEW_PREFIX SPLIT OUTPUT.jsonl
  tsw_route improve REPLAY BOUNDARY OUTPUT.jsonl [--seconds N]
  tsw_route economy REPLAY OUTPUT_PREFIX [--seconds N] [--rounds N] [--width N]
  tsw_route ledger REPLAY

PREFIX, SPLIT and BOUNDARY count native input records, starting at 1.
Search goals are first arrival at 11F or 21F. Defaults: 11F, one purchase,
width 128, depth 120, 60 seconds, eight outputs, balanced policy.
Scripts: go/room X Y; land FLOOR [X Y]; move DIRECTION; buy -1|0|1|2;
         item NAME; sweep. room may collect intervening items and spend keys.
improve tries earlier stat pickups on floors 1-20, preserving the comparison
board, stats, keys and spending, and validates the full continuation.
verify checks the complete first-cycle 50F seal challenge and all Octopus gold.
economy keeps full verified routes after key detours, door bypasses and
omitted key purchases; defaults: 60 seconds, three rounds, six retained routes.
ledger reports milestone resources and the actual merchant/key transactions.
Exit codes: 0 success; 1 invalid input/error; 2 bounded search found no goal.
Existing output files are never overwritten. The connected game is untouched.
)";

std::vector<PlayerInput> read(const std::string& path) {
    std::ifstream stream(path);
    if (!stream)
        throw std::invalid_argument("Cannot read " + path);
    return read_replay(stream);
}

int integer(const std::string& text) {
    std::size_t used = 0;
    const int result = std::stoi(text, &used);
    if (used != text.size() || result < 0)
        throw std::invalid_argument("Expected nonnegative integer: " + text);
    return result;
}

double duration(const std::string& text) {
    std::size_t used = 0;
    const double value = std::stod(text, &used);
    if (used != text.size() || !std::isfinite(value) || value <= 0)
        throw std::invalid_argument("Expected positive seconds: " + text);
    return value;
}

std::span<const PlayerInput> prefix(const std::vector<PlayerInput>& inputs, int count) {
    if (count < 1 || std::size_t(count) > inputs.size())
        throw std::invalid_argument("Prefix is outside the replay");
    return std::span(inputs).first(count);
}

void publish(const route::Route& candidate, const std::string& path) {
    route::write_route(candidate, path);
    std::cout << "output=" << path << ' ';
    route::print_summary(candidate, std::cout);
}
} // namespace

int main(int argc, char** argv) try {
    if (argc == 1 || (argc == 2 && std::string(argv[1]) == "--help")) {
        std::cout << Help;
        return 0;
    }
    if (argc < 3)
        throw std::invalid_argument("Missing replay; use --help");
    const std::string command = argv[1];
    const auto inputs = read(argv[2]);
    if (command == "inspect" && (argc == 3 || argc == 4)) {
        const auto candidate =
            route::replay(prefix(inputs, argc == 4 ? integer(argv[3]) : int(inputs.size())));
        route::print_summary(candidate, std::cout);
        std::cout << gameplay_json(candidate.game, candidate.flight) << '\n';
    } else if (command == "verify" && argc == 3) {
        route::verify_challenge(inputs, std::cout);
    } else if (command == "run" && argc == 5) {
        std::ifstream script(argv[3]);
        if (!script)
            throw std::invalid_argument("Cannot read script");
        publish(route::run_script(route::replay(inputs), script, std::cout), argv[4]);
    } else if (command == "rebase" && argc == 6) {
        publish(route::rebase(inputs, route::replay(read(argv[3])), integer(argv[4])), argv[5]);
    } else if (command == "improve" && (argc == 5 || argc == 7)) {
        if (argc == 7 && std::string(argv[5]) != "--seconds")
            throw std::invalid_argument("Unknown improve option");
        const auto improved = route::improve_pickups(route::replay(inputs), integer(argv[3]),
                                                     argc == 7 ? duration(argv[6]) : 60, std::cout);
        publish(improved, argv[4]);
    } else if (command == "ledger" && argc == 3) {
        route::report_economy(route::replay(inputs), std::cout);
    } else if (command == "economy" && argc >= 4 && argc % 2 == 0) {
        route::EconomyOptions options;
        for (int i = 4; i < argc; i += 2) {
            const std::string flag = argv[i], value = argv[i + 1];
            if (flag == "--seconds")
                options.seconds = duration(value);
            else if (flag == "--rounds")
                options.rounds = integer(value);
            else if (flag == "--width")
                options.width = integer(value);
            else
                throw std::invalid_argument("Unknown economy option: " + flag);
        }
        const auto result = route::improve_economy(route::replay(inputs), options, std::cout);
        for (std::size_t i = 0; i < result.routes.size(); ++i) {
            std::cout << "candidate=" << i << '\n';
            route::report_economy(result.routes[i], std::cout);
            publish(result.routes[i], std::string(argv[3]) + "-" + std::to_string(i) + ".jsonl");
        }
    } else if (command == "search" && argc >= 5 && argc % 2 == 1) {
        route::SearchOptions options;
        for (int i = 5; i < argc; i += 2) {
            const std::string flag = argv[i], value = argv[i + 1];
            if (flag == "--seconds")
                options.seconds = duration(value);
            else if (flag == "--goal")
                options.goal_floor = integer(value);
            else if (flag == "--purchases")
                options.max_purchases = integer(value);
            else if (flag == "--width")
                options.width = integer(value);
            else if (flag == "--depth")
                options.depth = integer(value);
            else if (flag == "--results")
                options.max_results = integer(value);
            else if (flag == "--policy")
                options.policy = integer(value);
            else
                throw std::invalid_argument("Unknown search option: " + flag);
        }
        const auto result =
            route::search(route::replay(prefix(inputs, integer(argv[3]))), options, std::cout);
        for (std::size_t i = 0; i < result.goals.size(); ++i)
            publish(result.goals[i], std::string(argv[4]) + "-" + std::to_string(i) + ".jsonl");
        if (result.goals.empty())
            publish(result.best_partial, std::string(argv[4]) + "-partial.jsonl");
        std::cout << "goals=" << result.goals.size() << " time_limit=" << result.time_limit << '\n';
        return result.goals.empty() ? 2 : 0;
    } else {
        throw std::invalid_argument("Unknown command or wrong argument count; use --help");
    }
    return 0;
} catch (const std::exception& error) {

    std::cerr << "Error: " << error.what() << '\n';
    return 1;
}
