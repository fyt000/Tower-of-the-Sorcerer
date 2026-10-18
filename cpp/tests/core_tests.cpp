#include "tsw/game.hpp"
#include "tsw/game_state.hpp"
#include "tsw/localization.hpp"
#include "tsw/save_slots.hpp"
#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <chrono>
#include <fstream>
#include <stdexcept>

using namespace tsw;

Game room(int floor = 1) {
    Game game;
    game.hero.floor = floor;
    game.hero.x = game.hero.y = 5;
    game.floors[floor].tiles.fill(Road);
    return game;
}

std::filesystem::path temporary_save(const char* name) {
    return std::filesystem::path(TSW_TEST_TEMP) /
           (std::string(name) + "-" +
            std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()) + ".save");
}

TEST_CASE("Defeated enemy panel retains encounter statistics", "[combat]") {
    auto g = room();
    g.tile(1, cell(5, 4)) = GreenSlime;
    g.move(Direction::Up);
    g.finish_commands();
    UNSCOPED_INFO("Successful battle retains the defeated enemy's encounter statistics");
    REQUIRE((g.visual.last_defeated && g.visual.last_defeated->monster_index == 0 &&
             g.visual.last_defeated->stats.hp == 35 && g.visual.last_defeated->damage == 0));
    g.monsters[0].hp = 999;
    g.move(Direction::Left);
    g.finish_commands();
    UNSCOPED_INFO("Walking and later shared monster changes preserve the previous battle record");
    REQUIRE(g.visual.last_defeated->stats.hp == 35);
    g.hero.hp = 1;
    g.hero.attack = 10;
    g.hero.defense = 0;
    g.tile(1, cell(4, 3)) = RedSlime;
    g.move(Direction::Up);
    g.finish_commands();
    UNSCOPED_INFO("A fatal encounter does not replace the last defeated enemy");
    REQUIRE((g.visual.dead && g.visual.last_defeated->monster_index == 0));
    g.new_game();
    UNSCOPED_INFO("A new game clears the defeated enemy panel");
    REQUIRE(!g.visual.last_defeated);
}

TEST_CASE("Doors consume keys without moving the hero", "[movement]") {
    auto g = room();
    g.tile(1, cell(5, 4)) = YellowDoor;
    g.hero.yellow_keys = 1;
    g.move(Direction::Up);
    g.finish_commands();
    UNSCOPED_INFO("Door opens without movement");
    REQUIRE((g.hero.y == 5 && g.tile(1, cell(5, 4)) == Road && g.hero.yellow_keys == 0));
    g.move(Direction::Up);
    UNSCOPED_INFO("Second step enters open door");
    REQUIRE(g.hero.y == 4);
}

TEST_CASE("Potion and gem rewards use the cycle factor", "[items]") {
    for (int scale : {0, 43}) {
        auto g = room(12);
        g.hero.cycle_factor_minus_one = scale;
        g.tile(12, cell(5, 4)) = RedPotion;
        g.move(Direction::Up);
        g.finish_commands();
        UNSCOPED_INFO("Potion scaling");
        REQUIRE(g.hero.hp == 1000 + 100 * (scale + 1));
        g.tile(12, cell(4, 4)) = RedGem;
        g.move(Direction::Left);
        g.finish_commands();
        UNSCOPED_INFO("Gem scaling");
        REQUIRE(g.hero.attack == 100 + 2 * (scale + 1));
    }
}

TEST_CASE("Fatal pincer damage cancels later rewards", "[hazards]") {
    auto g = room();
    g.hero.equipment_found[9] = 0;
    g.hero.hp = 1;
    g.tile(1, cell(4, 4)) = g.tile(1, cell(6, 4)) = Sorcerer;
    g.move(Direction::Up);
    g.commands.insert(g.commands.begin(), {Op::Reward, 100, 0}); // Executes after the pending damage.
    g.finish_commands();
    UNSCOPED_INFO("Pincer death cancels later rewards");
    REQUIRE((g.hero.hp == 0 && g.visual.dead && g.hero.gold == 0));
}

TEST_CASE("47F Magician retreats even when the shield prevents damage", "[hazards]") {
    auto g = room(47);
    g.tile(47, cell(5, 3)) = MagicianA;
    g.move(Direction::Up);
    g.finish_commands();
    UNSCOPED_INFO("Shield protects; magician still retreats");
    REQUIRE((g.tile(47, cell(5, 2)) == MagicianA && g.hero.hp == 1000));
}

TEST_CASE("47F horizontal retreat retains wrapping within the tile array", "[hazards][quirks]") {
    auto g = room(47);
    g.hero.x = 9;
    g.hero.y = 6;
    g.tile_at(47, 10, 5) = MagicianA;
    REQUIRE(g.move(Direction::Up));
    g.finish_commands();
    REQUIRE(g.tile_at(47, 10, 5) == Road);
    REQUIRE(g.tile_at(47, 0, 6) == MagicianA);
}

TEST_CASE("47F retreat rejects tile 121 and preserves the next floor's stair metadata", "[hazards]") {
    auto g = room(47);
    g.hero.x = 0;
    g.hero.y = 8;
    g.tile_at(47, 0, 10) = MagicianA;
    g.floors[48].up_landing = Road; // Make the adjacent metadata look like a free tile in the old layout.
    REQUIRE(g.move(Direction::Down));
    g.finish_commands();
    REQUIRE(g.tile_at(47, 0, 10) == MagicianA);
    REQUIRE(g.floors[48].up_landing == Road);
}

TEST_CASE("33F lower entrance retains the original trap softlock", "[quirks]") {
    Game g;
    g.hero.floor = 33;
    g.hero.x = 9;
    g.hero.y = 7;
    g.hero.attack = g.hero.defense = 10000;
    const auto walk = [&](Direction direction) {
        g.move(direction);
        g.finish_commands();
    };
    walk(Direction::Up);
    UNSCOPED_INFO("Original 33F lower entrance does not trigger the trap");
    REQUIRE((g.hero.y == 6 && g.tile_at(33, 9, 4) == SpecialRoad && g.tile_at(33, 9, 3) == Road &&
             g.tile_at(33, 9, 7) == Road));
    for (auto direction : {Direction::Up, Direction::Left, Direction::Up, Direction::Down, Direction::Right,
                           Direction::Right, Direction::Up, Direction::Down, Direction::Down, Direction::Left,
                           Direction::Left, Direction::Right, Direction::Up})
        walk(direction);
    UNSCOPED_INFO("All four 33F guards can be defeated before touching the upper trigger");
    REQUIRE((g.hero.x == 9 && g.hero.y == 5 && g.hero.gold == 160 && g.tile_at(33, 8, 4) == Road &&
             g.tile_at(33, 10, 4) == Road && g.tile_at(33, 8, 6) == Road && g.tile_at(33, 10, 6) == Road));
    walk(Direction::Up);
    UNSCOPED_INFO("The late 33F trigger seals both exits with no remaining guard to reopen them");
    REQUIRE((g.tile_at(33, 9, 3) == SealedGate && g.tile_at(33, 9, 7) == SealedGate && !g.busy()));
    walk(Direction::Up);
    UNSCOPED_INFO("The original 33F softlock remains in the baseline");
    REQUIRE(g.hero.y == 4);
}

