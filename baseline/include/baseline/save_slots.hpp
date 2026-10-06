#pragma once
#include "baseline/game.hpp"

namespace baseline {
inline constexpr int ManualSaveSlotCount = 8; // Data 1 through Data 8 in the original VCL form.
enum class SaveSlotState { Empty, Ready, Invalid };
struct SaveSlotInfo {
    SaveSlotState state = SaveSlotState::Empty;
    int floor{}, hp{}, attack{}, defense{};
    bool backside{}, later_cycle{};
    std::string error;
    bool original_location{};
};
using SaveSlots = std::array<SaveSlotInfo, ManualSaveSlotCount>;
std::filesystem::path save_slot_path(const std::filesystem::path& directory, int number);
std::filesystem::path load_slot_path(const std::filesystem::path& directory, int number,
                                     const std::filesystem::path& original_directory = {});
SaveSlots inspect_save_slots(const std::filesystem::path& directory,
                             const std::filesystem::path& original_directory = {});
} // namespace baseline
