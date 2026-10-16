#pragma once
#include "tsw/game.hpp"
#include <span>

namespace tsw::detail::save {
inline constexpr std::size_t OriginalMapBytes = FloorCount * (CellCount + 2);
inline constexpr std::size_t OriginalSaveBytes = OriginalMapBytes + OriginalHeroWordCount * 4;
using OriginalRecord = std::array<std::uint32_t, OriginalHeroWordCount>;
void validate(const Game&);
void reconstruct_monsters(Game&);
void write_file(const std::filesystem::path&, std::span<const std::uint8_t>);
OriginalRecord hero_record(std::span<const std::uint8_t>);
Game decode_original(std::span<const std::uint8_t>, OriginalRecord&, SaveKind);
std::vector<std::uint8_t> encode_original(const Game&, const OriginalRecord*, SaveKind);
} // namespace tsw::detail::save
