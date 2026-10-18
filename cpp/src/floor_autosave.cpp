#include "tsw/replay.hpp"
#include "tsw/save_slots.hpp"

namespace tsw {
void FloorAutosave::reset(const Game& game, bool save_current) {
    floor_ = game.hero.floor;
    cycle_ = game.hero.cycle_factor_minus_one;
    later_cycle_ = game.hero.later_cycle;
    pending_ = save_current;
}

bool FloorAutosave::update(Game& game, Recorder& recorder, const std::filesystem::path& directory,
                           bool ready) {
    if (floor_ != game.hero.floor || cycle_ != game.hero.cycle_factor_minus_one ||
        later_cycle_ != game.hero.later_cycle)
        reset(game, true);
    if (!pending_ || !ready || game.busy())
        return false;
    // One attempt per visit, including failures, so a bad directory cannot retry every frame.
    pending_ = false;
    recorder.save(game, floor_autosave_path(directory));
    return true;
}
} // namespace tsw
