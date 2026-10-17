#include "desktop_checks.hpp"
#include "tsw/localization.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>

namespace tsw {
// No DesktopSession or Audio instance: this suite is safe under ctest -LE audio.
int verify_localization(Presentation& renderer, const std::filesystem::path& output) {
    std::filesystem::create_directories(output);
    int checks = 0;
    for (const auto language : Languages) {
        Game game;
        DesktopUi ui;
        ui.language = language;
        const auto capture = [&](const char* name) {
            const auto path = output / (std::string(language_id(language)) + "-" + name + ".png");
            renderer.draw(game, ui, {-1, -1});
            renderer.present();
            Image image = renderer.capture_canvas();
            if (!image.data || image.width != CanvasWidth || image.height != CanvasHeight)
                throw std::runtime_error("Localized canvas has invalid dimensions");
            const bool saved = ExportImage(image, path.string().c_str());
            UnloadImage(image);
            if (!saved)
                throw std::runtime_error("Cannot export localization screenshot");
            ++checks;
        };
        ui.home = true;
        capture("home");
        ui.menu = Menu::Options;
        capture("settings");
        ui.item_collection = true;
        capture("settings-collection");
        ui.item_collection = false;
        ui.settings_tab = SettingsTab::Controls;
        capture("settings-controls");
        ui.settings_tab = SettingsTab::Replay;
        capture("settings-replay");
        ui.settings_tab = SettingsTab::Language;
        capture("settings-language");
        ui.menu = Menu::About;
        capture("about");
        ui.home = false;
        ui.menu = Menu::None;
        ui.help = true;
        capture("help");
        ui.help = false;
        game.dialogue = Dialogue{std::string(Game::original_dialogue(static_cast<DialogueId>(52))),
                                 ContinuationStage::None,
                                 false,
                                 {}};
        capture("dialogue");
        game.dialogue.reset();
        game.hero.floor = 10;
        game.hero.x = game.hero.y = 5;
        game.hero.music_track = MusicTrack::Disabled;
        game.floors[10].tiles.fill(Road);
        game.tile_at(10, 5, 4) = Fairy;
        game.move(Direction::Up);
        game.finish_commands();
        if (!game.dialogue || game.dialogue->text.empty())
            throw std::runtime_error("Fairy evaluation dialogue is missing");
        capture("fairy");
        // Long ranked speeches scroll; retain the title/closing in visual checks.
        ui.dialogue_scroll = 10000.f;
        capture("fairy-title");
        ui.dialogue_scroll = 0;
        game.new_game();
        game.hero.x = game.hero.y = 5;
        game.floors[1].tiles.fill(Road);
        game.tile_at(1, 5, 4) = RedPotion;
        game.move(Direction::Up);
        game.finish_commands();
        capture("pickup-status");
        ui.replay_active = ui.replay_paused = true;
        ui.replay_name = "status-fixture";
        capture("replay-status");
        ui.replay_active = ui.replay_paused = false;
        game.inventory(Item::Bomb) = 1;
        game.tile_at(1, 5, 3) = GreenSlime;
        game.use(Item::Bomb);
        game.finish_commands();
        capture("consumable-status");
        game.tile_at(1, 4, 5) = StairsUp;
        game.move(Direction::Down);
        capture("nearby-status");
        ui.item_collection = true;
        capture("collection-controls");
        ui.item_collection = false;
        game.new_game();
        for (int i = 0; i < 15; ++i)
            game.hero.items[i] = 1;
        ui.inventory = true;
        capture("inventory");
        ui.inventory = false;
        ui.enemies = true;
        capture("enemies");
        ui.enemies = false;
        ui.selected_item = int(Item::WarpStaff);
        capture("item");
        ui.selected_item = -1;
        ui.realtime_hero_orb = true;
        capture("realtime-orb");
        ui.realtime_hero_orb = false;
        game.visual.raster_mode = RasterMode::OpeningStory;
        game.visual.raster_frame = ContentHeight;
        capture("opening");
        game.visual.raster_mode = RasterMode::EndingStory;
        game.visual.raster_frame = 400;
        capture("ending");
        game.hero.zeno_sealed = true;
        game.hero.altar_purchases = 21;
        game.hero.red_keys = 5;
        game.hero.sword = EquipmentTier::Knight;
        game.hero.shield = EquipmentTier::Holy;
        game.inventory(Item::DragonSlayer) = 0;
        game.run_history.dragon_defeated = true;
        game.ending_summary = EndingSummary{game.hero, game.run_history};
        ui.ending_wait = true;
        capture("ending-summary-all");
        game.run_history.complete = false;
        game.ending_summary = EndingSummary{game.hero, game.run_history};
        capture("ending-summary-partial");
        game.hero.zeno_sealed = false;
        game.hero.altar_purchases = 20;
        game.hero.red_keys = 4;
        game.ending_summary = EndingSummary{game.hero, game.run_history};
        capture("ending-summary-empty");
    }
    std::ofstream report(output / "localization-report.json");
    report << "{\"languages\":5,\"rendered_scenes\":" << checks << ",\"audio_opened\":false}\n";
    std::cout << "Rendered " << checks << " localized scenes without opening audio\n";
    return 0;
}
} // namespace tsw
