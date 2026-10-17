#include "tsw/blink.hpp"
#include <algorithm>
#include <cstdlib>

namespace tsw {
// Ask native movement whether this floor cell is free of hazards and queued effects.
// The probe is disposable: it never drains commands or changes the live game.
bool blink_floor(const Game& game, int index, bool start) {
    if (index < 0 || index >= CellCount || game.busy())
        return false;
    const int tile = game.tile(game.hero.floor, index);
    if (tile != Road && !(start && (tile == StairsUp || tile == StairsDown)))
        return false;
    Game probe = game;
    probe.tile(probe.hero.floor, index) = Road;
    const int x = index % BoardWidth, y = index / BoardWidth;
    probe.hero.x = x == 0 ? 1 : x - 1;
    probe.hero.y = y;
    return probe.move(x == 0 ? Direction::Left : Direction::Right) && !probe.busy();
}

namespace {
Direction toward(int from, int to) {
    return to % BoardWidth < from % BoardWidth   ? Direction::Left
           : to % BoardWidth > from % BoardWidth ? Direction::Right
           : to < from                           ? Direction::Up
                                                 : Direction::Down;
}
} // namespace

std::vector<int> blink_path(const Game& game, int destination) {
    if (destination < 0 || destination >= CellCount || game.busy())
        return {};
    const int start = cell(game.hero.x, game.hero.y);
    if (std::abs(destination % BoardWidth - game.hero.x) + std::abs(destination / BoardWidth - game.hero.y) <=
            1 ||
        !blink_floor(game, start, true))
        return {};
    std::array<int, CellCount> previous, safe;
    previous.fill(-1);
    safe.fill(-1);
    previous[start] = start;
    std::vector<int> queue{start};
    for (std::size_t i = 0; i < queue.size(); ++i) {
        const int current = queue[i];
        for (const auto [dx, dy] : std::array<std::array<int, 2>, 4>{{{0, -1}, {-1, 0}, {1, 0}, {0, 1}}}) {
            const int x = current % BoardWidth + dx, y = current / BoardWidth + dy;
            if (x < 0 || x >= BoardWidth || y < 0 || y >= BoardWidth)
                continue;
            const int next = cell(x, y);
            if (previous[next] >= 0)
                continue;
            if (safe[next] < 0)
                safe[next] = blink_floor(game, next);
            if (!safe[next])
                continue;
            previous[next] = current;
            queue.push_back(next);
        }
    }
    int approach = destination;
    if (previous[destination] < 0) {
        approach = -1;
        // TSWH5 tries the destination, then its left, upper, lower and right neighbors.
        for (const auto [dx, dy] : std::array<std::array<int, 2>, 4>{{{-1, 0}, {0, -1}, {0, 1}, {1, 0}}}) {
            const int x = destination % BoardWidth + dx, y = destination / BoardWidth + dy;
            if (x >= 0 && x < BoardWidth && y >= 0 && y < BoardWidth && previous[cell(x, y)] >= 0) {
                approach = cell(x, y);
                break;
            }
        }
        if (approach < 0)
            return {};
    }
    std::vector<int> path;
    for (int next = approach; next != start; next = previous[next])
        path.push_back(next);
    std::reverse(path.begin(), path.end());
    if (approach != destination)
        path.push_back(destination);
    return path;
}

bool blink_to(Game& game, int destination, const std::function<void(Direction)>& move) {
    const auto path = blink_path(game, destination);
    if (path.empty())
        return false;
    const int floor = game.hero.floor;
    for (std::size_t i = 0; i < path.size(); ++i) {
        const int next = path[i];
        if (game.busy() || game.hero.floor != floor || (i + 1 < path.size() && !blink_floor(game, next)))
            break;
        move(toward(cell(game.hero.x, game.hero.y), next));
        // The last input is an ordinary contact; never enter an opened door automatically.
        if (game.busy() || game.hero.floor != floor || cell(game.hero.x, game.hero.y) != next)
            break;
    }
    return true;
}
} // namespace tsw
