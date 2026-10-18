#pragma once
#include "audio.hpp"
#include "presentation.hpp"
#include "tsw/replay.hpp"

namespace tsw {
// Shared desktop behavior, independent of native input polling and the window loop.
class DesktopSession {
  public:
    DesktopSession(const Assets& assets, const std::filesystem::path& save_directory, Game initial = {},
                   std::optional<bool> record = {});
    Game game;
    DesktopUi ui;
    Presentation renderer;
    Audio audio;
    void dispatch(UiAction action);
    void advance_commands(float seconds);
    void move(Direction direction);
    void load(const std::filesystem::path&, SaveKind = SaveKind::Slot);
    void open_home(bool startup = false);
    void replay(const std::filesystem::path&);
    float scaled_seconds(float real_seconds) const;

  private:
    std::filesystem::path save_directory_;
    Recorder recorder_;
    std::optional<ReplayPlayer> replay_;
    bool replay_action_{}, replay_single_step_{};
    float replay_age_{}, replay_speech_{};
    std::size_t replay_commands_{};
    float accumulator_{};
    std::string previous_dialogue_;
    MouseWalk mouse_walk_;
    void move_step(Direction direction, bool manual = false);
    void apply(UiAction action);
    bool play(const PlayerInput&);
    void recording_status();
    void preferences();
    bool advance_queue(float seconds);
    void advance_replay(float seconds);
    void seek_replay(std::size_t step);
    void refresh_rankings();
    void open_rankings(bool submission = false);
};
} // namespace tsw
