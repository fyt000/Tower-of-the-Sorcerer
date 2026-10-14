#pragma once
#include "tsw/game.hpp"
#include <functional>

namespace tsw {
// Cell indices after the hero's position, ending with one contact on the selected cell.
// Only apparent floor is traversed; hidden walls have the same reachability as ordinary walls.
std::vector<int> mouse_path(const Game&, int destination);

class MouseWalk {
  public:
    static constexpr float StepSeconds = .14f;
    void start(const Game&, int destination);
    void cancel();
    bool active() const;
    // Dispatch at most one native movement input, then stop immediately on any event or hazard.
    void advance(Game&, float seconds, const std::function<void(Direction)>& move);

  private:
    std::vector<int> path_;
    std::size_t step_{};
    int floor_{}, position_{};
    float remaining_{};
};
} // namespace tsw
