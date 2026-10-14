#pragma once
#include "tsw/localization.hpp"
#include <array>
#include <filesystem>

namespace tsw {
inline constexpr std::array<float, 3> GameSpeeds{1, 3, 10};
inline constexpr std::array<float, 7> ReplaySpeeds{.25f, .5f, 1, 2, 3, 5, 10};

struct Settings {
    int game_speed{}, replay_speed = 2;
    bool recording{}, muted{}, hero_orb_actual_damage{};
    std::string language = "en";
};

Settings load_settings(const std::filesystem::path&);
void save_settings(const std::filesystem::path&, const Settings&);
} // namespace tsw
