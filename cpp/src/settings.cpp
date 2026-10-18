#include "tsw/settings.hpp"
#include <cmath>
#include <glaze/json.hpp>
#include <stdexcept>

template <> struct glz::meta<tsw::Settings> {
    static constexpr auto modify = glz::object("game_speed", &tsw::Settings::game_speed_index, "replay_speed",
                                               &tsw::Settings::replay_speed_index);
};

namespace tsw {
namespace {
void validate(const Settings& settings) {
    parse_language(settings.language);
    if (settings.game_speed_index < 0 || settings.game_speed_index >= std::ssize(GameSpeeds) ||
        settings.replay_speed_index < 0 || settings.replay_speed_index >= std::ssize(ReplaySpeeds))
        throw std::runtime_error("Saved speed setting is out of range");
    if (settings.animation_speed &&
        (!std::isfinite(*settings.animation_speed) || *settings.animation_speed < MinAnimationSpeed / 10.f ||
         *settings.animation_speed > MaxAnimationSpeed / 10.f))
        throw std::runtime_error("Saved animation speed is out of range");
}
} // namespace

Settings load_settings(const std::filesystem::path& path) {
    Settings settings;
    if (std::filesystem::exists(path)) {
        std::string buffer;
        if (const auto error = glz::read_file_json(settings, path.string(), buffer))
            throw std::runtime_error("Unable to read settings: " + glz::format_error(error, buffer));
        validate(settings);
    }
    return settings;
}

void save_settings(const std::filesystem::path& path, const Settings& settings) {
    validate(settings);
    if (!path.parent_path().empty())
        std::filesystem::create_directories(path.parent_path());
    if (const auto error = glz::write_file_json(settings, path.string(), std::string{}))
        throw std::runtime_error("Unable to write settings: " + glz::format_error(error));
}
} // namespace tsw
