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
  DrawX := (Index mod 11) * Form.Image6.Width;
  DrawY := (Index div 11) * Form.Image6.Height;
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
    DrawX := (Index mod 11) * Form.Image6.Width;
    DrawY := (Index div 11) * Form.Image6.Height;
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
  EventSummon(Self, ScratchIndex, 91);
end;

procedure TTSW10.madoushilivework; { Materialize four temporary guards. $00461EF4 }
begin
  EventSummonFour(Self, ScratchIndex, NeighborIndex, NeighborY, DamageMode);
end;

procedure TTSW10.madoushi2; { Materialize the eight 49F sorcerer guards. $00462560 }
const
  Guards: array[0..7] of Longint = (26, 37, 38, 39, 28, 17, 16, 15);
  Masks: array[0..7] of Longint = (182, 179, 177, 175, 173, 171, 169, 167);
var
  I, J: Longint;
begin
  timer2on;
  for I := 0 to 7 do
    Maps[Hero.floor, Guards[I] + 2] := 93;
  for I := 0 to 7 do
    for J := 0 to 7 do
    begin
      PushEvent(0, 6, 93);
      PushEvent(9, Guards[J], Masks[I]);
    end;
end;

{$I EventScenes.inc}

procedure TTSW10.mevent; { Dispatch scenes triggered by special road tiles. $0046397C }
begin
  itemdel;
  case Hero.floor of
    3: { Step onto the capture trigger, then summon Zeno. }
    begin
      idou;
      Maps[Hero.floor, Hero.y * 11 + Hero.x + 2] := 6;
      timer2on;
      PushEvent(10, 10, 0);
      EventWaits(4);
      EventSummon(Self, 70, 91);
      if Hero.music_track <> 0 then
      begin
        PushEvent(0, 0, 0);
        PushEvent(1, 6, 0);
      end;
    end;
    23: { Block the false route by turning the contacted road into a wall. }
    begin
      timer2on;
      PushEvent(0, 0, 0);
      PushEvent(2, 114, 0);
      PushEvent(0, 0, 0);
      PushEvent(6, ContactIndex, 8);
      PushEvent(0, 0, 0);
      PushEvent(1, 1, 0);
      EventWaits(2);
    end;
    32, 42, 48:
    begin
      timer2on;
      ichicheck;
    end; { Remote or stair scenes preserve the hero cell. }
    10, 15, 20, 24, 25, 30, 33, 38, 40, 43, 49:
    begin
      idou;
      if (Hero.floor <> 20) or (Hero.y * 11 + Hero.x = 82) then
      begin
        Maps[Hero.floor, Hero.y * 11 + Hero.x + 2] := 6;
        if Hero.music_track <> 0 then
        begin
          case Hero.floor of
            20: Hero.music_track := 16;
            25: Hero.music_track := 7;
            40: Hero.music_track := 18;
            49: Hero.music_track := 19;
          end;
        end;
        timer2on;
        ichicheck;
      end
      else
        itemlive;
    end;
  else
    itemlive;
  end;
end;

procedure TTSW10.toroad2; { Dissolve a bomb target into road. $0044BC34 }
var
  Mask, Underlying: Longint;
begin
  timer2on;
  Underlying := Maps[Hero.floor, ContactIndex + 2];
  PushEvent(17, ContactIndex, 6);
  Mask := 182;
  while Mask >= 166 do
  begin
    { The wait record supplies the old tile and road color to the overlay. }
    PushEvent(0, Underlying, 6);
    PushEvent(9, ContactIndex, Mask);
    PushEvent(0, 0, 0);
    PushEvent(1, 1, 0);
    Dec(Mask, 4);
  end;
end;

