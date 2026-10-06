#include "baseline/game.hpp"
#include "original_constants.hpp"
#include "save_internal.hpp"
#include <fstream>
#include <stdexcept>
#include <tuple>
#include <type_traits>

namespace baseline {
namespace {
template <class Archive> void fields(Archive& archive, Game& game) {
    auto& h = game.hero;
    auto scalars = std::tie(
        h.hp, h.attack, h.defense, h.gold, h.floor, h.highest_floor, h.x, h.y, h.yellow_keys, h.red_keys,
        h.blue_keys, h.altar_purchases, h.fairy_visits, h.sword, h.shield, h.floor34_reward_created,
        h.floor35_reward_created, h.floor40_reward_created, h.floor41_reward_created, h.floor32_arrival_seen,
        h.zeno_sealed, h.cycle_factor_minus_one, h.later_cycle, h.facing, h.music_track, h.fairy_score,
        h.fairy_rank, h.fairy_category, h.flight_direction, h.highest_floor_stair);
    std::apply([&](auto&... values) { (archive(values), ...); }, scalars);
    for (auto& v : h.items)
        archive(v);
    for (auto& v : h.equipment_found)
        archive(v);
    for (auto& v : h.dialogue_seen)
        archive(v);
    for (auto& v : h.wisdom_hints)
        archive(v);
    for (auto& v : h.merchant_used)
        archive(v);
    for (auto& v : h.old_man_heard)
        archive(v);
    archive(h.merchant2_heard);
    for (auto& f : game.floors) {
        archive(f.up_landing);
        archive(f.down_landing);
        for (auto& t : f.tiles)
            archive(t);
    }
    for (auto& m : game.monsters) {
        archive(m.hp);
        archive(m.attack);
        archive(m.defense);
        archive(m.gold);
    }
}
std::uint32_t checksum(const std::vector<std::uint8_t>& bytes) {
    std::uint32_t value = 2166136261u;
    for (auto b : bytes) {
        value ^= b;
        value *= 16777619u;
    }
    return value;
}
std::uint32_t read_word(const std::vector<std::uint8_t>& bytes, std::size_t& cursor) {
    if (cursor > bytes.size() || bytes.size() - cursor < 4)
        throw std::runtime_error("Truncated baseline save");
    std::uint32_t value = 0;
    for (int i = 0; i < 4; ++i)
        value |= std::uint32_t(bytes[cursor++]) << (8 * i);
    return value;
}
} // namespace
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
        throw std::runtime_error("Invalid hero state in baseline save");
    for (const auto& floor : game.floors) {
        if (floor.up_landing >= CellCount || floor.down_landing >= CellCount)
            throw std::runtime_error("Invalid stair landing in baseline save");
        for (auto t : floor.tiles)
            if (t > 165)
                throw std::runtime_error("Invalid map tile in baseline save");
    }
    for (const auto& m : game.monsters)
        if (m.hp <= 0 || m.hp > 1000000 || m.attack < 0 || m.attack > 1000000 || m.defense < 0 ||
            m.defense > 1000000 || m.gold < 0 || m.gold > 32767)
            throw std::runtime_error("Invalid monster row in baseline save");
    for (int i = 0; i < int(h.items.size()); ++i)
        if (h.items[i] < 0 || h.items[i] > (i == int(Item::WarpStaff) ? 3 : i == int(Item::HeroOrb) ? 2 : 1))
            throw std::runtime_error("Invalid inventory in baseline save");
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
            throw std::runtime_error("Unable to write baseline save");
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
void Game::save(const std::filesystem::path& path) const {
    const auto bytes =
        save_detail::encode_original(*this, original_save_record_ ? &*original_save_record_ : nullptr);
    save_detail::write_file(path, bytes);
}
void Game::load(const std::filesystem::path& path) {
    std::ifstream input(path, std::ios::binary);
    if (!input)
        throw std::runtime_error("Unable to open baseline save");
    const auto size = std::filesystem::file_size(path);
    if (size < 76 || size > 100000)
        throw std::runtime_error("Invalid baseline save size");
    std::vector<std::uint8_t> bytes(static_cast<std::size_t>(size));
    input.read(reinterpret_cast<char*>(bytes.data()), static_cast<std::streamsize>(bytes.size()));
    if (!input)
        throw std::runtime_error("Unable to read baseline save");
    const bool baseline_header = std::string(bytes.begin(), bytes.begin() + 4) == "TOSB";
    if (!baseline_header && bytes.size() >= save_detail::OriginalSaveBytes) {
        save_detail::OriginalRecord record;
        // Original BlockRead consumes just these two fixed records, ignoring trailing data.
        const std::vector<std::uint8_t> original_bytes(bytes.begin(),
                                                       bytes.begin() + save_detail::OriginalSaveBytes);
        Game restored = save_detail::decode_original(original_bytes, record);
        restored.original_save_record_ = record;
        *this = std::move(restored);
        return;
    }
    std::size_t cursor = bytes.size() - 4;
    const auto expected = read_word(bytes, cursor);
    bytes.resize(bytes.size() - 4);
    if (checksum(bytes) != expected)
        throw std::runtime_error("Baseline save checksum mismatch");
    cursor = 4;
    if (std::string(bytes.begin(), bytes.begin() + 4) != "TOSB" || read_word(bytes, cursor) != 1)
        throw std::runtime_error("Unsupported baseline save version");
    if (std::string(bytes.begin() + 8, bytes.begin() + 72) != original::ImageHash)
        throw std::runtime_error("Baseline save uses a different original image");
    cursor = 72;
    Game restored;
    auto reader = [&](auto& value) {
        using T = std::remove_reference_t<decltype(value)>;
        const auto raw = static_cast<std::int32_t>(read_word(bytes, cursor));
        if constexpr (std::is_same_v<T, bool>) {
            if (raw != 0 && raw != 1)
                throw std::runtime_error("Invalid save flag");
        }
        if constexpr (std::is_same_v<T, std::uint8_t>) {
            if (raw < 0 || raw > 255)
                throw std::runtime_error("Invalid save byte");
        }
        value = static_cast<T>(raw);
    };
    fields(reader, restored);
    if (cursor != bytes.size())
        throw std::runtime_error("Unexpected baseline save data");
    save_detail::validate(restored);
    // Import earlier C++ snapshots using the same monster reconstruction as original .dat files.
    save_detail::reconstruct_monsters(restored);
    restored.contact_index = cell(restored.hero.x, restored.hero.y);
    restored.status = "Baseline save restored.";
    *this = std::move(restored); // A malformed file never partially changes the live game.
}
} // namespace baseline
