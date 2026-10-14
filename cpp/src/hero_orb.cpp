#include "tsw/hero_orb.hpp"
#include <array>
#include <utility>

namespace tsw {
std::optional<OrbTileInfo> orb_tile_info(const Game& game, int floor, int index, bool actual_damage) {
    if (!game.inventory(Item::HeroOrb) || floor < 0 || floor >= FloorCount || index < 0 || index >= CellCount)
        return {};
    const int tile = game.tile(floor, index), row = Game::monster_for_tile(tile);
    if (row < 0)
        return {};
    const auto& monster = game.monsters[row];
    const std::int64_t scale = game.hero.cycle_factor_minus_one + 1;
    std::int64_t gold = monster.gold;
    if (row == OctopusRow && tile != OctopusMouth)
        gold /= 2;
    gold *= std::int64_t(game.inventory(Item::LuckyGold)) + 1;
    return OrbTileInfo{row,
                       monster.hp * scale,
                       monster.attack * scale,
                       monster.defense * scale,
                       gold,
                       actual_damage ? game.forecast(tile) : game.orb_forecast(tile)};
}

std::string compact_orb_number(std::int64_t value) {
    // Abbreviations are display-only; the hover inspector retains exact values.
    if (value >= 1000000000000000LL) {
        int exponent = 0;
        for (auto leading = value; leading >= 10; leading /= 10)
            ++exponent;
        auto leading = value;
        for (int i = 0; i < exponent; ++i)
            leading /= 10;
        return std::to_string(leading) + "e" + std::to_string(exponent);
    }
    for (const auto [unit, suffix] : std::array<std::pair<std::int64_t, const char*>, 4>{
             {{1000000000000LL, "T"}, {1000000000, "B"}, {1000000, "M"}, {1000, "k"}}}) {
        if (value >= unit) {
            const auto whole = value / unit, tenth = value % unit / (unit / 10);
            return std::to_string(whole) + (whole < 10 && tenth ? "." + std::to_string(tenth) : "") + suffix;
        }
    }
    return std::to_string(value);
}
} // namespace tsw
