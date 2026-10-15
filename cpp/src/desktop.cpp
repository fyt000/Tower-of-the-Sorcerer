#include "desktop_session.hpp"
#include <algorithm>
#include <filesystem>
#include <iostream>
#include <string>
#include <tuple>

using namespace tsw;

namespace {
UiAction keyboard(const Game& game, DesktopUi& ui) {
    if (ui.rankings) {
        if (IsKeyPressed(KEY_ESCAPE)) {
            ui.close_overlays();
            return {};
        }
        const int step = IsKeyPressed(KEY_LEFT) ? -1 : IsKeyPressed(KEY_RIGHT) ? 1 : 0;
        if (step)
            return {Action::RankingCategory, ui.ranking_category + step};
        if (ui.ranking_entry && ui.ranking_entry_category == ui.ranking_category &&
            !ui.ranking_reset_confirmation) {
            if ((IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE)) &&
                !ui.ranking_name.empty()) {
                auto last = ui.ranking_name.size() - 1;
                while (last && (static_cast<unsigned char>(ui.ranking_name[last]) & 0xc0) == 0x80)
                    --last;
                ui.ranking_name.resize(last);
            }
            for (int codepoint = GetCharPressed(); codepoint; codepoint = GetCharPressed())
                if (codepoint >= 32) {
                    int size{};
                    const auto* text = CodepointToUTF8(codepoint, &size);
                    if (ui.ranking_name.size() + size <= RankingNameLimit)
                        ui.ranking_name.append(text, size);
                }
            if (IsKeyPressed(KEY_ENTER) && !ui.ranking_name.empty())
                return {Action::SubmitRanking};
        }
        return {};
    }
    if (ui.replay_picker) {
        if (IsKeyPressed(KEY_ESCAPE)) {
            ui.close_overlays();
            return {};
        }
        const int step = IsKeyPressed(KEY_UP) ? -1 : IsKeyPressed(KEY_DOWN) ? 1 : 0;
        if (step && !ui.replay_files.empty()) {
            ui.replay_selected = std::clamp(ui.replay_selected + step, 0, int(ui.replay_files.size()) - 1);
            const auto path = ui.replay_files[ui.replay_selected].u8string();
            ui.replay_path.assign(path.begin(), path.end());
            ui.replay_first_row =
                std::clamp(ui.replay_first_row, std::max(0, ui.replay_selected - 4), ui.replay_selected);
        }
        const bool control = IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL);
        if (ui.replay_path_focus && control && IsKeyPressed(KEY_V))
            if (const auto* clipboard = GetClipboardText())
                ui.replay_path = clipboard;
        if (ui.replay_path_focus && (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE)) &&
            !ui.replay_path.empty()) {
            auto last = ui.replay_path.size() - 1;
            while (last && (static_cast<unsigned char>(ui.replay_path[last]) & 0xc0) == 0x80)
                --last;
            ui.replay_path.resize(last);
        }
        for (int codepoint = GetCharPressed(); codepoint; codepoint = GetCharPressed())
            if (ui.replay_path_focus && !control && codepoint >= 32) {
                int size{};
                const auto* text = CodepointToUTF8(codepoint, &size);
                ui.replay_path.append(text, size);
            }
        return IsKeyPressed(KEY_ENTER) && !ui.replay_path.empty() ? UiAction{Action::PlayReplay} : UiAction{};
    }
    if (ui.save_picker != SavePicker::None) {
        if (ui.save_picker == SavePicker::Load) {
            if (IsKeyPressed(KEY_F9) && ui.quick_available)
                return {Action::Load};
            if (IsKeyPressed(KEY_F8) && ui.fairy_available)
                return {Action::FairyCheckpoint};
        }
        if (IsKeyPressed(KEY_ESCAPE)) {
            ui.close_overlays();
            return {};
        }
        for (int number = 1; number <= ManualSaveSlotCount; ++number)
            if (IsKeyPressed(KEY_ONE + number - 1) || IsKeyPressed(KEY_KP_1 + number - 1))
                ui.selected_slot = number;
        const int step = IsKeyPressed(KEY_UP)      ? -2
                         : IsKeyPressed(KEY_DOWN)  ? 2
                         : IsKeyPressed(KEY_LEFT)  ? -1
                         : IsKeyPressed(KEY_RIGHT) ? 1
                                                   : 0;
        ui.selected_slot = std::clamp(ui.selected_slot + step, 1, ManualSaveSlotCount);
        if (IsKeyPressed(KEY_ENTER) && (ui.save_picker == SavePicker::Save ||
                                        ui.save_slots[ui.selected_slot - 1].state == SaveSlotState::Ready))
            return {ui.save_picker == SavePicker::Save ? Action::SaveSlot : Action::LoadSlot,
                    ui.selected_slot};
        return {};
    }
    if (IsKeyPressed(KEY_M))
        return {Action::Mute};
    if (ui.menu != Menu::None || ui.help) {
        if (IsKeyPressed(KEY_ESCAPE))
            ui.close_overlays();
        return {};
    }
    if (ui.home) {
        if (IsKeyPressed(KEY_F2))
            return {Action::NewGame};
        if (IsKeyPressed(KEY_F7))
            return {Action::OpenLoadSlots};
        const int step = IsKeyPressed(KEY_UP) ? -1 : IsKeyPressed(KEY_DOWN) ? 1 : 0;
        if (step)
            ui.home_selection = std::clamp(ui.home_selection + step, ui.game_started ? 0 : 1, 4);
        constexpr std::array<Action, 5> actions{Action::ResumeGame, Action::NewGame, Action::OpenLoadSlots,
                                                Action::OpenReplays, Action::OpenSettings};
        return IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE) ? UiAction{actions[ui.home_selection]}
                                                                  : UiAction{};
    }
    if (ui.ending_wait) {
        if (!ui.replay_active) {
            if (IsKeyPressed(KEY_ESCAPE))
                return {Action::MainMenu};
            return IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE) ? UiAction{Action::ContinueEnding}
                                                                      : UiAction{};
        }
    }
    if (ui.replay_active) {
        if (game.dialogue)
            ui.dialogue_scroll = std::max(0.f, ui.dialogue_scroll - GetMouseWheelMove() * 35);
        if (IsKeyPressed(KEY_SPACE))
            return {Action::ReplayPause};
        if (IsKeyPressed(KEY_LEFT))
            return {Action::ReplayPrevious};
        if (IsKeyPressed(KEY_RIGHT))
            return {Action::ReplayNext};
        if (IsKeyPressed(KEY_HOME))
            return {Action::ReplayRestart};
        if (IsKeyPressed(KEY_T))
            return {Action::ReplayTakeOver};
        if (IsKeyPressed(KEY_O))
            return {Action::OpenSettings};
        if (IsKeyPressed(KEY_MINUS))
            return {Action::ReplaySpeed, ui.replay_speed_index - 1};
        if (IsKeyPressed(KEY_EQUAL))
            return {Action::ReplaySpeed, ui.replay_speed_index + 1};
        return IsKeyPressed(KEY_ESCAPE) ? UiAction{Action::MainMenu} : UiAction{};
    }
    if (IsKeyPressed(KEY_F2))
        return {Action::NewGame};
    if (IsKeyPressed(KEY_R) && !game.busy() && ui.flight < 0)
        return {Action::OpenRankings};
    if (IsKeyPressed(KEY_F5) && ui.file_controls_enabled())
        return {Action::Save};
    if (IsKeyPressed(KEY_F6) && ui.file_controls_enabled())
        return {Action::OpenSaveSlots};
    if (IsKeyPressed(KEY_F7) && ui.file_controls_enabled())
        return {Action::OpenLoadSlots};
    if (IsKeyPressed(KEY_F9) && ui.file_controls_enabled())
        return {Action::Load};
    if (IsKeyPressed(KEY_F8) && ui.file_controls_enabled())
        return {Action::FairyCheckpoint};
    if (ui.enemies) {
        if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_ENTER))
            ui.close_overlays();
        ui.enemy_first_row -= int(GetMouseWheelMove());
        if (IsKeyPressed(KEY_UP))
            --ui.enemy_first_row;
        if (IsKeyPressed(KEY_DOWN))
            ++ui.enemy_first_row;
        return {};
    }
    if (game.dialogue) {
        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE))
            return {game.dialogue->shop ? Action::Choose : Action::Continue};
        if (IsKeyPressed(KEY_ESCAPE) && game.dialogue->shop)
            return {Action::Choose, -1};
        ui.dialogue_scroll = std::max(0.f, ui.dialogue_scroll - GetMouseWheelMove() * 35);
    } else if (IsKeyPressed(KEY_ESCAPE)) {
        if (ui.modal())
            ui.close_overlays();
        else if (ui.flight >= 0)
            return {Action::CancelFlight};
        else
            return {Action::MainMenu};
    } else if (ui.selected_item >= 0) {
        if (IsKeyPressed(KEY_ENTER))
            return {Action::UseItem, ui.selected_item};
    } else if (IsKeyPressed(KEY_I) && !game.busy() && ui.flight < 0) {
        const bool opened = ui.inventory;
        ui.close_overlays();
        ui.inventory = !opened;
    } else if (ui.flight >= 0 && !ui.modal()) {
        if (IsKeyPressed(KEY_UP))
            return {Action::FlightUp};
        if (IsKeyPressed(KEY_DOWN))
            return {Action::FlightDown};
        if (IsKeyPressed(KEY_ENTER))
            return {Action::Travel};
    }
    return {};
}
} // namespace

