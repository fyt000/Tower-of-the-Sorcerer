procedure TTSW10.syokidata0; { $00484F48 }
var
  iVar1, iVar2, uVar11, Row, Column: Longint;
  Path: string;
begin
{$I GraphicsLayout.inc}
  Image1.Visible := False;
  Image2.Visible := False;
  Image3.Visible := False;
  Path := Memo12.Lines[1] + DataDirectory + '\center.bmp';
  Image1.Picture.LoadFromFile(Path);
  if Hero.cycle_factor_minus_one = 0 then
    Path := Memo12.Lines[1] + DataDirectory + '\left.bmp'
  else Path := Memo12.Lines[1] + DataDirectory + '\leftr.bmp';
  Image2.Picture.LoadFromFile(Path);
  if Hero.cycle_factor_minus_one = 0 then
    Path := Memo12.Lines[1] + DataDirectory + '\right.bmp'
  else Path := Memo12.Lines[1] + DataDirectory + '\rightr.bmp';
  Image3.Picture.LoadFromFile(Path);

  MapBitmap1 := TBitmap.Create;
  MapBitmap1.Height := Image6.Height * 11;
  MapBitmap1.Width := Image1.Width + Image2.Width + Image3.Width;
  Path := Memo12.Lines[1] + DataDirectory + '\chtable.oz';
  MapBitmap1.LoadFromFile(Path);
  MapBitmap2 := TBitmap.Create;
  MapBitmap2.Width := Image6.Width;
  MapBitmap2.Height := Image6.Height;
  MapBitmap2.Canvas.CopyMode := $CC0020;
  TargetRect := Rect(0, 0, Image6.Width, Image6.Height);
  ImageList1.Width := Image6.Width;
  ImageList1.Height := Image6.Height;
  for Row := 0 to 19 do
    for Column := 0 to 10 do
      if (Row < 19) or ((Row = 19) and (Column < 9)) then
      begin
        SourceRect := Rect(Image6.Width * Column, Image6.Height * Row,
          (Column + 1) * Image6.Width, (Row + 1) * Image6.Height);
        MapBitmap2.Canvas.CopyRect(TargetRect, MapBitmap1.Canvas, SourceRect);
        ImageList1.Add(MapBitmap2, nil);
      end;

  MapBitmap1.Height := Image6.Height * 11;
  MapBitmap1.Width := Image6.Width * 15;
  Path := Memo12.Lines[1] + DataDirectory + '\chtableb.oz';
  MapBitmap1.LoadFromFile(Path);
  ImageList3.Width := Image6.Width;
  ImageList3.Height := Image6.Height;
  { The original overwrites this global without freeing its previous bitmap. }
  MapBitmap2 := TBitmap.Create;
  MapBitmap2.Width := Image6.Width;
  MapBitmap2.Height := Image6.Height;
  MapBitmap2.Canvas.CopyMode := $CC0020;
  TargetRect := Rect(0, 0, Image6.Width, Image6.Height);
  for Row := 0 to 14 do
    for Column := 0 to 10 do
      if (Row < 14) or ((Row = 14) and (Column < 5)) then
      begin
        SourceRect := Rect(Image6.Width * Column, Image6.Height * Row,
          (Column + 1) * Image6.Width, (Row + 1) * Image6.Height);
        MapBitmap2.Canvas.CopyRect(TargetRect, MapBitmap1.Canvas, SourceRect);
        ImageList3.Add(MapBitmap2, nil);
      end;

  MapBitmap1.Free;
  MapBitmap1 := TBitmap.Create;
  MapBitmap1.Height := Image6.Height;
  MapBitmap1.Width := Image6.Width;
  Path := Memo12.Lines[1] + DataDirectory + '\key.oz';
  MapBitmap1.LoadFromFile(Path);
  ImageList2.Width := Image6.Width div 2;
  ImageList2.Height := Image6.Height div 2;
  MapBitmap2.Width := Image6.Width div 2;
  MapBitmap2.Height := Image6.Height div 2;
  MapBitmap2.Canvas.CopyMode := $CC0020;
  TargetRect := Rect(0, 0, MapBitmap2.Width, MapBitmap2.Height);
  for Row := 0 to 1 do
    for Column := 0 to 1 do
    begin
      SourceRect := Rect(MapBitmap2.Width * Column, MapBitmap2.Height * Row,
        (Column + 1) * MapBitmap2.Width, (Row + 1) * MapBitmap2.Height);
      MapBitmap2.Canvas.CopyRect(TargetRect, MapBitmap1.Canvas, SourceRect);
      ImageList2.Add(MapBitmap2, nil);
    end;

  MapBitmap1.Height := Image6.Height * 11;
  MapBitmap1.Width := Image6.Width * 11;
  MapBitmap2.Height := MapBitmap1.Height;
  MapBitmap2.Width := MapBitmap1.Width;
  WorkBitmap1 := TBitmap.Create;
  WorkBitmap1.Height := Image6.Height * 5;
  WorkBitmap1.Width := Image6.Width * 3;
  WorkBitmap2 := TBitmap.Create;
  WorkBitmap2.Height := Image6.Height * 2;
  WorkBitmap2.Width := Image6.Width * 3;
  WorkBitmap3 := TBitmap.Create;
  WorkBitmap3.Height := Image6.Height;
  WorkBitmap3.Width := Image6.Width;
  FrameBitmap := TBitmap.Create;
  FrameBitmap.Width := Image1.Width + Image2.Width + Image3.Width;
  FrameBitmap.Height := Image1.Height;
{$I GraphicsHints.inc}
  Memo11.Font.Color := $FFFFFF;
  DrawFlag1 := 0;
  DrawFlag2 := 0;
