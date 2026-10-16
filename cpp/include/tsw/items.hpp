#pragma once
#include <array>
#include <optional>
#include <string_view>
#include <utility>

namespace tsw {
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
inline constexpr int ItemCount = 15;

struct ItemDefinition {
    std::string_view id, name;
    bool passive;
    std::string_view description, usage;
};

// Array order is the saved inventory order and replay/MCP wire contract.
inline constexpr std::array<ItemDefinition, ItemCount> ItemDefinitions{{
    {"hero_orb", "Orb of the Hero", false,
     "Inspect enemy statistics and predicted battle damage for this floor. The battle panel keeps the last "
     "defeated enemy.",
     "Reveals enemy statistics and combat forecasts; unlocks manual saves."},
    {"wisdom_orb", "Orb of Wisdom", false,
     "Read the clues recorded from old men and merchants. Scroll through long passages with the mouse wheel.",
     "Shows clues recorded while owning the Orb of Wisdom."},
    {"flying_orb", "Orb of Flight", false,
     "Travel between visited floors. Use Up and Down to preview a floor, then Enter to travel.",
     "Use beside a staircase to travel from 1 through highest_floor, except 44. Supply floor, or use the "
     "flight selector."},
    {"cross", "Cross", true,
     "Works automatically in ordinary battles against Zombies, Zombie Knights and Vampires.",
     "Passive: doubles attack against Zombies, Zombie Knights and Vampires in ordinary combat."},
    {"elixir", "Elixir", false,
     "Restores life equal to ten times your attack plus five times your defense. Consumed when used.",
     "Restores attack * 10 + defense * 5 HP; consumed on use."},
    {"mattock", "Mattock", false,
     "Lowers ordinary walls directly above, below, left and right of you. Consumed when used.",
     "Removes adjacent brick walls; consumed on use."},
    {"bomb", "Bomb", false,
     "Destroys eligible monsters directly above, below, left and right of you. Consumed when used.",
     "Destroys eligible adjacent enemies; consumed on use."},
    {"warp_staff", "Warp Staff", false,
     "Warps to the opposite position on this floor when that position is a road. Each attempt uses one "
     "charge.",
     "Attempts to warp to the opposite square (10-x, 10-y); each attempt consumes one charge."},
    {"ascent_wing", "Ascent Wing", false,
     "Ascends one floor at the same map position if it is a road. Consumed on successful travel.",
     "Moves up one floor at the same coordinates if the destination is road; consumed on success."},
    {"descent_wing", "Descent Wing", false,
     "Descends one floor at the same map position if it is a road. Consumed on successful travel.",
     "Moves down one floor at the same coordinates if the destination is road; consumed on success."},
    {"dragon_slayer", "Dragon Slayer", true, "Works automatically in ordinary battles against the Dragon.",
     "Passive: doubles attack against the Dragon in ordinary combat."},
    {"snow_crystal", "Snow Crystal", false,
     "Turns adjacent lava into road. The crystal can be used repeatedly.",
     "Converts adjacent lava into road; reusable."},
    {"magic_key", "Magic Key", false, "Opens every yellow door on the current floor. Consumed when used.",
     "Opens every yellow door on the current floor; consumed on use."},
    {"super_mattock", "Super Mattock", false,
     "Removes ordinary walls across the current floor. Consumed when used.",
     "Removes all ordinary brick walls on the current floor; consumed on use."},
    {"lucky_gold", "Lucky Gold", true, "Works automatically, increasing gold awarded by battle victories.",
     "Passive: doubles ordinary combat gold rewards."},
}};

constexpr const ItemDefinition& item_definition(Item item) {
    return ItemDefinitions.at(std::to_underlying(item));
}

constexpr std::optional<Item> item_from_id(std::string_view id) {
    for (int i = 0; i < ItemCount; ++i)
        if (ItemDefinitions[i].id == id)
            return static_cast<Item>(i);
    return std::nullopt;
}
} // namespace tsw
