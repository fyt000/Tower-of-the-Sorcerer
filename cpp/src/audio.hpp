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
    void suspend(bool suspended);
    void speed(float multiplier); // Effect density/tails only; music and pitch stay unchanged.
    bool available() const;
    static int track_for_scene(const Game&);

  private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
} // namespace tsw
