#include "tsw/game.hpp"
#include "tsw/replay.hpp"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace tsw;

namespace {
template <class Range> void array(const Range& range) {
    std::cout << '[';
    bool first = true;
    for (const auto& value : range) {
        if (!first)
            std::cout << ',';
        first = false;
        std::cout << +value;
    }
    std::cout << ']';
}

void snapshot(const Game& game, int selector) {
    const auto& h = game.hero;
    std::cout << "{\"hero\":";
    array(std::array<int, 17>{h.hp, h.attack, h.defense, h.gold, h.floor, h.highest_floor, h.x, h.y,
                              h.yellow_keys, h.red_keys, h.blue_keys, h.altar_purchases,
                              int(game.visual.battle), 0, h.fairy_visits, h.sword, h.shield});
    std::cout << ",\"items\":";
    array(h.items);
    std::cout << ",\"equipment\":";
    array(h.equipment_found);
    std::cout << ",\"flags\":";
    array(h.dialogue_seen);
    std::cout << ",\"hints\":";
    array(h.wisdom_hints);
    std::cout << ",\"merchant_used\":";
    array(h.merchant_used);
    std::cout << ",\"old_man_heard\":";
    array(h.old_man_heard);
    std::cout << ",\"flight\":[" << h.flight_direction << ',' << h.highest_floor_stair << ',' << int(h.facing)
              << ']';
    std::cout << ",\"selector\":" << selector;
    std::cout << ",\"music\":" << h.music_track;
    std::cout << ",\"fairy\":[" << h.fairy_score << ',' << h.fairy_rank << ',' << h.fairy_category << ','
              << game.checkpoint_requested << ']';
    std::cout << ",\"cycle\":[" << h.cycle_factor_minus_one << ',' << h.later_cycle << ',' << h.zeno_sealed
              << ']';
    std::cout << ",\"reward_flags\":[" << h.floor34_reward_created << ',' << h.floor35_reward_created << ','
              << h.floor40_reward_created << ',' << h.floor41_reward_created << ']';
    std::cout << ",\"maps\": [";
    for (int f = 0; f < FloorCount; ++f) {
        if (f)
            std::cout << ',';
        array(game.floors[f].tiles);
    }
    std::cout << "],\"monsters\":[";
    for (int i = 0; i < 33; ++i) {
        if (i)
            std::cout << ',';
        const auto& m = game.monsters[i];
        array(std::array<int, 4>{m.hp, m.attack, m.defense, m.gold});
    }
    std::cout << "],\"queue\":[";
    bool first = true;
    for (auto it = game.commands.rbegin(); it != game.commands.rend(); ++it) {
        if (!first)
            std::cout << ',';
        first = false;
        array(std::array<int, 3>{int(it->op), it->a, it->b});
    }
    std::cout << "],\"dialogue\":" << (game.dialogue ? game.dialogue->continuation : -1) << "}\n"
              << std::flush;
}

void set(Game& game, const std::string& name, int value) {
    auto& h = game.hero;
    if (name == "hp")
        h.hp = value;
    else if (name == "attack")
        h.attack = value;
    else if (name == "defense")
        h.defense = value;
    else if (name == "gold")
        h.gold = value;
    else if (name == "floor")
        h.floor = value;
    else if (name == "highest")
        h.highest_floor = value;
    else if (name == "x")
        h.x = value;
    else if (name == "y")
        h.y = value;
    else if (name == "yellow")
        h.yellow_keys = value;
    else if (name == "red")
        h.red_keys = value;
    else if (name == "blue")
        h.blue_keys = value;
    else if (name == "altar")
        h.altar_purchases = value;
    else if (name == "cycle")
        h.cycle_factor_minus_one = value;
    else if (name == "later")
        h.later_cycle = value;
    else if (name == "sealed")
        h.zeno_sealed = value;
    else if (name == "contact")
        game.contact_index = value;
    else if (name == "facing")
        h.facing = static_cast<Direction>(value);
    else if (name == "music")
        h.music_track = value;
    else if (name == "reward34")
        h.floor34_reward_created = value;
    else if (name == "reward35")
        h.floor35_reward_created = value;
    else if (name == "reward40")
        h.floor40_reward_created = value;
    else if (name == "reward41")
        h.floor41_reward_created = value;
    else if (name == "flight_direction")
        h.flight_direction = value;
    else if (name == "highest_stair")
        h.highest_floor_stair = value;
    else
        throw std::runtime_error("Unknown probe field: " + name);
}
} // namespace