TEST_CASE("45F Merchant retains unscaled backside HP", "[quirks]") {
    for (int cycle : {0, 43}) {
        auto g = room(45);
        g.hero.cycle_factor_minus_one = cycle;
        g.hero.gold = 1000;
        g.tile_at(45, 5, 4) = Merchant;
        g.move(Direction::Up);
        UNSCOPED_INFO("45F Merchant accepts the original offer");
        REQUIRE((g.dialogue && g.dialogue->shop && g.choose(0)));
        g.finish_commands();
        UNSCOPED_INFO("45F Merchant adds an unscaled 2000 HP on both sides");
        REQUIRE((g.hero.hp == 3000 && g.hero.gold == 0 && g.hero.merchant_used[10]));
    }
}

TEST_CASE("Lucky Gold rewards and completion text", "[combat]") {
    for (bool enemy_first : {false, true})
        for (int lucky_gold : {0, 1}) {
            CAPTURE(enemy_first, lucky_gold);
            auto g = room();
            g.hero.attack = g.hero.defense = 10000;
            g.hero.gold = 123;
            g.inventory(Item::LuckyGold) = lucky_gold;
            g.contact_index = cell(5, 4);
            g.tile(1, g.contact_index) = GreenSlime;
            g.battle(enemy_first);
            g.finish_commands();
            REQUIRE(g.hero.gold == 124 + lucky_gold);
            REQUIRE(g.status ==
                    "Defeated Green Slime. Received " + std::to_string(1 + lucky_gold) + " gold.");
        }
}

TEST_CASE("Octopus completion text includes half rewards and Lucky Gold", "[combat]") {
    for (int target : {OctopusFirst, OctopusMouth}) {
        CAPTURE(target);
        auto g = room();
        g.hero.attack = g.hero.defense = 100000;
        g.hero.cycle_factor_minus_one = 43;
        g.inventory(Item::LuckyGold) = 1;
        g.contact_index = cell(5, 4);
        g.tile(1, g.contact_index) = static_cast<std::uint8_t>(target);
        g.battle(false);
        g.finish_commands();
        const int expected = target == OctopusMouth ? 200 : 100;
        REQUIRE(g.hero.gold == expected);
        REQUIRE(g.status == "Defeated Giant Octopus. Received " + std::to_string(expected) + " gold.");
    }
}

TEST_CASE("Bomb and blocked consumables retain original item rules", "[items]") {
    auto g = room();
    g.inventory(Item::Bomb) = g.inventory(Item::LuckyGold) = 1;
    g.tile(1, cell(5, 4)) = GreenSlime;
    g.use(Item::Bomb);
    g.finish_commands();
    UNSCOPED_INFO("Bomb gold is raw");
    REQUIRE((g.hero.gold == g.monsters[0].gold && g.tile(1, cell(5, 4)) == Road));
    g.inventory(Item::Mattock) = 1;
    g.use(Item::Mattock);
    g.finish_commands();
    UNSCOPED_INFO("Empty mattock consumed");
    REQUIRE(g.inventory(Item::Mattock) == 0);
    g.inventory(Item::WarpStaff) = 1;
    g.tile(1, 60) = Wall;
    g.use(Item::WarpStaff);
    UNSCOPED_INFO("Blocked warp consumed");
    REQUIRE(g.inventory(Item::WarpStaff) == 0);
}

TEST_CASE("Stairs and wings retain different 44F rules", "[movement]") {
    auto g = room(43);
    g.tile(43, cell(5, 4)) = StairsUp;
    g.move(Direction::Up);
    g.finish_commands();
    UNSCOPED_INFO("Stairs skip 44");
    REQUIRE((g.hero.floor == 45 && g.hero.highest_floor == 45));
    g = room(43);
    g.floors[44].tiles.fill(Road);
    g.inventory(Item::AscentWing) = 1;
    g.use(Item::AscentWing);
    g.finish_commands();
    UNSCOPED_INFO("Wing includes 44 without changing stair ceiling");
    REQUIRE((g.hero.floor == 44 && g.hero.highest_floor == 1));
}

TEST_CASE("42F arrival preserves the original Thief flag alias", "[scenes]") {
    auto g = room(41);
    g.hero.dialogue_seen[51] = 1;
    g.tile(41, cell(5, 4)) = StairsUp;
    g.tile_at(35, 4, 9) = Thief;
    g.move(Direction::Up);
    g.finish_commands(true);
    UNSCOPED_INFO("42F arrival uses the dialogue continuation flag alias");
    REQUIRE((g.hero.floor == 42 && g.tile_at(35, 4, 9) == Thief));
    g = room(41);
    g.tile(41, cell(5, 4)) = StairsUp;
    g.tile_at(35, 4, 9) = Thief;
    g.move(Direction::Up);
    g.finish_commands(true);
    UNSCOPED_INFO("First 42F arrival runs the original scene");
    REQUIRE((g.hero.dialogue_seen[51] && g.tile_at(35, 4, 9) == Road));
}

TEST_CASE("Combat forecasts and playback retain attack bonuses", "[combat]") {
    auto g = room();
    g.hero.attack = 100;
    g.hero.defense = 0;
    g.hero.hp = 1000;
    g.hero.equipment_found[9] = 0;
    g.monsters[0] = {250, 30, 10, 7};
    g.tile(1, cell(5, 4)) = GreenSlime;
    UNSCOPED_INFO("Player-first formula");
    REQUIRE(g.forecast(GreenSlime).damage == 60);
    g.move(Direction::Up);
    g.finish_commands();
    UNSCOPED_INFO("Combat playback result");
    REQUIRE((g.hero.hp == 940 && g.hero.gold == 7 && g.hero.y == 4));
    g = room();
    g.hero.attack = 50;
    g.monsters[12] = {300, 20, 60, 1};
    g.inventory(Item::Cross) = 1;
    UNSCOPED_INFO("Base ATK guard before Cross");
    REQUIRE(!g.forecast(85).penetrates);
    g.hero.attack = 100;
    UNSCOPED_INFO("Forced combat ignores Cross");
    REQUIRE((g.forecast(85, true).damage >= g.forecast(85).damage));
}

