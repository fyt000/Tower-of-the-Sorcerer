#pragma once
#include "baseline/game.hpp"
#include "raylib.h"
#include <memory>

namespace baseline {
class Audio {
  public:
    Audio(const std::filesystem::path& assets, const std::filesystem::path& soundfont);
    ~Audio();
    Audio(const Audio&) = delete;
    Audio& operator=(const Audio&) = delete;
    void update(Game& game);
    void mute(bool muted);
    bool available() const;
    static int track_for_scene(const Game&);
    static bool verify_tracks(const std::filesystem::path& assets, const std::filesystem::path& soundfont);
    static bool render_test(const std::filesystem::path& midi, const std::filesystem::path& soundfont,
                            const std::filesystem::path& output);

  private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
} // namespace baseline
