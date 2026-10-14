#include "planner_internal.hpp"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <map>
#include <ostream>
#include <stdexcept>
#include <unordered_map>

namespace tsw::planner {
using namespace detail;

SearchResult search(const Route& source, const SearchOptions& options, std::ostream& progress) {
    if ((options.goal_floor != 11 && options.goal_floor != 21) || options.max_purchases < 0 ||
        options.width < 1 || options.depth < 1 || !std::isfinite(options.seconds) || options.seconds <= 0 ||
        options.max_results < 1 || options.policy < 0 || options.policy > 2)
        throw std::invalid_argument(
            "Search needs goal 11 or 21 and positive width, depth, seconds and results");
    if (source.flight != -1 || source.game.dialogue || source.game.busy())
        throw std::invalid_argument("Search root must be at an idle command boundary");
    if (source.game.hero.highest_floor >= options.goal_floor)
        throw std::invalid_argument("Search root already reached the goal");
    Policy policy;
    policy.goal = options.goal_floor;
    policy.max_purchases = options.max_purchases;
    policy.early_policy = options.policy;
    policy.reserve_early_potions = false;
    Engine engine(policy);
    Node root;
    root.game = source.game;
    auto initial = source.inputs;
    engine.normalize(root.game, initial);
    root.inputs = int(initial.size());
    root.history = std::make_shared<History>(History{nullptr, std::move(initial)});
    root.score = engine.rank(root.game);
    Node best = root;
    std::vector<Node> beam{std::move(root)}, goals;
    std::unordered_map<std::string, std::vector<Hero>> seen;
    SearchResult result;
    const auto started = std::chrono::steady_clock::now();
    int first_goal = -1;
    auto elapsed = [&] {
        return std::chrono::duration<double>(std::chrono::steady_clock::now() - started).count();
    };
    for (int depth = 0; depth < options.depth && !beam.empty(); ++depth) {
        std::vector<Node> next;
        std::unordered_map<std::string, std::vector<Hero>> layer_seen;
        for (const auto& parent : beam) {
            if (elapsed() >= options.seconds) {
                result.time_limit = true;
                break;
            }
            for (auto& child : engine.expand(parent)) {
                const auto key = engine.signature(child.game);
                const auto& h = child.game.hero;
                if (child.score > best.score)
                    best = child;
                const auto old = seen.find(key);
                auto& frontier = layer_seen[key];
                if ((old != seen.end() &&
                     std::ranges::any_of(old->second, [&](const Hero& p) { return dominates(p, h); })) ||
                    std::ranges::any_of(frontier, [&](const Hero& p) { return dominates(p, h); }))
                    continue;
                std::erase_if(frontier, [&](const Hero& p) { return dominates(h, p); });
                frontier.push_back(h);
                if (h.highest_floor >= options.goal_floor) {
                    if (first_goal < 0)
                        first_goal = depth;
                    goals.push_back(std::move(child));
                } else {
                    next.push_back(std::move(child));
                }
            }
        }
        std::stable_sort(next.begin(), next.end(),
                         [](const Node& a, const Node& b) { return a.score > b.score; });
        // Round-robin purchase histories and reached floors. A high score in one
        // stat allocation must not consume the entire bounded frontier.
        if (next.size() > std::size_t(options.width)) {
            std::map<std::pair<std::uint64_t, int>, std::vector<std::size_t>> groups;
            for (std::size_t i = 0; i < next.size(); ++i)
                groups[{next[i].allocation, next[i].game.hero.highest_floor}].push_back(i);
            std::vector<std::vector<std::size_t>> lanes;
            for (const auto& [key, indices] : groups) {
                lanes.push_back(indices);
                auto survival = indices;
                std::stable_sort(survival.begin(), survival.end(), [&](auto a, auto b) {
                    const auto& x = next[a].game.hero;
                    const auto& y = next[b].game.hero;
                    return x.hp + x.gold * .3 > y.hp + y.gold * .3;
                });
                lanes.push_back(std::move(survival));
            }
            std::vector<bool> selected(next.size());
            std::vector<Node> retained;
            for (std::size_t round = 0; retained.size() < std::size_t(options.width); ++round) {
                bool available = false;
                for (const auto& indices : lanes) {
                    if (round >= indices.size())
                        continue;
                    available = true;
                    const auto index = indices[round];
                    if (selected[index])
                        continue;
                    selected[index] = true;
                    retained.push_back(std::move(next[index]));
                    if (retained.size() == std::size_t(options.width))
                        break;
                }
                if (!available)
                    break;
            }
            next = std::move(retained);
        }
        beam = std::move(next);
        // Discarded beam candidates never suppress an unexplored later branch.
        for (const auto& node : beam) {
            auto& frontier = seen[engine.signature(node.game)];
            std::erase_if(frontier, [&](const Hero& p) { return dominates(node.game.hero, p); });
            frontier.push_back(node.game.hero);
        }
        result.layers = depth + 1;
        if (depth % 5 == 0 || !goals.empty() || result.time_limit)
            progress << "layer=" << depth + 1 << " beam=" << beam.size()
                     << " evaluated=" << engine.evaluations << " goals=" << goals.size()
                     << " seconds=" << elapsed() << std::endl;
        if (result.time_limit || (first_goal >= 0 && depth >= first_goal + 8))
            break;
    }
    std::stable_sort(goals.begin(), goals.end(),
                     [](const Node& a, const Node& b) { return a.score > b.score; });
    if (goals.size() > std::size_t(options.max_results))
        goals.resize(options.max_results);
    for (const auto& goal : goals)
        result.goals.push_back({goal.game, history(goal)});
    result.best_partial = {best.game, history(best)};
    result.evaluated = engine.evaluations;
    result.rejected = engine.rejects;
    return result;
}
} // namespace tsw::planner
