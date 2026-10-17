#include "tsw/blink.hpp"
#include "tsw/mouse_walk.hpp"
#include "tsw/replay.hpp"
#include <catch2/catch_test_macros.hpp>
#include <sstream>

using namespace tsw;

namespace {
Game corridor(int floor = 1) {
    Game game;
    game.hero.floor = floor;
    game.hero.x = 1;
    game.hero.y = 5;
    game.floors[floor].tiles.fill(Wall);
    for (int x = 1; x <= 9; ++x)
        game.tile_at(floor, x, 5) = Road;
    return game;
}

void walk(MouseWalk& walking, Game& game, float seconds = MouseWalk::StepSeconds) {
    walking.advance(game, seconds, [&](Direction direction) { REQUIRE(game.move(direction)); });
}

void finish_walk(MouseWalk& walking, Game& game) {
    for (int step = 0; step < CellCount && walking.active(); ++step)
        walk(walking, game);
    REQUIRE_FALSE(walking.active());
}
} // namespace

TEST_CASE("Mouse paths cross only apparent floor before the selected destination", "[mouse][movement]") {
    for (int obstacle :
         {int(YellowDoor), int(BlueDoor),   int(RedDoor),        int(SealedGate),      int(PrisonGate),
          int(Wall),       int(SecretWall), int(HiddenObject),   int(StairsUp),        int(StairsDown),
          int(Lava),       int(Void),       int(StarVoid),       int(SolidDecoration), int(Altar),
          int(AltarTop),   int(AltarSide),  int(Merchant),       int(Fairy),           int(Thief),
          int(OldMan),     int(TimeGate),   int(YellowKey),      int(RedPotion),       int(BlueGem),
          int(Cross),      int(IronSword),  int(GreenSlime),     int(GreenSlime + 1),  int(OctopusFirst),
          int(DragonHead), int(MagicianA),  int(GateKeeperA + 1)}) {
        INFO("Obstacle atlas ID: " << obstacle);
        auto game = corridor();
        game.tile_at(1, 3, 5) = static_cast<std::uint8_t>(obstacle);
        REQUIRE(mouse_path(game, cell(9, 5)).empty());
        REQUIRE(mouse_path(game, cell(3, 5)) == std::vector<int>{cell(2, 5), cell(3, 5)});
        MouseWalk walking;
        walking.start(game, cell(9, 5));
        walk(walking, game);
        REQUIRE(game.hero.x == 1);
    }
}

TEST_CASE("Mouse paths detour around visible events and respect board edges", "[mouse][movement]") {
    auto game = corridor();
    game.floors[1].tiles.fill(Road);
    game.tile_at(1, 2, 5) = YellowDoor;
    game.hero.yellow_keys = 1;
    MouseWalk walking;
    REQUIRE(mouse_path(game, cell(3, 5)).size() == 4);
    walking.start(game, cell(3, 5));
    finish_walk(walking, game);
    REQUIRE(game.hero.x == 3);
    REQUIRE(game.hero.y == 5);
    REQUIRE(game.hero.yellow_keys == 1);
    REQUIRE(game.tile_at(1, 2, 5) == YellowDoor);

    game.hero.x = 10;
    game.hero.y = 0;
    REQUIRE(mouse_path(game, cell(0, 1)).size() == BoardWidth);
    REQUIRE(mouse_path(game, -1).empty());
    REQUIRE(mouse_path(game, CellCount).empty());
    REQUIRE(mouse_path(game, cell(10, 0)).empty());
}

TEST_CASE("Mouse planning treats hidden triggers exactly like ordinary floor", "[mouse][hidden]") {
    auto game = corridor(3);
    const auto ordinary = mouse_path(game, cell(9, 5));
    REQUIRE(ordinary.size() == 8);
    game.tile_at(3, 4, 5) = SpecialRoad;
    REQUIRE(mouse_path(game, cell(9, 5)) == ordinary);

    MouseWalk walking;
    walking.start(game, cell(9, 5));
    finish_walk(walking, game);
    REQUIRE(game.hero.x == 4);
    REQUIRE(game.hero.y == 5);
    REQUIRE(game.tile_at(3, 4, 5) == Road);
    REQUIRE(game.busy());
    game.finish_commands();
    REQUIRE(game.dialogue.has_value());
    const auto before = game.hero;
    walk(walking, game, 10);
    REQUIRE(game.hero.x == before.x);
    REQUIRE(game.hero.y == before.y);
    game.finish_commands(true);
    const auto after = game.hero;
    walk(walking, game, 10);
    REQUIRE(game.hero.x == after.x);
    REQUIRE(game.hero.y == after.y);
}

