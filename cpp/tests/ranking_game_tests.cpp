#include "tsw/game.hpp"
#include "tsw/game_state.hpp"
#include <catch2/catch_test_macros.hpp>
#include <format>
#include <sstream>

using namespace tsw;

namespace {
Game fairy_room(int floor = 10) {
    Game game;
    game.hero.floor = game.hero.highest_floor = floor;
    game.hero.x = game.hero.y = 5;
    game.hero.music_track = MusicTrack::Disabled;
    game.floors[floor].tiles.fill(Road);
    game.tile_at(floor, 5, 4) = Fairy;
    return game;
}
} // namespace

TEST_CASE("All five Fairy checkpoints display their computed score and ranking", "[rankings][npcs]") {
    constexpr std::array floors{10, 20, 25, 40, 49};
    constexpr std::array scores{415, 134, 0, 0, 0};
    constexpr std::array speeches{16, 22, 24, 40, 47};
    constexpr std::array targets{27, 49, 71, 60, 16};
    for (int category = 0; category < 5; ++category) {
        CAPTURE(category);
        auto game = fairy_room(floors[category]);
        game.tile(game.hero.floor, targets[category]) = Fairy;
        REQUIRE(game.move(Direction::Up));
        game.finish_commands();
        REQUIRE(game.dialogue);
        REQUIRE_FALSE(game.dialogue->text.empty());
        REQUIRE(game.dialogue->continuation == static_cast<ContinuationStage>(speeches[category] + 10));
        REQUIRE(game.hero.fairy_score == scores[category]);
        REQUIRE(game.hero.fairy_category == static_cast<FairyCategory>(category + 1));
        REQUIRE(game.hero.fairy_visits == 1);
        REQUIRE(game.checkpoint_requested);
        REQUIRE(game.dialogue->text.find(std::format(" {} points.", scores[category])) != std::string::npos);
        REQUIRE(game.hero.fairy_rank == (category < 2 ? 1 : 0));
        REQUIRE(
            game.dialogue->text.starts_with(category < 2 ? "Congratulations! You win the 1 " : "Judging by"));
        if (category == 0)
            REQUIRE(game.dialogue->text.ends_with(
                "FIGHTER GOD. You may as well play as good as you have from this point on."));
        if (category == 1)
            REQUIRE(game.dialogue->text.find("BRAVE MAN.") != std::string::npos);
        REQUIRE(game.continue_dialogue());
        game.finish_commands();
        REQUIRE_FALSE(game.busy());
        REQUIRE(game.hero.dialogue_seen[speeches[category] + 10] == 1);
        REQUIRE(game.tile(game.hero.floor, targets[category]) == Road);
    }
}

TEST_CASE("Fairy evaluations retain every recovered score band and visit closing", "[rankings][npcs]") {
    struct Evaluation {
        int low, high;
        std::string_view text;
    };

    constexpr std::array evaluations{
        Evaluation{0, 49, "If you have that many points, you might want to reconsider going higher... =)"},
        Evaluation{50, 59, "A bit below average. Maybe you should try harder."},
        Evaluation{60, 79, "You are ordinary. You might get by okay!"},
        Evaluation{80, 99, "Doing fine! If you wish to continue, I will give you a special rank..."},
        Evaluation{100, 120, "Congratulations! Your score is GREAT! I give you the special rank of FIGHTER."},
        Evaluation{121, 140,
                   "Congratulations! Your score is GREAT! I give you the special rank of BRAVE MAN."},
        Evaluation{141, 160, "Do you wish to go on? I give you the special rank of HERO."},
        Evaluation{161, 200, "Do you wish to go on? I give you the special rank of SWORD EMPEROR."},
        Evaluation{201, 9999, "Do you wish to go on? I give you the special rank of FIGHTER GOD."},
        Evaluation{10000, 10001, ""}};
    for (const auto& evaluation : evaluations)
        for (int score : {evaluation.low, evaluation.high})
            for (int visits : {0, 2, 3}) {
                CAPTURE(score, visits);
                auto game = fairy_room();
                game.hero.hp = 400;
                game.hero.attack = 9;
                game.hero.defense = 35;
                game.hero.yellow_keys = score;
                game.hero.fairy_visits = visits;
                for (auto& entry : game.rankings[0])
                    entry.score = 100000;
                REQUIRE(game.move(Direction::Up));
                game.finish_commands();
                REQUIRE(game.dialogue);
                REQUIRE(game.hero.fairy_score == score);
                REQUIRE(game.hero.fairy_rank == 0);
                auto expected =
                    std::format("Judging by your vital power, offensive power, defensive power, and "
                                "number of keys, you have {} points.",
                                score);
                if (!evaluation.text.empty())
                    expected += std::format(" {}", evaluation.text);
                if (score >= 100 && score <= 9999)
                    expected += visits < 3 ? " You may as well play as good as you have from this point on."
                                           : " It was nice fight so far.";
                REQUIRE(game.dialogue->text == expected);
            }
}

TEST_CASE("Fairy speech survives migration before and during its queued dialogue",
          "[rankings][runtime][npcs]") {
    auto game = fairy_room();
    for (int row = 0; row < 9; ++row)
        game.rankings[0][row].score = 500;
    game.rankings[0][9].score = 0;
    REQUIRE(game.move(Direction::Up));
    REQUIRE(game.hero.fairy_rank == 10);
    auto pending = GameState::capture(game).restore();
    pending.finish_commands();
    REQUIRE(pending.dialogue);
    REQUIRE(pending.dialogue->text.starts_with("Congratulations! You win the 10 "));
    auto speaking = GameState::capture(pending).restore();
    REQUIRE(speaking.dialogue == pending.dialogue);
    game.finish_commands();
    REQUIRE(game.dialogue == speaking.dialogue);
    speaking.finish_commands(true);
    REQUIRE_FALSE(speaking.busy());
    REQUIRE(speaking.tile(10, 27) == Road);
}

TEST_CASE("Fairy encounters use the game's ranking tables", "[rankings][npcs]") {
    Game game;
    game.hero.floor = 10;
    game.hero.highest_floor = 10;
    game.hero.x = game.hero.y = 5;
    game.hero.music_track = MusicTrack::Disabled;
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
