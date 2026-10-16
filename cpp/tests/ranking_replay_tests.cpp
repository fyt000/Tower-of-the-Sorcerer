#include "tsw/replay.hpp"
#include <catch2/catch_test_macros.hpp>
#include <chrono>
#include <fstream>
#include <glaze/json.hpp>
#include <sstream>
#include <stdexcept>

using namespace tsw;

static_assert(sizeof(PlayerInput) < sizeof(RankingTable));

namespace {
PlayerInput ranking_input(const RankingTables& tables) {
    PlayerInput input{InputKind::Rankings};
    input.rankings = std::make_shared<const RankingTables>(tables);
    return input;
}

RankingTables winners() {
    auto tables = default_rankings();
    for (auto& entry : tables[0])
        entry.score = 500;
    tables[0][0].name = "Previous winner";
    return tables;
}

void fairy_room(Game& game) {
    game.hero.floor = game.hero.highest_floor = 10;
    game.hero.x = game.hero.y = 5;
    game.hero.music_track = MusicTrack::Disabled;
    game.floors[10].tiles.fill(Road);
    game.tile_at(10, 5, 4) = Fairy;
}

struct RankingReplayFiles {
    std::filesystem::path directory =
        std::filesystem::path(TSW_TEST_TEMP) /
        ("ranking-replay-" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));

    RankingReplayFiles() { std::filesystem::create_directories(directory); }

    ~RankingReplayFiles() {
        std::error_code ignored;
        std::filesystem::remove_all(directory, ignored);
    }
};

std::string read_file(const std::filesystem::path& path) {
    std::ifstream input(path, std::ios::binary);
    REQUIRE(input.is_open());
    return {std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>()};
}

std::string ranking_json(const glz::generic& value) {
    std::string json;
    REQUIRE_FALSE(glz::write<glz::opts{.skip_null_members = false}>(value, json));
    return json;
}
} // namespace

TEST_CASE("Ranking replay records roundtrip complete tables and reject bad shapes", "[rankings][replay]") {
    const auto input = ranking_input(winners());
    const auto json = input_json(input);
    REQUIRE(parse_input(json) == input);
    const std::array inputs{PlayerInput{InputKind::NewGame}, input};
    std::ostringstream output;
    write_replay(output, inputs);
    std::istringstream source(output.str());
    REQUIRE(read_replay(source) == std::vector<PlayerInput>(inputs.begin(), inputs.end()));
    glz::generic valid;
    REQUIRE_FALSE(glz::read_json(valid, json));
    for (std::size_t count : {std::size_t(0), std::size_t(4), std::size_t(6)}) {
        auto invalid = valid;
        invalid["tables"].get_array().resize(count);
        REQUIRE_THROWS(parse_input(ranking_json(invalid)));
    }
    for (std::size_t count : {std::size_t(0), std::size_t(9), std::size_t(11)}) {
        auto invalid = valid;
        invalid["tables"][0].get_array().resize(count);
        REQUIRE_THROWS(parse_input(ranking_json(invalid)));
    }
    auto invalid = valid;
    invalid["tables"][0][0].get_object().erase("hp");
    REQUIRE_THROWS(parse_input(ranking_json(invalid)));
    invalid = valid;
    invalid["tables"][0][0]["extra"] = true;
    REQUIRE_THROWS(parse_input(ranking_json(invalid)));
    invalid = valid;
    invalid["tables"][0][0]["hp"] = "not a number";
    REQUIRE_THROWS(parse_input(ranking_json(invalid)));
    invalid = valid;
    invalid["tables"][0][0]["hp"] = 2147483648.0;
    REQUIRE_THROWS(parse_input(ranking_json(invalid)));
    REQUIRE_THROWS(parse_input(R"({"type":"rankings"})"));
    REQUIRE_THROWS(parse_input(R"({"type":"rankings","tables":null})"));
    REQUIRE_THROWS(input_json({InputKind::Rankings}));
}

TEST_CASE("Ranking replay input only changes in-memory ranking tables", "[rankings][replay]") {
    Game game;
    int flight = 1;
    game.push(Op::Wait);
    const auto hero = game.hero;
    const auto floors = game.floors;
    const auto monsters = game.monsters;
    const auto commands = game.commands;
    REQUIRE(apply_input(game, flight, ranking_input(winners())));
    REQUIRE(game.rankings == winners());
    REQUIRE(game.hero == hero);
    REQUIRE(game.floors == floors);
    REQUIRE(game.monsters == monsters);
    REQUIRE(game.commands == commands);
    REQUIRE(flight == 1);
    REQUIRE_THROWS(apply_input(game, flight, {InputKind::Rankings}));
    REQUIRE(game.rankings == winners());
}

