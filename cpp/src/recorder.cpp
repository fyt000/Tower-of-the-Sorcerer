#include "tsw/replay.hpp"
#include <fstream>
#include <stdexcept>
#include <utility>

namespace tsw {
namespace {
void write_recording(const std::filesystem::path& path, const std::vector<PlayerInput>& history) {
    std::ofstream output(path, std::ios::binary | std::ios::trunc);
    write_replay(output, history);
    output.flush();
    if (!output)
        throw std::runtime_error("Unable to write replay recording");
}

void remove_temporary(const std::filesystem::path& path) {
    std::error_code ignored;
    std::filesystem::remove(path, ignored);
}

void record_rankings(std::vector<PlayerInput>& history, const RankingTables& tables) {
    const RankingTables* previous = nullptr;
    for (auto input = history.rbegin(); input != history.rend(); ++input)
        if (input->kind == InputKind::Rankings) {
            if (!input->rankings)
                throw std::runtime_error("Ranking input is missing its tables");
            previous = input->rankings.get();
            break;
        }
    if (previous ? *previous == tables : tables == default_rankings())
        return;
    PlayerInput update{InputKind::Rankings};
    update.rankings = std::make_shared<const RankingTables>(tables);
    history.push_back(std::move(update));
}
} // namespace

std::filesystem::path recording_path(const std::filesystem::path& save) {
    auto path = save;
    path += ".replay.jsonl";
    return path;
}

Recorder::Recorder(bool enabled) : enabled_(enabled) {}

void Recorder::enable(bool enabled) {
    enabled_ = enabled;
    if (!enabled)
        history_.reset();
}

void Recorder::new_game(const RankingTables& tables) {
    history_.reset();
    if (enabled_) {
        history_ = std::vector<PlayerInput>{{InputKind::NewGame}};
        record_rankings(*history_, tables);
    }
}

void Recorder::stop() {
    history_.reset();
}

void Recorder::resume(std::span<const PlayerInput> history) {
    history_.reset();
    if (!enabled_)
        return;
    if (history.empty()) {
        new_game();
        return;
    }
    if (history.front().kind != InputKind::NewGame)
        throw std::runtime_error("A recording must begin with a new game command");
    history_ = std::vector<PlayerInput>(history.begin(), history.end());
}

void Recorder::append(const PlayerInput& input) {
    if (history_)
        history_->push_back(input);
}

void Recorder::rankings(const RankingTables& tables) {
    if (history_)
        record_rankings(*history_, tables);
}

void Recorder::save(Game& game, const std::filesystem::path& path, SaveKind kind) {
    const auto companion = recording_path(path);
    auto temporary = companion;
    temporary += ".tmp";
    auto pending = companion;
    pending += ".pending";
    auto backup_save = path;
    backup_save += ".bak";
    const auto backup_companion = recording_path(backup_save);
    const bool previous = std::filesystem::exists(companion);
    const bool previous_save = std::filesystem::exists(path);
    if (previous && !std::filesystem::is_regular_file(companion))
        throw std::runtime_error("Replay companion must be a regular file");
    const PlayerInput saved{InputKind::Save, Direction::Up, Item::HeroOrb, -1, kind};

    if (!path.parent_path().empty())
        std::filesystem::create_directories(path.parent_path());
    auto snapshot = history_;
    if (snapshot) {
        record_rankings(*snapshot, game.rankings);
        snapshot->push_back(saved);
        try {
            write_recording(temporary, *snapshot);
        } catch (...) {
            remove_temporary(temporary);
            throw;
        }
    }
    // Remove the old companion before replacing its save, so an interrupted write
    // leaves an unrecorded save rather than a recording for the wrong playthrough.
    try {
        if (previous)
            std::filesystem::rename(companion, pending);
        game.save(path, kind);
    } catch (...) {
        if (previous && std::filesystem::exists(pending))
            std::filesystem::rename(pending, companion);
        remove_temporary(temporary);
        throw;
    }
    try {
        std::filesystem::remove(backup_companion);
        if (previous && previous_save)
            std::filesystem::rename(pending, backup_companion);
        else
            remove_temporary(pending);
        if (history_) {
            std::filesystem::rename(temporary, companion);
            std::filesystem::last_write_time(companion, std::filesystem::last_write_time(path));
            history_ = std::move(snapshot);
        }
    } catch (const std::exception& error) {
        history_.reset();
        remove_temporary(companion);
        remove_temporary(temporary);
        remove_temporary(pending);
        throw std::runtime_error(std::string("Game saved, but recording was stopped: ") + error.what());
    }
}

void Recorder::load(Game& game, const std::filesystem::path& path, SaveKind kind) {
    game.load(path, kind);
    history_.reset();
    if (!enabled_)
        return;
    const auto companion = recording_path(path);
    try {
        if (!std::filesystem::exists(companion)) {
            game.status += " No replay recording for this save.";
            return;
        }
        if (std::filesystem::last_write_time(path) > std::filesystem::last_write_time(companion))
            throw std::runtime_error("Save is newer than its recording");
        std::ifstream input(companion, std::ios::binary);
        if (!input)
            throw std::runtime_error("Unable to open replay recording");
        auto history = read_replay(input);
        if (history.empty() || history.front().kind != InputKind::NewGame ||
            history.back().kind != InputKind::Save || history.back().save_kind != kind)
            throw std::runtime_error("Recording is not a complete history for this save kind");
        history.push_back({InputKind::Reload, Direction::Up, Item::HeroOrb, -1, kind});
        history_ = std::move(history);
        game.status += " Replay recording resumed.";
    } catch (const std::exception& error) {
        game.status += std::string(" Recording unavailable: ") + error.what();
    }
}
} // namespace tsw
