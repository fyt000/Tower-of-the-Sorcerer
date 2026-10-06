#include "audio.hpp"
#include "presentation.hpp"
#include <algorithm>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>
#include <tuple>

using namespace baseline;
namespace baseline {
int verify_presentation(Presentation&, const std::filesystem::path&, const std::filesystem::path&);
}
namespace {
std::filesystem::path saves() {
    if (const char* appdata = std::getenv("APPDATA"))
        return std::filesystem::path(appdata) / "TosOriginalBaseline";
    if (const char* data = std::getenv("XDG_DATA_HOME"))
        return std::filesystem::path(data) / "tos-original-baseline";
    if (const char* home = std::getenv("HOME"))
        return std::filesystem::path(home) / ".local/share/tos-original-baseline";
    return std::filesystem::current_path() / "baseline-saves";
}
void fixture(Game& game, DesktopUi& ui, const std::string& smoke) {
    if (smoke == "capture") {
        game.hero.floor = 3;
        game.hero.x = 4;
        game.hero.y = 9;
        game.move(Direction::Up);
    } else if (smoke == "stairs") {
        game.hero.x = 0;
        game.hero.y = 1;
        game.move(Direction::Up);
    } else if (smoke == "fight") {
        game.hero.x = game.hero.y = 5;
        game.hero.attack = game.hero.defense = 10;
        game.hero.hp = 1000;
        game.tile(1, cell(5, 4)) = GreenSlime;
        game.move(Direction::Up);
    } else if (smoke == "floor10" || smoke == "fairy") {
        game.hero.floor = 10;
        game.hero.x = 5;
        game.hero.y = smoke == "floor10" ? 4 : 5;
        if (smoke == "fairy") {
            game.tile(10, cell(5, 4)) = Fairy;
            game.move(Direction::Up);
        } else
            game.check_floor();
    } else if (smoke == "inventory" || smoke == "items" || smoke == "item" || smoke == "flight" ||
               smoke == "enemies") {
        game.hero.items.fill(1);
        game.inventory(Item::WarpStaff) = 5;
        game.hero.yellow_keys = 4;
        game.hero.blue_keys = 2;
        game.hero.red_keys = 1;
        game.hero.highest_floor = 7;
        ui.inventory = smoke == "inventory";
        ui.enemies = smoke == "enemies";
        ui.selected_item = smoke == "item" ? int(Item::Bomb) : -1;
        ui.flight = smoke == "flight" ? 5 : -1;
        game.status = "Click an item to inspect or use it. [I] opens the inventory.";
    } else if (smoke == "shop") {
        game.hero.x = game.hero.y = 5;
        game.hero.gold = 100;
        game.tile(1, cell(5, 4)) = Altar;
        game.move(Direction::Up);
    } else if (smoke == "ending") {
        game.hero.floor = 50;
        game.hero.x = game.hero.y = 5;
        game.tile(50, cell(5, 4)) = Zeno;
        game.move(Direction::Up);
    } else if (smoke == "help")
        ui.help = true;
    else if (smoke == "backside")
        game.hero.cycle_factor_minus_one = BacksideFactor - 1;
}
UiAction keyboard(const Game& game, DesktopUi& ui) {
    if (IsKeyPressed(KEY_F2))
        return {Action::NewGame};
    if (IsKeyPressed(KEY_F5))
        return {Action::Save};
    if (IsKeyPressed(KEY_F6))
        return {Action::OpenSaveSlots};
    if (IsKeyPressed(KEY_F7))
        return {Action::OpenLoadSlots};
    if (IsKeyPressed(KEY_F9))
        return {Action::Load};
    if (IsKeyPressed(KEY_F8))
        return {Action::FairyCheckpoint};
    if (IsKeyPressed(KEY_M))
        return {Action::Mute};
    if (ui.save_picker != SavePicker::None) {
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
    if (ui.menu != Menu::None || ui.help) {
        if (IsKeyPressed(KEY_ESCAPE))
            ui.close_overlays();
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
    if (ui.ending_wait)
        return IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE) ? UiAction{Action::ContinueEnding}
                                                                  : UiAction{};
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
void apply(UiAction action, Game& game, DesktopUi& ui, Presentation& renderer, Audio& audio,
           const std::filesystem::path& save_directory) {
    switch (action.kind) {
    case Action::NewGame:
        game.new_game();
        renderer.reset();
        ui.close_overlays();
        ui.flight = -1;
        ui.ending_wait = false;
        break;
    case Action::Save:
        game.save(save_directory / "quick.save");
        game.status = "Quick save written.";
        break;
    case Action::OpenSaveSlots:
    case Action::OpenLoadSlots:
        if (action.kind == Action::OpenSaveSlots && game.busy())
            throw std::runtime_error("Finish the current action before saving");
        ui.save_slots = inspect_save_slots(save_directory);
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
        game.save(save_slot_path(save_directory, action.value));
        ui.selected_slot = action.value;
        ui.close_overlays();
        game.status = "Saved to slot " + std::to_string(action.value) + ".";
        break;
    case Action::Load:
    case Action::FairyCheckpoint:
    case Action::LoadSlot:
        game.load(action.kind == Action::LoadSlot
                      ? save_slot_path(save_directory, action.value)
                      : save_directory / (action.kind == Action::Load ? "quick.save" : "fairy.save"));
        renderer.reset();
        ui.close_overlays();
        ui.flight = -1;
        ui.ending_wait = false;
        if (action.kind == Action::LoadSlot) {
            ui.selected_slot = action.value;
            game.status = "Restored slot " + std::to_string(action.value) + ".";
        }
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
} // namespace

int main(int argc, char** argv) try {
    const std::filesystem::path executable = std::filesystem::absolute(argv[0]).parent_path();
    auto assets = std::filesystem::exists(executable / "assets/original-atlas.png")
                      ? executable / "assets"
                      : std::filesystem::path(BASELINE_ASSETS);
    auto save_directory = saves();
    std::filesystem::path screenshot, presentation_test;
    std::string smoke;
    bool audio_test = false, visible_smoke = false;
    for (int i = 1; i < argc; ++i) {
        const std::string arg = argv[i];
        if (arg == "--assets" && i + 1 < argc)
            assets = argv[++i];
        else if (arg == "--save-dir" && i + 1 < argc)
            save_directory = argv[++i];
        else if (arg == "--screenshot" && i + 1 < argc)
            screenshot = argv[++i];
        else if (arg == "--presentation-test" && i + 1 < argc)
            presentation_test = argv[++i];
        else if (arg == "--smoke" && i + 1 < argc)
            smoke = argv[++i];
        else if (arg == "--audio-test")
            audio_test = true;
        else if (arg == "--visible-smoke")
            visible_smoke = true;
        else if (arg == "--help") {
            std::cout << "Tower of the Sorcerer original baseline\n"
                         "Arrows / WASD: move. Enter: continue. I: inventory.\n"
                         "F6 / F7: eight save / load slots. F5 / F9: quick save / restore.\n"
                         "F8: Fairy checkpoint. F2: new game. M: mute.\n"
                         "--assets DIR --save-dir DIR --screenshot FILE --audio-test\n"
                         "--smoke "
                         "initial|capture|stairs|fight|floor10|fairy|items|inventory|item|shop|flight|help|"
                         "backside|ending|enemies|slots\n"
                         "--visible-smoke --presentation-test DIR\n";
            return 0;
        } else
            throw std::runtime_error("Unknown argument: " + arg);
    }
    if (!std::filesystem::exists(assets / "original-atlas.png"))
        throw std::runtime_error("Original assets missing. Run tools/extract_original.py or pass --assets.");
    if (audio_test) {
        const auto output = screenshot.empty() ? executable / "midi-test.wav" : screenshot;
        const bool passed =
            Audio::verify_tracks(assets, executable / "music.sf2") &&
            Audio::render_test(assets / "midi/b_067xgw.mid", executable / "music.sf2", output);
        std::cout << (passed ? "MIDI synthesis passed: " : "MIDI synthesis failed: ") << output << '\n';
        return passed ? 0 : 1;
    }
    const bool hidden = !presentation_test.empty() || (!smoke.empty() && !visible_smoke);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI | FLAG_VSYNC_HINT |
                   (hidden ? FLAG_WINDOW_HIDDEN : 0));
    SetTraceLogLevel(LOG_WARNING);
    InitWindow(CanvasWidth, CanvasHeight, "Tower of the Sorcerer - Original Baseline");
    SetWindowMinSize(640, 447);
    SetExitKey(KEY_NULL);
    SetTargetFPS(hidden ? 0 : 60);
    int result = 0;
    {
        Presentation renderer(assets);
        if (!presentation_test.empty())
            result = verify_presentation(renderer, presentation_test, assets);
        else {
            Audio audio(assets, executable / "music.sf2");
            Game game;
            DesktopUi ui;
            fixture(game, ui, smoke);
            float accumulator = 0;
            WalkRepeat walking;
            int frame_count = 0;
            bool ending_seen = false, ending_pause_checked = false;
            bool slots_checked = false, slot_pause_checked = false, slot_restore_checked = false;
            std::string previous_dialogue;
            const auto dispatch = [&](UiAction action) {
                const auto before = game.hero;
                try {
                    apply(action, game, ui, renderer, audio, save_directory);
                } catch (const std::exception& error) {
                    game.status = error.what();
                }
                renderer.moved(before, game.hero);
            };
            if (smoke == "slots") {
                for (int number = 1; number <= ManualSaveSlotCount; ++number) {
                    game.new_game();
                    game.hero.floor = number;
                    game.hero.hp = 1000 + number * 100;
                    game.hero.cycle_factor_minus_one = number >= 5 ? 43 : 0;
                    game.hero.later_cycle = number >= 7;
                    dispatch({Action::SaveSlot, number});
                }
                game.new_game();
                game.push(Op::Wait);
                dispatch({Action::OpenLoadSlots});
                slots_checked = std::all_of(ui.save_slots.begin(), ui.save_slots.end(), [](const auto& slot) {
                    return slot.state == SaveSlotState::Ready;
                });
            }
            while (!WindowShouldClose()) {
                const float elapsed = GetFrameTime();
                const float game_elapsed = std::min(elapsed, .1f) * GameSpeeds[ui.speed_index];
                renderer.advance(game_elapsed);
                dispatch(keyboard(game, ui));
                if (smoke == "slots" && frame_count == 90) {
                    slot_pause_checked = game.commands.size() == 1 && ui.save_picker == SavePicker::Load;
                    dispatch({Action::LoadSlot, 8});
                    slot_restore_checked = !game.busy() && game.hero.floor == 8 && game.hero.hp == 1800 &&
                                           game.hero.cycle_factor_minus_one == 43 && game.hero.later_cycle;
                    dispatch({Action::OpenSaveSlots});
                }
                if (!smoke.empty() && ui.ending_wait) {
                    ending_pause_checked =
                        game.busy() && game.visual.raster_mode == 8 && game.hero.cycle_factor_minus_one == 0;
                    dispatch({Action::ContinueEnding});
                }
                if (!smoke.empty() && game.dialogue && !game.dialogue->shop)
                    game.continue_dialogue();
                if (!game.dialogue && ui.flight < 0 && !ui.modal() && !game.busy()) {
                    walking.advance(game_elapsed);
                    for (const auto [key, alternative, direction] :
                         std::array<std::tuple<int, int, Direction>, 4>{
                             {{KEY_UP, KEY_W, Direction::Up},
                              {KEY_DOWN, KEY_S, Direction::Down},
                              {KEY_LEFT, KEY_A, Direction::Left},
                              {KEY_RIGHT, KEY_D, Direction::Right}}})
                        if (walking.ready(IsKeyPressed(key) || IsKeyPressed(alternative),
                                          IsKeyDown(key) || IsKeyDown(alternative))) {
                            const auto before = game.hero;
                            game.move(direction);
                            renderer.moved(before, game.hero);
                            walking.stepped();
                            break;
                        }
                }
                accumulator += smoke.empty() ? game_elapsed : 1.f;
                for (int commands = 0; commands < (smoke.empty() ? 64 : 512); ++commands) {
                    if (ui.ending_wait || ui.save_picker != SavePicker::None) {
                        accumulator = 0;
                        break;
                    }
                    const float beat = command_interval(game);
                    if (accumulator < beat)
                        break;
                    Command command;
                    if (!game.run_one(&command)) {
                        accumulator = 0;
                        break;
                    }
                    renderer.command(command);
                    // 0x482E60 mode 8 stops the original timer until the player continues.
                    if (command.op == Op::Callback && command.a == int(Callback::RasterScene) &&
                        game.visual.raster_mode == 8) {
                        ui.ending_wait = true;
                        ending_seen = true;
                    }
                    accumulator -= beat;
                }
                audio.update(game);
                if (game.checkpoint_requested && !game.busy()) {
                    game.checkpoint_requested = false;
                    try {
                        game.save(save_directory / "fairy.save");
                    } catch (const std::exception& error) {
                        game.status = error.what();
                    }
                }
                const auto dialogue = game.dialogue ? game.dialogue->text : std::string();
                if (dialogue != previous_dialogue) {
                    ui.dialogue_scroll = 0;
                    previous_dialogue = dialogue;
                }
                dispatch(renderer.draw(game, ui, renderer.mouse_position()));
                renderer.present();
                if (!smoke.empty() && ++frame_count >= 180) {
                    if (!screenshot.empty() && !renderer.screenshot(screenshot))
                        result = 1;
                    const auto& h = game.hero;
                    if ((smoke == "capture" && (h.floor != 2 || h.hp != 400)) ||
                        (smoke == "stairs" && h.floor != 2) || (smoke == "fight" && h.gold == 0))
                        result = 1;
                    if (smoke == "ending" && (!ending_seen || !ending_pause_checked ||
                                              h.cycle_factor_minus_one != BacksideFactor - 1))
                        result = 1;
                    if (smoke == "slots" && (!slots_checked || !slot_pause_checked || !slot_restore_checked))
                        result = 1;
                    if (smoke == "fairy") {
                        try {
                            Game checkpoint;
                            checkpoint.load(save_directory / "fairy.save");
                            if (checkpoint.hero.fairy_visits != 1 || checkpoint.hero.fairy_score != 415 ||
                                checkpoint.tile(10, 27) != Road)
                                result = 1;
                        } catch (const std::exception& error) {
                            std::cerr << error.what() << '\n';
                            result = 1;
                        }
                    }
                    if (!audio.available())
                        result = 1;
                    std::cout << "Smoke " << smoke << ": floor=" << h.floor << " hp=" << h.hp
                              << " gold=" << h.gold << " audio=" << audio.available()
                              << " window=" << GetScreenWidth() << 'x' << GetScreenHeight()
                              << " framebuffer=" << GetRenderWidth() << 'x' << GetRenderHeight();
                    if (smoke == "ending")
                        std::cout << " ending-pause=" << ending_pause_checked;
                    if (smoke == "slots")
                        std::cout << " slots=" << slots_checked << " slot-pause=" << slot_pause_checked
                                  << " slot-restore=" << slot_restore_checked;
                    std::cout << '\n';
                    break;
                }
            }
        }
    }
    CloseWindow();
    return result;
} catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
    return 1;
}
