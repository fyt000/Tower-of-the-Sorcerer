#include "tsw/replay.hpp"
#include <stdexcept>
#include <utility>

namespace tsw {
ReplayPlayer::ReplayPlayer(std::vector<PlayerInput> inputs) : inputs_(std::move(inputs)) {
    if (inputs_.empty() || inputs_.front().kind != InputKind::NewGame)
        throw std::runtime_error("A visual replay must begin with a new game command");
}

bool ReplayPlayer::next(Game& game, int& flight) {
    if (finished())
        return false;
    apply_input(game, flight, inputs_[position_]);
    ++position_;
    return true;
}

void ReplayPlayer::seek(Game& game, int& flight, std::size_t position, const InputObserver& observer) {
    if (position > inputs_.size())
        throw std::out_of_range("Replay step is outside this recording");
    Game restored;
    int restored_flight = -1;
    for (std::size_t i = 0; i < position; ++i) {
        try {
            const auto outcome = execute_input(restored, restored_flight, inputs_[i]);
            if (observer)
                observer(inputs_[i], outcome);
        } catch (const std::exception& error) {
            throw std::runtime_error("Replay input " + std::to_string(i + 1) + ": " + error.what());
        }
    }
    game = std::move(restored);
    flight = restored_flight;
    position_ = position;
}
} // namespace tsw
