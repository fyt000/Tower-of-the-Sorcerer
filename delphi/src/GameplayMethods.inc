{ Movement, combat, shops and item interaction. Address comments identify
  the corresponding executable handlers. }
var
  GameplayItemChoice, GameplayInventoryCursor: Longint;
  GameplayWalkingFrom, GameplayWalkingStep, GameplayWalkingTotal: Longint;
  GameplayOrbEnemies: array[0..32] of Longint;
  GameplayOrbCount: Longint;
  GameplayFight: record
    Active, Fatal, EnemyFirst: Boolean;
    Target, Tile, Underlying, BaseCursor, Total, Turn: Longint;
  end;

procedure GameplayRefresh(Form: TTSW10);
begin
  if (MapBitmap1 = nil) or (MapBitmap2 = nil) then
    Exit;
  Form.mhyouji;
  Form.yusyahyouji1;
  Form.Canvas.Draw(UiSpan, UiStep, MapBitmap1);
end;

function GameplayText(Form: TTSW10; Index: Longint): string;
begin
  if (Index >= 0) and (Index < Form.ListBox2.Items.Count) then
    GameplayText := Form.ListBox2.Items[Index]
  else
    GameplayText := '';
end;

procedure GameplayMessage(Form: TTSW10; Index: Longint);
begin
  TileClass := Index;
  Form.disp;
end;

procedure GameplayDialogue(Form: TTSW10; Index, Stage: Longint);
begin
  Form.itemdel;
  DialogueStage := Stage;
  Form.RichEdit1.Text := GameplayText(Form, Index);
  Form.RichEdit1.Left := UiSpan + 8;
  Form.RichEdit1.Top := UiStep + 8;
  Form.RichEdit1.Width := Form.Image6.Width * 11 - 16;
  Form.RichEdit1.Height := Form.Image6.Height * 6;
  Form.RichEdit1.Visible := True;
  Form.Button1.Left := Form.RichEdit1.Left + Form.RichEdit1.Width - Form.Button1.Width;
  Form.Button1.Top := Form.RichEdit1.Top + Form.RichEdit1.Height + 4;
  Form.Button1.Visible := True;
  Form.Button1.Enabled := True;
  if Form.Visible then
    Form.Button1.SetFocus;
end;

procedure GameplayPose(Cell: Longint);
var
  Color: Longint;
begin
  { Damage poses occupy four atlas groups, eight frames apart. }
  Color := 191 + (Hero.facing - 1) * 8;
  PushEvent(0, 6, Color);
  PushEvent(9, Cell, Color + 1);
end;

procedure CancelBattle;
begin
  GameplayFight.Active := False;
  GameplayFight.Turn := 0;
  GameplayEnemyFirst := False;
end;

function BattleNeedsRefill: Boolean;
begin
  { A streamed turn may refill only after its previous records are consumed. }
  BattleNeedsRefill := GameplayFight.Active and (EventCursor = GameplayFight.BaseCursor);
end;

procedure GameplayStrike(
    Target, Tile, Underlying, Turn, Total: Longint;
    Fatal, EnemyFirst: Boolean
);
var
  EnemyTurn, FinalHero: Boolean;
  Operand: Longint;
begin
  EnemyTurn := (Turn mod 2 = 0) = EnemyFirst;
  FinalHero := (Turn = Total - 1) and not Fatal and not EnemyFirst;
  Operand := 0;
  if EnemyTurn and Fatal then
  begin
    if Turn = Total - 1 then
      Operand := Underlying
    else if EnemyFirst then
      Operand := 250
    else
      Operand := 184;
  end
  else if not EnemyTurn then
  begin
    if EnemyFirst and not Fatal then
      Operand := 193
    else if not FinalHero and not Fatal then
      Operand := 183;
  end;
  PushEvent(0, 0, 0);
  if EnemyTurn then
    PushEvent(4, Target, Operand)
  else
    PushEvent(5, Target, Operand);
  if EnemyTurn then
    GameplayPose(Target)
  else
  begin
    PushEvent(0, Underlying, 184);
    if FinalHero and ((Tile = 104) or (Tile = 122)) then
      PushEvent(14, Target, 183)
    else
      PushEvent(9, Target, 183);
  end;
  PushEvent(0, 0, 0);
  PushEvent(1, 3, 0);
end;

procedure QueueNextBattleTurn(Form: TTSW10);
begin
  if not BattleNeedsRefill then
    Exit;
  if GameplayFight.Turn >= GameplayFight.Total then
  begin
    GameplayFight.Active := False;
    Exit;
  end;
  GameplayStrike(
      GameplayFight.Target,
      GameplayFight.Tile,
      GameplayFight.Underlying,
      GameplayFight.Turn,
      GameplayFight.Total,
      GameplayFight.Fatal,
      GameplayFight.EnemyFirst
  );
  Inc(GameplayFight.Turn);
end;

procedure TTSW10.obudameiji; { $0044FF0C; Orb deliberately ignores Cross/Slayer }
begin
  Damage := ForecastDamage(MonsterIndex, False, True, StrikeCount);
  if not AttackPenetrates(MonsterIndex) then
  begin
    DamageMode := 1;
    MonsterText := GameplayText(Self, $B9);
  end
  else
  begin
    DamageMode := 0;
    MonsterText := GameplayText(Self, $B8) + ' ' + IntToStr(Damage);
  end;
end;

procedure TTSW10.dameiji; { $00450064 }
begin
  Damage := ForecastDamage(MonsterIndex, False, False, StrikeCount);
  DamageMode := Ord(not AttackPenetrates(MonsterIndex));
  if DamageMode <> 0 then
    MonsterText := GameplayText(Self, $B9)
  else
    MonsterText := GameplayText(Self, $B8) + ' ' + IntToStr(Damage);
end;

procedure GameplayBattle(Form: TTSW10; EnemyFirst: Boolean);
{ The octopus and dragon occupy a 3-by-3 body above their attackable cell. }
const
  BodyOffsets: array[0..8] of Longint = (-21, -22, -23, -12, -11, -10, -1, 0, 1);
var
  T,
  Enemy,
  Hits,
  Expected,
  EnemyHit,
  HeroTurns,
  EnemyTurns,
  Turn,
  Cell,
  Reward,
  I,
  Underlying,
  Total: Longint;
  Fatal: Boolean;
