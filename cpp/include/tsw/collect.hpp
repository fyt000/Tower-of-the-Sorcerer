#pragma once
#include "tsw/game.hpp"
#include <functional>

namespace tsw {
struct CollectedItem {
    int position{}, tile{};
};

// Collect only pickups connected by safe floor, repeatedly exposing more pickups.
// Omitted potions remain barriers. The hero finishes at the starting position.
// Native input expansion preserves existing saves and ordinary walking in replays.
std::vector<CollectedItem> collect_items(Game&, bool except_potions,
                                         const std::function<void(Direction)>& move = {});
} // namespace tsw