TEST_CASE("Long original fights complete with bounded command memory", "[combat]") {
    for (const auto [enemy_tile, cycle] : {std::pair<int, int>{GreatMagicMaster, 0}, {GateKeeperA, 43}}) {
        auto g = room();
        g.hero.hp = 100000;
        g.hero.cycle_factor_minus_one = cycle;
        const auto enemy = g.monsters[Game::monster_for_tile(enemy_tile)];
        g.hero.attack = enemy.defense * (cycle + 1) + 1;
        g.hero.defense = enemy.attack * (cycle + 1);
        g.tile(1, cell(5, 4)) = std::uint8_t(enemy_tile);
        const auto forecast = g.forecast(enemy_tile);
        UNSCOPED_INFO("Exercise an actual original overflow-triggering fight");
        REQUIRE(forecast.hero_strike_count >= 2500);
        g.move(Direction::Up);
        std::size_t maximum = 0;
        std::int64_t hero_strikes = 0;
        Command executed;
        for (int n = 0; n < 200000 && g.run_one(&executed); ++n) {
            maximum = std::max(maximum, g.commands.size());
            hero_strikes += executed.op == Op::HeroStrike;
        }
        UNSCOPED_INFO("Long fights retain every round with bounded command memory");
        REQUIRE((maximum < 20 && hero_strikes == forecast.hero_strike_count && !g.busy()));
        UNSCOPED_INFO("Overflow-length fights finish without corrupting hero or map state");
        REQUIRE((g.hero.hp == 100000 && g.hero.gold == enemy.gold && g.tile_at(1, 5, 4) == Road));
    }
}

TEST_CASE("Skipping battle rounds preserves native damage rewards and final strikes", "[combat]") {
    for (int target : {int(GreenSlime), int(Vampire), int(DragonHead), int(OctopusMouth), int(OctopusFirst),
                       int(GreatMagicMaster)})
        for (int cycle : {0, 43})
            for (bool enemy_first : {false, true})
                for (bool fatal : {false, true})
                    for (int delay : {0, 1, 5, 13}) {
                        CAPTURE(target, cycle, enemy_first, fatal, delay);
                        auto native = room();
                        native.hero.cycle_factor_minus_one = cycle;
                        native.monsters[Game::monster_for_tile(target)] = {200, 40, 20, 7};
                        native.hero.hp = fatal ? 7 : 100000;
                        native.hero.attack = 20 * (cycle + 1) + 3;
                        native.hero.defense = 40 * (cycle + 1) - 2;
                        native.inventory(Item::Cross) = native.inventory(Item::DragonSlayer) = 1;
                        native.inventory(Item::LuckyGold) = 1;
                        native.contact_index = cell(5, 4);
                        native.tile(1, native.contact_index) = std::uint8_t(target);
                        native.battle(enemy_first);
                        auto skipped = native;
                        native.finish_commands();
                        int commands = 0;
                        for (; commands < 1000; ++commands) {
                            if (commands >= delay)
                                skipped.skip_battle_rounds();
                            if (!skipped.run_one())
                                break;
                        }
                        REQUIRE(commands < 1000);
                        REQUIRE(skipped.hero == native.hero);
                        REQUIRE(skipped.floors == native.floors);
                        REQUIRE(skipped.run_history == native.run_history);
                        REQUIRE(skipped.commands == native.commands);
                        REQUIRE(skipped.status == native.status);
                        REQUIRE(skipped.visual.enemy_hp == native.visual.enemy_hp);
                        REQUIRE(skipped.visual.dead == native.visual.dead);
                        REQUIRE(skipped.busy() == native.busy());
                    }
}

TEST_CASE("Skipping a hundred million battle rounds takes bounded work", "[combat]") {
    auto game = room();
    game.monsters[0] = {100000000, 1, 1, 7};
    game.hero.attack = 2;
    game.hero.defense = 1;
    game.tile_at(1, 5, 4) = GreenSlime;
    game.move(Direction::Up);
    int commands = 0;
    for (; commands < 100; ++commands) {
        game.skip_battle_rounds();
        if (!game.run_one())
            break;
    }
    REQUIRE(commands < 100);
    REQUIRE_FALSE(game.busy());
    REQUIRE(game.hero.hp == 1000);
    REQUIRE(game.hero.gold == 7);
    REQUIRE(game.tile_at(1, 5, 4) == Road);
}

TEST_CASE("49F summon executes only its 128 written commands", "[scenes]") {
    for (bool longer_event : {false, true}) {
        auto g = room(49);
        if (longer_event) {
            g.commands.assign(600, {Op::Wait, 0, 0});
            g.finish_commands();
        }
        g.push(Op::Callback, Callback::SummonGuards);
        g.run_one();
        UNSCOPED_INFO("49F materialization starts with the first written command, never a ghost record");
        REQUIRE((g.commands.size() == 128 && g.commands.back().op == Op::Overlay &&
                 g.commands.back().a == 15 && g.commands.back().b == 167));
        g.finish_commands();
        UNSCOPED_INFO("49F materialization has the same safe outcome after a longer preceding event");
        REQUIRE((g.hero.hp == 1000 && g.hero.gold == 0 && !g.busy() &&
                 std::count(g.floors[49].tiles.begin(), g.floors[49].tiles.end(), Sorcerer) == 8));
    }
}

TEST_CASE("Altar purchases and Thief continuation update original state", "[npcs]") {
    auto g = room();
    g.hero.gold = 100;
    g.tile(1, cell(5, 4)) = Altar;
    g.move(Direction::Up);
    g.choose(1);
    g.finish_commands();
    UNSCOPED_INFO("Altar first transaction");
    REQUIRE((g.hero.attack == 102 && g.hero.gold == 80 && g.hero.altar_purchases == 1));
    g.hero.floor = 2;
    g.hero.x = 2;
    g.hero.y = 7;
    g.contact_index = 68;
    g.tile(2, 68) = Thief;
    g.contact();
    g.finish_commands(true);
    UNSCOPED_INFO("Thief continuation flag");
    REQUIRE(g.hero.dialogue_seen[14] == 1);
}