procedure TTSW10.openning31; { End capture in the 2F prison and reset equipment. $004653B8 }
begin
  if Hero.music_track <> 0 then
    if MediaPlayer5.DeviceID <> 0 then
      MediaPlayer5.Stop;
  Image1.Picture.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\center.bmp');
  if Hero.cycle_factor_minus_one = 0 then
  begin
    Image2.Picture.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\left.bmp');
    Image3.Picture.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\right.bmp');
    Hero.hp := 400;
    Hero.attack := 10;
    Hero.defense := 10;
  end
  else
  begin
    Image2.Picture.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\leftr.bmp');
    Image3.Picture.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\rightr.bmp');
    FillChar(Hero.hero_orb, 15 * SizeOf(Longint), 0);
  end;
  Image1.Visible := True;
  Image2.Visible := True;
  Image3.Visible := True;
  Hero.Word144 := 0;
  Hero.sacred_shield := 0;
  Hero.sword := 0;
  Hero.shield := 0;
  Hero.Word48 := 1;
  Hero.x := 2;
  Hero.y := 7;
  Hero.floor := 2;
  Hero.highest_floor := 2;
  HeroCell := Hero.y * 11 + Hero.x;
  timer2on;
  PushEvent(0, 0, 0);
  PushEvent(11, 8, 0);
  PushEvent(0, 0, 0);
  PushEvent(10, 3, 0);
  PushEvent(0, 0, 0);
  PushEvent(10, 2, 0);
  PushEvent(0, 0, 0);
  PushEvent(10, 1, 0);
  PushEvent(0, 0, 0);
  PushEvent(10, 1, 0);
  PushEvent(8, 0, 0);
  PushEvent(2, 0, 0);
  disp;
  Timer1.Enabled := False;
end;

procedure TTSW10.openning2; { Queue the capture presentation in reverse playback order. $00464048 }
var
  Group, Part, Frame, Groups, Height: Longint;
begin
  timer2on;
  Groups := 40;
  Height := 400;
  if Image6.Width = 40 then
  begin
    Groups := 50;
    Height := 500;
  end;
  PushEvent(11, 1, 0);
  PushEvent(0, 1, 0);
  PushEvent(11, 12, Height);
  for Group := Groups downto 0 do
    for Part := 5 downto 0 do
    begin
      PushEvent(0, 1, 0);
      PushEvent(11, 12, Group * 6 + 100 + Part);
    end;
  PushEvent(0, 1, 0);
  PushEvent(11, 12, 0);
  EventWaits(3);
  for Frame := 247 downto 232 do
  begin
    if Frame <> 247 then
      PushEvent(0, 0, 0);
    PushEvent(11, 12, Frame);
    PushEvent(0, 0, 0);
    PushEvent(1, 4, 0);
  end;
  PushEvent(0, 0, 0);
  PushEvent(11, 14, 0);
  EventWaits(25);
  PushEvent(11, 7, 0);
  PushEvent(0, 0, 0);
  PushEvent(8, 0, 0);
  PushEvent(0, 0, 0);
  PushEvent(6, 92, 6);
  EventWaits(4);
  PushEvent(0, 6, 191 + (Hero.facing - 1) * 8);
  PushEvent(9, 92, 192 + (Hero.facing - 1) * 8);
  PushEvent(0, 0, 0);
  PushEvent(1, 4, 0);
  EventWaits(5);
  PushEvent(10, 11, 0);
  EventSummonFour(Self, 81, 103, 91, 93);
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
  CancelBattle;
  Timer2.Enabled := False;
  Timer3.Enabled := False;
  Timer4.Enabled := False;
  EventPaused := False;
  RepeatEnabled := 0;
  EventCursor := 0;
  syokidata;
  syokidata2;
  itemlive;
  Timer1.Enabled := True;
  if BGMON1.Checked then
  begin
    soundcheck;
    soundplay;
  end;
end;

procedure TTSW10.append; { $00484DE8 }
begin
  if Hero.music_track <> 0 then
    if MediaPlayer5.DeviceID <> 0 then
      MediaPlayer5.Stop;
  EventHidePanels(Self);
  Timer2.Enabled := True;
end;

