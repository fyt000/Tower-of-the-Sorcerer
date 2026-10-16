#include "tsw/dialogue_ids.hpp"
#include "tsw/game.hpp"
#include <array>

namespace tsw {
namespace {
// 0x481E80 scans north, west, east, south through 0x44C9F0. Some
// classified neighbors overwrite an earlier stair result; road/wall do not.
// The original classifier returned 19/52/24/13/15/14/12/110/111.
// Only the last classified neighbor is tested, even after finding stairs.
enum class FlightNeighbor {
    Other,
    Stairs,
    Lava,
    Altar,
    Merchant,
    Thief,
    Fairy,
    OldMan,
    MagicianA,
    MagicianB
};

struct FlightScan {
    FlightNeighbor last_classified = FlightNeighbor::Other;
    StairKind highest_floor_stair = StairKind::None;
};

FlightScan flight_neighbors(const Game& game) {
    const auto& h = game.hero;
    const int position = cell(h.x, h.y);
    const std::array<int, 4> neighbors{h.y > 0 ? position - BoardWidth : -1, h.x > 0 ? position - 1 : -1,
                                       h.x < BoardWidth - 1 ? position + 1 : -1,
                                       h.y < BoardWidth - 1 ? position + BoardWidth : -1};
    FlightScan result;
    for (int index : neighbors) {
        if (index < 0)
            continue;
        const int tile = game.tile(h.floor, index);
        if (tile == StairsUp || tile == StairsDown) {
            result.last_classified = FlightNeighbor::Stairs;
            if (h.floor == h.highest_floor)
                result.highest_floor_stair = tile == StairsUp ? StairKind::Up : StairKind::Down;
        } else if (tile == Lava)
            result.last_classified = FlightNeighbor::Lava;
        else if (tile == Altar || tile == AltarSide)
            result.last_classified = FlightNeighbor::Altar;
        else if (tile >= Merchant && tile <= OldMan2)
            result.last_classified = tile < Thief    ? FlightNeighbor::Merchant
                                     : tile < Fairy  ? FlightNeighbor::Thief
                                     : tile < OldMan ? FlightNeighbor::Fairy
                                                     : FlightNeighbor::OldMan;
        else if (tile == MagicianA || tile == MagicianA + 1)
            result.last_classified = FlightNeighbor::MagicianA;
        else if (tile == MagicianB || tile == MagicianB + 1)
            result.last_classified = FlightNeighbor::MagicianB;
    }
    return result;
}
} // namespace

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

bool Game::can_open_flight() const {
    return !busy() && inventory(Item::FlightOrb) == 1 &&
           flight_neighbors(*this).last_classified == FlightNeighbor::Stairs;
}

bool Game::open_flight() {
    if (busy())
        return false;
    hero.flight_direction = FlightDirection::None;
    hero.highest_floor_stair_kind = StairKind::None;
    if (inventory(Item::FlightOrb) != 1)
        return false;
    const auto scan = flight_neighbors(*this);
    hero.highest_floor_stair_kind = scan.highest_floor_stair;
    if (scan.last_classified != FlightNeighbor::Stairs) {
        update_status(20);
        return false;
    }
    // The original map draw (0x442C38) clears the marker after the scan.
    hero.highest_floor_stair_kind = StairKind::None;
    return true;
}

bool Game::flight_preview(int destination, FlightDirection direction) {
    if (destination < 1 || destination > hero.highest_floor || destination == 44)
        return false;
    hero.flight_direction = direction;
    hero.highest_floor_stair_kind = StairKind::None; // 0x442C38 runs on every successful preview.
    if (direction == FlightDirection::Up && destination == 35 && tile(35, 91) + tile(2, 120) == 27)
        tile(2, 120) = Road;
    return true;
}

bool Game::confirm_flight(int destination) {
    if (busy() || inventory(Item::FlightOrb) <= 0 || destination < 1 || destination > hero.highest_floor ||
        destination == 44)
        return false;
    if (hero.flight_direction != FlightDirection::None) {
        if (destination != 25 && tile(25, 71) == Fairy)
            tile(25, 71) = Road;
        if (destination != 49 && tile(49, 16) == Fairy)
            tile(49, 16) = Road;
        if (hero.highest_floor == 29 && destination < 29) {
            tile(29, 38) = tile(29, 27) = Road;
            tile(29, 17) = Thief;
        }
        if (destination == hero.highest_floor) {
            if (hero.flight_direction == FlightDirection::Up &&
                hero.highest_floor_stair_kind == StairKind::Up)
                hero.flight_direction = FlightDirection::Down;
            else if (hero.flight_direction == FlightDirection::Down &&
                     hero.highest_floor_stair_kind != StairKind::Up)
                hero.flight_direction = FlightDirection::Up;
        }
        const int landing = hero.flight_direction == FlightDirection::Up ? floors[destination].up_landing
                                                                         : floors[destination].down_landing;
        hero.floor = destination;
        hero.x = landing % BoardWidth;
        hero.y = landing / BoardWidth;
        change_music_for_floor();
        face_away_from_stair(hero.flight_direction == FlightDirection::Up);
    }
    push(Op::Wait);
    push(Op::Sound, SoundCue::Get);
    return true;
}

bool Game::use(Item item, int destination) {
    if (busy() || inventory(item) <= 0)
        return false;
    const int position = cell(hero.x, hero.y);
    const auto cardinal = std::array<int, 4>{
        hero.y < BoardWidth - 1 ? position + BoardWidth : -1, hero.x < BoardWidth - 1 ? position + 1 : -1,
        hero.x > 0 ? position - 1 : -1, hero.y > 0 ? position - BoardWidth : -1};
    switch (item) {
    case Item::HeroOrb:
        status = "The Orb reveals this floor's enemy statistics and predicted battle damage.";
        return true;
    case Item::WisdomOrb: {
        std::string clues;
        for (int i = 0; i < 24; ++i)
            if (hero.wisdom_hints[i] == HintState::Recorded) {
                clues += original_dialogue(DialogueId::WisdomHintBase + i);
                clues += "\n\n";
            }
        dialogue =
            Dialogue{clues.empty() ? "No recorded clues yet." : clues, ContinuationStage::None, false, {}};
        return true;
    }
    case Item::FlightOrb:
        if (destination < 1 || destination > hero.highest_floor || destination == 44)
            return false;
        if (!open_flight())
            return false;
        for (int floor = hero.floor, step = destination > floor ? 1 : -1; floor != destination;) {
            floor += step;
            if (floor == 44)
                floor += step;
            flight_preview(floor, step > 0 ? FlightDirection::Up : FlightDirection::Down);
        }
        return confirm_flight(destination);
    case Item::Elixir: {
        const int gain = hero.attack * 10 + hero.defense * 5;
        prepared_status_ = {DialogueId::ElixirUsed, gain};
        message_code = msg::Prepared;
        hero.hp += gain;
        inventory(item) = 0;
        push(Op::Wait);
        push(Op::Message, msg::Prepared);
        push(Op::Wait);
        push(Op::UpdateInventory);
        push(Op::Wait);
        push(Op::Sound, SoundCue::Get);
        return true;
    }
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
    case Item::Bomb: {
        const int previous_gold = hero.gold;
        push(Op::Wait);
        push(Op::Callback, Callback::CheckGuards);
        push(Op::Message);
        push(Op::UpdateInventory);
        for (int index : cardinal)
            if (index >= 0 && classify_tile(tile(hero.floor, index)) == TileClass::BombTarget) {
                if (hero.floor == 44 && (index == cell(4, 8) || index == cell(6, 8)))
                    run_history.shield_guards_bombed = true;
                contact_index = neighbor_index = index;
                hero.gold += monsters[monster_for_tile(tile(hero.floor, index))].gold;
                bomb_dissolve(index);
            }
        inventory(item) = 0;
        prepared_status_ = {DialogueId::BombUsed, hero.gold - previous_gold};
        message_code = msg::Prepared;
        return true;
    }
    case Item::WarpStaff:
        --inventory(item);
        contact_index = CellCount - 1 - position;
        if (tile(hero.floor, contact_index) == Road) {
            hero.x = contact_index % BoardWidth;
            hero.y = contact_index / BoardWidth;
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
        hero.highest_floor_stair_kind = StairKind::None; // Successful wings redraw through 0x442C38.
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
        if (found)
            prepared_status_ = {DialogueId::SnowCrystalUsed};
        message_code = found ? msg::Prepared : msg::SnowFailed;
        push(Op::Message, message_code);
        return true;
    }
    case Item::MagicKey:
        inventory(item) = 0;
        push(Op::Message, 66);
        push(Op::UpdateInventory);
        for (int index = CellCount - 1; index >= 0; --index)
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
        for (int x = BoardWidth - 1; x >= 0; --x)
            for (int y = BoardWidth - 1; y >= 0; --y)
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
