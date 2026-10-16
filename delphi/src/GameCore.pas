unit GameCore;

{ Standalone core bodies for the isolated original-address/storage probes.
  The production executable uses the corresponding TTSW10 method bodies.
  Both copies are checked against the original's ordered writes and calls. }

{ Combat and checksums require signed 32-bit wrapping arithmetic.
  Address comments identify routines used by the comparison probes. }
{$A+,Z-,O+,R-,Q-,S-}

interface
uses
  GameState;

procedure InitializeCycle;
procedure ClassifyNeighbor;
procedure ClassifyInteraction;
procedure FaceUpLanding;
procedure FaceDownLanding;
procedure CountHeroStrikes;
procedure CountDoubleHeroStrikes;
procedure CountEnemyStrikes;
procedure EnemyFirstDamage;
procedure SelectGraphicFrame;
procedure DoubleEnemyFirstDamage;
procedure CountBattleHeroStrikes;
procedure CountBattleEnemyStrikes;
procedure BattleDamage;
procedure DoorAnimation;
procedure MattockWall;
procedure CrystalLava;
procedure CheckSpecialDoors;

implementation

procedure InitializeCycle;
begin
  {$I InitializeCycle.inc}
end;

procedure ClassifyNeighbor; { $00451C20 }
begin
  TileClass := 0;
  case Maps[Hero.floor, NeighborIndex + MapTileOffset] of
    tileWall: TileClass := 1;
    tileGreenSlime..tileRock + 1,
    tileSorcerer..tileVampire + 1,
    tileGoldenKnight..tileSlimeMan + 1,
    tileVampireBat..tileGateKeeperA + 1:
    begin
      TileClass := 2;
      case Maps[Hero.floor, NeighborIndex + MapTileOffset] of
        tileGreenSlime..tileVampire + 1:
          MonsterIndex := (Maps[Hero.floor, NeighborIndex + MapTileOffset] - tileGreenSlime) div 2;
        tileOctopusFirst..tileOctopusLast: MonsterIndex := Ord(monsterOctopus);
        tileDragonFirst..132: MonsterIndex := Ord(monsterDragon);
        tileGoldenKnight..tileGateKeeperA + 1:
          MonsterIndex :=
              (Maps[Hero.floor, NeighborIndex + MapTileOffset] - tileGoldenKnight) div 2
                  + Ord(monsterGoldenKnight);
      end;
    end;
    tileLava: TileClass := 3;
  end;
end;

procedure ClassifyInteraction; { $0044C9F0; preserves prior message unless a case matches }
begin
  case Maps[Hero.floor, NeighborIndex + MapTileOffset] - 1 of
    tileStairsUp - 1:
    begin
      TileClass := 19;
      if Hero.floor = Hero.highest_floor then
        Hero.Word664 := Ord(stairUp);
    end;
    tileStairsDown - 1:
    begin
      TileClass := 19;
      if Hero.floor = Hero.highest_floor then
        Hero.Word664 := Ord(stairDown);
    end;
    tileLava - 1: TileClass := 52;
    tileAltar - 1: TileClass := 24;
    tileAltarSide - 1: TileClass := 24;
    tileMerchant - 1, tileMerchant2 - 1: TileClass := 13;
    tileThief - 1, tileThief2 - 1: TileClass := 15;
    tileFairy - 1, tileFairy2 - 1: TileClass := 14;
    tileOldMan - 1, tileOldMan2 - 1: TileClass := 12;
    tileMagicianA - 1, tileMagicianA + 1 - 1: TileClass := 110;
    tileMagicianB - 1, tileMagicianB + 1 - 1: TileClass := 111;
  end;
end;

procedure FaceUpLanding; { $00442F80; the last matching adjacent stair sets facing }
begin
  ScratchIndex := Hero.y * BoardWidth + Hero.x;
  NeighborIndex := ScratchIndex - BoardWidth;
  case Hero.y of
    1..10:
      if Maps[Hero.floor, NeighborIndex + MapTileOffset] = tileStairsDown then
        Hero.facing := Ord(hfDown);
  end;
  NeighborIndex := ScratchIndex - 1;
  case Hero.x of
    1..10:
      if Maps[Hero.floor, NeighborIndex + MapTileOffset] = tileStairsDown then
        Hero.facing := Ord(hfRight);
  end;
  NeighborIndex := ScratchIndex + 1;
  case Hero.x of
    0..9:
      if Maps[Hero.floor, NeighborIndex + MapTileOffset] = tileStairsDown then
        Hero.facing := Ord(hfLeft);
  end;
  NeighborIndex := ScratchIndex + BoardWidth;
  case Hero.y of
    0..9:
      if Maps[Hero.floor, NeighborIndex + MapTileOffset] = tileStairsDown then
        Hero.facing := Ord(hfUp);
  end;
end;

procedure FaceDownLanding; { $00443050 }
begin
  ScratchIndex := Hero.y * BoardWidth + Hero.x;
  NeighborIndex := ScratchIndex - BoardWidth;
  case Hero.y of
    1..10:
      if Maps[Hero.floor, NeighborIndex + MapTileOffset] = tileStairsUp then
        Hero.facing := Ord(hfDown);
  end;
  NeighborIndex := ScratchIndex - 1;
  case Hero.x of
    1..10:
      if Maps[Hero.floor, NeighborIndex + MapTileOffset] = tileStairsUp then
        Hero.facing := Ord(hfRight);
  end;
  NeighborIndex := ScratchIndex + 1;
  case Hero.x of
    0..9:
      if Maps[Hero.floor, NeighborIndex + MapTileOffset] = tileStairsUp then
        Hero.facing := Ord(hfLeft);
  end;
  NeighborIndex := ScratchIndex + BoardWidth;
  case Hero.y of
    0..9:
      if Maps[Hero.floor, NeighborIndex + MapTileOffset] = tileStairsUp then
        Hero.facing := Ord(hfUp);
  end;
end;

procedure CountHeroStrikes; { $0045031C }
begin
  if RemainingHP > 0 then
  begin
    RemainingHP :=
        Monsters[MonsterIndex].Defense * (Hero.cycle_factor_minus_one + 1)
            + (RemainingHP - Hero.attack);
    Inc(StrikeCount);
    CountHeroStrikes;
  end;
end;

procedure CountDoubleHeroStrikes; { $00450360 }
begin
  if RemainingHP > 0 then
  begin
    RemainingHP :=
        RemainingHP
            - Hero.attack * 2
            + Monsters[MonsterIndex].Defense * (Hero.cycle_factor_minus_one + 1);
    Inc(StrikeCount);
    CountDoubleHeroStrikes;
  end;
end;

procedure CountEnemyStrikes; { $004503A8 }
begin
  if RemainingHP > 0 then
  begin
    RemainingHP :=
        RemainingHP
            - Monsters[MonsterIndex].Attack * (Hero.cycle_factor_minus_one + 1)
            + Hero.defense;
    Inc(StrikeCount);
    CountEnemyStrikes;
  end;
end;

procedure EnemyFirstDamage; { $00450288 }
begin
  StrikeCount := 0;
  RemainingHP := Hero.hp;
  CountEnemyStrikes;
  Damage :=
      (Hero.attack - Monsters[MonsterIndex].Defense * (Hero.cycle_factor_minus_one + 1))
          * (StrikeCount - 1);
end;

procedure SelectGraphicFrame; { $00454C10; the return register is unused by callers }
begin
  DoorOpened := 0;
  case GraphicTile of
    1..12: DoorOpened := 0;
    13: DoorOpened := 147;
    14: DoorOpened := 147;
    15: DoorOpened := 0;
    16: DoorOpened := 2;
    17..18: DoorOpened := 0;
    19..26: DoorOpened := 1;
    27..28:
      if Hero.Word464 = 1 then
        DoorOpened := 0
      else
        DoorOpened := 1;
    29..60: DoorOpened := 0;
    61..96: DoorOpened := 1;
    97..105: DoorOpened := 9;
    106..114: DoorOpened := 0;
    115..123: DoorOpened := 9;
    124..132: DoorOpened := 0;
    133..157: DoorOpened := 1;
  end;
end;

procedure DoubleEnemyFirstDamage; { $004502D0 }
begin
  StrikeCount := 0;
  RemainingHP := Hero.hp;
  CountEnemyStrikes;
  Damage :=
      (Hero.attack * 2 - Monsters[MonsterIndex].Defense * (Hero.cycle_factor_minus_one + 1))
          * (StrikeCount - 1);
end;

procedure CountBattleHeroStrikes; { $004802FC }
begin
  if RemainingHP > 0 then
  begin
    RemainingHP :=
        Monsters[MonsterIndex].Defense * (Hero.cycle_factor_minus_one + 1)
            + (RemainingHP - Hero.attack);
    Inc(StrikeCount);
    CountBattleHeroStrikes;
  end;
end;

procedure CountBattleEnemyStrikes; { $00480340 }
begin
  if RemainingHP > 0 then
  begin
    RemainingHP :=
        RemainingHP
            - Monsters[MonsterIndex].Attack * (Hero.cycle_factor_minus_one + 1)
            + Hero.defense;
    Inc(StrikeCount);
    CountBattleEnemyStrikes;
  end;
end;

procedure BattleDamage; { $0048028C }
begin
  StrikeCount := 0;
  RemainingHP := Monsters[MonsterIndex].HP * (Hero.cycle_factor_minus_one + 1);
  CountBattleHeroStrikes;
  if Hero.defense - Monsters[MonsterIndex].Attack * (Hero.cycle_factor_minus_one + 1) >= 0 then
    Damage := 0
  else
    Damage :=
        (Monsters[MonsterIndex].Attack * (Hero.cycle_factor_minus_one + 1) - Hero.defense)
            * StrikeCount;
end;

procedure DoorAnimation; { $004660D0; preserve the original unrolled writes }
begin
  ScratchIndex := Smallint(EventStack[EventCursor].A);
  NeighborIndex := Smallint(EventStack[EventCursor].B);
  { Expand one door/wall request into sixteen animation frames. Replace the
    current record with frame 16 operands, then push frames 16 down to 1.
    Reverse playback starts at frame 1; each preceding wait supplies its frame. }
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 16;
  { PushCommand(13, Word(ScratchIndex), Word(NeighborIndex)): door/wall animation frame. }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evDoorFrame);
  EventStack[EventCursor].A := Word(ScratchIndex);
  EventStack[EventCursor].B := Word(NeighborIndex);
  { PushCommand(0, 0, 15): wait / paired animation operands. }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 15;
  { PushCommand(13, Word(ScratchIndex), Word(NeighborIndex)): door/wall animation frame. }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evDoorFrame);
  EventStack[EventCursor].A := Word(ScratchIndex);
  EventStack[EventCursor].B := Word(NeighborIndex);
  { PushCommand(0, 0, 14): wait / paired animation operands. }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 14;
  { PushCommand(13, Word(ScratchIndex), Word(NeighborIndex)): door/wall animation frame. }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evDoorFrame);
  EventStack[EventCursor].A := Word(ScratchIndex);
  EventStack[EventCursor].B := Word(NeighborIndex);
  { PushCommand(0, 0, 13): wait / paired animation operands. }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 13;
  { PushCommand(13, Word(ScratchIndex), Word(NeighborIndex)): door/wall animation frame. }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evDoorFrame);
  EventStack[EventCursor].A := Word(ScratchIndex);
  EventStack[EventCursor].B := Word(NeighborIndex);
  { PushCommand(0, 0, 12): wait / paired animation operands. }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 12;
  { PushCommand(13, Word(ScratchIndex), Word(NeighborIndex)): door/wall animation frame. }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evDoorFrame);
  EventStack[EventCursor].A := Word(ScratchIndex);
  EventStack[EventCursor].B := Word(NeighborIndex);
  { PushCommand(0, 0, 11): wait / paired animation operands. }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 11;
  { PushCommand(13, Word(ScratchIndex), Word(NeighborIndex)): door/wall animation frame. }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evDoorFrame);
  EventStack[EventCursor].A := Word(ScratchIndex);
  EventStack[EventCursor].B := Word(NeighborIndex);
  { PushCommand(0, 0, 10): wait / paired animation operands. }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 10;
  { PushCommand(13, Word(ScratchIndex), Word(NeighborIndex)): door/wall animation frame. }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evDoorFrame);
  EventStack[EventCursor].A := Word(ScratchIndex);
  EventStack[EventCursor].B := Word(NeighborIndex);
  { PushCommand(0, 0, 9): wait / paired animation operands. }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 9;
  { PushCommand(13, Word(ScratchIndex), Word(NeighborIndex)): door/wall animation frame. }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evDoorFrame);
  EventStack[EventCursor].A := Word(ScratchIndex);
  EventStack[EventCursor].B := Word(NeighborIndex);
  { PushCommand(0, 0, 8): wait / paired animation operands. }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 8;
  { PushCommand(13, Word(ScratchIndex), Word(NeighborIndex)): door/wall animation frame. }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evDoorFrame);
  EventStack[EventCursor].A := Word(ScratchIndex);
  EventStack[EventCursor].B := Word(NeighborIndex);
  { PushCommand(0, 0, 7): wait / paired animation operands. }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 7;
  { PushCommand(13, Word(ScratchIndex), Word(NeighborIndex)): door/wall animation frame. }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evDoorFrame);
  EventStack[EventCursor].A := Word(ScratchIndex);
  EventStack[EventCursor].B := Word(NeighborIndex);
  { PushCommand(0, 0, 6): wait / paired animation operands. }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 6;
  { PushCommand(13, Word(ScratchIndex), Word(NeighborIndex)): door/wall animation frame. }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evDoorFrame);
  EventStack[EventCursor].A := Word(ScratchIndex);
  EventStack[EventCursor].B := Word(NeighborIndex);
  { PushCommand(0, 0, 5): wait / paired animation operands. }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 5;
  { PushCommand(13, Word(ScratchIndex), Word(NeighborIndex)): door/wall animation frame. }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evDoorFrame);
  EventStack[EventCursor].A := Word(ScratchIndex);
  EventStack[EventCursor].B := Word(NeighborIndex);
  { PushCommand(0, 0, 4): wait / paired animation operands. }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 4;
  { PushCommand(13, Word(ScratchIndex), Word(NeighborIndex)): door/wall animation frame. }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evDoorFrame);
  EventStack[EventCursor].A := Word(ScratchIndex);
  EventStack[EventCursor].B := Word(NeighborIndex);
  { PushCommand(0, 0, 3): wait / paired animation operands. }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 3;
  { PushCommand(13, Word(ScratchIndex), Word(NeighborIndex)): door/wall animation frame. }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evDoorFrame);
  EventStack[EventCursor].A := Word(ScratchIndex);
  EventStack[EventCursor].B := Word(NeighborIndex);
  { PushCommand(0, 0, 2): wait / paired animation operands. }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 2;
  { PushCommand(13, Word(ScratchIndex), Word(NeighborIndex)): door/wall animation frame. }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evDoorFrame);
  EventStack[EventCursor].A := Word(ScratchIndex);
  EventStack[EventCursor].B := Word(NeighborIndex);
  { PushCommand(0, 0, 1): wait / paired animation operands. }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 1;
  { PushCommand(13, Word(ScratchIndex), Word(NeighborIndex)): door/wall animation frame. }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evDoorFrame);
  EventStack[EventCursor].A := Word(ScratchIndex);
  EventStack[EventCursor].B := Word(NeighborIndex);