TEST_CASE("Ranking snapshots restore Fairy outcomes after replay steps and seeks", "[rankings][replay]") {
    const std::vector<PlayerInput> inputs{{InputKind::NewGame},
                                          ranking_input(winners()),
                                          PlayerInput::move(Direction::Up),
                                          ranking_input(default_rankings()),
                                          PlayerInput::move(Direction::Up)};
    for (bool seek : {false, true}) {
        CAPTURE(seek);
        ReplayPlayer player(inputs);
        Game game;
        int flight = -1;
        if (seek)
            player.seek(game, flight, 2);
        else {
            REQUIRE(player.next(game, flight));
            REQUIRE(player.next(game, flight));
        }
        REQUIRE(game.rankings == winners());
        // The board fixture begins at the Fairy contact; the replay owns its table environment.
        fairy_room(game);
        REQUIRE(player.next(game, flight));
        REQUIRE(game.hero.fairy_score == 415);
        REQUIRE(game.hero.fairy_rank == 0);
        settle_action(game);
        REQUIRE(player.next(game, flight));
        REQUIRE(game.rankings == default_rankings());
        fairy_room(game);
        REQUIRE(player.next(game, flight));
        REQUIRE(game.hero.fairy_rank == 1);
        settle_action(game);
        player.seek(game, flight, 2);
        REQUIRE(game.rankings == winners());
        player.seek(game, flight, 4);
        REQUIRE(game.rankings == default_rankings());
    }
}

TEST_CASE("Ranking recording updates are sparse and retain legacy defaults", "[rankings][replay]") {
    Recorder recorder(true);
    recorder.new_game();
    REQUIRE(recorder.history().size() == 1);
    recorder.rankings(default_rankings());
    REQUIRE(recorder.history().size() == 1);
    recorder.rankings(winners());
    REQUIRE(recorder.history().size() == 2);
    recorder.rankings(winners());
    REQUIRE(recorder.history().size() == 2);
    recorder.append(PlayerInput::move(Direction::Up));
    recorder.rankings(winners());
    REQUIRE(recorder.history().size() == 3);
    recorder.rankings(default_rankings());
    REQUIRE(recorder.history().size() == 4);
    REQUIRE(recorder.history().back() == ranking_input(default_rankings()));
    const auto history = std::vector<PlayerInput>(recorder.history().begin(), recorder.history().end());
    recorder.resume(history);
    recorder.rankings(default_rankings());
    REQUIRE(recorder.history().size() == 4);
    recorder.new_game(winners());
    REQUIRE(recorder.history().size() == 2);
    REQUIRE(recorder.history()[0].kind == InputKind::NewGame);
    REQUIRE(recorder.history()[1] == ranking_input(winners()));
    recorder.stop();
    recorder.rankings(winners());
    REQUIRE_FALSE(recorder.active());
    Recorder disabled;
    disabled.new_game(winners());
    disabled.rankings(winners());
    REQUIRE_FALSE(disabled.active());
}

TEST_CASE("Recorded ranking environments reproduce exact save bytes", "[rankings][replay][saves]") {
    RankingReplayFiles files;
    for (const auto kind : {SaveKind::Slot, SaveKind::Checkpoint}) {
        CAPTURE(kind == SaveKind::Slot);
        Game game;
        game.rankings = winners();
        Recorder recorder(true);
        recorder.new_game(game.rankings);
        int flight = -1;
        const PlayerInput move = PlayerInput::move(Direction::Up);
        execute_input(game, flight, move);
        recorder.append(move);
        auto current = default_rankings();
        current[2][0] = {800, 2345, 456, 567, "Later winner"};
        game.rankings = current;
        const auto path = files.directory / (kind == SaveKind::Slot ? "save1.dat" : "save0.dat");
        recorder.save(game, path, kind);
        REQUIRE(recorder.history().size() == 5);
        REQUIRE(recorder.history()[3] == ranking_input(current));
        std::istringstream history(read_file(recording_path(path)));
        ReplayPlayer player(read_replay(history));
        Game replayed;
        int replayed_flight = -1;
        player.seek(replayed, replayed_flight, player.size());
        REQUIRE(replayed.rankings == current);
        std::ostringstream saved(std::ios::out | std::ios::binary);
        replayed.save(saved, kind);
        REQUIRE(saved.str() == read_file(path));
        REQUIRE(saved.str().size() == 6957);
        recorder.load(game, path, kind);
        REQUIRE(recorder.active());
        const auto count = recorder.history().size();
        recorder.rankings(current);
        REQUIRE(recorder.history().size() == count);
    }
}

TEST_CASE("A failed save does not commit a prospective ranking update", "[rankings][replay][saves]") {
    RankingReplayFiles files;
    Game game;
    Recorder recorder(true);
    recorder.new_game();
    const auto path = files.directory / "save1.dat";
    recorder.save(game, path);
    const auto bytes = read_file(path);
    const auto companion = read_file(recording_path(path));
    const auto achievements = read_file(achievement_path(path));
    const auto history = std::vector<PlayerInput>(recorder.history().begin(), recorder.history().end());
    game.rankings = winners();
    game.push(Op::Wait);
    REQUIRE_THROWS(recorder.save(game, path));
    REQUIRE(read_file(path) == bytes);
    REQUIRE(read_file(recording_path(path)) == companion);
    REQUIRE(read_file(achievement_path(path)) == achievements);
    REQUIRE(std::vector<PlayerInput>(recorder.history().begin(), recorder.history().end()) == history);
    for (const auto& entry : std::filesystem::directory_iterator(files.directory))
        REQUIRE((entry.path() == path || entry.path() == recording_path(path) ||
                 entry.path() == achievement_path(path)));
    game.finish_commands();
    recorder.save(game, path);
    REQUIRE(recorder.history()[2] == ranking_input(winners()));
}
