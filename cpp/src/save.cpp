#include "save_internal.hpp"
#include "tsw/game.hpp"
#include <fstream>
#include <stdexcept>

namespace tsw {
void save_detail::validate(const Game& game) {
    const auto& h = game.hero;
    constexpr int MaxSavedValue = 100000000;
    if (h.floor < 0 || h.floor >= FloorCount || h.x < 0 || h.x >= 11 || h.y < 0 || h.y >= 11 ||
        h.highest_floor < 0 || h.highest_floor > 50 ||
        (h.cycle_factor_minus_one != 0 && h.cycle_factor_minus_one != 43) || h.hp <= 0 || h.attack < 0 ||
        h.defense < 0 || h.gold < 0 || h.yellow_keys < 0 || h.red_keys < 0 || h.blue_keys < 0 ||
        h.hp > MaxSavedValue || h.attack > MaxSavedValue || h.defense > MaxSavedValue ||
        h.gold > MaxSavedValue || h.yellow_keys > 1000000 || h.red_keys > 1000000 || h.blue_keys > 1000000 ||
        h.altar_purchases < 0 || h.altar_purchases > 4000 || h.fairy_visits < 0 || h.fairy_visits > 1000000 ||
        h.later_cycle < 0 || h.later_cycle > 1 || h.flight_direction < 0 || h.flight_direction > 2 ||
        h.highest_floor_stair < 0 || h.highest_floor_stair > 2 || h.fairy_score < 0 ||
        h.fairy_score > MaxSavedValue || h.fairy_rank < 0 || h.fairy_rank > 10 || h.fairy_category < 0 ||
        h.fairy_category > 5 || h.sword < 0 || h.sword > 5 || h.shield < 0 || h.shield > 5 ||
        int(h.facing) < 1 || int(h.facing) > 4 || h.music_track < 0 || h.music_track > 21)
        throw std::runtime_error("Invalid hero state in save");
    for (const auto& floor : game.floors) {
        if (floor.up_landing >= CellCount || floor.down_landing >= CellCount)
            throw std::runtime_error("Invalid stair landing in save");
        for (auto t : floor.tiles)
            if (t > 165)
                throw std::runtime_error("Invalid map tile in save");
    }
    for (const auto& m : game.monsters)
        if (m.hp <= 0 || m.hp > 1000000 || m.attack < 0 || m.attack > 1000000 || m.defense < 0 ||
            m.defense > 1000000 || m.gold < 0 || m.gold > 32767)
            throw std::runtime_error("Invalid monster row in save");
    for (int i = 0; i < int(h.items.size()); ++i)
        if (h.items[i] < 0 || h.items[i] > (i == int(Item::WarpStaff) ? 3 : i == int(Item::HeroOrb) ? 2 : 1))
            throw std::runtime_error("Invalid inventory in save");
    for (int flag : h.equipment_found)
        if (flag < 0 || flag > 1)
            throw std::runtime_error("Invalid acquisition flag");
    for (int flag : h.dialogue_seen)
        if (flag < 0 || flag > 1)
            throw std::runtime_error("Invalid dialogue flag");
    for (int flag : h.wisdom_hints)
        if (flag < 0 || flag > 2)
            throw std::runtime_error("Invalid clue flag");
    for (int flag : h.old_man_heard)
        if (flag < 0 || flag > 2)
            throw std::runtime_error("Invalid NPC clue flag");
    for (int flag : h.merchant_used)
        if (flag < 0 || flag > 1)
            throw std::runtime_error("Invalid merchant flag");
    if (h.merchant2_heard < 0 || h.merchant2_heard > 2)
        throw std::runtime_error("Invalid merchant clue flag");
}

void save_detail::write_file(const std::filesystem::path& path, const std::vector<std::uint8_t>& bytes) {
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
        save_detail::encode_original(*this, original_save_record_ ? &*original_save_record_ : nullptr, kind);
    save_detail::write_file(path, bytes);
    // The original manual writer updates the live checksum words before a later Fairy snapshot.
    original_save_record_ = save_detail::hero_record(bytes);
}

void Game::load(const std::filesystem::path& path, SaveKind kind) {
    std::ifstream input(path, std::ios::binary);
    if (!input)
        throw std::runtime_error("Unable to open save");
    load(input, kind);
}

void Game::save(std::ostream& output, SaveKind kind) const {
    const auto bytes =
        save_detail::encode_original(*this, original_save_record_ ? &*original_save_record_ : nullptr, kind);
    output.write(reinterpret_cast<const char*>(bytes.data()), static_cast<std::streamsize>(bytes.size()));
    if (!output)
        throw std::runtime_error("Unable to write save");
    original_save_record_ = save_detail::hero_record(bytes);
}

void Game::load(std::istream& input, SaveKind kind) {
    // Original BlockRead consumes two fixed records and ignores trailing data.
    std::vector<std::uint8_t> bytes(save_detail::OriginalSaveBytes);
    input.read(reinterpret_cast<char*>(bytes.data()), static_cast<std::streamsize>(bytes.size()));
    if (!input)
        throw std::runtime_error("Truncated original save: expected 6957 bytes");
    save_detail::OriginalRecord record;
    Game restored = save_detail::decode_original(bytes, record, kind);
    restored.original_save_record_ = record;
    *this = std::move(restored); // A malformed file never partially changes the live game.
}
} // namespace tsw
