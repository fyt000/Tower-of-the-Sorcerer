#pragma once
#include "raylib.h"
#include <array>
#include <filesystem>
#include <string_view>
#include <vector>

namespace tsw {
inline constexpr std::array<std::string_view, 29> SceneImageNames{
    "data3-left",    "data3-leftr",    "data3-center",          "data3-right",         "data3-rightr",
    "data3-title05", "data3-title05r", "data3-open0",           "data3-open1",         "data3-open2",
    "data2-end05",   "data2-end06",    "data2-end07",           "data2-end08",         "data2-end09",
    "data2-end10",   "data2-end11",    "data2-end12",           "data2-end13",         "data2-end14",
    "data2-end15",   "data2-end16",    "data2-end17",           "data2-end18",         "data2-end19",
    "data2-end20",   "data2-end26",    "data-exe-ending-story", "data-exe-ending-card"};

// One source directory, in either the original layout or the older extracted PNG layout.
class Assets {
  public:
    Assets(const std::filesystem::path& root, const std::filesystem::path& executable);

    bool original_layout() const { return original_; }

    const std::filesystem::path& root() const { return root_; }

    Image image(std::string_view name) const; // Caller owns the raylib image.
    std::vector<unsigned char> midi(std::string_view name) const;
    std::vector<unsigned char> wave(std::string_view name) const;
    std::vector<unsigned char> soundfont() const;
    static bool exists(const std::filesystem::path& root);
    static std::filesystem::path select(const std::filesystem::path& executable_directory,
                                        const std::filesystem::path& requested,
                                        const std::filesystem::path& development_original,
                                        const std::filesystem::path& development_extracted);

  private:
    std::filesystem::path root_, executable_;
    bool original_{};
};
} // namespace tsw
