#include "baseline/game.hpp"
namespace baseline {
// 0x46CB1C, switch targets recovered by RecoverArrival.java.
void Game::check_floor() {
    if (hero.floor >= 10 && hero.floor < 50) {
        switch (hero.floor) {
        case 10:
            if (hero.dialogue_seen[26] == 0) {
                if (hero.music_track != 0) {
                    hero.music_track = 15;
                    push(Op::Wait);
                    push(Op::Sound, SoundCue::MusicStart);
                }
                push(Op::DoorFrame, cell(7, 3), DoorMotion::CloseGate);
                expand_door();
                push(Op::Wait);
                push(Op::Sound, SoundCue::Open);
                push(Op::DoorFrame, cell(3, 3), DoorMotion::CloseGate);
                expand_door();
                push(Op::Wait);
                push(Op::Sound, SoundCue::Open);
                waits(5);
                push(Op::Sound, SoundCue::Zeno);
                push(Op::Wait);
                push(Op::MoveTile, cell(7, 3), cell(6, 3));
                waits(3);
                push(Op::Sound, SoundCue::Zeno);
                push(Op::Wait);
                push(Op::MoveTile, cell(8, 3), cell(7, 3));
                waits(3);
                push(Op::Sound, SoundCue::Zeno);
                push(Op::Wait);
                push(Op::MoveTile, cell(9, 3), cell(8, 3));
                waits(3);
                push(Op::Sound, SoundCue::Zeno);
                push(Op::Wait);
                push(Op::MoveTile, cell(10, 3), cell(9, 3));
                waits(3);
                push(Op::Sound, SoundCue::Zeno);
                push(Op::Wait);
                push(Op::MoveTile, cell(10, 2), cell(10, 3));
                waits(3);
                push(Op::Sound, SoundCue::Zeno);
                push(Op::Wait);
                push(Op::MoveTile, cell(3, 3), cell(4, 3));
                waits(3);
                push(Op::Sound, SoundCue::Zeno);
                push(Op::Wait);
                push(Op::MoveTile, cell(2, 3), cell(3, 3));
                waits(3);
                push(Op::Sound, SoundCue::Zeno);
                push(Op::Wait);
                push(Op::MoveTile, cell(1, 3), cell(2, 3));
                waits(3);
                push(Op::Sound, SoundCue::Zeno);
                push(Op::Wait);
                push(Op::MoveTile, cell(0, 3), cell(1, 3));
                waits(3);
                push(Op::Sound, SoundCue::Zeno);
                push(Op::Wait);
                push(Op::MoveTile, cell(0, 2), cell(0, 3));
                waits(3);
                push(Op::Sound, SoundCue::Zeno);
                push(Op::Wait);
                push(Op::MoveTile, cell(6, 3), cell(6, 4));
                waits(3);
                push(Op::Sound, SoundCue::Zeno);
                push(Op::Wait);
                push(Op::MoveTile, cell(7, 3), cell(6, 3));
                waits(3);
                push(Op::Sound, SoundCue::Zeno);
                push(Op::Wait);
                push(Op::MoveTile, cell(8, 3), cell(7, 3));
                waits(3);
                push(Op::Sound, SoundCue::Zeno);
                push(Op::Wait);
                push(Op::MoveTile, cell(9, 3), cell(8, 3));
                waits(3);
                push(Op::Sound, SoundCue::Zeno);
                push(Op::Wait);
                push(Op::MoveTile, cell(9, 2), cell(9, 3));
                waits(3);
                push(Op::Sound, SoundCue::Zeno);
                push(Op::Wait);
                push(Op::MoveTile, cell(4, 3), cell(4, 4));
                waits(3);
                push(Op::Sound, SoundCue::Zeno);
                push(Op::Wait);
                push(Op::MoveTile, cell(3, 3), cell(4, 3));
                waits(3);
                push(Op::Sound, SoundCue::Zeno);
                push(Op::Wait);
                push(Op::MoveTile, cell(2, 3), cell(3, 3));
                waits(3);
                push(Op::Sound, SoundCue::Zeno);
                push(Op::Wait);
                push(Op::MoveTile, cell(1, 3), cell(2, 3));
                waits(3);
                push(Op::Sound, SoundCue::Zeno);
                push(Op::Wait);
                push(Op::MoveTile, cell(1, 2), cell(1, 3));
                waits(3);
                push(Op::Sound, SoundCue::Zeno);
                push(Op::Wait);
                push(Op::MoveTile, cell(6, 4), cell(6, 5));
                waits(3);
                push(Op::Sound, SoundCue::Zeno);
                push(Op::Wait);
                push(Op::MoveTile, cell(6, 3), cell(6, 4));
                waits(3);
                push(Op::Sound, SoundCue::Zeno);
                push(Op::Wait);
                push(Op::MoveTile, cell(7, 3), cell(6, 3));
                waits(3);
                push(Op::Sound, SoundCue::Zeno);
                push(Op::Wait);
                push(Op::MoveTile, cell(8, 3), cell(7, 3));
                waits(3);
                push(Op::Sound, SoundCue::Zeno);
                push(Op::Wait);
                push(Op::MoveTile, cell(8, 2), cell(8, 3));
                waits(3);
                push(Op::Sound, SoundCue::Zeno);
                push(Op::Wait);
                push(Op::MoveTile, cell(4, 4), cell(4, 5));
                waits(3);
                push(Op::Sound, SoundCue::Zeno);
                push(Op::Wait);
                push(Op::MoveTile, cell(4, 3), cell(4, 4));
                waits(3);
                push(Op::Sound, SoundCue::Zeno);
                push(Op::Wait);
                push(Op::MoveTile, cell(3, 3), cell(4, 3));
                waits(3);
                push(Op::Sound, SoundCue::Zeno);
                push(Op::Wait);
                push(Op::MoveTile, cell(2, 3), cell(3, 3));
                waits(3);
                push(Op::Sound, SoundCue::Zeno);
                push(Op::Wait);
                push(Op::MoveTile, cell(2, 2), cell(2, 3));
                waits(3);
                push(Op::Sound, SoundCue::Zeno);
                push(Op::Wait);
                push(Op::MoveTile, cell(6, 3), cell(5, 3));
                waits(3);
                push(Op::Sound, SoundCue::Zeno);
                push(Op::Wait);
                push(Op::MoveTile, cell(7, 3), cell(6, 3));
                waits(3);
                push(Op::Sound, SoundCue::Zeno);
                push(Op::Wait);
                push(Op::MoveTile, cell(8, 3), cell(7, 3));
                waits(3);
                push(Op::Sound, SoundCue::Zeno);
                push(Op::Wait);
                push(Op::MoveTile, cell(9, 3), cell(8, 3));
                waits(3);
                push(Op::Sound, SoundCue::Zeno);
                push(Op::Wait);
                push(Op::MoveTile, cell(4, 5), cell(5, 5));
                waits(3);
                push(Op::Sound, SoundCue::Zeno);
                push(Op::Wait);
                push(Op::MoveTile, cell(4, 4), cell(4, 5));
                waits(3);
                push(Op::Sound, SoundCue::Zeno);
                push(Op::Wait);
                push(Op::MoveTile, cell(4, 3), cell(4, 4));
                waits(3);
                push(Op::Sound, SoundCue::Zeno);
                push(Op::Wait);
                push(Op::MoveTile, cell(3, 3), cell(4, 3));
                waits(3);
                push(Op::Sound, SoundCue::Zeno);
                push(Op::Wait);
                push(Op::MoveTile, cell(2, 3), cell(3, 3));
                waits(3);
                push(Op::Sound, SoundCue::Zeno);
                push(Op::Wait);
                push(Op::MoveTile, cell(1, 3), cell(2, 3));
                push(Op::DoorFrame, cell(7, 3), DoorMotion::OpenGate);
                expand_door();
                push(Op::Wait);
                push(Op::Sound, SoundCue::Open);
                push(Op::DoorFrame, cell(3, 3), DoorMotion::OpenGate);
                expand_door();
                push(Op::Wait);
                push(Op::Sound, SoundCue::Open);
                push(Op::DoorFrame, cell(5, 6), DoorMotion::CloseGate);
                expand_door();
                push(Op::Wait);
                push(Op::Sound, SoundCue::Open);
                push(Op::DoorFrame, cell(5, 2), DoorMotion::CloseGate);
                expand_door();
                push(Op::Wait);
                push(Op::Sound, SoundCue::Open);
                push(Op::Wait);
                push(Op::MoveTile, cell(5, 1), cell(5, 0));
                push(Op::Wait);
                push(Op::MoveTile, cell(5, 2), cell(5, 1));
                push(Op::Wait);
                push(Op::MoveTile, cell(5, 3), cell(5, 2));
                push(Op::Wait);
                push(Op::SetTile, cell(6, 5), Road);
                push(Op::Wait);
                push(Op::Sound, SoundCue::Get);
                push(Op::Wait);
                push(Op::SetTile, cell(4, 5), Road);
                push(Op::Wait);
                push(Op::Sound, SoundCue::Get);
                push(Op::Wait);
                push(Op::Dialogue, 13, 0);
                if (hero.music_track != 0) {
                    push(Op::Wait);
                    push(Op::Sound, SoundCue::MusicStop);
                }
            } else {
                push(Op::Wait);
                push(Op::SetTile, cell(5, 9), Road);
                push(Op::Wait);
                push(Op::Sound, SoundCue::Get);
                push(Op::Wait);
                push(Op::Dialogue, 17, 0);
                push(Op::Wait);
                push(Op::MoveTile, cell(4, 9), cell(5, 9));
                push(Op::Wait);
                push(Op::MoveTile, cell(4, 10), cell(4, 9));
                push(Op::Wait);
                push(Op::MoveTile, cell(3, 10), cell(4, 10));
                push(Op::Wait);
                push(Op::MoveTile, cell(2, 10), cell(3, 10));
                push(Op::Wait);
                push(Op::MoveTile, cell(2, 9), cell(2, 10));
                push(Op::Wait);
                push(Op::MoveTile, cell(2, 8), cell(2, 9));
                push(Op::Wait);
                push(Op::MoveTile, cell(2, 7), cell(2, 8));
                push(Op::Wait);
                push(Op::MoveTile, cell(1, 7), cell(2, 7));
                push(Op::Wait);
                push(Op::MoveTile, cell(0, 7), cell(1, 7));
                push(Op::Wait);
                push(Op::MoveTile, cell(0, 8), cell(0, 7));
                push(Op::Wait);
                push(Op::MoveTile, cell(0, 9), cell(0, 8));
                push(Op::Wait);
                push(Op::SetTile, cell(0, 9), Thief);
                push(Op::Wait);
                push(Op::Sound, SoundCue::Get);
            }
            break;
        case 15:
            push(Op::DoorFrame, cell(5, 8), DoorMotion::CloseGate);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, 1, 5);
            waits(2);
            break;
        case 20:
            if (hero.music_track != 0) {
                push(Op::Wait);
                push(Op::Sound, SoundCue::MusicStart);
            }
            tile_at(hero.floor, 4, 4) = Road;
            tile_at(hero.floor, 5, 4) = Road;
            tile_at(hero.floor, 6, 4) = Road;
            tile_at(hero.floor, 4, 5) = Road;
            tile_at(hero.floor, 6, 5) = Road;
            tile_at(hero.floor, 4, 6) = Road;
            tile_at(hero.floor, 5, 6) = Road;
            tile_at(hero.floor, 6, 6) = Road;
            tile_at(hero.floor, 5, 5) = Vampire;
            push(Op::Wait);
            push(Op::Dialogue, 20, 0);
            push(Op::Wait);
            push(Op::Callback, Callback::Transformation, 32);
            push(Op::Wait);
            push(Op::Callback, Callback::Transformation, 31);
            push(Op::Wait);
            push(Op::Callback, Callback::Transformation, 30);
            push(Op::Wait);
            push(Op::Callback, Callback::Transformation, 29);
            push(Op::Wait);
            push(Op::Callback, Callback::Transformation, 28);
            push(Op::Wait);
            push(Op::Callback, Callback::Transformation, 27);
            push(Op::Wait);
            push(Op::Callback, Callback::Transformation, 26);
            push(Op::Wait);
            push(Op::Callback, Callback::Transformation, 25);
            push(Op::Wait);
            push(Op::Callback, Callback::Transformation, 24);
            push(Op::Wait);
            push(Op::Callback, Callback::Transformation, 23);
            push(Op::Wait);
            push(Op::Callback, Callback::Transformation, 22);
            push(Op::Wait);
            push(Op::Callback, Callback::Transformation, 21);
            push(Op::Wait);
            push(Op::Callback, Callback::Transformation, 20);
            push(Op::Wait);
            push(Op::Callback, Callback::Transformation, 19);
            push(Op::Wait);
            push(Op::Callback, Callback::Transformation, 18);
            push(Op::Wait);
            push(Op::Callback, Callback::Transformation, 17);
            push(Op::Wait);
            push(Op::Callback, Callback::Transformation, 16);
            push(Op::Wait);
            push(Op::Callback, Callback::Transformation, 15);
            push(Op::Wait);
            push(Op::Callback, Callback::Transformation, 14);
            push(Op::Wait);
            push(Op::Callback, Callback::Transformation, 13);
            push(Op::Wait);
            push(Op::Callback, Callback::Transformation, 12);
            push(Op::Wait);
            push(Op::Callback, Callback::Transformation, BoardWidth);
            push(Op::Wait);
            push(Op::Callback, Callback::Transformation, 10);
            push(Op::Wait);
            push(Op::Callback, Callback::Transformation, 9);
            push(Op::Wait);
            push(Op::Callback, Callback::Transformation, 8);
            push(Op::Wait);
            push(Op::Callback, Callback::Transformation, 7);
            push(Op::Wait);
            push(Op::Callback, Callback::Transformation, 6);
            push(Op::Wait);
            push(Op::Callback, Callback::Transformation, 5);
            push(Op::Wait);
            push(Op::Callback, Callback::Transformation, 4);
            push(Op::Wait);
            push(Op::Callback, Callback::Transformation, 3);
            push(Op::Wait);
            push(Op::Callback, Callback::Transformation, 2);
            push(Op::Wait);
            push(Op::Callback, Callback::Transformation, 1);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Floor20);
            push(Op::DoorFrame, cell(5, 8), DoorMotion::CloseGate);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            waits(2);
            if (hero.music_track != 0) {
                push(Op::Wait);
                push(Op::Sound, SoundCue::MusicStop);
            }
            break;
        case 24:
            if (hero.zeno_sealed == 1) {
                hero.zeno_sealed = 0;
                monsters[ZenoRow].hp = monsters[ZenoRow].hp * 10;
                monsters[ZenoRow].attack = monsters[ZenoRow].attack * 10;
                monsters[ZenoRow].defense = monsters[ZenoRow].defense * 10;
            }
            if ((hero.cycle_factor_minus_one != 0) && (hero.later_cycle == 0)) {
                monsters[ZenoRow].hp = 1000;
                monsters[ZenoRow].attack = 625;
                monsters[ZenoRow].defense = 125;
                push(Op::Wait);
                push(Op::Callback, Callback::ForcedBattle, 71);
                waits(3);
                push(Op::MoveTile, cell(5, 5), cell(5, 6));
                push(Op::Wait);
                push(Op::Sound, SoundCue::Get);
                waits(3);
                push(Op::MoveTile, cell(5, 4), cell(5, 5));
                push(Op::Wait);
                push(Op::Sound, SoundCue::Get);
            }
            waits(3);
            push(Op::Dialogue, 57, 0);
            waits(5);
            push(Op::Dialogue, 56, 0);
            waits(5);
            push(Op::Dialogue, 55, 0);
            waits(5);
            push(Op::Dialogue, 54, 0);
            waits(5);
            push(Op::Dialogue, 53, 0);
            waits(5);
            push(Op::Dialogue, 52, 0);
            waits(5);
            push(Op::Dialogue, 51, 0);
            waits(5);
            push(Op::Dialogue, 50, 0);
            if (hero.music_track != 0) {
                push(Op::FloorMusic, 0, 0);
            }
            push(Op::WriteTile, cell(5, 4), Zeno);
            waits(6);
            push(Op::Wait, 21, 91);
            push(Op::Overlay, 49, 182);
            push(Op::Wait, 21, 91);
            push(Op::Overlay, 49, 181);
            push(Op::Wait, 21, 91);
            push(Op::Overlay, 49, 180);
            push(Op::Wait, 21, 91);
            push(Op::Overlay, 49, 179);
            push(Op::Wait, 21, 91);
            push(Op::Overlay, 49, 178);
            push(Op::Wait, 21, 91);
            push(Op::Overlay, 49, 177);
            push(Op::Wait, 21, 91);
            push(Op::Overlay, 49, 176);
            push(Op::Wait, 21, 91);
            push(Op::Overlay, 49, 175);
            push(Op::Wait, 21, 91);
            push(Op::Overlay, 49, 174);
            push(Op::Wait, 21, 91);
            push(Op::Overlay, 49, 173);
            push(Op::Wait, 21, 91);
            push(Op::Overlay, 49, 172);
            push(Op::Wait, 21, 91);
            push(Op::Overlay, 49, 171);
            push(Op::Wait, 21, 91);
            push(Op::Overlay, 49, 170);
            push(Op::Wait, 21, 91);
            push(Op::Overlay, 49, 169);
            push(Op::Wait, 21, 91);
            push(Op::Overlay, 49, 168);
            push(Op::Wait, 21, 91);
            push(Op::Overlay, 49, 167);
            push(Op::Wait, 21, 91);
            push(Op::Overlay, 49, 166);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Floor3);
            waits(7);
            push(Op::Dialogue, 49, 0);
            waits(5);
            push(Op::Dialogue, 48, 0);
            waits(11);
            push(Op::Callback, BoardWidth, 50);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            push(Op::Wait);
            push(Op::Callback, BoardWidth, 49);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            push(Op::Wait);
            push(Op::Callback, BoardWidth, 48);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            push(Op::Wait);
            push(Op::Callback, BoardWidth, 47);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            push(Op::Wait);
            push(Op::Callback, BoardWidth, 46);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            push(Op::Wait);
            push(Op::Callback, BoardWidth, 45);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            push(Op::Wait);
            push(Op::Callback, BoardWidth, 44);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            push(Op::Wait);
            push(Op::Callback, BoardWidth, 43);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            push(Op::Wait);
            push(Op::Callback, BoardWidth, 42);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            push(Op::Wait);
            push(Op::Callback, BoardWidth, 41);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            push(Op::Wait);
            push(Op::Callback, BoardWidth, 40);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            push(Op::Wait);
            push(Op::Callback, BoardWidth, 39);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            push(Op::Wait);
            push(Op::Callback, BoardWidth, 38);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            push(Op::Wait);
            push(Op::Callback, BoardWidth, 37);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            push(Op::Wait);
            push(Op::Callback, BoardWidth, 36);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            push(Op::Wait);
            push(Op::Callback, BoardWidth, 35);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            push(Op::Wait);
            push(Op::Callback, BoardWidth, 34);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            push(Op::Wait);
            push(Op::Callback, BoardWidth, 33);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            push(Op::Wait);
            push(Op::Callback, BoardWidth, 32);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            push(Op::Wait);
            push(Op::Callback, BoardWidth, 31);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            push(Op::Wait);
            push(Op::Callback, BoardWidth, 30);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            push(Op::Wait);
            push(Op::Callback, BoardWidth, 29);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            push(Op::Wait);
            push(Op::Callback, BoardWidth, 28);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            push(Op::Wait);
            push(Op::Callback, BoardWidth, 27);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            push(Op::Wait);
            push(Op::Callback, BoardWidth, 26);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            push(Op::Wait);
            push(Op::Callback, BoardWidth, 25);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            waits(2);
            if (hero.music_track != 0) {
                push(Op::Wait);
                push(Op::Sound, SoundCue::MusicStop);
            }
            break;
        case 25:
            push(Op::Wait);
            push(Op::Dialogue, 23, 0);
            push(Op::DoorFrame, cell(5, 9), DoorMotion::CloseGate);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            waits(2);
            break;
        case 30:
            push(Op::DoorFrame, cell(5, 6), DoorMotion::CloseGate);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            push(Op::DoorFrame, cell(5, 3), DoorMotion::CloseGate);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            waits(2);
            break;
        case 32:
            push(Op::Wait);
            push(Op::Callback, Callback::ForcedBattle, 104);
            waits(3);
            push(Op::MoveTile, cell(5, 8), cell(5, 9));
            waits(3);
            push(Op::MoveTile, cell(5, 7), cell(5, 8));
            waits(3);
            push(Op::MoveTile, cell(5, 6), cell(5, 7));
            waits(3);
            push(Op::MoveTile, cell(5, 5), cell(5, 6));
            waits(3);
            push(Op::Dialogue, 30, 0);
            waits(7);
            push(Op::MoveTile, cell(5, 4), cell(5, 5));
            waits(3);
            push(Op::MoveTile, cell(5, 3), cell(5, 4));
            waits(3);
            push(Op::MoveTile, cell(5, 2), cell(5, 3));
            waits(3);
            push(Op::MoveTile, cell(5, 1), cell(5, 2));
            waits(3);
            push(Op::MoveTile, cell(5, 0), cell(5, 1));
            waits(3);
            push(Op::MoveTile, cell(6, 0), cell(5, 0));
            waits(3);
            push(Op::MoveTile, cell(7, 0), cell(6, 0));
            waits(3);
            push(Op::MoveTile, cell(8, 0), cell(7, 0));
            waits(3);
            push(Op::MoveTile, cell(9, 0), cell(8, 0));
            waits(3);
            push(Op::SetTile, cell(9, 0), GoldenKnight);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            waits(10);
            break;
        case 33:
            if (hero.y * BoardWidth + hero.x == 107) {
                push(Op::Wait);
                push(Op::Message, 114, 0);
                push(Op::Wait);
                push(Op::DoorFrame, cell(7, 9), DoorMotion::RaiseWall);
                expand_door();
                push(Op::Wait);
                push(Op::Sound, SoundCue::Open);
                waits(2);
            } else {
                push(Op::DoorFrame, cell(9, 7), DoorMotion::CloseGate);
                expand_door();
                push(Op::Wait);
                push(Op::Sound, SoundCue::Open);
                push(Op::DoorFrame, cell(9, 3), DoorMotion::CloseGate);
                expand_door();
                push(Op::Wait);
                push(Op::Sound, SoundCue::Open);
                waits(2);
            }
            break;
        case 38:
            push(Op::Wait);
            push(Op::Message, 114, 0);
            push(Op::Wait);
            push(Op::DoorFrame, cell(1, 4), DoorMotion::RaiseWall);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            waits(2);
            break;
        case 40:
            if (tile_at(hero.floor, 4, 3) == 6) {
                tile_at(hero.floor, 4, 3) = GhostSoldier;
            }
            if (tile_at(hero.floor, 3, 3) == 6) {
                tile_at(hero.floor, 3, 3) = GhostSoldier;
            }
            if (tile_at(hero.floor, 2, 3) == 6) {
                tile_at(hero.floor, 2, 3) = GhostSoldier;
            }
            if (tile_at(hero.floor, 6, 3) == 6) {
                tile_at(hero.floor, 6, 3) = Soldier;
            }
            if (tile_at(hero.floor, 7, 3) == 6) {
                tile_at(hero.floor, 7, 3) = Soldier;
            }
            if (tile_at(hero.floor, 8, 3) == 6) {
                tile_at(hero.floor, 8, 3) = Soldier;
            }
            if (tile_at(hero.floor, 3, 1) == 6) {
                tile_at(hero.floor, 3, 1) = Swordsman;
            }
            if (tile_at(hero.floor, 2, 1) == 6) {
                tile_at(hero.floor, 2, 1) = Swordsman;
            }
            if (tile_at(hero.floor, 1, 1) == 6) {
                tile_at(hero.floor, 1, 1) = Swordsman;
            }
            if (tile_at(hero.floor, 7, 1) == 6) {
                tile_at(hero.floor, 7, 1) = Knight;
            }
            if (tile_at(hero.floor, 8, 1) == 6) {
                tile_at(hero.floor, 8, 1) = Knight;
            }
            if (tile_at(hero.floor, 9, 1) == 6) {
                tile_at(hero.floor, 9, 1) = Knight;
            }
            if (tile_at(hero.floor, 5, 1) == 6) {
                tile_at(hero.floor, 5, 1) = GoldenKnight;
            }
            push(Op::Wait);
            push(Op::Callback, Callback::CheckGuards, 0);
            push(Op::Wait);
            push(Op::SetTile, cell(5, 1), Road);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            push(Op::Wait);
            push(Op::MoveTile, cell(5, 2), cell(5, 1));
            waits(3);
            push(Op::MoveTile, cell(5, 3), cell(5, 2));
            waits(3);
            push(Op::MoveTile, cell(5, 4), cell(5, 3));
            waits(3);
            push(Op::MoveTile, cell(5, 5), cell(5, 4));
            waits(3);
            push(Op::MoveTile, cell(5, 6), cell(5, 5));
            waits(6);
            push(Op::WriteTile, cell(5, 6), GoldenKnight);
            push(Op::Dialogue, 39, 0);
            push(Op::Wait);
            push(Op::SetTile, cell(5, 0), BoardWidth);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            waits(3);
            push(Op::Message, 4, 0);
            push(Op::Wait);
            push(Op::DoorFrame, cell(5, 7), DoorMotion::OpenGate);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            waits(3);
            push(Op::Callback, Callback::ForcedBattle, 71);
            push(Op::Wait);
            push(Op::MoveTile, cell(5, 5), cell(5, 6));
            push(Op::Wait);
            push(Op::MoveTile, cell(5, 4), cell(5, 5));
            push(Op::Wait);
            push(Op::MoveTile, cell(5, 3), cell(5, 4));
            push(Op::Wait);
            push(Op::MoveTile, cell(5, 2), cell(5, 3));
            push(Op::Wait);
            push(Op::MoveTile, cell(5, 1), cell(5, 2));
            push(Op::Wait);
            push(Op::Dialogue, 38, 0);
            push(Op::Wait);
            push(Op::Callback, Callback::ForcedBattle, 71);
            push(Op::Wait);
            push(Op::MoveTile, cell(5, 5), cell(5, 6));
            push(Op::Wait);
            push(Op::MoveTile, cell(5, 4), cell(5, 5));
            push(Op::Wait);
            push(Op::MoveTile, cell(5, 3), cell(5, 4));
            push(Op::Wait);
            push(Op::MoveTile, cell(6, 3), cell(5, 3));
            push(Op::Wait);
            push(Op::MoveTile, cell(6, 2), cell(6, 3));
            push(Op::Wait);
            push(Op::MoveTile, cell(7, 2), cell(6, 2));
            push(Op::Wait);
            push(Op::MoveTile, cell(7, 1), cell(7, 2));
            push(Op::Wait);
            push(Op::MoveTile, cell(8, 1), cell(7, 1));
            push(Op::Wait);
            push(Op::MoveTile, cell(9, 1), cell(8, 1));
            push(Op::Wait);
            push(Op::Callback, Callback::ForcedBattle, 71);
            push(Op::Wait);
            push(Op::MoveTile, cell(5, 5), cell(5, 6));
            push(Op::Wait);
            push(Op::MoveTile, cell(5, 4), cell(5, 5));
            push(Op::Wait);
            push(Op::MoveTile, cell(5, 3), cell(5, 4));
            push(Op::Wait);
            push(Op::MoveTile, cell(6, 3), cell(5, 3));
            push(Op::Wait);
            push(Op::MoveTile, cell(6, 2), cell(6, 3));
            push(Op::Wait);
            push(Op::MoveTile, cell(7, 2), cell(6, 2));
            push(Op::Wait);
            push(Op::MoveTile, cell(7, 1), cell(7, 2));
            push(Op::Wait);
            push(Op::MoveTile, cell(8, 1), cell(7, 1));
            push(Op::Wait);
            push(Op::Callback, Callback::ForcedBattle, 71);
            push(Op::Wait);
            push(Op::MoveTile, cell(5, 5), cell(5, 6));
            push(Op::Wait);
            push(Op::MoveTile, cell(5, 4), cell(5, 5));
            push(Op::Wait);
            push(Op::MoveTile, cell(5, 3), cell(5, 4));
            push(Op::Wait);
            push(Op::MoveTile, cell(6, 3), cell(5, 3));
            push(Op::Wait);
            push(Op::MoveTile, cell(6, 2), cell(6, 3));
            push(Op::Wait);
            push(Op::MoveTile, cell(7, 2), cell(6, 2));
            push(Op::Wait);
            push(Op::MoveTile, cell(7, 1), cell(7, 2));
            push(Op::Wait);
            push(Op::Dialogue, 37, 0);
            push(Op::Wait);
            push(Op::Callback, Callback::ForcedBattle, 71);
            push(Op::Wait);
            push(Op::MoveTile, cell(5, 5), cell(5, 6));
            push(Op::Wait);
            push(Op::MoveTile, cell(5, 4), cell(5, 5));
            push(Op::Wait);
            push(Op::MoveTile, cell(5, 3), cell(5, 4));
            push(Op::Wait);
            push(Op::MoveTile, cell(4, 3), cell(5, 3));
            push(Op::Wait);
            push(Op::MoveTile, cell(4, 2), cell(4, 3));
            push(Op::Wait);
            push(Op::MoveTile, cell(3, 2), cell(4, 2));
            push(Op::Wait);
            push(Op::MoveTile, cell(3, 1), cell(3, 2));
            push(Op::Wait);
            push(Op::MoveTile, cell(2, 1), cell(3, 1));
            push(Op::Wait);
            push(Op::MoveTile, cell(1, 1), cell(2, 1));
            push(Op::Wait);
            push(Op::Callback, Callback::ForcedBattle, 71);
            push(Op::Wait);
            push(Op::MoveTile, cell(5, 5), cell(5, 6));
            push(Op::Wait);
            push(Op::MoveTile, cell(5, 4), cell(5, 5));
            push(Op::Wait);
            push(Op::MoveTile, cell(5, 3), cell(5, 4));
            push(Op::Wait);
            push(Op::MoveTile, cell(4, 3), cell(5, 3));
            push(Op::Wait);
            push(Op::MoveTile, cell(4, 2), cell(4, 3));
            push(Op::Wait);
            push(Op::MoveTile, cell(3, 2), cell(4, 2));
            push(Op::Wait);
            push(Op::MoveTile, cell(3, 1), cell(3, 2));
            push(Op::Wait);
            push(Op::MoveTile, cell(2, 1), cell(3, 1));
            push(Op::Wait);
            push(Op::Callback, Callback::ForcedBattle, 71);
            push(Op::Wait);
            push(Op::MoveTile, cell(5, 5), cell(5, 6));
            push(Op::Wait);
            push(Op::MoveTile, cell(5, 4), cell(5, 5));
            push(Op::Wait);
            push(Op::MoveTile, cell(5, 3), cell(5, 4));
            push(Op::Wait);
            push(Op::MoveTile, cell(4, 3), cell(5, 3));
            push(Op::Wait);
            push(Op::MoveTile, cell(4, 2), cell(4, 3));
            push(Op::Wait);
            push(Op::MoveTile, cell(3, 2), cell(4, 2));
            push(Op::Wait);
            push(Op::MoveTile, cell(3, 1), cell(3, 2));
            push(Op::Wait);
            push(Op::Dialogue, 36, 0);
            push(Op::Wait);
            push(Op::Callback, Callback::ForcedBattle, 71);
            push(Op::Wait);
            push(Op::MoveTile, cell(5, 5), cell(5, 6));
            push(Op::Wait);
            push(Op::MoveTile, cell(5, 4), cell(5, 5));
            push(Op::Wait);
            push(Op::MoveTile, cell(6, 4), cell(5, 4));
            push(Op::Wait);
            push(Op::MoveTile, cell(6, 3), cell(6, 4));
            push(Op::Wait);
            push(Op::MoveTile, cell(7, 3), cell(6, 3));
            push(Op::Wait);
            push(Op::MoveTile, cell(8, 3), cell(7, 3));
            push(Op::Wait);
            push(Op::Callback, Callback::ForcedBattle, 71);
            push(Op::Wait);
            push(Op::MoveTile, cell(5, 5), cell(5, 6));
            push(Op::Wait);
            push(Op::MoveTile, cell(5, 4), cell(5, 5));
            push(Op::Wait);
            push(Op::MoveTile, cell(6, 4), cell(5, 4));
            push(Op::Wait);
            push(Op::MoveTile, cell(6, 3), cell(6, 4));
            push(Op::Wait);
            push(Op::MoveTile, cell(7, 3), cell(6, 3));
            push(Op::Wait);
            push(Op::Callback, Callback::ForcedBattle, 71);
            push(Op::Wait);
            push(Op::MoveTile, cell(5, 5), cell(5, 6));
            push(Op::Wait);
            push(Op::MoveTile, cell(5, 4), cell(5, 5));
            push(Op::Wait);
            push(Op::MoveTile, cell(6, 4), cell(5, 4));
            push(Op::Wait);
            push(Op::MoveTile, cell(6, 3), cell(6, 4));
            push(Op::Wait);
            push(Op::Dialogue, 35, 0);
            push(Op::Wait);
            push(Op::Callback, Callback::ForcedBattle, 71);
            push(Op::Wait);
            push(Op::MoveTile, cell(5, 5), cell(5, 6));
            push(Op::Wait);
            push(Op::MoveTile, cell(5, 4), cell(5, 5));
            push(Op::Wait);
            push(Op::MoveTile, cell(4, 4), cell(5, 4));
            push(Op::Wait);
            push(Op::MoveTile, cell(4, 3), cell(4, 4));
            push(Op::Wait);
            push(Op::MoveTile, cell(3, 3), cell(4, 3));
            push(Op::Wait);
            push(Op::MoveTile, cell(2, 3), cell(3, 3));
            push(Op::Wait);
            push(Op::Callback, Callback::ForcedBattle, 71);
            push(Op::Wait);
            push(Op::MoveTile, cell(5, 5), cell(5, 6));
            push(Op::Wait);
            push(Op::MoveTile, cell(5, 4), cell(5, 5));
            push(Op::Wait);
            push(Op::MoveTile, cell(4, 4), cell(5, 4));
            push(Op::Wait);
            push(Op::MoveTile, cell(4, 3), cell(4, 4));
            push(Op::Wait);
            push(Op::MoveTile, cell(3, 3), cell(4, 3));
            push(Op::Wait);
            push(Op::Callback, Callback::ForcedBattle, 71);
            push(Op::Wait);
            push(Op::MoveTile, cell(5, 5), cell(5, 6));
            push(Op::Wait);
            push(Op::MoveTile, cell(5, 4), cell(5, 5));
            push(Op::Wait);
            push(Op::MoveTile, cell(4, 4), cell(5, 4));
            push(Op::Wait);
            push(Op::MoveTile, cell(4, 3), cell(4, 4));
            push(Op::Wait);
            push(Op::Dialogue, 34, 0);
            push(Op::DoorFrame, cell(5, 7), DoorMotion::CloseGate);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            waits(2);
            break;
        case 42:
            tile_at(35, 4, 9) = Road;
            push(Op::Wait);
            push(Op::SetTile, cell(5, 5), Road);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            waits(7);
            push(Op::Dialogue, 44, 0);
            waits(6);
            push(Op::SetTile, cell(6, 7), Road);
            push(Op::SetTile, cell(4, 7), Road);
            push(Op::SetTile, cell(5, 8), Road);
            push(Op::SetTile, cell(5, 6), Road);
            waits(7);
            push(Op::SetTile, cell(5, 7), Road);
            waits(4);
            push(Op::Wait, tile_at(hero.floor, 5, 7), HeroHitColor);
            push(Op::Overlay, 82, HeroHitMask);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Zeno);
            push(Op::Wait);
            push(Op::Dialogue, 43, 0);
            scratch_index = 71;
            neighbor_index = 93;
            summon_four_guards(scratch_index, neighbor_index, 81, 83);
            waits(5);
            push(Op::Dialogue, 42, 0);
            waits(5);
            push(Op::Dialogue, 41, 0);
            scratch_index = 60;
            summon(scratch_index, Zeno);
            waits(6);
            break;
        case 43:
            if (tile_at(hero.floor, 8, 0) == 93) {
                push(Op::Wait);
                push(Op::DoorFrame, cell(9, 0), DoorMotion::RaiseWall);
                expand_door();
                push(Op::Wait);
                push(Op::Sound, SoundCue::Open);
                waits(3);
                push(Op::DoorFrame, cell(6, 0), DoorMotion::RaiseWall);
                expand_door();
                push(Op::Wait);
                push(Op::Sound, SoundCue::Open);
                waits(5);
                push(Op::MoveTile, cell(9, 0), cell(10, 0));
                push(Op::Wait);
                push(Op::Sound, SoundCue::Get);
                waits(5);
                push(Op::MoveTile, cell(8, 0), cell(9, 0));
                push(Op::Wait);
                push(Op::Sound, SoundCue::Get);
                waits(2);
            } else {
                push(Op::Wait);
            }
            break;
        case 48:
            push(Op::Wait);
            push(Op::SetTile, cell(0, 0), Sorcerer);
            push(Op::Wait);
            push(Op::Sound, SoundCue::Get);
            waits(2);
            break;
        case 49:
            push(Op::Wait);
            push(Op::Callback, Callback::SummonGuards, 0);
            push(Op::Wait);
            if (hero.music_track != 0) {
                push(Op::Wait);
                push(Op::Sound, SoundCue::MusicStart);
            }
            push(Op::Wait);
            push(Op::Dialogue, 45, 0);
            waits(3);
            push(Op::Callback, Callback::SummonZeno, 0);
            push(Op::DoorFrame, cell(5, 6), DoorMotion::CloseGate);
            expand_door();
            push(Op::Wait);
            push(Op::Sound, SoundCue::Open);
            waits(2);
            if (hero.music_track != 0) {
                push(Op::Wait);
                push(Op::Sound, SoundCue::MusicStop);
            }
        }
    }
    return;
}
void Game::summon(int index, int color) {
    // 0x461A0C. Insertion descends, playback materializes from mask 166 to 182.
    for (int mask = DissolveLastMask; mask >= DissolveFirstMask; --mask) {
        push(Op::Wait, Road, color);
        push(Op::Overlay, index, mask);
    }
    push(Op::Wait);
    push(Op::Sound, SoundCue::Floor3);
}
void Game::summon_four_guards(int north, int south, int west, int east) {
    // 0x461EF4, used for the four temporary guards in the 42F speech.
    for (int mask : {182, 175, 171, 169, 167})
        for (int index : {east, west, south, north}) {
            push(Op::Wait, Road, Sorcerer);
            push(Op::Overlay, index, mask);
        }
    push(Op::Wait);
    push(Op::Sound, SoundCue::Floor3);
}
void Game::summon_guards() {
    // 0x462560 writes all eight 49F guards before their materialization stack.
    constexpr std::array<int, 8> Guards{26, 37, 38, 39, 28, 17, 16, 15};
    for (int index : Guards)
        tile(hero.floor, index) = Sorcerer;
    for (int mask : {182, 179, 177, 175, 173, 171, 169, 167})
        for (int index : Guards) {
            push(Op::Wait, Road, Sorcerer);
            push(Op::Overlay, index, mask);
        }
}
void Game::transform_vampire() {
    // Gameplay writes precede the original 32 rendering frames in check_floor.
    visual.raster_mode = 10;
    if (visual.raster_frame == 32)
        visual.raster_mode = -1;
}
void Game::capture() {
    // opening2, 0x464048. Select its original 40-pixel canvas branch.
    push(Op::Callback, Callback::Capture);
    push(Op::Wait, 1);
    push(Op::Callback, Callback::RasterScene, 500);
    for (int group = 50; group >= 0; --group)
        for (int part = 5; part >= 0; --part) {
            push(Op::Wait, 1);
            push(Op::Callback, Callback::RasterScene, group * 6 + 100 + part);
        }
    push(Op::Wait, 1);
    push(Op::Callback, Callback::RasterScene, 0);
    waits(3);
    for (int frame = 247; frame >= 232; --frame) {
        if (frame != 247)
            push(Op::Wait);
        push(Op::Callback, Callback::RasterScene, frame);
        push(Op::Wait);
        push(Op::Sound, SoundCue::Zeno);
    }
    push(Op::Wait);
    push(Op::Callback, Callback::HidePanels);
    waits(25);
    push(Op::Callback, Callback::Title);
    push(Op::Wait);
    push(Op::UpdateInventory);
    push(Op::Wait);
    push(Op::SetTile, 92, Road);
    waits(4);
    damage_pose(92, Road);
    push(Op::Wait);
    push(Op::Sound, SoundCue::Zeno);
    waits(5);
    push(Op::Dialogue, 11);
    summon_four_guards(81, 103, 91, 93);
}
void Game::ending() {
    // handan's first-cycle Zeno contact: preserve the original stack of raster callbacks.
    push(Op::Wait);
    push(Op::Callback, Callback::NextCycle);
    push(Op::Wait, 8);
    push(Op::Callback, Callback::RasterScene);
    push(Op::Wait, 7);
    push(Op::Callback, Callback::RasterScene);
    for (int frame = 400; frame >= 1; --frame) {
        push(Op::Wait, 5);
        push(Op::Callback, Callback::RasterScene, frame);
    }
    push(Op::Wait, 4);
    push(Op::Callback, Callback::RasterScene, 400);
    for (int frame = 399; frame >= 300; frame -= 3) {
        push(Op::Wait, 4);
        push(Op::Callback, Callback::RasterScene, frame);
    }
    for (int frame = 295; frame >= 205; frame -= 5) {
        push(Op::Wait, 4);
        push(Op::Callback, Callback::RasterScene, frame);
    }
    for (int frame = 197; frame >= 101; frame -= 8) {
        push(Op::Wait, 4);
        push(Op::Callback, Callback::RasterScene, frame);
    }
    for (int frame = 91; frame >= 1; frame -= 10) {
        push(Op::Wait, 4);
        push(Op::Callback, Callback::RasterScene, frame);
    }
    waits(2);
    for (int frame = 17; frame >= 1; --frame) {
        push(Op::Wait, 6);
        push(Op::Callback, Callback::RasterScene, frame);
        push(Op::Wait);
        push(Op::Sound, frame == 1 ? SoundCue::Open : SoundCue::Stairs2);
    }
    for (int frame = 247; frame >= 232; --frame) {
        push(Op::Wait, 2);
        push(Op::Callback, Callback::RasterScene, frame);
        push(Op::Wait);
        push(Op::Sound, SoundCue::Open);
    }
    push(Op::Wait);
    push(Op::Callback, Callback::CacheScene);
    push(Op::Wait);
    push(Op::Callback, Callback::HidePanels);
    status = "The princess is free. The stronger backside tower awaits.";
}
} // namespace baseline
