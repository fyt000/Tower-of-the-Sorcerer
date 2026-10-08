#include "tsw/replay.hpp"
#include <algorithm>
#include <charconv>
#include <glaze/json.hpp>
#include <map>
#include <sstream>
#include <stdexcept>

namespace tsw {
namespace replay_json {
// Glaze reflects these wire records; gameplay state keeps its native layout.
struct InputType {
    std::string type;
};

struct MoveInput {
    std::string type;
    std::string direction;
};

struct ItemInput {
    std::string type;
    std::string item;
};

struct FlightInput {
    std::string type;
    std::string item;
    int floor;
};

struct ChoiceInput {
    std::string type;
    std::string choice;
};

struct SaveInput {
    std::string type;
    std::string kind;
};

struct HeroValues {
    int floor, x, y;
    std::int32_t hp, attack, defense, gold;
    int highest_floor, yellow_keys, blue_keys, red_keys;
};

struct DialogueValues {
    std::string_view text;
    bool shop;
    std::array<std::string_view, 3> choices;
};

struct GameplayValues {
    HeroValues hero;
    std::map<std::string_view, int> inventory;
    int map_floor;
    std::array<std::uint8_t, CellCount> map;
    int flight;
    std::optional<DialogueValues> dialogue;
    bool dead;
    std::string_view status;
};
} // namespace replay_json

namespace {
using namespace replay_json;
constexpr std::array<std::string_view, 15> ItemIds{
    "hero_orb",      "wisdom_orb",   "flying_orb", "cross",         "elixir",
    "mattock",       "bomb",         "warp_staff", "ascent_wing",   "descent_wing",
    "dragon_slayer", "snow_crystal", "magic_key",  "super_mattock", "lucky_gold"};

struct ReadOptions : glz::opts {
    bool validate_skipped = true;
    bool validate_trailing_whitespace = true;
};

template <typename T, bool AllowUnknown = false> T read_input(std::string_view source) {
    constexpr auto options = [] {
        ReadOptions result;
        result.null_terminated = false;
        result.error_on_missing_keys = true;
        result.error_on_unknown_keys = !AllowUnknown;
        return result;
    }();
    T input{};
    if (const auto error = glz::read<options>(input, source))
        throw std::runtime_error(glz::format_error(error, source));
    return input;
}

template <typename T> std::string write_json(const T& value) {
    std::string result;
    if (const auto error = glz::write<glz::opts{.skip_null_members = false}>(value, result))
        throw std::runtime_error(glz::format_error(error));
    return result;
}

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

void save_in_memory(Game& game, SaveKind kind, bool reload) {
    std::stringstream record(std::ios::in | std::ios::out | std::ios::binary);
    game.save(record, kind);
    if (reload)
        game.load(record, kind);
}
} // namespace

PlayerInput parse_input(std::string_view source) {
    // Read the discriminator first, then let the selected record enforce its fields.
    const auto type = read_input<InputType, true>(source).type;
    PlayerInput action;
    if (type == "move") {
        action.kind = InputKind::Move;
        const auto direction = read_input<MoveInput>(source).direction;
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
        action.kind = InputKind::UseItem;
        auto item = read_input<ItemInput, true>(source).item;
        if (item == "orb_of_flying")
            item = "flying_orb";
        const auto found = std::find(ItemIds.begin(), ItemIds.end(), item);
        if (found == ItemIds.end())
            throw std::runtime_error("Unknown item: " + item);
        action.item = static_cast<Item>(found - ItemIds.begin());
        if (action.item == Item::FlightOrb)
            action.value = read_input<FlightInput>(source).floor;
        else
            read_input<ItemInput>(source);
    } else if (type == "choose") {
        action.kind = InputKind::Choose;
        const auto choice = read_input<ChoiceInput>(source).choice;
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
        action.kind = type == "save" ? InputKind::Save : InputKind::Reload;
        const auto kind = read_input<SaveInput>(source).kind;
        if (kind == "checkpoint")
            action.save_kind = SaveKind::Checkpoint;
        else if (kind != "slot")
            throw std::runtime_error("Save kind must be slot or checkpoint");
    } else {
        read_input<InputType>(source);
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
    switch (action.kind) {
    case InputKind::NewGame:
        return write_json(InputType{"new_game"});
    case InputKind::Move:
        return write_json(MoveInput{"move", std::string(direction_id(action.direction))});
    case InputKind::UseItem:
        if (action.item == Item::FlightOrb)
            return write_json(FlightInput{"use_item", "flying_orb", action.value});
        return write_json(ItemInput{"use_item", std::string(ItemIds.at(static_cast<int>(action.item)))});
    case InputKind::Choose:
        return write_json(ChoiceInput{"choose", action.value < 0 ? "leave" : std::to_string(action.value)});
    case InputKind::OpenFlight:
        return write_json(InputType{"flight_open"});
    case InputKind::FlightUp:
        return write_json(InputType{"flight_up"});
    case InputKind::FlightDown:
        return write_json(InputType{"flight_down"});
    case InputKind::Travel:
        return write_json(InputType{"flight_confirm"});
    case InputKind::Cancel:
        return write_json(InputType{"cancel"});
    case InputKind::Save:
    case InputKind::Reload:
        return write_json(SaveInput{action.kind == InputKind::Save ? "save" : "reload",
                                    action.save_kind == SaveKind::Slot ? "slot" : "checkpoint"});
    }
    throw std::runtime_error("Unknown player input");
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
    GameplayValues view{{h.floor, h.x, h.y, h.hp, h.attack, h.defense, h.gold, h.highest_floor, h.yellow_keys,
                         h.blue_keys, h.red_keys},
                        {},
                        map_floor,
                        game.floors.at(map_floor).tiles,
                        flight,
                        std::nullopt,
                        h.hp <= 0 || game.visual.dead,
                        game.status};
    for (std::size_t i = 0; i < ItemIds.size(); ++i)
        view.inventory.emplace(ItemIds[i], h.items[i]);
    if (game.dialogue) {
        const auto& d = *game.dialogue;
        view.dialogue = DialogueValues{d.text, d.shop, {d.choices[0], d.choices[1], d.choices[2]}};
    }
    return write_json(view);
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