end;

procedure MattockWall; { $00451B98 }
begin
  { PushCommand(0, 0, 0): wait / paired animation operands. }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(13, Word(NeighborIndex), 7): door/wall animation frame. }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evDoorFrame);
  EventStack[EventCursor].A := Word(NeighborIndex);
  EventStack[EventCursor].B := 7;
  DoorAnimation;
  { PushCommand(0, 0, 0): wait / paired animation operands. }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(1, 1, 0): sound or music action. }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSound);
  EventStack[EventCursor].A := 1;
  EventStack[EventCursor].B := 0;
end;

procedure CrystalLava; { $00451D3C }
begin
  { PushCommand(0, 0, 0): wait / paired animation operands. }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(17, Word(NeighborIndex), 6): change map only. }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSetTileOnly);
  EventStack[EventCursor].A := Word(NeighborIndex);
  EventStack[EventCursor].B := tileRoad;
  { PushCommand(0, 0, 0): wait / paired animation operands. }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(13, Word(NeighborIndex), Word(DamageMode)): door/wall animation frame. }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evDoorFrame);
  EventStack[EventCursor].A := Word(NeighborIndex);
  EventStack[EventCursor].B := Word(DamageMode);
  DoorAnimation;
  { PushCommand(0, 0, 0): wait / paired animation operands. }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(1, 1, 0): sound or music action. }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSound);
  EventStack[EventCursor].A := 1;
  EventStack[EventCursor].B := 0;