procedure TTSW10.timer3ontimer(Sender: TObject); { $00461760 }
begin
  if RepeatEnabled <> 1 then
  begin
    if RepeatEnabled = 0 then
      Timer3.Enabled := False;
    Exit;
  end;
  HeroCell := Hero.y * 11 + Hero.x;
  case FacingRequest of
    1:
      if Hero.y > 0 then
      begin
        ContactIndex := HeroCell - 11;
        handan;
      end;
    2:
      if Hero.x > 0 then
      begin
        ContactIndex := HeroCell - 1;
        handan;
      end;
    3:
      if Hero.x < 10 then
      begin
        ContactIndex := HeroCell + 1;
        handan;
      end;
    4:
      if Hero.y < 10 then
      begin
        ContactIndex := HeroCell + 11;
        handan;
      end;
    5:
      if Hero.floor < Hero.highest_floor then
      begin
        StrikeCount := 0;
        Button8Click(Sender);
      end;
    6:
      if Hero.floor > 1 then
      begin
        StrikeCount := 1;
        Button9Click(Sender);
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
    Hero.Word632 := 1;
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
    Hero.Word632 := 1;
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
    Hero.Word632 := 2;
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
    Hero.Word632 := 2;
  end;
end;

procedure TTSW10.K5Click(Sender: TObject);
begin
  K5.Checked := not K5.Checked;
  GameOptions[5] := Ord(K5.Checked);
end;

procedure TTSW10.touzoku; { Thief dialogue and tunnel scenes on 2F, 15F, 29F, 35F and 50F. $00465900 }
var
  Speech: Longint;
begin
  timer2on;
  case Hero.floor of
    2:
    begin
      if Hero.x = 0 then
      begin
        PushEvent(0, 0, 0);
        PushEvent(10, 5, 0);
      end
      else if (Hero.x = 2) or (Hero.x = 3) then
      begin
        PushEvent(0, 0, 0);
        PushEvent(10, 4, 0);
        PushEvent(0, 0, 0);
        PushEvent(2, 1, 0);
        PushEvent(0, 0, 0);
        PushEvent(13, 67, 7);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        if Hero.music_track <> 0 then
        begin
          soundcheck;
          soundplay;
        end;
      end
      else if (Hero.x = 9) or (Hero.x = 10) then
      begin
        Speech := 6;
        if Hero.floor2_thief_tunnel_started <> 0 then
          Speech := 7;
        PushEvent(0, 0, 0);
        PushEvent(10, Speech, 0);
      end;
    end;
    15:
    begin
      PushEvent(0, 0, 0);
      PushEvent(6, 6, 6);
      PushEvent(0, 0, 0);
      PushEvent(1, 2, 0);
      PushEvent(0, 0, 0);
      PushEvent(12, 7, 6);
      PushEvent(0, 0, 0);
      PushEvent(12, 8, 7);
      PushEvent(0, 0, 0);
      PushEvent(10, 18, 0);
      PushEvent(0, 0, 0);
      PushEvent(13, 7, 7);
      doorstackin;
      PushEvent(0, 0, 0);
      PushEvent(1, 1, 0);
      EventWaits(2);
    end;
    29:
    begin
      Speech := 28;
      if Hero.y * 11 + Hero.x = 27 then
        Speech := 27
      else if Hero.floor29_thief_heard <> 0 then
        Speech := 29;
      PushEvent(0, 0, 0);
      PushEvent(10, Speech, 0);
    end;
    35:
    begin
      Maps[2, 122] := 6;
      Speech := 32;
      if Hero.floor35_thief_heard <> 0 then
        Speech := 33;
      PushEvent(0, 0, 0);
      PushEvent(10, Speech, 0);
    end;
    50:
    begin
      PushEvent(0, 0, 0);
      PushEvent(10, 264, 0);
    end;
  end;
end;

procedure TTSW10.yousei; { Score and rank the hero at the 10F, 20F, 25F, 40F and 49F fairy checkpoints. $00478F0C }
var
  Scale, Keys, Score, Category, Target, Speech: Longint;
