#include "tsw/settings.hpp"
#include <glaze/json.hpp>
#include <stdexcept>

namespace tsw {
namespace {
void validate(const Settings& settings) {
    if (settings.game_speed < 0 || settings.game_speed >= int(GameSpeeds.size()) ||
        settings.replay_speed < 0 || settings.replay_speed >= int(ReplaySpeeds.size()))
        throw std::runtime_error("Saved speed setting is out of range");
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
