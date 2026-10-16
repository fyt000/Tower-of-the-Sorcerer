{ Additional integration checks use the real form handlers and event timer. }
procedure GameplayChecks;
const
  EquipmentGain: array[0..4] of Longint = (10, 20, 40, 50, 100);
var
  T, Hits, DamageValue, InitialHP, InitialAttack, InitialDefense, InitialGold, KeyValue: Longint;
  ClueLeft, ClueTop, CloseLeft, CloseTop: Longint;
begin
  Room(1);
  FillChar(Hero.hero_orb, 15 * SizeOf(Longint), 0);
  DrawFlag2 := 7;
  { The original caller skips the recursive scanner for an empty inventory. }
  MainForm.itemichiwork(4);
  Require(DrawFlag2 = 7, 'empty-inventory-caller-skips-recursive-scan');
  Hero.wisdom_orb := 1;
  Hero.elixir := 1;
  DrawFlag2 := 0;
  DrawFlag1 := 1;
  MainForm.itemichiwork(0);
  Require(
      (DrawFlag2 = 4)
          and MainForm.Image22.Visible
          and not MainForm.k1.Enabled
          and (MainForm.Image22.Top = MainForm.Image8.Top)
          and (MainForm.Image22.Left = MainForm.Image8.Left)
          and (MainForm.Image22.Picture.Bitmap.Width = MainForm.Image6.Width),
      'empty-inventory-column-uses-original-fallback-and-highlight'
  );
  Key := VK_ESCAPE;
  MainForm.formkeydown(nil, Key, []);
  Require(
      not MainForm.Image22.Visible
          and MainForm.k1.Enabled
          and (DrawFlag1 = 0)
          and (Key = VK_ESCAPE),
      'inventory-escape-restores-menu-without-consuming-key'
  );
  Room(1);
  Hero.wisdom_orb := 1;
  Hero.Word272 := 2;
  Hero.Word276 := 1;
  ClueLeft := MainForm.Button11.Left;
  ClueTop := MainForm.Button11.Top;
  CloseLeft := MainForm.Button35.Left;
  CloseTop := MainForm.Button35.Top;
  MainForm.img5work;
  Require(
      (DialogueStage = 1)
          and MainForm.Button11.Visible
          and MainForm.Button11.Enabled
          and MainForm.Button12.Visible
          and not MainForm.Button12.Enabled
          and (MainForm.Button11.Left = ClueLeft)
          and (MainForm.Button11.Top = ClueTop)
          and (MainForm.Button35.Left = CloseLeft)
          and (MainForm.Button35.Top = CloseTop),
      'wisdom-keeps-form-grid-and-enables-only-recorded-clues'
  );
  MainForm.Button11Click(nil);
  MainForm.Button35Click(nil);
  Require(
      (DialogueStage = 0)
          and (Hero.Word668 = 0)
          and not MainForm.RichEdit1.Visible
          and (MainForm.RichEdit1.Text = '')
          and not MainForm.Button11.Visible
          and not MainForm.Button34.Visible
          and not MainForm.Button35.Visible,
      'wisdom-close-clears-continuation-and-clue-controls'
  );
  Room(1);
  Hero.hero_orb := 1;
  Hero.Word48 := 0;
  Maps[1, 2] := 61;
  Maps[1, 3] := 62;
  for T := 1 to 8 do
    Maps[1, T + 3] := 61 + T * 2;
  MainForm.img6work;
  Require(
      (OrbRow = 8)
          and (OrbEnemies[1] = 0)
          and (OrbEnemies[2] = 1)
          and (OrbEnemies[7] = 6)
          and MainForm.Panel1.Visible
          and MainForm.Image24.Visible
          and MainForm.Image30.Visible
          and not MainForm.Timer1.Enabled
          and (Hero.Word48 = 0),
      'hero-orb-keeps-seven-unique-rows-and-pauses-map-timer'
  );
  Require(
      (MainForm.Edit13.Text = MainForm.ListBox2.Items[94])
          and (MainForm.Edit25.Text = MainForm.ListBox2.Items[100])
          and (MainForm.RichEdit1.Text = MainForm.ListBox2.Items[180])
          and (MainForm.Image24.Picture.Bitmap.Width = MainForm.Image6.Width),
      'hero-orb-uses-original-row-controls-and-localized-heading'
  );
  MainForm.Button36Click(nil);
  Require(
      not MainForm.Panel1.Visible
          and not MainForm.Image24.Visible
          and not MainForm.Image30.Visible
          and not MainForm.Edit13.Visible
          and not MainForm.Edit33.Visible
          and (MainForm.Edit13.Text = '')
          and (MainForm.Edit33.Text = '')
          and MainForm.Timer1.Enabled,
      'hero-orb-close-clears-rows-and-resumes-map-timer'
  );
  Room(1);
  Hero.hero_orb := 1;
  MainForm.img6work;
  Require(
      (OrbRow = 1) and (MainForm.Edit13.Text = '') and not MainForm.Image24.Visible,
      'hero-orb-empty-floor-does-not-reuse-previous-rows'
  );
  MainForm.Button36Click(nil);
  Room(45);
  ScratchIndex := 17;
  TileClass := 112;
  NeighborY := 99;
  MainForm.madoushi1;
  Require(
      (TileClass = 0) and (NeighborY = 1) and (EventStack[6].A = 17),
      'pincer-preserves-caller-cell-and-completes-neighbor-state'
  );
  Drain;
  Room(47);
  Hero.sacred_shield := 1;
  TileClass := 111;
  NeighborY := 0;
  MainForm.mazyutu1;
  Require(
      (EventCursor = 0) and (TileClass = 0) and (NeighborY = 1) and MainForm.Timer2.Enabled,
      'shield-suppresses-magician-damage-but-preserves-completion-state'
  );
  MainForm.timer2timer(nil);
  Room(47);
  Hero.x := 5;
  Hero.y := 5;
  Hero.sacred_shield := 1;
  Damage := 2;
  NeighborIndex := 17;
  TileClass := 110;
  MainForm.mazyutu1;
  Require(
      (EventCursor = 4)
          and (EventStack[2].Opcode = Ord(evMoveMonster))
          and (EventStack[2].A = 61)
          and (EventStack[2].B = 62),
      'magician-retreat-uses-hero-and-offset-not-stale-neighbor'
  );
  Drain;
  Room(1);
  ScratchIndex := 17;
  NeighborIndex := 8;
  DoorOpened := 99;
  PushEvent(Ord(evReserved), 0, 0);
  MainForm.stackwork;
  Require(
      (EventCursor = 0) and (ScratchIndex = 17) and (NeighborIndex = 8) and (DoorOpened = 99),
      'reserved-opcode18-does-not-animate-hero'
  );
  for T := 1 to 3 do
  begin
    Room(1);
    case T of
      1: MainForm.speedhigh;
      2: MainForm.speedmiddle;
      3: MainForm.speedlow;
    end;
    MainForm.Timer1.Enabled := True;
    MainForm.kaidanwork;
    Require(
        (EventCursor = 244)
            and not MainForm.Timer1.Enabled
            and MainForm.Timer2.Enabled
            and (MainForm.Timer2.Interval = 4 * T - 2)
            and (MapBitmap1.Width = MainForm.Image6.Width * 11)
            and (MapBitmap2.Height = MainForm.Image6.Height * 11),
        'stairs-bitmap-and-timing-' + IntToStr(T)
    );
    Drain;
  end;
  Room(2);
  Hero.x := 2;
  MainForm.Button1.Caption := 'Continue';
  MainForm.touzoku;
  Require(
      (MainForm.Button1.Caption = 'OK')
          and (TileClass = 1)
          and (MessageText = MainForm.ListBox2.Items[137])
          and (InputEnabled = 0),
      'thief-door-restores-prompt-message-and-input-gate'
  );
  Room(43);
  Hero.highest_floor := 45;
  Hero.Word632 := 2;
  RepeatEnabled := 1;
  FacingRequest := 5;
  MainForm.Button8.Enabled := False;
  MainForm.Button9.Enabled := False;
  MainForm.timer3ontimer(nil);
  Require(
      (Hero.floor = 45)
          and (Hero.Word632 = 2)
          and (StrikeCount = 0)
          and not MainForm.Button8.Enabled
          and not MainForm.Button9.Enabled,
      'flight-repeat-up-preserves-landing-mode-and-button-gates'
  );
  FacingRequest := 6;
  MainForm.timer3ontimer(nil);
  Require(
      (Hero.floor = 43) and (Hero.Word632 = 2) and (StrikeCount = 1),
      'flight-repeat-down-skips-floor44'
  );
  RepeatEnabled := 0;
  MainForm.Timer3.Enabled := True;
  MainForm.timer3ontimer(nil);
  Require(not MainForm.Timer3.Enabled, 'flight-repeat-stops-when-released');
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
    if T = 34 then
      Require(
          MessageText = MainForm.ListBox2.Items[164] + ' 1 point up!',
          'single-point-gem-keeps-original-message'
      );
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
  MonsterIndex := 12;
  MonsterText := 'monster name';
  Damage := 123;
  StrikeCount := 456;
  RemainingHP := 789;
  MainForm.dameiji;
  Require(
      (DamageMode = 1)
          and (Damage = 123)
          and (StrikeCount = 456)
          and (RemainingHP = 789)
          and (MonsterText = 'monster name')
          and (DamageText = MainForm.ListBox2.Items[$B9]),
      'blocked-damage-preview-preserves-calculation-state'
  );
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
  Require(
      (MessageText = MainForm.ListBox2.Items[181] + ' 100' + MainForm.ListBox2.Items[166])
          and (TileClass = 1)
          and (EventPaused = 0),
      'altar-health-message-and-resume-state'
  );
  Drain;
  Require((Hero.gold = 80) and (Hero.hp = 1100) and (Hero.Word44 = 1), 'altar-hp-purchase');
  ContactIndex := 49;
  MainForm.handan;
  Require(GameplayShopCost = 40, 'altar-next-price');
  MainForm.Button7Click(nil);
  Room(11);
  Hero.gold := 100;
  GameplayShopCost := 20;
  Hero.cycle_factor_minus_one := 1;
  InitialAttack := Hero.attack;
  InitialDefense := Hero.defense;
  MainForm.Button40Click(nil);
  Require(
      (Hero.attack = InitialAttack + 8)
          and (MessageText = MainForm.ListBox2.Items[182] + ' 8' + MainForm.ListBox2.Items[166]),
      'altar-attack-message-and-cycle-scaling'
  );
  Drain;
  MainForm.Button41Click(nil);
  Require(
      (Hero.defense = InitialDefense + 16)
          and (MessageText = MainForm.ListBox2.Items[183] + ' 16' + MainForm.ListBox2.Items[166]),
      'altar-defense-message-and-cycle-scaling'
  );
  Drain;
  Hero.gold := 19;
  InitialHP := Hero.hp;
  MainForm.Button39Click(nil);
  Require(
      (Hero.gold = 19)
          and (Hero.hp = InitialHP)
          and (Hero.Word44 = 2)
          and (EventCursor = 0)
          and (DialogueStage = 0)
          and MainForm.Button1.Visible
          and MainForm.RichEdit1.Visible
          and (MainForm.RichEdit1.Text = MainForm.ListBox2.Items[211])
          and (MainForm.Button1.Top
              = MainForm.RichEdit1.Top + MainForm.RichEdit1.Height - MainForm.Button1.Height - 16),
      'altar-insufficient-gold-keeps-state-and-places-dismiss-inside-dialogue'
  );
  MainForm.Button1Click(nil);
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
  Require(Hero.music_track = 0, 'ascent-wing-preserves-music-off');
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
  Require(
      MessageText = MainForm.ListBox2.Items[186] + ' 350' + MainForm.ListBox2.Items[166],
      'elixir-original-message-spacing'
  );
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
  Hero.bomb := 1;
  Maps[1, 51] := 61;
  Maps[1, 63] := 63;
  InitialGold := Hero.gold;
  MainForm.img10work;
  MainForm.Button38Click(nil);
  Require(
      (Hero.gold = InitialGold + Monsters[0].Gold + Monsters[1].Gold)
          and (MessageText
              = MainForm.ListBox2.Items[188]
                  + MainForm.ListBox2.Items[200]
                  + ' '
                  + IntToStr(Monsters[0].Gold + Monsters[1].Gold)
                  + MainForm.ListBox2.Items[201]),
      'bomb-original-gold-total-and-message'
  );
  Drain;
  Require((Maps[1, 51] = 6) and (Maps[1, 63] = 6), 'bomb-removes-both-neighbors');
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

