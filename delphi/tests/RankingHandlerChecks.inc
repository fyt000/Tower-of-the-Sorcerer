type
  TRankingDialog = class
    NameText, Warning: string;
    Answer, Seen: Integer;
    Started: DWORD;
    procedure Tick(Sender: TObject);
  end;

procedure TRankingDialog.Tick(Sender: TObject);
var
  I, J: Integer;
  Dialog: TForm;
  Text: string;
begin
  for I := 0 to Screen.FormCount - 1 do
  begin
    Dialog := Screen.Forms[I];
    if Dialog.Caption = 'Input your name' then
    begin
      for J := 0 to Dialog.ComponentCount - 1 do
        if Dialog.Components[J] is TEdit then
          TEdit(Dialog.Components[J]).Text := NameText;
      Inc(Seen);
      Dialog.ModalResult := Answer;
      Exit;
    end;
    for J := 0 to Dialog.ComponentCount - 1 do
      if Dialog.Components[J] is TLabel then
      begin
        Text := TLabel(Dialog.Components[J]).Caption;
        if Text = 'Initialize this data. Is it true?' then
        begin
          Inc(Seen);
          Dialog.ModalResult := Answer;
          Exit;
        end;
        if (Text = 'Ranking data is abnormal. Use a temporary Ranking.')
            or (Text = 'Version of Ranking data is abnormal. Use a temporary Ranking.')
            or (Text = 'Version of Ranking data is old. Use a temporary Ranking.') then
        begin
          Inc(Seen);
          Warning := Text;
          Dialog.ModalResult := mrOk;
          Exit;
        end;
      end;
  end;
  if GetTickCount - Started > 5000 then
  begin
    Writeln('Ranking dialog timed out');
    for I := 0 to Screen.FormCount - 1 do
    begin
      Writeln('Form: ', Screen.Forms[I].Caption);
      for J := 0 to Screen.Forms[I].ComponentCount - 1 do
        if Screen.Forms[I].Components[J] is TLabel then
          Writeln('Label: ', TLabel(Screen.Forms[I].Components[J]).Caption);
    end;
    Halt(3);
  end;
end;

procedure RankingHandlerChecks(Ranking: TForm2);
var
  Category, Rank, Row, Column, Mode: Integer;
  Rows, BeforeRows: TRankingTable;
  Names, BeforeNames: TRankingNames;
  CheckpointHero: THeroState;
  CheckpointMaps: TFloorMaps;
  Dismiss: TRankingDialog;
  Timer: TTimer;
  Stream: TFileStream;
  Path: string;
