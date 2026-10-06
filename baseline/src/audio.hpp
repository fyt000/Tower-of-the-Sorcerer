#pragma once
#include "assets.hpp"
#include "baseline/game.hpp"
#include "raylib.h"
#include <memory>

namespace baseline {
class Audio {
  public:
    explicit Audio(const Assets& assets);
    ~Audio();
    Audio(const Audio&) = delete;
    Audio& operator=(const Audio&) = delete;
    void update(Game& game);
    void mute(bool muted);
    bool available() const;
    static int track_for_scene(const Game&);
    static bool verify_tracks(const Assets& assets);
    static bool render_test(const Assets& assets, std::string_view midi, const std::filesystem::path& output);

  private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
} // namespace baseline
