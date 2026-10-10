#include "tsw/game.hpp"
#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <sstream>

using namespace tsw;

namespace {
Game combat_room(int floor = 1) {
    Game game;
    game.hero.floor = floor;
    game.hero.x = game.hero.y = 5;
    game.hero.hp = 1000;
    game.hero.attack = 100;
    game.hero.defense = 0;
    game.hero.gold = 123;
    game.hero.items.fill(0);
    game.floors[floor].tiles.fill(Road);
    for (int row = 0; row < int(game.monsters.size()); ++row)
        game.monsters[row] = {250, 30, 10, 8 + 2 * row};
    return game;
}
} // namespace

TEST_CASE("Every accepted monster tile reaches its forecast and battle row", "[combat][tiles]") {
    // One first tile per monster row; the octopus has eighteen pieces and the dragon one contact.
    constexpr std::array<int, 33> first_tiles{61,  63,  65,  67,  69,  71,  73,  75,  77,  79,  81,
                                              83,  85,  87,  89,  91,  93,  95,  97,  122, 133, 135,
                                              137, 139, 141, 143, 145, 147, 149, 151, 153, 155, 157};
    for (int row = 0; row < int(first_tiles.size()); ++row) {
        const int first = first_tiles[row];
        const int last = row == OctopusRow ? 114 : row == DragonRow ? 122 : first + 1;
        for (int tile = first; tile <= last; ++tile) {
            CAPTURE(row, tile);
            auto game = combat_room(row == ZenoRow ? 49 : 1);
            game.tile_at(game.hero.floor, 5, 4) = static_cast<std::uint8_t>(tile);
            for (const auto forecast : {game.forecast(tile), game.orb_forecast(tile)}) {
                REQUIRE(forecast.penetrates);
                REQUIRE(forecast.hero_hits == 3);
                REQUIRE(forecast.damage == 60);
            }
            REQUIRE(game.move(Direction::Up));
            REQUIRE(game.visual.battle);
            REQUIRE(game.visual.battle_enemy.row == row);
            REQUIRE(game.visual.battle_enemy.tile == tile);
            game.finish_commands();
            REQUIRE_FALSE(game.busy());
            REQUIRE(game.hero.x == 5);
            REQUIRE(game.hero.y == 4);
            REQUIRE(game.hero.hp == 940);
            const int reward = row == OctopusRow && tile != 104 ? (8 + 2 * row) / 2 : 8 + 2 * row;
            REQUIRE(game.hero.gold == 123 + reward);
            REQUIRE(game.tile_at(game.hero.floor, 5, 4) == Road);
            REQUIRE(game.visual.last_defeated);
            REQUIRE(game.visual.last_defeated->row == row);
        }
    }
}

TEST_CASE("Octopus pieces retain their exact reward and body clearing rules", "[combat][tiles]") {
    for (int tile = 97; tile <= 114; ++tile) {
        for (int lucky : {0, 1}) {
            CAPTURE(tile, lucky);
            auto game = combat_room();
            game.floors[1].tiles.fill(Wall);
            game.tile_at(1, 5, 4) = static_cast<std::uint8_t>(tile);
            game.inventory(Item::LuckyGold) = lucky;
            REQUIRE(game.forecast(tile).damage == 60);
            REQUIRE(game.orb_forecast(tile).damage == 60);
            REQUIRE(game.move(Direction::Up));
            REQUIRE(game.visual.battle_enemy.row == OctopusRow);
            int large_strikes = 0;
            Command executed;
            while (game.run_one(&executed))
                large_strikes += executed.op == Op::LargeMonsterStrike;
            REQUIRE_FALSE(game.busy());
            const bool mouth = tile == 104;
            REQUIRE(large_strikes == int(mouth));
            REQUIRE(game.hero.hp == 940);
            REQUIRE(game.hero.gold == 123 + (mouth ? 44 : 22) * (lucky + 1));
            for (int y = 0; y < BoardWidth; ++y)
                for (int x = 0; x < BoardWidth; ++x) {
                    const bool cleared = mouth ? x >= 4 && x <= 6 && y >= 2 && y <= 4 : x == 5 && y == 4;
                    REQUIRE(game.tile_at(1, x, y) == (cleared ? Road : Wall));
                }
        }
    }
}

