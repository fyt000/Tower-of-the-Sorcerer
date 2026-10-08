#include "desktop_checks.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace tsw {
namespace {
std::string file_contents(const std::filesystem::path& path) {
    std::ifstream input(path, std::ios::binary);
    if (!input)
        throw std::runtime_error("Cannot read test file: " + path.string());
    return {std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>()};
}

std::uint64_t board_fingerprint(Presentation& renderer) {
    Image image = renderer.capture_canvas();
    Color* pixels = LoadImageColors(image);
    std::uint64_t hash = 14695981039346656037ull;
    for (int y = BoardY; y < BoardY + BoardPixels; ++y)
        for (int x = BoardX; x < BoardX + BoardPixels; ++x) {
            const auto pixel = pixels[y * image.width + x];
            hash = (hash ^ (pixel.r | pixel.g << 8 | pixel.b << 16)) * 1099511628211ull;
        }
    UnloadImageColors(pixels);
    UnloadImage(image);
    return hash;
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
} // namespace

int verify_smoke(DesktopSession& session, const std::string& name, const std::filesystem::path& output) {
    std::filesystem::create_directories(output);
    auto& game = session.game;
    auto& ui = session.ui;
    auto& renderer = session.renderer;
    const auto require = [&](bool condition, const char* description) {
        if (!condition)
            throw std::runtime_error(name + ": " + description);
    };
    if (name == "menus") {
        session.open_home(true);
        game.push(Op::Wait);
        session.advance_commands(1);
        require(ui.home && !ui.game_started && game.commands.size() == 1, "Startup menu must pause gameplay");
        renderer.draw(game, ui, {-1, -1});
        require(renderer.screenshot(output / "home.png"), "Opening artwork and menu must render");
        session.dispatch({Action::OpenSettings});
        require(ui.home && ui.menu == Menu::Options, "Settings must open over the startup menu");
        session.dispatch({Action::Speed, 2});
        session.dispatch({Action::ReplaySpeed, 4});
        if (!ui.recording_enabled)
            session.dispatch({Action::Recording});
        if (!ui.muted)
            session.dispatch({Action::Mute});
        const auto settings = load_settings(output / "saves/settings.json");
        require(settings.game_speed == 2 && settings.replay_speed == 4 && settings.recording &&
                    settings.muted,
                "All menu preferences must be saved");
        renderer.draw(game, ui, {-1, -1});
        require(renderer.screenshot(output / "settings.png"),
                "Settings must render sharp labels and choices");
        ui.close_overlays();
        session.dispatch({Action::NewGame});
        require(!ui.home && ui.game_started && ui.recording_active && !game.busy(),
                "New game must leave the menu and honor recording");
        session.dispatch({Action::SaveSlot, 1});
        game.hero.hp = 1777;
        session.dispatch({Action::MainMenu});
        session.dispatch({Action::OpenLoadSlots});
        require(ui.home && ui.save_picker == SavePicker::Load &&
                    ui.save_slots[0].state == SaveSlotState::Ready,
                "Startup load must show original save slots");
        renderer.draw(game, ui, {-1, -1});
        require(renderer.screenshot(output / "load-menu.png"), "Startup load picker must render");
        session.dispatch({Action::LoadSlot, 1});
        require(!ui.home && game.hero.hp == 1000 && ui.recording_active,
                "Loading must enter the game and resume its recording");
        session.dispatch({Action::MainMenu});
        session.dispatch({Action::OpenReplays});
        require(ui.home && ui.replay_picker && !ui.replay_files.empty(),
                "Replay menu must discover save companions");
        renderer.draw(game, ui, {-1, -1});
        require(renderer.screenshot(output / "replay-menu.png"), "Replay file selection must render");
        save_settings(output / "saves/settings.json", {});
        std::cout << "Desktop menus: startup, settings, load and replay selection passed\n";
        return 0;
    }
    if (name == "replay") {
        const auto source = output / "watched.jsonl";
        constexpr auto trace = R"({"type":"new_game"}
{"type":"move","direction":"up"}
{"type":"move","direction":"up"}
{"type":"move","direction":"left"}
{"type":"move","direction":"right"}
{"type":"move","direction":"up"}
{"type":"move","direction":"up"}
{"type":"use_item","item":"bomb"}
{"type":"save","kind":"checkpoint"}
{"type":"reload","kind":"checkpoint"}
{"type":"save","kind":"slot"}
)";
        {
            std::ofstream recording(source);
            recording << trace;
        }
        const auto quick = output / "saves/quick.save", fairy = output / "saves/save0.dat";
        game.save(quick);
        game.save(fairy, SaveKind::Checkpoint);
        const auto quick_before = file_contents(quick), fairy_before = file_contents(fairy);
        if (!ui.recording_enabled)
            session.dispatch({Action::Recording});
        session.replay(source);
        ui.replay_speed_index = 2;
        require(ui.replay_active && !ui.recording_active, "Watching must keep recording inactive");
        const auto tick = [&] {
            const auto seconds = session.scaled_seconds(.02f);
            renderer.advance(seconds);
            session.advance_commands(seconds);
            renderer.draw(game, ui, {-1, -1});
        };
        session.dispatch({Action::ReplayPause});
        for (int i = 0; i < 10; ++i)
            tick();
        require(ui.replay_step == 0 && game.hero.y == 10, "Pause before playback must execute no inputs");
        session.dispatch({Action::ReplayNext});
        for (int i = 0; i < 100 && !ui.replay_paused; ++i)
            tick();
        require(ui.replay_paused && ui.replay_step == 1, "Next must finish exactly one input and pause");
        session.dispatch({Action::ReplayPause});
        for (int i = 0; i < 500 && !(ui.replay_step == 6 && game.busy()); ++i)
            tick();
        require(ui.replay_step == 6 && game.busy(), "Door animation must remain visible during playback");
        session.dispatch({Action::ReplayPause});
        const auto commands = game.commands;
        tick();
        const auto frozen = board_fingerprint(renderer);
        for (int i = 0; i < 10; ++i)
            tick();
        require(game.commands == commands && frozen == board_fingerprint(renderer),
                "Pause must freeze the command queue and all board animation");
        require(renderer.screenshot(output / "replay-paused-door.png"), "Paused replay controls must render");
        session.dispatch({Action::UseItem, int(Item::Bomb)});
        session.move(Direction::Down);
        require(ui.replay_step == 6 && game.commands == commands,
                "Live input must not alter a watched replay");
        session.dispatch({Action::ReplayPrevious});
        require(ui.replay_paused && ui.replay_step == 5 && game.hero.yellow_keys == 1 &&
                    game.tile(1, 93) == YellowDoor,
                "Previous must restore the boundary before door contact");
        session.dispatch({Action::ReplayNext});
        for (int i = 0; i < 200 && !ui.replay_paused; ++i)
            tick();
        require(ui.replay_step == 6 && !game.busy() && game.tile(1, 93) == Road &&
                    game.visual.door_cell == -1,
                "Single step must finish the door animation before pausing");
        session.dispatch({Action::ReplaySpeed, 6});
        session.dispatch({Action::ReplayPause});
        require(session.scaled_seconds(.1f) == 1.f, "Replay speed must scale the animation clock");
        for (int i = 0; i < 500 && !ui.replay_paused; ++i)
            tick();
        require(ui.replay_paused && ui.replay_step == ui.replay_count && game.hero.y == 8,
                "Completed replay must pause and remain available for takeover");
        Game expected;
        int flight = -1;
        std::istringstream inputs(trace);
        for (const auto& input : read_replay(inputs)) {
            apply_input(expected, flight, input);
            settle_action(expected);
        }
        require(gameplay_json(game, ui.flight) == gameplay_json(expected, flight),
                "Visual and headless playback must reach the same observations");
        require(file_contents(quick) == quick_before && file_contents(fairy) == fairy_before,
                "Playback must never modify quick or Fairy files");
        require(renderer.screenshot(output / "replay-finished.png"),
                "Finished replay must render takeover controls");
        session.dispatch({Action::ReplayTakeOver});
        require(!ui.replay_active && ui.recording_active, "Opted-in takeover must resume the played prefix");
        session.move(Direction::Down);
        for (int i = 0; i < 50 && game.busy(); ++i)
            session.advance_commands(.1f);
        session.dispatch({Action::SaveSlot, 3});
        Game played;
        flight = -1;
        std::ifstream saved(recording_path(output / "saves/save3.dat"));
        for (const auto& input : read_replay(saved)) {
            apply_input(played, flight, input);
            settle_action(played);
        }
        std::ostringstream record(std::ios::binary);
        played.save(record);
        require(record.str() == file_contents(output / "saves/save3.dat"),
                "Taken-over recording must reproduce exact native save bytes");
        saved.close();
        session.replay(source);
        session.dispatch({Action::ReplayPause});
        session.dispatch({Action::Recording});
        session.dispatch({Action::ReplayTakeOver});
        require(!ui.recording_active && !ui.replay_active, "Opted-out takeover must remain unrecorded");
        session.replay(source);
        ui.replay_speed_index = 2;
        for (int i = 0; i < 500 && !(ui.replay_step == 6 && game.busy()); ++i)
            tick();
        require(ui.replay_step == 6 && game.busy(), "Takeover fixture must reach a door animation");
        session.dispatch({Action::ReplayPause});
        session.dispatch({Action::Recording});
        session.dispatch({Action::ReplayTakeOver});
        require(!ui.replay_active && ui.recording_active && game.busy(),
                "Takeover during animation must preserve the current queue and recording prefix");
        for (int i = 0; i < 500 && game.busy(); ++i)
            tick();
        session.dispatch({Action::SaveSlot, 4});
        Game taken_over;
        flight = -1;
        {
            std::ifstream history(recording_path(output / "saves/save4.dat"));
            for (const auto& input : read_replay(history)) {
                apply_input(taken_over, flight, input);
                settle_action(taken_over);
            }
        }
        std::ostringstream takeover_save(std::ios::binary);
        taken_over.save(takeover_save);
        require(takeover_save.str() == file_contents(output / "saves/save4.dat"),
                "Takeover during a door animation must reproduce exact native save bytes");
        session.dispatch({Action::OpenReplays});
        const auto path = source.u8string();
        ui.replay_path = "  \"" + std::string(path.begin(), path.end()) + "\"  ";
        session.dispatch({Action::PlayReplay});
        require(ui.replay_active && !ui.replay_picker && ui.replay_step == 0,
                "A quoted path pasted from Explorer must open its recording");
        Game unchanged = game;
        ui.replay_path = (output / "missing.jsonl").string();
        session.dispatch({Action::PlayReplay});
        unchanged.status = game.status; // The error message changes; gameplay does not.
        require(ui.replay_active && ui.replay_step == 0 &&
                    gameplay_json(game, ui.flight) == gameplay_json(unchanged, ui.flight),
                "A failed file selection must preserve the current replay");

        // Edge states are test fixtures; recordings still contain only real player commands.
        const auto edge = output / "edge.jsonl";
        const auto prepare = [&](const char* commands) {
            {
                std::ofstream recording(edge);
                recording << "{\"type\":\"new_game\"}\n" << commands;
            }
            session.replay(edge);
            ui.replay_speed_index = 2;
            session.dispatch({Action::ReplayPause});
            session.dispatch({Action::ReplayNext});
            for (int i = 0; i < 100 && !ui.replay_paused; ++i)
                tick();
            require(ui.replay_paused && ui.replay_step == 1, "Fixture must start after the new game input");
        };
        constexpr auto up = "{\"type\":\"move\",\"direction\":\"up\"}\n";
        prepare(up);
        game.hero.x = game.hero.y = 5;
        game.hero.hp = 1;
        game.hero.attack = 10;
        game.hero.defense = 0;
        game.tile(1, cell(5, 4)) = GreenSlime;
        session.dispatch({Action::ReplayNext});
        for (int i = 0; i < 500 && game.hero.hp > 0; ++i)
            tick();
        require(game.hero.hp == 0 && !game.visual.dead && ui.replay_in_progress && !ui.replay_paused,
                "Zero HP must not complete playback before the final defeat animation");
        for (int i = 0; i < 500 && !ui.replay_paused; ++i)
            tick();
        require(ui.replay_paused && !ui.replay_in_progress && game.visual.dead && game.commands.empty(),
                "Fatal combat must finish the defeat command before single-step pauses");

        prepare(up);
        game.hero.x = game.hero.y = 5;
        game.hero.attack = game.hero.defense = 10;
        game.tile(1, cell(5, 4)) = GreenSlime;
        session.dispatch({Action::ReplayNext});
        for (int i = 0; i < 500 && !ui.replay_paused; ++i)
            tick();
        require(ui.replay_paused && !game.busy() && !game.visual.battle && game.visual.overlay_cell == -1 &&
                    std::all_of(game.visual.layers.begin(), game.visual.layers.end(),
                                [](const auto& layer) { return layer.underlying < 0; }),
                "Single-step victory must clear strike overlays and leave the hero idle");

        prepare("{\"type\":\"move\",\"direction\":\"up\"}\n"
                "{\"type\":\"choose\",\"choice\":\"attack\"}\n");
        game.hero.x = game.hero.y = 5;
        game.hero.gold = 100;
        game.tile(1, cell(5, 4)) = Altar;
        Game shop_expected = game;
        flight = -1;
        apply_input(shop_expected, flight, {InputKind::Move, Direction::Up});
        settle_action(shop_expected);
        apply_input(shop_expected, flight, {InputKind::Choose, Direction::Up, Item::HeroOrb, 1});
        settle_action(shop_expected);
        session.dispatch({Action::ReplayPause});
        for (int i = 0; i < 30; ++i)
            tick();
        require(ui.replay_step == 2 && game.dialogue && game.dialogue->shop && game.hero.gold == 100,
                "Playback must display a shop before executing its recorded choice");
        session.dispatch({Action::Choose, 0});
        require(game.hero.gold == 100, "Live shop choices must not change a watched recording");
        for (int i = 0; i < 500 && !ui.replay_paused; ++i)
            tick();
        require(ui.replay_step == 3 && gameplay_json(game, ui.flight) == gameplay_json(shop_expected, flight),
                "Recorded shop choices must match headless gameplay");

        prepare("{\"type\":\"use_item\",\"item\":\"wisdom_orb\"}\n");
        game.inventory(Item::WisdomOrb) = 1;
        session.dispatch({Action::ReplayNext});
        tick();
        require(game.dialogue && !game.dialogue->shop && ui.replay_in_progress,
                "Non-choice speech must remain visible during visual playback");
        for (int i = 0; i < 500 && !ui.replay_paused; ++i)
            tick();
        require(ui.replay_paused && !game.dialogue && !game.busy(),
                "Playback must automatically continue non-choice speech");

        prepare(up);
        game.hero.floor = 50;
        game.hero.x = game.hero.y = 5;
        game.tile(50, cell(5, 4)) = Zeno;
        Game ending_expected = game;
        flight = -1;
        apply_input(ending_expected, flight, {InputKind::Move, Direction::Up});
        settle_action(ending_expected);
        session.dispatch({Action::ReplayNext});
        for (int i = 0; i < 4000 && !ui.ending_wait; ++i)
            tick();
        require(ui.ending_wait && ui.replay_in_progress && !ui.replay_paused,
                "Visual playback must display the original ending card");
        session.dispatch({Action::ReplayPause});
        for (int i = 0; i < 100; ++i)
            tick();
        require(ui.ending_wait && game.hero.cycle_factor_minus_one == 0,
                "Pause must retain the ending card and delay the backside transition");
        session.dispatch({Action::ReplayNext});
        for (int i = 0; i < 4000 && !ui.replay_paused; ++i)
            tick();
        require(ui.replay_paused && !ui.ending_wait &&
                    game.hero.cycle_factor_minus_one == BacksideFactor - 1 &&
                    gameplay_json(game, ui.flight) == gameplay_json(ending_expected, flight),
                "The ending must continue to the same backside state as headless playback");
        const auto invalid = output / "invalid.jsonl";
        {
            std::ofstream recording(invalid);
            recording << "{\"type\":\"new_game\"}\n{\"type\":\"flight_up\"}\n";
        }
        session.replay(invalid);
        for (int i = 0; i < 50 && ui.replay_error.empty(); ++i)
            tick();
        require(ui.replay_paused && ui.replay_error.starts_with("Step 2:"),
                "Illegal replay sequencing must pause with the failed step");
        session.dispatch({Action::ReplayRestart});
        require(ui.replay_step == 0 && ui.replay_error.empty() && ui.replay_paused,
                "Restart must reconstruct the fresh boundary and clear errors");
        save_settings(output / "saves/settings.json", {});
        std::cout << "Desktop replay: stepping, rewind, takeover, death, shops, speech, ending and read-only "
                     "saves passed\n";
        return 0;
    }
    if (name == "recording") {
        const auto saves = output / "saves";
        session.dispatch({Action::Recording});
        require(ui.recording_enabled && !ui.recording_active, "Opt in must wait for a fresh game");
        session.dispatch({Action::NewGame});
        require(ui.recording_active, "New game must start recording after opting in");
        const auto walk = [&](Direction direction) {
            session.move(direction);
            for (int i = 0; i < 200 && game.busy(); ++i) {
                if (game.dialogue && !game.dialogue->shop)
                    session.dispatch({Action::Continue});
                session.advance_commands(1.f);
            }
            require(!game.busy(), "Recorded walk must finish through desktop scheduling");
        };
        walk(Direction::Up);
        walk(Direction::Left);
        session.dispatch({Action::SaveSlot, 1});
        require(std::filesystem::exists(recording_path(saves / "save1.dat")),
                "Manual save needs its companion");
        walk(Direction::Right);
        session.dispatch({Action::LoadSlot, 1});
        require(ui.recording_active && game.hero.yellow_keys == 1 && game.hero.x == 4,
                "Recorded load must restore and resume the saved branch");
        // Exercise the application's automatic raw-checkpoint writer with a real reached state.
        game.checkpoint_requested = true;
        session.advance_commands(1.f);
        require(std::filesystem::exists(recording_path(saves / "save0.dat")),
                "Fairy save needs its companion");
        session.dispatch({Action::FairyCheckpoint});
        require(ui.recording_active, "Raw Fairy restore must resume recording");
        walk(Direction::Down);
        session.dispatch({Action::Save});
        std::ifstream recording(recording_path(saves / "quick.save"));
        Game replayed;
        int flight = -1;
        for (const auto& input : read_replay(recording)) {
            apply_input(replayed, flight, input);
            settle_action(replayed);
        }
        recording.close();
        std::ostringstream expected(std::ios::out | std::ios::binary),
            actual(std::ios::out | std::ios::binary);
        game.save(expected);
        replayed.save(actual);
        require(expected.str() == actual.str(),
                "Desktop recording must reproduce native save bytes headlessly");
        std::filesystem::remove(recording_path(saves / "save1.dat"));
        session.dispatch({Action::LoadSlot, 1});
        require(!ui.recording_active, "A save without a companion must load without recording");
        session.dispatch({Action::Save});
        require(!std::filesystem::exists(recording_path(saves / "quick.save")),
                "Unrecorded replacement must remove a stale companion");
        session.dispatch({Action::NewGame});
        require(ui.recording_active, "Recording preference must survive an unrecorded load");
        session.dispatch({Action::Recording});
        require(!ui.recording_enabled && !ui.recording_active, "Opt out must stop recording immediately");
        ui.menu = Menu::Options;
    }
    fixture(game, ui, name);
    session.audio.restart(game);
    bool ending_pause = false, slot_pause = false, slot_restore = false;
    if (name == "slots") {
        for (int number = 1; number <= ManualSaveSlotCount; ++number) {
            game.new_game();
            game.hero.floor = number;
            game.hero.hp = 1000 + number * 100;
            game.hero.cycle_factor_minus_one = number >= 5 ? 43 : 0;
            game.hero.later_cycle = number >= 7;
            session.dispatch({Action::SaveSlot, number});
        }
        game.new_game();
        game.push(Op::Wait);
        session.dispatch({Action::OpenLoadSlots});
        require(std::all_of(ui.save_slots.begin(), ui.save_slots.end(),
                            [](const auto& slot) { return slot.state == SaveSlotState::Ready; }),
                "All eight slots must be readable");
    }
    for (int frame = 0; frame < 400; ++frame) {
        renderer.advance(1.f);
        if (name == "slots" && frame == 90) {
            slot_pause = game.commands.size() == 1 && ui.save_picker == SavePicker::Load;
            session.dispatch({Action::LoadSlot, 8});
            slot_restore = !game.busy() && game.hero.floor == 8 && game.hero.hp == 1800 &&
                           game.hero.cycle_factor_minus_one == 43 && game.hero.later_cycle;
            session.dispatch({Action::OpenSaveSlots});
        }
        if (ui.ending_wait) {
            const auto commands = game.commands;
            session.advance_commands(1.f);
            ending_pause = game.busy() && game.visual.raster_mode == 8 &&
                           game.hero.cycle_factor_minus_one == 0 && game.commands == commands;
            session.dispatch({Action::ContinueEnding});
        }
        if (game.dialogue && !game.dialogue->shop)
            session.dispatch({Action::Continue});
        session.advance_commands(1.f);
        renderer.draw(game, ui, {-1, -1});
        renderer.present();
    }
    const auto& hero = game.hero;
    if (name == "capture")
        require(hero.floor == 2 && hero.hp == 400, "Capture must finish at the prison");
    if (name == "stairs")
        require(hero.floor == 2, "Stairs must arrive on the next floor");
    if (name == "fight")
        require(hero.gold > 0, "Completed combat must give its reward");
    if (name == "ending")
        require(ending_pause && hero.cycle_factor_minus_one == BacksideFactor - 1,
                "Ending must pause at the card, then enter the backside");
    if (name == "slots")
        require(slot_pause && slot_restore, "Slot picker must pause commands and restore slot eight");
    if (name == "fairy") {
        Game checkpoint;
        checkpoint.load(output / "saves/save0.dat", SaveKind::Checkpoint);
        require(checkpoint.hero.fairy_visits == 1 && checkpoint.hero.fairy_score == 415 &&
                    checkpoint.tile(10, 27) == Road,
                "Completed Fairy scene must write the raw checkpoint");
    }
    require(renderer.screenshot(output / (name + ".png")), "Screenshot must be written");
    std::cout << "Desktop " << name << ": floor=" << hero.floor << " hp=" << hero.hp << " gold=" << hero.gold
              << '\n';
    return 0;
}
} // namespace tsw
