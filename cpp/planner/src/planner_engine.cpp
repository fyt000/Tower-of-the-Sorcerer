// Native event planning extracted from the campaign experiments.
#include "planner_internal.hpp"
#include <algorithm>
#include <stdexcept>

namespace tsw::planner::detail {
constexpr std::array<Direction, 4> Dirs{Direction::Up, Direction::Left, Direction::Right, Direction::Down};

int neighbor(int pos, Direction d) {
    int x = pos % BoardWidth, y = pos / BoardWidth;
    x += d == Direction::Left ? -1 : d == Direction::Right ? 1 : 0;
    y += d == Direction::Up ? -1 : d == Direction::Down ? 1 : 0;
    return x >= 0 && x < BoardWidth && y >= 0 && y < BoardWidth ? cell(x, y) : -1;
}

PlayerInput move(Direction d) {
    return PlayerInput::move(d);
}

PlayerInput use(Item i, int value) {
    return PlayerInput::use_item(i, value);
}

PlayerInput choose(int value) {
    return PlayerInput::choose(value);
}

bool input(Game& game, const PlayerInput& action, std::vector<PlayerInput>& history) {
    int flight = -1;
    const bool accepted = apply_input(game, flight, action);
    settle_action(game);
    if (!accepted || game.hero.hp <= 0 || game.visual.dead || game.hero.cycle_factor_minus_one)
        return false;
    history.push_back(action);
    return true;
}

double Engine::movement_cost(const Game& game, int p) const {
    if (game.hero.equipment_found[9])
        return 0;
    double cost = 0;
    for (auto d : Dirs) {
        int q = neighbor(p, d);
        if (q < 0)
            continue;
        int t = game.tile(game.hero.floor, q);
        if (t == MagicianA || t == MagicianA + 1)
            cost += 200;
        if (t == MagicianB || t == MagicianB + 1)
            cost += 100;
    }
    for (auto pair : std::array<std::array<Direction, 2>, 2>{
             {{Direction::Left, Direction::Right}, {Direction::Up, Direction::Down}}}) {
        int a = neighbor(p, pair[0]), b = neighbor(p, pair[1]);
        if (a >= 0 && b >= 0 && game.tile(game.hero.floor, a) == Sorcerer &&
            game.tile(game.hero.floor, b) == Sorcerer)
            cost += game.hero.hp * .5;
    }
    return cost;
}

Paths Engine::roads(const Game& game) const {
    Paths result;
    result.prev.fill(-1);
    result.distance.fill(-1);
    const int start = cell(game.hero.x, game.hero.y), floor = game.hero.floor;
    result.prev[start] = start;
    result.distance[start] = 0;
    std::array<double, 121> cost;
    cost.fill(1e30);
    cost[start] = 0;
    std::array<bool, 121> done{};
    for (int iteration = 0; iteration < 121; ++iteration) {
        int p = -1;
        for (int q = 0; q < 121; ++q)
            if (!done[q] && game.tile(floor, q) == Road && cost[q] < 1e29 && (p < 0 || cost[q] < cost[p]))
                p = q;
        if (p < 0)
            break;
        done[p] = true;
        for (auto d : Dirs) {
            const int q = neighbor(p, d);
            if (q < 0 || done[q])
                continue;
            double proposed = cost[p] + 1 + movement_cost(game, q);
            if (proposed >= cost[q])
                continue;
            cost[q] = proposed;
            result.prev[q] = p;
            result.direction[q] = d;
            result.distance[q] = result.distance[p] + 1;
        }
    }
    return result;
}

std::vector<Direction> path(const Paths& paths, int target) {
    std::vector<Direction> result;
    if (paths.prev[target] < 0)
        return result;
    for (int p = target; paths.prev[p] != p; p = paths.prev[p])
        result.push_back(paths.direction[p]);
    std::reverse(result.begin(), result.end());
    return result;
}

Paths Engine::room_paths(const Game& game, int target, int avoided_cell) const {
    // Price a whole room access rather than pruning after its first door.
    // These weights only select a proposed path. Native execution below
    // accounts for every actual fight, pickup, door and scripted callback.
    Paths result;
    result.prev.fill(-1);
    result.distance.fill(-1);
    std::array<double, 121> cost;
    cost.fill(1e30);
    std::array<bool, 121> done{};
    const int start = cell(game.hero.x, game.hero.y);
    cost[start] = 0;
    result.prev[start] = start;
    result.distance[start] = 0;
    for (int iteration = 0; iteration < 121; ++iteration) {
        int p = -1;
        for (int q = 0; q < 121; ++q)
            if (!done[q] && cost[q] < 1e29 && (p < 0 || cost[q] < cost[p]))
                p = q;
        if (p < 0 || p == target)
            break;
        done[p] = true;
        for (auto d : Dirs) {
            const int q = neighbor(p, d);
            if (q < 0 || q == avoided_cell)
                continue;
            const int t = game.tile(game.hero.floor, q);
            double weight = 1 + movement_cost(game, q);
            bool pass = t == Road || t == SecretWall || (t >= YellowKey && t <= Elixir) ||
                        (t >= IronSword && t <= HolyShield && t != SacredSword);
            if (t == YellowDoor && game.hero.yellow_keys) {
                pass = true;
                weight += 40;
            } else if (t == BlueDoor && game.hero.blue_keys) {
                pass = true;
                weight += 1000;

            } else if (t == RedDoor && game.hero.red_keys) {
                pass = true;
                weight += 400;
            }
            if (Game::monster_for_tile(t) >= 0) {
                const auto f = game.forecast(t);
                pass = f.penetrates && f.damage < game.hero.hp;
                weight += f.damage + 8;
            }
            if (q == target && eligible(game, t))
                pass = true;
            if (!pass || cost[p] + weight >= cost[q])
                continue;
            cost[q] = cost[p] + weight;
            result.prev[q] = p;
            result.direction[q] = d;
            result.distance[q] = result.distance[p] + 1;
        }
    }
    return result;
}

bool Engine::walk(Game& game, const Paths& paths, int target, std::vector<PlayerInput>& history) const {
    const int floor = game.hero.floor;
    const auto directions = path(paths, target);
    if (paths.prev[target] < 0)
        return false;
    for (std::size_t i = 0; i < directions.size(); ++i) {
        const auto d = directions[i];
        const int expected = neighbor(cell(game.hero.x, game.hero.y), d);
        const int t = game.tile(floor, expected);
        if (!input(game, move(d), history))
            return false;
        if (game.hero.floor == floor && cell(game.hero.x, game.hero.y) != expected &&
            game.tile(floor, expected) == Road &&
            (t == YellowDoor || t == BlueDoor || t == RedDoor || t == SecretWall)) {
            if (!input(game, move(d), history))
                return false;
        }
        if (i + 1 < directions.size() &&
            (game.hero.floor != floor || cell(game.hero.x, game.hero.y) != expected || game.busy()))
            return false;
        if (i + 1 == directions.size() && game.hero.floor == floor &&
            cell(game.hero.x, game.hero.y) != expected && game.tile(floor, expected) == Road &&
            (t == YellowDoor || t == BlueDoor || t == RedDoor || t == SecretWall)) {
            if (!input(game, move(d), history))
                return false;
        }
        if (i + 1 == directions.size() && game.hero.floor == floor && Game::monster_for_tile(t) >= 0 &&
            game.tile(floor, expected) == t)
            return false;
    }
    return true;
}

int farm_gold(const Game& game, int tile) {
    const int row = Game::monster_for_tile(tile);
    if (row < 0 || tile == GreatMagicMaster || tile == Zeno || tile == Zeno + 1 ||
        (tile >= DragonFirst && tile <= 123))
        return 0;
    const int reward = game.monsters[row].gold * (game.inventory(Item::LuckyGold) ? 2 : 1);
    return tile >= OctopusFirst && tile <= OctopusLast && tile != OctopusMouth ? reward / 2 : reward;
}

bool Engine::free_tile(const Game& game, int tile) const {
    // The mouth erases all remaining parts. Keep that irreversible tradeoff an
    // explicit search branch; a free sweep must collect the outer rewards first.
    if (tile == OctopusMouth)
        for (int part : game.floors[game.hero.floor].tiles)
            if (part >= OctopusFirst && part <= OctopusLast && part != OctopusMouth)
                return false;
    if (tile == SecretWall)
        return true;
    // This closure is valid for the early goal alone. A campaign comparison
    // must retain potion timing because later percentage hazards can make
    // an uncollected potion more valuable than current HP.
    if (config.goal <= 21 && !config.reserve_early_potions && (tile == RedPotion || tile == BluePotion))
        return true;
    if ((tile >= YellowKey && tile <= BlueKey) || tile == RedGem || tile == BlueGem ||
        (tile >= HeroOrb && tile <= Elixir) || (tile >= IronSword && tile <= HolyShield))
        return tile != SacredSword; // Access to Sacred Sword belongs to the boss chain.
    if (Game::monster_for_tile(tile) >= 0) {
        const auto f = game.forecast(tile);
        return f.penetrates && f.damage == 0;
    }
    return false;
}

void Engine::normalize_local(Game& game, std::vector<PlayerInput>& history) const {
    // Only early floors have this free-event closure. Late magic/pincer cells
    // require separate explicit decisions and an HP ledger.
    if (game.hero.floor >= 49)
        return;
    if (game.hero.floor > 39) {
        // Consolidate only native-verified free events in this component.
        // Never heal automatically or cross a percentage/movement hazard.
        for (int iteration = 0; iteration < 200; ++iteration) {
            const auto paths = roads(game);
            bool gained = false;
            for (int p = 0; p < 121; ++p) {
                const int t = game.tile(game.hero.floor, p);
                if (paths.distance[p] <= 0 || t == RedPotion || t == BluePotion || t == SacredShield ||
                    !free_tile(game, t) || !eligible(game, t))
                    continue;
                Game candidate = game;
                std::vector<PlayerInput> actions;
                if (!walk(candidate, paths, p, actions) || candidate.hero.hp != game.hero.hp ||
                    candidate.hero.floor != game.hero.floor || candidate.tile(candidate.hero.floor, p) == t)
                    continue;
                game = std::move(candidate);
                history.insert(history.end(), actions.begin(), actions.end());
                gained = true;
                break;
            }
            if (!gained)
                return;
        }
        return;
    }
    for (int iteration = 0; iteration < 200; ++iteration) {
        const auto paths = roads(game);
        int target = -1, best = 999;
        for (int p = 0; p < 121; ++p) {
            if (paths.distance[p] > 0 && free_tile(game, game.tile(game.hero.floor, p)) &&
                eligible(game, game.tile(game.hero.floor, p)) && paths.distance[p] < best) {
                best = paths.distance[p];
                target = p;
            }
        }
        if (target < 0)
            return;
        if (!walk(game, paths, target, history))
            return;
    }
}

bool Engine::fly_to(Game& game, int floor, std::vector<PlayerInput>& history) const {
    if (game.hero.floor == floor)
        return true;
    const auto paths = roads(game);
    std::vector<int> adjacent;
    for (int p = 0; p < 121; ++p) {
        if (paths.prev[p] < 0 || game.tile(game.hero.floor, p) != Road)
            continue;
        for (auto d : Dirs) {
            int q = neighbor(p, d);
            if (q >= 0 &&
                (game.tile(game.hero.floor, q) == StairsUp || game.tile(game.hero.floor, q) == StairsDown)) {
                adjacent.push_back(p);
                break;
            }
        }
    }
    std::sort(adjacent.begin(), adjacent.end(),
              [&](int a, int b) { return paths.distance[a] < paths.distance[b]; });
    for (int p : adjacent) {
        Game candidate = game;
        auto actions = history;
        if (walk(candidate, paths, p, actions) && candidate.can_open_flight() &&
            input(candidate, use(Item::FlightOrb, floor), actions) && candidate.hero.floor == floor) {
            game = std::move(candidate);
            history = std::move(actions);
            return true;
        }
    }
    return false;
}

void Engine::normalize(Game& game, std::vector<PlayerInput>& history) const {
    normalize_local(game, history);
    if (config.goal > 21 || !game.inventory(Item::FlightOrb) || game.hero.floor > 20)
        return;
    // Canonicalize the free early-floor sweep. All travel and pickups use
    // ordinary native inputs. No HP-dependent hazards occur in this range.
    // This removes combinatorial permutations of free visits/potion pickups.
    const int original_floor = game.hero.floor;
    for (int pass = 0; pass < 8; ++pass) {
        const int attack = game.hero.attack, defense = game.hero.defense;
        const int cross = game.inventory(Item::Cross);
        for (int f = 1; f <= std::min(20, game.hero.highest_floor); ++f) {
            Game candidate = game;
            std::vector<PlayerInput> sweep;
            if (!fly_to(candidate, f, sweep))
                continue;
            normalize_local(candidate, sweep);
            const auto& a = game.hero;
            const auto& b = candidate.hero;
            if (a.hp != b.hp || a.attack != b.attack || a.defense != b.defense || a.gold != b.gold ||
                a.yellow_keys != b.yellow_keys || a.blue_keys != b.blue_keys || a.red_keys != b.red_keys ||
                a.items != b.items) {
                game = std::move(candidate);
                history.insert(history.end(), sweep.begin(), sweep.end());
            }
        }
        if (attack == game.hero.attack && defense == game.hero.defense &&
            cross == game.inventory(Item::Cross))
            break;
    }
    fly_to(game, original_floor, history);
}

void append_value(std::string& key, int value) {
    for (int shift = 0; shift < 32; shift += 8)
        key.push_back(static_cast<char>((static_cast<unsigned>(value) >> shift) & 255));
}

std::string Engine::signature(const Game& game) const {
    std::string hash;
    for (const auto& floor : game.floors) {
        hash.append(reinterpret_cast<const char*>(floor.tiles.data()), floor.tiles.size());
        append_value(hash, floor.up_landing);
        append_value(hash, floor.down_landing);
    }
    for (const auto& monster : game.monsters) {
        append_value(hash, monster.hp);
        append_value(hash, monster.attack);
        append_value(hash, monster.defense);
        append_value(hash, monster.gold);
    }
    // Fields that affect scripted state are explicit; no padding bytes enter
    // the hash. Numeric resources are compared on the Pareto frontier below.
    const auto& h = game.hero;
    for (int value :
         {h.floor, h.highest_floor, std::to_underlying(h.sword), std::to_underlying(h.shield), h.fairy_visits,
          h.cycle_factor_minus_one, h.later_cycle, int(h.zeno_sealed), int(h.floor34_reward_created),
          int(h.floor35_reward_created), int(h.floor40_reward_created), int(h.floor41_reward_created),
          int(h.floor32_arrival_seen), std::to_underlying(h.merchant2_heard),
          std::to_underlying(h.flight_direction), std::to_underlying(h.highest_floor_stair_kind)})
        append_value(hash, value);
    for (int value : h.items)
        append_value(hash, value);
    for (int value : h.equipment_found)
        append_value(hash, value);
    for (int value : h.dialogue_seen)
        append_value(hash, value);
    for (auto value : h.wisdom_hints)
        append_value(hash, std::to_underlying(value));
    for (auto value : h.old_man_heard)
        append_value(hash, std::to_underlying(value));
    for (int value : h.merchant_used)
        append_value(hash, value);
    auto reachable = roads(game);
    int component = cell(h.x, h.y);
    for (int p = 0; p < component; ++p)
        if (reachable.prev[p] >= 0 && game.tile(h.floor, p) == Road) {
            component = p;
            break;
        }
    if (h.floor >= 40) {
        // Movement through magic and pincers has a cost; two positions in one
        // road component are not equivalent late-game planning states.
        const int position = cell(h.x, h.y);
        append_value(hash, position);
        return hash;
    }
    append_value(hash, component);
    return hash;
}

bool dominates(const Hero& a, const Hero& b) {
    return a.hp >= b.hp && a.attack >= b.attack && a.defense >= b.defense && a.gold >= b.gold &&
           a.yellow_keys >= b.yellow_keys && a.blue_keys >= b.blue_keys && a.red_keys >= b.red_keys &&
           a.altar_purchases <= b.altar_purchases;
}

double Engine::rank(const Game& game) const {
    const auto& h = game.hero;
    double reserve = 0;
    for (int f = 1; f <= std::min(10, h.highest_floor); ++f)
        for (int t : game.floors[f].tiles)
            reserve += t == BluePotion ? 200 : t == RedPotion ? 50 : 0;
    if (config.goal <= 21) {
        double milestone = game.inventory(Item::FlightOrb) * 1200;
        if (config.goal <= 11) {
            milestone += std::min(27, h.attack) * 500 + std::min(30, h.defense) * 500;
            if (h.highest_floor >= 10) {
                milestone += game.tile_at(10, 5, 8) == Road ? 3000 : 0;
                milestone += game.tile_at(10, 5, 4) == Road ? 6000 : 0;
                milestone += game.tile_at(10, 3, 3) == Road ? 2000 : 0;
                milestone += game.tile_at(10, 7, 3) == Road ? 2000 : 0;
                milestone += game.tile_at(10, 5, 0) == StairsUp ? 50000 : 0;
            }
        }
        // A boss victory can spend almost all HP while opening the goal stair.
        // Queue that concrete progress before healthier pre-boss permutations.
        if (config.goal == 21 && game.tile_at(20, 5, 0) == StairsUp)
            milestone += 50000;
        if (config.goal == 21 && h.highest_floor >= 20) {
            milestone += game.tile_at(20, 5, 8) == Road ? 6000 : 0;
            milestone += game.tile_at(20, 5, 7) == Road ? 12000 : 0;
        }
        if (config.goal > 11) {
            milestone += h.equipment_found[6] * 18000 + h.equipment_found[1] * 18000;
            if (h.equipment_found[6] && h.equipment_found[1]) {
                const int rock_defense = game.monsters[Game::monster_for_tile(Rock)].defense;
                milestone += std::min(h.attack, rock_defense + 1) * 800;
                milestone += h.attack > rock_defense ? 8000 : 0;
            }
            // Native access milestones prevent the floor-15 corridor from
            // being buried under high-stat states that have not crossed it.
            if (h.highest_floor >= 15) {
                milestone += game.tile_at(15, 8, 5) == Road ? 2000 : 0;
                milestone += game.tile_at(15, 10, 2) == Road ? 3500 : 0;
                milestone += game.tile_at(15, 7, 0) == Road ? 16000 : 0;
            }
            if (h.highest_floor >= 16) {
                milestone += game.tile_at(16, 5, 3) == Road ? 2000 : 0;
                milestone += game.tile_at(16, 5, 7) == Road ? 2000 : 0;
            }
        }
        if (config.goal <= 11)
            milestone +=
                (h.sword > EquipmentTier::None ? 1800 : 0) + (h.shield > EquipmentTier::None ? 2400 : 0);
        else {
            milestone += game.inventory(Item::Cross) * 8000;
            if (h.highest_floor >= 18 && h.attack > 68)
                milestone += 2400;
            if (game.inventory(Item::Cross)) {
                const auto vampire = game.forecast(Vampire);
                milestone += vampire.penetrates ? -.4 * vampire.damage : -4000;
            }
        }
        double survival_priority = 0;
        if (config.goal == 21 && h.highest_floor >= 20 && game.inventory(Item::Cross) &&
            game.tile_at(20, 5, 0) != StairsUp) {
            const auto boss = game.forecast(Vampire);
            if (boss.penetrates && h.hp <= boss.damage)
                survival_priority -= 2500 + (boss.damage + 1 - h.hp) * 8;
        }
        const int attack_weight = config.early_policy == SearchPolicy::Attack    ? 180
                                  : config.early_policy == SearchPolicy::Defense ? 90
                                                                                 : 45;
        const int defense_weight = config.early_policy == SearchPolicy::Attack    ? 25
                                   : config.early_policy == SearchPolicy::Defense ? 65
                                                                                  : 45;
        return h.highest_floor * 2000 + h.attack * attack_weight + h.defense * defense_weight + h.gold * .6 +
               h.yellow_keys * 100 + h.blue_keys * 450 + h.red_keys * 1800 + h.hp * .4 + reserve * .1 +
               milestone + survival_priority;
    }
    return h.highest_floor * 70 + h.attack * 160 + h.defense * 80 + h.gold * .35 + h.yellow_keys * 22 +
           h.blue_keys * 45 + h.red_keys * 80 + h.hp * .25 + reserve * .10 +
           game.inventory(Item::Cross) * 100 + game.inventory(Item::FlightOrb) * 180;
}

void Engine::attach(Node& child, const Node& parent, std::vector<PlayerInput> inputs) const {
    child.allocation = parent.allocation;
    child.input_count = parent.input_count + int(inputs.size());
    child.history = std::make_shared<History>(History{parent.history, std::move(inputs)});
    child.score = rank(child.game);
}

bool Engine::eligible(const Game& game, int tile) const {
    if (game.hero.floor == 28 && (tile == Merchant || tile == Merchant2))
        return false; // Key liquidation is only safe after the route's doors are budgeted.
    if (game.hero.floor == 23 && tile == SpecialRoad)
        return false;
    if (tile == Road || tile == Wall || tile == Void || tile == Lava || tile == StarVoid ||
        tile == SolidDecoration || tile == AltarSide || tile == AltarTop || tile == SacredShield ||
        (config.goal <= 21 &&
         (tile == SacredSword || tile == TimeGate || tile == TimeGate2 || tile == DragonSlayer)) ||
        (tile >= DragonFirst && tile <= 123 && tile != DragonHead))
        return false;
    if (config.goal > 21 && game.hero.floor == 50 && (tile == Zeno || tile == Zeno + 1))
        return false; // First-cycle contact runs the ending; search stops before
                      // contact.
    if (config.goal > 21 && game.hero.floor == 49) {
        if ((tile == Zeno || tile == Zeno + 1) && (!game.hero.zeno_sealed || game.tile_at(50, 5, 4) != Zeno))
            return false;
    }
    if (tile == YellowDoor && !game.hero.yellow_keys && game.hero.floor != 39)
        return false;
    if (tile == BlueDoor && !game.hero.blue_keys)
        return false;
    if (tile == RedDoor && !game.hero.red_keys)
        return false;
    if (tile == StairsUp && game.hero.floor >= config.goal)
        return false;
    if ((tile == OldMan || tile == OldMan2) && game.hero.floor == 2 && config.goal <= 21)
        return false; // The boost is a separate timed milestone.
    if ((tile == OldMan || tile == OldMan2) && game.hero.floor != 16 &&
        !(game.hero.floor == 2 && config.goal > 21))
        return false;
    if (Game::monster_for_tile(tile) >= 0) {
        const auto f = game.forecast(tile);
        return f.penetrates && f.damage < game.hero.hp;
    }
    return true;
}

std::vector<std::pair<Game, std::vector<PlayerInput>>> Engine::flight_origins(const Game& parent) const {
    std::vector<std::pair<Game, std::vector<PlayerInput>>> origins{{parent, {}}};
    if (!parent.inventory(Item::FlightOrb))
        return origins;
    const auto paths = roads(parent);
    for (int p = 0; p < 121; ++p) {
        if (paths.prev[p] < 0 || parent.tile(parent.hero.floor, p) != Road)
            continue;
        bool adjacent = false;
        for (auto d : Dirs) {
            int q = neighbor(p, d);
            adjacent |= q >= 0 && (parent.tile(parent.hero.floor, q) == StairsUp ||
                                   parent.tile(parent.hero.floor, q) == StairsDown);
        }
        if (!adjacent)
            continue;
        Game near = parent;
        std::vector<PlayerInput> travel;
        if (!walk(near, paths, p, travel) || !near.can_open_flight())
            continue;
        for (int f = 1; f <= std::min(config.goal, near.hero.highest_floor); ++f) {
            if (f == 44)
                continue;
            for (int direction : {1, 2}) {
                int waypoint = direction == 1 ? (f == 45 ? 43 : f - 1) : (f == 43 ? 45 : f + 1);
                if (waypoint < 1 || waypoint > near.hero.highest_floor)
                    continue;
                Game c = near;
                auto actions = travel;
                int preview = -1;
                auto enter = [&](InputKind kind) {
                    PlayerInput a{kind};
                    bool ok = apply_input(c, preview, a);
                    settle_action(c);
                    if (ok)
                        actions.push_back(a);
                    return ok;
                };
                if (!enter(InputKind::OpenFlight))
                    continue;
                bool ok = true;
                for (int step = 0; preview != waypoint && ok && step < FloorCount; ++step) {
                    const int previous = preview;
                    ok = enter(preview < waypoint ? InputKind::FlightUp : InputKind::FlightDown) &&
                         preview != previous;
                }
                ok = ok && preview == waypoint;
                if (!ok || !enter(direction == 1 ? InputKind::FlightUp : InputKind::FlightDown) ||
                    !enter(InputKind::Travel) || c.hero.floor != f)
                    continue;
                if (std::none_of(origins.begin(), origins.end(), [&](const auto& other) {
                        return other.first.hero.floor == c.hero.floor && other.first.hero.x == c.hero.x &&
                               other.first.hero.y == c.hero.y && other.first.floors == c.floors &&
                               other.first.hero.hp >= c.hero.hp;
                    }))
                    origins.emplace_back(std::move(c), std::move(actions));
            }
        }
        // Compare both cleared stair exits; their magic/pincer costs differ.
    }
    return origins;
}

std::vector<Node> Engine::expand(const Node& parent) {
    // Gather current-floor and Flight landing variants. All travel executes
    // native inputs; no destination coordinates or state fields are injected.
    std::vector<std::pair<Game, std::vector<PlayerInput>>> origins = flight_origins(parent.game);
    std::vector<Node> result;
    for (auto& [origin, travel] : origins) {
        if (config.atomic_events)
            normalize_local(origin, travel);
        else
            normalize(origin, travel);
        const auto road_paths = roads(origin);
        for (int p = 0; p < 121; ++p) {
            const int tile = origin.tile(origin.hero.floor, p);
            if (config.defer_merchant_hp && origin.hero.floor == 45 && tile == Merchant)
                continue;
            if (!eligible(origin, tile))
                continue;
            std::vector<Paths> proposals;
            if (config.atomic_events)
                proposals.push_back(road_paths);
            proposals.push_back(room_paths(origin, p));
            for (const auto& paths : proposals) {
                if (paths.distance[p] <= 0)
                    continue;
                ++evaluations;
                Game contacted = origin;
                auto inputs = travel;
                if (!walk(contacted, paths, p, inputs)) {
                    ++rejects;
                    continue;
                }
                if (contacted.dialogue && contacted.dialogue->shop) {
                    const bool altar = tile == Altar;
                    for (int choice = 0; choice < (altar ? 3 : 1); ++choice) {
                        if (altar && (contacted.hero.altar_purchases >= config.max_purchases ||
                                      (choice == 0 && (!config.hp_buys || contacted.hero.floor < 40)) ||
                                      (contacted.hero.floor + 10) / 10 <
                                          std::min(5, (contacted.hero.highest_floor + 10) / 10)))
                            continue;
                        Node child;
                        child.game = contacted;
                        auto actions = inputs;
                        if (!input(child.game, choose(choice), actions))
                            continue;
                        normalize(child.game, actions);
                        attach(child, parent, std::move(actions));
                        if (altar)
                            child.allocation = parent.allocation * 4 + choice + 1;
                        result.push_back(std::move(child));
                    }
                } else if (signature(contacted) != signature(parent.game) ||
                           !dominates(parent.game.hero, contacted.hero)) {
                    Node child;
                    child.game = std::move(contacted);
                    normalize(child.game, inputs);
                    attach(child, parent, std::move(inputs));
                    if (child.game.hero.hp > 0 && !child.game.visual.dead && !child.game.dialogue &&
                        !child.game.busy())
                        result.push_back(std::move(child));
                }
            }
        }
        // A Flight to a different connected component is itself a useful
        // native macro even if that landing has no immediately chosen event.
        if (config.goal > 21 && !travel.empty() && signature(origin) != signature(parent.game)) {
            Node child;
            child.game = std::move(origin);
            attach(child, parent, std::move(travel));
            result.push_back(std::move(child));
        }
    }
    return result;
}

std::vector<PlayerInput> history(const Node& node) {
    std::vector<const History*> chain;
    for (auto p = node.history.get(); p; p = p->parent.get())
        chain.push_back(p);
    std::vector<PlayerInput> result;
    for (auto it = chain.rbegin(); it != chain.rend(); ++it)
        result.insert(result.end(), (*it)->inputs.begin(), (*it)->inputs.end());
    return result;
}

} // namespace tsw::planner::detail