begin
  if (ContactIndex < 0) or (ContactIndex > 120) then
    Exit;
  T := Maps[Hero.floor, ContactIndex + 2];
  Enemy := MonsterForTile(T);
  if Enemy < 0 then
    Exit;
  MonsterIndex := Enemy;
  GameplayEnemyFirst := EnemyFirst;
  Expected := ForecastDamage(Enemy, EnemyFirst, False, Hits);
  Form.monshyouji;
  if not AttackPenetrates(Enemy) then
  begin
    GameplayMessage(Form, 113);
    Exit;
  end;
  if not EnemyFirst then
    Form.idou;
  MonsterIndex := Enemy;
  BattleHP := Monsters[Enemy].HP * (Hero.cycle_factor_minus_one + 1);
  Hero.Word48 := 1;
  Cell := Hero.y * 11 + Hero.x;
  Underlying := Maps[Hero.floor, Cell + 2];
  Fatal := Expected >= Hero.hp;
  EnemyHit := Monsters[Enemy].Attack * (Hero.cycle_factor_minus_one + 1) - Hero.defense;
  if EnemyHit < 0 then
    EnemyHit := 0;
  if Fatal and (EnemyHit > 0) then
  begin
    { Round up the lethal enemy strikes; stop before another hero turn. }
    EnemyTurns := Hero.hp div EnemyHit;
    if Hero.hp mod EnemyHit <> 0 then
      Inc(EnemyTurns);
    HeroTurns := EnemyTurns;
    if EnemyFirst then
      Dec(HeroTurns);
  end
  else
  begin
    HeroTurns := Hits;
    EnemyTurns := Hits;
    if not EnemyFirst then
      Dec(EnemyTurns);
  end;
  if Fatal then
  begin
    if EnemyFirst then
      PushEvent(0, 0, 0);
    PushEvent(3, 0, 0);
    for I := 1 to 6 do
      PushEvent(0, 0, 0);
    if EnemyFirst then
      for I := 1 to 12 do
        PushEvent(0, 0, 0);
  end
  else
  begin
    Reward := Monsters[Enemy].Gold;
    { Octopus body pieces yield half the mouth's reward. }
    if (Enemy = 18) and (T <> 104) then
      Reward := Reward div 2;
    PushEvent(11, 5, 5);
    PushEvent(7, Reward, 0);
    MessageText :=
        GameplayText(Form, 199)
            + ' '
            + GameplayText(Form, Enemy + 94)
            + ' '
            + GameplayText(Form, 200)
            + ' '
            + IntToStr(Reward * (Hero.lucky_gold + 1))
            + ' '
            + GameplayText(Form, 201);
    PushEvent(2, 1, 0);
    if not EnemyFirst and (((Enemy = 18) and (T = 104)) or ((Enemy = 19) and (T = 122))) then
    begin
      for I := 0 to 8 do
        if (Cell + BodyOffsets[I] >= 0) and (Cell + BodyOffsets[I] <= 120) then
          PushEvent(17, Cell + BodyOffsets[I], 6);
    end
    else
      PushEvent(17, Cell, 6);
    PushEvent(0, 0, 0);
    PushEvent(11, 9, 0);
  end;
  Total := HeroTurns + EnemyTurns;
  GameplayFight.Active := False;
  if Total <= (High(EventStack) - EventCursor) div 6 then
  begin
    { Each strike occupies six records. Append the last turn first for LIFO. }
    for Turn := Total - 1 downto 0 do
      GameplayStrike(ContactIndex, T, Underlying, Turn, Total, Fatal, EnemyFirst);
  end
  else
  begin
    { Refill one turn at a time when the complete fight exceeds stack capacity. }
    GameplayFight.Active := True;
    GameplayFight.Fatal := Fatal;
    GameplayFight.EnemyFirst := EnemyFirst;
    GameplayFight.Target := ContactIndex;
    GameplayFight.Tile := T;
    GameplayFight.Underlying := Underlying;
    GameplayFight.BaseCursor := EventCursor;
    GameplayFight.Total := Total;
    GameplayFight.Turn := 0;
    QueueNextBattleTurn(Form);
  end;
  Form.timer2on;
end;

procedure TTSW10.taisen;
begin
  GameplayBattle(Self, False);
end;
procedure TTSW10.taisen2;
begin
  GameplayBattle(Self, True);
end;

procedure TTSW10.madoushi1; { $0044C464, pincer loses half current HP }
begin
  PushEvent(0, 0, 0);
  PushEvent(19, 0, 0);
  PushEvent(0, 0, 0);
  PushEvent(2, 112, 0);
  GameplayPose(Hero.y * 11 + Hero.x);
  PushEvent(0, 0, 0);
  PushEvent(1, 1, 0);
  timer2on;
end;

procedure TTSW10.syounin; { $00449014 }
const
  Floors: array[0..11] of Longint = (2, 6, 7, 12, 12, 15, 28, 31, 38, 39, 45, 47);
  Costs: array[0..11] of Longint = (0, 50, 50, 800, 1000, 200, 0, 1000, 200, 2000, 1000, 4000);
  Hints: array[0..11] of Longint = (29, 2, 3, 4, -1, 5, -1, 11, 15, 17, 20, 22);
var
  I, Hint, Offset, Speech: Longint;
begin
  GameplayShopID := -1;
  for I := 0 to 11 do
    if (Floors[I] = Hero.floor) and ((Hero.floor <> 12) or ((Hero.x = 9) = (I = 4))) then
    begin
      GameplayShopID := I;
      Break;
    end;
  if GameplayShopID < 0 then
    Exit;
  Hint := Hints[GameplayShopID];
  { Completed one-time trades turn their merchant into a source of clues. }
  if (ReadHeroField(168 + GameplayShopID * 4) <> 0) and (Hint >= 0) then
  begin
    if Hint = 29 then
      Offset := 216
    else
      Offset := ClueFieldOffset(Hint);
    if ReadHeroField(Offset) = 0 then
    begin
      if Hero.wisdom_orb = 1 then
        WriteHeroField(Offset, 2)
      else
        WriteHeroField(Offset, 1);
      if Hint = 29 then
        Speech := 91
      else
        Speech := 62 + Hint;
    end
    else if Hint = 29 then
      Speech := 91
    else
      Speech := 90;
    GameplayDialogue(Self, Speech, 0);
    Exit;
  end;
  GameplayShopKind := 2;
  GameplayShopCost := Costs[GameplayShopID];
  GameplayDialogue(Self, 246 + GameplayShopID, 0);
  Button1.Visible := False;
  Button2.Left := RichEdit1.Left;
  Button2.Top := RichEdit1.Top + RichEdit1.Height + 4;
  Button2.Visible := True;
  Button2.Enabled := True;
  Button7.Left := Button2.Left + Button2.Width + 8;
  Button7.Top := Button2.Top;
  Button7.Visible := True;
  Button7.Enabled := True;
  if Visible then
    Button2.SetFocus;
end;

procedure TTSW10.roujin; { $00449708 }
var
  Hint, Speech, Special, Offset: Longint;
begin
  Hint := -1;
  Speech := 90;
  Special := -1;
  case Hero.floor of
    2:
    begin
      Speech := 87;
      Special := 0;
      if Hero.Word392 = 0 then
      begin
        Hero.Word392 := 1;
        Inc(Hero.attack, Hero.attack * 3 div 100);
        Inc(Hero.defense, Hero.defense * 3 div 100);
        PushEvent(0, 0, 0);
        PushEvent(2, 0, 0);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
      end;
    end;
    3:
    begin
      Speech := 88;
      Special := 1;
    end;
    4: Hint := 0;
    6: Hint := 1;
    16:
      if Hero.x = 9 then
      begin
        Speech := 89;
        Special := 2;
        if Hero.Word436 = 0 then
        begin
          Hero.Word436 := 1;
          Hero.elixir := 1;
          PushEvent(0, 0, 0);
          PushEvent(8, 0, 0);
          PushEvent(0, 0, 0);
          PushEvent(1, 2, 0);
        end;
      end
      else
        Hint := 6;
    18: Hint := 7;
    21: Hint := 8;
    23: Speech := 61;
    27: Hint := 9;
    31: Hint := 10;
    33: Hint := 12;
    36: Hint := 13;
    37: Hint := 14;
    39: Hint := 16;
    42: Hint := 18;
    45: Hint := 19;
    46: Hint := 21;
    48: Hint := 23;
  end;
  if Hint >= 0 then
  begin
    Offset := ClueFieldOffset(Hint);
    if ReadHeroField(Offset) <> 0 then
      Speech := 86
    else
    begin
      if Hero.wisdom_orb = 1 then
        WriteHeroField(Offset, 2)
      else
        WriteHeroField(Offset, 1);
      Speech := 62 + Hint;
    end;
  end;
  if Special >= 0 then
  begin
    { The three gift conversations have separate first-hearing flags. }
    if Special = 0 then
      Offset := 264
    else if Special = 1 then
      Offset := 268
    else
      Offset := 284;
    if ReadHeroField(Offset) <> 0 then
      Speech := 86
    else
    begin
      if Hero.wisdom_orb = 1 then
        WriteHeroField(Offset, 2)
      else
        WriteHeroField(Offset, 1);
      if Hero.floor = 3 then
      begin
        Hero.hero_orb := 2;
        PushEvent(0, 0, 0);
        PushEvent(8, 0, 0);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(2, 11, 0);
      end;
    end;
  end;
  GameplayDialogue(Self, Speech, 0);
end;

procedure TTSW10.Button1Click(Sender: TObject); { $0044DA10 }
var
  Stage: Longint;
begin
  Stage := DialogueStage;
  EventPaused := False;
  { Stages 11..67 persist as flags after the 320-byte state prefix. }
  if (Stage > 10) and (Stage < 68) then
    WriteHeroField(320 + Stage * 4, 1);
  Button1.Visible := False;
  RichEdit1.Visible := False;
  RichEdit1.Clear;
  case Stage of
    0:
      if Hero.hero_orb = 2 then
        Hero.hero_orb := 1;
    1:
    begin
      Button35.Visible := True;
      Exit;
    end;
    2..10, 22:;
    13:
    begin
      Hero.Word48 := 0;
      EventCursor := 0;
      Timer2.Enabled := False;
      GameplayRefresh(Self);
    end;
    14:
    begin
      PushEvent(0, 0, 0);
      PushEvent(12, 66, 77);
      PushEvent(0, 0, 0);
      PushEvent(12, 67, 66);
      PushEvent(0, 0, 0);
      PushEvent(12, 68, 67);
    end;
    15:
    begin
      PushEvent(0, 0, 0);
      PushEvent(6, 99, 6);
      PushEvent(0, 0, 0);
      PushEvent(1, 2, 0);
      PushEvent(0, 0, 0);
      PushEvent(12, 88, 99);
      PushEvent(0, 0, 0);
      PushEvent(12, 77, 88);
    end;
    16:
    begin
      Maps[35, 105] := 21;
      Maps[35, 93] := 6;
      GameplayRefresh(Self);
    end;
    20:
    begin
      openning2;
      Exit;
    end;
    26, 32, 34, 50, 57:
    begin
      TileClass := 0;
      if (Hero.cycle_factor_minus_one = 0) and (RankingForm <> nil) then
        RankingForm.ShowModal;
    end;
  end;
  DialogueStage := 0;
  if EventCursor > 0 then
    timer2on
  else
    itemlive;
  if not Timer2.Enabled then
    Timer1.Enabled := True;
end;

procedure TTSW10.Button2Click(Sender: TObject); { $0044E1CC }
begin
  Button2.Visible := False;
  Button7.Visible := False;
  if GameplayShopKind = 1 then
  begin
    Button39.Caption := GameplayText(Self, 204);
    Button40.Caption := GameplayText(Self, 205);
    Button41.Caption := GameplayText(Self, 206);
    Button42.Caption := GameplayText(Self, 207);
    Button39.Left := RichEdit1.Left;
    Button39.Top := RichEdit1.Top + RichEdit1.Height + 4;
    Button40.Left := Button39.Left;
    Button40.Top := Button39.Top + Button39.Height + 4;
    Button41.Left := Button39.Left + Button39.Width + 8;
    Button41.Top := Button39.Top;
    Button42.Left := Button41.Left;
    Button42.Top := Button40.Top;
    Button39.Visible := True;
    Button40.Visible := True;
    Button41.Visible := True;
    Button42.Visible := True;
    if Visible then
      Button39.SetFocus;
    Exit;
  end;
  if (GameplayShopID = 6) and (Hero.yellow_keys = 0) then
  begin
    GameplayDialogue(Self, 262, 0);
    Exit;
  end;
  if Hero.gold < GameplayShopCost then
  begin
    GameplayDialogue(Self, 258, 0);
    Exit;
  end;
  Dec(Hero.gold, GameplayShopCost);
  case GameplayShopID of
    0: Inc(Hero.gold, 1000);
    1, 5: Inc(Hero.blue_keys);
    2: Inc(Hero.yellow_keys, 5);
    3: Inc(Hero.red_keys);
    4: Inc(Hero.yellow_keys);
    6:
    begin
      Dec(Hero.yellow_keys);
      Inc(Hero.gold, 100);
    end;
    7:
    begin
      Inc(Hero.yellow_keys, 4);
      Inc(Hero.blue_keys);
    end;
    8: Inc(Hero.yellow_keys, 3);
    9: Inc(Hero.blue_keys, 3);
    10: Inc(Hero.hp, 2000);
    11: Hero.super_mattock := 1;
  end;
  if (GameplayShopID <> 4) and (GameplayShopID <> 6) then
    WriteHeroField(168 + GameplayShopID * 4, 1);
  GameplayShopKind := 0;
  PushEvent(2, 0, 0);
  PushEvent(8, 0, 0);
  PushEvent(0, 0, 0);
  PushEvent(1, 2, 0);
  GameplayDialogue(Self, 259, 0);
end;

procedure TTSW10.Button7Click(Sender: TObject);
begin
  GameplayShopKind := 0;
  Button2.Visible := False;
  Button7.Visible := False;
  RichEdit1.Visible := False;
  RichEdit1.Clear;
  DialogueStage := 0;
  itemlive;
end;

procedure GameplayAltar(Form: TTSW10; Choice: Longint);
var
  Scale, Area, Amount: Longint;
begin
  Form.Button39.Visible := False;
  Form.Button40.Visible := False;
  Form.Button41.Visible := False;
  Form.Button42.Visible := False;
  Form.RichEdit1.Visible := False;
  if Hero.gold < GameplayShopCost then
  begin
    GameplayDialogue(Form, 211, 0);
    Exit;
  end;
  Scale := Hero.cycle_factor_minus_one + 1;
  Area := (Hero.floor + 10) div 10;
  case Choice of
    0:
    begin
      Amount := 100 * (Hero.Word44 + 1) * Scale;
      Inc(Hero.hp, Amount);
    end;
    1:
    begin
      Amount := 2 * Area * Scale;
      Inc(Hero.attack, Amount);
    end;
    2:
    begin
      Amount := 4 * Area * Scale;
      Inc(Hero.defense, Amount);
    end;
  end;
  Inc(Hero.Word44);
  Dec(Hero.gold, GameplayShopCost);
  GameplayShopKind := 0;
  MessageText :=
      GameplayText(Form, 180 + Choice) + ' ' + IntToStr(Amount) + ' ' + GameplayText(Form, 166);
  PushEvent(0, 0, 0);
  PushEvent(2, 1, 0);
  PushEvent(0, 0, 0);
  PushEvent(1, 2, 0);
  Form.timer2on;
end;

procedure TTSW10.Button39Click(Sender: TObject);
begin
  GameplayAltar(Self, 0);
end;
procedure TTSW10.Button40Click(Sender: TObject);
begin
  GameplayAltar(Self, 1);
end;
procedure TTSW10.Button41Click(Sender: TObject);
begin
  GameplayAltar(Self, 2);
end;
procedure TTSW10.Button42Click(Sender: TObject);
begin
  Button39.Visible := False;
  Button40.Visible := False;
  Button41.Visible := False;
  Button42.Visible := False;
  RichEdit1.Visible := False;
  GameplayShopKind := 0;
  itemlive;
end;

procedure TTSW10.zyouout; { $00449E18; wisdom and queued story dialogue }
var
  Stage, Speech: Longint;
begin
  if DialogueStage = 9 then
  begin
    EventPaused := False;
    PushEvent(0, 0, 0);
    PushEvent(22, 0, 0);
    PushEvent(0, 0, 0);
    PushEvent(10, 93, 0);
    timer2on;
    Exit;
  end;
  Stage := DialogueStage;
  if Stage >= 10 then
  begin
    { Queued speech IDs are one-based; continuation stages add ten. }
    Speech := Stage - 10;
    GameplayDialogue(Self, Speech - 1, Stage);
    if (Speech = 16) or (Speech = 22) or (Speech = 24) or (Speech = 40) or (Speech = 47) then
      RichEdit1.Text :=
          GameplayText(Self, Speech - 1)
              + #13#10#13#10
              + 'Score: '
              + IntToStr(Hero.Word340)
              + #13#10
              + 'Rank: '
              + IntToStr(Hero.Word344);
    if Speech = 5 then
      RichEdit1.Text := RichEdit1.Text + GameplayText(Self, Speech + 52)
    else if Speech = 17 then
      RichEdit1.Text := RichEdit1.Text + GameplayText(Self, Speech + 41)
    else if Speech = 55 then
      RichEdit1.Text := RichEdit1.Text + GameplayText(Self, Speech + 4);
    Exit;
  end;
  if (GameplayHintIndex >= 0) and (GameplayHintIndex <= 23) then
  begin
    GameplayDialogue(Self, 62 + GameplayHintIndex, 1);
    Hero.Word668 := 1;
  end;
end;

procedure TTSW10.img5work; { $0048198C }
var
  I: Longint;
  Buttons: array[0..23] of TButton;
begin
  if Hero.wisdom_orb <> 1 then
    Exit;
  Buttons[0] := Button11;
  Buttons[1] := Button12;
  Buttons[2] := Button13;
  Buttons[3] := Button14;
  Buttons[4] := Button15;
  Buttons[5] := Button16;
  Buttons[6] := Button17;
  Buttons[7] := Button18;
  Buttons[8] := Button19;
  Buttons[9] := Button20;
  Buttons[10] := Button21;
  Buttons[11] := Button22;
  Buttons[12] := Button23;
  Buttons[13] := Button24;
  Buttons[14] := Button25;
  Buttons[15] := Button26;
  Buttons[16] := Button27;
  Buttons[17] := Button28;
  Buttons[18] := Button29;
  Buttons[19] := Button30;
  Buttons[20] := Button31;
  Buttons[21] := Button32;
  Buttons[22] := Button33;
  Buttons[23] := Button34;
  itemdel;
  DialogueStage := 1;
  for I := 0 to 23 do
  begin
    Buttons[I].Left := UiSpan + 8 + (I mod 4) * (Image6.Width * 11 div 4);
    Buttons[I].Top := UiStep + 8 + (I div 4) * (Buttons[I].Height + 4);
    Buttons[I].Visible := True;
    Buttons[I].Enabled := ReadHeroField(ClueFieldOffset(I)) = 2;
  end;
  Button35.Left := UiSpan + Image6.Width * 11 - Button35.Width - 8;
  Button35.Top := UiStep + Image6.Height * 11 - Button35.Height - 8;
  Button35.Visible := True;
  Button35.Enabled := True;
  if Visible then
    Button35.SetFocus;
end;

procedure GameplayClue(Form: TTSW10; Index: Longint);
begin
  GameplayHintIndex := Index;
  Form.zyouout;
end;
procedure TTSW10.Button11Click(Sender: TObject);
begin
  GameplayClue(Self, 0);
end;
procedure TTSW10.Button12Click(Sender: TObject);
begin
  GameplayClue(Self, 1);
end;
procedure TTSW10.Button13Click(Sender: TObject);
begin
  GameplayClue(Self, 2);
end;
procedure TTSW10.Button14Click(Sender: TObject);
begin
  GameplayClue(Self, 3);
end;
procedure TTSW10.Button15Click(Sender: TObject);
begin
  GameplayClue(Self, 4);
end;
procedure TTSW10.Button16Click(Sender: TObject);
begin
  GameplayClue(Self, 5);
end;
procedure TTSW10.Button17Click(Sender: TObject);
begin
  GameplayClue(Self, 6);
end;
procedure TTSW10.Button18Click(Sender: TObject);
begin
  GameplayClue(Self, 7);
end;
procedure TTSW10.Button19Click(Sender: TObject);
begin
  GameplayClue(Self, 8);
end;
procedure TTSW10.Button20Click(Sender: TObject);
begin
  GameplayClue(Self, 9);
end;
procedure TTSW10.Button21Click(Sender: TObject);
begin
  GameplayClue(Self, 10);
end;
procedure TTSW10.Button22Click(Sender: TObject);
begin
  GameplayClue(Self, 11);
end;
procedure TTSW10.Button23Click(Sender: TObject);
begin
  GameplayClue(Self, 12);
end;
procedure TTSW10.Button24Click(Sender: TObject);
begin
  GameplayClue(Self, 13);
end;
procedure TTSW10.Button25Click(Sender: TObject);
begin
  GameplayClue(Self, 14);
end;
procedure TTSW10.Button26Click(Sender: TObject);
begin
  GameplayClue(Self, 15);
end;
procedure TTSW10.Button27Click(Sender: TObject);
begin
  GameplayClue(Self, 16);
end;
procedure TTSW10.Button28Click(Sender: TObject);
begin
  GameplayClue(Self, 17);
end;
procedure TTSW10.Button29Click(Sender: TObject);
begin
  GameplayClue(Self, 18);
end;
procedure TTSW10.Button30Click(Sender: TObject);
begin
  GameplayClue(Self, 19);
end;
procedure TTSW10.Button31Click(Sender: TObject);
begin
  GameplayClue(Self, 20);
end;
procedure TTSW10.Button32Click(Sender: TObject);
begin
  GameplayClue(Self, 21);
end;
procedure TTSW10.Button33Click(Sender: TObject);
begin
  GameplayClue(Self, 22);
end;
procedure TTSW10.Button34Click(Sender: TObject);
begin
  GameplayClue(Self, 23);
end;

procedure TTSW10.Button35Click(Sender: TObject);
var
  I: Longint;
  Control: TComponent;
begin
  for I := 11 to 35 do
  begin
    Control := FindComponent('Button' + IntToStr(I));
    if Control <> nil then
      TButton(Control).Visible := False;
  end;
  Button1.Visible := False;
  RichEdit1.Visible := False;
  RichEdit1.Clear;
  DialogueStage := 0;
  Hero.Word668 := 0;
  itemlive;
end;

procedure TTSW10.yousya; { $0044F26C, append a unique Orb row }
var
  I: Longint;
begin
  MonsterIndex := NeighborIndex;
  if (MonsterIndex < 0) or (MonsterIndex > 32) then
    Exit;
  for I := 0 to GameplayOrbCount - 1 do
    if GameplayOrbEnemies[I] = MonsterIndex then
      Exit;
  GameplayOrbEnemies[GameplayOrbCount] := MonsterIndex;
  Inc(GameplayOrbCount);
  obudameiji;
  RichEdit1.Lines.Add(GameplayText(Self, 94 + MonsterIndex));
  RichEdit1.Lines.Add(
      'HP '
          + IntToStr(Monsters[MonsterIndex].HP * (Hero.cycle_factor_minus_one + 1))
          + '   ATK '
          + IntToStr(Monsters[MonsterIndex].Attack * (Hero.cycle_factor_minus_one + 1))
          + '   DEF '
          + IntToStr(Monsters[MonsterIndex].Defense * (Hero.cycle_factor_minus_one + 1))
  );
  RichEdit1.Lines.Add(MonsterText);
  RichEdit1.Lines.Add('');
end;

procedure TTSW10.img6work; { $00480F60 }
var
  I, Enemy: Longint;
begin
  if Hero.hero_orb <> 1 then
    Exit;
  itemdel;
  Hero.Word48 := 1;
  GameplayOrbCount := 0;
  RichEdit1.Clear;
  RichEdit1.Left := UiSpan + 8;
  RichEdit1.Top := UiStep + 8;
  RichEdit1.Width := Image6.Width * 11 - 16;
  RichEdit1.Height := Image6.Height * 10 - 16;
  RichEdit1.Visible := True;
  for I := 0 to 120 do
  begin
    Enemy := MonsterForTile(Maps[Hero.floor, I + 2]);
    if Enemy >= 0 then
    begin
      NeighborIndex := Enemy;
      yousya;
    end;
  end;
  if GameplayOrbCount = 0 then
    RichEdit1.Text := GameplayText(Self, 93);
  RichEdit1.SelStart := 0;
  Button36.Left := UiSpan + Image6.Width * 11 - Button36.Width - 8;
  Button36.Top := UiStep + Image6.Height * 11 - Button36.Height - 4;
  Button36.Visible := True;
  Button36.Enabled := True;
  if Visible then
    Button36.SetFocus;
end;

procedure TTSW10.Button36Click(Sender: TObject);
begin
  Button36.Visible := False;
  RichEdit1.Visible := False;
  RichEdit1.Clear;
  Hero.Word48 := 0;
  GameplayRefresh(Self);
  itemlive;
  keydisplay;
  Timer1.Enabled := True;
end;

procedure TTSW10.mazyutu1; { $0044C5C4 }
var
  Offset, Target, Amount, Message: Longint;
begin
  Offset := Damage;
  Target := Hero.y * 11 + Hero.x + Offset;
  { On 47F, magician A retreats two cells from the hero when that cell is road.
    The y guard also applies to horizontal retreats. }
  if (TileClass = 110)
      and (Hero.floor = 47)
      and (Hero.y > 0)
      and (Hero.y < 10)
      and (Target >= 0)
      and (Target < 121)
      and (Maps[47, Target + 2] = 6) then
  begin
    PushEvent(0, 0, 0);
    PushEvent(12, NeighborIndex, Target);
    PushEvent(0, 0, 0);
    PushEvent(1, 2, 0);
  end;
  { Sacred Shield immunity suppresses damage, including backside scaling. }
  if Hero.sacred_shield = 0 then
  begin
    if TileClass = 110 then
      Amount := 200
    else
      Amount := 100;
    Message := TileClass;
    if Hero.cycle_factor_minus_one <> 0 then
      Inc(Message, 28);
    PushEvent(0, 0, 0);
    PushEvent(16, -Amount * (Hero.cycle_factor_minus_one + 1), 0);
    PushEvent(0, 0, 0);
    PushEvent(2, Message, 0);
    GameplayPose(Hero.y * 11 + Hero.x);
    PushEvent(0, 0, 0);
    PushEvent(1, 1, 0);
  end;
  if EventCursor > 0 then
    timer2on;
  TileClass := 0;
end;

procedure TTSW10.yusyaidou; { $00443808; walking frame }
var
  OldX, OldY, NewX, NewY, PixelX, PixelY, Frame: Longint;
begin
  if (MapBitmap1 = nil) or (GameplayWalkingTotal = 0) then
    Exit;
  OldX := GameplayWalkingFrom mod 11;
  OldY := GameplayWalkingFrom div 11;
  NewX := ContactIndex mod 11;
  NewY := ContactIndex div 11;
  PixelX :=
      Image6.Width * OldX
          + Image6.Width * (NewX - OldX) * GameplayWalkingStep div GameplayWalkingTotal;
  PixelY :=
      Image6.Height * OldY
          + Image6.Height * (NewY - OldY) * GameplayWalkingStep div GameplayWalkingTotal;
  Canvas.Draw(UiSpan, UiStep, MapBitmap1);
  { Facing selects an eight-frame atlas group; the walk changes every four steps. }
  Frame := 184 + (Hero.facing - 1) * 8;
  if (GameplayWalkingStep div 4) mod 2 = 0 then
    Inc(Frame, 2);
  WorkBitmap1.Width := Image6.Width;
  WorkBitmap1.Height := Image6.Height;
  WorkBitmap2.Width := Image6.Width;
  WorkBitmap2.Height := Image6.Height;
  WorkBitmap3.Width := Image6.Width;
  WorkBitmap3.Height := Image6.Height;
  ImageList1.Draw(WorkBitmap1.Canvas, 0, 0, 5);
  ImageList1.Draw(WorkBitmap2.Canvas, 0, 0, Frame);
  ImageList3.Draw(WorkBitmap3.Canvas, 0, 0, Frame);
  TargetRect := Rect(0, 0, Image6.Width, Image6.Height);
  SourceRect := TargetRect;
  kasanegaki;
  Canvas.Draw(UiSpan + PixelX, UiStep + PixelY, WorkBitmap1);
end;
procedure TTSW10.yusyai1;
begin
  yusyaidou;
end;
procedure TTSW10.yusyai2;
begin
  yusyaidou;
end;
procedure TTSW10.yusyai3;
begin
  yusyaidou;
end;
procedure TTSW10.yusyai4;
begin
  yusyaidou;
end;

procedure TTSW10.idou; { $0044C04C }
const
  Offsets: array[0..3] of Longint = (-11, -1, 1, 11);
var
  I, Cell, Tile, SavedClass: Longint;
begin
  if (ContactIndex < 0) or (ContactIndex > 120) then
    Exit;
  GameplayWalkingFrom := Hero.y * 11 + Hero.x;
  GameplayWalkingTotal := Image6.Width;
  if High1.Checked then
    GameplayWalkingTotal := Image6.Width div 4
  else if Middle1.Checked then
    GameplayWalkingTotal := Image6.Width div 2;
  if GameplayWalkingTotal < 1 then
    GameplayWalkingTotal := 1;
  if MapBitmap1 <> nil then
  begin
    mhyouji;
    for I := 1 to GameplayWalkingTotal do
    begin
      GameplayWalkingStep := I;
      yusyaidou;
    end;
  end;
  Hero.x := ContactIndex mod 11;
  Hero.y := ContactIndex div 11;
  Cell := Hero.y * 11 + Hero.x;
  ScratchIndex := Cell;
  GameplayRefresh(Self);
  { Test each boundary before adding an offset, so east/west cannot wrap rows. }
  for I := 0 to 3 do
  begin
    NeighborIndex := Cell + Offsets[I];
    if ((I = 0) and (Hero.y = 0))
        or ((I = 1) and (Hero.x = 0))
        or ((I = 2) and (Hero.x = 10))
        or ((I = 3) and (Hero.y = 10)) then
      Continue;
    Tile := Maps[Hero.floor, NeighborIndex + 2];
    TileClass := 0;
    mmes;
    if (Tile = 151) or (Tile = 152) or (Tile = 153) or (Tile = 154) then
    begin
      Damage := Offsets[I] * 2;
      mazyutu1;
    end;
  end;
  if Hero.sacred_shield = 0 then
  begin
    if (Hero.x > 0)
        and (Hero.x < 10)
        and (Maps[Hero.floor, Cell + 1] = 93)
        and (Maps[Hero.floor, Cell + 3] = 93) then
      madoushi1;
    if (Hero.y > 0)
        and (Hero.y < 10)
        and (Maps[Hero.floor, Cell - 9] = 93)
        and (Maps[Hero.floor, Cell + 13] = 93) then
      madoushi1;
  end;
  if not Timer2.Enabled then
  begin
    TileClass := 0;
    for I := 0 to 3 do
    begin
      NeighborIndex := Cell + Offsets[I];
      if ((I = 0) and (Hero.y = 0))
          or ((I = 1) and (Hero.x = 0))
          or ((I = 2) and (Hero.x = 10))
          or ((I = 3) and (Hero.y = 10)) then
        Continue;
      mmes;
    end;
    disp;
  end;
  ScratchIndex := Cell;
end;

procedure TTSW10.kaidanwork; { $00442DC8; spiral stair transition }
var
  I: Longint;
begin
  soundcheck;
  for I := 121 downto 1 do
  begin
    if (Hero.music_track <> 0) and (I = 102) then
      PushEvent(15, 0, 0);
    PushEvent(21, 1, I);
  end;
  for I := 121 downto 1 do
    PushEvent(21, 0, I);
  PushEvent(0, 0, 0);
  PushEvent(1, 9, 0);
  GameplayRefresh(Self);
end;

procedure TTSW10.handan; { $00444490 }
const
  Gain: array[0..4] of Longint = (10, 20, 40, 50, 100);
var
  Tile, Scale, Area, KeyCount, Destination, Index, Reveal, OldFloor: Longint;
begin
  if (ContactIndex < 0) or (ContactIndex > 120) or (Hero.floor < 0) or (Hero.floor > 50) then
    Exit;
  Tile := Maps[Hero.floor, ContactIndex + 2];
  Scale := Hero.cycle_factor_minus_one + 1;
  Area := (Hero.floor + 9) div 10;
  case Tile of
    1..3:
    begin
      DoorOpened := 0;
      case Tile of
        1:
        begin
          KeyCount := Hero.yellow_keys;
          if KeyCount > 0 then
            Dec(Hero.yellow_keys);
        end;
        2:
        begin
          KeyCount := Hero.blue_keys;
          if KeyCount > 0 then
            Dec(Hero.blue_keys);
        end;
        3:
        begin
          KeyCount := Hero.red_keys;
          if KeyCount > 0 then
            Dec(Hero.red_keys);
        end;
      end;
      DoorOpened := Ord(KeyCount > 0);
      TileClass := Tile + 15;
      if DoorOpened = 1 then
        TileClass := Tile + 3;
      doorcheck;
      PushEvent(2, TileClass, 0);
      if DoorOpened = 1 then
      begin
        PushEvent(8, 0, 0);
        PushEvent(13, ContactIndex, Tile);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
      end;
      timer2on;
      Exit;
    end;
    6:
    begin
      idou;
      Exit;
    end;
    7:
    begin
      mevent;
      Exit;
    end;
    9:
    begin
      MessageText := GameplayText(Self, $89);
      PushEvent(0, 0, 0);
      PushEvent(2, 1, 0);
      PushEvent(0, 0, 0);
      PushEvent(13, ContactIndex, 7);
      doorstackin;
      PushEvent(0, 0, 0);
      PushEvent(1, 1, 0);
      timer2on;
      Exit;
    end;
    10:
    begin
      Reveal := -1;
      Index := ContactIndex;
      if (Hero.floor = 12) and (Index = 10) then
        Reveal := 19
      else if (Hero.floor = 16) and (Index = 120) then
        Reveal := 25
      else if (Hero.floor = 19) and (Index = 27) then
        Reveal := 39
      else if (Hero.floor = 41) and (Maps[41, 14] = 6) then
      begin
        Index := 20;
        Reveal := 151;
      end;
      if Reveal >= 0 then
      begin
        PushEvent(0, 0, 0);
        PushEvent(6, Index, Reveal);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(0, 0, 0);
        timer2on;
      end;
      Exit;
    end;
    11, 12:
    begin
      OldFloor := Hero.floor;
      { Stairs connect 43F directly to 45F; the flight orb uses the same gap. }
      if Tile = 11 then
      begin
        if Hero.floor = 43 then
          Destination := 45
        else
          Destination := Hero.floor + 1;
        if Destination > 50 then
          Exit;
        if (OldFloor = 20) and (Maps[20, 51] = 23) then
          Maps[20, 51] := 6;
        if (OldFloor = 25) and (Maps[25, 73] = 23) then
          Maps[25, 73] := 6;
        if (OldFloor = 40) and (Maps[40, 62] = 23) then
          Maps[40, 62] := 6;
      end
      else
      begin
        if Hero.floor = 45 then
          Destination := 43
        else
          Destination := Hero.floor - 1;
        if Destination < 0 then
          Exit;
        if (OldFloor = 25) and (Maps[25, 73] = 23) then
          Maps[25, 73] := 6;
        if (OldFloor = 49) and (Maps[49, 18] = 23) then
          Maps[49, 18] := 6;
      end;
      Hero.floor := Destination;
      if Hero.floor > Hero.highest_floor then
      begin
        Hero.highest_floor := Hero.floor;
        if (Hero.Word140 = 35) and (Maps[35, 93] + Maps[2, 122] = 27) then
          Maps[2, 122] := 6;
      end;
      if (Tile = 12) and (OldFloor = 29) and (Hero.floor = 28) and (Hero.highest_floor = 29) then
      begin
        Maps[29, 40] := 6;
        Maps[29, 29] := 6;
        Maps[29, 19] := 21;
      end;
      if Tile = 11 then
        Index := Maps[Hero.floor, 0]
      else
        Index := Maps[Hero.floor, 1];
      Hero.x := Index mod 11;
      Hero.y := Index div 11;
      if Tile = 11 then
        kaidanupcheck
      else
        kaidandowncheck;
      if (Tile = 11) and (Hero.floor = 32) and (Hero.floor32_arrival_seen = 0) then
      begin
        mevent;
        Hero.floor32_arrival_seen := 1;
      end;
      if (Tile = 11) and (Hero.floor = 42) and (Hero.Word524 = 0) then
      begin
        mevent;
        Hero.Word524 := 1;
      end;
      PushEvent(0, 0, 0);
      PushEvent(0, 0, 0);
      PushEvent(0, 0, 0);
      if Tile = 11 then
        PushEvent(2, 7, 0)
      else
        PushEvent(2, 8, 0);
      kaidanwork;
      timer2on;
      Exit;
    end;
    16:
    begin
      GameplayShopKind := 1;
      { With n altar purchases, the next price is 10 * (n*n + n + 2). }
      GameplayShopCost := 10 * (Hero.Word44 * Hero.Word44 + Hero.Word44 + 2);
      GameplayDialogue(Self, 202, 2);
      RichEdit1.Text :=
          RichEdit1.Text + ' ' + IntToStr(GameplayShopCost) + ' ' + GameplayText(Self, 203);
      Button1.Visible := False;
      Button2.Visible := True;
      Button7.Visible := True;
      Button2.Left := RichEdit1.Left;
      Button2.Top := RichEdit1.Top + RichEdit1.Height + 4;
      Button7.Left := Button2.Left + Button2.Width + 8;
      Button7.Top := Button2.Top;
      Exit;
    end;
    19, 20:
    begin
      syounin;
      Exit;
    end;
    21, 22:
    begin
      touzoku;
      Exit;
    end;
    23, 24:
    begin
      yousei;
      Exit;
    end;
    25, 26:
    begin
      roujin;
      Exit;
    end;
    27, 28:
    begin
      if Hero.music_track <> 0 then
      begin
        Hero.music_track := 13;
        soundplay;
      end;
      if Maps[25, 62] = 6 then
      begin
        Maps[24, 6] := 8;
        Maps[24, 8] := 8;
        Maps[24, 18] := 6;
        Maps[24, 29] := 6;
        Maps[24, 40] := 6;
        Maps[24, 7] := 7;
      end;
      Maps[50, 51] := 21;
      PushEvent(0, 0, 0);
      PushEvent(6, 60, 27);
      PushEvent(0, 0, 0);
      PushEvent(10, 26, 0);
      PushEvent(0, 0, 0);
      PushEvent(10, 25, 0);
      PushEvent(0, 0, 0);
      PushEvent(0, 0, 0);
      timer2on;
      Exit;
    end;
    29: Inc(Hero.yellow_keys);
    30: Inc(Hero.red_keys);
    31: Inc(Hero.blue_keys);
    32: Inc(Hero.hp, 50 * Area * Scale);
    33: Inc(Hero.hp, 200 * Area * Scale);
    34: Inc(Hero.attack, Area * Scale);
    35: Inc(Hero.defense, Area * Scale);
    37..50:
    begin
      { Inventory occupies four-byte fields beginning at byte 68. }
      if Tile = 43 then
        WriteHeroField(68 + (Tile - 36) * 4, 3)
      else
        WriteHeroField(68 + (Tile - 36) * 4, 1);
    end;
    51..60:
    begin
      Index := (Tile - 51) mod 5;
      if Tile < 56 then
      begin
        Inc(Hero.attack, Gain[Index] * Scale);
        Hero.sword := Index + 1;
      end
      else
      begin
        Inc(Hero.defense, Gain[Index] * Scale);
        Hero.shield := Index + 1;
      end;
      WriteHeroField(128 + (Tile - 51) * 4, 1);
    end;
    91, 92:
    begin
      if (Hero.floor = 50) and (Hero.cycle_factor_minus_one = 0) then
        QueueEnding(Self)
      else if (Hero.floor = 49) or (Hero.floor = 50) then
      begin
        if (Hero.floor = 50) and (Hero.later_cycle = 0) then
        begin
          Monsters[15].HP := 1000;
          Monsters[15].Attack := 625;
          Monsters[15].Defense := 125;
        end;
        taisen;
      end;
      Exit;
    end;
  else
    if MonsterForTile(Tile) >= 0 then
      taisen;
    Exit;
  end;
  MessageText := GameplayText(Self, $89);
  TileClass := 1;
  if (Tile >= 37) and (Tile <= 50) then
    if Tile = 37 then
      TileClass := 22
    else if Tile = 38 then
      TileClass := 21
    else
      TileClass := Tile + 1;
  PushEvent(2, TileClass, 0);
  PushEvent(8, 0, 0);
  PushEvent(0, 0, 0);
  PushEvent(1, 2, 0);
  Maps[Hero.floor, ContactIndex + 2] := 6;
  idou;
  timer2on;
end;

procedure GameplayConfirmItem(Form: TTSW10; Item: Longint);
begin
  if ReadHeroField(68 + (Item - 1) * 4) <= 0 then
    Exit;
  GameplayItemChoice := Item;
  Form.itemdel;
  TileClass := Item + 35;
  Form.disp;
  Form.Button37.Left := UiSpan + 8;
  Form.Button37.Top := UiStep + Form.Image6.Height * 10;
  Form.Button38.Left := Form.Button37.Left + Form.Button37.Width + 8;
  Form.Button38.Top := Form.Button37.Top;
  Form.Button37.Visible := True;
  Form.Button37.Enabled := True;
  Form.Button38.Visible := True;
  Form.Button38.Enabled := True;
  if Form.Visible then
    Form.Button37.SetFocus;
end;

procedure TTSW10.img8work;
begin
  GameplayConfirmItem(Self, 5);
end;
procedure TTSW10.img9work;
begin
  GameplayConfirmItem(Self, 6);
end;
procedure TTSW10.img10work;
begin
  GameplayConfirmItem(Self, 7);
end;
procedure TTSW10.img11work;
begin
  GameplayConfirmItem(Self, 8);
end;
procedure TTSW10.img12work;
begin
  GameplayConfirmItem(Self, 9);
end;
procedure TTSW10.img13work;
begin
  GameplayConfirmItem(Self, 10);
end;
procedure TTSW10.img15work;
begin
  GameplayConfirmItem(Self, 12);
end;
procedure TTSW10.img16work;
begin
  GameplayConfirmItem(Self, 13);
end;
procedure TTSW10.img17work;
begin
  GameplayConfirmItem(Self, 14);
end;

procedure TTSW10.Button38Click(Sender: TObject); { $00450BA0 }
const
  Offsets: array[0..3] of Longint = (11, 1, -1, -11);
  Motions: array[0..3] of Longint = (11, 10, 9, 12);
var
  Item, Position, Target, I, X, Y, Enemy, Tile, Destination, Found: Longint;
begin
  Item := GameplayItemChoice;
  Button37.Visible := False;
  Button38.Visible := False;
  if (Item < 5) or (Item > 14) or (ReadHeroField(68 + (Item - 1) * 4) <= 0) then
  begin
    itemlive;
    Exit;
  end;
  Position := Hero.y * 11 + Hero.x;
  case Item of
    5:
    begin
      ScratchIndex := Hero.attack * 10 + Hero.defense * 5;
      Inc(Hero.hp, ScratchIndex);
      Hero.elixir := 0;
      MessageText :=
          GameplayText(Self, 186) + ' ' + IntToStr(ScratchIndex) + ' ' + GameplayText(Self, 166);
      PushEvent(0, 0, 0);
      PushEvent(2, 1, 0);
      PushEvent(0, 0, 0);
      PushEvent(8, 0, 0);
      PushEvent(0, 0, 0);
      PushEvent(1, 2, 0);
    end;
    6, 7, 12:
    begin
      if Item = 6 then
      begin
        Hero.mattock := 0;
        PushEvent(2, 60, 0);
      end;
      if Item = 7 then
      begin
        Hero.bomb := 0;
        PushEvent(0, 0, 0);
        PushEvent(11, 5, 0);
        PushEvent(2, 0, 0);
      end;
      PushEvent(8, 0, 0);
      Found := 0;
      for I := 0 to 3 do
      begin
        if ((I = 0) and (Hero.y = 10))
            or ((I = 1) and (Hero.x = 10))
            or ((I = 2) and (Hero.x = 0))
            or ((I = 3) and (Hero.y = 0)) then
          Continue;
        Target := Position + Offsets[I];
        NeighborIndex := Target;
        ContactIndex := Target;
        Tile := Maps[Hero.floor, Target + 2];
        mmmes;
        if (Item = 6) and (TileClass = 1) then
          matokwork
        else if (Item = 7) and (TileClass = 2) then
        begin
          Enemy := MonsterIndex;
          Inc(Hero.gold, Monsters[Enemy].Gold);
          toroad2;
        end
        else if (Item = 12) and (TileClass = 3) then
        begin
          Found := 1;
          DamageMode := Motions[I];
          yukiwork;
        end;
      end;
      if Item = 12 then
      begin
        if Found = 1 then
        begin
          MessageText := GameplayText(Self, 198);
          PushEvent(2, 1, 0);
        end
        else
          PushEvent(2, 65, 0);
      end;
    end;
    8:
    begin
      Dec(Hero.warp_staff);
      { Opposite cell on the 11-by-11 board, equivalent to a half-turn. }
      Target := 120 - Position;
      if Maps[Hero.floor, Target + 2] = 6 then
      begin
        Hero.x := Target mod 11;
        Hero.y := Target div 11;
        GameplayRefresh(Self);
        PlayEffect(Self, 2);
        GameplayMessage(Self, 62);
      end
      else
        GameplayMessage(Self, 68);
      itemdisp;
      itemlive;
      Exit;
    end;
    9, 10:
    begin
      if Item = 9 then
        Destination := Hero.floor + 1
      else
        Destination := Hero.floor - 1;
      { Wings preserve coordinates and are consumed only for a road landing. }
      if (Destination >= 0) and (Destination <= 50) and (Maps[Destination, Position + 2] = 6) then
      begin
        if Item = 9 then
          Hero.ascent_wing := 0
        else
          Hero.descent_wing := 0;
        Hero.floor := Destination;
        soundcheck;
        soundplay;
        GameplayRefresh(Self);
        if Item = 9 then
          PushEvent(2, 63, 0)
        else
          PushEvent(2, 64, 0);
        PushEvent(8, 0, 0);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
      end
      else
      begin
        if Item = 9 then
          GameplayMessage(Self, 69)
        else
          GameplayMessage(Self, 70);
        itemlive;
        Exit;
      end;
    end;
    13:
    begin
      Hero.magic_key := 0;
      PushEvent(2, 66, 0);
      PushEvent(8, 0, 0);
      for Target := 120 downto 0 do
        if Maps[Hero.floor, Target + 2] = 1 then
        begin
          PushEvent(13, Target, 1);
          doorstackin;
          PushEvent(0, 0, 0);
          PushEvent(1, 1, 0);
        end;
    end;
    14:
    begin
      Hero.super_mattock := 0;
      PushEvent(2, 67, 0);
      PushEvent(8, 0, 0);
      for X := 10 downto 0 do
        for Y := 10 downto 0 do
        begin
          Target := Y * 11 + X;
          if Maps[Hero.floor, Target + 2] = 8 then
          begin
            PushEvent(0, 0, 0);
            PushEvent(6, Target, 6);
            PushEvent(0, 0, 0);
            PushEvent(1, 2, 0);
          end;
        end;
    end;
  end;
  timer2on;
end;

procedure TTSW10.Image4Click(Sender: TObject);
begin
  img4work;
end;
procedure TTSW10.Image5Click(Sender: TObject);
begin
  img5work;
end;
procedure TTSW10.Image6Click(Sender: TObject);
begin
  img6work;
end;
procedure TTSW10.Image8Click(Sender: TObject);
begin
  img8work;
end;
procedure TTSW10.Image9Click(Sender: TObject);
begin
  img9work;
end;
procedure TTSW10.Image10Click(Sender: TObject);
begin
  img10work;
end;
procedure TTSW10.Image11Click(Sender: TObject);
begin
  img11work;
end;
procedure TTSW10.Image12Click(Sender: TObject);
begin
  img12work;
end;
procedure TTSW10.Image13Click(Sender: TObject);
begin
  img13work;
end;
procedure TTSW10.Image15Click(Sender: TObject);
begin
  img15work;
end;
procedure TTSW10.Image16Click(Sender: TObject);
begin
  img16work;
end;
procedure TTSW10.Image17Click(Sender: TObject);
begin
  img17work;
end;

procedure TTSW10.itemichiwork2; { $0046171C; scan at most all fifteen inventory slots }
var
  I: Longint;
begin
  for I := 0 to 14 do
  begin
    GameplayInventoryCursor := (GameplayInventoryCursor + 15) mod 15;
    if ReadHeroField(68 + GameplayInventoryCursor * 4) <> 0 then
      Exit;
    Inc(GameplayInventoryCursor);
  end;
  GameplayInventoryCursor := 0;
end;

procedure TTSW10.itemichiwork; { $004610C4 }
var
  ItemImage: TImage;
  Count, Step, I: Longint;
begin
  Count := 0;
  for I := 0 to 14 do
    Inc(Count, ReadHeroField(68 + I * 4));
  if Count = 0 then
  begin
    Image22.Visible := False;
    Exit;
  end;
  case FacingRequest of
    1: Step := -3;
    2: Step := -1;
    3: Step := 1;
    4: Step := 3;
  else
    Step := 1;
  end;
  for I := 0 to 14 do
  begin
    GameplayInventoryCursor := (GameplayInventoryCursor + 15) mod 15;
    if ReadHeroField(68 + GameplayInventoryCursor * 4) <> 0 then
      Break;
    Inc(GameplayInventoryCursor, Step);
  end;
  { A vertical step visits only five slots. Fall back to the next occupied
    slot when that entire column is empty. }
  GameplayInventoryCursor := (GameplayInventoryCursor + 15) mod 15;
  if ReadHeroField(68 + GameplayInventoryCursor * 4) = 0 then
    itemichiwork2;
  case GameplayInventoryCursor of
    0: ItemImage := Image6;
    1: ItemImage := Image5;
    2: ItemImage := Image4;
    3: ItemImage := Image7;
    4: ItemImage := Image8;
    5: ItemImage := Image9;
    6: ItemImage := Image10;
    7: ItemImage := Image11;
    8: ItemImage := Image12;
    9: ItemImage := Image13;
    10: ItemImage := Image14;
    11: ItemImage := Image15;
    12: ItemImage := Image16;
    13: ItemImage := Image17;
  else
    ItemImage := Image18;
  end;
  Image22.Left := ItemImage.Left;
  Image22.Top := ItemImage.Top;
  Image22.Width := ItemImage.Width;
  Image22.Height := ItemImage.Height;
  Image22.Visible := True;
end;

procedure GameplayMove(Form: TTSW10; Direction: Longint);
var
  X, Y: Longint;
begin
  if (InputEnabled = 0) or (EventCursor > 0) or EventPaused or (Hero.hp <= 0) then
    Exit;
  X := Hero.x;
  Y := Hero.y;
  FacingRequest := Direction;
  case Direction of
    1:
    begin
      Dec(Y);
      Hero.facing := 4;
    end;
    2:
    begin
      Dec(X);
      Hero.facing := 2;
    end;
    3:
    begin
      Inc(X);
      Hero.facing := 3;
    end;
    4:
    begin
      Inc(Y);
      Hero.facing := 1;
    end;
  end;
  if (X < 0) or (X > 10) or (Y < 0) or (Y > 10) then
    Exit;
  HeroCell := Hero.y * 11 + Hero.x;
  PreviousCell := HeroCell;
  ContactIndex := Y * 11 + X;
  Form.handan;
end;

procedure TTSW10.BitBtn1Click(Sender: TObject);
begin
  GameplayMove(Self, 1);
end;
procedure TTSW10.BitBtn2Click(Sender: TObject);
begin
  GameplayMove(Self, 2);
end;
procedure TTSW10.BitBtn3Click(Sender: TObject);
begin
  GameplayMove(Self, 3);
end;
procedure TTSW10.BitBtn4Click(Sender: TObject);
begin
  GameplayMove(Self, 4);
end;

procedure TTSW10.formkeydown(Sender: TObject; var Key: Word; Shift: TShiftState);
var
  Direction, Step: Longint;
begin
  if Key = VK_ESCAPE then
  begin
    if Image22.Visible then
      Image22.Visible := False
    else if Button37.Visible then
      Button37Click(Self)
    else if Button36.Visible then
      Button36Click(Self)
    else if Button35.Visible then
      Button35Click(Self)
    else if Button10.Visible then
      Button10Click(Self)
    else if Button7.Visible then
      Button7Click(Self);
    Key := 0;
    Exit;
  end;
  if Key = VK_RETURN then
  begin
    if Button1.Visible then
      Button1Click(Self)
    else if Button38.Visible then
      Button38Click(Self)
    else if Button10.Visible then
      Button10Click(Self)
    else if Button36.Visible then
      Button36Click(Self)
    else if Button35.Visible then
      Button35Click(Self)
    else if Button2.Visible then
      Button2Click(Self)
    else if (InputEnabled <> 0) and (EventCursor = 0) then
    begin
      if not Image22.Visible then
        itemichiwork
      else
      begin
        Image22.Visible := False;
        case GameplayInventoryCursor of
          0: img6work;
          1: img5work;
          2: img4work;
          4: img8work;
          5: img9work;
          6: img10work;
          7: img11work;
          8: img12work;
          9: img13work;
          11: img15work;
          12: img16work;
          13: img17work;
        end;
      end;
    end;
    Key := 0;
    Exit;
  end;
  Direction := 0;
  case Key of
    VK_UP: Direction := 1;
    VK_LEFT: Direction := 2;
    VK_RIGHT: Direction := 3;
    VK_DOWN: Direction := 4;
  end;
  if Direction = 0 then
    Exit;
  if Image22.Visible then
  begin
    FacingRequest := Direction;
    case Direction of
      1: Step := -3;
      2: Step := -1;
      3: Step := 1;
    else
      Step := 3;
    end;
    Inc(GameplayInventoryCursor, Step);
    itemichiwork;
  end
  else if Button10.Visible then
  begin
    if (Direction = 1) and Button8.Enabled then
      Button8Click(Self)
    else if (Direction = 4) and Button9.Enabled then
      Button9Click(Self);
  end
  else if Button37.Visible then
  begin
    if Direction = 1 then
      Button37Click(Self)
    else if Direction = 4 then
      Button38Click(Self);
  end
  else
    GameplayMove(Self, Direction);
  Key := 0;
end;

procedure TTSW10.monidou; { $00480384; cardinal tile slide }
var
  FromCell, ToCell, OldContact, OldDirection, OldX, OldY, I, Tile: Longint;
begin
  FromCell := Smallint(EventStack[EventCursor].A);
  ToCell := Smallint(EventStack[EventCursor].B);
  if (FromCell < 0) or (FromCell > 120) or (ToCell < 0) or (ToCell > 120) then
    Exit;
  Tile := Maps[Hero.floor, FromCell + 2];
  OldContact := ContactIndex;
  OldDirection := Hero.facing;
  OldX := Hero.x;
  OldY := Hero.y;
  GameplayWalkingFrom := FromCell;
  GameplayWalkingTotal := Image6.Width;
  if GameplayWalkingTotal < 1 then
    GameplayWalkingTotal := 1;
  ContactIndex := ToCell;
  ScratchIndex := Tile - 1;
  case ToCell - FromCell of
    -11: Damage := 4;
    -1: Damage := 2;
    1: Damage := 3;
    11: Damage := 1;
  else
    Damage := 0;
  end;
  for I := 1 to GameplayWalkingTotal do
  begin
    GameplayWalkingStep := I;
    monidouwork;
  end;
  Maps[Hero.floor, ToCell + 2] := Tile;
  Maps[Hero.floor, FromCell + 2] := 6;
  ContactIndex := OldContact;
  Hero.facing := OldDirection;
  Hero.x := OldX;
  Hero.y := OldY;
  GameplayRefresh(Self);
end;

procedure TTSW10.monidouwork; { $00480A90 }
var
  PixelX, PixelY, FromX, FromY, ToX, ToY: Longint;
begin
  if (MapBitmap1 = nil) or (GameplayWalkingTotal = 0) then
    Exit;
  FromX := GameplayWalkingFrom mod 11;
  FromY := GameplayWalkingFrom div 11;
  ToX := ContactIndex mod 11;
  ToY := ContactIndex div 11;
  PixelX :=
      FromX * Image6.Width
          + (ToX - FromX) * Image6.Width * GameplayWalkingStep div GameplayWalkingTotal;
  PixelY :=
      FromY * Image6.Height
          + (ToY - FromY) * Image6.Height * GameplayWalkingStep div GameplayWalkingTotal;
  Canvas.Draw(UiSpan, UiStep, MapBitmap1);
  WorkBitmap1.Width := Image6.Width;
  WorkBitmap1.Height := Image6.Height;
  WorkBitmap2.Width := Image6.Width;
  WorkBitmap2.Height := Image6.Height;
  WorkBitmap3.Width := Image6.Width;
  WorkBitmap3.Height := Image6.Height;
  ImageList1.Draw(WorkBitmap1.Canvas, 0, 0, 5);
  ImageList1.Draw(WorkBitmap2.Canvas, 0, 0, ScratchIndex);
  ImageList3.Draw(WorkBitmap3.Canvas, 0, 0, ScratchIndex);
  TargetRect := Rect(0, 0, Image6.Width, Image6.Height);
  SourceRect := TargetRect;
  kasanegaki;
  Canvas.Draw(UiSpan + PixelX, UiStep + PixelY, WorkBitmap1);
end;

procedure TTSW10.dooropen; { $004770E0; sixteen-frame door/wall movement }
var
  Cell, Motion, Frame, Tile, PixelX, PixelY, Part: Longint;
begin
  Cell := Smallint(EventStack[EventCursor].A);
  Motion := Smallint(EventStack[EventCursor].B);
  if (Cell < 0) or (Cell > 120) then
    Exit;
  if EventCursor > 0 then
    Frame := Smallint(EventStack[EventCursor - 1].B)
  else
    Frame := 16;
  if Frame = 16 then
  begin
    if Motion = 5 then
      Maps[Hero.floor, Cell + 2] := 4
    else if Motion = 8 then
      Maps[Hero.floor, Cell + 2] := 8
    else
      Maps[Hero.floor, Cell + 2] := 6;
    GameplayRefresh(Self);
    Exit;
  end;
  if MapBitmap1 = nil then
    Exit;
  Tile := Maps[Hero.floor, Cell + 2];
  PixelX := (Cell mod 11) * Image6.Width;
  PixelY := (Cell div 11) * Image6.Height;
  Part := Image6.Height * Frame div 16;
  WorkBitmap1.Width := Image6.Width;
  WorkBitmap1.Height := Image6.Height;
  WorkBitmap2.Width := Image6.Width;
  WorkBitmap2.Height := Image6.Height;
  ImageList1.Draw(WorkBitmap1.Canvas, 0, 0, 5);
  if (Motion = 5) or (Motion = 8) then
  begin
    if Motion = 5 then
      Tile := 4
    else
      Tile := 8;
    ImageList1.Draw(WorkBitmap2.Canvas, 0, 0, Tile - 1);
    TargetRect := Rect(0, Image6.Height - Part, Image6.Width, Image6.Height);
    SourceRect := Rect(0, 0, Image6.Width, Part);
  end
  else
  begin
    ImageList1.Draw(WorkBitmap2.Canvas, 0, 0, Tile - 1);
    TargetRect := Rect(0, Part, Image6.Width, Image6.Height);
    SourceRect := Rect(0, 0, Image6.Width, Image6.Height - Part);
  end;
  WorkBitmap1.Canvas.CopyRect(TargetRect, WorkBitmap2.Canvas, SourceRect);
  MapBitmap1.Canvas.Draw(PixelX, PixelY, WorkBitmap1);
  MapBitmap2.Canvas.Draw(PixelX, PixelY, WorkBitmap1);
  Canvas.Draw(UiSpan + PixelX, UiStep + PixelY, WorkBitmap1);
end;

procedure TTSW10.banpaiawork; { $0047C978; transformation raster tile }
var
  Cell, Frame, PixelX, PixelY: Longint;
begin
  if MapBitmap1 = nil then
    Exit;
  Cell := ContactIndex;
  if (Cell < 0) or (Cell > 120) then
    Cell := 27;
  Frame := DoorOpened + 82;
  if (Frame < 0) or (Frame >= ImageList1.Count) then
    Exit;
  WorkBitmap1.Width := Image6.Width;
  WorkBitmap1.Height := Image6.Height;
  WorkBitmap2.Width := Image6.Width;
  WorkBitmap2.Height := Image6.Height;
  WorkBitmap3.Width := Image6.Width;
  WorkBitmap3.Height := Image6.Height;
  ImageList1.Draw(WorkBitmap1.Canvas, 0, 0, 5);
  ImageList1.Draw(WorkBitmap2.Canvas, 0, 0, Frame);
  ImageList3.Draw(WorkBitmap3.Canvas, 0, 0, Frame);
  TargetRect := Rect(0, 0, Image6.Width, Image6.Height);
  SourceRect := TargetRect;
  kasanegaki;
  PixelX := (Cell mod 11) * Image6.Width;
  PixelY := (Cell div 11) * Image6.Height;
  Canvas.Draw(UiSpan + PixelX, UiStep + PixelY, WorkBitmap1);
end;
