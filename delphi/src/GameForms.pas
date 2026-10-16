unit GameForms;

{ Class, component, and published handler names are DFM serialization keys. }
interface
uses
  Windows,
  Messages,
  SysUtils,
  Classes,
  Graphics,
  Controls,
  Forms,
  Dialogs,
  StdCtrls,
  ExtCtrls,
  ComCtrls,
  Menus,
  Buttons,
  FileCtrl,
  MPlayer,
  GameState;

type
{$I FormDeclarations.inc}

var
  MainForm: TTSW10;
  AboutBox: TAboutBox;
  DataHolderForm: TForm4;
  RankingForm: TForm2;

{ Layout helpers are also entry points for the comparison probes. }
procedure ApplyFontLayout(Form: TTSW10);
procedure PrepareSceneGraphics(Form: TTSW10);
procedure PushEvent(Opcode, A, B: Longint);
procedure InitializeAudio(Form: TTSW10);
procedure PlayEffect(Form: TTSW10; Index: Integer);
procedure UpdateFairyRanking(Form: TTSW10; Category: Longint);
procedure QueueEnding(Form: TTSW10);
procedure ConfigurePaths(const Assets, Saves: string);
procedure ActivatePortableInstallation(Form: TTSW10);

implementation
uses
  GameGraphics,
  Persistence,
  Gameplay,
  Audio,
  MMSystem,
  ShellAPI;

constructor TTSW10.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  { Windows forces disabled edit text to COLOR_GRAYTEXT. Keep the message
    line read-only and enabled so its white text remains visible. }
  Edit8.ReadOnly := True;
  Edit8.TabStop := False;
  Edit8.Enabled := True;
  Edit8.Color := clGray;
  Edit8.Font.Color := clWhite;
end;

procedure TTSW10.syokidata;
begin
  {$I InitializeCycle.inc}
end;
procedure TTSW10.mmmes; { $00451C20 }
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
procedure TTSW10.mmes; { $0044C9F0; preserves prior message unless a case matches }
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
procedure TTSW10.kaidanupcheck; { $00442F80; the last matching adjacent stair sets facing }
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
procedure TTSW10.kaidandowncheck; { $00443050 }
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
procedure TTSW10.damecount; { $0045031C }
begin
  if RemainingHP > 0 then
  begin
    RemainingHP :=
        Monsters[MonsterIndex].Defense * (Hero.cycle_factor_minus_one + 1)
            + (RemainingHP - Hero.attack);
    Inc(StrikeCount);
    damecount;
  end;
end;
procedure TTSW10.damecount2; { $00450360 }
begin
  if RemainingHP > 0 then
  begin
    RemainingHP :=
        RemainingHP
            - Hero.attack * 2
            + Monsters[MonsterIndex].Defense * (Hero.cycle_factor_minus_one + 1);
    Inc(StrikeCount);
    damecount2;
  end;
end;
procedure TTSW10.ydamecount; { $004503A8 }
begin
  if RemainingHP > 0 then
  begin
    RemainingHP :=
        RemainingHP
            - Monsters[MonsterIndex].Attack * (Hero.cycle_factor_minus_one + 1)
            + Hero.defense;
    Inc(StrikeCount);
    ydamecount;
  end;
end;
procedure TTSW10.ydameiji; { $00450288 }
begin
  StrikeCount := 0;
  RemainingHP := Hero.hp;
  ydamecount;
  Damage :=
      (Hero.attack - Monsters[MonsterIndex].Defense * (Hero.cycle_factor_minus_one + 1))
          * (StrikeCount - 1);
end;
procedure TTSW10.imagework; { $00454C10; the return register is unused by callers }
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
procedure TTSW10.ydameiji2; { $004502D0 }
begin
  StrikeCount := 0;
  RemainingHP := Hero.hp;
  ydamecount;
  Damage :=
      (Hero.attack * 2 - Monsters[MonsterIndex].Defense * (Hero.cycle_factor_minus_one + 1))
          * (StrikeCount - 1);
end;
procedure TTSW10.damei3; { $004802FC }
begin
  if RemainingHP > 0 then
  begin
    RemainingHP :=
        Monsters[MonsterIndex].Defense * (Hero.cycle_factor_minus_one + 1)
            + (RemainingHP - Hero.attack);
    Inc(StrikeCount);
    damei3;
  end;
end;
procedure TTSW10.ydamei3; { $00480340 }
begin
  if RemainingHP > 0 then
  begin
    RemainingHP :=
        RemainingHP
            - Monsters[MonsterIndex].Attack * (Hero.cycle_factor_minus_one + 1)
            + Hero.defense;
    Inc(StrikeCount);
    ydamei3;
  end;
end;
procedure TTSW10.dameiji2; { $0048028C }
begin
  StrikeCount := 0;
  RemainingHP := Monsters[MonsterIndex].HP * (Hero.cycle_factor_minus_one + 1);
  damei3;
  if Hero.defense - Monsters[MonsterIndex].Attack * (Hero.cycle_factor_minus_one + 1) >= 0 then
    Damage := 0
  else
    Damage :=
        (Monsters[MonsterIndex].Attack * (Hero.cycle_factor_minus_one + 1) - Hero.defense)
            * StrikeCount;
end;
procedure TTSW10.doorstackin; { $004660D0; preserve the original unrolled writes }
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
procedure TTSW10.matokwork; { $00451B98 }
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
  doorstackin;
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
procedure TTSW10.yukiwork; { $00451D3C }
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
  doorstackin;
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
procedure TTSW10.doorcheck; { $0047BEAC }
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