procedure OriginalBattleChecks;
const
  BodyOffsets: array[0..8] of Integer = (-21, -22, -23, -12, -11, -10, -1, 0, 1);
var
  SavedMonster: TMonsterStats;
  I: Integer;
begin
  Room(35);
  SavedMonster := Monsters[18];
  try
    Monsters[18].HP := 30;
    Monsters[18].Attack := 25;
    Monsters[18].Defense := 10;
    Monsters[18].Gold := 123;
    Hero.attack := 20;
    Hero.defense := 30;
    Hero.lucky_gold := 1;
    Maps[35, 51] := 97;
    ContactIndex := 49;
    MainForm.taisen;
    Require(
        (EventStack[2].Opcode = Ord(evAwardGold))
            and (EventStack[2].A = 61)
            and (Hero.Word48 = 0)
            and (MessageText
                = MainForm.ListBox2.Items[240]
                    + ' '
                    + MonsterText
                    + '. '
                    + MainForm.ListBox2.Items[200]
                    + ' 123'
                    + MainForm.ListBox2.Items[201]),
        'octopus-body-keeps-original-halved-reward-and-message'
    );
    Room(35);
    Monsters[18].HP := 30;
    Monsters[18].Attack := 25;
    Monsters[18].Defense := 10;
    Hero.attack := 20;
    Hero.defense := 30;
    for I := 0 to 8 do
      Maps[35, 49 + BodyOffsets[I] + 2] := 97;
    Maps[35, 51] := 104;
    MoveUp;
    for I := 0 to 8 do
      Require(Maps[35, 49 + BodyOffsets[I] + 2] = 6, 'octopus-mouth-clears-body-' + IntToStr(I));
  finally
    Monsters[18] := SavedMonster;
  end;
  Room(1);