begin
  Scale := Hero.cycle_factor_minus_one + 1;
  Keys := Hero.yellow_keys + Hero.blue_keys * 2 + Hero.red_keys * 3;
  Score := 0;
  Category := 0;
  Target := ContactIndex;
  Speech := 0;
  case Hero.floor of
    10:
    begin
      Score :=
          (Hero.hp - 400 * Scale) div 50
              + 60
              + Hero.attack * 3
              - 157 * Scale
              + Hero.defense * 2
              + Keys;
      Category := 1;
      Target := 27;
      Speech := 16;
    end;
    20:
    begin
      Score :=
          (Hero.hp - 800 * Scale) div 100
              + 60
              + Hero.attack * 2
              - 228 * Scale
              + Hero.defense
              + Keys;
      Category := 2;
      Target := 49;
      Speech := 22;
    end;
    25, 49:
    begin
      Score :=
          (Hero.hp - 3000 * Scale) div 400
              + 60
              + (Hero.attack - 240 * Scale) div 2
              + (Hero.defense - 300 * Scale) div 3
              + Keys;
      if Hero.floor = 25 then
      begin
        Category := 3;
        Target := 71;
        Speech := 24;
      end
      else
      begin
        Category := 5;
        Target := 16;
        Speech := 47;
      end;
    end;
    40:
    begin
      Score :=
          (Hero.hp - 1600 * Scale) div 200
              + 60
              + Hero.attack
              - 152 * Scale
              + (Hero.defense - 198 * Scale) div 2
              + Keys;
      Category := 4;
      Target := 60;
      Speech := 40;
    end;
  else
    Exit;
  end;
  Inc(Hero.Word56);
  if Score < 0 then
    Score := 0;
  Hero.Word340 := Score;
  Hero.Word344 := 0;
  Hero.Word348 := Category;
  UpdateFairyRanking(Self, Category);
  timer2on;
  if Hero.music_track <> 0 then
  begin
    Hero.music_track := 12;
    soundplay;
    PushEvent(15, 0, 0);
  end;
  PushEvent(6, Target, 6);
  PushEvent(0, 0, 0);
  PushEvent(1, 2, 0);
  EventWaits(3);
  PushEvent(10, Speech, 0);
  EventWaits(2);
end;

procedure TTSW10.stackwork; { $004526C0 }
type
  THeroWords = array[0..170] of Longint;
var
  Command, Operand: TEventCommand;
  A, B, Multiplier, Hit, Index: Longint;
