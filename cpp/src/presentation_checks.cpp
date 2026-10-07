#include "audio.hpp"
#include "presentation.hpp"
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
    Image expected = ImageFromImage(atlas, cell(Road));
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
            draw(game);
            require(matches_original_hero(renderer, target, atlas, WalkingTiles[facing - 1]),
                    "Direction " + std::to_string(facing) + " begins with the original first walking pose");
            renderer.advance(WalkAnimationSeconds * .6f);
            draw(game);
            require(matches_original_hero(renderer, target, atlas, WalkingTiles[facing - 1] + 2),
                    "Direction " + std::to_string(facing) + " advances to the original second walking pose");
            renderer.advance(WalkAnimationSeconds);
            draw(game);
            require(matches_original_hero(renderer, target, atlas, IdleTiles[facing - 1]),
                    "Direction " + std::to_string(facing) + " returns to the original standing pose");
            snapshot("idle-direction-" + std::to_string(facing));
        }
        UnloadImage(atlas);
        std::array<int, 3> counts{};
        for (int speed = 0; speed < 3; ++speed) {
            WalkRepeat walking;
            for (int frame = 0; frame < 120; ++frame) {
                walking.advance(GameSpeeds[speed] / 60.f);
                if (walking.ready(false, true)) {
                    ++counts[speed];
                    walking.stepped();
                }
            }
            require(!walking.ready(false, false) && walking.ready(true, true),
                    "Walking speed " + std::to_string(speed) + " waits for input and accepts a fresh tap");
        }
        require(counts[1] >= 2 * counts[0] && counts[2] >= 5 * counts[0],
                "3x and 10x game speed accelerate held walking through the same scaled clock");
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
        require(game.visual.last_defeated && game.visual.last_defeated->row == 0,
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
        require(ui.enemy_first_row == 0 && game.visual.last_defeated->row == 0,
                "An empty Hero Orb overlay resets scrolling without erasing the last victory");
        snapshot("hero-orb-empty");
        ui.close_overlays();
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
        require(frames == 32 && first != middle && middle != last && game.visual.raster_mode == -1,
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
                if (game.visual.raster_mode == 9 || game.visual.raster_mode == 0 ||
                    game.visual.raster_mode == 1)
                    capture_music = capture_music && Audio::track_for_scene(game) == 11;
                if (command.a == int(Callback::HidePanels)) {
                    title = fingerprint(renderer, ContentArea);
                    snapshot("capture-title");
                }
                if (command.a == int(Callback::RasterScene)) {
                    if (game.visual.raster_mode == 0) {
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
                    } else if (game.visual.raster_mode == 1) {
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
        require(game.hero.floor == 2 && game.hero.hp == 400 && game.visual.raster_mode == -1,
                "Capture compositor returns to the prison without changing the gameplay outcome");
        require(capture_music && Audio::track_for_scene(game) == game.hero.music_track,
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
                const int mode = game.visual.raster_mode;
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
                        draw(game);
                        snapshot("ending-wait");
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
        require(game.hero.cycle_factor_minus_one == BacksideFactor - 1 && game.visual.raster_mode == -1,
                "Ending returns to the playable backside tower");
        draw(game);
        snapshot("ending-backside");
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
            require(fight.visual.battle_enemy.row == ZenoRow && panel != previous,
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
        game.dialogue = Dialogue{"Dialogue remains paused under the load picker.", 0, false, {}};
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
        for (int i = 0; i < 15; ++i) {
            ui.selected_item = i;
            draw(game);
            snapshot("item-" + std::to_string(i));
        }
        ui.close_overlays();
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
        game.hero.wisdom_hints.fill(2);
        game.use(Item::WisdomOrb);
        ui.dialogue_scroll = 200;
        draw(game);
        require(ui.dialogue_scroll == 200, "Long Wisdom passages retain scrolling");
        snapshot("wisdom-scroll");
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
        const Vector2 target{BoardX + 5.5f * TileSize, BoardY + 10.5f * TileSize};
        const auto mapped = view.canvas_point(
            {area.x + target.x * area.width / CanvasWidth, area.y + target.y * area.height / CanvasHeight});
        if (std::abs(mapped.x - target.x) > .01f || std::abs(mapped.y - target.y) > .01f)
            throw std::runtime_error("Window pointer mapping differs from canvas scaling");
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
