#pragma once
#include "tsw/replay.hpp"
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <iosfwd>
#include <span>
#include <vector>

namespace tsw::planner {
// These bounds limit a heuristic search; exhausting them does not prove impossibility.
struct SearchOptions {
    int goal_floor = 11;
    int max_purchases = 1;
    int width = 128;
    int depth = 120;
    double seconds = 60;
    int max_results = 8;
    int policy = 0; // 0: balanced, 1: attack, 2: defense.
};

struct Route {
    Game game;
    std::vector<PlayerInput> inputs;
    int flight = -1;
};

struct SearchResult {
    std::vector<Route> goals;
    Route best_partial;
    std::uint64_t evaluated{}, rejected{};
    int layers{};
    bool time_limit{};
};

struct EconomyOptions {
    double seconds = 60;
    int rounds = 3;
    int width = 6;
};

struct EconomyResult {
    // Complete, independently verified continuations, including the original.
    // Alternatives can trade early HP, keys, gold and unopened rooms.
    std::vector<Route> routes;
    std::uint64_t trials{}, rejected{};
    int rounds{};
    bool time_limit{};
};

// A blocked contact is a legal input. Death, resets, reloads and later cycles are rejected.
Route replay(std::span<const PlayerInput> inputs);
SearchResult search(const Route& root, const SearchOptions&, std::ostream& progress);

// Commands are atomic: a failing line throws without exporting its partial route.
Route run_script(const Route& root, std::istream& script, std::ostream& progress);

// Rejoin the original walking route after a changed prefix; never edits game state.
Route rebase(std::span<const PlayerInput> original, const Route& prefix, std::size_t split);

// Try moving a later pickup earlier, then replay the original continuation. Only
// equivalent board/inventory/stat outcomes with more HP at the comparison boundary qualify.
Route improve_pickups(const Route& route, std::size_t end, double seconds, std::ostream& progress);

// Search key detours, door bypasses and omitted key purchases. Checkpoints are
// observations, not goals: every retained route must satisfy the full seal contract.
EconomyResult improve_economy(const Route&, const EconomyOptions&, std::ostream& progress);
void report_economy(const Route&, std::ostream&);

// Independent whole-route checks for the first-cycle seal challenge. Throws on failure.
void verify_challenge(std::span<const PlayerInput>, std::ostream& report);
void write_route(const Route&, const std::filesystem::path& output);
void print_summary(const Route&, std::ostream&);
} // namespace tsw::planner
