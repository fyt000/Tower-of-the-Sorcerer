var
  RankingCategory: Integer;
  RankingRows: TRankingTable;
  RankingNames: TRankingNames;
  RankingHero: THeroState;
  RankingMaps: TFloorMaps;

procedure TAboutBox.copyrightonclick(Sender: TObject); { $004345A4 }
begin
  ShellExecute(
      Handle,
      'open',
      'http://plaza.across.or.jp/~furano/index.html',
      nil,
      nil,
      SW_SHOWNORMAL
  );
end;

procedure TTSW10.savework; { $0047EADC }
begin
  SaveChecksums(Hero);
  if FileExists(IOPath) then
    if MessageDlg('Overwrite. Is it true?', mtConfirmation, [mbYes, mbNo], 0) <> mrYes then
      Exit;
  try
    WriteSave(IOPath, False);
    TileClass := 134;
    disp;
  except
    on E: Exception do
      ShowMessage('Cannot save game: ' + E.Message);
  end;
end;

procedure TTSW10.loadwork; { $0047E7D4 }
begin
  if BGMON1.Checked then
    MediaPlayer5.Close;
  try
    ReadSave(IOPath, False);
    syokidata2;
    TileClass := 133;
    disp;
  except
    on E: Exception do
      ShowMessage('Cannot load game: ' + E.Message);
  end;
  if BGMON1.Checked then
  begin
    soundcheck;
    soundplay;
  end;
end;

procedure SelectSlot(Form: TTSW10; Slot: Integer; Saving: Boolean);
var
  I: Integer;
  Item: TMenuItem;
begin
  for I := 1 to 8 do
  begin
    if Saving then
      Item := TMenuItem(Form.FindComponent('Save' + IntToStr(I) + '1'))
    else
      Item := TMenuItem(Form.FindComponent('Load' + IntToStr(I) + '1'));
    Item.Checked := I = Slot;
  end;
end;

procedure UpdateFairyRanking(Form: TTSW10; Category: Longint);
var
  Ranking: TRankingTable;
  Names: TRankingNames;
  Row: Integer;
begin
  Hero.Word344 := 0;
  Hero.Word348 := Category;
  if (Category < 1) or (Category > 5) then
    Exit;
  ReadRanking(Category, Hero.Word628, Ranking, Names);
  { The final tie-break deliberately compares attack + defense - row HP
    with row attack, matching the saved ranking rules. }
  for Row := 0 to 9 do
    if (Hero.Word340 > Ranking[Row, 0])
        or ((Hero.Word340 = Ranking[Row, 0])
            and ((Hero.hp > Ranking[Row, 1])
                or ((Hero.hp = Ranking[Row, 1])
                    and (Hero.attack + Hero.defense - Ranking[Row, 1] > Ranking[Row, 2])))) then
    begin
      Hero.Word344 := Row + 1;
      Break;
    end;
  WriteSave(SaveSlotPath(0), True);
end;

procedure LoadSlot(Form: TTSW10; Slot: Integer);
begin
  Form.Timer4.Enabled := False;
  Form.itemdel;
  try
    { Preserve the current game in save0.dat before attempting a slot load. }
    WriteSave(SaveSlotPath(0), True);
    IOPath := SaveSlotPath(Slot);
    SelectSlot(Form, Slot, False);
    Form.loadwork;
  finally
    Form.itemlive;
    Form.Timer1.Enabled := True;
  end;
end;

procedure SaveSlot(Form: TTSW10; Slot: Integer);
begin
  Form.itemdel;
  try
    IOPath := SaveSlotPath(Slot);
    SelectSlot(Form, Slot, True);
    Form.savework;
  finally
    Form.itemlive;
  end;
end;

procedure TTSW10.Load11Click(Sender: TObject);
begin
  LoadSlot(Self, 1);
end;
procedure TTSW10.Load21Click(Sender: TObject);
begin
  LoadSlot(Self, 2);