end;

procedure CheckSpecialDoors; { $0047BEAC }
begin
  { Nested checks preserve the original Delphi 2 register allocation. }
  case Hero.floor of
    39: { Seven marked cells form the treasure-room puzzle; test each entrance. }
    begin
      if (Maps[Hero.floor, 14]
              + Maps[Hero.floor, 18]
              + Maps[Hero.floor, 36]
              + Maps[Hero.floor, 38]
              + Maps[Hero.floor, 58]
              + Maps[Hero.floor, 60]
              + Maps[Hero.floor, 62]
          = 7) then
        if (Maps[Hero.floor, 16] = tileRoad) then
          if (ContactIndex = 38) then
          begin
            { PushCommand(0, 0, 0): wait / paired animation operands. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(6, 36, 43): change tile and redraw. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTile);
            EventStack[EventCursor].A := 36;
            EventStack[EventCursor].B := tileWarpStaff;
            { PushCommand(0, 0, 0): wait / paired animation operands. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 2, 0): sound or music action. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0): wait / paired animation operands. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0): wait / paired animation operands. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
          end;
      if (Maps[Hero.floor, 14]
              + Maps[Hero.floor, 18]
              + Maps[Hero.floor, 36]
              + Maps[Hero.floor, 38]
              + Maps[Hero.floor, 58]
              + Maps[Hero.floor, 60]
              + Maps[Hero.floor, 62]
          = 7) then
        if (Maps[Hero.floor, 40] = tileRoad) then
          if (ContactIndex = 14) then
          begin
            { PushCommand(0, 0, 0): wait / paired animation operands. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(6, 36, 43): change tile and redraw. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTile);
            EventStack[EventCursor].A := 36;
            EventStack[EventCursor].B := tileWarpStaff;
            { PushCommand(0, 0, 0): wait / paired animation operands. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 2, 0): sound or music action. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0): wait / paired animation operands. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0): wait / paired animation operands. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
          end;
    end;
    43: { Arm the sorcerer trap by changing contact cell 7 to special road. }
      if (ContactIndex = 7) then
        if (Maps[Hero.floor, 10] = tileSorcerer) then
        begin
          { PushCommand(6, 7, 7): change tile and redraw. }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evSetTile);
          EventStack[EventCursor].A := 7;
          EventStack[EventCursor].B := tileSpecialRoad;
        end;
  end;
end;

end.
