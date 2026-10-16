#include "planner_internal.hpp"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <numeric>
#include <ostream>
#include <set>
#include <sstream>
#include <stdexcept>
#include <tuple>

namespace tsw::planner {
using namespace detail;

namespace {
struct Metrics {
    Hero first11, first21;
    int merchant_spending{};
    std::int64_t margin{};
    std::string checkpoints;
};

bool key_trade(const Hero& before, const Hero& after) {
    return after.gold < before.gold &&
           (after.yellow_keys > before.yellow_keys || after.blue_keys > before.blue_keys ||
            after.red_keys > before.red_keys);
}

Metrics measure(const Route& route, std::ostream* report = nullptr) {
    Metrics result;
    Game game;
    int flight = -1;
    bool first11 = false, first21 = false;
    for (std::size_t i = 0; i < route.inputs.size(); ++i) {
        const auto old = game.hero;
        int contacted = -1;
        if (route.inputs[i].kind == InputKind::Move)
            contacted = neighbor(cell(old.x, old.y), route.inputs[i].direction);
        const int old_tile = contacted >= 0 ? game.tile(old.floor, contacted) : -1;
        apply_input(game, flight, route.inputs[i]);
        settle_action(game);
        const auto& h = game.hero;
        if (report && (old_tile == BlueDoor || old_tile == RedDoor) &&
            game.tile(old.floor, contacted) == Road)
            *report << "door input=" << i + 1 << " floor=" << old.floor << " xy=" << contacted % 11 << ','
                    << contacted / 11 << " color=" << (old_tile == BlueDoor ? "blue" : "red")
                    << " remaining=" << h.yellow_keys << '/' << h.blue_keys << '/' << h.red_keys << '\n';
        if ((!first11 && h.floor == 11) || (!first21 && h.floor == 21)) {
            if (h.floor == 11) {
                result.first11 = h;
                first11 = true;
            } else {
                result.first21 = h;
                first21 = true;
            }
            result.checkpoints += Engine{}.signature(game);
            if (report)
                *report << "milestone=" << h.floor << " input=" << i + 1 << " hp=" << h.hp
                        << " attack=" << h.attack << " defense=" << h.defense << " gold=" << h.gold
                        << " keys=" << h.yellow_keys << '/' << h.blue_keys << '/' << h.red_keys << '\n';
        }
        if (route.inputs[i].kind == InputKind::Choose && h.gold != old.gold &&
            h.altar_purchases == old.altar_purchases) {
            result.merchant_spending += std::max(0, old.gold - h.gold);
            if (report)
                *report << "merchant input=" << i + 1 << " floor=" << h.floor << " cost=" << old.gold - h.gold
                        << " keys_delta=" << h.yellow_keys - old.yellow_keys << '/'
                        << h.blue_keys - old.blue_keys << '/' << h.red_keys - old.red_keys
                        << " hp_delta=" << h.hp - old.hp << '\n';
        }
    }
    result.margin = route.game.hero.hp - route.game.forecast(Zeno).damage;
    if (report)
        *report << "merchant_spending=" << result.merchant_spending << " final_margin=" << result.margin
                << '\n';
    return result;
}

struct Candidate {
    Route route;
    Metrics metrics;
    std::string key;
};

std::vector<std::int64_t> resources(const Candidate& candidate) {
    const auto& m = candidate.metrics;
    const auto& h = candidate.route.game.hero;
    // No exchange rate between keys and gold. Each is an independent axis.
    std::vector<std::int64_t> result{m.margin,      h.hp,        h.attack,   h.defense,         h.gold,
                                     h.yellow_keys, h.blue_keys, h.red_keys, -h.altar_purchases};
    for (const auto* checkpoint : {&m.first11, &m.first21})
        for (int value : {checkpoint->hp, checkpoint->attack, checkpoint->defense, checkpoint->gold,
                          checkpoint->yellow_keys, checkpoint->blue_keys, checkpoint->red_keys})
            result.push_back(value);
    return result;
}

bool dominates_resources(const Candidate& a, const Candidate& b) {
    const auto x = resources(a), y = resources(b);
    for (std::size_t i = 0; i < x.size(); ++i)
        if (x[i] < y[i])
            return false;
    return true;
}

// Bounds are a heuristic choice, not a dominance proof across different boards.
// Keep the baseline plus representatives for each resource axis. In particular,
// a key-rich route may need another round before it can omit a purchase.
void trim(std::vector<Candidate>& candidates, int width) {
    if (candidates.size() <= std::size_t(width))
        return;
    constexpr int final_gold = 4, margin = 0, hp11 = 9, hp21 = 16;
    constexpr int blue21 = 21, yellow21 = 20, final_blue = 6, final_yellow = 5, gold11 = 12;
    const std::array<int, 9> axes{final_gold, margin,     hp11,         hp21,  blue21,
                                  yellow21,   final_blue, final_yellow, gold11};
    std::vector<std::vector<std::size_t>> lanes;
    std::vector<std::vector<std::int64_t>> values;
    for (const auto& c : candidates)
        values.push_back(resources(c));
    for (int axis : axes) {
        std::vector<std::size_t> order(candidates.size());
        std::iota(order.begin(), order.end(), 0);
        std::stable_sort(order.begin(), order.end(), [&](auto a, auto b) {
            return std::tuple{values[a][axis], values[a][margin], values[a][final_gold], values[a][hp21],
                              values[a][hp11]} > std::tuple{values[b][axis], values[b][margin],
                                                            values[b][final_gold], values[b][hp21],
                                                            values[b][hp11]};
        });
        lanes.push_back(std::move(order));
    }
    std::vector<bool> selected(candidates.size());
    std::vector<Candidate> kept;
    // The original is always retained. Search cannot silently discard the
    // known improvement merely because a different resource is easier to rank.
    selected[0] = true;
    kept.push_back(std::move(candidates[0]));
    for (std::size_t round = 0; kept.size() < std::size_t(width); ++round) {
        for (const auto& lane : lanes) {
            const auto index = lane[round];
            if (selected[index])
                continue;
            selected[index] = true;
            kept.push_back(std::move(candidates[index]));
            if (kept.size() == std::size_t(width))
                break;
        }
    }
    candidates = std::move(kept);
}

bool key_tile(int tile) {
    return tile == YellowKey || tile == BlueKey || tile == RedKey;
}

struct Snapshot {
    Game game;
    int flight;
};
} // namespace

void report_economy(const Route& route, std::ostream& report) {
    measure(route, &report);
    print_summary(route, report);
}

EconomyResult improve_economy(const Route& source, const EconomyOptions& options, std::ostream& progress) {
    if (!std::isfinite(options.seconds) || options.seconds <= 0 || options.rounds < 1 || options.width < 2)
        throw std::invalid_argument("Economy needs positive seconds/rounds and width at least two");
    std::ostringstream verification;
    verify_challenge(source.inputs, verification);
    const auto started = std::chrono::steady_clock::now();
    auto elapsed = [&] {
        return std::chrono::duration<double>(std::chrono::steady_clock::now() - started).count();
    };
    Engine engine;
    EconomyResult result;
    std::vector<Candidate> frontier{{source, measure(source), engine.signature(source.game)}};
    frontier[0].key += frontier[0].metrics.checkpoints;
    std::set<std::vector<PlayerInput>,
             bool (*)(const std::vector<PlayerInput>&, const std::vector<PlayerInput>&)>
        expanded([](const auto& a, const auto& b) {
            return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end(),
                                                [](const auto& x, const auto& y) {
                                                    return std::tie(x.kind, x.direction, x.item, x.value) <
                                                           std::tie(y.kind, y.direction, y.item, y.value);
                                                });
        });
    for (int round = 0; round < options.rounds; ++round) {
        auto next = frontier;
        for (const auto& parent : frontier) {
            if (!expanded.insert(parent.route.inputs).second)
                continue;
            const auto& original = parent.route.inputs;
            std::vector<Snapshot> timeline;
            timeline.reserve(original.size() + 1);
            Game game;
            int flight = -1;
            timeline.push_back({game, flight});
            for (const auto& action : original) {
                apply_input(game, flight, action);
                settle_action(game);
                timeline.push_back({game, flight});
            }
            auto attempt = [&](Route prefix, std::size_t split, const std::string& reason) {
                ++result.trials;
                try {
                    auto route = continue_route(original, prefix, split, true);
                    Candidate candidate{std::move(route), {}, {}};
                    candidate.metrics = measure(candidate.route);
                    candidate.key = engine.signature(candidate.route.game) + candidate.metrics.checkpoints;
                    // Only compare dominance within the same native board and
                    // progression state; equal key counts do not imply equal access.
                    for (const auto& old : next)
                        if (old.key == candidate.key && dominates_resources(old, candidate))
                            return;
                    std::ostringstream report;
                    verify_challenge(candidate.route.inputs, report);
                    // Keep the starting route at index zero as a named control.
                    std::erase_if(next, [&](const Candidate& old) {
                        return old.route.inputs != source.inputs && old.key == candidate.key &&
                               dominates_resources(candidate, old);
                    });
                    progress << "accepted round=" << round + 1 << ' ' << reason
                             << " hp11=" << candidate.metrics.first11.hp
                             << " hp21=" << candidate.metrics.first21.hp
                             << " gold=" << candidate.route.game.hero.gold
                             << " margin=" << candidate.metrics.margin
                             << " keys=" << candidate.route.game.hero.yellow_keys << '/'
                             << candidate.route.game.hero.blue_keys << '/'
                             << candidate.route.game.hero.red_keys << std::endl;
                    next.push_back(std::move(candidate));
                } catch (const std::runtime_error& error) {
                    ++result.rejected;
                    if (reason.starts_with("omit_trade="))
                        progress << "rejected " << reason << ' ' << error.what() << std::endl;
                } catch (const std::invalid_argument& error) {
                    ++result.rejected;
                    if (reason.starts_with("omit_trade="))
                        progress << "rejected " << reason << ' ' << error.what() << std::endl;
                }
            };
            auto prefix_at = [&](std::size_t at) {
                return Route{
                    timeline[at].game, {original.begin(), original.begin() + at}, timeline[at].flight};
            };
            // Trades are tested first, including those later in the campaign.
            // The native tail establishes whether the missing bundle was necessary.
            for (std::size_t i = 1; i < original.size(); ++i) {
                if (elapsed() >= options.seconds)
                    goto finished;
                if (original[i].kind != InputKind::Choose ||
                    !key_trade(timeline[i].game.hero, timeline[i + 1].game.hero))
                    continue;
                auto prefix = prefix_at(i);
                if (input(prefix.game, choose(-1), prefix.inputs))
                    attempt(std::move(prefix), i + 1, "omit_trade=" + std::to_string(i + 1));
            }
            for (std::size_t i = 1; i < original.size(); ++i) {
                if (elapsed() >= options.seconds)
                    goto finished;
                const auto& state = timeline[i];
                const auto& h = state.game.hero;
                if (h.floor < 1 || h.floor > 48 || state.flight != -1 || state.game.dialogue ||
                    state.game.busy())
                    continue;
                const auto& action = original[i];
                int target = -1, tile = -1;
                if (action.kind == InputKind::Move) {
                    target = neighbor(cell(h.x, h.y), action.direction);
                    if (target >= 0)
                        tile = state.game.tile(h.floor, target);
                }
                // Replace a door excursion with a road-only connection to a
                // later point. It can leave an entire optional room unopened.
                if (tile >= YellowDoor && tile <= RedDoor) {
                    const auto roads = engine.roads(state.game);
                    int previous_events = -1, events = 0;
                    for (std::size_t j = i + 1; j < std::min(original.size(), i + 241); ++j) {
                        const auto& end = timeline[j];
                        const auto& e = end.game.hero;
                        if (e.floor != h.floor || end.flight != -1 ||
                            (original[j - 1].kind != InputKind::Move &&
                             original[j - 1].kind != InputKind::Choose))
                            break;
                        const auto& before = timeline[j - 1].game;
                        if (before.floors != end.game.floors || before.hero.gold != e.gold)
                            ++events;
                        const int destination = cell(e.x, e.y);
                        if (end.game.dialogue || state.game.tile(h.floor, destination) != Road ||
                            roads.prev[destination] < 0 || events == previous_events)
                            continue;
                        previous_events = events;
                        auto prefix = prefix_at(i);
                        if (engine.walk(prefix.game, roads, destination, prefix.inputs))
                            attempt(std::move(prefix), j,
                                    "bypass=" + std::to_string(i + 1) + ":" + std::to_string(j));
                        if (elapsed() >= options.seconds)
                            goto finished;
                    }
                }
                // Decision points, not every walking square. Try each remaining
                // key, collecting road-accessible keys in its room, then return.
                const auto& before = timeline[i - 1].game.hero;
                if (before.floor == h.floor && before.attack == h.attack && before.defense == h.defense &&
                    !(action.kind == InputKind::Choose || (tile >= YellowDoor && tile <= RedDoor)))
                    continue;
                for (int p = 0; p < CellCount; ++p) {
                    if (elapsed() >= options.seconds)
                        goto finished;
                    if (!key_tile(state.game.tile(h.floor, p)))
                        continue;
                    auto prefix = prefix_at(i);
                    if (!engine.walk(prefix.game, engine.room_paths(prefix.game, p), p, prefix.inputs) ||
                        prefix.game.hero.floor != h.floor || prefix.game.dialogue)
                        continue;
                    for (int count = 0; count < CellCount; ++count) {
                        const auto roads = engine.roads(prefix.game);
                        int key = -1;
                        for (int q = 0; q < CellCount; ++q)
                            if (key_tile(prefix.game.tile(h.floor, q)) && roads.prev[q] >= 0) {
                                key = q;
                                break;
                            }
                        if (key < 0 || !engine.walk(prefix.game, roads, key, prefix.inputs))
                            break;
                    }
                    const auto& c = prefix.game.hero;
                    if (c.yellow_keys <= h.yellow_keys && c.blue_keys <= h.blue_keys &&
                        c.red_keys <= h.red_keys)
                        continue;
                    if (engine.walk(prefix.game, engine.roads(prefix.game), cell(h.x, h.y), prefix.inputs))
                        attempt(std::move(prefix), i,
                                "key_detour=" + std::to_string(i + 1) + "@" + std::to_string(h.floor) + ":" +
                                    std::to_string(p % 11) + "," + std::to_string(p / 11));
                }
            }
        }
        trim(next, options.width);
        frontier = std::move(next);
        result.rounds = round + 1;
        progress << "round=" << result.rounds << " retained=" << frontier.size()
                 << " trials=" << result.trials << " rejected=" << result.rejected << " seconds=" << elapsed()
                 << std::endl;
        continue;
    finished:
        trim(next, options.width);
        frontier = std::move(next);
        result.time_limit = true;
        break;
    }
    for (auto& candidate : frontier)
        result.routes.push_back(std::move(candidate.route));
    progress << "economy_trials=" << result.trials << " rejected=" << result.rejected
             << " retained=" << result.routes.size() << " completed_rounds=" << result.rounds
             << " time_limit=" << result.time_limit << " seconds=" << elapsed() << std::endl;
    return result;
}
} // namespace tsw::planner
