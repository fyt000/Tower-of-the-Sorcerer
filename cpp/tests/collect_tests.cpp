#include "tsw/collect.hpp"
#include "tsw/replay.hpp"
#include <catch2/catch_test_macros.hpp>
#include <sstream>

using namespace tsw;

namespace {
Game corridor(int floor = 1) {
    Game game;
    game.hero.floor = game.hero.highest_floor = floor;
    game.hero.x = 1;
    game.hero.y = 5;
    game.floors[floor].tiles.fill(Wall);
    for (int x = 1; x <= 9; ++x)
        game.tile_at(floor, x, 5) = Road;
    return game;
}

std::string saved(const Game& game) {
    std::ostringstream output;
    game.save(output);
    return output.str();
}
} // namespace

TEST_CASE("Collection uses native rewards for every pickup floor tier and cycle", "[collect][items]") {
    for (int floor : {1, 35}) {
        for (int cycle : {0, BacksideFactor - 1}) {
            for (int tile = YellowKey; tile <= SacredShield; ++tile) {
                INFO("floor=" << floor << " cycle=" << cycle << " tile=" << tile);
                auto game = corridor(floor);
                game.hero.cycle_factor_minus_one = cycle;
                game.tile_at(floor, 2, 5) = static_cast<std::uint8_t>(tile);
                auto expected = game;
                REQUIRE(expected.move(Direction::Right));
                expected.finish_commands();
                REQUIRE(expected.move(Direction::Left));
                expected.finish_commands();
                const auto items = collect_items(game, false);
                REQUIRE(items.size() == 1);
                REQUIRE(items[0].position == cell(2, 5));
                REQUIRE(items[0].tile == tile);
                REQUIRE(game.hero == expected.hero);
                REQUIRE(game.floors == expected.floors);
                REQUIRE(saved(game) == saved(expected));
                REQUIRE(game.hero.x == 1);
                REQUIRE(game.hero.y == 5);
                REQUIRE_FALSE(game.busy());
            }
        }
    }
}

TEST_CASE("Collection clears connected chains and remains a one-shot activation", "[collect][items]") {
    auto game = corridor();
    for (int x = 2; x <= 9; ++x)
        game.tile_at(1, x, 5) = x % 2 ? RedPotion : YellowKey;
    const auto hp = game.hero.hp;
    REQUIRE(collect_items(game, false).size() == 8);
    REQUIRE(game.hero.yellow_keys == 4);
    REQUIRE(game.hero.hp == hp + 200);
    REQUIRE(game.hero.x == 1);
    REQUIRE(game.hero.y == 5);
    REQUIRE(collect_items(game, false).empty());
    // Newly available items wait for another explicit activation.
    game.tile_at(1, 3, 5) = BlueGem;
    REQUIRE(game.tile_at(1, 3, 5) == BlueGem);
    REQUIRE(collect_items(game, false).size() == 1);
}

TEST_CASE("Collection except potions preserves both colors and their blocked branches", "[collect][items]") {
    for (const auto potion : {RedPotion, BluePotion}) {
        auto game = corridor();
        game.tile_at(1, 2, 5) = YellowKey;
        game.tile_at(1, 3, 5) = potion;
        game.tile_at(1, 4, 5) = RedGem;
        const auto hp = game.hero.hp, attack = game.hero.attack;
        REQUIRE(collect_items(game, true).size() == 1);
        REQUIRE(game.tile_at(1, 3, 5) == potion);
        REQUIRE(game.tile_at(1, 4, 5) == RedGem);
        REQUIRE(game.hero.hp == hp);
        REQUIRE(game.hero.attack == attack);
        for (int x = 2; x <= 4; ++x)
            game.tile_at(1, x, 4) = Road;
        REQUIRE(collect_items(game, true).size() == 1);
        REQUIRE(game.tile_at(1, 3, 5) == potion);
        REQUIRE(game.tile_at(1, 4, 5) == Road);
        REQUIRE(game.hero.hp == hp);
        REQUIRE(game.hero.attack == attack + 1);
    }
}

