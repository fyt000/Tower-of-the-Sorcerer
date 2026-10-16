{ Commands execute newest first. For masks, doors and raster scenes, the
  preceding wait record supplies the animation operands. }

procedure PushEvent(Opcode, A, B: Longint);
begin
  if (EventCursor < 0) or (EventCursor >= High(EventStack)) then
    raise Exception.Create('Event stack is full');
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Word(Opcode);
  EventStack[EventCursor].A := Word(A);
  EventStack[EventCursor].B := Word(B);
end;

procedure EventWaits(Count: Longint);
var
  I: Longint;
begin
  for I := 1 to Count do
    PushEvent(0, 0, 0);
end;

procedure EventSummon(Form: TTSW10; Index, Color: Longint);
var
  Mask: Longint;
begin
  { Descending masks play in ascending order because the stack runs backwards. }
  Form.timer2on;
  for Mask := 182 downto 166 do
  begin
    PushEvent(0, 6, Color);
    PushEvent(9, Index, Mask);
  end;
  PushEvent(0, 0, 0);
  PushEvent(1, 7, 0);
end;

procedure EventSummonFour(Form: TTSW10; North, South, West, East: Longint);
{ Temporary guards for the 3F capture and 42F Zeno scenes. }
const
  Masks: array[0..4] of Longint = (182, 175, 171, 169, 167);
var
  I, J: Longint;
  Cells: array[0..3] of Longint;
begin
  Form.timer2on;
  Cells[0] := East;
  Cells[1] := West;
  Cells[2] := South;
  Cells[3] := North;
  for I := 0 to 4 do
    for J := 0 to 3 do
    begin
      PushEvent(0, 6, 93);
      PushEvent(9, Cells[J], Masks[I]);
    end;
  PushEvent(0, 0, 0);
  PushEvent(1, 7, 0);
end;

procedure EventTile(Form: TTSW10; Index, Tile: Longint);
var
  Offset, Frame: Longint;
begin
  if (Index < 0) or (Index > 120) then
    Exit;
  DrawX := (Index mod BoardWidth) * Form.Image6.Width;
  DrawY := (Index div BoardWidth) * Form.Image6.Height;
  Form.ImageList1.Draw(MapBitmap1.Canvas, DrawX, DrawY, Tile - 1);
  GraphicTile := Tile;
  Form.imagework;
  Offset := DoorOpened;
  Frame := Tile - 1 + Offset;
  Form.ImageList1.Draw(MapBitmap2.Canvas, DrawX, DrawY, Frame);
end;

procedure EventOverlay(Form: TTSW10; Index, Mask, Underlying, Color: Longint);
var
  Frame, Offset: Longint;
begin
  if (Index < 0) or (Index > 120) then
    Exit;
  WorkBitmap1.Width := Form.Image6.Width;
  WorkBitmap1.Height := Form.Image6.Height;
  WorkBitmap2.Width := WorkBitmap1.Width;
  WorkBitmap2.Height := WorkBitmap1.Height;
  WorkBitmap3.Width := WorkBitmap1.Width;
  WorkBitmap3.Height := WorkBitmap1.Height;
  SourceRect := Rect(0, 0, WorkBitmap1.Width, WorkBitmap1.Height);
  TargetRect := SourceRect;
  for Frame := 0 to 1 do
  begin
    Offset := 0;
    if Frame = 1 then
    begin
      GraphicTile := Underlying;
      Form.imagework;
      Offset := DoorOpened;
    end;
    Form.ImageList1.Draw(WorkBitmap1.Canvas, 0, 0, Underlying - 1 + Offset);
    Offset := 0;
    if Frame = 1 then
    begin
      GraphicTile := Color;
      Form.imagework;
      Offset := DoorOpened;
    end;
    Form.ImageList1.Draw(WorkBitmap2.Canvas, 0, 0, Color - 1 + Offset);
    Form.ImageList1.Draw(WorkBitmap3.Canvas, 0, 0, Mask - 1);
    ComposeSprite;
    DrawX := (Index mod BoardWidth) * Form.Image6.Width;
    DrawY := (Index div BoardWidth) * Form.Image6.Height;
    if Frame = 0 then
      MapBitmap1.Canvas.Draw(DrawX, DrawY, WorkBitmap1)
    else
      MapBitmap2.Canvas.Draw(DrawX, DrawY, WorkBitmap1);
  end;
  Form.Canvas.Draw(UiSpan, UiStep, MapBitmap1);
end;

procedure EventHidePanels(Form: TTSW10);
var
  I: Longint;
  Component: TComponent;
begin
  for I := 0 to Form.ComponentCount - 1 do
  begin
    Component := Form.Components[I];
    if Component is TControl then
      if (Component is TMemo)
          or (Component is TImage)
          or (Component is TButton)
          or (Component is TBitBtn) then
        TControl(Component).Visible := False;
  end;
end;

