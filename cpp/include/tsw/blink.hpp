#pragma once
#include "tsw/game.hpp"
#include <functional>

namespace tsw {
// Whether an ordinary floor cell is free of hazards and queued movement effects.
// Stair cells are accepted only when testing the hero's starting position.
bool blink_floor(const Game&, int index, bool start = false);
// TSWH5-style: event-free floor only, optionally ending in one native contact.
// Adjacent clicks and routes without a safe approach fall back to ordinary walking.
std::vector<int> blink_path(const Game&, int destination);
bool blink_to(Game&, int destination, const std::function<void(Direction)>& move);
} // namespace tsw