int main(int argc, char** argv) try {
    const std::filesystem::path executable = GetApplicationDirectory();
    auto executable_file = executable / std::filesystem::path(argv[0]).filename();
#ifdef _WIN32
    if (!std::filesystem::exists(executable_file))
        executable_file += ".exe";
#endif
    std::filesystem::path requested_assets, load_file, replay_file, screenshot;
    auto save_directory = executable / "Savedat";
    std::optional<bool> record;
    std::optional<Language> language;
    SaveKind load_kind = SaveKind::Slot;
    for (int i = 1; i < argc; ++i) {
        const std::string arg = argv[i];
        if (arg == "--assets" && i + 1 < argc)
            requested_assets = argv[++i];
        else if (arg == "--save-dir" && i + 1 < argc)
            save_directory = argv[++i];
        else if (arg == "--load" && i + 1 < argc)
            load_file = argv[++i];
        else if (arg == "--replay" && i + 1 < argc)
            replay_file = argv[++i];
        else if (arg == "--screenshot" && i + 1 < argc)
            screenshot = argv[++i];
        else if (arg == "--record")
            record = true;
        else if (arg == "--language" && i + 1 < argc)
            language = parse_language(argv[++i]);
        else if (arg == "--checkpoint")
            load_kind = SaveKind::Checkpoint;
        else if (arg == "--help") {
            std::cout << "Tower of the Sorcerer original cpp\n"
                         "Arrows / WASD: move. Enter: continue. I: inventory.\n"
                         "F6 / F7: eight save / load slots. F5 / F9: quick save / restore.\n"
                         "F8: Fairy checkpoint. F2: new game. M: mute. R: Fairy rankings.\n"
                         "Saves: Savedat/save1.dat through save8.dat beside this executable.\n"
                         "--assets DIR --save-dir DIR --load FILE\n"
                         "--replay FILE: watch a JSONL recording with visual controls.\n"
                         "Replay: Space pause/resume, Left previous, Right next, Home restart, T take over.\n"
                         "Replay: -/+ speed, O settings, Esc main menu. Drop a replay file to watch it.\n"
                         "--record: opt in to save companion replay recordings.\n"
                         "--language en|ja|en-ja|zh-Hans-ja|zh-Hans-en: select display language.\n"
                         "--checkpoint: use raw Fairy format with --load.\n"
                         "--screenshot FILE: capture the initial frame and exit.\n";
            return 0;
        } else
            throw std::runtime_error("Unknown argument: " + arg);
    }
    if (load_kind == SaveKind::Checkpoint && load_file.empty())
        throw std::runtime_error("--checkpoint requires --load FILE");
    if (!load_file.empty() && !replay_file.empty())
        throw std::runtime_error("Choose --load or --replay");
    Assets assets(Assets::select(executable, requested_assets, TSW_ORIGINAL_ASSETS, TSW_ASSETS),
                  executable_file);
    std::cout << "Assets: " << assets.root()
              << (assets.original_layout() ? " (original layout)\n" : " (PNG layout)\n");
    std::cout << "Saves: " << save_directory << '\n';
    const bool hidden = !screenshot.empty();
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI | FLAG_VSYNC_HINT |
                   (hidden ? FLAG_WINDOW_HIDDEN : 0));
    SetTraceLogLevel(LOG_WARNING);
    InitWindow(CanvasWidth, CanvasHeight, "Tower of the Sorcerer");
    SetWindowMinSize(640, 447);
    SetExitKey(KEY_NULL);
    SetTargetFPS(hidden ? 0 : 60);
    int result = 0;
    {
        DesktopSession session(assets, save_directory, {}, record);
        if (language)
            session.ui.language = *language;
        if (!load_file.empty())
            session.load(load_file, load_kind);
        else if (!replay_file.empty())
            session.replay(replay_file);
        else
            session.open_home(true);
        auto& game = session.game;
        auto& ui = session.ui;
        auto& renderer = session.renderer;
        WalkRepeat walking;
        while (!WindowShouldClose()) {
            if (IsFileDropped()) {
                const auto files = LoadDroppedFiles();
                if (files.count) {
                    ui.replay_path = files.paths[0];
                    session.dispatch({Action::PlayReplay});
                }
                UnloadDroppedFiles(files);
            }
            session.dispatch(keyboard(game, ui));
            const float game_elapsed = session.scaled_seconds(std::min(GetFrameTime(), .1f));
            renderer.advance(game_elapsed);
            if (!ui.replay_active && !game.dialogue && ui.flight < 0 && !ui.modal() && !game.busy()) {
                walking.advance(game_elapsed);
                for (const auto [key, alternative, direction] :
                     std::array<std::tuple<int, int, Direction>, 4>{{{KEY_UP, KEY_W, Direction::Up},
                                                                     {KEY_DOWN, KEY_S, Direction::Down},
                                                                     {KEY_LEFT, KEY_A, Direction::Left},
                                                                     {KEY_RIGHT, KEY_D, Direction::Right}}})
                    if (walking.ready(IsKeyPressed(key) || IsKeyPressed(alternative),
                                      IsKeyDown(key) || IsKeyDown(alternative))) {
                        session.move(direction);
                        walking.stepped();
                        break;
                    }
            }
            session.advance_commands(game_elapsed);
            session.dispatch(renderer.draw(game, ui, renderer.mouse_position()));
            renderer.present();
            if (!screenshot.empty()) {
                result = renderer.screenshot(screenshot) ? 0 : 1;
                break;
            }
        }
    }
    CloseWindow();
    return result;
} catch (const std::exception& error) {

    std::cerr << error.what() << '\n';
    return 1;
}
