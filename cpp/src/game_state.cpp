#include "tsw/game_state.hpp"
#include "save_internal.hpp"
#include <stdexcept>

namespace tsw {
GameState GameState::capture(const Game& g) {
    return {.hero = g.hero,
            .run_history = g.run_history,
            .ending_summary = g.ending_summary,
            .floors = g.floors,
            .monsters = g.monsters,
            .rankings = g.rankings,
            .commands = g.commands,
            .dialogue = g.dialogue,
            .visual = g.visual,
            .status = g.status,
            .sounds = g.sounds,
            .checkpoint_requested = g.checkpoint_requested,
            .contact_index = g.contact_index,
            .scratch_index = g.scratch_index,
            .neighbor_index = g.neighbor_index,
            .message_code = g.message_code,
            .door_opened = g.door_opened,
            .original_save_record = g.original_save_record_,
            .fight = g.fight_,
            .shop_kind = g.shop_kind_,
            .shop_cost = g.shop_cost_,
            .shop_hint = g.shop_hint_,
            .shop_id = g.shop_id_,
            .shop_npc_cell = g.shop_npc_cell_,
            .stopped = g.stopped_};
}

Game GameState::restore() const {
    Game g;
    g.hero = hero;
    g.run_history = run_history;
    g.ending_summary = ending_summary;
    g.floors = floors;
    g.monsters = monsters;
    g.rankings = rankings;
    // Runtime migration also permits a fallen hero, unlike manual saves.
    if (hero.hp < 0)
        throw std::runtime_error("Invalid runtime hit points");
    if (g.hero.hp == 0)
        g.hero.hp = 1;
    detail::save::validate(g);
    g.hero.hp = hero.hp;
    const auto valid_cell = [](int index) { return index >= 0 && index < CellCount; };
    if (!valid_cell(contact_index) || !valid_cell(scratch_index) || !valid_cell(neighbor_index) ||
        commands.size() > 100000 || sounds.size() > 100000 || shop_kind < ShopKind::None ||
        shop_kind > ShopKind::Merchant || shop_cost < 0 || shop_hint < -1 || shop_hint > 29 || shop_id < -1 ||
        shop_id >= 12 || !valid_cell(shop_npc_cell))
        throw std::runtime_error("Invalid runtime continuation state");
    for (const auto& command : commands)
        if (command.op > Op::DeathScene)
            throw std::runtime_error("Invalid runtime command");
    for (const auto sound : sounds)
        if (sound < SoundCue::Open || sound > SoundCue::Stairs2)
            throw std::runtime_error("Invalid runtime sound cue");
    if (dialogue && (dialogue->continuation < ContinuationStage::None ||
                     dialogue->continuation > ContinuationStage::LastValid ||
                     (dialogue->shop &&
                      (shop_kind == ShopKind::None || (shop_kind == ShopKind::Merchant && shop_id < 0)))))
        throw std::runtime_error("Invalid runtime dialogue");
    if (fight &&
        (!valid_cell(fight->target) || fight->monster_index < 0 || fight->monster_index >= MonsterCount ||
         fight->hero_strike_count < 0 || fight->enemy_strike_count < 0 || fight->turn < 0 ||
         std::int64_t(fight->turn) > std::int64_t(fight->hero_strike_count) + fight->enemy_strike_count ||
         fight->base_commands > commands.size()))
        throw std::runtime_error("Invalid runtime fight");
    if (!valid_raster_mode(visual.raster_mode) || visual.monster_index < -1 ||
        visual.monster_index >= MonsterCount || visual.enemy_hp < 0 || visual.overlay_cell < -1 ||
        visual.overlay_cell >= CellCount || visual.door_cell < -1 || visual.door_cell >= CellCount ||
        visual.stair_source_floor < -1 || visual.stair_source_floor >= FloorCount ||
        (visual.stair_source_floor >= 0 &&
         (visual.stair_hero_x < 0 || visual.stair_hero_x >= BoardWidth || visual.stair_hero_y < 0 ||
          visual.stair_hero_y >= BoardWidth || int(visual.stair_hero_facing) < 1 ||
          int(visual.stair_hero_facing) > 4)))
        throw std::runtime_error("Invalid runtime visual state");
    const auto valid_enemy = [](const EnemyInfo& enemy) {
        return enemy.monster_index >= -1 && enemy.monster_index < MonsterCount && enemy.tile >= 0 &&
               enemy.tile <= MaxMapTile && enemy.stats.hp >= 0 && enemy.stats.attack >= 0 &&
               enemy.stats.defense >= 0 && enemy.stats.gold >= 0 && enemy.damage >= 0;
    };
    if (!valid_enemy(visual.battle_enemy) ||
        (visual.last_defeated &&
         (!valid_enemy(*visual.last_defeated) || visual.last_defeated->monster_index < 0)))
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
