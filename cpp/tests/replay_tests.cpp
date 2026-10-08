#include "tsw/replay.hpp"
#include "tsw/settings.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <chrono>
#include <fstream>
#include <glaze/json.hpp>
#include <map>
#include <sstream>

using namespace tsw;

namespace replay_test {
struct HeroView {
    int hp, floor, x;
};

struct DialogueView {
    std::string text;
    bool shop;
    std::array<std::string, 3> choices;
};

struct Observation {
    HeroView hero;
    std::map<std::string, int> inventory;
    int map_floor;
    std::vector<int> map;
    int flight;
    std::optional<DialogueView> dialogue;
    bool dead;
    std::string status;
};
} // namespace replay_test

namespace {
struct ReplayDirectory {
    std::filesystem::path path =
        std::filesystem::path(TSW_TEST_TEMP) /
        ("replay-" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));

    ReplayDirectory() { std::filesystem::create_directories(path); }

    ~ReplayDirectory() {
        std::error_code ignored;
        std::filesystem::remove_all(path, ignored);
    }
};

std::string contents(const std::filesystem::path& path) {
    std::ifstream input(path, std::ios::binary);
    REQUIRE(input.is_open());
    return {std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>()};
}

Game playback(const std::filesystem::path& path) {
    std::ifstream input(path, std::ios::binary);
    REQUIRE(input.is_open());
    Game game;
    int flight = -1;
    for (const auto& action : read_replay(input)) {
        apply_input(game, flight, action);
        settle_action(game);
    }
    return game;
}

void walk(Game& game, Recorder& recorder, Direction direction) {
    game.move(direction);
    recorder.append({InputKind::Move, direction});
    game.finish_commands(true);
}

void matches_save(const std::filesystem::path& save, SaveKind kind = SaveKind::Slot) {
    auto game = playback(recording_path(save));
    std::ostringstream record(std::ios::out | std::ios::binary);
    game.save(record, kind);
    REQUIRE(record.str() == contents(save));
    REQUIRE(record.str().size() == 6957);
}
} // namespace

TEST_CASE("Replay parser accepts player commands and rejects malformed inputs", "[replay]") {
    for (const auto* source :
         {R"({"type":"new_game"})", R"({"type":"move","direction":"up"})",
          R"({"type":"use_item","item":"bomb"})", R"({"type":"use_item","item":"flying_orb","floor":35})",
          R"({"type":"choose","choice":"leave"})", R"({"type":"choose","choice":"attack"})",
          R"({"type":"flight_open"})", R"({"type":"flight_up"})", R"({"type":"flight_down"})",
          R"({"type":"flight_confirm"})", R"({"type":"cancel"})", R"({"type":"save","kind":"slot"})",
          R"({"type":"reload","kind":"checkpoint"})", R"({"direction":"left","type":"move"})",
          R"({"floor":35,"item":"orb_of_flying","type":"use_item"})", R"({"kind":"slot","type":"reload"})",
          R"({"choice":"accept","type":"choose"})", R"({"type":"move","direction":"\u0075p"})"}) {
        INFO(source);
        const auto action = parse_input(source);
        REQUIRE(parse_input(input_json(action)) == action);
    }
    for (const auto* source : {"not json",
                               "[]",
                               "null",
                               "{}",
                               R"({"type":null})",
                               R"({"type":1})",
                               R"({"type":"walk"})",
                               R"({"type":"move","direction":"north"})",
                               R"({"type":"new_game","extra":1})",
                               R"({"type":"move"})",
                               R"({"type":"use_item","item":"missing"})",
                               R"({"type":"move","direction":null})",
                               R"({"type":"move","direction":1})",
                               R"({"type":"move","direction":"up","extra":1})",
                               R"({"type":"use_item"})",
                               R"({"type":"use_item","item":"flying_orb"})",
                               R"({"type":"use_item","item":"bomb","floor":1})",
                               R"({"type":"use_item","item":"bomb","floor":null})",
                               R"({"type":"use_item","item":"flying_orb","floor":null})",
                               R"({"type":"use_item","item":"flying_orb","floor":"35"})",
                               R"({"type":"use_item","item":"flying_orb","floor":true})",
                               R"({"type":"use_item","item":"flying_orb","floor":1.5})",
                               R"({"type":"use_item","item":"flying_orb","floor":1.0})",
                               R"({"type":"use_item","item":"flying_orb","floor":4294967296})",
                               R"({"type":"use_item","item":"flying_orb","floor":-2147483649})",
                               R"({"type":"use_item","item":"flying_orb","floor":35,"extra":1})",
                               R"({"type":"choose","choice":"3"})",
                               R"({"type":"choose","choice":""})",
                               R"({"type":"choose","choice":0})",
                               R"({"type":"choose"})",
                               R"({"type":"save","kind":"unknown"})",
                               R"({"type":"save"})",
                               R"({"type":"new_game"} trailing)",
                               R"({"type":"new_game"}{"type":"cancel"})"}) {
        INFO(source);
        REQUIRE_THROWS(parse_input(source));
    }
    const std::string padded = R"({"direction":"right","type":"move"}not part of the input)";
    REQUIRE(parse_input(std::string_view(padded).substr(0, padded.find('}') + 1)).direction ==
            Direction::Right);
    std::istringstream malformed("\n{\"type\":\"new_game\"}\nnot json\n");
    REQUIRE_THROWS_WITH(read_replay(malformed), Catch::Matchers::StartsWith("Line 3:"));
}

