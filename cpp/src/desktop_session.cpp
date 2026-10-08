#include "desktop_session.hpp"
#include <stdexcept>
#include <utility>

namespace tsw {
DesktopSession::DesktopSession(const Assets& assets, const std::filesystem::path& save_directory,
                               Game initial, bool record)
    : game(std::move(initial)), renderer(assets), audio(assets), save_directory_(save_directory),
      recorder_(record) {
    recorder_.new_game();
    recording_status();
    audio.restart(game);
}

void DesktopSession::dispatch(UiAction action) {
    const auto before = game.hero;
    try {
        apply(action);
    } catch (const std::exception& error) {
        game.status = error.what();
    }
    renderer.moved(before, game.hero);
    recording_status();
}

void DesktopSession::move(Direction direction) {
    const auto before = game.hero;
    play({InputKind::Move, direction});
    renderer.moved(before, game.hero);
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
}

void DesktopSession::load(const std::filesystem::path& path, SaveKind kind) {
    recorder_.load(game, path, kind);
    renderer.reset();
    ui.close_overlays();
    ui.flight = -1;
    ui.ending_wait = false;
    accumulator_ = 0;
    audio.restart(game);
    recording_status();
}

void DesktopSession::advance_commands(float seconds) {
    accumulator_ += seconds;
    for (int commands = 0; commands < 64; ++commands) {
        if (ui.ending_wait || ui.save_picker != SavePicker::None) {
            accumulator_ = 0;
            break;
        }
        const float beat = command_interval(game);
        if (accumulator_ < beat)
            break;
        Command command;
        if (!game.run_one(&command)) {
            accumulator_ = 0;
            break;
        }
        renderer.command(command);
        // 0x482E60 mode 8 stops the original timer until the player continues.
        if (command.op == Op::Callback && command.a == int(Callback::RasterScene) &&
            game.visual.raster_mode == 8) {
            ui.ending_wait = true;
        }
        accumulator_ -= beat;
    }
    audio.update(game);
    if (game.checkpoint_requested && !game.busy()) {
        game.checkpoint_requested = false;
        try {
            recorder_.save(game, save_directory_ / "save0.dat", SaveKind::Checkpoint);
        } catch (const std::exception& error) {
            game.status = error.what();
        }
    }
    recording_status();
    const auto dialogue = game.dialogue ? game.dialogue->text : std::string();
    if (dialogue != previous_dialogue_) {
        ui.dialogue_scroll = 0;
        previous_dialogue_ = dialogue;
    }
}

void DesktopSession::apply(UiAction action) {
    switch (action.kind) {
    case Action::NewGame:
        game.new_game();
        recorder_.new_game();
        renderer.reset();
        audio.restart(game);
        ui.close_overlays();
        ui.flight = -1;
        ui.ending_wait = false;
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
        game.status = "Saved to slot " + std::to_string(action.value) + ".";
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
            game.status = "Restored slot " + std::to_string(action.value) + ". " + game.status;
        }
        break;
    case Action::Continue:
        game.continue_dialogue();
        break;
    case Action::ContinueEnding:
        ui.ending_wait = false;
        break;
    case Action::Choose:
        play({InputKind::Choose, Direction::Up, Item::HeroOrb, action.value});
        break;
    case Action::UseItem: {
        const auto item = static_cast<Item>(action.value);
        ui.close_overlays();
        if (item == Item::FlightOrb) {
            play({InputKind::OpenFlight});
        } else if (item == Item::HeroOrb && play({InputKind::UseItem, Direction::Up, item})) {
            ui.enemies = true;
            ui.enemy_first_row = 0;
        } else if (item != Item::HeroOrb)
            play({InputKind::UseItem, Direction::Up, item});
        break;
    }
    case Action::FlightUp:
    case Action::FlightDown: {
        play({action.kind == Action::FlightUp ? InputKind::FlightUp : InputKind::FlightDown});
        break;
    }
    case Action::Travel:
        play({InputKind::Travel});
        break;
    case Action::CancelFlight:
        play({InputKind::Cancel});
        break;
    case Action::Mute:
        ui.muted = !ui.muted;
        audio.mute(ui.muted);
        break;
    case Action::Speed:
        ui.speed_index = action.value;
        break;
    case Action::Recording:
        recorder_.enable(!recorder_.enabled());
        game.status = recorder_.enabled() ? "Recording enabled for the next new game or a recorded save."
                                          : "Replay recording disabled.";
        break;
    case Action::None:
        break;
    }
}
} // namespace tsw
