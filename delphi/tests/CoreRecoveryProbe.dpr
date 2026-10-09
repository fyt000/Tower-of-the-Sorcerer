library CoreRecoveryProbe;

{ ORIGINAL_ADDRESSES is set by the builder. Read this DLL as bytes only. }
uses OriginalState, OriginalCore;

function HeroStorage: Pointer;
begin Result := @Hero; end;
function MapStorage: Pointer;
begin Result := @Maps; end;
function MonsterStorage: Pointer;
begin Result := @Monsters; end;
function ScratchStorage: Pointer;
begin Result := @ScratchIndex; end;
function NeighborStorage: Pointer;
begin Result := @NeighborIndex; end;
function TileClassStorage: Pointer;
begin Result := @TileClass; end;
function MonsterIndexStorage: Pointer;
begin Result := @MonsterIndex; end;
function RemainingHPStorage: Pointer;
begin Result := @RemainingHP; end;
function StrikeStorage: Pointer;
begin Result := @StrikeCount; end;
function DamageStorage: Pointer;
begin Result := @Damage; end;
function GraphicStorage: Pointer;
begin Result := @GraphicTile; end;
function DoorStorage: Pointer;
begin Result := @DoorOpened; end;
function EventCursorStorage: Pointer;
begin Result := @EventCursor; end;
function EventStackStorage: Pointer;
begin Result := @EventStack; end;
function ContactStorage: Pointer;
begin Result := @ContactIndex; end;
function DamageModeStorage: Pointer;
begin Result := @DamageMode; end;

exports InitializeCycle, ClassifyNeighbor, ClassifyInteraction,
  FaceUpLanding, FaceDownLanding, CountHeroStrikes, CountDoubleHeroStrikes,
  CountEnemyStrikes, EnemyFirstDamage, SelectGraphicFrame,
  DoubleEnemyFirstDamage, CountBattleHeroStrikes, CountBattleEnemyStrikes,
  BattleDamage, DoorAnimation, MattockWall, CrystalLava, CheckSpecialDoors,
  HeroStorage, MapStorage, MonsterStorage, ScratchStorage, NeighborStorage,
  TileClassStorage, MonsterIndexStorage, RemainingHPStorage, StrikeStorage,
  DamageStorage, GraphicStorage, DoorStorage, EventCursorStorage,
  EventStackStorage, ContactStorage, DamageModeStorage;

begin
end.