TEST_CASE("Mouse routes stop on hidden floor contacts without movement or queued speech", "[mouse][hidden]") {
    for (int floor : {1, 23}) {
        auto game = corridor(floor);
        game.tile_at(floor, 4, 5) = SpecialRoad;
        REQUIRE(mouse_path(game, cell(9, 5)).size() == 8);
        MouseWalk walking;
        walking.start(game, cell(9, 5));
        finish_walk(walking, game);
        REQUIRE(game.hero.x == 3);
        game.finish_commands(true);
        REQUIRE_FALSE(game.busy());
        REQUIRE(game.tile_at(floor, 4, 5) == (floor == 23 ? Wall : SpecialRoad));
        walk(walking, game, 10);
        REQUIRE(game.hero.x == 3);
    }
}

TEST_CASE("Mouse door contact happens once per click including refusals", "[mouse][movement]") {
    for (int keys : {0, 1}) {
        auto game = corridor();
        game.tile_at(1, 3, 5) = YellowDoor;
        game.hero.yellow_keys = keys;
        MouseWalk walking;
        walking.start(game, cell(3, 5));
        finish_walk(walking, game);
        REQUIRE(game.hero.x == 2);
        REQUIRE(game.hero.yellow_keys == 0);
        game.finish_commands();
        walk(walking, game, 10);
        REQUIRE(game.hero.x == 2);
        REQUIRE(game.tile_at(1, 3, 5) == (keys ? Road : YellowDoor));
        if (keys) {
            walking.start(game, cell(3, 5));
            finish_walk(walking, game);
            REQUIRE(game.hero.x == 3);
        }
    }
}

TEST_CASE("Hidden walls and tunnels require separate clicks without revealing reachability",
          "[mouse][hidden]") {
    auto game = corridor();
    game.tile_at(1, 3, 5) = Wall;
    const auto wall_path = mouse_path(game, cell(3, 5));
    game.tile_at(1, 3, 5) = HiddenObject;
    REQUIRE(mouse_path(game, cell(3, 5)) == wall_path);
    game.tile_at(1, 3, 5) = game.tile_at(1, 4, 5) = SecretWall;
    REQUIRE(mouse_path(game, cell(3, 5)) == wall_path);
    REQUIRE(mouse_path(game, cell(4, 5)).empty());
    REQUIRE(mouse_path(game, cell(5, 5)).empty());

    MouseWalk walking;
    walking.start(game, cell(3, 5));
    finish_walk(walking, game);
    game.finish_commands();
    REQUIRE(game.hero.x == 2);
    REQUIRE(game.tile_at(1, 3, 5) == Road);
    REQUIRE(game.tile_at(1, 4, 5) == SecretWall);
    walk(walking, game, 10);
    REQUIRE(game.hero.x == 2);

    walking.start(game, cell(4, 5));
    finish_walk(walking, game);
    game.finish_commands();
    REQUIRE(game.hero.x == 3);
    REQUIRE(game.tile_at(1, 4, 5) == Road);
}

TEST_CASE("Mouse contact reveals a hidden object without automatically interacting again",
          "[mouse][hidden]") {
    Game game;
    game.hero.floor = 12;
    game.hero.x = 8;
    game.hero.y = 0;
    game.floors[12].tiles.fill(Wall);
    game.tile_at(12, 8, 0) = game.tile_at(12, 9, 0) = Road;
    game.tile_at(12, 10, 0) = HiddenObject;
    MouseWalk walking;
    walking.start(game, cell(10, 0));
    finish_walk(walking, game);
    game.finish_commands();
    REQUIRE(game.hero.x == 9);
    REQUIRE(game.tile_at(12, 10, 0) == Merchant);
    REQUIRE_FALSE(game.dialogue.has_value());
    walk(walking, game, 10);
    REQUIRE_FALSE(game.dialogue.has_value());
}

