#include "tsw/achievements.hpp"
#include "save_internal.hpp"
#include "tsw/game.hpp"
#include <fstream>
#include <glaze/json.hpp>
#include <stdexcept>

namespace tsw {
namespace achievement_detail {
struct Companion {
    int version = 1;
    std::uint64_t save_fingerprint{};
    RunHistory history;
};

std::uint64_t fingerprint(std::span<const std::uint8_t> bytes) {
    std::uint64_t hash = 14695981039346656037ULL;
    for (auto byte : bytes) {
        hash ^= byte;
        hash *= 1099511628211ULL;
    }
    return hash;
}

AchievementStatus avoidance(bool violated, bool complete, bool requirement = true) {
    if (violated || (complete && !requirement))
        return AchievementStatus::Missed;
    return complete ? AchievementStatus::Earned : AchievementStatus::Unverified;
}
} // namespace achievement_detail

using namespace achievement_detail;

std::array<Achievement, 6> ending_achievements(const EndingSummary& summary) {
    const auto& h = summary.hero;
    const auto& run = summary.history;
    return {{{"50F Zeno seal", "Reach the ending with Zeno's seal still active.", Zeno, 0,
              h.zeno_sealed ? AchievementStatus::Earned : AchievementStatus::Missed},
             {"Octopus fair play", "Finish without defeating any outer Octopus part.", OctopusMouth, 0,
              avoidance(run.octopus_parts_defeated, run.complete)},
             {"No Dragon Slayer", "Slay the Dragon without ever acquiring the Dragon Slayer.", DragonHead,
              DragonSlayer,
              avoidance(run.dragon_slayer_acquired || h.items[int(Item::DragonSlayer)] > 0, run.complete,
                        run.dragon_defeated)},
             {"No Bomb on shield guards", "Finish without bombing either of the Sacred Shield's 44F guards.",
              SacredShield, Bomb, avoidance(run.shield_guards_bombed, run.complete)},
             {"Altar devotee", "Make at least 21 altar purchases.", Altar, 0,
              h.altar_purchases >= 21 ? AchievementStatus::Earned : AchievementStatus::Missed},
             {"Red key collector", "Finish with at least 5 red keys.", RedKey, 0,
              h.red_keys >= 5 ? AchievementStatus::Earned : AchievementStatus::Missed}}};
}

std::filesystem::path achievement_path(const std::filesystem::path& save) {
    auto path = save;
    path += ".achievements.json";
    return path;
}

std::optional<RunHistory> read_run_history(const std::filesystem::path& path,
                                           std::span<const std::uint8_t> bytes) {
    try {
        const auto companion = achievement_path(path);
        if (!std::filesystem::is_regular_file(companion) || std::filesystem::file_size(companion) > 4096)
            return {};
        std::ifstream input(companion, std::ios::binary);
        const std::string text{std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>()};
        Companion record;

        struct Options : glz::opts {
            bool validate_trailing_whitespace = true;
        };

        constexpr auto options = [] {
            Options value;
            value.null_terminated = false;
            value.error_on_missing_keys = true;
            return value;
        }();
        if (!input || glz::read<options>(record, text) || record.version != 1 ||
            record.save_fingerprint != fingerprint(bytes))
            return {};
        return record.history;
    } catch (const std::exception&) {
        return {}; // Optional metadata must never prevent loading an original save.
    }
}

void write_run_history(const std::filesystem::path& path, std::span<const std::uint8_t> bytes,
                       const RunHistory& history) {
    std::string text;
    if (const auto error = glz::write_json(Companion{1, fingerprint(bytes), history}, text))
        throw std::runtime_error(glz::format_error(error));
    save_detail::write_file(achievement_path(path), {text.begin(), text.end()});
}
} // namespace tsw