end;
procedure TTSW10.Load31Click(Sender: TObject);
begin
  LoadSlot(Self, 3);
end;
procedure TTSW10.Load41Click(Sender: TObject);
begin
  LoadSlot(Self, 4);
end;
procedure TTSW10.Load51Click(Sender: TObject);
begin
  LoadSlot(Self, 5);
end;
procedure TTSW10.Load61Click(Sender: TObject);
begin
  LoadSlot(Self, 6);
end;
procedure TTSW10.Load71Click(Sender: TObject);
begin
  LoadSlot(Self, 7);
end;
procedure TTSW10.Load81Click(Sender: TObject);
begin
  LoadSlot(Self, 8);
end;
procedure TTSW10.Save11Click(Sender: TObject);
begin
  SaveSlot(Self, 1);
end;
procedure TTSW10.Save21Click(Sender: TObject);
begin
  SaveSlot(Self, 2);
end;
procedure TTSW10.Save31Click(Sender: TObject);
begin
  SaveSlot(Self, 3);
end;
procedure TTSW10.Save41Click(Sender: TObject);
begin
  SaveSlot(Self, 4);
end;
procedure TTSW10.Save51Click(Sender: TObject);
begin
  SaveSlot(Self, 5);
end;
procedure TTSW10.Save61Click(Sender: TObject);
begin
  SaveSlot(Self, 6);
end;
procedure TTSW10.Save71Click(Sender: TObject);
begin
  SaveSlot(Self, 7);
end;
procedure TTSW10.Save81Click(Sender: TObject);
begin
  SaveSlot(Self, 8);
end;

procedure TTSW10.OptionSave1Click(Sender: TObject); { $0047D324 }
var
  Stream: TFileStream;
begin
  if MessageDlg('Save options. Is it true?', mtConfirmation, [mbYes, mbNo], 0) <> mrYes then
    Exit;
  GameOptions[0] := Memo1.Font.Size;
  GameOptions[1] := Edit8.Font.Size;
  GameOptions[2] := 0;
  GameOptions[3] := 2;
  if High1.Checked then
    GameOptions[3] := 1;
  if Low1.Checked then
    GameOptions[3] := 3;
  try
    Stream := TFileStream.Create(SaveDataPath('option.dat'), fmCreate);
    try
      Stream.WriteBuffer(GameOptions, 10);
    finally
      Stream.Free;
    end;
    ShowMessage('Done.');
  except
    on E: Exception do
      ShowMessage('Cannot save options: ' + E.Message);
  end;
end;

function RankingNameControl(Form: TForm2; Row: Integer): TMemo;
begin
  if Row = 0 then
    Result := Form.Memo21
  else
    Result := TMemo(Form.FindComponent('Memo' + IntToStr(21 + Row)));
end;

procedure TForm2.loadwork; { $0043A3FC }
begin
  ReadSaveRecords(SaveSlotPath(0), True, RankingMaps, RankingHero);
end;

procedure TForm2.scoreload; { $00437F2C }
var
  Row: Integer;
  Button: TBitBtn;
begin
  if (RankingCategory < 1) or (RankingCategory > 5) then
    RankingCategory := 1;
  ReadRanking(RankingCategory, RankingHero.Word628, RankingRows, RankingNames);
  for Row := 0 to 9 do
    RankingNameControl(Self, Row).Text := RankingNames[Row];
  Button := TBitBtn(FindComponent('BitBtn' + IntToStr(RankingCategory)));
  if Visible and Button.CanFocus then
    Button.SetFocus;
end;

procedure TForm2.scoresave; { $00439CE0 }
var
  Row: Integer;
begin
  for Row := 0 to 9 do
    RankingNames[Row] := RankingNameControl(Self, Row).Lines[0];
  WriteRanking(RankingCategory, RankingHero.Word628, RankingRows, RankingNames);
  RankingHero.Word340 := 0;
  RankingHero.Word344 := 0;
  RankingHero.Word348 := 0;
  WriteSaveRecords(SaveSlotPath(0), RankingMaps, RankingHero);
