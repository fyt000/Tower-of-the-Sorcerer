#include "tsw/dialogue_ids.hpp"
#include "tsw/game.hpp"
#include <algorithm>
#include <format>

namespace tsw {
namespace {
struct MerchantOffer {
    // hint is a wisdom_hints slot; -1 means no hint, 29 is the 2F rescue response.
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
    for (int i = 0; i < std::ssize(Merchants); ++i) {
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
        HintState& heard = shop_hint_ == 29 ? hero.merchant2_heard : hero.wisdom_hints[shop_hint_];
        const bool first = heard == HintState::Unheard;
        if (first)
            heard = inventory(Item::WisdomOrb) ? HintState::Recorded : HintState::Heard;
        const auto message = shop_hint_ == 29 ? DialogueId::MerchantRescueThanks
                             : first          ? DialogueId::WisdomHintBase + shop_hint_
                                              : DialogueId::NoMoreAdvice;
        dialogue = Dialogue{std::string(original_dialogue(message)), ContinuationStage::None, false, {}};
        return;
    }
    shop_kind_ = ShopKind::Merchant;
    shop_cost_ = offer.cost;
    shop_npc_cell_ = contact_index;
    dialogue = Dialogue{std::string(original_dialogue(DialogueId::MerchantOfferBase + shop_id_)),
                        ContinuationStage::None,
                        true,
                        {"Accept the trade", "", ""}};
}

bool Game::choose(int choice) {
    if (!dialogue || !dialogue->shop)
        return false;
    if (choice < 0) {
        dialogue.reset();
        shop_kind_ = ShopKind::None;
        return true;
    }
    if (hero.gold < shop_cost_) {
        status = "You do not have enough gold.";
        return false;
    }
    if (shop_kind_ == ShopKind::Altar) {
        if (choice > std::to_underlying(AltarUpgrade::Defense))
            return false;
        const int scale = hero.cycle_factor_minus_one + 1, area = (hero.floor + 10) / 10;
        switch (static_cast<AltarUpgrade>(choice)) {
        case AltarUpgrade::HitPoints: {
            const int gain = 100 * (hero.altar_purchases + 1) * scale;
            prepared_status_ = {DialogueId::AltarHitPoints, gain};
            hero.hp += gain;
            break;
        }
        case AltarUpgrade::Attack: {
            const int gain = 2 * area * scale;
            prepared_status_ = {DialogueId::AltarAttack, gain};
            hero.attack += gain;
            break;
        }
        case AltarUpgrade::Defense: {
            const int gain = 4 * area * scale;
            prepared_status_ = {DialogueId::AltarDefense, gain};
            hero.defense += gain;
            break;
        }
        }
        hero.gold -= shop_cost_;
        ++hero.altar_purchases;
    } else if (shop_kind_ == ShopKind::Merchant) {
        if (choice != std::to_underlying(MerchantChoice::Accept))
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
    const bool altar = shop_kind_ == ShopKind::Altar;
    dialogue.reset();
    shop_kind_ = ShopKind::None;
    if (altar) {
        push(Op::Wait);
        push(Op::Message, msg::Prepared);
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
    int hint = -1;
    auto message = DialogueId::NoMoreAdvice;
    // roujin, 0x449708. First-hearing state never upgrades retrospectively.
    switch (hero.floor) {
    case 2:
        message = DialogueId::OldManRescueReward;
        if (!hero.speech_seen(SpeechId::OldManRescueReward)) {
            hero.speech_seen(SpeechId::OldManRescueReward) = 1;
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
        message = DialogueId::OldManHeroOrb;
        break;
    case 4:
        hint = 0;
        break;
    case 6:
        hint = 1;
        break;
    case 16:
        if (hero.x == 9) {
            message = DialogueId::OldManElixir;
            if (!hero.speech_seen(SpeechId::OldManElixir)) {
                hero.speech_seen(SpeechId::OldManElixir) = 1;
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
        message = DialogueId::ZenoDefeated;
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
        if (hero.wisdom_hints[hint] != HintState::Unheard)
            message = DialogueId::OldManFinished;
        else {
            hero.wisdom_hints[hint] = inventory(Item::WisdomOrb) ? HintState::Recorded : HintState::Heard;
            message = DialogueId::WisdomHintBase + hint;
        }
    }
    const int special = hero.floor == 2 ? 0 : hero.floor == 3 ? 1 : hero.floor == 16 && hero.x == 9 ? 2 : -1;
    if (special >= 0) {
        HintState& heard = hero.old_man_heard[special];
        if (heard != HintState::Unheard)
            message = DialogueId::OldManFinished;
        else {
            heard = inventory(Item::WisdomOrb) ? HintState::Recorded : HintState::Heard;
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
        queue_speech(SpeechId::OldManFloor23);
        waits(2);
        return;
    }
    dialogue = Dialogue{std::string(original_dialogue(message)), ContinuationStage::None, false, {}};
}

void Game::continue_original(ContinuationStage stage) {
    if (std::to_underlying(stage) > 10 && stage <= ContinuationStage::LastSaved)
        hero.dialogue_seen[std::to_underlying(stage)] = 1;
    switch (stage) {
    case ContinuationStage::None:
        if (inventory(Item::HeroOrb) == 2)
            inventory(Item::HeroOrb) = 1;
        break;
    case ContinuationStage::WakeUpComplete:
        visual.battle = false;
        commands.clear();
        hero.highest_floor_stair_kind = StairKind::None; // 0x44DA10 redraws the map here.
        break;
    case ContinuationStage::ThiefOpensPrison:
        push(Op::Wait);
        push(Op::MoveTile, 66, 77);
        push(Op::Wait);
        push(Op::MoveTile, 67, 66);
        push(Op::Wait);
        push(Op::MoveTile, 68, 67);
        break;
    case ContinuationStage::ThiefFirstDeparture:
        push(Op::Wait);
        push(Op::SetTile, 99, Road);
        push(Op::Wait);
        push(Op::Sound, SoundCue::Get);
        push(Op::Wait);
        push(Op::MoveTile, 88, 99);
        push(Op::Wait);
        push(Op::MoveTile, 77, 88);
        break;
    case ContinuationStage::ThiefMovesToFloor35:
        tile(35, 103) = Thief;
        tile(35, 91) = Road;
        break;
    case ContinuationStage::Capture:
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
            queue_speech(SpeechId::ThiefFirstDeparture);
        } else if (hero.x == 2 || hero.x == 3) {
            prepared_status_ = {DialogueId::SecretPassage};
            message_code = msg::Prepared;
            push(Op::Wait);
            queue_speech(SpeechId::ThiefOpensPrison);
            push(Op::Wait);
            push(Op::Message, msg::Prepared);
            push(Op::Wait);
            push(Op::DoorFrame, 67, DoorMotion::LowerWall);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            change_music_for_floor();
        } else if (hero.x == 9 || hero.x == 10) {
            push(Op::Wait);
            queue_speech(hero.speech_seen(SpeechId::ThiefReturnsToPrison) ? SpeechId::ThiefPromisesToFollow
                                                                          : SpeechId::ThiefReturnsToPrison);
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
        queue_speech(SpeechId::ThiefOctopusTunnel);
        push(Op::Wait);
        push(Op::DoorFrame, 7, DoorMotion::LowerWall);
        expand_door();
        push(Op::Wait);
        push(Op::Sound, SoundCue::Open);
        waits(2);
        break;
    case 29:
        push(Op::Wait);
        queue_speech(cell(hero.x, hero.y) == 27                        ? SpeechId::ThiefUnfinishedTunnel
                     : hero.speech_seen(SpeechId::ThiefFinishedTunnel) ? SpeechId::ThiefWarnsAboutBoss
                                                                       : SpeechId::ThiefFinishedTunnel);
        break;
    case 35:
        tile(2, 120) = Road;
        push(Op::Wait);
        queue_speech(hero.speech_seen(SpeechId::ThiefDragonTunnel) ? SpeechId::ThiefGoldenKnightAdvice
                                                                   : SpeechId::ThiefDragonTunnel);
        break;
    case 50:
        push(Op::Wait);
        queue_speech(SpeechId::ThiefTimeGate);
        break;
    }
}

void Game::speak_fairy() {
    const int scale = hero.cycle_factor_minus_one + 1;
    const int keys = hero.yellow_keys + 2 * hero.blue_keys + 3 * hero.red_keys;
    int score = 0, target = contact_index;
    SpeechId speech{};
    FairyCategory category = FairyCategory::None;
    switch (hero.floor) {
    case 10:
        score = (hero.hp - 400 * scale) / 50 + 60 + 3 * hero.attack - 157 * scale + 2 * hero.defense + keys;
        category = FairyCategory::Floor10;
        target = 27;
        speech = SpeechId::FairyFloor10;
        break;
    case 20:
        score = (hero.hp - 800 * scale) / 100 + 60 + 2 * hero.attack - 228 * scale + hero.defense + keys;
        category = FairyCategory::Floor20;
        target = 49;
        speech = SpeechId::FairyFloor20;
        break;
    case 25:
    case 49:
        score = (hero.hp - 3000 * scale) / 400 + 60 + (hero.attack - 240 * scale) / 2 +
                (hero.defense - 300 * scale) / 3 + keys;
        category = hero.floor == 25 ? FairyCategory::Floor25 : FairyCategory::Floor49;
        target = hero.floor == 25 ? 71 : 16;
        speech = hero.floor == 25 ? SpeechId::FairyFloor25 : SpeechId::FairyFloor49;
        break;
    case 40:
        score = (hero.hp - 1600 * scale) / 200 + 60 + hero.attack - 152 * scale +
                (hero.defense - 198 * scale) / 2 + keys;
        category = FairyCategory::Floor40;
        target = 60;
        speech = SpeechId::FairyFloor40;
        break;
    default:
        return;
    }
    ++hero.fairy_visits;
    hero.fairy_score = std::max(0, score);
    hero.fairy_rank = ranking_position(rankings.at(std::to_underlying(category) - 1),
                                       {hero.fairy_score, hero.hp, hero.attack, hero.defense, {}});
    hero.fairy_category = category;
    checkpoint_requested = true;
    if (music_enabled(hero.music_track)) {
        hero.music_track = MusicTrack::Fairy;
        push(Op::FloorMusic);
    }
    push(Op::SetTile, target, Road);
    push(Op::Wait);
    push(Op::Sound, SoundCue::Get);
    waits(3);
    queue_speech(speech);
    waits(2);
    status = std::format("Fairy score: {}. Rank: {}.", hero.fairy_score,
                         hero.fairy_rank ? std::to_string(hero.fairy_rank) : "unranked");
}
} // namespace tsw