TEST_CASE("Replay actions run real movement and preserve refused door contact", "[replay]") {
    Game game;
    game.hero.x = game.hero.y = 5;
    game.floors[1].tiles.fill(Road);
    game.tile_at(1, 5, 4) = YellowDoor;
    int flight = -1;
    REQUIRE(apply_input(game, flight, parse_input(R"({"type":"move","direction":"up"})")));
    settle_action(game);
    REQUIRE(game.hero.y == 5);
    REQUIRE(game.hero.yellow_keys == 0);
    REQUIRE(game.tile_at(1, 5, 4) == YellowDoor);
    game.hero.yellow_keys = 1;
    apply_input(game, flight, parse_input(R"({"type":"move","direction":"up"})"));
    settle_action(game);
    REQUIRE(game.hero.y == 5);
    REQUIRE(game.hero.yellow_keys == 0);
    REQUIRE(game.tile_at(1, 5, 4) == Road);
    apply_input(game, flight, parse_input(R"({"type":"move","direction":"up"})"));
    settle_action(game);
    REQUIRE(game.hero.y == 4);
}

TEST_CASE("Headless settling continues speech but leaves actual shop decisions", "[replay]") {
    Game game;
    int flight = -1;
    game.inventory(Item::WisdomOrb) = 1;
    apply_input(game, flight, parse_input(R"({"type":"use_item","item":"wisdom_orb"})"));
    REQUIRE(game.dialogue);
    settle_action(game);
    REQUIRE_FALSE(game.dialogue);
    game.hero.x = game.hero.y = 5;
    game.hero.gold = 100;
    game.floors[1].tiles.fill(Road);
    game.tile_at(1, 5, 4) = Altar;
    apply_input(game, flight, parse_input(R"({"type":"move","direction":"up"})"));
    settle_action(game);
    REQUIRE(game.dialogue);
    REQUIRE(game.dialogue->shop);
    apply_input(game, flight, parse_input(R"({"type":"choose","choice":"attack"})"));
    settle_action(game);
    REQUIRE(game.hero.attack == 102);
    REQUIRE(game.hero.gold == 80);
    REQUIRE_FALSE(game.dialogue);
}

TEST_CASE("Flight playback retains preview writes reversals cancellation and landing direction", "[replay]") {
    Game game;
    int flight = -1;
    game.hero.floor = 34;
    game.hero.highest_floor = 45;
    game.inventory(Item::FlightOrb) = 1;
    game.tile(35, 91) = Road;
    game.tile(2, 120) = Thief;
    apply_input(game, flight, {InputKind::OpenFlight});
    REQUIRE(flight == 34);
    apply_input(game, flight, {InputKind::FlightUp});
    REQUIRE(flight == 35);
    REQUIRE(game.tile(2, 120) == Road);
    REQUIRE(game.hero.floor == 34);
    game.inventory(Item::HeroOrb) = 1;
    REQUIRE(apply_input(game, flight, {InputKind::UseItem, Direction::Up, Item::HeroOrb}));
    REQUIRE(flight == 35);
    apply_input(game, flight, {InputKind::FlightDown});
    REQUIRE(game.hero.flight_direction == 2);
    apply_input(game, flight, {InputKind::Cancel});
    REQUIRE(flight == -1);
    REQUIRE(game.hero.flight_direction == 2);
    apply_input(game, flight, {InputKind::OpenFlight});
    REQUIRE(game.hero.flight_direction == 0);
    for (int i = 0; i < 10; ++i)
        apply_input(game, flight, {InputKind::FlightUp});
    REQUIRE(flight == 45);
    apply_input(game, flight, {InputKind::Travel});
    settle_action(game);
    REQUIRE(game.hero.floor == 45);
    REQUIRE(flight == -1);
    REQUIRE_THROWS(apply_input(game, flight, {InputKind::FlightDown}));
}

