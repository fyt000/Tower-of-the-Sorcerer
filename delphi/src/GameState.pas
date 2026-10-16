unit GameState;

{ Record sizes and field order are part of the save-file format.
  EMULATOR_ADDRESSES maps globals to fixed addresses in an isolated CPU probe. }
{$A+,Z-,O+,R-,Q-,S-}

interface

const
  { Untyped constants fold to the existing immediates; typed constants would
    allocate storage and can change the linked binary. }
  BoardWidth = 11;
  BoardCellCount = BoardWidth * BoardWidth;
  FloorCount = 51;
  MapTileOffset = 2;
  MonsterCount = 33;
  HeroWordCount = 171;
  HeroLastWordOffset = (HeroWordCount - 1) * SizeOf(Longint);
  DialogueStageOffset = 10;
  stageNone = 0;
  stageAltar = 2;

  { option.dat byte positions; slots 6/7 retain their audio definitions. }
  optionSmallFont = 0;
  optionLargeFont = 1;
  optionReserved2 = 2;
  optionSpeed = 3;
  optionControls = 4;
  optionIntroduction = 5;
  optionDisplaySize = 8;
  optionReserved9 = 9;

  { Keep byte option values untyped: Ord(enum) widens Delphi 2 comparisons. }
  gameSpeedUnspecified = 0;
  gameSpeedHigh = 1;
  gameSpeedMiddle = 2;
  gameSpeedLow = 3;
  controlMouse = 0;
  controlKeyboard = 1;
  display640x400 = 0;
  display800x500 = 1;

  { Original map/atlas IDs. Animated pairs use the base ID plus one. }
  tileVoid = 0;
  tileYellowDoor = 1;
  tileBlueDoor = 2;
  tileRedDoor = 3;
  tileSealedGate = 4;
  tilePrisonGate = 5;
  tileRoad = 6;
  tileSpecialRoad = 7;
  tileWall = 8;
  tileSecretWall = 9;
  tileHiddenObject = 10;
  tileStairsUp = 11;
  tileStairsDown = 12;
  tileLava = 13;
  tileStarVoid = 14;
  tileSolidDecoration = 15;
  tileAltar = 16;
  tileAltarTop = 17;
  tileAltarSide = 18;
  tileMerchant = 19;
  tileMerchant2 = 20;
  tileThief = 21;
  tileThief2 = 22;
  tileFairy = 23;
  tileFairy2 = 24;
  tileOldMan = 25;
  tileOldMan2 = 26;
  tileTimeGate = 27;
  tileTimeGate2 = 28;
  tileYellowKey = 29;
  tileRedKey = 30;
  tileBlueKey = 31;
  tileRedPotion = 32;
  tileBluePotion = 33;
  tileRedGem = 34;
  tileBlueGem = 35;
  tileHeroOrb = 36;
  tileWisdomOrb = 37;
  tileFlightOrb = 38;
  tileCross = 39;
  tileElixir = 40;
  tileMattock = 41;
  tileBomb = 42;
  tileWarpStaff = 43;
  tileAscentWing = 44;
  tileDescentWing = 45;
  tileDragonSlayer = 46;
  tileSnowCrystal = 47;
  tileMagicKey = 48;
  tileSuperMattock = 49;
  tileLuckyGold = 50;
  tileIronSword = 51;
  tileSilverSword = 52;
  tileKnightSword = 53;
  tileHolySword = 54;
  tileSacredSword = 55;
  tileIronShield = 56;
  tileSilverShield = 57;
  tileKnightShield = 58;
  tileHolyShield = 59;
  tileSacredShield = 60;
  tileGreenSlime = 61;
  tileRedSlime = 63;
  tileBigSlime = 65;
  tileBat = 67;
  tilePriest = 69;
  tileSuperionPriest = 71;
  tileGateKeeperC = 73;
  tileGateKeeperB = 75;
  tileSkeletonC = 77;
  tileSkeletonB = 79;
  tileSkeletonA = 81;
  tileBigBat = 83;
  tileZombie = 85;
  tileZombieKnight = 87;
  tileRock = 89;
  tileZeno = 91;
  tileSorcerer = 93;
  tileVampire = 95;
  tileOctopusFirst = 97;
  tileOctopusMouth = 104;
  tileOctopusLast = 114;
  tileDragonFirst = 115;
  tileDragonHead = 122;
  tileGoldenKnight = 133;
  tileKnight = 135;
  tileSwordsman = 137;
  tileSoldier = 139;
  tileGhostSoldier = 141;
  tileSlimeMan = 143;
  tileGreatMagicMaster = 145;
  tileVampireBat = 147;
  tileSlimeLord = 149;
  tileMagicianA = 151;
  tileMagicianB = 153;
  tileDarkKnight = 155;
  tileGateKeeperA = 157;
  tileStairCover = 159;

  { One-based speech IDs; continuation stage = speech + DialogueStageOffset. }
  speechUnconscious = 1;
  speechThiefCallsHero = 2;
  speechThiefWakesHero = 3;
  speechThiefOpensPrison = 4;
  speechThiefFirstDeparture = 5;
  speechThiefReturnsToPrison = 6;
  speechThiefPromisesToFollow = 7;
  speechOldManRescueReward = 8;
  speechMerchantRescueReward = 9;
  speechZenoCaptureChallenge = 10;
  speechHeroCaptured = 11;
  speechOldManHeroOrb = 12;
  speechSkeletonLordChallenge = 13;
  speechSkeletonLordBattle = 14;
  speechSkeletonLordDefeated = 15;
  speechFairyFloor10 = 16;
  speechThiefSecondDeparture = 17;
  speechThiefOctopusTunnel = 18;
  speechOldManElixir = 19;
  speechVampireChallenge = 20;
  speechVampireDefeated = 21;
  speechFairyFloor20 = 22;
  speechRockChallenge = 23;
  speechFairyFloor25 = 24;
  speechTimeGateInvitation = 25;
  speechHeroFindsDoll = 26;
  speechThiefUnfinishedTunnel = 27;
  speechThiefFinishedTunnel = 28;
  speechThiefWarnsAboutBoss = 29;
  speechGreatMagicMasterChallenge = 30;
  speechGreatMagicMasterRetreat = 31;
  speechThiefDragonTunnel = 32;
  speechThiefGoldenKnightAdvice = 33;
  speechGreatMagicMasterFinalChallenge = 34;
  speechGreatMagicMasterSummonsSoldiers = 35;
  speechGreatMagicMasterSummonsSwordsmen = 36;
  speechGreatMagicMasterSummonsKnights = 37;
  speechGreatMagicMasterBattle = 38;
  speechGreatMagicMasterDefeated = 39;
  speechFairyFloor40 = 40;
  speechGoldenKnightReportsFailure = 41;
  speechZenoRebukesGoldenKnight = 42;
  speechGoldenKnightPleads = 43;
  speechZenoPromisesFairFight = 44;
  speechZenoFinalChallenge = 45;
  speechZenoDefeated = 46;
  speechFairyFloor49 = 47;
  speechHeroFindsThief = 48;
  speechThiefRevealsDisguise = 49;
  speechHeroRecognizesZeno = 50;
  speechZenoExplainsTest = 51;
  speechHeroQuestionsTest = 52;
  speechZenoExplainsLegend = 53;
  speechHeroQuestionsLegend = 54;
  speechZenoRevealsPlan = 55;
  speechHeroQuestionsPrincessRumor = 56;
  speechZenoOffersAlliance = 57;
  speechOldManFloor23 = 61;
  speechBacksideZenoDefeated = 62;
  speechThiefTimeGate = 264;

  { Zero-based indices in the original ListBox2 text catalog. }
  textThiefFirstEquipmentAdvice = 57;
  textThiefSecondEquipmentAdvice = 58;
  textZenoPlan = 59;
  textWisdomHintBase = 62;
  textZenoDefeated = 61;
  textOldManFinished = 86;
  textOldManRescueReward = 87;
  textOldManHeroOrb = 88;
  textOldManElixir = 89;
  textNoMoreAdvice = 90;
  textMerchantRescueThanks = 91;
  textMerchantOfferBase = 246;
  textStatusOffset = 127;
  textFairyScorePrefix = 220;
  textFairyScoreSuffix = 221;
  textFairyReconsider = 222;
  textFairyBelowAverage = 223;
  textFairyOrdinary = 224;
  textFairyDoingFine = 225;
  textFairyGreatScore = 226;
  textFairyContinue = 227;
  textFairyTitlePrefix = 228;
  textFairyFighter = 229;
  textFairyBrave = 230;
  textFairyHero = 231;
  textFairySwordEmperor = 232;
  textFairyFighterGod = 233;
  textFairyTitleSuffix = 234;
  textFairyKeepGoing = 235;
  textFairyFarewell = 236;
  textFairyRankPrefix = 244;
  textFairyRankSuffix = 245;

