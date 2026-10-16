unit Gameplay;

{ Combat arithmetic and byte-offset access to persisted hero fields. }
interface
uses
  GameState;

type
  THeroWords = array[0..HeroWordCount - 1] of Longint;
  PHeroWords = ^THeroWords;

function MonsterForTile(Tile: Longint): Longint;
function AttackMultiplier(Enemy: Longint; EnemyFirst: Boolean): Longint;
function AttackPenetrates(Enemy: Longint): Boolean;
function ForecastDamage(Enemy: Longint; EnemyFirst, Orb: Boolean; var Hits: Longint): Longint;
function ReadHeroField(Offset: Longint): Longint;
procedure WriteHeroField(Offset, Value: Longint);
function ClueFieldOffset(Index: Longint): Longint;

implementation

function ReadHeroField(Offset: Longint): Longint;
begin
  { The 684-byte hero record contains 171 aligned four-byte fields. }
  if (Offset < 0) or (Offset > HeroLastWordOffset) or (Offset mod SizeOf(Longint) <> 0) then
    ReadHeroField := 0
  else
    ReadHeroField := PHeroWords(@Hero)^[Offset div SizeOf(Longint)];
end;

procedure WriteHeroField(Offset, Value: Longint);
begin
  if (Offset >= 0) and (Offset <= HeroLastWordOffset) and (Offset mod SizeOf(Longint) = 0) then
    PHeroWords(@Hero)^[Offset div SizeOf(Longint)] := Value;
end;

function ClueFieldOffset(Index: Longint): Longint;
{ Clues use noncontiguous fields in the persisted hero record. }
const
  Offsets: array[0..23] of Longint = (
      272,
      276,
      220,
      224,
      228,
      236,
      280,
      288,
      292,
      296,
      300,
      244,
      304,
      308,
      312,
      248,
      316,
      252,
      320,
      324,
      256,
      328,
      260,
      332
  );
begin
  if (Index >= 0) and (Index <= 23) then
    ClueFieldOffset := Offsets[Index]
  else
    ClueFieldOffset := -1;
end;

function MonsterForTile(Tile: Longint): Longint; { $0044A480 }
begin
  MonsterForTile := -1;
  { Ordinary monsters have two animation tiles each. The octopus uses a
    body range, while only the dragon's head tile starts its battle. }
  if (Tile >= tileGreenSlime) and (Tile <= tileVampire + 1) then
    MonsterForTile := (Tile - tileGreenSlime) div 2
  else if (Tile >= tileOctopusFirst) and (Tile <= tileOctopusLast) then
    MonsterForTile := Ord(monsterOctopus)
  else if Tile = tileDragonHead then
    MonsterForTile := Ord(monsterDragon)
  else if (Tile >= tileGoldenKnight) and (Tile <= tileGateKeeperA + 1) then
    MonsterForTile := (Tile - tileGoldenKnight) div 2 + Ord(monsterGoldenKnight);
end;

function AttackMultiplier(Enemy: Longint; EnemyFirst: Boolean): Longint;
begin
  AttackMultiplier := 1;
  { Scripted enemy-first battles bypass the Cross and Dragon Slayer bonuses. }
  if EnemyFirst then
    Exit;
  if ((Enemy = Ord(monsterZombie))
          or (Enemy = Ord(monsterZombieKnight))
          or (Enemy = Ord(monsterVampire)))
      and (Hero.cross <> 0) then
    AttackMultiplier := 2;
  if (Enemy = Ord(monsterDragon)) and (Hero.dragon_slayer <> 0) then
    AttackMultiplier := 2;
end;

function AttackPenetrates(Enemy: Longint): Boolean;
begin
  AttackPenetrates := False;
  if (Enemy < 0) or (Enemy > MonsterCount - 1) then
    Exit;
  { Base attack must beat scaled defense before equipment bonuses apply.
    Penetration is independent of wrapped total damage. }
  AttackPenetrates := Hero.attack > Monsters[Enemy].Defense * (Hero.cycle_factor_minus_one + 1);
end;

function ForecastDamage(
    Enemy: Longint;
    EnemyFirst, Orb: Boolean;
    var Hits: Longint
): Longint; { $00450064, $0044FF0C, $0048028C }
var
  Scale, Hit, EnemyHit, HP: Longint;
begin
  Hits := 0;
  ForecastDamage := -1;
  if not AttackPenetrates(Enemy) then
    Exit;
  Scale := Hero.cycle_factor_minus_one + 1;
  Hit := Hero.attack;
  if not Orb then
    Hit := Hit * AttackMultiplier(Enemy, EnemyFirst);
  Hit := Hit - Monsters[Enemy].Defense * Scale;
  HP := Monsters[Enemy].HP * Scale;
  { Round up so a partial final strike still counts as a turn. }
  Hits := HP div Hit;
  if HP mod Hit <> 0 then
    Inc(Hits);
  EnemyHit := Monsters[Enemy].Attack * Scale - Hero.defense;
  if EnemyHit < 0 then
    EnemyHit := 0;
  { A hero-first victory ends before the enemy can take its final turn. }
  if EnemyFirst then
    ForecastDamage := EnemyHit * Hits
  else
    ForecastDamage := EnemyHit * (Hits - 1);
end;

end.
