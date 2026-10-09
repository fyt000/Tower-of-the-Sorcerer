program RankingSmoke;
{$APPTYPE CONSOLE}
uses
  Windows,
  SysUtils,
  Classes,
  Forms,
  StdCtrls,
  FileCtrl,
  GameForms,
  GameState,
  Persistence;
{$R ..\GameResources.res}

procedure Require(Value: Boolean; const Message: string);
begin
  if not Value then
    raise Exception.Create(Message);
end;

procedure Run;
var
  Form: TTSW10;
  Ranking: TForm2;
  Holder: TForm4;
  Rows: TRankingTable;
  Names: TRankingNames;
  I: Integer;
  Destination, SettingsPath: string;
begin
  Require(ParamCount = 2, 'RankingSmoke requires fixture directory and assets');
  SaveDirectory := ParamStr(1);
  AssetDirectory := ParamStr(2);
  Application.Initialize;
  Form := TTSW10.Create(nil);
  MainForm := Form;
  Ranking := TForm2.Create(nil);
  RankingForm := Ranking;
  Holder := TForm4.Create(nil);
  DataHolderForm := Holder;
  try
    Form.Timer2.Enabled := False;
    FillChar(Hero, SizeOf(Hero), 0);
    FillChar(Maps, SizeOf(Maps), 0);
    Hero.hp := 100;
    Hero.floor := 1;
    Hero.x := 5;
    Hero.y := 10;
    Hero.Word628 := -4;
    WriteSave(SaveSlotPath(0), True);
    for I := 1 to 5 do
    begin
      DefaultRanking(I, -4, Rows, Names);
      WriteRanking(I, -4, Rows, Names);
    end;
    Ranking.formactivate(nil);
    Require(not Ranking.Visible, 'Ranking fixture must stay hidden');
    Require(
        (Ranking.Memo1.Text = '1')
            and (Ranking.Memo10.Text = '10')
            and (Ranking.Memo61.Text = 'RANKING of Top 10'),
        'Ranking headings and row numbers'
    );
    Require(
        (Ranking.Memo60.Top + Ranking.Memo60.Height <= Ranking.Button6.Top)
            and (Ranking.Button1.Left + Ranking.Button1.Width <= Ranking.ClientWidth),
        'Ranking table and buttons fit window'
    );
    for I := 1 to 5 do
    begin
      case I of
        1: Ranking.BitBtn1Click(nil);
        2: Ranking.BitBtn2Click(nil);
        3: Ranking.BitBtn3Click(nil);
        4: Ranking.BitBtn4Click(nil);
        5: Ranking.BitBtn5Click(nil);
      end;
      DefaultRanking(I, -4, Rows, Names);
      Require(
          (Ranking.Memo11.Text = '100')
              and (Ranking.Memo20.Text = '10')
              and (Ranking.Memo21.Text = Names[0])
              and (Ranking.Memo31.Text = IntToStr(Rows[0, 1]))
              and (Ranking.Memo41.Text = IntToStr(Rows[0, 2]))
              and (Ranking.Memo51.Text = IntToStr(Rows[0, 3])),
          'All five ranking menu categories'
      );
    end;
    Ranking.Button6Click(nil);
    Require(Form.Timer2.Enabled and (Ranking.ModalResult = mrOk), 'Ranking close resumes game');
    Destination := SaveDirectory + '\relocated';
    Require(
        CreateDir(Destination) or DirectoryExists(Destination),
        'Create folder selector destination'
    );
    Holder.DirectoryListBox1.Directory := Destination;
    PortableInstallation := True;
    Holder.Button1Click(nil);
    Require(
        (SaveDirectory = Destination) and (Form.Memo12.Lines[0] = Destination),
        'Data-folder selection updates live installation'
    );
    for I := 1 to 5 do
      Require(ReadRanking(I, -4, Rows, Names), 'Data-folder selection preserves all rankings');
    SettingsPath := ExtractFilePath(ParamStr(0)) + 'TSW12.INI';
    Require(FileExists(SettingsPath), 'Portable data-folder settings stay beside executable');
    SaveDirectory := '';
    ConfigurePaths(ParamStr(2), '');
    Require(SaveDirectory = Destination, 'Portable startup restores selected data folder');
    Writeln('{"ranking_ui":"passed","categories":5,"data_folder":"passed"}');
  finally
    MainForm := nil;
    RankingForm := nil;
    DataHolderForm := nil;
    Holder.Free;
    Ranking.Free;
    Form.Free;
  end;
end;

begin
  try
    Run;
  except
    on E: Exception do
    begin
      Writeln(E.ClassName, ': ', E.Message);
      Halt(1);
    end;
  end;
end.
