unit OriginalState;

{ Original storage layout. Native builds use linker-owned storage. The
  ORIGINAL_ADDRESSES build is exclusively for isolated emulator comparisons. }
{$A+,Z-,O+,R-,Q-,S-}

interface

type
  TOriginalHero = record
{$I HeroFields.inc}
  end;
  TOriginalMaps = array[0..50, 0..122] of Byte;
  TOriginalMonster = record
    HP, Attack, Defense, Gold: Longint;
  end;
  TOriginalMonsters = array[0..32] of TOriginalMonster;
  TOriginalCommand = packed record
    Opcode, A, B: Word;
  end;
  { Storage provision for native reconstruction; original declared bound is
    not recovered. Comparisons state their exercised queue prefix explicitly. }
  TOriginalEventStack = array[0..29999] of TOriginalCommand;

const
  { Options is the original ten-byte option.dat record, initialized in .data. }
  OriginalOptions: array[0..9] of Byte = (10, 12, 0, 1, 0, 1, 0, 0, 0, 0);
var
  DataDirectory, FloorSpacing, MessageText, MonsterText: string;
  IOPath, WindowsDirectory, SaveDirectory, AssetDirectory: string;
  PlayerName: string[10];
  SettingsFile: file;
  UiSpan, UiStep, DrawX, DrawY, DrawIndex, NeighborY, FlightCell: Longint;
  RenderOrder: array[0..120] of Byte;
  DrawFlag1, DrawFlag2: Word;
  AnimationFrame: Byte;
  KeysPainted: Word;
{$IFDEF ORIGINAL_ADDRESSES}
  Hero: TOriginalHero absolute $004B8688;
  Maps: TOriginalMaps absolute $004B8934;
  Monsters: TOriginalMonsters absolute $00489910;
  ScratchIndex: Longint absolute $0048C558;
  NeighborIndex: Longint absolute $0048C55C;
  TileClass: Longint absolute $0048C58C;
  MonsterIndex: Longint absolute $0048C5B8;
  RemainingHP: Longint absolute $0048C5B4;
  StrikeCount: Longint absolute $0048C56C;
  Damage: Longint absolute $0048C568;
  GraphicTile: Longint absolute $0048C5A8;
  DoorOpened: Longint absolute $0048C554;
  EventCursor: Longint absolute $0048C5AC;
  EventStack: TOriginalEventStack absolute $0048C74C;
  ContactIndex: Longint absolute $0048C584;
  DamageMode: Longint absolute $0048C564;
  InputEnabled: Word absolute $0048C5CA;
{$ELSE}
  Hero: TOriginalHero;
  Maps: TOriginalMaps;
  Monsters: TOriginalMonsters;
  ScratchIndex, NeighborIndex, TileClass, MonsterIndex: Longint;
  RemainingHP, StrikeCount, Damage, GraphicTile, DoorOpened: Longint;
  EventCursor, ContactIndex: Longint;
  DamageMode: Longint;
  InputEnabled: Word;
  EventStack: TOriginalEventStack;
{$ENDIF}

implementation
end.
