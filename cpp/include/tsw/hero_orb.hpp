#pragma once
#include "tsw/game.hpp"

namespace tsw {
struct OrbTileInfo {
    int row{};
    std::int64_t hp{}, attack{}, defense{}, gold{};
    Forecast forecast;
};

// Presentation-only information, unlocked by owning the Orb. No state or scripts are executed.
std::optional<OrbTileInfo> orb_tile_info(const Game&, int floor, int index, bool actual_damage);
std::string compact_orb_number(std::int64_t value);
} // namespace tsw
