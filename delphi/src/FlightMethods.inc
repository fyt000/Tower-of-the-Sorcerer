procedure TTSW10.monswork; { $0044B6F4 }
begin
  MonsterText := ListBox2.Items[$5D];
  if (MonsterIndex >= 0) and (MonsterIndex < $22) then
    MonsterText := ListBox2.Items[MonsterIndex + $5E];
end;

procedure TTSW10.monshyouji; { $0044B78C }
var
  Frame: Longint;
begin
  Image31.Visible := False;
  DrawX := 0;
  DrawY := 0;
  if MonsterIndex < 0 then
  begin
    Memo5.ReadOnly := False;
    Memo6.ReadOnly := False;
    Memo7.ReadOnly := False;
    monswork;
    WorkBitmap3.Width := Image6.Width;
    WorkBitmap3.Height := Image6.Height;
    ImageList1.Draw(WorkBitmap3.Canvas, 0, 0, $A2);
    if OriginalOptions[8] = 0 then
    begin Image31.Top := $E6; Image31.Left := Image3.Left + $2E; end
    else if OriginalOptions[8] = 1 then
    begin Image31.Top := $120; Image31.Left := Image3.Left + $3A; end;
    Image31.Canvas.Draw(0, 0, WorkBitmap3);
    Memo8.Text := MonsterText;
    Memo5.Text := ListBox2.Items[$D6];
    Memo6.Text := ListBox2.Items[$D7];
    Memo7.Text := ListBox2.Items[$D8];
  end
  else
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
    if (MonsterIndex >= 0) and (MonsterIndex < $12) then Frame := MonsterIndex * 2 + $3C
    else if MonsterIndex = $12 then Frame := $67
    else if MonsterIndex = $13 then Frame := $79
    else if (MonsterIndex >= $14) and (MonsterIndex <= $20) then Frame := MonsterIndex * 2 + $5C;
    ImageList1.Draw(WorkBitmap1.Canvas, 0, 0, $A2);
    ImageList1.Draw(WorkBitmap2.Canvas, 0, 0, Frame);
    ImageList3.Draw(WorkBitmap3.Canvas, 0, 0, Frame);
    TargetRect := Rect(0, 0, Image6.Width, Image6.Height);
    SourceRect := TargetRect;
    kasanegaki;
    if OriginalOptions[8] = 0 then
    begin Image31.Top := $E6; Image31.Left := Image3.Left + $2E; end
    else if OriginalOptions[8] = 1 then
    begin Image31.Top := $120; Image31.Left := Image3.Left + $3A; end;
    Image31.Picture.Bitmap := WorkBitmap1;
    Memo8.Text := MonsterText;
    Memo5.Text := IntToStr(Monsters[MonsterIndex].HP * (Hero.cycle_factor_minus_one + 1));
    Memo6.Text := IntToStr(Monsters[MonsterIndex].Attack * (Hero.cycle_factor_minus_one + 1));
    Memo7.Text := IntToStr(Monsters[MonsterIndex].Defense * (Hero.cycle_factor_minus_one + 1));
    Image31.Visible := True;
  end;
end;

procedure TTSW10.disp; { $0044CB34 }
begin
  if Hero.floor < 10 then FloorSpacing := '  ' else FloorSpacing := ' ';
  Memo11.Text := ListBox2.Items[$D4] + FloorSpacing + IntToStr(Hero.floor) + ListBox2.Items[$D5];
  Memo1.Text := IntToStr(Hero.hp);
  Memo2.Text := IntToStr(Hero.attack);
  Memo3.Text := IntToStr(Hero.defense);
  Memo4.Text := IntToStr(Hero.gold);
  if TileClass = 1 then Edit8.Text := MessageText
  else Edit8.Text := ListBox2.Items[TileClass + $7F];
end;

