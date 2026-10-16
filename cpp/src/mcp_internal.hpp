#pragma once
#include "tsw/replay.hpp"
#include <glaze/json/generic.hpp>
#include <map>
#include <stdexcept>
#include <utility>

namespace tsw::detail::mcp {
using Json = glz::generic_u64;
Json parse(std::string_view);
std::string dump(const Json&);

struct IncompatibleRuntimeCheckpoint : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct Session {
    Game game;
    int flight = -1;
    std::uint64_t steps{};
    Recorder recorder{true};
    Json last_action;
    Json::array_t log;

    explicit Session(Game initial = Game{}) : game(std::move(initial)) {
        recorder.new_game(game.rankings);
        steps = recorder.history().size() - 1;
    }

    void act(const PlayerInput&);
    void record(const PlayerInput&, const InputOutcome&);
};

enum class ObservationDetail { Summary, Compact, Full };

constexpr std::string_view observation_detail_name(ObservationDetail detail) {
    switch (detail) {
    case ObservationDetail::Summary:
        return "summary";
    case ObservationDetail::Compact:
        return "compact";
    case ObservationDetail::Full:
        return "full";
    }
    return {};
}

Json observe(const Session&, bool developer, int map_floor = -1,
             ObservationDetail detail = ObservationDetail::Full);
Json changes(const Session& before, const Session& after, bool developer);
Json navigate(Session&, bool developer, int x, int y, bool interact);
Json inspect(const Game&, bool developer, int floor, int x, int y);
Json plan(const Session&, int x, int y);
Json action_schema();
void checkpoint_runtime(const std::filesystem::path&, bool developer, const Session&,
                        const std::map<std::string, Session>&, std::uint64_t next_checkpoint);
void restore_runtime(const std::filesystem::path&, bool developer, Session&, std::map<std::string, Session>&,
                     std::uint64_t& next_checkpoint);
} // namespace tsw::detail::mcp
