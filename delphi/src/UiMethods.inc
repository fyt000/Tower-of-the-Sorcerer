{ Status display, animation timer, and shared font/scene initialization. }

procedure TTSW10.keydisplay; { $0044BED8 }
var
  I: Longint;
begin
  if Hero.red_keys + Hero.blue_keys + Hero.yellow_keys = 0 then
    Image32.Visible := False
  else
  begin
    WorkBitmap2.Height := Image6.Height * 2;
    WorkBitmap2.Width := Image6.Width * 3;
    ScratchIndex := Hero.red_keys;
    NeighborIndex := Hero.blue_keys;
    NeighborY := Hero.yellow_keys;
    for I := 0 to 23 do
    begin
      DoorOpened := I;
      DrawX := I mod 6;
      DrawY := I div 6;
      if ScratchIndex <> 0 then
      begin
        DamageMode := 0;
        ScratchIndex := ScratchIndex - 1;
      end
      else if NeighborIndex <> 0 then
      begin
        DamageMode := 1;
        NeighborIndex := NeighborIndex - 1;
      end
      else if NeighborY <> 0 then
      begin
        DamageMode := 2;
        NeighborY := NeighborY - 1;
      end
      else
        DamageMode := 3;
      ImageList2.Draw(
          WorkBitmap2.Canvas,
          (Image6.Width div 2) * DrawX,
          (Image6.Height div 2) * DrawY,
          DamageMode
      );
    end;
    Image32.Picture.Bitmap := WorkBitmap2;
    Image32.Visible := True;
  end;
end;

procedure TTSW10.itemdisp; { $0044CCD8 }
type
  TItemWords = array[0..14] of Longint;
var
  Column, Row, Index, Value: Longint;
  ItemImages: array[0..14] of TImage;
  Item: TImage;
begin
  WorkBitmap1.Free;
  WorkBitmap1 := TBitmap.Create;
  WorkBitmap2.Free;
  WorkBitmap2 := TBitmap.Create;
  WorkBitmap3.Free;
  WorkBitmap3 := TBitmap.Create;
  WorkBitmap1.Height := Image6.Height;
  WorkBitmap1.Width := Image6.Width;
  WorkBitmap2.Height := WorkBitmap1.Height;
  WorkBitmap2.Width := WorkBitmap1.Width;
  WorkBitmap3.Height := WorkBitmap1.Height;
  WorkBitmap3.Width := WorkBitmap1.Width;
  DrawX := 0;
  DrawY := 0;
  DoorOpened := $A2;
  ImageList1.Draw(WorkBitmap1.Canvas, DrawX, 0, $A2);
  if Hero.sword <> 0 then
  begin
    ImageList1.Draw(WorkBitmap2.Canvas, DrawX, DrawY, Hero.sword + $31);
    ImageList3.Draw(WorkBitmap3.Canvas, DrawX, DrawY, Hero.sword + $31);
    TargetRect := Rect(0, 0, Image6.Width, Image6.Height);
    SourceRect := TargetRect;
    kasanegaki;
  end;
  Image19.Picture.Bitmap := WorkBitmap1;
  case Hero.sword of
    0:
    begin
      Memo9.Text := '      ';
      Image19.ShowHint := False;
    end;
    1:
    begin
      Memo9.Text := 'Iron';
      Image19.Hint := 'Iron Sword';
      Image19.ShowHint := True;
    end;
    2:
    begin
      Memo9.Text := 'Silver';
      Image19.Hint := 'Silver Sword';
      Image19.ShowHint := True;
    end;
    3:
    begin
      Memo9.Text := 'Knight';
      Image19.Hint := 'Knight Sword';
      Image19.ShowHint := True;
    end;
    4:
    begin
      Memo9.Text := 'Holy';
      Image19.Hint := 'Holy Sword';
      Image19.ShowHint := True;
    end;
    5:
    begin
      Memo9.Text := 'Sacred';
      Image19.Hint := 'Sacred Sword';
      Image19.ShowHint := True;
    end;
  end;
  DoorOpened := $A2;
  ImageList1.Draw(WorkBitmap1.Canvas, DrawX, DrawY, $A2);
  if Hero.shield <> 0 then
  begin
    ImageList1.Draw(WorkBitmap2.Canvas, DrawX, DrawY, Hero.shield + $36);
    ImageList3.Draw(WorkBitmap3.Canvas, DrawX, DrawY, Hero.shield + $36);
    TargetRect := Rect(0, 0, Image6.Width, Image6.Height);
    SourceRect := TargetRect;
    kasanegaki;
  end;
  Image20.Picture.Bitmap := WorkBitmap1;
  case Hero.shield of
    0:
    begin
      Memo10.Text := '      ';
      Image20.ShowHint := False;
    end;
    1:
    begin
      Memo10.Text := 'Iron';
      Image20.Hint := 'Iron Shield';
      Image20.ShowHint := True;
    end;
    2:
    begin
      Memo10.Text := 'Silver';
      Image20.Hint := 'Silver Shield';
      Image20.ShowHint := True;
    end;
    3:
    begin
      Memo10.Text := 'Knight';
      Image20.Hint := 'Knight Shield';
      Image20.ShowHint := True;
    end;
    4:
    begin
      Memo10.Text := 'Holy';
      Image20.Hint := 'Holy Shield';
      Image20.ShowHint := True;
    end;
    5:
    begin
      Memo10.Text := 'Sacred';
      Image20.Hint := 'Sacred Shield';
      Image20.ShowHint := True;
    end;
  end;
  ItemImages[0] := Image6;
  ItemImages[1] := Image5;
  ItemImages[2] := Image4;
  ItemImages[3] := Image7;
  ItemImages[4] := Image8;
  ItemImages[5] := Image9;
  ItemImages[6] := Image10;
  ItemImages[7] := Image11;
  ItemImages[8] := Image12;
  ItemImages[9] := Image13;
  ItemImages[10] := Image14;
  ItemImages[11] := Image15;
  ItemImages[12] := Image16;
  ItemImages[13] := Image17;
  ItemImages[14] := Image18;
  for Column := 0 to 2 do
    for Row := 0 to 4 do
    begin
      Index := Row * 3 + Column;
      DoorOpened := Index + $24;
      ImageList1.Draw(WorkBitmap1.Canvas, 0, 0, $A2);
      Value := TItemWords(Pointer(@Hero.hero_orb)^)[Index];
      if Value <> 0 then
      begin
        ImageList1.Draw(WorkBitmap2.Canvas, 0, 0, DoorOpened - 1);
        ImageList3.Draw(WorkBitmap3.Canvas, 0, 0, DoorOpened - 1);
        TargetRect := Rect(0, 0, Image6.Width, Image6.Height);
        SourceRect := TargetRect;
        kasanegaki;
      end;
      Item := ItemImages[Index];
      Item.Picture.Bitmap := WorkBitmap1;
      if Value = 0 then
        Item.ShowHint := False
      else
      begin
        Item.Visible := True;
        Item.ShowHint := True;
      end;
    end;