begin
  if (EventCursor <= 0) or EventPaused then
    Exit;
  Command := EventStack[EventCursor];
  Operand := EventStack[EventCursor - 1];
  A := Smallint(Command.A);
  B := Smallint(Command.B);
  case Command.Opcode of
    0: { Wait slot; A and B also supply operands to its paired animation command. };
    1:
    begin
      case A of
        1, 2, 3, 4, 7, 8, 9, 10: PlayEffect(Self, A);
        5:
          if Hero.music_track <> 0 then
            soundplay;
        6:
          if Hero.music_track <> 0 then
            if MediaPlayer5.DeviceID <> 0 then
              MediaPlayer5.Stop;
      end;
    end;
    2:
    begin
      if A <> 0 then
        TileClass := A;
      disp;
    end;
    3:
    begin
      Timer2.Enabled := False;
      EventPaused := True;
      Hero.Word48 := 1;
      DialogueStage := 9;
      TileClass := 30;
      zyouout;
    end;
    4:
    begin
      if (MonsterIndex >= 0) and (MonsterIndex <= 32) then
      begin
        Hit := Monsters[MonsterIndex].Attack * (Hero.cycle_factor_minus_one + 1) - Hero.defense;
        if Hit < 0 then
          Hit := 0;
        Dec(Hero.hp, Hit);
        if Hero.hp < 0 then
          Hero.hp := 0;
        Memo1.Text := IntToStr(Hero.hp);
      end;
    end;
    5, 14:
    begin
      if (MonsterIndex >= 0) and (MonsterIndex <= 32) then
      begin
        Multiplier := 1;
        if (Command.Opcode = 5) and not GameplayEnemyFirst then
        begin
          if ((MonsterIndex = 12) or (MonsterIndex = 13) or (MonsterIndex = 17))
              and (Hero.cross = 1) then
            Multiplier := 2;
          if (MonsterIndex = 19) and (Hero.dragon_slayer = 1) then
            Multiplier := 2;
        end;
        Hit :=
            Hero.attack * Multiplier
                - Monsters[MonsterIndex].Defense * (Hero.cycle_factor_minus_one + 1);
        if Hit < 0 then
          Hit := 0;
        Dec(BattleHP, Hit);
        if BattleHP < 0 then
          BattleHP := 0;
        Memo5.Text := IntToStr(BattleHP);
      end;
      if Command.Opcode = 14 then
        EventOverlay(Self, A, B, Operand.A, Operand.B);
    end;
    6, 17:
    begin
      if (A >= 0) and (A <= 120) then
      begin
        Maps[Hero.floor, A + 2] := Byte(B);
        if Command.Opcode = 6 then
        begin
          EventTile(Self, A, B);
          Canvas.Draw(UiSpan, UiStep, MapBitmap1);
        end;
      end;
    end;
    7:
    begin
      Inc(Hero.gold, A * (Hero.lucky_gold + 1));
      disp;
    end;
    8:
    begin
      Image2.Visible := True;
      Image3.Visible := True;
      keydisplay;
      itemdisp;
    end;
    9: EventOverlay(Self, A, B, Operand.A, Operand.B);
    10:
    begin
      Timer2.Enabled := False;
      EventPaused := True;
      DialogueStage := A + 10;
      zyouout;
    end;
    11:
    begin
      case A of
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
          Maps[Hero.floor, 29] := 91;
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
          ScratchIndex := B;
          banpaiawork;
          Canvas.Draw(UiSpan, UiStep, MapBitmap1);
        end;
        5:
        begin
          Dec(EventCursor);
          moncheck;
          Inc(EventCursor);
        end;
        6:
        begin
          Image23.Visible := False;
          Image23.Enabled := False;
          if Hero.cycle_factor_minus_one = 0 then
            Hero.cycle_factor_minus_one := 43
          else
            Hero.later_cycle := 1;
          gameover;
          Inc(EventCursor);
        end;
        7:
        begin
          if Hero.music_track <> 0 then
          begin
            Hero.music_track := 11;
            soundplay;
          end;
          Timer1.Enabled := False;
          if Hero.cycle_factor_minus_one = 0 then
            Image1.Picture.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\title05.bmp')
          else
            Image1.Picture.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\title05R.bmp');
          Image1.Visible := True;
          Image19.Enabled := False;
          Image20.Enabled := False;
        end;
        8:
        begin
          Hero.Word48 := 0;
          mhyouji;
          yusyahyouji1;
          Timer1.Enabled := True;
        end;
        9:
        begin
          Hero.Word48 := 0;
          yusyahyouji1;
        end;
        10:
        begin
          Dec(EventCursor);
          ContactIndex := B;
          taisen2;
          Inc(EventCursor);
        end;
        11:
        begin
          StrikeCount := 0;
          Hero.floor := B;
          mhyouji;
          disp;
          if Hero.floor = 50 then
          begin
            Hero.Word48 := 0;
            Hero.x := Maps[50, 0] mod 11;
            Hero.y := Maps[50, 0] div 11;
            HeroCell := Hero.y * 11 + Hero.x;
            Hero.facing := 4;
            yusyahyouji1;
          end;
        end;
        12: openning9;
        13:
        begin
          Hero.Word48 := 1;
          Timer1.Enabled := False;
        end;
        14: EventHidePanels(Self);
        15:
        begin
          FrameBitmap.Width := ClientWidth;
          FrameBitmap.Height := ClientHeight;
          FrameBitmap.Canvas.CopyRect(
              Rect(0, 0, ClientWidth, ClientHeight),
              Canvas,
              Rect(0, 0, ClientWidth, ClientHeight)
          );
        end;
      end;
    end;
    12: monidou;
    13: dooropen;
    15:
      if Hero.music_track <> 0 then
      begin
        if MediaPlayer5.DeviceID <> 0 then
          MediaPlayer5.Stop;
        soundcheck;
        soundplay;
      end;
    16, 19:
    begin
      if Command.Opcode = 16 then
        Inc(Hero.hp, A)
      else
        Hero.hp := Hero.hp div 2;
      if Hero.hp < 0 then
        Hero.hp := 0;
      Memo1.Text := IntToStr(Hero.hp);
      if Hero.hp = 0 then
      begin
        Timer2.Enabled := False;
        EventPaused := True;
        Hero.Word48 := 1;
        DialogueStage := 9;
        TileClass := 30;
        EventCursor := 1;
        zyouout;
      end;
    end;
    18: yusyaidou;
    20:
      if (A >= 0) and (A <= 170) then
        THeroWords(Pointer(@Hero)^)[A] := B;
    21:
    begin
      if (B >= 1) and (B <= 121) then
      begin
        Index := RenderOrder[B - 1];
        DrawX := (Index mod 11) * Image6.Width;
        DrawY := (Index div 11) * Image6.Height;
        if A = 0 then
          ImageList1.Draw(Canvas, UiSpan + DrawX, UiStep + DrawY, 158)
        else
        begin
          EventTile(Self, Index, Maps[Hero.floor, Index + 2]);
          Canvas.CopyRect(
              Rect(
                  UiSpan + DrawX,
                  UiStep + DrawY,
                  UiSpan + DrawX + Image6.Width,
                  UiStep + DrawY + Image6.Height
              ),
              MapBitmap1.Canvas,
              Rect(DrawX, DrawY, DrawX + Image6.Width, DrawY + Image6.Height)
          );
          if Index = Hero.y * 11 + Hero.x then
            yusyahyouji1;
          if B = 121 then
          begin
            timerin;
            Timer1.Enabled := True;
          end;
        end;
      end;
    end;
    22:
    begin
      Hero.cycle_factor_minus_one := 0;
      Hero.later_cycle := 0;
      gameover;
      Inc(EventCursor);
    end;
  else
    raise Exception.CreateFmt('Unknown event opcode %d', [Command.Opcode]);
  end;
  if EventCursor > 0 then
    Dec(EventCursor);
