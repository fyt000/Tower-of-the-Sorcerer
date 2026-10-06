#pragma once
#include <array>
#include <cstdint>
#include <filesystem>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace baseline {
inline constexpr int BoardWidth = 11;
inline constexpr int CellCount = BoardWidth * BoardWidth;
inline constexpr int FloorCount = 51;
inline constexpr int BacksideFactor = 44;
constexpr int cell(int x, int y) {
    return y * BoardWidth + x;
}

// Values are the original atlas/map IDs. They are kept stable for source comparison.
enum Tile : std::uint8_t {
    Void = 0,
    YellowDoor = 1,
    BlueDoor = 2,
    RedDoor = 3,
    SealedGate = 4,
    PrisonGate = 5,
    Road = 6,
    SpecialRoad = 7,
    Wall = 8,
    SecretWall = 9,
    HiddenObject = 10,
    StairsUp = 11,
    StairsDown = 12,
    Lava = 13,
    StarVoid = 14,
    SolidDecoration = 15,
    Altar = 16,
    AltarTop = 17,
    AltarSide = 18,
    Merchant = 19,
    Merchant2 = 20,
    Thief = 21,
    Thief2 = 22,
    Fairy = 23,
    Fairy2 = 24,
    OldMan = 25,
    OldMan2 = 26,
    TimeGate = 27,
    TimeGate2 = 28,
    YellowKey = 29,
    RedKey = 30,
    BlueKey = 31,
    RedPotion = 32,
    BluePotion = 33,
    RedGem = 34,
    BlueGem = 35,
    HeroOrb = 36,
    WisdomOrb = 37,
    FlightOrb = 38,
    Cross = 39,
    Elixir = 40,
    Mattock = 41,
    Bomb = 42,
    WarpStaff = 43,
    AscentWing = 44,
    DescentWing = 45,
    DragonSlayer = 46,
    SnowCrystal = 47,
    MagicKey = 48,
    SuperMattock = 49,
    LuckyGold = 50,
    IronSword = 51,
    SilverSword = 52,
    KnightSword = 53,
    HolySword = 54,
    SacredSword = 55,
    IronShield = 56,
    SilverShield = 57,
    KnightShield = 58,
    HolyShield = 59,
    SacredShield = 60,
    GreenSlime = 61,
    RedSlime = 63,
    BigSlime = 65,
    Bat = 67,
    Priest = 69,
    SuperionPriest = 71,
    GateKeeperC = 73,
    GateKeeperB = 75,
    SkeletonC = 77,
    SkeletonB = 79,
    SkeletonA = 81,
    BigBat = 83,
    Zombie = 85,
    ZombieKnight = 87,
    Rock = 89,
    Zeno = 91,
    Sorcerer = 93,
    Vampire = 95,
    OctopusFirst = 97,
    OctopusMouth = 104,
    DragonFirst = 115,
    DragonHead = 122,
    GoldenKnight = 133,
    Knight = 135,
    Swordsman = 137,
    Soldier = 139,
    GhostSoldier = 141,
    SlimeMan = 143,
    GreatMagicMaster = 145,
    VampireBat = 147,
    SlimeLord = 149,
    MagicianA = 151,
    MagicianB = 153,
    DarkKnight = 155,
    GateKeeperA = 157,
    StairCover = 159
};
inline constexpr int HeroHitMask = 183, HeroHitColor = 184;
inline constexpr int DownDamageColor = 191, FacingSpriteStride = 8;
inline constexpr int DissolveFirstMask = 166, DissolveLastMask = 182;
inline constexpr int ZombieRow = 12, ZombieKnightRow = 13, ZenoRow = 15;
inline constexpr int VampireRow = 17, OctopusRow = 18, DragonRow = 19;
inline constexpr int SacredShieldFlag = 9;
enum class TileClass : int { Other, Wall, BombTarget, Lava };
enum class Direction : int { Down = 1, Left = 2, Right = 3, Up = 4 };
enum class Item : int {
    HeroOrb,
    WisdomOrb,
    FlightOrb,
    Cross,
    Elixir,
    Mattock,
    Bomb,
    WarpStaff,
    AscentWing,
    DescentWing,
    DragonSlayer,
    SnowCrystal,
    MagicKey,
    SuperMattock,
    LuckyGold
};
// Three 16-bit words, as in the Delphi command stack. Operand interpretation depends on op.
enum class Op : std::uint16_t {
    Wait,
    Sound,
    Message,
    Defeat,
    EnemyStrike,
    HeroStrike,
    SetTile,
    Reward,
    UpdateInventory,
    Overlay,
    Dialogue,
    Callback,
    MoveTile,
    DoorFrame,
    LargeMonsterStrike,
    FloorMusic,
    HpDelta,
    WriteTile,
    MovementFrame,
    PincerDamage,
    SetHeroValue,
    StairFrame,
    DeathScene
};
enum class Callback : int {
    Capture = 1,
    SummonZeno,
    SummonGuards,
    Transformation,
    CheckGuards,
    NextCycle,
    Title,
    RestoreBoard,
    BattleEnd,
    ForcedBattle,
    Teleport,
    RasterScene,
    HideHero,
    HidePanels,
    CacheScene
};
enum class DoorMotion : int {
    Yellow = 1,
    Blue,
    Red,
    OpenGate,
    CloseGate,
    Prison,
    LowerWall,
    RaiseWall,
    RoadFromRight,
    RoadFromLeft,
    RoadFromTop,
    RoadFromBottom
};
enum class SoundCue : int {
    Open = 1,
    Get,
    Strike,
    Zeno,
    MusicStart,
    MusicStop,
    Floor3,
    Floor20,
    Stairs,
    Stairs2
};
struct Command {
    Op op{};
    std::uint16_t a{}, b{};
    friend bool operator==(const Command&, const Command&) = default;
};
struct Monster {
    std::int32_t hp{}, attack{}, defense{}, gold{};
};
struct EnemyInfo {
    int row = -1, tile{};
    Monster stats; // Encounter-time values, including the current cycle's scaling.
    std::int64_t damage{};
};
struct Floor {
    std::uint8_t up_landing{}, down_landing{};
    std::array<std::uint8_t, CellCount> tiles{};
};
struct Hero {
    std::int32_t hp = 1000, attack = 100, defense = 100, gold = 0;
    int floor = 1, highest_floor = 1, x = 5, y = 10;
    int yellow_keys{}, red_keys{}, blue_keys{}, altar_purchases{}, fairy_visits{};
    int sword = 5, shield = 5;
    std::array<int, 15> items{};
    std::array<int, 10> equipment_found{0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
    std::array<int, 68> dialogue_seen{};
    std::array<int, 24> wisdom_hints{};
    bool floor34_reward_created{}, floor35_reward_created{}, floor40_reward_created{},
        floor41_reward_created{};
    bool floor32_arrival_seen{}, zeno_sealed{};
    std::array<int, 3> old_man_heard{}; // Original hint slots 66, 67 and 71.
    int merchant2_heard{};
    std::array<int, 12> merchant_used{};
    int cycle_factor_minus_one{}, later_cycle{};
    Direction facing = Direction::Up;
    int music_track = 5;
    int flight_direction{}, highest_floor_stair{};
    int fairy_score{}, fairy_rank{}, fairy_category{};
};
struct Dialogue {
    std::string text;
    int continuation{};
    bool shop{};
    std::array<std::string, 3> choices{};
};
struct Visual {
    struct Layer {
        int mask{}, color{}, underlying = -1;
    };
    std::array<Layer, CellCount> layers{};
    int overlay_cell = -1, mask{}, color{}, underlying = Road;
    int door_cell = -1, door_mode{}, door_frame{}, door_tile{};
    int raster_mode = -1, raster_frame{};
    bool hide_hero{}, battle{}, dead{}, enemy_first{};
    int enemy_hp{}, enemy_index = -1;
    EnemyInfo battle_enemy;
    std::optional<EnemyInfo> last_defeated;
    std::array<bool, CellCount> stair_cover{};
    int stair_source_floor = -1;
    int stair_hero_x{}, stair_hero_y{};
    Direction stair_hero_facing = Direction::Up;
    bool stair_revealing{};
    Floor stair_source{};
};
struct Forecast {
    bool penetrates{};
    std::int64_t damage{};
    std::int64_t hero_hits{};
    int hero_hit{}, enemy_hit{};
};

class Game {
  public:
    Hero hero;
    std::array<Floor, FloorCount> floors{};
    std::array<Monster, 33> monsters{};
    std::vector<Command> commands; // Insertion order; back() executes first.
    std::optional<Dialogue> dialogue;
    Visual visual;
    std::string status;
    std::vector<SoundCue> sounds;
    bool checkpoint_requested{};
    Game();
    void new_game();
    bool move(Direction);
    bool use(Item, int destination_floor = -1);
    bool continue_dialogue();
    bool choose(int choice);
    bool run_one(Command* executed = nullptr); // One command, never a recursive timer call.
    void finish_commands(bool continue_speech = false);
    bool busy() const;
    int& inventory(Item item) { return hero.items.at(static_cast<int>(item)); }
    int inventory(Item item) const { return hero.items.at(static_cast<int>(item)); }
    std::uint8_t& tile(int floor, int index) { return floors.at(floor).tiles.at(index); }
    std::uint8_t tile(int floor, int index) const { return floors.at(floor).tiles.at(index); }
    std::uint8_t& tile_at(int floor, int x, int y) { return tile(floor, cell(x, y)); }
    std::uint8_t tile_at(int floor, int x, int y) const { return tile(floor, cell(x, y)); }
    Forecast forecast(int tile_id, bool enemy_first = false) const;
    static int monster_for_tile(int tile_id);
    static TileClass classify_tile(int tile_id);
    static int animation_offset(int tile_id);
    static std::string_view item_name(Item);
    static std::string_view monster_name(int index);
    static std::string_view original_dialogue(int id);
    void push(Op op, int a = 0, int b = 0);
    void push(Op op, Callback a, int b = 0) { push(op, static_cast<int>(a), b); }
    void push(Op op, SoundCue a, int b = 0) { push(op, static_cast<int>(a), b); }
    void push(Op op, int a, DoorMotion b) { push(op, a, static_cast<int>(b)); }
    void waits(int count) {
        for (int i = 0; i < count; ++i)
            push(Op::Wait);
    }
    void expand_door();
    void check_guards(); // 0x4664E4, including original numeric-sum predicates.
    void check_floor();  // 0x46CB1C, recovered two-level switch.
    void check_door();   // 0x47BEAC, called even when key contact is refused.
    void special_road(); // 0x46397C.
    void contact();      // 0x444490.
    void battle(bool enemy_first = false);
    void capture();
    void next_cycle();
    void save(const std::filesystem::path&) const;
    void load(const std::filesystem::path&);
    bool flight_preview(int destination_floor, int direction = 1);
    // Exposed state inputs for original-machine differential probes.
    int contact_index{}, scratch_index{}, neighbor_index{}, message_code{}, door_opened{};

  private:
    struct Fight {
        int target{}, enemy{}, hero_hits{}, enemy_hits{}, turn{}, underlying{};
        bool fatal{}, enemy_first{};
        std::size_t base_commands{};
    };
    std::optional<Fight> fight_;
    int shop_kind_{}, shop_cost_{}, shop_hint_{}, shop_id_{}, shop_npc_cell_{};
    bool stopped_{};
    void walk_to_contact();
    void stair(bool up);
    void face_away_from_stair(bool climbed);
    void hazard(int magician_cell, int retreat_cell);
    void damage_pose(int cell_index, int underlying = -1);
    void summon(int cell_index, int color);
    void summon_guards();
    void summon_four_guards(int north, int south, int west, int east);
    void transform_vampire();
    void show_dialogue(int one_based_id);
    void speak_old_man();
    void speak_merchant();
    void speak_thief();
    void speak_fairy();
    void continue_original(int stage);
    void bomb_dissolve(int cell_index);
    void battle_step();
    void battle_finished(const Fight&);
    int attack_multiplier(int enemy, bool enemy_first) const;
    void initialize_cycle();
    void update_status(int code);
    void change_music_for_floor();
    void ending();
    void queue_death();
};
} // namespace baseline
