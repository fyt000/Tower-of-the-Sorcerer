#include "original_constants.hpp"
#include "save_internal.hpp"
#include <bit>
#include <stdexcept>
#include <tuple>
#include <type_traits>

namespace tsw::save_detail {
namespace {
// Byte offsets in the original hero record, verified against its handlers and x86 save/load loops.
enum Field : std::size_t {
    Items = 68,
    Equipment = 128,
    Merchants = 168,
    Merchant2Heard = 216,
    FairyScore = 340,
    FairyRank = 344,
    FairyCategory = 348,
    Facing = 352,
    Music = 360,
    DialogueBase = 320,
    FirstDialogue = 11,
    Reward34 = 592,
    Reward35 = 596,
    Reward40 = 600,
    Reward41 = 616,
    Arrival32 = 620,
    ZenoSealed = 624,
    Sentinel = 628,
    FlightDirection = 632,
    Cycle = 636,
    LaterCycle = 640,
    Sum = 656,
    AlternatingSum = 660,
    HighestStair = 664
};

constexpr std::uint32_t OriginalSentinel = std::uint32_t(-4);
constexpr std::array<std::size_t, 24> ClueOffsets{272, 276, 220, 224, 228, 236, 280, 288, 292, 296, 300, 244,
                                                  304, 308, 312, 248, 316, 252, 320, 324, 256, 328, 260, 332};
constexpr std::array<std::size_t, 3> HeardOffsets{264, 268, 284};

std::pair<std::uint32_t, std::uint32_t> sums(const OriginalRecord& words) {
    std::uint32_t sum{}, alternating{};
    for (std::size_t i = 0; i < Sum / 4; ++i) {
        sum += words[i]; // Delphi's signed ADD/SUB wrap at 32 bits.
        alternating += i % 2 ? 0u - words[i] : words[i];
    }
    return {sum, alternating};
}

template <class Archive> void fields(Archive& archive, Hero& h) {
    auto scalars = std::tie(h.hp, h.attack, h.defense, h.gold, h.floor, h.highest_floor, h.x, h.y,
                            h.yellow_keys, h.red_keys, h.blue_keys, h.altar_purchases);
    std::size_t offset{};
    std::apply([&](auto&... values) { ((archive(offset, values), offset += 4), ...); }, scalars);
    archive(56, h.fairy_visits);
    archive(60, h.sword);
    archive(64, h.shield);
    for (std::size_t i = 0; i < h.items.size(); ++i)
        archive(Items + 4 * i, h.items[i]);
    for (std::size_t i = 0; i < h.equipment_found.size(); ++i)
        archive(Equipment + 4 * i, h.equipment_found[i]);
    for (std::size_t i = 0; i < h.merchant_used.size(); ++i)
        archive(Merchants + 4 * i, h.merchant_used[i]);
    for (std::size_t i = 0; i < h.wisdom_hints.size(); ++i)
        archive(ClueOffsets[i], h.wisdom_hints[i]);
    for (std::size_t i = 0; i < h.old_man_heard.size(); ++i)
        archive(HeardOffsets[i], h.old_man_heard[i]);
    archive(Merchant2Heard, h.merchant2_heard);
    // Earlier indices are aliases for clues, Fairy state and facing, not dialogue flags.
    for (std::size_t i = FirstDialogue; i < h.dialogue_seen.size(); ++i)
        archive(DialogueBase + 4 * i, h.dialogue_seen[i]);
    archive(FairyScore, h.fairy_score);
    archive(FairyRank, h.fairy_rank);
    archive(FairyCategory, h.fairy_category);
    archive(Facing, h.facing);
    archive(Music, h.music_track);
    archive(Reward34, h.floor34_reward_created);
    archive(Reward35, h.floor35_reward_created);
    archive(Reward40, h.floor40_reward_created);
    archive(Reward41, h.floor41_reward_created);
    archive(Arrival32, h.floor32_arrival_seen);
    archive(ZenoSealed, h.zeno_sealed);
    archive(FlightDirection, h.flight_direction);
    archive(HighestStair, h.highest_floor_stair);
    archive(Cycle, h.cycle_factor_minus_one);
    archive(LaterCycle, h.later_cycle);
}
} // namespace

void reconstruct_monsters(Game& game) {
    game.monsters = original::Monsters;
    // 0x455B49: reproduce the original load-time reconstruction, including its backside scaling.
    if (game.hero.zeno_sealed) {
        const int factor = game.hero.cycle_factor_minus_one + 1;
        game.monsters[ZenoRow] = {800 * factor, 500 * factor, 100 * factor, game.monsters[ZenoRow].gold};
    }
}

OriginalRecord hero_record(const std::vector<std::uint8_t>& bytes) {
    if (bytes.size() != OriginalSaveBytes)
        throw std::runtime_error("Original save must contain exactly 6957 bytes");
    OriginalRecord record;
    for (std::size_t i = 0; i < record.size(); ++i) {
        const auto offset = OriginalMapBytes + i * 4;
        record[i] = std::uint32_t(bytes[offset]) | std::uint32_t(bytes[offset + 1]) << 8 |
                    std::uint32_t(bytes[offset + 2]) << 16 | std::uint32_t(bytes[offset + 3]) << 24;
    }
    return record;
}

Game decode_original(const std::vector<std::uint8_t>& bytes, OriginalRecord& record, SaveKind kind) {
    record = hero_record(bytes);
    if (kind == SaveKind::Slot) {
        const auto [sum, alternating] = sums(record);
        if (record[Sentinel / 4] != OriginalSentinel || record[Sum / 4] != sum ||
            record[AlternatingSum / 4] != alternating)
            throw std::runtime_error("Original save sentinel or checksum mismatch");
    }
    Game game;
    std::size_t cursor{};
    for (auto& floor : game.floors) {
        floor.up_landing = bytes[cursor++];
        floor.down_landing = bytes[cursor++];
        for (auto& tile : floor.tiles)
            tile = bytes[cursor++];
    }
    auto reader = [&](std::size_t offset, auto& value) {
        using T = std::remove_reference_t<decltype(value)>;
        const auto raw = std::bit_cast<std::int32_t>(record[offset / 4]);
        if constexpr (std::is_same_v<T, bool>)
            if (raw != 0 && raw != 1)
                throw std::runtime_error("Invalid original save flag");
        value = static_cast<T>(raw);
    };
    fields(reader, game.hero);
    if (game.hero.cycle_factor_minus_one != 0 && game.hero.cycle_factor_minus_one != 43)
        throw std::runtime_error("Invalid original save cycle");
    reconstruct_monsters(game);
    validate(game);
    game.contact_index = cell(game.hero.x, game.hero.y);
    game.status = kind == SaveKind::Checkpoint ? "Fairy checkpoint restored." : "Original save restored.";
    return game;
}

std::vector<std::uint8_t> encode_original(const Game& game, const OriginalRecord* preserved, SaveKind kind) {
    if (game.busy())
        throw std::runtime_error("Finish the current action before saving");
    validate(game);
    OriginalRecord record = preserved ? *preserved : OriginalRecord{};
    auto hero = game.hero;
    auto writer = [&](std::size_t offset, const auto& value) {
        record[offset / 4] = static_cast<std::uint32_t>(value);
    };
    fields(writer, hero);
    if (!preserved || kind == SaveKind::Slot)
        record[Sentinel / 4] = OriginalSentinel;
    // 0x47ADE1: Fairy writes the two records directly, without refreshing checksum words.
    if (kind == SaveKind::Slot) {
        const auto [sum, alternating] = sums(record);
        record[Sum / 4] = sum;
        record[AlternatingSum / 4] = alternating;
    }
    std::vector<std::uint8_t> bytes;
    bytes.reserve(OriginalSaveBytes);
    for (const auto& floor : game.floors) {
        bytes.push_back(floor.up_landing);
        bytes.push_back(floor.down_landing);
        bytes.insert(bytes.end(), floor.tiles.begin(), floor.tiles.end());
    }
    for (const auto word : record)
        for (int byte = 0; byte < 4; ++byte)
            bytes.push_back(static_cast<std::uint8_t>(word >> (8 * byte)));
    return bytes;
}
} // namespace tsw::save_detail
