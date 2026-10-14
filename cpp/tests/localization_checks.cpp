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
        ui.home = false;
        ui.menu = Menu::None;
        game.dialogue = Dialogue{std::string(Game::original_dialogue(52)), 0, false, {}};
        capture("dialogue");
        game.dialogue.reset();
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
        game.visual.raster_mode = 1;
        game.visual.raster_frame = ContentHeight;
        capture("opening");
        game.visual.raster_mode = 5;
        game.visual.raster_frame = 400;
        capture("ending");
    }
    std::ofstream report(output / "localization-report.json");
    report << "{\"languages\":5,\"rendered_scenes\":" << checks << ",\"audio_opened\":false}\n";
    std::cout << "Rendered " << checks << " localized scenes without opening audio\n";
    return 0;
}
} // namespace tsw
