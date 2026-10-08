#include "tsw/replay.hpp"
#include <algorithm>
#include <charconv>
#include <limits>
#include <nlohmann/json.hpp>
#include <sstream>
#include <stdexcept>

namespace tsw {
namespace {
using Json = nlohmann::json;
constexpr std::array<std::string_view, 15> ItemIds{
    "hero_orb",      "wisdom_orb",   "flying_orb", "cross",         "elixir",
    "mattock",       "bomb",         "warp_staff", "ascent_wing",   "descent_wing",
    "dragon_slayer", "snow_crystal", "magic_key",  "super_mattock", "lucky_gold"};

std::string_view direction_id(Direction direction) {
    switch (direction) {
    case Direction::Up:
        return "up";
    case Direction::Down:
        return "down";
    case Direction::Left:
        return "left";
    case Direction::Right:
        return "right";
    }
    throw std::runtime_error("Unknown direction");
}

void fields(const Json& input, std::initializer_list<std::string_view> allowed) {
    for (auto field = input.begin(); field != input.end(); ++field)
        if (std::find(allowed.begin(), allowed.end(), field.key()) == allowed.end())
            throw std::runtime_error("Unknown input field: " + field.key());
}

int integer(const Json& input, const char* name) {
    const auto& value = input.at(name);
    if (!value.is_number_integer() || value < std::numeric_limits<int>::min() ||
        value > std::numeric_limits<int>::max())
        throw std::runtime_error(std::string(name) + " must be an integer in range");
    return value.get<int>();
}

void save_in_memory(Game& game, SaveKind kind, bool reload) {
    std::stringstream record(std::ios::in | std::ios::out | std::ios::binary);
    game.save(record, kind);
    if (reload)
        game.load(record, kind);
}
} // namespace

PlayerInput parse_input(std::string_view source) {
    const auto input = Json::parse(source);
    if (!input.is_object())
        throw std::runtime_error("Player input must be a JSON object");
    const auto type = input.at("type").get<std::string>();
    PlayerInput action;
    if (type == "move") {
        fields(input, {"type", "direction"});
        action.kind = InputKind::Move;
        const auto direction = input.at("direction").get<std::string>();
        if (direction == "up")
            action.direction = Direction::Up;
        else if (direction == "down")
            action.direction = Direction::Down;
        else if (direction == "left")
            action.direction = Direction::Left;
        else if (direction == "right")
            action.direction = Direction::Right;
        else
            throw std::runtime_error("Direction must be up, down, left or right");
    } else if (type == "use_item") {
        fields(input, {"type", "item", "floor"});
        action.kind = InputKind::UseItem;
        auto item = input.at("item").get<std::string>();
        if (item == "orb_of_flying")
            item = "flying_orb";
        const auto found = std::find(ItemIds.begin(), ItemIds.end(), item);
        if (found == ItemIds.end())
            throw std::runtime_error("Unknown item: " + item);
        action.item = static_cast<Item>(found - ItemIds.begin());
        if (input.contains("floor"))
            action.value = integer(input, "floor");
        if (action.item == Item::FlightOrb && !input.contains("floor"))
            throw std::runtime_error("Flying Orb requires a destination floor");
        if (action.item != Item::FlightOrb && input.contains("floor"))
            throw std::runtime_error("Only Flying Orb takes a destination floor");
    } else if (type == "choose") {
        fields(input, {"type", "choice"});
        action.kind = InputKind::Choose;
        const auto choice = input.at("choice").get<std::string>();
        if (choice == "leave")
            action.value = -1;
        else if (choice == "hp" || choice == "accept")
            action.value = 0;
        else if (choice == "attack")
            action.value = 1;
        else if (choice == "defense")
            action.value = 2;
        else {
            const auto [end, error] =
                std::from_chars(choice.data(), choice.data() + choice.size(), action.value);
            if (error != std::errc{} || end != choice.data() + choice.size() || action.value < 0 ||
                action.value > 2)
                throw std::runtime_error("Choice must be leave, hp, attack, defense, accept or 0..2");
        }
    } else if (type == "save" || type == "reload") {
        fields(input, {"type", "kind"});
        action.kind = type == "save" ? InputKind::Save : InputKind::Reload;
        const auto kind = input.at("kind").get<std::string>();
        if (kind == "checkpoint")
            action.save_kind = SaveKind::Checkpoint;
        else if (kind != "slot")
            throw std::runtime_error("Save kind must be slot or checkpoint");
    } else {
        fields(input, {"type"});
        if (type == "new_game")
            action.kind = InputKind::NewGame;
        else if (type == "flight_open")
            action.kind = InputKind::OpenFlight;
        else if (type == "flight_up")
            action.kind = InputKind::FlightUp;
        else if (type == "flight_down")
            action.kind = InputKind::FlightDown;
        else if (type == "flight_confirm")
            action.kind = InputKind::Travel;
        else if (type == "cancel")
            action.kind = InputKind::Cancel;
        else
            throw std::runtime_error("Unknown player input: " + type);
    }
    return action;
}

std::string input_json(const PlayerInput& action) {
    Json input;
    switch (action.kind) {
    case InputKind::NewGame:
        input = {{"type", "new_game"}};
        break;
    case InputKind::Move:
        input = {{"type", "move"}, {"direction", direction_id(action.direction)}};
        break;
    case InputKind::UseItem:
        input = {{"type", "use_item"}, {"item", ItemIds.at(static_cast<int>(action.item))}};
        if (action.item == Item::FlightOrb)
            input["floor"] = action.value;
        break;
    case InputKind::Choose:
        input = {{"type", "choose"}, {"choice", action.value < 0 ? "leave" : std::to_string(action.value)}};
        break;
    case InputKind::OpenFlight:
        input = {{"type", "flight_open"}};
        break;
    case InputKind::FlightUp:
        input = {{"type", "flight_up"}};
        break;
    case InputKind::FlightDown:
        input = {{"type", "flight_down"}};
        break;
    case InputKind::Travel:
        input = {{"type", "flight_confirm"}};
        break;
    case InputKind::Cancel:
        input = {{"type", "cancel"}};
        break;
    case InputKind::Save:
    case InputKind::Reload:
        input = {{"type", action.kind == InputKind::Save ? "save" : "reload"},
                 {"kind", action.save_kind == SaveKind::Slot ? "slot" : "checkpoint"}};
        break;
    }
    return input.dump();
}

bool apply_input(Game& game, int& flight, const PlayerInput& input) {
    switch (input.kind) {
    case InputKind::NewGame:
        game.new_game();
        flight = -1;
        return true;
    case InputKind::Move:
        if (flight >= 0)
            throw std::runtime_error("Close the Flight selector before moving");
        return game.move(input.direction);
    case InputKind::UseItem:
        // A direct flight follows the same monotonically selected route as the desktop.
        if (input.item == Item::FlightOrb && !game.busy() && game.inventory(input.item) > 0 &&
            input.value >= 1 && input.value <= game.hero.highest_floor && input.value != 44) {
            game.hero.flight_direction = 0;
            int floor = game.hero.floor;
            const int step = input.value > floor ? 1 : -1;
            while (floor != input.value) {
                floor += step;
                if (floor == 44)
                    floor += step;
                game.flight_preview(floor, step > 0 ? 1 : 2);
            }
        }
        return game.use(input.item, input.value);
    case InputKind::Choose:
        if (game.dialogue && !game.dialogue->shop && input.value < 0)
            return game.continue_dialogue();
        return game.choose(input.value);
    case InputKind::OpenFlight:
        if (game.busy() || game.inventory(Item::FlightOrb) <= 0)
            return false;
        flight = game.hero.floor;
        game.hero.flight_direction = 0;
        return true;
    case InputKind::FlightUp:
    case InputKind::FlightDown: {
        if (flight < 0)
            throw std::runtime_error("Flight selector is not open");
        const bool up = input.kind == InputKind::FlightUp;
        const int next = up ? (flight == 43 ? 45 : flight + 1) : (flight == 45 ? 43 : flight - 1);
        if (!game.flight_preview(next, up ? 1 : 2))
            return false;
        flight = next;
        return true;
    }
    case InputKind::Travel: {
        if (flight < 0)
            throw std::runtime_error("Flight selector is not open");
        const bool used = game.use(Item::FlightOrb, flight);
        flight = -1;
        return used;
    }
    case InputKind::Cancel:
        if (flight >= 0) {
            flight = -1;
            return true;
        }
        return game.choose(-1);
    case InputKind::Save:
    case InputKind::Reload:
        save_in_memory(game, input.save_kind, input.kind == InputKind::Reload);
        if (input.kind == InputKind::Reload)
            flight = -1;
        return true;
    }
    throw std::runtime_error("Unknown player input");
}

void settle_action(Game& game) {
    game.finish_commands(true);
    if (game.checkpoint_requested && !game.busy()) {
        game.checkpoint_requested = false;
        save_in_memory(game, SaveKind::Checkpoint, false);
    }
    game.sounds.clear(); // A headless run has no device consuming sound cues.
}

std::string gameplay_json(const Game& game, int flight, int map_floor) {
    const auto& h = game.hero;
    if (map_floor < 0)
        map_floor = h.floor;
    Json inventory = Json::object();
    for (std::size_t i = 0; i < ItemIds.size(); ++i)
        inventory[ItemIds[i]] = h.items[i];
    Json dialogue = nullptr;
    if (game.dialogue)
        dialogue = {{"text", game.dialogue->text},
                    {"shop", game.dialogue->shop},
                    {"choices", game.dialogue->choices}};
    return Json{{"hero",
                 {{"floor", h.floor},
                  {"x", h.x},
                  {"y", h.y},
                  {"hp", h.hp},
                  {"attack", h.attack},
                  {"defense", h.defense},
                  {"gold", h.gold},
                  {"highest_floor", h.highest_floor},
                  {"yellow_keys", h.yellow_keys},
                  {"blue_keys", h.blue_keys},
                  {"red_keys", h.red_keys}}},
                {"inventory", inventory},
                {"map_floor", map_floor},
                {"map", game.floors.at(map_floor).tiles},
                {"flight", flight},
                {"dialogue", dialogue},
                {"dead", h.hp <= 0 || game.visual.dead},
                {"status", game.status}}
        .dump();
}

std::vector<PlayerInput> read_replay(std::istream& stream) {
    std::vector<PlayerInput> inputs;
    std::string line;
    std::size_t number{};
    while (std::getline(stream, line)) {
        ++number;
        if (line.find_first_not_of(" \t\r") == std::string::npos)
            continue;
        try {
            inputs.push_back(parse_input(line));
        } catch (const std::exception& error) {
            throw std::runtime_error("Line " + std::to_string(number) + ": " + error.what());
        }
    }
    if (stream.bad())
        throw std::runtime_error("Unable to read recording");
    return inputs;
}
} // namespace tsw