end;

procedure TTSW10.mhyouji; { $00442C38 }
var
  I, Cell, Tile: Longint;
begin
  Hero.Word664 := 0;
  for I := 1 to 121 do
  begin
    DrawIndex := I;
    Cell := RenderOrder[DrawIndex - 1];
    DrawX := (Cell * Image6.Width) mod (Image6.Width * 11);
    DrawY := ((Cell * Image6.Height) div (Image6.Height * 11)) * Image6.Height;
    Tile := Maps[Hero.floor, Cell + 2] - 1;
    ImageList1.Draw(MapBitmap1.Canvas, DrawX, DrawY, Tile);
    GraphicTile := Maps[Hero.floor, RenderOrder[DrawIndex - 1] + 2];
    imagework;
    Tile := Maps[Hero.floor, RenderOrder[DrawIndex - 1] + 2] - 1 + DoorOpened;
    ImageList1.Draw(MapBitmap2.Canvas, DrawX, DrawY, Tile);
  end;
end;

procedure TTSW10.yusyahyouji; { $00443648 }
begin
  TargetRect := Rect(0, 0, Image6.Width, Image6.Height);
  WorkBitmap1.Free;
  WorkBitmap2.Free;
  WorkBitmap3.Free;
  WorkBitmap1 := TBitmap.Create;
  WorkBitmap2 := TBitmap.Create;
  WorkBitmap3 := TBitmap.Create;
  WorkBitmap1.Height := Image6.Height;
  WorkBitmap1.Width := Image6.Width;
  WorkBitmap2.Height := WorkBitmap1.Height;
  WorkBitmap2.Width := WorkBitmap1.Width;
  WorkBitmap3.Height := WorkBitmap1.Height;
  WorkBitmap3.Width := WorkBitmap1.Width;
  WorkBitmap1.Canvas.CopyMode := $CC0020;
  WorkBitmap2.Canvas.CopyMode := $CC0020;
  WorkBitmap3.Canvas.CopyMode := $CC0020;
  ImageList1.Draw(WorkBitmap1.Canvas, 0, 0, Maps[Hero.floor, Hero.y * 11 + Hero.x + 2] - 1);
  ImageList1.Draw(WorkBitmap2.Canvas, 0, 0, ScratchIndex - $42);
  ImageList1.Draw(WorkBitmap3.Canvas, 0, 0, ScratchIndex - $41);
  SourceRect := TargetRect;
  kasanegaki;
end;

procedure TTSW10.kasanegaki; { $0044439C }
begin ComposeSprite; end;

procedure TTSW10.yusyahyouji1; { $004433A4 }
var
  FirstFrame, SecondFrame: Longint;
begin
  case Hero.Word352 of
    1: begin FirstFrame := $FA; SecondFrame := $FC; end;
    2: begin FirstFrame := $102; SecondFrame := $104; end;
    3: begin FirstFrame := $10A; SecondFrame := $10C; end;
    4: begin FirstFrame := $112; SecondFrame := $114; end;
  else Exit;
  end;
  NeighborIndex := Image6.Width * Hero.x;
  NeighborY := Image6.Height * Hero.y;
  ScratchIndex := FirstFrame;
  DoorOpened := 1;
  yusyahyouji;
  MapBitmap2.Canvas.Draw(NeighborIndex, NeighborY, WorkBitmap1);
  ScratchIndex := SecondFrame;
  DoorOpened := 0;
  yusyahyouji;
  MapBitmap1.Canvas.Draw(NeighborIndex, NeighborY, WorkBitmap1);
end;
