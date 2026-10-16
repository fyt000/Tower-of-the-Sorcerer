procedure TTSW10.monswork; { $0044B6F4 }
begin
  MonsterText := ListBox2.Items[$5D];
  case MonsterIndex of
    Ord(monsterGreenSlime)..33: MonsterText := ListBox2.Items[MonsterIndex + $5E];
  end;
end;

procedure TTSW10.monshyouji; { $0044B78C }
var
  Frame: Longint;
begin
  Image31.Visible := False;
  DrawX := 0;
  DrawY := 0;
  if MonsterIndex >= Ord(monsterGreenSlime) then
  begin
    WorkBitmap1.Width := Image6.Width;
    WorkBitmap1.Height := Image6.Height;
    WorkBitmap2.Width := WorkBitmap1.Width;
    WorkBitmap2.Height := WorkBitmap1.Height;
    WorkBitmap3.Width := WorkBitmap1.Width;
    WorkBitmap3.Height := WorkBitmap1.Height;
    Memo5.ReadOnly := True;
    Memo6.ReadOnly := True;
    Memo7.ReadOnly := True;
    monswork;
    Frame := 0;
    case MonsterIndex of
      Ord(monsterGreenSlime)..Ord(monsterVampire): Frame := MonsterIndex * 2 + $3C;
      Ord(monsterOctopus): Frame := $67;
      Ord(monsterDragon): Frame := $79;
      Ord(monsterGoldenKnight)..Ord(monsterGateKeeperA): Frame := MonsterIndex * 2 + $5C;
    end;
    ImageList1.Draw(WorkBitmap1.Canvas, 0, 0, $A2);
    ImageList1.Draw(WorkBitmap2.Canvas, 0, 0, Frame);
    ImageList3.Draw(WorkBitmap3.Canvas, 0, 0, Frame);
    TargetRect := Rect(0, 0, Image6.Width, Image6.Height);
    SourceRect := TargetRect;
    kasanegaki;
    case GameOptions[optionDisplaySize] of
      display640x400:
      begin
        Image31.Top := $E6;
        Image31.Left := Image3.Left + $2E;
      end;
      display800x500:
      begin
        Image31.Top := $120;
        Image31.Left := Image3.Left + $3A;
      end;
    end;
    Image31.Picture.Bitmap := WorkBitmap1;
    Memo8.Text := MonsterText;
    Memo5.Text := IntToStr(Monsters[MonsterIndex].HP * (Hero.cycle_factor_minus_one + 1));
    Memo6.Text := IntToStr(Monsters[MonsterIndex].Attack * (Hero.cycle_factor_minus_one + 1));
    Memo7.Text := IntToStr(Monsters[MonsterIndex].Defense * (Hero.cycle_factor_minus_one + 1));
    Image31.Visible := True;
  end
  else
  begin
    Memo5.ReadOnly := False;
    Memo6.ReadOnly := False;
    Memo7.ReadOnly := False;
    monswork;
    WorkBitmap3.Width := Image6.Width;
    WorkBitmap3.Height := Image6.Height;
    ImageList1.Draw(WorkBitmap3.Canvas, 0, 0, $A2);
    case GameOptions[optionDisplaySize] of
      display640x400:
      begin
        Image31.Top := $E6;
        Image31.Left := Image3.Left + $2E;
      end;
      display800x500:
      begin
        Image31.Top := $120;
        Image31.Left := Image3.Left + $3A;
      end;
    end;
    Image31.Canvas.Draw(0, 0, WorkBitmap3);
    Memo8.Text := MonsterText;
    Memo5.Text := ListBox2.Items[$D6];
    Memo6.Text := ListBox2.Items[$D7];
    Memo7.Text := ListBox2.Items[$D8];
  end;
end;

procedure TTSW10.disp; { $0044CB34 }
begin
  if Hero.floor < 10 then
    FloorSpacing := '  '
  else
    FloorSpacing := ' ';
  Memo11.Text := ListBox2.Items[$D4] + FloorSpacing + IntToStr(Hero.floor) + ListBox2.Items[$D5];
  Memo1.Text := IntToStr(Hero.hp);
  Memo2.Text := IntToStr(Hero.attack);
  Memo3.Text := IntToStr(Hero.defense);
  Memo4.Text := IntToStr(Hero.gold);
  if TileClass = 1 then
    Edit8.Text := MessageText
  else
    Edit8.Text := ListBox2.Items[TileClass + $7F];
end;

