#pragma once
#include "tsw/game.hpp"

namespace tsw {
// Complete in-process state for worker migration. This is independent of the
// original save format and has no transport or serialization dependency.
struct GameState {
    using Fight = Game::Fight;
    Hero hero;
    RunHistory run_history;
    std::optional<EndingSummary> ending_summary;
    std::array<Floor, FloorCount> floors;
    std::array<Monster, MonsterCount> monsters;
    RankingTables rankings;
    std::vector<Command> commands;
    std::optional<Dialogue> dialogue;
    Visual visual;
    std::string status;
    std::vector<SoundCue> sounds;
    bool checkpoint_requested{};
    int contact_index{}, scratch_index{}, neighbor_index{}, message_code{}, door_opened{};
    std::optional<std::array<std::uint32_t, OriginalHeroWordCount>> original_save_record;
    std::optional<Fight> fight;
    ShopKind shop_kind{};
    int shop_cost{}, shop_hint{}, shop_id{}, shop_npc_cell{};
    bool stopped{};

    static GameState capture(const Game&);
    Game restore() const;
};
} // namespace tsw
