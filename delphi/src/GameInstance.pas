unit GameInstance;

interface

function ActivateExistingGame: Boolean;

implementation
uses
  Windows,
  Dialogs;

function ActivateExistingGame: Boolean; { Program entry at $00488D94. }
var
  ExistingWindow: HWND;
begin
  { The window class identifies the game, including renamed and copied executables. }
  ExistingWindow := FindWindow('TTSW10', nil);
  Result := ExistingWindow <> 0;
  if Result then
  begin
    ShowMessage('Sorry, cannot execute plural ''Tower of the Sorcerer''.');
    SetForegroundWindow(ExistingWindow);
  end;
end;

end.