end;

procedure TTSW10.timer2timer(Sender: TObject); { $0045265C }
var
  I: Longint;
begin
  if EventPaused then
  begin
    Timer2.Enabled := False;
    Exit;
  end;
  for I := 1 to 2 do
  begin
    if BattleNeedsRefill then
      QueueNextBattleTurn(Self);
    if EventCursor > 0 then
      stackwork;
    if EventPaused then
    begin
      Timer2.Enabled := False;
      Exit;
    end;
    if EventCursor < 1 then
    begin
      EventCursor := 0;
      Timer2.Enabled := False;
      itemlive;
      Exit;
    end;
  end;
end;

procedure TTSW10.openning9; { Draw capture and ending raster frames. $00482E60 }
var
  Mode, Frame, Width, Height, X, Y, Mask: Longint;
  Destination: TRect;
  PicturePath: string;
  Picture: TBitmap;
begin
  Timer1.Enabled := False;
  Mode := Smallint(EventStack[EventCursor - 1].A);
  Frame := Smallint(EventStack[EventCursor].B);
  Width := Image1.Width + Image2.Width + Image3.Width;
  Height := Image1.Height;
  case Mode of
    0, 2: { Masked fade between the captured frame and title or opening picture. }
    begin
      if Frame = 232 then
      begin
        Image23.Left := 0;
        Image23.Top := 0;
        Image23.Width := Width;
        Image23.Height := Height;
        Image1.Visible := False;
        Image2.Visible := False;
        Image3.Visible := False;
      end;
      WorkBitmap1.Width := Width;
      WorkBitmap1.Height := Height;
      WorkBitmap2.Width := Width;
      WorkBitmap2.Height := Height;
      WorkBitmap3.Width := Width;
      WorkBitmap3.Height := Height;
      WorkBitmap1.Canvas.Draw(0, 0, FrameBitmap);
      if Mode = 0 then
        PicturePath := '\open1.bmp'
      else
        PicturePath := '\open0.bmp';
      WorkBitmap2.LoadFromFile(Memo12.Lines[1] + DataDirectory + PicturePath);
      Mask := Frame - 66;
      for X := 0 to 19 do
        for Y := 0 to 12 do
          ImageList1.Draw(WorkBitmap3.Canvas, X * Image6.Width, Y * Image6.Height, Mask);
      SourceRect := Rect(0, 0, Width, Height);
      TargetRect := SourceRect;
      ComposeSprite;
      Canvas.Draw(0, 0, WorkBitmap1);
      if Frame = 247 then
      begin
        timerin;
        MapBitmap1.Width := Image6.Width * 11;
        MapBitmap1.Height := Image6.Height * 11;
        Image23.Visible := False;
        if Mode = 2 then
        begin
          Image23.Picture.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\open0.bmp');
          Image23.Visible := True;
        end;
      end;
    end;
    1: { Wipe in the capture text, then restore the gameplay controls. }
    begin
      if Frame = 0 then
      begin
        Image23.Width := Width;
        Image23.Height := Height;
        Image23.Picture.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\open2.bmp');
        Image23.Visible := False;
        case GameOptions[3] of
          1: Timer2.Interval := 30;
          2: Timer2.Interval := 50;
          3: Timer2.Interval := 70;
        end;
      end;
      WorkBitmap1.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\open1.bmp');
      WorkBitmap2.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\open2.bmp');
      if Frame > Height then
        Frame := Height;
      Destination := Rect(0, 0, Width, Frame);
      WorkBitmap1.Canvas.CopyRect(Destination, WorkBitmap2.Canvas, Destination);
      Canvas.Draw(0, 0, WorkBitmap1);
      if Frame = Height then
      begin
        Image1.Picture.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\center.bmp');
        if Hero.cycle_factor_minus_one = 0 then
        begin
          Image2.Picture.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\left.bmp');
          Image3.Picture.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\right.bmp');
        end
        else
        begin
          Image2.Picture.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\leftr.bmp');
          Image3.Picture.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\rightr.bmp');
        end;
        Image1.Visible := True;
        Image2.Visible := True;
        Image3.Visible := True;
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
        Edit8.Visible := True;
        RichEdit1.Visible := True;
        if MouseControl1.Checked then
        begin
          BitBtn1.Visible := True;
          BitBtn2.Visible := True;
          BitBtn3.Visible := True;
          BitBtn4.Visible := True;
        end;
        MonsterIndex := -1;
        monshyouji;
        keydisplay;
        itemdisp;
        timerin;
      end;
    end;
    4: { Shrink the ending picture toward the center. }
    begin
      Timer2.Interval := 100;
      Picture := TBitmap.Create;
      try
        Picture.LoadFromFile(Memo12.Lines[1] + '\data2\End20.bmp');
        WorkBitmap1.Width := 640;
        WorkBitmap1.Height := 400;
        WorkBitmap1.Canvas.Brush.Color := clWhite;
        WorkBitmap1.Canvas.FillRect(Rect(0, 0, 640, 400));
        X := Frame * 640 div 400 div 2;
        Y := Frame div 2;
        Destination := Rect(X, Y, 640 - X, 400 - Y);
        WorkBitmap1.Canvas.CopyRect(Destination, Picture.Canvas, Rect(0, 0, 640, 400));
        Canvas.CopyRect(Rect(0, 0, Width, Height), WorkBitmap1.Canvas, Rect(0, 0, 640, 400));
        if Frame = 400 then
        begin
          Image23.Left := 0;
          Image23.Top := 0;
          Image23.Width := Width;
          Image23.Height := Height;
          Image23.Picture.LoadFromFile(Memo12.Lines[1] + '\data2\End26.bmp');
        end;
      finally
        Picture.Free;
      end;
    end;
    5: { Wipe in the credits from the embedded Image21 bitmap. }
    begin
      Timer2.Interval := 60;
      WorkBitmap1.LoadFromFile(Memo12.Lines[1] + '\data2\End26.bmp');
      WorkBitmap2.Width := 640;
      WorkBitmap2.Height := 400;
      WorkBitmap2.Canvas.CopyRect(Rect(0, 0, 640, 400), Image21.Canvas, Rect(0, 0, 640, 400));
      Y := Frame;
      if Y > 400 then
        Y := 400;
      WorkBitmap1.Canvas.CopyRect(Rect(0, 0, 640, Y), WorkBitmap2.Canvas, Rect(0, 0, 640, Y));
      if Image6.Width = 32 then
        Canvas.Draw(0, 0, WorkBitmap1)
      else
        Canvas.Draw(80, 50, WorkBitmap1);
    end;
    6: { Show the ending picture pages. }
    begin
      Timer2.Interval := 450;
      if Frame = 1 then
        PicturePath := Memo12.Lines[1] + '\data\open0.bmp'
      else
        PicturePath := Memo12.Lines[1] + '\data2\End' + Format('%.2d', [Frame + 3]) + '.bmp';
      WorkBitmap1.LoadFromFile(PicturePath);
      Canvas.CopyRect(
          Rect(0, 0, Width, Height),
          WorkBitmap1.Canvas,
          Rect(0, 0, WorkBitmap1.Width, WorkBitmap1.Height)
      );
    end;
    7: { Show the embedded thank-you picture and enable its continuation click. }
    begin
      Image23.Left := 0;
      Image23.Top := 0;
      Image23.Width := Width;
      Image23.Height := Height;
      Image23.Picture.Bitmap.Width := Width;
      Image23.Picture.Bitmap.Height := Height;
      Image23.Picture.Bitmap.Canvas.CopyRect(
          Rect(0, 0, Width, Height),
          Image33.Canvas,
          Rect(0, 0, Image33.Width, Image33.Height)
      );
      Image23.Hint := 'Thank you for playing!';
      Image23.Enabled := True;
      Image23.Visible := True;
      if BGMON1.Checked then
      begin
        Hero.music_track := 14;
        soundplay;
      end;
    end;
    8: { Show the continuation panel and pause the event timer. }
    begin
      Panel2.Visible := True;
      Image34.Visible := True;
      KeyPreview := True;
      Timer2.Enabled := False;
    end;
  end;
