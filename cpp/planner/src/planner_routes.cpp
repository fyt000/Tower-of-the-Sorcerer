#include "planner_internal.hpp"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <fstream>
#include <map>
#include <ostream>
#include <sstream>
#include <stdexcept>

namespace tsw::planner {
using namespace detail;

namespace {
void living_first_cycle(const Game& game) {
    if (game.visual.dead || game.hero.hp <= 0 || game.hero.cycle_factor_minus_one || game.hero.later_cycle)
        throw std::runtime_error("Route died or left the first cycle");
}

int coordinate(std::istringstream& command) {
    int value = -1;
    if (!(command >> value) || value < 0 || value >= BoardWidth)
        throw std::runtime_error("Coordinates must be integers from 0 to 10");
    return value;
}

bool stat_pickup(int tile) {
    return tile == RedGem || tile == BlueGem || (tile >= IronSword && tile <= HolyShield);
}

bool bypass_door(Route& route, Route& reference, std::span<const PlayerInput> original, std::size_t& index,
                 int door, const Engine& engine) {
    auto ahead = reference;
    const int floor = reference.game.hero.floor;
    // A following fight/pickup must be executed, never skipped. Shops, stairs
    // and item uses remain explicit continuation boundaries.
    for (std::size_t j = index + 1; j < std::min(original.size(), index + 9); ++j) {
        const auto& step = original[j];
        if (step.kind != InputKind::Move)
            break;
        const auto old = ahead.game.hero;
        const int target = neighbor(cell(old.x, old.y), step.direction);
        if (target < 0)
            break;
        const int intent = ahead.game.tile(old.floor, target);
        const bool event = intent != Road;
        if (event && !((intent >= YellowKey && intent <= BlueGem) || Game::monster_for_tile(intent) >= 0))
            break;
        apply_input(ahead.game, ahead.flight, step);
        settle_action(ahead.game);
        if (ahead.game.hero.floor != floor)
            break;
        const int goal = cell(ahead.game.hero.x, ahead.game.hero.y);
        if (event && goal != target)
            break;
        auto alternate = route;
        if (!engine.walk(alternate.game, engine.room_paths(alternate.game, goal, door), goal,
                         alternate.inputs) ||
            alternate.game.hero.floor != floor ||
            cell(alternate.game.hero.x, alternate.game.hero.y) != goal) {
            if (event)
                break;
            continue;
        }
        living_first_cycle(alternate.game);
        route = std::move(alternate);
        reference = std::move(ahead);
        index = j;
        return true;
    }
    return false;
}
} // namespace

Route replay(std::span<const PlayerInput> inputs) {
    if (inputs.empty() || inputs.front().kind != InputKind::NewGame)
        throw std::invalid_argument("Replay must begin with new_game");
    Route route;
    for (std::size_t i = 0; i < inputs.size(); ++i) {
        const auto& action = inputs[i];
        if ((i && action.kind == InputKind::NewGame) || action.kind == InputKind::Reload ||
            action.kind == InputKind::Rankings)
            throw std::invalid_argument("Replay resets, reloads and external ranking inputs are unsupported");
        apply_input(route.game, route.flight, action);
        settle_action(route.game);
        living_first_cycle(route.game);
        route.inputs.push_back(action);
    }
    return route;
}

void print_summary(const Route& route, std::ostream& output) {
    const auto& h = route.game.hero;
    output << "inputs=" << route.inputs.size() << " floor=" << h.floor << " xy=" << h.x << ',' << h.y
           << " hp=" << h.hp << " attack=" << h.attack << " defense=" << h.defense << " gold=" << h.gold
           << " keys=" << h.yellow_keys << '/' << h.blue_keys << '/' << h.red_keys
           << " purchases=" << h.altar_purchases << '\n';
}

void write_route(const Route& route, const std::filesystem::path& path) {
    // Reconstruct the output before publication; a stale planning state is not evidence.
    const auto checked = replay(route.inputs);
    if (checked.game.hero != route.game.hero || checked.game.floors != route.game.floors ||
        checked.game.monsters != route.game.monsters || checked.game.dialogue != route.game.dialogue ||
        gameplay_json(checked.game, checked.flight) != gameplay_json(route.game, route.flight))
        throw std::runtime_error("Exported history does not reproduce the candidate state");
    if (!path.parent_path().empty())
        std::filesystem::create_directories(path.parent_path());
    if (std::filesystem::exists(path))
        throw std::runtime_error("Output already exists: " + path.string());
    std::ofstream output(path);
    if (!output)
        throw std::runtime_error("Cannot open output: " + path.string());
    write_replay(output, route.inputs);
    if (!output)
        throw std::runtime_error("Could not finish writing replay");
}

Route run_script(const Route& root, std::istream& script, std::ostream& progress) {
    if (root.flight != -1)
        throw std::invalid_argument("Close the Flight selector before running a script");
    Engine engine;
    Route current = root;
    std::string line;
    int number = 0;
    while (std::getline(script, line)) {
        ++number;
        line = line.substr(0, line.find('#'));
        std::istringstream command(line);
        std::string op;
        if (!(command >> op))
            continue;
        Game candidate = current.game;
        std::vector<PlayerInput> actions;
        bool ok = false;
        try {
            if (op == "go" || op == "room") {
                const int x = coordinate(command), y = coordinate(command), target = cell(x, y);
                if (op == "go" && candidate.tile(candidate.hero.floor, target) != Road)
                    throw std::runtime_error("go requires a road destination; use room for events");
                ok = engine.walk(candidate,
                                 op == "go" ? engine.roads(candidate) : engine.room_paths(candidate, target),
                                 target, actions);
                if (op == "go")
                    ok = ok && candidate.hero.x == x && candidate.hero.y == y;
            } else if (op == "land") {
                int floor = -1, x = -1, y = -1;
                if (!(command >> floor) || floor < 1 || floor >= FloorCount)
                    throw std::runtime_error("Invalid destination floor");
                command >> std::ws;
                if (!command.eof()) {
                    x = coordinate(command);
                    y = coordinate(command);
                }
                std::optional<Game> best;
                for (auto& [game, travel] : engine.flight_origins(candidate)) {
                    if (game.hero.floor != floor || (x >= 0 && (game.hero.x != x || game.hero.y != y)))
                        continue;
                    if (!best || game.hero.hp > best->hero.hp ||
                        (game.hero.hp == best->hero.hp && travel.size() < actions.size())) {
                        best = std::move(game);
                        actions = std::move(travel);
                    }
                }
                if (best) {
                    candidate = std::move(*best);
                    ok = true;
                }
            } else if (op == "buy") {
                int value = -2;
                if (!(command >> value) || value < -1 || value > 2)
                    throw std::runtime_error("Buy accepts -1 (leave), 0, 1 or 2");
                ok = input(candidate, choose(value), actions);
            } else if (op == "move") {
                static const std::map<std::string, Direction> names{{"up", Direction::Up},
                                                                    {"down", Direction::Down},
                                                                    {"left", Direction::Left},
                                                                    {"right", Direction::Right}};
                std::string name;
                command >> name;
                ok = input(candidate, move(names.at(name)), actions);
            } else if (op == "item") {
                static const std::map<std::string, Item> names{
                    {"warp", Item::WarpStaff},      {"magic", Item::MagicKey},
                    {"elixir", Item::Elixir},       {"bomb", Item::Bomb},
                    {"snow", Item::SnowCrystal},    {"ascent", Item::AscentWing},
                    {"descent", Item::DescentWing}, {"mattock", Item::Mattock},
                    {"super", Item::SuperMattock}};
                std::string name;
                command >> name;
                const auto item = names.at(name);
                const auto before = candidate.hero;
                ok = input(candidate, use(item), actions);
                if (item == Item::AscentWing || item == Item::DescentWing)
                    ok = ok && candidate.hero.floor != before.floor;
                if (item == Item::WarpStaff)
                    ok = ok && (candidate.hero.x != before.x || candidate.hero.y != before.y);
            } else if (op == "sweep") {
                engine.normalize_local(candidate, actions);
                ok = true;
            } else {
                throw std::runtime_error("Unknown operation: " + op);
            }
            std::string extra;
            if (command >> extra)
                throw std::runtime_error("Unexpected argument: " + extra);
            if (!ok)
                throw std::runtime_error("Native path or action did not complete");
            living_first_cycle(candidate);
        } catch (const std::exception& error) {
            throw std::runtime_error("Script line " + std::to_string(number) + ": " + error.what());
        }
        current.game = std::move(candidate);
        current.inputs.insert(current.inputs.end(), actions.begin(), actions.end());
        progress << "line=" << number << ' ';
        print_summary(current, progress);
    }
    return current;
}

Route rebase(std::span<const PlayerInput> original, const Route& prefix, std::size_t split) {
    return continue_route(original, prefix, split, false);
}

Route detail::continue_route(std::span<const PlayerInput> original, const Route& prefix, std::size_t split,
                             bool repair_access) {
    if (!split || split > original.size())
        throw std::invalid_argument("Invalid continuation split");
    for (std::size_t i = split; i < original.size(); ++i)
        if (original[i].kind == InputKind::NewGame || original[i].kind == InputKind::Reload ||
            original[i].kind == InputKind::Rankings)
            throw std::invalid_argument("Continuation cannot reset, reload or import external state");
    auto reference = replay(original.first(split));
    Route route = prefix;
    Engine engine;
    if (route.flight != reference.flight || route.game.hero.floor != reference.game.hero.floor)
        throw std::invalid_argument("Prefix must end on the reference floor with the same Flight state");
    for (std::size_t i = split; i < original.size(); ++i) {
        const auto& action = original[i];
        const auto before = reference.game.hero;
        bool opened = false;
        int retained_door = -1;
        if (action.kind == InputKind::Move) {
            const int target = neighbor(cell(before.x, before.y), action.direction);
            if (target >= 0) {
                const int tile = reference.game.tile(before.floor, target);
                opened = (tile == YellowDoor || tile == BlueDoor || tile == RedDoor || tile == SecretWall) &&
                         route.game.tile(before.floor, target) == Road;
                const int actual_tile = route.game.tile(before.floor, target);
                if (tile == Road && actual_tile >= YellowDoor && actual_tile <= RedDoor)
                    retained_door = target;
            }
        }
        apply_input(reference.game, reference.flight, action);
        settle_action(reference.game);
        const auto& expected = reference.game.hero;
        const auto& actual = route.game.hero;
        const bool aligned = before.floor == actual.floor && before.x == actual.x && before.y == actual.y;
        // Preserve a door deliberately left closed by the new prefix when an
        // alternative path exists. Blindly following the old walking trace
        // would spend that saved key again on a later visit.
        if (repair_access && aligned && retained_door >= 0 &&
            bypass_door(route, reference, original, i, retained_door, engine))
            continue;
        // Opening a door is a separate native contact from entering it. If the
        // new prefix opened it, omit only the now-redundant contact.
        const bool redundant =
            opened && expected.floor == before.floor && expected.x == before.x && expected.y == before.y;
        if (!redundant && (aligned || action.kind != InputKind::Move)) {
            apply_input(route.game, route.flight, action);
            settle_action(route.game);
            route.inputs.push_back(action);
        }
        // Skipping a one-time purchase changes later merchant contacts from
        // hint dialogue to an offer. Explicitly decline that incidental offer
        // so the continuation is not mistaken for a blocked walking route.
        if (repair_access && !reference.game.dialogue && route.game.dialogue && route.game.dialogue->shop) {
            if (!input(route.game, choose(-1), route.inputs))
                throw std::runtime_error("Cannot close incidental merchant offer");
        }
        if (action.kind == InputKind::Move && route.game.hero.floor == expected.floor &&
            (route.game.hero.x != expected.x || route.game.hero.y != expected.y)) {
            const int destination = cell(expected.x, expected.y);
            const int obstacle = route.game.tile(expected.floor, destination);
            if (repair_access && obstacle >= YellowDoor && obstacle <= RedDoor &&
                bypass_door(route, reference, original, i, destination, engine))
                continue;
            if (route.game.tile(expected.floor, destination) != Road ||
                !engine.walk(route.game, engine.roads(route.game), destination, route.inputs))
                throw std::runtime_error("No road continuation at input " + std::to_string(i + 1));
        }
        living_first_cycle(route.game);
        if (route.game.hero.floor != expected.floor || route.game.hero.x != expected.x ||
            route.game.hero.y != expected.y || route.flight != reference.flight)
            throw std::runtime_error("Continuation diverged at input " + std::to_string(i + 1));
    }
    return route;
}

bool detail::same_progress(const Game& a, const Game& b) {
    auto left = a.hero, right = b.hero;
    left.hp = right.hp = 0; // Comparing value copies, never modifying either native game.
    left.facing = right.facing;
    return left == right && a.floors == b.floors && a.monsters == b.monsters && a.dialogue == b.dialogue;
}

Route improve_pickups(const Route& route, std::size_t end, double seconds, std::ostream& progress) {
    if (end < 2 || end > route.inputs.size() || !std::isfinite(seconds) || seconds <= 0)
        throw std::invalid_argument("Invalid improvement boundary or time limit");

    struct Pickup {
        std::size_t at;
        int floor, position;
    };

    std::vector<Pickup> pickups;
    std::vector<std::pair<std::size_t, Game>> checkpoints;
    Game game;
    int flight = -1;
    for (std::size_t i = 0; i < end; ++i) {
        const auto before = game;
        apply_input(game, flight, route.inputs[i]);
        settle_action(game);
        const auto& h = game.hero;
        if (h.floor < 1 || h.floor > 20)
            continue;
        if (before.hero.floor == h.floor && stat_pickup(before.tile_at(h.floor, h.x, h.y)) &&
            game.tile_at(h.floor, h.x, h.y) == Road)
            pickups.push_back({i + 1, h.floor, cell(h.x, h.y)});
        if (i > 0 && !before.dialogue && !before.busy() &&
            (h.hp < before.hero.hp || h.gold > before.hero.gold || h.attack > before.hero.attack ||
             h.defense > before.hero.defense || h.floor != before.hero.floor))
            checkpoints.emplace_back(i, before);
    }
    const auto baseline = replay(std::span(route.inputs).first(end));
    Route best = route;
    int best_hp = baseline.game.hero.hp;
    Engine engine;
    std::size_t trials = 0, rejected = 0;
    const auto started = std::chrono::steady_clock::now();
    for (const auto& [split, state] : checkpoints) {
        for (const auto& pickup : pickups) {
            if (std::chrono::duration<double>(std::chrono::steady_clock::now() - started).count() >= seconds)
                goto finished;
            if (pickup.at <= split || pickup.floor != state.hero.floor ||
                !stat_pickup(state.tile(pickup.floor, pickup.position)))
                continue;
            ++trials;
            try {
                Route prefix{state, {route.inputs.begin(), route.inputs.begin() + split}};
                if (!engine.walk(prefix.game, engine.room_paths(prefix.game, pickup.position),
                                 pickup.position, prefix.inputs) ||
                    !engine.walk(prefix.game, engine.roads(prefix.game), cell(state.hero.x, state.hero.y),
                                 prefix.inputs))
                    continue;
                const auto candidate = rebase(std::span(route.inputs).first(end), prefix, split);
                if (candidate.game.hero.hp <= best_hp || !same_progress(candidate.game, baseline.game))
                    continue;
                // A locally better opening is accepted only if the entire continuation survives.
                auto complete = rebase(route.inputs, candidate, end);
                if (!same_progress(complete.game, route.game) || complete.game.hero.hp < route.game.hero.hp)
                    continue;
                best_hp = candidate.game.hero.hp;
                best = std::move(complete);
                progress << "improved before_input=" << split + 1 << " pickup=" << pickup.floor << ':'
                         << pickup.position % BoardWidth << ',' << pickup.position / BoardWidth
                         << " boundary_hp=" << best_hp << " gain=" << best_hp - baseline.game.hero.hp
                         << " final_hp=" << best.game.hero.hp << std::endl;
            } catch (const std::exception&) {
                ++rejected;
            }
        }
    }
finished:
    progress << "pickup_trials=" << trials << " rejected=" << rejected
             << " baseline_hp=" << baseline.game.hero.hp << " best_hp=" << best_hp << " seconds="
             << std::chrono::duration<double>(std::chrono::steady_clock::now() - started).count()
             << std::endl;
    return best;
}
} // namespace tsw::planner