procedure TTSW10.img4work; { $00481E80 }
begin
  Hero.Word632 := Ord(flightNone);
  Hero.Word664 := Ord(stairNone);
  DamageMode := 2;
  StrikeCount := -1;
  MonsterIndex := -1;
  monshyouji;
  if Hero.flight_orb = 1 then
  begin
    itemdel;
    TileClass := 0;
    ScratchIndex := Hero.y * BoardWidth + Hero.x;
    NeighborIndex := ScratchIndex - BoardWidth;
    case Hero.y of
      1..10: mmes;
    end;
    NeighborIndex := ScratchIndex - 1;
    case Hero.x of
      1..10: mmes;
    end;
    NeighborIndex := ScratchIndex + 1;
    case Hero.x of
      0..9: mmes;
    end;
    NeighborIndex := ScratchIndex + BoardWidth;
    case Hero.y of
      0..9: mmes;
    end;
    if TileClass = $13 then
    begin
      if Hero.music_track <> 0 then
        MediaPlayer5.Close;
      mhyouji;
      disp;
      Hero.Word48 := 1;
      Button8.Visible := True;
      Button8.Enabled := True;
      if Hero.floor = Hero.highest_floor then
        Button8.Enabled := False;
      Button9.Visible := True;
      Button9.Enabled := True;
      if Hero.floor <= 1 then
        Button9.Enabled := False;
      Button10.Visible := True;
      Button10.SetFocus;
    end
    else
    begin
      TileClass := $14;
      itemlive;
      disp;
    end;
  end;
end;

procedure TTSW10.Button9Click(Sender: TObject); { $0044ED1C }
begin
  if Hero.floor > 1 then
  begin
    Hero.Word632 := Ord(flightDown);
    if Hero.floor = $2D then
      Hero.floor := $2B
    else
      Dec(Hero.floor);
    mhyouji;
    disp;
    if not Button8.Enabled then
      Button8.Enabled := True;
    if Hero.floor = 1 then
    begin
      Button9.Enabled := False;
      Button10.SetFocus;
    end;
  end;
end;

procedure TTSW10.Button8Click(Sender: TObject); { $0044ED94 }
begin
  if Hero.floor < Hero.highest_floor then
  begin
    Hero.Word632 := Ord(flightUp);
    if Hero.floor = $2B then
      Hero.floor := $2D
    else
      Inc(Hero.floor);
    mhyouji;
    disp;
    if (Hero.floor = $23) and (Maps[35, 93] + Maps[2, 122] = $1B) then
      Maps[2, 122] := tileRoad;
    if not Button9.Enabled and (Hero.floor > 1) then
      Button9.Enabled := True;
    if Hero.highest_floor = Hero.floor then
    begin
      Button8.Enabled := False;
      Button10.SetFocus;
    end;
  end;
end;

procedure TTSW10.Button10Click(Sender: TObject); { $0044EAF4 }
begin
  Button8.Visible := False;
  Button9.Visible := False;
  Button10.Visible := False;
  if (Hero.Word632 <> Ord(flightNone)) and (Hero.floor <> $19) and (Maps[25, 73] = tileFairy) then
    Maps[25, 73] := tileRoad;
  if (Hero.Word632 <> Ord(flightNone)) and (Hero.floor <> $31) and (Maps[49, 18] = tileFairy) then
    Maps[49, 18] := tileRoad;
  Hero.Word48 := 0;
  case Hero.Word632 of
    Ord(flightUp):
      if (Hero.floor = Hero.highest_floor) and (Hero.Word664 = Ord(stairUp)) then
        Hero.Word632 := Ord(flightDown);
    Ord(flightDown):
      if (Hero.floor = Hero.highest_floor) and (Hero.Word664 <> Ord(stairUp)) then
        Hero.Word632 := Ord(flightUp);
  end;
  case Hero.Word632 of
    Ord(flightUp)..Ord(flightDown):
    begin
      Hero.x := Maps[Hero.floor, Hero.Word632 - 1] mod BoardWidth;
      Hero.y := Maps[Hero.floor, Hero.Word632 - 1] div BoardWidth;
    end;
  end;
  if (Hero.Word632 <> Ord(flightNone)) and (Hero.highest_floor = $1D) and (Hero.floor < $1D) then
  begin
    Maps[29, 40] := tileRoad;
    Maps[29, 29] := tileRoad;
    Maps[29, 19] := tileThief;
  end;
  { Preview rendering uses DrawIndex without changing the movement cursor. }
  FlightCell := Hero.y * BoardWidth + Hero.x;
  DrawX := (Image6.Width * FlightCell) mod (Image6.Width * BoardWidth);
  DrawY := ((Image6.Height * FlightCell) div (Image6.Height * BoardWidth)) * Image6.Height;
  case Hero.Word632 of
    Ord(flightUp): kaidanupcheck;
    Ord(flightDown): kaidandowncheck;
  end;
  timer2on;
  { PushCommand(0, 0, 0): wait. }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(1, 2, 0): flight sound. }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSound);
  EventStack[EventCursor].A := 2;
  EventStack[EventCursor].B := 0;
  yusyahyouji1;
  TileClass := $17;
  disp;
  if Hero.music_track <> 0 then
  begin
    soundcheck;
    soundplay;
  end;
  itemlive;
end;