TEST_CASE("Old Man dialogue rewards are granted only once", "[npcs]") {
    auto g = room(2);
    g.tile(2, cell(5, 4)) = OldMan;
    g.move(Direction::Up);
    g.finish_commands(true);
    UNSCOPED_INFO("Old-man gift shares original continuation slot 18");
    REQUIRE((g.hero.attack == 103 && g.hero.defense == 103 && g.hero.dialogue_seen[18] == 1));
    UNSCOPED_INFO("First hearing without Wisdom is retained");
    REQUIRE(g.hero.old_man_heard[0] == HintState::Heard);
    g.inventory(Item::WisdomOrb) = 1;
    g.move(Direction::Up);
    g.finish_commands(true);
    UNSCOPED_INFO("Repeated hearing does not grant or record the gift again");
    REQUIRE((g.hero.attack == 103 && g.hero.old_man_heard[0] == HintState::Heard));
}

TEST_CASE("Fairy checkpoint follows dialogue and scene completion", "[saves]") {
    auto g = room(10);
    g.tile(10, cell(5, 4)) = Fairy;
    g.hero.music_track = MusicTrack::Disabled;
    g.move(Direction::Up);
    UNSCOPED_INFO("Fairy requests a checkpoint while her scene is pending");
    REQUIRE((g.checkpoint_requested && g.busy()));
    UNSCOPED_INFO("Fairy score and default rank retain disabled music");
    REQUIRE(
        (g.hero.fairy_score == 415 && g.hero.fairy_rank == 1 && g.hero.music_track == MusicTrack::Disabled));
    g.finish_commands(true);
    UNSCOPED_INFO("Fairy checkpoint becomes saveable after her scene");
    REQUIRE((!g.busy() && g.tile(10, 27) == Road));
    const auto path = temporary_save("tos-baseline-fairy-test");
    g.save(path, SaveKind::Checkpoint);
    Game restored;
    restored.load(path, SaveKind::Checkpoint);
    UNSCOPED_INFO("Fairy checkpoint restores completed gameplay state");
    REQUIRE((restored.hero.fairy_score == 415 && restored.hero.fairy_visits == 1 &&
             restored.tile(10, 27) == Road));
    std::filesystem::remove(path);
}

TEST_CASE("Capture and new game retain original reset rules", "[scenes]") {
    auto g = room();
    g.hero.gold = 999;
    g.hero.equipment_found[1] = 1;
    g.inventory(Item::Bomb) = 1;
    g.push(Op::Callback, Callback::Capture);
    g.finish_commands(true);
    UNSCOPED_INFO("First-cycle capture preserves lower acquisition flags and specials");
    REQUIRE((g.hero.hp == 400 && g.hero.floor == 2 && g.hero.highest_floor == 2 &&
             g.hero.equipment_found[1] && g.inventory(Item::Bomb)));
    g.hero.cycle_factor_minus_one = 43;
    g.hero.hp = 321;
    g.push(Op::Callback, Callback::Capture);
    g.finish_commands(true);
    UNSCOPED_INFO("Backside capture preserves stats and clears specials");
    REQUIRE((g.hero.hp == 321 && !g.inventory(Item::Bomb)));
}

TEST_CASE("Fairy snapshots keep the original raw records and validate bounds", "[saves]") {
    constexpr std::size_t MapBytes = 6273, SaveBytes = 6957;
    const auto manual = temporary_save("manual-record");
    const auto checkpoint = temporary_save("fairy-record");
    const auto read = [](const std::filesystem::path& path) {
        std::ifstream input(path, std::ios::binary);
        return std::vector<unsigned char>(std::istreambuf_iterator<char>(input), {});
    };
    auto game = room(10);
    game.save(manual);
    const auto previous = read(manual);
    game.hero.hp = 1234;
    game.hero.fairy_visits = 1;
    game.hero.fairy_score = 415;
    game.hero.fairy_rank = 1;
    game.hero.fairy_category = FairyCategory::Floor10;
    game.save(checkpoint, SaveKind::Checkpoint);
    const auto bytes = read(checkpoint);
    REQUIRE(bytes.size() == SaveBytes);
    REQUIRE(std::equal(bytes.begin(), bytes.begin() + MapBytes, previous.begin()));
    REQUIRE(std::equal(bytes.begin() + MapBytes + 656, bytes.begin() + MapBytes + 664,
                       previous.begin() + MapBytes + 656));
    Game restored;
    REQUIRE_THROWS_AS(restored.load(checkpoint), std::runtime_error);
    restored.load(checkpoint, SaveKind::Checkpoint);
    REQUIRE(restored.hero.hp == 1234);
    REQUIRE(restored.hero.fairy_visits == 1);
    REQUIRE(restored.hero.fairy_score == 415);
    restored.save(manual);
    Game slot;
    slot.load(manual);
    REQUIRE(slot.hero.fairy_score == 415);
    // Raw checkpoint reading skips only the original checksum gate, never field validation.
    {
        std::fstream corrupt(checkpoint, std::ios::binary | std::ios::in | std::ios::out);
        corrupt.seekp(MapBytes + 16);
        const char invalid_floor[4]{51, 0, 0, 0};
        corrupt.write(invalid_floor, sizeof invalid_floor);
    }
    REQUIRE_THROWS_AS(restored.load(checkpoint, SaveKind::Checkpoint), std::runtime_error);
    REQUIRE(restored.hero.floor == 10);
    REQUIRE(restored.hero.hp == 1234);
    std::filesystem::remove(checkpoint);
    std::filesystem::remove(manual);
    std::filesystem::remove(manual.string() + ".bak");
}

TEST_CASE("Original saves preserve shared Zeno and reject invalid records", "[saves]") {
    auto g = room(49);
    g.hero.zeno_sealed = true;
    g.monsters[15] = {800, 500, 100, 500};
    const auto path = temporary_save("tos-baseline-test-save");
    g.save(path);
    Game restored;
    restored.load(path);
    UNSCOPED_INFO("Original save reconstructs frontside sealed Zeno");
    REQUIRE((restored.monsters[15].hp == 800 && restored.hero.zeno_sealed && restored.hero.floor == 49));
    UNSCOPED_INFO("New saves use the exact original record size without a monster table or extension");
    REQUIRE(std::filesystem::file_size(path) == FloorCount * (CellCount + 2) + 171 * 4);
    restored.save(path);
    restored.load(path);
    UNSCOPED_INFO("Repeated restore does not scale Zeno again");
    REQUIRE(restored.monsters[15].hp == 800);
    g.hero.equipment_found[0] = 2;
    UNSCOPED_INFO("Save rejects non-boolean equipment acquisition flags");
    REQUIRE_THROWS_AS(g.save(path), std::runtime_error);
    restored.load(path);
    UNSCOPED_INFO("Rejected save leaves the previous file intact");
    REQUIRE(restored.monsters[15].hp == 800);
    {
        std::fstream corrupt(path, std::ios::in | std::ios::out | std::ios::binary);
        corrupt.seekp(FloorCount * (CellCount + 2)); // HP is covered by the original checksums.
        corrupt.put('X');
    }
    UNSCOPED_INFO("Malformed save rejected without changing live game");
    REQUIRE_THROWS_AS(restored.load(path), std::runtime_error);
    REQUIRE(restored.hero.floor == 49);
    std::filesystem::remove(path);
    auto backup = path;
    backup += ".bak";
    std::filesystem::remove(backup);
}

