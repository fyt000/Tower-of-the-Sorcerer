#include "tsw/game.hpp"
#include <array>

namespace tsw {
TileClass Game::classify_tile(int tile_id) {
    if (tile_id == Wall)
        return TileClass::Wall;
    if (tile_id == Lava)
        return TileClass::Lava;
    if ((tile_id >= GreenSlime && tile_id <= Rock + 1) || (tile_id >= Sorcerer && tile_id <= Vampire + 1) ||
        (tile_id >= GoldenKnight && tile_id <= SlimeMan + 1) ||
        (tile_id >= VampireBat && tile_id <= GateKeeperA + 1))
        return TileClass::BombTarget;
    return TileClass::Other;
}

void Game::bomb_dissolve(int index) {
    // toroad2, 0x44BC34. The colored image is an operand, not a tile write.
    const int underlying = tile(hero.floor, index);
    push(Op::WriteTile, index, Road);
    for (int mask = DissolveLastMask; mask >= DissolveFirstMask; mask -= 4) {
        push(Op::Wait, underlying, Road);
        push(Op::Overlay, index, mask);
        push(Op::Wait);
        push(Op::Sound, SoundCue::Open);
    }
}

bool Game::flight_preview(int destination, int direction) {
    if (destination < 1 || destination > hero.highest_floor || destination == 44)
        return false;
    hero.flight_direction = direction;
    if (direction == 1 && destination == 35 && tile(35, 91) + tile(2, 120) == 27)
        tile(2, 120) = Road;
    return true;
}

bool Game::use(Item item, int destination) {
    if (busy() || inventory(item) <= 0)
        return false;
    const int position = cell(hero.x, hero.y);
    const auto cardinal =
        std::array<int, 4>{hero.y < 10 ? position + 11 : -1, hero.x < 10 ? position + 1 : -1,
                           hero.x > 0 ? position - 1 : -1, hero.y > 0 ? position - 11 : -1};
    switch (item) {
    case Item::HeroOrb:
        status = "The Orb reveals this floor's enemy statistics and predicted battle damage.";
        return true;
    case Item::WisdomOrb: {
        std::string clues;
        for (int i = 0; i < 24; ++i)
            if (hero.wisdom_hints[i] == 2)
                clues += std::string(original_dialogue(62 + i)) + "\n\n";
        dialogue = Dialogue{clues.empty() ? "No recorded clues yet." : clues, 0, false, {}};
        return true;
    }
    case Item::FlightOrb:
        if (destination < 1 || destination > hero.highest_floor || destination == 44)
            return false;
        if (!hero.flight_direction && destination != hero.floor)
            hero.flight_direction = destination > hero.floor ? 1 : 2;
        if (hero.flight_direction) {
            if (destination != 25 && tile(25, 71) == Fairy)
                tile(25, 71) = Road;
            if (destination != 49 && tile(49, 16) == Fairy)
                tile(49, 16) = Road;
            if (hero.highest_floor == 29 && destination < 29) {
                tile(29, 38) = tile(29, 27) = Road;
                tile(29, 17) = Thief;
            }
            if (destination == hero.highest_floor) {
                if (hero.flight_direction == 1 && hero.highest_floor_stair == 1)
                    hero.flight_direction = 2;
                else if (hero.flight_direction == 2 && hero.highest_floor_stair != 1)
                    hero.flight_direction = 1;
            }
            const int landing = hero.flight_direction == 1 ? floors[destination].up_landing
                                                           : floors[destination].down_landing;
            hero.floor = destination;
            hero.x = landing % 11;
            hero.y = landing / 11;
            change_music_for_floor();
            face_away_from_stair(hero.flight_direction == 1);
        }
        push(Op::Wait);
        push(Op::Sound, SoundCue::Get);
        return true;
    case Item::Elixir:
        hero.hp += hero.attack * 10 + hero.defense * 5;
        inventory(item) = 0;
        push(Op::Wait);
        push(Op::Message, 1);
        push(Op::Wait);
        push(Op::UpdateInventory);
        push(Op::Wait);
        push(Op::Sound, SoundCue::Get);
        return true;
    case Item::Mattock:
        inventory(item) = 0;
        push(Op::Message, 60);
        push(Op::UpdateInventory);
        for (int index : cardinal)
            if (index >= 0 && tile(hero.floor, index) == Wall) {
                // Mattock helper 0x451B98 uses the same sixteen-frame wall lowering.
                push(Op::Wait);
                push(Op::DoorFrame, index, DoorMotion::LowerWall);
                expand_door();
                push(Op::Wait);
                push(Op::Sound, SoundCue::Open);
            }
        return true;
    case Item::Bomb:
        push(Op::Wait);
        push(Op::Callback, Callback::CheckGuards);
        push(Op::Message);
        push(Op::UpdateInventory);
        for (int index : cardinal)
            if (index >= 0 && classify_tile(tile(hero.floor, index)) == TileClass::BombTarget) {
                contact_index = neighbor_index = index;
                hero.gold += monsters[monster_for_tile(tile(hero.floor, index))].gold;
                bomb_dissolve(index);
            }
        inventory(item) = 0;
        return true;
    case Item::WarpStaff:
        --inventory(item);
        contact_index = 120 - position;
        if (tile(hero.floor, contact_index) == Road) {
            hero.x = contact_index % 11;
            hero.y = contact_index / 11;
            push(Op::Sound, SoundCue::Get);
            update_status(62);
        } else
            update_status(68);
        return true;
    case Item::AscentWing:
    case Item::DescentWing: {
        const int floor = hero.floor + (item == Item::AscentWing ? 1 : -1);
        if (floor < 0 || floor >= FloorCount || tile(floor, position) != Road) {
            update_status(item == Item::AscentWing ? 69 : 70);
            return true;
        }
        inventory(item) = 0;
        hero.floor = floor;
        change_music_for_floor();
        push(Op::Message, item == Item::AscentWing ? 63 : 64);
        push(Op::UpdateInventory);
        push(Op::Wait);
        push(Op::Sound, SoundCue::Get);
        return true;
    }
    case Item::SnowCrystal: {
        push(Op::UpdateInventory);
        bool found = false;
        constexpr std::array<DoorMotion, 4> Motions{DoorMotion::RoadFromTop, DoorMotion::RoadFromLeft,
                                                    DoorMotion::RoadFromRight, DoorMotion::RoadFromBottom};
        for (int i = 0; i < 4; ++i)
            if (cardinal[i] >= 0 && tile(hero.floor, cardinal[i]) == Lava) {
                found = true;
                // 0x451D3C: the persistent tile write plays after the road animation.
                push(Op::Wait);
                push(Op::WriteTile, cardinal[i], Road);
                push(Op::Wait);
                push(Op::DoorFrame, cardinal[i], Motions[i]);
                expand_door();
                push(Op::Wait);
                push(Op::Sound, SoundCue::Open);
            }
        push(Op::Message, found ? 1 : 65);
        return true;
    }
    case Item::MagicKey:
        inventory(item) = 0;
        push(Op::Message, 66);
        push(Op::UpdateInventory);
        for (int index = 120; index >= 0; --index)
            if (tile(hero.floor, index) == YellowDoor) {
                push(Op::DoorFrame, index, DoorMotion::Yellow);
                expand_door();
                push(Op::Wait);
                push(Op::Sound, SoundCue::Open);
            }
        return true;
    case Item::SuperMattock:
        inventory(item) = 0;
        push(Op::Message, 67);
        push(Op::UpdateInventory);
        for (int x = 10; x >= 0; --x)
            for (int y = 10; y >= 0; --y)
                if (tile_at(hero.floor, x, y) == Wall) {
                    push(Op::Wait);
                    push(Op::SetTile, cell(x, y), Road);
                    push(Op::Wait);
                    push(Op::Sound, SoundCue::Get);
                }
        return true;
    case Item::Cross:
    case Item::DragonSlayer:
    case Item::LuckyGold:
        status = "This item works automatically.";
        return true;
    }
    return false;
}
} // namespace tsw