end;

procedure TTSW10.takowork1; { $004548A0 }
begin
  ScratchIndex := ((Hero.y * 11 + Hero.x) mod 11) * Image6.Width;
  NeighborIndex := ((Hero.y * 11 + Hero.x) div 11) * Image6.Height;
  ImageList1.Draw(MapBitmap1.Canvas, ScratchIndex - Image6.Width, NeighborIndex, 5);
  ImageList1.Draw(MapBitmap1.Canvas, ScratchIndex + Image6.Width, NeighborIndex, 5);
  ImageList1.Draw(MapBitmap1.Canvas, ScratchIndex - Image6.Width, NeighborIndex - Image6.Height, 5);
  ImageList1.Draw(MapBitmap1.Canvas, ScratchIndex, NeighborIndex - Image6.Height, 5);
  ImageList1.Draw(MapBitmap1.Canvas, ScratchIndex + Image6.Width, NeighborIndex - Image6.Height, 5);
  ImageList1
      .Draw(MapBitmap1.Canvas, ScratchIndex - Image6.Width, NeighborIndex - Image6.Height * 2, 5);
  ImageList1.Draw(MapBitmap1.Canvas, ScratchIndex, NeighborIndex - Image6.Height * 2, 5);
  ImageList1
      .Draw(MapBitmap1.Canvas, ScratchIndex + Image6.Width, NeighborIndex - Image6.Height * 2, 5);
end;

procedure TTSW10.takowork2; { $00454A58 }
begin
  ScratchIndex := ((Hero.y * 11 + Hero.x) mod 11) * Image6.Width;
  NeighborIndex := ((Hero.y * 11 + Hero.x) div 11) * Image6.Height;
  ImageList1.Draw(MapBitmap2.Canvas, ScratchIndex - Image6.Width, NeighborIndex, 5);
  ImageList1.Draw(MapBitmap2.Canvas, ScratchIndex + Image6.Width, NeighborIndex, 5);
  ImageList1.Draw(MapBitmap2.Canvas, ScratchIndex - Image6.Width, NeighborIndex - Image6.Height, 5);
  ImageList1.Draw(MapBitmap2.Canvas, ScratchIndex, NeighborIndex - Image6.Height, 5);
  ImageList1.Draw(MapBitmap2.Canvas, ScratchIndex + Image6.Width, NeighborIndex - Image6.Height, 5);
  ImageList1
      .Draw(MapBitmap2.Canvas, ScratchIndex - Image6.Width, NeighborIndex - Image6.Height * 2, 5);
  ImageList1.Draw(MapBitmap2.Canvas, ScratchIndex, NeighborIndex - Image6.Height * 2, 5);
  ImageList1
      .Draw(MapBitmap2.Canvas, ScratchIndex + Image6.Width, NeighborIndex - Image6.Height * 2, 5);
end;