TEST_CASE("Frontside ending and later cycles preserve their carry rules", "[scenes]") {
    auto g = room(50);
    g.hero.hp = 81234;
    g.hero.attack = 12345;
    g.hero.defense = 6789;
    g.hero.gold = 99;
    g.hero.highest_floor = 50;
    g.inventory(Item::Bomb) = 1;
    g.hero.equipment_found[0] = 1;
    g.tile(50, cell(5, 4)) = Zeno;
    g.move(Direction::Up);
    UNSCOPED_INFO("Frontside 50F Zeno starts the ending, not combat");
    REQUIRE((!g.visual.battle && !g.commands.empty()));
    g.finish_commands(true);
    UNSCOPED_INFO("First ending starts the second cycle with the 44x backside factor");
    REQUIRE((!g.busy() && g.hero.floor == 1 && g.hero.cycle_factor_minus_one == 43 && !g.hero.later_cycle));
    UNSCOPED_INFO("Second cycle carries stats and resets gold, items and acquisition flags");
    REQUIRE((g.hero.hp == 81234 && g.hero.attack == 12345 && g.hero.defense == 6789 && g.hero.gold == 0 &&
             !g.inventory(Item::Bomb) && !g.hero.equipment_found[0]));
    g.hero.gold = 99;
    g.hero.highest_floor = 50;
    g.inventory(Item::Bomb) = 1;
    g.hero.equipment_found[0] = 1;
    g.next_cycle();
    UNSCOPED_INFO("Third and later cycles preserve gold, explored ceiling, items and acquisition flags");
    REQUIRE((g.hero.later_cycle && g.hero.gold == 99 && g.hero.highest_floor == 50 &&
             g.inventory(Item::Bomb) && g.hero.equipment_found[0]));
}

TEST_CASE("24F gate restores the shared seal and forces 50F combat", "[scenes]") {
    // Play the actual 24F gate sequence: it restores a seal, teleports to 50F and forces cycle-2 combat.
    auto g = room(24);
    g.hero.cycle_factor_minus_one = 43;
    g.hero.zeno_sealed = true;
    g.monsters[ZenoRow] = {800, 500, 100, 500};
    g.hero.hp = g.hero.attack = 100000;
    g.hero.defense = 0;
    g.check_floor();
    UNSCOPED_INFO("Second-cycle gate removes the seal and installs the fixed Zeno row");
    REQUIRE((!g.hero.zeno_sealed && g.monsters[ZenoRow].hp == 1000 && g.monsters[ZenoRow].attack == 625 &&
             g.monsters[ZenoRow].defense == 125));
    bool forced = false;
    for (int n = 0; n < 10000; ++n) {
        if (g.dialogue)
            g.continue_dialogue();
        Command command;
        if (!g.run_one(&command))
            break;
        if (command.op == Op::Callback && command.a == int(Callback::ForcedBattle)) {
            forced = true;
            UNSCOPED_INFO("Second-cycle gate plays an enemy-first 50F Zeno encounter with 44x stats");
            REQUIRE((g.hero.floor == 50 && g.visual.enemy_first && g.visual.battle_enemy.stats.hp == 44000 &&
                     g.visual.battle_enemy.stats.attack == 27500 &&
                     g.visual.battle_enemy.stats.defense == 5500));
        }
    }
    UNSCOPED_INFO("Forced Zeno fight applies its opening strike, reward and next-cycle scene");
    REQUIRE((forced && !g.busy() && g.hero.floor == 1 && g.hero.later_cycle && g.hero.hp == 72500 &&
             g.hero.gold == 500));
}

TEST_CASE("49F seal and 50F wing encounters retain Zeno variants", "[scenes]") {
    auto g = room(49);
    g.hero.cycle_factor_minus_one = 43;
    g.hero.later_cycle = 1;
    g.hero.hp = 100000;
    g.hero.attack = 100000;
    g.hero.defense = 0;
    g.tile_at(49, 5, 2) = Zeno;
    for (int x : {4, 6})
        for (int y : {1, 3})
            g.tile_at(49, x, y) = Sorcerer;
    g.check_guards();
    g.finish_commands(true);
    UNSCOPED_INFO("49F seal puzzle divides the shared Zeno row by ten");
    REQUIRE((g.hero.zeno_sealed && g.monsters[ZenoRow].hp == 800 && g.monsters[ZenoRow].attack == 500 &&
             g.monsters[ZenoRow].defense == 100));
    g.check_guards();
    g.finish_commands(true);
    UNSCOPED_INFO("Repeated seal checks do not divide Zeno twice");
    REQUIRE(g.monsters[ZenoRow].hp == 800);
    g.hero.floor = 24;
    g.check_floor();
    g.finish_commands(true);
    UNSCOPED_INFO("Later-cycle gate restores the original row and leaves Zeno awaiting contact");
    REQUIRE((!g.busy() && g.hero.floor == 50 && !g.hero.zeno_sealed && g.monsters[ZenoRow].hp == 8000 &&
             g.tile(50, cell(5, 4)) == Zeno));
    g.hero.floor = 49;
    g.check_guards();
    g.finish_commands(true);
    g.hero.x = g.hero.y = 5;
    g.inventory(Item::AscentWing) = 1;
    UNSCOPED_INFO("A wing returns to 50F after re-sealing on 49F");
    REQUIRE(g.use(Item::AscentWing));
    g.finish_commands(true);
    g.move(Direction::Up);
    UNSCOPED_INFO("Later 50F contact respects the re-sealed shared row");
    REQUIRE((g.visual.battle && g.visual.battle_enemy.stats.hp == 35200 &&
             g.visual.battle_enemy.stats.attack == 22000 && g.visual.battle_enemy.stats.defense == 4400));
    g.finish_commands(true);
    UNSCOPED_INFO("Re-sealed Zeno victory completes its scene and starts another backside cycle");
    REQUIRE((!g.busy() && g.hero.floor == 1 && g.hero.later_cycle));
}