TEST_CASE("Large monster cleanup remains within accepted edge placement saves", "[combat][save][tiles]") {
    // Each expected set uses flat cell indices, including the retained row wrapping at board sides.
    struct Placement {
        int target, hero;
        Direction direction;
        std::vector<int> cleared;
    };

    const std::array placements{Placement{0, 11, Direction::Up, {0, 1}},
                                Placement{10, 21, Direction::Up, {0, 9, 10, 11}},
                                Placement{15, 26, Direction::Up, {3, 4, 5, 14, 15, 16}},
                                Placement{110, 99, Direction::Down, {87, 88, 89, 98, 99, 100, 109, 110, 111}},
                                Placement{120, 109, Direction::Down, {97, 98, 99, 108, 109, 110, 119, 120}}};
    for (int tile : {OctopusMouth, DragonHead})
        for (const auto& placement : placements) {
            CAPTURE(tile, placement.target);
            auto saved = combat_room();
            saved.hero.x = placement.hero % BoardWidth;
            saved.hero.y = placement.hero / BoardWidth;
            saved.hero.attack = saved.hero.defense = 10000;
            saved.floors[1].tiles.fill(Wall);
            saved.tile(1, placement.target) = static_cast<std::uint8_t>(tile);
            std::stringstream bytes;
            saved.save(bytes);
            Game game;
            REQUIRE_NOTHROW(game.load(bytes));
            REQUIRE(game.tile(1, placement.target) == tile);
            REQUIRE(game.move(placement.direction));
            REQUIRE(game.visual.battle);
            REQUIRE_NOTHROW(game.finish_commands());
            REQUIRE_FALSE(game.busy());
            REQUIRE(cell(game.hero.x, game.hero.y) == placement.target);
            REQUIRE(game.hero.hp == 1000);
            REQUIRE(game.hero.gold == 123 + (tile == OctopusMouth ? 100 : 800));
            for (int index = 0; index < CellCount; ++index) {
                const bool cleared = std::find(placement.cleared.begin(), placement.cleared.end(), index) !=
                                     placement.cleared.end();
                REQUIRE(game.tile(1, index) == (cleared ? Road : Wall));
            }
        }
}

TEST_CASE("Dragon and altar decorations retain contact boundaries", "[movement][tiles]") {
    // These are drawn atlas variants, but Pascal's contact dispatch keeps them inert.
    for (int tile : {17,  18,  36,  115, 116, 117, 118, 119, 120, 121, 123, 124,
                     125, 126, 127, 128, 129, 130, 131, 132, 159, 160, 161}) {
        CAPTURE(tile);
        auto game = combat_room();
        game.tile_at(1, 5, 4) = static_cast<std::uint8_t>(tile);
        REQUIRE_FALSE(game.forecast(tile).penetrates);
        REQUIRE(game.move(Direction::Up));
        game.finish_commands();
        REQUIRE_FALSE(game.busy());
        REQUIRE_FALSE(game.visual.battle);
        REQUIRE(game.hero.y == 5);
        REQUIRE(game.hero.hp == 1000);
        REQUIRE(game.hero.gold == 123);
        REQUIRE(game.tile_at(1, 5, 4) == tile);
    }
}

TEST_CASE("Both Zeno frames retain their floor and cycle contact branches", "[combat][tiles][scenes]") {
    for (int tile : {91, 92}) {
        CAPTURE(tile);
        auto ignored = combat_room();
        ignored.tile_at(1, 5, 4) = static_cast<std::uint8_t>(tile);
        REQUIRE(ignored.move(Direction::Up));
        ignored.finish_commands();
        REQUIRE(ignored.hero.y == 5);
        REQUIRE(ignored.hero.gold == 123);
        REQUIRE_FALSE(ignored.visual.battle);

        auto ending = combat_room(50);
        ending.tile_at(50, 5, 4) = static_cast<std::uint8_t>(tile);
        REQUIRE(ending.move(Direction::Up));
        REQUIRE_FALSE(ending.visual.battle);
        REQUIRE_FALSE(ending.commands.empty());
        ending.finish_commands(true);
        REQUIRE(ending.hero.floor == 1);
        REQUIRE(ending.hero.cycle_factor_minus_one == 43);
        REQUIRE_FALSE(ending.busy());

        for (int later_cycle : {0, 1}) {
            CAPTURE(later_cycle);
            auto battle = combat_room(50);
            battle.hero.cycle_factor_minus_one = 43;
            battle.hero.later_cycle = later_cycle;
            battle.hero.attack = battle.hero.defense = 100000;
            battle.tile_at(50, 5, 4) = static_cast<std::uint8_t>(tile);
            REQUIRE(battle.move(Direction::Up));
            REQUIRE(battle.visual.battle);
            REQUIRE(battle.visual.battle_enemy.row == ZenoRow);
            REQUIRE(battle.visual.battle_enemy.stats.hp == (later_cycle ? 11000 : 44000));
            battle.finish_commands();
            // The defeated boss opens the ending speech before the queued cycle reset.
            REQUIRE(battle.dialogue);
            REQUIRE(battle.dialogue->continuation == 72);
            REQUIRE(battle.hero.y == 4);
            REQUIRE(battle.hero.hp == 1000);
            REQUIRE(battle.hero.gold == 161);
            REQUIRE(battle.tile_at(50, 5, 4) == Road);
            battle.finish_commands(true);
            REQUIRE(battle.hero.floor == 1);
            REQUIRE(battle.hero.cycle_factor_minus_one == 43);
            REQUIRE(battle.hero.later_cycle == 1);
            REQUIRE_FALSE(battle.busy());
        }
    }
}