TEST_CASE("Replay reload runs original shared Zeno reconstruction", "[replay][saves]") {
    for (const auto kind : {SaveKind::Slot, SaveKind::Checkpoint}) {
        Game game;
        game.hero.zeno_sealed = true;
        game.hero.cycle_factor_minus_one = 43;
        game.monsters[ZenoRow] = {800, 500, 100, 1000};
        int flight = 35;
        apply_input(game, flight, {InputKind::Reload, Direction::Up, Item::HeroOrb, -1, kind});
        REQUIRE(game.monsters[ZenoRow].hp == 800 * 44);
        REQUIRE(game.monsters[ZenoRow].attack == 500 * 44);
        REQUIRE(game.monsters[ZenoRow].defense == 100 * 44);
        REQUIRE(flight == -1);
    }
}

TEST_CASE("Replay settling terminates after fatal combat", "[replay]") {
    Game game;
    game.hero.x = game.hero.y = 5;
    game.hero.hp = 1;
    game.hero.attack = 10;
    game.hero.defense = 0;
    game.floors[1].tiles.fill(Road);
    game.tile_at(1, 5, 4) = GreenSlime;
    int flight = -1;
    apply_input(game, flight, {InputKind::Move, Direction::Up});
    settle_action(game);
    REQUIRE(game.visual.dead);
    REQUIRE(game.busy());
    REQUIRE_FALSE(apply_input(game, flight, {InputKind::Move, Direction::Left}));
    settle_action(game);
}

TEST_CASE("CLI observations use named values and can inspect a remote floor", "[replay]") {
    constexpr auto options =
        glz::opts{.error_on_unknown_keys = false, .skip_null_members = false, .error_on_missing_keys = true};
    Game game;
    replay_test::Observation view{};
    REQUIRE_FALSE(glz::read<options>(view, gameplay_json(game, -1, 35)));
    REQUIRE(view.hero.hp == 1000);
    REQUIRE(view.hero.floor == 1);
    REQUIRE(view.hero.x == 5);
    REQUIRE(view.inventory.at("bomb") == 0);
    REQUIRE(view.inventory.size() == game.hero.items.size());
    REQUIRE(view.map_floor == 35);
    REQUIRE(view.map.size() == CellCount);
    REQUIRE(view.map[91] == game.tile(35, 91));
    REQUIRE(view.flight == -1);
    REQUIRE_FALSE(view.dialogue);
    REQUIRE_FALSE(view.dead);
    game.dialogue = Dialogue{"First line\n\"Quoted\" text", 0, true, {"HP", "Attack", "Leave"}};
    game.status = "A\tmessage";
    REQUIRE_FALSE(glz::read<options>(view, gameplay_json(game, 35)));
    REQUIRE(view.dialogue);
    REQUIRE(view.dialogue->text == game.dialogue->text);
    REQUIRE(view.dialogue->shop);
    REQUIRE(view.dialogue->choices == game.dialogue->choices);
    REQUIRE(view.flight == 35);
    REQUIRE(view.status == game.status);
    REQUIRE_THROWS(gameplay_json(game, -1, FloorCount));
}

TEST_CASE("Visual replay seeks real command boundaries without save snapshots", "[replay]") {
    std::istringstream source(R"({"type":"new_game"}
{"type":"move","direction":"up"}
{"type":"move","direction":"up"}
{"type":"move","direction":"left"}
{"type":"move","direction":"right"}
{"type":"move","direction":"up"}
{"type":"move","direction":"up"}
{"type":"save","kind":"slot"}
{"type":"reload","kind":"slot"}
)");
    ReplayPlayer player(read_replay(source));
    Game game;
    int flight = -1;
    REQUIRE(player.position() == 0);
    player.seek(game, flight, 4);
    REQUIRE(player.position() == 4);
    REQUIRE(game.hero.x == 4);
    REQUIRE(game.hero.y == 9);
    REQUIRE(game.hero.yellow_keys == 1);
    REQUIRE(game.tile(1, 93) == YellowDoor);
    player.seek(game, flight, 5);
    REQUIRE(player.next(game, flight));
    REQUIRE(player.position() == 6);
    REQUIRE(game.busy()); // Animation is left to the desktop scheduler.
    settle_action(game);
    REQUIRE(game.hero.y == 9);
    REQUIRE(game.hero.yellow_keys == 0);
    REQUIRE(game.tile(1, 93) == Road);
    player.seek(game, flight, 5);
    REQUIRE(game.tile(1, 93) == YellowDoor);
    REQUIRE(game.hero.yellow_keys == 1);
    player.seek(game, flight, player.size());
    REQUIRE(player.finished());
    REQUIRE_FALSE(player.next(game, flight));
    REQUIRE(game.hero.y == 8);
    const auto before = gameplay_json(game);
    REQUIRE_THROWS(player.seek(game, flight, player.size() + 1));
    REQUIRE(gameplay_json(game) == before);
    player.seek(game, flight, 0);
    REQUIRE(game.hero.y == 10);
    REQUIRE(player.history().empty());
}

