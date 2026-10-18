#pragma once
#include "tsw/localization.hpp"
#include <array>
#include <filesystem>
#include <optional>

namespace tsw {
inline constexpr std::array<float, 3> GameSpeeds{1, 3, 10};
inline constexpr std::array<float, 7> ReplaySpeeds{.25f, .5f, 1, 2, 3, 5, 10};
inline constexpr int MinAnimationSpeed = 10, MaxAnimationSpeed = 100; // Tenths of normal speed.

struct Settings {
    int game_speed_index{}, replay_speed_index = 2;
    bool recording{}, muted{}, hero_orb_actual_damage{};
    std::string language = "en";
    bool mouse_walking{};
    bool realtime_hero_orb{};
    std::optional<bool> touch_controls; // Unset follows the current input device.
    bool blink_mode{};
    bool item_collection{};
    bool skip_attack_animation{};
    bool skip_staircase_animation{};
    std::optional<float> animation_speed; // Missing in older settings; use the legacy preset.

    float effective_animation_speed() const { return animation_speed.value_or(GameSpeeds[game_speed_index]); }
};

Settings load_settings(const std::filesystem::path&);
void save_settings(const std::filesystem::path&, const Settings&);
} // namespace tsw
