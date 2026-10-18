#include "desktop_session.hpp"
#include <algorithm>
#include <filesystem>
#include <iostream>
#include <string>
#include <tuple>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#ifdef __ANDROID__
#include <android_native_app_glue.h>
extern "C" android_app* GetAndroidApp();
#endif

using namespace tsw;

namespace {
struct GameLoop {
    std::unique_ptr<Assets> assets;
    std::unique_ptr<DesktopSession> session;
    std::array<WalkRepeat, 4> walking;

    void frame() {
#ifdef __EMSCRIPTEN__
        // Raylib's web backend does not enable GLFW HiDPI. Keep its window in
        // physical pixels; the shell owns the CSS size and input is mapped by GLFW.
        const int width = EM_ASM_INT({
            return Math.round(Module['canvas'].getBoundingClientRect().width *
                              (window.devicePixelRatio || 1));
        });
        const int height = EM_ASM_INT({
            return Math.round(Module['canvas'].getBoundingClientRect().height *
                              (window.devicePixelRatio || 1));
        });
        if (width > 0 && height > 0 && (width != GetScreenWidth() || height != GetScreenHeight()))
            SetWindowSize(width, height);
#endif
        auto& game = session->game;
        auto& ui = session->ui;
        auto& renderer = session->renderer;
        if (IsFileDropped()) {
            const auto files = LoadDroppedFiles();
            if (files.count) {
                ui.replay_path = files.paths[0];
                session->dispatch({Action::PlayReplay});
            }
            UnloadDroppedFiles(files);
        }
        const auto walking_enabled = [&] {
            return IsWindowFocused() && game_shortcut_modifiers() && !ui.replay_active && !game.dialogue &&
                   ui.flight < 0 && !ui.modal() && !ui.ending_wait;
        };
        const bool was_walking = walking_enabled();
        session->dispatch(keyboard_input(game, ui));
        const float real_elapsed = std::min(GetFrameTime(), .1f);
        const float game_elapsed = session->scaled_seconds(real_elapsed);
        renderer.advance(game_elapsed, ui.modal() ? 0.f : real_elapsed);
        constexpr std::array<std::tuple<int, int, Direction>, 4> directions{
            {{KEY_UP, KEY_W, Direction::Up},
             {KEY_DOWN, KEY_S, Direction::Down},
             {KEY_LEFT, KEY_A, Direction::Left},
             {KEY_RIGHT, KEY_D, Direction::Right}}};
        std::optional<Direction> step;
        bool fresh_step = false;
        for (std::size_t i = 0; i < directions.size(); ++i) {
            const auto [key, alternative, direction] = directions[i];
            const bool pressed = IsKeyPressed(key) || IsKeyPressed(alternative);
            if (walking[i].update(pressed, IsKeyDown(key) || IsKeyDown(alternative), real_elapsed,
                                  was_walking && walking_enabled(), !game.busy()) &&
                (!step || (pressed && !fresh_step))) {
                step = direction;
                fresh_step = pressed;
            }
        }
        if (step && !game.busy())
            session->move(*step);
        session->advance_commands(game_elapsed);
        session->dispatch(renderer.draw(game, ui, renderer.mouse_position(), real_elapsed));
        if (!walking_enabled())
            for (std::size_t i = 0; i < directions.size(); ++i) {
                const auto [key, alternative, direction] = directions[i];
                walking[i].update(false, IsKeyDown(key) || IsKeyDown(alternative), 0, false);
            }
        renderer.present();
    }
};
} // namespace

