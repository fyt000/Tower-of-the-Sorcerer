#pragma once
#include "assets.hpp"
#include "tsw/game.hpp"
#include <memory>

namespace tsw {
class Audio {
  public:
    explicit Audio(const Assets& assets);
    ~Audio();
    Audio(const Audio&) = delete;
    Audio& operator=(const Audio&) = delete;
    void update(Game& game);
    void restart(Game& game); // Restart after new game/load, including the same track.
    void mute(bool muted);
    bool available() const;
    static int track_for_scene(const Game&);
    static bool verify_tracks(const Assets& assets);
    static bool verify_wave(const std::vector<unsigned char>& bytes);
    static bool verify_playback(const Assets& assets);
    static bool render_test(const Assets& assets, std::string_view midi, const std::filesystem::path& output);

  private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
} // namespace tsw