TEST_CASE("Eight save slots share original paths and keep independent backups", "[saves]") {
    const auto directory =
        std::filesystem::path(TSW_TEST_TEMP) /
        ("tos-baseline-slots-" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    auto slots = inspect_save_slots(directory);
    UNSCOPED_INFO("An absent save directory has eight empty slots without creating files");
    REQUIRE((std::all_of(slots.begin(), slots.end(),
                         [](const auto& slot) { return slot.state == SaveSlotState::Empty; }) &&
             !std::filesystem::exists(directory)));
    for (int number = 1; number <= ManualSaveSlotCount; ++number) {
        auto g = room(number);
        g.hero.hp = 1000 + number;
        g.save(save_slot_path(directory, number));
    }
    slots = inspect_save_slots(directory);
    for (int number = 1; number <= ManualSaveSlotCount; ++number) {
        Game restored;
        restored.load(save_slot_path(directory, number));
        UNSCOPED_INFO("All eight slots contain independent, validated saves");
        REQUIRE((slots[number - 1].state == SaveSlotState::Ready && slots[number - 1].floor == number &&
                 restored.hero.hp == 1000 + number));
    }
    for (int number : {0, ManualSaveSlotCount + 1}) {
        CAPTURE(number);
        UNSCOPED_INFO("Save paths reject numbers outside the eight manual slots");
        REQUIRE_THROWS_AS(save_slot_path(directory, number), std::out_of_range);
    }
    auto g = room(20);
    g.hero.hp = 4321;
    g.save(save_slot_path(directory, 8));
    auto backup = save_slot_path(directory, 8);
    backup += ".bak";
    Game restored;
    restored.load(backup);
    UNSCOPED_INFO("Replacing an occupied slot keeps that slot's previous save as a backup");
    REQUIRE((restored.hero.floor == 8 && restored.hero.hp == 1008));
    g.save(directory / "quick.save");
    g.hero.hp = 5432;
    g.save(directory / "save0.dat", SaveKind::Checkpoint);
    restored.load(save_slot_path(directory, 8));
    UNSCOPED_INFO("Quick save and Fairy checkpoint do not overwrite manual slots");
    REQUIRE(restored.hero.hp == 4321);
    {
        std::ofstream corrupt(save_slot_path(directory, 4), std::ios::binary | std::ios::trunc);
        corrupt << "invalid";
    }
    slots = inspect_save_slots(directory);
    UNSCOPED_INFO("Corrupt slot summaries show the error without hiding valid neighboring saves");
    REQUIRE((slots[3].state == SaveSlotState::Invalid && !slots[3].error.empty() &&
             slots[4].state == SaveSlotState::Ready));
    UNSCOPED_INFO("Loading a corrupt numbered slot leaves the live game intact");
    REQUIRE_THROWS_AS(restored.load(save_slot_path(directory, 4)), std::runtime_error);
    REQUIRE(restored.hero.floor == 20);
    REQUIRE(restored.hero.hp == 4321);
    for (int variant = 0; variant < 3; ++variant) {
        auto fight = room(50);
        fight.hero.highest_floor = 50;
        fight.hero.hp = 10000000;
        fight.hero.attack = 1000000;
        fight.hero.defense = 0;
        fight.hero.cycle_factor_minus_one = 43;
        fight.hero.later_cycle = variant != 0;
        fight.hero.zeno_sealed = variant == 2;
        fight.monsters[ZenoRow] = variant == 0   ? Monster{1000, 625, 125, 500}
                                  : variant == 1 ? Monster{8000, 5000, 1000, 500}
                                                 : Monster{800, 500, 100, 500};
        fight.tile(50, cell(5, 4)) = Zeno;
        const auto path = save_slot_path(directory, variant + 1);
        fight.save(path);
        fight.load(path);
        fight.save(path);
        fight.load(path);
        const int row_hp = variant == 2 ? 800 * BacksideFactor : 8000;
        UNSCOPED_INFO("Repeated slot restores rebuild the shared Zeno row exactly as original loading does");
        REQUIRE((fight.monsters[ZenoRow].hp == row_hp && fight.hero.later_cycle == int(variant != 0) &&
                 fight.hero.zeno_sealed == (variant == 2)));
        slots = inspect_save_slots(directory);
        UNSCOPED_INFO("Slot summaries distinguish the second and later backside cycles");
        REQUIRE((slots[variant].backside && slots[variant].later_cycle == (variant != 0)));
        fight.move(Direction::Up);
        const Monster expected = variant == 0   ? Monster{44000, 27500, 5500, 500}
                                 : variant == 1 ? Monster{352000, 220000, 44000, 500}
                                                : Monster{1548800, 968000, 193600, 500};
        const auto& enemy = fight.visual.battle_enemy.stats;
        UNSCOPED_INFO("Restored 50F contact uses the correct cycle-specific Zeno combat stats");
        REQUIRE((fight.visual.battle && !fight.visual.enemy_first && enemy.hp == expected.hp &&
                 enemy.attack == expected.attack && enemy.defense == expected.defense));
        const auto damage = fight.forecast(Zeno).damage;
        fight.finish_commands(true);
        UNSCOPED_INFO(
            "Each restored Zeno variant plays its strikes, reward and next-cycle scene to completion");
        REQUIRE((!fight.busy() && fight.hero.floor == 1 && fight.hero.later_cycle &&
                 fight.hero.hp == 10000000 - damage && fight.hero.gold == 500));
    }
    const auto shared = directory / "game" / "Savedat";
    const auto slot = shared / "save1.dat";
    auto old = room(31);
    old.hero.hp = 12345;
    old.save(slot);
    UNSCOPED_INFO("Manual slot names match the original save1.dat through save8.dat");
    REQUIRE((save_slot_path(shared, 1) == slot && save_slot_path(shared, 8) == shared / "save8.dat"));
    slots = inspect_save_slots(shared);
    UNSCOPED_INFO("An existing original record is an ordinary save slot");
    REQUIRE((slots[0].state == SaveSlotState::Ready && slots[0].floor == 31 && slots[0].hp == 12345));
    restored.load(save_slot_path(shared, 1));
    UNSCOPED_INFO("Reading a slot uses the original file directly");
    REQUIRE((restored.hero.floor == 31 && restored.hero.hp == 12345));
    restored.hero.hp = 54321;
    restored.save(save_slot_path(shared, 1));
    old.load(slot);
    UNSCOPED_INFO("Writing the slot updates the same file that the original executable reads");
    REQUIRE((old.hero.hp == 54321 && inspect_save_slots(shared)[0].hp == 54321));
    old.load(shared / "save1.dat.bak");
    UNSCOPED_INFO("Replacing a shared slot retains its previous bytes in the backup");
    REQUIRE(old.hero.hp == 12345);
    old.save(shared / "slot-2.save");
    old.save(shared / "Savedat" / "save2.dat");
    old.save(directory / "AppData" / "slot-2.save");
    UNSCOPED_INFO("Slot inspection does not search old names, nested directories or another save folder");
    REQUIRE((inspect_save_slots(shared)[1].state == SaveSlotState::Empty &&
             !std::filesystem::exists(save_slot_path(shared, 2))));
    old.hero.hp = 33333;
    old.save(save_slot_path(shared, 2));
    UNSCOPED_INFO("Only the selected directory's save2.dat supplies slot 2");
    REQUIRE(inspect_save_slots(shared)[1].hp == 33333);
    std::filesystem::remove_all(directory);
}

TEST_CASE("Queued conversations include their equipment clues and Zeno explanation",
          "[npcs][scenes][dialogue]") {
    SECTION("The 2F thief names the first sword and shield floors") {
        auto g = room(2);
        g.hero.x = 0;
        g.tile_at(2, 0, 4) = Thief;
        REQUIRE(g.move(Direction::Up));
        g.finish_commands();
        REQUIRE(g.dialogue);
        REQUIRE(g.dialogue->continuation == static_cast<ContinuationStage>(15));
        REQUIRE(g.dialogue->text.starts_with(Game::original_dialogue(static_cast<DialogueId>(4))));
        REQUIRE(g.dialogue->text.find("sword on the 5th floor and a shield on the 9th") != std::string::npos);
        REQUIRE(g.continue_dialogue());
        g.finish_commands();
        REQUIRE(g.hero.dialogue_seen[15] == 1);
        REQUIRE(!g.busy());
    }

    SECTION("The thief after the 10F boss names the next equipment floors") {
        auto g = room(10);
        g.hero.y = 9;
        g.hero.dialogue_seen[26] = 1;
        g.tile_at(10, 5, 8) = SpecialRoad;
        REQUIRE(g.move(Direction::Up));
        g.finish_commands();
        REQUIRE(g.dialogue);
        REQUIRE(g.dialogue->continuation == static_cast<ContinuationStage>(27));
        REQUIRE(g.dialogue->text.starts_with(Game::original_dialogue(static_cast<DialogueId>(16))));
        REQUIRE(g.dialogue->text.find("shield on the 11th floor and a sword on the 17th") !=
                std::string::npos);
        REQUIRE(g.continue_dialogue());
        g.finish_commands();
        REQUIRE(g.hero.dialogue_seen[27] == 1);
        REQUIRE(!g.busy());
    }

    SECTION("The 24F gate scene explains Zeno's false information and traps") {
        auto g = room(24);
        g.hero.y = 1;
        g.tile_at(24, 5, 0) = SpecialRoad;
        REQUIRE(g.move(Direction::Up));
        g.finish_commands();
        for (int speech = 48; speech < 55; ++speech) {
            REQUIRE(g.dialogue);
            REQUIRE(g.dialogue->continuation == static_cast<ContinuationStage>(speech + 10));
            REQUIRE(g.continue_dialogue());
            g.finish_commands();
        }
        REQUIRE(g.dialogue);
        REQUIRE(g.dialogue->continuation == static_cast<ContinuationStage>(65));
        REQUIRE(g.dialogue->text.starts_with(Game::original_dialogue(static_cast<DialogueId>(54))));
        REQUIRE(g.dialogue->text.find("false information, set various traps in this tower") !=
                std::string::npos);
        REQUIRE(g.dialogue->text.find("as arranged beforehand") != std::string::npos);
        REQUIRE(g.continue_dialogue());
        REQUIRE(g.hero.dialogue_seen[65] == 1);
        g.finish_commands(true);
        REQUIRE(!g.busy());
    }
}

TEST_CASE("Pickup status matches the recovered final display", "[status][items]") {
    // Expected strings were observed from the compiled recovery after event playback.
    const std::pair<Tile, std::string_view> cases[]{
        {YellowKey, "You've found a key."},
        {RedKey, "You've found a red key."},
        {BlueKey, "You've found a blue key."},
        {RedPotion, "Got a red elixir. Your vital power was 50 points up!"},
        {BluePotion, "Got a blue elixir. Your vital power was 200 points up!"},
        {RedGem, "Got a red crystal. Your offensive power was 1 point up!"},
        {BlueGem, "Got a blue crystal. Your defensive power was 1 point up!"},
        {WisdomOrb, "You've found the orb of wisdom."},
        {FlightOrb, "You've found the orb of flying."},
        {Cross, "Got a cross! Your offensive power against Vampires and Zombies has doubled."},
        {Elixir, "You recieved The Magic Elixir."},
        {Mattock, "You recieved The Magic Mattock."},
        {Bomb, "You recieved The destructible Ball!"},
        {WarpStaff, "You recieved The Warp Staff!"},
        {AscentWing, "You recieved wings to fly up!"},
        {DescentWing, "You recieved wings to fly down!"},
        {DragonSlayer, "You recieved The Dragon Slayer! Your attack power against the Dragon has doubled!"},
        {SnowCrystal, "Got the snow crystal!"},
        {MagicKey, "Got the magic key!"},
        {SuperMattock, "Got The Super Magic Mattock!"},
        {LuckyGold, "Got the Lucky Gold! You now get twice the normal amount of gold."},
        {IronSword, "Got an Iron Sword! Your offensive power was 10 points up!"},
        {SilverSword, "Got a Silver Sword! Your offensive power was 20 points up!"},
        {KnightSword, "Got a Sword of Knight! Your offensive power was 40 points up!"},
        {HolySword, "Got a Holy Sword! Your offensive power was 50 points up!"},
        {SacredSword, "Got a Sacred Sword! Your offensive power was 100 points up!"},
        {IronShield, "Got an Iron Shield! Your defensive power was 10 points up!"},
        {SilverShield, "Got a Silver Shield! Your defensive power was 20 points up!"},
        {KnightShield, "Got a Shield of Knight! Your defensive power was 40 points up!"},
        {HolyShield, "Got a Holy Shield! Your defensive power was 50 points up!"},
        {SacredShield, "Got a Sacred Shield! Your defensive power was 100 points up!"},
    };
    for (const auto& [target, expected] : cases) {
        CAPTURE(target);
        auto g = room();
        g.tile_at(1, 4, 5) = YellowDoor;
        REQUIRE(g.move(Direction::Left));
        g.finish_commands();
        REQUIRE(g.status == "You don't have the key.");
        g.tile_at(1, 5, 4) = target;
        REQUIRE(g.move(Direction::Up));
        // Movement refreshes first; the queued acquisition must publish afterward.
        REQUIRE(g.status.empty());
        g.finish_commands();
        REQUIRE(g.status == expected);
    }
}

TEST_CASE("Pickup messages report scaled gains and singular gems", "[status][items]") {
    auto g = room(12);
    g.hero.cycle_factor_minus_one = BacksideFactor - 1;
    g.tile_at(12, 5, 4) = RedPotion;
    REQUIRE(g.move(Direction::Up));
    g.finish_commands();
    REQUIRE(g.status == "Got a red elixir. Your vital power was 4400 points up!");
    g.tile_at(12, 4, 4) = BlueGem;
    REQUIRE(g.move(Direction::Left));
    g.finish_commands();
    REQUIRE(g.status == "Got a blue crystal. Your defensive power was 88 points up!");
}

TEST_CASE("Consumable results publish at their original command boundary", "[status][items]") {
    auto g = room();
    const auto previous = g.status;
    g.inventory(Item::Elixir) = 1;
    REQUIRE(g.use(Item::Elixir));
    REQUIRE(g.status == previous);
    g.finish_commands();
    REQUIRE(g.status == "You used the Magic Elixir. Your vital power is now 1500 points up!");
    g.inventory(Item::Bomb) = g.inventory(Item::LuckyGold) = 1;
    g.tile_at(1, 5, 4) = GreenSlime;
    g.tile_at(1, 6, 5) = RedSlime;
    REQUIRE(g.use(Item::Bomb));
    g.finish_commands();
    REQUIRE(g.status == "You used The destructible Ball! Enemies on all sides died!Recieved 3 Gold.");
    REQUIRE(g.hero.gold == 3);
    g.inventory(Item::Bomb) = 1;
    REQUIRE(g.use(Item::Bomb));
    g.finish_commands();
    REQUIRE(g.status == "You used The destructible Ball! Enemies on all sides died!Recieved 0 Gold.");
    g.inventory(Item::SnowCrystal) = 1;
    g.tile_at(1, 5, 4) = Lava;
    REQUIRE(g.use(Item::SnowCrystal));
    REQUIRE(g.status.find("Recieved 0 Gold.") != std::string::npos);
    REQUIRE(g.run_one()); // Snow Crystal publishes before its queued road animation.
    REQUIRE(g.status == "You've used the snow crystal!The lava cooled and turned to stone.");
    g.finish_commands();
    REQUIRE(g.use(Item::SnowCrystal));
    g.finish_commands();
    REQUIRE(g.status == Game::original_dialogue(DialogueId::SnowCrystalUsed));
}

TEST_CASE("Nearby status follows ordered classification and clears on plain road", "[status][movement]") {
    const std::pair<Tile, msg::Code> cases[]{
        {StairsUp, msg::Stairs}, {StairsDown, msg::Stairs}, {Lava, msg::Lava},          {Altar, msg::Altar},
        {AltarSide, msg::Altar}, {Merchant, msg::Merchant}, {Merchant2, msg::Merchant}, {Thief, msg::Thief},
        {Thief2, msg::Thief},    {Fairy, msg::Fairy},       {Fairy2, msg::Fairy},       {OldMan, msg::OldMan},
        {OldMan2, msg::OldMan}};
    for (const auto& [target, code] : cases) {
        CAPTURE(target);
        auto g = room();
        g.tile_at(1, 5, 3) = target;
        REQUIRE(g.move(Direction::Up));
        REQUIRE(g.status == Game::original_dialogue(DialogueId::StatusOffset + code));
        REQUIRE(g.commands.empty());
        REQUIRE(g.move(Direction::Down));
        REQUIRE(g.status.empty());
    }
    auto g = room();
    g.tile_at(1, 5, 3) = StairsUp;
    g.tile_at(1, 4, 4) = Merchant;
    g.tile_at(1, 6, 4) = Altar;
    // The last recognized neighbor wins; an ordinary southern tile does not erase it.
    REQUIRE(g.move(Direction::Up));
    REQUIRE(g.status == "You see an altar.");
    REQUIRE(g.hero.highest_floor_stair_kind == StairKind::Up);
    REQUIRE_FALSE(g.can_open_flight());
}

TEST_CASE("Hazards suppress immediate nearby status even with Sacred Shield", "[status][hazards]") {
    for (const Tile magician : std::array{MagicianA, MagicianA2, MagicianB, MagicianB2})
        for (const bool shield : {false, true}) {
            CAPTURE(magician, shield);
            auto g = room();
            g.hero.equipment_found[SacredShieldFlag] = shield;
            g.tile_at(1, 5, 3) = magician;
            g.tile_at(1, 6, 4) = Altar;
            const auto previous = g.status;
            REQUIRE(g.move(Direction::Up));
            REQUIRE(g.status == previous);
            g.finish_commands();
            if (shield)
                REQUIRE(g.status == previous);
            else
                REQUIRE(g.status ==
                        Game::original_dialogue(DialogueId::StatusOffset +
                                                (magician < MagicianB ? msg::MagicianA : msg::MagicianB)));
        }
    auto g = room();
    g.hero.equipment_found[SacredShieldFlag] = 0;
    g.tile_at(1, 4, 4) = g.tile_at(1, 6, 4) = Sorcerer;
    const auto previous = g.status;
    REQUIRE(g.move(Direction::Up));
    REQUIRE(g.status == previous);
    g.finish_commands();
    REQUIRE(g.status == Game::original_dialogue(DialogueId::StatusOffset + msg::Pincer));
}

TEST_CASE("Zero status operand republishes classification and migration retains prepared text",
          "[status][runtime]") {
    auto g = room();
    g.tile_at(1, 5, 4) = RedGem;
    REQUIRE(g.move(Direction::Up));
    auto pending = GameState::capture(g).restore();
    REQUIRE(pending.status.empty());
    g.finish_commands();
    pending.finish_commands();
    REQUIRE(g.status == "Got a red crystal. Your offensive power was 1 point up!");
    REQUIRE(pending.status == g.status);
    REQUIRE(localized_status(Language::Japanese, pending) == localized_status(Language::Japanese, g));
    pending.status = "stale display";
    pending.push(Op::Message);
    pending.finish_commands();
    REQUIRE(pending.status == g.status);
    pending.push(Op::Message, msg::MissingKey);
    pending.finish_commands();
    pending.status = "stale display";
    pending.push(Op::Message);
    pending.finish_commands();
    REQUIRE(pending.status == "You don't have the key.");
    auto invalid = GameState::capture(pending);
    invalid.prepared_status.text = DialogueId::Count;
    REQUIRE_THROWS(invalid.restore());
}