TEST_CASE("Collection never opens doors fights reveals tunnels or changes floors", "[collect][movement]") {
    for (const int obstacle :
         {int(YellowDoor), int(BlueDoor), int(RedDoor), int(SealedGate), int(PrisonGate), int(Wall),
          int(SecretWall), int(HiddenObject), int(SpecialRoad), int(StairsUp), int(StairsDown),
          int(GreenSlime), int(Altar), int(Merchant), int(Thief), int(Lava)}) {
        auto game = corridor();
        game.hero.yellow_keys = game.hero.blue_keys = game.hero.red_keys = 5;
        game.tile_at(1, 3, 5) = static_cast<std::uint8_t>(obstacle);
        game.tile_at(1, 4, 5) = YellowKey;
        const auto before = saved(game);
        REQUIRE(collect_items(game, false).empty());
        REQUIRE(saved(game) == before);
        REQUIRE(game.commands.empty());
        REQUIRE(game.sounds.empty());
    }
}

TEST_CASE("Collection excludes hazardous starts paths and pickup cells", "[collect][hazards]") {
    for (int floor : {1, 47}) {
        auto game = corridor(floor);
        game.hero.equipment_found[SacredShieldFlag] = floor == 47;
        game.tile_at(floor, 4, 4) = MagicianA;
        game.tile_at(floor, 4, 3) = Road;
        game.tile_at(floor, 4, 5) = YellowKey;
        const auto before = saved(game);
        REQUIRE(collect_items(game, false).empty());
        REQUIRE(saved(game) == before);
    }
    auto game = corridor();
    game.hero.equipment_found[SacredShieldFlag] = 0;
    game.tile_at(1, 4, 4) = game.tile_at(1, 4, 6) = Sorcerer;
    game.tile_at(1, 5, 5) = YellowKey;
    REQUIRE(collect_items(game, false).empty());
    game.tile_at(1, 1, 4) = MagicianB;
    game.tile_at(1, 2, 5) = YellowKey;
    REQUIRE(collect_items(game, false).empty());
}

TEST_CASE("Collection is inert during events and never returns through a stair", "[collect][movement]") {
    auto game = corridor();
    game.tile_at(1, 2, 5) = YellowKey;
    game.push(Op::Wait);
    REQUIRE(collect_items(game, false).empty());
    REQUIRE(game.hero.yellow_keys == 0);
    game.finish_commands();
    game.tile_at(1, 1, 5) = StairsUp;
    REQUIRE(collect_items(game, false).empty());
    REQUIRE(game.hero.floor == 1);
    REQUIRE(game.hero.x == 1);
    game.tile_at(1, 1, 5) = Road;
    REQUIRE(collect_items(game, false).size() == 1);
}

TEST_CASE("Collection respects board edges and cannot wrap into a disconnected row", "[collect][movement]") {
    auto game = corridor();
    game.floors[1].tiles.fill(Wall);
    game.hero.x = 10;
    game.hero.y = 0;
    game.tile_at(1, 10, 0) = Road;
    game.tile_at(1, 0, 1) = YellowKey;
    REQUIRE(collect_items(game, false).empty());
    game.tile_at(1, 9, 0) = BlueKey;
    REQUIRE(collect_items(game, false).size() == 1);
    REQUIRE(game.hero.x == 10);
    REQUIRE(game.hero.y == 0);
    REQUIRE(game.hero.blue_keys == 1);
    REQUIRE(game.hero.yellow_keys == 0);
}

TEST_CASE("Collection expands to replayable native moves without a schema change", "[collect][replay]") {
    Game game;
    Recorder recorder(true);
    recorder.new_game(game.rankings);
    const int x = game.hero.x, y = game.hero.y;
    int flight = -1;
    const auto items = collect_items(game, false, [&](Direction direction) {
        const auto input = PlayerInput::move(direction);
        REQUIRE(apply_input(game, flight, input));
        recorder.append(input);
    });
    REQUIRE_FALSE(items.empty());
    REQUIRE(game.hero.x == x);
    REQUIRE(game.hero.y == y);
    ReplayPlayer player({recorder.history().begin(), recorder.history().end()});
    Game replayed;
    player.seek(replayed, flight, player.size());
    REQUIRE(game.hero == replayed.hero);
    REQUIRE(saved(game) == saved(replayed));
}
