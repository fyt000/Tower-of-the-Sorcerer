#include "planner_internal.hpp"
#include "tsw/planner.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <fstream>
#include <sstream>

using namespace tsw;
using namespace tsw::planner;

namespace {
const std::vector<PlayerInput>& fixture() {
    static const auto inputs = [] {
        std::ifstream stream(TSW_PLANNER_FIXTURE);
        if (!stream)
            throw std::runtime_error("Missing planner fixture");
        return read_replay(stream);
    }();
    return inputs;
}

Route at(std::size_t count) {
    return replay(std::span(fixture()).first(count));
}
} // namespace

TEST_CASE("Native seal replay satisfies every campaign boundary", "[planner]") {
    std::ostringstream report;
    REQUIRE_NOTHROW(verify_challenge(fixture(), report));
    REQUIRE(report.str().find("damage=304 margin=57") != std::string::npos);
    REQUIRE_THROWS_WITH(verify_challenge(std::span(fixture()).first(9928), report),
                        "Finish sequence incomplete");
}

TEST_CASE("Octopus farming preserves outer rewards before the mouth", "[planner]") {
    detail::Engine engine;
    const auto before = at(5763);
    REQUIRE(detail::farm_gold(before.game, OctopusFirst) == 50);
    REQUIRE(detail::farm_gold(before.game, OctopusMouth) == 100);
    REQUIRE(detail::farm_gold(before.game, DragonFirst) == 0);
    REQUIRE(detail::farm_gold(before.game, DragonHead) == 0);
    REQUIRE_FALSE(engine.free_tile(before.game, OctopusMouth));
    const auto outer_complete = at(5772);
    REQUIRE(engine.free_tile(outer_complete.game, OctopusMouth));
    const auto complete = at(5773);
    REQUIRE(complete.game.hero.gold - before.game.hero.gold == 500);
    REQUIRE(complete.game.hero.hp == before.game.hero.hp);
}

TEST_CASE("Automatic late sweep preserves HP and deferred healing", "[planner]") {
    detail::Engine engine;
    auto candidate = at(8964);
    const auto before = candidate.game;
    std::vector<PlayerInput> actions;
    engine.normalize_local(candidate.game, actions);
    REQUIRE(candidate.game.hero.hp == before.hero.hp);
    REQUIRE(candidate.game.tile_at(41, 4, 3) == Sorcerer);
    REQUIRE(candidate.game.tile_at(41, 6, 3) == Sorcerer);
    REQUIRE(candidate.game.tile_at(35, 4, 4) == BluePotion);
    REQUIRE(at(8965).game.hero.hp == before.hero.hp / 2);
}

TEST_CASE("Script errors are reported before publishing partial output", "[planner]") {
    const auto root = at(53);
    const auto original = gameplay_json(root.game);
    for (const auto* text : {"room 11 0", "room x 0", "go 1 1", "land 0", "buy 7", "sweep extra"}) {
        std::istringstream script(text);
        std::ostringstream log;
        REQUIRE_THROWS_WITH(run_script(root, script, log), Catch::Matchers::StartsWith("Script line 1:"));
    }
    REQUIRE(gameplay_json(root.game) == original);
}

TEST_CASE("Explicit seal script reproduces the final native replay", "[planner]") {
    std::istringstream script("# Preserve every diagonal guard.\n"
                              "go 4 5\nitem descent\ngo 5 4\nitem bomb\ngo 4 5\nitem ascent\n");
    std::ostringstream log;
    const auto result = run_script(at(9928), script, log);
    REQUIRE(result.inputs == fixture());
    REQUIRE_NOTHROW(verify_challenge(result.inputs, log));
}

TEST_CASE("Search respects bounds and exports a reproducible partial candidate", "[planner]") {
    auto root = at(53);
    SearchOptions options;
    options.depth = 1;
    options.width = 4;
    std::ostringstream log;
    const auto result = search(root, options, log);
    REQUIRE(result.layers == 1);
    REQUIRE(result.goals.empty());
    REQUIRE(result.evaluated > 0);
    REQUIRE(gameplay_json(replay(result.best_partial.inputs).game) ==
            gameplay_json(result.best_partial.game));
    options.goal_floor = 50;
    REQUIRE_THROWS_AS(search(root, options, log), std::invalid_argument);
}

