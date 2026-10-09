unit GameState;

{ Record sizes and field order are part of the save-file format.
  EMULATOR_ADDRESSES maps globals to fixed addresses in an isolated CPU probe. }
{$A+,Z-,O+,R-,Q-,S-}

interface

type
  THeroState = record
  {$I HeroFields.inc}
  end;
  TFloorMaps = array[0..50, 0..122] of Byte;
  TMonsterStats = record
    HP, Attack, Defense, Gold: Longint;
  end;
  TMonsterTable = array[0..32] of TMonsterStats;
  TEventCommand = packed record
    Opcode, A, B: Word;
  end;
  { Large battles stream their turns when the complete queue exceeds this bound. }
  TEventStack = array[0..29999] of TEventCommand;

const
  { option.dat: two font sizes, reserved, speed, controls, intro, music,
    muted effects, display size, reserved. }
  GameOptions: array[0..9] of Byte = (10, 12, 0, 1, 0, 1, 0, 0, 0, 0);
var
  DataDirectory, FloorSpacing, MessageText, MonsterText: string;
  PortableInstallation, SkipIntroduction: Boolean;
  GameplayEnemyFirst: Boolean;
  IOPath, WindowsDirectory, SaveDirectory, AssetDirectory: string;
  PlayerName: string[10];
  SettingsFile: file;
  UiSpan, UiStep, DrawX, DrawY, DrawIndex, NeighborY, FlightCell: Longint;
  RenderOrder: array[0..120] of Byte;
  DrawFlag1, DrawFlag2: Word;
  AnimationFrame: Byte;
  KeysPainted: Word;
  { Runtime continuations shared by input, combat and the event interpreter. }
  GameplayShopKind, GameplayShopID, GameplayShopCost, GameplayHintIndex, GameplayMonsterChoice:
      Longint;
{$IFDEF EMULATOR_ADDRESSES}
  Hero: THeroState absolute $004B8688;
  Maps: TFloorMaps absolute $004B8934;
  Monsters: TMonsterTable absolute $00489910;
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
  EventStack: TEventStack absolute $0048C74C;
  ContactIndex: Longint absolute $0048C584;
  DamageMode: Longint absolute $0048C564;
  InputEnabled: Word absolute $0048C5CA;
  DialogueStage: Longint absolute $0048C5B0;
  BattleHP: Longint absolute $0048C5BC;
  EventPaused: Boolean absolute $0048C5C0;
  FacingRequest: Longint absolute $0048C590;
  HeroCell: Longint absolute $0048C580;
  PreviousCell: Longint absolute $0048C588;
  MouseRepeat: Word absolute $0048C5C4;
  RepeatEnabled: Word absolute $0048C5C6;
  SceneReady: Word absolute $0048C5D2;
{$ELSE}
  Hero: THeroState;
  Maps: TFloorMaps;
  Monsters: TMonsterTable;
  ScratchIndex, NeighborIndex, TileClass, MonsterIndex: Longint;
  RemainingHP, StrikeCount, Damage, GraphicTile, DoorOpened: Longint;
  EventCursor, ContactIndex: Longint;
  DamageMode: Longint;
  InputEnabled: Word;
  DialogueStage, BattleHP, FacingRequest, PreviousCell: Longint;
  HeroCell: Longint absolute FlightCell;
  EventPaused: Boolean;
  MouseRepeat, RepeatEnabled, SceneReady: Word;
  EventStack: TEventStack;
{$ENDIF}

implementation
end.