TEST_CASE("Failed replay reconstruction leaves the current game and position intact", "[replay]") {
    REQUIRE_THROWS(ReplayPlayer({}));
    REQUIRE_THROWS(ReplayPlayer({{InputKind::Move}}));
    ReplayPlayer player({{InputKind::NewGame}, {InputKind::FlightUp}});
    Game game;
    game.hero.hp = 2345;
    int flight = 35;
    REQUIRE_THROWS(player.seek(game, flight, 2));
    REQUIRE(game.hero.hp == 2345);
    REQUIRE(flight == 35);
    REQUIRE(player.position() == 0);
}

TEST_CASE("Replay takeover retains the played prefix only when recording is enabled", "[replay][saves]") {
    ReplayDirectory directory;
    ReplayPlayer player({{InputKind::NewGame},
                         {InputKind::Move, Direction::Up},
                         {InputKind::Move, Direction::Left},
                         {InputKind::Move, Direction::Right}});
    Game game;
    int flight = -1;
    player.seek(game, flight, 3);
    Recorder recorder(true);
    recorder.resume(player.history());
    REQUIRE(recorder.active());
    walk(game, recorder, Direction::Down);
    const auto save = directory.path / "takeover.dat";
    recorder.save(game, save);
    matches_save(save);
    std::ifstream recorded(recording_path(save));
    const auto history = read_replay(recorded);
    REQUIRE(history.size() == 5);
    REQUIRE(history[3].direction == Direction::Down);
    recorder.stop();
    REQUIRE(recorder.enabled());
    REQUIRE_FALSE(recorder.active());
    recorder.enable(false);
    recorder.resume(player.history());
    REQUIRE_FALSE(recorder.active());
}

TEST_CASE("Desktop settings persist opt in audio and both speeds with bounds checks", "[settings]") {
    ReplayDirectory directory;
    const auto path = directory.path / "settings.json";
    REQUIRE_FALSE(load_settings(path).recording);
    REQUIRE(load_settings(path).replay_speed == 2);
    save_settings(path, {2, 6, true, true});
    const auto settings = load_settings(path);
    REQUIRE(settings.game_speed == 2);
    REQUIRE(settings.replay_speed == 6);
    REQUIRE(settings.recording);
    REQUIRE(settings.muted);
    REQUIRE_THROWS(save_settings(path, {3, 0, false, false}));
    for (const auto* source :
         {R"({"game_speed":-1})", R"({"replay_speed":7})", R"({"recording":"true"})", "not json"}) {
        std::ofstream output(path);
        output << source;
        output.close();
        REQUIRE_THROWS(load_settings(path));
    }
}

TEST_CASE("Recording is opt in and never begins midway through an unrecorded game", "[replay][saves]") {
    ReplayDirectory directory;
    Game game;
    Recorder recorder;
    recorder.new_game();
    walk(game, recorder, Direction::Up);
    const auto save = directory.path / "save1.dat";
    recorder.save(game, save);
    REQUIRE(contents(save).size() == 6957);
    REQUIRE_FALSE(std::filesystem::exists(recording_path(save)));
    recorder.enable(true);
    REQUIRE_FALSE(recorder.active());
    recorder.load(game, save);
    REQUIRE(recorder.enabled());
    REQUIRE_FALSE(recorder.active());
    walk(game, recorder, Direction::Left);
    recorder.save(game, directory.path / "quick.save");
    REQUIRE_FALSE(std::filesystem::exists(recording_path(directory.path / "quick.save")));
    game.new_game();
    recorder.new_game();
    REQUIRE(recorder.active());
}

TEST_CASE("Manual quick and raw Fairy recordings reproduce exact native save bytes", "[replay][saves]") {
    ReplayDirectory directory;
    for (const auto kind : {SaveKind::Slot, SaveKind::Checkpoint}) {
        Game game;
        Recorder recorder(true);
        recorder.new_game();
        walk(game, recorder, Direction::Up);
        walk(game, recorder, Direction::Left);
        const auto save = directory.path / (kind == SaveKind::Slot ? "quick.save" : "save0.dat");
        recorder.save(game, save, kind);
        REQUIRE(std::filesystem::exists(recording_path(save)));
        matches_save(save, kind);
        recorder.load(game, save, kind);
        REQUIRE(recorder.active());
        walk(game, recorder, Direction::Right);
        const auto resumed = directory.path / "save3.dat";
        recorder.save(game, resumed);
        matches_save(resumed);
    }
}