TEST_CASE("Mouse walking contacts only the selected pickup monster NPC or stair", "[mouse][movement]") {
    for (int target : {int(RedPotion), int(GreenSlime), int(Altar), int(StairsUp)}) {
        auto game = corridor();
        game.tile_at(1, 3, 5) = static_cast<std::uint8_t>(target);
        const auto hp = game.hero.hp;
        MouseWalk walking;
        walking.start(game, cell(3, 5));
        finish_walk(walking, game);
        game.finish_commands();
        REQUIRE_FALSE(walking.active());
        if (target == RedPotion) {
            REQUIRE(game.hero.x == 3);
            REQUIRE(game.hero.hp > hp);
        } else if (target == GreenSlime) {
            REQUIRE(game.tile_at(1, 3, 5) == Road);
            REQUIRE(game.hero.gold > 0);
        } else if (target == Altar) {
            REQUIRE(game.hero.x == 2);
            REQUIRE(game.dialogue.has_value());
        } else {
            REQUIRE(game.hero.floor == 2);
        }
    }
}

TEST_CASE("Mouse routes stop immediately when an ordinary floor step causes a hazard", "[mouse][hazards]") {
    for (int floor : {1, 47}) {
        auto game = corridor(floor);
        game.hero.equipment_found[SacredShieldFlag] = 0;
        game.tile_at(floor, 2, 4) = MagicianA;
        if (floor == 47) {
            game.tile_at(47, 2, 3) = Road;
            game.hero.equipment_found[SacredShieldFlag] = 1;
        }
        MouseWalk walking;
        walking.start(game, cell(9, 5));
        walk(walking, game);
        REQUIRE(game.hero.x == 2);
        REQUIRE_FALSE(walking.active());
        game.finish_commands();
        REQUIRE(game.hero.hp == (floor == 1 ? 800 : 1000));
        if (floor == 47)
            REQUIRE(game.tile_at(47, 2, 3) == MagicianA);
        walk(walking, game, 10);
        REQUIRE(game.hero.x == 2);
    }
}

TEST_CASE("Mouse walking uses the walking interval and new clicks replace or cancel the route",
          "[mouse][movement]") {
    auto game = corridor();
    MouseWalk walking;
    walking.start(game, cell(9, 5));
    walk(walking, game, 0);
    REQUIRE(game.hero.x == 2);
    walk(walking, game, MouseWalk::StepSeconds / 4);
    REQUIRE(game.hero.x == 2);
    walk(walking, game, MouseWalk::StepSeconds);
    REQUIRE(game.hero.x == 3);
    walk(walking, game, 10);
    REQUIRE(game.hero.x == 4); // No multi-step catch-up within one frame.
    walking.start(game, cell(2, 5));
    finish_walk(walking, game);
    REQUIRE(game.hero.x == 2);
    walking.start(game, cell(9, 5));
    walking.start(game, cell(game.hero.x, game.hero.y));
    REQUIRE_FALSE(walking.active());
    walking.start(game, cell(9, 5));
    walking.start(game, -1);
    REQUIRE_FALSE(walking.active());
    walking.start(game, cell(9, 5));
    walking.start(game, cell(0, 0)); // An unreachable click also cancels the old route.
    REQUIRE_FALSE(walking.active());
    walking.start(game, cell(9, 5));
    walking.cancel();
    walk(walking, game, 10);
    REQUIRE(game.hero.x == 2);
}

TEST_CASE("Mouse routes cannot resume across map changes manual steps or busy game state",
          "[mouse][movement]") {
    for (int change = 0; change < 4; ++change) {
        auto game = corridor();
        MouseWalk walking;
        walking.start(game, cell(9, 5));
        walk(walking, game);
        if (change == 0)
            game.hero.floor = 2;
        else if (change == 1)
            REQUIRE(game.move(Direction::Right));
        else if (change == 2)
            game.push(Op::Wait);
        else
            game.tile_at(1, 3, 5) = YellowKey;
        const auto position = cell(game.hero.x, game.hero.y);
        walk(walking, game, 10);
        REQUIRE_FALSE(walking.active());
        REQUIRE(cell(game.hero.x, game.hero.y) == position);
        game.finish_commands();
        walk(walking, game, 10);
        REQUIRE(cell(game.hero.x, game.hero.y) == position);
    }
    auto game = corridor();
    game.push(Op::Wait);
    MouseWalk walking;
    walking.start(game, cell(9, 5));
    game.finish_commands();
    REQUIRE_FALSE(walking.active());
}

