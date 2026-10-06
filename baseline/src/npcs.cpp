#include "baseline/game.hpp"
#include <algorithm>

namespace baseline {
namespace {
struct MerchantOffer {
    int floor, cost, hint;
};
constexpr std::array<MerchantOffer, 12> Merchants{{{2, 0, 29},
                                                   {6, 50, 2},
                                                   {7, 50, 3},
                                                   {12, 800, 4},
                                                   {12, 1000, -1},
                                                   {15, 200, 5},
                                                   {28, 0, -1},
                                                   {31, 1000, 11},
                                                   {38, 200, 15},
                                                   {39, 2000, 17},
                                                   {45, 1000, 20},
                                                   {47, 4000, 22}}};
} // namespace
void Game::speak_merchant() {
    shop_id_ = -1;
    for (int i = 0; i < int(Merchants.size()); ++i) {
        if (Merchants[i].floor == hero.floor && (hero.floor != 12 || (hero.x == 9) == (i == 4))) {
            shop_id_ = i;
            break;
        }
    }
    if (shop_id_ < 0)
        return;
    const auto offer = Merchants[shop_id_];
    shop_hint_ = offer.hint;
    if (hero.merchant_used[shop_id_] && shop_hint_ >= 0) {
        int& heard = shop_hint_ == 29 ? hero.merchant2_heard : hero.wisdom_hints[shop_hint_];
        const bool first = !heard;
        if (first)
            heard = inventory(Item::WisdomOrb) ? 2 : 1;
        const int message = shop_hint_ == 29 ? 91 : first ? 62 + shop_hint_ : 90;
        dialogue = Dialogue{std::string(original_dialogue(message)), 0, false, {}};
        return;
    }
    shop_kind_ = 2;
    shop_cost_ = offer.cost;
    shop_npc_cell_ = contact_index;
    dialogue =
        Dialogue{std::string(original_dialogue(246 + shop_id_)), 0, true, {"Accept the trade", "", ""}};
}
bool Game::choose(int choice) {
    if (!dialogue || !dialogue->shop)
        return false;
    if (choice < 0) {
        dialogue.reset();
        shop_kind_ = 0;
        return true;
    }
    if (hero.gold < shop_cost_) {
        status = "You do not have enough gold.";
        return false;
    }
    if (shop_kind_ == 1) {
        if (choice > 2)
            return false;
        const int scale = hero.cycle_factor_minus_one + 1, area = (hero.floor + 10) / 10;
        switch (choice) {
        case 0:
            hero.hp += 100 * (hero.altar_purchases + 1) * scale;
            break;
        case 1:
            hero.attack += 2 * area * scale;
            break;
        case 2:
            hero.defense += 4 * area * scale;
            break;
        }
        hero.gold -= shop_cost_;
        ++hero.altar_purchases;
    } else if (shop_kind_ == 2) {
        if (choice != 0)
            return false;
        switch (shop_id_) {
        case 0:
            hero.gold += 1000;
            break;
        case 1:
        case 5:
            ++hero.blue_keys;
            break;
        case 2:
            hero.yellow_keys += 5;
            break;
        case 3:
            ++hero.red_keys;
            break;
        case 4:
            ++hero.yellow_keys;
            break;
        case 6:
            if (!hero.yellow_keys) {
                status = "You have no yellow key to sell.";
                return false;
            }
            --hero.yellow_keys;
            hero.gold += 100;
            break;
        case 7:
            hero.yellow_keys += 4;
            ++hero.blue_keys;
            break;
        case 8:
            hero.yellow_keys += 3;
            break;
        case 9:
            hero.blue_keys += 3;
            break;
        case 10:
            hero.hp += 2000;
            break; // Original unscaled 45F gift, including backside.
        case 11:
            inventory(Item::SuperMattock) = 1;
            break;
        }
        hero.gold -= shop_cost_;
        if (shop_id_ != 4 && shop_id_ != 6)
            hero.merchant_used[shop_id_] = 1;
    } else
        return false;
    const bool altar = shop_kind_ == 1;
    dialogue.reset();
    shop_kind_ = 0;
    if (altar) {
        push(Op::Wait);
        push(Op::Message, 1);
    } else {
        push(Op::Message);
        push(Op::UpdateInventory);
    }
    push(Op::Wait);
    push(Op::Sound, SoundCue::Get);
    status = "Trade completed.";
    return true;
}
void Game::speak_old_man() {
    int hint = -1, message = 90;
    // roujin, 0x449708. First-hearing state never upgrades retrospectively.
    switch (hero.floor) {
    case 2:
        message = 87;
        if (!hero.dialogue_seen[18]) {
            hero.dialogue_seen[18] = 1;
            hero.attack += hero.attack * 3 / 100;
            hero.defense += hero.defense * 3 / 100;
            push(Op::Wait);
            push(Op::Message);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            waits(2);
        }
        break;
    case 3:
        message = 88;
        break;
    case 4:
        hint = 0;
        break;
    case 6:
        hint = 1;
        break;
    case 16:
        if (hero.x == 9) {
            message = 89;
            if (!hero.dialogue_seen[29]) {
                hero.dialogue_seen[29] = 1;
                inventory(Item::Elixir) = 1;
                push(Op::Wait);
                push(Op::UpdateInventory);
                push(Op::Wait);
                push(Op::Sound, SoundCue::Get);
                waits(2);
            }
        } else
            hint = 6;
        break;
    case 18:
        hint = 7;
        break;
    case 21:
        hint = 8;
        break;
    case 23:
        message = 61;
        break;
    case 27:
        hint = 9;
        break;
    case 31:
        hint = 10;
        break;
    case 33:
        hint = 12;
        break;
    case 36:
        hint = 13;
        break;
    case 37:
        hint = 14;
        break;
    case 39:
        hint = 16;
        break;
    case 42:
        hint = 18;
        break;
    case 45:
        hint = 19;
        break;
    case 46:
        hint = 21;
        break;
    case 48:
        hint = 23;
        break;
    }
    if (hint >= 0) {
        if (hero.wisdom_hints[hint])
            message = 86;
        else {
            hero.wisdom_hints[hint] = inventory(Item::WisdomOrb) ? 2 : 1;
            message = 62 + hint;
        }
    }
    const int special = hero.floor == 2 ? 0 : hero.floor == 3 ? 1 : hero.floor == 16 && hero.x == 9 ? 2 : -1;
    if (special >= 0) {
        int& heard = hero.old_man_heard[special];
        if (heard)
            message = 86;
        else {
            heard = inventory(Item::WisdomOrb) ? 2 : 1;
            if (hero.floor == 3) {
                inventory(Item::HeroOrb) = 2;
                push(Op::Wait);
                push(Op::UpdateInventory);
                push(Op::Wait);
                push(Op::Sound, SoundCue::Get);
                push(Op::Wait);
                push(Op::Message, 11);
            }
        }
    }
    if (hero.floor == 23) {
        push(Op::Wait);
        push(Op::Dialogue, 61);
        waits(2);
        return;
    }
    dialogue = Dialogue{std::string(original_dialogue(message)), 0, false, {}};
}
void Game::continue_original(int stage) {
    if (stage > 10 && stage < 68)
        hero.dialogue_seen[stage] = 1;
    switch (stage) {
    case 0:
        if (inventory(Item::HeroOrb) == 2)
            inventory(Item::HeroOrb) = 1;
        break;
    case 13:
        visual.battle = false;
        commands.clear();
        break;
    case 14:
        push(Op::Wait);
        push(Op::MoveTile, 66, 77);
        push(Op::Wait);
        push(Op::MoveTile, 67, 66);
        push(Op::Wait);
        push(Op::MoveTile, 68, 67);
        break;
    case 15:
        push(Op::Wait);
        push(Op::SetTile, 99, Road);
        push(Op::Wait);
        push(Op::Sound, SoundCue::Get);
        push(Op::Wait);
        push(Op::MoveTile, 88, 99);
        push(Op::Wait);
        push(Op::MoveTile, 77, 88);
        break;
    case 16:
        tile(35, 103) = Thief;
        tile(35, 91) = Road;
        break;
    case 20:
        capture();
        break;
    default:
        break;
    }
}
void Game::speak_thief() {
    // touzoku, 0x465900. Speaker position and hero position are distinct inputs.
    switch (hero.floor) {
    case 2:
        if (hero.x == 0) {
            push(Op::Wait);
            push(Op::Dialogue, 5);
        } else if (hero.x == 2 || hero.x == 3) {
            push(Op::Wait);
            push(Op::Dialogue, 4);
            push(Op::Wait);
            push(Op::Message, 1);
            push(Op::Wait);
            push(Op::DoorFrame, 67, DoorMotion::LowerWall);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            change_music_for_floor();
        } else if (hero.x == 9 || hero.x == 10) {
            push(Op::Wait);
            push(Op::Dialogue, hero.dialogue_seen[16] ? 7 : 6);
        }
        break;
    case 15:
        push(Op::Wait);
        push(Op::SetTile, 6, Road);
        push(Op::Wait);
        push(Op::Sound, SoundCue::Get);
        push(Op::Wait);
        push(Op::MoveTile, 7, 6);
        push(Op::Wait);
        push(Op::MoveTile, 8, 7);
        push(Op::Wait);
        push(Op::Dialogue, 18);
        push(Op::Wait);
        push(Op::DoorFrame, 7, DoorMotion::LowerWall);
        expand_door();
        push(Op::Wait);
        push(Op::Sound, SoundCue::Open);
        waits(2);
        break;
    case 29:
        push(Op::Wait);
        push(Op::Dialogue, cell(hero.x, hero.y) == 27 ? 27 : hero.dialogue_seen[38] ? 29 : 28);
        break;
    case 35:
        tile(2, 120) = Road;
        push(Op::Wait);
        push(Op::Dialogue, hero.dialogue_seen[42] ? 33 : 32);
        break;
    case 50:
        push(Op::Wait);
        push(Op::Dialogue, 264);
        break;
    }
}
void Game::speak_fairy() {
    const int scale = hero.cycle_factor_minus_one + 1;
    const int keys = hero.yellow_keys + 2 * hero.blue_keys + 3 * hero.red_keys;
    int score = 0, category = 0, target = contact_index, speech = 0;
    switch (hero.floor) {
    case 10:
        score = (hero.hp - 400 * scale) / 50 + 60 + 3 * hero.attack - 157 * scale + 2 * hero.defense + keys;
        category = 1;
        target = 27;
        speech = 16;
        break;
    case 20:
        score = (hero.hp - 800 * scale) / 100 + 60 + 2 * hero.attack - 228 * scale + hero.defense + keys;
        category = 2;
        target = 49;
        speech = 22;
        break;
    case 25:
    case 49:
        score = (hero.hp - 3000 * scale) / 400 + 60 + (hero.attack - 240 * scale) / 2 +
                (hero.defense - 300 * scale) / 3 + keys;
        category = hero.floor == 25 ? 3 : 5;
        target = hero.floor == 25 ? 71 : 16;
        speech = hero.floor == 25 ? 24 : 47;
        break;
    case 40:
        score = (hero.hp - 1600 * scale) / 200 + 60 + hero.attack - 152 * scale +
                (hero.defense - 198 * scale) / 2 + keys;
        category = 4;
        target = 60;
        speech = 40;
        break;
    default:
        return;
    }
    ++hero.fairy_visits;
    hero.fairy_score = std::max(0, score);
    hero.fairy_rank = 0;
    hero.fairy_category = category;
    checkpoint_requested = true;
    // Default original rankings. Ties preserve the odd ATK+DEF-HP comparison at 0x479EAF.
    for (int row = 0; row < 10; ++row) {
        const int threshold = 100 - row * 10;
        const int hp = (10 - row) * (category == 1 ? 50 : category == 2 ? 100 : category == 4 ? 500 : 1000);
        const int attack = category == 1   ? 25 - row
                           : category == 2 ? 50 - row * 5
                           : category == 4 ? 200 - row * 10
                                           : 500 - row * 50;
        if (hero.fairy_score > threshold ||
            (hero.fairy_score == threshold &&
             (hero.hp > hp || (hero.hp == hp && hero.attack + hero.defense - hp > attack)))) {
            hero.fairy_rank = row + 1;
            break;
        }
    }
    if (hero.music_track) {
        hero.music_track = 12;
        push(Op::FloorMusic);
    }
    push(Op::SetTile, target, Road);
    push(Op::Wait);
    push(Op::Sound, SoundCue::Get);
    waits(3);
    push(Op::Dialogue, speech);
    waits(2);
    status = "Fairy score: " + std::to_string(hero.fairy_score) +
             ". Rank: " + (hero.fairy_rank ? std::to_string(hero.fairy_rank) : "unranked") + ".";
}
} // namespace baseline
