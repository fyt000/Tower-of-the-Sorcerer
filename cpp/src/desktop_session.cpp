#include "desktop_session.hpp"
#include <stdexcept>
#include <utility>

namespace tsw {
DesktopSession::DesktopSession(const Assets& assets, const std::filesystem::path& save_directory,
                               Game initial)
    : game(std::move(initial)), renderer(assets), audio(assets), save_directory_(save_directory) {
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
}

void DesktopSession::move(Direction direction) {
    const auto before = game.hero;
    game.move(direction);
    renderer.moved(before, game.hero);
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
            game.save(save_directory_ / "save0.dat", SaveKind::Checkpoint);
        } catch (const std::exception& error) {
            game.status = error.what();
        }
    }
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
        renderer.reset();
        audio.restart(game);
        ui.close_overlays();
        ui.flight = -1;
        ui.ending_wait = false;
        break;
    case Action::Save:
        game.save(save_directory_ / "quick.save");
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
        game.save(save_slot_path(save_directory_, action.value));
        ui.selected_slot = action.value;
        ui.close_overlays();
        game.status = "Saved to slot " + std::to_string(action.value) + ".";
        break;
    case Action::Load:
    case Action::FairyCheckpoint:
    case Action::LoadSlot:
        game.load(action.kind == Action::LoadSlot
                      ? save_slot_path(save_directory_, action.value)
                      : save_directory_ / (action.kind == Action::Load ? "quick.save" : "save0.dat"),
                  action.kind == Action::FairyCheckpoint ? SaveKind::Checkpoint : SaveKind::Slot);
        renderer.reset();
        ui.close_overlays();
        ui.flight = -1;
        ui.ending_wait = false;
        if (action.kind == Action::LoadSlot) {
            ui.selected_slot = action.value;
            game.status = "Restored slot " + std::to_string(action.value) + ".";
        }
        audio.restart(game);
        break;
    case Action::Continue:
        game.continue_dialogue();
        break;
    case Action::ContinueEnding:
        ui.ending_wait = false;
        break;
    case Action::Choose:
        game.choose(action.value);
        break;
    case Action::UseItem: {
        const auto item = static_cast<Item>(action.value);
        ui.close_overlays();
        if (item == Item::FlightOrb) {
            ui.flight = game.hero.floor;
            game.hero.flight_direction = 0;
        } else if (item == Item::HeroOrb && game.use(item)) {
            ui.enemies = true;
            ui.enemy_first_row = 0;
        } else
            game.use(item);
        break;
    }
    case Action::FlightUp:
    case Action::FlightDown: {
        const bool up = action.kind == Action::FlightUp;
        const int next = up ? (ui.flight == 43 ? 45 : ui.flight + 1) : (ui.flight == 45 ? 43 : ui.flight - 1);
        if (game.flight_preview(next, up ? 1 : 2))
            ui.flight = next;
        break;
    }
    case Action::Travel:
        game.use(Item::FlightOrb, ui.flight);
        ui.flight = -1;
        break;
    case Action::CancelFlight:
        ui.flight = -1;
        break;
    case Action::Mute:
        ui.muted = !ui.muted;
        audio.mute(ui.muted);
        break;
    case Action::Speed:
        ui.speed_index = action.value;
        break;
    case Action::None:
        break;
    }
}
} // namespace tsw