int main() {
    Game game;
    int selector = -1;
    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream input(line);
        std::string command;
        input >> command;
        try {
            int a = 0, b = 0, c = 0, d = 0;
            if (command == "reset")
                game.new_game();
            else if (command == "original") {
                selector = -1;
                game.new_game();
                game.hero = Hero{};
                game.hero.hp = 400;
                game.hero.attack = game.hero.defense = 10;
                game.hero.highest_floor = game.hero.sword = game.hero.shield = game.hero.music_track = 0;
                game.hero.equipment_found.fill(0);
                game.hero.x = game.hero.y = 0;
                game.hero.facing = static_cast<Direction>(0);
            } else if (command == "set") {
                std::string name;
                input >> name >> a;
                set(game, name, a);
            } else if (command == "tile") {
                input >> a >> b >> c;
                game.tile(a, b) = static_cast<std::uint8_t>(c);
            } else if (command == "flag") {
                input >> a >> b;
                game.hero.dialogue_seen.at(a) = b;
            } else if (command == "hint") {
                input >> a >> b;
                game.hero.wisdom_hints.at(a) = b;
            } else if (command == "merchant") {
                input >> a >> b;
                game.hero.merchant_used.at(a) = b;
            } else if (command == "heard") {
                input >> a >> b;
                game.hero.old_man_heard.at(a) = b;
            } else if (command == "item") {
                input >> a >> b;
                game.hero.items.at(a) = b;
            } else if (command == "equipment") {
                input >> a >> b;
                game.hero.equipment_found.at(a) = b;
            } else if (command == "monster") {
                input >> a >> b >> c >> d;
                int gold;
                input >> gold;
                game.monsters.at(a) = {b, c, d, gold};
            } else if (command == "call") {
                std::string name;
                input >> name;
                if (name == "guards")
                    game.check_guards();
                else if (name == "floor")
                    game.check_floor();
                else if (name == "door")
                    game.check_door();
                else if (name == "contact")
                    game.contact();
                else if (name == "special")
                    game.special_road();
                else if (name == "capture")
                    game.capture();
                else if (name == "summon") {
                    game.push(Op::Callback, Callback::SummonGuards);
                    game.run_one();
                } else if (name == "cycle")
                    game.next_cycle();
                else if (name == "battle") {
                    input >> a;
                    game.battle(a != 0);
                } else
                    throw std::runtime_error("Unknown probe handler");
            } else if (command == "continue") {
                input >> a;
                game.dialogue = Dialogue{"", a, false, {}};
                game.continue_dialogue();
            } else if (command == "use") {
                input >> a;
                b = -1;
                input >> b;
                game.use(static_cast<Item>(a), b);
            } else if (command == "input") {
                std::string source;
                std::getline(input, source);
                const bool accepted = apply_input(game, selector, parse_input(source));
                std::cout << "{\"accepted\":" << accepted << "}\n" << std::flush;
            } else if (command == "flight_open") {
                std::cout << "{\"accepted\":" << game.open_flight() << "}\n" << std::flush;
            } else if (command == "flight_confirm") {
                input >> a;
                game.confirm_flight(a);
            } else if (command == "preview") {
                input >> a >> b;
                game.flight_preview(a, b);
            } else if (command == "choose") {
                input >> a;
                game.choose(a);
            } else if (command == "move") {
                input >> a;
                game.move(static_cast<Direction>(a));
            } else if (command == "step")
                game.run_one();
            else if (command == "drain") {
                input >> a;
                game.finish_commands(a != 0);
            } else if (command == "trace") {
                input >> a;
                std::cout << '[';
                bool first = true;
                Command executed;
                for (int n = 0; n < a && game.run_one(&executed); ++n) {
                    if (!first)
                        std::cout << ',';
                    first = false;
                    array(std::array<int, 3>{int(executed.op), executed.a, executed.b});
                    if (executed.op == Op::Defeat ||
                        (executed.op == Op::Callback && executed.a == int(Callback::CheckGuards)))
                        break;
                }
                std::cout << "]\n" << std::flush;
            } else if (command == "load" || command == "save" || command == "load-checkpoint" ||
                       command == "save-checkpoint") {
                std::string path;
                input >> std::quoted(path);
                if (command == "load" || command == "load-checkpoint")
                    game.load(path, command == "load-checkpoint" ? SaveKind::Checkpoint : SaveKind::Slot);
                else
                    game.save(path, command == "save-checkpoint" ? SaveKind::Checkpoint : SaveKind::Slot);
            } else if (command == "snapshot")
                snapshot(game, selector);
            else if (command == "forecast" || command == "orb_forecast") {
                input >> a >> b;
                const auto f = command == "orb_forecast" ? game.orb_forecast(a) : game.forecast(a, b != 0);
                std::cout << "{\"penetrates\":" << f.penetrates << ",\"damage\":" << f.damage
                          << ",\"hits\":" << f.hero_hits << "}\n"
                          << std::flush;
            } else if (!command.empty())
                throw std::runtime_error("Unknown probe command");
        } catch (const std::exception& e) {
            std::cout << "{\"error\":\"" << e.what() << "\"}\n" << std::flush;
            if (command != "load" && command != "load-checkpoint")
                return 1;
        }
    }
}
