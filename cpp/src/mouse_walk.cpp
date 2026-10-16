#include "tsw/mouse_walk.hpp"
#include <algorithm>

namespace tsw {
namespace {
bool apparent_floor(int tile) {
    return tile == Road || tile == SpecialRoad;
}
} // namespace

std::vector<int> mouse_path(const Game& game, int destination) {
    if (destination < 0 || destination >= CellCount || game.busy())
        return {};
    const auto& hero = game.hero;
    const int start = cell(hero.x, hero.y);
    std::array<int, CellCount> previous;
    previous.fill(-1);
    previous[start] = start;
    std::vector<int> queue{start};
    for (std::size_t i = 0; i < queue.size(); ++i) {
        const int current = queue[i];
        if (current == destination)
            break;
        for (const auto [dx, dy] : std::array<std::array<int, 2>, 4>{{{0, -1}, {-1, 0}, {1, 0}, {0, 1}}}) {
            const int x = current % BoardWidth + dx, y = current / BoardWidth + dy;
            if (x < 0 || x >= BoardWidth || y < 0 || y >= BoardWidth)
                continue;
            const int next = cell(x, y);
            if (previous[next] >= 0 || (next != destination && !apparent_floor(game.tile(hero.floor, next))))
                continue;
            previous[next] = current;
            queue.push_back(next);
        }
    }
    if (previous[destination] < 0)
        return {};
    std::vector<int> path;
    for (int next = destination; next != start; next = previous[next])
        path.push_back(next);
    std::reverse(path.begin(), path.end());
    return path;
}

void MouseWalk::start(const Game& game, int destination) {
    cancel();
    path_ = mouse_path(game, destination);
    floor_ = game.hero.floor;
    position_ = cell(game.hero.x, game.hero.y);
}

void MouseWalk::cancel() {
    path_.clear();
    step_ = 0;
    remaining_ = 0;
}

bool MouseWalk::active() const {
    return step_ < path_.size();
}

void MouseWalk::advance(Game& game, float seconds, const std::function<void(Direction)>& move) {
    if (!active())
        return;
    if (game.busy() || game.hero.floor != floor_ || cell(game.hero.x, game.hero.y) != position_) {
        cancel();
        return;
    }
    remaining_ -= std::max(0.f, seconds);
    if (remaining_ > 0)
        return;
    const int next = path_[step_];
    const int tile = game.tile(floor_, next);
    const bool final = step_ + 1 == path_.size();
    // A changed route must not contact an event that the player did not select.
    if (!final && !apparent_floor(tile)) {
        cancel();
        return;
    }
    const int dx = next % BoardWidth - game.hero.x, dy = next / BoardWidth - game.hero.y;
    const Direction direction = dx < 0   ? Direction::Left
                                : dx > 0 ? Direction::Right
                                : dy < 0 ? Direction::Up
                                         : Direction::Down;
    move(direction);
    // Check before draining commands: even a hidden trigger with no remaining speech must stop us.
    // Door and secret-wall contact is deliberately one input, without a second step into the opening.
    if (final || tile != Road || game.busy() || game.hero.floor != floor_ ||
        cell(game.hero.x, game.hero.y) != next) {
        cancel();
        return;
    }
    ++step_;
    position_ = next;
    remaining_ = StepSeconds;
}
} // namespace tsw
