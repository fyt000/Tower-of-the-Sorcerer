#pragma once
#include <cstdint>
#include <filesystem>
#include <vector>

namespace tsw {
enum class EmbeddedMedia : int { Soundfont = 101, EndingStory, EndingCard };
// Read the replacement's PE resources with standard file I/O, without Win32 calls.
std::vector<unsigned char> read_embedded_media(const std::filesystem::path&, EmbeddedMedia);
} // namespace tsw
