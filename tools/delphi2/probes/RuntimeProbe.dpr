program RuntimeProbe;

{$APPTYPE CONSOLE}
{$O+,R-,Q-,S-}

uses
  Windows, Messages, SysUtils, Classes, Controls, Forms, StdCtrls, ExtCtrls;

type
  TObserver = class
    Clicks, Ticks, WindowMessages, Exceptions: Integer;
    RaiseOnTick: Boolean;
    procedure OnClick(Sender: TObject);
    procedure OnTimer(Sender: TObject);
    procedure OnException(Sender: TObject; E: Exception);
    procedure WindowMethod(var Message: TMessage);
  end;

var
  Observer: TObserver;
  Form: TForm;
  Panel: TPanel;
  Button: TButton;
  Timer: TTimer;
  Window: HWND;
  Failures: Integer;
  StartTick: DWORD;
  Before: Integer;
  KeyState: TKeyboardState;

procedure Check(const Name: string; Passed: Boolean; Value: Integer);
begin
  if Passed then
    WriteLn('{"name":"', Name, '","passed":true,"value":', Value, '}')
  else
  begin
    WriteLn('{"name":"', Name, '","passed":false,"value":', Value, '}');
    Inc(Failures);
  end;
end;

procedure Observe(const Name: string; Value: Integer);
begin
  WriteLn('{"name":"', Name, '","value":', Value, '}');
end;

procedure TObserver.OnClick(Sender: TObject);
begin
  Inc(Clicks);
end;

procedure TObserver.OnTimer(Sender: TObject);
begin
  Inc(Ticks);
  if RaiseOnTick then raise Exception.Create('Delphi 2 timer probe');
end;

procedure TObserver.OnException(Sender: TObject; E: Exception);
begin
  Inc(Exceptions);
end;

procedure TObserver.WindowMethod(var Message: TMessage);
begin
  if Message.Msg = WM_USER + 17 then
  begin
    Inc(WindowMessages);
    Message.Result := Message.WParam + Message.LParam;
  end;
end;

procedure CheckEscape(const Name: string; Expected: Integer; KeyData: Longint);
var
  Before, Handled: Integer;
begin
  Before := Observer.Clicks;
  Handled := Button.Perform(CM_DIALOGKEY, VK_ESCAPE, KeyData);
  Check(Name, (Observer.Clicks - Before = Expected) and
    (Handled = Expected), Observer.Clicks - Before);
end;

begin
  Failures := 0;
  { This is a framework probe. It never loads or launches TSW.exe. }
  FillChar(KeyState, SizeOf(KeyState), 0);
  SetKeyboardState(KeyState);
  Observer := TObserver.Create;
  Form := TForm.CreateNew(nil);
  try
    Panel := TPanel.Create(Form);
    Panel.Parent := Form;
    Button := TButton.Create(Form);
    Button.Parent := Panel;
    Button.Cancel := True;
    Button.OnClick := Observer.OnClick;
    Button.ModalResult := 7;

    Observe('TControl.InstanceSize', TControl.InstanceSize);
    Observe('TWinControl.InstanceSize', TWinControl.InstanceSize);
    Observe('TButton.InstanceSize', TButton.InstanceSize);
    Observe('TForm.InstanceSize', TForm.InstanceSize);
    Observe('TTimer.InstanceSize', TTimer.InstanceSize);
    Check('CanFocus.enabled', Button.CanFocus, Ord(Button.CanFocus));
    CheckEscape('Escape.enabled', 1, 0);
    Check('Escape.modal-result', Form.ModalResult = 7, Form.ModalResult);
    Button.Enabled := False;
    Check('CanFocus.button-disabled', not Button.CanFocus, Ord(Button.CanFocus));
    CheckEscape('Escape.button-disabled', 0, 0);
    Before := Observer.Clicks;
    Button.Click;
    Check('Click.direct-disabled', Observer.Clicks - Before = 1, Observer.Clicks - Before);
    Button.Enabled := True;
    Panel.Enabled := False;
    CheckEscape('Escape.parent-disabled', 0, 0);
    Panel.Enabled := True;
    Panel.Visible := False;
    CheckEscape('Escape.parent-hidden', 0, 0);
    Panel.Visible := True;
    Button.Visible := False;
    CheckEscape('Escape.button-hidden', 0, 0);
    Button.Visible := True;
    CheckEscape('Escape.alt', 0, $20000000);
    CheckEscape('Escape.reenabled', 1, 0);
    Button.Default := True;
    Button.Perform(CM_FOCUSCHANGED, 0, 0);
    Before := Observer.Clicks;
    Button.Perform(CM_DIALOGKEY, VK_RETURN, 0);
    Check('Enter.default-active', Observer.Clicks - Before = 1, Observer.Clicks - Before);

    Window := AllocateHWnd(Observer.WindowMethod);
    try
      Check('GeneratedWndProc.result', SendMessage(Window, WM_USER + 17, 7, 11) = 18,
        Observer.WindowMessages);
      Check('GeneratedWndProc.callback', Observer.WindowMessages = 1, Observer.WindowMessages);
    finally
      DeallocateHWnd(Window);
    end;

    Timer := TTimer.Create(nil);
    try
      Timer.Enabled := False;
      Timer.Interval := 10;
      Timer.OnTimer := Observer.OnTimer;
      Timer.Enabled := True;
      StartTick := GetTickCount;
      repeat
        Application.ProcessMessages;
        Sleep(1);
      until (Observer.Ticks >= 2) or (GetTickCount - StartTick >= 2000);
      Check('Timer.windows-dispatch', Observer.Ticks >= 2, Observer.Ticks);
      Timer.Enabled := False;
      Application.ProcessMessages;
      Before := Observer.Ticks;
      StartTick := GetTickCount;
      repeat
        Application.ProcessMessages;
        Sleep(1);
      until GetTickCount - StartTick >= 75;
      Check('Timer.disabled', Observer.Ticks = Before, Observer.Ticks - Before);
      { TTimer.WndProc has no Enabled check: registration eligibility and
        delivery of an already generated WM_TIMER are different boundaries.
        $28 is the window-handle field, checked against the supplied source. }
      Window := PLongint(Longint(Timer) + $28)^;
      Before := Observer.Ticks;
      PostMessage(Window, WM_TIMER, 1, 0);
      Application.ProcessMessages;
      Check('Timer.delivered-while-disabled', Observer.Ticks - Before = 1, Observer.Ticks - Before);
      Application.OnException := Observer.OnException;
      Observer.RaiseOnTick := True;
      PostMessage(Window, WM_TIMER, 1, 0);
      Application.ProcessMessages;
      Check('Timer.exception-continuation', Observer.Exceptions = 1, Observer.Exceptions);
      Observer.RaiseOnTick := False;
      Timer.OnTimer := nil;
      Before := Observer.Ticks;
      PostMessage(Window, WM_TIMER, 1, 0);
      Application.ProcessMessages;
      Check('Timer.no-handler', Observer.Ticks = Before, Observer.Ticks - Before);
    finally
      Timer.Free;
    end;
  finally
    Form.Free;
    Observer.Free;
  end;
  Halt(Ord(Failures <> 0));
end.
