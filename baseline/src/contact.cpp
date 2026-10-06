#include "baseline/game.hpp"
#include <algorithm>

namespace baseline {
// handan, 0x444490. Door contact opens the cell; a second step enters it.
void Game::contact() {
    const int target = tile(hero.floor, contact_index);
    const int scale = hero.cycle_factor_minus_one + 1;
    switch (target) {
    case YellowDoor:
    case BlueDoor:
    case RedDoor: {
        int& keys = target == YellowDoor ? hero.yellow_keys
                    : target == BlueDoor ? hero.blue_keys
                                         : hero.red_keys;
        door_opened = keys > 0;
        message_code = door_opened ? target + 3 : target + 15;
        if (door_opened)
            --keys;
        check_door(); // Runs on refusal too, before inserting the opening records.
        push(Op::Message, message_code);
        if (door_opened) {
            push(Op::UpdateInventory);
            push(Op::DoorFrame, contact_index, target);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
        }
        return;
    }
    case Road:
        walk_to_contact();
        return;
    case SpecialRoad:
        special_road();
        return;
    case SecretWall:
        push(Op::Wait);
        push(Op::Message, 1);
        push(Op::Wait);
        push(Op::DoorFrame, contact_index, DoorMotion::LowerWall);
        expand_door();
        push(Op::Wait);
        push(Op::Sound, SoundCue::Open);
        return;
    case HiddenObject: {
        int reveal = -1, index = contact_index;
        if (hero.floor == 12 && index == 10)
            reveal = Merchant;
        else if (hero.floor == 16 && index == 120)
            reveal = OldMan;
        else if (hero.floor == 19 && index == 27)
            reveal = Cross;
        else if (hero.floor == 41 && tile(hero.floor, 12) == Road) {
            index = 20;
            reveal = MagicianA;
        }
        if (reveal >= 0) {
            push(Op::Wait);
            push(Op::SetTile, index, reveal);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            waits(2);
        }
        return;
    }
    case StairsUp:
        stair(true);
        return;
    case StairsDown:
        stair(false);
        return;
    case Altar: {
        const int n = hero.altar_purchases;
        shop_kind_ = 1;
        shop_cost_ = 10 * (n * n + n + 2);
        const int area = (hero.floor + 10) / 10;
        dialogue = Dialogue{
            "Altar: each purchase increases the next price. Cost: " + std::to_string(shop_cost_) + " gold.",
            2,
            true,
            {"HP +" + std::to_string(100 * (n + 1) * scale), "ATK +" + std::to_string(2 * area * scale),
             "DEF +" + std::to_string(4 * area * scale)}};
        return;
    }
    case Merchant:
    case Merchant2:
        speak_merchant();
        return;
    case Thief:
    case Thief2:
        speak_thief();
        return;
    case Fairy:
    case Fairy2:
        speak_fairy();
        return;
    case OldMan:
    case OldMan2:
        speak_old_man();
        return;
    case TimeGate:
    case TimeGate2:
        hero.music_track = 13;
        if (tile(25, 60) == Road) {
            tile(24, 4) = tile(24, 6) = Wall;
            tile(24, 16) = tile(24, 27) = tile(24, 38) = Road;
            tile(24, 5) = SpecialRoad;
        }
        tile(50, 49) = Thief;
        push(Op::Wait);
        push(Op::SetTile, 60, TimeGate);
        push(Op::Wait);
        push(Op::Dialogue, 26);
        push(Op::Wait);
        push(Op::Dialogue, 25);
        waits(2);
        return;
    case YellowKey:
        ++hero.yellow_keys;
        break;
    case RedKey:
        ++hero.red_keys;
        break;
    case BlueKey:
        ++hero.blue_keys;
        break;
    case RedPotion:
        hero.hp += 50 * ((hero.floor + 9) / 10) * scale;
        break;
    case BluePotion:
        hero.hp += 200 * ((hero.floor + 9) / 10) * scale;
        break;
    case RedGem:
        hero.attack += ((hero.floor + 9) / 10) * scale;
        break;
    case BlueGem:
        hero.defense += ((hero.floor + 9) / 10) * scale;
        break;
    default:
        if (target >= WisdomOrb && target <= LuckyGold) {
            const auto item = static_cast<Item>(target - HeroOrb);
            inventory(item) = item == Item::WarpStaff ? 3 : 1;
            status = "Found " + std::string(item_name(item)) + ".";
        } else if (target >= IronSword && target <= SacredShield) {
            constexpr std::array<int, 5> Gain{10, 20, 40, 50, 100};
            const int equipment = target - IronSword, tier = equipment % 5;
            if (equipment < 5) {
                hero.attack += Gain[tier] * scale;
                hero.sword = tier + 1;
            } else {
                hero.defense += Gain[tier] * scale;
                hero.shield = tier + 1;
            }
            hero.equipment_found[equipment] = 1;
        } else if (target == Zeno || target == Zeno + 1) {
            if (hero.floor == 50 && !hero.cycle_factor_minus_one)
                ending();
            else if (hero.floor == 49 || hero.floor == 50) {
                if (hero.floor == 50 && !hero.later_cycle)
                    monsters[ZenoRow] = {1000, 625, 125, monsters[ZenoRow].gold};
                battle();
            }
            return;
        } else if (monster_for_tile(target) >= 0 && target <= MagicianB + 4) {
            battle();
            return;
        } else
            return;
    }
    message_code = 1;
    if (target >= WisdomOrb && target <= LuckyGold)
        message_code = target == WisdomOrb ? 22 : target == FlightOrb ? 21 : target + 1;
    push(Op::Message, message_code);
    push(Op::UpdateInventory);
    push(Op::Wait);
    push(Op::Sound, SoundCue::Get);
    tile(hero.floor, contact_index) = Road;
    walk_to_contact();
}

// idou, 0x44C04C: movement commits before the deferred magic damage.
void Game::walk_to_contact() {
    hero.x = contact_index % BoardWidth;
    hero.y = contact_index / BoardWidth;
    scratch_index = contact_index;
    for (const auto [dx, dy] : std::array<std::array<int, 2>, 4>{{{0, -1}, {-1, 0}, {1, 0}, {0, 1}}}) {
        const int x = hero.x + dx, y = hero.y + dy;
        if (x < 0 || x >= BoardWidth || y < 0 || y >= BoardWidth)
            continue;
        neighbor_index = cell(x, y);
        const int t = tile(hero.floor, neighbor_index);
        if (hero.floor == hero.highest_floor && (t == StairsUp || t == StairsDown))
            hero.highest_floor_stair = t == StairsUp ? 1 : 2;
        if (t == MagicianA || t == MagicianA + 1 || t == MagicianB || t == MagicianB + 1)
            hazard(neighbor_index, cell(hero.x + dx * 2, hero.y + dy * 2));
    }
    if (hero.equipment_found[SacredShieldFlag])
        return;
    const bool horizontal = hero.x > 0 && hero.x < 10 && tile(hero.floor, scratch_index - 1) == Sorcerer &&
                            tile(hero.floor, scratch_index + 1) == Sorcerer;
    const bool vertical = hero.y > 0 && hero.y < 10 && tile(hero.floor, scratch_index - 11) == Sorcerer &&
                          tile(hero.floor, scratch_index + 11) == Sorcerer;
    for (int pair = 0; pair < int(horizontal) + int(vertical); ++pair) {
        push(Op::Wait);
        push(Op::PincerDamage);
        push(Op::Wait);
        push(Op::Message, 112);
        damage_pose(scratch_index);
        push(Op::Wait);
        push(Op::Sound, SoundCue::Open);
    }
}
void Game::hazard(int magician_cell, int retreat_cell) {
    const int t = tile(hero.floor, magician_cell);
    const bool magician_a = t == MagicianA || t == MagicianA + 1;
    // Preserve the original extra y guard even for a horizontal retreat on 47F.
    // Index 121 would alias the next floor's stair metadata in the original 123-byte records.
    if (magician_a && hero.floor == 47 && hero.y > 0 && hero.y < 10 && retreat_cell >= 0 &&
        retreat_cell < CellCount && tile(hero.floor, retreat_cell) == Road) {
        push(Op::Wait);
        push(Op::MoveTile, magician_cell, retreat_cell);
        push(Op::Wait);
        push(Op::Sound, SoundCue::Get);
    }
    if (!hero.equipment_found[SacredShieldFlag]) {
        push(Op::Wait);
        push(Op::HpDelta, -(magician_a ? 200 : 100) * (hero.cycle_factor_minus_one + 1));
        push(Op::Wait);
        push(Op::Message, (magician_a ? 110 : 111) + (hero.cycle_factor_minus_one ? 28 : 0));
        damage_pose(scratch_index);
        push(Op::Wait);
        push(Op::Sound, SoundCue::Open);
    }
}
void Game::stair(bool up) {
    const int source = hero.floor;
    const int destination = up ? (source == 43 ? 45 : source + 1) : (source == 45 ? 43 : source - 1);
    if (destination < 0 || destination >= FloorCount)
        return;
    waits(2);
    visual.stair_source_floor = source;
    visual.stair_source = floors[source];
    visual.stair_hero_x = hero.x;
    visual.stair_hero_y = hero.y;
    visual.stair_hero_facing = hero.facing;
    visual.stair_revealing = false;
    if ((up && (source == 20 || source == 25 || source == 40)) || (!up && (source == 25 || source == 49))) {
        const int fairy_cell = source == 20 ? 49 : source == 25 ? 71 : source == 40 ? 60 : 16;
        if (tile(source, fairy_cell) == Fairy)
            tile(source, fairy_cell) = Road;
    }
    hero.floor = destination;
    if (up && hero.highest_floor < destination) {
        hero.highest_floor = destination;
        if (hero.equipment_found[3] == 35 && tile(35, 91) + tile(2, 120) == 27)
            tile(2, 120) = Road;
    }
    if (!up && source == 29 && destination == 28 && hero.highest_floor == 29) {
        tile(29, 38) = tile(29, 27) = Road;
        tile(29, 17) = Thief;
    }
    const int landing = up ? floors[destination].up_landing : floors[destination].down_landing;
    hero.x = landing % BoardWidth;
    hero.y = landing / BoardWidth;
    face_away_from_stair(up);
    change_music_for_floor();
    if (up && destination == 32 && !hero.floor32_arrival_seen) {
        special_road();
        hero.floor32_arrival_seen = true;
    }
    if (up && destination == 42 && !hero.dialogue_seen[51]) {
        special_road();
        hero.dialogue_seen[51] = 1;
    }
    push(Op::Wait);
    push(Op::Message, up ? 7 : 8);
    for (int index = CellCount; index >= 1; --index) {
        if (hero.music_track && index == 102)
            push(Op::FloorMusic);
        push(Op::StairFrame, 1, index);
    }
    for (int index = CellCount; index >= 1; --index)
        push(Op::StairFrame, 0, index);
    push(Op::Wait);
    push(Op::Sound, SoundCue::Stairs);
}
void Game::face_away_from_stair(bool climbed) {
    // 0x442F80 / 0x443050: the last adjacent matching stair sets facing.
    const Tile stair_tile = climbed ? StairsDown : StairsUp;
    for (const auto [dx, dy, facing] :
         std::array<std::array<int, 3>, 4>{{{0, -1, 1}, {-1, 0, 3}, {1, 0, 2}, {0, 1, 4}}}) {
        const int x = hero.x + dx, y = hero.y + dy;
        if (x >= 0 && x < BoardWidth && y >= 0 && y < BoardWidth && tile_at(hero.floor, x, y) == stair_tile)
            hero.facing = static_cast<Direction>(facing);
    }
}
void Game::check_door() {
    // doorcheck, 0x47BEAC: numeric sums also define behavior on altered maps.
    if (hero.floor == 39) {
        const int sum = tile(39, 12) + tile(39, 16) + tile(39, 34) + tile(39, 36) + tile(39, 56) +
                        tile(39, 58) + tile(39, 60);
        if (sum == 7 && ((tile(39, 14) == Road && contact_index == 38) ||
                         (tile(39, 38) == Road && contact_index == 14))) {
            push(Op::Wait);
            push(Op::SetTile, 36, WarpStaff);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            waits(2);
        }
    } else if (hero.floor == 43 && contact_index == 7 && tile(43, 8) == Sorcerer)
        push(Op::SetTile, 7, SpecialRoad);
}
void Game::special_road() {
    // mevent, 0x46397C. 23F is a blocked attempt; other scenes commit the step.
    switch (hero.floor) {
    case 3:
        walk_to_contact();
        tile(hero.floor, cell(hero.x, hero.y)) = Road;
        push(Op::Dialogue, 10);
        waits(4);
        summon(70, Zeno);
        push(Op::Wait);
        push(Op::Sound, SoundCue::MusicStop);
        break;
    case 23:
        push(Op::Wait);
        push(Op::Message, 114);
        push(Op::Wait);
        push(Op::SetTile, contact_index, Wall);
        push(Op::Wait);
        push(Op::Sound, SoundCue::Open);
        waits(2);
        break;
    case 32:
    case 42:
    case 48:
        check_floor();
        break;
    case 10:
    case 15:
    case 20:
    case 24:
    case 25:
    case 30:
    case 33:
    case 38:
    case 40:
    case 43:
    case 49:
        walk_to_contact();
        if (hero.floor != 20 || cell(hero.x, hero.y) == 82) {
            tile(hero.floor, cell(hero.x, hero.y)) = Road;
            if (hero.floor == 20)
                hero.music_track = 16;
            if (hero.floor == 25)
                hero.music_track = 7;
            if (hero.floor == 40)
                hero.music_track = 18;
            if (hero.floor == 49)
                hero.music_track = 19;
            check_floor();
        }
        break;
    default:
        break;
    }
}
void Game::change_music_for_floor() {
    if (!hero.music_track)
        return;
    if (hero.floor == 0)
        hero.music_track = 21;
    else if (hero.floor <= 10)
        hero.music_track = 5;
    else if (hero.floor <= 20)
        hero.music_track = 6;
    else if (hero.floor <= 30)
        hero.music_track = 17;
    else if (hero.floor <= 40)
        hero.music_track = 8;
    else if (hero.floor <= 49)
        hero.music_track = 9;
    else
        hero.music_track = 10;
}
} // namespace baseline
