#pragma once
#include "assets.hpp"
#include "tsw/game.hpp"
#include <memory>

namespace tsw {
inline constexpr int AudioSampleRate = 44100;

// Prepares assets once; the device thread owns synthesis and effect playback.
class AudioMixer {
  public:
    explicit AudioMixer(const Assets& assets);
    ~AudioMixer();
    AudioMixer(const AudioMixer&) = delete;
    AudioMixer& operator=(const AudioMixer&) = delete;
    void update(Game& game);
    void restart(Game& game);
    void mute(bool muted);
    void suspend(bool suspended); // Freeze music and effects for visual replay pause.
    void speed(float multiplier); // Above 1x, reduce repeated effects and fade long tails sooner.
    // Stereo floats. Called by one consumer; no allocation, I/O or mutex.
    void render(float* output, int frames);
    static int track_for_scene(const Game& game);

  private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
} // namespace tsw
