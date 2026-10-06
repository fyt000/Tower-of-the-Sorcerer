#pragma once
#include "baseline/game.hpp"

namespace baseline::save_detail {
inline constexpr std::size_t OriginalMapBytes = FloorCount * (CellCount + 2);
inline constexpr std::size_t OriginalSaveBytes = OriginalMapBytes + OriginalHeroWordCount * 4;
using OriginalRecord = std::array<std::uint32_t, OriginalHeroWordCount>;
void validate(const Game&);
void reconstruct_monsters(Game&);
void write_file(const std::filesystem::path&, const std::vector<std::uint8_t>&);
Game decode_original(const std::vector<std::uint8_t>&, OriginalRecord&);
std::vector<std::uint8_t> encode_original(const Game&, const OriginalRecord*);
} // namespace baseline::save_detail
