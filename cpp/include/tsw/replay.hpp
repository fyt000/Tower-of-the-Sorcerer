#pragma once
#include "tsw/game.hpp"
#include <iosfwd>
#include <span>

namespace tsw {
enum class InputKind {
    NewGame,
    Move,
    UseItem,
    Choose,
    OpenFlight,
    FlightUp,
    FlightDown,
    Travel,
    Cancel,
    Save,
    Reload
};

// Player commands belong to the application boundary, not the original command stack.
struct PlayerInput {
    InputKind kind = InputKind::NewGame;
    Direction direction = Direction::Up;
    Item item = Item::HeroOrb;
    int value = -1;
    SaveKind save_kind = SaveKind::Slot;
    friend bool operator==(const PlayerInput&, const PlayerInput&) = default;
};

PlayerInput parse_input(std::string_view);
std::string input_json(const PlayerInput&);
bool apply_input(Game&, int& flight, const PlayerInput&);
void settle_action(Game&);
std::string gameplay_json(const Game&, int flight = -1, int map_floor = -1);
std::vector<PlayerInput> read_replay(std::istream&);
std::filesystem::path recording_path(const std::filesystem::path& save);

// Rewind reconstructs a prefix through real actions, without snapshots or a state schema.
class ReplayPlayer {
  public:
    explicit ReplayPlayer(std::vector<PlayerInput> inputs);

    std::size_t position() const { return position_; }

    std::size_t size() const { return inputs_.size(); }

    bool finished() const { return position_ == inputs_.size(); }

    std::span<const PlayerInput> history() const { return {inputs_.data(), position_}; }

    bool next(Game&, int& flight);
    void seek(Game&, int& flight, std::size_t position);

  private:
    std::vector<PlayerInput> inputs_;
    std::size_t position_{};
};

class Recorder {
  public:
    explicit Recorder(bool enabled = false);

    bool enabled() const { return enabled_; }

    bool active() const { return history_.has_value(); }

    void enable(bool);
    void new_game();
    void stop();
    void resume(std::span<const PlayerInput>);
    void append(const PlayerInput&);
    void save(Game&, const std::filesystem::path&, SaveKind = SaveKind::Slot);
    // Loading the game succeeds independently of a missing or malformed companion.
    void load(Game&, const std::filesystem::path&, SaveKind = SaveKind::Slot);

  private:
    bool enabled_{};
    std::optional<std::vector<PlayerInput>> history_;
};
} // namespace tsw
