#include "tsw/collect.hpp"
#include "tsw/blink.hpp"
#include <algorithm>
#include <stdexcept>

namespace tsw {
namespace {
bool pickup(int tile, bool except_potions) {
    return tile >= YellowKey && tile <= SacredShield &&
           (!except_potions || (tile != RedPotion && tile != BluePotion));
}

std::vector<int> next_pickup(const Game& game, bool except_potions) {
    const int start = cell(game.hero.x, game.hero.y);
    std::array<int, CellCount> previous;
    previous.fill(-1);
    previous[start] = start;
    std::vector<int> queue{start};
    for (std::size_t i = 0; i < queue.size(); ++i) {
        for (const auto [dx, dy] : std::array<std::array<int, 2>, 4>{{{0, -1}, {-1, 0}, {1, 0}, {0, 1}}}) {
            const int x = queue[i] % BoardWidth + dx, y = queue[i] / BoardWidth + dy;
            if (x < 0 || x >= BoardWidth || y < 0 || y >= BoardWidth)
                continue;
            const int next = cell(x, y), tile = game.tile_at(game.hero.floor, x, y);
            if (previous[next] >= 0)
                continue;
            // Failed probes are also visited, so each tile is inspected once.
            previous[next] = queue[i];
            if (pickup(tile, except_potions)) {
                Game probe = game;
                probe.tile(probe.hero.floor, next) = Road;
                if (!blink_floor(probe, next))
                    continue;
                std::vector<int> path;
                for (int position = next; position != start; position = previous[position])
                    path.push_back(position);
                std::reverse(path.begin(), path.end());
                return path;
            }
            if (blink_floor(game, next))
                queue.push_back(next);
        }
    }
    return {};
}

Direction toward(int from, int to) {
    return to % BoardWidth < from % BoardWidth   ? Direction::Left
           : to % BoardWidth > from % BoardWidth ? Direction::Right
           : to < from                           ? Direction::Up
                                                 : Direction::Down;
}

bool trip(Game& game, const std::vector<int>& path, const std::function<void(Direction)>& move) {
    const int floor = game.hero.floor, start = cell(game.hero.x, game.hero.y);
    const auto step = [&](int next) {
        if (game.busy())
            return false;
        const auto direction = toward(cell(game.hero.x, game.hero.y), next);
        if (move)
            move(direction);
        else if (!game.move(direction))
            return false;
        game.finish_commands(); // Only validated pickup commands; never continue dialogue.
        return !game.busy() && game.hero.floor == floor && cell(game.hero.x, game.hero.y) == next;
    };
    for (const int next : path)
        if (!step(next))
            return false;
    for (std::size_t i = path.size(); i > 0; --i)
        if (!step(i == 1 ? start : path[i - 2]))
            return false;
    return true;
}
} // namespace

std::vector<CollectedItem> collect_items(Game& game, bool except_potions,
                                         const std::function<void(Direction)>& move) {
    const int start = cell(game.hero.x, game.hero.y);
    // Returning to a stair or hidden trigger would invoke it. Native landings use Road.
    if (!blink_floor(game, start))
        return {};
    std::vector<CollectedItem> collected;
    for (int count = 0; count < CellCount; ++count) {
        const auto path = next_pickup(game, except_potions);
        if (path.empty())
            break;
        const int position = path.back(), tile = game.tile(game.hero.floor, position);
        // Validate the entire round trip before any live inputs or recorder writes.
        Game probe = game;
        if (!trip(probe, path, {}))
            break;
        if (!trip(game, path, move))
            throw std::runtime_error("Collection route changed during execution");
        collected.push_back({position, tile});
    }
    return collected;
}
} // namespace tsw
