#pragma once
#include "audio.hpp"
#include "presentation.hpp"

namespace tsw {
// Shared desktop behavior, independent of native input polling and the window loop.
class DesktopSession {
  public:
    DesktopSession(const Assets& assets, const std::filesystem::path& save_directory, Game initial = {});
    Game game;
    DesktopUi ui;
    Presentation renderer;
    Audio audio;
    void dispatch(UiAction action);
    void advance_commands(float seconds);
    void move(Direction direction);

  private:
    std::filesystem::path save_directory_;
    float accumulator_{};
    std::string previous_dialogue_;
    void apply(UiAction action);
};
} // namespace tsw
