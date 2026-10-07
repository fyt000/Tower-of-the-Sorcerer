#include "tsw/game.hpp"
#include <algorithm>
#include <stdexcept>

namespace tsw {
namespace {
// Original forced-combat operands retained for executable trace comparison.
constexpr int ForcedFatalOperand = 250;
constexpr int ForcedVictoryOperand = 193;
} // namespace

int Game::monster_for_tile(int t) {
    if (t >= GreenSlime && t <= Vampire + 1)
        return (t - GreenSlime) / 2;
    if (t >= OctopusFirst && t <= OctopusMouth + 1)
        return OctopusRow;
    if (t == DragonHead)
        return DragonRow;
    if (t >= GoldenKnight && t <= GateKeeperA + 1)
        return (t - Sorcerer) / 2;
    return -1;
}

int Game::attack_multiplier(int enemy, bool enemy_first) const {
    if (enemy_first)
        return 1;
    if ((enemy == ZombieRow || enemy == ZombieKnightRow || enemy == VampireRow) && inventory(Item::Cross))
        return 2;
    if (enemy == DragonRow && inventory(Item::DragonSlayer))
        return 2;
    return 1;
}

Forecast Game::forecast(int t, bool enemy_first) const {
    const int enemy = monster_for_tile(t);
    if (enemy < 0)
        return {};
    const auto& row = monsters[enemy];
    const int scale = hero.cycle_factor_minus_one + 1;
    // 0x44A480 tests unmodified ATK before applying Cross/Slayer bonuses.
    if (hero.attack <= std::int64_t(row.defense) * scale)
        return {};
    const std::int64_t hero_hit =
        std::int64_t(hero.attack) * attack_multiplier(enemy, enemy_first) - std::int64_t(row.defense) * scale;
    const std::int64_t hits = (std::int64_t(row.hp) * scale + hero_hit - 1) / hero_hit;
    const int enemy_hit = std::max(0, row.attack * scale - hero.defense);
    return {true, enemy_hit * (hits - (enemy_first ? 0 : 1)), hits, static_cast<int>(hero_hit), enemy_hit};
}

void Game::damage_pose(int index, int underlying) {
    const int color = DownDamageColor + (static_cast<int>(hero.facing) - 1) * FacingSpriteStride;
    push(Op::Wait, underlying < 0 ? tile(hero.floor, cell(hero.x, hero.y)) : underlying, color);
    push(Op::Overlay, index, color + 1);
}

void Game::battle(bool enemy_first) {
    const int t = tile(hero.floor, contact_index), enemy = monster_for_tile(t);
    if (enemy < 0)
        throw std::runtime_error("Battle target is not an attackable enemy");
    const Forecast expected = forecast(t, enemy_first);
    if (!expected.penetrates) {
        status = "Your attack cannot penetrate this enemy's defense.";
        return;
    }
    if (!enemy_first)
        walk_to_contact();
    visual.battle = true;
    visual.enemy_index = enemy;
    visual.enemy_first = enemy_first;
    visual.enemy_hp = monsters[enemy].hp * (hero.cycle_factor_minus_one + 1);
    const auto& row = monsters[enemy];
    const int scale = hero.cycle_factor_minus_one + 1;
    visual.battle_enemy = {
        enemy, t, {row.hp * scale, row.attack * scale, row.defense * scale, row.gold}, expected.damage};
    const bool fatal = expected.damage >= hero.hp;
    const int enemy_turns = fatal && expected.enemy_hit
                                ? (hero.hp + expected.enemy_hit - 1) / expected.enemy_hit
                                : int(expected.hero_hits) - (enemy_first ? 0 : 1);
    const int hero_turns = fatal ? enemy_turns - (enemy_first ? 1 : 0) : int(expected.hero_hits);
    // Emit one strike at a time. A large fight has constant queue memory and identical beats.
    fight_ = Fight{contact_index, enemy,       hero_turns,
                   enemy_turns,   0,           tile(hero.floor, cell(hero.x, hero.y)),
                   fatal,         enemy_first, commands.size()};
}

void Game::battle_step() {
    if (!fight_)
        return;
    auto& fight = *fight_;
    const int strikes = fight.hero_hits + fight.enemy_hits;
    if (fight.turn >= strikes) {
        const Fight done = fight;
        fight_.reset();
        battle_finished(done);
        return;
    }
    const bool enemy_turn = (fight.turn % 2 == 0) == fight.enemy_first;
    const bool final_strike = fight.turn == strikes - 1;
    const bool final_hero = final_strike && !fight.fatal && !fight.enemy_first;
    ++fight.turn;
    push(Op::Wait);
    int operand = 0;
    if (enemy_turn && fight.fatal) {
        if (final_strike)
            operand = fight.underlying;
        else
            operand = fight.enemy_first ? ForcedFatalOperand : HeroHitColor;
    } else if (!enemy_turn) {
        if (fight.enemy_first && !fight.fatal)
            operand = ForcedVictoryOperand;
        else if (!final_hero && !fight.fatal)
            operand = HeroHitMask;
    }
    push(enemy_turn ? Op::EnemyStrike : Op::HeroStrike, fight.target, operand);
    if (enemy_turn)
        damage_pose(fight.target);
    else {
        push(Op::Wait, fight.underlying, HeroHitColor);
        const bool large = final_hero && (tile(hero.floor, fight.target) == OctopusMouth ||
                                          tile(hero.floor, fight.target) == DragonHead);
        push(large ? Op::LargeMonsterStrike : Op::Overlay, fight.target, HeroHitMask);
    }
    push(Op::Wait);
    push(Op::Sound, SoundCue::Strike);
}

void Game::battle_finished(const Fight& fight) {
    if (fight.fatal) {
        if (fight.enemy_first)
            push(Op::Wait);
        push(Op::Defeat);
        waits(6);
        if (fight.enemy_first)
            waits(12);
        return;
    }
    // The original 0x44B78C panel retains battle information between encounters.
    visual.last_defeated = visual.battle_enemy;
    int reward = monsters[fight.enemy].gold;
    const int target_tile = tile(hero.floor, fight.target);
    // 0x44A480: eight pieces award 50 raw gold; mouth awards 100 and clears the body.
    if (fight.enemy == OctopusRow && target_tile != OctopusMouth)
        reward /= 2;
    push(Op::Callback, Callback::CheckGuards, 5);
    push(Op::Reward, reward);
    push(Op::Message);
    const int position = cell(hero.x, hero.y);
    if (!fight.enemy_first && ((fight.enemy == OctopusRow && target_tile == OctopusMouth) ||
                               (fight.enemy == DragonRow && target_tile == DragonHead)))
        for (int offset : {-21, -22, -23, -12, -11, -10, -1, 0, 1})
            push(Op::WriteTile, position + offset, Road);
    else
        push(Op::WriteTile, position, Road);
    push(Op::Wait);
    push(Op::Callback, Callback::BattleEnd);
    const int earned = reward * (inventory(Item::LuckyGold) + 1);
    status = "Defeated " + std::string(monster_name(fight.enemy)) + ". Received " + std::to_string(earned) +
             " gold.";
}
} // namespace tsw
