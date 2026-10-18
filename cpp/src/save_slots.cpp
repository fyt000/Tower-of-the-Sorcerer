#include "tsw/save_slots.hpp"
#include <format>
#include <stdexcept>

namespace tsw {
namespace {
SaveSlotInfo inspect_save(const std::filesystem::path& path) {
    SaveSlotInfo info;
    try {
        if (!std::filesystem::exists(path))
            return info;
        Game saved;
        saved.load(path);
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
    return info;
}
} // namespace

std::filesystem::path save_slot_path(const std::filesystem::path& directory, int number) {
    if (number < 1 || number > ManualSaveSlotCount)
        throw std::out_of_range("Save slot must be between 1 and 8");
    return directory / std::format("save{}.dat", number);
}

SaveSlots inspect_save_slots(const std::filesystem::path& directory) {
    SaveSlots slots;
    for (int number = 1; number <= ManualSaveSlotCount; ++number) {
        slots[number - 1] = inspect_save(save_slot_path(directory, number));
    }
    return slots;
}

std::filesystem::path floor_autosave_path(const std::filesystem::path& directory) {
    return directory / "autosave.save";
}

SaveSlotInfo inspect_floor_autosave(const std::filesystem::path& directory) {
    return inspect_save(floor_autosave_path(directory));
}
} // namespace tsw
