#include "mcp_internal.hpp"
#include "tsw/game_state.hpp"
#include <algorithm>
#include <charconv>
#include <concepts>
#include <fstream>
#include <glaze/json.hpp>
#include <limits>
#include <stdexcept>

namespace tsw::mcp_detail {
namespace runtime_wire {
constexpr std::uint32_t RuntimeVersion = 1;
constexpr std::uintmax_t MaxRuntimeBytes = 128 * 1024 * 1024;

struct SessionState {
    GameState game;
    int flight = -1;
    std::uint64_t steps{};
    bool recording_enabled{};
    std::optional<std::vector<std::string>> history;
    Json last_action;
    Json::array_t log;
};

struct RuntimeState {
    std::uint32_t version{};
    bool developer{};
    SessionState session;
    std::map<std::string, SessionState> checkpoints;
    std::uint64_t next_checkpoint{};
};

// Glaze permits short std::arrays and omitted nullable members when reading
// ordinary records. A migration must include every field and array element.
template <typename T> void complete_shape(const T& value, const Json& source) {
    if constexpr (std::same_as<T, Json>) {
        return; // Action feedback and logs have their own validation below.
    } else if constexpr (glz::reflectable<T>) {
        const auto members = glz::to_tie(value);
        glz::for_each<glz::reflect<T>::size>([&]<std::size_t I> {
            const auto key = glz::reflect<T>::keys[I];
            if (!source.is_object() || !source.contains(key))
                throw std::runtime_error("Incomplete runtime object: " + std::string(key));
            complete_shape(glz::get<I>(members), source[key]);
        });
    } else if constexpr (glz::nullable_t<T>) {
        if (value)
            complete_shape(*value, source);
    } else if constexpr (glz::writable_map_t<T>) {
        for (const auto& [key, member] : value)
            complete_shape(member, source[key]);
    } else if constexpr (glz::writable_array_t<T>) {
        if (!source.is_array() || source.get_array().size() != value.size())
            throw std::runtime_error("Incomplete runtime array");
        std::size_t index{};
        for (const auto& member : value)
            complete_shape(member, source[index++]);
    }
}

SessionState capture(const Session& s) {
    SessionState result{GameState::capture(s.game),
                        s.flight,
                        s.steps,
                        s.recorder.enabled(),
                        std::nullopt,
                        s.last_action,
                        s.log};
    if (s.recorder.active()) {
        result.history.emplace();
        for (const auto& input : s.recorder.history())
            result.history->push_back(input_json(input));
    }
    return result;
}

Session restore(const SessionState& s) {
    Session result(s.game.restore());
    if (s.flight < -1 || s.flight >= FloorCount || s.flight == 0 || s.flight == 44 || s.log.size() > 100 ||
        s.steps == std::numeric_limits<std::uint64_t>::max() ||
        (!s.last_action.is_null() && !s.last_action.is_object()) ||
        (s.history && (!s.recording_enabled || s.history->empty())))
        throw std::runtime_error("Invalid runtime session");
    result.flight = s.flight;
    result.steps = s.steps;
    result.last_action = s.last_action;
    result.log = s.log;
    result.recorder.enable(s.recording_enabled);
    result.recorder.stop();
    if (!s.last_action.is_null()) {
        const auto& action = s.last_action;
        if (!action.contains("action") || !action.contains("accepted") || !action.contains("ok") ||
            !action.contains("moved") || !action.contains("messages") || !action.contains("message") ||
            !action["accepted"].holds<bool>() || !action["ok"].holds<bool>() ||
            !action["moved"].holds<bool>() || !action["messages"].is_array() ||
            !action["message"].is_string())
            throw std::runtime_error("Invalid runtime action feedback");
        parse_input(dump(action["action"]));
        for (const auto& message : action["messages"].get_array())
            if (!message.is_string())
                throw std::runtime_error("Invalid runtime action message");
    }
    if (s.history) {
        std::vector<PlayerInput> inputs;
        inputs.reserve(s.history->size());
        for (const auto& input : *s.history)
            inputs.push_back(parse_input(input));
        result.recorder.resume(inputs);
    }
    for (const auto& line : s.log)
        if (!line.is_object() || !line.contains("step") || !line.contains("text") ||
            !line["step"].holds<std::uint64_t>() || line["step"].get<std::uint64_t>() > s.steps ||
            !line["text"].is_string())
            throw std::runtime_error("Invalid runtime speech log");
    return result;
}
} // namespace runtime_wire

using namespace runtime_wire;

void checkpoint_runtime(const std::filesystem::path& path, bool developer, const Session& session,
                        const std::map<std::string, Session>& checkpoints, std::uint64_t next) {
    RuntimeState state{RuntimeVersion, developer, capture(session), {}, next};
    for (const auto& [id, saved] : checkpoints)
        state.checkpoints.emplace(id, capture(saved));
    std::string data;
    if (const auto error = glz::write<glz::opts{.skip_null_members = false}>(state, data))
        throw std::runtime_error(glz::format_error(error));
    if (data.size() > MaxRuntimeBytes)
        throw std::runtime_error("Runtime checkpoint exceeds 128 MiB");
    std::ofstream output(path, std::ios::binary | std::ios::trunc);
    output.write(data.data(), static_cast<std::streamsize>(data.size()));
    output.flush();
    if (!output)
        throw std::runtime_error("Unable to write runtime checkpoint");
}

void restore_runtime(const std::filesystem::path& path, bool developer, Session& session,
                     std::map<std::string, Session>& checkpoints, std::uint64_t& next) {
    if (std::filesystem::file_size(path) > MaxRuntimeBytes)
        throw std::runtime_error("Runtime checkpoint exceeds 128 MiB");
    std::ifstream input(path, std::ios::binary);
    if (!input)
        throw std::runtime_error("Unable to open runtime checkpoint");
    std::string data{std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>()};
    if (input.bad())
        throw std::runtime_error("Unable to read runtime checkpoint");

    struct Options : glz::opts {
        bool validate_trailing_whitespace = true;
    };

    constexpr auto options = [] {
        Options value;
        value.null_terminated = false;
        value.error_on_missing_keys = true;
        value.error_on_unknown_keys = true;
        return value;
    }();
    RuntimeState state{};
    if (const auto error = glz::read<options>(state, data))
        throw std::runtime_error(glz::format_error(error, data));
    complete_shape(state, parse(data));
    if (state.version != RuntimeVersion || state.developer != developer || state.checkpoints.size() > 64 ||
        state.next_checkpoint == std::numeric_limits<std::uint64_t>::max())
        throw std::runtime_error("Incompatible runtime checkpoint version, mode or checkpoint count");
    auto restored = restore(state.session);
    std::map<std::string, Session> restored_checkpoints;
    for (const auto& [id, saved] : state.checkpoints) {
        std::uint64_t number{};
        constexpr std::string_view prefix = "checkpoint-";
        const auto suffix = std::string_view(id).substr(std::min(id.size(), prefix.size()));
        const auto [end, error] = std::from_chars(suffix.data(), suffix.data() + suffix.size(), number);
        if (!id.starts_with(prefix) || error != std::errc{} || end != suffix.data() + suffix.size() ||
            number == 0 || number > state.next_checkpoint || id != "checkpoint-" + std::to_string(number))
            throw std::runtime_error("Invalid runtime checkpoint ID");
        restored_checkpoints.emplace(id, restore(saved));
    }
    // All parsing and validation completes before changing any live state.
    session = std::move(restored);
    checkpoints = std::move(restored_checkpoints);
    next = state.next_checkpoint;
}
} // namespace tsw::mcp_detail
