#include "baseline/game.hpp"
#include "baseline/save_slots.hpp"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace baseline;
int checks = 0;
void require(bool condition, const char* explanation) {
    ++checks;
    if (!condition)
        throw std::runtime_error(explanation);
}
Game room(int floor = 1) {
    Game game;
    game.hero.floor = floor;
    game.hero.x = game.hero.y = 5;
    game.floors[floor].tiles.fill(Road);
    return game;
}
int main() try {
    {
        auto g = room();
        g.tile(1, cell(5, 4)) = GreenSlime;
        g.move(Direction::Up);
        g.finish_commands();
        require(g.visual.last_defeated && g.visual.last_defeated->row == 0 &&
                    g.visual.last_defeated->stats.hp == 35 && g.visual.last_defeated->damage == 0,
                "Successful battle retains the defeated enemy's encounter statistics");
        g.monsters[0].hp = 999;
        g.move(Direction::Left);
        g.finish_commands();
        require(g.visual.last_defeated->stats.hp == 35,
                "Walking and later shared monster changes preserve the previous battle record");
        g.hero.hp = 1;
        g.hero.attack = 10;
        g.hero.defense = 0;
        g.tile(1, cell(4, 3)) = RedSlime;
        g.move(Direction::Up);
        g.finish_commands();
        require(g.visual.dead && g.visual.last_defeated->row == 0,
                "A fatal encounter does not replace the last defeated enemy");
        g.new_game();
        require(!g.visual.last_defeated, "A new game clears the defeated enemy panel");
    }
    {
        auto g = room();
        g.tile(1, cell(5, 4)) = YellowDoor;
        g.hero.yellow_keys = 1;
        g.move(Direction::Up);
        g.finish_commands();
        require(g.hero.y == 5 && g.tile(1, cell(5, 4)) == Road && g.hero.yellow_keys == 0,
                "Door opens without movement");
        g.move(Direction::Up);
        require(g.hero.y == 4, "Second step enters open door");
    }
    for (int scale : {0, 43}) {
        auto g = room(12);
        g.hero.cycle_factor_minus_one = scale;
        g.tile(12, cell(5, 4)) = RedPotion;
        g.move(Direction::Up);
        g.finish_commands();
        require(g.hero.hp == 1000 + 100 * (scale + 1), "Potion scaling");
        g.tile(12, cell(4, 4)) = RedGem;
        g.move(Direction::Left);
        g.finish_commands();
        require(g.hero.attack == 100 + 2 * (scale + 1), "Gem scaling");
    }
    {
        auto g = room();
        g.hero.equipment_found[9] = 0;
        g.hero.hp = 1;
        g.tile(1, cell(4, 4)) = g.tile(1, cell(6, 4)) = Sorcerer;
        g.move(Direction::Up);
        g.commands.insert(g.commands.begin(), {Op::Reward, 100, 0}); // Executes after the pending damage.
        g.finish_commands();
        require(g.hero.hp == 0 && g.visual.dead && g.hero.gold == 0, "Pincer death cancels later rewards");
    }
    {
        auto g = room(47);
        g.tile(47, cell(5, 3)) = MagicianA;
        g.move(Direction::Up);
        g.finish_commands();
        require(g.tile(47, cell(5, 2)) == MagicianA && g.hero.hp == 1000,
                "Shield protects; magician still retreats");
    }
    {
        auto g = room();
        g.inventory(Item::Bomb) = g.inventory(Item::LuckyGold) = 1;
        g.tile(1, cell(5, 4)) = GreenSlime;
        g.use(Item::Bomb);
        g.finish_commands();
        require(g.hero.gold == g.monsters[0].gold && g.tile(1, cell(5, 4)) == Road, "Bomb gold is raw");
        g.inventory(Item::Mattock) = 1;
        g.use(Item::Mattock);
        g.finish_commands();
        require(g.inventory(Item::Mattock) == 0, "Empty mattock consumed");
        g.inventory(Item::WarpStaff) = 1;
        g.tile(1, 60) = Wall;
        g.use(Item::WarpStaff);
        require(g.inventory(Item::WarpStaff) == 0, "Blocked warp consumed");
    }
    {
        auto g = room(43);
        g.tile(43, cell(5, 4)) = StairsUp;
        g.move(Direction::Up);
        g.finish_commands();
        require(g.hero.floor == 45 && g.hero.highest_floor == 45, "Stairs skip 44");
        g = room(43);
        g.floors[44].tiles.fill(Road);
        g.inventory(Item::AscentWing) = 1;
        g.use(Item::AscentWing);
        g.finish_commands();
        require(g.hero.floor == 44 && g.hero.highest_floor == 1,
                "Wing includes 44 without changing stair ceiling");
    }
    {
        auto g = room(41);
        g.hero.dialogue_seen[51] = 1;
        g.tile(41, cell(5, 4)) = StairsUp;
        g.tile_at(35, 4, 9) = Thief;
        g.move(Direction::Up);
        g.finish_commands(true);
        require(g.hero.floor == 42 && g.tile_at(35, 4, 9) == Thief,
                "42F arrival uses the dialogue continuation flag alias");
        g = room(41);
        g.tile(41, cell(5, 4)) = StairsUp;
        g.tile_at(35, 4, 9) = Thief;
        g.move(Direction::Up);
        g.finish_commands(true);
        require(g.hero.dialogue_seen[51] && g.tile_at(35, 4, 9) == Road,
                "First 42F arrival runs the original scene");
    }
    {
        auto g = room();
        g.hero.attack = 100;
        g.hero.defense = 0;
        g.hero.hp = 1000;
        g.hero.equipment_found[9] = 0;
        g.monsters[0] = {250, 30, 10, 7};
        g.tile(1, cell(5, 4)) = GreenSlime;
        require(g.forecast(GreenSlime).damage == 60, "Player-first formula");
        g.move(Direction::Up);
        g.finish_commands();
        require(g.hero.hp == 940 && g.hero.gold == 7 && g.hero.y == 4, "Combat playback result");
        g = room();
        g.hero.attack = 50;
        g.monsters[12] = {300, 20, 60, 1};
        g.inventory(Item::Cross) = 1;
        require(!g.forecast(85).penetrates, "Base ATK guard before Cross");
        g.hero.attack = 100;
        require(g.forecast(85, true).damage >= g.forecast(85).damage, "Forced combat ignores Cross");
    }
    {
        auto g = room();
        g.hero.hp = 100000;
        g.hero.attack = 1;
        g.monsters[0] = {10000, 0, 0, 1};
        g.tile(1, cell(5, 4)) = GreenSlime;
        g.move(Direction::Up);
        std::size_t maximum = 0;
        for (int n = 0; n < 200000 && g.run_one(); ++n)
            maximum = std::max(maximum, g.commands.size());
        require(maximum < 20 && g.hero.gold == 1, "Long fights keep a bounded command queue");
    }
    {
        auto g = room();
        g.hero.gold = 100;
        g.tile(1, cell(5, 4)) = Altar;
        g.move(Direction::Up);
        g.choose(1);
        g.finish_commands();
        require(g.hero.attack == 102 && g.hero.gold == 80 && g.hero.altar_purchases == 1,
                "Altar first transaction");
        g.hero.floor = 2;
        g.hero.x = 2;
        g.hero.y = 7;
        g.contact_index = 68;
        g.tile(2, 68) = Thief;
        g.contact();
        g.finish_commands(true);
        require(g.hero.dialogue_seen[14] == 1, "Thief continuation flag");
    }
    {
        auto g = room(2);
        g.tile(2, cell(5, 4)) = OldMan;
        g.move(Direction::Up);
        g.finish_commands(true);
        require(g.hero.attack == 103 && g.hero.defense == 103 && g.hero.dialogue_seen[18] == 1,
                "Old-man gift shares original continuation slot 18");
        require(g.hero.old_man_heard[0] == 1, "First hearing without Wisdom is retained");
        g.inventory(Item::WisdomOrb) = 1;
        g.move(Direction::Up);
        g.finish_commands(true);
        require(g.hero.attack == 103 && g.hero.old_man_heard[0] == 1,
                "Repeated hearing does not grant or record the gift again");
    }
    {
        auto g = room(10);
        g.tile(10, cell(5, 4)) = Fairy;
        g.hero.music_track = 0;
        g.move(Direction::Up);
        require(g.checkpoint_requested && g.busy(), "Fairy requests a checkpoint while her scene is pending");
        require(g.hero.fairy_score == 415 && g.hero.fairy_rank == 1 && g.hero.music_track == 0,
                "Fairy score and default rank retain disabled music");
        g.finish_commands(true);
        require(!g.busy() && g.tile(10, 27) == Road, "Fairy checkpoint becomes saveable after her scene");
        const auto path = std::filesystem::temp_directory_path() / "tos-baseline-fairy-test.save";
        g.save(path);
        Game restored;
        restored.load(path);
        require(restored.hero.fairy_score == 415 && restored.hero.fairy_visits == 1 &&
                    restored.tile(10, 27) == Road,
                "Fairy checkpoint restores completed gameplay state");
        std::filesystem::remove(path);
    }
    {
        auto g = room();
        g.hero.gold = 999;
        g.hero.equipment_found[1] = 1;
        g.inventory(Item::Bomb) = 1;
        g.push(Op::Callback, Callback::Capture);
        g.finish_commands(true);
        require(g.hero.hp == 400 && g.hero.floor == 2 && g.hero.highest_floor == 2 &&
                    g.hero.equipment_found[1] && g.inventory(Item::Bomb),
                "First-cycle capture preserves lower acquisition flags and specials");
        g.hero.cycle_factor_minus_one = 43;
        g.hero.hp = 321;
        g.push(Op::Callback, Callback::Capture);
        g.finish_commands(true);
        require(g.hero.hp == 321 && !g.inventory(Item::Bomb),
                "Backside capture preserves stats and clears specials");
    }
    {
        auto g = room(49);
        g.hero.zeno_sealed = true;
        g.monsters[15] = {800, 500, 100, 500};
        const auto path = std::filesystem::temp_directory_path() / "tos-baseline-test-save.bin";
        g.save(path);
        Game restored;
        restored.load(path);
        require(restored.monsters[15].hp == 800 && restored.hero.zeno_sealed && restored.hero.floor == 49,
                "Original save reconstructs frontside sealed Zeno");
        require(std::filesystem::file_size(path) == FloorCount * (CellCount + 2) + 171 * 4,
                "New saves use the exact original record size without a monster table or extension");
        restored.save(path);
        restored.load(path);
        require(restored.monsters[15].hp == 800, "Repeated restore does not scale Zeno again");
        g.hero.equipment_found[0] = 2;
        bool invalid_flag = false;
        try {
            g.save(path);
        } catch (...) {
            invalid_flag = true;
        }
        require(invalid_flag, "Save rejects non-boolean equipment acquisition flags");
        restored.load(path);
        require(restored.monsters[15].hp == 800, "Rejected save leaves the previous file intact");
        {
            std::fstream corrupt(path, std::ios::in | std::ios::out | std::ios::binary);
            corrupt.seekp(FloorCount * (CellCount + 2)); // HP is covered by the original checksums.
            corrupt.put('X');
        }
        bool rejected = false;
        try {
            restored.load(path);
        } catch (...) {
            rejected = true;
        }
        require(rejected && restored.hero.floor == 49, "Malformed save rejected without changing live game");
        std::filesystem::remove(path);
        auto backup = path;
        backup += ".bak";
        std::filesystem::remove(backup);
    }
    {
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
        require(!g.visual.battle && !g.commands.empty(), "Frontside 50F Zeno starts the ending, not combat");
        g.finish_commands(true);
        require(!g.busy() && g.hero.floor == 1 && g.hero.cycle_factor_minus_one == 43 && !g.hero.later_cycle,
                "First ending starts the second cycle with the 44x backside factor");
        require(g.hero.hp == 81234 && g.hero.attack == 12345 && g.hero.defense == 6789 && g.hero.gold == 0 &&
                    !g.inventory(Item::Bomb) && !g.hero.equipment_found[0],
                "Second cycle carries stats and resets gold, items and acquisition flags");
        g.hero.gold = 99;
        g.hero.highest_floor = 50;
        g.inventory(Item::Bomb) = 1;
        g.hero.equipment_found[0] = 1;
        g.next_cycle();
        require(g.hero.later_cycle && g.hero.gold == 99 && g.hero.highest_floor == 50 &&
                    g.inventory(Item::Bomb) && g.hero.equipment_found[0],
                "Third and later cycles preserve gold, explored ceiling, items and acquisition flags");
    }
    {
        // Play the actual 24F gate sequence: it restores a seal, teleports to 50F and forces cycle-2 combat.
        auto g = room(24);
        g.hero.cycle_factor_minus_one = 43;
        g.hero.zeno_sealed = true;
        g.monsters[ZenoRow] = {800, 500, 100, 500};
        g.hero.hp = g.hero.attack = 100000;
        g.hero.defense = 0;
        g.check_floor();
        require(!g.hero.zeno_sealed && g.monsters[ZenoRow].hp == 1000 && g.monsters[ZenoRow].attack == 625 &&
                    g.monsters[ZenoRow].defense == 125,
                "Second-cycle gate removes the seal and installs the fixed Zeno row");
        bool forced = false;
        for (int n = 0; n < 10000; ++n) {
            if (g.dialogue)
                g.continue_dialogue();
            Command command;
            if (!g.run_one(&command))
                break;
            if (command.op == Op::Callback && command.a == int(Callback::ForcedBattle)) {
                forced = true;
                require(g.hero.floor == 50 && g.visual.enemy_first &&
                            g.visual.battle_enemy.stats.hp == 44000 &&
                            g.visual.battle_enemy.stats.attack == 27500 &&
                            g.visual.battle_enemy.stats.defense == 5500,
                        "Second-cycle gate plays an enemy-first 50F Zeno encounter with 44x stats");
            }
        }
        require(forced && !g.busy() && g.hero.floor == 1 && g.hero.later_cycle && g.hero.hp == 72500 &&
                    g.hero.gold == 500,
                "Forced Zeno fight applies its opening strike, reward and next-cycle scene");
    }
    {
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
        require(g.hero.zeno_sealed && g.monsters[ZenoRow].hp == 800 && g.monsters[ZenoRow].attack == 500 &&
                    g.monsters[ZenoRow].defense == 100,
                "49F seal puzzle divides the shared Zeno row by ten");
        g.check_guards();
        g.finish_commands(true);
        require(g.monsters[ZenoRow].hp == 800, "Repeated seal checks do not divide Zeno twice");
        g.hero.floor = 24;
        g.check_floor();
        g.finish_commands(true);
        require(!g.busy() && g.hero.floor == 50 && !g.hero.zeno_sealed && g.monsters[ZenoRow].hp == 8000 &&
                    g.tile(50, cell(5, 4)) == Zeno,
                "Later-cycle gate restores the original row and leaves Zeno awaiting contact");
        g.hero.floor = 49;
        g.check_guards();
        g.finish_commands(true);
        g.hero.x = g.hero.y = 5;
        g.inventory(Item::AscentWing) = 1;
        require(g.use(Item::AscentWing), "A wing returns to 50F after re-sealing on 49F");
        g.finish_commands(true);
        g.move(Direction::Up);
        require(g.visual.battle && g.visual.battle_enemy.stats.hp == 35200 &&
                    g.visual.battle_enemy.stats.attack == 22000 &&
                    g.visual.battle_enemy.stats.defense == 4400,
                "Later 50F contact respects the re-sealed shared row");
        g.finish_commands(true);
        require(!g.busy() && g.hero.floor == 1 && g.hero.later_cycle,
                "Re-sealed Zeno victory completes its scene and starts another backside cycle");
    }
    {
        const auto directory = std::filesystem::temp_directory_path() /
                               ("tos-baseline-slots-" +
                                std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
        auto slots = inspect_save_slots(directory);
        require(std::all_of(slots.begin(), slots.end(),
                            [](const auto& slot) { return slot.state == SaveSlotState::Empty; }) &&
                    !std::filesystem::exists(directory),
                "An absent save directory has eight empty slots without creating files");
        for (int number = 1; number <= ManualSaveSlotCount; ++number) {
            auto g = room(number);
            g.hero.hp = 1000 + number;
            g.save(save_slot_path(directory, number));
        }
        slots = inspect_save_slots(directory);
        for (int number = 1; number <= ManualSaveSlotCount; ++number) {
            Game restored;
            restored.load(save_slot_path(directory, number));
            require(slots[number - 1].state == SaveSlotState::Ready && slots[number - 1].floor == number &&
                        restored.hero.hp == 1000 + number,
                    "All eight slots contain independent, validated saves");
        }
        for (int number : {0, ManualSaveSlotCount + 1}) {
            bool rejected = false;
            try {
                save_slot_path(directory, number);
            } catch (const std::out_of_range&) {
                rejected = true;
            }
            require(rejected, "Save paths reject numbers outside the eight manual slots");
        }
        auto g = room(20);
        g.hero.hp = 4321;
        g.save(save_slot_path(directory, 8));
        auto backup = save_slot_path(directory, 8);
        backup += ".bak";
        Game restored;
        restored.load(backup);
        require(restored.hero.floor == 8 && restored.hero.hp == 1008,
                "Replacing an occupied slot keeps that slot's previous save as a backup");
        g.save(directory / "quick.save");
        g.hero.hp = 5432;
        g.save(directory / "fairy.save");
        restored.load(save_slot_path(directory, 8));
        require(restored.hero.hp == 4321, "Quick save and Fairy checkpoint do not overwrite manual slots");
        {
            std::ofstream corrupt(save_slot_path(directory, 4), std::ios::binary | std::ios::trunc);
            corrupt << "invalid";
        }
        slots = inspect_save_slots(directory);
        require(slots[3].state == SaveSlotState::Invalid && !slots[3].error.empty() &&
                    slots[4].state == SaveSlotState::Ready,
                "Corrupt slot summaries show the error without hiding valid neighboring saves");
        bool rejected = false;
        try {
            restored.load(save_slot_path(directory, 4));
        } catch (const std::exception&) {
            rejected = true;
        }
        require(rejected && restored.hero.floor == 20 && restored.hero.hp == 4321,
                "Loading a corrupt numbered slot leaves the live game intact");
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
            require(fight.monsters[ZenoRow].hp == row_hp && fight.hero.later_cycle == int(variant != 0) &&
                        fight.hero.zeno_sealed == (variant == 2),
                    "Repeated slot restores rebuild the shared Zeno row exactly as original loading does");
            slots = inspect_save_slots(directory);
            require(slots[variant].backside && slots[variant].later_cycle == (variant != 0),
                    "Slot summaries distinguish the second and later backside cycles");
            fight.move(Direction::Up);
            const Monster expected = variant == 0   ? Monster{44000, 27500, 5500, 500}
                                     : variant == 1 ? Monster{352000, 220000, 44000, 500}
                                                    : Monster{1548800, 968000, 193600, 500};
            const auto& enemy = fight.visual.battle_enemy.stats;
            require(fight.visual.battle && !fight.visual.enemy_first && enemy.hp == expected.hp &&
                        enemy.attack == expected.attack && enemy.defense == expected.defense,
                    "Restored 50F contact uses the correct cycle-specific Zeno combat stats");
            const auto damage = fight.forecast(Zeno).damage;
            fight.finish_commands(true);
            require(
                !fight.busy() && fight.hero.floor == 1 && fight.hero.later_cycle &&
                    fight.hero.hp == 10000000 - damage && fight.hero.gold == 500,
                "Each restored Zeno variant plays its strikes, reward and next-cycle scene to completion");
        }
        const auto installation = directory / "original";
        const auto local = directory / "local";
        const auto historical = installation / "Savedat" / "save1.dat";
        auto old = room(31);
        old.hero.hp = 12345;
        old.save(historical);
        const auto original_write_time = std::filesystem::last_write_time(historical);
        slots = inspect_save_slots(local, installation);
        require(slots[0].state == SaveSlotState::Ready && slots[0].original_location &&
                    slots[0].floor == 31 && slots[0].hp == 12345 && !std::filesystem::exists(local),
                "Original Savedat slots are discovered without creating a modern save directory");
        restored.load(load_slot_path(local, 1, installation));
        require(restored.hero.floor == 31 && restored.hero.hp == 12345,
                "The picker loads the discovered original record");
        restored.hero.hp = 54321;
        restored.save(save_slot_path(local, 1));
        slots = inspect_save_slots(local, installation);
        require(slots[0].hp == 54321 && !slots[0].original_location &&
                    load_slot_path(local, 1, installation) == save_slot_path(local, 1),
                "A replacement in the user save folder takes precedence over its historical slot");
        old.load(historical);
        require(old.hero.hp == 12345 && std::filesystem::last_write_time(historical) == original_write_time,
                "Loading and saving a discovered slot leave the original file unchanged");
        old.save(local / "save2.dat");
        require(inspect_save_slots(local)[1].state == SaveSlotState::Ready &&
                    load_slot_path(local, 2) == local / "save2.dat",
                "An original record can also be loaded from the chosen save directory");
        std::filesystem::remove_all(directory);
    }
    std::cout << checks << " core checks passed\n";
    return 0;
} catch (const std::exception& error) {
    std::cerr << "FAILED: " << error.what() << '\n';
    return 1;
}