begin
  Dismiss := TRankingDialog.Create;
  Timer := TTimer.Create(nil);
  try
    Timer.Interval := 10;
    Timer.OnTimer := Dismiss.Tick;
    Timer.Enabled := False;
    for Category := 1 to 5 do
    begin
      for Mode := 1 to 3 do
      begin
        DefaultRanking(Category, -4, Rows, Names);
        WriteRanking(Category, -4, Rows, Names);
        Path := SaveDataPath('option' + IntToStr(Category) + '.dat');
        if Mode = 3 then
          DeleteFile(Path)
        else
        begin
          if Mode = 1 then
            Inc(Rows[0, 0])
          else
            Rows[11, 5] := -300 - Category;
          Stream := TFileStream.Create(Path, fmCreate);
          try
            Stream.WriteBuffer(Rows, SizeOf(Rows));
          finally
            Stream.Free;
          end;
        end;
        Dismiss.Seen := 0;
        Dismiss.Warning := '';
        Dismiss.Started := GetTickCount;
        Timer.Enabled := True;
        Ranking.scoreload(Category);
        Timer.Enabled := False;
        Require(
            (Dismiss.Seen = 1) and (Ranking.Memo11.Text <> '') and (Ranking.Memo21.Text = Names[0]),
            'Ranking error path retains name table'
        );
        case Mode of
          1:
            Require(
                Dismiss.Warning = 'Ranking data is abnormal. Use a temporary Ranking.',
                'Checksum warning'
            );
          2:
            Require(
                Dismiss.Warning = 'Version of Ranking data is abnormal. Use a temporary Ranking.',
                'Version warning'
            );
          3:
            Require(
                Dismiss.Warning = 'Version of Ranking data is old. Use a temporary Ranking.',
                'Read failure warning'
            );
        end;
      end;
      DefaultRanking(Category, -4, Rows, Names);
      WriteRanking(Category, -4, Rows, Names);
    end;
    for Category := 1 to 5 do
      for Rank := 1 to 10 do
      begin
        DefaultRanking(Category, -4, BeforeRows, BeforeNames);
        WriteRanking(Category, -4, BeforeRows, BeforeNames);
        Hero.Word340 := 777;
        Hero.Word344 := Rank;
        Hero.Word348 := Category;
        Hero.hp := 7654;
        Hero.attack := 321;
        Hero.defense := 123;
        WriteSave(SaveSlotPath(0), True);
        Ranking.loadwork;
        Dismiss.NameText := 'A name longer than eighteen';
        Dismiss.Answer := mrOk;
        Dismiss.Seen := 0;
        Dismiss.Started := GetTickCount;
        Timer.Enabled := True;
        Ranking.hyouji(Category);
        Timer.Enabled := False;
        Require(Dismiss.Seen = 1, 'Pending rank prompts once');
        Require(ReadRanking(Category, -4, Rows, Names), 'Recovered score writer checksums');
        Require(
            (Names[Rank - 1] = Dismiss.NameText)
                and (Rows[Rank - 1, 0] = 777)
                and (Rows[Rank - 1, 1] = 7654)
                and (Rows[Rank - 1, 2] = 321)
                and (Rows[Rank - 1, 3] = 123),
            'Recovered name and score insertion'
        );
        for Row := Rank to 9 do
        begin
          Require(Names[Row] = BeforeNames[Row - 1], 'Name rows shift together');
          for Column := 0 to 3 do
            Require(Rows[Row, Column] = BeforeRows[Row - 1, Column], 'Numeric rows shift together');
        end;
        for Row := 0 to Rank - 2 do
        begin
          Require(Names[Row] = BeforeNames[Row], 'Higher names preserved');
          for Column := 0 to 3 do
            Require(Rows[Row, Column] = BeforeRows[Row, Column], 'Higher scores preserved');
        end;
        ReadSaveRecords(SaveSlotPath(0), True, CheckpointMaps, CheckpointHero);
        Require(
            (CheckpointHero.Word340 = 0)
                and (CheckpointHero.Word344 = 0)
                and (CheckpointHero.Word348 = 0),
            'Ranking submission clears checkpoint flags'
        );
      end;
    for Mode := 1 to 2 do
    begin
      DefaultRanking(1, -4, BeforeRows, BeforeNames);
      WriteRanking(1, -4, BeforeRows, BeforeNames);
      Hero.Word340 := 777;
      Hero.Word344 := 1;
      Hero.Word348 := 1;
      WriteSave(SaveSlotPath(0), True);
      Ranking.loadwork;
      Dismiss.NameText := '';
      if Mode = 1 then
        Dismiss.Answer := mrCancel
      else
        Dismiss.Answer := mrOk;
      Dismiss.Started := GetTickCount;
      Timer.Enabled := True;
      Ranking.hyouji(1);
      Timer.Enabled := False;
      Require(ReadRanking(1, -4, Rows, Names), 'Cancelled ranking remains valid');
      Require(
          (Names[0] = BeforeNames[0]) and (Rows[0, 0] = 100),
          'Cancelled ranking stays unchanged'
      );
      ReadSaveRecords(SaveSlotPath(0), True, CheckpointMaps, CheckpointHero);
      if Mode = 1 then
        Require(CheckpointHero.Word344 = 0, 'Cancel consumes pending entry')
      else
        Require(CheckpointHero.Word344 = 1, 'Empty accepted name leaves checkpoint pending');
    end;
    Hero.Word344 := 0;
    Hero.Word348 := 0;
    WriteSave(SaveSlotPath(0), True);
    Ranking.loadwork;
    Ranking.BitBtn1Click(nil);
    Require(Ranking.Button1.Enabled and Ranking.Button1.Visible, 'Category enables reset button');
    Rows[0, 0] := 333;
    WriteRanking(1, -4, Rows, Names);
    for Mode := 1 to 2 do
    begin
      if Mode = 1 then
        Dismiss.Answer := mrNo
      else
        Dismiss.Answer := mrYes;
      Dismiss.Started := GetTickCount;
      Timer.Enabled := True;
      Ranking.Button1Click(nil);
      Timer.Enabled := False;
      Require(ReadRanking(1, -4, Rows, Names), 'Reset ranking remains valid');
      if Mode = 1 then
        Require(Rows[0, 0] = 333, 'Reset No preserves data')
      else
        Require((Rows[0, 0] = 100) and (Names[0] = 'Skeleton A'), 'Reset Yes restores defaults');
    end;
    Writeln('{"ranking_handlers":"passed","insertions":50,"error_paths":15,"cancel_paths":2}');
  finally
    Timer.Free;
    Dismiss.Free;
  end;
end;
