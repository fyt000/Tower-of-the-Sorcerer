unit Gameplay;

{ Combat arithmetic and byte-offset access to persisted hero fields. }
interface
uses
  GameState;

type
  THeroWords = array[0..170] of Longint;
  PHeroWords = ^THeroWords;

function MonsterForTile(Tile: Longint): Longint;
function AttackMultiplier(Enemy: Longint; EnemyFirst: Boolean): Longint;
function ForecastDamage(Enemy: Longint; EnemyFirst, Orb: Boolean; var Hits: Longint): Longint;
function ReadHeroField(Offset: Longint): Longint;
procedure WriteHeroField(Offset, Value: Longint);
function ClueFieldOffset(Index: Longint): Longint;

implementation

function ReadHeroField(Offset: Longint): Longint;
begin
  { The 684-byte hero record contains 171 aligned four-byte fields. }
  if (Offset < 0) or (Offset > 680) or (Offset mod 4 <> 0) then
    ReadHeroField := 0
  else
    ReadHeroField := PHeroWords(@Hero)^[Offset div 4];
end;

procedure WriteHeroField(Offset, Value: Longint);
begin
  if (Offset >= 0) and (Offset <= 680) and (Offset mod 4 = 0) then
    PHeroWords(@Hero)^[Offset div 4] := Value;
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
  if (Tile >= 61) and (Tile <= 96) then
    MonsterForTile := (Tile - 61) div 2
  else if (Tile >= 97) and (Tile <= 114) then
    MonsterForTile := 18
  else if Tile = 122 then
    MonsterForTile := 19
  else if (Tile >= 133) and (Tile <= 158) then
    MonsterForTile := (Tile - 133) div 2 + 20;
end;

function AttackMultiplier(Enemy: Longint; EnemyFirst: Boolean): Longint;
begin
  AttackMultiplier := 1;
  { Scripted enemy-first battles bypass the Cross and Dragon Slayer bonuses. }
  if EnemyFirst then
    Exit;
  if ((Enemy = 12) or (Enemy = 13) or (Enemy = 17)) and (Hero.cross <> 0) then
    AttackMultiplier := 2;
  if (Enemy = 19) and (Hero.dragon_slayer <> 0) then
    AttackMultiplier := 2;
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
  if (Enemy < 0) or (Enemy > 32) then
    Exit;
  Scale := Hero.cycle_factor_minus_one + 1;
  { Base attack must beat scaled defense before equipment bonuses apply. }
  if Hero.attack <= Monsters[Enemy].Defense * Scale then
    Exit;
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
