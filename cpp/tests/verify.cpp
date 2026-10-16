#include "desktop_checks.hpp"
#include <algorithm>
#include <iostream>
#include <stdexcept>

using namespace tsw;

namespace tsw {
int verify_localization(Presentation&, const std::filesystem::path&);
}

namespace {
struct Window {
    explicit Window(bool visible) {
        SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI | FLAG_VSYNC_HINT |
                       (visible ? 0 : FLAG_WINDOW_HIDDEN));
        SetTraceLogLevel(LOG_WARNING);
        InitWindow(CanvasWidth, CanvasHeight, "Tower of the Sorcerer verification");
        SetWindowMinSize(640, 447);
        SetExitKey(KEY_NULL);
        SetTargetFPS(0);
    }

    ~Window() { CloseWindow(); }
};
} // namespace

int main(int argc, char** argv) try {
    std::filesystem::path requested_assets, presentation, window, asset_check, output = TSW_CHECK_OUTPUT;
    std::filesystem::path compare_assets = TSW_ASSETS;
    std::filesystem::path localization;
    std::string smoke;
    bool visible = false;
    for (int i = 1; i < argc; ++i) {
        const std::string arg = argv[i];
        if (arg == "--assets" && i + 1 < argc)
            requested_assets = argv[++i];
        else if (arg == "--compare-assets" && i + 1 < argc)
            compare_assets = argv[++i];
        else if (arg == "--presentation" && i + 1 < argc)
            presentation = argv[++i];
        else if (arg == "--window" && i + 1 < argc)
            window = argv[++i];
        else if (arg == "--localization" && i + 1 < argc)
            localization = argv[++i];
        else if (arg == "--asset-check" && i + 1 < argc)
            asset_check = argv[++i];
        else if (arg == "--smoke" && i + 1 < argc)
            smoke = argv[++i];
        else if (arg == "--output" && i + 1 < argc)
            output = argv[++i];
        else if (arg == "--visible")
            visible = true;
        else if (arg == "--help") {
            std::cout << "Desktop verification, built only with BUILD_TESTING=ON.\n"
                         "--assets DIR: original or extracted assets.\n"
                         "Choose one: --presentation DIR, --window DIR, --asset-check DIR, --smoke NAME.\n"
                         "--localization DIR: render five languages without opening audio.\n"
                         "Asset checks: --compare-assets EXTRACTED_DIR.\n"
                         "Smoke: all, initial, capture, stairs, fight, floor10, fairy, ending, slots,\n"
                         "       items, inventory, item, shop, flight, help, backside, enemies, recording, "
                         "menus, replay.\n"
                         "--output DIR: smoke images and saves. --visible: show the test window.\n";
            return 0;
        } else
            throw std::runtime_error("Unknown argument: " + arg);
    }
    if (int(!presentation.empty()) + int(!window.empty()) + int(!asset_check.empty()) + int(!smoke.empty()) +
            int(!localization.empty()) !=
        1)
        throw std::runtime_error("Choose one verification suite; use --help for options");
    constexpr std::array<std::string_view, 20> SmokeNames{
        "all",    "initial",  "capture", "stairs",    "fight", "floor10", "fairy",
        "ending", "slots",    "items",   "inventory", "item",  "shop",    "flight",
        "help",   "backside", "enemies", "recording", "menus", "replay"};
    if (!smoke.empty() && std::find(SmokeNames.begin(), SmokeNames.end(), smoke) == SmokeNames.end())
        throw std::runtime_error("Unknown smoke scenario: " + smoke);
    const std::filesystem::path directory = GetApplicationDirectory();
    auto executable = directory / std::filesystem::path(argv[0]).filename();
#ifdef _WIN32
    if (!std::filesystem::exists(executable))
        executable += ".exe";
#endif
    Assets assets(Assets::select(directory, requested_assets, TSW_ORIGINAL_ASSETS, TSW_ASSETS), executable);
    if (!asset_check.empty())
        return verify_assets(assets, Assets(compare_assets, executable), executable, asset_check);
    Window native_window(visible);
    if (!localization.empty()) {
        Presentation renderer(assets);
        return verify_localization(renderer, localization);
    }
    if (!presentation.empty()) {
        Presentation renderer(assets);
        return verify_presentation(renderer, presentation, assets);
    }
    if (!window.empty()) {
        Presentation renderer(assets);
        return verify_window(renderer, window);
    }
    const auto run = [&](const std::string& name) {
        const auto scenario_output = output / name;
        DesktopSession session(assets, scenario_output / "saves");
        return verify_smoke(session, name, scenario_output);
    };
    if (smoke != "all")
        return run(smoke);
    for (const auto* name : {"initial", "capture", "stairs", "fight", "floor10", "fairy", "ending", "slots",
                             "recording", "menus", "replay"})
        if (run(name))
            return 1;
    return 0;
} catch (const std::exception& error) {

    std::cerr << error.what() << '\n';
    return 1;
}
