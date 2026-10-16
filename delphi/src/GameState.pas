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
  { Names recovered from the event interpreter. Declaration order is the
    original opcode number (0..22); never reorder these members. Use Ord(...)
    at write sites so the packed command remains three 16-bit words. }
  TEventOpcode = (
      evWait, { 0: Delay; A/B can be operands for the next animation. }
      evSound, { 1: Sound effect or music action selected by A. }
      evRefreshStatus, { 2: Refresh status/message, optionally selecting message A. }
      evDefeat, { 3: Pause for the defeat dialogue. }
      evEnemyAttack, { 4: Apply the enemy's hit to hero HP. }
      evHeroAttack, { 5: Apply the hero's hit to battle HP. }
      evSetTile, { 6: Set map cell A to tile B and redraw it. }
      evAwardGold, { 7: Award A gold with the lucky-gold multiplier. }
      evShowPanels, { 8: Restore key/item panels. }
      evOverlay, { 9: Draw mask B at cell A using the paired wait operands. }
      evDialogue, { 10: Pause for story dialogue A. }
      evSceneAction, { 11: Scene subcommand A with parameter B. }
      evMoveMonster, { 12: Animate a monster's move. }
      evDoorFrame, { 13: Draw a door/wall frame using the paired wait. }
      evHeroAttackOverlay, { 14: Apply a hero hit and draw an overlay. }
      evFloorMusic, { 15: Select and play the floor's music. }
      evChangeHP, { 16: Add signed A to hero HP. }
      evSetTileOnly, { 17: Set map cell A to tile B without redrawing. }
      evReserved, { 18: No action in the original dispatcher. }
      evHalveHP, { 19: Halve hero HP. }
      evSetHeroWord, { 20: Set hero word A to B. }
      evWipe, { 21: Reveal/cover cell B in the original render order. }
      evResetCycle { 22: Reset cycle flags and restart. }
  );
  TEventCommand = packed record
    Opcode, A, B: Word;
  end;
  { Provisioned event storage; the original array declaration is unverified. }
  TEventStack = array[0..29999] of TEventCommand;

const
  { option.dat: two font sizes, reserved, speed, controls, intro, music,
    muted effects, display size, reserved. }
  GameOptions: array[0..9] of Byte = (10, 12, 0, 1, 0, 1, 0, 0, 0, 0);
var
  DataDirectory, FloorSpacing, MessageText, MonsterText, DamageText: string;
  PortableInstallation, SkipIntroduction: Boolean;
  IOPath, WindowsDirectory, SaveDirectory, AssetDirectory: string;
  PlayerName: string[10];
  SettingsFile: file;
  UiSpan, UiStep, DrawX, DrawY, DrawIndex, NeighborY, FlightCell: Longint;
  RenderOrder: array[0..120] of Byte;
  DrawFlag1: Word;
  DrawFlag2: Smallint;
  AnimationFrame: Boolean;
  KeysPainted: Word;
  { Runtime continuations shared by input, combat and the event interpreter. }
  GameplayShopKind, GameplayShopID, GameplayHintIndex, GameplayMonsterChoice: Longint;
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
  OrbRow: Longint absolute $0048C5B0;
  OrbEnemies: array[1..7] of Byte absolute $00489908;
  ShopMode: Smallint absolute $0048C5CC;
  MerchantTradeWord: Longint absolute $0048C598;
  MerchantClueWord: Longint absolute $0048C59C;
  DialogueSpeech: Smallint absolute $0048C5C8;
  DialogueStage: Longint absolute $0048C5A4;
  GameplayShopCost: Longint absolute $0048C594;
  BattleHP: Longint absolute $0048C5BC;
  EventPaused: Longint absolute $0048C5C0;
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
  OrbRow: Longint;
  OrbEnemies: array[1..7] of Byte;
  ShopMode: Smallint;
  MerchantTradeWord, MerchantClueWord: Longint;
  DialogueSpeech: Smallint;
  DialogueStage, GameplayShopCost, BattleHP, FacingRequest, PreviousCell: Longint;
  HeroCell: Longint absolute FlightCell;
  EventPaused: Longint;
  MouseRepeat, RepeatEnabled, SceneReady: Word;
  EventStack: TEventStack;
{$ENDIF}

implementation
end.