end;

procedure TForm2.hyouji; { $00436C14 }
var
  Row, Column, Rank: Integer;
  Name: string;
  Memo: TMemo;
begin
  scoreload;
  Rank := RankingHero.Word344;
  if (RankingHero.Word348 = RankingCategory) and (Rank > 0) and (Rank <= 10) then
  begin
    Name := '';
    if InputQuery('Input your name', 'Please input within 18 words', Name) and (Name <> '') then
    begin
      for Row := 9 downto Rank do
      begin
        RankingNames[Row] := RankingNames[Row - 1];
        for Column := 0 to 3 do
          RankingRows[Row, Column] := RankingRows[Row - 1, Column];
      end;
      RankingNames[Rank - 1] := Copy(Name, 1, 18);
      RankingRows[Rank - 1, 0] := RankingHero.Word340;
      RankingRows[Rank - 1, 1] := RankingHero.hp;
      RankingRows[Rank - 1, 2] := RankingHero.attack;
      RankingRows[Rank - 1, 3] := RankingHero.defense;
      for Row := 0 to 9 do
        RankingNameControl(Self, Row).Text := RankingNames[Row];
      scoresave;
    end;
    { Clear the pending entry after either submission or cancellation. }
    RankingHero.Word344 := 0;
    RankingHero.Word348 := 0;
    WriteSaveRecords(SaveSlotPath(0), RankingMaps, RankingHero);
  end;
  for Row := 0 to 9 do
    for Column := 0 to 3 do
    begin
      if Column = 0 then
        Memo := TMemo(FindComponent('Memo' + IntToStr(11 + Row)))
      else
        Memo := TMemo(FindComponent('Memo' + IntToStr(21 + Column * 10 + Row)));
      Memo.Text := IntToStr(RankingRows[Row, Column]);
    end;
end;

procedure TForm2.optionload; { $004375D8 }
var
  I, Size: Integer;
begin
  Size := 10;
  if MainForm.Large1.Checked then
    Size := 12;
  if MainForm.Small1.Checked then
    Size := 9;
  if MainForm.tiny1.Checked then
    Size := 8;
  for I := 0 to ComponentCount - 1 do
    if Components[I] is TMemo then
      TMemo(Components[I]).Font.Size := Size
    else if Components[I] is TButton then
      TButton(Components[I]).Font.Size := Size
    else if Components[I] is TBitBtn then
      TBitBtn(Components[I]).Font.Size := Size;
  Memo61.Font.Size := Size + 2;
end;

procedure TForm2.formactivate(Sender: TObject); { $00434BC4 }
var
  I, iVar1, iVar3, uVar2: Integer;
begin
  {$I RankingLayout.inc}
  RankingCategory := 0;
  try
    loadwork;
  except
    RankingHero := Hero;
    RankingMaps := Maps;
  end;
  optionload;
  for I := 0 to ComponentCount - 1 do
    if Components[I] is TMemo then
    begin
      TMemo(Components[I]).Visible := True;
      TMemo(Components[I]).Clear;
    end;
  for I := 1 to 10 do
    TMemo(FindComponent('Memo' + IntToStr(I))).Text := IntToStr(I);
  Memo61.Text := 'RANKING of Top 10';
  Memo62.Visible := False;
  Button6.Visible := True;
  Button1.Visible := False;
  BitBtn1.Visible := True;
  BitBtn2.Visible := True;
  BitBtn3.Visible := True;
  BitBtn4.Visible := True;
  BitBtn5.Visible := True;
  if (RankingHero.Word348 >= 1) and (RankingHero.Word348 <= 5) then
  begin
    RankingCategory := RankingHero.Word348;
    Button1.Visible := True;
    hyouji;
  end;
end;

procedure TForm2.Button6Click(Sender: TObject); { $00436BF0 }
begin
  MainForm.Timer2.Enabled := True;
  ModalResult := mrOk;
