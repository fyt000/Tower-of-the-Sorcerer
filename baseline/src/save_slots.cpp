#include "baseline/save_slots.hpp"
#include <stdexcept>

namespace baseline {
std::filesystem::path save_slot_path(const std::filesystem::path& directory, int number) {
    if (number < 1 || number > ManualSaveSlotCount)
        throw std::out_of_range("Save slot must be between 1 and 8");
    return directory / ("slot-" + std::to_string(number) + ".save");
}
std::filesystem::path load_slot_path(const std::filesystem::path& directory, int number,
                                     const std::filesystem::path& original_directory) {
    const auto modern = save_slot_path(directory, number);
    if (std::filesystem::exists(modern))
        return modern;
    const auto name = "save" + std::to_string(number) + ".dat";
    for (const auto& path : {directory / name, directory / "Savedat" / name})
        if (std::filesystem::exists(path))
            return path;
    if (!original_directory.empty())
        for (const auto& path : {original_directory / "Savedat" / name, original_directory / name})
            if (std::filesystem::exists(path))
                return path;
    return modern;
}
SaveSlots inspect_save_slots(const std::filesystem::path& directory,
                             const std::filesystem::path& original_directory) {
    SaveSlots slots;
    for (int number = 1; number <= ManualSaveSlotCount; ++number) {
        auto& info = slots[number - 1];
        try {
            const auto path = load_slot_path(directory, number, original_directory);
            if (!std::filesystem::exists(path))
                continue;
            Game saved;
            saved.load(path); // Use the same validation as restore; never alter the live game.
            const auto& hero = saved.hero;
            info = {SaveSlotState::Ready,
                    hero.floor,
                    hero.hp,
                    hero.attack,
                    hero.defense,
                    hero.cycle_factor_minus_one != 0,
                    hero.later_cycle != 0,
                    {}};
            info.original_location = path != save_slot_path(directory, number);
        } catch (const std::exception& error) {
            info.state = SaveSlotState::Invalid;
            info.error = error.what();
        }
    }
    return slots;
}
} // namespace baseline
