program InstanceSmoke;
{$APPTYPE CONSOLE}
uses
  Windows,
  SysUtils,
  Classes,
  Controls,
  Forms,
  StdCtrls,
  ExtCtrls,
  GameInstance;

const
  WarningText = 'Sorry, cannot execute plural ''Tower of the Sorcerer''.';

type
  TTSW10 = class(TForm);
  TUnrelatedForm = class(TForm);
  TDialogDismiss = class
    MarkerPath: string;
    Started: DWORD;
    SawWarning: Boolean;
    procedure Tick(Sender: TObject);
  end;

var
  ProbeExitCode: Integer;

procedure WriteMarker(const Path: string);
var
  Marker: TextFile;
begin
  AssignFile(Marker, Path);
  Rewrite(Marker);
  try
    WriteLn(Marker, 'ready');
  finally
    CloseFile(Marker);
  end;
end;

procedure TDialogDismiss.Tick(Sender: TObject);
var
  I, J: Integer;
  Dialog: TForm;
begin
  { Screen contains this process's VCL forms, so no other dialog can be closed. }
  for I := 0 to Screen.FormCount - 1 do
  begin
    Dialog := Screen.Forms[I];
    for J := 0 to Dialog.ComponentCount - 1 do
      if (Dialog.Components[J] is TLabel)
          and (TLabel(Dialog.Components[J]).Caption = WarningText) then
      begin
        SawWarning := True;
        WriteMarker(MarkerPath);
        Dialog.ModalResult := mrOk;
        Exit;
      end;
  end;
  if GetTickCount - Started >= 3000 then
    Halt(3);
end;

procedure RunOwner;
var
  Started: DWORD;
  Form: TForm;
  Window: HWND;
begin
  Application.Initialize;
  if ParamStr(2) = 'game' then
  begin
    Form := TTSW10.CreateNew(nil);
    Form.Caption := 'Instance fixture with an unrelated caption';
  end
  else
  begin
    Form := TUnrelatedForm.CreateNew(nil);
    Form.Caption := 'Tower of the Sorcerer Ver1.2';
  end;
  try
    { Create an invisible top-level window with no DFM or game data. }
    Window := Form.Handle;
    if Window = 0 then
      raise Exception.Create('Instance fixture has no window');
    WriteMarker(ParamStr(3));
    Started := GetTickCount;
    repeat
      if FileExists(ParamStr(4)) then
        Exit;
      Application.ProcessMessages;
      Sleep(10);
    until GetTickCount - Started >= 15000;
    raise Exception.Create('Instance fixture release marker timed out');
  finally
    Form.Free;
  end;
end;

procedure RunChallenger;
var
  Dismiss: TDialogDismiss;
  Timer: TTimer;
  Existing: Boolean;
begin
  Dismiss := TDialogDismiss.Create;
  Timer := TTimer.Create(nil);
  try
    Dismiss.MarkerPath := ParamStr(2);
    Dismiss.Started := GetTickCount;
    Timer.Interval := 10;
    Timer.OnTimer := Dismiss.Tick;
    Timer.Enabled := True;
    { The application entry checks before Application.Initialize. }
    Existing := ActivateExistingGame;
    Timer.Enabled := False;
    if Existing <> Dismiss.SawWarning then
      raise Exception.Create('Existing-game decision did not match the warning dialog');
    if Existing then
      ProbeExitCode := 2;
  finally
    Timer.Free;
    Dismiss.Free;
  end;
end;

procedure Run;
begin
  if (ParamCount = 1) and (ParamStr(1) = '--available') then
  begin
    { This read-only check prevents tests from activating a user's game. }
    if FindWindow('TTSW10', nil) <> 0 then
      ProbeExitCode := 2;
  end
  else if (ParamCount = 4) and (ParamStr(1) = '--owner') then
    RunOwner
  else if (ParamCount = 2) and (ParamStr(1) = '--check') then
    RunChallenger
  else
    raise Exception.Create('InstanceSmoke requires --owner, --check, or --available');
end;

begin
  try
    Run;
  except
    on Error: Exception do
    begin
      WriteLn(Error.Message);
      Halt(1);
    end;
  end;
  Halt(ProbeExitCode);
end.
