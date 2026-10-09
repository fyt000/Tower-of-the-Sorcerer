program Tower;

uses Forms, OriginalForms, OriginalState, OriginalCore, OriginalContent;
{$R OriginalResources.res}

begin
  Application.Initialize;
  LoadOriginalContent;
  Application.Title := 'Tower of the Sorcerer Ver1.2';
  Application.CreateForm(TTSW10, MainForm);
  { Original entry $00488DDC-$00488E0A creates these three forms eagerly. }
  Application.CreateForm(TAboutBox, AboutBox);
  Application.CreateForm(TForm2, RankingForm);
  Application.CreateForm(TForm4, DataHolderForm);
  Application.Run;
end.
