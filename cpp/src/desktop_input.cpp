#include "presentation.hpp"
#include <algorithm>

namespace tsw {
bool game_shortcut_modifiers() {
    return !IsKeyDown(KEY_LEFT_CONTROL) && !IsKeyDown(KEY_RIGHT_CONTROL) && !IsKeyDown(KEY_LEFT_ALT) &&
           !IsKeyDown(KEY_RIGHT_ALT) && !IsKeyDown(KEY_LEFT_SUPER) && !IsKeyDown(KEY_RIGHT_SUPER);
}

UiAction keyboard_input(const Game& game, DesktopUi& ui) {
    const bool shift = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);
    if (!game_shortcut_modifiers() && !ui.rankings && !ui.replay_picker)
        return {};
#ifdef __ANDROID__
    if (IsKeyPressed(KEY_BACK)) {
        if (ui.modal())
            ui.close_overlays();
        else if (ui.flight >= 0)
            return {Action::CancelFlight};
        else
            return {Action::MainMenu};
        return {};
    }
#endif
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
        if (IsKeyPressed(KEY_L))
            return {shift ? Action::LoadAutosave : Action::OpenLoadSlots};
        if (ui.save_picker != SavePicker::Save) {
            if (shift && IsKeyPressed(KEY_Q) && ui.quick_available)
                return {Action::Load};
            if (shift && IsKeyPressed(KEY_F) && ui.fairy_available)
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
        if (IsKeyPressed(KEY_ESCAPE) ||
            (ui.menu == Menu::About && (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE))))
            ui.close_overlays();
        return {};
    }
    if (ui.home) {
        if (shift && IsKeyPressed(KEY_N))
            return {Action::NewGame};
        if (IsKeyPressed(KEY_L))
            return {shift ? Action::LoadAutosave : Action::OpenLoadSlots};
        const int step = IsKeyPressed(KEY_UP) ? -1 : IsKeyPressed(KEY_DOWN) ? 1 : 0;
        if (step)
            ui.home_selection = std::clamp(ui.home_selection + step, ui.game_started ? 0 : 1, 5);
        constexpr std::array<Action, 6> actions{Action::ResumeGame,    Action::NewGame,
                                                Action::OpenLoadSlots, Action::OpenReplays,
                                                Action::OpenSettings,  Action::OpenAbout};
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
    if (shift && IsKeyPressed(KEY_N))
        return {Action::NewGame};
    if (IsKeyPressed(KEY_R) && !game.busy() && ui.flight < 0)
        return {Action::OpenRankings};
    if (IsKeyPressed(KEY_Q) && ui.file_controls_enabled())
        return {shift ? Action::Load : Action::Save};
    if (IsKeyPressed(KEY_K) && ui.file_controls_enabled())
        return {Action::OpenSaveSlots};
    if (IsKeyPressed(KEY_L) && ui.file_controls_enabled())
        return {shift ? Action::LoadAutosave : Action::OpenLoadSlots};
    if (shift && IsKeyPressed(KEY_F) && ui.file_controls_enabled())
        return {Action::FairyCheckpoint};
    if (IsKeyPressed(KEY_O))
        return {Action::OpenSettings};
    if (IsKeyPressed(KEY_H) && !ui.modal()) {
        ui.help = true;
        return {};
    }
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

} // namespace tsw
