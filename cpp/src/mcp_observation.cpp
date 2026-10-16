#include "mcp_internal.hpp"
#include "tsw/dialogue_ids.hpp"
#include <algorithm>
#include <cmath>
#include <glaze/json.hpp>
#include <set>
#include <stdexcept>

namespace tsw::detail::mcp {
namespace {

constexpr std::array<std::string_view, 10> EquipmentNames{
    "Iron Sword",  "Silver Sword",  "Knight Sword",  "Holy Sword",  "Sacred Sword",
    "Iron Shield", "Silver Shield", "Knight Shield", "Holy Shield", "Sacred Shield"};

std::string_view facing(Direction d) {
    switch (d) {
    case Direction::Up:
        return "up";
    case Direction::Down:
        return "down";
    case Direction::Left:
        return "left";
    case Direction::Right:
        return "right";
    }
    return "unknown";
}

int visible_tile(int tile, bool developer) {
    if (developer)
        return tile;
    if (tile == SecretWall || tile == HiddenObject)
        return Wall;
    return tile == SpecialRoad ? Road : tile;
}

Json tile_definition(const Game& game, int floor, int tile) {
    std::string_view name = "Decoration", kind = "decoration";
    // Match contact()'s ending dispatch rather than predicting ordinary combat.
    const bool ending =
        floor == 50 && !game.hero.cycle_factor_minus_one && (tile == Zeno || tile == Zeno + 1);
    if (ending) {
        name = Game::monster_name(ZenoRow);
        kind = "trigger";
    } else if (const int enemy = Game::monster_for_tile(tile); enemy >= 0) {
        name = Game::monster_name(enemy);
        kind = "enemy";
    } else if (tile >= HeroOrb && tile <= LuckyGold) {
        name = Game::item_name(static_cast<Item>(tile - HeroOrb));
        kind = "item";
    } else if (tile >= IronSword && tile <= SacredShield) {
        name = EquipmentNames[tile - IronSword];
        kind = "equipment";
    } else {
        switch (tile) {
        case Void:
            name = "Void";
            kind = "void";
            break;
        case Road:
            name = "Road";
            kind = "floor";
            break;
        case SpecialRoad:
            name = "Special road";
            kind = "trigger";
            break;
        case Wall:
            name = "Brick wall";
            kind = "wall";
            break;
        case SecretWall:
            name = "Secret wall";
            kind = "hidden_wall";
            break;
        case HiddenObject:
            name = "Concealed object";
            kind = "hidden_wall";
            break;
        case YellowDoor:
            name = "Yellow door";
            kind = "door";
            break;
        case BlueDoor:
            name = "Blue door";
            kind = "door";
            break;
        case RedDoor:
            name = "Red door";
            kind = "door";
            break;
        case SealedGate:
            name = "Sealed gate";
            kind = "gate";
            break;
        case PrisonGate:
            name = "Prison gate";
            kind = "gate";
            break;
        case StairsUp:
            name = "Stairs up";
            kind = "stairs_up";
            break;
        case StairsDown:
            name = "Stairs down";
            kind = "stairs_down";
            break;
        case Lava:
            name = "Lava";
            kind = "lava";
            break;
        case StarVoid:
            name = "Starry void";
            kind = "void";
            break;
        case Altar:
            name = "Altar";
            kind = "npc";
            break;
        case AltarTop:
        case AltarSide:
            name = "Altar";
            break;
        case Merchant:
        case Merchant2:
            name = "Merchant";
            kind = "npc";
            break;
        case Thief:
        case Thief2:
            name = "Thief";
            kind = "npc";
            break;
        case Fairy:
        case Fairy2:
            name = "Fairy";
            kind = "npc";
            break;
        case OldMan:
        case OldMan2:
            name = "Old man";
            kind = "npc";
            break;
        case TimeGate:
        case TimeGate2:
            name = "Time gate";
            kind = "npc";
            break;
        case YellowKey:
            name = "Yellow key";
            kind = "key";
            break;
        case BlueKey:
            name = "Blue key";
            kind = "key";
            break;
        case RedKey:
            name = "Red key";
            kind = "key";
            break;
        case RedPotion:
            name = "Red potion";
            kind = "potion";
            break;
        case BluePotion:
            name = "Blue potion";
            kind = "potion";
            break;
        case RedGem:
            name = "Red gem";
            kind = "gem";
            break;
        case BlueGem:
            name = "Blue gem";
            kind = "gem";
            break;
        case StairCover:
            name = "Covered stairway";
            break;
        }
    }
    Json result{{"id", tile}, {"name", name}, {"kind", kind}};
    if (ending) {
        result["interaction"] = "ending";
        result["hp_cost"] = 0;
        result["available"] = true;
    }
    if (tile >= YellowDoor && tile <= RedDoor)
        result["key"] = tile == YellowDoor ? "yellow" : tile == BlueDoor ? "blue" : "red";
    if (tile >= YellowKey && tile <= BlueKey)
        result["key"] = tile == YellowKey ? "yellow" : tile == BlueKey ? "blue" : "red";
    if (tile >= HeroOrb && tile <= LuckyGold)
        result["item"] = ItemDefinitions[tile - HeroOrb].id;
    return result;
}

Json enemy_info(const Game& game, int tile) {
    const int row = Game::monster_for_tile(tile), scale = game.hero.cycle_factor_minus_one + 1;
    const auto& m = game.monsters.at(row);
    const auto f = game.forecast(tile);
    return Json{{"name", Game::monster_name(row)},
                {"row", row},
                {"hp", std::int64_t(m.hp) * scale},
                {"attack", std::int64_t(m.attack) * scale},
                {"defense", std::int64_t(m.defense) * scale},
                {"gold", m.gold},
                {"forecast", Json{{"penetrates", f.penetrates},
                                  {"damage", f.penetrates ? Json(f.damage) : Json{}},
                                  {"hero_hits", f.hero_strike_count},
                                  {"hero_hit", f.hero_damage_per_strike},
                                  {"enemy_hit", f.enemy_damage_per_strike},
                                  {"survivable", f.penetrates && f.damage < game.hero.hp}}}};
}
} // namespace

Json parse(std::string_view source) {
    struct Options : glz::opts {
        bool validate_skipped = true;
        bool validate_trailing_whitespace = true;
    };

    constexpr auto options = [] {
        Options o;
        o.null_terminated = false;
        return o;
    }();
    Json value;
    if (const auto error = glz::read<options>(value, source))
        throw std::runtime_error(glz::format_error(error, source));
    return value;
}

std::string dump(const Json& value) {
    std::string output;
    if (const auto error = glz::write<glz::opts{.skip_null_members = false}>(value, output))
        throw std::runtime_error(glz::format_error(error));
    return output;
}

void Session::act(const PlayerInput& input) {
    record(input, execute_input(game, flight, input));
    if (input.kind == InputKind::NewGame) {
        const auto previous = recorder.history().size();
        recorder.rankings(game.rankings);
        steps += recorder.history().size() - previous;
    }
}

void Session::record(const PlayerInput& input, const InputOutcome& outcome) {
    if (input.kind == InputKind::NewGame) {
        steps = 0;
        log.clear();
        recorder.new_game();
    } else {
        ++steps;
        recorder.append(input);
    }
    for (const auto& text : outcome.speech) {
        log.emplace_back(Json{{"step", steps}, {"text", text}});
    }
    if (log.size() > 100)
        log.erase(log.begin(), log.end() - 100);
    Json::array_t messages;
    for (const auto& text : outcome.messages)
        messages.emplace_back(text);
    last_action = Json{{"action", parse(input_json(input))},
                       {"accepted", outcome.accepted},
                       {"ok", outcome.ok},
                       {"moved", outcome.moved},
                       {"messages", messages},
                       {"message", outcome.message}};
}

Json inspect(const Game& game, bool developer, int floor, int x, int y) {
    const int raw = game.tile_at(floor, x, y);
    auto result = tile_definition(game, floor, visible_tile(raw, developer));
    result["floor"] = floor;
    result["x"] = x;
    result["y"] = y;
    if (result["kind"].get<std::string>() == "enemy") {
        const bool unlocked = developer || game.inventory(Item::HeroOrb) > 0;
        result["details_locked"] = !unlocked;
        if (unlocked)
            result["enemy"] = enemy_info(game, raw);
    }
    const int scale = game.hero.cycle_factor_minus_one + 1, area = (floor + 9) / 10;
    if (raw == RedPotion || raw == BluePotion || raw == RedGem || raw == BlueGem) {
        result["stat"] = raw == RedGem ? "attack" : raw == BlueGem ? "defense" : "hp";
        result["amount"] = (raw == RedPotion ? 50 : raw == BluePotion ? 200 : 1) * area * scale;
    } else if (raw >= IronSword && raw <= SacredShield) {
        constexpr std::array<int, 5> Gain{10, 20, 40, 50, 100};
        result["stat"] = raw <= SacredSword ? "attack" : "defense";
        result["amount"] = Gain[(raw - IronSword) % 5] * scale;
    }
    return result;
}

Json observe(const Session& session, bool developer, int map_floor, ObservationDetail detail) {
    const auto& game = session.game;
    const auto& h = game.hero;
    if (map_floor < 0)
        map_floor = session.flight >= 0 ? session.flight : h.floor;
    auto result = parse(gameplay_json(game, session.flight, map_floor));
    auto& map = result["map"].get_array();
    std::set<int> ids;
    Json definitions = Json::object_t{}, enemies = Json::array_t{};
    for (int i = 0; i < CellCount; ++i) {
        const int raw = game.tile(map_floor, i), id = visible_tile(raw, developer);
        map[i] = id;
        ids.insert(id);
        if (Game::monster_for_tile(raw) >= 0) {
            auto enemy = inspect(game, developer, map_floor, i % BoardWidth, i / BoardWidth);
            if (enemy["kind"].get<std::string>() == "enemy")
                enemies.get_array().push_back(std::move(enemy));
        }
    }
    for (int id : ids)
        definitions[std::to_string(id)] = tile_definition(game, map_floor, id);
    result["tile_defs"] = std::move(definitions);
    result["enemies"] = std::move(enemies);
    result["floor"] = h.floor;
    result["width"] = BoardWidth;
    result["height"] = BoardWidth;
    result["coordinates"] = Json{{"origin", "top_left"},
                                 {"indexing", "map[y * width + x]"},
                                 {"x_increases", "right"},
                                 {"y_increases", "down"}};
    result["hero"]["facing"] = facing(h.facing);
    result["equipment"] = Json{
        {"sword",
         h.sword != EquipmentTier::None ? Json(EquipmentNames.at(std::to_underlying(h.sword) - 1)) : Json{}},
        {"shield", h.shield != EquipmentTier::None ? Json(EquipmentNames.at(std::to_underlying(h.shield) + 4))
                                                   : Json{}},
        {"sacred_shield_protection", h.equipment_found[SacredShieldFlag] != 0}};
    result["cycle"] = Json{{"factor", h.cycle_factor_minus_one + 1}, {"later", h.later_cycle != 0}};
    result["steps"] = session.steps;
    result["phase"] = h.hp <= 0 || game.visual.dead ? "dead"
                      : game.dialogue               ? "shop"
                      : session.flight >= 0         ? "flight"
                      : game.busy()                 ? "busy"
                                                    : "playing";
    result["forecasts_unlocked"] = developer || game.inventory(Item::HeroOrb) > 0;
    const bool save_unlocked = h.hp > 0 && (developer || game.inventory(Item::HeroOrb) > 0);
    result["save_unlocked"] = save_unlocked;
    result["file_save_ready"] = save_unlocked && !game.busy() && session.flight < 0;
    result["recording"] =
        Json{{"active", session.recorder.active()}, {"inputs", session.recorder.history().size()}};
    result["last_action"] = session.last_action;
    result["log"] = session.log;
    Json::array_t items, clues, destinations;
    for (int i = 0; i < std::ssize(ItemDefinitions); ++i) {
        if (!h.items[i])
            continue;
        const auto item = static_cast<Item>(i);
        items.emplace_back(Json{{"id", ItemDefinitions[i].id},
                                {"name", Game::item_name(item)},
                                {"charges", h.items[i]},
                                {"usage", ItemDefinitions[i].usage},
                                {"passive", item_definition(item).passive},
                                {"usable", !game.busy() && session.flight < 0 &&
                                               (item != Item::FlightOrb || game.can_open_flight())}});
    }
    if (game.inventory(Item::WisdomOrb))
        for (int i = 0; i < std::ssize(h.wisdom_hints); ++i)
            if (h.wisdom_hints[i] == HintState::Recorded)
                clues.emplace_back(
                    Json{{"id", i}, {"text", Game::original_dialogue(DialogueId::WisdomHintBase + i)}});
    if (game.inventory(Item::FlightOrb))
        for (int floor = 1; floor <= h.highest_floor; ++floor)
            if (floor != 44)
                destinations.emplace_back(floor);
    result["inventory_items"] = std::move(items);
    result["wisdom_clues"] = std::move(clues);
    result["flight_destinations"] = std::move(destinations);
    result["pending_interaction"] = Json{};
    if (game.dialogue) {
        Json::array_t choices;
        for (int i = 0; i < 3; ++i)
            if (!game.dialogue->choices[i].empty())
                choices.emplace_back(Json{{"id", std::to_string(i)},
                                          {"label", game.dialogue->choices[i]},
                                          {"cost", game.shop_cost()},
                                          {"affordable", h.gold >= game.shop_cost()}});
        choices.emplace_back(Json{{"id", "leave"}, {"label", game.dialogue->shop ? "Leave" : "Continue"}});
        result["pending_interaction"] =
            Json{{"text", game.dialogue->text}, {"shop", game.dialogue->shop}, {"choices", choices}};
    }
    result["last_encounter"] = Json{};
    if (game.visual.last_defeated) {
        const auto& e = *game.visual.last_defeated;
        result["last_encounter"] = Json{{"name", Game::monster_name(e.monster_index)},
                                        {"hp", e.stats.hp},
                                        {"attack", e.stats.attack},
                                        {"defense", e.stats.defense},
                                        {"gold", e.stats.gold},
                                        {"damage", e.damage}};
    }
    if (developer && detail == ObservationDetail::Full) {
        Json::array_t floors, monsters;
        for (int i = 0; i < FloorCount; ++i) {
            Json::array_t tiles;
            for (auto t : game.floors[i].tiles)
                tiles.emplace_back(int(t));
            floors.emplace_back(Json{{"id", i},
                                     {"up_landing", int(game.floors[i].up_landing)},
                                     {"down_landing", int(game.floors[i].down_landing)},
                                     {"tiles", tiles}});
        }
        for (int i = 0; i < std::ssize(game.monsters); ++i) {
            const auto& m = game.monsters[i];
            monsters.emplace_back(Json{{"row", i},
                                       {"name", Game::monster_name(i)},
                                       {"hp", m.hp},
                                       {"attack", m.attack},
                                       {"defense", m.defense},
                                       {"gold", m.gold}});
        }
        // Diagnostic state stays a projection, never a second persistence schema.
        result["floors"] = std::move(floors);
        result["monsters"] = std::move(monsters);
        result["hero_state"] = parse(glz::write_json(h).value());
        result["pending_commands"] = parse(glz::write_json(game.commands).value());
    }
    if (detail == ObservationDetail::Full)
        return result;
    Json compact = Json::object_t{};
    for (auto key : {"hero", "equipment", "cycle", "steps", "phase", "forecasts_unlocked", "save_unlocked",
                     "file_save_ready", "recording", "last_action", "pending_interaction"})
        compact[key] = result[key];
    compact["detail"] = observation_detail_name(detail);
    compact["developer"] = developer;
    compact["inventory"] = Json::object_t{};
    for (const auto& [key, value] : result["inventory"].get_object())
        if (value.as<int>() != 0)
            compact["inventory"][key] = value;
    if (compact["last_action"].is_object()) {
        auto& action = compact["last_action"].get_object();
        if (action["ok"].get<bool>() || !action["messages"].get_array().empty())
            action.erase("message");
    }
    if (detail == ObservationDetail::Summary)
        return compact;

    // Descriptions, pickup values and forecasts occur once per type, not per square.
    Json tile_types = Json::object_t{};
    Json::array_t points, rows;
    for (int y = 0; y < BoardWidth; ++y) {
        std::string row;
        for (int x = 0; x < BoardWidth; ++x) {
            const int raw = game.tile_at(map_floor, x, y), id = visible_tile(raw, developer);
            row += visible_tile(raw, false) == Road ? '.' : '#';
            const auto definition = tile_definition(game, map_floor, id);
            const auto kind = definition["kind"].get<std::string>();
            if (kind == "floor" || kind == "wall" || kind == "void" || kind == "lava" || kind == "decoration")
                continue;
            const auto type_id = std::to_string(id);
            if (!tile_types.contains(type_id)) {
                auto type = inspect(game, developer, map_floor, x, y);
                for (auto key : {"floor", "x", "y", "id"})
                    type.get_object().erase(key);
                if (kind == "door") {
                    const int keys = id == YellowDoor ? h.yellow_keys
                                     : id == BlueDoor ? h.blue_keys
                                                      : h.red_keys;
                    type["available"] = keys > 0;
                    if (!keys)
                        type["blocked_reason"] = "missing_key";
                }
                if (type.contains("enemy")) {
                    type["available"] =
                        raw != GateKeeperA + 1 && type["enemy"]["forecast"]["survivable"].get<bool>();
                    type["enemy"].get_object().erase("name");
                    type.get_object().erase("details_locked");
                }
                tile_types[type_id] = std::move(type);
            }
            Json point{{"id", id}, {"x", x}, {"y", y}};
            if (map_floor == h.floor && session.flight < 0 && !game.busy()) {
                const auto path = plan(session, x, y);
                point["reachable"] = path["reached"];
                if (path["reached"].get<bool>())
                    point["walk_steps"] = path["directions"].get_array().size();
            }
            points.push_back(std::move(point));
        }
        rows.emplace_back(row);
    }
    compact["floor"] = Json{{"id", map_floor}, {"walkable_rows", rows}, {"points", points}};
    compact["tile_types"] = std::move(tile_types);
    compact["wisdom_clues"] = result["wisdom_clues"];
    if (session.flight >= 0)
        compact["flight"] =
            Json{{"selection", session.flight}, {"destinations", result["flight_destinations"]}};
    return compact;
}

Json changes(const Session& before, const Session& after, bool developer) {
    Json stats = Json::object_t{}, inventory = Json::object_t{};
    const auto old_hero = parse(gameplay_json(before.game))["hero"];
    const auto new_hero = parse(gameplay_json(after.game))["hero"];
    for (auto key : {"hp", "attack", "defense", "gold", "yellow_keys", "blue_keys", "red_keys"}) {
        const auto delta = new_hero[key].as<int>() - old_hero[key].as<int>();
        if (delta)
            stats[key] = delta;
    }
    for (int i = 0; i < std::ssize(ItemDefinitions); ++i)
        if (before.game.hero.items[i] != after.game.hero.items[i])
            inventory[ItemDefinitions[i].id] = after.game.hero.items[i];
    Json::array_t tiles;
    const int floor = after.game.hero.floor;
    for (int i = 0; i < CellCount; ++i) {
        const int previous = visible_tile(before.game.tile(floor, i), developer);
        const int next = visible_tile(after.game.tile(floor, i), developer);
        if (previous != next)
            tiles.emplace_back(Json{{"x", i % BoardWidth}, {"y", i / BoardWidth}, {"id", next}});
    }
    return Json{{"stats", stats},
                {"inventory", inventory},
                {"tiles", tiles},
                {"floor_changed", before.game.hero.floor != floor}};
}

Json plan(const Session& session, int x, int y) {
    const auto& h = session.game.hero;
    const int start = cell(h.x, h.y), target = cell(x, y);
    std::array<int, CellCount> previous;
    previous.fill(-1);
    std::array<std::string_view, CellCount> direction;
    previous[start] = start;
    std::vector<int> queue{start};
    int best = start;
    const auto distance = [=](int i) { return std::abs(i % BoardWidth - x) + std::abs(i / BoardWidth - y); };
    if (!session.game.busy() && session.flight < 0)
        for (std::size_t n = 0; n < queue.size(); ++n) {
            const int current = queue[n];
            if (distance(current) < distance(best))
                best = current;
            if (current == target) {
                best = current;
                break;
            }
            constexpr std::array<int, 4> Dx{0, -1, 1, 0}, Dy{-1, 0, 0, 1};
            constexpr std::array<std::string_view, 4> Directions{"up", "left", "right", "down"};
            for (int d = 0; d < 4; ++d) {
                const int nx = current % BoardWidth + Dx[d], ny = current / BoardWidth + Dy[d];
                if (nx < 0 || nx >= BoardWidth || ny < 0 || ny >= BoardWidth)
                    continue;
                const int next = cell(nx, ny), t = visible_tile(session.game.tile(h.floor, next), false);
                if (previous[next] >= 0 || (next != target && t != Road))
                    continue;
                previous[next] = current;
                direction[next] = Directions[d];
                queue.push_back(next);
            }
        }
    Json::array_t directions;
    for (int i = best; i != start; i = previous[i])
        directions.emplace_back(direction[i]);
    std::reverse(directions.begin(), directions.end());
    return Json{{"directions", directions},
                {"floor", h.floor},
                {"reached", best == target},
                {"endpoint", Json{{"x", best % BoardWidth}, {"y", best / BoardWidth}}},
                {"note", "Only apparent road is traversed. The final input can contact an obstacle; doors "
                         "may require another input to enter. Events and hazards can interrupt a route."}};
}

Json navigate(Session& session, bool developer, int x, int y, bool interact) {
    const auto path = plan(session, x, y);
    const int floor = session.game.hero.floor;
    const int target = cell(x, y);
    Json result{{"target", Json{{"floor", floor}, {"x", x}, {"y", y}}},
                {"reached", false},
                {"inputs", 0},
                {"messages", Json::array_t{}}};
    if (session.game.busy() || session.flight >= 0) {
        result["reason"] = "interaction_open";
        return result;
    }
    if (!path["reached"].get<bool>()) {
        result["reason"] = "blocked_by_event";
        return result;
    }
    const int apparent = visible_tile(session.game.tile(floor, target), developer);
    if (apparent == Wall || apparent == Void || apparent == Lava || apparent == StarVoid ||
        apparent == SolidDecoration || apparent == AltarTop || apparent == AltarSide) {
        result["reason"] = "not_a_destination";
        return result;
    }
    auto step = [&](Direction direction) {
        session.act(PlayerInput::move(direction));
        result["inputs"] = result["inputs"].as<int>() + 1;
        for (const auto& message : session.last_action["messages"].get_array())
            result["messages"].get_array().push_back(message);
    };
    const auto& directions = path["directions"].get_array();
    for (std::size_t i = 0; i < directions.size(); ++i) {
        const auto name = directions[i].get<std::string>();
        const auto direction = name == "up"     ? Direction::Up
                               : name == "down" ? Direction::Down
                               : name == "left" ? Direction::Left
                                                : Direction::Right;
        const auto h = session.game.hero;
        const int nx = h.x + (direction == Direction::Left ? -1 : direction == Direction::Right ? 1 : 0);
        const int ny = h.y + (direction == Direction::Up ? -1 : direction == Direction::Down ? 1 : 0);
        const int tile = session.game.tile_at(floor, nx, ny);
        const bool final = i + 1 == directions.size();
        if (final && !interact && visible_tile(tile, false) != Road) {
            result["reason"] = "ready_to_interact";
            result["reached"] = true;
            return result;
        }
        step(direction);
        if (!session.last_action["ok"].get<bool>()) {
            result["reason"] = "refused";
            return result;
        }
        // Opening a selected door/secret wall and stepping inside remain two native inputs.
        if (final && session.game.hero.floor == floor && session.game.hero.x == h.x &&
            session.game.hero.y == h.y && !session.game.busy() &&
            (tile == YellowDoor || tile == BlueDoor || tile == RedDoor || tile == SecretWall) &&
            session.game.tile_at(floor, nx, ny) == Road)
            step(direction);
        if (session.game.hero.floor != floor) {
            result["reached"] = final && tile != Road && tile != SpecialRoad;
            result["reason"] =
                final && (tile == StairsUp || tile == StairsDown) ? "floor_changed" : "interrupted";
            return result;
        }
        if (session.game.busy() || session.game.hero.hp <= 0) {
            result["reached"] = final;
            result["reason"] = session.game.hero.hp <= 0 ? "dead" : "interaction_open";
            return result;
        }
        if (!final &&
            (tile == SpecialRoad || session.game.hero.x != nx || session.game.hero.y != ny ||
             session.game.hero.hp != h.hp || session.game.hero.attack != h.attack ||
             session.game.hero.defense != h.defense || session.game.hero.gold != h.gold ||
             session.game.hero.items != h.items || !session.last_action["messages"].get_array().empty())) {
            result["reason"] = "interrupted";
            return result;
        }
    }
    result["reached"] = true;
    result["reason"] = "arrived";
    return result;
}

Json action_schema() {
    auto object = [](Json properties, Json::array_t required) {
        return Json{{"type", "object"},
                    {"properties", properties},
                    {"required", required},
                    {"additionalProperties", false}};
    };
    auto type = [](std::string_view name) { return Json{{"const", name}, {"type", "string"}}; };
    Json::array_t alternatives;
    for (auto name : {"new_game", "flight_open", "flight_up", "flight_down", "flight_confirm", "cancel"})
        alternatives.push_back(object(Json{{"type", type(name)}}, {"type"}));
    const Json directions{{"type", "string"}, {"enum", Json::array_t{"up", "down", "left", "right"}}};
    alternatives.push_back(
        object(Json{{"type", type("move")}, {"direction", directions}}, {"type", "direction"}));
    Json::array_t item_ids;
    for (const auto& definition : ItemDefinitions)
        if (definition.id != "flying_orb")
            item_ids.emplace_back(definition.id);
    alternatives.push_back(
        object(Json{{"type", type("use_item")}, {"item", Json{{"type", "string"}, {"enum", item_ids}}}},
               {"type", "item"}));
    alternatives.push_back(object(Json{{"type", type("use_item")},
                                       {"item", type("flying_orb")},
                                       {"floor", Json{{"type", "integer"}, {"minimum", 1}, {"maximum", 50}}}},
                                  {"type", "item", "floor"}));
    const Json choices{{"type", "string"},
                       {"enum", Json::array_t{"leave", "accept", "hp", "attack", "defense", "0", "1", "2"}}};
    alternatives.push_back(object(Json{{"type", type("choose")}, {"choice", choices}}, {"type", "choice"}));
    const Json kinds{{"type", "string"}, {"enum", Json::array_t{"slot", "checkpoint"}}};
    for (auto name : {"save", "reload"})
        alternatives.push_back(object(Json{{"type", type(name)}, {"kind", kinds}}, {"type", "kind"}));
    return Json{{"oneOf", alternatives}};
}
} // namespace tsw::detail::mcp
