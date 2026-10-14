#pragma once
#include "assets.hpp"
#include "raylib.h"
#include "tsw/game.hpp"
#include "tsw/mouse_walk.hpp"
#include "tsw/save_slots.hpp"
#include "tsw/settings.hpp"
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
    Language language = Language::English;
    int flight = -1, selected_item = -1, speed_index{}, enemy_first_row{};
    int selected_slot = 1;
    SavePicker save_picker = SavePicker::None;
    SaveSlots save_slots;
    bool inventory{}, enemies{}, help{}, muted{}, ending_wait{}, hero_orb_actual_damage{};
    bool recording_enabled{}, recording_active{};
    bool mouse_walking{};
    bool home{}, game_started = true, replay_picker{}, replay_active{}, replay_paused{}, replay_in_progress{};
    bool quick_available{}, fairy_available{};
    int home_selection = 1, replay_speed_index = 2, replay_selected{}, replay_first_row{};
    std::size_t replay_step{}, replay_count{};
    std::vector<std::filesystem::path> replay_files;
    std::string replay_path, replay_name, replay_error, notice;
    bool rankings{}, ranking_reset_confirmation{};
    int ranking_category = 1, ranking_entry_category{}, ranking_position{};
    std::optional<RankingEntry> ranking_entry;
    std::string ranking_name;
    bool replay_path_focus = true;
    Menu menu = Menu::None;
    float dialogue_scroll{};

    bool modal() const {
        return home || replay_picker || rankings || inventory || enemies || help || selected_item >= 0 ||
               menu != Menu::None || save_picker != SavePicker::None;
    }

    bool file_controls_enabled() const { return flight < 0 && !enemies && selected_item < 0; }

    void close_overlays() {
        inventory = enemies = help = false;
        selected_item = -1;
        menu = Menu::None;
        save_picker = SavePicker::None;
        replay_picker = false;
        rankings = ranking_reset_confirmation = false;
        ranking_entry.reset();
        ranking_name.clear();
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
    Speed,
    Recording,
    HeroOrbActualDamage,
    Language,
    MainMenu,
    ResumeGame,
    OpenSettings,
    OpenRankings,
    RankingCategory,
    SubmitRanking,
    ResetRankings,
    OpenReplays,
    PlayReplay,
    ReplayPause,
    ReplayPrevious,
    ReplayNext,
    ReplayRestart,
    ReplayTakeOver,
    ReplaySpeed,
    WalkTo,
    MouseWalking
};

struct UiAction {
    Action kind = Action::None;
    int value{};
};

inline constexpr float WalkRepeatSeconds = MouseWalk::StepSeconds, WalkAnimationSeconds = .12f;

std::optional<int> mouse_destination(const Game&, const DesktopUi&, Vector2 mouse);

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
    float animation_seconds_{};
    void draw_board(const Game&, int floor, bool animated);
    void draw_door(const Game&, int x, int y);
    void draw_transformation(const Game&, int animation);
    void draw_scene(const Game&);
    void cache_scene();
    void resize_canvas(const CanvasViewport&);
    UiAction draw_panels(const Game&, DesktopUi&, Vector2 mouse);
    UiAction draw_dialogue(const Game&, DesktopUi&, Vector2 mouse);
    UiAction draw_inventory(const Game&, DesktopUi&, Vector2 mouse);
    void draw_enemies(const Game&, DesktopUi&, Vector2 mouse);
    void draw_qol_status(const DesktopUi&, Rectangle, Vector2 mouse);
    UiAction draw_item(const Game&, DesktopUi&, Vector2 mouse);
    UiAction draw_menu(const Game&, DesktopUi&, Vector2 mouse);
    UiAction draw_save_slots(const Game&, DesktopUi&, Vector2 mouse);
    UiAction draw_home(const DesktopUi&, Vector2 mouse);
    UiAction draw_replays(DesktopUi&, Vector2 mouse);
    UiAction draw_rankings(const Game&, DesktopUi&, Vector2 mouse);
    UiAction draw_replay_controls(const DesktopUi&, Vector2 mouse);
    void draw_help(DesktopUi&, Vector2 mouse);
};

float command_interval(const Game&);
} // namespace tsw