int main(int argc, char** argv) try {
#ifdef __ANDROID__
    const std::filesystem::path application = GetAndroidApp()->activity->internalDataPath;
    std::filesystem::current_path(application / "game");
    const auto executable = application / "game";
#else
    const std::filesystem::path executable = GetApplicationDirectory();
#endif
    auto executable_file = executable / std::filesystem::path(argv[0]).filename();
#ifdef _WIN32
    if (!std::filesystem::exists(executable_file))
        executable_file += ".exe";
#endif
    std::filesystem::path requested_assets, load_file, replay_file, screenshot;
#ifdef __EMSCRIPTEN__
    std::filesystem::path save_directory = "/Savedat";
#elif defined(__ANDROID__)
    auto save_directory = application / "Savedat";
#else
    auto save_directory = executable / "Savedat";
#endif
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
                         "K / L: eight save / load slots. Q / Shift+Q: quick save / restore.\n"
                         "Shift+L: floor autosave. Shift+F: Fairy checkpoint. Shift+N: new game.\n"
                         "O: settings. H: help. M: mute. R: Fairy rankings. Saves: Savedat/.\n"
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
    auto loop = std::make_unique<GameLoop>();
    loop->assets = std::make_unique<Assets>(
        Assets::select(executable, requested_assets, TSW_ORIGINAL_ASSETS, TSW_ASSETS), executable_file);
    std::cout << "Assets: " << loop->assets->root()
              << (loop->assets->original_layout() ? " (original layout)\n" : " (PNG layout)\n");
    std::cout << "Saves: " << save_directory << '\n';
    const bool hidden = !screenshot.empty();
    unsigned flags = FLAG_WINDOW_HIGHDPI | FLAG_VSYNC_HINT | (hidden ? FLAG_WINDOW_HIDDEN : 0);
#if !defined(__ANDROID__) && !defined(__EMSCRIPTEN__)
    flags |= FLAG_WINDOW_RESIZABLE;
#endif
    SetConfigFlags(flags);
    SetTraceLogLevel(LOG_WARNING);
#ifdef __ANDROID__
    // Use native pixels so Android density and thumb targets refer to the same surface.
    InitWindow(0, 0, "Tower of the Sorcerer");
#else
    InitWindow(CanvasWidth, CanvasHeight, "Tower of the Sorcerer");
#endif
#if !defined(__ANDROID__) && !defined(__EMSCRIPTEN__)
    SetWindowMinSize(640, 447);
#endif
    SetExitKey(KEY_NULL);
#ifdef __EMSCRIPTEN__
    SetTargetFPS(0);
#else
    SetTargetFPS(hidden ? 0 : 60);
#endif
    int result = 0;
    {
        loop->session = std::make_unique<DesktopSession>(*loop->assets, save_directory, Game{}, record);
        auto& session = *loop->session;
#if defined(__ANDROID__) || defined(__EMSCRIPTEN__)
        if (!std::filesystem::exists(save_directory / "settings.json"))
            session.ui.mouse_walking = true;
#endif
        if (language)
            session.ui.language = *language;
        if (!load_file.empty())
            session.load(load_file, load_kind);
        else if (!replay_file.empty())
            session.replay(replay_file);
        else
            session.open_home(true);
#ifdef __EMSCRIPTEN__
        emscripten_set_main_loop_arg(
            [](void* state) {
                try {
                    static_cast<GameLoop*>(state)->frame();
                    static bool first_frame = true;
                    if (first_frame) {
                        first_frame = false;
                        EM_ASM({ Module['tswGameReady'](); });
                    }
                } catch (const std::exception& error) {
                    std::cerr << error.what() << '\n';
                    EM_ASM({ Module['tswGameError']('Game error: ' + UTF8ToString($0)); }, error.what());
                    emscripten_cancel_main_loop();
                }
            },
            loop.release(), 0, true);
#else
        while (!WindowShouldClose()) {
            loop->frame();
            if (!screenshot.empty()) {
                result = session.renderer.screenshot(screenshot) ? 0 : 1;
                break;
            }
        }
#endif
        loop.reset(); // Renderer resources must be released before closing the graphics context.
    }
    CloseWindow();
    return result;
} catch (const std::exception& error) {

    std::cerr << error.what() << '\n';
#ifdef __EMSCRIPTEN__
    EM_ASM({ Module['tswGameError']('Unable to start the game: ' + UTF8ToString($0)); }, error.what());
#endif
    return 1;
}