end;

procedure CounterattackChecks;
var
  SavedMonster: TMonsterStats;
  I: Integer;
begin
  Room(1);
  SavedMonster := Monsters[26];
  try
    Monsters[26].HP := 30;
    Monsters[26].Attack := 25;
    Monsters[26].Defense := 10;
    Monsters[26].Gold := 123;
    Hero.attack := 20;
    Hero.defense := 10;
    Hero.lucky_gold := 1;
    Maps[1, 51] := 145;
    ContactIndex := 60;
    EventStack[1].B := 49;
    MainForm.taisen2;
    Require(
        (ContactIndex = 49)
            and (MonsterIndex = 26)
            and (BattleHP = 30)
            and (Hero.x = 5)
            and (Hero.y = 5)
            and (Hero.Word48 = 0)
            and (Damage = 45)
            and (StrikeCount = 3)
            and (EventCursor = 42),
        'counterattack-reads-queued-target-and-prepares-original-turns'
    );
    Require(
        MessageText
            = MainForm.ListBox2.Items[199]
                + ' '
                + MonsterText
                + '. '
                + MainForm.ListBox2.Items[200]
                + ' 123'
                + MainForm.ListBox2.Items[201],
        'counterattack-message-keeps-unmultiplied-gold'
    );
    Room(1);
    Hero.hp := 10;
    Hero.attack := 20;
    Hero.defense := 10;
    Maps[1, 51] := 145;
    EventStack[1].B := 49;
    MainForm.taisen2;
    Require(
        (Hero.Word48 = 1)
            and (StrikeCount = 1)
            and (Damage = 0)
            and (EventCursor = 26)
            and (EventStack[2].Opcode = Ord(evDefeat)),
        'counterattack-fatal-first-strike-keeps-original-delays'
    );
    Room(1);
    Monsters[26].HP := 1000;
    Hero.attack := 11;
    Hero.defense := 30;
    Maps[1, 51] := 145;
    EventStack[1].B := 49;
    MainForm.taisen2;
    Require(
        (ContactIndex = 49) and (BattleHP = 1000) and (EventCursor = 12006),
        'counterattack-builds-complete-thousand-hit-queue'
    );
    for I := 1 to 3 do
      MainForm.timer2timer(nil);
    Require(
        (Hero.hp = 1000) and (BattleHP = 1000) and (EventCursor = 12000),
        'counterattack-consumes-enemy-first-records'
    );
  finally
    Monsters[26] := SavedMonster;
    EventCursor := 0;
    MainForm.Timer2.Enabled := False;
  end;
  Room(1);
end;
