#pragma once
#include "audio.hpp"
#include "presentation.hpp"
#include "tsw/replay.hpp"

namespace tsw {
// Shared desktop behavior, independent of native input polling and the window loop.
class DesktopSession {
  public:
    DesktopSession(const Assets& assets, const std::filesystem::path& save_directory, Game initial = {},
                   bool record = false);
    Game game;
    DesktopUi ui;
    Presentation renderer;
    Audio audio;
    void dispatch(UiAction action);
    void advance_commands(float seconds);
    void move(Direction direction);
    void load(const std::filesystem::path&, SaveKind = SaveKind::Slot);

  private:
    std::filesystem::path save_directory_;
    Recorder recorder_;
    float accumulator_{};
    std::string previous_dialogue_;
    void apply(UiAction action);
    bool play(const PlayerInput&);
    void recording_status();
};
} // namespace tsw
