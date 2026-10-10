#pragma once
#include "tsw/replay.hpp"
#include <glaze/json/generic.hpp>
#include <map>
#include <utility>

namespace tsw::mcp_detail {
using Json = glz::generic_u64;
Json parse(std::string_view);
std::string dump(const Json&);

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

Json observe(const Session&, bool developer, int map_floor = -1, std::string_view detail = "full");
Json changes(const Session& before, const Session& after, bool developer);
Json navigate(Session&, bool developer, int x, int y, bool interact);
Json inspect(const Game&, bool developer, int floor, int x, int y);
Json plan(const Session&, int x, int y);
Json action_schema();
void checkpoint_runtime(const std::filesystem::path&, bool developer, const Session&,
                        const std::map<std::string, Session>&, std::uint64_t next_checkpoint);
void restore_runtime(const std::filesystem::path&, bool developer, Session&, std::map<std::string, Session>&,
                     std::uint64_t& next_checkpoint);
} // namespace tsw::mcp_detail
