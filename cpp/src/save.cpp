#include "save_internal.hpp"
#include "tsw/game.hpp"
#include <fstream>
#include <stdexcept>

namespace tsw {
void detail::save::validate(const Game& game) {
    const auto& h = game.hero;
    constexpr int MaxSavedValue = 100000000;
    if (h.floor < 0 || h.floor >= FloorCount || h.x < 0 || h.x >= BoardWidth || h.y < 0 ||
        h.y >= BoardWidth || h.highest_floor < 0 || h.highest_floor >= FloorCount ||
        (h.cycle_factor_minus_one != 0 && h.cycle_factor_minus_one != BacksideFactor - 1) || h.hp <= 0 ||
        h.attack < 0 || h.defense < 0 || h.gold < 0 || h.yellow_keys < 0 || h.red_keys < 0 ||
        h.blue_keys < 0 || h.hp > MaxSavedValue || h.attack > MaxSavedValue || h.defense > MaxSavedValue ||
        h.gold > MaxSavedValue || h.yellow_keys > 1000000 || h.red_keys > 1000000 || h.blue_keys > 1000000 ||
        h.altar_purchases < 0 || h.altar_purchases > 4000 || h.fairy_visits < 0 || h.fairy_visits > 1000000 ||
        h.later_cycle < 0 || h.later_cycle > 1 || h.flight_direction < FlightDirection::None ||
        h.flight_direction > FlightDirection::Down || h.highest_floor_stair_kind < StairKind::None ||
        h.highest_floor_stair_kind > StairKind::Down || h.fairy_score < 0 || h.fairy_score > MaxSavedValue ||
        h.fairy_rank < 0 || h.fairy_rank > 10 || h.fairy_category < FairyCategory::None ||
        h.fairy_category > FairyCategory::Floor49 || h.sword < EquipmentTier::None ||
        h.sword > EquipmentTier::Sacred || h.shield < EquipmentTier::None ||
        h.shield > EquipmentTier::Sacred || int(h.facing) < 1 || int(h.facing) > 4 ||
        !valid_music_track(h.music_track))
        throw std::runtime_error("Invalid hero state in save");
    for (const auto& floor : game.floors) {
        if (floor.up_landing >= CellCount || floor.down_landing >= CellCount)
            throw std::runtime_error("Invalid stair landing in save");
        for (auto t : floor.tiles)
            if (t > MaxMapTile)
                throw std::runtime_error("Invalid map tile in save");
    }
    for (const auto& m : game.monsters)
        if (m.hp <= 0 || m.hp > 1000000 || m.attack < 0 || m.attack > 1000000 || m.defense < 0 ||
            m.defense > 1000000 || m.gold < 0 || m.gold > 32767)
            throw std::runtime_error("Invalid monster row in save");
    for (int i = 0; i < std::ssize(h.items); ++i)
        if (h.items[i] < 0 || h.items[i] > (i == int(Item::WarpStaff) ? 3 : i == int(Item::HeroOrb) ? 2 : 1))
            throw std::runtime_error("Invalid inventory in save");
    for (int flag : h.equipment_found)
        if (flag < 0 || flag > 1)
            throw std::runtime_error("Invalid acquisition flag");
    for (int flag : h.dialogue_seen)
        if (flag < 0 || flag > 1)
            throw std::runtime_error("Invalid dialogue flag");
    for (auto flag : h.wisdom_hints)
        if (flag < HintState::Unheard || flag > HintState::Recorded)
            throw std::runtime_error("Invalid clue flag");
    for (auto flag : h.old_man_heard)
        if (flag < HintState::Unheard || flag > HintState::Recorded)
            throw std::runtime_error("Invalid NPC clue flag");
    for (int flag : h.merchant_used)
        if (flag < 0 || flag > 1)
            throw std::runtime_error("Invalid merchant flag");
    if (h.merchant2_heard < HintState::Unheard || h.merchant2_heard > HintState::Recorded)
        throw std::runtime_error("Invalid merchant clue flag");
}

void detail::save::write_file(const std::filesystem::path& path, std::span<const std::uint8_t> bytes) {
    if (!path.parent_path().empty())
        std::filesystem::create_directories(path.parent_path());
    auto temporary = path;
    temporary += ".tmp";
    {
        std::ofstream output(temporary, std::ios::binary | std::ios::trunc);
        output.write(reinterpret_cast<const char*>(bytes.data()), static_cast<std::streamsize>(bytes.size()));
        output.flush();
        if (!output)
            throw std::runtime_error("Unable to write save");
    }
    auto backup = path;
    backup += ".bak";
    if (std::filesystem::exists(backup))
        std::filesystem::remove(backup);
    const bool existing = std::filesystem::exists(path);
    if (existing)
        std::filesystem::rename(path, backup);
    try {
        std::filesystem::rename(temporary, path);
    } catch (...) {
        if (existing)
            std::filesystem::rename(backup, path);
        throw;
    }
}

void Game::save(const std::filesystem::path& path, SaveKind kind) const {
    const auto bytes =
        detail::save::encode_original(*this, original_save_record_ ? &*original_save_record_ : nullptr, kind);
    const auto companion = achievement_path(path);
    auto pending = companion;
    pending += ".pending";
    auto backup = path;
    backup += ".bak";
    const bool previous = std::filesystem::exists(companion);
    const bool previous_save = std::filesystem::exists(path);
    if (previous && !std::filesystem::is_regular_file(companion))
        throw std::runtime_error("Achievement companion must be a regular file");
    // Detach old metadata first: even identical save bytes can belong to different histories.
    if (previous) {
        std::filesystem::remove(pending);
        std::filesystem::rename(companion, pending);
    }
    try {
        detail::save::write_file(path, bytes);
    } catch (...) {
        if (previous)
            std::filesystem::rename(pending, companion);
        throw;
    }
    // The original manual writer updates the live checksum words before a later Fairy snapshot.
    original_save_record_ = detail::save::hero_record(bytes);
    try {
        std::filesystem::remove(achievement_path(backup));
        if (previous && previous_save)
            std::filesystem::rename(pending, achievement_path(backup));
        else
            std::filesystem::remove(pending);
        write_run_history(path, bytes, run_history);
    } catch (const std::exception& error) {
        throw AchievementSaveError(std::string("Game saved, but achievement history was not saved: ") +
                                   error.what());
    }
}

void Game::load(const std::filesystem::path& path, SaveKind kind) {
    std::ifstream input(path, std::ios::binary);
    if (!input)
        throw std::runtime_error("Unable to open save");
    load(input, kind);
    input.clear();
    input.seekg(0);
    std::vector<std::uint8_t> bytes(detail::save::OriginalSaveBytes);
    input.read(reinterpret_cast<char*>(bytes.data()), static_cast<std::streamsize>(bytes.size()));
    if (input)
        if (const auto history = read_run_history(path, bytes))
            run_history = *history;
}

void Game::save(std::ostream& output, SaveKind kind) const {
    const auto bytes =
        detail::save::encode_original(*this, original_save_record_ ? &*original_save_record_ : nullptr, kind);
    output.write(reinterpret_cast<const char*>(bytes.data()), static_cast<std::streamsize>(bytes.size()));
    if (!output)
        throw std::runtime_error("Unable to write save");
    original_save_record_ = detail::save::hero_record(bytes);
}

void Game::load(std::istream& input, SaveKind kind) {
    // Original BlockRead consumes two fixed records and ignores trailing data.
    std::vector<std::uint8_t> bytes(detail::save::OriginalSaveBytes);
    input.read(reinterpret_cast<char*>(bytes.data()), static_cast<std::streamsize>(bytes.size()));
    if (!input)
        throw std::runtime_error("Truncated original save: expected 6957 bytes");
    detail::save::OriginalRecord record;
    Game restored = detail::save::decode_original(bytes, record, kind);
    restored.run_history.complete = false;
    restored.run_history.dragon_slayer_acquired = restored.inventory(Item::DragonSlayer) > 0;
    // Rankings belong to the save directory, not to an individual game slot.
    restored.rankings = rankings;
    restored.original_save_record_ = record;
    // The original load refresh (0x454DE8 -> 0x442C38) clears this live marker
    // after reading the raw record. Runtime snapshots bypass file loading.
    restored.hero.highest_floor_stair_kind = StairKind::None;
    *this = std::move(restored); // A malformed file never partially changes the live game.
}
} // namespace tsw