procedure TTSW10.itemdel; { $00450758 }
begin
  InputEnabled := 0;
  if MouseControl1.Checked then
  begin
    BitBtn1.Enabled := False;
    BitBtn2.Enabled := False;
    BitBtn3.Enabled := False;
    BitBtn4.Enabled := False;
  end;
  Image4.Enabled := False;
  Image5.Enabled := False;
  Image6.Enabled := False;
  Image8.Enabled := False;
  Image9.Enabled := False;
  Image10.Enabled := False;
  Image11.Enabled := False;
  Image12.Enabled := False;
  Image13.Enabled := False;
  Image15.Enabled := False;
  Image16.Enabled := False;
  Image17.Enabled := False;
  HighScore1.Enabled := False;
  GameLoad1.Enabled := False;
  GameSave1.Enabled := False;
  Option1.Enabled := False;
end;

procedure TTSW10.itemlive; { $00450880 }
begin
  if Hero.hero_orb <> 2 then
  begin
    if (MouseControl1.Checked = True) and (Timer4.Enabled = False) then
    begin
      BitBtn1.Enabled := True;
      BitBtn1.Visible := True;
      BitBtn2.Enabled := True;
      BitBtn2.Visible := True;
      BitBtn3.Enabled := True;
      BitBtn3.Visible := True;
      BitBtn4.Enabled := True;
      BitBtn4.Visible := True;
    end;
    if KeyboardControl1.Checked = True then
      MainForm.KeyPreview := True;
    if Hero.hero_orb = 1 then
    begin
      Image6.Enabled := True;
      GameSave1.Enabled := True;
    end
    else
    begin
      GameSave1.Enabled := False;
      Image6.Visible := False;
    end;
    if Hero.wisdom_orb = 1 then
      Image5.Enabled := True
    else
      Image5.Visible := False;
    if Hero.flight_orb = 1 then
      Image4.Enabled := True
    else
      Image4.Visible := False;
    if Hero.cross = 1 then
      Image7.Visible := True
    else
      Image7.Visible := False;
    if Hero.elixir = 1 then
      Image8.Enabled := True
    else
      Image8.Visible := False;
    if Hero.mattock = 1 then
      Image9.Enabled := True
    else
      Image9.Visible := False;
    if Hero.bomb = 1 then
      Image10.Enabled := True
    else
      Image10.Visible := False;
    if Hero.warp_staff >= 1 then
      Image11.Enabled := True
    else
      Image11.Visible := False;
    if Hero.ascent_wing = 1 then
      Image12.Enabled := True
    else
      Image12.Visible := False;
    if Hero.descent_wing = 1 then
      Image13.Enabled := True
    else
      Image13.Visible := False;
    if Hero.dragon_slayer = 1 then
      Image14.Visible := True
    else
      Image14.Visible := False;
    if Hero.snow_crystal = 1 then
      Image15.Enabled := True
    else
      Image15.Visible := False;
    if Hero.magic_key = 1 then
      Image16.Enabled := True
    else
      Image16.Visible := False;
    if Hero.super_mattock = 1 then
      Image17.Enabled := True
    else
      Image17.Visible := False;
    if Hero.lucky_gold = 1 then
      Image18.Visible := True
    else
      Image18.Visible := False;
    InputEnabled := 1;
    HighScore1.Enabled := True;
    GameLoad1.Enabled := True;
    Option1.Enabled := True;
  end;
end;

procedure TTSW10.timer2on; { $0044BC0C }
begin
  Timer3.Enabled := False;
  itemdel;
  Timer2.Enabled := True;
end;

procedure TTSW10.Button37Click(Sender: TObject); { $00450B78 }
begin
  Button37.Visible := False;
  Button38.Visible := False;
  itemlive;
end;

procedure TAboutBox.OKButtonClick(Sender: TObject);
begin
  AboutBox.ModalResult := 1;
end;
procedure TAboutBox.AboutBoxonclose(Sender: TObject; var Action: TCloseAction);
begin
  AboutBox.ModalResult := 1;
end;
procedure TAboutBox.image1onclick(Sender: TObject);
begin
  Image1.Visible := False;
  ProgramIcon.Visible := True;
end;
procedure TAboutBox.image2onclick(Sender: TObject);
begin
  Image1.Visible := True;
  ProgramIcon.Visible := False;
  Image2.Visible := False;
end;
procedure TAboutBox.programicononclick(Sender: TObject);
begin
  Image1.Visible := True;
  ProgramIcon.Visible := False;
  Image2.Visible := False;
end;
procedure TAboutBox.Timer1Timer(Sender: TObject);
begin
  if ProgramIcon.Visible = True then
  begin
    Image2.Visible := True;
    ProgramIcon.Visible := False;
  end
  else if Image2.Visible = True then
  begin
    ProgramIcon.Visible := True;
    Image2.Visible := False;
  end;
end;

procedure TForm4.DriveComboBox1Change(Sender: TObject);
begin
  DirectoryListBox1.Drive := DriveComboBox1.Drive;
end;
procedure TForm4.DirectoryListBox1Change(Sender: TObject);
begin
  memo1.Text := DirectoryListBox1.Directory;
  FileListBox1.Directory := DirectoryListBox1.Directory;
end;
procedure TForm4.Button2Click(Sender: TObject);
begin
  DataHolderForm.ModalResult := 1;
end;

{$I GraphicsMethods.inc}
{$I FlightMethods.inc}
{$I StartupMethods.inc}
{$I UiMethods.inc}
{$I AudioMethods.inc}
{$I PersistenceMethods.inc}
{$I OptionsMethods.inc}
{$I EventMethods.inc}
{$I GameplayMethods.inc}
end.
