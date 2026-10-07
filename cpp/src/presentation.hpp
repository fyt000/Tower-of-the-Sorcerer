#pragma once
#include "assets.hpp"
#include "raylib.h"
#include "tsw/game.hpp"
#include "tsw/save_slots.hpp"
#include <filesystem>
#include <memory>

namespace tsw {
inline constexpr int CanvasWidth = 800, ContentHeight = 500, MenuHeight = 28, StatusHeight = 30;
inline constexpr int CanvasHeight = MenuHeight + ContentHeight + StatusHeight;
inline constexpr int TileSize = 40, BoardPixels = BoardWidth * TileSize;
inline constexpr int BoardX = 180, BoardY = MenuHeight + 30;

struct CanvasViewport {
    int window_width{}, window_height{}, framebuffer_width{}, framebuffer_height{};
    Rectangle area{};
    Vector2 canvas_point(Vector2 point) const {
        return {(point.x - area.x) * CanvasWidth / area.width,
                (point.y - area.y) * CanvasHeight / area.height};
    }
};
CanvasViewport window_viewport();

enum class Menu { None, Game, Options };
enum class SavePicker { None, Save, Load };
struct DesktopUi {
    int flight = -1, selected_item = -1, speed_index{}, enemy_first_row{};
    int selected_slot = 1;
    SavePicker save_picker = SavePicker::None;
    SaveSlots save_slots;
    bool inventory{}, enemies{}, help{}, muted{}, ending_wait{};
    Menu menu = Menu::None;
    float dialogue_scroll{};
    bool modal() const {
        return inventory || enemies || help || selected_item >= 0 || menu != Menu::None ||
               save_picker != SavePicker::None;
    }
    void close_overlays() {
        inventory = enemies = help = false;
        selected_item = -1;
        menu = Menu::None;
        save_picker = SavePicker::None;
    }
};
enum class Action {
    None,
    NewGame,
    Save,
    Load,
    OpenSaveSlots,
    OpenLoadSlots,
    SaveSlot,
    LoadSlot,
    FairyCheckpoint,
    Continue,
    ContinueEnding,
    Choose,
    UseItem,
    FlightUp,
    FlightDown,
    Travel,
    CancelFlight,
    Mute,
    Speed
};
struct UiAction {
    Action kind = Action::None;
    int value{};
};
inline constexpr std::array<float, 3> GameSpeeds{1, 3, 10};
inline constexpr float WalkRepeatSeconds = .14f, WalkAnimationSeconds = .12f;
struct WalkRepeat {
    float remaining{};
    void advance(float seconds) { remaining -= seconds; }
    bool ready(bool pressed, bool held) const { return pressed || (held && remaining <= 0); }
    void stepped() { remaining = WalkRepeatSeconds; }
};

// Owns raylib resources. Gameplay and save files never depend on this class.
class Presentation {
  public:
    explicit Presentation(const Assets& assets);
    ~Presentation();
    Presentation(const Presentation&) = delete;
    Presentation& operator=(const Presentation&) = delete;
    Vector2 mouse_position() const;
    void moved(const Hero& before, const Hero& after);
    void advance(float seconds);  // The same scaled clock as walking input and commands.
    void command(const Command&); // Original rendering callbacks, after run_one().
    void reset();
    UiAction draw(const Game&, DesktopUi&, Vector2 mouse);
    void present() const;
    bool screenshot(const std::filesystem::path&) const;
    Image capture_canvas() const;        // Logical pixels, independent of desktop DPI.
    Image capture_native_canvas() const; // Canvas rasterized at the displayed pixel resolution.
    Image capture_window() const;        // Actual framebuffer, including letterboxing.

  private:
    struct Art;
    std::unique_ptr<Art> art_;
    RenderTexture2D canvas_{}, scene_cache_{};
    Shader dissolve_{};
    int dissolve_mask_location_{}, previous_raster_ = -1;
    bool hide_panels_{}, cache_requested_{}, cache_valid_{};
    float walking_remaining_{};
    void draw_board(const Game&, int floor, bool animated);
    void draw_door(const Visual&, int x, int y);
    void draw_transformation(const Game&, int animation);
    void draw_scene(const Game&);
    void cache_scene();
    void resize_canvas(const CanvasViewport&);
    UiAction draw_panels(const Game&, DesktopUi&, Vector2 mouse);
    UiAction draw_dialogue(const Game&, DesktopUi&, Vector2 mouse);
    UiAction draw_inventory(const Game&, DesktopUi&, Vector2 mouse);
    void draw_enemies(const Game&, DesktopUi&, Vector2 mouse);
    UiAction draw_item(const Game&, DesktopUi&, Vector2 mouse);
    UiAction draw_menu(const Game&, DesktopUi&, Vector2 mouse);
    UiAction draw_save_slots(const Game&, DesktopUi&, Vector2 mouse);
    void draw_help(DesktopUi&, Vector2 mouse);
};
float command_interval(const Game&);
} // namespace tsw