TEST_CASE("Earlier gem acquisition improves the opening without changing its resources", "[planner]") {
    const auto baseline = replay(fixture());
    std::ostringstream log;
    const auto improved = improve_pickups(baseline, 2864, 30, log);
    REQUIRE(improved.inputs != baseline.inputs);
    REQUIRE(log.str().find("boundary_hp=1774 gain=51") != std::string::npos);
    REQUIRE(detail::same_progress(improved.game, baseline.game));
    REQUIRE(improved.game.hero.hp >= baseline.game.hero.hp);
    REQUIRE_NOTHROW(verify_challenge(improved.inputs, log));
}

TEST_CASE("Event search can finish the arena through native inputs", "[planner]") {
    SearchOptions options;
    options.width = 4;
    options.depth = 8;
    options.seconds = 30;
    std::ostringstream log;
    const auto result = search(at(1505), options, log);
    REQUIRE_FALSE(result.goals.empty());
    for (const auto& goal : result.goals) {
        REQUIRE(goal.game.hero.highest_floor >= 11);
        REQUIRE(goal.game.hero.altar_purchases == 1);
        REQUIRE(gameplay_json(replay(goal.inputs).game) == gameplay_json(goal.game));
    }
}

TEST_CASE("Invalid replay prefixes cannot introduce external state", "[planner]") {
    REQUIRE_THROWS_AS(replay({}), std::invalid_argument);
    const std::array<PlayerInput, 2> reset{{{InputKind::NewGame}, {InputKind::NewGame}}};
    REQUIRE_THROWS_AS(replay(reset), std::invalid_argument);
    const std::array<PlayerInput, 2> reload{{{InputKind::NewGame}, {InputKind::Reload}}};
    REQUIRE_THROWS_AS(replay(reload), std::invalid_argument);
}

TEST_CASE("An omitted merchant purchase does not trap continuation in a later offer", "[planner]") {
    // Buy the 31F bundle in the reference, then revisit its merchant for a hint.
    // Declining instead must also decline the later offer through native inputs.
    auto prefix = at(4532);
    REQUIRE(prefix.game.dialogue);
    REQUIRE(prefix.game.dialogue->shop);
    REQUIRE(detail::input(prefix.game, detail::choose(-1), prefix.inputs));
    const auto tail = std::span(fixture()).first(4930);
    REQUIRE_THROWS(rebase(tail, prefix, 4533));
    const auto continued = detail::continue_route(tail, prefix, 4533, true);
    const auto reference = at(4930);
    REQUIRE(continued.game.hero.floor == reference.game.hero.floor);
    REQUIRE(continued.game.hero.x == reference.game.hero.x);
    REQUIRE(continued.game.hero.y == reference.game.hero.y);
    REQUIRE(continued.game.hero.gold == reference.game.hero.gold + 1000);
    REQUIRE_FALSE(continued.game.dialogue);
    REQUIRE(gameplay_json(replay(continued.inputs).game) == gameplay_json(continued.game));
}

TEST_CASE("Economy search validates continuations and preserves the control route", "[planner]") {
    const auto baseline = replay(fixture());
    // Leave the optional 12F merchant approach unopened: its two fights give
    // only 34 gold, whereas the later 38F yellow-key bundle costs 200.
    const auto seed = detail::continue_route(fixture(), at(4989), 5016, true);
    std::ostringstream log;
    REQUIRE_NOTHROW(verify_challenge(seed.inputs, log));
    REQUIRE(seed.game.hero.gold == baseline.game.hero.gold - 34);
    EconomyOptions options;
    options.rounds = 2;
    options.width = 6;
    options.seconds = 30;
    const auto result = improve_economy(seed, options, log);
    REQUIRE(result.routes.front().inputs == seed.inputs);
    REQUIRE(result.trials > 0);
    bool saved_bundle = false;
    for (const auto& candidate : result.routes) {
        REQUIRE_NOTHROW(verify_challenge(candidate.inputs, log));
        const auto reproduced = replay(candidate.inputs);
        REQUIRE(gameplay_json(reproduced.game) == gameplay_json(candidate.game));
        saved_bundle |= candidate.game.hero.merchant_used[8] == 0 &&
                        candidate.game.hero.gold >= baseline.game.hero.gold + 166;
    }
    REQUIRE(saved_bundle);
    options.width = 1;
    REQUIRE_THROWS_AS(improve_economy(seed, options, log), std::invalid_argument);
    REQUIRE_THROWS(improve_economy(at(1551), EconomyOptions{}, log));
}