TEST_CASE("Loading a recorded save resumes that branch and discards later moves", "[replay][saves]") {
    ReplayDirectory directory;
    Game game;
    Recorder recorder(true);
    recorder.new_game();
    const auto first = directory.path / "save1.dat", later = directory.path / "save2.dat";
    walk(game, recorder, Direction::Up);
    recorder.save(game, first);
    walk(game, recorder, Direction::Up);
    walk(game, recorder, Direction::Up);
    recorder.save(game, later);
    recorder.load(game, first);
    walk(game, recorder, Direction::Left);
    const auto branch = directory.path / "save3.dat";
    recorder.save(game, branch);
    std::ifstream input(recording_path(branch));
    const auto history = read_replay(input);
    REQUIRE(history.size() == 6);
    REQUIRE(history[3].kind == InputKind::Reload);
    REQUIRE(history[4].direction == Direction::Left);
    matches_save(first);
    matches_save(later);
    matches_save(branch);
}

TEST_CASE("Save replacement pairs backups and removes stale companions when recording is off",
          "[replay][saves]") {
    ReplayDirectory directory;
    const auto save = directory.path / "save1.dat";
    auto backup = save;
    backup += ".bak";
    Game game;
    Recorder recorder(true);
    recorder.new_game();
    walk(game, recorder, Direction::Up);
    recorder.save(game, save);
    const auto original = contents(save);
    walk(game, recorder, Direction::Left);
    recorder.save(game, save);
    REQUIRE(contents(backup) == original);
    matches_save(save);
    matches_save(backup);
    recorder.enable(false);
    recorder.save(game, save);
    REQUIRE_FALSE(std::filesystem::exists(recording_path(save)));
    matches_save(backup);
    recorder.enable(true);
    recorder.load(game, save);
    REQUIRE_FALSE(recorder.active());
}

TEST_CASE("Missing malformed and stale companions leave a successfully loaded game unrecorded",
          "[replay][saves]") {
    ReplayDirectory directory;
    Game game;
    Recorder recorder(true);
    recorder.new_game();
    const auto recorded = directory.path / "save1.dat", unrecorded = directory.path / "save2.dat";
    walk(game, recorder, Direction::Up);
    recorder.save(game, recorded);
    game.save(unrecorded);
    recorder.load(game, unrecorded);
    REQUIRE_FALSE(recorder.active());
    recorder.load(game, recorded);
    REQUIRE(recorder.active());
    SECTION("Malformed companion") {
        std::ofstream(recording_path(recorded)) << "not json\n";
        recorder.load(game, recorded);
        REQUIRE_FALSE(recorder.active());
        REQUIRE(game.hero.hp == 1000);
        REQUIRE(game.status.find("Recording unavailable") != std::string::npos);
    }
    SECTION("Save overwritten after its recording") {
        const auto time = std::filesystem::last_write_time(recording_path(recorded));
        std::filesystem::last_write_time(recorded, time + std::chrono::seconds(1));
        recorder.load(game, recorded);
        REQUIRE_FALSE(recorder.active());
    }
    SECTION("Opt out despite existing companion") {
        recorder.enable(false);
        recorder.load(game, recorded);
        REQUIRE_FALSE(recorder.active());
    }
    SECTION("A failed game load preserves the current recording") {
        REQUIRE_THROWS(recorder.load(game, directory.path / "missing.dat"));
        REQUIRE(recorder.active());
        recorder.save(game, directory.path / "save3.dat");
        matches_save(directory.path / "save3.dat");
    }
}

TEST_CASE("A refused save preserves both files and the active recording", "[replay][saves]") {
    ReplayDirectory directory;
    Game game;
    Recorder recorder(true);
    recorder.new_game();
    const auto save = directory.path / "save1.dat";
    recorder.save(game, save);
    const auto bytes = contents(save), recording = contents(recording_path(save));
    game.push(Op::Wait);
    REQUIRE_THROWS(recorder.save(game, save));
    REQUIRE(recorder.active());
    REQUIRE(contents(save) == bytes);
    REQUIRE(contents(recording_path(save)) == recording);
    for (const auto& entry : std::filesystem::directory_iterator(directory.path))
        REQUIRE((entry.path() == save || entry.path() == recording_path(save)));
    game.finish_commands();
    walk(game, recorder, Direction::Up);
    recorder.save(game, save);
    matches_save(save);
}
