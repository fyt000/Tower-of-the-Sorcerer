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
    Require(not Form.Visible, 'Graphics form became visible');
    WriteLn('{"graphics_smoke_passed":true}');
  finally
    ReleaseGraphics;
    Form.Free;
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
