program GraphicsSmoke;
{$APPTYPE CONSOLE}
uses
  Windows,
  SysUtils,
  Classes,
  Graphics,
  Controls,
  Forms,
  GameForms,
  GameState,
  GameCore,
  GameContent,
  GameGraphics;
{$R ..\GameResources.res}

procedure Require(Value: Boolean; const Message: string);
begin
  if not Value then
    raise Exception.Create(Message);
end;

procedure SaveBitmap(Bitmap: Graphics.TBitmap; const Name: string);
begin
  Bitmap.SaveToFile(ParamStr(2) + '\' + Name + '.bmp');
end;

function JsonString(const Text: string): string;
var
  I: Integer;
begin
  Result := '"';
  for I := 1 to Length(Text) do
    case Text[I] of
      '"': Result := Result + '\"';
      '\': Result := Result + '\\';
      #13: Result := Result + '\r';
      #10: Result := Result + '\n';
    else
      Result := Result + Text[I];
    end;
  Result := Result + '"';
end;

procedure SaveAtlas(Form: TTSW10);
var
  Bitmap: Graphics.TBitmap;
  I: Integer;
begin
  Bitmap := Graphics.TBitmap.Create;
  try
    Bitmap.Width := Form.Image6.Width * 11;
    Bitmap.Height := Form.Image6.Height * 20;
    for I := 0 to Form.ImageList1.Count - 1 do
      Form
          .ImageList1
          .Draw(Bitmap.Canvas, (I mod 11) * Form.Image6.Width, (I div 11) * Form.Image6.Height, I);
    SaveBitmap(Bitmap, 'atlas1');
    Bitmap.Height := Form.Image6.Height * 15;
    for I := 0 to Form.ImageList3.Count - 1 do
      Form
          .ImageList3
          .Draw(Bitmap.Canvas, (I mod 11) * Form.Image6.Width, (I div 11) * Form.Image6.Height, I);
    SaveBitmap(Bitmap, 'atlas3');
    Bitmap.Width := Form.ImageList2.Width * 2;
    Bitmap.Height := Form.ImageList2.Height * 2;
    for I := 0 to Form.ImageList2.Count - 1 do
      Form.ImageList2.Draw(
          Bitmap.Canvas,
          (I mod 2) * Form.ImageList2.Width,
          (I div 2) * Form.ImageList2.Height,
          I
      );
    SaveBitmap(Bitmap, 'keys');
  finally
    Bitmap.Free;
  end;
end;

procedure Run;
const
  SlideOffsets: array[1..4] of Integer = (11, -1, 1, -11);
var
  Form: TTSW10;
  Cycle, Scale, Facing, I, Row: Integer;
  Control: TControl;
begin
  Require(ParamCount = 4, 'GraphicsSmoke asset root, output directory, scale and cycle required');
  Scale := StrToInt(ParamStr(3));
  Cycle := StrToInt(ParamStr(4));
  Application.Initialize;
  LoadGameContent;
  Form := TTSW10.Create(nil);
  MainForm := Form;
  try
    Require(not Form.Visible, 'Graphics form must remain hidden');
    Form.Memo12.Lines.Clear;
    Form.Memo12.Lines.Add(ParamStr(2));
    Form.Memo12.Lines.Add(ParamStr(1));
    Require(
        Pointer(Pointer(Longint(Form.Memo12) + $114)^) = Pointer(Form.Memo12.Lines),
        'English Memo.Lines layout'
    );
    Require(
        Pointer(Pointer(Longint(Form.ListBox2) + $FC)^) = Pointer(Form.ListBox2.Items),
        'English ListBox.Items layout'
    );
    WriteLn('{"referenced_vcl_fields_verified":true}');
    GameOptions[8] := Scale;
    Hero.cycle_factor_minus_one := Cycle;
    WriteLn(
        '{"seed_form":[',
        Form.Width,
        ',',
        Form.Height,
        ',',
        Form.ClientWidth,
        ',',
        Form.ClientHeight,
        '],"screen_width":',
        Screen.Width,
        '}'
    );
    for I := 0 to Form.ComponentCount - 1 do
      if Form.Components[I] is TControl then
      begin
        Control := TControl(Form.Components[I]);
        WriteLn(
            '{"control_seed":"',
            Control.Name,
            '","bounds":[',
            Control.Left,
            ',',
            Control.Top,
            ',',
            Control.Width,
            ',',
            Control.Height,
            ']}'
        );
      end;
    Form.syokidata0;
    WriteLn(
        '{"graphics_startup":true,"scale":',
        Scale,
        ',"cycle":',
        Cycle,
        ',"tile_width":',
        Form.Image6.Width,
        ',"tile_height":',
        Form.Image6.Height,
        ',"counts":[',
        Form.ImageList1.Count,
        ',',
        Form.ImageList3.Count,
        ',',
        Form.ImageList2.Count,
        '],"form":[',
        Form.Width,
        ',',
        Form.Height,
        ',',
        Form.ClientWidth,
        ',',
        Form.ClientHeight,
        '],"hidden":true}'
    );
    for I := 0 to Form.ComponentCount - 1 do
      if Form.Components[I] is TControl then
      begin
        Control := TControl(Form.Components[I]);
        WriteLn(
            '{"control":"',
            Control.Name,
            '","bounds":[',
            Control.Left,
            ',',
            Control.Top,
            ',',
            Control.Width,
            ',',
            Control.Height,
            ']}'
        );
      end;
    Require(Form.ImageList1.Count = 218, 'main atlas count');
    Require(Form.ImageList3.Count = 159, 'ending atlas count');
    Require(Form.ImageList2.Count = 4, 'key atlas count');
    SaveAtlas(Form);
    Hero.cycle_factor_minus_one := 0;
    InitializeCycle;
    SaveBitmap(Form.Image1.Picture.Bitmap, 'center');
    SaveBitmap(Form.Image2.Picture.Bitmap, 'left');
    SaveBitmap(Form.Image3.Picture.Bitmap, 'right');
    Hero.floor := 1;
    Form.mhyouji;
    SaveBitmap(MapBitmap1, 'floor1a');
    SaveBitmap(MapBitmap2, 'floor1b');
    Hero.floor := 49;
    Form.mhyouji;
    SaveBitmap(MapBitmap1, 'floor49a');
    SaveBitmap(MapBitmap2, 'floor49b');
    Hero.floor := 1;
    Hero.x := 6;
    Hero.y := 10;
    for Facing := 1 to 4 do
    begin
      Hero.facing := Facing;
      Form.mhyouji;
      Form.yusyahyouji1;
      SaveBitmap(MapBitmap1, 'hero' + IntToStr(Facing) + 'a');
      SaveBitmap(MapBitmap2, 'hero' + IntToStr(Facing) + 'b');
    end;
    Hero.cycle_factor_minus_one := Cycle;
    for Row := -1 to 32 do
    begin
      MonsterIndex := Row;
      Form.monshyouji;
      SaveBitmap(Form.Image31.Picture.Bitmap, 'monster' + IntToStr(Row));
      WriteLn(
          '{"monster":',
          Row,
          ',"labels":[',
          JsonString(Form.Memo8.Text),
          ',',
          JsonString(Form.Memo5.Text),
          ',',
          JsonString(Form.Memo6.Text),
          ',',
          JsonString(Form.Memo7.Text),
          '],"visible":',
          Ord(Form.Image31.Visible),
          '}'
      );
    end;
    { Both animation buffers must retain the original moving-monster frames. }
    Hero.floor := 1;
    for Facing := 1 to 4 do
    begin
      for I := 2 to 122 do
        Maps[1, I] := 6;
      Maps[1, 62] := 61;
      Form.mhyouji;
      EventCursor := 1;
      EventStack[1].Opcode := Ord(evMoveMonster);
      EventStack[1].A := 60;
      EventStack[1].B := 60 + SlideOffsets[Facing];
      Form.monidou;
      Require(
          (Maps[1, 62] = 6)
              and (Maps[1, 62 + SlideOffsets[Facing]] = 61)
              and (NeighborIndex = Form.Image6.Width)
              and (DoorOpened = 1),
          'Monster slide map and animation state'
      );
      SaveBitmap(MapBitmap1, 'slide' + IntToStr(Facing) + 'a');
      SaveBitmap(MapBitmap2, 'slide' + IntToStr(Facing) + 'b');
    end;
    { Four positions cover the bat convergence and its central reveal mask. }
    for Row := 0 to 1 do
      for I := 0 to 3 do
      begin
        DoorOpened := Row;
        ScratchIndex := I * Form.Image6.Width div 3;
        Form.banpaiawork;
        SaveBitmap(WorkBitmap1, 'vampire' + IntToStr(Row) + '-' + IntToStr(I));
      end;
    { Every door, wall, fence and road effect, including its final frame. }
    Form.speedhigh;
    EventCursor := 1;
    EventStack[1].Opcode := Ord(evDoorFrame);
    EventStack[1].A := 60;
    for Row := 1 to 12 do
      for I := 0 to 2 do
      begin
        if I = 0 then
          EventStack[0].B := 1
        else
          EventStack[0].B := I * 8;
        EventStack[1].B := Row;
        Form.dooropen;
        if Row = 5 then
          Require(Maps[1, 62] = 4, 'Closing wall map tile')
        else if Row = 8 then
          Require(Maps[1, 62] = 8, 'Closing gate map tile')
        else
          Require(Maps[1, 62] = 6, 'Opening map tile');
        if I = 2 then
          Require(Form.Timer2.Interval = 150, 'Door restores selected timer speed')
        else
          Require(Form.Timer2.Interval = 8, 'Door uses frame timer speed');
        if Row = 6 then
          SaveBitmap(WorkBitmap1, 'door' + IntToStr(Row) + '-' + IntToStr(I))
        else
          SaveBitmap(WorkBitmap3, 'door' + IntToStr(Row) + '-' + IntToStr(I));
      end;
    StrikeCount := 5;
    Form.timer4ontimer(nil);
    if GameOptions[8] = 0 then
      Require(
          (SourceRect.Left = 309)
              and (SourceRect.Top = 373)
              and (SourceRect.Right = 336)
              and (SourceRect.Bottom = 400),
          'Small opening sprite must shrink against the fixed bottom/right corner'
      )
    else
      Require(
          (SourceRect.Left = 385)
              and (SourceRect.Top = 465)
              and (SourceRect.Right = 420)
              and (SourceRect.Bottom = 500),
          'Large opening sprite must shrink against the fixed bottom/right corner'
      );
    Require((StrikeCount = 6) and (Form.Timer4.Interval = 350), 'Opening frame/timing');
    { The title fade ends one frame after the capture fade. }
    EventCursor := 1;
    EventStack[0].A := 2;
    EventStack[1].B := 247;
    GameOptions[3] := 1;
    Form.Timer2.Interval := 777;
    Form.openning9;
    Require(Form.Timer2.Interval = 777, 'Title fade must not finish at capture frame 247');
    EventStack[1].B := 248;
    Form.openning9;
    Require((Form.Timer2.Interval = 150) and Form.Image23.Visible, 'Title fade finishes at 248');
    EventStack[0].A := 1;
    EventStack[1].B := 0;
    Form.openning9;
    Require(Form.Timer2.Interval = 30, 'Capture wipe frame timing');
    Form.RichEdit1.Visible := False;
    Form.Image4.Visible := False;
    Form.Image18.Visible := False;
    if Scale = 0 then
      EventStack[1].B := 400
    else
      EventStack[1].B := 500;
    Form.openning9;
    Require(
        (Form.Timer2.Interval = 130)
            and Form.Image4.Visible
            and Form.Image18.Visible
            and not Form.RichEdit1.Visible,
        'Capture completion restores original controls and timing'
    );
    Require(not Form.Visible, 'Graphics form became visible');
    WriteLn('{"graphics_smoke_passed":true}');
  finally
    ReleaseGraphics;
    Form.Free;
    MainForm := nil;
  end;
end;

begin
  try
    Run;
  except
    on E: Exception do
    begin
      WriteLn('{"graphics_smoke_passed":false,"error":"', E.Message, '"}');
      Halt(1);
    end;
  end;
end.
