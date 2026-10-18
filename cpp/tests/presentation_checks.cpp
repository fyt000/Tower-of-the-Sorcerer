#include "audio.hpp"
#include "desktop_checks.hpp"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

namespace tsw {
namespace {
std::uint64_t fingerprint(const Image& image, Rectangle region) {
    Color* pixels = LoadImageColors(image);
    std::uint64_t hash = 14695981039346656037ULL;
    for (int y = int(region.y); y < int(region.y + region.height); ++y)
        for (int x = int(region.x); x < int(region.x + region.width); ++x) {
            const auto p = pixels[y * image.width + x];
            for (unsigned char byte : {p.r, p.g, p.b}) {
                hash ^= byte;
                hash *= 1099511628211ULL;
            }
        }
    UnloadImageColors(pixels);
    return hash;
}

std::uint64_t fingerprint(Presentation& renderer, Rectangle region) {
    Image image = renderer.capture_canvas();
    const auto hash = fingerprint(image, region);
    UnloadImage(image);
    return hash;
}

bool matches_original_hero(Presentation& renderer, Rectangle target, const Image& atlas, int tile) {
    const auto cell = [](int tile) -> Rectangle {
        return {float((tile - 1) % 11 * 40), float((tile - 1) / 11 * 40), 40, 40};
    };
    Image road = ImageFromImage(atlas, cell(Road));
    Image expected = GenImageColor(40, 40, BLANK);
    // A sliding sprite spans tiles; the floor texture stays anchored to the board.
    for (int y = 0; y <= 1; ++y)
        for (int x = 0; x <= 1; ++x)
            ImageDraw(&expected, road, {0, 0, 40, 40},
                      {float(x * 40 - (int(target.x) - BoardX) % 40),
                       float(y * 40 - (int(target.y) - BoardY) % 40), 40, 40},
                      WHITE);
    UnloadImage(road);
    Image color = ImageFromImage(atlas, cell(tile));
    Image mask = ImageFromImage(atlas, cell(tile + 1));
    ImageColorInvert(&mask);
    ImageAlphaMask(&color, mask);
    ImageDraw(&expected, color, {0, 0, 40, 40}, {0, 0, 40, 40}, WHITE);
    Image canvas = renderer.capture_canvas();
    Color* actual = LoadImageColors(canvas);
    Color* reference = LoadImageColors(expected);
    bool matches = true;
    // CPU and GPU alpha blending can differ by one channel level at mask edges.
    for (int y = 0; y < 40; ++y)
        for (int x = 0; x < 40; ++x) {
            const auto a = actual[(int(target.y) + y) * canvas.width + int(target.x) + x];
            const auto b = reference[y * 40 + x];
            matches &= std::abs(int(a.r) - int(b.r)) <= 1 && std::abs(int(a.g) - int(b.g)) <= 1 &&
                       std::abs(int(a.b) - int(b.b)) <= 1;
        }
    UnloadImageColors(actual);
    UnloadImageColors(reference);
    UnloadImage(canvas);
    UnloadImage(expected);
    UnloadImage(color);
    UnloadImage(mask);
    return matches;
}

constexpr Rectangle BoardArea{BoardX, BoardY, BoardPixels, BoardPixels};
constexpr Rectangle ContentArea{0, MenuHeight, CanvasWidth, ContentHeight};
} // namespace

int verify_presentation(Presentation& renderer, const std::filesystem::path& output, const Assets& assets) {
    std::filesystem::create_directories(output);
    std::vector<std::string> checks;
    const auto require = [&](bool condition, const std::string& description) {
        if (!condition)
            throw std::runtime_error("Presentation check failed: " + description);
        checks.push_back(description);
    };
    DesktopUi ui;
    const auto draw = [&](const Game& game) { renderer.draw(game, ui, {-1, -1}); };
    const auto snapshot = [&](const std::string& name) {
        require(renderer.screenshot(output / (name + ".png")), "Export " + name);
    };

    {
        Game game;
        auto* window = glfwGetCurrentContext();
        const auto callback = glfwSetKeyCallback(window, nullptr);
        glfwSetKeyCallback(window, callback);
        const auto key = [&](int code, int modifier = 0) {
            if (modifier)
                callback(window, modifier, 0, GLFW_PRESS, 0);
            callback(window, code, 0, GLFW_PRESS, 0);
            const auto action = keyboard_input(game, ui);
            callback(window, code, 0, GLFW_RELEASE, 0);
            if (modifier)
                callback(window, modifier, 0, GLFW_RELEASE, 0);
            renderer.present();
            return action.kind;
        };
        require(key(KEY_Q) == Action::Save && key(KEY_Q, KEY_LEFT_SHIFT) == Action::Load,
                "Q saves and Shift+Q restores without function keys");
        require(key(KEY_K) == Action::OpenSaveSlots && key(KEY_L) == Action::OpenLoadSlots &&
                    key(KEY_L, KEY_RIGHT_SHIFT) == Action::LoadAutosave,
                "K and L select manual slots while Shift+L restores the floor autosave");
        require(key(KEY_F) == Action::None && key(KEY_F, KEY_LEFT_SHIFT) == Action::FairyCheckpoint &&
                    key(KEY_N) == Action::None && key(KEY_N, KEY_LEFT_SHIFT) == Action::NewGame,
                "Fairy restore and New game require Shift");
        for (int code = KEY_F1; code <= KEY_F12; ++code)
            require(key(code) == Action::None, "Function keys no longer dispatch game actions");
        for (const int modifier : {KEY_LEFT_CONTROL, KEY_RIGHT_CONTROL, KEY_LEFT_ALT, KEY_RIGHT_ALT,
                                   KEY_LEFT_SUPER, KEY_RIGHT_SUPER}) {
            require(key(KEY_Q, modifier) == Action::None && key(KEY_L, modifier) == Action::None &&
                        key(KEY_O, modifier) == Action::None,
                    "Browser and OS modifier combinations cannot invoke game shortcuts");
            callback(window, modifier, 0, GLFW_PRESS, 0);
            require(!game_shortcut_modifiers(), "Browser and OS modifiers also suspend WASD walking");
            callback(window, modifier, 0, GLFW_RELEASE, 0);
            renderer.present();
        }
        require(key(KEY_O) == Action::OpenSettings, "O opens Settings");
        key(KEY_H);
        require(ui.help, "H opens Help");
        require(key(KEY_Q) == Action::None, "Help consumes game shortcuts");
        ui.close_overlays();
        ui.selected_item = int(Item::Cross);
        require(key(KEY_Q) == Action::None && key(KEY_L, KEY_LEFT_SHIFT) == Action::None,
                "Save and restore shortcuts respect item panel file controls");
        require(key(KEY_ENTER) == Action::None && ui.selected_item < 0,
                "Enter closes passive item details without using an item");
        for (const auto item : {Item::Elixir, Item::Mattock, Item::Bomb, Item::WarpStaff, Item::AscentWing,
                                Item::DescentWing, Item::SnowCrystal, Item::MagicKey, Item::SuperMattock}) {
            ui.selected_item = int(item);
            game.inventory(item) = 1;
            require(key(KEY_ENTER) == Action::UseItem && ui.selected_item == int(item),
                    "Enter confirms each actionable item from its description panel");
            game.push(Op::Wait);
            require(key(KEY_ENTER) == Action::None,
                    "Keyboard confirmation cannot use an item while gameplay is busy");
            game.finish_commands();
            game.inventory(item) = 0;
            require(key(KEY_ENTER) == Action::None, "Keyboard confirmation cannot use an unavailable item");
            require(key(KEY_ESCAPE) == Action::None && ui.selected_item < 0,
                    "Escape cancels item confirmation");
        }
        ui.close_overlays();
        ui.replay_active = true;
        require(key(KEY_Q) == Action::None && key(KEY_L, KEY_LEFT_SHIFT) == Action::None,
                "Replay playback cannot save or restore through live shortcuts");
        ui.replay_active = false;
        ui.replay_picker = true;
        require(key(KEY_Q) == Action::None && key(KEY_N, KEY_LEFT_SHIFT) == Action::None,
                "Replay path entry consumes game shortcuts");
        ui.close_overlays();
        ui.save_picker = SavePicker::Load;
        require(key(KEY_L, KEY_LEFT_SHIFT) == Action::LoadAutosave,
                "The load picker can restore the floor autosave by shortcut");
        ui.close_overlays();
    }

    {
        TouchRepeat pad;
        const auto left = TouchButton::Left, confirm = TouchButton::Confirm;
        pad.update(TouchContext::Walk, {}, false, false, 0);
        require(pad.update(TouchContext::Walk, left, true, true, 0) == left,
                "A fresh direction touch emits one step immediately");
        require(!pad.update(TouchContext::Walk, left, true, false, .15f),
                "A short direction touch remains one step");
        require(pad.update(TouchContext::Walk, left, true, false, .101f) == left,
                "A held direction waits 250 ms before its first repeat");
        require(!pad.update(TouchContext::Walk, left, true, false, WalkRepeatSeconds / 2) &&
                    pad.update(TouchContext::Walk, left, true, false, WalkRepeatSeconds) == left,
                "Subsequent touch repeats use the keyboard's 120 ms real-time interval");
        require(!pad.update(TouchContext::Dialogue, left, true, false, 1) &&
                    !pad.update(TouchContext::Walk, left, true, false, 1),
                "A touch cannot carry across dialogue or return to movement without release");
        pad.update(TouchContext::Walk, {}, false, false, 0);
        require(!pad.update(TouchContext::Walk, left, true, false, 1),
                "Dragging onto the pad from elsewhere does not acquire a touch");
        pad.update(TouchContext::Dialogue, {}, false, false, 0);
        require(pad.update(TouchContext::Dialogue, confirm, true, true, 0) == confirm &&
                    !pad.update(TouchContext::Dialogue, confirm, true, false, 10),
                "Confirm is emitted on a fresh press and never auto repeats");
        pad.update(TouchContext::Walk, {}, false, false, 0);
        pad.update(TouchContext::Walk, left, true, true, 0);
        require(!pad.update(TouchContext::Walk, confirm, true, false, 1),
                "Sliding from an arrow to Confirm never confirms an action");
        pad.update(TouchContext::Hidden, left, true, false, 1);
        require(!pad.update(TouchContext::Walk, left, true, false, 1),
                "Menus disable a held direction until the pointer is released");
        pad.update(TouchContext::Walk, {}, false, false, 0);
        pad.update(TouchContext::Walk, left, true, true, 0);
        require(!pad.update(TouchContext::Walk, {}, false, false, 1),
                "Pointer cancellation releases a held direction");
        Game game;
        ui.touch_controls = true;
        draw(game);
        renderer.present();
        detail::UniqueImage controls(renderer.capture_window());
        require(ExportImage(controls.get(), (output / "touch-controls.png").string().c_str()),
                "Export screen-space touch controls");
        auto* window = glfwGetCurrentContext();
        const auto callback = glfwSetMouseButtonCallback(window, nullptr);
        glfwSetMouseButtonCallback(window, callback);
        const auto press = [&](Vector2 point) {
            callback(window, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);
            const auto action = renderer.draw(game, ui, point);
            callback(window, GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE, 0);
            draw(game);
            return action;
        };
        const auto control_point = [&](TouchButton button) {
            const auto view = window_viewport();
            const auto rect = touch_buttons(view)[int(button)];
            return view.canvas_point({rect.x + rect.width / 2, rect.y + rect.height / 2});
        };
        const auto step = press(control_point(TouchButton::Left));
        require(step.kind == Action::Move && step.value == int(Direction::Left),
                "The visible Left button dispatches a directional step instead of map walking");
        ui.flight = 2;
        draw(game);
        require(press(control_point(TouchButton::Up)).kind == Action::FlightUp &&
                    press(control_point(TouchButton::Confirm)).kind == Action::Travel &&
                    press(control_point(TouchButton::Cancel)).kind == Action::CancelFlight,
                "Touch Flight provides floor selection, travel and a visible Cancel button");
        snapshot("touch-flight");
        ui.flight = -1;
        game.dialogue = Dialogue{"Touch dialogue."};
        draw(game);
        const auto release = [&](Vector2 point) {
            callback(window, GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE, 0);
            const auto action = renderer.draw(game, ui, point);
            renderer.present();
            return action;
        };
        const auto begin = [&](Vector2 point) {
            callback(window, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);
            const auto action = renderer.draw(game, ui, point);
            renderer.present();
            return action;
        };
        require(begin({300, 210}).kind == Action::None && release({300, 210}).kind == Action::Continue,
                "A tap on conversation text continues on release without an extra OK button");
        require(press(control_point(TouchButton::Confirm)).kind == Action::None,
                "The former pad confirmation cannot skip dialogue");
        game.dialogue->text.clear();
        for (int line = 0; line < 30; ++line)
            game.dialogue->text += "A long conversation to scroll.\n";
        draw(game);
        begin({300, 290});
        renderer.draw(game, ui, {300, 180});
        require(ui.dialogue_scroll > 0 && release({300, 180}).kind == Action::None,
                "Dragging long conversation text scrolls without advancing it");
        begin({300, 210});
        game.dialogue->text = "A new conversation.";
        require(release({300, 210}).kind == Action::None,
                "A touch cannot carry over to a different conversation");
        snapshot("touch-dialogue");
        game.dialogue->shop = true;
        game.dialogue->choices[0] = "Buy";
        draw(game);
        require(begin({300, 210}).kind == Action::None && release({300, 210}).kind == Action::None &&
                    press(control_point(TouchButton::Confirm)).kind == Action::None,
                "Shop text and the former OK pad never select a purchase");
        for (int line = 0; line < 30; ++line)
            game.dialogue->text += "A long shop offer to scroll.\n";
        begin({300, 290});
        renderer.draw(game, ui, {300, 180});
        require(ui.dialogue_scroll > 0 && release({300, 180}).kind == Action::None,
                "Long shop prose can scroll without selecting an offer");
        require(press({260, 403}).kind == Action::Choose, "Purchases still require an explicit shop choice");
        game.dialogue.reset();
        ui.menu = Menu::Options;
        draw(game);
        require(press(control_point(TouchButton::Left)).kind == Action::None,
                "A menu consumes touches where the hidden pad would otherwise appear");
        ui.menu = Menu::Options; // That location can also activate the menu's Done button.
        ui.settings_tab = SettingsTab::Game;
        auto speed = begin({400, 300});
        require(speed.kind == Action::Speed && speed.value == 55,
                "Clicking the speed slider selects an intermediate 5.5x multiplier");
        ui.animation_speed = 5.5f;
        speed = renderer.draw(game, ui, {900, 260});
        require(speed.kind == Action::Speed && speed.value == MaxAnimationSpeed,
                "Dragging beyond the slider keeps capture and clamps at 10x");
        speed = renderer.draw(game, ui, {-100, 260});
        require(speed.kind == Action::Speed && speed.value == MinAnimationSpeed,
                "Dragging below the slider clamps at 1x");
        require(release({660, 300}).kind == Action::None &&
                    renderer.draw(game, ui, {140, 300}).kind == Action::None,
                "Releasing the slider stops speed changes");
        require(press({708, 300}).value == 56 && press({92, 300}).value == 54,
                "Speed buttons provide precise 0.1x adjustments");
        begin({400, 350});
        require(renderer.draw(game, ui, {660, 300}).kind == Action::None,
                "A drag starting outside the slider cannot acquire it");
        release({660, 300});
        snapshot("settings-speed-slider");
        ui.animation_speed = 1;
        press({266, 114});
        require(ui.settings_tab == SettingsTab::Qol, "Settings exposes a separate clickable QOL tab");
        require(press({568, 276}).kind == Action::SkipAttackAnimation &&
                    press({232, 336}).kind == Action::SkipStaircaseAnimation &&
                    press({568, 336}).kind == Action::MouseWalking,
                "Settings exposes separate clickable attack and staircase animation skips");
        require(ui.item_use_mode == ItemUseMode::Confirm,
                "Item use defaults to confirmation without descriptions");
        for (const auto mode : ItemUseModes) {
            ui.item_use_mode = mode;
            require(press({568, 396}).kind == Action::CycleItemUse,
                    "The QOL item use control remains clickable in all three modes");
        }
        ui.item_use_mode = ItemUseMode::Confirm;
        ui.close_overlays();
        ui.touch_controls.reset();
    }

    {
        // Independent sprite expectations from 0x443120 (idle) and 0x443808 (walk).
        Image atlas = assets.image("original-atlas");
        constexpr std::array<int, 4> IdleTiles{189, 197, 205, 213}, WalkingTiles{185, 193, 201, 209};
        for (int facing = 1; facing <= 4; ++facing) {
            renderer.reset();
            Game game;
            game.floors[1].tiles.fill(Road);
            game.hero.x = game.hero.y = 5;
            const auto before = game.hero;
            game.move(static_cast<Direction>(facing));
            game.finish_commands();
            const Rectangle target{float(BoardX + game.hero.x * TileSize),
                                   float(BoardY + game.hero.y * TileSize), TileSize, TileSize};
            renderer.moved(before, game.hero);
            const Rectangle origin{float(BoardX + before.x * TileSize), float(BoardY + before.y * TileSize),
                                   TileSize, TileSize};
            draw(game);
            require(matches_original_hero(renderer, origin, atlas, WalkingTiles[facing - 1]),
                    "Direction " + std::to_string(facing) + " begins with the original first walking pose");
            renderer.advance(WalkAnimationSeconds * .6f);
            draw(game);
            const Rectangle intermediate{origin.x + (target.x - origin.x) * .6f,
                                         origin.y + (target.y - origin.y) * .6f, TileSize, TileSize};
            require(matches_original_hero(renderer, intermediate, atlas, WalkingTiles[facing - 1] + 2),
                    "Direction " + std::to_string(facing) + " advances to the original second walking pose");
            renderer.advance(WalkAnimationSeconds);
            draw(game);
            require(matches_original_hero(renderer, target, atlas, IdleTiles[facing - 1]),
                    "Direction " + std::to_string(facing) + " returns to the original standing pose");
            snapshot("idle-direction-" + std::to_string(facing));
            for (float speed : {1.f, 3.f, 10.f}) {
                renderer.reset();
                renderer.moved(before, game.hero, true);
                renderer.advance(WalkAnimationSeconds * .6f * speed, WalkAnimationSeconds * .6f);
                draw(game);
                require(matches_original_hero(renderer, intermediate, atlas, WalkingTiles[facing - 1] + 2),
                        "Manual walking slides at the same real-time speed at 1x, 3x and 10x");
                renderer.advance(WalkAnimationSeconds * speed, WalkAnimationSeconds);
                draw(game);
                require(matches_original_hero(renderer, target, atlas, IdleTiles[facing - 1]),
                        "A released single step finishes at its destination without extra movement");
            }
            renderer.moved(game.hero, before);
            renderer.advance(WalkAnimationSeconds * 3, WalkAnimationSeconds / 3);
            Game automatic = game;
            automatic.hero = before;
            automatic.hero.facing = game.hero.facing;
            draw(automatic);
            require(matches_original_hero(renderer, origin, atlas, IdleTiles[facing - 1]),
                    "Automatic walking still finishes on the scaled animation clock");
        }
        UnloadImage(atlas);
        std::array<int, 3> counts{};
        for (int speed = 0; speed < 3; ++speed) {
            WalkRepeat walking;
            require(walking.update(true, true, 0), "A fresh arrow press moves immediately");
            require(!walking.update(false, true, .15f),
                    "A 150 ms arrow tap cannot accidentally take a second step");
            require(walking.update(false, true, .101f), "Holding an arrow for 250 ms begins repetition");
            require(!walking.update(false, true, .1f) && walking.update(false, true, .021f),
                    "Subsequent arrow repeats wait 120 ms");
            walking.update(false, false, 0);
            require(!walking.update(false, true, 1), "A held key without a fresh press cannot begin walking");
            for (int frame = 0; frame < 120; ++frame) {
                renderer.advance(GameSpeeds[speed] / 60.f);
                if (walking.update(frame == 0, true, 1.f / 60))
                    ++counts[speed];
            }
            require(!walking.update(false, false, 0) && walking.update(true, true, 0),
                    "Releasing and tapping again accepts a fresh step immediately");
            require(!walking.update(false, true, 1, false) && !walking.update(false, true, 1) &&
                        !walking.update(true, true, 0),
                    "Menus, dialogue and lost focus block held directions until release");
            require(!walking.update(false, false, 0) && walking.update(true, true, 0),
                    "Releasing a blocked direction restores normal input");
        }
        require(counts[0] > 10 && counts[0] == counts[1] && counts[0] == counts[2],
                "1x, 3x and 10x animation speeds retain identical real-time keyboard repeat timing");
        for (int fps : {30, 60, 144}) {
            WalkRepeat walking;
            int steps = walking.update(true, true, 0);
            for (int frame = 0; frame < fps * 10; ++frame)
                steps += walking.update(false, true, 1.f / fps);
            require(steps == 83,
                    "Held walking preserves its 120 ms cadence at " + std::to_string(fps) + " FPS");
        }
        WalkRepeat walking;
        require(walking.update(true, true, 0), "Held event fixture starts with an immediate step");
        require(!walking.update(false, true, .3f, true, false) &&
                    !walking.update(false, true, 2.f, true, false) && walking.update(false, true, 0),
                "A due held step waits for an event, then resumes immediately when movement is ready");
        require(!walking.update(false, true, .1f) && walking.update(false, true, .021f),
                "Resuming after an event retains the normal interval without a burst of queued steps");
        walking.update(false, false, 0);
        require(!walking.update(true, true, 0, true, false) && !walking.update(false, false, 0) &&
                    !walking.update(false, true, 1),
                "Releasing a direction during an event cancels its pending step");
    }
    {
        // Use the desktop scheduler directly so these regressions do not open an audio device.
        DesktopUi options;
        options.skip_attack_animation = options.skip_staircase_animation = true;
        for (bool replay : {false, true}) {
            options.replay_active = replay;
            Game game;
            game.floors[1].tiles.fill(Road);
            game.hero.x = game.hero.y = 5;
            game.hero.hp = 10000;
            game.hero.attack = game.hero.defense = 10;
            game.monsters[0] = {500, 20, 5, 7};
            game.tile_at(1, 5, 4) = GreenSlime;
            game.move(Direction::Up);
            auto native = game;
            native.finish_commands();
            CommandPlayback playback;
            for (int beat = 0; beat < 5; ++beat)
                playback.advance(game, .06f, options);
            require(game.visual.battle && game.visual.enemy_hp == 495 && game.hero.gold == 0,
                    "Attack skipping displays the first strike before resolving live or replay combat");
            draw(game);
            snapshot(replay ? "skip-attack-replay-preview" : "skip-attack-preview");
            playback.advance(game, .06f, options);
            require(!game.busy() && game.hero == native.hero && game.floors == native.floors &&
                        game.run_history == native.run_history && game.status == native.status,
                    "Attack skipping immediately retains native damage, rewards and map changes");

            // The next encounter must earn its own preview even when the scheduler is reused.
            game.tile_at(1, 5, 3) = GreenSlime;
            game.move(Direction::Up);
            playback.advance(game, .06f, options);
            require(game.visual.battle && game.hero.gold == 7,
                    "Every encounter shows a fresh attack preview");
        }
        Game stairs;
        stairs.hero.x = 0;
        stairs.hero.y = 1;
        stairs.move(Direction::Up);
        auto native = stairs;
        auto paced = stairs;
        CommandPlayback normal_playback;
        normal_playback.advance(paced, .1f, DesktopUi{});
        require(paced.busy() && paced.visual.stair_source_floor >= 0,
                "Staircase animation remains paced by default");
        native.finish_commands();
        CommandPlayback playback;
        playback.advance(stairs, 0, options);
        require(stairs.hero.floor == 2 && stairs.visual.stair_source_floor == -1 &&
                    std::none_of(stairs.visual.stair_cover.begin(), stairs.visual.stair_cover.end(),
                                 [](bool covered) { return covered; }),
                "Staircase skipping fully reveals the destination in a single frame without elapsed time");
        playback.advance(stairs, .1f, options);
        require(!stairs.busy() && stairs.hero == native.hero && stairs.floors == native.floors &&
                    stairs.status == native.status,
                "Skipping staircase presentation retains native arrival state and messages");
        std::array<int, 3> stair_frames{};
        for (int speed = 0; speed < 3; ++speed) {
            Game animated;
            animated.hero.x = 0;
            animated.hero.y = 1;
            animated.move(Direction::Up);
            CommandPlayback clock;
            while (animated.busy() && stair_frames[speed] < 600) {
                clock.advance(animated, GameSpeeds[speed] / 60.f, DesktopUi{});
                ++stair_frames[speed];
            }
        }
        require(stair_frames[0] > stair_frames[1] && stair_frames[1] > stair_frames[2] &&
                    std::abs(stair_frames[0] - stair_frames[2] * 10) <= 10,
                "The shared animation speed accelerates staircase wipes at 1x, 3x and 10x");

        Game door;
        door.tile_at(1, 5, 4) = YellowDoor;
        door.hero.yellow_keys = 1;
        door.hero.x = door.hero.y = 5;
        door.move(Direction::Up);
        playback.reset();
        playback.advance(door, .016f, options);
        require(door.busy(), "Animation skips retain ordinary door pacing");

        Game battle;
        battle.floors[1].tiles.fill(Road);
        battle.hero.x = battle.hero.y = 5;
        battle.hero.attack = battle.hero.defense = 10;
        battle.tile_at(1, 5, 4) = GreenSlime;
        battle.waits(20);
        battle.contact_index = cell(5, 4);
        battle.battle(false);
        playback.reset();
        playback.advance(battle, .36f, options);
        require(battle.hero.gold == 1 && battle.commands.size() == 20,
                "Fast combat stops at its boundary and preserves following scripted event delays");
    }
    {
        renderer.reset();
        Game game;
        game.floors[1].tiles.fill(Road);
        game.hero.x = game.hero.y = 5;
        const Vector2 hover{BoardX + 8 * TileSize + 20, BoardY + 5 * TileSize + 20};
        require(!ui.mouse_walking && !mouse_destination(game, ui, hover),
                "Mouse walking defaults off and cannot select a destination");
        ui.mouse_walking = true;
        require(mouse_destination(game, ui, hover) == cell(8, 5),
                "A map click selects the tile under the logical mouse coordinates");
        ui.mouse_walking = false;
        ui.blink_mode = true;
        require(mouse_destination(game, ui, hover) == cell(8, 5),
                "Blink enables map clicks independently of mouse walking");
        ui.blink_mode = false;
        ui.mouse_walking = true;
        const CanvasViewport viewport{1600, 1116, 1600, 1116, {0, 0, 1600, 1116}};
        require(mouse_destination(game, ui, viewport.canvas_point({hover.x * 2, hover.y * 2})) == cell(8, 5),
                "Resized-window mouse coordinates select the same map tile");
        for (const Vector2 outside : std::array<Vector2, 4>{{{BoardX - 1, BoardY},
                                                             {BoardX, BoardY - 1},
                                                             {BoardX + BoardPixels, BoardY},
                                                             {BoardX, BoardY + BoardPixels}}})
            require(!mouse_destination(game, ui, outside),
                    "Clicks outside each board edge cannot select a wrapped tile");
        for (auto flag :
             {&DesktopUi::home, &DesktopUi::replay_picker, &DesktopUi::rankings, &DesktopUi::inventory,
              &DesktopUi::enemies, &DesktopUi::help, &DesktopUi::replay_active, &DesktopUi::ending_wait}) {
            ui.*flag = true;
            require(!mouse_destination(game, ui, hover),
                    "Menus, panels, replay and ending cards disable map clicks");
            ui.*flag = false;
        }
        ui.flight = 2;
        require(!mouse_destination(game, ui, hover), "Flight preview cannot move the hero by clicking");
        ui.flight = -1;
        ui.selected_item = int(Item::Cross);
        require(!mouse_destination(game, ui, hover), "Item inspection disables map clicks");
        ui.close_overlays();
        ui.menu = Menu::Options;
        require(!mouse_destination(game, ui, hover), "Options disable map clicks");
        ui.close_overlays();
        ui.save_picker = SavePicker::Load;
        require(!mouse_destination(game, ui, hover), "The save picker disables map clicks");
        ui.close_overlays();
        game.push(Op::Wait);
        require(!mouse_destination(game, ui, hover), "Queued events disable map clicks");
        game.finish_commands();
        const auto press_at = [&](Vector2 mouse) {
            auto* window = glfwGetCurrentContext();
            const auto callback = glfwSetMouseButtonCallback(window, nullptr);
            glfwSetMouseButtonCallback(window, callback);
            require(callback != nullptr, "The window has a native mouse input callback");
            callback(window, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);
            const auto action = renderer.draw(game, ui, mouse);
            callback(window, GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE, 0);
            return action;
        };
        const auto click = press_at(hover);
        require(click.kind == Action::WalkTo && click.value == cell(8, 5),
                "A left map click dispatches the selected destination");
        ui.help = true;
        require(press_at({400, 480}).kind == Action::None && !ui.help,
                "Closing Help consumes its click without selecting the floor underneath");
        ui.inventory = true;
        require(press_at({BoardX + 50, BoardY + 400}).kind == Action::None && !ui.inventory,
                "Closing inventory consumes its click without selecting the floor underneath");
        ui.selected_item = int(Item::Cross);
        require(press_at({BoardX + 50, BoardY + 315}).kind == Action::None && ui.selected_item < 0,
                "Closing item inspection consumes its click without selecting the floor underneath");
        renderer.draw(game, ui, hover);
        const auto ordinary_floor = fingerprint(renderer, BoardArea);
        snapshot("mouse-hover-floor");
        game.tile_at(1, 7, 5) = SpecialRoad;
        renderer.draw(game, ui, hover);
        require(fingerprint(renderer, BoardArea) == ordinary_floor,
                "Hidden trigger floors do not change the map or mouse hover feedback");
        game.tile_at(1, 7, 5) = Road;
        game.tile_at(1, 8, 5) = Wall;
        renderer.draw(game, ui, hover);
        const auto ordinary_wall = fingerprint(renderer, BoardArea);
        for (const auto hidden : {SecretWall, HiddenObject}) {
            game.tile_at(1, 8, 5) = hidden;
            renderer.draw(game, ui, hover);
            require(fingerprint(renderer, BoardArea) == ordinary_wall,
                    "Hidden walls and objects do not change the map or mouse hover feedback");
        }
        snapshot("mouse-hover-wall");
        renderer.draw(game, ui, {230, 12});
        snapshot("mouse-qol-tooltip");
        ui.mouse_walking = false;
        ui.menu = Menu::Options;
        ui.settings_tab = SettingsTab::Qol;
        renderer.draw(game, ui, {-1, -1});
        snapshot("blink-settings-off");
        require(press_at({300, 396}).kind == Action::BlinkMode,
                "The QOL tab dispatches the Blink mode toggle");
        ui.blink_mode = true;
        renderer.draw(game, ui, {-1, -1});
        snapshot("blink-settings-on");
        ui.blink_mode = false;
        ui.close_overlays();
    }
    {
        renderer.reset();
        Game game;
        game.floors[1].tiles.fill(Road);
        game.hero.x = game.hero.y = 5;
        game.tile_at(1, 2, 2) = RedGem;
        game.tile_at(1, 8, 2) = BluePotion;
        game.tile_at(1, 8, 8) = IronSword;
        const auto press_at = [&](Vector2 mouse) {
            auto* window = glfwGetCurrentContext();
            const auto callback = glfwSetMouseButtonCallback(window, nullptr);
            glfwSetMouseButtonCallback(window, callback);
            callback(window, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);
            const auto action = renderer.draw(game, ui, mouse);
            callback(window, GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE, 0);
            return action;
        };
        constexpr Rectangle toolbar{22, 476, 112, 48};
        Image original_panel = assets.image("data3-left");
        const auto unobstructed = fingerprint(original_panel, {22, 448, 112, 48});
        UnloadImage(original_panel);
        draw(game);
        require(!ui.item_collection && fingerprint(renderer, toolbar) == unobstructed,
                "Collection defaults off with both buttons and their background completely absent");
        snapshot("collection-disabled");
        require(press_at({48, 500}).kind == Action::None && press_at({108, 500}).kind == Action::None,
                "Hidden collection buttons cannot be activated");
        ui.menu = Menu::Options;
        ui.settings_tab = SettingsTab::Qol;
        require(press_at({232, 276}).kind == Action::ItemCollection,
                "The QOL tab dispatches the Item collection toggle");
        ui.close_overlays();
        ui.item_collection = true;
        require(press_at({48, 500}).kind == Action::CollectAll,
                "Zuck all dispatches from the inventory toolbar");
        require(press_at({108, 500}).kind == Action::CollectExceptPotions,
                "Zuck all except potion dispatches from its separate button");
        ui.replay_active = true;
        require(press_at({48, 500}).kind == Action::None, "Collection cannot mutate an active replay");
        ui.replay_active = false;
        game.push(Op::Wait);
        require(press_at({48, 500}).kind == Action::None,
                "Collection controls are disabled while native events are pending");
        game.finish_commands();
        const int x = game.hero.x, y = game.hero.y;
        const auto items = collect_items(game, false);
        draw(game);
        const auto finished = fingerprint(renderer, BoardArea);
        renderer.collected(game.hero.floor, items);
        draw(game);
        snapshot("collection-start");
        require(renderer.collecting() && game.hero.x == x && game.hero.y == y,
                "Flying pickups keep the hero in place");
        renderer.draw(game, ui, {-1, -1}, .23f);
        snapshot("collection-flying");
        require(fingerprint(renderer, BoardArea) != finished,
                "Collected item icons fly over the cleared map");
        require(press_at({48, 500}).kind == Action::None,
                "Repeated collection is disabled until the flight animation finishes");
        renderer.draw(game, ui, {-1, -1}, .5f);
        require(!renderer.collecting() && fingerprint(renderer, BoardArea) == finished,
                "Item flights finish cleanly without leaving sprites on the board");
        snapshot("collection-finished");
        renderer.collected(game.hero.floor, items);
        renderer.reset();
        require(!renderer.collecting(), "Loads and new games clear pending collection effects");
        ui.item_collection = false;
        draw(game);
        require(fingerprint(renderer, toolbar) == unobstructed,
                "Turning collection back off restores the original panel background");
    }
    {
        renderer.reset();
        Game game;
        game.floors[1].tiles.fill(Road);
        game.hero.x = 5;
        game.hero.y = 9;
        game.hero.attack = 50;
        game.hero.defense = 40;
        game.hero.hp = 150;
        game.monsters[0] = {100, 40, 10, 1};
        game.monsters[1] = {100, 75, 20, 3};
        game.monsters[2] = {150, 100, 25, 8};
        game.monsters[3] = {100, 75, 80, 4};
        for (int row = 0; row < 4; ++row) {
            game.tile_at(1, 2 + row, 3) = static_cast<std::uint8_t>(GreenSlime + row * 2);
            game.tile_at(1, 2 + row, 4) = static_cast<std::uint8_t>(GreenSlime + row * 2 + 1);
        }
        draw(game);
        const auto original = fingerprint(renderer, BoardArea);
        require(!ui.realtime_hero_orb, "Realtime Hero Orb defaults off");
        ui.realtime_hero_orb = true;
        draw(game);
        require(fingerprint(renderer, BoardArea) == original,
                "Enabling realtime stats cannot reveal monster information before owning Hero Orb");
        game.inventory(Item::HeroOrb) = 1;
        const auto hero = game.hero;
        const auto floors = game.floors;
        draw(game);
        const auto labeled = fingerprint(renderer, BoardArea);
        require(labeled != original, "Owning Hero Orb displays labels on normal and animated monster tiles");
        require(game.hero == hero && game.floors == floors, "Realtime labels preserve gameplay state");
        snapshot("realtime-orb-costs");
        for (int row = 0; row < 4; ++row) {
            const float x = float(BoardX + (2 + row) * TileSize), y = float(BoardY + 3 * TileSize);
            const auto pixels = renderer.capture_canvas();
            const auto color_count = [&](Color color) {
                Color* colors = LoadImageColors(pixels);
                int count = 0;
                for (int yy = int(y); yy < y + 12; ++yy)
                    for (int xx = int(x); xx < x + TileSize; ++xx) {
                        const auto actual = colors[yy * pixels.width + xx];
                        if (std::abs(int(actual.r) - int(color.r)) < 8 &&
                            std::abs(int(actual.g) - int(color.g)) < 8 &&
                            std::abs(int(actual.b) - int(color.b)) < 8)
                            ++count;
                    }
                UnloadImageColors(colors);
                return count;
            };
            constexpr std::array<Color, 4> colors{
                {{139, 245, 174, 255}, {255, 222, 148, 255}, {255, 118, 118, 255}, {212, 171, 255, 255}}};
            require(color_count(colors[row]) > 0,
                    "HP labels distinguish zero cost, survivable damage, lethal damage and blocked defense");
            UnloadImage(pixels);
        }
        renderer.draw(game, ui, {BoardX + 3 * TileSize + 20, BoardY + 3 * TileSize + 20});
        snapshot("realtime-orb-hover");
        game.hero.defense = 100;
        draw(game);
        require(fingerprint(renderer, BoardArea) != labeled,
                "Realtime forecasts update immediately when hero stats change");
        game.hero.cycle_factor_minus_one = 43;
        game.inventory(Item::LuckyGold) = 1;
        game.tile_at(1, 7, 4) = DragonHead;
        game.tile_at(1, 7, 6) = OctopusMouth;
        draw(game);
        snapshot("realtime-orb-backside");
        ui.realtime_hero_orb = false;
        draw(game);
        const auto disabled = fingerprint(renderer, BoardArea);
        game.push(Op::Wait);
        ui.realtime_hero_orb = true;
        draw(game);
        require(fingerprint(renderer, BoardArea) == disabled,
                "Queued events suppress realtime labels so animations remain unobscured");
        ui.realtime_hero_orb = false;
    }
    {
        renderer.reset();
        Game game;
        game.floors[1].tiles.fill(Road);
        game.hero.x = game.hero.y = 5;
        game.inventory(Item::HeroOrb) = 1;
        game.tile(1, cell(5, 4)) = GreenSlime;
        game.tile(1, cell(8, 8)) = RedSlime;
        game.move(Direction::Up);
        game.finish_commands();
        draw(game);
        constexpr Rectangle EnemyPanel{656, MenuHeight + 278, 128, 168};
        const auto last_enemy = fingerprint(renderer, EnemyPanel);
        require(game.visual.last_defeated && game.visual.last_defeated->monster_index == 0,
                "The battle panel receives a completed real combat result");
        snapshot("last-defeated-enemy");
        renderer.draw(game, ui, {BoardX + 8 * TileSize + 20, BoardY + 8 * TileSize + 20});
        require(last_enemy == fingerprint(renderer, EnemyPanel),
                "Hovering another enemy does not replace the last defeated enemy panel");
        game.move(Direction::Left);
        game.finish_commands();
        draw(game);
        require(last_enemy == fingerprint(renderer, EnemyPanel),
                "The last defeated enemy panel persists after walking away");
        ui.enemies = true;
        draw(game);
        snapshot("hero-orb-enemies");
        std::array<bool, 33> present{};
        int count = 0;
        for (int tile = GreenSlime; tile <= 165; ++tile) {
            const int row = Game::monster_for_tile(tile);
            if (row >= 0 && !present[row]) {
                present[row] = true;
                game.tile(1, count++) = static_cast<std::uint8_t>(tile);
            }
        }
        ui.enemy_first_row = 999;
        draw(game);
        require(count > 6 && ui.enemy_first_row == count - 6,
                "Hero Orb scrolling clamps to the final full page of enemy types");
        snapshot("hero-orb-last-page");
        game.floors[1].tiles.fill(Road);
        draw(game);
        require(ui.enemy_first_row == 0 && game.visual.last_defeated->monster_index == 0,
                "An empty Hero Orb overlay resets scrolling without erasing the last victory");
        snapshot("hero-orb-empty");
        ui.close_overlays();
    }

    {
        renderer.reset();
        Game alternate;
        alternate.floors[1].tiles.fill(Road);
        alternate.hero.x = alternate.hero.y = 5;
        alternate.inventory(Item::HeroOrb) = 1;
        for (int tile = 106; tile <= 114; ++tile)
            alternate.tile(1, tile - 106) = static_cast<std::uint8_t>(tile);
        alternate.tile(1, 10) = 123;
        alternate.tile(1, 11) = 131;
        alternate.tile(1, 12) = StairCover;
        alternate.tile(1, 13) = GateKeeperA + 1;
        ui.enemies = true;
        ui.enemy_first_row = 0;
        draw(alternate);
        // Exclude the raw atlas-piece icons; names, counts, stats and damage must agree.
        constexpr Rectangle OrbRows{152, BoardY + 108, 532, 240};
        const auto alternate_rows = fingerprint(renderer, OrbRows);
        snapshot("hero-orb-alternate-pieces");
        auto canonical = alternate;
        for (int index = 0; index < 9; ++index)
            canonical.tile(1, index) = OctopusFirst;
        for (int index = 10; index <= 12; ++index)
            canonical.tile(1, index) = Road;
        canonical.tile(1, 13) = GateKeeperA;
        draw(canonical);
        require(fingerprint(renderer, OrbRows) == alternate_rows,
                "Hero Orb groups alternate octopus pieces and Gate-Keeper frames into the same rows as base "
                "tiles");
        canonical.floors[1].tiles.fill(Road);
        draw(canonical);
        require(fingerprint(renderer, OrbRows) != alternate_rows,
                "Hero Orb alternate-only enemies produce visible rows rather than an empty floor");
        ui.close_overlays();
    }

    for (int gate : {TimeGate, TimeGate2}) {
        renderer.reset();
        Game game;
        game.floors[1].tiles.fill(Road);
        game.hero.x = game.hero.y = 5;
        game.tile_at(1, 4, 4) = static_cast<std::uint8_t>(gate);
        game.tile_at(1, 3, 4) = Lava;
        game.tile_at(1, 5, 4) = Altar;
        const Rectangle gate_area{BoardX + 4 * TileSize, BoardY + 4 * TileSize, TileSize, TileSize};
        const Rectangle lava_area{BoardX + 3 * TileSize, BoardY + 4 * TileSize, TileSize, TileSize};
        const Rectangle altar_area{BoardX + 5 * TileSize, BoardY + 4 * TileSize, TileSize, TileSize};
        draw(game);
        const auto gate_first = fingerprint(renderer, gate_area);
        renderer.advance(.5f);
        draw(game);
        const auto gate_second = fingerprint(renderer, gate_area);
        const auto lava_second = fingerprint(renderer, lava_area);
        const auto altar_second = fingerprint(renderer, altar_area);
        require(gate_first != gate_second,
                "Time Gate tile " + std::to_string(gate) + " animates before its conversation completes");
        game.hero.dialogue_seen[36] = 1;
        draw(game);
        require(fingerprint(renderer, gate_area) == gate_first,
                "Time Gate tile " + std::to_string(gate) + " freezes on its stored frame after speech");
        renderer.advance(.5f);
        draw(game);
        require(fingerprint(renderer, gate_area) == gate_first &&
                    fingerprint(renderer, lava_area) != lava_second &&
                    fingerprint(renderer, altar_area) != altar_second,
                "Completed Time Gate speech freezes only the gate, while lava and altars keep animating");
        game.hero.dialogue_seen[36] = 2;
        renderer.advance(.5f);
        draw(game);
        require(fingerprint(renderer, gate_area) == gate_second,
                "Time Gate animation tests completion flag equal to one, rather than any nonzero value");
    }

    // All twelve door modes must animate and finish with exactly the committed tile.
    for (int mode = 1; mode <= 12; ++mode) {
        renderer.reset();
        Game game;
        game.floors[1].tiles.fill(Road);
        constexpr int index = cell(4, 4);
        game.tile(1, index) = static_cast<std::uint8_t>(mode <= 3   ? mode
                                                        : mode == 4 ? SealedGate
                                                        : mode == 6 ? PrisonGate
                                                        : mode == 7 ? Wall
                                                        : mode >= 9 ? Lava
                                                                    : Road);
        game.push(Op::DoorFrame, index, static_cast<DoorMotion>(mode));
        game.expand_door();
        std::uint64_t first{}, middle{}, last{};
        const Rectangle target{BoardX + 4 * TileSize, BoardY + 4 * TileSize, TileSize, TileSize};
        Command command;
        int frames = 0;
        while (game.run_one(&command)) {
            if (command.op != Op::DoorFrame)
                continue;
            ++frames;
            draw(game);
            if (frames == 1)
                first = fingerprint(renderer, target);
            if (frames == 8) {
                middle = fingerprint(renderer, target);
                snapshot("door-mode-" + std::to_string(mode));
            }
            if (frames == 16)
                last = fingerprint(renderer, target);
        }
        draw(game);
        require(frames == 16 && first != middle && middle != last,
                "Door mode " + std::to_string(mode) + " has distinct ordered frames");
        require(last == fingerprint(renderer, target),
                "Door mode " + std::to_string(mode) + " agrees with its final map tile");
    }
    {
        renderer.reset();
        Game game;
        game.hero.x = 0;
        game.hero.y = 1;
        game.move(Direction::Up);
        int closed = 0, revealed = 0;
        Command command;
        while (game.run_one(&command))
            if (command.op == Op::StairFrame) {
                command.a ? ++revealed : ++closed;
                if (command.b == 60) {
                    draw(game);
                    snapshot(command.a ? "stairs-reveal" : "stairs-close");
                }
            }
        draw(game);
        require(closed == CellCount && revealed == CellCount && game.visual.stair_source_floor == -1 &&
                    std::none_of(game.visual.stair_cover.begin(), game.visual.stair_cover.end(),
                                 [](bool b) { return b; }),
                "Stair spiral covers the source and completely reveals the destination");
        snapshot("stairs-arrival");
    }
    {
        renderer.reset();
        Game game;
        game.hero.floor = 20;
        game.hero.x = 5;
        game.hero.y = 7;
        game.check_floor();
        int frames = 0;
        std::uint64_t first{}, middle{}, last{};
        Command command;
        while (game.run_one(&command)) {
            renderer.command(command);
            if (command.op == Op::Callback && command.a == int(Callback::Transformation)) {
                ++frames;
                draw(game);
                if (frames == 1)
                    first = fingerprint(renderer, BoardArea);
                if (frames == 16) {
                    middle = fingerprint(renderer, BoardArea);
                    snapshot("vampire-transformation");
                }
                if (frames == 32)
                    last = fingerprint(renderer, BoardArea);
            }
            if (game.dialogue)
                game.continue_dialogue();
        }
        require(frames == 32 && first != middle && middle != last &&
                    game.visual.raster_mode == RasterMode::Inactive,
                "Vampire transformation retains all 32 frames and restores the board");
    }
    {
        renderer.reset();
        Game game;
        game.hero.floor = 3;
        game.hero.x = 4;
        game.hero.y = 9;
        draw(game);
        game.move(Direction::Up);
        int dissolve = 0, wipe = 0;
        bool capture_music = true;
        std::uint64_t first{}, middle{}, final{}, title{}, opening{};
        Command command;
        while (game.run_one(&command)) {
            renderer.command(command);
            if (command.op == Op::Callback) {
                draw(game);
                if (game.visual.raster_mode == RasterMode::Title ||
                    game.visual.raster_mode == RasterMode::OpeningDissolve ||
                    game.visual.raster_mode == RasterMode::OpeningStory)
                    capture_music = capture_music && Audio::track_for_scene(game) == 11;
                if (command.a == int(Callback::HidePanels)) {
                    title = fingerprint(renderer, ContentArea);
                    snapshot("capture-title");
                }
                if (command.a == int(Callback::RasterScene)) {
                    if (game.visual.raster_mode == RasterMode::OpeningDissolve) {
                        ++dissolve;
                        if (command.b == 232) {
                            first = fingerprint(renderer, ContentArea);
                            snapshot("capture-first-mask");
                        }
                        if (command.b == 240) {
                            middle = fingerprint(renderer, ContentArea);
                            snapshot("capture-dissolve");
                        }
                        if (command.b == 247)
                            final = fingerprint(renderer, ContentArea);
                    } else if (game.visual.raster_mode == RasterMode::OpeningStory) {
                        ++wipe;
                        if (command.b == 0)
                            opening = fingerprint(renderer, ContentArea);
                        if (command.b == 300)
                            snapshot("capture-words");
                    }
                }
            }
            if (game.dialogue)
                game.continue_dialogue();
        }
        draw(game);
        require(dissolve == 16 && wipe == 308 && first != title && first != middle && middle != final &&
                    final == opening,
                "Capture uses the cached title, all dissolve masks and ordered horizontal wipes");
        require(game.hero.floor == 2 && game.hero.hp == 400 &&
                    game.visual.raster_mode == RasterMode::Inactive,
                "Capture compositor returns to the prison without changing the gameplay outcome");
        require(capture_music && Audio::track_for_scene(game) == std::to_underlying(game.hero.music_track),
                "Capture title music persists through its scenes, then returns to floor music");
        snapshot("capture-prison");
    }
    {
        renderer.reset();
        Game game;
        game.hero.floor = 50;
        game.hero.x = game.hero.y = 5;
        game.tile(50, cell(5, 4)) = Zeno;
        draw(game);
        game.move(Direction::Up);
        std::array<int, 9> modes{};
        Command command;
        while (game.run_one(&command)) {
            renderer.command(command);
            if (command.op == Op::Callback) {
                draw(game);
                const int mode = std::to_underlying(game.visual.raster_mode);
                if (command.a == int(Callback::RasterScene) && mode >= 0 && mode <= 8) {
                    ++modes[mode];
                    if (mode == 6 && command.b == 9)
                        snapshot("ending-tower");
                    if (mode == 4 && command.b == 205)
                        snapshot("ending-shrink");
                    if (mode == 5 && command.b == 250)
                        snapshot("ending-story-wipe");
                    if (mode == 5 && command.b == 400)
                        snapshot("ending-story");
                    if (mode == 7) {
                        require(Audio::track_for_scene(game) == 20,
                                "Closing card selects the original ending MIDI");
                        snapshot("ending-card");
                    }
                    if (mode == 8) {
                        ui.ending_wait = true;
                        require(game.ending_summary.has_value(),
                                "Ending keeps a snapshot of final hero statistics");
                        draw(game);
                        snapshot("ending-wait");
                        require(!ui.file_controls_enabled(),
                                "Ending summary blocks file controls until continued");
                        ui.ending_wait = false;
                    }
                }
            }
            if (game.dialogue)
                game.continue_dialogue();
        }
        require(modes[2] == 16 && modes[6] == 17 && modes[4] > 50 && modes[5] == 400 && modes[7] == 1 &&
                    modes[8] == 1,
                "Ending executes dissolve, tower frames, collapse, story wipe and closing callbacks");
        require(game.hero.cycle_factor_minus_one == BacksideFactor - 1 &&
                    game.visual.raster_mode == RasterMode::Inactive,
                "Ending returns to the playable backside tower");
        draw(game);
        snapshot("ending-backside");
    }
    {
        Game game;
        game.hero.hp = 98765432;
        game.hero.attack = 12345678;
        game.hero.defense = 87654321;
        game.hero.gold = 99999999;
        game.hero.altar_purchases = 1234;
        game.hero.yellow_keys = game.hero.blue_keys = game.hero.red_keys = 999999;
        game.hero.zeno_sealed = true;
        game.run_history.dragon_defeated = true;
        game.ending_summary = EndingSummary{game.hero, game.run_history};
        ui.ending_wait = true;
        draw(game);
        snapshot("ending-summary-large-stats");
        game.hero.hp = 3421;
        game.hero.attack = 1576;
        game.hero.defense = 835;
        game.hero.gold = 112;
        game.hero.altar_purchases = 21;
        game.hero.yellow_keys = 14;
        game.hero.blue_keys = 3;
        game.hero.red_keys = 5;
        game.hero.sword = EquipmentTier::Knight;
        game.hero.shield = EquipmentTier::Holy;
        game.ending_summary = EndingSummary{game.hero, game.run_history};
        draw(game);
        snapshot("ending-summary-all-achievements");
        std::array<std::uint64_t, 6> cards{};
        for (int i = 0; i < 6; ++i)
            cards[i] = fingerprint(renderer, {32.f + i % 2 * 376, 272.f + i / 2 * 80, 360, 74});
        const Rectangle sword_icon{230, 119, 30, 30}, shield_icon{418, 119, 30, 30};
        const auto sword = fingerprint(renderer, sword_icon), shield = fingerprint(renderer, shield_icon);
        game.hero.sword = game.hero.shield = EquipmentTier::Iron;
        draw(game);
        require(fingerprint(renderer, sword_icon) == sword && fingerprint(renderer, shield_icon) == shield,
                "Ending equipment icons retain the captured sword and shield after live state changes");
        game.ending_summary->hero.sword = game.ending_summary->hero.shield = EquipmentTier::Iron;
        draw(game);
        require(fingerprint(renderer, sword_icon) != sword && fingerprint(renderer, shield_icon) != shield,
                "Ending equipment icons follow the latest obtained tiers instead of fixed Sacred icons");
        game.run_history.complete = false;
        game.ending_summary = EndingSummary{game.hero, game.run_history};
        draw(game);
        snapshot("ending-summary-partial");
        game.hero.zeno_sealed = false;
        game.hero.altar_purchases = 20;
        game.hero.red_keys = 4;
        game.ending_summary = EndingSummary{game.hero, game.run_history};
        draw(game);
        snapshot("ending-summary-empty");
        const auto empty = fingerprint(renderer, {32, 272, 360, 74});
        for (int i = 0; i < 6; ++i) {
            require(cards[i] != empty, "All six earned achievements occupy the same two-column grid");
            require(fingerprint(renderer, {32.f + i % 2 * 376, 272.f + i / 2 * 80, 360, 74}) == empty,
                    "Unverified achievements leave no visible cards or placeholders");
        }
        const auto unknown = fingerprint(renderer, ContentArea);
        game.run_history = {true, true, true, false, true};
        game.ending_summary = EndingSummary{game.hero, game.run_history};
        draw(game);
        require(fingerprint(renderer, ContentArea) == unknown,
                "Unachieved and unverified achievements are both hidden without status labels");
        ui.ending_wait = false;
    }
    {
        renderer.reset();
        Game game;
        draw(game);
        constexpr Rectangle LeftEdge{1, MenuHeight + 2, 12, ContentHeight - 4};
        constexpr Rectangle RightEdge{787, MenuHeight + 2, 12, ContentHeight - 4};
        constexpr Rectangle CenterEdge{157, MenuHeight + 2, 20, ContentHeight - 4};
        const auto left = fingerprint(renderer, LeftEdge), right = fingerprint(renderer, RightEdge);
        const auto center = fingerprint(renderer, CenterEdge);
        snapshot("frontside-panels");
        game.next_cycle();
        draw(game);
        Image original_left = assets.image("data3-leftr");
        Image original_right = assets.image("data3-rightr");
        require(left != fingerprint(renderer, LeftEdge) && right != fingerprint(renderer, RightEdge),
                "Backside switches both side panels to the original red palette");
        require(fingerprint(renderer, LeftEdge) == fingerprint(original_left, {1, 2, 12, 496}) &&
                    fingerprint(renderer, RightEdge) == fingerprint(original_right, {143, 2, 12, 496}),
                "Backside panel edges match the recovered red Data3 artwork");
        require(center == fingerprint(renderer, CenterEdge),
                "Backside preserves the original center frame and board proportions");
        UnloadImage(original_left);
        UnloadImage(original_right);
        snapshot("backside-red-panels");
    }
    {
        renderer.reset();
        Game game;
        game.hero.floor = 50;
        game.hero.x = game.hero.y = 5;
        game.hero.cycle_factor_minus_one = 43;
        game.hero.hp = 10000000;
        game.hero.attack = 100000;
        game.hero.defense = 0;
        game.floors[50].tiles.fill(Road);
        game.tile(50, cell(5, 4)) = Zeno;
        constexpr Rectangle EnemyPanel{656, MenuHeight + 278, 128, 168};
        std::uint64_t previous{};
        for (int variant = 0; variant < 3; ++variant) {
            auto fight = game;
            fight.hero.later_cycle = variant != 0;
            fight.monsters[ZenoRow] =
                variant == 2 ? Monster{800, 500, 100, 500} : Monster{8000, 5000, 1000, 500};
            fight.move(Direction::Up);
            draw(fight);
            const auto panel = fingerprint(renderer, EnemyPanel);
            require(fight.visual.battle_enemy.monster_index == ZenoRow && panel != previous,
                    "50F Zeno variant " + std::to_string(variant) + " renders its own encounter stats");
            previous = panel;
            snapshot(variant == 0   ? "zeno-50f-cycle2"
                     : variant == 1 ? "zeno-50f-later"
                                    : "zeno-50f-resealed");
        }
    }
    {
        renderer.reset();
        Game game;
        const auto directory = output / "slot-fixtures";
        for (int number = 1; number <= 4; ++number) {
            auto saved = game;
            saved.hero.floor = number == 1 ? 10 : 50;
            saved.hero.hp = number == 1 ? 1000 : 12345678;
            saved.hero.attack = number == 1 ? 100 : 10000000;
            saved.hero.defense = number == 1 ? 100 : 10000000;
            saved.hero.cycle_factor_minus_one = number == 1 ? 0 : 43;
            saved.hero.later_cycle = number >= 3;
            saved.save(save_slot_path(directory, number));
        }
        {
            std::ofstream invalid(save_slot_path(directory, 8), std::ios::binary | std::ios::trunc);
            invalid << "damaged";
        }
        ui.save_slots = inspect_save_slots(directory);
        require(ui.save_slots[0].state == SaveSlotState::Ready && ui.save_slots[1].backside &&
                    ui.save_slots[2].later_cycle && ui.save_slots[4].state == SaveSlotState::Empty &&
                    ui.save_slots[7].state == SaveSlotState::Invalid,
                "Save picker receives frontside, backside, later, empty and invalid slot summaries");
        ui.save_picker = SavePicker::Save;
        ui.selected_slot = 5;
        draw(game);
        snapshot("save-slot-picker");
        ui.selected_slot = 2;
        draw(game);
        snapshot("save-slot-replace");
        ui.save_picker = SavePicker::Load;
        ui.autosave_slot = {};
        const auto callback = glfwSetMouseButtonCallback(glfwGetCurrentContext(), nullptr);
        glfwSetMouseButtonCallback(glfwGetCurrentContext(), callback);
        const auto click_autosave = [&] {
            callback(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);
            const auto action = renderer.draw(game, ui, {480, MenuHeight + 460});
            callback(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE, 0);
            renderer.present();
            return action.kind;
        };
        require(click_autosave() == Action::None, "Missing floor autosaves cannot be restored");
        ui.autosave_slot = {SaveSlotState::Ready, 12, 1234, 100, 100};
        require(click_autosave() == Action::LoadAutosave,
                "The load picker restores the independent rolling floor autosave");
        game.dialogue =
            Dialogue{"Dialogue remains paused under the load picker.", ContinuationStage::None, false, {}};
        draw(game);
        const auto with_dialogue = fingerprint(renderer, BoardArea);
        game.dialogue.reset();
        draw(game);
        require(with_dialogue == fingerprint(renderer, BoardArea),
                "Load picker takes precedence over dialogue without changing the underlying save choices");
        snapshot("load-slot-picker");
        ui.selected_slot = 8;
        draw(game);
        snapshot("load-slot-invalid");
        ui.close_overlays();
        require(!ui.modal() && ui.save_picker == SavePicker::None,
                "Closing a save picker releases the modal state for walking and commands");
    }
    {
        renderer.reset();
        Game game;
        game.hero.items.fill(1);
        game.inventory(Item::WarpStaff) = 5;
        game.hero.yellow_keys = 4;
        game.hero.blue_keys = 2;
        game.hero.red_keys = 1;
        renderer.draw(game, ui, {BoardX + 90, BoardY + 10});
        snapshot("items-and-last-enemy");
        ui.inventory = true;
        draw(game);
        snapshot("inventory-overlay");
        ui.inventory = false;
        const auto press_item = [&](Vector2 mouse) {
            auto* window = glfwGetCurrentContext();
            const auto callback = glfwSetMouseButtonCallback(window, nullptr);
            glfwSetMouseButtonCallback(window, callback);
            callback(window, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);
            const auto action = renderer.draw(game, ui, mouse);
            callback(window, GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE, 0);
            renderer.present();
            return action;
        };
        for (int i = 0; i < ItemCount; ++i) {
            const auto item = static_cast<Item>(i);
            const bool orb = item == Item::HeroOrb || item == Item::WisdomOrb || item == Item::FlightOrb;
            const Vector2 sidebar{37.f + i % 3 * 42, MenuHeight + 258.f + i / 3 * 40};
            for (const auto mode : ItemUseModes) {
                ui.item_use_mode = mode;
                const bool direct = orb || (mode == ItemUseMode::OneClick && !item_definition(item).passive);
                for (const bool touch : {false, true}) {
                    ui.touch_controls = touch;
                    for (const bool inventory : {false, true}) {
                        ui.close_overlays();
                        ui.inventory = inventory;
                        const int owned_before = game.inventory(item);
                        const auto action = press_item(
                            inventory ? Vector2{BoardX + 30.f + i / 8 * 204, BoardY + 82.f + i % 8 * 39}
                                      : sidebar);
                        require(!ui.inventory, "Selecting an owned item closes inventory");
                        if (direct)
                            require(
                                action.kind == Action::UseItem && action.value == i && ui.selected_item < 0 &&
                                    !ui.modal(),
                                "Orbs and one-click items dispatch directly with mouse or touch controls");
                        else {
                            require(
                                action.kind == Action::None && ui.selected_item == i &&
                                    game.inventory(item) == owned_before,
                                "Other items open details without use or consumption with mouse or touch");
                            if (!item_definition(item).passive) {
                                require(press_item(sidebar).kind == Action::None && ui.selected_item == i,
                                        "Tapping an item icon again cannot bypass confirmation");
                                const auto confirm = press_item({BoardX + 56, BoardY + 315});
                                require(confirm.kind == Action::UseItem && confirm.value == i,
                                        "The Use button confirms every actionable item with mouse or touch");
                                require(press_item({BoardX + 270, BoardY + 315}).kind == Action::None &&
                                            ui.selected_item < 0 && game.inventory(item) == owned_before,
                                        "Cancel closes confirmation without using or consuming the item");
                            }
                        }
                    }
                }
            }
            ui.item_use_mode = ItemUseMode::Confirm;
            ui.touch_controls = false;
            ui.close_overlays();
            if (!orb)
                ui.selected_item = i;
            renderer.draw(game, ui, sidebar);
            snapshot("item-" + std::to_string(i));
        }
        ui.close_overlays();
        game.push(Op::Wait);
        require(press_item({37, MenuHeight + 258}).kind == Action::None && ui.selected_item < 0,
                "Busy gameplay blocks immediate item use from the sidebar");
        ui.inventory = true;
        require(press_item({BoardX + 30, BoardY + 82}).kind == Action::None && ui.inventory,
                "Busy gameplay blocks immediate item use from inventory");
        ui.close_overlays();
        ui.selected_item = int(Item::Bomb);
        require(press_item({BoardX + 56, BoardY + 315}).kind == Action::None &&
                    ui.selected_item == int(Item::Bomb),
                "Busy gameplay disables the item confirmation button");
        game.finish_commands();
        game.inventory(Item::Bomb) = 0;
        require(press_item({BoardX + 56, BoardY + 315}).kind == Action::None,
                "Unavailable items cannot be confirmed");
        game.inventory(Item::Bomb) = 1;
        ui.touch_controls = true;
        draw(game);
        snapshot("touch-item-confirmation");
        const auto confirmation = fingerprint(renderer, {BoardX + 38, BoardY + 210, 364, 80});
        ui.item_use_mode = ItemUseMode::Describe;
        draw(game);
        require(fingerprint(renderer, {BoardX + 38, BoardY + 210, 364, 80}) != confirmation,
                "Description mode adds the item explanation to the confirmation panel");
        snapshot("touch-item-description");
        ui.item_use_mode = ItemUseMode::Confirm;
        ui.touch_controls = false;
        ui.close_overlays();
        game.inventory(Item::HeroOrb) = 0;
        ui.inventory = true;
        require(press_item({BoardX + 30, BoardY + 82}).kind == Action::None && ui.inventory,
                "Missing items cannot be used from inventory");
        game.inventory(Item::HeroOrb) = 1;
        ui.close_overlays();
        ui.replay_active = true;
        require(press_item({37, MenuHeight + 258}).kind == Action::None && ui.selected_item < 0,
                "Replay playback blocks immediate item use");
        ui.replay_active = false;
        game.hero.hp = 2147483647;
        game.hero.attack = game.hero.defense = game.hero.gold = 10000000;
        draw(game);
        snapshot("large-stat-values");
        game.new_game();
        ui.flight = 5;
        draw(game);
        snapshot("flight-preview");
        ui.flight = -1;
        ui.help = true;
        draw(game);
        snapshot("help-overlay");
        ui.close_overlays();
        game.hero.gold = 100;
        game.hero.x = game.hero.y = 5;
        game.tile(1, cell(5, 4)) = Altar;
        game.move(Direction::Up);
        draw(game);
        require(game.dialogue && game.dialogue->shop, "Shop choices render from an actual core offer");
        snapshot("shop-overlay");
        game.choose(-1);
        game.finish_commands();
        game.inventory(Item::WisdomOrb) = 1;
        game.hero.wisdom_hints.fill(HintState::Recorded);
        game.use(Item::WisdomOrb);
        ui.dialogue_scroll = 200;
        draw(game);
        require(ui.dialogue_scroll == 200, "Long Wisdom passages retain scrolling");
        snapshot("wisdom-scroll");
    }
    {
        Game game;
        ui.close_overlays();
        ui.rankings = true;
        ui.ranking_category = 1;
        ui.ranking_entry_category = 1;
        ui.ranking_position = 1;
        ui.ranking_entry = RankingEntry{415, 1000, 100, 100, {}};
        ui.ranking_name = "Hero";
        const auto before = game.rankings;
        draw(game);
        require(ui.modal(), "Ranking entry pauses gameplay while a name is entered");
        require(game.rankings == before, "Rendering a ranking entry does not submit or reset scores");
        snapshot("ranking-entry");
        ui.ranking_category = 5;
        ui.ranking_reset_confirmation = true;
        draw(game);
        snapshot("ranking-reset-confirmation");
        ui.close_overlays();
        require(!ui.ranking_entry && !ui.rankings, "Closing rankings cancels the pending entry");
    }
    std::ofstream report(output / "presentation-report.json");
    report << "{\n  \"passed\": " << checks.size() << ",\n  \"checks\": [\n";
    for (std::size_t i = 0; i < checks.size(); ++i)
        report << "    \"" << checks[i] << "\"" << (i + 1 < checks.size() ? "," : "") << '\n';
    report << "  ],\n  \"limits\": \"Renderer frame checks and screenshots; no pixel comparison with Delphi "
              "or timer equivalence claim.\"\n}\n";
    std::cout << checks.size() << " presentation checks passed; snapshots: " << output << '\n';
    return 0;
}

int verify_window(Presentation& renderer, const std::filesystem::path& output) {
    std::filesystem::create_directories(output);
    Game game;
    DesktopUi ui;
    std::ofstream report(output / "window-report.json");
    report << "{\n  \"sizes\": [\n";
    auto* native_window = glfwGetCurrentContext();
    const auto cursor = glfwSetCursorPosCallback(native_window, nullptr);
    glfwSetCursorPosCallback(native_window, cursor);
    const auto button = glfwSetMouseButtonCallback(native_window, nullptr);
    glfwSetMouseButtonCallback(native_window, button);
    bool first = true;
    const auto check = [&](const char* name) {
        // Render both swap buffers after the native resize notification settles.
        for (int frame = 0; frame < 12; ++frame) {
            renderer.draw(game, ui, {-1, -1});
            renderer.present();
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        const auto view = window_viewport();
        const auto& area = view.area;
        if (area.width <= 0 || area.height <= 0 || area.x < -.01f || area.y < -.01f ||
            std::abs(area.width / area.height - float(CanvasWidth) / CanvasHeight) > .001f)
            throw std::runtime_error("Invalid window canvas bounds");
        const auto point = [&](Vector2 target) {
            // Feed the real input callback without moving the system cursor. The pure
            // viewport inverse alone cannot detect raylib applying an extra DPI scale.
            cursor(native_window, area.x + target.x * area.width / CanvasWidth,
                   area.y + target.y * area.height / CanvasHeight);
            const auto mapped = renderer.mouse_position();
            if (std::abs(mapped.x - target.x) > .01f || std::abs(mapped.y - target.y) > .01f)
                throw std::runtime_error(std::string("Window pointer mapping differs from canvas after ") +
                                         name);
            return mapped;
        };
        for (const Vector2 target :
             std::array<Vector2, 7>{{{1, 1},
                                     {CanvasWidth - 1, CanvasHeight - 1},
                                     {109, 14},
                                     {BoardX + .5f * TileSize, BoardY + .5f * TileSize},
                                     {BoardX + 10.5f * TileSize, BoardY + .5f * TileSize},
                                     {BoardX + .5f * TileSize, BoardY + 10.5f * TileSize},
                                     {BoardX + 10.5f * TileSize, BoardY + 10.5f * TileSize}}})
            point(target);
        const auto click = [&](Vector2 target) {
            const auto mouse = point(target);
            button(native_window, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);
            const auto action = renderer.draw(game, ui, mouse);
            button(native_window, GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE, 0);
            return action;
        };
        click({109, 14});
        if (ui.menu != Menu::Options)
            throw std::runtime_error("Window click missed the visible Options button");
        ui.close_overlays();
        ui.mouse_walking = true;
        const auto walk = click({BoardX + 8.5f * TileSize, BoardY + 5.5f * TileSize});
        if (walk.kind != Action::WalkTo || walk.value != cell(8, 5))
            throw std::runtime_error("Window click selected the wrong map tile");
        for (const Vector2 outside : std::array<Vector2, 4>{{{BoardX - 1, BoardY},
                                                             {BoardX, BoardY - 1},
                                                             {BoardX + BoardPixels, BoardY},
                                                             {BoardX, BoardY + BoardPixels}}})
            if (mouse_destination(game, ui, point(outside)))
                throw std::runtime_error("Window pointer outside the board selected a map tile");
        ui.mouse_walking = false;
        renderer.draw(game, ui, {-1, -1});
        renderer.present();
        Image canvas = renderer.capture_canvas(), window = renderer.capture_window();
        Image native = renderer.capture_native_canvas();
        const int expected_width = int(std::round(area.width * view.framebuffer_width / view.window_width));
        const int expected_height =
            int(std::round(area.height * view.framebuffer_height / view.window_height));
        if (native.width != expected_width || native.height != expected_height)
            throw std::runtime_error("Canvas was not rasterized at the display resolution");
        auto* expected = LoadImageColors(canvas);
        auto* actual = LoadImageColors(window);
        auto* native_pixels = LoadImageColors(native);
        int text_detail = 0;
        // Enlarged text must contain detail within each old logical pixel. A stretched
        // 800x558 canvas cannot pass this check, even if its window viewport is correct.
        const float sx = native.width / float(CanvasWidth), sy = native.height / float(CanvasHeight);
        for (int y = int(5 * sy); y < int(22 * sy); ++y)
            for (int x = int(8 * sx); x < int(61 * sx); ++x) {
                const auto value = native_pixels[y * native.width + x];
                const auto coarse = expected[int(y / sy) * CanvasWidth + int(x / sx)];
                if (value.r > 150 && value.g > 140 && value.b > 130)
                    text_detail += std::abs(int(value.r) - coarse.r) > 8;
            }
        if (sx > 2 && sy > 2 && text_detail < 40)
            throw std::runtime_error("Enlarged menu text has no native-resolution glyph detail");
        bool pixels_match = true;
        int compared = 0;
        // Compare flat neighborhoods throughout the logical canvas. This checks the
        // physical viewport/projection without depending on fractional texture filtering.
        for (int y = 8; y < CanvasHeight - 8; y += 19)
            for (int x = 8; x < CanvasWidth - 8; x += 23) {
                const auto reference = expected[y * CanvasWidth + x];
                bool flat = true;
                for (int dy = -2; dy <= 2; ++dy)
                    for (int dx = -2; dx <= 2; ++dx) {
                        const auto neighbor = expected[(y + dy) * CanvasWidth + x + dx];
                        flat &= neighbor.r == reference.r && neighbor.g == reference.g &&
                                neighbor.b == reference.b;
                    }
                if (!flat)
                    continue;
                const int px =
                    int((area.x + (x + .5f) * area.width / CanvasWidth) * window.width / view.window_width);
                const int py = int((area.y + (y + .5f) * area.height / CanvasHeight) * window.height /
                                   view.window_height);
                const auto value = actual[py * window.width + px];
                pixels_match &= std::abs(int(value.r) - reference.r) <= 2 &&
                                std::abs(int(value.g) - reference.g) <= 2 &&
                                std::abs(int(value.b) - reference.b) <= 2;
                ++compared;
            }
        ExportImage(window, (output / (std::string(name) + ".png")).string().c_str());
        UnloadImageColors(expected);
        UnloadImageColors(actual);
        UnloadImageColors(native_pixels);
        UnloadImage(canvas);
        UnloadImage(window);
        UnloadImage(native);
        if (!pixels_match || compared < 20)
            throw std::runtime_error(std::string("Framebuffer does not match canvas after ") + name);
        if (!first)
            report << ",\n";
        first = false;
        report << "    {\"name\": \"" << name << "\", \"window\": [" << view.window_width << ','
               << view.window_height << "], \"framebuffer\": [" << view.framebuffer_width << ','
               << view.framebuffer_height << "], \"canvas\": [" << expected_width << ',' << expected_height
               << "], \"native_text_detail\": " << text_detail << ", \"pixels_compared\": " << compared
               << '}';
        return view;
    };
    SetWindowSize(CanvasWidth, CanvasHeight);
    check("initial");
    SetWindowSize(1200, 700);
    check("wide");
    SetWindowSize(640, 700);
    check("tall");
    SetWindowSize(CanvasWidth, CanvasHeight);
    check("resize-back");
    MaximizeWindow();
    const auto maximized = check("maximized");
    RestoreWindow();
    const auto restored = check("restored");
    // Windows may apply a different monitor DPI when restoring. The canvas must
    // fit the new native dimensions, rather than retaining the maximized scale.
    if (restored.window_width >= maximized.window_width || restored.window_height >= maximized.window_height)
        throw std::runtime_error("Restore retained the maximized window size");
    report << "\n  ],\n  \"passed\": 6\n}\n";
    std::cout
        << "Six window layouts passed: resize, maximize, restore, framebuffer pixels and pointer mapping\n";
    return 0;
}
} // namespace tsw
