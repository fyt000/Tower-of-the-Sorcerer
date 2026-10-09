{ Additional integration checks use the real form handlers and event timer. }
procedure GameplayChecks;
const
  EquipmentGain: array[0..4] of Longint = (10, 20, 40, 50, 100);
var
  T, Hits, DamageValue, InitialHP, InitialAttack, InitialDefense, InitialGold, KeyValue: Longint;
begin
  Room(1);
  Maps[1, 51] := 1;
  Hero.yellow_keys := 0;
  MoveUp;
  Require((Hero.y = 5) and (Maps[1, 51] = 1), 'door-refuses-without-key');
  Room(1);
  Maps[1, 51] := 2;
  Hero.blue_keys := 1;
  MoveUp;
  Require((Hero.blue_keys = 0) and (Maps[1, 51] = 6) and (Hero.y = 5), 'blue-door-contact');
  Room(1);
  Maps[1, 51] := 3;
  Hero.red_keys := 1;
  MoveUp;
  Require((Hero.red_keys = 0) and (Maps[1, 51] = 6), 'red-door-contact');

  for T := 29 to 35 do
  begin
    Room(1);
    Maps[1, 51] := T;
    InitialHP := Hero.hp;
    InitialAttack := Hero.attack;
    InitialDefense := Hero.defense;
    MoveUp;
    Require((Maps[1, 51] = 6) and (Hero.y = 4), 'pickup-moves-and-clears-' + IntToStr(T));
    case T of
      29: Require(Hero.yellow_keys = 1, 'yellow-key-pickup');
      30: Require(Hero.red_keys = 1, 'red-key-pickup');
      31: Require(Hero.blue_keys = 1, 'blue-key-pickup');
      32: Require(Hero.hp = InitialHP + 50, 'red-potion-pickup');
      33: Require(Hero.hp = InitialHP + 200, 'blue-potion-pickup');
      34: Require(Hero.attack = InitialAttack + 1, 'red-gem-pickup');
      35: Require(Hero.defense = InitialDefense + 1, 'blue-gem-pickup');
    end;
  end;
  for T := 37 to 50 do
  begin
    Room(1);
    Maps[1, 51] := T;
    MoveUp;
    if T = 43 then
      KeyValue := 3
    else
      KeyValue := 1;
    Require(
        (ReadHeroField(68 + (T - 36) * 4) = KeyValue) and (Maps[1, 51] = 6),
        'inventory-pickup-' + IntToStr(T)
    );
  end;
  for T := 51 to 60 do
  begin
    Room(1);
    Maps[1, 51] := T;
    InitialAttack := Hero.attack;
    InitialDefense := Hero.defense;
    MoveUp;
    Require(ReadHeroField(128 + (T - 51) * 4) = 1, 'equipment-record-' + IntToStr(T));
    if T < 56 then
      Require(
          Hero.attack = InitialAttack + EquipmentGain[(T - 51) mod 5],
          'sword-gain-' + IntToStr(T)
      )
    else
      Require(
          Hero.defense = InitialDefense + EquipmentGain[(T - 51) mod 5],
          'shield-gain-' + IntToStr(T)
      );
  end;

  Room(1);
  Monsters[12].HP := 100;
  Monsters[12].Attack := 20;
  Monsters[12].Defense := 10;
  Hero.attack := 20;
  Hero.defense := 0;
  Hero.cross := 1;
  DamageValue := ForecastDamage(12, False, False, Hits);
  Require((Hits = 4) and (DamageValue = 60), 'cross-combat-forecast');
  DamageValue := ForecastDamage(12, False, True, Hits);
  Require((Hits = 10) and (DamageValue = 180), 'hero-orb-unmodified-forecast');
  DamageValue := ForecastDamage(12, True, False, Hits);
  Require((Hits = 10) and (DamageValue = 200), 'forced-combat-unmodified-forecast');
  Hero.attack := 10;
  DamageValue := ForecastDamage(12, False, False, Hits);
  Require((DamageValue = -1) and (Hits = 0), 'cross-keeps-defense-gate');
  Room(1);
  Maps[1, 51] := 85;
  Hero.attack := 20;
  Hero.defense := 0;
  Hero.cross := 1;
  Hero.hp := 1000;
  Monsters[12].HP := 100;
  Monsters[12].Attack := 20;
  Monsters[12].Defense := 10;
  MoveUp;
  Require((Hero.hp = 940) and (Maps[1, 51] = 6), 'cross-battle-applies-four-strikes');

  Room(1);
  Hero.gold := 100;
  Maps[1, 51] := 16;
  MoveUp;
  MainForm.Button2Click(nil);
  MainForm.Button39Click(nil);
  Drain;
  Require((Hero.gold = 80) and (Hero.hp = 1100) and (Hero.Word44 = 1), 'altar-hp-purchase');
  ContactIndex := 49;
  MainForm.handan;
  Require(GameplayShopCost = 40, 'altar-next-price');
  MainForm.Button7Click(nil);
  Room(6);
  Hero.gold := 100;
  ContactIndex := 49;
  MainForm.syounin;
  MainForm.Button2Click(nil);
  MainForm.Button1Click(nil);
  Drain;
  Require((Hero.gold = 50) and (Hero.blue_keys = 1) and (Hero.Word172 = 1), 'merchant-trade');
  MainForm.syounin;
  Require(Hero.Word220 = 1, 'merchant-records-hint');
  MainForm.Button1Click(nil);
  Room(4);
  MainForm.roujin;
  MainForm.Button1Click(nil);
  Require(Hero.Word272 = 1, 'old-man-heard-without-wisdom');
  Hero.wisdom_orb := 1;
  MainForm.roujin;
  MainForm.Button1Click(nil);
  Require(Hero.Word272 = 1, 'wisdom-does-not-retroactively-record');

  Room(43);
  Maps[43, 51] := 11;
  Maps[45, 0] := 60;
  MoveUp;
  Require((Hero.floor = 45) and (Hero.x = 5) and (Hero.y = 5), 'stairs-skip-floor44-up');
  Maps[45, 51] := 12;
  Maps[43, 1] := 60;
  MoveUp;
  Require(Hero.floor = 43, 'stairs-skip-floor44-down');
  Room(2);
  Hero.ascent_wing := 1;
  Maps[3, 62] := 6;
  MainForm.img12work;
  MainForm.Button38Click(nil);
  Drain;
  Require(
      (Hero.floor = 3) and (Hero.ascent_wing = 0) and (Hero.x = 5) and (Hero.y = 5),
      'ascent-wing-preserves-cell'
  );
  Room(2);
  Hero.descent_wing := 1;
  Maps[1, 62] := 8;
  MainForm.img13work;
  MainForm.Button38Click(nil);
  Drain;
  Require((Hero.floor = 2) and (Hero.descent_wing = 1), 'blocked-wing-not-consumed');
  Room(1);
  Hero.warp_staff := 3;
  Maps[1, 62] := 8;
  MainForm.img11work;
  MainForm.Button38Click(nil);
  Drain;
  Require((Hero.warp_staff = 2) and (Hero.x = 5) and (Hero.y = 5), 'blocked-warp-consumes-charge');
  Room(1);
  Hero.elixir := 1;
  Hero.attack := 20;
  Hero.defense := 30;
  InitialHP := Hero.hp;
  MainForm.img8work;
  MainForm.Button38Click(nil);
  Drain;
  Require((Hero.elixir = 0) and (Hero.hp = InitialHP + 350), 'elixir-stat-based-healing');
  Room(1);
  Hero.mattock := 1;
  Maps[1, 51] := 8;
  MainForm.img9work;
  MainForm.Button38Click(nil);
  Drain;
  Require((Hero.mattock = 0) and (Maps[1, 51] = 6), 'mattock-opens-wall');
  Room(1);
  Hero.snow_crystal := 1;
  Maps[1, 51] := 13;
  MainForm.img15work;
  MainForm.Button38Click(nil);
  Drain;
  Require((Hero.snow_crystal = 1) and (Maps[1, 51] = 6), 'snow-crystal-reusable');
  Room(1);
  Hero.magic_key := 1;
  Maps[1, 3] := 1;
  Maps[1, 120] := 1;
  Maps[1, 51] := 2;
  MainForm.img16work;
  MainForm.Button38Click(nil);
  Drain;
  Require(
      (Hero.magic_key = 0) and (Maps[1, 3] = 6) and (Maps[1, 120] = 6) and (Maps[1, 51] = 2),
      'magic-key-yellow-only'
  );
  Room(1);
  Hero.super_mattock := 1;
  Maps[1, 3] := 8;
  Maps[1, 120] := 8;
  MainForm.img17work;
  MainForm.Button38Click(nil);
  Drain;
  Require(
      (Hero.super_mattock = 0) and (Maps[1, 3] = 6) and (Maps[1, 120] = 6),
      'super-mattock-floor-walls'
  );

  Room(45);
  Hero.sacred_shield := 0;
  Maps[45, 40] := 151;
  MoveUp;
  Require(Hero.hp = 800, 'magician-adjacent-damage');
  Room(45);
  Hero.sacred_shield := 0;
  Maps[45, 40] := 153;
  MoveUp;
  Require(Hero.hp = 900, 'second-magician-adjacent-damage');
  Room(45);
  Hero.sacred_shield := 0;
  Maps[45, 50] := 93;
  Maps[45, 52] := 93;
  MoveUp;
  Require(Hero.hp = 500, 'sorcerer-pincer-halves-hp');
  Room(45);
  Hero.sacred_shield := 1;
  Maps[45, 40] := 151;
  Maps[45, 50] := 93;
  Maps[45, 52] := 93;
  MoveUp;
  Require(Hero.hp = 1000, 'sacred-shield-prevents-magic-and-pincer');
end;
