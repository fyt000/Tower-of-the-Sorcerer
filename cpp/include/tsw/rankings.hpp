#pragma once
#include <array>
#include <cstdint>
#include <filesystem>
#include <string>

namespace tsw {
inline constexpr int RankingCategoryCount = 5;
inline constexpr int RankingEntryCount = 10;
inline constexpr int RankingNameLimit = 18;

struct RankingEntry {
    std::int32_t score{}, hp{}, attack{}, defense{};
    std::string name;
    friend bool operator==(const RankingEntry&, const RankingEntry&) = default;
};

using RankingTable = std::array<RankingEntry, RankingEntryCount>;
using RankingTables = std::array<RankingTable, RankingCategoryCount>;

RankingTable default_rankings(int category);
RankingTables default_rankings();
// Positions are one-based; zero means the entry does not enter the top ten.
int ranking_position(const RankingTable&, const RankingEntry&) noexcept;
// Insert at a previously calculated position. Names occupy at most 18 bytes.
void insert_ranking(RankingTable&, int position, RankingEntry);
// Missing or invalid numeric/name data restores the complete default table.
RankingTable load_rankings(const std::filesystem::path& directory, int category);
RankingTables load_rankings(const std::filesystem::path& directory);
void write_rankings(const std::filesystem::path& directory, int category, const RankingTable&);
RankingTable reset_rankings(const std::filesystem::path& directory, int category);
} // namespace tsw
