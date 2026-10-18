#pragma once
#include "tsw/game.hpp"
#include <functional>
#include <iosfwd>
#include <memory>
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
    Reload,
    Rankings
};

// Player commands belong to the application boundary, not the original command stack.
struct PlayerInput {
    InputKind kind = InputKind::NewGame;
    Direction direction = Direction::Up;
    Item item = Item::HeroOrb;
    int value = -1;
    SaveKind save_kind = SaveKind::Slot;
    std::shared_ptr<const RankingTables> rankings;

    static PlayerInput move(Direction direction) { return {.kind = InputKind::Move, .direction = direction}; }

    static PlayerInput use_item(Item item, int floor = -1) {
        return {.kind = InputKind::UseItem, .item = item, .value = floor};
    }

    static PlayerInput choose(int choice) { return {.kind = InputKind::Choose, .value = choice}; }

    static PlayerInput save(SaveKind kind = SaveKind::Slot) {
        return {.kind = InputKind::Save, .save_kind = kind};
    }

    static PlayerInput reload(SaveKind kind = SaveKind::Slot) {
        return {.kind = InputKind::Reload, .save_kind = kind};
    }

    friend bool operator==(const PlayerInput& left, const PlayerInput& right) {
        return left.kind == right.kind && left.direction == right.direction && left.item == right.item &&
               left.value == right.value && left.save_kind == right.save_kind &&
               (left.rankings ? right.rankings && *left.rankings == *right.rankings : !right.rankings);
    }
};

PlayerInput parse_input(std::string_view);
std::string input_json(const PlayerInput&);
bool apply_input(Game&, int& flight, const PlayerInput&);
void settle_action(Game&, std::vector<std::string>* speech = nullptr);

// Settled execution shared by headless clients and replay seek. Animated playback
// deliberately uses apply_input alone and lets the desktop drain the command stack.
struct InputOutcome {
    bool accepted{}, ok{}, moved{};
    std::vector<std::string> speech, messages;
    std::string message;
};

InputOutcome execute_input(Game&, int& flight, const PlayerInput&);
using InputObserver = std::function<void(const PlayerInput&, const InputOutcome&)>;
std::string gameplay_json(const Game&, int flight = -1, int map_floor = -1);
std::optional<PlayerInput> read_replay_input(std::istream&, std::size_t& line_number);
std::vector<PlayerInput> read_replay(std::istream&);
void write_replay(std::ostream&, std::span<const PlayerInput>);
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
    void seek(Game&, int& flight, std::size_t position, const InputObserver& = {});

  private:
    std::vector<PlayerInput> inputs_;
    std::size_t position_{};
};

class Recorder {
  public:
    explicit Recorder(bool enabled = false);

    bool enabled() const { return enabled_; }

    bool active() const { return history_.has_value(); }

    std::span<const PlayerInput> history() const {
        return history_ ? std::span<const PlayerInput>(*history_) : std::span<const PlayerInput>{};
    }

    void enable(bool);
    void new_game(const RankingTables& = default_rankings());
    void stop();
    void resume(std::span<const PlayerInput>);
    void append(const PlayerInput&);
    // Sparse environment records keep external ranking changes deterministic.
    void rankings(const RankingTables&);
    void save(Game&, const std::filesystem::path&, SaveKind = SaveKind::Slot);
    // Loading the game succeeds independently of a missing or malformed companion.
    void load(Game&, const std::filesystem::path&, SaveKind = SaveKind::Slot);

  private:
    bool enabled_{};
    std::optional<std::vector<PlayerInput>> history_;
};

// Application-only floor-entry saves; the native command queue and replay format stay unchanged.
class FloorAutosave {
  public:
    void reset(const Game&, bool save_current = false);
    bool update(Game&, Recorder&, const std::filesystem::path& directory, bool ready = true);

  private:
    int floor_ = -1, cycle_{}, later_cycle_{};
    bool pending_{};
};
} // namespace tsw
