{ Status display, animation timer, and shared font/scene initialization. }

procedure TTSW10.keydisplay; { $0044BED8 }
var
  I: Longint;
begin
  if Hero.red_keys + Hero.blue_keys + Hero.yellow_keys <> 0 then
  begin
    WorkBitmap2.Height := Image6.Height * 2;
    WorkBitmap2.Width := Image6.Width * 3;
    ScratchIndex := Hero.red_keys;
    NeighborIndex := Hero.blue_keys;
    NeighborY := Hero.yellow_keys;
    for I := 0 to 23 do
    begin
      DoorOpened := I;
      DrawX := DoorOpened mod 6;
      DrawY := DoorOpened div 6;
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
  end
  else
    Image32.Visible := False;
end;

procedure TTSW10.itemdisp; { $0044CCD8 }
type
  THeroWords = array[0..170] of Longint;
var
  Column, Row: Longint;
  { Word 17 begins the fifteen inventory fields in the saved hero record. }
  HeroWords: THeroWords absolute Hero;
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
  ImageList1.Draw(WorkBitmap1.Canvas, DrawX, DrawY, DoorOpened);
  if Hero.sword <> Ord(equipmentNone) then
  begin
    ImageList1.Draw(WorkBitmap2.Canvas, DrawX, DrawY, Hero.sword + $31);
    ImageList3.Draw(WorkBitmap3.Canvas, DrawX, DrawY, Hero.sword + $31);
    TargetRect := Rect(0, 0, Image6.Width, Image6.Height);
    SourceRect := TargetRect;
    kasanegaki;
  end;
  Image19.Picture.Bitmap := WorkBitmap1;
  case Hero.sword of
    Ord(equipmentNone):
    begin
      Memo9.Text := '      ';
      Image19.ShowHint := False;
    end;
    Ord(equipmentIron):
    begin
      Memo9.Text := 'Iron';
      Image19.Hint := 'Iron Sword';
      Image19.ShowHint := True;
    end;
    Ord(equipmentSilver):
    begin
      Memo9.Text := 'Silver';
      Image19.Hint := 'Silver Sword';
      Image19.ShowHint := True;
    end;
    Ord(equipmentKnight):
    begin
      Memo9.Text := 'Knight';
      Image19.Hint := 'Knight Sword';
      Image19.ShowHint := True;
    end;
    Ord(equipmentHoly):
    begin
      Memo9.Text := 'Holy';
      Image19.Hint := 'Holy Sword';
      Image19.ShowHint := True;
    end;
    Ord(equipmentSacred):
    begin
      Memo9.Text := 'Sacred';
      Image19.Hint := 'Sacred Sword';
      Image19.ShowHint := True;
    end;
  end;
  DoorOpened := $A2;
  ImageList1.Draw(WorkBitmap1.Canvas, DrawX, DrawY, DoorOpened);
  if Hero.shield <> Ord(equipmentNone) then
  begin
    ImageList1.Draw(WorkBitmap2.Canvas, DrawX, DrawY, Hero.shield + $36);
    ImageList3.Draw(WorkBitmap3.Canvas, DrawX, DrawY, Hero.shield + $36);
    TargetRect := Rect(0, 0, Image6.Width, Image6.Height);
    SourceRect := TargetRect;
    kasanegaki;
  end;
  Image20.Picture.Bitmap := WorkBitmap1;
  case Hero.shield of
    Ord(equipmentNone):
    begin
      Memo10.Text := '      ';
      Image20.ShowHint := False;
    end;
    Ord(equipmentIron):
    begin
      Memo10.Text := 'Iron';
      Image20.Hint := 'Iron Shield';
      Image20.ShowHint := True;
    end;
    Ord(equipmentSilver):
    begin
      Memo10.Text := 'Silver';
      Image20.Hint := 'Silver Shield';
      Image20.ShowHint := True;
    end;
    Ord(equipmentKnight):
    begin
      Memo10.Text := 'Knight';
      Image20.Hint := 'Knight Shield';
      Image20.ShowHint := True;
    end;
    Ord(equipmentHoly):
    begin
      Memo10.Text := 'Holy';
      Image20.Hint := 'Holy Shield';
      Image20.ShowHint := True;
    end;
    Ord(equipmentSacred):
    begin
      Memo10.Text := 'Sacred';
      Image20.Hint := 'Sacred Shield';
      Image20.ShowHint := True;
    end;
  end;
  { Paint the inventory in column order, then update each original image control. }
  for Column := 0 to 2 do
    for Row := 0 to 4 do
    begin
      DoorOpened := Column + $A8 + Row * 3 - $84;
      ImageList1.Draw(WorkBitmap1.Canvas, 0, 0, $A2);
      if HeroWords[Row * 3 + Column + 17] <> 0 then
      begin
        ImageList1.Draw(WorkBitmap2.Canvas, 0, 0, DoorOpened - 1);
        ImageList3.Draw(WorkBitmap3.Canvas, 0, 0, DoorOpened - 1);
        TargetRect := Rect(0, 0, Image6.Width, Image6.Height);
        SourceRect := TargetRect;
        kasanegaki;
      end;
      case Row of
        0:
          case Column of
            0:
            begin
              Image6.Picture.Bitmap := WorkBitmap1;
              if HeroWords[Row * 3 + Column + 17] <> 0 then
              begin
                Image6.Visible := True;
                Image6.ShowHint := True;
              end
              else
                Image6.ShowHint := False;
            end;
            1:
            begin
              Image5.Picture.Bitmap := WorkBitmap1;
              if HeroWords[Row * 3 + Column + 17] <> 0 then
              begin
                Image5.Visible := True;
                Image5.ShowHint := True;
              end
              else
                Image5.ShowHint := False;
            end;
            2:
            begin
              Image4.Picture.Bitmap := WorkBitmap1;
              if HeroWords[Row * 3 + Column + 17] <> 0 then
              begin
                Image4.Visible := True;
                Image4.ShowHint := True;
              end
              else
                Image4.ShowHint := False;
            end;
          end;
        1:
          case Column of
            0:
            begin
              Image7.Picture.Bitmap := WorkBitmap1;
              if HeroWords[Row * 3 + Column + 17] <> 0 then
              begin
                Image7.Visible := True;
                Image7.ShowHint := True;
              end
              else
                Image7.ShowHint := False;
            end;
            1:
            begin
              Image8.Picture.Bitmap := WorkBitmap1;
              if HeroWords[Row * 3 + Column + 17] <> 0 then
              begin
                Image8.Visible := True;
                Image8.ShowHint := True;
              end
              else
                Image8.ShowHint := False;
            end;
            2:
            begin
              Image9.Picture.Bitmap := WorkBitmap1;
              if HeroWords[Row * 3 + Column + 17] <> 0 then
              begin
                Image9.Visible := True;
                Image9.ShowHint := True;
              end
              else
                Image9.ShowHint := False;
            end;
          end;
        2:
          case Column of
            0:
            begin
              Image10.Picture.Bitmap := WorkBitmap1;
              if HeroWords[Row * 3 + Column + 17] <> 0 then
              begin
                Image10.Visible := True;
                Image10.ShowHint := True;
              end
              else
                Image10.ShowHint := False;
            end;
            1:
            begin
              Image11.Picture.Bitmap := WorkBitmap1;
              if HeroWords[Row * 3 + Column + 17] <> 0 then
              begin
                Image11.Visible := True;
                Image11.ShowHint := True;
              end
              else
                Image11.ShowHint := False;
            end;
            2:
            begin
              Image12.Picture.Bitmap := WorkBitmap1;
              if HeroWords[Row * 3 + Column + 17] <> 0 then
              begin
                Image12.Visible := True;
                Image12.ShowHint := True;
              end
              else
                Image12.ShowHint := False;
            end;
          end;
        3:
          case Column of
            0:
            begin
              Image13.Picture.Bitmap := WorkBitmap1;
              if HeroWords[Row * 3 + Column + 17] <> 0 then
              begin
                Image13.Visible := True;
                Image13.ShowHint := True;
              end
              else
                Image13.ShowHint := False;
            end;
            1:
            begin
              Image14.Picture.Bitmap := WorkBitmap1;
              if HeroWords[Row * 3 + Column + 17] <> 0 then
              begin
                Image14.Visible := True;
                Image14.ShowHint := True;
              end
              else
                Image14.ShowHint := False;
            end;
            2:
            begin
              Image15.Picture.Bitmap := WorkBitmap1;
              if HeroWords[Row * 3 + Column + 17] <> 0 then
              begin
                Image15.Visible := True;
                Image15.ShowHint := True;
              end
              else
                Image15.ShowHint := False;
            end;
          end;
        4:
          case Column of
            0:
            begin
              Image16.Picture.Bitmap := WorkBitmap1;
              if HeroWords[Row * 3 + Column + 17] <> 0 then
              begin
                Image16.Visible := True;
                Image16.ShowHint := True;
              end
              else
                Image16.ShowHint := False;
            end;
            1:
            begin
              Image17.Picture.Bitmap := WorkBitmap1;
              if HeroWords[Row * 3 + Column + 17] <> 0 then
              begin
                Image17.Visible := True;
                Image17.ShowHint := True;
              end
              else
                Image17.ShowHint := False;
            end;
            2:
            begin
              Image18.Picture.Bitmap := WorkBitmap1;
              if HeroWords[Row * 3 + Column + 17] <> 0 then
              begin
                Image18.Visible := True;
                Image18.ShowHint := True;
              end
              else
                Image18.ShowHint := False;
            end;
          end;
      end;
    end;