end;
procedure TForm2.form2onclose(Sender: TObject; var Action: TCloseAction); { $0043A504 }
begin
  MainForm.Timer2.Enabled := True;
  ModalResult := mrOk;
end;
procedure TForm2.BitBtn1Click(Sender: TObject);
begin
  RankingCategory := 1;
  Button1.Visible := True;
  hyouji;
end;
procedure TForm2.BitBtn2Click(Sender: TObject);
begin
  RankingCategory := 2;
  Button1.Visible := True;
  hyouji;
end;
procedure TForm2.BitBtn3Click(Sender: TObject);
begin
  RankingCategory := 3;
  Button1.Visible := True;
  hyouji;
end;
procedure TForm2.BitBtn4Click(Sender: TObject);
begin
  RankingCategory := 4;
  Button1.Visible := True;
  hyouji;
end;
procedure TForm2.BitBtn5Click(Sender: TObject);
begin
  RankingCategory := 5;
  Button1.Visible := True;
  hyouji;
end;
procedure TForm2.Button1Click(Sender: TObject); { $0043A5F0 }
var
  Row: Integer;
begin
  if MessageDlg('Initialize this data. Is it true?', mtConfirmation, [mbYes, mbNo], 0) <> mrYes then
    Exit;
  DefaultRanking(RankingCategory, RankingHero.Word628, RankingRows, RankingNames);
  for Row := 0 to 9 do
    RankingNameControl(Self, Row).Text := RankingNames[Row];
  WriteRanking(RankingCategory, RankingHero.Word628, RankingRows, RankingNames);
  hyouji;
end;

procedure TForm4.Button1Click(Sender: TObject); { $004402E8 }
var
  Destination, Source, SettingsPath: string;
  I: Integer;
  Lines: TStringList;
begin
  Destination := DirectoryListBox1.Directory;
  if not DirectoryExists(Destination) then
    Exit;
  Lines := TStringList.Create;
  try
    for I := 0 to 5 do
    begin
      if I = 0 then
        Source := 'option.dat'
      else
        Source := 'option' + IntToStr(I) + '.dat';
      if FileExists(SaveDataPath(Source))
          and (CompareText(
                  ExpandFileName(SaveDataPath(Source)),
                  ExpandFileName(Destination + '\' + Source))
              <> 0) then
        if not CopyFile(PChar(SaveDataPath(Source)), PChar(Destination + '\' + Source), False) then
          raise Exception.Create('Cannot copy ' + Source);
      if I > 0 then
      begin
        Source := 'option' + IntToStr(I) + '1.dat';
        if FileExists(SaveDataPath(Source))
            and (CompareText(
                    ExpandFileName(SaveDataPath(Source)),
                    ExpandFileName(Destination + '\' + Source))
                <> 0) then
          if not CopyFile(
              PChar(SaveDataPath(Source)),
              PChar(Destination + '\' + Source),
              False) then
            raise Exception.Create('Cannot copy ' + Source);
      end;
    end;
    SaveDirectory := Destination;
    Lines.Add(SaveDirectory);
    Lines.Add(AssetDirectory);
    Lines.Add(PlayerName);
    MainForm.Memo12.Lines.Assign(Lines);
    if PortableInstallation then
      SettingsPath := ExtractFilePath(ParamStr(0)) + 'TSW12.INI'
    else
      SettingsPath := WindowsDirectory + '\TSW12.INI';
    Lines.SaveToFile(SettingsPath);
    ModalResult := mrOk;
  finally
    Lines.Free;
  end;
end;

procedure TForm4.Button3Click(Sender: TObject); { $00440984 }
var
  Path: string;
begin
  Path := DirectoryListBox1.Directory + '\new';
  if InputQuery('Make holder', 'Please, input the name of holder', Path) then
    if CreateDir(Path) then
    begin
      DirectoryListBox1.Directory := Path;
      DriveComboBox1.Drive := Path[1];
      FileListBox1.Directory := Path;
      memo1.Text := Path;
    end;
end;