type
  { Semantic names only: persisted fields and event operands keep their original
    integer types. Use Ord at access sites; never reorder enum members.
    Saved facing and movement requests have different up/down encodings.
    Word632 is Flight direction; Word664 is the highest-floor stair kind. }
  THeroFacing = (hfNone, hfDown, hfLeft, hfRight, hfUp);
  TMoveRequest = (moveNone, moveUp, moveLeft, moveRight, moveDown);
  TFlightDirection = (flightNone, flightUp, flightDown);
  TStairKind = (stairNone, stairUp, stairDown);
  TEquipmentTier = (
      equipmentNone,
      equipmentIron,
      equipmentSilver,
      equipmentKnight,
      equipmentHoly,
      equipmentSacred
  );
  TInventoryChoice = (
      itemNone,
      itemHeroOrb,
      itemWisdomOrb,
      itemFlightOrb,
      itemCross,
      itemElixir,
      itemMattock,
      itemBomb,
      itemWarpStaff,
      itemAscentWing,
      itemDescentWing,
      itemDragonSlayer,
      itemSnowCrystal,
      itemMagicKey,
      itemSuperMattock,
      itemLuckyGold
  );
  TShopMode = (shopMerchant, shopAltar);
  TMonsterKind = (
      monsterGreenSlime,
      monsterRedSlime,
      monsterBigSlime,
      monsterBat,
      monsterPriest,
      monsterSuperionPriest,
      monsterGateKeeperC,
      monsterGateKeeperB,
      monsterSkeletonC,
      monsterSkeletonB,
      monsterSkeletonA,
      monsterBigBat,
      monsterZombie,
      monsterZombieKnight,
      monsterRock,
      monsterZeno,
      monsterSorcerer,
      monsterVampire,
      monsterOctopus,
      monsterDragon,
      monsterGoldenKnight,
      monsterKnight,
      monsterSwordsman,
      monsterSoldier,
      monsterGhostSoldier,
      monsterSlimeMan,
      monsterGreatMagicMaster,
      monsterVampireBat,
      monsterSlimeLord,
      monsterMagicianA,
      monsterMagicianB,
      monsterDarkKnight,
      monsterGateKeeperA
  );
  THeroState = record
  {$I HeroFields.inc}
  end;
  TFloorMaps = array[0..FloorCount - 1, 0..MapTileOffset + BoardCellCount - 1] of Byte;
  TMonsterStats = record
    HP, Attack, Defense, Gold: Longint;
  end;
  TMonsterTable = array[0..MonsterCount - 1] of TMonsterStats;
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
  RenderOrder: array[0..BoardCellCount - 1] of Byte;
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