procedure TTSW10.Timer1Timer(Sender: TObject); { $00443120 }
begin
  if AnimationFrame = 1 then
  begin
    MainForm.Canvas.Draw(UiSpan, UiStep, MapBitmap2);
    if Hero.Word48 = 0 then
    begin
      if (Hero.floor = 15)
          and (Hero.y * 11 + Hero.x = $3C)
          and (Maps[15, 62] = 6)
          and (Hero.Word608 < 2) then
      begin
        takowork2;
        Hero.Word608 := Hero.Word608 + 1;
      end;
      if (Hero.floor = 35)
          and (Hero.y * 11 + Hero.x = $47)
          and (Maps[35, 73] = 6)
          and (Hero.Word612 < 2) then
      begin
        takowork2;
        Hero.Word612 := Hero.Word612 + 1;
      end;
      case Hero.facing of
        1: ScratchIndex := $FE;
        2: ScratchIndex := $106;
        3: ScratchIndex := $10E;
        4: ScratchIndex := $116;
      end;
      DoorOpened := 1;
      yusyahyouji;
      MapBitmap2.Canvas.Draw(Image6.Width * Hero.x, Image6.Height * Hero.y, WorkBitmap1);
    end;
  end
  else
  begin
    MainForm.Canvas.Draw(UiSpan, UiStep, MapBitmap1);
    if Hero.Word48 = 0 then
    begin
      if (Hero.floor = 15)
          and (Hero.y * 11 + Hero.x = $3C)
          and (Maps[15, 62] = 6)
          and (Hero.Word608 < 2) then
      begin
        takowork1;
        Hero.Word608 := Hero.Word608 + 1;
      end;
      if (Hero.floor = 35)
          and (Hero.y * 11 + Hero.x = $47)
          and (Maps[35, 73] = 6)
          and (Hero.Word612 < 2) then
      begin
        takowork1;
        Hero.Word612 := Hero.Word612 + 1;
      end;
      case Hero.facing of
        1: ScratchIndex := $FE;
        2: ScratchIndex := $106;
        3: ScratchIndex := $10E;
        4: ScratchIndex := $116;
      end;
      DoorOpened := 0;
      yusyahyouji;
      MapBitmap1.Canvas.Draw(Image6.Width * Hero.x, Image6.Height * Hero.y, WorkBitmap1);
    end;
  end;
  AnimationFrame := AnimationFrame xor 1;
  if KeysPainted = 0 then
  begin
    keydisplay;
    KeysPainted := 1;
  end;
end;

procedure TAboutBox.formactivate(Sender: TObject); { $0043416C }
begin
  {$I AboutLayout.inc}
end;

procedure TForm4.form4activate(Sender: TObject); { $00440A98 }
var
  FontSize: Longint;
begin
  {$I DataHolderLayout.inc}
end;

procedure TForm4.form4onclose(Sender: TObject; var Action: TCloseAction); { $00440A88 }
begin
  ModalResult := 1;
end;

procedure ApplyFontLayout(Form: TTSW10); { $0047D4A4 before $0047F5A8 }
begin
  with Form do
  begin
    {$I FontLayout.inc}
  end;
end;

procedure PrepareSceneGraphics(Form: TTSW10); { $00454DE8 before $00431C8C }
var
  Path: string;
begin
  with Form do
  begin
    {$I StartupHidden.inc}
    if Hero.cycle_factor_minus_one = 0 then
      Path := Memo12.Lines[1] + DataDirectory + '\left.bmp'
    else
      Path := Memo12.Lines[1] + DataDirectory + '\leftr.bmp';
    Image2.Picture.LoadFromFile(Path);
    if Hero.cycle_factor_minus_one = 0 then
      Path := Memo12.Lines[1] + DataDirectory + '\right.bmp'
    else
      Path := Memo12.Lines[1] + DataDirectory + '\rightr.bmp';
    Image3.Picture.LoadFromFile(Path);
    TargetRect := Rect(0, 0, Image2.Width, Image2.Height);
    FrameBitmap.Canvas.CopyRect(TargetRect, Image2.Canvas, TargetRect);
    TargetRect := Rect(Image2.Width, 0, Image2.Width + Image1.Width, Image1.Height);
    SourceRect := Rect(0, 0, Image1.Width, Image1.Height);
    Image23.Width := Image1.Width;
    Image23.Height := Image1.Height;
    if Hero.cycle_factor_minus_one = 0 then
      Path := Memo12.Lines[1] + DataDirectory + '\title05.bmp'
    else
      Path := Memo12.Lines[1] + DataDirectory + '\title05R.bmp';
    Image23.Picture.LoadFromFile(Path);
    FrameBitmap.Canvas.CopyRect(TargetRect, Image23.Canvas, SourceRect);
    TargetRect :=
        Rect(
            Image2.Width + Image1.Width,
            0,
            Image2.Width + Image1.Width + Image3.Width,
            Image3.Height
        );
    SourceRect := Rect(0, 0, Image3.Width, Image3.Height);
    FrameBitmap.Canvas.CopyRect(TargetRect, Image3.Canvas, SourceRect);
  end;
end;
