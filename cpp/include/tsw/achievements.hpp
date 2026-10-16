#pragma once
#include <array>
#include <cstdint>
#include <filesystem>
#include <optional>
#include <span>
#include <stdexcept>
#include <string_view>

namespace tsw {
// Per-cycle history. Kept outside Hero and the original save record.
struct RunHistory {
    bool complete = true;
    bool octopus_parts_defeated{}, dragon_slayer_acquired{}, dragon_defeated{};
    bool shield_guards_bombed{};
    friend bool operator==(const RunHistory&, const RunHistory&) = default;
};

enum class AchievementStatus { Earned, Missed, Unverified };

struct Achievement {
    std::string_view name, description;
    int icon{}, overlay{};
    AchievementStatus status{};
};

struct EndingSummary;

// The original save was committed successfully; callers must still commit matching replay metadata.
class AchievementSaveError : public std::runtime_error {
  public:
    using std::runtime_error::runtime_error;
};

std::array<Achievement, 6> ending_achievements(const EndingSummary&);
std::filesystem::path achievement_path(const std::filesystem::path& save);
// Companions are bound to the exact original save bytes. Missing/stale metadata is unknown history.
std::optional<RunHistory> read_run_history(const std::filesystem::path&, std::span<const std::uint8_t>);
void write_run_history(const std::filesystem::path&, std::span<const std::uint8_t>, const RunHistory&);
} // namespace tsw
