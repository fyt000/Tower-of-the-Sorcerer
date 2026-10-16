program UISmoke;
{$APPTYPE CONSOLE}
uses
  Windows,
  Messages,
  SysUtils,
  Classes,
  TypInfo,
  Graphics,
  Controls,
  Forms,
  StdCtrls,
  ExtCtrls,
  Menus,
  GameForms,
  GameState,
  GameCore,
  GameContent,
  GameGraphics;
{$R ..\GameResources.res}

type
  TFixturePainter = class
    Gameplay: Boolean;
    procedure Paint(Sender: TObject);
  end;

function FlushWindowCompositor: Longint; stdcall; external 'dwmapi.dll' name 'DwmFlush';
function UsePhysicalWindowPixels: BOOL; stdcall; external 'user32.dll' name 'SetProcessDPIAware';
function DisableCaptureTransitions(
    Wnd: HWND;
    Attribute: Longint;
    Value: Pointer;
    Bytes: Longint
): Longint; stdcall; external 'dwmapi.dll' name 'DwmSetWindowAttribute';

function OwnCapturePoint(Form: TForm; X, Y: Integer): Boolean;
var
  Wnd: HWND;
begin
  Wnd := WindowFromPoint(Form.ClientToScreen(Point(X, Y)));
  while (Wnd <> 0) and (Wnd <> Form.Handle) do
    Wnd := GetParent(Wnd);
  Result := Wnd = Form.Handle;
end;

function Quoted(const Text: string): string;
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
      if Ord(Text[I]) < 32 then
        Result := Result + '\u' + IntToHex(Ord(Text[I]), 4)
      else
        Result := Result + Text[I];
    end;
  Result := Result + '"';
end;

procedure Snapshot(Form: TForm; const Stage: string);
var
  I: Integer;
  Component: TComponent;
  Control: TControl;
  Info: PPropInfo;
  Font: TFont;
begin
  WriteLn(
      '{"stage":',
      Quoted(Stage),
      ',"form":',
      Quoted(Form.ClassName),
      ',"outer":[',
      Form.Width,
      ',',
      Form.Height,
      '],"client":[',
      Form.ClientWidth,
      ',',
      Form.ClientHeight,
      '],"ppi":',
      Form.PixelsPerInch,
      ',"screen_width":',
      Screen.Width,
      ',"position":[',
      Form.Left,
      ',',
      Form.Top,
      ']}'
  );
  for I := 0 to Form.ComponentCount - 1 do
  begin
    Component := Form.Components[I];
    if Component is TControl then
    begin
      Control := TControl(Component);
      Write(
          '{"stage":',
          Quoted(Stage),
          ',"form":',
          Quoted(Form.ClassName),
          ',"control":',
          Quoted(Control.Name),
          ',"class":',
          Quoted(Control.ClassName),
          ',"bounds":[',
          Control.Left,
          ',',
          Control.Top,
          ',',
          Control.Width,
          ',',
          Control.Height,
          '],"visible":',
          Ord(Control.Visible),
          ',"enabled":',
          Ord(Control.Enabled),
          ',"show_hint":',
          Ord(Control.ShowHint),
          ',"hint":',
          Quoted(Control.Hint)
      );
      Info := GetPropInfo(Control.ClassInfo, 'Font');
      if Info <> nil then
      begin
        Font := TFont(GetOrdProp(Control, Info));
        Write(
            ',"font":{"name":',
            Quoted(Font.Name),
            ',"size":',
            Font.Size,
            ',"height":',
            Font.Height,
            ',"color":',
            Font.Color,
            '}'
        );
      end;
      Info := GetPropInfo(Control.ClassInfo, 'Caption');
      if Info <> nil then
        Write(',"caption":', Quoted(GetStrProp(Control, Info)));
      Info := GetPropInfo(Control.ClassInfo, 'Color');
      if Info <> nil then
        Write(',"color":', GetOrdProp(Control, Info));
      Info := GetPropInfo(Control.ClassInfo, 'Text');
      if Info <> nil then
        Write(',"text":', Quoted(GetStrProp(Control, Info)));
      if Control is TWinControl then
        Write(',"window_visible":', Ord(IsWindowVisible(TWinControl(Control).Handle)));
      if Control is TMemo then
        Write(',"memo_text":', Quoted(TMemo(Control).Text));
      WriteLn('}');
    end
    else if Component is TMenuItem then
      with TMenuItem(Component) do
        WriteLn(
            '{"stage":',
            Quoted(Stage),
            ',"menu":',
            Quoted(Name),
            ',"caption":',
            Quoted(Caption),
            ',"checked":',
            Ord(Checked),
            ',"enabled":',
            Ord(Enabled),
            ',"visible":',
            Ord(Visible),
            '}'
        );
  end;
