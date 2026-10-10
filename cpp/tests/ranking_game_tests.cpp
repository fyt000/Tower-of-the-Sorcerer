#include "tsw/game.hpp"
#include "tsw/game_state.hpp"
#include <catch2/catch_test_macros.hpp>
#include <sstream>

using namespace tsw;

TEST_CASE("Fairy encounters use the game's ranking tables", "[rankings][npcs]") {
    Game game;
    game.hero.floor = 10;
    game.hero.highest_floor = 10;
    game.hero.x = game.hero.y = 5;
    game.hero.music_track = 0;
    game.floors[10].tiles.fill(Road);
    game.tile_at(10, 5, 4) = Fairy;
    for (auto& entry : game.rankings[0])
        entry.score = 500;
    REQUIRE(game.move(Direction::Up));
    REQUIRE(game.hero.fairy_score == 415);
    REQUIRE(game.hero.fairy_rank == 0);
    game.finish_commands(true);
    const auto tables = game.rankings;
    game.next_cycle();
    REQUIRE(game.rankings == tables);
    game.new_game();
    REQUIRE(game.rankings == tables);
}

TEST_CASE("Game slot loads preserve directory rankings", "[rankings][saves]") {
    Game saved;
    saved.hero.gold = 321;
    std::stringstream stream(std::ios::in | std::ios::out | std::ios::binary);
    saved.save(stream);
    Game restored;
    restored.rankings[2][0] = {999, 1234, 567, 890, "Previous run"};
    const auto tables = restored.rankings;
    restored.load(stream);
    REQUIRE(restored.hero.gold == 321);
    REQUIRE(restored.rankings == tables);
}

TEST_CASE("Runtime migration retains ranking-dependent Fairy outcomes", "[rankings][runtime]") {
    Game game;
    game.hero.floor = game.hero.highest_floor = 10;
    game.hero.x = game.hero.y = 5;
    game.floors[10].tiles.fill(Road);
    game.tile_at(10, 5, 4) = Fairy;
    for (auto& entry : game.rankings[0])
        entry.score = 500;
    Game restored = GameState::capture(game).restore();
    REQUIRE(restored.rankings == game.rankings);
    REQUIRE(restored.move(Direction::Up));
    REQUIRE(restored.hero.fairy_rank == 0);
}
