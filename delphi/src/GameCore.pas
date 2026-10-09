unit GameCore;

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
  case Maps[Hero.floor, NeighborIndex + 2] of
    8: TileClass := 1;
    61..90, 93..96, 133..144, 147..158:
    begin
      TileClass := 2;
      case Maps[Hero.floor, NeighborIndex + 2] of
        61..96: MonsterIndex := (Maps[Hero.floor, NeighborIndex + 2] - 61) div 2;
        97..114: MonsterIndex := 18;
        115..132: MonsterIndex := 19;
        133..158: MonsterIndex := (Maps[Hero.floor, NeighborIndex + 2] - 133) div 2 + 20;
      end;
    end;
    13: TileClass := 3;
  end;
end;

procedure ClassifyInteraction; { $0044C9F0; preserves prior message unless a case matches }
begin
  case Maps[Hero.floor, NeighborIndex + 2] of
    11:
    begin
      TileClass := 19;
      if Hero.floor = Hero.highest_floor then
        Hero.Word664 := 1;
    end;
    12:
    begin
      TileClass := 19;
      if Hero.floor = Hero.highest_floor then
        Hero.Word664 := 2;
    end;
    13: TileClass := 52;
    16, 18: TileClass := 24;
    19, 20: TileClass := 13;
    21, 22: TileClass := 15;
    23, 24: TileClass := 14;
    25, 26: TileClass := 12;
    151, 152: TileClass := 110;
    153, 154: TileClass := 111;
  end;
end;

procedure FaceUpLanding; { $00442F80; the last matching adjacent stair sets facing }
begin
  ScratchIndex := Hero.y * 11 + Hero.x;
  NeighborIndex := ScratchIndex - 11;
  if (Hero.y >= 1) and (Hero.y <= 10) and (Maps[Hero.floor, NeighborIndex + 2] = 12) then
    Hero.facing := 1;
  NeighborIndex := ScratchIndex - 1;
  if (Hero.x >= 1) and (Hero.x <= 10) and (Maps[Hero.floor, NeighborIndex + 2] = 12) then
    Hero.facing := 3;
  NeighborIndex := ScratchIndex + 1;
  if (Hero.x >= 0) and (Hero.x < 10) and (Maps[Hero.floor, NeighborIndex + 2] = 12) then
    Hero.facing := 2;
  NeighborIndex := ScratchIndex + 11;
  if (Hero.y >= 0) and (Hero.y < 10) and (Maps[Hero.floor, ScratchIndex + 13] = 12) then
    Hero.facing := 4;
end;

procedure FaceDownLanding; { $00443050 }
begin
  ScratchIndex := Hero.y * 11 + Hero.x;
  NeighborIndex := ScratchIndex - 11;
  if (Hero.y >= 1) and (Hero.y <= 10) and (Maps[Hero.floor, NeighborIndex + 2] = 11) then
    Hero.facing := 1;
  NeighborIndex := ScratchIndex - 1;
  if (Hero.x >= 1) and (Hero.x <= 10) and (Maps[Hero.floor, NeighborIndex + 2] = 11) then
    Hero.facing := 3;
  NeighborIndex := ScratchIndex + 1;
  if (Hero.x >= 0) and (Hero.x < 10) and (Maps[Hero.floor, NeighborIndex + 2] = 11) then
    Hero.facing := 2;
  NeighborIndex := ScratchIndex + 11;
  if (Hero.y >= 0) and (Hero.y < 10) and (Maps[Hero.floor, ScratchIndex + 13] = 11) then
    Hero.facing := 4;
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
    1..12, 15, 17, 18, 29..60, 106..114, 124..132: DoorOpened := 0;
    13, 14: DoorOpened := 147;
    16: DoorOpened := 2;
    19..26: DoorOpened := 1;
    27, 28:
      if Hero.Word464 <> 1 then
        DoorOpened := 1
      else
        DoorOpened := 0;
    61..96: DoorOpened := 1;
    97..105, 115..123: DoorOpened := 9;
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
var
  Attack: Longint;
begin
  StrikeCount := 0;
  RemainingHP := Monsters[MonsterIndex].HP * (Hero.cycle_factor_minus_one + 1);
  CountBattleHeroStrikes;
  Attack := Monsters[MonsterIndex].Attack * (Hero.cycle_factor_minus_one + 1);
  if Hero.defense - Attack >= 0 then
    Damage := 0
  else
    Damage := (Attack - Hero.defense) * StrikeCount;
end;

procedure PushCommand(Opcode, A, B: Word);
begin
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Opcode;
  EventStack[EventCursor].A := A;
  EventStack[EventCursor].B := B;
end;

procedure DoorAnimation; { $004660D0 }
var
  A, B: Word;
  Frame: Integer;
begin
  ScratchIndex := Smallint(EventStack[EventCursor].A);
  NeighborIndex := Smallint(EventStack[EventCursor].B);
  A := Word(ScratchIndex);
  B := Word(NeighborIndex);
  EventStack[EventCursor].Opcode := 0;
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 16;
  PushCommand(13, A, B);
  for Frame := 15 downto 1 do
  begin
    PushCommand(0, 0, Frame);
    PushCommand(13, A, B);
  end;
end;

procedure MattockWall; { $00451B98; DoorAnimation executes in the same chain }
begin
  PushCommand(0, 0, 0);
  PushCommand(13, NeighborIndex, 7);
  DoorAnimation;
  PushCommand(0, 0, 0);
  PushCommand(1, 1, 0);
end;

procedure CrystalLava; { $00451D3C }
var
  Index: Word;
begin
  PushCommand(0, 0, 0);
  Index := Word(NeighborIndex);
  PushCommand(17, Index, 6);
  PushCommand(0, 0, 0);
  PushCommand(13, Index, Word(DamageMode));
  DoorAnimation;
  PushCommand(0, 0, 0);
  PushCommand(1, 1, 0);
end;

procedure DoorReward;
begin
  PushCommand(0, 0, 0);
  PushCommand(6, 36, 43);
  PushCommand(0, 0, 0);
  PushCommand(1, 2, 0);
  PushCommand(0, 0, 0);
  PushCommand(0, 0, 0);
end;

procedure CheckSpecialDoors; { $0047BEAC }
begin
  if Hero.floor = 39 then
  begin
    if (Maps[39, 14]
                + Maps[39, 18]
                + Maps[39, 36]
                + Maps[39, 38]
                + Maps[39, 58]
                + Maps[39, 60]
                + Maps[39, 62]
            = 7)
        and (Maps[39, 16] = 6)
        and (ContactIndex = 38) then
      DoorReward;
    if (Maps[39, 14]
                + Maps[39, 18]
                + Maps[39, 36]
                + Maps[39, 38]
                + Maps[39, 58]
                + Maps[39, 60]
                + Maps[39, 62]
            = 7)
        and (Maps[39, 40] = 6)
        and (ContactIndex = 14) then
      DoorReward;
  end
  else if (Hero.floor = 43) and (ContactIndex = 7) and (Maps[43, 10] = 93) then
    PushCommand(6, 7, 7);
end;

end.
