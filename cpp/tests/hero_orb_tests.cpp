#include "tsw/hero_orb.hpp"
#include <catch2/catch_test_macros.hpp>
#include <limits>

using namespace tsw;

TEST_CASE("Realtime Hero Orb information requires ownership and does not expose hidden events", "[orb]") {
    Game game;
    game.tile_at(1, 5, 4) = GreenSlime;
    REQUIRE_FALSE(orb_tile_info(game, 1, cell(5, 4), false));
    game.inventory(Item::HeroOrb) = 1;
    REQUIRE(orb_tile_info(game, 1, cell(5, 4), false).has_value());
    for (const auto hidden : {SpecialRoad, SecretWall, HiddenObject}) {
        game.tile_at(1, 5, 4) = hidden;
        REQUIRE_FALSE(orb_tile_info(game, 1, cell(5, 4), true));
    }
    REQUIRE_FALSE(orb_tile_info(game, -1, 0, false));
    REQUIRE_FALSE(orb_tile_info(game, FloorCount, 0, false));
    REQUIRE_FALSE(orb_tile_info(game, 1, -1, false));
    REQUIRE_FALSE(orb_tile_info(game, 1, CellCount, false));
}

TEST_CASE("Realtime Hero Orb follows the forecast preference and refreshes changed stats", "[orb]") {
    Game game;
    game.inventory(Item::HeroOrb) = game.inventory(Item::Cross) = 1;
    game.tile_at(1, 5, 4) = Zombie;
    game.monsters[ZombieRow] = {200, 180, 90, 5};
    auto info = orb_tile_info(game, 1, cell(5, 4), false);
    REQUIRE(info->forecast.penetrates);
    REQUIRE(info->forecast.damage == 1520);
    info = orb_tile_info(game, 1, cell(5, 4), true);
    REQUIRE(info->forecast.damage == 80);
    REQUIRE(info->hp == 200);
    REQUIRE(info->attack == 180);
    REQUIRE(info->defense == 90);
    REQUIRE(info->gold == 5);
    game.hero.defense = 180;
    REQUIRE(orb_tile_info(game, 1, cell(5, 4), true)->forecast.damage == 0);
    game.hero.attack = 90;
    REQUIRE_FALSE(orb_tile_info(game, 1, cell(5, 4), true)->forecast.penetrates);
    game.hero.attack = 200;
    game.monsters[ZombieRow].defense = 200;
    REQUIRE_FALSE(orb_tile_info(game, 1, cell(5, 4), true)->forecast.penetrates);
    game.tile_at(1, 5, 4) = Road;
    REQUIRE_FALSE(orb_tile_info(game, 1, cell(5, 4), true));
}

TEST_CASE("Realtime Hero Orb stats and gold follow cycle equipment and large monster rewards", "[orb]") {
    Game game;
    game.inventory(Item::HeroOrb) = 1;
    game.hero.cycle_factor_minus_one = 43;
    game.tile_at(1, 5, 4) = GreenSlime;
    const auto slime = game.monsters[0];
    const auto info = orb_tile_info(game, 1, cell(5, 4), false);
    REQUIRE(info->hp == slime.hp * 44);
    REQUIRE(info->attack == slime.attack * 44);
    REQUIRE(info->defense == slime.defense * 44);
    REQUIRE(info->gold == slime.gold);
    game.inventory(Item::LuckyGold) = 1;
    REQUIRE(orb_tile_info(game, 1, cell(5, 4), false)->gold == slime.gold * 2);
    for (int tile = OctopusFirst; tile <= OctopusLast; ++tile) {
        game.tile_at(1, 5, 4) = static_cast<std::uint8_t>(tile);
        REQUIRE(orb_tile_info(game, 1, cell(5, 4), true)->gold ==
                (tile == OctopusMouth ? game.monsters[OctopusRow].gold * 2 : game.monsters[OctopusRow].gold));
    }
    game.tile_at(1, 5, 4) = DragonHead;
    REQUIRE(orb_tile_info(game, 1, cell(5, 4), true)->row == DragonRow);
    game.tile_at(1, 5, 4) = DragonFirst;
    REQUIRE_FALSE(orb_tile_info(game, 1, cell(5, 4), true));
    game.tile_at(1, 5, 4) = GreenSlime + 1;
    REQUIRE(orb_tile_info(game, 1, cell(5, 4), true)->row == 0);
}

TEST_CASE("Realtime Hero Orb abbreviations keep large numbers compact", "[orb]") {
    REQUIRE(compact_orb_number(0) == "0");
    REQUIRE(compact_orb_number(999) == "999");
    REQUIRE(compact_orb_number(1000) == "1k");
    REQUIRE(compact_orb_number(1250) == "1.2k");
    REQUIRE(compact_orb_number(10000) == "10k");
    REQUIRE(compact_orb_number(1000000) == "1M");
    REQUIRE(compact_orb_number(2500000000LL) == "2.5B");
    REQUIRE(compact_orb_number(1000000000000LL) == "1T");
    REQUIRE(compact_orb_number(std::numeric_limits<std::int64_t>::max()) == "9e18");
}
