// Read-only assertions over a normal replay, using the unchanged native engine.
#include "tsw/planner.hpp"
#include <ostream>
#include <stdexcept>
#include <utility>

namespace tsw::planner {
namespace {

void require(bool condition, const char* message) {
    if (!condition)
        throw std::runtime_error(message);
}

int octopus_parts(const Game& game) {
    int count = 0;
    for (const auto& floor : game.floors)
        for (int tile : floor.tiles)
            count += tile >= OctopusFirst && tile <= OctopusLast;
    return count;
}

} // namespace

void verify_challenge(std::span<const PlayerInput> actions, std::ostream& report) {
    require(!actions.empty() && actions.front().kind == InputKind::NewGame, "Must start new_game");
    Game game;
    int flight = -1, octopus_kills = 0, octopus_gold = 0, hp_purchases = 0;
    int dragon = 0, sword = 0, master = 0, first50 = 0, descent = 0, seal = 0, ascent = 0;
    int post_sword_fights = 0;
    for (int i = 0; i < int(actions.size()); ++i) {
        const auto& action = actions[i];
        require(i == 0 || action.kind != InputKind::NewGame, "Mid-route reset");
        require(action.kind != InputKind::Reload && action.kind != InputKind::Rankings,
                "External replay state is forbidden");
        const auto old = game.hero;
        const int before_parts = octopus_parts(game);
        const int before_dragon = game.tile_at(35, 5, 6);
        const int before_master = game.tile_at(25, 5, 5);
        const int before_sword = game.tile_at(13, 5, 4);
        apply_input(game, flight, action);
        settle_action(game);
        const auto& h = game.hero;
        require(!game.visual.dead && h.hp > 0, "Replay died");
        require(h.cycle_factor_minus_one == 0 && !h.later_cycle, "Left first cycle");
        if (h.altar_purchases > old.altar_purchases && action.value == 0)
            ++hp_purchases;
        const int after_parts = octopus_parts(game);
        if (i > 0 && after_parts < before_parts) {
            require(before_parts - after_parts == 1, "Mouth erased uncollected Octopus parts");
            const int reward = h.gold - old.gold;
            require(reward == (before_parts == 1 ? 100 : 50), "Incorrect Octopus reward");
            require(h.hp == old.hp, "Octopus fight took damage");
            ++octopus_kills;
            octopus_gold += reward;
            report << "Octopus input=" << i + 1 << " DEF=" << h.defense << " gold=" << reward
                   << " damage=0 remaining_parts=" << after_parts << '\n';
        }
        if (before_dragon == DragonHead && game.tile_at(35, 5, 6) != DragonHead && i > 0) {
            require(!game.inventory(Item::DragonSlayer), "Dragon Slayer was used");
            dragon = i + 1;
            report << "Dragon input=" << dragon << " hp=" << old.hp << "->" << h.hp << '\n';
        }
        if (before_sword == SacredSword && game.tile_at(13, 5, 4) != SacredSword && i > 0) {
            require(dragon > 0, "Sword before Dragon");
            sword = i + 1;
            report << "Sacred Sword input=" << sword << " attack=" << h.attack << '\n';
        }
        if (sword && !master && h.gold > old.gold && game.status.rfind("Defeated ", 0) == 0 &&
            action.kind == InputKind::Move)
            ++post_sword_fights;
        if (before_master == GreatMagicMaster && game.tile_at(25, 5, 5) != GreatMagicMaster && i > 0) {
            require(sword > dragon && post_sword_fights > 1, "No farming between Sword and Master");
            master = i + 1;
            report << "Master input=" << master << " hp=" << old.hp << "->" << h.hp << '\n';
        }
        if (!first50 && h.floor == 50) {
            first50 = i + 1;
            require(master > 0 && game.inventory(Item::AscentWing) && game.inventory(Item::DescentWing),
                    "Reached 50 without Master and both Wings");
        }
        if (old.floor == 50 && h.floor == 49) {
            require(action.kind == InputKind::UseItem && action.item == Item::DescentWing,
                    "Expected Descent Wing");
            descent = i + 1;
        }
        if (!old.zeno_sealed && h.zeno_sealed) {
            require(descent > first50 && first50 > master, "Seal must follow gate and descent");
            require(action.kind == InputKind::UseItem && action.item == Item::Bomb,
                    "Expected final guard Bomb");
            seal = i + 1;
        }
        if (old.floor == 49 && h.floor == 50) {
            require(seal > descent && action.kind == InputKind::UseItem && action.item == Item::AscentWing,
                    "Expected ascent after sealing");
            ascent = i + 1;
        }
    }
    require(octopus_kills == 9 && octopus_gold == 500, "Octopus incomplete");
    require(hp_purchases == 0, "Unexpected HP altar purchase");
    require(ascent > seal && seal > descent, "Finish sequence incomplete");
    require(game.hero.floor == 50 && game.hero.x == 4 && game.hero.y == 5 && game.hero.zeno_sealed,
            "Incorrect final position or seal");
    for (const auto [x, y] : {std::pair{4, 1}, {6, 1}, {4, 3}, {6, 3}})
        require(game.tile_at(49, x, y) == Sorcerer, "Diagonal guard missing");
    for (const auto [x, y] : {std::pair{5, 1}, {4, 2}, {6, 2}, {5, 3}})
        require(game.tile_at(49, x, y) == Road, "Cardinal guard remains");
    require(game.tile_at(50, 5, 4) == Zeno && !game.visual.hide_hero, "Ending was contacted");
    const auto& zeno = game.monsters[Game::monster_for_tile(Zeno)];
    const auto forecast = game.forecast(Zeno);
    require(zeno.hp == 800 && zeno.attack == 500 && zeno.defense == 100, "Wrong sealed Zeno stats");
    require(forecast.penetrates && game.hero.hp > forecast.damage, "Hypothetical Zeno fight is lethal");
    report << "PASS inputs=" << actions.size() << " first50=" << first50 << " descent=" << descent
           << " seal=" << seal << " ascent=" << ascent << " hp_altar_buys=" << hp_purchases
           << " post_sword_fights=" << post_sword_fights << '\n';
    report << "Zeno HP=" << zeno.hp << " ATK=" << zeno.attack << " DEF=" << zeno.defense
           << " hero_hits=" << forecast.hero_hits << " damage=" << forecast.damage
           << " margin=" << game.hero.hp - forecast.damage << '\n';
    report << gameplay_json(game) << '\n';
}
} // namespace tsw::planner
