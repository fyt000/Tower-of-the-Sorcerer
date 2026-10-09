program Tower;

uses
  SysUtils,
  Forms,
  GameForms,
  GameState,
  GameCore,
  GameContent;
{$R GameResources.res}

var
  I: Integer;
  Assets, Saves: string;
begin
  Application.Initialize;
  Assets := '';
  Saves := '';
  I := 1;
  while I <= ParamCount do
  begin
    if ParamStr(I) = '--assets' then
    begin
      Inc(I);
      Assets := ParamStr(I);
    end
    else if ParamStr(I) = '--save-dir' then
    begin
      Inc(I);
      Saves := ParamStr(I);
    end
    else if ParamStr(I) = '--no-intro' then
      SkipIntroduction := True;
    Inc(I);
  end;
  if Assets <> '' then
    ConfigurePaths(Assets, Saves);
  LoadGameContent;
  Application.Title := 'Tower of the Sorcerer Ver1.2';
  Application.CreateForm(TTSW10, MainForm);
  { Create shared forms before timer and input handlers can reference them. }
  Application.CreateForm(TAboutBox, AboutBox);
  Application.CreateForm(TForm2, RankingForm);
  Application.CreateForm(TForm4, DataHolderForm);
  Application.Run;
end.
