#include "baseline/save_slots.hpp"
#include <stdexcept>

namespace baseline {
std::filesystem::path save_slot_path(const std::filesystem::path& directory, int number) {
    if (number < 1 || number > ManualSaveSlotCount)
        throw std::out_of_range("Save slot must be between 1 and 8");
    return directory / ("save" + std::to_string(number) + ".dat");
}
SaveSlots inspect_save_slots(const std::filesystem::path& directory) {
    SaveSlots slots;
    for (int number = 1; number <= ManualSaveSlotCount; ++number) {
        auto& info = slots[number - 1];
        try {
            const auto path = save_slot_path(directory, number);
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
        } catch (const std::exception& error) {
            info.state = SaveSlotState::Invalid;
            info.error = error.what();
        }
    }
    return slots;
}
} // namespace baseline
