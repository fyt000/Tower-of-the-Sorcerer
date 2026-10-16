#include "tsw/achievements.hpp"
#include "tsw/game.hpp"
#include "tsw/game_state.hpp"
#include "tsw/replay.hpp"
#include <catch2/catch_test_macros.hpp>
#include <chrono>
#include <fstream>
#include <sstream>

using namespace tsw;

namespace {
Game arena(int floor = 1) {
    Game game;
    game.hero.floor = floor;
    game.hero.x = game.hero.y = 5;
    game.hero.hp = game.hero.attack = game.hero.defense = 100000;
    game.floors[floor].tiles.fill(Road);
    game.hero.equipment_found[SacredShieldFlag] = 0;
    return game;
}

void defeat(Game& game, int tile) {
    game.tile_at(game.hero.floor, game.hero.x, game.hero.y - 1) = std::uint8_t(tile);
    REQUIRE(game.move(Direction::Up));
    game.finish_commands(true);
}

auto results(const Game& game) {
    return ending_achievements({game.hero, game.run_history});
}

struct SaveFixture {
    std::filesystem::path directory =
        std::filesystem::path(TSW_TEST_TEMP) /
        ("achievements-" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::filesystem::path path = directory / "save1.dat";

    ~SaveFixture() { std::filesystem::remove_all(directory); }
};

std::string contents(const std::filesystem::path& path) {
    std::ifstream input(path, std::ios::binary);
    return {std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>()};
}
} // namespace

TEST_CASE("Ending summary captures the cleared tower before cycle resets", "[achievements][scenes]") {
    auto game = arena(50);
    game.hero.gold = 123;
    game.hero.altar_purchases = 21;
    game.hero.yellow_keys = 8;
    game.hero.blue_keys = 3;
    game.hero.red_keys = 5;
    game.hero.zeno_sealed = true;
    game.run_history.dragon_defeated = true;
    const EndingSummary expected{game.hero, game.run_history};
    game.tile_at(50, 5, 4) = Zeno;
    game.move(Direction::Up);
    REQUIRE(game.ending_summary == expected);
    game.finish_commands(true);
    REQUIRE(game.ending_summary == expected);
    REQUIRE(game.hero.gold == 0);
    REQUIRE(game.hero.altar_purchases == 0);
    REQUIRE(game.hero.yellow_keys == 0);
    REQUIRE(game.run_history == RunHistory{});
    REQUIRE(ending_achievements(*game.ending_summary)[0].status == AchievementStatus::Earned);
    REQUIRE(ending_achievements(*game.ending_summary)[4].status == AchievementStatus::Earned);
    REQUIRE(ending_achievements(*game.ending_summary)[5].status == AchievementStatus::Earned);
    game.new_game();
    REQUIRE_FALSE(game.ending_summary);
}

TEST_CASE("Backside summary includes the last Zeno battle reward and seal", "[achievements][scenes]") {
    auto game = arena(50);
    game.hero.cycle_factor_minus_one = 43;
    game.hero.later_cycle = 1;
    game.hero.zeno_sealed = true;
    game.hero.gold = 10;
    game.monsters[ZenoRow] = {800, 500, 100, 500};
    game.run_history.octopus_parts_defeated = true;
    game.inventory(Item::DragonSlayer) = 1;
    defeat(game, Zeno);
    REQUIRE(game.ending_summary);
    REQUIRE(game.ending_summary->hero.gold == 510);
    REQUIRE(game.ending_summary->hero.zeno_sealed);
    REQUIRE(game.ending_summary->history.octopus_parts_defeated);
    REQUIRE(ending_achievements(*game.ending_summary)[0].status == AchievementStatus::Earned);
    REQUIRE_FALSE(game.run_history.octopus_parts_defeated);
    REQUIRE(game.run_history.dragon_slayer_acquired); // Carried equipment belongs to the new cycle too.
}

TEST_CASE("Octopus achievement follows successful outer-part battles", "[achievements][combat]") {
    for (int target : std::array<int, 4>{OctopusFirst, OctopusFirst + 1, OctopusLast, OctopusMouth}) {
        auto game = arena(32);
        defeat(game, target);
        REQUIRE(game.run_history.octopus_parts_defeated == (target != OctopusMouth));
        REQUIRE(results(game)[1].status ==
                (target == OctopusMouth ? AchievementStatus::Earned : AchievementStatus::Missed));
    }
    SECTION("An unpenetrable or fatal encounter earns no outer-part reward") {
        for (bool fatal : {false, true}) {
            auto game = arena(32);
            game.hero.attack = fatal ? 301 : 0;
            game.hero.hp = 1;
            game.hero.defense = 0;
            defeat(game, OctopusFirst);
            REQUIRE_FALSE(game.run_history.octopus_parts_defeated);
        }
    }
}

TEST_CASE("Dragon achievement requires a victory and no Dragon Slayer acquisition",
          "[achievements][combat]") {
    auto game = arena(35);
    REQUIRE(results(game)[2].status == AchievementStatus::Missed);
    SECTION("Dragon defeated without the item") {
        defeat(game, DragonHead);
        REQUIRE(results(game)[2].status == AchievementStatus::Earned);
    }
    SECTION("Acquiring and later losing the item still disqualifies the cycle") {
        game.tile_at(35, 4, 5) = DragonSlayer;
        game.move(Direction::Left);
        game.finish_commands();
        REQUIRE(game.run_history.dragon_slayer_acquired);
        game.inventory(Item::DragonSlayer) = 0;
        defeat(game, DragonHead);
        REQUIRE(results(game)[2].status == AchievementStatus::Missed);
    }
    SECTION("Using the item in combat also disqualifies the cycle") {
        game.inventory(Item::DragonSlayer) = 1;
        defeat(game, DragonHead);
        REQUIRE(results(game)[2].status == AchievementStatus::Missed);
    }
}

TEST_CASE("Altar and red key achievements use inclusive final-state thresholds", "[achievements]") {
    for (int purchases : {20, 21, 22})
        for (int keys : {4, 5, 6}) {
            auto game = arena();
            game.hero.altar_purchases = purchases;
            game.hero.red_keys = keys;
            game.run_history.complete = false; // These totals are known even for original saves.
            REQUIRE(results(game)[4].status ==
                    (purchases >= 21 ? AchievementStatus::Earned : AchievementStatus::Missed));
            REQUIRE(results(game)[5].status ==
                    (keys >= 5 ? AchievementStatus::Earned : AchievementStatus::Missed));
        }
}

TEST_CASE("Shield achievement allows leaving the shield uncollected", "[achievements]") {
    auto game = arena();
    REQUIRE(game.hero.equipment_found[SacredShieldFlag] == 0);
    REQUIRE(results(game)[3].status == AchievementStatus::Earned);
    game.run_history.complete = false;
    REQUIRE(results(game)[3].status == AchievementStatus::Unverified);
    game.run_history.shield_guards_bombed = true;
    REQUIRE(results(game)[3].status == AchievementStatus::Missed);
    game.run_history.complete = true;
    REQUIRE(results(game)[3].status == AchievementStatus::Missed);
}

TEST_CASE("Shield achievement detects Bomb targets at the two guard cells only", "[achievements][items]") {
    for (int floor : {43, 44}) {
        auto game = arena(floor);
        game.hero.y = 8;
        game.tile_at(floor, 4, 8) = GateKeeperA;
        game.tile_at(floor, 6, 8) = GateKeeperA + 1;
        game.inventory(Item::Bomb) = 1;
        REQUIRE(game.use(Item::Bomb));
        game.finish_commands(true);
        REQUIRE(game.run_history.shield_guards_bombed == (floor == 44));
        REQUIRE(results(game)[3].status ==
                (floor == 44 ? AchievementStatus::Missed : AchievementStatus::Earned));
        game.tile_at(floor, 5, 7) = SacredShield;
        game.move(Direction::Up);
        game.finish_commands(true);
        REQUIRE(results(game)[3].status ==
                (floor == 44 ? AchievementStatus::Missed : AchievementStatus::Earned));
    }
    SECTION("Bombing elsewhere on 44F does not disqualify it") {
        auto game = arena(44);
        game.tile_at(44, 4, 5) = DarkKnight;
        game.inventory(Item::Bomb) = 1;
        game.use(Item::Bomb);
        game.finish_commands(true);
        REQUIRE_FALSE(game.run_history.shield_guards_bombed);
    }
    SECTION("Ordinary guard battles qualify") {
        auto game = arena(44);
        game.hero.x = 4;
        game.hero.y = 9;
        defeat(game, GateKeeperA);
        game.tile_at(44, 5, 8) = SacredShield;
        game.move(Direction::Right);
        game.finish_commands(true);
        REQUIRE(results(game)[3].status == AchievementStatus::Earned);
    }
}

TEST_CASE("Achievement companions preserve exact original bytes and independent backups",
          "[achievements][saves]") {
    SaveFixture fixture;
    auto game = arena();
    std::stringstream original;
    game.save(original);
    game.run_history.dragon_defeated = true;
    game.save(fixture.path);
    REQUIRE(contents(fixture.path) == original.str());
    REQUIRE(contents(fixture.path).size() == 6957);
    Game restored;
    restored.load(fixture.path);
    REQUIRE(restored.run_history == game.run_history);
    const auto first_history = game.run_history;
    game.run_history.octopus_parts_defeated = true;
    game.save(fixture.path);
    REQUIRE(contents(fixture.path) == original.str());
    restored.load(fixture.path);
    REQUIRE(restored.run_history == game.run_history);
    auto backup = fixture.path;
    backup += ".bak";
    restored.load(backup);
    REQUIRE(restored.run_history == first_history);
}

TEST_CASE("Missing stale or corrupt achievement companions never fabricate a clean run",
          "[achievements][saves]") {
    SaveFixture fixture;
    auto game = arena();
    game.hero.zeno_sealed = true;
    game.save(fixture.path);
    SECTION("Absent companion") {
        std::filesystem::remove(achievement_path(fixture.path));
    }
    SECTION("Invalid JSON") {
        std::ofstream(achievement_path(fixture.path)) << "{invalid";
    }
    SECTION("Incomplete history") {
        const auto path = achievement_path(fixture.path);
        auto text = contents(path);
        const auto at = text.find("\"complete\":true,");
        REQUIRE(at != std::string::npos);
        text.erase(at, std::string("\"complete\":true,").size());
        std::ofstream(path) << text;
    }
    SECTION("Save replaced without its companion") {
        game.hero.gold = 100;
        std::ofstream output(fixture.path, std::ios::binary | std::ios::trunc);
        game.save(output);
    }
    SECTION("Unsupported version") {
        const auto path = achievement_path(fixture.path);
        auto text = contents(path);
        text.replace(text.find("\"version\":1"), std::string("\"version\":1").size(), "\"version\":9");
        std::ofstream(path) << text;
    }
    Game restored;
    restored.load(fixture.path);
    REQUIRE_FALSE(restored.run_history.complete);
    REQUIRE(results(restored)[0].status == AchievementStatus::Earned);
    REQUIRE(results(restored)[1].status == AchievementStatus::Unverified);
    REQUIRE(results(restored)[2].status == AchievementStatus::Unverified);
    REQUIRE(results(restored)[3].status == AchievementStatus::Unverified);
    restored.run_history.octopus_parts_defeated = true;
    REQUIRE(results(restored)[1].status == AchievementStatus::Missed);
}

TEST_CASE("Checkpoint companions and runtime snapshots retain run evidence", "[achievements][saves]") {
    SaveFixture fixture;
    auto game = arena();
    game.run_history.shield_guards_bombed = true;
    game.save(fixture.path, SaveKind::Checkpoint);
    Game restored;
    restored.load(fixture.path, SaveKind::Checkpoint);
    REQUIRE(restored.run_history == game.run_history);
    game.ending_summary = EndingSummary{game.hero, game.run_history};
    restored = GameState::capture(game).restore();
    REQUIRE(restored.run_history == game.run_history);
    REQUIRE(restored.ending_summary == game.ending_summary);
    int flight = -1;
    apply_input(restored, flight, {InputKind::Reload});
    REQUIRE(restored.run_history == game.run_history);
    REQUIRE(restored.ending_summary == game.ending_summary);
}

TEST_CASE("An original save without history stays unverified after saving again", "[achievements][saves]") {
    SaveFixture fixture;
    Game game;
    std::stringstream record;
    game.save(record);
    game.load(record);
    REQUIRE_FALSE(game.run_history.complete);
    game.save(fixture.path);
    Game restored;
    restored.load(fixture.path);
    REQUIRE_FALSE(restored.run_history.complete);
    restored.next_cycle();
    REQUIRE(restored.run_history.complete);
}

TEST_CASE("A failed save restores its detached achievement companion", "[achievements][saves]") {
    SaveFixture fixture;
    auto game = arena();
    game.run_history.octopus_parts_defeated = true;
    game.save(fixture.path);
    const auto saved_history = game.run_history;
    auto temporary = fixture.path;
    temporary += ".tmp";
    std::filesystem::create_directory(temporary); // Force the original save writer to fail.
    game.run_history = {};
    REQUIRE_THROWS(game.save(fixture.path));
    Game restored;
    restored.load(fixture.path);
    REQUIRE(restored.run_history == saved_history);
}

TEST_CASE("A committed save keeps its replay even when achievement metadata fails",
          "[achievements][replay][saves]") {
    SaveFixture fixture;
    Game game;
    Recorder recorder(true);
    recorder.new_game();
    recorder.save(game, fixture.path);
    auto backup = fixture.path;
    backup += ".bak";
    const auto blocked = achievement_path(backup);
    std::filesystem::create_directory(blocked);
    std::ofstream(blocked / "occupied") << "Prevent backup removal";
    int flight = -1;
    const PlayerInput move = PlayerInput::move(Direction::Up);
    apply_input(game, flight, move);
    game.finish_commands(true);
    recorder.append(move);
    REQUIRE_THROWS_AS(recorder.save(game, fixture.path), AchievementSaveError);
    REQUIRE(recorder.active());
    Game restored;
    restored.load(fixture.path);
    REQUIRE(restored.hero == game.hero);
    REQUIRE_FALSE(restored.run_history.complete);
    std::ifstream input(recording_path(fixture.path));
    ReplayPlayer player(read_replay(input));
    Game replayed;
    player.seek(replayed, flight, player.size());
    std::stringstream record;
    replayed.save(record);
    REQUIRE(record.str() == contents(fixture.path));
}