TEST_CASE("Mouse movement records and replays ordinary native inputs", "[mouse][replay]") {
    Game game;
    // The initial floor's clear entrance corridor is reached using the original map.
    const auto path = mouse_path(game, cell(6, 9));
    REQUIRE_FALSE(path.empty());
    Recorder recorder(true);
    recorder.new_game(game.rankings);
    MouseWalk walking;
    int flight = -1;
    walking.start(game, cell(6, 9));
    for (int step = 0; step < CellCount && walking.active(); ++step) {
        walking.advance(game, MouseWalk::StepSeconds, [&](Direction direction) {
            const PlayerInput input = PlayerInput::move(direction);
            REQUIRE(apply_input(game, flight, input));
            recorder.append(input);
        });
        game.finish_commands();
    }
    REQUIRE_FALSE(walking.active());
    REQUIRE(game.hero.x == 6);
    REQUIRE(game.hero.y == 9);
    REQUIRE(recorder.history().size() == path.size() + 1);
    for (const auto& input : recorder.history().subspan(1))
        REQUIRE(input.kind == InputKind::Move);
    ReplayPlayer player({recorder.history().begin(), recorder.history().end()});
    Game replayed;
    player.seek(replayed, flight, player.size());
    REQUIRE(gameplay_json(replayed) == gameplay_json(game));
}

TEST_CASE("Blink crosses a connected clear route in one call without crossing events", "[blink][movement]") {
    auto game = corridor();
    game.floors[1].tiles.fill(Road);
    game.tile_at(1, 2, 5) = YellowDoor;
    game.hero.yellow_keys = 1;
    const auto before = gameplay_json(game);
    const auto path = blink_path(game, cell(3, 5));
    REQUIRE(path.size() == 4);
    REQUIRE(gameplay_json(game) == before);
    REQUIRE(blink_to(game, cell(3, 5), [&](Direction direction) { REQUIRE(game.move(direction)); }));
    REQUIRE(game.hero.x == 3);
    REQUIRE(game.hero.y == 5);
    REQUIRE(game.hero.yellow_keys == 1);
    REQUIRE(game.tile_at(1, 2, 5) == YellowDoor);
    REQUIRE_FALSE(game.busy());
}

TEST_CASE("Blink cannot cross a door monster pickup or hidden event", "[blink][movement]") {
    for (const int obstacle :
         {int(YellowDoor), int(BlueDoor), int(RedDoor), int(GreenSlime), int(RedPotion), int(YellowKey),
          int(Wall), int(SecretWall), int(HiddenObject), int(SpecialRoad), int(StairsUp), int(Altar)}) {
        INFO("Obstacle: " << obstacle);
        auto game = corridor();
        game.tile_at(1, 4, 5) = static_cast<std::uint8_t>(obstacle);
        REQUIRE(blink_path(game, cell(9, 5)).empty());
        int inputs = 0;
        REQUIRE_FALSE(blink_to(game, cell(9, 5), [&](Direction) { ++inputs; }));
        REQUIRE(inputs == 0);
        REQUIRE(game.hero.x == 1);
    }
}

TEST_CASE("Blink makes just one normal contact on a selected door or tunnel", "[blink][movement]") {
    for (const int target : {int(YellowDoor), int(SecretWall)}) {
        for (const int keys : {0, 1}) {
            auto game = corridor();
            game.hero.yellow_keys = keys;
            game.tile_at(1, 5, 5) = static_cast<std::uint8_t>(target);
            REQUIRE(blink_to(game, cell(5, 5), [&](Direction direction) { REQUIRE(game.move(direction)); }));
            REQUIRE(game.hero.x == 4);
            game.finish_commands();
            REQUIRE(game.hero.x == 4);
            REQUIRE(game.hero.yellow_keys == (target == YellowDoor ? 0 : keys));
            REQUIRE(game.tile_at(1, 5, 5) == (target == SecretWall || keys ? Road : YellowDoor));
        }
    }
}