procedure TTSW10.img4work; { $00481E80 }
begin
  Hero.Word632 := 0;
  Hero.Word664 := 0;
  DamageMode := 2;
  StrikeCount := -1;
  MonsterIndex := -1;
  monshyouji;
  if Hero.flight_orb = 1 then
  begin
    itemdel;
    TileClass := 0;
    ScratchIndex := Hero.y * 11 + Hero.x;
    if (Hero.y >= 1) and (Hero.y <= 10) then
    begin NeighborIndex := ScratchIndex - 11; mmes; end;
    NeighborIndex := ScratchIndex - 1;
    if (Hero.x >= 1) and (Hero.x <= 10) then mmes;
    NeighborIndex := ScratchIndex + 1;
    if (Hero.x >= 0) and (Hero.x < 10) then mmes;
    NeighborIndex := ScratchIndex + 11;
    if (Hero.y >= 0) and (Hero.y < 10) then mmes;
    if TileClass = $13 then
    begin
      if Hero.Word360 <> 0 then MediaPlayer5.Stop;
      mhyouji;
      disp;
      Hero.Word48 := 1;
      Button8.Visible := True;
      Button8.Enabled := True;
      if Hero.floor = Hero.Word20 then Button8.Enabled := False;
      Button9.Visible := True;
      Button9.Enabled := True;
      if Hero.floor < 2 then Button9.Enabled := False;
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
    Hero.Word632 := 2;
    if Hero.floor = $2D then Hero.floor := $2B
    else Dec(Hero.floor);
    mhyouji;
    disp;
    if not Button8.Enabled then Button8.Enabled := True;
    if Hero.floor = 1 then
    begin Button9.Enabled := False; Button10.SetFocus; end;
  end;
end;

procedure TTSW10.Button8Click(Sender: TObject); { $0044ED94 }
begin
  if Hero.floor < Hero.Word20 then
  begin
    Hero.Word632 := 1;
    if Hero.floor = $2B then Hero.floor := $2D
    else Inc(Hero.floor);
    mhyouji;
    disp;
    if (Hero.floor = $23) and (Maps[35, 93] + Maps[2, 122] = $1B) then Maps[2, 122] := 6;
    if not Button9.Enabled and (Hero.floor > 1) then Button9.Enabled := True;
    if Hero.Word20 = Hero.floor then
    begin Button8.Enabled := False; Button10.SetFocus; end;
  end;
end;

procedure TTSW10.Button10Click(Sender: TObject); { $0044EAF4 }
var
  Cursor: Longint;
begin
  Button8.Visible := False;
  Button9.Visible := False;
  Button10.Visible := False;
  if (Hero.Word632 <> 0) and (Hero.floor <> $19) and (Maps[25, 73] = $17) then Maps[25, 73] := 6;
  if (Hero.Word632 <> 0) and (Hero.floor <> $31) and (Maps[49, 18] = $17) then Maps[49, 18] := 6;
  Hero.Word48 := 0;
  if Hero.Word632 = 1 then
  begin
    if (Hero.floor = Hero.Word20) and (Hero.Word664 = 1) then Hero.Word632 := 2;
  end
  else if (Hero.Word632 = 2) and (Hero.floor = Hero.Word20) and (Hero.Word664 <> 1) then Hero.Word632 := 1;
  if (Hero.Word632 >= 1) and (Hero.Word632 <= 2) then
  begin
    Hero.x := Maps[Hero.floor, Hero.Word632 - 1] mod 11;
    Hero.y := Maps[Hero.floor, Hero.Word632 - 1] div 11;
  end;
  if (Hero.Word632 <> 0) and (Hero.Word20 = $1D) and (Hero.floor < $1D) then
  begin Maps[29, 40] := 6; Maps[29, 29] := 6; Maps[29, 19] := $15; end;
  { The original display cursor is separate from ScratchIndex. }
  FlightCell := Hero.y * 11 + Hero.x;
  DrawX := (Image6.Width * FlightCell) mod (Image6.Width * 11);
  DrawY := ((Image6.Height * FlightCell) div (Image6.Height * 11)) * Image6.Height;
  if Hero.Word632 = 1 then kaidanupcheck
  else if Hero.Word632 = 2 then kaidandowncheck;
  timer2on;
  Cursor := EventCursor + 1;
  EventCursor := Cursor;
  EventStack[Cursor].Opcode := 0;
  EventStack[Cursor].A := 0;
  EventStack[Cursor].B := 0;
  Cursor := EventCursor + 1;
  EventCursor := Cursor;
  EventStack[Cursor].Opcode := 1;
  EventStack[Cursor].A := 2;
  EventStack[Cursor].B := 0;
  yusyahyouji1;
  TileClass := $17;
  disp;
  if Hero.Word360 <> 0 then
  begin soundcheck; soundplay; end;
  itemlive;
end;