end;

procedure TTSW10.takowork1; { $004548A0 }
begin
  ScratchIndex := ((Hero.y * BoardWidth + Hero.x) mod BoardWidth) * Image6.Width;
  NeighborIndex := ((Hero.y * BoardWidth + Hero.x) div BoardWidth) * Image6.Height;
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
  ScratchIndex := ((Hero.y * BoardWidth + Hero.x) mod BoardWidth) * Image6.Width;
  NeighborIndex := ((Hero.y * BoardWidth + Hero.x) div BoardWidth) * Image6.Height;
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
  if AnimationFrame = True then
  begin
    MainForm.Canvas.Draw(UiSpan, UiStep, MapBitmap2);
    if Hero.Word48 = 0 then
    begin
      if Hero.floor = 15 then
        if Hero.y * BoardWidth + Hero.x = $3C then
          if Maps[15, 62] = tileRoad then
            if Hero.Word608 <= 1 then
            begin
              takowork2;
              Hero.Word608 := Hero.Word608 + 1;
            end;
      if Hero.floor = 35 then
        if Hero.y * BoardWidth + Hero.x = $47 then
          if Maps[35, 73] = tileRoad then
            if Hero.Word612 <= 1 then
            begin
              takowork2;
              Hero.Word612 := Hero.Word612 + 1;
            end;
      case Hero.facing of
        Ord(hfDown): ScratchIndex := $FE;
        Ord(hfLeft): ScratchIndex := $106;
        Ord(hfRight): ScratchIndex := $10E;
        Ord(hfUp): ScratchIndex := $116;
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
      if Hero.floor = 15 then
        if Hero.y * BoardWidth + Hero.x = $3C then
          if Maps[15, 62] = tileRoad then
            if Hero.Word608 <= 1 then
            begin
              takowork1;
              Hero.Word608 := Hero.Word608 + 1;
            end;
      if Hero.floor = 35 then
        if Hero.y * BoardWidth + Hero.x = $47 then
          if Maps[35, 73] = tileRoad then
            if Hero.Word612 <= 1 then
            begin
              takowork1;
              Hero.Word612 := Hero.Word612 + 1;
            end;
      case Hero.facing of
        Ord(hfDown): ScratchIndex := $FE;
        Ord(hfLeft): ScratchIndex := $106;
        Ord(hfRight): ScratchIndex := $10E;
        Ord(hfUp): ScratchIndex := $116;
      end;
      DoorOpened := 0;
      yusyahyouji;
      MapBitmap1.Canvas.Draw(Image6.Width * Hero.x, Image6.Height * Hero.y, WorkBitmap1);
    end;
  end;
  AnimationFrame := not AnimationFrame;
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
begin
  DataHolderForm.Width := $1E0;
  DataHolderForm.Height := $106;
  Button1.Width := $68;
  Button1.Height := $19;
  Button1.Left := $F1;
  Button1.Top := 200;
  Button2.Width := Button1.Width;
  Button2.Height := Button1.Height;
  Button2.Left := $16B;
  Button2.Top := Button1.Top;
  Button3.Width := $E2;
  Button3.Height := Button1.Height;
  Button3.Left := Button1.Left;
  Button3.Top := $A8;
  Label1.Width := $1CC;
  Label1.Height := $15;
  Label1.Left := 5;
  Label1.Top := 4;
  Label2.Width := $5A;
  Label2.Height := $15;
  Label2.Left := 5;
  Label2.Top := $24;
  memo1.Width := Label1.Width - Label2.Width;
  memo1.Height := $19;
  memo1.Left := Label2.Left + Label2.Width + 2;
  memo1.Top := Label2.Top - 4;
  DirectoryListBox1.Width := $E2;
  DirectoryListBox1.Height := $89;
  DirectoryListBox1.Left := Label2.Left;
  DirectoryListBox1.Top := $58;
  DriveComboBox1.Width := $E2;
  DriveComboBox1.Height := $14;
  DriveComboBox1.Left := Label2.Left;
  DriveComboBox1.Top := $40;
  FileListBox1.Width := Button3.Width;
  FileListBox1.Height := $61;
  FileListBox1.Left := Button3.Left;
  FileListBox1.Top := DriveComboBox1.Top;
  Label1.Font.Size := $D;
  Label2.Font.Size := $B;
  if MainForm.Small1.Checked = True then
  begin
    Label1.Font.Size := $B;
    Label2.Font.Size := 9;
  end;
  if MainForm.tiny1.Checked = True then
  begin
    Label1.Font.Size := 10;
    Label2.Font.Size := 8;
  end;
  memo1.Font.Size := Label2.Font.Size;
  DirectoryListBox1.Font.Size := Label2.Font.Size;
  DriveComboBox1.Font.Size := Label2.Font.Size;
  FileListBox1.Font.Size := Label2.Font.Size;
  Button1.Font.Size := Label2.Font.Size;
  Button2.Font.Size := Label2.Font.Size;
  Button3.Font.Size := Label2.Font.Size;
  Button1.Visible := True;
  Button2.Visible := True;
  Button3.Visible := True;
  Label1.Visible := True;
  Label2.Visible := True;
  memo1.Visible := True;
  DirectoryListBox1.Visible := True;
  DriveComboBox1.Visible := True;
  FileListBox1.Visible := True;
  Button2.SetFocus;
end;

procedure TForm4.form4onclose(Sender: TObject; var Action: TCloseAction); { $00440A88 }
begin
  DataHolderForm.ModalResult := 1;
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