TEST_CASE("The combined economy recording preserves the opening gains and full seal", "[planner]") {
    std::ifstream stream(TSW_PLANNER_ECONOMY_FIXTURE);
    REQUIRE(stream.good());
    const auto inputs = read_replay(stream);
    const auto complete = replay(inputs);
    std::ostringstream report;
    REQUIRE_NOTHROW(verify_challenge(inputs, report));
    REQUIRE(complete.game.hero.gold == 1330);
    REQUIRE(complete.game.hero.hp == 361);
    REQUIRE(complete.game.hero.merchant_used[8] == 0);
    const auto first11 = replay(std::span(inputs).first(1836));
    REQUIRE(first11.game.hero.floor == 11);
    REQUIRE(first11.game.hero.hp == 736);
    REQUIRE(first11.game.hero.yellow_keys == 4);
    const auto first21 = replay(std::span(inputs).first(3245));
    REQUIRE(first21.game.hero.floor == 21);
    REQUIRE(first21.game.hero.hp == 1880);
    REQUIRE(first21.game.hero.yellow_keys == 7);
}

TEST_CASE("Earlier key sales fund defense while preserving a potion for Master", "[planner]") {
    std::ifstream stream(TSW_PLANNER_CASHFLOW_FIXTURE);
    REQUIRE(stream.good());
    const auto inputs = read_replay(stream);
    std::ostringstream report;
    REQUIRE_NOTHROW(verify_challenge(inputs, report));
    REQUIRE(report.str().find("damage=304 margin=307") != std::string::npos);

    Game game;
    int flight = -1, sales = 0;
    bool bridge_funded = false, replacement_bought = false, potion_deferred = false;
    for (const auto& action : inputs) {
        const auto old = game.hero;
        apply_input(game, flight, action);
        settle_action(game);
        const auto& h = game.hero;
        if (action.kind == InputKind::Choose && h.floor == 28 && h.gold == old.gold + 100)
            ++sales;
        if (action.kind == InputKind::Choose && h.floor == 31 && h.gold == old.gold - 1000) {
            // Three sales bridge the earlier 920-gold defense purchase and
            // this required key bundle, leaving only one gold at this point.
            REQUIRE(sales == 3);
            REQUIRE(h.altar_purchases == 10);
            REQUIRE(h.gold == 1);
            bridge_funded = true;
        }
        if (action.kind == InputKind::Choose && h.floor == 38 && h.gold == old.gold - 200) {
            REQUIRE(sales == 3);
            REQUIRE(h.yellow_keys == old.yellow_keys + 3);
            replacement_bought = true;
        }
        if (h.floor == 41 && h.x == 0 && h.y == 0 && h.hp == old.hp + 250) {
            REQUIRE(h.attack == 409);
            REQUIRE(h.defense == 348);
            REQUIRE(h.merchant_used[10] == 1);
            REQUIRE(game.tile_at(25, 5, 5) == GreatMagicMaster);
            potion_deferred = true;
        }
    }
    REQUIRE(bridge_funded);
    REQUIRE(replacement_bought);
    REQUIRE(potion_deferred);
    REQUIRE(sales == 8);
    REQUIRE(game.hero.hp == 611);
    REQUIRE(game.hero.gold == 1930);
    REQUIRE(game.hero.yellow_keys == 0);
}
