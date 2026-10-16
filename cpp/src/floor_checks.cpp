#include "tsw/game.hpp"

namespace tsw {
// Direct translation of 0x4664E4. Numeric sums intentionally preserve altered-state behavior.
void Game::check_guards() {
    int sum = 0;
    switch (hero.floor) {
    case 2:
        sum = tile_at(hero.floor, 4, 4);
        if (tile_at(hero.floor, 5, 1) + tile_at(hero.floor, 7, 1) + sum == 17) {
            push(Op::DoorFrame, cell(8, 10), DoorMotion::Prison);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            push(Op::DoorFrame, cell(4, 10), DoorMotion::Prison);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            push(Op::DoorFrame, cell(8, 7), DoorMotion::Prison);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            push(Op::DoorFrame, cell(4, 7), DoorMotion::Prison);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            push(Op::DoorFrame, cell(8, 4), DoorMotion::Prison);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            push(Op::DoorFrame, cell(4, 4), DoorMotion::Prison);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            waits(2);
        }
        break;
    case 8:
        sum = tile_at(hero.floor, 9, 3);
        if (tile_at(hero.floor, 8, 4) + tile_at(hero.floor, 10, 4) + sum == 16) {
            push(Op::DoorFrame, cell(9, 3), DoorMotion::OpenGate);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            waits(2);
        }
        break;
    case 10:
        if (tile_at(hero.floor, 4, 3) + tile_at(hero.floor, 5, 3) + tile_at(hero.floor, 6, 3) +
                tile_at(hero.floor, 4, 4) + tile_at(hero.floor, 6, 4) + tile_at(hero.floor, 4, 5) +
                tile_at(hero.floor, 5, 5) + tile_at(hero.floor, 6, 5) + tile_at(hero.floor, 5, 2) ==
            52) {
            if (hero.music_track != MusicTrack::Disabled) {
                push(Op::Wait);
                push(Op::Sound, SoundCue::MusicStart);
            }
            push(Op::DoorFrame, cell(5, 2), DoorMotion::OpenGate);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            waits(3);
            queue_speech(SpeechId::SkeletonLordBattle);
            waits(2);
        }
        sum = tile_at(hero.floor, 3, 3);
        if (tile_at(hero.floor, 5, 0) + tile_at(hero.floor, 5, 6) + tile_at(hero.floor, 7, 3) + sum == 18) {
            push(Op::Wait);
            push(Op::SetTile, cell(5, 8), SpecialRoad);
            push(Op::Wait);
            push(Op::SetTile, cell(5, 10), StairsUp);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(10, 3), YellowKey);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(9, 3), YellowKey);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(8, 3), YellowKey);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(2, 3), BluePotion);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(1, 3), BluePotion);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(0, 3), BluePotion);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(10, 2), BlueGem);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(9, 2), BlueGem);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(8, 2), BlueGem);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(2, 2), RedGem);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(1, 2), RedGem);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(0, 2), RedGem);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(5, 2), Fairy);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::DoorFrame, cell(5, 6), DoorMotion::OpenGate);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            push(Op::DoorFrame, cell(7, 3), DoorMotion::OpenGate);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            push(Op::DoorFrame, cell(3, 3), DoorMotion::OpenGate);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            waits(3);
            queue_speech(SpeechId::SkeletonLordDefeated);
            waits(2);
            if (hero.music_track != MusicTrack::Disabled) {
                push(Op::Wait);
                push(Op::Sound, SoundCue::MusicStop);
            }
        }
        break;
    case 11:
        sum = tile_at(hero.floor, 1, 3);
        if (tile_at(hero.floor, 0, 4) + tile_at(hero.floor, 2, 4) + sum == 16) {
            push(Op::DoorFrame, cell(1, 3), DoorMotion::OpenGate);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            waits(2);
        }
        break;
    case 14:
        sum = tile_at(hero.floor, 0, 2);
        if (tile_at(hero.floor, 0, 0) + tile_at(hero.floor, 2, 0) + tile_at(hero.floor, 1, 1) + sum == 26) {
            push(Op::Wait);
            push(Op::SetTile, cell(0, 2), RedKey);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            waits(2);
        }
        break;
    case 15:
        sum = tile_at(hero.floor, 5, 5) + tile_at(hero.floor, 5, 2) + tile_at(hero.floor, 5, 8);
        if (sum == 14) {
            push(Op::Wait);
            push(Op::SetTile, cell(5, 4), Mattock);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::DoorFrame, cell(5, 8), DoorMotion::OpenGate);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            push(Op::DoorFrame, cell(5, 2), DoorMotion::OpenGate);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            waits(2);
        }
        break;
    case 17:
        if (tile_at(hero.floor, 8, 4) + tile_at(hero.floor, 10, 4) + tile_at(hero.floor, 9, 3) == 16) {
            push(Op::DoorFrame, cell(9, 3), DoorMotion::OpenGate);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            waits(2);
        }
        if (tile_at(hero.floor, 8, 7) + tile_at(hero.floor, 10, 7) + tile_at(hero.floor, 9, 6) == 16) {
            push(Op::DoorFrame, cell(9, 6), DoorMotion::OpenGate);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            waits(2);
        }
        if (tile_at(hero.floor, 0, 4) + tile_at(hero.floor, 2, 4) + tile_at(hero.floor, 1, 3) == 16) {
            push(Op::DoorFrame, cell(1, 3), DoorMotion::OpenGate);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            waits(2);
        }
        sum = tile_at(hero.floor, 0, 7) + tile_at(hero.floor, 2, 7) + tile_at(hero.floor, 1, 6);
        if (sum == 16) {
            push(Op::DoorFrame, cell(1, 6), DoorMotion::OpenGate);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            waits(2);
        }
        break;
    case 20:
        sum = tile_at(hero.floor, 4, 4) + tile_at(hero.floor, 5, 4) + tile_at(hero.floor, 6, 4) +
              tile_at(hero.floor, 4, 5) + tile_at(hero.floor, 6, 5) + tile_at(hero.floor, 4, 6) +
              tile_at(hero.floor, 5, 6) + tile_at(hero.floor, 6, 6) + tile_at(hero.floor, 5, 5) +
              tile_at(hero.floor, 5, 2) + tile_at(hero.floor, 5, 8);
        if (sum == 62) {
            push(Op::Wait);
            push(Op::SetTile, cell(5, 0), StairsUp);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(6, 3), YellowKey);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(5, 3), YellowKey);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(4, 3), YellowKey);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(6, 7), BluePotion);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(5, 7), BluePotion);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(4, 7), BluePotion);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(7, 6), BlueGem);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(7, 5), BlueGem);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(7, 4), BlueGem);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(3, 6), RedGem);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(3, 5), RedGem);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(3, 4), RedGem);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(5, 4), Fairy);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            if (hero.music_track != MusicTrack::Disabled) {
                push(Op::Wait);
                push(Op::Sound, SoundCue::MusicStop);
            }
            push(Op::Wait);
            queue_speech(SpeechId::VampireDefeated);
            push(Op::DoorFrame, cell(5, 8), DoorMotion::OpenGate);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            push(Op::DoorFrame, cell(5, 2), DoorMotion::OpenGate);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            waits(2);
        }
        break;
    case 25:
        sum = tile_at(hero.floor, 5, 5) + tile_at(hero.floor, 5, 9);
        if (sum == 10) {
            if (hero.speech_seen(SpeechId::HeroFindsDoll) == 1) {
                tile_at(24, 4, 0) = Wall;
                tile_at(24, 6, 0) = Wall;
                tile_at(24, 5, 1) = Road;
                tile_at(24, 5, 2) = Road;
                tile_at(24, 5, 3) = Road;
                tile_at(24, 5, 0) = SpecialRoad;
            }
            push(Op::Wait);
            push(Op::SetTile, cell(7, 7), RedKey);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(6, 7), RedKey);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(5, 7), RedKey);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(4, 7), RedKey);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(3, 7), RedKey);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(5, 6), Fairy);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::DoorFrame, cell(5, 9), DoorMotion::OpenGate);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            waits(2);
        }
        break;
    case 30:
        sum = tile_at(hero.floor, 2, 4) + tile_at(hero.floor, 3, 4) + tile_at(hero.floor, 4, 4) +
              tile_at(hero.floor, 6, 4) + tile_at(hero.floor, 7, 4) + tile_at(hero.floor, 8, 4) +
              tile_at(hero.floor, 5, 3) + tile_at(hero.floor, 5, 6);
        if (sum == 44) {
            push(Op::Wait);
            push(Op::SetTile, cell(5, 0), StairsUp);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::DoorFrame, cell(5, 6), DoorMotion::OpenGate);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            push(Op::DoorFrame, cell(5, 3), DoorMotion::OpenGate);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            waits(2);
        }
        break;
    case 32:
        if (tile_at(hero.floor, 0, 9) + tile_at(hero.floor, 2, 9) + tile_at(hero.floor, 1, 8) == 16) {
            push(Op::DoorFrame, cell(1, 8), DoorMotion::OpenGate);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            waits(2);
        }
        sum = tile_at(hero.floor, 5, 5) + hero.speech_seen(SpeechId::GreatMagicMasterChallenge) +
              hero.speech_seen(SpeechId::GreatMagicMasterRetreat);
        if (sum == 7) {
            tile_at(29, 6, 1) = Road;
            tile_at(2, 10, 10) = Thief;
            push(Op::Wait);
            push(Op::SetTile, cell(9, 0), Road);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            waits(3);
            push(Op::MoveTile, cell(8, 0), cell(9, 0));
            waits(3);
            push(Op::MoveTile, cell(7, 0), cell(8, 0));
            waits(3);
            push(Op::MoveTile, cell(6, 0), cell(7, 0));
            waits(3);
            push(Op::MoveTile, cell(5, 0), cell(6, 0));
            waits(3);
            push(Op::MoveTile, cell(5, 1), cell(5, 0));
            waits(3);
            push(Op::MoveTile, cell(5, 2), cell(5, 1));
            waits(3);
            push(Op::MoveTile, cell(5, 3), cell(5, 2));
            waits(3);
            push(Op::MoveTile, cell(5, 4), cell(5, 3));
            waits(3);
            push(Op::MoveTile, cell(5, 5), cell(5, 4));
            waits(3);
            push(Op::MoveTile, cell(5, 6), cell(5, 5));
            waits(3);
            push(Op::MoveTile, cell(5, 7), cell(5, 6));
            waits(3);
            push(Op::MoveTile, cell(5, 8), cell(5, 7));
            waits(3);
            push(Op::MoveTile, cell(5, 9), cell(5, 8));
            push(Op::Wait);
            push(Op::WriteTile, cell(5, 9), GoldenKnight);
            waits(5);
            queue_speech(SpeechId::GreatMagicMasterRetreat);
            waits(2);
        }
        break;
    case 33:
        sum = tile_at(hero.floor, 8, 4) + tile_at(hero.floor, 10, 4) + tile_at(hero.floor, 8, 6) +
              tile_at(hero.floor, 10, 6) + tile_at(hero.floor, 9, 3) + tile_at(hero.floor, 9, 7);
        if (sum == 32) {
            push(Op::DoorFrame, cell(9, 7), DoorMotion::OpenGate);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            push(Op::DoorFrame, cell(9, 3), DoorMotion::OpenGate);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            waits(2);
        }
        break;
    case 34:
        sum = tile_at(hero.floor, 4, 3) + tile_at(hero.floor, 6, 3) + tile_at(hero.floor, 8, 3) +
              tile_at(hero.floor, 10, 3) + tile_at(hero.floor, 4, 7) + tile_at(hero.floor, 6, 7) +
              tile_at(hero.floor, 8, 7) + tile_at(hero.floor, 10, 7);
        if ((sum == 48) && (hero.floor34_reward_created == 0)) {
            hero.floor34_reward_created = 1;
            push(Op::Wait);
            push(Op::SetTile, cell(2, 6), YellowKey);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(0, 6), YellowKey);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(2, 4), YellowKey);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(0, 4), YellowKey);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(1, 5), RedKey);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            waits(2);
        }
        break;
    case 35:
        sum = tile_at(hero.floor, 5, 6) + tile_at(hero.floor, 5, 2);
        if ((sum == 10) && (hero.floor35_reward_created == 0)) {
            hero.floor35_reward_created = 1;
            push(Op::Wait);
            push(Op::SetTile, cell(6, 4), BluePotion);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(5, 4), BluePotion);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(4, 4), BluePotion);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(5, 5), SnowCrystal);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::DoorFrame, cell(5, 2), DoorMotion::OpenGate);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            waits(2);
        }
        break;
    case 38:
        sum = tile_at(hero.floor, 0, 9) + tile_at(hero.floor, 2, 9);
        if (sum == 12) {
            tile_at(hero.floor, 1, 8) = SecretWall;
        }
        break;
    case 40:
        sum = tile_at(hero.floor, 5, 1) + tile_at(hero.floor, 5, 0);
        if ((sum == 17) && (hero.floor40_reward_created == 0)) {
            hero.floor40_reward_created = 1;
            push(Op::Wait);
            push(Op::SetTile, cell(8, 3), YellowKey);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(7, 3), YellowKey);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(6, 3), YellowKey);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(4, 3), BluePotion);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(3, 3), BluePotion);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(2, 3), BluePotion);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(9, 1), BlueGem);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(8, 1), BlueGem);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(7, 1), BlueGem);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(3, 1), RedGem);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(2, 1), RedGem);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(1, 1), RedGem);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(5, 5), Fairy);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            waits(2);
            if (hero.music_track != MusicTrack::Disabled) {
                push(Op::Wait);
                push(Op::Sound, SoundCue::MusicStop);
            }
        }
        break;
    case 41:
        sum = tile_at(hero.floor, 1, 1) + tile_at(hero.floor, 9, 1);
        if ((sum == 12) && (hero.floor41_reward_created == 0)) {
            hero.floor41_reward_created = 1;
            push(Op::Wait);
            push(Op::SetTile, cell(5, 4), DescentWing);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(6, 6), Road);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            push(Op::Wait);
            push(Op::SetTile, cell(4, 6), Road);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            push(Op::Wait);
            push(Op::SetTile, cell(6, 5), Wall);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            push(Op::Wait);
            push(Op::SetTile, cell(5, 5), Wall);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            push(Op::Wait);
            push(Op::SetTile, cell(4, 5), Wall);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            waits(2);
        }
        break;
    case 44:
        sum = tile_at(hero.floor, 4, 8) + tile_at(hero.floor, 6, 8) + tile_at(hero.floor, 5, 7);
        if (sum == 16) {
            push(Op::DoorFrame, cell(5, 7), DoorMotion::OpenGate);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            waits(2);
        }
        break;
    case 45:
        if (tile_at(hero.floor, 4, 8) + tile_at(hero.floor, 4, 10) + tile_at(hero.floor, 3, 9) == 16) {
            push(Op::DoorFrame, cell(3, 9), DoorMotion::OpenGate);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            waits(2);
        }
        sum = tile_at(hero.floor, 7, 8) + tile_at(hero.floor, 7, 10) + tile_at(hero.floor, 6, 9);
        if (sum == 16) {
            push(Op::DoorFrame, cell(6, 9), DoorMotion::OpenGate);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            waits(2);
        }
        break;
    case 48:
        sum = tile_at(hero.floor, 0, 0) + tile_at(hero.floor, 7, 7);
        if (sum == 10) {
            push(Op::DoorFrame, cell(7, 7), DoorMotion::OpenGate);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            waits(2);
        }
        break;
    case 49:
        if (tile_at(hero.floor, 4, 9) + tile_at(hero.floor, 6, 9) + tile_at(hero.floor, 5, 8) == 16) {
            push(Op::DoorFrame, cell(5, 8), DoorMotion::OpenGate);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            waits(2);
        }
        if (tile_at(hero.floor, 4, 7) + tile_at(hero.floor, 6, 7) + tile_at(hero.floor, 5, 6) +
                tile_at(hero.floor, 5, 5) ==
            23) {
            push(Op::DoorFrame, cell(5, 6), DoorMotion::OpenGate);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            waits(2);
        }
        if ((tile_at(hero.floor, 5, 1) + tile_at(hero.floor, 4, 2) + tile_at(hero.floor, 6, 2) +
                 tile_at(hero.floor, 5, 3) ==
             24) &&
            (tile_at(hero.floor, 4, 1) + tile_at(hero.floor, 6, 1) + tile_at(hero.floor, 4, 3) +
                 tile_at(hero.floor, 6, 3) ==
             372)) {
            if (hero.zeno_sealed == 0) {
                hero.zeno_sealed = 1;
                monsters[ZenoRow].hp = monsters[ZenoRow].hp / 10;
                monsters[ZenoRow].attack = monsters[ZenoRow].attack / 10;
                monsters[ZenoRow].defense = monsters[ZenoRow].defense / 10;
            }
            if (hero.music_track != MusicTrack::Disabled) {
                push(Op::Wait);
                push(Op::Sound, SoundCue::MusicStart);
            }
            push(Op::Wait);
            queue_speech(SpeechId::ZenoDefeated);
            if (hero.music_track != MusicTrack::Disabled) {
                push(Op::Wait);
                push(Op::Sound, SoundCue::MusicStop);
            }
            waits(2);
        }
        sum = tile_at(hero.floor, 5, 2) + tile_at(hero.floor, 5, 6) + tile_at(hero.floor, 5, 5);
        if (sum == 16) {
            // The original overwrites the pending seal speech with its loot stack.
            commands.clear();
            push(Op::Wait);
            push(Op::SetTile, cell(6, 1), DragonSlayer);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(4, 1), RedKey);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(9, 3), BlueGem);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(8, 3), BlueGem);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(7, 3), BlueGem);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(3, 3), RedGem);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(2, 3), RedGem);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(1, 3), RedGem);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(6, 4), BluePotion);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(5, 4), BluePotion);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(4, 4), BluePotion);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::SetTile, cell(5, 1), Fairy);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::DoorFrame, cell(5, 6), DoorMotion::OpenGate);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            push(Op::SetTile, cell(6, 3), Road);
            push(Op::SetTile, cell(4, 3), Road);
            push(Op::SetTile, cell(6, 1), Road);
            push(Op::SetTile, cell(4, 1), Road);
            waits(2);
            if (hero.music_track != MusicTrack::Disabled) {
                push(Op::Wait);
                push(Op::Sound, SoundCue::MusicStop);
            }
        }
        break;
    case 50:
        if (hero.cycle_factor_minus_one != 0) {
            push(Op::Wait);
            push(Op::Callback, Callback::NextCycle, 0);
            queue_raster(RasterMode::EndingDissolve, 247);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            queue_raster(RasterMode::EndingDissolve, 246);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            queue_raster(RasterMode::EndingDissolve, 245);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            queue_raster(RasterMode::EndingDissolve, 244);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            queue_raster(RasterMode::EndingDissolve, 243);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            queue_raster(RasterMode::EndingDissolve, 242);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            queue_raster(RasterMode::EndingDissolve, 241);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            queue_raster(RasterMode::EndingDissolve, 240);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            queue_raster(RasterMode::EndingDissolve, 239);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            queue_raster(RasterMode::EndingDissolve, 238);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            queue_raster(RasterMode::EndingDissolve, 237);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            queue_raster(RasterMode::EndingDissolve, 236);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            queue_raster(RasterMode::EndingDissolve, 235);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            queue_raster(RasterMode::EndingDissolve, 234);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            queue_raster(RasterMode::EndingDissolve, 233);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            queue_raster(RasterMode::EndingDissolve, 232);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            push(Op::Wait);
            push(Op::Callback, Callback::CacheScene, 0);
            push(Op::Wait);
            push(Op::Callback, Callback::HidePanels, 0);
            push(Op::Wait);
            push(Op::Callback, Callback::HideHero, 0);
            push(Op::Wait);
            push(Op::Message, 140, 0);
            waits(3);
            queue_speech(SpeechId::BacksideZenoDefeated, 99);
        }
    }
    return;
}
} // namespace tsw
