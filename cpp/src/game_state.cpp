#include "tsw/game_state.hpp"
#include "save_internal.hpp"
#include <stdexcept>

namespace tsw {
GameState GameState::capture(const Game& g) {
    return {g.hero,           g.floors,
            g.monsters,       g.rankings,
            g.commands,       g.dialogue,
            g.visual,         g.status,
            g.sounds,         g.checkpoint_requested,
            g.contact_index,  g.scratch_index,
            g.neighbor_index, g.message_code,
            g.door_opened,    g.original_save_record_,
            g.fight_,         g.shop_kind_,
            g.shop_cost_,     g.shop_hint_,
            g.shop_id_,       g.shop_npc_cell_,
            g.stopped_};
}

Game GameState::restore() const {
    Game g;
    g.hero = hero;
    g.floors = floors;
    g.monsters = monsters;
    g.rankings = rankings;
    // Runtime migration also permits a fallen hero, unlike manual saves.
    if (hero.hp < 0)
        throw std::runtime_error("Invalid runtime hit points");
    if (g.hero.hp == 0)
        g.hero.hp = 1;
    save_detail::validate(g);
    g.hero.hp = hero.hp;
    const auto valid_cell = [](int index) { return index >= 0 && index < CellCount; };
    if (!valid_cell(contact_index) || !valid_cell(scratch_index) || !valid_cell(neighbor_index) ||
        commands.size() > 100000 || sounds.size() > 100000 || shop_kind < 0 || shop_kind > 2 ||
        shop_cost < 0 || shop_hint < -1 || shop_hint > 29 || shop_id < -1 || shop_id >= 12 ||
        !valid_cell(shop_npc_cell))
        throw std::runtime_error("Invalid runtime continuation state");
    for (const auto& command : commands)
        if (command.op > Op::DeathScene)
            throw std::runtime_error("Invalid runtime command");
    for (const auto sound : sounds)
        if (sound < SoundCue::Open || sound > SoundCue::Stairs2)
            throw std::runtime_error("Invalid runtime sound cue");
    if (dialogue && (dialogue->continuation < 0 || dialogue->continuation > 300 ||
                     (dialogue->shop && (shop_kind == 0 || (shop_kind == 2 && shop_id < 0)))))
        throw std::runtime_error("Invalid runtime dialogue");
    if (fight && (!valid_cell(fight->target) || fight->enemy < 0 || fight->enemy >= 33 ||
                  fight->hero_hits < 0 || fight->enemy_hits < 0 || fight->turn < 0 ||
                  std::int64_t(fight->turn) > std::int64_t(fight->hero_hits) + fight->enemy_hits ||
                  fight->base_commands > commands.size()))
        throw std::runtime_error("Invalid runtime fight");
    if (visual.enemy_index < -1 || visual.enemy_index >= 33 || visual.enemy_hp < 0 ||
        visual.overlay_cell < -1 || visual.overlay_cell >= CellCount || visual.door_cell < -1 ||
        visual.door_cell >= CellCount || visual.stair_source_floor < -1 ||
        visual.stair_source_floor >= FloorCount ||
        (visual.stair_source_floor >= 0 &&
         (visual.stair_hero_x < 0 || visual.stair_hero_x >= BoardWidth || visual.stair_hero_y < 0 ||
          visual.stair_hero_y >= BoardWidth || int(visual.stair_hero_facing) < 1 ||
          int(visual.stair_hero_facing) > 4)))
        throw std::runtime_error("Invalid runtime visual state");
    const auto valid_enemy = [](const EnemyInfo& enemy) {
        return enemy.row >= -1 && enemy.row < 33 && enemy.tile >= 0 && enemy.tile <= 165 &&
               enemy.stats.hp >= 0 && enemy.stats.attack >= 0 && enemy.stats.defense >= 0 &&
               enemy.stats.gold >= 0 && enemy.damage >= 0;
    };
    if (!valid_enemy(visual.battle_enemy) ||
        (visual.last_defeated && (!valid_enemy(*visual.last_defeated) || visual.last_defeated->row < 0)))
        throw std::runtime_error("Invalid runtime encounter state");
    g.commands = commands;
    g.dialogue = dialogue;
    g.visual = visual;
    g.status = status;
    g.sounds = sounds;
    g.checkpoint_requested = checkpoint_requested;
    g.contact_index = contact_index;
    g.scratch_index = scratch_index;
    g.neighbor_index = neighbor_index;
    g.message_code = message_code;
    g.door_opened = door_opened;
    g.original_save_record_ = original_save_record;
    g.fight_ = fight;
    g.shop_kind_ = shop_kind;
    g.shop_cost_ = shop_cost;
    g.shop_hint_ = shop_hint;
    g.shop_id_ = shop_id;
    g.shop_npc_cell_ = shop_npc_cell;
    g.stopped_ = stopped;
    return g;
}
} // namespace tsw