procedure TTSW10.zenolivework; { Materialize Zeno. $00461A0C }
begin
  TargetRect := Rect(0, 0, Image6.Width, Image6.Height);
  WorkBitmap1.Width := Image6.Width;
  WorkBitmap1.Height := Image6.Height;
  WorkBitmap2.Width := WorkBitmap1.Width;
  WorkBitmap2.Height := WorkBitmap1.Height;
  WorkBitmap3.Width := WorkBitmap1.Width;
  WorkBitmap3.Height := WorkBitmap1.Height;
  timer2on;
  { PushCommand(0, 6, 91) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 91;
  { PushCommand(9, Word(ScratchIndex), 182) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := Word(ScratchIndex);
  EventStack[EventCursor].B := 182;
  { PushCommand(0, 6, 91) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 91;
  { PushCommand(9, Word(ScratchIndex), 181) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := Word(ScratchIndex);
  EventStack[EventCursor].B := 181;
  { PushCommand(0, 6, 91) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 91;
  { PushCommand(9, Word(ScratchIndex), 180) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := Word(ScratchIndex);
  EventStack[EventCursor].B := 180;
  { PushCommand(0, 6, 91) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 91;
  { PushCommand(9, Word(ScratchIndex), 179) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := Word(ScratchIndex);
  EventStack[EventCursor].B := 179;
  { PushCommand(0, 6, 91) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 91;
  { PushCommand(9, Word(ScratchIndex), 178) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := Word(ScratchIndex);
  EventStack[EventCursor].B := 178;
  { PushCommand(0, 6, 91) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 91;
  { PushCommand(9, Word(ScratchIndex), 177) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := Word(ScratchIndex);
  EventStack[EventCursor].B := 177;
  { PushCommand(0, 6, 91) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 91;
  { PushCommand(9, Word(ScratchIndex), 176) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := Word(ScratchIndex);
  EventStack[EventCursor].B := 176;
  { PushCommand(0, 6, 91) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 91;
  { PushCommand(9, Word(ScratchIndex), 175) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := Word(ScratchIndex);
  EventStack[EventCursor].B := 175;
  { PushCommand(0, 6, 91) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 91;
  { PushCommand(9, Word(ScratchIndex), 174) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := Word(ScratchIndex);
  EventStack[EventCursor].B := 174;
  { PushCommand(0, 6, 91) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 91;
  { PushCommand(9, Word(ScratchIndex), 173) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := Word(ScratchIndex);
  EventStack[EventCursor].B := 173;
  { PushCommand(0, 6, 91) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 91;
  { PushCommand(9, Word(ScratchIndex), 172) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := Word(ScratchIndex);
  EventStack[EventCursor].B := 172;
  { PushCommand(0, 6, 91) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 91;
  { PushCommand(9, Word(ScratchIndex), 171) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := Word(ScratchIndex);
  EventStack[EventCursor].B := 171;
  { PushCommand(0, 6, 91) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 91;
  { PushCommand(9, Word(ScratchIndex), 170) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := Word(ScratchIndex);
  EventStack[EventCursor].B := 170;
  { PushCommand(0, 6, 91) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 91;
  { PushCommand(9, Word(ScratchIndex), 169) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := Word(ScratchIndex);
  EventStack[EventCursor].B := 169;
  { PushCommand(0, 6, 91) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 91;
  { PushCommand(9, Word(ScratchIndex), 168) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := Word(ScratchIndex);
  EventStack[EventCursor].B := 168;
  { PushCommand(0, 6, 91) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 91;
  { PushCommand(9, Word(ScratchIndex), 167) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := Word(ScratchIndex);
  EventStack[EventCursor].B := 167;
  { PushCommand(0, 6, 91) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 91;
  { PushCommand(9, Word(ScratchIndex), 166) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := Word(ScratchIndex);
  EventStack[EventCursor].B := 166;
  { PushCommand(0, 0, 0) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(1, 7, 0) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSound);
  EventStack[EventCursor].A := 7;
  EventStack[EventCursor].B := 0;
end;

procedure TTSW10.madoushilivework; { Materialize four temporary guards. $00461EF4 }
begin
  TargetRect := Rect(0, 0, Image6.Width, Image6.Height);
  WorkBitmap1.Width := Image6.Width;
  WorkBitmap1.Height := Image6.Height;
  WorkBitmap2.Width := WorkBitmap1.Width;
  WorkBitmap2.Height := WorkBitmap1.Height;
  WorkBitmap3.Width := WorkBitmap1.Width;
  WorkBitmap3.Height := WorkBitmap1.Height;
  timer2on;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, Word(DamageMode), 182) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := Word(DamageMode);
  EventStack[EventCursor].B := 182;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, Word(NeighborY), 182) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := Word(NeighborY);
  EventStack[EventCursor].B := 182;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, Word(NeighborIndex), 182) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := Word(NeighborIndex);
  EventStack[EventCursor].B := 182;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, Word(ScratchIndex), 182) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := Word(ScratchIndex);
  EventStack[EventCursor].B := 182;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, Word(DamageMode), 175) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := Word(DamageMode);
  EventStack[EventCursor].B := 175;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, Word(NeighborY), 175) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := Word(NeighborY);
  EventStack[EventCursor].B := 175;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, Word(NeighborIndex), 175) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := Word(NeighborIndex);
  EventStack[EventCursor].B := 175;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, Word(ScratchIndex), 175) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := Word(ScratchIndex);
  EventStack[EventCursor].B := 175;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, Word(DamageMode), 171) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := Word(DamageMode);
  EventStack[EventCursor].B := 171;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, Word(NeighborY), 171) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := Word(NeighborY);
  EventStack[EventCursor].B := 171;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, Word(NeighborIndex), 171) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := Word(NeighborIndex);
  EventStack[EventCursor].B := 171;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, Word(ScratchIndex), 171) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := Word(ScratchIndex);
  EventStack[EventCursor].B := 171;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, Word(DamageMode), 169) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := Word(DamageMode);
  EventStack[EventCursor].B := 169;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, Word(NeighborY), 169) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := Word(NeighborY);
  EventStack[EventCursor].B := 169;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, Word(NeighborIndex), 169) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := Word(NeighborIndex);
  EventStack[EventCursor].B := 169;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, Word(ScratchIndex), 169) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := Word(ScratchIndex);
  EventStack[EventCursor].B := 169;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, Word(DamageMode), 167) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := Word(DamageMode);
  EventStack[EventCursor].B := 167;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, Word(NeighborY), 167) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := Word(NeighborY);
  EventStack[EventCursor].B := 167;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, Word(NeighborIndex), 167) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := Word(NeighborIndex);
  EventStack[EventCursor].B := 167;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, Word(ScratchIndex), 167) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := Word(ScratchIndex);
  EventStack[EventCursor].B := 167;
  { PushCommand(0, 0, 0) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(1, 7, 0) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSound);
  EventStack[EventCursor].A := 7;
  EventStack[EventCursor].B := 0;
end;

procedure TTSW10.madoushi2; { Materialize the eight 49F sorcerer guards. $00462560 }
begin
  Maps[Hero.floor, 17] := tileSorcerer;
  Maps[Hero.floor, 18] := tileSorcerer;
  Maps[Hero.floor, 19] := tileSorcerer;
  Maps[Hero.floor, 30] := tileSorcerer;
  Maps[Hero.floor, 41] := tileSorcerer;
  Maps[Hero.floor, 40] := tileSorcerer;
  Maps[Hero.floor, 39] := tileSorcerer;
  Maps[Hero.floor, 28] := tileSorcerer;
  TargetRect := Rect(0, 0, Image6.Width, Image6.Height);
  WorkBitmap1.Width := Image6.Width;
  WorkBitmap1.Height := Image6.Height;
  WorkBitmap2.Width := WorkBitmap1.Width;
  WorkBitmap2.Height := WorkBitmap1.Height;
  WorkBitmap3.Width := WorkBitmap1.Width;
  WorkBitmap3.Height := WorkBitmap1.Height;
  timer2on;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 26, 182) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 26;
  EventStack[EventCursor].B := 182;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 37, 182) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 37;
  EventStack[EventCursor].B := 182;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 38, 182) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 38;
  EventStack[EventCursor].B := 182;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 39, 182) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 39;
  EventStack[EventCursor].B := 182;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 28, 182) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 28;
  EventStack[EventCursor].B := 182;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 17, 182) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 17;
  EventStack[EventCursor].B := 182;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 16, 182) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 16;
  EventStack[EventCursor].B := 182;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 15, 182) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 15;
  EventStack[EventCursor].B := 182;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 26, 179) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 26;
  EventStack[EventCursor].B := 179;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 37, 179) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 37;
  EventStack[EventCursor].B := 179;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 38, 179) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 38;
  EventStack[EventCursor].B := 179;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 39, 179) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 39;
  EventStack[EventCursor].B := 179;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 28, 179) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 28;
  EventStack[EventCursor].B := 179;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 17, 179) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 17;
  EventStack[EventCursor].B := 179;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 16, 179) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 16;
  EventStack[EventCursor].B := 179;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 15, 179) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 15;
  EventStack[EventCursor].B := 179;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 26, 177) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 26;
  EventStack[EventCursor].B := 177;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 37, 177) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 37;
  EventStack[EventCursor].B := 177;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 38, 177) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 38;
  EventStack[EventCursor].B := 177;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 39, 177) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 39;
  EventStack[EventCursor].B := 177;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 28, 177) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 28;
  EventStack[EventCursor].B := 177;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 17, 177) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 17;
  EventStack[EventCursor].B := 177;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 16, 177) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 16;
  EventStack[EventCursor].B := 177;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 15, 177) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 15;
  EventStack[EventCursor].B := 177;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 26, 175) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 26;
  EventStack[EventCursor].B := 175;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 37, 175) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 37;
  EventStack[EventCursor].B := 175;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 38, 175) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 38;
  EventStack[EventCursor].B := 175;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 39, 175) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 39;
  EventStack[EventCursor].B := 175;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 28, 175) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 28;
  EventStack[EventCursor].B := 175;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 17, 175) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 17;
  EventStack[EventCursor].B := 175;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 16, 175) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 16;
  EventStack[EventCursor].B := 175;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 15, 175) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 15;
  EventStack[EventCursor].B := 175;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 26, 173) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 26;
  EventStack[EventCursor].B := 173;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 37, 173) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 37;
  EventStack[EventCursor].B := 173;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 38, 173) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 38;
  EventStack[EventCursor].B := 173;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 39, 173) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 39;
  EventStack[EventCursor].B := 173;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 28, 173) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 28;
  EventStack[EventCursor].B := 173;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 17, 173) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 17;
  EventStack[EventCursor].B := 173;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 16, 173) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 16;
  EventStack[EventCursor].B := 173;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 15, 173) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 15;
  EventStack[EventCursor].B := 173;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 26, 171) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 26;
  EventStack[EventCursor].B := 171;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 37, 171) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 37;
  EventStack[EventCursor].B := 171;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 38, 171) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 38;
  EventStack[EventCursor].B := 171;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 39, 171) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 39;
  EventStack[EventCursor].B := 171;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 28, 171) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 28;
  EventStack[EventCursor].B := 171;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 17, 171) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 17;
  EventStack[EventCursor].B := 171;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 16, 171) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 16;
  EventStack[EventCursor].B := 171;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 15, 171) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 15;
  EventStack[EventCursor].B := 171;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 26, 169) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 26;
  EventStack[EventCursor].B := 169;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 37, 169) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 37;
  EventStack[EventCursor].B := 169;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 38, 169) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 38;
  EventStack[EventCursor].B := 169;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 39, 169) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 39;
  EventStack[EventCursor].B := 169;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 28, 169) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 28;
  EventStack[EventCursor].B := 169;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 17, 169) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 17;
  EventStack[EventCursor].B := 169;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 16, 169) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 16;
  EventStack[EventCursor].B := 169;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 15, 169) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 15;
  EventStack[EventCursor].B := 169;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 26, 167) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 26;
  EventStack[EventCursor].B := 167;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 37, 167) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 37;
  EventStack[EventCursor].B := 167;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 38, 167) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 38;
  EventStack[EventCursor].B := 167;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 39, 167) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 39;
  EventStack[EventCursor].B := 167;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 28, 167) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 28;
  EventStack[EventCursor].B := 167;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 17, 167) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 17;
  EventStack[EventCursor].B := 167;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 16, 167) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 16;
  EventStack[EventCursor].B := 167;
  { PushCommand(0, 6, 93) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  EventStack[EventCursor].B := 93;
  { PushCommand(9, 15, 167) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 15;
  EventStack[EventCursor].B := 167;
  { Original $004637DD increments the cursor without writing a command.
    Omit that stale record: its previous contents can crash the 49F summon. }
end;

{$I EventScenes.inc}

procedure TTSW10.mevent; { Dispatch scenes triggered by special road tiles. $0046397C }
begin
  itemdel;
  case Hero.floor of
    3:
    begin
      idou;
      timer2on;
      Maps[Hero.floor, Hero.y * BoardWidth + Hero.x + MapTileOffset] := tileRoad;
      Button1.Caption := ListBox2.Items[218];
      { PushCommand(10, 10, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evDialogue);
      EventStack[EventCursor].A := speechZenoCaptureChallenge;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      ScratchIndex := 70;
      zenolivework;
      if Hero.music_track <> 0 then
      begin
        { PushCommand(0, 0, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 6, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 6;
        EventStack[EventCursor].B := 0;
      end;
    end;
    10:
    begin
      idou;
      Maps[Hero.floor, Hero.y * BoardWidth + Hero.x + MapTileOffset] := tileRoad;
      ichicheck;
    end;
    15:
    begin
      idou;
      Maps[Hero.floor, Hero.y * BoardWidth + Hero.x + MapTileOffset] := tileRoad;
      ichicheck;
    end;
    20:
    begin
      idou;
      if Hero.y * BoardWidth + Hero.x = 82 then
      begin
        Maps[Hero.floor, Hero.y * BoardWidth + Hero.x + MapTileOffset] := tileRoad;
        if Hero.music_track <> 0 then
        begin
          MediaPlayer5.Close;
          Hero.music_track := 16;
          soundplay;
        end;
        ichicheck;
      end;
    end;
    23:
    begin
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(2, 114, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evRefreshStatus);
      EventStack[EventCursor].A := 114;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(6, ContactIndex, 8). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSetTile);
      EventStack[EventCursor].A := ContactIndex;
      EventStack[EventCursor].B := tileWall;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 1, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 1;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      timer2on;
    end;
    24:
    begin
      idou;
      Maps[Hero.floor, Hero.y * BoardWidth + Hero.x + MapTileOffset] := tileRoad;
      ichicheck;
    end;
    25:
    begin
      idou;
      Maps[Hero.floor, Hero.y * BoardWidth + Hero.x + MapTileOffset] := tileRoad;
      if Hero.music_track <> 0 then
      begin
        MediaPlayer5.Close;
        Hero.music_track := 7;
        soundplay;
      end;
      ichicheck;
    end;
    30:
    begin
      idou;
      Maps[Hero.floor, Hero.y * BoardWidth + Hero.x + MapTileOffset] := tileRoad;
      ichicheck;
    end;
    32:
    begin
      ichicheck;
    end;
    33:
    begin
      idou;
      Maps[Hero.floor, Hero.y * BoardWidth + Hero.x + MapTileOffset] := tileRoad;
      ichicheck;
    end;
    38:
    begin
      idou;
      Maps[Hero.floor, Hero.y * BoardWidth + Hero.x + MapTileOffset] := tileRoad;
      ichicheck;
    end;
    40:
    begin
      idou;
      Maps[Hero.floor, Hero.y * BoardWidth + Hero.x + MapTileOffset] := tileRoad;
      if Hero.music_track <> 0 then
      begin
        MediaPlayer5.Close;
        Hero.music_track := 18;
        soundplay;
      end;
      ichicheck;
    end;
    42:
    begin
      ichicheck;
    end;
    43:
    begin
      idou;
      Maps[Hero.floor, Hero.y * BoardWidth + Hero.x + MapTileOffset] := tileRoad;
      ichicheck;
    end;
    48:
    begin
      ichicheck;
    end;
    49:
    begin
      idou;
      Maps[Hero.floor, Hero.y * BoardWidth + Hero.x + MapTileOffset] := tileRoad;
      if Hero.music_track <> 0 then
      begin
        MediaPlayer5.Close;
        Hero.music_track := 19;
        soundplay;
      end;
      ichicheck;
    end;
  end;
end;

procedure TTSW10.toroad2; { Dissolve a bomb target into road. $0044BC34 }
begin
  timer2on;
  { PushCommand(17, Word(ContactIndex), 6) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSetTileOnly);
  EventStack[EventCursor].A := Word(ContactIndex);
  EventStack[EventCursor].B := tileRoad;
  { PushCommand(0, Maps[Hero.floor, ContactIndex + 2], 6) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := Maps[Hero.floor, ContactIndex + MapTileOffset];
  EventStack[EventCursor].B := 6;
  { PushCommand(9, Word(ContactIndex), 182) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := Word(ContactIndex);
  EventStack[EventCursor].B := 182;
  { PushCommand(0, 0, 0) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(1, 1, 0) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSound);
  EventStack[EventCursor].A := 1;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, Maps[Hero.floor, ContactIndex + 2], 6) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := Maps[Hero.floor, ContactIndex + MapTileOffset];
  EventStack[EventCursor].B := 6;
  { PushCommand(9, Word(ContactIndex), 178) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := Word(ContactIndex);
  EventStack[EventCursor].B := 178;
  { PushCommand(0, 0, 0) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(1, 1, 0) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSound);
  EventStack[EventCursor].A := 1;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, Maps[Hero.floor, ContactIndex + 2], 6) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := Maps[Hero.floor, ContactIndex + MapTileOffset];
  EventStack[EventCursor].B := 6;
  { PushCommand(9, Word(ContactIndex), 174) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := Word(ContactIndex);
  EventStack[EventCursor].B := 174;
  { PushCommand(0, 0, 0) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(1, 1, 0) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSound);
  EventStack[EventCursor].A := 1;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, Maps[Hero.floor, ContactIndex + 2], 6) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := Maps[Hero.floor, ContactIndex + MapTileOffset];
  EventStack[EventCursor].B := 6;
  { PushCommand(9, Word(ContactIndex), 170) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := Word(ContactIndex);
  EventStack[EventCursor].B := 170;
  { PushCommand(0, 0, 0) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(1, 1, 0) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSound);
  EventStack[EventCursor].A := 1;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, Maps[Hero.floor, ContactIndex + 2], 6) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := Maps[Hero.floor, ContactIndex + MapTileOffset];
  EventStack[EventCursor].B := 6;
  { PushCommand(9, Word(ContactIndex), 166) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := Word(ContactIndex);
  EventStack[EventCursor].B := 166;
  { PushCommand(0, 0, 0) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(1, 1, 0) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSound);
  EventStack[EventCursor].A := 1;
  EventStack[EventCursor].B := 0;
end;

procedure TTSW10.openning31; { End capture in the 2F prison and reset equipment. $004653B8 }
begin
  if Hero.music_track <> 0 then
    MediaPlayer5.Close;
  Image1.Picture.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\center.bmp');
  if Hero.cycle_factor_minus_one = 0 then
    Image2.Picture.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\left.bmp')
  else
    Image2.Picture.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\leftr.bmp');
  if Hero.cycle_factor_minus_one = 0 then
    Image3.Picture.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\right.bmp')
  else
    Image3.Picture.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\rightr.bmp');
  Image1.Visible := True;
  Image2.Visible := True;
  Image3.Visible := True;
  Button1.Caption := 'OK';
  { Capture resets position/equipment; later cycles retain combat stats. }
  if Hero.cycle_factor_minus_one = 0 then
  begin
    Hero.floor := 2;
    Hero.highest_floor := 2;
    Hero.x := 2;
    Hero.y := 7;
    Hero.hp := 400;
    Hero.attack := 10;
    Hero.defense := 10;
    Hero.Word48 := 1;
    Hero.sword := Ord(equipmentNone);
    Hero.shield := Ord(equipmentNone);
    Hero.Word144 := 0;
    Hero.sacred_shield := 0;
  end
  else
  begin
    Hero.floor := 2;
    Hero.highest_floor := 2;
    Hero.x := 2;
    Hero.y := 7;
    Hero.Word48 := 1;
    Hero.sword := Ord(equipmentNone);
    Hero.shield := Ord(equipmentNone);
    Hero.hero_orb := 0;
    Hero.wisdom_orb := 0;
    Hero.flight_orb := 0;
    Hero.cross := 0;
    Hero.elixir := 0;
    Hero.mattock := 0;
    Hero.bomb := 0;
    Hero.warp_staff := 0;
    Hero.ascent_wing := 0;
    Hero.descent_wing := 0;
    Hero.dragon_slayer := 0;
    Hero.snow_crystal := 0;
    Hero.magic_key := 0;
    Hero.super_mattock := 0;
    Hero.lucky_gold := 0;
    Hero.Word144 := 0;
    Hero.sacred_shield := 0;
  end;
  timer2on;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(11, 8, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSceneAction);
  EventStack[EventCursor].A := 8;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(10, 3, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evDialogue);
  EventStack[EventCursor].A := speechThiefWakesHero;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(10, 2, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evDialogue);
  EventStack[EventCursor].A := speechThiefCallsHero;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(10, 1, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evDialogue);
  EventStack[EventCursor].A := speechUnconscious;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(10, 1, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evDialogue);
  EventStack[EventCursor].A := speechUnconscious;
  EventStack[EventCursor].B := 0;
  { PushCommand(8, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evShowPanels);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(2, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evRefreshStatus);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  disp;
  Timer1.Enabled := False;
end;

procedure TTSW10.openning2; { Queue the capture presentation in reverse playback order. $00464048 }
var
  I, Groups: Longint;
begin
  timer2on;
  Button1.Caption := ListBox2.Items[219];
  { PushCommand(11, 1, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSceneAction);
  EventStack[EventCursor].A := 1;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 1, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 1;
  EventStack[EventCursor].B := 0;
  { PushCommand(11, 12, display height). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSceneAction);
  EventStack[EventCursor].A := 12;
  case Image6.Width of
    32:
    begin
      EventStack[EventCursor].B := 400;
      Groups := 40;
    end;
    40:
    begin
      EventStack[EventCursor].B := 500;
      Groups := 50;
    end;
  end;
  { Six raster steps per group, played in reverse queue order. }
  for I := Groups downto 0 do
  begin
    { PushCommand(0, 1, 0). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evWait);
    EventStack[EventCursor].A := 1;
    EventStack[EventCursor].B := 0;
    { PushCommand(11, 12, I * 6 + 100 + 5). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evSceneAction);
    EventStack[EventCursor].A := 12;
    EventStack[EventCursor].B := I * 6 + 100 + 5;
    { PushCommand(0, 1, 0). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evWait);
    EventStack[EventCursor].A := 1;
    EventStack[EventCursor].B := 0;
    { PushCommand(11, 12, I * 6 + 100 + 4). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evSceneAction);
    EventStack[EventCursor].A := 12;
    EventStack[EventCursor].B := I * 6 + 100 + 4;
    { PushCommand(0, 1, 0). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evWait);
    EventStack[EventCursor].A := 1;
    EventStack[EventCursor].B := 0;
    { PushCommand(11, 12, I * 6 + 100 + 3). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evSceneAction);
    EventStack[EventCursor].A := 12;
    EventStack[EventCursor].B := I * 6 + 100 + 3;
    { PushCommand(0, 1, 0). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evWait);
    EventStack[EventCursor].A := 1;
    EventStack[EventCursor].B := 0;
    { PushCommand(11, 12, I * 6 + 100 + 2). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evSceneAction);
    EventStack[EventCursor].A := 12;
    EventStack[EventCursor].B := I * 6 + 100 + 2;
    { PushCommand(0, 1, 0). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evWait);
    EventStack[EventCursor].A := 1;
    EventStack[EventCursor].B := 0;
    { PushCommand(11, 12, I * 6 + 100 + 1). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evSceneAction);
    EventStack[EventCursor].A := 12;
    EventStack[EventCursor].B := I * 6 + 100 + 1;
    { PushCommand(0, 1, 0). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evWait);
    EventStack[EventCursor].A := 1;
    EventStack[EventCursor].B := 0;
    { PushCommand(11, 12, I * 6 + 100 + 0). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evSceneAction);
    EventStack[EventCursor].A := 12;
    EventStack[EventCursor].B := I * 6 + 100 + 0;
  end;
  { PushCommand(0, 1, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 1;
  EventStack[EventCursor].B := 0;
  { PushCommand(11, 12, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSceneAction);
  EventStack[EventCursor].A := 12;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { Capture flash frames and sound pulses. }
  { PushCommand(11, 12, 247). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSceneAction);
  EventStack[EventCursor].A := 12;
  EventStack[EventCursor].B := 247;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(1, 4, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSound);
  EventStack[EventCursor].A := 4;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(11, 12, 246). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSceneAction);
  EventStack[EventCursor].A := 12;
  EventStack[EventCursor].B := 246;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(1, 4, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSound);
  EventStack[EventCursor].A := 4;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(11, 12, 245). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSceneAction);
  EventStack[EventCursor].A := 12;
  EventStack[EventCursor].B := 245;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(1, 4, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSound);
  EventStack[EventCursor].A := 4;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(11, 12, 244). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSceneAction);
  EventStack[EventCursor].A := 12;
  EventStack[EventCursor].B := 244;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(1, 4, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSound);
  EventStack[EventCursor].A := 4;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(11, 12, 243). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSceneAction);
  EventStack[EventCursor].A := 12;
  EventStack[EventCursor].B := 243;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(1, 4, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSound);
  EventStack[EventCursor].A := 4;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(11, 12, 242). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSceneAction);
  EventStack[EventCursor].A := 12;
  EventStack[EventCursor].B := 242;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(1, 4, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSound);
  EventStack[EventCursor].A := 4;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(11, 12, 241). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSceneAction);
  EventStack[EventCursor].A := 12;
  EventStack[EventCursor].B := 241;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(1, 4, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSound);
  EventStack[EventCursor].A := 4;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(11, 12, 240). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSceneAction);
  EventStack[EventCursor].A := 12;
  EventStack[EventCursor].B := 240;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(1, 4, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSound);
  EventStack[EventCursor].A := 4;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(11, 12, 239). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSceneAction);
  EventStack[EventCursor].A := 12;
  EventStack[EventCursor].B := 239;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(1, 4, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSound);
  EventStack[EventCursor].A := 4;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(11, 12, 238). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSceneAction);
  EventStack[EventCursor].A := 12;
  EventStack[EventCursor].B := 238;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(1, 4, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSound);
  EventStack[EventCursor].A := 4;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(11, 12, 237). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSceneAction);
  EventStack[EventCursor].A := 12;
  EventStack[EventCursor].B := 237;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(1, 4, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSound);
  EventStack[EventCursor].A := 4;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(11, 12, 236). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSceneAction);
  EventStack[EventCursor].A := 12;
  EventStack[EventCursor].B := 236;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(1, 4, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSound);
  EventStack[EventCursor].A := 4;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(11, 12, 235). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSceneAction);
  EventStack[EventCursor].A := 12;
  EventStack[EventCursor].B := 235;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(1, 4, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSound);
  EventStack[EventCursor].A := 4;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(11, 12, 234). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSceneAction);
  EventStack[EventCursor].A := 12;
  EventStack[EventCursor].B := 234;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(1, 4, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSound);
  EventStack[EventCursor].A := 4;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(11, 12, 233). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSceneAction);
  EventStack[EventCursor].A := 12;
  EventStack[EventCursor].B := 233;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(1, 4, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSound);
  EventStack[EventCursor].A := 4;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(11, 12, 232). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSceneAction);
  EventStack[EventCursor].A := 12;
  EventStack[EventCursor].B := 232;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(1, 4, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSound);
  EventStack[EventCursor].A := 4;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(11, 14, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSceneAction);
  EventStack[EventCursor].A := 14;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(11, 7, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSceneAction);
  EventStack[EventCursor].A := 7;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(8, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evShowPanels);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(6, 92, 6). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSetTile);
  EventStack[EventCursor].A := 92;
  EventStack[EventCursor].B := tileRoad;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 6, facing damage frame). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  case Hero.facing of
    Ord(hfDown): EventStack[EventCursor].B := 191;
    Ord(hfLeft): EventStack[EventCursor].B := 199;
    Ord(hfRight): EventStack[EventCursor].B := 207;
    Ord(hfUp): EventStack[EventCursor].B := 215;
  end;
  { PushCommand(9, 92, facing damage frame). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := 92;
  case Hero.facing of
    Ord(hfDown): EventStack[EventCursor].B := 192;
    Ord(hfLeft): EventStack[EventCursor].B := 200;
    Ord(hfRight): EventStack[EventCursor].B := 208;
    Ord(hfUp): EventStack[EventCursor].B := 216;
  end;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(1, 4, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSound);
  EventStack[EventCursor].A := 4;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(10, 11, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evDialogue);
  EventStack[EventCursor].A := speechHeroCaptured;
  EventStack[EventCursor].B := 0;
  ScratchIndex := 81;
  NeighborIndex := 103;
  NeighborY := 91;
  DamageMode := 93;
  madoushilivework;
end;

procedure QueueEnding(Form: TTSW10);
{ First-cycle princess ending, followed by the stronger cycle. }
var
  Frame: Longint;
begin
  Form.timer2on;
  PushEvent(0, 0, 0);
  PushEvent(11, 6, 0);
  PushEvent(0, 8, 0);
  PushEvent(11, 12, 0);
  PushEvent(0, 7, 0);
  PushEvent(11, 12, 0);
  for Frame := 400 downto 1 do
  begin
    PushEvent(0, 5, 0);
    PushEvent(11, 12, Frame);
  end;
  PushEvent(0, 4, 0);
  PushEvent(11, 12, 400);
  Frame := 399;
  while Frame >= 300 do
  begin
    PushEvent(0, 4, 0);
    PushEvent(11, 12, Frame);
    Dec(Frame, 3);
  end;
  Frame := 295;
  while Frame >= 205 do
  begin
    PushEvent(0, 4, 0);
    PushEvent(11, 12, Frame);
    Dec(Frame, 5);
  end;
  Frame := 197;
  while Frame >= 101 do
  begin
    PushEvent(0, 4, 0);
    PushEvent(11, 12, Frame);
    Dec(Frame, 8);
  end;
  Frame := 91;
  while Frame >= 1 do
  begin
    PushEvent(0, 4, 0);
    PushEvent(11, 12, Frame);
    Dec(Frame, 10);
  end;
  EventWaits(2);
  for Frame := 17 downto 1 do
  begin
    PushEvent(0, 6, 0);
    PushEvent(11, 12, Frame);
    PushEvent(0, 0, 0);
    if Frame = 1 then
      PushEvent(1, 1, 0)
    else
      PushEvent(1, 10, 0);
  end;
  for Frame := 247 downto 232 do
  begin
    PushEvent(0, 2, 0);
    PushEvent(11, 12, Frame);
    PushEvent(0, 0, 0);
    PushEvent(1, 1, 0);
  end;
  PushEvent(0, 0, 0);
  PushEvent(11, 15, 0);
  PushEvent(0, 0, 0);
  PushEvent(11, 14, 0);
end;

procedure TTSW10.gameover; { Reset the map and hero for a restart or next cycle. $00454DA0 }
begin
  syokidata;
  syokidata2;
  itemlive;
  if Timer1.Enabled = False then
    Timer1.Enabled := True;
  if BGMON1.Checked = True then
  begin
    soundcheck;
    soundplay;
  end;
end;

procedure TTSW10.append; { $00484DE8 }
begin
  if Hero.music_track <> 0 then
    MediaPlayer5.Close;
  Image1.Visible := False;
  Image2.Visible := False;
  Image3.Visible := False;
  Image4.Visible := False;
  Image5.Visible := False;
  Image6.Visible := False;
  Image7.Visible := False;
  Image8.Visible := False;
  Image9.Visible := False;
  Image10.Visible := False;
  Image11.Visible := False;
  Image12.Visible := False;
  Image13.Visible := False;
  Image14.Visible := False;
  Image15.Visible := False;
  Image16.Visible := False;
  Image17.Visible := False;
  Image18.Visible := False;
  Image19.Visible := False;
  Image20.Visible := False;
  Image23.Visible := False;
  Image32.Visible := False;
  Timer2.Enabled := True;
  Image34.Visible := False;
  Panel2.Visible := False;
end;

procedure TTSW10.timer3ontimer(Sender: TObject); { $00461760 }
begin
  case RepeatEnabled of
    0: Timer3.Enabled := False;
    1:
      case FacingRequest of
        Ord(moveUp):
        begin
          FlightCell := Hero.y * BoardWidth + Hero.x;
          ContactIndex := FlightCell - 11;
          if Hero.y <> 0 then
            handan;
        end;
        Ord(moveLeft):
        begin
          FlightCell := Hero.y * BoardWidth + Hero.x;
          ContactIndex := FlightCell - 1;
          if Hero.x <> 0 then
            handan;
        end;
        Ord(moveRight):
        begin
          FlightCell := Hero.y * BoardWidth + Hero.x;
          ContactIndex := FlightCell + 1;
          if Hero.x <> 10 then
            handan;
        end;
        Ord(moveDown):
        begin
          FlightCell := Hero.y * BoardWidth + Hero.x;
          ContactIndex := FlightCell + 11;
          if Hero.y <> 10 then
            handan;
        end;
        5:
          if Hero.floor < Hero.highest_floor then
          begin
            StrikeCount := 0;
            if Hero.floor <> 43 then
              Inc(Hero.floor)
            else
              Inc(Hero.floor, 2);
            mhyouji;
            disp;
          end;
        6:
          if Hero.floor > 1 then
          begin
            StrikeCount := 1;
            if Hero.floor <> 45 then
              Dec(Hero.floor)
            else
              Dec(Hero.floor, 2);
            mhyouji;
            disp;
          end;
      end;
  end;
end;

procedure TTSW10.button8onmousedown(
    Sender: TObject;
    Button: TMouseButton;
    Shift: TShiftState;
    X, Y: Integer
);
begin
  if Button8.Visible then
  begin
    timerin;
    Timer3.Enabled := True;
    FacingRequest := 5;
    RepeatEnabled := 1;
    Hero.Word632 := Ord(flightUp);
  end;
end;

procedure TTSW10.button8onmouseup(
    Sender: TObject;
    Button: TMouseButton;
    Shift: TShiftState;
    X, Y: Integer
);
begin
  if Button8.Visible then
  begin
    RepeatEnabled := 0;
    Timer3.Enabled := False;
    timerin;
    Hero.Word632 := Ord(flightUp);
  end;
end;

procedure TTSW10.button9onmousedown(
    Sender: TObject;
    Button: TMouseButton;
    Shift: TShiftState;
    X, Y: Integer
);
begin
  if Button9.Visible then
  begin
    timerin;
    Timer3.Enabled := True;
    FacingRequest := 6;
    RepeatEnabled := 1;
    Hero.Word632 := Ord(flightDown);
  end;
end;

procedure TTSW10.button9onmouseup(
    Sender: TObject;
    Button: TMouseButton;
    Shift: TShiftState;
    X, Y: Integer
);
begin
  if Button9.Visible then
  begin
    RepeatEnabled := 0;
    Timer3.Enabled := False;
    timerin;
    Hero.Word632 := Ord(flightDown);
  end;
end;

procedure TTSW10.K5Click(Sender: TObject);
begin
  if K5.Checked = True then
  begin
    K5.Checked := False;
    GameOptions[optionIntroduction] := 0;
  end
  else
  begin
    K5.Checked := True;
    GameOptions[optionIntroduction] := 1;
  end;
end;

procedure TTSW10.touzoku; { Thief dialogue and tunnel scenes on 2F, 15F, 29F, 35F and 50F. $00465900 }
begin
  itemdel;
  Button1.Caption := 'OK';
  case Hero.floor of
    2:
      case Hero.x of
        2..3:
        begin
          TileClass := 1;
          MessageText := ListBox2.Items[137];
          timer2on;
          { PushCommand(0, 0, 0). }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evWait);
          EventStack[EventCursor].A := 0;
          EventStack[EventCursor].B := 0;
          { PushCommand(10, 4, 0). }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evDialogue);
          EventStack[EventCursor].A := speechThiefOpensPrison;
          EventStack[EventCursor].B := 0;
          { PushCommand(0, 0, 0). }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evWait);
          EventStack[EventCursor].A := 0;
          EventStack[EventCursor].B := 0;
          { PushCommand(2, 1, 0). }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evRefreshStatus);
          EventStack[EventCursor].A := 1;
          EventStack[EventCursor].B := 0;
          { PushCommand(0, 0, 0). }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evWait);
          EventStack[EventCursor].A := 0;
          EventStack[EventCursor].B := 0;
          { PushCommand(13, 67, 7). }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evDoorFrame);
          EventStack[EventCursor].A := 67;
          EventStack[EventCursor].B := 7;
          doorstackin;
          { PushCommand(0, 0, 0). }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evWait);
          EventStack[EventCursor].A := 0;
          EventStack[EventCursor].B := 0;
          { PushCommand(1, 1, 0). }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evSound);
          EventStack[EventCursor].A := 1;
          EventStack[EventCursor].B := 0;
          if Hero.music_track <> 0 then
          begin
            soundcheck;
            soundplay;
          end;
        end;
        0:
        begin
          timer2on;
          { PushCommand(0, 0, 0). }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evWait);
          EventStack[EventCursor].A := 0;
          EventStack[EventCursor].B := 0;
          { PushCommand(10, 5, 0). }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evDialogue);
          EventStack[EventCursor].A := speechThiefFirstDeparture;
          EventStack[EventCursor].B := 0;
        end;
        9..10:
        begin
          ScratchIndex := 6;
          if Hero.floor2_thief_tunnel_started = 1 then
            ScratchIndex := 7;
          timer2on;
          { PushCommand(0, 0, 0). }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evWait);
          EventStack[EventCursor].A := 0;
          EventStack[EventCursor].B := 0;
          { PushCommand(10, ScratchIndex, 0). }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evDialogue);
          EventStack[EventCursor].A := ScratchIndex;
          EventStack[EventCursor].B := 0;
        end;
      end;
    15:
    begin
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(6, 6, 6). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSetTile);
      EventStack[EventCursor].A := 6;
      EventStack[EventCursor].B := tileRoad;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 2, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 2;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, 7, 6). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := 7;
      EventStack[EventCursor].B := 6;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, 8, 7). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := 8;
      EventStack[EventCursor].B := 7;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(10, 18, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evDialogue);
      EventStack[EventCursor].A := speechThiefOctopusTunnel;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(13, 7, 7). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evDoorFrame);
      EventStack[EventCursor].A := 7;
      EventStack[EventCursor].B := 7;
      doorstackin;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 1, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 1;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      timer2on;
    end;
    29:
    begin
      if Hero.y * BoardWidth + Hero.x = 27 then
      begin
        { PushCommand(0, 0, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(10, 27, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDialogue);
        EventStack[EventCursor].A := speechThiefUnfinishedTunnel;
        EventStack[EventCursor].B := 0;
        timer2on;
      end
      else
        case Hero.floor29_thief_heard of
          0:
          begin
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(10, 28, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evDialogue);
            EventStack[EventCursor].A := speechThiefFinishedTunnel;
            EventStack[EventCursor].B := 0;
            timer2on;
          end;
          1:
          begin
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(10, 29, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evDialogue);
            EventStack[EventCursor].A := speechThiefWarnsAboutBoss;
            EventStack[EventCursor].B := 0;
            timer2on;
          end;
        end;
    end;
    35:
    begin
      Maps[2, 122] := tileRoad;
      ScratchIndex := 32;
      if Hero.floor35_thief_heard = 1 then
        ScratchIndex := 33;
      timer2on;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(10, ScratchIndex, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evDialogue);
      EventStack[EventCursor].A := ScratchIndex;
      EventStack[EventCursor].B := 0;
    end;
    50:
    begin
      timer2on;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(10, 264, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evDialogue);
      EventStack[EventCursor].A := speechThiefTimeGate;
      EventStack[EventCursor].B := 0;
    end;
  end;
end;

procedure TTSW10.yousei; { Score and rank the hero at the 10F, 20F, 25F, 40F and 49F fairy checkpoints. $00478F0C }
var
  Column, Row, Sum, Invalid, Category: Longint;
  Rows: array[1..12, 1..6] of Longint;
begin
  Button1.Caption := 'OK';
  RichEdit1.Font.Size := GameOptions[optionLargeFont];
  if Hero.music_track <> 0 then
  begin
    MediaPlayer5.Close;
    Hero.music_track := 12;
    soundplay;
  end;
  Inc(Hero.Word56);
  ScratchIndex := 0;
  case Hero.floor of
    10:
      ScratchIndex :=
          60
              + (Hero.hp - 400 * (Hero.cycle_factor_minus_one + 1)) div 50
              + (Hero.attack - 29 * (Hero.cycle_factor_minus_one + 1)) * 3
              + (Hero.defense - 35 * (Hero.cycle_factor_minus_one + 1)) * 2
              + Hero.yellow_keys
              + Hero.blue_keys * 2
              + Hero.red_keys * 3;
    20:
      ScratchIndex :=
          60
              + (Hero.hp - 800 * (Hero.cycle_factor_minus_one + 1)) div 100
              + (Hero.attack - 74 * (Hero.cycle_factor_minus_one + 1)) * 2
              + (Hero.defense - 80 * (Hero.cycle_factor_minus_one + 1))
              + Hero.yellow_keys
              + Hero.blue_keys * 2
              + Hero.red_keys * 3;
    25:
      ScratchIndex :=
          60
              + (Hero.hp - 3000 * (Hero.cycle_factor_minus_one + 1)) div 400
              + (Hero.attack - 240 * (Hero.cycle_factor_minus_one + 1)) div 2
              + (Hero.defense - 300 * (Hero.cycle_factor_minus_one + 1)) div 3
              + Hero.yellow_keys
              + Hero.blue_keys * 2
              + Hero.red_keys * 3;
    40:
      ScratchIndex :=
          60
              + (Hero.hp - 1600 * (Hero.cycle_factor_minus_one + 1)) div 200
              + (Hero.attack - 152 * (Hero.cycle_factor_minus_one + 1))
              + (Hero.defense - 198 * (Hero.cycle_factor_minus_one + 1)) div 2
              + Hero.yellow_keys
              + Hero.blue_keys * 2
              + Hero.red_keys * 3;
    49:
      ScratchIndex :=
          60
              + (Hero.hp - 3000 * (Hero.cycle_factor_minus_one + 1)) div 400
              + (Hero.attack - 240 * (Hero.cycle_factor_minus_one + 1)) div 2
              + (Hero.defense - 300 * (Hero.cycle_factor_minus_one + 1)) div 3
              + Hero.yellow_keys
              + Hero.blue_keys * 2
              + Hero.red_keys * 3;
  end;
  if ScratchIndex < 0 then
    ScratchIndex := 0;
  Hero.Word340 := ScratchIndex;
  Hero.Word344 := 0;
  Category := 0;
  case Hero.floor of
    10:
    begin
      Category := 1;
      IOPath := Memo12.Lines[0] + '\option1.dat';
    end;
    20:
    begin
      Category := 2;
      IOPath := Memo12.Lines[0] + '\option2.dat';
    end;
    25:
    begin
      Category := 3;
      IOPath := Memo12.Lines[0] + '\option3.dat';
    end;
    40:
    begin
      Category := 4;
      IOPath := Memo12.Lines[0] + '\option4.dat';
    end;
    49:
    begin
      Category := 5;
      IOPath := Memo12.Lines[0] + '\option5.dat';
    end;
  end;
  try
    AssignFile(SettingsFile, IOPath);
    Reset(SettingsFile, 1);
    BlockRead(SettingsFile, Rows, SizeOf(Rows));
    CloseFile(SettingsFile);
    Invalid := 0;
    for Row := 1 to 10 do
    begin
      Sum := 0;
      for Column := 1 to 4 do
        Sum := Sum + Rows[Row, Column];
      if Sum <> Rows[Row, 5] then
        Invalid := 1;
      Sum := 0;
      for Column := 1 to 5 do
        case Column of
          1, 3, 5: Sum := Sum + Rows[Row, Column];
          2, 4: Sum := Sum - Rows[Row, Column];
        end;
      if Sum <> Rows[Row, 6] then
        Invalid := 1;
    end;
    for Row := 1 to 6 do
    begin
      Sum := 0;
      for Column := 1 to 10 do
        Sum := Sum + Rows[Column, Row];
      if Sum <> Rows[11, Row] then
        Invalid := 1;
      Sum := 0;
      for Column := 1 to 11 do
        case Column of
          1, 3, 5, 7, 9, 11: Sum := Sum + Rows[Column, Row];
          2, 4, 6, 8, 10: Sum := Sum - Rows[Column, Row];
        end;
      if (Row <> 6) and (Sum <> Rows[12, Row]) then
        Invalid := 1;
    end;
    if (Invalid = 0) and (Rows[12, 6] div 100 <> Hero.Word628) then
      Invalid := 2;
    if (Invalid = 0) and (Hero.Word628 * (-100) + Rows[12, 6] <> (-1) * Category) then
      Invalid := 2;
    if (Invalid = 1) or (Invalid = 2) then
    begin
      case Invalid of
        1: ShowMessage('Ranking data is abnormal. Use a temporary Ranking.');
        2: ShowMessage('Version of Ranking data is abnormal. Use a temporary Ranking.');
      end;
      case Category of
        1:
        begin
          Rows[1, 1] := 100;
          Rows[1, 2] := 500;
          Rows[1, 3] := 25;
          Rows[1, 4] := 25;
          Rows[1, 5] := 0;
          Rows[1, 6] := 0;
          Rows[2, 1] := 90;
          Rows[2, 2] := 450;
          Rows[2, 3] := 24;
          Rows[2, 4] := 24;
          Rows[2, 5] := 0;
          Rows[2, 6] := 0;
          Rows[3, 1] := 80;
          Rows[3, 2] := 400;
          Rows[3, 3] := 23;
          Rows[3, 4] := 23;
          Rows[3, 5] := 0;
          Rows[3, 6] := 0;
          Rows[4, 1] := 70;
          Rows[4, 2] := 350;
          Rows[4, 3] := 22;
          Rows[4, 4] := 22;
          Rows[4, 5] := 0;
          Rows[4, 6] := 0;
          Rows[5, 1] := 60;
          Rows[5, 2] := 300;
          Rows[5, 3] := 21;
          Rows[5, 4] := 21;
          Rows[5, 5] := 0;
          Rows[5, 6] := 0;
          Rows[6, 1] := 50;
          Rows[6, 2] := 250;
          Rows[6, 3] := 20;
          Rows[6, 4] := 20;
          Rows[6, 5] := 0;
          Rows[6, 6] := 0;
          Rows[7, 1] := 40;
          Rows[7, 2] := 200;
          Rows[7, 3] := 19;
          Rows[7, 4] := 19;
          Rows[7, 5] := 0;
          Rows[7, 6] := 0;
          Rows[8, 1] := 30;
          Rows[8, 2] := 150;
          Rows[8, 3] := 18;
          Rows[8, 4] := 18;
          Rows[8, 5] := 0;
          Rows[8, 6] := 0;
          Rows[9, 1] := 20;
          Rows[9, 2] := 100;
          Rows[9, 3] := 17;
          Rows[9, 4] := 17;
          Rows[9, 5] := 0;
          Rows[9, 6] := 0;
          Rows[10, 1] := 10;
          Rows[10, 2] := 50;
          Rows[10, 3] := 16;
          Rows[10, 4] := 16;
          Rows[10, 5] := 0;
          Rows[10, 6] := 0;
          Rows[11, 1] := 0;
          Rows[11, 2] := 0;
          Rows[11, 3] := 0;
          Rows[11, 4] := 0;
          Rows[11, 5] := 0;
          Rows[11, 6] := 0;
          Rows[12, 1] := 0;
          Rows[12, 2] := 0;
          Rows[12, 3] := 0;
          Rows[12, 4] := 0;
          Rows[12, 5] := 0;
          Rows[12, 6] := 0;
        end;
        2:
        begin
          Rows[1, 1] := 100;
          Rows[1, 2] := 1000;
          Rows[1, 3] := 50;
          Rows[1, 4] := 50;
          Rows[1, 5] := 0;
          Rows[1, 6] := 0;
          Rows[2, 1] := 90;
          Rows[2, 2] := 900;
          Rows[2, 3] := 45;
          Rows[2, 4] := 45;
          Rows[2, 5] := 0;
          Rows[2, 6] := 0;
          Rows[3, 1] := 80;
          Rows[3, 2] := 800;
          Rows[3, 3] := 40;
          Rows[3, 4] := 40;
          Rows[3, 5] := 0;
          Rows[3, 6] := 0;
          Rows[4, 1] := 70;
          Rows[4, 2] := 700;
          Rows[4, 3] := 35;
          Rows[4, 4] := 35;
          Rows[4, 5] := 0;
          Rows[4, 6] := 0;
          Rows[5, 1] := 60;
          Rows[5, 2] := 600;
          Rows[5, 3] := 30;
          Rows[5, 4] := 30;
          Rows[5, 5] := 0;
          Rows[5, 6] := 0;
          Rows[6, 1] := 50;
          Rows[6, 2] := 500;
          Rows[6, 3] := 25;
          Rows[6, 4] := 25;
          Rows[6, 5] := 0;
          Rows[6, 6] := 0;
          Rows[7, 1] := 40;
          Rows[7, 2] := 400;
          Rows[7, 3] := 20;
          Rows[7, 4] := 20;
          Rows[7, 5] := 0;
          Rows[7, 6] := 0;
          Rows[8, 1] := 30;
          Rows[8, 2] := 300;
          Rows[8, 3] := 15;
          Rows[8, 4] := 15;
          Rows[8, 5] := 0;
          Rows[8, 6] := 0;
          Rows[9, 1] := 20;
          Rows[9, 2] := 200;
          Rows[9, 3] := 10;
          Rows[9, 4] := 10;
          Rows[9, 5] := 0;
          Rows[9, 6] := 0;
          Rows[10, 1] := 10;
          Rows[10, 2] := 100;
          Rows[10, 3] := 5;
          Rows[10, 4] := 5;
          Rows[10, 5] := 0;
          Rows[10, 6] := 0;
          Rows[11, 1] := 0;
          Rows[11, 2] := 0;
          Rows[11, 3] := 0;
          Rows[11, 4] := 0;
          Rows[11, 5] := 0;
          Rows[11, 6] := 0;
          Rows[12, 1] := 0;
          Rows[12, 2] := 0;
          Rows[12, 3] := 0;
          Rows[12, 4] := 0;
          Rows[12, 5] := 0;
          Rows[12, 6] := 0;
        end;
        3, 5:
        begin
          Rows[1, 1] := 100;
          Rows[1, 2] := 10000;
          Rows[1, 3] := 500;
          Rows[1, 4] := 500;
          Rows[1, 5] := 0;
          Rows[1, 6] := 0;
          Rows[2, 1] := 90;
          Rows[2, 2] := 9000;
          Rows[2, 3] := 450;
          Rows[2, 4] := 450;
          Rows[2, 5] := 0;
          Rows[2, 6] := 0;
          Rows[3, 1] := 80;
          Rows[3, 2] := 8000;
          Rows[3, 3] := 400;
          Rows[3, 4] := 400;
          Rows[3, 5] := 0;
          Rows[3, 6] := 0;
          Rows[4, 1] := 70;
          Rows[4, 2] := 7000;
          Rows[4, 3] := 350;
          Rows[4, 4] := 350;
          Rows[4, 5] := 0;
          Rows[4, 6] := 0;
          Rows[5, 1] := 60;
          Rows[5, 2] := 6000;
          Rows[5, 3] := 300;
          Rows[5, 4] := 300;
          Rows[5, 5] := 0;
          Rows[5, 6] := 0;
          Rows[6, 1] := 50;
          Rows[6, 2] := 5000;
          Rows[6, 3] := 250;
          Rows[6, 4] := 250;
          Rows[6, 5] := 0;
          Rows[6, 6] := 0;
          Rows[7, 1] := 40;
          Rows[7, 2] := 4000;
          Rows[7, 3] := 200;
          Rows[7, 4] := 200;
          Rows[7, 5] := 0;
          Rows[7, 6] := 0;
          Rows[8, 1] := 30;
          Rows[8, 2] := 3000;
          Rows[8, 3] := 150;
          Rows[8, 4] := 150;
          Rows[8, 5] := 0;
          Rows[8, 6] := 0;
          Rows[9, 1] := 20;
          Rows[9, 2] := 2000;
          Rows[9, 3] := 100;
          Rows[9, 4] := 100;
          Rows[9, 5] := 0;
          Rows[9, 6] := 0;
          Rows[10, 1] := 10;
          Rows[10, 2] := 1000;
          Rows[10, 3] := 50;
          Rows[10, 4] := 50;
          Rows[10, 5] := 0;
          Rows[10, 6] := 0;
          Rows[11, 1] := 0;
          Rows[11, 2] := 0;
          Rows[11, 3] := 0;
          Rows[11, 4] := 0;
          Rows[11, 5] := 0;
          Rows[11, 6] := 0;
          Rows[12, 1] := 0;
          Rows[12, 2] := 0;
          Rows[12, 3] := 0;
          Rows[12, 4] := 0;
          Rows[12, 5] := 0;
          Rows[12, 6] := 0;
        end;
        4:
        begin
          Rows[1, 1] := 100;
          Rows[1, 2] := 5000;
          Rows[1, 3] := 200;
          Rows[1, 4] := 200;
          Rows[1, 5] := 0;
          Rows[1, 6] := 0;
          Rows[2, 1] := 90;
          Rows[2, 2] := 4500;
          Rows[2, 3] := 190;
          Rows[2, 4] := 190;
          Rows[2, 5] := 0;
          Rows[2, 6] := 0;
          Rows[3, 1] := 80;
          Rows[3, 2] := 4000;
          Rows[3, 3] := 180;
          Rows[3, 4] := 180;
          Rows[3, 5] := 0;
          Rows[3, 6] := 0;
          Rows[4, 1] := 70;
          Rows[4, 2] := 3500;
          Rows[4, 3] := 170;
          Rows[4, 4] := 170;
          Rows[4, 5] := 0;
          Rows[4, 6] := 0;
          Rows[5, 1] := 60;
          Rows[5, 2] := 3000;
          Rows[5, 3] := 160;
          Rows[5, 4] := 160;
          Rows[5, 5] := 0;
          Rows[5, 6] := 0;
          Rows[6, 1] := 50;
          Rows[6, 2] := 2500;
          Rows[6, 3] := 150;
          Rows[6, 4] := 150;
          Rows[6, 5] := 0;
          Rows[6, 6] := 0;
          Rows[7, 1] := 40;
          Rows[7, 2] := 2000;
          Rows[7, 3] := 140;
          Rows[7, 4] := 140;
          Rows[7, 5] := 0;
          Rows[7, 6] := 0;
          Rows[8, 1] := 30;
          Rows[8, 2] := 1500;
          Rows[8, 3] := 130;
          Rows[8, 4] := 130;
          Rows[8, 5] := 0;
          Rows[8, 6] := 0;
          Rows[9, 1] := 20;
          Rows[9, 2] := 1000;
          Rows[9, 3] := 120;
          Rows[9, 4] := 120;
          Rows[9, 5] := 0;
          Rows[9, 6] := 0;
          Rows[10, 1] := 10;
          Rows[10, 2] := 500;
          Rows[10, 3] := 110;
          Rows[10, 4] := 110;
          Rows[10, 5] := 0;
          Rows[10, 6] := 0;
          Rows[11, 1] := 0;
          Rows[11, 2] := 0;
          Rows[11, 3] := 0;
          Rows[11, 4] := 0;
          Rows[11, 5] := 0;
          Rows[11, 6] := 0;
          Rows[12, 1] := 0;
          Rows[12, 2] := 0;
          Rows[12, 3] := 0;
          Rows[12, 4] := 0;
          Rows[12, 5] := 0;
          Rows[12, 6] := 0;
        end;
      end;
    end;
  except
    ShowMessage('Version of Ranking data is old. Use a temporary Ranking.');
    case Category of
      1:
      begin
        Rows[1, 1] := 100;
        Rows[1, 2] := 500;
        Rows[1, 3] := 25;
        Rows[1, 4] := 25;
        Rows[1, 5] := 0;
        Rows[1, 6] := 0;
        Rows[2, 1] := 90;
        Rows[2, 2] := 450;
        Rows[2, 3] := 24;
        Rows[2, 4] := 24;
        Rows[2, 5] := 0;
        Rows[2, 6] := 0;
        Rows[3, 1] := 80;
        Rows[3, 2] := 400;
        Rows[3, 3] := 23;
        Rows[3, 4] := 23;
        Rows[3, 5] := 0;
        Rows[3, 6] := 0;
        Rows[4, 1] := 70;
        Rows[4, 2] := 350;
        Rows[4, 3] := 22;
        Rows[4, 4] := 22;
        Rows[4, 5] := 0;
        Rows[4, 6] := 0;
        Rows[5, 1] := 60;
        Rows[5, 2] := 300;
        Rows[5, 3] := 21;
        Rows[5, 4] := 21;
        Rows[5, 5] := 0;
        Rows[5, 6] := 0;
        Rows[6, 1] := 50;
        Rows[6, 2] := 250;
        Rows[6, 3] := 20;
        Rows[6, 4] := 20;
        Rows[6, 5] := 0;
        Rows[6, 6] := 0;
        Rows[7, 1] := 40;
        Rows[7, 2] := 200;
        Rows[7, 3] := 19;
        Rows[7, 4] := 19;
        Rows[7, 5] := 0;
        Rows[7, 6] := 0;
        Rows[8, 1] := 30;
        Rows[8, 2] := 150;
        Rows[8, 3] := 18;
        Rows[8, 4] := 18;
        Rows[8, 5] := 0;
        Rows[8, 6] := 0;
        Rows[9, 1] := 20;
        Rows[9, 2] := 100;
        Rows[9, 3] := 17;
        Rows[9, 4] := 17;
        Rows[9, 5] := 0;
        Rows[9, 6] := 0;
        Rows[10, 1] := 10;
        Rows[10, 2] := 50;
        Rows[10, 3] := 16;
        Rows[10, 4] := 16;
        Rows[10, 5] := 0;
        Rows[10, 6] := 0;
        Rows[11, 1] := 0;
        Rows[11, 2] := 0;
        Rows[11, 3] := 0;
        Rows[11, 4] := 0;
        Rows[11, 5] := 0;
        Rows[11, 6] := 0;
        Rows[12, 1] := 0;
        Rows[12, 2] := 0;
        Rows[12, 3] := 0;
        Rows[12, 4] := 0;
        Rows[12, 5] := 0;
        Rows[12, 6] := 0;
      end;
      2:
      begin
        Rows[1, 1] := 100;
        Rows[1, 2] := 1000;
        Rows[1, 3] := 50;
        Rows[1, 4] := 50;
        Rows[1, 5] := 0;
        Rows[1, 6] := 0;
        Rows[2, 1] := 90;
        Rows[2, 2] := 900;
        Rows[2, 3] := 45;
        Rows[2, 4] := 45;
        Rows[2, 5] := 0;
        Rows[2, 6] := 0;
        Rows[3, 1] := 80;
        Rows[3, 2] := 800;
        Rows[3, 3] := 40;
        Rows[3, 4] := 40;
        Rows[3, 5] := 0;
        Rows[3, 6] := 0;
        Rows[4, 1] := 70;
        Rows[4, 2] := 700;
        Rows[4, 3] := 35;
        Rows[4, 4] := 35;
        Rows[4, 5] := 0;
        Rows[4, 6] := 0;
        Rows[5, 1] := 60;
        Rows[5, 2] := 600;
        Rows[5, 3] := 30;
        Rows[5, 4] := 30;
        Rows[5, 5] := 0;
        Rows[5, 6] := 0;
        Rows[6, 1] := 50;
        Rows[6, 2] := 500;
        Rows[6, 3] := 25;
        Rows[6, 4] := 25;
        Rows[6, 5] := 0;
        Rows[6, 6] := 0;
        Rows[7, 1] := 40;
        Rows[7, 2] := 400;
        Rows[7, 3] := 20;
        Rows[7, 4] := 20;
        Rows[7, 5] := 0;
        Rows[7, 6] := 0;
        Rows[8, 1] := 30;
        Rows[8, 2] := 300;
        Rows[8, 3] := 15;
        Rows[8, 4] := 15;
        Rows[8, 5] := 0;
        Rows[8, 6] := 0;
        Rows[9, 1] := 20;
        Rows[9, 2] := 200;
        Rows[9, 3] := 10;
        Rows[9, 4] := 10;
        Rows[9, 5] := 0;
        Rows[9, 6] := 0;
        Rows[10, 1] := 10;
        Rows[10, 2] := 100;
        Rows[10, 3] := 5;
        Rows[10, 4] := 5;
        Rows[10, 5] := 0;
        Rows[10, 6] := 0;
        Rows[11, 1] := 0;
        Rows[11, 2] := 0;
        Rows[11, 3] := 0;
        Rows[11, 4] := 0;
        Rows[11, 5] := 0;
        Rows[11, 6] := 0;
        Rows[12, 1] := 0;
        Rows[12, 2] := 0;
        Rows[12, 3] := 0;
        Rows[12, 4] := 0;
        Rows[12, 5] := 0;
        Rows[12, 6] := 0;
      end;
      3, 5:
      begin
        Rows[1, 1] := 100;
        Rows[1, 2] := 10000;
        Rows[1, 3] := 500;
        Rows[1, 4] := 500;
        Rows[1, 5] := 0;
        Rows[1, 6] := 0;
        Rows[2, 1] := 90;
        Rows[2, 2] := 9000;
        Rows[2, 3] := 450;
        Rows[2, 4] := 450;
        Rows[2, 5] := 0;
        Rows[2, 6] := 0;
        Rows[3, 1] := 80;
        Rows[3, 2] := 8000;
        Rows[3, 3] := 400;
        Rows[3, 4] := 400;
        Rows[3, 5] := 0;
        Rows[3, 6] := 0;
        Rows[4, 1] := 70;
        Rows[4, 2] := 7000;
        Rows[4, 3] := 350;
        Rows[4, 4] := 350;
        Rows[4, 5] := 0;
        Rows[4, 6] := 0;
        Rows[5, 1] := 60;
        Rows[5, 2] := 6000;
        Rows[5, 3] := 300;
        Rows[5, 4] := 300;
        Rows[5, 5] := 0;
        Rows[5, 6] := 0;
        Rows[6, 1] := 50;
        Rows[6, 2] := 5000;
        Rows[6, 3] := 250;
        Rows[6, 4] := 250;
        Rows[6, 5] := 0;
        Rows[6, 6] := 0;
        Rows[7, 1] := 40;
        Rows[7, 2] := 4000;
        Rows[7, 3] := 200;
        Rows[7, 4] := 200;
        Rows[7, 5] := 0;
        Rows[7, 6] := 0;
        Rows[8, 1] := 30;
        Rows[8, 2] := 3000;
        Rows[8, 3] := 150;
        Rows[8, 4] := 150;
        Rows[8, 5] := 0;
        Rows[8, 6] := 0;
        Rows[9, 1] := 20;
        Rows[9, 2] := 2000;
        Rows[9, 3] := 100;
        Rows[9, 4] := 100;
        Rows[9, 5] := 0;
        Rows[9, 6] := 0;
        Rows[10, 1] := 10;
        Rows[10, 2] := 1000;
        Rows[10, 3] := 50;
        Rows[10, 4] := 50;
        Rows[10, 5] := 0;
        Rows[10, 6] := 0;
        Rows[11, 1] := 0;
        Rows[11, 2] := 0;
        Rows[11, 3] := 0;
        Rows[11, 4] := 0;
        Rows[11, 5] := 0;
        Rows[11, 6] := 0;
        Rows[12, 1] := 0;
        Rows[12, 2] := 0;
        Rows[12, 3] := 0;
        Rows[12, 4] := 0;
        Rows[12, 5] := 0;
        Rows[12, 6] := 0;
      end;
      4:
      begin
        Rows[1, 1] := 100;
        Rows[1, 2] := 5000;
        Rows[1, 3] := 200;
        Rows[1, 4] := 200;
        Rows[1, 5] := 0;
        Rows[1, 6] := 0;
        Rows[2, 1] := 90;
        Rows[2, 2] := 4500;
        Rows[2, 3] := 190;
        Rows[2, 4] := 190;
        Rows[2, 5] := 0;
        Rows[2, 6] := 0;
        Rows[3, 1] := 80;
        Rows[3, 2] := 4000;
        Rows[3, 3] := 180;
        Rows[3, 4] := 180;
        Rows[3, 5] := 0;
        Rows[3, 6] := 0;
        Rows[4, 1] := 70;
        Rows[4, 2] := 3500;
        Rows[4, 3] := 170;
        Rows[4, 4] := 170;
        Rows[4, 5] := 0;
        Rows[4, 6] := 0;
        Rows[5, 1] := 60;
        Rows[5, 2] := 3000;
        Rows[5, 3] := 160;
        Rows[5, 4] := 160;
        Rows[5, 5] := 0;
        Rows[5, 6] := 0;
        Rows[6, 1] := 50;
        Rows[6, 2] := 2500;
        Rows[6, 3] := 150;
        Rows[6, 4] := 150;
        Rows[6, 5] := 0;
        Rows[6, 6] := 0;
        Rows[7, 1] := 40;
        Rows[7, 2] := 2000;
        Rows[7, 3] := 140;
        Rows[7, 4] := 140;
        Rows[7, 5] := 0;
        Rows[7, 6] := 0;
        Rows[8, 1] := 30;
        Rows[8, 2] := 1500;
        Rows[8, 3] := 130;
        Rows[8, 4] := 130;
        Rows[8, 5] := 0;
        Rows[8, 6] := 0;
        Rows[9, 1] := 20;
        Rows[9, 2] := 1000;
        Rows[9, 3] := 120;
        Rows[9, 4] := 120;
        Rows[9, 5] := 0;
        Rows[9, 6] := 0;
        Rows[10, 1] := 10;
        Rows[10, 2] := 500;
        Rows[10, 3] := 110;
        Rows[10, 4] := 110;
        Rows[10, 5] := 0;
        Rows[10, 6] := 0;
        Rows[11, 1] := 0;
        Rows[11, 2] := 0;
        Rows[11, 3] := 0;
        Rows[11, 4] := 0;
        Rows[11, 5] := 0;
        Rows[11, 6] := 0;
        Rows[12, 1] := 0;
        Rows[12, 2] := 0;
        Rows[12, 3] := 0;
        Rows[12, 4] := 0;
        Rows[12, 5] := 0;
        Rows[12, 6] := 0;
      end;
    end;
  end;
  if Hero.Word340 - Rows[1, 1] > 0 then
    Hero.Word344 := 1
  else if (Hero.Word340 - Rows[1, 1] = 0) and (Hero.hp - Rows[1, 2] > 0) then
    Hero.Word344 := 1
  else if (Hero.Word340 - Rows[1, 1] = 0)
      and (Hero.hp - Rows[1, 2] = 0)
      and (Hero.attack + Hero.defense - Rows[1, 2] - Rows[1, 3] > 0) then
    Hero.Word344 := 1
  else if Hero.Word340 - Rows[2, 1] > 0 then
    Hero.Word344 := 2
  else if (Hero.Word340 - Rows[2, 1] = 0) and (Hero.hp - Rows[2, 2] > 0) then
    Hero.Word344 := 2
  else if (Hero.Word340 - Rows[2, 1] = 0)
      and (Hero.hp - Rows[2, 2] = 0)
      and (Hero.attack + Hero.defense - Rows[2, 2] - Rows[2, 3] > 0) then
    Hero.Word344 := 2
  else if Hero.Word340 - Rows[3, 1] > 0 then
    Hero.Word344 := 3
  else if (Hero.Word340 - Rows[3, 1] = 0) and (Hero.hp - Rows[3, 2] > 0) then
    Hero.Word344 := 3
  else if (Hero.Word340 - Rows[3, 1] = 0)
      and (Hero.hp - Rows[3, 2] = 0)
      and (Hero.attack + Hero.defense - Rows[3, 2] - Rows[3, 3] > 0) then
    Hero.Word344 := 3
  else if Hero.Word340 - Rows[4, 1] > 0 then
    Hero.Word344 := 4
  else if (Hero.Word340 - Rows[4, 1] = 0) and (Hero.hp - Rows[4, 2] > 0) then
    Hero.Word344 := 4
  else if (Hero.Word340 - Rows[4, 1] = 0)
      and (Hero.hp - Rows[4, 2] = 0)
      and (Hero.attack + Hero.defense - Rows[4, 2] - Rows[4, 3] > 0) then
    Hero.Word344 := 4
  else if Hero.Word340 - Rows[5, 1] > 0 then
    Hero.Word344 := 5
  else if (Hero.Word340 - Rows[5, 1] = 0) and (Hero.hp - Rows[5, 2] > 0) then
    Hero.Word344 := 5
  else if (Hero.Word340 - Rows[5, 1] = 0)
      and (Hero.hp - Rows[5, 2] = 0)
      and (Hero.attack + Hero.defense - Rows[5, 2] - Rows[5, 3] > 0) then
    Hero.Word344 := 5
  else if Hero.Word340 - Rows[6, 1] > 0 then
    Hero.Word344 := 6
  else if (Hero.Word340 - Rows[6, 1] = 0) and (Hero.hp - Rows[6, 2] > 0) then
    Hero.Word344 := 6
  else if (Hero.Word340 - Rows[6, 1] = 0)
      and (Hero.hp - Rows[6, 2] = 0)
      and (Hero.attack + Hero.defense - Rows[6, 2] - Rows[6, 3] > 0) then
    Hero.Word344 := 6
  else if Hero.Word340 - Rows[7, 1] > 0 then
    Hero.Word344 := 7
  else if (Hero.Word340 - Rows[7, 1] = 0) and (Hero.hp - Rows[7, 2] > 0) then
    Hero.Word344 := 7
  else if (Hero.Word340 - Rows[7, 1] = 0)
      and (Hero.hp - Rows[7, 2] = 0)
      and (Hero.attack + Hero.defense - Rows[7, 2] - Rows[7, 3] > 0) then
    Hero.Word344 := 7
  else if Hero.Word340 - Rows[8, 1] > 0 then
    Hero.Word344 := 8
  else if (Hero.Word340 - Rows[8, 1] = 0) and (Hero.hp - Rows[8, 2] > 0) then
    Hero.Word344 := 8
  else if (Hero.Word340 - Rows[8, 1] = 0)
      and (Hero.hp - Rows[8, 2] = 0)
      and (Hero.attack + Hero.defense - Rows[8, 2] - Rows[8, 3] > 0) then
    Hero.Word344 := 8
  else if Hero.Word340 - Rows[9, 1] > 0 then
    Hero.Word344 := 9
  else if (Hero.Word340 - Rows[9, 1] = 0) and (Hero.hp - Rows[9, 2] > 0) then
    Hero.Word344 := 9
  else if (Hero.Word340 - Rows[9, 1] = 0)
      and (Hero.hp - Rows[9, 2] = 0)
      and (Hero.attack + Hero.defense - Rows[9, 2] - Rows[9, 3] > 0) then
    Hero.Word344 := 9
  else if Hero.Word340 - Rows[10, 1] > 0 then
    Hero.Word344 := 10
  else if (Hero.Word340 - Rows[10, 1] = 0) and (Hero.hp - Rows[10, 2] > 0) then
    Hero.Word344 := 10
  else if (Hero.Word340 - Rows[10, 1] = 0)
      and (Hero.hp - Rows[10, 2] = 0)
      and (Hero.attack + Hero.defense - Rows[10, 2] - Rows[10, 3] > 0) then
    Hero.Word344 := 10;
  case Hero.floor of
    10: Hero.Word348 := 1;
    20: Hero.Word348 := 2;
    25: Hero.Word348 := 3;
    40: Hero.Word348 := 4;
    49: Hero.Word348 := 5;
  end;
  IOPath := Memo12.Lines[0] + '\save0.dat';
  AssignFile(SettingsFile, IOPath);
  Rewrite(SettingsFile, 1);
  BlockWrite(SettingsFile, Maps, SizeOf(Maps));
  BlockWrite(SettingsFile, Hero, SizeOf(Hero));
  CloseFile(SettingsFile);
  TileClass := 1;
  if Hero.Word344 > 0 then
    RichEdit1.Text :=
        ListBox2.Items[textFairyRankPrefix]
            + ' '
            + IntToStr(Hero.Word344)
            + ' '
            + ListBox2.Items[textFairyRankSuffix]
            + ListBox2.Items[textFairyScorePrefix]
            + ' '
            + IntToStr(Hero.Word340)
            + ' '
            + ListBox2.Items[textFairyScoreSuffix]
  else
    RichEdit1.Text :=
        ListBox2.Items[textFairyScorePrefix]
            + ' '
            + IntToStr(ScratchIndex)
            + ' '
            + ListBox2.Items[textFairyScoreSuffix];
  case ScratchIndex of
    0..49:
    begin
      RichEdit1.Text := RichEdit1.Text + ListBox2.Items[textFairyReconsider];
    end;
    50..59:
    begin
      RichEdit1.Text := RichEdit1.Text + ListBox2.Items[textFairyBelowAverage];
    end;
    60..79:
    begin
      RichEdit1.Text := RichEdit1.Text + ListBox2.Items[textFairyOrdinary];
    end;
    80..99:
    begin
      RichEdit1.Text := RichEdit1.Text + ListBox2.Items[textFairyDoingFine];
    end;
    100..120:
    begin
      RichEdit1.Text :=
          RichEdit1.Text
              + ListBox2.Items[textFairyGreatScore]
              + ListBox2.Items[textFairyTitlePrefix]
              + ListBox2.Items[textFairyFighter]
              + ListBox2.Items[textFairyTitleSuffix];
      if Hero.Word56 <= 3 then
        RichEdit1.Text := RichEdit1.Text + ListBox2.Items[textFairyKeepGoing]
      else
        RichEdit1.Text := RichEdit1.Text + ListBox2.Items[textFairyFarewell];
    end;
    121..140:
    begin
      RichEdit1.Text :=
          RichEdit1.Text
              + ListBox2.Items[textFairyGreatScore]
              + ListBox2.Items[textFairyTitlePrefix]
              + ListBox2.Items[textFairyBrave]
              + ListBox2.Items[textFairyTitleSuffix];
      if Hero.Word56 <= 3 then
        RichEdit1.Text := RichEdit1.Text + ListBox2.Items[textFairyKeepGoing]
      else
        RichEdit1.Text := RichEdit1.Text + ListBox2.Items[textFairyFarewell];
    end;
    141..160:
    begin
      RichEdit1.Text :=
          RichEdit1.Text
              + ListBox2.Items[textFairyContinue]
              + ListBox2.Items[textFairyTitlePrefix]
              + ListBox2.Items[textFairyHero]
              + ListBox2.Items[textFairyTitleSuffix];
      if Hero.Word56 <= 3 then
        RichEdit1.Text := RichEdit1.Text + ListBox2.Items[textFairyKeepGoing]
      else
        RichEdit1.Text := RichEdit1.Text + ListBox2.Items[textFairyFarewell];
    end;
    161..200:
    begin
      RichEdit1.Text :=
          RichEdit1.Text
              + ListBox2.Items[textFairyContinue]
              + ListBox2.Items[textFairyTitlePrefix]
              + ListBox2.Items[textFairySwordEmperor]
              + ListBox2.Items[textFairyTitleSuffix];
      if Hero.Word56 <= 3 then
        RichEdit1.Text := RichEdit1.Text + ListBox2.Items[textFairyKeepGoing]
      else
        RichEdit1.Text := RichEdit1.Text + ListBox2.Items[textFairyFarewell];
    end;
    201..9999:
    begin
      RichEdit1.Text :=
          RichEdit1.Text
              + ListBox2.Items[textFairyContinue]
              + ListBox2.Items[textFairyTitlePrefix]
              + ListBox2.Items[textFairyFighterGod]
              + ListBox2.Items[textFairyTitleSuffix];
      if Hero.Word56 <= 3 then
        RichEdit1.Text := RichEdit1.Text + ListBox2.Items[textFairyKeepGoing]
      else
        RichEdit1.Text := RichEdit1.Text + ListBox2.Items[textFairyFarewell];
    end;
  end;
  if Hero.music_track <> 0 then
  begin
    { PushCommand(15, 0, 0). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evFloorMusic);
    EventStack[EventCursor].A := 0;
    EventStack[EventCursor].B := 0;
  end;
  { PushCommand(6, fairy cell, 6). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSetTile);
  case Hero.floor of
    10:
    begin
      EventStack[EventCursor].A := 27;
      DialogueSpeech := speechFairyFloor10;
    end;
    20:
    begin
      EventStack[EventCursor].A := 49;
      DialogueSpeech := speechFairyFloor20;
    end;
    25:
    begin
      EventStack[EventCursor].A := 71;
      DialogueSpeech := speechFairyFloor25;
    end;
    40:
    begin
      EventStack[EventCursor].A := 60;
      DialogueSpeech := speechFairyFloor40;
    end;
    49:
    begin
      EventStack[EventCursor].A := 16;
      DialogueSpeech := speechFairyFloor49;
    end;
  end;
  EventStack[EventCursor].B := 6;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(1, 2, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSound);
  EventStack[EventCursor].A := 2;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(10, DialogueSpeech, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evDialogue);
  EventStack[EventCursor].A := DialogueSpeech;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  timer2on;
end;

procedure TTSW10.stackwork; { $004526C0 }
type
  THeroWords = array[0..HeroWordCount - 1] of Longint;
var
  HeroWords: THeroWords absolute Hero;
begin
  EventPaused := 0;
  case Smallint(EventStack[EventCursor].Opcode) of
    Ord(evSound):
    begin
      case Smallint(EventStack[EventCursor].A) of
        1:
          if Hero.effects_muted = 0 then
            MediaPlayer1.Play;
        2:
          if Hero.effects_muted = 0 then
            MediaPlayer2.Play;
        3:
          if Hero.effects_muted = 0 then
            MediaPlayer3.Play;
        4:
          if Hero.effects_muted = 0 then
            MediaPlayer4.Play;
        5:
          if Hero.music_track <> 0 then
            soundplay;
        6:
          if Hero.music_track <> 0 then
            MediaPlayer5.Close;
        7:
          if Hero.effects_muted = 0 then
          begin
            MediaPlayer6.FileName := Memo12.Lines[1] + '\wav\3f.wav';
            MediaPlayer6.Open;
            MediaPlayer6.Play;
          end;
        8:
          if Hero.effects_muted = 0 then
          begin
            MediaPlayer6.FileName := Memo12.Lines[1] + '\wav\20f.wav';
            MediaPlayer6.Open;
            MediaPlayer6.Play;
          end;
        9:
          if Hero.effects_muted = 0 then
          begin
            MediaPlayer6.FileName := Memo12.Lines[1] + '\wav\kai.wav';
            MediaPlayer6.Open;
            MediaPlayer6.Play;
          end;
        10:
          if Hero.effects_muted = 0 then
          begin
            MediaPlayer6.FileName := Memo12.Lines[1] + '\wav\kai2.wav';
            MediaPlayer6.Open;
            MediaPlayer6.Play;
          end;
      end;
    end;
    Ord(evSetTile):
    begin
      Maps[Hero.floor, Smallint(EventStack[EventCursor].A) + MapTileOffset] :=
          Byte(EventStack[EventCursor].B);
      DrawX :=
          (Smallint(EventStack[EventCursor].A) mod BoardWidth
                  + Smallint(EventStack[EventCursor].A) div BoardWidth * BoardWidth)
              * Image6.Width
              mod (Image6.Width * BoardWidth);
      DrawY :=
          ((Smallint(EventStack[EventCursor].A) mod BoardWidth
                      + Smallint(EventStack[EventCursor].A) div BoardWidth * BoardWidth)
                  * Image6.Height
                  div (Image6.Height * BoardWidth))
              * Image6.Height;
      ImageList1.Draw(
          MapBitmap1.Canvas,
          DrawX,
          DrawY,
          Maps[Hero.floor, Smallint(EventStack[EventCursor].A) + MapTileOffset] - 1
      );
      GraphicTile := Smallint(EventStack[EventCursor].B);
      imagework;
      ImageList1.Draw(
          MapBitmap2.Canvas,
          DrawX,
          DrawY,
          Maps[Hero.floor, Smallint(EventStack[EventCursor].A) + MapTileOffset] - 1 + DoorOpened
      );
      MainForm.Canvas.Draw(UiSpan, UiStep, MapBitmap1);
    end;
    Ord(evHeroAttack):
    begin
      NeighborIndex := 0;
      case MonsterIndex of
        Ord(monsterZombie), Ord(monsterZombieKnight):
          if Hero.cross = 1 then
            NeighborIndex := 1;
        Ord(monsterVampire):
          if Hero.cross = 1 then
            NeighborIndex := 1;
        Ord(monsterDragon):
          if Hero.dragon_slayer = 1 then
            NeighborIndex := 1;
      end;
      case NeighborIndex of
        0:
          ScratchIndex :=
              Monsters[MonsterIndex].Defense * (Hero.cycle_factor_minus_one + 1) - Hero.attack;
        1:
          ScratchIndex :=
              Monsters[MonsterIndex].Defense * (Hero.cycle_factor_minus_one + 1) - Hero.attack * 2;
      end;
      if ScratchIndex > 0 then
        ScratchIndex := 0;
      BattleHP := BattleHP + ScratchIndex;
      if BattleHP < 0 then
        BattleHP := 0;
      Memo5.Text := IntToStr(BattleHP);
    end;
    Ord(evEnemyAttack):
    begin
      ScratchIndex :=
          Hero.defense - Monsters[MonsterIndex].Attack * (Hero.cycle_factor_minus_one + 1);
      if ScratchIndex > 0 then
        ScratchIndex := 0;
      Hero.hp := Hero.hp + ScratchIndex;
      if Hero.hp < 0 then
        Hero.hp := 0;
      Memo1.Text := IntToStr(Hero.hp);
    end;
    Ord(evDefeat):
    begin
      ImageList1.Draw(
          MapBitmap1.Canvas,
          DrawX,
          DrawY,
          Maps[Hero.floor, Hero.y * BoardWidth + Hero.x + MapTileOffset] - 1
      );
      GraphicTile := Maps[Hero.floor, Hero.y * BoardWidth + Hero.x + MapTileOffset];
      imagework;
      ImageList1.Draw(
          MapBitmap2.Canvas,
          DrawX,
          DrawY,
          Maps[Hero.floor, Hero.y * BoardWidth + Hero.x + MapTileOffset] - 1 + DoorOpened
      );
      if Hero.music_track <> 0 then
      begin
        MediaPlayer5.Close;
        Hero.music_track := 14;
        soundplay;
      end;
      Timer2.Enabled := False;
      EventPaused := 1;
      Hero.Word48 := 1;
      DialogueStage := 9;
      GameplayHintIndex := 30;
      zyouout;
    end;
    Ord(evRefreshStatus):
    begin
      if Smallint(EventStack[EventCursor].A) <> 0 then
        TileClass := Smallint(EventStack[EventCursor].A);
      disp;
    end;
    Ord(evAwardGold):
    begin
      Hero.gold := Hero.gold + Smallint(EventStack[EventCursor].A) * (Hero.lucky_gold + 1);
      disp;
    end;
    Ord(evShowPanels):
    begin
      Image2.Visible := True;
      Image3.Visible := True;
      keydisplay;
      itemdisp;
    end;
    Ord(evOverlay):
    begin
      TargetRect := Rect(0, 0, Image6.Width, Image6.Height);
      SourceRect := TargetRect;
      WorkBitmap1.Height := Image6.Height;
      WorkBitmap1.Width := Image6.Width;
      WorkBitmap2.Height := WorkBitmap1.Height;
      WorkBitmap2.Width := WorkBitmap1.Width;
      WorkBitmap3.Height := WorkBitmap1.Height;
      WorkBitmap3.Width := WorkBitmap1.Width;
      WorkBitmap1.Canvas.CopyMode := cmSrcCopy;
      WorkBitmap2.Canvas.CopyMode := cmSrcCopy;
      WorkBitmap3.Canvas.CopyMode := cmSrcCopy;
      ImageList1.Draw(WorkBitmap3.Canvas, 0, 0, Smallint(EventStack[EventCursor].B) - 1);
      ImageList1.Draw(WorkBitmap1.Canvas, 0, 0, Smallint(EventStack[EventCursor - 1].A) - 1);
      ImageList1.Draw(WorkBitmap2.Canvas, 0, 0, Smallint(EventStack[EventCursor - 1].B) - 1);
      kasanegaki;
      DrawX := Smallint(EventStack[EventCursor].A) mod BoardWidth * Image6.Width;
      DrawY := Smallint(EventStack[EventCursor].A) div BoardWidth * Image6.Height;
      MapBitmap1.Canvas.Draw(DrawX, DrawY, WorkBitmap1);
      ImageList1.Draw(WorkBitmap3.Canvas, 0, 0, Smallint(EventStack[EventCursor].B) - 1);
      GraphicTile := Smallint(EventStack[EventCursor - 1].A);
      imagework;
      ImageList1
          .Draw(WorkBitmap1.Canvas, 0, 0, Smallint(EventStack[EventCursor - 1].A) - 1 + DoorOpened);
      GraphicTile := Smallint(EventStack[EventCursor - 1].B);
      imagework;
      ImageList1
          .Draw(WorkBitmap2.Canvas, 0, 0, Smallint(EventStack[EventCursor - 1].B) - 1 + DoorOpened);
      kasanegaki;
      DrawX := Smallint(EventStack[EventCursor].A) mod BoardWidth * Image6.Width;
      DrawY := Smallint(EventStack[EventCursor].A) div BoardWidth * Image6.Height;
      MapBitmap2.Canvas.Draw(DrawX, DrawY, WorkBitmap1);
      MainForm.Canvas.Draw(UiSpan, UiStep, MapBitmap1);
    end;
    Ord(evDialogue):
    begin
      Timer2.Enabled := False;
      EventPaused := 1;
      DialogueStage := Smallint(EventStack[EventCursor].A) + DialogueStageOffset;
      DialogueSpeech := Smallint(EventStack[EventCursor].A);
      zyouout;
    end;
    Ord(evSceneAction):
    begin
      case Smallint(EventStack[EventCursor].A) of
        1:
        begin
          Dec(EventCursor);
          openning31;
          Inc(EventCursor);
        end;
        2:
        begin
          Dec(EventCursor);
          ScratchIndex := 27;
          Maps[Hero.floor, 29] := tileZeno;
          zenolivework;
          Inc(EventCursor);
        end;
        3:
        begin
          Dec(EventCursor);
          madoushi2;
          Inc(EventCursor);
        end;
        4:
        begin
          ScratchIndex := Smallint(EventStack[EventCursor].B);
          if GameOptions[optionDisplaySize] = display800x500 then
            ScratchIndex := ScratchIndex * 5 div 4;
          DoorOpened := 0;
          banpaiawork;
          DrawX := Image6.Width * 4;
          DrawY := Image6.Height * 4;
          MapBitmap1.Canvas.Draw(DrawX, DrawY, WorkBitmap1);
          DoorOpened := 1;
          banpaiawork;
          DrawX := Image6.Width * 4;
          DrawY := Image6.Height * 4;
          MapBitmap2.Canvas.Draw(DrawX, DrawY, WorkBitmap1);
          MainForm.Canvas.Draw(UiSpan, UiStep, MapBitmap1);
          WorkBitmap1.Height := Image6.Height;
          WorkBitmap1.Width := Image6.Width;
          WorkBitmap1.Canvas.CopyMode := cmSrcCopy;
          WorkBitmap2.Canvas.CopyMode := cmSrcCopy;
          WorkBitmap3.Canvas.CopyMode := cmSrcCopy;
        end;
        5:
        begin
          Dec(EventCursor);
          moncheck;
          Inc(EventCursor);
        end;
        6:
        begin
          Image23.ShowHint := False;
          Image23.Visible := False;
          Dec(EventCursor);
          if Hero.cycle_factor_minus_one = 0 then
          begin
            Hero.cycle_factor_minus_one := 43;
            gameover;
            Inc(EventCursor);
          end
          else
          begin
            Hero.later_cycle := 1;
            gameover;
            Inc(EventCursor);
          end;
        end;
        7:
        begin
          if Hero.music_track <> 0 then
          begin
            MediaPlayer5.Close;
            Hero.music_track := 11;
            soundplay;
          end;
          Timer1.Enabled := False;
          WorkBitmap1.Height := Image6.Height * BoardWidth;
          WorkBitmap1.Width := Image6.Width * BoardWidth;
          WorkBitmap2.Height := WorkBitmap1.Height;
          WorkBitmap2.Width := WorkBitmap1.Width;
          WorkBitmap3.Height := WorkBitmap1.Height;
          WorkBitmap3.Width := WorkBitmap1.Width;
          WorkBitmap1.Canvas.CopyMode := cmSrcCopy;
          WorkBitmap2.Canvas.CopyMode := cmSrcCopy;
          WorkBitmap3.Canvas.CopyMode := cmSrcCopy;
          if Hero.cycle_factor_minus_one = 0 then
            Image1.Picture.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\title05.bmp')
          else
            Image1.Picture.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\title05R.bmp');
          Image19.ShowHint := False;
          Image20.ShowHint := False;
        end;
        8: yusyahyouji;
        9: yusyahyouji1;
        10:
        begin
          Dec(EventCursor);
          taisen2;
          Inc(EventCursor);
        end;
        11:
        begin
          StrikeCount := 0;
          Hero.floor := Smallint(EventStack[EventCursor].B);
          mhyouji;
          disp;
          if Hero.floor = 50 then
          begin
            Hero.Word48 := 0;
            Hero.x := Maps[Hero.floor, 0] mod BoardWidth;
            Hero.y := Maps[Hero.floor, 0] div BoardWidth;
            FlightCell := Hero.y * BoardWidth + Hero.x;
            DrawX := Image6.Width * FlightCell mod (Image6.Width * BoardWidth);
            DrawY := (Image6.Height * FlightCell div (Image6.Height * BoardWidth)) * Image6.Height;
            Hero.facing := Ord(hfUp);
            yusyahyouji1;
          end;
        end;
        12: openning9;
        13: Timer1.Enabled := False;
        14:
        begin
          BitBtn1.Visible := False;
          BitBtn2.Visible := False;
          BitBtn3.Visible := False;
          BitBtn4.Visible := False;
          Memo1.Visible := False;
          Memo2.Visible := False;
          Memo3.Visible := False;
          Memo4.Visible := False;
          Memo5.Visible := False;
          Memo6.Visible := False;
          Memo7.Visible := False;
          Memo8.Visible := False;
          Memo9.Visible := False;
          Memo10.Visible := False;
          Memo11.Visible := False;
          Memo12.Visible := False;
          if Image4.Visible = True then
            Image4.Visible := False;
          if Image5.Visible = True then
            Image5.Visible := False;
          if Image6.Visible = True then
            Image6.Visible := False;
          if Image7.Visible = True then
            Image7.Visible := False;
          if Image8.Visible = True then
            Image8.Visible := False;
          if Image9.Visible = True then
            Image9.Visible := False;
          if Image10.Visible = True then
            Image10.Visible := False;
          if Image11.Visible = True then
            Image11.Visible := False;
          if Image12.Visible = True then
            Image12.Visible := False;
          if Image13.Visible = True then
            Image13.Visible := False;
          if Image14.Visible = True then
            Image14.Visible := False;
          if Image15.Visible = True then
            Image15.Visible := False;
          if Image16.Visible = True then
            Image16.Visible := False;
          if Image17.Visible = True then
            Image17.Visible := False;
          if Image18.Visible = True then
            Image18.Visible := False;
          if Image19.Visible = True then
            Image19.Visible := False;
          if Image20.Visible = True then
            Image20.Visible := False;
          if Image31.Visible = True then
            Image31.Visible := False;
          if Image32.Visible = True then
            Image32.Visible := False;
        end;
        15:
        begin
          TargetRect := Rect(0, 0, ClientWidth, ClientHeight - Edit8.Height);
          FrameBitmap.Canvas.CopyRect(TargetRect, MainForm.Canvas, TargetRect);
        end;
      end;
    end;
    Ord(evMoveMonster): monidou;
    Ord(evDoorFrame): dooropen;
    Ord(evHeroAttackOverlay):
    begin
      TargetRect := Rect(0, 0, Image6.Width, Image6.Height);
      WorkBitmap1.Height := Image6.Height;
      WorkBitmap1.Width := Image6.Width;
      WorkBitmap2.Height := WorkBitmap1.Height;
      WorkBitmap2.Width := WorkBitmap1.Width;
      WorkBitmap3.Height := WorkBitmap1.Height;
      WorkBitmap3.Width := WorkBitmap1.Width;
      WorkBitmap1.Canvas.CopyMode := cmSrcCopy;
      WorkBitmap2.Canvas.CopyMode := cmSrcCopy;
      WorkBitmap3.Canvas.CopyMode := cmSrcCopy;
      ImageList1.Draw(WorkBitmap3.Canvas, 0, 0, Smallint(EventStack[EventCursor].B) - 1);
      ImageList1.Draw(WorkBitmap1.Canvas, 0, 0, Smallint(EventStack[EventCursor - 1].A) - 1);
      ImageList1.Draw(WorkBitmap2.Canvas, 0, 0, Smallint(EventStack[EventCursor - 1].B) - 1);
      WorkBitmap2.Canvas.CopyMode := cmSrcPaint;
      WorkBitmap2.Canvas.CopyRect(TargetRect, WorkBitmap3.Canvas, TargetRect);
      WorkBitmap2.Canvas.CopyMode := cmSrcCopy;
      ImageList1.Draw(WorkBitmap3.Canvas, 0, 0, Smallint(EventStack[EventCursor].B) - 1);
      WorkBitmap3.Canvas.CopyMode := cmNotSrcCopy;
      WorkBitmap3.Canvas.CopyRect(TargetRect, WorkBitmap3.Canvas, TargetRect);
      WorkBitmap3.Canvas.CopyMode := cmSrcCopy;
      WorkBitmap1.Canvas.CopyMode := cmSrcPaint;
      WorkBitmap1.Canvas.CopyRect(TargetRect, WorkBitmap3.Canvas, TargetRect);
      WorkBitmap1.Canvas.CopyMode := cmSrcAnd;
      WorkBitmap1.Canvas.CopyRect(TargetRect, WorkBitmap2.Canvas, TargetRect);
      WorkBitmap1.Canvas.CopyMode := cmSrcCopy;
      DrawX := Smallint(EventStack[EventCursor].A) mod BoardWidth * Image6.Width;
      DrawY := Smallint(EventStack[EventCursor].A) div BoardWidth * Image6.Height;
      MapBitmap1.Canvas.Draw(DrawX, DrawY, WorkBitmap1);
      ImageList1.Draw(WorkBitmap3.Canvas, 0, 0, Smallint(EventStack[EventCursor].B) - 1);
      GraphicTile := Smallint(EventStack[EventCursor - 1].A);
      imagework;
      ImageList1
          .Draw(WorkBitmap1.Canvas, 0, 0, Smallint(EventStack[EventCursor - 1].A) - 1 + DoorOpened);
      GraphicTile := Smallint(EventStack[EventCursor - 1].B);
      imagework;
      ImageList1
          .Draw(WorkBitmap2.Canvas, 0, 0, Smallint(EventStack[EventCursor - 1].B) - 1 + DoorOpened);
      WorkBitmap2.Canvas.CopyMode := cmSrcPaint;
      WorkBitmap2.Canvas.CopyRect(TargetRect, WorkBitmap3.Canvas, TargetRect);
      WorkBitmap2.Canvas.CopyMode := cmSrcCopy;
      ImageList1.Draw(WorkBitmap3.Canvas, 0, 0, Smallint(EventStack[EventCursor].B) - 1);
      WorkBitmap3.Canvas.CopyMode := cmNotSrcCopy;
      WorkBitmap3.Canvas.CopyRect(TargetRect, WorkBitmap3.Canvas, TargetRect);
      WorkBitmap3.Canvas.CopyMode := cmSrcCopy;
      WorkBitmap1.Canvas.CopyMode := cmSrcPaint;
      WorkBitmap1.Canvas.CopyRect(TargetRect, WorkBitmap3.Canvas, TargetRect);
      WorkBitmap1.Canvas.CopyMode := cmSrcAnd;
      WorkBitmap1.Canvas.CopyRect(TargetRect, WorkBitmap2.Canvas, TargetRect);
      WorkBitmap1.Canvas.CopyMode := cmSrcCopy;
      DrawX := Smallint(EventStack[EventCursor].A) mod BoardWidth * Image6.Width;
      DrawY := Smallint(EventStack[EventCursor].A) div BoardWidth * Image6.Height;
      MapBitmap2.Canvas.Draw(DrawX, DrawY, WorkBitmap1);
      ScratchIndex :=
          Monsters[MonsterIndex].Defense * (Hero.cycle_factor_minus_one + 1) - Hero.attack;
      if ScratchIndex > 0 then
        ScratchIndex := 0;
      BattleHP := BattleHP + ScratchIndex;
      if BattleHP < 0 then
        BattleHP := 0;
      Memo5.Text := IntToStr(BattleHP);
      MainForm.Canvas.Draw(UiSpan, UiStep, MapBitmap1);
    end;
    Ord(evFloorMusic):
    begin
      MediaPlayer5.Close;
      soundcheck;
      soundplay;
    end;
    Ord(evChangeHP):
    begin
      Hero.hp := Hero.hp + Smallint(EventStack[EventCursor].A);
      if Hero.hp < 0 then
        Hero.hp := 0;
      Memo1.Text := IntToStr(Hero.hp);
      if Hero.hp = 0 then
      begin
        if Hero.music_track <> 0 then
        begin
          MediaPlayer5.Close;
          Hero.music_track := 14;
          soundplay;
        end;
        ImageList1.Draw(
            MapBitmap1.Canvas,
            DrawX,
            DrawY,
            Maps[Hero.floor, Hero.y * BoardWidth + Hero.x + MapTileOffset] - 1
        );
        GraphicTile := Smallint(EventStack[EventCursor].B);
        imagework;
        ImageList1.Draw(
            MapBitmap2.Canvas,
            DrawX,
            DrawY,
            Maps[Hero.floor, Hero.y * BoardWidth + Hero.x + MapTileOffset] - 1 + DoorOpened
        );
        EventPaused := 1;
        Hero.Word48 := 1;
        DialogueStage := 9;
        EventCursor := 1;
        GameplayHintIndex := 30;
        zyouout;
      end;
    end;
    Ord(evSetTileOnly):
      Maps[Hero.floor, Smallint(EventStack[EventCursor].A) + MapTileOffset] :=
          Byte(EventStack[EventCursor].B);
    Ord(evHalveHP):
    begin
      Hero.hp := Hero.hp div 2;
      if Hero.hp < 0 then
        Hero.hp := 0;
      Memo1.Text := IntToStr(Hero.hp);
      if Hero.hp = 0 then
      begin
        if Hero.music_track <> 0 then
        begin
          MediaPlayer5.Close;
          Hero.music_track := 14;
          soundplay;
        end;
        ImageList1.Draw(
            MapBitmap1.Canvas,
            DrawX,
            DrawY,
            Maps[Hero.floor, Hero.y * BoardWidth + Hero.x + MapTileOffset] - 1
        );
        GraphicTile := Smallint(EventStack[EventCursor].B);
        imagework;
        ImageList1.Draw(
            MapBitmap2.Canvas,
            DrawX,
            DrawY,
            Maps[Hero.floor, Hero.y * BoardWidth + Hero.x + MapTileOffset] - 1 + DoorOpened
        );
        EventPaused := 1;
        Hero.Word48 := 1;
        DialogueStage := 9;
        EventCursor := 1;
        GameplayHintIndex := 30;
        zyouout;
      end;
    end;
    Ord(evSetHeroWord):
      HeroWords[Smallint(EventStack[EventCursor].A)] := Smallint(EventStack[EventCursor].B);
    Ord(evWipe):
    begin
      DrawIndex := Smallint(EventStack[EventCursor].B);
      DrawX := RenderOrder[DrawIndex - 1] * Image6.Width mod (Image6.Width * BoardWidth);
      DrawY :=
          (RenderOrder[DrawIndex - 1] * Image6.Height div (Image6.Height * BoardWidth))
              * Image6.Height;
      case Smallint(EventStack[EventCursor].A) of
        0:
        begin
          if (Hero.effects_muted = 0) and (DrawIndex = 1) then
            MediaPlayer1.Play;
          ImageList1.Draw(MainForm.Canvas, UiSpan + DrawX, UiStep + DrawY, 158);
          if (Smallint(EventStack[EventCursor - 1].Opcode) = Ord(evWipe))
              and (EventStack[EventCursor - 1].A = 0) then
          begin
            Dec(EventCursor);
            DrawIndex := Smallint(EventStack[EventCursor].B);
            DrawX := RenderOrder[DrawIndex - 1] * Image6.Width mod (Image6.Width * BoardWidth);
            DrawY :=
                (RenderOrder[DrawIndex - 1] * Image6.Height div (Image6.Height * BoardWidth))
                    * Image6.Height;
            if (Hero.effects_muted = 0) and (DrawIndex = 1) then
              MediaPlayer1.Play;
            ImageList1.Draw(MainForm.Canvas, UiSpan + DrawX, UiStep + DrawY, 158);
          end;
        end;
        1:
        begin
          ImageList1.Draw(
              MapBitmap1.Canvas,
              DrawX,
              DrawY,
              Maps[Hero.floor, RenderOrder[DrawIndex - 1] + MapTileOffset] - 1
          );
          GraphicTile := Maps[Hero.floor, RenderOrder[DrawIndex - 1] + MapTileOffset];
          imagework;
          ImageList1.Draw(
              MapBitmap2.Canvas,
              DrawX,
              DrawY,
              Maps[Hero.floor, RenderOrder[DrawIndex - 1] + MapTileOffset] - 1 + DoorOpened
          );
          if RenderOrder[DrawIndex - 1] = Hero.y * BoardWidth + Hero.x then
            yusyahyouji1;
          ImageList1.Draw(
              MainForm.Canvas,
              UiSpan + DrawX,
              UiStep + DrawY,
              Maps[Hero.floor, RenderOrder[DrawIndex - 1] + MapTileOffset] - 1
          );
          if (Smallint(EventStack[EventCursor - 1].Opcode) = Ord(evWipe))
              and (EventStack[EventCursor - 1].A = 1) then
          begin
            Dec(EventCursor);
            DrawIndex := Smallint(EventStack[EventCursor].B);
            DrawX := RenderOrder[DrawIndex - 1] * Image6.Width mod (Image6.Width * BoardWidth);
            DrawY :=
                (RenderOrder[DrawIndex - 1] * Image6.Height div (Image6.Height * BoardWidth))
                    * Image6.Height;
            ImageList1.Draw(
                MapBitmap1.Canvas,
                DrawX,
                DrawY,
                Maps[Hero.floor, RenderOrder[DrawIndex - 1] + MapTileOffset] - 1
            );
            GraphicTile := Maps[Hero.floor, RenderOrder[DrawIndex - 1] + MapTileOffset];
            imagework;
            ImageList1.Draw(
                MapBitmap2.Canvas,
                DrawX,
                DrawY,
                Maps[Hero.floor, RenderOrder[DrawIndex - 1] + MapTileOffset] - 1 + DoorOpened
            );
            if RenderOrder[DrawIndex - 1] = Hero.y * BoardWidth + Hero.x then
              yusyahyouji1;
            ImageList1.Draw(
                MainForm.Canvas,
                UiSpan + DrawX,
                UiStep + DrawY,
                Maps[Hero.floor, RenderOrder[DrawIndex - 1] + MapTileOffset] - 1
            );
          end;
          if DrawIndex = 121 then
          begin
            timerin;
            Timer1.Enabled := True;
          end;
        end;
      end;
    end;
    Ord(evResetCycle):
    begin
      Hero.cycle_factor_minus_one := 0;
      Hero.later_cycle := 0;
      gameover;
    end;
  end;
  Dec(EventCursor);
end;

procedure TTSW10.timer2timer(Sender: TObject); { $0045265C }
begin
  if EventCursor >= 1 then
  begin
    stackwork;
    if EventCursor >= 1 then
      stackwork
    else
    begin
      Timer2.Enabled := False;
      if EventPaused = 0 then
        itemlive;
    end;
  end
  else
  begin
    Timer2.Enabled := False;
    if EventPaused = 0 then
      itemlive;
  end;
end;

procedure TTSW10.openning9; { Draw capture and ending raster frames. $00482E60 }
var
  I, J: Integer;
begin
  Timer1.Enabled := False;
  case Smallint(EventStack[EventCursor - 1].A) of
    0, 2:
    begin
      { Mask the captured frame into the title or opening picture. }
      if Smallint(EventStack[EventCursor].B) = 232 then
      begin
        Image23.Top := 0;
        Image23.Left := 0;
        Image23.Width := ClientWidth;
        Image23.Height := ClientHeight - Edit8.Height;
        if Image1.Visible = True then
          Image1.Visible := False;
        if Image2.Visible = True then
          Image2.Visible := False;
        if Image3.Visible = True then
          Image3.Visible := False;
      end;
      TargetRect := Rect(0, 0, ClientWidth, ClientHeight - Edit8.Height);
      SourceRect := TargetRect;
      WorkBitmap1.Free;
      WorkBitmap1 := TBitmap.Create;
      WorkBitmap2.Free;
      WorkBitmap2 := TBitmap.Create;
      WorkBitmap3.Free;
      WorkBitmap3 := TBitmap.Create;
      WorkBitmap1.Width := ClientWidth;
      WorkBitmap1.Height := ClientHeight - Edit8.Height;
      WorkBitmap2.Width := ClientWidth;
      WorkBitmap2.Height := ClientHeight - Edit8.Height;
      WorkBitmap3.Width := ClientWidth;
      WorkBitmap3.Height := ClientHeight - Edit8.Height;
      WorkBitmap1.Canvas.CopyRect(TargetRect, FrameBitmap.Canvas, TargetRect);
      case Smallint(EventStack[EventCursor - 1].A) of
        0: WorkBitmap2.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\open1.bmp');
        2: WorkBitmap2.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\open0.bmp');
      end;
      for I := 0 to 19 do
        for J := 0 to 12 do
          ImageList1.Draw(
              WorkBitmap3.Canvas,
              I * Image6.Width,
              J * Image6.Height,
              Smallint(EventStack[EventCursor].B) - 66
          );
      kasanegaki;
      MainForm.Canvas.Draw(0, 0, WorkBitmap1);
      if ((Smallint(EventStack[EventCursor].B) = 247)
              and (Smallint(EventStack[EventCursor - 1].A) = 0))
          or ((Smallint(EventStack[EventCursor].B) = 248)
              and (Smallint(EventStack[EventCursor - 1].A) = 2)) then
      begin
        case GameOptions[optionSpeed] of
          gameSpeedHigh: Timer2.Interval := 150;
          gameSpeedMiddle: Timer2.Interval := 250;
          gameSpeedLow: Timer2.Interval := 350;
        end;
        MapBitmap1.Free;
        MapBitmap1 := TBitmap.Create;
        MapBitmap1.Height := Image6.Height * BoardWidth;
        MapBitmap1.Width := Image6.Width * BoardWidth;
        Image23.Visible := False;
        if Smallint(EventStack[EventCursor - 1].A) = 2 then
        begin
          Image23.Width := Image1.Width + Image2.Width + Image3.Width;
          Image23.Height := Image1.Height;
          Image23.Picture.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\open0.bmp');
          Image23.Visible := True;
        end;
      end;
    end;
    1:
    begin
      { Reveal the capture text, then restore the individual gameplay controls. }
      if Smallint(EventStack[EventCursor].B) = 0 then
      begin
        WorkBitmap1.Width := ClientWidth;
        WorkBitmap1.Height := ClientHeight - Edit8.Height;
        WorkBitmap2.Width := ClientWidth;
        WorkBitmap2.Height := ClientHeight - Edit8.Height;
        TargetRect := Rect(0, 0, ClientWidth, ClientHeight - Edit8.Height);
        Image23.Width := Image1.Width + Image2.Width + Image3.Width;
        Image23.Height := Image1.Height;
        Image23.Picture.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\open1.bmp');
        WorkBitmap1.Canvas.CopyRect(TargetRect, Image23.Canvas, TargetRect);
        Image23.Picture.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\open2.bmp');
        WorkBitmap2.Canvas.CopyRect(TargetRect, Image23.Canvas, TargetRect);
        case GameOptions[optionSpeed] of
          gameSpeedHigh: Timer2.Interval := 30;
          gameSpeedMiddle: Timer2.Interval := 50;
          gameSpeedLow: Timer2.Interval := 70;
        end;
      end;
      TargetRect := Rect(0, 0, ClientWidth, Smallint(EventStack[EventCursor].B));
      WorkBitmap1.Canvas.CopyRect(TargetRect, WorkBitmap2.Canvas, TargetRect);
      MainForm.Canvas.Draw(0, 0, WorkBitmap1);
      if ((Smallint(EventStack[EventCursor].B) = 400) and (Image6.Width = 32))
          or ((Smallint(EventStack[EventCursor].B) = 500) and (Image6.Width = 40)) then
      begin
        Memo1.Visible := True;
        Memo2.Visible := True;
        Memo3.Visible := True;
        Memo4.Visible := True;
        Memo5.Visible := True;
        Memo6.Visible := True;
        Memo7.Visible := True;
        Memo8.Visible := True;
        Memo9.Visible := True;
        Memo10.Visible := True;
        Memo11.Visible := True;
        if MouseControl1.Checked = True then
        begin
          BitBtn1.Visible := True;
          BitBtn2.Visible := True;
          BitBtn3.Visible := True;
          BitBtn4.Visible := True;
        end;
        Image19.Visible := True;
        Image20.Visible := True;
        Image1.Picture.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\center.bmp');
        if Hero.cycle_factor_minus_one = 0 then
          Image2.Picture.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\left.bmp')
        else
          Image2.Picture.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\leftr.bmp');
        if Hero.cycle_factor_minus_one = 0 then
          Image3.Picture.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\right.bmp')
        else
          Image3.Picture.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\rightr.bmp');
        Image1.Visible := True;
        Image2.Visible := True;
        Image3.Visible := True;
        MonsterIndex := -1;
        monshyouji;
        keydisplay;
        itemdisp;
        Image4.Visible := True;
        Image5.Visible := True;
        Image6.Visible := True;
        Image7.Visible := True;
        Image8.Visible := True;
        Image9.Visible := True;
        Image10.Visible := True;
        Image11.Visible := True;
        Image12.Visible := True;
        Image13.Visible := True;
        Image14.Visible := True;
        Image15.Visible := True;
        Image16.Visible := True;
        Image17.Visible := True;
        Image18.Visible := True;
        case GameOptions[optionSpeed] of
          gameSpeedHigh: Timer2.Interval := 130;
          gameSpeedMiddle: Timer2.Interval := 200;
          gameSpeedLow: Timer2.Interval := 300;
        end;
      end;
    end;
    4:
    begin
      { Shrink the ending picture, keeping the original integer-division order. }
      Timer2.Interval := 100;
      TargetRect :=
          Rect(0, 0, Image1.Width + Image2.Width + Image3.Width, ClientHeight - Edit8.Height);
      SourceRect := Rect(0, 0, 640, 400);
      WorkBitmap1.LoadFromFile(Memo12.Lines[1] + '\data2\End20.bmp');
      TargetRect :=
          Rect(
              Smallint(EventStack[EventCursor].B) * 640 div 400 div 2,
              Smallint(EventStack[EventCursor].B) div 2,
              640 - Smallint(EventStack[EventCursor].B) div 2 * 640 div 400,
              400 - Smallint(EventStack[EventCursor].B) div 2
          );
      WorkBitmap2.Canvas.CopyMode := cmWhiteness;
      WorkBitmap2.Canvas.CopyRect(SourceRect, WorkBitmap2.Canvas, SourceRect);
      WorkBitmap2.Canvas.CopyMode := cmSrcCopy;
      WorkBitmap2.Canvas.CopyRect(TargetRect, WorkBitmap1.Canvas, SourceRect);
      TargetRect :=
          Rect(0, 0, Image1.Width + Image2.Width + Image3.Width, ClientHeight - Edit8.Height);
      MainForm.Canvas.CopyRect(TargetRect, WorkBitmap2.Canvas, SourceRect);
      if Smallint(EventStack[EventCursor].B) = 400 then
      begin
        Image23.Top := 0;
        Image23.Left := 0;
        Image23.Width := ClientWidth;
        Image23.Height := ClientHeight - Edit8.Height;
        Image23.Picture.LoadFromFile(Memo12.Lines[1] + '\data2\End26.bmp');
      end;
    end;
    5:
    begin
      { Wipe the embedded credits over the final ending picture. }
      Timer2.Interval := 60;
      TargetRect :=
          Rect(0, 0, Image1.Width + Image2.Width + Image3.Width, ClientHeight - Edit8.Height);
      if Smallint(EventStack[EventCursor].B) = 1 then
      begin
        WorkBitmap1.LoadFromFile(Memo12.Lines[1] + '\data2\End26.bmp');
        MainForm.Canvas.CopyRect(TargetRect, WorkBitmap1.Canvas, SourceRect);
      end;
      WorkBitmap2.Canvas.CopyRect(TargetRect, Image21.Canvas, TargetRect);
      TargetRect := Rect(0, 0, 640, Smallint(EventStack[EventCursor].B));
      if Smallint(EventStack[EventCursor].B) >= 400 then
        TargetRect := Rect(0, 0, 640, 400);
      WorkBitmap1.Canvas.CopyRect(TargetRect, WorkBitmap2.Canvas, TargetRect);
      case Image6.Width of
        32: MainForm.Canvas.Draw(0, 0, WorkBitmap1);
        40: MainForm.Canvas.Draw(80, 50, WorkBitmap1);
      end;
    end;
    6:
    begin
      { Each ending page retains the original literal path and drawing call. }
      Timer2.Interval := 450;
      TargetRect :=
          Rect(0, 0, Image1.Width + Image2.Width + Image3.Width, ClientHeight - Edit8.Height);
      SourceRect := Rect(0, 0, 640, 400);
      case Smallint(EventStack[EventCursor].B) of
        1:
        begin
          WorkBitmap1.LoadFromFile(Memo12.Lines[1] + '\data\open0.bmp');
          MainForm.Canvas.CopyRect(TargetRect, WorkBitmap1.Canvas, SourceRect);
        end;
        2:
        begin
          WorkBitmap1.LoadFromFile(Memo12.Lines[1] + '\data2\End05.bmp');
          MainForm.Canvas.CopyRect(TargetRect, WorkBitmap1.Canvas, SourceRect);
        end;
        3:
        begin
          WorkBitmap1.LoadFromFile(Memo12.Lines[1] + '\data2\End06.bmp');
          MainForm.Canvas.CopyRect(TargetRect, WorkBitmap1.Canvas, SourceRect);
        end;
        4:
        begin
          WorkBitmap1.LoadFromFile(Memo12.Lines[1] + '\data2\End07.bmp');
          MainForm.Canvas.CopyRect(TargetRect, WorkBitmap1.Canvas, SourceRect);
        end;
        5:
        begin
          WorkBitmap1.LoadFromFile(Memo12.Lines[1] + '\data2\End08.bmp');
          MainForm.Canvas.CopyRect(TargetRect, WorkBitmap1.Canvas, SourceRect);
        end;
        6:
        begin
          WorkBitmap1.LoadFromFile(Memo12.Lines[1] + '\data2\End09.bmp');
          MainForm.Canvas.CopyRect(TargetRect, WorkBitmap1.Canvas, SourceRect);
        end;
        7:
        begin
          WorkBitmap1.LoadFromFile(Memo12.Lines[1] + '\data2\End10.bmp');
          MainForm.Canvas.CopyRect(TargetRect, WorkBitmap1.Canvas, SourceRect);
        end;
        8:
        begin
          WorkBitmap1.LoadFromFile(Memo12.Lines[1] + '\data2\End11.bmp');
          MainForm.Canvas.CopyRect(TargetRect, WorkBitmap1.Canvas, SourceRect);
        end;
        9:
        begin
          WorkBitmap1.LoadFromFile(Memo12.Lines[1] + '\data2\End12.bmp');
          MainForm.Canvas.CopyRect(TargetRect, WorkBitmap1.Canvas, SourceRect);
        end;
        10:
        begin
          WorkBitmap1.LoadFromFile(Memo12.Lines[1] + '\data2\End13.bmp');
          MainForm.Canvas.CopyRect(TargetRect, WorkBitmap1.Canvas, SourceRect);
        end;
        11:
        begin
          WorkBitmap1.LoadFromFile(Memo12.Lines[1] + '\data2\End14.bmp');
          MainForm.Canvas.CopyRect(TargetRect, WorkBitmap1.Canvas, SourceRect);
        end;
        12:
        begin
          WorkBitmap1.LoadFromFile(Memo12.Lines[1] + '\data2\End15.bmp');
          MainForm.Canvas.CopyRect(TargetRect, WorkBitmap1.Canvas, SourceRect);
        end;
        13:
        begin
          WorkBitmap1.LoadFromFile(Memo12.Lines[1] + '\data2\End16.bmp');
          MainForm.Canvas.CopyRect(TargetRect, WorkBitmap1.Canvas, SourceRect);
        end;
        14:
        begin
          WorkBitmap1.LoadFromFile(Memo12.Lines[1] + '\data2\End17.bmp');
          MainForm.Canvas.CopyRect(TargetRect, WorkBitmap1.Canvas, SourceRect);
        end;
        15:
        begin
          WorkBitmap1.LoadFromFile(Memo12.Lines[1] + '\data2\End18.bmp');
          MainForm.Canvas.CopyRect(TargetRect, WorkBitmap1.Canvas, SourceRect);
        end;
        16:
        begin
          WorkBitmap1.LoadFromFile(Memo12.Lines[1] + '\data2\End19.bmp');
          MainForm.Canvas.CopyRect(TargetRect, WorkBitmap1.Canvas, SourceRect);
        end;
        17:
        begin
          WorkBitmap1.LoadFromFile(Memo12.Lines[1] + '\data2\End20.bmp');
          MainForm.Canvas.CopyRect(TargetRect, WorkBitmap1.Canvas, SourceRect);
        end;
      end;
    end;
    7:
    begin
      { Show the thank-you picture and its hint; start the ending music directly. }
      TargetRect :=
          Rect(0, 0, Image1.Width + Image2.Width + Image3.Width, ClientHeight - Edit8.Height);
      Image23.Top := 0;
      Image23.Left := 0;
      Image23.Width := Image1.Width + Image2.Width + Image3.Width;
      Image23.Height := ClientHeight - Edit8.Height;
      WorkBitmap2.Canvas.CopyRect(TargetRect, Image33.Canvas, TargetRect);
      Image23.Canvas.StretchDraw(TargetRect, WorkBitmap2);
      Image23.Hint := 'Thank you for playing!';
      Image23.ShowHint := True;
      Image23.Visible := True;
      if MainForm.BGMON1.Checked = True then
      begin
        MediaPlayer5.DeviceType := dtSequencer;
        MediaPlayer5.FileName := Memo12.Lines[1] + '\midi\b_014xgw.mid';
        MediaPlayer5.Open;
        MediaPlayer5.Notify := True;
        MediaPlayer5.Play;
      end;
    end;
    8:
    begin
      { Pause on the continuation panel until its click/key handler resumes. }
      Panel2.Visible := True;
      Image34.Visible := True;
      MainForm.KeyPreview := True;
      Timer2.Enabled := False;
    end;
  end;
end;

procedure TTSW10.timer4ontimer(
    Sender: TObject
); { Walk across open0, then start the first cycle after 20 frames. $00482A98 }
begin
  case StrikeCount of
    0..7: Timer4.Interval := 350;
    8..14: Timer4.Interval := 250;
    15..20: Timer4.Interval := 150;
  end;
  WorkBitmap1.Free;
  WorkBitmap2.Free;
  WorkBitmap3.Free;
  WorkBitmap1 := TBitmap.Create;
  WorkBitmap2 := TBitmap.Create;
  WorkBitmap3 := TBitmap.Create;
  TargetRect := Rect(0, 0, Image1.Width + Image2.Width + Image3.Width, Image1.Height);
  WorkBitmap1.Width := Image1.Width + Image2.Width + Image3.Width;
  WorkBitmap1.Height := Image1.Height;
  Image23.Width := Image1.Width + Image2.Width + Image3.Width;
  Image23.Height := Image1.Height;
  WorkBitmap1.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\open0.bmp');
  WorkBitmap2.Width := Image6.Width;
  WorkBitmap2.Height := Image6.Height;
  WorkBitmap3.Width := Image6.Width;
  WorkBitmap3.Height := Image6.Height;
  if StrikeCount mod 2 = 0 then
  begin
    ImageList1.Draw(WorkBitmap2.Canvas, 0, 0, 216);
    ImageList1.Draw(WorkBitmap3.Canvas, 0, 0, 209);
  end
  else
  begin
    ImageList1.Draw(WorkBitmap2.Canvas, 0, 0, 217);
    ImageList1.Draw(WorkBitmap3.Canvas, 0, 0, 211);
  end;
  { Keep the bottom/right corner fixed as the hero leaves the opening picture. }
  case GameOptions[optionDisplaySize] of
    display640x400: SourceRect := Rect(StrikeCount + 304, StrikeCount + 368, 336, 400);
    display800x500: SourceRect := Rect(StrikeCount + 380, StrikeCount + 460, 420, 500);
  end;
  TargetRect := Rect(0, 0, Image6.Width, Image6.Height);
  if StrikeCount <= 18 then
    kasanegaki;
  MainForm.Canvas.Draw(0, 0, WorkBitmap1);
  Inc(StrikeCount);
  if StrikeCount >= 20 then
  begin
    Timer4.Enabled := False;
    Hero.cycle_factor_minus_one := 0;
    Hero.later_cycle := 0;
    gameover;
  end;
end;
