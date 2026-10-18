#include "desktop_session.hpp"
#include "tsw/blink.hpp"
#include <algorithm>
#include <format>
#include <fstream>
#include <stdexcept>
#include <utility>

namespace tsw {
namespace {
std::string path_text(const std::filesystem::path& path) {
    const auto text = path.u8string();
    return {text.begin(), text.end()};
}

std::filesystem::path text_path(const std::string& text) {
    std::string_view path = text;
    const auto first = path.find_first_not_of(" \t\r\n"), last = path.find_last_not_of(" \t\r\n");
    if (first == std::string_view::npos)
        throw std::runtime_error("Choose a recording file");
    path = path.substr(first, last - first + 1);
    if (path.size() >= 2 && path.front() == '"' && path.back() == '"')
        path = path.substr(1, path.size() - 2);
    return std::filesystem::path(std::u8string(path.begin(), path.end()));
}
} // namespace

DesktopSession::DesktopSession(const Assets& assets, const std::filesystem::path& save_directory,
                               Game initial, std::optional<bool> record)
    : game(std::move(initial)), renderer(assets), audio(assets), save_directory_(save_directory) {
    refresh_rankings();
    Settings settings;
    try {
        settings = load_settings(save_directory_ / "settings.json");
    } catch (const std::exception& error) {
        game.status = error.what();
        ui.notice = error.what();
    }
    ui.game_speed_index = settings.game_speed_index;
    ui.replay_speed_index = settings.replay_speed_index;
    ui.muted = settings.muted;
    ui.hero_orb_actual_damage = settings.hero_orb_actual_damage;
    ui.mouse_walking = settings.mouse_walking;
    ui.blink_mode = settings.blink_mode;
    ui.item_collection = settings.item_collection;
    ui.realtime_hero_orb = settings.realtime_hero_orb;
    ui.touch_controls = settings.touch_controls;
    ui.language = parse_language(settings.language);
    recorder_.enable(record.value_or(settings.recording));
    recorder_.new_game(game.rankings);
    recording_status();
    audio.mute(ui.muted);
    audio.restart(game);
}

void DesktopSession::dispatch(UiAction action) {
    if (action.kind != Action::None && action.kind != Action::WalkTo)
        mouse_walk_.cancel();
    const auto before = game.hero;
    try {
        apply(action);
    } catch (const std::exception& error) {
        game.status = error.what();
        ui.notice = error.what();
    }
    if ((!ui.mouse_walking && !ui.blink_mode) || ui.modal() || ui.replay_active || ui.flight >= 0 ||
        ui.ending_wait)
        mouse_walk_.cancel();
    if (action.kind != Action::Move) // move() already starts the manual walking animation.
        renderer.moved(before, game.hero);
    recording_status();
}

float DesktopSession::scaled_seconds(float real_seconds) const {
    if (ui.home)
        return real_seconds;
    if (ui.modal() || (ui.replay_active && ui.replay_paused))
        return 0;
    return real_seconds *
           (ui.replay_active ? ReplaySpeeds[ui.replay_speed_index] : GameSpeeds[ui.game_speed_index]);
}

void DesktopSession::move(Direction direction) {
    mouse_walk_.cancel();
    if (ui.modal() || ui.replay_active || ui.flight >= 0 || ui.ending_wait)
        return;
    move_step(direction, true);
}

void DesktopSession::move_step(Direction direction, bool manual) {
    // Read the category files before a Fairy encounter can calculate its rank.
    const int x = game.hero.x + (direction == Direction::Right) - (direction == Direction::Left);
    const int y = game.hero.y + (direction == Direction::Down) - (direction == Direction::Up);
    if (!game.busy() && x >= 0 && x < BoardWidth && y >= 0 && y < BoardWidth) {
        const auto target = game.tile_at(game.hero.floor, x, y);
        if (target == Fairy || target == Fairy2)
            refresh_rankings();
    }
    const auto before = game.hero;
    play(PlayerInput::move(direction));
    renderer.moved(before, game.hero, manual);
}

bool DesktopSession::play(const PlayerInput& input) {
    // Busy movement/item input has no effects and is not a gameplay decision.
    if (game.busy() && (input.kind == InputKind::Move || input.kind == InputKind::UseItem ||
                        input.kind == InputKind::OpenFlight))
        return false;
    const bool result = apply_input(game, ui.flight, input);
    recorder_.append(input);
    return result;
}

void DesktopSession::recording_status() {
    ui.recording_enabled = recorder_.enabled();
    ui.recording_active = recorder_.active();
    if (replay_) {
        ui.replay_step = replay_->position();
        ui.replay_count = replay_->size();
        ui.replay_in_progress = replay_action_;
    }
    audio.speed(ui.home            ? 1.f
                : ui.replay_active ? ReplaySpeeds[ui.replay_speed_index]
                                   : GameSpeeds[ui.game_speed_index]);
    audio.suspend(ui.replay_active && !ui.home && (ui.replay_paused || ui.modal()));
}

void DesktopSession::preferences() {
    save_settings(save_directory_ / "settings.json", {.game_speed_index = ui.game_speed_index,
                                                      .replay_speed_index = ui.replay_speed_index,
                                                      .recording = recorder_.enabled(),
                                                      .muted = ui.muted,
                                                      .hero_orb_actual_damage = ui.hero_orb_actual_damage,
                                                      .language = std::string(language_id(ui.language)),
                                                      .mouse_walking = ui.mouse_walking,
                                                      .realtime_hero_orb = ui.realtime_hero_orb,
                                                      .touch_controls = ui.touch_controls,
                                                      .blink_mode = ui.blink_mode,
                                                      .item_collection = ui.item_collection});
}

void DesktopSession::open_home(bool startup) {
    mouse_walk_.cancel();
    ui.close_overlays();
    ui.home = true;
    ui.home_selection = ui.game_started && !startup ? 0 : 1;
    if (startup) {
        ui.game_started = false;
        recorder_.stop();
    }
    if (replay_)
        ui.replay_paused = true;
    Game opening;
    opening.visual.raster_mode = RasterMode::Title;
    audio.suspend(false);
    audio.restart(opening);
    recording_status();
}

void DesktopSession::load(const std::filesystem::path& path, SaveKind kind) {
    mouse_walk_.cancel();
    recorder_.load(game, path, kind);
    replay_.reset();
    ui.replay_active = ui.replay_paused = false;
    refresh_rankings();
    ui.home = false;
    ui.game_started = true;
    renderer.reset();
    ui.close_overlays();
    ui.flight = -1;
    ui.ending_wait = false;
    accumulator_ = 0;
    previous_dialogue_.clear();
    audio.suspend(false);
    audio.restart(game);
    recording_status();
}

void DesktopSession::refresh_rankings() {
    game.rankings = load_rankings(save_directory_);
    if (!ui.replay_active)
        recorder_.rankings(game.rankings);
}

void DesktopSession::open_rankings(bool submission) {
    ui.close_overlays();
    if (!ui.replay_active)
        refresh_rankings();
    ui.rankings = true;
    ui.ranking_category = std::clamp(std::to_underlying(game.hero.fairy_category), 1, RankingCategoryCount);
    if (submission && game.hero.fairy_rank > 0) {
        const auto& hero = game.hero;
        ui.ranking_entry = RankingEntry{hero.fairy_score, hero.hp, hero.attack, hero.defense, {}};
        ui.ranking_entry_category = ui.ranking_category;
        // Fairy contact caches the insertion position; reloading rows does not rerank it.
        ui.ranking_position = game.hero.fairy_rank;
    }
}

void DesktopSession::replay(const std::filesystem::path& path) {
    mouse_walk_.cancel();
    std::ifstream input(path, std::ios::binary);
    if (!input)
        throw std::runtime_error("Unable to open replay: " + path_text(path));
    ReplayPlayer player(read_replay(input));
    player.seek(game, ui.flight, 0);
    replay_ = std::move(player);
    recorder_.stop();
    renderer.reset();
    ui.close_overlays();
    ui.home = false;
    ui.game_started = ui.replay_active = true;
    ui.replay_paused = ui.ending_wait = false;
    ui.replay_name = path_text(path.filename());
    ui.replay_error.clear();
    replay_action_ = replay_single_step_ = false;
    accumulator_ = replay_age_ = replay_speech_ = 0;
    previous_dialogue_.clear();
    audio.suspend(false);
    audio.restart(game);
    recording_status();
}

void DesktopSession::seek_replay(std::size_t step) {
    replay_->seek(game, ui.flight, step);
    replay_action_ = replay_single_step_ = false;
    replay_commands_ = 0;
    accumulator_ = replay_age_ = replay_speech_ = 0;
    previous_dialogue_.clear();
    ui.replay_paused = true;
    ui.ending_wait = false;
    ui.replay_error.clear();
    renderer.reset();
    audio.restart(game);
}

bool DesktopSession::advance_queue(float seconds) {
    accumulator_ += seconds;
    bool blocked = false;
    for (int commands = 0; commands < 64; ++commands) {
        if (ui.ending_wait || ui.save_picker != SavePicker::None) {
            accumulator_ = 0;
            break;
        }
        const float beat = command_interval(game);
        if (accumulator_ < beat)
            break;
        Command command;
        const bool backside = game.hero.cycle_factor_minus_one != 0;
        if (!game.run_one(&command)) {
            accumulator_ = 0;
            blocked = true;
            break;
        }
        if (replay_ && ++replay_commands_ > 10000000)
            throw std::runtime_error("Replay action exceeded ten million operations");
        renderer.command(command);
        // 0x482E60 mode 8 stops the original timer until the player continues.
        if (command.op == Op::Callback && command.a == int(Callback::RasterScene) &&
            game.visual.raster_mode == RasterMode::ClosingCard) {
            ui.ending_wait = true;
            replay_speech_ = 0;
        }
        if (backside && command.op == Op::Callback && command.a == int(Callback::NextCycle)) {
            ui.ending_wait = true;
            replay_speech_ = 0;
        }
        accumulator_ -= beat;
    }
    audio.update(game);
    return blocked;
}

void DesktopSession::advance_replay(float seconds) {
    if (ui.replay_paused)
        return;
    constexpr float SpeechSeconds = 1.2f;
    try {
        if (!replay_action_) {
            if (replay_->finished()) {
                ui.replay_paused = true;
                return;
            }
            const auto before = game.hero;
            replay_->next(game, ui.flight);
            const auto kind = replay_->history().back().kind;
            if (kind == InputKind::NewGame || kind == InputKind::Reload) {
                renderer.reset();
                ui.ending_wait = false;
                audio.restart(game);
            }
            renderer.moved(before, game.hero);
            replay_action_ = true;
            replay_commands_ = 0;
            replay_age_ = replay_speech_ = 0;
        }
        replay_age_ += seconds;
        if (game.dialogue || ui.ending_wait) {
            replay_speech_ += seconds;
            if (replay_speech_ >= SpeechSeconds) {
                if (ui.ending_wait)
                    ui.ending_wait = false;
                else if (!game.dialogue->shop)
                    game.continue_dialogue();
            }
        }
        const bool blocked = advance_queue(seconds);
        if (game.checkpoint_requested && !game.busy()) {
            game.checkpoint_requested = false;
            apply_input(game, ui.flight, PlayerInput::save(SaveKind::Checkpoint));
        }
        const bool shop = game.dialogue && game.dialogue->shop;
        // The empty-queue run also clears transient layers/door frames before a paused boundary.
        if ((shop || (blocked && !game.dialogue && !ui.ending_wait)) &&
            (shop ? replay_speech_ >= SpeechSeconds : replay_age_ >= ReplayStepSeconds)) {
            replay_action_ = false;
            accumulator_ = 0;
            if (replay_single_step_ || replay_->finished()) {
                replay_single_step_ = false;
                ui.replay_paused = true;
            }
        }
    } catch (const std::exception& error) {
        ui.replay_error =
            std::format("Step {}: {}", replay_->position() + (replay_action_ ? 0 : 1), error.what());
        ui.replay_paused = true;
    }
}

void DesktopSession::advance_commands(float seconds) {
    if ((!ui.mouse_walking && !ui.blink_mode) || ui.modal() || ui.replay_active || ui.flight >= 0 ||
        ui.ending_wait)
        mouse_walk_.cancel();
    if (ui.home || ui.replay_picker || ui.rankings || ui.save_picker != SavePicker::None ||
        ui.menu != Menu::None || ui.help) {
        recording_status();
        return;
    }
    if (replay_)
        advance_replay(seconds);
    else {
        mouse_walk_.advance(game, seconds, [this](Direction direction) { move_step(direction); });
        advance_queue(seconds);
        if (game.checkpoint_requested && !game.busy()) {
            game.checkpoint_requested = false;
            try {
                recorder_.save(game, save_directory_ / "save0.dat", SaveKind::Checkpoint);
            } catch (const std::exception& error) {
                game.status = error.what();
            }
        }
    }
    recording_status();
    const auto dialogue = game.dialogue ? game.dialogue->text : std::string();
    if (dialogue != previous_dialogue_) {
        ui.dialogue_scroll = 0;
        replay_speech_ = 0;
        previous_dialogue_ = dialogue;
    }
}

void DesktopSession::apply(UiAction action) {
    if (ui.ending_wait && !ui.replay_active && action.kind != Action::ContinueEnding &&
        action.kind != Action::MainMenu && action.kind != Action::ResumeGame &&
        action.kind != Action::NewGame && action.kind != Action::Mute)
        return;
    switch (action.kind) {
    case Action::Save:
    case Action::SaveSlot:
    case Action::OpenSaveSlots:
    case Action::Load:
    case Action::LoadSlot:
    case Action::OpenLoadSlots:
    case Action::FairyCheckpoint:
        // Original item, Hero Orb and Flight panels call 0x450758. Enforce
        // their file-control gate here as well as in the rendered buttons:
        // shortcuts and direct dispatch must obey the same modal state.
        if (!ui.file_controls_enabled())
            throw std::runtime_error("Close the item or Orb panel before saving or loading");
        break;
    default:
        break;
    }
    if (ui.replay_active && !ui.home)
        switch (action.kind) {
        case Action::Save:
        case Action::SaveSlot:
        case Action::OpenSaveSlots:
        case Action::Continue:
        case Action::ContinueEnding:
        case Action::Choose:
        case Action::UseItem:
        case Action::FlightUp:
        case Action::FlightDown:
        case Action::Travel:
        case Action::CancelFlight:
            return;
        default:
            break;
        }
    switch (action.kind) {
    case Action::Move:
        move(static_cast<Direction>(action.value));
        break;
    case Action::ScrollDialogue:
        if (game.dialogue)
            ui.dialogue_scroll = std::max(0.f, ui.dialogue_scroll + action.value);
        break;
    case Action::WalkTo:
        if ((ui.mouse_walking || ui.blink_mode) && !ui.modal() && !ui.replay_active && ui.flight < 0 &&
            !ui.ending_wait) {
            mouse_walk_.cancel();
            if (!ui.blink_mode ||
                !blink_to(game, action.value, [this](Direction direction) { move_step(direction); }))
                mouse_walk_.start(game, action.value);
        }
        break;
    case Action::CollectAll:
    case Action::CollectExceptPotions:
        if (!ui.item_collection || game.busy() || ui.modal() || ui.replay_active || ui.flight >= 0 ||
            ui.ending_wait || game.visual.raster_mode != RasterMode::Inactive || renderer.collecting())
            break;
        {
            const auto collected =
                collect_items(game, action.kind == Action::CollectExceptPotions,
                              [this](Direction direction) { play(PlayerInput::move(direction)); });
            renderer.collected(game.hero.floor, collected);
            game.status = collected.empty() ? "No safely reachable items to collect."
                          : action.kind == Action::CollectExceptPotions
                              ? "Collected reachable items. Potions were left untouched."
                              : "Collected all safely reachable items.";
        }
        break;
    case Action::MainMenu:
        open_home();
        break;
    case Action::Language:
        ui.language = Languages.at(action.value);
        ui.dialogue_scroll = 0;
        preferences();
        break;
    case Action::ResumeGame:
        if (!ui.game_started)
            break;
        ui.close_overlays();
        ui.home = false;
        audio.restart(game);
        break;
    case Action::OpenSettings:
        ui.close_overlays();
        ui.menu = Menu::Options;
        break;
    case Action::OpenAbout:
        ui.close_overlays();
        ui.menu = Menu::About;
        break;
    case Action::NewGame:
        game.new_game();
        refresh_rankings();
        replay_.reset();
        ui.replay_active = ui.replay_paused = ui.home = false;
        ui.game_started = true;
        recorder_.new_game(game.rankings);
        renderer.reset();
        audio.suspend(false);
        audio.restart(game);
        ui.close_overlays();
        ui.flight = -1;
        ui.ending_wait = false;
        accumulator_ = 0;
        previous_dialogue_.clear();
        ui.notice.clear();
        break;
    case Action::OpenReplays:
        ui.close_overlays();
        ui.notice.clear();
        ui.replay_files.clear();
        if (std::filesystem::is_directory(save_directory_))
            for (const auto& entry : std::filesystem::directory_iterator(save_directory_))
                if (entry.is_regular_file() && entry.path().extension() == ".jsonl")
                    ui.replay_files.push_back(entry.path());
        std::ranges::sort(ui.replay_files);
        ui.replay_selected = ui.replay_first_row = 0;
        ui.replay_path = ui.replay_files.empty() ? "" : path_text(ui.replay_files.front());
        ui.replay_path_focus = true;
        ui.replay_picker = true;
        break;
    case Action::OpenRankings:
        if (!game.busy() || ui.home)
            open_rankings();
        break;
    case Action::RankingCategory:
        ui.ranking_category = std::clamp(action.value, 1, RankingCategoryCount);
        ui.ranking_reset_confirmation = false;
        break;
    case Action::SubmitRanking:
        if (ui.rankings && !ui.replay_active && ui.ranking_entry &&
            ui.ranking_entry_category == ui.ranking_category) {
            auto table = game.rankings[ui.ranking_category - 1];
            auto entry = *ui.ranking_entry;
            entry.name = ui.ranking_name;
            insert_ranking(table, ui.ranking_position, std::move(entry));
            write_rankings(save_directory_, ui.ranking_category, table);
            game.rankings[ui.ranking_category - 1] = std::move(table);
            recorder_.rankings(game.rankings);
            ui.ranking_entry.reset();
            ui.ranking_name.clear();
            ui.ranking_reset_confirmation = false;
        }
        break;
    case Action::ResetRankings:
        if (ui.rankings && !ui.replay_active) {
            if (!ui.ranking_reset_confirmation)
                ui.ranking_reset_confirmation = true;
            else {
                game.rankings[ui.ranking_category - 1] = reset_rankings(save_directory_, ui.ranking_category);
                recorder_.rankings(game.rankings);
                ui.ranking_reset_confirmation = false;
            }
        }
        break;
    case Action::PlayReplay:
        replay(text_path(ui.replay_path));
        break;
    case Action::ReplayPause:
        if (replay_ && ui.replay_error.empty() && (!replay_->finished() || replay_action_)) {
            ui.replay_paused = !ui.replay_paused;
            replay_single_step_ = false;
        }
        break;
    case Action::ReplayPrevious:
        if (replay_ && replay_->position() > 0)
            seek_replay(replay_->position() - 1);
        break;
    case Action::ReplayRestart:
        if (replay_)
            seek_replay(0);
        break;
    case Action::ReplayNext:
        if (replay_ && ui.replay_error.empty() && (!replay_->finished() || replay_action_)) {
            ui.replay_paused = false;
            replay_single_step_ = true;
        }
        break;
    case Action::ReplayTakeOver:
        if (replay_ && ui.replay_error.empty()) {
            recorder_.resume(replay_->history());
            replay_.reset();
            replay_action_ = replay_single_step_ = false;
            ui.replay_active = ui.replay_paused = false;
            ui.close_overlays();
            game.status = "You now control the hero.";
            audio.suspend(false);
        }
        break;
    case Action::ReplaySpeed:
        ui.replay_speed_index = std::clamp(action.value, 0, int(ReplaySpeeds.size()) - 1);
        preferences();
        break;
    case Action::Save:
        recorder_.save(game, save_directory_ / "quick.save");
        game.status = "Quick save written.";
        break;
    case Action::OpenSaveSlots:
    case Action::OpenLoadSlots:
        if (action.kind == Action::OpenSaveSlots && game.busy())
            throw std::runtime_error("Finish the current action before saving");
        ui.save_slots = inspect_save_slots(save_directory_);
        ui.quick_available = std::filesystem::is_regular_file(save_directory_ / "quick.save");
        ui.fairy_available = std::filesystem::is_regular_file(save_directory_ / "save0.dat");
        ui.close_overlays();
        ui.save_picker = action.kind == Action::OpenSaveSlots ? SavePicker::Save : SavePicker::Load;
        if (ui.save_picker == SavePicker::Load &&
            ui.save_slots[ui.selected_slot - 1].state != SaveSlotState::Ready)
            for (int number = 1; number <= ManualSaveSlotCount; ++number)
                if (ui.save_slots[number - 1].state == SaveSlotState::Ready) {
                    ui.selected_slot = number;
                    break;
                }
        break;
    case Action::SaveSlot:
        recorder_.save(game, save_slot_path(save_directory_, action.value));
        ui.selected_slot = action.value;
        ui.close_overlays();
        game.status = std::format("Saved to slot {}.", action.value);
        break;
    case Action::Load:
    case Action::FairyCheckpoint:
    case Action::LoadSlot:
        load(action.kind == Action::LoadSlot
                 ? save_slot_path(save_directory_, action.value)
                 : save_directory_ / (action.kind == Action::Load ? "quick.save" : "save0.dat"),
             action.kind == Action::FairyCheckpoint ? SaveKind::Checkpoint : SaveKind::Slot);
        if (action.kind == Action::LoadSlot) {
            ui.selected_slot = action.value;
            game.status = std::format("Restored slot {}. {}", action.value, game.status);
        }
        break;
    case Action::Continue: {
        const auto stage = game.dialogue ? game.dialogue->continuation : ContinuationStage::None;
        const bool fairy = !game.hero.cycle_factor_minus_one && is_fairy_continuation(stage);
        game.continue_dialogue();
        if (fairy)
            open_rankings(true);
    } break;
    case Action::ContinueEnding:
        ui.ending_wait = false;
        accumulator_ = 0;
        break;
    case Action::Choose:
        play(PlayerInput::choose(action.value));
        break;
    case Action::UseItem: {
        const auto item = static_cast<Item>(action.value);
        ui.close_overlays();
        if (item == Item::FlightOrb)
            play({InputKind::OpenFlight});
        else if (item == Item::HeroOrb && play(PlayerInput::use_item(item))) {
            ui.enemies = true;
            ui.enemy_first_row = 0;
        } else if (item != Item::HeroOrb)
            play(PlayerInput::use_item(item));
        break;
    }
    case Action::FlightUp:
    case Action::FlightDown:
        play({action.kind == Action::FlightUp ? InputKind::FlightUp : InputKind::FlightDown});
        break;
    case Action::Travel:
        play({InputKind::Travel});
        break;
    case Action::CancelFlight:
        play({InputKind::Cancel});
        break;
    case Action::Mute:
        ui.muted = !ui.muted;
        audio.mute(ui.muted);
        preferences();
        break;
    case Action::Speed:
        ui.game_speed_index = std::clamp(action.value, 0, int(GameSpeeds.size()) - 1);
        preferences();
        break;
    case Action::Recording:
        recorder_.enable(!recorder_.enabled());
        preferences();
        game.status = recorder_.enabled()
                          ? "Recording enabled for new games, recorded loads and replay takeover."
                          : "Replay recording disabled.";
        break;
    case Action::HeroOrbActualDamage:
        ui.hero_orb_actual_damage = !ui.hero_orb_actual_damage;
        preferences();
        break;
    case Action::MouseWalking:
        ui.mouse_walking = !ui.mouse_walking;
        preferences();
        break;
    case Action::BlinkMode:
        ui.blink_mode = !ui.blink_mode;
        preferences();
        break;
    case Action::ItemCollection:
        ui.item_collection = !ui.item_collection;
        preferences();
        break;
    case Action::RealtimeHeroOrb:
        ui.realtime_hero_orb = !ui.realtime_hero_orb;
        preferences();
        break;
    case Action::TouchControls:
        ui.touch_controls = !ui.touch_enabled();
        preferences();
        break;
    case Action::None:
        break;
    }
}
} // namespace tsw