end;

procedure Capture(Form: TForm; const Name: string);
var
  Bitmap: TBitmap;
  OldLeft, OldTop: Integer;
  WasVisible: Boolean;
  Origin: TPoint;
  ScreenDC: HDC;
  Bounds: TRect;
  DisableTransitions: BOOL;
begin
  OldLeft := Form.Left;
  OldTop := Form.Top;
  WasVisible := Form.Visible;
  Form.OnActivate := nil;
  Form.Position := poDesigned;
  { This is an internal test of our own forms, not external app automation.
    Real on-screen pixels include modern edit/button rendering, which
    Delphi 2 PaintTo and WM_PRINT fail to capture reliably on this host. }
  Form.Left := 40;
  Form.Top := 40;
  DisableTransitions := True;
  DisableCaptureTransitions(Form.Handle, 3, @DisableTransitions, SizeOf(DisableTransitions));
  Form.Show;
  { A hidden launcher can override the first ShowWindow call via STARTUPINFO. }
  ShowWindow(Form.Handle, SW_SHOWNORMAL);
  Form.BringToFront;
  SetForegroundWindow(Form.Handle);
  Form.Update;
  Bitmap := TBitmap.Create;
  try
    Bitmap.Width := Form.ClientWidth;
    Bitmap.Height := Form.ClientHeight;
    Bitmap.Canvas.Brush.Color := clFuchsia;
    Bitmap.Canvas.FillRect(Rect(0, 0, Bitmap.Width, Bitmap.Height));
    { The timer paints after the normal child/control paint cycle. }
    if Pos('main-gameplay', Name) = 1 then
      MainForm.Timer1Timer(nil);
    if Pos('main-animation', Name) = 1 then
      MainForm.Timer1Timer(nil);
    GdiFlush;
    FlushWindowCompositor;
    if (GetForegroundWindow <> Form.Handle)
        or not OwnCapturePoint(Form, 2, 2)
        or not OwnCapturePoint(Form, Form.ClientWidth - 3, 2)
        or not OwnCapturePoint(Form, 2, Form.ClientHeight - 3)
        or not OwnCapturePoint(Form, Form.ClientWidth - 3, Form.ClientHeight - 3)
        or not OwnCapturePoint(Form, Form.ClientWidth div 2, Form.ClientHeight div 2) then
    begin
      WriteLn(
          '{"capture_skipped":',
          Quoted(Name),
          ',"reason":"test window was not foreground and unobstructed"}'
      );
      Exit;
    end;
    Origin := Form.ClientToScreen(Point(0, 0));
    ScreenDC := GetDC(0);
    try
      if not BitBlt(
          Bitmap.Canvas.Handle,
          0,
          0,
          Bitmap.Width,
          Bitmap.Height,
          ScreenDC,
          Origin.X,
          Origin.Y,
          SRCCOPY) then
        raise Exception.Create('client capture failed');
      Bitmap.SaveToFile(ParamStr(2) + '\' + Name + '.bmp');
      GetWindowRect(Form.Handle, Bounds);
      Bitmap.Width := Bounds.Right - Bounds.Left;
      Bitmap.Height := Bounds.Bottom - Bounds.Top;
      if not BitBlt(
          Bitmap.Canvas.Handle,
          0,
          0,
          Bitmap.Width,
          Bitmap.Height,
          ScreenDC,
          Bounds.Left,
          Bounds.Top,
          SRCCOPY) then
        raise Exception.Create('outer capture failed');
      Bitmap.SaveToFile(ParamStr(2) + '\' + Name + '-window.bmp');
    finally
      ReleaseDC(0, ScreenDC);
    end;
    WriteLn(
        '{"capture":',
        Quoted(Name),
        ',"client":[',
        Form.ClientWidth,
        ',',
        Form.ClientHeight,
        '],"outer":[',
        Bitmap.Width,
        ',',
        Bitmap.Height,
        ']}'
    );
  finally
    Bitmap.Free;
    if not WasVisible then
      Form.Hide;
    Form.Left := OldLeft;
    Form.Top := OldTop;
  end;
end;

procedure TFixturePainter.Paint(Sender: TObject);
begin
  { Paint only the staged fixture background. Gameplay frames are delivered
    through the animation timer after the normal child-control paint cycle. }
  MainForm.Canvas.Draw(0, 0, FrameBitmap);
end;

procedure ShowGameplayFixture;
begin
  { Visibility witness copied from syokidata2's Timer4-off branch. This is a
    staged visual fixture, not a replacement implementation of syokidata2. }
  with MainForm do
  begin
    Image1.Picture.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\center.bmp');
    Image1.Visible := True;
    Image2.Visible := True;
    Image3.Visible := True;
    Image19.Visible := True;
    Image20.Visible := True;
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
    mhyouji;
    yusyahyouji1;
    MonsterIndex := -1;
    monshyouji;
    keydisplay;
    itemdisp;
    disp;
    itemlive;
  end;
end;

procedure CheckMessageLine;
const
  FontSizes: array[0..3, 0..1] of Byte = ((8, 10), (9, 11), (10, 12), (12, 14));
var
  I: Integer;
  DC: HDC;
  SavedText: string;
  OldFont, OldMessageFont: Byte;
begin
  OldFont := GameOptions[0];
  OldMessageFont := GameOptions[1];
  SavedText := MainForm.Edit8.Text;
  DC := CreateCompatibleDC(0);
  if DC = 0 then
    raise Exception.Create('Cannot allocate the message-line color test context');
  try
    for I := 0 to 3 do
    begin
      GameOptions[0] := FontSizes[I, 0];
      GameOptions[1] := FontSizes[I, 1];
      ApplyFontLayout(MainForm);
      with MainForm.Edit8 do
      begin
        if not Enabled
            or not ReadOnly
            or TabStop
            or (GetWindowLong(Handle, GWL_STYLE) and WS_DISABLED <> 0) then
          raise Exception.Create('Message line must be enabled, read-only and outside tab order');
        if (Top <> MainForm.Image1.Height) or (Top + Height <> MainForm.ClientHeight) then
          raise Exception.Create('Message line does not fill the area below the artwork');
        if Color <> clGray then
          raise Exception.Create('Message line must use a fixed gray background');
        SendMessage(MainForm.Handle, WM_CTLCOLORSTATIC, DC, Handle);
        if (GetTextColor(DC) <> ColorToRGB(clWhite)) or (GetBkColor(DC) <> ColorToRGB(clGray)) then
          raise Exception.Create('Message line colors do not contrast');
        Text := 'You got a yellow key.';
        Perform(WM_CHAR, Ord('x'), 0);
        if Text <> 'You got a yellow key.' then
          raise Exception.Create('Message line accepted typed input');
      end;
    end;
    WriteLn('{"message_line_font_modes":4,"passed":true,"scale":', GameOptions[8], '}');
  finally
    DeleteDC(DC);
    MainForm.Edit8.Text := SavedText;
    GameOptions[0] := OldFont;
    GameOptions[1] := OldMessageFont;
    ApplyFontLayout(MainForm);
  end;
end;

procedure Run;
var
  Painter: TFixturePainter;
  Scale, I: Integer;
  Form: TForm;
  Action: TCloseAction;
begin
  if ParamCount <> 2 then
    raise Exception.Create('UISmoke requires asset root and output directory');
  { Physical-pixel capture is a test configuration; production stays intact. }
  UsePhysicalWindowPixels;
  Application.Initialize;
  LoadGameContent;
  MainForm := TTSW10.Create(nil);
  MainForm.Caption := 'Tower of the Sorcerer Ver1.2';
  AboutBox := TAboutBox.Create(nil);
  DataHolderForm := TForm4.Create(nil);
  Painter := TFixturePainter.Create;
  try
    MainForm.OnActivate := nil;
    AboutBox.OnActivate := nil;
    DataHolderForm.OnActivate := nil;
    for I := 0 to MainForm.ComponentCount - 1 do
      if MainForm.Components[I] is TTimer then
        TTimer(MainForm.Components[I]).Enabled := False;
    AboutBox.Timer1.Enabled := False;
    MainForm.Memo12.Lines.Clear;
    MainForm.Memo12.Lines.Add(ParamStr(2));
    MainForm.Memo12.Lines.Add(ParamStr(1));
    Snapshot(MainForm, 'main-seed');
    for Scale := 0 to 1 do
    begin
      GameOptions[8] := Scale;
      GameOptions[0] := 10;
      GameOptions[1] := 12;
      Hero.cycle_factor_minus_one := 0;
      InitializeCycle;
      Snapshot(MainForm, 'main-seed' + IntToStr(Scale));
      MainForm.ImageList1.Clear;
      MainForm.ImageList2.Clear;
      MainForm.ImageList3.Clear;
      MainForm.syokidata0;
      ApplyFontLayout(MainForm);
      CheckMessageLine;
      PrepareSceneGraphics(MainForm);
      FrameBitmap.SaveToFile(ParamStr(2) + '\title-frame' + IntToStr(Scale) + '.bmp');
      Snapshot(MainForm, 'main-title' + IntToStr(Scale));
      Painter.Gameplay := False;
      MainForm.OnPaint := Painter.Paint;
      Capture(MainForm, 'main-title' + IntToStr(Scale));
      Hero.hero_orb := 1;
      Hero.wisdom_orb := 1;
      Hero.flight_orb := 1;
      Hero.sword := 2;
      Hero.shield := 3;
      Hero.red_keys := 2;
      Hero.blue_keys := 3;
      Hero.yellow_keys := 10;
      ShowGameplayFixture;
      MainForm.Image19.Picture.Bitmap.SaveToFile(ParamStr(2) + '\sword' + IntToStr(Scale) + '.bmp');
      MainForm.Image20.Picture.Bitmap.SaveToFile(
          ParamStr(2) + '\shield' + IntToStr(Scale) + '.bmp'
      );
      MainForm.Image6.Picture.Bitmap.SaveToFile(
          ParamStr(2) + '\hero-orb' + IntToStr(Scale) + '.bmp'
      );
      MainForm.keydisplay;
      MainForm.Image32.Picture.Bitmap.SaveToFile(
          ParamStr(2) + '\key-display' + IntToStr(Scale) + '.bmp'
      );
      AnimationFrame := True;
      KeysPainted := 0;
      Painter.Gameplay := True;
      Capture(MainForm, 'main-gameplay' + IntToStr(Scale));
      Capture(MainForm, 'main-animation' + IntToStr(Scale));
      Snapshot(MainForm, 'main-gameplay' + IntToStr(Scale));
      MainForm.Show;
      MainForm.img6work;
      Snapshot(MainForm, 'orb-open' + IntToStr(Scale));
      Capture(MainForm, 'orb-open' + IntToStr(Scale));
      MainForm.Button36Click(nil);
      Snapshot(MainForm, 'orb-close' + IntToStr(Scale));
      MainForm.Hide;
      MainForm.OnPaint := nil;
      ReleaseGraphics;
    end;
    for I := 0 to 2 do
    begin
      MainForm.Small1.Checked := I = 1;
      MainForm.tiny1.Checked := I = 2;
      Snapshot(AboutBox, 'about-seed' + IntToStr(I));
      AboutBox.formactivate(nil);
      Snapshot(AboutBox, 'about' + IntToStr(I));
      Capture(AboutBox, 'about' + IntToStr(I));
      AboutBox.Timer1.Enabled := False;
    end;
    { A real focus target requires a visible window. The test window
      is offscreen; no game activation, save/settings writes or campaign input. }
    DataHolderForm.Left := -30000;
    DataHolderForm.Top := -30000;
    DataHolderForm.Position := poDesigned;
    DataHolderForm.Show;
    for I := 0 to 2 do
    begin
      MainForm.Small1.Checked := I = 1;
      MainForm.tiny1.Checked := I = 2;
      Snapshot(DataHolderForm, 'holder-seed' + IntToStr(I));
      DataHolderForm.form4activate(nil);
      if DataHolderForm.ActiveControl <> DataHolderForm.Button2 then
        raise Exception.Create('data-holder focus target');
      Snapshot(DataHolderForm, 'holder' + IntToStr(I));
      Capture(DataHolderForm, 'holder' + IntToStr(I));
    end;
    Action := caNone;
    DataHolderForm.form4onclose(nil, Action);
    if DataHolderForm.ModalResult <> 1 then
      raise Exception.Create('Data-holder close result');
    DataHolderForm.Hide;
    Form := TForm2.Create(nil);
    try
      Snapshot(Form, 'ranking-design-only');
      Capture(Form, 'ranking-design-only');
    finally
      Form.Free;
    end;
    Form := TOKBottomDlg.Create(nil);
    try
      Snapshot(Form, 'template-design-only');
      Capture(Form, 'template-design-only');
    finally
      Form.Free;
    end;
    WriteLn('{"ui_smoke_passed":true,"reference_window_pixels_verified":false}');
  finally
    ReleaseGraphics;
    Painter.Free;
    DataHolderForm.Free;
    AboutBox.Free;
    MainForm.Free;
  end;
end;

begin
  try
    Run;
  except
    on E: Exception do
    begin
      WriteLn('{"ui_smoke_passed":false,"error":', Quoted(E.Message), '}');
      Halt(1);
    end;
  end;
end.