end;

procedure TTSW10.timer4ontimer(
    Sender: TObject
); { Walk across open0, then start the first cycle after 20 frames. $00482A98 }
var
  X, Y, Sprite, Mask: Longint;
begin
  if StrikeCount < 8 then
    Timer4.Interval := 350
  else if StrikeCount < 15 then
    Timer4.Interval := 250
  else if StrikeCount < 21 then
    Timer4.Interval := 150;
  WorkBitmap1.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\open0.bmp');
  WorkBitmap2.Width := Image6.Width;
  WorkBitmap2.Height := Image6.Height;
  WorkBitmap3.Width := Image6.Width;
  WorkBitmap3.Height := Image6.Height;
  Sprite := 216;
  Mask := 209;
  if Odd(StrikeCount) then
  begin
    Sprite := 217;
    Mask := 211;
  end;
  ImageList1.Draw(WorkBitmap2.Canvas, 0, 0, Sprite);
  ImageList1.Draw(WorkBitmap3.Canvas, 0, 0, Mask);
  X := StrikeCount + 304;
  Y := StrikeCount + 368;
  if Image6.Width = 40 then
  begin
    X := StrikeCount + 380;
    Y := StrikeCount + 460;
  end;
  SourceRect := Rect(X, Y, X + Image6.Width, Y + Image6.Height);
  TargetRect := Rect(0, 0, Image6.Width, Image6.Height);
  if StrikeCount < 19 then
    ComposeSprite;
  Canvas.Draw(0, 0, WorkBitmap1);
  Inc(StrikeCount);
  if StrikeCount >= 20 then
  begin
    Timer4.Enabled := False;
    Hero.cycle_factor_minus_one := 0;
    Hero.later_cycle := 0;
    gameover;
  end;
end;