TEST_CASE("Blink selected events retain native combat dialogue pickup and stair behavior",
          "[blink][movement]") {
    for (const int target : {int(RedPotion), int(GreenSlime), int(Altar), int(StairsUp)}) {
        auto game = corridor();
        game.tile_at(1, 5, 5) = static_cast<std::uint8_t>(target);
        auto expected = game;
        for (int i = 0; i < 4; ++i)
            REQUIRE(expected.move(Direction::Right));
        REQUIRE(blink_to(game, cell(5, 5), [&](Direction direction) { REQUIRE(game.move(direction)); }));
        REQUIRE(gameplay_json(game) == gameplay_json(expected));
        game.finish_commands();
        expected.finish_commands();
        REQUIRE(gameplay_json(game) == gameplay_json(expected));
    }
}

TEST_CASE("Blink avoids magic pincer damage and moving magicians without probing live state",
          "[blink][hazards]") {
    for (const int floor : {1, 47}) {
        auto game = corridor(floor);
        game.hero.equipment_found[SacredShieldFlag] = floor == 47;
        game.tile_at(floor, 4, 4) = MagicianA;
        game.tile_at(floor, 4, 3) = Road;
        const auto before = gameplay_json(game);
        REQUIRE(blink_path(game, cell(9, 5)).empty());
        REQUIRE(gameplay_json(game) == before);
        REQUIRE(game.commands.empty());
        REQUIRE(game.sounds.empty());
    }
    auto game = corridor();
    game.hero.equipment_found[SacredShieldFlag] = 0;
    game.tile_at(1, 4, 4) = game.tile_at(1, 4, 6) = Sorcerer;
    REQUIRE(blink_path(game, cell(9, 5)).empty());
    game.floors[1].tiles.fill(Road);
    game.tile_at(1, 4, 4) = MagicianA;
    const auto hp = game.hero.hp;
    REQUIRE(blink_to(game, cell(9, 5), [&](Direction direction) { REQUIRE(game.move(direction)); }));
    REQUIRE(game.hero.x == 9);
    REQUIRE(game.hero.hp == hp);
    REQUIRE_FALSE(game.busy());
}

TEST_CASE("Blink validates its start edges nearby clicks and busy state", "[blink][movement]") {
    auto game = corridor();
    for (const int destination : {-1, CellCount, cell(1, 5), cell(2, 5), cell(0, 0)})
        REQUIRE(blink_path(game, destination).empty());
    game.tile_at(1, 1, 5) = StairsUp;
    REQUIRE_FALSE(blink_path(game, cell(9, 5)).empty());
    game.hero.equipment_found[SacredShieldFlag] = 0;
    game.tile_at(1, 1, 4) = MagicianA;
    REQUIRE(blink_path(game, cell(9, 5)).empty());
    game.tile_at(1, 1, 4) = Wall;
    game.push(Op::Wait);
    REQUIRE(blink_path(game, cell(9, 5)).empty());
    game.finish_commands();
    game.hero.x = 10;
    game.hero.y = 0;
    game.floors[1].tiles.fill(Road);
    REQUIRE(blink_path(game, cell(0, 1)).size() == BoardWidth);
}

TEST_CASE("Blink picks TSWH5's first safe adjacent approach to a selected event", "[blink][movement]") {
    auto game = corridor();
    game.floors[1].tiles.fill(Road);
    game.hero.x = 8;
    game.tile_at(1, 5, 5) = Altar;
    const auto path = blink_path(game, cell(5, 5));
    REQUIRE(path.back() == cell(5, 5));
    REQUIRE(path[path.size() - 2] == cell(4, 5));
    REQUIRE(blink_to(game, cell(5, 5), [&](Direction direction) { REQUIRE(game.move(direction)); }));
    REQUIRE(game.hero.x == 4);
    REQUIRE(game.dialogue.has_value());
}

TEST_CASE("Blink records native moves and replays the identical save", "[blink][replay]") {
    Game game;
    Recorder recorder(true);
    recorder.new_game(game.rankings);
    int flight = -1;
    REQUIRE(blink_to(game, cell(6, 9), [&](Direction direction) {
        const auto input = PlayerInput::move(direction);
        REQUIRE(apply_input(game, flight, input));
        recorder.append(input);
    }));
    REQUIRE(game.hero.x == 6);
    REQUIRE(game.hero.y == 9);
    ReplayPlayer player({recorder.history().begin(), recorder.history().end()});
    Game replayed;
    player.seek(replayed, flight, player.size());
    REQUIRE(gameplay_json(replayed) == gameplay_json(game));
    std::ostringstream actual, expected;
    game.save(actual);
    replayed.save(expected);
    REQUIRE(actual.str() == expected.str());
}
